/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerAudioInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#define _INITIAL_I_CODE                             0x0040
#define _STABLE_I_CODE                              0x0002

#define _AUDIO_DYNAMIC_I_CODE_TIMER_MS              100 // Unit: ms

#define _DVC_VOLUME_ADJUST_TIMER                    20 // ms

#define _DVC_DB_STEP_NUMBER                         64
#define _DVC_ZCD_TIMEOUT_DEFAULT                    (0x0030 & 0x0FFF) // 48KHz, Fcut = 500Hz

#define _AUTO_FREQ_DETECT_XTAL_DIV                  (BYTE)(((((WORD) _GDI_CLK_KHZ << 1) / 160) + 1) >> 1)

#define _AUDIO_PLL_K                                2
#define _AUDIO_PLL_M                                (BYTE)((((DWORD) _AUDIO_PLL_VCO * _AUDIO_PLL_K * 2 / _GDI_CLK_KHZ) + 1) / 2)

#define _ZCD_TIMEOUT_DEFAULT                        0x1F

#define _AUDIO_TEST_1K_S_CODE                       0x2E
#define _AUDIO_TEST_1K_D_CODE                       0xE3D8

#define _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE        0xB0
#define _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE        0xA0
#define _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE        0xA0

#define _DP_SAMPLING_FREQ_32K_GROUP_S_CODE          (0x30 & 0x7F)
#define _DP_SAMPLING_FREQ_44K_GROUP_S_CODE          (0x20 & 0x7F)
#define _DP_SAMPLING_FREQ_48K_GROUP_S_CODE          (0x20 & 0x7F)

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#define _AUDIO_FW_TRCK_FIRST_STABLE_CNT             0x20
#define _AUDIO_WL_GOES_UP                           2
#define _AUDIO_WL_GOES_DOWN                         1
#define _AUDIO_WL_GOES_UNKNOWN                      0
#define _AUDIO_FW_TRCK_PREPARING_CHECK              30
#define _AUDIO_FW_TRCK_PLAYBACK_CHECK               20
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#define GET_AUDIO_DAC_STATE()                       (g_stAudioDACInfo.b3AudioDACState)
#define SET_AUDIO_DAC_STATE(x)                      (g_stAudioDACInfo.b3AudioDACState = (x))

#define GET_AUDIO_DAC_STATE_CHANGE()                (bit)(g_stAudioDACInfo.b1AudioDACStateChange)
#define SET_AUDIO_DAC_STATE_CHANGE()                (g_stAudioDACInfo.b1AudioDACStateChange = _TRUE)
#define CLR_AUDIO_DAC_STATE_CHANGE()                (g_stAudioDACInfo.b1AudioDACStateChange = _FALSE)
#endif

#define GET_AUDIO_DVC_MUTE_CTRL_STATUS()            (g_bAudioDVCMuteCtrlStatus)
#define SET_AUDIO_DVC_MUTE_CTRL_STATUS(x)           (g_bAudioDVCMuteCtrlStatus = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_EMBEDDED_DAC_SUPPORT == _ON)
typedef struct
{
    BYTE b3AudioDACState : 3;
    BYTE b1AudioDACStateChange : 1;
} StructAudioDACInfo;
#endif

typedef struct
{
    BYTE b4AudioSamplingFreq : 4;
    BYTE b1AudioDetected : 1;
    BYTE b1AudioICodeReloaded : 1;
    BYTE b2AudioDigitalSource : 2;
    BYTE b1AudioCurrentMAC : 1;
} StructAudioDigitalInfo;

typedef struct
{
    BYTE ucAudioFs;
    BYTE b1AutoLoad : 1;
} StructAudioFreqParameter;

typedef struct
{
    EnumAudioCodingType enumAudioCodingType;
    BYTE b1AudioCodingTypeChange : 1;
} StructAudioDpCodingType;

typedef enum
{
    _AUDIO_TRACKING_AUTO_LOAD_MODE = 0,
    _AUDIO_TRACKING_MANNUAL_MODE = 1,
} EnumAudioFreqTrackingMode;

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
typedef struct
{
    BYTE b2AudioFwTrackState : 2;
    BYTE b1AudioFwTrackEventStatus : 1;
    BYTE b1AudioFwTrackReset : 1;
    BYTE b1AudioFwTrackTimeoutEvent : 1;
    BYTE b2AudioWaterLevelTargetDirection : 2;
    BYTE b1AudioFwTrackStable : 1;
    BYTE ucAfifoBackup;
    BYTE ucAfifoTrackStableCnt;
    BYTE ucAudioFreqRecord;
} StructAudioFwTrackingInfo;

typedef enum
{
    _AUDIO_FW_TRACKING_INITIAL,
    _AUDIO_FW_TRACKING_PROCESS_PREPARING,
    _AUDIO_FW_TRACKING_PROCESS_PLAYBACK,
} EnumAudioFwTrackingState;
#endif

//--------------------------------------------------
// Enumerations of Audio DAC Output Gain
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUTPUT_GAIN_0_DB = 0x00,
    _AUDIO_DAC_OUTPUT_GAIN_1_5_DB = 0x01,
    _AUDIO_DAC_OUTPUT_GAIN_3_DB = 0x02,
    _AUDIO_DAC_OUTPUT_GAIN_4_5_DB = 0x03,
    _AUDIO_DAC_OUTPUT_GAIN_6_DB = 0x04,
    _AUDIO_DAC_OUTPUT_GAIN_7_5_DB = 0x05,
    _AUDIO_DAC_OUTPUT_GAIN_9_DB = 0x06,
    _AUDIO_DAC_OUTPUT_GAIN_10_5_DB = 0x07,
} EnumAudioDacOutputGain;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern StructAudioDACInfo g_stAudioDACInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerAudioMuteProc(bit bMute, WORD usVolume);
extern void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume);
extern void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput);
extern BYTE ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput);
extern EnumAudioSamplingFreqPacket ScalerAudioGetSamplingFreqPacket(EnumAudioSamplingFreqType enumSamplingFreqType);
extern WORD ScalerAudioGetUserSamplingFreqDCode(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern BYTE ScalerAudioGetUserSamplingFreqSCode(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern WORD ScalerAudioGetUserSamplingFreqDCode_EXINT0(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern BYTE ScalerAudioGetUserSamplingFreqSCode_EXINT0(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern BYTE ScalerAudioChannelOutputSel(BYTE ucCa);

#if(_LINE_IN_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_NONE)

#if(_DP_SUPPORT == _ON)
extern BYTE ScalerAudioGetDigitalAudioPort_EXINT0(EnumAudioOutputType enumAudioOutput);
#endif

extern EnumAudioInputSource ScalerAudioGetInputSource_EXINT0(void);
#endif

extern EnumAudioInputSource ScalerAudioGetInputSource(void);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern void ScalerAudioDACSetState(EnumAudioDACState enumTargetState);
extern void ScalerAudioDACSetVcmReady(bit bReady);
extern void ScalerAudioDACNormalToDepop(void);
extern void ScalerAudioDACDepopToNormal(void);
extern void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain);
#endif

extern void ScalerAudioDVCResetProc(void);

#endif // End of #if(_AUDIO_SUPPORT == _ON)
