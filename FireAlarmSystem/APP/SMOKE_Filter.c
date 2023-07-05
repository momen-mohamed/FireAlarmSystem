#include "StdTypes.h"
#include "Sensors_interface.h"


#define  NO_OF_SAMPLES 10

typedef enum{
	FILLING,
	FILLED
}FILTER_STATUS;

static u16 smokeFilterArray[NO_OF_SAMPLES];
static u16 filterdResult;
static u8 index;
static FILTER_STATUS status ;


void SMOKE_FilterInit(){
	status = FILLING;
}

void SMOKE_FilterRunnable(){
	u32 sum = 0;
	if (index < NO_OF_SAMPLES)
	{
		smokeFilterArray[index] = SMOKE_Read();
		index++;
	}
	else{
		status = FILLED;
		index = 0;
	}
	
	if (status == FILLING)
	{
		filterdResult = smokeFilterArray[index-1];
	}
	else{
		for (u8 i = 0 ; i < NO_OF_SAMPLES ; i++)
		{
			sum += smokeFilterArray[i];
		}
		filterdResult = sum / NO_OF_SAMPLES;
	}
}

u16 SMOKE_FilterGetter(void){
	return filterdResult;
}
