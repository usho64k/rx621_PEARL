#ifndef __PEARL621_INTR_H__
#define __PEARL621_INTR_H__


extern void tmr_OS_Initialize(void);				//timer for OS
extern void tmr_OS_Interrupt(void);					//timer for OS
extern int tmr_OS_GetTimer(void);					//timer for Task

//Timer interrupt en/disable
 void dis_intr_taskTimer(void);
 void ena_intr_taskTimer(void);
#endif