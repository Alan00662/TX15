/**
 ****************************************************************************************************
 * @file        adc3.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       ADC3驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 北极星 H750开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __ADC3_H
#define __ADC3_H

#include "main.h"

/* ADC定义 */
#define ADC_ADC_BAT                                ADC3
#define ADC_ADC_BAT_CLK_ENABLE()                   do { __HAL_RCC_ADC3_CLK_ENABLE(); } while (0)
#define ADC_ADC_BAT_CHY                            ADC_CHANNEL_11
#define ADC_ADC_BAT_CHY_GPIO_PORT                  GPIOH
#define ADC_ADC_BAT_CHY_GPIO_PIN                   GPIO_PIN_1
#define ADC_ADC_BAT_CHY_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOH_CLK_ENABLE(); } while (0)


/* 函数声明 */
void adc3_init(void);                                               /* 初始化ADC3 */
uint32_t adc3_get_result(uint32_t channel);                         /* 获取ADC3结果 */
uint32_t adc3_get_result_average(uint32_t channel, uint8_t times);  /* 均值滤波获取ADC3结果 */
int32_t adc3_get_temperature(void);                                 /* 获取内部温度传感器结果 */

#endif
