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

#include "drivers/gpio.h"
#include "drivers/timers.h"
#include "wheels.h"

#include "stm32f4xx_tim.h"
//int pulse=0;

void wheel_set_speed(int,int);

int wheels_init(void)
{
  gpio_init();
  TimersInit();
  wheel_set_speed(0,0);
  
  
  return 0;
};

void wheel_set_speed(int speed_left,int speed_right)
{
  
  return;
}


void wheel_faster(void)
{
        
       // pulse +=6;
        TimersInit();
   
};