/*
 * delay.c
 *
 *  Created on: Oct 27, 2024
 *      Author: L1
 */
#include "delay.h"

extern TIM_HandleTypeDef htim1;

void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < us);
}
