						   
/********************************************************************************																			    	   
* ����дʱ�䡿�� 2011.07.07
* ����    �ߡ��� �������
* ����    ������ V1.0
* ����    վ���� http://ylelectronic.taobao.com/ 
* ��Q      Q���� 348439350
* ����    ������ �˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��
* ���������ܡ��� AT24C02ʵ��
* ����    ��:  11.0592M		    
* ��Ӳ�����ӡ��� ����	ѡ��ģ��			���ӻ�Ͽ�
                 J1		8λ�����ģ��		����
				 J2		����ģ��			�Ͽ�
				 J3		ʱ��ģ��			�Ͽ�
				 J4		8λ�����ģ��		�Ͽ�
				 J6		������ģ��			�Ͽ�
				 J7		�̵���ģ��			�Ͽ� 		   			            			    
* ��ʹ��˵������	���¶�������K1 ��������     
                    ���¶�������K2 ��ȡ����						   	           
                    ���¶�������K3 ���ݼ�1    
                    ���¶�������K4 ���ݼ�1  
*******************************************************************************/
/*Ԥ��������*/
#include<reg52.h>    //������Ƭ���Ĵ�����ͷ�ļ�	 
#include<Function.h>
#define uchar unsigned char
#define uint unsigned int

#define  AT24C02 0xa0  //AT24C02 ��ַ

sbit MOSIO=P2^2;	   //��λ�Ĵ���-���������
sbit R_CLKa=P2^3;
sbit S_CLKa=P2^4; 

sbit K1=P3^2;	 //����
sbit K2=P3^3;	 //��ȡ
sbit K3=P3^4;	 //+����
sbit K4=P3^5;   //-����

uchar code duan[]={~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F};//�˱�ΪLED����������ܶ�ѡ��ģ 
uchar code wei[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};	//�˱�ΪLED�����λѡ��ģ

uchar Count1;
unsigned long D[16], LedOut[5],LedNumVal;
uint idata USEC;

void delay(uint i)
{
    char j;
    for(i; i > 0; i--)
        for(j = 200; j > 0; j--);
}  
/***************74HC595��������ܳ���******************/
void send595(uchar dat)	   //��������
{  
	uchar i; 	
	for(i=0;i<8;i++) 
	{
		if((dat<<i)&0x80) 
			MOSIO=1; 
		else MOSIO=0;
		
		S_CLKa=0;
		S_CLKa=1;	
	}	

}
void out595(void)			  // �������
{
	R_CLKa=0;
	R_CLKa=1;	//������
} 
void disp(uchar w,uchar d)	  //�������ʾ������w-λ�룬d-����
{
	send595(wei[w]);
	send595(duan[d]);
	out595();
}
void dispoff()      //�رչ��������
{
	send595(0);
	out595();
	
	send595(0xff);
	out595();
}
/**********************ϵͳ��ʼ��*************************/
void  system_ini() 
{    
    TMOD|= 0x11;
    TH1=0xfe; //11.0592
	TL1=0x33;
	TR1=1; 
    IE=0x8A;
}
/**********************������**************************/
void main()
{
	uchar i;
	uchar pDat[8];
	dispoff();			//�ȹر������
	system_ini();
	while(1)
	{
		//========================IIC ��ȡ
		if(K2 == 0)	   //�ڶ�����ť��ȡ����
		{ 
			IRcvStr(AT24C02, 0 , &pDat[0], 8); 
			for (i=0; i<4; i++)
			{
				D[14+i]=pDat[i*2+0]+pDat[i*2+1]*0x100;
				Count1 = D[14];
			}	     
		}
		
		//========================IIC ����
		if(K1 == 0)    //��һ����ť��������
		{ 
			D[14]= Count1;
			for (i=0; i<4; i++)
			{
				pDat[i*2+0]=D[14+i];
				pDat[i*2+1]=D[14+i]>>8;
			}
			ISendStr(AT24C02, 0 , &pDat[0], 8); 
		}
		
		
		/********���½�2402�б���������͵�LED�������ʾ*************/
		LedNumVal=Count1;
		LedOut[0]=LedNumVal%10000/1000;
		LedOut[1]=LedNumVal%1000/100;
		LedOut[2]=LedNumVal%100/10;
		LedOut[3]=LedNumVal%10; 
		
		for(i=0; i<4; i++) 
		{		
			disp(i,LedOut[i]);
			delay(150);
		}	
	}
} 

/*************************************
 [ t1 (0.5ms)�ж�] �ж����� PWM ���
  ------------1000/(0.02ms*250)=200Hz
*************************************/
void T1zd(void) interrupt 3   //3 Ϊ��ʱ��1���жϺ�  1 ��ʱ��0���жϺ� 0 �ⲿ�ж�1 2 �ⲿ�ж�2  4 �����ж�
{
	 TH1 = 0xfe; //12M	
	 TL1 = 0x33;
   if(USEC++==200)
   {	USEC=0;
	 
    if (K3) Count1++;     //�ı�����
    if (K4&Count1!=0) Count1--;
  
    }  

}


