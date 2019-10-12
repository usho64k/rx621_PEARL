#include "testcode/main.h"
#include "pearl621.h"			//write at head of *****(project name).c and hwsetup.c

#include "pearl621_intr.h"
#include "pearl621_task.h"


void pearl621_init(void)
{
	//OS�̏������֐�
	tmr_OS_Initialize();
	initTask();
}

void tskMainLoop(void)
{
	//OS�̃��C�����[�v
	while(1)
	{
		int ercd;
		ercd = selectTask();
		if(ercd == 0)
		{
			ercd = executeTask();
		}
	}
}

void osTmrInterrupt(void)
{
	//OS�̃^�C�}���荞��
	tmr_OS_Interrupt();
}
