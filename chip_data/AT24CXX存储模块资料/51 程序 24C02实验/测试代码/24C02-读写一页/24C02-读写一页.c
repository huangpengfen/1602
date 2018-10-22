/********************************************************************/
/*                   飞翔科技开发板专卖店                           */
/*                    AT24C02模块测试代码                           */
/*  	         	   飞翔科技  助您成功	                        */
//实验现象：单片机向AT24C02写入一页数据，再将数据读出，
//如果读出的数据与写入的数据一致，则点亮指示灯
/*                  http://fxfreefly.taobao.com                     */
/********************************************************************/
#include<reg52.h> //包含头文件，一般情况不需要改动
#include<intrins.h>

sbit SCL = P2^0;   //定义端口 
sbit SDA = P2^1;
sbit LED = P2^2;

#define somenop();   _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();

unsigned char data_send[8];
unsigned char data_receive[8];
unsigned char j;

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
/*             向AT24C02写入一页的数据                       */
/*          adr为写入的地址，Data为写入的数据                */
/*************************************************************/
void write_page(unsigned char adr,unsigned char *Datain)
{
	unsigned char ix;
	I2Cstart();
	I2Csend(0xa0);
	I2Creadack();
	
	I2Csend(adr);
	I2Creadack();
	
	for(ix=0;ix<8;ix++)
	{
		I2Csend(Datain[ix]);
		I2Creadack();
	}
	I2Cstop();
}

/*************************************************************/
/*             由AT24C02读取一页的数据                       */
/*          adr为读取的地址，Dataout为读取的数据             */
/*************************************************************/
void read_page(unsigned char adr,unsigned char *Dataout)
{
	unsigned char ix;  
	I2Cstart();
	I2Csend(0xa0);
	I2Creadack();
	
	I2Csend(adr);
	I2Creadack();
	
	
	I2Cstart();
	I2Csend(0xa1);
	I2Creadack();
	
	for(ix=0;ix<8;ix++)
	{
		Dataout[ix] = I2Creceive();
			if(ix!=7)
				I2Csendack();
			else
				I2Csendnoack();
	}

	I2Cstop();


}


/********************************************************************/
/*                              主函数                              */
/********************************************************************/
void main(void) 
{ 
	LED=1;
	delay1ms(20);
	for(j=1;j<=8;j++)
		data_send[j-1]=j;
	
	write_page(0x00,data_send);

	delay1ms(20);

	read_page(0x00,data_receive);
	
	for(j=1;j<=8;j++)
		if(data_receive[j-1]!=j)   //如果读取的数据与写入的不同则跳出，
			break;

	if(j==9)   //如果完全相同，则点亮LED灯
		LED=0;	
	for(;;);
}
