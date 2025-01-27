#include <LCD1602.h>
 
#include <STC15F2K60S2.H>
 
 
//1602�Ŀ������Ŷ���
sbit RS = P2^0;    	//�Ĵ���ѡ�񣬸ߵ�ƽʱѡ�����ݼĴ������͵�ƽʱѡ��ָ��Ĵ���
sbit RW = P2^1;		//��д���ƣ���д���߶�
					// RS��0��RW��0������ʾ��LCMд��ָ�����д��ָ�������ʾ��ַ
					// RS��0��RW��1������ʾ��ȡBusy��־
					// RS��1��RW��0������ʾ��LCMд������
					// RS��1��RW��1������ʾ��LCM��ȡ����
sbit EN = P1^2;		//ʹ�ܶˣ���E���ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ��ִ������
#define LCD_DATA P0	//���崫�����ݵ����⹦�ܼĴ���������ʹ�� ��static sfr LCD_DATA=0X80;������
static unsigned char MaxStrlen = 40;	//����һ�������ʾ�ַ���
 
 
 
/*****��������*****/
static void LCD_Delay();
static bit LCD_BUSY(void);
 
/*************************************************
 * @name LCD_Delay()
 * @brief LCD��ʱ����(12Mhz������ʱ4uS)
 * @param ��
 * @return ��
**************************************************/
static void LCD_Delay()
{
	unsigned char data i;
	i = 10;
	while (--i);
}
 
/*************************************************
 * @name LCD_BUSY()
 * @brief ���LCD1602�Ƿ���æ״̬
 * @param ��
 * @return æ�źŲ���ֵ��bit��������1����LCD_BUSY������0����OK
**************************************************/
static bit LCD_BUSY(void)
{
	LCD_DATA=0xff;
	RS = 0;
	RW = 1;
	EN = 1;
	LCD_Delay();
	EN = 0;
	return (bit)(LCD_DATA & 0x80); //���λΪæ�ź�λ
}
 
/*************************************************
 * @name LcdWriteCom()
 * @brief LCDдһ�ֽ�����
 * @param cmd ��д�������unsigned char��
 * @return ��
**************************************************/
void LcdWriteCom(unsigned char cmd)
{
	while(LCD_BUSY());   //��æ
	RS = 0;
	RW = 0;
	EN = 1;
	LCD_DATA = cmd;
	LCD_Delay();
	EN = 0;
}
 
/*************************************************
 * @name LcdWriteData()
 * @brief LCDдһ�ֽ�����
 * @param dat ��д��ʾ���ݣ�unsigned char��
 * @return ��
**************************************************/
void LcdWriteData(unsigned char dat)
{
	while(LCD_BUSY());   //��æ
	RS = 1;
	RW = 0;
	EN = 1;
	LCD_DATA = dat;
	LCD_Delay();
	EN = 0;
}
 
/*************************************************
 * @name LCD_ClsLine()
 * @brief LCD�����
 * @param line ���ô�����кţ�unsigned char��
 * @return ��
**************************************************/
void LCD_ClsLine(unsigned char line)
{
	unsigned char i=0;
	for(i=0;i<16;i++)
		LCD_Display_Char(i,line,' ');
}
 
/*************************************************
 * @name LCD_Clear()
 * @brief LCD����
 * @param ��
 * @return ��
**************************************************/
void LCD_Clear(void)
{
	LCD_ClsLine(0);
	LCD_ClsLine(1);
}
 
/*************************************************
 * @name LcdInit()
 * @brief LCDҺ�����ĳ�ʼ��
 * @param ��
 * @return ��
**************************************************/
void LCD_Init(void)
{
	LcdWriteCom(0x38);   //��������,8λ���ݽӿڣ�������ʾ��5��8���󣬼�0b00111000Ҳ����0x38
	LcdWriteCom(0x0c);   //��ʾ���ؿ���,00001100 ��ʾ������겻��ʾ����겻��˸
	LcdWriteCom(0x06);   //���뷽ʽ����,00000110 I/D=1��д�������ݺ������ƣ�S=0����ʾ���ƶ���
	LcdWriteCom(0x01);   //���LCD����ʾ����
	LCD_Clear();
}
 
 
/*************************************************
 * @name LCD_Display_Char()
 * @brief LCDдһ���ַ�
 * @param p ������ʾ�������꣨unsigned char��
 * @param q ������ʾ�������꣨unsigned char��
 * @param ch ��д�ַ���unsigned char��
 * @return ��
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
    	addr = 0x00 + q; //��һ�е�xλ����ʾ
  	}
  	else
  	{
    	addr = 0x40 + q; //�ڶ���x��λ����ʾ
  	}
  	LcdWriteCom(addr + 0x80);
		LcdWriteData(ch);
}
 
/*************************************************
 * @name LCD_Display_String()
 * @brief LCDд�ַ���
 * @param p ������ʾ�������꣨unsigned char��
 * @param q ������ʾ�������꣨unsigned char��
 * @param str ��д�ַ�����unsigned char��
 * @return �ַ����ȣ�unsigned char��
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
 * @brief 	LCDдһ�����֡�
 * 			������ʾ����len=����λ����point=0��num=Ҫ��ʾ�����֣�
 * 			С����ʾ����len=numλ����point=С��λ����num=��Ҫ��ʾ��С��*10^(point)�������Ƚ�С���Ŵ�Ϊ���Σ�
 * @param p ������ʾ�������꣨unsigned char��
 * @param q ������ʾ�������꣨unsigned char��
 * @param len 	����ʾ������λ����unsigned char��
 * @param point С����λ�ã�unsigned char����point=0ʱ����ʾ����
 * @param num 	����ʾ�����֣�long����С����Ŵ�Ϊ��������Χ-2147483648~2147483648
 * @return ��ʾ������������ռ��ʵλ����unsigned char)
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