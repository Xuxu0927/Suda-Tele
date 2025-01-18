#include <LCD1602.h>
 
#include <STC15F2K60S2.H>
 
 
//1602的控制引脚定义
sbit RS = P2^0;    	//寄存器选择，高电平时选择数据寄存器、低电平时选择指令寄存器
sbit RW = P2^1;		//读写控制，低写，高读
					// RS＝0、RW＝0——表示向LCM写入指令，可以写入指令或者显示地址
					// RS＝0、RW＝1——表示读取Busy标志
					// RS＝1、RW＝0——表示向LCM写入数据
					// RS＝1、RW＝1——表示从LCM读取数据
sbit EN = P1^2;		//使能端，当E端由高电平跳变成低电平时，液晶模块执行命令
#define LCD_DATA P0	//定义传入数据的特殊功能寄存器，或者使用 “static sfr LCD_DATA=0X80;”定义
static unsigned char MaxStrlen = 40;	//定义一行最多显示字符数
 
 
 
/*****函数部分*****/
static void LCD_Delay();
static bit LCD_BUSY(void);
 
/*************************************************
 * @name LCD_Delay()
 * @brief LCD延时函数(12Mhz晶振延时4uS)
 * @param 无
 * @return 无
**************************************************/
static void LCD_Delay()
{
	unsigned char data i;
	i = 10;
	while (--i);
}
 
/*************************************************
 * @name LCD_BUSY()
 * @brief 检测LCD1602是否处于忙状态
 * @param 无
 * @return 忙信号布尔值（bit）。返回1，则LCD_BUSY；返回0，则OK
**************************************************/
static bit LCD_BUSY(void)
{
	LCD_DATA=0xff;
	RS = 0;
	RW = 1;
	EN = 1;
	LCD_Delay();
	EN = 0;
	return (bit)(LCD_DATA & 0x80); //最高位为忙信号位
}
 
/*************************************************
 * @name LcdWriteCom()
 * @brief LCD写一字节命令
 * @param cmd 待写控制命令（unsigned char）
 * @return 无
**************************************************/
void LcdWriteCom(unsigned char cmd)
{
	while(LCD_BUSY());   //测忙
	RS = 0;
	RW = 0;
	EN = 1;
	LCD_DATA = cmd;
	LCD_Delay();
	EN = 0;
}
 
/*************************************************
 * @name LcdWriteData()
 * @brief LCD写一字节数据
 * @param dat 待写显示数据（unsigned char）
 * @return 无
**************************************************/
void LcdWriteData(unsigned char dat)
{
	while(LCD_BUSY());   //测忙
	RS = 1;
	RW = 0;
	EN = 1;
	LCD_DATA = dat;
	LCD_Delay();
	EN = 0;
}
 
/*************************************************
 * @name LCD_ClsLine()
 * @brief LCD清除行
 * @param line 设置待清除行号（unsigned char）
 * @return 无
**************************************************/
void LCD_ClsLine(unsigned char line)
{
	unsigned char i=0;
	for(i=0;i<16;i++)
		LCD_Display_Char(i,line,' ');
}
 
/*************************************************
 * @name LCD_Clear()
 * @brief LCD清屏
 * @param 无
 * @return 无
**************************************************/
void LCD_Clear(void)
{
	LCD_ClsLine(0);
	LCD_ClsLine(1);
}
 
/*************************************************
 * @name LcdInit()
 * @brief LCD液晶屏的初始化
 * @param 无
 * @return 无
**************************************************/
void LCD_Init(void)
{
	LcdWriteCom(0x38);   //功能设置,8位数据接口，两行显示，5×8点阵，即0b00111000也就是0x38
	LcdWriteCom(0x0c);   //显示开关控制,00001100 显示开，光标不显示，光标不闪烁
	LcdWriteCom(0x06);   //输入方式设置,00000110 I/D=1：写入新数据后光标右移；S=0：显示不移动。
	LcdWriteCom(0x01);   //清除LCD的显示内容
	LCD_Clear();
}
 
 
/*************************************************
 * @name LCD_Display_Char()
 * @brief LCD写一个字符
 * @param p 设置显示的行坐标（unsigned char）
 * @param q 设置显示的列坐标（unsigned char）
 * @param ch 待写字符（unsigned char）
 * @return 无
**************************************************/
void LCD_Display_Char(unsigned char p,unsigned char q,unsigned char ch)
{
 
	unsigned char addr;
	p-=1;
	q-=1;
	while(q>=16)
	{
		q-=16;
		p++;
	}
	while(p>=2) p-=2;
	if (p == 0)
  	{
    	addr = 0x00 + q; //第一行的x位置显示
  	}
  	else
  	{
    	addr = 0x40 + q; //第二行x的位置显示
  	}
  	LcdWriteCom(addr + 0x80);
		LcdWriteData(ch);
}
 
/*************************************************
 * @name LCD_Display_String()
 * @brief LCD写字符串
 * @param p 设置显示的行坐标（unsigned char）
 * @param q 设置显示的列坐标（unsigned char）
 * @param str 待写字符串（unsigned char）
 * @return 字符长度（unsigned char）
**************************************************/
void LCD_Display_String(unsigned char p,unsigned char q, unsigned char *str)
{
 
	unsigned char i=0;
	while(str[i]!=0)
	{
		LCD_Display_Char(p,q, str[i]);
		q++;
		i++;
	}
}
 
 
/*************************************************
 * @name 	LCD_WriteNum()
 * @brief 	LCD写一个数字。
 * 			整数显示——len=数字位数，point=0，num=要显示的数字；
 * 			小数显示——len=num位数，point=小数位数，num=需要显示的小数*10^(point)（即，先将小数放大为整形）
 * @param p 设置显示的行坐标（unsigned char）
 * @param q 设置显示的列坐标（unsigned char）
 * @param len 	待显示的数字位数（unsigned char）
 * @param point 小数点位置（unsigned char）。point=0时，显示整数
 * @param num 	待显示的数字（long）。小数请放大为整数，范围-2147483648~2147483648
 * @return 显示出来的数字所占真实位数（unsigned char)
**************************************************/
unsigned char LCD_WriteNum(unsigned char p, unsigned char q, unsigned char len, unsigned char point, long num)
{
 
	unsigned char real_len, flag=0;
	if(point) 	len++;
	else		point--;
	if(num<0)
	{
		LCD_Display_Char(p,q,'-');
		len++;
		num=-num;
		flag=1;
	}
	real_len=len+6;
	while(len-flag)
	{
		if(num>=0) len--;
		if(point)
		{
			
			LCD_Display_Char(p, q+len, '0'+num%10);
			num/=10;
		}
		else
		{
			LCD_Display_Char(p, q+len, '.');
		}
		point--;
	}
	return real_len;
}