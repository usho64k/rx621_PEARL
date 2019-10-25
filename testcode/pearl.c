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
static void countLoop1(void);
static void countLoop2(void);
static void countLoop3(void);
//タスク2用
static void countInit2(void);
static void countLoop2_1(void);
static void countLoop2_2(void);
static void countLoop2_3(void);

T_TSK task1 = {THIS_NULL,0,128};
T_TSK task2 = {THIS_NULL,0,128};

T_JUDGE judge1 = {E_VALIABLE,&itIsTrue,&itIsTrue};
T_JUDGE judge2 = {E_VALIABLE,&itIsTrue2,&itIsTrue2};
T_JUDGE judge3 = {E_VALIABLE,&itIsTrue3,&itIsTrue3};

T_FUNKS func_task1[3] =
{
	{&judge1,countInit},
	{&judge1,countLoop1},
	{&judge2,countLoop2}
};

T_FUNKS func_task2[3] = 
{
	{&judge2,countInit2},
	{&judge2,countLoop2_1},
	{&judge2,countLoop2_2}
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
		
		ercd = setTaskFunc(0,&func_task1[0]);
		while(ercd < 0){printf("error at setTask1Func1");}
		ercd = setTaskFunc(0,&func_task1[1]);
		while(ercd < 0){printf("error at setTask1Func2");}
		
		ercd = setTaskFunc(1,&func_task2[0]);
		while(ercd < 0){printf("error at setTask2Func1");}
		ercd = setTaskFunc(1,&func_task2[1]);
		while(ercd < 0){printf("error at setTask2Func2");}
		
		//タスク実行
		ercd = startTask(0);
		while(ercd < 0){printf("error at start");}
		ercd = startTask(1);
		while(ercd < 0){printf("error at start");}
		
		//実行
		tskMainLoop();
}

static void countInit(void)
{
	//タスク1のInitialize
	count = 0;
	printf("Output %d\r\n",count);
}

static void countLoop1(void)
{
	count++;
	if(itIsTrue2 == 10)
	{
		itIsTrue2 = 0;
	}
	printf("Output %d\r\n",count);
}

static void countLoop2(void)
{
	count++;
	printf("Output %d\r\n",count);
}

static void countLoop3(void)
{
	count++;
	printf("Output %d\r\n",count);
}

static void countInit2(void)
{
	//タスク2のInitialize
	count2 = 0;
	printf("Task 2 Initialized\n");
}

static void countLoop2_1(void)
{
	count2+=3;
	itIsTrue2++;
	printf("Output:::: %d\r\n",count2);
}

static void countLoop2_2(void)
{
	count2+=3;
}

static void countLoop2_3(void)
{
	count2+=3;
}
