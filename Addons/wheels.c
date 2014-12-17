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

int wheels_init(void)
{
  gpio_init();
  TimersInit();
  
  return 0;
};
