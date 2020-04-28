#include "pearl621.h"			//write at head of *****(project name).c and hwsetup.c

#include "pearl621_intr.h"
#include "pearl621_task.h"

#ifdef TESTCODE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "testcode/main.h"
#endif

void pearl621_init(void)
{
	//OS初期化
	tmr_OS_Initialize();
	initTask();
}

void tskMainLoop(void)
{
	//OS本ループ
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
#ifdef MAIN_H
		sleep(1);
#endif
	}
}

void osTmrInterrupt(void)
{
	//OSで使うタイマ割り込み
	tmr_OS_Interrupt();
}

int getTimer(void)
{
	//OSカウンタ値を直接見る関数
	return tmr_OS_GetTimer();

}

//produced function for interrupt control
extern void dis_int(void)
{
	dis_intr_taskTimer();
}

extern void ena_int(void)
{
	ena_intr_taskTimer();
}