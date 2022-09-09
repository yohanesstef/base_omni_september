/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define pwm_3_Pin GPIO_PIN_6
#define pwm_3_GPIO_Port GPIOE
#define enc_0A_Pin GPIO_PIN_0
#define enc_0A_GPIO_Port GPIOA
#define enc_0B_Pin GPIO_PIN_1
#define enc_0B_GPIO_Port GPIOA
#define dir_2A_Pin GPIO_PIN_5
#define dir_2A_GPIO_Port GPIOA
#define pwm_1_Pin GPIO_PIN_6
#define pwm_1_GPIO_Port GPIOA
#define pwm_2_Pin GPIO_PIN_7
#define pwm_2_GPIO_Port GPIOA
#define dir_1A_Pin GPIO_PIN_0
#define dir_1A_GPIO_Port GPIOB
#define dir_1B_Pin GPIO_PIN_1
#define dir_1B_GPIO_Port GPIOB
#define dir_3B_Pin GPIO_PIN_2
#define dir_3B_GPIO_Port GPIOB
#define dir_3A_Pin GPIO_PIN_7
#define dir_3A_GPIO_Port GPIOE
#define dir_0B_Pin GPIO_PIN_14
#define dir_0B_GPIO_Port GPIOE
#define dir_0A_Pin GPIO_PIN_11
#define dir_0A_GPIO_Port GPIOB
#define pwm_0_Pin GPIO_PIN_14
#define pwm_0_GPIO_Port GPIOB
#define dir_2B_Pin GPIO_PIN_8
#define dir_2B_GPIO_Port GPIOD
#define enc_3A_Pin GPIO_PIN_15
#define enc_3A_GPIO_Port GPIOA
#define enc_3B_Pin GPIO_PIN_3
#define enc_3B_GPIO_Port GPIOB
#define enc_2A_Pin GPIO_PIN_4
#define enc_2A_GPIO_Port GPIOB
#define enc_2B_Pin GPIO_PIN_5
#define enc_2B_GPIO_Port GPIOB
#define enc_1A_Pin GPIO_PIN_6
#define enc_1A_GPIO_Port GPIOB
#define enc_1B_Pin GPIO_PIN_7
#define enc_1B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
