#ifndef __ds1302_H__
#define __ds1302_H__
extern int DS1302_Time[],Temp_DS1302_Time[],alarm_Time[];
extern unsigned char KeyNum,MODE,TimeSetFlashFlag;
void DS1302_Init(void);//初始化
void DS1302_WriteByte(unsigned char Command,Data);//写入
unsigned char DS1302_ReadByte(unsigned char Command);//读取
void DS1302_Time_Load(void);//时间加载
void DS1302_Time_ReLoad(void);//反加载
void DS1302_SetTime(void);//时间设置
void DS1302_ReSetTime(void);//反设置
void DS1302_ReadTime(void);//读时间
void DS1302_ShowTime(void);//显示时间
void DS1302_ShowStopTime(void);//暂停时间并显示
#endif