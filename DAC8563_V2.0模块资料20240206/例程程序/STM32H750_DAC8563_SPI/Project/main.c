//-----------------------------------------------------------------
// ��������:
//     DAC8563���Գ���
// ��    ��: ���ǵ���
// ��ʼ����: 2020-11-11
// �������: 2020-11-11
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0: DAC8563����ʵ��
// ���Թ���: ����STM32H750���İ塢LZE_ST_LINK2
// ˵    ��: DAC8563ģ���LDAC���ź�CLR���Ų��ý�
//		   STM32H750					DAC8563ģ��
//				 +5V			->				+5V
//				 GND			->				GND
//				 SYNC			->				PB12
//				 SCLK			->				PB13
//				 DIN			->				PB15
//    
//-----------------------------------------------------------------

#define ChipError			-36	// ���

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include "system.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "dac8563.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
int main(void)
{
	u8 but[16];
	u16 key;
	u32 D_Data;
	float V_A=0;
	float V_B=0;
  HAL_Init();          		// ��ʼ��HAL��
	MPU_Memory_Protection();// ���ñ�������
	SystemClock_Config(); 	// ����ϵͳʱ��,400Mhz  
	SysTick_clkconfig(400);	// SysTick��������
	KEY_Init();							// ��ʼ������
	LCD_Init();             // ��ʼ��LCD
	DAC8563_Init();					// DAC8563���ų�ʼ��
	
	DAC8563_Write_CHA((int32_t)((V_A+10000-ChipError)/20000*65535));
	DAC8563_Write_CHB((int32_t)((V_B+10000-ChipError)/20000*65535));
	POINT_COLOR=BLUE; 
	LCD_ShowString(70,10,320,16,16,"DAC8563 Test Experiment");
	POINT_COLOR=BLACK; 
	LCD_ShowString(70,60,320,16,16,"CHA Voltage:          ");
	LCD_ShowString(70,80,320,16,16,"CHB Voltage:          ");
	sprintf((char *)but,"%9.3fmV",V_A);
	LCD_ShowString(170,60,320,16,16,(char *)but);
	sprintf((char *)but,"%9.3fmV",V_B);
	LCD_ShowString(170,80,320,16,16,(char *)but);
	POINT_COLOR=RED; 
	LCD_ShowString(50,120,320,16,16,"K1: CHA+100mV  K2: CHA-100mV");
	LCD_ShowString(50,140,320,16,16,"K3: CHB+100mV  K4: CHB-100mV");
	POINT_COLOR=BLACK; 
	while(1)
	{	
		key=KEY_Scan(0);
		if(key==1)
		{
			V_A+=100;
			if(V_A>10000)
				V_A=10000;
			sprintf((char *)but,"%9.3fmV",V_A);
			LCD_ShowString(170, 60, 320,16,16,(char *)but);
			if(V_A+10000-ChipError > 20000)
				D_Data = 65535;
			else if(V_A+10000-ChipError < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_A+10000-ChipError)/20000*65535);
			DAC8563_Write_CHA((uint16_t)D_Data);
		}
		else if(key==2)
		{
			V_A-=100;
			if(V_A<-10000)
				V_A=-10000;
			sprintf((char *)but,"%9.3fmV",V_A);
			LCD_ShowString(170, 60, 320,16,16,(char *)but);
			if(V_A+10000-ChipError > 20000)
				D_Data = 65535;
			else if(V_A+10000-ChipError < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_A+10000-ChipError)/20000*65535);
			DAC8563_Write_CHA((uint16_t)D_Data);
		}
		else if(key==3)
		{
			V_B+=100;
			if(V_B>10000)
				V_B=10000;
			sprintf((char *)but,"%9.3fmV",V_B);
			LCD_ShowString(170, 80, 320,16,16,(char *)but);
			if(V_B+10000-ChipError > 20000)
				D_Data = 65535;
			else if(V_B+10000-ChipError < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_B+10000-ChipError)/20000*65535);
			DAC8563_Write_CHB((uint16_t)D_Data);
		}
		else if(key==4)
		{
			V_B-=100;
			if(V_B<-10000)
				V_B=-10000;
			sprintf((char *)but,"%9.3fmV",V_B);
			LCD_ShowString(170, 80, 320,16,16,(char *)but);
			if(V_B+10000-ChipError > 20000)
				D_Data = 65535;
			else if(V_B+10000-ChipError < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_B+10000-ChipError)/20000*65535);
			DAC8563_Write_CHB((uint16_t)D_Data);
		}
	}
}

//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
