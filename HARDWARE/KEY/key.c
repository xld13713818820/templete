/*********************************************************************
	
	** @file    key.c
	** @date    2018/8/8
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------������ͷ�ļ�----------------------------*/

#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/*********************************************************************

	** @func   ������ʼ������
	** @param  None
	** @retval None
	** @brief  None
	
*********************************************************************/	

void vKEY_Init(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;		  // KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   // ���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				  // ��ʼ��GPIOE4
                                                     	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;      // KEY2 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   // PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  // ��ʼ��GPIOA.0
                                                  
}

/*********************************************************************

	** @func   ����������
	** @param  None
	** @retval 0:û���κΰ�������  2:KEY2����  3:KEY2����
	** @brief  mode:0,��֧��������;1,֧��������;
	
*********************************************************************/

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up && (KEY2==1 || KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY2==1)			return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
	}
	else if(KEY2==0&&KEY3==1)key_up=1; 	    
 	return 0;			// �ް�������
}
