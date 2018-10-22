/********************************************************************/
/*                   ����Ƽ�������ר����                           */
/*                    AT24C02ģ����Դ���                           */
/*  	         	   ����Ƽ�  �����ɹ�	                        */
//ʵ�����󣺵�Ƭ����AT24C02д��һ���ֽ����ݣ��ٽ����ݶ�����
//���������������д�������һ�£������ָʾ��
/*                  http://fxfreefly.taobao.com                     */
/********************************************************************/
#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ�
#include<intrins.h>

sbit SCL = P2^0;   //����˿� 
sbit SDA = P2^1;
sbit LED = P2^2;

#define somenop();   _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();

unsigned char receivedata = 0;

/********************************************************************/
/*                            ��ʱ����                              */
/*               ��ʱʱ��ļ����Ӧ��Ƭ��12MHz�ľ���                */
/*            xΪ��ʱ��ms��������xΪ10ʱ����ʱʱ��ԼΪ10ms          */
/********************************************************************/
void delay1ms(unsigned int x)
{
	unsigned int i,j;
	for(j=0;j<x;j++)
		for(i=0;i<123;i++);
}

/*************************************************************/
/*                         ����IIC                           */
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
/*                       IIC��������                         */
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
/*                       IIC��������                         */
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
/*                      IIC��ȡӦ��λ                        */
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
/*                      IIC����Ӧ��λ                        */
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
/*                      IIC������Ӧ��λ                      */
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
/*                         ֹͣIIC                           */
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
/*             ��AT24C02д��һ���ֽڵ�����                   */
/*          adrΪд��ĵ�ַ��DataΪд�������                */
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
/*             ��AT24C02��ȡһ���ֽڵ�����                   */
/*          adrΪ��ȡ�ĵ�ַ������ֵΪ��ȡ������              */
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
/*                              ������                              */
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
