/******************************************************************************/
#ifndef __1602_H__		
#define __1602_H__
#include "STC12c5a60s2.H"
#define uchar    unsigned char
#define uint     unsigned int
                
/*************************************************
Òý½Å¶¨Òå:
*************************************************/
#define lcdDb  	P0			
sbit	lcdRs=P3^5;	 	
sbit    lcdRw=P3^6;			
sbit    lcdE =P3^7;			
/************************************************/			
void lcdCheckbusy();
void lcdInit (void);
void lcdWriteCommand (uchar Command); 
void lcdWriteData (uchar Data); 
void lcdWritePic (); 
void dispString (uchar x,uchar y,uchar dat); 
void delay40us(uint n);

#endif
