#include "STC15F2K60S2.h"
#include "intrins.h"
#include "onewire.h"
#include "iic.h"    //I2C���������� 

code unsigned char seg7code[10]={ 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //��ʾ���� ������ָ�
unsigned char wei[4]={0XEf,0XDf,0XBf,0X7f};  //λ�Ŀ��ƶ�								 //λ������
code unsigned char tab[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff };
unsigned char dspbuf[8] = {10,10,10,10,10,0,0,0};  //��ʾ������
unsigned char dspcom = 0;
unsigned char ad_value, intr;
bit flag_100;


sbit CLK = P3^7;  //ʱ������  
sbit SE = P1^2;   // LCDʹ�ܶ˿�
sbit RW = P2^1;   // LCD��д�˿�
sbit RS = P2^0;   // LCDд���ݻ�д����˿�
sbit DQ = P1^4;   // ����P1^4��ΪDS18B20�����ݿ�
sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;
sbit LED = P0^0;	 //���嵥Ƭ��P1�ڵĵ�1λ ����P1.0��Ϊָʾ��
sbit DOUT = P2^0;	 //���嵥Ƭ��P2�ڵĵ�1λ ����P2.0��Ϊ�������������,


unsigned int Temp;
unsigned int ND;
unsigned char du1[16];
unsigned char display[16];
unsigned char date[8];
unsigned char max1 = 30;
unsigned char max2 = 30;
unsigned char disflag = 0;
unsigned char tempflag = 0;



void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} 
	while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}


void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


void delay()//�����ʱ����
{
unsigned char m,n,s;
for(m=20;m>0;m--)
for(n=20;n>0;n--)
for(s=248;s>0;s--);
}
void LCD_COM(unsigned char dat)    //LCDд����
{
	 Delay5ms();
	 RW = 0; //0д���� 1������
	 RS = 0; //0д���� 1������
	 
	 SE = 1;
	 P0 = dat;  //LCD���ݶ˿�

	 SE = 0;    //���������½��ش�������
}

void LCD_write(unsigned char dat)   //LCDд����
{
	 Delay5ms();
	 RW = 0;  //0д���� 1������
	 RS = 1;   //0д���� 1д����
	 
	 SE = 1;
	 P0 = dat;   //LCD���ݶ˿�
	 
	 SE = 0;      //���������½��ش�������
}

void LCD_init() //LCD��ʼ��
{

	 LCD_COM(0x38); //��0x38��5*7����0x3c��5*10����8λ���ߣ���ʾ���У��޹�꣬5*7����
	 LCD_COM(0x01); //����
	 LCD_COM(0x06); //��0x06дһ�������ƣ�0x04������ƣ�0x07��Ļ�����ҹ����ƣ������ƣ���ʾ��������
	 LCD_COM(0x0c); //��0x0e��ʾ��겻��˸��0x0f�������˸��B2λ��ʾ�����޹�꣬����˸
}
void timer0( ) interrupt 1 //��ʱ��0������ʽ1
{

TH0=(65536-2)/256;	  //��װ������ֵ
TL0=(65536-2)%256;	  //��װ������ֵ
CLK=!CLK;			  //ȡ��
}

void isr_timer_0(void)  interrupt 1  //Ĭ���ж����ȼ� 1
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  //��ʱ������ 
	  if(++intr==50)
		{
			flag_100=1;
			intr=0;
		}
}
unsigned int ReadTemp(void)    //DS18B20��ȡ�¶�
{
     unsigned char TH,TL;
	unsigned int temp;
	unsigned int tt;
	 
	 init_ds18b20();   //��ʼ��
	 Write_DS18B20(0xcc); //����ѡ��ROM
	 Write_DS18B20(0x44); //����ת������
	
	 init_ds18b20();   //�ٴγ�ʼ��
	 Write_DS18B20(0xcc);
	 Write_DS18B20(0xbe);  //��ȡ��������
	
	 TL = Read_DS18B20();
	 TH = Read_DS18B20();
	
   	temp = ((TH << 8) | TL); //��ȷ��С��
	tt = temp * 10 * 0.0625 + 0.05; //��ȷ��С����һλ
	
	 return tt;
}

void init_pcf8591(unsigned char channel)
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(channel);  //ADCͨ��3
	IIC_WaitAck();
	IIC_Stop();
	Delay10us();
}

unsigned char read_pcf8591(void)
{
	unsigned char ND;

	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	ND = IIC_RecByte();
	IIC_Ack(0);     //���ͷ�Ӧ���ź� 
	IIC_Stop();
	
	return ND;
}
void display1() //LCD��һ����ʾ
{
	unsigned char test1,test2;
	Temp = ReadTemp();
	while (Temp != ReadTemp())
	Temp = ReadTemp();
	ND = read_pcf8591();
	while (ND != read_pcf8591())
	ND = read_pcf8591();
	if(disflag==0)
	{
		du1[0] = 'T';
		du1[1] =' ';
	  du1[2] = Temp / 100 % 10 + 0x30; //��0x30��ԭ����������LCD������ʾҪת�����ַ�����AIISC��;
	  du1[3] = Temp / 10 % 10 + 0x30;
	  du1[4] = '.';
		du1[5] = Temp % 10 + 0x30;
		du1[6] = 0xdf;
		du1[7] = 'C';
	  du1[8] = ' ';
		du1[9] = 'N';
		du1[10] =' ';
	 	du1[11] = ND / 100 % 10 + 0x30;
		du1[12] = ND / 10 % 10 + 0x30;
		du1[13] ='.';
		du1[14] =ND % 10 + 0x30;
		du1[15] =' ';
	
	}
	if(disflag==1)
	{
	 	du1[0] = ' ';
	  	du1[1] = ' ';
	  	du1[2] = ' ';
	  	du1[3] = ' ';
	  	du1[4] = ' ';
		du1[5] = ' ';
		du1[6] = ' ';
	  	du1[7] = ' ';
		du1[8] = ' ';
	 	du1[9] = ' ';
		du1[10] =' ';
		du1[11] =' ';
		du1[12] =' ';
		du1[13] =' ';
		du1[14] =' ';
		du1[15] =' ';
	}	

	test1 = Temp / 100 % 10 * 10 + Temp / 10 % 10;
	test2 = ND / 100 % 10 * 10 + ND / 10 % 10;
	if (test1 >= max1||test2 >= max2)
	{
		P06 = 1;
		P04 = 1;
		P2 = ((P2 & 0x1f) | 0xA0);
		P2 &= 0x1f;
		P0=0x00;
		P2 = ((P2 & 0x1f) | 0x80);
		P2 &= 0x1f;
		
	}
	else 
	{
		P06 = 0;
		P04 = 0;
		P2 = ((P2 & 0x1f) | 0xA0);
		P2 &= 0x1f;
	}	
}

void display2() //LCD�ڶ�����ʾ
{
	if(disflag==0)
	{
		display[0] = 'T';
		display[1] = 'M';
		display[2] = 'A';
		display[3] = 'X';
		display[4] = ' '; 
		display[5] = max1 / 10 + 0x30;
		display[6] = max1 % 10 + 0x30;
		display[7] = ' ';
		display[8] = 'N';
		display[9] = 'M';
		display[10] = 'A';
		display[11] = 'X';
		display[12] = ' ';
		display[13] = max2/ 10 + 0x30;
		display[14] = max2 % 10 + 0x30;
		display[15] = ' '; 
	}
}

void key_scan()
{		
	if(S7 == 0)
	{
		Delay10ms();
	    if(S7 == 0)
			{			  
				disflag++;
				if(disflag==2)
				disflag=0;
			}
			while(S7 == 0);
  	}

	if(S6 == 0)
	{
		Delay10ms();
	    if(S6 == 0)
			{			  
				tempflag++;
				if(tempflag==2)
				tempflag=0;
			}
			while(S7 == 0);
  	}

	if(S4 == 0)
	{
		Delay10ms();
    	if(S4 == 0)
		{
			if(tempflag==1)		  
			{
				max2--;
			}
			if(tempflag==0)		  
			{			  
				max1--;
				if(max1 == 255)
				max1 = 0;
			}
		}
		while(S4 == 0);
  	}
	if(S5 == 0)
	{
		Delay10ms();
    	if(S5 == 0)
		{
			if(tempflag==1)			  
			{
				max2++;
				if(max1 == 99)
				max2 = 99;
			}
			if(tempflag==0)			  
			{			  
				max1++;
	
			}
		
		while(S5 == 0);
  	}		
}
	}

void main()
{
	  unsigned char reset_cnt=0;  //���������洢 (���洢ֵ255)
	unsigned char i,j;
		P2=0xa0;P0=0x00;P2=0x00;
		P2=0x80;P0=0xff;P2=0x00;
		P2=0xe0;P0=0xff;P2=0x00;
		LCD_init();
	
		TMOD=0X01;			  //��ʱ���ж�0
		CLK=0;				  //�����źų�ʼֵΪ0
		TH0=(65536-2)/256;	  //��ʱʱ��߰�λ��ֵ
		TL0=(65536-2)%256;	  //��ʱʱ��Ͱ�λ��ֵ
		EA=1;				  //��CPU�ж�
		ET0=1;				  //��T/C0�ж�
		TR0=1;
		
        
   /* TMOD |= 0x01;  //���ö�ʱ������ģʽ
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  
    EA = 1;
    ET0 = 1;  //�򿪶�ʱ���ж�
    TR0 = 1;  //������ʱ��*/

    while(1)
		{
			if(flag_100)
			{	
				flag_100=0;
        init_pcf8591(0x03); 
	      ND= read_pcf8591();
			}
	  	display1();
	  	LCD_COM(0x80); //��ʾ��һ��
    	for(i = 0;i < 16;i++)
		  LCD_write(du1[i]);

	  	LCD_COM(0x40 + 0x80); //��ʾ�ڶ���
	  	display2();
		  for(j = 0;j < 16;j++)
		  LCD_write(display[j]);

		  key_scan();
		  LED=1;	   //Ϩ��P1.0�ڵ�
	    if(DOUT==1)//��Ũ�ȸ����趨ֵʱ ��ִ����������
		 {
				delay();//��ʱ������
			if(DOUT==1)//ȷ�� Ũ�ȸ����趨ֵʱ ��ִ����������
				{
					LED=0;	   //����P1.0�ڵ�
				}
		 }
	 }
}