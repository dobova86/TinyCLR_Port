/*

SDRAM for DISCO-STM32F746NG

*/

// SDRAM base address for Bank 2
#define SDRAM_BASE 0xD0000000
// SDRAM size is 8MB
#define SDRAM_SIZE 0x00010000

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

// refresh for the SDRAM Micron is 64mS, for INIX .... / 4096 rows = 15.6uS per row
#define REFRESH_COUNT                    ((uint32_t) 0x056A)  /* SDRAM refresh counter (90Mhz SD clock) */


#define MODE_INPUT 	0
#define MODE_GPIO		1
#define MODE_AF			2
#define MODE_ANALOG	3

#define TYPE_PUSHPULL 	0
#define TYPE_OPENDRAIN 	1

#define SPEED_2MHz		0
#define SPEED_25MHz		1
#define SPEED_50MHz		2
#define SPEED_100MHz	3

#define PULLUP_NONE		0
#define PULLUP_UP			1
#define PULLUP_DOWN		2

#define MASK1BIT(pin) ((uint32_t)~(1 << (pin * 1)))
#define MASK2BIT(pin) ((uint32_t)~(3 << (pin * 2)))
#define MASK4BIT(pin) ((uint32_t)~(15 << (pin * 4)))
#define AFMASKL(pin)	((uint32_t)~(15 << (pin * 4)))
#define AFMASKH(pin)	((uint32_t)~(15 << ((pin - 8) * 4)))


//=================================================================================================
//
//=================================================================================================
//void gpio_conf(GPIO_TypeDef * GPIO, uint8_t pin, uint8_t mode, uint8_t type, uint8_t speed, uint8_t pullup, uint8_t af);
void InitSdramPins(void);
//=================================================================================================
//
//=================================================================================================


void SDRAM_Init(void);