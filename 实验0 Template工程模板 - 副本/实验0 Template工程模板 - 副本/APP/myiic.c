#include "myiic.h"
#include "delay.h"
#include "sys.h"


//��ʼ��LDC1314_IIC
void LDC1314_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE ); 
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
 
    LDC1314_IIC_SCL=1;
    LDC1314_IIC_SDA=1;

}
//����LDC1314_IIC��ʼ�ź�
void LDC1314_IIC_Start(void)
{
    LDC1314_SDA_OUT();     //sda�����
    LDC1314_IIC_SDA=1;        
    LDC1314_IIC_SCL=1;
    delay_us(4);
    LDC1314_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
    delay_us(4);
    LDC1314_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}     
//����LDC1314_IICֹͣ�ź�
void LDC1314_IIC_Stop(void)
{
    LDC1314_SDA_OUT();//sda�����
    LDC1314_IIC_SCL=0;
    LDC1314_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    delay_us(4);
    LDC1314_IIC_SCL=1; 
    LDC1314_IIC_SDA=1;//����I2C���߽����ź�
    delay_us(4);                                
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 LDC1314_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    LDC1314_SDA_IN();      //SDA����Ϊ����  
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
    LDC1314_IIC_SCL=0;//ʱ�����0   
    return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��         
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
//LDC1314_IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��           
void LDC1314_IIC_Send_Byte(u8 txd)
{
    u8 t;   
    LDC1314_SDA_OUT();      
    LDC1314_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
        LDC1314_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;       //txd����һλ
        delay_us(2);   //��TEA5767��������ʱ���Ǳ����
        LDC1314_IIC_SCL=1;
        delay_us(2); 
        LDC1314_IIC_SCL=0;  
        delay_us(2);
    }
}       
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 LDC1314_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    LDC1314_SDA_IN();//SDA����Ϊ����
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
        LDC1314_IIC_NAck();//����nACK
    else
        LDC1314_IIC_Ack(); //����ACK   
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
























