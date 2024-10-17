#include "interface.h"



uint32_t tft_display_tick = 0;
void Menu_Display_Loop(void)
{
	static char ch = 'a';
	static uint8_t cnt = 0;
	if((HAL_GetTick() - tft_display_tick) > 1)
	{

//		TFT_show_char(50,50,ch,TFT_FONT_16,BLACK); 
//		cnt++;
//		if(cnt >20)
//		{
//			cnt = 0;
//			ch++;
//		}


	TFT_show_string(85,0,260,"RadioMaster_TX15",TFT_FONT_32,BLUE); 
	TFT_show_string(0,32,80,"Backlght:",TFT_FONT_16,RED); 
	TFT_show_num(90,32,pwm_value,5,TFT_FONT_16,RED);
		
	TFT_show_string(0,50,72,"key_sys:",TFT_FONT_16,RED); 
	TFT_show_num(72,50,Key_info.sys,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(88,50,72,"key_mdl:",TFT_FONT_16,RED); 
	TFT_show_num(160,50,Key_info.modle,1,TFT_FONT_16,DARKBLUE);		
	TFT_show_string(176,50,72,"key_rtn:",TFT_FONT_16,RED); 
	TFT_show_num(248,50,Key_info.rtn,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(264,50,72,"key_>>:",TFT_FONT_16,RED); 
	TFT_show_num(336,50,Key_info.right,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(352,50,72,"key_<<:",TFT_FONT_16,RED); 
	TFT_show_num(424,50,Key_info.left,1,TFT_FONT_16,DARKBLUE);
		
	TFT_show_string(0,70,72,"key_tel:",TFT_FONT_16,RED); 
	TFT_show_num(72,70,Key_info.tele,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(88,70,72,"key_ent:",TFT_FONT_16,RED); 
	TFT_show_num(160,70,Key_info.enter,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(176,70,72,"tri_rvu:",TFT_FONT_16,BLACK); 
	TFT_show_num(248,70,Trim_info.rvu,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(264,70,72,"tri_rvd:",TFT_FONT_16,BLACK); 
	TFT_show_num(336,70,Trim_info.rvd,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(352,70,72,"tri_rhr:",TFT_FONT_16,BLACK); 
	TFT_show_num(424,70,Trim_info.rhr,1,TFT_FONT_16,DARKBLUE);	
	
	TFT_show_string(0,90,72,"tri_rhl:",TFT_FONT_16,BLACK); 
	TFT_show_num(72,90,Trim_info.rhl,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(88,90,72,"tri_lvu:",TFT_FONT_16,BLACK); 
	TFT_show_num(160,90,Trim_info.lvu,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(176,90,72,"tri_lvd:",TFT_FONT_16,BLACK); 
	TFT_show_num(248,90,Trim_info.lvd,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(264,90,72,"tri_lhr:",TFT_FONT_16,BLACK); 
	TFT_show_num(336,90,Trim_info.lhr,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(352,90,72,"tri_lhl:",TFT_FONT_16,BLACK); 
	TFT_show_num(424,90,Trim_info.lhl,1,TFT_FONT_16,DARKBLUE);	

	TFT_show_string(0,110,72,"sw_se_h:",TFT_FONT_16,BLUE); 
	TFT_show_num(72,110,Switch_info.seh,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(88,110,72,"sw_se_l:",TFT_FONT_16,BLUE); 
	TFT_show_num(160,110,Switch_info.sel,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(176,110,72,"sw_sf_h:",TFT_FONT_16,BLUE); 
	TFT_show_num(248,110,Switch_info.sfh,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(264,110,72,"sw_sf_l:",TFT_FONT_16,BLUE); 
	TFT_show_num(336,110,Switch_info.sfl,1,TFT_FONT_16,DARKBLUE);

	TFT_show_string(0,130,30,"k1:",TFT_FONT_16,BROWN); 
	TFT_show_num(30,130,Tca9539.k1,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(46,130,30,"k2:",TFT_FONT_16,BROWN); 
	TFT_show_num(76,130,Tca9539.k2,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(92,130,30,"k3:",TFT_FONT_16,BROWN); 
	TFT_show_num(122,130,Tca9539.k3,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(138,130,30,"k4:",TFT_FONT_16,BROWN); 
	TFT_show_num(168,130,Tca9539.k4,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(184,130,30,"k5:",TFT_FONT_16,BROWN); 
	TFT_show_num(214,130,Tca9539.k5,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(230,130,30,"k6:",TFT_FONT_16,BROWN); 
	TFT_show_num(260,130,Tca9539.k6,1,TFT_FONT_16,DARKBLUE);

	TFT_show_string(276,130,30,"SA:",TFT_FONT_16,BROWN); 
	TFT_show_num(306,130,Tca9539_sw.SA,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(322,130,30,"SB:",TFT_FONT_16,BROWN); 
	TFT_show_num(352,130,Tca9539_sw.SB,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(368,130,30,"SC:",TFT_FONT_16,BROWN); 
	TFT_show_num(398,130,Tca9539_sw.SC,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(414,130,30,"SD:",TFT_FONT_16,BROWN); 
	TFT_show_num(444,130,Tca9539_sw.SD,1,TFT_FONT_16,DARKBLUE);

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

