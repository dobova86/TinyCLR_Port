
/*
IMPLEMENTATION and Initialization of DSI engine in the STM32F7x9 mcu
*/


#include "HAL_DsiDisplay.h"

#define LCD_DSI_ID              0x11
#define LCD_DSI_ID_REG          0xA8

//DMA2D_HandleTypeDef hdma2d_discovery;
//LTDC_HandleTypeDef  hltdc_discovery;
DSI_HandleTypeDef  hdsi_discovery;
static DSI_VidCfgTypeDef hdsivideo_handle;

uint32_t lcd_x_size = OTM8009A_800X480_WIDTH;
uint32_t lcd_y_size = OTM8009A_800X480_HEIGHT;


bool HAL_DSI_Init(DSI_HandleTypeDef *hdsi, DSI_PLLInitTypeDef *PLLInit)
{
	uint32_t tickstart = 0;
	uint32_t unitIntervalx4 = 0;
	uint32_t tempIDF = 0;

	/* Check the DSI handle allocation */
	if (hdsi == NULL)
	{
		return false;
	}

	/* Change DSI peripheral state */
	hdsi->State = HAL_DSI_STATE_BUSY;

	/**************** Turn on the regulator and enable the DSI PLL ****************/

	/* Enable the regulator */
	__HAL_DSI_REG_ENABLE(hdsi);


	/* Set the PLL division factors */
	hdsi->Instance->WRPCR &= ~(DSI_WRPCR_PLL_NDIV | DSI_WRPCR_PLL_IDF | DSI_WRPCR_PLL_ODF);
	hdsi->Instance->WRPCR |= (((PLLInit->PLLNDIV) << 2) | ((PLLInit->PLLIDF) << 11) | ((PLLInit->PLLODF) << 16));

	/* Enable the DSI PLL */
	__HAL_DSI_PLL_ENABLE(hdsi);

	/* Get tick */

	/*************************** Set the PHY parameters ***************************/

	/* D-PHY clock and digital enable*/
	hdsi->Instance->PCTLR |= (DSI_PCTLR_CKE | DSI_PCTLR_DEN);

	/* Clock lane configuration */
	hdsi->Instance->CLCR &= ~(DSI_CLCR_DPCC | DSI_CLCR_ACR);
	hdsi->Instance->CLCR |= (DSI_CLCR_DPCC | hdsi->Init.AutomaticClockLaneControl);

	/* Configure the number of active data lanes */
	hdsi->Instance->PCONFR &= ~DSI_PCONFR_NL;
	hdsi->Instance->PCONFR |= hdsi->Init.NumberOfLanes;

	/************************ Set the DSI clock parameters ************************/

	/* Set the TX escape clock division factor */
	hdsi->Instance->CCR &= ~DSI_CCR_TXECKDIV;
	hdsi->Instance->CCR |= hdsi->Init.TXEscapeCkdiv;

	/* Calculate the bit period in high-speed mode in unit of 0.25 ns (UIX4) */
	/* The equation is : UIX4 = IntegerPart( (1000/F_PHY_Mhz) * 4 )          */
	/* Where : F_PHY_Mhz = (NDIV * HSE_Mhz) / (IDF * ODF)                    */
	tempIDF = (PLLInit->PLLIDF > 0) ? PLLInit->PLLIDF : 1;
	unitIntervalx4 = (4000000 * tempIDF * (1 << PLLInit->PLLODF)) / ((HSE_VALUE / 1000) * PLLInit->PLLNDIV);

	/* Set the bit period in high-speed mode */
	hdsi->Instance->WPCR[0] &= ~DSI_WPCR0_UIX4;
	hdsi->Instance->WPCR[0] |= unitIntervalx4;

	/****************************** Error management *****************************/

	/* Disable all error interrupts and reset the Error Mask */
	hdsi->Instance->IER[0] = 0;
	hdsi->Instance->IER[1] = 0;
	hdsi->ErrorMsk = 0;

	/* Initialise the error code */
	hdsi->ErrorCode = HAL_DSI_ERROR_NONE;

	/* Initialize the DSI state*/
	hdsi->State = HAL_DSI_STATE_READY;

	return true;
}

uint8_t BSP_LCD_InitEx(LCD_OrientationTypeDef orientation)
{
	DSI_PLLInitTypeDef dsiPllInit;
	//static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
	uint32_t LcdClock = 27429; /*!< LcdClk = 27429 kHz */
	uint16_t read_id = 0;

	uint32_t laneByteClk_kHz = 0;
	uint32_t                   VSA; /*!< Vertical start active time in units of lines */
	uint32_t                   VBP; /*!< Vertical Back Porch time in units of lines */
	uint32_t                   VFP; /*!< Vertical Front Porch time in units of lines */
	uint32_t                   VACT; /*!< Vertical Active time in units of lines = imageSize Y in pixels to display */
	uint32_t                   HSA; /*!< Horizontal start active time in units of lcdClk */
	uint32_t                   HBP; /*!< Horizontal Back Porch time in units of lcdClk */
	uint32_t                   HFP; /*!< Horizontal Front Porch time in units of lcdClk */
	uint32_t                   HACT; /*!< Horizontal Active time in units of lcdClk = imageSize X in pixels to display */

	/* Toggle Hardware Reset of the DSI LCD using
	* its XRES signal (active low) */
	BSP_LCD_Reset();

	/* Check the connected monitor */
	read_id = LCD_IO_GetID();

	if (read_id != LCD_DSI_ID)
	{
		return LCD_ERROR;
	}

	/* Call first MSP Initialize only in case of first initialization
	* This will set IP blocks LTDC, DSI and DMA2D
	* - out of reset
	* - clocked
	* - NVIC IRQ related to IP blocks enabled
	*/
	BSP_LCD_MspInit();

	/*************************DSI Initialization***********************************/

	/* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
	hdsi_discovery.Instance = DSI;

	HAL_DSI_DeInit(&(hdsi_discovery));

	dsiPllInit.PLLNDIV = 100;
	dsiPllInit.PLLIDF = DSI_PLL_IN_DIV5;
	dsiPllInit.PLLODF = DSI_PLL_OUT_DIV1;
	laneByteClk_kHz = 62500; /* 500 MHz / 8 = 62.5 MHz = 62500 kHz */

							 /* Set number of Lanes */
	hdsi_discovery.Init.NumberOfLanes = DSI_TWO_DATA_LANES;

	/* TXEscapeCkdiv = f(LaneByteClk)/15.62 = 4 */
	hdsi_discovery.Init.TXEscapeCkdiv = laneByteClk_kHz / 15620;

	HAL_DSI_Init(&(hdsi_discovery), &(dsiPllInit));

	/* Timing parameters for all Video modes
	* Set Timing parameters of LTDC depending on its chosen orientation
	*/
	if (orientation == LCD_ORIENTATION_PORTRAIT)
	{
		lcd_x_size = OTM8009A_480X800_WIDTH;  /* 480 */
		lcd_y_size = OTM8009A_480X800_HEIGHT; /* 800 */
	}
	else
	{
		/* lcd_orientation == LCD_ORIENTATION_LANDSCAPE */
		lcd_x_size = OTM8009A_800X480_WIDTH;  /* 800 */
		lcd_y_size = OTM8009A_800X480_HEIGHT; /* 480 */
	}

	HACT = lcd_x_size;
	VACT = lcd_y_size;

	/* The following values are same for portrait and landscape orientations */
	VSA = OTM8009A_480X800_VSYNC;        /* 12  */
	VBP = OTM8009A_480X800_VBP;          /* 12  */
	VFP = OTM8009A_480X800_VFP;          /* 12  */
	HSA = OTM8009A_480X800_HSYNC;        /* 63  */
	HBP = OTM8009A_480X800_HBP;          /* 120 */
	HFP = OTM8009A_480X800_HFP;          /* 120 */

	hdsivideo_handle.VirtualChannelID = LCD_OTM8009A_ID;
	hdsivideo_handle.ColorCoding = LCD_DSI_PIXEL_DATA_FMT_RBG888;
	hdsivideo_handle.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
	hdsivideo_handle.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
	hdsivideo_handle.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
	hdsivideo_handle.Mode = DSI_VID_MODE_BURST; /* Mode Video burst ie : one LgP per line */
	hdsivideo_handle.NullPacketSize = 0xFFF;
	hdsivideo_handle.NumberOfChunks = 0;
	hdsivideo_handle.PacketSize = HACT; /* Value depending on display orientation choice portrait/landscape */
	hdsivideo_handle.HorizontalSyncActive = (HSA * laneByteClk_kHz) / LcdClock;
	hdsivideo_handle.HorizontalBackPorch = (HBP * laneByteClk_kHz) / LcdClock;
	hdsivideo_handle.HorizontalLine = ((HACT + HSA + HBP + HFP) * laneByteClk_kHz) / LcdClock; /* Value depending on display orientation choice portrait/landscape */
	hdsivideo_handle.VerticalSyncActive = VSA;
	hdsivideo_handle.VerticalBackPorch = VBP;
	hdsivideo_handle.VerticalFrontPorch = VFP;
	hdsivideo_handle.VerticalActive = VACT; /* Value depending on display orientation choice portrait/landscape */

											/* Enable or disable sending LP command while streaming is active in video mode */
	hdsivideo_handle.LPCommandEnable = DSI_LP_COMMAND_ENABLE; /* Enable sending commands in mode LP (Low Power) */

															  /* Largest packet size possible to transmit in LP mode in VSA, VBP, VFP regions */
															  /* Only useful when sending LP packets is allowed while streaming is active in video mode */
	hdsivideo_handle.LPLargestPacketSize = 16;

	/* Largest packet size possible to transmit in LP mode in HFP region during VACT period */
	/* Only useful when sending LP packets is allowed while streaming is active in video mode */
	hdsivideo_handle.LPVACTLargestPacketSize = 0;

	/* Specify for each region of the video frame, if the transmission of command in LP mode is allowed in this region */
	/* while streaming is active in video mode                                                                         */
	hdsivideo_handle.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE;   /* Allow sending LP commands during HFP period */
	hdsivideo_handle.LPHorizontalBackPorchEnable = DSI_LP_HBP_ENABLE;   /* Allow sending LP commands during HBP period */
	hdsivideo_handle.LPVerticalActiveEnable = DSI_LP_VACT_ENABLE;  /* Allow sending LP commands during VACT period */
	hdsivideo_handle.LPVerticalFrontPorchEnable = DSI_LP_VFP_ENABLE;   /* Allow sending LP commands during VFP period */
	hdsivideo_handle.LPVerticalBackPorchEnable = DSI_LP_VBP_ENABLE;   /* Allow sending LP commands during VBP period */
	hdsivideo_handle.LPVerticalSyncActiveEnable = DSI_LP_VSYNC_ENABLE; /* Allow sending LP commands during VSync = VSA period */

																	   /* Configure DSI Video mode timings with settings set above */
	HAL_DSI_ConfigVideoMode(&(hdsi_discovery), &(hdsivideo_handle));

	/*************************End DSI Initialization*******************************/


	/************************LTDC Initialization***********************************/

	/* Get LTDC Configuration from DSI Configuration */
	//HAL_LTDC_StructInitFromVideoConfig(&(hltdc_discovery), &(hdsivideo_handle));

	/* Initialize the LTDC */
	//HAL_LTDC_Init(&hltdc_discovery);

	/* Enable the DSI host and wrapper after the LTDC initialization
	To avoid any synchronization issue, the DSI shall be started after enabling the LTDC */
	//HAL_DSI_Start(&hdsi_discovery);

#if !defined(DATA_IN_ExtSDRAM)
	/* Initialize the SDRAM */
	//BSP_SDRAM_Init();
#endif /* DATA_IN_ExtSDRAM */

	/* Initialize the font */
	//BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/************************End LTDC Initialization*******************************/


	/***********************OTM8009A Initialization********************************/

	/* Initialize the OTM8009A LCD Display IC Driver (KoD LCD IC Driver)
	*  depending on configuration set in 'hdsivideo_handle'.
	*/
	OTM8009A_Init(OTM8009A_FORMAT_RGB888, orientation);

	/***********************End OTM8009A Initialization****************************/

	return LCD_OK;
}

void BSP_LCD_Reset(void) {
	// TODO: Reset XRES pin for LCD, example:
	/*
	  __HAL_RCC_GPIOJ_CLK_ENABLE();

	/* Configure the GPIO on PJ15 */
	//gpio_init_structure.Pin = GPIO_PIN_15;
	//gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
	//gpio_init_structure.Pull = GPIO_PULLUP;
	//gpio_init_structure.Speed = GPIO_SPEED_HIGH;

	//HAL_GPIO_Init(GPIOJ, &gpio_init_structure);

	///* Activate XRES active low */
	//HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_15, GPIO_PIN_RESET);

	//HAL_Delay(20); /* wait 20 ms */

	//			   /* Desactivate XRES */
	//HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_15, GPIO_PIN_SET);

	///* Wait for 10ms after releasing XRES before sending commands */
	//HAL_Delay(10);

	
}

/**
* @brief  De-Initializes the BSP LCD Msp
* Application can surcharge if needed this function implementation.
*/
__weak void BSP_LCD_MspDeInit(void)
{
	
	/** @brief Force and let in reset state LTDC, DMA2D and DSI Host + Wrapper IPs */
	//__HAL_RCC_LTDC_FORCE_RESET();
	//__HAL_RCC_DMA2D_FORCE_RESET();
	//__HAL_RCC_DSI_FORCE_RESET();

	///** @brief Disable the LTDC, DMA2D and DSI Host and Wrapper clocks */
	//__HAL_RCC_LTDC_CLK_DISABLE();
	//__HAL_RCC_DMA2D_CLK_DISABLE();
	//__HAL_RCC_DSI_CLK_DISABLE();
}

/**
* @brief  Initialize the BSP LCD Msp.
* Application can surcharge if needed this function implementation
*/
__weak void BSP_LCD_MspInit(void)
{
	/** @brief Enable the LTDC clock */
	//__HAL_RCC_LTDC_CLK_ENABLE();

	///** @brief Toggle Sw reset of LTDC IP */
	//__HAL_RCC_LTDC_FORCE_RESET();
	//__HAL_RCC_LTDC_RELEASE_RESET();

	///** @brief Enable the DMA2D clock */
	//__HAL_RCC_DMA2D_CLK_ENABLE();

	///** @brief Toggle Sw reset of DMA2D IP */
	//__HAL_RCC_DMA2D_FORCE_RESET();
	//__HAL_RCC_DMA2D_RELEASE_RESET();

	///** @brief Enable DSI Host and wrapper clocks */
	//__HAL_RCC_DSI_CLK_ENABLE();

	///** @brief Soft Reset the DSI Host and wrapper */
	//__HAL_RCC_DSI_FORCE_RESET();
	//__HAL_RCC_DSI_RELEASE_RESET();

}

static uint16_t LCD_IO_GetID(void)
{
	return LCD_DSI_ID;
}

bool HAL_DSI_DeInit(DSI_HandleTypeDef *hdsi)
{
	/* Check the DSI handle allocation */
	if (hdsi == NULL)
	{
		return false;
	}

	/* Change DSI peripheral state */
	hdsi->State = HAL_DSI_STATE_BUSY;

	/* Disable the DSI wrapper */
	__HAL_DSI_WRAPPER_DISABLE(hdsi);

	/* Disable the DSI host */
	__HAL_DSI_DISABLE(hdsi);

	/* D-PHY clock and digital disable */
	hdsi->Instance->PCTLR &= ~(DSI_PCTLR_CKE | DSI_PCTLR_DEN);

	/* Turn off the DSI PLL */
	__HAL_DSI_PLL_DISABLE(hdsi);

	/* Disable the regulator */
	__HAL_DSI_REG_DISABLE(hdsi);

	/* DeInit the low level hardware */
	//HAL_DSI_MspDeInit(hdsi);

	/* Initialise the error code */
	hdsi->ErrorCode = HAL_DSI_ERROR_NONE;

	/* Initialize the DSI state*/
	hdsi->State = HAL_DSI_STATE_RESET;

	return true;
}
