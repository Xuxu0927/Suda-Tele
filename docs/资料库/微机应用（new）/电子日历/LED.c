#include <STC15F2K60S2.H>
#include "LED.h"
void LED(unsigned char x)
{
	P2 = ((P2 & 0x1f) | 0x80);
	P0 = x;
	P2 &= 0x1f;
}