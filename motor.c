#include	"SYSCFG.h"
#ifndef __MOTOR_H
#define __MOTOR_H

#define REVERSE 0

#if REVERSE
#define INA    RC2
#define INB    RC3
#else
#define INA    RC3
#define INB    RC2
#endif

void MOTOR_Init(void)
{
	TRISC2 = 0;	//PC2输出模式
	TRISC3 = 0;	//PC3输出模式
    
	INA = 0;
    INB = 0;
}

void Forward(void)	//前进
{
	INA = 1;
    INB = 0;
}

void Backward(void)	//后退
{
	INA = 0;
    INB = 1;
}

void Stop(void)	//停止
{
	INA = 0;
    INB = 0;
}

void Brake(void)	//刹车
{
    INA = 1;
    INB = 1;
}

#endif