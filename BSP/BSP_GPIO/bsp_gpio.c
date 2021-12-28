/**
  ******************************************************************************
  * @file    bsp_gpio.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   led应用函数接口

  ******************************************************************************
  */
  
#include "bsp_gpio.h"   

 /**
  * @brief  初始化控制的IO
  * @param  无
  * @retval 无
  */
void GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( PWR_CTL_GPIO_CLK, ENABLE);

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = PWR_CTL_GPIO_PIN ;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(PWR_CTL_GPIO_PORT, &GPIO_InitStructure);

}

/*********************************************END OF FILE**********************/
