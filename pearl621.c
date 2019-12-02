#include "pearl621.h"			//write at head of *****(project name).c and hwsetup.c

#include "pearl621_intr.h"
#include "pearl621_task.h"

#ifdef TESTCODE
#include <stdio.h>
#include "testcode/main.h"
#endif

void pearl621_init(void)
{
	//OSの初期化関数
	tmr_OS_Initialize();
	initTask();
}

void tskMainLoop(void)
{
	//OSのメインループ
	while(1)
	{
		int ercd;
		ercd = selectTask();
		if(ercd == 0)
		{
			ercd = executeTask();
		}
		else
		{
#ifdef MAIN_H
			printf("No Select");
#endif
		}
	}
}

void osTmrInterrupt(void)
{
	//OSのタイマ割り込み
	tmr_OS_Interrupt();
}
