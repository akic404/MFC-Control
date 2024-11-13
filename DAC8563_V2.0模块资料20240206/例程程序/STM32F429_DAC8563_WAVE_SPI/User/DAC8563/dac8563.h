//-----------------------------------------------------------------
// 程序描述:
// 		 DAC8563驱动头文件
// 作    者: 凌智电子
// 开始日期: 2022-06-27
// 完成日期: 2022-06-27
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0: DAC8563驱动头文件
// 调试工具: 凌智STM32F429+CycloneIV电子系统设计开发板、LZE_ST_LINK2、DAC8563模块
// 说    明: 
//    
//-----------------------------------------------------------------
#ifndef _DAC8563_H_
#define _DAC8563_H_
#include "stm32f429_winner.h"

extern int16_t ZeroCode_Error;	

//-----------------------------------------------------------------
// 引脚声明
//-----------------------------------------------------------------
#define DAC8563_SYNC_L      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET)
#define DAC8563_SYNC_H     	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET)

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern void DAC8563_Init(void);
extern void DAC8563_Write_Reg(uint8_t cmd, uint16_t data);
extern void DAC8563_Write_CHA(uint16_t data);
extern void DAC8563_Write_CHB(uint16_t data);
extern void DAC8563_Write_CHA_CHB(uint16_t data);

#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
