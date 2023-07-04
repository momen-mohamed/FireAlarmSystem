/*
* MOTOR_Cfg.c
*
* Created: 6/12/2023 12:18:33 AM
*  Author: mo2a
*/

#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Private.h"

/*******************MOTORS PIN CONFIG *******************/

const MOTOR_Config_Type MOTOR_PinsConifgArr[TOTAL_MOTORS] = {
	{
		.M_IN1 = PINA0,		//M1_INIT1
		.M_IN2 = PINA1		//M2_INIT2
	},
	{
		.M_IN1 = PINA2,		//M2_INIT1
		.M_IN2 = PINA3,		//M2_INIT2
	},
	{
		.M_IN1 = PINA3,		//M3_INIT1
		.M_IN2 = PINA4,		//M3_INIT2
	},
	{
		.M_IN1 = PINA5,		//M4_INIT1
		.M_IN2 = PINA6,		//M4_INIT2
	},
};