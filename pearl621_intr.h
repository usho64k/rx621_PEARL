#ifndef PEARL621_INTR_H
#define PEARL621_INTR_H


extern void tmr_OS_Initialize(void);				//timer for OS
extern void tmr_OS_Interrupt(void);					//timer for OS
extern int tmr_OS_GetTimer(void);					//timer for Task

//Timer interrupt en/disable
 void dis_intr_taskTimer(void);
 void ena_intr_taskTimer(void);
#endif