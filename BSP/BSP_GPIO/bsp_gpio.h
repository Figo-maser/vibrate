#ifndef __GPIO_H
#define	__GPIO_H


#include "stm32f10x.h"


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */


#define PWR_CTL_GPIO_PORT         GPIOB			              /* GPIO�˿� */
#define PWR_CTL_GPIO_CLK 	        RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define PWR_CTL_GPIO_PIN		      GPIO_Pin_6			        /* ���ӵ�PWR_CTLʱ���ߵ�GPIO */

/* ���κ꣬��������������һ��ʹ�� */

#define POWER_CTL(a)	if (a)	\
					GPIO_SetBits(PWR_CTL_GPIO_PORT,PWR_CTL_GPIO_PIN);\
					else		\
					GPIO_ResetBits(PWR_CTL_GPIO_PORT,PWR_CTL_GPIO_PIN)
					
				
					
					
void GPIO_Config(void);


#endif /* __LED_H */
