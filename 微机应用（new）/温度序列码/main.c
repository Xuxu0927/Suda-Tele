#include "tou.h"
#include "intrins.h"
#include "onewire.h"
sbit rsLCD=P2^0;
sbit wrLCD=P2^1;
sbit enLCD=P1^2;
sbit S7=P3^0;
sbit S6=P3^1;
sbit S5=P3^2;
sbit S4=P3^3;
unsigned char min = 15;
unsigned char max = 30;
unsigned int Temp;
unsigned char du1[16];
unsigned char display[16];
unsigned char date[8];
unsigned char disflag = 0;

void delaynms(unsigned int ms)
{
   unsigned int x,y;
   for(x=ms;x;x--)
   for(y=110;y;y--);	
}

void comLCD(unsigned char com) 
{
   enLCD=0;
   rsLCD=0;
   wrLCD=0; 
   P0=com;
   delaynms(1);
   enLCD=1;
   delaynms(1);
   enLCD=0;
}
void datLCD(unsigned char dat)
{
   enLCD = 0;
   rsLCD=1;
   wrLCD=0;
   P0=dat;
   delaynms(1);
   enLCD=1;
   delaynms(1);
   enLCD=0;
}
void initLCD()
{
   comLCD(0x38);
   delaynms(10);
   comLCD(0x06); 
   delaynms(10);
   comLCD(0x0c);
   delaynms(10);
   comLCD(0x01); 
   delaynms(10);
   comLCD(0x02+0x80); 
}
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



void LCD_ASCII(char rom) //取ASCII码
{
	unsigned char a,b;
	a = rom & 0x0f;  //取低四位
	b = rom & 0xf0;  //取高四位
	b >>= 4;
	if((b >= 0x00)&&(b <= 0x09))
	{
		datLCD(b + 0x30);
  	}
	else
	{
		datLCD(b + 0x37);
  	}
	if((a >= 0x00)&&(a <= 0x09))
	{
		datLCD(a + 0x30);
  	}
	else
	{
		datLCD(a + 0x37);
  	}
}

void get_number() //将读取序列号写入数组
{
	unsigned char i;
	init_ds18b20(); //初始化
	Write_DS18B20(0x33);
	for(i = 0;i < 8; i++)
	{
		date[i] = Read_DS18B20();
  	}	
	}
void display2() //LCD第二行显示
{
	if(disflag==0)
	{
		get_number();
		LCD_ASCII(date[7]);
		LCD_ASCII(date[6]);
		LCD_ASCII(date[5]);
		LCD_ASCII(date[4]);
		LCD_ASCII(date[3]);
		LCD_ASCII(date[2]);
		LCD_ASCII(date[1]);
		LCD_ASCII(date[0]);
	}
}
void display1() //LCD第一行显示
{

if(disflag==0)
{
 	du1[0] = 'N';
  	du1[1] = 'U';
  	du1[2] = 'M';
  	du1[3] = 'B';
  	du1[4] = 'E';
	du1[5] = 'R';
	du1[6] = ':';
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
}
unsigned char aa[13];
unsigned char i;
unsigned char mm[15];
bit flag=0;
bit flag1=0;
void main()
{
float temper;
unsigned int temp;
P2=((P2&0x1f)|0x80);
	P0=0xff;
	P2&=0x1f;
	P2=((P2&0x1f)|0xc0);
	P0&=0x00;
	P2&=0x1f;
   initLCD();
   delaynms(10);
    while(1)
   {   
		 if(S7==0)
			 {
			delaynms(10);
			if(S7==0)
			{
				comLCD(0x01);
			flag1=~flag1;
				while(S7==0);
			}
		}
			 if(flag1==0)
				 {
    temper= read_temperature();
		 temp=temper*100;


  aa[0]='T';
  aa[1]='e';
  aa[2]='m';
  aa[3]='p';
  aa[4]=':';
  aa[5]= temp/1000+'0';
  aa[6]= temp%1000/100+'0';
  aa[7]=0x2E;
  aa[8]=temp%100/10+'0';
  aa[9]=temp%10+'0';
  aa[10]=temp/1000+'0';					 
  aa[11]=0xdf;
  aa[12]='C';
	if(temper>=max)
	{
		P2=((P2&0x1f)|0xa0);
		P0=0x40;
		P2&=0x1f;
		P2=((P2&0x1f)|0x80);
	P0=0xfb;
	P2&=0x1f;
		delaynms(500);
		P2=((P2&0x1f)|0x80);
	P0=0xff;
	P2&=0x1f;
		delaynms(500);
	}
	else if(temper<=min)
	{
		P2=((P2&0x1f)|0xa0);
		P0=0xaf;
		P2&=0x1f;
		P2=((P2&0x1f)|0x80);
	P0=0xfe;
	P2&=0x1f;
	}

	 else
	{
		P2=((P2&0x1f)|0xa0);
		P0=0x10;
		P2&=0x1f;
		P2=((P2&0x1f)|0x80);
	P0=0xfd;
	P2&=0x1f;
	}
  
		 comLCD(0x82);
      for(i=0;i<12;i++)
     {
      datLCD(aa[i]);
     delaynms(10);
	 
     }
	 if(S6==0)
		{
			delaynms(10);
			if(S6==0)
				flag=~flag;
			
				while(S6==0);
		}
		if(S5==0)
		{
			delaynms(10);
		if(S5==0)
		{
			if(flag==1)
			max=max+1;
			else 
				min=min+1;
				while(S5==0);
		}
	}
		if(S4==0)
		{
			delaynms(10);
			if(S4==0)
			{
				if(flag==1)
				max=max-1;
				else
				min=min-1;
				
				if(max <= min)
					max=min;
					
				while(S4==0);
			}
		}
		 comLCD(0x80+0x40);
		mm[0]='H';
		mm[1]=':';
		mm[2]=max/10+'0';
		mm[3]=max%10+'0';
		mm[4]=0xdf;
		mm[5]='C';
		mm[6]=' ';
		mm[7]=' ';
		mm[8]='L';
		mm[9]=':';
		mm[10]=min/10+'0';
		mm[11]=min%10+'0';
		mm[12]=0xdf;
        mm[13]='C';
      for(i=0;i<14;i++)
		{
      datLCD(mm[i]);
     delaynms(10);
		 }
	 }
				 if(flag1==1)
				 {
					 unsigned char i,j;
	  	display1();
	  	comLCD(0x80); //显示第一行
    	for(i = 0;i < 16;i++)
		datLCD(du1[i]);

	  	comLCD(0x40 + 0x80); //显示第二行
	  	display2();
		for(j = 0;j < 16;j++)
		datLCD(display[j]);
				  }
 }
}