#include "tft_display.h"
#include "tft.h"
//----------------------------------------------------------------------
void WriteComm(uint16_t data)
{
	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(0);

	//	DBH=i>>8;
	//	DBL=i;
	Write_TFT_Data(data);
	TFT_WR(0);
	TFT_WR(1);

	TFT_CS(1);
}

void WriteData(uint16_t data)
{
	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	//	DBH=i>>8;
	//	DBL=i;
	Write_TFT_Data(data);

	TFT_WR(0);
	TFT_WR(1);

	TFT_CS(1);
}

void WriteDispData(uint16_t data)
{
	// TFT_CS(0);
	// TFT_RD(1);
	// TFT_RS(1);

	//	 DBH=DataH;
	//	 DBL=DataL;
	Write_TFT_Data(data);
	TFT_WR(0);
	TFT_WR(1);

	// TFT_CS(1);
}

void WriteOneDot(uint16_t color)
{

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	//	DBH=color>>8;
	//	DBL=color;
	Write_TFT_Data(color);
	TFT_WR(0);
	TFT_WR(1);

	TFT_CS(1);
}

void LCD_Init(void)
{
	// TFT_CS(0);

	//	RST=1;
	TFT_RST(1);
	HAL_Delay(200);

	//	RST=0;
	TFT_RST(0);
	HAL_Delay(500);

	//	RST=1;
	TFT_RST(1);
	HAL_Delay(500);

	HAL_Delay(120);

	WriteComm(0x11);

	HAL_Delay(120); // HAL_Delay 120ms

	WriteComm(0x36); // Memory Data Access Control MY,MX~~
	WriteData(0x48); // 28  转90度 		   48 竖	 fc 横 fpc

	WriteComm(0x3A);
	WriteData(0x55); // 55:RGB565 66:RGB666 77:RGB888

	WriteComm(0xF0); // Command Set Control
	WriteData(0xC3);

	WriteComm(0xF0);
	WriteData(0x96);

	WriteComm(0xB4);
	WriteData(0x01);

	WriteComm(0xB7);
	WriteData(0xC6);

	WriteComm(0xC0);
	WriteData(0x80);
	WriteData(0x45);

	WriteComm(0xC1);
	WriteData(0x18); // 18  //00

	WriteComm(0xC2);
	WriteData(0xA7); // A7

	WriteComm(0xC5);
	WriteData(0x0A);

	WriteComm(0xE8);
	WriteData(0x40);
	WriteData(0x8A);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x29);
	WriteData(0x19);
	WriteData(0xA5);
	WriteData(0x33);

	WriteComm(0xE0);
	WriteData(0xD0);
	WriteData(0x08);
	WriteData(0x0F);
	WriteData(0x06);
	WriteData(0x06);
	WriteData(0x33);
	WriteData(0x30);
	WriteData(0x33);
	WriteData(0x47);
	WriteData(0x17);
	WriteData(0x13);
	WriteData(0x13);
	WriteData(0x2B);
	WriteData(0x31);

	WriteComm(0xE1);
	WriteData(0xD0);
	WriteData(0x0A);
	WriteData(0x11);
	WriteData(0x0B);
	WriteData(0x09);
	WriteData(0x07);
	WriteData(0x2F);
	WriteData(0x33);
	WriteData(0x47);
	WriteData(0x38);
	WriteData(0x15);
	WriteData(0x16);
	WriteData(0x2C);
	WriteData(0x32);

	WriteComm(0xF0);
	WriteData(0x3C);

	WriteComm(0xF0);
	WriteData(0x69);

	HAL_Delay(120);

	WriteComm(0x21);

	WriteComm(0x29);
}

void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend)
{
	WriteComm(0x2A);
	// WriteData(Xstart >> 8);
	// WriteData(Xstart);
	// WriteData(Xend >> 8);
	// WriteData(Xend);
	WriteData(Xstart);
	WriteData(Xend);	
	WriteData(0x7f);

	WriteComm(0x2B);
	// WriteData(Ystart >> 8);
	// WriteData(Ystart);
	// WriteData(Yend >> 8);
	// WriteData(Yend);
	WriteData(Ystart);
	WriteData(Yend);

	WriteData(0x7f);

	WriteComm(0x2c);
}

void DispColor(unsigned char color)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);
	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < ROW / 8; j++)
		{
			for (k = 0; k < COL; k++)
			{
				DBL = color; //>>8;
				TFT_WR(0);
				TFT_WR(1);

				DBL = color;
				TFT_WR(0);
				TFT_WR(1);
				//
				//				DBL=color;
				//				TFT_WR(0);
				//				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispColor1(uint16_t color)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);
	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < ROW / 8; j++)
		{
			for (k = 0; k < COL; k++)
			{
				//				DBH=colorH;//>>8;
				//				DBL=colorL;
				Write_TFT_Data(color);
				TFT_WR(0);
				TFT_WR(1);
				//
				//				DBL=color;
				//				TFT_WR(0);
				//				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispBand(void)
{
	unsigned int i, j, k;
	// unsigned int color[8]={0x001f,0x07e0,0xf800,0x07ff,0xf81f,0xffe0,0x0000,0xffff};
	unsigned int color[8] = {0xf800, 0xf800, 0x07e0, 0x07e0, 0x001f, 0x001f, 0xffff, 0xffff}; // 0x94B2
	// unsigned int gray16[]={0x0000,0x1082,0x2104,0x3186,0x42,0x08,0x528a,0x630c,0x738e,0x7bcf,0x9492,0xa514,0xb596,0xc618,0xd69a,0xe71c,0xffff};

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < ROW / 8; j++)
		{
			for (k = 0; k < COL; k++)
			{
				//				DBL=color[i]>>8;
				//				TFT_WR(0);
				//				TFT_WR(1);

				DBL = color[i];
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}
	for (j = 0; j < ROW % 8; j++)
	{
		for (k = 0; k < COL; k++)
		{
			//			DBL=color[7]>>8;
			//			TFT_WR(0);
			//			TFT_WR(1);

			DBL = color[7];
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	TFT_CS(1);
}

void DispFrame(void)
{
	unsigned int i, j;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

//	DBH = RED >> 8;
//	DBL = RED;
	Write_TFT_Data(RED);
	
	TFT_WR(0);
	TFT_WR(1);
	for (i = 0; i < COL - 2; i++)
	{
//		DBH = RED >> 8;
//		DBL = RED;
		Write_TFT_Data(RED);
		TFT_WR(0);
		TFT_WR(1);
	}
//		DBH = RED >> 8;
//		DBL = RED;
		Write_TFT_Data(RED);
	TFT_WR(0);
	TFT_WR(1);

	for (j = 0; j < ROW - 2; j++)
	{
//		DBH = RED >> 8;
//		DBL = RED;
		Write_TFT_Data(RED);
		TFT_WR(0);
		TFT_WR(1);
		for (i = 0; i < COL - 2; i++)
		{
//			DBH = BLACK >> 8;
//			DBL = BLACK;
			Write_TFT_Data(BLACK);
			TFT_WR(0);
			TFT_WR(1);
		}
//		DBH = RED >> 8;
//		DBL = RED;
		Write_TFT_Data(RED);
		TFT_WR(0);
		TFT_WR(1);
	}

//		DBH = RED >> 8;
//		DBL = RED;
		Write_TFT_Data(RED);
	TFT_WR(0);
	TFT_WR(1);
	for (i = 0; i < COL - 2; i++)
	{
//		DBH = RED >> 8;
//		DBL = RED;
		Write_TFT_Data(RED);
		TFT_WR(0);
		TFT_WR(1);
	}
//		DBH = RED >> 8;
//		DBL = RED;
		Write_TFT_Data(RED);
	TFT_WR(0);
	TFT_WR(1);

	TFT_CS(1);
}
/*
void DispScaleVer_Gray(void)
{
	unsigned int i,j,k;

	BlockWrite(0,COL-1,0,ROW-1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// BLACK
	for(k=0;k<ROW%32;k++)
	{
		for(j=0;j<COL;j++)
		{
			DBL=0;
			TFT_WR(0);
			TFT_WR(1);

			DBL=0;
			TFT_WR(0);
			TFT_WR(1);

		}
	}

	for(k=0;k<32;k++)
	{
		for(i=0;i<ROW/32;i++)
		{
			// GRAY
			for(j=0;j<COL;j++)
			{
				DBL=(k<<3)|((k*2)>>3);
				TFT_WR(0);
				TFT_WR(1);

				DBL=((k*2)<<5)|k;
				TFT_WR(0);
				TFT_WR(1);
			}
		}

	}

	TFT_CS(1);
}
*/

#ifdef EVAL_PIC
void DispPic(unsigned int code *picture)
{
	unsigned int *p;
	unsigned int i, j;	// i-row,j-col
	unsigned char n, k; // n-row repeat count,k-col repeat count

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	RS = 1;
	TFT_RD(1);

	for (n = 0; n < ROW / PIC_HEIGHT; n++) // n-row repeat count
	{
		for (i = 0; i < PIC_HEIGHT; i++)
		{
			p = picture;
			for (k = 0; k < COL / PIC_WIDTH; k++) // k-col repeat count
			{
				for (j = 0; j < PIC_WIDTH; j++)
				{
					DBL = (*(p + i * PIC_HEIGHT + j)) >> 8;
					TFT_WR(0);
					TFT_WR(1);

					DBL = *(p + i * PIC_HEIGHT + j);
					TFT_WR(0);
					TFT_WR(1);
				}
			}

			p = picture;
			for (j = 0; j < COL % PIC_WIDTH; j++)
			{
				DBL = (*(p + i * PIC_HEIGHT + j)) >> 8;
				TFT_WR(0);
				TFT_WR(1);

				DBL = *(p + i * PIC_HEIGHT + j);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	for (i = 0; i < ROW % PIC_HEIGHT; i++)
	{
		p = picture;
		for (k = 0; k < COL / PIC_WIDTH; k++) // k-col repeat count
		{
			for (j = 0; j < PIC_WIDTH; j++)
			{
				DBL = (*(p + i * PIC_HEIGHT + j)) >> 8;
				TFT_WR(0);
				TFT_WR(1);

				DBL = *(p + i * PIC_HEIGHT + j);
				TFT_WR(0);
				TFT_WR(1);
			}
		}

		p = picture;
		for (j = 0; j < COL % PIC_WIDTH; j++)
		{
			DBL = (*(p + i * PIC_HEIGHT + j)) >> 8;
			TFT_WR(0);
			TFT_WR(1);

			DBL = *(p + i * PIC_HEIGHT + j);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	TFT_CS(1);
}

#endif

#ifdef SD_PIC_DEMO_MODE
void DispPicFromSD(unsigned char PicNum)
{
	unsigned long page_s, page_e;
	unsigned int i;
	unsigned long page_num;

	SD_Start();

	CLKSEL = 0x03;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	// TFT_RD(1);
	TFT_RS(1);

	page_num = (unsigned long)ROW * (unsigned long)COL * 2 / 512;
	page_s = PicNum * page_num + 1;
	page_e = (PicNum + 1) * page_num + 1;
	for (; page_s < page_e; page_s++)
	{
		MMC_SD_ReadSingleBlock(page_s);

		for (i = 0; i < 512; i += 2)
		{
			WriteDispData(buffer[i], buffer[i + 1]);
		}
	}

	TFT_CS(1);
	CLKSEL = 0x00;
}
#endif

#ifdef SD_PIC_TEST_MODE
unsigned int GetPageNum(unsigned int row, unsigned int col)
{
	unsigned long page_num;

	page_num = (unsigned long)row * (unsigned long)col * 2 / 512;

	return page_num;
}

void DispPicFromSD(unsigned char PicNum)
{
	unsigned long page_s, page_e;
	unsigned long page_offset = 0;
	unsigned long page_num;
	unsigned int i;

	// 128128-64p
	// 128160-80p
	// 176220-151.25p
	// 240320-300p
	// 240400-375p
	// 272480-510p

#ifdef QQVGA1
	page_offset = 0;
#endif
#ifdef QQVGA2
	page_offset = GetPageNum(128, 128);
#endif
#ifdef QCIF
	page_offset = GetPageNum(128, 128) + GetPageNum(128, 160);
#endif
#ifdef QVGA
	page_offset = GetPageNum(128, 128) + GetPageNum(128, 160) + GetPageNum(220 * 4, 176);
#endif
#ifdef WQVGA
	page_offset = GetPageNum(128, 128) + GetPageNum(128, 160) + GetPageNum(220 * 4, 176) + GetPageNum(320, 240);
#endif
#ifdef HVGA1
	page_offset = GetPageNum(128, 128) + GetPageNum(128, 160) + GetPageNum(220 * 4, 176) + GetPageNum(320, 240) + GetPageNum(400, 240);
#endif
#ifdef HVGA2
	page_offset = GetPageNum(128, 128) + GetPageNum(128, 160) + GetPageNum(220 * 4, 176) + GetPageNum(320, 240) + GetPageNum(400, 240) + GetPageNum(272, 480);
#endif
#ifdef WVGA
	page_offset = GetPageNum(128, 128) + GetPageNum(128, 160) + GetPageNum(220 * 4, 176) + GetPageNum(320, 240) + GetPageNum(400, 240) + GetPageNum(272, 480) + GetPageNum(480, 320);
#endif

	SD_Start();

	CLKSEL = 0x03;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	// TFT_RD(1);
	TFT_RS(1);

	page_num = (unsigned long)ROW * (unsigned long)COL * 2 / 512;
	page_s = PicNum * page_num + 1;
	page_e = (PicNum + 1) * page_num + 1;

	for (; page_s < page_e; page_s++)
	{
		MMC_SD_ReadSingleBlock(page_s + page_offset);

		for (i = 0; i < 512; i += 2)
		{
			WriteDispData(buffer[i], buffer[i + 1]);
		}
	}

	TFT_CS(1);
	CLKSEL = 0x00;
}

#endif
/*
void DispGrayHor16(void)
{
	unsigned int i,j,k;

	BlockWrite(0,COL-1,0,ROW-1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL%16;j++)
		{
			DBH=0;
			DBL=0;
			TFT_WR(0);
			TFT_WR(1);
		}

		for(j=0;j<16;j++)
		{
			for(k=0;k<COL/16;k++)
			{
				DBH=((j*2)<<3)|((j*4)>>3);
				DBL=((j*4)<<5)|(j*2);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}
*/

#ifdef EXTEND_TEST
void DispScaleHor1(void)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// balck -> red
	for (k = 0; k < ROW / 4; k++)
	{
		for (i = 0; i < COL % 32; i++)
		{
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
		}
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < COL / 32; j++)
			{
				DBL = i << 3;
				TFT_WR(0);
				TFT_WR(1);

				DBL = 0;
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	// balck -> green
	for (k = 0; k < ROW / 4; k++)
	{
		for (i = 0; i < COL % 32; i++)
		{
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
		}
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < COL / 32; j++)
			{
				DBL = (i * 2) >> 3;
				TFT_WR(0);
				TFT_WR(1);

				DBL = (i * 2) << 5;
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	// balck -> blue
	for (k = 0; k < ROW / 4; k++)
	{
		for (i = 0; i < COL % 32; i++)
		{
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
		}
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < COL / 32; j++)
			{
				DBL = 0;
				TFT_WR(0);
				TFT_WR(1);

				DBL = i;
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	// black -> white
	for (k = 0; k < (ROW / 4 + ROW % 4); k++)
	{
		for (i = 0; i < COL % 32; i++)
		{
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
			DBL = 0x00;
			TFT_WR(0);
			TFT_WR(1);
		}
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < COL / 32; j++)
			{
				DBL = (i << 3) | ((i * 2) >> 3);
				TFT_WR(0);
				TFT_WR(1);

				DBL = ((i * 2) << 5) | i;
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispScaleVer(void)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// BLACK
	for (k = 0; k < ROW % 32; k++)
	{
		for (j = 0; j < COL; j++)
		{
			DBL = 0;
			TFT_WR(0);
			TFT_WR(1);

			DBL = 0;
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	for (k = 0; k < 32; k++)
	{

		for (i = 0; i < ROW / 32; i++)
		{
			// RED
			for (j = 0; j < COL / 4; j++)
			{
				DBL = k << 3;
				TFT_WR(0);
				TFT_WR(1);

				DBL = 0;
				TFT_WR(0);
				TFT_WR(1);
			}
			// GREEN
			for (j = 0; j < COL / 4; j++)
			{
				DBL = (k * 2) >> 3;
				TFT_WR(0);
				TFT_WR(1);

				DBL = (k * 2) << 5;
				TFT_WR(0);
				TFT_WR(1);
			}
			// BLUE
			for (j = 0; j < COL / 4; j++)
			{
				DBL = 0;
				TFT_WR(0);
				TFT_WR(1);

				DBL = k;
				TFT_WR(0);
				TFT_WR(1);
			}
			// GRAY
			for (j = 0; j < COL / 4; j++)
			{
				DBL = (k << 3) | ((k * 2) >> 3);
				TFT_WR(0);
				TFT_WR(1);

				DBL = ((k * 2) << 5) | k;
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispScaleVer_Red(void)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// BLACK
	for (k = 0; k < ROW % 32; k++)
	{
		for (j = 0; j < COL; j++)
		{
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);

			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	for (k = 0; k < 32; k++)
	{
		for (i = 0; i < ROW / 32; i++)
		{
			// RED
			for (j = 0; j < COL; j++)
			{
//				DBL = k << 3;
				Write_TFT_Data_u8_L(k << 3);
				TFT_WR(0);
				TFT_WR(1);

				Write_TFT_Data_u8_L(0);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispScaleVer_Green(void)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// BLACK
	for (k = 0; k < ROW % 64; k++)
	{
		for (j = 0; j < COL; j++)
		{
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);

			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	for (k = 0; k < 64; k++)
	{
		for (i = 0; i < ROW / 64; i++)
		{
			// GREEN
			for (j = 0; j < COL; j++)
			{
//				DBL = k >> 3;
				Write_TFT_Data_u8_L(k >> 3);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = k << 5;
				Write_TFT_Data_u8_L(k << 5);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispScaleVer_Blue(void)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// BLACK
	for (k = 0; k < ROW % 32; k++)
	{
		for (j = 0; j < COL; j++)
		{
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);

			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	for (k = 0; k < 32; k++)
	{
		for (i = 0; i < ROW / 32; i++)
		{
			// BLUE
			for (j = 0; j < COL; j++)
			{
				Write_TFT_Data_u8_L(0);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = k;
				Write_TFT_Data_u8_L(k);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispScaleVer_Gray(void)
{
	unsigned int i, j, k;
	uint8_t data_L =0;
	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// BLACK
	for (k = 0; k < ROW % 32; k++)
	{
		for (j = 0; j < COL; j++)
		{
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);

			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	for (k = 0; k < 32; k++)
	{
		for (i = 0; i < ROW / 32; i++)
		{
			// GRAY
			for (j = 0; j < COL; j++)
			{
//				DBL = (k << 3) | ((k * 2) >> 3);
				data_L= (k << 3) | ((k * 2) >> 3);
				Write_TFT_Data_u8_L(data_L);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = ((k * 2) << 5) | k;
				data_L= ((k * 2) << 5) | k;
				Write_TFT_Data_u8_L(data_L);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispGrayHor16(void)
{
	unsigned int i, j, k;
	uint8_t data_H;
	uint8_t data_L;
	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL % 16; j++)
		{
//			DBH = 0;
//			DBL = 0;
			Write_TFT_Data(0);
			TFT_WR(0);
			TFT_WR(1);
		}

		for (j = 0; j < 16; j++)
		{
			for (k = 0; k < COL / 16; k++)
			{
//				DBH = ((j * 2) << 3) | ((j * 4) >> 3);
				data_H = ((j * 2) << 3) | ((j * 4) >> 3);
				Write_TFT_Data_u8_H(data_H);
//				DBL = ((j * 4) << 5) | (j * 2);
				data_L= ((j * 4) << 5) | (j * 2);
				Write_TFT_Data_u8_L(data_L);				
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispGrayHor32(void)
{
	unsigned int i, j, k;
	uint8_t data_L;
	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL % 32; j++)
		{
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);

			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}

		for (j = 0; j < 32; j++)
		{
			for (k = 0; k < COL / 32; k++)
			{
//				DBL = (j << 3) | ((j * 2) >> 3);
				data_L= (j << 3) | ((j * 2) >> 3);
				Write_TFT_Data_u8_L(data_L);		
				
				TFT_WR(0);
				TFT_WR(1);

//				DBL = ((j * 2) << 5) | j;
				data_L = ((j * 2) << 5) | j;
				Write_TFT_Data_u8_L(data_L);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	TFT_CS(1);
}

void DispScaleHor2(void)
{
	unsigned int i, j, k;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);

	// balck -> red
	for (k = 0; k < ROW / 6; k++)
	{
		for (i = 0; i < COL % 32; i++)
		{
			// DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
			// DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < COL / 32; j++)
			{
//				DBL = i << 3;
				Write_TFT_Data_u8_L(i << 3);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = 0;
				Write_TFT_Data_u8_L(0);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	// red -> black
	for (k = 0; k < ROW / 6; k++)
	{
		for (i = 32; i > 0; i--)
		{
			for (j = 0; j < COL / 32; j++)
			{
//				DBL = (i - 1) << 3;
				Write_TFT_Data_u8_L((i - 1) << 3);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = 0;
				Write_TFT_Data_u8_L(0);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
		for (i = 0; i < COL % 32; i++)
		{
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
	}
	// balck -> green
	for (k = 0; k < ROW / 6; k++)
	{
		for (i = 0; i < COL % 64; i++)
		{
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
		for (i = 0; i < 64; i++)
		{
			for (j = 0; j < COL / 64; j++)
			{
//				DBL = i >> 3;
				Write_TFT_Data_u8_L(i >> 3);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = i << 5;
				Write_TFT_Data_u8_L(i << 5);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	// green -> black
	for (k = 0; k < ROW / 6; k++)
	{
		for (i = 64; i > 0; i--)
		{
			for (j = 0; j < COL / 64; j++)
			{
//				DBL = (i - 1) >> 3;
				Write_TFT_Data_u8_L((i - 1) >> 3);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = (i - 1) << 5;
				Write_TFT_Data_u8_L((i - 1) << 5);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
		for (i = 0; i < COL % 64; i++)
		{
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	// balck -> blue
	for (k = 0; k < ROW / 6; k++)
	{
		for (i = 0; i < COL % 32; i++)
		{
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < COL / 32; j++)
			{
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
				TFT_WR(0);
				TFT_WR(1);

//			DBL = i;
			Write_TFT_Data_u8_L(i);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
	}

	// blue -> black
	for (k = 0; k < (ROW / 6 + ROW % 6); k++)
	{
		for (i = 32; i > 0; i--)
		{
			for (j = 0; j < COL / 32; j++)
			{
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
				TFT_WR(0);
				TFT_WR(1);

//				DBL = (i - 1);
				Write_TFT_Data_u8_L(i - 1);
				TFT_WR(0);
				TFT_WR(1);
			}
		}
		for (i = 0; i < COL % 32; i++)
		{
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	TFT_CS(1);
}

void DispSnow(void)
{
	unsigned int i, j;
	uint8_t data_L = 0;
	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RS(1);
	TFT_RD(1);

//			DBL = 0x00;
			Write_TFT_Data_u8_L(0);


	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL / 2; j++)
		{
			TFT_WR(0);
			TFT_WR(1);
			TFT_WR(0);
			TFT_WR(1);

//			DBL = ~DBL;
			data_L = ~data_L;
			Write_TFT_Data_u8_L(data_L);
			
			TFT_WR(0);
			TFT_WR(1);
			TFT_WR(0);
			TFT_WR(1);

//			DBL = ~DBL;
			data_L = ~data_L;
			Write_TFT_Data_u8_L(data_L);
		}

//			DBL = ~DBL;
			data_L = ~data_L;
			Write_TFT_Data_u8_L(data_L);
		// DBL = ~DBL;
	}

//	CS0 = 1;
	TFT_CS(1);
}

void DispBlock(void)
{
	unsigned int i, j, k;
	k = ROW / 4;

	BlockWrite(0, COL - 1, 0, ROW - 1);

	TFT_CS(0);
	TFT_RS(1);
	TFT_RD(1);

	for (i = 0; i < k; i++)
	{
		for (j = 0; j < COL; j++)
		{
//			DBL = GRAY50 >> 8;
			Write_TFT_Data_u8_L(GRAY50 >> 8);
			TFT_WR(0);
			TFT_WR(1);

//			DBL = GRAY50;
			Write_TFT_Data_u8_L(GRAY50);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	for (i = 0; i < k * 2; i++)
	{

		for (j = 0; j < COL / 4; j++)
		{
//			DBL = GRAY50 >> 8;
			Write_TFT_Data_u8_L(GRAY50 >> 8);
			TFT_WR(0);
			TFT_WR(1);

//			DBL = GRAY50;
			Write_TFT_Data_u8_L(GRAY50);
			TFT_WR(0);
			TFT_WR(1);
		}

		for (j = 0; j < COL / 2; j++)
		{
//			DBL = BLACK >> 8;
			Write_TFT_Data_u8_L(BLACK >> 8);
			TFT_WR(0);
			TFT_WR(1);

//			DBL = BLACK;
			Write_TFT_Data_u8_L(BLACK);
			TFT_WR(0);
			TFT_WR(1);
		}

		for (j = 0; j < COL / 4; j++)
		{
//			DBL = GRAY50 >> 8;
			Write_TFT_Data_u8_L(GRAY50 >> 8);
			TFT_WR(0);
			TFT_WR(1);

//			DBL = GRAY50;
			Write_TFT_Data_u8_L(GRAY50);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	for (i = 0; i < k; i++)
	{
		for (j = 0; j < COL; j++)
		{
//			DBL = GRAY50 >> 8;
			Write_TFT_Data_u8_L(GRAY50 >> 8);
			TFT_WR(0);
			TFT_WR(1);

//			DBL = GRAY50;
			Write_TFT_Data_u8_L(GRAY50);
			TFT_WR(0);
			TFT_WR(1);
		}
	}

	TFT_CS(1);
}

#endif

#ifdef STRING_FUNCTION

// ascii 32~90(!~Z), (32~47)空格~/,(48~57)0~9,(58~64):~@,(65~126)A~~
// ord 0~95, (48~57)0~9,(65~126)A~z,(33~47)!~/,(58~64):~@
unsigned char ToOrd(unsigned char ch)
{
	if (ch < 32)
	{
		ch = 95;
	}
	else if ((ch >= 32) && (ch <= 47)) //(32~47)空格~/
	{
		ch = (ch - 32) + 10 + 62;
	}
	else if ((ch >= 48) && (ch <= 57)) //(48~57)0~9
	{
		ch = ch - 48;
	}
	else if ((ch >= 58) && (ch <= 64)) //(58~64):~@
	{
		ch = (ch - 58) + 10 + 62 + 16;
	}
	else if ((ch >= 65) && (ch <= 126)) //(65~126)A~~
	{
		ch = (ch - 65) + 10;
	}
	else if (ch > 126)
	{
		ch = 95;
	}

	return ch;
}

void DispOneChar(unsigned char ord, unsigned int Xstart, unsigned int Ystart, unsigned int TextColor, unsigned int BackColor) // ord:0~95
{
	unsigned char i, j;
	unsigned char *p;
	unsigned char dat;
	unsigned int index;

	BlockWrite(Xstart, Xstart + (FONT_W - 1), Ystart, Ystart + (FONT_H - 1));

	index = ord;

	if (index > 95) // 95:ASCII CHAR NUM
		index = 95;

	index = index * ((FONT_W / 8) * FONT_H);

	p = ascii;
	p = p + index;

	for (i = 0; i < (FONT_W / 8 * FONT_H); i++)
	{
		dat = *p++;
		for (j = 0; j < 8; j++)
		{
			if ((dat << j) & 0x80)
			{
				WriteOneDot(TextColor);
			}
			else
			{
				WriteOneDot(BackColor);
			}
		}
	}
}

void DispStr(unsigned char *str, unsigned int Xstart, unsigned int Ystart, unsigned int TextColor, unsigned int BackColor)
{

	while (!(*str == '\0'))
	{
		DispOneChar(ToOrd(*str++), Xstart, Ystart, TextColor, BackColor);

		if (Xstart > ((COL - 1) - FONT_W))
		{
			Xstart = 0;
			Ystart = Ystart + FONT_H;
		}
		else
		{
			Xstart = Xstart + FONT_W;
		}

		if (Ystart > ((ROW - 1) - FONT_H))
		{
			Ystart = 0;
		}
	}
	BlockWrite(0, COL - 1, 0, ROW - 1);
}

void DispInt(unsigned int i, unsigned int Xstart, unsigned int Ystart, unsigned int TextColor, unsigned int BackColor)
{
	if (Xstart > ((COL - 1) - FONT_W * 4))
	{
		Xstart = (COL - 1) - FONT_W * 4;
	}
	if (Ystart > ((ROW - 1) - FONT_H))
	{
		Ystart = (Ystart - 1) - FONT_H;
	}

	DispOneChar((i >> 12) % 16, Xstart, Ystart, TextColor, BackColor); // ID value
	DispOneChar((i >> 8) % 16, Xstart + FONT_W, Ystart, TextColor, BackColor);
	DispOneChar((i >> 4) % 16, Xstart + FONT_W * 2, Ystart, TextColor, BackColor);
	DispOneChar(i % 16, Xstart + FONT_W * 3, Ystart, TextColor, BackColor);

	BlockWrite(0, COL - 1, 0, ROW - 1);
}

#endif

#ifdef READ_FUNCTION
uint16_t ReadData(void)
{
	// unsigned char dataH;
	unsigned char dataL;
	uint16_t data;
	////////////////
//	P2MDIN |= 0xFF;
//	P2MDOUT |= 0x00;

//	P4MDIN |= 0xFF;
//	P4MDOUT |= 0x00;

//	DBL = 0xFF;
//	DBL = 0xFF;

//	CS0 = 0;
//	RS = 1;
//	WR0 = 1;
	TFT_CS(0);
	TFT_RS(1);
	TFT_WR(1);
	
//	RD0 = 0;
	TFT_RD(0);
	HAL_Delay(10);
	data = Read_TFT_Data();
//	dataL = DBL;
//	RD0 = 1;
	TFT_RD(0);
	TFT_CS(1);

	////////////////
//	P2MDIN |= 0xFF;
//	P2MDOUT |= 0xFF;

//	P4MDIN |= 0xFF;
//	P4MDOUT |= 0xFF;

	// return (dataH<<8)|dataL;
	return data;
}
#endif

#ifdef READ_REG
//void DispRegValue(unsigned int RegIndex, unsigned char ParNum)
//{
//	unsigned char i;
//	unsigned int reg_data[20];

//	WriteComm(RegIndex);

//	if (ParNum > 20)
//		ParNum = 20;

//	for (i = 0; i < ParNum; i++)
//	{
//		reg_data[i] = ReadData();
//	}

//	// READ REG
//	DispStr("READ ID ", 0, 0, BLACK, WHITE);
//	// DispStr("READ REG:0X",0,0,BLACK,WHITE);

//	DispInt(RegIndex, 0, (FONT_H + 1), GREEN, BLACK);
//	for (i = 0; i < ParNum; i++)
//	{
//		// DispStr("0X",0,(FONT_H+1)*(i+1),BLUE,WHITE);
//		// DispInt(reg_data[i],FONT_W*2,(FONT_H+1)*(i+1),BLUE,WHITE);

//		DispInt(reg_data[i], 0, (FONT_H + 1) * (i + 2), BLUE, WHITE);
//	}
//}

#endif

#ifdef SLEEP_TEST
void EnterSLP(void)
{
	// FOR ILI9163C

	WriteComm(0x0010);
}

void ExitSLP(void)
{
	// FOR ILI9163C

	WriteComm(0x0011);
}

#endif
#ifdef DEBUG
void Pause(void)
{
	while (KEY_STEP)
		;
	HAL_Delay(500);
	while (!KEY_STEP)
		;
}

void DispDebugCode(void)
{
	unsigned int i, j;

	i = 0;
	j = 0;
	while (i < DEBUG_X)
	{
		j = 0;
		while ((j < DEBUG_Y) && (debug_code[i][j] != END))
		{
			if (j == 0)
			{
				WriteComm(debug_code[i][j]);
			}
			else
			{
				WriteData(debug_code[i][j]);
			}
			j++;
		}

		j = 0;
		while ((j < DEBUG_Y) && (debug_code[i][j] != END))
		{
			if (j == 0)
			{
				// WriteComm(debug_code[i][j]);
				DispStr("0X", 0, (FONT_H + 1) * (j + 1), RED, WHITE);
				DispInt(debug_code[i][j], FONT_W * 2, (FONT_H + 1) * (j + 1), RED, WHITE);
			}
			else
			{
				// WriteData(debug_code[i][j]);
				DispStr("0X", 0, (FONT_H + 1) * (j + 1), BLUE, WHITE);
				DispInt(debug_code[i][j], FONT_W * 2, (FONT_H + 1) * (j + 1), BLUE, WHITE);
			}
			j++;
		}
		i++;

		Pause();
		HAL_Delay(800);

		if ((j == 0) && (debug_code[i][j] != END))
			break;
	}
}

void Debug(void)
{
	DispStr("DEBUG CODE", 0, 0, BLACK, WHITE);

	while (1)
	{
		DispDebugCode();
	}
}

#endif

#ifdef DRAW_FUNCTION
void PutPixel(unsigned int x, unsigned int y, unsigned int color)
{
#if 0
	BlockWrite(x,x+1,y,y+1);

	TFT_CS(0);
	TFT_RD(1);
	TFT_RS(1);
	
	DBL=color>>8;
	TFT_WR(0);  
	TFT_WR(1); 

	DBL=color;  
	TFT_WR(0);  
	TFT_WR(1); 

	DBL=color>>8;
	TFT_WR(0);  
	TFT_WR(1); 

	DBL=color;  
	TFT_WR(0);  
	TFT_WR(1); 

	DBL=color>>8;
	TFT_WR(0);  
	TFT_WR(1); 

	DBL=color;  
	TFT_WR(0);  
	TFT_WR(1); 

	DBL=color>>8;
	TFT_WR(0);  
	TFT_WR(1); 

	DBL=color;  
	TFT_WR(0);  
	TFT_WR(1); 
  
	TFT_CS(1);
#endif

#if 1
	unsigned char i;

	for (i = 0; i < 3; i++)
	{
		BlockWrite(x, COL - 1, y + i, ROW - 1);
		WriteOneDot(color);
		WriteOneDot(color);
	}

#endif
}

void DrawLine(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend, unsigned int color)
{
	unsigned int i, j;

	BlockWrite(Xstart, Xend, Ystart, Yend);

	for (i = Ystart; i < Yend + 1; i++)
	{
		for (j = Xstart; j < Xend + 1; j++)
		{
			WriteOneDot(color);
		}
	}
}

void DrawGird(unsigned int color)
{
	unsigned int i;

	for (i = 15; i < ROW - 1; i = i + 16)
	{
		DrawLine(0, COL - 1, i, i, color);
	}

	for (i = 15; i < COL - 1; i = i + 16)
	{
		DrawLine(i, i, 0, ROW - 1, color);
	}
}
#endif

// ARRAY DIFINE
//-------------------------------------------------------------------------
#ifdef DEBUG
unsigned int code debug_code[50][15] =
	{
		// ILI9481
		{0xd1, 0x00, 0x1d, 0x0c, END},
		{0xd1, 0x00, 0x1d, 0x08, END},
		{0xd1, 0x00, 0x1d, 0x07, END},
		{0xd1, 0x00, 0x1d, 0x0b, END},

		{END}, // end

};
#endif
