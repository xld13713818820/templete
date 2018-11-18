
/*********************************************************************
	
	** @file    uasrt.h
	** @date    2018/8/9
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*--------------------------定义防止递归包含--------------------------*/

#ifndef __USART_H
#define __USART_H

/*----------------------------包含的头文件----------------------------*/

#include "sys.h" 

/*----------------------------类型与宏定义----------------------------*/

#define USART_REC_LEN  			200  	// 定义最大接收字节数 200

#define USART1_MAX_RECV_LEN   600   //接收缓冲,最大USART2_MAX_RECV_LEN个字节.
#define USART1_MAX_SEND_LEN		600

#define	UART1_EN	1     					// 串口1 TX = PA9   RX = PA10
#define	UART2_EN	1     					// 串口2 TX = PA2   RX = PA3 
#define	UART3_EN	0								// 串口3 TX = PB10  RX = PB11


/* 定义串口波特率和FIFO缓冲区大小，分为发送缓冲区和接收缓冲区, 支持全双工 */
#if UART1_EN == 1
	#define UART1_BAUD						115200
	#define UART1_TX_BUF_SIZE	1*1
	#define UART1_RX_BUF_SIZE	1*1
#endif

#if UART2_EN == 1
	#define UART2_BAUD			115200
	#define UART2_TX_BUF_SIZE	1*32
	#define UART2_RX_BUF_SIZE	1*1
	
#endif

#if UART3_EN == 1
	#define UART3_BAUD			57600
	#define UART3_TX_BUF_SIZE	1*1
	#define UART3_RX_BUF_SIZE	1*1
#endif

/*----------------------------全局变量定义----------------------------*/		
			
extern u8  USART_RX_BUF[USART_REC_LEN]; // 接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         				// 接收状态标记	

/*------------------------------函数声明 -----------------------------*/
	
void vUART_Init(void);

void u1_printf(char* fmt,...);  
#endif
