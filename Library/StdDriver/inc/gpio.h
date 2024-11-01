/**************************************************************************//**
 * @file     GPIO.h
 * @version  V3.00
 * $Revision: 9 $
 * $Date: 15/04/01 7:31p $
 * @brief    General Purpose I/O Driver Header File
 *
 * @note
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 * @copyright Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_EXPORTED_CONSTANTS GPIO Exported Constants
  @{
*/
#define GPIO_PIN_MAX            8 /*!< Specify Maximum Pins of Each GPIO Port */

/*---------------------------------------------------------------------------------------------------------*/
/*  PMD Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_PMD_INPUT          0x0UL /*!< Input Mode */
#define GPIO_PMD_OUTPUT         0x1UL /*!< Output Mode */
#define GPIO_PMD_OPEN_DRAIN     0x2UL /*!< Open-Drain Mode */
#define GPIO_PMD_QUASI          0x3UL /*!< Quasi-bidirectional Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO Interrupt Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INT_RISING         0x00010000UL /*!< Interrupt enable by Input Rising Edge */
#define GPIO_INT_FALLING        0x00000001UL /*!< Interrupt enable by Input Falling Edge */
#define GPIO_INT_BOTH_EDGE      0x00010001UL /*!< Interrupt enable by both Rising Edge and Falling Edge */
#define GPIO_INT_HIGH           0x01010000UL /*!< Interrupt enable by Level-High */
#define GPIO_INT_LOW            0x01000001UL /*!< Interrupt enable by Level-Level */

/*---------------------------------------------------------------------------------------------------------*/
/*  IMD Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_IMD_EDGE           0UL /*!< IMD Setting for Edge Trigger Mode */
#define GPIO_IMD_LEVEL          1UL /*!< IMD Setting for Edge Level Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  DBNCECON Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INT_CLK_ON         0x00000020UL /*!< DBNCECON setting for all IO pins edge detection circuit is always active after reset */
#define GPIO_INT_CLK_OFF        0x00000000UL /*!< DBNCECON setting for edge detection circuit is active only if IO pin corresponding GPIOx_IEN bit is set to 1 */

#define GPIO_DBCLKSRC_LIRC      0x00000010UL /*!< DBNCECON setting for de-bounce counter clock source is LIRC */
#define GPIO_DBCLKSRC_HCLK      0x00000000UL /*!< DBNCECON setting for de-bounce counter clock source is HCLK */

#define GPIO_DBCLKSEL_1         0x00000000UL /*!< DBNCECON setting for sampling cycle = 1 clocks */
#define GPIO_DBCLKSEL_2         0x00000001UL /*!< DBNCECON setting for sampling cycle = 2 clocks */
#define GPIO_DBCLKSEL_4         0x00000002UL /*!< DBNCECON setting for sampling cycle = 4 clocks */
#define GPIO_DBCLKSEL_8         0x00000003UL /*!< DBNCECON setting for sampling cycle = 8 clocks */
#define GPIO_DBCLKSEL_16        0x00000004UL /*!< DBNCECON setting for sampling cycle = 16 clocks */
#define GPIO_DBCLKSEL_32        0x00000005UL /*!< DBNCECON setting for sampling cycle = 32 clocks */
#define GPIO_DBCLKSEL_64        0x00000006UL /*!< DBNCECON setting for sampling cycle = 64 clocks */
#define GPIO_DBCLKSEL_128       0x00000007UL /*!< DBNCECON setting for sampling cycle = 128 clocks */
#define GPIO_DBCLKSEL_256       0x00000008UL /*!< DBNCECON setting for sampling cycle = 256 clocks */
#define GPIO_DBCLKSEL_512       0x00000009UL /*!< DBNCECON setting for sampling cycle = 512 clocks */
#define GPIO_DBCLKSEL_1024      0x0000000AUL /*!< DBNCECON setting for sampling cycle = 1024 clocks */
#define GPIO_DBCLKSEL_2048      0x0000000BUL /*!< DBNCECON setting for sampling cycle = 2048 clocks */
#define GPIO_DBCLKSEL_4096      0x0000000CUL /*!< DBNCECON setting for sampling cycle = 4096 clocks */
#define GPIO_DBCLKSEL_8192      0x0000000DUL /*!< DBNCECON setting for sampling cycle = 8192 clocks */
#define GPIO_DBCLKSEL_16384     0x0000000EUL /*!< DBNCECON setting for sampling cycle = 16384 clocks */
#define GPIO_DBCLKSEL_32768     0x0000000FUL /*!< DBNCECON setting for sampling cycle = 32768 clocks */


/** Define GPIO Pin Data Input/Output. It could be used to control each I/O pin by pin address mapping.
 *  Example 1:
 *
 *      P00 = 1;
 *
 *  It is used to set P0.0 to high;
 *
 *  Example 2:
 *
 *      if (P00)
 *          P00 = 0;
 *
 *  If P0.0 pin status is high, then set P0.0 data output to low.
 */
#define GPIO_PIN_DATA(port, pin)    (*((volatile uint32_t *)((GPIO_PIN_DATA_BASE+(0x20*(port))) + ((pin)<<2))))
#define P00             GPIO_PIN_DATA(0, 0) /*!< Specify P00 Pin Data Input/Output */
#define P01             GPIO_PIN_DATA(0, 1) /*!< Specify P01 Pin Data Input/Output */
#define P02             GPIO_PIN_DATA(0, 2) /*!< Specify P02 Pin Data Input/Output */
#define P03             GPIO_PIN_DATA(0, 3) /*!< Specify P03 Pin Data Input/Output */
#define P04             GPIO_PIN_DATA(0, 4) /*!< Specify P04 Pin Data Input/Output */
#define P05             GPIO_PIN_DATA(0, 5) /*!< Specify P05 Pin Data Input/Output */
#define P06             GPIO_PIN_DATA(0, 6) /*!< Specify P06 Pin Data Input/Output */
#define P07             GPIO_PIN_DATA(0, 7) /*!< Specify P07 Pin Data Input/Output */
#define P10             GPIO_PIN_DATA(1, 0) /*!< Specify P10 Pin Data Input/Output */
#define P11             GPIO_PIN_DATA(1, 1) /*!< Specify P11 Pin Data Input/Output */
#define P12             GPIO_PIN_DATA(1, 2) /*!< Specify P12 Pin Data Input/Output */
#define P13             GPIO_PIN_DATA(1, 3) /*!< Specify P13 Pin Data Input/Output */
#define P14             GPIO_PIN_DATA(1, 4) /*!< Specify P14 Pin Data Input/Output */
#define P15             GPIO_PIN_DATA(1, 5) /*!< Specify P15 Pin Data Input/Output */
#define P16             GPIO_PIN_DATA(1, 6) /*!< Specify P16 Pin Data Input/Output */
#define P17             GPIO_PIN_DATA(1, 7) /*!< Specify P17 Pin Data Input/Output */
#define P20             GPIO_PIN_DATA(2, 0) /*!< Specify P20 Pin Data Input/Output */
#define P21             GPIO_PIN_DATA(2, 1) /*!< Specify P21 Pin Data Input/Output */
#define P22             GPIO_PIN_DATA(2, 2) /*!< Specify P22 Pin Data Input/Output */
#define P23             GPIO_PIN_DATA(2, 3) /*!< Specify P23 Pin Data Input/Output */
#define P24             GPIO_PIN_DATA(2, 4) /*!< Specify P24 Pin Data Input/Output */
#define P25             GPIO_PIN_DATA(2, 5) /*!< Specify P25 Pin Data Input/Output */
#define P26             GPIO_PIN_DATA(2, 6) /*!< Specify P26 Pin Data Input/Output */
#define P27             GPIO_PIN_DATA(2, 7) /*!< Specify P27 Pin Data Input/Output */
#define P30             GPIO_PIN_DATA(3, 0) /*!< Specify P30 Pin Data Input/Output */
#define P31             GPIO_PIN_DATA(3, 1) /*!< Specify P31 Pin Data Input/Output */
#define P32             GPIO_PIN_DATA(3, 2) /*!< Specify P32 Pin Data Input/Output */
#define P33             GPIO_PIN_DATA(3, 3) /*!< Specify P33 Pin Data Input/Output */
#define P34             GPIO_PIN_DATA(3, 4) /*!< Specify P34 Pin Data Input/Output */
#define P35             GPIO_PIN_DATA(3, 5) /*!< Specify P35 Pin Data Input/Output */
#define P36             GPIO_PIN_DATA(3, 6) /*!< Specify P36 Pin Data Input/Output */
#define P37             GPIO_PIN_DATA(3, 7) /*!< Specify P37 Pin Data Input/Output */
#define P40             GPIO_PIN_DATA(4, 0) /*!< Specify P40 Pin Data Input/Output */
#define P41             GPIO_PIN_DATA(4, 1) /*!< Specify P41 Pin Data Input/Output */
#define P42             GPIO_PIN_DATA(4, 2) /*!< Specify P42 Pin Data Input/Output */
#define P43             GPIO_PIN_DATA(4, 3) /*!< Specify P43 Pin Data Input/Output */
#define P44             GPIO_PIN_DATA(4, 4) /*!< Specify P44 Pin Data Input/Output */
#define P45             GPIO_PIN_DATA(4, 5) /*!< Specify P45 Pin Data Input/Output */
#define P46             GPIO_PIN_DATA(4, 6) /*!< Specify P46 Pin Data Input/Output */
#define P47             GPIO_PIN_DATA(4, 7) /*!< Specify P47 Pin Data Input/Output */
#define P50             GPIO_PIN_DATA(5, 0) /*!< Specify P50 Pin Data Input/Output */
#define P51             GPIO_PIN_DATA(5, 1) /*!< Specify P51 Pin Data Input/Output */
#define P52             GPIO_PIN_DATA(5, 2) /*!< Specify P52 Pin Data Input/Output */
#define P53             GPIO_PIN_DATA(5, 3) /*!< Specify P53 Pin Data Input/Output */
#define P54             GPIO_PIN_DATA(5, 4) /*!< Specify P54 Pin Data Input/Output */
#define P55             GPIO_PIN_DATA(5, 5) /*!< Specify P55 Pin Data Input/Output */
#define P56             GPIO_PIN_DATA(5, 6) /*!< Specify P56 Pin Data Input/Output */
#define P57             GPIO_PIN_DATA(5, 7) /*!< Specify P57 Pin Data Input/Output */
#define P60             GPIO_PIN_DATA(6, 0) /*!< Specify P60 Pin Data Input/Output */
#define P61             GPIO_PIN_DATA(6, 1) /*!< Specify P61 Pin Data Input/Output */
#define P62             GPIO_PIN_DATA(6, 2) /*!< Specify P62 Pin Data Input/Output */
#define P63             GPIO_PIN_DATA(6, 3) /*!< Specify P63 Pin Data Input/Output */
#define P64             GPIO_PIN_DATA(6, 4) /*!< Specify P64 Pin Data Input/Output */
#define P65             GPIO_PIN_DATA(6, 5) /*!< Specify P65 Pin Data Input/Output */
#define P66             GPIO_PIN_DATA(6, 6) /*!< Specify P66 Pin Data Input/Output */
#define P67             GPIO_PIN_DATA(6, 7) /*!< Specify P67 Pin Data Input/Output */
#define P70             GPIO_PIN_DATA(7, 0) /*!< Specify P70 Pin Data Input/Output */
#define P71             GPIO_PIN_DATA(7, 1) /*!< Specify P71 Pin Data Input/Output */
#define P72             GPIO_PIN_DATA(7, 2) /*!< Specify P72 Pin Data Input/Output */
#define P73             GPIO_PIN_DATA(7, 3) /*!< Specify P73 Pin Data Input/Output */
#define P74             GPIO_PIN_DATA(7, 4) /*!< Specify P74 Pin Data Input/Output */
#define P75             GPIO_PIN_DATA(7, 5) /*!< Specify P75 Pin Data Input/Output */
#define P76             GPIO_PIN_DATA(7, 6) /*!< Specify P76 Pin Data Input/Output */
#define P77             GPIO_PIN_DATA(7, 7) /*!< Specify P77 Pin Data Input/Output */
#define P80             GPIO_PIN_DATA(8, 0) /*!< Specify P80 Pin Data Input/Output */
#define P81             GPIO_PIN_DATA(8, 1) /*!< Specify P81 Pin Data Input/Output */
#define P82             GPIO_PIN_DATA(8, 2) /*!< Specify P82 Pin Data Input/Output */
#define P83             GPIO_PIN_DATA(8, 3) /*!< Specify P83 Pin Data Input/Output */
#define P84             GPIO_PIN_DATA(8, 4) /*!< Specify P84 Pin Data Input/Output */
#define P85             GPIO_PIN_DATA(8, 5) /*!< Specify P85 Pin Data Input/Output */
#define P86             GPIO_PIN_DATA(8, 6) /*!< Specify P86 Pin Data Input/Output */
#define P87             GPIO_PIN_DATA(8, 7) /*!< Specify P87 Pin Data Input/Output */
#define P90             GPIO_PIN_DATA(9, 0) /*!< Specify P90 Pin Data Input/Output */
#define P91             GPIO_PIN_DATA(9, 1) /*!< Specify P91 Pin Data Input/Output */
#define P92             GPIO_PIN_DATA(9, 2) /*!< Specify P92 Pin Data Input/Output */
#define P93             GPIO_PIN_DATA(9, 3) /*!< Specify P93 Pin Data Input/Output */
#define P94             GPIO_PIN_DATA(9, 4) /*!< Specify P94 Pin Data Input/Output */
#define P95             GPIO_PIN_DATA(9, 5) /*!< Specify P95 Pin Data Input/Output */
#define P96             GPIO_PIN_DATA(9, 6) /*!< Specify P96 Pin Data Input/Output */
#define P97             GPIO_PIN_DATA(9, 7) /*!< Specify P97 Pin Data Input/Output */
#define PA0             GPIO_PIN_DATA(10, 0)/*!< Specify PA0 Pin Data Input/Output */
#define PA1             GPIO_PIN_DATA(10, 1)/*!< Specify PA1 Pin Data Input/Output */


/*@}*/ /* end of group GPIO_EXPORTED_CONSTANTS */


/** @addtogroup GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Clear GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     Clear the interrupt status of specified GPIO pin.
 */
#define GPIO_CLR_INT_FLAG(port, u32PinMask)         ((port)->ISF = (u32PinMask))

/**
 * @brief       Disable Pin De-bounce Function
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     Disable the interrupt de-bounce function of specified GPIO pin.
 */
#define GPIO_DISABLE_DEBOUNCE(port, u32PinMask)     ((port)->DBEN &= ~(u32PinMask))

/**
 * @brief       Enable Pin De-bounce Function
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     Enable the interrupt de-bounce function of specified GPIO pin.
 */
#define GPIO_ENABLE_DEBOUNCE(port, u32PinMask)      ((port)->DBEN |= (u32PinMask))

/**
 * @brief       Disable I/O Digital Input Path
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O digital input path of specified GPIO pin.
 */
#define GPIO_DISABLE_DIGITAL_PATH(port, u32PinMask) ((port)->OFFD |= ((u32PinMask)<<16))

/**
 * @brief       Enable I/O Digital Input Path
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O digital input path of specified GPIO pin.
 */
#define GPIO_ENABLE_DIGITAL_PATH(port, u32PinMask)  ((port)->OFFD &= ~((u32PinMask)<<16))

/**
 * @brief       Disable I/O DOUT mask
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     Disable I/O DOUT mask of specified GPIO pin.
 */
#define GPIO_DISABLE_DOUT_MASK(port, u32PinMask)    ((port)->DMASK &= ~(u32PinMask))

/**
 * @brief       Enable I/O DOUT mask
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     Enable I/O DOUT mask of specified GPIO pin.
 */
#define GPIO_ENABLE_DOUT_MASK(port, u32PinMask) ((port)->DMASK |= (u32PinMask))

/**
 * @brief       Get GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT0 ~ BIT7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be BIT0 ~ BIT1 for PA GPIO port.
 *
 * @retval      0           No interrupt at specified GPIO pin
 * @retval      1           The specified GPIO pin generate an interrupt
 *
 * @details     Get the interrupt status of specified GPIO pin.
 */
#define GPIO_GET_INT_FLAG(port, u32PinMask)     ((port)->ISF & (u32PinMask))

/**
 * @brief       Set De-bounce Sampling Cycle Time
 *
 * @param[in]   u32ClkSrc   The de-bounce counter clock source. It could be
 *                          - \ref GPIO_DBCTL_DBCLKSRC_HCLK
 *                          - \ref GPIO_DBCTL_DBCLKSRC_LIRC
 * @param[in]   u32ClkSel   The de-bounce sampling cycle selection. It could be \n
 *                          - \ref GPIO_DBCLKSEL_1
 *                          - \ref GPIO_DBCLKSEL_2
 *                          - \ref GPIO_DBCLKSEL_4
 *                          - \ref GPIO_DBCLKSEL_8
 *                          - \ref GPIO_DBCLKSEL_16
 *                          - \ref GPIO_DBCLKSEL_32
 *                          - \ref GPIO_DBCLKSEL_64
 *                          - \ref GPIO_DBCLKSEL_128
 *                          - \ref GPIO_DBCLKSEL_256
 *                          - \ref GPIO_DBCLKSEL_512
 *                          - \ref GPIO_DBCLKSEL_1024
 *                          - \ref GPIO_DBCLKSEL_2048
 *                          - \ref GPIO_DBCLKSEL_4096
 *                          - \ref GPIO_DBCLKSEL_8192
 *                          - \ref GPIO_DBCLKSEL_16384
 *                          - \ref GPIO_DBCLKSEL_32768
 *
 * @return      None
 *
 * @details     Set the interrupt de-bounce sampling cycle time based on the debounce counter clock source. \n
 *              Example: GPIO_SET_DEBOUNCE_TIME(GPIO_DBCLKSRC_LIRC, GPIO_DBCLKSEL_4). \n
 *              It's meaning the De-debounce counter clock source is internal 10 KHz and sampling cycle selection is 4. \n
 *              Then the target de-bounce sampling cycle time is (4)*(1/(10*1000)) s = 4*0.0001 s = 400 us,
 *              and system will sampling interrupt input once per 400 us.
 */
#define GPIO_SET_DEBOUNCE_TIME(u32ClkSrc, u32ClkSel)    (GPIO->DBNCECON = (GPIO_DBNCECON_ICLK_ON_Msk | (u32ClkSrc) | (u32ClkSel)))

/**
 * @brief       Get GPIO Port IN Data
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 *
 * @return      The specified port data
 *
 * @details     Get the PIN register of specified GPIO port.
 */
#define GPIO_GET_IN_DATA(port)  ((port)->PIN)

/**
 * @brief       Set GPIO Port OUT Data
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32Data     GPIO port data.
 *
 * @return      None
 *
 * @details     Set the Data into specified GPIO port.
 */
#define GPIO_SET_OUT_DATA(port, u32Data)    ((port)->DOUT = (u32Data))

/**
 * @brief       Toggle Specified GPIO pin
 *
 * @param[in]   u32Pin      Pxy
 *
 * @return      None
 *
 * @details     Toggle the specified GPIO pint.
 */
#define GPIO_TOGGLE(u32Pin) ((u32Pin) ^= 1)

/**
 * @brief       Enable External GPIO Interrupt 0
 *
 * @param[in]   port            GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32Pin          The pin of specified GPIO port.  \n
 *                              It could be 0 ~ 7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                              It could be 0 ~ 1 for PA GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              - \ref GPIO_INT_RISING
 *                              - \ref GPIO_INT_FALLING
 *                              - \ref GPIO_INT_BOTH_EDGE
 *                              - \ref GPIO_INT_HIGH
 *                              - \ref GPIO_INT_LOW
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_EnableEINT0    GPIO_EnableInt


/**
 * @brief       Disable External GPIO Interrupt 0
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32Pin      The pin of specified GPIO port. \n
 *                          It could be 0 ~ 7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be 0 ~ 1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     This function is used to disable specified GPIO pin interrupt.
 */
#define GPIO_DisableEINT0   GPIO_DisableInt


/**
 * @brief       Enable External GPIO Interrupt 1
 *
 * @param[in]   port            GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32Pin          The pin of specified GPIO port.  \n
 *                              It could be 0 ~ 7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                              It could be 0 ~ 1 for PA GPIO port.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              - \ref GPIO_INT_RISING
 *                              - \ref GPIO_INT_FALLING
 *                              - \ref GPIO_INT_BOTH_EDGE
 *                              - \ref GPIO_INT_HIGH
 *                              - \ref GPIO_INT_LOW
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
#define GPIO_EnableEINT1    GPIO_EnableInt


/**
 * @brief       Disable External GPIO Interrupt 1
 *
 * @param[in]   port        GPIO port. It could be P0, P1, P2, P3, P4, P5, P6 ,P7, P8, P9 or PA.
 * @param[in]   u32Pin      The pin of specified GPIO port. \n
 *                          It could be 0 ~ 7 for P0/P1/P2/P3/P4/P5/P6/P7/P8/P9 GPIO port. \n
 *                          It could be 0 ~ 1 for PA GPIO port.
 *
 * @return      None
 *
 * @details     This function is used to disable specified GPIO pin interrupt.
 */
#define GPIO_DisableEINT1   GPIO_DisableInt


void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs);
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin);


/*@}*/ /* end of group GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group GPIO_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__GPIO_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
