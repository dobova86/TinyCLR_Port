#pragma once

#include <TinyCLR.h>

struct Interop_GHIElectronics_TinyCLR_Native_GHIElectronics_TinyCLR_Native_Api {
    static const size_t FIELD_STATIC___defaultCreators___mscorlibSystemCollectionsHashtable = 0;

    static const size_t FIELD___Author__BackingField___STRING = 1;
    static const size_t FIELD___Name__BackingField___STRING = 2;
    static const size_t FIELD___Version__BackingField___U8 = 3;
    static const size_t FIELD___Type__BackingField___GHIElectronicsTinyCLRNativeApiType = 4;
    static const size_t FIELD___Implementation__BackingField___I = 5;
    static const size_t FIELD___State__BackingField___I = 6;

    static TinyCLR_Result Add___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Remove___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Find___STATIC___GHIElectronicsTinyCLRNativeApi__STRING__GHIElectronicsTinyCLRNativeApiType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetDefaultName___STATIC___STRING__GHIElectronicsTinyCLRNativeApiType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result SetDefaultName___STATIC___VOID__GHIElectronicsTinyCLRNativeApiType__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result FindAll___STATIC___SZARRAY_GHIElectronicsTinyCLRNativeApi(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_Native_GHIElectronics_TinyCLR_Native_DeviceInformation {
    static const size_t FIELD_STATIC___DeviceName__BackingField___STRING = 1;
    static const size_t FIELD_STATIC___ManufacturerName__BackingField___STRING = 2;
    static const size_t FIELD_STATIC___Version__BackingField___U8 = 3;

    static TinyCLR_Result cctor___STATIC___VOID(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_Native_GHIElectronics_TinyCLR_Native_Interop {
    static const size_t FIELD___Name__BackingField___STRING = 1;
    static const size_t FIELD___Checksum__BackingField___U4 = 2;
    static const size_t FIELD___Methods__BackingField___I = 3;

    static TinyCLR_Result Add___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Remove___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result RaiseEvent___STATIC___VOID__STRING__STRING__U8__U8__U8__I__mscorlibSystemDateTime(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result FindAll___STATIC___SZARRAY_GHIElectronicsTinyCLRNativeInterop(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_Native_GHIElectronics_TinyCLR_Native_Memory {
    static TinyCLR_Result Allocate___STATIC___I__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Free___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetStats___STATIC___VOID__BYREF_I__BYREF_I(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_Native_GHIElectronics_TinyCLR_Native_NativeEventDispatcher {
    static const size_t FIELD_STATIC___instances___mscorlibSystemCollectionsHashtable = 4;

    static const size_t FIELD___m_threadSpawn___GHIElectronicsTinyCLRNativeNativeEventHandler = 1;
    static const size_t FIELD___m_callbacks___GHIElectronicsTinyCLRNativeNativeEventHandler = 2;
    static const size_t FIELD___m_disposed___BOOLEAN = 3;
    static const size_t FIELD___m_NativeEventDispatcher___OBJECT = 4;
    static const size_t FIELD___name___STRING = 5;

    static TinyCLR_Result ctor___VOID__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result EnableInterrupt___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DisableInterrupt___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Dispose___VOID__BOOLEAN(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_Native_GHIElectronics_TinyCLR_Native_Power {
    static TinyCLR_Result Reset___STATIC___VOID__BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Sleep___STATIC___VOID__GHIElectronicsTinyCLRNativePowerSleepLevel__GHIElectronicsTinyCLRNativePowerSleepWakeSource(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_Native_GHIElectronics_TinyCLR_Native_SystemTime {
    static TinyCLR_Result SetTime___STATIC___VOID__I8__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetTime___STATIC___VOID__BYREF_I8__BYREF_I4(const TinyCLR_Interop_MethodData md);
};

extern const TinyCLR_Interop_Assembly Interop_GHIElectronics_TinyCLR_Native;
