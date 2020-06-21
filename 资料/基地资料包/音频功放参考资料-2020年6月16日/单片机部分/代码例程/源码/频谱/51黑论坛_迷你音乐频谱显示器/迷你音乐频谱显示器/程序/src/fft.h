#ifndef _FFT_INCLUDED_
#define _FFT_INCLUDED_

struct compx
{
	float real;
	float imag;
};//定义数据存放机构体 

struct compx dd[65]; //FFT数据段    
code float iw[64]=
{
	1.000,0,0.9952,-0.0980,0.9808,-0.1951,0.9569,-0.2903,0.9239,-0.3827,0.8819,-0.4714,0.8315,-0.5556,
	0.7730,-0.6344,0.7071,-0.7071,0.6344,-0.7730,0.5556,-0.8315,0.4714,-0.8819,0.3827,-0.9239,0.2903,-0.9569,
	0.1951,-0.9808,0.0980,-0.9952,0.0,-1.0000,-0.0980,-0.9952,-0.1951,-0.9808,-0.2903,0.9569,-0.3827,-0.9239,
	-0.4714,-0.8819,-0.5556,-0.8315,-0.6344,-0.7730,-0.7071,-0.7071,-0.7730,-0.6344,-0.8315,-0.5556,-0.8819,-0.4714,
	-0.9239,-0.3827,-0.9569,-0.2903,-0.9808,-0.1951,-0.9952,-0.0980
};//w值缓存区

data struct compx temp;  
//复数乘法
void ee(struct compx b1,uchar data b2)
{ 
	temp.real=b1.real*iw[2*b2]-b1.imag*iw[2*b2+1];
	temp.imag=b1.real*iw[2*b2+1]+b1.imag*iw[2*b2]; 
} 
//乘方函数,计算 nbottom^ntop   
uint mypow(uchar data nbottom,uchar data ntop)
{
    uint data result=1;
    uchar data t;    
    for(t=0;t<ntop;t++)result*=nbottom;//nbottom^ntop 
    return result;
}
//快速傅立叶变换  
void fft(struct compx *xin,uchar data N)
{
	uchar data  fftnum,i,j,k,l,m,n,disbuff,dispos,dissec;
	data struct compx t;
	fftnum=N;//傅立叶变换的点数
	for(m=1;(fftnum=fftnum/2)!=1;m++);//求得M的值 
	for(k=0;k<=N-1;k++)//码位倒置
	{
		n=k;
		j=0; 
		for(i=m;i>0;i--)//倒置
		{
			j=j+((n%2)<<(i-1));
			n=n/2;
		} 
		if(k<j){t=xin[1+j];xin[1+j]=xin[1+k];xin[1+k]=t;}//交换数据
	}  
	for(l=1;l<=m;l++)//fft运算
	{
		disbuff=mypow(2,l);//求得碟间距离
		dispos=disbuff/2;//求得碟形两点之间的距离
		for(j=1;j<=dispos;j++)
			for(i=j;i<N;i=i+disbuff)//遍历M级所有的碟形
			{
				dissec=i+dispos;//求得第二点的位置
				ee(xin[dissec],(uint)(j-1)*(uint)N/disbuff);//复数乘法
				t=temp;
				xin[dissec].real=xin[i].real-t.real;
				xin[dissec].imag=xin[i].imag-t.imag;
				xin[i].real=xin[i].real+t.real;
				xin[i].imag=xin[i].imag+t.imag;
			}
	}
} 

//对fft数据进行处理,得到各个频率段的电压幅值
void processfft( )
{ 
    uchar data pt=0,tmp; 
    for(pt=1;pt<65;pt++)
    {
        dd[pt].imag=0; //清零虚部 
    }
    fft(dd,64);//对当前数据进行傅立叶变换 
	dd[0].imag=0;  dd[0].real=0;
    for(pt=1;pt<65;pt++)
    {                                      
        dd[pt].real=sqrt(dd[pt].real*dd[pt].real+dd[pt].imag*dd[pt].imag);//取均方根 
    }

	if(Menu==1)
	{
		for(pt=2;pt<34;pt+=2)	
	    {       
			for(tmp=(dd[pt].real/32)+1,LEDBuf[pt]=0xFF;tmp>=1;tmp--)		  //tmp>1;不保留  最低位那一行常亮;{}一次也不执行；
			{
			 	LEDBuf[pt]<<=1;	
				
			}
			LEDBuf[pt]=~(LEDBuf[pt]);
		}
	}
	else if(Menu==2)
	{

		//下落感频谱
		for(pt=2;pt<34;pt+=2)	
	    {       
			tmp=(dd[pt].real/32)+1;
			if(refreshflag[pt]<tmp)		  //刷新数据,取较大高度值 存储显示  
			{
				for(LEDBuf[pt]=0xFF;tmp>1;tmp--)		  //tmp>1;不保留  最低位那一行常亮;{}一次也不执行；
				{
				 	LEDBuf[pt]<<=1;	
					
				}
				refreshflag[pt]=(dd[pt].real/32)+1;
			}
			else
			{
			 	if(refreshflag[pt]>1)refreshflag[pt]--;                            //顶端下落速度控制  改变值可以改变下降速度
			 	for(LEDBuf[pt]=0xFF,tmp=refreshflag[pt];tmp>1;tmp--)		  //tmp>1;不保留  最低位那一行常亮;{}一次也不执行；
				{
				 	LEDBuf[pt]<<=1;	
					
				}

			}
 	
		}

	} 
	else if(Menu==0)
	{
		//下落感频谱
		for(pt=2;pt<34;pt+=2)	
	    {       
			tmp=(dd[pt].real/32)+1;
			if(refreshflag[pt]<tmp)		  //刷新数据,取较大高度值 存储显示  
			{
				for(LEDBuf[pt]=0xFF;tmp>=1;tmp--)		  //tmp>1;不保留  最低位那一行常亮;{}一次也不执行；
				{
				 	LEDBuf[pt]<<=1;	
					
				}
				refreshflag[pt]=(dd[pt].real/32)+1;
			}
			else
			{
			 	if(refreshflag[pt]>1)refreshflag[pt]--;                            //顶端下落速度控制  改变值可以改变下降速度
			 	for(LEDBuf[pt]=0xFF,tmp=refreshflag[pt];tmp>=1;tmp--)		  //tmp>1;不保留  最低位那一行常亮;{}一次也不执行；
				{
				 	LEDBuf[pt]<<=1;	
					
				}

			}
			LEDBuf[pt]=~(LEDBuf[pt]);
 	
		}

	}


	
}  
#endif      















