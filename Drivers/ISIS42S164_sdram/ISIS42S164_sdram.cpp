/* 

SDRAM code implementation
*/
//=================================================================================================
// STM32F429I-Discovery SDRAM configuration
// Author : Dome Bova, on the code from Radoslaw Kwiecien
// Date : 18.03.2018
//=================================================================================================
#include <STM32F4.h>
#include <Device.h>
//#include "gpiof4.h"
#include "ISIS42S164_sdram.h"

//=================================================================================================
// Macros for SDRAM Timing Register
//=================================================================================================
#define TMRD(x) (x << 0)
#define TXSR(x) (x << 4)
#define TRAS(x) (x << 8)
#define TRC(x)  (x << 12)
#define TWR(x)  (x << 16)
#define TRP(x)  (x << 20)
#define TRCD(x) (x << 24)

#define FILL_PATTERN	0x55AA55AA //001F


const STM32F4_Gpio_Pin GPIOInitTable[] = SDRAM_PINS;

//=================================================================================================
// SDRAM_Init function
//=================================================================================================
void SDRAM_Init(void)
{
	volatile uint32_t ptr = 0;
	volatile uint32_t i = 0;

	uint32_t tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 | \
		SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL | \
		SDRAM_MODEREG_CAS_LATENCY_2 | \
		SDRAM_MODEREG_OPERATING_MODE_STANDARD | \
		SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;


	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN;

	InitSdramPins();

	RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;

	// Initialization step 1
	FMC_Bank5_6->SDCR[0] = FMC_SDCR1_SDCLK_1 | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE_1;
	FMC_Bank5_6->SDCR[1] = FMC_SDCR1_NR_0 | FMC_SDCR1_MWID_0 | FMC_SDCR1_NB | FMC_SDCR1_CAS;
	// Initialization step 2
	FMC_Bank5_6->SDTR[0] = TMRD(2) | TXSR(7) | TRAS(4) | TRC(7) | TWR(2) | TRP(2) | TRCD(2);
	FMC_Bank5_6->SDTR[1] = TMRD(2) | TXSR(7) | TRAS(4) | TWR(2) | TRCD(2);
	// Initialization step 3	
	while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
	FMC_Bank5_6->SDCMR = 1 | FMC_SDCMR_CTB2 | (1 << 5);
	// Initialization step 4
	for (i = 0; i < 1000000; i++);
	// Initialization step 5
	while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
	FMC_Bank5_6->SDCMR = 2 | FMC_SDCMR_CTB2 | (1 << 5);
	// Initialization step 6
	while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
	FMC_Bank5_6->SDCMR = 3 | FMC_SDCMR_CTB2 | (4 << 5);
	// Initialization step 7
	while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
	FMC_Bank5_6->SDCMR = 4 | FMC_SDCMR_CTB2 | (1 << 5) | (tmpmrd << 9);
	// Initialization step 8
	while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);
	FMC_Bank5_6->SDRTR |= (REFRESH_COUNT << 1);
	while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY);

	// remap SDRAM to 0x60000000
	//SYSCFG->MEMRMP |= SYSCFG_MEMRMP_SWP_FMC_0;

	// Clear SDRAM
	for (ptr = SDRAM_BASE; ptr < (SDRAM_BASE + SDRAM_SIZE); ptr += 4) {
		*((uint32_t *)ptr) = 0xFFFFFFFF;
	}
}



void InitSdramPins() {
	size_t totpins = SIZEOF_ARRAY(GPIOInitTable);
	for (int i = 0; i < totpins; i++) {
		STM32F4_GpioInternal_ConfigurePin(GPIOInitTable[i].number, STM32F4_Gpio_PortMode::AlternateFunction,
			STM32F4_Gpio_OutputType::PushPull, STM32F4_Gpio_OutputSpeed::VeryHigh,
			STM32F4_Gpio_PullDirection::None, GPIOInitTable[i].alternateFunction);
	}
}

//=================================================================================================
// End of file
//=================================================================================================

