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
// ID Code      : RTD2014NVRamOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_NVRAM_OSD__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)	// 	//0 ~ 4096=>// usContrast(1024) + ColorTemp(1024) + SubContrast(1024) + ColorGain(1024) 

#define _CONTRAST_VGA                               0x800//512//0x800	// usContrast(1024)/2	
#define _CONTRAST_DVI                               0x800//512//0x800
#define _CONTRAST_VIDEO8                            0x800//512//0x800
#define _CONTRAST_HDMI                              0x800//512//0x800
#define _CONTRAST_DP                                0x800//512//0x800

#define _SUB_CONTRAST_VGA                           512//0x800	// usSubContrast(1024)/2	
#define _SUB_CONTRAST_DVI                           512//0x800
#define _SUB_CONTRAST_VIDEO8                        512//0x800
#define _SUB_CONTRAST_HDMI                          512//0x800
#define _SUB_CONTRAST_DP                            512//0x800

#define _COLOR_GAIN_R								512//1024//0x400	// ColorGain(1024)/2
#define _COLOR_GAIN_G								512//1024//0x400
#define _COLOR_GAIN_B								512//1024//0x400

#else												//0 ~ 256 =>// usContrast(64) + ColorTemp(64) + SubContrast(64) + ColorGain(64) 

#define _CONTRAST_VGA                               0x080//32//0x080	// usContrast(64)/2
#define _CONTRAST_DVI                               0x080//32//0x080
#define _CONTRAST_VIDEO8                            0x080//32//0x080
#define _CONTRAST_HDMI                              0x080//32//0x080
#define _CONTRAST_DP                                0x080//32//0x080

#define _SUB_CONTRAST_VGA                           32//0x080	// usSubContrast(64)/2	
#define _SUB_CONTRAST_DVI                           32//0x080
#define _SUB_CONTRAST_VIDEO8                        32//0x080
#define _SUB_CONTRAST_HDMI                          32//0x080
#define _SUB_CONTRAST_DP                            32//0x080

#define _COLOR_GAIN_R								32//64//0x040	// ColorGain(64)/2
#define _COLOR_GAIN_G								32//64//0x040
#define _COLOR_GAIN_B								32//64//0x040

#endif

#if(_BRI_TYPE == _BRI_GEN_1_10BIT)	// //0 ~ 1024=>// usBrightness(512) + SubBrightness(256) + ColorOffset(256)

#define _BRIGHTNESS_VGA                             0x200//256//0x1F8	// usBrightness(512)/2	
#define _BRIGHTNESS_DVI                             0x200//256//0x200
#define _BRIGHTNESS_VIDEO8                          0x200//256//0x200
#define _BRIGHTNESS_HDMI                            0x200//256//0x200
#define _BRIGHTNESS_DP                              0x200//256//0x200

#define _SUB_BRIGHTNESS_VGA                         128			// SubBrightness(256)/2
#define _SUB_BRIGHTNESS_DVI                         128	
#define _SUB_BRIGHTNESS_VIDEO8                      128	
#define _SUB_BRIGHTNESS_HDMI                        128	
#define _SUB_BRIGHTNESS_DP                          128	

#define _COLOR_OFFSET_R								128//256//0x100	// ColorOffset(256)/2
#define _COLOR_OFFSET_G								128//256//0x100
#define _COLOR_OFFSET_B								128//256//0x100

#else												//0 ~ 256 =>// usBrightness(128) + ColorOffset(64) + ColorOffset(64)

#define _BRIGHTNESS_VGA                             0x080//64//0x07E	// usBrightness(128)/2
#define _BRIGHTNESS_DVI                             0x080//64//0x080
#define _BRIGHTNESS_VIDEO8                          0x080//64//0x080
#define _BRIGHTNESS_HDMI                            0x080//64//0x080
#define _BRIGHTNESS_DP                              0x080//64//0x080

#define _SUB_BRIGHTNESS_VGA                         32			// SubBrightness(64)/2
#define _SUB_BRIGHTNESS_DVI                         32	
#define _SUB_BRIGHTNESS_VIDEO8                      32	
#define _SUB_BRIGHTNESS_HDMI                        32	
#define _SUB_BRIGHTNESS_DP    

#define _COLOR_OFFSET_R								32//64		// ColorOffset(64)/2
#define _COLOR_OFFSET_G								32//64
#define _COLOR_OFFSET_B								32//64

#endif
//--------------------------------------------------
// Six Color Data Default Values
//--------------------------------------------------
#define _SIX_COLOR_HUE_R                            50
#define _SIX_COLOR_SATURATION_R                     100

#define _SIX_COLOR_HUE_Y                            50
#define _SIX_COLOR_SATURATION_Y                     100

#define _SIX_COLOR_HUE_G                            50
#define _SIX_COLOR_SATURATION_G                     100

#define _SIX_COLOR_HUE_C                            50
#define _SIX_COLOR_SATURATION_C                     100

#define _SIX_COLOR_HUE_B                            50
#define _SIX_COLOR_SATURATION_B                     100

#define _SIX_COLOR_HUE_M                            50
#define _SIX_COLOR_SATURATION_M                     100

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PageInfo Address
//--------------------------------------------------
#define _FLASH_FW_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 16)
#define _FLASH_FW_VERSIONCODE_ADDR                  (_FLASH_PAGE_SIZE - 15)
#define _PAGEINFO_CHECKSUM_ADDR                     (_FLASH_PAGE_SIZE - 5)
#define _PAGEINFO_PAGEID_ADDR                       (_FLASH_PAGE_SIZE - 4)
#define _PAGEINFO_MOVECOUNT_ADDR                    (_FLASH_PAGE_SIZE - 3)

// This value is used to indicate the EEPROM emulaiton FW version
#define _EEPROM_EMULATION_VERSION                   0x01
#endif

#define CUSTOMER_USERDATA_BANK           17
#define CUSTOMER_USERDATA_PAGE_START     0
#define FLASH_PAGE_SIZE         256
#define CUSTOMER_USERDATA_STRUCT_SIZE         sizeof(StructOsdCustomerUserDataType)

typedef struct
{
    StructOsdUserDataType stOsdUserData;
    StructBriConDataType stBriConData;
    StructBriConDataType stBackupBriConData[_SOURCE_AMOUNT];
    StructColorProcDataType stColorProcData;
    StructSixColorDataType stSixColorData;

} StructOsdCustomerUserDataType;

//--------------------------------------------------
code StructOsdServiceDataType g_stOsdServiceDataDefault =	
    {
        _OFF,                   // BYTE b1IsService : 1;	
        _OFF,                   // BYTE b1LCDtest:1;
        _SOURCE_NAME_DP1,       // BYTE b4D0Name : 4;
        _SOURCE_NAME_DP2,       // BYTE b4D1Name : 4;
        _SOURCE_NAME_HDMI1,     // BYTE b4D2Name : 4;
#if(_SDI_CONVERTER_TYPE == _SDI_CONVERTER_NONE)
        _SOURCE_NAME_HDMI2,     // BYTE b4D3Name : 4;
#else
        _SOURCE_NAME_SDI,       // BYTE b4D3Name : 4;
#endif
        _OFF,                   // BYTE b1OsdLogo : 1;	
        _ON,                    // BYTE b1BacklightInvert : 1;
        180,                    // WORD usBacklightFreq;
        _DEFAULT_BACKLIGHT_MIN, // WORD usBacklightMin;		
        _DEFAULT_BACKLIGHT_MAX, // WORD usBacklightMax;		
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
        _DEFAULT_STABILUX, // WORD usStabilux;
#endif
#if (_ENABLE_LIGHT_SENSOR == _ON)
        _OFF,                    // BYTE b1LightSensorStatus : 1;  
#endif
        _OFF,                 // BYTE b1LCDtestMode;
#if (_ENABLE_FAN_CONTROL == _ON)
        _AUTO, // BYTE b1FanStatus : 2;
        0x80,  // BYTE ucFanPwm;
        //0x80,  // BYTE ucFanPwm1;
        //0x80,  // BYTE ucFanPwm2;
        //0x80,  // BYTE ucFanPwm3;
        //0x80,  // BYTE ucFanPwm4;
        _OFF,  // BYTE b1ShutDownStatus : 1;
        75,    // BYTE b1ShutDownTemp;
        0,     // BYTE ucMaxTemp;
#endif
#if (_ENABLE_MENU_OLED == _ON)
	_OFFRS_AUTO,						// BYTE ucOLEDOffRsStatus;
	_OFF,						// BYTE b1OLEDJBStatus : 1;
	_OFF,						//b1OffRSExcute :1
	_OFF,						//b1JBCompExcute :1
	0,						    // BYTE ucOffRSHour
	0,						    // BYTE ucOffRSMin
	0,							// WORD usJBHour
	0,							// BYTE ucJBMin
    _POWER_SAVE_5MIN,            //BYTE ucSequenceTime;
#endif
    0,                   // BYTE ucOSDLogoList 
    {'T', 'I', 'T', 'A', 'N', 0, 0, 0, 0, 0, 0, 0, 0, 0}, // BYTE b14EDIDName[14];
    {'0', '0', '0', '0', '0', '0', '0', 0, 0, 0, 0, 0, 0, 0},  // BYTE b14EDIDSerial[14];    
    70,//BYTE b1EIDHSize;
    40,//BYTE b1EDIDVSize;
    _USERASSIGN_NONE,//BYTE b1UserAssignUp;
    _USERASSIGN_NONE,//BYTE b1UserAssignDown;
    _USERASSIGN_BACKLIGHT,//BYTE b1UserAssignLeft;
    _USERASSIGN_CONTRAST,//BYTE b1UserAssignRight;
};

//--------------------------------------------------

// Attention: it is necessary for sizeof(StructOsdUserDataType) < ((_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START) * (_DATA_ITEM_LENGTH - 2))
// Please check it when add items in StructOsdUserDataType
code StructOsdUserDataType g_stOSDDefaultData =		//  OSD Default Data
{
	/*
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
    (WORD)_BACKLIGHT_MAX,//0x0080,  // usBackLight;	//  _BACKLIGHT_MAX : 255 (_BACKLIGHT_PWM_INVERSE => _OFF)
#else
    (WORD)_BACKLIGHT_MAX,//0x0800,  // usBackLight;	
#endif
	*/
	(WORD)_DEFAULT_BACKLIGHT_MAX, // 0x0800,                   // usBackLight;	// (4095)
	_LINEAR,					  // BYTE b1BacklightControl : 1;	
    _OSD_H_POS_MIN,//64,//62,//50,//55,//50,                       // ucOsdHPos;	
    _OSD_V_POS_MIN,//50,//4,//50,                       // ucOsdVPos;	
    30,//10,                       // ucOsdTimeout;		
    0,                        // ucAspectOriginRatio
    20,//30,//0,                        // ucTransparency;	
//--------------------------------------------------------
	_OSD_DM_1P,               // BYTE ucDisplayMode		//  RTD2795 Not Used
    0,                        // BYTE ucSelectRegionWidth
    _SELECT_REGION_COLOR_0,   // BYTE ucSelectRegionColor
    _PIP_POSITON_RB,                          // BYTE ucPipSubPosType
    _OSD_PIP_USER_POSITION_H_MAX,          // WORD usPipSubHPos
    _OSD_PIP_USER_POSITION_V_MAX,          // WORD usPipSubVPos
    _OSD_PIP_SIZE_MAX,                        // BYTE ucPipSubScaling
    _OSD_PIP_TRANSPARENCY_MIN,                // BYTE ucPipSubBlending
    _OSD_PBP_LR_RATIO_MIN,                 // BYTE ucPbpLrRatio
//--------------------------------------------------------
    _ENGLISH,                 // b4Language;
    _COLOREFFECT_STANDARD,    // b4ColorEffect;
//--------------------------------------------------------
    _CT_D65,//_CT_SRGB,//_CT_6500,                 // b4ColorTempType;	//  _CT_6500 -> _CT_SRGB ( Gain Center )	
    _COLOR_SPACE_RGB,         // b3VGARGBYUV;
    _COLOR_SPACE_RGB,         // b3DVIRGBYUV;
//--------------------------------------------------------
    2,                        // b3Sharpness;
    _OSD_ROTATE_DEGREE_0,     // b1OsdRotate;
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,     // b2DispRotationSizeType;
    _OFF,//_ON,                      // b1OverScan;		//  OverScan Off
//--------------------------------------------------------
    _GAMMA_OFF,               // b3Gamma;
    _OSD_ASPECT_RATIO_FULL,   // b3AspectRatio;
    _ON,                      // b1DDCCIStatus;
    _OFF,                     // b1OsdESStatus;
//--------------------------------------------------------
    _OD_GAIN_CENTER,          // ucODGain;
    _DEFAULT_HUE,             // cHue;
    _DEFAULT_SATURATION,      // ucSaturation;
    _HL_WIN_OFF,              // ucHLWinType;
//--------------------------------------------------------
    _PCM_OSD_NATIVE,          // b3PCMStatus : 3;
    _ULTRA_VIVID_OFF,         // b2UltraVividStatus : 2;
    _OFF,                     // b1VolumeMute : 1;
    _OFF,                     // b1AudioStandAloneStatus : 1;
    _DIGITAL_AUDIO,//0,       // b1AudioSourceStatus : 1;	//  ( 0: _LINE_IN_AUDIO  1: _DIGITAL_AUDIO )
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    0,						  // BYTE b1TtsSupport: 1;
    0,						  // BYTE ucTtsTextVolume;
    0,						  // BYTE ucTtsAudioVolume;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
//--------------------------------------------------------
    30,//50,                  // ucVolume;		//  DAC Volume Set
//--------------------------------------------------------
    _OFF,                      // b1ODStatus : 1;
    0x00,                      // b33DConvergenceMode : 3;
    _AUTO_COLOR_TYPE_EXTERNAL, // b1FactoryAutoColorType : 1;
    _ON,                       // BYTE b1PanelUniformity : 1;
    0,                         // BYTE b1PCMSoftProftMode : 1;
//--------------------------------------------------------
    _OSD_INPUT_AUTO,//_OSD_INPUT_D1,	//0,                        // BYTE ucOsdInputPort;		// AUTO -> DP1
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _TYPE_C_U3_OFF,            // BYTE b1D0TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D1TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D2TypeCU3Mode;
    _TYPE_C_U3_OFF,            // BYTE b1D6TypeCU3Mode;
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D0TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D1TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D2TypeCPinAssignmentESupportSelect;
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON,            // BYTE b1D6TypeCPinAssignmentESupportSelect;
#endif
#endif
//--------------------------------------------------------
    _DP_VER_1_DOT_3,//0,                     // b1OsdDpD0PortVersion : 2;		//  DP Version 1.1/1.2/1.3
    _DP_VER_1_DOT_3,//0,                     // b1OsdDpD1PortVersion : 2;
    0,                         // b3OsdDispRotate : 3;
    0,                         // b1OsdDpVersionHotKeyDisp : 1;
//--------------------------------------------------------
    0,                         // b1PreShowDpHotKeyVersion : 1;
    0,                         // b3PanelUniformityType : 3;
    0,                         // b1OsdDpD6PortVersion : 2;
    0,                         // b1OsdDpD2PortVersion : 2;
    _OFF,                      // b1FreeSyncStatus : 1;
    _OFF,                      // b1DpAdaptiveSyncStatus : 1;
    _OSD_CLONE_ON,             // b1CloneMode: 1;				// 	Clone Mode On
    0,							// b3CloneSrc : 3;	
//--------------------------------------------------------
	_OFF,   					// b1ResetDo : 1;				
	_POWER_SAVE_30SEC,			// ucPowerSaveTime;
	1,							// ucSetId;
	0,							// ucTransferId;				//  ( 0: All Set , 0~100 )	
	_HPD_MODE1,					// b2HpdMode : 2;

	_OFF,						// b1AutoAdjustDo : 1;		
	_FAN_MODE_OFF,				// b2FanControl : 2;		// 0: Auto , 1: On , 2: Off
	40,							// ucActiveTemp;
	3,							// ucHysteresis;
	0,							// ucCurrentTemp;
	_OFF,						// b1ShutdownMode : 1;
	80,							// ucShutdownTemp;
	_OFF,						// b1AutoDimming : 1;
	//100,	//WORD ucDimming;	//WORD usBackLight;
	400,						// usMaxAmbient;
	200,						// usMinAmbient;
	0,							// usCurLux;
	_ON,//_OFF,						// b1VideoWall : 1;
	1,							// ucDisplayNum;
	1,							// ucHSetCount;
	1,							// ucVSetCount;
	0,							// ucHEdgeAdjust;
	0,							// ucVEdgeAdjust;
	0,							// b1ReverseScan : 1;
	0,							// b1InputSwapDo : 1;	
	0,							// b1BurnIn : 1;		
	0, 							// ucSelectRegion;		
    0,							// b1KeyLock : 1;	
#if(_CUSTOMER_TYPE == _CUSTOMER_TECNNIT )
	0,							// b1Stabilizer : 1; 
#endif	
//--------------------------------------------------------
    _LATENCY_L,                // b2LatencyStatus : 2
    _OFF,                      // BYTE b1OsdDoubleSize :1;
	_OFF,                      // b2OsdDpMST : 3;				 
//--------------------------------------------------------	
#if(_HDR10_SUPPORT == _ON)
    _HDR10_MODE_OFF,              // BYTE ucHdrMode;
    _OFF,                       // b1DarkEnhanceStatus : 1;
    _OFF,                       // b1HdrSharpness : 1;
    0,                          // BYTE ucHdrContrast;
    0,                          // BYTE ucHdrColorEnhance;
    0,                          // BYTE ucHdrLightEnhance;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _OFF,                       // BYTE b1HdrLocalDimming : 1;
    50,                         // BYTE ucHdrLocalDimmingAdj;
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
    _OFF,                       // b1Sdr2HdrStatus : 1;
#endif

// --------------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    _HDMI_1P4,                 // BYTE b2OsdHdmiD0PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD1PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD2PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD3PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD4PortVersion : 2;
    _HDMI_1P4,                 // BYTE b2OsdHdmiD5PortVersion : 2;
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
    _TRUE,                     // BYTE b1OsdUsb3RetimerPDWakeUp: 1;
    _TRUE,                     // BYTE b1OsdUsb3RetimerPSWakeUp: 1;
    _HUB_UFP_TYPE_C_INPUT_PORT, // EnumHubInputPort enumHubInputPortSwitchbyUser;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
	_OSD_MBR_USER_DISABLE,    // b2MbrStatus : 2;
	_OSD_MBR_DUTY_DEFAULT,    // b7MbrDutys : 7;
	_OSD_MBR_POS_DEFAULT,     // b7MbrPosition : 7;
#endif
};

code StructBriConDataType tBriConDefaultData[] =	// Color Control Default Data
{
    {
        _BRIGHTNESS_VGA,
        _CONTRAST_VGA,

		_SUB_BRIGHTNESS_VGA,	
        _SUB_CONTRAST_VGA,
        
        _COLOR_OFFSET_R,	
        _COLOR_OFFSET_G,
        _COLOR_OFFSET_B,
        _COLOR_GAIN_R,
        _COLOR_GAIN_G,
        _COLOR_GAIN_B,
    },

    {
        _BRIGHTNESS_VIDEO8,
        _CONTRAST_VIDEO8,

		_SUB_BRIGHTNESS_VIDEO8,	
        _SUB_CONTRAST_VIDEO8,

		_COLOR_OFFSET_R,
        _COLOR_OFFSET_G,
        _COLOR_OFFSET_B,
        _COLOR_GAIN_R,
        _COLOR_GAIN_G,
        _COLOR_GAIN_B,
    },

    {
        _BRIGHTNESS_DVI,
        _CONTRAST_DVI,

		_SUB_BRIGHTNESS_DVI,	
        _SUB_CONTRAST_DVI,

		_COLOR_OFFSET_R,
        _COLOR_OFFSET_G,
        _COLOR_OFFSET_B,
        _COLOR_GAIN_R,
        _COLOR_GAIN_G,
        _COLOR_GAIN_B,
    },

    {
        _BRIGHTNESS_HDMI,
        _CONTRAST_HDMI,

		_SUB_BRIGHTNESS_HDMI,	
        _SUB_CONTRAST_HDMI,

		_COLOR_OFFSET_R,
        _COLOR_OFFSET_G,
        _COLOR_OFFSET_B,
        _COLOR_GAIN_R,
        _COLOR_GAIN_G,
        _COLOR_GAIN_B,
    },

    {
        _BRIGHTNESS_DP,
        _CONTRAST_DP,

		_SUB_BRIGHTNESS_DP,	
        _SUB_CONTRAST_DP,

		_COLOR_OFFSET_R,
        _COLOR_OFFSET_G,
        _COLOR_OFFSET_B,
        _COLOR_GAIN_R,
        _COLOR_GAIN_G,
        _COLOR_GAIN_B,
    },

};
/*
code StructColorProcDataType tColorTempDefaultData[] =	//  Color Temp Default Data
{
    {
        _CT9300_RED,
        _CT9300_GREEN,
        _CT9300_BLUE,
    },

    {
        _CT7500_RED,
        _CT7500_GREEN,
        _CT7500_BLUE,
    },

    {
        _CT6500_RED,
        _CT6500_GREEN,
        _CT6500_BLUE,
    },

    {
        _CT5800_RED,
        _CT5800_GREEN,
        _CT5800_BLUE,
    },

    {
        _CTSRGB_RED,
        _CTSRGB_GREEN,
        _CTSRGB_BLUE,
    },

    {
        _CTUSER_RED,
        _CTUSER_GREEN,
        _CTUSER_BLUE,
    },
};
*/
//--------------------------------------------------
code StructColorProcDataType tColorTempDefaultData[] =	
    {
        // D56
        {
            _CT_D56_RED,
            _CT_D56_GREEN,
            _CT_D56_BLUE,
            (_COLOR_BIAS_CENTER << 2), // usColorBIASR
            (_COLOR_BIAS_CENTER << 2), // usColorBIASG
            (_COLOR_BIAS_CENTER << 2), // usColorBIASB
            (_COLOR_GAIN_CENTER << 4), // usColorGainR
            (_COLOR_GAIN_CENTER << 4), // usColorGainG
            (_COLOR_GAIN_CENTER << 4), // usColorGainB
        },
        // D65
        {
            _CT_D65_RED,
            _CT_D65_GREEN,
            _CT_D65_BLUE,
            (_COLOR_BIAS_CENTER << 2), // usColorBIASR
            (_COLOR_BIAS_CENTER << 2), // usColorBIASG
            (_COLOR_BIAS_CENTER << 2), // usColorBIASB
            (_COLOR_GAIN_CENTER << 4), // usColorGainR
            (_COLOR_GAIN_CENTER << 4), // usColorGainG
            (_COLOR_GAIN_CENTER << 4), // usColorGainB
        },
        // D93
        {
            _CT_D93_RED,
            _CT_D93_GREEN,
            _CT_D93_BLUE,
            (_COLOR_BIAS_CENTER << 2), // usColorBIASR
            (_COLOR_BIAS_CENTER << 2), // usColorBIASG
            (_COLOR_BIAS_CENTER << 2), // usColorBIASB
            (_COLOR_GAIN_CENTER << 4), // usColorGainR
            (_COLOR_GAIN_CENTER << 4), // usColorGainG
            (_COLOR_GAIN_CENTER << 4), // usColorGainB
        },
        // USER
        {
            _CTUSER_RED,
            _CTUSER_GREEN,
            _CTUSER_BLUE,
            (_COLOR_BIAS_CENTER << 2), // usColorBIASR
            (_COLOR_BIAS_CENTER << 2), // usColorBIASG
            (_COLOR_BIAS_CENTER << 2), // usColorBIASB
            (_COLOR_GAIN_CENTER << 4), // usColorGainR
            (_COLOR_GAIN_CENTER << 4), // usColorGainG
            (_COLOR_GAIN_CENTER << 4), // usColorGainB
        },
        /*
                {
                    _CTSRGB_RED,
                    _CTSRGB_GREEN,
                    _CTSRGB_BLUE,
                    (_COLOR_BIAS_CENTER << 2), // usColorBIASR
                    (_COLOR_BIAS_CENTER << 2), // usColorBIASG
                    (_COLOR_BIAS_CENTER << 2),  // usColorBIASB
                    (_COLOR_GAIN_CENTER << 4),  // usColorGainR
                    (_COLOR_GAIN_CENTER << 4),  // usColorGainG
                    (_COLOR_GAIN_CENTER << 4),  // usColorGainB
                },

                {
                    _CTUSER_RED,
                    _CTUSER_GREEN,
                    _CTUSER_BLUE,
                    (_COLOR_BIAS_CENTER << 2), // usColorBIASR
                    (_COLOR_BIAS_CENTER << 2), // usColorBIASG
                    (_COLOR_BIAS_CENTER << 2),  // usColorBIASB
                    (_COLOR_GAIN_CENTER << 4),  // usColorGainR
                    (_COLOR_GAIN_CENTER << 4),  // usColorGainG
                    (_COLOR_GAIN_CENTER << 4),  // usColorGainB
                },
                */
};

code StructOsdInputPortDataType tOsdInputPortDataDefault[_OSD_INPUT_AMOUNT] =	
    {
        {
// _A0_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },

        {
// _D0_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },

        {
// _D1_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },

        {
// _D2_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },

        {
// _D3_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },

        {
// _D4_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },

        {
// _D5_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },

        {
// _D6_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },
/*
        {
// _D7_INPUT_PORT
#if (_HDR10_SUPPORT == _ON)
            _HDR10_MODE_OFF,
#endif
            0,                      // BYTE ucAspectOriginRatio
            2,                      // BYTE b3Sharpness : 3;
            _OSD_ASPECT_RATIO_USER, // BYTE b3AspectRatio : 3;
            _OFF,                   // BYTE b1OverScan : 1;
        },
*/
};

//--------------------------------------------------
code StructSixColorDataType g_stSixColorDefaultData =
{
    _SIX_COLOR_HUE_R,
    _SIX_COLOR_SATURATION_R,
    _SIX_COLOR_HUE_Y,
    _SIX_COLOR_SATURATION_Y,
    _SIX_COLOR_HUE_G,
    _SIX_COLOR_SATURATION_G,
    _SIX_COLOR_HUE_C,
    _SIX_COLOR_SATURATION_C,
    _SIX_COLOR_HUE_B,
    _SIX_COLOR_SATURATION_B,
    _SIX_COLOR_HUE_M,
    _SIX_COLOR_SATURATION_M,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructOsdUserDataType g_stOSDUserData;
StructBriConDataType g_stBriConData;
StructBriConDataType g_stBackupBriConData[_SOURCE_AMOUNT];	
StructColorProcDataType g_stColorProcData;
StructSixColorDataType g_stSixColorData;
StructTimeType g_stPanelTimeData;

StructOsdServiceDataType g_stOsdServiceData;	
StructOsdCustomerUserDataType g_stOSDCustomerUserData;

bit g_bForceSkip;
BYTE ucBackupSerialNum[13];	
BYTE ucBackupSetId;	

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
DWORD g_ulFlashMoveCount;
BYTE g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
WORD g_pusFlashAddrArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
BYTE g_pucFlashPageArr[_END_OF_PAGEID - _START_OF_PAGEID + 1];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
void RTDEepromStartup(void);
void RTDEepromWholeRestore(void);
void RTDEepromRestoreBacklight(void);
void RTDEepromLoadOSDData(void);
void RTDEepromSaveOSDData(void);
void RTDEepromRestoreOSDData(void);
void RTDEepromLoadOsdServiceData(void);	
void RTDEepromSaveOsdServiceData(void);	
void RTDEepromRestoreOsdServiceData(void);	

void RTDEepromLoadBriCon(BYTE ucSource);
void RTDEepromSaveBriCon(BYTE ucSource);
void RTDEepromRestoreBriCon(void);

void RTDEepromBackupColorCon(void);	
void RTDEepromRecoveryColorCon(void);

void RTDEepromBackupSetId(void);
void RTDEepromRecoverySetId(void);


void RTDEepromLoadColorSetting(BYTE ucColorTempType);
void RTDEepromSaveColorSetting(BYTE ucColorTempType);
void RTDEepromRestoreColorSetting(void);
void RTDEepromRestoreUserColorSetting(void);
void RTDEepromLoadSixColorData(void);
void RTDEepromSaveSixColorData(void);
void RTDEepromRestoreSixColorData(void);
void RTDEepromLoadPanelUsedTimeData(void);
void RTDEepromSavePanelUsedTimeData(void);
void RTDEepromRestorePanelUsedTimeData(void);

void UserCommonFlashSaveCustomerUserData(void);
void UserCommonFlashCustomerUserData(void);
#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

BYTE RTDFlashGetFreePage(void);
bit RTDFlashIsPageInfoValid(BYTE ucPage);
void RTDFlashInitialDataPage(BYTE ucPageID);
WORD RTDFlashSearchPageAddr(BYTE ucPageID);
void RTDFlashInitialAddr(void);
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode);
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode);
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData);

void RTDFlashStartup(void);
void RTDFlashWholeRestore(void);
void RTDFlashRestoreBacklight(void);
void RTDFlashLoadOSDData(void);
void RTDFlashSaveOSDData(void);
void RTDFlashRestoreOSDData(void);
void RTDFlashLoadBriCon(BYTE ucSource);
void RTDFlashSaveBriCon(BYTE ucSource);
void RTDFlashRestoreBriCon(void);
void RTDFlashLoadColorSetting(BYTE ucColorTempType);
void RTDFlashSaveColorSetting(BYTE ucColorTempType);
void RTDFlashRestoreColorSetting(void);
void RTDFlashRestoreUserColorSetting(void);
void RTDFlashLoadSixColorData(void);
void RTDFlashSaveSixColorData(void);
void RTDFlashRestoreSixColorData(void);
void RTDFlashLoadPanelUsedTimeData(void);
void RTDFlashSavePanelUsedTimeData(void);
void RTDFlashRestorePanelUsedTimeData(void);
#if(_PANEL_EXIST_MULTIPANEL == _ON)
void RTDFlashLoadPanelIndex(void);
void RTDFlashSavePanelIndex(void);
void RTDFlashRestorePanelIndex(void);
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromStartup(void)
{
    BYTE ucCnt = 0;

    // Check twice if VERSION CODE matches
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        pData[0] = _CHECKSUM ^ 0xFF;
        pData[1] = _VERSION_CODE ^ 0xFF;
        UserCommonEepromRead(_EEPROM_CHECKSUM_ADDRESS, 2, pData);
		
		if(!ucCnt)
		{
			printf("_CHECKSUM:%X pData[0]:%X\n\r",(int)_CHECKSUM,(int)pData[0]);	
			printf("_VERSION_CODE:%X pData[1]:%X\n\r",(int)_VERSION_CODE,(int)pData[1]);	
		}
		
        if((pData[0] == _CHECKSUM) && (pData[1] == _VERSION_CODE))
        {
            break;
        }
    }

    if(pData[0] != _CHECKSUM)	//  Reset All
    {
        BYTE pucData[3] = {0};

        // Load default value and save to EEPROM
        RTDEepromWholeRestore();
		printf("CHECKSUM Not Equal => RTDEepromWholeRestore() All Data\n\r");	
		
        // Save VERSION CODE to EEPROM
        pucData[0] = _CHECKSUM;
        pucData[1] = _VERSION_CODE;
        pucData[2] = 0; // _PANEL_INDEX_ADDRESS

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        SET_MDOMAIN_PANEL_INDEX(0);
#endif

        UserCommonEepromWrite(_EEPROM_CHECKSUM_ADDRESS, 2, pucData);
        UserCommonEepromWrite(_PANEL_INDEX_ADDRESS, 1, &pucData[2]);

		//------------------------------------------------------------------------------
        UserCommonFlashSaveCustomerUserData();
    }
    else if(pData[1] != _VERSION_CODE)
    {
		printf("_VERSION_CODE Not Equal => User OSD, Color ...\n\r");	
		
        //g_stColorProcData = tColorTempDefaultData[_CT_USER];
        //RTDEepromSaveColorSetting(_CT_USER);
		RTDEepromRestoreColorSetting();	
		
        UserCommonEepromRestoreSystemData();
        RTDEepromRestoreOSDData();
		RTDEepromLoadOsdServiceData();	

#if(_VGA_SUPPORT == _ON)
        UserCommonEepromRestoreModeUserData();
#endif

        RTDEepromRestoreBriCon();
        RTDEepromRestoreSixColorData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        pData[1] = _VERSION_CODE;
        UserCommonEepromWrite(_EEPROM_VERSION_CODE_ADDRESS, 1, &pData[1]);
    }
    else
    {
		printf("RTDEepromLoad All Data \n\r");	
		
        UserCommonEepromLoadSystemData();
        RTDEepromLoadOSDData();
		RTDEepromLoadOsdServiceData();	
        RTDEepromLoadSixColorData();
        RTDEepromLoadPanelUsedTimeData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        UserCommonEepromRead(_PANEL_INDEX_ADDRESS, 1, pData);
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS() > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            RTDEepromSaveOSDData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDEepromSaveOSDData();
        }
#endif
    }

    // SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
    /*
    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    */

    RTDEepromLoadColorSetting(GET_COLOR_TEMP_TYPE());
}

//--------------------------------------------------
// Description  : Load default data and save to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromWholeRestore(void)
{
    UserCommonEepromRestoreSystemData();
    RTDEepromRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonEepromRestoreModeUserData();
    UserCommonEepromRestoreADCSetting();
#endif

    RTDEepromRestoreBriCon();

    RTDEepromRestoreColorSetting();	
    //RTDEepromRestoreUserColorSetting();

    RTDEepromRestoreSixColorData();
    RTDEepromRestorePanelUsedTimeData();

	//--------------------------------------
	// Osd service data
    RTDEepromRestoreOsdServiceData();	
	//--------------------------------------
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBacklight(void)
{
    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight);
    RTDEepromSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOSDData(void)
{
    UserCommonEepromRead(_OSD_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOSDUserData));

#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) &&
       (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}

//--------------------------------------------------
// Description  : Save OSD data to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOSDData(void)
{
    UserCommonEepromWrite(_OSD_DATA_ADDRESS, sizeof(StructOsdUserDataType), (BYTE *)(&g_stOSDUserData));
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOSDData(void)
{
    g_stOSDUserData = g_stOSDDefaultData;
    RTDEepromSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD Service from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadOsdServiceData(void)	
{
    UserCommonEepromRead(_OSD_USER_SERVICE_ADDRESS, sizeof(StructOsdServiceDataType), (BYTE *)(&g_stOsdServiceData));
}

//--------------------------------------------------
// Description  : Save OSD Service to EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveOsdServiceData(void)	
{
    UserCommonEepromWrite(_OSD_USER_SERVICE_ADDRESS, sizeof(StructOsdServiceDataType), (BYTE *)(&g_stOsdServiceData));
}
//--------------------------------------------------
// Description  : Restore default OSD Service
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreOsdServiceData(void)	
{
    g_stOsdServiceData = g_stOsdServiceDataDefault;
    RTDEepromSaveOsdServiceData();
}

//--------------------------------------------------
// Description  : Load brightness/contrast from EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadBriCon(BYTE ucSource)
{
    UserCommonEepromRead(_BRICON_DATA_ADDRESS + ucSource * sizeof(StructBriConDataType), sizeof(StructBriConDataType), (BYTE *)(&g_stBriConData));
}

//--------------------------------------------------
// Description  : Save brightness/contrast to EEPROM
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveBriCon(BYTE ucSource)
{
    UserCommonEepromWrite(_BRICON_DATA_ADDRESS + ucSource * sizeof(StructBriConDataType), sizeof(StructBriConDataType), (BYTE *)(&g_stBriConData));
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreBriCon(void)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _SOURCE_AMOUNT; ucTemp++)
    {
        g_stBriConData = tBriConDefaultData[ucTemp];
        RTDEepromSaveBriCon(ucTemp);
    }
}

void RTDEepromBackupColorCon(void)	
{
    BYTE ucTemp = 0;
	
    for(ucTemp = 0; ucTemp < _SOURCE_AMOUNT; ucTemp++)
    {
        RTDEepromLoadBriCon(ucTemp);
		g_stBriConData.usBrightness = tBriConDefaultData[ucTemp].usBrightness;	// Default User Brightness 
		g_stBriConData.usContrast = tBriConDefaultData[ucTemp].usContrast;		// Default User Contrast 
        g_stBackupBriConData[ucTemp] = g_stBriConData;
    }
}

void RTDEepromRecoveryColorCon(void)	
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _SOURCE_AMOUNT; ucTemp++)
    {
        g_stBriConData = g_stBackupBriConData[ucTemp];
        RTDEepromSaveBriCon(ucTemp);
    }
}


void RTDEepromBackupSetId(void)	
{
    ucBackupSetId = GET_OSD_SETID();
}

void RTDEepromRecoverySetId(void)
{
    SET_OSD_SETID(ucBackupSetId);
	RTDEepromSaveOSDData();
}



//--------------------------------------------------
// Description  : Load color settings from EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadColorSetting(BYTE ucColorTempType)
{
#if 0//(_OGC_SUPPORT == _ON)
    if(GET_OSD_GAMMA() != _GAMMA_OFF)
    {
        UserCommonAdjustOGCColorTempGain(ucColorTempType, (GET_OSD_GAMMA() - 1), pData, _OGC_NORMAL_TYPE);

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
#elif(_CTS_TYPE == _CTS_GEN_0_8BIT)
        g_stColorProcData.usColorTempR = pData[0];
        g_stColorProcData.usColorTempG = pData[1];
        g_stColorProcData.usColorTempB = pData[2];
#endif
    }
    else
#endif
    {
        UserCommonEepromRead(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
    }

    /*
    else
    {
        g_stColorProcData.usColorTempR = 0x800;
        g_stColorProcData.usColorTempG = 0x800;
        g_stColorProcData.usColorTempB = 0x800;
    }
    */
}

//--------------------------------------------------
// Description  : Save color settings to EEPROM
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveColorSetting(BYTE ucColorTempType)
{
    // if(ucColorTempType != _CT_OFF)
    {
        UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (ucColorTempType) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&g_stColorProcData.usColorTempR));
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreColorSetting(void)
{
    BYTE ucTemp = 0;
    for (ucTemp = _CT_D56; ucTemp <= _CT_USER; ucTemp++)
    {
        g_stColorProcData = tColorTempDefaultData[ucTemp];
        RTDEepromSaveColorSetting(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp;

    stUserColorTemp = tColorTempDefaultData[_CT_USER];

    UserCommonEepromWrite(_COLORTEMP_DATA_ADDRESS + (_CT_USER) * sizeof(StructColorProcDataType), sizeof(StructColorProcDataType), (BYTE *)(&stUserColorTemp));
}


//--------------------------------------------------
// Description  : Load six color data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadSixColorData(void)
{
    UserCommonEepromRead(_SIXCOLOR_DATA_ADDRESS, sizeof(StructSixColorDataType), (BYTE *)(&g_stSixColorData));
}

//--------------------------------------------------
// Description  : Save six color data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSaveSixColorData(void)
{
    UserCommonEepromWrite(_SIXCOLOR_DATA_ADDRESS, sizeof(StructSixColorDataType), (BYTE *)(&g_stSixColorData));
}

//--------------------------------------------------
// Description  : Restore default six color data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestoreSixColorData(void)
{
    g_stSixColorData = g_stSixColorDefaultData;
    RTDEepromSaveSixColorData();
}

//--------------------------------------------------
// Description  : Load Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromLoadPanelUsedTimeData(void)
{
    UserCommonEepromRead(_PANEL_TIME_DATA_ADDRESS, sizeof(StructTimeType), (BYTE *)(&g_stPanelTimeData));
}

//--------------------------------------------------
// Description  : Save Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromSavePanelUsedTimeData(void)
{
    UserCommonEepromWrite(_PANEL_TIME_DATA_ADDRESS, sizeof(StructTimeType), (BYTE *)(&g_stPanelTimeData));
}

//--------------------------------------------------
// Description  : Restore Panel Used Time Data from EEPROM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDEepromRestorePanelUsedTimeData(void)
{
    SET_PANEL_TIME_HOUR(0);
    SET_PANEL_TIME_MIN(0);
    RTDEepromSavePanelUsedTimeData();
}

    // StructOsdUserDataType stOsdUserData;
    // StructBriConDataType stBriConData;
    // StructBriConDataType stBackupBriConData[_SOURCE_AMOUNT];
    // StructColorProcDataType stColorProcData;
    // StructSixColorDataType stSixColorData;

void UserCommonFlashSaveCustomerUserData(void)
{
    BYTE ucPageIdx = 0;
    BYTE *pucData;
    BYTE ucIndex = 0;
    BYTE ucTotalPageCount;
    WORD usRemainingSize = sizeof(g_stOSDCustomerUserData);
    
    ucTotalPageCount = (CUSTOMER_USERDATA_STRUCT_SIZE + (FLASH_PAGE_SIZE - 1)) / FLASH_PAGE_SIZE;

    g_stOSDCustomerUserData.stOsdUserData = g_stOSDUserData;
    g_stOSDCustomerUserData.stBriConData = g_stBriConData;

	for(ucIndex = 0; ucIndex <= _SOURCE_AMOUNT; ++ucIndex)
	{
		g_stOSDCustomerUserData.stBackupBriConData[ucIndex] = g_stBackupBriConData[ucIndex];
	}

    g_stOSDCustomerUserData.stColorProcData = g_stColorProcData;
    g_stOSDCustomerUserData.stSixColorData = g_stSixColorData;

    DebugMessageMemory("g_stOSDCustomerUserData SIZE ",CUSTOMER_USERDATA_STRUCT_SIZE);
    pucData = (BYTE *)&g_stOSDCustomerUserData;

    if(UserCommonFlashErasePage(CUSTOMER_USERDATA_BANK, CUSTOMER_USERDATA_PAGE_START) == _FALSE)
    {
        return; 
    }

    for(ucPageIdx = 0; ucPageIdx < ucTotalPageCount; ucPageIdx++) 
    {

        WORD usWriteSize = (usRemainingSize >= FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : usRemainingSize;

        if(UserCommonFlashWrite(CUSTOMER_USERDATA_BANK, 
                                (CUSTOMER_USERDATA_PAGE_START + ucPageIdx), 
                                usWriteSize,  
                                (pucData + (ucPageIdx * FLASH_PAGE_SIZE))) == _FALSE)
        {
            break;
        }

        usRemainingSize -= usWriteSize; 
        if(usRemainingSize == 0) break; 
    }

}

void UserCommonFlashCustomerUserData(void)
{
    BYTE ucIndex = 0;
    UserCommonFlashRead(CUSTOMER_USERDATA_BANK, 
                    CUSTOMER_USERDATA_PAGE_START, 
                    CUSTOMER_USERDATA_STRUCT_SIZE, 
                    (BYTE *)&g_stOSDCustomerUserData);
					

    g_stOSDUserData = g_stOSDCustomerUserData.stOsdUserData;
    g_stBriConData = g_stOSDCustomerUserData.stBriConData;

	for(ucIndex = 0; ucIndex <= _SOURCE_AMOUNT; ++ucIndex)
	{
		g_stBackupBriConData[ucIndex] = g_stOSDCustomerUserData.stBackupBriConData[ucIndex];
	}

    g_stColorProcData = g_stOSDCustomerUserData.stColorProcData;
    g_stSixColorData = g_stOSDCustomerUserData.stSixColorData;

}
#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get the free page number of flash
// Input Value  : None
// Output Value : Free page index
//--------------------------------------------------
BYTE RTDFlashGetFreePage(void)
{
    BYTE ucPageID = _START_OF_PAGEID;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    // If the _END_PAGE page has the biggest move count, suppose first page is free page
    if(g_ulFlashMoveCount > 0)
    {
        if(g_ucFlashLastPage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
        {
            ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
        }
        else
        {
            ucFreePage = g_ucFlashLastPage + 1;
        }
    }

    // Check the supposed free page is actual free page which has not been used ever
    do
    {
        if(ucFreePage == g_pucFlashPageArr[ucPageID])
        {
            if(ucFreePage >= _SYSTEM_EEPROM_EMULATION_END_PAGE)
            {
                ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
            }
            else
            {
                ucFreePage += 1;
            }

            ucPageID = _START_OF_PAGEID;
        }
        else
        {
            ucPageID++;
        }
    }
    while(ucPageID <= _END_OF_PAGEID);

    return ucFreePage;
}

//--------------------------------------------------
// Description  : Check the page is vaild or not
// Input Value  : ucPage: The page to be check, must between 0 and (_END_PAGE - _START_PAGE)
// Output Value : _TRUE means the page is valid, _FLASE is invalid
//--------------------------------------------------
bit RTDFlashIsPageInfoValid(BYTE ucPage)
{
    WORD usPageInfoAddr = ucPage * _FLASH_PAGE_SIZE;
    BYTE ucPageInfoChecksum = 0;
    BYTE pucPageInfo[5] = {0};
    BYTE pucPageInfoTemp[4] = {0};

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageInfoAddr + _PAGEINFO_CHECKSUM_ADDR, 5, pucPageInfo);
    pucPageInfoTemp[0] = pucPageInfo[1];
    pucPageInfoTemp[1] = pucPageInfo[2];
    pucPageInfoTemp[2] = pucPageInfo[3];
    pucPageInfoTemp[3] = pucPageInfo[4];
    ucPageInfoChecksum = UserCommonFlashCalculateCheckSumData(pucPageInfoTemp, 4);
    ucPageInfoChecksum = (ucPageInfoChecksum & 0x7F);

    if(ucPageInfoChecksum == pucPageInfo[0])
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial data page
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialDataPage(BYTE ucPageID)
{
    WORD usAddr = _SYSTEM_EEPROM_EMULATION_START_PAGE * _FLASH_PAGE_SIZE;
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucVersionCode = 0;
    BYTE ucChecksum = 0;

    ucFreePage = RTDFlashGetFreePage();
    // Initial page index
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Initial address
    g_pusFlashAddrArr[ucPageID] = 0;
    // Initial move count
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;
    UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID]);

    {
        BYTE pucBuffer[5] = {0};

        pucBuffer[0] = ucPageID;
        pucBuffer[1] = (BYTE)(g_ulFlashMoveCount >> 16);
        pucBuffer[2] = (BYTE)(g_ulFlashMoveCount >> 8);
        pucBuffer[3] = (BYTE)g_ulFlashMoveCount;
        pucBuffer[4] = UserCommonFlashCalculateCheckSumData(pucBuffer, 4);
        pucBuffer[4] = (pucBuffer[4] & 0x7F);

        ucVersionCode = _VERSION_CODE;
        ucChecksum = _CHECKSUM;

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_PAGEID_ADDR, 4, pucBuffer);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + _PAGEINFO_CHECKSUM_ADDR, 1, &pucBuffer[4]);
    }
}

//--------------------------------------------------
// Description  : Search the last saved item address, and next new item position
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD RTDFlashSearchPageAddr(BYTE ucPageID)
{
    WORD usItemAddr = 0;
    WORD usPageAddr = 0;

    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the last data item address
    for(usItemAddr = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usItemAddr > 0; usItemAddr--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + (usItemAddr - 1) * _DATA_ITEM_LENGTH, 1, pData);
        if(pData[0] != 0xFF)
        {
            return usItemAddr;
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  : Flash address initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashInitialAddr(void)
{
    BYTE ucCnt = 0;
    WORD usAddr = 0;
    DWORD ulMoveCount = 0;
    BYTE ucPageID = 0;
    BYTE pucData[4] = {0};
    DWORD ulMoveCountTemp = 0;

    g_ulFlashMoveCount = 0;
    g_ucFlashLastPage = _SYSTEM_EEPROM_EMULATION_START_PAGE;

    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        g_pucFlashPageArr[ucPageID] = 0xFF;
    }

    // Find the page whose move count is the biggest and get the max move count
    for(ucCnt = _SYSTEM_EEPROM_EMULATION_START_PAGE; ucCnt < (_SYSTEM_EEPROM_EMULATION_END_PAGE + 1); ucCnt++)
    {
        // Check the page is valid or not
        if(RTDFlashIsPageInfoValid(ucCnt) == _TRUE)
        {
            usAddr = ucCnt * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR;

            // Get the move count of current page
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 4, pucData);
            ulMoveCount = ((DWORD)(pucData[1]) << 16) | ((DWORD)(pucData[2]) << 8) | ((DWORD)(pucData[3]));

            // Get the max move count and its page index, ulMoveCount Only 3 Bytes, extra Judge 0xFFFFFF < 0x000001 Case
            if(((ulMoveCount >= g_ulFlashMoveCount) && (!((ulMoveCount == 0xFFFFFF) && (g_ulFlashMoveCount == 0x01)))) ||\
               ((ulMoveCount < g_ulFlashMoveCount) && ((ulMoveCount == 0x01) && (g_ulFlashMoveCount == 0xFFFFFF))))
            {
                g_pucFlashPageArr[pucData[0]] = ucCnt;
                g_ulFlashMoveCount = ulMoveCount;
                g_ucFlashLastPage = ucCnt;
            }
            // Check Other vaild page index
            else
            {
                if(g_pucFlashPageArr[pucData[0]] == 0xFF)
                {
                    g_pucFlashPageArr[pucData[0]] = ucCnt;
                }
                else // Check which page have begger Movecount
                {
                    usAddr = g_pucFlashPageArr[pucData[0]] * _FLASH_PAGE_SIZE + _PAGEINFO_MOVECOUNT_ADDR;
                    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr, 3, &pucData[1]);
                    ulMoveCountTemp = (((DWORD)(pucData[1]) << 16) | ((DWORD)(pucData[2]) << 8) | ((DWORD)(pucData[3])));
                    if(((ulMoveCount >= ulMoveCountTemp) && (!((ulMoveCount == 0xFFFFFF) && (ulMoveCountTemp == 0x01)))) ||\
                       ((ulMoveCount < ulMoveCountTemp) && ((ulMoveCount == 0x01) && (ulMoveCountTemp == 0xFFFFFF))))
                    {
                        g_pucFlashPageArr[pucData[0]] = ucCnt;
                    }
                }
            }
        }
    }

    // If this page is missing, intial this single page
    for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
    {
        if(g_pucFlashPageArr[ucPageID] == 0xFF)
        {
            // This function will increase g_ulFlashMovePage,and now g_ucFlashLastPage is the page index which has the biggest move count value
            RTDFlashInitialDataPage(ucPageID);
            RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
        }
        else
        {
            // Initial g_pusFlashAddrArr
            g_pusFlashAddrArr[ucPageID] = RTDFlashSearchPageAddr(ucPageID);
        }
    }
}

//--------------------------------------------------
// Description  : Get the checksum and version code from flash
// Input Value  : pucChecksum: the checksum get from flash
//                pucVersionCode: the version code get from flash
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadChecksumVersioncode(BYTE *pucChecksum, BYTE *pucVersionCode)
{
    // Get the checksum and version code
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, pucChecksum);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, pucVersionCode);
}

//--------------------------------------------------
// Description  : Save the checksum & version code to flash
// Input Value  : ucChecksum, checksum value
//                ucVersionCode, version code value
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveChecksumVersionCode(BYTE ucChecksum, BYTE ucVersionCode)
{
    BYTE ucVersionCodeRead = 0;
    BYTE ucChecksumRead = 0;

    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCodeRead);
    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksumRead);

    // Do not need save checksum or version code
    if((ucVersionCode == ucVersionCodeRead) && (ucChecksum == ucChecksumRead))
    {
        return;
    }
    // Need to save version code and checksum in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save version code in current page
    else if((ucVersionCode != ucVersionCodeRead) && (ucVersionCodeRead == 0xFF) && (ucChecksum == ucChecksumRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
    }
    // Need to save checksum in current page
    else if((ucChecksum != ucChecksumRead) && (ucChecksumRead == 0xFF) && (ucVersionCode == ucVersionCodeRead))
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
    // Need to save checksum and version code to free page
    else
    {
        memset(pData, 0xFF, _DATA_ITEM_LENGTH);
        RTDFlashMoveData(_CHECKSUM_VERSIONCODE_ID, pData);

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersionCode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[_CHECKSUM_VERSIONCODE_ID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }
}

//--------------------------------------------------
// Description  : Move data to another page of flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDFlashMoveData(BYTE ucPageID, BYTE *pucData)
{
    BYTE ucPrevPage = g_pucFlashPageArr[ucPageID];
    BYTE ucFreePage = _SYSTEM_EEPROM_EMULATION_START_PAGE;
    BYTE ucItemIndex = 0;
    WORD usAddrIndex = 0;
    WORD usPageAddr = 0;
    WORD usPrevPageAddr = 0;
    WORD usMovedItemCount = 0;
    WORD usMovedAddrIndex = 0;
    BYTE ucItemID = 0;
    BYTE ucChecksum = 0xFF;
    BYTE ucVersioncode = 0xFF;

    // Load checksum and version code
    if(pucData[0] != 0xFF)
    {
        RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersioncode);
    }

    // Get free page data will move to
    ucFreePage = RTDFlashGetFreePage();

    // First sector erase the free page specified by g_ucFlashFreePage
    if(UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage) == _FALSE)
    {
        return _FALSE;
    }

    // Save the latest data item to the new page if need, when save checksum and version, it is not necessary
    // We do not save the item id at last because page info has not been saved
    if(pucData[0] != 0xFF)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, ucFreePage * _FLASH_PAGE_SIZE + ucItemIndex, _DATA_ITEM_LENGTH, pucData);

        // Clear Buffer
        memset(pucData, 0xFF, _DATA_ITEM_LENGTH);

        // And then load the latest data items which saved in the old full page to the new page from bottom to top
        usMovedItemCount = 1;
    }
    else
    {
        usMovedItemCount = 0;
    }

    // Update ucFlashPage
    g_pucFlashPageArr[ucPageID] = ucFreePage;
    // Update move count value
    if(g_ulFlashMoveCount == 0xFFFFFF)
    {
        g_ulFlashMoveCount = 0x01;
    }
    else
    {
        g_ulFlashMoveCount++;
    }

    g_ucFlashLastPage = ucFreePage;

    usPrevPageAddr = ucPrevPage * _FLASH_PAGE_SIZE;
    usPageAddr = g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE;

    // Find the valid item and move to new free page
    for(usAddrIndex = ((_FLASH_PAGE_SIZE - _PAGE_INFO_LENGTH) / _DATA_ITEM_LENGTH); usAddrIndex > 0; usAddrIndex--)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, 1, &ucItemID);

        if(ucItemID != 0xFF)
        {
            // Check the item has been moved or not by item ID
            for(usMovedAddrIndex = 0; usMovedAddrIndex < usMovedItemCount; usMovedAddrIndex++)
            {
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedAddrIndex * _DATA_ITEM_LENGTH, 1, pData);
                if(pData[0] == ucItemID)
                {
                    break;
                }
            }

            if(usMovedAddrIndex >= usMovedItemCount)
            {
                // The item has not been moved, then check the item is valid or not
                pucData[15] = 0;
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH, _DATA_ITEM_LENGTH - 1, pData);
                pucData[15] = UserCommonFlashCalculateCheckSumData(pData, (_DATA_ITEM_LENGTH - 1));
                pucData[15] = (pucData[15] & 0x7F);

                // Check the checksum
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + usAddrIndex * _DATA_ITEM_LENGTH - 1, 1, pData);
                if(pucData[15] != pData[0])
                {
                    // Checksum check fail, the item is invalid
                    continue;
                }

                // Move the item to new free page
                UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPrevPageAddr + (usAddrIndex - 1) * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);
                UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usPageAddr + usMovedItemCount * _DATA_ITEM_LENGTH + ucItemIndex, _DATA_ITEM_LENGTH, pData);

                usMovedItemCount++;
            }
        }
    }

    // Update the data item address in the new page
    g_pusFlashAddrArr[ucPageID] = usMovedItemCount;

    // Last update the new moved page info fields
    // Save checksum & version code
    if(ucPageID == _CHECKSUM_VERSIONCODE_ID)
    {
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_VERSIONCODE_ADDR, 1, &ucVersioncode);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _FLASH_FW_CHECKSUM_ADDR, 1, &ucChecksum);
    }

    // Save page info
    {
        BYTE pucBuffer[5] = {0};

        pucBuffer[0] = ucPageID;
        pucBuffer[1] = (BYTE)(g_ulFlashMoveCount >> 16);
        pucBuffer[2] = (BYTE)(g_ulFlashMoveCount >> 8);
        pucBuffer[3] = (BYTE)g_ulFlashMoveCount;
        pucBuffer[4] = UserCommonFlashCalculateCheckSumData(pucBuffer, 4);
        pucBuffer[4] = (pucBuffer[4] & 0x7F);

        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_PAGEID_ADDR, 4, pucBuffer);
        UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, g_pucFlashPageArr[ucPageID] * _FLASH_PAGE_SIZE + _PAGEINFO_CHECKSUM_ADDR, 1, &pucBuffer[4]);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Flash check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashStartup(void)
{
    BYTE ucChecksum = 0;
    BYTE ucVersionCode = 0;
    BYTE ucPageID = 0;

    RTDFlashInitialAddr();

    // Get FW checksum and version code
    RTDFlashLoadChecksumVersioncode(&ucChecksum, &ucVersionCode);

    if(ucChecksum != _CHECKSUM)
    {
        // Checksum is changed, load default value and save to flash
        for(ucPageID = _START_OF_PAGEID; ucPageID <= _END_OF_PAGEID; ucPageID++)
        {
            RTDFlashInitialDataPage(ucPageID);
        }

        RTDFlashWholeRestore();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashRestorePanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else if(ucVersionCode != _VERSION_CODE)
    {
        // Restore CT User color setting
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + _CT_USER, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(_CT_USER);
        }

        UserCommonFlashRestoreSystemData();
        RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
        UserCommonFlashRestoreModeUserData();
#endif

        RTDFlashRestoreBriCon();
        RTDFlashRestoreSixColorData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        RTDFlashSaveChecksumVersionCode(_CHECKSUM, _VERSION_CODE);
    }
    else
    {
        UserCommonFlashLoadSystemData();
        RTDFlashLoadOSDData();
        RTDFlashLoadSixColorData();
        RTDFlashLoadPanelUsedTimeData();

#if(_PANEL_EXIST_MULTIPANEL == _ON)
        RTDFlashLoadPanelIndex();
#endif

        // Check PCM Flag
        if(GET_OSD_PCM_STATUS() > _PCM_OSD_AMOUNT)
        {
            SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            RTDFlashSaveOSDData();
        }

#if(_OSD_3D_FUNCTION == _ON)
        if((GET_OSD_3DOSD_STATUS() == _ON) &&
           ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)))
        {
            SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
            RTDFlashSaveOSDData();
        }
#endif
    }

    RTDFlashLoadColorSetting(GET_COLOR_TEMP_TYPE());
}

//--------------------------------------------------
// Description  : Load default data and save to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashWholeRestore(void)
{
    UserCommonFlashRestoreSystemData();
    RTDFlashRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonFlashRestoreModeUserData();
    UserCommonFlashRestoreADCSetting();
#endif

    RTDFlashRestoreBriCon();
    RTDFlashRestoreColorSetting();
    RTDFlashRestoreSixColorData();
    RTDFlashRestorePanelUsedTimeData();
}

//--------------------------------------------------
// Description  : Restore default backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBacklight(void)
{
    BYTE ucItemOffset = 0;

    SET_OSD_BACKLIGHT(g_stOSDDefaultData.usBackLight);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load OSD data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            g_stOSDUserData = g_stOSDDefaultData;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((((BYTE *)(&g_stOSDUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((((BYTE *)(&g_stOSDUserData)) + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, ucStructLen);
            break;
        }
    }

#if(_DP_MST_SUPPORT == _ON)
    if((GET_OSD_DP_MST() != _MST_OFF) && (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
}


//--------------------------------------------------
// Description  : Save OSD data to Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveOSDData(void)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOSDUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), (((BYTE *)(&g_stOSDUserData)) + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Restore default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreOSDData(void)
{
    BYTE ucItemOffset = 0;

    g_stOSDUserData = g_stOSDDefaultData;

    for(ucItemOffset = 0; ucItemOffset < ((sizeof(StructOsdUserDataType) + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_OSD_DATA_END - _FLASH_ITEMID_OSD_DATA_START + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_OSD_DATA_START + ucItemOffset), pData, 1) == _FALSE)
        {
            return;
        }
    }

    RTDFlashSaveOSDData();
}

//--------------------------------------------------
// Description  : Load brightness/contrast from Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadBriCon(BYTE ucSource)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSource, pData, sizeof(StructBriConDataType)) == _TRUE)
    {
        memcpy(&g_stBriConData, pData, sizeof(StructBriConDataType));
    }
    else
    {
        g_stBriConData = tBriConDefaultData[ucSource];
    }
}

//--------------------------------------------------
// Description  : Save brightness/contrast to Flash
// Input Value  : ucSource --> Source Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveBriCon(BYTE ucSource)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSource, (BYTE *)(&g_stBriConData), sizeof(StructBriConDataType));
}

//--------------------------------------------------
// Description  : Restore default brightness/contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreBriCon(void)
{
    BYTE ucSourceIndex = 0;

    for(ucSourceIndex = 0; ucSourceIndex < _SOURCE_AMOUNT; ucSourceIndex++)
    {
        g_stBriConData = tBriConDefaultData[ucSourceIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_BRICON_SRC0_VGA + ucSourceIndex, pData, 1) == _TRUE)
        {
            RTDFlashSaveBriCon(ucSourceIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Load color settings from Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadColorSetting(BYTE ucColorTempType)
{
#if(_OGC_SUPPORT == _ON)
    if(GET_OSD_GAMMA() != _GAMMA_OFF)
    {
        UserCommonAdjustOGCColorTempGain(ucColorTempType, (GET_OSD_GAMMA() - 1), pData, _OGC_NORMAL_TYPE);

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
        g_stColorProcData.usColorTempR = PDATA_WORD(0);
        g_stColorProcData.usColorTempG = PDATA_WORD(1);
        g_stColorProcData.usColorTempB = PDATA_WORD(2);
#elif(_CTS_TYPE == _CTS_GEN_0_8BIT)
        g_stColorProcData.usColorTempR = pData[0];
        g_stColorProcData.usColorTempG = pData[1];
        g_stColorProcData.usColorTempB = pData[2];
#endif
    }
    else
#endif
    {
        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, pData, sizeof(StructColorProcDataType)) == _TRUE)
        {
            memcpy(&g_stColorProcData, pData, sizeof(StructColorProcDataType));
        }
        else
        {
            g_stColorProcData = tColorTempDefaultData[ucColorTempType];
        }
    }
}


//--------------------------------------------------
// Description  : Save color settings to Flash
// Input Value  : ucSource --> Source Type
//                ucColorTempType --> Color Temp Type
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveColorSetting(BYTE ucColorTempType)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempType, (BYTE *)(&g_stColorProcData), sizeof(StructColorProcDataType));
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreColorSetting(void)
{
    BYTE ucColorTempIndex = 0;

    for(ucColorTempIndex = 0; ucColorTempIndex < _CT_COLORTEMP_AMOUNT; ucColorTempIndex++)
    {
        g_stColorProcData = tColorTempDefaultData[ucColorTempIndex];

        if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC0_9300 + ucColorTempIndex, pData, 1) == _TRUE)
        {
            RTDFlashSaveColorSetting(ucColorTempIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Restore default color settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreUserColorSetting(void)
{
    StructColorProcDataType stUserColorTemp = {0};

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_COLORPROC5_USER, pData, 1) == _TRUE)
    {
        stUserColorTemp = g_stColorProcData;
        g_stColorProcData = tColorTempDefaultData[_CT_USER];
        RTDFlashSaveColorSetting(_CT_USER);
        g_stColorProcData = stUserColorTemp;
    }
}

//--------------------------------------------------
// Description  : Load six color data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadSixColorData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SIXCOLOR_DATA, pData, sizeof(StructSixColorDataType)) == _TRUE)
    {
        memcpy((BYTE *)(&g_stSixColorData), pData, sizeof(StructSixColorDataType));
    }
    else
    {
        g_stSixColorData = g_stSixColorDefaultData;
    }
}

//--------------------------------------------------
// Description  : Save six color data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSaveSixColorData(void)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_SIXCOLOR_DATA, (BYTE *)(&g_stSixColorData), sizeof(StructSixColorDataType));
}

//--------------------------------------------------
// Description  : Restore default six color data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestoreSixColorData(void)
{
    g_stSixColorData = g_stSixColorDefaultData;

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_SIXCOLOR_DATA, pData, 1) == _TRUE)
    {
        RTDFlashSaveSixColorData();
    }
}

//--------------------------------------------------
// Description  : Load Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelUsedTimeData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_DATA, pData, sizeof(StructTimeType)) == _TRUE)
    {
        memcpy((BYTE *)(&g_stPanelTimeData), pData, sizeof(StructTimeType));
    }
    else
    {
        SET_PANEL_TIME_HOUR(0);
        SET_PANEL_TIME_MIN(0);
    }
}

//--------------------------------------------------
// Description  : Save Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelUsedTimeData(void)
{
    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_DATA, (BYTE *)(&g_stPanelTimeData), sizeof(StructTimeType));
}

//--------------------------------------------------
// Description  : Restore Panel Used Time Data from Flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelUsedTimeData(void)
{
    SET_PANEL_TIME_HOUR(0);
    SET_PANEL_TIME_MIN(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_DATA, pData, 1) == _TRUE)
    {
        RTDFlashSavePanelUsedTimeData();
    }
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Load panel index from flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashLoadPanelIndex(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        SET_MDOMAIN_PANEL_INDEX(pData[0]);
    }
    else
    {
        SET_MDOMAIN_PANEL_INDEX(0);
    }
}

//--------------------------------------------------
// Description  : Save panel index to flash
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashSavePanelIndex(void)
{
    BYTE ucPanelIndex = 0;

    ucPanelIndex = GET_MDOMAIN_PANEL_INDEX();

    UserCommonFlashSaveItem(_FLASH_ITEMID_PANEL_INDEX, &ucPanelIndex, 1);
}

//--------------------------------------------------
// Description  : Restore panel index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFlashRestorePanelIndex(void)
{
    SET_MDOMAIN_PANEL_INDEX(0);

    if(UserCommonFlashLoadItem(_FLASH_ITEMID_PANEL_INDEX, pData, 1) == _TRUE)
    {
        RTDFlashSavePanelIndex();
    }
}
#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _ON)

#endif // End of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

#endif // #if(_OSD_TYPE == _REALTEK_2014_OSD)
