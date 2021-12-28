#ifndef __GPIO_H
#define	__GPIO_H


#include "stm32f10x.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */


#define PWR_CTL_GPIO_PORT         GPIOB			              /* GPIO端口 */
#define PWR_CTL_GPIO_CLK 	        RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define PWR_CTL_GPIO_PIN		      GPIO_Pin_6			        /* 连接到PWR_CTL时钟线的GPIO */

/* 带参宏，可以像内联函数一样使用 */

#define POWER_CTL(a)	if (a)	\
					GPIO_SetBits(PWR_CTL_GPIO_PORT,PWR_CTL_GPIO_PIN);\
					else		\
					GPIO_ResetBits(PWR_CTL_GPIO_PORT,PWR_CTL_GPIO_PIN)
					
				
					
					
void GPIO_Config(void);


#endif /* __LED_H */
