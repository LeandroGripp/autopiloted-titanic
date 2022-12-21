/*
 * Servo.c
 *
 *  Created on: Dec 11, 2022
 *      Author: opdpires
 */

#include "../Inc/Servo.h"


const float ANGLE_PERCENTAGE_90_NEG = 0.0256;
const float ANGLE_PERCENTAGE_90_POS = 0.1240;
const float ANGLE_PERCENTAGE_NEUTRAL = 0.0744;

void setServoAngle(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, int8_t angle){
	uint16_t pulse = 0;
	if(angle<-90){
		pulse = ANGLE_PERCENTAGE_90_NEG*period;
	}
	if(angle>90){
		pulse = ANGLE_PERCENTAGE_90_POS*period;
	}
	if((angle>=-90)&&(angle<0)){
		pulse = (((angle+90.0)/90)*(ANGLE_PERCENTAGE_NEUTRAL-ANGLE_PERCENTAGE_90_NEG)+ANGLE_PERCENTAGE_90_NEG)*period;
	}
	if((angle>=0)&&(angle<=90)){
		pulse = (((angle)/90.0)*(ANGLE_PERCENTAGE_90_POS-ANGLE_PERCENTAGE_NEUTRAL)+ANGLE_PERCENTAGE_NEUTRAL)*period;
	}
	setServoPWM(timer,channel,period,pulse);
}

/*
void setServoAngle(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, int8_t angle){
	static int8_t pastAngle = 0;
	if(angle<-90){
		angle = -90;
	}
	if(angle>90){
		angle = 90;
	}
	int8_t nbOfSteps = (angle-pastAngle) > 0 ? angle-pastAngle : pastAngle-angle;
	int8_t signalStep = (angle >= pastAngle) ? 1 : -1;
	int8_t currentAngle = pastAngle;

	for (int i = 0; i<nbOfSteps; i++) {
		currentAngle += signalStep;
		uint16_t pulse = 0;
		if((currentAngle>=-90)&&(currentAngle<0)){
			pulse = (((currentAngle+90.0)/90)*(ANGLE_PERCENTAGE_NEUTRAL-ANGLE_PERCENTAGE_90_NEG)+ANGLE_PERCENTAGE_90_NEG)*period;
		}
		if((currentAngle>=0)&&(currentAngle<=90)){
			pulse = (((currentAngle)/90.0)*(ANGLE_PERCENTAGE_90_POS-ANGLE_PERCENTAGE_NEUTRAL)+ANGLE_PERCENTAGE_NEUTRAL)*period;
		}
		setServoPWM(timer,channel,period,pulse);
	}
	pastAngle = angle;
}
*/

void setServoPWM(TIM_HandleTypeDef* timer, uint32_t channel, uint16_t period, uint16_t pulse)
{
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
}
