#include <stdio.h>
#include "dummyTask1.h"
#include "../../pearl621.h"

#define TASK1_FUNC_NUM		3
static int itIsTrue = 0;
static int count;

static void countInit(void);
static void countLoop(void);
static void countLoop2(void);

T_TSK task1 = {THIS_NULL,0,128};

T_JUDGE judgeThisTask[TASK1_FUNC_NUM] = {
	{E_VALIABLE,&itIsTrue,&itIsTrue},
	{E_VALIABLE,&itIsTrue,&itIsTrue},
	{E_VALIABLE,&itIsTrue,&itIsTrue}
};

T_FUNKS funcThisTask[TASK1_FUNC_NUM] = {
	{&judgeThisTask[0],countInit},
	{&judgeThisTask[1],countLoop},
	{&judgeThisTask[2],countLoop2}
};

int makeTask(void)
{
	int i,ercd = 0;
	ercd = createTask(0,&task1);

	for(i = 0; i < TASK1_FUNC_NUM; i++)
	{
		ercd = setTaskFunc(0,&funcThisTask[i]);
		while(ercd < 0){printf("error at create");}
	}
}

int startTasks(void)
{
	int ercd = 0;
	ercd = startTask(0);
	while(ercd < 0){printf("error at start");}
}

static void countInit(void)
{
	count = 0;
	printf("Output %d\r\n",count);
}
static void countLoop(void)
{
	count++;
	printf("Output %d\r\n",count);
}
static void countLoop2(void)
{
	count+=2;
	printf("Output %d\r\n",count);
}
