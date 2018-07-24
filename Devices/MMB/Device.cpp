#include "Device.h"


extern TinyCLR_Api_Info* Mikroe_TinyCLR_MMB_GetApi();

void STM32F4_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider, const TinyCLR_Interop_Provider *interopProvider) {

	apiProvider->Add(apiProvider, Mikroe_TinyCLR_MMB_GetApi());

}
