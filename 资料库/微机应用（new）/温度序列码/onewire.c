/*
  ????: ???????
  ????: Keil uVision 4.10 
  ????: CT107?????????
  ?    ?: 2011-8-9
*/
#include "onewire.h"
sbit DQ = P1^4;
void Delay_OneWire(unsigned int t)  //STC12C5260S2
{
	unsigned char i;
	while(t--){
		for(i=0;i<12;i++);
	}
}

//DS18B20?????
bit Init_DS18B20(void)
{
	bit initflag = 0;
	DQ = 1;
	Delay_OneWire(12);
	DQ = 0;
	Delay_OneWire(80); 
	DQ = 1;
	Delay_OneWire(10); 
	initflag = DQ;    
	Delay_OneWire(5);
  
	return initflag;
}

//??????DS18B20?????
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
}

//?DS18B20??????
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}

float read_temperature(void)
{
unsigned char low,high;
unsigned int temp;
float temperature;
	
Init_DS18B20();
Write_DS18B20(0xcc);
Write_DS18B20(0x44);
Delay_OneWire(200);
	
Init_DS18B20();
Write_DS18B20(0xcc); 
Write_DS18B20(0xbe);
	
low=Read_DS18B20();
high=Read_DS18B20();
temp=high;
temp <<= 8;
temp |= low;
temperature = temp*0.0625;
return temperature;
}