# Firmware_Update_Using_Secondary_Bootloader

## Intro
This sample bootloader and firmware have feature for dual image updates (reliable updates) for Nuvoton M0519VE3AE MCU.
This feature that at least one image is bootable and can always works fine.
If occur event of accident during firmware update, bootloader can boot with original image by checking success flag for ISP update.
If occur event of accident during firmware copy, bootloader can retry to copy new image by checking success flag for firmware copy.

## Development environment
|N|Name|Description|Note|
|---|---|---|---|
|1|Windows OS|Windows 11 Home 23H2||
|2|ARM-MDK|Keil uVision v5.34.0.0|IDE|
|3|ARM Compiler|V5.06 update 7 (build 960)|Compiler|
|4|NuTiny-SDK-M0519V|NT-M0519V|Nuvoton EVB Board|

## System Overview
This sample bootloader and firmware made by based Nuvoton ISP function. If you want know more information for Nuvoton ISP function, Please refer below links.</br>
[ISPTool](https://github.com/OpenNuvoton/ISPTool)</br>
[Using_Nuvoton_ISP_on_the_Android](https://github.com/Super-Thomas/Using_Nuvoton_ISP_on_the_Android)</br>
[Nuvoton_ISP_Lite_for_Windows](https://github.com/Super-Thomas/Nuvoton_ISP_Lite_for_Windows)</br>

### Hardware configuration
![image](https://github.com/user-attachments/assets/0014fdc2-a2a1-4740-b01b-5edd1cbba289)</br>
The NuTiny-SDK-M0519V EVB Board is powered by PC via USB.</br>
You can run the ICP Program via USB and check the debugging messages via UART0(VCOM).</br>
You can run the ISP Program via UART1.</br>

### Flash structure of Nuvoton M0519VE3AE MCU
![image](https://github.com/user-attachments/assets/69975453-82b9-48be-af00-620715d184f9)</br>
The firmware runs on execution area(APROM Part-1).</br>
The new firmware data will be write to update area(APROM Part-2) by firmware with ISP function.</br>
The Flag area (Data Flash) have CRC-16 data for verifying firmware errors and flag for check the success about write firmware data.</br>
The bootloader runs on boot-loader area(LDROM).</br>

### Config values ​​of Nuvoton M0519VE3AE MCU
![image](https://github.com/user-attachments/assets/a45d2e60-51dd-4805-a811-f9aab3d4cad0)</br>
Boot Options: LDROM</br>
Enable Data Flash, Base Address: 0x1F000, Data Flash Size: 4 KB</br>

### Flow chart of Bootloader
![image](https://github.com/user-attachments/assets/852ffa44-bbe8-493f-9943-b93c2f46b75c)

### Flow chart of Firmware
![image](https://github.com/user-attachments/assets/ccf61618-e967-42b8-bd63-998ab23cda18)

## How to test
1. Please program to NuTiny-SDK-M0519V board with Nuvoton ICP Tool like below:
   - Binary/Bootloader.bin to LDROM
   - Binary/Firmware_Ver_A.bin to APROM
   - Config 0: 0xFFFFFF7E, Config 1: 0x0001F000 (Boot options: LDROM, Enable data flash, Base Address: 0x1F000, Data flash size: 4 KB)
2. Open the UART0(USB VCOM) port using Terminal(like as Tera-term).</br>
(Port settings: Baudrate 115200, Data 8-bit, Parity none, Stop bit 1, Flow control none)</br>
And then press reset button of NuTiny-SDK-M0519V board. You can check debug message from NuTiny-SDK-M0519V board.</br>
![image](https://github.com/user-attachments/assets/737f8b11-057e-4796-ad90-aecddcb569b4)
3. Please connect between NuTiny-SDK-M0519V board and ISP Tool using UART1.</br>
![image](https://github.com/user-attachments/assets/954b2288-0b2d-43e4-acf7-59444516d0bb)
4. Load binary of firmware version B to APROM of load file section. And then enable APROM of programming section. Then press start button.</br>
![image](https://github.com/user-attachments/assets/4a58c088-9fe0-42ea-8271-c3c484096d75)
5. Please press reset button of NuTiny-SDK-M0519V board when completed program. Then you can see the bootloader copying the firmware in debug message. After then you can see that firmware version B is running.</br>
![image](https://github.com/user-attachments/assets/a30ffcc9-4287-42f8-9ea1-1a9e7892a441)

## Thanks to
[AN12327 - Firmware Update Using Secondary Bootloader](https://www.nxp.com/docs/en/application-note/AN12327.pdf)</br>
[ISPTool](https://github.com/OpenNuvoton/ISPTool)</br>
[M0519 BSP](https://github.com/OpenNuvoton/M0519BSP)
