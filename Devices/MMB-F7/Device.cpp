#include "Device.h"
#include "../../Drivers/UsbClient/UsbClient.h"
//#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices.h"
//#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_InteropUtil.h"

extern TinyCLR_Api_Info* Mikroe_TinyCLR_MMB_GetApi();

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Manager* apiProvider, const TinyCLR_Interop_Manager* interopManager) {

	DevicesInterop_Add(interopManager);

	
	//apiProvider->Add(apiProvider, Mikroe_TinyCLR_MMB_GetApi());
	//interopManager->Add(interopProvider, &Interop_GHIElectronics_TinyCLR_Devices);

}
