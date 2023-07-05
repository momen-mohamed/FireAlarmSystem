#include "StdTypes.h"
#include "Sensors_interface.h"
#define F_CPU 8000000
#include "util/delay.h"


#define  NO_OF_SAMPLES 10

typedef enum{
	FILLING,
	FILLED
}FILTER_STATUS;

static u16 tempFilterArray[NO_OF_SAMPLES];
static u16 filterdResult;
static u8 index;
static FILTER_STATUS status ;



void TEMP_FilterInit(){
	status = FILLING;
}

void TEMP_FilterRunnable(){
	u8 i;
	u32 sum = 0;
	if (index < NO_OF_SAMPLES)
	{
		tempFilterArray[index] = TEMP_Read();
		index++;
	}
	else{
		status = FILLED;
		index = 0;
	}
	
	if (status == FILLING)
	{
		filterdResult = tempFilterArray[index-1];
	}
	else{
		for (i = 0 ; i < NO_OF_SAMPLES ; i++)
		{
			sum += tempFilterArray[i];
		}
		filterdResult = sum / NO_OF_SAMPLES;
	}
}

u16 TEMP_FilterGetter(void){
	return filterdResult;
}
