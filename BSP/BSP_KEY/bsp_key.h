#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"

#define BOUNDING     1
#define DISBOUND     0
#define BLE_WORK     1
#define BLE_SLEEP    0

//  ���Ŷ���
#define    LINK_GPIO_CLK            RCC_APB2Periph_GPIOA
#define    LINK_GPIO_PORT           GPIOA			   
#define    LINK_GPIO_PIN		        GPIO_Pin_7

#define    LPOUT_GPIO_CLK           RCC_APB2Periph_GPIOA
#define    LPOUT_GPIO_PORT          GPIOA		   
#define    LPOUT_GPIO_PIN		        GPIO_Pin_8

#define    PWR_SW_GPIO_PORT         GPIOB			              /* GPIO�˿� */
#define    PWR_SW_GPIO_CLK 	        RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define    PWR_SW_GPIO_PIN		      GPIO_Pin_13			        /* ���ӵ�SCLʱ���ߵ�GPIO */

//#define    BLE_REDY_GPIO_PORT         GPIOC		              /* GPIO�˿� */
//#define    BLE_REDY_GPIO_CLK 	        RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
//#define    BLE_REDY_GPIO_PIN		      GPIO_Pin_13			        /* ���ӵ�SCLʱ���ߵ�GPIO */


 /** �������±��ú�
	*  ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	*  ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define KEY_ON	1
#define KEY_OFF	0

/*
	�����˲�ʱ��50ms, ��λ10ms��
	ֻ��������⵽50ms״̬�������Ϊ��Ч����������Ͱ��������¼�
	��ʹ������·����Ӳ���˲������˲�����Ҳ���Ա�֤�ɿ��ؼ�⵽�����¼�
*/
#define KEY_FILTER_TIME   5
#define KEY_LONG_TIME     150			/* ��λ20ms�� ����3�룬��Ϊ�����¼� */
#define KEY_ALWAYS_UP     500     /* ��λ20ms�� ����10�룬��Ϊ�����¼� */
/*
	ÿ��������Ӧ1��ȫ�ֵĽṹ�������
*/
typedef struct
{
	/* ������һ������ָ�룬ָ���жϰ����ַ��µĺ��� */
	uint8_t (*IsKeyDownFunc)(void); /* �������µ��жϺ���,1��ʾ���� */

	uint8_t  Count;			/* �˲��������� */
	uint16_t LongCount;		/* ���������� */
	uint16_t LongTime;		/* �������³���ʱ��, 0��ʾ����ⳤ�� */
	uint8_t  State;			/* ������ǰ״̬�����»��ǵ��� */
	uint8_t  LongState; /*����״̬*/
	uint8_t  RepeatSpeed;	/* ������������ */
	uint8_t  RepeatCount;	/* �������������� */
}KEY_T;

extern  KEY_T key_pwr;
extern  KEY_T key_bleLink;

void Key_GPIO_Config(void);

void Key_Scan(void);

void EXTIX_Init(void);
#endif /* __KEY_H */

