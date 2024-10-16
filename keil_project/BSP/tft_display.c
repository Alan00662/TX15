

#include "tft_display.h"

const unsigned char  *point;

static void TFT_write(uint16_t tft_data)				
{
	//WR上升沿写入
	TFT_WR(0);
	Write_TFT_Data(tft_data);
	TFT_WR(1);
	
}

static void TFT_send_cmd(uint16_t o_command)
{
  TFT_RS(0);
  TFT_CS(0);
  TFT_write(o_command);
  TFT_CS(1);
 
  //TFT_RS(1);
}

static void TFT_send_data(uint16_t o_data)
{ 
  TFT_RS(1);
  TFT_CS(0);
  TFT_write(o_data);
  TFT_CS(1);
  
}
  
static void TFT_set_add(uint16_t X,uint16_t Y,uint16_t X_END,uint16_t Y_END)
{	
     //判断地址是否合法
    if((X_END>(TFT_COLUMN_NUMBER-1))|| (X>(TFT_COLUMN_NUMBER-1)) )       //横向向显示    //超出x地址范围
    {
        X_END = (TFT_COLUMN_NUMBER-1);
    //X = 0;
    }   
    if((Y_END > (TFT_LINE_NUMBER-1) )||(Y > (TFT_LINE_NUMBER-1) ))     //超出Y范围
    {
    //Y = 0;                         //移动到第一行
       Y_END =  ( TFT_LINE_NUMBER-1);                
    }
	TFT_send_cmd(0x2A);     //窗口地址横向               
    TFT_send_data(X>>8);     
    TFT_send_data(X);//start column
	TFT_send_data(X_END>>8);     
    TFT_send_data(X_END);//start column
	TFT_send_cmd(0x2B);      //窗口地址纵向                                   
    TFT_send_data(Y>>8);     
    TFT_send_data(Y);		//start row
    TFT_send_data(Y_END>>8);     
    TFT_send_data(Y_END);		//start row
    TFT_send_cmd(0x2C);     //write data
}  
//清除液晶数据，刷颜色
void TFT_Clear(uint16_t back_c)									
{
	unsigned int ROW=0,column=0;
	TFT_set_add(0,0,TFT_COLUMN_NUMBER-1,TFT_LINE_NUMBER-1);
	for(ROW = 0;ROW < TFT_LINE_NUMBER;ROW++)             //ROW loop
	{ 
		for(column=0;column<TFT_COLUMN_NUMBER;column++)  //column loop
		{         
			TFT_send_data(~back_c);
		}
	}
}

//清除局部位置数据，刷上背景颜色
static void TFT_Clear_char(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t back_c)									
{
	unsigned int ROW=0,column=0;
	TFT_set_add(x1,y1,x2,y2);
	for(ROW = y1;ROW<= y2;ROW++)             //ROW loop
	{ 
		for(column=x1;column <= x2;column++)  //column loop
		{         
			TFT_send_data(~back_c);
		}
	}
}

void TFT_init(void)        ////ST7796
{
	#if BackLight_USE_PWM ==0
	TFT_BL(1);
	#endif
	TFT_RD(1);
	TFT_RST(0);
	HAL_Delay(200);	 
	TFT_RST(1);	
	HAL_Delay(200);	 
	//************ Reset LCD Driver****************//
	TFT_WR(1);
	TFT_CS(0);
	TFT_RST(1);
	HAL_Delay(20);
	TFT_RST(0);
	HAL_Delay(20);	
	TFT_RST(1);
	HAL_Delay(200);	        
	TFT_RD(1);
			
	//************* Start Initial Sequence**********//
	HAL_Delay(100);        //software start 0x01最小5ms
	TFT_send_cmd(0X11);   //  退出睡眠
	HAL_Delay(100);
	
	TFT_send_cmd(0Xf0);     //命令设置
	TFT_send_data(0xc3);       //use command2 part1
	
	TFT_send_cmd(0Xf0);
	TFT_send_data(0x96);    //use command2 part2
	
	TFT_send_cmd(0X36);     //现存数据控制，显示方向设置
	//调整显示方向  MY,MX,MV,ML,RGB,MH,X,X       row-order，column-order，row/column exchange，
								  //vertical refresh（1-bottom2top），rgb，0-left2right
	if (DIS_DIR == DIR_0)                    //正常竖显
	{
		TFT_send_data(0x48);
	}
	else if (DIS_DIR == DIR_90)                   //旋转90度显示
	{
		TFT_send_data(0x28);		
	}

	else if (DIS_DIR == DIR_180)                   //旋转180度显示
	{
		TFT_send_data(0x88);		
	}

	else if(DIS_DIR == DIR_270)                   //旋转270度显示
	{
		TFT_send_data(0xE8);		
	}

     
	TFT_send_cmd(0x3A);
	TFT_send_data(0x05);		//RGB565        
	TFT_send_cmd(0Xe8);
	TFT_send_data(0x40);
	TFT_send_data(0x82);
	TFT_send_data(0x07);
	TFT_send_data(0x18);
	TFT_send_data(0x27);
	TFT_send_data(0x0a);
	TFT_send_data(0xb6);
	TFT_send_data(0x33);
        
    TFT_send_cmd(0Xc5);
    TFT_send_data(0x27);
    
    TFT_send_cmd(0Xc2);
    TFT_send_data(0xa7);
    
    TFT_send_cmd(0Xe0);
    TFT_send_data(0xf0);
    TFT_send_data(0x01);
    TFT_send_data(0x06);
    TFT_send_data(0x0f);
    TFT_send_data(0x12);
    TFT_send_data(0x1d);
    TFT_send_data(0x36);
    TFT_send_data(0x54);
    TFT_send_data(0x44);
    TFT_send_data(0x0c);
    TFT_send_data(0x18);
    TFT_send_data(0x16);
    TFT_send_data(0x13);
    TFT_send_data(0x15);
    
    TFT_send_cmd(0Xe1);
    TFT_send_data(0xf0);
    TFT_send_data(0x01);
    TFT_send_data(0x05);
    TFT_send_data(0x0a);
    TFT_send_data(0x0b);
    TFT_send_data(0x07);
    TFT_send_data(0x32);
    TFT_send_data(0x44);
    TFT_send_data(0x44);
    TFT_send_data(0x0c);
    TFT_send_data(0x18);
    TFT_send_data(0x17);
    TFT_send_data(0x13);
    TFT_send_data(0x16);
    
    TFT_send_cmd(0Xf0);         
    TFT_send_data(0x3c);        //Disable command2 part1
    
    TFT_send_cmd(0Xf0);
    TFT_send_data(0x69);        //Disable command2 part2
    HAL_Delay(20);
    
    TFT_send_cmd(0X29);	//turn on display

}

/**
 * @brief       开始写ATK-MD0350模块显存
 * @param       无
 * @retval      无
 */
static void TFT_start_write_memory(void)
{
    TFT_send_cmd(0x2C);
}


/**
 * @brief       设置ATK-MD0350模块列地址
 * @param       无
 * @retval      无
 */
static void TFT_set_column_address(uint16_t sc, uint16_t ec)
{
    TFT_send_cmd(0x2A);
    TFT_send_data((uint8_t)(sc >> 8) & 0xFF);
    TFT_send_data((uint8_t)sc & 0xFF);
    TFT_send_data((uint8_t)(ec >> 8) & 0xFF);
    TFT_send_data((uint8_t)ec & 0xFF);
}

/**
 * @brief       设置ATK-MD0350模块页地址
 * @param       无
 * @retval      无
 */
static void TFT_set_page_address(uint16_t sp, uint16_t ep)
{
    TFT_send_cmd(0x2B);
    TFT_send_data((uint8_t)(sp >> 8) & 0xFF);
    TFT_send_data((uint8_t)sp & 0xFF);
    TFT_send_data((uint8_t)(ep >> 8) & 0xFF);
    TFT_send_data((uint8_t)ep & 0xFF);
}

void TFT_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    TFT_set_column_address(x, x);
    TFT_set_page_address(y, y);
    TFT_start_write_memory();
    TFT_send_data(~color);
}

/**
 * @brief       平方函数，x^y
 * @param       x: 底数
 *              y: 指数
 * @retval      x^y
 */
static uint32_t TFT_pow(uint8_t x, uint8_t y)
{
    uint8_t loop;
    uint32_t res = 1;
    
    for (loop=0; loop<y; loop++)
    {
        res *= x;
    }
    
    return res;
}


/**
 * @brief       ATK-MD0350模块LCD显示数字，可控制显示高位0
 * @param       x    : 待显示数字的X坐标
 *              y    : 待显示数字的Y坐标
 *              num  : 待显示数字
 *              len  : 待显示数字的位数
 *              mode : TFT_NUM_SHOW_NOZERO: 数字高位0不显示
 *                     TFT_NUM_SHOW_ZERO  : 数字高位0显示
 *              font : 待显示数字的字体
 *              color: 待显示数字的颜色
 * @retval      无
 */
void TFT_show_char(uint16_t x, uint16_t y, char ch, tft_lcd_font_t font, uint16_t color)
{
    const uint8_t *ch_code;
    uint8_t ch_width;
    uint8_t ch_height;
    uint8_t ch_size;
    uint8_t ch_offset;
    uint8_t byte_index;
    uint8_t byte_code;
    uint8_t bit_index;
    uint8_t width_index = 0;
    uint8_t height_index = 0;
    
    ch_offset = ch - ' ';
    switch (font)
    {
        case TFT_FONT_12:
        {
            ch_code = asc2_1206[ch_offset];
            ch_width = TFT_FONT_12_CHAR_WIDTH;
            ch_height = TFT_FONT_12_CHAR_HEIGHT;
            ch_size = TFT_FONT_12_CHAR_SIZE;
            break;
        }


        case TFT_FONT_16:
        {
            ch_code = asc2_1608[ch_offset];
            ch_width = TFT_FONT_16_CHAR_WIDTH;
            ch_height = TFT_FONT_16_CHAR_HEIGHT;
            ch_size = TFT_FONT_16_CHAR_SIZE;
            break;
        }


        case TFT_FONT_24:
        {
            ch_code = asc2_2412[ch_offset];
            ch_width = TFT_FONT_24_CHAR_WIDTH;
            ch_height = TFT_FONT_24_CHAR_HEIGHT;
            ch_size = TFT_FONT_24_CHAR_SIZE;
            break;
        }


        case TFT_FONT_32:
        {
            ch_code = asc2_3216[ch_offset];
            ch_width = TFT_FONT_32_CHAR_WIDTH;
            ch_height = TFT_FONT_32_CHAR_HEIGHT;
            ch_size = TFT_FONT_32_CHAR_SIZE;
            break;
        }

        default:
        {
            return;
        }
    }
    
    if ((x + ch_width > TFT_COLUMN_NUMBER) || (y + ch_height > TFT_LINE_NUMBER))
    {
        return;
    }
	
    TFT_Clear_char(x,y,x + ch_width,y + ch_height,WHITE); //清除局部背景颜色
	
    for (byte_index=0; byte_index<ch_size; byte_index++)
    {
        byte_code = ch_code[byte_index];
        for (bit_index=0; bit_index<8; bit_index++)
        {
            if ((byte_code & 0x80) != 0)
            {
                TFT_draw_point(x + width_index, y + height_index, color);
            }
            height_index++;
            if (height_index == ch_height)
            {
                height_index = 0;
                width_index++;
                break;
            }
            byte_code <<= 1;
        }
    }
}

/**
 * @brief       ATK-MD0350模块LCD显示字符串
 * @note        会自动换行和换页
 * @param       x     : 待显示字符串的X坐标
 *              y     : 待显示字符串的Y坐标
 *              width : 待显示字符串的显示高度
 *              height: 待显示字符串的显示宽度
 *              str   : 待显示字符串
 *              font  : 待显示字符串的字体
 *              color : 待显示字符串的颜色
 * @retval      无
 */
void TFT_show_string(uint16_t x, uint16_t y, uint16_t width, char *str, tft_lcd_font_t font, uint16_t color)
{
    uint8_t ch_width;
    uint8_t ch_height;
    uint16_t x_raw;
    uint16_t y_raw;
    uint16_t x_limit;
    uint16_t y_limit;
    
    switch (font)
    {
        case TFT_FONT_12:
        {
            ch_width = TFT_FONT_12_CHAR_WIDTH;
            ch_height = TFT_FONT_12_CHAR_HEIGHT;
            break;
        }
        case TFT_FONT_16:
        {
            ch_width = TFT_FONT_16_CHAR_WIDTH;
            ch_height = TFT_FONT_16_CHAR_HEIGHT;
            break;
        }
        case TFT_FONT_24:
        {
            ch_width = TFT_FONT_24_CHAR_WIDTH;
            ch_height = TFT_FONT_24_CHAR_HEIGHT;
            break;
        }
        case TFT_FONT_32:
        {
            ch_width = TFT_FONT_32_CHAR_WIDTH;
            ch_height = TFT_FONT_32_CHAR_HEIGHT;
            break;
        }
        default:
        {
            return;
        }
    }
    
    x_raw = x;
    y_raw = y;
    x_limit = ((x + width + 1) > TFT_COLUMN_NUMBER) ? TFT_COLUMN_NUMBER : (x + width + 1);
    y_limit = ((y + ch_height + 1) > TFT_LINE_NUMBER) ? TFT_LINE_NUMBER : (y + ch_height + 1);
    
    while ((*str >= ' ') && (*str <= '~'))
    {
        if (x + ch_width >= x_limit)
        {
            x = x_raw;
            y += ch_height;
        }
        
        if (y + ch_height >= y_limit)
        {
            y = x_raw;
            x = y_raw;
        }
        
        TFT_show_char(x, y, *str, font, color);
        
        x += ch_width;
        str++;
    }
}

void TFT_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, tft_num_mode_t mode, tft_lcd_font_t font, uint16_t color)
{
    uint8_t ch_width;
    uint8_t len_index;
    uint8_t num_index;
    uint8_t first_nozero = 0;
    char pad;
    
    switch (font)
    {

        case TFT_FONT_12:
        {
            ch_width = TFT_FONT_12_CHAR_WIDTH;
            break;
        }


        case TFT_FONT_16:
        {
            ch_width = TFT_FONT_16_CHAR_WIDTH;
            break;
        }

        case TFT_FONT_24:
        {
            ch_width = TFT_FONT_24_CHAR_WIDTH;
            break;
        }

        case TFT_FONT_32:
        {
            ch_width = TFT_FONT_32_CHAR_WIDTH;
            break;
        }

        default:
        {
            return;
        }
    }
    
    switch (mode)
    {
        case TFT_NUM_SHOW_NOZERO:
        {
            pad = ' ';
            break;
        }
        case TFT_NUM_SHOW_ZERO:
        {
            pad = '0';
            break;
        }
        default:
        {
            return;
        }
    }
    
    for (len_index=0; len_index<len; len_index++)
    {
        num_index = (num / TFT_pow(10, len - len_index - 1)) % 10;
        if ((first_nozero == 0) && (len_index < (len - 1)))
        {
            if (num_index == 0)
            {
                TFT_show_char(x + ch_width * len_index, y, pad, font, color);
                continue;
            }
            else
            {
                first_nozero = 1;
            }
        }
        
        TFT_show_char(x + ch_width * len_index, y, num_index + '0', font, color);
    }
}
/**
 * @brief       ATK-MD0350模块LCD显示数字，不显示高位0
 * @param       x    : 待显示数字的X坐标
 *              y    : 待显示数字的Y坐标
 *              num  : 待显示数字
 *              len  : 待显示数字的位数
 *              font : 待显示数字的字体
 *              color: 待显示数字的颜色
 * @retval      无
 */
void TFT_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, tft_lcd_font_t font, uint16_t color)
{
    TFT_show_xnum(x, y, num, len, TFT_NUM_SHOW_NOZERO, font, color);
}

//字体背景黑色  
void TFT_show_Chinese_16x16(uint16_t x,uint16_t y,uint16_t color_char,uint16_t color_back,uint8_t word_number)
{
	unsigned int column;
	unsigned char tm = 0,temp = 0,num=0;
	
	TFT_send_cmd(0x2a);    //Column address set
	TFT_send_data(x>>8);    //start column
	TFT_send_data(x);
	x = x + 15;
	TFT_send_data(x>>8);    //end column
	TFT_send_data(x);
	
	TFT_send_cmd(0x2b);     //Row address set
	TFT_send_data(y>>8);    //start row
	TFT_send_data(y); 
	y = y + 15;
	TFT_send_data(y>>8);    //end row
	TFT_send_data(y);
	TFT_send_cmd(0x2C);     //Memory write
      
	for(column = 0;column < 32;column++)  //column loop
	{
		temp=chines_word[word_number][num];
		for(tm=0;tm < 8;tm++)
		{
			if(temp&0x01)
			{
				TFT_send_data(~color_char);
			}
			else 
			{
				TFT_send_data(~color_back);
			}
			temp >>= 1;
		}
		num++;
			
	}
}

/**
 * @brief       ATK-MD0350模块LCD图片
 * @note        图片取模方式: 水平扫描、RGB565、高位在前
 * @param       x     : 待显示图片的X坐标
 *              y     : 待显示图片的Y坐标
 *              width : 待显示图片的宽度
 *              height: 待显示图片的高度
 *              pic   : 待显示图片数组首地址
 * @retval      无
 */

void TFT_show_pic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *pic)
{
    uint16_t x_index;
    uint16_t y_index;
    
    if ((x + width > TFT_COLUMN_NUMBER) || (y + height > TFT_LINE_NUMBER))
    {
        return;
    }
    
    TFT_set_column_address(x, x + width - 1);
    TFT_set_page_address(y, y + height - 1);
    TFT_start_write_memory();
    for (y_index=y; y_index<=(y + height); y_index++)
    {
        for (x_index=x; x_index<=(x + width); x_index++)
        {
            TFT_send_data(*pic);
            pic++;
        }
    }
}

void Picture_Display(const uint8_t *ptr_pic)
{
    unsigned long  number;
	unsigned int pdata;
	TFT_send_cmd(0x2a); 		//Column address set
	TFT_send_data(0x00); 		//start column
	TFT_send_data(0x00); 
	TFT_send_data(0x00);		//end column
	TFT_send_data(0x77);

	TFT_send_cmd(0x2b); 		//Row address set
	TFT_send_data(0x00); 		//start row
	TFT_send_data(0x00); 
	TFT_send_data(0x00);		//end row
	TFT_send_data(0x78);
	TFT_send_cmd(0x2C);			//Memory write
	  
	for(number = 0;number < PIC_NUM;number++)	
    {
        pdata = *ptr_pic++;
		pdata <<= 8;
        pdata |= *ptr_pic++;
		number++;
        TFT_send_data(pdata);		
    }
}

