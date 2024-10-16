#include "interface.h"

uint32_t tft_display_tick = 0;
void Menu_Display_Loop(void)
{
	if((HAL_GetTick() - tft_display_tick) > 1)
	{
//	TFT_Clear(RED);
//	TFT_Clear(GREEN);
//	TFT_Clear(BLUE);
//	TFT_Clear(BLACK);
	TFT_show_string(85,0,260,"RadioMaster_TX15",TFT_FONT_32,BLUE); 
	TFT_show_string(0,32,80,"Backlght:",TFT_FONT_16,RED); 
	TFT_show_num(90,32,pwm_value,5,TFT_FONT_16,RED);
		
	TFT_show_string(0,50,72,"key_sys:",TFT_FONT_16,BLACK); 
	TFT_show_num(72,50,Key_info.sys,1,TFT_FONT_16,GREEN);
	TFT_show_string(88,50,72,"key_mdl:",TFT_FONT_16,BLACK); 
	TFT_show_num(160,50,Key_info.modle,1,TFT_FONT_16,GREEN);		
	TFT_show_string(176,50,72,"key_rtn:",TFT_FONT_16,BLACK); 
	TFT_show_num(248,50,Key_info.rtn,1,TFT_FONT_16,GREEN);
	TFT_show_string(264,50,72,"key_>>:",TFT_FONT_16,BLACK); 
	TFT_show_num(336,50,Key_info.right,1,TFT_FONT_16,GREEN);
	TFT_show_string(352,50,72,"key_<<:",TFT_FONT_16,BLACK); 
	TFT_show_num(424,50,Key_info.left,1,TFT_FONT_16,GREEN);
		
	TFT_show_string(0,70,72,"key_tel:",TFT_FONT_16,BLACK); 
	TFT_show_num(72,70,Key_info.tele,1,TFT_FONT_16,GREEN);
	TFT_show_string(88,70,72,"key_ent:",TFT_FONT_16,BLACK); 
	TFT_show_num(160,70,Key_info.enter,1,TFT_FONT_16,GREEN);
	TFT_show_string(176,70,72,"tri_rvu:",TFT_FONT_16,BLACK); 
	TFT_show_num(248,70,Trim_info.rvu,1,TFT_FONT_16,GREEN);
	TFT_show_string(264,70,72,"tri_rvd:",TFT_FONT_16,BLACK); 
	TFT_show_num(336,70,Trim_info.rvd,1,TFT_FONT_16,GREEN);
	TFT_show_string(352,70,72,"tri_rhr:",TFT_FONT_16,BLACK); 
	TFT_show_num(424,70,Trim_info.rhr,1,TFT_FONT_16,GREEN);	
	
	TFT_show_string(0,90,72,"tri_rhl:",TFT_FONT_16,BLACK); 
	TFT_show_num(72,90,Trim_info.rhl,1,TFT_FONT_16,GREEN);
	TFT_show_string(88,90,72,"tri_lvu:",TFT_FONT_16,BLACK); 
	TFT_show_num(160,90,Trim_info.lvu,1,TFT_FONT_16,GREEN);
	TFT_show_string(176,90,72,"tri_lvd:",TFT_FONT_16,BLACK); 
	TFT_show_num(248,90,Trim_info.lvd,1,TFT_FONT_16,GREEN);
	TFT_show_string(264,90,72,"tri_lhr:",TFT_FONT_16,BLACK); 
	TFT_show_num(336,90,Trim_info.lhr,1,TFT_FONT_16,GREEN);
	TFT_show_string(352,90,72,"tri_lhl:",TFT_FONT_16,BLACK); 
	TFT_show_num(424,90,Trim_info.lhl,1,TFT_FONT_16,GREEN);	
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

