/////////////////////////////////////////////
//
//  Copyright (c) LEDONET by Dom
//
/////////////////////////////////////////////
#include <TinyCLR.h>
#include <STM32F7.h>

#include "STM32F7_GPIO.h" 

#include "LCD.h"
#include "SSD1963_CMD.h"
//#include "../../Targets/STM32F7xx/inc/stm32f7xx.h"

extern unsigned char font_8x8[];
extern const unsigned char* Font_GetGlyph(unsigned char c);
extern int Font_Width();
extern int Font_Height();

uint16_t LCD_MaxWidth;
uint16_t LCD_MaxHeight;

extern "C" void IDelayLoop(int32_t iterations);

static void TimeDelay(uint64_t nanoseconds)
{
	int32_t iterations = (int32_t)(nanoseconds * STM32F7_AHB_CLOCK_HZ / 1000000000);
	IDelayLoop(iterations - 5);
}

/*
	Define PIN configuration for MMB LCD for STN32F4->SSD1963 controller 
	Data: E8..15, G0..7 (16bit interface IO)
	CTRL: F11..15
*/
void LCD_PinConfig(void)
{
	//GPIO_TypeDef GPIO_InitStructure;

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOB, ENABLE);  
	//STM32F4_GpioInternal_ConfigurePin(PIN(E, 7), STM32F4_Gpio_PortMode::GeneralPurposeOutput, STM32F4_Gpio_OutputType::PushPull, STM32F4_Gpio_OutputSpeed::High, STM32F4_Gpio_PullDirection::None, STM32F4_Gpio_AlternateFunction::AF0);


	GPIOE->MODER = ( GPIOE->MODER & 0xFFFF ) | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
	GPIOE->OSPEEDR = ( GPIOE->OSPEEDR & 0xFFFF) | GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1 | GPIO_OSPEEDER_OSPEEDR10_1 | GPIO_OSPEEDER_OSPEEDR11_1 | GPIO_OSPEEDER_OSPEEDR12_1 | GPIO_OSPEEDER_OSPEEDR13_1 | GPIO_OSPEEDER_OSPEEDR14_1 | GPIO_OSPEEDER_OSPEEDR15_1;


	GPIOG->MODER = (GPIOG->MODER & 0xFFFF0000) | GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;
	GPIOG->OSPEEDR = ( GPIOG->OSPEEDR & 0xFFFF0000) | GPIO_OSPEEDER_OSPEEDR0_1 | GPIO_OSPEEDER_OSPEEDR1_1 | GPIO_OSPEEDER_OSPEEDR2_1 | GPIO_OSPEEDER_OSPEEDR3_1 | GPIO_OSPEEDER_OSPEEDR4_1 | GPIO_OSPEEDER_OSPEEDR5_1 | GPIO_OSPEEDER_OSPEEDR6_1 | GPIO_OSPEEDER_OSPEEDR7_1;
	
	GPIOF->MODER = (GPIOF->MODER & 0x03FFFFF) | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
	GPIOF->OSPEEDR = ( GPIOF->OSPEEDR & 0x03FFFFF ) | GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1 | GPIO_OSPEEDER_OSPEEDR10_1 | GPIO_OSPEEDER_OSPEEDR11_1 | GPIO_OSPEEDER_OSPEEDR12_1 | GPIO_OSPEEDER_OSPEEDR13_1 | GPIO_OSPEEDER_OSPEEDR14_1 | GPIO_OSPEEDER_OSPEEDR15_1;


	// LED Green, Red, Blu
	//GPIOB->MODER = (GPIOB->MODER & 0xFFFFFC3F) | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0;
	//GPIOB->OSPEEDR = (GPIOB->OSPEEDR & 0xFFFFFC3F) | GPIO_OSPEEDER_OSPEEDR3_1 | GPIO_OSPEEDER_OSPEEDR4_1;

	//GPIOG->MODER = (GPIOG->MODER & 0x3FFFFFFF) | GPIO_MODER_MODE15_0;
	//GPIOG->OSPEEDR = (GPIOG->OSPEEDR & 0x3FFFFFFF) | GPIO_OSPEEDER_OSPEEDR15_1;


	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4; // Green LED and BLU
	//GPIO_Init(GPIOB, &GPIO_InitStructure);
	//STM32F4_GpioInternal_WritePin(PIN(B, 3), true);
}

void LCD_Init()
{

	//LCD_Delay(100);
	TimeDelay(100000);
	Set_Rst;		
	Set_Cs;        	// SSD1963 is not selected by default
	Set_nRd;
	Set_nWr;

	Clr_Rst;
	//LCD_DelayUs(200);
	TimeDelay(200000);
	Set_Rst;       // release from reset state to sleep state
	
	//LCD_DelayUs(250);
	TimeDelay(250000);
	Clr_Cs;
	
	LCD_WriteCommand(CMD_SOFT_RESET);				// Soft reset
	//LCD_DelayUs(250);
	TimeDelay(500000);

	//Set MN(multipliers) of PLL, VCO = crystal freq * (N+1)
	//PLL freq = VCO/M with 250MHz < VCO < 800MHz
	//The max PLL freq is around 120MHz. To obtain 120MHz as the PLL freq
	LCD_WriteCommand(CMD_SET_PLL_MN);				// Set PLL with OSC = 10MHz (hardware)
													// Multiplier N = 35, VCO (>250MHz)= OSC*(N+1), VCO = 360MHz
	Clr_Cs;
	LCD_WriteData(35);
	LCD_WriteData(2);				    // Divider M = 2, PLL = 360/(M+1) = 120MHz
	LCD_WriteData(0x54);				// Validate M and N values
	Set_Cs;	

	LCD_WriteCommand(CMD_PLL_START);				// Start PLL command
	Clr_Cs;
	LCD_WriteData(0x01);				// enable PLL
	Set_Cs;	

	//LCD_DelayUs(500);						// wait stablize
	TimeDelay(500000);
	LCD_WriteCommand(CMD_PLL_START);				// Start PLL command again
	Clr_Cs;
	LCD_WriteData(0x03);				// now, use PLL output as system clock	
	Set_Cs;	

	//Set LSHIFT freq, i.e. the DCLK with PLL freq 120MHz set previously
	//Typical DCLK for TM070RBH10 is 29.23MHz(datasheet), experiment shows 30MHz gives a stable result
	//29.23MHz = 120MHz*(LCDC_FPR + 1)/2^20
	//LCDC_FPR = 255415  (0x3E5B7)
	//Time per line = (DISP_HOR_RESOLUTION+DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH+DISP_HOR_FRONT_PORCH)/30 us = 1056/30 = 35.2us
	LCD_WriteCommand(CMD_SET_PCLK); // set for 
	Clr_Cs;
	LCD_WriteData(0x01);
	LCD_WriteData(0x45);
	LCD_WriteData(0x47);
	//LCD_WriteData((LCD_FPR >> 16) & 0xFF);
	//LCD_WriteData((LCD_FPR >> 8) & 0xFF);
	//LCD_WriteData(LCD_FPR & 0xFF);	
	Set_Cs;
	
	//Set panel mode, varies from individual manufacturer
	LCD_WriteCommand(CMD_SET_PANEL_MODE);
	Clr_Cs;
	//LCD_WriteData(0x10);				// set 18-bit for 7" panel TY700TFT800480
	LCD_WriteData(0x28);				// set 18-bit for 4,5" 
	LCD_WriteData(0x20);				// set TTL mode (originale : 0x80)
	LCD_WriteData(0x01);
	LCD_WriteData(0xdf);				//RGB sequence	
	LCD_WriteData(0x01);
	LCD_WriteData(0x0f);
	LCD_WriteData(0x00);
	Set_Cs;

	//Set horizontal period
	#define HPS (DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH)
	//#define HT (DISP_HOR_RESOLUTION+DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH+DISP_HOR_FRONT_PORCH)
	LCD_WriteCommand(CMD_SET_HOR_PERIOD);
	Clr_Cs;
	LCD_WriteData(0x02);
	LCD_WriteData(0x0d);
	LCD_WriteData(0x00);
	LCD_WriteData(0x2b);
	LCD_WriteData(0x28);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	Set_Cs;
	
	//Set vertical period
	#define VSP (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH)
	//#define VT (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH+DISP_VER_FRONT_PORCH+DISP_VER_RESOLUTION)
	LCD_WriteCommand(CMD_SET_VER_PERIOD);
	Clr_Cs;
	LCD_WriteData(0x01);
	LCD_WriteData(0x1d);
	LCD_WriteData(0x00);
	LCD_WriteData(0x0c);
	LCD_WriteData(0x09);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	Set_Cs;
	
	//Set pixel format, i.e. the bpp
	LCD_WriteCommand(CMD_SET_PIXEL_FORMAT );
	Clr_Cs;
	LCD_WriteData(0x60); 				// set 18bpp
	Set_Cs;

	//Set pixel data interface
	LCD_WriteCommand(CMD_SET_PIXEL_DATA_INTERFACE);
	Clr_Cs;
	LCD_WriteData(0x03);				//18-bit(666 format) 
	Set_Cs;

	LCD_WriteCommand(CMD_SET_ADDR_MODE);
	Clr_Cs;
	LCD_WriteData(0x00);
	Set_Cs;
	
	LCD_WriteCommand(CMD_SET_PWM_CONF);
	Clr_Cs;
	LCD_WriteData(0x06);
	LCD_WriteData(0xF0);
	LCD_WriteData(0x01);
	LCD_WriteData(0xFF);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	Set_Cs;
	
	LCD_WriteCommand(CMD_ON_DISPLAY);	
	//Set_Cs;
	//Clr_Cs;
	LCD_WriteCommand(CMD_BLANK_DISPLAY);	        
	//Set_Cs;
	//Clr_Cs;
	LCD_WriteCommand(CMD_ON_DISPLAY);	        
	Set_Cs;     
	LCD_MaxWidth = 480;
	LCD_MaxHeight = 272;

	//STM32F4_GpioInternal_WritePin(PIN(B, 4), true);

}

void LCD_Delay(uint32_t nCount)
{
  nCount = nCount * 1000;
  while(nCount--);
}

void LCD_DelayUs(uint32_t nCount)
{
  //while(nCount--);
	TimeDelay(nCount * 1000);
}

void LCD_WriteCommand(uint16_t cmd) 
{
	Set_nRd;
	Clr_Rs;
	Clr_nWr;
	Clr_Cs; 
	GPIOG->ODR =((GPIOG->ODR & 0xff00)|(cmd & 0x00ff)); 
	GPIOE->ODR =((GPIOE->ODR & 0x00ff)|(cmd & 0xff00)); 
	//TimeDelay(10000);
	Set_Cs; 
	Set_nWr;
	Set_Rs;
};

void LCD_WriteData(uint16_t data)
{
	Set_nRd;
	Set_Rs;
	Clr_nWr;
	Clr_Cs; 
	GPIOG->ODR =((GPIOG->ODR & 0xff00)|(data & 0x00ff)); 
	GPIOE->ODR =((GPIOE->ODR & 0x00ff)|(data & 0xff00)); 
	//TimeDelay(10000);
	Set_Cs; 
	Set_nWr;
};

uint16_t LCD_ReadData()
{
	uint16_t data;

	Clr_nRd;
	Set_Rs;
	Set_nWr;
	Clr_Cs; 
	data = GPIOG->ODR; 	
	Set_Cs; 
	Clr_nWr;
	Set_nRd;

	return(data);
}

void LCD_SetPixelAddress(uint16_t x, uint16_t y, uint16_t color)
{ 	
	LCD_SetDrawingWindow( x, y, LCD_MaxWidth, LCD_MaxHeight);
	LCD_WriteCommand(CMD_WR_MEMSTART);
	Clr_Cs;         
	LCD_WriteData(color);
	Set_Cs;
}

void LCD_SetDrawingWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	LCD_WriteCommand(CMD_SET_COLUMN);
	//Clr_Cs;
	LCD_WriteData((x>>8) & 0xff);
	LCD_WriteData(x & 0xff);
	LCD_WriteData(((x + width - 1)>>8) & 0xff);
	LCD_WriteData((x + width - 1) & 0xff);
	//Set_Cs;
	LCD_WriteCommand(CMD_SET_PAGE);
	//Clr_Cs;
	LCD_WriteData((y>>8) & 0xff);
	LCD_WriteData(y & 0xff);
	LCD_WriteData(((y + height - 1)>>8) & 0xff);
	LCD_WriteData((y + height - 1) & 0xff);
	//Set_Cs;
	//STM32F4_GpioInternal_WritePin(PIN(B, 3), true);

}

void LCD_Clear(uint16_t color)
{
//	u32     counter;
	uint32_t xcounter, ycounter;

	LCD_SetDrawingWindow(0, 0, LCD_MaxWidth, LCD_MaxHeight);

	LCD_WriteCommand(CMD_WR_MEMSTART);

	//Clr_Cs;
	for(ycounter=0; ycounter < LCD_MaxHeight + 1; ycounter++)
	{
		for(xcounter=0;xcounter < LCD_MaxWidth + 1;xcounter++)
		{
			LCD_WriteData(color);
		}
	}        
	//Set_Cs;
}

void LCD_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	uint16_t x,y;
	uint16_t dx;// = abs(x1 - x0);
	uint16_t dy;// = abs(y1 - y0);

	if(y0==y1)
	{
		if(x0<=x1)
		{
			x=x0;
		}
		else
		{
			x=x1;
			x1=x0;
		}
		while(x <= x1)
		{
			LCD_SetPixelAddress(x, y0, color);
			x++;
		}
		return;
	}
	else if(y0>y1)
	{
		dy=y0-y1;
	}
	else
	{
		dy=y1-y0;
	}
 
	if(x0==x1)
	{
		if(y0<=y1)
		{
			y=y0;
		}
		else
		{
			y=y1;
			y1=y0;
		}
		while(y <= y1)
		{
			LCD_SetPixelAddress(x0,y,color);
			y++;
		}
		return;
	}
	else if(x0 > x1)
	{
		dx=x0-x1;
		x = x1;
		x1 = x0;
		y = y1;
		y1 = y0;
	}
	else
	{
		dx=x1-x0;
		x = x0;
		y = y0;
	}

	if(dx == dy)
	{
		while(x <= x1)
		{

			x++;
			if(y>y1)
			{
				y--;
			}
			else
			{
				y++;
			}
			LCD_SetPixelAddress(x,y,color);
		}
	}
	else
	{
		LCD_SetPixelAddress(x, y, color);
		if(y < y1)
		{
			if(dx > dy)
			{
				int16_t p = dy * 2 - dx;
				int16_t twoDy = 2 * dy;
				int16_t twoDyMinusDx = 2 * (dy - dx);
				while(x < x1)
				{
					x++;
					if(p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoDyMinusDx;
					}
					LCD_SetPixelAddress(x, y,color);
				}
			}
			else
			{
				int16_t p = dx * 2 - dy;
				int16_t twoDx = 2 * dx;
				int16_t twoDxMinusDy = 2 * (dx - dy);
				while(y < y1)
				{
					y++;
					if(p < 0)
					{
						p += twoDx;
					}
					else
					{
						x++;
						p+= twoDxMinusDy;
					}
					LCD_SetPixelAddress(x, y, color);
				}
			}
		}
		else
		{
			if(dx > dy)
			{
				int16_t p = dy * 2 - dx;
				int16_t twoDy = 2 * dy;
				int16_t twoDyMinusDx = 2 * (dy - dx);
				while(x < x1)
				{
					x++;
					if(p < 0)
					{
						p += twoDy;
					}
					else
					{
						y--;
						p += twoDyMinusDx;
					}
					LCD_SetPixelAddress(x, y,color);
				}
			}
			else
			{
				int16_t p = dx * 2 - dy;
				int16_t twoDx = 2 * dx;
				int16_t twoDxMinusDy = 2 * (dx - dy);
				while(y1 < y)
				{
					y--;
					if(p < 0)
					{
						p += twoDx;
					}
					else
					{
						x++;
						p+= twoDxMinusDy;
					}
					LCD_SetPixelAddress(x, y,color);
				}
			}
		}
	}
}

void LCD_Rectangle(uint16_t left, uint16_t top, uint16_t width, uint16_t height, uint16_t color, bool fill)
{
	register uint16_t  x,y;
	uint16_t  right, bottom;

	//debug:
	//STM32F4_GpioInternal_WritePin(PIN(B, 3), false);

	if ( width < 1 ) width = 1;
	if ( height < 1 ) height = 1;
	right = left + width - 1;
	bottom = top + height - 1;
	if (!fill) 
	{
		LCD_Line(left, top, left, bottom, color);
		LCD_Line(left, bottom, right , bottom , color);
		LCD_Line(right, bottom, right, top, color);
		LCD_Line(right, top, left, top, color);
	} 
	else
	{ // Filled Rectangle

		LCD_SetDrawingWindow(left, top, width, height);
		LCD_WriteCommand(CMD_WR_MEMSTART);
		Clr_Cs;
		for(y = top; y <= bottom; y++)
		{
			for(x = left; x <= right; x++)
			{
				LCD_WriteData(color);
			}
		}
		Set_Cs;
	}
}

int power (int base, int n) 
{
	int     i,p;
	p = 1;
	for (i = 1; i <= n; ++i)
	p *= base;
	return p;
}


void LCD_PutChar(uint16_t x, uint16_t y, uint8_t Character, uint16_t ForeColor, uint16_t BackColor)
{
		int row = 0;
		int column = 0;
		//int offset = 0; //(Character - 32) * font_8x8[0];
		int font_w, font_h;
		char pixel = 0;

		font_w = Font_Width();
		font_h = Font_Height();
		const uint8_t * ch = Font_GetGlyph(Character);
		LCD_Rectangle( x, y, font_w, font_h, BackColor, true );
		LCD_SetDrawingWindow(x, y, font_w, font_h);
		LCD_WriteCommand(CMD_WR_MEMSTART);
		Clr_Cs;        
		for(row = 0; row < font_h; row++)
		{
			for(column = 0; column < font_w; column++)
			{
				pixel = (ch[row] << column) & 0x80;
				if ( pixel == 0x80 )
					LCD_WriteData(ForeColor);					
				else
					LCD_WriteData(BackColor);
			}
		}
		Set_Cs;
}   


void LCD_Text(uint16_t x, uint16_t y, const char* str, uint16_t len, uint16_t ForeColor, uint16_t BackColor)
{
  uint8_t i;
  
  if ( (len*Font_Width() + x) > LCD_MaxWidth ) // you are going out of screen
  {
	  len = (uint16_t)( (LCD_MaxWidth - x) / Font_Width() );
  }
  for (i=0; i<len; i++)
  {
	LCD_PutChar(x + (i*Font_Width()), y, *str++, ForeColor, BackColor);
  }
}

void LCD_DrawImage(char* bmp_buffer, uint16_t buff_len, uint16_t x, uint16_t y, uint16_t o_width, uint16_t o_height, uint16_t x_src, uint16_t y_src, uint16_t width, uint16_t height)
{

	uint16_t x_des = x;
	uint16_t y_des = y;
	uint16_t width_org = o_width;
	uint16_t height_org = o_height;
	int len = (width * height) << 1; // RGB_565 format
	int data = 0;
	int i, j;

	// check if pos + offset is out of screen
	// if (x_des +width> screen_width ) return FALSE;
	// if (y_des + height > screen_height) return FALSE;   
	if (x_src == 0 && y_src == 0 && width_org == width && height_org == height) // Draw full image
	{
		LCD_SetDrawingWindow(x, y, width, height);
		LCD_WriteCommand(CMD_WR_MEMSTART);
		Clr_Cs;
		for (i = 0; i < len; i += 2)
		{
			data = ((bmp_buffer[i] << 8) | (bmp_buffer[i + 1]));
			LCD_WriteData(data);
		}
		Set_Cs;
		return;
	}
	else
	{
		// Draw a piece of image
		if ((x_src + width) <= width_org && (y_src + height) <= height_org)
		{
			if (x_src % 2 != 0) x_src--;
			LCD_SetDrawingWindow(x_des, y_des, width, height);
			LCD_WriteCommand(CMD_WR_MEMSTART);
			Clr_Cs;
			for (i = y_src; i<y_src + height; i++)
			{
				//for(j=x_src*2;j<(x_src*2+width*2);j+=2)
				for (j = (x_src << 1); j<((x_src << 1) + (width << 1)); j += 2)
				{

					data = ((bmp_buffer[i*width_org * 2 + j] << 8) | (bmp_buffer[i*width_org * 2 + j + 1]));
					LCD_WriteData(data);
				}
			}
			Set_Cs;
			return;
		}
		else
		{
			return;
		}
	}

}

void LCD_Circle(uint16_t cx, uint16_t cy, uint16_t r,uint16_t color, bool fill)
{
	uint16_t x,y;
	int16_t delta,tmp;
	x = 0;
	y = r;
	delta = 3 - (r<<1);

	while(y > x)
	{
		if(fill)
		{
			LCD_Line(cx+x,cy+y,cx-x,cy+y,color);
			LCD_Line(cx+x,cy-y,cx-x,cy-y,color);
			LCD_Line(cx+y,cy+x,cx-y,cy+x,color);
			LCD_Line(cx+y,cy-x,cx-y,cy-x,color);
		}
		else
		{
			LCD_SetPixelAddress(cx+x,cy+y,color);
			LCD_SetPixelAddress(cx-x,cy+y,color);
			LCD_SetPixelAddress(cx+x,cy-y,color);
			LCD_SetPixelAddress(cx-x,cy-y,color);
			LCD_SetPixelAddress(cx+y,cy+x,color);
			LCD_SetPixelAddress(cx-y,cy+x,color);
			LCD_SetPixelAddress(cx+y,cy-x,color);
			LCD_SetPixelAddress(cx-y,cy-x,color);
		}
		x++;
		if(delta >= 0)
		{
			y--;
			tmp = (x<<2);
			tmp -= (y<<2);
			delta += (tmp+10);
		}
		else
		{
			delta+=((x<<2)+6);
		}
	}
}

void LCD_SetScrollArea(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t scrollx, uint16_t scrolly, bool up_down)
{
	// x, width, scrollx, updown not used
	uint8_t l_data, h_data;
	h_data = (uint8_t) (((y + height) & 0xff00) >> 8 );
	l_data = (uint8_t) (((y + height) & 0x00ff));

	LCD_WriteCommand(CMD_SET_SCROLL_START); // set scroll area start
	LCD_WriteData(h_data);
	LCD_WriteData(l_data);

}

void SetPWMBacklight(uint8_t value)
{
	LCD_WriteCommand(CMD_SET_PWM_CONF);
	Clr_Cs;
	LCD_WriteData(0x06);
	LCD_WriteData(value);
	LCD_WriteData(0x01);
	LCD_WriteData(0xFF);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	Set_Cs;
}

/*

INT8 LCD_SetSpecialConfig(INT32 key, INT32 value)
{
	switch (key)
	{
		case 1: //Display Type
			if (value != N18 && value != GAMEO)
				return 0;

			g_SpecialDisplayConfigType = value;

			return 1;

		case 2: //Display BPP
			if (value != 7 && value != 8)
				return 0;

			g_SpecialDisplayConfigBPP = value;

			return 1;

		case 3: //Display Orientation
			if (value != ORIENTATION_ROT_0 && value != ORIENTATION_ROT_90 && value != ORIENTATION_ROT_180 && value != ORIENTATION_ROT_270)
				return 0;

			g_SpecialDisplayConfigOrientation = value;

			return 1;

		case 4: //Display Pin
			g_SpecialDisplayConfigRSPin = value;

			return 1;
		
		//SPI Configuration
		case 5: g_SpecialDisplayConfigSPI.DeviceCS = (GPIO_PIN)value; return 1;
		case 6: g_SpecialDisplayConfigSPI.CS_Active = (BOOL)value; return 1;
		case 7: g_SpecialDisplayConfigSPI.MSK_IDLE = (BOOL)value; return 1;
		case 8: g_SpecialDisplayConfigSPI.MSK_SampleEdge = (BOOL)value; return 1;
		case 9: g_SpecialDisplayConfigSPI.Clock_RateKHz = (UINT32)value; return 1;
		case 10: g_SpecialDisplayConfigSPI.CS_Setup_uSecs = (UINT32)value; return 1;
		case 11: g_SpecialDisplayConfigSPI.CS_Hold_uSecs = (UINT32)value; return 1;
		case 12: g_SpecialDisplayConfigSPI.SPI_mod = (UINT32)value; return 1;
		case 13: g_SpecialDisplayConfigSPI.BusyPin.Pin = (GPIO_PIN)value; return 1;
		case 14: g_SpecialDisplayConfigSPI.BusyPin.ActiveState = (BOOL)value; return 1;

		default:
			return 0;
	}
	return 0;
}
	*/
