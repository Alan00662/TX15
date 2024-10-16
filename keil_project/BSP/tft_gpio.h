
#ifndef __TFT_GPIO_H
#define __TFT_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#if BackLight_USE_PWM == 0 
#define TFT_BL_GPIO_PORT            GPIOG
#define TFT_BL_GPIO_PIN             GPIO_PIN_10
#define TFT_BL_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOG_CLK_ENABLE(); } while (0)
#endif

#define TFT_WR_GPIO_PORT            GPIOI
#define TFT_WR_GPIO_PIN             GPIO_PIN_14
#define TFT_WR_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define TFT_RD_GPIO_PORT            GPIOK
#define TFT_RD_GPIO_PIN             GPIO_PIN_7
#define TFT_RD_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOK_CLK_ENABLE(); } while (0)


#define TFT_CS_GPIO_PORT            GPIOI
#define TFT_CS_GPIO_PIN             GPIO_PIN_13
#define TFT_CS_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define TFT_RS_GPIO_PORT            GPIOI
#define TFT_RS_GPIO_PIN             GPIO_PIN_12
#define TFT_RS_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define TFT_RST_GPIO_PORT            GPIOK
#define TFT_RST_GPIO_PIN             GPIO_PIN_2
#define TFT_RST_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOK_CLK_ENABLE(); } while (0)
#if BackLight_USE_PWM == 0 
#define TFT_BL(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#endif
#define TFT_WR(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_WR_GPIO_PORT, TFT_WR_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_WR_GPIO_PORT, TFT_WR_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

#define TFT_RD(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_RD_GPIO_PORT, TFT_RD_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_RD_GPIO_PORT, TFT_RD_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

#define TFT_CS(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

#define TFT_RS(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_RS_GPIO_PORT, TFT_RS_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_RS_GPIO_PORT, TFT_RS_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

#define TFT_RST(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_RST_GPIO_PORT, TFT_RST_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_RST_GPIO_PORT, TFT_RST_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

#define TFT_B0_PORT            GPIOJ
#define TFT_B0_PIN             GPIO_PIN_12
#define TFT_B0_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_B1_PORT            GPIOJ
#define TFT_B1_PIN             GPIO_PIN_13
#define TFT_B1_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_B2_PORT            GPIOJ
#define TFT_B2_PIN             GPIO_PIN_14
#define TFT_B2_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_B3_PORT            GPIOJ
#define TFT_B3_PIN             GPIO_PIN_15
#define TFT_B3_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_B4_PORT            GPIOK
#define TFT_B4_PIN             GPIO_PIN_3
#define TFT_B4_CLK_ENABLE()    do { __HAL_RCC_GPIOK_CLK_ENABLE(); } while (0)
#define TFT_G0_PORT            GPIOJ
#define TFT_G0_PIN             GPIO_PIN_7
#define TFT_G0_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_G1_PORT            GPIOJ
#define TFT_G1_PIN             GPIO_PIN_8
#define TFT_G1_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_G2_PORT            GPIOJ
#define TFT_G2_PIN             GPIO_PIN_9
#define TFT_G2_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_G3_PORT            GPIOJ
#define TFT_G3_PIN             GPIO_PIN_10
#define TFT_G3_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_G4_PORT            GPIOJ
#define TFT_G4_PIN             GPIO_PIN_11
#define TFT_G4_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_G5_PORT            GPIOK
#define TFT_G5_PIN             GPIO_PIN_0
#define TFT_G5_CLK_ENABLE()    do { __HAL_RCC_GPIOK_CLK_ENABLE(); } while (0)
#define TFT_R0_PORT            GPIOI
#define TFT_R0_PIN             GPIO_PIN_15
#define TFT_R0_CLK_ENABLE()    do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)
#define TFT_R1_PORT            GPIOJ
#define TFT_R1_PIN             GPIO_PIN_0
#define TFT_R1_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_R2_PORT            GPIOJ
#define TFT_R2_PIN             GPIO_PIN_1
#define TFT_R2_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_R3_PORT            GPIOJ
#define TFT_R3_PIN             GPIO_PIN_2
#define TFT_R3_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define TFT_R4_PORT            GPIOJ
#define TFT_R4_PIN             GPIO_PIN_3
#define TFT_R4_CLK_ENABLE()    do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)


#define TFT_B0(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_B0_PORT, TFT_B0_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_B0_PORT, TFT_B0_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#define TFT_B1(x)                   do { (x) ?                                                                  \
                                       HAL_GPIO_WritePin(TFT_B1_PORT, TFT_B1_PIN, GPIO_PIN_SET):     \
                                       HAL_GPIO_WritePin(TFT_B1_PORT, TFT_B1_PIN, GPIO_PIN_RESET);   \
                                   } while (0)
#define TFT_B2(x)                   do { (x) ?                                                                 \
                                       HAL_GPIO_WritePin(TFT_B2_PORT, TFT_B2_PIN, GPIO_PIN_SET):     \
                                       HAL_GPIO_WritePin(TFT_B2_PORT, TFT_B2_PIN, GPIO_PIN_RESET);   \
                                   } while (0)
#define TFT_B3(x)                   do { (x) ?                                                                 \
                                       HAL_GPIO_WritePin(TFT_B3_PORT, TFT_B3_PIN, GPIO_PIN_SET):     \
                                       HAL_GPIO_WritePin(TFT_B3_PORT, TFT_B3_PIN, GPIO_PIN_RESET);   \
                                   } while (0)
#define TFT_B4(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_B4_PORT, TFT_B4_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_B4_PORT, TFT_B4_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#define TFT_G0(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_G0_PORT, TFT_G0_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_G0_PORT, TFT_G0_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#define TFT_G1(x)                   do { (x) ?                                                                  \
                                      HAL_GPIO_WritePin(TFT_G1_PORT, TFT_G1_PIN, GPIO_PIN_SET):     \
                                      HAL_GPIO_WritePin(TFT_G1_PORT, TFT_G1_PIN, GPIO_PIN_RESET);   \
                                  } while (0)
#define TFT_G2(x)                   do { (x) ?                                                                  \
                                      HAL_GPIO_WritePin(TFT_G2_PORT, TFT_G2_PIN, GPIO_PIN_SET):     \
                                      HAL_GPIO_WritePin(TFT_G2_PORT, TFT_G2_PIN, GPIO_PIN_RESET);   \
                                  } while (0)
#define TFT_G3(x)                   do { (x) ?                                                                  \
                                      HAL_GPIO_WritePin(TFT_G3_PORT, TFT_G3_PIN, GPIO_PIN_SET):     \
                                      HAL_GPIO_WritePin(TFT_G3_PORT, TFT_G3_PIN, GPIO_PIN_RESET);   \
                                  } while (0)
#define TFT_G4(x)                   do { (x) ?                                                                  \
                                      HAL_GPIO_WritePin(TFT_G4_PORT, TFT_G4_PIN, GPIO_PIN_SET):     \
                                      HAL_GPIO_WritePin(TFT_G4_PORT, TFT_G4_PIN, GPIO_PIN_RESET);   \
                                  } while (0)
#define TFT_G5(x)                   do { (x) ?                                                                  \
                                      HAL_GPIO_WritePin(TFT_G5_PORT, TFT_G5_PIN, GPIO_PIN_SET):     \
                                      HAL_GPIO_WritePin(TFT_G5_PORT, TFT_G5_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#define TFT_R0(x)                   do { (x) ?                                                                  \
                                       HAL_GPIO_WritePin(TFT_R0_PORT, TFT_R0_PIN, GPIO_PIN_SET):     \
                                       HAL_GPIO_WritePin(TFT_R0_PORT, TFT_R0_PIN, GPIO_PIN_RESET);   \
                                   } while (0)
#define TFT_R1(x)                   do { (x) ?                                                                  \
                                       HAL_GPIO_WritePin(TFT_R1_PORT, TFT_R1_PIN, GPIO_PIN_SET):     \
                                       HAL_GPIO_WritePin(TFT_R1_PORT, TFT_R1_PIN, GPIO_PIN_RESET);   \
                                   } while (0)
#define TFT_R2(x)                   do { (x) ?                                                                  \
                                       HAL_GPIO_WritePin(TFT_R2_PORT, TFT_R2_PIN, GPIO_PIN_SET):     \
                                       HAL_GPIO_WritePin(TFT_R2_PORT, TFT_R2_PIN, GPIO_PIN_RESET);   \
                                   } while (0)
#define TFT_R3(x)                   do { (x) ?                                                                  \
                                       HAL_GPIO_WritePin(TFT_R3_PORT, TFT_R3_PIN, GPIO_PIN_SET):     \
                                       HAL_GPIO_WritePin(TFT_R3_PORT, TFT_R3_PIN, GPIO_PIN_RESET);   \
                                   } while (0)
#define TFT_R4(x)                   do { (x) ?                                                                  \
                                        HAL_GPIO_WritePin(TFT_R4_PORT, TFT_R4_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(TFT_R4_PORT, TFT_R4_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

void TFT_GPIO_init(void);
void Write_TFT_Data(uint16_t data);
void Write_TFT_Data_u8_H(uint8_t data);
void Write_TFT_Data_u8_L(uint8_t data);
uint16_t Read_TFT_Data(void);
#ifdef __cplusplus
}
#endif

#endif 
