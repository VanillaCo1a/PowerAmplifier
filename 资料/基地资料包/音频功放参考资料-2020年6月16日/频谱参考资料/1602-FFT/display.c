#include 	"display.h"
#include 	"1602.h"
#define uchar unsigned char
#define uint unsigned int
/******************************************************************/
xdata struct compx s[ 64 ]; 			//FFT数据缓存放在XDATA空间
extern float pow   (float x, float y);	//计算x的y次幂
extern float cos   (float val);
extern float sin   (float val);						
float sqrt  (float val);				//计算一个非负实数的平方根
extern struct compx           			//定义复数结构体
{
	float real;	/*实部*/
	float imag;	/*虚部*/
};

/*******************************************************************
显示频谱函数
LCD1602显示方式：从下往上，从左往右
j=1	
j=2	 	 
******************************************************************/
void showbar(void)
{
	uchar i,j,dat1,dat2;
	uint  tmp1=0,tmp2=0;  // 系数

	for(i=1;i<32;i+=4)
	{
		float t0=0,t2=0;
		t0=sqrt(pow((s[i  ].real+s[i+1].real),2)+pow((s[i  ].imag+s[i+1].imag),2))/2;
		t2=sqrt(pow((s[i+2].real+s[i+3].real),2)+pow((s[i+2].imag+s[i+3].imag),2))/2;
		//z=a+bi  ∣z∣=√（a^2+b^2)
		//求变换后结果的模值，存入复数的实部部分
		tmp1=(uint)(t0/2); //放大倍数，可改变
		tmp2=(uint)(t2/2);
		for(j=2;j>0;j--)
		{  							  //dat范围是0~7，表示显示8个自定义字符的第几个
			if (tmp1>=8) 	          //满格 第0(j=0)层第dat1格，第1(j=1)层第tmp1格
			{
				dat1=7;
				tmp1=tmp1-8;
			}			
			else  
				if(tmp1==0) dat1=32;			//空格 大于15小于33都为空格 0x10~0x20为空字符
					else 								
					 {
						 dat1=tmp1-1;			//1-8格
						 tmp1=0;
					 }
						
			dispString(i/2,j-1,dat1);	   //第1、2、5、7、9、11、13、15列	 //32/4=8							   
			if (tmp2>=8)				   //满格
			{
				dat2=7;
				tmp2=tmp2-8;
			} 			
			else  
				if(tmp2==0) dat2=32;		//空格
					else 
					 {
						 dat2=tmp2-1;		//1-8格
						 tmp2=0;
					 }											
			dispString(i/2+1,j-1,dat2);    //第2、4、6、8、10、12、14、16列
		} 						
	}
}
