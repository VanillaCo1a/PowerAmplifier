#include<stc12c5a.h>
#include<intrins.h>
//#include"basic.h"

sbit led9 = P0^7;//9L
sbit led13 = P2^0;//13L
sbit led15 = P2^1;//15L
sbit led16 = P2^2;//16L
sbit led12 = P2^5;//12L
sbit led8 = P1^2;//8L
sbit led7 = P1^3;//7L
sbit led6 = P1^4;//6L
sbit led5 = P1^5;//5L
sbit led4 = P1^6;//4L
sbit led3 = P1^7;//3L
sbit led14 = P3^7;//14L
sbit led11 = P3^6;//11L
sbit led10 = P3^4;//10L
sbit led2 = P3^3;//2L
sbit led1 = P3^2;//1L

sbit hang4 = P0^0;//4H
sbit hang3 = P0^1;//3H
sbit hang2 = P0^2;//2H
sbit hang1 = P0^3;//1H
sbit hang11 = P0^4;//11H
sbit hang12 = P0^5;//12H
sbit hang10 = P0^6;//10H
sbit hang5 = P2^3;//5H
sbit hang6 = P2^4;//6H
sbit hang7 = P2^6;//7H
sbit hang8 = P2^7;//8H
sbit hang9 = P3^5;//9H

typedef unsigned char uint8;
typedef unsigned int uint16;
#define ADC_FLAG    (1<<4)    /*ADC_�жϱ�־*/
/*�Ŵ�128�����sin������128��*/ 
code char SIN_TAB[128]={0,6,12,18,24,30,36,42,48,54,59,65,70,75,80,85,89,94,98,102, 
                        105,108,112,114,117,119,121,123,124,125,126,126,126,126,126,
125,124,123,121,119,117,114,112,108,105,102,98,94,89,85,80,75,
70,65,59,54,48,42,36,30,24,18,12,6,0,-6,-12,-18,-24,-30,-36,-42,
-48,-54,-59,-65,-70,-75,-80,-85,-89,-94,-98,-102,-105,-108,-112,
-114,-117,-119,-121,-123,-124,-125,-126,-126,-126,-126,-126,-125,
-124,-123,-121,-119,-117,-114,-112,-108,-105,-102,-98,-94,-89,-85,
-80,-75,-70,-65,-59,-54,-48,-42,-36,-30,-24,-18,-12,-6
  };
 
/*�Ŵ�128�����cos������128��*/
code char COS_TAB[128]={127,126,126,125,124,123,121,119,117,114,112,108,105,102,98,94, 
                        89,85,80,75,70,65,59,54,48,42,36,30,24,18,12,6,0,-6,-12,-18,-24,
-30,-36,-42,-48,-54,-59,-65,-70,-75,-80,-85,-89,-94,-98,-102,
-105,-108,-112,-114,-117,-119,-121,-123,-124,-125,-126,-126,-126,
-126,-126,-125,-124,-123,-121,-119,-117,-114,-112,-108,-105,-102,
-98,-94,-89,-85,-80,-75,-70,-65,-59,-54,-48,-42,-36,-30,-24,-18,
-12,-6,0,6,12,18,24,30,36,42,48,54,59,65,70,75,80,85,89,94,98,102,
105,108,112,114,117,119,121,123,124,125,126,126
  };
 
/*�����洢���б�*/
code char LIST_TAB[128] = {0,64,32,96,16,80,48,112,8,72,40,104,24,88,56,120,4,68,36,100,20,84,52,116,
                           12,76,44,108,28,92,60,124,2,66,34,98,18,82,50,114,10,74,42,106,26,90,58,
  122,6,70,38,102,22,86,54,118,14,78,46,110,30,94,62,126,1,65,33,97,17,81,49,
  113,9,73,41,105,25,89,57,121,5,69,37,101,21,85,53,117,13,77,45,109,29,93,61,
  125,3,67,35,99,19,83,51,115,11,75,43,107,27,91,59,123,7,71,39,103,23,87,55,
  119,15,79,47,111,31,95,63,127
 };
 
/*�ּ�������*/
uint8 QTY_TAB[] = {0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};
uint8 ADC_Count=0;
uint8 i,j,k,b,p,anum; 
uint16 xdata Fft_Real[128]; 
uint16 xdata Fft_Image[128];               // fft���鲿 
uint8 xdata LED_TAB[16]; //��¼��ɫ��״
uint8 data lie[16] = {0};
uint8 data hang[12] = {0};
int lie_count = 0;
int hang_count = 0;

void delay_ms(uint16 ms)
{
	   unsigned char a,b,z;
	   for (z = 0; z < ms; ++z)
	   {
	   	 	for(b=4;b>0;b--)
         	for(a=248;a>0;a--);
   			 _nop_();  //if Keil,require use intrins.h
	   }
    
}

void lie_rst()
{
	uint8 i;
	for (i = 0; i < 16; ++i)
	{
		lie[i] = 1;
	}
} 

void hang_rst()
{
	uint8 i;
	for (i = 0; i < 12; ++i)
	{
		hang[i] = 0;
	}
}

void lie_work()
{
	led1 = lie[0];
	led2 = lie[1];
	led3 = lie[2];
	led4 = lie[3];
	led5 = lie[4];
	led6 = lie[5];
	led7 = lie[6];
	led8 = lie[7];
	led9 = lie[8];
	led10 = lie[9];
	led11 = lie[10];
	led12 = lie[11];
	led13 = lie[12];
	led14 = lie[13];
	led15 = lie[14];
	led16 = lie[15];
}

void hang_work()
{
	hang1 = hang[0];
	hang2 = hang[1];
	hang3 = hang[2];
	hang4 = hang[3];
	hang5 = hang[4];
	hang6 = hang[5];
	hang7 = hang[6];
	hang8 = hang[7];
	hang9 = hang[8];
	hang10 = hang[9];
	hang11 = hang[10];
	hang12 = hang[11];
}

/********************************************************************
* ���� : FFT
* ���� : ��������ת��
* ���� : ��
* ��� : ������ֵ
***********************************************************************/
void FFT()//��2fft
{                 
uint16 Temp_Real,Temp_Imag,temp;                // �м���ʱ����
uint16 TEMP1 = 0,max=0;
for( i=1; i<=7; i++)                            /* for(1) */
{ 
b=1;
b <<=(i-1);                                 //��ʽ���㣬���ڼ���������м������� ��һ�� 1��2�м���
for( j=0; j<=b-1; j++)                      /* for (2) */
{ 
p=1;
p <<= (7-i);            
p = p*j;
for( k=j; k<128; k=k+2*b)               /* for (3)  */
{ 
Temp_Real=Fft_Real[k];
Temp_Imag=Fft_Image[k];
temp=Fft_Real[k+b];
Fft_Real[k]=Fft_Real[k]+((Fft_Real[k+b]*COS_TAB[p])>>7)+((Fft_Image[k+b]*SIN_TAB[p])>>7);
Fft_Image[k]=Fft_Image[k]-((Fft_Real[k+b]*SIN_TAB[p])>>7)+((Fft_Image[k+b]*COS_TAB[p])>>7);
Fft_Real[k+b]=Temp_Real-((Fft_Real[k+b]*COS_TAB[p])>>7)-((Fft_Image[k+b]*SIN_TAB[p])>>7);
Fft_Image[k+b]=Temp_Imag+((temp*SIN_TAB[p])>>7)-((Fft_Image[k+b]*COS_TAB[p])>>7);          // ��λ.��ֹ���. ����Ѿ��Ǳ�ֵ�� 1/64               
Fft_Real[k] >>= 1;             
Fft_Image[k] >>= 1; 
Fft_Real[k+b] >>= 1;                 
Fft_Image[k+b] >>= 1;                                                      
}     
} 
} 
 
for(j=0;j<16;j++)//16��Ƶ 
{ 
TEMP1=((((Fft_Real[j+1]* Fft_Real[j+1]))+((Fft_Image[j+1]*Fft_Image[j+1])))>>1);//���Ƶ�η�ֵ
if(TEMP1<1)TEMP1=0; 
LED_TAB[j]=TEMP1; 
if(LED_TAB[j]>max) max=LED_TAB[j];
}
if(max > 16)//�ּ�����
{
max/=16;
for(j=0;j<16;j++)LED_TAB[j]/=max;
}       
}

 
/********************************************************************
* ���� : GPIO_init
* ���� : GPIO��ʼ��
* ���� : ��
* ��� : ������ֵ
***********************************************************************/
void GPIO_init()
{
P0M0 = 1; P0M1 = 0; P0 = 0XFF;    /*��*/
P2M0 = 1; P2M1 = 0; P2 = 0XFF;
P3M0 = 1; P3M1 = 0; P3 = 0XFF;   /*��*/
}
/********************************************************************
* ���� : timer_Init
* ���� : �ڲ��Ĵ�����ʼ��
* ���� : ��
* ��� : ��
***********************************************************************/
void timer_Init()
{
	//AUXR = 0x40;
TMOD = 0X12;
TH0 = 0xb0;                                  
TL0 = 0xb0;
ET0 = 1;        //��ʱ��0 ��
TR0 = 0;        //�رն�ʱ��
TH1 = 0xf8; 
TL1 = 0X30;
ET1  = 1;
TR1  = 1; 
EA   = 1; 
}
/********************************************************************
* ���� : adc_Init
* ���� : �ڲ��Ĵ�����ʼ��
* ���� : ��
* ��� : ��
***********************************************************************/
void adc_Init()
{   
ADC_CONTR = 0x80;             //ADC��Դ��
_nop_();_nop_();_nop_();_nop_();
P1ASF = 0x01;                 //0000,0001, �� P1.0 �ó�ģ���
AUXR1 &=0xFB;                 //1111,1011, �� ADRJ=0
P1M1 = 0x01;
P1M0 = 0x00;
ADC_RES = 0x00;               //����Ĵ���
ADC_RESL = 0x00;
EADC  = 1;   //AD�жϴ�
EA = 1;   //���жϴ�
}
 
/********************************************************************
* ���� : main
* ���� : ������
* ���� : ��
* ��� : ��
***********************************************************************/
void main()
{
uint8 i = 0;
//GPIO_init();
timer_Init();
adc_Init();
while(1)
{
ADC_Count = 0;
EADC = 1;
TR0  = 1;
while(ADC_Count < 128);       //����128��
for(i=0; i<128; i++)   //����鲿
{
Fft_Image[i] = 0;
}
FFT();                        //FFT���㲢ת��Ϊ��Ƶ�η�ֵ
 //delay_ms(5);
}
}
/********************************************************************
* ���� : ADC_Finish
* ���� : ADCת������жϷ���
* ���� : ��
* ��� : ��
***********************************************************************/
void ADC_Finish() interrupt 5
{
Fft_Real[LIST_TAB[ADC_Count]] = (int)(((ADC_RES)<<1)+(ADC_RESL>>1)*2)<<4;    /*��LIST_TAB��˳�򣬽��д洢����ֵ*/
if(ADC_Count <= 127)
{
ADC_Count++;           /*�Զ���������*/
ADC_CONTR &= !ADC_FLAG;
}
else
{
EADC = 0;
TR0  = 0; 
} 
}
/********************************************************************
* ���� : interrupt_timer1
* ���� : ��ʾ��Ļˢ���жϷ���
* ���� : ��
* ��� : ��
***********************************************************************/
void interrupt_timer1() interrupt 3
{ 
	TH1 = 0xf8;  
	TL1 = 0x30;  
	
	
	
	
		
		hang_rst();
		lie_rst();
		lie[lie_count] 	 = 	0;
		
		if(LED_TAB[lie_count] > 11)    LED_TAB[lie_count] = 11;
		if(LED_TAB[lie_count] < 0)    LED_TAB[lie_count] = 0;
		for (hang_count = 11; hang_count >= 11-LED_TAB[lie_count]; --hang_count)
		{
			hang[hang_count] = 1;
		}
		hang_work();
		lie_work();
		lie_count++;
		if (lie_count == 16)
		{
			lie_count = 0;
		}
}
/********************************************************************
* ���� : Ad_Control
* ���� : ���Ʋ�����
* ���� : ��
* ��� : ��
***********************************************************************/
void Ad_Control() interrupt 1
{
ADC_CONTR = 0xe8;       //��ʼAD�ɼ�
_nop_();_nop_();_nop_();_nop_(); 
} 