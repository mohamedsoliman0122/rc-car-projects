#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "ADC.h"

#define F_CPU  8000000
#include <util/delay.h>

u16 Volt_ref;
void ADC_Init(ADC_VREF_type vref,ADC_Prescaler_type scaler)
{
	/* clock */
    scaler=scaler&0x07;  //00000111  
	ADCSRA=ADCSRA&0xf8;  //11111000
	ADCSRA=ADCSRA|scaler;

	/* volt ref */
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		Volt_ref=AREF;
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		Volt_ref=5000;
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		Volt_ref=2560;
		break;
		
	}
	CLR_BIT(ADMUX,ADLAR); //Register 215
	/* REG->ADCSRA->ADC ENABL-E (7) */
	
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_type ch)
{
	
	u16 adc;
	u8 adcl,adch;
	/* select channel */
	ADMUX=ADMUX&0xE0;  //11100000
	ADMUX=ADMUX|ch;
	/* start conversion */
	SET_BIT(ADCSRA,ADSC);
	/* w8 until finish */
	/*_delay_ms(1);*/
	while(READ_BIT(ADCSRA,ADSC));
	/*adcl=ADCL;
	  adch=ADCH;
	adc=adch<<8 |adcl;*/
	//adc=ADC;
	return ADC;
}

u16 ADC_ReadVolt(ADC_Channel_type ch)
{
	u16 adc=ADC_Read(ch);
	
	u16 volt =(adc*(u32)Volt_ref)/1024;
	return volt;
}





/*
         clock	
	case ADC_SCALER_1:
	CLR_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
	break;
	case ADC_SCALER_4:
	SET_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
	break;
	......*/


/****************50*************************/
/*int main(void)
{
	u16 num;
	DIO_Init();
	LCD_Init();
	//KEYPAD_int();
	ADC_Init(VREF_AVCC, ADC_SCALER_64);

	while(1)
	{
		READ_BIT(PORTA,PINA3);
		/*num=ADC_Read(CH_0);
		LCD_SetCursor(0,0);
		LCD_WriteNumber(num);
		num=ADC_Read(CH_3);
		LCD_SetCursor(1,0);
		LCD_WriteNumber(num);
		LCD_WriteString("     ");*/
		/*ponshomiter*/
		/*num=ADC_ReadVolt(CH_3);
		LCD_SetCursor(1,0);
		LCD_WriteNumber(num);
		LCD_WriteString("     ");*/
		/* LDR */
		/*num=ADC_ReadVolt(CH_3);
		LCD_SetCursor(1,0);
		LCD_WriteNumber(num);
		LCD_WriteString("     ");
	}
	
}*/