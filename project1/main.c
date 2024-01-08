#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "LCD.h"
#include "DIO_interface.h"
#include "move.h"
#include "MOTOR_interface.h"
#include "KeyPad.h"
#include "ADC.h"
#include "Sensors.h"
#include "UART.h"
#include "UART_Services.h"
#include "UART_Private.h"
#include "Timers.h"
#include "Timers_Services.h"
#define F_CPU  8000000
#include <util/delay.h>

#define Repet 5
volatile long i=0;

#define LED_RED    PINA1
#define LED_GREEN  PINA2
#define LED_BLUEE  PINA3

#define MOTOR  PINB7   //MOTOR AND RELAY

               //MOTOR AND ULN2003A
#define M1  PINC0     
#define M2  PINC1
#define M3  PINC2
               //MOTOR AND L293D h bridge
#define IN1  PIND0
#define IN2  PIND1
#define IN3  PIND2
#define IN4	 PIND3	
               /******/
#define IN5  PINA0
#define IN6	 PINA1	

#include "RC_Project.h"

u8  rec;
void UART_Project(void)
{
	rec=UART_ReceiveNoBlock();
}
/**********************************************************/
void SERVO_setPosition(u8 angle)
{
	OCR1A=((angle*(u32)1000)/180)+999;
}
int main(void)
{  
	DIO_Init();
	LCD_Init();
	UART_Init();
	ADC_Init(VREF_AVCC,ADC_SCALER_64);	
    sei();
	UART_Receive_SetCallBack(UART_Project);
    UART_ReceiveInterruptEnable();
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	TIMER0_OC_Mode(OC0_NON_INVERTING);
	TIMER1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	TIMER1_OCRA1_Mode(OCRA_NON_INVERTING);
	
	ICR1=19999;
	LCD_WriteString("Rc Car");
	//OCR1A=1499;
	//OCR0=49;
    //u8 x=0;
	
///u16 num=0,num2=0;
	while(1)
	{
		/*num2++;
		if (num2==10)
		{
			num2=0;
		}
		num=ADC_Read(CH_0);
		OCR0=(num/4);*/
		
/********************************************************* Forward and Receive *************************************************************************/		
		if ( UART_Receive()=='F')
		{
			car_Forward();
			SERVO_setPosition(140);
			while((UART_Receive()=='F'));
			LCD_WriteString("car_Forward");
			LCD_SetCursor(1,0);
			
		}
		else if (UART_Receive()=='B')
		{
			car_Backward();
			SERVO_setPosition(140);
			while((UART_Receive()=='B'));
			LCD_WriteString("car_Backward");
			LCD_SetCursor(1,0);
		}
		
/****************************** Forward Right(I) /\ Forward Left(G) /\ ReceiveRight(J) /\ ReceiveLeft(H)********************************************/		
		else if (UART_Receive()=='I')
		{
			car_Forward();
			SERVO_setPosition(200);
			while((UART_Receive()=='I'));
			LCD_WriteString("Forward Right(I)");
			LCD_SetCursor(1,0);
		}
		
		else if (UART_Receive()=='G')
		{
			car_Forward();
			SERVO_setPosition(90);
			while((UART_Receive()=='G'));
			LCD_WriteString("Forward Left(G)");
			LCD_SetCursor(1,0);
		}
		
		else if (UART_Receive()=='J')
		{
			car_Backward();
			SERVO_setPosition(200);
			while((UART_Receive()=='J'));
			LCD_WriteString("Receive Right(J)");
			LCD_SetCursor(1,0);
		}
		
		else if (UART_Receive()=='H')
		{
			car_Backward();
			SERVO_setPosition(90);
			while((UART_Receive()=='H'));
			LCD_WriteString("Receive Left(H)");
			LCD_SetCursor(1,0);
		}
		
/******************************************************** Right and Left and stop *********************************************************************/

		else if (UART_Receive()=='R')
		{
			SERVO_setPosition(180);
			LCD_WriteString("Right(R)");
			LCD_SetCursor(1,0);
			
		}
		else if (UART_Receive()=='L')
		{
			SERVO_setPosition(90);
			LCD_WriteString("Left(L)");
			LCD_SetCursor(1,0);
		}
		else if (UART_Receive()=='S')
		{
			car_Stop();
			SERVO_setPosition(140);
			LCD_WriteString("Stop(S)");
			LCD_SetCursor(1,0);
		}
/********************************************************************* LED /\ BUZZER *********************************************************************************/		
		else if (UART_Receive()=='W')
		{
			DIO_Writepin(PINB0,HIGH);
			DIO_Writepin(PINB1,HIGH);
			DIO_Writepin(PINB2,HIGH);
			DIO_Writepin(PINB3,HIGH);
			LCD_WriteString("Front Lights(on)");
			LCD_SetCursor(1,0);
		}
		else if (UART_Receive()=='w')
		{
			DIO_Writepin(PINB0,LOW);
			DIO_Writepin(PINB1,LOW);
			DIO_Writepin(PINB2,LOW);
			DIO_Writepin(PINB3,LOW);
			LCD_WriteString("Front Lights(off)");
			LCD_SetCursor(1,0);
		}
		else if (UART_Receive()=='U')
		{
			DIO_Writepin(PINB4,HIGH);
			DIO_Writepin(PINB5,HIGH);
			DIO_Writepin(PINB6,HIGH);
			DIO_Writepin(PINB7,HIGH);
			LCD_WriteString("Back Lights(on)");
			LCD_SetCursor(1,0);
		}
		else if (UART_Receive()=='u')
		{
			DIO_Writepin(PINB4,LOW);
			DIO_Writepin(PINB5,LOW);
			DIO_Writepin(PINB6,LOW);
			DIO_Writepin(PINB7,LOW);
			LCD_WriteString("Back Lights(off)");
			LCD_SetCursor(1,0);
		}
		else if (UART_Receive()=='V')
		{
			DIO_Writepin(PINC5,HIGH);
			LCD_WriteString("BUZZER(on)");
			LCD_SetCursor(1,0);
		}
		else if (UART_Receive()=='v')
		{
			DIO_Writepin(PINC5,LOW);
			LCD_WriteString("BUZZER(off)");
			LCD_SetCursor(1,0);
		}
		
	}
}
	
	
	
	
	
	
	//DIO_Writepin(PINB1,LOW);
	//DIO_WritePort(PA,LOW);
	/*	
		SERVO_setPosition(181);
		_delay_ms(1000);
		SERVO_setPosition(0);
				_delay_ms(1000);

		/*x++;
		if (x==181)
		{
			x=0;
		}
		_delay_ms(1000);*/
		/*OCR1A=999;
		_delay_ms(1000);
		OCR1A=1499;
		_delay_ms(1000);
		OCR1A=1999;
		_delay_ms(1000);*/		
		
	//	DIO_Writepin(PINB1,HIGH);
	
	
	
	
	
	
	
	
	
	/*#include "RC_Project.h"
u8 rec;
void UART_Project(void)
{
	rec=UART_ReceiveNoBlock();
}
int main(void)
{   sei();
	
	DIO_Init();
	LCD_Init();
	LCD_WriteString("Hello");
    _delay_ms(300);
	LCD_Clear();
	UART_Init();
	
	UART_Receive_SetCallBack(UART_Project);
    UART_ReceiveInterruptEnable();
	
	char arr[10];
	while(1)
	{
		/*UART_recieve_string(arr);
		_delay_ms(1000);
		LCD_WriteString(arr);
		LCD_SetCursor(1,1);

		if(compareString(arr,"CARF"))
		{
			car_Forward();
			while(compareString(arr,"CARF"));
		}
		else if(compareString(arr,"startA"))
		{
			car_Backward();
			while(DIO_ReadPin(BT_B)== LOW);
		}
		else if(DIO_ReadPin(BT_RR)== LOW)
		{
			car_RotatRight();
			while(DIO_ReadPin(BT_RR)== LOW);
		}
		else if(DIO_ReadPin(BT_RL)== LOW)
		{
			car_RotatLeft();
			while(DIO_ReadPin(BT_RL)== LOW);
		}
		else
		{
			car_Stop();
		}*/
	/*}
}*/
	
	
	
	
	
	
	
	
	
	
	
	      
/*int main(void)
{
	u16 num;
	DIO_Init();
	LCD_Init();
	KEYPAD_int();
	ADC_Init(VREF_AVCC, ADC_SCALER_64);
   /* LCD_SetCursor(1,0);
	LCD_WriteString("AHMED");*/
	/*LCD_SetCursor(0,0);
    num=KEYPAD_GetKey();
	LCD_WriteNumber(num);
	while(1)
	{
		/*num=TEMP_Read();
		LCD_SetCursor(1,0);
		LCD_WriteNumber(num);
		LCD_WriteString("     ");*/
		//////////////////////////////////
		/*
		num=TEMP_Read();
		LCD_SetCursor(1,0);
		LCD_WriteNumber(num/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(num%10);
		LCD_WriteChar('c');
		LCD_WriteString("     ");
		
		/*if (num>500)
		{
			MOTOR_ccw()
		}*/
		
		
	/*}
	
}*/

/*int main(void)
{
	DIO_WritePort(PA,0XFF);
	/*DIO_Init();
	LCD_Init();
	KEYPAD_int();
	u8 k,i=0;
	u16 num=0,flag=0;
	//LCD_WriteString("keypad");
	LCD_SetCursor(0,0);
	LCD_SetCursor(0,10);
	LCD_WriteString("ahmed");
	while(1)
	{
		k=KEYPAD_GetKey();
		if (k!=NO_KEY)
		{
			
			if(k>='0'&&k<='9')
			{
				
				if(flag==0)
				{
					LCD_SetCursor(0,0);
					LCD_WriteString("      ");
					LCD_SetCursor(0,0);
					flag=1;
				}
				LCD_WriteChar(k);
				num=num*10+(k-'0');
			}
			if(k=='=')
			{
				LCD_SetCursor(1,0);
				LCD_WriteBinary(num);
				
				num=0;
				flag=0;
			}
			
			if (k=='c')
			{
				//LCD_Clear();
				READ_BIT(PORTC,PINC5);
			}
			
		}
	}*/
	
/*}*/

	   
	   
	
				
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			   

		
	 
		
		
		/*segment_dis_MLX(x);
		x++;
		_delay_ms(1000);*/
		
		/*x++;
		for (i=0;i<50;i++)
		{
			segment_dis_MLX(x);
		}
		_delay_ms(300);
		
		
		segment_dis(x);
		x++;
		if(x==100)
		{
			x=0;
		}
		_delay_ms(300);*/
	 