#include "reg52.h"
#include "intrins.h"
#include "math.h"
#include "iic.h"
#include "lcd.h"
#include "stdio.h"



u8 ge=0,shi=0,bai=0,qian=0,wan=0;          //��ʾ����             
u8 BUF[8]=0; 						 //���ݻ�����

//******************************��ʾ��LCD������ȡλ********************************//
void Conversion(u16 temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
	  qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
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
		Multiple_Read_HMC5883();      				//������ȡ����Ƕ����ݣ��洢��BUF�� 
		//---------��ʾXY��
		X=BUF[1] << 8 | BUF[0]; //Combine MSB and LSB of X Data output register  �����Чλ
		Y=BUF[3] << 8 | BUF[2]; //Combine MSB and LSB of Y Data output register
		Z=BUF[5] << 8 | BUF[4]; //Combine MSB and LSB of Z Data output register
		
		if(X>0x7fff)X-=0xffff;	  
		if(Y>0x7fff)Y-=0xffff;
		if(Z>0x7fff)Z-=0xffff;	 
		
		
		Angle_XY= atan2((double)Y,(double)X) * (180 / 3.14159265) + 180; //����XYƽ��Ƕ�
		Angle_XY*=10;
		angle=Angle_XY;
		Conversion(Angle_XY);       //����XYƽ��Ƕ����ݺ���ʾ
		Display_One_Char(5,1,':'); 
		Display_One_Char(6,1,qian); 
    Display_One_Char(7,1,bai); 
    Display_One_Char(8,1,shi); 
		Display_One_Char(9,1,'.'); 
    Display_One_Char(10,1,ge);
		
		if((angle >= 3380) || (angle <= 220))	  //�� N
		 {
       
        Display_One_Char(3,1,'N'); 
        Display_One_Char(4,1,' '); 
     }
		if((angle >= 230) && (angle <= 670))	  //�� ��
		{
       
        Display_One_Char(3,1,'E'); 
        Display_One_Char(4,1,'N'); 
     }
		if((angle >= 680) && (angle <= 1120))	  //�� E
		{
       
        Display_One_Char(3,1,'E'); 
        Display_One_Char(4,1,' '); 
     }
		if((angle >= 1130) && (angle <= 1570))	  //�� ��
			{
       
        Display_One_Char(3,1,'E'); 
        Display_One_Char(4,1,'S'); 
     }
		if((angle >= 1580) && (angle <= 2010))	  //��  S
			{
       
        Display_One_Char(3,1,'S'); 
        Display_One_Char(4,1,' '); 
     }
		if((angle >= 2020) && (angle <= 2460))	  //�� ��  
			{
       
        Display_One_Char(3,1,'W'); 
        Display_One_Char(4,1,'S'); 
     }
		if((angle >= 2470) && (angle <= 2910))	  //��  W  
			{
       
        Display_One_Char(3,1,'W'); 
        Display_One_Char(4,1,' '); 
     }	
		if((angle >= 2920) && (angle <= 3360))	  //��  ��  
		{
       
        Display_One_Char(3,1,'W'); 
        Display_One_Char(4,1,'N'); 
     }
		
		
		/*
		Angle_XZ= atan2((double)Z,(double)X) * (180 / 3.14159265) + 180; //����XZƽ��Ƕ�
		Angle_XZ*=10;
		Conversion(Angle_XZ);       //����XZƽ��Ƕ����ݺ���ʾ
		
    Angle_YZ= atan2((double)Z,(double)Y) * (180 / 3.14159265) + 180; //����YZƽ��Ƕ�
		Angle_YZ*=10;
		Conversion(Angle_YZ);       //����YZƽ��Ƕ����ݺ���ʾ
		*/
	
		Delay_ms(500);   //��ʱ                     
  }



}




























