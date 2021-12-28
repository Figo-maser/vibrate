/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  */
#include "bsp_led.h"

uint8_t Led_station = Led_OFF ;
 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 /*����LED��ص�GPIO����ʱ��*/
	RCC_APB2PeriphClockCmd( LED_STATUS_GPIO_CLK , ENABLE);
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = LED_STATUS_GPIO_PIN;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(LED_STATUS_GPIO_PORT, &GPIO_InitStructure);	
	
	LED_STATUS_OFF;
}
 
