// Copyright Microsoft Corporation
// Copyright GHI Electronics, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <string.h>
#include "STM32F7.h"

#ifdef INCLUDE_DISPLAY_DSI

#include "HAL_DsiDisplay.h"
#include "STM32F7_DsiDisplay.h"

#define MAX_LAYER  2

/**
  * @brief  LTDC color structure definition
  */
typedef struct {
	uint8_t Blue;                    /*!< Configures the blue value.
										  This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */
	uint8_t Green;                   /*!< Configures the green value.
										  This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */
	uint8_t Red;                     /*!< Configures the red value.
										  This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */
	uint8_t Reserved;                /*!< Reserved 0xFF */
} LTDC_ColorTypeDef;

/**
  * @brief  LTDC Init structure definition
  */
typedef struct {
	uint32_t            HSPolarity;                /*!< configures the horizontal synchronization polarity.
														This parameter can be one value of @ref LTDC_HS_POLARITY */
	uint32_t            VSPolarity;                /*!< configures the vertical synchronization polarity.
														This parameter can be one value of @ref LTDC_VS_POLARITY */
	uint32_t            DEPolarity;                /*!< configures the data enable polarity.
														This parameter can be one of value of @ref LTDC_DE_POLARITY */
	uint32_t            PCPolarity;                /*!< configures the pixel clock polarity.
														This parameter can be one of value of @ref LTDC_PC_POLARITY */
	uint32_t            HorizontalSync;            /*!< configures the number of Horizontal synchronization width.
														This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
	uint32_t            VerticalSync;              /*!< configures the number of Vertical synchronization height.
														This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF. */
	uint32_t            AccumulatedHBP;            /*!< configures the accumulated horizontal back porch width.
														This parameter must be a number between Min_Data = LTDC_HorizontalSync and Max_Data = 0xFFF. */
	uint32_t            AccumulatedVBP;            /*!< configures the accumulated vertical back porch height.
														This parameter must be a number between Min_Data = LTDC_VerticalSync and Max_Data = 0x7FF. */
	uint32_t            AccumulatedActiveW;        /*!< configures the accumulated active width.
														This parameter must be a number between Min_Data = LTDC_AccumulatedHBP and Max_Data = 0xFFF. */
	uint32_t            AccumulatedActiveH;        /*!< configures the accumulated active height.
														This parameter must be a number between Min_Data = LTDC_AccumulatedVBP and Max_Data = 0x7FF. */
	uint32_t            TotalWidth;                /*!< configures the total width.
														This parameter must be a number between Min_Data = LTDC_AccumulatedActiveW and Max_Data = 0xFFF. */
	uint32_t            TotalHeigh;                /*!< configures the total height.
														This parameter must be a number between Min_Data = LTDC_AccumulatedActiveH and Max_Data = 0x7FF. */
	LTDC_ColorTypeDef   Backcolor;                 /*!< Configures the background color. */
} LTDC_InitTypeDef;

/**
  * @brief  LTDC Layer structure definition
  */
typedef struct {
	uint32_t WindowX0;                   /*!< Configures the Window Horizontal Start Position.
											  This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
	uint32_t WindowX1;                   /*!< Configures the Window Horizontal Stop Position.
											  This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
	uint32_t WindowY0;                   /*!< Configures the Window vertical Start Position.
											  This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF. */
	uint32_t WindowY1;                   /*!< Configures the Window vertical Stop Position.
											  This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x7FF. */
	uint32_t PixelFormat;                /*!< Specifies the pixel format.
											  This parameter can be one of value of @ref LTDC_Pixelformat */
	uint32_t Alpha;                      /*!< Specifies the constant alpha used for blending.
											  This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */
	uint32_t Alpha0;                     /*!< Configures the default alpha value.
											  This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */
	uint32_t BlendingFactor1;            /*!< Select the blending factor 1.
											  This parameter can be one of value of @ref LTDC_BlendingFactor1 */
	uint32_t BlendingFactor2;            /*!< Select the blending factor 2.
											  This parameter can be one of value of @ref LTDC_BlendingFactor2 */
	uint32_t FBStartAdress;              /*!< Configures the color frame buffer address */
	uint32_t ImageWidth;                 /*!< Configures the color frame buffer line length.
											  This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x1FFF. */
	uint32_t ImageHeight;                /*!< Specifies the number of line in frame buffer.
											  This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF. */
	LTDC_ColorTypeDef   Backcolor;       /*!< Configures the layer background color. */
} LTDC_LayerCfgTypeDef;


/**
  * @brief  LTDC handle Structure definition
  */
typedef struct {
	LTDC_TypeDef                *Instance;                /*!< LTDC Register base address                */
	LTDC_InitTypeDef            Init;                     /*!< LTDC parameters                           */
	LTDC_LayerCfgTypeDef        LayerCfg[MAX_LAYER];      /*!< LTDC Layers parameters                    */
} LTDC_HandleTypeDef;

/**
  * @}
  */

/** @defgroup LTDC_HS_POLARITY LTDC HS POLARITY
* @{
*/
#define LTDC_HSPOLARITY_AL                ((uint32_t)0x00000000)                /*!< Horizontal Synchronization is active low. */
#define LTDC_HSPOLARITY_AH                LTDC_GCR_HSPOL                        /*!< Horizontal Synchronization is active high. */
/**
* @}
*/

/** @defgroup LTDC_VS_POLARITY LTDC VS POLARITY
* @{
*/
#define LTDC_VSPOLARITY_AL                ((uint32_t)0x00000000)                /*!< Vertical Synchronization is active low. */
#define LTDC_VSPOLARITY_AH                LTDC_GCR_VSPOL                        /*!< Vertical Synchronization is active high. */
/**
* @}
*/

/** @defgroup LTDC_DE_POLARITY LTDC DE POLARITY
* @{
*/
#define LTDC_DEPOLARITY_AL                ((uint32_t)0x00000000)                /*!< Data Enable, is active low. */
#define LTDC_DEPOLARITY_AH                LTDC_GCR_DEPOL                        /*!< Data Enable, is active high. */
/**
* @}
*/

/** @defgroup LTDC_PC_POLARITY LTDC PC POLARITY
* @{
*/
#define LTDC_PCPOLARITY_IPC               ((uint32_t)0x00000000)                /*!< input pixel clock. */
#define LTDC_PCPOLARITY_IIPC              LTDC_GCR_PCPOL                        /*!< inverted input pixel clock. */

/** @defgroup LTDC_Pixelformat LTDC Pixel format
* @{
*/
#define LTDC_PIXEL_FORMAT_ARGB8888                  ((uint32_t)0x00000000)      /*!< ARGB8888 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_RGB888                    ((uint32_t)0x00000001)      /*!< RGB888 LTDC pixel format   */
#define LTDC_PIXEL_FORMAT_RGB565                    ((uint32_t)0x00000002)      /*!< RGB565 LTDC pixel format   */
#define LTDC_PIXEL_FORMAT_ARGB1555                  ((uint32_t)0x00000003)      /*!< ARGB1555 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_ARGB4444                  ((uint32_t)0x00000004)      /*!< ARGB4444 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_L8                        ((uint32_t)0x00000005)      /*!< L8 LTDC pixel format       */
#define LTDC_PIXEL_FORMAT_AL44                      ((uint32_t)0x00000006)      /*!< AL44 LTDC pixel format     */
#define LTDC_PIXEL_FORMAT_AL88                      ((uint32_t)0x00000007)      /*!< AL88 LTDC pixel format     */
/**
* @}
*/

/** @defgroup LTDC_BlendingFactor1 LTDC Blending Factor1
* @{
*/
#define LTDC_BLENDING_FACTOR1_CA                       ((uint32_t)0x00000400)   /*!< Blending factor : Cte Alpha */
#define LTDC_BLENDING_FACTOR1_PAxCA                    ((uint32_t)0x00000600)   /*!< Blending factor : Cte Alpha x Pixel Alpha*/
/**
* @}
*/

/** @defgroup LTDC_BlendingFactor2 LTDC Blending Factor2
* @{
*/
#define LTDC_BLENDING_FACTOR2_CA                       ((uint32_t)0x00000005)   /*!< Blending factor : Cte Alpha */
#define LTDC_BLENDING_FACTOR2_PAxCA                    ((uint32_t)0x00000007)   /*!< Blending factor : Cte Alpha x Pixel Alpha*/
/**
* @}
*/

#define LTDC_LAYER(__HANDLE__, __LAYER__)         ((LTDC_Layer_TypeDef *)((uint32_t)(((uint32_t)((__HANDLE__)->Instance)) + 0x84 + (0x80*(__LAYER__)))))



uint32_t lcd_x_size = OTM8009A_800X480_WIDTH;
uint32_t lcd_y_size = OTM8009A_800X480_HEIGHT;



///////////////////////////////////////////////// FONTS
const uint8_t characters[129][5] = {
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00, /* Espace	0x20 */
0x00,0x00,0x4f,0x00,0x00, /* ! */
0x00,0x07,0x00,0x07,0x00, /* " */
0x14,0x7f,0x14,0x7f,0x14, /* # */
0x24,0x2a,0x7f,0x2a,0x12, /* 0x */
0x23,0x13,0x08,0x64,0x62, /* % */
0x36,0x49,0x55,0x22,0x20, /* & */
0x00,0x05,0x03,0x00,0x00, /* ' */
0x00,0x1c,0x22,0x41,0x00, /* ( */
0x00,0x41,0x22,0x1c,0x00, /* ) */
0x14,0x08,0x3e,0x08,0x14, /* // */
0x08,0x08,0x3e,0x08,0x08, /* + */
0x50,0x30,0x00,0x00,0x00, /* , */
0x08,0x08,0x08,0x08,0x08, /* - */
0x00,0x60,0x60,0x00,0x00, /* . */
0x20,0x10,0x08,0x04,0x02, /* / */
0x3e,0x51,0x49,0x45,0x3e, /* 0		0x30 */
0x00,0x42,0x7f,0x40,0x00, /* 1 */
0x42,0x61,0x51,0x49,0x46, /* 2 */
0x21,0x41,0x45,0x4b,0x31, /* 3 */
0x18,0x14,0x12,0x7f,0x10, /* 4 */
0x27,0x45,0x45,0x45,0x39, /* 5 */
0x3c,0x4a,0x49,0x49,0x30, /* 6 */
0x01,0x71,0x09,0x05,0x03, /* 7 */
0x36,0x49,0x49,0x49,0x36, /* 8 */
0x06,0x49,0x49,0x29,0x1e, /* 9 */
0x00,0x36,0x36,0x00,0x00, /* : */
0x00,0x56,0x36,0x00,0x00, /* ; */
0x08,0x14,0x22,0x41,0x00, /* < */
0x14,0x14,0x14,0x14,0x14, /* = */
0x00,0x41,0x22,0x14,0x08, /* > */
0x02,0x01,0x51,0x09,0x06, /* ? */
0x3e,0x41,0x5d,0x55,0x1e, /* @		0x40 */
0x7e,0x11,0x11,0x11,0x7e, /* A */
0x7f,0x49,0x49,0x49,0x36, /* B */
0x3e,0x41,0x41,0x41,0x22, /* C */
0x7f,0x41,0x41,0x22,0x1c, /* D */
0x7f,0x49,0x49,0x49,0x41, /* E */
0x7f,0x09,0x09,0x09,0x01, /* F */
0x3e,0x41,0x49,0x49,0x7a, /* G */
0x7f,0x08,0x08,0x08,0x7f, /* H */
0x00,0x41,0x7f,0x41,0x00, /* I */
0x20,0x40,0x41,0x3f,0x01, /* J */
0x7f,0x08,0x14,0x22,0x41, /* K */
0x7f,0x40,0x40,0x40,0x40, /* L */
0x7f,0x02,0x0c,0x02,0x7f, /* M */
0x7f,0x04,0x08,0x10,0x7f, /* N */
0x3e,0x41,0x41,0x41,0x3e, /* O */
0x7f,0x09,0x09,0x09,0x06, /* P		0x50 */
0x3e,0x41,0x51,0x21,0x5e, /* Q */
0x7f,0x09,0x19,0x29,0x46, /* R */
0x26,0x49,0x49,0x49,0x32, /* S */
0x01,0x01,0x7f,0x01,0x01, /* T */
0x3f,0x40,0x40,0x40,0x3f, /* U */
0x1f,0x20,0x40,0x20,0x1f, /* V */
0x3f,0x40,0x38,0x40,0x3f, /* W */
0x63,0x14,0x08,0x14,0x63, /* X */
0x07,0x08,0x70,0x08,0x07, /* Y */
0x61,0x51,0x49,0x45,0x43, /* Z */
0x00,0x7f,0x41,0x41,0x00, /* [ */
0x02,0x04,0x08,0x10,0x20, /* \ */
0x00,0x41,0x41,0x7f,0x00, /* ] */
0x04,0x02,0x01,0x02,0x04, /* ^ */
0x40,0x40,0x40,0x40,0x40, /* _ */
0x00,0x00,0x03,0x05,0x00, /* `		0x60 */
0x20,0x54,0x54,0x54,0x78, /* a */
0x7F,0x44,0x44,0x44,0x38, /* b */
0x38,0x44,0x44,0x44,0x44, /* c */
0x38,0x44,0x44,0x44,0x7f, /* d */
0x38,0x54,0x54,0x54,0x18, /* e */
0x04,0x04,0x7e,0x05,0x05, /* f */
0x08,0x54,0x54,0x54,0x3c, /* g */
0x7f,0x08,0x04,0x04,0x78, /* h */
0x00,0x44,0x7d,0x40,0x00, /* i */
0x20,0x40,0x44,0x3d,0x00, /* j */
0x7f,0x10,0x28,0x44,0x00, /* k */
0x00,0x41,0x7f,0x40,0x00, /* l */
0x7c,0x04,0x7c,0x04,0x78, /* m */
0x7c,0x08,0x04,0x04,0x78, /* n */
0x38,0x44,0x44,0x44,0x38, /* o */
0x7c,0x14,0x14,0x14,0x08, /* p		0x70 */
0x08,0x14,0x14,0x14,0x7c, /* q */
0x7c,0x08,0x04,0x04,0x00, /* r */
0x48,0x54,0x54,0x54,0x24, /* s */
0x04,0x04,0x3f,0x44,0x44, /* t */
0x3c,0x40,0x40,0x20,0x7c, /* u */
0x1c,0x20,0x40,0x20,0x1c, /* v */
0x3c,0x40,0x30,0x40,0x3c, /* w */
0x44,0x28,0x10,0x28,0x44, /* x */
0x0c,0x50,0x50,0x50,0x3c, /* y */
0x44,0x64,0x54,0x4c,0x44, /* z */
0x08,0x36,0x41,0x41,0x00, /* { */
0x00,0x00,0x77,0x00,0x00, /* | */
0x00,0x41,0x41,0x36,0x08, /* } */
0x08,0x08,0x2a,0x1c,0x08, /* <- */
0x08,0x1c,0x2a,0x08,0x08, /* -> */
0xff,0xff,0xff,0xff,0xff, /* 	 	0x80 */
};

#define VIDEO_RAM_SIZE (800*480*2) // Maximum LCD screen size times bytes per pixel
//#define VIDEO_RAM_SIZE (0x40000) // Maximum LCD screen size times bytes per pixel

#define UNCACHE_LCD_BUFFER_ADDRESS 0xC0000000 // fix it on SDRAM (end=0xC003FC00)
//#define UNCACHE_LCD_BUFFER_ADDRESS 0x081C0000

#define VIDEO_RAM_ADDRESS UNCACHE_LCD_BUFFER_ADDRESS 

#define LCD_MAX_ROW	32
#define LCD_MAX_COLUMN 70

enum STM32F7xx_LCD_Rotation {
	rotateNormal_0,
	rotateCW_90,
	rotate_180,
	rotateCCW_90,
};

// default to RK043
uint32_t m_STM32F7_DisplayWidth = 800;
uint32_t m_STM32F7_DisplayHeight = 640;
uint32_t m_STM32F7_DisplayPixelClockRateKHz = 9600;
uint32_t m_STM32F7_DisplayHorizontalSyncPulseWidth = 41;
uint32_t m_STM32F7_DisplayHorizontalFrontPorch = 32;
uint32_t m_STM32F7_DisplayHorizontalBackPorch = 13;
uint32_t m_STM32F7_DisplayVerticalSyncPulseWidth = 10;
uint32_t m_STM32F7_DisplayVerticalFrontPorch = 2;
uint32_t m_STM32F7_DisplayVerticalBackPorch = 2;
uint32_t m_STM32F7_Display_TextRow = 0;
uint32_t m_STM32F7_Display_TextColumn = 0;

bool m_STM32F7_DisplayOutputEnableIsFixed = true;
bool m_STM32F7_DisplayOutputEnablePolarity = true;
bool m_STM32F7_DisplayPixelPolarity = false;
bool m_STM32F7_DisplayHorizontalSyncPolarity = false;
bool m_STM32F7_DisplayVerticalSyncPolarity = false;
bool m_STM32F7_DisplayEnable = false;

uint16_t* m_STM32F7_Display_VituralRam = (uint16_t*)UNCACHE_LCD_BUFFER_ADDRESS;
uint8_t m_STM32F7_Display_TextBuffer[LCD_MAX_COLUMN][LCD_MAX_ROW];

STM32F7xx_LCD_Rotation m_STM32F7_Display_CurrentRotation = STM32F7xx_LCD_Rotation::rotateNormal_0;

bool STM32F7_Display_Initialize(LTDC_HandleTypeDef* hltdc_F);
bool STM32F7_Display_Uninitialize();
bool STM32F7_Display_SetPinConfiguration();

void STM32F7_Display_WriteFormattedChar(uint8_t c);
void STM32F7_Display_WriteChar(uint8_t c, int32_t row, int32_t col);
void STM32F7_Display_BitBltEx(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t data[]);
void STM32F7_Display_PaintPixel(uint32_t x, uint32_t y, uint8_t c);
void STM32F7_Display_Paint8HorizontalPixels(uint32_t x, uint32_t y, uint8_t p);
void STM32F7_Display_TextEnterClearMode();
void STM32F7_Display_PrintChracter(uint32_t x, uint32_t y, uint8_t c);
void STM32F7_Display_TextShiftColUp();
void STM32F7_Display_Clear();
void STM32F7_Display_GetRotatedDimensions(int32_t *screenWidth, int32_t *screenHeight);

int32_t STM32F7_Display_GetWidth();
int32_t STM32F7_Display_GetHeight();
int32_t STM32F7_Display_BitPerPixel();
uint32_t STM32F7_Display_GetPixelClockDivider();
int32_t STM32F7_Display_GetOrientation();
uint32_t* STM32F7_Display_GetFrameBuffer();

static TinyCLR_Display_Provider displayProvider;
static TinyCLR_Api_Info displayApi;
static LTDC_HandleTypeDef hltdc_discovery;

// Implementations for the DSI Hal

bool HAL_DSI_ConfigVideoMode(DSI_HandleTypeDef *hdsi, DSI_VidCfgTypeDef *VidCfg);
bool HAL_DSI_ConfigAdaptedCommandMode(DSI_HandleTypeDef *hdsi, DSI_CmdCfgTypeDef *CmdCfg);
bool HAL_DSI_ConfigCommand(DSI_HandleTypeDef *hdsi, DSI_LPCmdTypeDef *LPCmd);
bool HAL_DSI_Init(DSI_HandleTypeDef *hdsi, DSI_PLLInitTypeDef *PLLInit);
//void BSP_LCD_Reset(void);
static uint16_t LCD_IO_GetID(void);
void BSP_LCD_MspInit(void);
bool BSP_DSI_Deinit(DSI_HandleTypeDef *hdsi);
bool HAL_DSI_DeInit(DSI_HandleTypeDef *hdsi);
bool HAL_LTDC_StructInitFromVideoConfig(LTDC_HandleTypeDef* hltdc, DSI_VidCfgTypeDef *VidCfg);
uint8_t BSP_LCD_InitEx(LCD_OrientationTypeDef orientation);
bool HAL_DSI_Start(DSI_HandleTypeDef *hdsi);
bool HAL_DSI_ShortWrite(DSI_HandleTypeDef *hdsi, uint32_t ChannelID, uint32_t Mode,	uint32_t Param1, uint32_t Param2);
bool HAL_DSI_LongWrite(DSI_HandleTypeDef *hdsi,	uint32_t ChannelID,	uint32_t Mode,	uint32_t NbParams,	uint32_t Param1, uint8_t* ParametersTable);
static void DSI_ConfigPacketHeader(DSI_TypeDef *DSIx, uint32_t ChannelID, uint32_t DataType, uint32_t Data0, uint32_t Data1);



DSI_HandleTypeDef  hdsi_discovery;
static DSI_VidCfgTypeDef hdsivideo_handle;


extern void STM32F7_DebugLed(uint16_t pin, bool onoff);

void STM32F7_WriteHello()
{
	//STM32F7_Display_Enable(NULL);
	char buffer[] = "\nDiscovery DISC0-STM32F769NI DSI Display driver\n";
	size_t t = strlen(buffer);
	STM32F7_Display_Clear();
	STM32F7_DsiDisplay_WriteString(NULL, buffer, t);	
}


bool STM32F7_Ltdc_Initialize(LTDC_HandleTypeDef *hltdc) {
	uint32_t tmp = 0, tmp1 = 0;

	/* Check the LTDC peripheral state */
	if (hltdc == nullptr) {
		return false;
	}

	/* Configures the HS, VS, DE and PC polarity */
	hltdc->Instance->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
	hltdc->Instance->GCR |= (uint32_t)(hltdc->Init.HSPolarity | hltdc->Init.VSPolarity | \
		hltdc->Init.DEPolarity | hltdc->Init.PCPolarity);

	/* Sets Synchronization size */
	hltdc->Instance->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
	tmp = (hltdc->Init.HorizontalSync << 16);
	hltdc->Instance->SSCR |= (tmp | hltdc->Init.VerticalSync);

	/* Sets Accumulated Back porch */
	hltdc->Instance->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
	tmp = (hltdc->Init.AccumulatedHBP << 16);
	hltdc->Instance->BPCR |= (tmp | hltdc->Init.AccumulatedVBP);

	/* Sets Accumulated Active Width */
	hltdc->Instance->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
	tmp = (hltdc->Init.AccumulatedActiveW << 16);
	hltdc->Instance->AWCR |= (tmp | hltdc->Init.AccumulatedActiveH);

	/* Sets Total Width */
	hltdc->Instance->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
	tmp = (hltdc->Init.TotalWidth << 16);
	hltdc->Instance->TWCR |= (tmp | hltdc->Init.TotalHeigh);

	/* Sets the background color value */
	tmp = ((uint32_t)(hltdc->Init.Backcolor.Green) << 8);
	tmp1 = ((uint32_t)(hltdc->Init.Backcolor.Red) << 16);
	hltdc->Instance->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
	hltdc->Instance->BCCR |= (tmp1 | tmp | hltdc->Init.Backcolor.Blue);

	/* Enable the transfer Error interrupt */
	hltdc->Instance->IER |= LTDC_IER_TERRIE;

	/* Enable the FIFO underrun interrupt */
	hltdc->Instance->IER |= LTDC_IER_FUIE;


	/* Enable LTDC by setting LTDCEN bit */
	hltdc->Instance->GCR |= LTDC_GCR_LTDCEN;

	// reload regs immediately
	hltdc->Instance->SRCR = LTDC_SRCR_IMR;

	return true;
}

void STM32F7_Ltdc_SetConfiguration(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx) {
	uint32_t tmp = 0;
	uint32_t tmp1 = 0;
	uint32_t tmp2 = 0;

	/* Configures the horizontal start and stop position */
	tmp = ((pLayerCfg->WindowX1 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16)) << 16);
	LTDC_LAYER(hltdc, LayerIdx)->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
	LTDC_LAYER(hltdc, LayerIdx)->WHPCR = ((pLayerCfg->WindowX0 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16) + 1) | tmp);

	/* Configures the vertical start and stop position */
	tmp = ((pLayerCfg->WindowY1 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP)) << 16);
	LTDC_LAYER(hltdc, LayerIdx)->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
	LTDC_LAYER(hltdc, LayerIdx)->WVPCR = ((pLayerCfg->WindowY0 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP) + 1) | tmp);

	/* Specifies the pixel format */
	LTDC_LAYER(hltdc, LayerIdx)->PFCR &= ~(LTDC_LxPFCR_PF);
	LTDC_LAYER(hltdc, LayerIdx)->PFCR = (pLayerCfg->PixelFormat);

	/* Configures the default color values */
	tmp = ((uint32_t)(pLayerCfg->Backcolor.Green) << 8);
	tmp1 = ((uint32_t)(pLayerCfg->Backcolor.Red) << 16);
	tmp2 = (pLayerCfg->Alpha0 << 24);
	LTDC_LAYER(hltdc, LayerIdx)->DCCR &= ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
	LTDC_LAYER(hltdc, LayerIdx)->DCCR = (pLayerCfg->Backcolor.Blue | tmp | tmp1 | tmp2);

	/* Specifies the constant alpha value */
	LTDC_LAYER(hltdc, LayerIdx)->CACR &= ~(LTDC_LxCACR_CONSTA);
	LTDC_LAYER(hltdc, LayerIdx)->CACR = (pLayerCfg->Alpha);

	/* Specifies the blending factors */
	LTDC_LAYER(hltdc, LayerIdx)->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
	LTDC_LAYER(hltdc, LayerIdx)->BFCR = (pLayerCfg->BlendingFactor1 | pLayerCfg->BlendingFactor2);

	/* Color key */
	//LTDC_LAYER(hltdc, LayerIdx)->CKCR &= ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
	//LTDC_LAYER(hltdc, LayerIdx)->CKCR = 0x0;

	/* Configures the color frame buffer start address */
	LTDC_LAYER(hltdc, LayerIdx)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
	LTDC_LAYER(hltdc, LayerIdx)->CFBAR = (pLayerCfg->FBStartAdress);

	if (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888) {
		tmp = 4;
	}
	else if (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB888) {
		tmp = 3;
	}
	else if ((pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
		(pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB565) || \
		(pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
		(pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_AL88)) {
		tmp = 2;
	}
	else {
		tmp = 1;
	}

	/* Configures the color frame buffer pitch in byte */
	LTDC_LAYER(hltdc, LayerIdx)->CFBLR &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
	LTDC_LAYER(hltdc, LayerIdx)->CFBLR = (((pLayerCfg->ImageWidth * tmp) << 16) | (((pLayerCfg->WindowX1 - pLayerCfg->WindowX0) * tmp) + 3));

	/* Configures the frame buffer line number */
	LTDC_LAYER(hltdc, LayerIdx)->CFBLNR &= ~(LTDC_LxCFBLNR_CFBLNBR);
	LTDC_LAYER(hltdc, LayerIdx)->CFBLNR = (pLayerCfg->ImageHeight);

	/* Enable LTDC_Layer by setting LEN bit */
	LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_LEN;
}


void STM32F7_Ltdc_LayerConfiguration(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx) {
	
	
	/* Copy new layer configuration into handle structure */
	hltdc->LayerCfg[LayerIdx] = *pLayerCfg;

	/* Configure the LTDC Layer */
	STM32F7_Ltdc_SetConfiguration(hltdc, pLayerCfg, LayerIdx);

	/* Sets the Reload to immediate */
	hltdc->Instance->SRCR = LTDC_SRCR_IMR;
}

bool STM32F7_Display_Initialize(LTDC_HandleTypeDef* hltdc) {
	// InitializeConfiguration
	LTDC_LayerCfgTypeDef      pLayerCfg;

	RCC->CR &= ~(RCC_CR_PLLSAION);
	// Wait for locked bit
	while (RCC->CR & RCC_CR_PLLSAIRDY == 0);

	STM32F7_Time_Delay(nullptr, 0x20000);

	RCC->PLLSAICFGR = (0x180 << 6) | ((0x3) << 16) | ((0xF) << 24) | ((0x7) << 28);

	// LDTC clock set is at 9.5Mhz PLLR/4
	MODIFY_REG(RCC->DCKCFGR1, RCC_DCKCFGR1_PLLSAIDIVR, (uint32_t)(0x00000000));

	//RCC->DCKCFGR1 &= ~(RCC_DCKCFGR1_PLLSAIDIVR);
	//RCC->DCKCFGR1 |= RCC_DCKCFGR1_PLLSAIDIVR_0; // now LDTC clock is at 9.5Mhz 

	RCC->CR |= (RCC_CR_PLLSAION);

	// Wait for unlocked bit
	while (RCC->CR & RCC_CR_PLLSAIRDY != RCC_CR_PLLSAIRDY);

	STM32F7_Time_Delay(nullptr, 0x10000);

	// Activate LTDC
	do {
		RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;
		__IO uint32_t rr = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);
	} while (0);
	
	//hltdc_F.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	//hltdc_F.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	//hltdc_F.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	//hltdc_F.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

	///* The RK043FN48H LCD 480x272 is selected */
	///* Timing Configuration */
	//hltdc_F.Init.HorizontalSync = (m_STM32F7_DisplayHorizontalSyncPulseWidth - 1);
	//hltdc_F.Init.VerticalSync = (m_STM32F7_DisplayVerticalSyncPulseWidth - 1);
	//hltdc_F.Init.AccumulatedHBP = (m_STM32F7_DisplayHorizontalSyncPulseWidth + m_STM32F7_DisplayHorizontalBackPorch - 1);
	//hltdc_F.Init.AccumulatedVBP = (m_STM32F7_DisplayVerticalSyncPulseWidth + m_STM32F7_DisplayVerticalBackPorch - 1);
	//hltdc_F.Init.AccumulatedActiveH = (m_STM32F7_DisplayHeight + m_STM32F7_DisplayVerticalSyncPulseWidth + m_STM32F7_DisplayVerticalBackPorch - 1);
	//hltdc_F.Init.AccumulatedActiveW = (m_STM32F7_DisplayWidth + m_STM32F7_DisplayHorizontalSyncPulseWidth + m_STM32F7_DisplayHorizontalBackPorch - 1);
	//hltdc_F.Init.TotalHeigh = (m_STM32F7_DisplayHeight + m_STM32F7_DisplayVerticalSyncPulseWidth + m_STM32F7_DisplayVerticalBackPorch + m_STM32F7_DisplayVerticalFrontPorch - 1);
	//hltdc_F.Init.TotalWidth = (m_STM32F7_DisplayWidth + m_STM32F7_DisplayHorizontalSyncPulseWidth + m_STM32F7_DisplayHorizontalBackPorch + m_STM32F7_DisplayHorizontalFrontPorch - 1);
	///* Layer1 Configuration ------------------------------------------------------*/


	///* Configure R,G,B component values for LCD background color : all black background */
	//hltdc_F.Init.Backcolor.Blue = 0;
	//hltdc_F.Init.Backcolor.Green = 0;
	//hltdc_F.Init.Backcolor.Red = 0;

	hltdc->Instance = LTDC;

	/* Windowing configuration */
	/* In this case all the active display area is used to display a picture then :
	 Horizontal start = horizontal synchronization + Horizontal back porch = 43
	 Vertical start   = vertical synchronization + vertical back porch     = 12
	 Horizontal stop = Horizontal start + window width -1 = 43 + 480 -1
	 Vertical stop   = Vertical start + window height -1  = 12 + 272 -1      */
	pLayerCfg.WindowX0 = 0;
	pLayerCfg.WindowX1 = m_STM32F7_DisplayWidth;
	pLayerCfg.WindowY0 = 0;
	pLayerCfg.WindowY1 = m_STM32F7_DisplayHeight;
	/* Pixel Format configuration*/
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
	//pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;

	/* Start Address configuration : frame buffer is located at SDRAM memory */
	pLayerCfg.FBStartAdress = (uint32_t)VIDEO_RAM_ADDRESS;

	/* Alpha constant (255 == totally opaque) */
	pLayerCfg.Alpha = 255;

	/* Default Color configuration (configure A,R,G,B component values) : no background color */
	pLayerCfg.Alpha0 = 0; /* fully transparent */
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;

	/* Configure blending factors */
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	//pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	//pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;

	/* Configure the number of lines and number of pixels per line */
	//pLayerCfg.ImageWidth = pLayerCfg.WindowX1;
	//pLayerCfg.ImageHeight = pLayerCfg.WindowY1;
	pLayerCfg.ImageWidth = m_STM32F7_DisplayWidth;
	pLayerCfg.ImageHeight = m_STM32F7_DisplayHeight;

	/* Configure the LTDC */
	if (!STM32F7_Ltdc_Initialize(hltdc)) {
		return false;
	}

	/* Configure the Layer*/
	STM32F7_Ltdc_LayerConfiguration(hltdc, &pLayerCfg, 0);

	m_STM32F7_DisplayEnable = true;

	STM32F7_DebugLed(PIN(J,13), true);
	//STM32F7_Display_Clear();
	return true;
}

bool STM32F7_Display_Uninitialize() {
	m_STM32F7_DisplayEnable = false;

	return true;
}

//====================================================
void STM32F7_Display_WriteFormattedChar(uint8_t c) {
	if (m_STM32F7_DisplayEnable == false)
		return;

	if (c == '\f') {
		STM32F7_Display_Clear();
		STM32F7_Display_TextEnterClearMode();
		m_STM32F7_Display_TextColumn = 0;

		return;
	}

	if (c == '\r') {
		m_STM32F7_Display_TextColumn = 0;

		return;
	}
	if (c == '\n') {
		m_STM32F7_Display_TextColumn = 0;

		if (++m_STM32F7_Display_TextRow >= LCD_MAX_ROW) {
			m_STM32F7_Display_TextRow = LCD_MAX_ROW - 1;
			STM32F7_Display_TextShiftColUp();
		}
		// clean the new line
		for (c = 0; c < (LCD_MAX_COLUMN - 1); c++) {
			m_STM32F7_Display_TextBuffer[c][m_STM32F7_Display_TextRow] = ' ';
		}

		return;
	}

	STM32F7_Display_PrintChracter(m_STM32F7_Display_TextColumn * 6, m_STM32F7_Display_TextRow * 8, c);
	m_STM32F7_Display_TextBuffer[m_STM32F7_Display_TextColumn][m_STM32F7_Display_TextRow] = c;

	if (++m_STM32F7_Display_TextColumn >= (LCD_MAX_COLUMN - 1)) {
		m_STM32F7_Display_TextColumn = 0;

		if (++m_STM32F7_Display_TextRow >= LCD_MAX_ROW) {
			m_STM32F7_Display_TextRow = LCD_MAX_ROW - 1;
			STM32F7_Display_TextShiftColUp();
		}
		else {
			// clean the new line
			for (c = 0; c < LCD_MAX_COLUMN; c++) {
				m_STM32F7_Display_TextBuffer[c][m_STM32F7_Display_TextRow] = ' ';
			}
		}
	}
}
//=======================================================
void STM32F7_Display_PaintPixel(uint32_t x, uint32_t y, uint8_t c) {
	__IO uint16_t* loc;

	if (m_STM32F7_DisplayEnable == false)
		return;

	if (x >= m_STM32F7_DisplayWidth)
		return;
	if (y >= m_STM32F7_DisplayHeight)
		return;

	loc = m_STM32F7_Display_VituralRam + (y * m_STM32F7_DisplayWidth) + x;
	//m_STM32F7_Display_VituralRam + (2 * (y * m_STM32F7_DisplayWidth) + (x));
	if (c)
		*loc = 0x0FFF;
	else
		*loc = 0x0;
}
//=======================================================
void STM32F7_Display_Paint8HorizontalPixels(uint32_t x, uint32_t y, uint8_t p) {
	if (m_STM32F7_DisplayEnable == false)
		return;

	for (int32_t i = 0; i < 8; i++) {
		if (p&(1 << i))
			STM32F7_Display_PaintPixel(x, y + i, 1);
		else
			STM32F7_Display_PaintPixel(x, y + i, 0); //clear
	}
}
//===========================================================
void STM32F7_Display_TextEnterClearMode() {
	uint32_t r, c;

	if (m_STM32F7_DisplayEnable == false)
		return;

	STM32F7_Display_Clear();
	m_STM32F7_Display_TextRow = 0;
	m_STM32F7_Display_TextColumn = 0;

	for (r = 0; r < LCD_MAX_ROW; r++) {
		for (c = 0; c < (LCD_MAX_COLUMN - 1); c++) {
			m_STM32F7_Display_TextBuffer[c][r] = '1';
		}
	}
}
//===========================================================
void STM32F7_Display_PrintChracter(uint32_t x, uint32_t y, uint8_t c) {
	uint8_t i;

	if (m_STM32F7_DisplayEnable == false)
		return;

	for (i = 0; i < 5; i++)
		STM32F7_Display_Paint8HorizontalPixels(x + i, y, characters[c][i]);

	STM32F7_Display_Paint8HorizontalPixels(x + i, y, 0);
}

void STM32F7_Display_TextShiftColUp() {
	uint32_t r, c;

	if (m_STM32F7_DisplayEnable == false)
		return;

	// refresh with new data
	STM32F7_Display_Clear();
	m_STM32F7_Display_TextRow = 0;
	m_STM32F7_Display_TextColumn = 0;

	for (r = 0; r < (LCD_MAX_ROW - 1); r++) {
		for (c = 0; c < LCD_MAX_COLUMN - 1; c++) {
			m_STM32F7_Display_TextBuffer[c][r] = m_STM32F7_Display_TextBuffer[c][r + 1];
			STM32F7_Display_WriteFormattedChar(m_STM32F7_Display_TextBuffer[c][r]);
		}
	}
}

void STM32F7_Display_Clear() {
	if (m_STM32F7_DisplayEnable == false)
		return;
	uint32_t len = m_STM32F7_DisplayWidth * m_STM32F7_DisplayHeight * 2;
	uint32_t i = 0;
	uint16_t *ptr_frame_mem;
	ptr_frame_mem = (uint16_t*)VIDEO_RAM_ADDRESS;

	for (i = 0; i < len; i++) {
		*ptr_frame_mem++ = 0x00;
	}

	//memset((uint32_t*)m_STM32F7_Display_VituralRam, 0x8080, len);

}

//const STM32F7_Gpio_Pin g_Display_ControllerPins[] = STM32F7_DISPLAY_CONTROLLER_PINS;
const STM32F7_Gpio_Pin g_Display_BacklightPin = STM32F7_DISPLAY_BACKLIGHT_PIN;
const STM32F7_Gpio_Pin g_Display_ResetPin = STM32F7_DISPLAY_RESET_PIN;

bool  STM32F7_DsiDisplay_SetPinConfiguration() {

	// Reset need to be HIGH level
	STM32F7_GpioInternal_ConfigurePin(g_Display_ResetPin.number, STM32F7_Gpio_PortMode::GeneralPurposeOutput, STM32F7_Gpio_OutputType::PushPull, STM32F7_Gpio_OutputSpeed::VeryHigh, STM32F7_Gpio_PullDirection::None, STM32F7_Gpio_AlternateFunction::AF0);
	STM32F7_GpioInternal_WritePin(g_Display_ResetPin.number, true);

	//backlight LCD
	STM32F7_GpioInternal_ConfigurePin(g_Display_BacklightPin.number, STM32F7_Gpio_PortMode::GeneralPurposeOutput, STM32F7_Gpio_OutputType::PushPull, STM32F7_Gpio_OutputSpeed::VeryHigh, STM32F7_Gpio_PullDirection::None, STM32F7_Gpio_AlternateFunction::AF0);
	STM32F7_GpioInternal_WritePin(g_Display_BacklightPin.number, true);

	return true;
}

bool STM32F7_DsiDisplay_ResetLCD() {
	STM32F7_GpioInternal_ConfigurePin(g_Display_ResetPin.number, STM32F7_Gpio_PortMode::GeneralPurposeOutput, STM32F7_Gpio_OutputType::PushPull, STM32F7_Gpio_OutputSpeed::VeryHigh, STM32F7_Gpio_PullDirection::None, STM32F7_Gpio_AlternateFunction::AF0);
	STM32F7_GpioInternal_WritePin(g_Display_ResetPin.number, false);
	STM32F7_Time_Delay(nullptr, 1000000);
	STM32F7_GpioInternal_WritePin(g_Display_ResetPin.number, true);
}

uint32_t* STM32F7_Display_GetFrameBuffer() {
	return (uint32_t*)m_STM32F7_Display_VituralRam;
}

int32_t STM32F7_Display_GetWidth() {
	int32_t width = m_STM32F7_DisplayWidth;
	int32_t height = m_STM32F7_DisplayHeight;

	STM32F7_Display_GetRotatedDimensions(&width, &height);

	return width;
}

int32_t STM32F7_Display_GetHeight() {
	int32_t width = m_STM32F7_DisplayWidth;
	int32_t height = m_STM32F7_DisplayHeight;

	STM32F7_Display_GetRotatedDimensions(&width, &height);

	return height;
}

uint32_t STM32F7_Display_GetPixelClockDivider() {
	return m_STM32F7_DisplayPixelClockRateKHz;
}
int32_t STM32F7_Display_GetOrientation() {
	return m_STM32F7_Display_CurrentRotation;
}

void  STM32F7_Display_MemCopy(void *dest, void *src, int32_t size) {
	const int32_t MEMCOPY_BYTES_ALIGNED = 8;

	uint64_t *from64 = (uint64_t *)src;
	uint64_t *to64 = (uint64_t *)dest;

	int32_t block = size / MEMCOPY_BYTES_ALIGNED;
	int32_t remainder = size % MEMCOPY_BYTES_ALIGNED;

	while (block > 0) {
		*to64++ = *from64++;
		block--;
	}

	if (remainder > 0) {
		uint8_t *from8 = (uint8_t *)from64;
		uint8_t *to8 = (uint8_t *)to64;

		while (remainder > 0) {
			*to8++ = *from8++;

			remainder--;
		}
	}
}

void STM32F7_Display_BitBltEx(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t data[]) {

	int32_t xTo, yTo, xFrom, yFrom;
	int32_t xOffset = x;
	int32_t yOffset = y;
	uint16_t *from = (uint16_t *)data;
	uint16_t *to = (uint16_t *)m_STM32F7_Display_VituralRam;


	int32_t screenWidth = m_STM32F7_DisplayWidth;
	int32_t screenHeight = m_STM32F7_DisplayHeight;
	int32_t startPx, toAddition;

	if (m_STM32F7_DisplayEnable == false)
		return;

	switch (m_STM32F7_Display_CurrentRotation) {
	case STM32F7xx_LCD_Rotation::rotateNormal_0:

		if (xOffset == 0 && yOffset == 0 &&
			width == screenWidth &&    height == screenHeight) {
			STM32F7_Display_MemCopy(to, from, (screenWidth*screenHeight * 2));
		}
		else {
			for (yTo = yOffset; yTo < (yOffset + height); yTo++) {
				STM32F7_Display_MemCopy((void*)(to + yTo * screenWidth + xOffset), (void*)(from + yTo * screenWidth + xOffset), (width * 2));
			}
		}

		break;

	case STM32F7xx_LCD_Rotation::rotateCCW_90:

		startPx = yOffset * screenHeight;
		xFrom = xOffset + width;
		yTo = screenHeight - xOffset - width;
		xTo = yOffset;
		to += yTo * screenWidth + xTo;
		toAddition = screenWidth - height;

		for (; yTo < (screenHeight - xOffset); yTo++) {
			xFrom--;
			yFrom = startPx + xFrom;

			for (xTo = yOffset; xTo < (yOffset + height); xTo++) {
				*to++ = from[yFrom];
				yFrom += screenHeight;
			}

			to += toAddition;
		}

		break;

	case STM32F7xx_LCD_Rotation::rotateCW_90:

		startPx = (yOffset + height - 1) * screenHeight;
		xFrom = xOffset;

		yTo = xOffset;
		xTo = screenWidth - yOffset - height;
		to += yTo * screenWidth + xTo;
		toAddition = screenWidth - height;

		for (; yTo < (xOffset + width); yTo++) {
			yFrom = startPx + xFrom;

			for (xTo = screenWidth - yOffset - height; xTo < (screenWidth - yOffset); xTo++) {
				*to++ = from[yFrom];
				yFrom -= screenHeight;
			}

			to += toAddition;
			xFrom++;
		}

		break;

	case STM32F7xx_LCD_Rotation::rotate_180:

		xFrom = (yOffset + height - 1) * screenWidth + xOffset + width;

		yTo = screenHeight - yOffset - height;
		xTo = screenWidth - xOffset - width;
		to += yTo * screenWidth + xTo;
		toAddition = screenWidth - width;

		for (; yTo < (screenHeight - yOffset); yTo++) {

			for (xTo = screenWidth - xOffset - width; xTo < (screenWidth - xOffset); xTo++) {
				xFrom--;
				*to++ = from[xFrom];
			}

			to += toAddition;
			xFrom -= toAddition;
		}

		break;
	}

}

void STM32F7_Display_WriteChar(uint8_t c, int32_t row, int32_t col) {
	m_STM32F7_Display_TextRow = row;
	m_STM32F7_Display_TextColumn = col;
	STM32F7_Display_WriteFormattedChar(c);

}
void STM32F7_Display_GetRotatedDimensions(int32_t *screenWidth, int32_t *screenHeight) {
	switch (m_STM32F7_Display_CurrentRotation) {
	case STM32F7xx_LCD_Rotation::rotateNormal_0:
	case STM32F7xx_LCD_Rotation::rotate_180:
		*screenWidth = m_STM32F7_DisplayWidth;
		*screenHeight = m_STM32F7_DisplayHeight;
		break;

	case STM32F7xx_LCD_Rotation::rotateCCW_90:
	case STM32F7xx_LCD_Rotation::rotateCW_90:
		*screenWidth = m_STM32F7_DisplayHeight;
		*screenHeight = m_STM32F7_DisplayWidth;
		break;
	}
}


TinyCLR_Result STM32F7_DsiDisplay_Acquire(const TinyCLR_Display_Provider* self) {
	m_STM32F7_Display_CurrentRotation = STM32F7xx_LCD_Rotation::rotateNormal_0;

	m_STM32F7_Display_VituralRam = (uint16_t*)VIDEO_RAM_ADDRESS;

	return TinyCLR_Result::Success;
}

TinyCLR_Result STM32F7_DsiDisplay_Release(const TinyCLR_Display_Provider* self) {
	if (STM32F7_Display_Uninitialize())
		return TinyCLR_Result::Success;

	return  TinyCLR_Result::InvalidOperation;
}

TinyCLR_Result STM32F7_DsiDisplay_Enable(const TinyCLR_Display_Provider* self) {
	if (!STM32F7_DsiDisplay_SetPinConfiguration()) {
		return TinyCLR_Result::NotSupported;
	}
	auto a = BSP_LCD_InitEx(LCD_OrientationTypeDef::LCD_ORIENTATION_LANDSCAPE);

	return TinyCLR_Result::Success;
}

TinyCLR_Result STM32F7_DsiDisplay_Disable(const TinyCLR_Display_Provider* self) {
	return TinyCLR_Result::NotSupported;
}

TinyCLR_Result STM32F7_DsiDisplay_SetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat dataFormat, uint32_t width, uint32_t height, const void* configuration) {
	if (dataFormat != TinyCLR_Display_DataFormat::Rgb565) return TinyCLR_Result::NotSupported;

	m_STM32F7_DisplayWidth = width;
	m_STM32F7_DisplayHeight = height;

	if (configuration != nullptr) {
		
		auto& cfg = *(const TinyCLR_Display_ParallelConfiguration*)configuration;

		m_STM32F7_DisplayOutputEnableIsFixed = cfg.DataEnableIsFixed;
		m_STM32F7_DisplayOutputEnablePolarity = cfg.DataEnablePolarity;
		m_STM32F7_DisplayPixelPolarity = cfg.PixelPolarity;

		m_STM32F7_DisplayPixelClockRateKHz = cfg.PixelClockRate / 1000;

		m_STM32F7_DisplayHorizontalSyncPolarity = cfg.HorizontalSyncPolarity;

		m_STM32F7_DisplayHorizontalSyncPulseWidth = cfg.HorizontalSyncPulseWidth;
		m_STM32F7_DisplayHorizontalFrontPorch = cfg.HorizontalFrontPorch;
		m_STM32F7_DisplayHorizontalBackPorch = cfg.HorizontalBackPorch;

		m_STM32F7_DisplayVerticalSyncPolarity = cfg.VerticalSyncPolarity;

		m_STM32F7_DisplayVerticalSyncPulseWidth = cfg.VerticalSyncPulseWidth;
		m_STM32F7_DisplayVerticalFrontPorch = cfg.VerticalFrontPorch;
		m_STM32F7_DisplayVerticalBackPorch = cfg.VerticalBackPorch;

	}
	
	return  TinyCLR_Result::Success;
}

TinyCLR_Result STM32F7_DsiDisplay_GetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat& dataFormat, uint32_t& width, uint32_t& height, void* configuration) {
	dataFormat = TinyCLR_Display_DataFormat::Rgb565;
	width = m_STM32F7_DisplayWidth;
	height = m_STM32F7_DisplayHeight;

	if (configuration != nullptr) {
		auto& cfg = *(TinyCLR_Display_ParallelConfiguration*)configuration;

		cfg.DataEnableIsFixed = m_STM32F7_DisplayOutputEnableIsFixed;
		cfg.DataEnablePolarity = m_STM32F7_DisplayOutputEnablePolarity;
		cfg.PixelPolarity = m_STM32F7_DisplayPixelPolarity;

		cfg.PixelClockRate = m_STM32F7_DisplayPixelClockRateKHz * 1000;

		cfg.HorizontalSyncPolarity = m_STM32F7_DisplayHorizontalSyncPolarity;

		cfg.HorizontalSyncPulseWidth = m_STM32F7_DisplayHorizontalSyncPulseWidth;
		cfg.HorizontalFrontPorch = m_STM32F7_DisplayHorizontalFrontPorch;
		cfg.HorizontalBackPorch = m_STM32F7_DisplayHorizontalBackPorch;

		cfg.VerticalSyncPolarity = m_STM32F7_DisplayVerticalSyncPolarity;

		cfg.VerticalSyncPulseWidth = m_STM32F7_DisplayVerticalSyncPulseWidth;
		cfg.VerticalFrontPorch = m_STM32F7_DisplayVerticalFrontPorch;
		cfg.VerticalBackPorch = m_STM32F7_DisplayVerticalBackPorch;

	}

	return TinyCLR_Result::InvalidOperation;
}

TinyCLR_Result STM32F7_DsiDisplay_DrawBuffer(const TinyCLR_Display_Provider* self, int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t* data) {
	STM32F7_Display_BitBltEx(x, y, width, height, (uint32_t*)data);
	return TinyCLR_Result::Success;
}

TinyCLR_Result STM32F7_DsiDisplay_WriteString(const TinyCLR_Display_Provider* self, const char* buffer, size_t length) {
	for (size_t i = 0; i < length; i++)
		STM32F7_Display_WriteFormattedChar(buffer[i]);

	//STM32F7_DebugLed(true);
	return TinyCLR_Result::Success;
}

TinyCLR_Display_DataFormat dataFormats[] = { TinyCLR_Display_DataFormat::Rgb565 }; // , TinyCLR_Display_DataFormat::Rgb888 };

TinyCLR_Result STM32F7_DsiDisplay_GetCapabilities(const TinyCLR_Display_Provider* self, TinyCLR_Display_InterfaceType& type, const TinyCLR_Display_DataFormat*& supportedDataFormats, size_t& supportedDataFormatCount) {
	type = TinyCLR_Display_InterfaceType::Parallel;
	supportedDataFormatCount = SIZEOF_ARRAY(dataFormats);
	supportedDataFormats = dataFormats;

	return TinyCLR_Result::Success;
}

const TinyCLR_Api_Info* STM32F7_DsiDisplay_GetApi() {
	displayProvider.Parent = &displayApi;
	displayProvider.Index = 0;
	displayProvider.Acquire = &STM32F7_DsiDisplay_Acquire;
	displayProvider.Release = &STM32F7_DsiDisplay_Release;
	displayProvider.Enable = &STM32F7_DsiDisplay_Enable;
	displayProvider.Disable = &STM32F7_DsiDisplay_Disable;
	displayProvider.SetConfiguration = &STM32F7_DsiDisplay_SetConfiguration;
	displayProvider.GetConfiguration = &STM32F7_DsiDisplay_GetConfiguration;
	displayProvider.GetCapabilities = &STM32F7_DsiDisplay_GetCapabilities;
	displayProvider.DrawBuffer = &STM32F7_DsiDisplay_DrawBuffer;
	displayProvider.WriteString = &STM32F7_DsiDisplay_WriteString;

	displayApi.Author = "DB for Discovery-F769NI";
	displayApi.Name = "GHIElectronics.TinyCLR.NativeApis.STM32F7.DisplayProvider";
	displayApi.Type = TinyCLR_Api_Type::DisplayProvider;
	displayApi.Version = 0;
	displayApi.Count = 1;
	displayApi.Implementation = &displayProvider;

	return &displayApi;
}

void STM32F7_DsiDisplay_Reset() {
	STM32F7_Display_Uninitialize();
}


bool HAL_DSI_Init(DSI_HandleTypeDef *hdsi, DSI_PLLInitTypeDef *PLLInit)
{
	uint32_t tickstart = 0;
	uint32_t unitIntervalx4 = 0;
	uint32_t tempIDF = 0;

	/* Check the DSI handle allocation */
	if (hdsi == NULL)
	{
		return false;
	}

	/* Change DSI peripheral state */
	hdsi->State = HAL_DSI_STATE_BUSY;

	/**************** Turn on the regulator and enable the DSI PLL ****************/

	/* Enable the regulator */
	__HAL_DSI_REG_ENABLE(hdsi);

	while (__HAL_DSI_GET_FLAG(hdsi, DSI_FLAG_RRS) == RESET);
	/* Set the PLL division factors */
	hdsi->Instance->WRPCR &= ~(DSI_WRPCR_PLL_NDIV | DSI_WRPCR_PLL_IDF | DSI_WRPCR_PLL_ODF);
	hdsi->Instance->WRPCR |= (((PLLInit->PLLNDIV) << 2) | ((PLLInit->PLLIDF) << 11) | ((PLLInit->PLLODF) << 16));

	/* Enable the DSI PLL */
	__HAL_DSI_PLL_ENABLE(hdsi);

	/* Get tick */
	while (__HAL_DSI_GET_FLAG(hdsi, DSI_FLAG_PLLLS) == RESET);

	/*************************** Set the PHY parameters ***************************/

	/* D-PHY clock and digital enable*/
	hdsi->Instance->PCTLR |= (DSI_PCTLR_CKE | DSI_PCTLR_DEN);

	/* Clock lane configuration */
	hdsi->Instance->CLCR &= ~(DSI_CLCR_DPCC | DSI_CLCR_ACR);
	hdsi->Instance->CLCR |= (DSI_CLCR_DPCC | hdsi->Init.AutomaticClockLaneControl);

	/* Configure the number of active data lanes */
	hdsi->Instance->PCONFR &= ~DSI_PCONFR_NL;
	hdsi->Instance->PCONFR |= hdsi->Init.NumberOfLanes;

	/************************ Set the DSI clock parameters ************************/

	/* Set the TX escape clock division factor */
	hdsi->Instance->CCR &= ~DSI_CCR_TXECKDIV;
	hdsi->Instance->CCR |= hdsi->Init.TXEscapeCkdiv;

	/* Calculate the bit period in high-speed mode in unit of 0.25 ns (UIX4) */
	/* The equation is : UIX4 = IntegerPart( (1000/F_PHY_Mhz) * 4 )          */
	/* Where : F_PHY_Mhz = (NDIV * HSE_Mhz) / (IDF * ODF)                    */
	tempIDF = (PLLInit->PLLIDF > 0) ? PLLInit->PLLIDF : 1;
	unitIntervalx4 = (4000000 * tempIDF * (1 << PLLInit->PLLODF)) / ((HSE_VALUE / 1000) * PLLInit->PLLNDIV);

	/* Set the bit period in high-speed mode */
	hdsi->Instance->WPCR[0] &= ~DSI_WPCR0_UIX4;
	hdsi->Instance->WPCR[0] |= unitIntervalx4;

	/****************************** Error management *****************************/

	/* Disable all error interrupts and reset the Error Mask */
	hdsi->Instance->IER[0] = 0;
	hdsi->Instance->IER[1] = 0;
	hdsi->ErrorMsk = 0;

	/* Initialise the error code */
	hdsi->ErrorCode = HAL_DSI_ERROR_NONE;

	/* Initialize the DSI state*/
	hdsi->State = HAL_DSI_STATE_READY;

	return true;
}

uint8_t BSP_LCD_InitEx(LCD_OrientationTypeDef orientation)
{
	DSI_PLLInitTypeDef dsiPllInit;
	//static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
	uint32_t LcdClock = 27429; /*!< LcdClk = 27429 kHz */
	uint16_t read_id = 0;

	uint32_t laneByteClk_kHz = 0;
	uint32_t                   VSA; /*!< Vertical start active time in units of lines */
	uint32_t                   VBP; /*!< Vertical Back Porch time in units of lines */
	uint32_t                   VFP; /*!< Vertical Front Porch time in units of lines */
	uint32_t                   VACT; /*!< Vertical Active time in units of lines = imageSize Y in pixels to display */
	uint32_t                   HSA; /*!< Horizontal start active time in units of lcdClk */
	uint32_t                   HBP; /*!< Horizontal Back Porch time in units of lcdClk */
	uint32_t                   HFP; /*!< Horizontal Front Porch time in units of lcdClk */
	uint32_t                   HACT; /*!< Horizontal Active time in units of lcdClk = imageSize X in pixels to display */

									 /* Toggle Hardware Reset of the DSI LCD using
									 * its XRES signal (active low) */
	//BSP_LCD_Reset();
	STM32F7_DsiDisplay_ResetLCD();

	/* Check the connected monitor */
	read_id = LCD_IO_GetID();

	if (read_id != LCD_DSI_ID)
	{
		return LCD_ERROR;
	}

	/* Call first MSP Initialize only in case of first initialization
	* This will set IP blocks LTDC, DSI and DMA2D
	* - out of reset
	* - clocked
	* - NVIC IRQ related to IP blocks enabled
	*/
	BSP_LCD_MspInit();

	/*************************DSI Initialization***********************************/

	/* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
	hdsi_discovery.Instance = DSI;

	HAL_DSI_DeInit(&(hdsi_discovery));

	dsiPllInit.PLLNDIV = 100;
	dsiPllInit.PLLIDF = DSI_PLL_IN_DIV5;
	dsiPllInit.PLLODF = DSI_PLL_OUT_DIV1;
	laneByteClk_kHz = 62500; /* 500 MHz / 8 = 62.5 MHz = 62500 kHz */

							 /* Set number of Lanes */
	hdsi_discovery.Init.NumberOfLanes = DSI_TWO_DATA_LANES;

	/* TXEscapeCkdiv = f(LaneByteClk)/15.62 = 4 */
	hdsi_discovery.Init.TXEscapeCkdiv = laneByteClk_kHz / 15620;

	HAL_DSI_Init(&(hdsi_discovery), &(dsiPllInit));

	/* Timing parameters for all Video modes
	* Set Timing parameters of LTDC depending on its chosen orientation
	*/
	if (orientation == LCD_ORIENTATION_PORTRAIT)
	{
		lcd_x_size = OTM8009A_480X800_WIDTH;  /* 480 */
		lcd_y_size = OTM8009A_480X800_HEIGHT; /* 800 */
	}
	else
	{
		/* lcd_orientation == LCD_ORIENTATION_LANDSCAPE */
		lcd_x_size = OTM8009A_800X480_WIDTH;  /* 800 */
		lcd_y_size = OTM8009A_800X480_HEIGHT; /* 480 */
	}

	HACT = lcd_x_size;
	VACT = lcd_y_size;

	/* The following values are same for portrait and landscape orientations */
	VSA = OTM8009A_480X800_VSYNC;        /* 12  */
	VBP = OTM8009A_480X800_VBP;          /* 12  */
	VFP = OTM8009A_480X800_VFP;          /* 12  */
	HSA = OTM8009A_480X800_HSYNC;        /* 63  */
	HBP = OTM8009A_480X800_HBP;          /* 120 */
	HFP = OTM8009A_480X800_HFP;          /* 120 */

	hdsivideo_handle.VirtualChannelID = LCD_OTM8009A_ID;
	hdsivideo_handle.ColorCoding = LCD_DSI_PIXEL_DATA_FMT_RBG888;
	hdsivideo_handle.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
	hdsivideo_handle.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
	hdsivideo_handle.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
	hdsivideo_handle.Mode = DSI_VID_MODE_BURST; /* Mode Video burst ie : one LgP per line */
	hdsivideo_handle.NullPacketSize = 0xFFF;
	hdsivideo_handle.NumberOfChunks = 0;
	hdsivideo_handle.PacketSize = HACT; /* Value depending on display orientation choice portrait/landscape */
	hdsivideo_handle.HorizontalSyncActive = (HSA * laneByteClk_kHz) / LcdClock;
	hdsivideo_handle.HorizontalBackPorch = (HBP * laneByteClk_kHz) / LcdClock;
	hdsivideo_handle.HorizontalLine = ((HACT + HSA + HBP + HFP) * laneByteClk_kHz) / LcdClock; /* Value depending on display orientation choice portrait/landscape */
	hdsivideo_handle.VerticalSyncActive = VSA;
	hdsivideo_handle.VerticalBackPorch = VBP;
	hdsivideo_handle.VerticalFrontPorch = VFP;
	hdsivideo_handle.VerticalActive = VACT; /* Value depending on display orientation choice portrait/landscape */

											/* Enable or disable sending LP command while streaming is active in video mode */
	hdsivideo_handle.LPCommandEnable = DSI_LP_COMMAND_ENABLE; /* Enable sending commands in mode LP (Low Power) */

															  /* Largest packet size possible to transmit in LP mode in VSA, VBP, VFP regions */
															  /* Only useful when sending LP packets is allowed while streaming is active in video mode */
	hdsivideo_handle.LPLargestPacketSize = 16;

	/* Largest packet size possible to transmit in LP mode in HFP region during VACT period */
	/* Only useful when sending LP packets is allowed while streaming is active in video mode */
	hdsivideo_handle.LPVACTLargestPacketSize = 0;

	/* Specify for each region of the video frame, if the transmission of command in LP mode is allowed in this region */
	/* while streaming is active in video mode                                                                         */
	hdsivideo_handle.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE;   /* Allow sending LP commands during HFP period */
	hdsivideo_handle.LPHorizontalBackPorchEnable = DSI_LP_HBP_ENABLE;   /* Allow sending LP commands during HBP period */
	hdsivideo_handle.LPVerticalActiveEnable = DSI_LP_VACT_ENABLE;  /* Allow sending LP commands during VACT period */
	hdsivideo_handle.LPVerticalFrontPorchEnable = DSI_LP_VFP_ENABLE;   /* Allow sending LP commands during VFP period */
	hdsivideo_handle.LPVerticalBackPorchEnable = DSI_LP_VBP_ENABLE;   /* Allow sending LP commands during VBP period */
	hdsivideo_handle.LPVerticalSyncActiveEnable = DSI_LP_VSYNC_ENABLE; /* Allow sending LP commands during VSync = VSA period */

																	   /* Configure DSI Video mode timings with settings set above */
	HAL_DSI_ConfigVideoMode(&(hdsi_discovery), &(hdsivideo_handle));

	/*************************End DSI Initialization*******************************/


	/************************LTDC Initialization***********************************/

	hltdc_discovery.Init.HorizontalSync = (HSA - 1);
	hltdc_discovery.Init.AccumulatedHBP = (HSA + HBP - 1);
	hltdc_discovery.Init.AccumulatedActiveW = (lcd_x_size + HSA + HBP - 1);
	hltdc_discovery.Init.TotalWidth = (lcd_x_size + HSA + HBP + HFP - 1);

	/* Initialize the LCD pixel width and pixel height */
	hltdc_discovery.LayerCfg->ImageWidth = lcd_x_size;
	hltdc_discovery.LayerCfg->ImageHeight = lcd_y_size;

	hltdc_discovery.Init.Backcolor.Blue = 0;
	hltdc_discovery.Init.Backcolor.Green = 0;
	hltdc_discovery.Init.Backcolor.Red = 0;
	hltdc_discovery.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	hltdc_discovery.Instance = LTDC;

	/* Get LTDC Configuration from DSI Configuration */
	HAL_LTDC_StructInitFromVideoConfig(&(hltdc_discovery), &(hdsivideo_handle));

	/* Initialize the LTDC */
	//HAL_LTDC_Init(&hltdc_F);
	STM32F7_Display_Initialize(&hltdc_discovery);

	/* Enable the DSI host and wrapper after the LTDC initialization
	To avoid any synchronization issue, the DSI shall be started after enabling the LTDC */
	HAL_DSI_Start(&hdsi_discovery);

	/* Initialize the font */
	//BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/************************End LTDC Initialization*******************************/


	/***********************OTM8009A Initialization********************************/

	/* Initialize the OTM8009A LCD Display IC Driver (KoD LCD IC Driver)
	*  depending on configuration set in 'hdsivideo_handle'.
	*/
	OTM8009A_Init(OTM8009A_FORMAT_RGB888, orientation);

	/***********************End OTM8009A Initialization****************************/

	return LCD_OK;
}

bool HAL_DSI_Start(DSI_HandleTypeDef *hdsi)
{
	/* Process locked */
	//__HAL_LOCK(hdsi);

	/* Enable the DSI host */
	__HAL_DSI_ENABLE(hdsi);

	/* Enable the DSI wrapper */
	__HAL_DSI_WRAPPER_ENABLE(hdsi);

	/* Process unlocked */
	//__HAL_UNLOCK(hdsi);

	return true;
}

/**
* @brief  De-Initializes the BSP LCD Msp
* Application can surcharge if needed this function implementation.
*/
__weak void BSP_LCD_MspDeInit(void)
{

	/** @brief Force and let in reset state LTDC, DMA2D and DSI Host + Wrapper IPs */
	__HAL_RCC_LTDC_FORCE_RESET();
	//__HAL_RCC_DMA2D_FORCE_RESET();
	__HAL_RCC_DSI_FORCE_RESET();

	///** @brief Disable the LTDC, DMA2D and DSI Host and Wrapper clocks */
	__HAL_RCC_LTDC_CLK_DISABLE();
	//__HAL_RCC_DMA2D_CLK_DISABLE();
	__HAL_RCC_DSI_CLK_DISABLE();
}

/**
* @brief  Initialize the BSP LCD Msp.
* Application can surcharge if needed this function implementation
*/
__weak void BSP_LCD_MspInit(void)
{
	/** @brief Enable the LTDC clock */
	__HAL_RCC_LTDC_CLK_ENABLE();

	///** @brief Toggle Sw reset of LTDC IP */
	__HAL_RCC_LTDC_FORCE_RESET();
	__HAL_RCC_LTDC_RELEASE_RESET();

	///** @brief Enable the DMA2D clock */
	//__HAL_RCC_DMA2D_CLK_ENABLE();

	///** @brief Toggle Sw reset of DMA2D IP */
	//__HAL_RCC_DMA2D_FORCE_RESET();
	//__HAL_RCC_DMA2D_RELEASE_RESET();

	///** @brief Enable DSI Host and wrapper clocks */
	__HAL_RCC_DSI_CLK_ENABLE();

	///** @brief Soft Reset the DSI Host and wrapper */
	__HAL_RCC_DSI_FORCE_RESET();
	__HAL_RCC_DSI_RELEASE_RESET();

}

static uint16_t LCD_IO_GetID(void)
{
	// Now it is only for DSI ouput. Can be managed also the case of HDMI chip output with more code
	return LCD_DSI_ID;
}

bool HAL_DSI_DeInit(DSI_HandleTypeDef *hdsi)
{
	/* Check the DSI handle allocation */
	if (hdsi == NULL)
	{
		return false;
	}

	/* Change DSI peripheral state */
	hdsi->State = HAL_DSI_STATE_BUSY;

	/* Disable the DSI wrapper */
	__HAL_DSI_WRAPPER_DISABLE(hdsi);

	/* Disable the DSI host */
	__HAL_DSI_DISABLE(hdsi);

	/* D-PHY clock and digital disable */
	hdsi->Instance->PCTLR &= ~(DSI_PCTLR_CKE | DSI_PCTLR_DEN);

	/* Turn off the DSI PLL */
	__HAL_DSI_PLL_DISABLE(hdsi);

	/* Disable the regulator */
	__HAL_DSI_REG_DISABLE(hdsi);

	/* DeInit the low level hardware */
	//HAL_DSI_MspDeInit(hdsi);

	/* Initialise the error code */
	hdsi->ErrorCode = HAL_DSI_ERROR_NONE;

	/* Initialize the DSI state*/
	hdsi->State = HAL_DSI_STATE_RESET;

	return true;
}

bool HAL_DSI_ConfigVideoMode(DSI_HandleTypeDef *hdsi, DSI_VidCfgTypeDef *VidCfg)
{
	/* Process locked */
	//__HAL_LOCK(hdsi);

	/* Check the LooselyPacked variant only in 18-bit mode */
	if (VidCfg->ColorCoding == DSI_RGB666)
	{
		//assert_param(IS_DSI_LOOSELY_PACKED(VidCfg->LooselyPacked));
	}

	/* Select video mode by resetting CMDM and DSIM bits */
	hdsi->Instance->MCR &= ~DSI_MCR_CMDM;
	hdsi->Instance->WCFGR &= ~DSI_WCFGR_DSIM;

	/* Configure the video mode transmission type */
	hdsi->Instance->VMCR &= ~DSI_VMCR_VMT;
	hdsi->Instance->VMCR |= VidCfg->Mode;

	/* Configure the video packet size */
	hdsi->Instance->VPCR &= ~DSI_VPCR_VPSIZE;
	hdsi->Instance->VPCR |= VidCfg->PacketSize;

	/* Set the chunks number to be transmitted through the DSI link */
	hdsi->Instance->VCCR &= ~DSI_VCCR_NUMC;
	hdsi->Instance->VCCR |= VidCfg->NumberOfChunks;

	/* Set the size of the null packet */
	hdsi->Instance->VNPCR &= ~DSI_VNPCR_NPSIZE;
	hdsi->Instance->VNPCR |= VidCfg->NullPacketSize;

	/* Select the virtual channel for the LTDC interface traffic */
	hdsi->Instance->LVCIDR &= ~DSI_LVCIDR_VCID;
	hdsi->Instance->LVCIDR |= VidCfg->VirtualChannelID;

	/* Configure the polarity of control signals */
	hdsi->Instance->LPCR &= ~(DSI_LPCR_DEP | DSI_LPCR_VSP | DSI_LPCR_HSP);
	hdsi->Instance->LPCR |= (VidCfg->DEPolarity | VidCfg->VSPolarity | VidCfg->HSPolarity);

	/* Select the color coding for the host */
	hdsi->Instance->LCOLCR &= ~DSI_LCOLCR_COLC;
	hdsi->Instance->LCOLCR |= VidCfg->ColorCoding;

	/* Select the color coding for the wrapper */
	hdsi->Instance->WCFGR &= ~DSI_WCFGR_COLMUX;
	hdsi->Instance->WCFGR |= ((VidCfg->ColorCoding) << 1);

	/* Enable/disable the loosely packed variant to 18-bit configuration */
	if (VidCfg->ColorCoding == DSI_RGB666)
	{
		hdsi->Instance->LCOLCR &= ~DSI_LCOLCR_LPE;
		hdsi->Instance->LCOLCR |= VidCfg->LooselyPacked;
	}

	/* Set the Horizontal Synchronization Active (HSA) in lane byte clock cycles */
	hdsi->Instance->VHSACR &= ~DSI_VHSACR_HSA;
	hdsi->Instance->VHSACR |= VidCfg->HorizontalSyncActive;

	/* Set the Horizontal Back Porch (HBP) in lane byte clock cycles */
	hdsi->Instance->VHBPCR &= ~DSI_VHBPCR_HBP;
	hdsi->Instance->VHBPCR |= VidCfg->HorizontalBackPorch;

	/* Set the total line time (HLINE=HSA+HBP+HACT+HFP) in lane byte clock cycles */
	hdsi->Instance->VLCR &= ~DSI_VLCR_HLINE;
	hdsi->Instance->VLCR |= VidCfg->HorizontalLine;

	/* Set the Vertical Synchronization Active (VSA) */
	hdsi->Instance->VVSACR &= ~DSI_VVSACR_VSA;
	hdsi->Instance->VVSACR |= VidCfg->VerticalSyncActive;

	/* Set the Vertical Back Porch (VBP)*/
	hdsi->Instance->VVBPCR &= ~DSI_VVBPCR_VBP;
	hdsi->Instance->VVBPCR |= VidCfg->VerticalBackPorch;

	/* Set the Vertical Front Porch (VFP)*/
	hdsi->Instance->VVFPCR &= ~DSI_VVFPCR_VFP;
	hdsi->Instance->VVFPCR |= VidCfg->VerticalFrontPorch;

	/* Set the Vertical Active period*/
	hdsi->Instance->VVACR &= ~DSI_VVACR_VA;
	hdsi->Instance->VVACR |= VidCfg->VerticalActive;

	/* Configure the command transmission mode */
	hdsi->Instance->VMCR &= ~DSI_VMCR_LPCE;
	hdsi->Instance->VMCR |= VidCfg->LPCommandEnable;

	/* Low power largest packet size */
	hdsi->Instance->LPMCR &= ~DSI_LPMCR_LPSIZE;
	hdsi->Instance->LPMCR |= ((VidCfg->LPLargestPacketSize) << 16);

	/* Low power VACT largest packet size */
	hdsi->Instance->LPMCR &= ~DSI_LPMCR_VLPSIZE;
	hdsi->Instance->LPMCR |= VidCfg->LPVACTLargestPacketSize;

	/* Enable LP transition in HFP period */
	hdsi->Instance->VMCR &= ~DSI_VMCR_LPHFPE;
	hdsi->Instance->VMCR |= VidCfg->LPHorizontalFrontPorchEnable;

	/* Enable LP transition in HBP period */
	hdsi->Instance->VMCR &= ~DSI_VMCR_LPHBPE;
	hdsi->Instance->VMCR |= VidCfg->LPHorizontalBackPorchEnable;

	/* Enable LP transition in VACT period */
	hdsi->Instance->VMCR &= ~DSI_VMCR_LPVAE;
	hdsi->Instance->VMCR |= VidCfg->LPVerticalActiveEnable;

	/* Enable LP transition in VFP period */
	hdsi->Instance->VMCR &= ~DSI_VMCR_LPVFPE;
	hdsi->Instance->VMCR |= VidCfg->LPVerticalFrontPorchEnable;

	/* Enable LP transition in VBP period */
	hdsi->Instance->VMCR &= ~DSI_VMCR_LPVBPE;
	hdsi->Instance->VMCR |= VidCfg->LPVerticalBackPorchEnable;

	/* Enable LP transition in vertical sync period */
	hdsi->Instance->VMCR &= ~DSI_VMCR_LPVSAE;
	hdsi->Instance->VMCR |= VidCfg->LPVerticalSyncActiveEnable;

	/* Enable the request for an acknowledge response at the end of a frame */
	hdsi->Instance->VMCR &= ~DSI_VMCR_FBTAAE;
	hdsi->Instance->VMCR |= VidCfg->FrameBTAAcknowledgeEnable;

	/* Process unlocked */
	//__HAL_UNLOCK(hdsi);

	return true;
}

bool HAL_LTDC_StructInitFromVideoConfig(LTDC_HandleTypeDef* hltdc, DSI_VidCfgTypeDef *VidCfg)
{
	/* Retrieve signal polarities from DSI */

	/* The following polarity is inverted:
	LTDC_DEPOLARITY_AL <-> LTDC_DEPOLARITY_AH */

	/* Note 1 : Code in line w/ Current LTDC specification */
	hltdc->Init.DEPolarity = (VidCfg->DEPolarity == DSI_DATA_ENABLE_ACTIVE_HIGH) ? LTDC_DEPOLARITY_AL : LTDC_DEPOLARITY_AH;
	hltdc->Init.VSPolarity = (VidCfg->VSPolarity == DSI_VSYNC_ACTIVE_HIGH) ? LTDC_VSPOLARITY_AH : LTDC_VSPOLARITY_AL;
	hltdc->Init.HSPolarity = (VidCfg->HSPolarity == DSI_HSYNC_ACTIVE_HIGH) ? LTDC_HSPOLARITY_AH : LTDC_HSPOLARITY_AL;

	/* Note 2: Code to be used in case LTDC polarities inversion updated in the specification */
	/* hltdc->Init.DEPolarity = VidCfg->DEPolarity << 29;
	hltdc->Init.VSPolarity = VidCfg->VSPolarity << 29;
	hltdc->Init.HSPolarity = VidCfg->HSPolarity << 29; */

	/* Retrieve vertical timing parameters from DSI */
	hltdc->Init.VerticalSync = VidCfg->VerticalSyncActive - 1;
	hltdc->Init.AccumulatedVBP = VidCfg->VerticalSyncActive + VidCfg->VerticalBackPorch - 1;
	hltdc->Init.AccumulatedActiveH = VidCfg->VerticalSyncActive + VidCfg->VerticalBackPorch + VidCfg->VerticalActive - 1;
	hltdc->Init.TotalHeigh = VidCfg->VerticalSyncActive + VidCfg->VerticalBackPorch + VidCfg->VerticalActive + VidCfg->VerticalFrontPorch - 1;

	return true;
}

void DSI_IO_WriteCmd(uint32_t NbrParams, uint8_t *pParams)
{
	if (NbrParams <= 1)
	{
		HAL_DSI_ShortWrite(&hdsi_discovery, LCD_OTM8009A_ID, DSI_DCS_SHORT_PKT_WRITE_P1, pParams[0], pParams[1]);
  }
	else
	{
		HAL_DSI_LongWrite(&hdsi_discovery, LCD_OTM8009A_ID, DSI_DCS_LONG_PKT_WRITE, NbrParams, pParams[NbrParams], pParams);
	}
}

bool HAL_DSI_ShortWrite(DSI_HandleTypeDef *hdsi,
	uint32_t ChannelID,
	uint32_t Mode,
	uint32_t Param1,
	uint32_t Param2)
{
	uint32_t tickstart = 0;

	/* Process locked */
	//__HAL_LOCK(hdsi);


	/* Get tick */
	tickstart = 0; //HAL_GetTick();

	/* Wait for Command FIFO Empty */
	while ((hdsi->Instance->GPSR & DSI_GPSR_CMDFE) == 0);

	/* Configure the packet to send a short DCS command with 0 or 1 parameter */
	DSI_ConfigPacketHeader(hdsi->Instance,
		ChannelID,
		Mode,
		Param1,
		Param2);

	/* Process unlocked */
	//__HAL_UNLOCK(hdsi);

	return true;
}

bool HAL_DSI_LongWrite(DSI_HandleTypeDef *hdsi,
	uint32_t ChannelID,
	uint32_t Mode,
	uint32_t NbParams,
	uint32_t Param1,
	uint8_t* ParametersTable)
{
	uint32_t uicounter = 0;
	uint32_t tickstart = 0;

	/* Process locked */
	//__HAL_LOCK(hdsi);
	/* Get tick */
	tickstart = 0; // HAL_GetTick();

	/* Wait for Command FIFO Empty */
	while ((hdsi->Instance->GPSR & DSI_GPSR_CMDFE) == RESET);

	/* Set the DCS code hexadecimal on payload byte 1, and the other parameters on the write FIFO command*/
	while (uicounter < NbParams)
	{
		if (uicounter == 0x00)
		{
			hdsi->Instance->GPDR = (Param1 | \
				((uint32_t)(*(ParametersTable + uicounter)) << 8) | \
				((uint32_t)(*(ParametersTable + uicounter + 1)) << 16) | \
				((uint32_t)(*(ParametersTable + uicounter + 2)) << 24));
			uicounter += 3;
		}
		else
		{
			hdsi->Instance->GPDR = ((uint32_t)(*(ParametersTable + uicounter)) | \
				((uint32_t)(*(ParametersTable + uicounter + 1)) << 8) | \
				((uint32_t)(*(ParametersTable + uicounter + 2)) << 16) | \
				((uint32_t)(*(ParametersTable + uicounter + 3)) << 24));
			uicounter += 4;
		}
	}

	/* Configure the packet to send a long DCS command */
	DSI_ConfigPacketHeader(hdsi->Instance,
		ChannelID,
		Mode,
		((NbParams + 1) & 0x00FF),
		(((NbParams + 1) & 0xFF00) >> 8));

	/* Process unlocked */
	//__HAL_UNLOCK(hdsi);

	return true;
}


static void DSI_ConfigPacketHeader(DSI_TypeDef *DSIx,
	uint32_t ChannelID,
	uint32_t DataType,
	uint32_t Data0,
	uint32_t Data1)
{
	/* Update the DSI packet header with new information */
	DSIx->GHCR = (DataType | (ChannelID << 6) | (Data0 << 8) | (Data1 << 16));
}

void OTM8009A_IO_Delay(uint32_t Delay) {
	STM32F7_Time_Delay(nullptr, Delay * 1000);
}

#endif //INCLUDE_DISPLAY_DSI
