
#line 1 "src\prj.c" /0
  
#line 1 "src\STC12C5A.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  PSW        =   0xd0;        
 
 
 
 sbit CY         =   PSW^7;       
 sbit AC         =   PSW^6;       
 sbit F0         =   PSW^5;       
 sbit RS1        =   PSW^4;       
 sbit RS0        =   PSW^3;       
 sbit OV         =   PSW^2;       
 sbit P          =   PSW^0;       
 
 
 
 sfr  ACC        =   0xe0;        
 
 
 sbit ACC7       =   ACC^7;       
 sbit ACC6       =   ACC^6;       
 sbit ACC5       =   ACC^5;       
 sbit ACC4       =   ACC^4;       
 sbit ACC3       =   ACC^3;       
 sbit ACC2       =   ACC^2;       
 sbit ACC1       =   ACC^1;       
 sbit ACC0       =   ACC^0;       
 
 
 
 sfr  B          =   0xf0;        
 
 
 
 
 sfr  SP         =   0x81;        
 
 
 
 
 sfr  DPL        =   0x82;        
 
 
 
 
 sfr  DPH        =   0x83;        
 
 
 
 
 sfr  PCON       =   0x87;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  WAKE_CLKO  =   0x8f;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  CLK_DIV    =   0x97;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  BUS_SPEED  =   0xa1;        
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  WDT_CONTR  =   0xc1;        
 
 
 
 
 
 
 
 
 
 
 sfr  AUXR       =   0x8e;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  AUXR1      =   0xa2;        
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  P0         =   0x80;        
 
 
 
 sbit P07        =   P0^7;        
 sbit P06        =   P0^6;        
 sbit P05        =   P0^5;        
 sbit P04        =   P0^4;        
 sbit P03        =   P0^3;        
 sbit P02        =   P0^2;        
 sbit P01        =   P0^1;        
 sbit P00        =   P0^0;        
 
 
 
 sfr  P1         =   0x90;        
 
 
 
 sbit P17        =   P1^7;        
 sbit P16        =   P1^6;        
 sbit P15        =   P1^5;        
 sbit P14        =   P1^4;        
 sbit P13        =   P1^3;        
 sbit P12        =   P1^2;        
 sbit P11        =   P1^1;        
 sbit P10        =   P1^0;        
 
 sbit ADCIN7     =   P1^7;        
 sbit ADCIN6     =   P1^6;        
 sbit ADCIN5     =   P1^5;        
 sbit ADCIN4     =   P1^4;        
 sbit ADCIN3     =   P1^3;        
 sbit ADCIN2     =   P1^2;        
 sbit ADCIN1     =   P1^1;        
 sbit ADCIN0     =   P1^0;        
 
 sbit SPISCLK    =   P1^7;        
 sbit SPIMISO    =   P1^6;        
 sbit SPIMOSI    =   P1^5;        
 sbit SPISS      =   P1^4;        
 
 sbit CEX1       =   P1^4;        
 sbit CEX0       =   P1^3;        
 sbit ECI        =   P1^2;        
 
 sbit TXD2       =   P1^3;        
 sbit RXD2       =   P1^2;        
 
 sbit BRTCLKO    =   P1^0;        
 
 
 
 sfr  P2         =   0xa0;        
 
 
 
 sbit P27        =   P2^7;        
 sbit P26        =   P2^6;        
 sbit P25        =   P2^5;        
 sbit P24        =   P2^4;        
 sbit P23        =   P2^3;        
 sbit P22        =   P2^2;        
 sbit P21        =   P2^1;        
 sbit P20        =   P2^0;        
 
 
 
 sfr  P3         =   0xb0;        
 
 
 
 sbit P37        =   P3^7;        
 sbit P36        =   P3^6;        
 sbit P35        =   P3^5;        
 sbit P34        =   P3^4;        
 sbit P33        =   P3^3;        
 sbit P32        =   P3^2;        
 sbit P31        =   P3^1;        
 sbit P30        =   P3^0;        
 
 sbit RXD        =   P3^0;        
 sbit TXD        =   P3^1;        
 sbit INT0       =   P3^2;        
 sbit INT1       =   P3^3;        
 sbit T0         =   P3^4;        
 sbit T1         =   P3^5;        
 sbit WR         =   P3^6;        
 sbit RD         =   P3^7;        
 
 sbit T0CLKO     =   P3^4;        
 sbit T1CLKO     =   P3^5;        
 
 
 
 sfr  P4         =   0xc0;        
 
 
 
 sbit P47        =   P4^7;        
 sbit P46        =   P4^6;        
 sbit P45        =   P4^5;        
 sbit P44        =   P4^4;        
 sbit P43        =   P4^3;        
 sbit P42        =   P4^2;        
 sbit P41        =   P4^1;        
 sbit P40        =   P4^0;        
 
 sbit RST        =   P4^7;        
 sbit EX_LVD     =   P4^6;        
 
 sbit P4SPISCLK  =   P4^3;        
 sbit P4SPIMISO  =   P4^2;        
 sbit P4SPIMOSI  =   P4^1;        
 sbit P4SPISS    =   P4^0;        
 
 sbit P4CEX1     =   P4^3;        
 sbit P4CEX0     =   P4^2;        
 sbit P4ECI      =   P4^1;        
 
 sbit P4TXD2     =   P4^3;        
 sbit P4RXD2     =   P4^2;        
 
 
 
 sfr  P5         =   0xc8;        
 
 
 
 sbit P53        =   P5^3;        
 sbit P52        =   P5^2;        
 sbit P51        =   P5^1;        
 sbit P50        =   P5^0;        
 
 
 
 sfr  P1M1       =   0x91;        
 
 
 
 
 sfr  P1M0       =   0x92;        
 
 
 
 
 sfr  P0M1       =   0x93;        
 
 
 
 
 sfr  P0M0       =   0x94;        
 
 
 
 
 sfr  P2M1       =   0x95;        
 
 
 
 
 sfr  P2M0       =   0x96;        
 
 
 
 
 sfr  P3M1       =   0xb1;        
 
 
 
 
 sfr  P3M0       =   0xb2;        
 
 
 
 
 sfr  P4M1       =   0xb3;        
 
 
 
 
 sfr  P4M0       =   0xb4;        
 
 
 
 
 sfr  P5M1       =   0xc9;        
 
 
 
 
 sfr  P5M0       =   0xca;        
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  P1ASF      =   0x9d;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  P4SW       =   0xbb;        
 
 
 
 
 
 
 
 
 
 sfr  IE         =   0xa8;        
 
 
 
 sbit EA         =   IE^7;        
 sbit ELVD       =   IE^6;        
 sbit EADC       =   IE^5;        
 sbit ES         =   IE^4;        
 sbit ET1        =   IE^3;        
 sbit EX1        =   IE^2;        
 sbit ET0        =   IE^1;        
 sbit EX0        =   IE^0;        
 
 
 
 sfr  IE2        =   0xaf;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  IP2        =   0xb5;        
 
 
 
 
 
 
 
 
 sfr  IP2H       =   0xb6;        
 
 
 
 
 
 
 
 
 sfr  IPH        =   0xb7;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  IP         =   0xb8;        
 
 
 
 sbit PPCA       =   IP^7;        
 sbit PLVD       =   IP^6;        
 sbit PADC       =   IP^5;        
 sbit PS         =   IP^4;        
 sbit PT1        =   IP^3;        
 sbit PX1        =   IP^2;        
 sbit PT0        =   IP^1;        
 sbit PX0        =   IP^0;        
 
 
 
 sfr  TCON       =   0x88;        
 
 
 
 sbit TF1        = TCON^7;        
 sbit TR1        = TCON^6;        
 sbit TF0        = TCON^5;        
 sbit TR0        = TCON^4;        
 sbit IE1        = TCON^3;        
 sbit IT1        = TCON^2;        
 sbit IE0        = TCON^1;        
 sbit IT0        = TCON^0;        
 
 
 
 sfr  TMOD       =   0x89;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  TL0        = 0x8a;          
 
 
 
 
 sfr  TL1        = 0x8b;          
 
 
 
 
 sfr  TH0        = 0x8c;          
 
 
 
 
 sfr  TH1        = 0x8d;          
 
 
 
 
 sfr  SCON       =   0x98;        
 
 
 
 sbit FE         =   SCON^7;      
 sbit SM0        =   SCON^7;      
 sbit SM1        =   SCON^6;      
 sbit SM2        =   SCON^5;      
 sbit REN        =   SCON^4;      
 sbit TB8        =   SCON^3;      
 sbit RB8        =   SCON^2;      
 sbit TI         =   SCON^1;      
 sbit RI         =   SCON^0;      
 
 
 
 sfr  SBUF       =   0x99;        
 
 
 
 
 sfr  S2CON      =   0x9a;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  S2BUF      =   0x9b;        
 
 
 
 
 sfr  SADDR      =   0xa9;        
 
 
 
 
 sfr  SADEN      =   0xb9;        
 
 
 
 
 sfr  BRT        =   0x9c;        
 
 
 
 
 sfr  ADC_CONTR  =   0xbc;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  ADC_RES    =   0xbd;        
 
 
 
 
 sfr  ADC_RESL   =   0xbe;        
 
 
 
 
 sfr  IAP_DATA   =   0xc2;        
 
 
 
 
 sfr  IAP_ADDRH  =   0xc3;        
 
 
 
 
 sfr  IAP_ADDRL  =   0xc4;        
 
 
 
 
 sfr  IAP_CMD    =   0xc5;        
 
 
 
 
 
 
 
 
 
 sfr  IAP_TRIG   =   0xc6;        
 
 
 
 
 
 
 
 sfr  IAP_CONTR  =   0xc7;        
 
 
 
 
 
 
 
 
 
 
 sfr  SPSTAT     =   0xcd;        
 
 
 
 
 
 
 
 
 sfr  SPCTL      =   0xce;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  SPDAT      =   0xcf;        
 
 
 
 
 sfr  CCON       =   0xd8;        
 
 
 
 sbit CF         =   CCON^7;      
 sbit CR         =   CCON^6;      
 sbit CCF1       =   CCON^1;      
 sbit CCF0       =   CCON^0;      
 
 
 
 sfr  CMOD       =   0xd9;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  CCAPM0     =   0xda;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  CCAPM1     =   0xdb;        
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr  CL         =   0xe9;        
 
 
 
 
 sfr  CH         =   0xf9;        
 
 
 
 
 sfr  CCAP0L     =   0xea;        
 
 
 
 
 sfr  CCAP1L     =   0xeb;        
 
 
 
 
 sfr  CCAP0H     =   0xfa;        
 
 
 
 
 sfr  CCAP1H     =   0xfb;        
 
 
 
 
 sfr  PCA_PWM0   =   0xf2;        
 
 
 
 
 
 sfr  PCA_PWM1   =   0xf3;        
 
 
 
 
 
 
#line 1 "src\prj.c" /0
 
 
  
#line 1 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /0






 
 
 
 
 
 #pragma SAVE
 
 
#line 15 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /1
 
 
 
#line 18 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /0
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_(float);
 
#line 29 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /1
 
 
 
#line 32 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /0
 
 extern void          _push_    (unsigned char _sfr);
 extern void          _pop_     (unsigned char _sfr);
 
 
 #pragma RESTORE
 
 
 
#line 3 "src\prj.c" /0
 
  
#line 1 "D:\Program Files (x86)\keil\C51\Inc\math.h" /0






 
 
 
 
 
 
#line 13 "D:\Program Files (x86)\keil\C51\Inc\math.h" /1
 
 
 
 
 
 
#line 19 "D:\Program Files (x86)\keil\C51\Inc\math.h" /0
 
 #pragma SAVE
 #pragma REGPARMS
 extern char  cabs  (char  val);
 
 extern int    abs  (int   val);
 
 extern long  labs  (long  val);
 extern float fabs  (float val);
 extern float sqrt  (float val);
 extern float exp   (float val);
 extern float log   (float val);
 extern float log10 (float val);
 extern float sin   (float val);
 extern float cos   (float val);
 extern float tan   (float val);
 extern float asin  (float val);
 extern float acos  (float val);
 extern float atan  (float val);
 extern float sinh  (float val);
 extern float cosh  (float val);
 extern float tanh  (float val);
 extern float atan2 (float y, float x);
 
 extern float ceil  (float val);
 extern float floor (float val);
 extern float modf  (float val, float *n);
 extern float fmod  (float x, float y);
 extern float pow   (float x, float y);
 
 #pragma RESTORE
 
 
#line 4 "src\prj.c" /0
 
 
  
#line 1 "src\Define.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 6 "src\prj.c" /0
 
 
 
 
  unsigned char data DelayTime=9;	   
  unsigned char data INTTime=0x40;   
  unsigned char data gain=6;
  unsigned char data Menu=2;
  unsigned char idata refreshflag[40];
  unsigned char  data LEDBuf[35];	   
  unsigned long int  data TouchKey=0;
  unsigned char data CBeep=0;
 
 
 
 void Delays(unsigned int t)
 {  
  unsigned int j;
 while(--t)
 for(j=0;j<5;j++);    
 }
 void Delaysms(unsigned int t)
 {  
  unsigned int j;
 while(--t)
 for(j=0;j<15;j++);    
 }
 
 
 
  
#line 1 "src\ADC.c" /0
 
 
 
 
 
 
  
#line 1 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /0






 
 
 
#line 10 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /1
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 40 "D:\Program Files (x86)\keil\C51\Inc\intrins.h" /0
 
#line 7 "src\ADC.c" /0
 
 
 
 
 
 typedef unsigned char BYTE;
 typedef unsigned int WORD;
 
 
 
 
 sfr ADC_LOW2    =   0xBE;            
 
 
 
 
 
 
 
 
 
 
 
 void InitUart();
 void InitADC();
 void SendData(BYTE dat);
 BYTE GetADCResult(BYTE ch);
 void Delay(WORD n);
 void ShowResult(BYTE ch);
 
 


 
 void ShowResult(BYTE ch)
 {
 SendData(ch);                    
 SendData(GetADCResult(ch));      
 
 
 
 }
 


 
 BYTE GetADCResult(BYTE ch)
 {
 ADC_CONTR = 0x80 | 0x00 | ch | 0x08;
 _nop_();                         
 _nop_();
 _nop_();
 _nop_();
 while (!(ADC_CONTR & 0x10)); 
 ADC_CONTR &= ~0x10;          
 
 return ADC_RES;                  
 }
 


 
 void InitUart()
 {
 SCON = 0x5a;                     
 TMOD = 0x20;                     
 TH1 = TL1 = -(18432000L/12/32/9600);  
 TR1 = 1;                         
 }
 


 
 void InitADC()
 {
 
 ADC_RES = 0;                     
 ADC_CONTR = 0x80 | 0x00;
 Delay(2);                        
 }
 




 
 void SendData(BYTE dat)
 {
 while (!TI);                     
 TI = 0;                          
 SBUF = dat;                      
 }
 


 
 void Delay(WORD n)
 {
 WORD x;
 
 while (n--)
 {
 x = 5000;
 while (x--);
 }
 }
 
#line 36 "src\prj.c" /0
 
  
#line 1 "src\Font.c" /0
 
 
 
 
 
  unsigned char code FontLib[156+35]=
 {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	
 
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x50,0x50,0x00,0x3E,
 0x22,0x3E,0x00,0x3E,0x10,0x20,0x00,0x3E,0x2A,0x3A,0x00,0x3C,0x02,0x3C,0x00,0x3E,
 0x2A,0x3A,0x00,0x3E,0x10,0x20,0x00,0x40,0x7E,0x40,0x00,0x3E,0x22,0x3E,0x00,0x3F,
 0x24,0x3C,0x00,0x00,0x00,0x00,0x7E,0x42,0x00,0x1C,0x10,0x1C,0x10,0x1C,0x00,0x5C,
 0x00,0x1C,0x10,0x1C,0x00,0x5C,0x00,0x00,0x3E,0x28,0x28,0x00,0x3E,0x28,0x28,0x00,
 0x20,0x3E,0x20,0x00,0x42,0x7E,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,
 0x1C,0x1C,0x5D,0x7F,0x3E,0x1C,0x08,0x00,0x00,0x00,0x08,0x1C,0x3E,0x7F,0x5D,0x1C,
 0x1C,0x1C,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x10,0x20,0x7F,0xFF,0x7F,0x20,0x10,0x00,
 0x00,0x00,0x08,0x04,0xFE,0xFF,0xFE,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
 
 
 
 };
 
 
 void FontDisp()
 {
  unsigned char data i,ii,count;
 
 for(ii=0;ii<156;ii++)
 {
 for(i=2,count=0;i<35;i+=2,count++)	  
 {
 LEDBuf[i]=FontLib[count+ii];	  
 }
 Delaysms(9000);
 }       
 
 }
#line 37 "src\prj.c" /0
 
  
#line 1 "src\fft.h" /0
 
 
 
 struct compx
 {
 float real;
 float imag;
 };
 struct compx dd[65];  
 data struct compx temp;  
 
 code float iw[64]=
 {
 1.000,0,0.9952,-0.0980,0.9808,-0.1951,0.9569,-0.2903,0.9239,-0.3827,0.8819,-0.4714,0.8315,-0.5556,
 0.7730,-0.6344,0.7071,-0.7071,0.6344,-0.7730,0.5556,-0.8315,0.4714,-0.8819,0.3827,-0.9239,0.2903,-0.9569,
 0.1951,-0.9808,0.0980,-0.9952,0.0,-1.0000,-0.0980,-0.9952,-0.1951,-0.9808,-0.2903,0.9569,-0.3827,-0.9239,
 -0.4714,-0.8819,-0.5556,-0.8315,-0.6344,-0.7730,-0.7071,-0.7071,-0.7730,-0.6344,-0.8315,-0.5556,-0.8819,-0.4714,
 -0.9239,-0.3827,-0.9569,-0.2903,-0.9808,-0.1951,-0.9952,-0.0980
 };
 
 
 
 void ee(struct compx b1,unsigned char data b2)
 { 
 temp.real=b1.real*iw[2*b2]-b1.imag*iw[2*b2+1];
 temp.imag=b1.real*iw[2*b2+1]+b1.imag*iw[2*b2]; 
 } 
 
  unsigned int mypow(unsigned char data nbottom,unsigned char data ntop)
 {
  unsigned int data result=1;
  unsigned char data t;    
 for(t=0;t<ntop;t++)result*=nbottom; 
 return result;
 }
 
 void fft(struct compx *xin,unsigned char data N)
 {
  unsigned char data  fftnum,i,j,k,l,m,n,disbuff,dispos,dissec;
 data struct compx t;
 fftnum=N;                          
 for(m=1;(fftnum=fftnum/2)!=1;m++); 
 for(k=0;k<=N-1;k++)                
 {
 n=k;
 j=0; 
 for(i=m;i>0;i--)              
 {
 j=j+((n%2)<<(i-1));
 n=n/2;
 } 
 if(k<j){t=xin[1+j];xin[1+j]=xin[1+k];xin[1+k]=t;} 
 }  
 for(l=1;l<=m;l++)                 
 {
 disbuff=mypow(2,l);           
 dispos=disbuff/2;             
 for(j=1;j<=dispos;j++)
 for(i=j;i<N;i=i+disbuff)  
 {
 dissec=i+dispos;      
 ee(xin[dissec],(unsigned int)(j-1)*(unsigned int)N/disbuff); 
 t=temp;
 xin[dissec].real=xin[i].real-t.real;
 xin[dissec].imag=xin[i].imag-t.imag;
 xin[i].real=xin[i].real+t.real;
 xin[i].imag=xin[i].imag+t.imag;
 }
 }
 } 
 
 
 
 
 void processfft(void)
 { 
  unsigned char data pt=0,tmp; 
 
 for(pt=1;pt<65;pt++)
 {
 dd[pt].imag=0;                 
 }
 fft(dd,64);                        
 
 for(pt=1;pt<65;pt++)
 {                                      
 dd[pt].real=sqrt(dd[pt].real*dd[pt].real+dd[pt].imag*dd[pt].imag); 
 }
 
 if(Menu==1)
 {
 for(pt=2;pt<34;pt+=2)	 
 {       
 for(tmp=(dd[pt].real/32)+1,LEDBuf[pt]=0xFF;tmp>=1;tmp--) 
 {
 LEDBuf[pt]<<=1;			
 }
 
 LEDBuf[pt]=~(LEDBuf[pt]);
 
 }
 }
 else if(Menu==2)
 {
 
 
 for(pt=2;pt<34;pt+=2)	
 {       
 tmp=(dd[pt].real/32)+1;
 if(refreshflag[pt]<tmp)		             
 {
 for(LEDBuf[pt]=0xFF;tmp>1;tmp--)	 
 {
 LEDBuf[pt]<<=1;	
 
 }
 refreshflag[pt]=(dd[pt].real/32)+1;
 }
 else
 {
 if(refreshflag[pt]>1)refreshflag[pt]--;                 
 for(LEDBuf[pt]=0xFF,tmp=refreshflag[pt];tmp>1;tmp--)    
 {
 LEDBuf[pt]<<=1;						
 }
 }
 }
 } 
 else if(Menu==0)
 {
 
 
 for(pt=2;pt<34;pt+=2)	 
 {       
 tmp=(dd[pt].real/32)+1;
 if(refreshflag[pt]<tmp)		           
 {
 for(LEDBuf[pt]=0xFF;tmp>=1;tmp--) 
 {
 LEDBuf[pt]<<=1;	
 
 }
 refreshflag[pt]=(dd[pt].real/32)+1;
 
 }
 else
 {
 if(refreshflag[pt]>1)refreshflag[pt]--;                         
 for(LEDBuf[pt]=0xFF,tmp=refreshflag[pt];tmp>=1;tmp--)	
 {
 LEDBuf[pt]<<=1;					
 }
 }
 LEDBuf[pt]=~(LEDBuf[pt]);
 }
 }
 
 }  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 38 "src\prj.c" /0
 
 
 
 
 void PWM_init (void)	   
 {		   
 CMOD=0x00;     
 CL=0xEF; 
 CH=0xEF;
 CCAPM0=0x42;  
 CCAP0L=0xEF;  
 CCAP0H=0xFF;  
 
 CR=1;         
 }
 
 void PWM0_set (unsigned char set)	    
 {
 CCAP0L= set;  
 CCAP0H= set;  
 }
 
 
 void IOINIT(void)							   
 {
 P4SW = 0xff;	                           
 P4M1 = (((0x00000000l>>21)&0x80)|((0x00000000l>>18)&0x40)|((0x00000000l>>15)&0x20)|((0x00000000l>>12)&0x10)|((0x00000000l>>9)& 0x08)|((0x00000000l>>6)&0x04)|((0x00000000l>>3)&0x02)|((0x00000000l)&0x01)); P4M0 = (((0x10000000l>>21)&0x80)|((0x10000000l>>18)&0x40)|((0x10000000l>>15)&0x20)|((0x10000000l>>12)&0x10)|((0x10000000l>>9)& 0x08)|((0x10000000l>>6)&0x04)|((0x10000000l>>3)&0x02)|((0x10000000l)&0x01));P47=0; 
 P0M1 = 0x00;	    P0M0 = 0xff;       P0=0;  
 P1M1 = (((0x01000011l>>21)&0x80)|((0x01000011l>>18)&0x40)|((0x01000011l>>15)&0x20)|((0x01000011l>>12)&0x10)|((0x01000011l>>9)& 0x08)|((0x01000011l>>6)&0x04)|((0x01000011l>>3)&0x02)|((0x01000011l)&0x01)); P1M0 = (((0x00110100l>>21)&0x80)|((0x00110100l>>18)&0x40)|((0x00110100l>>15)&0x20)|((0x00110100l>>12)&0x10)|((0x00110100l>>9)& 0x08)|((0x00110100l>>6)&0x04)|((0x00110100l>>3)&0x02)|((0x00110100l)&0x01));P1=(((0x10110111l>>21)&0x80)|((0x10110111l>>18)&0x40)|((0x10110111l>>15)&0x20)|((0x10110111l>>12)&0x10)|((0x10110111l>>9)& 0x08)|((0x10110111l>>6)&0x04)|((0x10110111l>>3)&0x02)|((0x10110111l)&0x01));  
 P2M1 = (((0x00000000l>>21)&0x80)|((0x00000000l>>18)&0x40)|((0x00000000l>>15)&0x20)|((0x00000000l>>12)&0x10)|((0x00000000l>>9)& 0x08)|((0x00000000l>>6)&0x04)|((0x00000000l>>3)&0x02)|((0x00000000l)&0x01)); P2M0 = (((0x11111111l>>21)&0x80)|((0x11111111l>>18)&0x40)|((0x11111111l>>15)&0x20)|((0x11111111l>>12)&0x10)|((0x11111111l>>9)& 0x08)|((0x11111111l>>6)&0x04)|((0x11111111l>>3)&0x02)|((0x11111111l)&0x01));P2=0;  
 P3M1 = (((0x00000000l>>21)&0x80)|((0x00000000l>>18)&0x40)|((0x00000000l>>15)&0x20)|((0x00000000l>>12)&0x10)|((0x00000000l>>9)& 0x08)|((0x00000000l>>6)&0x04)|((0x00000000l>>3)&0x02)|((0x00000000l)&0x01));	P3M0 = (((0x11111111l>>21)&0x80)|((0x11111111l>>18)&0x40)|((0x11111111l>>15)&0x20)|((0x11111111l>>12)&0x10)|((0x11111111l>>9)& 0x08)|((0x11111111l>>6)&0x04)|((0x11111111l>>3)&0x02)|((0x11111111l)&0x01));P3=0;  
 P1ASF =(((0x00000011l>>21)&0x80)|((0x00000011l>>18)&0x40)|((0x00000011l>>15)&0x20)|((0x00000011l>>12)&0x10)|((0x00000011l>>9)& 0x08)|((0x00000011l>>6)&0x04)|((0x00000011l>>3)&0x02)|((0x00000011l)&0x01));                           
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 }
 
 
 
 void BufToLED_Refresh()                      
 {	
  unsigned char data i; 
  unsigned char data X=1;	  
  unsigned char data Y=1;
 for(X=1,i=2;X;X<<=1,i+=2)               
 {
 P2=X;
 for(Y=1;Y!=0;Y<<=1)		             
 {
 P0=Y&LEDBuf[i];
 Delays(DelayTime);
 P0=0;
 }
 P2=0;	
 };
 for(X=1;X<(((0x10000000l>>21)&0x80)|((0x10000000l>>18)&0x40)|((0x10000000l>>15)&0x20)|((0x10000000l>>12)&0x10)|((0x10000000l>>9)& 0x08)|((0x10000000l>>6)&0x04)|((0x10000000l>>3)&0x02)|((0x10000000l)&0x01));X<<=1,i+=2)	     
 {
 P3=X;
 for(Y=1;Y!=0;Y<<=1)		             
 {
 P0=Y&LEDBuf[i];
 Delays(DelayTime);
 P0=0;
 }
 P3=0;	
 };
 
 }
 
 
 
 
 void LEDRefresh_INT() interrupt 3  
 { 
 static unsigned int x=0;		   
 static unsigned char flag=1;
 
 TL1 = 0x00;      
 TH1 = INTTime;                
 
 if(flag)
 {
 if(++x==0xFF)			  
 {
 flag=0;		
 }		
 }
 else
 {
 if(--x==0xCF)	          
 {
 flag=1;			
 }
 }	 		
 PWM0_set(x);                  
 
 BufToLED_Refresh();	 		
 }  
 
 
 void Timer_INT()
 {
 TMOD = 0x11;  
 EA = 1;	      
 TH1 = 0x00;   
 TL1 = 0x00;   
 ET1 = 1;      
 TR1 = 1;      
 
 }
 
 
 void FullScan()
 {
  unsigned char data X=1;	  
  unsigned char data Y=1;
 
 for(Y=1;Y!=0;Y<<=1)		        
 {	
 P0=Y;
 for(X=1;X;X<<=1)	            
 {
 P2=X;
 Delays(7);	
 };
 
 P2=0;
 for(X=1;X<(((0x10000000l>>21)&0x80)|((0x10000000l>>18)&0x40)|((0x10000000l>>15)&0x20)|((0x10000000l>>12)&0x10)|((0x10000000l>>9)& 0x08)|((0x10000000l>>6)&0x04)|((0x10000000l>>3)&0x02)|((0x10000000l)&0x01));X<<=1)     
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
  unsigned int data Count=700;
  unsigned char data i,Cgain,num=0;
 
 IOINIT();
 InitADC();                   
 
 while(--Count)
 FullScan();
 
 for(i=0;i<40;i++) refreshflag[i]=0x09;
 
 P14=0;			   
 Delays(4000);
 P14=1;
 
 PWM_init();       
 PWM0_set(0xFB);
 
 Timer_INT();
 
 for(i=0;i<34;i++) 
 LEDBuf[i]=0x00;
 FontDisp();
 
 while(520)
 {
 for(i=0;i<65;i++)
 {  
 dd[i].real=(GetADCResult(0)+GetADCResult(1))<<gain;	   
 }
 
 processfft(); 
 
 
 while(P16==1)					    
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
 
 
 if(P17==0)CBeep=!CBeep;
 
 if(dd[2].real<32)
 {
 if(++Count==300)	   
 {
 Count=0;
 
 gain=6;
 
 P14=0;			   
 Delays(1000);
 P14=1;
 }
 }
 else 
 {
 Count=1;
 
 if(++num==0xAF)			  
 {
 num=0;
 
 P14=0;			            
 Delays(700);
 P14=1;
 
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
 
 
