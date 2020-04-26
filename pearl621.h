#ifndef __PEARL621_H__
#define __PEARL621_H__


//User Public header
extern void pearl621_init(void);					//OS�������֐�
extern void tskMainLoop(void);						//Main Loop
extern void osTmrInterrupt(void);					//���荞�݊֐�

//�^�X�N���莮
typedef enum judgeType
{
	E_NOTYPE,
	E_TIMER,		//�����^�C�}����
	E_IOFLAG,		//I/O����
	E_MESSAGE,		//���[���{�b�N�X����
	E_VALIABLE		//����ϐ�����
}E_JTYPE;

//�^�X�N�֐����s����
typedef struct t_tskExinf{
	E_JTYPE		jType;		//�����^�C�v
	int *		moveVal;	//���肷�������
	int *		moveRes;	//�֐����s���̏�������
}T_JUDGE;

//�^�X�N�֐�
typedef struct t_taskfunks{
	T_JUDGE		*judge;		//�֐��̎��s����
	void 		(*po)();	//���s����֐��|�C���^
}T_FUNKS;

//�^�X�N�쐬�p(T_CTSK��RTOS�p��Ȃ񂾂��c�H)
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

//produced function for interrupt control
extern void dis_int(void);
extern void ena_int(void);

#define TSK_MAX		8
#define TSKFUNK_MAX	24
#endif
