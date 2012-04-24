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
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  
return 0;
}