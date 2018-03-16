#include "Device.h"

extern void SDRAM_Init(void);
extern void STM32F7_Display_Initialize(void);
extern void STM32F7_WriteHello(void);

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider) {
	//STM32F7_Display_Enable((TinyCLR_Display_Provider*)apiProvider);
	//STM32F7_WriteHello();
}
