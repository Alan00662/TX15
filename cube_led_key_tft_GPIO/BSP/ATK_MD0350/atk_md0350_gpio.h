/**
 ****************************************************************************************************
 * @file        atk_md0350_gpio.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MD0350ģ��GPIO�ӿ���������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� MiniSTM32 V4������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATK_MD0350_GPIO_H
#define __ATK_MD0350_GPIO_H

#include "main.h"
#include "tft.h"
/* ���Ŷ��� */
#define ATK_MD0350_GPIO_RS_GPIO_PORT            GPIOI
#define ATK_MD0350_GPIO_RS_GPIO_PIN             GPIO_PIN_12
#define ATK_MD0350_GPIO_RS_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)
#define ATK_MD0350_GPIO_CS_GPIO_PORT            GPIOI
#define ATK_MD0350_GPIO_CS_GPIO_PIN             GPIO_PIN_13
#define ATK_MD0350_GPIO_CS_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOI_CLK_ENABLE(); }while(0)
#define ATK_MD0350_GPIO_RD_GPIO_PORT            GPIOK
#define ATK_MD0350_GPIO_RD_GPIO_PIN             GPIO_PIN_7
#define ATK_MD0350_GPIO_RD_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOK_CLK_ENABLE(); }while(0)
#define ATK_MD0350_GPIO_WR_GPIO_PORT            GPIOI
#define ATK_MD0350_GPIO_WR_GPIO_PIN             GPIO_PIN_14
#define ATK_MD0350_GPIO_WR_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOI_CLK_ENABLE(); }while(0)

//#define ATK_MD0350_GPIO_DATA_GPIO_PORT          GPIOB
//#define ATK_MD0350_GPIO_DATA_GPIO_PIN           GPIO_PIN_All
//#define ATK_MD0350_GPIO_DATA_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOB_CLK_ENABLE();   \
//                                                    __HAL_RCC_AFIO_CLK_ENABLE();    \
//                                                    __HAL_AFIO_REMAP_SWJ_NOJTAG();  \
//                                                }while(0)
//#define ATK_MD0350_GPIO_DATA_GPIO_PORT          GPIOJ

												
/* IO���� */
#define ATK_MD0350_GPIO_RS(x)        do{ x ?                                                                             \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_RS_GPIO_PORT, ATK_MD0350_GPIO_RS_GPIO_PIN, GPIO_PIN_SET):     \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_RS_GPIO_PORT, ATK_MD0350_GPIO_RS_GPIO_PIN, GPIO_PIN_RESET);   \
									} while (0)
#define ATK_MD0350_GPIO_CS(x)        do{ x ?                                                                             \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_CS_GPIO_PORT, ATK_MD0350_GPIO_CS_GPIO_PIN, GPIO_PIN_SET):     \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_CS_GPIO_PORT, ATK_MD0350_GPIO_CS_GPIO_PIN, GPIO_PIN_RESET);   \
									} while (0)
#define ATK_MD0350_GPIO_RD(x)        do{ x ?                                                                             \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_RD_GPIO_PORT, ATK_MD0350_GPIO_RD_GPIO_PIN, GPIO_PIN_SET):     \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_RD_GPIO_PORT, ATK_MD0350_GPIO_RD_GPIO_PIN, GPIO_PIN_RESET);   \
									} while (0)
#define ATK_MD0350_GPIO_WR(x)        do{ x ?                                                                             \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_WR_GPIO_PORT, ATK_MD0350_GPIO_WR_GPIO_PIN, GPIO_PIN_SET):     \
										HAL_GPIO_WritePin(ATK_MD0350_GPIO_WR_GPIO_PORT, ATK_MD0350_GPIO_WR_GPIO_PIN, GPIO_PIN_RESET);   \
									} while (0)
//#define ATK_MD0350_GPIO_DATA(x)      do{ ATK_MD0350_GPIO_DATA_GPIO_PORT->ODR = x; }while(0)
//#define ATK_MD0350_GPIO_READ_DATA()  ATK_MD0350_GPIO_DATA_GPIO_PORT->IDR

/* �������� */
void ATK_MD0350_GPIO_DATA(uint16_t data);
uint16_t ATK_MD0350_GPIO_READ_DATA(void);
void atk_md0350_gpio_init(void);                            /* ATK-MD0350ģ��GPIO�ӿڳ�ʼ�� */
void atk_md0350_gpio_write_cmd(uint16_t cmd);               /* ATK-MD0350ģ��ͨ��GPIO�ӿ�д���� */
void atk_md0350_gpio_write_dat(uint16_t dat);               /* ATK-MD0350ģ��ͨ��GPIO�ӿ�д���� */
void atk_md0350_gpio_write_reg(uint16_t reg, uint16_t dat); /* ATK-MD0350ģ��ͨ��GPIO�ӿ�д�Ĵ��� */
//uint16_t atk_md0350_gpio_read_dat(void);                    /* ATK-MD0350ģ��ͨ��GPIO�ӿڶ����� */
uint16_t tft_gpio_read_dat(void);

void TFT_input_Mode(void);
#endif
