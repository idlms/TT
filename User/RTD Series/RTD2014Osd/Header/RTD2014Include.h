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
#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + (_A0_INPUT_PORT_TYPE & 0x0F))
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + (_D0_INPUT_PORT_TYPE & 0x0F))
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + (_D1_INPUT_PORT_TYPE & 0x0F))
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + (_D2_INPUT_PORT_TYPE & 0x0F))
//#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + (_D3_INPUT_PORT_TYPE & 0x0F))
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + (_D3_DVI_PORT & 0x0F))
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + (_D4_INPUT_PORT_TYPE & 0x0F))
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + (_D5_INPUT_PORT_TYPE & 0x0F))
#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + (_D6_INPUT_PORT_TYPE & 0x0F))


//#if(_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)
//#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_VGA)
//#else
//#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//
//#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
//#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
//#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
//#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
//#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
//#elif(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
//#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
//#else
//#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//
//#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
//#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
//#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
//#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
//#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
//#elif(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
//#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
//#else
//#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//
//#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
//#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
//#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
//#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
//#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
//#elif(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
//#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
//#else
//#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//
//
//#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
//#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
//#elif(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
//#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
//#elif(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
//#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
//#else
//#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//
//#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
//#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
//#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
//#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
//#elif(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
//#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
//#else
//#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//
//
//#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
//#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DVI)
//#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
//#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_HDMI)
//#elif(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
//#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_MHL)
//#else
//#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//
//
//
//#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_DP)
//#else
//#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + _INPUT_NO_PORT)
//#endif
//#if( _ENABLE_VIDEO_WALL == _ON)
//extern BYTE GetVideoWallDisplayNumber(void);
//#endif
//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#define _CONTRAST_MAX                               4910//2848
#define _CONTRAST_MIN                               0//1248
#else
#define _CONTRAST_MAX                               178
#define _CONTRAST_MIN                               78
#endif

#define _CONTRAST_CENTER                            (((_CONTRAST_MAX - _CONTRAST_MIN) / 2) + _CONTRAST_MIN)

//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
//#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
//#define _BACKLIGHT_MAX()                              255
//#else
//#define _BACKLIGHT_MAX()                              4095
//#endif
//#define _BACKLIGHT_MIN                               0 //30
//#define _BACKLIGHT_CENTER                           (((_BACKLIGHT_MAX() - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)
#define _BACKLIGHT_MAX()							4095//(g_stOsdUserData.usBacklightMax)		// 255
#define  SET_BACKLIGHT_MAX(x)						(g_stOsdUserData.usBacklightMax = (x))		// 255
#define _BACKLIGHT_MIN								0		// 30
#define _BACKLIGHT_CENTER							(((_BACKLIGHT_MAX() - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)
//--------------------------------------------------
// Definitions of Brightness Range
//--------------------------------------------------
#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
#define _BRIGHTNESS_MAX                             1020	// 912	// 712
#define _BRIGHTNESS_MIN                             20		// 112	// 312
#else
#define _BRIGHTNESS_MAX                             178
#define _BRIGHTNESS_MIN                             78
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

#if(_ENABLE_VIDEO_WALL == _ON)
//--------------------------------------------------
// Definitions of Video Wall Display Number Range
//--------------------------------------------------
#define _VIDEO_WALL_DISP_NUM_MAX                       25 //255
#define _VIDEO_WALL_DISP_NUM_MIN                       1
#define _VIDEO_WALL_DISP_NUM_CENTER()                  (((GetVideoWallDisplayNumber() - _VIDEO_WALL_DISP_NUM_MIN) / 2) + _VIDEO_WALL_DISP_NUM_MIN)

//--------------------------------------------------
// Definitions of Video Wall H,V Number Range
//--------------------------------------------------
#define _VIDEO_WALL_HV_NUM_MAX                       5//15
#define _VIDEO_WALL_HV_NUM_MIN                       1
#define _VIDEO_WALL_HV_NUM_CENTER                    (((_VIDEO_WALL_HV_NUM_MAX - _VIDEO_WALL_HV_NUM_MIN) / 2) + _VIDEO_WALL_HV_NUM_MIN)

//--------------------------------------------------
// Definitions of Video Wall RS232 ID Range
//--------------------------------------------------
#define _VIDEO_WALL_RS232ID_MAX                       25// 255
#define _VIDEO_WALL_RS232ID_MIN                       1
#define _VIDEO_WALL_RS232ID_CENTER()                    (((GetVideoWallDisplayNumber() - _VIDEO_WALL_RS232ID_MIN) / 2) + _VIDEO_WALL_RS232ID_MIN)
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
//--------------------------------------------------
// Definitions of Fan PWM Range
//--------------------------------------------------
#define _FAN_PWM_MAX                       255
#define _FAN_PWM_MIN                       0
#define _FAN_PWM_CENTER                    (((_FAN_PWM_MAX - _FAN_PWM_MIN) / 2) + _FAN_PWM_MIN)

#define _SHUTDOWN_TEMP_MAX                 85
#define _SHUTDOWN_TEMP_MIN                 60
#define _SHUTDOWN_TEMP_CENTER              (((_SHUTDOWN_TEMP_MAX - _SHUTDOWN_TEMP_MIN) / 2) + _SHUTDOWN_TEMP_MIN)
#endif

//--------------------------------------------------
// Definitions of Colortemp User RGB
//--------------------------------------------------
#define _USER_RGB_MAX                               255
#define _USER_RGB_MIN                               0
#define _USER_RGB_CENTER                            (((_USER_RGB_MAX - _USER_RGB_MIN) / 2) + _USER_RGB_MIN)

//--------------------------------------------------
// Definitions of OD Gain Range
//--------------------------------------------------
#define _OD_GAIN_MAX                                127
#define _OD_GAIN_MIN                                0
#define _OD_GAIN_CENTER                             (((_OD_GAIN_MAX - _OD_GAIN_MIN) / 2) + _OD_GAIN_MIN)

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
#define _OSD_TRANSPARENCY_MAX                       242 // 255
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

//--------------------------------------------------
// Definitions of OSD Volume Range
//--------------------------------------------------
#define _OSD_VOLUME_MAX                             100
#define _OSD_VOLUME_MIN                             0
#define _OSD_VOLUME_CENTER                          (((_OSD_VOLUME_MAX - _OSD_VOLUME_MIN) / 2) + _OSD_VOLUME_MIN)

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
// Definitions of Sharpness Range
//--------------------------------------------------
#define _AUDIO_MODE_MAX                              3
#define _AUDIO_MODE_MIN                              0
#define _AUDIO_MODE_CENTER                           (((_AUDIO_MODE_MAX - _AUDIO_MODE_MIN) / 2) + _AUDIO_MODE_CENTER)
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
#define GET_COMP_RUN_RESTART()						(g_stOsdInfo.ucCompRunNRestart)
#define SET_COMP_RUN_RESTART(x) 					(g_stOsdInfo.ucCompRunNRestart = (x))
#endif
//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
//#define _MENU_KEY_MESSAGE                           0
//#define _RIGHT_KEY_MESSAGE                          1
//#define _LEFT_KEY_MESSAGE                           2
//#define _SELECT_KEY_MESSAGE                           3
//#define _5_KEY_MESSAGE                              4
//#define _6_KEY_MESSAGE                              5
//#define _7_KEY_MESSAGE                              6
//#define _HOLD_KEY_MESSAGE                           7
//#define _NONE_KEY_MESSAGE                           8

//#define _KEY_AMOUNT                                 4
#if (_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
#define _UART_CMD2_AUDIO_VOL_P		'7'
#define _UART_CMD2_AUDIO_VOL_M		'8'
#define _UART_CMD2_HDMI1			'A'
#define _UART_CMD2_HDMI2			'B'
#define _UART_CMD2_DP1				'C'
#define _UART_CMD2_DP2				'D'
//#define _UART_CMD2_SPLIT			'E'
//#define _UART_CMD2_QUAD				'F'
#endif

typedef enum
{
	_MENU_KEY_MESSAGE,
	_RIGHT_KEY_MESSAGE,
	_LEFT_KEY_MESSAGE,
	_SELECT_KEY_MESSAGE,
	_UP_KEY_MESSAGE,
	_DOWN_KEY_MESSAGE,
	//	_SOURCE_KEY_MESSAGE,

	//	IR Message
	_SOURCE_IR_MESSAGE,
	_UP_IR_MESSAGE,
	_DOWN_IR_MESSAGE,
	_RIGHT_IR_MESSAGE,
	_LEFT_IR_MESSAGE,

	_F1_IR_MESSAGE,
	_F2_IR_MESSAGE,
	_F3_IR_MESSAGE,

	_MUTE_IR_MESSAGE,
	_VOL_P_IR_MESSAGE,
	_VOL_M_IR_MESSAGE,
#if		1	// 2017.03.24 - ERIC-ADD
	_SELECT_IR_MESSAGE,
#endif

	_DUMMY_KEY_MESSAGE,

	_HOLD_KEY_MESSAGE,
	_NONE_KEY_MESSAGE,
	_KEY_MESSAGE_AMOUNT,
}EnumKeyMessageType;
#define _KEY_AMOUNT                                 (_HOLD_KEY_MESSAGE - 1)


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

} EnumOsdPutStringMode;

//--------------------------------------------------
// MACRO for OSD Logo Status
//--------------------------------------------------
#define GET_OSD_LOGO_ON()                           (g_stOsdInfo.b1OsdLogo)
#define SET_OSD_LOGO_ON(x)                          (g_stOsdInfo.b1OsdLogo = (x))

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
#define GET_OSD_SIX_COLOR_HUE()                     (g_stOsdInfo.b3OsdsixColorHue)
#define SET_OSD_SIX_COLOR_HUE(x)                    (g_stOsdInfo.b3OsdsixColorHue = (x))

//--------------------------------------------------
// MACRO for Six Color Saturation
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_SATURATION()              (g_stOsdInfo.b3OsdsixColorSaturation)
#define SET_OSD_SIX_COLOR_SATURATION(x)             (g_stOsdInfo.b3OsdsixColorSaturation = (x))

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

//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_BRIGHTNESS()                        (g_stBriConData.usBrightness)
#define SET_OSD_BRIGHTNESS(x)                       (g_stBriConData.usBrightness = (x))

//==========================================================================================================
// Macro of NVRam User Data
//==========================================================================================================
//--------------------------------------------------
// MACRO for Rotation Status
//--------------------------------------------------
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_OSD_DISP_ROTATION_SIZE_TYPE()           (g_stOsdUserData.b2DispRotationSizeType)
#define SET_OSD_DISP_ROTATION_SIZE_TYPE(x)          (g_stOsdUserData.b2DispRotationSizeType = (x))
#endif


//--------------------------------------------------
// MACRO for DP Port Version
//--------------------------------------------------
#define GET_OSD_DP_D0_VERSION()                     (g_stOsdUserData.b2OsdDpD0PortVersion)
#define SET_OSD_DP_D0_VERSION(x)                    (g_stOsdUserData.b2OsdDpD0PortVersion = (x))

#define GET_OSD_DP_D1_VERSION()                     (g_stOsdUserData.b2OsdDpD1PortVersion)
#define SET_OSD_DP_D1_VERSION(x)                    (g_stOsdUserData.b2OsdDpD1PortVersion = (x))

#define GET_OSD_DP_D2_VERSION()                     (g_stOsdUserData.b2OsdDpD2PortVersion)
#define SET_OSD_DP_D2_VERSION(x)                    (g_stOsdUserData.b2OsdDpD2PortVersion = (x))

#define GET_OSD_DP_D6_VERSION()                     (g_stOsdUserData.b2OsdDpD6PortVersion)
#define SET_OSD_DP_D6_VERSION(x)                    (g_stOsdUserData.b2OsdDpD6PortVersion = (x))

#define GET_OSD_DP_MST()                            (g_stOsdUserData.b2OsdDpMST)
#define SET_OSD_DP_MST(x)                           (g_stOsdUserData.b2OsdDpMST = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DISP_ROTATE()                       (g_stOsdUserData.b3OsdDispRotate)
#define SET_OSD_DISP_ROTATE(x)                      (g_stOsdUserData.b3OsdDispRotate = (x))

//--------------------------------------------------
// MACRO for Latency
//--------------------------------------------------
#define GET_OSD_LATENCY()                           (g_stOsdUserData.b2LatencyStatus)
#define SET_OSD_LATENCY(x)                          (g_stOsdUserData.b2LatencyStatus = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DP_VERSION_HOTKEY_DISP()            (g_stOsdUserData.b1OsdDpVersionHotKeyDisp)
#define SET_OSD_DP_VERSION_HOTKEY_DISP(x)           (g_stOsdUserData.b1OsdDpVersionHotKeyDisp = (x))

//--------------------------------------------------
// MACRO for Display
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_OPTION()       (g_stOsdUserData.b1PreShowDpHotKeyVersion)
#define SET_OSD_POWER_SAVING_SHOW_DP_OPTION(x)      (g_stOsdUserData.b1PreShowDpHotKeyVersion = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY()                  (g_stOsdUserData.b1PanelUniformity)
#define SET_OSD_PANEL_UNIFORMITY(x)                 (g_stOsdUserData.b1PanelUniformity = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY_TYPE()             (g_stOsdUserData.b3PanelUniformityType)
#define SET_OSD_PANEL_UNIFORMITY_TYPE(x)            (g_stOsdUserData.b3PanelUniformityType = (x))

//--------------------------------------------------
// MACRO for PCM Soft Proft
//--------------------------------------------------

#define GET_OSD_PCM_SOFT_PROFT_MODE()               (g_stOsdUserData.b1PCMSoftProftMode)
#define SET_OSD_PCM_SOFT_PROFT_MODE(x)              (g_stOsdUserData.b1PCMSoftProftMode = (x))

//--------------------------------------------------
// MACRO for OSD Input Port Value
//--------------------------------------------------
#define GET_OSD_INPUT_PORT_OSD_ITEM()               (g_stOsdUserData.ucOsdInputPort)
#define SET_OSD_INPUT_PORT_OSD_ITEM(x)              (g_stOsdUserData.ucOsdInputPort = (x))


//--------------------------------------------------
// MACRO for OSD Rotate
//--------------------------------------------------
#define GET_OSD_ROTATE_STATUS()                     (g_stOsdUserData.b2OsdRotate)
#define SET_OSD_ROTATE_STATUS(x)                    (g_stOsdUserData.b2OsdRotate = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_3DOSD_STATUS()                      (g_stOsdUserData.b1Osd3DOSD)
#define SET_OSD_3DOSD_STATUS(x)                     (g_stOsdUserData.b1Osd3DOSD = (x))

//--------------------------------------------------
// Macro of BackLight
//--------------------------------------------------
#define GET_OSD_BACKLIGHT()                         (g_stOsdUserData.usBackLight)
#define SET_OSD_BACKLIGHT(x)                        (g_stOsdUserData.usBackLight = (x))

//--------------------------------------------------
// Macro of Aspect Origin Ratio
//--------------------------------------------------
#define GET_OSD_ASPECT_ORIGIN_RATIO()               (g_stOsdUserData.ucAspectOriginRatio)
#define SET_OSD_ASPECT_ORIGIN_RATIO(x)              (g_stOsdUserData.ucAspectOriginRatio = (x))

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE()                       (g_stOsdUserData.b4ColorTempType)
#define SET_COLOR_TEMP_TYPE(x)                      (g_stOsdUserData.b4ColorTempType = (x))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_R()                (g_stColorProcData.usColorTempR >> 4)
#define SET_COLOR_TEMP_TYPE_USER_R(x)               (g_stColorProcData.usColorTempR = ((x) << 4))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_G()                (g_stColorProcData.usColorTempG >> 4)
#define SET_COLOR_TEMP_TYPE_USER_G(x)               (g_stColorProcData.usColorTempG = ((x) << 4))
//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_B()                (g_stColorProcData.usColorTempB >> 4)
#define SET_COLOR_TEMP_TYPE_USER_B(x)               (g_stColorProcData.usColorTempB = ((x) << 4))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_ASPECT_RATIO_TYPE()                 (g_stOsdUserData.b3AspectRatio)
#define SET_OSD_ASPECT_RATIO_TYPE(x)                (g_stOsdUserData.b3AspectRatio = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_VGA_COLOR_FORMAT_STATUS()               (g_stOsdUserData.b3VGARGBYUV)
#define SET_VGA_COLOR_FORMAT_STATUS(x)              (g_stOsdUserData.b3VGARGBYUV = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_DVI_COLOR_FORMAT_STATUS()               (g_stOsdUserData.b3DVIRGBYUV)
#define SET_DVI_COLOR_FORMAT_STATUS(x)              (g_stOsdUserData.b3DVIRGBYUV = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_DDCCI_STATUS()                      (g_stOsdUserData.b1DDCCIStatus)
#define SET_OSD_DDCCI_STATUS(x)                     (g_stOsdUserData.b1DDCCIStatus = (x))

//--------------------------------------------------
// MACRO for Ultra Vivid Status
//--------------------------------------------------
#define GET_OSD_ULTRA_VIVID_STATUS()                (g_stOsdUserData.b2UltraVividStatus)
#define SET_OSD_ULTRA_VIVID_STATUS(x)               (g_stOsdUserData.b2UltraVividStatus = (x))

//--------------------------------------------------
// MACRO for Sharpness
//--------------------------------------------------
#define GET_OSD_SHARPNESS()                         (g_stOsdUserData.b3Sharpness)
#define SET_OSD_SHARPNESS(x)                        (g_stOsdUserData.b3Sharpness = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_TRANSPARENCY_STATUS()               (g_stOsdUserData.ucTransparency)
#define SET_OSD_TRANSPARENCY_STATUS(x)              (g_stOsdUserData.ucTransparency = (x))

//--------------------------------------------------
// MACRO for Language
//--------------------------------------------------
#define GET_OSD_LANGUAGE()                          (g_stOsdUserData.b4Language)
#define SET_OSD_LANGUAGE(x)                         (g_stOsdUserData.b4Language = (x))

//--------------------------------------------------
// MACRO for Language
//--------------------------------------------------
#define GET_OSD_AIM()                          (g_stOsdUserData.aim)
#define SET_OSD_AIM(x)                         (g_stOsdUserData.aim = (x))

// MACRO for Language
//--------------------------------------------------
#define GET_OSD_Timer()                          (g_stOsdUserData.timernumber)
#define SET_OSD_Timer(x)                         (g_stOsdUserData.timernumber = (x))
//--------------------------------------------------
#define GET_OSD_Left_Menu_Choose()                          (g_stOsdUserData.leftMenuChoose)
#define SET_OSD_Left_Menu_Choose(x)                         (g_stOsdUserData.leftMenuChoose = (x))
//--------------------------------------------------
#define GET_OSD_Left_Timer_Position()                          (g_stOsdUserData.leftTimerPosition)
#define SET_OSD_Left_Timer_Position(x)                         (g_stOsdUserData.leftTimerPosition = (x))

//--------------------------------------------------
// MACRO for Power Save
//--------------------------------------------------
#define GET_OSD_POWER_SAVE()                      (g_stOsdUserData.ucPowerSave)
#define SET_OSD_POWER_SAVE(x)                     (g_stOsdUserData.ucPowerSave = (x))

//--------------------------------------------------
// MACRO for OsdTimeout
//--------------------------------------------------
#define GET_OSD_TIME_OUT()                          (g_stOsdUserData.ucOsdTimeout)
#define SET_OSD_TIME_OUT(x)                         (g_stOsdUserData.ucOsdTimeout = (x))

//--------------------------------------------------
// MACRO for OsdHPos
//--------------------------------------------------
#define GET_OSD_HPOS()                              (g_stOsdUserData.ucOsdHPos)
#define SET_OSD_HPOS(x)                             (g_stOsdUserData.ucOsdHPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_VPOS()                              (g_stOsdUserData.ucOsdVPos)
#define SET_OSD_VPOS(x)                             (g_stOsdUserData.ucOsdVPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_GAMMA()                             (g_stOsdUserData.b3Gamma)
#define SET_OSD_GAMMA(x)                            (g_stOsdUserData.b3Gamma = (x))

//--------------------------------------------------
// MACRO for OD Status
//--------------------------------------------------
#define GET_OSD_OD_STATUS()                         (g_stOsdUserData.b1ODStatus)
#define SET_OSD_OD_STATUS(x)                        (g_stOsdUserData.b1ODStatus = (x))

//--------------------------------------------------
// MACRO for OD Gain
//--------------------------------------------------
#define GET_OSD_OD_GAIN()                           (g_stOsdUserData.ucODGain)
#define SET_OSD_OD_GAIN(x)                          (g_stOsdUserData.ucODGain = (x))

//--------------------------------------------------
// MACRO for Color Effect
//--------------------------------------------------
#define GET_OSD_COLOR_EFFECT()                      (g_stOsdUserData.b4ColorEffect)
#define SET_OSD_COLOR_EFFECT(x)                     (g_stOsdUserData.b4ColorEffect = (x))

//--------------------------------------------------
// MACRO for DCRStatus
//--------------------------------------------------
#define GET_OSD_DCR_STATUS()                        (g_stOsdUserData.b1OsdDcrStatus)
#define SET_OSD_DCR_STATUS(x)                       (g_stOsdUserData.b1OsdDcrStatus = (x))

//--------------------------------------------------
// MACRO for FreeSync Status
//--------------------------------------------------
#define GET_OSD_FREE_SYNC_STATUS()                  (g_stOsdUserData.b1FreeSyncStatus)
#define SET_OSD_FREE_SYNC_STATUS(x)                 (g_stOsdUserData.b1FreeSyncStatus = (x))

//--------------------------------------------------
// MACRO for Clone Mode
//--------------------------------------------------
#define GET_OSD_CLONE_MODE()                        (g_stOsdUserData.b1CloneMode)
#define SET_OSD_CLONE_MODE(x)                       (g_stOsdUserData.b1CloneMode = (x))


//--------------------------------------------------
// MACRO for ALCW (Advanced Low Color Washout)
//--------------------------------------------------
#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
#define GET_OSD_ALCW()								(g_stOsdUserData.b1EnableALCW)
#define SET_OSD_ALCW(x)								(g_stOsdUserData.b1EnableALCW = (x))
#endif

//--------------------------------------------------
// MACRO for Video Wall Setting
//--------------------------------------------------
#if (_ENABLE_VIDEO_WALL == _ON)
#define GET_OSD_VIDEO_WALL_STATUS()                         (g_stOsdUserData.b1VideoWallStatus)
#define SET_OSD_VIDEO_WALL_STATUS(x)                        (g_stOsdUserData.b1VideoWallStatus = (x))

#define GET_OSD_VIDEO_WALL_DISP_NUM()                       (g_stOsdUserData.ucVideoWallDispNum)
#define SET_OSD_VIDEO_WALL_DISP_NUM(x)                      (g_stOsdUserData.ucVideoWallDispNum = (x))

#define GET_OSD_VIDEO_WALL_H_NUM()                          (g_stOsdUserData.ucVideoWallHNum)
#define SET_OSD_VIDEO_WALL_H_NUM(x)                         (g_stOsdUserData.ucVideoWallHNum = (x))

#define GET_OSD_VIDEO_WALL_V_NUM()                          (g_stOsdUserData.ucVideoWallVNum)
#define SET_OSD_VIDEO_WALL_V_NUM(x)                         (g_stOsdUserData.ucVideoWallVNum = (x))

#define GET_OSD_VIDEO_WALL_RS232ID()						(g_stOsdUserData.ucVideoWallRs232Id)
#define SET_OSD_VIDEO_WALL_RS232ID(x)						(g_stOsdUserData.ucVideoWallRs232Id = (x))
extern BYTE GetVideoWallStatus(void);
extern BYTE GetVideoWallRS232ID(void);
#endif

//--------------------------------------------------
// MACRO for Light Sensor Setting
//--------------------------------------------------
#if (_ENABLE_LIGHT_SENSOR == _ON)
#define MIN_STEP											100
#define GET_OSD_LIGHT_SENSOR_STATUS()                       (g_stOsdUserData.b1LightSensorStatus)
#define SET_OSD_LIGHT_SENSOR_STATUS(x)                      (g_stOsdUserData.b1LightSensorStatus = (x))
#endif

//--------------------------------------------------
// MACRO for Fan Control Setting
//--------------------------------------------------
#if (_ENABLE_FAN_CONTROL == _ON)
#define GET_OSD_FAN_STATUS()                     (g_stOsdUserData.b1FanStatus)
#define SET_OSD_FAN_STATUS(x)                    (g_stOsdUserData.b1FanStatus = (x))

#define GET_OSD_FAN_PWM1()                       (g_stOsdUserData.ucFanPwm1)
#define SET_OSD_FAN_PWM1(x)                      (g_stOsdUserData.ucFanPwm1 = (x))

#define GET_OSD_FAN_PWM2()                       (g_stOsdUserData.ucFanPwm2)
#define SET_OSD_FAN_PWM2(x)                      (g_stOsdUserData.ucFanPwm2 = (x))

#define GET_OSD_FAN_PWM3()                       (g_stOsdUserData.ucFanPwm3)
#define SET_OSD_FAN_PWM3(x)                      (g_stOsdUserData.ucFanPwm3 = (x))

#define GET_OSD_FAN_PWM4()                       (g_stOsdUserData.ucFanPwm4)
#define SET_OSD_FAN_PWM4(x)                      (g_stOsdUserData.ucFanPwm4 = (x))

#define GET_OSD_SHUTDOWN_STATUS()                (g_stOsdUserData.b1ShutDownStatus)
#define SET_OSD_SHUTDOWN_STATUS(x)               (g_stOsdUserData.b1ShutDownStatus = (x))

#define GET_OSD_SHUTDOWN_TEMP()                (g_stOsdUserData.b1ShutDownTemp)
#define SET_OSD_SHUTDOWN_TEMP(x)               (g_stOsdUserData.b1ShutDownTemp = (x))

#endif

//--------------------------------------------------
// MACRO for Self Check Setting
//--------------------------------------------------
#if (_ENABLE_SELF_CHECK == _ON)
#define GET_OSD_SELF_CHECK_STATUS()                       (g_stOsdUserData.b1SelfCheckStatus)
#define SET_OSD_SELF_CHECK_STATUS(x)                      (g_stOsdUserData.b1SelfCheckStatus = (x))
#endif

#if (_ENABLE_MENU_OLED == _ON)
#define GET_OSD_OLED_OFFRS_STATUS()                       (g_stOsdUserData.b1OLEDOffRsStatus)
#define SET_OSD_OLED_OFFRS_STATUS(x)                      (g_stOsdUserData.b1OLEDOffRsStatus = (x))

#define GET_OSD_OLED_JB_STATUS()                       (g_stOsdUserData.b1OLEDJBStatus)
#define SET_OSD_OLED_JB_STATUS(x)                      (g_stOsdUserData.b1OLEDJBStatus = (x))

//--------------------------------------------------
// MACRO for OFF RS Excute							//Every 4 hours of watching tv
//--------------------------------------------------
#define GET_WAIT_TO_RUN_OFFRS()							(g_stOsdUserData.b1OffRSExcute)
#define SET_WAIT_TO_RUN_OFFRS(x)						(g_stOsdUserData.b1OffRSExcute = (x))


//--------------------------------------------------
// MACRO for JB Compensation Excute					//Every 2000 hours of watching tv
//--------------------------------------------------
#define GET_WAIT_TO_RUN_JB() 						(g_stOsdUserData.b1JBCompExcute)
#define SET_WAIT_TO_RUN_JB(x)						(g_stOsdUserData.b1JBCompExcute = (x))


//--------------------------------------------------
// MACRO for Panel Time Min
//--------------------------------------------------
#define GET_JB_MIN()                      	  		(g_stOsdUserData.ucJBMin)
#define SET_JB_MIN(x)                  	    		(g_stOsdUserData.ucJBMin = (x))

//--------------------------------------------------
// MACRO for Panel Time Hour
//--------------------------------------------------
#define GET_JB_HOUR()         		      	        (g_stOsdUserData.usJBHour)
#define SET_JB_HOUR(x)      	         	        (g_stOsdUserData.usJBHour = (x))


//--------------------------------------------------
// Macro of Off RS Hour
//--------------------------------------------------
#define GET_OFF_RS_HOUR()							(g_stOsdUserData.ucOffRSHour)
#define SET_OFF_RS_HOUR(x) 							(g_stOsdUserData.ucOffRSHour = (x))

//--------------------------------------------------
// Macro of Off RS Min
//--------------------------------------------------
#define GET_OFF_RS_MIN()							(g_stOsdUserData.ucOffRSMin)
#define SET_OFF_RS_MIN(x)							(g_stOsdUserData.ucOffRSMin = (x))
#endif

#define GET_OSD_BACKLIGHT_PWM_RES()                (g_stOsdUserData.usBacklightFreq)
#define SET_OSD_BACKLIGHT_PWM_RES(x)               (g_stOsdUserData.usBacklightFreq = (x))

#define GET_OSD_BACKLIGHT_CONTROL()					(g_stOsdUserData.b1BacklightControl)
#define SET_OSD_BACKLIGHT_CONTROL(x)				(g_stOsdUserData.b1BacklightControl = (x))

#define GET_OSD_BACKLIGHT_FREQ()                (g_stOsdUserData.usBacklightFreq)
#define SET_OSD_BACKLIGHT_FREQ(x)               (g_stOsdUserData.usBacklightFreq = (x))

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#define GET_OSD_PIXEL_SHIFT_STATUS()                (g_stOsdUserData.b1PixelShiftStatus)
#define SET_OSD_PIXEL_SHIFT_STATUS(x)               (g_stOsdUserData.b1PixelShiftStatus = (x))

#define GET_OSD_PIXEL_SHIFT_TIME()                (g_stOsdUserData.ucPixelShiftTimes)
#define SET_OSD_PIXEL_SHIFT_TIME(x)               (g_stOsdUserData.ucPixelShiftTimes = (x))
#endif
//#define GET_OSD_BACKLIGHT_INVERT()              (g_stOsdUserData.b1BacklightInvert)
//#define SET_OSD_BACKLIGHT_INVERT(x)             (g_stOsdUserData.b1BacklightInvert = (x))
//


#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR Mode
//--------------------------------------------------
#define GET_OSD_HDR_MODE()                          (g_stOsdUserData.ucHdrMode)
#define SET_OSD_HDR_MODE(x)                         (g_stOsdUserData.ucHdrMode = (x))

//--------------------------------------------------
// MACRO for Dark Enhance Status
//--------------------------------------------------
#define GET_OSD_DARK_ENHANCE_STATUS()               (g_stOsdUserData.b1DarkEnhanceStatus)
#define SET_OSD_DARK_ENHANCE_STATUS(x)              (g_stOsdUserData.b1DarkEnhanceStatus = (x))

//--------------------------------------------------
// MACRO for HDR Sharpness
//--------------------------------------------------
#define GET_OSD_HDR_SHARPNESS()                     (g_stOsdUserData.b1HdrSharpnesse)
#define SET_OSD_HDR_SHARPNESS(x)                    (g_stOsdUserData.b1HdrSharpnesse = (x))

//--------------------------------------------------
// MACRO for HDR Contrast
//--------------------------------------------------
#define GET_OSD_HDR_CONTRAST()                      (g_stOsdUserData.ucHdrContrast)
#define SET_OSD_HDR_CONTRAST(x)                     (g_stOsdUserData.ucHdrContrast = (x))

#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR ColorEnhance
//--------------------------------------------------
#define GET_OSD_HDR_COLOR_ENHANCE()                 (g_stOsdUserData.ucHdrColorEnhance)
#define SET_OSD_HDR_COLOR_ENHANCE(x)                (g_stOsdUserData.ucHdrColorEnhance= (x))
#endif
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR LightEnhance
//--------------------------------------------------
#define GET_OSD_HDR_LIGHT_ENHANCE()                 (g_stOsdUserData.ucHdrLightEnhance)
#define SET_OSD_HDR_LIGHT_ENHANCE(x)                (g_stOsdUserData.ucHdrLightEnhance= (x))
#endif
#endif

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for Local Dimming
//--------------------------------------------------
#define GET_OSD_LOCAL_DIMMING()                     (g_stOsdUserData.b1HdrLocalDimming)
#define SET_OSD_LOCAL_DIMMING(x)                    (g_stOsdUserData.b1HdrLocalDimming= (x))

//--------------------------------------------------
// MACRO for Local Dimming Smooth Backlight adjust
//--------------------------------------------------
#define GET_OSD_LD_ADJ()                            (g_stOsdUserData.ucHdrLocalDimmingAdj)
#define SET_OSD_LD_ADJ(x)                           (g_stOsdUserData.ucHdrLocalDimmingAdj = (x))
#endif

#if (_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for SDR to HDR
//--------------------------------------------------
#define GET_OSD_SDR_TO_HDR()                        (g_stOsdUserData.b1Sdr2HdrStatus)
#define SET_OSD_SDR_TO_HDR(x)                       (g_stOsdUserData.b1Sdr2HdrStatus = (x))
#endif

//--------------------------------------------------
// MACRO for Screen Mute
//--------------------------------------------------
#define GET_OSD_SCREEN_MUTE()				(g_bScreenMuteSatus)
#define SET_OSD_SCREEN_MUTE(x)			(g_bScreenMuteSatus = (x))
//--------------------------------------------------
// MACRO for Volume Mute
//--------------------------------------------------
#define GET_OSD_VOLUME_MUTE()                       (g_stOsdUserData.b1VolumeMute)
#define SET_OSD_VOLUME_MUTE(x)                      (g_stOsdUserData.b1VolumeMute = (x))

//--------------------------------------------------
// MACRO for Volume
//--------------------------------------------------
#define GET_OSD_VOLUME()                            (g_stOsdUserData.ucVolume)
#define SET_OSD_VOLUME(x)                           (g_stOsdUserData.ucVolume = (x))

//--------------------------------------------------
// MACRO for Audio Mode // 171010
//--------------------------------------------------
#define GET_OSD_AUDIO_MODE()                      (g_stOsdUserData.b2AudioMode)
#define SET_OSD_AUDIO_MODE(x)                     (g_stOsdUserData.b2AudioMode = (x))
//--------------------------------------------------
// MACRO for Audio Stand a long
//--------------------------------------------------
#define GET_OSD_AUDIO_STAND_ALONE()                 (g_stOsdUserData.b1AudioStandAloneStatus)
#define SET_OSD_AUDIO_STAND_ALONE(x)                (g_stOsdUserData.b1AudioStandAloneStatus = (x))

//--------------------------------------------------
// MACRO for Audio Source
//--------------------------------------------------
#define GET_OSD_AUDIO_SOURCE()                      (g_stOsdUserData.b1AudioSourceStatus)
#define SET_OSD_AUDIO_SOURCE(x)                     (g_stOsdUserData.b1AudioSourceStatus = (x))

//--------------------------------------------------
// MACRO for Hue
//--------------------------------------------------
#define GET_OSD_HUE()                               (g_stOsdUserData.ucHue)
#define SET_OSD_HUE(x)                              (g_stOsdUserData.ucHue = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_SATURATION()                        (g_stOsdUserData.ucSaturation)
#define SET_OSD_SATURATION(x)                       (g_stOsdUserData.ucSaturation = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_OVERSCAN_STATUS()                   (g_stOsdUserData.b1OverScan)
#define SET_OSD_OVERSCAN_STATUS(x)                  (g_stOsdUserData.b1OverScan = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_HLWIN_TYPE()                        (g_stOsdUserData.ucHLWinType)
#define SET_OSD_HLWIN_TYPE(x)                       (g_stOsdUserData.ucHLWinType = (x))

//--------------------------------------------------
// MACRO for 3D Status
//--------------------------------------------------
#define GET_OSD_3D_STATUS()                         (g_stOsdUserData.b23DStatus)
#define SET_OSD_3D_STATUS(x)                        (g_stOsdUserData.b23DStatus = (x))

//--------------------------------------------------
// MACRO for 3D LR Status
//--------------------------------------------------
#define GET_OSD_3D_LR_STATUS()                      (g_stOsdUserData.b13DLRStatus)
#define SET_OSD_3D_LR_STATUS(x)                     (g_stOsdUserData.b13DLRStatus = (x))

//--------------------------------------------------
// MACRO for 3D Format Status
//--------------------------------------------------
#define GET_OSD_3D_FORMAT_STATUS()                  (g_stOsdUserData.b23DFormatStatus)
#define SET_OSD_3D_FORMAT_STATUS(x)                 (g_stOsdUserData.b23DFormatStatus = (x))

//--------------------------------------------------
// MACRO for 3D EFFECT
//--------------------------------------------------
#define GET_OSD_3D_EFFECT()                         (g_stOsdUserData.uc3DEffect)
#define SET_OSD_3D_EFFECT(x)                        (g_stOsdUserData.uc3DEffect = (x))

//--------------------------------------------------
// MACRO for 3D 3DTO2D
//--------------------------------------------------
#define GET_OSD_3D_3DTO2D()                         (g_stOsdUserData.b13D3DTO2DStatus)
#define SET_OSD_3D_3DTO2D(x)                        (g_stOsdUserData.b13D3DTO2DStatus = (x))

//--------------------------------------------------
// MACRO for 3D Convergence
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE()                    (g_stOsdUserData.uc3DConvergence)
#define SET_OSD_3D_CONVERGENCE(x)                   (g_stOsdUserData.uc3DConvergence = (x))

//--------------------------------------------------
// MACRO for 3D Convergence Mode
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE_MODE()               (g_stOsdUserData.b33DConvergenceMode)
#define SET_OSD_3D_CONVERGENCE_MODE(x)              (g_stOsdUserData.b33DConvergenceMode = (x))

//--------------------------------------------------
// MACRO for Auto-Color Type
//--------------------------------------------------
#define _AUTO_COLOR_TYPE_INTERNAL                   0
#define _AUTO_COLOR_TYPE_EXTERNAL                   1

#define GET_OSD_FACTORY_AUTO_COLOR_TYPE()           (g_stOsdUserData.b1FactoryAutoColorType)
#define SET_OSD_FACTORY_AUTO_COLOR_TYPE(x)          (g_stOsdUserData.b1FactoryAutoColorType = (x))

//--------------------------------------------------
// MACRO for PCM Status
//--------------------------------------------------
#define GET_OSD_PCM_STATUS()                        (g_stOsdUserData.b3PCMStatus)
#define SET_OSD_PCM_STATUS(x)                       (g_stOsdUserData.b3PCMStatus = (x))


//--------------------------------------------------
// MACRO for DP Lane Count switch
//--------------------------------------------------
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#define GET_OSD_D0_TYPEC_U3_MODE()                   (g_stOsdUserData.b2D0TypeCU3Mode)
#define SET_OSD_D0_TYPEC_U3_MODE(x)                  (g_stOsdUserData.b2D0TypeCU3Mode = (x))

#define GET_OSD_D1_TYPEC_U3_MODE()                   (g_stOsdUserData.b2D1TypeCU3Mode)
#define SET_OSD_D1_TYPEC_U3_MODE(x)                  (g_stOsdUserData.b2D1TypeCU3Mode = (x))

#define GET_OSD_D2_TYPEC_U3_MODE()                   (g_stOsdUserData.b2D2TypeCU3Mode)
#define SET_OSD_D2_TYPEC_U3_MODE(x)                  (g_stOsdUserData.b2D2TypeCU3Mode = (x))

#define GET_OSD_D6_TYPEC_U3_MODE()                   (g_stOsdUserData.b2D6TypeCU3Mode)
#define SET_OSD_D6_TYPEC_U3_MODE(x)                  (g_stOsdUserData.b2D6TypeCU3Mode = (x))
#endif

//--------------------------------------------------
// MACRO for HDMI version
//--------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#define GET_OSD_D0_HDMI_VER()                       (g_stOsdUserData.b2OsdHdmiD0PortVersion)
#define SET_OSD_D0_HDMI_VER(x)                      (g_stOsdUserData.b2OsdHdmiD0PortVersion = (x))

#define GET_OSD_D1_HDMI_VER()                       (g_stOsdUserData.b2OsdHdmiD1PortVersion)
#define SET_OSD_D1_HDMI_VER(x)                      (g_stOsdUserData.b2OsdHdmiD1PortVersion = (x))

#define GET_OSD_D2_HDMI_VER()                       (g_stOsdUserData.b2OsdHdmiD2PortVersion)
#define SET_OSD_D2_HDMI_VER(x)                      (g_stOsdUserData.b2OsdHdmiD2PortVersion = (x))

#define GET_OSD_D3_HDMI_VER()                       (g_stOsdUserData.b2OsdHdmiD3PortVersion)
#define SET_OSD_D3_HDMI_VER(x)                      (g_stOsdUserData.b2OsdHdmiD3PortVersion = (x))

#define GET_OSD_D4_HDMI_VER()                       (g_stOsdUserData.b2OsdHdmiD4PortVersion)
#define SET_OSD_D4_HDMI_VER(x)                      (g_stOsdUserData.b2OsdHdmiD4PortVersion = (x))

#define GET_OSD_D5_HDMI_VER()                       (g_stOsdUserData.b2OsdHdmiD5PortVersion)
#define SET_OSD_D5_HDMI_VER(x)                      (g_stOsdUserData.b2OsdHdmiD5PortVersion = (x))
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
#define GET_OSD_USB3_RETIMER_PS_PD_WAKEUP()         (g_stOsdUserData.b1OsdUsb3RetimerPSPDWakeUp)
#define SET_OSD_USB3_RETIMER_PS_PD_WAKEUP(x)        (g_stOsdUserData.b1OsdUsb3RetimerPSPDWakeUp = (x))
#endif

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_NVRAM_DOUBLE_SIZE()                 (g_stOsdUserData.b1OsdDoubleSize)
#define SET_OSD_NVRAM_DOUBLE_SIZE(x)                (g_stOsdUserData.b1OsdDoubleSize = (x))

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
#define _OSD_RELATIVE_POSITION_ROW                 4
#define _OSD_NUMBER_1_ROW                           4
#define _OSD_NUMBER_2_ROW                           7
#define _OSD_NUMBER_3_ROW                           10
#define _OSD_NUMBER_4_ROW                           13
#define _OSD_NUMBER_11_ROW                         16
#define _OSD_NUMBER_12_ROW                         19
#define _OSD_NUMBER_13_ROW                         22

#define _OSD_NUMBER_5_ROW                           3
#define _OSD_NUMBER_6_ROW                           (_OSD_NUMBER_5_ROW+(_OSD_RELATIVE_POSITION_ROW*1))
#define _OSD_NUMBER_7_ROW                           (_OSD_NUMBER_5_ROW+(_OSD_RELATIVE_POSITION_ROW*2))
#define _OSD_NUMBER_8_ROW                           (_OSD_NUMBER_5_ROW+(_OSD_RELATIVE_POSITION_ROW*3))
#define _OSD_NUMBER_9_ROW                           (_OSD_NUMBER_5_ROW+(_OSD_RELATIVE_POSITION_ROW*4))
#define _OSD_NUMBER_10_ROW                          13
#define _OSD_TIMER_NUMBER_1_ROW                          8
#if  (_OSD_ROTATE_CW180_SUPPORT == _ON)
#define _OSD_WINDOW_CHOOSE_WIDTH_1  			13 
#define _OSD_WINDOW_CHOOSE_WIDTH_2  			12 
#else
#define _OSD_WINDOW_CHOOSE_WIDTH_1  			13//14 
#define _OSD_WINDOW_CHOOSE_WIDTH_2  			13 
#endif

#define _OSD_NUMBER_1_COL                          21    
#define _OSD_NUMBER_2_COL                          38
#define _OSD_NUMBER_2_COL                          38

#define _OSD_NUMBER_3_COL                            55
#define _OSD_NUMBER_4_COL                           (55+15)

#define _OSD_NUMBER_5_COL                           104
#define _OSD_NUMBER_6_COL                             (104+15)
#define _OSD_NUMBER_7_COL                             2
#define _OSD_NUMBER_10_COL                         38// 37
#define _OSD_NUMBER_11_COL                          49
#define _OSD_SLIDE_VALUE_OFFSET                    10
#define _OSD_TIMER_NUMBER_1_COL                    8    


#define _OSD_POSITION_1_1                                       0
#define _OSD_POSITION_1_2                                        1
#define _OSD_POSITION_1_3                                        2
#define _OSD_POSITION_2_1                                        3
#define _OSD_POSITION_2_2                                        4
#define _OSD_POSITION_2_3                                        5
#define _OSD_POSITION_3_1                                        6
#define _OSD_POSITION_3_2                                        7
#define _OSD_POSITION_3_3                                        8



#define _OSD_POSITION_1_COUNT                                       3

#define _OSD_POSITION_2_COUNT                                       6
#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
#define _OSD_POSITION_3_COUNT                                       (5+1)
#else
#define _OSD_POSITION_3_COUNT                                       5
#endif

 #if(_OD_SUPPORT == _ON)
#define _OSD_POSITION_4_COUNT                                     4
 #else
#define _OSD_POSITION_4_COUNT                                     2
#endif

#define _OSD_POSITION_5_COUNT                                      5
#define _OSD_POSITION_6_COUNT                                       3
#define _OSD_POSITION_7_COUNT                                       8
#define _OSD_POSITION_TEMP_USER_COUNT                     3
#define _OSD_NUMBER_SELECT_COLOR                      COLOR(_CP_ORANGE_H, _CP_BG)
#define _OSD_NUMBER_UNSELECT_COLOR                  COLOR(_CP_LIGHTBLUE, _CP_BG)
#define _OSD_NUMBER_GRAY_COLOR                  COLOR(_CP_GRAY, _CP_BG)

//--------------------------------------------------
// Definitions of OSD
//--------------------------------------------------
#define _PFONT_PAGE_0                               0
#define _PFONT_PAGE_1                               1
#define _PFONT_PAGE_2                               2
#define _PFONT_PAGE_3                               3
#define _PFONT_PAGE_4                               4
#define _PFONT_PAGE_5                               5
#define _PFONT_PAGE_6                               6
#define _PFONT_PAGE_7                               7
#define _PFONT_PAGE_8                               8


#define _PFONT_PAGE_ITEM_1                          3
#define _PFONT_PAGE_ITEM_2                          4
#define _PFONT_PAGE_ITEM_3                          5
#define _PFONT_PAGE_ITEM_4                          6
#define _PFONT_PAGE_ITEM_5                          7
#define _PFONT_PAGE_ITEM_6                          8
#define _PFONT_PAGE_ITEM_7                          9
#define _PFONT_PAGE_ITEM_8                          10
#define _PFONT_PAGE_INFORMATION                          11

#define _OSD_GLOBAL_START                           0x01
#define _OSD_GLOBAL_END                             0x0F

#define _OSD_PAGE_0_START                           0x04 // 4
#define _OSD_PAGE_0_END                             0x48 // 72

#define _OSD_PAGE_1_START                           0x49 // 73
#define _OSD_PAGE_1_END                             0xA6 // 166  //0x5F    

#define _OSD_PAGE_2_START							0xA7  // 167    //0xC1    
#define _OSD_PAGE_2_END								0xF5  // 245 0xF0

#define _OSD_PAGE1_0_START                           0x00
#define _OSD_PAGE1_0_END                             0x27

#define _OSD_PAGE1_1_START                           0x28
#define _OSD_PAGE1_1_END                             0x9F //0x5F

#define _OSD_PAGE1_2_START                           0xC1
#define _OSD_PAGE1_2_END                             0xF5

#define _SUB_PAGE_ITEM_1                               (_OSD_PAGE_2_END+1) // (_OSD_PAGE_2_START)
#define _SUB_PAGE_ITEM_1_END                        (_OSD_PAGE_2_END+5) // (_OSD_PAGE_2_START + 6)
#define _SUB_PAGE_ITEM_2                            (_SUB_PAGE_ITEM_1_END)
#define _SUB_PAGE_ITEM_2_END                        (_SUB_PAGE_ITEM_1_END + 5)
#define _SUB_PAGE_ITEM_3                            (_SUB_PAGE_ITEM_2_END)
#define _SUB_PAGE_ITEM_3_END                        (_SUB_PAGE_ITEM_2_END + 10)
#define _SUB_PAGE_ITEM_4                            (_SUB_PAGE_ITEM_3_END)
#define _SUB_PAGE_ITEM_4_END                        (_SUB_PAGE_ITEM_3_END + 10)
#define _SUB_PAGE_ITEM_5                            (_SUB_PAGE_ITEM_4_END)
#define _SUB_PAGE_ITEM_5_END                        (_SUB_PAGE_ITEM_4_END + 8)
#define _SUB_PAGE_ITEM_6                            (_SUB_PAGE_ITEM_5_END)
#define _SUB_PAGE_ITEM_6_END                        (_SUB_PAGE_ITEM_5_END + 8)
#define _SUB_PAGE_ITEM_7                            (_SUB_PAGE_ITEM_6_END)
#define _SUB_PAGE_ITEM_7_END                        (_SUB_PAGE_ITEM_6_END + 6)
#define _SUB_PAGE_ITEM_8                            (_SUB_PAGE_ITEM_7_END) 
#define _SUB_PAGE_ITEM_8_END                        (_SUB_PAGE_ITEM_7_END + 10)

#define _OSD_PAGE_INFORMATION_START                 0x28
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
#define _WIN0_ROTATE_BORDER_COLOR                   ((_CP_BLUE_120 << 4) | _CP_BLUE_120)
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
#define _1GLOBAL_START                          0x00                        // Global 49
#define _1DYNAMIC_START                         _1GLOBAL_START + 30          // Dynamic 0
#define _1DYNAMIC_ICON_START                    _1DYNAMIC_START + 0x08         // main menu icon (6 x 4 x 8) = 196
#define _2DYNAMIC_START                         0x00
#define _2BIT_ICON_OFFSET                     0x23 // 0x7F
#define _2BIT_ICON_START_ADDRESS               0x23   //  0x7F
#define _2BIT_ICON_START                            0x00
#define _LEFT_MENU_TIME_ICON_START           (_1DYNAMIC_START + 0x19)
#define _LEFT_MENU_AIM_ICON_START           (_1DYNAMIC_START + 0x43)
#define _LEFT_MENU_NUMBER_ICON_START           (_1DYNAMIC_START + 0x91)

#define _LOGO_START_ADDRESS                         0x00


//=============== 1Bit Icon ========================
#define _LEFT_CORNER_0								(_1DYNAMIC_START + 0x01)
#define _WHITE_EDGE_0								(_1DYNAMIC_START + 0x02)
#define _WHITE_EDGE_1								(_1DYNAMIC_START + 0x06)
#define _WHITE_EDGE_2								(_1DYNAMIC_START + 0x0F)
#define _EDGE_LINE									(_1DYNAMIC_START + 0x10)
#define _CHOOSE_ICON								(_1DYNAMIC_START + 0x16)
#define _BACKGROUND_ICON							(_1DYNAMIC_START + 0x18)





//=========== OSD Font Print Form ======================//
#define _ARC_WINDOW_0							0
#define _QUADRANGLE_WINDOW_0					1
#define _GRID_WINDOW_0							2
//=========== OSD Font Icon Address ======================//

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
//#define _LOGO_WINDOW_SIZE_X                         839
//#define _LOGO_WINDOW_SIZE_Y                         179
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

#elif(_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
#define _LOGO_WINDOW_SIZE_X			3840	 // 840	
#define _LOGO_WINDOW_SIZE_Y			2160	//145

//#define    _Logo_0x00        0x00
//#define    _Logo_0x01        0x01
//#define    _Logo_0x02        0x02
//#define    _Logo_0x03        0x03
//#define    _Logo_0x04        0x04
//#define    _Logo_0x05        0x05
//#define    _Logo_0x06        0x06
//#define    _Logo_0x07        0x07
//#define    _Logo_0x08        0x08
//#define    _Logo_0x09        0x09
//#define    _Logo_0x0a        0x0a
//#define    _Logo_0x0b        0x0b
//#define    _Logo_0x0c        0x0c
//#define    _Logo_0x0d        0x0d
//#define    _Logo_0x0e        0x0e
//#define    _Logo_0x0f        0x0f
//#define    _Logo_0x10        0x10
//#define    _Logo_0x11        0x11
//#define    _Logo_0x12        0x12
//#define    _Logo_0x13        0x13
//#define    _Logo_0x14        0x14
//#define    _Logo_0x15        0x15
//#define    _Logo_0x16        0x16
//#define    _Logo_0x17        0x17
//#define    _Logo_0x18        0x18
//#define    _Logo_0x19        0x19
//#define    _Logo_0x1a        0x1a
//#define    _Logo_0x1b        0x1b
//#define    _Logo_0x1c        0x1c
//#define    _Logo_0x1d        0x1d
//#define    _Logo_0x1e        0x1e
//#define    _Logo_0x1f        0x1f
//#define    _Logo_0x20        0x20
//#define    _Logo_0x21        0x21
//#define    _Logo_0x22        0x22
//#define    _Logo_0x23        0x23
//#define    _Logo_0x24        0x24
//#define    _Logo_0x25        0x25
//#define    _Logo_0x26        0x26
//#define    _Logo_0x27        0x27
//#define    _Logo_0x28        0x28
//#define    _Logo_0x29        0x29
//#define    _Logo_0x2a        0x2a
//#define    _Logo_0x2b        0x2b
//#define    _Logo_0x2c        0x2c
//#define    _Logo_0x2d        0x2d
//#define    _Logo_0x2e        0x2e
//#define    _Logo_0x2f        0x2f
//#define    _Logo_0x30        0x30
//#define    _Logo_0x31        0x31
//#define    _Logo_0x32        0x32
//#define    _Logo_0x33        0x33
//#define    _Logo_0x34        0x34
//#define    _Logo_0x35        0x35
//#define    _Logo_0x36        0x36
//#define    _Logo_0x37        0x37
//#define    _Logo_0x38        0x38
//#define    _Logo_0x39        0x39
//#define    _Logo_0x3a        0x3a
//#define    _Logo_0x3b        0x3b
//#define    _Logo_0x3c        0x3c
//#define    _Logo_0x3d        0x3d
//#define    _Logo_0x3e        0x3e
//#define    _Logo_0x3f        0x3f
//#define    _Logo_0x40        0x40
//#define    _Logo_0x41        0x41
//#define    _Logo_0x42        0x42
//#define    _Logo_0x43        0x43
//#define    _Logo_0x44        0x44
//#define    _Logo_0x45        0x45
//#define    _Logo_0x46        0x46
//#define    _Logo_0x47        0x47
//#define    _Logo_0x48        0x48
//#define    _Logo_0x49        0x49
//#define    _Logo_0x4a        0x4a
//#define    _Logo_0x4b        0x4b
//#define    _Logo_0x4c        0x4c
//#define    _Logo_0x4d        0x4d
//#define    _Logo_0x4e        0x4e
//#define    _Logo_0x4f        0x4f
//#define    _Logo_0x50        0x50
//#define    _Logo_0x51        0x51
//#define    _Logo_0x52        0x52
//#define    _Logo_0x53        0x53
//#define    _Logo_0x54        0x54
//#define    _Logo_0x55        0x55
//#define    _Logo_0x56        0x56
//#define    _Logo_0x57        0x57
//#define    _Logo_0x58        0x58
//#define    _Logo_0x59        0x59
//#define    _Logo_0x5a        0x5a
//#define    _Logo_0x5b        0x5b
//#define    _Logo_0x5c        0x5c
//#define    _Logo_0x5d        0x5d
//#define    _Logo_0x5e        0x5e
//#define    _Logo_0x5f        0x5f
//#define    _Logo_0x60        0x60
//#define    _Logo_0x61        0x61
//#define    _Logo_0x62        0x62
//#define    _Logo_0x63        0x63
//#define    _Logo_0x64        0x64
//#define    _Logo_0x65        0x65
//#define    _Logo_0x66        0x66
//#define    _Logo_0x67        0x67
//#define    _Logo_0x68        0x68
//#define    _Logo_0x69        0x69
//#define    _Logo_0x6a        0x6a
//#define    _Logo_0x6b        0x6b
//#define    _Logo_0x6c        0x6c
//#define    _Logo_0x6d        0x6d
//#define    _Logo_0x6e        0x6e
//#define    _Logo_0x6f        0x6f
//#define    _Logo_0x70        0x70
//#define    _Logo_0x71        0x71
//#define    _Logo_0x72        0x72
//#define    _Logo_0x73        0x73
//#define    _Logo_0x74        0x74
//#define    _Logo_0x75        0x75
//#define    _Logo_0x76        0x76
//#define    _Logo_0x77        0x77
//#define    _Logo_0x78        0x78
//#define    _Logo_0x79        0x79
//#define    _Logo_0x7a        0x7a
//#define    _Logo_0x7b        0x7b
//#define    _Logo_0x7c        0x7c
//#define    _Logo_0x7d        0x7d
//#define    _Logo_0x7e        0x7e
//#define    _Logo_0x7f        0x7f
//#define    _Logo_0x80        0x80
//#define	   _Logo_0x80_END    0x81
//
//
//#define    _Logo1_0x00        (_Logo_0x80_END + 0x00)
//#define    _Logo1_0x01        (_Logo1_0x00 + 0x01)
//#define    _Logo1_0x02        (_Logo1_0x00 + 0x02)
//#define    _Logo1_0x03        (_Logo1_0x00 + 0x03)
//#define    _Logo1_0x04        (_Logo1_0x00 + 0x04)
//#define    _Logo1_0x05        (_Logo1_0x00 + 0x05)
//#define    _Logo1_0x06        (_Logo1_0x00 + 0x06)
//#define    _Logo1_0x07        (_Logo1_0x00 + 0x07)
//#define    _Logo1_0x08        (_Logo1_0x00 + 0x08)
//#define    _Logo1_0x09        (_Logo1_0x00 + 0x09)
//#define    _Logo1_0x0a        (_Logo1_0x00 + 0x0a)
//#define    _Logo1_0x0b        (_Logo1_0x00 + 0x0b)
//#define    _Logo1_0x0c        (_Logo1_0x00 + 0x0c)
//#define    _Logo1_0x0d        (_Logo1_0x00 + 0x0d)
//#define    _Logo1_0x0e        (_Logo1_0x00 + 0x0e)
//#define    _Logo1_0x0f        (_Logo1_0x00 + 0x0f)
//#define    _Logo1_0x10        (_Logo1_0x00 + 0x10)
//#define    _Logo1_0x11        (_Logo1_0x00 + 0x11)
//#define    _Logo1_0x12        (_Logo1_0x00 + 0x12)
//#define    _Logo1_0x13        (_Logo1_0x00 + 0x13)
//#define    _Logo1_0x14        (_Logo1_0x00 + 0x14)
//#define    _Logo1_0x15        (_Logo1_0x00 + 0x15)
//#define    _Logo1_0x16        (_Logo1_0x00 + 0x16)
//#define    _Logo1_0x17        (_Logo1_0x00 + 0x17)
//#define    _Logo1_0x18        (_Logo1_0x00 + 0x18)
//#define    _Logo1_0x19        (_Logo1_0x00 + 0x19)
//#define    _Logo1_0x1a        (_Logo1_0x00 + 0x1a)
//#define    _Logo1_0x1b        (_Logo1_0x00 + 0x1b)
//#define    _Logo1_0x1c        (_Logo1_0x00 + 0x1c)
//#define    _Logo1_0x1d        (_Logo1_0x00 + 0x1d)
//#define    _Logo1_0x1e        (_Logo1_0x00 + 0x1e)
//#define    _Logo1_0x1f        (_Logo1_0x00 + 0x1f)
//#define    _Logo1_0x20        (_Logo1_0x00 + 0x20)
//#define    _Logo1_0x21        (_Logo1_0x00 + 0x21)
//#define    _Logo1_0x22        (_Logo1_0x00 + 0x22)
//#define    _Logo1_0x23        (_Logo1_0x00 + 0x23)
//#define    _Logo1_0x24        (_Logo1_0x00 + 0x24)
//#define    _Logo1_0x25        (_Logo1_0x00 + 0x25)
//#define    _Logo1_0x26        (_Logo1_0x00 + 0x26)
//#define    _Logo1_0x27        (_Logo1_0x00 + 0x27)
//#define    _Logo1_0x28        (_Logo1_0x00 + 0x28)
//#define    _Logo1_0x29        (_Logo1_0x00 + 0x29)
//#define    _Logo1_0x2a        (_Logo1_0x00 + 0x2a)
//#define    _Logo1_0x2b        (_Logo1_0x00 + 0x2b)
//#define    _Logo1_0x2c        (_Logo1_0x00 + 0x2c)
//#define    _Logo1_0x2d        (_Logo1_0x00 + 0x2d)
//#define    _Logo1_0x2e        (_Logo1_0x00 + 0x2e)
//#define    _Logo1_0x2f        (_Logo1_0x00 + 0x2f)
//#define    _Logo1_0x30        (_Logo1_0x00 + 0x30)
//#define    _Logo1_0x31        (_Logo1_0x00 + 0x31)
//#define    _Logo1_0x32        (_Logo1_0x00 + 0x32)
//#define    _Logo1_0x33        (_Logo1_0x00 + 0x33)
//#define    _Logo1_0x34        (_Logo1_0x00 + 0x34)
//#define    _Logo1_0x35        (_Logo1_0x00 + 0x35)
//#define    _Logo1_0x36        (_Logo1_0x00 + 0x36)
//#define    _Logo1_0x37        (_Logo1_0x00 + 0x37)
//#define    _Logo1_0x38        (_Logo1_0x00 + 0x38)

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
#define    _Logo_0x55        0x55
#define    _Logo_0x56        0x56
#define    _Logo_0x57        0x57
#define    _Logo_0x58        0x58
#define    _Logo_0x59        0x59
#define    _Logo_0x5a        0x5a
#define    _Logo_0x5b        0x5b
#define    _Logo_0x5c        0x5c
#define    _Logo_0x5d        0x5d
#define    _Logo_0x5e        0x5e
#define    _Logo_0x5f        0x5f
#define    _Logo_0x60        0x60
#define    _Logo_0x61        0x61
#define    _Logo_0x62        0x62
#define    _Logo_0x63        0x63
#define    _Logo_0x64        0x64
#define    _Logo_0x65        0x65
#define    _Logo_0x66        0x66
#define    _Logo_0x67        0x67
#define    _Logo_0x68        0x68
#define    _Logo_0x69        0x69
#define    _Logo_0x6a        0x6a
#define    _Logo_0x6b        0x6b
#define    _Logo_0x6c        0x6c
#define    _Logo_0x6d        0x6d
#define    _Logo_0x6e        0x6e
#define    _Logo_0x6f        0x6f
#define    _Logo_0x70        0x70
#define    _Logo_0x71        0x71
#define    _Logo_0x72        0x72
#define    _Logo_0x73        0x73
#define    _Logo_0x74        0x74
#define    _Logo_0x75        0x75
#define    _Logo_0x76        0x76
#define    _Logo_0x77        0x77
#define    _Logo_0x78        0x78
#define    _Logo_0x79        0x79
#define    _Logo_0x7a        0x7a
#define    _Logo_0x7b        0x7b
#define    _Logo_0x7c        0x7c
#define    _Logo_0x7d        0x7d
#define    _Logo_0x7e        0x7e
#define    _Logo_0x7f        0x7f
#define    _Logo_0x80        0x80
#define    _Logo_0x81        0x81
#define    _Logo_0x82        0x82
#define    _Logo_0x83        0x83
#define    _Logo_0x84        0x84
#define    _Logo_0x85        0x85
#define    _Logo_0x86        0x86
#define    _Logo_0x87        0x87
#define    _Logo_0x88        0x88
#define    _Logo_0x89        0x89
#define    _Logo_0x8a        0x8a
#define    _Logo_0x8b        0x8b
#define    _Logo_0x8c        0x8c
#define    _Logo_0x8d        0x8d
#define    _Logo_0x8e        0x8e
#define    _Logo_0x8f        0x8f
#define    _Logo_0x90        0x90
#define    _Logo_0x91        0x91
#define    _Logo_0x92        0x92
#define    _Logo_0x93        0x93
#define    _Logo_0x94        0x94
#define    _Logo_0x95        0x95
#define    _Logo_0x96        0x96
#define    _Logo_0x97        0x97
#define    _Logo_0x98        0x98
#define    _Logo_0x99        0x99
#define    _Logo_0x9a        0x9a
#define    _Logo_0x9b        0x9b
#define    _Logo_0x9c        0x9c
#define    _Logo_0x9d        0x9d
#define    _Logo_0x9e        0x9e
#define    _Logo_0x9f        0x9f
#define    _Logo_0xa0        0xa0
#define    _Logo_0xa1        0xa1
#define    _Logo_0xa2        0xa2
#define    _Logo_0xa3        0xa3
#define    _Logo_0xa4        0xa4
#define    _Logo_0xa5        0xa5
#define    _Logo_0xa6        0xa6
#define    _Logo_0xa7        0xa7
#define    _Logo_0xa8        0xa8
#define    _Logo_0xa9        0xa9
#define    _Logo_0xaa        0xaa
#define    _Logo_0xab        0xab
#define    _Logo_0xac        0xac
#define    _Logo_0xad        0xad
#define    _Logo_0xae        0xae
#define    _Logo_0xaf        0xaf
#define    _Logo_0xb0        0xb0
#define    _Logo_0xb1        0xb1
#define    _Logo_0xb2        0xb2
#define    _Logo_0xb3        0xb3
#define    _Logo_0xb4        0xb4
#define    _Logo_0xb5        0xb5
#define    _Logo_0xb6        0xb6
#define    _Logo_0xb7        0xb7
#define    _Logo_0xb8        0xb8
#define    _Logo_0xb9        0xb9
#define    _Logo_0xba        0xba
#define    _Logo_0xbb        0xbb
#define    _Logo_0xbc        0xbc
#define    _Logo_0xbd        0xbd
#define    _Logo_0xbe        0xbe
#define    _Logo_0xbf        0xbf
#define    _Logo_0xc0        0xc0
#define    _Logo_0xc1        0xc1
#define    _Logo_0xc2        0xc2
#define    _Logo_0xc3        0xc3
#define    _Logo_0xc4        0xc4
#define    _Logo_0xc5        0xc5
#define    _Logo_0xc6        0xc6
#define    _Logo_0xc7        0xc7
#define    _Logo_0xc8        0xc8
#define    _Logo_0xc9        0xc9
#define    _Logo_0xca        0xca
#define    _Logo_0xcb        0xcb
#define    _Logo_0xcc        0xcc
#define    _Logo_0xcd        0xcd
#define    _Logo_0xce        0xce
#define    _Logo_0xce_END    0xcf

#define    _Logo1_0x00        (_Logo_0xce_END + 0x00)
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

//=============== 2Bit Icon ========================

#define _HKC_MAIN_ICON0							(_2BIT_ICON_START + 0)

#define _HKC_MAIN_ICON1							(_2BIT_ICON_START + 1)
#define _HKC_MAIN_ICON2							(_2BIT_ICON_START + 2)
#define _HKC_MAIN_ICON3							(_2BIT_ICON_START + 3)
#define _HKC_MAIN_ICON4							(_2BIT_ICON_START + 4)
#define _HKC_MAIN_ICON5							(_2BIT_ICON_START + 5)
#define _HKC_MAIN_ICON6							(_2BIT_ICON_START + 6)
#define _HKC_MAIN_ICON7							(_2BIT_ICON_START + 7)
#define _HKC_MAIN_ICON8							(_2BIT_ICON_START + 8)

#define _HKC_MAIN_ICON9							(_2BIT_ICON_START + 9)
#define _HKC_MAIN_ICON10							(_2BIT_ICON_START + 10)
#define _HKC_MAIN_ICON11							(_2BIT_ICON_START + 11)
#define _HKC_MAIN_ICON12							(_2BIT_ICON_START + 12)
#define _HKC_MAIN_ICON13							(_2BIT_ICON_START + 13)
#define _HKC_MAIN_ICON14							(_2BIT_ICON_START + 14)
#define _HKC_MAIN_ICON15							(_2BIT_ICON_START + 15)
#define _HKC_MAIN_ICON16							(_2BIT_ICON_START + 16)

#define _HKC_MAIN_ICON17							(_2BIT_ICON_START + 17)
#define _HKC_MAIN_ICON18							(_2BIT_ICON_START + 18)
#define _HKC_MAIN_ICON19							(_2BIT_ICON_START + 19)
#define _HKC_MAIN_ICON20							(_2BIT_ICON_START + 20)
#define _HKC_MAIN_ICON21							(_2BIT_ICON_START + 21)
#define _HKC_MAIN_ICON22							(_2BIT_ICON_START + 22)
#define _HKC_MAIN_ICON23							(_2BIT_ICON_START + 23)
#define _HKC_MAIN_ICON24							(_2BIT_ICON_START + 24)

#define _HKC_MAIN_ICON25							(_2BIT_ICON_START + 25)
#define _HKC_MAIN_ICON26							(_2BIT_ICON_START + 26)
#define _HKC_MAIN_ICON27							(_2BIT_ICON_START + 27)
#define _HKC_MAIN_ICON28							(_2BIT_ICON_START + 28)
#define _HKC_MAIN_ICON29							(_2BIT_ICON_START + 29)
#define _HKC_MAIN_ICON30							(_2BIT_ICON_START + 30)
#define _HKC_MAIN_ICON31							(_2BIT_ICON_START + 31)
#define _HKC_MAIN_ICON32							(_2BIT_ICON_START + 32)

#define _HKC_MAIN_ICON33							(_2BIT_ICON_START + 33)
#define _HKC_MAIN_ICON34							(_2BIT_ICON_START + 34)
#define _HKC_MAIN_ICON35							(_2BIT_ICON_START + 35)
#define _HKC_MAIN_ICON36							(_2BIT_ICON_START + 36)
#define _HKC_MAIN_ICON37							(_2BIT_ICON_START + 37)
#define _HKC_MAIN_ICON38							(_2BIT_ICON_START + 38)
#define _HKC_MAIN_ICON39							(_2BIT_ICON_START + 39)
#define _HKC_MAIN_ICON40							(_2BIT_ICON_START + 40)

#define _HKC_MAIN_ICON41							(_2BIT_ICON_START + 41)
#define _HKC_MAIN_ICON42							(_2BIT_ICON_START + 42)
#define _HKC_MAIN_ICON43							(_2BIT_ICON_START + 43)
#define _HKC_MAIN_ICON44							(_2BIT_ICON_START + 44)
#define _HKC_MAIN_ICON45							(_2BIT_ICON_START + 45)
#define _HKC_MAIN_ICON46							(_2BIT_ICON_START + 46)
#define _HKC_MAIN_ICON47							(_2BIT_ICON_START + 47)
#define _HKC_MAIN_ICON48							(_2BIT_ICON_START + 48)
#define _HKC_MAIN_ICON49							(_2BIT_ICON_START + 49)
#define _HKC_MAIN_ICON50							(_2BIT_ICON_START + 50)
#define _HKC_MAIN_ICON51							(_2BIT_ICON_START + 51)
#define _HKC_MAIN_ICON52							(_2BIT_ICON_START + 52)
#define _HKC_MAIN_ICON53							(_2BIT_ICON_START + 53)
#define _HKC_MAIN_ICON54							(_2BIT_ICON_START + 54)
#define _HKC_MAIN_ICON55							(_2BIT_ICON_START + 55)
#define _HKC_MAIN_ICON56							(_2BIT_ICON_START + 56)
#define _HKC_MAIN_ICON57							(_2BIT_ICON_START + 57)
#define _HKC_MAIN_ICON58							(_2BIT_ICON_START + 58)
#define _HKC_MAIN_ICON59							(_2BIT_ICON_START + 59)
#define _HKC_MAIN_ICON60							(_2BIT_ICON_START + 60)


#define _HKC_MAIN_ICON_END					(_2BIT_ICON_START + 61)

extern BYTE code tiOSD_MAIN_BIR_ICON[];
//extern BYTE code tiOSD_MAIN_IMAGE_ICON[] ;
extern BYTE code tiOSD_MAIN_COLORTEMP_ICON[] ;
extern BYTE code tiOSD_MAIN_OSDSETTING_ICON[] ;
extern BYTE code tiOSD_MAIN_RESET_ICON[] ;
extern BYTE code tiOSD_MAIN_MISC_ICON[] ;



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
#define _OSD_MAIN_MENU_WIDTH                      55// (74+2) //150//132// 88//small osd set
#define _OSD_RIGHT_KEY_WIDTH                      34 //150//132// 88//small osd set
#define _OSD_LEFT_KEY_WIDTH                      80 //150//132// 88//small osd set
#define _OSD_LEFT_KEY_AIM_WIDTH                      8 //150//132// 88//small osd set
#define _OSD_MENU_HOT_INPUT_WIDTH                    ( 3+(11* _OSD_INPUT_AMOUNT))//150//132// 88//small osd set
#define _OSD_LEFT_KEY_TIMER_WIDTH                      12 //150//132// 88//small osd set
#define _OSD_INPUT_PORT_INFORMATION_WIDTH                      24 //150//132// 88//small osd set
#define _OSD_MAIN_MENU_HEIGHT                       27 //26
#define _OSD_RIGHT_KEY_HEIGHT                       10
#define _OSD_LEFT_KEY_HEIGHT                       24
#define _OSD_LEFT_KEY_AIM_HEIGHT                    4
#define _OSD_MENU_HOT_INPUT_HEIGHT                      5 //150//132// 88//small osd set
#define _OSD_LEFT_KEY_TIMER_HEIGHT                    5
#define _OSD_INPUT_PORT_INFORMATION_HEIGHT         8

#define _OSD_HOTKEY_MENU_WIDTH                      36
#define _OSD_HOTKEY_MENU_HEIGHT                     8

#define _OSD_HOTKEY_SOURCE_MENU_WIDTH               64
#define _OSD_HOTKEY_SOURCE_MENU_HEIGHT              8
#define _OSD_MAIN_MENU_LV1_LINE_WIDTH               15
//--------------------------------------------------
// Definations of OSD Type
//--------------------------------------------------

#define _OSD_MESSAGE_ROW_START                      2
#define _OSD_MESSAGE_CENTER_COL_START               12
#define _OSD_MESSAGE_CENTER_COL_END                 23

//--------------------------------------------------
// Definations of HL window Border Size
//--------------------------------------------------
#define _HL_WIN_BORDER_SIZE                         2

//--------------------------------------------------
// Definations of Slider
//--------------------------------------------------
#define _SLIDER_LENGHT                                      (150-2)    //small osd set
#define _SLIDER_HIGH                                16
#define _SLIDER_LENGHT_2                           250
#define _SLIDER_HIGH_2                             24
#define _SLIDER_BORDER_PIXEL                        2
#define _SLIDER_OFFSET                              6

#define _SLIDER_SELECT_BORDER_COLOR                 _CP_WHITE  
#define _SLIDER_SELECT_BG_COLOR                     _CP_BLACK

#define _SLIDER_UNSELECT_BORDER_COLOR               _CP_WHITE
#define _SLIDER_UNSELECT_BG_COLOR                   _CP_BLACK

#define _SLIDER_SELECT_COLOR                        _CP_RED
#define _SLIDER_UNSELECT_COLOR                      _CP_WHITE   


#define _SLIDER_0                                   0
#define _SLIDER_1                                   1
#define _SLIDER_2                                   2
#define _SLIDER_3                                  3
#define _SLIDER_4                                  4
#define _SLIDER_5                                  5
#define _SLIDER_6                                  6
#define _SLIDER_7                                  7
#define _SLIDER_8                                  8
#define _SLIDER_9                                  9

#define _SELECT                                     1
#define _UNSELECT                                   0

#define _SLIDER_0_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_6 //_OSD_WINDOW_4_5
#define _SLIDER_0_BG_WINDOW                         _OSD_WINDOW_4_4 //_OSD_WINDOW_5 //_OSD_WINDOW_4_4
#define _SLIDER_0_BORDER_WINDOW                     _OSD_WINDOW_4_3 //_OSD_WINDOW_5//_OSD_WINDOW_4_3

#define _SLIDER_1_BAR_WINDOW                       _OSD_WINDOW_4_5// _OSD_WINDOW_4_8
#define _SLIDER_1_BG_WINDOW                        _OSD_WINDOW_4_4 //_OSD_WINDOW_4_7
#define _SLIDER_1_BORDER_WINDOW                    _OSD_WINDOW_4_3 //_OSD_WINDOW_4_6

#define _SLIDER_2_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_5_5
#define _SLIDER_2_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5_4
#define _SLIDER_2_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_5_3

#define _SLIDER_3_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_5_8
#define _SLIDER_3_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5_7
#define _SLIDER_3_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_5_6

#define _SLIDER_4_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_6
#define _SLIDER_4_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5
#define _SLIDER_4_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_4

#define _SLIDER_5_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_6
#define _SLIDER_5_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5
#define _SLIDER_5_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_4

#define _SLIDER_6_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_5_8
#define _SLIDER_6_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5_7
#define _SLIDER_6_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_5_6

#define _SLIDER_7_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_6
#define _SLIDER_7_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5
#define _SLIDER_7_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_4

#define _SLIDER_8_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_6
#define _SLIDER_8_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5
#define _SLIDER_8_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_4

#define _SLIDER_9_BAR_WINDOW                        _OSD_WINDOW_4_5//_OSD_WINDOW_6
#define _SLIDER_9_BG_WINDOW                         _OSD_WINDOW_4_4//_OSD_WINDOW_5
#define _SLIDER_9_BORDER_WINDOW                     _OSD_WINDOW_4_3//_OSD_WINDOW_4

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

#define _NONE_ITEM                                  8

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
typedef enum
{
    _GAMMA_OFF,
    _GAMMA_18,
    _GAMMA_20,
    _GAMMA_22,
    _GAMMA_24,
#if(_TECNINT_DICOM)
	_GAMMA_RC2,
	_GAMMA_RC3,
    _GAMMA_AMOUNT = _GAMMA_RC3,
#else
    _GAMMA_AMOUNT = _GAMMA_24,
#endif
}EnumGammaType;

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

typedef enum
{
    _COLOREFFECT_STANDARD,
    _COLOREFFECT_GAME,
    _COLOREFFECT_MOVIE,
    _COLOREFFECT_PHOTO,
    _COLOREFFECT_VIVID,
    _COLOREFFECT_USER,
//    _COLOREFFECT_FPS,
    _COLOREFFECT_RTS = _COLOREFFECT_USER,

    _COLOREFFECT_AMOUNT = _COLOREFFECT_VIVID,
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
    _OSD_INPUT_A0,
    _OSD_INPUT_D0,
    _OSD_INPUT_D2,
    _OSD_INPUT_D3,
    _OSD_INPUT_D1,
    _OSD_INPUT_D4,
    _OSD_INPUT_D5,
    _OSD_INPUT_D6,
    _OSD_INPUT_AMOUNT = _OSD_INPUT_D3,
}EnumOSDInputPortDef;


//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
typedef enum
{
    _CT_9300,
    _CT_7500,
    _CT_6500,
    _CT_5800,
    _CT_SRGB,
    _CT_USER,
    _CT_COLORTEMP_AMOUNT = _CT_USER,
}EnumColortemptureDef;


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
#if(_OCC_SUPPORT == _ON)
    _PCM_OSD_SRGB,
    _PCM_OSD_ADOBE_RGB,
#endif

    _PCM_OSD_USER,
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
    _OSD_CLONE_OFF = _OFF,
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
// Definitions of Audio Mode // 171010
//--------------------------------------------------
typedef enum
{
    _AUDIO_MODE_STANDARD = 0,
    _AUDIO_MODE_MOVIE,
    _AUDIO_MODE_SPORTS,
    _AUDIO_MODE_MUSIC,
     _AUDIO_MODE_AMOUNT = _AUDIO_MODE_MOVIE,
}EnumAudioModeDef;
//--------------------------------------------------
//--------------------------------------------------

typedef struct
{
    BYTE b1OsdLogo : 1;
    BYTE b1OsdWakeUpSwitchDdcciPort : 1;
    BYTE b1OsdWakeUpShowSource : 1;
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
    BYTE b3OsdsixColorHue;
    BYTE b3OsdsixColorSaturation;
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
    _ = 0,
    _0_, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_,
    _A_, _B_, _C_, _D_, _E_, _F_, _G_, _H_, _I_, _J_, _K_, _L_, _M_, _N_, _O_, _P_, _Q_, _R_, _S_, _T_, _U_, _V_, _W_, _X_, _Y_, _Z_,
    _a_, _b_, _c_, _d_, _e_, _f_, _g_, _h_, _i_, _j_, _k_, _l_, _m_, _n_, _o_, _p_, _q_, _r_, _s_, _t_, _u_, _v_, _w_, _x_, _y_, _z_,
    _A0_,_A1_, _A2_, _a2_, _a3_, _a4_,_c0_, _E0_, _e0_, _e1_, _e2_, _N0_, _U0_, _u1_, _u2_, _o0_, _o1_, _o2_, _O3_,_I0_,

    _DOWNDOT_,                //  '
    _DOT_,                  //  .
    _LEFT_BRACE_,           //  (
    _RIGHT_BRACE_,          //  )
    _AND_,                  //  /
    _COLON_,                //  :
    _AT_0_,                 //  @
    _COMMA_,                //  ,
    _SLINE_,                //  -
    _SHIFT_LEFT_,           //  <<
    _SHIFT_RIGHT_,          //  >>
    _SEPERATE_,             //;
    _QUERY_,                //  ?  
    _60_, _61_, _62_, _63_, _64_,_65_, _66_, _67_, _68_, _69_, _6a_, _6b_, _6c_, _6d_, _6e_, _6f_,
    _70_, _71_, _72_, _73_, _74_,_75_, _76_, _77_, _78_, _79_, _7a_, _7b_, _7c_, _7d_, _7e_,_7f_, _80_, _81_, _82_, _83_, _84_,_85_, _86_, _87_, _88_, _89_,
    _8a_, _8b_, _8c_, _8d_, _8e_,_8f_, _90_, _91_, _92_, _93_, _94_, _95_, 
	_CH_JIAN, _CH_TI, _CH_ZHONG, _CH_WEN, _PLUS_, _LEFT_ARROWS_,	//<-
	_RIGHT_ARROWS_,//->
	_EU_C, _EU_N, _EU_E, _EU_y, _EU_c, _EU_k, _EU_n, _EU_n1, _KO_0, _KO_1
}EnumOSDFontDef;

typedef enum
{
	_96_ = 150,
	_97_ = 151,
	_98_ = 152,
	_99_ = 153, 
	_9a_ = 154, 
	_9b_ = 155, 
	_9c_ = 156, 
	_9d_ = 157,
	_9e_ = 158,
	_9f_ = 159,
	_a0 = 160,
	_a1 = 161,
	_a2 = 162,
	_a3 = 163,
	_a4 = 164,
	_a5 = 165,

}EnumOSDFontDef2;

typedef enum
{
    _CP_EMPTY = 0,
    _CP_BG = 0,
    _CP_BLACK = 0,
    _CP_WHITE,
    _CP_BLUE_65,
    _CP_BLUE = _CP_BLUE_65,
    _CP_GREEN_119,
    _CP_GREEN_66,
    _CP_YELLOW,
    _CP_RED,
    _CP_ORANGE,
    _CP_LIGHTBLUE,
    _CP_SELECTBOTTOM,
    _CP_PINK,
    _CP_GRAY,
    _CP_GREEN_1,
    _CP_ORANGE_DARK,
    _CP_ORANGE_H,
    _CP_GRAY_1,
	_CP_GREEN_241,
	_CP_GREEN_39,
	_CP_BLUE_158,
	_CP_BLUE_120,
		
}EnumOSDColorPaletteDef;

//typedef enum
//{
//    _LOGO_CP_BG = 0,
//    _LOGO_CP_BLACK = 0,
//    _LOGO_CP_WHITE,
//    _LOGO_CP_RED,
//    _LOGO_CP_GREEN,
//    _LOGO_CP_BLUE,
//    _LOGO_CP_YELLOW,
//    _LOGO_CP_GRAY,
//    _LOGO_CP_DARKBLUE,
//    _LOGO_CP_LIGHTBLUE,
//    _LOGO_CP_SELECTBOTTOM,
//    _LOGO_CP_PINK,
//    _LOGO_CP_RED_1,
//    _LOGO_CP_GREEN_1,
//    _LOGO_CP_ORANGE_L,
//    _LOGO_CP_ORANGE_H,
//    _LOGO_CP_GRAY_1,
//}EnumOSDColorPaletteLogo;
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
#if		1
	_LOGO_CP_COLOR1,
	_LOGO_CP_COLOR2,
	_LOGO_CP_COLOR3,
	_LOGO_CP_COLOR4,
#else
	_LOGO_CP_DARKBLUE,
	_LOGO_CP_LIGHTBLUE,
	_LOGO_CP_SELECTBOTTOM,
	_LOGO_CP_PINK,
#endif
	_LOGO_CP_RED_1,
	_LOGO_CP_GREEN_1,
	_LOGO_CP_ORANGE_L,
	_LOGO_CP_ORANGE_H,
	_LOGO_CP_GRAY_1,
}EnumOSDColorPaletteLogo;
typedef enum
{
    _MENU_NONE,

    _MENU_PICTURE,
    _MENU_COLOR,
    _MENU_OSDSETTINGS,
    _MENU_SETUP,
    _MENU_OTHER,
	_MENU_SERVICE,

	_MENU_PICTURE_BACKLIGHT,
    _MENU_PICTURE_BRIGHTNESS,
    _MENU_PICTURE_CONTRAST,
	_MENU_PICTURE_SHARPNESS,
	_MENU_PICTURE_HUE,
	_MENU_PICTURE_SATURATION,
#if (_ENABLE_MENU_OLED == _ON)
	_MENU_PICTURE_OLED_SETTINGS,
	_MENU_PICTURE_OLED_OFFRS,
	_MENU_PICTURE_OLED_JB,
#endif

    
    _MENU_COLOR_TEMPERATURE,
    _MENU_COLOR_TEMP_USER_R,
    _MENU_COLOR_TEMP_USER_G,
    _MENU_COLOR_TEMP_USER_B,
#if (_HDR10_SUPPORT == _ON)
    _MENU_COLOR_HDR,
#endif
	_MENU_COLOR_ECO,
	_MENU_COLOR_GAMMA,


    _MENU_OSDSETTINGS_LANGUAGE,
    _MENU_OSDSETTINGS_OSD_HPOS,
    _MENU_OSDSETTINGS_OSD_VPOS,
    _MENU_OSDSETTINGS_TRNASPARENCY,
    _MENU_OSDSETTINGS_MENU_TIME,
	_MENU_OSDSETTINGS_ROTATE,

    _MENU_SETUP_INPUT,
	_MENU_SETUP_AUDIOMUTE,
	_MENU_SETUP_AUDIO,
	_MENU_SETUP_DP_FORMAT,
	_MENU_SETUP_DP_MST,
	_MENU_SETUP_CLONE_MODE,
    _MENU_SETUP_RESET,


    _MENU_OTHERS_DISPLAY_SIZE,
	_MENU_OTHERS_DISPLAY_ROTATE,
#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
    _MENU_OTHERS_LOW_BLUE_LIGHT,
#endif
#if(_OD_SUPPORT== _ON)
    _MENU_OTHERS_OD,
#endif

#if (_ENABLE_VIDEO_WALL == _ON)
	_MENU_OTHERS_VIDEO_WALL_SETTINGS,
	_MENU_OTHERS_VIDEO_WALL,
	_MENU_OTHERS_VIDEO_WALL_DISP_NUM,
	_MENU_OTHERS_VIDEO_WALL_HNUM,
	_MENU_OTHERS_VIDEO_WALL_VNUM,
	_MENU_OTHERS_VIDEO_WALL_RS232ID,
#endif
#if (_ENABLE_LIGHT_SENSOR == _ON)
	_MENU_OTHERS_LIGHT_SENSOR,
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
	_MENU_OTHERS_FAN_CONTROLS,
	_MENU_OTHERS_FAN,
	_MENU_OTHERS_FAN_PWM1,
	_MENU_OTHERS_FAN_PWM2,
	_MENU_OTHERS_FAN_PWM3,
	_MENU_OTHERS_FAN_PWM4,
	_MENU_OTHERS_SHUTDOWN,
	_MENU_OTHERS_SHUTDOWN_TEMP,
	_MENU_OTHERS_TEMP,
#endif

#if (_ENABLE_SELF_CHECK == _ON)
	_MENU_OTHERS_SELF_CHECK,
#endif
#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
	_MENU_OTHERS_ALCW,
#endif

    _MENU_OTHERS_FREE_SYNC,

	_MENU_SERVICE_BACKLIGHT_PWM_RES,
	_MENU_SERVICE_BACKLIGHT_CONTROL,
#if(_PIXEL_SHIFT_SUPPORT == _ON)
	_MENU_SERVICE_PIXEL_SHIFT,
	_MENU_SERVICE_PIXEL_SHIFT_TIME,
#endif
	//_MENU_SERVICE_BACKLIGHT_INVERT,
	//_MENU_SERVICE_BACKLIGHT_FREQ,

	_MENU_PICTURE_BACKLIGHT_ADJUST,
    _MENU_PICTURE_BRIGHTNESS_ADJUST,
    _MENU_PICTURE_CONTRAST_ADJUST,
	_MENU_PICTURE_SHARPNESS_ADJUST,
	_MENU_PICTURE_HUE_ADJUST,
	_MENU_PICTURE_SATURATION_ADJUST,
#if (_ENABLE_MENU_OLED == _ON)
	_MENU_PICTURE_OLED_OFFRS_ADJ,
	_MENU_PICTURE_OLED_JB_ADJ,
#endif


    _MENU_COLOR_TEMPERATURE_ADJUST,
    _MENU_COLOR_TEMP_USER_ADJUST_R,
    _MENU_COLOR_TEMP_USER_ADJUST_G,
    _MENU_COLOR_TEMP_USER_ADJUST_B,
#if (_HDR10_SUPPORT == _ON)
    _MENU_COLOR_HDR_ADJUST,
#endif
	_MENU_COLOR_ECO_ADJUST,
	_MENU_COLOR_GAMMA_ADJUST,

	//Osd Setting 
    _MENU_OSDSETTINGS_LANGUAGE_ADJUST,
    _MENU_OSDSETTINGS_OSD_HPOS_ADJUST,
    _MENU_OSDSETTINGS_OSD_VPOS_ADJUST,
    _MENU_OSDSETTINGS_TRNASPARENCY_ADJUST,
    _MENU_OSDSETTINGS_MENU_TIME_ADJUST,
	_MENU_OSDSETTINGS_ROTATE_ADJUST,

#if 0
	_Menu_Hotkey_ECO_Adjust,
	_Menu_LEFTKEY_GAME,
	_Menu_LEFTKEY_GAME_ADJUST,
	_Menu_LEFTKEY_TIMER,
	_Menu_LEFTKEY_TIMER_ADJUST,
	_OSD_DISPLEFT_TIMER_MENU,
	_OSD_DISPLEFT_TIMER_MENU_ADJUST,
	_OSD_DISPLEFT_TIMER_MENU_POSITION,
#endif
	//setup
    _MENU_INPUT_ADJUST,
	_MENU_AUDIO_AUDIOMUTE_ON_OFF,
	_MENU_AUDIO_ADJUST,
	_MENU_SETUP_DP_FORMAT_ADJ,
	_MENU_SETUP_DP_MST_ADJ,
	_MENU_SETUP_CLONE_MODE_ADJ,

    _MENU_OTHERS_DISPLAY_SIZE_ADJUST,
	_MENU_OTHERS_DISPLAY_ROTATE_ADJUST,
#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
    _MENU_OTHERS_LOW_BLUE_LIGHT_ADJUST,
#endif
#if(_OD_SUPPORT == _ON)
    _MENU_OTHERS_OD_ADJUST,
#endif

#if (_ENABLE_VIDEO_WALL == _ON)
	_MENU_OTHERS_VIDEO_WALL_ADJ,
	_MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ,
	_MENU_OTHERS_VIDEO_WALL_HNUM_ADJ,
	_MENU_OTHERS_VIDEO_WALL_VNUM_ADJ,
	_MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ,
#endif
#if (_ENABLE_LIGHT_SENSOR == _ON)
	_MENU_OTHERS_LIGHT_SENSOR_ADJ,
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
	_MENU_OTHERS_FAN_ADJ,
	_MENU_OTHERS_FAN_PWM1_ADJ,
	_MENU_OTHERS_FAN_PWM2_ADJ,
	_MENU_OTHERS_FAN_PWM3_ADJ,
	_MENU_OTHERS_FAN_PWM4_ADJ,
	_MENU_OTHERS_SHUTDOWN_ADJ,
	_MENU_OTHERS_SHUTDOWN_TEMP_ADJ,
	//_MENU_OTHERS_TEMP_ADJ,
#endif

#if (_ENABLE_SELF_CHECK == _ON)
	_MENU_OTHERS_SELF_CHECK_ADJ,
#endif


#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
		_MENU_OTHERS_ALCW_ADJ,
#endif
    _MENU_OTHERS_FREE_SYNC_ADJUST,

	_MENU_SERVICE_BACKLIGHT_PWM_RES_ADJ,
	_MENU_SERVICE_BACKLIGHT_CONTROL_ADJ,
#if(_PIXEL_SHIFT_SUPPORT == _ON)
	_MENU_SERVICE_PIXEL_SHIFT_ADJ,
	_MENU_SERVICE_PIXEL_SHIFT_TIME_ADJ,
#endif
	//_MENU_SERVICE_BACKLIGHT_INVERT_ADJ,
	//_MENU_SERVICE_BACKLIGHT_FREQ_ADJ,

	_MENU_HOT_INPUT_ADJUST,

    _MENU_HOTKEY_VOLUME, // 170928_02
    _MENU_HOTKEY_MUTE, // 180    
    _MENU_HOTKEY_AUDIOMODE, //Eric_171010
    _MENU_HOTKEY_PICTUREMODE, //Eric_171010
#if 0
    _MENU_CONNECT_BLUETOOTH_ADJUST,			//170928_00
    _MENU_DISCONNECT_BLUETOOTH_ADJUST,	
#endif
	_MENU_HOTKEY_BACKLIGHT,
	_MENU_HOTKEY_SOURCE,
   _MENU_END,
}EnumOsdMenuState;

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
    _ICON_PAGE_DP_1_DOT_X,
    _ICON_PAGE_DP_MST,
    _ICON_PAGE_DISP_ROTATE_0,
    _ICON_PAGE_DISP_ROTATE_1,
    _ICON_PAGE_RESOLUTION,
    _ICON_PAGE_CLONE_0,
    _ICON_PAGE_FREESYNC,
    _ICON_PAGE_LATENCY,

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _ICON_PAGE_TYPEC_MODE,
    _ICON_PAGE_TYPEC_MODE_U3_ONOFF,
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
}EnumIconPageIndex;

typedef enum
{
    _ICON_SUB_SEL_NONE,
    _ICON_SUB_SEL_INPUT,

}EnumIconSun;

typedef enum
{
    _ICON_NONE = 0,
    // main
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
    _ICON_TYPEC_MODE,
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

    //option icon
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

#if (_ENABLE_MENU_OLED == _ON)
		_ICON_OFFRS,
		_ICON_JBCOMP,

		_ICON_DISP_JB_TEXT_1,
		_ICON_DISP_JB_TEXT_2,
		_ICON_DISP_OFFRS_TEXT_1,
		_ICON_DISP_OFFRS_TEXT_2,
#endif
    _OPTION_ICON_END,
}EnumIconIndex;


typedef enum
{
	_ICON_INPUT_NO_PORT = _OPTION_ICON_END,
	_ICON_INPUT_VGA,
	_ICON_INPUT_DVI,
	_ICON_INPUT_HDMI,
	_ICON_INPUT_DP,
	_ICON_INPUT_MHL,
	_ICON_INPUT_HDMI20,
	_ICON_INPUT_DUAL_DVI,
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
    _INPUT_OSD_VGA ,    
    _INPUT_OSD_DVI ,
    _INPUT_OSD_HDMI,
    _INPUT_OSD_DP,
    _INPUT_OSD_END,
    
};



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

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _OPTION_TYPEC_MODE_SELECT,
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
}EnumOptionIndex;


typedef enum
{
	_FONT1_GLOBAL,
	_REALTEK_1BIT_LOGO0,
	_REALTEK_1BIT_LOGO1,
	_REALTEK_1BIT_LOGO2,
	_REALTEK_1BIT_LOGO3,
	_REALTEK_1BIT_LOGO4,
	_REALTEK_1BIT_LOGO5,
	_FOUR_CORNER,
	_MAIN_MENU_2BIT_ICON,
	_LEFT_MENU_AIM_ICON,
	_LEFT_MENU_TIME_ICON,
	_LEFT_MENU_NUMBER_ICON,
}EnumFont;


typedef enum
{
    _PALETTE_RTD_LOGO,
    _PALETTE_MAIN_MENU,
}EnumPalette;

typedef enum
{
#if (_ENABLE_MENU_OLED == _ON)
    _ENGLISH,
	_CHINESE_T,
	_ESPANA,	
	_FRENCH,
	_GERMAN,
	_ITALIANO,
	_RUSSIAN,
	_KOREAN,
	_CHINESE_T_ArrayOriginal, // string �迭�� ��ġ.
    _LANGUAGE_AMOUNT = _RUSSIAN,
#else
	_ENGLISH,
	_ESPANA,
	_FRENCH,
	_GERMAN,
	_ITALIANO,
	_NEDERLAND, //Nederland
	_RUSSIAN,
	_KOREAN,
	_CHINESE_T,

	_LANGUAGE_AMOUNT = _RUSSIAN,
#endif
}EnumOSDLanguageDef;

enum OSDFontDefEurope
{
	_EU_0x39 = 0x39,
	_EU_0x3A,
	_EU_0x3B,
	_EU_0x3C,
	_EU_0x3D,
	_EU_0x3E,
	_EU_0x3F,
	_EU_0x40,
	_EU_0x41,
	_EU_0x42,
	_EU_0x43,
	_EU_0x44,
	_EU_0x45,
	_EU_0x46,
	_EU_0x47,
	_EU_0x48,
	_EU_0x49,
	_EU_0x4A,
	_EU_0x4B,
	_EU_0x4C,
	_EU_0x4D,
	_EU_0x4E,
	_EU_0x4F,
	_EU_0x50,
	_EU_0x51,
	_EU_0x52,
	_EU_0x53,
	_EU_0x54,
	_EU_0x55,
	_EU_0x56,
	_EU_0x57,
	_EU_0x58,
	_EU_0x59,
	_EU_0x5A,
	_EU_0x5B,
	_EU_0x5C,
	_EU_0x5D,
	_EU_0x5E,
	_EU_0x5F,
	_EU_0x60,
	_EU_0x61,
	_EU_0x62,
	_EU_0x63,
	_EU_0x64,
	_EU_0x65,
	_EU_0x66,
	_EU_0x67,
	_EU_0x68,
	_EU_0x69,
	_EU_0x6A,
	_EU_0x6B,
	_EU_0x6C,
	_EU_0x6D,
	_EU_0x6E,
	_EU_0x6F,
	_EU_0x70,
};
enum OSDAimDef
{
   // _AIM_START = 0,
	_AIM_1,
	_AIM_2,
	_AIM_3,
	_AIM_4,
	_AIM_END=_AIM_4,

};
enum OSDTimerNumberDef
{
	_TIMER_START = 0,
	_TIMER_10,
	_TIMER_20,
	_TIMER_30,
	_TIMER_40,
	_TIMER_50,
	_TIMER_60,
	_TIMER_90,
	_TIMER_END=_TIMER_90,

};
enum OSDLeftMenuChooseDef
{
	_LEFT_MENU_START = 0,
	_LEFT_AIM,
	_TIMER_TIMER,
	_LEFT_MENU_END=_TIMER_TIMER,

};

enum OSDLeftTimerPositionDef
{
	_LEFT_TIMER_POSITION_START = 0,
	_LEFT_TIMER_POSITION_1,
	_LEFT_TIMER_POSITION_2,
	_LEFT_TIMER_POSITION_3,
	_LEFT_TIMER_POSITION_END=_LEFT_TIMER_POSITION_3,

};

enum OSDFontCountDef
{
	_Countstar=0,
    _LANGUAGE,
    _HORIZONTAL,
    _VERTICAL,
    _TRANSPARENCY,
    _OSDTIMEOUT,
    _FONT_AMOUNT,

};


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
    _OSDEVENT_SHOW_CONNECT_BLUETOOTH_MSG, // Eric_170928_00
    _OSDEVENT_SHOW_DISCONNECT_BLUETOOTH_MSG, // Eric_170928_00        
}EnumOSDEvenMassage;

typedef enum
{
    _OSD_DISP_NOSIGNAL_MSG,
    _OSD_DISP_NOCABLE_MSG,
    _OSD_DISP_NOSUPPORT_MSG,
    _OSD_DISP_FAIL_SAFE_MODE_MSG,
    _OSD_DISP_AUTO_CONFIG_MSG,
    _OSD_DISP_INPUT_SIGNAL_MSG,
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
    _OSD_DISP_CONNECT_BLUETOOTH_YESNO_MSG, //170928_00
    _OSD_DISP_DISCONNECT_BLUETOOTH_YESNO_MSG, 

#if (_ENABLE_MENU_OLED == _ON)
	_OSD_DISP_JB_MSG,
	_OSD_DISP_OFF_RS_MSG,
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

//
_ICON_CHOOSE,

//
    _STRING_PICTURE,        
    _STRING_DISPLAY,
    _STRING_COLOR,
    _STRING_ADVANCE,
    _STRING_SETUP,
    _STRING_AUDIO,
    _STRING_OTHER,
	_STRING_SERVICE,

    // picture
    _STRING_BACKLIGHT,
	_STRING_BRIGHTNESS,
    _STRING_CONTRAST,
	_STRING_SHARPNESS,
	_STRING_SATURATION,
	_STRING_HUE,
	//_STRING_MAINSR,

#if (_ENABLE_MENU_OLED == _ON)
	_STRING_OLED_SETTINGS,
	_STRING_OLED_OFFRS,
	_STRING_OLED_JB,
#endif
//ECO
	_STRING_COLOR_STANDARD,	
	_STRING_COLOR_GAME,
	_STRING_COLOR_MOVIE,
	_STRING_COLOR_PHOTO,
	_STRING_COLOR_VIVID,
	_STRING_COLOR_FPS,
	_STRING_COLOR_RTS,
	_STRING_COLOR_USER,

#if 0
//GAME
	_STRING_GAME_MENU,
	_STRING_GAME_TIME,
	_STRING_GAME_CURSOR,
	_STRING_GAME_TIMER_POSITION,
#endif
//MainSR
	
	_STRING_PICTURE_OFF,
	_STRING_PICTURE_WEAK,	
	_STRING_PICTURE_MEDIAN,	
	_STRING_PICTURE_STRONG,
	_STRING_PICTURE_STRONGEST,
//#if(_USER_FUNCTION_BLACK_EQUALIZER==_ON)
//    _STRING_BLACK_EQUALIZER,
//#endif   
   //  _STRING_DCR,

    // display
    _STRING_AUTO_ADJUST,
    _STRING_HPOS,
    _STRING_VPOS,
    _STRING_CLOCK,
    _STRING_PHASE,
    //_STRING_DISP_ROTATE,    

    // color
     _STRING_COLORTEMP,
	_STRING_COLOR_RED,
	_STRING_COLOR_GREEN,
	_STRING_COLOR_BLUE,
     _STRING_HDR,
	 _STRING_COLOR_EFFECT,
	 _STRING_GAMMA,

	_STRING_COLOR_9300K,
	_STRING_COLOR_7500K,
	_STRING_COLOR_6500K,
	_STRING_COLOR_5800K,
	_STRING_COLOR_SRGB,
	_STRING_COLOR_USER_DEFINE,
	_STRING_COLOR_OFF,
	_STRING_COLOR_AUTO,
	_STRING_COLOR_SMPTE2084,

//OSD Settings
	_CHOOSE_LANGUAGE,
	_STRING_OSDSET_LANGUAGE,
	_STRING_OSDSET_HORIZONTAL,
	_STRING_OSDSET_VERTICAL,
	_STRING_OSDSET_TRANSPARENCY,
	_STRING_OSDSET_OSDTIMEOUT,
	_STRING_OSDSET_ROTATE,
//SETUP
	_STRING_SETUP_INPUT,
	_STRING_SETUP_AUDIOMUTE,
	_STRING_SETUP_AUDIO,
	_STRING_SETUP_RESET,
	_STRING_SETUP_DVI,
	_STRING_SETUP_HDMI,
	_STRING_SETUP_DP,
    _STRING_SETUP_VGA,
	_STRING_OUT_OF_RANGE,
	_STRING_NO_VIDEO_INPUT,
	_STRING_STANDBY_MODE,
	_STRING_NO_SIGNAL_INPUT,
    //_STRING_COLOR_EFFECT,
     //_STRING_COLOR_FORMAT,
     //_STRING_GAMMA,
  //  _STRING_PCM,
 #if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
    _STRING_LOW_BLUE_LIGHT_ADJUST,
#endif
//Other
	_STRING_OTHER_MENU,
	_STRING_OTHER_DISPLAY_SIZE,
	_STRING_OTHER_DISPLAY_ROTATE,
	_STRING_OTHER_LOW_BLUE,
	_STRING_OTHER_OVER_DRIVE,
	_STRING_OTHER_FREESYNC,
	_STRING_OTHER_FULLSCREEN,
	_STRING_OTHER_AUTO,
	_STRING_OTHER_4_3,
	_STRING_OTHER_5_4,
	_STRING_OTHER_1_1,
	//_STRING_OTHER_ON,
	//_STRING_OTHER_OFF,
#if 0
	_STRING_OTHER_WEAK,
	_STRING_OTHER_MEDIAN,
	_STRING_OTHER_STRONG,
	_STRING_OTHER_STRONGEST,
#endif
	//_STRING_OTHER_ALCW_SETTING_STATUS,

	_STRING_OTHER_VIDEO_WALL_SETTINGS,
#if (_ENABLE_VIDEO_WALL == _ON)
	_STRING_OTHER_VIDEO_WALL,
	_STRING_OTHER_DISPLAY_NUMBER,
	_STRING_OTHER_HORIZONTAL_NUMBER,
	_STRING_OTHER_VERTICAL_NUMBER,
	_STRING_OTHER_RS232_ID,
#endif

	_STRING_LIGHT_SENSOR,
	//_STRING_LIGHT_SENSOR_STATUS

	_STRING_OTHER_FAN_CONTROLS,

#if (_ENABLE_FAN_CONTROL == _ON)
	_STRING_OTHER_FAN,
	_STRING_OTHER_FAN_PWM1,
	_STRING_OTHER_FAN_PWM2,
	_STRING_OTHER_FAN_PWM3,
	_STRING_OTHER_FAN_PWM4,
	_STRING_OTHER_SHUTDOWN,
	_STRING_OTHER_SHUTDOWN_TEMP,
	_STRING_OTHER_TEMP,
	_STRING_OTHER_TEMP1,
	_STRING_OTHER_TEMP2,
	_STRING_OTHER_TEMP3,
	_STRING_OTHER_TEMP4,
	_STRING_OTHER_TEMP5,
	_STRING_OTHER_FAN_CONTROLS2,
#endif

	_STRING_OTHER_SELF_CHECK,
	_STRING_OTHER_ALCW_SETTING,
//

	_STRING_SERVICE_PWM_RES,
	_STRING_SERVICE_CONTROL,
#if(_PIXEL_SHIFT_SUPPORT == _ON)
	_STRING_SERVICE_PIXEL_SHIFT,
	_STRING_SERVICE_PIXEL_SHIFT_TIME,
	_STRING_5MIN,
	_STRING_10MIN,
	_STRING_15MIN,
	_STRING_20MIN,
#endif
	//_STRING_SERVICE_INVERT,
	//_STRING_SERVICE_FREQ,
	
	_STRING_SERVICE_255,
	_STRING_SERVICE_4095,
	_STRING_SERVICE_CURVE,
	_STRING_SERVICE_LINEAR,
#if 0
	_STRING_LEFT_MENU_AIM,
#endif
	_STRING_LEFT_MENU_TIMER,
//
   _STRING_COLOR_TEMP_USER_R,
   _STRING_COLOR_TEMP_USER_G,
   _STRING_COLOR_TEMP_USER_B,

    // MST
    _STRING_DP_FORMAT,
	_STRING_DP_MST,
	_STRING_CLONE,
	_STRING_DP1_1,
	_STRING_DP1_2,
	_STRING_DP1,
	_STRING_DP2,
	//_STRING_DP_FORMAT_STATUS,
	//_STRING_DP_MST_STATUS,
	//_STRING_CLONE_MODE_STATUS,

    _STRING_DDCCI,
    _STRING_ULTRA_VIVID,
    _STRING_ASPECT_RATIO,
    //_STRING_DP_EDID,
//    _STRING_OD,
 //   _STRING_OVER_SCAN,
  //  _STRING_OVER_DRIVE,


//INPUT
    _STRING_AUTO_SELECT,
    _STRING_INPUT_SELECT,
   _STRING_INPUT_STRING_ALL,
// _STRING_A0_NO_PORT,
//     _STRING_D0_DP,
//    _STRING_D1_HDMI1,
//     _STRING_D2_HDMI2,
//     _STRING_D3_DVI,
 //    _STRING_D4_DVI,
 //    _STRING_D5_DVI,
  //   _STRING_D6_DVI,
	//_STRING_D4_DVI,
	//_STRING_D5_NO_PORT,

    // audio
    _STRING_VOLUME,
    _STRING_MUTE,
  //  _STRING_STAND_ALONG,
    _STRING_AUDIO_SOURCE,

    // other
     _STRING_LANGUAGE,
     _STRING_OSD_HPOS,
     _STRING_OSD_VPOS,
    _STRING_MENU_TIME,
    _STRING_TRANSPARENCY,
    _STRING_RESET,
    _STRING_INFORMATION,
    _STRING_FACTORY,

    
    //Show OSD Number
    _STRING_SHOW_NUMBER,

    // information
    _STRING_HDCP_MODE,    

    //Adjust message
   _STRING_NO_SUPPORT,
    _STRING_AUTO_COLOR,
 //   _STRING_GO_TO_POWER_SAVING_MODE,
    _STRING_NOW_RESOLUTION,

#if 0
    _STRING_PASS,
    _STRING_FAIL,
#endif

       _STRING_ON,
       _STRING_OFF,

  // _STRING_ROTATE_TABLE1,
#if 0
    _STRING_DP_EDID_TABLE1,

    _STRING_COLOR_TEMP_TABLE1, 
//    _STRING_Color_Effect_TABLE1, 
   // _STRING_Color_Format_TABLE1, 
    _STRING_Gama_TABLE1, 
  //  _STRING_PCM_TABLE1, 
  
   _STRING_DP_OPTION_TABLE1,
  // _STRING_DP_MST_TABLE1,
   _STRING_UltraVivid_TABLE1,
   _STRING_Aspect_Ratio_TABLE1,
   //_STRING_Over_Drive_TABLE1,
   _STRING_Audio_Source_TABLE1,
    _STRING_Language_TABLE1,
   _STRING_OPTION_LEFT,
    _STRING_OPTION_RIGHT,
_STRING_CONNECT_BLUETOOTH_MSG0, //170928_01
_STRING_CONNECT_BLUETOOTH_MSG1,
_STRING_DISCONNECT_BLUETOOTH_MSG0,
_STRING_DISCONNECT_BLUETOOTH_MSG1,
_STRING_AUDIO_STANDARD, //171010
_STRING_AUDIO_MOVIE,
_STRING_AUDIO_SPORTS,
_STRING_AUDIO_MUSIC,


    _STRING_COLOREFFECT_STANDARD,
    _STRING_COLOREFFECT_GAME,
    _STRING_COLOREFFECT_MOVIE,
    _STRING_COLOREFFECT_PHOTO,
    _STRING_COLOREFFECT_VIVID,
    _STRING_COLOREFFECT_USER,
#endif
	_STRING_POWER_SAVE_STATUS,
	_STRING_VERSION,
	_STRING_GAMMA_OFF,
	_STRING_GAMMA_18,
	_STRING_GAMMA_20,
	_STRING_GAMMA_22,
	_STRING_GAMMA_24,
#if(_TECNINT_DICOM)
	_STRING_GAMMA_RC2,
	_STRING_GAMMA_RC3,
#endif
	_STRING_0_DEGREE,
	_STRING_90_DEGREE,
	_STRING_180_DEGREE,
	_STRING_270_DEGREE,
	_STRING_HFREQPCLK,

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
	_STRING_D7_PORT,
	_STRING_AUTOSELECT_PORT,
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
    _AUTO_CONFIG_DO = 0,
    _AUTO_CONFIG_RESULT,
}EnumautoConfig;

typedef enum
{
	POWER_SAVE_OFF,
	POWER_SAVE_5SEC,
	POWER_SAVE_30SEC,
	POWER_SAVE_1MIN,
	POWER_SAVE_2MIN,
	POWER_SAVE_5MIN,
	POWER_SAVE_30MIN,
	POWER_SAVE_60MIN,
	POWER_SAVE_120MIN,
}EnumPowerSaveTimes;

typedef enum
{
	PIXEL_SHIFT_5MIN = 0,
	PIXEL_SHIFT_10MIN = 1,
	PIXEL_SHIFT_15MIN = 2,
	PIXEL_SHIFT_20MIN = 3,
}EnumPixelShiftTimes;
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
extern bit b1BlueToothStatus ;	//Eric_170929

extern BYTE g_usItemNum;

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
extern BYTE g_ucFontPointer4;
extern BYTE g_ucFontPointer5;
extern BYTE g_ucFontPointer6;
extern BYTE g_ucFontPointer7;
extern BYTE g_ucFontPointer8;
//----------------------------------------------------------------------------------------
// Extern Tables from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
#if		(_CUSTOMER_TYPE == _CUSTOMER_VIMSE)		// 2017.03.22 SUH-EDIT
#if		1
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];
extern BYTE code tICON_REALTEK_1BIT_LOGO2[];	// VIMS
extern BYTE code tICON_REALTEK_1BIT_LOGO3[];	// VIMS
extern BYTE code tICON_REALTEK_1BIT_LOGO4[];	// VIMS
extern BYTE code tICON_REALTEK_1BIT_LOGO5[];	// VIMS
#else
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];	// VIMS
extern BYTE code tICON_REALTEK_1BIT_LOGO2[];	// VIMS
extern BYTE code tICON_REALTEK_1BIT_LOGO3[];	// VIMS
extern BYTE code tICON_REALTEK_1BIT_LOGO4[];	// VIMS
#endif
#elif	(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];
#elif	(_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];
#elif	(_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];
#else
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];
#endif


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
#else
extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];		// VIMS
extern BYTE code tiOSD_REALTEK_1BIT_LOGO2[];		// VIMS
extern BYTE code tiOSD_REALTEK_1BIT_LOGO3[];		// VIMS
extern BYTE code tiOSD_REALTEK_1BIT_LOGO4[];		// VIMS
#endif
#elif (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];
#else
extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];
#endif

extern BYTE	code tSTRING_5SEC[];
extern BYTE	code tSTRING_30SEC[];
extern BYTE	code tSTRING_1MIN[];
extern BYTE	code tSTRING_2MIN[];
extern BYTE	code tSTRING_5MIN[];
extern BYTE	code tSTRING_30MIN[];
extern BYTE	code tSTRING_60MIN[];
extern BYTE	code tSTRING_120MIN[];
// __RTD_OSDFONTPROP__
extern BYTE g_pucModeInfoData[];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserDdcci.c
//----------------------------------------------------------------------------------------
// __RTD_DDCCI__
extern void UserDdcciHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from RTDKey.c
//----------------------------------------------------------------------------------------
// __RTD_KEY__
extern void RTDKeyInitial(void);

//----------------------------------------------------------------------------------------
// Extern functions from Osd.c
//----------------------------------------------------------------------------------------
// __RTD_OSD__


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
//extern void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth ,BYTE ucHeight, BYTE ucColor);
//extern void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth ,BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
extern void OsdFuncSet2BitIconOffset(BYTE ucOffset);
extern void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth ,BYTE ucHeight);
#if (_ENABLE_SELF_CHECK == _ON)
extern void OsdFuncApplySelfCheckMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
#endif
#if(_SIX_COLOR_SUPPORT == _ON)
//extern void OsdFuncSixColorAdjust(void);
#endif

//extern void OsdFuncColorFormatAdjust(void);
#if(_SDR_TO_HDR_SUPPORT == _ON)
extern void OsdFuncColorPcmAdjust(void);
#endif
extern void OsdFuncSetOsdItemFlag(void);

#if(_FREEZE_SUPPORT == _ON)
extern bit OsdFuncCheckFreezeDisable(void);
extern void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern BYTE OsdFuncGetHdmiPortVersion(EnumSourceSearchPort enumSearchPort);
extern void OsdFuncSetHdmiPortVersion(EnumSourceSearchPort enumSearchPort,BYTE ucValue);
#endif
//----------------------------------------------------------------------------------------
// Extern functions from OsdDisplay.c
//----------------------------------------------------------------------------------------
// __RTD_OSDDISPLAY__
extern BYTE OsdDispJudgeSourceType(void);

extern void OsdDispDisableOsd(void);
extern void OsdDispSetPosition(BYTE ucType,EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);

extern void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor);


extern void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState);
extern void OsdDispMainMenukeySlideAndOption(BYTE ucOsdPositionState,BYTE OSDState,BYTE SlideNum,BYTE MenuExit, BYTE type);
extern WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle, bit bNumberic);
extern WORD OsdDisplayDetOverRange_Curved(WORD usValue, WORD usMax, WORD usMin, bit bCycle);

extern void OsdDispMainMenu(void);
//extern void OsdDispRightMenu(void);
extern void OsdDispLeftMenu(void);
extern void OsdDispLeftAimMenu(void);

extern void OsdDispHotKeyVolumeMenu(void); //170928_02
extern void OsdDispHotKeyMuteMenu(void);
//extern void OsdDispHotKeyAudioMode(void); //171010
//extern void OsdDispHotKeyPictureMode(void); //Eric_171010

extern void OsdDispOsdReset(void);
extern void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);
#if(_VGA_SUPPORT == _ON)
extern void OsdDispAutoConfigProc(void);
extern void OsdDisplayAutoBalanceProc(void);
#endif

#if		(_CUSTOMER_TYPE == _CUSTOMER_VIMSE)		// 2017.03.22 SUH-EDIT
extern void			OsdDispShowMainLogo(void);
#endif
#if		(_CUSTOMER_TYPE != _CUSTOMER_STANDARD)	// 2017.03.28 SUH-EDIT
extern void			OsdDispShowLogo(void);
#endif
#if		(_CUSTOMER_TYPE == _CUSTOMER_VIMSE)		// 2017.03.22 SUH-EDIT
extern void			OsdDispShowLogoColor(void);
#endif

extern void OsdDisplaySixColorGetOneColor(BYTE ucColor);
//extern void OsdDisplaySixColorSetOneColor(BYTE ucColor);


extern void COsdShowPageText(BYTE PageNo);
extern void COsdShowChoosePictureText(BYTE number);
extern void COsdShowChooseColorText(BYTE number);
extern void COsdShowChooseOSDSetText(BYTE number);
extern void COsdShowChooseSetupText(BYTE number);
extern void COsdShowChooseOtherText(BYTE number);
extern void COsdShowChooseServiceText(BYTE number);
extern void COsdShowChooseLeftMenuText(BYTE number);

extern void COsdShowPageInputString(BYTE InputOsd,BYTE InputType,BYTE NUM,BYTE MAINOSDINF);
extern void COsdShowPageInputText(void);


//Eric_20180306_Delete : Start --------------------------------- 
//extern WORD OsdDispDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
//extern void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState);
//extern void OsdDispMainMenuItemIndication2(BYTE ucItem, BYTE ucAmount, BYTE ucState);
//extern void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
//extern void OsdDispClearSelectColor(BYTE ucUpDown);

//extern void OsdDispMainSubString(BYTE ucState);
//extern void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor);
extern void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState);

//extern void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState);
//extern void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption);
//extern void OsdDispClearArrow(BYTE ucUpDown);
//extern void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious);
//extern void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary);

extern void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue);
//extern WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);

//extern void OsdDispClearSliderAndNumber(void);
//extern void OsdDispHotKeyOptionMenu(BYTE ucOption);
//extern void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption);
extern void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
extern void OsdDispHotKeySourceMenu(void);
//extern void OsdDispPanelUniformityMsgSwitch(void);
 extern void OsdDispHotKeySourceMenuSwitch(BYTE ucPort);
extern void OsdDispHotKeyBacklightMenu(void);
extern void OsdFuncShowSourceMenuCheck(void);
//extern void OsdDispShowInformation(void);
//#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
extern void OsdDispOsdRotateSwitch(void);
//#endif
//extern void OsdDispAdvanceMenuReDraw(bit bRedrawLevel);
//extern bit OsdDispAdvanceItemCheck(BYTE ucIndex);
//extern bit OsdDispAdvanceItemCountbyKeyMessage(void);
//extern BYTE OsdDispAdvanceIconGet(BYTE ucIndex);
//extern void OsdDispAdvanceItemSwitch(BYTE ucIndex);
//extern void OsdDispAdvanceItemSelect(BYTE ucIndex);

//Eric_20180306_Delete : End --------------------------------- 

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
#if		(_CUSTOMER_TYPE != _CUSTOMER_STANDARD)
extern void OsdFontPut1BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor);
#endif
extern void OsdFontPut1BitMainMenuIcon(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
extern void OsdFontPut2Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void OsdFontPut2BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void OsdFontPut1BitBackLightIcon(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);

// __RTD_OSDFONTPROP__
extern void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor ,BYTE ucLanguage);
extern void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar ,BYTE ucFontPoint, BYTE ucColor);
extern void OsdPropShowNumberTemp(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
extern void OsdPropShowNumberFloat(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
//extern BYTE OsdPutStringPropFontTable(BYTE ucLanguage, WORD ucFontPoint);

// __RTD_OSDPALETTE__
extern void OsdPaletteSelectPalette(BYTE ucValue);

// __RTD_OSDWINDOW__
extern void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
//extern void OsdWindowDrawingHighlight(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow1, BYTE ucCol1, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
//extern void OsdWindowSliderDisable(void);

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

extern void OsdFontPut1ChooseIcon(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucForeground, BYTE ucBackground);
extern void OsdFontPut1FuncHLine(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucLength,BYTE ucForeground, BYTE ucBackground);
extern void OsdThreeColorChooseTableForm(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucbox,BYTE ucType);
extern void OsdFontPut1NumberTableForm(BYTE ucRow, BYTE ucCol, BYTE ucNumberIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucnumber);
extern void OsdFontPut1FuncAimTableForm(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucbox,BYTE ucType);
extern void OsdFontPut1FuncTableForm(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucType);
extern BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum);

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
