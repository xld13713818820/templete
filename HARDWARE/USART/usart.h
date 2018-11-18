
/*********************************************************************
	
	** @file    uasrt.h
	** @date    2018/8/9
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*--------------------------�����ֹ�ݹ����--------------------------*/

#ifndef __USART_H
#define __USART_H

/*----------------------------������ͷ�ļ�----------------------------*/

#include "sys.h" 

/*----------------------------������궨��----------------------------*/

#define USART_REC_LEN  			200  	// �����������ֽ��� 200

#define USART1_MAX_RECV_LEN   600   //���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
#define USART1_MAX_SEND_LEN		600

#define	UART1_EN	1     					// ����1 TX = PA9   RX = PA10
#define	UART2_EN	1     					// ����2 TX = PA2   RX = PA3 
#define	UART3_EN	0								// ����3 TX = PB10  RX = PB11


/* ���崮�ڲ����ʺ�FIFO��������С����Ϊ���ͻ������ͽ��ջ�����, ֧��ȫ˫�� */
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

/*----------------------------ȫ�ֱ�������----------------------------*/		
			
extern u8  USART_RX_BUF[USART_REC_LEN]; // ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         				// ����״̬���	

/*------------------------------�������� -----------------------------*/
	
void vUART_Init(void);

void u1_printf(char* fmt,...);  
#endif
