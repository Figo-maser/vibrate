/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  g-f
  * @version V1.0
  * @date    2021-xx-xx
  * @brief   �ض���c��printf������usart�˿�

  ******************************************************************************
  */ 
#include "sys.h"
#include "bsp_usart.h"	  
enum RECSTEP  avrecstep;
//����1��������  
Uart_Rxtpye Uart1RX;
//����2��������  
Uart_Rxtpye Uart2RX;
//����3��������  
Uart_Rxtpye Uart3RX;
//����1�������ݽṹ
Uart_Txtype Usart2TX;

 /**
  * @brief  USART1 GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	// �򿪴���GPIO��ʱ��
	DEVICE1_USART_GPIO_APBxClkCmd(DEVICE1_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEVICE1_USART_APBxClkCmd(DEVICE1_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEVICE1_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE1_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEVICE1_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEVICE1_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEVICE1_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEVICE1_USARTx, &USART_InitStructure);
	
	 
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEVICE1_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	// ���� ���ڿ���IDEL �ж�
//	USART_ITConfig(DEVICE1_USARTx, USART_IT_IDLE, ENABLE);  
	USART_ITConfig(DEVICE1_USARTx,USART_IT_RXNE,ENABLE);  

	// ʹ�ܴ���
	USART_Cmd(DEVICE1_USARTx, ENABLE);
  avrecstep=FRAMEHEAD1;	
}
 /**
  * @brief  USART2_Config ����,������������
  * @param  ��
  * @retval ��
  */
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
// �����ж����ȼ�����
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// �򿪴���GPIO��ʱ��
	BLE_USART_GPIO_APBxClkCmd(BLE_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	BLE_USART_APBxClkCmd(BLE_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = BLE_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BLE_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = BLE_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(BLE_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = BLE_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(BLE_USARTx, &USART_InitStructure);
	
  

  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = BLE_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	// ���� ���ڿ���IDEL �ж�
	USART_ITConfig(BLE_USARTx, USART_IT_IDLE, ENABLE);  
	USART_ITConfig(BLE_USARTx,USART_IT_RXNE,ENABLE);  

	// ʹ�ܴ���
	USART_Cmd(BLE_USARTx, ENABLE);	    
}

 /**
  * @brief  USART3_Config ����,������������
  * @param  ��
  * @retval ��
  */
void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	// �����ж����ȼ�����
//	NVIC_InitTypeDef NVIC_InitStructure;
	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);

  
  /* Ƕ�������жϿ�������ѡ�� */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
//  /* ����USARTΪ�ж�Դ */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* �������ȼ�*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
//  /* �����ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  /* ʹ���ж� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure);
	
//	// ���� ���ڿ���IDEL �ж�
//	USART_ITConfig(DEBUG_USARTx, USART_IT_IDLE, ENABLE);  
//	USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);  

	// ʹ�ܴ���
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
///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
} 
	

