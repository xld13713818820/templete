
/*********************************************************************
	
	** @file    key.h
	** @date    2018/8/8
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*--------------------------定义防止递归包含--------------------------*/

#ifndef __KEY_H
#define __KEY_H	 

/*----------------------------包含的头文件----------------------------*/

#include "sys.h"
	 
/*----------------------------类型与宏定义----------------------------*/


#define KEY3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) // 读取KEY3
                                                         
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  // 读取KEY2

#define KEY2_PRES	  2	// KEY2按下
#define KEY3_PRES	  3	// KEY3按下

/*------------------------------函数声明 -----------------------------*/ 

void vKEY_Init(void);

u8 KEY_Scan(u8);  					    
#endif
