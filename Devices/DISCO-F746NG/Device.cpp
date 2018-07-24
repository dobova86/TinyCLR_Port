#include "Device.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"

extern void SDRAM_Init(uint8_t databits);
extern void STM32F7_Display_Initialize(void);
extern void STM32F7_WriteHello(void);

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider, const TinyCLR_Interop_Provider* interopProvider) {
	//SDRAM_Init(SDRAM_BIT);
	//STM32F7_Display_Enable((TinyCLR_Display_Provider*)apiProvider);
	//STM32F7_WriteHello();
	interopProvider->Add(interopProvider, &Interop_GHIElectronics_TinyCLR_Devices);
}
