#include	"SYSCFG.h"
#ifndef __LED_H
#define __LED_H

#define LED    RC4

void LED_Init(void)
{
	TRISC4 = 0;	//PC4????ģʽ
    LED = 0;
}

#endif

