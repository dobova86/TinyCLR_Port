#include <TinyCLR.h>
#include "Device.h"
#include "../../Drivers/UsbClient/UsbClient.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"

//extern void SDRAM_Init(uint8_t databits);
//extern void STM32H7_Display_Initialize(void);
//extern void STM32F7_WriteHello(void);
//extern TinyCLR_Api_Info* STM32H7_DsiDisplay_GetApi();

void STM32H7_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider, const TinyCLR_Interop_Provider* interopProvider) {

	interopProvider->Add(interopProvider, &Interop_GHIElectronics_TinyCLR_Devices);


#ifdef INCLUDE_DISPLAY_DSI
	apiProvider->Add(apiProvider, STM32H7_DsiDisplay_GetApi());
	apiProvider->SetDefaultSelector(apiProvider, TinyCLR_Api_Type::DisplayProvider, STM32H7_DsiDisplay_GetApi()->Name);
#pragma message "Using DSI Display interface"
#endif

}
