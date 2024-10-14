/**
 ****************************************************************************************************
 * @file        atk_md0350.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MD0350ģ����������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� MiniSTM32 V4������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "atk_md0350.h"
#include "atk_md0350_font.h"
#include "atk_md0350_gpio.h"
//#include "./SYSTEM/delay/delay.h"

/* ATK-MD0350ģ��LCD������ID */
#define ATK_MD0350_CHIP_ID          0x5310

/* ATK-MD0350ģ��LCDɨ�跽�� */
#define ATK_MD0350_SCAN_DIR_L2R_U2D (0x0000)
#define ATK_MD0350_SCAN_DIR_L2R_D2U (0x0080)
#define ATK_MD0350_SCAN_DIR_R2L_U2D (0x0040)
#define ATK_MD0350_SCAN_DIR_R2L_D2U (0x00C0)
#define ATK_MD0350_SCAN_DIR_U2D_L2R (0x0020)
#define ATK_MD0350_SCAN_DIR_U2D_R2L (0x0060)
#define ATK_MD0350_SCAN_DIR_D2U_L2R (0x00A0)
#define ATK_MD0350_SCAN_DIR_D2U_R2L (0x00E0)

/* ATK-MD0350ģ��״̬���ݽṹ�� */
struct
{
    uint16_t chip_id;                   /* ������ID */
    uint16_t width;                     /* LCD��� */
    uint16_t height;                    /* LCD�߶� */
    atk_md0350_lcd_scan_dir_t scan_dir; /* LCDɨ�跽�� */
    atk_md0350_lcd_disp_dir_t disp_dir; /* LCD��ʾ���� */
} g_atk_md0350_sta = {0};

/**
 * @brief       ATK-MD0350ģ��Ӳ����ʼ��
 * @param       ��
 * @retval      ��
 */
static void atk_md0350_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* ʹ��ʱ�� */
    ATK_MD0350_BL_GPIO_CLK_ENABLE();
    
    /* ��ʼ��BL���� */
    gpio_init_struct.Pin    = ATK_MD0350_BL_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_BL_GPIO_PORT, &gpio_init_struct);
    
    ATK_MD0350_BL(1);
}

/**
 * @brief       ��ȡATK-MD0350ģ��������ID
 * @param       ��
 * @retval      ��
 */
static inline uint16_t atk_md0350_get_chip_id(void)
{
    uint16_t chip_id;
    
    atk_md0350_gpio_write_cmd(0x04);
	chip_id = tft_gpio_read_dat(); //1st
    chip_id = tft_gpio_read_dat();
    chip_id = tft_gpio_read_dat() << 8;
    chip_id |= (tft_gpio_read_dat()) & 0x00FF;
	
//    chip_id = atk_md0350_gpio_read_dat(); //1st
//    chip_id = atk_md0350_gpio_read_dat();
//    chip_id = atk_md0350_gpio_read_dat() << 8;
//    chip_id |= (atk_md0350_gpio_read_dat()) & 0x00FF;
    
    return chip_id;
}

/**
 * @brief       ATK-MD0350ģ��Ĵ�����ʼ��
 * @param       ��
 * @retval      ��
 */
static void atk_md0350_reg_init(void)
{
	TFT_RST(1);
	HAL_Delay(100);

	//	RST=0;
	TFT_RST(0);
	HAL_Delay(100);

	//	RST=1;
	TFT_RST(1);
	HAL_Delay(100);
	
	atk_md0350_gpio_write_cmd(0x36); // Memory Data Access Control MY,MX~~
	atk_md0350_gpio_write_dat(0x48); // 

	atk_md0350_gpio_write_cmd(0x3A);
	atk_md0350_gpio_write_dat(0x55); // 55:RGB565 66:RGB666 77:RGB888

	atk_md0350_gpio_write_cmd(0xF0); // Command Set Control
	atk_md0350_gpio_write_dat(0xC3);

	atk_md0350_gpio_write_cmd(0xF0);
	atk_md0350_gpio_write_dat(0x96);

	atk_md0350_gpio_write_cmd(0xB4);
	atk_md0350_gpio_write_dat(0x01);

	atk_md0350_gpio_write_cmd(0xB7);
	atk_md0350_gpio_write_dat(0xC6);

	atk_md0350_gpio_write_cmd(0xC0);
	atk_md0350_gpio_write_dat(0x80);
	atk_md0350_gpio_write_dat(0x45);

	atk_md0350_gpio_write_cmd(0xC1);
	atk_md0350_gpio_write_dat(0x18); // 18  //00

	atk_md0350_gpio_write_cmd(0xC2);
	atk_md0350_gpio_write_dat(0xA7); // A7

	atk_md0350_gpio_write_cmd(0xC5);
	atk_md0350_gpio_write_dat(0x0A);

	atk_md0350_gpio_write_cmd(0xE8);
	atk_md0350_gpio_write_dat(0x40);
	atk_md0350_gpio_write_dat(0x8A);
	atk_md0350_gpio_write_dat(0x00);
	atk_md0350_gpio_write_dat(0x00);
	atk_md0350_gpio_write_dat(0x29);
	atk_md0350_gpio_write_dat(0x19);
	atk_md0350_gpio_write_dat(0xA5);
	atk_md0350_gpio_write_dat(0x33);

	atk_md0350_gpio_write_cmd(0xE0);
	atk_md0350_gpio_write_dat(0xD0);
	atk_md0350_gpio_write_dat(0x08);
	atk_md0350_gpio_write_dat(0x0F);
	atk_md0350_gpio_write_dat(0x06);
	atk_md0350_gpio_write_dat(0x06);
	atk_md0350_gpio_write_dat(0x33);
	atk_md0350_gpio_write_dat(0x30);
	atk_md0350_gpio_write_dat(0x33);
	atk_md0350_gpio_write_dat(0x47);
	atk_md0350_gpio_write_dat(0x17);
	atk_md0350_gpio_write_dat(0x13);
	atk_md0350_gpio_write_dat(0x13);
	atk_md0350_gpio_write_dat(0x2B);
	atk_md0350_gpio_write_dat(0x31);

	atk_md0350_gpio_write_cmd(0xE1);
	atk_md0350_gpio_write_dat(0xD0);
	atk_md0350_gpio_write_dat(0x0A);
	atk_md0350_gpio_write_dat(0x11);
	atk_md0350_gpio_write_dat(0x0B);
	atk_md0350_gpio_write_dat(0x09);
	atk_md0350_gpio_write_dat(0x07);
	atk_md0350_gpio_write_dat(0x2F);
	atk_md0350_gpio_write_dat(0x33);
	atk_md0350_gpio_write_dat(0x47);
	atk_md0350_gpio_write_dat(0x38);
	atk_md0350_gpio_write_dat(0x15);
	atk_md0350_gpio_write_dat(0x16);
	atk_md0350_gpio_write_dat(0x2C);
	atk_md0350_gpio_write_dat(0x32);

	atk_md0350_gpio_write_cmd(0xF0);
	atk_md0350_gpio_write_dat(0x3C);

	atk_md0350_gpio_write_cmd(0xF0);
	atk_md0350_gpio_write_dat(0x69);

	HAL_Delay(120);

	atk_md0350_gpio_write_cmd(0x21);

	atk_md0350_gpio_write_cmd(0x29);

}

/**
 * @brief       ����ATK-MD0350ģ���е�ַ
 * @param       ��
 * @retval      ��
 */
static void atk_md0350_set_column_address(uint16_t sc, uint16_t ec)
{
    atk_md0350_gpio_write_cmd(0x2A);
    atk_md0350_gpio_write_dat((uint8_t)(sc >> 8) & 0xFF);
    atk_md0350_gpio_write_dat((uint8_t)sc & 0xFF);
    atk_md0350_gpio_write_dat((uint8_t)(ec >> 8) & 0xFF);
    atk_md0350_gpio_write_dat((uint8_t)ec & 0xFF);
}

/**
 * @brief       ����ATK-MD0350ģ��ҳ��ַ
 * @param       ��
 * @retval      ��
 */
static void atk_md0350_set_page_address(uint16_t sp, uint16_t ep)
{
    atk_md0350_gpio_write_cmd(0x2B);
    atk_md0350_gpio_write_dat((uint8_t)(sp >> 8) & 0xFF);
    atk_md0350_gpio_write_dat((uint8_t)sp & 0xFF);
    atk_md0350_gpio_write_dat((uint8_t)(ep >> 8) & 0xFF);
    atk_md0350_gpio_write_dat((uint8_t)ep & 0xFF);
}

/**
 * @brief       ��ʼдATK-MD0350ģ���Դ�
 * @param       ��
 * @retval      ��
 */
static void atk_md0350_start_write_memory(void)
{
    atk_md0350_gpio_write_cmd(0x2C);
}

/**
 * @brief       ��ʼ��ATK-MD0350ģ���Դ�
 * @param       ��
 * @retval      ��
 */
static void atk_md0350_start_read_memory(void)
{
    atk_md0350_gpio_write_cmd(0x2E);
}

/**
 * @brief       ƽ��������x^y
 * @param       x: ����
 *              y: ָ��
 * @retval      x^y
 */
static uint32_t atk_md0350_pow(uint8_t x, uint8_t y)
{
    uint8_t loop;
    uint32_t res = 1;
    
    for (loop=0; loop<y; loop++)
    {
        res *= x;
    }
    
    return res;
}

uint16_t Mychip_id;
/**
 * @brief       ATK-MD0350ģ���ʼ��
 * @param       ��
 * @retval      ATK_MD0350_EOK  : ATK_MD0350ģ���ʼ���ɹ�
 *              ATK_MD0350_ERROR: ATK_MD0350ģ���ʼ��ʧ��
 */
uint8_t atk_md0350_init(void)
{

    
    atk_md0350_hw_init();               /* 1.������ */
    atk_md0350_gpio_init();             /* 2.GPIO�ӿڳ�ʼ�� */
    Mychip_id = atk_md0350_get_chip_id(); /* 3.��ȡATK-MD0350ģ��������ID */
//    if (chip_id != ATK_MD0350_CHIP_ID)
//    {
//        return ATK_MD0350_ERROR;
//    }
//    else
//    {
        g_atk_md0350_sta.chip_id = Mychip_id;
        g_atk_md0350_sta.width = ATK_MD0350_LCD_WIDTH;
        g_atk_md0350_sta.height = ATK_MD0350_LCD_HEIGHT;
//    }
    atk_md0350_reg_init(); 		//4.�Ĵ�����ʼ��
    atk_md0350_set_disp_dir(ATK_MD0350_LCD_DISP_DIR_0); //5.������Ļ����
    atk_md0350_clear(ATK_MD0350_WHITE);
    atk_md0350_display_on();
    atk_md0350_backlight_on();
	
#if (ATK_MD0350_USING_TOUCH != 0)
    atk_md0350_touch_init();
#endif
    
    return ATK_MD0350_EOK;
}

/**
 * @brief       ��ȡATK-MD0350ģ��LCD���
 * @param       ��
 * @retval      ATK-MD0350ģ��LCD���
 */
uint16_t atk_md0350_get_lcd_width(void)
{
    return g_atk_md0350_sta.width;
}

/**
 * @brief       ��ȡATK-MD0350ģ��LCD�߶�
 * @param       ��
 * @retval      ATK-MD0350ģ��LCD�߶�
 */
uint16_t atk_md0350_get_lcd_height(void)
{
    return g_atk_md0350_sta.height;
}

/**
 * @brief       ����ATK-MD0350ģ��LCD����
 * @param       ��
 * @retval      ��
 */
void atk_md0350_backlight_on(void)
{
    ATK_MD0350_BL(1);
}

/**
 * @brief       �ر�ATK-MD0350ģ��LCD����
 * @param       ��
 * @retval      ��
 */
void atk_md0350_backlight_off(void)
{
    ATK_MD0350_BL(0);
}

/**
 * @brief       ����ATK-MD0350ģ��LCD��ʾ
 * @param       ��
 * @retval      ��
 */
void atk_md0350_display_on(void)
{
    atk_md0350_gpio_write_cmd(0x29);
}

/**
 * @brief       �ر�ATK-MD0350ģ��LCD��ʾ
 * @param       ��
 * @retval      ��
 */
void atk_md0350_display_off(void)
{
    atk_md0350_gpio_write_cmd(0x28);
}

/**
 * @brief       ����ATK-MD0350ģ��LCDɨ�跽��
 * @param       scan_dir: ATK_MD0350_LCD_SCAN_DIR_L2R_U2D: �����ң����ϵ���
 *                        ATK_MD0350_LCD_SCAN_DIR_L2R_D2U: �����ң����µ���
 *                        ATK_MD0350_LCD_SCAN_DIR_R2L_U2D: ���ҵ��󣬴��ϵ���
 *                        ATK_MD0350_LCD_SCAN_DIR_R2L_D2U: ���ҵ��󣬴��µ���
 *                        ATK_MD0350_LCD_SCAN_DIR_U2D_L2R: ���ϵ��£�������
 *                        ATK_MD0350_LCD_SCAN_DIR_U2D_R2L: ���ϵ��£����ҵ���
 *                        ATK_MD0350_LCD_SCAN_DIR_D2U_L2R: ���µ��ϣ�������
 *                        ATK_MD0350_LCD_SCAN_DIR_D2U_R2L: ���µ��ϣ����ҵ���
 * @retval      ATK_MD0350_EOK   : ����ATK-MD0350ģ��LCDɨ�跽��ɹ�
 *              ATK_MD0350_ERROR : ����ATK-MD0350ģ��LCDɨ�跽��ʧ��
*               ATK_MD0350_EINVAL: �����������
 */
uint8_t atk_md0350_set_scan_dir(atk_md0350_lcd_scan_dir_t scan_dir)
{
    uint16_t reg36;
    
    switch (g_atk_md0350_sta.disp_dir)
    {
        case ATK_MD0350_LCD_DISP_DIR_0:
        {
            reg36 = (uint16_t)scan_dir;
            break;
        }
        case ATK_MD0350_LCD_DISP_DIR_90:
        {
            switch (scan_dir)
            {
                case ATK_MD0350_LCD_SCAN_DIR_L2R_U2D:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_U2D_R2L;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_L2R_D2U:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_U2D_L2R;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_R2L_U2D:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_D2U_R2L;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_R2L_D2U:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_D2U_L2R;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_U2D_L2R:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_R2L_U2D;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_U2D_R2L:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_R2L_D2U;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_D2U_L2R:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_L2R_U2D;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_D2U_R2L:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_L2R_D2U;
                    break;
                }
                default:
                {
                    return ATK_MD0350_EINVAL;
                }
            }
            break;
        }
        case ATK_MD0350_LCD_DISP_DIR_180:
        {
            switch (scan_dir)
            {
                case ATK_MD0350_LCD_SCAN_DIR_L2R_U2D:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_R2L_D2U;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_L2R_D2U:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_R2L_U2D;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_R2L_U2D:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_L2R_D2U;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_R2L_D2U:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_L2R_U2D;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_U2D_L2R:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_D2U_R2L;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_U2D_R2L:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_D2U_L2R;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_D2U_L2R:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_U2D_R2L;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_D2U_R2L:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_U2D_L2R;
                    break;
                }
                default:
                {
                    return ATK_MD0350_EINVAL;
                }
            }
            break;
        }
        case ATK_MD0350_LCD_DISP_DIR_270:
        {
            switch (scan_dir)
            {
                case ATK_MD0350_LCD_SCAN_DIR_L2R_U2D:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_D2U_L2R;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_L2R_D2U:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_D2U_R2L;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_R2L_U2D:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_U2D_L2R;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_R2L_D2U:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_U2D_R2L;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_U2D_L2R:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_L2R_D2U;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_U2D_R2L:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_L2R_U2D;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_D2U_L2R:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_R2L_D2U;
                    break;
                }
                case ATK_MD0350_LCD_SCAN_DIR_D2U_R2L:
                {
                    reg36 = ATK_MD0350_LCD_SCAN_DIR_R2L_U2D;
                    break;
                }
                default:
                {
                    return ATK_MD0350_EINVAL;
                }
            }
            break;
        }
        default:
        {
            return ATK_MD0350_ERROR;
        }
    }
    
    g_atk_md0350_sta.scan_dir = (atk_md0350_lcd_scan_dir_t)reg36;
    atk_md0350_gpio_write_reg(0X36, reg36);
    atk_md0350_set_column_address(0, g_atk_md0350_sta.width - 1);
    atk_md0350_set_page_address(0, g_atk_md0350_sta.height - 1);
    
    return ATK_MD0350_EOK;
}

/**
 * @brief       ����ATK-MD0350ģ��LCD��ʾ����
 * @param       disp_dir: ATK_MD0350_LCD_DISP_DIR_0  : LCD˳ʱ����ת0����ʾ����
 *                        ATK_MD0350_LCD_DISP_DIR_90 : LCD˳ʱ����ת90����ʾ����
 *                        ATK_MD0350_LCD_DISP_DIR_180: LCD˳ʱ����ת180����ʾ����
 *                        ATK_MD0350_LCD_DISP_DIR_270: LCD˳ʱ����ת270����ʾ����
 * @retval      ATK_MD0350_EOK   : ����ATK-MD0350ģ��LCD��ʾ����ɹ�
 *              ATK_MD0350_EINVAL: �����������
 */
uint8_t atk_md0350_set_disp_dir(atk_md0350_lcd_disp_dir_t disp_dir)
{
    switch (disp_dir)
    {
        case ATK_MD0350_LCD_DISP_DIR_0:
        {
            g_atk_md0350_sta.width = ATK_MD0350_LCD_WIDTH;
            g_atk_md0350_sta.height = ATK_MD0350_LCD_HEIGHT;
            break;
        }
        case ATK_MD0350_LCD_DISP_DIR_90:
        {
            g_atk_md0350_sta.width = ATK_MD0350_LCD_HEIGHT;
            g_atk_md0350_sta.height = ATK_MD0350_LCD_WIDTH;
            break;
        }
        case ATK_MD0350_LCD_DISP_DIR_180:
        {
            g_atk_md0350_sta.width = ATK_MD0350_LCD_WIDTH;
            g_atk_md0350_sta.height = ATK_MD0350_LCD_HEIGHT;
            break;
        }
        case ATK_MD0350_LCD_DISP_DIR_270:
        {
            g_atk_md0350_sta.width = ATK_MD0350_LCD_HEIGHT;
            g_atk_md0350_sta.height = ATK_MD0350_LCD_WIDTH;
            break;
        }
        default:
        {
            return ATK_MD0350_EINVAL;
        }
    }
    
    g_atk_md0350_sta.disp_dir = disp_dir;
    atk_md0350_set_scan_dir(ATK_MD0350_LCD_SCAN_DIR_L2R_U2D);
    
    return ATK_MD0350_EOK;
}

/**
 * @brief       ��ȡATK-MD0350ģ��LCDɨ�跽��
 * @param       ��
 * @retval      ATK-MD0350ģ��LCDɨ�跽��
 */
atk_md0350_lcd_scan_dir_t atk_md0350_get_scan_dir(void)
{
    return g_atk_md0350_sta.scan_dir;
}

/**
 * @brief       ��ȡATK-MD0350ģ��LCD��ʾ����
 * @param       ��
 * @retval      ATK-MD0350ģ��LCD��ʾ����
 */
atk_md0350_lcd_disp_dir_t atk_md0350_get_disp_dir(void)
{
    return g_atk_md0350_sta.disp_dir;
}

/**
 * @brief       ATK-MD0350ģ��LCD�������
 * @param       xs   : ������ʼX����
 *              ys   : ������ʼY����
 *              xe   : ������ֹX����
 *              ye   : ������ֹY����
 *              color: ���������ɫ
 * @retval      ��
 */
void atk_md0350_fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    uint16_t x_index;
    uint16_t y_index;
    
    atk_md0350_set_column_address(xs, xe);
    atk_md0350_set_page_address(ys, ye);
    atk_md0350_start_write_memory();
    for (y_index=ys; y_index<=ye; y_index++)
    {
        for (x_index=xs; x_index<= xe; x_index++)
        {
            atk_md0350_gpio_write_dat(color);
        }
    }
}

/**
 * @brief       ATK-MD0350ģ��LCD����
 * @param       color: ������ɫ
 * @retval      ��
 */
void atk_md0350_clear(uint16_t color)
{
    atk_md0350_fill(0, 0, ATK_MD0350_LCD_WIDTH - 1, ATK_MD0350_LCD_HEIGHT - 1, color);
}

/**
 * @brief       ATK-MD0350ģ��LCD����
 * @param       x    : �������X����
 *              y    : �������Y����
 *              color: ���������ɫ
 * @retval      ��
 */
void atk_md0350_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    atk_md0350_set_column_address(x, x);
    atk_md0350_set_page_address(y, y);
    atk_md0350_start_write_memory();
    atk_md0350_gpio_write_dat(color);
}

/**
 * @brief       ATK-MD0350ģ��LCD����
 * @param       x    : �������X����
 *              y    : �������Y����
 * @retval      ���������ɫ
 */
uint16_t atk_md0350_read_point(uint16_t x, uint16_t y)
{
    uint16_t color;
    uint8_t color_r;
    uint8_t color_g;
    uint8_t color_b;
    
    if ((x >= g_atk_md0350_sta.width) || (y >= g_atk_md0350_sta.height))
    {
        return ATK_MD0350_EINVAL;
    }
    
    atk_md0350_set_column_address(x, x);
    atk_md0350_set_page_address(y, y);
    atk_md0350_start_read_memory();
    
//    color = atk_md0350_gpio_read_dat(); /* Dummy */
//    color = atk_md0350_gpio_read_dat(); /* [15:11]: R, [7:2]:G */
	color = tft_gpio_read_dat(); /* Dummy */
    color = tft_gpio_read_dat(); /* [15:11]: R, [7:2]:G */
	
    color_r = (uint8_t)(color >> 11) & 0x1F;
    color_g = (uint8_t)(color >> 2) & 0x3F;
//    color = atk_md0350_gpio_read_dat(); /* [15:11]: B */
	    color = tft_gpio_read_dat(); /* [15:11]: B */
    color_b = (uint8_t)(color >> 11) & 0x1F;
    
    return (uint16_t)(color_r << 11) | (color_g << 5) | color_b;
}

/**
 * @brief       ATK-MD0350ģ��LCD���߶�
 * @param       x1   : �����߶ζ˵�1��X����
 *              y1   : �����߶ζ˵�1��Y����
 *              x2   : �����߶ζ˵�2��X����
 *              y2   : �����߶ζ˵�2��Y����
 *              color: �����߶ε���ɫ
 * @retval      ��
 */
void atk_md0350_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t x_delta;
    uint16_t y_delta;
    int16_t x_sign;
    int16_t y_sign;
    int16_t error;
    int16_t error2;
    
    x_delta = (x1 < x2) ? (x2 - x1) : (x1 - x2);
    y_delta = (y1 < y2) ? (y2 - y1) : (y1 - y2);
    x_sign = (x1 < x2) ? 1 : -1;
    y_sign = (y1 < y2) ? 1 : -1;
    error = x_delta - y_delta;
    
    atk_md0350_draw_point(x2, y2, color);
    
    while ((x1 != x2) || (y1 != y2))
    {
        atk_md0350_draw_point(x1, y1, color);
        
        error2 = error << 1;
        if (error2 > -y_delta)
        {
            error -= y_delta;
            x1 += x_sign;
        }
        
        if (error2 < x_delta)
        {
            error += x_delta;
            y1 += y_sign;
        }
    }
}

/**
 * @brief       ATK-MD0350ģ��LCD�����ο�
 * @param       x1   : �������ο�˵�1��X����
 *              y1   : �������ο�˵�1��Y����
 *              x2   : �������ο�˵�2��X����
 *              y2   : �������ο�˵�2��Y����
 *              color: �������ο����ɫ
 * @retval      ��
 */
void atk_md0350_draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    atk_md0350_draw_line(x1, y1, x2, y1, color);
    atk_md0350_draw_line(x1, y2, x2, y2, color);
    atk_md0350_draw_line(x1, y1, x1, y2, color);
    atk_md0350_draw_line(x2, y1, x2, y2, color);
}

/**
 * @brief       ATK-MD0350ģ��LCD��Բ�ο�
 * @param       x    : ����Բ�ο�ԭ���X����
 *              y    : ����Բ�ο�ԭ���Y����
 *              r    : ����Բ�ο�İ뾶
 *              color: ����Բ�ο����ɫ
 * @retval      ��
 */
void atk_md0350_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
    int32_t x_t;
    int32_t y_t;
    int32_t error;
    int32_t error2;
    
    x_t = -r;
    y_t = 0;
    error = 2 - 2 * r;
    
    do {
        atk_md0350_draw_point(x - x_t, y + y_t, color);
        atk_md0350_draw_point(x + x_t, y + y_t, color);
        atk_md0350_draw_point(x + x_t, y - y_t, color);
        atk_md0350_draw_point(x - x_t, y - y_t, color);
        
        error2 = error;
        if (error2 <= y_t)
        {
            y_t++;
            error = error + (y_t * 2 + 1);
            if ((-x_t == y_t) && (error2 <= x_t))
            {
                error2 = 0;
            }
        }
        
        if (error2 > x_t)
        {
            x_t++;
            error = error + (x_t * 2 + 1);
        }
    } while (x_t <= 0);
}

/**
 * @brief       ATK-MD0350ģ��LCD��ʾ1���ַ�
 * @param       x    : ����ʾ�ַ���X����
 *              y    : ����ʾ�ַ���Y����
 *              ch   : ����ʾ�ַ�
 *              font : ����ʾ�ַ�������
 *              color: ����ʾ�ַ�����ɫ
 * @retval      ��
 */
void atk_md0350_show_char(uint16_t x, uint16_t y, char ch, atk_md0350_lcd_font_t font, uint16_t color)
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
#if (ATK_MD0350_FONT_12 != 0)
        case ATK_MD0350_LCD_FONT_12:
        {
            ch_code = atk_md0350_font_1206[ch_offset];
            ch_width = ATK_MD0350_FONT_12_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_12_CHAR_HEIGHT;
            ch_size = ATK_MD0350_FONT_12_CHAR_SIZE;
            break;
        }
#endif
#if (ATK_MD0350_FONT_16 != 0)
        case ATK_MD0350_LCD_FONT_16:
        {
            ch_code = atk_md0350_font_1608[ch_offset];
            ch_width = ATK_MD0350_FONT_16_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_16_CHAR_HEIGHT;
            ch_size = ATK_MD0350_FONT_16_CHAR_SIZE;
            break;
        }
#endif
#if (ATK_MD0350_FONT_24 != 0)
        case ATK_MD0350_LCD_FONT_24:
        {
            ch_code = atk_md0350_font_2412[ch_offset];
            ch_width = ATK_MD0350_FONT_24_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_24_CHAR_HEIGHT;
            ch_size = ATK_MD0350_FONT_24_CHAR_SIZE;
            break;
        }
#endif
#if (ATK_MD0350_FONT_32 != 0)
        case ATK_MD0350_LCD_FONT_32:
        {
            ch_code = atk_md0350_font_3216[ch_offset];
            ch_width = ATK_MD0350_FONT_32_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_32_CHAR_HEIGHT;
            ch_size = ATK_MD0350_FONT_32_CHAR_SIZE;
            break;
        }
#endif
        default:
        {
            return;
        }
    }
    
    if ((x + ch_width > ATK_MD0350_LCD_WIDTH) || (y + ch_height > ATK_MD0350_LCD_HEIGHT))
    {
        return;
    }
    
    for (byte_index=0; byte_index<ch_size; byte_index++)
    {
        byte_code = ch_code[byte_index];
        for (bit_index=0; bit_index<8; bit_index++)
        {
            if ((byte_code & 0x80) != 0)
            {
                atk_md0350_draw_point(x + width_index, y + height_index, color);
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
 * @brief       ATK-MD0350ģ��LCD��ʾ�ַ���
 * @note        ���Զ����кͻ�ҳ
 * @param       x     : ����ʾ�ַ�����X����
 *              y     : ����ʾ�ַ�����Y����
 *              width : ����ʾ�ַ�������ʾ�߶�
 *              height: ����ʾ�ַ�������ʾ���
 *              str   : ����ʾ�ַ���
 *              font  : ����ʾ�ַ���������
 *              color : ����ʾ�ַ�������ɫ
 * @retval      ��
 */
void atk_md0350_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, char *str, atk_md0350_lcd_font_t font, uint16_t color)
{
    uint8_t ch_width;
    uint8_t ch_height;
    uint16_t x_raw;
    uint16_t y_raw;
    uint16_t x_limit;
    uint16_t y_limit;
    
    switch (font)
    {
#if (ATK_MD0350_FONT_12 != 0)
        case ATK_MD0350_LCD_FONT_12:
        {
            ch_width = ATK_MD0350_FONT_12_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_12_CHAR_HEIGHT;
            break;
        }
#endif
#if (ATK_MD0350_FONT_16 != 0)
        case ATK_MD0350_LCD_FONT_16:
        {
            ch_width = ATK_MD0350_FONT_16_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_16_CHAR_HEIGHT;
            break;
        }
#endif
#if (ATK_MD0350_FONT_24 != 0)
        case ATK_MD0350_LCD_FONT_24:
        {
            ch_width = ATK_MD0350_FONT_24_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_24_CHAR_HEIGHT;
            break;
        }
#endif
#if (ATK_MD0350_FONT_32 != 0)
        case ATK_MD0350_LCD_FONT_32:
        {
            ch_width = ATK_MD0350_FONT_32_CHAR_WIDTH;
            ch_height = ATK_MD0350_FONT_32_CHAR_HEIGHT;
            break;
        }
#endif
        default:
        {
            return;
        }
    }
    
    x_raw = x;
    y_raw = y;
    x_limit = ((x + width + 1) > ATK_MD0350_LCD_WIDTH) ? ATK_MD0350_LCD_WIDTH : (x + width + 1);
    y_limit = ((y + height + 1) > ATK_MD0350_LCD_HEIGHT) ? ATK_MD0350_LCD_HEIGHT : (y + height + 1);
    
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
        
        atk_md0350_show_char(x, y, *str, font, color);
        
        x += ch_width;
        str++;
    }
}

/**
 * @brief       ATK-MD0350ģ��LCD��ʾ���֣��ɿ�����ʾ��λ0
 * @param       x    : ����ʾ���ֵ�X����
 *              y    : ����ʾ���ֵ�Y����
 *              num  : ����ʾ����
 *              len  : ����ʾ���ֵ�λ��
 *              mode : ATK_MD0350_NUM_SHOW_NOZERO: ���ָ�λ0����ʾ
 *                     ATK_MD0350_NUM_SHOW_ZERO  : ���ָ�λ0��ʾ
 *              font : ����ʾ���ֵ�����
 *              color: ����ʾ���ֵ���ɫ
 * @retval      ��
 */
void atk_md0350_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, atk_md0350_num_mode_t mode, atk_md0350_lcd_font_t font, uint16_t color)
{
    uint8_t ch_width;
    uint8_t len_index;
    uint8_t num_index;
    uint8_t first_nozero = 0;
    char pad;
    
    switch (font)
    {
#if (ATK_MD0350_FONT_12 != 0)
        case ATK_MD0350_LCD_FONT_12:
        {
            ch_width = ATK_MD0350_FONT_12_CHAR_WIDTH;
            break;
        }
#endif
#if (ATK_MD0350_FONT_16 != 0)
        case ATK_MD0350_LCD_FONT_16:
        {
            ch_width = ATK_MD0350_FONT_16_CHAR_WIDTH;
            break;
        }
#endif
#if (ATK_MD0350_FONT_24 != 0)
        case ATK_MD0350_LCD_FONT_24:
        {
            ch_width = ATK_MD0350_FONT_24_CHAR_WIDTH;
            break;
        }
#endif
#if (ATK_MD0350_FONT_32 != 0)
        case ATK_MD0350_LCD_FONT_32:
        {
            ch_width = ATK_MD0350_FONT_32_CHAR_WIDTH;
            break;
        }
#endif
        default:
        {
            return;
        }
    }
    
    switch (mode)
    {
        case ATK_MD0350_NUM_SHOW_NOZERO:
        {
            pad = ' ';
            break;
        }
        case ATK_MD0350_NUM_SHOW_ZERO:
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
        num_index = (num / atk_md0350_pow(10, len - len_index - 1)) % 10;
        if ((first_nozero == 0) && (len_index < (len - 1)))
        {
            if (num_index == 0)
            {
                atk_md0350_show_char(x + ch_width * len_index, y, pad, font, color);
                continue;
            }
            else
            {
                first_nozero = 1;
            }
        }
        
        atk_md0350_show_char(x + ch_width * len_index, y, num_index + '0', font, color);
    }
}

/**
 * @brief       ATK-MD0350ģ��LCD��ʾ���֣�����ʾ��λ0
 * @param       x    : ����ʾ���ֵ�X����
 *              y    : ����ʾ���ֵ�Y����
 *              num  : ����ʾ����
 *              len  : ����ʾ���ֵ�λ��
 *              font : ����ʾ���ֵ�����
 *              color: ����ʾ���ֵ���ɫ
 * @retval      ��
 */
void atk_md0350_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, atk_md0350_lcd_font_t font, uint16_t color)
{
    atk_md0350_show_xnum(x, y, num, len, ATK_MD0350_NUM_SHOW_NOZERO, font, color);
}

/**
 * @brief       ATK-MD0350ģ��LCDͼƬ
 * @note        ͼƬȡģ��ʽ: ˮƽɨ�衢RGB565����λ��ǰ
 * @param       x     : ����ʾͼƬ��X����
 *              y     : ����ʾͼƬ��Y����
 *              width : ����ʾͼƬ�Ŀ��
 *              height: ����ʾͼƬ�ĸ߶�
 *              pic   : ����ʾͼƬ�����׵�ַ
 * @retval      ��
 */
void atk_md0350_show_pic(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *pic)
{
    uint16_t x_index;
    uint16_t y_index;
    
    if ((x + width > ATK_MD0350_LCD_WIDTH) || (y + height > ATK_MD0350_LCD_HEIGHT))
    {
        return;
    }
    
    atk_md0350_set_column_address(x, x + width - 1);
    atk_md0350_set_page_address(y, y + height - 1);
    atk_md0350_start_write_memory();
    for (y_index=y; y_index<=(y + height); y_index++)
    {
        for (x_index=x; x_index<=(x + width); x_index++)
        {
            atk_md0350_gpio_write_dat(*pic);
            pic++;
        }
    }
}
