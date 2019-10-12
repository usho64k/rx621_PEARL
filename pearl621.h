#ifndef __PEARL621_H__
#define __PEARL621_H__

#define THIS_NULL		(void *)(0)

//User Public header
extern void pearl621_init(void);					//OS初期化関数
extern void tskMainLoop(void);						//Main Loop
extern void osTmrInterrupt(void);					//割り込み関数

//タスク判定式
typedef enum judgeType
{
	E_NOTYPE,
	E_TIMER,		//内部タイマ反応
	E_IOFLAG,		//I/O反応
	E_MESSAGE,		//メールボックス反応
	E_VALIABLE		//特定変数反応
}E_JTYPE;

//タスク関数実行条件
typedef struct t_tskExinf{
	E_JTYPE		jType;		//条件タイプ
	int *		moveVal;	//判定する条件式
	int *		moveRes;	//関数実行時の条件結果
}T_JUDGE;

//タスク関数
typedef struct t_taskfunks{
	T_JUDGE		*judge;		//関数の実行条件
	void 		(*po)();	//実行する関数ポインタ
}T_FUNKS;

//タスク作成用(T_CTSKはRTOS用語なんだが…？)
typedef struct t_ctsk{
	void *		exinf;		//External information(TBD)
	int			pri;		//Task Priority(0-15)
	int			stksize;	//Task Stack Size(TBD)
}T_TSK;

//produced function for Task
extern int createTask(int tskid,const T_TSK *pk_ctsk);	//pearl621Task.c
extern int deleteTask(int tskid);					//pearl621Task.c
extern int startTask(int tskid);					//pearl621Task.c
extern int sleepTask(int tskid,int millisecond);	//pearl621Task.c
extern int wakeupTask(int tskid);					//pearl621Task.c

extern int setTaskFunc(int tskid,const T_FUNKS *func);		//pearl621Task.c

#define TSK_MAX		8
#define TSKFUNK_MAX	24
#endif
