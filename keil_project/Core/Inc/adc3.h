/**
 ****************************************************************************************************
 * @file        adc3.h
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

#ifndef __ADC3_H
#define __ADC3_H

#include "./SYSTEM/sys/sys.h"

/* �������� */
void adc3_init(void);                                               /* ��ʼ��ADC3 */
uint32_t adc3_get_result(uint32_t channel);                         /* ��ȡADC3��� */
uint32_t adc3_get_result_average(uint32_t channel, uint8_t times);  /* ��ֵ�˲���ȡADC3��� */
int32_t adc3_get_temperature(void);                                 /* ��ȡ�ڲ��¶ȴ�������� */

#endif
