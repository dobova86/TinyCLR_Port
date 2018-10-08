// Copyright Microsoft Corporation
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

#include "LPC24.h"

#define VECTORING_GUARD  32
#define DEFINE_IRQ(index) { index, { NULL, (void*)(size_t)index } }
#define DISABLED_MASK 0x80

extern "C" {
    uint32_t    IRQ_LOCK_Release_asm();
    void        IRQ_LOCK_Probe_asm();
    uint32_t    IRQ_LOCK_GetState_asm();
    uint32_t    IRQ_LOCK_ForceDisabled_asm();
    uint32_t    IRQ_LOCK_ForceEnabled_asm();
    uint32_t    IRQ_LOCK_Disable_asm();
    void        IRQ_LOCK_Restore_asm();
}

typedef void(*LPC24_Interrupt_Handler)(void* arg);

struct LPC24_Interrupt_Callback {

public:
    void* EntryPoint;
    void* Argument;

public:
    void Initialize(uint32_t* EntryPoint, void* Argument) {
        this->EntryPoint = (void*)EntryPoint;
        this->Argument = Argument;
    }

    void Execute() const {
        LPC24_Interrupt_Handler EntryPoint = (LPC24_Interrupt_Handler)this->EntryPoint;

        void* Argument = this->Argument;

        if (EntryPoint) {
            EntryPoint(Argument);
        }
    }
};

struct LPC24_Interrupt_Vectors {
    uint32_t                    Index;
    LPC24_Interrupt_Callback    Handler;
};

static LPC24_Interrupt_Vectors* LPC24_Interrupt_IrqToVector(uint32_t Irq);

LPC24_Interrupt_Vectors s_IsrTable[] =
{
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_WDT),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_SW),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_DBG_COM_RX),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_DBG_COM_TX),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_TIMER0),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_TIMER1),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_UART0),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_UART1),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_PWM_0_1),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_I2C0),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_SPI_SSP0),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_SSP1),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_PLL),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_RTC),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_EINT0),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_EINT1),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_EINT2_LCD),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_EINT3),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_ADC0),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_I2C1),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_BOD),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_EMAC),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_USB),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_CAN),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_SD),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_DMA),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_TIMER2),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_TIMER3),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_UART2),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_UART3),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_I2C2),
    DEFINE_IRQ(LPC24XX_VIC::c_IRQ_INDEX_I2S),

    DEFINE_IRQ(VECTORING_GUARD),
};

LPC24_Interrupt_Vectors* LPC24_Interrupt_IrqToVector(uint32_t Irq) {
    LPC24_Interrupt_Vectors* IsrVector = s_IsrTable;

    while (IsrVector->Index != VECTORING_GUARD) {
        if (IsrVector->Index == Irq) return IsrVector;

        IsrVector++;
    }

    return NULL;
}

void LPC24_Interrupt_StubIrqVector(void* Param) {

}

#define TOTAL_INTERRUPT_CONTROLLERS 1

TinyCLR_Interrupt_StartStopHandler LPC24_Interrupt_Started;
TinyCLR_Interrupt_StartStopHandler LPC24_Interrupt_Ended;

struct InterruptState {
    uint32_t controllerIndex;
    bool tableInitialized;
};

const char* interruptApiNames[TOTAL_INTERRUPT_CONTROLLERS] = {
    "GHIElectronics.TinyCLR.NativeApis.LPC24.InterruptController\\0"
};

static TinyCLR_Interrupt_Controller interruptControllers[TOTAL_INTERRUPT_CONTROLLERS];
static TinyCLR_Api_Info interruptApi[TOTAL_INTERRUPT_CONTROLLERS];
static InterruptState interruptStates[TOTAL_INTERRUPT_CONTROLLERS];

void LPC24_Interrupt_EnsureTableInitialized() {
    for (auto i = 0; i < TOTAL_INTERRUPT_CONTROLLERS; i++) {
        if (interruptStates[i].tableInitialized)
            continue;

        interruptControllers[i].ApiInfo = &interruptApi[i];
        interruptControllers[i].Initialize = &LPC24_Interrupt_Initialize;
        interruptControllers[i].Uninitialize = &LPC24_Interrupt_Uninitialize;
        interruptControllers[i].Enable = &LPC24_Interrupt_Enable;
        interruptControllers[i].Disable = &LPC24_Interrupt_Disable;
        interruptControllers[i].WaitForInterrupt = &LPC24_Interrupt_WaitForInterrupt;
        interruptControllers[i].IsDisabled = &LPC24_Interrupt_IsDisabled;

        interruptApi[i].Author = "GHI Electronics, LLC";
        interruptApi[i].Name = interruptApiNames[i];
        interruptApi[i].Type = TinyCLR_Api_Type::InterruptController;
        interruptApi[i].Version = 0;
        interruptApi[i].Implementation = &interruptControllers[i];
        interruptApi[i].State = &interruptStates[i];

        interruptStates[i].controllerIndex = i;
        interruptStates[i].tableInitialized = true;
    }
}

const TinyCLR_Api_Info* LPC24_Interrupt_GetRequiredApi() {
    LPC24_Interrupt_EnsureTableInitialized();

    return &interruptApi[0];
}

void LPC24_Interrupt_AddApi(const TinyCLR_Api_Manager* apiManager) {
    LPC24_Interrupt_EnsureTableInitialized();

    for (auto i = 0; i < TOTAL_INTERRUPT_CONTROLLERS; i++) {
        apiManager->Add(apiManager, &interruptApi[i]);
    }

    apiManager->SetDefaultName(apiManager, TinyCLR_Api_Type::InterruptController, interruptApi[0].Name);
}


TinyCLR_Result LPC24_Interrupt_Initialize(const TinyCLR_Interrupt_Controller* self, TinyCLR_Interrupt_StartStopHandler onInterruptStart, TinyCLR_Interrupt_StartStopHandler onInterruptEnd) {
    LPC24_Interrupt_Started = onInterruptStart;
    LPC24_Interrupt_Ended = onInterruptEnd;

    LPC24XX_VIC& VIC = LPC24XX::VIC();

    // disable all interrupts
    VIC.INTENCLR = 0xFFFFFFFF;

    LPC24_Interrupt_Vectors* IsrVector = s_IsrTable;

    while (IsrVector->Index != VECTORING_GUARD) {
        IsrVector->Handler.Initialize((uint32_t*)&LPC24_Interrupt_StubIrqVector, (void*)(size_t)IsrVector->Index);

        IsrVector++;
    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Interrupt_Uninitialize(const TinyCLR_Interrupt_Controller* self) {
    return TinyCLR_Result::Success;
}

bool LPC24_InterruptInternal_Activate(uint32_t Irq_Index, uint32_t *ISR, void* ISR_Param) {
    // figure out the interrupt
    LPC24_Interrupt_Vectors* IsrVector = LPC24_Interrupt_IrqToVector(Irq_Index);

    if (!IsrVector)
        return false;

    {
        DISABLE_INTERRUPTS_SCOPED(irq);

        LPC24XX_VIC& VIC = LPC24XX::VIC();

        // disable this interrupt while we change it
        VIC.INTENCLR = 1 << IsrVector->Index;

        // set the vector
        IsrVector->Handler.Initialize(ISR, ISR_Param);

        // Use Vector Address register to identify the source of interrupt
        VIC.VECTADDR[Irq_Index] = Irq_Index;

        // enable the interrupt if we have a vector
        VIC.INTENABLE = 1 << IsrVector->Index;
    }

    return true;

}

bool LPC24_InterruptInternal_Deactivate(uint32_t Irq_Index) {
    // figure out the interrupt
    LPC24_Interrupt_Vectors* IsrVector = LPC24_Interrupt_IrqToVector(Irq_Index);

    if (!IsrVector)
        return false;
    {
        DISABLE_INTERRUPTS_SCOPED(irq);

        LPC24XX_VIC& VIC = LPC24XX::VIC();

        // disable this interrupt while we change it
        VIC.INTENCLR = 1 << IsrVector->Index;

        IsrVector->Handler.Initialize((uint32_t*)&LPC24_Interrupt_StubIrqVector, (void*)(size_t)IsrVector->Index);
    }

    return true;
}

LPC24_InterruptStarted_RaiiHelper::LPC24_InterruptStarted_RaiiHelper() { LPC24_Interrupt_Started(); };
LPC24_InterruptStarted_RaiiHelper::~LPC24_InterruptStarted_RaiiHelper() { LPC24_Interrupt_Ended(); };

LPC24_DisableInterrupts_RaiiHelper::LPC24_DisableInterrupts_RaiiHelper() {
    state = IRQ_LOCK_Disable_asm();
}
LPC24_DisableInterrupts_RaiiHelper::~LPC24_DisableInterrupts_RaiiHelper() {
    uint32_t Cp = state;

    if ((Cp & DISABLED_MASK) == 0) {
        state = IRQ_LOCK_Release_asm();
    }
}

bool LPC24_DisableInterrupts_RaiiHelper::IsDisabled() {
    return (state & DISABLED_MASK) == DISABLED_MASK;
}

void LPC24_DisableInterrupts_RaiiHelper::Acquire() {
    uint32_t Cp = state;

    if ((Cp & DISABLED_MASK) == DISABLED_MASK) {
        state = IRQ_LOCK_Disable_asm();
    }
}

void LPC24_DisableInterrupts_RaiiHelper::Release() {
    uint32_t Cp = state;

    if ((Cp & DISABLED_MASK) == 0) {
        state = IRQ_LOCK_Release_asm();
    }
}

//////////////////////////////////////////////////////////////////////////////
//Global Interrupt - Use in System Cote
//////////////////////////////////////////////////////////////////////////////
bool LPC24_Interrupt_IsDisabled() {
    return ((IRQ_LOCK_GetState_asm() & DISABLED_MASK) == 0);
}

void LPC24_Interrupt_Enable() {
    IRQ_LOCK_Release_asm();
}

void LPC24_Interrupt_Disable() {
    IRQ_LOCK_Disable_asm();
}

void LPC24_Interrupt_WaitForInterrupt() {
    IRQ_LOCK_Probe_asm();
}

extern "C" {
    void LPC24_Interrupt_UndefHandler(unsigned int*, unsigned int, unsigned int) {
        volatile uint32_t debug = 0;

        while (debug == 0) {
            debug += debug;
        }
    }

    void LPC24_Interrupt_AbortpHandler(unsigned int*, unsigned int, unsigned int) {
        volatile uint32_t debug = 0;

        while (debug == 0) {
            debug += debug;
        }
    }

    void LPC24_Interrupt_AbortdHandler(unsigned int*, unsigned int, unsigned int) {
        volatile uint32_t debug = 0;
        while (debug == 0) {
            debug += debug;
        }
    }

    void __attribute__((interrupt("IRQ"))) IRQ_Handler(void *param) {
        // set before jumping elsewhere or allowing other interrupts
        INTERRUPT_STARTED_SCOPED(isr);

        uint32_t index;

        LPC24XX_VIC& VIC = LPC24XX::VIC();

        index = VIC.ADDRESS;

        LPC24_Interrupt_Vectors* IsrVector = &s_IsrTable[index];

        // In case the interrupt was forced, remove the flag.
        VIC.RemoveForcedInterrupt(index);

        IsrVector->Handler.Execute();

        // Reset VIC priority hw logic.
        VIC.ADDRESS = 0xFF;
    }
}
