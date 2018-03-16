
/*

GENERAL DISPLAY DSI for DISCOVERY-F769NI DEFINES

*/

#define STM32F769xx	 

#include <inc/stm32f7xx.h>
#include "otm8009a.h"

#define MAX_LAYER  2

//// Implementations
//
//bool HAL_DSI_ConfigVideoMode(DSI_HandleTypeDef *hdsi, DSI_VidCfgTypeDef *VidCfg);
//bool HAL_DSI_ConfigAdaptedCommandMode(DSI_HandleTypeDef *hdsi, DSI_CmdCfgTypeDef *CmdCfg);
//bool HAL_DSI_ConfigCommand(DSI_HandleTypeDef *hdsi, DSI_LPCmdTypeDef *LPCmd);
//bool HAL_DSI_Init(DSI_HandleTypeDef *hdsi, DSI_PLLInitTypeDef *PLLInit);
//void BSP_LCD_Reset(void);
//static uint16_t LCD_IO_GetID(void);
//void BSP_LCD_MspInit(void);
//bool BSP_DSI_Deinit(DSI_HandleTypeDef *hdsi);
//bool HAL_DSI_DeInit(DSI_HandleTypeDef *hdsi);
//bool HAL_LTDC_StructInitFromVideoConfig(LTDC_HandleTypeDef* hltdc, DSI_VidCfgTypeDef *VidCfg);
//
//****************************

/*
DISPLAY Api for Discovery F769NI, with DSI (HDMI) attached display
*/

void STM32F7_Display_Reset();
const TinyCLR_Api_Info* STM32F7_DsiDisplay_GetApi();
TinyCLR_Result STM32F7_DsiDisplay_Acquire(const TinyCLR_Display_Provider* self);
TinyCLR_Result STM32F7_DsiDisplay_Release(const TinyCLR_Display_Provider* self);
TinyCLR_Result STM32F7_DsiDisplay_Enable(const TinyCLR_Display_Provider* self);
TinyCLR_Result STM32F7_DsiDisplay_Disable(const TinyCLR_Display_Provider* self);
TinyCLR_Result STM32F7_DsiDisplay_GetCapabilities(const TinyCLR_Display_Provider* self, TinyCLR_Display_InterfaceType& type, const TinyCLR_Display_DataFormat*& supportedDataFormats, size_t& supportedDataFormatCount);
TinyCLR_Result STM32F7_DsiDisplay_GetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat& dataFormat, uint32_t& width, uint32_t& height, void* configuration);
TinyCLR_Result STM32F7_DsiDisplay_SetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat dataFormat, uint32_t width, uint32_t height, const void* configuration);
TinyCLR_Result STM32F7_DsiDisplay_DrawBuffer(const TinyCLR_Display_Provider* self, int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t* data);
TinyCLR_Result STM32F7_DsiDisplay_WriteString(const TinyCLR_Display_Provider* self, const char* buffer, size_t length);
