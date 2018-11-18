
/*********************************************************************
	
	** @file    main.c
	** @date    2018/8/11
	** @author  adong
	** @brief   None
	
*********************************************************************/

/*----------------------------������ͷ�ļ�----------------------------*/

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
			
	 delay_init();	    			// ��ʱ������ʼ��	  
	 vLED_Init();		  	 			// ��ʼ����LED���ӵ�Ӳ���ӿ�
	 vKEY_Init();				 			// ������ʼ��
	 vUART_Init();						// ���ڳ�ʼ��	
			
	 LED0 = 0;
	 LED1 = 1;
  while(1)
	{
		u8 key;
		key = KEY_Scan(0);
	
		if(key==KEY2_PRES)				// KEY2����,д��W25QXX
		{
			
			break;
		}                                                              
		else if(key==KEY3_PRES)		// KEY3����,��ȡ�ַ�������ʾ                
		{                                                              
			break;
		}
		i++;
		delay_ms(10);
		if (50 == i)
		{
			LED0=!LED0;							// ��ʾϵͳ��������	
			LED1=!LED1;
			DBG_vPrintf("CPU running...\n");
			i = 0;
		}
	}
}
