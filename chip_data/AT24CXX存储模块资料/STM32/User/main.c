/*********************************************************************************************************
*
* File                : main.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "24C02.h"
#include <string.h>
#include <stdio.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
void USART_Configuration(void);


/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
  uint16_t Addr;
	uint8_t WriteBuffer[256],ReadBuffer[256];

  GPIO_Configuration();
  USART_Configuration();
	I2C_Configuration();

  printf("\r\n****************************************************************\r\n");

	for(Addr=0; Addr<256; Addr++)
	WriteBuffer[Addr]=Addr;	 /* 填充WriteBuffer */

	/* 开始向EEPROM写数据 */
 	printf("\r\n EEPROM 24C02 Write Test \r\n");
  I2C_Write(I2C1,ADDR_24LC02,0,WriteBuffer,sizeof(WriteBuffer) );
 	printf("\r\n EEPROM 24C02 Write Test OK \r\n");

  /* EEPROM读数据 */
	printf("\r\n EEPROM 24C02 Read Test \r\n");
	I2C_Read(I2C1,ADDR_24LC02,0,ReadBuffer,sizeof(WriteBuffer) );

	if(  memcmp(WriteBuffer,ReadBuffer,sizeof(WriteBuffer)) == 0 ) /* 匹配数据 */
	printf("\r\n EEPROM 24C02 Read Test OK\r\n");
	else
	printf("\r\n EEPROM 24C02 Read Test False\r\n");

    /* Infinite loop */

  while (1)
  {
	/*====LED-ON=======*/
	GPIO_SetBits(GPIOF , GPIO_Pin_6);
	GPIO_SetBits(GPIOF , GPIO_Pin_7);
	GPIO_SetBits(GPIOF , GPIO_Pin_8);
	GPIO_SetBits(GPIOF , GPIO_Pin_9);
	Delay(0xfffff);
	Delay(0xfffff);
	Delay(0x5ffff);	

	/*====LED-OFF=======*/ 
	GPIO_ResetBits(GPIOF , GPIO_Pin_6);
	GPIO_ResetBits(GPIOF , GPIO_Pin_7);
	GPIO_ResetBits(GPIOF , GPIO_Pin_8);
	GPIO_ResetBits(GPIOF , GPIO_Pin_9);
	Delay(0xfffff);
	Delay(0xfffff);
	Delay(0x5ffff);	
  }
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF , ENABLE); 						 
/**
 *  LED1 -> PF6 , LED2 -> PF7 , LED3 -> PF8 , LED4 -> PF9
 */					 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOF, &GPIO_InitStructure);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

