//-----------------------------------------------------------------
// 程序描述:
// 		 DAC8563驱动头文件
// 作    者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0: DAC8563驱动头文件
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说    明: 
//    
//-----------------------------------------------------------------
#ifndef _DAC8563_H_
#define _DAC8563_H_
#include "system.h"

//-----------------------------------------------------------------
// 引脚声明
//-----------------------------------------------------------------
#define DAC8563_SYNC_L      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)
#define DAC8563_SYNC_H     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)
#define DAC8563_SCLK_L     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)
#define DAC8563_SCLK_H     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)
#define DAC8563_DIN_L      	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET)
#define DAC8563_DIN_H     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET)

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern void DAC8563_Init(void);
extern void SPI_Send_Data(uint32_t dat);
extern void DAC8563_Write_Reg(uint32_t data);
extern void DAC8563_Write_CHA(uint16_t data);
extern void DAC8563_Write_CHB(uint16_t data);
extern void DAC8563_Write_CHA_CHB(uint16_t data);

#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
