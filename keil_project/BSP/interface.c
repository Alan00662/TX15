#include "interface.h"

uint32_t tft_display_tick = 0;
void Menu_Display_Loop(void)
{
	if((HAL_GetTick() - tft_display_tick) > 5)
	{
//	TFT_Clear(RED);
//	TFT_Clear(GREEN);
//	TFT_Clear(BLUE);
//	TFT_Clear(BLACK);
	TFT_show_string(85,0,260,"RadioMaster_TX15",TFT_FONT_32,BLUE); 
	TFT_show_string(0,40,100,"Backlght:",TFT_FONT_16,RED); 
	TFT_show_num(110,40,pwm_value,5,TFT_FONT_16,RED);
//	TFT_show_pic(40,40,120,120,picture_tab);
//	TFT_show_Chinese_16x16(10,160,BLACK,CYAN,0);
//	TFT_show_Chinese_16x16(36,160,GREEN,WHITE,1);
//	TFT_show_Chinese_16x16(60,160,RED,WHITE,2);
//	TFT_show_Chinese_16x16(76,160,BLUE,WHITE,3);
//	TFT_show_Chinese_16x16(92,160,GREEN,WHITE,4);
//	TFT_show_Chinese_16x16(118,160,BLUE,WHITE,5);
//	TFT_show_Chinese_16x16(134,160,RED,WHITE,6);
		tft_display_tick =  HAL_GetTick();
	}

}	

