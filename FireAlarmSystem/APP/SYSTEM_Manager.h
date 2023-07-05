/*
 * SYSTEM_Manager.h
 *
 * Created: 7/4/2023 9:37:26 PM
 *  Author: mo2a
 */ 


#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

typedef enum {
	FINE,
	HEAT,
	FIRE,
	PASSWORD_ENTERY
}SYSTEM_Status_type;

void SYSTEM_ManagerInit(void);
void SYSTEM_ManagerRunnable(void);
SYSTEM_Status_type GetSystemStatus();

#endif /* SYSTEM_MANAGER_H_ */