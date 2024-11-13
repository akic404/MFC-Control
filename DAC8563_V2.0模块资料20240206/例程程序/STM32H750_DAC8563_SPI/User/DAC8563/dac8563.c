//-----------------------------------------------------------------
// ��������:
//     DAC8563��������
// ��    ��: ���ǵ���
// ��ʼ����: 2020-11-11
// �������: 2020-11-11
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0:  DAC8563��������
// ���Թ���: ����STM32H750���İ塢LZE_ST_LINK2
// ˵    ��: 
//    
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include "dac8563.h"
#include "delay.h"

SPI_HandleTypeDef SPI2_Handler;  	// SPI���
//-----------------------------------------------------------------
// void DAC8563_Init(void)
//-----------------------------------------------------------------
//
// ��������: DAC8563��ʼ��
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��

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

	// DAC-A��DAC-B�ϵ�
	DAC8563_Write_Reg((4 << 19) | (0 << 16) | (3 << 0));
	// LDAC���Ų�ʹ��
	DAC8563_Write_Reg((6 << 19) | (0 << 16) | (3 << 0));
	// DACͨ������Ϊ2
  DAC8563_Write_Reg((7 << 19) | (0 << 16) | (1 << 0));
}

//-----------------------------------------------------------------
// void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//-----------------------------------------------------------------
// 
// ��������: SPI�ײ�������ʱ��ʹ�ܣ���������
// ��ڲ���: SPI_HandleTypeDef *hspi��SPI���
// �� �� ֵ: ��
// ע������: �˺����ᱻHAL_SPI_Init()����
//
//-----------------------------------------------------------------
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef GPIO_Initure;
	RCC_PeriphCLKInitTypeDef SPI2ClkInit;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();       // ʹ��GPIOBʱ��
	__HAL_RCC_SPI2_CLK_ENABLE();        // ʹ��SPI2ʱ��
	
	// ����SPI2��ʱ��Դ 
	SPI2ClkInit.PeriphClockSelection=RCC_PERIPHCLK_SPI2;	    // ����SPI2ʱ��Դ
	SPI2ClkInit.Spi123ClockSelection=RCC_SPI123CLKSOURCE_PLL;	// SPI2ʱ��Դʹ��PLL1Q
	HAL_RCCEx_PeriphCLKConfig(&SPI2ClkInit);
	
	GPIO_Initure.Pin= GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;      // �����������
	GPIO_Initure.Pull=GPIO_PULLUP;          // ����
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH; // ����       
	GPIO_Initure.Alternate=GPIO_AF5_SPI2;   // ����ΪSPI2
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);			// ��ʼ��	
}

//-----------------------------------------------------------------
// void SPI2_Send_Data(uint32_t dat)
//-----------------------------------------------------------------
// 
// ��������: SPI2����1���ֽ�����
// ��ڲ���: u8 dat�� �����͵�����
// �� �� ֵ: ��
// ע������: ��
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
// ��������: DAC8563д����
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��

//-----------------------------------------------------------------
void DAC8563_Write_Reg(uint32_t data)
{
	SPI2_Send_Data(data);
}

//-----------------------------------------------------------------
// void DAC8563_Write_CHA(uint16_t data)
//-----------------------------------------------------------------
//
// ��������: DAC8563ͨ��A���ݸ���
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��
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
// ��������: DAC8563ͨ��B���ݸ���
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��
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
// ��������: DAC8563ͨ��Aͨ��B���ݸ���
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��
//
//-----------------------------------------------------------------
void DAC8563_Write_CHA_CHB(uint16_t data)
{
	DAC8563_Write_Reg(0x1F0000|data);
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
