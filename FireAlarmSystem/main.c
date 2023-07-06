#include "StdTypes.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"
#include "Sensors_interface.h"
#include "KeyPad_Interface.h"
#include "TEMP_Filter.h"
#include "SMOKE_Filter.h"
#include "SYSTEM_Manager.h"
#include "MOTOR_Interface.h"
#include "MOTION.h"
#define F_CPU 8000000
#include <util/delay.h>

int main(void)
{
	/*initialization*/
	DIO_init();
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	LCD_Init();
	KEYPAD_Init();
	TEMP_FilterInit();
	SMOKE_FilterInit();
	SYSTEM_ManagerInit();
	MOTOR_Init();
	MOTION_Init();
	
	
	while (1)
	{
		TEMP_FilterRunnable();
		if (GetSystemStatus() != FINE)
		{
			SMOKE_FilterRunnable();
		}
		SYSTEM_ManagerRunnable();
		MOTION_Runnable();
	}
}

