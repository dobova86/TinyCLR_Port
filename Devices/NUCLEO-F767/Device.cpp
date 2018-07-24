#include <TinyCLR.h>
#include "Device.h"
#include "../../Drivers/UsbClient/UsbClient.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"

extern void SDRAM_Init(uint8_t databits);
extern void STM32F7_Display_Initialize(void);
//extern void STM32F7_WriteHello(void);
extern TinyCLR_Api_Info* STM32F7_DsiDisplay_GetApi();

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider, const TinyCLR_Interop_Provider* interopProvider) {

//#ifdef SDRAM_32BIT // Init SDRAM
//	SDRAM_Init(32);
//#endif

	interopProvider->Add(interopProvider, &Interop_GHIElectronics_TinyCLR_Devices);


#ifdef INCLUDE_DISPLAY_DSI
	apiProvider->Add(apiProvider, STM32F7_DsiDisplay_GetApi());
	apiProvider->SetDefaultSelector(apiProvider, TinyCLR_Api_Type::DisplayProvider, STM32F7_DsiDisplay_GetApi()->Name);
#pragma message "Using DSI Display interface"
#endif

}
