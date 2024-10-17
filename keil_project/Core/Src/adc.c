/**
 ****************************************************************************************************
 * @file        adc.c
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

#include "adc.h"

/* ADC��� */
ADC_HandleTypeDef g_adc_handle = {0};
ADC_HandleTypeDef g_adc_dma_handle = {0};
ADC_HandleTypeDef g_adc_nch_dma_handle = {0};

/* ��ͨ��ADC�ɼ���DMA��ȡ����ر��� */
DMA_HandleTypeDef g_adc_dma_dma_handle = {0};
uint8_t g_adc_dma_sta = 0;
uint32_t g_adc_dma_memory_base;

/* ��ͨ��ADC�ɼ���DMA��ȡ����ر��� */
DMA_HandleTypeDef g_adc_nch_dma_dma_handle = {0};
uint8_t g_adc_nch_dma_sta = 0;
uint32_t g_adc_nch_dma_memory_base;

/**
 * @brief   ��ʼ��ADC
 * @param   ��
 * @retval  ��
 */
static void adc1_s1_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
	
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* ����ʱ�� */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* ʹ��ʱ�� */
    ADC_ADC_S1_CLK_ENABLE();
    ADC_ADC_S1_CHY_GPIO_CLK_ENABLE();
    
    /* ѡ��ʱ��Դ */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* ����ADC�������� */
    gpio_init_struct.Pin = ADC_ADC_S1_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_ADC_S1_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* ����ADC */
    g_adc_handle.Instance = ADC_ADC_S1;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* ʱ��Դ��ʱ��Ԥ��Ƶϵ�� */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;                                          /* �ֱ��� */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* ɨ��ת��ģʽ */
    g_adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* ת������������Flag */
    g_adc_handle.Init.LowPowerAutoWait = DISABLE;                                               /* �Զ��ӳ�ת�� */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                                             /* ����ת��ģʽ */
    g_adc_handle.Init.NbrOfConversion = 1;                                                      /* ɨ��ת��ģʽ�µ�Rank���� */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* ɨ��ת��ģʽ�µļ��ת��ģʽ */
    g_adc_handle.Init.NbrOfDiscConversion = 1;                                                  /* ���ת��ģʽ��һ��ת����Rank���� */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* ת���ⲿ����Դ */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* ת���ⲿ����Դ����Ч�� */
    g_adc_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                         /* ת�����ݹ��� */
    g_adc_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* ת�����������д */
    g_adc_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* ת���������� */
    g_adc_handle.Init.OversamplingMode = DISABLE;                                               /* ������ģʽ */
    g_adc_handle.Init.Oversampling.Ratio = 0;                                                   /* �������� */
    g_adc_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* ���������� */
    g_adc_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* ����������ģʽ */
    g_adc_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* ���������ģʽ */
    HAL_ADC_Init(&g_adc_handle);
    
    /* ADC�Զ���У׼ */
    HAL_ADCEx_Calibration_Start(&g_adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}


static void adc1_s2_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
	
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* ����ʱ�� */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* ʹ��ʱ�� */
    ADC_ADC_S2_CLK_ENABLE();
    ADC_ADC_S2_CHY_GPIO_CLK_ENABLE();
    
    /* ѡ��ʱ��Դ */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* ����ADC�������� */
    gpio_init_struct.Pin = ADC_ADC_S2_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_ADC_S2_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* ����ADC */
    g_adc_handle.Instance = ADC_ADC_S2;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* ʱ��Դ��ʱ��Ԥ��Ƶϵ�� */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;                                          /* �ֱ��� */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* ɨ��ת��ģʽ */
    g_adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* ת������������Flag */
    g_adc_handle.Init.LowPowerAutoWait = DISABLE;                                               /* �Զ��ӳ�ת�� */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                                             /* ����ת��ģʽ */
    g_adc_handle.Init.NbrOfConversion = 1;                                                      /* ɨ��ת��ģʽ�µ�Rank���� */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* ɨ��ת��ģʽ�µļ��ת��ģʽ */
    g_adc_handle.Init.NbrOfDiscConversion = 1;                                                  /* ���ת��ģʽ��һ��ת����Rank���� */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* ת���ⲿ����Դ */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* ת���ⲿ����Դ����Ч�� */
    g_adc_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                         /* ת�����ݹ��� */
    g_adc_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* ת�����������д */
    g_adc_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* ת���������� */
    g_adc_handle.Init.OversamplingMode = DISABLE;                                               /* ������ģʽ */
    g_adc_handle.Init.Oversampling.Ratio = 0;                                                   /* �������� */
    g_adc_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* ���������� */
    g_adc_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* ����������ģʽ */
    g_adc_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* ���������ģʽ */
    HAL_ADC_Init(&g_adc_handle);
    
    /* ADC�Զ���У׼ */
    HAL_ADCEx_Calibration_Start(&g_adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}

void adc1_init(void)
{
	adc1_s1_init();
	adc1_s2_init();
}
/**
 * @brief   ��ȡADC���
 * @param   channel: ADCͨ��
 * @retval  ADC���
 */
uint32_t adc_get_result(uint32_t channel)
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
    HAL_ADC_ConfigChannel(&g_adc_handle, &adc_channel_conf_struct);
    
    HAL_ADC_Start(&g_adc_handle);                                       /* ����ADCת�� */
    HAL_ADC_PollForConversion(&g_adc_handle, HAL_MAX_DELAY);            /* �ȴ�ADCת������ */
    result = HAL_ADC_GetValue(&g_adc_handle);                           /* ��ȡADCת����� */
    HAL_ADC_Stop(&g_adc_handle);                                        /* ֹͣADCת�� */
    
    return result;
}

/**
 * @brief   ��ֵ�˲���ȡADC���
 * @param   channel: ADCͨ��
 * @param   times: ��ֵ�˲���ԭʼ���ݸ���
 * @retval  ADC���
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
 * @brief   ��ʼ��ADC DMA��ȡ
 * @param   memory_base: ��ȡĿ���ڴ����ַ
 * @retval  ��
 */
void adc_dma_init(uint32_t memory_base)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* ����ʱ�� */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* ʹ��ʱ�� */
    ADC_DMA_ADCX_CLK_ENABLE();
    ADC_DMA_ADCX_CHY_GPIO_CLK_ENABLE();
    ADC_DMA_ADCX_DMA_CLK_ENABLE();
    
    /* ѡ��ʱ��Դ */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* ����ADC�������� */
    gpio_init_struct.Pin = ADC_DMA_ADCX_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_DMA_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* ����DMA */
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
    
    /* ����ADC */
    g_adc_dma_handle.Instance = ADC_DMA_ADCX;
    g_adc_dma_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* ʱ��Դ��ʱ��Ԥ��Ƶϵ�� */
    g_adc_dma_handle.Init.Resolution = ADC_RESOLUTION_16B;                                          /* �ֱ��� */
    g_adc_dma_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* ɨ��ת��ģʽ */
    g_adc_dma_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* ת������������Flag */
    g_adc_dma_handle.Init.LowPowerAutoWait = DISABLE;                                               /* �Զ��ӳ�ת�� */
    g_adc_dma_handle.Init.ContinuousConvMode = ENABLE;                                              /* ����ת��ģʽ */
    g_adc_dma_handle.Init.NbrOfConversion = 1;                                                      /* ɨ��ת��ģʽ�µ�Rank���� */
    g_adc_dma_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* ɨ��ת��ģʽ�µļ��ת��ģʽ */
    g_adc_dma_handle.Init.NbrOfDiscConversion = 1;                                                  /* ���ת��ģʽ��һ��ת����Rank���� */
    g_adc_dma_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* ת���ⲿ����Դ */
    g_adc_dma_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* ת���ⲿ����Դ����Ч�� */
    g_adc_dma_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_ONESHOT;                /* ת�����ݹ��� */
    g_adc_dma_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* ת�����������д */
    g_adc_dma_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* ת���������� */
    g_adc_dma_handle.Init.OversamplingMode = DISABLE;                                               /* ������ģʽ */
    g_adc_dma_handle.Init.Oversampling.Ratio = 0;                                                   /* �������� */
    g_adc_dma_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* ���������� */
    g_adc_dma_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* ����������ģʽ */
    g_adc_dma_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* ���������ģʽ */
    HAL_ADC_Init(&g_adc_dma_handle);
    
    /* ADC�Զ���У׼ */
    HAL_ADCEx_Calibration_Start(&g_adc_dma_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    
    g_adc_dma_memory_base = memory_base;
}

/**
 * @brief   ����ADC DMA��ȡ
 * @param   length: DMA��ȡ����
 * @retval  ��
 */
void adc_dma_enable(uint32_t length)
{
    ADC_ChannelConfTypeDef adc_channel_conf_struct = {0};
    
    /* ֹͣADC DMAת�� */
    HAL_ADC_Stop_DMA(&g_adc_dma_handle);
    
    /* ����ADCͨ�� */
    adc_channel_conf_struct.Channel = ADC_DMA_ADCX_CHY;                 /* ͨ�� */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_1;                  /* Rank��� */
    adc_channel_conf_struct.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;  /* ����ʱ�� */
    adc_channel_conf_struct.SingleDiff = ADC_SINGLE_ENDED;              /* ��������ģʽ */
    adc_channel_conf_struct.OffsetNumber = ADC_OFFSET_NONE;             /* ƫ�� */
    adc_channel_conf_struct.Offset = 0;                                 /* ƫ���� */
    adc_channel_conf_struct.OffsetRightShift = DISABLE;                 /* ƫ�ƺ����� */
    adc_channel_conf_struct.OffsetSignedSaturation = DISABLE;           /* ���ű��� */
    HAL_ADC_ConfigChannel(&g_adc_dma_handle, &adc_channel_conf_struct);
    
    /* ����ADC DMAת�� */
    HAL_ADC_Start_DMA(&g_adc_dma_handle, (uint32_t *)g_adc_dma_memory_base, length);
}

/**
 * @brief   ��ʼ����ͨ��ADC DMA��ȡ
 * @param   memory_base: ��ȡĿ���ڴ����ַ
 * @retval  ��
 */
void adc_nch_dma_init(uint32_t memory_base)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* ����ʱ�� */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* ʹ��ʱ�� */
    ADC_NCH_DMA_ADCX_CLK_ENABLE();
    ADC_NCH_DMA_ADCX_CHA_GPIO_CLK_ENABLE();
    ADC_NCH_DMA_ADCX_CHB_GPIO_CLK_ENABLE();
    ADC_NCH_DMA_ADCX_DMA_CLK_ENABLE();
    
    /* ѡ��ʱ��Դ */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* ����ADC�������� */
    gpio_init_struct.Pin = ADC_NCH_DMA_ADCX_CHA_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_NCH_DMA_ADCX_CHA_GPIO_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = ADC_NCH_DMA_ADCX_CHB_GPIO_PIN;
    HAL_GPIO_Init(ADC_NCH_DMA_ADCX_CHB_GPIO_PORT, &gpio_init_struct);
    
    /* ����DMA */
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
    
    /* ����ADC */
    g_adc_nch_dma_handle.Instance = ADC_NCH_DMA_ADCX;
    g_adc_nch_dma_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* ʱ��Դ��ʱ��Ԥ��Ƶϵ�� */
    g_adc_nch_dma_handle.Init.Resolution = ADC_RESOLUTION_16B;                                          /* �ֱ��� */
    g_adc_nch_dma_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;                                           /* ɨ��ת��ģʽ */
    g_adc_nch_dma_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* ת������������Flag */
    g_adc_nch_dma_handle.Init.LowPowerAutoWait = DISABLE;                                               /* �Զ��ӳ�ת�� */
    g_adc_nch_dma_handle.Init.ContinuousConvMode = ENABLE;                                              /* ����ת��ģʽ */
    g_adc_nch_dma_handle.Init.NbrOfConversion = ADC_NCH_DMA_ADCX_CH_NUM;                                /* ɨ��ת��ģʽ�µ�Rank���� */
    g_adc_nch_dma_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* ɨ��ת��ģʽ�µļ��ת��ģʽ */
    g_adc_nch_dma_handle.Init.NbrOfDiscConversion = 1;                                                  /* ���ת��ģʽ��һ��ת����Rank���� */
    g_adc_nch_dma_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* ת���ⲿ����Դ */
    g_adc_nch_dma_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* ת���ⲿ����Դ����Ч�� */
    g_adc_nch_dma_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_ONESHOT;                /* ת�����ݹ��� */
    g_adc_nch_dma_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* ת�����������д */
    g_adc_nch_dma_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* ת���������� */
    g_adc_nch_dma_handle.Init.OversamplingMode = DISABLE;                                               /* ������ģʽ */
    g_adc_nch_dma_handle.Init.Oversampling.Ratio = 0;                                                   /* �������� */
    g_adc_nch_dma_handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;                      /* ���������� */
    g_adc_nch_dma_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* ����������ģʽ */
    g_adc_nch_dma_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* ���������ģʽ */
    HAL_ADC_Init(&g_adc_nch_dma_handle);
    
    /* ADC�Զ���У׼ */
    HAL_ADCEx_Calibration_Start(&g_adc_nch_dma_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    
    g_adc_nch_dma_memory_base = memory_base;
}

/**
 * @brief   ������ͨ��ADC DMA��ȡ
 * @param   length: DMA��ȡ����
 * @retval  ��
 */
void adc_nch_dma_enable(uint32_t length)
{
    ADC_ChannelConfTypeDef adc_channel_conf_struct = {0};
    
    /* ֹͣADC DMAת�� */
    HAL_ADC_Stop_DMA(&g_adc_nch_dma_handle);
    
    /* ����ADCͨ�� */
    adc_channel_conf_struct.Channel = ADC_NCH_DMA_ADCX_CHA;                 /* ͨ�� */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_1;                      /* Rank��� */
    adc_channel_conf_struct.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;      /* ����ʱ�� */
    adc_channel_conf_struct.SingleDiff = ADC_SINGLE_ENDED;                  /* ��������ģʽ */
    adc_channel_conf_struct.OffsetNumber = ADC_OFFSET_NONE;                 /* ƫ�� */
    adc_channel_conf_struct.Offset = 0;                                     /* ƫ���� */
    adc_channel_conf_struct.OffsetRightShift = DISABLE;                     /* ƫ�ƺ����� */
    adc_channel_conf_struct.OffsetSignedSaturation = DISABLE;               /* ���ű��� */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_channel_conf_struct);
    
    adc_channel_conf_struct.Channel = ADC_NCH_DMA_ADCX_CHB;                 /* ͨ�� */
    adc_channel_conf_struct.Rank = ADC_REGULAR_RANK_2;                      /* Rank��� */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_channel_conf_struct);
    
    /* ����ADC DMAת�� */
    HAL_ADC_Start_DMA(&g_adc_nch_dma_handle, (uint32_t *)g_adc_nch_dma_memory_base, length);
}

/**
 * @brief   HAL��ADCת����ɻص�����
 * @param   hadc: ADC���
 * @retval  ��
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
 * @brief   DMA�жϷ�����
 * @param   ��
 * @retval  ��
 */
void ADC_DMA_ADCX_DMASX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_adc_dma_dma_handle);
}

/**
 * @brief   DMA�жϷ�����
 * @param   ��
 * @retval  ��
 */
void ADC_NCH_DMA_ADCX_DMASX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&g_adc_nch_dma_dma_handle);
}

/**
 * @brief   ��ʼ��ADC������
 * @param   ratio: ����������
 * @param   right_shift: ����������λ��
 * @arg     ADC_RIGHTBITSHIFT_NONE: ������
 * @arg     ADC_RIGHTBITSHIFT_1: ����1λ
 * @arg     ADC_RIGHTBITSHIFT_2: ����2λ
 * @arg     ADC_RIGHTBITSHIFT_3: ����3λ
 * @arg     ADC_RIGHTBITSHIFT_4: ����4λ
 * @arg     ADC_RIGHTBITSHIFT_5: ����5λ
 * @arg     ADC_RIGHTBITSHIFT_6: ����6λ
 * @arg     ADC_RIGHTBITSHIFT_7: ����7λ
 * @arg     ADC_RIGHTBITSHIFT_8: ����8λ
 * @arg     ADC_RIGHTBITSHIFT_9: ����9λ
 * @arg     ADC_RIGHTBITSHIFT_10: ����10λ
 * @arg     ADC_RIGHTBITSHIFT_11: ����11λ
 * @retval  ��
 */
void adc_oversample_init(uint32_t ratio, uint32_t right_shift)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef rcc_periph_clk_init_struct = {0};
    /* ����ʱ�� */
    rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    rcc_periph_clk_init_struct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
    
    /* ʹ��ʱ�� */
    ADC_OS_ADCX_CLK_ENABLE();
    ADC_OS_ADCX_CHY_GPIO_CLK_ENABLE();
    
    /* ѡ��ʱ��Դ */
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);
    
    /* ����ADC�������� */
    gpio_init_struct.Pin = ADC_OS_ADCX_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_OS_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* ����ADC */
    g_adc_handle.Instance = ADC_OS_ADCX;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;                                    /* ʱ��Դ��ʱ��Ԥ��Ƶϵ�� */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_16B;                                          /* �ֱ��� */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;                                          /* ɨ��ת��ģʽ */
    g_adc_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;                                       /* ת������������Flag */
    g_adc_handle.Init.LowPowerAutoWait = DISABLE;                                               /* �Զ��ӳ�ת�� */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                                             /* ����ת��ģʽ */
    g_adc_handle.Init.NbrOfConversion = 1;                                                      /* ɨ��ת��ģʽ�µ�Rank���� */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                                          /* ɨ��ת��ģʽ�µļ��ת��ģʽ */
    g_adc_handle.Init.NbrOfDiscConversion = 1;                                                  /* ���ת��ģʽ��һ��ת����Rank���� */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                                    /* ת���ⲿ����Դ */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;                     /* ת���ⲿ����Դ����Ч�� */
    g_adc_handle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;                         /* ת�����ݹ��� */
    g_adc_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;                                       /* ת�����������д */
    g_adc_handle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;                                     /* ת���������� */
    g_adc_handle.Init.OversamplingMode = ENABLE;                                                /* ������ģʽ */
    g_adc_handle.Init.Oversampling.Ratio = ratio;                                               /* �������� */
    g_adc_handle.Init.Oversampling.RightBitShift = right_shift;                                 /* ���������� */
    g_adc_handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;            /* ����������ģʽ */
    g_adc_handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;  /* ���������ģʽ */
    HAL_ADC_Init(&g_adc_handle);
    
    /* ADC�Զ���У׼ */
    HAL_ADCEx_Calibration_Start(&g_adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
}

