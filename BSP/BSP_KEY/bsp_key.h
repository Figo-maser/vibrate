#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"

#define BOUNDING     1
#define DISBOUND     0
#define BLE_WORK     1
#define BLE_SLEEP    0

//  引脚定义
#define    LINK_GPIO_CLK            RCC_APB2Periph_GPIOA
#define    LINK_GPIO_PORT           GPIOA			   
#define    LINK_GPIO_PIN		        GPIO_Pin_7

#define    LPOUT_GPIO_CLK           RCC_APB2Periph_GPIOA
#define    LPOUT_GPIO_PORT          GPIOA		   
#define    LPOUT_GPIO_PIN		        GPIO_Pin_8

#define    PWR_SW_GPIO_PORT         GPIOB			              /* GPIO端口 */
#define    PWR_SW_GPIO_CLK 	        RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define    PWR_SW_GPIO_PIN		      GPIO_Pin_13			        /* 连接到SCL时钟线的GPIO */

//#define    BLE_REDY_GPIO_PORT         GPIOC		              /* GPIO端口 */
//#define    BLE_REDY_GPIO_CLK 	        RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
//#define    BLE_REDY_GPIO_PIN		      GPIO_Pin_13			        /* 连接到SCL时钟线的GPIO */


 /** 按键按下标置宏
	*  按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	*  若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define KEY_ON	1
#define KEY_OFF	0

/*
	按键滤波时间50ms, 单位10ms。
	只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件
	即使按键电路不做硬件滤波，该滤波机制也可以保证可靠地检测到按键事件
*/
#define KEY_FILTER_TIME   5
#define KEY_LONG_TIME     150			/* 单位20ms， 持续3秒，认为长按事件 */
#define KEY_ALWAYS_UP     500     /* 单位20ms， 持续10秒，认为长按事件 */
/*
	每个按键对应1个全局的结构体变量。
*/
typedef struct
{
	/* 下面是一个函数指针，指向判断按键手否按下的函数 */
	uint8_t (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

	uint8_t  Count;			/* 滤波器计数器 */
	uint16_t LongCount;		/* 长按计数器 */
	uint16_t LongTime;		/* 按键按下持续时间, 0表示不检测长按 */
	uint8_t  State;			/* 按键当前状态（按下还是弹起） */
	uint8_t  LongState; /*长按状态*/
	uint8_t  RepeatSpeed;	/* 连续按键周期 */
	uint8_t  RepeatCount;	/* 连续按键计数器 */
}KEY_T;

extern  KEY_T key_pwr;
extern  KEY_T key_bleLink;

void Key_GPIO_Config(void);

void Key_Scan(void);

void EXTIX_Init(void);
#endif /* __KEY_H */

