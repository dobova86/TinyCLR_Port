#include <TinyCLR.h>
#include "Device.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_InteropUtil.h"

//extern void STM32F7_WriteHello(void);
extern TinyCLR_Api_Info* STM32F7_DsiDisplay_GetApi();

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Manager* apiProvider, const TinyCLR_Interop_Manager* interopManager) {

	DevicesInterop_Add(interopManager);

	//interopProvider->Add(interopProvider, &Interop_GHIElectronics_TinyCLR_Devices);


}
