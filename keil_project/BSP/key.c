
#include "key.h"

void KEY_GPIO_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Pin = KEY_PAGE_R_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_PAGE_R_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = KEY_SYS_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_SYS_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = KEY_MDL_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_MDL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = KEY_PAGE_L_GPIO_PIN | KEY_TELE_GPIO_PIN | KEY_RTN_GPIO_PIN | KEY_ENTER_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}
void TRIM_GPIO_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOK_CLK_ENABLE();

    GPIO_InitStruct.Pin = TRIM_RHL_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TRIM_RHL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TRIM_RVU_GPIO_PIN|TRIM_RVD_GPIO_PIN|TRIM_LHR_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TRIM_RVU_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TRIM_RHR_GPIO_PIN|TRIM_LVU_GPIO_PIN|TRIM_LVD_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TRIM_LHL_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TRIM_LHL_GPIO_PORT, &GPIO_InitStruct);
}


key_info_t Key_info = {0};
uint32_t key_scan_tick = 0;
void key_scan_Loop(void)
{
	if((HAL_GetTick() - key_scan_tick) > 10)
	{
		Key_info.enter = KEY_ENTER;
		Key_info.left = KEY_PAGE_L;
		Key_info.right = KEY_PAGE_R;
		Key_info.sys = KEY_SYS;
		Key_info.modle = KEY_MDL;
		Key_info.tele = KEY_TELE;
		Key_info.rtn = KEY_RTN;
		key_scan_tick = HAL_GetTick();
	}
}

trim_info_t Trim_info = {0};
uint32_t trim_scan_tick = 0;
void trim_scan_Loop(void)
{
	if((HAL_GetTick() - trim_scan_tick) > 20)
	{
        Trim_info.rvu = TRIM_RVU;
        
        Trim_info.rvd = TRIM_RVD;
        
        Trim_info.rhr = TRIM_RHR;
        
        Trim_info.rhl = TRIM_RHL;        
        
        Trim_info.lvu = TRIM_LVU;
        
        Trim_info.lvd = TRIM_LVD;
        
        Trim_info.lhr = TRIM_LHR;
        
        Trim_info.lhl = TRIM_LHL;
        trim_scan_tick = HAL_GetTick();
	}
}
