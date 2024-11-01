#ifndef __CRC16_H_
#define __CRC16_H_

#pragma pack(1) // Please refer about "Packing Bytes in Unions and Structures" for ARM.
// If without this option, there have some problem about wrong size of struct.

void CRC16_Clear(void);
uint16_t CRC16_Add(uint8_t* pu8Data, uint16_t u16Length);
uint16_t CRC16_GetValue(void);

#endif //__CRC16_H_
