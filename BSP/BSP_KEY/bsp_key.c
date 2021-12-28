/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   按键应用bsp（扫描模式）
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
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(LINK_GPIO_CLK|LPOUT_GPIO_CLK | PWR_SW_GPIO_CLK ,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = LINK_GPIO_PIN; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(LINK_GPIO_PORT, &GPIO_InitStructure);
	
	key_bleLink.Count = KEY_FILTER_TIME / 2;
	key_bleLink.LongTime = 80;	
	key_bleLink.State = 0 ;
	key_bleLink.LongState = 0;
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = LPOUT_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	//使用结构体初始化按键
	GPIO_Init(LPOUT_GPIO_PORT, &GPIO_InitStructure);	
	
		//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = PWR_SW_GPIO_PIN; 
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	//使用结构体初始化按键
	GPIO_Init(PWR_SW_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_SetBits(PWR_SW_GPIO_PORT,PWR_SW_GPIO_PIN);
	
	
	key_pwr.Count = KEY_FILTER_TIME / 2;
	key_pwr.LongTime = KEY_LONG_TIME;	
	key_pwr.State = 0 ;
	key_pwr.LongState = 0;
	
//			//选择按键的引脚
//	GPIO_InitStructure.GPIO_Pin = BLE_REDY_GPIO_PIN; 
//	//设置按键的引脚为浮空输入
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	/* 输入浮空模式 */
//	//使用结构体初始化按键
//	GPIO_Init(BLE_REDY_GPIO_PORT, &GPIO_InitStructure);	
//	

	
}

extern uint8_t single_NOT_zero ;
 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：
 *		     	
 * 输出  ：
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
				if ((key_pwr.State == 1) &&  (key_pwr.LongState == 0))  //蓝牙短按唤醒
				{
					key_pwr.State = 0;																		
				}
			}
		}
		
		if((GPIO_ReadInputDataBit(LINK_GPIO_PORT,LINK_GPIO_PIN) == KEY_OFF) )
		{
			if(device_setting.Bound_station == DISBOUND)
			{
				device_setting.Bound_station = BOUNDING ;   //蓝牙连接
				device_setting.Ble_station = BLE_WORK; 

			}
		}
		else if(GPIO_ReadInputDataBit(LINK_GPIO_PORT,LINK_GPIO_PIN) == KEY_ON)
		{
			if(device_setting.Bound_station == BOUNDING)
			{
				device_setting.Bound_station = DISBOUND ;   //蓝牙连接
				device_setting.Ble_station = BLE_SLEEP; 
	
			}
						
		}
	}

}

int PWRDownFlag;  
//外部中断0服务程序
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;



  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOE.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

//   //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
//  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	
 
}

//外部中断0服务程序 
void EXTI15_10_IRQHandler(void)
{
if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
	{
		delay_ms(800);   //消抖			 
    if(GPIO_ReadInputDataBit(PWR_SW_GPIO_PORT,PWR_SW_GPIO_PIN) == KEY_OFF)		//按键0
		{
			PWRDownFlag=1;
		
		}	
	}		
	EXTI_ClearITPendingBit(EXTI_Line13); //清除LINE0上的中断标志位  
}
/*********************************************END OF FILE**********************/
