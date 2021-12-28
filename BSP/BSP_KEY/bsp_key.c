/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  */ 
  
#include "bsp_key.h"  
#include "bsp_usart.h"
#include "bsp_gpio.h" 
#include "delay.h"

#include "bsp_GeneralTim.h" 
#include "bsp_led.h"
KEY_T key_pwr;
KEY_T key_bleLink;

extern Device_set  device_setting ;

/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(LINK_GPIO_CLK|LPOUT_GPIO_CLK | PWR_SW_GPIO_CLK ,ENABLE);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = LINK_GPIO_PIN; 
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(LINK_GPIO_PORT, &GPIO_InitStructure);
	
	key_bleLink.Count = KEY_FILTER_TIME / 2;
	key_bleLink.LongTime = 80;	
	key_bleLink.State = 0 ;
	key_bleLink.LongState = 0;
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = LPOUT_GPIO_PIN; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(LPOUT_GPIO_PORT, &GPIO_InitStructure);	
	
		//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = PWR_SW_GPIO_PIN; 
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(PWR_SW_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_SetBits(PWR_SW_GPIO_PORT,PWR_SW_GPIO_PIN);
	
	
	key_pwr.Count = KEY_FILTER_TIME / 2;
	key_pwr.LongTime = KEY_LONG_TIME;	
	key_pwr.State = 0 ;
	key_pwr.LongState = 0;
	
//			//ѡ�񰴼�������
//	GPIO_InitStructure.GPIO_Pin = BLE_REDY_GPIO_PIN; 
//	//���ð���������Ϊ��������
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	/* ���븡��ģʽ */
//	//ʹ�ýṹ���ʼ������
//	GPIO_Init(BLE_REDY_GPIO_PORT, &GPIO_InitStructure);	
//	

	
}

extern uint8_t single_NOT_zero ;
 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��
 *		     	
 * ���  ��
 */
void Key_Scan(void)
{			
	if(device_setting.power_flag == 1)
	{
		if(GPIO_ReadInputDataBit(PWR_SW_GPIO_PORT,PWR_SW_GPIO_PIN) == KEY_OFF)
		{
			if(key_pwr.Count < KEY_FILTER_TIME)
			{
				key_pwr.Count =  KEY_FILTER_TIME;
			}
			else if(key_pwr.Count < 2 * KEY_FILTER_TIME)
			{
				key_pwr.Count ++;
			}
			else
			{
				if(key_pwr.State == 0)
					key_pwr.State =1;
			}
			if(key_pwr.LongTime > 0)
			{
				if(key_pwr.LongCount < key_pwr.LongTime)
					key_pwr.LongCount++;
				else
				{
					key_pwr.LongState = 1;
							
					key_pwr.State = 0;
					key_pwr.LongState = 0;
					key_pwr.LongCount =0;
					Led_station = Led_pwrOFF ;
					time =0 ;
					time_1s =0 ;
					single_NOT_zero =0;
					device_setting.power_flag = 0;
					
								
							
				}
			}
		}
		else
		{
			key_pwr.LongCount = 0;
			key_pwr.LongState = 0;
			if(key_pwr.Count > KEY_FILTER_TIME)
			{
				key_pwr.Count = KEY_FILTER_TIME;
			}
			else if(key_pwr.Count != 0)
			{
				key_pwr.Count--;
			}
			else
			{
				if ((key_pwr.State == 1) &&  (key_pwr.LongState == 0))  //�����̰�����
				{
					key_pwr.State = 0;																		
				}
			}
		}
		
		if((GPIO_ReadInputDataBit(LINK_GPIO_PORT,LINK_GPIO_PIN) == KEY_OFF) )
		{
			if(device_setting.Bound_station == DISBOUND)
			{
				device_setting.Bound_station = BOUNDING ;   //��������
				device_setting.Ble_station = BLE_WORK; 

			}
		}
		else if(GPIO_ReadInputDataBit(LINK_GPIO_PORT,LINK_GPIO_PIN) == KEY_ON)
		{
			if(device_setting.Bound_station == BOUNDING)
			{
				device_setting.Bound_station = DISBOUND ;   //��������
				device_setting.Ble_station = BLE_SLEEP; 
	
			}
						
		}
	}

}

int PWRDownFlag;  
//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;



  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

//   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
//  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	
 
}

//�ⲿ�ж�0������� 
void EXTI15_10_IRQHandler(void)
{
if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
	{
		delay_ms(800);   //����			 
    if(GPIO_ReadInputDataBit(PWR_SW_GPIO_PORT,PWR_SW_GPIO_PIN) == KEY_OFF)		//����0
		{
			PWRDownFlag=1;
		
		}	
	}		
	EXTI_ClearITPendingBit(EXTI_Line13); //���LINE0�ϵ��жϱ�־λ  
}
/*********************************************END OF FILE**********************/
