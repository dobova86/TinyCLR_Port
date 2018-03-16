#include "Mikroe_MMB_LCD.h"

static const TinyCLR_Interop_MethodHandler methods[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::InitializeDisplay___VOID,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::WriteCommand___VOID__U2,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::WriteData___VOID__U2,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawRect___VOID__U2__U2__U2__U2__U2__BOOLEAN,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawLine___VOID__U2__U2__U2__U2__U2__U2,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawCircle___VOID__U2__U2__U2__U2__BOOLEAN,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawImage___VOID__SZARRAY_U1__U2__U2__U2__U2__U2__U2__U2__U2,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawText___VOID__STRING__U2__U2__U2__U4,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::ClearDisplay___VOID__U4,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::ScrollArea___VOID__U2__U2__U2__U2__U2__U2__BOOLEAN,
    Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::SetPixel___VOID__U2__U2__U2,
    nullptr,
};

const TinyCLR_Interop_Assembly Interop_Mikroe_MMB_LCD = {
    "Mikroe_MMB_LCD",
    0x039CCA4A,
    methods
};
