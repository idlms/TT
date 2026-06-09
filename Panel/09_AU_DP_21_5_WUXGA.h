/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

#if(_PANEL_TYPE == _AU_DP_21_5_WUXGA)
//----------------------------------------------------------------------------------------------------
// ID Code      : _AU_DP_21_5_WUXGA.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_2
#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT

//--------------------------------------------------
// Definitions for DPTx Panel Force Output Parameters
//--------------------------------------------------
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT        _ON//_OFF 
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING   _DISABLE
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD       _DISABLE
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP    _DISABLE
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP      _DISABLE

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_AUO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   630//760
#define _PANEL_MIN_FRAME_RATE                   470//460


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         1920
#define _PANEL_DH_END                           (1920+_PANEL_DH_START)

#define _PANEL_DH_TOTAL                         2200
#define _PANEL_DH_TOTAL_MAX                     2400
#define _PANEL_DH_TOTAL_MIN                     2120

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        1080
#define _PANEL_DV_END                           (1080+_PANEL_DV_START)

#define _PANEL_DV_TOTAL                         1125
#define _PANEL_DV_TOTAL_MAX                     1380
#define _PANEL_DV_TOTAL_MIN                     1100

#define _PANEL_DH_SYNC_WIDTH                    4
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      148500// Unit KHz  
#define _PANEL_PIXEL_CLOCK_MAX                  156000
#define _PANEL_PIXEL_CLOCK_MIN                  120000


#define _PANEL_POWER_ON_T1                      100
#define _PANEL_POWER_ON_T2                      40
#define _PANEL_POWER_ON_T3                      300

#define _PANEL_POWER_OFF_T4                     20
#define _PANEL_POWER_OFF_T5                     40
#define _PANEL_POWER_OFF_T6                     600


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------

#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL-80)	// eDP to LVDS	 



//-------------------------------------------------
/*
//--------------------------------------------------
// MN Frame Tracking Fine Tune Last Line
//--------------------------------------------------
#define _MN_FINE_TUNE_LASTLINE_SUPPORT          _ON		// check Last Line	
#define _MN_LAST_LINE_MAX                       (_LAST_LINE_TARGET + 50)
#define _MN_LAST_LINE_MIN                       (_LAST_LINE_TARGET - 50)

//-----------------------------------------------
*/




// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_KHZ//_PANEL_CLOCK_MHZ	

//--------------------------------------------------
// Definitions for video compensation
//-------------------------------------------------
#define BYPASS_VIDEO_COMPENSATION(Vin, Vout)    ((Vin) == ((Vout) >> 1))


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0)
#define _PANEL_ADC_GAIN_BIAS                    (0)


///////////////////////////
// Color Characteristics //
///////////////////////////



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#endif // End of #if(_PANEL_TYPE == _AU_DP_21_5_WUXGA)
