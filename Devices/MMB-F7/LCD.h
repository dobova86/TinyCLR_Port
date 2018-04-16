/////////////////////////////////////////////
//
//  Copyright (c) LEDONET by Dom.
//
/////////////////////////////////////////////
//#include <..\..\..\GHI\Include\GHI_OSHW_HAL.h
#include <string.h>
#include <TinyCLR.h>


static void TimeDelay(uint64_t delay);
void LCD_WriteData(uint16_t value);
uint16_t LCD_ReadData();
void LCD_WriteCommand(uint16_t reg);
void LCD_Clear(uint16_t color);
void LCD_Init();
void LCD_PinConfig(void);
void LCD_SetPixelAddress(uint16_t x, uint16_t y, uint16_t color);
void LCD_SetDrawingWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void LCD_Delay(uint32_t nCount);
void LCD_DelayUs(uint32_t nCount);
void LCD_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t color);
void LCD_Rectangle(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t color, bool fill);
void LCD_DrawImage(char* bmp_buffer, uint16_t buff_len, uint16_t x, uint16_t y, uint16_t o_width, uint16_t o_height, uint16_t x_src, uint16_t y_src, uint16_t width, uint16_t height);
int power (int base, int n);
void LCD_PutChar(uint16_t x, uint16_t y, uint8_t Character, uint16_t ForeColor, uint16_t BackColor);
void LCD_Text(uint16_t x, uint16_t y, const char* str, uint16_t len, uint16_t ForeColor, uint16_t BackColor);
void LCD_Circle(uint16_t cx, uint16_t cy, uint16_t r,uint16_t color, bool fill);
void LCD_SetScrollArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t scrollx, uint16_t scrolly, bool up_down);
//INT8 LCD_SetSpecialConfig(INT32 key, INT32 value);
