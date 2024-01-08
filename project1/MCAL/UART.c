#include "UART.h"

#include <util/delay.h>

static const u8* TX_Str[20];
static u8* RX_Str;
static u8 CounterFlag = 0;
static u8 FirstTimeFlag = 0;

static u8 Flag=1;


static void FUNC_TX(void);
static void FUNC_RX(void);
static void FUNC_TX_NO_CODE(void);


void(*UART_Transmit_pFunc) (void) = NULL_PTR;
void(*UART_Receive_pFunc)(void) = NULL_PTR;
/***************************** Control Funtion ****************************/
void UART_Init(void)
{
	//Baud Rate 9600 , freq  = 8 MHZ
	UBRRL = BAUD_RATE ; 
	//Normal Speed Mode
	CLR_BIT(UCSRA,U2X);
	
	//ana hena 3amel comment 34an howa al initial value bt3thom zai mana 3awz m4 m7tag a8yaro 
	//lakn law 7abet a8er lazm a3del feh
	/*
	//select Register UCSRC
	SET_BIT(UCSRC,URSEL);
	// Frame -> Parity  , Data Bits , Stop Bits
	//parity -> No Parity
	CLR_BIT(UCSRC,UPM0);
	CLR_BIT(UCSRC,UPM1);
	//Data bits -> 8 data bits
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	CLR_BIT(UCSRC,UCSZ2);
	//Stop Bits -> 1 Stop Bit
	CLR_BIT(UCSRC,USBS);
	*/
	
	//Enable TX , RX 
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}
/*************************** UART Send Data **************************/
void UART_SendNoBlock(u8 data)
{
	UDR = data ;
}
void UART_SendBusyWait(u8 data)
{
	//Busy Wait
	while(READ_BIT(UCSRA,UDRE) == 0);
	UDR = data ;
}

u8 UART_SendPeriodicCheck(u8 data)
{
	if(READ_BIT(UCSRA,UDRE))
	{
		UDR = data ;
		return 1 ;
	}
	return 0 ;
}
/*************************** UART Receive Data **************************/
u8 UART_ReceiveNoBlock(void)
{
	return UDR ;
}

u8 UART_ReceiveBusyWait(void)
{
	//Busy Wait
	while(READ_BIT(UCSRA,RXC) == 0);
	return UDR ;
}

u8 UART_ReceivePeriodicCheck(u8*pdata)
{
	if(READ_BIT(UCSRA,RXC))
	{
		*pdata = UDR ;
		return 1 ;
	}
	return 0 ;
}
/*************************** Pointer to Functions to be assigned to ISR **************************/
//we make it static ti not be edited by any one in another files
//concept of setter and getter
static void (*Fptr_UDRIE)(void) = NULL_PTR;
static void (*Fptr_TXCIE)(void) = NULL_PTR;
static void (*Fptr_RXCIE)(void) = NULL_PTR;
/**************************************** Call Back Functions ************************************/
void UART_SetCallBack(UART_InterruptSource_type Interrupt,void(*LocalPtr)(void))
{
	switch(Interrupt)
	{
		case UART_UDRIE:
		Fptr_UDRIE = LocalPtr;
		break;
		case UART_TXCIE:
		Fptr_TXCIE = LocalPtr;
		break;
		case UART_RXCIE:
		Fptr_RXCIE = LocalPtr;
		break;
	}
}
/************************************** Enable/Disable Functions *********************************/
void UART_INT_Enable(UART_InterruptSource_type Interrupt)
{
	switch(Interrupt)
	{
		case UART_UDRIE:
		SET_BIT(UCSRB,UDRIE);
		break;
		case UART_TXCIE:
		SET_BIT(UCSRB,TXCIE);
		break;
		case UART_RXCIE:
		SET_BIT(UCSRB,RXCIE);
		break;
	}
}

void UART_INT_Disable(UART_InterruptSource_type Interrupt)
{
	switch(Interrupt)
	{
		case UART_UDRIE:
		CLR_BIT(UCSRB,UDRIE);
		break;
		case UART_TXCIE:
		CLR_BIT(UCSRB,TXCIE);
		break;
		case UART_RXCIE:
		CLR_BIT(UCSRB,RXCIE);
		break;
	}
}
/********************************************** ISR **********************************************/
ISR(UART_UDRE_vect)
{
	if(Fptr_UDRIE != NULL_PTR)
	{
		Fptr_UDRIE();
	}
}

ISR(UART_TX_vect)
{
	if(Fptr_TXCIE != NULL_PTR)
	{
		Fptr_TXCIE();
	}
}

ISR(UART_RX_vect)
{
	if(Fptr_RXCIE != NULL_PTR)
	{
		Fptr_RXCIE();
	}
}

/***********************************************/
u8 compareString(char arr1[10], char arr2[10])
{
	int i=0;
	char flag=0;
	while((arr2[i]!='\0'))
	{
		if (arr1[i]==arr2[i])
		{
			flag=1;
		}
		else
		{
			flag=0;
		}
		i++;
	}
	return flag;
}

void UART_Send_byte(u8 byte)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR = byte ;
}

void UART_send_steing(char *ptr)
{
	int i=0;
	while(ptr[i]!='\0')
	{
		UART_Send_byte(ptr[i]);
		i++;
	}
	UART_Send_byte(ptr[i]);
}
u8 UART_receive_byte(void)
{
	while(READ_BIT(UCSRA,RXC) == 0);
	return UDR ;
}

void UART_recieve_string(char*ptr)
{
	int i=0;
	ptr[i]=UART_receive_byte();
	while(ptr[i] !='#')
	{
		i++;
		ptr[i]=UART_receive_byte();
	}
	ptr[i]='\0';
}
/****************************************************/
void UART_Receive_SetCallBack(void(*Local_fPtr)(void))
{
	if(Local_fPtr != NULL_PTR)
	{
		UART_Receive_pFunc = Local_fPtr;
	}
	else
	{
		/* Return Error */
	}
	
}

void UART_ReceiveInterruptEnable(void)
{
	SET_BIT(UCSRB,UCSRB_RXCIE);
}

u8 UART_Receive(void)
{
	/* Busy Wait till the UXC Flag is Set "There is unread data" */
	while(!READ_BIT(UCSRA,UCSRA_RXC));
	
	return UDR;
}
/************************************************************************/