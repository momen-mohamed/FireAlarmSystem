
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Private.h"
#include "MOTOR_Cfg.h"


void MOTOR_Init(){
	
	MOTOR_type i;
	for (i = M1 ; i < TOTAL_MOTORS ; i++)
	{
		DIO_WritePin(MOTOR_PinsConifgArr[i].M_IN1,LOW);
		DIO_WritePin(MOTOR_PinsConifgArr[i].M_IN2,LOW);
	}
}
void MOTOR_Stop(MOTOR_type m){
	
	DIO_WritePin(MOTOR_PinsConifgArr[m].M_IN1,LOW);
	DIO_WritePin(MOTOR_PinsConifgArr[m].M_IN2,LOW);
	
}
void MOTOR_CW(MOTOR_type m){
	DIO_WritePin(MOTOR_PinsConifgArr[m].M_IN1,LOW);
	DIO_WritePin(MOTOR_PinsConifgArr[m].M_IN2,HIGH);
}
void MOTOR_CW2(MOTOR_type m){
	switch (m)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,HIGH);
		break;
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,HIGH);
		break;
		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,HIGH);
		break;
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,HIGH);
		break;
		default:
		break;
	}
}

void MOTOR_CCW(MOTOR_type m){
	DIO_WritePin(MOTOR_PinsConifgArr[m].M_IN1,HIGH);
	DIO_WritePin(MOTOR_PinsConifgArr[m].M_IN2,LOW);
}