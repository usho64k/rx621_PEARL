#ifndef __PEARL621_TASK_H__
#define __PEARL621_TASK_H__


extern int initTask(void);			//初期化関数(タスク構造)

extern int selectTask(void);		//メインループ関数(タスク選別)
extern int executeTask(void);		//メインループ関数(タスク実行)

#endif