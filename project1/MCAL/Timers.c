#include "Timers.h"

/************************************************************************************************************/
/**************************************************** Timer 0 ***********************************************/
/************************************************************************************************************/
/************************************** Control Functions ****************************************/
void TIMER0_Init(Timer0Mode_type mode ,Timer0Scaler_type scaler)
{
	//Select Mode
	switch(mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	//prescaler (clock)
	TCCR0 = TCCR0  & 0xf8  ; //11111000
	scaler = scaler  & 0x07  ; //00000111
	TCCR0 = TCCR0  | scaler;
	
}

void TIMER0_OC_Mode(OC0Mode_type mode)
{
	switch(mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}

/*************************** Enable/Disable Functions **************************/
void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}

void TIMER0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}

void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}

void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}

/*************************** Read/Write Functions **************************/
u8 Timer0_OVF_Read(void)
{
	return TCNT0 ;
}

u8 Timer0_Read_OVF_Flag(void)
{
	return READ_BIT(TIFR,TOV0);
}

u8 Timer0_OC_Read(void)
{
	return OCR0 ;
}

u8 Timer0_Read_OC_Flag(void)
{
	return READ_BIT(TIFR,OCF0);
}

/*************************** Pointer to Functions to be assigned to ISR **************************/
//we make it static to not be edited by any one in another files
//concept of setter and getter
static void (*Fptr_OVF0_INT)(void) = NULL_PTR;
static void (*Fptr_OC0_INT)(void) = NULL_PTR;
/**************************************** Call Back Functions ************************************/
void TIMER0_SetCallBack(Timer0InterruptSource_type Interrupt,void(*Local_fptr)(void))
{
	switch(Interrupt)
	{
		case OVF0_INT:
		Fptr_OVF0_INT=Local_fptr;
		break;
		case OC0_INT:
		Fptr_OC0_INT=Local_fptr;
		break;
	}
}
/********************************************** ISR **********************************************/
ISR(TIMER0_OVF_vect)
{
	if(Fptr_OVF0_INT != NULL_PTR)
	{
		Fptr_OVF0_INT();
	}
}
ISR(TIMER0_OC_vect)
{
	if(Fptr_OC0_INT != NULL_PTR)
	{
		Fptr_OC0_INT();
	}
}
/************************************************************************************************************/
/**************************************************** Timer 1 ***********************************************/
/************************************************************************************************************/
/************************************** Control Functions ****************************************/
void TIMER1_Init(Timer1Mode_type mode ,Timer1Scaler_type scaler)
{
	//Select Mode
	switch(mode)
	{
		case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_PHASECORRECT_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_PHASECORRECT_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}
	//prescaler (clock)
	TCCR1B = TCCR1B  & 0xf8  ; //11111000
	scaler = scaler  & 0x07  ; //00000111
	TCCR1B = TCCR1B  | scaler;
	
}

void TIMER1_OCRA1_Mode(OC1A_Mode_type oc1a_mode)
{
	switch(oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}

void TIMER1_OCRB1_Mode(OC1B_Mode_type oc1b_mode)
{
	switch(oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}

void TIMER1_InputCaptureEdge(ICU_Edge_type edge)
{
	switch(edge)
	{
		case RISING:
		SET_BIT(TCCR1B,ICES1);
		break;
		case FALLING:
		CLR_BIT(TCCR1B,ICES1);
		break;
	}
}

/*************************** Enable/Disable Functions **************************/
void TIMER1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void TIMER1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}

void TIMER1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void TIMER1_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}

void TIMER1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void TIMER1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}

void TIMER1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void TIMER1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

/*************************** Read/Write Functions **************************/
u16 Timer1_OVF_Read(void)
{
	return TCNT1 ;
}
u8  Timer1_Read_OVF_Flag(void)
{
	return READ_BIT(TIFR,TOV1);
}

u16 Timer1_OCA_Read(void)
{
	return OCR1A ;
}
u8  Timer1_Read_OCA_Flag(void)
{
	return READ_BIT(TIFR,OCF1A);
}

u16 Timer1_OCB_Read(void)
{
	return OCR1B ;
}
u8  Timer1_Read_OCB_Flag(void)
{
	return READ_BIT(TIFR,OCF1B);
}

u16 Timer1_ICR1_Read(void)
{
	return ICR1 ;
}
u8  Timer1_Read_ICU_Flag(void)
{
	return READ_BIT(TIFR,ICF1);
}

/*************************** Pointer to Functions to be assigned to ISR **************************/
//we make it static to not be edited by any one in another files
//concept of setter and getter
static void (*Fptr_OVF1_INT)(void) = NULL_PTR;
static void (*Fptr_OCA_INT)(void) = NULL_PTR;
static void (*Fptr_OCB_INT)(void) = NULL_PTR;
static void (*Fptr_ICU1_INT)(void) = NULL_PTR;
/**************************************** Call Back Functions ************************************/
void TIMER1_SetCallBack(Timer1InterruptSource_type Interrupt,void(*Local_fptr)(void))
{
	switch(Interrupt)
	{
		case OVF1_INT:
		Fptr_OVF1_INT=Local_fptr;
		break;
		case OCA_INT:
		Fptr_OCA_INT=Local_fptr;
		break;
		case OCB_INT:
		Fptr_OCB_INT=Local_fptr;
		break;
		case ICU1_INT:
		Fptr_ICU1_INT=Local_fptr;
		break;
	}
}
/********************************************** ISR **********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Fptr_OVF1_INT != NULL_PTR)
	{
		Fptr_OVF1_INT();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Fptr_OCA_INT != NULL_PTR)
	{
		Fptr_OCA_INT();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Fptr_OCB_INT != NULL_PTR)
	{
		Fptr_OCB_INT();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Fptr_ICU1_INT != NULL_PTR)
	{
		Fptr_ICU1_INT();
	}
}
/************************************************************************************************************/
/**************************************************** Timer 2 ***********************************************/
/************************************************************************************************************/
/************************************** Control Functions ****************************************/
void TIMER2_Init(Timer2Mode_type mode ,Timer2Scaler_type scaler)
{
	//Select Mode
	switch(mode)
	{
		case TIMER2_NORMAL_MODE:
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		case TIMER2_PHASECORRECT_MODE:
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		case TIMER2_CTC_MODE:
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
		case TIMER2_FASTPWM_MODE:
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	}
	//prescaler (clock)
	TCCR2 = TCCR2  & 0xf8  ; //11111000
	scaler = scaler  & 0x07  ; //00000111
	TCCR2 = TCCR2  | scaler;
	
}

void TIMER2_OC_Mode(OC2Mode_type mode)
{
	switch(mode)
	{
		case OC2_DISCONNECTED:
		CLR_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		case OC2_TOGGLE:
		SET_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		case OC2_NON_INVERTING:
		CLR_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
		case OC2_INVERTING:
		SET_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	}
}

/*************************** Enable/Disable Functions **************************/
void TIMER2_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE2);
}

void TIMER2_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE2);
}

void TIMER2_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE2);
}

void TIMER2_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE2);
}

/*************************** Read/Write Functions **************************/
u8 Timer2_OVF_Read(void)
{
	return TCNT2 ;
}

u8 Timer2_Read_OVF_Flag(void)
{
	return READ_BIT(TIFR,TOV2);
}

u8 Timer2_OC_Read(void)
{
	return OCR2 ;
}

u8 Timer2_Read_OC_Flag(void)
{
	return READ_BIT(TIFR,OCF2);
}

/*************************** Pointer to Functions to be assigned to ISR **************************/
//we make it static to not be edited by any one in another files
//concept of setter and getter
static void (*Fptr_OVF2_INT)(void) = NULL_PTR;
static void (*Fptr_OC2_INT)(void) = NULL_PTR;
/**************************************** Call Back Functions ************************************/
void TIMER2_SetCallBack(Timer2InterruptSource_type Interrupt,void(*Local_fptr)(void))
{
	switch(Interrupt)
	{
		case OVF2_INT:
		Fptr_OVF2_INT=Local_fptr;
		break;
		case OC2_INT:
		Fptr_OC2_INT=Local_fptr;
		break;
	}
}
/********************************************** ISR **********************************************/
ISR(TIMER2_OVF_vect)
{
	if(Fptr_OVF2_INT != NULL_PTR)
	{
		Fptr_OVF2_INT();
	}
}
ISR(TIMER2_OC_vect)
{
	if(Fptr_OC2_INT != NULL_PTR)
	{
		Fptr_OC2_INT();
	}
}