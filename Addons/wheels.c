/** ������ ���������� � �������� � ������� �������
��� ������ ����������� � ������� ���������� L298N
�� ��� �������� �� ����� ��� � �����������
����� ������ - 
    ph1 - �����������
    pc15 - ���
������ ������ 
    pc13 - ���
    pe5 - �����������
*/

#include "gpio.h"
#include "timers.h"
#include "wheels.h"

#include "stm32f4xx_tim.h"
extern int pulse=0;
int wheels_init(void)
{
  gpio_init();
  TimersInit();
  
  return 0;
};

void wheel_faster(void)
{
        
        pulse +=6;
        TimersInit();
   
};