/*
 * stepmotor.c
 *
 *  Created on: Oct 27, 2024
 *      Author: L1
 */
#include "stepmotor.h"

extern uint8_t Start;
extern uint8_t State;

extern uint8_t button_state; // 0Ready, 1floor, 2floor, 3floor, 4reset
extern uint8_t re_button_state;

extern uint8_t Floor;	// 0Ready, 1floor1, 2floor2, 3floor3

extern uint16_t steps;

extern uint8_t Step_Stop;

void Step_Drive(int step)
{
	switch(step)
	{
		case 1:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
		break;

		case 2:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
		break;

		case 3:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
		break;

		case 4:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
		break;

		case 5:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
		break;

		case 6:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
		break;

		case 7:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
		break;

		case 8:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
		break;
	}
}

void Step_Drive_Stop()
{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
}

void StepMotor_RotateCW(uint16_t delay_us_time)
{
	if (Start == 0) // Reset 1Floor
	{
	    for (uint16_t i = 0; i < steps; i++)
	    {

	        if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
	        {
	            Step_Drive_Stop();
	            return;
	        }

	        for (uint8_t j = 1; j <= 8; j++)
	        {
	            Step_Drive(j);
	            delay_us(delay_us_time);
	            if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
	            {
	                Step_Drive_Stop();
	                return;
	            }
	        }
	    }
	}

	if (Start == 2 && re_button_state == 3 && Floor == 3) //3Floor -> 1Floor
	{
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
		{
			Floor = 1;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
		}
		for (uint16_t i = 0; i < steps; i++)
		{
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
			}
			if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
			{
				Step_Drive_Stop();
				return;
			}

			for (uint8_t j = 1; j <= 8; j++)
			{
				Step_Drive(j);
				delay_us(delay_us_time);
				if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
				{
					Step_Drive_Stop();
					return;
				}
			}
		}
	}

	if (Start == 2 && re_button_state == 2 && Floor == 3) // 3층에?�� 2층으�? ?��?���? ?��?��
	{
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
		{
			Floor = 2;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
		}
		for (uint16_t i = 0; i < steps; i++)
		{
			if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
			{
				Step_Drive_Stop();
				return;
			}

			for (uint8_t j = 1; j <= 8; j++)
			{
				Step_Drive(j);
				delay_us(delay_us_time);
				if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
				{
					Step_Drive_Stop();
					return;
				}
			}
		}
	}

	if (Start == 2 && re_button_state == 3 && Floor == 2) // 2층에?�� 1층으�? ?��?���? ?��?��
	{
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
		{
			Floor = 1;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
		}
		for (uint16_t i = 0; i < steps; i++)
		{
			if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
			{
				Step_Drive_Stop();
				return;
			}

			for (uint8_t j = 1; j <= 8; j++)
			{
				Step_Drive(j);
				delay_us(delay_us_time);
				if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
				{
					Step_Drive_Stop();
					return;
				}
			}
		}
	}
}

void StepMotor_RotateCCW(uint16_t delay_us_time)
{
	if (Start == 0)
	{
		for (uint16_t i = 0; i < steps; i++)
		{
			if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
			{
				Step_Drive_Stop();
				return;
			}

			for (int8_t j = 8; j >= 1; j--)
			{
				Step_Drive(j);
				delay_us(delay_us_time);
				if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
				{
					Step_Drive_Stop();
					return;
				}
			}
		}
	}
	if (Start == 2 && button_state == 2 && Floor == 1) // 1층에?�� 2층으�? ?���? ?��?��
	{
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
		{
			Floor = 2;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
		}
		for (uint16_t i = 0; i < steps; i++)
		{
			if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
			{
				Step_Drive_Stop();
				return;
			}

			for (int8_t j = 8; j >= 1; j--)
			{
				Step_Drive(j);
				delay_us(delay_us_time);
				if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
				{
					Step_Drive_Stop();
					return;
				}
			}
		}
	}
	if (Start == 2 && button_state == 3 && Floor == 1) // 1층에?�� 3층으�? ?���? ?��?��
		{
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)
			{
				Floor = 3;
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
			}
			for (uint16_t i = 0; i < steps; i++)
			{
				if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
				}
				if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)
				{
					Step_Drive_Stop();
					return;
				}

				for (int8_t j = 8; j >= 1; j--)
				{
					Step_Drive(j);
					delay_us(delay_us_time);
					if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)
					{
						Step_Drive_Stop();
						return;
					}
				}
			}
		}
	if (Start == 2 && button_state == 3 && Floor == 2) // 2층에?�� 3층으�? ?���? ?��?��
		{
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)
			{
				Floor = 3;
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
			}
			for (uint16_t i = 0; i < steps; i++)
			{
				if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)
				{
					Step_Drive_Stop();
					return;
				}

				for (int8_t j = 8; j >= 1; j--)
				{
					Step_Drive(j);
					delay_us(delay_us_time);
					if (Step_Stop == 1 && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 0)
					{
						Step_Drive_Stop();
						return;
					}
				}
			}
		}
}
