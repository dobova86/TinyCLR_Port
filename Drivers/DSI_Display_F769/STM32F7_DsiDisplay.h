/*
GENERAL DISPLAY DSI for DISCOVERY-F769NI DEFINES
*/

#include "otm8009a.h"

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
