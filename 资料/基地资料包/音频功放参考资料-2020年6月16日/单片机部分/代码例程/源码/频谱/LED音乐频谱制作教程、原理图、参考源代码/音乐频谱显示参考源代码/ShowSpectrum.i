
#line 1 "src\FFTCode\ShowSpectrum.c" /0
















 
 
  
#line 1 "SRC\FFTCODE\SHOWSPECTRUM.H" /0
















 
 
 
 
 
 
  
#line 1 "SRC\FFTCODE\MYTYPE.H" /0
















 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 23 "SRC\FFTCODE\SHOWSPECTRUM.H" /0
 
  
#line 1 "SRC\FFTCODE\FFT.H" /0
















 
 
 
 
 
  
#line 1 "C:\PROGRAM FILES X\KEIL\C51\INC\MATH.H" /0






 
 
 
 
 
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
 
 
#line 22 "SRC\FFTCODE\FFT.H" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void InitBitRev(void);
 void FftInput(short int *pIn);
 void FftExe(short int *pIn, long int *pRe, long int *pIm);
 void DftExe(short int *pIn, long int *pRe, long int *pIm);
 
 
#line 24 "SRC\FFTCODE\SHOWSPECTRUM.H" /0
 
 
 void ShowSpectrum(void);
 
 extern signed short int AudioInBuf[650];    
 extern unsigned long int AudioInByteCount;   
 
 
#line 19 "src\FFTCode\ShowSpectrum.c" /0
 
 
 
  long int Re[128];
  long int Im[128];
 
 unsigned char Peak[64];
 unsigned char PeakTime[64];
 
 
 
 





 
 void ProcPeak(unsigned char x, unsigned char y)
 {
 if(PeakTime[x]>0)
 {
 PeakTime[x]--;
 }
 else
 {
 if(Peak[x]<8)Peak[x]+=2;
 }
 if(y<Peak[x])
 {
 Peak[x]=y;  
 PeakTime[x]=3;  
 }
 }
 
 





 
 int Compress(int y)
 {
 return sqrt(y);   
 }
 
 





 
 void ShowSpectrum(void)
 {
 int i,x,y,j,p;
 
 
 
 {
 
 }
 
 FftInput(AudioInBuf);        
 FftExe(AudioInBuf,Re,Im);    
 
 
 





















 
 
 
 
 x=17;
 y=8-(Re[0]*8/128)/1024;
 ProcPeak(0,y);  
 Glib_Line(x,y,x,8,RGBS);
 Glib_Line(x+1,y,x+1,8,RGBS);   
 
 
 
 for(i=1;i<14;i++)
 {
 x+=3;
 y=sqrt(Re[i]*Re[i]+Im[i]*Im[i]);    
 y/=10;
 y=Compress(y);   
 y=8-y;   
 ProcPeak(i,y);  
 Glib_Line(x,y,x,8,RGBS);    
 Glib_Line(x+1,y,x+1,8,RGBS);   
 }
 
 
 p=14;
 for(i=14;i<24;i++)
 {
 x+=3;
 y=0;
 for(j=0;j<2;j++)
 {
 y+=sqrt(Re[p]*Re[p]+Im[p]*Im[p]);    
 p++;
 }
 y/=20;  
 y=Compress(y);   
 y=8-y;   
 ProcPeak(i,y);  
 Glib_Line(x,y,x,8,RGBS);  
 Glib_Line(x+1,y,x+1,8,RGBS);   
 }
 
 
 for(i=24;i<34;i++)
 {
 x+=3;
 y=0;
 for(j=0;j<3;j++)
 {
 y+=sqrt(Re[p]*Re[p]+Im[p]*Im[p]);    
 p++;
 }
 y/=30;  
 y=Compress(y);   
 y=8-y;   
 ProcPeak(i,y);  
 Glib_Line(x,y,x,8,RGBS);    
 Glib_Line(x+1,y,x+1,8,RGBS);   
 }
 
 
 for(i=34;i<44;i++)
 {
 x+=3;
 y=0;
 for(j=0;j<4;j++)
 {
 y+=sqrt(Re[p]*Re[p]+Im[p]*Im[p]);    
 p++;
 }
 y/=40;  
 y=Compress(y);   
 y=8-y;   
 ProcPeak(i,y);  
 Glib_Line(x,y,x,8,RGBS);     
 Glib_Line(x+1,y,x+1,8,RGBS);   
 }
 
 
 for(i=44;i<54;i++)
 {
 x+=3;
 y=0;
 for(j=0;j<6;j++)
 {
 y+=sqrt(Re[p]*Re[p]+Im[p]*Im[p]);    
 p++;
 }
 y/=60;  
 y=Compress(y);   
 y=8-y;   
 ProcPeak(i,y);  
 Glib_Line(x,y,x,8,RGBS);     
 Glib_Line(x+1,y,x+1,8,RGBS);   
 }
 
 
 for(i=54;i<64;i++)
 {
 x+=3;
 y=0;
 for(j=0;j<9;j++)
 {
 y+=sqrt(Re[p]*Re[p]+Im[p]*Im[p]);    
 p++;
 }
 y/=90;  
 y=Compress(y);   
 y=8-y;   
 ProcPeak(i,y);    
 Glib_Line(x,y,x,8,RGBS);    
 Glib_Line(x+1,y,x+1,8,RGBS);   
 }
 
 for(i=0;i<64;i++)
 {
 PutPixel(i*3+17,Peak[i],RGB(0x0F,0x0F,0x00));
 PutPixel(i*3+17+1,Peak[i],RGB( 0x0F,0x0F,0x00));
 }
 
 }
 
