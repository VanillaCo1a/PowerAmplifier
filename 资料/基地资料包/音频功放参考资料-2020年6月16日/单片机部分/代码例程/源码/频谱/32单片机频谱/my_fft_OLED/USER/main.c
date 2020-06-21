//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : main.c
//  版 本 号   : V1.0
//  作    者   : RJX
//  生成日期   : 2017.11
//  功能描述   : 音响音量控制及频谱显示

//  修改历史   :
//  日    期   :  
//  作    者   : RJX
//  最近修改   : 
//  修改内容   : 创建文件
//  版权所有，盗版必究。
//  Copyright(C) 新星电子有限公司
//  All rights reserved
//******************************************************************************/

#include "delay.h"
#include "sys.h"
#include "oled.h"
//#include "bmp.h"
#include "adc.h"
#include "stm32_dsp.h"
#include "math.h"

#define NPT	256  //FFT采样点数


uint32_t ADC_DataNum=0;			//ADC采样点数

volatile uint8_t ADC_TimeOutFlag=1;			  //ADC定时采样时间到标志
extern __IO uint16_t ADCConvertedValue;		//ADC采样值

uint8_t SW,GW;    //全局变量
uint8_t A[2]={0,0};
u8 X;  //调试时用的

long lBUFMAG[NPT+NPT/2];		//存储求模后的数据
long lBUFOUT[NPT];          //FFT输出序列
long lBUFIN[NPT];           //FFT输入系列
u16 COLUMN1[25];
static u16 COLUMN1_LOD[25]={0};

//从126个模值中挑选出25个模值，在OLED屏上显示出25条柱型，挑选的原则是以0-4K频率段为主，4K-8K频段次之，8K-18K再次之。
/*u8 COLUMN1[25]={lBUFMAG[1],lBUFMAG[2],lBUFMAG[3],lBUFMAG[4],lBUFMAG[5],lBUFMAG[6],lBUFMAG[7],lBUFMAG[8],lBUFMAG[9],lBUFMAG[10],
                   lBUFMAG[11],lBUFMAG[13],lBUFMAG[16],lBUFMAG[19],lBUFMAG[23],lBUFMAG[26],lBUFMAG[29],lBUFMAG[32],lBUFMAG[38],lBUFMAG[45],
                   lBUFMAG[51],lBUFMAG[64],lBUFMAG[77],lBUFMAG[90],lBUFMAG[115] };*/

                 

void dsp_column(void);
void powerMag(long nfill);
void arctan(void);
void gain_ctl(void);	
void BCD(u16 R1);
void dsp_column_1(void);
	
 int main(void)
 {	
		
		//u8 i,j; 
	  delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();
		OLED_Init();			//初始化OLED 
	 
	 	TIM2_Configuration();
	  TIM2_NVIC_Configuration();
	  FFT_RCC_Configuration();
	  FFT_GPIO_Configuration();
	  FFT_DMA_Init();
	  FFT_ADC_Init();
	 
	 
	  TIM_Cmd(TIM2, ENABLE);
	  ADC_SoftwareStartConvCmd(ADC1, DISABLE);	 
	 
		OLED_Clear(); 
	 
		
		OLED_ShowCHinese(18,0,0);//音
		OLED_ShowCHinese(36,0,1);//量
		OLED_ShowCHinese(54,0,2);//控
		OLED_ShowCHinese(72,0,3);//制
		OLED_ShowCHinese(90,0,4);//器
	 
	  OLED_ShowCHinese(18,2,5); //设
		OLED_ShowCHinese(36,2,6); //计	 
	  OLED_ShowString(58,2,":");
		OLED_ShowString(80,2,"RJX");
		
	  OLED_ShowString(18,4,"2017/10/26");
		
		OLED_ShowString(0,6,"nova_007@163.com");		
		
	  delay_ms(1500);
		OLED_Clear();
		//OLED_ShowChar_1(1,2,5,24,1);
		X=85;
		BCD(X);
		/*/OLED_ShowNum(8,8,GW,1,16); //数字显示测试
		OLED_ShowCHinese32(38,8,SW);			
		OLED_ShowCHinese32(70,8,GW);	
			
		
		//X=23
		//BCD(X);
		//OLED_ShowChar(8,8,GW+0x30);
		delay_ms(1500);
		delay_ms(1500);
		delay_ms(1500);
		
		OLED_Clear();
		
		OLED_ShowCHinese48(20,8,SW);
		OLED_ShowCHinese48(68,8,GW);
		
		
		delay_ms(500);
		OLED_Clear();
		
		OLED_ShowAsc48(20,8,SW);
		OLED_ShowAsc48(48,8,GW);
		delay_ms(1500);
		delay_ms(1500);
		delay_ms(1500);
		OLED_Clear();	*/
		
	
 		
		
	while(1) 
	 {		
		 if(ADC_TimeOutFlag)
			{
			
			   ADC_TimeOutFlag=0;
			   if(ADC_DataNum<NPT)   //采样点没有达到所要求的点
				  {            
				    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
				    while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
				    /* Clear channel1 transfer complete flag */
			 	    DMA_ClearFlag(DMA1_FLAG_TC1);            
				    ADC_SoftwareStartConvCmd(ADC1, DISABLE);
				    lBUFIN[ADC_DataNum]=ADCConvertedValue<<16;
				    ADC_DataNum++;
						
				  }
			  else
				 {
				     TIM_Cmd(TIM2, DISABLE);
				     ADC_DataNum=0;
				     cr4_fft_256_stm32(lBUFOUT,lBUFIN,NPT);//调用STM32的DSP库作FFT变换
				     powerMag(NPT);//计算频点幅值				
       
             arctan();	//挑选25个频点，0-4K为主，4-8K次之，8K-18K最少。幅度较大的予以压缩。				   
						 
				     dsp_column();//显示25根柱条。
						 
			       TIM_Cmd(TIM2, ENABLE);
			   }
		  } 		
		
	  }
 }	  


//显示各频点的柱条
void dsp_column(void)
{
   u8 i,j=2;
	 
	 for(i=0;i<25;i++)
	   {    OLED_Fill(j,2,j+3,64,0);
			    OLED_Fill(j,0,j+3,COLUMN1[i],1);
			    j=j+5;	 		  		     
		 }
		OLED_Refresh_Gram();		 
		delay_ms(100); 
}
 
void dsp_column_1(void)
{
   u8 x,i,j=2;
	 //static u16 COLUMN1_LOD[25];
	 
	 for(i=1;i<26;i++)
	   { 
			 OLED_Fill(2,2,5,64,0);
			 OLED_Fill(2,0,5,COLUMN1[0],1);
			if(COLUMN1[i]>COLUMN1_LOD[i]) //如果高度超过原值，在原值基础上增加
			 {
				 x=COLUMN1[i]-COLUMN1_LOD[i];
				 OLED_Fill(j,COLUMN1_LOD[i],j+3,COLUMN1_LOD[i]+x,1); 
				 delay_us(100);
				 
			 }
			if(COLUMN1[i]<COLUMN1_LOD[i])  //新值小于老值，将高出的部分的显示清除
			 { OLED_Fill(j,COLUMN1[i],j+3,COLUMN1_LOD[i],0);}
			 
			  delay_us(100);
			  j=j+5;	
 		  	COLUMN1_LOD[i] =COLUMN1[i];	     
		 }
		 
		OLED_Refresh_Gram();		 
		delay_ms(50);			     
		  
}



//计算各频点的模值
void powerMag(long nfill)
{	 int32_t lX,lY; 
		uint32_t i; 
		for (i=0; i < nfill; i++) 
		{ 
			lX= (lBUFOUT[i]<<16)>>16; /* sine_cosine --> cos */ 
			lY= (lBUFOUT[i] >> 16);   /* sine_cosine --> sin */     
			{ 
					float X=  64*((float)lX)/32768; 
					float Y = 64*((float)lY)/32768; 
					float Mag = sqrt(X*X+ Y*Y)/nfill;  // 先平方和,再开方 
			  	lBUFMAG[i] = (long)(Mag*65536); 
    }     
  }
}


//从取模结果lBUFMAG[i]中（前128个）挑选出25个值做显示。挑选的原则是：0-4K为主，4K-8K次之，8K-18K最少。将挑选出的25个值赋给COLUMN1[i]
void arctan(void)
 {
    
	  u8 i,temp,a[14]={13,16,19,23,26,29,32,38,45,51,64,77,90,115}; //因为后14个无规律，所以将其位置号列出来
    //u8 j=2;
    for(i=0;i<12;i++)
        { COLUMN1[i]= lBUFMAG[i+1];}  //挑选前面11个（除lBUFMAG[0]外），因为lBUFMAG[0]为直流分量。
				
    for(i=0;i<15;i++)  //后14个
        {
           temp=a[i];
           COLUMN1[i+12]=lBUFMAG[temp];                
    
				}	
	 
    for(i=1;i<26;i++)  //增益调整
       {    
          COLUMN1[i]=COLUMN1[i]*4;
				  //COLUMN1[i]=2*atan(COLUMN1[i]); //用反正切函数来适当压缩较高的模的值,使柱条显示均衡
				 if(COLUMN1[i]==0) 
           {COLUMN1[i]=2;}
				 else if((COLUMN1[i]<5)&&(COLUMN1[i]>0)) 
           {COLUMN1[i]=COLUMN1[i]+7;}
				 else if((COLUMN1[i]>=5)&&(COLUMN1[i]<10))
           {COLUMN1[i]=COLUMN1[i]+5;}
				 else if((COLUMN1[i]>=10)&&(COLUMN1[i]<15))
           {COLUMN1[i]=COLUMN1[i]+4;} 
				 else if(COLUMN1[i]>=64) 
           {COLUMN1[i]=63;} 			 
				 else if((COLUMN1[i]>=55)&&(COLUMN1[i]<=63)) 
           {COLUMN1[i]=COLUMN1[i]-8;}
					 
			 } 
 }
  

//定时器2溢出中断，置位ADC转换标志 
void TIM2_IRQHandler(void)
{
   	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
			{
         //TIM2->SR = (uint16_t)~TIM_FLAG_Update;
			   TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);	//清中断
	       ADC_TimeOutFlag=1;
	    }
}

//BCD码转换程序
void BCD(u16 R1)
	{
		SW=0;GW=0;
			
		while(R1>=10)
			{R1-=10;SW++;}
		GW=R1;
		A[0]=SW;
		A[1]=GW;		
	}




