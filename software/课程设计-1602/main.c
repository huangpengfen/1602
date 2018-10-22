
/*
//����P15 P16 P17	 
//������ P00  spk=0��������
�̵��� P24
����  P33  P34  P35
at24C02  SCL P23
		 SDA P24
DHT11	P17
1602    ����/����ѡ���rs P25
		��д���ƶ� P26
		ʹ�ܶˣ�P27 
		���ݿڣ�P0
*/


#include "reg52.h"
#include "intrins.h"
#include "1602.h"
#include "DHT11.h"
#include "AT24C02.h"
//������������
sbit an1 = P3^5;
sbit an2 = P3^4;
sbit an3 = P3^3;
//�̵���
sbit jidianqi = P3^6;
//������
sbit fengmingqi = P1^0;
//��־λ  ��Ϊģʽѡ���õ�
unsigned char flag=0;     //flag=0,1,2,3,4,5  �ֱ��Ӧ������ʾ��ʪ��ֵ������ʪ�ȵ����ޣ�����ʪ�ȵ����ޣ������¶ȵ����ޣ������¶ȵ����ޣ�
						 //��⵽���ú�ֵ��д��at24c01����Ȼ�����������ʾ(������0)
uchar shidu_gao=90, shidu_di=40, wendu_gao=0, wendu_di=50;	   //����ʪ�����¶ȵ���ֵ���ֱ��Ӧʪ�ȸߣ�ʪ�ȵͣ��¶ȸߣ��¶ȵͣ�

unsigned char no_loop = 0;

unsigned char xdata sdd1[5];
unsigned char xdata sdd2[5];

unsigned char xdata sdd3[16];
unsigned char xdata sdd4[16];	
unsigned char xdata sdd5[16];
unsigned char xdata sdd6[16];		   //1602�������

unsigned char code she[]="H and T is OK";
unsigned char code zhi[]="data changing...";	//��������������ϵͳ������ֵ����ʾд��at24c02��״̬

unsigned char code kai[]="H Design by XXX.";
unsigned char code shi[]="  DORM: XX-XXX  ";	//����������������ɷ��ӣ�д�Լ������ֵ�

unsigned char code ban[]="XXXXXXXXXX";
unsigned char code ji[]="ClASS-X";		   //д��רҵ���༶

void delay_10_us(unsigned int num)		 //��ʱ��������ʱʱ��Ϊ10us
{
	while(num--)
		;
}			   

/********************************************************************
 * ��������delay_ms
 * ����  ��������뼶��ʱ(12Mhz�ľ���)
 * ����  ��-num:	������Ҫ��ʱ���ٺ��롣��num����1������ʱ1����
 * ���  ����
 * ����  ���ⲿ����
 ********************************************************************/
void delay__ms(unsigned int num)		   //��ʱ��������ʱʱ��Ϊxms
{
	unsigned int i;
	for(i=0;i<num;i++)
	{
		delay_10_us(100);
	}
}

//��������ɨ��
void keyscan(void)
{
	if (an1 == 0)
	{
		delay__ms(5);
		if (an1 == 0)
		{
			 //�����л����л�ʪ�Ȼ����¶ȸı䣬�����ֵ������С��ֵ
			 flag++;

		}
		while (!an1);
	}
	else if (an2 == 0)
	{
		delay__ms(5);
		if (an2 == 0)
		{
			//ʪ��/�¶�����1
			switch(flag)
			{
				case 1:	//����ʪ������
					shidu_gao++;
					break;
				case 2:	//����ʪ������
					shidu_di++;
					break;
				case 3:	//�����¶�����
					wendu_gao++;
					break;
				case 4:	//�����¶�����
					wendu_di++;
					break;
				default:
					break;
			}
					
		}
		while (!an2);
	}
	else if (an3 == 0)
	{
		delay__ms(5);
		if (an3 == 0)
		{
			//ʪ��/�¶��½�1
			switch(flag)
			{
				case 1:	//����ʪ������
					shidu_gao--;
					break;
				case 2:	//����ʪ������
					shidu_di--;
					break;
				case 3:	//�����¶�����
					wendu_gao--;
					break;
				case 4:	//�����¶�����
					wendu_di--;
					break;
				default:
					break;
			}
		}
		while (!an3);
	}
}

void baojing(void)		//������������������ֵʱ����
{
	if (U8RH_data_H<shidu_di || U8RH_data_H>shidu_gao)
	{
		//ʪ�ȱ���
		jidianqi = 0;
		fengmingqi = 0;
	}
	else if (U8T_data_H<wendu_di || U8T_data_H>wendu_gao)
	{
		//�¶ȱ���
		jidianqi = 0;
		fengmingqi = 0;
	}
	else
	{
		//û����
		jidianqi = 1;
		fengmingqi = 1;
	}
}

void Timer1Init(void)		//��ʱ��
{
	TMOD = 0x20;	  //��ʱ��T1ʹ�ù�����ʽ2
	TH1 = 253;        // ���ó�ֵ
	TL1 = 253;
	TR1 = 1;          // ��ʼ��ʱ
	SCON = 0x50;	  //������ʽ1��������9600bps���������   
	ES = 1;
	EA = 1;           // �������ж�   
	TI = 0;
	RI = 0;
}

void Timer0Init(void)		//��ʱ����ʼ����10����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xF0;		//���ö�ʱ��ֵ
	TH0 = 0xD8;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ

	ET0 = 1;
	EA = 1;
}
	

void timer0() interrupt 1		//��ʱ��������
{
	if (1 == no_loop)
	{
		keyscan();
		baojing();
	}
}


void zhuanhua()			  //����ȡ��������ת�����ܹ���1602��ʾ���ַ�
{
	sdd1[2]=str[0]/100+48;
	sdd1[3]=str[0]%100/10+48;
	sdd1[4]=str[0]%10+48;		 //�ռ�����ʪ������ת������ʾҺ����

	sdd2[2]=str[2]/100+48;
	sdd2[3]=str[2]%100/10+48;
	sdd2[4]=str[2]%10+48;		//�ռ������¶�����ת������ʾҺ����

	sdd3[6]=shidu_gao/100+48;
	sdd3[7]=shidu_gao%100/10+48;
	sdd3[8]=shidu_gao%10+48;		//�ռ������¶�����ת������ʾҺ����

	sdd4[6]=shidu_di/100+48;
	sdd4[7]=shidu_di%100/10+48;
	sdd4[8]=shidu_di%10+48;		//�ռ������¶�����ת������ʾҺ����

	sdd5[6]=wendu_gao/100+48;
	sdd5[7]=wendu_gao%100/10+48;
	sdd5[8]=wendu_gao%10+48;		//�ռ������¶�����ת������ʾҺ����

	sdd6[6]=wendu_di/100+48;
	sdd6[7]=wendu_di%100/10+48;
	sdd6[8]=wendu_di%10+48;		//�ռ������¶�����ת������ʾҺ����
}


/***********************************************************************
* ��������lcd_display
* ������1602Һ����ʾ����
* ���룺��
* �������
* ���ã��ⲿ����
***********************************************************************/
void lcd_displayKS()		   //ϵͳ���ϵ��һ��ʼ��ʾ���Ǹ�����
{ 
		unsigned char num1;
		
 		write_command(0x80+0x00);
		for(num1=0;num1<16;num1++)
			write_data(kai[num1]);	 	

		write_command(0x80+0x40);
		for(num1=0;num1<16;num1++)
			write_data(shi[num1]);	 		
}

void lcd_display1()
{ 
		unsigned char num1;
		
 		write_command(0x80+0x00);
		for(num1=0;num1<5;num1++)
			write_data(sdd1[num1]);	 		

		write_command(0x80+0x40);
		for(num1=0;num1<5;num1++)
			write_data(sdd2[num1]);	 	
}

void lcd_display2()
{ 
		unsigned char num1;
		unsigned char var_1;
		unsigned char var_2;

		if (1 == flag)
		{
			var_1 = 16;
			var_2 = 9;	
		}
		else if (2 == flag)
		{
			var_1 = 9;
			var_2 = 16;
		}
 		write_command(0x80+0x00);
		for(num1=0;num1<var_1;num1++)
			write_data(sdd3[num1]);	 

		write_command(0x80+0x40);
		for(num1=0;num1<var_2;num1++)
			write_data(sdd4[num1]);	 		
}

void lcd_display3()
{ 
		unsigned char num1;
		unsigned char var_1;
		unsigned char var_2;

		if (3 == flag)
		{
			var_1 = 16;
			var_2 = 9;	
		}
		else if (4 == flag)
		{
			var_1 = 9;
			var_2 = 16;
		}		

 		write_command(0x80+0x00);
		for(num1=0;num1<var_1;num1++)
			write_data(sdd5[num1]);	 	

		write_command(0x80+0x40);
		for(num1=0;num1<var_2;num1++)
			write_data(sdd6[num1]);	 	
}

void lcd_display4()
{ 
		unsigned char num1;
		
 		write_command(0x80+0x00);
		for(num1=0;num1<13;num1++)
			write_data(she[num1]);	 	

		write_command(0x80+0x40);
		for(num1=0;num1<16;num1++)
			write_data(zhi[num1]);	 	
}

void lcd_display5()
{ 
		unsigned char num1;
		
 		write_command(0x80+0x03);
		for(num1=0;num1<10;num1++)
			write_data(ban[num1]);	 		

		write_command(0x80+0x45);
		for(num1=0;num1<7;num1++)
			write_data(ji[num1]);	 	
}

void init_all(void)		//ϵͳ��ʼ��
{
	Timer1Init();   //���ڶ�ʱ����ʼ��
	Timer0Init();   //��ʱ��0��ʼ��
	lcd_init();					 //��ʼ��1602Һ��	
	jidianqi = 1;
	fengmingqi = 1;
	lcd_displayKS();
	delay__ms(1500);
//	lcd_init();	
}

void main(void)
{
	init_all();

	write_command(0x01);	//����
	lcd_display5();
	delay__ms(1500);
	
//	SendData(str) ;   //���͵����� 
//	Delay_t(1);         //��ʱ100US��12M����)
//
//	delay(4000);

//EEPROM
//	IIC_EEPROM_Write(0x20, 90);
//		delay__ms(1000);
//	IIC_EEPROM_Write(0x22, 20);
//		delay__ms(1000);
//	IIC_EEPROM_Write(0x24, 50);
//		delay__ms(1000);
//	IIC_EEPROM_Write(0x26, 0);	 
//		delay__ms(1000);delay__ms(2000);				//��¼��һ�κ�Ͳ�����

	sdd1[0]='H'; sdd1[1]=':';
	sdd2[0]='T'; sdd2[1]=':';
	sdd3[0]='H'; sdd3[1]='-'; sdd3[2]='G'; sdd3[3]='A'; sdd3[4]='O'; sdd3[5]=':'; sdd3[9]=' ';sdd3[10]='c';sdd3[11]='h';sdd3[12]='a';sdd3[13]='n';sdd3[14]='g';sdd3[15]='e';
	sdd4[0]='H'; sdd4[1]='-'; sdd4[2]='D'; sdd4[3]='I'; sdd4[4]=' '; sdd4[5]=':'; sdd4[9]=' ';sdd4[10]='c';sdd4[11]='h';sdd4[12]='a';sdd4[13]='n';sdd4[14]='g';sdd4[15]='e';
	sdd5[0]='T'; sdd5[1]='-'; sdd5[2]='G'; sdd5[3]='A'; sdd5[4]='O'; sdd5[5]=':'; sdd5[9]=' ';sdd5[10]='c';sdd5[11]='h';sdd5[12]='a';sdd5[13]='n';sdd5[14]='g';sdd5[15]='e';
	sdd6[0]='T'; sdd6[1]='-'; sdd6[2]='D'; sdd6[3]='I'; sdd6[4]=' '; sdd6[5]=':'; sdd6[9]=' ';sdd6[10]='c';sdd6[11]='h';sdd6[12]='a';sdd6[13]='n';sdd6[14]='g';sdd6[15]='e';

	//оƬһ�ϵ�Ͷ�ȡ����õ���AT24C02�����ֵ
	shidu_gao = IIC_EEPROM_Read(0x20);
	delay__ms(300);
	shidu_di = IIC_EEPROM_Read(0x22);
	delay__ms(300);
	wendu_gao = IIC_EEPROM_Read(0x24);
	delay__ms(300);
	wendu_di = IIC_EEPROM_Read(0x26);
	delay__ms(300);	delay__ms(300);

	no_loop = 1;

	while(1)
	{
		zhuanhua();
		
		if (flag > 4)	   //�¶�����ֵ�������
		{
//			 lcd_init();
			 write_command(0x01);	//����
			 lcd_display4();    //��ʾ��������OK

			 IIC_EEPROM_Write(0x20, shidu_gao);
			 delay__ms(1000);
			 IIC_EEPROM_Write(0x22, shidu_di);
			 delay__ms(1000);
			 IIC_EEPROM_Write(0x24, wendu_gao);
			 delay__ms(1000);
			 IIC_EEPROM_Write(0x26, wendu_di);
			 delay__ms(1000);
		}

		if (0 == flag)
		{
			write_command(0x01);	//����
			lcd_display1();
		}
		else if (flag>4)
		{
			flag = 0;
		}
		else
		{
			if (1==flag || 2==flag)
			{

				write_command(0x01);	//����
				lcd_display2();
			}
			else if (3==flag || 4==flag)
			{
				write_command(0x01);	//����
				lcd_display3();
			}
		}
		

		//������ʪ�ȴ��������ĸ�����
		   RH();
	   str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;

//	   SendData(str) ;  //���͵�����
//	   SendData(sdd1);  
//	   SendData(sdd2);  
	   //��ȡģ���������ڲ���С�� 2S 
	   Delay_t(10000);
	}
}
