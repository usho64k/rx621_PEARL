//#include "testcode/main.h"
#include "pearl621_intr.h"

#ifndef MAIN_H
#include "..\iodefine.h"
#endif

//Timer interrupt setting(static)
static int app_timcnt;

//Timer interrupt en/disable
static void dis_intr_taskTimer(void);
static void ena_intr_taskTimer(void);

/********************************************************/
/*					Public function						*/
/********************************************************/
//Timer interrupt setting for OS
#ifndef MAIN_H
static void dis_intr_taskTimer(void)
{
	TMR0.TCR.BIT.CMIEA = 0;
}
//Timer interrupt setting for OS
static void ena_intr_taskTimer(void)
{
	TMR0.TCR.BIT.CMIEA = 1;
}
#else
//OS検査用
static void dis_intr_taskTimer(void)
{
    return;
}

static void ena_intr_taskTimer(void)
{
    return;
}
#endif

/********************************************************/
/*					Public function						*/
/********************************************************/
//Timer definition for OS
#ifndef MAIN_H
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
#else
void tmr_OS_Initialize(void)
{
	//For Linux Test Env.(Clear the variable only)
    app_timcnt = 0;
}
#endif

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
