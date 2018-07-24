#include <TinyCLR.h>
#include "Mikroe_MMB_LCD.h"
#include "Mikroe_TinyCLR_MMB_ApiInfo.h"

static TinyCLR_Api_Info ApiInfo;

const TinyCLR_Api_Info* Mikroe_TinyCLR_MMB_GetApi()
{
	ApiInfo.Author = "LEDONET";
	ApiInfo.Name = "Mikroe_MMB_LCD";
	ApiInfo.Type = TinyCLR_Api_Type::Custom;
	ApiInfo.Version = 0;
	//ApiInfo.Count = 1;
	ApiInfo.Implementation = &Interop_Mikroe_MMB_LCD;

	return &ApiInfo;
}
