#include <math.h>
#include "display.h"
#include "1602.h"
#include "FFT.h"
#define uchar unsigned char
#define uint unsigned int
/***************************************************/
extern struct compx           		//定义复数结构体
{
	float real;						/*实部*/
	float imag;						/*虚部*/
};
extern xdata struct compx s[ 64 ]; 	//FFT数据缓存放在XDATA空间

/****************************************************
主函数:
****************************************************/						
void main()             							
{
	int N=64,i;     				//变量初始化，64点FFT运算
	P0=0xff;
	P2=0xff;
	lcdInit();
	lcdWritePic();				    //显示一个字符
 	P1ASF=0x01;		      			//P10口做AD使用
	P1M0 = 0x01;                	//0000，0001用于A/D转换的P1.x口，先设为开漏
	P1M1 = 0x01;                	//0000，0001 P1.0先设为开漏。断开内部上拉电阻													  
	while(1)
	{					
		for(i=0;i<N;i++)     	 			//采集64点音频信号
  		{ 
			ADC_CONTR=0xC8;	 				//40.96K采样率	设置ADC_CONTR第5、6位，具体参考说明书
			while(!(ADC_CONTR&0x10));
			s[i].real=(float)ADC_RES*4+(float)(ADC_RESL);//存入采集值	 //ＡＤ结果高８位左移２位，低２位不变，然后相加
   			s[i].imag=0;
  		}  
  		FFT(s,N);               			//调用FFT函数进行变换
  		showbar();							//显示频谱					
	}
}