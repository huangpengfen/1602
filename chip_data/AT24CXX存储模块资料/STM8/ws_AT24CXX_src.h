/********************************************************************************************************
*
* File                : ws_AT24CXX_src.h
* Hardware Environment: ST Visual Develop 4.1.6
* Build Environment   : 
* Version             : V1.0
* By                  : Xiao xian hui
*
*                                  (c) Copyright 2005-2010, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#ifndef _WS_AT24CXX_H_
#define _WS_AT24CXX_H_

#define WD_DADR 0xa0
#define RD_DADR 0xa1

#include <ws_i2c.h>

void AT24CXX_Init(void)
{
	I2C_Init();
}

void AT24CXX_WriteAByte(u8 wordAdr,u8 dat)
{
	I2C_Start();
	I2C_SendDAdr(WD_DADR);
	I2C_SendDat(wordAdr);
	I2C_SendDat(dat);
	I2C_stop();
}

u8 AT24CXX_ReadAByte(u8 wordAdr)
{
	u8 dat;
	I2C_Start();
	I2C_SendDAdr(WD_DADR);
	I2C_SendDat(wordAdr);
	I2C_Start();
	I2C_NAck();
	I2C_SendDAdr(RD_DADR);
	dat=I2C_RcvDat();
	I2C_stop();
	I2C_Ack();
	return dat;
}

#endif /*_WS_AT24CXX_H_*/