#include 	"FFT.h"
/********************************************************************/
float pow   (float x, float y);	  //����x��y����
float cos   (float val);
float sin   (float val);
struct compx       //���帴���ṹ��
{
	float real;	   /*ʵ��*/
	float imag;	   /*�鲿*/
};

/******************************************************************* 
����ԭ�ͣ�struct compx EE(struct compx a1,struct compx b2) 
�������ܣ��������������г˷�����
��������������������嶨��ĸ���a,b 
���������a��b�ĳ˻��������������ʽ���
*******************************************************************/
struct compx EE(struct compx a1,struct compx b2) 	//�����˷�
{
	struct compx b3;
	b3.real=a1.real*b2.real-a1.imag*b2.imag;
	b3.imag=a1.real*b2.imag+a1.imag*b2.real;
	return(b3);
}

/***************************************************************** 
FFT����
����ԭ�ͣ�void FFT(struct compx *xin,int N) 
�������ܣ�������ĸ�������п��ٸ���Ҷ�任��FFT��
���������xin[]���飬struct��
*****************************************************************/ 
void FFT(struct compx xin[],int N)   				
{
	int f,m,nv2,nm1,i,k,j=1,l;
	struct compx v,w,t;
	int le,lei,ip;	   			//FFT����ˣ�ʹ�õ����������FFT����
  	float pi;
	nv2=N/2;					//��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵���
	f=N;
	for(m=1;(f=f/2)!=1;m++){;}
	nm1=N-1;
	for(i=0;i<nm1;i++)          //�������
	{
		if(i<j)	 				//���i<j,�����б�ַ
		{
			t=xin[j];
			xin[j]=xin[i];
			xin[i]=t;
		}
		k=nv2;    				//��j����һ����λ��  	//kΪ��������Ӧλ�õ�Ȩֵ
		while(k<j)
		{
			j=j-k; 				//�����λ���0
			k=k/2; 				//k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
		}
		j=j+k;	   				//��0��Ϊ1 
	}
	 
	for(l=1;l<=m;l++)  		//����l��ֵ����������μ���
	{
		le=pow(2,l);    	//�˷�
		lei=le/2;
		pi=3.14159265;		//���ṹ�帳ֵ
		v.real=1.0;	  		//ʵ��Ϊ���Ҳ�FFT_N���������ֵΪ1
		v.imag=0.0;  	  				//�鲿Ϊ0
		w.real=cos(pi/lei);   			//��ת����
		w.imag=-sin(pi/lei);
		
	for(j=1;j<=lei;j++)      			//���Ƶ�������ļ���
 		{
		for(i=j-1;i<N;i=i+le) 			//����ÿ����������Ĵ���
  			{
				ip=i+lei;  				//i��ip�ֱ��ʾ�μӵ�������������ڵ�
   				t=EE(xin[ ip ],v); 		//�������㣬�����ʽ
   				xin[ ip ].real=xin[ i ].real-t.real;   
   				xin[ ip ].imag=xin[ i ].imag-t.imag;
   				xin[ i ].real=xin[ i ].real+t.real;
   				xin[ i ].imag=xin[ i ].imag+t.imag;
  			}
  			v=EE(v,w); //�ı�ϵ����������һ����������  
  		}     
	}
}