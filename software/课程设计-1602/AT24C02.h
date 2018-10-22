/*
  程序说明: IIC总线驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "intrins.h"

#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();}  
#define uchar unsigned char  


//总线引脚定义

sbit SCL_t = P2^3;  /* 时钟线 */
sbit SDA_t = P2^4;  /* 数据线 */


void IIC_Start_t(void)
{
	SDA_t = 1;
	SCL_t = 1;
	somenop;
	SDA_t = 0;
	somenop;
	SCL_t = 0;	
}

//总线停止条件
void IIC_Stop_t_t(void)
{
	SDA_t = 0;
	SCL_t = 1;
	somenop;
	SDA_t = 1;
}

//应答位控制
void IIC_Ack(bit ackbit)
{
	if(ackbit) 
	{	
		SDA_t = 0;
	}
	else 
	{
		SDA_t = 1;
	}
	somenop;
	SCL_t = 1;
	somenop;
	SCL_t = 0;
	SDA_t = 1; 
	somenop;
}

//等待应答
bit IIC_WaitAck(void)
{
	SDA_t = 1;
	somenop;
	SCL_t = 1;
	somenop;
	if(SDA_t)    
	{   
		SCL_t = 0;
		IIC_Stop_t_t();
		return 0;
	}
	else  
	{ 
		SCL_t = 0;
		return 1;
	}
}

//通过I2C总线发送数据
void IIC_SendByte(uchar byt)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{   
		if(byt&0x80) 
		{	
			SDA_t = 1;
		}
		else 
		{
			SDA_t = 0;
		}
		somenop;
		SCL_t = 1;
		byt <<= 1;
		somenop;
		SCL_t = 0;
	}
}

//从I2C总线上接收数据
uchar IIC_RecByte(void)
{
	unsigned char da;
	unsigned char i;
	
	for(i=0;i<8;i++)
	{   
		SCL_t = 1;
		somenop;
		da <<= 1;
		if(SDA_t) 
			da |= 0x01;
		SCL_t = 0;
		somenop;
	}
	return da;
}

//读写IIC的值
uchar IIC_AD_Read(uchar add)	  //add为地址
{
	uchar temp;
			
	IIC_Start_t();   	//启动总线
	IIC_SendByte(0x90);		//8591的地址
	IIC_WaitAck();			//等待响应
	IIC_SendByte(add);		 //读哪个通道的内容
	IIC_WaitAck();
	IIC_Stop_t_t();

	IIC_Start_t();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Stop_t_t();

	return temp;		//返回temp
}

//读EEPROM的值
uchar IIC_EEPROM_Read(uchar add1)	  //add为地址
{
	uchar temp1;
			
	IIC_Start_t();   	//启动总线
	IIC_SendByte(0xa0);		//8591的地址
	IIC_WaitAck();			//等待响应
	IIC_SendByte(add1);		 //读哪个通道的内容
	IIC_WaitAck();
	IIC_Stop_t_t();

	IIC_Start_t();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	temp1 = IIC_RecByte();
	IIC_Stop_t_t();

	return temp1;		//返回temp
}

//将数值写入EEPROM
void IIC_EEPROM_Write(uchar add2, uchar dat)
{
	IIC_Start_t();
	IIC_SendByte(0xa0);    //选择EEPROM芯片
	IIC_WaitAck();       //等待响应
	IIC_SendByte(add2);	 //写地址
	IIC_WaitAck();    //等待响应
	IIC_SendByte(dat);     //对其进行写数据
	IIC_WaitAck();	   //等待响应
	IIC_Stop_t_t();		
}

