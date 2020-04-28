#ifndef __PEARL621_H__
#define __PEARL621_H__


//User Public header
extern void pearl621_init(void);					//OS初期化関数
extern void tskMainLoop(void);						//Main Loop
extern void osTmrInterrupt(void);					//割り込み本体(TMR0に登録するなどする)

extern int getTimer(void);							//OSカウンタ値を直接見る関数

//produced function for task modules
#include "pearl621_task_usr.h"

//produced function for chattering driver
#include "pearl621_chatter_usr.h"

//produced function for interrupt control
extern void dis_int(void);
extern void ena_int(void);

#endif
