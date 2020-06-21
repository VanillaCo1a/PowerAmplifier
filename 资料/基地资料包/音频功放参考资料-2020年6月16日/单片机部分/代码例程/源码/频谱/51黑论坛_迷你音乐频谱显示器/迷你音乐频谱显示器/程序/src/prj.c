/********************************************************************************************
程序名： 　　 迷你音乐频谱显示器
编写人： 　　 
编写时间：　　
硬件支持：　　2个8*8点阵  STC12C5A60S2　外部32.768MHz晶振 
接口说明：　　见说明文档　
*********************************************************************************************/
#include "src\STC12C5A.h"		 
#include <intrins.h>    //51基本运算（包括_nop_空函数）
#include <math.h>
#include "src\Define.h"
///////全局变量///////
uchar data DelayTime=10;
uchar data INTTime=0x45;
uchar data gain=1;
uchar data Menu=0;
uchar idata  refreshflag[40];
//////////////////////
void Delays(uint t)
{  
	uint j;
	while(--t)
		for(j=0;j<5;j++);    
}
uchar data LEDBuf[35];			 //15列；从左到右；亮的位为真（1）；
#include "src\ADC.c"
#include "src\fft.h"
#include "src\LED168D.h"

void LIOINIT( )
{
	P4SW = 0xff;	                          //启动I/O：P4；

	P0M1 = 0x00;	    P0M0 = 0xff;          //I/O强上拉模式；
	P1M1 = B(00000001);	P1M0 = B(11111110);   //P10(光敏电阻:AD：高阻或开漏)
	P4M1 = 0x00;     	P4M0 = 0xff;        
	P2M1 = B(00000000); P2M0 = B(11111001);   //P21,P20(强上拉)；P22(传统IO);
	P3M1 = 0x00;       	P3M0 = 0xff;          //!!!

	P0 = 0xff;		                          //初始化；
	P1 = B(11111110);
	P4 = 0xff;
	P2 = B(11111100);
	P3 = 0xff;	
	////////////////////////////////
	P04=0;P26=0;  //LY;
	P01=0;P45=0;
	P06=0;P24=0;
	P00=0;P46=0;
	P15=0;P34=0;
	P07=0;P23=0;
	P13=0;P32=0;
	P47=0;P37=0;
	////////////////////////////////
	P14=1; P33=1;  //LX0; //LX1; 
	P02=1; P44=1;         
	P03=1; P27=1;         
	P17=1; P36=1;         
	P05=1; P25=1;         
	P16=1; P35=1;         
	P12=1; P31=1;         
	P11=1; P30=1;         		
}

//////////////////////////////////////////////////////
void LEDRefresh() interrupt 3 //using 3   
{ 
    TL1 = 0x00;      
    TH1 = INTTime;   //0x50~0x80 //0x6A
	BuftoLED168_Refresh();
}  
/////////////////////////////////////////////////////

/*SFR中与定时/计数器工作方式有关的设计]
-----------------------------------------------------------------------------
M1	M0	方式	说明
0	0	0	13位T/C，由TL低5位和TH的8位组成13位计数器
0	1	1	16位T/C，TL和TH共16位计数器
1	0	2	8位T/C，TL用于计数，当TL溢出时将TH中的值自动写入TL
1	1	3	两组8位T/C
-----------------------------------------------------------------------------
*/
void Timer_INT()
{
 	TMOD = 0x11; //高4位控制T/C1 [ GATE，C/T，M1，M0，GATE，C/T，M1，M0 ]
	EA = 1;	//中断总开关

	TH1 = 0x00; //16位计数寄存器T1高8位（写入初值）
	TL1 = 0x00; //16位计数寄存器T1低8位
	ET1 = 1; //T/C1中断开关
    TR1 = 1; //T/C1启动开关
}

void Main()
{  
	uint data Count=700;
	uchar data i,Cgain,LED=0,num=0;
	LIOINIT();	  //I/O强上拉模式
	InitADC();    //Init ADC sfr  	
	for(i=0;i<40;i++) refreshflag[i]=0x09;
	P20=0;		  //LED负极
	Timer_INT();  //定时器初始化
	while(1)
	{
		for(i=0;i<65;i++)
		{  
			dd[i].real=(GetADCResult(0))<<gain;
			dd[i].imag=0; //清零虚部 
		}
		 processfft();//傅立叶变化及处理
		 LED=!LED;
		 if(dd[2].real<32)
		 {
		 	LED=1;
		 }
		 else 
		 {
			 Count=1;
			 if(++num==0xAF)				 //播放时，Auto gain；
			 {
				num=0;

				P2M0 = B(11111011); 
				P21=1;			  //LED正极
				Delays(2000);
				P21=0;			 //LED正极
				P2M0 = B(11111001); 

				//自动增益；Automatic gain;
				Cgain=dd[2].real/32;
				if(7<Cgain<=8) 
				{
					gain=2;
					
				}
				else if(4<Cgain<=6) 
				{
					gain=3;		
				}
				else if(2<Cgain<=4) 
				{
					gain=4;
				}
				else 
				{
					gain=5;
				}
			 }
		  }

		  P21=LED;	 //LED正极	 
	}
}
/*****************************************************************************/
//
/*****************************************************************************/

