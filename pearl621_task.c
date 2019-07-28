#include "pearl621.h"
#include "pearl621_task.h"

//tasks
#define TSK_NO_DEFINE	-1

//タスクステータス(作成したとか動かせるとかそういう状態)
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
	int id;							//task id
	int pri;						//task priority
	E_STATE status;					//task status
	T_FUNKS funcs[TSKFUNK_MAX];		//task functionModule
	int funcExecNum;				//task function executing
	int funcCount;					//task function count
}T_TSKARY;

//内部タスク本体
T_TSKARY tasks[TSK_MAX];		//internalTask information
static int execute[TSK_MAX];	//executeTask que
static int taskCount = 0;		//nodef

/********************************************************/
/*					Public function						*/
/********************************************************/
int initTask(void)
{
	int i,j;
	//taskque reset
	for(i = 0; i < TSK_MAX; i++)
	{
		tasks[i].id = TSK_NO_DEFINE;
		tasks[i].pri = 0;
		tasks[i].status = E_NONE;
		for(j = 0; j < TSKFUNK_MAX; j++)
		{
			tasks[i].funcs[j].judge.jType = E_NOTYPE;
			tasks[i].funcs[j].judge.moveVal = (void *)(0);
			tasks[i].funcs[j].judge.moveRes = (void *)(0);
			tasks[i].funcs[j].po = (void *)(0);
		}
		execute[i] = TSK_NO_DEFINE;
	}
	taskCount = 0;
	return 0;
}

//タスク作成(タスク関数は作らない)
int createTask(int tskid,T_TSK pk_ctsk)
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

//関数セット
int setTaskFunc(int tskid,T_FUNKS func);
{
	int fCount = tasks[tskid].funcCount;
	
	//関数セット処理
	tasks[tskid].funcs[fCount].po = func.po;
	tasks[tskid].funcs[fCount].judge.jType = func.judge.jType;
	tasks[tskid].funcs[fCount].judge.moveVal = func.judge.moveVal;
	tasks[tskid].funcs[fCount].judge.moveRes = func.judge.moveRes;
	
	//関数増加
	tasks[tskid].funcCount++;
	
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
//select(pearl621)
int selectTask(void)
{
	int i,j;
	int iPri;
	//実行タスク列の状態
	for(iPri = 0; iPri < 16; iPri++)
	{
		for(i = 0; i < taskCount; i++)
		{
			//Priorityが合わなければ次のタスクを判定する
			if(tasks[i].pri != iPri)
			{
				continue;
			}
			//現在のタスク実行列に登録済みでもスルーする
			for(j = 0;(execute[j] < 0) && (execute[j] != i); j++);
			if(execute[j] == i)
			{
				continue;
			}
			//どちらでもないのなら実行条件と照らし合わせる
			if(tasks[i].funcExecNum != 0)
			{
				//0でないなら、判定式
				//最大値なら最初と判定する
				if(tasks[i].funcExecNum == tasks[i].funcCount)
				{
					tasks[i].funcExecNum = 1;
				}
				else
				{
					tasks[i].funcExecNum++;
				}
				if((*(tasks[i].funcs[funcExecNum].moveVal)) == (*(tasks[i].funcs[funcExecNum].moveRes)))
				{
					execute[j] = i;
				}
			}
			else
			{
				//待機列に追加
				execute[j] = i;
			}
			
		}
	}
}
//execute(pearl621)
int executeTask(void)
{
	int i;
	void (*pFunc)();
	if(execute[0] < 0)
	{
		return 0;	//[TODO]ここで待機する
	}
	//else
	pFunc = tasks[execute[0]].;	//get next function to execute
	
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