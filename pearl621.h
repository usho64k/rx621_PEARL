#ifndef __PEARL621_H__
#define __PEARL621_H__


//User Public header
extern void pearl621_init(void);
extern void tskMainLoop(void);						//Main Loop
extern void osTmrInterrupt(void);


//Task
typedef struct t_ctsk{
	int			tskatr;		//Attribute (TBD)
	void *		exinf;		//External information(TBD)
	void		(*task)();	//Task function
	int			pri;		//Task Priority(0-15)
	int			stksize;	//Task Stack Size(TBD)
}T_CTSK;

//produced function for Task
extern int createTask(int tskid,T_CTSK pk_ctsk);	//pearl621Task.c
extern int deleteTask(int tskid);					//pearl621Task.c
extern int startTask(int tskid);					//pearl621Task.c
extern int sleepTask(int tskid,int millisecond);	//pearl621Task.c
extern int wakeupTask(int tskid);					//pearl621Task.c


#define TSK_MAX		8

#endif