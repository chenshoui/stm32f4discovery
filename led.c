
#include "led.h"


void ledInit (void)
{
  /* ��������� ��� �������������*/
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* ������ ������������ �� ���� D */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  /* Configure the GPIOD */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  
}

//������ ���������
void ledOn(uint16_t led)
{
   (GPIOD->BSRRL) = led; //on led4 
}

//�������� ���������
void ledOff (uint16_t led)
{

  (GPIOD->BSRRH) =led; 
}

//������������� ��������� ����������
void ledInvert (uint16_t led)
{  int val=GPIOD->ODR;

 if ( val) 
   ledOff(led);
 else 
   ledOn(led);
}

