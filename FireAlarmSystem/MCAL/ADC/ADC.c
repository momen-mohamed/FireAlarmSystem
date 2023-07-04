/*
* ADC.c
*
* Created: 6/22/2023 4:53:24 PM
*  Author: momen mohamed
*/

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interface.h"
#define F_CPU 8000000
#include "util/delay.h"




void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler){
	
	/*PRESCALLER*/
	
	ADCSRA&=0xF8; //clear last 3 bits in ADCSRA register.
	scaler = scaler & 0x07; //clear all remaning bit in enum in order to make sure that only first three bits has value.
	ADCSRA |= scaler; // setting scaler value in first 3 bits.
	
	/*vref*/
	switch(vref){
		case VREF_AREF:
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	

	
	CLEAR_BIT(ADMUX,ADLAR);
	
	
	/*ENABLE ADC*/
	SET_BIT(ADCSRA,ADEN);
	
}

u16 ADC_Read(ADC_Channel_type ch){
	u16 value = (u16) 0;
	u8 adcl,adch;
	/*set channel mux*/
	ADMUX &= 0xE0; //clear last 5 bits in ADMUX register.
	ch&=0x07; //clear all remaning bits in enum to make sure that only first three bits has value.
	ADMUX |= ch;
	
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	
	/*wait ADC finish*/
	_delay_ms(2);
	
	adcl = ADCL;
	adch = ADCH;
	/*get read*/
	value = ((u16)adch << 8) | adcl;
	//value = value | ((u16)ADCH << 8);
	
	return value;
}


// return voltage in millivolt.
u16 ADC_VoltRead(ADC_Channel_type CH){
	u16 volt;
	u16 adc;
	adc = ADC_Read(CH);
	
	volt = (adc * (u32)5000)/1024;
	return volt;
}