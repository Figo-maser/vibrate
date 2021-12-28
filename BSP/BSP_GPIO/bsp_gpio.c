/**
  ******************************************************************************
  * @file    bsp_gpio.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   ledӦ�ú����ӿ�

  ******************************************************************************
  */
  
#include "bsp_gpio.h"   

 /**
  * @brief  ��ʼ�����Ƶ�IO
  * @param  ��
  * @retval ��
  */
void GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( PWR_CTL_GPIO_CLK, ENABLE);

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = PWR_CTL_GPIO_PIN ;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(PWR_CTL_GPIO_PORT, &GPIO_InitStructure);

}

/*********************************************END OF FILE**********************/
