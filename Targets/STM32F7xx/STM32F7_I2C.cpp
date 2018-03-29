// Copyright Microsoft Corporation
// Copyright Oberon microsystems, Inc
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

#include "STM32F7.h"

#ifdef INCLUDE_I2C

typedef enum
{
	HAL_I2C_MODE_NONE = 0x00U,   /*!< No I2C communication on going             */
	HAL_I2C_MODE_MASTER = 0x10U,   /*!< I2C communication is in Master Mode       */
	HAL_I2C_MODE_SLAVE = 0x20U,   /*!< I2C communication is in Slave Mode        */
	HAL_I2C_MODE_MEM = 0x40U    /*!< I2C communication is in Memory Mode       */

} HAL_I2C_ModeTypeDef;

#define  I2C_NO_STARTSTOP               (0x00000000U)
#define  I2C_GENERATE_STOP              (uint32_t)(0x80000000U | I2C_CR2_STOP)
#define  I2C_GENERATE_START_READ        (uint32_t)(0x80000000U | I2C_CR2_START | I2C_CR2_RD_WRN)
#define  I2C_GENERATE_START_WRITE       (uint32_t)(0x80000000U | I2C_CR2_START)

#define I2C_TIMINGR_FM	0x00B01B59 // timings reg for fastmode (400khz) - value calculated with STCubeMX
//#define I2C_TIMINGR_FM	0xA0110206 // timings reg for fastmode (400khz) - value calculated with STCubeMX
#define I2C_TIMINGR_SM  0x80201721 // timings reg for standard mode (100Khz) - value calculated with STCubeMX

/** @defgroup I2C_Interrupt_configuration_definition I2C Interrupt configuration definition
* @brief I2C Interrupt definition
*        Elements values convention: 0xXXXXXXXX
*           - XXXXXXXX  : Interrupt control mask
* @{
*/
#define I2C_IT_ERRI                     I2C_CR1_ERRIE
#define I2C_IT_TCI                      I2C_CR1_TCIE
#define I2C_IT_STOPI                    I2C_CR1_STOPIE
#define I2C_IT_NACKI                    I2C_CR1_NACKIE
#define I2C_IT_ADDRI                    I2C_CR1_ADDRIE
#define I2C_IT_RXI                      I2C_CR1_RXIE
#define I2C_IT_TXI                      I2C_CR1_TXIE
/**
* @}
*/

/** @defgroup I2C_Flag_definition I2C Flag definition
* @{
*/
#define I2C_FLAG_TXE                    I2C_ISR_TXE
#define I2C_FLAG_TXIS                   I2C_ISR_TXIS
#define I2C_FLAG_RXNE                   I2C_ISR_RXNE
#define I2C_FLAG_ADDR                   I2C_ISR_ADDR
#define I2C_FLAG_AF                     I2C_ISR_NACKF
#define I2C_FLAG_STOPF                  I2C_ISR_STOPF
#define I2C_FLAG_TC                     I2C_ISR_TC
#define I2C_FLAG_TCR                    I2C_ISR_TCR
#define I2C_FLAG_BERR                   I2C_ISR_BERR
#define I2C_FLAG_ARLO                   I2C_ISR_ARLO
#define I2C_FLAG_OVR                    I2C_ISR_OVR
#define I2C_FLAG_PECERR                 I2C_ISR_PECERR
#define I2C_FLAG_TIMEOUT                I2C_ISR_TIMEOUT
#define I2C_FLAG_ALERT                  I2C_ISR_ALERT
#define I2C_FLAG_BUSY                   I2C_ISR_BUSY
#define I2C_FLAG_DIR                    I2C_ISR_DIR



#define __HAL_I2C_CLEAR_FLAG(__HANDLE__, __FLAG__)				(((__FLAG__) == I2C_FLAG_TXE) ? ((__HANDLE__)->ISR |= (__FLAG__)) : ((__HANDLE__)->ICR = (__FLAG__)))

#define __HAL_I2C_ENABLE(__HANDLE__)                            (SET_BIT((__HANDLE__)->Instance->CR1,  I2C_CR1_PE))
#define __HAL_I2C_DISABLE(__HANDLE__)                           (CLEAR_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE))
#define __HAL_I2C_GENERATE_NACK(__HANDLE__)                     (SET_BIT((__HANDLE__)->Instance->CR2, I2C_CR2_NACK))

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void STM32F7_I2c_StartTransaction(int32_t port_id);
void STM32F7_I2c_StopTransaction(int32_t port_id);

static const STM32F7_Gpio_Pin g_STM32F7_I2c_Scl_Pins[] = STM32F7_I2C_SCL_PINS;
static const STM32F7_Gpio_Pin g_STM32F7_I2c_Sda_Pins[] = STM32F7_I2C_SDA_PINS;

static const int TOTAL_I2C_CONTROLLERS = SIZEOF_ARRAY(g_STM32F7_I2c_Scl_Pins);

static I2C_TypeDef* g_STM32_I2c_Port[TOTAL_I2C_CONTROLLERS];

#define I2C_TRANSACTION_TIMEOUT 2000 // 2 seconds

struct STM32F7_I2c_Configuration {

    int32_t					address;
    uint32_t				clockRate;     // primary clock factor to generate the i2c clock reg TIMINGR
    uint8_t                 clockRate2;   // additional clock factors, if more than one is needed for the clock (optional)
};
struct STM32F7_I2c_Transaction {
    bool                        isReadTransaction;
    bool                        repeatedStart;
    bool                        isDone;

    uint8_t                     *buffer;

    size_t                      bytesToTransfer;
    size_t                      bytesTransferred;

    TinyCLR_I2c_TransferStatus  result;
};

static STM32F7_I2c_Configuration g_I2cConfiguration[TOTAL_I2C_CONTROLLERS];
static STM32F7_I2c_Transaction   *g_currentI2cTransactionAction[TOTAL_I2C_CONTROLLERS];
static STM32F7_I2c_Transaction   g_ReadI2cTransactionAction[TOTAL_I2C_CONTROLLERS];
static STM32F7_I2c_Transaction   g_WriteI2cTransactionAction[TOTAL_I2C_CONTROLLERS];

static uint8_t i2cProviderDefs[TOTAL_I2C_CONTROLLERS * sizeof(TinyCLR_I2c_Provider)];
static TinyCLR_I2c_Provider* i2cProvider[TOTAL_I2C_CONTROLLERS];
static TinyCLR_Api_Info i2cApi;

const TinyCLR_Api_Info* STM32F7_I2c_GetApi() {
    for (auto i = 0; i < TOTAL_I2C_CONTROLLERS; i++) {
        i2cProvider[i] = (TinyCLR_I2c_Provider*)(i2cProviderDefs + (i * sizeof(TinyCLR_I2c_Provider)));
        i2cProvider[i]->Parent = &i2cApi;
        i2cProvider[i]->Index = i;
        i2cProvider[i]->Acquire = &STM32F7_I2c_Acquire;
        i2cProvider[i]->Release = &STM32F7_I2c_Release;
        i2cProvider[i]->SetActiveSettings = &STM32F7_I2c_SetActiveSettings;
        i2cProvider[i]->Read = &STM32F7_I2c_Read;
        i2cProvider[i]->Write = &STM32F7_I2c_Write;
        i2cProvider[i]->WriteRead = &STM32F7_I2c_WriteRead;
    }

    i2cApi.Author = "GHI Electronics, LLC";
    i2cApi.Name = "GHIElectronics.TinyCLR.NativeApis.STM32F7.I2cProvider";
    i2cApi.Type = TinyCLR_Api_Type::I2cProvider;
    i2cApi.Version = 0;
    i2cApi.Count = TOTAL_I2C_CONTROLLERS;
    i2cApi.Implementation = (i2cApi.Count > 1) ? i2cProvider : (TinyCLR_I2c_Provider**)&i2cProviderDefs;

    if (TOTAL_I2C_CONTROLLERS > 0)
        g_STM32_I2c_Port[0] = I2C1;

    if (TOTAL_I2C_CONTROLLERS > 1)
        g_STM32_I2c_Port[1] = I2C2;

    if (TOTAL_I2C_CONTROLLERS > 2)
        g_STM32_I2c_Port[2] = I2C3;

    if (TOTAL_I2C_CONTROLLERS > 3)
        g_STM32_I2c_Port[3] = I2C4;

    for (auto i = 0; i < TOTAL_I2C_CONTROLLERS; i++) {
        STM32F7_I2c_Release(i2cProvider[i]);
        g_I2cConfiguration[i].address = 0;
        g_I2cConfiguration[i].clockRate = 0;
        g_I2cConfiguration[i].clockRate2 = 0; // not used on F7

        g_ReadI2cTransactionAction[i].bytesToTransfer = 0;
        g_ReadI2cTransactionAction[i].bytesTransferred = 0;

        g_WriteI2cTransactionAction[i].bytesToTransfer = 0;
        g_WriteI2cTransactionAction[i].bytesTransferred = 0;
    }

    return &i2cApi;
}


// Error Interrupt Handle
void STM32F7_I2C_ER_Interrupt(int32_t port_id) {
    INTERRUPT_STARTED_SCOPED(isr);

    g_STM32_I2c_Port[port_id]->ICR = I2C_ICR_ALERTCF | I2C_ICR_TIMOUTCF | I2C_ICR_OVRCF; // reset errors

    if (g_currentI2cTransactionAction[port_id] != nullptr)
        g_currentI2cTransactionAction[port_id]->result = TinyCLR_I2c_TransferStatus::SlaveAddressNotAcknowledged;


    STM32F7_I2c_StopTransaction(port_id);
}



// Event Interrupt Handler
void STM32F7_I2C_EV_Interrupt(int32_t port_id) {
    INTERRUPT_STARTED_SCOPED(isr);

    auto& I2Cx = g_STM32_I2c_Port[port_id];

    STM32F7_I2c_Transaction *transaction = g_currentI2cTransactionAction[port_id];

    int todo = transaction->bytesToTransfer;
    uint32_t isr_r = I2Cx->ISR;  // read status register
    uint32_t cr1 = I2Cx->CR1;  // initial control register
	uint32_t cr2 = I2Cx->CR2;

	uint8_t nbytes = 0;

	
    //transaction->isReadTransaction { // read transaction
	if (((isr_r & I2C_ISR_NACKF) != 0 ) && (( cr1 & I2C_CR1_NACKIE) != 0 )) {
			// Error .... to do
			__HAL_I2C_CLEAR_FLAG(I2Cx, I2C_FLAG_AF);
			STM32F7_I2c_StopTransaction(port_id);
	}
	else if (((isr_r & I2C_ISR_RXNE) != 0) && ((cr1 & I2C_CR1_RXIE ) != 0 )) {
			uint8_t data = I2Cx->RXDR; // read data
			transaction->buffer[transaction->bytesTransferred] = data; // save data
			transaction->bytesTransferred++;
			transaction->bytesToTransfer--; // update todo
			//usr_r = I2Cx->ISR;  // update status register copy				
	}
    else if (((isr_r & I2C_ISR_TXIS) != 0) && ((cr1 & I2C_CR1_TXIE) != 0)) {// write transaction
			I2Cx->TXDR = transaction->buffer[transaction->bytesTransferred]; // next data byte;
			transaction->bytesTransferred++;
			transaction->bytesToTransfer--; // update todo
			//isr_r = I2Cx->ISR;  // update status register copy		
	}
	else if (((isr_r & I2C_ISR_TCR) != 0) && ((cr1 & I2C_CR1_TCIE) != 0)) {
		// not used
		//I2Cx->CR2 |= I2C_CR2_STOP;
		//STM32F7_I2c_StopTransaction(port_id);
	}
	else if (((isr_r & I2C_ISR_TC) != 0) && ((cr1 & I2C_CR1_TCIE) != 0)) { // transfer complete
		// not used
		//I2Cx->CR2 |= I2C_CR2_STOP;
		//STM32F7_I2c_StopTransaction(port_id);
	}
	else if (((isr_r & I2C_ISR_STOPF) != 0) && ((cr1 & I2C_CR1_STOPIE) != 0)) {
		//STM32F7_I2c_StopTransaction(port_id);
	}

	if (transaction->bytesToTransfer == 0) {
		STM32F7_I2c_StopTransaction(port_id);
	}

	I2Cx->ICR |= I2C_ICR_STOPCF | I2C_ICR_ADDRCF | I2C_ICR_ALERTCF | I2C_ICR_TIMOUTCF | I2C_ICR_NACKCF;
}

// Error interrupt
void STM32F7_I2C1_ER_Interrupt(void *param) {
    STM32F7_I2C_ER_Interrupt(0);
}

void STM32F7_I2C2_ER_Interrupt(void *param) {
    STM32F7_I2C_ER_Interrupt(1);
}

void STM32F7_I2C3_ER_Interrupt(void *param) {
    STM32F7_I2C_ER_Interrupt(2);
}

void STM32F7_I2C4_ER_Interrupt(void *param) {
    STM32F7_I2C_ER_Interrupt(3);
}

// Event interrupt
void STM32F7_I2C1_EV_Interrupt(void *param) {
    STM32F7_I2C_EV_Interrupt(0);
}

void STM32F7_I2C2_EV_Interrupt(void *param) {
    STM32F7_I2C_EV_Interrupt(1);
}

void STM32F7_I2C3_EV_Interrupt(void *param) {
    STM32F7_I2C_EV_Interrupt(2);
}

void STM32F7_I2C4_EV_Interrupt(void *param) {
	STM32F7_I2C_EV_Interrupt(3);
}


void STM32F7_I2c_StartTransaction(int32_t port_id) {
    auto& I2Cx = g_STM32_I2c_Port[port_id];

	uint32_t Request = 0;
	uint32_t timingr = g_I2cConfiguration[port_id].clockRate; //+ (g_I2cConfiguration[port_id].clockRate2 << 8);
	I2Cx->TIMINGR = timingr;

	if (g_currentI2cTransactionAction[port_id]->isReadTransaction) {
		Request = I2C_GENERATE_START_READ;
	}
	else {
		Request = I2C_GENERATE_START_WRITE;
	}
	I2Cx->CR1 |= I2C_CR1_PE; // enable i2c and reset special flags

	uint32_t Mode = I2C_CR2_AUTOEND;
	uint32_t Size = g_currentI2cTransactionAction[port_id]->bytesToTransfer;
	uint32_t DevAddress = (g_I2cConfiguration[port_id].address) << 1;

	MODIFY_REG(I2Cx->CR2, ((I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | (I2C_CR2_RD_WRN & (uint32_t)(Request >> (31U - I2C_CR2_RD_WRN_Pos))) | I2C_CR2_START | I2C_CR2_STOP)), \
							(uint32_t)(((uint32_t)DevAddress & I2C_CR2_SADD) | (((uint32_t)Size << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES) | (uint32_t)Mode | (uint32_t)Request) );

	if (g_currentI2cTransactionAction[port_id]->isReadTransaction) {
		I2Cx->CR1 |= I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_RXIE; // | I2C_CR1_STOPIE | I2C_CR1_TCIE
	}
	else {
		I2Cx->CR1 |= I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_TXIE; // | I2C_CR1_STOPIE | I2C_CR1_TCIE
	}
}

void STM32F7_I2c_StopTransaction(int32_t port_id) {
    auto& I2Cx = g_STM32_I2c_Port[port_id];

    //if (I2Cx->ISR & I2C_ISR_BUSY && !(I2Cx->CR2 & I2C_CR2_STOP)) {
        //I2Cx->CR2 |= I2C_CR2_STOP; // send stop
    //}

    I2Cx->CR1 &= ~(I2C_CR1_ERRIE | I2C_CR1_NACKIE | I2C_CR1_TXIE | I2C_CR1_RXIE ); // disable interrupts
	
	// disable the i2c PE bit of I2C_CR1 ? This means reset the i2c setting any time
	//I2Cx->CR1 &= ~(I2C_CR1_PE);

    g_currentI2cTransactionAction[port_id]->isDone = true;
}

TinyCLR_Result STM32F7_I2c_Read(const TinyCLR_I2c_Provider* self, uint8_t* buffer, size_t& length, TinyCLR_I2c_TransferStatus& result) {
    int32_t timeout = I2C_TRANSACTION_TIMEOUT;
    int32_t port_id = self->Index;

    g_ReadI2cTransactionAction[port_id].isReadTransaction = true;
    g_ReadI2cTransactionAction[port_id].buffer = buffer;
    g_ReadI2cTransactionAction[port_id].bytesToTransfer = length;
    g_ReadI2cTransactionAction[port_id].isDone = false;
    g_ReadI2cTransactionAction[port_id].repeatedStart = false;
    g_ReadI2cTransactionAction[port_id].bytesTransferred = 0;

    g_currentI2cTransactionAction[port_id] = &g_ReadI2cTransactionAction[port_id];

    STM32F7_I2c_StartTransaction(port_id);

    while (g_currentI2cTransactionAction[port_id]->isDone == false && timeout > 0) {
        STM32F7_Time_Delay(nullptr, 1000);

        timeout--;
    }

    if (g_currentI2cTransactionAction[port_id]->bytesTransferred == length)
        result = TinyCLR_I2c_TransferStatus::FullTransfer;
    else if (g_currentI2cTransactionAction[port_id]->bytesTransferred < length && g_currentI2cTransactionAction[port_id]->bytesTransferred > 0)
        result = TinyCLR_I2c_TransferStatus::PartialTransfer;

    length = g_currentI2cTransactionAction[port_id]->bytesTransferred;

    return timeout > 0 ? TinyCLR_Result::Success : TinyCLR_Result::TimedOut;
}

TinyCLR_Result STM32F7_I2c_Write(const TinyCLR_I2c_Provider* self, const uint8_t* buffer, size_t& length, TinyCLR_I2c_TransferStatus& result) {
    int32_t timeout = I2C_TRANSACTION_TIMEOUT;
    int32_t port_id = self->Index;

    g_WriteI2cTransactionAction[port_id].isReadTransaction = false;
    g_WriteI2cTransactionAction[port_id].buffer = (uint8_t*)buffer;
    g_WriteI2cTransactionAction[port_id].bytesToTransfer = length;
    g_WriteI2cTransactionAction[port_id].isDone = false;
    g_WriteI2cTransactionAction[port_id].repeatedStart = false;
    g_WriteI2cTransactionAction[port_id].bytesTransferred = 0;

    g_currentI2cTransactionAction[port_id] = &g_WriteI2cTransactionAction[port_id];

    STM32F7_I2c_StartTransaction(port_id);

    while (g_currentI2cTransactionAction[port_id]->isDone == false && timeout > 0) {
        STM32F7_Time_Delay(nullptr, 1000);

        timeout--;
    }

    if (g_currentI2cTransactionAction[port_id]->bytesTransferred == length)
        result = TinyCLR_I2c_TransferStatus::FullTransfer;
    else if (g_currentI2cTransactionAction[port_id]->bytesTransferred < length && g_currentI2cTransactionAction[port_id]->bytesTransferred > 0)
        result = TinyCLR_I2c_TransferStatus::PartialTransfer;

    length = g_currentI2cTransactionAction[port_id]->bytesTransferred;

    return timeout > 0 ? TinyCLR_Result::Success : TinyCLR_Result::TimedOut;
}

TinyCLR_Result STM32F7_I2c_WriteRead(const TinyCLR_I2c_Provider* self, const uint8_t* writeBuffer, size_t& writeLength, uint8_t* readBuffer, size_t& readLength, TinyCLR_I2c_TransferStatus& result) {
    int32_t timeout = I2C_TRANSACTION_TIMEOUT;
    int32_t port_id = self->Index;

    g_WriteI2cTransactionAction[port_id].isReadTransaction = false;
    g_WriteI2cTransactionAction[port_id].buffer = (uint8_t*)writeBuffer;
    g_WriteI2cTransactionAction[port_id].bytesToTransfer = writeLength;
    g_WriteI2cTransactionAction[port_id].isDone = false;
    g_WriteI2cTransactionAction[port_id].repeatedStart = true;
    g_WriteI2cTransactionAction[port_id].bytesTransferred = 0;

    g_ReadI2cTransactionAction[port_id].isReadTransaction = true;
    g_ReadI2cTransactionAction[port_id].buffer = readBuffer;
    g_ReadI2cTransactionAction[port_id].bytesToTransfer = readLength;
    g_ReadI2cTransactionAction[port_id].isDone = false;
    g_ReadI2cTransactionAction[port_id].repeatedStart = false;
    g_ReadI2cTransactionAction[port_id].bytesTransferred = 0;

    g_currentI2cTransactionAction[port_id] = &g_WriteI2cTransactionAction[port_id];

    STM32F7_I2c_StartTransaction(port_id);

    while (g_currentI2cTransactionAction[port_id]->isDone == false && timeout > 0) {
        STM32F7_Time_Delay(nullptr, 1000);

        timeout--;
    }

    if (g_WriteI2cTransactionAction[port_id].bytesTransferred != writeLength) {
        writeLength = g_WriteI2cTransactionAction[port_id].bytesTransferred;
        result = TinyCLR_I2c_TransferStatus::PartialTransfer;
    }
    else {
        readLength = g_ReadI2cTransactionAction[port_id].bytesTransferred;

        if (g_currentI2cTransactionAction[port_id]->bytesTransferred == readLength)
            result = TinyCLR_I2c_TransferStatus::FullTransfer;
        else if (g_currentI2cTransactionAction[port_id]->bytesTransferred < readLength && g_currentI2cTransactionAction[port_id]->bytesTransferred > 0)
            result = TinyCLR_I2c_TransferStatus::PartialTransfer;
    }

    return timeout > 0 ? TinyCLR_Result::Success : TinyCLR_Result::TimedOut;
}

TinyCLR_Result STM32F7_I2c_SetActiveSettings(const TinyCLR_I2c_Provider* self, int32_t slaveAddress, TinyCLR_I2c_BusSpeed busSpeed) {
    uint32_t rateKhz;
    uint32_t timingr;

    int32_t port_id = self->Index;

    if (busSpeed == TinyCLR_I2c_BusSpeed::FastMode)
        rateKhz = 400; // FastMode
    else if (busSpeed == TinyCLR_I2c_BusSpeed::StandardMode)
        rateKhz = 100; // StandardMode
    else
        return TinyCLR_Result::NotSupported;

    if (rateKhz <= 100) { // slow clock
		timingr = I2C_TIMINGR_SM; //(STM32F7_APB1_CLOCK_HZ / 1000 / 2 - 1) / rateKhz + 1; // round up
    }
    else { // fast clock
		timingr = I2C_TIMINGR_FM; //(STM32F7_APB1_CLOCK_HZ / 1000 / 3 - 1) / rateKhz + 1; // round up
    }

    g_I2cConfiguration[port_id].clockRate = timingr; // low byte
    g_I2cConfiguration[port_id].address = slaveAddress;



    return TinyCLR_Result::Success;
}

TinyCLR_Result STM32F7_I2c_Acquire(const TinyCLR_I2c_Provider* self) {
    if (self == nullptr)
        return TinyCLR_Result::ArgumentNull;

    int32_t port_id = self->Index;

    auto& I2Cx = g_STM32_I2c_Port[port_id];

    auto& scl = g_STM32F7_I2c_Scl_Pins[port_id];
    auto& sda = g_STM32F7_I2c_Sda_Pins[port_id];

    if (!STM32F7_GpioInternal_OpenPin(sda.number) || !STM32F7_GpioInternal_OpenPin(scl.number))
        return TinyCLR_Result::SharingViolation;

    STM32F7_GpioInternal_ConfigurePin(sda.number, STM32F7_Gpio_PortMode::AlternateFunction, STM32F7_Gpio_OutputType::OpenDrain, STM32F7_Gpio_OutputSpeed::VeryHigh, STM32F7_Gpio_PullDirection::PullUp, sda.alternateFunction);
    STM32F7_GpioInternal_ConfigurePin(scl.number, STM32F7_Gpio_PortMode::AlternateFunction, STM32F7_Gpio_OutputType::OpenDrain, STM32F7_Gpio_OutputSpeed::VeryHigh, STM32F7_Gpio_PullDirection::PullUp, scl.alternateFunction);
    switch (port_id) {
    case 0:
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // enable I2C clock
        RCC->APB1RSTR = RCC_APB1RSTR_I2C1RST; // reset I2C peripheral
        STM32F7_InterruptInternal_Activate(I2C1_EV_IRQn, (uint32_t*)&STM32F7_I2C1_EV_Interrupt, 0);
        STM32F7_InterruptInternal_Activate(I2C1_ER_IRQn, (uint32_t*)&STM32F7_I2C1_ER_Interrupt, 0);
        break;

    case 1:
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; // enable I2C clock
        RCC->APB1RSTR = RCC_APB1RSTR_I2C2RST; // reset I2C peripheral
        STM32F7_InterruptInternal_Activate(I2C2_EV_IRQn, (uint32_t*)&STM32F7_I2C2_EV_Interrupt, 0);
        STM32F7_InterruptInternal_Activate(I2C2_ER_IRQn, (uint32_t*)&STM32F7_I2C2_ER_Interrupt, 0);
        break;

    case 2:
        RCC->APB1ENR |= RCC_APB1ENR_I2C3EN; // enable I2C clock
        RCC->APB1RSTR = RCC_APB1RSTR_I2C3RST; // reset I2C peripheral
        STM32F7_InterruptInternal_Activate(I2C3_EV_IRQn, (uint32_t*)&STM32F7_I2C3_EV_Interrupt, 0);
        STM32F7_InterruptInternal_Activate(I2C3_ER_IRQn, (uint32_t*)&STM32F7_I2C3_ER_Interrupt, 0);
        break;
    case 3:
        RCC->APB1ENR |= RCC_APB1ENR_I2C4EN; // enable I2C clock
        RCC->APB1RSTR = RCC_APB1RSTR_I2C4RST; // reset I2C peripheral
        STM32F7_InterruptInternal_Activate(I2C4_EV_IRQn, (uint32_t*)&STM32F7_I2C4_EV_Interrupt, 0);
        STM32F7_InterruptInternal_Activate(I2C4_ER_IRQn, (uint32_t*)&STM32F7_I2C4_ER_Interrupt, 0);
        break;
    }

    RCC->APB1RSTR = 0;

	//I2Cx->TIMINGR = I2C_TIMINGR_FM; // initialize in fast mode
    //I2Cx->OAR1 = I2C_OAR1_OA1EN; // init address register
	
	//I2Cx->TIMINGR = timingr;
	
    //I2Cx->CR1 |= I2C_CR1_PE; // enable peripheral

    return TinyCLR_Result::Success;
}

TinyCLR_Result STM32F7_I2c_Release(const TinyCLR_I2c_Provider* self) {
    if (self == nullptr)
        return TinyCLR_Result::ArgumentNull;

    int32_t port_id = self->Index;

    auto& I2Cx = g_STM32_I2c_Port[port_id];
    auto& scl = g_STM32F7_I2c_Scl_Pins[port_id];
    auto& sda = g_STM32F7_I2c_Sda_Pins[port_id];

    switch (port_id) {
    case 0:
        STM32F7_InterruptInternal_Deactivate(I2C1_EV_IRQn);
        STM32F7_InterruptInternal_Deactivate(I2C1_ER_IRQn);

        I2Cx->CR1 = 0; // disable peripheral
        RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN; // disable I2C clock
        break;

    case 1:
        STM32F7_InterruptInternal_Deactivate(I2C2_EV_IRQn);
        STM32F7_InterruptInternal_Deactivate(I2C2_ER_IRQn);

        I2Cx->CR1 = 0; // disable peripheral
        RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN; // disable I2C clock
        break;

    case 2:
        STM32F7_InterruptInternal_Deactivate(I2C3_EV_IRQn);
        STM32F7_InterruptInternal_Deactivate(I2C3_ER_IRQn);

        I2Cx->CR1 = 0; // disable peripheral
        RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN; // disable I2C clock

        break;
    case 3:
        STM32F7_InterruptInternal_Deactivate(I2C4_EV_IRQn);
        STM32F7_InterruptInternal_Deactivate(I2C4_ER_IRQn);

        I2Cx->CR1 = 0; // disable peripheral
        RCC->APB1ENR &= ~RCC_APB1ENR_I2C4EN; // disable I2C clock

        break;
    }

    STM32F7_GpioInternal_ClosePin(sda.number);
    STM32F7_GpioInternal_ClosePin(scl.number);

    return TinyCLR_Result::Success;
}

#endif // INCLDE_I2C