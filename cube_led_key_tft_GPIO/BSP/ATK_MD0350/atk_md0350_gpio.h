/**
 ****************************************************************************************************
 * @file        atk_md0350_gpio.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MD0350模块GPIO接口驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 MiniSTM32 V4开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATK_MD0350_GPIO_H
#define __ATK_MD0350_GPIO_H

#include "main.h"
#include "tft.h"
/* 引脚定义 */
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

												
/* IO操作 */
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

/* 操作函数 */
void ATK_MD0350_GPIO_DATA(uint16_t data);
uint16_t ATK_MD0350_GPIO_READ_DATA(void);
void atk_md0350_gpio_init(void);                            /* ATK-MD0350模块GPIO接口初始化 */
void atk_md0350_gpio_write_cmd(uint16_t cmd);               /* ATK-MD0350模块通过GPIO接口写命令 */
void atk_md0350_gpio_write_dat(uint16_t dat);               /* ATK-MD0350模块通过GPIO接口写数据 */
void atk_md0350_gpio_write_reg(uint16_t reg, uint16_t dat); /* ATK-MD0350模块通过GPIO接口写寄存器 */
//uint16_t atk_md0350_gpio_read_dat(void);                    /* ATK-MD0350模块通过GPIO接口读数据 */
uint16_t tft_gpio_read_dat(void);

void TFT_input_Mode(void);
#endif
