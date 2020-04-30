#include "pearl621_chatter_usr.h"
#include "pearl621_chatter.h"
#include "..\iodefine.h"


volatile static T_CHATTER chatter_setting[32];
volatile static unsigned char data_chatter[32];
volatile static unsigned char state_chatter[32];
volatile static unsigned char flag_chatter[32];

volatile static int chatter_num;


/********************************************************/
/*					Chattering Driver					*/
/********************************************************/
void init_chatteringDrv(void)
{
    int i;
	//chattering driver setting
	chatter_num = 0;
	for(i = 0; i < 32; i++)
	{
		chatter_setting[i].c_num = 0;
		chatter_setting[i].judge = (void *)(0);
		chatter_setting[i].bits = 0;
		chatter_setting[i].v_func_on = (void *)(0);
		chatter_setting[i].v_func_off = (void *)(0);

		data_chatter[i] = 0;
		state_chatter[i] = 0;
		flag_chatter[i] = 0;
	}
}

//Interrupt statics
void checkPortChattering(void)
{
	//process at chattering
	int i;
	for(i = 0; i < chatter_num; i++)
	{
		int j;
		unsigned char chk = 0x01;
		//if port is 0, it is not set.
		if(chatter_setting[i].judge == (void *)(0))
			continue;
		
		PORT4.DR.BIT.B6 = 1;
		//make value of checking bitfield
		for(j = 0; j < chatter_setting[i].bits-1;j++)
		{
			chk = (chk << 1);
		}

		//check chattering
		if((chatter_setting[i].judge() & chk) != state_chatter[i])
		{
			data_chatter[i]++;
			if(data_chatter[i] == chatter_setting[i].c_num)
			{
				//chattering reset and change state and trigger flag is to be on.
				state_chatter[i] = (chatter_setting[i].judge() & chk);
				if(state_chatter[i] != 0)
				{
					if(chatter_setting[i].v_func_on != (void *)0)
					{
						chatter_setting[i].v_func_on();
					}
				}
				else
				{
					if(chatter_setting[i].v_func_off != (void *)0)
					{
						chatter_setting[i].v_func_off();
					}
					PORT4.DR.BIT.B6 = 0;
				}
				
				flag_chatter[i] = 1;
				data_chatter[i] = 0;
			}
		}
		else
		{
			//trigger miss. and reset counter
			data_chatter[i] = 0;
		}
	}
}

//flag reset.
void resetFlagChatter(int id)
{
	if((id >= 0) && (id < chatter_num))
	{
		flag_chatter[id] = 0;
	}
}

//1... flag stood ,  0... flag not stood
int getFlagChatter(int id)
{
	if((id >= 0) && (id < chatter_num))
	{
		return flag_chatter[id];
	}

	return 0;
}

//return ercd
int createChatter(T_CHATTER t)
{
	if(t.judge == 0)
	{
		return -4;		//iregular pointer
	}
	if(t.bits > 15)
	{
		return -8;		//iregular num
	}
	if(chatter_num == 32)
	{
		return -1;		//id over
	}

    //no problem and set object
	chatter_setting[chatter_num].judge = t.judge;
	chatter_setting[chatter_num].c_num = t.c_num;
	chatter_setting[chatter_num].bits = t.bits;
	chatter_setting[chatter_num].v_func_on = t.v_func_on;
	chatter_setting[chatter_num].v_func_off = t.v_func_off;
	chatter_num++;

    return 0;
}