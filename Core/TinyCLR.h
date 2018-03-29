// Copyright GHI Electronics, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>
#include <cstddef>

////////////////////////////////////////////////////////////////////////////////
//Results
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Result : uint32_t {
    Success = 0,
    ArgumentInvalid = 1,
    ArgumentNull = 2,
    ArgumentOutOfRange = 3,
    NotSupported = 4,
    NotFound = 5,
    NotAvailable = 6,
    NotImplemented = 7,
    InvalidOperation = 8,
    IndexOutOfRange = 9,
    NullReference = 10,
    AlreadyExists = 11,
    SharingViolation = 12,
    SynchronizationFailed = 13,
    Disposed = 14,
    WrongType = 15,
    DivideByZero = 16,
    SerializationFailed = 17,
    TimedOut = 18,
    WatchdogTimedOut = 19,
    Busy = 20,
    OutOfMemory = 21,
    WrongChecksum = 22,
    ShuttingDown = 23,
    DeviceFailure = 24,
    UnknownFailure = 25,
    NoDataAvailable = 26,
};

////////////////////////////////////////////////////////////////////////////////
//API
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Api_Type : uint32_t {
    ApiProvider = 0,
    DebuggerProvider = 1,
    InteropProvider = 2,
    MemoryProvider = 3,
    TaskProvider = 4,
    DeploymentProvider = 0 | 0x20000000,
    InterruptProvider = 1 | 0x20000000,
    PowerProvider = 2 | 0x20000000,
    TimeProvider = 3 | 0x20000000,
    AdcProvider = 0 | 0x40000000,
    CanProvider = 1 | 0x40000000,
    DacProvider = 2 | 0x40000000,
    DisplayProvider = 3 | 0x40000000,
    GpioProvider = 4 | 0x40000000,
    I2cProvider = 5 | 0x40000000,
    PwmProvider = 6 | 0x40000000,
    SpiProvider = 7 | 0x40000000,
    UartProvider = 8 | 0x40000000,
    UsbClientProvider = 9 | 0x40000000,
    UsbHostProvider = 10 | 0x40000000,
    Custom = 0 | 0x80000000,
};

struct TinyCLR_Api_Info {
    const char* Author;
    const char* Name;
    TinyCLR_Api_Type Type;
    void* State;
    uint64_t Version;
    size_t Count;
    const void* Implementation;
};

struct TinyCLR_Api_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Api_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Api_Provider* self);
    TinyCLR_Result(*Add)(const TinyCLR_Api_Provider* self, const TinyCLR_Api_Info* api);
    TinyCLR_Result(*Remove)(const TinyCLR_Api_Provider* self, const TinyCLR_Api_Info* api);
    const TinyCLR_Api_Info*(*Find)(const TinyCLR_Api_Provider* self, const char* name, TinyCLR_Api_Type type);
    const void*(*FindBySelector)(const TinyCLR_Api_Provider* self, const char* selector, TinyCLR_Api_Type type);
    const void*(*FindByIndex)(const TinyCLR_Api_Provider* self, const char* apiName, size_t index, TinyCLR_Api_Type type);
    const void*(*FindDefault)(const TinyCLR_Api_Provider* self, TinyCLR_Api_Type type);
    TinyCLR_Result(*SetDefaultSelector)(const TinyCLR_Api_Provider* self, TinyCLR_Api_Type type, const char* selector);
    const char*(*GetDefaultSelector)(const TinyCLR_Api_Provider* self, TinyCLR_Api_Type type);
};

////////////////////////////////////////////////////////////////////////////////
//Debugger
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Debugger_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Debugger_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Debugger_Provider* self);
    TinyCLR_Result(*Log)(const TinyCLR_Debugger_Provider* self, const char* str, size_t length);
};

////////////////////////////////////////////////////////////////////////////////
//Interop
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Interop_StackFrame;

struct TinyCLR_Interop_MethodData {
    const TinyCLR_Api_Provider& ApiProvider;
    TinyCLR_Interop_StackFrame& Stack;
};

typedef TinyCLR_Result(*TinyCLR_Interop_MethodHandler)(const TinyCLR_Interop_MethodData md);

struct TinyCLR_Interop_Assembly {
    const char* Name;
    uint32_t Checksum;
    const TinyCLR_Interop_MethodHandler* Methods;
};

typedef uint32_t TinyCLR_Interop_ClrTypeId;

struct TinyCLR_Interop_ClrObjectReference {
    uint64_t a;
    uint64_t b;
};

struct TinyCLR_Interop_ClrObject {
    uint64_t a;
    uint64_t b;
};

struct TinyCLR_Interop_ClrValue {
    union NumericType {
        bool Boolean;
        int8_t I1;
        uint8_t U1;
        char16_t Char;
        int16_t I2;
        uint16_t U2;
        int32_t I4;
        uint32_t U4;
        float R4;
        intptr_t I;
        uintptr_t U;
        int64_t I8;
        uint64_t U8;
        double R8;
    };

    struct StringType {
        const char* Data;
        size_t Length;
    };

    struct SzArrayType {
        void* Data;
        size_t Length;
    };

    union DataType {
        NumericType* Numeric;
        StringType String;
        SzArrayType SzArray;
    };

    const TinyCLR_Interop_ClrObjectReference* Ref;
    const TinyCLR_Interop_ClrObject* Object;
    DataType Data;
};

struct TinyCLR_Interop_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Interop_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Interop_Provider* self);
    TinyCLR_Result(*Add)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_Assembly* interop);
    TinyCLR_Result(*Remove)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_Assembly* interop);
    TinyCLR_Result(*RaiseEvent)(const TinyCLR_Interop_Provider* self, const char* eventDispatcherName, const char* apiName, size_t implementationIndex, uint64_t data0, uint64_t data1, intptr_t data2);
    TinyCLR_Result(*FindType)(const TinyCLR_Interop_Provider* self, const char* assemblyName, const char* namespaceName, const char* typeName, TinyCLR_Interop_ClrTypeId& type);
    TinyCLR_Result(*GetClrTypeId)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_ClrObject* object, TinyCLR_Interop_ClrTypeId& type);
    TinyCLR_Result(*CreateArray)(const TinyCLR_Interop_Provider* self, size_t length, TinyCLR_Interop_ClrTypeId elementType, TinyCLR_Interop_ClrValue& value);
    TinyCLR_Result(*CreateString)(const TinyCLR_Interop_Provider* self, const char* data, size_t length, TinyCLR_Interop_ClrValue& value);
    TinyCLR_Result(*CreateObject)(const TinyCLR_Interop_Provider* self, TinyCLR_Interop_StackFrame& stack, TinyCLR_Interop_ClrTypeId type, TinyCLR_Interop_ClrValue& value);
    TinyCLR_Result(*CreateObjectReference)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_ClrObject* object, TinyCLR_Interop_ClrValue& value);
    TinyCLR_Result(*AssignObjectReference)(const TinyCLR_Interop_Provider* self, TinyCLR_Interop_ClrValue& target, const TinyCLR_Interop_ClrObject* object);
    TinyCLR_Result(*ExtractObjectFromReference)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_ClrObjectReference* reference, const TinyCLR_Interop_ClrObject*& object);
    TinyCLR_Result(*GetThisObject)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_StackFrame& stack, const TinyCLR_Interop_ClrObject*& object);
    TinyCLR_Result(*GetField)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_ClrObject* object, size_t index, TinyCLR_Interop_ClrValue& value);
    TinyCLR_Result(*GetStaticField)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_Assembly& interop, size_t index, TinyCLR_Interop_ClrValue& value);
    TinyCLR_Result(*GetArgument)(const TinyCLR_Interop_Provider* self, const TinyCLR_Interop_StackFrame& stack, size_t index, TinyCLR_Interop_ClrValue& value);
    TinyCLR_Result(*GetReturn)(const TinyCLR_Interop_Provider* self, TinyCLR_Interop_StackFrame& stack, TinyCLR_Interop_ClrValue& value);
};

////////////////////////////////////////////////////////////////////////////////
//Memory
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Memory_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Memory_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Memory_Provider* self);
    void*(*Allocate)(const TinyCLR_Memory_Provider* self, size_t length);
    void(*Free)(const TinyCLR_Memory_Provider* self, void* ptr);
};

////////////////////////////////////////////////////////////////////////////////
//Task
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Task_Provider;

typedef const void* TinyCLR_Task_Inst;
typedef void(*TinyCLR_Task_Callback)(const TinyCLR_Task_Provider* self, const TinyCLR_Api_Provider* api, TinyCLR_Task_Inst task, void* arg);

struct TinyCLR_Task_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Task_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Task_Provider* self);
    TinyCLR_Result(*Create)(const TinyCLR_Task_Provider* self, TinyCLR_Task_Callback callback, void* arg, bool fireInIsr, TinyCLR_Task_Inst& result);
    TinyCLR_Result(*Free)(const TinyCLR_Task_Provider* self, TinyCLR_Task_Inst& task);
    TinyCLR_Result(*Enqueue)(const TinyCLR_Task_Provider* self, TinyCLR_Task_Inst task, uint64_t microsecondsFromNow);
};

////////////////////////////////////////////////////////////////////////////////
//Deployment
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Deployment_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Deployment_Provider* self, bool& supportsXip);
    TinyCLR_Result(*Release)(const TinyCLR_Deployment_Provider* self);
    TinyCLR_Result(*Read)(const TinyCLR_Deployment_Provider* self, uint32_t address, size_t length, uint8_t* buffer);
    TinyCLR_Result(*Write)(const TinyCLR_Deployment_Provider* self, uint32_t address, size_t length, const uint8_t* buffer);
    TinyCLR_Result(*EraseSector)(const TinyCLR_Deployment_Provider* self, uint32_t sector);
    TinyCLR_Result(*IsSectorErased)(const TinyCLR_Deployment_Provider* self, uint32_t sector, bool& erased);
    TinyCLR_Result(*GetSectorMap)(const TinyCLR_Deployment_Provider* self, const uint32_t*& addresses, const uint32_t*& sizes, size_t& count);
};

////////////////////////////////////////////////////////////////////////////////
//Interrupt
////////////////////////////////////////////////////////////////////////////////
typedef void(*TinyCLR_Interrupt_StartStopHandler)();

struct TinyCLR_Interrupt_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(TinyCLR_Interrupt_StartStopHandler onInterruptStart, TinyCLR_Interrupt_StartStopHandler onInterruptEnd);
    TinyCLR_Result(*Release)();
    bool(*Enable)(bool force);
    bool(*Disable)(bool force);
    void(*WaitForInterrupt)();
    bool(*IsDisabled)();
    void(*Restore)();
};

////////////////////////////////////////////////////////////////////////////////
//Power
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Power_SleepLevel : uint32_t {
    Sleep = 0,
    Hibernate = 1,
    Off = 2,
};

struct TinyCLR_Power_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Power_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Power_Provider* self);
    void(*Reset)(const TinyCLR_Power_Provider* self, bool runCoreAfter);
    void(*Sleep)(const TinyCLR_Power_Provider* self, TinyCLR_Power_SleepLevel level);
};

////////////////////////////////////////////////////////////////////////////////
//Time
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Time_Provider;

typedef void(*TinyCLR_Time_TickCallback)();

struct TinyCLR_Time_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Time_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Time_Provider* self);
    TinyCLR_Result(*GetInitialTime)(const TinyCLR_Time_Provider* self, int64_t& utcTime, int32_t& timeZoneOffsetMinutes);
    uint64_t(*GetCurrentProcessorTicks)(const TinyCLR_Time_Provider* self);
    uint64_t(*GetTimeForProcessorTicks)(const TinyCLR_Time_Provider* self, uint64_t ticks);
    uint64_t(*GetProcessorTicksForTime)(const TinyCLR_Time_Provider* self, uint64_t time);
    TinyCLR_Result(*SetTickCallback)(const TinyCLR_Time_Provider* self, TinyCLR_Time_TickCallback callback);
    TinyCLR_Result(*SetNextTickCallbackTime)(const TinyCLR_Time_Provider* self, uint64_t processorTicks);
    void(*Delay)(const TinyCLR_Time_Provider* self, uint64_t microseconds);
    void(*DelayNoInterrupt)(const TinyCLR_Time_Provider* self, uint64_t microseconds);
};

////////////////////////////////////////////////////////////////////////////////
//Startup
////////////////////////////////////////////////////////////////////////////////
typedef void(*TinyCLR_Startup_SoftResetHandler)(const TinyCLR_Api_Provider* apiProvider);

TinyCLR_Result TinyCLR_Startup_AddHeapRegion(uint8_t* start, size_t length);
TinyCLR_Result TinyCLR_Startup_SetDeviceInformation(const char* deviceName, const char* manufacturerName, uint64_t version);
TinyCLR_Result TinyCLR_Startup_SetDebuggerTransportProvider(const TinyCLR_Api_Info* api, size_t index);
TinyCLR_Result TinyCLR_Startup_SetRequiredProviders(const TinyCLR_Api_Info* deploymentApi, const TinyCLR_Api_Info* interruptApi, const TinyCLR_Api_Info* powerApi, const TinyCLR_Api_Info* timeApi);
TinyCLR_Result TinyCLR_Startup_Start(TinyCLR_Startup_SoftResetHandler handler, bool runManagedApplication);

////////////////////////////////////////////////////////////////////////////////
//ADC
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Adc_ChannelMode : uint32_t {
    SingleEnded = 0,
    Differential = 1
};

struct TinyCLR_Adc_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Adc_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Adc_Provider* self);
    TinyCLR_Result(*AcquireChannel)(const TinyCLR_Adc_Provider* self, int32_t channel);
    TinyCLR_Result(*ReleaseChannel)(const TinyCLR_Adc_Provider* self, int32_t channel);
    TinyCLR_Result(*ReadValue)(const TinyCLR_Adc_Provider* self, int32_t channel, int32_t& value);
    TinyCLR_Result(*SetChannelMode)(const TinyCLR_Adc_Provider* self, TinyCLR_Adc_ChannelMode mode);
    TinyCLR_Adc_ChannelMode(*GetChannelMode)(const TinyCLR_Adc_Provider* self);
    bool(*IsChannelModeSupported)(const TinyCLR_Adc_Provider* self, TinyCLR_Adc_ChannelMode mode);
    int32_t(*GetMinValue)(const TinyCLR_Adc_Provider* self);
    int32_t(*GetMaxValue)(const TinyCLR_Adc_Provider* self);
    int32_t(*GetResolutionInBits)(const TinyCLR_Adc_Provider* self);
    int32_t(*GetChannelCount)(const TinyCLR_Adc_Provider* self);
};

////////////////////////////////////////////////////////////////////////////////
//CAN
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Can_Provider;

enum class TinyCLR_Can_Error : uint32_t {
    ReadBufferOverrun = 0,
    ReadBufferFull = 1,
    BusOff = 2,
    Passive = 3
};

typedef void(*TinyCLR_Can_MessageReceivedHandler)(const TinyCLR_Can_Provider* self, size_t count);
typedef void(*TinyCLR_Can_ErrorReceivedHandler)(const TinyCLR_Can_Provider* self, TinyCLR_Can_Error error);

struct TinyCLR_Can_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Can_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Can_Provider* self);
    TinyCLR_Result(*Reset)(const TinyCLR_Can_Provider* self);
    TinyCLR_Result(*WriteMessage)(const TinyCLR_Can_Provider* self, uint32_t arbitrationId, bool isExtendedId, bool isRemoteTransmissionRequest, uint8_t* data, size_t length);
    TinyCLR_Result(*ReadMessage)(const TinyCLR_Can_Provider* self, uint32_t& arbitrationId, bool& isExtendedId, bool& isRemoteTransmissionRequest, uint64_t& timestamp, uint8_t* data, size_t& length);
    TinyCLR_Result(*SetBitTiming)(const TinyCLR_Can_Provider* self, int32_t propagation, int32_t phase1, int32_t phase2, int32_t baudratePrescaler, int32_t synchronizationJumpWidth, int8_t useMultiBitSampling);
    TinyCLR_Result(*GetUnreadMessageCount)(const TinyCLR_Can_Provider* self, size_t& count);
    TinyCLR_Result(*SetMessageReceivedHandler)(const TinyCLR_Can_Provider* self, TinyCLR_Can_MessageReceivedHandler handler);
    TinyCLR_Result(*SetErrorReceivedHandler)(const TinyCLR_Can_Provider* self, TinyCLR_Can_ErrorReceivedHandler handler);
    TinyCLR_Result(*SetExplicitFilters)(const TinyCLR_Can_Provider* self, uint8_t* filters, size_t length);
    TinyCLR_Result(*SetGroupFilters)(const TinyCLR_Can_Provider* self, uint8_t* lowerBounds, uint8_t* upperBounds, size_t length);
    TinyCLR_Result(*ClearReadBuffer)(const TinyCLR_Can_Provider* self);
    TinyCLR_Result(*IsWritingAllowed)(const TinyCLR_Can_Provider* self, bool& allowed);
    TinyCLR_Result(*GetWriteErrorCount)(const TinyCLR_Can_Provider* self, size_t& count);
    TinyCLR_Result(*GetReadErrorCount)(const TinyCLR_Can_Provider* self, size_t& count);
    TinyCLR_Result(*GetSourceClock)(const TinyCLR_Can_Provider* self, uint32_t& sourceClock);
    TinyCLR_Result(*GetReadBufferSize)(const TinyCLR_Can_Provider* self, size_t& size);
    TinyCLR_Result(*SetReadBufferSize)(const TinyCLR_Can_Provider* self, size_t size);
    TinyCLR_Result(*GetWriteBufferSize)(const TinyCLR_Can_Provider* self, size_t& size);
    TinyCLR_Result(*SetWriteBufferSize)(const TinyCLR_Can_Provider* self, size_t size);
};

////////////////////////////////////////////////////////////////////////////////
//DAC
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Dac_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Dac_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Dac_Provider* self);
    TinyCLR_Result(*AcquireChannel)(const TinyCLR_Dac_Provider* self, int32_t channel);
    TinyCLR_Result(*ReleaseChannel)(const TinyCLR_Dac_Provider* self, int32_t channel);
    TinyCLR_Result(*WriteValue)(const TinyCLR_Dac_Provider* self, int32_t channel, int32_t value);
    int32_t(*GetMinValue)(const TinyCLR_Dac_Provider* self);
    int32_t(*GetMaxValue)(const TinyCLR_Dac_Provider* self);
    int32_t(*GetResolutionInBits)(const TinyCLR_Dac_Provider* self);
    int32_t(*GetChannelCount)(const TinyCLR_Dac_Provider* self);
};

////////////////////////////////////////////////////////////////////////////////
//Display
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Display_DataFormat : uint32_t {
    Rgb565 = 0,
	Rgb888 = 1
};

enum class TinyCLR_Display_InterfaceType : uint32_t {
    Parallel = 0,
    Spi = 1,
};

struct TinyCLR_Display_ParallelConfiguration {
    bool DataEnableIsFixed;
    bool DataEnablePolarity;
    bool PixelPolarity;
    uint32_t PixelClockRate;
    bool HorizontalSyncPolarity;
    uint32_t HorizontalSyncPulseWidth;
    uint32_t HorizontalFrontPorch;
    uint32_t HorizontalBackPorch;
    bool VerticalSyncPolarity;
    uint32_t VerticalSyncPulseWidth;
    uint32_t VerticalFrontPorch;
    uint32_t VerticalBackPorch;
};

struct TinyCLR_Display_SpiConfiguration {
    const char* SpiSelector;
};

struct TinyCLR_Display_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Display_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Display_Provider* self);
    TinyCLR_Result(*GetCapabilities)(const TinyCLR_Display_Provider* self, TinyCLR_Display_InterfaceType& type, const TinyCLR_Display_DataFormat*& supportedDataFormats, size_t& supportedDataFormatCount);
    TinyCLR_Result(*GetConfiguration)(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat& dataFormat, uint32_t& width, uint32_t& height, void* configuration);
    TinyCLR_Result(*SetConfiguration)(const TinyCLR_Display_Provider* self, TinyCLR_Display_DataFormat dataFormat, uint32_t width, uint32_t height, const void* configuration);
    TinyCLR_Result(*DrawBuffer)(const TinyCLR_Display_Provider* self, int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t* data);
    TinyCLR_Result(*WriteString)(const TinyCLR_Display_Provider* self, const char* data, size_t length);
    TinyCLR_Result(*Enable)(const TinyCLR_Display_Provider* self);
    TinyCLR_Result(*Disable)(const TinyCLR_Display_Provider* self);
};

////////////////////////////////////////////////////////////////////////////////
//GPIO
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Gpio_PinDriveMode : uint32_t {
    Input = 0,
    Output = 1,
    InputPullUp = 2,
    InputPullDown = 3,
    OutputOpenDrain = 4,
    OutputOpenDrainPullUp = 5,
    OutputOpenSource = 6,
    OutputOpenSourcePullDown = 7,
};

enum class TinyCLR_Gpio_PinValue : uint32_t {
    Low = 0,
    High = 1,
};

struct TinyCLR_Gpio_Provider;

typedef void(*TinyCLR_Gpio_ValueChangedHandler)(const TinyCLR_Gpio_Provider* self, int32_t pin, TinyCLR_Gpio_PinValue value);

struct TinyCLR_Gpio_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Gpio_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Gpio_Provider* self);
    TinyCLR_Result(*AcquirePin)(const TinyCLR_Gpio_Provider* self, int32_t pin);
    TinyCLR_Result(*ReleasePin)(const TinyCLR_Gpio_Provider* self, int32_t pin);
    TinyCLR_Result(*Read)(const TinyCLR_Gpio_Provider* self, int32_t pin, TinyCLR_Gpio_PinValue& value);
    TinyCLR_Result(*Write)(const TinyCLR_Gpio_Provider* self, int32_t pin, TinyCLR_Gpio_PinValue value);
    bool(*IsDriveModeSupported)(const TinyCLR_Gpio_Provider* self, int32_t pin, TinyCLR_Gpio_PinDriveMode mode);
    TinyCLR_Gpio_PinDriveMode(*GetDriveMode)(const TinyCLR_Gpio_Provider* self, int32_t pin);
    TinyCLR_Result(*SetDriveMode)(const TinyCLR_Gpio_Provider* self, int32_t pin, TinyCLR_Gpio_PinDriveMode mode);
    int32_t(*GetDebounceTimeout)(const TinyCLR_Gpio_Provider* self, int32_t pin);
    TinyCLR_Result(*SetDebounceTimeout)(const TinyCLR_Gpio_Provider* self, int32_t pin, int32_t debounceMilliseconds);
    TinyCLR_Result(*SetValueChangedHandler)(const TinyCLR_Gpio_Provider* self, int32_t pin, TinyCLR_Gpio_ValueChangedHandler handler);
    int32_t(*GetPinCount)(const TinyCLR_Gpio_Provider* self);
};

////////////////////////////////////////////////////////////////////////////////
//I2C
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_I2c_BusSpeed : uint32_t {
    StandardMode = 0,
    FastMode = 1	
};

enum class TinyCLR_I2c_TransferStatus : uint32_t {
    FullTransfer = 0,
    PartialTransfer = 1,
    SlaveAddressNotAcknowledged = 2,
    ClockStretchTimeout = 3,
    UnknownError = 4,
};

struct TinyCLR_I2c_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_I2c_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_I2c_Provider* self);
    TinyCLR_Result(*SetActiveSettings)(const TinyCLR_I2c_Provider* self, int32_t slaveAddress, TinyCLR_I2c_BusSpeed busSpeed);
    TinyCLR_Result(*Read)(const TinyCLR_I2c_Provider* self, uint8_t* buffer, size_t& length, TinyCLR_I2c_TransferStatus& result);
    TinyCLR_Result(*Write)(const TinyCLR_I2c_Provider* self, const uint8_t* buffer, size_t& length, TinyCLR_I2c_TransferStatus& result);
    TinyCLR_Result(*WriteRead)(const TinyCLR_I2c_Provider* self, const uint8_t* writeBuffer, size_t& writeLength, uint8_t* readBuffer, size_t& readLength, TinyCLR_I2c_TransferStatus& result);
};

////////////////////////////////////////////////////////////////////////////////
//PWM
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_Pwm_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Pwm_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Pwm_Provider* self);
    TinyCLR_Result(*AcquirePin)(const TinyCLR_Pwm_Provider* self, int32_t pin);
    TinyCLR_Result(*ReleasePin)(const TinyCLR_Pwm_Provider* self, int32_t pin);
    TinyCLR_Result(*EnablePin)(const TinyCLR_Pwm_Provider* self, int32_t pin);
    TinyCLR_Result(*DisablePin)(const TinyCLR_Pwm_Provider* self, int32_t pin);
    TinyCLR_Result(*SetPulseParameters)(const TinyCLR_Pwm_Provider* self, int32_t pin, double dutyCycle, bool invertPolarity);
    TinyCLR_Result(*SetDesiredFrequency)(const TinyCLR_Pwm_Provider* self, double& frequency);
    double(*GetMinFrequency)(const TinyCLR_Pwm_Provider* self);
    double(*GetMaxFrequency)(const TinyCLR_Pwm_Provider* self);
    int32_t(*GetPinCount)(const TinyCLR_Pwm_Provider* self);
};

////////////////////////////////////////////////////////////////////////////////
//SPI
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Spi_Mode : uint32_t {
    Mode0 = 0,
    Mode1 = 1,
    Mode2 = 2,
    Mode3 = 3,
};

struct TinyCLR_Spi_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Spi_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Spi_Provider* self);
    TinyCLR_Result(*SetActiveSettings)(const TinyCLR_Spi_Provider* self, int32_t chipSelectLine, int32_t clockFrequency, int32_t dataBitLength, TinyCLR_Spi_Mode mode);
    TinyCLR_Result(*Read)(const TinyCLR_Spi_Provider* self, uint8_t* buffer, size_t& length);
    TinyCLR_Result(*Write)(const TinyCLR_Spi_Provider* self, const uint8_t* buffer, size_t& length);
    TinyCLR_Result(*TransferFullDuplex)(const TinyCLR_Spi_Provider* self, const uint8_t* writeBuffer, size_t& writeLength, uint8_t* readBuffer, size_t& readLength);
    TinyCLR_Result(*TransferSequential)(const TinyCLR_Spi_Provider* self, const uint8_t* writeBuffer, size_t& writeLength, uint8_t* readBuffer, size_t& readLength);
    int32_t(*GetChipSelectLineCount)(const TinyCLR_Spi_Provider* self);
    int32_t(*GetMinClockFrequency)(const TinyCLR_Spi_Provider* self);
    int32_t(*GetMaxClockFrequency)(const TinyCLR_Spi_Provider* self);
    TinyCLR_Result(*GetSupportedDataBitLengths)(const TinyCLR_Spi_Provider* self, int32_t* dataBitLengths, size_t& dataBitLengthsCount);
};

////////////////////////////////////////////////////////////////////////////////
//UART
////////////////////////////////////////////////////////////////////////////////
enum class TinyCLR_Uart_Parity : uint32_t {
    None = 0,
    Odd = 1,
    Even = 2,
    Mark = 3,
    Space = 4,
};

enum class TinyCLR_Uart_StopBitCount : uint32_t {
    One = 0,
    OnePointFive = 1,
    Two = 2,
};

enum class TinyCLR_Uart_Handshake : uint32_t {
    None = 0,
    RequestToSend = 1,
    XOnXOff = 2,
    RequestToSendXOnXOff = 3,
};

enum class TinyCLR_Uart_PinChange : uint32_t {
    BreakSignal = 0,
    CarrierDetect = 1,
    ClearToSend = 2,
    DataSetReady = 3,
    RingIndicator = 4,
};

enum class TinyCLR_Uart_Error : uint32_t {
    Frame = 0,
    BufferOverrun = 1,
    ReceiveFull = 2,
    ReceiveParity = 3,
    TransmitFull = 4,
};

struct TinyCLR_Uart_Provider;

typedef void(*TinyCLR_Uart_PinChangedHandler)(const TinyCLR_Uart_Provider* self, TinyCLR_Uart_PinChange pinChange);
typedef void(*TinyCLR_Uart_ErrorReceivedHandler)(const TinyCLR_Uart_Provider* self, TinyCLR_Uart_Error error);
typedef void(*TinyCLR_Uart_DataReceivedHandler)(const TinyCLR_Uart_Provider* self, size_t count);

struct TinyCLR_Uart_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_Uart_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_Uart_Provider* self);
    TinyCLR_Result(*SetActiveSettings)(const TinyCLR_Uart_Provider* self, uint32_t baudRate, uint32_t dataBits, TinyCLR_Uart_Parity parity, TinyCLR_Uart_StopBitCount stopBits, TinyCLR_Uart_Handshake handshaking);
    TinyCLR_Result(*Flush)(const TinyCLR_Uart_Provider* self);
    TinyCLR_Result(*Read)(const TinyCLR_Uart_Provider* self, uint8_t* buffer, size_t& length);
    TinyCLR_Result(*Write)(const TinyCLR_Uart_Provider* self, const uint8_t* buffer, size_t& length);
    TinyCLR_Result(*SetPinChangedHandler)(const TinyCLR_Uart_Provider* self, TinyCLR_Uart_PinChangedHandler handler);
    TinyCLR_Result(*SetErrorReceivedHandler)(const TinyCLR_Uart_Provider* self, TinyCLR_Uart_ErrorReceivedHandler handler);
    TinyCLR_Result(*SetDataReceivedHandler)(const TinyCLR_Uart_Provider* self, TinyCLR_Uart_DataReceivedHandler handler);
    TinyCLR_Result(*GetBreakSignalState)(const TinyCLR_Uart_Provider* self, bool& state);
    TinyCLR_Result(*SetBreakSignalState)(const TinyCLR_Uart_Provider* self, bool state);
    TinyCLR_Result(*GetCarrierDetectState)(const TinyCLR_Uart_Provider* self, bool& state);
    TinyCLR_Result(*GetClearToSendState)(const TinyCLR_Uart_Provider* self, bool& state);
    TinyCLR_Result(*GetDataReadyState)(const TinyCLR_Uart_Provider* self, bool& state);
    TinyCLR_Result(*GetIsDataTerminalReadyEnabled)(const TinyCLR_Uart_Provider* self, bool& state);
    TinyCLR_Result(*SetIsDataTerminalReadyEnabled)(const TinyCLR_Uart_Provider* self, bool state);
    TinyCLR_Result(*GetIsRequestToSendEnabled)(const TinyCLR_Uart_Provider* self, bool& state);
    TinyCLR_Result(*SetIsRequestToSendEnabled)(const TinyCLR_Uart_Provider* self, bool state);
    TinyCLR_Result(*GetReadBufferSize)(const TinyCLR_Uart_Provider* self, size_t& size);
    TinyCLR_Result(*SetReadBufferSize)(const TinyCLR_Uart_Provider* self, size_t size);
    TinyCLR_Result(*GetWriteBufferSize)(const TinyCLR_Uart_Provider* self, size_t& size);
    TinyCLR_Result(*SetWriteBufferSize)(const TinyCLR_Uart_Provider* self, size_t size);
};

////////////////////////////////////////////////////////////////////////////////
//USB Client
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_UsbClient_Provider;

enum class TinyCLR_UsbClient_PipeMode : uint32_t {
    In = 0,
    Out = 1,
    InOut = 2,
};

enum class TinyCLR_UsbClient_EndpointAttribute : uint32_t {
    Isochronous = 0,
    Bulk = 1,
    Interrupt = 2,
};

enum class TinyCLR_UsbClient_StringDescriptorType : uint32_t {
    ManufacturerName = 0,
    ProductName = 1,
    DisplayName = 2,
    FriendlyName = 3,
};

typedef void(*TinyCLR_UsbClient_DataReceivedHandler)(const TinyCLR_UsbClient_Provider* self);
typedef void(*TinyCLR_UsbClient_OsExtendedPropertyHandler)(const TinyCLR_UsbClient_Provider* self, uint8_t*& osString, uint8_t*& osXCompatibleId, uint8_t*& osXPropertiesWinUsb);

struct TinyCLR_UsbClient_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    TinyCLR_Result(*Acquire)(const TinyCLR_UsbClient_Provider* self);
    TinyCLR_Result(*Release)(const TinyCLR_UsbClient_Provider* self);
    TinyCLR_Result(*Open)(const TinyCLR_UsbClient_Provider* self, int32_t& pipe, TinyCLR_UsbClient_PipeMode mode);
    TinyCLR_Result(*Close)(const TinyCLR_UsbClient_Provider* self, int32_t pipe);
    TinyCLR_Result(*Write)(const TinyCLR_UsbClient_Provider* self, int32_t pipe, const uint8_t* data, size_t& length);
    TinyCLR_Result(*Read)(const TinyCLR_UsbClient_Provider* self, int32_t pipe, uint8_t* data, size_t& length);
    TinyCLR_Result(*Flush)(const TinyCLR_UsbClient_Provider* self, int32_t pipe);
    TinyCLR_Result(*SetDeviceDescriptor)(const TinyCLR_UsbClient_Provider* self, const void* descriptor, int32_t length);
    TinyCLR_Result(*SetConfigDescriptor)(const TinyCLR_UsbClient_Provider* self, const void* descriptor, int32_t length);
    TinyCLR_Result(*SetStringDescriptor)(const TinyCLR_UsbClient_Provider* self, TinyCLR_UsbClient_StringDescriptorType type, const wchar_t* value);
    TinyCLR_Result(*SetDataReceivedHandler)(const TinyCLR_UsbClient_Provider* self, TinyCLR_UsbClient_DataReceivedHandler handler);
    TinyCLR_Result(*SetOsExtendedPropertyHandler)(const TinyCLR_UsbClient_Provider* self, TinyCLR_UsbClient_OsExtendedPropertyHandler handler);
};

////////////////////////////////////////////////////////////////////////////////
//USB Host
////////////////////////////////////////////////////////////////////////////////
struct TinyCLR_UsbHost_Provider {
    const TinyCLR_Api_Info* Parent;
    size_t Index;

    //TODO
};
