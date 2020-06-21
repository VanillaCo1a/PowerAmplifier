//电脑音量推荐设置为40%，手机及MP4等要高一些
#include <STC12C5A60S2.h>
#include<intrins.h>

/********************************************************************/
#define SAMPLE_NUM 128
#define LOG 6
#define TIME 2048	   //中断
#define FFT_OUT_MIN 0
#define FFT_OUT_MAX	7	
#define OFF L1=L2=L3=L4=L5=L6=L7=L8=L9=L10=L11=L12=L13=L14=L15=L16=L17=L18=L19=L20=L21=L22=L23=L24=1;
#define ADC_POWER   0x80            //ADC power control bit 
#define ADC_FLAG    0x10            //ADC complete flag 
#define ADC_START   0x08            //ADC start control bit 
//#define ADC_SPEEDLL 0x00            //420 clocks 
//#define ADC_SPEEDL  0x20            //280 clocks 
#define ADC_SPEEDH  0x40            //140 clocks 
//#define ADC_SPEEDHH 0x60            //70 clocks 

/********************************************************************/
//采样存储序列表
unsigned char code BRTable[SAMPLE_NUM] ={0, 64, 32, 96, 16, 80, 48, 112,
8, 72, 40, 104, 24, 88, 56, 120,
4, 68, 36, 100, 20, 84, 52, 116,
12, 76, 44, 108, 28, 92, 60, 124,
2, 66, 34, 98, 18, 82, 50, 114,
10, 74, 42, 106, 26, 90, 58, 122,
6, 70, 38, 102, 22, 86, 54, 118,
14, 78, 46, 110, 30, 94, 62, 126,
1, 65, 33, 97, 17, 81, 49, 113,
9, 73, 41, 105, 25, 89, 57, 121,
5, 69, 37, 101, 21, 85, 53, 117,
13, 77, 45, 109, 29, 93, 61, 125,
3, 67, 35, 99, 19, 83, 51, 115,
11, 75, 43, 107, 27, 91, 59, 123,
7, 71, 39, 103, 23, 87, 55, 119,
15, 79, 47, 111, 31, 95, 63, 127};
char code sin_tabb[SAMPLE_NUM] = {0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 59, 65, 70, 75, 80, 85, 89, 94, 98, 102, 

105, 108, 112, 114, 117, 119, 121, 123, 124, 125, 126, 126, 126, 126, 126, 125, 124, 123, 121, 119, 117, 114, 112, 

108, 105, 102, 98, 94, 89, 85, 80, 75, 70, 65, 59, 54, 48, 42, 36, 30, 24, 18, 12, 6, 0, -6, -12, -18, -24, -30, 

-36, -42, -48, -54, -59, -65, -70, -75, -80, -85, -89, -94, -98, -102, -105, -108, -112, -114, -117, -119, -121, 

-123, -124, -125, -126, -126, -126, -126, -126, -125, -124, -123, -121, -119, -117, -114, -112, -108, -105, -102, 

-98, -94, -89, -85, -80, -75, -70, -65, -59, -54, -48, -42, -36, -30, -24, -18, -12, -6};                         
char code cos_tabb[SAMPLE_NUM] = {127, 126, 126, 125, 124, 123, 121, 119, 117, 114, 112, 108, 105, 102, 98, 94, 

89, 85, 80, 75, 70, 65, 59, 54, 48, 42, 36, 30, 24, 18, 12, 6, 0, -6, -12, -18, -24, -30, -36, -42, -48, -54, -59, 

-65, -70, -75, -80, -85, -89, -94, -98, -102, -105, -108, -112, -114, -117, -119, -121, -123, -124, -125, -126, -

126, -126, -126, -126, -125, -124, -123, -121, -119, -117, -114, -112, -108, -105, -102, -98, -94, -89, -85, -80, 

-75, -70, -65, -59, -54, -48, -42, -36, -30, -24, -18, -12, -6, 0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 59, 65, 70, 

75, 80, 85, 89, 94, 98, 102, 105, 108, 112, 114, 117, 119, 121, 123, 124, 125, 126, 126};
xdata unsigned char result[128];
xdata unsigned char temp[128];
xdata unsigned char num[128];
unsigned char anum,timernum,timernum2,lednum3,Ltime,t;//用于分离
unsigned char lednum[]={0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};//0-7的显示数组  P2组控制
int xdata FftReal[SAMPLE_NUM];
int xdata FftImage[SAMPLE_NUM];

unsigned char code musicdisplay[]={
	0x00,0x00,
	0xFE,0x40,0x30,0x40,0xFE,0x00, // -M-
	0xFC,0x02,0x02,0x02,0xFC,0x00, // -U-
	0x64,0x92,0x92,0x92,0x4C,0x00, // -S-
	0x00,0x82,0xFE,0x82,0x00,0x00, // -I-
	0x7C,0x82,0x82,0x82,0x44,0x00, // -C-
	0x00,0x00,0x00,
	0xFE,0x82,0x82,0x82,0x7C,0x00, // -D-
	0x00,0x82,0xFE,0x82,0x00,0x00, // -I-
	0x64,0x92,0x92,0x92,0x4C,0x00, // -S-
	0xFE,0x90,0x90,0x90,0x60,0x00, // -P-
	0xFE,0x02,0x02,0x02,0x02,0x00, // -L-
	0x3E,0x48,0x88,0x48,0x3E,0x00, // -A-
	0xC0,0x20,0x1E,0x20,0xC0,0x00, // -Y-
	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00};
/********************************************************************/
#define LED P2
#define pwm 9

sbit L24=P3^2;
sbit L23=P3^1;
sbit L22=P3^0;
sbit L21=P4^7;
sbit L20=P1^7;
sbit L19=P1^6;
sbit L18=P1^5;
sbit L17=P1^4;
sbit L16=P3^3;
sbit L15=P3^4;
sbit L14=P3^5;
sbit L13=P3^6;
sbit L12=P3^7;
sbit L11=P0^2;
sbit L10=P0^1;
sbit L9=P0^0;
sbit L8=P0^3;
sbit L7=P0^4;
sbit L6=P0^5;
sbit L5=P0^6;
sbit L4=P0^7;
sbit L3=P4^6;
sbit L2=P4^5;
sbit L1=P4^4;
/********************************************************************/
void delay(unsigned char a)
{ 
	unsigned int i;
	while(--a)
		for(i=0;i<50;i++);  				   
}
/********************************************************************/
void off()
{ 
	LED = 0x00;
	OFF
//	delay(10-pwm); 
}
/********************************************************************/
void display(unsigned char i,unsigned char dat)
{
	P2=dat;
	switch(i)
	{
		case 1:L1=0;break;
		case 2:L2=0;break;
		case 3:L3=0;break;
		case 4:L4=0;break;
		case 5:L5=0;break;
		case 6:L6=0;break;
		case 7:L7=0;break;
		case 8:L8=0;break;
		case 9:L9=0;break;
		case 10:L10=0;break;
		case 11:L11=0;break;
		case 12:L12=0;break;
		case 13:L13=0;break;
		case 14:L14=0;break;
		case 15:L15=0;break;
		case 16:L16=0;break;
		case 17:L17=0;break;
		case 18:L18=0;break;
		case 19:L19=0;break;
		case 20:L20=0;break;
		case 21:L21=0;break;
		case 22:L22=0;break;
		case 23:L23=0;break;
		case 24:L24=0;break;
	}
	delay(pwm);
	off();
}
/********************************************************************/
void show_musicdisplay()
{
	unsigned char a,b,c;
	for(c=0;c<80;c++)
		for(b=12;b>0;b--)
	   		for(a=1;a<25;a++)
				display(a,musicdisplay[a-1+c]);
}
/********************************************************************/             
void FFT_process()			  //下落迟滞
{
	unsigned char i;
	for(i=0;i<24;i++)
	{	
		if(result[i] < temp[i])
		{
			num[i]++;
			if(num[i] == 1)
			{
				if(temp[0]==0&&temp[1]==0&&temp[2]==0&&temp[3]==0&&temp[4]==0&&temp[5]==0&&temp[6]==0&&temp[7]==0&&temp[8]==0&&temp[9]==0&&temp[10]==0&&temp[11]==0&&temp[12]==0&&temp[13]==0&&temp[14]==0&&temp[15]==0&&temp[16]==0&&temp[17]==0&&temp[18]==0&&temp[19]==0&&temp[20]==0&&temp[21]==0&&temp[22]==0&&temp[23]==0&&temp[24]==0);
				else
				{
					result[i] = --temp[i];
					num[i] = 0;
				}
			}
		}
		else
			num[i] = 0;		
	}
}
/********************************************************************/
void disp()
{
//	unsigned char i,j,buff;
	timernum++;
	if(timernum == 25) 
		timernum = 1;
   	OFF
	FFT_process();
	/*for(i=0;i<16;i++)
		for(j=i+1;j<16;j++)
			if(result[j] > result[i])
			{
				buff = result[i];
				result[i] = result[j];
				result[j] = buff;
			}*/					  
	switch(timernum)
	{
		case 1:anum = result[0];L1=0;break;
		case 2:anum = result[1];L2=0;break;
		case 3:anum = result[2];L3=0;break;
		case 4:anum = result[3];L4=0;break;
		case 5:anum = result[4];L5=0;break;
		case 6:anum = result[5];L6=0;break;
		case 7:anum = result[6];L7=0;break;
		case 8:anum = result[7];L8=0;break;
		case 9:anum = result[8];L9=0;break;
		case 10:anum = result[9];L10=0;break;
		case 11:anum = result[10];L11=0;break;
		case 12:anum = result[11];L12=0;break;
		case 13:anum = result[12];L13=0;break;
		case 14:anum = result[13];L14=0;break;
		case 15:anum = result[14];L15=0;break;
		case 16:anum = result[15];L16=0;break;
		case 17:anum = result[16];L17=0;break;
		case 18:anum = result[17];L18=0;break;
		case 19:anum = result[18];L19=0;break;
		case 20:anum = result[19];L20=0;break;
		case 21:anum = result[20];L21=0;break;
		case 22:anum = result[21];L22=0;break;
		case 23:anum = result[22];L23=0;break;
		case 24:anum = result[23];L24=0;break;
	}
	if(anum >= 8)
		anum = FFT_OUT_MAX;
	LED = lednum[anum];
}
/********************************************************************/
void ADC_init()
{
	P1ASF = 0x01;                   //Open 8 channels ADC function 
    ADC_RES = 0;                    //Clear previous result 
	ADC_RESL= 0;
    ADC_CONTR = ADC_POWER | ADC_SPEEDH; 
    delay(5);                       //ADC power-on and delay      
}
/********************************************************************/
float ADC_read()
{
//delay(10);	
    ADC_CONTR = ADC_POWER | ADC_SPEEDH  | ADC_START; 
    _nop_();                        //至少要延时4个时钟周期
    _nop_(); 
    _nop_(); 
    _nop_();
	_nop_(); 
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag 
    ADC_CONTR &= ~ADC_FLAG;         //关闭ADC 
    return (ADC_RES*4+ADC_RESL);                 //Return ADC result
}
/********************************************************************/
short sqrt_16(unsigned long M)   
{
    unsigned int N,i;
    unsigned long tmp,ttp; 
    if( M == 0 )             
        return 0;   
    N = 0;  
    tmp = (M >> 30);        
    M <<= 2;
    if( tmp > 1 )            
    {
        N++;               
        tmp -= N;
    }   
    for( i=15; i>0; i-- )   
    {
        N <<= 1;                  
        tmp <<= 2;
        tmp += (M >> 30);          
        ttp = N;
        ttp = (ttp<<1)+1;        
        M <<= 2;
        if( tmp >= ttp )    
        {
            tmp -= ttp;
            N ++;
        }       
    }   
    return N;
}
/********************************************************************/
void FFT()
{
    register unsigned char i,bb,j,k,p;
    register short TR,TI,temp;
    unsigned long ulReal,ulImage;                             
	unsigned char max;
                                                                   
    for(i=0;i<SAMPLE_NUM;i++)	 
    {
		FftReal[BRTable[i]] = ADC_read();
        FftImage[i] = 0;
    } 	

    for(i=1;i<=LOG;i++)                         
    { 
        bb=1;
        bb <<= (i-1);                                      
        for(j=0;j<=bb-1;j++)                            
        { 
            p=1;
            p <<= (LOG-i);           
            p = p*j;
            for(k=j;k<SAMPLE_NUM;k=k+2*bb)               
            { 
                TR=FftReal[k];TI=FftImage[k];temp=FftReal[k+bb];
                FftReal[k]=FftReal[k]+((FftReal[k+bb]*cos_tabb[p])>>7)+((FftImage[k+bb]*sin_tabb[p])>>7);
                FftImage[k]=FftImage[k] - ((FftReal[k+bb]*sin_tabb[p])>>7)+((FftImage[k+bb]*cos_tabb[p])>>7);
                FftReal[k+bb]=TR-((FftReal[k+bb]*cos_tabb[p])>>7)-((FftImage[k+bb]*sin_tabb[p])>>7);
                FftImage[k+bb]=TI+((temp*sin_tabb[p])>>7)-((FftImage[k+bb]*cos_tabb[p])>>7); 
                
                FftReal[k] >>= 1;             
                FftImage[k] >>= 1; 
                FftReal[k+bb] >>= 1;                 
                FftImage[k+bb] >>= 1;                                                                               
            }  
        }
    }

   for(i=0;i<24;i++)
    {  
        ulReal = FftReal[i+1];
        ulReal *= ulReal;
        ulImage = FftImage[i+1];
        ulImage *= ulImage;       
        result[i] = sqrt_16(ulReal+ulImage);  		                      	                  
                    
    }
/*	for(i=0;i<17;i++)
    {
		while(result[i] > FFT_OUT_MAX)
		{
		for(i=0;i<17;i++)
	     {	 		
			result[i] =result[i] -1;      
	 	 } 
	    }
	}	 */
	while(result[i] == FFT_OUT_MIN)
		{
		for(i=0;i<24;i++)
	     {	 		
			result[i] =result[i] +1;      
	 	 } 
	    }
	for(i=0;i<24;i++)
	{
		if(result[i] > FFT_OUT_MAX)
		{
			result[i] = FFT_OUT_MAX;      
			if(result[i] > max)
                max = result[i];
		} 
	}
	//局部增益	*/	/*			
		/*if(max >= 4)		
		for(i=1;i<24;i++)
			if(result[i] >= 2)
				result[i]+=1;	  */
								 
}
/********************************************************************/             
void init()
{
	P2M0=0XFF;
	P2M1=0X00;
	P3M0=0XFF;
	P3M1=0X00;
	P1M0=0XFE;
	P1M1=0X01;
	P4SW=0x70;

	ADC_init();
	//AUXR |= 0x80;		//定时器时钟1T模式
	TMOD=0x01;
	TH0=(65535-TIME)/256;
	TL0=(65535-TIME)%256;
    EA=1;
	ET0=1;		
	show_musicdisplay();  
	TR0=1;
}
/********************************************************************/
void main()
{
	init();
    while(1)	  
        FFT();
}
/********************************************************************/
void timer0() interrupt 1
{
	unsigned char i;
	t++;
	if(t == 24)
	{
		for(i=0;i<24;i++)
			temp[i] = result[i];
		t = 0;
	}				   
	disp();
	TH0=(65535-TIME)/256;	
	TL0=(65535-TIME)%256;
}
/********************************************************************/