
#include <STM32F4.h>
#include "SPIDisplay.h"
#include "ili9341.h"


extern bool STM32F4_GpioInternal_ConfigurePin(int32_t pin, STM32F4_Gpio_PortMode portMode, STM32F4_Gpio_OutputType outputType, STM32F4_Gpio_OutputSpeed outputSpeed, STM32F4_Gpio_PullDirection pullDirection, STM32F4_Gpio_AlternateFunction alternateFunction);
extern void STM32F4_GpioInternal_WritePin(int32_t pin, bool value);

extern const TinyCLR_Api_Provider* apiProvider;
extern void STM32F4_Time_Delay(const TinyCLR_NativeTime_Provider* self, uint64_t microseconds);

static TinyCLR_Display_Provider spiDisplayProvider;
static TinyCLR_Api_Info spiDisplayApi;
static TinyCLR_Display_DataFormat spiDisplayDataFormats[] = { TinyCLR_Display_DataFormat::Rgb565 };
static int32_t spiDisplayWidth = 0;
static int32_t spiDisplayHeight = 0;
static TinyCLR_Display_SpiConfiguration spiDisplayConfig;
static const TinyCLR_Spi_Provider* spiDisplayBus;

const TinyCLR_Api_Info* SPIDisplay_GetApi() {
    spiDisplayProvider.Parent = &spiDisplayApi;
    spiDisplayProvider.Acquire = &SPIDisplay_Acquire;
    spiDisplayProvider.Release = &SPIDisplay_Release;
    spiDisplayProvider.Enable = &SPIDisplay_Enable;
    spiDisplayProvider.Disable = &SPIDisplay_Disable;
    spiDisplayProvider.SetConfiguration = &SPIDisplay_SetConfiguration;
    spiDisplayProvider.GetConfiguration = &SPIDisplay_GetConfiguration;
    spiDisplayProvider.GetCapabilities = &SPIDisplay_GetCapabilities;
    spiDisplayProvider.DrawBuffer = &SPIDisplay_DrawBuffer;
    spiDisplayProvider.WriteString = &SPIDisplay_WriteString;

    spiDisplayApi.Author = "GHI Electronics, LLC";
    spiDisplayApi.Name = "GHIElectronics.TinyCLR.NativeApis.Drivers.SPIDisplay";
    spiDisplayApi.Type = TinyCLR_Api_Type::DisplayProvider;
    spiDisplayApi.Version = 0;
    //spiDisplayApi.Count = 1;
    spiDisplayApi.Implementation = &spiDisplayProvider;

    return &spiDisplayApi;
}

void SPIDisplay_Initialize()
{
	// Setup LCD PINS
	STM32F4_GpioInternal_ConfigurePin( PIN(C, 2), STM32F4_Gpio_PortMode::GeneralPurposeOutput, STM32F4_Gpio_OutputType::PushPull, STM32F4_Gpio_OutputSpeed::High, STM32F4_Gpio_PullDirection::None, AF(0));
	STM32F4_GpioInternal_ConfigurePin( PIN(D,13), STM32F4_Gpio_PortMode::GeneralPurposeOutput, STM32F4_Gpio_OutputType::PushPull, STM32F4_Gpio_OutputSpeed::High, STM32F4_Gpio_PullDirection::None, AF(0));
	STM32F4_GpioInternal_ConfigurePin( PIN(D,12), STM32F4_Gpio_PortMode::GeneralPurposeOutput, STM32F4_Gpio_OutputType::PushPull, STM32F4_Gpio_OutputSpeed::High, STM32F4_Gpio_PullDirection::None, AF(0));

	STM32F4_GpioInternal_WritePin(PIN(C, 2), true);
	STM32F4_GpioInternal_WritePin(PIN(D,13), false);
	STM32F4_GpioInternal_WritePin(PIN(D,12), false);

	ili9341_Init();
}

TinyCLR_Result SPIDisplay_Acquire(const TinyCLR_Display_Provider* self, int32_t controller) {
    return TinyCLR_Result::Success;
}

TinyCLR_Result SPIDisplay_Release(const TinyCLR_Display_Provider* self, int32_t controller) {
    return TinyCLR_Result::Success;
}

TinyCLR_Result SPIDisplay_Enable(const TinyCLR_Display_Provider* self) {
    spiDisplayBus = reinterpret_cast<const TinyCLR_Spi_Provider*>(apiProvider->FindBySelector(apiProvider, spiDisplayConfig.SpiSelector, TinyCLR_Api_Type::SpiProvider));

	if ( spiDisplayBus != nullptr )
		SPIDisplay_Initialize();

	//LCD_WRX_HIGH();

    return spiDisplayBus != nullptr ? TinyCLR_Result::Success : TinyCLR_Result::InvalidOperation;
}

TinyCLR_Result SPIDisplay_Disable(const TinyCLR_Display_Provider* self) {
    spiDisplayBus = nullptr;

    return TinyCLR_Result::Success;
}

TinyCLR_Result SPIDisplay_WriteString(const TinyCLR_Display_Provider* self, const char* buffer, size_t length) {
    return TinyCLR_Result::NotSupported;
}

TinyCLR_Result SPIDisplay_GetCapabilities(const TinyCLR_Display_Provider* self, TinyCLR_Display_InterfaceType& type, const TinyCLR_Display_DataFormat*& supportedDataFormats, size_t& supportedDataFormatCount) {
    type = TinyCLR_Display_InterfaceType::Spi;
    supportedDataFormatCount = sizeof(spiDisplayDataFormats) / sizeof(spiDisplayDataFormats[0]);
    supportedDataFormats = spiDisplayDataFormats;

    return TinyCLR_Result::Success;
}

TinyCLR_Result SPIDisplay_GetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat& dataFormat, int32_t& width, int32_t& height, void* configuration) {
    dataFormat = TinyCLR_Display_DataFormat::Rgb565;
    width = spiDisplayWidth;
    height = spiDisplayHeight;

    if (configuration != nullptr)
        reinterpret_cast<TinyCLR_Display_SpiConfiguration*>(configuration)->SpiSelector = spiDisplayConfig.SpiSelector;

    return TinyCLR_Result::Success;
}

TinyCLR_Result SPIDisplay_SetConfiguration(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat dataFormat, int32_t width, int32_t height, const void* configuration) {
    if (dataFormat != TinyCLR_Display_DataFormat::Rgb565) return TinyCLR_Result::NotSupported;


    spiDisplayWidth = width;
    spiDisplayHeight = height;

    if (configuration != nullptr)
        spiDisplayConfig.SpiSelector = reinterpret_cast<const TinyCLR_Display_SpiConfiguration*>(configuration)->SpiSelector;

	//SPIDisplay_Initialize();

    return TinyCLR_Result::Success;
}

static void Swap(uint8_t* a, uint8_t* b) {
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

TinyCLR_Result SPIDisplay_DrawBuffer(const TinyCLR_Display_Provider* self, int32_t controller, int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t* data) {
    auto d = const_cast<uint8_t*>(data);

    for (auto i = 0; i < spiDisplayWidth * spiDisplayHeight * 2; i += 2)
        Swap(d + i, d + i + 1);

    if (x == 0 && spiDisplayWidth == width) {
        auto len = static_cast<size_t>(width * height * 2);

        spiDisplayBus->Write(spiDisplayBus, data + (y * spiDisplayWidth * 2), len);
    }
    else {
        auto len = static_cast<size_t>(width * 2);

        for (auto yy = y; yy < y + height; yy++)
            spiDisplayBus->Write(spiDisplayBus, data + (yy * spiDisplayWidth * 2) + (x * 2), len);
    }

    for (auto i = 0; i < (spiDisplayWidth * spiDisplayHeight * 2); i += 2)
        Swap(d + i, d + i + 1);

    return TinyCLR_Result::Success;
}

/************************************************************************************************
	Utility for LCD setup and r/w
*/

/**
* @brief  Writes register value.
*/
void LCD_IO_WriteData(uint16_t RegValue)
{
	size_t len = 1;
	uint8_t reg_buffer[2]{ 0, 0 }; // = RegValue & 0x00FF;
	reg_buffer[0] = RegValue & 0x00FF;
	reg_buffer[1] = (RegValue & 0xFF00) >> 8;

	/* Set WRX to send data */
	LCD_WRX_HIGH();
	/* Reset LCD control line(/CS) and Send data */
	LCD_CS_LOW();

	spiDisplayBus->Write(spiDisplayBus, &reg_buffer[0], len);
	if ( reg_buffer[1] != 0)
		spiDisplayBus->Write(spiDisplayBus, &(reg_buffer[1]), len);
	/* Deselect: Chip Select high */
	LCD_CS_HIGH();
}

/**
* @brief  Writes register address.
*/
void LCD_IO_WriteReg(uint8_t Reg)
{
	size_t len = 1;
	/* Reset WRX to send command */
	LCD_WRX_LOW();
	/* Reset LCD control line(/CS) and Send command */
	LCD_CS_LOW();

	spiDisplayBus->Write(spiDisplayBus, &Reg, len);
	/* Deselect: Chip Select high */
	LCD_CS_HIGH();
}

/**
* @brief  Reads register value.
* @param  RegValue Address of the register to read
* @param  ReadSize Number of bytes to read
* @retval Content of the register value
*/
uint32_t LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
	uint32_t readvalue = 0;
	uint8_t buffer[ReadSize];
	uint8_t reg_buffer[2];
	size_t len = 2, rd_len = ReadSize;


	/* Select: Chip Select low */
	LCD_CS_LOW();

	/* Reset WRX to send command */
	LCD_WRX_LOW();
	
	reg_buffer[0] = RegValue & 0x00FF;
	reg_buffer[1] = (RegValue & 0xFF00) >> 8;

	spiDisplayBus->Write(spiDisplayBus, reg_buffer, len); // 16bit register address
	spiDisplayBus->Read(spiDisplayBus, buffer, rd_len);
	readvalue = buffer[0];

	/* Set WRX to send data */
	LCD_WRX_HIGH();

	/* Deselect: Chip Select high */
	LCD_CS_HIGH();

	return readvalue;
}

void LCD_Delay(uint32_t delay) {
	STM32F4_Time_Delay(nullptr, delay * 1000);
}

void ili9341_Init(void)
{
	/* Initialize ILI9341 low level bus layer ----------------------------------*/
	//LCD_IO_Init();
	LCD_CS_LOW();
	LCD_CS_HIGH();

	/* Configure LCD */
	ili9341_WriteReg(0xCA);
	ili9341_WriteData(0xC3);
	ili9341_WriteData(0x08);
	ili9341_WriteData(0x50);
	ili9341_WriteReg(LCD_POWERB);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0xC1);
	ili9341_WriteData(0x30);
	ili9341_WriteReg(LCD_POWER_SEQ);
	ili9341_WriteData(0x64);
	ili9341_WriteData(0x03);
	ili9341_WriteData(0x12);
	ili9341_WriteData(0x81);
	ili9341_WriteReg(LCD_DTCA);
	ili9341_WriteData(0x85);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x78);
	ili9341_WriteReg(LCD_POWERA);
	ili9341_WriteData(0x39);
	ili9341_WriteData(0x2C);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x34);
	ili9341_WriteData(0x02);
	ili9341_WriteReg(LCD_PRC);
	ili9341_WriteData(0x20);
	ili9341_WriteReg(LCD_DTCB);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteReg(LCD_FRMCTR1);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x1B);
	ili9341_WriteReg(LCD_DFC);
	ili9341_WriteData(0x0A);
	ili9341_WriteData(0xA2);
	ili9341_WriteReg(LCD_POWER1);
	ili9341_WriteData(0x10);
	ili9341_WriteReg(LCD_POWER2);
	ili9341_WriteData(0x10);
	ili9341_WriteReg(LCD_VCOM1);
	ili9341_WriteData(0x45);
	ili9341_WriteData(0x15);
	ili9341_WriteReg(LCD_VCOM2);
	ili9341_WriteData(0x90);
	ili9341_WriteReg(LCD_MAC);
	ili9341_WriteData(0xC8);
	ili9341_WriteReg(LCD_3GAMMA_EN);
	ili9341_WriteData(0x00);
	ili9341_WriteReg(LCD_RGB_INTERFACE);
	ili9341_WriteData(0xC2);
	ili9341_WriteReg(LCD_DFC);
	ili9341_WriteData(0x0A);
	ili9341_WriteData(0xA7);
	ili9341_WriteData(0x27);
	ili9341_WriteData(0x04);

	/* Colomn address set */
	ili9341_WriteReg(LCD_COLUMN_ADDR);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0xEF);
	/* Page address set */
	ili9341_WriteReg(LCD_PAGE_ADDR);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x01);
	ili9341_WriteData(0x3F);
	ili9341_WriteReg(LCD_INTERFACE);
	ili9341_WriteData(0x01);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x06);

	ili9341_WriteReg(LCD_GRAM);
	LCD_Delay(200);

	ili9341_WriteReg(LCD_GAMMA);
	ili9341_WriteData(0x01);

	ili9341_WriteReg(LCD_PGAMMA);
	ili9341_WriteData(0x0F);
	ili9341_WriteData(0x29);
	ili9341_WriteData(0x24);
	ili9341_WriteData(0x0C);
	ili9341_WriteData(0x0E);
	ili9341_WriteData(0x09);
	ili9341_WriteData(0x4E);
	ili9341_WriteData(0x78);
	ili9341_WriteData(0x3C);
	ili9341_WriteData(0x09);
	ili9341_WriteData(0x13);
	ili9341_WriteData(0x05);
	ili9341_WriteData(0x17);
	ili9341_WriteData(0x11);
	ili9341_WriteData(0x00);
	ili9341_WriteReg(LCD_NGAMMA);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x16);
	ili9341_WriteData(0x1B);
	ili9341_WriteData(0x04);
	ili9341_WriteData(0x11);
	ili9341_WriteData(0x07);
	ili9341_WriteData(0x31);
	ili9341_WriteData(0x33);
	ili9341_WriteData(0x42);
	ili9341_WriteData(0x05);
	ili9341_WriteData(0x0C);
	ili9341_WriteData(0x0A);
	ili9341_WriteData(0x28);
	ili9341_WriteData(0x2F);
	ili9341_WriteData(0x0F);

	ili9341_WriteReg(LCD_SLEEP_OUT);
	LCD_Delay(200);
	ili9341_WriteReg(LCD_DISPLAY_ON);
	/* GRAM start writing */
	ili9341_WriteReg(LCD_GRAM);
}

void ili9341_DisplayOn(void)
{
	/* Display On */
	ili9341_WriteReg(LCD_DISPLAY_ON);
}

/**
* @brief  Disables the Display.
* @param  None
* @retval None
*/
void ili9341_DisplayOff(void)
{
	/* Display Off */
	ili9341_WriteReg(LCD_DISPLAY_OFF);
}

/**
* @brief  Writes  to the selected LCD register.
* @param  LCD_Reg: address of the selected register.
* @retval None
*/
void ili9341_WriteReg(uint8_t LCD_Reg)
{
	LCD_IO_WriteReg(LCD_Reg);
}

/**
* @brief  Writes data to the selected LCD register.
* @param  LCD_Reg: address of the selected register.
* @retval None
*/
void ili9341_WriteData(uint16_t RegValue)
{
	LCD_IO_WriteData(RegValue);
}

/**
* @brief  Reads the selected LCD Register.
* @param  RegValue: Address of the register to read
* @param  ReadSize: Number of bytes to read
* @retval LCD Register Value.
*/
uint32_t ili9341_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
	/* Read a max of 4 bytes */
	return (LCD_IO_ReadData(RegValue, ReadSize));
}
