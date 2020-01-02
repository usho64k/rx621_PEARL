//標準関数群
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
static void test_intrTimer(void);		//タイマ割り込み

int main(void)
{
	pid_t p_pid,pid;

	printf("parent process : %d\n",p_pid = getpid());
	//main
	pearl621_init();
	//ここにタスクを登録していく
	makeAllTasks();

	//タスク実行開始
	startAllTasks();
	
	//タスク実行本体
	switch(pid=fork())
	{
	case 0:
		tskMainLoop();
		exit(0);
	case -1:
		perror("fork");
		break;
	default:
		printf("[%d]child pid=%d\n",p_pid,pid);
		break;
	}

	//割り込み実行本体
	switch(pid=fork())
	{
	case 0:
		test_intrTimer();
		exit(0);
	case -1:
		perror("fork");
		break;
	default:
		printf("[%d]child pid=%d\n",p_pid,pid);
		break;
	}
	//実行

	pid = wait(0);
	printf("[%d]pid = %d end\n",p_pid,pid);
	pid = wait(0);
	printf("[%d]pid = %d end\n",p_pid,pid);

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

static void test_intrTimer(void)
{
	while(1)
	{
		sleep(1);
		osTmrInterrupt();	//普通に割り込み関数を呼ぶだけ
	}
}
