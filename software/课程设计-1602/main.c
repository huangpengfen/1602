
/*
//键盘P15 P16 P17	 
//蜂鸣器 P00  spk=0蜂鸣器响
继电器 P24
按键  P33  P34  P35
at24C02  SCL P23
		 SDA P24
DHT11	P17
1602    数据/命令选择端rs P25
		读写控制端 P26
		使能端：P27 
		数据口：P0
*/


#include "reg52.h"
#include "intrins.h"
#include "1602.h"
#include "DHT11.h"
#include "AT24C02.h"
//按键设置引脚
sbit an1 = P3^5;
sbit an2 = P3^4;
sbit an3 = P3^3;
//继电器
sbit jidianqi = P3^6;
//蜂鸣器
sbit fengmingqi = P1^0;
//标志位  作为模式选择用的
unsigned char flag=0;     //flag=0,1,2,3,4,5  分别对应正常显示温湿度值，设置湿度的上限，设置湿度的下限，设置温度的上限，设置温度的下限，
						 //检测到设置好值后写入at24c01保存然后继续正常显示(即返回0)
uchar shidu_gao=90, shidu_di=40, wendu_gao=0, wendu_di=50;	   //设置湿度与温度的阈值（分别对应湿度高，湿度低，温度高，温度低）

unsigned char no_loop = 0;

unsigned char xdata sdd1[5];
unsigned char xdata sdd2[5];

unsigned char xdata sdd3[16];
unsigned char xdata sdd4[16];	
unsigned char xdata sdd5[16];
unsigned char xdata sdd6[16];		   //1602输出数组

unsigned char code she[]="H and T is OK";
unsigned char code zhi[]="data changing...";	//这两个数组是在系统设置阈值后显示写入at24c02的状态

unsigned char code kai[]="H Design by XXX.";
unsigned char code shi[]="  DORM: XX-XXX  ";	//这连个数组可以自由发挥，写自己的名字等

unsigned char code ban[]="XXXXXXXXXX";
unsigned char code ji[]="ClASS-X";		   //写上专业，班级

void delay_10_us(unsigned int num)		 //延时函数，延时时间为10us
{
	while(num--)
		;
}			   

/********************************************************************
 * 函数名：delay_ms
 * 描述  ：软件毫秒级延时(12Mhz的晶振)
 * 输入  ：-num:	控制需要延时多少毫秒。如num等于1，即延时1毫秒
 * 输出  ：无
 * 调用  ：外部调用
 ********************************************************************/
void delay__ms(unsigned int num)		   //延时函数，延时时间为xms
{
	unsigned int i;
	for(i=0;i<num;i++)
	{
		delay_10_us(100);
	}
}

//独立按键扫描
void keyscan(void)
{
	if (an1 == 0)
	{
		delay__ms(5);
		if (an1 == 0)
		{
			 //功能切换：切换湿度还是温度改变，最大阈值还是最小阈值
			 flag++;

		}
		while (!an1);
	}
	else if (an2 == 0)
	{
		delay__ms(5);
		if (an2 == 0)
		{
			//湿度/温度上升1
			switch(flag)
			{
				case 1:	//调节湿度上限
					shidu_gao++;
					break;
				case 2:	//调节湿度下限
					shidu_di++;
					break;
				case 3:	//调节温度上限
					wendu_gao++;
					break;
				case 4:	//调节温度下限
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
			//湿度/温度下降1
			switch(flag)
			{
				case 1:	//调节湿度上限
					shidu_gao--;
					break;
				case 2:	//调节湿度下限
					shidu_di--;
					break;
				case 3:	//调节温度上限
					wendu_gao--;
					break;
				case 4:	//调节温度下限
					wendu_di--;
					break;
				default:
					break;
			}
		}
		while (!an3);
	}
}

void baojing(void)		//报警函数，当超出阈值时报警
{
	if (U8RH_data_H<shidu_di || U8RH_data_H>shidu_gao)
	{
		//湿度报警
		jidianqi = 0;
		fengmingqi = 0;
	}
	else if (U8T_data_H<wendu_di || U8T_data_H>wendu_gao)
	{
		//温度报警
		jidianqi = 0;
		fengmingqi = 0;
	}
	else
	{
		//没报警
		jidianqi = 1;
		fengmingqi = 1;
	}
}

void Timer1Init(void)		//定时器
{
	TMOD = 0x20;	  //定时器T1使用工作方式2
	TH1 = 253;        // 设置初值
	TL1 = 253;
	TR1 = 1;          // 开始计时
	SCON = 0x50;	  //工作方式1，波特率9600bps，允许接收   
	ES = 1;
	EA = 1;           // 打开所以中断   
	TI = 0;
	RI = 0;
}

void Timer0Init(void)		//定时器初始化，10毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xF0;		//设置定时初值
	TH0 = 0xD8;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时

	ET0 = 1;
	EA = 1;
}
	

void timer0() interrupt 1		//定时器服务函数
{
	if (1 == no_loop)
	{
		keyscan();
		baojing();
	}
}


void zhuanhua()			  //将获取到的数据转化成能够在1602显示的字符
{
	sdd1[2]=str[0]/100+48;
	sdd1[3]=str[0]%100/10+48;
	sdd1[4]=str[0]%10+48;		 //收集到的湿度数据转化后（显示液晶）

	sdd2[2]=str[2]/100+48;
	sdd2[3]=str[2]%100/10+48;
	sdd2[4]=str[2]%10+48;		//收集到的温度数据转化后（显示液晶）

	sdd3[6]=shidu_gao/100+48;
	sdd3[7]=shidu_gao%100/10+48;
	sdd3[8]=shidu_gao%10+48;		//收集到的温度数据转化后（显示液晶）

	sdd4[6]=shidu_di/100+48;
	sdd4[7]=shidu_di%100/10+48;
	sdd4[8]=shidu_di%10+48;		//收集到的温度数据转化后（显示液晶）

	sdd5[6]=wendu_gao/100+48;
	sdd5[7]=wendu_gao%100/10+48;
	sdd5[8]=wendu_gao%10+48;		//收集到的温度数据转化后（显示液晶）

	sdd6[6]=wendu_di/100+48;
	sdd6[7]=wendu_di%100/10+48;
	sdd6[8]=wendu_di%10+48;		//收集到的温度数据转化后（显示液晶）
}


/***********************************************************************
* 函数名：lcd_display
* 描述：1602液晶显示函数
* 输入：无
* 输出：无
* 调用：外部调用
***********************************************************************/
void lcd_displayKS()		   //系统接上电后一开始显示的那个数组
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

void init_all(void)		//系统初始化
{
	Timer1Init();   //串口定时器初始化
	Timer0Init();   //定时器0初始化
	lcd_init();					 //初始化1602液晶	
	jidianqi = 1;
	fengmingqi = 1;
	lcd_displayKS();
	delay__ms(1500);
//	lcd_init();	
}

void main(void)
{
	init_all();

	write_command(0x01);	//清屏
	lcd_display5();
	delay__ms(1500);
	
//	SendData(str) ;   //发送到串口 
//	Delay_t(1);         //延时100US（12M晶振)
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
//		delay__ms(1000);delay__ms(2000);				//烧录完一次后就不用了

	sdd1[0]='H'; sdd1[1]=':';
	sdd2[0]='T'; sdd2[1]=':';
	sdd3[0]='H'; sdd3[1]='-'; sdd3[2]='G'; sdd3[3]='A'; sdd3[4]='O'; sdd3[5]=':'; sdd3[9]=' ';sdd3[10]='c';sdd3[11]='h';sdd3[12]='a';sdd3[13]='n';sdd3[14]='g';sdd3[15]='e';
	sdd4[0]='H'; sdd4[1]='-'; sdd4[2]='D'; sdd4[3]='I'; sdd4[4]=' '; sdd4[5]=':'; sdd4[9]=' ';sdd4[10]='c';sdd4[11]='h';sdd4[12]='a';sdd4[13]='n';sdd4[14]='g';sdd4[15]='e';
	sdd5[0]='T'; sdd5[1]='-'; sdd5[2]='G'; sdd5[3]='A'; sdd5[4]='O'; sdd5[5]=':'; sdd5[9]=' ';sdd5[10]='c';sdd5[11]='h';sdd5[12]='a';sdd5[13]='n';sdd5[14]='g';sdd5[15]='e';
	sdd6[0]='T'; sdd6[1]='-'; sdd6[2]='D'; sdd6[3]='I'; sdd6[4]=' '; sdd6[5]=':'; sdd6[9]=' ';sdd6[10]='c';sdd6[11]='h';sdd6[12]='a';sdd6[13]='n';sdd6[14]='g';sdd6[15]='e';

	//芯片一上电就读取保存好的在AT24C02里面的值
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
		
		if (flag > 4)	   //温度上下值设置完成
		{
//			 lcd_init();
			 write_command(0x01);	//清屏
			 lcd_display4();    //显示正在设置OK

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
			write_command(0x01);	//清屏
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

				write_command(0x01);	//清屏
				lcd_display2();
			}
			else if (3==flag || 4==flag)
			{
				write_command(0x01);	//清屏
				lcd_display3();
			}
		}
		

		//接受温湿度传感器的四个数据
		   RH();
	   str[0]=U8RH_data_H;
	   str[1]=U8RH_data_L;
	   str[2]=U8T_data_H;
	   str[3]=U8T_data_L;
	   str[4]=U8checkdata;

//	   SendData(str) ;  //发送到串口
//	   SendData(sdd1);  
//	   SendData(sdd2);  
	   //读取模块数据周期不易小于 2S 
	   Delay_t(10000);
	}
}
