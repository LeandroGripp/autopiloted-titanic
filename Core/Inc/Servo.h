/*
 * Servo.h
 *
 *  Created on: Dec 11, 2022
 *      Author: opdpires
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f1xx_hal.h"


void setServoAngle(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, int16_t angle);
void setServoPWM(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, uint16_t pulse);

#endif /* INC_SERVO_H_ */
