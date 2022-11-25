/*
 * motor.c
 *
 *  Created on: Sep 8, 2022
 *      Author: yohanes
 */
#include "main.h"
#include "motor.h"
#include "math.h"

# define PI 3.14159265359
# define rad PI/180.0

extern float rasio_speed;

int16_t enc_speed[4];
int pwm[4];
//---PID------
float kpid[4][3]={{2.5,0.6,0},
				 {2.5,0.6,0},
				 {2.5,0.6,0},
				 {2.5,0.6,0}};
int16_t error_speed[4];
int16_t target_speed[4];
float p[4],j[4],d[4];
int16_t pid[4];
float resultan_vektor;
float sudut_resultan;
//int16_t base_speed[3];
float koordinat_bulat[2];
float matrix[4][3] ={
                    {cosf(45.0*rad), sinf(45.0*rad), -1},
                    {cosf(135.0*rad), sinf(135.0*rad), -1},
                    {cosf(225.0*rad), sinf(225.0*rad), -1},
                    {cosf(315.0*rad), sinf(315.0*rad), -1}};

void invers_kinematik(int16_t base_speed[3], int mode){
	if (mode == 1){//bu;at
		koordinat_bulat[0] = (base_speed[0] * sqrtf(1 - 0.5 * powf(base_speed[1]/128.0,2)));
		koordinat_bulat[1] = (base_speed[1] * sqrtf(1 - 0.5 * powf(base_speed[0]/128.0,2)));

		base_speed[0] = koordinat_bulat[0];
		base_speed[1] = koordinat_bulat[1];
	}
	for(int i=0; i<4 ;i++){
		target_speed[i] = rasio_speed * (matrix[i][0] * base_speed[0] + matrix[i][1] * base_speed[1]) * 0.25 + matrix[i][2] * base_speed [2] * 0.1;
	}

}

void kontrol_base(){
	enc_speed[0] = -TIM5->CNT;
	enc_speed[1] = TIM4->CNT;
	enc_speed[2] = TIM3->CNT;
	enc_speed[3] = -TIM2->CNT;

	TIM5->CNT = 0;
	TIM2->CNT = 0;
	TIM3->CNT = 0;
	TIM4->CNT = 0;

//	resultan_vektor = sqrtf(base_speed[0]*base_speed[0]+base_speed[1]*base_speed[1]);
//	sudut_resultan = atan2f(base_speed[1],base_speed[0]);
//
//	target_speed[0] = resultan_vektor * cosf(315.0f * M_PI/180.0f - sudut_resultan) *faktor_pengali + base_speed[2];
//	target_speed[1] = resultan_vektor * cosf(45.0f * M_PI/180.0f - sudut_resultan) * faktor_pengali + base_speed[2];
//	target_speed[2] = resultan_vektor * cosf(135.0f * M_PI/180.0f - sudut_resultan) * faktor_pengali + base_speed[2];
//	target_speed[3] = resultan_vektor * cosf(225.0f * M_PI/180.0f - sudut_resultan) * faktor_pengali + base_speed[2];
//
	for(int i=0; i<4 ; i++){
		error_speed[i] = target_speed[i] - enc_speed[i];
		if((j[i] > 0 && target_speed[i] <= 0) || (j[i] < 0 && target_speed[i] >= 0))j[i]=0;
		p[i] = (float)(error_speed[i] * kpid[i][0]);
		j[i] += (float)(error_speed[i] * kpid[i][1]);
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

