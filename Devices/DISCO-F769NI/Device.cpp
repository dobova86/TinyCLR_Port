#include <TinyCLR.h>
#include "Device.h"

extern void SDRAM_Init(void);
extern void STM32F7_Display_Initialize(void);
extern void STM32F7_WriteHello(void);
extern TinyCLR_Api_Info* STM32F7_DsiDisplay_GetApi();

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider) {
#ifdef INCLUDE_DISPLAY_DSI
	apiProvider->Add(apiProvider, STM32F7_DsiDisplay_GetApi());
	apiProvider->SetDefaultSelector(apiProvider, TinyCLR_Api_Type::DisplayProvider, STM32F7_DsiDisplay_GetApi()->Name);
#pragma message "Using DSI Display interface"

#endif

}
