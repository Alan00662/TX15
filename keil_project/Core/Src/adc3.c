/**
 ****************************************************************************************************
 * @file        adc3.c
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

#include "adc3.h"

/* ADC句柄 */
ADC_HandleTypeDef g_adc3_handle = {0};

/**
 * @brief   初始化ADC3
 * @param   无
 * @retval  无
 */
void adc3_init(void)
{
    /* 配置时钟 */
	    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* 使能时钟 */
    __HAL_RCC_ADC3_CLK_ENABLE();
    
    /* 选择时钟源 */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* 配置ADC */
    g_adc3_handle.Instance = ADC3;
    g_adc3_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                   /* 时钟源和时钟预分频系数 */
    g_adc3_handle.Init.Resolution = ADC_RESOLUTION_16B;                                         /* 分辨率 */
    g_adc3_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                         /* 扫描转换模式 */
    g_adc3_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                      /* 转换结束产生的Flag */
    g_adc3_handle.Init.LowPowerAutoWait = DISABLE;                                              /* 自动延迟转换 */
    g_adc3_handle.Init.ContinuousConvMode = DISABLE;                                            /* 连续转换模式 */
    g_adc3_handle.Init.NbrOfConversion = 1;                                                     /* 扫描转换模式下的Rank数量 */
    g_adc3_handle.Init.DiscontinuousConvMode = DISABLE;                                         /* 扫描转换模式下的间断转换模式 */
    g_adc3_handle.Init.NbrOfDiscConversion = 1;                                                 /* 间断转换模式下一次转化的Rank数量 */
    g_adc3_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                   /* 转换外部触发源 */
    g_adc3_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                    /* 转换外部触发源的有效沿 */
    g_adc3_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                        /* 转换数据管理 */
    g_adc3_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                      /* 转换数据溢出覆写 */
    g_adc3_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                    /* 转换数据左移 */
    g_adc3_handle.Init.OversamplingMode = DISABLE;                                              /* 过采样模式 */
    g_adc3_handle.Init.Oversampling.Ratio = 0;                                                  /* 过采样率 */
    g_adc3_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                     /* 过采样右移 */
    g_adc3_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;           /* 过采样触发模式 */
    g_adc3_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE; /* 常规过采样模式 */
    HAL_ADC_Init(&g_adc3_handle);
    
    /* ADC自动自校准 */
    HAL_ADCEx_Calibration_Start(&g_adc3_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}

/**
 * @brief   获取ADC3结果
 * @param   channel: ADC3通道
 * @retval  ADC结果
 */
uint32_t adc3_get_result(uint32_t channel)
{
    ADC_ChannelConfTypeDef adc_channel_conf_struct = {0};
    uint32_t result;
    
    /* 配置ADC通道 */
    adc_channel_conf_struct.Channel = channel;                          /* 通道 */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_1;                  /* Rank编号 */
    adc_channel_conf_struct.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;  /* 采样时间 */
    adc_channel_conf_struct.SingleDiff = ADC_SINGLE_ENDED;              /* 采样输入模式 */
    adc_channel_conf_struct.OffsetNumber = ADC_OFFSET_NONE;             /* 偏移 */
    adc_channel_conf_struct.Offset = 0;                                 /* 偏移量 */
    adc_channel_conf_struct.OffsetRightShift = DISABLE;                 /* 偏移后右移 */
    adc_channel_conf_struct.OffsetSignedSaturation = DISABLE;           /* 符号饱和 */
    HAL_ADC_ConfigChannel(&g_adc3_handle, &adc_channel_conf_struct);
    
    HAL_ADC_Start(&g_adc3_handle);                                      /* 开启ADC转换 */
    HAL_ADC_PollForConversion(&g_adc3_handle, HAL_MAX_DELAY);           /* 等待ADC转换结束 */
    result = HAL_ADC_GetValue(&g_adc3_handle);                          /* 获取ADC转换结果 */
    HAL_ADC_Stop(&g_adc3_handle);                                       /* 停止ADC转换 */
    
    return result;
}

/**
 * @brief   均值滤波获取ADC3结果
 * @param   channel: ADC3通道
 * @param   times: 均值滤波的原始数据个数
 * @retval  ADC结果
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
 * @brief   获取内部温度传感器结果
 * @param   无
 * @retval  温度值（单位：摄氏度）
 */
int32_t adc3_get_temperature(void)
{
    uint32_t result;
    
    result = adc3_get_result_average(ADC_CHANNEL_TEMPSENSOR, 10);
    return __HAL_ADC_CALC_TEMPERATURE(VDD_VALUE, result, ADC_RESOLUTION_16B);
}
