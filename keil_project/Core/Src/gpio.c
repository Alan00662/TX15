/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, LED0_Pin|LED1_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PWR_OUT_GPIO_Port, PWR_OUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PIPin PIPin PIPin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = PWR_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PWR_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = PWR_SWITCH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PWR_SWITCH_GPIO_Port, &GPIO_InitStruct);
  
  
  HAL_GPIO_WritePin(PWR_OUT_GPIO_Port, PWR_OUT_Pin, GPIO_PIN_SET);
}

/* USER CODE BEGIN 2 */

uint32_t led0_bink_tick = 0;
void led0_bink(uint16_t ms)
{
	if((HAL_GetTick() - led0_bink_tick) > ms)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED0_Pin);
		led0_bink_tick =  HAL_GetTick();
	}

}	

uint32_t led1_bink_tick = 0;
void led1_bink(uint16_t ms)
{
	if((HAL_GetTick() - led1_bink_tick) > ms)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		led1_bink_tick =  HAL_GetTick();
	}

}	

uint32_t led2_bink_tick = 0;
void led2_bink(uint16_t ms)
{
	if((HAL_GetTick() - led2_bink_tick) > ms)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED2_Pin);
		led2_bink_tick =  HAL_GetTick();
	}

}	
/* USER CODE END 2 */
