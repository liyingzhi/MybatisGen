#include "myiic.h"
#include "delay.h"
#include "ldc.h"
#include "sys.h"




void LDC_Init()
{

	LDC1314_IIC_Init();

}

void Write_ldc_address(u8 address ,u16 Date)
{
    u8 eight_h, eight_l;
	  eight_h = (u8)(Date>>8);
    eight_l = (u8)(Date&0xff);
    
    LDC1314_IIC_Start();

    /* Send EEPROM address for write */
    LDC1314_IIC_Send_Byte(0X54);
  
    /* Test on EV6 and clear it */
    LDC1314_IIC_Wait_Ack();
		
      
    /* Send Address (on 2 bytes) of first byte to be written & wait event detection */
    LDC1314_IIC_Send_Byte(address);                        //发送寄存器地址
    /* Test on EV8 and clear it */
    LDC1314_IIC_Wait_Ack();

    LDC1314_IIC_Send_Byte(eight_h);                        //发送高八位数据
    /* Test on EV8 and clear it */
    LDC1314_IIC_Wait_Ack();
 
    /* Send the byte to be written */
    LDC1314_IIC_Send_Byte(eight_l);                        //发送低八位数据
   
    /* Test on EV8 and clear it */
    LDC1314_IIC_Wait_Ack(); 
  
    /* Send STOP condition */
    LDC1314_IIC_Stop();

    delay_ms(10);
}



u16 Read_ldc_address(u8 ldc_add)
{
    u16 data_h, data_l;
    u16 ldc_data;
    
    /* Send STRAT condition */
    LDC1314_IIC_Start(); 

    /* Send EEPROM address for write */
    LDC1314_IIC_Send_Byte(0X54);  //发送芯片地址
  
    /* Test on EV6 and clear it */
    LDC1314_IIC_Wait_Ack();
      
    /* Send Address (on 2 bytes) of first byte to be written & wait event detection */
    LDC1314_IIC_Send_Byte(ldc_add);                        //发送寄存器地址
    /* Test on EV8 and clear it */
    LDC1314_IIC_Wait_Ack();
    

    
    LDC1314_IIC_Start(); 

    /* Send EEPROM address for write */
    LDC1314_IIC_Send_Byte(0X55);  //发送芯片地址

    /* Test on EV8 and clear it */
    LDC1314_IIC_Wait_Ack(); 
 
    /* Send the byte to be written */
    data_h = LDC1314_IIC_Read_Byte(1);

    data_l = LDC1314_IIC_Read_Byte(1);  
    
    /* Send STOP condition */
    LDC1314_IIC_Stop();//
    
    ldc_data=(data_h<<8)+data_l;
    
    return ldc_data; 
}


void Config_LDC()
{
	
    Write_ldc_address(0x1C ,0x8600);// CMD Reset Device 8C00
    delay_ms(100);
    
    Write_ldc_address(0x08 ,0x0400);// CH0 COUNT 0400//Y
		
    Write_ldc_address(0x09 ,0x0400);// CH1 COUNT 0400//Y
    Write_ldc_address(0x0A ,0XFFFF);// CH2 COUNT  LDC1314 Only//N
    Write_ldc_address(0x0B ,0xFFFF);// CH3 COUNT  LDC1314 Only//N
    
    Write_ldc_address(0x0C ,0x0000);// CH0 OffSet //N
		
    Write_ldc_address(0x0D ,0x0000);// CH1 OffSet //N
    Write_ldc_address(0x0E ,0x0000);// CH2 OffSet LDC1314 Only //N
    Write_ldc_address(0x0F ,0x0000);// CH3 OffSet LDC1314 Only //N
			
		
    Write_ldc_address(0x10 ,0x0008);// CH0 Settle   //0400 //N
    Write_ldc_address(0x11 ,0x0008);// CH1 Settle   //0400 //N
    Write_ldc_address(0x12 ,0x0400);// CH2 Settle LDC1314 Only //Y
    Write_ldc_address(0x13 ,0x0400);// CH3 Settle LDC1314 Only //Y
    
    Write_ldc_address(0x14 ,0x0008);// CH0 Clock Devide //0x0008 //N
    Write_ldc_address(0x15 ,0x0008);// CH1 Clock Devide //0x0008 //N
    Write_ldc_address(0x16 ,0x0000);// CH2 Clock Devide LDC1314 Only //N
    Write_ldc_address(0x17 ,0x0000);// CH3 Clock Devide LDC1314 Only //N
    
    Write_ldc_address(0x18 ,0x0008);// Status  0001 //N
    Write_ldc_address(0x1A ,0x0200);// CLK Pin//Y
    
    Write_ldc_address(0x19 ,0x0000);//ERROR
    
    //Write_ldc_address(0x1B ,0x02FF);// LDC1312 & LDC1612 Seq Config // 820F 02ff
		Write_ldc_address(0x1B ,0xC20F);// LDC1314 & LDC1614 Seq Config //N
    
    Write_ldc_address(0x1D ,0x0200);// LDC Clock Config//Y
    
    Write_ldc_address(0x1E ,0xF000);// CH0 Driver Current //9500
    Write_ldc_address(0x1F ,0xF000);// CH1 Driver Current //9500
    Write_ldc_address(0x20 ,0x0000);// CH2 Driver Current
    Write_ldc_address(0x21 ,0x0000);// CH3 Driver Current
		//Read_ldc_address(0x0D);
}
