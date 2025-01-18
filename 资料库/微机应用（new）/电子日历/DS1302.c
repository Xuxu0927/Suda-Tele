#include <STC15F2K60S2.h>
#include <intrins.h>
#include "LCD1602.h"
sbit DS1302_SCLK=P1^7;
sbit DS1302_IO=P2^3;
sbit DS1302_CE=P1^3;
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E
int Temp_DS1302_Time[]={24,11,6,10,0,0,3}; 
int DS1302_Time[]={24,11,6,10,0,0,3}; 
int alarm_Time[]={12,0,0,0};
unsigned char TimeSetSelect;
// char *week[]={"SUN"."MON","TUE","WEN","THU","FRI","SAT"};
void DS1302_Init()
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}
/**
  * @brief  DS1302?????
  * @param  Command ???/??
  * @param  Data ??????
  * @retval ?
  */
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}
/**
  * @brief  DS1302?????
  * @param  Command ???/??
  * @retval ?????
  */
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
	Command|=0x01;	//?????????
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO){Data|=(0x01<<i);}
	}
	DS1302_CE=0;
	DS1302_IO=0;	//????IO???0,??????????
	return Data;
}
void DS1302_Time_Load()
{
	int i=0;
	for(i=0;i<7;i++)
	{
		DS1302_Time[i]=Temp_DS1302_Time[i];
	}
}
void DS1302_Time_ReLoad()
{
	int i=0;
	for(i=0;i<7;i++)
	{
		Temp_DS1302_Time[i]=DS1302_Time[i];
	}
}
/**
  * @brief  DS1302????,????,DS1302_Time??????????DS1302?
  * @param  ?
  * @retval ?
  */
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);//????BCD????
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
}
void DS1302_ReSetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_YEAR,Temp_DS1302_Time[0]/10*16+Temp_DS1302_Time[0]%10);//????BCD????
	DS1302_WriteByte(DS1302_MONTH,Temp_DS1302_Time[1]/10*16+Temp_DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,Temp_DS1302_Time[2]/10*16+Temp_DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,Temp_DS1302_Time[3]/10*16+Temp_DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,Temp_DS1302_Time[4]/10*16+Temp_DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,Temp_DS1302_Time[5]/10*16+Temp_DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,Temp_DS1302_Time[6]/10*16+Temp_DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
}
/**
  * @brief  DS1302????,????,DS1302?????????DS1302_Time???
  * @param  ?
  * @retval ?
  */
void DS1302_ReadTime(void)
{
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=Temp/16*10+Temp%16;//BCD???????
	Temp=DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=Temp/16*10+Temp%16;
}
void DS1302_ShowTime(void)
{
	LCD_WriteNum(1,6,2,0,DS1302_Time[0]);
	LCD_WriteNum(1,9,2,0,DS1302_Time[1]);
	LCD_WriteNum(1,12,2,0,DS1302_Time[2]);	
	LCD_WriteNum(2,6,2,0,DS1302_Time[3]);
	LCD_WriteNum(2,9,2,0,DS1302_Time[4]);
	LCD_WriteNum(2,12,2,0,DS1302_Time[5]);	
}
 