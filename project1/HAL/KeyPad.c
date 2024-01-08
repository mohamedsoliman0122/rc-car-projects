

#define KEYPAD_C
#include "Utils.h"
#include "StdTypes.h"
#include "KeyPad.h"
#include "KeyPad_cfg.h"
#include "DIO_interface.h"







void KEYPAD_int(void)
{
	
	DIO_Writepin(FIRST_OUTPUT,HIGH);
	DIO_Writepin(FIRST_OUTPUT+1,HIGH);
	DIO_Writepin(FIRST_OUTPUT+2,HIGH);
	DIO_Writepin(FIRST_OUTPUT+3,HIGH);
}

s8 KEYPAD_GetKey(void)
{
	u8 r,c,Key=NO_KEY;
	for (r=0;r<ROWS;r++)
	{
		DIO_Writepin(FIRST_OUTPUT+r,LOW);
		for (c=0;c<CLOS;c++)
		{
			if (DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{ 
				Key=KeysArray[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
			}
		}
		DIO_Writepin(FIRST_OUTPUT+r,HIGH);  
	}
	return Key;
}




/*
int main(void)
{
	
	DIO_Init();
	LCD_Init();
	KEYPAD_int();
	u8 k,i=0;
	u16 num=0,flag=0;
	//LCD_WriteString("keypad");
	LCD_SetCursor(0,0);
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
				LCD_Clear();
			}
			
		}
	}
	
}
*/





/*************************/
/*int main(void)
{

DIO_Init();
LCD_Init();
KEYPAD_int();
u8 k,i=0;
u16 num=0,flag=0,sum=0,n1,n2;
//LCD_WriteString("keypad");
LCD_SetCursor(0,0);
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
LCD_Clear();
}

}
}

}*/