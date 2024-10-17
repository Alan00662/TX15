#include "adc1.h"
#include "adc_comom.h"
uint32_t adc_s1 = 0;
uint32_t adc_s2 = 0;

uint32_t adc_scan_tick = 0;
void ADC_scan_Loop(void)
{
	if((HAL_GetTick() - adc_scan_tick) > 1)
	{
		adc_s1 = adc1_get_result_average(ADC_ADC_S1_CHY,10);
		adc_s2 = adc1_get_result_average(ADC_ADC_S2_CHY,10);
        adc_scan_tick = HAL_GetTick();
	}
}