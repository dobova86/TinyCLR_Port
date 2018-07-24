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

#define STM32F769xx 

#include <STM32F7.h>



#define DEVICE_TARGET STM32F7
#define DEVICE_NAME "DISCO-F769NI"
#define DEVICE_MANUFACTURER "STM32F769Disco"
#define DEVICE_VERSION ((0ULL << 48) | (12ULL << 32) | (0ULL << 16) | (0ULL << 0))

#define USB_DEBUGGER_VENDOR_ID 0x1B9F
#define USB_DEBUGGER_PRODUCT_ID 0x5000

#define UART_DEBUGGER_INDEX 0
#define USB_DEBUGGER_INDEX 0

//#define DEBUGGER_SELECTOR_PIN PIN(B, 13)
//#define DEBUGGER_SELECTOR_PULL TinyCLR_Gpio_PinDriveMode::InputPullUp
//#define DEBUGGER_SELECTOR_USB_STATE TinyCLR_Gpio_PinValue::High
#define DEBUGGER_FORCE_API STM32F7_UsbClient_GetApi()
//#define DEBUGGER_FORCE_API STM32F7_Uart_GetApi()
#define DEBUGGER_FORCE_INDEX USB_DEBUGGER_INDEX


//#define RUN_APP_PIN PIN(E, 4)
//#define RUN_APP_PULL TinyCLR_Gpio_PinDriveMode::InputPullUp
//#define RUN_APP_STATE TinyCLR_Gpio_PinValue::High
#define RUN_APP_FORCE_STATE true

#define SDRAM_DATABITS		32
#define SDRAM_32BIT		32 // SDRAM_16BIT for Disco-F746, SDRAM_32BIT for Disco-F769 [SDRAM_8BIT not used]
#define USE_SDRAM_HEAP
#define SDRAM_PINS {/* FMC bus pins (A0..12, D0-31) + CTRL Pins */\
				{ PIN(G, 2), AF(12) }, { PIN(D, 0), AF(12) }, { PIN(D, 1), AF(12) }, { PIN(D, 8), AF(12) }, { PIN(D, 9), AF(12) }, { PIN(D,10), AF(12) },\
				{ PIN(D,14), AF(12) }, { PIN(D,15), AF(12) }, { PIN(E, 0), AF(12) }, { PIN(E, 1), AF(12) }, { PIN(E, 7), AF(12) }, { PIN(E, 8), AF(12) },\
				{ PIN(E, 9), AF(12) }, { PIN(E,10), AF(12) }, { PIN(E,11), AF(12) }, { PIN(E,12), AF(12) }, { PIN(E,13), AF(12) }, { PIN(E,14), AF(12) },\
				{ PIN(E,15), AF(12) }, { PIN(F, 0), AF(12) }, { PIN(F, 1), AF(12) }, { PIN(F, 2), AF(12) }, { PIN(F, 3), AF(12) }, { PIN(F, 4), AF(12) },\
				{ PIN(F, 5), AF(12) }, { PIN(F,11), AF(12) }, { PIN(F,12), AF(12) }, { PIN(F,13), AF(12) }, { PIN(F,14), AF(12) }, { PIN(F,15), AF(12) },\
				{ PIN(G, 0), AF(12) }, { PIN(G, 1), AF(12) }, { PIN(G, 4), AF(12) }, { PIN(G, 5), AF(12) }, { PIN(G, 8), AF(12) }, { PIN(G,15), AF(12) },\
				{ PIN(H, 2), AF(12) }, { PIN(H, 3), AF(12) }, { PIN(H, 5), AF(12) },\
				{ PIN(H, 8), AF(12) }, { PIN(H, 9), AF(12) }, { PIN(H,10), AF(12) }, { PIN(H,11), AF(12) }, { PIN(H,12), AF(12) }, { PIN(H,13), AF(12) },\
				{ PIN(H,14), AF(12) }, { PIN(H,15), AF(12) }, { PIN(I, 0), AF(12) }, { PIN(I, 1), AF(12) }, { PIN(I, 2), AF(12) }, { PIN(I, 3), AF(12) },\
				{ PIN(I, 4), AF(12) }, { PIN(I, 5), AF(12) }, { PIN(I, 6), AF(12) }, { PIN(I, 7), AF(12) }, { PIN(I, 9), AF(12) }, { PIN(I,10), AF(12) },\
			}

#define DEPLOYMENT_SECTORS 	{\
								{ 0x06, 0x08080000, 0x00040000 }, { 0x07, 0x080C0000, 0x00040000 },\
								{ 0x08, 0x08100000, 0x00040000 }, { 0x09, 0x08140000, 0x00040000 },\
								{ 0x0A, 0x08180000, 0x00040000 }, { 0x0B, 0x081C0000, 0x00040000 }\
							 } //,



#define STM32F7_SYSTEM_CLOCK_HZ 216000000	 // 168000000 // 180000000 // 216000000
#define STM32F7_AHB_CLOCK_HZ	216000000	 // 168000000 // 180000000 // 216000000
#define STM32F7_APB1_CLOCK_HZ	54000000	 // 42000000  // 45000000  //  54000000
#define STM32F7_APB2_CLOCK_HZ	108000000	 // 84000000  // 90000000 //  108000000
#define STM32F7_EXT_CRYSTAL_CLOCK_HZ 25000000
#define STM32F7_SUPPLY_VOLTAGE_MV 3300

#define INCLUDE_ADC

//#define INCLUDE_CAN
#define STM32F7_CAN_BUFFER_DEFAULT_SIZE { 128 , 128 }
#define STM32F7_CAN_TX_PINS { { PIN(D, 1), AF(9) }, { PIN(B, 9), AF(9) } }
#define STM32F7_CAN_RX_PINS { { PIN(D, 0), AF(9) }, { PIN(B, 8), AF(9) } }

//#define INCLUDE_DAC

#define INCLUDE_GPIO
#define STM32F7_GPIO_PINS {/*      0          1          2          3          4          5          6          7          8          9          10         11         12         13         14         15      */\
						   /*PAx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PBx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PCx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PDx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PEx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PFx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PGx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PHx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PIx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PJx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						   /*PKx*/ NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(), NO_INIT(),\
						  }

#define INCLUDE_I2C
#define STM32F7_I2C_SCL_PINS { { PIN(B, 8), AF(4) } }
#define STM32F7_I2C_SDA_PINS { { PIN(B, 9), AF(4) } }

#define INCLUDE_PWM
#define STM32F7_PWM_PINS {/* CH         1                          2                        3                        4                       */\
						  /* TIM1  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN(A, 11), AF(1)   } },\
						  /* TIM2  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM3  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN(C,  8), AF(2)   }, { PIN_NONE  , AF_NONE } },\
						  /* TIM4  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM5  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM6  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM7  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM8  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM9  */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM10 */ { { PIN(F,  6), AF(3)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM11 */ { { PIN(F,  7), AF(3)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM12 */ { { PIN(H,  6), AF(9)   }, { PIN(B, 15), AF(9)   }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM13 */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						  /* TIM14 */ { { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE }, { PIN_NONE  , AF_NONE } },\
						 }

#define INCLUDE_SPI
#define STM32F7_SPI_SCLK_PINS { { PIN(B, 3), AF(5) }, { PIN(A,12), AF(5) } } //, { PIN(B, 10), AF(5) } }
#define STM32F7_SPI_MISO_PINS { { PIN(B, 4), AF(5) }, { PIN(B,14), AF(5) } } //, { PIN(C,  2), AF(5) } }
#define STM32F7_SPI_MOSI_PINS { { PIN(B, 5), AF(5) }, { PIN(B,15), AF(5) } } //, { PIN(C,  3), AF(5) } }

#define INCLUDE_UART
#define STM32F7_UART_DEFAULT_TX_BUFFER_SIZE  { 256, 256, 256, 256, 256, 256 }
#define STM32F7_UART_DEFAULT_RX_BUFFER_SIZE  { 512, 512, 512, 512, 512, 512 }
#define STM32F7_UART_TX_PINS  { { PIN(A, 9), AF(7) }, { PIN(C, 12), AF(8)  },{ PIN_NONE , AF_NONE },{ PIN_NONE , AF_NONE },{ PIN_NONE , AF_NONE }, { PIN(C, 6), AF(8) } }
#define STM32F7_UART_RX_PINS  { { PIN(A,10), AF(7) }, { PIN(D,  2), AF(8)  },{ PIN_NONE , AF_NONE },{ PIN_NONE , AF_NONE },{ PIN_NONE , AF_NONE }, { PIN(C, 7), AF(8) } }
#define STM32F7_UART_CTS_PINS { { PIN_NONE , AF_NONE },  { PIN_NONE , AF_NONE },  { PIN_NONE , AF_NONE },  { PIN_NONE , AF_NONE }, { PIN_NONE , AF_NONE }, { PIN_NONE, AF_NONE } }
#define STM32F7_UART_RTS_PINS { { PIN_NONE , AF_NONE },  { PIN_NONE , AF_NONE },  { PIN_NONE , AF_NONE },  { PIN_NONE , AF_NONE }, { PIN_NONE , AF_NONE }, { PIN_NONE, AF_NONE } }

#define INCLUDE_DISPLAY_DSI	// this enable code for DSI Display. NOT DEFINE INCLUDE_DISPLAY toghether
//#define INCLUDE_DISPLAY
#define STM32F7_DISPLAY_BACKLIGHT_PIN		{ PIN(I, 14), AF_NONE } // LCD Backlight control
#define STM32F7_DISPLAY_ENABLE_PIN			{ PIN(J,  2), AF_NONE } // LCD Enable control
#define STM32F7_DISPLAY_RESET_PIN			{ PIN(J, 15), AF_NONE } // this is DSI LCD RESET signal
#define STM32F7_DISPLAY_CONTROLLER_PINS     { PIN(I, 14), AF_NONE }

#define INCLUDE_USBCLIENT
#define STM32F7_TOTAL_USB_CONTROLLERS	1
#define STM32F7_USB_PACKET_FIFO_COUNT	64
#define STM32F7_USB_ENDPOINT_SIZE		64
#define STM32F7_USB_ENDPOINT0_SIZE		8
#define STM32F7_USB_ENDPOINT_COUNT		4
#define STM32F7_USB_PIPE_COUNT			4

// NOTE: To USE discovery board for STM32F769 OTG_HS, you need both defines:
#define OTG_USE_HS						1
#define OTG_USE_HS_ULPI					1

#if defined(OTG_USE_HS)
#define STM32F7_USB_DM_PINS { { PIN(B, 14), AF(12) } }
#define STM32F7_USB_DP_PINS { { PIN(B, 15), AF(12) } }
#define STM32F7_USB_VB_PINS { { PIN(B, 13), AF(12) } }
#define STM32F7_USB_ID_PINS { { PIN(B, 12), AF(12) } }
#else // USE OTG_FS port
#define STM32F7_USB_DM_PINS { { PIN(A, 11), AF(10) } }
#define STM32F7_USB_DP_PINS { { PIN(A, 12), AF(10) } }
#define STM32F7_USB_VB_PINS { { PIN(A,  9), AF(10) } }
#define STM32F7_USB_ID_PINS { { PIN(A, 10), AF(10) } }
#endif // OTG_USE_HS
#if defined(OTG_USE_HS_ULPI)
#define STM32F7_USB_ULPI_PINS {\
			{ /* D0..D7   */ PIN(A, 3), AF(10) }, { PIN(B, 0), AF(10) },{ PIN(B, 1), AF(10) },{ PIN(B, 10), AF(10) },{ PIN(B, 11), AF(10) },{ PIN(B, 12), AF(10) },{ PIN(B, 13), AF(10) },{ PIN(B, 5), AF(10) },\
			{ /* CTRL PIN */ PIN(A, 5), AF(10) },{ PIN(I, 11), AF(10) },{ PIN(C, 0), AF(10) },{ PIN(H, 4), AF(10) }\
		}
#endif

#define INCLUDE_RTC

#define INCLUDE_SD
#define STM32F7_SD_DATA0_PINS { { PIN(G, 9), AF(11) } }
#define STM32F7_SD_DATA1_PINS { { PIN(G,10), AF(11) } }
#define STM32F7_SD_DATA2_PINS { { PIN(B, 3), AF(10) } }
#define STM32F7_SD_DATA3_PINS { { PIN(B, 4), AF(10) } }
#define STM32F7_SD_CLK_PINS   { { PIN(D, 6), AF(11) } }
#define STM32F7_SD_CMD_PINS   { { PIN(D, 7), AF(11) } }
