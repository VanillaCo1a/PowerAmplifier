#ifndef __MAIN_H__
#define __MAIN_H__

#include<STC12C5A60S2.h>  
#include <intrins.h>



sbit LED1 = P1^5;
sbit LED2 = P3^0;
	


//函数或者变量声明
extern void Delay_ms(unsigned int n);


#endif