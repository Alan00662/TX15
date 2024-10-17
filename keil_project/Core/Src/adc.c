/**
 ****************************************************************************************************
 * @file        adc.c
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

#include "adc.h"

/* ADC句柄 */
ADC_HandleTypeDef g_adc_handle = {0};
ADC_HandleTypeDef g_adc_dma_handle = {0};
ADC_HandleTypeDef g_adc_nch_dma_handle = {0};

/* 单通道ADC采集（DMA读取）相关变量 */
DMA_HandleTypeDef g_adc_dma_dma_handle = {0};
uint8_t g_adc_dma_sta = 0;
uint32_t g_adc_dma_memory_base;

/* 多通道ADC采集（DMA读取）相关变量 */
DMA_HandleTypeDef g_adc_nch_dma_dma_handle = {0};
uint8_t g_adc_nch_dma_sta = 0;
uint32_t g_adc_nch_dma_memory_base;

/**
 * @brief   初始化ADC
 * @param   无
 * @retval  无
 */
static void adc1_s1_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
	
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* 配置时钟 */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* 使能时钟 */
    ADC_ADC_S1_CLK_ENABLE();
    ADC_ADC_S1_CHY_GPIO_CLK_ENABLE();
    
    /* 选择时钟源 */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* 配置ADC采样引脚 */
    gpio_init_struct.Pin = ADC_ADC_S1_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_ADC_S1_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* 配置ADC */
    g_adc_handle.Instance = ADC_ADC_S1;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* 时钟源和时钟预分频系数 */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;                                          /* 分辨率 */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* 扫描转换模式 */
    g_adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* 转换结束产生的Flag */
    g_adc_handle.Init.LowPowerAutoWait = DISABLE;                                               /* 自动延迟转换 */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                                             /* 连续转换模式 */
    g_adc_handle.Init.NbrOfConversion = 1;                                                      /* 扫描转换模式下的Rank数量 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* 扫描转换模式下的间断转换模式 */
    g_adc_handle.Init.NbrOfDiscConversion = 1;                                                  /* 间断转换模式下一次转化的Rank数量 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* 转换外部触发源 */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* 转换外部触发源的有效沿 */
    g_adc_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                         /* 转换数据管理 */
    g_adc_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* 转换数据溢出覆写 */
    g_adc_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* 转换数据左移 */
    g_adc_handle.Init.OversamplingMode = DISABLE;                                               /* 过采样模式 */
    g_adc_handle.Init.Oversampling.Ratio = 0;                                                   /* 过采样率 */
    g_adc_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* 过采样右移 */
    g_adc_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* 过采样触发模式 */
    g_adc_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* 常规过采样模式 */
    HAL_ADC_Init(&g_adc_handle);
    
    /* ADC自动自校准 */
    HAL_ADCEx_Calibration_Start(&g_adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}


static void adc1_s2_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
	
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* 配置时钟 */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* 使能时钟 */
    ADC_ADC_S2_CLK_ENABLE();
    ADC_ADC_S2_CHY_GPIO_CLK_ENABLE();
    
    /* 选择时钟源 */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* 配置ADC采样引脚 */
    gpio_init_struct.Pin = ADC_ADC_S2_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_ADC_S2_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* 配置ADC */
    g_adc_handle.Instance = ADC_ADC_S2;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* 时钟源和时钟预分频系数 */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;                                          /* 分辨率 */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* 扫描转换模式 */
    g_adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* 转换结束产生的Flag */
    g_adc_handle.Init.LowPowerAutoWait = DISABLE;                                               /* 自动延迟转换 */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                                             /* 连续转换模式 */
    g_adc_handle.Init.NbrOfConversion = 1;                                                      /* 扫描转换模式下的Rank数量 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* 扫描转换模式下的间断转换模式 */
    g_adc_handle.Init.NbrOfDiscConversion = 1;                                                  /* 间断转换模式下一次转化的Rank数量 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* 转换外部触发源 */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* 转换外部触发源的有效沿 */
    g_adc_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                         /* 转换数据管理 */
    g_adc_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* 转换数据溢出覆写 */
    g_adc_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* 转换数据左移 */
    g_adc_handle.Init.OversamplingMode = DISABLE;                                               /* 过采样模式 */
    g_adc_handle.Init.Oversampling.Ratio = 0;                                                   /* 过采样率 */
    g_adc_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* 过采样右移 */
    g_adc_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* 过采样触发模式 */
    g_adc_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* 常规过采样模式 */
    HAL_ADC_Init(&g_adc_handle);
    
    /* ADC自动自校准 */
    HAL_ADCEx_Calibration_Start(&g_adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}

void adc1_init(void)
{
	adc1_s1_init();
	adc1_s2_init();
}
/**
 * @brief   获取ADC结果
 * @param   channel: ADC通道
 * @retval  ADC结果
 */
uint32_t adc_get_result(uint32_t channel)
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
    HAL_ADC_ConfigChannel(&g_adc_handle, &adc_channel_conf_struct);
    
    HAL_ADC_Start(&g_adc_handle);                                       /* 开启ADC转换 */
    HAL_ADC_PollForConversion(&g_adc_handle, HAL_MAX_DELAY);            /* 等待ADC转换结束 */
    result = HAL_ADC_GetValue(&g_adc_handle);                           /* 获取ADC转换结果 */
    HAL_ADC_Stop(&g_adc_handle);                                        /* 停止ADC转换 */
    
    return result;
}

/**
 * @brief   均值滤波获取ADC结果
 * @param   channel: ADC通道
 * @param   times: 均值滤波的原始数据个数
 * @retval  ADC结果
 */
uint32_t adc_get_result_average(uint32_t channel, uint8_t times)
{
    uint32_t sum_result = 0;
    uint8_t index;
    uint32_t result;
    
    for (index=0; index<times; index++)
    {
        sum_result += adc_get_result(channel);
    }
    
    result = sum_result / times;
    
    return result;
}

/**
 * @brief   初始化ADC DMA读取
 * @param   memory_base: 读取目标内存基地址
 * @retval  无
 */
void adc_dma_init(uint32_t memory_base)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* 配置时钟 */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* 使能时钟 */
    ADC_DMA_ADCX_CLK_ENABLE();
    ADC_DMA_ADCX_CHY_GPIO_CLK_ENABLE();
    ADC_DMA_ADCX_DMA_CLK_ENABLE();
    
    /* 选择时钟源 */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* 配置ADC采样引脚 */
    gpio_init_struct.Pin = ADC_DMA_ADCX_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_DMA_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* 配置DMA */
    g_adc_dma_dma_handle.Instance = ADC_DMA_ADCX_DMASX;
    g_adc_dma_dma_handle.Init.Request = ADC_DMA_ADCX_DMASX_REQ;
    g_adc_dma_dma_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    g_adc_dma_dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;
    g_adc_dma_dma_handle.Init.MemInc = DMA_MINC_ENABLE;
    g_adc_dma_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    g_adc_dma_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    g_adc_dma_dma_handle.Init.Mode = DMA_NORMAL;
    g_adc_dma_dma_handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    g_adc_dma_dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    g_adc_dma_dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
    g_adc_dma_dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;
    g_adc_dma_dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&g_adc_dma_dma_handle);
    HAL_NVIC_SetPriority(ADC_DMA_ADCX_DMASX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_DMA_ADCX_DMASX_IRQn);
    
    __HAL_LINKDMA(&g_adc_dma_handle, DMA_Handle, g_adc_dma_dma_handle);
    
    /* 配置ADC */
    g_adc_dma_handle.Instance = ADC_DMA_ADCX;
    g_adc_dma_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* 时钟源和时钟预分频系数 */
    g_adc_dma_handle.Init.Resolution = ADC_RESOLUTION_16B;                                          /* 分辨率 */
    g_adc_dma_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* 扫描转换模式 */
    g_adc_dma_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* 转换结束产生的Flag */
    g_adc_dma_handle.Init.LowPowerAutoWait = DISABLE;                                               /* 自动延迟转换 */
    g_adc_dma_handle.Init.ContinuousConvMode = ENABLE;                                              /* 连续转换模式 */
    g_adc_dma_handle.Init.NbrOfConversion = 1;                                                      /* 扫描转换模式下的Rank数量 */
    g_adc_dma_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* 扫描转换模式下的间断转换模式 */
    g_adc_dma_handle.Init.NbrOfDiscConversion = 1;                                                  /* 间断转换模式下一次转化的Rank数量 */
    g_adc_dma_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* 转换外部触发源 */
    g_adc_dma_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* 转换外部触发源的有效沿 */
    g_adc_dma_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_ONESHOT;                /* 转换数据管理 */
    g_adc_dma_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* 转换数据溢出覆写 */
    g_adc_dma_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* 转换数据左移 */
    g_adc_dma_handle.Init.OversamplingMode = DISABLE;                                               /* 过采样模式 */
    g_adc_dma_handle.Init.Oversampling.Ratio = 0;                                                   /* 过采样率 */
    g_adc_dma_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* 过采样右移 */
    g_adc_dma_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* 过采样触发模式 */
    g_adc_dma_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* 常规过采样模式 */
    HAL_ADC_Init(&g_adc_dma_handle);
    
    /* ADC自动自校准 */
    HAL_ADCEx_Calibration_Start(&g_adc_dma_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    
    g_adc_dma_memory_base = memory_base;
}

/**
 * @brief   开启ADC DMA读取
 * @param   length: DMA读取次数
 * @retval  无
 */
void adc_dma_enable(uint32_t length)
{
    ADC_ChannelConfTypeDef adc_channel_conf_struct = {0};
    
    /* 停止ADC DMA转换 */
    HAL_ADC_Stop_DMA(&g_adc_dma_handle);
    
    /* 配置ADC通道 */
    adc_channel_conf_struct.Channel = ADC_DMA_ADCX_CHY;                 /* 通道 */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_1;                  /* Rank编号 */
    adc_channel_conf_struct.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;  /* 采样时间 */
    adc_channel_conf_struct.SingleDiff = ADC_SINGLE_ENDED;              /* 采样输入模式 */
    adc_channel_conf_struct.OffsetNumber = ADC_OFFSET_NONE;             /* 偏移 */
    adc_channel_conf_struct.Offset = 0;                                 /* 偏移量 */
    adc_channel_conf_struct.OffsetRightShift = DISABLE;                 /* 偏移后右移 */
    adc_channel_conf_struct.OffsetSignedSaturation = DISABLE;           /* 符号饱和 */
    HAL_ADC_ConfigChannel(&g_adc_dma_handle, &adc_channel_conf_struct);
    
    /* 开启ADC DMA转换 */
    HAL_ADC_Start_DMA(&g_adc_dma_handle, (uint32_t *)g_adc_dma_memory_base, length);
}

/**
 * @brief   初始化多通道ADC DMA读取
 * @param   memory_base: 读取目标内存基地址
 * @retval  无
 */
void adc_nch_dma_init(uint32_t memory_base)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* 配置时钟 */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* 使能时钟 */
    ADC_NCH_DMA_ADCX_CLK_ENABLE();
    ADC_NCH_DMA_ADCX_CHA_GPIO_CLK_ENABLE();
    ADC_NCH_DMA_ADCX_CHB_GPIO_CLK_ENABLE();
    ADC_NCH_DMA_ADCX_DMA_CLK_ENABLE();
    
    /* 选择时钟源 */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* 配置ADC采样引脚 */
    gpio_init_struct.Pin = ADC_NCH_DMA_ADCX_CHA_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_NCH_DMA_ADCX_CHA_GPIO_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = ADC_NCH_DMA_ADCX_CHB_GPIO_PIN;
    HAL_GPIO_Init(ADC_NCH_DMA_ADCX_CHB_GPIO_PORT, &gpio_init_struct);
    
    /* 配置DMA */
    g_adc_nch_dma_dma_handle.Instance = ADC_NCH_DMA_ADCX_DMASX;
    g_adc_nch_dma_dma_handle.Init.Request = ADC_NCH_DMA_ADCX_DMASX_REQ;
    g_adc_nch_dma_dma_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    g_adc_nch_dma_dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;
    g_adc_nch_dma_dma_handle.Init.MemInc = DMA_MINC_ENABLE;
    g_adc_nch_dma_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    g_adc_nch_dma_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    g_adc_nch_dma_dma_handle.Init.Mode = DMA_NORMAL;
    g_adc_nch_dma_dma_handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    g_adc_nch_dma_dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    g_adc_nch_dma_dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
    g_adc_nch_dma_dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;
    g_adc_nch_dma_dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&g_adc_nch_dma_dma_handle);
    HAL_NVIC_SetPriority(ADC_NCH_DMA_ADCX_DMASX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_NCH_DMA_ADCX_DMASX_IRQn);
    
    __HAL_LINKDMA(&g_adc_nch_dma_handle, DMA_Handle, g_adc_nch_dma_dma_handle);
    
    /* 配置ADC */
    g_adc_nch_dma_handle.Instance = ADC_NCH_DMA_ADCX;
    g_adc_nch_dma_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* 时钟源和时钟预分频系数 */
    g_adc_nch_dma_handle.Init.Resolution = ADC_RESOLUTION_16B;                                          /* 分辨率 */
    g_adc_nch_dma_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;                                           /* 扫描转换模式 */
    g_adc_nch_dma_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* 转换结束产生的Flag */
    g_adc_nch_dma_handle.Init.LowPowerAutoWait = DISABLE;                                               /* 自动延迟转换 */
    g_adc_nch_dma_handle.Init.ContinuousConvMode = ENABLE;                                              /* 连续转换模式 */
    g_adc_nch_dma_handle.Init.NbrOfConversion = ADC_NCH_DMA_ADCX_CH_NUM;                                /* 扫描转换模式下的Rank数量 */
    g_adc_nch_dma_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* 扫描转换模式下的间断转换模式 */
    g_adc_nch_dma_handle.Init.NbrOfDiscConversion = 1;                                                  /* 间断转换模式下一次转化的Rank数量 */
    g_adc_nch_dma_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* 转换外部触发源 */
    g_adc_nch_dma_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* 转换外部触发源的有效沿 */
    g_adc_nch_dma_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_ONESHOT;                /* 转换数据管理 */
    g_adc_nch_dma_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* 转换数据溢出覆写 */
    g_adc_nch_dma_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* 转换数据左移 */
    g_adc_nch_dma_handle.Init.OversamplingMode = DISABLE;                                               /* 过采样模式 */
    g_adc_nch_dma_handle.Init.Oversampling.Ratio = 0;                                                   /* 过采样率 */
    g_adc_nch_dma_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* 过采样右移 */
    g_adc_nch_dma_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* 过采样触发模式 */
    g_adc_nch_dma_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* 常规过采样模式 */
    HAL_ADC_Init(&g_adc_nch_dma_handle);
    
    /* ADC自动自校准 */
    HAL_ADCEx_Calibration_Start(&g_adc_nch_dma_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    
    g_adc_nch_dma_memory_base = memory_base;
}

/**
 * @brief   开启多通道ADC DMA读取
 * @param   length: DMA读取次数
 * @retval  无
 */
void adc_nch_dma_enable(uint32_t length)
{
    ADC_ChannelConfTypeDef adc_channel_conf_struct = {0};
    
    /* 停止ADC DMA转换 */
    HAL_ADC_Stop_DMA(&g_adc_nch_dma_handle);
    
    /* 配置ADC通道 */
    adc_channel_conf_struct.Channel = ADC_NCH_DMA_ADCX_CHA;                 /* 通道 */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_1;                      /* Rank编号 */
    adc_channel_conf_struct.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;      /* 采样时间 */
    adc_channel_conf_struct.SingleDiff = ADC_SINGLE_ENDED;                  /* 采样输入模式 */
    adc_channel_conf_struct.OffsetNumber = ADC_OFFSET_NONE;                 /* 偏移 */
    adc_channel_conf_struct.Offset = 0;                                     /* 偏移量 */
    adc_channel_conf_struct.OffsetRightShift = DISABLE;                     /* 偏移后右移 */
    adc_channel_conf_struct.OffsetSignedSaturation = DISABLE;               /* 符号饱和 */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_channel_conf_struct);
    
    adc_channel_conf_struct.Channel = ADC_NCH_DMA_ADCX_CHB;                 /* 通道 */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_2;                      /* Rank编号 */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_channel_conf_struct);
    
    /* 开启ADC DMA转换 */
    HAL_ADC_Start_DMA(&g_adc_nch_dma_handle, (uint32_t *)g_adc_nch_dma_memory_base, length);
}

/**
 * @brief   HAL库ADC转换完成回调函数
 * @param   hadc: ADC句柄
 * @retval  无
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC_DMA_ADCX)
    {
        g_adc_dma_sta = 1;
    }
    else if (hadc->Instance == ADC_NCH_DMA_ADCX)
    {
        g_adc_nch_dma_sta = 1;
    }
}

/**
 * @brief   DMA中断服务函数
 * @param   无
 * @retval  无
 */
void ADC_DMA_ADCX_DMASX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_adc_dma_dma_handle);
}

/**
 * @brief   DMA中断服务函数
 * @param   无
 * @retval  无
 */
void ADC_NCH_DMA_ADCX_DMASX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_adc_nch_dma_dma_handle);
}

/**
 * @brief   初始化ADC过采样
 * @param   ratio: 过采样倍率
 * @param   right_shift: 过采样右移位数
 * @arg     ADC_RIGHTBITSHIFT_NONE: 无右移
 * @arg     ADC_RIGHTBITSHIFT_1: 右移1位
 * @arg     ADC_RIGHTBITSHIFT_2: 右移2位
 * @arg     ADC_RIGHTBITSHIFT_3: 右移3位
 * @arg     ADC_RIGHTBITSHIFT_4: 右移4位
 * @arg     ADC_RIGHTBITSHIFT_5: 右移5位
 * @arg     ADC_RIGHTBITSHIFT_6: 右移6位
 * @arg     ADC_RIGHTBITSHIFT_7: 右移7位
 * @arg     ADC_RIGHTBITSHIFT_8: 右移8位
 * @arg     ADC_RIGHTBITSHIFT_9: 右移9位
 * @arg     ADC_RIGHTBITSHIFT_10: 右移10位
 * @arg     ADC_RIGHTBITSHIFT_11: 右移11位
 * @retval  无
 */
void adc_oversample_init(uint32_t ratio, uint32_t right_shift)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* 配置时钟 */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* 使能时钟 */
    ADC_OS_ADCX_CLK_ENABLE();
    ADC_OS_ADCX_CHY_GPIO_CLK_ENABLE();
    
    /* 选择时钟源 */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* 配置ADC采样引脚 */
    gpio_init_struct.Pin = ADC_OS_ADCX_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_OS_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* 配置ADC */
    g_adc_handle.Instance = ADC_OS_ADCX;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* 时钟源和时钟预分频系数 */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_16B;                                          /* 分辨率 */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* 扫描转换模式 */
    g_adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* 转换结束产生的Flag */
    g_adc_handle.Init.LowPowerAutoWait = DISABLE;                                               /* 自动延迟转换 */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                                             /* 连续转换模式 */
    g_adc_handle.Init.NbrOfConversion = 1;                                                      /* 扫描转换模式下的Rank数量 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* 扫描转换模式下的间断转换模式 */
    g_adc_handle.Init.NbrOfDiscConversion = 1;                                                  /* 间断转换模式下一次转化的Rank数量 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* 转换外部触发源 */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* 转换外部触发源的有效沿 */
    g_adc_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                         /* 转换数据管理 */
    g_adc_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* 转换数据溢出覆写 */
    g_adc_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* 转换数据左移 */
    g_adc_handle.Init.OversamplingMode = ENABLE;                                                /* 过采样模式 */
    g_adc_handle.Init.Oversampling.Ratio = ratio;                                               /* 过采样率 */
    g_adc_handle.Init.Oversampling.RightBitShift = right_shift;                                 /* 过采样右移 */
    g_adc_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* 过采样触发模式 */
    g_adc_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* 常规过采样模式 */
    HAL_ADC_Init(&g_adc_handle);
    
    /* ADC自动自校准 */
    HAL_ADCEx_Calibration_Start(&g_adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}

