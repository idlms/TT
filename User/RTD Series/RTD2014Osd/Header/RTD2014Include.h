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

//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2014Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "RTD2014Project.h"
#include "RTD2014NVRamOsd.h"
#include "RTD2014OsdTextTableDefine.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)
#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_VGA)
#else
#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
#elif(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
#elif(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
#elif(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif


#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif


#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
#elif(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
#else
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif



#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
#else
#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
#endif


//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)	// (0x000~0xFFF) max 4096 ( Contrast(1024) + ColorTemp(1024) + Sub Contrast(1024) + ColorControl(1024) )
#define _CONTRAST_MAX                               2848//1024//2848	
#define _CONTRAST_MIN                               1248//0//1248

#define _SUB_CONTRAST_MAX							1024//1024	
#define _SUB_CONTRAST_MIN							0

#define _COLOR_GAIN_R_MAX							1024//2048
#define _COLOR_GAIN_R_MIN							0
#define _COLOR_GAIN_G_MAX							1024//2048
#define _COLOR_GAIN_G_MIN							0
#define _COLOR_GAIN_B_MAX							1024//2048
#define _COLOR_GAIN_B_MIN							0


#else								// (0x00~0xFF) max 256 ( Contrast(64) + ColorTemp(64) + Sub Contrast(64) + ColorControl(64) )
#define _CONTRAST_MAX                               178//64//178	
#define _CONTRAST_MIN                               78//0//78

#define _SUB_CONTRAST_MAX							64//128	
#define _SUB_CONTRAST_MIN							0

#define _COLOR_GAIN_R_MAX							64//128
#define _COLOR_GAIN_R_MIN							0
#define _COLOR_GAIN_G_MAX							64//128
#define _COLOR_GAIN_G_MIN							0
#define _COLOR_GAIN_B_MAX							64//128
#define _COLOR_GAIN_B_MIN							0


#endif

#define _CONTRAST_CENTER                            (((_CONTRAST_MAX - _CONTRAST_MIN) / 2) + _CONTRAST_MIN)

//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
/*
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define _BACKLIGHT_MAX                              255
#else
#define _BACKLIGHT_MAX                              4095
#endif
#define _BACKLIGHT_MIN                              30
#define _BACKLIGHT_CENTER                           (((_BACKLIGHT_MAX - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)

*/
#define _DEFAULT_BACKLIGHT_MAX 4095
#define _DEFAULT_BACKLIGHT_MIN 256

#define _BACKLIGHT_MAX (g_stOsdServiceData.usBacklightMax) // 4095	
#define _BACKLIGHT_MIN (g_stOsdServiceData.usBacklightMin) // 256
#define _BACKLIGHT_CENTER (((_BACKLIGHT_MAX - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)

#define GET_BACKLIGHT_MAX() (g_stOsdServiceData.usBacklightMax)
#define SET_BACKLIGHT_MAX(x) (g_stOsdServiceData.usBacklightMax = (x))

#define GET_BACKLIGHT_MIN() (g_stOsdServiceData.usBacklightMin)
#define SET_BACKLIGHT_MIN(x) (g_stOsdServiceData.usBacklightMin = (x))

//--------------------------------------------------
// MACRO for Service
//--------------------------------------------------
#define GET_OSD_BACKLIGHT_INVERT() (g_stOsdServiceData.b1BacklightInvert)
#define SET_OSD_BACKLIGHT_INVERT(x) (g_stOsdServiceData.b1BacklightInvert = (x))

#define GET_OSD_BACKLIGHT_FREQ() (g_stOsdServiceData.usBacklightFreq)
#define SET_OSD_BACKLIGHT_FREQ(x) (g_stOsdServiceData.usBacklightFreq = (x))

//--------------------------------------------------
// Macro of BackLight
//--------------------------------------------------
#define GET_OSD_BACKLIGHT() (g_stOSDUserData.usBackLight)
#define SET_OSD_BACKLIGHT(x) (g_stOSDUserData.usBackLight = (x))

#define GET_OSD_BACKLIGHT_CONTROL() (g_stOSDUserData.b1BacklightControl)
#define SET_OSD_BACKLIGHT_CONTROL(x) (g_stOSDUserData.b1BacklightControl = (x))

#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
//--------------------------------------------------
// Macro of Stabbilux
//--------------------------------------------------
#define _DEFAULT_STABILUX 500
#define _DEFAULT_STABILUX_MAX 1024
#define _DEFAULT_STABILUX_MIN 0

#define GET_OSD_STABILUX() (g_stOsdServiceData.usStabilux)
#define SET_OSD_STABILUX(x) (g_stOsdServiceData.usStabilux = (x))

#define GET_OSD_STABILIZER() (g_stOSDUserData.b1Stabilizer)
#define SET_OSD_STABILIZER(x) (g_stOSDUserData.b1Stabilizer = (x))
#endif






//--------------------------------------------------
// Definitions of Brightness Range
//--------------------------------------------------
#if(_BRI_TYPE == _BRI_GEN_1_10BIT) 	// (0x000~0x3FF) max 1024 ( Brightness(512) + Sub brightness(256) + ColorControl(256) ) 
#define _BRIGHTNESS_MAX                             712//512//712 
#define _BRIGHTNESS_MIN                             312//0//312

#define _SUB_BRIGHTNESS_MAX                         256//512 
#define _SUB_BRIGHTNESS_MIN                         0

#define _COLOR_OFFSET_R_MAX							256//512
#define _COLOR_OFFSET_R_MIN							0
#define _COLOR_OFFSET_G_MAX							256//512
#define _COLOR_OFFSET_G_MIN							0
#define _COLOR_OFFSET_B_MAX							256//512
#define _COLOR_OFFSET_B_MIN							0

#else								// (0x00~0xFF) max 256 ( Brightness(128) + ColorControl(128) ) 
#define _BRIGHTNESS_MAX                             178//128//178
#define _BRIGHTNESS_MIN                             78//0//78

#define _COLOR_OFFSET_R_MAX							128
#define _COLOR_OFFSET_R_MIN							0
#define _COLOR_OFFSET_G_MAX							128
#define _COLOR_OFFSET_G_MIN							0
#define _COLOR_OFFSET_B_MAX							128
#define _COLOR_OFFSET_B_MIN							0

#endif

#define _BRIGHTNESS_CENTER                          (((_BRIGHTNESS_MAX - _BRIGHTNESS_MIN) / 2) + _BRIGHTNESS_MIN)

//--------------------------------------------------
// Definitions of Sharpness Range
//--------------------------------------------------
#define _SHARPNESS_MAX                              4
#define _SHARPNESS_MIN                              0
#define _SHARPNESS_CENTER                           (((_SHARPNESS_MAX - _SHARPNESS_MIN) / 2) + _SHARPNESS_MIN)
//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _OSD_PHASE_MAX                              100
#define _OSD_PHASE_MIN                              0

//--------------------------------------------------
// Definitions of Colortemp User RGB
//--------------------------------------------------
#define _USER_RGB_MAX                               1024//255	//  ColorTemp(1024)	
#define _USER_RGB_MIN                               0
#define _USER_RGB_CENTER                            (((_USER_RGB_MAX - _USER_RGB_MIN) / 2) + _USER_RGB_MIN)
//--------------------------------------------------------------
//--------------------------------------------------
// Definitions of Colortemp Gain					
//--------------------------------------------------
#define _COLOR_GAIN_MAX 255
#define _COLOR_GAIN_MIN 64
#define _COLOR_GAIN_CENTER (((_COLOR_GAIN_MAX - _COLOR_GAIN_MIN) / 2) + _COLOR_GAIN_MIN)

//--------------------------------------------------
// Definitions of Colortemp BIAS
//--------------------------------------------------
#define _COLOR_BIAS_MAX 218
#define _COLOR_BIAS_MIN 64
#define _COLOR_BIAS_CENTER (((_COLOR_BIAS_MAX - _COLOR_BIAS_MIN) / 2) + _COLOR_BIAS_MIN)


//--------------------------------------------------------------
//--------------------------------------------------
// Definitions of OD Gain Range
//--------------------------------------------------
#define _OD_GAIN_MAX                                127
#define _OD_GAIN_MIN                                0
#define _OD_GAIN_CENTER                             (((_OD_GAIN_MAX - _OD_GAIN_MIN) / 2) + _OD_GAIN_MIN)

//--------------------------------------------------
// Definitions of MBR Backlight Range
//--------------------------------------------------
#define _OSD_MBR_DUTY_MAX                           100
#define _OSD_MBR_DUTY_MIN                           0
#define _OSD_MBR_DUTY_CENTER                        (((_OSD_MBR_DUTY_MAX - _OSD_MBR_DUTY_MIN) / 2) + _OSD_MBR_DUTY_MIN)
#define _OSD_MBR_DUTY_DEFAULT                       40
#define _OSD_MBR_POS_MAX                            100
#define _OSD_MBR_POS_MIN                            0
#define _OSD_MBR_POS_CENTER                         (((_OSD_MBR_POS_MAX - _OSD_MBR_POS_MIN) / 2) + _OSD_MBR_POS_MIN)
#define _OSD_MBR_POS_DEFAULT                        _OSD_MBR_POS_CENTER

//--------------------------------------------------
// Definitions of 3D EFFECT
//--------------------------------------------------
#define _3D_EFFECT_MAX                              0x10
#define _3D_EFFECT_MIN                              0x00

//--------------------------------------------------
// Definitions of 2DTO3D EFFECT
//--------------------------------------------------
#define _2DTO3D_H_EFFECT_MAX                        0x30
#define _2DTO3D_H_EFFECT_MIN                        0x00

#define _2DTO3D_H_V_EFFECT_MAX                      0xFF
#define _2DTO3D_H_V_EFFECT_MIN                      0x00

//--------------------------------------------------
// Definitions of Menu Time Range
//--------------------------------------------------
#define _OSD_TIMEOUT_MAX                            60
#define _OSD_TIMEOUT_MIN                            10
#define _OSD_TIMEOUT_CENTER                         (((_OSD_TIMEOUT_MAX - _OSD_TIMEOUT_MIN) / 2) + _OSD_TIMEOUT_MIN)
//--------------------------------------------------
// Definitions of Transparency Range
//--------------------------------------------------
#define _OSD_TRANSPARENCY_MAX                       255
#define _OSD_TRANSPARENCY_MIN                       0
#define _OSD_TRANSPARENCY_CENTER                    (((_OSD_TRANSPARENCY_MAX - _OSD_TRANSPARENCY_MIN) / 2) + _OSD_TRANSPARENCY_MIN)
//--------------------------------------------------
// Definitions of OSD H Position Range
//--------------------------------------------------
#define _OSD_H_POS_MAX                              100
#define _OSD_H_POS_MIN                              0
#define _OSD_H_POS_CENTER                           (((_OSD_H_POS_MAX - _OSD_H_POS_MIN) / 2) + _OSD_H_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_V_POS_MAX                              100
#define _OSD_V_POS_MIN                              0
#define _OSD_V_POS_CENTER                           (((_OSD_V_POS_MAX - _OSD_V_POS_MIN) / 2) + _OSD_V_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_ASPECT_ORIGINAL_RATIO_MAX              100
#define _OSD_ASPECT_ORIGINAL_RATIO_MIN              0
#define _OSD_ASPECT_ORIGINAL_RATIO_CENTER           ((_OSD_ASPECT_ORIGINAL_RATIO_MAX - _OSD_ASPECT_ORIGINAL_RATIO_MIN) / 2)

//--------------------------------------------------
// Definitions of Hue Saturation Range
// Allowed Hue = 0 ~ 360, Sat = 0 ~ 330
//--------------------------------------------------
#define _DEFAULT_HUE                                _HUE_CENTER
#define _DEFAULT_SATURATION                         _SATURATION_CENTER
#define _DEFAULT_BRIGHTNESS 						0x200
#define _DEFAULT_CONTRAST 							0x800
#define _DEFAULT_SHARPNESS 							2

#if (_CUSTOMER_TYPE == _CUSTOMER_MEDICAL_ENGINEERS)
#define _DEFAULT_GAMMA _GAMMA_DICOM
#else
#define _DEFAULT_GAMMA _GAMMA_OFF
#endif

//--------------------------------------------------
// Definitions of OSD Volume Range
//--------------------------------------------------
#define _OSD_VOLUME_MAX                             100
#define _OSD_VOLUME_MIN                             0
#define _OSD_VOLUME_CENTER                          (((_OSD_VOLUME_MAX - _OSD_VOLUME_MIN) / 2) + _OSD_VOLUME_MIN)

#define _OSD_SETID_MAX                             	100
#define _OSD_SETID_MIN                 	            1		
#define _OSD_SETID_CENTER                     	    (((_OSD_SETID_MAX - _OSD_SETID_MIN) / 2) + _OSD_SETID_MIN)

#define _OSD_TRANSFER_ID_MAX                       	100	
#define _OSD_TRANSFER_ID_MIN           	            0		//  ( 0: All Set , 1~100 )
#define _OSD_TRANSFER_ID_CENTER                	    (((_OSD_TRANSFER_ID_MAX - _OSD_TRANSFER_ID_MIN) / 2) + _OSD_TRANSFER_ID_MIN)

//--------------------------------------------------
// Definitions of Hue Saturation Range
//--------------------------------------------------
#define _SIX_COLOR_SATURATION_MAX                   200
#define _SIX_COLOR_SATURATION_MIN                   0
#define _SIX_COLOR_SATURATION_CENTER                100

#define _SIX_COLOR_HUE_MAX                          100
#define _SIX_COLOR_HUE_MIN                          0
#define _SIX_COLOR_HUE_CENTER                       50

//--------------------------------------------------
// Definitions of OSD Select Region Width			//  RTD2795 Not Used
//--------------------------------------------------
#define _OSD_SR_WIDTH_MAX                           10
#define _OSD_SR_WIDTH_MIN                           0
#define _OSD_SR_WIDTH_CENTER                        (((_OSD_SR_WIDTH_MAX - _OSD_SR_WIDTH_MIN) / 2) + _OSD_SR_WIDTH_MIN)

//--------------------------------------------------
// Definitions of OSD Select Region Border Color	
//--------------------------------------------------
typedef enum
{
    _SELECT_REGION_COLOR_0,
    _SELECT_REGION_COLOR_1,
    _SELECT_REGION_COLOR_2,
    _SELECT_REGION_COLOR_3,
    _SELECT_REGION_COLOR_AMOUNT,
}EnumSelectRegionColorType;

//--------------------------------------------------
// Definitions of OSD Select Region Border Color	//  RTD2795 Not Used
//--------------------------------------------------
#define _OSD_SELECT_REGION_BORDER_RED               (0x80)
#define _OSD_SELECT_REGION_BORDER_GREEN             (0x80)
#define _OSD_SELECT_REGION_BORDER_BLUE              (0x80)
#define _OSD_SELECT_REGION_BORDER_WHITE             (0xFF)

//--------------------------------------------------
// Definitions of OSD PBP LR RATIO					//  RTD2795 Not Used
//--------------------------------------------------
#define _OSD_PBP_LR_RATIO_MAX                       4
#define _OSD_PBP_LR_RATIO_MIN                       0
#define _OSD_PBP_LR_RATIO_CENTER                    (((_OSD_PBP_LR_RATIO_MAX - _OSD_PBP_LR_RATIO_MIN) / 2) + _OSD_PBP_LR_RATIO_MIN)

//--------------------------------------------------
// Definitions of OSD PIP SUB position				//  RTD2795 Not Used
//--------------------------------------------------
typedef enum
{
    _PIP_POSITON_LT,
    _PIP_POSITON_RT,
    _PIP_POSITON_LB,
    _PIP_POSITON_RB,
    _PIP_POSITON_MIDDLE,
    _PIP_POSITON_USER,
    _PIP_POSITON_AMOUNT,
}EnumPipPositionType;

#define _OSD_PIP_USER_POSITION_H_MAX                100
#define _OSD_PIP_USER_POSITION_H_MIN                0
#define _OSD_PIP_USER_POSITION_H_CENTER             (((_OSD_PIP_USER_POSITION_H_MAX - _OSD_PIP_USER_POSITION_H_MIN) / 2) + _OSD_PIP_USER_POSITION_H_MIN)

#define _OSD_PIP_USER_POSITION_V_MAX                100
#define _OSD_PIP_USER_POSITION_V_MIN                0
#define _OSD_PIP_USER_POSITION_V_CENTER             (((_OSD_PIP_USER_POSITION_V_MAX - _OSD_PIP_USER_POSITION_V_MIN) / 2) + _OSD_PIP_USER_POSITION_V_MIN)

//--------------------------------------------------
// Definitions of OSD PIP Transparency				//  RTD2795 Not Used
//--------------------------------------------------
#define _OSD_PIP_TRANSPARENCY_MAX                   10
#define _OSD_PIP_TRANSPARENCY_MIN                   0
#define _OSD_PIP_TRANSPARENCY_CENTER                (((_OSD_PIP_TRANSPARENCY_MAX - _OSD_PIP_TRANSPARENCY_MIN) / 2) + _OSD_PIP_TRANSPARENCY_MIN)

//--------------------------------------------------
// Definitions of OSD PIP Size						//  RTD2795 Not Used
//--------------------------------------------------
#define _OSD_PIP_SIZE_MAX                           10
#define _OSD_PIP_SIZE_MIN                           0
#define _OSD_PIP_SIZE_CENTER                        (((_OSD_PIP_TRANSPARENCY_MAX - _OSD_PIP_TRANSPARENCY_MIN) / 2) + _OSD_PIP_TRANSPARENCY_MIN)

#define _OSD_PIP_SIZE_MIN_H_SIZE                    (640)
#define _OSD_PIP_SIZE_MIN_V_SIZE                    (480)


//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT1))
#define SET_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT1)

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT0))
#define SET_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT0)

//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()                        (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT2)
#define SET_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl |= _BIT2)
#define CLR_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl &= ~_BIT2)

//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()                       (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl |= _BIT3)
#define CLR_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl &= ~_BIT3)

//--------------------------------------------------
// Macro of Key Hold Start
//--------------------------------------------------
#define GET_KEY_HOLD()                              (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT4)
#define SET_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl |= _BIT4)
#define CLR_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl &= ~_BIT4)

#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_OSD_ADDRESS()                  (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress)
#define SET_FREESYNC_OSD_ADDRESS(x)                 (g_stOsdInfo.ucOsdFREESYNCInforOsdAddress = (x))
#endif

//--------------------------------------------------
// Macro of Key Message
//--------------------------------------------------
#define GET_KEYMESSAGE()                            (g_stOsdInfo.ucOsdKeyMessage)
#define SET_KEYMESSAGE(x)                           (g_stOsdInfo.ucOsdKeyMessage = (x))

#if (_ENABLE_MENU_OLED == _ON)
//--------------------------------------------------
// Macro of Off RS Min
//--------------------------------------------------
#define GET_COMP_RUN_RESTART() (g_stOsdInfo.ucCompRunNRestart)
#define SET_COMP_RUN_RESTART(x) (g_stOsdInfo.ucCompRunNRestart = (x))
#endif

//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------

#define _MENU_KEY_MESSAGE                           0	
#define _SELECT_KEY_MESSAGE                         1
#define _LEFT_KEY_MESSAGE                           2
#define _RIGHT_KEY_MESSAGE                          3
#define _UP_KEY_MESSAGE                             4	//  Add Key message 
#define _DOWN_KEY_MESSAGE                           5
#define _EXIT_KEY_MESSAGE                           6
#define _SOURCE_KEY_MESSAGE                         7
//------------------------------------------------------- 

#define _MUTE_KEY_MESSAGE                         	8
#define _FUNC_KEY_MESSAGE                         	9
#define _F1_KEY_MESSAGE                         	10	
#define _F2_KEY_MESSAGE                         	11
#define _F3_KEY_MESSAGE                         	12
#define _VOL_P_KEY_MESSAGE                         	13
#define _VOL_M_KEY_MESSAGE                         	14

#define _IR_UP_KEY_MESSAGE                          15	 
#define _IR_DOWN_KEY_MESSAGE                        16

#define _NONE_KEY_MESSAGE                           17

#define _KEY_AMOUNT                                 _NONE_KEY_MESSAGE
#define _NAVI_KEY_AMOUNT							8	


//------------------------------------------------------

#define _FAC_MENU_KEY_MESSAGE                   	0
#define _FAC_SELECT_KEY_MESSAGE                 	1
#define _FAC_LEFT_KEY_MESSAGE                   	2
#define _FAC_RIGHT_KEY_MESSAGE                  	3
#define _FAC_UP_KEY_MESSAGE                   		4
#define _FAC_DOWN_KEY_MESSAGE                  		5
#define _FAC_EXIT_KEY_MESSAGE                  		6


#define _FAC_NAVI_KEY_AMOUNT						7

//------------------------------------------------------


//--------------------------------------------------
// Definitions of LED indicction
//--------------------------------------------------
typedef enum
{
    _LED_ALL_OFF = _LED_SYSTEM_END,
} EnumUserLedIndication;

//--------------------------------------------------
// Macro of OSD
//--------------------------------------------------
#define FONTBYTE0(x)                                HIBYTE(0x1000 | (x)), LOBYTE(0x1000 | (x))
#define FONTBYTE1(x)                                HIBYTE(0x5000 | (x)), LOBYTE(0x5000 | (x))
#define FONTBYTE2(x)                                HIBYTE(0x9000 | (x)), LOBYTE(0x9000 | (x))
#define FONTALLBYTE(x)                              HIBYTE(0xD000 | (x)), LOBYTE(0xD000 | (x))
#define WINDOWBYTE0(x)                              HIBYTE(0x0000 | (x)), LOBYTE(0x0000 | (x))
#define WINDOWBYTE1(x)                              HIBYTE(0x4000 | (x)), LOBYTE(0x4000 | (x))
#define WINDOWBYTE2(x)                              HIBYTE(0x8000 | (x)), LOBYTE(0x8000 | (x))
#define WINDOWALLBYTE(x)                            HIBYTE(0xC000 | (x)), LOBYTE(0xC000 | (x))
#define FRAMEBYTE0(x)                               WINDOWBYTE0(x)
#define FRAMEBYTE1(x)                               WINDOWBYTE1(x)
#define FRAMEBYTE2(x)                               WINDOWBYTE2(x)
#define FRAMEALLBYTE(x)                             WINDOWALLBYTE(x)
#define WINNO(x)                                    (x)
#define ROW(x)                                      (x)
#define COL(x)                                      (x)
#define WIDTH(x)                                    (x)
#define HEIGHT(x)                                   (x)
#define LENGTH(x)                                   (x)
#define FGCOLOR(x)                                  (x)
#define BGCOLOR(x)                                  (x)
#define COLOR00(x)                                  (x)
#define COLOR01(x)                                  (x)
#define COLOR10(x)                                  (x)
#define COLOR11(x)                                  (x)
#define XSTART(x)                                   (x)
#define YSTART(x)                                   (x)
#define XEND(x)                                     (x)
#define YEND(x)                                     (x)
#define PIXELROW(x)                                 ((x) * 18)
#define PIXELCOL(x)                                 ((x) * 12)

//--------------------------------------------------
// Definitions of Checking Max or Min Value Used by OsdDisplayDetOverRange()
//--------------------------------------------------
#define _DET_OVERRANGE_MAX                          (0)
#define _DET_OVERRANGE_MIN                          (1)

//--------------------------------------------------
// Definations of OSD Function
//--------------------------------------------------
#define _SPACE_                                     0xfc
#define _EXT_                                       0xfc
#define _REPEAT_                                    0xfd
#define _NEXT_                                      0xfe
#define _END_                                       0xff


//--------------------------------------------------
// Definations of Write Byte
//--------------------------------------------------
#define _WRITE_BYTE0                                0
#define _WRITE_BYTE1                                1
#define _WRITE_BYTE2                                2
#define _WRITE_BYTEALL                              3

//--------------------------------------------------
// Macro of Osd Put String Mode
//--------------------------------------------------
typedef enum
{
    _PUT_STRING_LEFT = 0,
    _PUT_STRING_CENTER,
    _PUT_STRING_RIGHT,
	_PUT_STRING_LEFT_EMPTY_REMOVE,

} EnumOsdPutStringMode;

//--------------------------------------------------
// MACRO for OSD Logo Status
//--------------------------------------------------
#define GET_OSD_LOGO_ON() (g_stOsdServiceData.b1OsdLogo)
#define SET_OSD_LOGO_ON(x) (g_stOsdServiceData.b1OsdLogo = (x))

#define GET_OSD_LOGO_LIST() (g_stOsdServiceData.ucOSDLogoList)
#define SET_OSD_LOGO_LIST(x) (g_stOsdServiceData.ucOSDLogoList = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_WAKE_UP_SWITCH_DDCCI_PORT()         (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort)
#define SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(x)        (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort = (x))
#if(_DP_DEBUG_MSG == _ON)
//--------------------------------------------------
// MACRO for Power Saving Show DP Info
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_INFO()         (g_stOsdInfo.b1OsdWakeUpShowDpINFO)
#define SET_OSD_POWER_SAVING_SHOW_DP_INFO(x)        (g_stOsdInfo.b1OsdWakeUpShowDpINFO = (x))
#define GET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT()    (g_stOsdInfo.b4OsdWakeUpShowDpINFOPort)
#define SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(x)   (g_stOsdInfo.b4OsdWakeUpShowDpINFOPort = (x))


#endif

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_SOURCE()          (g_stOsdInfo.b1OsdWakeUpShowSource)
#define SET_OSD_POWER_SAVING_SHOW_SOURCE(x)         (g_stOsdInfo.b1OsdWakeUpShowSource = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_MENU()      	    (g_stOsdInfo.b1OsdWakeUpShowMenu)		// Reactive Power Saving Message flag
#define SET_OSD_POWER_SAVING_SHOW_MENU(x)      		(g_stOsdInfo.b1OsdWakeUpShowMenu = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Display Mode
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE() (g_stOsdInfo.b1OsdWakeUpShowDisplayMode)
#define SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(x) (g_stOsdInfo.b1OsdWakeUpShowDisplayMode = (x))


//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_IN_FACTORY_MENU_STATUS()            (g_stOsdInfo.b1OsdFactoryModeStatus)
#define SET_OSD_IN_FACTORY_MENU_STATUS(x)           (g_stOsdInfo.b1OsdFactoryModeStatus = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_DO_ASPECT_RATIO()                   (g_stOsdInfo.b1OsdDoAspectRatio)
#define SET_OSD_DO_ASPECT_RATIO(x)                  (g_stOsdInfo.b1OsdDoAspectRatio = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_COLOR_FORMAT()                      (g_stOsdInfo.b3OsdColorFormat)
#define SET_OSD_COLOR_FORMAT(x)                     (g_stOsdInfo.b3OsdColorFormat = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE_PREVIOUS()                    (g_stOsdInfo.ucOsdStatePrevious)
#define SET_OSD_STATE_PREVIOUS(x)                   (g_stOsdInfo.ucOsdStatePrevious = (x))


//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE()                             (g_stOsdInfo.usOsdState)
#define SET_OSD_STATE(x)                            (g_stOsdInfo.usOsdState = (x))

//--------------------------------------------------
// MACRO for Osd Evevt Message
//--------------------------------------------------
#define GET_OSD_EVENT_MESSAGE()                     (g_stOsdInfo.ucOsdEventMsg)
#define SET_OSD_EVENT_MESSAGE(x)                    (g_stOsdInfo.ucOsdEventMsg = (x))

//--------------------------------------------------
// MACRO for Six Color
//--------------------------------------------------
#define GET_OSD_SIX_COLOR()                         (g_stOsdInfo.b3OsdsixColor)
#define SET_OSD_SIX_COLOR(x)                        (g_stOsdInfo.b3OsdsixColor = (x))

//--------------------------------------------------
// MACRO for Six Color Hue
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_HUE()                     (g_stOsdInfo.ucOsdsixColorHue)
#define SET_OSD_SIX_COLOR_HUE(x)                    (g_stOsdInfo.ucOsdsixColorHue = (x))

//--------------------------------------------------
// MACRO for Six Color Saturation
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_SATURATION()              (g_stOsdInfo.ucOsdsixColorSaturation)
#define SET_OSD_SIX_COLOR_SATURATION(x)             (g_stOsdInfo.ucOsdsixColorSaturation = (x))

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_DOUBLE_SIZE()                       (g_stOsdInfo.b1OsdDoubleSizeStatus)
#define SET_OSD_DOUBLE_SIZE(x)                      (g_stOsdInfo.b1OsdDoubleSizeStatus = (x))

//--------------------------------------------------
// MACRO for Freeze Status
//--------------------------------------------------
#define GET_OSD_FREEZE_STATUS()                     (g_stOsdInfo.b1FreezeStatus)
#define SET_OSD_FREEZE_STATUS(x)                    (g_stOsdInfo.b1FreezeStatus = (x))

#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
#define GET_FREEZE_DISABLE_MSG_STATE()              (g_stOsdInfo.b1FreezeDisableOsdStatus)
#define SET_FREEZE_DISABLE_MSG_STATE(x)             (g_stOsdInfo.b1FreezeDisableOsdStatus = (x))
#endif

#define GET_OSD_ITEM_INDEX()                        (g_stOsdInfo.ucOsdItemIndex)
#define SET_OSD_ITEM_INDEX(x)                       (g_stOsdInfo.ucOsdItemIndex = (x))


#define GET_OSD_INFO_STRING_MODE()                  (g_stOsdInfo.b2StringMode)
#define SET_OSD_INFO_STRING_MODE(x)                 (g_stOsdInfo.b2StringMode = x)
#define CLR_OSD_INFO_STRING_MODE()                  (g_stOsdInfo.b2StringMode = _PUT_STRING_LEFT)

//--------------------------------------------------
// Macro of Osd Put String Center Length
//--------------------------------------------------
#define GET_OSD_INFO_STRING_MODE_LENGTH()           (g_stOsdInfo.ucStringModeLength)
#define SET_OSD_INFO_STRING_MODE_LENGTH(x)          (g_stOsdInfo.ucStringModeLength = x)
#define CLR_OSD_INFO_STRING_MODE_LENGTH()           (g_stOsdInfo.ucStringModeLength = 0)

//--------------------------------------------------
// Macro of Osd Put String Blank Pixel
//--------------------------------------------------
#define GET_OSD_INFO_STRING_BLANK_PIXEL()           (g_stOsdInfo.ucStringBlankPixel)
#define SET_OSD_INFO_STRING_BLANK_PIXEL(x)          (g_stOsdInfo.ucStringBlankPixel = x)
#define CLR_OSD_INFO_STRING_BLANK_PIXEL()           (g_stOsdInfo.ucStringBlankPixel = 0)

//==========================================================================================================
// Macro of NVRam BriCon Data
//==========================================================================================================
//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_CONTRAST()                          (g_stBriConData.usContrast)			
#define SET_OSD_CONTRAST(x)                         (g_stBriConData.usContrast = (x))

#define GET_OSD_SUB_CONTRAST()                    	(g_stBriConData.usSubContrast)			
#define SET_OSD_SUB_CONTRAST(x)                   	(g_stBriConData.usSubContrast = (x))

#define GET_OSD_COLOR_GAIN_R()                      (g_stBriConData.usColorGainR)		
#define SET_OSD_COLOR_GAIN_R(x)                   	(g_stBriConData.usColorGainR = (x))
#define GET_OSD_COLOR_GAIN_G()                      (g_stBriConData.usColorGainG)		
#define SET_OSD_COLOR_GAIN_G(x)                   	(g_stBriConData.usColorGainG = (x))
#define GET_OSD_COLOR_GAIN_B()                      (g_stBriConData.usColorGainB)		
#define SET_OSD_COLOR_GAIN_B(x)                   	(g_stBriConData.usColorGainB = (x))


//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_BRIGHTNESS()                        (g_stBriConData.usBrightness)		
#define SET_OSD_BRIGHTNESS(x)                       (g_stBriConData.usBrightness = (x))

#define GET_OSD_SUB_BRIGHTNESS()                    (g_stBriConData.usSubBrightness)			
#define SET_OSD_SUB_BRIGHTNESS(x)                   (g_stBriConData.usSubBrightness = (x))

#define GET_OSD_COLOR_OFFSET_R()                    (g_stBriConData.usColorOffsetR)		
#define SET_OSD_COLOR_OFFSET_R(x)                   (g_stBriConData.usColorOffsetR = (x))
#define GET_OSD_COLOR_OFFSET_G()                    (g_stBriConData.usColorOffsetG)		
#define SET_OSD_COLOR_OFFSET_G(x)                   (g_stBriConData.usColorOffsetG = (x))
#define GET_OSD_COLOR_OFFSET_B()                    (g_stBriConData.usColorOffsetB)		
#define SET_OSD_COLOR_OFFSET_B(x)                   (g_stBriConData.usColorOffsetB = (x))



//==========================================================================================================
// Macro of NVRam User Data
//==========================================================================================================

//--------------------------------------------------
// MACRO for OSD Display Mode
//--------------------------------------------------
#define GET_OSD_DISPLAY_MODE()                      (g_stOSDUserData.ucDisplayMode)				//  RTD2795 Not Used
#define SET_OSD_DISPLAY_MODE(x)                     (g_stOSDUserData.ucDisplayMode = (x))

//--------------------------------------------------
// MACRO for OSD Select Region Width
//--------------------------------------------------
#define GET_OSD_SELECT_REGION_WIDTH()               (g_stOSDUserData.ucSelectRegionWidth)
#define SET_OSD_SELECT_REGION_WIDTH(x)              (g_stOSDUserData.ucSelectRegionWidth = (x))

//--------------------------------------------------
// MACRO for OSD Select Region Color
//--------------------------------------------------
#define GET_OSD_SELECT_REGION_COLOR()               (g_stOSDUserData.ucSelectRegionColor)
#define SET_OSD_SELECT_REGION_COLOR(x)              (g_stOSDUserData.ucSelectRegionColor = (x))

//--------------------------------------------------
// MACRO for PBP LR Ratio
//--------------------------------------------------
#define GET_OSD_PBP_LR_RATIO()                      (g_stOSDUserData.ucPbpLrRatio)
#define SET_OSD_PBP_LR_RATIO(x)                     (g_stOSDUserData.ucPbpLrRatio = (x))

//--------------------------------------------------
// MACRO for PIP Position
//--------------------------------------------------
#define GET_OSD_PIP_POSITION_TYPE()                 (g_stOSDUserData.ucPipSubPosType)
#define SET_OSD_PIP_POSITION_TYPE(x)                (g_stOSDUserData.ucPipSubPosType = (x))

#define GET_OSD_PIP_USER_POSITION_H()               (g_stOSDUserData.usPipSubHPos)
#define SET_OSD_PIP_USER_POSITION_H(x)              (g_stOSDUserData.usPipSubHPos = (x))

#define GET_OSD_PIP_USER_POSITION_V()               (g_stOSDUserData.usPipSubVPos)
#define SET_OSD_PIP_USER_POSITION_V(x)              (g_stOSDUserData.usPipSubVPos = (x))

//--------------------------------------------------
// MACRO for PIP Transparency
//--------------------------------------------------
#define GET_OSD_PIP_TRANSPARENCY()                  (g_stOSDUserData.ucPipSubBlending)
#define SET_OSD_PIP_TRANSPARENCY(x)                 (g_stOSDUserData.ucPipSubBlending = (x))

//--------------------------------------------------
// MACRO for PIP Size
//--------------------------------------------------
#define GET_OSD_PIP_SIZE()                          (g_stOSDUserData.ucPipSubScaling)
#define SET_OSD_PIP_SIZE(x)                         (g_stOSDUserData.ucPipSubScaling = (x))


//--------------------------------------------------
// MACRO for Rotation Status
//--------------------------------------------------
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_OSD_DISP_ROTATION_SIZE_TYPE()           (g_stOSDUserData.b2DispRotationSizeType)
#define SET_OSD_DISP_ROTATION_SIZE_TYPE(x)          (g_stOSDUserData.b2DispRotationSizeType = (x))
#endif

//--------------------------------------------------
// MACRO for Motion Blur Reduction
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define GET_OSD_MBR_STATUS()                        (g_stOSDUserData.b2MbrStatus)
#define SET_OSD_MBR_STATUS(x)                       (g_stOSDUserData.b2MbrStatus = (x))
#define GET_OSD_MBR_DUTY()                          (g_stOSDUserData.b7MbrDuty)
#define SET_OSD_MBR_DUTY(x)                         (g_stOSDUserData.b7MbrDuty = (x))
#define GET_OSD_MBR_POSITION()                      (g_stOSDUserData.b7MbrPosition)
#define SET_OSD_MBR_POSITION(x)                     (g_stOSDUserData.b7MbrPosition = (x))
#endif

//--------------------------------------------------
// MACRO for DP Port Version
//--------------------------------------------------
#define GET_OSD_DP_D0_VERSION()                     (g_stOSDUserData.b2OsdDpD0PortVersion)
#define SET_OSD_DP_D0_VERSION(x)                    (g_stOSDUserData.b2OsdDpD0PortVersion = (x))

#define GET_OSD_DP_D1_VERSION()                     (g_stOSDUserData.b2OsdDpD1PortVersion)
#define SET_OSD_DP_D1_VERSION(x)                    (g_stOSDUserData.b2OsdDpD1PortVersion = (x))

#define GET_OSD_DP_D2_VERSION()                     (g_stOSDUserData.b2OsdDpD2PortVersion)
#define SET_OSD_DP_D2_VERSION(x)                    (g_stOSDUserData.b2OsdDpD2PortVersion = (x))

#define GET_OSD_DP_D6_VERSION()                     (g_stOSDUserData.b2OsdDpD6PortVersion)
#define SET_OSD_DP_D6_VERSION(x)                    (g_stOSDUserData.b2OsdDpD6PortVersion = (x))

#define GET_OSD_DP_MST()                            (g_stOSDUserData.b3OsdDpMST)
#define SET_OSD_DP_MST(x)                           (g_stOSDUserData.b3OsdDpMST = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DISP_ROTATE()                       (g_stOSDUserData.b3OsdDispRotate)
#define SET_OSD_DISP_ROTATE(x)                      (g_stOSDUserData.b3OsdDispRotate = (x))

//--------------------------------------------------
// MACRO for Latency
//--------------------------------------------------
#define GET_OSD_LATENCY()                           (g_stOSDUserData.b2LatencyStatus)
#define SET_OSD_LATENCY(x)                          (g_stOSDUserData.b2LatencyStatus = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DP_VERSION_HOTKEY_DISP()            (g_stOSDUserData.b1OsdDpVersionHotKeyDisp)
#define SET_OSD_DP_VERSION_HOTKEY_DISP(x)           (g_stOSDUserData.b1OsdDpVersionHotKeyDisp = (x))

//--------------------------------------------------
// MACRO for Display
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_OPTION()       (g_stOSDUserData.b1PreShowDpHotKeyVersion)
#define SET_OSD_POWER_SAVING_SHOW_DP_OPTION(x)      (g_stOSDUserData.b1PreShowDpHotKeyVersion = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY()                  (g_stOSDUserData.b1PanelUniformity)
#define SET_OSD_PANEL_UNIFORMITY(x)                 (g_stOSDUserData.b1PanelUniformity = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY_TYPE()             (g_stOSDUserData.b3PanelUniformityType)
#define SET_OSD_PANEL_UNIFORMITY_TYPE(x)            (g_stOSDUserData.b3PanelUniformityType = (x))

//--------------------------------------------------
// MACRO for PCM Soft Proft
//--------------------------------------------------

#define GET_OSD_PCM_SOFT_PROFT_MODE()               (g_stOSDUserData.b1PCMSoftProftMode)
#define SET_OSD_PCM_SOFT_PROFT_MODE(x)              (g_stOSDUserData.b1PCMSoftProftMode = (x))

//--------------------------------------------------
// MACRO for OSD Input Port Value
//--------------------------------------------------
#define GET_OSD_INPUT_PORT_OSD_ITEM()               (g_stOSDUserData.ucOsdInputPort)
#define SET_OSD_INPUT_PORT_OSD_ITEM(x)              (g_stOSDUserData.ucOsdInputPort = (x))


//--------------------------------------------------
// MACRO for OSD Rotate
//--------------------------------------------------
#define GET_OSD_ROTATE_STATUS()                     (g_stOSDUserData.b2OsdRotate)
#define SET_OSD_ROTATE_STATUS(x)                    (g_stOSDUserData.b2OsdRotate = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_3DOSD_STATUS()                      (g_stOSDUserData.b1Osd3DOSD)
#define SET_OSD_3DOSD_STATUS(x)                     (g_stOSDUserData.b1Osd3DOSD = (x))

//--------------------------------------------------
// Macro of BackLight
//--------------------------------------------------
#define GET_OSD_BACKLIGHT()                         (g_stOSDUserData.usBackLight)
#define SET_OSD_BACKLIGHT(x)                        (g_stOSDUserData.usBackLight = (x))

//--------------------------------------------------
// Macro of Aspect Origin Ratio
//--------------------------------------------------
#define GET_OSD_ASPECT_ORIGIN_RATIO()               (g_stOSDUserData.ucAspectOriginRatio)
#define SET_OSD_ASPECT_ORIGIN_RATIO(x)              (g_stOSDUserData.ucAspectOriginRatio = (x))

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE()                       (g_stOSDUserData.b4ColorTempType)
#define SET_COLOR_TEMP_TYPE(x)                      (g_stOSDUserData.b4ColorTempType = (x))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_R()                (g_stColorProcData.usColorTempR)//(g_stColorProcData.usColorTempR >> 4)	
#define SET_COLOR_TEMP_TYPE_USER_R(x)               (g_stColorProcData.usColorTempR = (x))//(g_stColorProcData.usColorTempR = ((x) << 4))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_G()                (g_stColorProcData.usColorTempG)//(g_stColorProcData.usColorTempG >> 4)	
#define SET_COLOR_TEMP_TYPE_USER_G(x)               (g_stColorProcData.usColorTempG = (x))//(g_stColorProcData.usColorTempG = ((x) << 4))
//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_B()                (g_stColorProcData.usColorTempB)//(g_stColorProcData.usColorTempB >> 4)	
#define SET_COLOR_TEMP_TYPE_USER_B(x)               (g_stColorProcData.usColorTempB = (x))//(g_stColorProcData.usColorTempB = ((x) << 4))

#define GET_COLOR_BIAS_R() 							(g_stColorProcData.usColorBIASR >> 2)	
#define SET_COLOR_BIAS_R(x) 						(g_stColorProcData.usColorBIASR = ((x) << 2))
#define GET_COLOR_BIAS_G() 							(g_stColorProcData.usColorBIASG >> 2)
#define SET_COLOR_BIAS_G(x) 						(g_stColorProcData.usColorBIASG = ((x) << 2))
#define GET_COLOR_BIAS_B() 							(g_stColorProcData.usColorBIASB >> 2)
#define SET_COLOR_BIAS_B(x) 						(g_stColorProcData.usColorBIASB = ((x) << 2))

#define GET_COLOR_GAIN_R() 							(g_stColorProcData.usColorGainR >> 4)
#define SET_COLOR_GAIN_R(x) 						(g_stColorProcData.usColorGainR = ((x) << 4))
#define GET_COLOR_GAIN_G() 							(g_stColorProcData.usColorGainG >> 4)
#define SET_COLOR_GAIN_G(x) 						(g_stColorProcData.usColorGainG = ((x) << 4))
#define GET_COLOR_GAIN_B() 							(g_stColorProcData.usColorGainB >> 4)
#define SET_COLOR_GAIN_B(x) 						(g_stColorProcData.usColorGainB = ((x) << 4))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
//--------------------------------------------------
#define GET_OSD_SERVICE() 							(g_stOsdServiceData.b1IsService)
#define SET_OSD_SERVICE(x) 							(g_stOsdServiceData.b1IsService = (x))

#define GET_OSD_LCD_TEST_STATUS() 					(g_stOsdServiceData.b1LCDtest)
#define SET_OSD_LCD_TEST_STATUS(x) 					(g_stOsdServiceData.b1LCDtest = (x))

#define GET_OSD_LCD_TEST_MODE() 					(g_stOsdServiceData.b1LCDtestMode)
#define SET_OSD_LCD_TEST_MODE(x) 					(g_stOsdServiceData.b1LCDtestMode = (x))

#define GET_OSD_D0_NAME() 							(g_stOsdServiceData.b4D0Name)
#define SET_OSD_D0_NAME(x) 							(g_stOsdServiceData.b4D0Name = (x))

#define GET_OSD_D1_NAME() 							(g_stOsdServiceData.b4D1Name)
#define SET_OSD_D1_NAME(x) 							(g_stOsdServiceData.b4D1Name = (x))

#define GET_OSD_D2_NAME() 							(g_stOsdServiceData.b4D2Name)
#define SET_OSD_D2_NAME(x) 							(g_stOsdServiceData.b4D2Name = (x))

#define GET_OSD_D3_NAME() 							(g_stOsdServiceData.b4D3Name)
#define SET_OSD_D3_NAME(x)							(g_stOsdServiceData.b4D3Name = (x))

#define GET_OSD_USER_ASSIGN_UP()                    (g_stOsdServiceData.b1UserAssignUp)
#define SET_OSD_USER_ASSIGN_UP(x)                   (g_stOsdServiceData.b1UserAssignUp = (x))

#define GET_OSD_USER_ASSIGN_DOWN()                  (g_stOsdServiceData.b1UserAssignDown)
#define SET_OSD_USER_ASSIGN_DOWN(x)                 (g_stOsdServiceData.b1UserAssignDown = (x))

#define GET_OSD_USER_ASSIGN_LEFT()                  (g_stOsdServiceData.b1UserAssignLeft)
#define SET_OSD_USER_ASSIGN_LEFT(x)                 (g_stOsdServiceData.b1UserAssignLeft = (x))

#define GET_OSD_USER_ASSIGN_RIGHT()                 (g_stOsdServiceData.b1UserAssignRight)
#define SET_OSD_USER_ASSIGN_RIGHT(x)                (g_stOsdServiceData.b1UserAssignRight = (x))

#define GET_OSD_POWERSAVE_TIME()                    (g_stOSDUserData.ucPowerSaveTime)
#define SET_OSD_POWERSAVE_TIME(x)                   (g_stOSDUserData.ucPowerSaveTime = (x))

#define GET_OSD_KEYLOCK() 							(g_stOSDUserData.b1KeyLock)			
#define SET_OSD_KEYLOCK(x) 							(g_stOSDUserData.b1KeyLock = (x))

#define GET_OSD_ASPECT_RATIO_TYPE()                 (g_stOSDUserData.b3AspectRatio)
#define SET_OSD_ASPECT_RATIO_TYPE(x)                (g_stOSDUserData.b3AspectRatio = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_VGA_COLOR_FORMAT_STATUS()               (g_stOSDUserData.b3VGARGBYUV)
#define SET_VGA_COLOR_FORMAT_STATUS(x)              (g_stOSDUserData.b3VGARGBYUV = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_DVI_COLOR_FORMAT_STATUS()               (g_stOSDUserData.b3DVIRGBYUV)
#define SET_DVI_COLOR_FORMAT_STATUS(x)              (g_stOSDUserData.b3DVIRGBYUV = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_DDCCI_STATUS()                      (g_stOSDUserData.b1DDCCIStatus)
#define SET_OSD_DDCCI_STATUS(x)                     (g_stOSDUserData.b1DDCCIStatus = (x))

//--------------------------------------------------
// MACRO for Ultra Vivid Status
//--------------------------------------------------
#define GET_OSD_ULTRA_VIVID_STATUS()                (g_stOSDUserData.b2UltraVividStatus)
#define SET_OSD_ULTRA_VIVID_STATUS(x)               (g_stOSDUserData.b2UltraVividStatus = (x))

//--------------------------------------------------
// MACRO for Sharpness
//--------------------------------------------------
#define GET_OSD_SHARPNESS()                         (g_stOSDUserData.b3Sharpness)
#define SET_OSD_SHARPNESS(x)                        (g_stOSDUserData.b3Sharpness = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_TRANSPARENCY_STATUS()               (g_stOSDUserData.ucTransparency)
#define SET_OSD_TRANSPARENCY_STATUS(x)              (g_stOSDUserData.ucTransparency = (x))

//--------------------------------------------------
// MACRO for Language
//--------------------------------------------------
#define GET_OSD_LANGUAGE()                          (g_stOSDUserData.b4Language)
#define SET_OSD_LANGUAGE(x)                         (g_stOSDUserData.b4Language = (x))

//--------------------------------------------------
// MACRO for OsdTimeout
//--------------------------------------------------
#define GET_OSD_TIME_OUT()                          (g_stOSDUserData.ucOsdTimeout)
#define SET_OSD_TIME_OUT(x)                         (g_stOSDUserData.ucOsdTimeout = (x))

//--------------------------------------------------
// MACRO for OsdHPos
//--------------------------------------------------
#define GET_OSD_HPOS()                              (g_stOSDUserData.ucOsdHPos)
#define SET_OSD_HPOS(x)                             (g_stOSDUserData.ucOsdHPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_VPOS()                              (g_stOSDUserData.ucOsdVPos)
#define SET_OSD_VPOS(x)                             (g_stOSDUserData.ucOsdVPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_GAMMA()                             (g_stOSDUserData.b3Gamma)
#define SET_OSD_GAMMA(x)                            (g_stOSDUserData.b3Gamma = (x))

//--------------------------------------------------
// MACRO for OD Status
//--------------------------------------------------
#define GET_OSD_OD_STATUS()                         (g_stOSDUserData.b1ODStatus)
#define SET_OSD_OD_STATUS(x)                        (g_stOSDUserData.b1ODStatus = (x))

//--------------------------------------------------
// MACRO for OD Gain
//--------------------------------------------------
#define GET_OSD_OD_GAIN()                           (g_stOSDUserData.ucODGain)
#define SET_OSD_OD_GAIN(x)                          (g_stOSDUserData.ucODGain = (x))

//--------------------------------------------------
// MACRO for Color Effect
//--------------------------------------------------
#define GET_OSD_COLOR_EFFECT()                      (g_stOSDUserData.b4ColorEffect)
#define SET_OSD_COLOR_EFFECT(x)                     (g_stOSDUserData.b4ColorEffect = (x))

//--------------------------------------------------
// MACRO for DCRStatus
//--------------------------------------------------
#define GET_OSD_DCR_STATUS()                        (g_stOSDUserData.b1OsdDcrStatus)
#define SET_OSD_DCR_STATUS(x)                       (g_stOSDUserData.b1OsdDcrStatus = (x))

//--------------------------------------------------
// MACRO for FreeSync Status
//--------------------------------------------------
#define GET_OSD_FREE_SYNC_STATUS()                  (g_stOSDUserData.b1FreeSyncStatus)
#define SET_OSD_FREE_SYNC_STATUS(x)                 (g_stOSDUserData.b1FreeSyncStatus = (x))

//--------------------------------------------------
// MACRO for AdaptiveSync Status
//--------------------------------------------------
#define GET_OSD_DP_ADAPTIVE_SYNC_STATUS()           (g_stOSDUserData.b1DpAdaptiveSyncStatus)
#define SET_OSD_DP_ADAPTIVE_SYNC_STATUS(x)          (g_stOSDUserData.b1DpAdaptiveSyncStatus = (x))

//--------------------------------------------------
// MACRO for Clone Mode
//--------------------------------------------------
#define GET_OSD_CLONE_MODE()                        (g_stOSDUserData.b1CloneMode)
#define SET_OSD_CLONE_MODE(x)                       (g_stOSDUserData.b1CloneMode = (x))

#define GET_OSD_CLONE_SRC()                         (g_stOSDUserData.b3CloneSrc)		
#define SET_OSD_CLONE_SRC(x)                        (g_stOSDUserData.b3CloneSrc = (x))

//-------------------------------------------------- 
#define GET_OSD_RESET_MODE()                        (g_stOSDUserData.b1ResetDo)			
#define SET_OSD_RESET_MODE(x)                       (g_stOSDUserData.b1ResetDo = (x))

#define GET_OSD_SETID()                    			(g_stOSDUserData.ucSetId)			
#define SET_OSD_SETID(x)                   			(g_stOSDUserData.ucSetId = (x))

#define GET_OSD_TRANSFER_ID()              			(g_stOSDUserData.ucTransferId)						
#define SET_OSD_TRANSFER_ID(x)             			(g_stOSDUserData.ucTransferId = (x))

#define GET_OSD_HPD_MODE()     						(g_stOSDUserData.b2HpdMode)			
#define SET_OSD_HPD_MODE(x)    						(g_stOSDUserData.b2HpdMode = (x))

#define GET_VGA_AUTOADJ_MODE()         				(g_stOSDUserData.b1AutoAdjustDo)			
#define SET_VGA_AUTOADJ_MODE(x)        				(g_stOSDUserData.b1AutoAdjustDo = (x))

#define GET_OSD_FAN_CONTROL()             			(g_stOSDUserData.b2FanControl)			
#define SET_OSD_FAN_CONTROL(x)            			(g_stOSDUserData.b2FanControl = (x))

#define GET_OSD_ACT_TEMP()             				(g_stOSDUserData.ucActiveTemp)			
#define SET_OSD_ACT_TEMP(x)            				(g_stOSDUserData.ucActiveTemp = (x))

#define GET_OSD_HYSTERESIS()             			(g_stOSDUserData.ucHysteresis)			
#define SET_OSD_HYSTERESIS(x)            			(g_stOSDUserData.ucHysteresis = (x))

#define GET_OSD_CUR_TEMP()             				(g_stOSDUserData.ucCurrentTemp)			
#define SET_OSD_CUR_TEMP(x)            				(g_stOSDUserData.ucCurrentTemp = (x))

#define GET_OSD_SHUTDOWN_MODE()        				(g_stOSDUserData.b1ShutdownMode)			
#define SET_OSD_SHUTDOWN_MODE(x)       				(g_stOSDUserData.b1ShutdownMode = (x))

#define GET_OSD_AUTO_DIMMING()        				(g_stOSDUserData.b1AutoDimming)			
#define SET_OSD_AUTO_DIMMING(x)       				(g_stOSDUserData.b1AutoDimming = (x))

#define GET_OSD_MAX_AMBIENT()        				(g_stOSDUserData.usMaxAmbient)			
#define SET_OSD_MAX_AMBIENT(x)       				(g_stOSDUserData.usMaxAmbient = (x))

#define GET_OSD_MIN_AMBIENT()        				(g_stOSDUserData.usMinAmbient)			
#define SET_OSD_MIN_AMBIENT(x)       				(g_stOSDUserData.usMinAmbient = (x))

#define GET_OSD_CUR_LUX()        					(g_stOSDUserData.usCurLux)			
#define SET_OSD_CUR_LUX(x)       					(g_stOSDUserData.usCurLux = (x))

#define GET_OSD_VIDEO_WALL()        				(g_stOSDUserData.b1VideoWall)			
#define SET_OSD_VIDEO_WALL(x)       				(g_stOSDUserData.b1VideoWall = (x))

#define GET_OSD_DISPLAY_NUM()      					(g_stOSDUserData.ucDisplayNum)			
#define SET_OSD_DISPLAY_NUM(x)       				(g_stOSDUserData.ucDisplayNum = (x))

#define GET_OSD_H_SET_COUNT()      					(g_stOSDUserData.ucHSetCount)			
#define SET_OSD_H_SET_COUNT(x)       				(g_stOSDUserData.ucHSetCount = (x))

#define GET_OSD_V_SET_COUNT()      					(g_stOSDUserData.ucVSetCount)			
#define SET_OSD_V_SET_COUNT(x)       				(g_stOSDUserData.ucVSetCount = (x))

#define GET_OSD_H_EDGE_ADJ()      					(g_stOSDUserData.ucHEdgeAdjust)			
#define SET_OSD_H_EDGE_ADJ(x)       				(g_stOSDUserData.ucHEdgeAdjust = (x))

#define GET_OSD_V_EDGE_ADJ()      					(g_stOSDUserData.ucVEdgeAdjust)			
#define SET_OSD_V_EDGE_ADJ(x)       				(g_stOSDUserData.ucVEdgeAdjust = (x))

#define GET_OSD_REVERSE_SCAN()     					(g_stOSDUserData.b1ReverseScan)			
#define SET_OSD_REVERSE_SCAN(x)       				(g_stOSDUserData.b1ReverseScan = (x))

#define GET_OSD_SELECT_REGION()                     (g_stOSDUserData.ucSelectRegion)		
#define SET_OSD_SELECT_REGION(x)                    (g_stOSDUserData.ucSelectRegion = (x))

#define GET_OSD_INPUT_SWAP()                     	(g_stOSDUserData.b1InputSwapDo)			
#define SET_OSD_INPUT_SWAP(x)                    	(g_stOSDUserData.b1InputSwapDo = (x))

#define GET_OSD_BURNIN_MODE()                     	(g_stOSDUserData.b1BurnIn)			
#define SET_OSD_BURNIN_MODE(x)                    	(g_stOSDUserData.b1BurnIn = (x))



//--------------------------------------------------
// MACRO for Light Sensor Setting
//--------------------------------------------------
#if (_ENABLE_LIGHT_SENSOR == _ON)
#define GET_OSD_LIGHT_SENSOR_STATUS() (g_stOsdServiceData.b1LightSensorStatus)
#define SET_OSD_LIGHT_SENSOR_STATUS(x) (g_stOsdServiceData.b1LightSensorStatus = (x))

// #define GET_OSD_LIGHT_SENSOR_STEP()                         (g_stOsdUserData.usLightSensorStep)
// #define SET_OSD_LIGHT_SENSOR_STEP(x)                        (g_stOsdUserData.usLightSensorStep = (x))
//
// #define GET_OSD_LIGHT_SENSOR_MIN()                          (g_stOsdUserData.usLightSensorMin)
// #define SET_OSD_LIGHT_SENSOR_MIN(x)                         (g_stOsdUserData.usLightSensorMin = (x))
//
// #define GET_OSD_LIGHT_SENSOR_MAX()                          (g_stOsdUserData.usLightSensorMax)
// #define SET_OSD_LIGHT_SENSOR_MAX(x)                         (g_stOsdUserData.usLightSensorMax = (x))
#endif

//--------------------------------------------------
// MACRO for Fan Control Setting
//--------------------------------------------------
#if (_ENABLE_FAN_CONTROL == _ON)
#define GET_OSD_FAN_STATUS() (g_stOsdServiceData.b1FanStatus)
#define SET_OSD_FAN_STATUS(x) (g_stOsdServiceData.b1FanStatus = (x))

#define GET_OSD_FAN_PWM() (g_stOsdServiceData.ucFanPwm)
#define SET_OSD_FAN_PWM(x) (g_stOsdServiceData.ucFanPwm = (x))
/*
#define GET_OSD_FAN_PWM2()                       (g_stOsdServiceData.ucFanPwm2)
#define SET_OSD_FAN_PWM2(x)                      (g_stOsdServiceData.ucFanPwm2 = (x))

#define GET_OSD_FAN_PWM3()                       (g_stOsdServiceData.ucFanPwm3)
#define SET_OSD_FAN_PWM3(x)                      (g_stOsdServiceData.ucFanPwm3 = (x))

#define GET_OSD_FAN_PWM4()                       (g_stOsdServiceData.ucFanPwm4)
#define SET_OSD_FAN_PWM4(x)                      (g_stOsdServiceData.ucFanPwm4 = (x))
*/
#define GET_OSD_SHUTDOWN_STATUS() (g_stOsdServiceData.b1ShutDownStatus)
#define SET_OSD_SHUTDOWN_STATUS(x) (g_stOsdServiceData.b1ShutDownStatus = (x))

#define GET_OSD_SHUTDOWN_TEMP() (g_stOsdServiceData.b1ShutDownTemp)
#define SET_OSD_SHUTDOWN_TEMP(x) (g_stOsdServiceData.b1ShutDownTemp = (x))

#define GET_OSD_MAX_TEMP() (g_stOsdServiceData.ucMaxTemp)
#define SET_OSD_MAX_TEMP(x) (g_stOsdServiceData.ucMaxTemp = (x))
#endif

//--------------------------------------------------
// MACRO for OLED Setting
//--------------------------------------------------
#if (_ENABLE_MENU_OLED == _ON)
typedef enum
{
    _OFFRS_AUTO,
    //_OFFRS_START_RUN,
    _OFFRS_END_RUN,
    _OFFRS_NOW_RUN,
} EnumOffRsTiming;

#define GET_OSD_OLED_OFFRS_STATUS() (g_stOsdServiceData.ucOLEDOffRsStatus)
#define SET_OSD_OLED_OFFRS_STATUS(x) (g_stOsdServiceData.ucOLEDOffRsStatus = (x))

#define GET_OSD_OLED_SEQUENCE_TIME() (g_stOsdServiceData.ucSequenceTime)
#define SET_OSD_OLED_SEQUENCE_TIME(x) (g_stOsdServiceData.ucSequenceTime = (x))

#define GET_OSD_OLED_JB_STATUS() (g_stOsdServiceData.b1OLEDJBStatus)
#define SET_OSD_OLED_JB_STATUS(x) (g_stOsdServiceData.b1OLEDJBStatus = (x))

//--------------------------------------------------
// MACRO for OFF RS Excute							//Every 4 hours of watching tv
//--------------------------------------------------
#define GET_WAIT_TO_RUN_OFFRS() (g_stOsdServiceData.b1OffRSExcute)
#define SET_WAIT_TO_RUN_OFFRS(x) (g_stOsdServiceData.b1OffRSExcute = (x))

//--------------------------------------------------
// MACRO for JB Compensation Excute					//Every 2000 hours of watching tv
//--------------------------------------------------
#define GET_WAIT_TO_RUN_JB() (g_stOsdServiceData.b1JBCompExcute)
#define SET_WAIT_TO_RUN_JB(x) (g_stOsdServiceData.b1JBCompExcute = (x))

//--------------------------------------------------
// MACRO for Panel Time Min
//--------------------------------------------------
#define GET_JB_MIN() (g_stOsdServiceData.ucJBMin)
#define SET_JB_MIN(x) (g_stOsdServiceData.ucJBMin = (x))

//--------------------------------------------------
// MACRO for Panel Time Hour
//--------------------------------------------------
#define GET_JB_HOUR() (g_stOsdServiceData.usJBHour)
#define SET_JB_HOUR(x) (g_stOsdServiceData.usJBHour = (x))

//--------------------------------------------------
// Macro of Off RS Hour
//--------------------------------------------------
#define GET_OFF_RS_HOUR() (g_stOsdServiceData.ucOffRSHour)
#define SET_OFF_RS_HOUR(x) (g_stOsdServiceData.ucOffRSHour = (x))

//--------------------------------------------------
// Macro of Off RS Min
//--------------------------------------------------
#define GET_OFF_RS_MIN() (g_stOsdServiceData.ucOffRSMin)
#define SET_OFF_RS_MIN(x) (g_stOsdServiceData.ucOffRSMin = (x))

#endif

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR Mode
//--------------------------------------------------
#define GET_OSD_HDR_MODE()                          (g_stOSDUserData.ucHdrMode)
#define SET_OSD_HDR_MODE(x)                         (g_stOSDUserData.ucHdrMode = (x))

//--------------------------------------------------
// MACRO for Dark Enhance Status
//--------------------------------------------------
#define GET_OSD_DARK_ENHANCE_STATUS()               (g_stOSDUserData.b1DarkEnhanceStatus)
#define SET_OSD_DARK_ENHANCE_STATUS(x)              (g_stOSDUserData.b1DarkEnhanceStatus = (x))

//--------------------------------------------------
// MACRO for HDR Sharpness
//--------------------------------------------------
#define GET_OSD_HDR_SHARPNESS()                     (g_stOSDUserData.b1HdrSharpnesse)
#define SET_OSD_HDR_SHARPNESS(x)                    (g_stOSDUserData.b1HdrSharpnesse = (x))

//--------------------------------------------------
// MACRO for HDR Contrast
//--------------------------------------------------
#define GET_OSD_HDR_CONTRAST()                      (g_stOSDUserData.ucHdrContrast)
#define SET_OSD_HDR_CONTRAST(x)                     (g_stOSDUserData.ucHdrContrast = (x))

#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR ColorEnhance
//--------------------------------------------------
#define GET_OSD_HDR_COLOR_ENHANCE()                 (g_stOSDUserData.ucHdrColorEnhance)
#define SET_OSD_HDR_COLOR_ENHANCE(x)                (g_stOSDUserData.ucHdrColorEnhance = (x))
#endif
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR LightEnhance
//--------------------------------------------------
#define GET_OSD_HDR_LIGHT_ENHANCE()                 (g_stOSDUserData.ucHdrLightEnhance)
#define SET_OSD_HDR_LIGHT_ENHANCE(x)                (g_stOSDUserData.ucHdrLightEnhance = (x))
#endif
#endif

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for Local Dimming
//--------------------------------------------------
#define GET_OSD_LOCAL_DIMMING()                     (g_stOSDUserData.b1HdrLocalDimming)
#define SET_OSD_LOCAL_DIMMING(x)                    (g_stOSDUserData.b1HdrLocalDimming = (x))

//--------------------------------------------------
// MACRO for Local Dimming Smooth Backlight adjust
//--------------------------------------------------
#define GET_OSD_LD_ADJ()                            (g_stOSDUserData.ucHdrLocalDimmingAdj)
#define SET_OSD_LD_ADJ(x)                           (g_stOSDUserData.ucHdrLocalDimmingAdj = (x))
#endif

#if (_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for SDR to HDR
//--------------------------------------------------
#define GET_OSD_SDR_TO_HDR()                        (g_stOSDUserData.b1Sdr2HdrStatus)
#define SET_OSD_SDR_TO_HDR(x)                       (g_stOSDUserData.b1Sdr2HdrStatus = (x))
#endif

//--------------------------------------------------
// MACRO for Screen Mute	
//--------------------------------------------------
#define GET_OSD_SCREEN_MUTE()						(g_bScreenMuteSatus)
#define SET_OSD_SCREEN_MUTE(x)						(g_bScreenMuteSatus = (x))

//--------------------------------------------------
// MACRO for Volume Mute
//--------------------------------------------------
#define GET_OSD_VOLUME_MUTE()                       (g_stOSDUserData.b1VolumeMute)
#define SET_OSD_VOLUME_MUTE(x)                      (g_stOSDUserData.b1VolumeMute = (x))

//--------------------------------------------------
// MACRO for Volume
//--------------------------------------------------
#define GET_OSD_VOLUME()                            (g_stOSDUserData.ucVolume)
#define SET_OSD_VOLUME(x)                           (g_stOSDUserData.ucVolume = (x))

//--------------------------------------------------
// MACRO for Audio Stand a long
//--------------------------------------------------
#define GET_OSD_AUDIO_STAND_ALONE()                 (g_stOSDUserData.b1AudioStandAloneStatus)
#define SET_OSD_AUDIO_STAND_ALONE(x)                (g_stOSDUserData.b1AudioStandAloneStatus = (x))

//--------------------------------------------------
// MACRO for Audio Source
//--------------------------------------------------
#define GET_OSD_AUDIO_SOURCE()                      (g_stOSDUserData.b1AudioSourceStatus)
#define SET_OSD_AUDIO_SOURCE(x)                     (g_stOSDUserData.b1AudioSourceStatus = (x))

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
//--------------------------------------------------
// MACRO for Audio TTS Support
//--------------------------------------------------
#define GET_OSD_AUDIO_TTS_SUPPORT()                 (g_stOSDUserData.b1TtsSupport)
#define SET_OSD_AUDIO_TTS_SUPPORT(x)                (g_stOSDUserData.b1TtsSupport = (x))

//--------------------------------------------------
// MACRO for Audio TTS Text Volume
//--------------------------------------------------
#define GET_OSD_AUDIO_TTS_TEXT_VOLUME()             (g_stOSDUserData.ucTtsTextVolume)
#define SET_OSD_AUDIO_TTS_TEXT_VOLUME(x)            (g_stOSDUserData.ucTtsTextVolume = (x))

//--------------------------------------------------
// MACRO for Audio TTS Audio Volume
//--------------------------------------------------
#define GET_OSD_AUDIO_TTS_AUDIO_VOLUME()            (g_stOSDUserData.ucTtsAudioVolume)
#define SET_OSD_AUDIO_TTS_AUDIO_VOLUME(x)           (g_stOSDUserData.ucTtsAudioVolume = (x))

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

//--------------------------------------------------
// MACRO for Hue
//--------------------------------------------------
#define GET_OSD_HUE()                               (g_stOSDUserData.ucHue)
#define SET_OSD_HUE(x)                              (g_stOSDUserData.ucHue = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_SATURATION()                        (g_stOSDUserData.ucSaturation)
#define SET_OSD_SATURATION(x)                       (g_stOSDUserData.ucSaturation = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_OVERSCAN_STATUS()                   (g_stOSDUserData.b1OverScan)
#define SET_OSD_OVERSCAN_STATUS(x)                  (g_stOSDUserData.b1OverScan = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_HLWIN_TYPE()                        (g_stOSDUserData.ucHLWinType)
#define SET_OSD_HLWIN_TYPE(x)                       (g_stOSDUserData.ucHLWinType = (x))

//--------------------------------------------------
// MACRO for 3D Status
//--------------------------------------------------
#define GET_OSD_3D_STATUS()                         (g_stOSDUserData.b23DStatus)
#define SET_OSD_3D_STATUS(x)                        (g_stOSDUserData.b23DStatus = (x))

//--------------------------------------------------
// MACRO for 3D LR Status
//--------------------------------------------------
#define GET_OSD_3D_LR_STATUS()                      (g_stOSDUserData.b13DLRStatus)
#define SET_OSD_3D_LR_STATUS(x)                     (g_stOSDUserData.b13DLRStatus = (x))

//--------------------------------------------------
// MACRO for 3D Format Status
//--------------------------------------------------
#define GET_OSD_3D_FORMAT_STATUS()                  (g_stOSDUserData.b23DFormatStatus)
#define SET_OSD_3D_FORMAT_STATUS(x)                 (g_stOSDUserData.b23DFormatStatus = (x))

//--------------------------------------------------
// MACRO for 3D EFFECT
//--------------------------------------------------
#define GET_OSD_3D_EFFECT()                         (g_stOSDUserData.uc3DEffect)
#define SET_OSD_3D_EFFECT(x)                        (g_stOSDUserData.uc3DEffect = (x))

//--------------------------------------------------
// MACRO for 3D 3DTO2D
//--------------------------------------------------
#define GET_OSD_3D_3DTO2D()                         (g_stOSDUserData.b13D3DTO2DStatus)
#define SET_OSD_3D_3DTO2D(x)                        (g_stOSDUserData.b13D3DTO2DStatus = (x))

//--------------------------------------------------
// MACRO for 3D Convergence
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE()                    (g_stOSDUserData.uc3DConvergence)
#define SET_OSD_3D_CONVERGENCE(x)                   (g_stOSDUserData.uc3DConvergence = (x))

//--------------------------------------------------
// MACRO for 3D Convergence Mode
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE_MODE()               (g_stOSDUserData.b33DConvergenceMode)
#define SET_OSD_3D_CONVERGENCE_MODE(x)              (g_stOSDUserData.b33DConvergenceMode = (x))

//--------------------------------------------------
// MACRO for Auto-Color Type
//--------------------------------------------------
#define _AUTO_COLOR_TYPE_INTERNAL                   0
#define _AUTO_COLOR_TYPE_EXTERNAL                   1

#define GET_OSD_FACTORY_AUTO_COLOR_TYPE()           (g_stOSDUserData.b1FactoryAutoColorType)
#define SET_OSD_FACTORY_AUTO_COLOR_TYPE(x)          (g_stOSDUserData.b1FactoryAutoColorType = (x))

//--------------------------------------------------
// MACRO for PCM Status
//--------------------------------------------------
#define GET_OSD_PCM_STATUS()                        (g_stOSDUserData.b3PCMStatus)
#define SET_OSD_PCM_STATUS(x)                       (g_stOSDUserData.b3PCMStatus = (x))

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for DP Lane Count switch
//--------------------------------------------------
#define GET_OSD_D0_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D0TypeCU3Mode)
#define SET_OSD_D0_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D0TypeCU3Mode = (x))

#define GET_OSD_D1_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D1TypeCU3Mode)
#define SET_OSD_D1_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D1TypeCU3Mode = (x))

#define GET_OSD_D2_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D2TypeCU3Mode)
#define SET_OSD_D2_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D2TypeCU3Mode = (x))

#define GET_OSD_D6_TYPE_C_U3_MODE()                 (g_stOSDUserData.b1D6TypeCU3Mode)
#define SET_OSD_D6_TYPE_C_U3_MODE(x)                (g_stOSDUserData.b1D6TypeCU3Mode = (x))

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for Type-C Pin Assignment E Support Switch
//--------------------------------------------------
#define GET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D0TypeCPinAssignmentESupportSelect)
#define SET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D0TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D1TypeCPinAssignmentESupportSelect)
#define SET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D1TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D2_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D2TypeCPinAssignmentESupportSelect)
#define SET_OSD_D2_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D2TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D6_TYPE_C_PIN_ASSIGNMENT_E_SELECT()  (g_stOSDUserData.b1D6TypeCPinAssignmentESupportSelect)
#define SET_OSD_D6_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x) (g_stOSDUserData.b1D6TypeCPinAssignmentESupportSelect = (x))
#endif
#endif

//--------------------------------------------------
// MACRO for HDMI version
//--------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#define GET_OSD_D0_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD0PortVersion)
#define SET_OSD_D0_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD0PortVersion = (x))

#define GET_OSD_D1_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD1PortVersion)
#define SET_OSD_D1_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD1PortVersion = (x))

#define GET_OSD_D2_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD2PortVersion)
#define SET_OSD_D2_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD2PortVersion = (x))

#define GET_OSD_D3_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD3PortVersion)
#define SET_OSD_D3_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD3PortVersion = (x))

#define GET_OSD_D4_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD4PortVersion)
#define SET_OSD_D4_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD4PortVersion = (x))

#define GET_OSD_D5_HDMI_VER()                       (g_stOSDUserData.b2OsdHdmiD5PortVersion)
#define SET_OSD_D5_HDMI_VER(x)                      (g_stOSDUserData.b2OsdHdmiD5PortVersion = (x))
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Hub UFP Switch marco
//--------------------------------------------------
#define GET_OSD_USB3_RETIMER_PD_WAKEUP()            (g_stOSDUserData.b1OsdUsb3RetimerPDWakeUp)
#define SET_OSD_USB3_RETIMER_PD_WAKEUP(x)           (g_stOSDUserData.b1OsdUsb3RetimerPDWakeUp = (x))
#define GET_OSD_USB3_RETIMER_PS_WAKEUP()            (g_stOSDUserData.b1OsdUsb3RetimerPSWakeUp)
#define SET_OSD_USB3_RETIMER_PS_WAKEUP(x)           (g_stOSDUserData.b1OsdUsb3RetimerPSWakeUp = (x))

//--------------------------------------------------
// Hub UFP Switch marco
//--------------------------------------------------
#define GET_USER_USB_HUB_UFP_SWITCH()               (g_stOSDUserData.enumHubInputPortSwitchbyUser)
#define SET_USER_USB_HUB_UFP_SWITCH(x)              (g_stOSDUserData.enumHubInputPortSwitchbyUser = (x))
#endif

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_NVRAM_DOUBLE_SIZE()                 (g_stOSDUserData.b1OsdDoubleSize)
#define SET_OSD_NVRAM_DOUBLE_SIZE(x)                (g_stOSDUserData.b1OsdDoubleSize = (x))

//--------------------------------------------------
// MACRO for Panel Time Min
//--------------------------------------------------
#define GET_PANEL_TIME_MIN()                        (g_stPanelTimeData.ucMin)
#define SET_PANEL_TIME_MIN(x)                       (g_stPanelTimeData.ucMin = (x))

//--------------------------------------------------
// MACRO for Panel Time Hour
//--------------------------------------------------
#define GET_PANEL_TIME_HOUR()                       (g_stPanelTimeData.usHour)
#define SET_PANEL_TIME_HOUR(x)                      (g_stPanelTimeData.usHour = (x))

//--------------------------------------------------
// MACRO for Factory Power Saving Case
//--------------------------------------------------
#define GET_FORCE_POW_SAV_STATUS()                  (g_bForcePowSavStatus)
#define SET_FORCE_POW_SAV_STATUS(x)                 (g_bForcePowSavStatus = (x))

//--------------------------------------------------
// Definitions of OSD Number ROW COL
//--------------------------------------------------
#define _OSD_NUMBER_1_ROW                           15
#define _OSD_NUMBER_1_COL                           21

#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_BLUE, _CP_BG)
#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_BLUE, _CP_BG)
//--------------------------------------------------
// Definitions of OSD
//--------------------------------------------------
#define _PFONT_PAGE_0                               0
#define _PFONT_PAGE_1                               1
#define _PFONT_PAGE_2                               2
#define _PFONT_PAGE_ITEM_1                          3
#define _PFONT_PAGE_ITEM_2                          4
#define _PFONT_PAGE_ITEM_3                          5
#define _PFONT_PAGE_ITEM_4                          6
#define _PFONT_PAGE_ITEM_5                          7
#define _PFONT_PAGE_ITEM_6                          8
#define _PFONT_PAGE_ITEM_7                          9
#define _PFONT_PAGE_ITEM_8                          10
#define _PFONT_PAGE_ITEM_9                          11
#define _PFONT_PAGE_ITEM_10                         12
#define _PFONT_PAGE_INFORMATION                     13
#define _PFONT_PAGE_3                               14



#define _OSD_GLOBAL_START                           0x01
#define _OSD_GLOBAL_END                             0x0F

#define _OSD_PAGE_0_START                           0x00
#define _OSD_PAGE_0_END                             0x50//0x27				// Section1	( Main Page )					

#define _OSD_PAGE_1_START                           0x51//0x28				// Section2 ( Sub Page )					
#define _OSD_PAGE_1_END                             0x95//0xB0//0xC8//0x5F	

#define _OSD_PAGE_2_START                           0x96//0xB1//0xC1		// Item 	
#define _OSD_PAGE_2_END                             0xDA//0xD5//0xF0

#define _OSD_PAGE_3_START                           0xDB//0xD6				// Section3 ( Item Page ) 	
#define _OSD_PAGE_3_END                             0xFC	

#define _SUB_PAGE_ITEM_1 (_OSD_PAGE_2_START)
#define _SUB_PAGE_ITEM_1_END (_OSD_PAGE_2_START + 10)
#define _SUB_PAGE_ITEM_2 (_SUB_PAGE_ITEM_1_END)
#define _SUB_PAGE_ITEM_2_END (_SUB_PAGE_ITEM_1_END + 10)
#define _SUB_PAGE_ITEM_3 (_SUB_PAGE_ITEM_2_END)
#define _SUB_PAGE_ITEM_3_END (_SUB_PAGE_ITEM_2_END + 10)
#define _SUB_PAGE_ITEM_4 (_SUB_PAGE_ITEM_3_END)
#define _SUB_PAGE_ITEM_4_END (_SUB_PAGE_ITEM_3_END + 10)
#define _SUB_PAGE_ITEM_5 (_SUB_PAGE_ITEM_4_END)
#define _SUB_PAGE_ITEM_5_END (_SUB_PAGE_ITEM_4_END + 6)
#define _SUB_PAGE_ITEM_6 (_SUB_PAGE_ITEM_5_END)
#define _SUB_PAGE_ITEM_6_END (_SUB_PAGE_ITEM_5_END + 6)
#define _SUB_PAGE_ITEM_7 (_SUB_PAGE_ITEM_6_END)
#define _SUB_PAGE_ITEM_7_END (_SUB_PAGE_ITEM_6_END + 6)
#define _SUB_PAGE_ITEM_8 (_SUB_PAGE_ITEM_7_END)
#define _SUB_PAGE_ITEM_8_END (_SUB_PAGE_ITEM_7_END + 10)
/*
#define _SUB_PAGE_ITEM_9                            (_SUB_PAGE_ITEM_8_END)
#define _SUB_PAGE_ITEM_9_END                        (_SUB_PAGE_ITEM_8_END + 6)	
#define _SUB_PAGE_ITEM_10                           (_SUB_PAGE_ITEM_9_END)
#define _SUB_PAGE_ITEM_10_END                       (_SUB_PAGE_ITEM_9_END + 10)	
*/


#define _OSD_PAGE_INFORMATION_START                 0x51//0x28//0x51//0x28		
#define _OSD_PAGE_INFORMATION_END                   0xFF

#define _NORMAL                                     0
#define _CENTER                                     1
#define _START                                      0
#define _RUN                                        1

#define _UP                                         0
#define _DOWN                                       1

#define _OUTSUBSET                                  0
#define _INSUBSET                                   1

//--------------------------------------------------
// Definitions of OSD Window
//--------------------------------------------------
//=========== OSD Window Setting ======================//
//Blending type1:Only windows blending.
//Blending type2:All blending.
//Blending type3:Windows & Character background blending.
#define _WIN0                                       0
#define _WIN1                                       1
#define _WIN2                                       2
#define _WIN3                                       3
#define _WIN4                                       4
#define _WIN5                                       5
#define _WIN6                                       6
#define _WIN7                                       7
#define _WIN8                                       8
#define _WIN9                                       9
#define _WIN_ALL                                    0xFF

#define _WIN0_TRANS                                 (_BIT7 | 0)
#define _WIN1_TRANS                                 (_BIT7 | 1)
#define _WIN2_TRANS                                 (_BIT7 | 2)
#define _WIN3_TRANS                                 (_BIT7 | 3)
#define _WIN4_TRANS                                 (_BIT7 | 4)
#define _WIN5_TRANS                                 (_BIT7 | 5)
#define _WIN6_TRANS                                 (_BIT7 | 6)
#define _WIN7_TRANS                                 (_BIT7 | 7)

#define COLOR(fg, bg)                               ((fg) << 4 | (bg))
#define COLOR0(x)                                   (x)
#define COLOR1(x)                                   (x)
#define COLOR2(x)                                   (x)
#define COLOR3(x)                                   (x)

#define X_START(x)                                  (x)
#define Y_START(x)                                  (x)
#define X_END(x)                                    (x)
#define Y_END(x)                                    (x)

#define _BORDER0_1_PIXEL                            0
#define _BORDER0_2_PIXEL                            1
#define _BORDER0_3_PIXEL                            2
#define _BORDER0_4_PIXEL                            3
#define _BORDER0_5_PIXEL                            4
#define _BORDER0_6_PIXEL                            5
#define _BORDER0_7_PIXEL                            6
#define _BORDER0_8_PIXEL                            7

#define _BORDER1_1_PIXEL                            0x00
#define _BORDER1_2_PIXEL                            0x08
#define _BORDER1_3_PIXEL                            0x10
#define _BORDER1_4_PIXEL                            0x18
#define _BORDER1_5_PIXEL                            0x20
#define _BORDER1_6_PIXEL                            0x28
#define _BORDER1_7_PIXEL                            0x30
#define _BORDER1_8_PIXEL                            0x38

#define _BLEND_DISABLE                              0
#define _BLEND_ENABLE                               0x80
#define _GRADIENT_DISABLE                           0
#define _GRADIENT_ENABLE                            0x40
#define _GRADIENT_DIRECTION_H                       0
#define _GRADIENT_DIRECTION_V                       0x20
#define _BORDER_DISABLE                             0
#define _BORDER_ENABLE                              0x10

#define _1_LEVEL_RER_GRADIENT                       0x20
#define _2_LEVEL_RER_GRADIENT                       0x40
#define _3_LEVEL_RER_GRADIENT                       0x60
#define _4_LEVEL_RER_GRADIENT                       0x80
#define _5_LEVEL_RER_GRADIENT                       0xA0
#define _6_LEVEL_RER_GRADIENT                       0xC0
#define _7_LEVEL_RER_GRADIENT                       0xE0
#define _8_LEVEL_RER_GRADIENT                       0x00

#define _R_GRADIENT_DEC                             0x00
#define _R_GRADIENT_INC                             0x80
#define _G_GRADIENT_DEC                             0x00
#define _G_GRADIENT_INC                             0x40
#define _B_GRADIENT_DEC                             0x00
#define _B_GRADIENT_INC                             0x20

#define _GRADIENT_LEVEL_1                           0
#define _GRADIENT_LEVEL_2                           0x08
#define _GRADIENT_LEVEL_3                           0x10
#define _GRADIENT_LEVEL_4                           0x18

#define _R_GRADIENT_ENABLE                          0x04
#define _R_GRADIENT_DISABLE                         0x00
#define _G_GRADIENT_ENABLE                          0x02
#define _G_GRADIENT_DISABLE                         0x00
#define _B_GRADIENT_ENABLE                          0x01
#define _B_GRADIENT_DISABLE                         0x00

#define _SHADOW_1                                   0x00
#define _SHADOW_2                                   0x02
#define _SHADOW_3                                   0x04
#define _SHADOW_4                                   0x06
#define _3D_BUTTON_1                                0x08
#define _3D_BUTTON_2                                0x0A

#define _WIN0_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN0_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)

#define _WIN0_FUNC_CONTROL                          (_BLEND_ENABLE | _GRADIENT_DISABLE | _GRADIENT_DIRECTION_H | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN0_GRADIENT_CONTROL0                     (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_3 | _R_GRADIENT_INC | _G_GRADIENT_INC | _B_GRADIENT_INC)
#define _WIN0_GRADIENT_CONTROL1                     (_3_LEVEL_RER_GRADIENT)

#define _WIN0_ROTATE_BORDER_PIXEL                   (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN0_ROTATE_BORDER_COLOR                   ((_CP_DARKBLUE << 4) | _CP_DARKBLUE)
#define _WIN0_ROTATE_FUNC_CONTROL                   (_BLEND_ENABLE | _GRADIENT_ENABLE | _GRADIENT_DIRECTION_V | _BORDER_ENABLE | _SHADOW_3)
#define _WIN0_ROTATE_GRADIENT_CONTROL0              (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_4 | _R_GRADIENT_DEC | _G_GRADIENT_DEC | _B_GRADIENT_DEC)
#define _WIN0_ROTATE_GRADIENT_CONTROL1              (_3_LEVEL_RER_GRADIENT)

#define _WIN1_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN1_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)

#define _WIN1_FUNC_CONTROL                          (_BLEND_ENABLE | _GRADIENT_DISABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN1_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN1_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN2_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN2_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN2_FUNC_CONTROL                          (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN2_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN2_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN3_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN3_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN3_FUNC_CONTROL                          (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN3_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN3_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN7_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN7_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN7_FUNC_CONTROL                          (_BLEND_ENABLE)
#define _WIN7_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN7_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN0_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN0_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN0_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN0_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN0_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN1_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN1_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN1_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN1_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN1_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN2_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN2_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN2_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN2_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN2_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN3_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN3_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN3_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN3_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN3_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN4_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN4_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN4_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN4_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN4_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN5_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN5_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN5_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN5_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN5_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN6_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN6_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN6_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN6_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN6_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN7_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN7_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN7_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN7_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN7_TRANS_GRADIENT_CONTROL1               (_DISABLE)



#define _OSD_UNSELECT                               0
#define _OSD_SELECT                                 1
#define _OSD_REJECT                                 2
#define _OSD_ADJUST                                 3
#define _OSD_UNHIGHLIGHT                            4
#define _OSD_HIGHLIGHT                              5
#define _OSD_PRE_SELECT                             6
#define _OSD_SELECT_ADJUST                          7


#define _KEY_INFO_ENTER                             0
#define _KEY_INFO_RIGHT                             1
#define _KEY_INFO_LEFT                              2
#define _KEY_INFO_EXIT                              3
#define _KEY_INFO_BACK                              4
#define _KEY_INFO_ALL                               5   // exit, left, right, enter

//=========== OSD Font Icon Address ======================//
#define _1GLOBAL_START                              0x00                        // Global 49
#define _1DYNAMIC_START                             (_1GLOBAL_START + 50)       // Dynamic 0
#define _1DYNAMIC_ICON_START                        (_1DYNAMIC_START + 0)       // main menu icon (6 x 4 x 8) = 196
#define _2DYNAMIC_START                             0x00
#define _2BIT_ICON_OFFSET                           0xFF

#define _LOGO_START_ADDRESS                         0x00

//=============== 1Bit Icon ========================

typedef enum
{
    ___ = 0,
    _iREALTEK_00,
    _iREALTEK_01,
    _iREALTEK_02,
    _iREALTEK_03,
    _iREALTEK_04,
    _iREALTEK_05,
    _iREALTEK_06,
    _iREALTEK_07,
    _iREALTEK_08,
    _iREALTEK_09,
    _iREALTEK_0A,
    _iREALTEK_0B,
    _iREALTEK_10,
    _iREALTEK_11,
    _iREALTEK_12,
    _iREALTEK_13,
    _iREALTEK_14,
    _iREALTEK_15,
    _iREALTEK_16,
    _iREALTEK_17,
    _iREALTEK_18,
    _iREALTEK_19,
    _iREALTEK_1A,
    _iREALTEK_1B,
    _iLEFT_00,
    _iLEFT_01,
    _iRIGHT_00,
    _iRIGHT_01,
    _iKEY_BACK_00,
    _iKEY_BACK_01,
    _iKEY_BACK_10,
    _iKEY_BACK_11,
    _iKEY_LEFT_00,
    _iKEY_LEFT_01,
    _iKEY_LEFT_10,
    _iKEY_LEFT_11,
    _iKEY_RIGHT_00,
    _iKEY_RIGHT_01,
    _iKEY_RIGHT_10,
    _iKEY_RIGHT_11,
    _iKEY_ENTER_00,
    _iKEY_ENTER_01,
    _iKEY_ENTER_10,
    _iKEY_ENTER_11,
    _iKEY_EXIT_00,
    _iKEY_EXIT_01,
    _iKEY_EXIT_10,
    _iKEY_EXIT_11,
    _iINDICATE,
}EnumOneBitGLOBAL;

// RTD LOGO
/*
#define _LOGO_WINDOW_SIZE_X                         839
#define _LOGO_WINDOW_SIZE_Y                         179

#define _Logo_0x00                                  0x00
#define _Logo_0x01                                  (_Logo_0x00 + 0x01)
#define _Logo_0x02                                  (_Logo_0x00 + 0x02)
#define _Logo_0x03                                  (_Logo_0x00 + 0x03)
#define _Logo_0x04                                  (_Logo_0x00 + 0x04)
#define _Logo_0x05                                  (_Logo_0x00 + 0x05)
#define _Logo_0x06                                  (_Logo_0x00 + 0x06)
#define _Logo_0x07                                  (_Logo_0x00 + 0x07)
#define _Logo_0x08                                  (_Logo_0x00 + 0x08)
#define _Logo_0x09                                  (_Logo_0x00 + 0x09)
#define _Logo_0x0a                                  (_Logo_0x00 + 0x0a)
#define _Logo_0x0b                                  (_Logo_0x00 + 0x0b)
#define _Logo_0x0c                                  (_Logo_0x00 + 0x0c)
#define _Logo_0x0d                                  (_Logo_0x00 + 0x0d)
#define _Logo_0x0e                                  (_Logo_0x00 + 0x0e)
#define _Logo_0x0f                                  (_Logo_0x00 + 0x0f)
#define _Logo_0x10                                  (_Logo_0x00 + 0x10)
#define _Logo_0x11                                  (_Logo_0x00 + 0x11)
#define _Logo_0x12                                  (_Logo_0x00 + 0x12)
#define _Logo_0x13                                  (_Logo_0x00 + 0x13)
#define _Logo_0x14                                  (_Logo_0x00 + 0x14)
#define _Logo_0x15                                  (_Logo_0x00 + 0x15)
#define _Logo_0x16                                  (_Logo_0x00 + 0x16)
#define _Logo_0x17                                  (_Logo_0x00 + 0x17)
#define _Logo_0x18                                  (_Logo_0x00 + 0x18)
#define _Logo_0x19                                  (_Logo_0x00 + 0x19)
#define _Logo_0x1a                                  (_Logo_0x00 + 0x1a)
#define _Logo_0x1b                                  (_Logo_0x00 + 0x1b)
#define _Logo_0x1c                                  (_Logo_0x00 + 0x1c)
#define _Logo_0x1d                                  (_Logo_0x00 + 0x1d)
#define _Logo_0x1e                                  (_Logo_0x00 + 0x1e)
#define _Logo_0x1f                                  (_Logo_0x00 + 0x1f)
#define _Logo_0x20                                  (_Logo_0x00 + 0x20)
#define _Logo_0x21                                  (_Logo_0x00 + 0x21)
#define _Logo_0x22                                  (_Logo_0x00 + 0x22)
#define _Logo_0x23                                  (_Logo_0x00 + 0x23)
#define _Logo_0x24                                  (_Logo_0x00 + 0x24)
#define _Logo_0x25                                  (_Logo_0x00 + 0x25)
#define _Logo_0x26                                  (_Logo_0x00 + 0x26)
#define _Logo_0x27                                  (_Logo_0x00 + 0x27)
#define _Logo_0x28                                  (_Logo_0x00 + 0x28)
#define _Logo_0x29                                  (_Logo_0x00 + 0x29)
#define _Logo_0x2a                                  (_Logo_0x00 + 0x2a)
#define _Logo_0x2b                                  (_Logo_0x00 + 0x2b)
#define _Logo_0x2c                                  (_Logo_0x00 + 0x2c)
#define _Logo_0x2d                                  (_Logo_0x00 + 0x2d)
#define _Logo_0x2e                                  (_Logo_0x00 + 0x2e)
#define _Logo_0x2f                                  (_Logo_0x00 + 0x2f)
#define _Logo_0x30                                  (_Logo_0x00 + 0x30)
#define _Logo_0x31                                  (_Logo_0x00 + 0x31)
#define _Logo_0x32                                  (_Logo_0x00 + 0x32)
#define _Logo_0x33                                  (_Logo_0x00 + 0x33)
#define _Logo_0x34                                  (_Logo_0x00 + 0x34)
#define _Logo_0x35                                  (_Logo_0x00 + 0x35)
#define _Logo_0x36                                  (_Logo_0x00 + 0x36)
#define _Logo_0x37                                  (_Logo_0x00 + 0x37)
#define _Logo_0x38                                  (_Logo_0x00 + 0x38)
#define _Logo_0x39                                  (_Logo_0x00 + 0x39)
#define _Logo_0x3a                                  (_Logo_0x00 + 0x3a)
#define _Logo_0x3b                                  (_Logo_0x00 + 0x3b)
#define _Logo_0x3c                                  (_Logo_0x00 + 0x3c)
#define _Logo_0x3d                                  (_Logo_0x00 + 0x3d)
#define _Logo_0x3e                                  (_Logo_0x00 + 0x3e)
#define _Logo_0x3f                                  (_Logo_0x00 + 0x3f)
#define _Logo_0x40                                  (_Logo_0x00 + 0x40)
#define _Logo_0x41                                  (_Logo_0x00 + 0x41)
#define _Logo_0x42                                  (_Logo_0x00 + 0x42)
#define _Logo_0x43                                  (_Logo_0x00 + 0x43)
#define _Logo_0x44                                  (_Logo_0x00 + 0x44)
#define _Logo_0x45                                  (_Logo_0x00 + 0x45)
#define _Logo_0x46                                  (_Logo_0x00 + 0x46)
#define _Logo_0x47                                  (_Logo_0x00 + 0x47)
#define _Logo_0x48                                  (_Logo_0x00 + 0x48)
#define _Logo_0x49                                  (_Logo_0x00 + 0x49)
#define _Logo_0x4a                                  (_Logo_0x00 + 0x4a)
#define _Logo_0x4b                                  (_Logo_0x00 + 0x4b)
#define _Logo_0x4c                                  (_Logo_0x00 + 0x4c)
#define _Logo_0x4d                                  (_Logo_0x00 + 0x4d)
#define _Logo_0x4e                                  (_Logo_0x00 + 0x4e)
#define _Logo_0x4f                                  (_Logo_0x00 + 0x4f)
#define _Logo_0x50_End                              (_Logo_0x00 + 0x50)

#define _Logo1_0x00                                 (_Logo_0x50_End + 0x00)
#define _Logo1_0x01                                 (_Logo1_0x00 + 0x01)
#define _Logo1_0x02                                 (_Logo1_0x00 + 0x02)
#define _Logo1_0x03                                 (_Logo1_0x00 + 0x03)
#define _Logo1_0x04                                 (_Logo1_0x00 + 0x04)
#define _Logo1_0x05                                 (_Logo1_0x00 + 0x05)
#define _Logo1_0x06                                 (_Logo1_0x00 + 0x06)
#define _Logo1_0x07                                 (_Logo1_0x00 + 0x07)
#define _Logo1_0x08                                 (_Logo1_0x00 + 0x08)
#define _Logo1_0x09                                 (_Logo1_0x00 + 0x09)
#define _Logo1_0x0a                                 (_Logo1_0x00 + 0x0a)
#define _Logo1_0x0b                                 (_Logo1_0x00 + 0x0b)
#define _Logo1_0x0c                                 (_Logo1_0x00 + 0x0c)
#define _Logo1_0x0d                                 (_Logo1_0x00 + 0x0d)
#define _Logo1_0x0e                                 (_Logo1_0x00 + 0x0e)
#define _Logo1_0x0f                                 (_Logo1_0x00 + 0x0f)
#define _Logo1_0x10                                 (_Logo1_0x00 + 0x10)
#define _Logo1_0x11                                 (_Logo1_0x00 + 0x11)
#define _Logo1_0x12                                 (_Logo1_0x00 + 0x12)
#define _Logo1_0x13                                 (_Logo1_0x00 + 0x13)
#define _Logo1_0x14                                 (_Logo1_0x00 + 0x14)
#define _Logo1_0x15                                 (_Logo1_0x00 + 0x15)
#define _Logo1_0x16                                 (_Logo1_0x00 + 0x16)
#define _Logo1_0x17                                 (_Logo1_0x00 + 0x17)
#define _Logo1_0x18                                 (_Logo1_0x00 + 0x18)
#define _Logo1_0x19                                 (_Logo1_0x00 + 0x19)
#define _Logo1_0x1a                                 (_Logo1_0x00 + 0x1a)
#define _Logo1_0x1b                                 (_Logo1_0x00 + 0x1b)
#define _Logo1_0x1c                                 (_Logo1_0x00 + 0x1c)
#define _Logo1_0x1d                                 (_Logo1_0x00 + 0x1d)
#define _Logo1_0x1e                                 (_Logo1_0x00 + 0x1e)
#define _Logo1_0x1f                                 (_Logo1_0x00 + 0x1f)
#define _Logo1_0x20                                 (_Logo1_0x00 + 0x20)
#define _Logo1_0x21                                 (_Logo1_0x00 + 0x21)
#define _Logo1_0x22                                 (_Logo1_0x00 + 0x22)
#define _Logo1_0x23                                 (_Logo1_0x00 + 0x23)
#define _Logo1_0x24                                 (_Logo1_0x00 + 0x24)
#define _Logo1_0x25                                 (_Logo1_0x00 + 0x25)
#define _Logo1_0x26                                 (_Logo1_0x00 + 0x26)
#define _Logo1_0x27                                 (_Logo1_0x00 + 0x27)
#define _Logo1_0x28                                 (_Logo1_0x00 + 0x28)
#define _Logo1_0x29                                 (_Logo1_0x00 + 0x29)
#define _Logo1_0x2a                                 (_Logo1_0x00 + 0x2a)
#define _Logo1_0x2b                                 (_Logo1_0x00 + 0x2b)
#define _Logo1_0x2c                                 (_Logo1_0x00 + 0x2c)
#define _Logo1_0x2d                                 (_Logo1_0x00 + 0x2d)
#define _Logo1_0x2e                                 (_Logo1_0x00 + 0x2e)
#define _Logo1_0x2f                                 (_Logo1_0x00 + 0x2f)
#define _Logo1_0x30                                 (_Logo1_0x00 + 0x30)
#define _Logo1_0x31                                 (_Logo1_0x00 + 0x31)
#define _Logo1_0x32                                 (_Logo1_0x00 + 0x32)
#define _Logo1_0x33                                 (_Logo1_0x00 + 0x33)
#define _Logo1_0x34                                 (_Logo1_0x00 + 0x34)
#define _Logo1_0x35                                 (_Logo1_0x00 + 0x35)
#define _Logo1_0x36                                 (_Logo1_0x00 + 0x36)
#define _Logo1_0x37                                 (_Logo1_0x00 + 0x37)
#define _Logo1_0x38                                 (_Logo1_0x00 + 0x38)
#define _Logo1_0x39                                 (_Logo1_0x00 + 0x39)
#define _Logo1_0x3a                                 (_Logo1_0x00 + 0x3a)
#define _Logo1_0x3b                                 (_Logo1_0x00 + 0x3b)
#define _Logo1_0x3c                                 (_Logo1_0x00 + 0x3c)
#define _Logo1_0x3d                                 (_Logo1_0x00 + 0x3d)
#define _Logo1_0x3e                                 (_Logo1_0x00 + 0x3e)
#define _Logo1_0x3f                                 (_Logo1_0x00 + 0x3f)
#define _Logo1_0x40                                 (_Logo1_0x00 + 0x40)
#define _Logo1_0x41                                 (_Logo1_0x00 + 0x41)
#define _Logo1_0x42                                 (_Logo1_0x00 + 0x42)
#define _Logo1_0x43                                 (_Logo1_0x00 + 0x43)
#define _Logo1_0x44                                 (_Logo1_0x00 + 0x44)
#define _Logo1_0x45                                 (_Logo1_0x00 + 0x45)
#define _Logo1_0x46                                 (_Logo1_0x00 + 0x46)

//=============== 2Bit Icon ========================
*/
#if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
#define _LOGO_WINDOW_SIZE_X                        ((0x4b) * 12)// 839
#define _LOGO_WINDOW_SIZE_Y                         (0x06 * 18)

#define    _Logo_0x00        0x00
#define    _Logo_0x01        0x01
#define    _Logo_0x02        0x02
#define    _Logo_0x03        0x03
#define    _Logo_0x04        0x04
#define    _Logo_0x05        0x05
#define    _Logo_0x06        0x06
#define    _Logo_0x07        0x07
#define    _Logo_0x08        0x08
#define    _Logo_0x09        0x09
#define    _Logo_0x0a        0x0a
#define    _Logo_0x0b        0x0b
#define    _Logo_0x0c        0x0c
#define    _Logo_0x0d        0x0d
#define    _Logo_0x0e        0x0e
#define    _Logo_0x0f        0x0f
#define    _Logo_0x10        0x10
#define    _Logo_0x11        0x11
#define    _Logo_0x12        0x12
#define    _Logo_0x13        0x13
#define    _Logo_0x14        0x14
#define    _Logo_0x15        0x15
#define    _Logo_0x16        0x16
#define    _Logo_0x17        0x17
#define    _Logo_0x18        0x18
#define    _Logo_0x19        0x19
#define    _Logo_0x1a        0x1a
#define    _Logo_0x1b        0x1b
#define    _Logo_0x1c        0x1c
#define    _Logo_0x1d        0x1d
#define    _Logo_0x1e        0x1e
#define    _Logo_0x1f        0x1f
#define    _Logo_0x20        0x20
#define    _Logo_0x21        0x21
#define    _Logo_0x22        0x22
#define    _Logo_0x23        0x23
#define    _Logo_0x24        0x24
#define    _Logo_0x25        0x25
#define    _Logo_0x26        0x26
#define    _Logo_0x27        0x27
#define    _Logo_0x28        0x28
#define    _Logo_0x29        0x29
#define    _Logo_0x2a        0x2a
#define    _Logo_0x2b        0x2b
#define    _Logo_0x2c        0x2c
#define    _Logo_0x2d        0x2d
#define    _Logo_0x2e        0x2e
#define    _Logo_0x2f        0x2f
#define    _Logo_0x30        0x30
#define    _Logo_0x31        0x31
#define    _Logo_0x32        0x32
#define    _Logo_0x33        0x33
#define    _Logo_0x34        0x34
#define    _Logo_0x35        0x35
#define    _Logo_0x36        0x36
#define    _Logo_0x37        0x37
#define    _Logo_0x38        0x38
#define    _Logo_0x39        0x39
#define    _Logo_0x3a        0x3a
#define    _Logo_0x3b        0x3b
#define    _Logo_0x3c        0x3c
#define    _Logo_0x3d        0x3d
#define    _Logo_0x3e        0x3e
#define    _Logo_0x3f        0x3f
#define    _Logo_0x40        0x40
#define    _Logo_0x41        0x41
#define    _Logo_0x42        0x42
#define    _Logo_0x43        0x43
#define    _Logo_0x44        0x44
#define    _Logo_0x45        0x45
#define    _Logo_0x46        0x46
#define    _Logo_0x47        0x47
#define    _Logo_0x48        0x48
#define    _Logo_0x49        0x49
#define    _Logo_0x4a        0x4a
#define    _Logo_0x4b        0x4b
#define    _Logo_0x4c        0x4c
#define    _Logo_0x4d        0x4d
#define    _Logo_0x4e        0x4e
#define    _Logo_0x4f        0x4f
#define    _Logo_0x50        0x50
#define    _Logo_0x51        0x51
#define    _Logo_0x52        0x52
#define    _Logo_0x53        0x53
#define    _Logo_0x54        0x54
#define    _Logo_0x54_End        0x55




#define _Logo1_0x00                                 (_Logo_0x54_End + 0x00)
#define _Logo1_0x01                                 (_Logo1_0x00 + 0x01)
#define _Logo1_0x02                                 (_Logo1_0x00 + 0x02)
#define _Logo1_0x03                                 (_Logo1_0x00 + 0x03)
#define _Logo1_0x04                                 (_Logo1_0x00 + 0x04)
#define _Logo1_0x05                                 (_Logo1_0x00 + 0x05)
#define _Logo1_0x06                                 (_Logo1_0x00 + 0x06)
#define _Logo1_0x07                                 (_Logo1_0x00 + 0x07)
#define _Logo1_0x08                                 (_Logo1_0x00 + 0x08)
#define _Logo1_0x09                                 (_Logo1_0x00 + 0x09)
#define _Logo1_0x0a                                 (_Logo1_0x00 + 0x0a)
#define _Logo1_0x0b                                 (_Logo1_0x00 + 0x0b)
#define _Logo1_0x0c                                 (_Logo1_0x00 + 0x0c)
#define _Logo1_0x0d                                 (_Logo1_0x00 + 0x0d)
#define _Logo1_0x0e                                 (_Logo1_0x00 + 0x0e)
#define _Logo1_0x0f                                 (_Logo1_0x00 + 0x0f)
#define _Logo1_0x10                                 (_Logo1_0x00 + 0x10)
#define _Logo1_0x11                                 (_Logo1_0x00 + 0x11)
#define _Logo1_0x12                                 (_Logo1_0x00 + 0x12)
#define _Logo1_0x13                                 (_Logo1_0x00 + 0x13)
#define _Logo1_0x14                                 (_Logo1_0x00 + 0x14)
#define _Logo1_0x15                                 (_Logo1_0x00 + 0x15)
#define _Logo1_0x16                                 (_Logo1_0x00 + 0x16)
#define _Logo1_0x17                                 (_Logo1_0x00 + 0x17)
#define _Logo1_0x18                                 (_Logo1_0x00 + 0x18)
#define _Logo1_0x19                                 (_Logo1_0x00 + 0x19)
#define _Logo1_0x1a                                 (_Logo1_0x00 + 0x1a)
#define _Logo1_0x1b                                 (_Logo1_0x00 + 0x1b)
#define _Logo1_0x1c                                 (_Logo1_0x00 + 0x1c)
#define _Logo1_0x1d                                 (_Logo1_0x00 + 0x1d)
#define _Logo1_0x1e                                 (_Logo1_0x00 + 0x1e)
#define _Logo1_0x1f                                 (_Logo1_0x00 + 0x1f)
#define _Logo1_0x20                                 (_Logo1_0x00 + 0x20)
#define _Logo1_0x21                                 (_Logo1_0x00 + 0x21)
#define _Logo1_0x22                                 (_Logo1_0x00 + 0x22)
#define _Logo1_0x23                                 (_Logo1_0x00 + 0x23)
#define _Logo1_0x24                                 (_Logo1_0x00 + 0x24)
#define _Logo1_0x25                                 (_Logo1_0x00 + 0x25)
#define _Logo1_0x26                                 (_Logo1_0x00 + 0x26)
#define _Logo1_0x27                                 (_Logo1_0x00 + 0x27)
#define _Logo1_0x28                                 (_Logo1_0x00 + 0x28)
#define _Logo1_0x29                                 (_Logo1_0x00 + 0x29)
#define _Logo1_0x2a                                 (_Logo1_0x00 + 0x2a)
#define _Logo1_0x2b                                 (_Logo1_0x00 + 0x2b)
#define _Logo1_0x2c                                 (_Logo1_0x00 + 0x2c)
#define _Logo1_0x2d                                 (_Logo1_0x00 + 0x2d)
#define _Logo1_0x2e                                 (_Logo1_0x00 + 0x2e)
#define _Logo1_0x2f                                 (_Logo1_0x00 + 0x2f)
#define _Logo1_0x30                                 (_Logo1_0x00 + 0x30)
#define _Logo1_0x31                                 (_Logo1_0x00 + 0x31)
#define _Logo1_0x32                                 (_Logo1_0x00 + 0x32)
#define _Logo1_0x33                                 (_Logo1_0x00 + 0x33)
#define _Logo1_0x34                                 (_Logo1_0x00 + 0x34)
#define _Logo1_0x35                                 (_Logo1_0x00 + 0x35)
#define _Logo1_0x36                                 (_Logo1_0x00 + 0x36)
#define _Logo1_0x37                                 (_Logo1_0x00 + 0x37)
#define _Logo1_0x38                                 (_Logo1_0x00 + 0x38)


#elif	(_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
	#define _LOGO_WINDOW_SIZE_X			((0x47) * 12)// 839
	#define _LOGO_WINDOW_SIZE_Y			17*18	// (0x0b * 18)

	#define _Logo_0x00		0x00
	#define _Logo_0x01		0x01
	#define _Logo_0x02		0x02
	#define _Logo_0x03		0x03
	#define _Logo_0x04		0x04
	#define _Logo_0x05		0x05
	#define _Logo_0x06		0x06
	#define _Logo_0x07		0x07
	#define _Logo_0x08		0x08
	#define _Logo_0x09		0x09
	#define _Logo_0x0a		0x0A
	#define _Logo_0x0b		0x0B
	#define _Logo_0x0c		0x0C
	#define _Logo_0x0d		0x0D
	#define _Logo_0x0e		0x0E
	#define _Logo_0x0f		0x0F
	#define _Logo_0x10		0x10
	#define _Logo_0x11		0x11
	#define _Logo_0x12		0x12
	#define _Logo_0x13		0x13
	#define _Logo_0x14		0x14
	#define _Logo_0x15		0x15
	#define _Logo_0x16		0x16
	#define _Logo_0x17		0x17
	#define _Logo_0x18		0x18
	#define _Logo_0x19		0x19
	#define _Logo_0x1a		0x1A
	#define _Logo_0x1b		0x1B
	#define _Logo_0x1c		0x1C
	#define _Logo_0x1d		0x1D
	#define _Logo_0x1e		0x1E
	#define _Logo_0x1f		0x1F
	#define _Logo_0x20		0x20
	#define _Logo_0x21		0x21
	#define _Logo_0x22		0x22
	#define _Logo_0x23		0x23
	#define _Logo_0x24		0x24
	#define _Logo_0x25		0x25
	#define _Logo_0x26		0x26
	#define _Logo_0x27		0x27
	#define _Logo_0x28		0x28
	#define _Logo_0x29		0x29
	#define _Logo_0x2a		0x2A
	#define _Logo_0x2b		0x2B
	#define _Logo_0x2c		0x2C
	#define _Logo_0x2d		0x2D
	#define _Logo_0x2e		0x2E
	#define _Logo_0x2f		0x2F
	#define _Logo_0x30		0x30
	#define _Logo_0x31		0x31
	#define _Logo_0x32		0x32
	#define _Logo_0x33		0x33
	#define _Logo_0x34		0x34
	#define _Logo_0x35		0x35
	#define _Logo_0x36		0x36
	#define _Logo_0x37		0x37
	#define _Logo_0x38		0x38
	#define _Logo_0x39		0x39
	#define _Logo_0x3a		0x3A
	#define _Logo_0x3b		0x3B
	#define _Logo_0x3c		0x3C
	#define _Logo_0x3d		0x3D
	#define _Logo_0x3e		0x3E
	#define _Logo_0x3f		0x3F
	#define _Logo_0x40		0x40
	#define _Logo_0x41		0x41
	#define _Logo_0x42		0x42
	#define _Logo_0x43		0x43
	#define _Logo_0x44		0x44
	#define _Logo_0x45		0x45
	#define _Logo_0x46		0x46
	#define _Logo_0x47		0x47
	#define _Logo_0x48		0x48
	#define _Logo_0x49		0x49
	#define _Logo_0x4a		0x4A
	#define _Logo_0x4b		0x4B
	#define _Logo_0x4c		0x4C
	#define _Logo_0x4d		0x4D
	#define _Logo_0x4e		0x4E
	#define _Logo_0x4f		0x4F
	#define _Logo_0x50		0x50
	#define _Logo_0x51		0x51
	#define _Logo_0x52		0x52
	#define _Logo_0x53		0x53
	#define _Logo_0x54		0x54
	#define _Logo_0x55		0x55
	#define _Logo_0x56		0x56
	#define _Logo_0x57		0x57
	#define _Logo_0x58		0x58
	#define _Logo_0x59		0x59
	#define _Logo_0x5a		0x5A
	#define _Logo_0x5b		0x5B
	#define _Logo_0x5c		0x5C
	#define _Logo_0x5d		0x5D
	#define _Logo_0x5e		0x5E
	#define _Logo_0x5f		0x5F
	#define _Logo_0x60		0x60
	#define _Logo_0x61		0x61
	#define _Logo_0x62		0x62
	#define _Logo_0x63		0x63
	#define _Logo_0x64		0x64
	#define _Logo_0x65		0x65
	#define _Logo_0x66		0x66
	#define _Logo_0x67		0x67
	#define _Logo_0x68		0x68
	#define _Logo_0x69		0x69
	#define _Logo_0x6a		0x6A
	#define _Logo_0x6b		0x6B
	#define _Logo_0x6c		0x6C
	#define _Logo_0x6d		0x6D
	#define _Logo_0x6e		0x6E
	#define _Logo_0x6f		0x6F
	#define _Logo_0x70		0x70
	#define _Logo_0x71		0x71
	#define _Logo_0x72		0x72
	#define _Logo_0x73		0x73
	#define _Logo_0x74		0x74
	#define _Logo_0x75		0x75
	#define _Logo_0x76		0x76
	#define _Logo_0x77		0x77
	#define _Logo_0x78		0x78
	#define _Logo_0x79		0x79
	#define _Logo_0x7a		0x7A
	#define _Logo_0x7b		0x7B
	#define _Logo_0x7c		0x7C
	#define _Logo_0x7d		0x7D
	#define _Logo_0x7e		0x7E
	#define _Logo_0x7f		0x7F
	#define _Logo_0x80		0x80
	#define _Logo_0x81		0x81
	#define _Logo_0x82		0x82
	#define _Logo_0x83		0x83
	#define _Logo_0x84		0x84
	#define _Logo_0x85		0x85
	#define _Logo_0x86		0x86
	#define _Logo_0x87		0x87
	#define _Logo_0x88		0x88
	#define _Logo_0x89		0x89
	#define _Logo_0x8a		0x8A
	#define _Logo_0x8b		0x8B
	#define _Logo_0x8c		0x8C
	#define _Logo_0x8d		0x8D
	#define _Logo_0x8e		0x8E
	#define _Logo_0x8f		0x8F
	#define _Logo_0x90		0x90
	#define _Logo_0x91		0x91
	#define _Logo_0x92		0x92
	#define _Logo_0x93		0x93
	#define _Logo_0x94		0x94
	#define _Logo_0x95		0x95
	#define _Logo_0x96		0x96
	#define _Logo_0x96_End        (_Logo_0x96 + 1)

  #if		1
	#define _Logo1_0x00		(_Logo_0x96_End + 0x00)
	#define _Logo1_0x01		(_Logo1_0x00 + 0x01)
	#define _Logo1_0x02		(_Logo1_0x00 + 0x02)
	#define _Logo1_0x03		(_Logo1_0x00 + 0x03)
	#define _Logo1_0x04		(_Logo1_0x00 + 0x04)
	#define _Logo1_0x05		(_Logo1_0x00 + 0x05)
	#define _Logo1_0x06		(_Logo1_0x00 + 0x06)
	#define _Logo1_0x07		(_Logo1_0x00 + 0x07)
	#define _Logo1_0x08		(_Logo1_0x00 + 0x08)
	#define _Logo1_0x09		(_Logo1_0x00 + 0x09)
	#define _Logo1_0x0a		(_Logo1_0x00 + 0x0A)
	#define _Logo1_0x0b		(_Logo1_0x00 + 0x0B)
	#define _Logo1_0x0c		(_Logo1_0x00 + 0x0C)
	#define _Logo1_0x0d		(_Logo1_0x00 + 0x0D)
	#define _Logo1_0x0e		(_Logo1_0x00 + 0x0E)
	#define _Logo1_0x0f		(_Logo1_0x00 + 0x0F)
	#define _Logo1_0x10		(_Logo1_0x00 + 0x10)
	#define _Logo1_0x11		(_Logo1_0x00 + 0x11)
	#define _Logo1_0x12		(_Logo1_0x00 + 0x12)
	#define _Logo1_0x13		(_Logo1_0x00 + 0x13)
	#define _Logo1_0x14		(_Logo1_0x00 + 0x14)
	#define _Logo1_0x15		(_Logo1_0x00 + 0x15)
	#define _Logo1_0x16		(_Logo1_0x00 + 0x16)
	#define _Logo1_0x17		(_Logo1_0x00 + 0x17)
	#define _Logo1_0x18		(_Logo1_0x00 + 0x18)
	#define _Logo1_0x19		(_Logo1_0x00 + 0x19)
	#define _Logo1_0x1a		(_Logo1_0x00 + 0x1A)
	#define _Logo1_0x1b		(_Logo1_0x00 + 0x1B)
	#define _Logo1_0x1c		(_Logo1_0x00 + 0x1C)
	#define _Logo1_0x1d		(_Logo1_0x00 + 0x1D)
	#define _Logo1_0x1e		(_Logo1_0x00 + 0x1E)
	#define _Logo1_0x1f		(_Logo1_0x00 + 0x1F)
	#define _Logo1_0x20		(_Logo1_0x00 + 0x20)
	#define _Logo1_0x21		(_Logo1_0x00 + 0x21)
	#define _Logo1_0x22		(_Logo1_0x00 + 0x22)
	#define _Logo1_0x23		(_Logo1_0x00 + 0x23)
	#define _Logo1_0x24		(_Logo1_0x00 + 0x24)
	#define _Logo1_0x25		(_Logo1_0x00 + 0x25)
	#define _Logo1_0x26		(_Logo1_0x00 + 0x26)
	#define _Logo1_0x27		(_Logo1_0x00 + 0x27)
	#define _Logo1_0x28		(_Logo1_0x00 + 0x28)
	#define _Logo1_0x29		(_Logo1_0x00 + 0x29)
	#define _Logo1_0x2a		(_Logo1_0x00 + 0x2A)
	#define _Logo1_0x2b		(_Logo1_0x00 + 0x2B)
	#define _Logo1_0x2c		(_Logo1_0x00 + 0x2C)
	#define _Logo1_0x2d		(_Logo1_0x00 + 0x2D)
	#define _Logo1_0x2e		(_Logo1_0x00 + 0x2E)
	#define _Logo1_0x2f		(_Logo1_0x00 + 0x2F)
	#define _Logo1_0x30		(_Logo1_0x00 + 0x30)
	#define _Logo1_0x31		(_Logo1_0x00 + 0x31)
	#define _Logo1_0x32		(_Logo1_0x00 + 0x32)
	#define _Logo1_0x33		(_Logo1_0x00 + 0x33)
	#define _Logo1_0x34		(_Logo1_0x00 + 0x34)
	#define _Logo1_0x35		(_Logo1_0x00 + 0x35)
	#define _Logo1_0x36		(_Logo1_0x00 + 0x36)
	#define _Logo1_0x37		(_Logo1_0x00 + 0x37)
	#define _Logo1_0x38		(_Logo1_0x00 + 0x38)
	#define _Logo1_0x39		(_Logo1_0x00 + 0x39)
	#define _Logo1_0x3a		(_Logo1_0x00 + 0x3A)
	#define _Logo1_0x3b		(_Logo1_0x00 + 0x3B)
	#define _Logo1_0x3c		(_Logo1_0x00 + 0x3C)
	#define _Logo1_0x3d		(_Logo1_0x00 + 0x3D)
  #endif

#define _Logo2_0x00                                 0x00	// (_Logo2_0x62_End + 0x00)
#define _Logo2_0x01                                 (_Logo2_0x00 + 0x01)
#define _Logo2_0x02                                 (_Logo2_0x00 + 0x02)
#define _Logo2_0x03                                 (_Logo2_0x00 + 0x03)
#define _Logo2_0x04                                 (_Logo2_0x00 + 0x04)
#define _Logo2_0x05                                 (_Logo2_0x00 + 0x05)
#define _Logo2_0x06                                 (_Logo2_0x00 + 0x06)
#define _Logo2_0x07                                 (_Logo2_0x00 + 0x07)
#define _Logo2_0x08                                 (_Logo2_0x00 + 0x08)
#define _Logo2_0x09                                 (_Logo2_0x00 + 0x09)
#define _Logo2_0x0a                                 (_Logo2_0x00 + 0x0a)
#define _Logo2_0x0b                                 (_Logo2_0x00 + 0x0b)
#define _Logo2_0x0c                                 (_Logo2_0x00 + 0x0c)
#define _Logo2_0x0d                                 (_Logo2_0x00 + 0x0d)
#define _Logo2_0x0e                                 (_Logo2_0x00 + 0x0e)
#define _Logo2_0x0f                                 (_Logo2_0x00 + 0x0f)
#define _Logo2_0x10                                 (_Logo2_0x00 + 0x10)
#define _Logo2_0x11                                 (_Logo2_0x00 + 0x11)
#define _Logo2_0x12                                 (_Logo2_0x00 + 0x12)
#define _Logo2_0x13                                 (_Logo2_0x00 + 0x13)
#define _Logo2_0x14                                 (_Logo2_0x00 + 0x14)
#define _Logo2_0x15                                 (_Logo2_0x00 + 0x15)
#define _Logo2_0x16                                 (_Logo2_0x00 + 0x16)
#define _Logo2_0x17                                 (_Logo2_0x00 + 0x17)
#define _Logo2_0x18                                 (_Logo2_0x00 + 0x18)
#define _Logo2_0x19                                 (_Logo2_0x00 + 0x19)
#define _Logo2_0x1a                                 (_Logo2_0x00 + 0x1a)
#define _Logo2_0x1b                                 (_Logo2_0x00 + 0x1b)
#define _Logo2_0x1c                                 (_Logo2_0x00 + 0x1c)
#define _Logo2_0x1d                                 (_Logo2_0x00 + 0x1d)
#define _Logo2_0x1e                                 (_Logo2_0x00 + 0x1e)
#define _Logo2_0x1f                                 (_Logo2_0x00 + 0x1f)
#define _Logo2_0x20                                 (_Logo2_0x00 + 0x20)
#define _Logo2_0x21                                 (_Logo2_0x00 + 0x21)
#define _Logo2_0x22                                 (_Logo2_0x00 + 0x22)
#define _Logo2_0x23                                 (_Logo2_0x00 + 0x23)
#define _Logo2_0x24                                 (_Logo2_0x00 + 0x24)
#define _Logo2_0x25                                 (_Logo2_0x00 + 0x25)
#define _Logo2_0x26                                 (_Logo2_0x00 + 0x26)
#define _Logo2_0x27                                 (_Logo2_0x00 + 0x27)
#define _Logo2_0x28                                 (_Logo2_0x00 + 0x28)
#define _Logo2_0x29                                 (_Logo2_0x00 + 0x29)
#define _Logo2_0x2a                                 (_Logo2_0x00 + 0x2a)
#define _Logo2_0x2b                                 (_Logo2_0x00 + 0x2b)
#define _Logo2_0x2c                                 (_Logo2_0x00 + 0x2c)
#define _Logo2_0x2d                                 (_Logo2_0x00 + 0x2d)
#define _Logo2_0x2e                                 (_Logo2_0x00 + 0x2e)
#define _Logo2_0x2f                                 (_Logo2_0x00 + 0x2f)
#define _Logo2_0x30                                 (_Logo2_0x00 + 0x30)
#define _Logo2_0x31                                 (_Logo2_0x00 + 0x31)
#define _Logo2_0x32                                 (_Logo2_0x00 + 0x32)
#define _Logo2_0x33                                 (_Logo2_0x00 + 0x33)
#define _Logo2_0x34                                 (_Logo2_0x00 + 0x34)
#define _Logo2_0x35                                 (_Logo2_0x00 + 0x35)
#define _Logo2_0x36                                 (_Logo2_0x00 + 0x36)
#define _Logo2_0x37                                 (_Logo2_0x00 + 0x37)
#define _Logo2_0x38                                 (_Logo2_0x00 + 0x38)
#define _Logo2_0x39                                 (_Logo2_0x00 + 0x39)
#define _Logo2_0x3a                                 (_Logo2_0x00 + 0x3a)
#define _Logo2_0x3b                                 (_Logo2_0x00 + 0x3b)
#define _Logo2_0x3c                                 (_Logo2_0x00 + 0x3c)
#define _Logo2_0x3d                                 (_Logo2_0x00 + 0x3d)
#define _Logo2_0x3e                                 (_Logo2_0x00 + 0x3e)
#define    _Logo2_0x3e_End        (_Logo2_0x3e + 1)

#define _Logo3_0x00                                 (_Logo2_0x3e_End + 0x00)
#define _Logo3_0x01                                 (_Logo3_0x00 + 0x01)
#define _Logo3_0x02                                 (_Logo3_0x00 + 0x02)
#define _Logo3_0x03                                 (_Logo3_0x00 + 0x03)
#define _Logo3_0x04                                 (_Logo3_0x00 + 0x04)
#define _Logo3_0x05                                 (_Logo3_0x00 + 0x05)
#define _Logo3_0x06                                 (_Logo3_0x00 + 0x06)
#define _Logo3_0x07                                 (_Logo3_0x00 + 0x07)
#define _Logo3_0x08                                 (_Logo3_0x00 + 0x08)
#define _Logo3_0x09                                 (_Logo3_0x00 + 0x09)
#define _Logo3_0x0a                                 (_Logo3_0x00 + 0x0a)
#define _Logo3_0x0b                                 (_Logo3_0x00 + 0x0b)
#define _Logo3_0x0c                                 (_Logo3_0x00 + 0x0c)
#define _Logo3_0x0d                                 (_Logo3_0x00 + 0x0d)
#define _Logo3_0x0e                                 (_Logo3_0x00 + 0x0e)
#define _Logo3_0x0f                                 (_Logo3_0x00 + 0x0f)
#define _Logo3_0x10                                 (_Logo3_0x00 + 0x10)
#define _Logo3_0x11                                 (_Logo3_0x00 + 0x11)
#define _Logo3_0x12                                 (_Logo3_0x00 + 0x12)
#define _Logo3_0x13                                 (_Logo3_0x00 + 0x13)
#define _Logo3_0x14                                 (_Logo3_0x00 + 0x14)
#define _Logo3_0x15                                 (_Logo3_0x00 + 0x15)
#define _Logo3_0x16                                 (_Logo3_0x00 + 0x16)
#define _Logo3_0x17                                 (_Logo3_0x00 + 0x17)
#define _Logo3_0x18                                 (_Logo3_0x00 + 0x18)
#define _Logo3_0x19                                 (_Logo3_0x00 + 0x19)
#define _Logo3_0x1a                                 (_Logo3_0x00 + 0x1a)
#define _Logo3_0x1b                                 (_Logo3_0x00 + 0x1b)
#define _Logo3_0x1c                                 (_Logo3_0x00 + 0x1c)
#define _Logo3_0x1d                                 (_Logo3_0x00 + 0x1d)
#define _Logo3_0x1e                                 (_Logo3_0x00 + 0x1e)
#define _Logo3_0x1f                                 (_Logo3_0x00 + 0x1f)
#define _Logo3_0x20                                 (_Logo3_0x00 + 0x20)
#define _Logo3_0x21                                 (_Logo3_0x00 + 0x21)
#define _Logo3_0x22                                 (_Logo3_0x00 + 0x22)
#define _Logo3_0x23                                 (_Logo3_0x00 + 0x23)
#define _Logo3_0x24                                 (_Logo3_0x00 + 0x24)
#define _Logo3_0x25                                 (_Logo3_0x00 + 0x25)
#define _Logo3_0x26                                 (_Logo3_0x00 + 0x26)
#define _Logo3_0x27                                 (_Logo3_0x00 + 0x27)
#define _Logo3_0x28                                 (_Logo3_0x00 + 0x28)
#define _Logo3_0x29                                 (_Logo3_0x00 + 0x29)
#define _Logo3_0x2a                                 (_Logo3_0x00 + 0x2a)
#define _Logo3_0x2b                                 (_Logo3_0x00 + 0x2b)
#define _Logo3_0x2c                                 (_Logo3_0x00 + 0x2c)
#define _Logo3_0x2d                                 (_Logo3_0x00 + 0x2d)
#define _Logo3_0x2e                                 (_Logo3_0x00 + 0x2e)
#define _Logo3_0x2f                                 (_Logo3_0x00 + 0x2f)
#define _Logo3_0x30                                 (_Logo3_0x00 + 0x30)
#define _Logo3_0x31                                 (_Logo3_0x00 + 0x31)
#define _Logo3_0x32                                 (_Logo3_0x00 + 0x32)
#define _Logo3_0x33                                 (_Logo3_0x00 + 0x33)
#define _Logo3_0x34                                 (_Logo3_0x00 + 0x34)
#define _Logo3_0x35                                 (_Logo3_0x00 + 0x35)
#define _Logo3_0x36                                 (_Logo3_0x00 + 0x36)
#define _Logo3_0x37                                 (_Logo3_0x00 + 0x37)
#define    _Logo3_0x37_End        (_Logo3_0x37 + 1)

#define _Logo4_0x00                                 (_Logo3_0x37_End + 0x00)
#define _Logo4_0x01                                 (_Logo4_0x00 + 0x01)
#define _Logo4_0x02                                 (_Logo4_0x00 + 0x02)
#define _Logo4_0x03                                 (_Logo4_0x00 + 0x03)
#define _Logo4_0x04                                 (_Logo4_0x00 + 0x04)
#define _Logo4_0x05                                 (_Logo4_0x00 + 0x05)
#define _Logo4_0x06                                 (_Logo4_0x00 + 0x06)
#define _Logo4_0x07                                 (_Logo4_0x00 + 0x07)
#define _Logo4_0x08                                 (_Logo4_0x00 + 0x08)
#define _Logo4_0x09                                 (_Logo4_0x00 + 0x09)
#define _Logo4_0x0a                                 (_Logo4_0x00 + 0x0a)
#define _Logo4_0x0b                                 (_Logo4_0x00 + 0x0b)
#define _Logo4_0x0c                                 (_Logo4_0x00 + 0x0c)
#define _Logo4_0x0d                                 (_Logo4_0x00 + 0x0d)
#define _Logo4_0x0e                                 (_Logo4_0x00 + 0x0e)
#define _Logo4_0x0f                                 (_Logo4_0x00 + 0x0f)
#define _Logo4_0x10                                 (_Logo4_0x00 + 0x10)
#define _Logo4_0x11                                 (_Logo4_0x00 + 0x11)
#define _Logo4_0x12                                 (_Logo4_0x00 + 0x12)
#define _Logo4_0x13                                 (_Logo4_0x00 + 0x13)
#define _Logo4_0x14                                 (_Logo4_0x00 + 0x14)
#define _Logo4_0x15                                 (_Logo4_0x00 + 0x15)
#define _Logo4_0x16                                 (_Logo4_0x00 + 0x16)
#define _Logo4_0x17                                 (_Logo4_0x00 + 0x17)
#define _Logo4_0x18                                 (_Logo4_0x00 + 0x18)
#define _Logo4_0x19                                 (_Logo4_0x00 + 0x19)
#define _Logo4_0x1a                                 (_Logo4_0x00 + 0x1a)
#define _Logo4_0x1b                                 (_Logo4_0x00 + 0x1b)
#define _Logo4_0x1c                                 (_Logo4_0x00 + 0x1c)
#define _Logo4_0x1d                                 (_Logo4_0x00 + 0x1d)
#define _Logo4_0x1e                                 (_Logo4_0x00 + 0x1e)
#define _Logo4_0x1f                                 (_Logo4_0x00 + 0x1f)
#define _Logo4_0x20                                 (_Logo4_0x00 + 0x20)
#define _Logo4_0x21                                 (_Logo4_0x00 + 0x21)
#define _Logo4_0x22                                 (_Logo4_0x00 + 0x22)
#define _Logo4_0x23                                 (_Logo4_0x00 + 0x23)
#define _Logo4_0x24                                 (_Logo4_0x00 + 0x24)
#define _Logo4_0x25                                 (_Logo4_0x00 + 0x25)
#define _Logo4_0x26                                 (_Logo4_0x00 + 0x26)
#define _Logo4_0x27                                 (_Logo4_0x00 + 0x27)
#define _Logo4_0x28                                 (_Logo4_0x00 + 0x28)
#define _Logo4_0x29                                 (_Logo4_0x00 + 0x29)
#define _Logo4_0x2a                                 (_Logo4_0x00 + 0x2a)
#define _Logo4_0x2b                                 (_Logo4_0x00 + 0x2b)
#define _Logo4_0x2c                                 (_Logo4_0x00 + 0x2c)
#define _Logo4_0x2d                                 (_Logo4_0x00 + 0x2d)
#define _Logo4_0x2e                                 (_Logo4_0x00 + 0x2e)
#define _Logo4_0x2f                                 (_Logo4_0x00 + 0x2f)
#define _Logo4_0x30                                 (_Logo4_0x00 + 0x30)
#define _Logo4_0x31                                 (_Logo4_0x00 + 0x31)
#define _Logo4_0x32                                 (_Logo4_0x00 + 0x32)
#define _Logo4_0x33                                 (_Logo4_0x00 + 0x33)
#define _Logo4_0x34                                 (_Logo4_0x00 + 0x34)
#define _Logo4_0x35                                 (_Logo4_0x00 + 0x35)
#define _Logo4_0x36                                 (_Logo4_0x00 + 0x36)
#define _Logo4_0x37                                 (_Logo4_0x00 + 0x37)
#define _Logo4_0x38                                 (_Logo4_0x00 + 0x38)
#define _Logo4_0x39                                 (_Logo4_0x00 + 0x39)
#define _Logo4_0x3a                                 (_Logo4_0x00 + 0x3a)
#define    _Logo4_0x3a_End        (_Logo4_0x3a + 1)

#define _Logo5_0x00                                 (_Logo4_0x3a_End + 0x00)
#define _Logo5_0x01                                 (_Logo5_0x00 + 0x01)
#define _Logo5_0x02                                 (_Logo5_0x00 + 0x02)
#define _Logo5_0x03                                 (_Logo5_0x00 + 0x03)
#define _Logo5_0x04                                 (_Logo5_0x00 + 0x04)
#define _Logo5_0x05                                 (_Logo5_0x00 + 0x05)
#define _Logo5_0x06                                 (_Logo5_0x00 + 0x06)
#define _Logo5_0x07                                 (_Logo5_0x00 + 0x07)
#define _Logo5_0x08                                 (_Logo5_0x00 + 0x08)
#define _Logo5_0x09                                 (_Logo5_0x00 + 0x09)
#define _Logo5_0x0a                                 (_Logo5_0x00 + 0x0a)
#define _Logo5_0x0b                                 (_Logo5_0x00 + 0x0b)
#define _Logo5_0x0c                                 (_Logo5_0x00 + 0x0c)
#define _Logo5_0x0d                                 (_Logo5_0x00 + 0x0d)
#define _Logo5_0x0e                                 (_Logo5_0x00 + 0x0e)
#define _Logo5_0x0f                                 (_Logo5_0x00 + 0x0f)
#define _Logo5_0x10                                 (_Logo5_0x00 + 0x10)
#define _Logo5_0x11                                 (_Logo5_0x00 + 0x11)
#define _Logo5_0x12                                 (_Logo5_0x00 + 0x12)
#define _Logo5_0x13                                 (_Logo5_0x00 + 0x13)
#define _Logo5_0x14                                 (_Logo5_0x00 + 0x14)
#define _Logo5_0x15                                 (_Logo5_0x00 + 0x15)
#define _Logo5_0x16                                 (_Logo5_0x00 + 0x16)
#define _Logo5_0x17                                 (_Logo5_0x00 + 0x17)
#define _Logo5_0x18                                 (_Logo5_0x00 + 0x18)
#define _Logo5_0x19                                 (_Logo5_0x00 + 0x19)
#define _Logo5_0x1a                                 (_Logo5_0x00 + 0x1a)
#define _Logo5_0x1b                                 (_Logo5_0x00 + 0x1b)
#define _Logo5_0x1c                                 (_Logo5_0x00 + 0x1c)
#define _Logo5_0x1d                                 (_Logo5_0x00 + 0x1d)
#define _Logo5_0x1e                                 (_Logo5_0x00 + 0x1e)
#define _Logo5_0x1f                                 (_Logo5_0x00 + 0x1f)
#define _Logo5_0x20                                 (_Logo5_0x00 + 0x20)
#define _Logo5_0x21                                 (_Logo5_0x00 + 0x21)
#define _Logo5_0x22                                 (_Logo5_0x00 + 0x22)
#define _Logo5_0x23                                 (_Logo5_0x00 + 0x23)
#define _Logo5_0x24                                 (_Logo5_0x00 + 0x24)
#define _Logo5_0x25                                 (_Logo5_0x00 + 0x25)

#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
#define _LOGO_WINDOW_SIZE_X			3240	 // 840
#define _LOGO_WINDOW_SIZE_Y			2160	//145
#define    _Logo_0x00        0x00
#define    _Logo_0x01        0x01
#define    _Logo_0x02        0x02
#define    _Logo_0x03        0x03
#define    _Logo_0x04        0x04
#define    _Logo_0x05        0x05
#define    _Logo_0x06        0x06
#define    _Logo_0x07        0x07
#define    _Logo_0x08        0x08
#define    _Logo_0x09        0x09
#define    _Logo_0x0a        0x0a
#define    _Logo_0x0b        0x0b
#define    _Logo_0x0c        0x0c
#define    _Logo_0x0d        0x0d
#define    _Logo_0x0e        0x0e
#define    _Logo_0x0f        0x0f
#define    _Logo_0x10        0x10
#define    _Logo_0x11        0x11
#define    _Logo_0x12        0x12
#define    _Logo_0x13        0x13
#define    _Logo_0x14        0x14
#define    _Logo_0x15        0x15
#define    _Logo_0x16        0x16
#define    _Logo_0x17        0x17
#define    _Logo_0x18        0x18
#define    _Logo_0x19        0x19
#define    _Logo_0x1a        0x1a
#define    _Logo_0x1b        0x1b
#define    _Logo_0x1c        0x1c
#define    _Logo_0x1d        0x1d
#define    _Logo_0x1e        0x1e
#define    _Logo_0x1f        0x1f
#define    _Logo_0x20        0x20
#define    _Logo_0x21        0x21
#define    _Logo_0x22        0x22
#define    _Logo_0x23        0x23
#define    _Logo_0x24        0x24
#define    _Logo_0x25        0x25
#define    _Logo_0x26        0x26
#define    _Logo_0x27        0x27
#define    _Logo_0x28        0x28
#define    _Logo_0x29        0x29
#define    _Logo_0x2a        0x2a
#define    _Logo_0x2b        0x2b
#define    _Logo_0x2c        0x2c
#define    _Logo_0x2d        0x2d
#define    _Logo_0x2e        0x2e
#define    _Logo_0x2f        0x2f
#define    _Logo_0x30        0x30
#define    _Logo_0x31        0x31
#define    _Logo_0x32        0x32
#define    _Logo_0x32_END        0x33

#define    _Logo1_0x00        (_Logo_0x32_END + 0x00)
#define    _Logo1_0x01        (_Logo1_0x00 + 0x01)
#define    _Logo1_0x02        (_Logo1_0x00 + 0x02)
#define    _Logo1_0x03        (_Logo1_0x00 + 0x03)
#define    _Logo1_0x04        (_Logo1_0x00 + 0x04)
#define    _Logo1_0x05        (_Logo1_0x00 + 0x05)
#define    _Logo1_0x06        (_Logo1_0x00 + 0x06)
#define    _Logo1_0x07        (_Logo1_0x00 + 0x07)
#define    _Logo1_0x08        (_Logo1_0x00 + 0x08)
#define    _Logo1_0x09        (_Logo1_0x00 + 0x09)
#define    _Logo1_0x0a        (_Logo1_0x00 + 0x0a)
#define    _Logo1_0x0b        (_Logo1_0x00 + 0x0b)
#define    _Logo1_0x0c        (_Logo1_0x00 + 0x0c)
#define    _Logo1_0x0d        (_Logo1_0x00 + 0x0d)
#define    _Logo1_0x0e        (_Logo1_0x00 + 0x0e)
#define    _Logo1_0x0f        (_Logo1_0x00 + 0x0f)
#define    _Logo1_0x10        (_Logo1_0x00 + 0x10)
#define    _Logo1_0x11        (_Logo1_0x00 + 0x11)
#define    _Logo1_0x12        (_Logo1_0x00 + 0x12)
#define    _Logo1_0x13        (_Logo1_0x00 + 0x13)
#define    _Logo1_0x14        (_Logo1_0x00 + 0x14)
#define    _Logo1_0x15        (_Logo1_0x00 + 0x15)
#define    _Logo1_0x16        (_Logo1_0x00 + 0x16)
#define    _Logo1_0x17        (_Logo1_0x00 + 0x17)
#define    _Logo1_0x18        (_Logo1_0x00 + 0x18)
#define    _Logo1_0x19        (_Logo1_0x00 + 0x19)
#define    _Logo1_0x1a        (_Logo1_0x00 + 0x1a)
#define    _Logo1_0x1b        (_Logo1_0x00 + 0x1b)
#define    _Logo1_0x1c        (_Logo1_0x00 + 0x1c)
#define    _Logo1_0x1d        (_Logo1_0x00 + 0x1d)
#define    _Logo1_0x1e        (_Logo1_0x00 + 0x1e)
#define    _Logo1_0x1f        (_Logo1_0x00 + 0x1f)
#define    _Logo1_0x20        (_Logo1_0x00 + 0x20)
#define    _Logo1_0x21        (_Logo1_0x00 + 0x21)
#define    _Logo1_0x22        (_Logo1_0x00 + 0x22)
#define    _Logo1_0x23        (_Logo1_0x00 + 0x23)
#define    _Logo1_0x24        (_Logo1_0x00 + 0x24)
#define    _Logo1_0x25        (_Logo1_0x00 + 0x25)
#define    _Logo1_0x26        (_Logo1_0x00 + 0x26)
#define    _Logo1_0x27        (_Logo1_0x00 + 0x27)
#define    _Logo1_0x28        (_Logo1_0x00 + 0x28)
#define    _Logo1_0x29        (_Logo1_0x00 + 0x29)
#define    _Logo1_0x2a        (_Logo1_0x00 + 0x2a)
#define    _Logo1_0x2b        (_Logo1_0x00 + 0x2b)
#define    _Logo1_0x2c        (_Logo1_0x00 + 0x2c)
#define    _Logo1_0x2d        (_Logo1_0x00 + 0x2d)
#define    _Logo1_0x2e        (_Logo1_0x00 + 0x2e)
#define    _Logo1_0x2f        (_Logo1_0x00 + 0x2f)
#define    _Logo1_0x30        (_Logo1_0x00 + 0x30)
#define    _Logo1_0x31        (_Logo1_0x00 + 0x31)
#define    _Logo1_0x32        (_Logo1_0x00 + 0x32)
#define    _Logo1_0x33        (_Logo1_0x00 + 0x33)
#define    _Logo1_0x34        (_Logo1_0x00 + 0x34)
#define    _Logo1_0x35        (_Logo1_0x00 + 0x35)
#define    _Logo1_0x36        (_Logo1_0x00 + 0x36)
#define    _Logo1_0x37        (_Logo1_0x00 + 0x37)
#define    _Logo1_0x38        (_Logo1_0x00 + 0x38)
#define    _Logo1_0x39        (_Logo1_0x00 + 0x39)
#define    _Logo1_0x3a        (_Logo1_0x00 + 0x3a)
#define    _Logo1_0x3b        (_Logo1_0x00 + 0x3b)
#define    _Logo1_0x3c        (_Logo1_0x00 + 0x3c)
#define    _Logo1_0x3d        (_Logo1_0x00 + 0x3d)
#define    _Logo1_0x3e        (_Logo1_0x00 + 0x3e)
#define    _Logo1_0x3f        (_Logo1_0x00 + 0x3f)
#define    _Logo1_0x40        (_Logo1_0x00 + 0x40)
#define    _Logo1_0x41        (_Logo1_0x00 + 0x41)
#define    _Logo1_0x42        (_Logo1_0x00 + 0x42)
#define    _Logo1_0x43        (_Logo1_0x00 + 0x43)
#define    _Logo1_0x44        (_Logo1_0x00 + 0x44)
#define    _Logo1_0x45        (_Logo1_0x00 + 0x45)
#define    _Logo1_0x46        (_Logo1_0x00 + 0x46)
#define    _Logo1_0x47        (_Logo1_0x00 + 0x47)
#define    _Logo1_0x48        (_Logo1_0x00 + 0x48)
#define    _Logo1_0x49        (_Logo1_0x00 + 0x49)
#define    _Logo1_0x4a        (_Logo1_0x00 + 0x4a)
#define    _Logo1_0x4b        (_Logo1_0x00 + 0x4b)
#define    _Logo1_0x4c        (_Logo1_0x00 + 0x4c)
#define    _Logo1_0x4d        (_Logo1_0x00 + 0x4d)
#define    _Logo1_0x4e        (_Logo1_0x00 + 0x4e)
#define    _Logo1_0x4f        (_Logo1_0x00 + 0x4f)
#define    _Logo1_0x50        (_Logo1_0x00 + 0x50)
#define    _Logo1_0x51        (_Logo1_0x00 + 0x51)
#define    _Logo1_0x52        (_Logo1_0x00 + 0x52)
#define    _Logo1_0x53        (_Logo1_0x00 + 0x53)
#define    _Logo1_0x54        (_Logo1_0x00 + 0x54)
#define    _Logo1_0x55        (_Logo1_0x00 + 0x55)
#define    _Logo1_0x56        (_Logo1_0x00 + 0x56)
#define    _Logo1_0x57        (_Logo1_0x00 + 0x57)
#define    _Logo1_0x58        (_Logo1_0x00 + 0x58)
#define    _Logo1_0x59        (_Logo1_0x00 + 0x59)
#define    _Logo1_0x5a        (_Logo1_0x00 + 0x5a)
#define    _Logo1_0x5b        (_Logo1_0x00 + 0x5b)
#define    _Logo1_0x5c        (_Logo1_0x00 + 0x5c)
#define    _Logo1_0x5d        (_Logo1_0x00 + 0x5d)
#define    _Logo1_0x5e        (_Logo1_0x00 + 0x5e)
#define    _Logo1_0x5f        (_Logo1_0x00 + 0x5f)
#define    _Logo1_0x60        (_Logo1_0x00 + 0x60)
#define    _Logo1_0x61        (_Logo1_0x00 + 0x61)
#define    _Logo1_0x62        (_Logo1_0x00 + 0x62)
#define    _Logo1_0x63        (_Logo1_0x00 + 0x63)
#define    _Logo1_0x64        (_Logo1_0x00 + 0x64)
#define    _Logo1_0x65        (_Logo1_0x00 + 0x65)
#define    _Logo1_0x66        (_Logo1_0x00 + 0x66)
#define    _Logo1_0x67        (_Logo1_0x00 + 0x67)
#define    _Logo1_0x68        (_Logo1_0x00 + 0x68)
#define    _Logo1_0x69        (_Logo1_0x00 + 0x69)
#define    _Logo1_0x6a        (_Logo1_0x00 + 0x6a)
#define    _Logo1_0x6b        (_Logo1_0x00 + 0x6b)
#define    _Logo1_0x6c        (_Logo1_0x00 + 0x6c)
#define    _Logo1_0x6d        (_Logo1_0x00 + 0x6d)
#define    _Logo1_0x6e        (_Logo1_0x00 + 0x6e)
#define    _Logo1_0x6f        (_Logo1_0x00 + 0x6f)
#define    _Logo1_0x70        (_Logo1_0x00 + 0x70)
#define    _Logo1_0x71        (_Logo1_0x00 + 0x71)
#define    _Logo1_0x72        (_Logo1_0x00 + 0x72)
#define    _Logo1_0x73        (_Logo1_0x00 + 0x73)
#define    _Logo1_0x74        (_Logo1_0x00 + 0x74)
#define    _Logo1_0x75        (_Logo1_0x00 + 0x75)
#define    _Logo1_0x76        (_Logo1_0x00 + 0x76)
#define    _Logo1_0x77        (_Logo1_0x00 + 0x77)
#define    _Logo1_0x78        (_Logo1_0x00 + 0x78)
#define    _Logo1_0x79        (_Logo1_0x00 + 0x79)
#define    _Logo1_0x7a        (_Logo1_0x00 + 0x7a)
#define    _Logo1_0x7b        (_Logo1_0x00 + 0x7b)
#define    _Logo1_0x7c        (_Logo1_0x00 + 0x7c)
#define    _Logo1_0x7d        (_Logo1_0x00 + 0x7d)
#define    _Logo1_0x7e        (_Logo1_0x00 + 0x7e)
#define    _Logo1_0x7f        (_Logo1_0x00 + 0x7f)
#define    _Logo1_0x80        (_Logo1_0x00 + 0x80)
#define    _Logo1_0x81        (_Logo1_0x00 + 0x81)
#define    _Logo1_0x82        (_Logo1_0x00 + 0x82)
#define    _Logo1_0x83        (_Logo1_0x00 + 0x83)

#else

#define _LOGO_WINDOW_SIZE_X                         839
#define _LOGO_WINDOW_SIZE_Y                         179

#define _Logo_0x00                                  0x00
#define _Logo_0x01                                  (_Logo_0x00 + 0x01)
#define _Logo_0x02                                  (_Logo_0x00 + 0x02)
#define _Logo_0x03                                  (_Logo_0x00 + 0x03)
#define _Logo_0x04                                  (_Logo_0x00 + 0x04)
#define _Logo_0x05                                  (_Logo_0x00 + 0x05)
#define _Logo_0x06                                  (_Logo_0x00 + 0x06)
#define _Logo_0x07                                  (_Logo_0x00 + 0x07)
#define _Logo_0x08                                  (_Logo_0x00 + 0x08)
#define _Logo_0x09                                  (_Logo_0x00 + 0x09)
#define _Logo_0x0a                                  (_Logo_0x00 + 0x0a)
#define _Logo_0x0b                                  (_Logo_0x00 + 0x0b)
#define _Logo_0x0c                                  (_Logo_0x00 + 0x0c)
#define _Logo_0x0d                                  (_Logo_0x00 + 0x0d)
#define _Logo_0x0e                                  (_Logo_0x00 + 0x0e)
#define _Logo_0x0f                                  (_Logo_0x00 + 0x0f)
#define _Logo_0x10                                  (_Logo_0x00 + 0x10)
#define _Logo_0x11                                  (_Logo_0x00 + 0x11)
#define _Logo_0x12                                  (_Logo_0x00 + 0x12)
#define _Logo_0x13                                  (_Logo_0x00 + 0x13)
#define _Logo_0x14                                  (_Logo_0x00 + 0x14)
#define _Logo_0x15                                  (_Logo_0x00 + 0x15)
#define _Logo_0x16                                  (_Logo_0x00 + 0x16)
#define _Logo_0x17                                  (_Logo_0x00 + 0x17)
#define _Logo_0x18                                  (_Logo_0x00 + 0x18)
#define _Logo_0x19                                  (_Logo_0x00 + 0x19)
#define _Logo_0x1a                                  (_Logo_0x00 + 0x1a)
#define _Logo_0x1b                                  (_Logo_0x00 + 0x1b)
#define _Logo_0x1c                                  (_Logo_0x00 + 0x1c)
#define _Logo_0x1d                                  (_Logo_0x00 + 0x1d)
#define _Logo_0x1e                                  (_Logo_0x00 + 0x1e)
#define _Logo_0x1f                                  (_Logo_0x00 + 0x1f)
#define _Logo_0x20                                  (_Logo_0x00 + 0x20)
#define _Logo_0x21                                  (_Logo_0x00 + 0x21)
#define _Logo_0x22                                  (_Logo_0x00 + 0x22)
#define _Logo_0x23                                  (_Logo_0x00 + 0x23)
#define _Logo_0x24                                  (_Logo_0x00 + 0x24)
#define _Logo_0x25                                  (_Logo_0x00 + 0x25)
#define _Logo_0x26                                  (_Logo_0x00 + 0x26)
#define _Logo_0x27                                  (_Logo_0x00 + 0x27)
#define _Logo_0x28                                  (_Logo_0x00 + 0x28)
#define _Logo_0x29                                  (_Logo_0x00 + 0x29)
#define _Logo_0x2a                                  (_Logo_0x00 + 0x2a)
#define _Logo_0x2b                                  (_Logo_0x00 + 0x2b)
#define _Logo_0x2c                                  (_Logo_0x00 + 0x2c)
#define _Logo_0x2d                                  (_Logo_0x00 + 0x2d)
#define _Logo_0x2e                                  (_Logo_0x00 + 0x2e)
#define _Logo_0x2f                                  (_Logo_0x00 + 0x2f)
#define _Logo_0x30                                  (_Logo_0x00 + 0x30)
#define _Logo_0x31                                  (_Logo_0x00 + 0x31)
#define _Logo_0x32                                  (_Logo_0x00 + 0x32)
#define _Logo_0x33                                  (_Logo_0x00 + 0x33)
#define _Logo_0x34                                  (_Logo_0x00 + 0x34)
#define _Logo_0x35                                  (_Logo_0x00 + 0x35)
#define _Logo_0x36                                  (_Logo_0x00 + 0x36)
#define _Logo_0x37                                  (_Logo_0x00 + 0x37)
#define _Logo_0x38                                  (_Logo_0x00 + 0x38)
#define _Logo_0x39                                  (_Logo_0x00 + 0x39)
#define _Logo_0x3a                                  (_Logo_0x00 + 0x3a)
#define _Logo_0x3b                                  (_Logo_0x00 + 0x3b)
#define _Logo_0x3c                                  (_Logo_0x00 + 0x3c)
#define _Logo_0x3d                                  (_Logo_0x00 + 0x3d)
#define _Logo_0x3e                                  (_Logo_0x00 + 0x3e)
#define _Logo_0x3f                                  (_Logo_0x00 + 0x3f)
#define _Logo_0x40                                  (_Logo_0x00 + 0x40)
#define _Logo_0x41                                  (_Logo_0x00 + 0x41)
#define _Logo_0x42                                  (_Logo_0x00 + 0x42)
#define _Logo_0x43                                  (_Logo_0x00 + 0x43)
#define _Logo_0x44                                  (_Logo_0x00 + 0x44)
#define _Logo_0x45                                  (_Logo_0x00 + 0x45)
#define _Logo_0x46                                  (_Logo_0x00 + 0x46)
#define _Logo_0x47                                  (_Logo_0x00 + 0x47)
#define _Logo_0x48                                  (_Logo_0x00 + 0x48)
#define _Logo_0x49                                  (_Logo_0x00 + 0x49)
#define _Logo_0x4a                                  (_Logo_0x00 + 0x4a)
#define _Logo_0x4b                                  (_Logo_0x00 + 0x4b)
#define _Logo_0x4c                                  (_Logo_0x00 + 0x4c)
#define _Logo_0x4d                                  (_Logo_0x00 + 0x4d)
#define _Logo_0x4e                                  (_Logo_0x00 + 0x4e)
#define _Logo_0x4f                                  (_Logo_0x00 + 0x4f)
#define _Logo_0x50_End                              (_Logo_0x00 + 0x50)

#define _Logo1_0x00                                 (_Logo_0x50_End + 0x00)
#define _Logo1_0x01                                 (_Logo1_0x00 + 0x01)
#define _Logo1_0x02                                 (_Logo1_0x00 + 0x02)
#define _Logo1_0x03                                 (_Logo1_0x00 + 0x03)
#define _Logo1_0x04                                 (_Logo1_0x00 + 0x04)
#define _Logo1_0x05                                 (_Logo1_0x00 + 0x05)
#define _Logo1_0x06                                 (_Logo1_0x00 + 0x06)
#define _Logo1_0x07                                 (_Logo1_0x00 + 0x07)
#define _Logo1_0x08                                 (_Logo1_0x00 + 0x08)
#define _Logo1_0x09                                 (_Logo1_0x00 + 0x09)
#define _Logo1_0x0a                                 (_Logo1_0x00 + 0x0a)
#define _Logo1_0x0b                                 (_Logo1_0x00 + 0x0b)
#define _Logo1_0x0c                                 (_Logo1_0x00 + 0x0c)
#define _Logo1_0x0d                                 (_Logo1_0x00 + 0x0d)
#define _Logo1_0x0e                                 (_Logo1_0x00 + 0x0e)
#define _Logo1_0x0f                                 (_Logo1_0x00 + 0x0f)
#define _Logo1_0x10                                 (_Logo1_0x00 + 0x10)
#define _Logo1_0x11                                 (_Logo1_0x00 + 0x11)
#define _Logo1_0x12                                 (_Logo1_0x00 + 0x12)
#define _Logo1_0x13                                 (_Logo1_0x00 + 0x13)
#define _Logo1_0x14                                 (_Logo1_0x00 + 0x14)
#define _Logo1_0x15                                 (_Logo1_0x00 + 0x15)
#define _Logo1_0x16                                 (_Logo1_0x00 + 0x16)
#define _Logo1_0x17                                 (_Logo1_0x00 + 0x17)
#define _Logo1_0x18                                 (_Logo1_0x00 + 0x18)
#define _Logo1_0x19                                 (_Logo1_0x00 + 0x19)
#define _Logo1_0x1a                                 (_Logo1_0x00 + 0x1a)
#define _Logo1_0x1b                                 (_Logo1_0x00 + 0x1b)
#define _Logo1_0x1c                                 (_Logo1_0x00 + 0x1c)
#define _Logo1_0x1d                                 (_Logo1_0x00 + 0x1d)
#define _Logo1_0x1e                                 (_Logo1_0x00 + 0x1e)
#define _Logo1_0x1f                                 (_Logo1_0x00 + 0x1f)
#define _Logo1_0x20                                 (_Logo1_0x00 + 0x20)
#define _Logo1_0x21                                 (_Logo1_0x00 + 0x21)
#define _Logo1_0x22                                 (_Logo1_0x00 + 0x22)
#define _Logo1_0x23                                 (_Logo1_0x00 + 0x23)
#define _Logo1_0x24                                 (_Logo1_0x00 + 0x24)
#define _Logo1_0x25                                 (_Logo1_0x00 + 0x25)
#define _Logo1_0x26                                 (_Logo1_0x00 + 0x26)
#define _Logo1_0x27                                 (_Logo1_0x00 + 0x27)
#define _Logo1_0x28                                 (_Logo1_0x00 + 0x28)
#define _Logo1_0x29                                 (_Logo1_0x00 + 0x29)
#define _Logo1_0x2a                                 (_Logo1_0x00 + 0x2a)
#define _Logo1_0x2b                                 (_Logo1_0x00 + 0x2b)
#define _Logo1_0x2c                                 (_Logo1_0x00 + 0x2c)
#define _Logo1_0x2d                                 (_Logo1_0x00 + 0x2d)
#define _Logo1_0x2e                                 (_Logo1_0x00 + 0x2e)
#define _Logo1_0x2f                                 (_Logo1_0x00 + 0x2f)
#define _Logo1_0x30                                 (_Logo1_0x00 + 0x30)
#define _Logo1_0x31                                 (_Logo1_0x00 + 0x31)
#define _Logo1_0x32                                 (_Logo1_0x00 + 0x32)
#define _Logo1_0x33                                 (_Logo1_0x00 + 0x33)
#define _Logo1_0x34                                 (_Logo1_0x00 + 0x34)
#define _Logo1_0x35                                 (_Logo1_0x00 + 0x35)
#define _Logo1_0x36                                 (_Logo1_0x00 + 0x36)
#define _Logo1_0x37                                 (_Logo1_0x00 + 0x37)
#define _Logo1_0x38                                 (_Logo1_0x00 + 0x38)
#define _Logo1_0x39                                 (_Logo1_0x00 + 0x39)
#define _Logo1_0x3a                                 (_Logo1_0x00 + 0x3a)
#define _Logo1_0x3b                                 (_Logo1_0x00 + 0x3b)
#define _Logo1_0x3c                                 (_Logo1_0x00 + 0x3c)
#define _Logo1_0x3d                                 (_Logo1_0x00 + 0x3d)
#define _Logo1_0x3e                                 (_Logo1_0x00 + 0x3e)
#define _Logo1_0x3f                                 (_Logo1_0x00 + 0x3f)
#define _Logo1_0x40                                 (_Logo1_0x00 + 0x40)
#define _Logo1_0x41                                 (_Logo1_0x00 + 0x41)
#define _Logo1_0x42                                 (_Logo1_0x00 + 0x42)
#define _Logo1_0x43                                 (_Logo1_0x00 + 0x43)
#define _Logo1_0x44                                 (_Logo1_0x00 + 0x44)
#define _Logo1_0x45                                 (_Logo1_0x00 + 0x45)
#define _Logo1_0x46                                 (_Logo1_0x00 + 0x46)

#endif
//=============== 2Bit Icon ========================


//---------------------------------------------------------------------
// Definitions of OSD Show Number Function Used by OsdDisplayShowNumber()
//---------------------------------------------------------------------
#define _ALIGN_LEFT                                 (0)
#define _ALIGN_RIGHT                                (1)

#define _FORCE_SHOW_NUMBER_OFF                      (0 << 1)
#define _FORCE_SHOW_NUMBER_ON                       (1 << 1)

#define _SHOW_1                                     (0 << 4)
#define _SHOW_2                                     (1 << 4)
#define _SHOW_3                                     (2 << 4)
#define _SHOW_4                                     (3 << 4)
#define _SHOW_5                                     (4 << 4)
#define _SHOW_6                                     (5 << 4)

//------------------------------------------------------
// Definitions of OSD Slider Function Used by OsdDisplaySlider()
//------------------------------------------------------
#define _SLIDER_RESOLUTION                          (10)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define _PALETTE_INDEX0                             0   // 0 ~ 15
#define _PALETTE_INDEX1                             1   // 16 ~ 31
#define _PALETTE_INDEX2                             2   // 32 ~ 47
#define _PALETTE_INDEX3                             3   // 48 ~ 63

// OSD Position
#define _POS_DIRECT                                 0
#define _POS_PERCENT                                1

//--------------------------------------------------
// Definations of OSD MAIN MENU
//--------------------------------------------------

#define _OSD_MAIN_MENU_WIDTH 44 + 2 + 5 + 5 // (14+22+8 + 2)	
#define _OSD_MAIN_MENU_HEIGHT 12//19

#define _MENU_SECTION_0_WIDTH 10//14 + 5
#define _MENU_SECTION_1_WIDTH 21
#define _MENU_SECTION_2_WIDTH 8

#define _OSD_DIALOG_BOX_WIDTH 26
#define _OSD_DIALOG_BOX_HEIGHT 8

#define _OSD_INFO_BOX_WIDTH 20
#define _OSD_INFO_BOX_HEIGHT 6

#define _SECTION_SPACE 0
// #define _SECTION_1_SPACE							1
// #define _SECTION_2_SPACE							2

#define _MENU_STRING_INDENT 1

#define _MENU_SECTION_0_WIN_X (0)
#define _MENU_SECTION_1_WIN_X (_MENU_SECTION_0_WIDTH + _SECTION_SPACE)
#define _MENU_SECTION_2_WIN_X (_MENU_SECTION_1_WIN_X + _MENU_SECTION_1_WIDTH + _SECTION_SPACE)

#define _MENU_SECTION_0_STR_X (_MENU_SECTION_0_WIN_X + _MENU_STRING_INDENT)
#define _MENU_SECTION_0_SUB_STR_X (_MENU_SECTION_0_STR_X + _MENU_STRING_INDENT + 8)
#define _MENU_SECTION_0_SUB_STR_WIDTH 8
#define _MENU_SECTION_0_SUB_NUM_X 15

#define _MENU_SECTION_1_STR_X (_MENU_SECTION_1_WIN_X + _MENU_STRING_INDENT)
#define _MENU_SECTION_1_SUB_STR_X (_MENU_SECTION_1_NUM_X + _MENU_STRING_INDENT - _MENU_SECTION_1_SUB_STR_WIDTH)
#define _MENU_SECTION_1_SUB_STR_WIDTH 10
#define _MENU_SECTION_1_SUB_NUM_X (_MENU_SECTION_1_STR_X + _MENU_STRING_INDENT + 15)

#define _MENU_SECTION_2_STR_X (_MENU_SECTION_2_WIN_X + _MENU_STRING_INDENT)

#define _MENU_SECTION_1_NUM_X (_MENU_SECTION_1_STR_X + _MENU_SECTION_1_WIDTH - 3)
#define _MENU_SECTION_1_NUM_X_STR (_MENU_SECTION_1_NUM_X - _MENU_SECTION_1_SUB_STR_WIDTH + _MENU_STRING_INDENT)

#define _MENU_SECTION_1_NUM_X_CLR4 (_MENU_SECTION_1_NUM_X - 4)

#define _MENU_SECTION_INFO_X _MENU_SECTION_1_WIN_X + _MENU_SECTION_0_SUB_STR_X + 2

#define _MENU_SECTION_0 0
#define _MENU_SECTION_1 1
#define _MENU_SECTION_2 2

//-------------------------------------------------------------------------
#define _MENU_SECTION_1_SUB 						3

#define _MENU_SECTION_0_WINDOW _OSD_WINDOW_0	
#define _MENU_SECTION_1_WINDOW _OSD_WINDOW_5
#define _MENU_SECTION_2_WINDOW _OSD_WINDOW_5_1	//_OSD_WINDOW_4_8

#define _MENU_SECTION_0_TITLE_WINDOW _OSD_WINDOW_5_2			
#define _MENU_SECTION_1_TITLE_WINDOW _OSD_WINDOW_5_3
//#define _MENU_SECTION_0_DIALOG_WINDOW _OSD_WINDOW_5_4			
//#define _MENU_SECTION_1_DIALOG_WINDOW _OSD_WINDOW_5_5


#define _MENU_SECTION_0_SELECT_WINDOW _OSD_WINDOW_5_6//1
#define _MENU_SECTION_1_SELECT_WINDOW _OSD_WINDOW_5_7//2
#define _MENU_SECTION_2_SELECT_WINDOW _OSD_WINDOW_5_8//3

#define _MENU_SECTION_TRANSPARENT_WINDOW _OSD_WINDOW_7	//  Not Used
//-------------------------------------------------------------------------


#define _MENU_SECTION_SOURCE 						4		
#define _MENU_SECTION_SOURCE_ITEM					5		
#define _MENU_SECTION_DIALOG						6		
#define _MENU_SECTION_USERASSIGN					7

#define ROW_OFFSET	0				


#define _MENU_SOURCE_WIDTH							13//12	
#if(_ENABLE_MENU_VGA != _ON)	
#define _MENU_SOURCE_HEIGHT							10		
#else
#define _MENU_SOURCE_HEIGHT							11
#endif

#define _MENU_SECTION_SOURCE_ITEM_WIDTH				8	
#define _MENU_SECTION_SOURC_ITEM_WIN_X				(_MENU_SOURCE_WIDTH+_SECTION_SPACE)
#define _MENU_SECTION_SOURC_ITEM_STR_X				(_MENU_SECTION_SOURC_ITEM_WIN_X + _MENU_STRING_INDENT)



//--------------------------------------------------
// Definations of OSD Type
//--------------------------------------------------

#define _OSD_MESSAGE_ROW_START                      3//2	
#define _OSD_MESSAGE_CENTER_COL_START               6//12
#define _OSD_MESSAGE_CENTER_COL_END                 23

//--------------------------------------------------
// Definations of HL window Border Size
//--------------------------------------------------
#define _HL_WIN_BORDER_SIZE                         2

//--------------------------------------------------
// Definations of Slider
//--------------------------------------------------
#define _SLIDER_LENGHT                              250
#define _SLIDER_HIGH                                20
#define _SLIDER_BORDER_PIXEL                        2
#define _SLIDER_OFFSET                              6

#define _SLIDER_SELECT_BORDER_COLOR                 _CP_GRAY
#define _SLIDER_SELECT_BG_COLOR                     _CP_WHITE

#define _SLIDER_UNSELECT_BORDER_COLOR               _CP_WHITE
#define _SLIDER_UNSELECT_BG_COLOR                   _CP_GRAY

#define _SLIDER_SELECT_COLOR                        _CP_BLACK
#define _SLIDER_UNSELECT_COLOR                      _CP_GRAY

#define _SLIDER_0                                   0
#define _SLIDER_1                                   1
#define _SLIDER_2                                   2

#define _SELECT                                     1
#define _UNSELECT                                   0

#define _SLIDER_0_BAR_WINDOW                        _OSD_WINDOW_4_8 // _OSD_WINDOW_4_5
#define _SLIDER_0_BG_WINDOW                         _OSD_WINDOW_4_7 // _OSD_WINDOW_4_4
#define _SLIDER_0_BORDER_WINDOW                     _OSD_WINDOW_4_6 // _OSD_WINDOW_4_3

#define _SLIDER_1_BAR_WINDOW                        _OSD_WINDOW_4_8
#define _SLIDER_1_BG_WINDOW                         _OSD_WINDOW_4_7
#define _SLIDER_1_BORDER_WINDOW                     _OSD_WINDOW_4_6

#define _SLIDER_0_ROW                               16
#define _SLIDER_0_COL                               11

#define _ITEM_0                                     0
#define _ITEM_1                                     1
#define _ITEM_2                                     2
#define _ITEM_3                                     3
#define _ITEM_4                                     4
#define _ITEM_5                                     5
#define _ITEM_6                                     6
#define _ITEM_7                                     7
#define _ITEM_8                                     8
#define _ITEM_9                                     9
#define _ITEM_10                                    10
#define _ITEM_11                                    11
#define _ITEM_12                                    12
#define _ITEM_13                                    13
#define _ITEM_14                                    14
#define _ITEM_15                                    15


#define _NONE_ITEM                                  16

#define _FONTFROM_0_255                             0x00
#define _FONTFROM_256_512                           _BIT5


//--------------------------------------------------
// Definations of Color effect user mode Hue & Saturation
//--------------------------------------------------
#define _COLOR_HUE                                  0
#define _COLOR_SATURATION                           1

//--------------------------------------------------
// Define enter panel uniformity msg adjust from pcm or gamma
//--------------------------------------------------
typedef enum
{
    _FROM_STATE_PCM,
    _FROM_STATE_GAMMA,
    _FROM_STATE_HDR,
    _FROM_STATE_LD,
    _FROM_STATE_SDRTOHDR,
} EnumFromWhichState;


//--------------------------------------------------
// Define PCM Soft Proft
//--------------------------------------------------
typedef enum
{
    _PCM_SOFT_MODE_1,
    _PCM_SOFT_MODE_2,
    _PCM_SOFT_MODE_AMOUNT = _PCM_SOFT_MODE_2,
} EnumPCMSoftProftMode;


//--------------------------------------------------
// Define Gamma
//--------------------------------------------------
#if ((_CUSTOMER_TYPE == _CUSTOMER_MEDICAL) || (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT))
typedef enum
{
    _GAMMA_OFF,
    _GAMMA_22,
    _GAMMA_DICOM,
    _GAMMA_AMOUNT = _GAMMA_DICOM,
} EnumGammaType;
#else
typedef enum
{
    _GAMMA_OFF,
    _GAMMA_20,
    _GAMMA_22,
    _GAMMA_24,
    _GAMMA_DICOM,
    _GAMMA_AMOUNT = _GAMMA_DICOM,
} EnumGammaType;
#endif


//--------------------------------------------------
// Define HL Window Type
//--------------------------------------------------
typedef enum
{
    _HL_WIN_OFF,
    _HL_WIN_1,
    _HL_WIN_2,
    _HL_WIN_3,
    _HL_WIN_4,
    _HL_WIN_5,
    _HL_WIN_AMOUNT = _HL_WIN_5,
}EnumHLWinType;

//--------------------------------------------------
// Definitions of Display Mode	//  RTD2795 Not Used
//--------------------------------------------------
typedef enum
{
    _OSD_DM_1P,
    _OSD_DM_2P_LR,
    _OSD_DM_2P_TB,
    _OSD_DM_2P_PIP,
    _OSD_DM_3P,	
    _OSD_DM_4P,
    _OSD_DM_AMOUNT,
}EnumOSDDisplayModeDef;	

//--------------------------------------------------
// Definitions of Select Region	
//--------------------------------------------------
typedef enum
{
    _OSD_SR_1P_FULL,
}EnumOSDSelectRegion1PDef;

typedef enum
{
    _OSD_SR_2P_LR_L,
    _OSD_SR_2P_LR_R,
    _OSD_SR_2P_LR_FULL,
}EnumOSDSelectRegion2PLRDef;

typedef enum
{
    _OSD_SR_2P_TB_T,
    _OSD_SR_2P_TB_B,
    _OSD_SR_2P_TB_FULL,
}EnumOSDSelectRegion2PTBDef;

typedef enum
{
    _OSD_SR_3P_1P,
    _OSD_SR_3P_2P,
    _OSD_SR_3P_3P,
    _OSD_SR_3P_FULL,
}EnumOSDSelectRegion3PDef;	

typedef enum
{
    _OSD_SR_2P_PIP_MAIN,
    _OSD_SR_2P_PIP_SUB,
    _OSD_SR_2P_PIP_FULL,
}EnumOSDSelectRegion2PPIPDef;

typedef enum
{
    _OSD_SR_4P_LT_INSIDE,
    //_OSD_SR_4P_LT_OUTSIDE,	
    _OSD_SR_4P_LB_INSIDE,
    //_OSD_SR_4P_LB_OUTSIDE,
    _OSD_SR_4P_RT_INSIDE,
    //_OSD_SR_4P_RT_OUTSIDE,
    _OSD_SR_4P_RB_INSIDE,
    //_OSD_SR_4P_RB_OUTSIDE,
    _OSD_SR_4P_FULL,
}EnumOSDSelectRegion4PDef;	

typedef enum
{
    _COLOREFFECT_STANDARD,
	_COLOREFFECT_MONO,		
    _COLOREFFECT_NIGHT,
    _COLOREFFECT_GAME,
    _COLOREFFECT_MOVIE,
    _COLOREFFECT_PHOTO,
    _COLOREFFECT_VIVID,
    _COLOREFFECT_USER,
    _COLOREFFECT_AMOUNT = _COLOREFFECT_NIGHT,	
}EnumColorEffectType;

//--------------------------------------------------
// Define Color Effect Six Color
//--------------------------------------------------
typedef enum
{
    _SIXCOLOR_R,
    _SIXCOLOR_Y,
    _SIXCOLOR_G,
    _SIXCOLOR_C,
    _SIXCOLOR_B,
    _SIXCOLOR_M,
    _SIXCOLOR_AMOUNT = _SIXCOLOR_M,
}EnumSixColorType;

//--------------------------------------------------
// Define Ultra Vivid
//--------------------------------------------------
typedef enum
{
    _ULTRA_VIVID_OFF,
    _ULTRA_VIVID_L,
    _ULTRA_VIVID_M,
    _ULTRA_VIVID_H,
    _ULTRA_VIVID_AMOUNT = _ULTRA_VIVID_H,
}EnumUltraVividType;


//--------------------------------------------------
// Define Supported Aspect Ratios
//--------------------------------------------------

typedef enum
{
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_16_BY_9,
    _OSD_ASPECT_RATIO_4_BY_3,
    _OSD_ASPECT_RATIO_5_BY_4,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_ORIGIN,
}EnumAspectRatioTypeIndex;

typedef enum
{
    _OSD_OFF,
    _OSD_ON,
}EnumOnOffTypeIndex;	

//--------------------------------------------------
// Define DP Port Version
//--------------------------------------------------
typedef enum
{
    _DP_VER_1_DOT_1 = 0,
    _DP_VER_1_DOT_2,
    _DP_VER_1_DOT_3,
    _DP_VER_AMOUNT = _DP_VER_1_DOT_3,
}EnumOSDDpPortVersionDef;

typedef enum
{
    _MST_OFF = 0,
#if (_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    _MST_AUTO,
#endif
    _MST_D0,
    _MST_D1,
    _MST_D6,
    _MST_AMOUNT = _MST_D6,
}EnumOSDDpMstTypeDef;

//--------------------------------------------------
// Define Display Image Rotate
//--------------------------------------------------
typedef enum
{
    _DISP_ROTATE_0 = 0,
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
    _DISP_ROTATE_90,
#endif
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
    _DISP_ROTATE_180,
#endif
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
    _DISP_ROTATE_270,
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_HOR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_VER_MIRROR,
#endif

    _DISP_ROTATE_AMOUNT,

}EnumOSDDispRotateDegree;

//--------------------------------------------------
// Define Display Latency
//--------------------------------------------------
typedef enum
{
    _LATENCY_L = 0,
    _LATENCY_M,
    _LATENCY_H,
    _LATENCY_AMOUNT = _LATENCY_H,
}EnumOSDDLatency;

//--------------------------------------------------
// Define HotKey Option
//--------------------------------------------------
typedef enum
{
    _HOTKEY_DDCCI = 0,
    _HOTKEY_DP_D0_OPTION,
    _HOTKEY_DP_D1_OPTION,
    _HOTKEY_DP_D2_OPTION,
    _HOTKEY_DP_D6_OPTION,
    _HOTKEY_AMOUNT = _HOTKEY_DP_D6_OPTION,
}EnumOSDHotKeyDef;


//--------------------------------------------------
// Definitions of Input Port
//--------------------------------------------------
typedef enum
{
    _OSD_INPUT_AUTO = 0,
    _OSD_INPUT_A0,	// VGA
    _OSD_INPUT_D0,	// DP2
    _OSD_INPUT_D1,	// DP1
    _OSD_INPUT_D2,	// HDMI2
    _OSD_INPUT_D3,	// HDMI1
    _OSD_INPUT_D4,
    _OSD_INPUT_D5,
    _OSD_INPUT_D6,
    _OSD_INPUT_AMOUNT = _OSD_INPUT_D6,
}EnumOSDInputPortDef;


//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
///*
typedef enum
{
    _CT_9300,
    _CT_7500,
    _CT_6500,
    _CT_5800,
    _CT_SRGB,
    //_CT_USER,
   // _CT_COLORTEMP_AMOUNT = _CT_USER,
}EnumColortemptureDef_old;
//*/	
typedef enum
{
    _CT_D56,
    _CT_D65,
    _CT_D93,
    _CT_USER,
    _CT_COLORTEMP_AMOUNT = _CT_USER,
} EnumColortemptureDef;	

typedef enum
{
    _BT709,
    _DCI_P3,
    _BT2020,
    _NATIVE,
    _COLOR_AMOUNT = _NATIVE,
} EnumColorDef;	
//--------------------------------------------------
// Definitions of 3D Effect
//--------------------------------------------------
typedef enum
{
    _3D_EFFECT_OFF = _OFF,
    _3D_EFFECT_WEAK,
    _3D_EFFECT_MEDIUM,
    _3D_EFFECT_STRONG,
    _3D_EFFECT_AMOUNT = _3D_EFFECT_STRONG,
}EnumOSDSelect3DEffectDef;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
#if(_OCC_SUPPORT == _OFF)
    _PCM_OSD_SRGB,
    _PCM_OSD_ADOBE_RGB,
#endif

    _PCM_OSD_BT709,
    _PCM_OSD_DCI_P3,
    _PCM_OSD_BT2020,
    _PCM_OSD_NATIVE,
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
    _PCM_OSD_SOFT_PROFT,
    _PCM_OSD_AMOUNT = _PCM_OSD_SOFT_PROFT,
#else
    _PCM_OSD_AMOUNT = _PCM_OSD_NATIVE,
#endif
}EnumPCMTypeIndex;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_OSD_TYPE1 = 0,  // gamma 1.8
    _UNIFORMITY_OSD_TYPE2,      // gamma 2.0
    _UNIFORMITY_OSD_TYPE3,      // gamma 2.2
    _UNIFORMITY_OSD_TYPE4,      // gamma 2.4
    _UNIFORMITY_OSD_TYPE5,      // srgb
    _UNIFORMITY_OSD_TYPE6,      // adobe rgb
}EnumUniformityTypeSelectIndex;
//--------------------------------------------------
// Definitions of Clone Mode
//--------------------------------------------------
typedef enum
{
    _OSD_CLONE_OFF = 0,
    _OSD_CLONE_ON,
}EnumOSDCloneModeDef;
//--------------------------------------------------
// Define of Level Type
//--------------------------------------------------
typedef enum
{
    _LEVEL_OFF = 0,
    _LEVEL_L,
    _LEVEL_M,
    _LEVEL_H,
    _LEVEL_AMOUNT = _LEVEL_H,
}EnumLevelType;

//--------------------------------------------------
//--------------------------------------------------

typedef struct
{
    BYTE b1OsdLogo : 1;
    BYTE b1OsdWakeUpSwitchDdcciPort : 1;
    BYTE b1OsdWakeUpShowSource : 1;
	BYTE b1OsdWakeUpShowMenu : 1;		// Reactive Power Saving Message flag
    BYTE b1OsdWakeUpShowDisplayMode : 1;
    BYTE b1OsdFactoryModeStatus : 1;
    BYTE b1OsdDoAspectRatio : 1;
    BYTE b3OsdColorFormat : 3;
    BYTE b3OsdsixColor : 3;
    BYTE b1OsdDoubleSizeStatus : 1;
    BYTE b1FreezeStatus : 1;
#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
    BYTE b1FreezeDisableOsdStatus : 1;
#endif
#if(_DP_DEBUG_MSG == _ON)
    BYTE b1OsdWakeUpShowDpINFO : 1;
    BYTE b4OsdWakeUpShowDpINFOPort : 4;
#endif
    BYTE ucOsdStatePrevious;
    WORD usOsdState;
    BYTE ucOsdEventMsg;
    BYTE ucOsdKeyMessage;
    BYTE ucOsdKeyControl;
    BYTE ucOsdsixColorHue;
    BYTE ucOsdsixColorSaturation;
    BYTE ucOsd3DEffectRealValue;

#if(_FREESYNC_SUPPORT == _ON)
    BYTE ucOsdFREESYNCInforOsdAddress;
#endif
    BYTE ucOsdItemIndex;

    BYTE b2StringMode               : 2;
    BYTE ucStringModeLength;
    BYTE ucStringBlankPixel;
#if (_ENABLE_MENU_OLED == _ON)
	BYTE ucCompRunNRestart;
#endif

} StructOsdInfo;

typedef enum
{
    _ = U0020,							
    _UPDOT_ = U0027,                //  '
    _LEFT_BRACE_ = U0028,           //  (
    _RIGHT_BRACE_ = U0029,          //  )
    _COMMA_ = U002C,                //  ,
    _SLINE_ = U002D,                //  -
    _DOT_ = U002E,                  //  .
    _AND_ = U002F,                  //  /


    _0_ = U0030, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_,

    _COLON_ = U003A,                //  :
    _SEPERATE_ = U003B,             //  ;
    _QUERY_ = U003F,                //  ?
    _AT_0_ = U0040_0,               //  @
    _AT_1_ = U0040_1,               //  @

    _A_ = U0041, _B_, _C_, _D_, _E_, _F_, _G_, _H_, _I_, _J_, _K_, _L_,
    _M_,_N_, _O_, _P_, _Q_, _R_, _S_, _T_, _U_, _V_,
    _W_0,_W_1,
    _X_, _Y_, _Z_,

    _a_ = U0061, _b_, _c_, _d_, _e_, _f_, _g_, _h_, _i_, _j_, _k_, _l_,
    _m_,_n_, _o_, _p_, _q_, _r_, _s_, _t_, _u_, _v_,
    _w_0,_w_1,
    _x_, _y_, _z_,
    _DEGREE_ = U00B0,	
    _L = U2026,

}EnumOSDFontDef;

typedef enum
{
    _CP_EMPTY = 0,
    _CP_BG = 0,
    _CP_BLACK = 0,
    _CP_WHITE,
    _CP_BLUE_120,
    _CP_GREEN_119,
    _CP_BLUE,
    _CP_YELLOW,
    _CP_GRAY, 
    _CP_ORANGE,
    _CP_LIGHTBLUE,
    _CP_SELECTBOTTOM,
    _CP_PINK,
    _CP_RED,
    _CP_GREEN_1,
    _CP_ORANGE_DARK,
    _CP_ORANGE_H,
    _CP_DARKGRAY,	
}EnumOSDColorPaletteDef;

/*
typedef enum
{
    _LOGO_CP_BG = 0,
    _LOGO_CP_BLACK = 0,
    _LOGO_CP_WHITE,
    _LOGO_CP_RED,
    _LOGO_CP_GREEN,
    _LOGO_CP_BLUE,
    _LOGO_CP_YELLOW,
    _LOGO_CP_GRAY,
    _LOGO_CP_DARKBLUE,
    _LOGO_CP_LIGHTBLUE,
    _LOGO_CP_SELECTBOTTOM,
    _LOGO_CP_PINK,
    _LOGO_CP_RED_1,
    _LOGO_CP_GREEN_1,
    _LOGO_CP_ORANGE_L,
    _LOGO_CP_ORANGE_H,
    _LOGO_CP_GRAY_1,
	_LOGO_CP_RED_2,
	_LOGO_CP_GRAY_2,
	_LOGO_CP_COLOR1,
	_LOGO_CP_COLOR2,
	_LOGO_CP_COLOR3,
	_LOGO_CP_COLOR4,
} EnumOSDColorPaletteLogo;
*/
typedef enum
{
    _LOGO_CP_BG = 0,
    _LOGO_CP_BLACK = 0,
    _LOGO_CP_WHITE,
    _LOGO_CP_RED,
    _LOGO_CP_GREEN,
    _LOGO_CP_BLUE,
    _LOGO_CP_YELLOW,
    _LOGO_CP_GRAY,
#if (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
	_LOGO_CP_COLOR1,
	_LOGO_CP_COLOR2,
	_LOGO_CP_COLOR3,
	_LOGO_CP_COLOR4,
#else
    _LOGO_CP_BLACK_2,
    _LOGO_CP_LIGHTBLUE,
    _LOGO_CP_SELECTBOTTOM,
    _LOGO_CP_PINK,
#endif
    _LOGO_CP_RED_1,
    _LOGO_CP_GREEN_1,
	_LOGO_CP_RED_2,
	_LOGO_CP_GRAY_2,
    _LOGO_CP_GRAY_1,

}EnumOSDColorPaletteLogo;

typedef enum
{
    _USERASSIGN_NONE,
    _USERASSIGN_MUTE,
    _USERASSIGN_ROTATE,
    _USERASSIGN_SCAN,
    _USERASSIGN_CONTRAST,
    _USERASSIGN_VOLUME,
    _USERASSIGN_BACKLIGHT,
    _USERASSIGN_MONO_COLOR,
    _USERASSIGN_MONO,
    _USERASSIGN_DP1,
    _USERASSIGN_DP2,
    _USERASSIGN_HDMI1,
    _USERASSIGN_HDMI2,
    _USERASSIGN_REDMODE,
    _USERASSIGN_BRIGHTNESS,
    _USERASSIGN_AMOUNT = _USERASSIGN_REDMODE,
} EnumUserAssign;

typedef enum
{
    _MENU_NONE,		
    _MENU_DIALOG_MESSAGE,		
	_MENU_HOTKEY_SOURCE,
	_MENU_HOTKEY_VOLUME,	
	_MENU_HOTKEY_MUTE,

    _MENU_HOTKEY_BACKLIGHT,
    _MENU_HOTKEY_CONTRAST,
    _MENU_HOTKEY_BRIGHTNESS,
	_MENU_HOTKEY_DISPLAY_MODE,
	_MENU_HOTKEY_PIP_SWAP,
	_MENU_HOTKEY_BLK_ONOFF,

	_MENU_INFO,		
	_MENU_INPUT,	
    _MENU_PICTURE,
    _MENU_COLOR,
    _MENU_SCREEN,
    _MENU_AUDIO,
    _MENU_SETUP,
    
    _MENU_SERVICE1,
    _MENU_SERVICE2,
    _MENU_SERVICE3,
    _MENU_SERVICE_USERASSIGN,
    _MENU_SERVICE_OLED,
//-----------------------------------------
	// INPUT
    _MENU_INPUT_SOURCE1,
    _MENU_INPUT_SOURCE1_ADJ,
    _MENU_INPUT_SOURCE2,
    _MENU_INPUT_SOURCE2_ADJ,
    _MENU_INPUT_SOURCE3,
    _MENU_INPUT_SOURCE3_ADJ,
    _MENU_INPUT_SOURCE4,
    _MENU_INPUT_SOURCE4_ADJ,
//--------------------------------------------
    // PICURE
    _MENU_PICTURE_BLACKLEVEL,
    _MENU_PICTURE_BLACKLEVEL_ADJ, 
    _MENU_PICTURE_CONTRAST,
    _MENU_PICTURE_CONTRAST_ADJ,
    _MENU_PICTURE_CHROMA,
    _MENU_PICTURE_CHROMA_ADJ,
    _MENU_PICTURE_SHARPNESS,
    _MENU_PICTURE_SHARPNESS_ADJ,
    _MENU_PICTURE_GAMMA,
    _MENU_PICTURE_GAMMA_ADJ,
    _MENU_PICTURE_RESETTODEFAULT,
#if (_ENABLE_MENU_REGION == _ON)
    _MENU_PICTURE_REGION,
    _MENU_PICTURE_REGION_ADJ,
#endif
    // COLOR
    _MENU_COLOR_TEMPERATURE,
    _MENU_COLOR_TEMPERATURE_ADJ,
    _MENU_COLOR_SURGICAL,
    _MENU_COLOR_SURGICAL_ADJ,
    _MENU_COLOR_BIAS_R,
    _MENU_COLOR_BIAS_R_ADJ,
    _MENU_COLOR_BIAS_G,
    _MENU_COLOR_BIAS_G_ADJ,
    _MENU_COLOR_BIAS_B,
    _MENU_COLOR_BIAS_B_ADJ,
    _MENU_COLOR_GAIN_R,
    _MENU_COLOR_GAIN_R_ADJ,
    _MENU_COLOR_GAIN_G,
    _MENU_COLOR_GAIN_G_ADJ,
    _MENU_COLOR_GAIN_B,
    _MENU_COLOR_GAIN_B_ADJ,

    _MENU_COLOR_EFFECT,
    _MENU_COLOR_EFFECT_ADJ,
    _MENU_COLOR_GAMMA,
    _MENU_COLOR_GAMMA_ADJ,
#if (_ENABLE_MENU_REGION == _ON)
    _MENU_COLOR_REGION,
    _MENU_COLOR_REGION_ADJ,
#endif
    // SCREEN
    _MENU_SCREEN_OVERSCAN,
    _MENU_SCREEN_OVERSCAN_ADJ,
    _MENU_SCREEN_ASPECT,
    _MENU_SCREEN_ASPECT_ADJ,
    _MENU_SCREEN_MONO_COLOR,
    _MENU_SCREEN_MONO_COLOR_ADJ,
    _MENU_SCREEN_ROTATE,
    _MENU_SCREEN_ROTATE_ADJ,

    // AUDIO
	_MENU_AUDIO_INFO,
    _MENU_AUDIO_VOLUME,
    _MENU_AUDIO_VOLUME_ADJ,
    _MENU_AUDIO_MUTE,
    _MENU_AUDIO_MUTE_ADJ,
    _MENU_AUDIO_SOURCE,
    _MENU_AUDIO_SOURCE_ADJ,
    // SETUP
    _MENU_SETUP_POWERSAVE,
    _MENU_SETUP_POWERSAVE_ADJ,
    _MENU_SETUP_KEYLOCK,
    _MENU_SETUP_KEYLOCK_ADJ,
    _MENU_SETUP_BACKLIGHT,
    _MENU_SETUP_BACKLIGHT_ADJ,
    _MENU_SETUP_BACKLIGHT_CONTROL,
    _MENU_SETUP_BACKLIGHT_CONTROL_ADJ,
    _MENU_SETUP_RESET,
    _MENU_SETUP_RESET_ADJ,
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
    _MENU_SETUP_STABILIZER_CONTROL,
    _MENU_SETUP_STABILIZER_CONTROL_ADJ,
#endif
    _MENU_SETUP_SETID,
	// SERVICE1
    _MENU_SERVICE_SCREENTEST,
    _MENU_SERVICE_TEMPERATURE,
    _MENU_SERVICE_WHITEBALANCE,
    _MENU_SERVICE_D0NAME,
    _MENU_SERVICE_D0NAME_ADJ,
    _MENU_SERVICE_D1NAME,
    _MENU_SERVICE_D1NAME_ADJ,
    _MENU_SERVICE_D2NAME,
    _MENU_SERVICE_D2NAME_ADJ,
    _MENU_SERVICE_D3NAME,
    _MENU_SERVICE_D3NAME_ADJ,
    // SERVICE2
    _MENU_SERVICE_BACKLIGHT_MIN,
    _MENU_SERVICE_BACKLIGHT_MIN_ADJ,
    _MENU_SERVICE_BACKLIGHT_MAX,
    _MENU_SERVICE_BACKLIGHT_MAX_ADJ,
    _MENU_SERVICE_BACKLIGHT_INVERT,
    _MENU_SERVICE_BACKLIGHT_INVERT_ADJ,
    _MENU_SERVICE_BACKLIGHT_FREQ,
    _MENU_SERVICE_BACKLIGHT_FREQ_ADJ,
    _MENU_SERVICE_LOGO,
    _MENU_SERVICE_LOGO_ADJ,
    _MENU_SERVICE_LOGO_LIST,
    _MENU_SERVICE_LOGO_LIST_ADJ,
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
    _MENU_SERVICE_STABILUX,
    _MENU_SERVICE_STABILUX_ADJ,
#endif
    // SERVICE3
    _MENU_SERVICE_DP_OPTION,
    _MENU_SERVICE_DP_OPTION_ADJ,
    _MENU_SERVICE_LIGHTSENSOR,
    _MENU_SERVICE_LIGHTSENSOR_ADJ,
    _MENU_SERVICE_FAN_OPTION,
    _MENU_SERVICE_FAN_OPTION_ADJ,
    _MENU_SERVICE_FAN_SPEED,
    _MENU_SERVICE_FAN_SPEED_ADJ,
    _MENU_SERVICE_USER_BACKUP_CONFIG,
    _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ,
    _MENU_SERVICE_RESTORE_FACTORY_DEFAULT,
    _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ,
    //USERASSIGN
    _MENU_SERVICE_USERASSIGN_UP,
    _MENU_SERVICE_USERASSIGN_UP_ADJ,
    _MENU_SERVICE_USERASSIGN_DOWN,
    _MENU_SERVICE_USERASSIGN_DOWN_ADJ,
    _MENU_SERVICE_USERASSIGN_LEFT,
    _MENU_SERVICE_USERASSIGN_LEFT_ADJ,
    _MENU_SERVICE_USERASSIGN_RIGHT,
    _MENU_SERVICE_USERASSIGN_RIGHT_ADJ, 
    // OLED
    _MENU_SERVICE_OLED_OFFRS,
    _MENU_SERVICE_OLED_OFFRS_ADJ,
    _MENU_SERVICE_OLED_JB,
    _MENU_SERVICE_OLED_JB_ADJ,
    _MENU_SERVICE_OLED_SEQUENCE_TIME,
    _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ,

	_MENU_INFO_FW_VERSION,
	_MENU_INFO_SERIAL_NUM,
	//---------------------------------------
	_MENU_INFO_MODEL,		
    _MENU_INFO_INPUT,
    _MENU_INFO_FORAMT,
    _MENU_INFO_RANGE,
    _MENU_INFO_COLOR_TEMP,
    _MENU_HOTKEY_INFORMATION,
#if (_ENABLE_MENU_OLED == _ON)
    _MENU_HOTKEY_OFFRS,
#endif
//----------------------------------------
	_MENU_END,	// END OSD Menu


//=====================================================
//=====================================================

   

    _MENU_HOTKEY_DDCCI,
//    _MENU_HOTKEY_SOURCE,
    _MENU_HOTKEY_DP_OPTION,
    _MENU_PANEL_UNIFORMITY_MSG_ADJUST,

    //_MENU_END,	
};

typedef enum
{
    _ICON_PAGE_CLEAR = 0,
    _ICON_PAGE_MAIN_0,
    _ICON_PAGE_MAIN_1,
    _ICON_PAGE_MAIN_2,

    _ICON_PAGE_PICTURE_0,

    _ICON_PAGE_DISPLAY_0,
    _ICON_PAGE_DISPLAY_1,

    _ICON_PAGE_COLOR_0,
    _ICON_PAGE_COLOR_1,
    _ICON_PAGE_COLOR_2,

    _ICON_PAGE_ADVANCE,

    _ICON_PAGE_INPUT_0,
    _ICON_PAGE_INPUT_1,
    _ICON_PAGE_INPUT_2,

    _ICON_PAGE_AUDIO_0,
    _ICON_PAGE_AUDIO_1,

    _ICON_PAGE_OTHER_0,
    _ICON_PAGE_OTHER_1,

    _ICON_PAGE_INFORMATION_0,

    _ICON_PAGE_FACTORY_0,

    _ICON_PAGE_ON_OFF,
    _ICON_PAGE_ASPECT_RATIO_0,
    _ICON_PAGE_ASPECT_RATIO_1,
    _ICON_PAGE_AUDIO_SOURCE,
    _ICON_PAGE_ULTRA_VIVID,

    _ICON_PAGE_GAMMA_0,
    _ICON_PAGE_GAMMA_1,
    _ICON_PAGE_TEMPRATURE_0,
    _ICON_PAGE_TEMPRATURE_1,

    _ICON_PAGE_COLOR_EFFECT_0,
    _ICON_PAGE_COLOR_EFFECT_1,

    _ICON_PAGE_COLOR_DEMO_0,
    _ICON_PAGE_COLOR_DEMO_1,

    _ICON_PAGE_COLOR_FORMAT,

    _ICON_PAGE_COLOR_PCM_0,
    _ICON_PAGE_COLOR_PCM_1,
    _ICON_PAGE_TEMPERATURE_USER,
    _ICON_PAGE_COLOR_EFFECT_USER_0,
    _ICON_PAGE_COLOR_EFFECT_USER_1,
    _ICON_PAGE_COLOR_RGBYCM_HUE_SAT,

    _ICON_PAGE_PCM_SOFT_PROFT,
    _ICON_PAGE_OSD_ROTATE,
    _ICON_PAGE_OD_ADJUST,

    _ICON_PAGE_DP_OPTION,
    _ICON_PAGE_DP_D0_1_DOT_X,
    _ICON_PAGE_DP_D1_1_DOT_X,
    _ICON_PAGE_DP_D2_1_DOT_X,
    _ICON_PAGE_DP_D6_1_DOT_X,
    _ICON_PAGE_DP_MST,
    _ICON_PAGE_DP_MST_1,
    _ICON_PAGE_DISP_ROTATE_0,
    _ICON_PAGE_DISP_ROTATE_1,
    _ICON_PAGE_RESOLUTION,
    _ICON_PAGE_CLONE_0,
    _ICON_PAGE_FREESYNC,
    _ICON_PAGE_ADAPTIVESYNC,
    _ICON_PAGE_LATENCY,

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _ICON_PAGE_TYPE_C_MODE,
    _ICON_PAGE_TYPE_C_MODE_U3_ONOFF,
#endif

#if(_HDR10_SUPPORT == _ON)
    _ICON_PAGE_HDR_ADJUST,
    _ICON_PAGE_HDR_ADJUST_1,
    _ICON_PAGE_HDR_MODE,
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _ICON_PAGE_LOCAL_DIMMING,
#endif

    _ICON_PAGE_OSD_LANGUAGE,

    _ICON_PAGE_EDID_PORT_0,
    _ICON_PAGE_EDID_PORT_1,

    _ICON_PAGE_HDMI_VERSIONS,
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _ICON_PAGE_MBR,
    _ICON_PAGE_MBR_MODE,
#endif
}EnumIconPageIndex;

typedef enum
{
    _ICON_SUB_SEL_NONE,
    _ICON_SUB_SEL_INPUT,

}EnumIconSun;

typedef enum
{
    _ICON_NONE = 0,		
    // main			//  tFONT1_MAIN_ICON_TABLE_1
    _ICON_PICTURE,
    _ICON_DISPLAY,
    _ICON_COLOR,
    _ICON_ADVANCE,
    _ICON_INPUT,
    _ICON_AUDIO,
    _ICON_OTHER,
    _ICON_INFORMATION,
    _ICON_FACTORY,

    // picture
    _ICON_BACKLIGHT,
    _ICON_BRIGHTNESS,
    _ICON_CONTRAST,
    _ICON_SHARPNESS,

    // display
    _ICON_AUTO_ADJUST,
    _ICON_HPOS,
    _ICON_VPOS,
    _ICON_CLOCK,
    _ICON_PHASE,
    _ICON_DISP_ROTATE,
    _ICON_LANTENCY,
    _ICON_FREEZE,


    // color
    _ICON_PANEL_UNIFORMITY,
    _ICON_GAMMA,
    _ICON_COLOR_TEMPERATURE,
    _ICON_COLOR_EFFECT,
    _ICON_COLOR_DEMO,
    _ICON_COLOR_FORMAT,
    _ICON_PCM,
    _ICON_HUE,
    _ICON_SATURATION,

    // advance
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _ICON_TYPE_C_MODE,
#endif
    _ICON_ASPECT,
    _ICON_OVER_SCAN,
    _ICON_OVER_DRIVE,
    _ICON_DCR,
    _ICON_DDCCI,
    _ICON_ULTRAVIVID,
    _ICON_DP_OPTION,
    _ICON_DP_MST,
    _ICON_RESOLUTION,
    _ICON_CLONE,
    _ICON_FREESYNC,
    _ICON_DP_ADAPTIVESYNC,
#if(_HDR10_SUPPORT == _ON)
    _ICON_HDR,
    _ICON_HDR_MODE,
    _ICON_DARK_ENHANCE,
    _ICON_HDR_SHARPNESS,
    _ICON_COLOR_ENHANCE,
    _ICON_LIGHT_ENHANCE,
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _ICON_LOCAL_DIMMING,
#endif
#if (_PIXEL_SHIFT_SUPPORT == _ON)
    _ICON_PIXEL_SHIFT,
#endif
    _ICON_HDMI_VERSIONS,
#if (_SDR_TO_HDR_SUPPORT == _ON)
    _ICON_SDR_TO_HDR,
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _ICON_MBR,
    _ICON_MBR_MODE,
    _ICON_DUTY,
    _ICON_POSITION,
#endif
    // input
    _ICON_INPUT_AUTO,


    // audio
    _ICON_VOLUME,
    _ICON_MUTE,
    _ICON_STAND_ALONG,
    _ICON_AUDIO_SOURCE,
    _ICON_SOUND_MODE,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    _ICON_AUDIO_SELF_TEST,
#endif

    // other
    _ICON_RESET,
    _ICON_MENU_TIME,
    _ICON_OSD_HPOS,
    _ICON_OSD_VPOS,
    _ICON_LANGUAGE,
    _ICON_TRNASPARENCY,
    _ICON_ROTATE,

    //option icon		//  tFONT1_MAIN_ICON_TABLE_2
    _ICON_ON,
    _ICON_OFF,
    _ICON_AUDIO_ANALOG,
    _ICON_AUDIO_DIGITAL,
    _ICON_AS_RATIO_FULL,
    _ICON_AS_RATIO_16_9,
    _ICON_AS_RATIO_4_3,
    _ICON_AS_RATIO_5_4,
    _ICON_AS_RATIO_ORIGINAL,

    _ICON_ULTRA_VIVID_H,
    _ICON_ULTRA_VIVID_M,
    _ICON_ULTRA_VIVID_L,


    _ICON_TEMP_9300,
    _ICON_TEMP_7500,
    _ICON_TEMP_6500,
    _ICON_TEMP_5800,
    _ICON_TEMP_SRGB,
    _ICON_TEMP_USER,

    _ICON_COLOR_EFF_STD,
    _ICON_COLOR_EFF_GAME,
    _ICON_COLOR_EFF_MOVIE,
    _ICON_COLOR_EFF_PHOTO,
    _ICON_COLOR_EFF_VIVID,
    _ICON_COLOR_EFF_USER,

    _ICON_COLOR_DEMO_TYPE1,
    _ICON_COLOR_DEMO_TYPE2,
    _ICON_COLOR_DEMO_TYPE3,
    _ICON_COLOR_DEMO_TYPE4,
    _ICON_COLOR_DEMO_TYPE5,


    _ICON_COLOR_FORMAT_RGB,
    _ICON_COLOR_FORMAT_YUV,

    _ICON_TEMP_USER_R,
    _ICON_TEMP_USER_G,
    _ICON_TEMP_USER_B,

    _ICON_COLOR_PCM_SRGB,
    _ICON_COLOR_PCM_ADOBE_RGB,
    _ICON_COLOR_PCM_USER,
    _ICON_COLOR_PCM_NACTIVE,
    _ICON_COLOR_PCM_SOFT_PROFT,

    _ICON_COLOR_EFF_USER_Y,
    _ICON_COLOR_EFF_USER_C,
    _ICON_COLOR_EFF_USER_M,
    _ICON_COLOR_EFF_USER_HUE,
    _ICON_COLOR_EFF_USER_SAT,

    _ICON_NO_SUPPORT,
    _ICON_NO_SUPPORT_TEXT_0,
    _ICON_NO_SUPPORT_TEXT_1,
    _ICON_NO_CABLE,
    _ICON_NO_CABLE_TEXT_0,
    _ICON_NO_CABLE_TEXT_1,

    _ICON_NO_SIGNAL,
    _ICON_NO_SIGNAL_TEXT_0,
    _ICON_NO_SIGNAL_TEXT_1,

    _ICON_POWER_SAVING,
    _ICON_POWER_SAVING_TEXT_0,
    _ICON_POWER_SAVING_TEXT_1,
    _ICON_POWER_SAVING_TEXT_2,

    _ICON_AUTO_ADJUST_TEXT_0,
    _ICON_AUTO_ADJUST_TEXT_1,
    _ICON_AUTO_ADJUST_TEXT_2,

    _ICON_AUTO_COLOR_TEXT_0,
    _ICON_AUTO_COLOR_TEXT_1,
    _ICON_AUTO_COLOR_TEXT_2,

    _ICON_MODE1,
    _ICON_MODE2,


    _ICON_0_DEGREE,
    _ICON_90_DEGREE,
    _ICON_180_DEGREE,
    _ICON_270_DEGREE,
    _ICON_LR_MIRROR,
    _ICON_UD_MIRROR,

    _ICON_DP_1080P,
    _ICON_DP_2560_1440,
    _ICON_DP_4K2K_30HZ,
    _ICON_DP_4K2K_60HZ,


    _ICON_TRUN_OFF_PANEL_UNI_TEXT0,
    _ICON_TRUN_OFF_PANEL_UNI_TEXT1,

    _ICON_YES,
    _ICON_NO,

    _ICON_ONOFF,
    _ICON_OD_GAIN,


    _ICON_D0,
    _ICON_D1,
    _ICON_D2,
    _ICON_D6,

    _ICON_1_DOT_1,
    _ICON_1_DOT_2,
    _ICON_1_DOT_3,
    _ICON_1_DOT_4,

    _ICON_1_DOT_8,
    _ICON_2_DOT_0,
    _ICON_2_DOT_1,
    _ICON_2_DOT_2,
    _ICON_2_DOT_4,

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _ICON_U3_ON,
    _ICON_U3_OFF,
#endif

#if(_HDR10_SUPPORT == _ON)
    _ICON_HDR10_MODE_FORCE_2084,
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _ICON_LD_SMOOTHADJ,
#endif

    _ICON_FREEZE_DISABLE_TEXT_0,
    _ICON_FREEZE_DISABLE_TEXT_1,
    _ICON_FREEZE_DISABLE_TEXT_2,
#if(_DP_MST_SUPPORT == _ON)
    _ICON_MST_WARNING_MSG_0,
    _ICON_MST_WARNING_MSG_1,
    _ICON_MST_WARNING_MSG_2,
#endif

    _ICON_ENGLISH,
    _ICON_CHINESE_T,
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _ICON_RTK_ADV,
#endif
#if (_ENABLE_MENU_OLED == _ON)
	_ICON_OFFRS,
	_ICON_JBCOMP,
	
	_ICON_DISP_JB_TEXT_1,
	_ICON_DISP_JB_TEXT_2,
	_ICON_DISP_OFFRS_TEXT_1,
	_ICON_DISP_OFFRS_TEXT_2,
	_ICON_DISP_OFFRS_PWR_SUPPLY_TEXT_1,
	_ICON_DISP_OFFRS_PWR_SUPPLY_TEXT_2,
	_ICON_DISP_POWEROFF_OFFRS_TEXT_1,
	_ICON_DISP_POWEROFF_OFFRS_TEXT_2,
	_ICON_DISP_OFFRS_SEQUENCE_TIME_TEXT_1,
	_ICON_DISP_OFFRS_SEQUENCE_TIME_TEXT_2,
#endif

    _OPTION_ICON_END,
}EnumIconIndex;


typedef enum
{
    _ICON_INPUT_VGA = _OPTION_ICON_END ,
    _ICON_INPUT_DVI,
    _ICON_INPUT_HDMI,
    _ICON_INPUT_DP,
    _ICON_INPUT_MHL,
    _ICON_INPUT_NO_PORT,

    _ICON_INPUT_END,

}EnumIconPort;

typedef enum
{
    _ICON_A0_PORT = _ICON_INPUT_END,
    _ICON_D0_PORT,
    _ICON_D1_PORT,
    _ICON_D2_PORT,
    _ICON_D3_PORT,
    _ICON_D4_PORT,
    _ICON_D5_PORT,
    _ICON_D6_PORT,

    _ICON_PORT_END,
}EnumIconPortIndex;




typedef enum
{
    _OPTION_NORMAL,
    _OPTION_OVERSCAN_ONOFF,
    _OPTION_OVERDRIVE_ONOFF,
    _OPTION_DCR_ONOFF,
    _OPTION_LANGUAGE_ADJUST,
    _OPTION_DDCCI_ONOFF,
    _OPTION_ROTATE_ADJUST,
    _OPTION_MUTE_ONOFF,
    _OPTION_STAND_ALONG_ONOFF,
    _OPTION_PANEL_UNIFORMITY_ONOFF,
    _OPTION_AUDIO_SOURCE,

    _OPTION_ASPECT_RATIO_TYPE,
    _OPTION_ULTRA_VIVID_TYPE,
    _OPTION_GAMMA_TYPE,
    _OPTION_TEMPRATURE_TYPE,
    _OPTION_COLOR_EFFECT_TYPE,
    _OPTION_COLOR_DEMO_TYPE,
    _OPTION_COLOR_FORMAT_TYPE,
    _OPTION_COLOR_PCM_TYPE,
    _OPTION_COLOR_PCM_SOFT_PROFT_TYPE,
    _OPTION_TEMPRATURE_USER_ADJUST,
    _OPTION_COLOR_EFFC_USER_ADJUST,
    _OPTION_COLOR_EFFC_USER_RGBYCM,
    _OPTION_COLOR_RGBYCM_HUE_STA,

    _OPTION_INPUT_SOURCE_TYPE,
    _OPTION_DP_PORT_VERSION,
    _OPTION_DP_MST_TYPE,
    _OPTION_DISP_ROTATE_TYPE,
    _OPTION_LATENCY_TYPE,
    _OPTION_DP_EDID_TYPE,

    _OPTION_CLONE_TYPE,
    _OPTION_FREESYNC_ONOFF_TYPE,
    _OPTION_DP_ADAPTIVESYNC_ONOFF_TYPE,

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _OPTION_TYPE_C_MODE_SELECT,
#endif
#if(_HDR10_SUPPORT == _ON)
    _OPTION_HDR_MODE_SELECT,
#endif
    _OPTION_LEVEL_TYPE,
    _OPTION_ON_OFF,
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _OPTION_LOCAL_DIMMING_TYPE,
#endif
    _OPTION_HDMI_VERSIONS_TYPE,
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _OPTION_MBR_MODE,
#endif
}EnumOptionIndex;

/*
typedef enum
{
    _FONT1_GLOBAL,
    _REALTEK_1BIT_LOGO0,
    _REALTEK_1BIT_LOGO1,
}EnumFont;


typedef enum
{
    _PALETTE_RTD_LOGO,
    _PALETTE_MAIN_MENU,
}EnumPalette;
*/
typedef enum
{
	_FONT1_GLOBAL,
	_REALTEK_1BIT_LOGO0,
	_REALTEK_1BIT_LOGO1,
	_REALTEK_1BIT_LOGO2,
	_REALTEK_1BIT_LOGO3,
	_REALTEK_1BIT_LOGO4,
	_REALTEK_1BIT_LOGO5,
#if (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	_REALTEK_1BIT_LOGO_THRUPUT0,
	_REALTEK_1BIT_LOGO_THRUPUT1,
	_REALTEK_1BIT_LOGO_SABB0,
	_REALTEK_1BIT_LOGO_SABB1,
	_REALTEK_1BIT_LOGO_ATG0,
	_REALTEK_1BIT_LOGO_ATG1,
#endif
#if (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)
    _REALTEK_1BIT_LOGO_ALPHACLIN_0,
    _REALTEK_1BIT_LOGO_ALPHACLIN_1,
    _REALTEK_1BIT_LOGO_ARTHREX_0,
    _REALTEK_1BIT_LOGO_RIWOLINK_0,
    _REALTEK_1BIT_LOGO_RIWOLINK_1,
    _REALTEK_1BIT_LOGO_RIWOLINK_2,
#endif
}EnumFontSel;

typedef enum
{
    _PALETTE_RTD_LOGO,
    _PALETTE_MAIN_MENU,
//#if (_FALSE_COLOR_SUPPORT == _ON)
//    _PALETTE_FALSE_COLOR_MENU,
//#endif
} EnumPalette;

typedef enum
{
    _ENGLISH = 0,
    _CHINESE_T,
    _FRENCH,
    _GERMAN,
    _SPANISH,
    _CHINESE_S,
    _JAPAN,

    _LANGUAGE_AMOUNT
}EnumOSDLanguageDef;

typedef enum
{
    _OSDEVENT_NONE_MSG = 0,
    _OSDEVENT_SHOW_NOSIGNAL_MSG,
    _OSDEVENT_SHOW_NOCABLE_MSG,
    _OSDEVENT_SHOW_NOSUPPORT_MSG,
    _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG,
    _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG,
    _OSDEVENT_SHOW_DISPLAY_MODE_MENU_MSG,
    _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG,
    _OSDEVENT_DO_AUTO_CONFIG_MSG,
    _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG,
    _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG,
    _OSDEVENT_SAVE_NVRAM_BRICON_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG,
    _OSDEVENT_DP_VERSIOM_MSG,

}EnumOSDEvenMassage;

typedef enum
{
    _OSD_DISP_NOSIGNAL_MSG,
    _OSD_DISP_NOCABLE_MSG,
    _OSD_DISP_NOSUPPORT_MSG,
    _OSD_DISP_FAIL_SAFE_MODE_MSG,
    _OSD_DISP_AUTO_CONFIG_MSG,
    _OSD_DISP_INPUT_SIGNAL_MSG,
    _OSD_DISP_INPUTSOURCE_CHANGE_MSG,
    _OSD_DISP_AUTO_COLOR_MSG,
    _OSD_DISP_SWITCH_DDCCI_PORT_MSG,
    _OSD_DISP_POWER_SAVING_MSG,
    _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG,
#if(_FREEZE_SUPPORT == _ON)
    _OSD_DISP_DISABLE_FREEZE_MSG,
#endif
#if(_DP_MST_SUPPORT == _ON)
    _OSD_DISP_MST_WARNING_MSG,
#endif
#if (_ENABLE_MENU_OLED == _ON)
	_OSD_DISP_JB_MSG,
	_OSD_DISP_OFF_RS_MSG,
	_OSD_DISP_OFF_RS_PWR_SUPPLY_MSG,
	_OSD_DISP_OFF_RS_30SEC_MSG,
#endif

} EnumOSDDispMsg;

typedef enum
{
    _ICON_POS_UP_0,
    _ICON_POS_UP_1,
    _ICON_POS_UP_2,
    _ICON_POS_UP_3,
    _ICON_POS_DOWN_0,
    _ICON_POS_DOWN_1,
    _ICON_POS_DOWN_2,
    _ICON_POS_DOWN_3,
}EnumOSDMainMenuIcon;

typedef enum
{
    _STRING_PICTURE,
    _STRING_DISPLAY,
    _STRING_COLOR,
    _STRING_ADVANCE,
    _STRING_INPUT,
    _STRING_AUDIO,
    _STRING_OTHER,
    _STRING_INFORMATION,
    _STRING_FACTORY,

    // picture
    _STRING_BACKLIGHT,
    _STRING_BRIGHTNESS,
    _STRING_CONTRAST,
    _STRING_SHARPNESS,

    // display
    _STRING_AUTO_ADJUST,
    _STRING_HPOS,
    _STRING_VPOS,
    _STRING_CLOCK,
    _STRING_PHASE,
    _STRING_DISP_ROTATE,
    _STRING_LATENCY,
    _STRING_FREEZE,

    // color
    _STRING_PANEL_UNIFORMITY,
    _STRING_GAMMA,
    _STRING_COLOR_TEMP,
    _STRING_COLOR_EFFECT,
    _STRING_DEMO,
    _STRING_COLOR_FORMAT,
    _STRING_PCM,
    _STRING_HUE,
    _STRING_SATURATION,

    // advance
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _STRING_TYPE_C_MODE,
#endif
    _STRING_ASPECT_RATIO,
    _STRING_OVER_SCAN,
    _STRING_OVER_DRIVE,
    _STRING_DCR,
    _STRING_DDCCI,
    _STRING_ULTRA_VIVID,

    _STRING_DP_OPTION,
    _STRING_DP_MST,
    _STRING_DP_RESOLUTION,
    _STRING_CLONE,
    _STRING_FREESYNC,
    _STRING_DP_ADAPTIVESYNC,

#if(_HDR10_SUPPORT == _ON)
    _STRING_ULTRA_HDR,
    _STRING_ULTRA_HDR_MODE,
    _STRING_DARK_ENHANCE,
    _STRING_SHARPNESS_ENHANCE,
    _STRING_COLOR_ENHANCE,
    _STRING_LIGHT_ENHANCE,
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _STRING_LOCAL_DIMMING,
#endif
#if (_PIXEL_SHIFT_SUPPORT == _ON)
    _STRING_PIXEL_SHIFT,
#endif
    _STRING_HDMI_VERSION,
#if(_SDR_TO_HDR_SUPPORT == _ON)
    _STRING_SDR_TO_HDR,
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _STRING_MBR,
    _STRING_MBR_MODE,
    _STRING_DUTY,
    _STRING_POSTION,
#endif
    _STRING_AUTO_SELECT,

    // audio
    _STRING_VOLUME,
    _STRING_MUTE,
    _STRING_STAND_ALONG,
    _STRING_AUDIO_SOURCE,
    _STRING_SOUND_MODE,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    _STRING_AUDIO_SELF_TEST,
#endif

    // other
    _STRING_RESET,
    _STRING_MENU_TIME,
    _STRING_OSD_HPOS,
    _STRING_OSD_VPOS,
    _STRING_LANGUAGE,
    _STRING_TRANSPARENCY,
    _STRING_ROTATE,

    // Show OSD Number
    _STRING_SHOW_NUMBER,

    // information
    _STRING_HFREQPCLK,
    _STRING_VFREQUENCY,
    _STRING_VGA_USER_MODE,
    _STRING_VGA_PRESET_MODE,
    _STRING_HDCP_MODE,

    // Adjust message
    _STRING_PLEASE_WAIT,
    _STRING_NO_SIGNAL,
    _STRING_NO_CABLE,
    _STRING_NO_SUPPORT,
    _STRING_AUTO_COLOR,
    _STRING_GO_TO_POWER_SAVING_MODE,
    _STRING_NOW_RESOLUTION,

    _STRING_PASS,
    _STRING_FAIL,
    _STRING_FREESYNC_SUPPORT_V_RANGE,

#if(_DP_DEBUG_MSG == _ON)
    _STRING_DP_INFO,
    _STRING_DP_INFO_2,
#endif

    _STRIN_END,
}EnumStringIndex;

typedef enum
{
    // input
    _STRING_A0_PORT = _STRIN_END,
    _STRING_D0_PORT,
    _STRING_D1_PORT,
    _STRING_D2_PORT,
    _STRING_D3_PORT,
    _STRING_D4_PORT,
    _STRING_D5_PORT,
    _STRING_D6_PORT,
}EnumStringPort;

typedef enum
{
    _A0_PORT = 0,
    _D0_PORT,
    _D1_PORT,
    _D2_PORT,
    _D3_PORT,
    _D4_PORT,
    _D5_PORT,
    _D6_PORT,
}EnumPortInx;

typedef enum
{
    _OSD_ROTATE_DISPLAY_FULL = 0,
    _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL,
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,
}EnumOsdRotationDisplaySizeDef;

typedef enum
{
    _OSD_MBR_USER_DISABLE = _OFF,
    _OSD_MBR_USER_ENABLE,
    _OSD_RTK_ADV_MBR_USER_ENABLE,
}EnumOsdMbrUserSelectStatus;

typedef enum
{
    _AUTO_CONFIG_DO = 0,
    _AUTO_CONFIG_RESULT,
    _AUTO_CONFIG_CLOSE_WIN,		
}EnumautoConfig;

typedef enum
{
	_POWER_SAVE_OFF,
	_POWER_SAVE_5SEC,
	_POWER_SAVE_30SEC,
	_POWER_SAVE_1MIN,
	_POWER_SAVE_2MIN,
	_POWER_SAVE_5MIN,
	_POWER_SAVE_30MIN,
	_POWER_SAVE_60MIN,
	_POWER_SAVE_120MIN,
}EnumPowerSaveTimes;		

typedef enum
{
	_HPD_MODE1=0,
	_HPD_MODE2,
	_HPD_MODE3,
	_HPD_MODE4,
}EnumHpdMode;	

typedef enum
{
	_FAN_MODE_AUTO,
	_FAN_MODE_ON,
	_FAN_MODE_OFF,
}EnumFanMode;			

typedef enum
{
    _KEY_UNLOCK,
    _KEY_LOCK,
} EnumKeyLock;		

typedef enum
{
    _LINEAR,
    _CORVED,
} EnumBacklightControl;	

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
// __RTD_DDCCI__
extern bit g_bForcePowSavStatus;
extern bit g_bScreenMuteSatus; 	

// __RTD_OSD__
extern StructOsdInfo g_stOsdInfo;
extern WORD g_usAdjustValue;
extern WORD g_usBackupValue;
extern BYTE g_ucLogoTimerCounter;
extern bit g_bLogoOn;

extern BYTE g_ucBackupColorTempType;	
extern BYTE g_ucBurnInCnt;	

// __RTD_OSDFUNC__
extern WORD g_usFontSelectStart;
extern WORD g_usFontTableStart;
extern BYTE g_ucOsdWidth;
extern BYTE g_ucOsdHeight;
extern BYTE g_ucOsdWidthB;
extern BYTE g_ucOsdHeightB;
extern BYTE g_ucFontPointer0;
extern BYTE g_ucFontPointer1;
extern BYTE g_ucFontPointer2;
extern BYTE g_ucFontPointer3;	

extern BYTE g_pucModeInfoData[28];		

#if (_ENABLE_MENU_OLED == _ON)
extern bit bEnable_OFF_RS_Message;
#endif

//----------------------------------------------------------------------------------------
// Extern Tables from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];

//----------------------------------------------------------------------------------------
// Extern Tables from OsdTable.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTTABLE__
extern BYTE code tOSD_iREALTEK[];
extern BYTE code tOSD_iKEY_BACK[];
extern BYTE code tOSD_iKEY_LEFT[];
extern BYTE code tOSD_iKEY_RIGHT[];
extern BYTE code tOSD_iKEY_ENTER[];
extern BYTE code tOSD_iKEY_EXIT[];

#if		(_CUSTOMER_TYPE == _CUSTOMER_VIMSE)		// 2017.03.22 SUH-EDIT
  #if		1
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO2[];		// VIMS
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO3[];		// VIMS
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO4[];		// VIMS
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO5[];		// VIMS

    extern BYTE code u8_Table[20][4];
    extern BYTE code u8_Palette[4][3];
    extern BYTE code u8_Table_RGB[20][4];
  #else
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];		// VIMS
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO2[];		// VIMS
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO3[];		// VIMS
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO4[];		// VIMS
  #endif
#elif (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_THRUPUT0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_THRUPUT1[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_SABB_0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_SABB_1[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_ATG_0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_ATG_1[];
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];
#elif (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_ALPHACLIN_0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_ALPHACLIN_1[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_ARTHREX_0[];		
 	extern BYTE code tiOSD_REALTEK_1BIT_LOGO_RIWOLINK_0[];	   
    extern BYTE code tiOSD_REALTEK_1BIT_LOGO_RIWOLINK_1[];	  
    extern BYTE code tiOSD_REALTEK_1BIT_LOGO_RIWOLINK_2[];	  
#else
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
	extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];
#endif

#if (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)	
extern BYTE _OGC_FLASH_BANK;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserDdcci.c
//----------------------------------------------------------------------------------------
// __RTD_DDCCI__
extern void UserDdcciHandler(void);
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)
extern void UserInterfaceDdcciGetCpStringData(BYTE *pucDest, EnumInputPortType enumPortType, WORD usStartIndex, WORD usLength);
extern WORD UserInterfaceDdcciGetCpStringSize(EnumInputPortType enumPortType);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from RTDKey.c
//----------------------------------------------------------------------------------------
// __RTD_KEY__
extern void RTDKeyInitial(void);

//----------------------------------------------------------------------------------------
// Extern functions from Osd.c
//----------------------------------------------------------------------------------------
// __RTD_OSD__

extern void MenuSourceSelect(void);	
extern void DirectSourceSelect(void); 
extern void DirectSourceSwitchInputPort(BYTE ucInputPort);

extern void SetMenuDp1D1Version(void);	
extern void SetMenuDp2D0Version(void);

//----------------------------------------------------------------------------------------
// Extern functions from OsdFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFUNC__
extern void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void OsdFuncTransparency(BYTE ucTrans);
extern void OsdFuncBlending(BYTE ucType);

extern void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
extern void OsdFuncDisableOsd(void);
extern void OsdFuncEnableOsd(void);
extern void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth ,BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
extern void OsdFuncSet2BitIconOffset(BYTE ucOffset);
extern void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth ,BYTE ucHeight);
extern void OsdFuncClearOsdAndXOffset(BYTE ucRow, BYTE ucCol, BYTE ucXOffset, BYTE ucWidth, BYTE ucHeight);	

#if(_SIX_COLOR_SUPPORT == _ON)
extern void OsdFuncSixColorAdjust(void);
#endif

extern void OsdFuncColorFormatAdjust(void);
extern void OsdFuncColorPcmAdjust(void);
extern void OsdFuncSetOsdItemFlag(void);

#if(_FREEZE_SUPPORT == _ON)
extern bit OsdFuncCheckFreezeDisable(void);
extern void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern BYTE OsdFuncGetHdmiPortVersion(EnumSourceSearchPort enumSearchPort);
extern void OsdFuncSetHdmiPortVersion(EnumSourceSearchPort enumSearchPort,BYTE ucValue);
#endif
extern void LCDtest_ShowBurninPicture(BYTE ucScreen);

//----------------------------------------------------------------------------------------
// Extern functions from OsdDisplay.c
//----------------------------------------------------------------------------------------
// __RTD_OSDDISPLAY__
extern BYTE OsdDispJudgeSourceType(void);

extern void OsdDispDisableOsd(void);
extern void OsdDispSetPosition(BYTE ucType,EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);

extern void OsdDispHotKeyProcess(BYTE ucKeyMessage);	
//extern void OsdFactoryEnterKeyProcess(BYTE ucKeyMessage);	

extern void OsdDispClearSelectColor(BYTE ucUpDown);


extern void OsdDispMainMenu(void);
extern void OsdMainMenuPageDraw(void);	
extern void OsdMainMenuItemDraw(void);	

extern void OsdSubMenuPageDraw(BYTE ucMainItem);	
extern void OsdSection3ItemPageDraw(BYTE ucMainItem);	

extern void OsdSubMenuItemText(BYTE ucMainItem, BYTE ucSubItem, BYTE ucColor);	

extern void OsdDispNumberAndText(WORD usOsdState, WORD usValue, BYTE ucColor);	

extern void SetFocus(BYTE ucSection, BYTE ucRow);	
extern void ClearFocus(BYTE ucSection);


extern WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
extern WORD OsdDisplayDetOverRange_Long(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
extern WORD OsdDisplayDetOverRange_Curved(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
extern WORD OsdDisplayDetOverRange_Freq(WORD usValue, WORD usMax, WORD usMin, bit bCycle);

#if (_ENABLE_MENU_OLED == _ON)
extern void OsdDispHotKeyOffRSMenu(void);

#endif

extern void OsdDispOsdReset(void);
extern void OsdDispOsdFactoryReset(void);	
extern void OsdUserBackupConfig(void);
extern void OsdUserRestoreConfig(void);
extern void OsdDispClearSliderAndNumber(void);


extern void OsdDispHotKeySourceMenu(void);

extern void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);
extern void OsdDispHotKeyOsdMessage(BYTE ucHotKeyItem);			
extern void OsdDispReactiveOsdMessage(void);	
extern void OsdDispHotKeyMuteMessage(void);

#if(_VGA_SUPPORT == _ON)
extern void OsdDispAutoConfigProc(void);
extern void OsdDisplayAutoBalanceProc(void);
#endif

#if (_CUSTOMER_TYPE == _CUSTOMER_VIMSE) // 2017.03.22 SUH-EDIT
extern void OsdDispShowMainLogo(void);
#endif

extern void OsdDispShowLogo(void);

#if (_CUSTOMER_TYPE == _CUSTOMER_VIMSE) // 2017.03.22 SUH-EDIT
extern void OsdDispShowLogoColor(void);
#endif
#if(_DP_SUPPORT == _ON)
extern void OsdDispResetDpCapabilitySwitch(void);
#endif

extern void OsdDispShowInformation(void);
extern void OsdDispTransferId(BYTE AdjValue);	

extern void OsdDisplaySixColorGetOneColor(BYTE ucColor);
extern void OsdDisplaySixColorSetOneColor(BYTE ucColor);

extern void OsdDispOsdRotateSwitch(void);

#if(_ENABLE_REVERSE_SCAN == _ON)	
extern void OsdDispOsdReverseScanSwitch(void);	
#endif
//----------------------------------------------------------------------------------------
// Extern functions from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern void OsdFontVLCLoadFont(BYTE ucState);

// __RTD_OSDFONTDYNAMICICON_1__
extern void OsdFontVLCDynamicLoadIcon(BYTE ucIconPos, WORD usIcon);

// __RTD_OSDFONTDYNAMICICON_2__
extern void OsdFontVLCLoadMainIcon_2(BYTE ucIconPos, WORD usIcon);

// __RTD_OSDFONTTABLE__
extern void OsdFontPut1Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor);
extern void OsdFontPut1BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor);
extern void OsdFontPut1BitTable2(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor, BYTE boffset);
extern void OsdFontPut1BitMainMenuIcon(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
extern void OsdFontPut2Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void OsdFontPut2BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);

// __RTD_OSDFONTPROP__
extern void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropPutpString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE *pucString, BYTE ucColor, BYTE ucLanguage);	 

extern void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor ,BYTE ucLanguage);
extern void OsdPropPutpStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE *pucString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropPutpStringRight(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE *pucString, BYTE ucColor, BYTE ucLanguage);	
extern void OsdPropPutpStringLeft(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE *pucString, BYTE ucColor, BYTE ucLanguage);

extern void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar ,BYTE ucFontPoint, BYTE ucColor);
extern void OsdPropShowNumberRight(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);	
extern void OsdPropShowNumberRightBig(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
extern void OsdPropShowNumberFloat(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
extern void OsdPropShowNumberRightFreq(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);

extern BYTE OsdPutStringPropFontTable(BYTE ucLanguage, WORD ucFontPoint);
extern void OsdPropShowFreeSyncVFreqRange(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor, BYTE ucLanguage);

// __RTD_OSDPALETTE__
extern void OsdPaletteSelectPalette(BYTE ucValue);

// __RTD_OSDWINDOW__
extern void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);

extern void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdWindowDrawingByFontOrg(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);

extern void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);

extern void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
extern void OsdWindowSliderDisable(void);

//----------------------------------------------------------------------------------------
// Extern functions from OsdTableFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDTABLEFUNC__
extern void OsdTableFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint);
extern BYTE OsdTableFuncVideoResolution(void);
extern void OsdTableFuncPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, BYTE ucLanguage);
extern void OsdTableFuncPutStringCenter(BYTE ucRow, BYTE ucColStart, BYTE ucColEnd, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, SBYTE chCenterOffset, BYTE ucLanguage);
extern void OsdTableFuncDrawWindow(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdTableFuncPutIcon1BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
extern void OsdTableFuncPutIcon2BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
//----------------------------------------------------------------------------------------
extern BYTE OsdDisplayGetSourcePortString(void);
extern BYTE *OsdDisplayGetHFreqPClkStringP(void);
extern BYTE *OsdDisplayGetVFreqStringP(void);

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
