//-----------------------------------------------------------------
// ��������:
//     LED��ʾ��������
// ��    ��: ���ǵ���
// ��ʼ����: 2014-01-28
// �������: 2014-01-28
// �޸�����: 2014-02-16
// ��ǰ�汾: V1.0.1
// ��ʷ�汾:
//  - V1.0: (2014-02-07)LED IO ����
// - V1.0.1:(2014-02-16)ͷ�ļ��в���������ͷ�ļ�
// ���Թ���: ����STM32���Ŀ����塢LZE_ST_LINK2
// ˵    ��:
//
//-----------------------------------------------------------------
//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include <stm32f10x.h>

#include "spi.h"

//-----------------------------------------------------------------
// void SPI2_Init(void)
//-----------------------------------------------------------------
//
// ��������: SPI�ڳ�ʼ��
// ��ڲ���: ��
// �� �� ֵ: ��
// ȫ�ֱ���: ��
// ����ģ��: RCC_APB2PeriphClockCmd();GPIO_Init();
// ע������: ��
//
//-----------------------------------------------------------------
void SPI2_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  // ����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;												// ����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;										// ����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;													// ����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;												// ����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;														// NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; // ���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ32
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;									// ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;														// CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);  																// ����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI2, ENABLE); 		// ʹ��SPI����
	SPI2_ReadWriteByte(0xff);	// ��������		 
}   

void SPI2_SetSpeed(uint8_t SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI2,ENABLE); 

} 

//-----------------------------------------------------------------
// uint8_t SPI2_ReadWriteByte(uint8_t TxData)
//-----------------------------------------------------------------
//
// ��������: SPI��дһ���ֽ�
// ��ڲ���: TxData�����͵��ֽ�
// �� �� ֵ: ��ȡ���ֽ�
// ȫ�ֱ���: ��
// ע������: ��
//
//-----------------------------------------------------------------
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) 	// ���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)
			return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData); 	// ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) // ���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)
			return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2);	// ����ͨ��SPIx������յ�����					    
}

//-----------------------------------------------------------------
// uint8_t SPI2_WriteByte(uint8_t TxData)
//-----------------------------------------------------------------
//
// ��������: SPI�ڳ�ʼ��
// ��ڲ���: TxData�����͵��ֽ�
// �� �� ֵ: ����״̬��1������ʧ��  0�����ͳɹ�
// ȫ�ֱ���: ��
// ע������: ��
//
//-----------------------------------------------------------------
uint8_t SPI2_WriteByte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) 	// ���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)
			return 1;
	}			  
	SPI_I2S_SendData(SPI2, TxData); // ͨ������SPIx����һ������   
	return 0;
}

//-----------------------------------------------------------------
// uint8_t SPI2_ReadByte(void)
//-----------------------------------------------------------------
//
// ��������: SPI��дһ������
// ��ڲ���: ��
// �� �� ֵ: ��ȡ���ֽ�
// ȫ�ֱ���: ��
// ע������: ��
//
//-----------------------------------------------------------------
uint8_t SPI2_ReadByte(void)
{		
	uint8_t retry=0;				 	

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) // ���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)
			return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); // ����ͨ��SPIx������յ�����					    
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
