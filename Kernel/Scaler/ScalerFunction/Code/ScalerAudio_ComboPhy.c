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
// ID Code      : ScalerAudio_ComboPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
#define GET_HDMI_AUDIO_CHANNEL_ALLOCATION()           (ScalerGetDataPortSingleByte(P2_CD_HDMI_PSAP, 0x18))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
void ScalerAudioDigitalAudioInitial(void);
void ScalerAudioDigitalDetect(void);
void ScalerAudioDigitalEnable(BYTE ucInputPort);
void ScalerAudioDigitalReset(BYTE ucInputPort);
void ScalerAudioDigitalOutputMute(bit bMute);
void ScalerAudioDisableAudioPLL(void);
bit ScalerAudioGetAudioInputPortChanged(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);
void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID);
void ScalerAudioSourceInputSwitch(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);
void ScalerAudioSetUserDefineAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq);
void ScalerAudioSyncUserDefineFrequency(void);

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
void ScalerAudioFwTrackingHandler(void);
void ScalerAudioFwTrackingEventSet(EnumScalerTimerEventID enumEventID);
void ScalerAudioTimeoutEventSet(EnumScalerTimerEventID enumEventID);
#endif

#if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
void ScalerAudioD0DigitalDetectProc(void);
bit ScalerAudioD0GetAudioDetected(void);
void ScalerAudioD0DigitalAudioReset(void);
void ScalerAudioD0LoadInitialICode(void);
void ScalerAudioD0LoadStableICodeEvent(void);
EnumAudioSamplingFreqType ScalerAudioD0SamplingFreqDetect(void);
void ScalerAudioD0SetAudioPLL(void);
void ScalerAudioD0WatchDogProc(bit bOn);
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
void ScalerAudioD0AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#if(_DP_SUPPORT == _ON)
void ScalerAudioD0AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#if(_D1_DP_EXIST == _ON)
void ScalerAudioD1AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif // End of #if(_D1_DP_EXIST == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
bit ScalerAudioD0GetInternalAudioGenEnable(void);
void ScalerAudioD0InternalAudioGenSwitch(bit bOn);
#endif
#endif // End of #if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))

#if(_DP_SUPPORT == _ON)
void ScalerAudioD0DPAudioInitial(void);
void ScalerAudioD0DPDigitalOutputProc(bit bEnable);
void ScalerAudioD0DPSetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
void ScalerAudioD0DPSetDVCVolumeAdjustType(bit bAdjustType);
bit ScalerAudioGetDPNormalLinkTrainingStatus(void);
#endif

#if(_HDMI_SUPPORT == _ON)
void ScalerAudioD0HDMIAudioInitial(void);
void ScalerAudioD0HdmiI2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
void ScalerAudioD0FwTrackingHandler(void);
void ScalerAudioD0FwTrackingInitial(void);
void ScalerAudioD0DcodeSettingInitial(void);
void ScalerAudioD0FwPreparingTracking(void);
void ScalerAudioD0FwBoundaryTracking(void);
void ScalerAudioD0FwTrackingReset(void);
void ScalerAudioD0FwTrackingEventSet(void);
void ScalerAudioD0TimeoutEventSet(void);
BYTE ScalerAudioD0FwTrackingTimerEventPeriod(void);
#endif
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial HDMI/DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalAudioInitial(void)
{
    ScalerAudioD0SetAudioPLL();

#if(_HDMI_SUPPORT == _ON)
    ScalerAudioD0HDMIAudioInitial();
#endif

#if(_DP_SUPPORT == _ON)
    ScalerAudioD0DPAudioInitial();
#endif

    CLR_AUDIO_D0_ICODE_RELOADED();

    SET_AUDIO_CURRENT_MAC_TYPE(GET_REG_D0_MAC_SWITCH_TO_HDMI());
}

//--------------------------------------------------
// Description  : Detect digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalDetect(void)
{
    ScalerAudioD0DigitalDetectProc();
}

//--------------------------------------------------
// Description  : Enable Digital Audio Proc
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalEnable(BYTE ucInputPort)
{
    ScalerAudioLPCMDetectEnableProc(ucInputPort);

    ScalerAudioWatchDogProc(_ON, ucInputPort);
}

//--------------------------------------------------
// Description  : Reset Digital Audio Proc
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalReset(BYTE ucInputPort)
{
    ScalerAudioLPCMResetProc(ucInputPort);

    ScalerAudioWatchDogProc(_OFF, ucInputPort);
}

//--------------------------------------------------
// Description  : Switch Digital Audio Output Mute
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalOutputMute(bit bMute)
{
    if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
    {
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_07_PORT_PAGE2_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (((!bMute) == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_08_PORT_PAGE2_HDMI_MAG_L_FINAL, 0x00);
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_09_PORT_PAGE2_HDMI_MAG_R_FINAL, 0x00);
    }
    else
    {
#if(_DP_SUPPORT == _ON)
        ScalerAudioDPDigitalOutputProc(~bMute, _D0_INPUT_PORT);
#endif
    }
}

//--------------------------------------------------
// Description  : Disable Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDisableAudioPLL(void)
{
    // Power Down D0 DPLL
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Get if Digital Audio Port Changed
// Input Value  : ucInputPort
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit ScalerAudioGetAudioInputPortChanged(EnumAudioInputSource enumAudioSource, BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    enumAudioSource = enumAudioSource;

#if(_LINE_IN_SUPPORT == _ON)
    if(enumAudioSource != ScalerAudioGetInputSource())
    {
        return _TRUE;
    }
#endif

#if(_NO_MUTE_LINE_IN_AUDIO_WHILE_SWITCHING_DIGITAL_PORT == _ON)
    if(enumAudioSource == _DIGITAL_AUDIO)
#endif
    {
        if(GET_AUDIO_CURRENT_MAC_TYPE() != GET_REG_D0_MAC_SWITCH_TO_HDMI())
        {
            DebugMessageAudio("Audio MAC Changed", GET_AUDIO_CURRENT_MAC_TYPE());

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))

        case _SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE:

            ScalerAudioD0LoadStableICodeEvent();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Switch audio Input (AIN / DAC)
// Input Value  : bAudioSource
// Output Value : None
//--------------------------------------------------
void ScalerAudioSourceInputSwitch(EnumAudioInputSource enumAudioSource, BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    SET_AUDIO_CURRENT_MAC_TYPE(GET_REG_D0_MAC_SWITCH_TO_HDMI());
    SET_AUDIO_PLL_SOURCE_MUX();

    if(enumAudioSource == _DIGITAL_AUDIO)
    {
        DebugMessageAudio("Switch To Digital Audio", 0);

        // Select DAC Mux to Digital input
        ScalerSetBit(P6_D1_DA_MUTE, ~_BIT3, 0x00);

        ScalerAudioInputPortSwitch(_AUDIO_FROM_D0_PORT);

#if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
        ScalerAudioD0DigitalAudioReset();
#endif

#if(_LINE_IN_SUPPORT == _ON)
#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
        // Set DAC Path
        ScalerSetByte(P6_E0_REG_MUX_ANA_OUT, 0x00);
#endif

#if(_HDMI_SUPPORT == _ON)
        DebugMessageAudio("HDMI Audio -> ON", GET_REG_D0_MAC_SWITCH_TO_HDMI());

        // Enable SDM
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_2D_PORT_PAGE2_HDMI_AAPNR, ~_BIT1, _BIT1);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)
        // Disable Auto Load S Code and D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

        // Set S code for 32kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

        // Set D code for 32kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

        // Set S code for 44.1kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

        // Set D code for 44.1kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

        // Set S code for 48kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code for 48kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

        // Set Double Buffer bit
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Load D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

#else

        // Enable Auto Load S Code and D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, _BIT6);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

        // Enable audio FIFO
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
        DebugMessageAudio("DP Audio -> ON", GET_REG_D0_MAC_SWITCH_TO_HDMI());

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

        // Set S code by FW manual
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

        // S code for 32kHz
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

        // D code for 32kHz
        ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));
        ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

        // S code for 44.1kHz
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

        // D code for 44.1kHz
        ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));
        ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

        // S code for 48kHz
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // D code for 48kHz
        ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
#endif

        // D code Double Buffer
        ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
#else

        // Set S code by HW auto
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);

        // Set D code by HW auto
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, _BIT6);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

        // Enable Audio FSM
        ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);
#endif // End of #if(_DP_SUPPORT == _ON)
#endif

        // Resolve Audio Phase Delay of L/R Channel
        ScalerAudioDVCResetProc();

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Set SOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_SPEAKER, _DIGITAL_DAC_AOUT_GAIN_DB);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Set HPOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_HEADPHONE, _DIGITAL_DAC_HPOUT_GAIN_DB);
#endif
#endif

#if(_AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT == _ON)
        // Set Hard Gain for Digital Audio
        ScalerSetBit(P8_A9_DVC_GAIN_DONE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _DIGITAL_HARD_GAIN_VALUE);
#endif
    }
#if(_LINE_IN_SUPPORT == _ON)
    else if(enumAudioSource == _LINE_IN_AUDIO)
    {
        DebugMessageAudio("Switch To Line in Audio", 0);

#if(_HDMI_SUPPORT == _ON)
        DebugMessageAudio("HDMI Audio -> OFF", GET_REG_D0_MAC_SWITCH_TO_HDMI());

        // Diable Audio Freq Changed INT
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);

        // Disable audio FIFO
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Audio FIFO Tracking
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, ~(_BIT3 | _BIT2), 0x00);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Disable Auto Load S Code and D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, 0x00);

        // Set S code
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Enable double buffer
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Load D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

        // Disable SDM
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_2D_PORT_PAGE2_HDMI_AAPNR, ~_BIT1, 0x00);
#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
        DebugMessageAudio("DP Audio -> OFF", GET_REG_D0_MAC_SWITCH_TO_HDMI());

        // Disable Audio FSM
        ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

        // Disable Boundary Tracking
        ScalerSetBit(PB6_81_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Trend Tracking
        ScalerSetBit(PB6_92_AUD_TRND_0, ~_BIT7, 0x00);

        // Set S code by FW
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

        // S code for 48kHz
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Disable auto load D code
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, 0x00);

        // Set D code
        ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Load D code
        ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
#endif // End of #if(_DP_SUPPORT == _ON)

        // Select DAC Mux to ADC input
        ScalerSetBit(P6_D1_DA_MUTE, ~_BIT3, _BIT3);

        ScalerAudioInputPortSwitch(_AUDIO_FROM_ADC_PORT);

        // Resolve Audio Phase Delay of L/R Channel
        ScalerAudioDVCResetProc();

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Set SOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_SPEAKER, _LINE_IN_DAC_AOUT_GAIN_DB);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Set HPOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_HEADPHONE, _LINE_IN_DAC_HPOUT_GAIN_DB);
#endif
#endif

#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
        // Set A-A Path
        ScalerSetByte(P6_E0_REG_MUX_ANA_OUT, 0xAA);
#endif

#if(_AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT == _ON)
        // Set Hard Gain for Line in Audio
        ScalerSetBit(P8_A9_DVC_GAIN_DONE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_HARD_GAIN_VALUE);
#endif
    }
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio Port
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
void ScalerAudioSetUserDefineAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq)
{
    enumAudioFreq = enumAudioFreq;

#if((_DP_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    SET_D0_SAMPLING_FREQ_USER_DEFINE(enumAudioFreq);
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSyncUserDefineFrequency(void)
{
    if(GET_AUDIO_D0_AUTO_LOAD_FREQ() == _FALSE)
    {
        ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_MANNUAL_MODE);
    }
}

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FW tracking Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioFwTrackingHandler(void)
{
    if((GET_AUDIO_D0_FW_TRACKING_RESET() == _FALSE) && (GET_AUDIO_D0_SAMPLING_FREQ() <= _AUDIO_FREQ_48K))
    {
        // FW Tracking mode active only when fs <= 48kHz
        ScalerAudioD0FwTrackingHandler();
    }
    else // FW Tracking mode reset
    {
        // Audio Tracking Reset
        ScalerAudioD0FwTrackingReset();

        DebugMessageAudio("D0 Audio : FW Tracking End", GET_AUDIO_D0_SAMPLING_FREQ());
    }
}

//--------------------------------------------------
// Description  : Timer Event to FW Tracking Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioFwTrackingEventSet(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_HDMI_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_PREPARING:

            ScalerAudioD0FwTrackingEventSet();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Timer Event to FW Tracking Timeout Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTimeoutEventSet(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_HDMI_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_TIMEOUT:

            ScalerAudioD0TimeoutEventSet();
            break;
#endif

        default:
            break;
    }
}
#endif

#if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Detect D0 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DigitalDetectProc(void)
{
#if(_DP_SUPPORT == _ON)
    if((GET_REG_D0_MAC_SWITCH_TO_HDMI() == _FALSE) &&
       (ScalerAudioGetDPNormalLinkTrainingStatus() == _FALSE))
    {
#if(_LINE_IN_SUPPORT == _ON)
        if((ScalerAudioGetInputSource() == _DIGITAL_AUDIO) &&
           (ScalerGetBit(PB6_81_AUD_BDRY_0, _BIT7) == _BIT7))
#else
        if(ScalerGetBit(PB6_81_AUD_BDRY_0, _BIT7) == _BIT7)
#endif
        {
            // -----------------------------------------
            // Disable Tracking Function
            // -----------------------------------------

            // Disable INT for Auido Sampling Change
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

            // Disable Boundary Tracking Method
            ScalerSetBit(PB6_81_AUD_BDRY_0, ~_BIT7, 0x00);

            // Disable Trend Tracking Method
            ScalerSetBit(PB6_92_AUD_TRND_0, ~_BIT7, 0x00);

            // Reload D code
            ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);

            DebugMessageAudio("D0 Audio Tracking Disable", 0);
        }

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        if(GET_AUDIO_D0_AUTO_LOAD_FREQ() == _TRUE)
        {
            // -----------------------------------------
            // Set User Define Frequency When No Audio
            // -----------------------------------------
            ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_MANNUAL_MODE);

            // Clear Flag
            CLR_AUDIO_D0_AUTO_LOAD_FREQ();

            DebugMessageAudio("Dp Rx0 Audio Mannual Mode", 0);
        }
#endif

        CLR_AUDIO_D0_PACKET_DETECT();
        SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_AUDIO_D0_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE);

            ScalerAudioD0LoadInitialICode();

            CLR_AUDIO_D0_ICODE_RELOADED();
        }

        return;
    }
#endif

    if(ScalerAudioD0SamplingFreqDetect() != 0x00)
    {
#if(_HDMI_SUPPORT == _ON)
        // MAC Switch to HDMI or DP
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
        {
            // Enable Audio output
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_30_PORT_PAGE2_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            if(GET_AUDIO_D0_AUTO_LOAD_FREQ() == _FALSE)
            {
                // Set HW Auto Load Frequency
                ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_AUTO_LOAD_MODE);

                // Set Flag
                SET_AUDIO_D0_AUTO_LOAD_FREQ();

                DebugMessageAudio("HDMI D0 Audio Auto_Load Mode", 0);
            }
#endif
#if(_LINE_IN_SUPPORT == _ON)
            if((ScalerAudioGetInputSource() == _DIGITAL_AUDIO) &&
               (ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, (_BIT3 | _BIT2)) == 0x00))
#else
            if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, (_BIT3 | _BIT2)) == 0x00)
#endif
            {
#if(_DIGITAL_AUDIO_OUTPUT_FIX_I2S_PHASE_DELAY == _ON)
                if(ScalerAudioGetDigitalAudioPort(_AUDIO_I2S_OUT) == _AUDIO_FROM_D0_PORT)
                {
                    // Resolve Audio Phase Delay of L/R Channel
                    ScalerAudioDVCResetProc();
                }
#endif
                // Enable Audio FIFO Tracking
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Set Double Buffer bit
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

                // Clear Audio Freq Changed Flag
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~(_BIT1 | _BIT0), _BIT1);

                // Enable Audio Freq Changed INT
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), _BIT3);

                DebugMessageAudio("D0 Audio Tracking Enable", 0);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
                ScalerGetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_16_PORT_PAGE2_HDMI_FDDR, 1, &(g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup), _NON_AUTOINC);
#endif
            }

            SET_AUDIO_D0_PACKET_DETECT();
            SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_HDMI);
        }
        else
#endif
        {
#if(_DP_SUPPORT == _ON)

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            if(GET_AUDIO_D0_AUTO_LOAD_FREQ() == _FALSE)
            {
                // -----------------------------------------
                // Set HW Auto Load Frequency
                // -----------------------------------------
                ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_AUTO_LOAD_MODE);

                // Set Flag
                SET_AUDIO_D0_AUTO_LOAD_FREQ();

                DebugMessageAudio("Dp Rx0 Audio Auto_Load Mode", 0);
            }
#endif

#if(_LINE_IN_SUPPORT == _ON)
            if((ScalerAudioGetInputSource() == _DIGITAL_AUDIO) &&
               (ScalerGetBit(PB6_81_AUD_BDRY_0, _BIT7) == 0x00))
#else
            if(ScalerGetBit(PB6_81_AUD_BDRY_0, _BIT7) == 0x00)
#endif
            {
#if(_DIGITAL_AUDIO_OUTPUT_FIX_I2S_PHASE_DELAY == _ON)
                if(ScalerAudioGetDigitalAudioPort(_AUDIO_I2S_OUT) == _AUDIO_FROM_D0_PORT)
                {
                    // Resolve Audio Phase Delay of L/R Channel
                    ScalerAudioDVCResetProc();
                }
#endif
                // -----------------------------------------
                // Enable Tracking Function
                // -----------------------------------------

                // Enable Boundary Tracking Method
                ScalerSetBit(PB6_81_AUD_BDRY_0, ~_BIT7, _BIT7);

                // Enable Trend Tracking Method
                ScalerSetBit(PB6_92_AUD_TRND_0, ~_BIT7, _BIT7);

                // Clear Auido Sampling Change Flag
                ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

                // Enable INT for Auido Sampling Change
                ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), _BIT6);

                DebugMessageAudio("D0 Audio Tracking Enable", 0);
            }

            if(ScalerGetBit(PB6_01_DP_VBID, _BIT4) == 0x00)
            {
                SET_AUDIO_D0_PACKET_DETECT();
                SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_DP);

#if(_D0_DP_EXIST == _ON)
                if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    // Set D0 DP Receive Port1 In Sync
                    ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_IN_SYNC);
                }
#endif

#if(_D1_DP_EXIST == _ON)
                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    // Set D1 DP Receive Port1 In Sync
                    ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_IN_SYNC);
                }
#endif
            }
            else
            {
                CLR_AUDIO_D0_PACKET_DETECT();
                SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

#if(_D0_DP_EXIST == _ON)
                if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    // Set DP Receive Port1 Out Of Sync
                    ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
                }
#endif

#if(_D1_DP_EXIST == _ON)
                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
                {
                    // Set DP Receive Port1 Out Of Sync
                    ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
                }
#endif
            }
#else
            CLR_AUDIO_D0_PACKET_DETECT();
            SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);
#endif
        }

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        if(GET_AUDIO_D0_SAMPLING_FREQ() > _AUDIO_FREQ_48K)
#endif
        {
            if(GET_AUDIO_D0_ICODE_RELOADED() == _FALSE)
            {
                ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE);

                SET_AUDIO_D0_ICODE_RELOADED();
            }
        }
    }
    else
    {
#if(_HDMI_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _ON)
        if((ScalerAudioGetInputSource() == _DIGITAL_AUDIO) &&
           (ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, (_BIT3 | _BIT2)) != 0x00))
#else
        if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, (_BIT3 | _BIT2)) != 0x00)
#endif
        {
            // Diable Audio Freq Changed INT
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);

            // Disable Audio FIFO Tracking
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, ~(_BIT3 | _BIT2), 0x00);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

            // Reload D code
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

            DebugMessageAudio("D0 Audio Tracking Disable", 0);
        }

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        if(GET_AUDIO_D0_AUTO_LOAD_FREQ() == _TRUE)
        {
            // Set User Define Frequency When No Audio
            ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_MANNUAL_MODE);

            // CLR PLL Autoload Status Flag
            CLR_AUDIO_D0_AUTO_LOAD_FREQ();

            DebugMessageAudio("HDMI FRL Rx3 Audio Mannual Mode", 0);
        }
#endif
#endif

#if(_DP_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _ON)
        if((ScalerAudioGetInputSource() == _DIGITAL_AUDIO) &&
           (ScalerGetBit(PB6_81_AUD_BDRY_0, _BIT7) == _BIT7))
#else
        if(ScalerGetBit(PB6_81_AUD_BDRY_0, _BIT7) == _BIT7)
#endif
        {
            // Disable INT for Auido Sampling Change
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

            // Disable Boundary Tracking Method
            ScalerSetBit(PB6_81_AUD_BDRY_0, ~_BIT7, 0x00);

            // Disable Trend Tracking Method
            ScalerSetBit(PB6_92_AUD_TRND_0, ~_BIT7, 0x00);

            // Reload D code
            ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);

            DebugMessageAudio("D0 Audio Tracking Disable", 0);
        }

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        if(GET_AUDIO_D0_AUTO_LOAD_FREQ() == _TRUE)
        {
            // -----------------------------------------
            // Set User Define Frequency When No Audio
            // -----------------------------------------
            ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_MANNUAL_MODE);

            // Clear Flag
            CLR_AUDIO_D0_AUTO_LOAD_FREQ();

            DebugMessageAudio("Dp Rx0 Audio Mannual Mode", 0);
        }
#endif

        if(GET_D0_DIGITAL_AUDIO_SOURCE() == _DIGITAL_AUDIO_SOURCE_DP)
        {
#if(_D0_DP_EXIST == _ON)
            if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
            {
                // Set D0 DP Receive Port1 Out Of Sync
                ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
            }
#endif

#if(_D1_DP_EXIST == _ON)
            if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
            {
                // Set D1 DP Receive Port1 Out Of Sync
                ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
            }
#endif
        }
#endif
        CLR_AUDIO_D0_PACKET_DETECT();
        SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        if(GET_AUDIO_D0_SAMPLING_FREQ() > _AUDIO_FREQ_48K)
#endif
        {
            if(GET_AUDIO_D0_ICODE_RELOADED() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE);

                ScalerAudioD0LoadInitialICode();

                CLR_AUDIO_D0_ICODE_RELOADED();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get D0 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioD0GetAudioDetected(void)
{
    // Check audio packet
    if(GET_AUDIO_D0_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : D0 Audio Packet", 0);
        return _FALSE;
    }

    // Check FW tracking state
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
    if((GET_AUDIO_D0_FW_TRACKING_STATE() != _AUDIO_FW_TRACKING_PROCESS_PLAYBACK) &&
       (GET_AUDIO_D0_SAMPLING_FREQ() <= _AUDIO_FREQ_48K))
    {
        DebugMessageAudio("False : D0 Audio FW Tracking preparing", 0);
        return _FALSE;
    }
#endif

    if(GET_D0_DIGITAL_AUDIO_SOURCE() == _DIGITAL_AUDIO_SOURCE_HDMI)
    {
        // Check AVMute
        if(ScalerGetBit(P2_CB_HDMI_SR, _BIT6) == _BIT6)
        {
            DebugMessageAudio("False : D0 AVMute", 0);
            return _FALSE;
        }

        // Check Audio Tracking
        if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, (_BIT3 | _BIT2)) == 0x00)
        {
            DebugMessageAudio("False : D0 HDMI Audio Tracking Disable", 0);
            return _FALSE;
        }

        // Check HDMI audio FIFO overflow and underflow
        if(ScalerGetBit(P2_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
        {
            DebugMessageAudio("False : D0 HDMI Audio FIFO", ScalerGetBit(P2_CB_HDMI_SR, (_BIT2 | _BIT1)));

            if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, (_BIT2 | _BIT1)) == 0x00)
            {
                // Clear HDMI audio FIFO overflow and underflow status
                ScalerSetBit(P2_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

                if(ScalerGetBit(P2_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
                {
                    DebugMessageAudio("False : D0 HDMI Audio DB Retry", ScalerGetBit(P2_CB_HDMI_SR, (_BIT2 | _BIT1)));

                    // Set Double Buffer bit
                    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

                    // Clear HDMI audio FIFO overflow and underflow status
                    ScalerSetBit(P2_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                }
            }

            return _FALSE;
        }
    }
#if(_DP_SUPPORT == _ON)
    else if(GET_D0_DIGITAL_AUDIO_SOURCE() == _DIGITAL_AUDIO_SOURCE_DP)
    {
        // Check Audio FSM
        if(ScalerGetBit(PB6_74_AUD_FSM_CTRL_0, _BIT7) == 0x00)
        {
            DebugMessageAudio("False : D0 DP Audio Fsm Disable", 0);

            return _FALSE;
        }

        // Check Audio Tracking
        if(ScalerGetBit(PB6_81_AUD_BDRY_0, _BIT7) == 0x00)
        {
            DebugMessageAudio("False : D0 DP Audio Tracking Disable", 0);

            return _FALSE;
        }

        // Check DP audio buffer overflow and underflow
        if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageAudio("False : D0 DP Audio Buffer", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

            if(ScalerGetBit(PB6_39_DP_AWD_CTRL, (_BIT7 | _BIT6)) == 0x00)
            {
                // Clear audio FIFO overflow and underflow status
                ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
                ScalerTimerDelayXms(3);

                if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
                {
                    DebugMessageAudio("False : D0 DP Audio FSM Reset", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

                    // Reset Audio FSM
                    ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

                    // Clear audio FIFO overflow and underflow status
                    ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Enable Audio FSM
                    ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

                    // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
                    ScalerTimerDelayXms(3);
                }
            }

            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DigitalAudioReset(void)
{
    DebugMessageAudio("[I Code] Port Switch Reset Flow", 0);

    CLR_AUDIO_D0_PACKET_DETECT();

    SET_D0_DIGITAL_AUDIO_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE);

    ScalerAudioD0LoadInitialICode();

    CLR_AUDIO_D0_ICODE_RELOADED();
}

//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0LoadInitialICode(void)
{
#if(_HDMI_SUPPORT == _ON)
    // Set high byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_24_PORT_PAGE2_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for HDMI audio
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_25_PORT_PAGE2_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));
#endif

#if(_DP_SUPPORT == _ON)
    // Set high byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB6_83_AUD_BDRY_2, HIBYTE(_INITIAL_I_CODE));

    // Set low byte of I code for boundary tracking for DP audio
    ScalerSetByte(PB6_84_AUD_BDRY_3, LOBYTE(_INITIAL_I_CODE));
#endif

    DebugMessageAudio("Load initial I code", _INITIAL_I_CODE);
}

//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0LoadStableICodeEvent(void)
{
    if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
    {
        // Set high byte of I code for boundary tracking
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_24_PORT_PAGE2_HDMI_ICBPSR0, HIBYTE(_STABLE_I_CODE));

        // Set low byte of I code for boundary tracking
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_25_PORT_PAGE2_HDMI_ICBPSR1, LOBYTE(_STABLE_I_CODE));
    }
    else
    {
        // Set high byte of I code for boundary tracking for DP audio
        ScalerSetByte(PB6_83_AUD_BDRY_2, HIBYTE(_STABLE_I_CODE));

        // Set low byte of I code for boundary tracking for DP audio
        ScalerSetByte(PB6_84_AUD_BDRY_3, LOBYTE(_STABLE_I_CODE));
    }

    DebugMessageAudio("Load stable I code", _STABLE_I_CODE);
}

//--------------------------------------------------
// Description  : Detect D0 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerAudioD0SamplingFreqDetect(void)
{
    EnumAudioSamplingFreqType enumAudioFreq = _AUDIO_FREQ_NO_AUDIO;

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioD0GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_AUDIO_D0_SAMPLING_FREQ(_AUDIO_FREQ_48K);
        return _AUDIO_FREQ_48K;
    }
#endif

    if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
    {
        enumAudioFreq = ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8B_PORT_PAGE2_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        enumAudioFreq = (ScalerGetBit(PB6_61_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    }

    if(enumAudioFreq != GET_AUDIO_D0_SAMPLING_FREQ())
    {
#if(_EMBEDDED_DAC_SUPPORT == _ON)
        if(enumAudioFreq <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(enumAudioFreq <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
#endif

#if(_DP_SUPPORT == _ON)
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _FALSE)
        {
            // Audio DVC Setting
            ScalerAudioD0DPSetDVCWindowSize(_DP_DVC_ADJUST_TYPE, ScalerAudioGetSamplingFreqPacket(enumAudioFreq));
        }
#endif
    }

    SET_AUDIO_D0_SAMPLING_FREQ(enumAudioFreq);

    return enumAudioFreq;
}

//--------------------------------------------------
// Description  : Initial D0 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0SetAudioPLL(void)
{
#if(_DP_SUPPORT == _OFF)
    // Force digital MAC to HDMI when DP is not supported. Switch MAC to Hdmi
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);
#endif

    // DPLL power down
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0, ~_BIT7, _BIT7);

    // Set M code
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_11_PORT_PAGE2_HDMI_MCAPR, (_AUDIO_PLL_M - 2));

    // Set O code
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0, ~(_BIT5 | _BIT4), 0x00);

    // Set K code and enable double buffer
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | ((_AUDIO_PLL_K - 2) & 0x0F)));

    // Initial VCO Band = 10
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_3A_PORT_PAGE2_HDMI_DPCR2, ~(_BIT4 | _BIT3), _BIT4);

    // Set MN PLL Path1 => [2]: 1 = Path1, 0 = Path2
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_3A_PORT_PAGE2_HDMI_DPCR2, ~(_BIT7 | _BIT2), _BIT2);

#if(_HW_PLL_AUTO_EDGE_SELECT_SUPPORT == _ON)
    // Set PLL Edge = Negative
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_3F_PORT_PAGE2_DPLL_LDO, ~_BIT1, 0x00);
#endif

    // DPLL VCORSTB Set to Normal
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_3B_PORT_PAGE2_HDMI_DPCR3, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL power up
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0, ~_BIT7, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // DPLL CMP enable
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0, ~_BIT0, _BIT0);

    // Delay at least 1000us
    ScalerTimerDelayXms(2);

    // DPLL latch calibration enable
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0, ~_BIT1, _BIT1);

    // Delay at least 1000us
    ScalerTimerDelayXms(2);

    // DPLL calibration validated
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : D0 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0WatchDogProc(bit bOn)
{
    if(bOn == _ON)
    {
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
        {
            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(P2_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Audio Watch Dog for FIFO Overflow/Underflow
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
        }
        else
        {
            // Clear audio buffer overflow and underflow status
            ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Enable Audio Watch Dog for Buffer Overflow/Underflow
            ScalerSetBit(PB6_39_DP_AWD_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
    }
    else
    {
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
        {
            // Disable Audio Watch Dog for FIFO Overflow/Underflow
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);
        }
        else
        {
            // Disable Audio Watch Dog for Buffer Overflow/Underflow
            ScalerSetBit(PB6_39_DP_AWD_CTRL, ~(_BIT7 | _BIT6), 0x00);

            if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
            {
                DebugMessageAudio("WD : D0 DP Audio Over/Underflow", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

                // Reset Audio FSM
                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

                // Clear audio FIFO overflow and underflow status
                ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Enable Audio FSM
                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

                // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
                ScalerTimerDelayXms(3);
            }
        }
    }
}

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : D0 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0AudioFrequencyMode(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode)
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
        {
#if(_HDMI_SUPPORT == _ON)
            // Set S code for auto load mode
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_95_PORT_PAGE2_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

            // Set D code for auto load mode
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_99_PORT_PAGE2_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_9A_PORT_PAGE2_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

            // Enable Auto Load S Code and D Code
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, _BIT6);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);
#endif
        }
        else
        {
#if(_DP_SUPPORT == _ON)
            // Set S code by HW auto
            ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);

            // Set D code by HW auto
            ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, _BIT6);

            // S code for 48kHz
            ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

            // D code for 48kHz
            ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(ScalerAudioGetUserSamplingFreqDCode(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));
            ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(ScalerAudioGetUserSamplingFreqDCode(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));

            // D code Double Buffer
            ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
#endif
        }
    }
    else
    {
#if(_HDMI_SUPPORT == _ON)
        // Disable Auto Load S Code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, 0x00);

        // Set S code User Define
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, ScalerAudioGetUserSamplingFreqSCode(_PORT_HDMI, GET_D0_SAMPLING_FREQ_USER_DEFINE()));

        // Set D code User Define
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(ScalerAudioGetUserSamplingFreqDCode(_PORT_HDMI, GET_D0_SAMPLING_FREQ_USER_DEFINE())));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(ScalerAudioGetUserSamplingFreqDCode(_PORT_HDMI, GET_D0_SAMPLING_FREQ_USER_DEFINE())));

        // Set Double Buffer bit
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Load D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);
#endif

#if(_DP_SUPPORT == _ON)
        // S code for User Define
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE()));

        // D code for User Define
        ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(ScalerAudioGetUserSamplingFreqDCode(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));
        ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(ScalerAudioGetUserSamplingFreqDCode(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));

        // D code Double Buffer
        ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, 0x00);
#endif
    }
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : D0 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode) using 1
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
        {
#if(_HDMI_SUPPORT == _ON)
            // Set S code for auto load mode
            ScalerSetDataPortByte_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_95_PORT_PAGE2_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

            // Set D code for auto load mode
            ScalerSetDataPortByte_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_99_PORT_PAGE2_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
            ScalerSetDataPortByte_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_9A_PORT_PAGE2_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

            // Enable Auto Load S Code and D Code
            ScalerSetDataPortBit_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, _BIT6);

            // Set Double Buffer bit
            ScalerSetDataPortBit_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);
#endif
        }
        else
        {
#if(_DP_SUPPORT == _ON)
            // Set S code by HW auto
            ScalerSetBit_EXINT(PB6_58_SCODE_0, ~_BIT7, 0x00);

            // Set D code by HW auto
            ScalerSetBit_EXINT(PB6_80_AUD_PS_CTRL_0, ~_BIT6, _BIT6);

            // S code for 48kHz
            ScalerSetBit_EXINT(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

            // D code for 48kHz
            ScalerSetByte_EXINT(PB6_9D_AUD_D_CODE_0, HIBYTE(ScalerAudioGetUserSamplingFreqDCode_EXINT0(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));
            ScalerSetByte_EXINT(PB6_A0_AUD_D_CODE_1, LOBYTE(ScalerAudioGetUserSamplingFreqDCode_EXINT0(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));

            // D code Double Buffer
            ScalerSetBit_EXINT(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
#endif
        }
    }
    else
    {
#if(_HDMI_SUPPORT == _ON)
        // Disable Auto Load S Code
        ScalerSetDataPortBit_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, 0x00);

        // Set S code User Define
        ScalerSetDataPortByte_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_HDMI, GET_D0_SAMPLING_FREQ_USER_DEFINE()));

        // Set D code User Define
        ScalerSetDataPortByte_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(ScalerAudioGetUserSamplingFreqDCode_EXINT0(_PORT_HDMI, GET_D0_SAMPLING_FREQ_USER_DEFINE())));
        ScalerSetDataPortByte_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(ScalerAudioGetUserSamplingFreqDCode_EXINT0(_PORT_HDMI, GET_D0_SAMPLING_FREQ_USER_DEFINE())));

        // Set Double Buffer bit
        ScalerSetDataPortBit_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Load D code
        ScalerSetDataPortBit_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
        ScalerSetDataPortBit_EXINT0(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);
#endif

#if(_DP_SUPPORT == _ON)
        // S code for User Define
        ScalerSetBit_EXINT(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE()));

        // D code for User Define
        ScalerSetByte_EXINT(PB6_9D_AUD_D_CODE_0, HIBYTE(ScalerAudioGetUserSamplingFreqDCode_EXINT0(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));
        ScalerSetByte_EXINT(PB6_A0_AUD_D_CODE_1, LOBYTE(ScalerAudioGetUserSamplingFreqDCode_EXINT0(_PORT_DP, GET_D0_SAMPLING_FREQ_USER_DEFINE())));

        // D code Double Buffer
        ScalerSetBit_EXINT(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit_EXINT(PB6_58_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit_EXINT(PB6_80_AUD_PS_CTRL_0, ~_BIT6, 0x00);
#endif
    }
}

#if(_D1_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : D0 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerAudioD1AudioFrequencyMode_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode) using 1
{
    ScalerAudioD0AudioFrequencyMode_EXINT0(enumAudioFreqTrackingMode);
}
#endif // End of #if(_D1_DP_EXIST == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)


#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioD0GetInternalAudioGenEnable(void)
{
    if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, _BIT4) == _BIT4)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}

//--------------------------------------------------
// Description  : D0 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0InternalAudioGenSwitch(bit bOn)
{
    if(bOn == _ON)
    {
        DebugMessageAudio("D0 Audio Test On", ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, _BIT4));

        // Disable audio FIFO and Enable audio internal generator
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Disbale DPLL Freq. Tuning
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_3A_PORT_PAGE2_HDMI_DPCR2, ~_BIT1, 0x00);

        // Set S code
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set D code
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

        // Disable sample freq. detection and auto load S code / D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~(_BIT7 | _BIT6), 0x00);

        // Enable double buffer
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        ScalerAudioDigitalOutputMute(_OFF);
    }
    else
    {
        DebugMessageAudio("D0 Aduio Test Off", ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, _BIT4));

        ScalerAudioDigitalOutputMute(_ON);

        // Enable sample freq. detection and auto load S code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable double buffer
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Enable DPLL Freq. Tuning
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_3A_PORT_PAGE2_HDMI_DPCR2, ~_BIT1, _BIT1);

        // Enable audio FIFO and Disable audio internal generator
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
    }
}
#endif

#endif // End of #if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial D0 DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DPAudioInitial(void)
{
    // Disable Check VBID[4] to Mute Audio by HW and disable Audio FSM
    ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~(_BIT7 | _BIT1), 0x00);

    // Disable AFD, set 2ms for auto freq. detect and disable 44.1kHz as 48kHz
    ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT3 | _BIT2 | _BIT0), _BIT2);

    // Set threshold to separate sampling frequency
    ScalerSetByte(PB6_52_AUD_FREQUENY_TH_0, 0x00);
    ScalerSetByte(PB6_53_AUD_FREQUENY_TH_1, 0x00);
    ScalerSetByte(PB6_54_AUD_FREQUENY_TH_2, 0x28);
    ScalerSetByte(PB6_55_AUD_FREQUENY_TH_3, 0x4C);
    ScalerSetByte(PB6_56_AUD_FREQUENY_TH_4, 0x5C);
    ScalerSetByte(PB6_57_AUD_FREQUENY_TH_5, 0x70);

    // Enable RS Decode
    ScalerSetBit(PB6_2B_MN_RS_DEC_CTRL, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set xtal divider for sampling freq. detection
    ScalerSetByte(PB6_51_AUD_FREQUENY_DET_1, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Enable SDM control
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT7, _BIT7);

    // Disable Boundary Tracking Method
    ScalerSetBit(PB6_81_AUD_BDRY_0, ~_BIT7, 0x00);

    // Set I code of boundary tracking
    ScalerSetByte(PB6_83_AUD_BDRY_2, HIBYTE(_INITIAL_I_CODE));
    ScalerSetByte(PB6_84_AUD_BDRY_3, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary tracking
    ScalerSetByte(PB6_85_AUD_BDRY_4, 0x7F);
    ScalerSetByte(PB6_86_AUD_BDRY_5, 0xFF);

    // Disable Trend Tracking Method
    ScalerSetBit(PB6_92_AUD_TRND_0, ~_BIT7, 0x00);

    // Set I code of trend tracking
    ScalerSetByte(PB6_99_AUD_TRND_7, 0x00);
    ScalerSetByte(PB6_9A_AUD_TRND_8, 0x02);

    // Set P code of trend tracking
    ScalerSetByte(PB6_9B_AUD_TRND_9, 0x7F);
    ScalerSetByte(PB6_9C_AUD_TRND_10, 0xFF);

    // Enable Audio Buffer & Valid_Bit Detect
    ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Disable Audio Coding Type Change INT
    ScalerSetBit(PB6_3B_DP_IRQ_CTRL1, ~_BIT0, 0x00);

    // Reset Coding Type Detect
    SET_DP_D0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_CODING_TYPE_NONE);

    // Clear Change Flag
    CLR_DP_D0_AUDIO_CODING_TYPE_CHANGE();

    // Set AUD PKT ID
    ScalerSetByte(PB6_B1_DP_AUD_ID, 0x00);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Set S code by FW manual
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

    // Set D code by FW manual
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // S code for 32kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // D code for 32kHz
    ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // S code for 44.1kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // D code for 44.1kHz
    ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // S code for 48kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // D code for 48kHz
    ScalerSetByte(PB6_9D_AUD_D_CODE_0, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetByte(PB6_A0_AUD_D_CODE_1, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
#endif

    // D code Double Buffer
    ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
#else

    // Set S code by HW auto
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);

    // Set D code by HW auto
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~_BIT6, _BIT6);

    // S code for 32kHz
    ScalerSetBit(PB6_58_SCODE_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // S code for 44.1kHz
    ScalerSetBit(PB6_59_SCODE_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // S code for 48kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // D code for 32kHz
    ScalerSetByte(PB6_5B_DCODE_0, HIBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetByte(PB6_5C_DCODE_1, LOBYTE(_DP_SAMPLING_FREQ_32K_GROUP_D_CODE));

    // D code for 44.1kHz
    ScalerSetByte(PB6_5D_DCODE_2, HIBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetByte(PB6_5E_DCODE_3, LOBYTE(_DP_SAMPLING_FREQ_44K_GROUP_D_CODE));

    // D code for 48kHz
    ScalerSetByte(PB6_5F_DCODE_4, HIBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetByte(PB6_60_DCODE_5, LOBYTE(_DP_SAMPLING_FREQ_48K_GROUP_D_CODE));

    // D code Double Buffer
    ScalerSetBit(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);

    // Set User Define Frequency When No Audio
    ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_MANNUAL_MODE);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // DP Audio DVC Mode Setting
    ScalerAudioD0DPSetDVCVolumeAdjustType(_DP_DVC_ADJUST_TYPE);

    // Enable AFD, Disable Samping Freq. Change INT
    ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT6), _BIT7);

    // Enable I2S Output
    ScalerSetBit(PB6_B8_DP_I2S_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable SPDIF Output
    ScalerSetBit(PB6_A9_SPDIF_TX_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // CLR PLL Autoload Status Flag
    CLR_AUDIO_D0_AUTO_LOAD_FREQ();
}

//--------------------------------------------------
// Description  : DP Digital Audio Output Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DPDigitalOutputProc(bit bEnable)
{
    ScalerSetByte(PB6_B3_DP_CHANNEL_EN, ((bEnable == _ENABLE) ? 0xFF : 0x00));
}

//--------------------------------------------------
// Description  : Set ZCD Timeout for DP Audio
// Input Value  : bAdjustType, enumSamplingFreqPacket
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DPSetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket)
{
    if(enumSamplingFreqPacket == _AUDIO_FREQ_PACKET_NO_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }

    if(bAdjustType == _DB_GAIN)
    {
        // Get numbers of the volume step for mute or unmute
        PDATA_WORD(0) = _DVC_DB_STEP_NUMBER << 3;
    }
    else
    {
        // Volume Max = 0x3FFF
        PDATA_WORD(0) = 0x3FFF / _DP_VOLUME_STEP_SIZE_VALUE + 1;
    }

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DP_DVC_VOLUME_MUTE_TIMER / PDATA_WORD(0);

    // Avoid Overflow
    if(PDATA_DWORD(1) > 0x0FFF)
    {
        PDATA_WORD(0) = 0x0FFF;
    }
    else
    {
        PDATA_WORD(0) = (WORD)PDATA_DWORD(1);
    }

    // Set DVC ZCD window size
    ScalerSetBit(PB6_78_DVC_WINDOW_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(PB6_79_DVC_WINDOW_CONTROL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Select DVC Volume Adjust Type
// Input Value  : _DB_GAIN, _VOLUME_STEP_SIZE
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DPSetDVCVolumeAdjustType(bit bAdjustType)
{
    if(bAdjustType == _DB_GAIN)
    {
        // Select Value Mode to DB Gain Setp
        ScalerSetBit(PB6_76_DVC_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | (_DP_DB_GAIN_DOWN_VALUE << 2) | _DP_DB_GAIN_UP_VALUE));

        // Initial Volume Step Size for DB Gain Mode
        ScalerSetByte(PB6_77_DVC_VA, 0x01);
    }
    else // _VOLUME_STEP_SIZE
    {
        // Select Value Mode to Volume Setp
        ScalerSetBit(PB6_76_DVC_CTRL, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

        // Set Volume Step Size
        ScalerSetByte(PB6_77_DVC_VA, _DP_VOLUME_STEP_SIZE_VALUE);
    }

    // DP Audio DVC Window Setting
    ScalerAudioD0DPSetDVCWindowSize(bAdjustType, _AUDIO_FREQ_PACKET_48K);
}

//--------------------------------------------------
// Description  : Get DP Normal Link Training Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerAudioGetDPNormalLinkTrainingStatus(void)
{
#if(_D0_DP_EXIST == _ON)
    if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _TRUE;
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}
#endif

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial D0 HDMI audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0HDMIAudioInitial(void)
{
    // Disable sine wave generator
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Disable FIFO Boundary Tracking, Disable Trend Tracking
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));

    // Enable SDM
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_2D_PORT_PAGE2_HDMI_AAPNR, ~_BIT1, _BIT1);

    // Set auto gain delay mode and final gain = full gain
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_07_PORT_PAGE2_HDMI_MAG_M_FINAL, ~_BIT3, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_0A_PORT_PAGE2_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_0B_PORT_PAGE2_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_0D_PORT_PAGE2_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set Boundary Address for Boundary Tracking
    SET_AUDIO_HDMI_TRACKING_BOUNDARY_DISTANCE();

    // Set I code of trend
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_20_PORT_PAGE2_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_21_PORT_PAGE2_HDMI_ICTPSR1, 0x02);

    // Set P code of trend
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_22_PORT_PAGE2_HDMI_PCTPSR0, 0x7F);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_23_PORT_PAGE2_HDMI_PCTPSR1, 0xFF);

    // Set I code of boundary
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_24_PORT_PAGE2_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_25_PORT_PAGE2_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_26_PORT_PAGE2_HDMI_PCBPSR0, 0x7F);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_27_PORT_PAGE2_HDMI_PCBPSR1, 0xFF);

    // Audio Normal Output
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_30_PORT_PAGE2_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_32_PORT_PAGE2_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_33_PORT_PAGE2_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_9F_PORT_PAGE2_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8B_PORT_PAGE2_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8C_PORT_PAGE2_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_8E_PORT_PAGE2_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to sepeerate sampling frequency
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_90_PORT_PAGE2_TH1, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_91_PORT_PAGE2_TH2, 0x28);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_92_PORT_PAGE2_TH3, 0x4C);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_93_PORT_PAGE2_TH4, 0x5C);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_94_PORT_PAGE2_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)
    // Disable Auto Load S Code
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set D code for 32kHz
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set D code for 44.1kHz
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for 48kHz
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

    // Load D code
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

#else
    // Set S code for auto load mode
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_95_PORT_PAGE2_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_96_PORT_PAGE2_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_97_PORT_PAGE2_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set D code for auto load mode
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_99_PORT_PAGE2_PRESET_D_CODE_0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_9A_PORT_PAGE2_PRESET_D_CODE_1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_9B_PORT_PAGE2_PRESET_D_CODE_2, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_9C_PORT_PAGE2_PRESET_D_CODE_3, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_9D_PORT_PAGE2_PRESET_D_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_9E_PORT_PAGE2_PRESET_D_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, _BIT6);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

    // Set User Define Frequency When No Audio
    ScalerAudioD0AudioFrequencyMode(_AUDIO_TRACKING_MANNUAL_MODE);
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)

    // Audio Tracking Reset
    ScalerAudioD0FwTrackingReset();
#endif

    // Enable Audio Freq Detect, Disable Samping Freq. Change INT
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), _BIT7);

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_62_PORT_PAGE2_HDMI_AOCR, 0xFF);

    // CLR PLL Autoload Status Flag
    CLR_AUDIO_D0_AUTO_LOAD_FREQ();
}

//--------------------------------------------------
// Description  : D0 SPDIF/IIS Output Select
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0HdmiI2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput)
{
    if(enumAudioIisSpdifOutput == _AUDIO_SELECT_BY_CA_MODE)
    {
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
        {
            // SPDIF/I2S 4 lane Output Select By Audio Channel Allocation
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_62_PORT_PAGE2_HDMI_AOCR, (((ScalerAudioChannelOutputSel(GET_HDMI_AUDIO_CHANNEL_ALLOCATION()) << 4) | ScalerAudioChannelOutputSel(GET_HDMI_AUDIO_CHANNEL_ALLOCATION()))));
        }
    }
    else
    {
        if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
        {
            // SPDIF/I2S 4 lane Output
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_62_PORT_PAGE2_HDMI_AOCR, 0xFF);
        }
    }
}

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : D0 HDMI FW tracking Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0FwTrackingHandler(void)
{
    switch(GET_AUDIO_D0_FW_TRACKING_STATE())
    {
        case _AUDIO_FW_TRACKING_INITIAL:

            if(GET_D0_DIGITAL_AUDIO_SOURCE() != _DIGITAL_AUDIO_SOURCE_NONE)
            {
                SET_AUDIO_D0_FW_TRACKING_STATE(_AUDIO_FW_TRACKING_PROCESS_PREPARING);

                // Initialize Audio Tracking By FW Control
                ScalerAudioD0FwTrackingInitial();

                SET_AUDIO_D0_FW_TRACKING_EVENT();

                CLR_AUDIO_D0_FW_TRACKING_RESET();

                DebugMessageAudio("D0 Audio: FW Tracking Start", 0);
            }

            break;

        case _AUDIO_FW_TRACKING_PROCESS_PREPARING:

            if(GET_AUDIO_D0_FW_TRACKING_EVENT() == _TRUE)
            {
                CLR_AUDIO_D0_FW_TRACKING_EVENT();

                // Find stable SUMC or already 4s --> boundary tracking
                if((g_stHDMID0AudioFwTrackingInfo.b1AudioFwTrackStable != 0x00) || (GET_AUDIO_D0_FW_TRACKING_TIMEOUT() == _TRUE))
                {
                    if(g_stHDMID0AudioFwTrackingInfo.b1AudioFwTrackStable != 0x00)
                    {
                        g_stHDMID0AudioFwTrackingInfo.b1AudioFwTrackStable = 0x00;

                        DebugMessageAudio("D0 Audio: SUMC Stable", g_stHDMID0AudioFwTrackingInfo.b1AudioFwTrackStable);
                    }
                    else
                    {
                        DebugMessageAudio("D0 Audio: SUMC Final", 0);
                    }

                    SET_AUDIO_D0_FW_TRACKING_STATE(_AUDIO_FW_TRACKING_PROCESS_PLAYBACK);

                    CLR_AUDIO_D0_FW_TRACKING_TIMEOUT();
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_TIMEOUT);
                }
                else
                {
                    // FW tracking - preparing tracking
                    ScalerAudioD0FwPreparingTracking();
                }

                ScalerTimerActiveTimerEvent(ScalerAudioD0FwTrackingTimerEventPeriod(), _SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_PREPARING);
            }

            break;

        case _AUDIO_FW_TRACKING_PROCESS_PLAYBACK:

            if(GET_AUDIO_D0_FW_TRACKING_EVENT() == _TRUE)
            {
                CLR_AUDIO_D0_FW_TRACKING_EVENT();

                // FW tracking - boundary tracking
                ScalerAudioD0FwBoundaryTracking();

                ScalerTimerActiveTimerEvent(ScalerAudioD0FwTrackingTimerEventPeriod(), _SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_PREPARING);
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : D0 HDMI FW tracking Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0FwTrackingInitial(void)
{
    g_stHDMID0AudioFwTrackingInfo.b1AudioFwTrackStable = 0x00;
    g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt = 0x00;
    g_stHDMID0AudioFwTrackingInfo.ucAudioFreqRecord = ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8B_PORT_PAGE2_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set I code of trend
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_20_PORT_PAGE2_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_21_PORT_PAGE2_HDMI_ICTPSR1, 0x00);

    // Set P code of trend
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_22_PORT_PAGE2_HDMI_PCTPSR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_23_PORT_PAGE2_HDMI_PCTPSR1, 0x00);

    // Set I code of boundary
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_24_PORT_PAGE2_HDMI_ICBPSR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_25_PORT_PAGE2_HDMI_ICBPSR1, 0x00);

    // Set P code of boundary
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_26_PORT_PAGE2_HDMI_PCBPSR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_27_PORT_PAGE2_HDMI_PCBPSR1, 0x00);

    // Disable Auto Load S/D Code
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, 0x00);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

    // Initialize D Code for FW Audio Tracking
    ScalerAudioD0DcodeSettingInitial();

    CLR_AUDIO_D0_FW_TRACKING_TIMEOUT();

    // When the stable N.F Code is not found within 4 seconds, tracking state force to playback for play audio
    ScalerTimerReactiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_TIMEOUT);
}

//--------------------------------------------------
// Description  : Initial D code setting by fs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0DcodeSettingInitial(void)
{
    if(GET_AUDIO_D0_SAMPLING_FREQ() == _AUDIO_FREQ_32K)
    {
        // Set S code for 32kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
        // Set D code for 32kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE));
    }
    else if(GET_AUDIO_D0_SAMPLING_FREQ() == _AUDIO_FREQ_44_1K)
    {
        // Set S code for 44.1kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
        // Set D code for 44.1kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE));
    }
    else if(GET_AUDIO_D0_SAMPLING_FREQ() == _AUDIO_FREQ_48K)
    {
        // Set S code for 48kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);
        // Set D code for 48kHz
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE));
    }

    // Set Double Buffer bit
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

    // Load D code
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : D0 Pll Fw Tracking Process - Preparing Tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0FwPreparingTracking(void)
{
    // check WL, adjust SUMC
    WORD usbackupSumc = 0x00;
    BYTE ucAfifoCurrent = 0x00;

    // get current AFIFO waterlevel
    ScalerGetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_16_PORT_PAGE2_HDMI_FDDR, 1, &(ucAfifoCurrent), _NON_AUTOINC);

    // get current Dcode
    ScalerGetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_3C_PORT_PAGE2_HDMI_SUMCM, 2, &pData[0], _AUTOINC);
    usbackupSumc = (((WORD)pData[0] << 8) | pData[1]);

    // AFIFO water level going up --> decrease SUMC
    if((ucAfifoCurrent > (g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup + 0x02)) ||
       (ucAfifoCurrent >= 0x1A))
    {
        if(ucAfifoCurrent < 0x1A)
        {
            if((GET_AUDIO_D0_WL_TARGET_DIRECTION() == _AUDIO_WL_GOES_UP) &&
               (ucAfifoCurrent >= (g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup + 0x02)))
            {
                DebugMessageAudio("D0 Audio: AFIFO has gone up", ucAfifoCurrent);

                // set stable count = _stable_cnt(0x20)/2
                g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt = (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2);
            }
            else
            {
                if(g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt < (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2))
                {
                    usbackupSumc -= (((_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2) - g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt) * (ucAfifoCurrent - (g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup + 0x01)));
                }
                else
                {
                    usbackupSumc -= 0x01;
                }

                // Set D code
                ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(usbackupSumc));
                ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(usbackupSumc));

                // Set Double Buffer
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

                // Load D code
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

                // set stable count = 0
                g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt = 0;

                DebugMessageAudio("D0 Audio: AFIFO current", ucAfifoCurrent);
                DebugMessageAudio("D0 Audio: SUMC-", usbackupSumc);
            }
        }
        else
        {
            usbackupSumc -= 0x10;

            // Set D code
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(usbackupSumc));
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(usbackupSumc));

            // Set Double Buffer
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

            // Load D code
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

            // set stable count = 0
            g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

            DebugMessageAudio("D0 Audio: AFIFO Full", ucAfifoCurrent);
            DebugMessageAudio("D0 Audio: SUMC- Full", usbackupSumc);
        }

        SET_AUDIO_D0_WL_TARGET_DIRECTION(_AUDIO_WL_GOES_DOWN);

        // Reset AFIFO water level backup
        g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;
    }
    else if((ucAfifoCurrent < (g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup - 0x02)) ||
            (ucAfifoCurrent <= 0x06))  // AFIFO water level going down  -> increase SUMC
    {
        if(ucAfifoCurrent > 0x06)
        {
            if((GET_AUDIO_D0_WL_TARGET_DIRECTION() == _AUDIO_WL_GOES_DOWN) &&
               (ucAfifoCurrent <= (g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup - 0x02)))
            {
                DebugMessageAudio("D0 Audio: AFIFO has gone down", ucAfifoCurrent);

                // Set stable count = _stable_cnt(0x20)/2
                g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt = (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2);
            }
            else
            {
                if(g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt < (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2))
                {
                    usbackupSumc += (((_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2) - g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt) * ((g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup - 0x01) - ucAfifoCurrent));
                }
                else
                {
                    usbackupSumc += 0x01;
                }

                // Set D code
                ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(usbackupSumc));
                ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(usbackupSumc));

                // Set Double Buffer
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

                // Load D code
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

                // set stable count = 0
                g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

                DebugMessageAudio("D0 Audio: AFIFO current", ucAfifoCurrent);
                DebugMessageAudio("D0 Audio: SUMC+", usbackupSumc);
            }
        }
        else
        {
            usbackupSumc += 0x10;

            // Set D code
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(usbackupSumc));
            ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(usbackupSumc));

            // Set Double Buffer
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

            // Load D code
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);

            // set stable count = 0
            g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

            DebugMessageAudio("D0 Audio: AFIFO Empty", ucAfifoCurrent);
            DebugMessageAudio("D0 Audio: SUMC+ Empty", usbackupSumc);
        }

        SET_AUDIO_D0_WL_TARGET_DIRECTION(_AUDIO_WL_GOES_UP);

        // Reset AFIFO water level backup
        g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;
    }
    else    // AfifoBackup-2 < AfifoCurrent < AfifoBackup+2
    {
        if(g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt < _AUDIO_FW_TRCK_FIRST_STABLE_CNT)
        {
            g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt++;
        }
    }

    // check stable
    if(g_stHDMID0AudioFwTrackingInfo.ucAfifoTrackStableCnt >= _AUDIO_FW_TRCK_FIRST_STABLE_CNT)
    {
        // Set stable SUMC
        g_stHDMID0AudioFwTrackingInfo.b1AudioFwTrackStable = 0x01;

        DebugMessageAudio("D0 Audio: Find Stable D", usbackupSumc);
    }
}

//--------------------------------------------------
// Description  : D0 Pll Fw Tracking Process - Boundary Tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0FwBoundaryTracking(void)
{
    // check WL, adjust SUMC
    WORD usbackupSumc = 0x00;
    BYTE ucAfifoCurrent = 0x00;

    // get current AFIFO waterlevel
    ScalerGetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_16_PORT_PAGE2_HDMI_FDDR, 1, &(ucAfifoCurrent), _NON_AUTOINC);

    // get current SUMC
    ScalerGetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_3C_PORT_PAGE2_HDMI_SUMCM, 2, &pData[0], _AUTOINC);
    usbackupSumc = (((WORD)pData[0] << 8) | pData[1]);

    // AFIFO water level goes up, decrease SUMC
    if(((ucAfifoCurrent > 0x12) && (ucAfifoCurrent > g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup)) ||
       (ucAfifoCurrent > 0x18))
    {
        DebugMessageAudio("D0 Audio: Boundary up", g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup);
        DebugMessageAudio("D0 Audio: SUMC-", usbackupSumc);

        if(ucAfifoCurrent > 0x18)
        {
            usbackupSumc -= 0x08;
        }
        else
        {
            usbackupSumc -= ((ucAfifoCurrent - 0x12) + 1);
        }

        // Reset AFIFO water level backup
        g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;

        // Set D code
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(usbackupSumc));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(usbackupSumc));

        // Set Double Buffer
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Load D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);
    }

    // AFIFO water level goes down, increase SUMC
    if(((ucAfifoCurrent < 0x0E) && (ucAfifoCurrent < g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup)) ||
       (ucAfifoCurrent < 0X08))
    {
        DebugMessageAudio("Audio: Boundary down", g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup);
        DebugMessageAudio("Audio: SUMC+", usbackupSumc);

        if(ucAfifoCurrent < 0x08)
        {
            usbackupSumc += 0x08;
        }
        else
        {
            usbackupSumc += ((0x0E - ucAfifoCurrent) + 1);
        }

        // Reset AFIFO water level backup
        g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;

        // Set D code
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1, LOBYTE(usbackupSumc));
        ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0, HIBYTE(usbackupSumc));

        // Set Double Buffer
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

        // Load D code
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, _BIT6);
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : D0 Pll Fw Tracking Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0FwTrackingReset(void)
{
    g_stHDMID0AudioFwTrackingInfo.ucAfifoBackup = 0x00;

    CLR_AUDIO_D0_FW_TRACKING_RESET();

    SET_AUDIO_D0_FW_TRACKING_STATE(_AUDIO_FW_TRACKING_INITIAL);

    // Set I code of trend
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_20_PORT_PAGE2_HDMI_ICTPSR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_21_PORT_PAGE2_HDMI_ICTPSR1, 0x02);

    // Set P code of trend
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_22_PORT_PAGE2_HDMI_PCTPSR0, 0x7F);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_23_PORT_PAGE2_HDMI_PCTPSR1, 0xFF);

    // Set I code of boundary
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_24_PORT_PAGE2_HDMI_ICBPSR0, HIBYTE(_INITIAL_I_CODE));
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_25_PORT_PAGE2_HDMI_ICBPSR1, LOBYTE(_INITIAL_I_CODE));

    // Set P code of boundary
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_26_PORT_PAGE2_HDMI_PCBPSR0, 0x7F);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_27_PORT_PAGE2_HDMI_PCBPSR1, 0xFF);

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET, ~_BIT6, _BIT6);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);

    CLR_AUDIO_D0_FW_TRACKING_EVENT();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_PREPARING);

    CLR_AUDIO_D0_FW_TRACKING_TIMEOUT();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_AUDIO_D0_FW_TRACKING_TIMEOUT);

    CLR_AUDIO_D0_WL_TARGET_DIRECTION();
}

//--------------------------------------------------
// Description  : Audio FW tracking timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0FwTrackingEventSet(void)
{
    SET_AUDIO_D0_FW_TRACKING_EVENT();
}

//--------------------------------------------------
// Description  : Audio FW tracking 4s timeout event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioD0TimeoutEventSet(void)
{
    SET_AUDIO_D0_FW_TRACKING_TIMEOUT();
}

//--------------------------------------------------
// Description  : Audio FW tracking timer event period
// Input Value  : None
// Output Value : Timer event period
//--------------------------------------------------
BYTE ScalerAudioD0FwTrackingTimerEventPeriod(void)
{
    if(GET_AUDIO_D0_FW_TRACKING_STATE() == _AUDIO_FW_TRACKING_PROCESS_PREPARING)
    {
        return (_AUDIO_FW_TRCK_PREPARING_CHECK);
    }
    else
    {
        return (_AUDIO_FW_TRCK_PLAYBACK_CHECK);
    }
}
#endif
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)
