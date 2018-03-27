#include "Device.h"
#include "..\..\Drivers\ISIS42S164_sdram\ISIS42S164_sdram.h"
#include "../../Drivers/SPIDisplay/SPIDisplay.h"
//extern void STM32F4_DebugLed();

void STM32F4_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider) {
	//apiProvider->Add(apiProvider, SPIDisplay_GetApi());
}

