/**
 ****************************************************************************************************
 * @file        atk_md0350_gpio.c
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

#include "atk_md0350_gpio.h"

//把一个16位数据拆解成16个二进制数依次输出到相应的引脚
void ATK_MD0350_GPIO_DATA(uint16_t data)
{
	GPIO_PinState DB0,DB1,DB2,DB3,DB4,DB5,DB6,DB7,DB8,
				DB9,DB10,DB11,DB12,DB13,DB14,DB15;
	
    DB15 = (data & 0x8000) >> 15;
    DB14 = (data & 0x4000) >> 14;
    DB13 = (data & 0x2000) >> 13;
    DB12 = (data & 0x1000) >> 12;
    DB11 = (data & 0x0800) >> 11;
    DB10 = (data & 0x0400) >> 10;
    DB9 = (data & 0x0200) >> 9;
    DB8 = (data & 0x0100) >> 8;
    DB7 = (data & 0x0080) >> 7;
    DB6 = (data & 0x0040) >> 6;
    DB5 = (data & 0x0020) >> 5;
    DB4 = (data & 0x0010) >> 4;
    DB3 = (data & 0x0008) >> 3;
    DB2 = (data & 0x0004) >> 2;
    DB1 = (data & 0x0002) >> 1;
    DB0 = data & 0x0001;
    
	TFT_R4(DB15);
	TFT_R3(DB14);
	TFT_R2(DB13);
	TFT_R1(DB12);
	TFT_R0(DB11);
	TFT_G5(DB10);
	TFT_G4(DB9);
	TFT_G3(DB8);
	TFT_G2(DB7);
	TFT_G1(DB6);
	TFT_G0(DB5);
	TFT_B4(DB4);
	TFT_B3(DB3);
	TFT_B2(DB2);
	TFT_B1(DB1);
	TFT_B0(DB0);
	
}

/**
 * @brief       ATK-MD0350模块GPIO接口初始化
 * @param       无
 * @retval      无
 */
void atk_md0350_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能时钟 */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
    
    /* 初始化RS引脚 */
    gpio_init_struct.Pin    = ATK_MD0350_GPIO_RS_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_GPIO_RS_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化CS引脚 */
    gpio_init_struct.Pin    = ATK_MD0350_GPIO_CS_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_GPIO_CS_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化RD引脚 */
    gpio_init_struct.Pin    = ATK_MD0350_GPIO_RD_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_GPIO_RD_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化WR引脚 */
    gpio_init_struct.Pin    = ATK_MD0350_GPIO_WR_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_GPIO_WR_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化DATA引脚 */
//    gpio_init_struct.Pin    = ATK_MD0350_GPIO_DATA_GPIO_PIN;
//    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
//    gpio_init_struct.Pull   = GPIO_PULLUP;
//    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(ATK_MD0350_GPIO_DATA_GPIO_PORT, &gpio_init_struct);
	gpio_init_struct.Pin = TFT_R0_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Pull = GPIO_PULLUP;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOI, &gpio_init_struct);
	
	gpio_init_struct.Pin = TFT_B4_PIN|TFT_G5_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Pull = GPIO_PULLUP;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOK, &gpio_init_struct);
	
	gpio_init_struct.Pin = TFT_B0_PIN|TFT_B1_PIN|TFT_B2_PIN|TFT_B3_PIN|TFT_G0_PIN|TFT_G1_PIN|TFT_G2_PIN|TFT_G3_PIN|
						TFT_G4_PIN|TFT_R1_PIN|TFT_R2_PIN|TFT_R3_PIN|TFT_R4_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Pull = GPIO_PULLUP;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOJ, &gpio_init_struct);
  
    ATK_MD0350_GPIO_RS(1);
    ATK_MD0350_GPIO_CS(1);
    ATK_MD0350_GPIO_RD(1);
    ATK_MD0350_GPIO_WR(1);
    ATK_MD0350_GPIO_DATA(0xFFFF);


}

/**
 * @brief       ATK-MD0350模块通过GPIO接口写命令
 * @param       cmd: 待写命令
 * @retval      无
 */
void atk_md0350_gpio_write_cmd(uint16_t cmd)
{
    ATK_MD0350_GPIO_RS(0);
    ATK_MD0350_GPIO_CS(0);
    ATK_MD0350_GPIO_DATA(cmd);
    ATK_MD0350_GPIO_WR(0);
    ATK_MD0350_GPIO_WR(1);
    ATK_MD0350_GPIO_CS(1);
}

/**
 * @brief       ATK-MD0350模块通过GPIO接口写数据
 * @param       dat: 待写数据
 * @retval      无
 */
void atk_md0350_gpio_write_dat(uint16_t dat)
{
    ATK_MD0350_GPIO_RS(1);
    ATK_MD0350_GPIO_CS(0);
    ATK_MD0350_GPIO_DATA(dat);
    ATK_MD0350_GPIO_WR(0);
    ATK_MD0350_GPIO_WR(1);
    ATK_MD0350_GPIO_CS(1);
}

/**
 * @brief       ATK-MD0350模块通过GPIO接口写寄存器
 * @param       reg: 待操作寄存器
 *              dat: 待写数据
 * @retval      无
 */
void atk_md0350_gpio_write_reg(uint16_t reg, uint16_t dat)
{
    atk_md0350_gpio_write_cmd(reg);
    atk_md0350_gpio_write_dat(dat);
}

/*挨个读取TFT数据引脚高低电平，然后按顺序合并成一个16位数据*/
//R、G、B，对应15-0
uint16_t ATK_MD0350_GPIO_READ_DATA(void)
{
	uint16_t ret;
	GPIO_PinState DB0,DB1,DB2,DB3,DB4,DB5,DB6,DB7,DB8,
					DB9,DB10,DB11,DB12,DB13,DB14,DB15;
	
	DB0 = HAL_GPIO_ReadPin(GPIOJ,TFT_B0_PIN);
	DB1 = HAL_GPIO_ReadPin(GPIOJ,TFT_B1_PIN);
	DB2 = HAL_GPIO_ReadPin(GPIOJ,TFT_B2_PIN);
	DB3 = HAL_GPIO_ReadPin(GPIOJ,TFT_B3_PIN);
	
	DB4 = HAL_GPIO_ReadPin(GPIOK,TFT_B4_PIN);
	
	DB5 = HAL_GPIO_ReadPin(GPIOJ,TFT_G0_PIN);
	DB6 = HAL_GPIO_ReadPin(GPIOJ,TFT_G1_PIN);
	DB7 = HAL_GPIO_ReadPin(GPIOJ,TFT_G2_PIN);	
	DB8 = HAL_GPIO_ReadPin(GPIOJ,TFT_G3_PIN);
	DB9 = HAL_GPIO_ReadPin(GPIOJ,TFT_G4_PIN);
	
	DB10 = HAL_GPIO_ReadPin(GPIOK,TFT_G5_PIN);
	
	DB11 = HAL_GPIO_ReadPin(GPIOI,TFT_R0_PIN);	
	
	DB12 = HAL_GPIO_ReadPin(GPIOJ,TFT_R1_PIN);
	DB13 = HAL_GPIO_ReadPin(GPIOJ,TFT_R3_PIN);
	DB14 = HAL_GPIO_ReadPin(GPIOJ,TFT_R3_PIN);
	DB15 = HAL_GPIO_ReadPin(GPIOJ,TFT_R4_PIN);

    // 按顺序合并成16位数据
    ret |= (DB0 << 0);
    ret |= (DB1 << 1);
    ret |= (DB2 << 2);
    ret |= (DB3 << 3);
    ret |= (DB4 << 4);
    ret |= (DB5 << 5);
    ret |= (DB6 << 6);
    ret |= (DB7 << 7);
    ret |= (DB8 << 8);
    ret |= (DB9 << 9);
    ret |= (DB10 << 10);
    ret |= (DB11 << 11);
    ret |= (DB12 << 12);
    ret |= (DB13 << 13);
    ret |= (DB14 << 14);
    ret |= (DB15 << 15);

    return ret;

}

uint16_t tft_gpio_read_dat(void)
{
	uint16_t dat;
    ATK_MD0350_GPIO_RS(1);
    ATK_MD0350_GPIO_CS(0);
    ATK_MD0350_GPIO_RD(0);
//    __nop();
//    __nop();
	HAL_Delay(1);
    dat = ATK_MD0350_GPIO_READ_DATA();
    ATK_MD0350_GPIO_RD(1);
    ATK_MD0350_GPIO_CS(1);
	return dat;
}
/**
 * @brief       ATK-MD0350模块通过GPIO接口读数据
 * @param       无
 * @retval      读取到的数据
 */
uint16_t atk_md0350_gpio_read_dat(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
	
    GPIO_InitTypeDef gpio_init_struct = {0};
    uint16_t dat;

	
/* 把数据引脚设置成输入模式  */  
//    gpio_init_struct.Pin    = ATK_MD0350_GPIO_DATA_GPIO_PIN;
//    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
//    gpio_init_struct.Pull   = GPIO_PULLUP;
//    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(ATK_MD0350_GPIO_DATA_GPIO_PORT, &gpio_init_struct);
//数据引脚 
  gpio_init_struct.Pin = TFT_R0_PIN;
  gpio_init_struct.Mode = GPIO_MODE_INPUT;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &gpio_init_struct);
  
  gpio_init_struct.Pin = TFT_B4_PIN|TFT_G5_PIN;
  gpio_init_struct.Mode = GPIO_MODE_INPUT;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOK, &gpio_init_struct);
  
  gpio_init_struct.Pin = TFT_B0_PIN|TFT_B1_PIN|TFT_B2_PIN|TFT_B3_PIN|TFT_G0_PIN|TFT_G1_PIN|TFT_G2_PIN|TFT_G3_PIN|
						TFT_G4_PIN|TFT_R1_PIN|TFT_R2_PIN|TFT_R3_PIN|TFT_R4_PIN;
  gpio_init_struct.Mode = GPIO_MODE_INPUT;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOJ, &gpio_init_struct);
/***************************************************/
    ATK_MD0350_GPIO_RS(1);
    ATK_MD0350_GPIO_CS(0);
    ATK_MD0350_GPIO_RD(0);
//    __nop();
//    __nop();
	HAL_Delay(1);
    dat = ATK_MD0350_GPIO_READ_DATA();
    ATK_MD0350_GPIO_RD(1);
    ATK_MD0350_GPIO_CS(1);

/* 把数据引脚设置成输出模式  */  
//    gpio_init_struct.Pin    = ATK_MD0350_GPIO_DATA_GPIO_PIN;
//    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
//    gpio_init_struct.Pull   = GPIO_PULLUP;
//    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(ATK_MD0350_GPIO_DATA_GPIO_PORT, &gpio_init_struct);
  gpio_init_struct.Pin = TFT_R0_PIN;
  gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &gpio_init_struct);
  
  gpio_init_struct.Pin = TFT_B4_PIN|TFT_G5_PIN;
  gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOK, &gpio_init_struct);
  
  gpio_init_struct.Pin = TFT_B0_PIN|TFT_B1_PIN|TFT_B2_PIN|TFT_B3_PIN|TFT_G0_PIN|TFT_G1_PIN|TFT_G2_PIN|TFT_G3_PIN|
						TFT_G4_PIN|TFT_R1_PIN|TFT_R2_PIN|TFT_R3_PIN|TFT_R4_PIN;
  gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOJ, &gpio_init_struct);
  
    return dat;
}

void TFT_input_Mode(void)
{

  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
	
    GPIO_InitTypeDef gpio_init_struct = {0};
	
	gpio_init_struct.Pin = TFT_R0_PIN;
  gpio_init_struct.Mode = GPIO_MODE_INPUT;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &gpio_init_struct);
  
  gpio_init_struct.Pin = TFT_B4_PIN|TFT_G5_PIN;
  gpio_init_struct.Mode = GPIO_MODE_INPUT;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOK, &gpio_init_struct);
  
  gpio_init_struct.Pin = TFT_B0_PIN|TFT_B1_PIN|TFT_B2_PIN|TFT_B3_PIN|TFT_G0_PIN|TFT_G1_PIN|TFT_G2_PIN|TFT_G3_PIN|
						TFT_G4_PIN|TFT_R1_PIN|TFT_R2_PIN|TFT_R3_PIN|TFT_R4_PIN;
  gpio_init_struct.Mode = GPIO_MODE_INPUT;
  gpio_init_struct.Pull = GPIO_PULLUP;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOJ, &gpio_init_struct);
	
  gpio_init_struct.Pin = LED0_Pin;
  gpio_init_struct.Mode = GPIO_MODE_INPUT;
  gpio_init_struct.Pull = GPIO_NOPULL;
  gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &gpio_init_struct);
}