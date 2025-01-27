#include "reg52.h"
#include "intrins.h"
#include "math.h"
#include "iic.h"
#include "lcd.h"
#include "stdio.h"



u8 ge=0,shi=0,bai=0,qian=0,wan=0;          //显示变量             
u8 BUF[8]=0; 						 //数据缓冲区

//******************************显示在LCD的数据取位********************************//
void Conversion(u16 temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	  qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	
}


void main()
{
//	u16 i;
	int X=0,Y=0,Z=0;
	double Angle_XY=0,Angle_XZ=0,Angle_YZ=0, angle;;	
  Init_Lcd();
	
	
	Init_HMC5883();
	
	Display_One_Char(2,0,'Z'); 
	Display_One_Char(3,0,'h'); 
	Display_One_Char(4,0,'i'); 

	Display_One_Char(6,0,'N');
	Display_One_Char(7,0,'a');
	Display_One_Char(8,0,'n');

	Display_One_Char(10,0,'Z');
	Display_One_Char(11,0,'h');
	Display_One_Char(12,0,'e');
	Display_One_Char(13,0,'n');

	Display_One_Char(4,1,'E'); 
  Display_One_Char(5,1,':'); 
  Display_One_Char(9,1,'.'); 
				
	Delay_ms(300);
	while(1)            
	{ 
		Multiple_Read_HMC5883();      				//连续读取三轴角度数据，存储在BUF中 
		//---------显示XY轴
		X=BUF[1] << 8 | BUF[0]; //Combine MSB and LSB of X Data output register  最高有效位
		Y=BUF[3] << 8 | BUF[2]; //Combine MSB and LSB of Y Data output register
		Z=BUF[5] << 8 | BUF[4]; //Combine MSB and LSB of Z Data output register
		
		if(X>0x7fff)X-=0xffff;	  
		if(Y>0x7fff)Y-=0xffff;
		if(Z>0x7fff)Z-=0xffff;	 
		
		
		Angle_XY= atan2((double)Y,(double)X) * (180 / 3.14159265) + 180; //计算XY平面角度
		Angle_XY*=10;
		angle=Angle_XY;
		Conversion(Angle_XY);       //计算XY平面角度数据和显示
		Display_One_Char(5,1,':'); 
		Display_One_Char(6,1,qian); 
    Display_One_Char(7,1,bai); 
    Display_One_Char(8,1,shi); 
		Display_One_Char(9,1,'.'); 
    Display_One_Char(10,1,ge);
		
		if((angle >= 3380) || (angle <= 220))	  //北 N
		 {
       
        Display_One_Char(3,1,'N'); 
        Display_One_Char(4,1,' '); 
     }
		if((angle >= 230) && (angle <= 670))	  //东 北
		{
       
        Display_One_Char(3,1,'E'); 
        Display_One_Char(4,1,'N'); 
     }
		if((angle >= 680) && (angle <= 1120))	  //东 E
		{
       
        Display_One_Char(3,1,'E'); 
        Display_One_Char(4,1,' '); 
     }
		if((angle >= 1130) && (angle <= 1570))	  //东 南
			{
       
        Display_One_Char(3,1,'E'); 
        Display_One_Char(4,1,'S'); 
     }
		if((angle >= 1580) && (angle <= 2010))	  //南  S
			{
       
        Display_One_Char(3,1,'S'); 
        Display_One_Char(4,1,' '); 
     }
		if((angle >= 2020) && (angle <= 2460))	  //西 南  
			{
       
        Display_One_Char(3,1,'W'); 
        Display_One_Char(4,1,'S'); 
     }
		if((angle >= 2470) && (angle <= 2910))	  //西  W  
			{
       
        Display_One_Char(3,1,'W'); 
        Display_One_Char(4,1,' '); 
     }	
		if((angle >= 2920) && (angle <= 3360))	  //西  北  
		{
       
        Display_One_Char(3,1,'W'); 
        Display_One_Char(4,1,'N'); 
     }
		
		
		/*
		Angle_XZ= atan2((double)Z,(double)X) * (180 / 3.14159265) + 180; //计算XZ平面角度
		Angle_XZ*=10;
		Conversion(Angle_XZ);       //计算XZ平面角度数据和显示
		
    Angle_YZ= atan2((double)Z,(double)Y) * (180 / 3.14159265) + 180; //计算YZ平面角度
		Angle_YZ*=10;
		Conversion(Angle_YZ);       //计算YZ平面角度数据和显示
		*/
	
		Delay_ms(500);   //延时                     
  }



}




























