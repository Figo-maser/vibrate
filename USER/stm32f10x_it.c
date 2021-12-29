/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 

#include "bsp_usart.h"
#include "bsp_GeneralTim.h" 
#include "bsp_led.h"
#include "bsp_key.h"  
#include "bsp_gpio.h"  

extern Device_set  device_setting ;
extern enum RECSTEP  avrecstep;

void NMI_Handler(void)
{
}
 
//void HardFault_Handler(void)
//{
//  /* Go to infinite loop when Hard Fault exception occurs */
//  while (1)
//  {
//  }
//}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
/*********************************************************************************
  * @ 函数名  ： DEVICE1_USART_IRQHandler
  * @ 功能说明： 串口中断服务函数
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  ********************************************************************************/
void DEVICE1_USART_IRQHandler(void)
{
  uint8_t Res;
	if(USART_GetITStatus(DEVICE1_USARTx, USART_IT_RXNE) != RESET)  
	{
		USART_ClearITPendingBit(DEVICE1_USARTx, USART_IT_RXNE);	
		
    Res=USART_ReceiveData(DEVICE1_USARTx);	
		//Uart1RX.RXBuf[Uart1RX.USART_cnt++] = DEVICE1_USARTx->DR;
		switch(avrecstep)
		{
			case FRAMEHEAD1: if(Res == 0xaa )
												{
													Uart1RX.RXBuf[Uart1RX.USART_cnt++]=Res;
													avrecstep=FRAMEHEAD2;
												}
												break;
			case FRAMEHEAD2:
												if (Res == 0xaa)
												{
													Uart1RX.RXBuf[Uart1RX.USART_cnt++]=Res;
													
													avrecstep=LEN;
												}
												else
												{
													 Uart1RX.USART_cnt=0;
													 avrecstep=FRAMEHEAD1;
												}
												break;	
			case LEN:
												if (Res == 0x20)
												{
													Uart1RX.RXBuf[Uart1RX.USART_cnt++]=Res;
													
													avrecstep=DAT;
												}
												else
												{
													Uart1RX.USART_cnt=0;
													avrecstep=FRAMEHEAD1;
												}										
										    break;
			case DAT:					if(Uart1RX.USART_cnt<34)
												{
													Uart1RX.RXBuf[Uart1RX.USART_cnt++]=Res;
												}
												else
												{
													Uart1RX.RXBuf[Uart1RX.USART_cnt++]=Res;
													avrecstep=SUM;
												}
												break;
			case SUM:         
												Uart1RX.RXBuf[Uart1RX.USART_cnt++]=Res;
												Uart1RX.receive_len = Uart1RX.USART_cnt;
												Uart1RX.USART_cnt =0 ;
												avrecstep=FRAMEHEAD1;
			                  Uart1RX.rec_finish = 1;
			
												break;
				
		}
  } 
//	if(USART_GetITStatus(DEVICE1_USARTx,USART_IT_IDLE)!=RESET)
//	{		
//		
//		DEVICE1_USARTx->SR;
//		DEVICE1_USARTx->DR;						
//		
//		Uart1RX.receive_len = Uart1RX.USART_cnt;
//		
//		Uart1RX.USART_cnt=0;
//		if(Uart1RX.receive_len>8)
//		{
//			Uart1RX.rec_finish = 1;
//		}
//	}	 

  

}



/*********************************************************************************
  * @ 函数名  ： BLE_USART_IRQHandler
  * @ 功能说明： 串口中断服务函数
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  ********************************************************************************/
void BLE_USART_IRQHandler(void)
{

	if(USART_GetITStatus(BLE_USARTx, USART_IT_RXNE) != RESET)  
	{
		USART_ClearITPendingBit(BLE_USARTx, USART_IT_RXNE);	
		//Usart_SendByte(BLE_USARTx,BLE_USARTx->DR);
    Uart2RX.RXBuf[Uart2RX.USART_cnt++]=BLE_USARTx->DR;	
  } 
	if(USART_GetITStatus(BLE_USARTx,USART_IT_IDLE)!=RESET)
	{		
		
		BLE_USARTx->SR;
		BLE_USARTx->DR;						
		
		Uart2RX.receive_len = Uart2RX.USART_cnt;
		Uart2RX.rec_finish = 1;
		Uart2RX.USART_cnt=0;
	}	 
  if (USART_GetITStatus(BLE_USARTx,USART_IT_TXE)!=RESET)
  {
 
		USART_ClearITPendingBit(BLE_USARTx, USART_IT_TXE);	 
		if(Usart2TX.TX_cnt<Usart2TX.USART_LEN)
		{
			USART_SendData(BLE_USARTx,Usart2TX.TXBuf[Usart2TX.TX_cnt++]);
		}
		else
		{
			USART_ITConfig(BLE_USARTx,USART_IT_TXE,DISABLE);
			Usart2TX.TX_cnt=0;
		}
  }  

}

uint16_t time_20ms =0 ;
extern uint8_t single_NOT_zero ;
/*********************************************************************************
  * @ 函数名  ： GENERAL_TIM_IRQHandler (void)
  * @ 功能说明： 定时器中断服务函数
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  ********************************************************************************/

void  GENERAL_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
		time++;
		if(Led_station ==Led_OFF)
		{
			LED_STATUS_OFF;
		}
		else if(Led_station ==Led_pwrON)
		{
			LED_STATUS_ON;
			if(time>=10000)
			{
				time = 0;
				time_1s++;
			}
			if(time_1s>=3)
			{
				
				time_1s =0;
//				LED_STATUS_OFF;
//				Led_station = Led_OFF;
				device_setting.power_flag =1; //开机标志位置1
			}
		}

		else if(Led_station == Led_pwrOFF)
		{
			single_NOT_zero =0;
			if(time>=500)
			{
				time = 0;
				time_1s++;
				LED_STATUS_TOGGLE;
			}
			if(time_1s>=60)
			{
				
				time_1s =0;
				LED_STATUS_OFF;
				Led_station = Led_OFF;
				POWER_CTL(0);  //关机
			}
		}
		else if(Led_station == Led_twinkle)
		{
			if(time>=10000)
			{
				time = 0;
				
				LED_STATUS_TOGGLE;
			}

		}
		else if(Led_station == Led_green_on)
		{
			LED_STATUS_ON;
		}
		time_20ms ++;
		if(time_20ms>=200)
		{
			time_20ms =0 ;
			Key_Scan();
		}
		TIM_ClearITPendingBit(GENERAL_TIM , TIM_FLAG_Update);  		 
	}		 	
}

///*********************************************************************************
//  * @ 函数名  ： BLE_USART_IRQHandler
//  * @ 功能说明： 串口中断服务函数
//  * @ 参数    ： 无  
//  * @ 返回值  ： 无
//  ********************************************************************************/
//void BLE_USART_IRQHandler(void)
//{

//	if(USART_GetITStatus(BLE_USARTx, USART_IT_RXNE) != RESET)  
//	{
//		USART_ClearITPendingBit(BLE_USARTx, USART_IT_RXNE);	
//    Uart3RX.RXBuf[Uart3RX.USART_cnt++]=BLE_USARTx->DR;	
//  } 
//	if(USART_GetITStatus(BLE_USARTx,USART_IT_IDLE)!=RESET)
//	{		
//		
//		BLE_USARTx->SR;
//		BLE_USARTx->DR;						
//		
//		Uart3RX.receive_len = Uart3RX.USART_cnt;

//		Uart3RX.USART_cnt=0;
//	}	 
//  
//}

