#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_interface.h"
#include "Sensors_Cfg.h"


//return temp c * 10
u16 TEMP_Read(void){
	u16 temp;
	temp = (ADC_Read(LM35_CH) * (u32)100) / 1023;
	return temp;
}


u16 SMOKE_Read(void){
	u16 smoke;
	smoke = (ADC_Read(SMOKE_CH) * (u32)100) / 1023;
	return smoke;
}


u16 PRESSURE_Read(void){
	
	u16 pressure ;
	u16 adc = ADC_Read(MPX_4115);
	
	pressure =  (((((u32)1000 * adc) - 55000) + 460) / 921) + 150;
	
	return pressure;
	
}
