/* Exported types ------------------------------------------------------------*/
/**

* @brief  DSI Init Structure definition
*/

#include <stdlib.h>
#include <stdio.h>

//#define STM32F769xx	 1
//#include <inc/stm32f7xx.h>

#include <STM32F7.h>

#define UNUSED(x) ((x)=(x))

#define MAX_LAYER  2

#define LCD_DSI_ID              0x11
#define LCD_DSI_ID_REG          0xA8


typedef struct
{
	uint32_t AutomaticClockLaneControl; /*!< Automatic clock lane control
										This parameter can be any value of @ref DSI_Automatic_Clk_Lane_Control */

	uint32_t TXEscapeCkdiv;             /*!< TX Escape clock division
										The values 0 and 1 stop the TX_ESC clock generation                    */

	uint32_t NumberOfLanes;             /*!< Number of lanes
										This parameter can be any value of @ref DSI_Number_Of_Lanes            */

}DSI_InitTypeDef;

/**
* @brief  DSI PLL Clock structure definition
*/
typedef struct
{
	uint32_t PLLNDIV; /*!< PLL Loop Division Factor
					  This parameter must be a value between 10 and 125   */

	uint32_t PLLIDF;  /*!< PLL Input Division Factor
					  This parameter can be any value of @ref DSI_PLL_IDF */

	uint32_t PLLODF;  /*!< PLL Output Division Factor
					  This parameter can be any value of @ref DSI_PLL_ODF */

}DSI_PLLInitTypeDef;

/**
* @brief  DSI Video mode configuration
*/
typedef struct
{
	uint32_t VirtualChannelID;             /*!< Virtual channel ID                                                 */

	uint32_t ColorCoding;                  /*!< Color coding for LTDC interface
										   This parameter can be any value of @ref DSI_Color_Coding           */

	uint32_t LooselyPacked;                /*!< Enable or disable loosely packed stream (needed only when using
										   18-bit configuration).
										   This parameter can be any value of @ref DSI_LooselyPacked          */

	uint32_t Mode;                         /*!< Video mode type
										   This parameter can be any value of @ref DSI_Video_Mode_Type        */

	uint32_t PacketSize;                   /*!< Video packet size                                                  */

	uint32_t NumberOfChunks;               /*!< Number of chunks                                                   */

	uint32_t NullPacketSize;               /*!< Null packet size                                                   */

	uint32_t HSPolarity;                   /*!< HSYNC pin polarity
										   This parameter can be any value of @ref DSI_HSYNC_Polarity         */

	uint32_t VSPolarity;                   /*!< VSYNC pin polarity
										   This parameter can be any value of @ref DSI_VSYNC_Polarity         */

	uint32_t DEPolarity;                   /*!< Data Enable pin polarity
										   This parameter can be any value of @ref DSI_DATA_ENABLE_Polarity   */

	uint32_t HorizontalSyncActive;         /*!< Horizontal synchronism active duration (in lane byte clock cycles) */

	uint32_t HorizontalBackPorch;          /*!< Horizontal back-porch duration (in lane byte clock cycles)         */

	uint32_t HorizontalLine;               /*!< Horizontal line duration (in lane byte clock cycles)               */

	uint32_t VerticalSyncActive;           /*!< Vertical synchronism active duration                               */

	uint32_t VerticalBackPorch;            /*!< Vertical back-porch duration                                       */

	uint32_t VerticalFrontPorch;           /*!< Vertical front-porch duration                                      */

	uint32_t VerticalActive;               /*!< Vertical active duration                                           */

	uint32_t LPCommandEnable;              /*!< Low-power command enable
										   This parameter can be any value of @ref DSI_LP_Command             */

	uint32_t LPLargestPacketSize;          /*!< The size, in bytes, of the low power largest packet that
										   can fit in a line during VSA, VBP and VFP regions                  */

	uint32_t LPVACTLargestPacketSize;      /*!< The size, in bytes, of the low power largest packet that
										   can fit in a line during VACT region                               */

	uint32_t LPHorizontalFrontPorchEnable; /*!< Low-power horizontal front-porch enable
										   This parameter can be any value of @ref DSI_LP_HFP                 */

	uint32_t LPHorizontalBackPorchEnable;  /*!< Low-power horizontal back-porch enable
										   This parameter can be any value of @ref DSI_LP_HBP                 */

	uint32_t LPVerticalActiveEnable;       /*!< Low-power vertical active enable
										   This parameter can be any value of @ref DSI_LP_VACT                */

	uint32_t LPVerticalFrontPorchEnable;   /*!< Low-power vertical front-porch enable
										   This parameter can be any value of @ref DSI_LP_VFP                 */

	uint32_t LPVerticalBackPorchEnable;    /*!< Low-power vertical back-porch enable
										   This parameter can be any value of @ref DSI_LP_VBP                 */

	uint32_t LPVerticalSyncActiveEnable;   /*!< Low-power vertical sync active enable
										   This parameter can be any value of @ref DSI_LP_VSYNC               */

	uint32_t FrameBTAAcknowledgeEnable;    /*!< Frame bus-turn-around acknowledge enable
										   This parameter can be any value of @ref DSI_FBTA_acknowledge       */

}DSI_VidCfgTypeDef;

/**
* @brief  DSI Adapted command mode configuration
*/
typedef struct
{
	uint32_t VirtualChannelID;      /*!< Virtual channel ID                                                */

	uint32_t ColorCoding;           /*!< Color coding for LTDC interface
									This parameter can be any value of @ref DSI_Color_Coding          */

	uint32_t CommandSize;           /*!< Maximum allowed size for an LTDC write memory command, measured in
									pixels. This parameter can be any value between 0x00 and 0xFFFF   */

	uint32_t TearingEffectSource;   /*!< Tearing effect source
									This parameter can be any value of @ref DSI_TearingEffectSource   */

	uint32_t TearingEffectPolarity; /*!< Tearing effect pin polarity
									This parameter can be any value of @ref DSI_TearingEffectPolarity */

	uint32_t HSPolarity;            /*!< HSYNC pin polarity
									This parameter can be any value of @ref DSI_HSYNC_Polarity        */

	uint32_t VSPolarity;            /*!< VSYNC pin polarity
									This parameter can be any value of @ref DSI_VSYNC_Polarity        */

	uint32_t DEPolarity;            /*!< Data Enable pin polarity
									This parameter can be any value of @ref DSI_DATA_ENABLE_Polarity  */

	uint32_t VSyncPol;              /*!< VSync edge on which the LTDC is halted
									This parameter can be any value of @ref DSI_Vsync_Polarity        */

	uint32_t AutomaticRefresh;      /*!< Automatic refresh mode
									This parameter can be any value of @ref DSI_AutomaticRefresh      */

	uint32_t TEAcknowledgeRequest;  /*!< Tearing Effect Acknowledge Request Enable
									This parameter can be any value of @ref DSI_TE_AcknowledgeRequest */

}DSI_CmdCfgTypeDef;

/**
* @brief  DSI command transmission mode configuration
*/
typedef struct
{
	uint32_t LPGenShortWriteNoP;  /*!< Generic Short Write Zero parameters Transmission
								  This parameter can be any value of @ref DSI_LP_LPGenShortWriteNoP  */

	uint32_t LPGenShortWriteOneP; /*!< Generic Short Write One parameter Transmission
								  This parameter can be any value of @ref DSI_LP_LPGenShortWriteOneP */

	uint32_t LPGenShortWriteTwoP; /*!< Generic Short Write Two parameters Transmission
								  This parameter can be any value of @ref DSI_LP_LPGenShortWriteTwoP */

	uint32_t LPGenShortReadNoP;   /*!< Generic Short Read Zero parameters Transmission
								  This parameter can be any value of @ref DSI_LP_LPGenShortReadNoP   */

	uint32_t LPGenShortReadOneP;  /*!< Generic Short Read One parameter Transmission
								  This parameter can be any value of @ref DSI_LP_LPGenShortReadOneP  */

	uint32_t LPGenShortReadTwoP;  /*!< Generic Short Read Two parameters Transmission
								  This parameter can be any value of @ref DSI_LP_LPGenShortReadTwoP  */

	uint32_t LPGenLongWrite;      /*!< Generic Long Write Transmission
								  This parameter can be any value of @ref DSI_LP_LPGenLongWrite      */

	uint32_t LPDcsShortWriteNoP;  /*!< DCS Short Write Zero parameters Transmission
								  This parameter can be any value of @ref DSI_LP_LPDcsShortWriteNoP  */

	uint32_t LPDcsShortWriteOneP; /*!< DCS Short Write One parameter Transmission
								  This parameter can be any value of @ref DSI_LP_LPDcsShortWriteOneP */

	uint32_t LPDcsShortReadNoP;   /*!< DCS Short Read Zero parameters Transmission
								  This parameter can be any value of @ref DSI_LP_LPDcsShortReadNoP   */

	uint32_t LPDcsLongWrite;      /*!< DCS Long Write Transmission
								  This parameter can be any value of @ref DSI_LP_LPDcsLongWrite      */

	uint32_t LPMaxReadPacket;     /*!< Maximum Read Packet Size Transmission
								  This parameter can be any value of @ref DSI_LP_LPMaxReadPacket     */

	uint32_t AcknowledgeRequest;  /*!< Acknowledge Request Enable
								  This parameter can be any value of @ref DSI_AcknowledgeRequest     */

}DSI_LPCmdTypeDef;

/**
* @brief  DSI PHY Timings definition
*/
typedef struct
{
	uint32_t ClockLaneHS2LPTime;        /*!< The maximum time that the D-PHY clock lane takes to go from high-speed
										to low-power transmission                                              */

	uint32_t ClockLaneLP2HSTime;        /*!< The maximum time that the D-PHY clock lane takes to go from low-power
										to high-speed transmission                                             */

	uint32_t DataLaneHS2LPTime;         /*!< The maximum time that the D-PHY data lanes takes to go from high-speed
										to low-power transmission                                              */

	uint32_t DataLaneLP2HSTime;         /*!< The maximum time that the D-PHY data lanes takes to go from low-power
										to high-speed transmission                                             */

	uint32_t DataLaneMaxReadTime;       /*!< The maximum time required to perform a read command */

	uint32_t StopWaitTime;              /*!< The minimum wait period to request a High-Speed transmission after the
										Stop state                                                             */

}DSI_PHY_TimerTypeDef;

/**
* @brief  DSI HOST Timeouts definition
*/
typedef struct
{
	uint32_t TimeoutCkdiv;                 /*!< Time-out clock division                                  */

	uint32_t HighSpeedTransmissionTimeout; /*!< High-speed transmission time-out                         */

	uint32_t LowPowerReceptionTimeout;     /*!< Low-power reception time-out                             */

	uint32_t HighSpeedReadTimeout;         /*!< High-speed read time-out                                 */

	uint32_t LowPowerReadTimeout;          /*!< Low-power read time-out                                  */

	uint32_t HighSpeedWriteTimeout;        /*!< High-speed write time-out                                */

	uint32_t HighSpeedWritePrespMode;      /*!< High-speed write presp mode
										   This parameter can be any value of @ref DSI_HS_PrespMode */

	uint32_t LowPowerWriteTimeout;         /*!< Low-speed write time-out                                 */

	uint32_t BTATimeout;                   /*!< BTA time-out                                             */

}DSI_HOST_TimeoutTypeDef;

/**
* @brief  DSI States Structure definition
*/
typedef enum
{
	HAL_DSI_STATE_RESET = 0x00U,
	HAL_DSI_STATE_READY = 0x01U,
	HAL_DSI_STATE_ERROR = 0x02U,
	HAL_DSI_STATE_BUSY = 0x03U,
	HAL_DSI_STATE_TIMEOUT = 0x04U
}HAL_DSI_StateTypeDef;

/**
* @brief  DSI Handle Structure definition
*/
typedef struct
{
	DSI_TypeDef               *Instance;    /*!< Register base address      */
	DSI_InitTypeDef           Init;         /*!< DSI required parameters    */
//    HAL_LockTypeDef           Lock;         /*!< DSI peripheral status      */
	__IO HAL_DSI_StateTypeDef State;        /*!< DSI communication state    */
	__IO uint32_t             ErrorCode;    /*!< DSI Error code             */
	uint32_t                  ErrorMsk;     /*!< DSI Error monitoring mask  */
}DSI_HandleTypeDef;


typedef enum
{
	LCD_ORIENTATION_PORTRAIT = 0x00, /*!< Portrait orientation choice of LCD screen  */
	LCD_ORIENTATION_LANDSCAPE = 0x01, /*!< Landscape orientation choice of LCD screen */
	LCD_ORIENTATION_INVALID = 0x02  /*!< Invalid orientation choice of LCD screen   */
} LCD_OrientationTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup DSI_DCS_Command DSI DCS Command
* @{
*/
#define DSI_ENTER_IDLE_MODE       0x39U
#define DSI_ENTER_INVERT_MODE     0x21U
#define DSI_ENTER_NORMAL_MODE     0x13U
#define DSI_ENTER_PARTIAL_MODE    0x12U
#define DSI_ENTER_SLEEP_MODE      0x10U
#define DSI_EXIT_IDLE_MODE        0x38U
#define DSI_EXIT_INVERT_MODE      0x20U
#define DSI_EXIT_SLEEP_MODE       0x11U
#define DSI_GET_3D_CONTROL        0x3FU
#define DSI_GET_ADDRESS_MODE      0x0BU
#define DSI_GET_BLUE_CHANNEL      0x08U
#define DSI_GET_DIAGNOSTIC_RESULT 0x0FU
#define DSI_GET_DISPLAY_MODE      0x0DU
#define DSI_GET_GREEN_CHANNEL     0x07U
#define DSI_GET_PIXEL_FORMAT      0x0CU
#define DSI_GET_POWER_MODE        0x0AU
#define DSI_GET_RED_CHANNEL       0x06U
#define DSI_GET_SCANLINE          0x45U
#define DSI_GET_SIGNAL_MODE       0x0EU
#define DSI_NOP                   0x00U
#define DSI_READ_DDB_CONTINUE     0xA8U
#define DSI_READ_DDB_START        0xA1U
#define DSI_READ_MEMORY_CONTINUE  0x3EU
#define DSI_READ_MEMORY_START     0x2EU
#define DSI_SET_3D_CONTROL        0x3DU
#define DSI_SET_ADDRESS_MODE      0x36U
#define DSI_SET_COLUMN_ADDRESS    0x2AU
#define DSI_SET_DISPLAY_OFF       0x28U
#define DSI_SET_DISPLAY_ON        0x29U
#define DSI_SET_GAMMA_CURVE       0x26U
#define DSI_SET_PAGE_ADDRESS      0x2BU
#define DSI_SET_PARTIAL_COLUMNS   0x31U
#define DSI_SET_PARTIAL_ROWS      0x30U
#define DSI_SET_PIXEL_FORMAT      0x3AU
#define DSI_SET_SCROLL_AREA       0x33U
#define DSI_SET_SCROLL_START      0x37U
#define DSI_SET_TEAR_OFF          0x34U
#define DSI_SET_TEAR_ON           0x35U
#define DSI_SET_TEAR_SCANLINE     0x44U
#define DSI_SET_VSYNC_TIMING      0x40U
#define DSI_SOFT_RESET            0x01U
#define DSI_WRITE_LUT             0x2DU
#define DSI_WRITE_MEMORY_CONTINUE 0x3CU
#define DSI_WRITE_MEMORY_START    0x2CU
/**
* @}
*/

/** @defgroup DSI_Video_Mode_Type DSI Video Mode Type
* @{
*/
#define DSI_VID_MODE_NB_PULSES 0U
#define DSI_VID_MODE_NB_EVENTS 1U
#define DSI_VID_MODE_BURST     2U
/**
* @}
*/

/** @defgroup DSI_Color_Mode DSI Color Mode
* @{
*/
#define DSI_COLOR_MODE_FULL  0U
#define DSI_COLOR_MODE_EIGHT DSI_WCR_COLM
/**
* @}
*/

/** @defgroup DSI_ShutDown DSI ShutDown
* @{
*/
#define DSI_DISPLAY_ON  0U
#define DSI_DISPLAY_OFF DSI_WCR_SHTDN
/**
* @}
*/

/** @defgroup DSI_LP_Command DSI LP Command
* @{
*/
#define DSI_LP_COMMAND_DISABLE 0U
#define DSI_LP_COMMAND_ENABLE  DSI_VMCR_LPCE
/**
* @}
*/

/** @defgroup DSI_LP_HFP DSI LP HFP
* @{
*/
#define DSI_LP_HFP_DISABLE 0U
#define DSI_LP_HFP_ENABLE  DSI_VMCR_LPHFPE
/**
* @}
*/

/** @defgroup DSI_LP_HBP DSI LP HBP
* @{
*/
#define DSI_LP_HBP_DISABLE 0U
#define DSI_LP_HBP_ENABLE  DSI_VMCR_LPHBPE
/**
* @}
*/

/** @defgroup DSI_LP_VACT DSI LP VACT
* @{
*/
#define DSI_LP_VACT_DISABLE 0U
#define DSI_LP_VACT_ENABLE  DSI_VMCR_LPVAE
/**
* @}
*/

/** @defgroup DSI_LP_VFP DSI LP VFP
* @{
*/
#define DSI_LP_VFP_DISABLE 0
#define DSI_LP_VFP_ENABLE  DSI_VMCR_LPVFPE
/**
* @}
*/

/** @defgroup DSI_LP_VBP DSI LP VBP
* @{
*/
#define DSI_LP_VBP_DISABLE 0U
#define DSI_LP_VBP_ENABLE  DSI_VMCR_LPVBPE
/**
* @}
*/

/** @defgroup DSI_LP_VSYNC DSI LP VSYNC
* @{
*/
#define DSI_LP_VSYNC_DISABLE 0U
#define DSI_LP_VSYNC_ENABLE  DSI_VMCR_LPVSAE
/**
* @}
*/

/** @defgroup DSI_FBTA_acknowledge DSI FBTA Acknowledge
* @{
*/
#define DSI_FBTAA_DISABLE 0U
#define DSI_FBTAA_ENABLE  DSI_VMCR_FBTAAE
/**
* @}
*/

/** @defgroup DSI_TearingEffectSource DSI Tearing Effect Source
* @{
*/
#define DSI_TE_DSILINK  0U
#define DSI_TE_EXTERNAL DSI_WCFGR_TESRC
/**
* @}
*/

/** @defgroup DSI_TearingEffectPolarity DSI Tearing Effect Polarity
* @{
*/
#define DSI_TE_RISING_EDGE  0U
#define DSI_TE_FALLING_EDGE DSI_WCFGR_TEPOL
/**
* @}
*/

/** @defgroup DSI_Vsync_Polarity DSI Vsync Polarity
* @{
*/
#define DSI_VSYNC_FALLING 0U
#define DSI_VSYNC_RISING  DSI_WCFGR_VSPOL
/**
* @}
*/

/** @defgroup DSI_AutomaticRefresh DSI Automatic Refresh
* @{
*/
#define DSI_AR_DISABLE 0U
#define DSI_AR_ENABLE  DSI_WCFGR_AR
/**
* @}
*/

/** @defgroup DSI_TE_AcknowledgeRequest DSI TE Acknowledge Request
* @{
*/
#define DSI_TE_ACKNOWLEDGE_DISABLE 0U
#define DSI_TE_ACKNOWLEDGE_ENABLE DSI_CMCR_TEARE
/**
* @}
*/

/** @defgroup DSI_AcknowledgeRequest DSI Acknowledge Request
* @{
*/
#define DSI_ACKNOWLEDGE_DISABLE 0U
#define DSI_ACKNOWLEDGE_ENABLE DSI_CMCR_ARE
/**
* @}
*/

/** @defgroup DSI_LP_LPGenShortWriteNoP DSI LP LPGen Short Write NoP
* @{
*/
#define DSI_LP_GSW0P_DISABLE 0U
#define DSI_LP_GSW0P_ENABLE DSI_CMCR_GSW0TX
/**
* @}
*/

/** @defgroup DSI_LP_LPGenShortWriteOneP DSI LP LPGen Short Write OneP
* @{
*/
#define DSI_LP_GSW1P_DISABLE 0U
#define DSI_LP_GSW1P_ENABLE DSI_CMCR_GSW1TX
/**
* @}
*/

/** @defgroup DSI_LP_LPGenShortWriteTwoP DSI LP LPGen Short Write TwoP
* @{
*/
#define DSI_LP_GSW2P_DISABLE 0U
#define DSI_LP_GSW2P_ENABLE DSI_CMCR_GSW2TX
/**
* @}
*/

/** @defgroup DSI_LP_LPGenShortReadNoP DSI LP LPGen Short Read NoP
* @{
*/
#define DSI_LP_GSR0P_DISABLE 0U
#define DSI_LP_GSR0P_ENABLE DSI_CMCR_GSR0TX
/**
* @}
*/

/** @defgroup DSI_LP_LPGenShortReadOneP DSI LP LPGen Short Read OneP
* @{
*/
#define DSI_LP_GSR1P_DISABLE 0U
#define DSI_LP_GSR1P_ENABLE DSI_CMCR_GSR1TX
/**
* @}
*/

/** @defgroup DSI_LP_LPGenShortReadTwoP DSI LP LPGen Short Read TwoP
* @{
*/
#define DSI_LP_GSR2P_DISABLE 0U
#define DSI_LP_GSR2P_ENABLE DSI_CMCR_GSR2TX
/**
* @}
*/

/** @defgroup DSI_LP_LPGenLongWrite DSI LP LPGen LongWrite
* @{
*/
#define DSI_LP_GLW_DISABLE 0U
#define DSI_LP_GLW_ENABLE DSI_CMCR_GLWTX
/**
* @}
*/

/** @defgroup DSI_LP_LPDcsShortWriteNoP DSI LP LPDcs Short Write NoP
* @{
*/
#define DSI_LP_DSW0P_DISABLE 0U
#define DSI_LP_DSW0P_ENABLE DSI_CMCR_DSW0TX
/**
* @}
*/

/** @defgroup DSI_LP_LPDcsShortWriteOneP DSI LP LPDcs Short Write OneP
* @{
*/
#define DSI_LP_DSW1P_DISABLE 0U
#define DSI_LP_DSW1P_ENABLE DSI_CMCR_DSW1TX
/**
* @}
*/

/** @defgroup DSI_LP_LPDcsShortReadNoP DSI LP LPDcs Short Read NoP
* @{
*/
#define DSI_LP_DSR0P_DISABLE 0U
#define DSI_LP_DSR0P_ENABLE DSI_CMCR_DSR0TX
/**
* @}
*/

/** @defgroup DSI_LP_LPDcsLongWrite DSI LP LPDcs Long Write
* @{
*/
#define DSI_LP_DLW_DISABLE 0U
#define DSI_LP_DLW_ENABLE DSI_CMCR_DLWTX
/**
* @}
*/

/** @defgroup DSI_LP_LPMaxReadPacket DSI LP LPMax Read Packet
* @{
*/
#define DSI_LP_MRDP_DISABLE 0U
#define DSI_LP_MRDP_ENABLE DSI_CMCR_MRDPS
/**
* @}
*/

/** @defgroup DSI_HS_PrespMode DSI HS Presp Mode
* @{
*/
#define DSI_HS_PM_DISABLE 0U
#define DSI_HS_PM_ENABLE DSI_TCCR3_PM
/**
* @}
*/


/** @defgroup DSI_Automatic_Clk_Lane_Control DSI Automatic Clk Lane Control
* @{
*/
#define DSI_AUTO_CLK_LANE_CTRL_DISABLE 0U
#define DSI_AUTO_CLK_LANE_CTRL_ENABLE  DSI_CLCR_ACR
/**
* @}
*/

/** @defgroup DSI_Number_Of_Lanes DSI Number Of Lanes
* @{
*/
#define DSI_ONE_DATA_LANE  0U
#define DSI_TWO_DATA_LANES 1U
/**
* @}
*/

/** @defgroup DSI_FlowControl DSI Flow Control
* @{
*/
#define DSI_FLOW_CONTROL_CRC_RX  DSI_PCR_CRCRXE
#define DSI_FLOW_CONTROL_ECC_RX  DSI_PCR_ECCRXE
#define DSI_FLOW_CONTROL_BTA     DSI_PCR_BTAE
#define DSI_FLOW_CONTROL_EOTP_RX DSI_PCR_ETRXE
#define DSI_FLOW_CONTROL_EOTP_TX DSI_PCR_ETTXE
#define DSI_FLOW_CONTROL_ALL     (DSI_FLOW_CONTROL_CRC_RX | DSI_FLOW_CONTROL_ECC_RX | \
								  DSI_FLOW_CONTROL_BTA | DSI_FLOW_CONTROL_EOTP_RX | \
								  DSI_FLOW_CONTROL_EOTP_TX)
/**
* @}
*/

/** @defgroup DSI_Color_Coding DSI Color Coding
* @{
*/
#define DSI_RGB565 ((uint32_t)0x00000000U) /*!< The values 0x00000001 and 0x00000002 can also be used for the RGB565 color mode configuration */
#define DSI_RGB666 ((uint32_t)0x00000003U) /*!< The value 0x00000004 can also be used for the RGB666 color mode configuration                 */
#define DSI_RGB888 ((uint32_t)0x00000005U)
/**
* @}
*/

/** @defgroup DSI_LooselyPacked DSI Loosely Packed
* @{
*/
#define DSI_LOOSELY_PACKED_ENABLE  DSI_LCOLCR_LPE
#define DSI_LOOSELY_PACKED_DISABLE 0U
/**
* @}
*/

/** @defgroup DSI_HSYNC_Polarity DSI HSYNC Polarity
* @{
*/
#define DSI_HSYNC_ACTIVE_HIGH       0U
#define DSI_HSYNC_ACTIVE_LOW        DSI_LPCR_HSP
/**
* @}
*/

/** @defgroup DSI_VSYNC_Polarity DSI VSYNC Polarity
* @{
*/
#define DSI_VSYNC_ACTIVE_HIGH       0U
#define DSI_VSYNC_ACTIVE_LOW        DSI_LPCR_VSP
/**
* @}
*/

/** @defgroup DSI_DATA_ENABLE_Polarity DSI DATA ENABLE Polarity
* @{
*/
#define DSI_DATA_ENABLE_ACTIVE_HIGH 0U
#define DSI_DATA_ENABLE_ACTIVE_LOW  DSI_LPCR_DEP
/**
* @}
*/

/** @defgroup DSI_PLL_IDF DSI PLL IDF
* @{
*/
#define DSI_PLL_IN_DIV1 ((uint32_t)0x00000001U)
#define DSI_PLL_IN_DIV2 ((uint32_t)0x00000002U)
#define DSI_PLL_IN_DIV3 ((uint32_t)0x00000003U)
#define DSI_PLL_IN_DIV4 ((uint32_t)0x00000004U)
#define DSI_PLL_IN_DIV5 ((uint32_t)0x00000005U)
#define DSI_PLL_IN_DIV6 ((uint32_t)0x00000006U)
#define DSI_PLL_IN_DIV7 ((uint32_t)0x00000007U)
/**
* @}
*/

/** @defgroup DSI_PLL_ODF DSI PLL ODF
* @{
*/
#define DSI_PLL_OUT_DIV1 ((uint32_t)0x00000000U)
#define DSI_PLL_OUT_DIV2 ((uint32_t)0x00000001U)
#define DSI_PLL_OUT_DIV4 ((uint32_t)0x00000002U)
#define DSI_PLL_OUT_DIV8 ((uint32_t)0x00000003U)
/**
* @}
*/

/** @defgroup DSI_Flags DSI Flags
* @{
*/
#define DSI_FLAG_TE    DSI_WISR_TEIF
#define DSI_FLAG_ER    DSI_WISR_ERIF
#define DSI_FLAG_BUSY  DSI_WISR_BUSY
#define DSI_FLAG_PLLLS DSI_WISR_PLLLS
#define DSI_FLAG_PLLL  DSI_WISR_PLLLIF
#define DSI_FLAG_PLLU  DSI_WISR_PLLUIF
#define DSI_FLAG_RRS   DSI_WISR_RRS
#define DSI_FLAG_RR    DSI_WISR_RRIF
/**
* @}
*/

/** @defgroup DSI_Interrupts DSI Interrupts
* @{
*/
#define DSI_IT_TE   DSI_WIER_TEIE
#define DSI_IT_ER   DSI_WIER_ERIE
#define DSI_IT_PLLL DSI_WIER_PLLLIE
#define DSI_IT_PLLU DSI_WIER_PLLUIE
#define DSI_IT_RR   DSI_WIER_RRIE
/**
* @}
*/

/** @defgroup DSI_SHORT_WRITE_PKT_Data_Type DSI SHORT WRITE PKT Data Type
* @{
*/
#define DSI_DCS_SHORT_PKT_WRITE_P0 ((uint32_t)0x00000005U) /*!< DCS short write, no parameters      */
#define DSI_DCS_SHORT_PKT_WRITE_P1 ((uint32_t)0x00000015U) /*!< DCS short write, one parameter      */
#define DSI_GEN_SHORT_PKT_WRITE_P0 ((uint32_t)0x00000003U) /*!< Generic short write, no parameters  */
#define DSI_GEN_SHORT_PKT_WRITE_P1 ((uint32_t)0x00000013U) /*!< Generic short write, one parameter  */
#define DSI_GEN_SHORT_PKT_WRITE_P2 ((uint32_t)0x00000023U) /*!< Generic short write, two parameters */
/**
* @}
*/

/** @defgroup DSI_LONG_WRITE_PKT_Data_Type DSI LONG WRITE PKT Data Type
* @{
*/
#define DSI_DCS_LONG_PKT_WRITE ((uint32_t)0x00000039U) /*!< DCS long write     */
#define DSI_GEN_LONG_PKT_WRITE ((uint32_t)0x00000029U) /*!< Generic long write */
/**
* @}
*/

/** @defgroup DSI_SHORT_READ_PKT_Data_Type DSI SHORT READ PKT Data Type
* @{
*/
#define DSI_DCS_SHORT_PKT_READ    ((uint32_t)0x00000006U) /*!< DCS short read                     */
#define DSI_GEN_SHORT_PKT_READ_P0 ((uint32_t)0x00000004U) /*!< Generic short read, no parameters  */
#define DSI_GEN_SHORT_PKT_READ_P1 ((uint32_t)0x00000014U) /*!< Generic short read, one parameter  */
#define DSI_GEN_SHORT_PKT_READ_P2 ((uint32_t)0x00000024U) /*!< Generic short read, two parameters */
/**
* @}
*/

/** @defgroup DSI_Error_Data_Type DSI Error Data Type
* @{
*/
#define HAL_DSI_ERROR_NONE 0
#define HAL_DSI_ERROR_ACK  ((uint32_t)0x00000001U) /*!< acknowledge errors          */
#define HAL_DSI_ERROR_PHY  ((uint32_t)0x00000002U) /*!< PHY related errors          */
#define HAL_DSI_ERROR_TX   ((uint32_t)0x00000004U) /*!< transmission error          */
#define HAL_DSI_ERROR_RX   ((uint32_t)0x00000008U) /*!< reception error             */
#define HAL_DSI_ERROR_ECC  ((uint32_t)0x00000010U) /*!< ECC errors                  */
#define HAL_DSI_ERROR_CRC  ((uint32_t)0x00000020U) /*!< CRC error                   */
#define HAL_DSI_ERROR_PSE  ((uint32_t)0x00000040U) /*!< Packet Size error           */
#define HAL_DSI_ERROR_EOT  ((uint32_t)0x00000080U) /*!< End Of Transmission error   */
#define HAL_DSI_ERROR_OVF  ((uint32_t)0x00000100U) /*!< FIFO overflow error         */
#define HAL_DSI_ERROR_GEN  ((uint32_t)0x00000200U) /*!< Generic FIFO related errors */
/**
* @}
*/

/** @defgroup DSI_Lane_Group DSI Lane Group
* @{
*/
#define DSI_CLOCK_LANE ((uint32_t)0x00000000U)
#define DSI_DATA_LANES ((uint32_t)0x00000001U)
/**
* @}
*/

/** @defgroup DSI_Communication_Delay DSI Communication Delay
* @{
*/
#define DSI_SLEW_RATE_HSTX ((uint32_t)0x00000000U)
#define DSI_SLEW_RATE_LPTX ((uint32_t)0x00000001U)
#define DSI_HS_DELAY       ((uint32_t)0x00000002U)
/**
* @}
*/

/** @defgroup DSI_CustomLane DSI CustomLane
* @{
*/
#define DSI_SWAP_LANE_PINS   ((uint32_t)0x00000000U)
#define DSI_INVERT_HS_SIGNAL ((uint32_t)0x00000001U)
/**
* @}
*/

/** @defgroup DSI_Lane_Select DSI Lane Select
* @{
*/
#define DSI_CLOCK_LANE ((uint32_t)0x00000000U)
#define DSI_DATA_LANE0 ((uint32_t)0x00000001U)
#define DSI_DATA_LANE1 ((uint32_t)0x00000002U)
/**
* @}
*/

/** @defgroup DSI_PHY_Timing DSI PHY Timing
* @{
*/
#define DSI_TCLK_POST    ((uint32_t)0x00000000U)
#define DSI_TLPX_CLK     ((uint32_t)0x00000001U)
#define DSI_THS_EXIT     ((uint32_t)0x00000002U)
#define DSI_TLPX_DATA    ((uint32_t)0x00000003U)
#define DSI_THS_ZERO     ((uint32_t)0x00000004U)
#define DSI_THS_TRAIL    ((uint32_t)0x00000005U)
#define DSI_THS_PREPARE  ((uint32_t)0x00000006U)
#define DSI_TCLK_ZERO    ((uint32_t)0x00000007U)
#define DSI_TCLK_PREPARE ((uint32_t)0x00000008U)
/**
* @}
*/

#define HSE_VALUE 25000000 // Hse clock for the CPU

/* Exported macros -----------------------------------------------------------*/
/**
* @brief  Enables the DSI host.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= DSI_CR_EN)

/**
* @brief  Disables the DSI host.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR &= ~DSI_CR_EN)

/**
* @brief  Enables the DSI wrapper.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_WRAPPER_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->WCR |= DSI_WCR_DSIEN)

/**
* @brief  Disable the DSI wrapper.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_WRAPPER_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->WCR &= ~DSI_WCR_DSIEN)

/**
* @brief  Enables the DSI PLL.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_PLL_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->WRPCR |= DSI_WRPCR_PLLEN)

/**
* @brief  Disables the DSI PLL.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_PLL_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->WRPCR &= ~DSI_WRPCR_PLLEN)

/**
* @brief  Enables the DSI regulator.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_REG_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->WRPCR |= DSI_WRPCR_REGEN)

/**
* @brief  Disables the DSI regulator.
* @param  __HANDLE__ DSI handle
* @retval None.
*/
#define __HAL_DSI_REG_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->WRPCR &= ~DSI_WRPCR_REGEN)

/**
* @brief  Get the DSI pending flags.
* @param  __HANDLE__ DSI handle.
* @param  __FLAG__ Get the specified flag.
*          This parameter can be any combination of the following values:
*            @arg DSI_FLAG_TE   : Tearing Effect Interrupt Flag
*            @arg DSI_FLAG_ER   : End of Refresh Interrupt Flag
*            @arg DSI_FLAG_BUSY : Busy Flag
*            @arg DSI_FLAG_PLLLS: PLL Lock Status
*            @arg DSI_FLAG_PLLL : PLL Lock Interrupt Flag
*            @arg DSI_FLAG_PLLU : PLL Unlock Interrupt Flag
*            @arg DSI_FLAG_RRS  : Regulator Ready Flag
*            @arg DSI_FLAG_RR   : Regulator Ready Interrupt Flag
* @retval The state of FLAG (SET or RESET).
*/
#define __HAL_DSI_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->WISR & (__FLAG__))

/**
* @brief  Clears the DSI pending flags.
* @param  __HANDLE__ DSI handle.
* @param  __FLAG__ specifies the flag to clear.
*          This parameter can be any combination of the following values:
*            @arg DSI_FLAG_TE   : Tearing Effect Interrupt Flag
*            @arg DSI_FLAG_ER   : End of Refresh Interrupt Flag
*            @arg DSI_FLAG_PLLL : PLL Lock Interrupt Flag
*            @arg DSI_FLAG_PLLU : PLL Unlock Interrupt Flag
*            @arg DSI_FLAG_RR   : Regulator Ready Interrupt Flag
* @retval None
*/
#define __HAL_DSI_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->WIFCR = (__FLAG__))

/**
* @brief  Enables the specified DSI interrupts.
* @param  __HANDLE__ DSI handle.
* @param __INTERRUPT__ specifies the DSI interrupt sources to be enabled.
*          This parameter can be any combination of the following values:
*            @arg DSI_IT_TE  : Tearing Effect Interrupt
*            @arg DSI_IT_ER  : End of Refresh Interrupt
*            @arg DSI_IT_PLLL: PLL Lock Interrupt
*            @arg DSI_IT_PLLU: PLL Unlock Interrupt
*            @arg DSI_IT_RR  : Regulator Ready Interrupt
* @retval None
*/
#define __HAL_DSI_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->WIER |= (__INTERRUPT__))

/**
* @brief  Disables the specified DSI interrupts.
* @param  __HANDLE__ DSI handle
* @param __INTERRUPT__ specifies the DSI interrupt sources to be disabled.
*          This parameter can be any combination of the following values:
*            @arg DSI_IT_TE  : Tearing Effect Interrupt
*            @arg DSI_IT_ER  : End of Refresh Interrupt
*            @arg DSI_IT_PLLL: PLL Lock Interrupt
*            @arg DSI_IT_PLLU: PLL Unlock Interrupt
*            @arg DSI_IT_RR  : Regulator Ready Interrupt
* @retval None
*/
#define __HAL_DSI_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->WIER &= ~(__INTERRUPT__))

/**
* @brief  Checks whether the specified DSI interrupt has occurred or not.
* @param  __HANDLE__ DSI handle
* @param  __INTERRUPT__ specifies the DSI interrupt source to check.
*          This parameter can be one of the following values:
*            @arg DSI_IT_TE  : Tearing Effect Interrupt
*            @arg DSI_IT_ER  : End of Refresh Interrupt
*            @arg DSI_IT_PLLL: PLL Lock Interrupt
*            @arg DSI_IT_PLLU: PLL Unlock Interrupt
*            @arg DSI_IT_RR  : Regulator Ready Interrupt
* @retval The state of INTERRUPT (SET or RESET).
*/
#define __HAL_DSI_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->WISR & (__INTERRUPT__))


#define __HAL_RCC_LTDC_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)

#define __HAL_RCC_DSI_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_DSIEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_DSIEN);\
                                        UNUSED(tmpreg); \
                                      } while(0)                                                                            

#define __HAL_RCC_LTDC_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_LTDCEN))
#define __HAL_RCC_DSI_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_DSIEN))

#define __HAL_RCC_LTDC_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_LTDCRST))
#define __HAL_RCC_LTDC_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_LTDCRST))

#define __HAL_RCC_DSI_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_DSIRST))
#define __HAL_RCC_DSI_RELEASE_RESET()    (RCC->APB2RSTR &= ~(RCC_APB2RSTR_DSIRST))


#define BSP_LCD_DMA2D_IRQHandler        DMA2D_IRQHandler
#define BSP_LCD_DSI_IRQHandler          DSI_IRQHandler
#define BSP_LCD_LTDC_IRQHandler         LTDC_IRQHandler
#define BSP_LCD_LTDC_ER_IRQHandler      LTDC_ER_IRQHandler


#define LCD_LayerCfgTypeDef    LTDC_LayerCfgTypeDef
/**
* @brief  LCD FB_StartAddress
*/
#define LCD_FB_START_ADDRESS       ((uint32_t)0xC0000000)

/** @brief Maximum number of LTDC layers
*/
#define LTDC_MAX_LAYER_NUMBER             ((uint32_t) 2)

/** @brief LTDC Background layer index
*/
#define LTDC_ACTIVE_LAYER_BACKGROUND      ((uint32_t) 0)

/** @brief LTDC Foreground layer index
*/
#define LTDC_ACTIVE_LAYER_FOREGROUND      ((uint32_t) 1)

/** @brief Number of LTDC layers
*/
#define LTDC_NB_OF_LAYERS                 ((uint32_t) 2)

/** @brief LTDC Default used layer index
*/
#define LTDC_DEFAULT_ACTIVE_LAYER         LTDC_ACTIVE_LAYER_FOREGROUND

/**
* @brief  LCD status structure definition
*/
#define   LCD_OK         0x00
#define   LCD_ERROR      0x01
#define   LCD_TIMEOUT    0x02

/**
* @brief  LCD Display OTM8009A DSI Virtual Channel  ID
*/
#define LCD_OTM8009A_ID  ((uint32_t) 0)

/**
* @brief  HDMI ADV7533 DSI Virtual Channel  ID
*/
#define HDMI_ADV7533_ID  ((uint32_t) 0) 

/**
* @brief  HDMI Foramt
*/
#define HDMI_FORMAT_720_480   ((uint8_t) 0x00) /*720_480 format choice of HDMI display */
#define HDMI_FORMAT_720_576   ((uint8_t) 0x01) /*720_576 format choice of HDMI display*/

/**
* @brief  LCD color definitions values
* in ARGB8888 format.
*/
#define LCD_COLOR_BLUE          ((uint32_t) 0xFF0000FF)
#define LCD_COLOR_GREEN         ((uint32_t) 0xFF00FF00)
#define LCD_COLOR_CYAN          ((uint32_t) 0xFF00FFFF)
#define LCD_COLOR_MAGENTA       ((uint32_t) 0xFFFF00FF)
#define LCD_COLOR_YELLOW        ((uint32_t) 0xFFFFFF00)
#define LCD_COLOR_LIGHTBLUE     ((uint32_t) 0xFF8080FF)
#define LCD_COLOR_LIGHTGREEN    ((uint32_t) 0xFF80FF80)
#define LCD_COLOR_LIGHTRED      ((uint32_t) 0xFFFF8080)
#define LCD_COLOR_LIGHTCYAN     ((uint32_t) 0xFF80FFFF)
#define LCD_COLOR_LIGHTMAGENTA  ((uint32_t) 0xFFFF80FF)
#define LCD_COLOR_LIGHTYELLOW   ((uint32_t) 0xFFFFFF80)
#define LCD_COLOR_DARKBLUE      ((uint32_t) 0xFF000080)
#define LCD_COLOR_DARKGREEN     ((uint32_t) 0xFF008000)
#define LCD_COLOR_DARKRED       ((uint32_t) 0xFF800000)
#define LCD_COLOR_DARKCYAN      ((uint32_t) 0xFF008080)
#define LCD_COLOR_DARKMAGENTA   ((uint32_t) 0xFF800080)
#define LCD_COLOR_DARKYELLOW    ((uint32_t) 0xFF808000)
#define LCD_COLOR_WHITE         ((uint32_t) 0xFFFFFFFF)
#define LCD_COLOR_LIGHTGRAY     ((uint32_t) 0xFFD3D3D3)
#define LCD_COLOR_GRAY          ((uint32_t) 0xFF808080)
#define LCD_COLOR_DARKGRAY      ((uint32_t) 0xFF404040)
#define LCD_COLOR_BLACK         ((uint32_t) 0xFF000000)
#define LCD_COLOR_BROWN         ((uint32_t) 0xFFA52A2A)
#define LCD_COLOR_ORANGE        ((uint32_t) 0xFFFFA500)
#define LCD_COLOR_TRANSPARENT   ((uint32_t) 0xFF000000)
//#define LCD_DEFAULT_FONT        Font24
#define LCD_DSI_PIXEL_DATA_FMT_RBG888  DSI_RGB888 /*!< DSI packet pixel format chosen is RGB888 : 24 bpp */
#define LCD_DSI_PIXEL_DATA_FMT_RBG565  DSI_RGB565 /*!< DSI packet pixel format chosen is RGB565 : 16 bpp */
/**
* @}
*/


//// Implementations
//
//bool HAL_DSI_ConfigVideoMode(DSI_HandleTypeDef *hdsi, DSI_VidCfgTypeDef *VidCfg);
//bool HAL_DSI_ConfigAdaptedCommandMode(DSI_HandleTypeDef *hdsi, DSI_CmdCfgTypeDef *CmdCfg);
//bool HAL_DSI_ConfigCommand(DSI_HandleTypeDef *hdsi, DSI_LPCmdTypeDef *LPCmd);
//bool HAL_DSI_Init(DSI_HandleTypeDef *hdsi, DSI_PLLInitTypeDef *PLLInit);
//void BSP_LCD_Reset(void);
//static uint16_t LCD_IO_GetID(void);
//void BSP_LCD_MspInit(void);
//bool BSP_DSI_Deinit(DSI_HandleTypeDef *hdsi);
//bool HAL_DSI_DeInit(DSI_HandleTypeDef *hdsi);
//bool HAL_LTDC_StructInitFromVideoConfig(LTDC_HandleTypeDef* hltdc, DSI_VidCfgTypeDef *VidCfg);
//
////****************************