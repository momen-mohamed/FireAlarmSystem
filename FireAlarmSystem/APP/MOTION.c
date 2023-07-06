#include "StdTypes.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Cfg.h"
#include "SYSTEM_Manager.h"


void MOTION_Init(void){
	
}


void MOTION_Runnable(void){
	if (GetSystemStatus() == FIRE)
	{
		MOTOR_CW(M1);
	}else{
		MOTOR_Stop(M1);
	}
}