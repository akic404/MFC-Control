//-----------------------------------------------------------------
// DAC8563����ͷ�ļ�
// ͷ�ļ���: DAC8563.h
// ��    ��: ���ǵ���
// ��дʱ��: 2020-09-29
// �޸�����: 2020-09-29
// ��ǰ�汾: V1.0.1 
// ��ʷ�汾:
//-----------------------------------------------------------------
#ifndef _DAC8563_H_
#define _DAC8563_H_
#include "stm32f10x.h"

extern int16_t ZeroCode_Error;

//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
#define DAC8563_SYNC_L      GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define DAC8563_SYNC_H     	GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define DAC8563_SCLK_L     	GPIO_ResetBits(GPIOB, GPIO_Pin_13)
#define DAC8563_SCLK_H     	GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define DAC8563_DIN_L      	GPIO_ResetBits(GPIOB, GPIO_Pin_15)
#define DAC8563_DIN_H     	GPIO_SetBits(GPIOB, GPIO_Pin_15)

//-----------------------------------------------------------------
// �ⲿ��������
//-----------------------------------------------------------------
extern void DAC8563_GPIO_Init(void);
extern void DAC8563_Write_Reg(uint32_t data);
extern void DAC8563_Write_CHA(uint16_t data);
extern void DAC8563_Write_CHB(uint16_t data);
extern void DAC8563_Write_CHA_CHB(uint16_t data);

#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
