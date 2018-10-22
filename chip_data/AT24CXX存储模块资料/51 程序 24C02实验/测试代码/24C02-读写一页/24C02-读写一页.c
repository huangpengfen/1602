/********************************************************************/
/*                   ����Ƽ�������ר����                           */
/*                    AT24C02ģ����Դ���                           */
/*  	         	   ����Ƽ�  �����ɹ�	                        */
//ʵ�����󣺵�Ƭ����AT24C02д��һҳ���ݣ��ٽ����ݶ�����
//���������������д�������һ�£������ָʾ��
/*                  http://fxfreefly.taobao.com                     */
/********************************************************************/
#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ�
#include<intrins.h>

sbit SCL = P2^0;   //����˿� 
sbit SDA = P2^1;
sbit LED = P2^2;

#define somenop();   _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();

unsigned char data_send[8];
unsigned char data_receive[8];
unsigned char j;

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
/*             ��AT24C02д��һҳ������                       */
/*          adrΪд��ĵ�ַ��DataΪд�������                */
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
/*             ��AT24C02��ȡһҳ������                       */
/*          adrΪ��ȡ�ĵ�ַ��DataoutΪ��ȡ������             */
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
/*                              ������                              */
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
		if(data_receive[j-1]!=j)   //�����ȡ��������д��Ĳ�ͬ��������
			break;

	if(j==9)   //�����ȫ��ͬ�������LED��
		LED=0;	
	for(;;);
}
