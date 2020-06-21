#include "src\STC12C5A.h"		 

#include <intrins.h>      //51基本运算（包括_nop_空函数）
#include <math.h>

#include "src\Define.h"


///////全局变量///////
uchar data DelayTime=9;	  //<=8效果最好；
uchar data INTTime=0x40;  //0x40;	
uchar data gain=6;
uchar data Menu=2;
uchar idata refreshflag[40];
uchar  data LEDBuf[35];	  //15列；从左到右；亮的位为真（1）；
uint32  data TouchKey=0;
uchar data CBeep=0;
//////////////////////


void Delays(uint t)
{  
	uint j;
	while(--t)
		for(j=0;j<5;j++);    
}
void Delaysms(uint t)
{  
	uint j;
	while(--t)
		for(j=0;j<15;j++);    
}



#include "src\ADC.c"
#include "src\Font.c"
#include "src\fft.h"



void PWM_init (void)	  //PWM初始化函数	 //PWM模式，接P1.3接口（PWM0）,强上拉.
{		   
	CMOD=0x00;    //设置PCA定时器	  0x00～0x03；
 	CL=0xEF; 
 	CH=0xEF;
	CCAPM0=0x42; //PWM0设置PCA工作方式为PWM方式（0100 0010）
 	CCAP0L=0xEF; //设置PWM0初始值与CCAP0H相同
 	CCAP0H=0xFF; // PWM0初始时为0

 	CR=1;        //启动PCA定时器
}

void PWM0_set (uchar set)	   //PWM0占空比设置函数	(0x00~0xFF)
{
	CCAP0L= set; //设置值写入CCAP0L
 	CCAP0H= set; //设置值写入CCAP0H
}


void IOINIT(void)							  //I/O强上拉模式；
{
	P4SW = 0xff;	                          //启动I/O：P4；
	P4M1 = B(00000000); P4M0 = B(10000000);P47=0;//震动马达；
	P0M1 = 0x00;	    P0M0 = 0xff;       P0=0; //点阵列（Y）（L:OFF； H，H+:ON,ON+;）
	P1M1 = B(01000011); P1M0 = B(00110100);P1=B(10110111); //(P17@（高阻，IN）&P16@（高阻，IN）；TouchKey) ... P14@(传统IO,Beep，IN) P13@(强推，OUT)呼吸灯 ... P11@(高阻，IN)AD2;P10@(高阻，IN)AD1;      
	P2M1 = B(00000000); P2M0 = B(11111111);P2=0; //点阵行（X0（Left））（L:OFF； H，H+:ON,ON+;）  
	P3M1 = B(00000000);	P3M0 = B(11111111);P3=0; //点阵行（X1（Right））（L:OFF； H，H+:ON,ON+;）  	      
	P1ASF =B(00000011);                          //将P10,P11的IO设置为模拟输入功能；     

//  Y(P0)
//  ↑
//H	|
// 	|
//	|
//L	|
//	 ---------------------→
//	[L:X0(P2):H][L:X1(P3):H]

//TestCode:
//	P0=B(10000000);
//	P2=B(00000001);
//	P3=B(00010000);

}



void BufToLED_Refresh()                     //Refresh&Write Buf to LED ;
{	
	 uchar data i; 
	 uchar data X=1;	  
	 uchar data Y=1;
	 for(X=1,i=2;X;X<<=1,i+=2)              //for(X=1;X!=0;X<<=1) //8bit
	 {
	  	P2=X;
		for(Y=1;Y!=0;Y<<=1)		            //Y=Y<<1;
	 	{
			P0=Y&LEDBuf[i];
			Delays(DelayTime);
			P0=0;
		}
		P2=0;	
	 };
	 for(X=1;X<B(10000000);X<<=1,i+=2)	    //7bit
	 {
	  	P3=X;
		for(Y=1;Y!=0;Y<<=1)		            //Y=Y<<1;
	 	{
			P0=Y&LEDBuf[i];
			Delays(DelayTime);
			P0=0;
		}
		P3=0;	
	 };
		
}




void LEDRefresh_INT() interrupt 3 //using 3   
{ 
	static uint x=0;		   
	static uchar flag=1;

    TL1 = 0x00;      
    TH1 = INTTime;               //0x50~0x80 

 	if(flag)
	{
		if(++x==0xFF)			 //MINOUTPUT
		{
			flag=0;		
		}		
	}
	else
	{
		if(--x==0xCF)	         //MAXOUTPUT
		{
			flag=1;			
		}
	}	 		
	PWM0_set(x);                 //设置PWM占空比

	BufToLED_Refresh();	 		
}  


void Timer_INT()
{
 	TMOD = 0x11; //高4位控制T/C1 
	EA = 1;	     //开总中断
	TH1 = 0x00;  //16位计数寄存器T1高8位
	TL1 = 0x00;  //16位计数寄存器T1低8位
	ET1 = 1;     //T/C1中断开
    TR1 = 1;     //T/C1启动

}


void FullScan()
{
	uchar data X=1;	  
	uchar data Y=1;

	 for(Y=1;Y!=0;Y<<=1)		       //Y=Y<<1;
	 {	
	 	P0=Y;
		for(X=1;X;X<<=1)	           //8bit
		{
		 	P2=X;
			Delays(7);	
		};

		P2=0;
		for(X=1;X<B(10000000);X<<=1)    //7bit
		{
		 	P3=X;
			Delays(7);
		};
		P3=0;
		P0=0;
	 }
}


void Main()
{  
	uint data Count=700;
	uchar data i,Cgain,num=0;

	IOINIT();
	InitADC();                   

	while(--Count)
		FullScan();

	for(i=0;i<40;i++) refreshflag[i]=0x09;
	
	P14=0;			  //Beep
	Delays(4000);
	P14=1;

	PWM_init();      //PWM初始化
	PWM0_set(0xFB);
	
	Timer_INT();

	for(i=0;i<34;i++) 
		LEDBuf[i]=0x00;
	FontDisp();

	while(520)
	{
		for(i=0;i<65;i++)
		{  
			dd[i].real=(GetADCResult(0)+GetADCResult(1))<<gain;	  //读取ad结果并放大；
		}

		 processfft();//傅立叶变化及处理

		 ///////////////////TouchKey//////////////////////////
		 while(P16==1)					   //依据：脉冲 干扰持续时间短；
		 {	
			if(CBeep)P14=0;
			if(++TouchKey>0x0000FF00)break;	
		 }
		 P14=1;

		 if(P16==1)
		 {
			if(++Menu==4)Menu=0;

			P14=0;
			P47=1;
			Delays(7000);	  
			P14=1;
			P47=0;		
		 }	
			TouchKey=0;
		 //////////////////////////////////////////////

		if(P17==0)CBeep=!CBeep;

		 if(dd[2].real<32)
		 {
			 if(++Count==300)	  //电平值过小，这降低gain，减少噪音的电平显示；
			 {
				Count=0;
				//if(++Menu==4)Menu=0;	  	//切换Menu，显示方式；
				gain=6;

				P14=0;			  //Beep
				Delays(1000);
				P14=1;
			 }
		 }
		 else 
		 {
			 Count=1;
	
			 if(++num==0xAF)			 //播放时，Auto gain；
			 {
				num=0;

				P14=0;			           //Beep
				Delays(700);
				P14=1;
				                           //自动增益；Automatic gain;
				Cgain=dd[2].real/32;
				if(7<Cgain<=8) 
				{
					gain=4;
					
				}
				else if(4<Cgain<=6) 
				{
					gain=5;
					
				}
				else if(2<Cgain<=4) 
				{
					gain=6;
				}
				else 
				{
					gain=7;
			
				}
	
			 }

		  }		 
	}
	while(1);
}


