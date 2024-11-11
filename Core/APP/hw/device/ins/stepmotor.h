/*
 * stepmotor.h
 *
 *  Created on: Oct 27, 2024
 *      Author: L1
 */

#ifndef APP_HW_DEVICE_INS_STEPMOTOR_H_
#define APP_HW_DEVICE_INS_STEPMOTOR_H_

#include "hw.h"

void Step_Drive(int step);
void Step_Drive_Stop();
void StepMotor_RotateCW(uint16_t delay_us_time);
void StepMotor_RotateCCW(uint16_t delay_us_time);

#endif /* APP_HW_DEVICE_INS_STEPMOTOR_H_ */
