


#ifndef LCD_H_
#define LCD_H_

#include "DIO_interface.h"
#define F_CPU  8000000
#include <util/delay.h>
#include "StdTypes.h"
#include "Utils.h"


#define  _8_BIT   1
#define  _4_BIT   2

/******************** pin config *************************/

/* choose _8_BIT  _4_BIT*/ 
/*#define  LCD_MODE   _4_BIT	
//#define  LCD_MODE   _8_BIT
#define   RS    PINB0
#define   EN    PINB1

#define   LCD_PORT    PA

#define D7 PINA7 	
#define D6 PINA6 
#define D5 PINA5 
#define D4 PINA4*/
/*************************************************/
/* choose _8_BIT  _4_BIT*/
#define  LCD_MODE   _4_BIT
//#define  LCD_MODE   _8_BIT
#define   RS    PINA1
#define   EN    PINA2

#define   LCD_PORT    PA

#define D7 PINA6
#define D6 PINA5
#define D5 PINA4
#define D4 PINA3
        
/*****************************************************/  

void LCD_Init(void);
void LCD_WriteNumber(s32 num);
void LCD_WriteNumber_4D(u16 num);
void LCD_WriteChar(u8 ch);
void LCD_WriteString(u8*str);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_SetCursor(u8 line,u8 cell);  //line 1,2 cell 1:16

void LCD_Clear(void);




#endif /* LCD_H_ */