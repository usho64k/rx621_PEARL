#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "../pearl621.h"






#define THIS_NULL		(void *)(0)

static int itIsTrue = 0;
static int itIsTrue2 = 0;
static int itIsTrue3 = 1;

//タスク1用
static void countInit(void);
static void countLoop(void);
static void countLoop2(void);
static void countLoop3(void);
//タスク2用
static void countInit2(void);
static void countLoop2_3(void);

T_TSK task1 = {THIS_NULL,0,128};
T_TSK task2 = {THIS_NULL,0,128};

T_JUDGE judge1 = {E_VALIABLE,&itIsTrue,&itIsTrue};
T_JUDGE judge2 = {E_VALIABLE,&itIsTrue2,&itIsTrue2};
T_JUDGE judge3 = {E_VALIABLE,&itIsTrue3,&itIsTrue3};

T_FUNKS func1 = {&judge1,countInit};
T_FUNKS func2 = {&judge1,countLoop};
T_FUNKS func3 = {&judge2,countLoop2};
T_FUNKS func4 = {&judge3,countLoop3};

T_FUNKS func_task2[3] = 
{
	{&judge1,countInit2},
	{&judge1,countLoop2_3},
	{&judge2,countLoop2_3},
};


static int count;
static int count2;

void main(void)
{
	int ercd = 0;
		//main
		pearl621_init();
		//ここにタスクを登録していく
		ercd = createTask(0,&task1);
		while(ercd < 0){printf("error at create");}
		ercd = createTask(1,&task2);
		while(ercd < 0){printf("error at create");}

		ercd = setTaskFunc(0,&func1);
		while(ercd < 0){printf("error at setTaskFunc1");}
		ercd = setTaskFunc(0,&func2);
		while(ercd < 0){printf("error at setTaskFunc2");}

		ercd = setTaskFunc(1,&func_task2[0]);
		while(ercd < 0){printf("error at setTaskFunc2");}
		ercd = setTaskFunc(1,&func_task2[1]);
		while(ercd < 0){printf("error at setTaskFunc2");}
		

		ercd = startTask(0);
		while(ercd < 0){printf("error at start");}
		ercd = startTask(1);
		while(ercd < 0){printf("error at start");}
		

		tskMainLoop();
}

static void countInit(void)
{
	//タスク1のInitialize
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

static void countLoop3(void)
{
	count+=3;
	printf("Output %d\r\n",count);
}

static void countInit2(void)
{
	//タスク2のInitialize
	count2 = 0;
	printf("Task 2 Initialized\n");
}

static void countLoop2_3(void)
{
	count2+=3;
	printf("Output:::: %d\r\n",count2);
}
