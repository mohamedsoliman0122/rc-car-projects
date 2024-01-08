#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#include "UART.h"

/*************************** UART Send Data **************************/
void UART_SendString_BusyWait_Synch(u8* str);

void UART_SendString_Asynch(u8* str);

void UART_SendNumber_BusyWait(u32 num);

void UART_SendString_CheckSum(u8* str);


/*************************** UART Receive Data **************************/
void UART_ReceiveString_BusyWait_Synch(u8* str);

u32 UART_ReceiveNumber_BusyWait(void);

u8 UART_ReceiveString_CheckSum(u8* str);

void UART_ReceiveString_Asynch(u8*str);




#endif /* UART_SERVICES_H_ */