#include "UART_Services.h"
/*************************** UART Send Data **************************/
//Synchronous Function
void UART_SendString_BusyWait_Synch(u8* str)
{
	u8 i = 0 ;
	for(i = 0 ; str[i];i++)
	{
		UART_SendBusyWait(str[i]);
	}
}
//Synchronous Function
void UART_SendNumber_BusyWait(u32 num)
{
	//By Pointer
	u8 *p = &num ;
	UART_SendBusyWait(p[0]);
	UART_SendBusyWait(p[1]);
	UART_SendBusyWait(p[2]);
	UART_SendBusyWait(p[3]);
	/* 
	//By Bitwise Operator
	UART_SendBusyWait((u8)num);
	UART_SendBusyWait((u8)(num>>8));
	UART_SendBusyWait((u8)(num>>16));
	UART_SendBusyWait((u8)(num>>24));	
	*/
}

void UART_SendString_CheckSum(u8* str)
{
	u8 i, len=0  ;
	u16 sum = 0 ;
	for(len = 0; str[len];len++);
	UART_SendBusyWait(len);
	for(i=0;i<len;i++)
	{
		UART_SendBusyWait(str[i]);
		sum = sum +str[i];
	}
	UART_SendBusyWait((u8)sum);
	UART_SendBusyWait((u8)(sum>>8));
}

static volatile u8*TX_str_Asynch[20]; 
static void FUN_TX(void); 

void UART_SendString_Asynch(u8*str)
{
	static  u8 str_num =0 ,flag =0 ;
	TX_str_Asynch[str_num]= str ;
	str_num++ ;
	if(flag == 0)
	{   
		UART_SetCallBack(UART_TXCIE,FUN_TX);
		UART_INT_Enable(UART_TXCIE);
		UART_SendBusyWait(TX_str_Asynch[0][0]);	
		flag = 1;
	}
	if(str_num == 19)
 	{
		str_num = 0 ;
 	}
}
static void FUN_TX(void)
{
	static u8 i = 1 , str_indx = 0,flag =0;
	if(TX_str_Asynch[str_indx][i] != 0)
	{
		UART_SendNoBlock(TX_str_Asynch[str_indx][i]);
		i++ ;
		flag = 0 ;
	}
	else
	{
		i = 1;
		str_indx++ ;
		if(flag == 0)
		{
			UART_SendNoBlock(TX_str_Asynch[str_indx][0]);
			flag = 1 ;
		}
		
	}
}


/*
deh been al Ashynchro we been al synch
34an lazm tb2a gowa al while (1) bas fe nafs al wa2t m4 bt stuck fe al code
we hya 3arfa amta t4t8al we amta la2 3al4an al flag
*/
static volatile u8 flag = 0 ;
static void FUN_TX2(void) ;
/* bykon feha al 7agat aly m4 htetkrar we bkon 7tetha abl al while(1) */
void UART_BCM_Init(void)
{
	UART_SetCallBack(UART_TXCIE,FUN_TX2);
	UART_INT_Enable(UART_TXCIE);
}
void UART_BCM_Runnable(u8*str)
{
	static u8 i = 0 ;
	if(flag == 0)
	{
		if(str[i] != NULL)
		{
			UART_SendNoBlock(str[i]);
			i++;
			flag = 1 ;
		}
	}
}
static void FUN_TX2(void)
{
	flag = 0 ;
}


/*************************** UART Receive Data **************************/
//Synchronous Function
void UART_ReceiveString_BusyWait_Synch(u8* str)
{
	u8 i ;
	for(i = 0 ; ; i++)
	{
		str[i] = UART_ReceiveBusyWait();
		if ( str[i] == '#')
		break ;
	}
	str[i] = 0;
}
//
u32 UART_ReceiveNumber_BusyWait(void)
{
	//By Pointer
	u32 num ;
	u8 *p = num ;
	p[0]=UART_ReceiveBusyWait();
	p[1]=UART_ReceiveBusyWait();
	p[2]=UART_ReceiveBusyWait();
	p[3]=UART_ReceiveBusyWait();
	return num ;
	/*
	//By Bitwise Operator
	u32 num ;
	u8 b0 =UART_ReceiveBusyWait();
	u8 b1 =UART_ReceiveBusyWait();
	u8 b2 =UART_ReceiveBusyWait();
	u8 b3 =UART_ReceiveBusyWait();
	num = (u32)b0|(u32)b1<<8|(u32)b2<<16|(u32)b3<<24 ;
	return num ;
	*/
}

u8 UART_ReceiveString_CheckSum(u8* str)
{
	u8 i , len ,b0 ,b1 ;
	u16 sum_calc=0 , sum_rec = 0;
	len = UART_ReceiveBusyWait();
	for(i=0 ; i<len ; i++)
	{
		str[i]=UART_ReceiveBusyWait();
		sum_calc = sum_calc + str[i];
	}
	b0 = UART_ReceiveBusyWait();
	b1 = UART_ReceiveBusyWait();
	sum_rec = (u16)b0|(u16)b1<<8 ;
	str[i]=0 ;
	if(sum_rec == sum_calc)
	{
		return 1 ;
	}
	else
	{
		return 0 ;
	}
}

static u8*RX_str_Asynch;
static void FUN_RX(void);
void UART_ReceiveString_Asynch(u8*str)
{
	UART_SetCallBack(UART_RXCIE,FUN_RX);
	UART_INT_Enable(UART_RXCIE);
	RX_str_Asynch=str ;	
}

static void FUN_RX(void)
{
	static u8 i = 0;
	RX_str_Asynch[i]=UART_ReceiveNoBlock();
	i++;
}