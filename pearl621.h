#ifndef __PEARL621_H__
#define __PEARL621_H__

//Task
typedef struct t_ctsk{
	int			tskatr;		//Attribute (TBD)
	void *		exinf;		//External information(TBD)
	(void *)	task;		//Task function
	int			pri;		//Task Priority(0-15)
	int			stksize;	//Task Stack Size(TBD)
}T_CTSK;

extern void tmr_OS_Initialize(void);				//timer for OS
extern void tmr_OS_Interrupt(void);					//timer for OS


extern int createTask(int tskid,T_CTSK pk_ctsk);	//
extern int deleteTask(int tskid);
extern int startTask(int tskid);
extern int sleepTask(int tskid,int millisecond);
extern int wakeupTask(int tskid);

#endif