#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


/******************************* 宏定义 ************************************/

#define Led_pwrOFF    0
#define Led_pwrON     1
#define Led_OFF       2
#define Led_twinkle   3

#define LED_STATUS_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define LED_STATUS_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED_STATUS_GPIO_PIN		    GPIO_Pin_7			        /* 连接到SCL时钟线的GPIO */

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

/* 定义控制IO的宏 */
#define LED_STATUS_TOGGLE		 digitalToggle(LED_STATUS_GPIO_PORT,LED_STATUS_GPIO_PIN)
#define LED_STATUS_OFF		   digitalHi(LED_STATUS_GPIO_PORT,LED_STATUS_GPIO_PIN)
#define LED_STATUS_ON			   digitalLo(LED_STATUS_GPIO_PORT,LED_STATUS_GPIO_PIN)

extern uint8_t Led_station;

void LED_Init(void);//初始化

		 				    
#endif
