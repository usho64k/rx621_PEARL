#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "../pearl621.h"








#define THIS_NULL		(void *)(0)

static int itIsTrue = 0;
static int itIsTrue2 = 0;

void printffff(void);
static void countInit(void);
static void countLoop(void);
static void countLoop2(void);

T_TSK task1 = {THIS_NULL,0,128};

T_JUDGE judge1 = {E_VALIABLE,&itIsTrue,&itIsTrue};
T_JUDGE judge2 = {E_VALIABLE,&itIsTrue2,&itIsTrue2};

T_FUNKS func1 = {&judge1,countInit};
T_FUNKS func2 = {&judge1,countLoop};
T_FUNKS func3 = {&judge2,countLoop2};

static int count;

void main(void)
{
	int ercd = 0;
		//main
		pearl621_init();
		//ここにタスクを登録していく
		ercd = createTask(0,&task1);
		while(ercd < 0){printf("error at create");}

		ercd = setTaskFunc(0,&func1);
		while(ercd < 0){printf("error at setTaskFunc1");}
		ercd = setTaskFunc(0,&func2);
		while(ercd < 0){printf("error at setTaskFunc2");}

		ercd = startTask(0);
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


void printffff(void)
{
	printf("supersamurai\r\n");
}
