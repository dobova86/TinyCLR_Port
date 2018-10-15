#include <TinyCLR.h>
#include "Device.h"
#include "../../Drivers/UsbClient/UsbClient.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_InteropUtil.h"

extern void SDRAM_Init(uint8_t databits);
extern void STM32F7_Display_Initialize(void);

#ifdef INCLUDE_DISPLAY_DSI
extern TinyCLR_Api_Info* STM32F7_DsiDisplay_GetApi();
#endif

extern "C" {
	extern int HeapBegin;
}

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Manager* apiProvider, const TinyCLR_Interop_Manager* interopManager) {

	//STM32F7_DebugLed(LED_DEBUG, true);	
	DevicesInterop_Add(interopManager);
	//STM32F7_Display_Enable((TinyCLR_Display_Controller*)apiProvider);

#ifdef INCLUDE_DISPLAY_DSI
	apiProvider->Add(apiProvider, STM32F7_DsiDisplay_GetApi());
#pragma message "Using DSI Display interface"
#endif

}

void STM32F7_Startup_MpuConfiguration() {
#ifdef USE_SDRAM_HEAP
	STM32F7_Mpu_Configuration(reinterpret_cast<uint32_t>(reinterpret_cast<uint32_t*>(&HeapBegin)), STM32F7_Mpu_RegionSize::Size_32MBytes, STM32F7_Mpu_RegionNumber::Region0, true);
#endif
}
