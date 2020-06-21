#include 	"FFT.h"
/********************************************************************/
float pow   (float x, float y);	  //计算x的y次幂
float cos   (float val);
float sin   (float val);
struct compx       //定义复数结构体
{
	float real;	   /*实部*/
	float imag;	   /*虚部*/
};

/******************************************************************* 
函数原型：struct compx EE(struct compx a1,struct compx b2) 
函数功能：对两个复数进行乘法运算
输入参数：两个以联合体定义的复数a,b 
输出参数：a和b的乘积，以联合体的形式输出
*******************************************************************/
struct compx EE(struct compx a1,struct compx b2) 	//复数乘法
{
	struct compx b3;
	b3.real=a1.real*b2.real-a1.imag*b2.imag;
	b3.imag=a1.real*b2.imag+a1.imag*b2.real;
	return(b3);
}

/***************************************************************** 
FFT函数
函数原型：void FFT(struct compx *xin,int N) 
函数功能：对输入的复数组进行快速傅里叶变换（FFT）
输入参数：xin[]数组，struct型
*****************************************************************/ 
void FFT(struct compx xin[],int N)   				
{
	int f,m,nv2,nm1,i,k,j=1,l;
	struct compx v,w,t;
	int le,lei,ip;	   			//FFT运算核，使用蝶形运算完成FFT运算
  	float pi;
	nv2=N/2;					//变址运算，即把自然顺序变成倒位序，采用雷德算
	f=N;
	for(m=1;(f=f/2)!=1;m++){;}
	nm1=N-1;
	for(i=0;i<nm1;i++)          //倒序操作
	{
		if(i<j)	 				//如果i<j,即进行变址
		{
			t=xin[j];
			xin[j]=xin[i];
			xin[i]=t;
		}
		k=nv2;    				//求j的下一个倒位序  	//k为倒序中相应位置的权值
		while(k<j)
		{
			j=j-k; 				//把最高位变成0
			k=k/2; 				//k/2，比较次高位，依次类推，逐个比较，直到某个位为0
		}
		j=j+k;	   				//把0改为1 
	}
	 
	for(l=1;l<=m;l++)  		//计算l的值，即计算蝶形级数
	{
		le=pow(2,l);    	//乘方
		lei=le/2;
		pi=3.14159265;		//给结构体赋值
		v.real=1.0;	  		//实部为正弦波FFT_N点采样，赋值为1
		v.imag=0.0;  	  				//虚部为0
		w.real=cos(pi/lei);   			//旋转因子
		w.imag=-sin(pi/lei);
		
	for(j=1;j<=lei;j++)      			//控制蝶形运算的级数
 		{
		for(i=j-1;i<N;i=i+le) 			//控制每级蝶形运算的次数
  			{
				ip=i+lei;  				//i，ip分别表示参加蝶形运算的两个节点
   				t=EE(xin[ ip ],v); 		//蝶形运算，详见公式
   				xin[ ip ].real=xin[ i ].real-t.real;   
   				xin[ ip ].imag=xin[ i ].imag-t.imag;
   				xin[ i ].real=xin[ i ].real+t.real;
   				xin[ i ].imag=xin[ i ].imag+t.imag;
  			}
  			v=EE(v,w); //改变系数，进行下一个蝶形运算  
  		}     
	}
}