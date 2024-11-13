//-----------------------------------------------------------------
// ��������:
// ����DAC8563���Գ���
// ��������: ���ǵ���
// ��ʼ����: 2020-09-29
// �������: 2020-09-29
// �޸�����: 2020-09-29
// ��ǰ�汾: V1.0
// ��ʷ�汾:
// ��- V1.0: DAC8563����ʵ��
// ���Թ���: ����STM3���Ŀ����塢LZE_ST_LINK2��2.8��Һ������DAC8563ģ��
// ˵������: �ӿ�˵��(DAC8563ģ���LDAC���ź�CLR���Ų��ý�)
//				���İ�						DAC8563ģ��
//				 +5V			->				+5V
//				 GND			->				GND
//				 SYNC			->				PB12
//				 SCLK			->				PB13
//				 DIN			->				PB15
//				
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include <stm32f10x.h>
#include "Delay.h"
#include "key.h"
#include "lze_lcd.h"
#include "dac8563.h"
#include "PeripheralInit.h"

//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
int main(void)
{
	uint8_t  but[16];
	uint16_t key;
	u32 D_Data;
	float V_A=0;
	float V_B=0;
	PeripheralInit();	
	DAC8563_Write_CHA((int32_t)((V_A+10000-ZeroCode_Error)/20000*65535));
	DAC8563_Write_CHB((int32_t)((V_B+10000-ZeroCode_Error)/20000*65535));
	LCD_Clear(LCD_COLOR_WHITE);
	LCD_WriteString(70, 10, LCD_COLOR_BLUE, LCD_COLOR_WHITE, (uint8_t *)"DAC8563 Test Experiment");
	LCD_WriteString(70, 60, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)"CHA Voltage:          ");
	LCD_WriteString(70, 80, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)"CHB Voltage:          ");
	sprintf((char *)but,"%9.3fmV",V_A);
	LCD_WriteString(170, 60, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)but);
	sprintf((char *)but,"%9.3fmV",V_B);
	LCD_WriteString(170, 80, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)but);
	LCD_WriteString(50, 120, LCD_COLOR_RED, LCD_COLOR_WHITE, (uint8_t *)"K1: CHA+100mV  K2: CHA-100mV");
	LCD_WriteString(50, 140, LCD_COLOR_RED, LCD_COLOR_WHITE, (uint8_t *)"K3: CHB+100mV  K4: CHB-100mV");
  while (1)
	{
		key=Key_Scan();
		if(key==1)
		{
			V_A+=100;
			if(V_A>10000)
				V_A=10000;
			sprintf((char *)but,"%9.3fmV",V_A);
			LCD_WriteString(170, 60, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)but);
			if(V_A+10000-ZeroCode_Error > 20000)
				D_Data = 65535;
			else if(V_A+10000-ZeroCode_Error < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_A+10000-ZeroCode_Error)/20000*65535);
			DAC8563_Write_CHA((uint16_t)D_Data);
		}
		else if(key==2)
		{
			V_A-=100;
			if(V_A<-10000)
				V_A=-10000;
			sprintf((char *)but,"%9.3fmV",V_A);
			LCD_WriteString(170, 60, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)but);
			if(V_A+10000-ZeroCode_Error > 20000)
				D_Data = 65535;
			else if(V_A+10000-ZeroCode_Error < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_A+10000-ZeroCode_Error)/20000*65535);
			DAC8563_Write_CHA((uint16_t)D_Data);
		}
		else if(key==3)
		{
			V_B+=100;
			if(V_B>10000)
				V_B=10000;
			sprintf((char *)but,"%9.3fmV",V_B);
			LCD_WriteString(170, 80, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)but);
			if(V_B+10000-ZeroCode_Error > 20000)
				D_Data = 65535;
			else if(V_B+10000-ZeroCode_Error < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_B+10000-ZeroCode_Error)/20000*65535);
			DAC8563_Write_CHB((uint16_t)D_Data);
		}
		else if(key==4)
		{
			V_B-=100;
			if(V_B<-10000)
				V_B=-10000;
			sprintf((char *)but,"%9.3fmV",V_B);
			LCD_WriteString(170, 80, LCD_COLOR_BLACK, LCD_COLOR_WHITE, (uint8_t *)but);
			if(V_B+10000-ZeroCode_Error > 20000)
				D_Data = 65535;
			else if(V_B+10000-ZeroCode_Error < 0)
				D_Data = 0;
			else
				D_Data = (uint32_t)((V_B+10000-ZeroCode_Error)/20000*65535);
			DAC8563_Write_CHB((uint16_t)D_Data);
		}
	}
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
