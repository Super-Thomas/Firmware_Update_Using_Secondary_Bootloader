/**************************************************************************//**
 * @file     wwdt.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 15/04/01 7:32p $
 * @brief    M0519 series WWDT driver source file
 *
 * @note
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "M0519.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup M0519_WWDT_Driver WWDT Driver
  @{
*/

/** @addtogroup M0519_WWDT_EXPORTED_FUNCTIONS WWDT Exported Functions
  @{
*/

/**
  * @brief      Open WWDT function to start counting
  *
  * @param[in]  u32PreScale     Prescale period for the WWDT counter period. Valid values are:
  *                             - \ref WWDT_PRESCALER_1
  *                             - \ref WWDT_PRESCALER_2
  *                             - \ref WWDT_PRESCALER_4
  *                             - \ref WWDT_PRESCALER_8
  *                             - \ref WWDT_PRESCALER_16
  *                             - \ref WWDT_PRESCALER_32
  *                             - \ref WWDT_PRESCALER_64
  *                             - \ref WWDT_PRESCALER_128
  *                             - \ref WWDT_PRESCALER_192
  *                             - \ref WWDT_PRESCALER_256
  *                             - \ref WWDT_PRESCALER_384
  *                             - \ref WWDT_PRESCALER_512
  *                             - \ref WWDT_PRESCALER_768
  *                             - \ref WWDT_PRESCALER_1024
  *                             - \ref WWDT_PRESCALER_1536
  *                             - \ref WWDT_PRESCALER_2048
  * @param[in]  u32CmpValue     Setting the window compared value. Valid values are between 0x0 to 0x3F.
  * @param[in]  u32EnableInt    Enable WWDT interrupt function. Valid values are TRUE and FALSE.
  *
  * @return     None
  *
  * @details    This function make WWDT module start counting with different counter period and compared window value.
  * @note       Application can call this function valid only once after boot up.
  */
void WWDT_Open(uint32_t u32PreScale,
               uint32_t u32CmpValue,
               uint32_t u32EnableInt)
{
    WWDT->WWDTCR = u32PreScale |
                   (u32CmpValue << WWDT_WWDTCR_WINCMP_Pos) |
                   ((u32EnableInt == TRUE) ? WWDT_WWDTCR_WWDTIE_Msk : 0) |
                   WWDT_WWDTCR_WWDTEN_Msk;
    return;
}

/*@}*/ /* end of group M0519_WWDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M0519_WWDT_Driver */

/*@}*/ /* end of group M0519_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
