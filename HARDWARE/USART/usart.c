
/*********************************************************************
	
	** @file    usart.c
	** @date    2018/8/9
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------������ͷ�ļ�----------------------------*/

#include "usart.h"

/*----------------------------ȫ�ֱ�������----------------------------*/

//u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
////����״̬
////bit15��	������ɱ�־
////bit14��	���յ�0x0d
////bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART_RX_STA=0;       //����״̬���	  


#if UART1_EN == 1
  uint8_t Usart1RxBuf[UART1_RX_BUF_SIZE];		/* ���ݴ洢�� */
#endif

#if UART2_EN == 1
  uint8_t Usart2RxBuf[UART2_RX_BUF_SIZE];		/* ���ݴ洢�� */
#endif

#if UART3_EN == 1
  uint8_t Usart3RxBuf[UART3_RX_BUF_SIZE];		/* ���ݴ洢�� */
#endif

u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 			// ���ջ���,���USART1_MAX_RECV_LEN���ֽ�.
u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 			// ���ͻ���,���USART1_MAX_SEND_LEN�ֽ�
	
	
	
/*********************************************************************

	** @func   ���ڳ�ʼ��
	** @param  None
	** @retval None
	** @brief  None
	
*********************************************************************/
	
void vUART_Init(void)
{
	/* GPIO�˿����� */
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
/*********************************USART1����***********************************/
#if UART1_EN   /* ����1 TX = PA9   RX = PA10 */
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	
	/* USART1_TX   GPIOA.9��ʼ�� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 								
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;							//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);											
				
 	/* USART1_RX   GPIOA.10��ʼ�� */			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10			
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;				//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure); 			
			
  /* USART1 NVIC ���� */		
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;		// ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;					// �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ����ָ���Ĳ�����ʼ��VIC�Ĵ���
			                                                           
  /* USART1 ��ʼ������ */		                                     
	USART_InitStructure.USART_BaudRate = UART1_BAUD;						// ���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;// ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); 								  // ��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);						  // �������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    						  // ʹ�ܴ���1 
#endif		
	/*
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
		
		CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
*/

/*********************************USART2����***********************************/
#if UART2_EN   /* ����2 TX = PA2�� RX = PA3  */

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				// ʹ��USART2��GPIOAʱ��
			
	/* USART2_TX   GPIOA.2��ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;							// �����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
			
	/* USART2_RX   GPIOA.3��ʼ�� */		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 			// ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	
  /* USART2 NVIC ���� */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			// ��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					// �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ����ָ���Ĳ�����ʼ��VIC�Ĵ���


  /* USART2 ��ʼ������ */
	USART_InitStructure.USART_BaudRate = UART2_BAUD;						// ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ
	
	USART_Init(USART2, &USART_InitStructure); 									// ��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);							// �������ڽ����ж�
	USART_Cmd(USART2, ENABLE);                    							// ʹ�ܴ���2 
	//USART_ClearFlag(USART2, USART_FLAG_TC);    								 // �巢����ɱ�־��Transmission Complete flag */
#endif
/*
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
		
		CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
*/
	
/*********************************USART3����***********************************/
#if UART3_EN   /* ����3 TX = PB10   RX = PB11 */

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	      // ʹ��USART3��GPIOBʱ��
                                                                                                                        
	/* USART3_TX   GPIOB.10��ʼ�� */                            
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			        // �����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);                      
                                                              
                                                              
	/* USART3_RX   GPIOB.11��ʼ�� */                            
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       // ��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);  

  /* USART3 NVIC ���� */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			// ��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// �����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
  /* USART3 ��ʼ������ */
	USART_InitStructure.USART_BaudRate = UART3_BAUD;						// ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;// ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ
	
	
	USART_Init(USART3, &USART_InitStructure); 									// ��ʼ������3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);							// �������ڽ����ж�
	USART_Cmd(USART3, ENABLE);                    							// ʹ�ܴ���3 	
	USART_ClearFlag(USART3, USART_FLAG_TC);    								  // �巢����ɱ�־��Transmission Complete flag */	

#endif  
/*
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	
		CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������
*/
                                                 
}




/* �������´���,֧��printf����,������Ҫѡ��use MicroLIB */

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
while((USART2->SR&0X40)==0);// ѭ������,ֱ���������   
    USART2->DR = (u8) ch;      
return ch;
}
#endif 


/* ʹ��΢�����˺������ض��� */

//int fputc(int ch, FILE *f)
//{ 
//while((USART2->SR&0X40)==0);//ѭ������,ֱ��������� 
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
	i=strlen((const char*)USART1_TX_BUF);		// �˴η������ݵĳ���
	for(j=0;j<i;j++)												// ѭ����������
	{
	  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); // ѭ������,ֱ���������   
		USART_SendData(USART1,USART1_TX_BUF[j]); 
	} 
}








