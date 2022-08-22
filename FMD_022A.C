//Project: FMD_022A.prj
// Device: FT61F02X
// Memory: Flash 2KX14b, EEPROM 256X8b, SRAM 128X8b
// Author: 
//Company: 
//Version:
//   Date: 
//===========================================================
//===========================================================
#include "SYSCFG.h"
#include "key.c"
#include "led.c"
#include "motor.c"
#include "Hardward.c"
#include "oled.c"
#include "oledfont.h"

BITS_T falg;
#define Per1ms	falg.bit0
#define Per10ms	falg.bit1

//��ʱ���ж����
void interrupt ISR(void)
{
	static u8 t00,t01;

	if(T0IF) 
	{ ///100usÿ��
		T0IF = 0;
		TMR0 += 256-200+2;	//ע��:��TMR0���¸�ֵTMR0�����������ڲ��仯
        
		if(++t00 >= 10)
        {
			t00 = 0;
            Per1ms = 1;
            if(++t01 >= 10)
            {
                t01 = 0;
                Per10ms = 1;
			}
		}
	}
    
	INTF = 0;  
}

//ϵͳ��ʼ��
void Sys_Init(void) 
{ 
	OSCCON = 0B01010001;    //WDT:32KHZ;	IRCF=101=16MHZ/4=4MHZ;
    //Bit0=1����ϵͳʱ��Ϊ�ڲ�������Bit0=0����ʱ��Դ��FOSC<2��0>����������ѡ��ʱѡ��

    INTCON= 0;      //�ݽ�ֹ�����ж�
	
	//�˿�����
	//A
    TRISA = 0x00;    //0-�����1-���룻
    PORTA = 0x00;	//���ݼĴ���
    //WPUA = 0x00;    //0-�ر���������1-��������

	//C
    TRISC     = 0x00;    //0-�����1-���룻
    PORTC     = 0x00;
    //WPUC      = 0x00;    //0-�ر���������1-��������
    
    MSCKCON = 0x00;
	//MSCKCON.7��������λ:д0
    //MSCKCON.6���VREG_OE:1 = ��Ƭ����ѹ����PA4 �� PC5 �����ѹ����ѹ��\
											  0 = PA4 �� PC5 Ϊ��ͨ IO
    //MSCKCON.5����T2CKSRC:0 = TIMER2 ʱ��ԴΪϵͳʱ��\
												1 = TIMER2 ʱ��ԴΪ�ڲ� 32MHz
    //MSCKCON.4����SLVREN:1 = �� LVR\
											0 = ��ֹ LVR\
											�� UCFG1<1:0>��Ϊ 01 ʱ����λ��ʵ������
    
    //MSCKCON.3��������λ��д0
    //MSCKCON.2����CKMAVG:1 = ��ƽ��ģʽ���Զ��������ۼ� 4 �Σ�\
												0 = �ر�ƽ��ģʽ
    //MSCKCON.1����CKCNTI:1 = ʹ�ܿ�ʱ�Ӳ�����ʱ������\
											0 = �رտ�ʱ�Ӳ�����ʱ������
    //MSCKCON.0��������λ��д0

    CMCON0 = 0B00000111;     //�رձȽ�����CxINΪ����IO��
    
//    ADCON1 = 0B01100000;     //DIVS=0,ʱ��ѡFOSC    //ADCS[2:0]=110,��ƵFOSC/64
//    ADCON0 = 0B10011101;     //B7,ADFM=1,����Ҷ���                         
    ANSEL = 0X00;	//�ر�����ģ������

    OPTION = 0x08;    //Bit4=1 WDT MODE,PS=000=1:1 WDT RATE	
    //Bit7(RAPU)=0 ENABLED PULL UP PA
    //Ԥ��Ƶ������� WDT
    
    T0IF = 0;	//0 = Timer0�Ĵ���û�����
}

//������
int main(void)
{
	Sys_Init();
    Key_Init();
    LED_Init();
    MOTOR_Init();
    
	//���ж�
	T0IE = 1;  	//����ʱ��0�ж�
	GIE = 1;   	//�����ж�
    
	//��ѭ��
	while(1)
    {
		T0IE = 1;  	//�_���r��0�Д�
		GIE = 1;   	//���Д�
		ClrWdt(); //�忴�Ź�
        
		if(Per1ms)
        {
            Per1ms = 0;
            
		}
        
		if(Per10ms)
        {
			Per10ms = 0;
            
			Key_Scanf();
            Key_Handle();
		}
	}
	return 0;
}
//===========================================================