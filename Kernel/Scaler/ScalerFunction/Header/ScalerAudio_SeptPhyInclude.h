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
// ID Code      : ScalerAudio_SeptPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Definition of VCO Frequency of Audio PLL With Frequency Up
//----------------------------------------------------------------------------
#define _AUDIO_PLL_VCO                              378000 // 1KHz,

//----------------------------------------------------------------------------
// Definition of Offset of Audio PLL With Path1 and Frequency Up
//----------------------------------------------------------------------------
#define _HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE        0xD847
#define _HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE        0x2CC8
#define _HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE        0xD847

#define _DP_SAMPLING_FREQ_32K_GROUP_D_CODE          0x29E0
#define _DP_SAMPLING_FREQ_44K_GROUP_D_CODE          0xD334
#define _DP_SAMPLING_FREQ_48K_GROUP_D_CODE          0x29E0

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#if(_DP_SUPPORT == _ON)
extern bit ScalerAudioDPGetMuteProc(BYTE ucInputPort);
extern void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort);
extern void ScalerAudioDpAudioEnable_EXINT0(bit bEnable, BYTE ucInputPort);

#if(_D0_DP_EXIST == _ON)
extern void ScalerAudioD0DPAudioInitial(void);
extern void ScalerAudioD0DPDigitalOutputProc(bit bEnable);
extern void ScalerAudioD0DPSetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
extern void ScalerAudioD0AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
extern void ScalerAudioD0AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif
#endif

#if(_D1_DP_EXIST == _ON)
extern void ScalerAudioD1DPAudioInitial(void);
extern void ScalerAudioD1DPDigitalOutputProc(bit bEnable);
extern void ScalerAudioD1DPSetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
extern void ScalerAudioD1AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
extern void ScalerAudioD1AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif
#endif

#endif

#if(_HDMI_SUPPORT == _ON)

#if((_D1_HDMI_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON))
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD2GetInternalAudioGenEnable(void);
extern void ScalerAudioD2InternalAudioGenSwitch(bit bOn);
#endif
#endif

#if(_D2_HDMI_SUPPORT == _ON)
extern void ScalerAudioD2DigitalDetectProc(void);
extern bit ScalerAudioD2GetAudioDetected(void);
extern void ScalerAudioD2LoadStableICodeEvent(void);
extern void ScalerAudioD2WatchDogProc(bit bOn);
extern void ScalerAudioD2I2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput);
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
extern void ScalerAudioD2AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioD2FwTrackingEventSet(void);
extern void ScalerAudioD2TimeoutEventSet(void);
extern void ScalerAudioD2FwTrackingHandler(void);
extern void ScalerAudioD2FwTrackingReset(void);
#endif
#endif

#if(_D3_HDMI_SUPPORT == _ON)
extern void ScalerAudioD3DigitalDetectProc(void);
extern bit ScalerAudioD3GetAudioDetected(void);
extern void ScalerAudioD3HDMIAudioInitial(void);
extern void ScalerAudioD3LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerAudioD3SamplingFreqDetect(void);
extern void ScalerAudioD3WatchDogProc(bit bOn);
extern void ScalerAudioD3I2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput);
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
extern void ScalerAudioD3AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD3GetInternalAudioGenEnable(void);
extern void ScalerAudioD3InternalAudioGenSwitch(bit bOn);
#endif

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioD3FwTrackingEventSet(void);
extern void ScalerAudioD3TimeoutEventSet(void);
extern void ScalerAudioD3FwTrackingHandler(void);
extern void ScalerAudioD3FwTrackingReset(void);
#endif
#endif

#if(_D4_HDMI_SUPPORT == _ON)
extern void ScalerAudioD4DigitalDetectProc(void);
extern bit ScalerAudioD4GetAudioDetected(void);
extern void ScalerAudioD4HDMIAudioInitial(void);
extern void ScalerAudioD4LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerAudioD4SamplingFreqDetect(void);
extern void ScalerAudioD4WatchDogProc(bit bOn);
extern void ScalerAudioD4I2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput);
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
extern void ScalerAudioD4AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD4GetInternalAudioGenEnable(void);
extern void ScalerAudioD4InternalAudioGenSwitch(bit bOn);
#endif

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioD4FwTrackingEventSet(void);
extern void ScalerAudioD4TimeoutEventSet(void);
extern void ScalerAudioD4FwTrackingHandler(void);
extern void ScalerAudioD4FwTrackingReset(void);
#endif
#endif

#if(_D5_HDMI_SUPPORT == _ON)
extern void ScalerAudioD5DigitalDetectProc(void);
extern bit ScalerAudioD5GetAudioDetected(void);
extern void ScalerAudioD5HDMIAudioInitial(void);
extern void ScalerAudioD5LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerAudioD5SamplingFreqDetect(void);
extern void ScalerAudioD5WatchDogProc(bit bOn);
extern void ScalerAudioD5I2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput);
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
extern void ScalerAudioD5AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD5GetInternalAudioGenEnable(void);
extern void ScalerAudioD5InternalAudioGenSwitch(bit bOn);
#endif

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioD5FwTrackingEventSet(void);
extern void ScalerAudioD5TimeoutEventSet(void);
extern void ScalerAudioD5FwTrackingHandler(void);
extern void ScalerAudioD5FwTrackingReset(void);
#endif
#endif

#endif

#if(_LINE_IN_SUPPORT == _ON)
extern void ScalerAudioSetADCAudioPLL(void);
#endif

#endif
