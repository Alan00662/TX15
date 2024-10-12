
#ifndef __TFT_H
#define __TFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"


#define TFT_WR_GPIO_PORT            GPIOI
#define TFT_WR_GPIO_PIN             GPIO_PIN_14
//#define TFT_WR_GPIO_AF              GPIO_AF14_LTDC
#define TFT_WR_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define TFT_RD_GPIO_PORT            GPIOK
#define TFT_RD_GPIO_PIN             GPIO_PIN_7
//#define TFT_RD_GPIO_AF              GPIO_AF14_LTDC
#define TFT_RD_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOK_CLK_ENABLE(); } while (0)

#define TFT_BL_GPIO_PORT            GPIOG
#define TFT_BL_GPIO_PIN             GPIO_PIN_10
#define TFT_BL_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOG_CLK_ENABLE(); } while (0)

#define TFT_CS_GPIO_PORT            GPIOI
#define TFT_CS_GPIO_PIN             GPIO_PIN_13
//#define TFT_CS_GPIO_AF              GPIO_AF14_LTDC
#define TFT_CS_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define TFT_RS_GPIO_PORT            GPIOI
#define TFT_RS_GPIO_PIN             GPIO_PIN_12
//#define TFT_RS_GPIO_AF              GPIO_AF14_LTDC
#define TFT_RS_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

/* LCDÒý½Å²Ù×÷ */
#define TFT_BL(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

void TFT_Init(void);
#ifdef __cplusplus
}
#endif

#endif 
