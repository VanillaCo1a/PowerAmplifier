#include <stdlib.h>
#include "INTRINS.H"
#include <qumoshuju.h>
#define uchar unsigned char
#define uint unsigned int


sbit pmw=P1^3;
sbit R1=P2^3;     
sbit R2=P2^1;	
sbit G1=P2^2;	
sbit G2=P2^0; 	
sbit STCP=P0^6;		
sbit SHCP=P2^7;		
sbit OE=P2^4;	
sbit IA=P0^5;	
sbit IB=P2^6; 	
sbit IC=P0^4;	
sbit ID=P2^5;		
sbit ds18b20=P0^2;	 
sbit ds1302rst=P0^3;  
sbit ds1302io=P3^3;	   
sbit ds1302cslk=P3^4; 
sbit key_jia=P3^0;		
sbit key_jian=P3^1;		
sbit key_fan_hiu=P3^6;						
sbit key_qu_ren=P3^5;


uchar yangshi=3;
 
uchar i,j,jj,k,b,p,G,color=0,daid=1; uint TEMP1,ansdw,wen,tcssd=0; bit stop,xyz=0;
uchar COUNT=15,COUNT1=0,ADC_Count=0,LINE=15;
uchar TPL,TPH,ii,wdbc;sbit ACC_7 = ACC^7;
 
uchar bianjie,sudu=1,kai_shi=1,kai_sh=1,sscan=0;
uchar efenge=0,efenshi=0,efenbai=0,efenqian=0;
uchar xinz=0,fangx=0,fkx=3,fky=17,xiaxia=0;
uchar newxinz=1,newfangx,newfkx,newfky,sssddd=1;

uchar wnian,wyue,wri,wshi,wfen,wmiao,wxinq;
uchar nian1,nian2,yue1,yue2,ri1,ri2,shi1,shi2,shi3,shi4;
uchar fen1,fen2,fen3,fen4,miao1,miao2,xinqi,kaij,szxh=0,ysh,ysfu;
uchar yiji,erji,foo,foo1,jishu,shanji,shiji,aaajjj=0,hysj=0;
int Real,Imag,temp;



void scan(uchar Value)	 //行使能
{
	switch(Value)
	{
		case  0: scan0;break;
		case  1: scan1;break;
		case  2: scan2;break;
		case  3: scan3;break;
		case  4: scan4;break;
		case  5: scan5;break;
		case  6: scan6;break;
		case  7: scan7;break;
		case  8: scan8;break;
		case  9: scan9;break;
		case 10:scan10;break;
		case 11:scan11;break;
		case 12:scan12;break;
		case 13:scan13;break;
		case 14:scan14;break;
		case 15:scan15;break;
		default:break;
	}
}




void Init()	  //	 单片机初始化
{
	
	
	P1ASF = 0x01;

	P0M0=0x70;
	P0M1=0x00;

	P1M0 = 0x08; // 0000 1000
	P1M1 = 0x01; //	0000 0001

	P2M0=0xef;
	P2M1=0x00;
	

		               	    
	AUXR1 &= 0xFB;	                
	EADC=1;			 
	ADC_CONTR = 0x08;
	hua_88(32,45,1,8,0);
	hua_816(32,45,1,8,0);
	hua_1616(32,45,1,8,0);
	qu_88(32,45,1,8,0);
	qu_816(32,45,1,8,0);
	qu_1616(32,45,1,8,0);
	hua_dian1(0,0,1);
	qing_dian1(0,0,1);
	qing_hong();
	qing_nv();	 
	TMOD = 0X12;					   
	TH0 = 0x70;                                				  
	TL0 = 0x70;
	TH1 = 0xf3;												 
	TL1 = 0Xaa;		
	ET0 = 1;					  
	TR0 = 0;					   	 
	ET1 = 1;
	TR1 = 1;
	PT1 = 0;
	PT0 = 1;
	IPH |= 0x20;
	IP |= 0x20;


	CMOD=0x00;
	CCON=0x40;
	CCAPM0=0x42;
	CCAP0H=254;

	BRT=0xfa;
	AUXR|=0x11;
	SCON|=0x50;
	ES=1;
						
	EA = 1;
	kaij=yangshi;
	yangshi=2;						
	OE = 1; 
	if(OE==0) kai_ji();
	delay(65530);
	Initial();
	read_ds18b20_1T();
	//kai_ji();
	for(i=0;i<64;i++)
	{
		LB[i]=0;
		LB1[i]=0;
	}
	if(kaij==1)
	{
		for(p=0;p<64;p++)
		{
			ttb1.eal[p]=0x0c00;
			   
		}
		ttb1.eal[3]=0x0fff;
		ttb1.eal[2]=0x0fff;
		ttb1.eal[1]=0x0fff;
		ttb1.eal[0]=0x0fff;
		kai_shi=1;kai_sh=1;
	}
	ysh=kaij;
	yangshi=kaij;
		 
}



void ADC_Finish() interrupt 5	//		 频谱ad采样
{
	ADC_CONTR &= !0x10;
	ttb1.eal[LIST_TAB[ADC_Count]]=(int)((ADC_RES*3)<<2)+(ADC_RESL)*5;
	if(ADC_Count<=127) ADC_Count++;
	else {EADC=0;TR0=0;}
}

void bbc() interrupt 4
{
	if(TI==1) TI=0;
	if(RI==1)
	{
		RI=0;
		hysj=SBUF;
		if(hysj==0x40|hysj==0x44|hysj==0x43|hysj==0x15|hysj==0x46) aaajjj=hysj;
		if(hysj==0x16) {if(color==0) color=1;else color=0;}
		if(hysj==0x09) {if(daid==1) daid=0;else daid=1;}
		if(hysj==0x45) {if(CCAP0H>15) CCAP0H=CCAP0H-10;}		   
		if(hysj==0x47) {if(CCAP0H<240) CCAP0H=CCAP0H+10;}
		if(hysj==0x19) {if(sssddd>2) sssddd--;}
		if(hysj==0x0d) {if(sssddd<15) sssddd++;} 
		hysj=0;
	}

}

void LED_Display() interrupt 3	//		  显示中断
{
	if(yangshi==0) pinpu();
	if(yangshi==1) elsyx();
	if(yangshi>1) shezhi();
}
void Ad_Control() interrupt 1	//		  控制ad采样时间	
{
	ADC_CONTR = 0xe8;
}

void main()	   //		  主函数
{
	Init();
	while(1)
	{
		if(yangshi==0) pinpufft();
		if(yangshi==1) elsfk();
		if(yangshi==2) chan_shu();
		if(yangshi==3) wanln();
		if(yangshi==4) tcs_zhukong();
	}				   
}



void pinpu()	//		  中断频谱显示
{
	TH1=0xf3;
	TL1=0xaa;
	LB[0]=LB[1];
	LB1[0]=LB1[1];
	//LB[15]=20;
	//LB[24]=20;
	//LB[33]=20;
	//LB[41]=20;
	//LB[53]=20;
	for	(G=0;G<64;G++)				
	{
		if(color==1)
		{
			if(LB[G]<=LINE+16)R1=1;
			else R1=0;
		  	if(LB[G]<=LINE)R2=1;
			else R2=0;

			if(LB1[G]==LINE){G1=1;G2=0;}
			else if(LB1[G]==(LINE+16)){G1=0;G2=1;}
			else G2=G1=1; 
		}
		if(color==0)
		{
			if(LB[G]<=LINE+16)G1=1;
			else G1=0;
		  	if(LB[G]<=LINE)G2=1;
			else G2=0;

			if(LB1[G]==LINE){R1=1;R2=0;}
			else if(LB1[G]==(LINE+16)){R1=0;R2=1;}
			else R2=R1=1; 	
		}
		SHCP=1;
		_nop_();
		_nop_();
		_nop_();
		SHCP=0;		
	}
	P2M0|=0x10;
	scan(15-LINE);
	STCP=1;
	_nop_();
	_nop_();
	_nop_();
	STCP=0;
	P2M0&=0xef;

	//delay(4);

	if(LINE>0) LINE--;
	else LINE=15;
	for(jj=0;jj<4;jj++)
	{
		if(LB[COUNT]>0)
			LB[COUNT]--;	
		if(COUNT>0)
			COUNT--;	
		else 
			COUNT=64-1;
	}
	for(jj=0;jj<4;jj++)
	{
		if(stop==1)
		{
			if(LB2[COUNT1]==0)
			{
				if(LB1[COUNT1]>LB[COUNT1])LB1[COUNT1]--;
			}
			else 
				LB2[COUNT1]--;
		COUNT1++;
		stop=0;
		}
		else
		stop=1;
	}
	if(COUNT1>=64) COUNT1=0;
	if(key_qu_ren==0|aaajjj==0x40)
	{
		for(G=0;G<100;G++);
		if(key_qu_ren==0|aaajjj==0x40) {aaajjj=0;ysh=2;ysfu=yangshi;}
	}
}



void FFT()		 //		  fft算法
{
	for( i=1; i<=7; i++)                         
	{
		b=1;
		b <<=(i-1);                                       
		for( j=0; j<=b-1; j++)                             
		{
			p=1;
			p <<= (7-i);            
			p = p*j;
			for( k=j; k<128; k=k+2*b)             
			{
				Real = ttb1.eal[k]; Imag = ttb2.age[k]; temp = ttb1.eal[k+b];
				ttb1.eal[k] = ttb1.eal[k] + ((ttb1.eal[k+b]*COS_TAB[p])>>7) + ((ttb2.age[k+b]*SIN_TAB[p])>>7);
				ttb2.age[k] = ttb2.age[k] - ((ttb1.eal[k+b]*SIN_TAB[p])>>7) + ((ttb2.age[k+b]*COS_TAB[p])>>7);
				ttb1.eal[k+b] = Real - ((ttb1.eal[k+b]*COS_TAB[p])>>7) - ((ttb2.age[k+b]*SIN_TAB[p])>>7);
				ttb2.age[k+b] = Imag + ((temp*SIN_TAB[p])>>7) - ((ttb2.age[k+b]*COS_TAB[p])>>7);              
				ttb1.eal[k] >>= 1;             
				ttb2.age[k] >>= 1; 
				ttb1.eal[k+b]  >>= 1;                 
				ttb2.age[k+b]  >>= 1;
			}
		}
	} 
	ttb1.eal[0]=ttb2.age[0]=0;
	for(j=0;j<64;j++)											 
	{
		TEMP1=((((ttb1.eal[j]* ttb1.eal[j]))+((ttb2.age[j]*ttb2.age[j]))));
		if(TEMP1<8)TEMP1=0;
		else if(TEMP1<12)TEMP1=1;
		else if(TEMP1<18)TEMP1=2;
		else if(TEMP1<28)TEMP1=3;
		else if(TEMP1<40)TEMP1=4;
		else if(TEMP1<49)TEMP1=5;
		else if(TEMP1<64)TEMP1=6;
		else if(TEMP1<81)TEMP1=7;
		else if(TEMP1<100)TEMP1=8;
		else if(TEMP1<121)TEMP1=9;
		else if(TEMP1<144)TEMP1=10;
		else if(TEMP1<169)TEMP1=11;
		else if(TEMP1<196)TEMP1=12;
		else if(TEMP1<225)TEMP1=13;
		else if(TEMP1<256)TEMP1=14;
		else if(TEMP1<270)TEMP1=15;
		else if(TEMP1<324)TEMP1=16;
		else if(TEMP1<361)TEMP1=17;
		else if(TEMP1<400)TEMP1=18;
		else if(TEMP1<441)TEMP1=19;
		else if(TEMP1<484)TEMP1=20;
		else if(TEMP1<529)TEMP1=21;
		else if(TEMP1<576)TEMP1=22;
		else if(TEMP1<625)TEMP1=23 ;
		else if(TEMP1<676)TEMP1=24;
		else if(TEMP1<729)TEMP1=25;
		else if(TEMP1<784)TEMP1=26;
		else if(TEMP1<841)TEMP1=27;
		else if(TEMP1<900)TEMP1=28;
		else if(TEMP1<961)TEMP1=29;
		else if(TEMP1<1024)TEMP1=30;
		else TEMP1=31;	
		if(TEMP1>(LB[j]))LB[j]=TEMP1;        
		if(TEMP1>(LB1[j]))
		{
			LB1[j]=TEMP1;
			LB2[j]=8;
		}
	}
}




void pinpufft()		//		  频谱主控
{
	ADC_Count=0;
	TR0=1;
	EADC=1;
	while(ADC_Count<128);
	for(i=0;i<128;i++)
	{
		ttb2.age[i]=0;
	}
	FFT();
	if(ysh!=yangshi)
	{
	   yangshi=ysh;
	   qing_huan_chong();
	}
}



void delay(uint ran_shi)	//		延时
{
    while (ran_shi--)
    {
        _nop_();
        _nop_();
	}
}


void DS18B20_Reset_1T()		
{
    CY = 1;
    while (CY)
    {
        ds18b20 = 0;             
        delay(240);        
        delay(170);
        ds18b20 = 1;               
        delay(60);         
        CY = ds18b20;               
        delay(200);     
    }
}


uchar DS18B20_ReadByte_1T()	   			
{
    uchar dat = 0;
    for (ii=0; ii<8; ii++)          
    {
        dat >>= 1;
        ds18b20 = 0;                
        delay(1);              
        ds18b20 = 1;                   
        delay(1);               
        if (ds18b20) dat |= 0x80;      
        delay(45);              
    }
    return dat;
}


void DS18B20_WriteByte_1T(uchar dat)	 
{
    for (ii=0; ii<8; ii++)        
    {
        ds18b20 = 0;                    
        delay(1);               
        dat >>= 1;                
        ds18b20 = CY;
        delay(50);         
        ds18b20 = 1;               
        delay(1);             
    }
}



void read_ds18b20_1T()	 
{
	while (!ds18b20); 
    DS18B20_Reset_1T();                
    DS18B20_WriteByte_1T(0xCC);        
    DS18B20_WriteByte_1T(0xBE);       
    TPL = DS18B20_ReadByte_1T();      
    TPH = DS18B20_ReadByte_1T();
	if(TPH>200)
	{
		TPH=~TPH;
		TPL=~TPL;
	} 
	wen=TPH*160+(TPL/16)*10+(TPL%16)*5/8;		
    DS18B20_Reset_1T();               
    DS18B20_WriteByte_1T(0xCC);       
    DS18B20_WriteByte_1T(0x44);  
}



void Write1302 ( uchar addr,uchar dat )		 //
{
	uchar temp2;
	ds1302rst=0; 
	ds1302cslk=0; 
	ds1302rst = 1; 
	for ( ii=8; ii>0; ii-- )
	{
		ds1302cslk = 0;
		temp2 = addr;
		ds1302io = (bit)(temp2&0x01);
		addr >>= 1;
		ds1302cslk = 1;
	}
	
	for ( ii=8; ii>0; ii-- )
	{
		ds1302cslk = 0;
		temp2 = dat;
		ds1302io = (bit)(temp2&0x01);
		dat >>= 1;
		ds1302cslk = 1;
	}
	ds1302rst = 0;
}

uchar Read1302 ( uchar addr )	   //
{
	uchar temp2,dat1;
	ds1302rst=0;
	ds1302cslk=0;
	ds1302rst = 1;
	for ( ii=8; ii>0; ii-- )
	{
		ds1302cslk = 0;
		temp2 = addr;
		ds1302io = (bit)(temp2&0x01);
		addr >>= 1;
		ds1302cslk = 1;
	}
	
	for ( ii=8; ii>0; ii-- )
	{
		ACC_7=ds1302io;
		ds1302cslk = 1;
		ACC>>=1;
		ds1302cslk = 0;
	}
	ds1302rst=0;
	dat1=ACC;
	return (dat1);
}

void Initial()	  //	   1302初始化
{
	p=Read1302 (du_miao);
	if((p>>=7)>=1)
	{
		Write1302 (xie_dian_yuan,0x00);
		Write1302 (xie_miao,0x00); 
		Write1302 (xie_fen_zhong,0x44);
		Write1302 (xie_xiao_shi,0x10);
		Write1302 (xie_tian,0x02);
		Write1302 (xie_xin_qi,0x01);
		Write1302 (xie_yue,0x05);
		Write1302 (xie_nian,0x14);
		Write1302 (xie_chong_din,0xa3);	
		Write1302 (xie_dian_yuan,0x80);
	}
}



void elsyx()	 //		   俄罗斯方块中断显示
{
	TH1=0xf5;
	TL1=0Xca;
	for(bianjie=0;bianjie<64;bianjie++)
	{
		if(sscan==0)
		{
			if(bianjie<56)
			{
				R1=0;
				if(bianjie==0)R2=0; else R2=1;
				if(bianjie>0)
				{	
					if((((ttb1.eal[(bianjie-1)/3+4])>>5)&0x0001)>0)G2=0; else G2=1;
				
				}
				if(bianjie==55) 
				{
					R1=R2=0;
				}
			}
			else
			{
				R1=R2=1;
				if(bianjie>55)
			
				{
					if(((fensu[efenqian*6]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
					if(((fensu[efenshi*6+4]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
				}
				G2=1;
			}


		}
		if(0<sscan)
		{
			if(sscan<15)
			{
				if(bianjie<56)
				{
					if(bianjie==0)
					{
						R2=0;
						R1=0;
					}
					else
					{ 
						R2=1;
						R1=1;
					}
	
					if(bianjie>0)
					{	
						if((((ttb1.eal[(bianjie-1)/3+4])>>((sscan-1)/3))&0x0001)>0)G1=0; else G1=1;
						if(bianjie>1)
						{
							if((sscan-2)%3==0)
							{	
								if(sscan!=1)
								if(((bianjie-2)%3)==0) {G1=1;if(daid==0) R1=0;}
							}
							
						}
						
						
	
	
						if((((ttb1.eal[(bianjie-1)/3+4])>>(sscan/3+5))&0x0001)>0)G2=0; else G2=1;
						if((sscan-1)%3==0)
						{
							if(bianjie>1)
							{
								if(((bianjie-2)%3)==0){ G2=1;if(daid==0) R2=0;}
							}
						}
					}
					if(bianjie==55) 
					{
						R1=R2=0;
						G1=G2=1;
					}
				}
				else
				{
					
					G2=1;
					G1=1;
					R1=R2=1;
					if(bianjie>55)
				
					{ 
						if(sscan==1)
						{
							if(((fensu[efenqian*6+1]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							if(((fensu[efenshi*6+5]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
						}
						if(sscan==2)
						{
							if(((fensu[efenqian*6+2]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							if(((fensu[efenge*6]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
						}
						if(sscan==3)
						{
							if(((fensu[efenqian*6+3]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							if(((fensu[efenge*6+1]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
						}
						if(sscan==4)
						{
							 if(((fensu[efenqian*6+4]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							if(((fensu[efenge*6+2]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
						}
						if(sscan==5)
						{
							 if(((fensu[efenqian*6+5]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							if(((fensu[efenge*6+3]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
						}
						if(sscan==6)
						{
							 if(((fensu[efenbai*6]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							if(((fensu[efenge*6+4]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
						}
						if(sscan==7)
						{
							 if(((fensu[efenbai*6+1]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							if(((fensu[efenge*6+5]>>(bianjie-56))&0x01)>0) R2=1; else R2=0;
						}
						if(sscan==8)
						{
							 if(((fensu[efenbai*6+2]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							 if(((fangk[newxinz][newfangx][(bianjie-56)/2])&0x01)>0) G2=0; else G2=1;
						}
						if(sscan==9)
						{
							 if(((fensu[efenbai*6+3]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							 if(((fangk[newxinz][newfangx][(bianjie-56)/2])&0x01)>0) G2=0; else G2=1;
						}
						if(sscan==10)
						{
							 if(((fensu[efenbai*6+4]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							 if((((fangk[newxinz][newfangx][(bianjie-56)/2])>>1)&0x01)>0) G2=0; else G2=1;
						}
						if(sscan==11)
						{
							 if(((fensu[efenbai*6+5]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							 if((((fangk[newxinz][newfangx][(bianjie-56)/2])>>1)&0x01)>0) G2=0; else G2=1;
						}
						if(sscan==12)
						{
							 if(((fensu[efenshi*6]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							 if((((fangk[newxinz][newfangx][(bianjie-56)/2])>>2)&0x01)>0) G2=0; else G2=1;
						}
						if(sscan==13)
						{
							 if(((fensu[efenshi*6+1]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							 if((((fangk[newxinz][newfangx][(bianjie-56)/2])>>2)&0x01)>0) G2=0; else G2=1;
						}
						if(sscan==14)
						{
							 if(((fensu[efenshi*6+2]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
							 if((((fangk[newxinz][newfangx][(bianjie-56)/2])>>3)&0x01)>0) G2=0; else G2=1;
						}

					}
				}
			}
		}
		if(sscan==15)
		{
			if(bianjie<56)
			{
				R2=0;G2=1;
				if(bianjie==0)R1=0; else R1=1;
				if(bianjie>0)
				{	
					if((((ttb1.eal[(bianjie-1)/3+4])>>4)&0x0001)>0)G1=0; else G1=1;
					
				}
				if(bianjie==55) 
				{
					R1=R2=0;
				}
			}
			else
			{
				R1=R2=1;
				R2=1;
				G1=1;
				if(bianjie>55)
				{
					if(((fensu[efenshi*6+3]>>(bianjie-56))&0x01)>0) R1=1; else R1=0;
					if((((fangk[newxinz][newfangx][(bianjie-56)/2])>>3)&0x01)>0) G2=0; else G2=1;
				}
			}
		}
		SHCP=1;
		delay(2);
		SHCP=0;
	}
	P2M0|=0x10;
	STCP=1;
	delay(2);
	STCP=0;	
	scan(sscan);
	P2M0&=0xef;
	if(sscan<15) sscan++; else sscan=0;
	i++;
	if(i==(250/sudu))
	{	
		j++;
		i=0;
		if(j>3)
		{xiaxia=1;
		j=0;
		}
	}
	if((key_qu_ren==0&&key_fan_hiu==0)|aaajjj==0x46)
	{
		for(bianjie=0;bianjie<100;bianjie++);
		if((key_qu_ren==0&&key_fan_hiu==0)|aaajjj==0x46) {aaajjj=0;ysh=2; ysfu=yangshi;}
	}
}



void elsfk()	  //		俄罗斯方块主控
{
	if(kai_sh==1) kai_shi=1;
	while(kai_shi&&ysh==1)
	{
		for(p=0;p<64;p++)
		{
			ttb1.eal[p]=0x0c00;
			   
		}
		ttb1.eal[3]=0x0fff;
		ttb1.eal[2]=0x0fff;
		ttb1.eal[1]=0x0fff;
		ttb1.eal[0]=0x0fff;
		efenge=1;
		while(kai_sh&&ysh==1)
		{
			if(key_jia==0|aaajjj==0x44)
	     	{
				delay(2000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
				 	efenge++;
					if(efenge>9) efenge--;			
				}
				delay(10000);
				
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(2000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;
					efenge--;
					if(efenge==0) efenge++;
				}
				delay(10000);
				
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(1000);
				if(key_qu_ren==0|aaajjj==0x40)
				{
					while(key_qu_ren==0&&aaajjj==0x40) 
					{	
						aaajjj=0;
						COUNT++;
						delay(10);
						if(COUNT==30) COUNT=5;
					}
					kai_shi=0;
					kai_sh=0;
					sudu=efenge;
					efenge=0;
					srand(rand()+fangx+fkx+fky+COUNT);
					fkx=4;
					fky=18;
					xinz=newxinz;
					fangx=newfangx;
				    newxinz=rand()%6;
					newfangx=rand()%3;
					srand(rand()+fangx+fkx+fky+COUNT);
					xinz=newxinz;
					fangx=newfangx;
				    newxinz=rand()%6;
					newfangx=rand()%3;
					TEMP1=0;		
				}
			}
		}
	}
	kai_shi=1;
	xiefk();
	while(kai_shi&&ysh==1)
	{
		if(key_jia==0|aaajjj==0x44)
     	{
			delay(1000);
			if(key_jia==0|aaajjj==0x44)
			{	aaajjj=0;
				if(fkx>0)
				{
					qufk();
				   fkx--;
				   if(chongt()==1) fkx++;
				   xiefk();
				 }
			}
			delay(13000);
		}
		if(key_jian==0|aaajjj==0x43)
		{
			delay(1000);
			if(key_jian==0|aaajjj==0x43)
			{	aaajjj=0;
				qufk();			
			   fkx++;
			   if(chongt()==1) fkx--;
			   xiefk();				
			}
			delay(13000);
		}
		if(key_qu_ren==0|aaajjj==0x40)
		{
			delay(1000);
			if(key_qu_ren==0|aaajjj==0x40)
			{	aaajjj=0;
				qufk();		
			   fangx++;
			   if(chongt()==1) fangx--;
			   if(fangx>3) fangx=0;
			   xiefk(); 				
			}
			while(key_qu_ren==0);
			delay(1000);
			
		}

		 if(key_fan_hiu==0|aaajjj==0x15)
		{
			delay(1000);
			if(key_fan_hiu==0|aaajjj==0x15)
			{	
				//qufk();
				COUNT1=1;
				while((key_fan_hiu==0&&COUNT1==1)||aaajjj==0x15)
				{		
						qufk();
					    fky--;
					   if(chongt()==1)
					   {
					   		
					   		COUNT1=0;
							 fky++;
							 xiaxia=1;
							 aaajjj=0;
					   }
					   if(COUNT1==1)
					   {
					   	   //fky++;
						   //qufk();
						   //fky--;
						   xiefk();
					   }
					   delay(1500); 
			     }
			   xiefk(); 				
			}
			delay(1000);
		}


		if(xiaxia==1)
		{	 
			qufk();
			fky--;
			if(chongt()==1)
			{
				fky++;
				xiefk();
				manfk();
				chanfk();
				if(chongt()==1)
				   {
				   		xiefk();
						while(key_qu_ren==1&&aaajjj==0);
						aaajjj=0;
						delay(65534);
				   	    for(p=0;p<64;p++)
						{
							ttb1.eal[p]=0x0c00;
							   
						}
						ttb1.eal[3]=0x0fff;
						ttb1.eal[2]=0x0fff;
						ttb1.eal[1]=0x0fff;
						ttb1.eal[0]=0x0fff;
						kai_shi=0;
						kai_sh=1;
				   } 
					
			}
			xiefk();
			if(kai_sh==1) qufk();
			xiaxia=0;
		}
		if(yangshi==0) kai_shi=0;	
	}
	if(ysh!=yangshi)
	{
	   yangshi=ysh;
	   qing_huan_chong();
	}	
}

void qufk()	//				取一个方块
{
	for(p=0;p<4;p++)
	{
		G=fangk[xinz][fangx][p];
		for(k=0;k<4;k++)
		{
			if((G&0x01)>0)
			{
				 ttb1.eal[fky+p]&=qufksz[fkx+k];
			}
			G>>=1;	
		}
	}
}

void xiefk()	//			写一个方块
{
	uint fkxie;
	for(k=0;k<4;k++)
	{
		fkxie=fangk[xinz][fangx][k];
		fkxie<<=fkx;
		ttb1.eal[fky+k]|=fkxie;
	}
}



void chanfk()	  //		 产生一个方块
{
   	srand(rand()+fangx+fkx+fky);
	fkx=4;
	fky=18;
	xinz=newxinz;
	fangx=newfangx;
    newxinz=rand()%7;
	newfangx=rand()%4;
}



void manfk()	 // 		 满行处理
{
	G=0;
	for(k=4;k<22;k++)
	{
		if(ttb1.eal[k]==0x0fff)
		{
		G++; 
		ttb1.eal[k]=0;
		}
	}
	delay(5000);
	for(k=4;k<22;k++)
	{
		if(ttb1.eal[k]==0) ttb1.eal[k]=0x0fff;
	}
	delay(5000);
	for(k=4;k<22;k++)
	{
		if(ttb1.eal[k]==0x0fff) ttb1.eal[k]=0;
	}
	delay(5000);
	for(k=4;k<22;k++)
	{
		if(ttb1.eal[k]==0)
		{
			 p=k;
			 for(b=p;b<22;b++)
			 {
			 	  ttb1.eal[b]=ttb1.eal[b+1];
			 }
			 ttb1.eal[22]=0x0c00;
			 k--;
		}
	}
	 if(G==1) TEMP1+=1;
	 if(G==2) TEMP1+=2;
	 if(G==3) TEMP1+=5;
	 if(G==4) TEMP1+=10;
	efenge=TEMP1%10;
	efenshi=TEMP1%100/10; 
	efenbai=TEMP1%1000/100;
	efenqian=TEMP1/1000;	   
}



uchar chongt()	  // 		  方块碰撞检测
{
	b=0;
	temp=0x0000;
	for(k=0;k<4;k++)
	{
	temp=fangk[xinz][fangx][k];
	temp<<=fkx;	
	if((temp+(ttb1.eal[(fky+k)]))!=(temp|(ttb1.eal[(fky+k)]))) b=1;
	}
	return(b);
	
}


void shezhi()	//设置和显示扫描
{
	TH1=0xf5;
	TL1=0Xca;
	for(bianjie=0;bianjie<8;bianjie++)
	{	
		i=ttb1.sjr[bianjie+sscan*8];
		j=ttb1.sjr[bianjie+sscan*8+128];
		k=ttb2.sjg[bianjie+sscan*8];
		b=ttb2.sjg[bianjie+sscan*8+128];					
		for(sudu=0;sudu<8;sudu++)
		{
			p=i; if(((p>>sudu)&0x01)>0) R1=1; else R1=0;
			p=j; if(((j>>sudu)&0x01)>0) R2=1; else R2=0;
			p=k; if(((k>>sudu)&0x01)>0) G1=1; else G1=0;
			p=b; if(((b>>sudu)&0x01)>0) G2=1; else G2=0;
			SHCP=1;
			delay(2);
			SHCP=0;
		}
	}
	P2M0|=0x10;
	STCP=1;
	delay(2);
	STCP=0;	
	scan(sscan);
	P2M0&=0xef;
	if(sscan<15) sscan++; else sscan=0;
	ansdw++;
	if(ansdw==397&&yangshi==3)
	{
		P2M0|=0x10;
		wnian=Read1302(du_nian);
		wyue=Read1302(du_yue);
		wri=Read1302(du_tian);
		wxinq=Read1302(du_xin_qi);
		wshi=Read1302(du_xiao_shi);
		wfen=Read1302(du_fen_zhong);
		P2M0&=0xef;
	}
	if(ansdw>757)
	{
	 	ansdw=0;
		P2M0|=0x10;
		read_ds18b20_1T();
		P2M0&=0xef;
	}
	kai_sh++;
	if(kai_sh>100)
	{
	kai_sh=0;
	P2M0|=0x10;
	biankuang();
	P2M0&=0xef;		
	}
	Real++;
	if(Real>340)
	{
		Real=0;
		if(yangshi==3&&xyz==1)
		{
			P2M0|=0x10;
			if(stop==0) huashidian(); else qushidian();
			P2M0&=0xef;
			stop=~stop;
		}
	}
	/*if((yangshi!=4&&yangshi!=2&&key_qu_ren==0)|(yangshi!=2&&aaajjj==0x40))
	{
		for(sudu=0;sudu<100;sudu++);
		if(key_qu_ren==0|aaajjj==0x40) {aaajjj=0;ysh=2; ysfu=yangshi;}
	}*/
	if(key_qu_ren==0&&key_fan_hiu==0)
	{
		for(sudu=0;sudu<100;sudu++);
		if((key_qu_ren==0&&key_fan_hiu==0)) {aaajjj=0;ysh=2; ysfu=yangshi;}
	}
	if(yangshi!=2&&aaajjj==0x40) {aaajjj=0;ysh=2; ysfu=yangshi;}

	if(yangshi==4)
	{ 
		tcssd++;
		if(tcssd>(500/sssddd))
		{
			tcssd=0;
			efenbai=1;
		}
	} 
}


void chan_shu()	  //参数设置函数
{	
	jishu=1;
	szxh=1;
	qing_hong();
	qing_nv();
	for(jj=0;jj<64;jj++)
	{
		LB[jj]=ajshezhi1[jj];
		LB1[jj]=ajshezhi1[jj+64];
		LB2[jj]=ajshezhi1[jj+128];
	}
	jj=0;
	while(key_jian==0);
	while(key_qu_ren==0);
	yiji=1;
	while(szxh)
	{
		yjszxs();
		while(yiji==4)	//显示设置
		{
			erszxs();
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					if(jishu==1) ysfu=0;
					if(jishu==2) ysfu=1;
					if(jishu==3) ysfu=3;
					if(jishu==4) ysfu=4;  //ttttttttttttttttttttttttttttttttttt
				}
				yiji=1;
				while(key_qu_ren==0);
			
			}
		}
		while(yiji==5)     //参数设置
		{
			erszxs();
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					if(jishu==1) erji=6;
					if(jishu==2) erji=7;
					if(jishu==3) erji=8;
					if(jishu==4) erji=9;
				}
				while(key_qu_ren==0);
				shanji=1;
				
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					yiji=1;
				}
				while(key_fan_hiu==0);
			
			}
			while(erji==6)		//频谱颜色设置
			{
				if(shanji==1)
				{	
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=ajshezhi1[jj];
					}
					qing_hong();
					qing_nv();
					hua_1616(50,23,2,0,0);
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=ajshezhi3[jj+96];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi3[jj+64];
					}					
					gunzhi(30,10000);			
					jishu=shanji;
					shanji=3;
				}
				if(shanji==2)
				{	
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=ajshezhi1[jj];
					}
					qing_hong();
					qing_nv();
					hua_1616(50,23,2,0,0);
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=ajshezhi3[jj+64];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi3[jj+96];
					}					
					gunzhi(30,10000);			
					jishu=shanji;
					shanji=3;
				}
				if(key_jia==0|aaajjj==0x44)
				{
					delay(5000);
					if(key_jia==0|aaajjj==0x44)
					{	aaajjj=0;
						if(jishu==1) shanji=2; else shanji=1;
					}
					while(key_jia==0);
				
				}
				if(key_jian==0|aaajjj==0x43)
				{
					delay(5000);
					if(key_jian==0|aaajjj==0x43)
					{	aaajjj=0;
						if(jishu==1) shanji=2; else shanji=1;
					}
					while(key_jia==0);
				
				}
				if(key_qu_ren==0|aaajjj==0x40)
				{
					delay(5000);
					if(key_qu_ren==0|aaajjj==0x40)
					{	aaajjj=0;
						if(jishu==1) color=1; else color=0;
					}
					while(key_qu_ren==0);
					erji=1;
				
				}
			}
			while(erji==7)	   // 方块设置
			{
				if(shanji==1)
				{	
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=k1616[jj+32];
					}
					qing_hong();
					qing_nv();
					hua_1616(50,23,2,0,0);
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=ajshezhi4[jj+32];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi4[jj];
					}					
					gunzhi(30,10000);			
					jishu=shanji;
					shanji=3;
				}
				if(shanji==2)
				{	
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=k1616[jj+32];
					}
					qing_hong();
					qing_nv();
					hua_1616(50,23,2,0,0);
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=ajshezhi4[jj];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi4[jj+32];
					}					
					gunzhi(30,10000);			
					jishu=shanji;
					shanji=3;
				}
				if(key_jia==0|aaajjj==0x44)
				{
					delay(5000);
					if(key_jia==0|aaajjj==0x44)
					{	aaajjj=0;
						if(jishu==1) shanji=2; else shanji=1;
					}
					while(key_jia==0);
				
				}
				if(key_jian==0|aaajjj==0x43)
				{
					delay(5000);
					if(key_jian==0|aaajjj==0x43)
					{	aaajjj=0;
						if(jishu==1) shanji=2; else shanji=1;
					}
					while(key_jia==0);
				
				}
				if(key_qu_ren==0|aaajjj==0x40)
				{
					delay(5000);
					if(key_qu_ren==0|aaajjj==0x40)
					{	aaajjj=0;
						if(jishu==1) daid=0; else daid=1;
					}
					while(key_qu_ren==0);
					erji=1;
				
				}
			}
			while(erji==8)	   //	万年历设置
			{
				if(shanji==1)
				{
				   for(foo=32;foo<60;foo++)
				   {
				   		for(foo1=5;foo1<26;foo1++)
						{
							qing_dian1(foo,foo1,3);
							qing_dian1(63-foo,foo1,3);
						}
						delay(6000);
				   }
				   for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi1[jj+128];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=0xff;
					}
					gunzhi(30,3000);
					for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi1[jj+160];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=0xff;
					}
					gunzhi(50,3000);
					jishu=shanji;
					shanji=3;
				}
				if(shanji==2)
				{
					for(foo=32;foo<60;foo++)
				   {
				   		for(foo1=5;foo1<26;foo1++)
						{
							qing_dian1(foo,foo1,3);
							qing_dian1(63-foo,foo1,3);
						}
						delay(6000);
				   }
				   for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi4[jj+64];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=0xff;
					}
					gunzhi(30,3000);
					for(jj=0;jj<32;jj++)
					{
						LB[jj+32]=ajshezhi4[jj+96];
					}
					for(jj=0;jj<32;jj++)
					{
						LB[jj]=0xff;
					}
					gunzhi(50,3000);
					jishu=shanji;
					shanji=3;
				}
				if(key_jia==0|aaajjj==0x44)
				{
					delay(5000);
					if(key_jia==0|aaajjj==0x44)
					{	aaajjj=0;
						if(jishu==1) shanji=2; else shanji=1;
					}
					while(key_jia==0);
					
				}
				if(key_jian==0|aaajjj==0x43)
				{
					delay(5000);
					if(key_jian==0|aaajjj==0x43)
					{	aaajjj=0;
						if(jishu==1) shanji=2; else shanji=1;
					}
					while(key_jia==0);
				
				}
				if(key_qu_ren==0|aaajjj==0x40)
				{
					delay(5000);
					if(key_qu_ren==0|aaajjj==0x40)
					{	aaajjj=0;
						if(jishu==1) shanji=4; else shanji=5;
					}
					while(key_qu_ren==0);
					shiji=1;
				
				}
				if(key_fan_hiu==0|aaajjj==0x15)
				{
					delay(5000);
					if(key_fan_hiu==0|aaajjj==0x15)
					{	aaajjj=0;
						erji=1;
					}
					while(key_fan_hiu==0);
					
				}
				while(shanji==4)    //万年历参数
				{
					sj1302();	//时间年月日时分设置
				}
				while(shanji==5)	 //万年历颜色
				{
				   shanji=1;
				}
			}
			while(erji==9)	   //	 贪吃蛇设置
			{
				erji=1;
			}
		}

	}

	yangshi=ysfu;
	ysh=yangshi;
	if(yangshi==0)
	{
		for(i=0;i<64;i++)
		{
			LB[i]=0;
			LB1[i]=0;
			LB2[i]=0;
		}
		for(i=0;i<128;i++)
		{
			ttb1.eal[i]=0;
			ttb2.age[i]=0;
		}
	}
	if(yangshi==1)
	{
		for(p=0;p<64;p++)
		{
			ttb1.eal[p]=0x0c00;
			   
		}
		ttb1.eal[3]=0x0fff;
		ttb1.eal[2]=0x0fff;
		ttb1.eal[1]=0x0fff;
		ttb1.eal[0]=0x0fff;
	}
	if(yangshi==3)
	{
		qing_huan_chong();
	}

}	


void hua_dian(uchar zbx, uchar zby, uchar hnsj)	  //画点中断用
{
	if(zbx<64&&zby<32)
	{
		if(hnsj==1)
		{
			LINE=zby*8+zbx/8;
			ttb1.sjr[LINE]&=huad[zbx%8];
		}
		if(hnsj==2)
		{
			LINE=zby*8+zbx/8;
			ttb2.sjg[LINE]&=huad[zbx%8];
		}
		if(hnsj==3)
		{
			LINE=zby*8+zbx/8;
			ttb1.sjr[LINE]&=huad[zbx%8];
			LINE=zby*8+zbx/8;
			ttb2.sjg[LINE]&=huad[zbx%8];
		}
	}
}



void qing_dian(uchar zbx, uchar zby, uchar hnsj)	  //清点中断用
{
	if(zbx<64&&zby<32)
	{
		if(hnsj==1)
		{
			LINE=zby*8+zbx/8;
			ttb1.sjr[LINE]|=qingd[zbx%8];
		}
		if(hnsj==2)
		{
			LINE=zby*8+zbx/8;
			ttb2.sjg[LINE]|=qingd[zbx%8];
		}
		if(hnsj==3)
		{
			LINE=zby*8+zbx/8;
			ttb1.sjr[LINE]|=qingd[zbx%8];
			LINE=zby*8+zbx/8;
			ttb2.sjg[LINE]|=qingd[zbx%8];
		}
	}
}




void hua_dian1(uchar zbx1, uchar zby1, uchar hnsj1)	  //画点主控用
{
	if(zbx1<64&&zby1<32)
	{
		if(hnsj1==1)
		{
			COUNT1=zby1*8+zbx1/8;
			ttb1.sjr[COUNT1]&=huad[zbx1%8];
		}							  
		if(hnsj1==2)
		{
			COUNT1=zby1*8+zbx1/8;
			ttb2.sjg[COUNT1]&=huad[zbx1%8];
		}
		if(hnsj1==3)
		{
			COUNT1=zby1*8+zbx1/8;
			ttb1.sjr[COUNT1]&=huad[zbx1%8];
			COUNT1=zby1*8+zbx1/8;
			ttb2.sjg[COUNT1]&=huad[zbx1%8];
		}
	}
}



void qing_dian1(uchar zbx1, uchar zby1, uchar hnsj1)	  //清点主控用
{
	if(zbx1<64&&zby1<32)
	{
		if(hnsj1==1)
		{
			COUNT1=zby1*8+zbx1/8;
			ttb1.sjr[COUNT1]|=qingd[zbx1%8];
		}
		if(hnsj1==2)
		{
			COUNT1=zby1*8+zbx1/8;
			ttb2.sjg[COUNT1]|=qingd[zbx1%8];
		}
		if(hnsj1==3)
		{
			COUNT1=zby1*8+zbx1/8;
			ttb1.sjr[COUNT1]|=qingd[zbx1%8];
			COUNT1=zby1*8+zbx1/8;
			ttb2.sjg[COUNT1]|=qingd[zbx1%8];
		}
	}
}




void qing_hong()	   //清零红色
{
	for(jj=8;jj<245;jj+=8)
	{
		ttb1.sjr[jj]|=0xfe;
	}
	for(jj=15;jj<252;jj+=8)
	{
		ttb1.sjr[jj]|=0x7f;
	}
	for(jj=9;jj<247;jj++)
	{
		ttb1.sjr[jj]=0xff;
		if(jj%8==6) jj+=2;
	}

}



void qing_nv()	   //清零绿色
{
	for(jj=8;jj<245;jj+=8)
	{
		ttb2.sjg[jj]|=0xfe;
	}
	for(jj=15;jj<252;jj+=8)
	{
		ttb2.sjg[jj]|=0x7f;
	}
	for(jj=9;jj<247;jj++)
	{
		ttb2.sjg[jj]=0xff;
		if(jj%8==6) jj+=2;
	}
}

void biankuang()	//边框
{	
	kai_shi++;
	if(kai_shi>7)
	{
		kai_shi=0;
	}

	for(G=0;G<64;G++)
	{	
		qing_dian(G,0,3);
		hua_dian(G,0,((G+7-kai_shi)/4)%2+1);
	}
	for(G=0;G<31;G++)
	{
		qing_dian(63,G,3);
		hua_dian(63,G,((G+7-kai_shi)/4)%2+1);
	}
	for(G=0;G<64;G++)
	{	
		qing_dian(G,31,3);
		hua_dian(G,31,((G+kai_shi+5)/4)%2+1);
	}
	for(G=0;G<31;G++)
	{
		qing_dian(0,G,3);
		hua_dian(0,G,((G+kai_shi+5)/4)%2+1);
	}
}


void hua_88(uchar kzbx, uchar kzby, uchar khnsj, uchar kms, uchar fany)	 //画88
{
	if(khnsj==1)
	{
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8]&=~((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8+kzbx/8-1]&=~((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb1.sjr[jj*8+kzbx/8]&=~((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
	}
	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	if(khnsj==2)
	{
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8]&=~((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8+kzbx/8-1]&=~((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb2.sjg[jj*8+kzbx/8]&=~((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if(khnsj==3)
	{
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8]&=~((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8+kzbx/8-1]&=~((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb1.sjr[jj*8+kzbx/8]&=~((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		//@@@@@@@@@@@@@@@@@@@
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8]&=~((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8+kzbx/8-1]&=~((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb2.sjg[jj*8+kzbx/8]&=~((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]&=~((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]&=~((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]&=~((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
	}		
}


void hua_816(uchar kzbx1, uchar kzby1, uchar khnsj1, uchar kms1, uchar fany1)  //画816
{												 
	 hua_88(kzbx1,kzby1-8,khnsj1,kms1,fany1);
	 hua_88(kzbx1,kzby1,khnsj1,kms1+1,fany1);
}


void hua_1616(uchar kzbx2, uchar kzby2, uchar khnsj2, uchar kms2, uchar fany2)	//画1616
{
		hua_88(kzbx2-8,kzby2-8,khnsj2,kms2,fany2);
		hua_88(kzbx2-8,kzby2,khnsj2,kms2+1,fany2);
		hua_88(kzbx2,kzby2-8,khnsj2,kms2+2,fany2);
		hua_88(kzbx2,kzby2,khnsj2,kms2+3,fany2);	
}


void qu_88(uchar kzbx, uchar kzby, uchar khnsj, uchar kms, uchar fany)			//取88
{
	if(khnsj==1)
	{
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8]|=((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8+kzbx/8-1]|=((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb1.sjr[jj*8+kzbx/8]|=((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
	}
	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	if(khnsj==2)
	{
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8]|=((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8+kzbx/8-1]|=((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb2.sjg[jj*8+kzbx/8]|=((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if(khnsj==3)
	{
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8]|=((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb1.sjr[jj*8+kzbx/8-1]|=((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb1.sjr[jj*8+kzbx/8]|=((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb1.sjr[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		//@@@@@@@@@@@@@@@@@@@
		if(kzby<8)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8]|=((~LB[8+kms*8+jj+fany-kzby])>>(8-kzbx));
				}
			}
			if(kzbx>7&&kzbx<72)
			{
				for(jj=0;jj<kzby;jj++)
				{
					ttb2.sjg[jj*8+kzbx/8-1]|=((~LB[8+kms*8+jj+fany-kzby])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<kzby;jj++)
					{
						ttb2.sjg[jj*8+kzbx/8]|=((~LB[8+kms*8+jj+fany-kzby])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>7&&kzby<33)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8;jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8;jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
		if(kzby>32&&kzby<41)
		{
			if(kzbx<8)
			{
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8]|=((~LB[kms*8+jj+fany])>>((8-kzbx)));
				}
			}
			
			if(kzbx>7&&kzbx<72)
			{	
				for(jj=0;jj<8-(kzby-32);jj++)
				{
					ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8]|=((~LB[kms*8+jj+fany])<<((kzbx%8)));
				}
				if(kzbx<64)
				{
					for(jj=0;jj<8-(kzby-32);jj++)
					{
						ttb2.sjg[(kzby-8)*8+jj*8+(kzbx-8)/8+1]|=((~LB[kms*8+jj+fany])>>((8-kzbx%8)));
					}
				}
			}
		}
	}
}


void qu_816(uchar kzbx1, uchar kzby1, uchar khnsj1, uchar kms1, uchar fany1)	 //取816
{												 
	 qu_88(kzbx1,kzby1-8,khnsj1,kms1,fany1);
	 qu_88(kzbx1,kzby1,khnsj1,kms1+1,fany1);
}


void qu_1616(uchar kzbx2, uchar kzby2, uchar khnsj2, uchar kms2, uchar fany2)	 //取1616
{
		qu_88(kzbx2-8,kzby2-8,khnsj2,kms2,fany2);
		qu_88(kzbx2-8,kzby2,khnsj2,kms2+1,fany2);
		qu_88(kzbx2,kzby2-8,khnsj2,kms2+2,fany2);
		qu_88(kzbx2,kzby2,khnsj2,kms2+3,fany2);	
}




void kai_ji()  //开机画面
{
	uchar x1=27,x2=35,x3=65,x4=53,y1=39,y2=1,y3=39,y4=1,fo;
	for(jj=0;jj<64;jj++)
	{
		LB[jj]=k1616[jj];
	}
	for(fo=0;fo<8;fo++)
	{
		qing_hong();
		hua_88(x2,y2,1,1,0);
		hua_88(x4,y4,1,3,0);
		delay(10000);
		x2--;y2++;	
		x4++;y4++;
	}
	for(fo=0;fo<8;fo++)
	{	
		hua_88(x1,y1,1,0,0);
		hua_88(x2,y2,1,1,0);
		hua_88(x3,y3,1,2,0);	
		hua_88(x4,y4,1,3,0);
		x1--;y1--;
		x2--;y2++;
		x3--;y3--;
		if(fo>1) x4--; else x4++;
		y4++;
		delay(10000);
		qing_hong();
	}
	for(fo=0;fo<25;fo++)
	{
		if(fo<10) x1--; else x1++;
		if(fo<22) y1--;	else y1++;
		if(fo<10) x2--;	else x2++;
		if(fo<14) y2++;	else y2--;
		x3--;
		if(fo<22) y3--;	else y3++;
		x4--;
		if(fo<14) y4++;	else y4--;	
		qing_hong();
		hua_88(x1,y1,1,0,0);
		hua_88(x2,y2,1,1,0);
		hua_88(x3,y3,1,2,0);
		hua_88(x4,y4,1,3,0);
		delay(10000);
	}
	x1=0;y1=12;
	for(fo=0;fo<8;fo++)
	{
		qu_88(x1+1,y1,2,4,0);
		hua_88(x1,y1,2,4,0);
		x1++;
		delay(4000);
	}
	 x2=72;y2=20;
	for(fo=0;fo<33;fo++)
	{
		qing_nv();
		qu_88(x1+1,y1,2,4,0);
		hua_88(x1,y1,2,4,0);
		hua_88(x2,y2,2,5,0);
		x1++; x2--;
		delay(4000);
	}
	x1=72;y1=20;
	for(fo=0;fo<25;fo++)
	{
		qu_816(x1+1,y1,2,6,0);
		hua_816(x1,y1,2,6,0);
		x1--;		   
		delay(4000);
	}
	for(fo=0;fo<48;fo++)
	{	
		hua_dian1(fo+8,24,1);
		hua_dian1(55-fo,27,1);
		delay(1000);
	}
	hua_dian1(8,26,1);
	delay(2000);
	hua_dian1(55,25,1);
	hua_dian1(8,25,1);
	delay(2000);
	hua_dian1(55,26,1);
	for(fo=0;fo<46;fo++)
	{	
		hua_dian1(fo+9,25,2);
		hua_dian1(fo+9,26,2);
		delay(10000);
		if(fo==11) delay(60000);
		if(fo==24) {delay(60000);delay(60000);}	
	}
	x1=0;
	for(fo=4;fo<20;fo++)
	{
			fenhang(fo,0);
			delay(10000);
			hangyi(fo-1,1);
			fenhang(fo,2);
			delay(10000);
			hangyi(fo,1);
	}
	for(fo=0;fo<25;fo++)
	{
		hangyi(21,1);
		delay(10000);
		qing_dian1(fo+8,24,3);
		qing_dian1(fo+8,25,3);
		qing_dian1(fo+8,26,3);
		qing_dian1(fo+8,27,3);

		qing_dian1(fo+18,24,3);
		qing_dian1(fo+18,25,3);
		qing_dian1(fo+18,26,3);
		qing_dian1(fo+18,27,3);

		qing_dian1(fo+28,24,3);
		qing_dian1(fo+28,25,3);
		qing_dian1(fo+28,26,3);
		qing_dian1(fo+28,27,3);

		qing_dian1(fo+38,24,3);
		qing_dian1(fo+38,25,3);
		qing_dian1(fo+38,26,3);
		qing_dian1(fo+38,27,3);

		qing_dian1(fo+48,24,3);
		qing_dian1(fo+48,25,3);
		qing_dian1(fo+48,26,3);
		qing_dian1(fo+48,27,3);
	}
}


void hangyi(uchar hsy,uchar kks)     //行上移
{
	uchar hsy1,hsy2;
	for(hsy1=0;hsy1<8;hsy1++)
	{
		if(hsy1==0)
		{
		  	ttb1.sjr[kks*8+hsy1]|=0xfe;
			ttb2.sjg[kks*8+hsy1]|=0xfe;
		}
		if(hsy1>0&&hsy1<7)
		{
			ttb1.sjr[kks*8+hsy1]=0xff;
			ttb2.sjg[kks*8+hsy1]=0xff;
		}
		if(hsy1==7)
		{
			ttb1.sjr[kks*8+hsy1]|=0x7f;
			ttb2.sjg[kks*8+hsy1]|=0x7f;
		}
	}	
	for(hsy1=kks;hsy1<hsy;hsy1++)
	{
		for(hsy2=0;hsy2<8;hsy2++)
		{
			if(hsy2==0)
			{
				ttb1.sjr[hsy1*8+hsy2]=(ttb1.sjr[hsy1*8+8+hsy2]|0x01)&(ttb1.sjr[hsy1*8+hsy2]|0xfe);
				ttb2.sjg[hsy1*8+hsy2]=(ttb2.sjg[hsy1*8+8+hsy2]|0x01)&(ttb2.sjg[hsy1*8+hsy2]|0xfe);
			}
			if(hsy2>0&&hsy2<7)
			{
			ttb1.sjr[hsy1*8+hsy2]=ttb1.sjr[hsy1*8+8+hsy2];
			ttb2.sjg[hsy1*8+hsy2]=ttb2.sjg[hsy1*8+8+hsy2];
			}
			if(hsy2==7)
			{
				ttb1.sjr[hsy1*8+hsy2]=(ttb1.sjr[hsy1*8+8+hsy2]|0x80)&(ttb1.sjr[hsy1*8+hsy2]|0x7f);
				ttb2.sjg[hsy1*8+hsy2]=(ttb2.sjg[hsy1*8+8+hsy2]|0x80)&(ttb2.sjg[hsy1*8+hsy2]|0x7f);
			}
		}
	}	
}


void fenhang(uchar fenh, uchar fenhs)    //分行
{			
	uchar hsy1;						   
	for(hsy1=0;hsy1<8;hsy1++)		   
	{
		if(hsy1==0)
		{
			ttb1.sjr[fenh*8+hsy1-8]&=(ttb1.sjr[fenh*8+hsy1]|fhsz[fenhs])|0x01;
			ttb2.sjg[fenh*8+hsy1-8]&=(ttb2.sjg[fenh*8+hsy1]|fhsz[fenhs])|0x01;
			ttb1.sjr[fenh*8+hsy1]|=(~fhsz[fenhs])&0xfe;
			ttb2.sjg[fenh*8+hsy1]|=(~fhsz[fenhs])&0xfe;
		}
		if(hsy1>0&&hsy1<7)
		{
			ttb1.sjr[fenh*8+hsy1-8]=ttb1.sjr[fenh*8+hsy1]|fhsz[fenhs];
			ttb2.sjg[fenh*8+hsy1-8]=ttb2.sjg[fenh*8+hsy1]|fhsz[fenhs];
			ttb1.sjr[fenh*8+hsy1]|=~fhsz[fenhs];
			ttb2.sjg[fenh*8+hsy1]|=~fhsz[fenhs];
		}
		if(hsy1==7)
		{
			ttb1.sjr[fenh*8+hsy1-8]&=(ttb1.sjr[fenh*8+hsy1]|fhsz[fenhs])|0x80;
			ttb2.sjg[fenh*8+hsy1-8]&=(ttb2.sjg[fenh*8+hsy1]|fhsz[fenhs])|0x80;
			ttb1.sjr[fenh*8+hsy1]|=(~fhsz[fenhs])&0x7f;
			ttb2.sjg[fenh*8+hsy1]|=(~fhsz[fenhs])&0x7f;
		}
	}
}

void wanln()	//万年历显示
{
	uchar bbf,yys;
	qing_hong();
	qing_nv();
	delay(65530);
	delay(65530);
	delay(65530);
	for(jj=0;jj<64;jj++)
	{
		LB[jj]=k816[jj];
		LB1[jj]=k816[jj+64];
		LB2[jj]=k816[jj+128];
	}
	shi1=wshi/16;
	shi2=wshi%16;
	fen1=wfen/16;
	fen2=wfen%16;
	hua_816(34,15,2,fen2*2,0);
	hua_816(27,15,1,fen1*2,0);
	hua_816(16,15,2,shi2*2,0);
	hua_816(9,15,3,shi1*2,0);

	hua_dian1(52,11,1);
	hua_dian1(53,11,1);
	hua_dian1(52,12,1);
	hua_dian1(53,12,1);
	xyz=1;
	while(yangshi==3&&ysh==3)
	{
		shiwen();
		bbf++;
		if(bbf>3) bbf=1;
		yys++;
		if(yys>6) yys=1;
		xian_xiao(1,bbf,yys);
		delay(65530);
		delay(65530);
		delay(65530);
		delay(65530);
		kaij++;
		if(kaij>8) {kaij=1; yys++;};
		xian_xiao(2,1,kaij);	
	}
	if(ysh!=yangshi)
	{
	   yangshi=ysh;
	   qing_huan_chong();
	}
}


void xian_xiao(uchar xiaox,uchar bufen,uchar yangss)	//万年历动画显示和消失
{
	if(xiaox==1)   
	{
		if(bufen==1)	 
		{
			if(yangss==1)	 
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(16,29,3,4,0);
				delay(30000);
				hua_816(24,29,2,0,0);
				delay(30000);
				hua_816(32,29,1,nian1*2,0);
				delay(30000);
				hua_816(40,29,2,nian2*2,0);
				delay(30000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj];
					LB1[jj]=k1616[jj+64];
					LB2[jj]=k1616[jj+128];
				}
				hua_1616(56,29,3,8,0);
			}
			if(yangss==2)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj];
					LB1[jj]=k1616[jj+64];
					LB2[jj]=k1616[jj+128];
				}
				hua_1616(56,29,3,8,0);
				delay(30000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(40,29,2,nian2*2,0);
				delay(30000);
				hua_816(32,29,1,nian1*2,0);
				delay(30000);
				hua_816(24,29,2,0,0);
				delay(30000);
				hua_816(16,29,3,4,0);
			}
			if(yangss==3)
			{
				 for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(16,foo+1,3,4,0);
					hua_816(16,foo,3,4,0);
					delay(3000);	
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(24,foo+1,2,0,0);					
					hua_816(24,foo,2,0,0);
					delay(3000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(32,foo+1,1,nian1*2,0);					
					hua_816(32,foo,1,nian1*2,0);
					delay(3000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(40,foo+1,2,nian2*2,0);					
					hua_816(40,foo,2,nian2*2,0);
					delay(3000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj];
					LB1[jj]=k1616[jj+64];
					LB2[jj]=k1616[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(56,foo+1,3,8,0);					
					hua_1616(56,foo,3,8,0);
					delay(3000);
				}
			}
			if(yangss==4)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj];
					LB1[jj]=k1616[jj+64];
					LB2[jj]=k1616[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(56,foo+1,3,8,0);					
					hua_1616(56,foo,3,8,0);
					delay(3000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(40,foo+1,2,nian2*2,0);					
					hua_816(40,foo,2,nian2*2,0);
					delay(3000);
				}
				
				for(foo=48;foo!=29;foo--)
				{
					qu_816(32,foo+1,1,nian1*2,0);					
					hua_816(32,foo,1,nian1*2,0);
					delay(3000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(24,foo+1,2,0,0);					
					hua_816(24,foo,2,0,0);
					delay(3000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(16,foo+1,3,4,0);
					hua_816(16,foo,3,4,0);
					delay(3000);	
				}
			}
			if(yangss==5)
			{
				 for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}								
				hua_816(32,29,1,nian1*2,0);				
				hua_816(40,29,2,nian2*2,0);
				delay(60000);
				hua_816(24,29,2,0,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
				}
				hua_816(49,29,3,0,0);
				delay(60000);				
				hua_816(57,29,3,2,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(16,29,3,4,0);
			}
			if(yangss==6)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(16,29,3,4,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
				}
				hua_816(57,29,3,2,0);
				delay(60000);
				hua_816(49,29,3,0,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(24,29,2,0,0);
				delay(60000);
				hua_816(32,29,1,nian1*2,0);				
				hua_816(40,29,2,nian2*2,0);				
			}
		}
		if(bufen==2)  
		{
			if(yangss==1)	 
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(9,29,2,yue1*2,0);
				delay(30000);
				hua_816(17,29,3,yue2*2,0);
				delay(30000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_1616(33,30,1,4,0);
				delay(30000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(40,29,2,ri1*2,0);
				delay(30000);
				hua_816(48,29,1,ri2*2,0);
				delay(30000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_1616(63,30,3,8,0);
				
			}
			if(yangss==2)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_1616(63,30,3,8,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}				
				hua_816(48,29,1,ri2*2,0);
				delay(30000);
				hua_816(40,29,2,ri1*2,0);
				delay(30000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_1616(33,30,1,4,0);
				delay(30000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(17,29,3,yue2*2,0);				
				delay(30000);
				hua_816(9,29,2,yue1*2,0);
			}
			if(yangss==3)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(9,foo+1,2,yue1*2,0);
					hua_816(9,foo,2,yue1*2,0);
					delay(2000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(17,foo+1,3,yue2*2,0);
					hua_816(17,foo,3,yue2*2,0);
					delay(2000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(33,foo+1,1,4,0);
					hua_1616(33,foo,1,4,0);
					delay(2000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(40,foo+1,2,ri1*2,0);
					hua_816(40,foo,2,ri1*2,0);
					delay(2000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(48,foo+1,1,ri2*2,0);
					hua_816(48,foo,1,ri2*2,0);
					delay(2000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(63,foo+1,3,8,0);					
					hua_1616(63,foo,3,8,0);
					delay(2000);
				}
			}
			if(yangss==4)
			{
					for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(63,foo+1,3,8,0);					
					hua_1616(63,foo,3,8,0);
					delay(2000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}				
				for(foo=48;foo!=29;foo--)
				{
					qu_816(48,foo+1,1,ri2*2,0);
					hua_816(48,foo,1,ri2*2,0);
					delay(2000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(40,foo+1,2,ri1*2,0);
					hua_816(40,foo,2,ri1*2,0);
					delay(2000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(33,foo+1,1,4,0);
					hua_1616(33,foo,1,4,0);
					delay(2000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}				
				for(foo=48;foo!=29;foo--)
				{
					qu_816(17,foo+1,3,yue2*2,0);
					hua_816(17,foo,3,yue2*2,0);
					delay(2000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_816(9,foo+1,2,yue1*2,0);
					hua_816(9,foo,2,yue1*2,0);
					delay(2000);
				}				
			
			}
			if(yangss==5)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(40,29,2,ri1*2,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_816(33,30,1,6,0);
				delay(60000);
				hua_816(25,30,1,4,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(48,29,1,ri2*2,0);
				delay(60000);
				hua_816(17,29,3,yue2*2,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_816(55,30,3,8,0);
				delay(60000);
				hua_816(63,30,3,10,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				 hua_816(9,29,2,yue1*2,0);
			}
			if(yangss==6)
			{
				 for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				 hua_816(9,29,2,yue1,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_816(63,30,3,10,0);
				delay(60000);
				hua_816(55,30,3,8,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(17,29,3,yue2*2,0);
				delay(60000);
				hua_816(48,29,1,ri2*2,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+64];
					LB1[jj]=k1616[jj+128];
				}
				hua_816(25,30,1,4,0);
				delay(60000);
				hua_816(33,30,1,6,0);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
				hua_816(40,29,2,ri1*2,0);	
			}
		}
		if(bufen==3)	
		{
			 if(yangss==1)	
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}
				hua_1616(24,30,2,0,0);
				delay(60000);
				hua_1616(40,30,1,4,0);
				delay(60000);
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					hua_1616(56,30,3,(xinqi-1)*4,0);
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					hua_1616(56,30,3,0,0);
				}
			}
			if(yangss==2)
			{
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					hua_1616(56,30,3,(xinqi-1)*4,0);
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					hua_1616(56,30,3,0,0);
				}
				delay(60000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}				
				hua_1616(40,30,1,4,0);
				delay(60000);
				hua_1616(24,30,2,0,0);
				delay(60000);
			}
			if(yangss==3)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(24,foo+1,2,0,0);
					hua_1616(24,foo,2,0,0);
					delay(3000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(40,foo+1,1,4,0);
					hua_1616(40,foo,1,4,0);
					delay(3000);
				}
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					for(foo=48;foo!=29;foo--)
					{
						qu_1616(56,foo+1,3,(xinqi-1)*4,0);
						hua_1616(56,foo,3,(xinqi-1)*4,0);
						delay(3000);
					}
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					for(foo=48;foo!=29;foo--)
					{
						qu_1616(56,foo+1,3,0,0);
						hua_1616(56,foo,3,0,0);
						delay(3000);
					}
				}
			}
			if(yangss==4)
			{
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					for(foo=48;foo!=29;foo--)
					{
						qu_1616(56,foo+1,3,(xinqi-1)*4,0);
						hua_1616(56,foo,3,(xinqi-1)*4,0);
						delay(3000);
					}
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					for(foo=48;foo!=29;foo--)
					{
						qu_1616(56,foo+1,3,0,0);
						hua_1616(56,foo,3,0,0);
						delay(3000);
					}
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}				
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(40,foo+1,1,4,0);
					hua_1616(40,foo,1,4,0);
					delay(3000);
				}
				for(foo=48;foo!=29;foo--)
				{
					qu_1616(24,foo+1,2,0,0);
					hua_1616(24,foo,2,0,0);
					delay(3000);
				}
			}
			if(yangss==5)
			{
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}
				hua_1616(40,30,1,4,0);
				delay(60000);
				hua_816(24,30,2,2,0);
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					hua_816(48,30,3,(xinqi-1)*4,0);
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					hua_816(48,30,3,0,0);
				}
				delay(60000);
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					hua_816(56,30,3,(xinqi-1)*4+2,0);
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					hua_816(56,30,3,2,0);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}
				hua_816(16,30,2,0,0);
			}
			if(yangss==6)
			{
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					hua_816(56,30,3,(xinqi-1)*4+2,0);
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					hua_816(56,30,3,2,0);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}
				hua_816(16,30,2,0,0);
				delay(60000);
				hua_816(24,30,2,2,0);
				if(xinqi<7)
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=xinq[jj];
						LB1[jj]=xinq[jj+64];
						LB2[jj]=xinq[jj+128];
					}
					hua_816(48,30,3,(xinqi-1)*4,0);
				}
				else
				{
					for(jj=0;jj<64;jj++)
					{
						LB[jj]=k1616[jj+128];
					}
					hua_816(48,30,3,0,0);
				}
				delay(60000);
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k1616[jj+160];
				}
				hua_1616(40,30,1,4,0);
				
				
			}
		}
	}
	if(xiaox==2)	  
	{
		if(bufen>0&&bufen<4)	  
		{
			 if(yangss==1)	
			{
				for(foo=1;foo<63;foo++)
				{
					for(jj=13;jj<31;jj++)
					{
						qing_dian1(foo,jj,3);
					}
					delay(3000);
				}
			}
			if(yangss==2)
			{
				for(foo=62;foo>0;foo--)
				{
					for(jj=13;jj<31;jj++)
					{
						qing_dian1(foo,jj,3);
					}
					delay(3000);
				}
			}
			if(yangss==3)
			{
				for(foo=14;foo<31;foo++)
				{
						fenhang(foo,0);
						delay(5000);
						hangyi(foo-1,13);
						fenhang(foo,2);
						delay(5000);
						hangyi(foo,13);
				}
				for(foo=0;foo<19;foo++)
				{
					hangyi(30,13);
				}
			}
			if(yangss==4)
			{
				for(foo=62;foo>30;foo--)
				{
					for(jj=13;jj<31;jj++)
					{
						qing_dian1(foo-30,jj,3);
						qing_dian1(93-foo,jj,3);
					}
					delay(6000);
				}
			}
			if(yangss==5)
			{
				for(foo=62;foo>0;foo--)
				{
					for(jj=13;jj<22;jj++)
					{
						qing_dian1(foo,jj,3);
						qing_dian1(63-foo,jj+9,3);
					}
					delay(3000);
				}
			}
			if(yangss==6)
			{
				for(foo=13;foo<31;foo++)
				{
					for(jj=1;jj<63;jj++)
					{
						qing_dian1(jj,foo,3);
					}
					delay(10000);
				}
			}
			if(yangss==7)
			{
				for(foo=13;foo<31;foo++)
				{
					for(jj=1;jj<55;jj++)
					{
						qing_dian1(jj,foo,3);
						qing_dian1(jj+8,43-foo,3);
						qing_dian1(55,foo,3);
						qing_dian1(56,foo,3);
						if(jj%8==0) jj+=8;
					}
					delay(10000);
				}
			}
			if(yangss==8)
			{
				for(foo=22;foo<31;foo++)
				{
					for(jj=1;jj<63;jj++)
					{
						qing_dian1(jj,foo,3);
						qing_dian1(jj,43-foo,3);
					}
					delay(20000);
				}
			}
		}
	}
}


void shiwen()		  //显示温度
{
	uchar fo;
	for(jj=0;jj<64;jj++)
	{
		LB[jj]=k816[jj];
		LB1[jj]=k816[jj+64];
		LB2[jj]=k816[jj+128];
	}
	TR1=0;
	P2M0|=0x10;
	qu_816(44,15,1,efenbai*2,0);
	efenbai=wen/100;
	hua_816(44,15,1,efenbai*2,0);
	P2M0&=0xef;
	TR1=1;
	TR1=0;
	P2M0|=0x10;
	qu_816(51,15,2,efenshi*2,0);
	efenshi=wen%100/10;
	hua_816(51,15,2,efenshi*2,0);
	P2M0&=0xef;
	TR1=1;		
	TR1=0;
	P2M0|=0x10;									
	qu_816(62,15,3,efenge*2,0);
	efenge=wen%10;
	hua_816(62,15,3,efenge*2,0);
	P2M0&=0xef;
	TR1=1;

	fen4=wfen%16;
	if(fen4!=fen2)
	{
		for(fo=0;fo<16;fo++)
		{
		 	qu_816(34,15,2,fen2*2,fo);
			hua_816(34,15,2,fen2*2,fo+1);
			delay(10000);
		}
		fen2=fen4;
	}
	fen3=wfen/16;
	if(fen3!=fen1)
	{
		if(fen3>0)
		{
			for(fo=0;fo<16;fo++)
			{
			 	qu_816(27,15,1,fen1*2,fo);
				hua_816(27,15,1,fen1*2,fo+1);
				delay(10000);
			}
		}
		if(fen3==0)
		{
			for(jj=0;jj<16;jj++)
			{
				LB1[jj+32]=k816[jj];
			}
			for(fo=0;fo<16;fo++)
			{
			 	qu_816(27,15,1,fen1*2,fo);
				hua_816(27,15,1,fen1*2,fo+1);
				delay(10000);
			}
			for(jj=0;jj<64;jj++)
			{
				LB[jj]=k816[jj];
				LB1[jj]=k816[jj+64];
				LB2[jj]=k816[jj+128];
			}
		}
		fen1=fen3;

	}
	shi4=wshi%16;
	if(shi4!=shi2)
	{
		if(shi3!=2)
		{
			for(fo=0;fo<16;fo++)
			{
			 	qu_816(16,15,2,shi2*2,fo);
				hua_816(16,15,2,shi2*2,fo+1);
				delay(10000);
			}
		}
		if(shi3==2)
		{
			if(shi4!=0)
			{
				for(fo=0;fo<16;fo++)
				{
				 	qu_816(16,15,2,shi2*2,fo);
					hua_816(16,15,2,shi2*2,fo+1);
					delay(10000);
				}
			}
			if(shi4==0)
			{
				for(jj=0;jj<16;jj++)
				{

					LB1[jj]=k816[jj];;
				}
				for(fo=0;fo<16;fo++)
				{
				 	qu_816(16,15,2,shi2*2,fo);
					hua_816(16,15,2,shi2*2,fo+1);
					delay(10000);
				}
				for(jj=0;jj<64;jj++)
				{
					LB[jj]=k816[jj];
					LB1[jj]=k816[jj+64];
					LB2[jj]=k816[jj+128];
				}
			}
		}
		shi2=shi4;
	}
	shi3=wshi/16;
	if(shi3!=shi1)
	{
		if(shi3>0)
		{
			for(fo=0;fo<16;fo++)
			{
			 	qu_816(9,15,3,shi1*2,fo);
				hua_816(9,15,3,shi1*2,fo+1);
				delay(10000);
			}
		}
		if(shi3==0)
		{
			for(jj=0;jj<16;jj++)
			{
				LB[jj+48]=k816[jj];
			}
			for(fo=0;fo<16;fo++)
			{
			 	qu_816(9,15,3,shi1*2,fo);
				hua_816(9,15,3,shi1*2,fo+1);
				delay(10000);
			}
			for(jj=0;jj<64;jj++)
			{
				LB[jj]=k816[jj];
				LB1[jj]=k816[jj+64];
				LB2[jj]=k816[jj+128];
			}	
		}
		shi1=shi3;
	}		
	nian1=wnian/16;		
	nian2=wnian%16;
	yue1=wyue/16;
	yue2=wyue%16;
	ri1=wri/16;
	ri2=wri%16;
	xinqi=wxinq%16;	
}


void huashidian()	  //画时间闪点
{
	hua_dian(17,4,2);
	hua_dian(17,5,2);
	hua_dian(18,4,2);
	hua_dian(18,5,2);

	hua_dian(17,9,2);
	hua_dian(17,10,2);
	hua_dian(18,9,2);
	hua_dian(18,10,2);
}



void qushidian()	  //取时间闪点
{
	qing_dian(17,4,2);
	qing_dian(17,5,2);
	qing_dian(18,4,2);
	qing_dian(18,5,2);
	
	qing_dian(17,9,2);
	qing_dian(17,10,2);
	qing_dian(18,9,2);
	qing_dian(18,10,2);
}

void qing_huan_chong()		 //清缓冲
{
	for(i=0;i<64;i++)
	{
		LB[i]=0xff;
		LB1[i]=0xff;
		LB2[i]=0xff;
	}
	for(i=0;i<128;i++)
	{
		ttb1.eal[i]=0xffff;
		ttb2.age[i]=0xffff;
	}
}

void yjszxs()		  //一级设置显示
{
	if(yiji==1)
	{
		for(foo=1;foo<24;foo++)
		{
				fenhang(foo,0);
				delay(5000);
				hangyi(foo-1,1);
				fenhang(foo,2);
				delay(5000);
				hangyi(foo,1);
		}
		for(foo=0;foo<24;foo++)
		{
			hangyi(23,1);
		}
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=ajshezhi1[jj+64];
			LB1[jj]=ajshezhi1[jj+192];
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(17,foo+1,2,0,0);
			hua_1616(17,foo,2,0,0);
			delay(1500);
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(32,foo+1,2,4,0);
			hua_1616(32,foo,2,4,0);
			delay(1500);
		}
		 for(foo=48;foo>22;foo--)
		{
			qu_1616(48,foo+1,2,8,0);
			hua_1616(48,foo,2,8,0);
			delay(1500);
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(63,foo+1,2,12,0);
			hua_1616(63,foo,2,12,0);
			delay(1500);
		}
		jishu=yiji;
		yiji=3;			
	}
	if(yiji==2)
	{
		for(foo=1;foo<24;foo++)
		{
				fenhang(foo,0);
				delay(5000);
				hangyi(foo-1,1);
				fenhang(foo,2);
				delay(5000);
				hangyi(foo,1);
		}
		for(foo=0;foo<24;foo++)
		{
			hangyi(23,1);
		}
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=ajshezhi1[jj+128];
			LB1[jj]=ajshezhi1[jj+192];
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(17,foo+1,2,0,0);
			hua_1616(17,foo,2,0,0);
			delay(1500);
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(33,foo+1,2,4,0);
			hua_1616(33,foo,2,4,0);
			delay(1500);
		}
		 for(foo=48;foo>22;foo--)
		{
			qu_1616(49,foo+1,2,8,0);
			hua_1616(49,foo,2,8,0);
			delay(1500);
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(63,foo+1,2,12,0);
			hua_1616(63,foo,2,12,0);
			delay(1500);
		}
		jishu=yiji;
		yiji=3;			
	}
	
	if(key_jian==0|aaajjj==0x43)
	{
		delay(5000);
		if(key_jian==0|aaajjj==0x43)
		{
			if(jishu==1) yiji=2; else yiji=1;
			aaajjj=0;

		}
		while(key_jian==0);
		
	}
	if(key_jia==0|aaajjj==0x44)
	{
		delay(5000);
		if(key_jia==0|aaajjj==0x44)
		{
			if(jishu==1) yiji=2; else yiji=1;
			aaajjj=0;

		}
		while(key_jia==0);
		
	}
	if(key_fan_hiu==0|aaajjj==0x15)
	{
		delay(5000);
		if(key_fan_hiu==0|aaajjj==0x15)
		{
			szxh=0;
			aaajjj=0;
		}
		while(key_fan_hiu==0);
		
	}
	if(key_qu_ren==0|aaajjj==0x40)
	{
		delay(5000);
		if(key_qu_ren==0|aaajjj==0x40)
		{
			for(foo=1;foo<24;foo++)
			{
					fenhang(foo,0);
					delay(5000);
					hangyi(foo-1,1);
					fenhang(foo,2);
					delay(5000);
					hangyi(foo,1);
			}
			for(foo=0;foo<24;foo++)
			{
				hangyi(23,1);
			}
			if(jishu==1) yiji=4; else yiji=5;
			erji=1;
			aaajjj=0;
		}
		while(key_qu_ren==0);
		
	}
}

void erszxs()		  //二级设置显示
{
	if(erji==1)
	{
		for(foo=1;foo<63;foo++)
		{
			for(foo1=6;foo1<24;foo1++)
			{
				qing_dian1(foo,foo1,3);
			}
			delay(3000);
		}
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=ajshezhi2[jj];
			LB1[jj]=ajshezhi2[jj+64];
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(30,foo+1,2,0,0);
			hua_1616(30,foo,2,0,0);
			delay(1500);
		}
		for(foo=0;foo<24;foo++)
		{
			qu_1616(50,foo-1,2,4,0);
			hua_1616(50,foo,2,4,0);
			delay(1500);
		}

		jishu=erji;
		erji=5;
	}
	if(erji==2)
	{
		for(foo=62;foo>0;foo--)
		{
			for(foo1=6;foo1<24;foo1++)
			{
				qing_dian1(foo,foo1,3);
			}
			delay(3000);
		}
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=ajshezhi2[jj+64];
			LB1[jj]=ajshezhi2[jj+128];
		}
		for(foo=0;foo<31;foo++)
		{
			qu_1616(foo-1,23,2,0,0);
			hua_1616(foo,23,2,0,0);
			delay(1500);
		}
		for(foo=80;foo>49;foo--)
		{
			qu_1616(foo+1,23,2,4,0);
			hua_1616(foo,23,2,4,0);
			delay(1500);
		}

		jishu=erji;
		erji=5;
	}
	if(erji==3)
	{
		for(foo=25;foo>4;foo--)
		{
			for(foo1=1;foo1<63;foo1++)
			{
				qing_dian1(foo1,foo,3);
			}
			delay(5000);
		}
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=ajshezhi2[jj+128];					
		}
		for(jj=0;jj<32;jj++)
		{
			LB1[jj]=ajshezhi2[jj+192];
		}
		for(foo=0;foo<24;foo++)
		{
			qu_1616(23,foo-1,2,0,0);
			hua_1616(23,foo,2,0,0);
			delay(1500);
		}
		for(foo=0;foo<24;foo++)
		{
			qu_1616(40,foo-1,2,4,0);
			hua_1616(40,foo,2,4,0);
			delay(1500);
		}
		for(foo=0;foo<24;foo++)
		{
			qu_1616(57,foo-1,2,8,0);
			hua_1616(57,foo,2,8,0);
			delay(1500);
		}
		jishu=erji;
		erji=5;
	}
	if(erji==4)
	{
		for(foo=25;foo>4;foo--)
		{
			for(foo1=1;foo1<63;foo1++)
			{
				qing_dian1(foo1,foo,3);
			}
			delay(5000);
		}
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=ajshezhi3[jj+128];					
		}
		for(jj=0;jj<32;jj++)
		{
			LB1[jj]=ajshezhi3[jj+192];
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(23,foo+1,2,0,0);
			hua_1616(23,foo,2,0,0);
			delay(1500);
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(40,foo+1,2,4,0);
			hua_1616(40,foo,2,4,0);
			delay(1500);
		}
		for(foo=48;foo>22;foo--)
		{
			qu_1616(57,foo+1,2,8,0);
			hua_1616(57,foo,2,8,0);
			delay(1500);
		}
		jishu=erji;
		erji=5;
	}
	if(key_jia==0|aaajjj==0x44)
	{
		delay(5000);
		if(key_jia==0|aaajjj==0x44)
		{	aaajjj=0;
			if(jishu<4) jishu++; else jishu=1;
			erji=jishu;
		}
		while(key_jia==0);
	
	}
	if(key_jian==0|aaajjj==0x43)
	{
		delay(5000);
		if(key_jian==0|aaajjj==0x43)
		{	aaajjj=0;
			if(jishu>1) jishu--; else jishu=4;
			erji=jishu;
		}
		while(key_jian==0);
		
	}
}

void gunzhi(uchar zzzz,uint zzz)  //翻字
{
	for(foo1=0;foo1<16;foo1++)
	{
		qu_1616(zzzz,23,2,0,0);
		for(foo=0;foo<15;foo++)
		{
			LB[foo]=LB[foo+1];
			LB[foo+16]=LB[foo+17];
		}
		LB[15]=LB[32];
		LB[31]=LB[48];
		for(foo=32;foo<47;foo++)
		{
			LB[foo]=LB[foo+1];
			LB[foo+16]=LB[foo+17];
		}
		hua_1616(zzzz,23,2,0,0);
		delay(zzz);
	 }
}


void sjcscsh()	  //时间参数初始化
{
	for(jj=0;jj<64;jj++)
	{
		LB[jj]=k816[jj];
		LB1[jj]=k816[jj+64];
		LB2[jj]=k816[jj+128];
	}
	for(foo=1;foo<63;foo++)
   {
   		for(foo1=1;foo1<31;foo1++)
		{
			qing_dian1(foo,foo1,3);
		}
		delay(3000);
   }
	TR1=0;
	P2M0|=0x10;
	wnian=Read1302(du_nian);
	wyue=Read1302(du_yue);
	wri=Read1302(du_tian);
	wxinq=Read1302(du_xin_qi);
	wshi=Read1302(du_xiao_shi);
	wfen=Read1302(du_fen_zhong);
	P2M0&=0xef;
	TR1=1;
	nian1=wnian/16;		
	nian2=wnian%16;
	yue1=wyue/16;
	yue2=wyue%16;
	ri1=wri/16;
	ri2=wri%16;
	xinqi=wxinq%16;
	shi1=wshi/16;
	shi2=wshi%16;
	fen1=wfen/16;
	fen2=wfen%16;
	hua_816(8,17,2,4,0);
	delay(20000);
	hua_816(15,17,2,0,0);
	delay(20000);
	hua_816(22,17,2,nian1*2,0);
	delay(20000);
	hua_816(29,17,2,nian2*2,0);
	delay(20000);

	hua_dian1(29,9,1);
	hua_dian1(30,9,1);
	hua_dian1(31,9,1);
	hua_dian1(29,10,1);
	hua_dian1(30,10,1);
	hua_dian1(31,10,1);
	delay(20000);
	hua_816(39,17,2,yue1*2,0);
	delay(20000);
	hua_816(46,17,2,yue2*2,0);
	delay(20000);
	hua_dian1(46,9,1);
	hua_dian1(47,9,1);
	hua_dian1(48,9,1);
	hua_dian1(46,10,1);
	hua_dian1(47,10,1);
	hua_dian1(48,10,1);
	delay(20000);
	hua_816(56,17,2,ri1*2,0);
	delay(20000);
	hua_816(63,17,2,ri2*2,0);
	delay(20000);
	hua_816(11,31,2,shi1*2,0);
	delay(20000);
	hua_816(19,31,2,shi2*2,0);
	delay(20000);
	hua_dian1(20,20,1);
	hua_dian1(21,20,1);
	hua_dian1(20,21,1);
	hua_dian1(21,21,1);

	hua_dian1(20,25,1);
	hua_dian1(21,25,1);
	hua_dian1(20,26,1);
	hua_dian1(21,26,1);
	delay(20000);
	hua_816(30,31,2,fen1*2,0);
	delay(20000);
	hua_816(38,31,2,fen2*2,0);
	delay(20000);
	if(wxinq==7)
	{
	   for(jj=0;jj<32;jj++)
		{
			LB[jj]=xinq[jj+192];
		}
		hua_1616(59,31,2,0,0);
	}
	else
	{
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=xinq[jj];
			LB1[jj]=xinq[jj+64];
			LB2[jj]=xinq[jj+128];
		}
		hua_1616(59,31,2,wxinq*4-4,0);
	}
	for(jj=0;jj<64;jj++)
	{
		LB[jj]=k816[jj];
		LB1[jj]=k816[jj+64];
		LB2[jj]=k816[jj+128];
	}
	shiji=2;
}
void sj1302()	  //时间年月日时分设置
{
	if(shiji==1)
	{
		sjcscsh();
	}
	while(shiji==2)
	{
		qu_816(22,17,2,nian1*2,0);
		hua_816(22,17,1,nian1*2,0);
		while(shiji==2)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(nian1<9) 
					{	
						for(foo=1;foo<17;foo++)
   						{
							qu_816(22,17,1,nian1*2,foo-1);
							hua_816(22,17,1,nian1*2,foo);
							delay(10000);
						}
						nian1++;
					}
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(nian1>0)
					{					
						for(foo=16;foo>0;foo--)
   						{
							qu_816(22,17,1,(nian1-1)*2,foo);
							hua_816(22,17,1,(nian1-1)*2,foo-1);
							delay(10000);
						}
						nian1--;
					}
				}
				while(key_jian==0);
				
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
				
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(22,17,1,nian1*2,0);
					hua_816(22,17,2,nian1*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==3)
	{
	   qu_816(29,17,2,nian2*2,0);
		hua_816(29,17,1,nian2*2,0);
		while(shiji==3)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(nian2<9) 
					{											
						for(foo=1;foo<17;foo++)
   						{
							qu_816(29,17,1,nian2*2,foo-1);
							hua_816(29,17,1,nian2*2,foo);
							delay(10000);
						}
						nian2++;
					}
				}
				while(key_jia==0);
				
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(nian2>0)
					{					
						for(foo=16;foo>0;foo--)
   						{
							qu_816(29,17,1,(nian2-1)*2,foo);
							hua_816(29,17,1,(nian2-1)*2,foo-1);
							delay(10000);
						}
						nian2--;
					}
				}
				while(key_jian==0);
				
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
				
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(29,17,1,nian2*2,0);
					hua_816(29,17,2,nian2*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==4)
	{
		qu_816(39,17,2,yue1*2,0);
		hua_816(39,17,1,yue1*2,0);
		while(shiji==4)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(yue1<1) 
					{	
						for(foo=1;foo<17;foo++)
   						{
							qu_816(39,17,1,yue1*2,foo-1);
							hua_816(39,17,1,yue1*2,foo);
							delay(10000);
						}
						yue1++;
					}
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(yue1>0)
					{					
						for(foo=16;foo>0;foo--)
   						{
							qu_816(39,17,1,(yue1-1)*2,foo);
							hua_816(39,17,1,(yue1-1)*2,foo-1);
							delay(10000);
						}
						yue1--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
				
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(39,17,1,yue1*2,0);
					hua_816(39,17,2,yue1*2,0);
				}
				while(key_qu_ren==0);
												
			}
		}
	}
	while(shiji==5)
	{
	   qu_816(46,17,2,yue2*2,0);
		hua_816(46,17,1,yue2*2,0);
		while(shiji==5)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(yue2<9) 
					{	
						for(foo=1;foo<17;foo++)
   						{
							qu_816(46,17,1,yue2*2,foo-1);
							hua_816(46,17,1,yue2*2,foo);
							delay(10000);
						}
						yue2++;
					}
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(yue2>0)
					{					
						for(foo=16;foo>0;foo--)
   						{
							qu_816(46,17,1,(yue2-1)*2,foo);
							hua_816(46,17,1,(yue2-1)*2,foo-1);
							delay(10000);
						}
						yue2--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
			
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(46,17,1,yue2*2,0);
					hua_816(46,17,2,yue2*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==6)
	{
		qu_816(56,17,2,ri1*2,0);
		hua_816(56,17,1,ri1*2,0);
		while(shiji==6)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(shi1<3) 
					{	
						for(foo=1;foo<17;foo++)
   						{
							qu_816(56,17,1,ri1*2,foo-1);
							hua_816(56,17,1,ri1*2,foo);
							delay(10000);
						}
						ri1++;
					}
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(ri1>0)
					{
						for(foo=16;foo>0;foo--)
   						{
							qu_816(56,17,1,(ri1-1)*2,foo);
							hua_816(56,17,1,(ri1-1)*2,foo-1);
							delay(10000);
						}
						ri1--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
			
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(56,17,1,ri1*2,0);
					hua_816(56,17,2,ri1*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==7)
	{
		qu_816(63,17,2,ri2*2,0);
		hua_816(63,17,1,ri2*2,0);
		while(shiji==7)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(shi1<9) 
					{	
						for(foo=1;foo<17;foo++)
   						{
							qu_816(63,17,1,ri2*2,foo-1);
							hua_816(63,17,1,ri2*2,foo);
							delay(10000);
						}
						ri2++;
					}
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(ri2>0)
					{
						for(foo=16;foo>0;foo--)
   						{
							qu_816(63,17,1,(ri2-1)*2,foo);
							hua_816(63,17,1,(ri2-1)*2,foo-1);
							delay(10000);
						}
						ri2--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
			
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(63,17,1,ri2*2,0);
					hua_816(63,17,2,ri2*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==8)
	{
		qu_816(11,31,2,shi1*2,0);
		hua_816(11,31,1,shi1*2,0);
		while(shiji==8)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(shi1<2) 
					{
						for(foo=1;foo<17;foo++)
   						{
							qu_816(11,31,1,shi1*2,foo-1);
							hua_816(11,31,1,shi1*2,foo);
							delay(10000);
						}
						shi1++;
					}
				}
				while(key_jia==0);
				
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(shi1>0)
					{
						for(foo=16;foo>0;foo--)
   						{
							qu_816(11,31,1,(shi1-1)*2,foo);
							hua_816(11,31,1,(shi1-1)*2,foo-1);
							delay(10000);
						}
						shi1--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
			
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(11,31,1,shi1*2,0);
					hua_816(11,31,2,shi1*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==9)
	{
	   qu_816(19,31,2,shi2*2,0);
		hua_816(19,31,1,shi2*2,0);
		while(shiji==9)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(shi2<9) 
					{	
						for(foo=1;foo<17;foo++)
   						{
							qu_816(19,31,1,shi2*2,foo-1);
							hua_816(19,31,1,shi2*2,foo);
							delay(10000);
						}
						shi2++;
					}
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(shi2>0)
					{					
						for(foo=16;foo>0;foo--)
   						{
							qu_816(19,31,1,(shi2-1)*2,foo);
							hua_816(19,31,1,(shi2-1)*2,foo-1);
							delay(10000);
						}
						shi2--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{  aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
			
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(19,31,1,shi2*2,0);
					hua_816(19,31,2,shi2*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==10)
	{
		qu_816(30,31,2,fen1*2,0);
		hua_816(30,31,1,fen1*2,0);
		while(shiji==10)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(fen1<5) 
					{	
						for(foo=1;foo<17;foo++)
   						{
							qu_816(30,31,1,fen1*2,foo-1);
							hua_816(30,31,1,fen1*2,foo);
							delay(10000);
						}
						fen1++;
					}
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(shi2>0)
					{					
						for(foo=16;foo>0;foo--)
   						{
							qu_816(30,31,1,(fen1-1)*2,foo);
							hua_816(30,31,1,(fen1-1)*2,foo-1);
							delay(10000);
						}
						fen1--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
			
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(30,31,1,fen1*2,0);
					hua_816(30,31,2,fen1*2,0);
				}
				while(key_qu_ren==0);
										
			}
		}
	}
	while(shiji==11)
	{
		qu_816(38,31,2,fen2*2,0);
		hua_816(38,31,1,fen2*2,0);
		while(shiji==11)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	aaajjj=0;
					if(fen2<9) 
					{
						for(foo=1;foo<17;foo++)
   						{
							qu_816(38,31,1,fen2*2,foo-1);
							hua_816(38,31,1,fen2*2,foo);
							delay(10000);
						}
						fen2++;
					}
				}
				while(key_jia==0);
				
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(fen2>0)
					{
						for(foo=16;foo>0;foo--)
   						{
							qu_816(38,31,1,(fen2-1)*2,foo);
							hua_816(38,31,1,(fen2-1)*2,foo-1);
							delay(10000);
						}
						fen2--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
				
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					shiji++;
					qu_816(38,31,1,fen2*2,0);
					hua_816(38,31,2,fen2*2,0);
				}
				while(key_qu_ren==0);
											
			}
		}
	}
	while(shiji==12)
	{
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=xinq[jj];
			LB1[jj]=xinq[jj+64];
			LB2[jj]=xinq[jj+128];
		}
		if(wxinq==7)
		{
			for(jj=0;jj<64;jj++)
			{
				LB[jj]=xinq[jj+160];
			}
			qu_1616(59,31,2,4,0);
			hua_1616(59,31,1,4,0);
			for(jj=0;jj<64;jj++)
			{
				LB[jj]=xinq[jj];
				LB1[jj]=xinq[jj+64];
				LB2[jj]=xinq[jj+128];
			}
		}
		else
		{
			qu_1616(59,31,2,wxinq*4-4,0);
			hua_1616(59,31,1,wxinq*4-4,0);
		}
		
		while(shiji==12)
		{
			if(key_jia==0|aaajjj==0x44)
			{
				delay(5000);
				if(key_jia==0|aaajjj==0x44)
				{	 aaajjj=0;
					 if(wxinq<7)
					 {
						if(wxinq==6) 
						{
							qu_1616(59,31,1,20,0);
							for(foo=59;foo<80;foo++)
	   						{
								qu_1616(foo-1,31,1,20,0);
								hua_1616(foo,31,1,20,0);
								delay(1500);
							}
							for(jj=0;jj<64;jj++)
							{
								LB[jj]=xinq[jj+192];
							}
							for(foo=48;foo>30;foo--)
	   						{
								qu_1616(59,foo+1,1,0,0);
								hua_1616(59,foo,1,0,0);
								delay(1500);
							}
							for(jj=0;jj<64;jj++)
							{
								LB[jj]=xinq[jj];
								LB1[jj]=xinq[jj+64];
								LB2[jj]=xinq[jj+128];
							}
						}
						else
						{
							for(foo=59;foo<80;foo++)
	   						{
								qu_1616(foo-1,31,1,wxinq*4-4,0);
								hua_1616(foo,31,1,wxinq*4-4,0);
								delay(1500);
							}
							for(foo=48;foo>30;foo--)
	   						{
								qu_1616(59,foo+1,1,wxinq*4,0);
								hua_1616(59,foo,1,wxinq*4,0);
								delay(1500);
							}											
						 }
						 wxinq++;
					 }
				}
				while(key_jia==0);
			
			}
			if(key_jian==0|aaajjj==0x43)
			{
				delay(5000);
				if(key_jian==0|aaajjj==0x43)
				{	aaajjj=0;								
					if(wxinq>1)
					{
					   if(wxinq==7)
					   {
						    for(jj=0;jj<64;jj++)
							{
								LB[jj]=xinq[jj+192];
							}
							qu_1616(59,31,1,0,0);
							for(foo=59;foo<80;foo++)
	   						{
								qu_1616(foo-1,31,1,0,0);
								hua_1616(foo,31,1,0,0);
								delay(1500);
							}
							for(jj=0;jj<64;jj++)
							{
								LB[jj]=xinq[jj];
								LB1[jj]=xinq[jj+64];
								LB2[jj]=xinq[jj+128];
							}
							for(foo=48;foo>30;foo--)
	   						{
								qu_1616(59,foo+1,1,wxinq*4-8,0);
								hua_1616(59,foo,1,wxinq*4-8,0);
								delay(1500);
							}
					   }
					   else
					   {
					   		for(foo=59;foo<80;foo++)
	   						{
								qu_1616(foo-1,31,1,wxinq*4-4,0);
								hua_1616(foo,31,1,wxinq*4-4,0);
								delay(1500);
							}
							for(foo=48;foo>30;foo--)
	   						{
								qu_1616(59,foo+1,1,wxinq*4-8,0);
								hua_1616(59,foo,1,wxinq*4-8,0);
								delay(1500);
							}
					   }
					   wxinq--;
					}
				}
				while(key_jian==0);
			
			}
			if(key_fan_hiu==0|aaajjj==0x15)
			{
				delay(5000);
				if(key_fan_hiu==0|aaajjj==0x15)
				{	aaajjj=0;
					shiji=15;
					shanji=1;
					for(foo=1;foo<63;foo++)
				   {
				   		for(foo1=1;foo1<31;foo1++)
						{
							qing_dian1(foo,foo1,3);
						}
						delay(3000);
				   }
				}
				while(key_fan_hiu==0);
			
			}
			if(key_qu_ren==0|aaajjj==0x40)
			{
				delay(5000);
				if(key_qu_ren==0|aaajjj==0x40)
				{	aaajjj=0;
					if(wxinq==7)
					{
						for(jj=0;jj<64;jj++)
						{
							LB[jj]=xinq[jj+192];
						}
						qu_1616(59,31,1,0,0);
						hua_1616(59,31,2,0,0);
						for(jj=0;jj<64;jj++)
						{
							LB[jj]=xinq[jj];
							LB1[jj]=xinq[jj+64];
							LB2[jj]=xinq[jj+128];
						}
					}
					else
					{
						qu_1616(59,31,1,wxinq*4-4,0);
						hua_1616(59,31,2,wxinq*4-4,0);
					}
					shiji=2;
				}
				while(key_qu_ren==0);
										
			}
		}
		for(jj=0;jj<64;jj++)
		{
			LB[jj]=k816[jj];
			LB1[jj]=k816[jj+64];
			LB2[jj]=k816[jj+128];
		}
	}
	if(shiji==15)
	{
		TR1=0;
		P2M0|=0x10;
		wnian=nian1*16+nian2;
		wyue=yue1*16+yue2;
		wri=ri1*16+ri2;
		wshi=shi1*16+shi2;
		wfen=fen1*16+fen2;
		Write1302 (xie_dian_yuan,0x00);
		Write1302 (xie_miao,0x00);
		Write1302 (xie_fen_zhong,wfen);
		Write1302 (xie_xiao_shi,wshi);
		Write1302 (xie_tian,wri);
		Write1302 (xie_xin_qi,wxinq);
		Write1302 (xie_yue,wyue);
		Write1302 (xie_nian,wnian);	
		Write1302 (xie_dian_yuan,0x80);
		TR1=1;
		P2M0&=0xef;
	}
}


void tcs_huadian(uchar tx,uchar ty)		 //贪吃蛇画点
{
	hua_dian1(3+(tx-1)*3,1+(ty-1)*3,2);
	hua_dian1(2+(tx-1)*3,2+(ty-1)*3,2);
	hua_dian1(4+(tx-1)*3,2+(ty-1)*3,2);
	hua_dian1(3+(tx-1)*3,3+(ty-1)*3,2);
	hua_dian1(2+(tx-1)*3,1+(ty-1)*3,1);
	hua_dian1(4+(tx-1)*3,1+(ty-1)*3,1);
	hua_dian1(2+(tx-1)*3,3+(ty-1)*3,1);
	hua_dian1(4+(tx-1)*3,3+(ty-1)*3,1);
}

void tcs_qudian(uchar tx1,uchar ty1)		 //贪吃蛇取点
{
	qing_dian1(3+(tx1-1)*3,1+(ty1-1)*3,2);
	qing_dian1(2+(tx1-1)*3,2+(ty1-1)*3,2);
	qing_dian1(4+(tx1-1)*3,2+(ty1-1)*3,2);
	qing_dian1(3+(tx1-1)*3,3+(ty1-1)*3,2);
	qing_dian1(2+(tx1-1)*3,1+(ty1-1)*3,1);
	qing_dian1(4+(tx1-1)*3,1+(ty1-1)*3,1);
	qing_dian1(2+(tx1-1)*3,3+(ty1-1)*3,1);
	qing_dian1(4+(tx1-1)*3,3+(ty1-1)*3,1);
}


void tcs_zhukong()			//贪吃蛇主控
{
	xinz=1;
	tcskais();
	while(xinz&&ysh==4)
	{
		if(key_jian==0|aaajjj==0x43)
		{
			delay(5000);
			if(key_jian==0|aaajjj==0x43)
			{	aaajjj=0;
				if(xiaxia!=2)
				efenqian=0;
			}			
		}
		if(key_jia==0|aaajjj==0x44)
		{
			delay(5000);
			if(key_jia==0|aaajjj==0x44)
			{	aaajjj=0;
				if(xiaxia!=0)
				efenqian=2;
			}
		}
		if(key_fan_hiu==0|aaajjj==0x15)
		{
			delay(5000);
			if(key_fan_hiu==0|aaajjj==0x15)
			{	aaajjj=0;
				if(xiaxia!=1)
				efenqian=3;
			}			
		}
		if(key_qu_ren==0|aaajjj==0x46)
		{
			delay(5000);
			if(key_qu_ren==0|aaajjj==0x46)
			{	aaajjj=0;
				if(xiaxia!=3)
				efenqian=1;
			}	
		}
		if(efenbai==1)
		{
			if(tcs_qfyd()==1)
			{	
				efenbai=0;
				tcskais();
				
			}
			if(tcs_qfyd()==2)
			{	
				efenbai=0;
				szxh++;
				LB3[(szxh-1)*2]=newxinz;
				LB3[(szxh-1)*2+1]=newfangx;
				efenge=1;
				while(efenge)
				{
					tcs_sjd();
					if(tcs_jc()==1) efenge=1;else efenge=0;
				}
				tcs_huadian(newfkx,newfky);				
				
			}
			if(tcs_qfyd()==0)
			{	
				efenbai=0;
				tcs_qudian(LB3[0],LB3[1]);
				tcs_huadian(newxinz,newfangx);
				for(foo=0;foo<(szxh-1);foo++)
				{
					 LB3[foo*2]=LB3[foo*2+2];
					 LB3[foo*2+1]=LB3[foo*2+3];
				}
				LB3[(szxh-1)*2]=newxinz;
				LB3[(szxh-1)*2+1]=newfangx;
				xiaxia=efenqian;
				
			}		
			
		}
		
	}
	if(ysh!=yangshi)
	{
		yangshi=ysh;		
		qing_huan_chong();
	}
}

void tcs_sjd()       //产生随机点
{
	srand(rand()+fangx+fkx+fky+newfkx+newfky+efenshi);
    newfkx=rand()%20;
	newfky=rand()%10;
	newfkx++;
	newfky++;
}


uchar tcs_jc()		 //检测点是否落在身上
{
	b=0;
	for(foo=0;foo<szxh;foo++)
	{
		if(LB3[foo*2]==newfkx)
		{
			if(LB3[foo*2+1]==newfky)
			{
				b=1;
			}
		}
	}
	return(b);
}

uchar tcs_qfyd()		//检测前方有没有冲突
{
	b=0;
	newxinz=LB3[(szxh-1)*2];
	newfangx=LB3[(szxh-1)*2+1];
	if(efenqian==0) newxinz++;
	if(efenqian==1) newfangx--;
	if(efenqian==2) newxinz--;
	if(efenqian==3) newfangx++;
	for(foo=0;foo<szxh;foo++)
	{
		if(LB3[foo*2]==newxinz)
		{
			if(LB3[foo*2+1]==newfangx)
			{
				b=1;
			}
		}
	}
	if(newxinz<1|newxinz>20)  b=1;
	if(newfangx<1|newfangx>10)  b=1;
	if(newxinz==newfkx&&newfangx==newfky) b=2;
	return(b);
}

void tcskais()			 //贪吃蛇开始
{
	efenge=1;
	efenbai=0;
	efenqian=0;
	xiaxia=0;	
	szxh=7;
	qing_hong();
	qing_nv();
	
	for(foo=0;foo<200;foo++)
	{
		LB3[foo]=0;
	}
	tcs_qudian(2,5);
	tcs_huadian(2,5);
	tcs_huadian(3,5);
	tcs_huadian(4,5);
	tcs_huadian(5,5);
	tcs_huadian(6,5);
	tcs_huadian(7,5);
	tcs_huadian(8,5);
	LB3[0]=2;LB3[1]=5;LB3[2]=3;LB3[3]=5;LB3[4]=4;LB3[5]=5;
	LB3[6]=5;LB3[7]=5;LB3[8]=6;LB3[9]=5;LB3[10]=7;LB3[11]=5;
	LB3[12]=8;LB3[13]=5;
	while(key_qu_ren==1&&ysh==4&&aaajjj!=0x46)
	{
		efenshi++;
	}
	delay(10000);
	while(key_qu_ren==0&&ysh==4&&aaajjj!=0x46);
	delay(10000);
	while(efenge)
	{
		tcs_sjd();
		if(tcs_jc()==1) efenge=1;else efenge=0;
	}
	tcs_huadian(newfkx,newfky);
}