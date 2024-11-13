//-----------------------------------------------------------------
// 程序描述:
//     DAC8563测试程序
// 作    者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0: DAC8563测试实验
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说    明: DAC8563模块的LDAC引脚和CLR引脚不用接
//		   STM32H750					DAC8563模块
//				 +5V			->				+5V
//				 GND			->				GND
//				 SYNC			->				PB12
//				 SCLK			->				PB13
//				 DIN			->				PB15
//    
//-----------------------------------------------------------------

#define ChipError			-36	// 误差

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "system.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "dac8563.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
int main(void)
{
	u8 but[16];
	u16 key;
	u32 D_Data;
	float V_A=0;
	float V_B=0;
  HAL_Init();          		// 初始化HAL库
	MPU_Memory_Protection();// 设置保护区域
	SystemClock_Config(); 	// 设置系统时钟,400Mhz  
	SysTick_clkconfig(400);	// SysTick参数配置
	KEY_Init();							// 初始化按键
	LCD_Init();             // 初始化LCD
	DAC8563_Init();					// DAC8563引脚初始化
	
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
