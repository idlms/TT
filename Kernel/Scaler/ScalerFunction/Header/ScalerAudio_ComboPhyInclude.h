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
// ID Code      : ScalerAudio_ComboPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
extern void ScalerAudioDigitalAudioInitial(void);
extern void ScalerAudioDisableAudioPLL(void);
extern void ScalerAudioDigitalReset(BYTE ucInputPort);
extern void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID);

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioFwTrackingEventSet(EnumScalerTimerEventID enumEventID);
extern void ScalerAudioTimeoutEventSet(EnumScalerTimerEventID enumEventID);
#endif

#if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
extern bit ScalerAudioD0GetAudioDetected(void);
extern EnumAudioSamplingFreqType ScalerAudioD0SamplingFreqDetect(void);
extern void ScalerAudioD0WatchDogProc(bit bOn);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
extern void ScalerAudioD0AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#if(_DP_SUPPORT == _ON)
extern void ScalerAudioD0AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#if(_D1_DP_EXIST == _ON)
extern void ScalerAudioD1AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif // End of #if(_D1_DP_EXIST == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerAudioD0GetInternalAudioGenEnable(void);
extern void ScalerAudioD0InternalAudioGenSwitch(bit bOn);
#endif
#endif

#if(_DP_SUPPORT == _ON)
extern void ScalerAudioD0DPDigitalOutputProc(bit bEnable);
extern void ScalerAudioD0DPSetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
#endif

#if(_HDMI_SUPPORT == _ON)
extern void ScalerAudioD0HdmiI2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioD0FwTrackingEventSet(void);
extern void ScalerAudioD0TimeoutEventSet(void);
#endif
#endif
#endif

