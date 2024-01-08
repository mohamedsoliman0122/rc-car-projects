
#include "MOTOR_cfg.h"
#include "MOTOR_interface.h"
#include "MOTOR_private.h"
const DIO_Pin_type MOTORPinArray [NUMBER_OF_MOTORS][NUMBER_OF_PIN_PER_MOTORS]={

                           /*IN1       IN2*/
	/* MOTOR 1*/          { M1_IN1  ,  M1_IN2},
	/* MOTOR 2*/          { M2_IN1  ,  M2_IN2},
	/* MOTOR 3*/          { M3_IN1  ,  M3_IN2},
	/* MOTOR 4*/          { M4_IN1  ,  M4_IN2}
		
};