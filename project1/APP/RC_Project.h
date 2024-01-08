/*
 * RC_Project.h
 *
 * Created: 3/21/2023 10:19:25 PM
 *  Author: HP
 */ 


#ifndef RC_PROJECT_H_
#define RC_PROJECT_H_

#include "DIO_interface.h"
#include "MOTOR_interface.h"


#define  F_R    M1
#define  F_L    M2
#define  B_R    M3
#define  B_L    M4

#define  BT_F   PIND3
#define  BT_B   PIND4
#define  BT_RR  PIND5
#define  BT_RL  PIND6
#define  BT_ST  PIND7



void car_Forward(void);

void car_Backward(void);

void car_RotatLeft(void);

void car_RotatRight(void);

void car_Stop(void);





#endif /* RC_PROJECT_H_ */