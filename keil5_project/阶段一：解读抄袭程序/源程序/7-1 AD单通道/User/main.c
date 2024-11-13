#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADValue;
u16 i;
float Voltage = 0;
float ave = 0;

float D_float;
u16	 D_u16;





for(i=0;i<50;i++){
	ADValue = AD_GetValue();
	Voltage += (float)ADValue / 4095 * 3.3;
	}
	ave = Voltage/50;
	ave = 0;
	ADValue = 0;
	Voltage = 0;
int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "ADValue:");
	OLED_ShowString(2, 1, "Volatge:0.00V");
	
	while (1)
	{
		ADValue = AD_GetValue();
		Voltage = (float)ADValue / 4095 * 3.3;
		D_float = (Voltage+10000)/20000*65535;
		D_u16 = (u16)D_float;
		
		OLED_ShowNum(1, 9, ADValue, 4);
		OLED_ShowNum(2, 9, Voltage, 1);
		OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 2);
		
		Delay_ms(100);
	}
}
