/**
 ****************************************************************************************************
 * @file        adc3.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       ADC3��������
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

#include "adc3.h"

/* ADC��� */
ADC_HandleTypeDef g_adc3_handle = {0};

/**
 * @brief   ��ʼ��ADC3
 * @param   ��
 * @retval  ��
 */
void adc3_init(void)
{
    /* ����ʱ�� */
	    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* ʹ��ʱ�� */
    __HAL_RCC_ADC3_CLK_ENABLE();
    
    /* ѡ��ʱ��Դ */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* ����ADC */
    g_adc3_handle.Instance = ADC3;
    g_adc3_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                   /* ʱ��Դ��ʱ��Ԥ��Ƶϵ�� */
    g_adc3_handle.Init.Resolution = ADC_RESOLUTION_16B;                                         /* �ֱ��� */
    g_adc3_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                         /* ɨ��ת��ģʽ */
    g_adc3_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                      /* ת������������Flag */
    g_adc3_handle.Init.LowPowerAutoWait = DISABLE;                                              /* �Զ��ӳ�ת�� */
    g_adc3_handle.Init.ContinuousConvMode = DISABLE;                                            /* ����ת��ģʽ */
    g_adc3_handle.Init.NbrOfConversion = 1;                                                     /* ɨ��ת��ģʽ�µ�Rank���� */
    g_adc3_handle.Init.DiscontinuousConvMode = DISABLE;                                         /* ɨ��ת��ģʽ�µļ��ת��ģʽ */
    g_adc3_handle.Init.NbrOfDiscConversion = 1;                                                 /* ���ת��ģʽ��һ��ת����Rank���� */
    g_adc3_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                   /* ת���ⲿ����Դ */
    g_adc3_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                    /* ת���ⲿ����Դ����Ч�� */
    g_adc3_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                        /* ת�����ݹ��� */
    g_adc3_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                      /* ת�����������д */
    g_adc3_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                    /* ת���������� */
    g_adc3_handle.Init.OversamplingMode = DISABLE;                                              /* ������ģʽ */
    g_adc3_handle.Init.Oversampling.Ratio = 0;                                                  /* �������� */
    g_adc3_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                     /* ���������� */
    g_adc3_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;           /* ����������ģʽ */
    g_adc3_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE; /* ���������ģʽ */
    HAL_ADC_Init(&g_adc3_handle);
    
    /* ADC�Զ���У׼ */
    HAL_ADCEx_Calibration_Start(&g_adc3_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}

/**
 * @brief   ��ȡADC3���
 * @param   channel: ADC3ͨ��
 * @retval  ADC���
 */
uint32_t adc3_get_result(uint32_t channel)
{
    ADC_ChannelConfTypeDef adc_channel_conf_struct = {0};
    uint32_t result;
    
    /* ����ADCͨ�� */
    adc_channel_conf_struct.Channel = channel;                          /* ͨ�� */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_1;                  /* Rank��� */
    adc_channel_conf_struct.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;  /* ����ʱ�� */
    adc_channel_conf_struct.SingleDiff = ADC_SINGLE_ENDED;              /* ��������ģʽ */
    adc_channel_conf_struct.OffsetNumber = ADC_OFFSET_NONE;             /* ƫ�� */
    adc_channel_conf_struct.Offset = 0;                                 /* ƫ���� */
    adc_channel_conf_struct.OffsetRightShift = DISABLE;                 /* ƫ�ƺ����� */
    adc_channel_conf_struct.OffsetSignedSaturation = DISABLE;           /* ���ű��� */
    HAL_ADC_ConfigChannel(&g_adc3_handle, &adc_channel_conf_struct);
    
    HAL_ADC_Start(&g_adc3_handle);                                      /* ����ADCת�� */
    HAL_ADC_PollForConversion(&g_adc3_handle, HAL_MAX_DELAY);           /* �ȴ�ADCת������ */
    result = HAL_ADC_GetValue(&g_adc3_handle);                          /* ��ȡADCת����� */
    HAL_ADC_Stop(&g_adc3_handle);                                       /* ֹͣADCת�� */
    
    return result;
}

/**
 * @brief   ��ֵ�˲���ȡADC3���
 * @param   channel: ADC3ͨ��
 * @param   times: ��ֵ�˲���ԭʼ���ݸ���
 * @retval  ADC���
 */
uint32_t adc3_get_result_average(uint32_t channel, uint8_t times)
{
    uint32_t sum_result = 0;
    uint8_t index;
    uint32_t result;
    
    for (index=0; index<times; index++)
    {
        sum_result += adc3_get_result(channel);
    }
    
    result = sum_result / times;
    
    return result;
}

/**
 * @brief   ��ȡ�ڲ��¶ȴ��������
 * @param   ��
 * @retval  �¶�ֵ����λ�����϶ȣ�
 */
int32_t adc3_get_temperature(void)
{
    uint32_t result;
    
    result = adc3_get_result_average(ADC_CHANNEL_TEMPSENSOR, 10);
    return __HAL_ADC_CALC_TEMPERATURE(VDD_VALUE, result, ADC_RESOLUTION_16B);
}
