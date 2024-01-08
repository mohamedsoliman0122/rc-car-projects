#include "RC_Project.h"


void car_Forward(void)
{
	MOTOR_CW(F_R);
	MOTOR_CW(F_L);
	MOTOR_CW(B_R);
	MOTOR_CW(B_L);
}

void car_Backward(void)
{
	MOTOR_CCW(F_R);
	MOTOR_CCW(F_L);
	MOTOR_CCW(B_R);
	MOTOR_CCW(B_L);
}

void car_RotatLeft(void)
{
	MOTOR_CW(F_R) ;
	MOTOR_CW(B_R) ;
	MOTOR_CCW(F_L);
	MOTOR_CCW(B_L);
}

void car_RotatRight(void)
{
	MOTOR_CCW(F_R);
	MOTOR_CCW(B_R);
	MOTOR_CW(F_L) ;
	MOTOR_CW(B_L) ;
}
void car_Stop(void)
{
	MOTOR_stop(F_R);
	MOTOR_stop(F_L);
	MOTOR_stop(B_R);
	MOTOR_stop(B_L);
}
