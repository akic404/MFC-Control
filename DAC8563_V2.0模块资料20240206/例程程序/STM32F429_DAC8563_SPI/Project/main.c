//-----------------------------------------------------------------
// 程序描述:
//     DAC8563实验
// 作    者: 凌智电子
// 开始日期: 2022-06-27
// 完成日期: 2022-06-27
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0: (2022-06-27)	DAC8563实验
// 调试工具: 凌智STM32F429+CycloneIV电子系统设计开发板、LZE_ST_LINK2、4.3寸/2.8寸 TFT液晶屏、DAC8563模块
// 说    明: 硬件连接(DAC8563模块的LDAC引脚和CLR引脚不用接)
//		   STM32F429					DAC8563模块
//				 +5V			->				+5V
//				 GND			->				GND
//				 SYNC			->				PC4
//				 SCLK			->				PF7
//				 DIN			->				PF9
//    
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "stm32f429_winner.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "sdram.h"
#include "usart.h"
#include "spi.h"	
#include "dac8563.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
int main(void)
{
	uint8_t  but[16];
	uint16_t key;
	u32 D_Data;
	float V_A=0;
	float V_B=0;
  HAL_Init();          							// 初始化HAL库
	SystemClock_Config(360,25,2,8); 	// 设置系统时钟,180Mhz  
	LED_Init();                  			// 初始化LED 
	KEY_Init();												// 按键初始化
	uart_init(115200);								// 初始化串口
	SDRAM_Init();                			// SDRAM初始化
	LCD_Init();                  			// LCD初始化
	DAC8563_Init();					// DAC8563引脚初始化
	
	DAC8563_Write_CHA((int32_t)((V_A+10000-ZeroCode_Error)/20000*65535));
	DAC8563_Write_CHB((int32_t)((V_B+10000-ZeroCode_Error)/20000*65535));
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
			LCD_ShowString(170, 60, 320,16,16,(char *)but);
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
			LCD_ShowString(170, 80, 320,16,16,(char *)but);
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
			LCD_ShowString(170, 80, 320,16,16,(char *)but);
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
