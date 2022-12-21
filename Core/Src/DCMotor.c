/*
 * DCMotor.c
 *
 *  Created on: Dec 14, 2022
 *      Author: opdpires
 */

#include "main.h"
#include "DCMotor.h"

TIM_OC_InitTypeDef sConfigOC_DC_Motor = {0};

void setupMotor(TIM_HandleTypeDef *htimx, uint32_t channel, uint16_t period){
	HAL_TIM_PWM_Start(htimx, channel);
	setMotorDirection(Forward);
	setMotorSpeed(htimx,channel,period,100);
}

void setMotorSpeed(TIM_HandleTypeDef *htimx, uint32_t channel, uint16_t period, uint16_t speed){

	sConfigOC_DC_Motor.Pulse = (1.0*speed*period)/100;
	sConfigOC_DC_Motor.OCMode = TIM_OCMODE_PWM1;
	sConfigOC_DC_Motor.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC_DC_Motor.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_Stop(htimx, channel);
	HAL_TIM_PWM_Init(htimx);
	HAL_TIM_PWM_ConfigChannel(htimx, &sConfigOC_DC_Motor, channel);
	HAL_TIM_PWM_Start(htimx, channel);
}
/*
uint16_t setMotorSpeed(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, uint16_t speed){
	uint16_t pulse = (speed*1.0/100)*period;
	setMotorPWM(timer,channel,period,pulse);
	return pulse;
}
*/
void setMotorDirection(Direction dir_code){

	GPIO_PinState bit_to_send = GPIO_PIN_RESET;

	//Enviar código de controle da direção:
	HAL_GPIO_WritePin(GPIOA, DIR_EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, DIR_LATCH_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, DIR_CLK_Pin, GPIO_PIN_RESET);

	unsigned char comparator = 0x80;

	for (int i = 0; i<8; i++){
		if (dir_code & comparator){
		  bit_to_send = GPIO_PIN_SET;
		}
		else{
		  bit_to_send = GPIO_PIN_RESET;
		}

		comparator = comparator >> 1;

		HAL_GPIO_WritePin(GPIOA, DIR_SER_Pin, bit_to_send);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOB, DIR_CLK_Pin, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOB, DIR_CLK_Pin, GPIO_PIN_RESET);
		HAL_Delay(1);
	}

	HAL_GPIO_WritePin(GPIOA, DIR_LATCH_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, DIR_LATCH_Pin, GPIO_PIN_RESET);
}
/*
void setMotorPWM(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, uint16_t pulse){
	 HAL_TIM_PWM_Stop(timer, channel); // stop generation of pwm
	 TIM_OC_InitTypeDef sConfigOC;
	 timer->Init.Period = period; // set the period duration
	 HAL_TIM_PWM_Init(timer); // reinititialise with new period value
	 sConfigOC.OCMode = TIM_OCMODE_PWM1;
	 sConfigOC.Pulse = pulse; // set the pulse duration
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	 HAL_TIM_PWM_ConfigChannel(timer, &sConfigOC, channel);
	 HAL_TIM_PWM_Start(timer, channel); // start pwm generation
}*/
