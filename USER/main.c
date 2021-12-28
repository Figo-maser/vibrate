/**
  *********************************************************************
  * @file    main.c
  * @author  g-f
  * @version V1.0
  * @date    2021-12-xx
  * @brief   

  **********************************************************************
  */ 
	
	
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/
#include "sys.h"
#include "delay.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_key.h" 
#include "bsp_gpio.h" 
#include "bsp_GeneralTim.h" 
#include <string.h>
#include <stdlib.h>
#include <math.h>
/******************************* 全局变量 ************************************/
#define  High_frequency   70-1
#define  Mid_frequency    50-1
#define  Low_frequency    30-1
#define  Off_frequency    0


Device_set  device_setting ;

 
/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
/*****************************************************************
  * @brief  void Set_pwm_dutycycle(uint16_t val)
  * @param  val PWM占空比值
  * @retval 无
  * @note   
  ****************************************************************/
	
void Set_pwm_dutycycle(uint16_t val)
{
	TIM_SetCompare4(TIM4,val);	//修改比较值，修改占空比
}

/*****************************************************************
  * @brief  void Set_vibrate(uint8_t num )
  * @param  设置震动次数
  * @retval 无
  * @note   
  ****************************************************************/
void Set_vibrate(uint8_t num ,uint16_t fre)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		Set_pwm_dutycycle(fre);
		delay_ms(500);
		Set_pwm_dutycycle(Off_frequency);
		delay_ms(1000);
	}
}	

/*****************************************************************
  * @brief  void Upload_to_APP(uint8_t att)
  * @param  上传APP的注意力值 
  * @retval 无
  * @note   
  ****************************************************************/
void Upload_to_APP(uint8_t att)
{
	Usart2TX.USART_LEN = 6;
	Usart2TX.TXBuf[0] = 0xaa;
	Usart2TX.TXBuf[1] = 0x01;
	Usart2TX.TXBuf[2] = 0x00;
	Usart2TX.TXBuf[3] = 0x01;
	Usart2TX.TXBuf[4] = att;
	Usart2TX.TXBuf[5] = 0xFF;
	Usart2TX.TX_cnt=0;
	USART_SendData(BLE_USARTx,Usart2TX.TXBuf[Usart2TX.TX_cnt++]);
	USART_ITConfig(BLE_USARTx,USART_IT_TXE,ENABLE);
}

/*****************************************************************
  * @brief  移植的函数
  * @param  
  * @retval 无
  * @note   
  ****************************************************************/

#define K_num 9

uint8_t single_NOT_zero =0;
uint16_t result;
uint16_t vibration_result = 0;
uint16_t k = 0;
uint8_t attention_buffer[5] = {0}; // Sum of 5 attention values
float average5_attention = 0; // Average of 5 attention values
uint16_t attention_loop = 0;	
uint16_t attention_loop_num = 5 ;
uint16_t AllResult[5000] = {0};
uint16_t allresult_count = 0;

//uint8_t  checksum = 0;
uint16_t Test_scope = 800;                //******可调变量
float Threshold = 0.7;                //******可调变量

//需要读取的信息变量
uint8_t signalquality = 0;
uint8_t attention = 0;   
uint8_t meditation = 0; 


void Sort(float Distance[][2], uint16_t rowNum) 
{
	uint16_t i ,j;
  for (i = 0; i < rowNum; i++)
  {
    for ( j = 0; j < rowNum - 1 - i; j++)
    {
      float t1;
      float t2;
      if (Distance[j][0] > Distance[j + 1][0])
      {
        t1 = Distance[j][0];
        Distance[j][0] = Distance[j + 1][0];
        Distance[j + 1][0] = t1;

        t2 = Distance[j][1];
        Distance[j][1] = Distance[j + 1][1];
        Distance[j + 1][1] = t2;
      }
    }
  }
}

uint16_t KNN(float testData, uint16_t K) 
{
  float trainData[30] = {48.8928571428571, 50.7407407407407, 43.8928571428571, 52.2592592592593, 56.4814814814815,
                          45.1818181818182, 44.8636363636364, 44.1818181818182, 53.1739130434783, 53.3043478260870,
                          53.043478260869560, 50.727272727272730, 71.454545454545450, 39.857142857142854, 41.142857142857146,
                          38.130434782608695, 37.681818181818180, 40.363636363636370, 49.272727272727270, 38.272727272727270,
                          30.772727272727270, 33.750000000000000, 35.909090909090910, 44.045454545454550, 43.636363636363630,
                          28.629629629629630, 40.321428571428570, 32.107142857142854, 28.285714285714285, 33.607142857142854
                         };


  uint16_t rowNum = (sizeof(trainData) / sizeof(uint16_t));
	uint16_t i;			
												 
	/*数组大小待解决需要和traindata同步修改*/
  uint16_t Label_Emotion[60] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; //==============Need to be changed with trainData================//
  float Dist[30][2];
  uint16_t KClass[K_num] = {0};
  uint16_t countClass1 = 0;
  uint16_t countClass2 = 0;
  uint16_t result;


  float sum = 0.0;
  for ( i = 0; i < rowNum; i++) 
	{
    sum = sum + (trainData[i] - testData) * (trainData[i] - testData);
    //      sum += (trainData[i][j] - testData[j])*(trainData[i][j] - testData[j]);
    Dist[i][0] = sqrt(sum);
    Dist[i][1] = Label_Emotion[i];
    sum = 0;
  }

  Sort(Dist, rowNum);

  for ( i = 0; i < K; i++) 
	{
    KClass[i] = Dist[i][1];
    if (KClass[i] == 1) 
		{
      countClass1++;
    } 
		else 
		{
      countClass2++;
    }
  }

  if (countClass1 == countClass2) 
	{
    result = KClass[0];
  } 
	else if (countClass1 > countClass2) 
	{
    result = 1;
  } 
	else
	{
    result = 2;
  }

  return result;
}



/*****************************************************************
  * @brief  void read_serial_data()
  * @param  //读取串口数据
  * @retval 无
  * @note   
  ****************************************************************/

void read_serial_data()
{
	uint16_t i;
	uint8_t  checksum = 0;
	uint16_t   generatedChecksum = 0;
	//接收数据长度和数据数组
	uint8_t  payloadLength = 0;
	uint8_t  payloadData[32] = {0};//总共接收32个自己的数据


	if(Uart1RX.rec_finish == 1)
	{
		Uart1RX.rec_finish = 0;
		if(Uart1RX.RXBuf[0] == 0xAA)
		{
			if(Uart1RX.RXBuf[1] == 0xAA)
			{
				payloadLength = Uart1RX.RXBuf[2];//读取第三个，数据包字节的长度
				if (payloadLength == 0x20) //如果接收到的是大包数据才继续读取，小包数据则舍弃不读取
				{
					generatedChecksum = 0; //校验变量清0
					for ( i = 0; i < payloadLength; i++) //连续读取32个字节
					{
						payloadData[i] = Uart1RX.RXBuf[i+3];//读取指定长度数据包中的数据
						generatedChecksum += payloadData[i];//计算数据累加和
					}
					checksum = Uart1RX.RXBuf[payloadLength+3];//读取校验字节
					//校验
					generatedChecksum = (~generatedChecksum) & 0xff;
					//比较校验字节
					if (checksum == generatedChecksum) //数据接收正确，继续处理
					{
						
						signalquality = 0;
						attention = 0;   
						//赋值数据
						signalquality = payloadData[1];
						if(signalquality != 0)
						{
							single_NOT_zero++;
							if(single_NOT_zero>=10)
							{
								Led_station = Led_twinkle ;
								time =0 ;
								
							}
						}
						else
						{
							Led_station = Led_pwrON;
							time =0 ;
						}
						attention = payloadData[29];
						Upload_to_APP(attention); // 上传 attention 值
						meditation = payloadData[31];
						
						attention_buffer[attention_loop] = attention;                                    
            attention_loop = attention_loop + 1;
						if (attention_loop == attention_loop_num)
						{
							average5_attention = (attention_buffer[0] + attention_buffer[1] + attention_buffer[2] + attention_buffer[3] + attention_buffer[4]) / 5;
							printf("Average attention value is:%f ",average5_attention);
//						printf(average5_attention, DEC);
							printf("\n");
							memset(attention_buffer, 0, sizeof(attention_buffer));
							attention_loop = 0;
							result = KNN(average5_attention, K_num);
							AllResult[allresult_count] = result;
							printf("KNN:%d ",result);
//							Serial.print(result);
							printf("\n");
							allresult_count = allresult_count + 1;
						}
						
						if (allresult_count == Test_scope) 
						{
							uint16_t result_length = (sizeof(AllResult) / sizeof(uint16_t));

							for ( i = 0; i < result_length; i++)
							{
								if (AllResult[i] == 2) 
								{
									k = k + 1;
								}
								if (k >= floor(Test_scope*Threshold)) 
								{
									vibration_result = 2;
								}
								else 
								{
									vibration_result = 1;
								}
							}
							printf("vibration_result: %d",vibration_result);
//							printf(vibration_result);
							printf("\n");
							allresult_count = 0;
							k = 0;
							vibration_result = 0;
							memset(AllResult, 0, sizeof(AllResult));
						}
					}
				}
			}
		}			
	}
}

/*****************************************************************
  * @brief  void ble_cmd()
  * @param  //读取蓝牙数据
  * @retval 无
  * @note   
  ****************************************************************/
void ble_cmd(void)
{
//	uint8_t check_sum =0;
	if(Uart2RX.rec_finish == 1)
		{
			Uart2RX.rec_finish= 0;
			if((Uart2RX.RXBuf[0] == 0xaa) && (Uart2RX.RXBuf[1] == 0x00) )
			{
//				check_sum = crc_check(Uart2RX.RXBuf,Uart2RX.receive_len-1);
				if(0XFF == Uart2RX.RXBuf[Uart2RX.receive_len-1])
				{
					switch(Uart2RX.RXBuf[2] )
					{		
						case 0x01 : 
											Test_scope = (Uart2RX.RXBuf[Uart2RX.receive_len-3]<<8) + Uart2RX.RXBuf[Uart2RX.receive_len-2];
											printf("Test_scrope = %d",Test_scope);
											break;
						case 0x02 : 
											if(Uart2RX.RXBuf[Uart2RX.receive_len-2] < 10)
											{
												Threshold = Uart2RX.RXBuf[Uart2RX.receive_len-2] * 0.1 + Uart2RX.RXBuf[Uart2RX.receive_len-4];
											}
											else if(Uart2RX.RXBuf[Uart2RX.receive_len-2] >= 10 && Uart2RX.RXBuf[Uart2RX.receive_len-2] < 100)
											{
												Threshold = Uart2RX.RXBuf[Uart2RX.receive_len-2] * 0.01 + Uart2RX.RXBuf[Uart2RX.receive_len-4];
											}
											else if(Uart2RX.RXBuf[Uart2RX.receive_len-2] >= 100 )
											{
												Threshold = Uart2RX.RXBuf[Uart2RX.receive_len-2] * 0.001 + Uart2RX.RXBuf[Uart2RX.receive_len-4];
											}
											printf("Threshold = %f",Threshold);
											break;
						case 0x03 : 
											Set_pwm_dutycycle(Low_frequency);
											//Set_vibrate(2,Low_frequency);
											break;
						case 0x04 :	  
											Set_pwm_dutycycle(Mid_frequency);
											//Set_vibrate(2,Mid_frequency);
											break;
						case 0x05:
											Set_pwm_dutycycle(High_frequency);
											//Set_vibrate(2,High_frequency);
											break;
						case 0x07: 
											attention_loop_num = (Uart2RX.RXBuf[Uart2RX.receive_len-3]<<8) + Uart2RX.RXBuf[Uart2RX.receive_len-2];
											break;
									
					}
				}
			}
		}
}	

/*****************************************************************
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   
  ****************************************************************/
	
 int main(void)
 {	
	
	 
	delay_init();	    //延时函数初始化	  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	/* LED 初始化 */
	LED_Init();	
	 
	/*I/O口初始化*/
	GPIO_Config();
	 
	/*按键初始化*/
	Key_GPIO_Config();
	 
	/* 串口初始化	*/
	USART1_Config();
	USART2_Config();
	USART3_Config();
	 
	/*定时器初始化*/
	GENERAL_TIM_Init();
	 
	// EXTIX_Init();
	/*开机按键检测*/
	while(!device_setting.power_flag)
	{
		if(GPIO_ReadInputDataBit(PWR_SW_GPIO_PORT,PWR_SW_GPIO_PIN) == KEY_OFF)
			{
				if(key_pwr.Count < KEY_FILTER_TIME)
				{
					key_pwr.Count =  KEY_FILTER_TIME;
				}
				else if(key_pwr.Count < 2 * KEY_FILTER_TIME)
				{
					key_pwr.Count ++;
				}
				else
				{
					if(key_pwr.State == 0)
						key_pwr.State =1;
				}
				if(key_pwr.LongTime > 0)
				{
					if(key_pwr.LongCount < key_pwr.LongTime)
						key_pwr.LongCount++;
					else
					{
						
						if(device_setting.power_flag == 0)
						{
							
							POWER_CTL(1);  //开机
							key_pwr.Count = 0 ;
							key_pwr.State = 0 ;
							key_pwr.LongCount = 0;
							Led_station = Led_pwrON ;
							time =0 ;
							time_1s =0 ;
							break;
							//xEventGroupSetBits(LED_Event_Handle,GREEN_LIGHT);
						}
					}
				}
			}

			delay_ms(20);
	}
//	POWER_CTL(1);  //开机
//	LED_STATUS_ON;
	//device_setting.power_flag = 1;
	Set_pwm_dutycycle(0);
	while(1)
	{
		//Key_Scan();
		ble_cmd();
		read_serial_data();
		delay_ms(100);
	}
 }




