/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       ADC驱动代码
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

#ifndef __ADC_H
#define __ADC_H

#include "main.h"

/* ADC定义 */
#define ADC_ADC_S1                                ADC1
#define ADC_ADC_S1_CLK_ENABLE()                   do { __HAL_RCC_ADC12_CLK_ENABLE(); } while (0)
#define ADC_ADC_S1_CHY                            ADC_CHANNEL_11
#define ADC_ADC_S1_CHY_GPIO_PORT                  GPIOC
#define ADC_ADC_S1_CHY_GPIO_PIN                   GPIO_PIN_1
#define ADC_ADC_S1_CHY_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)


/* ADC定义 */
#define ADC_ADC_S2                                ADC1
#define ADC_ADC_S2_CLK_ENABLE()                   do { __HAL_RCC_ADC12_CLK_ENABLE(); } while (0)
#define ADC_ADC_S2_CHY                            ADC_CHANNEL_5
#define ADC_ADC_S2_CHY_GPIO_PORT                  GPIOB
#define ADC_ADC_S2_CHY_GPIO_PIN                   GPIO_PIN_1
#define ADC_ADC_S2_CHY_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)

#define ADC_DMA_ADCX                            ADC1
#define ADC_DMA_ADCX_CLK_ENABLE();              do { __HAL_RCC_ADC12_CLK_ENABLE(); } while (0)
#define ADC_DMA_ADCX_CHY                        ADC_CHANNEL_19
#define ADC_DMA_ADCX_CHY_GPIO_PORT              GPIOA
#define ADC_DMA_ADCX_CHY_GPIO_PIN               GPIO_PIN_5
#define ADC_DMA_ADCX_CHY_GPIO_CLK_ENABLE()      do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)
#define ADC_DMA_ADCX_DMASX                      DMA1_Stream0
#define ADC_DMA_ADCX_DMA_CLK_ENABLE()           do { __HAL_RCC_DMA1_CLK_ENABLE(); } while (0)
#define ADC_DMA_ADCX_DMASX_REQ                  DMA_REQUEST_ADC1
#define ADC_DMA_ADCX_DMASX_IRQn                 DMA1_Stream0_IRQn
#define ADC_DMA_ADCX_DMASX_IRQHandler           DMA1_Stream0_IRQHandler

#define ADC_NCH_DMA_ADCX                        ADC2
#define ADC_NCH_DMA_ADCX_CLK_ENABLE()           do { __HAL_RCC_ADC12_CLK_ENABLE(); } while (0)
#define ADC_NCH_DMA_ADCX_CH_NUM                 2
#define ADC_NCH_DMA_ADCX_CHA                    ADC_CHANNEL_18
#define ADC_NCH_DMA_ADCX_CHA_GPIO_PORT          GPIOA
#define ADC_NCH_DMA_ADCX_CHA_GPIO_PIN           GPIO_PIN_4
#define ADC_NCH_DMA_ADCX_CHA_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)
#define ADC_NCH_DMA_ADCX_CHB                    ADC_CHANNEL_19
#define ADC_NCH_DMA_ADCX_CHB_GPIO_PORT          GPIOA
#define ADC_NCH_DMA_ADCX_CHB_GPIO_PIN           GPIO_PIN_5
#define ADC_NCH_DMA_ADCX_CHB_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)
#define ADC_NCH_DMA_ADCX_DMASX                  DMA1_Stream1
#define ADC_NCH_DMA_ADCX_DMA_CLK_ENABLE()       do { __HAL_RCC_DMA1_CLK_ENABLE(); } while (0)
#define ADC_NCH_DMA_ADCX_DMASX_REQ              DMA_REQUEST_ADC2
#define ADC_NCH_DMA_ADCX_DMASX_IRQn             DMA1_Stream1_IRQn
#define ADC_NCH_DMA_ADCX_DMASX_IRQHandler       DMA1_Stream1_IRQHandler

#define ADC_OS_ADCX                             ADC1
#define ADC_OS_ADCX_CLK_ENABLE()                do { __HAL_RCC_ADC12_CLK_ENABLE(); } while (0)
#define ADC_OS_ADCX_CHY                         ADC_CHANNEL_19
#define ADC_OS_ADCX_CHY_GPIO_PORT               GPIOA
#define ADC_OS_ADCX_CHY_GPIO_PIN                GPIO_PIN_5
#define ADC_OS_ADCX_CHY_GPIO_CLK_ENABLE()       do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)

/* 函数声明 */
void adc1_init(void);                                                /* 初始化ADC */
uint32_t adc_get_result(uint32_t channel);                          /* 获取ADC结果 */
uint32_t adc_get_result_average(uint32_t channel, uint8_t times);   /* 均值滤波获取ADC结果 */
void adc_dma_init(uint32_t memory_base);                            /* 初始化ADC DMA读取 */
void adc_dma_enable(uint32_t length);                               /* 开启ADC DMA读取 */
void adc_nch_dma_init(uint32_t memory_base);                        /* 初始化多通道ADC DMA读取 */
void adc_nch_dma_enable(uint32_t length);                           /* 开启多通道ADC DMA读取 */
void adc_oversample_init(uint32_t ratio, uint32_t right_shift);     /* 初始化ADC过采样 */

#endif
