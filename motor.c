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
	TRISC2 = 0;	//PC2���ģʽ
	TRISC3 = 0;	//PC3���ģʽ
    
	INA = 0;
    INB = 0;
}

void Forward(void)	//ǰ��
{
	INA = 1;
    INB = 0;
}

void Backward(void)	//����
{
	INA = 0;
    INB = 1;
}

void Stop(void)	//ֹͣ
{
	INA = 0;
    INB = 0;
}

void Brake(void)	//ɲ��
{
    INA = 1;
    INB = 1;
}

#endif