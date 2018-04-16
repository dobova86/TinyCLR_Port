#include "Device.h"

extern TinyCLR_Api_Info* Mikroe_TinyCLR_MMB_GetApi();

void STM32F7_Startup_OnSoftResetDevice(const TinyCLR_Api_Provider* apiProvider) {

	apiProvider->Add(apiProvider, Mikroe_TinyCLR_MMB_GetApi());

}
