#include "Device.h"
//#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices.h"
//#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_InteropUtil.h"

//extern void STM32F7_Display_Initialize(void);
//extern void STM32F7_WriteHello(void);

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Manager* apiProvider, const TinyCLR_Interop_Manager* interopManager) {
	
	STM32F7_DebugLed(LED_DEBUG, true);	
	DevicesInterop_Add(interopManager);
	//STM32F7_Display_Enable((TinyCLR_Display_Controller*)apiProvider);

}

