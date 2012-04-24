/*������� ��� ������ �  �������� �������� LIS302DL �������� �� SPI*/

/*
  PA7 - SPI1_MOSI
  PA5 - SPI1_SCK
  PE0 - MEMS_INT1
  PE1 - MEMS_INT2
  PE3 - CS_I2C/SPI
  PA6 - SPI1_MISO
*/
#include "stm32f4xx.h"
#include "motion_sensor.h"


int InitMotionSensor (void)
{

  //���������� ��������� ���  ������������ �������
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
  
  //SPI ����� �� APB2 ����. �������� ������������
  RCC_APB2PeriphClockCmd(LIS302DL_SPI_CLK, ENABLE);
  
  //�� ����� ���� ��� �� ���� ������� SCK, MOSI � MISO GPIO ������������ 
  //��� ��������� ����� �� ������ ���� ����� ��� ����������
  RCC_AHB1PeriphClockCmd(LIS302DL_SPI_SCK_GPIO_CLK | LIS302DL_SPI_MISO_GPIO_CLK | LIS302DL_SPI_MOSI_GPIO_CLK, ENABLE);

  //CS ������� ������ �������� ����� �� � ������ �� ���� ������������
  RCC_AHB1PeriphClockCmd(LIS302DL_SPI_CS_GPIO_CLK, ENABLE);
  
  // ������������  INT1, INT2 ��� ����� ���� �� �
  RCC_AHB1PeriphClockCmd(LIS302DL_SPI_INT1_GPIO_CLK, ENABLE);

  //���������������� �������������� ������� �����
  
  GPIO_PinAFConfig(LIS302DL_SPI_SCK_GPIO_PORT, LIS302DL_SPI_SCK_SOURCE, LIS302DL_SPI_SCK_AF); // ���� � ��� 5 SPI1
  GPIO_PinAFConfig(LIS302DL_SPI_MISO_GPIO_PORT, LIS302DL_SPI_MISO_SOURCE, LIS302DL_SPI_MISO_AF); // ���� � ��� 6 SPI1
  GPIO_PinAFConfig(LIS302DL_SPI_MOSI_GPIO_PORT, LIS302DL_SPI_MOSI_SOURCE, LIS302DL_SPI_MOSI_AF); // ���� � ��� 7 SPI1
  
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //�������� �������������� �������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;//��������� � �����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//������� 50 ���
  
  GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_SCK_PIN; // ��� 5
  GPIO_Init(LIS302DL_SPI_SCK_GPIO_PORT, &GPIO_InitStructure); // �������������
  
  GPIO_InitStructure.GPIO_Pin =  LIS302DL_SPI_MOSI_PIN; // ��� 7 
  GPIO_Init(LIS302DL_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure); //������������� MOSI

  GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_MISO_PIN; //��� 6
  GPIO_Init(LIS302DL_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);//������������� MISO
  
  /* ���������� ��������� SPI*/
  
  SPI_I2S_DeInit(LIS302DL_SPI); //��������������� SPI 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // �� ����� � ��������
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //�� 8 ���
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; // ��� ����� ��� ����� ���������� ����� low
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;// ���� �����-��
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//
  SPI_InitStructure.SPI_CRCPolynomial = 7;//
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//
  SPI_Init(LIS302DL_SPI, &SPI_InitStructure);// �������������
  
  // ���-���!!!     �������� SPI
  SPI_Cmd(LIS302DL_SPI, ENABLE);
  
  //������ ������������� ��� �������
  
  GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LIS302DL_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
  
  /*���������� ��� ������ */
  GPIO_SetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN);
  
  // ������������ ����� ��� INT2
  GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_INT1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(LIS302DL_SPI_INT1_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_INT2_PIN;
  GPIO_Init(LIS302DL_SPI_INT2_GPIO_PORT, &GPIO_InitStructure);
  
 ////����� ����������� ���� ����������������////////////////////////////
  
  uint8_t ctrl = 0x00;
  
  /* Configure MEMS: data rate, power mode, full scale, self test and axes */
  ctrl = (uint8_t) (LIS302DL_InitStruct->Output_DataRate | LIS302DL_InitStruct->Power_Mode | \
                    LIS302DL_InitStruct->Full_Scale | LIS302DL_InitStruct->Self_Test | \
                    LIS302DL_InitStruct->Axes_Enable);
  
  /* �������� ����������������� ���� � CTRL_REG1 ������� */
  LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG1_ADDR, 1);
  
  
  //������������ ���������
  
  
return 0;
}