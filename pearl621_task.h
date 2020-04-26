#ifndef __PEARL621_TASK_H__
#define __PEARL621_TASK_H__


extern int initTask(void);			//タスク構造の初期化

extern int selectTask(void);		//メインループで起動可能なタスクを選別
extern int executeTask(void);		//メインループで実際にタスクを実行

#endif