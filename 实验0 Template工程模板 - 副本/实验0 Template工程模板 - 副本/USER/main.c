#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ldc.h"
#include "myiic.h"

//

//Modified by Li Yingli 20160728

//
 int main(void)
 {		
 	u16 t[4];
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	LDC1314_IIC_Init();
	Config_LDC();
	while(1)
	{
		t[0]=Read_ldc_address(0x00);
		t[1]=Read_ldc_address(0x02);
		t[2]=Read_ldc_address(0x04);
		t[3]=Read_ldc_address(0x06);
		
//		LDC1314_IIC_Start();
//    LDC1314_IIC_Send_Byte(0x54);
//		LDC1314_IIC_Wait_Ack();
//		LDC1314_IIC_Send_Byte(0x10);
//		LDC1314_IIC_Wait_Ack();
//		LDC1314_IIC_Start();
//    LDC1314_IIC_Send_Byte(0x55);
//    LDC1314_IIC_Wait_Ack();
//		H_data=LDC1314_IIC_Read_Byte(1);
//		L_data=LDC1314_IIC_Read_Byte(0);
//		LDC1314_IIC_Stop();
		printf("%d,%d,%d,%d\n",t[0],t[1],t[2],t[3]);
		delay_ms(500);
	}
 }

