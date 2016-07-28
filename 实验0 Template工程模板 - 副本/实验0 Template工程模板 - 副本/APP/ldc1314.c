#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "IIC.h"
#include "ldc1314.h"
#include "LDC1314_cmd.h"


void ldc1314_write(uint8 addr1,uint8 addr2,uint16 data)
{
	IIC_Start();
	IIC_Send_Byte(addr1);
	IIC_Wait_Ack();
	IIC_Send_Byte(addr2);
	data_H=(data>>)&0x
}