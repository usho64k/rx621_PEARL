#ifndef PEARL621_CHATTER_H
#define PEARL621_CHATTER_H


void init_chatteringDrv(void);		//OSの初期化時に行うチャタリングドライバ初期化

void checkPortChattering(void);	    //OSの割り込み処理内で行うチャタリングチェック処理

#endif