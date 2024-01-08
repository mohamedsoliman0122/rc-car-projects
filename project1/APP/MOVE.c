#include "move.h"
#include "DIO_interface.h"

void MOVE_Init(void)
{
	
	/*do nothing*/
}

void MOVE_RUNNABOL(void)
{
	if(DIO_ReadPin(FORWARD_B)==LOW)
	{
		MOVE_Forward();
	}
	if(DIO_ReadPin(BACKWARD_B)==LOW)
	{
		MOVE_BACKWARD();
	}
	if(DIO_ReadPin(LEFT_B)==LOW)
	{
		MOVE_Left();
		while(DIO_ReadPin(LEFT_B)==LOW);
		MOVE_Stop();
		
	}
	if(DIO_ReadPin(RIGHT_B)==LOW)
	{
		MOVE_Right();
		while(DIO_ReadPin(RIGHT_B)==LOW);
		MOVE_Stop();
	}
	
}



void MOVE_Forward(void)
{
	MOTOR_CW(FRONT_LEFT);
	MOTOR_CW(FRONT_LEFT);
	MOTOR_CW(FRONT_LEFT);
	MOTOR_CW(FRONT_LEFT);
}

void MOVE_BACKWARD(void)
{
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
}
 
void MOVE_Left(void)
{
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
}

void MOVE_Right(void)
{
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
	MOTOR_CCW(FRONT_LEFT);
}

void MOVE_Stop(void)
{
	MOTOR_stop(FRONT_LEFT);
	MOTOR_stop(FRONT_LEFT);
	MOTOR_stop(FRONT_LEFT);
	MOTOR_stop(FRONT_LEFT);
}