/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  */
#include "bsp_led.h"

uint8_t Led_station = Led_OFF ;
 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 /*开启LED相关的GPIO外设时钟*/
	RCC_APB2PeriphClockCmd( LED_STATUS_GPIO_CLK , ENABLE);
	/*选择要控制的GPIO引脚*/
	GPIO_InitStructure.GPIO_Pin = LED_STATUS_GPIO_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIO*/
	GPIO_Init(LED_STATUS_GPIO_PORT, &GPIO_InitStructure);	
	
	LED_STATUS_OFF;
}
 
