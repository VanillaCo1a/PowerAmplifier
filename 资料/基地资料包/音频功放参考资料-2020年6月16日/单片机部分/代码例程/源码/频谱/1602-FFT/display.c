#include 	"display.h"
#include 	"1602.h"
#define uchar unsigned char
#define uint unsigned int
/******************************************************************/
xdata struct compx s[ 64 ]; 			//FFT���ݻ������XDATA�ռ�
extern float pow   (float x, float y);	//����x��y����
extern float cos   (float val);
extern float sin   (float val);						
float sqrt  (float val);				//����һ���Ǹ�ʵ����ƽ����
extern struct compx           			//���帴���ṹ��
{
	float real;	/*ʵ��*/
	float imag;	/*�鲿*/
};

/*******************************************************************
��ʾƵ�׺���
LCD1602��ʾ��ʽ���������ϣ���������
j=1	
j=2	 	 
******************************************************************/
void showbar(void)
{
	uchar i,j,dat1,dat2;
	uint  tmp1=0,tmp2=0;  // ϵ��

	for(i=1;i<32;i+=4)
	{
		float t0=0,t2=0;
		t0=sqrt(pow((s[i  ].real+s[i+1].real),2)+pow((s[i  ].imag+s[i+1].imag),2))/2;
		t2=sqrt(pow((s[i+2].real+s[i+3].real),2)+pow((s[i+2].imag+s[i+3].imag),2))/2;
		//z=a+bi  �Oz�O=�̣�a^2+b^2)
		//��任������ģֵ�����븴����ʵ������
		tmp1=(uint)(t0/2); //�Ŵ������ɸı�
		tmp2=(uint)(t2/2);
		for(j=2;j>0;j--)
		{  							  //dat��Χ��0~7����ʾ��ʾ8���Զ����ַ��ĵڼ���
			if (tmp1>=8) 	          //���� ��0(j=0)���dat1�񣬵�1(j=1)���tmp1��
			{
				dat1=7;
				tmp1=tmp1-8;
			}			
			else  
				if(tmp1==0) dat1=32;			//�ո� ����15С��33��Ϊ�ո� 0x10~0x20Ϊ���ַ�
					else 								
					 {
						 dat1=tmp1-1;			//1-8��
						 tmp1=0;
					 }
						
			dispString(i/2,j-1,dat1);	   //��1��2��5��7��9��11��13��15��	 //32/4=8							   
			if (tmp2>=8)				   //����
			{
				dat2=7;
				tmp2=tmp2-8;
			} 			
			else  
				if(tmp2==0) dat2=32;		//�ո�
					else 
					 {
						 dat2=tmp2-1;		//1-8��
						 tmp2=0;
					 }											
			dispString(i/2+1,j-1,dat2);    //��2��4��6��8��10��12��14��16��
		} 						
	}
}
