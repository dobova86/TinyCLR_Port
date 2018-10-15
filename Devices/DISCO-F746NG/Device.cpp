#include "Device.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_InteropUtil.h"

//extern void STM32F7_Display_Initialize(void);
//extern void STM32F7_WriteHello(void);

extern "C" {
	extern int HeapBegin;
}



void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Manager* apiProvider, const TinyCLR_Interop_Manager* interopManager) {
	
	STM32F7_DebugLed(LED_DEBUG, true);	
	DevicesInterop_Add(interopManager);
	//STM32F7_Display_Enable((TinyCLR_Display_Controller*)apiProvider);

}

void STM32F7_Startup_MpuConfiguration() {
	//STM32F7_Mpu_Configuration(reinterpret_cast<uint32_t>(reinterpret_cast<uint32_t*>(&HeapBegin)), STM32F7_Mpu_RegionSize::Size_32MBytes, STM32F7_Mpu_RegionNumber::Region0, true);
}
