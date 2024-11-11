/*
 * ap.c
 *
 *  Created on: Oct 26, 2024
 *      Author: L1
 */
#include "ap.h"

uint8_t Start = 0;

uint8_t button_state = 0; // 0Ready, 1floor, 2floor, 3floor, 4reset
uint8_t re_button_state = 0;

uint8_t Floor = 0;	// 0Ready, 1floor1, 2floor2, 3floor3

uint16_t steps = 0;

uint8_t Step_Stop = 0;

void apInit(void)
{

}

void apMain(void)
{
	while(1)
	{
		// Reset 1Floor
		if (Start == 0)
		{
			 Step_Stop = 1;

			 steps = 4096;
			 StepMotor_RotateCW(1300);

			 Start = 1;
		}

		if (Start == 1)
		{
			  button_state = 1;
			  Floor = 1;
			  Step_Stop = 0;
			  Start = 2;
		}

		// 1Floor Start
		if (Start == 2)
		{
			  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0)
			  {
				  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
			  }

				  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0)
				  {
					  button_state = 1;
					  re_button_state = 3;
				  }

				  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == 0)
				  {
					  button_state = 2;
					  re_button_state = 2;
				  }

				  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 0)
				  {
					  button_state = 3;
					  re_button_state = 1;
				  }

			  ////////////////////////////////////////////////////////
			  if(re_button_state == 1)
			  {
				  Step_Stop = 1;

				  steps = 4096;
				  StepMotor_RotateCW(1300);
			  }

			  if(re_button_state == 2)
			  {
				  Step_Stop = 1;

				  steps = 4096;
				  StepMotor_RotateCW(1300);
			  }

			  if(re_button_state == 3)
			  {
				  Step_Stop = 1;

				  steps = 4096;
				  StepMotor_RotateCW(1300);
			  }

				  if(button_state == 1)
				  {
					  Step_Stop = 1;

					  steps = 4096;
					  StepMotor_RotateCW(1300);
				  }

				  if(button_state == 2)
				  {
					  Step_Stop = 1;

					  steps = 4096;
					  StepMotor_RotateCCW(1300);
				  }

				  if(button_state == 3)
				  {
					  Step_Stop = 1;

					  steps = 4096;
					  StepMotor_RotateCCW(1300);
				  }
		}
	}
}
