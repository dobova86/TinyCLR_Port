#include "GHIElectronics_TinyCLR_Devices_Storage.h"
#include "../GHIElectronics_TinyCLR_InteropUtil.h"

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::get_Descriptor___GHIElectronicsTinyCLRDevicesStorageStorageDescriptor(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    const TinyCLR_Storage_Descriptor* descriptor;

    auto result = api->GetDescriptor(api, descriptor);

    TinyCLR_Interop_ClrValue obj, ret;
    TinyCLR_Interop_ClrTypeId type;

    md.InteropManager->FindType(md.InteropManager, "GHIElectronics.TinyCLR.Devices.Storage", "GHIElectronics.TinyCLR.Devices.Storage", "StorageDescriptor", type);

    md.InteropManager->CreateObject(md.InteropManager, md.Stack, type, obj);

    TinyCLR_Interop_ClrValue canReadDirectField, canWriteDirectField, canExecuteDirectField, eraseBeforeWriteField, removableField, regionsContiguousField, regionsEqualSizedField, regionCountField, regionAddressesField, regionSizesField;

    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___CanReadDirect__BackingField___BOOLEAN, canReadDirectField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___CanWriteDirect__BackingField___BOOLEAN, canWriteDirectField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___CanExecuteDirect__BackingField___BOOLEAN, canExecuteDirectField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___EraseBeforeWrite__BackingField___BOOLEAN, eraseBeforeWriteField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___Removable__BackingField___BOOLEAN, removableField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___RegionsContiguous__BackingField___BOOLEAN, regionsContiguousField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___RegionsEqualSized__BackingField___BOOLEAN, regionsEqualSizedField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___RegionCount__BackingField___I4, regionCountField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___RegionAddresses__BackingField___SZARRAY_I8, regionAddressesField);
    md.InteropManager->GetField(md.InteropManager, obj.Object, Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_StorageDescriptor::FIELD___RegionSizes__BackingField___SZARRAY_I4, regionSizesField);

    if (descriptor != nullptr) {
        canReadDirectField.Data.Numeric->Boolean = descriptor->CanReadDirect;
        canWriteDirectField.Data.Numeric->Boolean = descriptor->CanWriteDirect;
        canExecuteDirectField.Data.Numeric->Boolean = descriptor->CanWriteDirect;
        eraseBeforeWriteField.Data.Numeric->Boolean = descriptor->EraseBeforeWrite;
        removableField.Data.Numeric->Boolean = descriptor->Removable;
        regionsContiguousField.Data.Numeric->Boolean = descriptor->RegionsContiguous;
        regionsEqualSizedField.Data.Numeric->Boolean = descriptor->RegionsEqualSized;
        regionCountField.Data.Numeric->I4 = descriptor->RegionCount;

        auto addressCount = descriptor->RegionCount;
        auto sizeCount = descriptor->RegionCount;

        if (descriptor->RegionsContiguous) {
            addressCount = 1;
        }

        if (descriptor->RegionsEqualSized) {
            sizeCount = 1;
        }

        TinyCLR_Interop_ClrValue regionAddressesFieldArray, regionSizesFieldArray;

        md.InteropManager->FindType(md.InteropManager, "mscorlib", "System", "Int64", type);
        md.InteropManager->CreateArray(md.InteropManager, addressCount, type, regionAddressesFieldArray);

        md.InteropManager->FindType(md.InteropManager, "mscorlib", "System", "Int32", type);
        md.InteropManager->CreateArray(md.InteropManager, sizeCount, type, regionSizesFieldArray);

        auto regionAddresses = reinterpret_cast<int64_t*>(regionAddressesFieldArray.Data.SzArray.Data);
        auto regionSizes = reinterpret_cast<int32_t*>(regionSizesFieldArray.Data.SzArray.Data);

        for (auto i = 0; i < addressCount; i++) {
            regionAddresses[i] = descriptor->RegionAddresses[i];
        }

        for (auto i = 0; i < sizeCount; i++) {
            regionSizes[i] = descriptor->RegionSizes[i];
        }

        md.InteropManager->AssignObjectReference(md.InteropManager, regionAddressesField, regionAddressesFieldArray.Object);
        md.InteropManager->AssignObjectReference(md.InteropManager, regionSizesField, regionSizesFieldArray.Object);

        md.InteropManager->GetReturn(md.InteropManager, md.Stack, ret);

        md.InteropManager->AssignObjectReference(md.InteropManager, ret, obj.Object);
    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::Open___VOID(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    return api->Open(api);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::Close___VOID(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    return api->Close(api);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::Read___I4__I8__I4__SZARRAY_U1__I4__mscorlibSystemTimeSpan(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    TinyCLR_Interop_ClrValue args[5];

    for (auto i = 0; i < sizeof(args) / sizeof(TinyCLR_Interop_ClrValue); i++) {
        md.InteropManager->GetArgument(md.InteropManager, md.Stack, i, args[i]);
    }

    auto address = static_cast<uint64_t>(args[0].Data.Numeric->I8);
    auto count = static_cast<size_t>(args[1].Data.Numeric->I4);
    auto buffer = reinterpret_cast<uint8_t*>(args[2].Data.SzArray.Data);
    auto offset = args[3].Data.Numeric->I4;
    auto timeout = args[4].Data.Numeric->I8;

    buffer += offset;

    auto result = api->Read(api, address, count, buffer, timeout);

    TinyCLR_Interop_ClrValue ret;

    md.InteropManager->GetReturn(md.InteropManager, md.Stack, ret);

    ret.Data.Numeric->I4 = count;

    return result;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::Write___I4__I8__I4__SZARRAY_U1__I4__mscorlibSystemTimeSpan(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    TinyCLR_Interop_ClrValue args[5];

    for (auto i = 0; i < sizeof(args) / sizeof(TinyCLR_Interop_ClrValue); i++) {
        md.InteropManager->GetArgument(md.InteropManager, md.Stack, i, args[i]);
    }

    auto address = static_cast<uint64_t>(args[0].Data.Numeric->I8);
    auto count = static_cast<size_t>(args[1].Data.Numeric->I4);
    auto buffer = reinterpret_cast<uint8_t*>(args[2].Data.SzArray.Data);
    auto offset = args[3].Data.Numeric->I4;
    auto timeout = args[4].Data.Numeric->I8;

    buffer += offset;

    auto result = api->Write(api, address, count, buffer, timeout);

    TinyCLR_Interop_ClrValue ret;

    md.InteropManager->GetReturn(md.InteropManager, md.Stack, ret);

    ret.Data.Numeric->I4 = count;

    return result;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::Erase___I4__I8__I4__mscorlibSystemTimeSpan(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    TinyCLR_Interop_ClrValue args[3];

    for (auto i = 0; i < sizeof(args) / sizeof(TinyCLR_Interop_ClrValue); i++) {
        md.InteropManager->GetArgument(md.InteropManager, md.Stack, i, args[i]);
    }

    auto address = static_cast<uint64_t>(args[0].Data.Numeric->I8);
    auto count = static_cast<size_t>(args[1].Data.Numeric->I4);

    auto timeout = args[2].Data.Numeric->I8;

    auto result = api->Erase(api, address, count, timeout);

    TinyCLR_Interop_ClrValue ret;

    md.InteropManager->GetReturn(md.InteropManager, md.Stack, ret);

    ret.Data.Numeric->I4 = count;

    return result;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::IsErased___BOOLEAN__I8__I4(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));
    TinyCLR_Interop_ClrValue arg0, arg1, ret;

    md.InteropManager->GetArgument(md.InteropManager, md.Stack, 0, arg0);
    md.InteropManager->GetArgument(md.InteropManager, md.Stack, 1, arg1);
    md.InteropManager->GetReturn(md.InteropManager, md.Stack, ret);

    size_t count = arg1.Data.Numeric->I4;

    return api->IsErased(api, arg0.Data.Numeric->I8, count, ret.Data.Numeric->Boolean);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::Acquire___VOID(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    return api->Acquire(api);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_Storage_GHIElectronics_TinyCLR_Devices_Storage_Provider_StorageControllerApiWrapper::Release___VOID(const TinyCLR_Interop_MethodData md) {
    auto api = reinterpret_cast<const TinyCLR_Storage_Controller*>(TinyCLR_Interop_GetApi(md, FIELD___impl___I));

    return api->Release(api);
}
