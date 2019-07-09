#include "..\iodefine.h"		//use iodefine.h

#include "pearl621.h"			//write at head of *****(project name).c and hwsetup.c
#include "pearl621_intr.h"		//write at head of intprg.c



//Timer interrupt setting(static)
static app_timcnt;
static dis_intr_taskTimer(void);
static ena_intr_taskTimer(void);

//Timer interrupt setting for OS
static dis_intr_taskTimer(void)
{
	TMR0.TCR.BIT.CMIEA = 0;
}
//Timer interrupt setting for OS
static ena_intr_taskTimer(void)
{
	TMR0.TCR.BIT.CMIEA = 1;
}
//Timer definition for OS
void tmr_OS_Initialize(void)
{
	//For RX621(Clock speed -> 48MHz)
	SYSTEM.MSTPCRA.BIT.MSTPA5 = 0;
	
	//TMR1 [Count for 1.5MHz]
	//TMR0 [Count overflows of Timer1]
	TMR0.TCCR.BIT.CSS = 3;		//Clock resource is Timer1
	TMR1.TCCR.BIT.CSS = 1;		//Clock resource is internal clock(PCLK)
	TMR1.TCCR.BIT.CKS = 3;		//Count at PCLK / 32
	TMR0.TCR.BIT.CCLR = 1;		//Clear counter for compare match
	TMR0.TCR.BIT.OVIE = 0;		//Disable use overflow interrupt
	TMR1.TCR.BIT.OVIE = 0;		//Disable use overflow interrupt
	
	app_timcnt = 0;				//high rayer counter reset.
 	TMR01.TCNT = 0x00;			//Counter reset.
	TMR01.TCORA = 1500;			// 48 MHz / 32 = 1500kHz -> 1kHz
	TMR01.TCORB = 0x00;			//Clear.
	ICU.IPR[0x68].BYTE = 0x0F;	//interrupt priority is 15(Max)
	//vector table =>174
}
//Set at vector table 174
void tmr_OS_Interrupt(void)
{
	dis_intr_taskTimer();
	app_timcnt++;
	if(app_timcnt == 65536)
	{
		app_timcnt = 0;
	}
	ena_intr_taskTimer();
}

void tskMainLoop(void)
{
	//MainLoop
}
int createTask(int tskid,T_CTSK pk_ctsk)
{
	
}
int deleteTask(int tskid)
{
	
}
int startTask(int tskid)
{
	
}
int sleepTask(int tskid,int millisecond)
{
	
}
int wakeupTask(int tskid)
{
	
}