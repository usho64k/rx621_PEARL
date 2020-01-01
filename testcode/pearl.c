//標準関数群
#include <stdio.h>
#include <stdlib.h>

//OS
#include "../pearl621.h"

//テストコード用
#include "main.h"

//タスクコード用
#include "dummyTask/dummyTask1.h"
#include "dumtask2/dummyTask2.h"




#define THIS_NULL		(void *)(0)

static void makeAllTasks(void);			//タスク作成
static void startAllTasks(void);		//タスク起動

int main(void)
{
	//main
	pearl621_init();
	//ここにタスクを登録していく
	makeAllTasks();

	//タスク実行
	startAllTasks();
	
	//実行
	tskMainLoop();

	return 0;
}
static void makeAllTasks(void)
{
	makeTask_tsk1();
	makeTask_tsk2();
}
static void startAllTasks(void)
{
	int ercd = 0;

	startTask(DUMTASK1_ID);
	while(ercd < 0){printf("error at start[%d}\n",DUMTASK1_ID);}
	startTask(DUMTASK2_ID);
	while(ercd < 0){printf("error at start[%d}\n",DUMTASK2_ID);}
}


