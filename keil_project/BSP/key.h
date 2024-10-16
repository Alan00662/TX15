
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define KEY_PAGE_L_GPIO_PORT GPIOG
#define KEY_PAGE_L_GPIO_PIN GPIO_PIN_7
#define KEY_PAGE_L_GPIO_CLK_ENABLE()  \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_PAGE_R_GPIO_PORT GPIOA
#define KEY_PAGE_R_GPIO_PIN GPIO_PIN_8
#define KEY_PAGE_R_GPIO_CLK_ENABLE()  \
    do                                \
    {                                 \
        __HAL_RCC_GPIOA_CLK_ENABLE(); \
    } while (0)

#define KEY_MDL_GPIO_PORT GPIOE
#define KEY_MDL_GPIO_PIN GPIO_PIN_3
#define KEY_MDL_GPIO_CLK_ENABLE()     \
    do                                \
    {                                 \
        __HAL_RCC_GPIOE_CLK_ENABLE(); \
    } while (0)

#define KEY_TELE_GPIO_PORT GPIOG
#define KEY_TELE_GPIO_PIN GPIO_PIN_2
#define KEY_TELE_GPIO_CLK_ENABLE()    \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_SYS_GPIO_PORT GPIOB
#define KEY_SYS_GPIO_PIN GPIO_PIN_2
#define KEY_SYS_GPIO_CLK_ENABLE()     \
    do                                \
    {                                 \
        __HAL_RCC_GPIOB_CLK_ENABLE(); \
    } while (0)

#define KEY_RTN_GPIO_PORT GPIOG
#define KEY_RTN_GPIO_PIN GPIO_PIN_3
#define KEY_RTN_GPIO_CLK_ENABLE()     \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_ENTER_GPIO_PORT GPIOG
#define KEY_ENTER_GPIO_PIN GPIO_PIN_12
#define KEY_ENTER_GPIO_CLK_ENABLE()   \
    do                                \
    {                                 \
        __HAL_RCC_GPIOG_CLK_ENABLE(); \
    } while (0)

#define KEY_PAGE_L HAL_GPIO_ReadPin(KEY_PAGE_L_GPIO_PORT, KEY_PAGE_L_GPIO_PIN)
#define KEY_PAGE_R HAL_GPIO_ReadPin(KEY_PAGE_R_GPIO_PORT, KEY_PAGE_R_GPIO_PIN)
#define KEY_MDL HAL_GPIO_ReadPin(KEY_MDL_GPIO_PORT, KEY_MDL_GPIO_PIN)
#define KEY_TELE HAL_GPIO_ReadPin(KEY_TELE_GPIO_PORT, KEY_TELE_GPIO_PIN)
#define KEY_SYS HAL_GPIO_ReadPin(KEY_SYS_GPIO_PORT, KEY_SYS_GPIO_PIN)
#define KEY_RTN HAL_GPIO_ReadPin(KEY_RTN_GPIO_PORT, KEY_RTN_GPIO_PIN)
#define KEY_ENTER HAL_GPIO_ReadPin(KEY_ENTER_GPIO_PORT, KEY_ENTER_GPIO_PIN)

#define TRIM_RVU_GPIO_PORT          GPIOH
#define TRIM_RVU_GPIO_PIN           GPIO_PIN_15
#define TRIM_RVU_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOH_CLK_ENABLE(); } while (0)
#define TRIM_RVD_GPIO_PORT          GPIOH
#define TRIM_RVD_GPIO_PIN           GPIO_PIN_13
#define TRIM_RVD_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOH_CLK_ENABLE(); } while (0)
#define TRIM_RHR_GPIO_PORT          GPIOI
#define TRIM_RHR_GPIO_PIN           GPIO_PIN_7
#define TRIM_RHR_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)
#define TRIM_RHL_GPIO_PORT          GPIOD
#define TRIM_RHL_GPIO_PIN           GPIO_PIN_5
#define TRIM_RHL_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOD_CLK_ENABLE(); } while (0)
#define TRIM_LVU_GPIO_PORT          GPIOI
#define TRIM_LVU_GPIO_PIN           GPIO_PIN_5
#define TRIM_LVU_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)
#define TRIM_LVD_GPIO_PORT          GPIOI
#define TRIM_LVD_GPIO_PIN           GPIO_PIN_6
#define TRIM_LVD_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)
#define TRIM_LHR_GPIO_PORT          GPIOH
#define TRIM_LHR_GPIO_PIN           GPIO_PIN_2
#define TRIM_LHR_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOH_CLK_ENABLE(); } while (0)
#define TRIM_LHL_GPIO_PORT          GPIOK
#define TRIM_LHL_GPIO_PIN           GPIO_PIN_1
#define TRIM_LHL_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOK_CLK_ENABLE(); } while (0)
#define SCAN_TIMEOUT  10

#define TRIM_RVU HAL_GPIO_ReadPin(TRIM_RVU_GPIO_PORT, TRIM_RVU_GPIO_PIN)
#define TRIM_RVD HAL_GPIO_ReadPin(TRIM_RVD_GPIO_PORT, TRIM_RVD_GPIO_PIN)
#define TRIM_RHR HAL_GPIO_ReadPin(TRIM_RHR_GPIO_PORT, TRIM_RHR_GPIO_PIN)
#define TRIM_RHL HAL_GPIO_ReadPin(TRIM_RHL_GPIO_PORT, TRIM_RHL_GPIO_PIN)
#define TRIM_LVU HAL_GPIO_ReadPin(TRIM_LVU_GPIO_PORT, TRIM_LVU_GPIO_PIN)
#define TRIM_LVD HAL_GPIO_ReadPin(TRIM_LVD_GPIO_PORT, TRIM_LVD_GPIO_PIN)
#define TRIM_LHR HAL_GPIO_ReadPin(TRIM_LHR_GPIO_PORT, TRIM_LHR_GPIO_PIN)
#define TRIM_LHL HAL_GPIO_ReadPin(TRIM_LHL_GPIO_PORT, TRIM_LHL_GPIO_PIN)

#define SE_H_GPIO_PORT          GPIOJ
#define SE_H_GPIO_PIN           GPIO_PIN_6
#define SE_H_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define SE_L_GPIO_PORT          GPIOJ
#define SE_L_GPIO_PIN           GPIO_PIN_5
#define SE_L_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOJ_CLK_ENABLE(); } while (0)
#define SF_H_GPIO_PORT          GPIOK
#define SF_H_GPIO_PIN           GPIO_PIN_6
#define SF_H_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOK_CLK_ENABLE(); } while (0)
#define SF_L_GPIO_PORT          GPIOI
#define SF_L_GPIO_PIN           GPIO_PIN_4
#define SF_L_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOI_CLK_ENABLE(); } while (0)

#define SWITCH_SE_H HAL_GPIO_ReadPin(SE_H_GPIO_PORT, SE_H_GPIO_PIN)
#define SWITCH_SE_L HAL_GPIO_ReadPin(SE_L_GPIO_PORT, SE_L_GPIO_PIN)
#define SWITCH_SF_H HAL_GPIO_ReadPin(SF_H_GPIO_PORT, SF_H_GPIO_PIN)
#define SWITCH_SF_L HAL_GPIO_ReadPin(SF_L_GPIO_PORT, SF_L_GPIO_PIN)

/* 键值定义 */
enum
{
    NONE_PRES = 0,
    SYS_PRES,            
    RTN_PRES,              
    RIGHT_PRES,            
    LEFT_PRES,             
    TELE_PRES, 
    MDL_PRES,               
    ENTER_PRES          
 
};
          

typedef struct key_info
{
    uint8_t left;  /* data */
    uint8_t right; /* data */
    uint8_t sys;   /* data */
    uint8_t modle; /* data */
    uint8_t enter; /* data */
    uint8_t tele;  /* data */
    uint8_t rtn;   /* data */
} key_info_t;
extern key_info_t Key_info;

typedef struct trim_info
{
    uint8_t rvu;  /* data */
    uint8_t rvd; /* data */
    uint8_t rhr;   /* data */
    uint8_t rhl; /* data */
    uint8_t lvu;  /* data */
    uint8_t lvd; /* data */
    uint8_t lhr;   /* data */
    uint8_t lhl; /* data */
} trim_info_t;
extern trim_info_t Trim_info;

typedef struct switch_info
{
    uint8_t seh;  /* data */
    uint8_t sel; /* data */
    uint8_t sfh;   /* data */
    uint8_t sfl; /* data */

} switch_info_t;
extern switch_info_t Switch_info;

void KEY_GPIO_init(void);
void key_scan_Loop(void);
void TRIM_GPIO_init(void);
void SWITCH_GPIO_init(void);
void trim_scan_Loop(void);
void switch_scan_Loop(void);
#ifdef __cplusplus
}
#endif

#endif
