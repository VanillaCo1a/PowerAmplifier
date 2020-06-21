//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//  �� �� ��   : main.c
//  �� �� ��   : V1.0
//  ��    ��   : RJX
//  ��������   : 2017.11
//  ��������   : �����������Ƽ�Ƶ����ʾ

//  �޸���ʷ   :
//  ��    ��   :  
//  ��    ��   : RJX
//  ����޸�   : 
//  �޸�����   : �����ļ�
//  ��Ȩ���У�����ؾ���
//  Copyright(C) ���ǵ������޹�˾
//  All rights reserved
//******************************************************************************/

#include "delay.h"
#include "sys.h"
#include "oled.h"
//#include "bmp.h"
#include "adc.h"
#include "stm32_dsp.h"
#include "math.h"

#define NPT	256  //FFT��������


uint32_t ADC_DataNum=0;			//ADC��������

volatile uint8_t ADC_TimeOutFlag=1;			  //ADC��ʱ����ʱ�䵽��־
extern __IO uint16_t ADCConvertedValue;		//ADC����ֵ

uint8_t SW,GW;    //ȫ�ֱ���
uint8_t A[2]={0,0};
u8 X;  //����ʱ�õ�

long lBUFMAG[NPT+NPT/2];		//�洢��ģ�������
long lBUFOUT[NPT];          //FFT�������
long lBUFIN[NPT];           //FFT����ϵ��
u16 COLUMN1[25];
static u16 COLUMN1_LOD[25]={0};

//��126��ģֵ����ѡ��25��ģֵ����OLED������ʾ��25�����ͣ���ѡ��ԭ������0-4KƵ�ʶ�Ϊ����4K-8KƵ�δ�֮��8K-18K�ٴ�֮��
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
	  delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();
		OLED_Init();			//��ʼ��OLED 
	 
	 	TIM2_Configuration();
	  TIM2_NVIC_Configuration();
	  FFT_RCC_Configuration();
	  FFT_GPIO_Configuration();
	  FFT_DMA_Init();
	  FFT_ADC_Init();
	 
	 
	  TIM_Cmd(TIM2, ENABLE);
	  ADC_SoftwareStartConvCmd(ADC1, DISABLE);	 
	 
		OLED_Clear(); 
	 
		
		OLED_ShowCHinese(18,0,0);//��
		OLED_ShowCHinese(36,0,1);//��
		OLED_ShowCHinese(54,0,2);//��
		OLED_ShowCHinese(72,0,3);//��
		OLED_ShowCHinese(90,0,4);//��
	 
	  OLED_ShowCHinese(18,2,5); //��
		OLED_ShowCHinese(36,2,6); //��	 
	  OLED_ShowString(58,2,":");
		OLED_ShowString(80,2,"RJX");
		
	  OLED_ShowString(18,4,"2017/10/26");
		
		OLED_ShowString(0,6,"nova_007@163.com");		
		
	  delay_ms(1500);
		OLED_Clear();
		//OLED_ShowChar_1(1,2,5,24,1);
		X=85;
		BCD(X);
		/*/OLED_ShowNum(8,8,GW,1,16); //������ʾ����
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
			   if(ADC_DataNum<NPT)   //������û�дﵽ��Ҫ��ĵ�
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
				     cr4_fft_256_stm32(lBUFOUT,lBUFIN,NPT);//����STM32��DSP����FFT�任
				     powerMag(NPT);//����Ƶ���ֵ				
       
             arctan();	//��ѡ25��Ƶ�㣬0-4KΪ����4-8K��֮��8K-18K���١����Ƚϴ������ѹ����				   
						 
				     dsp_column();//��ʾ25��������
						 
			       TIM_Cmd(TIM2, ENABLE);
			   }
		  } 		
		
	  }
 }	  


//��ʾ��Ƶ�������
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
			if(COLUMN1[i]>COLUMN1_LOD[i]) //����߶ȳ���ԭֵ����ԭֵ����������
			 {
				 x=COLUMN1[i]-COLUMN1_LOD[i];
				 OLED_Fill(j,COLUMN1_LOD[i],j+3,COLUMN1_LOD[i]+x,1); 
				 delay_us(100);
				 
			 }
			if(COLUMN1[i]<COLUMN1_LOD[i])  //��ֵС����ֵ�����߳��Ĳ��ֵ���ʾ���
			 { OLED_Fill(j,COLUMN1[i],j+3,COLUMN1_LOD[i],0);}
			 
			  delay_us(100);
			  j=j+5;	
 		  	COLUMN1_LOD[i] =COLUMN1[i];	     
		 }
		 
		OLED_Refresh_Gram();		 
		delay_ms(50);			     
		  
}



//�����Ƶ���ģֵ
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
					float Mag = sqrt(X*X+ Y*Y)/nfill;  // ��ƽ����,�ٿ��� 
			  	lBUFMAG[i] = (long)(Mag*65536); 
    }     
  }
}


//��ȡģ���lBUFMAG[i]�У�ǰ128������ѡ��25��ֵ����ʾ����ѡ��ԭ���ǣ�0-4KΪ����4K-8K��֮��8K-18K���١�����ѡ����25��ֵ����COLUMN1[i]
void arctan(void)
 {
    
	  u8 i,temp,a[14]={13,16,19,23,26,29,32,38,45,51,64,77,90,115}; //��Ϊ��14���޹��ɣ����Խ���λ�ú��г���
    //u8 j=2;
    for(i=0;i<12;i++)
        { COLUMN1[i]= lBUFMAG[i+1];}  //��ѡǰ��11������lBUFMAG[0]�⣩����ΪlBUFMAG[0]Ϊֱ��������
				
    for(i=0;i<15;i++)  //��14��
        {
           temp=a[i];
           COLUMN1[i+12]=lBUFMAG[temp];                
    
				}	
	 
    for(i=1;i<26;i++)  //�������
       {    
          COLUMN1[i]=COLUMN1[i]*4;
				  //COLUMN1[i]=2*atan(COLUMN1[i]); //�÷����к������ʵ�ѹ���ϸߵ�ģ��ֵ,ʹ������ʾ����
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
  

//��ʱ��2����жϣ���λADCת����־ 
void TIM2_IRQHandler(void)
{
   	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
			{
         //TIM2->SR = (uint16_t)~TIM_FLAG_Update;
			   TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);	//���ж�
	       ADC_TimeOutFlag=1;
	    }
}

//BCD��ת������
void BCD(u16 R1)
	{
		SW=0;GW=0;
			
		while(R1>=10)
			{R1-=10;SW++;}
		GW=R1;
		A[0]=SW;
		A[1]=GW;		
	}




