#ifndef PEARL621_TASK_USR
#define PEARL621_TASK_USR

//関数起動タイプ定義値
typedef enum judgeType
{
	E_NOTYPE,
	E_TIMER,		//1ms周期タイマのカウントコンペアマッチ
	E_IOFLAG,		//I/Oポート起動
	E_MESSAGE,		//メッセージオブジェクト待機
	E_VALIABLE		//変数条件コンペアマッチ
}E_JTYPE;

//各関数起動の情報の構造体
typedef struct t_tskExinf{
	E_JTYPE		jType;		//関数起動タイプ指定
	int *		moveVal;	//起動変数1(説明読んで欲しいが、主に可動値)
	int *		moveRes;	//起動変数2(説明読んで欲しいが、主に静的値)
}T_JUDGE;

//各関数の情報の構造体
typedef struct t_taskfunks{
	T_JUDGE		*judge;		//関数起動情報
	void 		(*po)();	//起動情報に沿って実行する関数
}T_FUNKS;

//タスクの情報の構造体
typedef struct t_ctsk{
	void *		exinf;		//External information(TBD)
	int			pri;		//Task Priority(0-15)
	int			stksize;	//Task Stack Size(TBD)
}T_TSK;

//produced function for Task
extern int createTask(int tskid,const T_TSK *pk_ctsk);	//pearl621Task.c
extern int deleteTask(int tskid);						//pearl621Task.c
extern int startTask(int tskid);						//pearl621Task.c
extern int sleepTask(int tskid,int millisecond);		//pearl621Task.c
extern int wakeupTask(int tskid);						//pearl621Task.c

extern int setTaskFunc(int tskid,const T_FUNKS *func);	//pearl621Task.c

#define TSK_MAX		8           //
#define TSKFUNK_MAX	24

#endif