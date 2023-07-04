/*
* MOTOR_Interface.h
*
* Created: 6/10/2023 9:12:46 PM
*  Author: mo2a
*/


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum{
	M1,
	M2,
	M3,
	M4,
	TOTAL_MOTORS
}MOTOR_type;

typedef enum{
	FW,
	BW
}MOTOR_Direction;

typedef enum{
	STOP,
	MOVE
}MOTOR_Status;

void MOTOR_Init(void);
void MOTOR_Stop(MOTOR_type m);
void MOTOR_CW(MOTOR_type m);
void MOTOR_CCW(MOTOR_type m);



#endif /* MOTOR_INTERFACE_H_ */