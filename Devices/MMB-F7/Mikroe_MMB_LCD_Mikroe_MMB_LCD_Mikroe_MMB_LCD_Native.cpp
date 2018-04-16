
#include "SSD1963_CMD.h"
#include "LCD.h"
#include "Mikroe_MMB_LCD.h"


TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::InitializeDisplay___VOID(const TinyCLR_Interop_MethodData md) {

	LCD_PinConfig();
	LCD_Init();
    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::WriteCommand___VOID__U2(const TinyCLR_Interop_MethodData md) {


    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::WriteData___VOID__U2(const TinyCLR_Interop_MethodData md) {


    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawRect___VOID__U2__U2__U2__U2__U2__BOOLEAN(const TinyCLR_Interop_MethodData md) {

	auto ip = reinterpret_cast<const TinyCLR_Interop_Provider*>(md.ApiProvider.FindDefault(&md.ApiProvider, TinyCLR_Api_Type::InteropProvider));
	TinyCLR_Interop_ClrValue x, y, fill;
	TinyCLR_Interop_ClrValue width, height, color;

	ip->GetArgument(ip, md.Stack, 1, x);
	ip->GetArgument(ip, md.Stack, 2, y);
	ip->GetArgument(ip, md.Stack, 3, width);
	ip->GetArgument(ip, md.Stack, 4, height);
	ip->GetArgument(ip, md.Stack, 5, color);
	ip->GetArgument(ip, md.Stack, 6, fill);

	LCD_Rectangle(x.Data.Numeric->U2, y.Data.Numeric->U2, width.Data.Numeric->U2, height.Data.Numeric->U2, color.Data.Numeric->U2, false);
	//LCD_Rectangle(10, 10, 150, 150, 65535, false);
    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawLine___VOID__U2__U2__U2__U2__U2__U2(const TinyCLR_Interop_MethodData md) {

	auto ip = reinterpret_cast<const TinyCLR_Interop_Provider*>(md.ApiProvider.FindDefault(&md.ApiProvider, TinyCLR_Api_Type::InteropProvider));
	TinyCLR_Interop_ClrValue x, y, x1, y1, color;

	ip->GetArgument(ip, md.Stack, 1, x);
	ip->GetArgument(ip, md.Stack, 2, y);
	ip->GetArgument(ip, md.Stack, 3, x1);
	ip->GetArgument(ip, md.Stack, 4, y1);
	ip->GetArgument(ip, md.Stack, 5, color);

	LCD_Line(x.Data.Numeric->U2, y.Data.Numeric->U2, x1.Data.Numeric->U2, y1.Data.Numeric->U2, color.Data.Numeric->U2);
    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawCircle___VOID__U2__U2__U2__U2__BOOLEAN(const TinyCLR_Interop_MethodData md) {

	auto ip = reinterpret_cast<const TinyCLR_Interop_Provider*>(md.ApiProvider.FindDefault(&md.ApiProvider, TinyCLR_Api_Type::InteropProvider));
	TinyCLR_Interop_ClrValue x, y, radius, color;
	ip->GetArgument(ip, md.Stack, 1, x);
	ip->GetArgument(ip, md.Stack, 2, y);
	ip->GetArgument(ip, md.Stack, 3, radius);
	ip->GetArgument(ip, md.Stack, 4, color);
	bool fill = true;

	LCD_Circle(x.Data.Numeric->U2, y.Data.Numeric->U2, radius.Data.Numeric->U2, color.Data.Numeric->U2, fill);
    return TinyCLR_Result::Success;
}

// byte[] image, ushort xDst, ushort yDst, ushort originalWidth, ushort originalHeight, ushort xSrc, ushort ySrc, ushort width, ushort height
TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawImage___VOID__SZARRAY_U1__U2__U2__U2__U2__U2__U2__U2__U2(const TinyCLR_Interop_MethodData md) {

	/*
	NOTE: The implementation need to be moved to LCD.cpp !!!!
	*/
	auto ip = reinterpret_cast<const TinyCLR_Interop_Provider*>(md.ApiProvider.FindDefault(&md.ApiProvider, TinyCLR_Api_Type::InteropProvider));
	TinyCLR_Interop_ClrValue x, y, xWidth, yHeight, xSrc, ySrc, dwidth, dheight;
	TinyCLR_Interop_ClrValue bitmap;

	ip->GetArgument(ip, md.Stack, 1, bitmap);
	ip->GetArgument(ip, md.Stack, 2, x);
	ip->GetArgument(ip, md.Stack, 3, y);
	ip->GetArgument(ip, md.Stack, 4, xWidth);
	ip->GetArgument(ip, md.Stack, 5, yHeight);
	ip->GetArgument(ip, md.Stack, 6, xSrc);
	ip->GetArgument(ip, md.Stack, 7, ySrc);
	ip->GetArgument(ip, md.Stack, 8, dwidth);
	ip->GetArgument(ip, md.Stack, 9, dheight);

	char *bitmaparray = (char*) bitmap.Data.SzArray.Data ;
	uint16_t bmp_len = bitmap.Data.SzArray.Length;
	uint16_t x_des = x.Data.Numeric->U2;
	uint16_t y_des = y.Data.Numeric->U2;
	uint16_t width_org = xWidth.Data.Numeric->U2;
	uint16_t height_org = yHeight.Data.Numeric->U2;
	uint16_t x_src = xSrc.Data.Numeric->U2;
	uint16_t y_src = ySrc.Data.Numeric->U2;
	uint16_t width = dwidth.Data.Numeric->U2;
	uint16_t height = dheight.Data.Numeric->U2;
	int len = (width * height) << 1; // RGB_565 format
	
	LCD_DrawImage(bitmaparray, bmp_len, x_des, y_des, width_org, height_org, x_src, y_src, width, height);

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::DrawText___VOID__STRING__U2__U2__U2__U4(const TinyCLR_Interop_MethodData md) {

	auto ip = reinterpret_cast<const TinyCLR_Interop_Provider*>(md.ApiProvider.FindDefault(&md.ApiProvider, TinyCLR_Api_Type::InteropProvider));
	TinyCLR_Interop_ClrValue text, x, y, color;
	
	ip->GetArgument(ip, md.Stack, 1, text);
	ip->GetArgument(ip, md.Stack, 3, x);
	ip->GetArgument(ip, md.Stack, 4, y);
	ip->GetArgument(ip, md.Stack, 5, color);
	LCD_Text(x.Data.Numeric->U2, y.Data.Numeric->U2, text.Data.String.Data, text.Data.String.Length, color.Data.Numeric->U4, 0);
    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::ClearDisplay___VOID__U4(const TinyCLR_Interop_MethodData md) {

	auto ip = reinterpret_cast<const TinyCLR_Interop_Provider*>(md.ApiProvider.FindDefault(&md.ApiProvider, TinyCLR_Api_Type::InteropProvider));
	TinyCLR_Interop_ClrValue color;
	ip->GetArgument(ip, md.Stack, 1, color);
	LCD_Clear(color.Data.Numeric->U4);

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::ScrollArea___VOID__U2__U2__U2__U2__U2__U2__BOOLEAN(const TinyCLR_Interop_MethodData md) {


    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Mikroe_MMB_LCD_Native::SetPixel___VOID__U2__U2__U2(const TinyCLR_Interop_MethodData md) {


    return TinyCLR_Result::Success;
}
