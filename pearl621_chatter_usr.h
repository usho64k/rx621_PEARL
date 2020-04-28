#ifndef PEARL621_CHATTER_USR
#define PEARL621_CHATTER_USR

typedef struct t_chatter{
	unsigned char *port;			//target port (pointer)
	void (*v_func_on)();			//For the flag, the function execute in interrupt(state is not 0). Set (void *)0 to unuse.
	void (*v_func_off)();			//For the flag, the function execute in interrupt(state is 0). Set (void *)0 to unuse.
	unsigned char bits;				//bitfield (0:normal 1～8:single port(bit shifted -1) 9～15:undef)
	unsigned char c_num;			//Number of changing at counted number of chattering check
}T_CHATTER;

int createChatter(T_CHATTER t_cht);	//create the chattering object
void resetFlagChatter(int id);     //reset Flag
int getFlagChatter(int id);        //get Flag
#endif