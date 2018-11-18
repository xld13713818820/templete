
/*********************************************************************
	
	** @file    led.c
	** @date    2018/8/8
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------������ͷ�ļ�----------------------------*/

#include "led.h"

/*********************************************************************

	** @func   LED IO��ʼ�� 	
	** @param  None
	** @retval None
	** @brief  ��ʼ��PE5��PE6Ϊ�����.��ʹ���������ڵ�ʱ��
	
*********************************************************************/
	 
void vLED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	   	// ʹ��PE�˿�ʱ��
	                                                             
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;				// LED1-->PE5,LED0-->PE6 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					// �������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					// IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 						// �����趨������ʼ��GPIOE5,GPIOE6
 GPIO_SetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_6);									// PE.5,PE.6�����

}
 
