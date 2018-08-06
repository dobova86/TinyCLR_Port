#include "Device.h"
#include "../../Drivers/SPIDisplay/SPIDisplay.h"
#include "../../Drivers/UsbClient/UsbClient.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"
#include "../../Drivers/ISIS42S164_sdram/ISIS42S164_sdram.h"
//#include "../../Drivers/SPI_F429_Display/SPIDisplay.h"

extern void STM32F4_DebugLed(uint16_t pin, bool onoff);

void STM32F4_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider,  const TinyCLR_Interop_Provider* interopProvider) {

	interopProvider->Add(interopProvider, &Interop_GHIElectronics_TinyCLR_Devices);

#ifdef INCLUDE_DISPLAY
	apiProvider->Add(apiProvider, SPIDisplay_GetApi());
	//apiProvider->SetDefaultSelector(apiProvider, TinyCLR_Api_Type::DisplayProvider, SPIDisplay_GetApi()->Name);
#endif
}

