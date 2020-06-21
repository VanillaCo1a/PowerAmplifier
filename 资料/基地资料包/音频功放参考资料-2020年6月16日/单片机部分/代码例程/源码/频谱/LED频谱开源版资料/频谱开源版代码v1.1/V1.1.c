#include "STC15F2K60S2.H"		 
#include "intrins.h"      
#include "math.h"
#include"data_define.h"
sbit Rest = P3^0;
#define LEDS0 P0
#define LEDS1 P2
#define Clear 0x00;
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks
#define tmp_Max    			    8			   //最大值（LED高度）
#define ADC_sensitivity	 		1
#define Process_sensitivity		4		 
uByte idata refreshflag[16];
uByte idata LEDBuf[16];	
uByte code LED_table[]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};
uByte code LEDS_tab[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uByte code Light_tab[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
struct compx
{
	float real;
	float imag;
};
struct compx ADC_buf[65];
data struct compx temp; 
code float iw[64]=
{
	 1.0000, 0     , 0.9952,-0.0980, 0.9808,-0.1951, 0.9569,-0.2903,
	 0.9239,-0.3827, 0.8819,-0.4714, 0.8315,-0.5556, 0.7730,-0.6344,
	 0.7071,-0.7071, 0.6344,-0.7730, 0.5556,-0.8315, 0.4714,-0.8819,
	 0.3827,-0.9239, 0.2903,-0.9569, 0.1951,-0.9808, 0.0980,-0.9952,
	 0.0   ,-1.0000,-0.0980,-0.9952,-0.1951,-0.9808,-0.2903, 0.9569,
	-0.3827,-0.9239,-0.4714,-0.8819,-0.5556,-0.8315,-0.6344,-0.7730,
	-0.7071,-0.7071,-0.7730,-0.6344,-0.8315,-0.5556,-0.8819,-0.4714,
	-0.9239,-0.3827,-0.9569,-0.2903,-0.9808,-0.1951,-0.9952,-0.0980
};

uByte xdata vv[16], vvd[16];
float xdata tempOUTADC_buf[16];

void Delay100us();
void Delay(uWord n);
void IOINIT(void);
void Spectrum_diplay();
void Timer1Init(void);
void InitADC();
void initfft(void);
void ee(struct compx b1,uByte data b2);
void fft(struct compx *xin,uByte data N);
void processfft(void);
uByte GetADCResult(uByte ch);
uWord mypow(uByte data nbottom,uByte data ntop);


void Main()
{  
	uByte data i;
	IOINIT();
	InitADC();
	Timer1Init();                   
	initfft();
	while(1)
	{
		if(Rest==0)IAP_CONTR=0x60;
	
		for(i=0;i<65;i++)
		{  
			ADC_buf[i].real=(GetADCResult(6)+GetADCResult(7))<<ADC_sensitivity	;	  
		}
			processfft(); 		
	
	
	} 
}

void IOINIT(void)
{							  		
	
	P1M1 = 0xc0; 
	P1M0 = 0x00;     
	P3M1 = 0x00;	
	P3M0 = 0xff;	      
	P1ASF =0xc0;							//将P16,P17的IO设置为模拟输入功能；	  
}

void Spectrum_diplay()
{					
  	uByte data i,j;

			P0M1=0x00;	   	//A组8*8初始化
			P0M0=0xff;
			P2M1=0xff;	   
			P2M0=0xff;
					
			for(i=0;i<8;i++)
			{
				LEDS1=LEDS_tab[i];
				for(j=0;j<8;j++)
				{
					LEDS0=LED_table[LEDBuf[i]]&Light_tab[j];
					Delay100us();
					LEDS0=Clear;
				}
			}
			LEDS0=Clear;
			LEDS1=Clear;

			P0M1=0xff;	   	//B组8*8初始化
			P0M0=0xff;
			P2M1=0x00;	   
			P2M0=0xff;

			for(i=0;i<8;i++)
			{
				LEDS0=LEDS_tab[i];
				for(j=0;j<8;j++)
				{
					LEDS1=LED_table[LEDBuf[i+8]]&Light_tab[j];
					Delay100us();
					LEDS1=Clear;
				}
			}

			LEDS1=Clear;
			LEDS0=Clear;
}
void LEDRefresh_INT() interrupt 3  using 1
{  
	Spectrum_diplay();
}  

void Timer1Init(void)		//@33.1776MHz
{
	EA=1;
	ET1 = 1;     //T/C1中断开
	AUXR &= 0xbf;		//定时器时钟1T模式
	TMOD = 0x00;		//设置定时器模式
	TL1 = 0x00;		//设置定时初值
	TH1 = 0x10;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
}
void InitADC()
{
    ADC_RES = 0;                   
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       
}

uByte GetADCResult(uByte ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));
    ADC_CONTR &= ~ADC_FLAG;         

    return (ADC_RES);                
}

void Delay(uWord n)
{
    uWord x;

    while (n--)
	{
        x = 5000;
        while (x--);
    }
}

void initfft(void)
{
	uByte i;
	for(i=0;i<16;i++){
		refreshflag[i]=0;
		vv[i]= 0;
		vvd[i]= 0;
	}
} 

void ee(struct compx b1,uByte data b2)
{ 
	temp.real=b1.real*iw[2*b2]-b1.imag*iw[2*b2+1];
	temp.imag=b1.real*iw[2*b2+1]+b1.imag*iw[2*b2]; 
}

uWord mypow(uByte data nbottom,uByte data ntop)
{
    uWord data result=1;
    uByte data t;    
    for(t=0;t<ntop;t++)result*=nbottom; 
    return result;
}

void fft(struct compx *xin,uByte data N)
{
	uByte data  fftnum,i,j,k,l,m,n,disbuff,dispos,dissec;
	data struct compx t;
	fftnum=N;                         
	for(m=1;(fftnum=fftnum/2)!=1;m++);
	for(k=0;k<=N-1;k++){               
		n=k;
		j=0; 
		for(i=m;i>0;i--){             
			j=j+((n%2)<<(i-1));
			n=n/2;
		} 
		if(k<j){t=xin[1+j];xin[1+j]=xin[1+k];xin[1+k]=t;}
	}  
	for(l=1;l<=m;l++){               
		disbuff=mypow(2,l);         
		dispos=disbuff/2;            
		for(j=1;j<=dispos;j++){
			for(i=j;i<N;i=i+disbuff){ 
				dissec=i+dispos;    
				ee(xin[dissec],(uWord)(j-1)*(uWord)N/disbuff);
				t=temp;
				xin[dissec].real=xin[i].real-t.real;
				xin[dissec].imag=xin[i].imag-t.imag;
				xin[i].real=xin[i].real+t.real;
				xin[i].imag=xin[i].imag+t.imag;
			}
		}
	}
}

void processfft(void)
{ 
    uByte data pt=0,tmp,i,p,p1,p2; 
    for(pt=0;pt<65;pt++){
        ADC_buf[pt].imag=0;                 
    }
    fft(ADC_buf,64);                      
	 
    for(pt=2,i=0;pt<34;pt+=2){                                      
        tempOUTADC_buf[i++] = sqrt(ADC_buf[pt].real*ADC_buf[pt].real+ADC_buf[pt].imag*ADC_buf[pt].imag);//取均方根 
    }


	for(i=0,pt=15;i<16;i++,pt--)
	{ 
	 tmp = ((uByte)tempOUTADC_buf[i]) >> Process_sensitivity;

if(tmp<=1)tmp=0;      
if(tmp>p)
{
p1=(tmp-p);
if(p1>3)
{
p2=(p1-3);
tmp=(tmp-p2);
p=tmp;
}
}
if(tmp<p)
{
p1=(p-tmp);
if(p1>3)
{
p2=(p1-3);
tmp=(tmp+p2);
p=tmp;
}
} 
		

		if(refreshflag[i] <= tmp)
		{		           
			refreshflag[i] = tmp;
		}else
		{
		 	if(refreshflag[i]>0)refreshflag[i]--;	
			tmp = refreshflag[i];
		}
		if(tmp>tmp_Max)tmp = tmp_Max; 							
	
			LEDBuf[i] = tmp;
	}
}

void Delay100us()		//@33.1776MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 4;
	j = 54;
	do
	{
		while (--j);
	} while (--i);

}



