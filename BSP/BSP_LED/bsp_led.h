#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


/******************************* �궨�� ************************************/

#define Led_pwrOFF    0
#define Led_pwrON     1
#define Led_OFF       2
#define Led_twinkle   3

#define LED_STATUS_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define LED_STATUS_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LED_STATUS_GPIO_PIN		    GPIO_Pin_7			        /* ���ӵ�SCLʱ���ߵ�GPIO */

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

/* �������IO�ĺ� */
#define LED_STATUS_TOGGLE		 digitalToggle(LED_STATUS_GPIO_PORT,LED_STATUS_GPIO_PIN)
#define LED_STATUS_OFF		   digitalHi(LED_STATUS_GPIO_PORT,LED_STATUS_GPIO_PIN)
#define LED_STATUS_ON			   digitalLo(LED_STATUS_GPIO_PORT,LED_STATUS_GPIO_PIN)

extern uint8_t Led_station;

void LED_Init(void);//��ʼ��

		 				    
#endif
