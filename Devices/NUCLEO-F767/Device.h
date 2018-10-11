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

#define STM32F767xx 

#include <STM32F7.h>



#define DEVICE_TARGET STM32F7
#define DEVICE_NAME "NUCLEO-F767"
#define DEVICE_MANUFACTURER "Nucleo STM32F767"
#define DEVICE_VERSION ((1ULL << 48) | (0ULL << 32) | (0ULL << 16) | (10001ULL << 0))

#define USB_DEBUGGER_VENDOR_ID 0x1B9F
#define USB_DEBUGGER_PRODUCT_ID 0x5000

#define UART_DEBUGGER_INDEX 0
#define USB_DEBUGGER_INDEX 0

//#define DEBUGGER_SELECTOR_PIN PIN(B, 13)
//#define DEBUGGER_SELECTOR_PULL TinyCLR_Gpio_PinDriveMode::InputPullUp
//#define DEBUGGER_SELECTOR_USB_STATE TinyCLR_Gpio_PinValue::High
#define DEBUGGER_FORCE_API STM32F7_UsbDevice_GetRequiredApi()
//#define DEBUGGER_FORCE_API STM32F7_Uart_GetApi()
#define DEBUGGER_FORCE_INDEX USB_DEBUGGER_INDEX


//#define RUN_APP_PIN PIN(E, 4)
//#define RUN_APP_PULL TinyCLR_Gpio_PinDriveMode::InputPullUp
//#define RUN_APP_STATE TinyCLR_Gpio_PinValue::High
#define RUN_APP_FORCE_STATE true

#define DEVICE_MEMORY_PROFILE_FACTOR 9


#define DEPLOYMENT_SECTORS 	{\
								{ 0x06, 0x08080000, 0x00040000 }, { 0x07, 0x080C0000, 0x00040000 },\
								{ 0x08, 0x08100000, 0x00040000 }, { 0x09, 0x08140000, 0x00040000 },\
								{ 0x0A, 0x08180000, 0x00040000 }, { 0x0B, 0x081C0000, 0x00040000 }\
							 } //,



#define STM32F7_SYSTEM_CLOCK_HZ 216000000	 // 168000000 // 180000000 // 216000000
#define STM32F7_AHB_CLOCK_HZ	216000000	 // 168000000 // 180000000 // 216000000
#define STM32F7_APB1_CLOCK_HZ	54000000	 // 42000000  // 45000000  //  54000000
#define STM32F7_APB2_CLOCK_HZ	108000000	 // 84000000  // 90000000 //  108000000
#define STM32F7_EXT_CRYSTAL_CLOCK_HZ 8000000
#define STM32F7_SUPPLY_VOLTAGE_MV 3300

#define INCLUDE_ADC

#define INCLUDE_CAN
#define TOTAL_CAN_CONTROLLERS 1
#define STM32F7_CAN_BUFFER_DEFAULT_SIZE { 128 }
#define STM32F7_CAN_TX_PINS { { PIN(D, 1), AF(9) } }
#define STM32F7_CAN_RX_PINS { { PIN(D, 0), AF(9) } }

#define INCLUDE_DAC

#define INCLUDE_GPIO
#define STM32F7_GPIO_PINS {/*      0          1          2          3          4          5          6          7          8          9          10         11         12         13         14         15      */\
						   /*PAx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PBx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PCx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PDx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PEx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PFx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PGx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), DEFAULT(),\
						   /*PHx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PIx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PJx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PKx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						  }

#define INCLUDE_I2C			// NOTE: I2C1 on Nucleo is not connected to CN9 by default (see Nucleo-144 user guide)
#define TOTAL_I2C_CONTROLLERS 2
#define STM32F7_I2C_SCL_PINS { { PIN(B, 8), AF(4) }, { PIN(F, 1), AF(4) } }
#define STM32F7_I2C_SDA_PINS { { PIN(B, 9), AF(4) }, { PIN(F, 0), AF(4) } }

#define INCLUDE_PWM
#define TOTAL_PWM_CONTROLLERS 14
#define STM32F7_PWM_PINS {/* CH         1                          2                        3                        4                       */\
						  /* TIM1  */ { { PIN(E,  9), AF(1)   }, { PIN(E, 11), AF(1)   }, { PIN(E, 13), AF(1)   }, { PIN_NONE  , AF_NONE } },\
						  /* TIM2  */ { { PIN(A,  0), AF(1)   }, { PIN_NONE  , AF_NONE }, { PIN(B, 10), AF(1)   }, { PIN(B, 11), AF(1)   } },\
						  /* TIM3  */ { { PIN_NONE  , AF_NONE }, { PIN(B,  5), AF(2)   }, { PIN(B,  0), AF(2)   }, { PIN_NONE  , AF_NONE } },\
						  /* TIM4  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN(D, 14), AF(2)   }, { PIN(D, 15), AF(2)   } },\
						  /* TIM5  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM6  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM7  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM8  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM9  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM10 */ { { PIN(F,  6), AF(3)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM11 */ { { PIN(F,  7), AF(3)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM12 */ { { PIN(H,  6), AF(9)   }, { PIN(B, 15), AF(9)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM13 */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM14 */ { { PIN(A,  7), AF(9)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						 }

#define INCLUDE_SIGNALS

#define INCLUDE_SPI
#define TOTAL_SPI_CONTROLLERS 2
#define STM32F7_SPI_SCLK_PINS { { PIN(A, 5), AF(5) }, { PIN(A,12), AF(5) } } //, { PIN(B, 10), AF(5) } }
#define STM32F7_SPI_MISO_PINS { { PIN(A, 6), AF(5) }, { PIN(B,14), AF(5) } } //, { PIN(C,  2), AF(5) } }
#define STM32F7_SPI_MOSI_PINS { { PIN(A, 7), AF(5) }, { PIN(B,15), AF(5) } } //, { PIN(C,  3), AF(5) } }

// UART note: PB6,PB7 mapped to UART1 can be used on CN1-CN2 connectors
#define INCLUDE_UART
#define TOTAL_UART_CONTROLLERS 6	 /* ST-LINK USART3: TX-PD8, RX-PD9 (AF7) */
#define STM32F7_UART_DEFAULT_TX_BUFFER_SIZE  { 256, 256, 256, 256, 256, 256 }
#define STM32F7_UART_DEFAULT_RX_BUFFER_SIZE  { 512, 512, 512, 512, 512, 512 }	
#define STM32F7_UART_TX_PINS  { { PIN_NONE , AF_NONE }, { PIN(D,  5), AF(7)  }, { PIN(D, 8) , AF(7) }, { PIN(D, 1) , AF(8)  }, { PIN_NONE , AF_NONE }, { PIN(G,14), AF(8) } }
#define STM32F7_UART_RX_PINS  { { PIN_NONE , AF_NONE }, { PIN(D,  6), AF(7)  }, { PIN(D, 9) , AF(7) }, { PIN(D, 0) , AF(8)  }, { PIN_NONE , AF_NONE }, { PIN(G, 9), AF(8) } }
#define STM32F7_UART_CTS_PINS { { PIN_NONE , AF_NONE }, { PIN(D,  3), AF(7)  }, { PIN_NONE , AF_NONE },{ PIN_NONE , AF_NONE }, { PIN_NONE , AF_NONE }, { PIN_NONE, AF_NONE } }
#define STM32F7_UART_RTS_PINS { { PIN_NONE , AF_NONE }, { PIN(D,  4), AF(7)  }, { PIN_NONE , AF_NONE },{ PIN_NONE , AF_NONE }, { PIN_NONE , AF_NONE }, { PIN_NONE, AF_NONE } }

#define INCLUDE_USBCLIENT
#define STM32F7_TOTAL_USB_CONTROLLERS	1
#define STM32F7_USB_PACKET_FIFO_COUNT	64
#define STM32F7_USB_ENDPOINT_SIZE		64
#define STM32F7_USB_ENDPOINT0_SIZE		8
#define STM32F7_USB_ENDPOINT_COUNT		4
#define STM32F7_USB_PIPE_COUNT			4

#define STM32F7_USB_DM_PINS { { PIN(A, 11), AF(10) } }
#define STM32F7_USB_DP_PINS { { PIN(A, 12), AF(10) } }
#define STM32F7_USB_VB_PINS { { PIN(A,  9), AF(10) } }
#define STM32F7_USB_ID_PINS { { PIN(A, 10), AF(10) } }

#define INCLUDE_RTC

#define INCLUDE_SD	// SD connectione are on CN8 (no embedded socket on nucleo)
#define STM32F7_SD_DATA0_PINS { { PIN(C, 8), AF(12) } }
#define STM32F7_SD_DATA1_PINS { { PIN(C, 9), AF(12) } }
#define STM32F7_SD_DATA2_PINS { { PIN(C,10), AF(12) } }
#define STM32F7_SD_DATA3_PINS { { PIN(C,11), AF(12) } }
#define STM32F7_SD_CLK_PINS   { { PIN(C,12), AF(12) } }
#define STM32F7_SD_CMD_PINS   { { PIN(D, 2), AF(12) } }

#define INCLUDE_STORAGE
