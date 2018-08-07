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

#define STM32F429xx 1

#include <STM32F4.h>

#define DEVICE_TARGET STM32F4
#define DEVICE_NAME "DISCO-F429ZI"
#define DEVICE_MANUFACTURER "ST Discovery F429ZI"
#define DEVICE_VERSION ((0ULL << 48) | (12ULL << 32) | (0ULL << 16) | (0ULL << 0))

#define USB_DEBUGGER_VENDOR_ID 0x1B9F
#define USB_DEBUGGER_PRODUCT_ID 0x5000

#define UART_DEBUGGER_INDEX 0
#define USB_DEBUGGER_INDEX 0

//#define DEBUGGER_SELECTOR_PIN PIN(B, 13)
//#define DEBUGGER_SELECTOR_PULL TinyCLR_Gpio_PinDriveMode::InputPullUp
//#define DEBUGGER_SELECTOR_USB_STATE TinyCLR_Gpio_PinValue::High
#define DEBUGGER_FORCE_API STM32F4_UsbClient_GetApi()
//#define DEBUGGER_FORCE_API STM32F4_Uart_GetApi()
#define DEBUGGER_FORCE_INDEX USB_DEBUGGER_INDEX


//#define RUN_APP_PIN PIN(E, 4)
//#define RUN_APP_PULL TinyCLR_Gpio_PinDriveMode::InputPullUp
//#define RUN_APP_STATE TinyCLR_Gpio_PinValue::High
#define RUN_APP_FORCE_STATE true

//#define BOOTLOADER_HOLD_ADDRESS 0x2002FFF8
//#define BOOTLOADER_HOLD_VALUE 0x37D56D4A

#define DEPLOYMENT_SECTORS {/* NOTE: F429 is 2Mb flash with dual bank org. At the moment NOT ALL sectors are activated. See text file F429_flash_mem_banks.MD  */\
							 { 0x06, 0x08040000, 0x00020000 }, { 0x07, 0x08060000, 0x00020000 }, { 0x08, 0x08080000, 0x00020000 },\
							 { 0x09, 0x080A0000, 0x00020000 }, { 0x0A, 0x080C0000, 0x00020000 }, { 0x0B, 0x080E0000, 0x00020000 },\
							 { 0x10, 0x08110000, 0x00010000 }, { 0x11, 0x08120000, 0x00020000 }, { 0x12, 0x08140000, 0x00020000 },\
							 { 0x13, 0x08160000, 0x00020000 }, { 0x14, 0x08180000, 0x00020000 }, { 0x15, 0x081A0000, 0x00020000 },\
							 { 0x16, 0x081C0000, 0x00020000 }, { 0x17, 0x081E0000, 0x00020000 },\
						 }


#define SDRAM_DATABITS 16 
#define USE_SDRAM_HEAP
#define SDRAM_PINS {\
				{ PIN(C, 0), AF(12) },\
				{ PIN(D, 0), AF(12) }, { PIN(D, 1), AF(12) }, { PIN(D, 8), AF(12) }, { PIN(D, 9), AF(12) }, { PIN(D,10), AF(12) }, { PIN(D,14), AF(12) }, { PIN(D,15), AF(12) },\
				{ PIN(E, 0), AF(12) }, { PIN(E, 1), AF(12) }, { PIN(E, 7), AF(12) }, { PIN(E, 8), AF(12) },	{ PIN(E, 9), AF(12) }, { PIN(E,10), AF(12) },\
				{ PIN(E,11), AF(12) }, { PIN(E,12), AF(12) }, { PIN(E,13), AF(12) }, { PIN(E,14), AF(12) },	{ PIN(E,15), AF(12) },\
				{ PIN(F, 0), AF(12) }, { PIN(F, 1), AF(12) }, { PIN(F, 2), AF(12) }, { PIN(F, 3), AF(12) }, { PIN(F, 4), AF(12) }, { PIN(F, 5), AF(12) },\
				{ PIN(F,11), AF(12) }, { PIN(F,12), AF(12) }, { PIN(F,13), AF(12) }, { PIN(F,14), AF(12) }, { PIN(F,15), AF(12) },\
				{ PIN(G, 0), AF(12) }, { PIN(G, 1), AF(12) }, { PIN(G, 8), AF(12) }, { PIN(G,15), AF(12) },\
				{ PIN(B, 5), AF(12) }, { PIN(B, 6), AF(12) },\
			}


#define STM32F4_SYSTEM_CLOCK_HZ 180000000	 // 168000000 // 180000000
#define STM32F4_AHB_CLOCK_HZ	180000000	 // 168000000 // 180000000
#define STM32F4_APB1_CLOCK_HZ	45000000	 // 42000000  // 45000000
#define STM32F4_APB2_CLOCK_HZ	90000000	 // 84000000  // 90000000
#define STM32F4_EXT_CRYSTAL_CLOCK_HZ 8000000
#define STM32F4_SUPPLY_VOLTAGE_MV 3300

#define INCLUDE_ADC

#define INCLUDE_CAN
#define STM32F4_CAN_BUFFER_DEFAULT_SIZE { 128 , 128 }
#define STM32F4_CAN_TX_PINS { { PIN(D, 1), AF(9) }, { PIN(B, 9), AF(9) } }
#define STM32F4_CAN_RX_PINS { { PIN(D, 0), AF(9) }, { PIN(B, 8), AF(9) } }

//#define INCLUDE_DAC

#define INCLUDE_GPIO
#define STM32F4_GPIO_PINS {/*      0          1          2          3          4          5          6          7          8          9          10         11         12         13         14         15      */\
                           /*PAx*/ DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), NO_INIT(), NO_INIT(), DEFAULT(),\
                           /*PBx*/ DEFAULT(), DEFAULT(), DEFAULT(), NO_INIT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
                           /*PCx*/ DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(),\
                           /*PDx*/ DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(),\
                           /*PEx*/ DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(),\
                           /*PFx*/ DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(),\
                           /*PGx*/ DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT(), DEFAULT()\
                          }

#define INCLUDE_I2C
#define STM32F4_I2C_SCL_PINS { { PIN(B, 6), AF(4) } }
#define STM32F4_I2C_SDA_PINS { { PIN(B, 7), AF(4) } }

#define INCLUDE_PWM
#define STM32F4_PWM_PINS {/*          0                          1                        2                        3                       */\
                          /* TIM1  */ { { PIN(E,  9), AF(1)   }, { PIN(E, 11), AF(1)   }, { PIN(E, 13), AF(1)   }, { PIN(E, 14), AF(1)   } },\
                          /* TIM2  */ { { PIN(A, 15), AF(1)   }, { PIN(B,  3), AF(1)   }, { PIN(B, 10), AF(1)   }, { PIN(B, 11), AF(1)   } },\
                          /* TIM3  */ { { PIN(B,  4), AF(2)   }, { PIN(B,  5), AF(2)   }, { PIN(B,  0), AF(2)   }, { PIN(B,  1), AF(2)   } },\
                          /* TIM4  */ { { PIN(D, 12), AF(2)   }, { PIN(D, 13), AF(2)   }, { PIN(D, 14), AF(2)   }, { PIN(D, 15), AF(2)   } },\
                          /* TIM5  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM6  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM7  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM8  */ { { PIN(C,  6), AF(3)   }, { PIN(C,  7), AF(3)   }, { PIN(C,  8), AF(3)   }, { PIN(C,  9), AF(3)   } },\
                          /* TIM9  */ { { PIN(A,  2), AF(3)   }, { PIN(A,  3), AF(3)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM10 */ { { PIN(B,  8), AF(3)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM11 */ { { PIN(B,  9), AF(3)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM12 */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM13 */ { { PIN(A,  6), AF(9)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                          /* TIM14 */ { { PIN(A,  7), AF(9)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
                         }

// NOTE: SPI5 is used for LCD IL9341 and MEMS Sensor. See documentation for Disco Board
#define INCLUDE_SPI				// SPI1					SPI2					SPI3					SPI4					SPI5
#define STM32F4_SPI_SCLK_PINS { { PIN(B, 3), AF(5) }, { PIN(B, 10), AF(5) }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN(F, 7), AF(5) } }
#define STM32F4_SPI_MISO_PINS { { PIN(B, 4), AF(5) }, { PIN(C,  2), AF(5) }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN(F, 8), AF(5) } }
#define STM32F4_SPI_MOSI_PINS { { PIN(B, 5), AF(5) }, { PIN(C,  3), AF(5) }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN(F, 9), AF(5) } }

#define INCLUDE_UART
#define STM32F4_UART_DEFAULT_TX_BUFFER_SIZE  { 256, 256, 256, 256 }
#define STM32F4_UART_DEFAULT_RX_BUFFER_SIZE  { 512, 512, 512, 512 }
#define STM32F4_UART_TX_PINS  { { PIN(A,  9), AF(7)  }, { PIN(D, 5), AF(7) }, { PIN(D,  8), AF(7) }, { PIN(A, 0), AF(8)   } }
#define STM32F4_UART_RX_PINS  { { PIN(A, 10), AF(7)  }, { PIN(D, 6), AF(7) }, { PIN(D,  9), AF(7) }, { PIN(A, 1), AF(8)   } }
#define STM32F4_UART_CTS_PINS { { PIN_NONE , AF_NONE }, { PIN(D, 3), AF(7) }, { PIN(D, 11), AF(7) }, { PIN_NONE , AF_NONE } }
#define STM32F4_UART_RTS_PINS { { PIN_NONE , AF_NONE }, { PIN(D, 4), AF(7) }, { PIN(D, 12), AF(7) }, { PIN_NONE , AF_NONE } }

#define INCLUDE_RTC

//#define INCLUDE_DISPLAY
#define STM32F4_DISPLAY_CONTROLLER_PINS { \
				{ PIN(C, 10), AF(14) }, { PIN(B,  0), AF(14) }, { PIN(A, 11), AF(14) }, { PIN(A, 12), AF(14) },\
				{ PIN(B,  1), AF(14) }, { PIN(G,  6), AF(14) }, { PIN(A,  6), AF(14) }, { PIN(G, 10), AF(14) },\
				{ PIN(B, 10), AF(14) }, { PIN(B, 11), AF(14) }, { PIN(C,  7), AF(14) }, { PIN(D,  3), AF(14) },\
				{ PIN(D,  6), AF(14) }, { PIN(G, 11), AF(14) }, { PIN(G, 12), AF(14) }, { PIN(A,  3), AF(14) },\
				{ PIN(B,  8), AF(14) }, { PIN(B,  9), AF(14) } }

#define STM32F4_DISPLAY_BACKLIGHT_PIN	{ PIN_NONE, AF_NONE }
#define STM32F4_DISPLAY_ENABLE_PIN	{ PIN(F, 10), AF_NONE }

#define INCLUDE_USBCLIENT
#define STM32F4_TOTAL_USB_CONTROLLERS	1
#define STM32F4_USB_PACKET_FIFO_COUNT	64
#define STM32F4_USB_ENDPOINT_SIZE		64
#define STM32F4_USB_ENDPOINT0_SIZE		8
#define STM32F4_USB_ENDPOINT_COUNT		4
#define STM32F4_USB_PIPE_COUNT			4
#define OTG_USE_HS

#ifdef OTG_USE_HS
#define STM32F4_USB_DM_PINS { { PIN(B, 14), AF(12) } }
#define STM32F4_USB_DP_PINS { { PIN(B, 15), AF(12) } }
#define STM32F4_USB_VB_PINS { { PIN(B, 13), AF(12) } }
#define STM32F4_USB_ID_PINS { { PIN(B, 12), AF(12) } }
#else
#define STM32F4_USB_DM_PINS { { PIN(A, 11), AF(10) } }
#define STM32F4_USB_DP_PINS { { PIN(A, 12), AF(10) } }
#define STM32F4_USB_VB_PINS { { PIN(A,  9), AF(10) } }
#define STM32F4_USB_ID_PINS { { PIN(A, 10), AF(10) } }
#endif // OTG_USE_HS

//#define INCLUDE_SD
#define STM32F4_SD_DATA0_PINS { { PIN(C, 8), AF(12) } }
#define STM32F4_SD_DATA1_PINS { { PIN(C, 9), AF(12) } }
#define STM32F4_SD_DATA2_PINS { { PIN(C, 10), AF(12) } }
#define STM32F4_SD_DATA3_PINS { { PIN(C, 11), AF(12) } }
#define STM32F4_SD_CLK_PINS { { PIN(C, 12), AF(12) } }
#define STM32F4_SD_CMD_PINS { { PIN(D, 2), AF(12) } }
