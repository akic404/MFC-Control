//-----------------------------------------------------------------
// ��������:
// 		 DAC8563����ͷ�ļ�
// ��    ��: ���ǵ���
// ��ʼ����: 2020-11-11
// �������: 2020-11-11
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0: DAC8563����ͷ�ļ�
// ���Թ���: ����STM32H750���İ塢LZE_ST_LINK2
// ˵    ��: 
//    
//-----------------------------------------------------------------
#ifndef _DAC8563_H_
#define _DAC8563_H_
#include "system.h"

//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
#define DAC8563_SYNC_L      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)
#define DAC8563_SYNC_H     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)
#define DAC8563_SCLK_L     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)
#define DAC8563_SCLK_H     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)
#define DAC8563_DIN_L      	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET)
#define DAC8563_DIN_H     	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET)

//-----------------------------------------------------------------
// �ⲿ��������
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
