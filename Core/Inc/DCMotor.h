/*
 * DCMotor.h
 *
 *  Created on: Dec 14, 2022
 *      Author: opdpires
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32f1xx_hal.h"

typedef enum{

	Stop = 0x00,
	Forward = 0x01,//Motor_4_F = 0x01; Motor_4_R = 0x40
	Back = 0x10

} Direction;

void setupMotor(TIM_HandleTypeDef *htimx);
void setMotorSpeed(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, uint16_t speed);
void setMotorDirection(Direction dir);
//void setMotorPWM(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, uint16_t pulse);

#endif /* DCMOTOR_H_ */
