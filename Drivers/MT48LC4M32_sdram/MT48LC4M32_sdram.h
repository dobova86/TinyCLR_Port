/*

SDRAM for DISCO-STM32F746NG

*/

// SDRAM base address for Bank 1
//#define SDRAM_BASE ((uint32_t) 0xC0000000)
#define SDRAM_BASE ((uint32_t) 0x60000000)

// SDRAM size is 8MB --- USED ONLY TO FILL PATTERN IN MEMORY
//#define SDRAM_SIZE ((uint32_t)0x800000)
#define SDRAM_SIZE ((uint32_t) 0x1000)


// SDRAM defines for LOAD MODE REGISTER of the sram
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200) 

// refresh for the SDRAM Micron is 64mS / 4096 rows = 15.6uS per row
#define REFRESH_COUNT                    ((uint32_t) 0x0680) //((uint32_t) 0x0603)   /* SDRAM refresh counter (108Mhz SD clock) */

// GPIO
#define MODE_INPUT 		0
#define MODE_GPIO		1
#define MODE_AF			2
#define MODE_ANALOG		3

#define TYPE_PUSHPULL 	0
#define TYPE_OPENDRAIN 	1

#define SPEED_2MHz		0
#define SPEED_25MHz		1
#define SPEED_50MHz		2
#define SPEED_100MHz	3

#define PULLUP_NONE		0
#define PULLUP_UP		1
#define PULLUP_DOWN		2

#define MASK1BIT(pin) ((uint32_t)~(1 << (pin * 1)))
#define MASK2BIT(pin) ((uint32_t)~(3 << (pin * 2)))
#define MASK4BIT(pin) ((uint32_t)~(15 << (pin * 4)))
#define AFMASKL(pin)	((uint32_t)~(15 << (pin * 4)))
#define AFMASKH(pin)	((uint32_t)~(15 << ((pin - 8) * 4)))

extern void STM32F7_DebugLed(uint16_t pin, bool onoff);
//=================================================================================================
// PinsInit function
//=================================================================================================
void InitSdramPins(void);

//=================================================================================================
// Init function
//=================================================================================================

void SDRAM_Init(uint8_t databits);