#include "Device.h"
#include "../../Drivers/DevicesInterop/GHIElectronics_TinyCLR_InteropUtil.h"

extern "C" {
	extern int HeapBegin;
	extern uint32_t Image$$ER_RAM_RW$$Base;
	extern uint32_t __Vectors;
}

extern void SWO_PrintString(const char *s, uint8_t portNumber);

//extern void STM32F7_Display_Initialize(void);
//extern void STM32F7_WriteHello(void);

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Manager* apiProvider, const TinyCLR_Interop_Manager* interopManager) {
	
	SWO_PrintString("SoftResetDevice INIT\r\n", SWO_PORT);
	DevicesInterop_Add(interopManager);
	//STM32F7_Display_Enable((TinyCLR_Display_Controller*)apiProvider);
	SWO_PrintString("SoftResetDevice END\r\n", SWO_PORT);
}

void STM32F7_Startup_MpuConfiguration() {
	STM32F7_Mpu_Configuration(reinterpret_cast<uint32_t>(&__Vectors), STM32F7_Mpu_RegionSize::Size_64KBytes, STM32F7_Mpu_RegionNumber::Region0, true);
	STM32F7_Mpu_Configuration(reinterpret_cast<uint32_t>(&Image$$ER_RAM_RW$$Base), STM32F7_Mpu_RegionSize::Size_256KBytes, STM32F7_Mpu_RegionNumber::Region1, true);
	STM32F7_Mpu_Configuration(reinterpret_cast<uint32_t>(reinterpret_cast<uint32_t*>(&HeapBegin)), STM32F7_Mpu_RegionSize::Size_32MBytes, STM32F7_Mpu_RegionNumber::Region2, true);
}
