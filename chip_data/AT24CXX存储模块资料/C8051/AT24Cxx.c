/********************************************************************************************************
*
* File                : AT24Cxx.c
* Hardware Environment:	DVK501 && F320 EX
* Build Environment   : uVision3 V3.80 20100913
* Version             : 
* By                  : Su Wei Feng
*
*                                  (c) Copyright 2005-2010, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#define _DVK501_F320_EX_ 

#include <c8051f320.h>
#include <ws_clock.h>
#include <ws_delay.h>
#include <ws_iic_port.h>
#include <ws_at24cxx.h>
#include <ws_lcd_st7920_port.h>

void main(void)
{
	uchar *pRdDat;	

	PCA0MD &= ~0x40;            // Clear watchdog timer enable
   	clock_external();			// Set oscillator in external,the clock is 12M
	delay_ms(100);
   	Check_SDA();	
	XBR1 = 0x40;                // Enable crossbar and weak pull-ups
	SPI_Init();
	st7920LcdInit();
   	SMBus_Init();
	Enb_Interrupt(); 

	showLine(0,0,lcd_buffer,"AT24Cxx Example");
	showLine(0,1,lcd_buffer,"Program and");
	showLine(0,2,lcd_buffer,"Verify");
	showLine(0,3,lcd_buffer,"Results:");
	refreshLCD(lcd_buffer); 

	Write_AT24Cxx(0x00,'P');
	Read_AT24Cxx(0x00,pRdDat);
	showLine(9,3,lcd_buffer,"%c",*pRdDat);
	refreshLCD(lcd_buffer); 
	
	while(1);
}
