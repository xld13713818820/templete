
/*********************************************************************
	
	** @file    usart.c
	** @date    2018/8/9
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------包含的头文件----------------------------*/

#include "usart.h"

/*----------------------------全局变量定义----------------------------*/

//u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
////接收状态
////bit15，	接收完成标志
////bit14，	接收到0x0d
////bit13~0，	接收到的有效字节数目
//u16 USART_RX_STA=0;       //接收状态标记	  


#if UART1_EN == 1
  uint8_t Usart1RxBuf[UART1_RX_BUF_SIZE];		/* 数据存储区 */
#endif

#if UART2_EN == 1
  uint8_t Usart2RxBuf[UART2_RX_BUF_SIZE];		/* 数据存储区 */
#endif

#if UART3_EN == 1
  uint8_t Usart3RxBuf[UART3_RX_BUF_SIZE];		/* 数据存储区 */
#endif

u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 			// 接收缓冲,最大USART1_MAX_RECV_LEN个字节.
u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 			// 发送缓冲,最大USART1_MAX_SEND_LEN字节
	
	
	
/*********************************************************************

	** @func   串口初始化
	** @param  None
	** @retval None
	** @brief  None
	
*********************************************************************/
	
void vUART_Init(void)
{
	/* GPIO端口设置 */
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
/*********************************USART1配置***********************************/
#if UART1_EN   /* 串口1 TX = PA9   RX = PA10 */
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	
	/* USART1_TX   GPIOA.9初始化 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 								
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;							//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);											
				
 	/* USART1_RX   GPIOA.10初始化 */			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10			
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;				//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure); 			
			
  /* USART1 NVIC 配置 */		
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;		// 抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;					// 子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);															// 根据指定的参数初始化VIC寄存器
			                                                           
  /* USART1 初始化设置 */		                                     
	USART_InitStructure.USART_BaudRate = UART1_BAUD;						// 串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;					// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;// 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式

  USART_Init(USART1, &USART_InitStructure); 								  // 初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);						  // 开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    						  // 使能串口1 
#endif		
	/*
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
		
		CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 
*/

/*********************************USART2配置***********************************/
#if UART2_EN   /* 串口2 TX = PA2， RX = PA3  */

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				// 使能USART2，GPIOA时钟
			
	/* USART2_TX   GPIOA.2初始化 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;							// 复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
			
	/* USART2_RX   GPIOA.3初始化 */		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 			// 浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	
  /* USART2 NVIC 配置 */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			// 抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					// 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);															// 根据指定的参数初始化VIC寄存器


  /* USART2 初始化设置 */
	USART_InitStructure.USART_BaudRate = UART2_BAUD;						// 波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;					// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式
	
	USART_Init(USART2, &USART_InitStructure); 									// 初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);							// 开启串口接收中断
	USART_Cmd(USART2, ENABLE);                    							// 使能串口2 
	//USART_ClearFlag(USART2, USART_FLAG_TC);    								 // 清发送完成标志，Transmission Complete flag */
#endif
/*
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
		
		CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 
*/
	
/*********************************USART3配置***********************************/
#if UART3_EN   /* 串口3 TX = PB10   RX = PB11 */

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	      // 使能USART3，GPIOB时钟
                                                                                                                        
	/* USART3_TX   GPIOB.10初始化 */                            
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			        // 复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);                      
                                                              
                                                              
	/* USART3_RX   GPIOB.11初始化 */                            
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       // 浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);  

  /* USART3 NVIC 配置 */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			// 抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// 子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);															// 根据指定的参数初始化VIC寄存器
	
  /* USART3 初始化设置 */
	USART_InitStructure.USART_BaudRate = UART3_BAUD;						// 波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;					// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;// 无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式
	
	
	USART_Init(USART3, &USART_InitStructure); 									// 初始化串口3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);							// 开启串口接收中断
	USART_Cmd(USART3, ENABLE);                    							// 使能串口3 	
	USART_ClearFlag(USART3, USART_FLAG_TC);    								  // 清发送完成标志，Transmission Complete flag */	

#endif  
/*
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	
		CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题
*/
                                                 
}




/* 加入以下代码,支持printf函数,而不需要选择use MicroLIB */

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
while((USART2->SR&0X40)==0);// 循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
return ch;
}
#endif 


/* 使用微库加入此函数跟重定向 */

//int fputc(int ch, FILE *f)
//{ 
//while((USART2->SR&0X40)==0);//循环发送,直到发送完毕 
// USART2->DR = (u8) ch; 
//return ch;
//}

void u1_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART1_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART1_TX_BUF);		// 此次发送数据的长度
	for(j=0;j<i;j++)												// 循环发送数据
	{
	  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); // 循环发送,直到发送完毕   
		USART_SendData(USART1,USART1_TX_BUF[j]); 
	} 
}








