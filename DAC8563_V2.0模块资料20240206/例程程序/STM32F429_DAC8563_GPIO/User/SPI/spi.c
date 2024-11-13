//-----------------------------------------------------------------
// ��������:
//     SPI��������
// ��    ��: ���ǵ���
// ��ʼ����: 2018-08-04
// �������: 2018-08-04
// �޸�����:
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0: (2018-08-04)SPI����
// ���Թ���: ����STM32F429+CycloneIV����ϵͳ��ƿ����塢LZE_ST_LINK2
// ˵    ��:
//
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include "spi.h"

//-----------------------------------------------------------------
SPI_HandleTypeDef SPI5_Handler; // SPI���
//-----------------------------------------------------------------
// void SPI5_Init(void)
//-----------------------------------------------------------------
//
// ��������: SPI5�����������ó�����ģʽ
// ��ڲ���: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void SPI5_Init(void)
{
  SPI5_Handler.Instance               = SPI5;                     // SP5
  SPI5_Handler.Init.Mode              = SPI_MODE_MASTER;          // ����SPI����ģʽ������Ϊ��ģʽ
  SPI5_Handler.Init.Direction         = SPI_DIRECTION_2LINES;     // ����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
  SPI5_Handler.Init.DataSize          = SPI_DATASIZE_8BIT;        // ����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
  SPI5_Handler.Init.CLKPolarity       = SPI_POLARITY_LOW;         // ����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
  SPI5_Handler.Init.CLKPhase          = SPI_PHASE_2EDGE;          // ����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
  SPI5_Handler.Init.NSS               = SPI_NSS_SOFT;             // NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
  SPI5_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; // ���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ32
  SPI5_Handler.Init.FirstBit          = SPI_FIRSTBIT_MSB;         // ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
  SPI5_Handler.Init.CRCPolynomial     = 0;                        // CRCֵ����Ķ���ʽ
  HAL_SPI_Init(&SPI5_Handler);                                    // ��ʼ��
  __HAL_SPI_ENABLE(&SPI5_Handler);                                // ʹ��SPI5
}

//-----------------------------------------------------------------
// void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//-----------------------------------------------------------------
//
// ��������: SPI5�ײ�������ʱ��ʹ�ܣ���������
// ��ڲ���: SPI_HandleTypeDef *hspi��SPI���
// �� �� ֵ: ��
// ע������: �˺����ᱻHAL_SPI_Init()����
//
//-----------------------------------------------------------------
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef GPIO_Initure;

  __HAL_RCC_GPIOF_CLK_ENABLE(); // ʹ��GPIOFʱ��
  __HAL_RCC_SPI5_CLK_ENABLE();  // ʹ��SPI5ʱ��

  GPIO_Initure.Pin       = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_Initure.Mode      = GPIO_MODE_AF_PP;   // �����������
  GPIO_Initure.Pull      = GPIO_PULLUP;       // ����
  GPIO_Initure.Speed     = GPIO_SPEED_LOW;   // ����
  GPIO_Initure.Alternate = GPIO_AF5_SPI5; 		// ����ΪSPI5
  HAL_GPIO_Init(GPIOF, &GPIO_Initure);    		// ��ʼ��
}

//-----------------------------------------------------------------
// void SPI5_SetSpeed(u8 SPI_BaudRatePrescaler)
//-----------------------------------------------------------------
//
// ��������: SPI�ٶ����ú���
// ��ڲ���: u8 SPI_BaudRatePrescaler��SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
// �� �� ֵ: ��
// ע������: SPI�ٶ�=fAPB1/��Ƶϵ����fAPB1ʱ��һ��Ϊ45Mhz
//
//-----------------------------------------------------------------
void SPI5_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler)); // �ж���Ч��
  __HAL_SPI_DISABLE(&SPI5_Handler);                               // �ر�SPI
  SPI5_Handler.Instance->CR1 &= 0XFFC7;                           // λ3-5���㣬�������ò�����
  SPI5_Handler.Instance->CR1 |= SPI_BaudRatePrescaler;            // ����SPI�ٶ�
  __HAL_SPI_ENABLE(&SPI5_Handler);                                // ʹ��SPI
}

//-----------------------------------------------------------------
// void SPI5_Send_Byte(u8 dat)
//-----------------------------------------------------------------
//
// ��������: SPI5����1���ֽ�����
// ��ڲ���: u8 dat�� �����͵�����
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void SPI5_Send_Byte(u8 dat)
{
  u8 Rxdata;
  HAL_SPI_TransmitReceive(&SPI5_Handler, &dat, &Rxdata, 1, 1000);
}

//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
