#pragma once

#include <TinyCLR.h>

#define LCD_CS_PIN	PIN(C, 2)
#define LCD_WRX_PIN	PIN(D,13)
#define LCD_RDX_PIN PIN(D,12)

/*################################ LCD #######################################*/
/* Chip Select macro definition */
#define LCD_CS_LOW()       STM32F4_GpioInternal_WritePin(LCD_CS_PIN, false)
#define LCD_CS_HIGH()      STM32F4_GpioInternal_WritePin(LCD_CS_PIN, true)

/* Set WRX High to send data */
#define LCD_WRX_LOW()      STM32F4_GpioInternal_WritePin(LCD_WRX_PIN, false)
#define LCD_WRX_HIGH()     STM32F4_GpioInternal_WritePin(LCD_WRX_PIN, true)

/* Set RDX High to send data */
#define LCD_RDX_LOW()      STM32F4_GpioInternal_WritePin(LCD_RDX_PIN, false)
#define LCD_RDX_HIGH()     STM32F4_GpioInternal_WritePin(LCD_RDX_PIN, true)



const TinyCLR_Api_Info* SPIDisplay_GetApi();
TinyCLR_Result SPIDisplay_Acquire(const TinyCLR_Display_Provider* self, int32_t controller);
TinyCLR_Result SPIDisplay_Release(const TinyCLR_Display_Provider* self, int32_t controller);
TinyCLR_Result SPIDisplay_Enable(const TinyCLR_Display_Provider* self);
TinyCLR_Result SPIDisplay_Disable(const TinyCLR_Display_Provider* self);
TinyCLR_Result SPIDisplay_GetCapabilities(const TinyCLR_Display_Provider* self, TinyCLR_Display_InterfaceType& type, const TinyCLR_Display_DataFormat*& supportedDataFormats, size_t& supportedDataFormatCount);
TinyCLR_Result SPIDisplay_GetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat& dataFormat, int32_t& width, int32_t& height, void* configuration);
TinyCLR_Result SPIDisplay_SetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat dataFormat, int32_t width, int32_t height, const void* configuration);
TinyCLR_Result SPIDisplay_DrawBuffer(const TinyCLR_Display_Provider* self, int32_t controller, int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t* data);
TinyCLR_Result SPIDisplay_WriteString(const TinyCLR_Display_Provider* self, const char* buffer, size_t length);
