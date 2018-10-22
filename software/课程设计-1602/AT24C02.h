/*
  ����˵��: IIC������������
  �������: Keil uVision 4.10 
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨ 8051��12MHz
  ��    ��: 2011-8-9
*/

#include "intrins.h"

#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();}  
#define uchar unsigned char  


//�������Ŷ���

sbit SCL_t = P2^3;  /* ʱ���� */
sbit SDA_t = P2^4;  /* ������ */


void IIC_Start_t(void)
{
	SDA_t = 1;
	SCL_t = 1;
	somenop;
	SDA_t = 0;
	somenop;
	SCL_t = 0;	
}

//����ֹͣ����
void IIC_Stop_t_t(void)
{
	SDA_t = 0;
	SCL_t = 1;
	somenop;
	SDA_t = 1;
}

//Ӧ��λ����
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

//�ȴ�Ӧ��
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

//ͨ��I2C���߷�������
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

//��I2C�����Ͻ�������
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

//��дIIC��ֵ
uchar IIC_AD_Read(uchar add)	  //addΪ��ַ
{
	uchar temp;
			
	IIC_Start_t();   	//��������
	IIC_SendByte(0x90);		//8591�ĵ�ַ
	IIC_WaitAck();			//�ȴ���Ӧ
	IIC_SendByte(add);		 //���ĸ�ͨ��������
	IIC_WaitAck();
	IIC_Stop_t_t();

	IIC_Start_t();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Stop_t_t();

	return temp;		//����temp
}

//��EEPROM��ֵ
uchar IIC_EEPROM_Read(uchar add1)	  //addΪ��ַ
{
	uchar temp1;
			
	IIC_Start_t();   	//��������
	IIC_SendByte(0xa0);		//8591�ĵ�ַ
	IIC_WaitAck();			//�ȴ���Ӧ
	IIC_SendByte(add1);		 //���ĸ�ͨ��������
	IIC_WaitAck();
	IIC_Stop_t_t();

	IIC_Start_t();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	temp1 = IIC_RecByte();
	IIC_Stop_t_t();

	return temp1;		//����temp
}

//����ֵд��EEPROM
void IIC_EEPROM_Write(uchar add2, uchar dat)
{
	IIC_Start_t();
	IIC_SendByte(0xa0);    //ѡ��EEPROMоƬ
	IIC_WaitAck();       //�ȴ���Ӧ
	IIC_SendByte(add2);	 //д��ַ
	IIC_WaitAck();    //�ȴ���Ӧ
	IIC_SendByte(dat);     //�������д����
	IIC_WaitAck();	   //�ȴ���Ӧ
	IIC_Stop_t_t();		
}

