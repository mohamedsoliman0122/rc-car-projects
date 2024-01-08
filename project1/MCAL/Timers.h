/*
 * Timers.h
 *
 * Created: 4/8/2023 2:37:10 PM
 *  Author: HP
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

/************************************************************************************************************/
/*************************************************** Timer 0 ************************************************/
typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer0Scaler_type	;

typedef enum{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
}Timer0Mode_type;

typedef enum{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING
}OC0Mode_type;

typedef enum{
	OVF0_INT=0,
	OC0_INT
}Timer0InterruptSource_type;

#define Timer0_Set(value)         TCNT0 = value
#define Timer0_OC_Set(value)      OCR0  = value

void TIMER0_Init(Timer0Mode_type mode ,Timer0Scaler_type scaler);
void TIMER0_OC_Mode(OC0Mode_type mode);

void TIMER0_OV_InterruptEnable(void);
void TIMER0_OV_InterruptDisable(void);

void TIMER0_OC_InterruptEnable(void);
void TIMER0_OC_InterruptDisable(void);

u8 Timer0_OVF_Read(void);
u8 Timer0_Read_OVF_Flag(void);

u8 Timer0_OC_Read(void);
u8 Timer0_Read_OC_Flag(void);

void TIMER0_SetCallBack(Timer0InterruptSource_type Interrupt,void(*Local_fptr)(void));
/************************************************************************************************************/
/*************************************************** Timer 1 ************************************************/
typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL1_FALLING,
	EXTERNAL1_RISING
}Timer1Scaler_type	;

typedef enum{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_PHASECORRECT_ICR_TOP_MODE,
	TIMER1_PHASECORRECT_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE
}Timer1Mode_type;

typedef enum{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING
}OC1A_Mode_type;

typedef enum{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING
}OC1B_Mode_type;

typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;

typedef enum{
	OVF1_INT=0,
	OCA_INT,
	OCB_INT,
	ICU1_INT
}Timer1InterruptSource_type;

#define Timer1_Set(value)          TCNT1  = value
#define Timer1_OCA_Set(value)      OCR1A  = value
#define Timer1_OCB_Set(value)      OCR1B  = value
#define Timer1_ICR1_Set(value)     ICR1   = value

void TIMER1_Init(Timer1Mode_type mode,Timer1Scaler_type scaler);
void TIMER1_InputCaptureEdge(ICU_Edge_type edge);
void TIMER1_OCRA1_Mode(OC1A_Mode_type oc1a_mode);
void TIMER1_OCRB1_Mode(OC1B_Mode_type oc1b_mode);

void TIMER1_ICU_InterruptEnable(void);
void TIMER1_ICU_InterruptDisable(void);

void TIMER1_OVF_InterruptEnable(void);
void TIMER1_OVF_InterruptDisable(void);

void TIMER1_OCA_InterruptEnable(void);
void TIMER1_OCA_InterruptDisable(void);

void TIMER1_OCB_InterruptEnable(void);
void TIMER1_OCB_InterruptDisable(void);

u16 Timer1_OVF_Read(void);
u8  Timer1_Read_OVF_Flag(void);

u16 Timer1_OCA_Read(void);
u8  Timer1_Read_OCA_Flag(void);

u16 Timer1_OCB_Read(void);
u8  Timer1_Read_OCB_Flag(void);

u16 Timer1_ICR1_Read(void);
u8  Timer1_Read_ICU_Flag(void);

void TIMER1_SetCallBack(Timer1InterruptSource_type Interrupt,void(*Local_fptr)(void));
/************************************************************************************************************/
/*************************************************** Timer 2 ************************************************/
typedef enum{
	TIMER2_STOP=0,
	TIMER2_SCALER_1,
	TIMER2_SCALER_8,
	TIMER2_SCALER_64,
	TIMER2_SCALER_256,
	TIMER2_SCALER_1024,
	EXTERNAL2_FALLING,
	EXTERNAL2_RISING
}Timer2Scaler_type	;

typedef enum{
	TIMER2_NORMAL_MODE=0,
	TIMER2_PHASECORRECT_MODE,
	TIMER2_CTC_MODE,
	TIMER2_FASTPWM_MODE
}Timer2Mode_type;

typedef enum{
	OC2_DISCONNECTED=0,
	OC2_TOGGLE,
	OC2_NON_INVERTING,
	OC2_INVERTING
}OC2Mode_type;

typedef enum{
	OVF2_INT=0,
	OC2_INT
}Timer2InterruptSource_type;

#define Timer2_Set(value)         TCNT2 = value
#define Timer2_OC_Set(value)      OCR2  = value

void TIMER2_Init(Timer2Mode_type mode ,Timer2Scaler_type scaler);
void TIMER2_OC_Mode(OC2Mode_type mode);

void TIMER2_OV_InterruptEnable(void);
void TIMER2_OV_InterruptDisable(void);

void TIMER2_OC_InterruptEnable(void);
void TIMER2_OC_InterruptDisable(void);

u8 Timer2_OVF_Read(void);
u8 Timer2_Read_OVF_Flag(void);

u8 Timer2_OC_Read(void);
u8 Timer2_Read_OC_Flag(void);

void TIMER2_SetCallBack(Timer2InterruptSource_type Interrupt,void(*Local_fptr)(void));




#endif /* TIMERS_H_ */