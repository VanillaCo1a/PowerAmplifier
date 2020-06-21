#include "STC12c5a60s2.H"
#include "1602.h"
sbit busyFlag = P0^7;
/***********************************************/
//�Զ����8���ַ� �ֱ�Ϊ��1���8���
uchar code Pic[8][8]=
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x1f},
	{0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x1f},
	{0x00,0x00,0x00,0x00,0x1f,0x00,0x1f,0x1f},
	{0x00,0x00,0x00,0x1f,0x1f,0x00,0x1f,0x1f},
	{0x00,0x00,0x00,0x1f,0x1f,0x00,0x1f,0x1f},
	{0x00,0x1f,0x00,0x1f,0x1f,0x00,0x1f,0x1f},
	{0x1f,0x1f,0x00,0x1f,0x1f,0x00,0x1f,0x1f},
};
/*********���LCDæ****************************/
void lcdCheckbusy()				
{ 
	lcdDb=0xff;
	lcdRs=0; 						//dc=1Ϊ����,=0Ϊ����.
	lcdRw=1; 						//rw=1Ϊ��,=0Ϊд.
	lcdE=1; 						//cs=1ѡͨ.
	delay40us(1);
	while(busyFlag);
	lcdE=0;
}
/*******��ʼ������*****************************/
void lcdInit(void)
{
	lcdWriteCommand(0x38);			//����8λ��ʽ��2�У�5x7
	lcdWriteCommand(0x0c);			//������ʾ���ع�꣬����˸
	lcdWriteCommand(0x06);			//�趨���뷽ʽ����������λ
	lcdWriteCommand(0x01);			//�����Ļ��ʾ
}
/********дָ���*****************************/
void lcdWriteCommand(uchar dat)
{
	lcdCheckbusy();
	lcdDb=dat;
	lcdRs=0;					//ָ��
	lcdRw=0;					//д��
	lcdE=1;						//����
	delay40us(1);
	lcdE=0;
}
/********д���ݺ���*****************************/
void lcdWriteData(uchar dat)
{
	lcdCheckbusy();
	lcdDb=dat;
	lcdRs=1;				//����
	lcdRw=0;				//д��
	lcdE=1;					//����
	lcdE=0;
}
/********д��CGRAM "�Զ���" �ַ�***************/
void lcdWritePic()
{
	uchar i,j;
	for(i=0;i<8;i++)
	 {
		lcdWriteCommand(0x40+i*8); //ָ���ַΪ0100 0000 +��0000 0000~0011 1000������ο�˵����CGRAM��ʹ��
		for(j=0;j<8;j++)lcdWriteData(Pic[i][j]);//��CGRAMд�����ͱ�������(CGRAM����).
	 }
}
/*******************************************************
���ܣ���ʾһ���ַ�
�������� �� ��ʾ���꣨x,y,dat����Χ (0~f,0~1,0~7)
*******************************************************/
void dispString(uchar x,uchar y,uchar dat)//dat��Χ��0~7����ʾ��ʾ8���Զ����ַ��ĵڼ���
{
	uchar address;
	switch (y)
	{
		case 0:  address=0x80+x;  //00000000B��00H��+10000000B(80H)=10000000B(80H)
			break;
		case 1:	 address=0xc0+x;  //01000000B��40H��+10000000B(80H)=11000000B(C0H)
			break;
	}
	lcdWriteCommand(address);	  //��ַ��ʾ
	lcdWriteData(dat);			  //��ʾ�Զ���ĵڼ����ַ�
}
/********��ʱ���� 1T 22.1148M***************/
void delay40us(uint n)
{
	uchar a,b;
	while(n--)
	{    
    	for(b=185;b>0;b--)
        	for(a=1;a>0;a--);
	}
}