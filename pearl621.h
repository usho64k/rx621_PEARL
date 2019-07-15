#ifndef __PEARL621_H__
#define __PEARL621_H__


//User Public header
extern void pearl621_init(void);
extern void tskMainLoop(void);						//Main Loop
extern void osTmrInterrupt(void);

//Judgement type
typedef enum judgeType
{
	E_TIMER,		//Timer response
	E_IOFLAG,		//I/O edge response
	E_MESSAGE,		//Message response
	E_VALIABLE		//Valiable response
}E_JTYPE;

typedef struct t_tskExinf{
	E_JTYPE		jType;		//Task moveType
	int *		moveVal;	//Judge to move task
}T_JUDGE;

//Task
typedef struct t_ctsk{
	int			tskatr;		//Attribute (TBD)
	void *		exinf;		//External information(TBD)
	void		(*task)();	//Task function
	int			pri;		//Task Priority(0-15)
	int			stksize;	//Task Stack Size(TBD)
	
	E_JTYPE		jType;		//Task moveType
	int *		moveVal;	//Judge to move task
	int *		moveRes;	//Judge OK to move task
	
}T_CTSK;

//produced function for Task
extern int createTask(int tskid,T_CTSK pk_ctsk);	//pearl621Task.c
extern int deleteTask(int tskid);					//pearl621Task.c
extern int startTask(int tskid);					//pearl621Task.c
extern int sleepTask(int tskid,int millisecond);	//pearl621Task.c
extern int wakeupTask(int tskid);					//pearl621Task.c


#define TSK_MAX		8

#endif