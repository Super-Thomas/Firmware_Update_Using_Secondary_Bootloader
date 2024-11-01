#include <stdio.h>
#include <stdlib.h>
#include "M0519.h"
#include "crc16.h"

#define PLLCON_SETTING  						(CLK_PLLCON_72MHz_HXT)
#define PLL_CLOCK       						(72000000)

#define DATAFLASH_UFWSIZE_ADDRESS		(0x0001F000)
#define DATAFLASH_UFWCRC16_ADDRESS	(0x0001F004)
#define CLEAR_VALUE									(0xFFFFFFFF)

#define APROM_UFW_ADDRESS						(0x0000F800)

#define	V6M_AIRCR_VECTKEY_DATA			(0x05FA0000UL)
#define V6M_AIRCR_SYSRESETREQ				(0x00000004UL)

uint32_t g_u32UpdatedFWSize = 0, g_u32CRC16Value = 0;

int FMC_Erase_User(uint32_t u32Addr)
{
	uint32_t Reg;
	FMC->ISPCMD = FMC_ISPCMD_PAGE_ERASE;
	FMC->ISPADR = u32Addr;
	FMC->ISPTRG = 0x1;
	__ISB();
	Reg = FMC->ISPCON;
	
	if (Reg & FMC_ISPCON_ISPFF_Msk) {
		FMC->ISPCON = Reg;
		return -1;
	}
	
	return 0;
}

int FMC_Read_User(uint32_t u32Addr, uint32_t *data)
{
	uint32_t Reg;
	FMC->ISPCMD = FMC_ISPCMD_READ;
	FMC->ISPADR = u32Addr;
	FMC->ISPDAT = 0;
	FMC->ISPTRG = 0x1;
	__ISB();
	Reg = FMC->ISPCON;
	
	if (Reg & FMC_ISPCON_ISPFF_Msk) {
		FMC->ISPCON = Reg;
		return -1;
	}
	
	*data = FMC->ISPDAT;
	return 0;
}

int FMC_Write_User(uint32_t u32Addr, uint32_t u32Data)
{
	uint32_t Reg;
	FMC->ISPCMD = FMC_ISPCMD_PROGRAM;
	FMC->ISPADR = u32Addr;
	FMC->ISPDAT = u32Data;
	FMC->ISPTRG = 0x1;
	__ISB();
	Reg = FMC->ISPCON;
	
	if (Reg & FMC_ISPCON_ISPFF_Msk) {
		FMC->ISPCON = Reg;
		return -1;
	}
	
	return 0;
}

void EraseAP(uint32_t addr_start, uint32_t addr_end)
{
	uint32_t eraseLoop = addr_start;
	
	for (; eraseLoop < addr_end; eraseLoop += FMC_FLASH_PAGE_SIZE) {
		FMC_Erase_User(eraseLoop);
	}
	
	return;
}

void ReadData(uint32_t addr_start, uint32_t addr_end, uint32_t *data) // Read data from flash
{
	uint32_t rLoop;
	
	for (rLoop = addr_start; rLoop < addr_end; rLoop += 4) {
		FMC_Read_User(rLoop, data);
		data++;
	}
	
	return;
}

void WriteData(uint32_t addr_start, uint32_t addr_end, uint32_t *data) // Write data into flash
{
	uint32_t wLoop;
	
	for (wLoop = addr_start; wLoop < addr_end; wLoop += 4) {
		FMC_Write_User(wLoop, *data);
		data++;
	}
}

//
void CalcCRC16(void)
{
	uint32_t i;
	uint32_t u32Length = g_u32UpdatedFWSize;
	uint32_t* pu16Data = (uint32_t*)malloc(sizeof(uint32_t) * FMC_FLASH_PAGE_SIZE);
	
	CRC16_Clear();
	
	for (i=0; i<g_u32UpdatedFWSize; i+=FMC_FLASH_PAGE_SIZE)
	{
		ReadData(APROM_UFW_ADDRESS + i, APROM_UFW_ADDRESS + i + FMC_FLASH_PAGE_SIZE, &pu16Data[0]);
		
		if (u32Length >= FMC_FLASH_PAGE_SIZE)
		{
			CRC16_Add((uint8_t *)&pu16Data[0], FMC_FLASH_PAGE_SIZE);
		}
		else
		{
			CRC16_Add((uint8_t *)&pu16Data[0], u32Length);
		}
		
		u32Length -= FMC_FLASH_PAGE_SIZE;
	}
	
	free(pu16Data);
}

void CopyFirmware(void)
{
	uint32_t i;
	uint32_t* pu16Data = (uint32_t*)malloc(sizeof(uint32_t) * FMC_FLASH_PAGE_SIZE);
	
	EraseAP(FMC_APROM_BASE, FMC_APROM_BASE + g_u32UpdatedFWSize);
	
	for (i=0; i<g_u32UpdatedFWSize; i+=FMC_FLASH_PAGE_SIZE)
	{
		ReadData(APROM_UFW_ADDRESS + i, APROM_UFW_ADDRESS + i + FMC_FLASH_PAGE_SIZE, &pu16Data[0]);
		WriteData(0x00 + i, 0x00 + i + FMC_FLASH_PAGE_SIZE, &pu16Data[0]);
	}
	
	free(pu16Data);
}

void ClearDataFlash(void)
{
	FMC_Erase(DATAFLASH_UFWSIZE_ADDRESS);
	FMC_Erase(DATAFLASH_UFWCRC16_ADDRESS);
}
//

void SYS_Init(void)
{
	CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk); // Enable External XTAL (4~24 MHz)
	CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk); // Waiting for External XTAL clock ready
	
	// Switch HCLK clock source to Internal RC and HCLK source divide 1
	CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_CLKDIV_HCLK(1));
	
	CLK_SetCoreClock(PLL_CLOCK); // Set core clock as PLL_CLOCK from PLL
	
	CLK_EnableModuleClock(UART0_MODULE); // Enable UART module clock
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_PLL, CLK_CLKDIV_UART(1)); // Select UART module clock source
	
	// Set P3 multi-function pins for UART0 RXD and TXD
	SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
	SYS->P3_MFP |= (SYS_MFP_P30_UART0_RXD | SYS_MFP_P31_UART0_TXD);
}

void UART0_Init(void)
{
	SYS_ResetModule(UART0_RST); // Reset UART
	
	UART_Open(UART0, 115200); // Configure UART0 and set UART0 Baudrate
}

int32_t main(void)
{
	uint32_t i;
	
	SYS_UnlockReg(); // Unlock protected registers
	
	SYS_Init(); // Init System, peripheral clock and multi-function I/O
	UART0_Init();
	FMC->ISPCON |= FMC_ISPCON_ISPEN_Msk; // Enable FMC ISP
	
	printf("\n\n");
  printf("+-------------------------------------------------------+\n");
  printf(" M0519 Bootloader Sample\n");
  printf("+-------------------------------------------------------+\n");
	
	g_u32UpdatedFWSize = FMC_Read(DATAFLASH_UFWSIZE_ADDRESS); // Read updated firmware size
	g_u32CRC16Value = FMC_Read(DATAFLASH_UFWCRC16_ADDRESS); // Read CRC-16
	for (i=0; i<1000000; i++);
	
	if (g_u32UpdatedFWSize != CLEAR_VALUE && g_u32CRC16Value != CLEAR_VALUE)
	{
		printf("Stored CRC-16: [0x%04x]\n", g_u32CRC16Value);
		printf("Calculate CRC-16 of updated firmware data...\n");
		CalcCRC16();
		printf("Calculated CRC-16: [0x%04x]\n", CRC16_GetValue());
		
		if (g_u32CRC16Value == CRC16_GetValue())
		{
			printf("CRC-16 matches!\n");
			
			printf("Updated firmware size: %d Bytes\n", g_u32UpdatedFWSize);
			printf("Copying the firmware [0x%08x] to [0x00000000]...\n", APROM_UFW_ADDRESS);
			CopyFirmware();
			ClearDataFlash();
			printf("Done.\n");
		}
		else
		{
			printf("CRC-16 does not match!\n");
		}
	}
	
	printf("Let's go boot to APROM.\n");
	for (i=0; i<1000000; i++);
	
	// Reset system and boot from APROM
  SYS->RSTSRC = (SYS_RSTSRC_RSTS_POR_Msk | SYS_RSTSRC_RSTS_RESET_Msk); /* Clear reset status flag */
  FMC->ISPCON &= ~(FMC_ISPCON_BS_Msk|FMC_ISPCON_ISPEN_Msk);
  SCB->AIRCR = (V6M_AIRCR_VECTKEY_DATA | V6M_AIRCR_SYSRESETREQ);
	
	while (1); // Trap the CPU
}
