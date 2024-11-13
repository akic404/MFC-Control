//-----------------------------------------------------------------
// 程序描述:
//     DAC8563驱动程序
// 作    者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0:  DAC8563驱动程序
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说    明: 
//    
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "dac8563.h"
#include "delay.h"

SPI_HandleTypeDef SPI2_Handler;  	// SPI句柄
//-----------------------------------------------------------------
// void DAC8563_Init(void)
//-----------------------------------------------------------------
//
// 函数功能: DAC8563初始化
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无

//-----------------------------------------------------------------
void DAC8563_Init(void)
{
  SPI2_Handler.Instance = SPI2;
  SPI2_Handler.Init.Mode = SPI_MODE_MASTER;
  SPI2_Handler.Init.Direction = SPI_DIRECTION_2LINES;
  SPI2_Handler.Init.DataSize = SPI_DATASIZE_24BIT;
  SPI2_Handler.Init.CLKPolarity = SPI_POLARITY_HIGH;
  SPI2_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;
  SPI2_Handler.Init.NSS = SPI_NSS_HARD_OUTPUT;
  SPI2_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  SPI2_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;
  SPI2_Handler.Init.TIMode = SPI_TIMODE_DISABLE;
  SPI2_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  SPI2_Handler.Init.CRCPolynomial = 0x0;
  SPI2_Handler.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  SPI2_Handler.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  SPI2_Handler.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  SPI2_Handler.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  SPI2_Handler.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  SPI2_Handler.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  SPI2_Handler.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  SPI2_Handler.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  SPI2_Handler.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;
  SPI2_Handler.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	HAL_SPI_Init(&SPI2_Handler);
	__HAL_SPI_ENABLE(&SPI2_Handler);

	// DAC-A和DAC-B上电
	DAC8563_Write_Reg((4 << 19) | (0 << 16) | (3 << 0));
	// LDAC引脚不使用
	DAC8563_Write_Reg((6 << 19) | (0 << 16) | (3 << 0));
	// DAC通道增益为2
  DAC8563_Write_Reg((7 << 19) | (0 << 16) | (1 << 0));
}

//-----------------------------------------------------------------
// void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//-----------------------------------------------------------------
// 
// 函数功能: SPI底层驱动，时钟使能，引脚配置
// 入口参数: SPI_HandleTypeDef *hspi：SPI句柄
// 返 回 值: 无
// 注意事项: 此函数会被HAL_SPI_Init()调用
//
//-----------------------------------------------------------------
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef GPIO_Initure;
	RCC_PeriphCLKInitTypeDef SPI2ClkInit;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();       // 使能GPIOB时钟
	__HAL_RCC_SPI2_CLK_ENABLE();        // 使能SPI2时钟
	
	// 设置SPI2的时钟源 
	SPI2ClkInit.PeriphClockSelection=RCC_PERIPHCLK_SPI2;	    // 设置SPI2时钟源
	SPI2ClkInit.Spi123ClockSelection=RCC_SPI123CLKSOURCE_PLL;	// SPI2时钟源使用PLL1Q
	HAL_RCCEx_PeriphCLKConfig(&SPI2ClkInit);
	
	GPIO_Initure.Pin= GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;      // 复用推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          // 上拉
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH; // 低速       
	GPIO_Initure.Alternate=GPIO_AF5_SPI2;   // 复用为SPI2
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);			// 初始化	
}

//-----------------------------------------------------------------
// void SPI2_Send_Data(uint32_t dat)
//-----------------------------------------------------------------
// 
// 函数功能: SPI2发送1个字节数据
// 入口参数: u8 dat： 待发送的数据
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void SPI2_Send_Data(uint32_t dat)
{
	uint32_t RxDat;
	HAL_SPI_TransmitReceive(&SPI2_Handler,(uint8_t *)&dat,(uint8_t *)&RxDat,1,1000);
}

//-----------------------------------------------------------------
// void DAC8563_Write_Reg(uint32_t data)
//-----------------------------------------------------------------
//
// 函数功能: DAC8563写数据
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无

//-----------------------------------------------------------------
void DAC8563_Write_Reg(uint32_t data)
{
	SPI2_Send_Data(data);
}

//-----------------------------------------------------------------
// void DAC8563_Write_CHA(uint16_t data)
//-----------------------------------------------------------------
//
// 函数功能: DAC8563通道A数据更新
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无
//
//-----------------------------------------------------------------
void DAC8563_Write_CHA(uint16_t data)
{
  DAC8563_Write_Reg(0x180000|data);
}

//-----------------------------------------------------------------
// void DAC8563_Write_CHB(uint16_t data)
//-----------------------------------------------------------------
//
// 函数功能: DAC8563通道B数据更新
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无
//
//-----------------------------------------------------------------
void DAC8563_Write_CHB(uint16_t data)
{
	DAC8563_Write_Reg(0x190000|data);
}

//-----------------------------------------------------------------
// void DAC8563_Write_CHA_CHB(uint16_t data)
//-----------------------------------------------------------------
//
// 函数功能: DAC8563通道A通道B数据更新
// 入口参数: 无
// 返回参数: 无
// 全局变量: 无
//
//-----------------------------------------------------------------
void DAC8563_Write_CHA_CHB(uint16_t data)
{
	DAC8563_Write_Reg(0x1F0000|data);
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
