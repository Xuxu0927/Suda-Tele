#ifndef __ds1302_H__
#define __ds1302_H__
extern int DS1302_Time[],Temp_DS1302_Time[],alarm_Time[];
extern unsigned char KeyNum,MODE,TimeSetFlashFlag;
void DS1302_Init(void);//��ʼ��
void DS1302_WriteByte(unsigned char Command,Data);//д��
unsigned char DS1302_ReadByte(unsigned char Command);//��ȡ
void DS1302_Time_Load(void);//ʱ�����
void DS1302_Time_ReLoad(void);//������
void DS1302_SetTime(void);//ʱ������
void DS1302_ReSetTime(void);//������
void DS1302_ReadTime(void);//��ʱ��
void DS1302_ShowTime(void);//��ʾʱ��
void DS1302_ShowStopTime(void);//��ͣʱ�䲢��ʾ
#endif