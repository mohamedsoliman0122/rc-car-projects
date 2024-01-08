#include "LCD.h"
#include "DIO_interface.h"
#include "StdTypes.h"
#include "Utils.h"
#define F_CPU  8000000
#include <util/delay.h>

#if LCD_MODE==_8_BIT

static void WriteIns(u8 ins)
{
	DIO_Writepin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_Writepin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_Writepin(EN,HIGH);
	_delay_ms(1); 
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x38);// 2 line 8 bit mode , 8*7
	WriteIns(0x0c);// Cursor off 0x0e,0x0f
	WriteIns(0x01);// Clear
	_delay_ms(1);
	WriteIns(0x06);// increase DDRAM address no shift
	
}
           /**************  _4_BIT  ****************/
#elif LCD_MODE==_4_BIT

static void WriteIns(u8 ins)
{
	DIO_Writepin(RS,LOW);
	DIO_Writepin(D7,READ_BIT(ins,7));
	DIO_Writepin(D6,READ_BIT(ins,6));
	DIO_Writepin(D5,READ_BIT(ins,5));
	DIO_Writepin(D4,READ_BIT(ins,4));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	//DIO_Writepin(RS,LOW);
	DIO_Writepin(D7,READ_BIT(ins,3));
	DIO_Writepin(D6,READ_BIT(ins,2));
	DIO_Writepin(D5,READ_BIT(ins,1));
	DIO_Writepin(D4,READ_BIT(ins,0));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 ins)
{
	DIO_Writepin(RS,HIGH);
	DIO_Writepin(D7,READ_BIT(ins,7));
	DIO_Writepin(D6,READ_BIT(ins,6));
	DIO_Writepin(D5,READ_BIT(ins,5));
	DIO_Writepin(D4,READ_BIT(ins,4));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	//DIO_Writepin(RS,LOW);
	DIO_Writepin(D7,READ_BIT(ins,3));
	DIO_Writepin(D6,READ_BIT(ins,2));
	DIO_Writepin(D5,READ_BIT(ins,1));
	DIO_Writepin(D4,READ_BIT(ins,0));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);// 2 line 8 bit mode , 8*7
	WriteIns(0x0c);// Cursor off 0x0e,0x0f
	WriteIns(0x01);// Clear
	_delay_ms(1);
	WriteIns(0x06);// increase DDRAM address no shift
	
}
#endif

/*******************************************************/



void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_Clear(void)
{
	 WriteIns(0x01);//clear screen
	 _delay_ms(1);
}

void LCD_WriteNumber(s32 num)//-548484
{
	u8 rem,i=0,str[16];
	s8 j;
	if (num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if (num<0)
	{
		num=num*(-1);
		LCD_WriteChar('-');
	}
	
	while(num)
	{
		rem=num%10;
		rem=rem+'0';
		str[i]=rem;
		i++;
		num=num/10;
	}
	
	for (j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
}

void LCD_WriteNumber_4D(u16 num)//8542
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%10000)/100)+'0');
	LCD_WriteChar(((num%10000)/10)+'0');
	LCD_WriteChar(((num%10000)/1)+'0');
}

void LCD_WriteBinary(u8 num) //0011 1100
{
	s8 i;
	for (i=7;i>=0;i--)
	{
		LCD_WriteChar(((num>>i)&1)+'0');
	}

}

/*void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		if(READ_BIT(num,i))
		{
			LCD_WriteChar('1');
		}
		else
		{
			LCD_WriteChar('0');
		}
	}
}*/

void LCD_WriteHex(u8 num) //0x35
{
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN-10+'A');
	}
	if (LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar(LN-10+'A');
	}
}

void LCD_WriteString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}
void LCD_SetCursor(u8 line,u8 cell)
{
	if (line==0)
	{
		WriteIns(0x80|cell);
	}
	else if (line==1)
	{
		WriteIns(0x80|0x40|cell);
	}
}


/****************************************************/



void LCD_GoToWriteString(u8 line , u8 cell , u8 *str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}

void LCD_GoToWriteNumber(u8 line , u8 cell , s32 num)
{
	LCD_SetCursor(line,cell);
	LCD_WriteNumber(num);
}























/*void LCD_Init(void)
{
	_delay_ms(50);
	
	DIO_ReadPin(RS,LOW);
	DIO_Writepin(LCD_PORT,0X38);// 2 line 8 bit mode , 8*7
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	
	DIO_ReadPin(RS,LOW);
	DIO_Writepin(LCD_PORT,0X0C);// Cursor off 0x0e,0x0f
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	
	DIO_ReadPin(RS,LOW);
	DIO_Writepin(LCD_PORT,0X01);// Clear
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}*/

/************************** --------->  *************************/
/*int main(void)
	{
		
		DIO_Init();
		MOVE_Init();
		LCD_Init();
		LCD_WriteChar('A');
		LCD_WriteChar('h');
		LCD_WriteChar('m');
		LCD_WriteChar('e');
		LCD_WriteChar('d');
		LCD_WriteNumber(2002);
	  // LCD_WriteBinary(5);
	 // LCD_WriteHex(300);
	  //LCD_WriteNumber(-30);
	 // **********
	  /*LCD_WriteString("char  :");
	  LCD_SetCursor(1,0);
	  LCD_WriteString("ascii :");*/
	  //u8 a='A';
	  
	  /*u8 str[20]="----->";
	   while(1)
	   {
		   
		   LCD_SetCursor(0,i);
		   LCD_WriteString(str);
		   i++;
		   if(i==15)
		   {
			   i=0x40;
			   LCD_SetCursor(1,i);  
		   }
		   if(i==0x4f)
		   {
			   i=0;
			   LCD_SetCursor(0,i);
		   }
		   _delay_ms(60);
		   LCD_Clear();*/
		   
		  /*LCD_SetCursor(0,7);
		  LCD_WriteChar(a);
		  LCD_SetCursor(1,7);
		  LCD_WriteNumber(a);
		  _delay_ms(500);
		  a++;
		  
	   }*/
		  
		  /**************************=========>******************/
		  
		  
		  /**********************************************************/
		  /*int main(void)
		  {
			  
			  DIO_Init();
			  MOVE_Init();
			  LCD_Init();
			  s32 x=120;
			  while(1)
			  {
				  
				  LCD_SetCursor(1,0);
				  LCD_WriteNumber(x);
				  x--;
				  _delay_ms(200);
				  
			  }
			  
		  }*/
		  
		  /**********************************/
		 /* 
		  int main(void)
		  {
			  
			  DIO_Init();
			  MOVE_Init();
			  LCD_Init();
			  u8 str[100]="ahmed";
			  s16 x=120;
			  while(1)
			  {
				  LCD_SetCursor(1,0);
				  LCD_WriteNumber(x);
				  LCD_WriteString("  ");
				  x=x-2;
				  _delay_ms(300);
			  }
			  
		  }*/
/************************************************************************/
            /*******  ==================>  **********/
/*int main(void)
{
	
	DIO_Init();
	MOVE_Init();
	LCD_Init();
	u8 str[100]="ahmed";
	while(1)
	{
		u8 l=0;
		while(str[l])
		l++;
		for(u8 i=l;i>1;i--)
		{
			LCD_SetCursor(0,0);
			LCD_WriteString(str+i-1);
			_delay_ms(60);
			LCD_Clear();
		}
		for(u8 i=1;i<=15;i++)
		{
			LCD_SetCursor(0,i);
			LCD_WriteString(str);
			_delay_ms(60);
			LCD_Clear();
		}
		for(u8 j=l;j>1;j--)
		{
			LCD_SetCursor(1,0);
			LCD_WriteString(str+j-1);
			_delay_ms(60);
			LCD_Clear();
		}
		for(u8 i=0;i<=15;i++)
		{
			LCD_SetCursor(1,i);
			LCD_WriteString(str);
			_delay_ms(60);
			LCD_Clear();
		}
		
	}
}*/		  


/****************************************************************/



/***************************************************/
/*
int main(void)
{
	
	DIO_Init();
	LCD_Init();
	KEYPAD_int();
	u8 k,i=0;
	LCD_WriteString("keypad");
	LCD_SetCursor(1,i);
	while(1)
	{
		k=KEYPAD_GetKey();
		if (k!=NO_KEY)
		{
			
			//i++;
			LCD_WriteChar(k);
		}
		LCD_SetCursor(1,0);
		LCD_WriteBinary(23);
		LCD_SetCursor(1,12);
		LCD_WriteNumber(23);
	}
	
}*/