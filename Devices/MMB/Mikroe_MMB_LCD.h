#pragma once

#include <TinyCLR.h>

struct Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD {
    static const size_t FIELD____native___MikroeMMBLCDMikroeMMBLCDNative = 1;
};

struct Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native {
    static TinyCLR_Result InitializeDisplay___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result WriteCommand___VOID__U2(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result WriteData___VOID__U2(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DrawRect___VOID__U2__U2__U2__U2__U2__BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DrawLine___VOID__U2__U2__U2__U2__U2__U2(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DrawCircle___VOID__U2__U2__U2__U2__BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DrawImage___VOID__SZARRAY_U1__U2__U2__U2__U2__U2__U2__U2__U2(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DrawText___VOID__STRING__U2__U2__U2__U4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ClearDisplay___VOID__U4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ScrollArea___VOID__U2__U2__U2__U2__U2__U2__BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result SetPixel___VOID__U2__U2__U2(const TinyCLR_Interop_MethodData md);
};

extern const TinyCLR_Interop_Assembly Interop_Mikroe_MMB_LCD;
