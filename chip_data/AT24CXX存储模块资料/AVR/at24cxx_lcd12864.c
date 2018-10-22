/********************************************************************************************************
*********************************************************************************************************
*
* File                : at24cxx_lcd12864.c
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313  (ICCAVR --> GCCAVR)
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/

#define _DVK501_M128_EX_ 1
#include <avr/io.h>
#include <util/delay.h>
#include <ws_iic_port.h>
#include <ws_at24cxx_port.h>
#include <ws_lcd_ST7920_port.h>


int main(void)
{
	uint8_t adr,WrDat,t;	
	uint8_t *pRdDat=&t;	//随便给"*pRdDat"一个具体地址，以免内存发生错误

	st7920LcdInit(); /*LCD初始化*/
	showLine(0,0,lcd_buffer,"深圳微雪电子");
	showLine(0,1,lcd_buffer,"AT24CX实验");
	showLine(0,2,lcd_buffer,"读取结果：");
	refreshLCD(lcd_buffer); /*刷新LCD*/
	adr=0x00;
	WrDat='P';
	twi_init();		
	if( I2C_Write(AT24C_WR_ADDR,adr,WrDat)!=I2C_ERR )	//AT24CXX写成功？
	{
		_delay_ms(50);	//等待EERPOM写完
		if( I2C_Read(AT24C_WR_ADDR,adr,AT24C_RD_ADDR,pRdDat)!=I2C_ERR )	//AT24CXX读成功？
			showLine(10,2,lcd_buffer,"%c",*pRdDat);
		else
			showLine(10,2,lcd_buffer,"error");	//读取错误，反馈错误信号
	}	
	else
		showLine(10,2,lcd_buffer,"error");	//写入错误，反馈错误信号

	refreshLCD(lcd_buffer); /*刷新LCD*/
	while(1);
}
