#include "STC12c5a60s2.H"
#include "1602.h"
sbit busyFlag = P0^7;
/***********************************************/
//自定义的8个字符 分别为第1横格到8横格
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
/*********检查LCD忙****************************/
void lcdCheckbusy()				
{ 
	lcdDb=0xff;
	lcdRs=0; 						//dc=1为数据,=0为命令.
	lcdRw=1; 						//rw=1为读,=0为写.
	lcdE=1; 						//cs=1选通.
	delay40us(1);
	while(busyFlag);
	lcdE=0;
}
/*******初始化函数*****************************/
void lcdInit(void)
{
	lcdWriteCommand(0x38);			//设置8位格式，2行，5x7
	lcdWriteCommand(0x0c);			//整体显示，关光标，不闪烁
	lcdWriteCommand(0x06);			//设定输入方式，增量不移位
	lcdWriteCommand(0x01);			//清除屏幕显示
}
/********写指令函数*****************************/
void lcdWriteCommand(uchar dat)
{
	lcdCheckbusy();
	lcdDb=dat;
	lcdRs=0;					//指令
	lcdRw=0;					//写入
	lcdE=1;						//允许
	delay40us(1);
	lcdE=0;
}
/********写数据函数*****************************/
void lcdWriteData(uchar dat)
{
	lcdCheckbusy();
	lcdDb=dat;
	lcdRs=1;				//数据
	lcdRw=0;				//写入
	lcdE=1;					//允许
	lcdE=0;
}
/********写入CGRAM "自定义" 字符***************/
void lcdWritePic()
{
	uchar i,j;
	for(i=0;i<8;i++)
	 {
		lcdWriteCommand(0x40+i*8); //指令地址为0100 0000 +（0000 0000~0011 1000）具体参考说明书CGRAM的使用
		for(j=0;j<8;j++)lcdWriteData(Pic[i][j]);//向CGRAM写入字型编码数据(CGRAM数据).
	 }
}
/*******************************************************
功能：显示一个字符
函数参数 ： 显示坐标（x,y,dat）范围 (0~f,0~1,0~7)
*******************************************************/
void dispString(uchar x,uchar y,uchar dat)//dat范围是0~7，表示显示8个自定义字符的第几个
{
	uchar address;
	switch (y)
	{
		case 0:  address=0x80+x;  //00000000B（00H）+10000000B(80H)=10000000B(80H)
			break;
		case 1:	 address=0xc0+x;  //01000000B（40H）+10000000B(80H)=11000000B(C0H)
			break;
	}
	lcdWriteCommand(address);	  //地址显示
	lcdWriteData(dat);			  //显示自定义的第几个字符
}
/********延时函数 1T 22.1148M***************/
void delay40us(uint n)
{
	uchar a,b;
	while(n--)
	{    
    	for(b=185;b>0;b--)
        	for(a=1;a>0;a--);
	}
}