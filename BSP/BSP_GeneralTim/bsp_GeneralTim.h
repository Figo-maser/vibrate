#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H


#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3

#define            GENERAL_TIM                   TIM4
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM_Period            99
#define            GENERAL_TIM_Prescaler         71
#define            GENERAL_TIM_IRQ               TIM4_IRQn
#define            GENERAL_TIM_IRQHandler        TIM4_IRQHandler

// TIM3 ����Ƚ�ͨ��4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH4_PORT          GPIOB
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_9

/**************************��������********************************/

extern uint16_t time_1s  ;
extern uint16_t time ;

void GENERAL_TIM_Init(void);


#endif	/* __BSP_GENERALTIME_H */


