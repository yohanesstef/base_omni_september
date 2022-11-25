/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define JSSL 0x1
#define JSL3 0x2
#define JSR3 0x4
#define JSST 0x8
#define JSUP 0x10
#define JSRG 0x20
#define JSDW 0x40
#define JSLF 0x80
#define JSL2 0x100
#define JSR2 0x200
#define JSL1 0x400
#define JSR1 0x800
#define JSTR 0x1000
#define JSCR 0x2000
#define JSXX 0x4000
#define JSSQ 0x8000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float rasio_speed = 0.5;
int mode = 0;
int latch = 0, latch_XX = 0, latch_TR = 0;
int8_t joystick_status;
int16_t joystick_analog [3];
uint8_t joystick_value[9];
uint16_t joystick_button;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef* huart){
	if(huart->Instance==USART2){
		if (joystick_value[0] == 'i' && joystick_value[1] == 't' && joystick_value[2] == 's'){
			joystick_status = 1;
		}
		else{
			joystick_status= 0;
			HAL_UART_DMAStop(&huart2);
			HAL_UART_Receive_DMA(&huart2, joystick_value, 9);
		}
	}
}

void input_analog(){
	if (joystick_status == 1){
		joystick_button = ~(joystick_value[3] + (joystick_value[4]<<8));
		joystick_analog[0]= (joystick_value [7]-127);
		joystick_analog[1] = (127-joystick_value [8]);
		joystick_analog[2] = (joystick_value [5]-127);
	}
	else {
		joystick_analog[0] = 0;
		joystick_analog[1] = 0;
		joystick_analog[2] = 0;
	}
	if(joystick_button == JSR1) {
		latch = 1;
		rasio_speed = 0.75;
	}
	else if(joystick_button != JSR1 && latch == 1){
		latch = 0;
		rasio_speed = 0.5;
	}

	if(joystick_button == JSSQ)mode = 0;
	else if(joystick_button == JSCR) mode = 1;

	if(joystick_button == JSXX && latch_XX == 1){
		latch_XX = 0;
		rasio_speed += 0.01;
	}
	else if(joystick_button != JSXX && latch_XX == 0)latch_XX = 1;

	if (joystick_button == JSTR && latch_TR == 1){
		latch_TR = 0;
		rasio_speed -= 0.01;
	}
	else if (joystick_button != JSTR && latch_TR == 0)latch_TR = 1;

	if(rasio_speed >= 0.8) rasio_speed = 0.8;
	else if(rasio_speed <= 0) rasio_speed = 0;

}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM9_Init();
  MX_TIM12_Init();
  MX_TIM13_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
  ///--------------start encoder dan timer pwm----------------
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);


  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);

  HAL_UART_Receive_DMA(&huart2, joystick_value, 9);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

