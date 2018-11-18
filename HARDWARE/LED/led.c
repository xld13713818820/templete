
/*********************************************************************
	
	** @file    led.c
	** @date    2018/8/8
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------包含的头文件----------------------------*/

#include "led.h"

/*********************************************************************

	** @func   LED IO初始化 	
	** @param  None
	** @retval None
	** @brief  初始化PE5和PE6为输出口.并使能这两个口的时钟
	
*********************************************************************/
	 
void vLED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	   	// 使能PE端口时钟
	                                                             
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;				// LED1-->PE5,LED0-->PE6 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					// 推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					// IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 						// 根据设定参数初始化GPIOE5,GPIOE6
 GPIO_SetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_6);									// PE.5,PE.6输出高

}
 
