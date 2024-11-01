#include <stdio.h>
#include "M0519.h"
#include "ISP_USER.h"

#if 0
#define FIRMWARE_VERSION		('A')
#else
#define FIRMWARE_VERSION		('B')
#endif

#define PLLCON_SETTING  		(CLK_PLLCON_72MHz_HXT)
#define PLL_CLOCK       		(72000000)

#define MAX_PKT_SIZE       	64 // Define maximum packet size

__attribute__((aligned(4))) uint8_t  g_uart_rcvbuf[MAX_PKT_SIZE] = {0};
extern __attribute__((aligned(4))) uint8_t g_response_buff[64];
uint8_t volatile g_bUartDataReady = 0;
uint8_t volatile g_bufhead = 0;

uint8_t g_u8BlinkFlag = 0; // 0: LED Off, 1: LED On
uint8_t g_u8FWUpdateFlag = 0; // 0: Normal mode, 1: Firmware update mode

void UART1_IRQHandler(void)
{
	uint32_t u32IntSrc = UART1->ISR;
	
	// RDA FIFO interrupt and RDA timeout interrupt
  if (u32IntSrc & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk))
	{
		// Read data until RX FIFO is empty or data is over maximum packet size
		while (((UART1->FSR & UART_FSR_RX_EMPTY_Msk) == 0) && (g_bufhead < MAX_PKT_SIZE))
		{
			g_uart_rcvbuf[g_bufhead++] = UART1->RBR;
    }
	}
	
	// Reset data buffer index
	if (g_bufhead == MAX_PKT_SIZE)
	{
		g_bUartDataReady = TRUE;
    g_bufhead = 0;
	}
	else if (u32IntSrc & 0x10)
	{
		g_bufhead = 0;
  }
}

void TMR0_IRQHandler(void)
{
	if(TIMER_GetIntFlag(TIMER0) == 1)
	{
		// Clear Timer0 time-out interrupt flag
		TIMER_ClearIntFlag(TIMER0);
		
		g_u8BlinkFlag = !g_u8BlinkFlag;
	}
}

void SYS_Init(void)
{
	CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk); // Enable External XTAL (4~24 MHz)
	CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk); // Waiting for External XTAL clock ready
	
	// Switch HCLK clock source to Internal RC and HCLK source divide 1
	CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_CLKDIV_HCLK(1));
	
	CLK_SetCoreClock(PLL_CLOCK); // Set core clock as PLL_CLOCK from PLL
	
	CLK_EnableModuleClock(UART0_MODULE); // Enable UART module clock
	CLK_EnableModuleClock(UART1_MODULE); // Enable UART module clock
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_PLL, CLK_CLKDIV_UART(1)); // Select UART module clock source
	CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART_S_PLL, CLK_CLKDIV_UART(1)); // Select UART module clock source
	
	CLK_EnableModuleClock(TMR0_MODULE);
	
	// Set P3 multi-function pins for UART0 RXD and TXD
	SYS->P3_MFP &= ~(SYS_MFP_P30_Msk | SYS_MFP_P31_Msk);
	SYS->P3_MFP |= (SYS_MFP_P30_UART0_RXD | SYS_MFP_P31_UART0_TXD);
	
	// Set PA multi-function pins for UART1 RXD and TXD
	SYS->PA_MFP &= ~(SYS_MFP_PA0_Msk | SYS_MFP_PA1_Msk);
	SYS->PA_MFP |= (SYS_MFP_PA1_UART1_RXD | SYS_MFP_PA0_UART1_TXD);
}

void UART_Init(void)
{
  SYS_ResetModule(UART0_RST); // Reset UART
	SYS_ResetModule(UART1_RST); // Reset UART
	
	UART_Open(UART0, 115200); // Configure UART0 and set UART0 Baudrate
	UART_Open(UART1, 115200); // Configure UART1 and set UART1 Baudrate
	// Set UART Rx and RTS trigger level
  UART1->FCR = UART_FCR_RFITL_14BYTES | UART_FCR_RTS_TRI_LEV_14BYTES;
  // Set time-out interrupt comparator
  UART1->TOR = (UART1->TOR & ~UART_TOR_TOIC_Msk) | (0x40);
	
	// Enable Interrupt
  UART_EnableInt(UART1, (UART_IER_TIME_OUT_EN_Msk | UART_IER_TOUT_IEN_Msk | UART_IER_RDA_IEN_Msk));
	NVIC_SetPriority(UART1_IRQn, 2);
  NVIC_EnableIRQ(UART1_IRQn);
}

void GPIO_Init(void)
{
	GPIO_SetMode(P7, BIT7, GPIO_PMD_OUTPUT);
}

void TIMER_Init(void)
{
#if (FIRMWARE_VERSION == 'A')
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1); // 1 sec Timer
#else
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 3); // 0.3 sec Timer
#endif
  TIMER_EnableInt(TIMER0);
	NVIC_EnableIRQ(TMR0_IRQn);
	TIMER_Start(TIMER0);
}

void PutString(void)
{
	uint32_t i;
	// UART send response to master
  for (i = 0; i<MAX_PKT_SIZE; i++)
	{
		// Wait for TX not full
		while ((UART1->FSR & UART_FSR_TX_FULL_Msk));
		// UART send data
    UART1->THR = g_response_buff[i];
	}
}

uint8_t CheckFirmwareUpdate(void)
{
	if ((g_bufhead >= 4) || (g_bUartDataReady == TRUE))
	{
		uint32_t lcmd;
		lcmd = inpw(g_uart_rcvbuf);
		
		if (lcmd == CMD_CONNECT)
		{
			return 1;
		}
		else
		{
			g_bUartDataReady = FALSE;
			g_bufhead = 0;
    }
  }
	
	return 0;
}

int32_t main(void)
{
	SYS_UnlockReg(); // Unlock protected registers
	
	SYS_Init(); // Init System, peripheral clock and multi-function I/O
	UART_Init();
	FMC->ISPCON |=  FMC_ISPCON_ISPEN_Msk | FMC_ISPCON_APUEN_Msk; // Enable FMC ISP
	GPIO_Init();
	TIMER_Init();
	
	printf("\n\n");
  printf("+-------------------------------------------------------+\n");
  printf(" Hello World! Im firmware version %c.\n", FIRMWARE_VERSION);
  printf("+-------------------------------------------------------+\n");
	
	printf("CPU @ %dHz\n", SystemCoreClock);
#if (FIRMWARE_VERSION == 'A')
	printf("I can blink LED every 1 second.\n");
#else
	printf("I can blink LED every about 0.3 second.\n");
#endif
	
	UpdateFlashInfo();
	
	while (1)
	{
		P77 = g_u8BlinkFlag;
		
		if (g_u8FWUpdateFlag == 0) // Normal mode
		{
			g_u8FWUpdateFlag = CheckFirmwareUpdate();
			
			//
			// Drawing here.
			//
		}
		else // Firmware update mode
		{
			if (g_bUartDataReady == TRUE)
			{
				g_bUartDataReady = FALSE;
        ParseCmd(g_uart_rcvbuf, 64);
        PutString();
      }
		}
	}
}
