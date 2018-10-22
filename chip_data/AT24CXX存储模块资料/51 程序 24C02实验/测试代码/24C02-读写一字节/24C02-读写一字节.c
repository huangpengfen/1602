/********************************************************************/
/*                   飞翔科技开发板专卖店                           */
/*                    AT24C02模块测试代码                           */
/*  	         	   飞翔科技  助您成功	                        */
//实验现象：单片机向AT24C02写入一个字节数据，再将数据读出，
//如果读出的数据与写入的数据一致，则点亮指示灯
/*                  http://fxfreefly.taobao.com                     */
/********************************************************************/
#include<reg52.h> //包含头文件，一般情况不需要改动
#include<intrins.h>

sbit SCL = P2^0;   //定义端口 
sbit SDA = P2^1;
sbit LED = P2^2;

#define somenop();   _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();

unsigned char receivedata = 0;

/********************************************************************/
/*                            延时函数                              */
/*               延时时间的计算对应单片机12MHz的晶振                */
/*            x为延时的ms数，例：x为10时，延时时间约为10ms          */
/********************************************************************/
void delay1ms(unsigned int x)
{
	unsigned int i,j;
	for(j=0;j<x;j++)
		for(i=0;i<123;i++);
}

/*************************************************************/
/*                         启动IIC                           */
/*************************************************************/
void I2Cstart(void) 
{
  SDA = 1;
  somenop();
  SCL = 1;
  somenop();
  somenop();
  SDA = 0;
  somenop();
  somenop();
  SCL = 0;
}

/*************************************************************/
/*                       IIC发送数据                         */
/*************************************************************/
void I2Csend(unsigned char Data) 
{
 unsigned char i=8;
 while(i) 
 {
      SCL = 0;  
      somenop();
      SDA=(Data&0x80)>>7; 
      Data<<=1; 
      somenop();
      SCL = 1;
      somenop();
      somenop();
      i--;     
 }
 SCL = 0;
}

/*************************************************************/
/*                       IIC接收数据                         */
/*************************************************************/
unsigned char I2Creceive(void) 
{
 unsigned char i=8;
 unsigned char Data=0;
 SDA = 1;
 while(i) 
 {
      SCL = 0;  
      somenop();
      somenop();
      SCL = 1;
      somenop();
      Data<<=1;
      Data|=SDA;
      somenop();
      i--;     
 }
 SCL = 0;
 return(Data);
}

/*************************************************************/
/*                      IIC读取应答位                        */
/*************************************************************/
void I2Creadack(void) 
{
  SCL = 0;
  SDA = 1;
  somenop();
  somenop();
  SCL = 1;
  somenop();
  if(SDA == 1) 
  {
     for(;;) ;  
  }
  somenop();
  SCL = 0;
  somenop();
  somenop();
}

/*************************************************************/
/*                      IIC发送应答位                        */
/*************************************************************/
void I2Csendack(void) 
{
  SCL = 0;
  somenop();
  SDA = 0;
  somenop();
  SCL = 1;
  somenop();
  somenop();
  SCL = 0;
  somenop();
  somenop();
}

/*************************************************************/
/*                      IIC不发送应答位                      */
/*************************************************************/
void I2Csendnoack(void) 
{
  SCL = 0;
  somenop();
  SDA = 1;
  somenop();
  SCL = 1;
  somenop();
  somenop();
  SCL = 0;
  somenop();
  somenop();
}

/*************************************************************/
/*                         停止IIC                           */
/*************************************************************/
void I2Cstop(void) 
{
  SCL = 0;
  SDA = 0;
  somenop(); 
  somenop();
  SCL = 1;
  somenop();
  SDA = 1; 
  somenop(); 
  somenop();
}

/*************************************************************/
/*             向AT24C02写入一个字节的数据                   */
/*          adr为写入的地址，Data为写入的数据                */
/*************************************************************/
void write_byte(unsigned char adr,unsigned char Data)
{
  I2Cstart();
  I2Csend(0xa0);
  I2Creadack();

  I2Csend(adr);
  I2Creadack();

  I2Csend(Data);
  I2Creadack();
  I2Cstop();
}

/*************************************************************/
/*             由AT24C02读取一个字节的数据                   */
/*          adr为读取的地址，返回值为读取的数据              */
/*************************************************************/
unsigned char read_byte(unsigned char adr)
{
  unsigned char readdata;
  I2Cstart();
  I2Csend(0xa0);
  I2Creadack();

  I2Csend(adr);
  I2Creadack();


  I2Cstart();
  I2Csend(0xa1);
  I2Creadack();

  readdata = I2Creceive();
  I2Csendnoack();
  I2Cstop();
  return readdata;

}


/********************************************************************/
/*                              主函数                              */
/********************************************************************/
void main(void) 
{ 
	LED=1;
	delay1ms(20);
	write_byte(0x00,'A');
	delay1ms(20);
	receivedata=read_byte(0x00);
	
	if(receivedata=='A')
		LED=0;
	
	for(;;);
}
