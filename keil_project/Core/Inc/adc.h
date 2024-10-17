/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       ADC��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� ������ H750������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __ADC_H
#define __ADC_H

#include "main.h"

/* ADC���� */
#define ADC_ADC_S1                                ADC1
#define ADC_ADC_S1_CLK_ENABLE()                   do { __HAL_RCC_ADC12_CLK_ENABLE(); } while (0)
#define ADC_ADC_S1_CHY                            ADC_CHANNEL_11
#define ADC_ADC_S1_CHY_GPIO_PORT                  GPIOC
#define ADC_ADC_S1_CHY_GPIO_PIN                   GPIO_PIN_1
#define ADC_ADC_S1_CHY_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)


/* ADC���� */
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

/* �������� */
void adc1_init(void);                                                /* ��ʼ��ADC */
uint32_t adc_get_result(uint32_t channel);                          /* ��ȡADC��� */
uint32_t adc_get_result_average(uint32_t channel, uint8_t times);   /* ��ֵ�˲���ȡADC��� */
void adc_dma_init(uint32_t memory_base);                            /* ��ʼ��ADC DMA��ȡ */
void adc_dma_enable(uint32_t length);                               /* ����ADC DMA��ȡ */
void adc_nch_dma_init(uint32_t memory_base);                        /* ��ʼ����ͨ��ADC DMA��ȡ */
void adc_nch_dma_enable(uint32_t length);                           /* ������ͨ��ADC DMA��ȡ */
void adc_oversample_init(uint32_t ratio, uint32_t right_shift);     /* ��ʼ��ADC������ */

#endif
