#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

               
//IO��������
#define LDC1314_SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define LDC1314_SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO��������     
#define LDC1314_IIC_SCL    PCout(12) //SCL
#define LDC1314_IIC_SDA    PCout(11) //SDA   
#define READ_SDA   PCin(11)  //����SDA 

//LDC1314_IIC���в�������
void LDC1314_IIC_Init(void);                //��ʼ��LDC1314_IIC��IO��                
void LDC1314_IIC_Start(void);               //����LDC1314_IIC��ʼ�ź�
void LDC1314_IIC_Stop(void);                //����LDC1314_IICֹͣ�ź�
void LDC1314_IIC_Send_Byte(u8 txd);         //LDC1314_IIC����һ���ֽ�
u8 LDC1314_IIC_Read_Byte(unsigned char ack);//LDC1314_IIC��ȡһ���ֽ�
u8 LDC1314_IIC_Wait_Ack(void);              //LDC1314_IIC�ȴ�ACK�ź�
void LDC1314_IIC_Ack(void);                 //LDC1314_IIC����ACK�ź�
void LDC1314_IIC_NAck(void);                //LDC1314_IIC������ACK�ź�
u16 ReadData_ID(void);

void LDC1314_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 LDC1314_IIC_Read_One_Byte(u8 daddr,u8 addr);   
#endif
















