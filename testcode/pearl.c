#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "../pearl621.h"



#define THIS_NULL		(void *)(0)

void printffff(void);

const T_TSK TASK_METHODS001 = { THIS_NULL,5,0};

const T_JUDGE T01_J01 = {E_NOTYPE,THIS_NULL,THIS_NULL};
const T_FUNKS T01_F01 = {&T01_J01, printf};

void main(void)
{
		//main
		pearl621_init();
		//ここにタスクを登録していく
		createTask(0,&TASK_METHODS001);

		setTaskFunc(0,&T01_F01);
		//mainloop
		tskMainLoop();
}

void printffff(void)
{
	printf("supersamurai\r\n");
}
