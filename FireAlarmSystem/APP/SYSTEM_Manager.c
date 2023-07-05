#include "StdTypes.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"
#include "SMOKE_Filter.h"
#include "TEMP_Filter.h"
#include "DIO_Interface.h"
#include "Utils.h"
#include "KeyPad_Interface.h"
#include "SYSTEM_Manager.h"

#define SYSTEM_MANAGER 1
#include "SYSTEM_Manager_Private.h"
#include "SYSTEM_Cfg.h"
#define F_CPU 8000000
#include <util/delay.h>


#define DELAY 2000

static SYSTEM_Status_type currentStatus = FINE;
static u8 initialEntery = 1;



//Init function of the system
void SYSTEM_ManagerInit(void){
	
	
}


//this function contains the runnable System Manager Code.
void SYSTEM_ManagerRunnable(void){
	
	if (currentStatus == FINE)
	{
		fineStateRunnable();
		
	}
	else if (currentStatus == HEAT)
	{
		heatStateRunnable();
	}
	else if (currentStatus == FIRE)
	{
		fireStateRunnable();
	}else
	{
		passwordEnteryStateRunnable();
	}
	
}


//this function manage the system in FINE state
static void fineStateRunnable(){
	u16 currentTemp;
	if (initialEntery)
	{
		LCD_Clear();
		resetLeds();
		DIO_WritePin(PINC1,HIGH);
		LCD_GoTo(0,6);
		LCD_WriteString("FINE");
		initialEntery = 0;
	}
	currentTemp = TEMP_FilterGetter();
	if (currentTemp > MAX_HYST_TEMP)
	{
		currentStatus = HEAT;
		initialEntery = 1;
	}
	LCD_GoTo(1,0);
	LCD_WriteString("TEMP:");
	LCD_WriteNumber(currentTemp);
	LCD_WriteString("C     ");
	
}

//this function manage the system in HEAT state
static void heatStateRunnable(){
	u16 smokePerc;
	u16 temp ;
	if (initialEntery)
	{
		LCD_Clear();
		resetLeds();
		DIO_WritePin(PINC2,HIGH);
		LCD_GoTo(0,6);
		LCD_WriteString("HEAT");
		initialEntery = 0;
	}
	smokePerc = SMOKE_FilterGetter();
	temp = TEMP_FilterGetter();
	
	//check smoke and temp to change state either to FIRE or FINE
	if (smokePerc > MAX_HYST_TEMP)
	{
		currentStatus = FIRE;
		initialEntery = 1;
	}
	else if(smokePerc < MAX_HYST_TEMP && temp < MIN_HYST_TEMP){
		currentStatus = FINE;
		initialEntery = 1;
	}
	LCD_GoTo(1,0);
	LCD_WriteString("SMOKE:");
	LCD_WriteNumber(smokePerc);
	LCD_WriteString("% ");
	LCD_WriteString("T:");
	LCD_WriteNumber(temp);
	LCD_WriteString("C  ");
}

//this function manage the system in FIRE state
static void fireStateRunnable(){
	u8 keyPressed ;
	if (initialEntery)
	{
		LCD_Clear();
		resetLeds();
		DIO_WritePin(PINC0,HIGH);
		//DIO_WritePin(PINC5,HIGH);
		LCD_GoTo(0,6);
		LCD_WriteString("FIRE");
		LCD_GoTo(1,0);
		LCD_WriteString("PRESS 1 TO RESET SYSTEM");
		initialEntery = 0;
	}
	
	keyPressed = KEYPAD_GetKey();
	if (keyPressed == '1')
	{
		LCD_Clear();
		currentStatus = PASSWORD_ENTERY;
		initialEntery = 1;
	}
}


//this function manage the entry of password 
static void passwordEnteryStateRunnable(){
	static c8 password[PASS_LEN+1];
	static u8 index;
	u8 keyPressed ;

	if (initialEntery)
	{
		LCD_Clear();
		LCD_GoTo(0,1);
		LCD_WriteString("ENTER PASSWORD");
		LCD_GoTo(1,5);
		initialEntery = 0;
	}
	
	keyPressed = KEYPAD_GetKey();

	if (keyPressed !='T')
	{
		if (keyPressed >= '0' && keyPressed<='9')
		{
			if (index < PASS_LEN)
			{
				password[index] = keyPressed;
				LCD_WriteChar(keyPressed);
				index++;
			}
		}
		
		if (keyPressed == '=')
		{
			password[index] = '\0';
			index = 0;
			if (string_compare(password,PASSWORD) == TRUE)
			{
				LCD_Clear();
				LCD_GoTo(0,3);
				LCD_WriteString("RESETTING");
				_delay_ms(DELAY);
				resetSystem();
			}
			else{
				LCD_Clear();
				LCD_GoTo(0,1);
				LCD_WriteString("WRONG PASSWORD");
				_delay_ms(DELAY);
				initialEntery = 1;
			}
		}
	}
}


//this function reset all LEDs to OFF state
static void resetLeds(){
	DIO_WritePin(PINC0,LOW);
	DIO_WritePin(PINC1,LOW);
	DIO_WritePin(PINC2,LOW);
}

//this function reset the system to FINE state
static void resetSystem(){
	DIO_WritePin(PINC5,LOW);
	currentStatus = FINE;
	initialEntery = 1;
}


//return current status of the system (STATUS GETTER)
SYSTEM_Status_type GetSystemStatus(){
	return currentStatus;
}