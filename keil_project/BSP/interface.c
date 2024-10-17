#include "interface.h"


uint32_t tft_display_tick = 0;
void Menu_Display_Loop(void)
{
	static char ch = 'a';
	static uint8_t cnt = 0;
	if((HAL_GetTick() - tft_display_tick) > 5)
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
		
	TFT_show_string(0,50,64,"key_SYS:",TFT_FONT_16,RED); 
	TFT_show_num(64,50,Key_info.sys,1,TFT_FONT_16,RED);		
	TFT_show_string(96,50,64,"key_MDL:",TFT_FONT_16,RED); 
	TFT_show_num(160,50,Key_info.modle,1,TFT_FONT_16,RED);			
	TFT_show_string(192,50,64,"key_RTN:",TFT_FONT_16,RED); 
	TFT_show_num(256,50,Key_info.rtn,1,TFT_FONT_16,RED);	
	TFT_show_string(288,50,64,"key_>>:",TFT_FONT_16,RED); 
	TFT_show_num(352,50,Key_info.right,1,TFT_FONT_16,RED);	
	TFT_show_string(384,50,64,"key_<<:",TFT_FONT_16,RED); 
	TFT_show_num(448,50,Key_info.left,1,TFT_FONT_16,RED);
		
	TFT_show_string(0,70,64,"key_TEL:",TFT_FONT_16,RED); 
	TFT_show_num(64,70,Key_info.tele,1,TFT_FONT_16,RED);
	TFT_show_string(96,70,64,"key_ENT:",TFT_FONT_16,RED); 
	TFT_show_num(160,70,Key_info.enter,1,TFT_FONT_16,RED);
	TFT_show_string(192,70,64,"tri_rvu:",TFT_FONT_16,BLACK); 
	TFT_show_num(256,70,Trim_info.rvu,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(288,70,64,"tri_rvd:",TFT_FONT_16,BLACK); 
	TFT_show_num(352,70,Trim_info.rvd,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(384,70,64,"tri_rhr:",TFT_FONT_16,BLACK); 
	TFT_show_num(448,70,Trim_info.rhr,1,TFT_FONT_16,DARKBLUE);	
	
	TFT_show_string(0,90,64,"tri_rhl:",TFT_FONT_16,BLACK); 
	TFT_show_num(64,90,Trim_info.rhl,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(96,90,64,"tri_lvu:",TFT_FONT_16,BLACK); 
	TFT_show_num(160,90,Trim_info.lvu,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(192,90,64,"tri_lvd:",TFT_FONT_16,BLACK); 
	TFT_show_num(256,90,Trim_info.lvd,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(288,90,64,"tri_lhr:",TFT_FONT_16,BLACK); 
	TFT_show_num(352,90,Trim_info.lhr,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(384,90,72,"tri_lhl:",TFT_FONT_16,BLACK); 
	TFT_show_num(448,90,Trim_info.lhl,1,TFT_FONT_16,DARKBLUE);	

	TFT_show_string(0,110,72,"sw_SE:",TFT_FONT_16,BLUE); 
	TFT_show_num(54,110,Switch_info.seh,1,TFT_FONT_16,BLUE);
	TFT_show_string(96,110,72,"sw_SF:",TFT_FONT_16,BLUE); 
	TFT_show_num(150,110,Switch_info.sfh,1,TFT_FONT_16,BLUE);
	TFT_show_string(192,110,70,"adc_S1:",TFT_FONT_16,BLUE); 
	TFT_show_num(256,110,adc_s1,4,TFT_FONT_16,BLUE);
	TFT_show_string(320,110,70,"adc_S2:",TFT_FONT_16,BLUE); 
	TFT_show_num(390,110,adc_s2,4,TFT_FONT_16,BLUE);

	TFT_show_string(0,130,30,"k1:",TFT_FONT_16,BROWN); 
	TFT_show_num(30,130,Tca9539.k1,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(64,130,30,"k2:",TFT_FONT_16,BROWN); 
	TFT_show_num(94,130,Tca9539.k2,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(128,130,30,"k3:",TFT_FONT_16,BROWN); 
	TFT_show_num(158,130,Tca9539.k3,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(192,130,30,"k4:",TFT_FONT_16,BROWN); 
	TFT_show_num(222,130,Tca9539.k4,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(256,130,30,"k5:",TFT_FONT_16,BROWN); 
	TFT_show_num(286,130,Tca9539.k5,1,TFT_FONT_16,DARKBLUE);
	
	TFT_show_string(320,130,30,"k6:",TFT_FONT_16,BROWN); 
	TFT_show_num(350,130,Tca9539.k6,1,TFT_FONT_16,DARKBLUE);

	TFT_show_string(0,150,30,"SA:",TFT_FONT_16,BROWN); 
	TFT_show_num(30,150,Tca9539_sw.SA,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(64,150,30,"SB:",TFT_FONT_16,BROWN); 
	TFT_show_num(94,150,Tca9539_sw.SB,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(128,150,30,"SC:",TFT_FONT_16,BROWN); 
	TFT_show_num(158,150,Tca9539_sw.SC,1,TFT_FONT_16,DARKBLUE);
	TFT_show_string(192,150,30,"SD:",TFT_FONT_16,BROWN); 
	TFT_show_num(222,150,Tca9539_sw.SD,1,TFT_FONT_16,DARKBLUE);

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

