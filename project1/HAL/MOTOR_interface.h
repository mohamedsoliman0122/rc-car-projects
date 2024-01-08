

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#include "DIO_interface.h"
#include "StdTypes.h"


 typedef enum{
	 M1,
	 M2,
	 M3,
	 M4
	 }MOTOR_type;

void MOTOR_stop(MOTOR_type motor);
void MOTOR_cw(MOTOR_type motor);
void MOTOR_ccw(MOTOR_type motor);
/* speed from 0to 100 % */
void MOTOR_Speed(MOTOR_type motor,u8 speed);

#endif /* MOTOR_INTERFACE_H_ */