#include "reg52.h"
#include "intrins.h"

//#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();}    
//#define somenop
// {
// 	unsigned char i;

// 	_nop_();
// 	_nop_();
// 	i = 12;
// 	while (--i);
// }

#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//总线引脚定义
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */

void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}



//总线启动条件
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	Delay5us();
	SDA = 0;
	Delay5us();
	SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	Delay5us();
	SDA = 1;
}

//应答位控制
void IIC_Ack(bit ackbit)
{
	if(ackbit) 
	{	
		SDA = 0;
	}
	else 
	{
		SDA = 1;
	}
	Delay5us();
	SCL = 1;
	Delay5us();
	SCL = 0;
	SDA = 1; 
	Delay5us();
}

//等待应答
bit IIC_WaitAck(void)
{
	SDA = 1;
	Delay5us();
	SCL = 1;
	Delay5us();
	if(SDA)    
	{   
		SCL = 0;
		IIC_Stop();
		return 0;
	}
	else  
	{ 
		SCL = 0;
		return 1;
	}
}

//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{   
		if(byt&0x80) 
		{	
			SDA = 1;
		}
		else 
		{
			SDA = 0;
		}
		Delay5us();
		SCL = 1;
		byt <<= 1;
		Delay5us();
		SCL = 0;
	}
}

//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
	unsigned char da;
	unsigned char i;
	
	for(i=0;i<8;i++)
	{   
		SCL = 1;
		Delay5us();
		da <<= 1;
		if(SDA) 
		da |= 0x01;
		SCL = 0;
		Delay5us();
	}
	return da;
}