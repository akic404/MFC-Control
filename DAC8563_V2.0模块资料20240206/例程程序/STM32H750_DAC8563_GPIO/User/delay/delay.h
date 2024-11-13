//-----------------------------------------------------------------
// 程序描述:
//    	延时程序头文件
// 作    者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 当前版本: V1.0
// 历史版本:
//   - V1.0: 基于STM32的延时：us,ms
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说    明: 
//
//-----------------------------------------------------------------
#ifndef _DELAY_H
#define _DELAY_H
#include "system.h"

//-----------------------------------------------------------------
// 函数声明
//-----------------------------------------------------------------
extern void SysTick_clkconfig(u16 SYSCLK);
extern void delay_us(u32 nus);
extern void delay_ms(u16 nms);
#endif
//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
