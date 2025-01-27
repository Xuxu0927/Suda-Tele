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

//�������Ŷ���
sbit SDA = P2^1;  /* ������ */
sbit SCL = P2^0;  /* ʱ���� */

void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}



//������������
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	Delay5us();
	SDA = 0;
	Delay5us();
	SCL = 0;	
}

//����ֹͣ����
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	Delay5us();
	SDA = 1;
}

//Ӧ��λ����
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

//�ȴ�Ӧ��
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

//ͨ��I2C���߷�������
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

//��I2C�����Ͻ�������
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