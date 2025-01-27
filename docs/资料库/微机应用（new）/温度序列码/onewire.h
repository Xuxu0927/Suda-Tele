#ifndef _ONEWIRE_H
#define _ONEWIRE_H

#include "tou.h"
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int 
void Write_DS18B20(unsigned char dat);
unsigned char Read_DS18B20(void);
bit init_ds18b20(void);
float read_temperature(void);

#endif