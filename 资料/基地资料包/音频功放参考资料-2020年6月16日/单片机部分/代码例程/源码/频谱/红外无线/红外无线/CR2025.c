#include<reg52.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<intrins.h> //����_nop_()���������ͷ�ļ�
#define uchar unsigned char
#define uint  unsigned int


sbit IRIN=P3^2;         //���������������


sbit led1=P1^0;
sbit led2=P1^1;
sbit led3=P1^2;
sbit led4=P1^3;
sbit led5=P1^4;
sbit led6=P1^5;
sbit led7=P1^6;
sbit led8=P1^7;

uchar IRCOM[7];

void delay(unsigned char x) ;

/*******************************************************************/
void main()
{
	 unsigned int  a;
   
	IRIN=1;                    //I/O�ڳ�ʼ��	
	IE=0x81;                 //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
	TCON=TCON|0x01;               //������ʽΪ���帺���ش���
	
	 while(1)
	 {		
	    for(a=100;a>0;a--)
   {
     void IR_IN();
   }	
	  }
} 
/**********************************************************/
void IR_IN() interrupt 0 using 0
{
	unsigned char j,k,N=0;
	unsigned char q=0;
	EX0 = 0;   
	delay(15);
	if (IRIN==1) 
	{ 
		EX0 =1;
		return;
	} 
	           //ȷ��IR�źų���
	while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
		delay(1);
	
	for (j=0;j<4;j++)         //�ռ���������
	{ 
		for (k=0;k<8;k++)        //ÿ��������8λ
		{
			while (IRIN)            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
			{delay(1);}
			while (!IRIN)          //�� IR ��Ϊ�ߵ�ƽ
				delay(1);
			while (IRIN)           //����IR�ߵ�ƽʱ��
			{
				delay(1);
				N++;           
				if (N>=30)
				{ 
					EX0=1;
					return;
				}                  //0.14ms���������Զ��뿪��
			}                        //�ߵ�ƽ�������                
			IRCOM[j]=IRCOM[j] >> 1;     //�������λ����0��
			if(N>=8)
			{
				IRCOM[j] = IRCOM[j] | 0x80;		  //�������λ����1��
			}  
			N=0;
		}
	}
	
	if(IRCOM[2]!=~IRCOM[3])
	{ 
		EX0=1;
		return; 
	}
	
	IRCOM[5]=IRCOM[2] & 0x0F;     //ȡ����ĵ���λ
	IRCOM[6]=IRCOM[2] >> 4;       //����4�Σ�����λ��Ϊ����λ
	
	if(IRCOM[5]>9)
	{ 
		IRCOM[5]=IRCOM[5]+0x37;
	}
	else
	IRCOM[5]=IRCOM[5]+0x30;
	
	if(IRCOM[6]>9)
	{ 
		IRCOM[6]=IRCOM[6]+0x37;
	}
	else
	IRCOM[6]=IRCOM[6]+0x30;

	q= (((IRCOM[6]&0x0f)<<4) + (IRCOM[5]&0x0f));
    

	switch(q)    //�жϰ�������ֵ
	{
		case 0x04:led1=1;led2=0;led3=1;led4=0;led5=1;led6=0;led7=1;led8=0;break;  //��#��
		case 0x19:led1=0;break;  //��0��
		case 0x40:led5=0;break;  //��5��
		case 0x43:led6=0;break;  //��6��
		case 0x44:led4=0;break;  //��4��
		case 0x45:led1=0;break;  //��1��
		case 0x46:led2=0;break;  //��2��
		case 0x47:led3=0;break;  //��3��
		case 0x07:led7=0;break;  //��7��
		case 0x18:led1=0;led2=0;led3=1;led4=1;led5=1;led6=1;led7=1;led8=1;break;  //���ϣ�
		case 0x09:led1=0;led2=0;led3=0;led4=0;led5=0;led6=0;led7=0;led8=0;break;  //��9��
		case 0x08:led1=1;led2=1;led3=1;led4=1;led5=0;led6=0;led7=1;led8=1;break;  //����
		case 0x13:led1=1;led2=1;led3=1;led4=1;led5=1;led6=1;led7=1;led8=1;break;  //��ok��
		case 0x51:led1=1;led2=1;led3=1;led4=1;led5=1;led6=1;led7=0;led8=0;break;  //���ң�
		case 0x15:led8=0;break;  //��8��
		case 0x52:led1=1;led2=1;led3=0;led4=0;led5=1;led6=1;led7=1;led8=1;break;  //���£�
		case 0x16:led1=0;led2=1;led3=0;led4=1;led5=0;led6=1;led7=0;led8=1;break;  // ��*��
	
		default :break; 
	}

	 EX0 = 1; 
}


/***************��ʱ����*****************************/
void delay(unsigned char x)    //x*0.14MS
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++) {}
	}
}





