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
// ID Code      : RL6449_Series_AudioInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
#define GET_AUDIO_D0_ICODE_RELOADED()               (bit)(g_stAudioD0DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D0_ICODE_RELOADED()               (g_stAudioD0DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D0_ICODE_RELOADED()               (g_stAudioD0DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D0_SAMPLING_FREQ()                (g_stAudioD0DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D0_SAMPLING_FREQ(x)               (g_stAudioD0DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D0_PACKET_DETECT()                (bit)(g_stAudioD0DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D0_PACKET_DETECT()                (g_stAudioD0DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D0_PACKET_DETECT()                (g_stAudioD0DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D0_DIGITAL_AUDIO_SOURCE()               (g_stAudioD0DigtalInfo.b2AudioDigitalSource)
#define SET_D0_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD0DigtalInfo.b2AudioDigitalSource = (x))

#define GET_AUDIO_D0_AUTO_LOAD_FREQ()               (g_stAudioD0FreqParameter.b1AutoLoad)
#define SET_AUDIO_D0_AUTO_LOAD_FREQ()               (g_stAudioD0FreqParameter.b1AutoLoad = _TRUE)
#define CLR_AUDIO_D0_AUTO_LOAD_FREQ()               (g_stAudioD0FreqParameter.b1AutoLoad = _FALSE)

#define GET_D0_SAMPLING_FREQ_USER_DEFINE()          (g_stAudioD0FreqParameter.ucAudioFs)
#define SET_D0_SAMPLING_FREQ_USER_DEFINE(x)         (g_stAudioD0FreqParameter.ucAudioFs = (x))

#define GET_DP_D0_AUDIO_CODING_TYPE_FORMAT()        (g_stDpAudioD0CodingType.enumAudioCodingType)
#define SET_DP_D0_AUDIO_CODING_TYPE_FORMAT(x)       (g_stDpAudioD0CodingType.enumAudioCodingType = (x))

#define GET_DP_D0_AUDIO_CODING_TYPE_CHANGE()        (g_stDpAudioD0CodingType.b1AudioCodingTypeChange)
#define SET_DP_D0_AUDIO_CODING_TYPE_CHANGE()        (g_stDpAudioD0CodingType.b1AudioCodingTypeChange = _TRUE)
#define CLR_DP_D0_AUDIO_CODING_TYPE_CHANGE()        (g_stDpAudioD0CodingType.b1AudioCodingTypeChange = _FALSE)
#endif

#if(_D1_DP_EXIST == _ON)
#define GET_AUDIO_D1_ICODE_RELOADED()               (bit)(g_stAudioD1DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D1_ICODE_RELOADED()               (g_stAudioD1DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D1_ICODE_RELOADED()               (g_stAudioD1DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D1_SAMPLING_FREQ()                (g_stAudioD1DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D1_SAMPLING_FREQ(x)               (g_stAudioD1DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D1_PACKET_DETECT()                (bit)(g_stAudioD1DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D1_PACKET_DETECT()                (g_stAudioD1DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D1_PACKET_DETECT()                (g_stAudioD1DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D1_DIGITAL_AUDIO_SOURCE()               (g_stAudioD1DigtalInfo.b2AudioDigitalSource)
#define SET_D1_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD1DigtalInfo.b2AudioDigitalSource = (x))

#define GET_AUDIO_D1_AUTO_LOAD_FREQ()               (g_stAudioD1FreqParameter.b1AutoLoad)
#define SET_AUDIO_D1_AUTO_LOAD_FREQ()               (g_stAudioD1FreqParameter.b1AutoLoad = _TRUE)
#define CLR_AUDIO_D1_AUTO_LOAD_FREQ()               (g_stAudioD1FreqParameter.b1AutoLoad = _FALSE)

#define GET_D1_SAMPLING_FREQ_USER_DEFINE()          (g_stAudioD1FreqParameter.ucAudioFs)
#define SET_D1_SAMPLING_FREQ_USER_DEFINE(x)         (g_stAudioD1FreqParameter.ucAudioFs = (x))

#define GET_DP_D1_AUDIO_CODING_TYPE_FORMAT()        (g_stDpAudioD1CodingType.enumAudioCodingType)
#define SET_DP_D1_AUDIO_CODING_TYPE_FORMAT(x)       (g_stDpAudioD1CodingType.enumAudioCodingType = (x))

#define GET_DP_D1_AUDIO_CODING_TYPE_CHANGE()        (g_stDpAudioD1CodingType.b1AudioCodingTypeChange)
#define SET_DP_D1_AUDIO_CODING_TYPE_CHANGE()        (g_stDpAudioD1CodingType.b1AudioCodingTypeChange = _TRUE)
#define CLR_DP_D1_AUDIO_CODING_TYPE_CHANGE()        (g_stDpAudioD1CodingType.b1AudioCodingTypeChange = _FALSE)
#endif

#if(_D2_HDMI_SUPPORT == _ON)
#define GET_AUDIO_D2_ICODE_RELOADED()               (bit)(g_stAudioD2DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D2_ICODE_RELOADED()               (g_stAudioD2DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D2_ICODE_RELOADED()               (g_stAudioD2DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D2_SAMPLING_FREQ()                (g_stAudioD2DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D2_SAMPLING_FREQ(x)               (g_stAudioD2DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D2_PACKET_DETECT()                (bit)(g_stAudioD2DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D2_PACKET_DETECT()                (g_stAudioD2DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D2_PACKET_DETECT()                (g_stAudioD2DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D2_DIGITAL_AUDIO_SOURCE()               (g_stAudioD2DigtalInfo.b2AudioDigitalSource)
#define SET_D2_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD2DigtalInfo.b2AudioDigitalSource = (x))

#define GET_AUDIO_D2_AUTO_LOAD_FREQ()               (g_stAudioD2FreqParameter.b1AutoLoad)
#define SET_AUDIO_D2_AUTO_LOAD_FREQ()               (g_stAudioD2FreqParameter.b1AutoLoad = _TRUE)
#define CLR_AUDIO_D2_AUTO_LOAD_FREQ()               (g_stAudioD2FreqParameter.b1AutoLoad = _FALSE)

#define GET_D2_SAMPLING_FREQ_USER_DEFINE()          (g_stAudioD2FreqParameter.ucAudioFs)
#define SET_D2_SAMPLING_FREQ_USER_DEFINE(x)         (g_stAudioD2FreqParameter.ucAudioFs = (x))

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#define GET_AUDIO_D2_FW_TRACKING_STATE()            (g_stHDMID2AudioFwTrackingInfo.b2AudioFwTrackState)
#define SET_AUDIO_D2_FW_TRACKING_STATE(x)           (g_stHDMID2AudioFwTrackingInfo.b2AudioFwTrackState = (x))

#define GET_AUDIO_D2_FW_TRACKING_EVENT()            (bit)(g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackEventStatus)
#define SET_AUDIO_D2_FW_TRACKING_EVENT()            (g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackEventStatus = _TRUE)
#define CLR_AUDIO_D2_FW_TRACKING_EVENT()            (g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackEventStatus = _FALSE)

#define GET_AUDIO_D2_FW_TRACKING_TIMEOUT()          (bit)(g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackTimeoutEvent)
#define SET_AUDIO_D2_FW_TRACKING_TIMEOUT()          (g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackTimeoutEvent = _TRUE)
#define CLR_AUDIO_D2_FW_TRACKING_TIMEOUT()          (g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackTimeoutEvent = _FALSE)

#define GET_AUDIO_D2_FW_TRACKING_RESET()            (bit)(g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackReset)
#define SET_AUDIO_D2_FW_TRACKING_RESET()            (g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackReset = _TRUE)
#define CLR_AUDIO_D2_FW_TRACKING_RESET()            (g_stHDMID2AudioFwTrackingInfo.b1AudioFwTrackReset = _FALSE)

#define GET_AUDIO_D2_WL_TARGET_DIRECTION()          (g_stHDMID2AudioFwTrackingInfo.b2AudioWaterLevelTargetDirection)
#define SET_AUDIO_D2_WL_TARGET_DIRECTION(x)         (g_stHDMID2AudioFwTrackingInfo.b2AudioWaterLevelTargetDirection = (x))
#define CLR_AUDIO_D2_WL_TARGET_DIRECTION()          (g_stHDMID2AudioFwTrackingInfo.b2AudioWaterLevelTargetDirection = _AUDIO_WL_GOES_UNKNOWN)
#endif
#endif

#if(_D3_HDMI_SUPPORT == _ON)
#define GET_AUDIO_D3_ICODE_RELOADED()               (bit)(g_stAudioD3DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D3_ICODE_RELOADED()               (g_stAudioD3DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D3_ICODE_RELOADED()               (g_stAudioD3DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D3_SAMPLING_FREQ()                (g_stAudioD3DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D3_SAMPLING_FREQ(x)               (g_stAudioD3DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D3_PACKET_DETECT()                (bit)(g_stAudioD3DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D3_PACKET_DETECT()                (g_stAudioD3DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D3_PACKET_DETECT()                (g_stAudioD3DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D3_DIGITAL_AUDIO_SOURCE()               (g_stAudioD3DigtalInfo.b2AudioDigitalSource)
#define SET_D3_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD3DigtalInfo.b2AudioDigitalSource = (x))

#define GET_AUDIO_D3_AUTO_LOAD_FREQ()               (g_stAudioD3FreqParameter.b1AutoLoad)
#define SET_AUDIO_D3_AUTO_LOAD_FREQ()               (g_stAudioD3FreqParameter.b1AutoLoad = _TRUE)
#define CLR_AUDIO_D3_AUTO_LOAD_FREQ()               (g_stAudioD3FreqParameter.b1AutoLoad = _FALSE)

#define GET_D3_SAMPLING_FREQ_USER_DEFINE()          (g_stAudioD3FreqParameter.ucAudioFs)
#define SET_D3_SAMPLING_FREQ_USER_DEFINE(x)         (g_stAudioD3FreqParameter.ucAudioFs = (x))

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#define GET_AUDIO_D3_FW_TRACKING_STATE()            (g_stHDMID3AudioFwTrackingInfo.b2AudioFwTrackState)
#define SET_AUDIO_D3_FW_TRACKING_STATE(x)           (g_stHDMID3AudioFwTrackingInfo.b2AudioFwTrackState = (x))

#define GET_AUDIO_D3_FW_TRACKING_EVENT()            (bit)(g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackEventStatus)
#define SET_AUDIO_D3_FW_TRACKING_EVENT()            (g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackEventStatus = _TRUE)
#define CLR_AUDIO_D3_FW_TRACKING_EVENT()            (g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackEventStatus = _FALSE)

#define GET_AUDIO_D3_FW_TRACKING_TIMEOUT()          (bit)(g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackTimeoutEvent)
#define SET_AUDIO_D3_FW_TRACKING_TIMEOUT()          (g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackTimeoutEvent = _TRUE)
#define CLR_AUDIO_D3_FW_TRACKING_TIMEOUT()          (g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackTimeoutEvent = _FALSE)

#define GET_AUDIO_D3_FW_TRACKING_RESET()            (bit)(g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackReset)
#define SET_AUDIO_D3_FW_TRACKING_RESET()            (g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackReset = _TRUE)
#define CLR_AUDIO_D3_FW_TRACKING_RESET()            (g_stHDMID3AudioFwTrackingInfo.b1AudioFwTrackReset = _FALSE)

#define GET_AUDIO_D3_WL_TARGET_DIRECTION()          (g_stHDMID3AudioFwTrackingInfo.b2AudioWaterLevelTargetDirection)
#define SET_AUDIO_D3_WL_TARGET_DIRECTION(x)         (g_stHDMID3AudioFwTrackingInfo.b2AudioWaterLevelTargetDirection = (x))
#define CLR_AUDIO_D3_WL_TARGET_DIRECTION()          (g_stHDMID3AudioFwTrackingInfo.b2AudioWaterLevelTargetDirection = _AUDIO_WL_GOES_UNKNOWN)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
extern StructAudioDigitalInfo g_stAudioD0DigtalInfo;
extern StructAudioFreqParameter g_stAudioD0FreqParameter;
extern StructAudioDpCodingType g_stDpAudioD0CodingType;
#endif

#if(_D1_DP_EXIST == _ON)
extern StructAudioDigitalInfo g_stAudioD1DigtalInfo;
extern StructAudioFreqParameter g_stAudioD1FreqParameter;
extern StructAudioDpCodingType g_stDpAudioD1CodingType;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
extern StructAudioDigitalInfo g_stAudioD2DigtalInfo;
extern StructAudioFreqParameter g_stAudioD2FreqParameter;

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern StructAudioFwTrackingInfo g_stHDMID2AudioFwTrackingInfo;
#endif
#endif

#if(_D3_HDMI_SUPPORT == _ON)
extern StructAudioDigitalInfo g_stAudioD3DigtalInfo;
extern StructAudioFreqParameter g_stAudioD3FreqParameter;

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern StructAudioFwTrackingInfo g_stHDMID3AudioFwTrackingInfo;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerAudioDigitalAudioInitial(void);
extern void ScalerAudioDisableAudioPLL(void);
extern void ScalerAudioDigitalReset(BYTE ucInputPort);
extern EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort);
extern void ScalerAudioDigitalOutputMute(bit bMute);
extern void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID);
extern void ScalerAudioHdmiI2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput, BYTE ucInputPort);
extern EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void);

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioFwTrackingEventSet(EnumScalerTimerEventID enumEventID);
extern void ScalerAudioTimeoutEventSet(EnumScalerTimerEventID enumEventID);
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_D2_HDMI_SUPPORT == _ON)
extern EnumAudioSamplingFreqType ScalerAudioD2SamplingFreqDetect(void);
#endif
#endif

#if(_DP_SUPPORT == _ON)

#if(_D0_DP_EXIST == _ON)
extern void ScalerAudioD0SetAudioPLL(void);
#endif

#if(_D1_DP_EXIST == _ON)
extern void ScalerAudioD1SetAudioPLL(void);
#endif
#endif

extern BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort);

#endif // End of #if(_AUDIO_SUPPORT == _ON)
