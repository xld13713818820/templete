
/*********************************************************************
	
	** @file    main.c
	** @date    2018/8/11
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------包含的头文件----------------------------*/

#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"

/*********************************************************************

	** @func   main.c
	** @param  None
	** @retval None
	** @brief  None
	
*********************************************************************/

 int main(void)
 {
	 u16 i=0;
			
	 delay_init();	    			// 延时函数初始化	  
	 vLED_Init();		  	 			// 初始化与LED连接的硬件接口
	 vKEY_Init();				 			// 按键初始化
	 vUART_Init();						// 串口初始化	
			
	 LED0 = 0;
	 LED1 = 1;
  while(1)
	{
		u8 key;
		key = KEY_Scan(0);
	
		if(key==KEY2_PRES)				// KEY2按下,写入W25QXX
		{
			
			break;
		}                                                              
		else if(key==KEY3_PRES)		// KEY3按下,读取字符串并显示                
		{                                                              
			break;
		}
		i++;
		delay_ms(10);
		if (50 == i)
		{
			LED0=!LED0;							// 提示系统正在运行	
			LED1=!LED1;
			DBG_vPrintf("CPU running...\n");
			i = 0;
		}
	}
}
