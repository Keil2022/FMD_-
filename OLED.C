#include	"SYSCFG.h"
#ifndef __OLED_H
#define __OLED_H

#include "stdlib.h"
#include "oledfont.h"  	 

const u8 OLED_GRAM[128][8];

#define OLED_SCLK 	RA3
#define OLED_SDIN 	RA2
#define OLED_RS  	RC0

#define OLED_CMD  0	//д????
#define OLED_DATA 1	//д????


//??ʼ??SSD1306					    
void OLED_Init(void)
{
	
}

#endif