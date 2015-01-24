/* ������������ ������ �����/������*/

/*
���� A  
���� B
pb4 - in1 ��� ������ ������
pb7 - in4 ��� ����� ������ �����
pb9 - in3 ��� ����� ������ ������

���� D
pd12 - ������� ���������
���� E
pe5 - in2 ��� ������ ������ �����
���� H
���� I

*/
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "gpio.h"

int gpio_init (void)
{
  /* ��������� ��� ������������� ����� */
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  /* �������� ����������� �������� �� ������ A,B,C, D,E */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  
  /*���������������� GPIOA*/
  //���������������� PA0 ��� ���� � ���������������� ������
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /*���������������� GPIOB*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_7 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinAFConfig (GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);  // � PB7 ��������� TIM11_CH1
  GPIO_PinAFConfig (GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);  // � PB9 ��������� TIM11_CH1
  GPIO_PinAFConfig (GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);  // � PB4 ��������� TIM3_CH1
  /*���������������� GPIOC*/
  
  /*���������������� GPIOD*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /*���������������� GPIOE*/
  
 /* GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_PinAFConfig (GPIOE, GPIO_PinSource5, GPIO_AF_TIM9); */ // � PE5 ��������� TIM9_CH1
  /*���������������� GPIOH*/
  /*���������������� GPIOI*/

  return 0;  
}
