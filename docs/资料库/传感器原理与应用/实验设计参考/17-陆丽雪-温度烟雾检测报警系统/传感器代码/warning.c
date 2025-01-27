#include "STC15F2K60S2.h"
#include "intrins.h"
#include "onewire.h"
#include "iic.h"    //I2C总线驱动库 

code unsigned char seg7code[10]={ 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //显示段码 数码管字跟
unsigned char wei[4]={0XEf,0XDf,0XBf,0X7f};  //位的控制端								 //位控制码
code unsigned char tab[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff };
unsigned char dspbuf[8] = {10,10,10,10,10,0,0,0};  //显示缓冲区
unsigned char dspcom = 0;
unsigned char ad_value, intr;
bit flag_100;


sbit CLK = P3^7;  //时钟脉冲  
sbit SE = P1^2;   // LCD使能端口
sbit RW = P2^1;   // LCD读写端口
sbit RS = P2^0;   // LCD写数据或写命令端口
sbit DQ = P1^4;   // 定义P1^4口为DS18B20的数据口
sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;
sbit LED = P0^0;	 //定义单片机P1口的第1位 （即P1.0）为指示端
sbit DOUT = P2^0;	 //定义单片机P2口的第1位 （即P2.0）为传感器的输入端,


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


void delay()//输出延时程序
{
unsigned char m,n,s;
for(m=20;m>0;m--)
for(n=20;n>0;n--)
for(s=248;s>0;s--);
}
void LCD_COM(unsigned char dat)    //LCD写命令
{
	 Delay5ms();
	 RW = 0; //0写数据 1读数据
	 RS = 0; //0写命令 1读命令
	 
	 SE = 1;
	 P0 = dat;  //LCD数据端口

	 SE = 0;    //保持数据下降沿传输数据
}

void LCD_write(unsigned char dat)   //LCD写数据
{
	 Delay5ms();
	 RW = 0;  //0写数据 1读数据
	 RS = 1;   //0写命令 1写数据
	 
	 SE = 1;
	 P0 = dat;   //LCD数据端口
	 
	 SE = 0;      //保持数据下降沿传输数据
}

void LCD_init() //LCD初始化
{

	 LCD_COM(0x38); //（0x38开5*7方阵，0x3c开5*10方阵）8位总线，显示两行，无光标，5*7点阵
	 LCD_COM(0x01); //清屏
	 LCD_COM(0x06); //（0x06写一个光标后移，0x04光标左移，0x07屏幕右移且光标后移）光标后移，显示屏不右移
	 LCD_COM(0x0c); //（0x0e显示光标不闪烁，0x0f开光标闪烁）B2位显示开，无光标，不闪烁
}
void timer0( ) interrupt 1 //定时器0工作方式1
{

TH0=(65536-2)/256;	  //重装计数初值
TL0=(65536-2)%256;	  //重装计数初值
CLK=!CLK;			  //取反
}

void isr_timer_0(void)  interrupt 1  //默认中断优先级 1
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  //定时器重载 
	  if(++intr==50)
		{
			flag_100=1;
			intr=0;
		}
}
unsigned int ReadTemp(void)    //DS18B20读取温度
{
     unsigned char TH,TL;
	unsigned int temp;
	unsigned int tt;
	 
	 init_ds18b20();   //初始化
	 Write_DS18B20(0xcc); //跳过选择ROM
	 Write_DS18B20(0x44); //启动转换命令
	
	 init_ds18b20();   //再次初始化
	 Write_DS18B20(0xcc);
	 Write_DS18B20(0xbe);  //读取数据命令
	
	 TL = Read_DS18B20();
	 TH = Read_DS18B20();
	
   	temp = ((TH << 8) | TL); //精确到小数
	tt = temp * 10 * 0.0625 + 0.05; //精确到小数后一位
	
	 return tt;
}

void init_pcf8591(unsigned char channel)
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(channel);  //ADC通道3
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
	IIC_Ack(0);     //发送非应答信号 
	IIC_Stop();
	
	return ND;
}
void display1() //LCD第一行显示
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
	  du1[2] = Temp / 100 % 10 + 0x30; //＋0x30的原因是数字在LCD不能显示要转化成字符就是AIISC码;
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

void display2() //LCD第二行显示
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
	  unsigned char reset_cnt=0;  //开机次数存储 (最大存储值255)
	unsigned char i,j;
		P2=0xa0;P0=0x00;P2=0x00;
		P2=0x80;P0=0xff;P2=0x00;
		P2=0xe0;P0=0xff;P2=0x00;
		LCD_init();
	
		TMOD=0X01;			  //定时器中断0
		CLK=0;				  //脉冲信号初始值为0
		TH0=(65536-2)/256;	  //定时时间高八位初值
		TL0=(65536-2)%256;	  //定时时间低八位初值
		EA=1;				  //开CPU中断
		ET0=1;				  //开T/C0中断
		TR0=1;
		
        
   /* TMOD |= 0x01;  //配置定时器工作模式
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  
    EA = 1;
    ET0 = 1;  //打开定时器中断
    TR0 = 1;  //启动定时器*/

    while(1)
		{
			if(flag_100)
			{	
				flag_100=0;
        init_pcf8591(0x03); 
	      ND= read_pcf8591();
			}
	  	display1();
	  	LCD_COM(0x80); //显示第一行
    	for(i = 0;i < 16;i++)
		  LCD_write(du1[i]);

	  	LCD_COM(0x40 + 0x80); //显示第二行
	  	display2();
		  for(j = 0;j < 16;j++)
		  LCD_write(display[j]);

		  key_scan();
		  LED=1;	   //熄灭P1.0口灯
	    if(DOUT==1)//当浓度高于设定值时 ，执行条件函数
		 {
				delay();//延时抗干扰
			if(DOUT==1)//确定 浓度高于设定值时 ，执行条件函数
				{
					LED=0;	   //点亮P1.0口灯
				}
		 }
	 }
}