#include "pearl621.h"
#include "pearl621_task.h"

//tasks
#define TSK_NO_DEFINE	-1

typedef enum taskStatus
{
	E_NONE,
	E_CREATED,
	E_STARTED,
	E_JUMPABLE,
	E_SLEPT,
	E_RESERVED01,
	E_RESERVED02,
	E_RESERVED03,
	E_ENWUP,
	E_STATEMAX
}E_STATE;


//internal task data
typedef struct t_tsk
{
	int id;					//task id
	int *judge;				//task movejudge pointer
	int *judgeResult;		//task movejudgement Result
	E_JTYPE jType;			//task movejudgement Type
	
	E_STATE status;			//task status
	void (*taskfunc)();		//task function
}T_TSKARY;

//
T_TSKARY tasks[TSK_MAX];		//internalTask information
static int execute[TSK_MAX];	//executeTask que
static int taskCount = 0;		//nodef

int initTask(void)
{
	int i;
	//taskque reset
	for(i = 0; i < TSK_MAX; i++)
	{
		tasks[i].id = TSK_NO_DEFINE;
		tasks[i].taskfunc = (void *)(0);
		execute[i] = TSK_NO_DEFINE;
	}
	return 0;
}

int createTask(int tskid,T_CTSK pk_ctsk)
{
	//input to T_TSKARY tasks
	if(taskCount < TSK_MAX)
	{
		if((tskid < TSK_MAX) && (tskid >= 0))
		{
			if((tasks[tskid].status & E_CREATED) == 0x00)
			{ 
				tasks[tskid].id = tskid;
				tasks[tskid].status |= E_CREATED;
				tasks[tskid].taskfunc = pk_ctsk.task;
				taskCount++;
			}
			else
			{
				return -4;	//[tskid] is created other function.
			}
		}
		else
		{
			return -2;	//[tskid] is out of range
		}
	}
	else
	{
		return -1;	//taskCount over
	}
	return 0;
}

//delete(User)
int deleteTask(int tskid)
{
	return 0;	//undef
}

//start(User)
int startTask(int tskid)
{
	int i;
	for(i = 0; i < 8; i++)
	{
		if(execute[i] == tskid)
		{
			return;					//not allow to "double input"
		}
		if(execute[i] == TSK_NO_DEFINE)
		{
			execute[i] = tskid;		//input tskid to "no-define"
			return;			
		}
	}
	return 0;	//undef
}

//sleep(User)
int sleepTask(int tskid,int millisecond)
{
	tasks[tskid].status |= E_SLEPT;		//task to be slept.
	return 0;
}

//wakeup(User)
int wakeupTask(int tskid)
{
	tasks[tskid].status &= ~E_SLEPT;	//task to wake up.
	return 0;
}

//execute(pearl621)
int executeTask(void)
{
	int i;
	void (*pFunc)();
	if(execute[0] < 0)
	{
		return 0;	//[TODO]‚±‚±‚Å‘Ò‹@‚·‚é
	}
	//else
	pFunc = tasks[execute[0]].taskfunc;	//get next function to execute
	
	for(i = 0; i < TSK_MAX; i++)
	{
		if(i != TSK_MAX - 1)
		{
			execute[i] = execute[i + 1];	//function executable array is final shift.
		}
		else
		{
			execute[i] = TSK_NO_DEFINE;		//end of array is to be no-define.
		}
	}
	
	pFunc();		//execute
	
	return 1;
}