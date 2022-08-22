#include	"SYSCFG.h"
#ifndef __KEY_H
#define __KEY_H

#include "led.c"
#include "motor.c"

#define KEY1    RA7
#define KEY2    RA6
#define KEY3    RC1
#define KEY4    RA4

#define KEY_Press 	0
#define KEY_Lift 		1
#define	True			1
#define	Fault			0

#define KEY_ShortTime		5	//50ms
#define KEY_LongTime		70	//700ms
#define KEY_EndTime		300	//3s
#define Inching_SetTime	5

#define Back_Off_BrakeTime		1
#define Back_Off_BackwardTime	(Back_Off_BrakeTime+1)

bit KEY1_ShortOK;		//�̰���Ч
bit KEY1_LongOK;			//������Ч
bit KEY1_EndOK;			//��������
u8 KEY1_Phase;			//�����׶�
u16 KEY1_TimeCount;	//����ʱ��

bit KEY2_ShortOK;
bit KEY2_LongOK;	
bit KEY2_EndOK;
u8 KEY2_Phase;
u16 KEY2_TimeCount;

bit KEY3_ShortOK;
bit KEY3_LongOK;	
bit KEY3_EndOK;
u8 KEY3_Phase;
u16 KEY3_TimeCount;

bit KEY4_ShortOK;
bit KEY4_LongOK;	
bit KEY4_EndOK;
u8 KEY4_Phase;
u16 KEY4_TimeCount;

bit MODE = 0; 	//0-�㶯ģʽ�� 1-����ģʽ
u8 Inching_Time = 0;
u8 Back_Off = 0;

void Key_Init(void)
{
	TRISC |= 0x02;	//PC1����ģʽ
	WPUC |= 0x02;	//PC1������
   
	TRISA |= 0xD0;	//PA4 6 7����ģʽ
	WPUA |= 0xD0;	//PA4 6 7������ 
    
	KEY1_Phase = 0;
    KEY1_TimeCount = 0;
    
	KEY2_Phase = 0;
    KEY2_TimeCount = 0;
    
	KEY3_Phase = 0;
    KEY3_TimeCount = 0;
    
	KEY4_Phase = 0;
    KEY4_TimeCount = 0;
}

void Key1_Scanf(void)
{
	switch(KEY1_Phase)
    {
		case 0:
					//����1
					if(KEY1 == KEY_Press)
					{
						KEY1_TimeCount++;
						if(KEY1_TimeCount >=  KEY_LongTime)
						{
							//KEY1_Phase = 1;	//ע�͵�Ϊ ����ת��������
						}
					}
					else
					{
						if(KEY1_TimeCount >= KEY_ShortTime)		KEY1_ShortOK = True;
						KEY1_TimeCount = 0;
					}
		break;
        
        
        case 1:
					if(KEY1 == KEY_Press)
					{
						KEY1_TimeCount++;
						if(KEY1_TimeCount >= KEY_EndTime)
						{
							KEY1_Phase = 2;
                            //KEY1_LongOK = True;
						}
					}
					else
					{
						KEY1_Phase = 0;
						KEY1_TimeCount = 0;
                        KEY1_LongOK = True;
					}
		break;
        
        
        case 2:
					if(KEY1 == KEY_Lift)	//�ȴ�����
					{
						KEY1_Phase = 0;
						KEY1_TimeCount = 0;
                        KEY1_LongOK = True;
					}
		break;
        

        default:
					KEY1_Phase = 0;
					KEY1_TimeCount = 0;
		break;
	}
}

void Key_Scanf(void)
{
	//����1
	if(KEY1 == KEY_Press)
	{
		KEY1_TimeCount++;
		if(KEY1_TimeCount >=  KEY_LongTime)
		{
			//KEY1_Phase = 1;	//ע�͵�Ϊ ����ת��������
		}
        else {/*do nothing*/}
	}
	else
	{
		if(KEY1_TimeCount >= KEY_ShortTime)	KEY1_ShortOK = True;
        else {/*do nothing*/}

		KEY1_TimeCount = 0;
	}
	
	//����2
	if(KEY2 == KEY_Press)
	{
		KEY2_TimeCount++;
		if(KEY2_TimeCount >=  KEY_LongTime)
		{
			//KEY2_Phase = 1;	//ע�͵�Ϊ ����ת��������
		}
        else {/*do nothing*/}
	}
	else
	{
		if(KEY2_TimeCount >= KEY_ShortTime)	KEY2_ShortOK = True;
        else {/*do nothing*/}
		
		KEY2_TimeCount = 0;
	}
	
	//����3
	if(KEY3 == KEY_Press)
	{
		KEY3_TimeCount++;
		if(KEY3_TimeCount >=  KEY_LongTime)
		{
			//KEY2_Phase = 1;	//ע�͵�Ϊ ����ת��������
		}
        else {/*do nothing*/}
	}
	else
	{
		if(KEY3_TimeCount >= KEY_ShortTime)	KEY3_ShortOK = True;
        else {/*do nothing*/}
        
		KEY3_TimeCount = 0;
	}	
	
	//����4
	if(KEY4 == KEY_Press)
	{
		KEY4_TimeCount++;
		if(KEY4_TimeCount >=  KEY_ShortTime)
		{
            if(MODE)	Forward();
            else
            {
                if(Inching_Time)
                {
                    Forward();
                    if(Inching_Time > 0) Inching_Time--;
                }
            }
            
			Back_Off = 0;
		}
        else {/*do nothing*/}
	}
	else
	{
		KEY4_TimeCount = 0;
        Inching_Time = Inching_SetTime;
        
		if(Back_Off < 255)	Back_Off++;
		if(Back_Off <= Back_Off_BrakeTime)					Brake();
        else if(Back_Off <= Back_Off_BackwardTime)		Backward();
        else 	Stop();
	}    
}

void Key_Handle(void)
{
	if(KEY1_ShortOK == True)
    {
		KEY1_ShortOK = Fault;
        
		MODE ^= 1;
        LED = MODE;
	}
    else {/*do nothing*/}
    
	if(KEY2_ShortOK == True)
    {
		KEY2_ShortOK = Fault;
        
		
	}
    else {/*do nothing*/}
    
	if(KEY3_ShortOK == True)
    {
		KEY3_ShortOK = Fault;
        
		
	}
    else {/*do nothing*/}
}

#endif
