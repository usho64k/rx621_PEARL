#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "../pearl621.h"



#define THIS_NULL		(void *)(0)

void printffff(void);

T_TSK task1 = {THIS_NULL,0,128};
T_JUDGE judge1 = {E_VALIABLE,THIS_NULL,THIS_NULL};
T_FUNKS func1 = {&judge1,printffff};

void main(void)
{
		//main
		pearl621_init();
		//ここにタスクを登録していく
		createTask(1,&task1);
		createTask(0,&task1);
		setTaskFunc(0,&func1);
		startTask(0);

		//tskMainLoop();
}

void printffff(void)
{
	printf("supersamurai\r\n");
}
