#include <math.h>
#include "display.h"
#include "1602.h"
#include "FFT.h"
#define uchar unsigned char
#define uint unsigned int
/***************************************************/
extern struct compx           		//���帴���ṹ��
{
	float real;						/*ʵ��*/
	float imag;						/*�鲿*/
};
extern xdata struct compx s[ 64 ]; 	//FFT���ݻ������XDATA�ռ�

/****************************************************
������:
****************************************************/						
void main()             							
{
	int N=64,i;     				//������ʼ����64��FFT����
	P0=0xff;
	P2=0xff;
	lcdInit();
	lcdWritePic();				    //��ʾһ���ַ�
 	P1ASF=0x01;		      			//P10����ADʹ��
	P1M0 = 0x01;                	//0000��0001����A/Dת����P1.x�ڣ�����Ϊ��©
	P1M1 = 0x01;                	//0000��0001 P1.0����Ϊ��©���Ͽ��ڲ���������													  
	while(1)
	{					
		for(i=0;i<N;i++)     	 			//�ɼ�64����Ƶ�ź�
  		{ 
			ADC_CONTR=0xC8;	 				//40.96K������	����ADC_CONTR��5��6λ������ο�˵����
			while(!(ADC_CONTR&0x10));
			s[i].real=(float)ADC_RES*4+(float)(ADC_RESL);//����ɼ�ֵ	 //���Ľ���ߣ�λ���ƣ�λ���ͣ�λ���䣬Ȼ�����
   			s[i].imag=0;
  		}  
  		FFT(s,N);               			//����FFT�������б任
  		showbar();							//��ʾƵ��					
	}
}