
/********************************************************************************************************
*
* File                : AT24CXX.c
* Hardware Environment: 
* Build Environment   : ST Visual Develop 4.1.6
* Version             : V1.0
* By                  : Xiao xian hui
*
*                                  (c) Copyright 2005-2010, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#include <STM8S208MB.h>
#include <system.h>
#include <ws_at24cxx_src.h>
#include <ws_lcd_st7920.h>

main()
{
	u8 tmp;
	AT24CXX_Init();
	st7920LcdInit();
	
	showLine(0,0,lcd_buffer,"AT24Cxx Example");
	showLine(0,1,lcd_buffer,"Program and");
	showLine(0,2,lcd_buffer,"Verify");
	showLine(0,3,lcd_buffer,"Results:");
	refreshLCD(lcd_buffer);
	
	AT24CXX_WriteAByte(0x01,'P');
	delay_ms(10);
	tmp=AT24CXX_ReadAByte(0x01);
	
	showLine(9,3,lcd_buffer,"%c",tmp);
	refreshLCD(lcd_buffer); 
	while (1);
}