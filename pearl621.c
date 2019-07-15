#include "..\iodefine.h"		//use iodefine.h

#include "pearl621.h"			//write at head of *****(project name).c and hwsetup.c

#include "pearl621_intr.h"
#include "pearl621_task.h"


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
		executeTask();
	}
}

void osTmrInterrupt(void)
{
	//OSのタイマ割り込み
	tmr_OS_Interrupt();
}