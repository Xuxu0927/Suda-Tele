#ifndef __IIC_H_
#define __IIC_H_

#include "lcd.h"


#define	Slave_Address   0x1a	 //����������IIC�����еĴӵ�ַ  read
                	
sbit	SCL=P3^0;      //IICʱ����
sbit	SDA=P3^1;      //IIC������

void HMC5883_Start();
void HMC5883_Stop();
void HMC5883_SendACK(bit ack);
bit HMC5883_RecvACK();
void HMC5883_SendByte(u8 dat);
u8 HMC5883_RecvByte();
void Single_Write_HMC5883(u8 REG_Address,u8 REG_data);
void Multiple_Read_HMC5883(void);
void Init_HMC5883();














#endif

















