#include "Timers_Services.h"


static volatile u16 t1,t2,t3,flag = 0 ;
/************************************************************** PWM ****************************************************************/

void PWM_Init(void)
{
	TIMER1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	TIMER1_OCRA1_Mode(OCRA_NON_INVERTING);
	TIMER1_OCRB1_Mode(OCRB_NON_INVERTING);
}

void PWM_Freq_KHZ(u16 freq)
{
	if(freq == 0);
	else
	{
		u16 Ttotal = 1000/freq ;
		if(Ttotal >= 1)
		{
			Timer1_ICR1_Set(Ttotal -1);
		}
		else Timer1_ICR1_Set(0);
	}
}
void PWM_Freq_HZ(u16 freq)
{
	if(freq == 0);
	else
	{
		u16 Ttotal=(u32)1000000/freq ;
		if(Ttotal >= 1)
		{
			Timer1_ICR1_Set(Ttotal -1);
		}
		else Timer1_ICR1_Set(0);
	}
}
void PWM_Duty(u16 duty)
{
	if(duty <= 100)
	{
		u16 Ton =((u32)duty*(ICR1+1))/100 ;
		if(Ton>1)
		{
			Timer1_OCA_Set(Ton-1);
		}
		else Timer1_OCA_Set(0);
	}
}

/*************************************************** Set Interrupt Time ************************************************************/
void Timer1_SetInterruptTime_us(u16 time ,void(*LocalFptr)(void))
{
	TIMER1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);
	//TIMER1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	Timer1_OCA_Set(time-1);
	TIMER1_SetCallBack(OCA_INT,LocalFptr);
	TIMER1_OCA_InterruptEnable();
}
void Timer1_SetInterruptTime_ms(u16 time ,void(*LocalFptr)(void))
{
	TIMER1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);
	//TIMER1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	Timer1_OCA_Set((time * 1000)-1);
	TIMER1_SetCallBack(OCA_INT,LocalFptr);
	TIMER1_OCA_InterruptEnable();
}
void Timer1_SetInterruptTime_s(u16 time ,void(*LocalFptr)(void))
{
	TIMER1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8);
	TIMER1_OCRA1_Mode(OCRA_DISCONNECTED);
	TIMER1_OCRB1_Mode(OCRB_DISCONNECTED);
	Timer1_OCA_Set(((u32)time * 1000000) - 1);
	TIMER1_SetCallBack(OCA_INT,LocalFptr);
	TIMER1_OCA_InterruptEnable();
}

/******************************************************* Measure PWM ***************************************************************/
void PWM_Measure(u32* Pfreq,u8* Pduty)
{
	u16 Ton , Toff ;
	Timer1_Set(0);// momkan y3mli mo4kla law ana bast5dm al timer dah fe 7aga tania 34an ana hena basfro 2wel m5o4
	TIMER1_SetCallBack(ICU1_INT,Func_ICU);
	TIMER1_InputCaptureEdge(RISING);
	TIMER1_ICU_InterruptEnable();
	flag = 0 ;
	while(flag < 3); // deh bt5linii ady3 wa2t bas 34an at2ked anii ana tal3 b2ryat m4 bgarbage
	Ton=t2-t1 ;
	Toff=t3-t2 ;
	
	*Pduty=((u32)Ton*100)/(Ton+Toff) ;
	*Pfreq=((u32)1000000)/((u32)Toff+Ton) ;
}
void PWM_Measure2(u32* Pfreq,u8* Pduty)
{
	u16 Ton , Toff;
	flag = 0 ;
	Timer1_Set(0);
	while(DIO_ReadPin(PIND6));
	while(!DIO_ReadPin(PIND6));
	Timer1_Set(0);
	while(DIO_ReadPin(PIND6));
	Ton= Timer1_OVF_Read();
	Timer1_Set(0);
	while(!DIO_ReadPin(PIND6));
	Toff=Timer1_OVF_Read();
	*Pduty=((u32)Ton*100)/(Ton+Toff) ;
	*Pfreq=((u32)1000000)/((u32)Toff+Ton) ;
}

void f1(void)
{
	if(flag == 0 )
	{
		Timer1_Set(0);
		TIMER1_SetCallBack(ICU1_INT,Func_ICU);
		TIMER1_InputCaptureEdge(RISING);
		TIMER1_ICU_InterruptEnable();
		
	}
}

u8 f2(u32* Pfreq,u8*Pduty)
{
	u16 Ton ,Toff ;
	if(flag == 3)
	{
		Ton=t2-t1 ;
		Toff=t3-t2;
		
		*Pduty=((u32)Ton*100)/(Ton+Toff) ;
		*Pfreq=((u32)1000000)/((u32)Toff+Ton) ;
		flag=0;
		return 1 ;
	}
	return 0;
}

static void Func_ICU(void)
{
	if(flag == 0)
	{
		t1=Timer1_ICR1_Read();
		TIMER1_InputCaptureEdge(FALLING);
		flag = 1 ;
	}
	else if(flag == 1)
	{
		t2 = Timer1_ICR1_Read();
		TIMER1_InputCaptureEdge(RISING);
		flag = 2 ;
	}
	else if(flag == 2)
	{
		t3 = Timer1_ICR1_Read();
		TIMER1_ICU_InterruptDisable();
		flag = 3 ;
	}
}


