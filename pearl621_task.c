
#ifdef TESTCODE
#include "testcode/main.h"
#endif

#include "pearl621_task_usr.h"
#include "pearl621_task.h"
#include "pearl621_intr.h"

//#include "testcode/main.h"

#ifdef MAIN_H
#include <stdio.h>
#endif

//tasks
#define TSK_NO_DEFINE	-1

//タスク状態について
typedef enum taskStatus
{
	E_NONE,
	E_CREATED,				//Create完了
	E_STARTED,				//Start完了
	E_JUMPABLE,				//Create かつ Start
	E_SLEPT,				//タスク動作フラグ未達成
	E_RESERVED05,
	E_RESERVED06,
	E_RESERVED07,
	E_ENWUP,				//タスク動作フラグ既達成
	E_RESERVED09,
	E_RESERVED0A,
	E_EXECUTABLE,			//動作可能(ENWUP & SLEPT)
	E_RESERVED0C,
	E_RESERVED0D,
	E_RESERVED0E,
	E_RESERVED0F,
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

//static valiables definition
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
			tasks[i].funcs[j].judge = (void *)(0);
			tasks[i].funcs[j].po = (void *)(0);
		}
		tasks[i].funcExecNum = 0;
		tasks[i].funcCount = 0;
		execute[i] = TSK_NO_DEFINE;
	}
	taskCount = 0;
	return 0;
}

//タスク作成(関数列の親玉を作る)
int createTask(int tskid,const T_TSK *pk_ctsk)
{
	//input to T_TSKARY tasks
	if(taskCount >= TSK_MAX)
	{
		return -1;	//タスク数オーバー
	}
	if((tskid >= TSK_MAX) || (tskid < 0))
	{
		return -2;	//tskid不正
	}
	if((tasks[tskid].status & E_CREATED) != 0x00)
	{
		return -4;	//tskidが既に存在している
	}
	
	//タスクIDを登録する
	tasks[tskid].id = tskid;
	tasks[tskid].status |= E_CREATED;
	taskCount++;
	return 0;
}

//タスク関数登録(関数列の登録)
int setTaskFunc(int tskid,const T_FUNKS *func)
{
	int fCount = tasks[tskid].funcCount;
	
	//指定されたタスクIDの関数に一つずつ追加
	tasks[tskid].funcs[fCount].po = func->po;
	tasks[tskid].funcs[fCount].judge = func->judge;
	
	//関数列の数を更新
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
	
	if((tasks[tskid].status & E_CREATED) == 0x00)
	{
		return -1;		//Createされてない
	}
	tasks[tskid].status |= E_STARTED;
	tasks[tskid].status |= E_ENWUP;
	return 0;
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
	tasks[tskid].status |= E_ENWUP;
	return 0;
}
//select(pearl621)
int selectTask(void)
{
	int i,j;
	//起動状態のタスクを、優先度を考慮してタスク実行列に配置する
	for(i = 0; i < taskCount; i++)
	{
		if(tasks[i].status == E_EXECUTABLE)
		{
			//起動状態のとき
			//Executable条件ならExecute列にタスクIDがなければ追加
			for(j = 0; j < taskCount; j++)
			{
				if(execute[j] == TSK_NO_DEFINE)
				{
					//tsk no define (=blanc) -> 100% this place.
					execute[j] = i;
					tasks[i].status &= ~E_ENWUP;
					break;
				}
				
				//自分より優先度が低い、Execute列にあるタスクIDをチェックする。
				if(tasks[execute[j]].pri < tasks[i].pri)
				{
					int k;
					//後ろから探索、後ろに１つずつズラす
					for(k = TSK_MAX - 1; k > j; k--)
					{
						execute[k] = execute[k - 1];
					}
					//優先タスクを入れる
					execute[j] = i;
					tasks[i].status &= ~E_ENWUP;
					break;
				}
			}
		}
	}
	if(execute[0] != TSK_NO_DEFINE)
	{
		return 0;
	}
	return -32;
}
//execute(pearl621)
int executeTask(void)
{
	int i;
	int exeFunc = tasks[execute[0]].funcExecNum;
	void (*pFunc)();
	
	if(execute[0] < 0)
	{
		//実行列が負の値(タスクIDではない)
		return -16;	//[TODO]
	}
	//else
	pFunc = tasks[execute[0]].funcs[exeFunc].po;	//get next function to execute
	
	//タスク関数実行
	pFunc();		//execute
	
	//関数実行後は実行した関数の次の関数について吟味するように参照先を変更する
	if(exeFunc >= tasks[execute[0]].funcCount - 1)
	{
		tasks[execute[0]].funcExecNum = 1;
	}
	else
	{
		tasks[execute[0]].funcExecNum++;
	}

	//実行する予定のタスクIDを、前にずらす
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

	return 1;
}

void checkWakeupTask(void)
{
	//SLEPT状態のタスクをWakeup状態にするか判定する
	int i;
	for(i = 0; i < taskCount; i++)
	{
		if((tasks[i].status & E_SLEPT) == 0x00)
		{
			int exeFunc = tasks[i].funcExecNum;
			if(tasks[i].funcs[exeFunc].judge->jType == E_VALIABLE)
			{
				int argument = *(tasks[i].funcs[exeFunc].judge->moveVal);
				int response = *(tasks[i].funcs[exeFunc].judge->moveRes);
			
				if(argument == response)
				{
					tasks[i].status &= ~E_SLEPT;
					tasks[i].status |= E_ENWUP;
				}
			}
			else if(tasks[i].funcs[exeFunc].judge->jType == E_TIMER)
			{
				int response = *(tasks[i].funcs[exeFunc].judge->moveRes);
				
				if(response == tmr_OS_GetTimer())
				{
					tasks[i].status &= ~E_SLEPT;
					tasks[i].status |= E_ENWUP;
					*tasks[i].funcs[exeFunc].judge->moveRes += *tasks[i].funcs[exeFunc].judge->moveVal;
					*tasks[i].funcs[exeFunc].judge->moveRes &= 0xFFFF;	//65536
				}
			}
		}
	}
}