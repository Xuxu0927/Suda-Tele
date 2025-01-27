#ifndef __LCD1602_H__
#define __LCD1602_H__
void LcdWriteCom(unsigned char com);
void LcdWriteData(unsigned char dat);
void LCD_Init(void);						      
void LCD_SET_POS(unsigned char p,unsigned char q);
void LCD_Display_Char(unsigned char p,unsigned char q,unsigned char ch);
void LCD_Display_String(unsigned char p,q,unsigned char *s);
unsigned char LCD_WriteNum(unsigned char p, unsigned char q, unsigned char len, unsigned char point, long num);
//unsigned char LCD_WriteHex(unsigned char p, unsigned char q, unsigned char len, long num);
#endif