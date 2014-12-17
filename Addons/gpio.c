/* ������������ ������ �����/������*/

/*
���� A  
���� B
���� C
pc13 - ����������� ������ ������
pc15 - ��� ����� ������
���� D
pd12 - ������� ���������
���� E
pe5 - ��� ������ ������
���� H
ph1 - ����������� ������ ������
���� I

*/
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "gpio.h"

int gpio_init (void)
{
  /* ��������� ��� ������������� ����� */
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  /* �������� ����������� �������� �� ������ C,D,E,H */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
  
  /*���������������� GPIOA*/
  
  /*���������������� GPIOB*/
  
  /*���������������� GPIOC*/
  /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  GPIO_PinAFConfig (GPIOC, GPIO_PinSource13, GPIO_AF_TIM4);
  GPIO_PinAFConfig (GPIOC, GPIO_PinSource15, GPIO_AF_TIM4);*/
  
  /*���������������� GPIOD*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /*���������������� GPIOE*/
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_PinAFConfig (GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);  // � PE5 ��������� TIM9_CH1
  /*���������������� GPIOH*/
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  /*���������������� GPIOI*/

  return 0;  
}
