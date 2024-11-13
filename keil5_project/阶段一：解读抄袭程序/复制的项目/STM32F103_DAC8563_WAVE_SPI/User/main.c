//-----------------------------------------------------------------
// 程序描述:
// 　　DAC8563测试程序
// 作　　者: 凌智电子
// 开始日期: 2020-09-29
// 完成日期: 2020-09-29
// 修改日期: 2020-09-29
// 当前版本: V1.0
// 历史版本:
// 　- V1.0: DAC8563测试实验
// 调试工具: 凌智STM3核心开发板、LZE_ST_LINK2、2.8寸液晶屏、DAC8563模块
// 说　　明: 接口说明(DAC8563模块的LDAC引脚和CLR引脚不用接)
//				核心板						DAC8563模块
//				 +5V			->				+5V
//				 GND			->				GND
//				 SYNC			->				PB12
//				 SCLK			->				PB13
//				 DIN			->				PB15
//				
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include <stm32f10x.h>
#include "Delay.h"
#include "key.h"
#include "lze_lcd.h"
#include "dac8563.h"
#include "PeripheralInit.h"
#include "AD.h"



//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
int main(void)
{	
	u16 i;
	PeripheralInit();	
	float D_floatA,D_floatB;
	u16	 D_u16A,D_u16B;
	
	uint16_t ADValue;
	float Voltage = 0;
	float ave = 0;
	
	
	for(i=0;i<50;i++){
		ADValue = AD_GetValue();
		Voltage += (float)ADValue / 4095 * 3.3;
		}
		ave = Voltage/50;
		//ave = 0;
		ADValue = 0;
		Voltage = 0;
  while (1)
	{	
		/*
		for(i=0;i<256;i++)
		{
			DAC8563_Write_CHA_CHB(sin_data[i]/2 + 0x3FFF);
			
		}
		*/
		ADValue = AD_GetValue();
		Voltage = ((float)ADValue/ 4095 * 3.3-ave)*5;
		
		D_floatA = (Voltage/0.001+10000)/20000*65535;
		D_u16A = (u16)D_floatA;
		
		D_floatB = (-Voltage/0.001+10000)/20000*65535;
		D_u16B = (u16)D_floatB;
		
		
		DAC8563_Write_CHA(D_u16A);
		DAC8563_Write_CHB(D_u16B);
	}
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
