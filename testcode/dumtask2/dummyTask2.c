#include <stdio.h>
#include "dummyTask2.h"
#include "../../pearl621.h"

#define THIS_NULL		((void *)0)
#define TASK2_FUNC_NUM	3	

static int itIsTrue = 0;
static int itIsTrue2 = 0;
static int itIsTrue3 = 0;
static int count;

static void countInit(void);
static void countLoop1(void);
static void countLoop2(void);
//static void countLoop3(void);

static T_TSK task2 = {THIS_NULL,0,128};

static T_JUDGE judge_task2[3] = 
{
	{E_VALIABLE,&itIsTrue,&itIsTrue},
	{E_VALIABLE,&itIsTrue2,&itIsTrue2},
	{E_VALIABLE,&itIsTrue3,&itIsTrue3}
};

static T_FUNKS func_task2[3] =
{
	{&judge_task2[1],countInit},
	{&judge_task2[1],countLoop1},
	{&judge_task2[1],countLoop2}
};

static void countInit(void)
{
	count = 0;
	printf("Task 2 Initialized \r\n");
}
static void countLoop1(void)
{
	count += 3;
	itIsTrue2++;
	printf("Output:::: %d\r\n",count);
}
static void countLoop2(void)
{
	count += 3;
}
/*static void countLoop3(void)
{
	count += 3;
}*/

//public
void makeTask_tsk2(void)
{
	int ercd = 0;
	
	ercd = createTask(1,&task2);
	while(ercd < 0){printf("error at create");}

	ercd = setTaskFunc(1,&func_task2[0]);
	while(ercd < 0){printf("error at setTask2Func1");}
	ercd = setTaskFunc(1,&func_task2[1]);
	while(ercd < 0){printf("error at setTask2Func2");}
}
