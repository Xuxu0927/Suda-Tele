#include <STC15F2K60S2.H>
#include <DS1302.H>
#include "LCD1602.h"
#include "LED.h"
#include <intrins.h>
int key_flag = 0;			
unsigned	char key_value = 0xff;
unsigned char mode=0;

void cls_buzz(void)	
{
    P2 = (P2 & 0x1F | 0xA0);
    P0 = 0x00;
    P2 &= 0x1F;
}

void open_buzz(void)
{
		P2 = (P2 & 0x1F | 0xA0);
    P0 = 0xFF;
    P2 &= 0x1F;
}

void alarm(void)
{
		if((DS1302_Time[3]==alarm_Time[0])&(DS1302_Time[4]==alarm_Time[1])&(DS1302_Time[5]==alarm_Time[2]))
		{
				if(DS1302_Time[6]<=5&alarm_Time[3]==0) 
				open_buzz();
				if(DS1302_Time[6]>5&alarm_Time[3]==1)
				open_buzz();
		}			
		if(DS1302_Time[5]==alarm_Time[2]+10)
		cls_buzz();

}

void Day_Show()//��ʾ����
{
		switch(DS1302_Time[6])
		{
			case 1:
				LCD_Display_String(1,14,"MON");
			break;
			case 2:
				LCD_Display_String(1,14,"TUE");
			break;
			case 3:
				LCD_Display_String(1,14,"WEN");
			break;
			case 4:
				LCD_Display_String(1,14,"THU");
			break;
			case 5:
				LCD_Display_String(1,14,"FRI");
			break;
			case 6:
				LCD_Display_String(1,14,"SAT");
			break;
			case 7:
				LCD_Display_String(1,14,"SUN");
			break;
		}
 
}
void ClockDay_Show()//��ʾ���ӹ���״̬
{
		switch(alarm_Time[3])
		{
			case 0:
				LCD_Display_String(2,1,"Weekday");
			break;
			case 1:
				LCD_Display_String(2,1,"Weekend");
			break;
		}
 
}
void read_keyboard(void)//������̶�ȡ
{
  static unsigned char hang;
	static unsigned char key_state=0;	
	switch(key_state)
	{
		case 0:
		{
			P3 = 0x0f; P42 = 0; P44 = 0;
			if(P3 != 0x0f) //�а�������
			key_state=1;	
		}
		break;
		case 1:
		{
			P3 = 0x0f; P42 = 0; P44 = 0;
			if(P3 != 0x0f) //�а�������
			{
				if(P30 == 0)hang = 1;
				if(P31 == 0)hang = 2;
				if(P32 == 0)hang = 3;
				if(P33 == 0)hang = 4;//ȷ����	    
				switch(hang){
					case 1:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0)		  {key_value=0;key_state=2;}//S7����
						else if(P42 == 0) {key_value=1;key_state=2;}//S11����
						else if(P35 == 0) {key_value=2;key_state=2;}//S15����
						else if(P34 == 0) {key_value=3;key_state=2;}//S19����
					}
					break;
					case 2:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0) 			{key_value=4;key_state=2;}//S6����
						else if(P42 == 0) {key_value=5;key_state=2;}//S10����
						else if(P35 == 0) {key_value=6;key_state=2;}//S14����
						else if(P34 == 0) {key_value=7;key_state=2;}//S18����
					}
					break;
					case 3:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0) 			{key_value=8;key_state=2;}//S5����
						else if(P42 == 0) {key_value=9;key_state=2;}//S9����
						else if(P35 == 0) {key_value=10;key_state=2;}//S13����
						else if(P34 == 0) {key_value=11;key_state=2;}//S17����
					}
					break;
					case 4:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0) 			{key_value=12;key_state=2;}//S4����
						else if(P42 == 0) {key_value=13;key_state=2;}//S8����
						else if(P35 == 0) {key_value=14;key_state=2;}//S12����
						else if(P34 == 0) {key_value=15;key_state=2;}//S16����
					}
					break;
				}	
			}
			else
			{
				key_state=0;	
			}  	   
		}
		break;
		case 2:     
		{
			P3 = 0x0f; P42 = 0; P44 = 0;
			if(P3 == 0x0f) //�����ſ�
			key_state=0;	
		}
		break;			
    } 
}
void KeyAction()
{
	switch(key_value)
	{
		case 0:
			mode=1;
			LED(0xfe);
		break;
		case 1:
			mode=2;
			LED(0xfd);
		break;
		case 2:
			mode=3;
			LED(0xfb);
		break;
		case 4:
			mode=4;
			LED(0xf7);
		break;
		case 5:
			mode=5;
			LED(0xef);
		break;
		case 6:
			mode=6;
			LED(0xdf);
		break;
		case 8:
			mode=7;
			LED(0xbf);
		break;
		case 14://�޸�ȡ��
			LCD_Init();
			mode=0;
		break;
		case 15:
			mode=15;
			LED(0xff);
		break;
		case 13:  
     mode = 19;
     LED(0xbf); 
    break;	
    case 9:  
     mode = 20;  
    break;
    case 10: 
     mode = 21;  
    break;
    case 11: 
     mode = 22;  
    break;	
		case 12: 
		 mode = 23;  
		break;
	}
}
void Disply()
{
	switch(mode)
	{
		case 0:
			DS1302_Time_ReLoad();
			LCD_Display_String(1,1,"DATE:");
			LCD_Display_String(2,1,"TIME:");
			LCD_Display_String(1,8,"-");
			LCD_Display_String(1,11,"-");	
			LCD_Display_String(2,8,":");
			LCD_Display_String(2,11,":");
			DS1302_ReadTime();
			DS1302_ShowTime();
			Day_Show();
			break;
		case 1://�޸����
			LCD_Display_String(1,1,"YearSet      ");
			LCD_WriteNum(2,1,2,0,Temp_DS1302_Time[0]);
			if(key_value==3)//+1��
			{
				Temp_DS1302_Time[0]++;
				if(Temp_DS1302_Time[0]>99){Temp_DS1302_Time[0]=0;}
			}
			if(key_value==7)//-1��
			{
				Temp_DS1302_Time[0]--;
				if(Temp_DS1302_Time[0]<0){Temp_DS1302_Time[0]=99;}	
			}
			break;
			
		case 2://���޸�
			LCD_Display_String(1,1,"MonthSet   ");
			LCD_WriteNum(2,1,2,0,Temp_DS1302_Time[1]);
 
			if(key_value==3)//+1��
			{
				Temp_DS1302_Time[1]++;
				if(Temp_DS1302_Time[1]>12){Temp_DS1302_Time[1]=1;}
			}
			if(key_value==7)//-1��
			{
				Temp_DS1302_Time[1]--;
				if(Temp_DS1302_Time[1]<1){Temp_DS1302_Time[1]=12;}
			}
			break;
	
		case 3://���޸�
			LCD_Display_String(1,1,"DateSet      ");
			LCD_WriteNum(2,1,2,0,Temp_DS1302_Time[2]);
			
			if(key_value==3)//+1��
			{
				Temp_DS1302_Time[2]++;
				if( Temp_DS1302_Time[1]==1 || Temp_DS1302_Time[1]==3 || Temp_DS1302_Time[1]==5 || Temp_DS1302_Time[1]==7 || 
						Temp_DS1302_Time[1]==8 || Temp_DS1302_Time[1]==10 || Temp_DS1302_Time[1]==12)//����
				{
						if(Temp_DS1302_Time[2]>31){Temp_DS1302_Time[2]=1;}//1-31
				}
				else if(Temp_DS1302_Time[1]==4 || Temp_DS1302_Time[1]==6 || Temp_DS1302_Time[1]==9 || Temp_DS1302_Time[1]==11)//С��
				{
						if(Temp_DS1302_Time[2]>30){Temp_DS1302_Time[2]=1;}//1-30
				}
				else if(Temp_DS1302_Time[1]==2)//ƽ��
				{
						if(Temp_DS1302_Time[0]%4==0&&Temp_DS1302_Time[0]%100!=0)//����
						{
							if(Temp_DS1302_Time[2]>29){Temp_DS1302_Time[2]=1;}
						}
						else if(Temp_DS1302_Time[0]%400==0)
						{
							if(Temp_DS1302_Time[2]>29){Temp_DS1302_Time[2]=1;}
						}
						else     //ƽ��
						{
							if(Temp_DS1302_Time[2]>28){Temp_DS1302_Time[2]=1;}
						}
				}
				Temp_DS1302_Time[6]++;
				if(Temp_DS1302_Time[6]>7){Temp_DS1302_Time[6]=1;}
			}
			if(key_value==7)//-1��
			{
				Temp_DS1302_Time[2]--;
				if( Temp_DS1302_Time[1]==1 || Temp_DS1302_Time[1]==3 || Temp_DS1302_Time[1]==5 || Temp_DS1302_Time[1]==7 || 
						Temp_DS1302_Time[1]==8 || Temp_DS1302_Time[1]==10 || Temp_DS1302_Time[1]==12)
				{
						if(Temp_DS1302_Time[2]<1){Temp_DS1302_Time[2]=31;}
						if(Temp_DS1302_Time[2]>31){Temp_DS1302_Time[2]=1;}
				}
				else if(Temp_DS1302_Time[1]==4 || Temp_DS1302_Time[1]==6 || Temp_DS1302_Time[1]==9 || Temp_DS1302_Time[1]==11)
				{
						if(Temp_DS1302_Time[2]<1){Temp_DS1302_Time[2]=30;}
						if(Temp_DS1302_Time[2]>30){Temp_DS1302_Time[2]=1;}
				}
				else if(Temp_DS1302_Time[1]==2)
				{
						if(Temp_DS1302_Time[0]%4==0&&Temp_DS1302_Time[0]%100!=0)
						{
							if(Temp_DS1302_Time[2]<1){Temp_DS1302_Time[2]=29;}
							if(Temp_DS1302_Time[2]>29){Temp_DS1302_Time[2]=1;}
						}
						else if(Temp_DS1302_Time[0]%400==0)
						{
							if(Temp_DS1302_Time[2]<1){Temp_DS1302_Time[2]=29;}
							if(Temp_DS1302_Time[2]>29){Temp_DS1302_Time[2]=1;}
						}
						else
						{
							if(Temp_DS1302_Time[2]<1){Temp_DS1302_Time[2]=28;}
							if(Temp_DS1302_Time[2]>28){Temp_DS1302_Time[2]=1;}
						}
				}
				Temp_DS1302_Time[6]--;
				if(Temp_DS1302_Time[6]==0){Temp_DS1302_Time[6]=7;}	
			}
 
			break;
			
			
		case 4://ʱ�޸�
			LCD_Display_String(1,1,"HourSet      ");
			LCD_WriteNum(2,1,2,0,Temp_DS1302_Time[3]);
			
			if(key_value==3)//+1ʱ
			{
				Temp_DS1302_Time[3]++;
				if(Temp_DS1302_Time[3]>23){Temp_DS1302_Time[3]=0;}//24����
			}
			if(key_value==7)//-1ʱ
			{
				Temp_DS1302_Time[3]--;
			if(Temp_DS1302_Time[3]<0){Temp_DS1302_Time[3]=23;}
			}
			break;
		case 5://���޸�
			LCD_Display_String(1,1,"MinuteSet  ");
			LCD_WriteNum(2,1,2,0,Temp_DS1302_Time[4]);
			
			if(key_value==3)//+1��
			{
				Temp_DS1302_Time[4]++;
				if(Temp_DS1302_Time[4]>59){Temp_DS1302_Time[4]=0;}//60����
			}
			if(key_value==7)//-1��
			{
				Temp_DS1302_Time[4]--;
				if(Temp_DS1302_Time[4]<0){Temp_DS1302_Time[4]=59;}
			}
			break;
		case 6://���޸�
			LCD_Display_String(1,1,"SecondSet     ");
			LCD_WriteNum(2,1,2,0,Temp_DS1302_Time[5]);
			
			if(key_value==3)//+1��
			{
				Temp_DS1302_Time[5]++;
				if(Temp_DS1302_Time[5]>59){Temp_DS1302_Time[5]=0;}//60����
			}
			if(key_value==7)//-1��
			{
				Temp_DS1302_Time[5]--;
				if(Temp_DS1302_Time[5]<0){Temp_DS1302_Time[5]=59;}
			}
			break;
		case 7://�����޸�
			LCD_Display_String(1,1,"DaySet          ");
			LCD_WriteNum(2,1,2,0,Temp_DS1302_Time[6]);	
			if(key_value==3)
			{
				Temp_DS1302_Time[6]++;
				if(Temp_DS1302_Time[6]>7){Temp_DS1302_Time[6]=1;}
			}
			if(key_value==7)
			{
				Temp_DS1302_Time[6]--;
				if(Temp_DS1302_Time[6]==0){Temp_DS1302_Time[6]=7;}	
			}
			break;
		case 15://�޸�ȷ��
			LCD_Init();
			DS1302_Time_Load();
			DS1302_Time_ReLoad();
			DS1302_ReSetTime();
			mode=0;
		break;
		case 19: // �������ý���
            LCD_Display_String(1, 1, "CLOCK SET");
						ClockDay_Show();
            LCD_WriteNum(2, 9, 2, 0, alarm_Time[0]);
            LCD_Display_Char(2, 11, ':');
            LCD_WriteNum(2, 12, 2, 0, alarm_Time[1]);
            LCD_Display_Char(2, 14, ':');
            LCD_WriteNum(2, 15, 2, 0, alarm_Time[2]);
            break;

    case 20: // ��������Сʱ
            LCD_Display_String(1, 1, "CLOCK_HourSet");
            LCD_WriteNum(2, 1, 2, 0, alarm_Time[0]);
            if (key_value == 3) { // +1 Сʱ
                alarm_Time[0] = (alarm_Time[0] + 1) % 24;
            }
            if (key_value == 7) { // -1 Сʱ
                alarm_Time[0] = (alarm_Time[0] == 0) ? 23 : alarm_Time[0] - 1;
            }
            break;
						
    case 21: // �������ӷ���
            LCD_Display_String(1, 1, "CLOCK_MinuteSet");
            LCD_WriteNum(2, 1, 2, 0, alarm_Time[1]);
            if (key_value == 3) { // +1 ����
                alarm_Time[1] = (alarm_Time[1] + 1) % 60;
            }
            if (key_value == 7) { // -1 ����
                alarm_Time[1] = (alarm_Time[1] == 0) ? 59 : alarm_Time[1] - 1;
            }
            break;

    case 22: // ������������
            LCD_Display_String(1, 1, "CLOCK_SecondSet");
            LCD_WriteNum(2, 1, 2, 0, alarm_Time[2]);
            if (key_value == 3) { // +1 ��
                alarm_Time[2] = (alarm_Time[2] + 1) % 60;
            }
            if (key_value == 7) { // -1 ��
                alarm_Time[2] = (alarm_Time[2] == 0) ? 59 : alarm_Time[2] - 1;
            }
            break;
		case 23: // �������ӹ���״̬
           LCD_Display_String(1,1,"CLOCK_WorkSet");
					 LCD_WriteNum(2,1,2,0,alarm_Time[3]);	
			     if(key_value==3)
			     {
								alarm_Time[3]++;
				   if(alarm_Time[3]>1){alarm_Time[3]=0;}
			     }
			     if(key_value==7)
			     {
								alarm_Time[3]--;
				   if(alarm_Time[3]==-1){alarm_Time[3]=1;}
			     }
			     break;
	}
	key_value = 0xff;
}

void Timer0_Isr(void) interrupt 1
{	
	static unsigned char icount = 0;		// ��ʱ��������
	if(icount==10)
	{
		key_flag = 1;
		icount=0;
	}
	icount++;
}

 
void Timer0_Init(void)		//1����@11.0592MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x20;				//���ö�ʱ��ʼֵ
	TH0 = 0xD1;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
	EA=1;
}
void main(void)
{
	cls_buzz();
	DS1302_Init();
	LCD_Init();
	Timer0_Init();					    
	DS1302_SetTime();
	LED(0xff);//��LED
	while(1)
	{
		alarm();
		if(key_flag)
    {
      key_flag = 0;
			read_keyboard();
			if(key_value != 0xFF)
			{
			LCD_Init();
			KeyAction();
			}
		} 
		Disply();
	}
}