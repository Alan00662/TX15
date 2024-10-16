
#include "tft_gpio.h"


void TFT_GPIO_init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  

  GPIO_InitStruct.Pin = TFT_BL_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TFT_BL_GPIO_PORT, &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(TFT_BL_GPIO_PORT, TFT_BL_GPIO_PIN, GPIO_PIN_SET);
  

  GPIO_InitStruct.Pin = TFT_WR_GPIO_PIN|TFT_CS_GPIO_PIN|TFT_RS_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = TFT_RD_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TFT_RD_GPIO_PORT, &GPIO_InitStruct);
  
   GPIO_InitStruct.Pin = TFT_RST_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);
  

  GPIO_InitStruct.Pin = TFT_R0_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = TFT_B4_PIN|TFT_G5_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = TFT_B0_PIN|TFT_B1_PIN|TFT_B2_PIN|TFT_B3_PIN|TFT_G0_PIN|TFT_G1_PIN|TFT_G2_PIN|TFT_G3_PIN|
						TFT_G4_PIN|TFT_R1_PIN|TFT_R2_PIN|TFT_R3_PIN|TFT_R4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);
  
  
}


void Write_TFT_Data(uint16_t data)
{
	uint16_t DB_H=0;
	uint16_t DB_L =0;


#if 1	
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

#else
	DB_L &= 0XFF00 ;
	DB_L |= (0X00FF & data);
	Write_TFT_Data_u8_L(DB_L);
	
	DB_H &= 0X00FF;
	DB_H |= (0XFF00 & data);

	Write_TFT_Data_u8_H(DB_H);

#endif
	
}


void Write_TFT_Data_u8_H(uint8_t data)
{
	GPIO_PinState DB8,DB9,DB10,DB11,DB12,DB13,DB14,DB15;
	
    DB15 = (data & 0x8000) >> 15;
    DB14 = (data & 0x4000) >> 14;
    DB13 = (data & 0x2000) >> 13;
    DB12 = (data & 0x1000) >> 12;
    DB11 = (data & 0x0800) >> 11;
    DB10 = (data & 0x0400) >> 10;
    DB9 = (data & 0x0200) >> 9;
    DB8 = (data & 0x0100) >> 8;
    
    TFT_R4(DB15);
    TFT_R3(DB14);
    TFT_R2(DB13);
    TFT_R1(DB12);
    TFT_R0(DB11);
    TFT_G5(DB10);
    TFT_G4(DB9);
    TFT_G3(DB8);
	
}

void Write_TFT_Data_u8_L(uint8_t data)
{
	GPIO_PinState DB0,DB1,DB2,DB3,DB4,DB5,DB6,DB7;
	
    DB7 = (data & 0x80) >> 7;
    DB6 = (data & 0x40) >> 6;
    DB5 = (data & 0x20) >> 5;
    DB4 = (data & 0x10) >> 4;
    DB3 = (data & 0x08) >> 3;
    DB2 = (data & 0x04) >> 2;
    DB1 = (data & 0x02) >> 1;
    DB0 = data & 0x01;
    
    TFT_G2(DB7);
    TFT_G1(DB6);
    TFT_G0(DB5);
    TFT_B4(DB4);
    TFT_B3(DB3);
    TFT_B2(DB2);
    TFT_B1(DB1);
    TFT_B0(DB0);
	
}

uint16_t Read_TFT_Data(void)
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