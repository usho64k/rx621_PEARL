#include "testcode/main.h"
#include "pearl621.h"			//write at head of *****(project name).c and hwsetup.c

#include "pearl621_intr.h"
#include "pearl621_task.h"

#ifdef MAIN_H
#include <stdio.h>
#endif

void pearl621_init(void)
{
	//OS�̏������֐�
	tmr_OS_Initialize();
	initTask();
}

void tskMainLoop(void)
{
	//OS�̃��C�����[�v
	int i;
	while(1)
	{
		selectTask();
		executeTask();
		printf("executed #%d",i);
	}
}

void osTmrInterrupt(void)
{
	//OS�̃^�C�}���荞��
	tmr_OS_Interrupt();
}
