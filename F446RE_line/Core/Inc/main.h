/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define MUX1X_Pin GPIO_PIN_0
#define MUX1X_GPIO_Port GPIOC
#define MUX1Y_Pin GPIO_PIN_1
#define MUX1Y_GPIO_Port GPIOC
#define LEFTSIDE_LINE_Pin GPIO_PIN_2
#define LEFTSIDE_LINE_GPIO_Port GPIOC
#define ENCODER3_Pin GPIO_PIN_3
#define ENCODER3_GPIO_Port GPIOC
#define MUX2X_Pin GPIO_PIN_2
#define MUX2X_GPIO_Port GPIOA
#define MUX2Y_Pin GPIO_PIN_3
#define MUX2Y_GPIO_Port GPIOA
#define MUX2A_Pin GPIO_PIN_4
#define MUX2A_GPIO_Port GPIOA
#define MUX2B_Pin GPIO_PIN_5
#define MUX2B_GPIO_Port GPIOA
#define ENCODER4_Pin GPIO_PIN_6
#define ENCODER4_GPIO_Port GPIOA
#define ENCODER2_Pin GPIO_PIN_7
#define ENCODER2_GPIO_Port GPIOA
#define ENCODER1_Pin GPIO_PIN_4
#define ENCODER1_GPIO_Port GPIOC
#define MUX3X_Pin GPIO_PIN_5
#define MUX3X_GPIO_Port GPIOC
#define MUX3Y_Pin GPIO_PIN_0
#define MUX3Y_GPIO_Port GPIOB
#define RIGHTSIDE_LINE_Pin GPIO_PIN_1
#define RIGHTSIDE_LINE_GPIO_Port GPIOB
#define MUX3A_Pin GPIO_PIN_12
#define MUX3A_GPIO_Port GPIOB
#define MUX3B_Pin GPIO_PIN_13
#define MUX3B_GPIO_Port GPIOB
#define LED_LINE_Pin GPIO_PIN_8
#define LED_LINE_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_11
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOC
#define MUX1A_Pin GPIO_PIN_7
#define MUX1A_GPIO_Port GPIOB
#define MUX1B_Pin GPIO_PIN_9
#define MUX1B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
