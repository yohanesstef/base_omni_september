/*
 * motor.c
 *
 *  Created on: Sep 8, 2022
 *      Author: yohanes
 */
#include "main.h"
#include "motor.h"


int16_t enc_speed[4];
int pwm[4];
//---PID------
float kpid[4][3]={{10,0.6,0},
				 {10,0.6,0},
				 {10,0.6,0},
				 {10,0.6,0}};
int sum_error[4];
int16_t error_speed[4];
int16_t target_speed[4];
float p[4],j[4],d[4];
int16_t pid[4];



void kontrol_base(){
	enc_speed[0] = -TIM5->CNT;
	enc_speed[1] = -TIM4->CNT;
	enc_speed[2] = -TIM3->CNT;
	enc_speed[3] = -TIM2->CNT;

	TIM5->CNT = 0;
	TIM2->CNT = 0;
	TIM3->CNT = 0;
	TIM4->CNT = 0;

	for(int i=0; i<4 ; i++){
		error_speed[i] = target_speed[i] - enc_speed[i];
		sum_error[i] += error_speed[i];
		if((sum_error[i] > 0 && target_speed[i] <= 0) || (sum_error[i] < 0 && target_speed[i] >= 0))sum_error[i]=0;
		p[i] = (float)(error_speed[i] * kpid[i][0]);
		j[i] = (float)(sum_error[i] * kpid[i][1]);
		pid[i] = (int16_t)(p[i]+j[i]);
		if(pid[i]>=499)pwm[i] = 499;
		else if(pid[i]<=-499)pwm[i] = -499;
		else pwm[i] = pid[i];
	}

	HAL_GPIO_WritePin(dir_0A_GPIO_Port, dir_0A_Pin, pwm[0] < 0 ? 0 : 1);
	HAL_GPIO_WritePin(dir_0B_GPIO_Port, dir_0B_Pin, pwm[0] < 0 ? 1 : 0);
	TIM12->CCR1	 = abs(pwm[0]);

	HAL_GPIO_WritePin(dir_1A_GPIO_Port, dir_1A_Pin, pwm[1] < 0 ? 1 : 0);
	HAL_GPIO_WritePin(dir_1B_GPIO_Port, dir_1B_Pin, pwm[1] < 0 ? 0 : 1);
	TIM13->CCR1	 = abs(pwm[1]);

	HAL_GPIO_WritePin(dir_2A_GPIO_Port, dir_2A_Pin, pwm[2] < 0 ? 0 : 1);
	HAL_GPIO_WritePin(dir_2B_GPIO_Port, dir_2B_Pin, pwm[2] < 0 ? 1 : 0);
	TIM14->CCR1	 = abs(pwm[2]);

	HAL_GPIO_WritePin(dir_3A_GPIO_Port, dir_3A_Pin, pwm[3] < 0 ? 0 : 1);
	HAL_GPIO_WritePin(dir_3B_GPIO_Port, dir_3B_Pin, pwm[3] < 0 ? 1 : 0);
	TIM9->CCR2	 = abs(pwm[3]);
}

