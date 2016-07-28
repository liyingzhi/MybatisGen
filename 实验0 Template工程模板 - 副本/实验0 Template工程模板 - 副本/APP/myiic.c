#include "myiic.h"
#include "delay.h"
#include "sys.h"


//初始化LDC1314_IIC
void LDC1314_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//先使能外设IO PORTC时钟 
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE ); 
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
 
    LDC1314_IIC_SCL=1;
    LDC1314_IIC_SDA=1;

}
//产生LDC1314_IIC起始信号
void LDC1314_IIC_Start(void)
{
    LDC1314_SDA_OUT();     //sda线输出
    LDC1314_IIC_SDA=1;        
    LDC1314_IIC_SCL=1;
    delay_us(4);
    LDC1314_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
    delay_us(4);
    LDC1314_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}     
//产生LDC1314_IIC停止信号
void LDC1314_IIC_Stop(void)
{
    LDC1314_SDA_OUT();//sda线输出
    LDC1314_IIC_SCL=0;
    LDC1314_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    delay_us(4);
    LDC1314_IIC_SCL=1; 
    LDC1314_IIC_SDA=1;//发送I2C总线结束信号
    delay_us(4);                                
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 LDC1314_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    LDC1314_SDA_IN();      //SDA设置为输入  
    LDC1314_IIC_SDA=1;delay_us(1);     
    LDC1314_IIC_SCL=1;delay_us(1);   
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            LDC1314_IIC_Stop();
            return 1;
						
					
        }
    }
    LDC1314_IIC_SCL=0;//时钟输出0   
    return 0;  
} 
//产生ACK应答
void LDC1314_IIC_Ack(void)
{
    LDC1314_IIC_SCL=0;
    LDC1314_SDA_OUT();
    LDC1314_IIC_SDA=0;
    delay_us(2);
    LDC1314_IIC_SCL=1;
    delay_us(2);
    LDC1314_IIC_SCL=0;
}
//不产生ACK应答         
void LDC1314_IIC_NAck(void)
{
    LDC1314_IIC_SCL=0;
    LDC1314_SDA_OUT();
    LDC1314_IIC_SDA=1;
    delay_us(2);
    LDC1314_IIC_SCL=1;
    delay_us(2);
    LDC1314_IIC_SCL=0;
}                                        
//LDC1314_IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答           
void LDC1314_IIC_Send_Byte(u8 txd)
{
    u8 t;   
    LDC1314_SDA_OUT();      
    LDC1314_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
        LDC1314_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;       //txd左移一位
        delay_us(2);   //对TEA5767这三个延时都是必须的
        LDC1314_IIC_SCL=1;
        delay_us(2); 
        LDC1314_IIC_SCL=0;  
        delay_us(2);
    }
}       
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 LDC1314_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    LDC1314_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        LDC1314_IIC_SCL=0; 
        delay_us(2);
        LDC1314_IIC_SCL=1;
			  delay_us(2); 
        receive<<=1;
        if(READ_SDA)receive++;
    }                    
    if (!ack)
        LDC1314_IIC_NAck();//发送nACK
    else
        LDC1314_IIC_Ack(); //发送ACK   
    return receive;
}



u16 ReadData_ID(void)
{
			u16 data_rece;
	    u8 i,j;
			LDC1314_IIC_Send_Byte(0x55); 
			delay_us(20);
	    i=LDC1314_IIC_Read_Byte(0);
			///ReadBuffer[0] = TWI_ReceiveByte(); 
			LDC1314_IIC_Ack();
			j = LDC1314_IIC_Read_Byte(1);
			LDC1314_IIC_Ack();
			LDC1314_IIC_Stop();
      data_rece=j*256+i;
   return data_rece;
}
























