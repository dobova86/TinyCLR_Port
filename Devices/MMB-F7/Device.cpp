#include "Device.h"
#include "../../Drivers/UsbClient/UsbClient.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"

extern TinyCLR_Api_Info* Mikroe_TinyCLR_MMB_GetApi();

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider, const TinyCLR_Interop_Provider* interopProvider) {

	apiProvider->Add(apiProvider, Mikroe_TinyCLR_MMB_GetApi());
	interopProvider->Add(interopProvider, &Interop_GHIElectronics_TinyCLR_Devices);

}
