#ifndef PEARL621_CHATTER_H
#define PEARL621_CHATTER_H

typedef struct t_chatter{
	unsigned char *port;			//target port (pointer)
	void (*v_func)();				//For the flag, the function execute in interrupt. Set (void *)0 to unuse.
	unsigned char bits;				//bitfield (0:normal 1～8:single port(bit shifted -1) 9～15:undef)
	unsigned char c_num;			//Number of changing at counted number of chattering check
}T_CHATTER;

void init_chatteringDrv(void);
void resetFlag(int id);             //reset Flag
int getFlag(int id);                //get Flag
int setChatteringDrv(T_CHATTER t);  //set to id


void checkPortChattering(void);	    //chattering driver(used on pearl621_intr.c)

#endif