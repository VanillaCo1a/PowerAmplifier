
#line 1 "src\FFTCode\FFT.c" /0
















 
 
  
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
 
 
#line 19 "src\FFTCode\FFT.c" /0
 
 
  short int BitRev[128];   
 
 
 
 
 
 
 
 
 
 
#line 32 "src\FFTCode\FFT.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 46 "src\FFTCode\FFT.c" /0
 
 
#line 48 "src\FFTCode\FFT.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 72 "src\FFTCode\FFT.c" /0
 
 
 
 const short int COS_TABLE[128/2]=
 {
 1024,1023,1019,1013,1004,993,980,964,946,926,
 
 903,878,851,822,792,759,724,688,650,610,
 
 569,526,483,438,392,345,297,249,200,150,
 
 100,50,0,-50,-100,-150,-200,-249,-297,-345,
 
 -392,-438,-483,-526,-569,-610,-650,-688,-724,-759,
 
 -792,-822,-851,-878,-903,-926,-946,-964,-980,-993,
 
 -1004,-1013,-1019,-1023
 };
 
 
 const short int SIN_TABLE[128/2]=
 {
 0,50,100,150,200,249,297,345,392,438,
 
 483,526,569,610,650,688,724,759,792,822,
 
 851,878,903,926,946,964,980,993,1004,1013,
 
 1019,1023,1024,1023,1019,1013,1004,993,980,964,
 
 946,926,903,878,851,822,792,759,724,688,
 
 650,610,569,526,483,438,392,345,297,249,
 
 200,150,100,50
 };
 
 
 
#line 112 "src\FFTCode\FFT.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 172 "src\FFTCode\FFT.c" /0
 
 
#line 174 "src\FFTCode\FFT.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 286 "src\FFTCode\FFT.c" /0
 
 
#line 288 "src\FFTCode\FFT.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 504 "src\FFTCode\FFT.c" /0
 
 





 
  short int DoBitRev(short int N, short int L)
 {
  short int Temp1,Temp2;
  short int i;
 for(i=0;i<L/2;i++)
 {
 Temp1=0;
 Temp2=0;
 if(N&(1<<i))
 Temp1=1;
 if(N&(1<<(L-1-i)))
 Temp2=1;
 N&=~(1<<i);
 N&=~(1<<(L-1-i));
 N|=(Temp2<<i);
 N|=(Temp1<<(L-1-i));
 }
 return N;
 }
 
 





 
 void InitBitRev(void)
 {
  short int i;
 for(i=0;i<128;i++)  
 {
 BitRev[i]=DoBitRev(i,9);
 }
 }
 
 





 
 void FftInput(short int *pIn)
 {
  short int i;
  short int Temp;
 for(i=0;i<128;i++)
 {
 if(BitRev[i]>i)   
 {
 Temp=pIn[i];
 pIn[i]=pIn[BitRev[i]];
 pIn[BitRev[i]]=Temp;
 }
 }
 }
 
 





 
 void FftExe(short int *pIn, long int *pRe, long int *pIm)
 {
  short int i,j;
  short int BlockSize;
  long int tr,ti;
  short int OffSet1,OffSet2;
 
 
  short int OffSet0;
 
 
 long c,s;
 
 
 for(j=0;j<128;j+=2)
 {
 tr=pIn[j+1];
 pRe[j+1]=(pIn[j]-tr);
 pIm[j+1]=0;
 pRe[j]=(pIn[j]+tr);
 pIm[j]=0;
 }
 
 for(BlockSize=4;BlockSize<=128;BlockSize<<=1)  
 {
 for(j=0;j<128;j+=BlockSize)
 {
 for(i=0;i<BlockSize/2;i++)
 {
 
#line 607 "src\FFTCode\FFT.c" /1
 
 
 
#line 610 "src\FFTCode\FFT.c" /0
 OffSet0=128/BlockSize*i;
 c=COS_TABLE[OffSet0];
 s=SIN_TABLE[OffSet0];
 
 
 OffSet1=i+j;
 OffSet2=OffSet1+BlockSize/2;
 tr=(long int)((c*pRe[OffSet2]+s*pIm[OffSet2])/1024);
 ti=(long int)((c*pIm[OffSet2]-s*pRe[OffSet2])/1024);
 
#line 620 "src\FFTCode\FFT.c" /1
 
 
 
 
 
#line 625 "src\FFTCode\FFT.c" /0
 pRe[OffSet2]=(pRe[OffSet1]-tr);
 pIm[OffSet2]=(pIm[OffSet1]-ti);
 pRe[OffSet1]=(pRe[OffSet1]+tr);
 pIm[OffSet1]=(pIm[OffSet1]+ti);
 
 }
 }
 }
 
#line 634 "src\FFTCode\FFT.c" /1
 
 
 
#line 637 "src\FFTCode\FFT.c" /0
 }
 
 





 
 void DftExe(short int *pIn, long int *pRe, long int *pIm)
 {
  short int i,j;
  long int tRe,tIm;
 for(i=0;i<128;i++)
 {
 tRe=0;
 tIm=0;
 for(j=0;j<128;j++)
 {
 tRe+=(long int)(pIn[j]*cos(2*3.1415926535897932384626433832795*i*j/128));
 tIm+=(long int)(0-pIn[j]*sin(2*3.1415926535897932384626433832795*i*j/128));
 }
 
#line 660 "src\FFTCode\FFT.c" /1
 
 
 
 
 
 
 
 
 
 
 
#line 671 "src\FFTCode\FFT.c" /0
 pRe[i]=tRe;
 pIm[i]=tIm;
 
 }
 }
 
 
