/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   重定向c库printf函数到usart端口

  ******************************************************************************
  */ 
#include "sys.h"
#include "bsp_usart.h"	  
enum RECSTEP  avrecstep;
//串口1接收数组  
Uart_Rxtpye Uart1RX;
//串口2接收数组  
Uart_Rxtpye Uart2RX;
//串口3接收数组  
Uart_Rxtpye Uart3RX;
//串口1发送数据结构
Uart_Txtype Usart2TX;

 /**
  * @brief  USART1 GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	// 打开串口GPIO的时钟
	DEVICE1_USART_GPIO_APBxClkCmd(DEVICE1_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEVICE1_USART_APBxClkCmd(DEVICE1_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEVICE1_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE1_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEVICE1_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEVICE1_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEVICE1_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEVICE1_USARTx, &USART_InitStructure);
	
	 
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEVICE1_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	// 开启 串口空闲IDEL 中断
//	USART_ITConfig(DEVICE1_USARTx, USART_IT_IDLE, ENABLE);  
	USART_ITConfig(DEVICE1_USARTx,USART_IT_RXNE,ENABLE);  

	// 使能串口
	USART_Cmd(DEVICE1_USARTx, ENABLE);
  avrecstep=FRAMEHEAD1;	
}
 /**
  * @brief  USART2_Config 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
// 串口中断优先级配置
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// 打开串口GPIO的时钟
	BLE_USART_GPIO_APBxClkCmd(BLE_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	BLE_USART_APBxClkCmd(BLE_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = BLE_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BLE_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = BLE_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(BLE_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = BLE_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(BLE_USARTx, &USART_InitStructure);
	
  

  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = BLE_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	// 开启 串口空闲IDEL 中断
	USART_ITConfig(BLE_USARTx, USART_IT_IDLE, ENABLE);  
	USART_ITConfig(BLE_USARTx,USART_IT_RXNE,ENABLE);  

	// 使能串口
	USART_Cmd(BLE_USARTx, ENABLE);	    
}

 /**
  * @brief  USART3_Config 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	// 串口中断优先级配置
//	NVIC_InitTypeDef NVIC_InitStructure;
	// 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx, &USART_InitStructure);

  
  /* 嵌套向量中断控制器组选择 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
//  /* 配置USART为中断源 */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* 抢断优先级*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
//  /* 子优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  /* 使能中断 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* 初始化配置NVIC */
//  NVIC_Init(&NVIC_InitStructure);
	
//	// 开启 串口空闲IDEL 中断
//	USART_ITConfig(DEBUG_USARTx, USART_IT_IDLE, ENABLE);  
//	USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);  

	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}


uint8_t crc_check(uint8_t *ptr , uint8_t len)
{
	uint8_t i;
	uint8_t crc = 0x00;
	while(len--)
	{
		crc^=(*ptr++);
		for(i=8;i>0;--i)
		{
			if(crc & 0x80)
				crc = (crc<<1)^0x07;
			else
				crc = crc<<1;
		}
	}
	return(crc);
}

uint8_t HEX2BCD(uint8_t hex_data)
{
	uint8_t bcd_data;
	uint8_t temp;
	temp = hex_data % 100;
	bcd_data = (temp/10)<<4;
	bcd_data = bcd_data | (temp%10);
	return bcd_data ;
}
///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
} 
	

