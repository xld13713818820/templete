/*********************************************************************
	
	** @file    key.c
	** @date    2018/8/8
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------包含的头文件----------------------------*/

#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

/*********************************************************************

	** @func   按键初始化函数
	** @param  None
	** @retval None
	** @brief  None
	
*********************************************************************/	

void vKEY_Init(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;		  // KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   // 设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				  // 初始化GPIOE4
                                                     	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;      // KEY2 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   // PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  // 初始化GPIOA.0
                                                  
}

/*********************************************************************

	** @func   按键处理函数
	** @param  None
	** @retval 0:没有任何按键按下  2:KEY2按下  3:KEY2按下
	** @brief  mode:0,不支持连续按;1,支持连续按;
	
*********************************************************************/

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up && (KEY2==1 || KEY3==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY2==1)			return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
	}
	else if(KEY2==0&&KEY3==1)key_up=1; 	    
 	return 0;			// 无按键按下
}
