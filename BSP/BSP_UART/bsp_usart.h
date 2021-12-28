#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

// 串口1-USART1
#define  DEVICE1_USARTx                   USART1
#define  DEVICE1_USART_CLK                RCC_APB2Periph_USART1
#define  DEVICE1_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEVICE1_USART_BAUDRATE           57600

// USART GPIO 引脚宏定义
#define  DEVICE1_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEVICE1_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEVICE1_USART_TX_GPIO_PORT       GPIOA   
#define  DEVICE1_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEVICE1_USART_RX_GPIO_PORT       GPIOA
#define  DEVICE1_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEVICE1_USART_IRQ                USART1_IRQn
#define  DEVICE1_USART_IRQHandler         USART1_IRQHandler


// 串口2-USART2
#define  BLE_USARTx                   USART2
#define  BLE_USART_CLK                RCC_APB1Periph_USART2
#define  BLE_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  BLE_USART_BAUDRATE           9600

// USART GPIO 引脚宏定义
#define  BLE_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  BLE_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  BLE_USART_TX_GPIO_PORT       GPIOA   
#define  BLE_USART_TX_GPIO_PIN        GPIO_Pin_2
#define  BLE_USART_RX_GPIO_PORT       GPIOA
#define  BLE_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  BLE_USART_IRQ                USART2_IRQn
#define  BLE_USART_IRQHandler         USART2_IRQHandler

// 串口3-USART3
#define  DEBUG_USARTx                   USART3
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART3
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOB   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT       GPIOB
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART_IRQ                USART3_IRQn
#define  DEBUG_USART_IRQHandler         USART3_IRQHandler


typedef struct Msg
{
	uint8_t RXBuf[200];
  uint8_t USART_cnt;
  uint8_t rec_finish;
	uint16_t receive_len;
}Uart_Rxtpye;


typedef struct
{
	uint8_t  TXBuf[200];
	uint8_t  TX_cnt;
	uint16_t USART_LEN;
}Uart_Txtype;

typedef struct 
{
	uint8_t Bound_station;
	uint8_t Ble_station;
	uint8_t Device_mode;
	float Persent_power;
	float Vlotage_base;
	uint16_t Disconnetc_time_5min;
	uint16_t Disconnetc_time_20min;
	uint8_t power_flag  ;
}Device_set;

enum RECSTEP{
    FRAMEHEAD1=1,
    FRAMEHEAD2,
	  LEN,
    DAT,
    SUM,
};

extern              Uart_Rxtpye Uart1RX;
extern              Uart_Rxtpye Uart2RX;
extern              Uart_Rxtpye Uart3RX;
extern              Uart_Txtype Usart2TX;

void USART1_Config(void);
void USART2_Config(void);
void USART3_Config(void);

uint8_t crc_check(uint8_t *ptr , uint8_t len);
uint8_t HEX2BCD(uint8_t hex_data);

#endif


