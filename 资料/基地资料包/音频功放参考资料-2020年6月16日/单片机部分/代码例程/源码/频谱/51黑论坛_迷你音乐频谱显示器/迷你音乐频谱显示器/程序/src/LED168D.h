/*
/////////////////////////////////////
             y
             ^
			 |
//   YL		 |
         	 |
     	   --|--------------------- > x 
             |		  //XL
*/
uchar YL;
uint XL;


////////////////////////////////////////
void LEDdelay(unsigned int dtime)	  // 1ms延时程序（12MHz 10倍于51单片机速度时）
{ 
	while( --dtime != 0);  				   
}

///////////////////////列选—//////////行选+///////////行选+//
void FFTMtL(uchar data VLX,uchar data VLY0,uchar data VLY1 ,uint data Dtime)  //Chang Data Form Virtual IO(LY<=7,LX<=15) to MCU IO AND LED IO port;
{
	 char data ii=0,LY=0xFF,LX0=0xFF,LX1=0xFF;
	 
		switch (VLX)
		{
		
			case B(10000000):P11=0;P30=0;break;
			case B(01000000):P12=0;P31=0;break;
			case B(00100000):P16=0;P35=0;break;
			case B(00010000):P05=0;P25=0;break;
			case B(00001000):P17=0;P36=0;break;
			case B(00000100):P03=0;P27=0;break;
			case B(00000010):P02=0;P44=0;break;
			case B(00000001):P14=0;P33=0;break;
			
			case 0xff:  break;
			//default : break;
		}
		
		switch (VLY0)
		{
			
			case B(10000000):P47=1;break;
			case B(01000000):P13=1;break;
			case B(00100000):P07=1;break;
			case B(00010000):P15=1;break;
			case B(00001000):P00=1;break;
			case B(00000100):P06=1;break;
			case B(00000010):P01=1;break;	
			case B(00000001):P04=1;break;

			case 0xff:  break;
			//default: break;	 //?
		}

		switch (VLY1)
		{
			
			case B(10000000):P37=1;break;
			case B(01000000):P32=1;break;
			case B(00100000):P23=1;break;
			case B(00010000):P34=1;break;
			case B(00001000):P46=1;break;
			case B(00000100):P24=1;break;
			case B(00000010):P45=1;break;	
			case B(00000001):P26=1;break;

			case 0xff:  break;
			//default: break;	 //?
		}

	



		//////////////////////////////Delay////
		LEDdelay(Dtime);
		///////////////////////////// Close////
		
		switch (VLX)
		{
		
			case B(10000000):P11=1;P30=1;break;
			case B(01000000):P12=1;P31=1;break;
			case B(00100000):P16=1;P35=1;break;
			case B(00010000):P05=1;P25=1;break;
			case B(00001000):P17=1;P36=1;break;
			case B(00000100):P03=1;P27=1;break;
			case B(00000010):P02=1;P44=1;break;
			case B(00000001):P14=1;P33=1;break;
			
			case 0xff:  break;
			//default : break;
		}
		
		switch (VLY0)
		{
			
			case B(10000000):P47=0;break;
			case B(01000000):P13=0;break;
			case B(00100000):P07=0;break;
			case B(00010000):P15=0;break;
			case B(00001000):P00=0;break;
			case B(00000100):P06=0;break;
			case B(00000010):P01=0;break;	
			case B(00000001):P04=0;break;

			case 0xff:  break;
			//default: break;	 //?
		}

		switch (VLY1)
		{
			
			case B(10000000):P37=0;break;
			case B(01000000):P32=0;break;
			case B(00100000):P23=0;break;
			case B(00010000):P34=0;break;
			case B(00001000):P46=0;break;
			case B(00000100):P24=0;break;
			case B(00000010):P45=0;break;	
			case B(00000001):P26=0;break;

			case 0xff:  break;
			//default: break;	 //?
		}
	
}




void BuftoLED168_Refresh()  //Refresh&Write Buf to LED168 ;
{
	 uchar data i,ty=1,tx=0x01;
     for(tx=0x01,i=2;tx;tx<<=1,i+=2)				  //tx!=0; or tx<=0x08;
     {
	 	for(ty=0x01;ty;ty<<=1)
     	{	   
		   FFTMtL(tx,ty&(LEDBuf[i]),ty&(LEDBuf[i+16]),200);	   //亮度调节（20～200）	   
        } 	
     }
	
}