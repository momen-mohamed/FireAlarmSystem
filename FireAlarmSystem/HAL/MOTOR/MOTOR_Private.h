/*
* MOTOR_Private.h
*
* Created: 6/12/2023 12:18:04 AM
*  Author: momen mohamed
*/


#ifndef MOTOR_PRIVATE_H_
#define MOTOR_PRIVATE_H_

typedef struct{
	DIO_Pin_type M_IN1;
	DIO_Pin_type M_IN2;
}MOTOR_Config_Type;

extern const MOTOR_Config_Type MOTOR_PinsConifgArr[TOTAL_MOTORS];


#endif /* MOTOR_PRIVATE_H_ */