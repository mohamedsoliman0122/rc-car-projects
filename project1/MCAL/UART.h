

#ifndef UART_H_
#define UART_H_
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "UART_Private.h"


/********************* Pin Config ******************/
//Select the Baud Rate Normal Speed
#define BAUD_RATE            RATE_9600
/***************************************************/
typedef enum{
	RATE_2400   = 207,
	RATE_4800   = 103,
	RATE_9600   = 51 ,
	RATE_14_4k  = 34 ,
	RATE_19_2k  = 25 ,
	RATE_28_8k  = 16 ,
	RATE_38_4k  = 12 ,
	RATE_57_6k  = 8  ,
	RATE_76_8k  = 6  ,
	RATE_115_2k = 3  ,
	RATE_230_4k = 1  ,
	RATE_250k   = 1  ,
	RATE_500k   = 0  ,
	RATE_1M     = 0
}BUAD_Rate_NormalSpeed_type;

typedef enum{
	UART_UDRIE=0,
	UART_TXCIE,
	UART_RXCIE
}UART_InterruptSource_type;

/***************************** Control Funtion ****************************/
void UART_Init(void);
/*************************** UART Send Data **************************/
void UART_SendNoBlock(u8 data);

void UART_SendBusyWait(u8 data);

u8 UART_SendPeriodicCheck(u8 data);
/*************************** UART Receive Data **************************/
u8 UART_ReceiveNoBlock(void);

u8 UART_ReceiveBusyWait(void);

u8 UART_ReceivePeriodicCheck(u8*pdata);



/**************************************** Call Back Functions ************************************/
void UART_SetCallBack(UART_InterruptSource_type Interrupt,void(*LocalPtr)(void));
/************************************** Enable/Disable Functions *********************************/
void UART_INT_Enable(UART_InterruptSource_type Interrupt);

void UART_INT_Disable(UART_InterruptSource_type Interrupt);

/*******************************************/
u8 compareString(char arr1[10], char arr2[10]);
void UART_Send_byte(u8 byte);
void UART_send_steing(char *ptr);
u8 UART_receive_byte(void);
void UART_recieve_string(char*ptr);

void UART_Transmit_SetCallBack(void(*Local_fPtr)(void));
void UART_Receive_SetCallBack(void(*Local_fPtr)(void));
void UART_ReceiveInterruptEnable(void);
u8 UART_Receive(void);






#endif /* UART_H_ */