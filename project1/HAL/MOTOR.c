
#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"


void MOTOR_stop(MOTOR_type motor)
{
	DIO_Writepin(MOTORPinArray[motor][IN1],LOW);
	DIO_Writepin(MOTORPinArray[motor][IN2],LOW);

}
void MOTOR_CW(MOTOR_type motor)
{
	DIO_Writepin(MOTORPinArray[motor][IN1],HIGH);
	DIO_Writepin(MOTORPinArray[motor][IN2],LOW);

}
void MOTOR_CCW(MOTOR_type motor)
{
	DIO_Writepin(MOTORPinArray[motor][IN1],LOW);
	DIO_Writepin(MOTORPinArray[motor][IN2],HIGH);

}


































           /*MOTOR_stop(M2);
		   _delay_ms(4000);
		   MOTOR_ccw(M2);
		   _delay_ms(4000);
		   MOTOR_cw(M2);
		   _delay_ms(4000);
		   /**************/
		   /*DIO_Writepin(IN5,HIGH);
		   DIO_Writepin(IN6,LOW);
		   _delay_ms(4000);
		   DIO_Writepin(IN5,LOW);
		   DIO_Writepin(IN6,HIGH);
		   _delay_ms(4000);
		   DIO_Writepin(IN5,LOW);
		   DIO_Writepin(IN6,LOW);
		   _delay_ms(4000);*/
		   
		   /******************/
		  /* DIO_Writepin(IN1,HIGH);
		   DIO_Writepin(IN2,LOW);
		   DIO_Writepin(IN3,LOW);
		   DIO_Writepin(IN4,HIGH);
		   _delay_ms(4000);
	       DIO_Writepin(IN1,LOW);
	       DIO_Writepin(IN2,HIGH);
	       DIO_Writepin(IN3,HIGH);
	       DIO_Writepin(IN4,LOW);
		   _delay_ms(4000);
		   DIO_Writepin(IN1,LOW);
		   DIO_Writepin(IN2,LOW);
		   DIO_Writepin(IN3,LOW);
		   DIO_Writepin(IN4,LOW);
		   _delay_ms(4000);*/
		  
		   /*****************
		   DIO_Writepin(M1,HIGH);
		   DIO_Writepin(M2,HIGH);
		   DIO_Writepin(M3,HIGH);
		   DIO_Writepin(MOTOR,HIGH);
		   _delay_ms(4000);
		   DIO_Writepin(M1,LOW);
		   DIO_Writepin(M2,LOW);
		   DIO_Writepin(M3,LOW);
		   DIO_Writepin(MOTOR,LOW);
		   _delay_ms(4000);*/