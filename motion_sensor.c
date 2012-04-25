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


int InitMotionSensor (LIS302DL_InitTypeDef *LIS302DL_InitStruct)
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
  MotionSensorWrite(&ctrl, LIS302DL_CTRL_REG1_ADDR, 1);
  
  
  
  
  //������������ ���������
  
  
return 0;
}





/*���������� ���� �� SPI � ���������� ���� ��������*/
uint8_t MotionSensorSendByte(uint8_t byte)

{

  /* Loop while DR register in not emplty */
  uint32_t LIS302DLTimeout = 0x1000;  //��� �������� ���� ���-�� ������� ������ �� �������, �� � ����� � ���� ��� �����.
  while (SPI_I2S_GetFlagStatus(LIS302DL_SPI, SPI_I2S_FLAG_TXE) == RESET)/*���� ��������� ���� TransmitBuferEmti � ������ ������ SET*/
  {
    if((LIS302DLTimeout--) == 0) return 0; //�� ���� ������ ������ 0 ���� �������� ������� ������ � ����������������
  }
  
  /* ������� byte �� SPI LIS302DL_SPI */
  SPI_I2S_SendData(LIS302DL_SPI, byte);
  
  /* ���� ������ ����� */
  LIS302DLTimeout = 0x1000;
  while (SPI_I2S_GetFlagStatus(LIS302DL_SPI, SPI_I2S_FLAG_RXNE) == RESET)//������� ���� � ����� ������ ���-�� �� ��������.
  {
    if((LIS302DLTimeout--) == 0) return 0; //�� ���� ������ ������ 0 ���� �������� ������� ������ � ����������������
  }
  
  /* ���������� �������� �������� */
  return (uint8_t)SPI_I2S_ReceiveData(LIS302DL_SPI);
}


void MotionSensorWrite (uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
/* Configure the MS bit: 
       - When 0, the address will remain unchanged in multiple read/write commands.
       - When 1, the address will be auto incremented in multiple read/write commands.
  */
  if(NumByteToWrite > 0x01)
  {
    WriteAddr |= 0x40;//0x40 = 100000 ������������� ��� MS
  }
  /* ��� ������ ������ ������������� ������ ������� �� ��� ������ */
 GPIO_ResetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN);
  
  /* Send the Address of the indexed register */
  MotionSensorSendByte(WriteAddr);
  /* Send the data that will be written into the device (MSB First) */
  while(NumByteToWrite >= 0x01)
  {
    MotionSensorSendByte(*pBuffer);
    NumByteToWrite--;
    pBuffer++;
  }
  
  /* ����� ������, ���������� ������� ������� �� ��� ������ */ 
  GPIO_SetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN);
}

/**
  * @brief  Reads a block of data from the LIS302DL.
  * @param  pBuffer : pointer to the buffer that receives the data read from the LIS302DL.
  * @param  ReadAddr : LIS302DL's internal address to read from.
  * @param  NumByteToRead : number of bytes to read from the LIS302DL.
  * @retval None
  */
void MotionSensorRead(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{  
  if(NumByteToRead > 0x01)
  {
    ReadAddr |= (uint8_t)(0x80 | 0x40); //���������� ���� RW, MS
  }
  else
  {
    ReadAddr |= 0x80; //���������� RW
  }
  
  /* ��� ������ ������ ������������� ������ ������� �� ��� ������ */
 GPIO_ResetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN);
  
  /* Send the Address of the indexed register */
  MotionSensorSendByte(ReadAddr);
  
  /* Receive the data that will be read from the device (MSB First) */
  while(NumByteToRead > 0x00)
  {
    /* Send dummy byte (0x00) to generate the SPI clock to LIS302DL (Slave device) */
    *pBuffer = MotionSensorSendByte(0x00);
    NumByteToRead--;
    pBuffer++;
  }
  
  /* ����� ������, ���������� ������� ������� �� ��� ������ */ 
  GPIO_SetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN);
}
