#include "src\STC12C5A.h"		 

#include <intrins.h>      //51�������㣨����_nop_�պ�����
#include <math.h>

#include "src\Define.h"


///////ȫ�ֱ���///////
uchar data DelayTime=9;	  //<=8Ч����ã�
uchar data INTTime=0x40;  //0x40;	
uchar data gain=6;
uchar data Menu=2;
uchar idata refreshflag[40];
uchar  data LEDBuf[35];	  //15�У������ң�����λΪ�棨1����
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



void PWM_init (void)	  //PWM��ʼ������	 //PWMģʽ����P1.3�ӿڣ�PWM0��,ǿ����.
{		   
	CMOD=0x00;    //����PCA��ʱ��	  0x00��0x03��
 	CL=0xEF; 
 	CH=0xEF;
	CCAPM0=0x42; //PWM0����PCA������ʽΪPWM��ʽ��0100 0010��
 	CCAP0L=0xEF; //����PWM0��ʼֵ��CCAP0H��ͬ
 	CCAP0H=0xFF; // PWM0��ʼʱΪ0

 	CR=1;        //����PCA��ʱ��
}

void PWM0_set (uchar set)	   //PWM0ռ�ձ����ú���	(0x00~0xFF)
{
	CCAP0L= set; //����ֵд��CCAP0L
 	CCAP0H= set; //����ֵд��CCAP0H
}


void IOINIT(void)							  //I/Oǿ����ģʽ��
{
	P4SW = 0xff;	                          //����I/O��P4��
	P4M1 = B(00000000); P4M0 = B(10000000);P47=0;//����
	P0M1 = 0x00;	    P0M0 = 0xff;       P0=0; //�����У�Y����L:OFF�� H��H+:ON,ON+;��
	P1M1 = B(01000011); P1M0 = B(00110100);P1=B(10110111); //(P17@�����裬IN��&P16@�����裬IN����TouchKey) ... P14@(��ͳIO,Beep��IN) P13@(ǿ�ƣ�OUT)������ ... P11@(���裬IN)AD2;P10@(���裬IN)AD1;      
	P2M1 = B(00000000); P2M0 = B(11111111);P2=0; //�����У�X0��Left������L:OFF�� H��H+:ON,ON+;��  
	P3M1 = B(00000000);	P3M0 = B(11111111);P3=0; //�����У�X1��Right������L:OFF�� H��H+:ON,ON+;��  	      
	P1ASF =B(00000011);                          //��P10,P11��IO����Ϊģ�����빦�ܣ�     

//  Y(P0)
//  ��
//H	|
// 	|
//	|
//L	|
//	 ---------------------��
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
	PWM0_set(x);                 //����PWMռ�ձ�

	BufToLED_Refresh();	 		
}  


void Timer_INT()
{
 	TMOD = 0x11; //��4λ����T/C1 
	EA = 1;	     //�����ж�
	TH1 = 0x00;  //16λ�����Ĵ���T1��8λ
	TL1 = 0x00;  //16λ�����Ĵ���T1��8λ
	ET1 = 1;     //T/C1�жϿ�
    TR1 = 1;     //T/C1����

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

	PWM_init();      //PWM��ʼ��
	PWM0_set(0xFB);
	
	Timer_INT();

	for(i=0;i<34;i++) 
		LEDBuf[i]=0x00;
	FontDisp();

	while(520)
	{
		for(i=0;i<65;i++)
		{  
			dd[i].real=(GetADCResult(0)+GetADCResult(1))<<gain;	  //��ȡad������Ŵ�
		}

		 processfft();//����Ҷ�仯������

		 ///////////////////TouchKey//////////////////////////
		 while(P16==1)					   //���ݣ����� ���ų���ʱ��̣�
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
			 if(++Count==300)	  //��ƽֵ��С���⽵��gain�����������ĵ�ƽ��ʾ��
			 {
				Count=0;
				//if(++Menu==4)Menu=0;	  	//�л�Menu����ʾ��ʽ��
				gain=6;

				P14=0;			  //Beep
				Delays(1000);
				P14=1;
			 }
		 }
		 else 
		 {
			 Count=1;
	
			 if(++num==0xAF)			 //����ʱ��Auto gain��
			 {
				num=0;

				P14=0;			           //Beep
				Delays(700);
				P14=1;
				                           //�Զ����棻Automatic gain;
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


