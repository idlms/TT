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
// ID Code      : ScalerAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_AUDIO__

#include "ScalerFunctionInclude.h"

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

#if(_EMBEDDED_DAC_SUPPORT == _ON)
StructAudioDACInfo g_stAudioDACInfo;
#endif

bit g_bAudioDVCMuteCtrlStatus;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerAudioInitial(void);
void ScalerAudioDigitalAdjustVolume(WORD usVolume);
void ScalerAudioMuteProc(bit bMute, WORD usVolume);
void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume);
void ScalerAudioDisable(void);
void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput);
BYTE ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput);
EnumAudioSamplingFreqPacket ScalerAudioGetSamplingFreqPacket(EnumAudioSamplingFreqType enumSamplingFreqType);
WORD ScalerAudioGetUserSamplingFreqDCode(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
BYTE ScalerAudioGetUserSamplingFreqSCode(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
WORD ScalerAudioGetUserSamplingFreqDCode_EXINT0(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
BYTE ScalerAudioGetUserSamplingFreqSCode_EXINT0(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
BYTE ScalerAudioChannelOutputSel(BYTE ucCa);

#if(_LINE_IN_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_NONE)

#if(_DP_SUPPORT == _ON)
BYTE ScalerAudioGetDigitalAudioPort_EXINT0(EnumAudioOutputType enumAudioOutput);
#endif

EnumAudioInputSource ScalerAudioGetInputSource_EXINT0(void);
#endif

EnumAudioInputSource ScalerAudioGetInputSource(void);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
void ScalerAudioDACInitial(void);
void ScalerAudioDACOutputSwitch(EnumAudioDACOutput enumDACOutput);
void ScalerAudioDACSetState(EnumAudioDACState enumTargetState);
EnumAudioDACState ScalerAudioDACGetState(void);
bit ScalerAudioDACGetStateChange(void);
void ScalerAudioDACClrStateChange(void);
void ScalerAudioDACSetVcmReady(bit bReady);
void ScalerAudioDACNormalToDepop(void);
void ScalerAudioDACDepopToNormal(void);
void ScalerAudioDACOutputEnable(void);
EnumAudioDACOutput ScalerAudioDACGetOutput(void);
void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain);
#endif

void ScalerAudioDVCInitial(void);
void ScalerAudioDVCVolumeAdjustType(bit bAdjustType);
void ScalerAudioDVCAdjustVolume(WORD usVolume);
void ScalerAudioDVCVolumeMute(bit bMute, WORD usVolume);
void ScalerAudioDVCSetMuteZCDTimeout(bit bMute, WORD usVolume, bit bAdjustType);
void ScalerAudioDVCSetVolumeZCDTimeout(WORD usVolume);
bit ScalerAudioDVCGetVolumeMuteStatus(void);
void ScalerAudioDVCResetProc(void);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
void ScalerAudioSpdifChannelStatusProc(EnumAudioInputSource enumAudioSource, BYTE ucInputPort);
void ScalerAudioSpdifCheckIfSamplingFrequencyChange(BYTE ucInputPort);
#endif

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define _AUDIO_AMP_MAX                              255		
#else
#define _AUDIO_AMP_MAX                              4095	// Audio Amp PWM 12BIT
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Audio Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioInitial(void)
{
    ScalerAudioDigitalAudioInitial();

    ScalerAudioDVCInitial();
	
	PCB_VOLUME_PWM((WORD)(_AUDIO_AMP_MAX/2.8));	// External Audio AMP Default Set ( _PWM_8BIT : 0x50 / _PWM_12BIT : 0x5B6 )
}

//--------------------------------------------------
// Description  : Adjust Digital volume
// Input Value  : ucVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalAdjustVolume(WORD usVolume)
{
    ScalerAudioDVCSetVolumeZCDTimeout(usVolume);

    ScalerAudioDVCAdjustVolume(usVolume);
}

//--------------------------------------------------
// Description  : Audio Mute proc
// Input Value  : bMute, usVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioMuteProc(bit bMute, WORD usVolume)
{
    ScalerAudioDigitalVolumeMute(bMute, usVolume);
}

//--------------------------------------------------
// Description  : Smooth adjust digital volume for mute/unmute
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume)
{
    ScalerAudioDVCVolumeMute(bMute, usVolume);
}

//--------------------------------------------------
// Description  : Transfer depop mode to Normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDisable(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)

    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL);
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);

    ScalerAudioDACNormalToDepop();

    ScalerAudioDACSetVcmReady(_OFF);

    // Power Down Depop CLK
    ScalerSetBit(P6_D4_DA_CLK_CTRL, ~_BIT4, 0x00);

    // Power Down DAC
    ScalerSetByte(P6_C0_REG_DAC_POWER0, 0x00);
    ScalerSetBit(P6_C1_REG_DAC_POWER1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    SET_AUDIO_DAC_STATE(_AUDIO_DAC_OFF);

#endif

#if(_LINE_IN_SUPPORT == _ON)

#if(_HW_AUDIO_LINE_IN_AFE_POWER_TYPE == _ADC_AFE_POWER_CONTROL_GEN_1)
    // Power Down ADC
    ScalerSetBit(P6_B0_REG_ADC_POWER, ~_BIT7, 0x00);
#else
    // Power Down ADC
    ScalerSetBit(P6_B0_REG_ADC_POWER, ~(_BIT7 | _BIT6), 0x00);
#endif

    // Power Down Input Buffer and Mbias
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

    // Disable DVC counter for power saving
    ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);

    // Power Down DPLL
    ScalerAudioDisableAudioPLL();
}

//--------------------------------------------------
// Description  : Switch Audio Input Port For Each Audio Output
// Input Value  : ucAudioOutput, ucAudioInput
// Output Value : None
//--------------------------------------------------
void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput)
{
    // Set DAC Input
    ScalerSetBit(P6F_01_MUX_DA_DVC_IN, ~(_BIT2 | _BIT1 | _BIT0), enumAudioInput);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _OFF)
    // Set IIS Input
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT6 | _BIT5 | _BIT4), (enumAudioInput << 4));

    // Set SPDIF Input
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT2 | _BIT1 | _BIT0), enumAudioInput);
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _ON)
    // Set DP Tx Input
    ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), enumAudioInput);
#endif
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio Port For Output Type
// Input Value  : None
// Output Value : audio port
//--------------------------------------------------
BYTE ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:

            return (ScalerGetBit(P6F_01_MUX_DA_DVC_IN, (_BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_I2S_OUT:

            return (ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT6 | _BIT5 | _BIT4)) >> 4);

        case _AUDIO_SPDIF_OUT:

            return (ScalerGetBit(P6F_00_MUX_DIG_OUT, (_BIT2 | _BIT1 | _BIT0)));

#if(_DP_TX_SUPPORT == _ON)
        case _AUDIO_DPTX_OUT:

            return (ScalerGetBit(P6F_02_MUX_DP_I2S_IN, (_BIT2 | _BIT1 | _BIT0)));
#endif

        default:
            break;
    }

    return _AUDIO_FROM_D0_PORT;
}

//--------------------------------------------------
// Description  : Get Audio Sampling Freq Packet
// Input Value  : EnumAudioSamplingFreqType
// Output Value : EnumAudioSamplingFreqPacket
//--------------------------------------------------
EnumAudioSamplingFreqPacket ScalerAudioGetSamplingFreqPacket(EnumAudioSamplingFreqType enumSamplingFreqType)
{
    switch(enumSamplingFreqType)
    {
        case _AUDIO_FREQ_32K:
            return _AUDIO_FREQ_PACKET_32K;

        case _AUDIO_FREQ_44_1K:
            return _AUDIO_FREQ_PACKET_44_1K;

        case _AUDIO_FREQ_48K:
            return _AUDIO_FREQ_PACKET_48K;

        case _AUDIO_FREQ_64K:
            return _AUDIO_FREQ_PACKET_64K;

        case _AUDIO_FREQ_88_2K:
            return _AUDIO_FREQ_PACKET_88_2K;

        case _AUDIO_FREQ_96K:
            return _AUDIO_FREQ_PACKET_96K;

        case _AUDIO_FREQ_128K:
            return _AUDIO_FREQ_PACKET_128K;

#if(_HW_HDMI_AUDIO_AFD_MODE_FOR_176P4_192 == _AUDIO_AFD_FW_MODE)
        case _AUDIO_FREQ_176_4K:
        case _AUDIO_FREQ_192K:

            if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
            {
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_8C_PORT_PAGE2_AUDIO_FREQ_RESULT_M, ~_BIT4, _BIT4);

                ScalerGetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_8C_PORT_PAGE2_AUDIO_FREQ_RESULT_M, 2, &pData[2], _AUTOINC);

                if((PDATA_WORD(1) & 0xFFF) < 0x171)
                {
                    DebugMessageAudio("Fs = 176.4kHz", (PDATA_WORD(1) & 0xFFF));
                    return _AUDIO_FREQ_PACKET_176_4K;
                }
                else
                {
                    DebugMessageAudio("Fs = 192kHz", (PDATA_WORD(1) & 0xFFF));
                    return _AUDIO_FREQ_PACKET_192K;
                }
            }
            else
            {
                if(enumSamplingFreqType == _AUDIO_FREQ_176_4K)
                {
                    return _AUDIO_FREQ_PACKET_176_4K;
                }
                else
                {
                    return _AUDIO_FREQ_PACKET_192K;
                }
            }
#else
        case _AUDIO_FREQ_176_4K:
            return _AUDIO_FREQ_PACKET_176_4K;

        case _AUDIO_FREQ_192K:
            return _AUDIO_FREQ_PACKET_192K;
#endif

        default:
            break;
    }

    return _AUDIO_FREQ_PACKET_NO_AUDIO;
}

//--------------------------------------------------
// Description  : Get User Define D Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
WORD ScalerAudioGetUserSamplingFreqDCode(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq)
{
    WORD usDCode = 0x00;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:
        case _AUDIO_FREQ_64K:
        case _AUDIO_FREQ_128K:
        case _AUDIO_FREQ_256K:
        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_32K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE;
            }

            break;

        case _AUDIO_FREQ_44_1K:
        case _AUDIO_FREQ_88_2K:
        case _AUDIO_FREQ_176_4K:
        case _AUDIO_FREQ_352_8K:
        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_44K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE;
            }

            break;

        case _AUDIO_FREQ_48K:
        case _AUDIO_FREQ_96K:
        case _AUDIO_FREQ_192K:
        case _AUDIO_FREQ_384K:
        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }

            break;
    }

    return usDCode;
}

//--------------------------------------------------
// Description  : Get User Define S Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
BYTE ScalerAudioGetUserSamplingFreqSCode(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq)
{
    BYTE ucSCode = 0x00;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }

            break;

        case _AUDIO_FREQ_44_1K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
            break;

        case _AUDIO_FREQ_48K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }

            break;

        case _AUDIO_FREQ_64K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }

            break;

        case _AUDIO_FREQ_88_2K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }

            break;

        case _AUDIO_FREQ_96K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }

            break;

        case _AUDIO_FREQ_128K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }

            break;

        case _AUDIO_FREQ_176_4K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }

            break;

        case _AUDIO_FREQ_192K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }

            break;

        case _AUDIO_FREQ_256K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }

            break;

        case _AUDIO_FREQ_352_8K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }

            break;

        case _AUDIO_FREQ_384K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }

            break;

        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }

            break;

        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }

            break;

        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }

            break;
    }

    return ucSCode;
}

//--------------------------------------------------
// Description  : Get User Define D Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
WORD ScalerAudioGetUserSamplingFreqDCode_EXINT0(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq) using 1
{
    WORD usDCode = 0x00;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:
        case _AUDIO_FREQ_64K:
        case _AUDIO_FREQ_128K:
        case _AUDIO_FREQ_256K:
        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_32K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE;
            }

            break;

        case _AUDIO_FREQ_44_1K:
        case _AUDIO_FREQ_88_2K:
        case _AUDIO_FREQ_176_4K:
        case _AUDIO_FREQ_352_8K:
        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_44K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE;
            }

            break;

        case _AUDIO_FREQ_48K:
        case _AUDIO_FREQ_96K:
        case _AUDIO_FREQ_192K:
        case _AUDIO_FREQ_384K:
        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                usDCode = _DP_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                usDCode = _HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE;
            }

            break;
    }

    return usDCode;
}

//--------------------------------------------------
// Description  : Get User Define S Code of Audio Sampling Freq
// Input Value  : EnumPortType
// Input Value  : EnumAudioSamplingFreqType
// Output Value : NF Code
//--------------------------------------------------
BYTE ScalerAudioGetUserSamplingFreqSCode_EXINT0(EnumInputPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq) using 1
{
    BYTE ucSCode = 0x00;

    switch(enumAudioFreq)
    {
        case _AUDIO_FREQ_32K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE;
            }

            break;

        case _AUDIO_FREQ_44_1K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE;
            }
            break;

        case _AUDIO_FREQ_48K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }

            break;

        case _AUDIO_FREQ_64K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 1;
            }

            break;

        case _AUDIO_FREQ_88_2K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 1;
            }

            break;

        case _AUDIO_FREQ_96K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 1;
            }

            break;

        case _AUDIO_FREQ_128K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 2;
            }

            break;

        case _AUDIO_FREQ_176_4K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 2;
            }

            break;

        case _AUDIO_FREQ_192K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 2;
            }

            break;

        case _AUDIO_FREQ_256K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 3;
            }

            break;

        case _AUDIO_FREQ_352_8K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 3;
            }

            break;

        case _AUDIO_FREQ_384K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 3;
            }

            break;

        case _AUDIO_FREQ_512K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE >> 4;
            }

            break;

        case _AUDIO_FREQ_705_6K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE >> 4;
            }

            break;

        case _AUDIO_FREQ_768K:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE >> 4;
            }

            break;

        case _AUDIO_FREQ_NO_AUDIO:
        default:

            if(enumPortType == _PORT_DP)
            {
                ucSCode = _DP_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }
            else if(enumPortType == _PORT_HDMI)
            {
                ucSCode = _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE;
            }

            break;
    }

    return ucSCode;
}

//--------------------------------------------------
// Description  : SPDIF/IIS Output By Channel Allocation
// Input Value  : Channel Allocation
// Output Value : Which channel need active
//--------------------------------------------------
BYTE ScalerAudioChannelOutputSel(BYTE ucCa)
{
    // ucRseult[0/1/2/3] = SPDIF/IIS Lane 4/3/2/1
    BYTE ucResult = 0x0F;

    switch(ucCa)
    {
        case 0x01:
        case 0x02:
        case 0x03:

            // Lane1,2
            ucResult = 0x0C;
            break;

        case 0x04:
        case 0x08:

            // Lane1,3
            ucResult = 0x0A;
            break;

        case 0x05:
        case 0x06:
        case 0x07:
        case 0x09:
        case 0x0A:
        case 0x0B:

            // Lane1,2,3
            ucResult = 0x0E;
            break;

        case 0x14:

            // Lane1,4
            ucResult = 0x09;
            break;

        case 0x15:
        case 0x16:
        case 0x17:

            // Lane1,2,4
            ucResult = 0x0D;
            break;

        case 0x0C:
        case 0x10:
        case 0x18:
        case 0x1C:
        case 0x24:
        case 0x26:

            // Lane1,3,4
            ucResult = 0x0B;
            break;

        case 0x0D:
        case 0x0E:
        case 0x0F:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x25:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:

            // Lane1,2,3,4
            ucResult = 0x0F;
            break;

        default:
            break;
    }

    return ucResult;
}

#if(_LINE_IN_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_NONE)
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current Audio Port For Output Type
// Input Value  : None
// Output Value : audio port
//--------------------------------------------------
BYTE ScalerAudioGetDigitalAudioPort_EXINT0(EnumAudioOutputType enumAudioOutput) using 1
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:

            return (ScalerGetBit_EXINT(P6F_01_MUX_DA_DVC_IN, (_BIT2 | _BIT1 | _BIT0)));

        case _AUDIO_I2S_OUT:

            return (ScalerGetBit_EXINT(P6F_00_MUX_DIG_OUT, (_BIT6 | _BIT5 | _BIT4)) >> 4);

        case _AUDIO_SPDIF_OUT:

            return (ScalerGetBit_EXINT(P6F_00_MUX_DIG_OUT, (_BIT2 | _BIT1 | _BIT0)));

#if(_DP_TX_SUPPORT == _ON)
        case _AUDIO_DPTX_OUT:

            return (ScalerGetBit_EXINT(P6F_02_MUX_DP_I2S_IN, (_BIT2 | _BIT1 | _BIT0)));
#endif

        default:
            break;
    }

    return _AUDIO_FROM_D0_PORT;
}
#endif

//--------------------------------------------------
// Description  : Get Current DAC Input Source
// Input Value  : None
// Output Value : _LINE_IN_AUDIO/ _DIGITAL_AUDIO
//--------------------------------------------------
EnumAudioInputSource ScalerAudioGetInputSource_EXINT0(void) using 1
{
    return ((ScalerGetBit_EXINT(P6_D1_DA_MUTE, _BIT3) == 0x00) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
}
#endif

//--------------------------------------------------
// Description  : Get Current DAC Input Source
// Input Value  : None
// Output Value : _LINE_IN_AUDIO/ _DIGITAL_AUDIO
//--------------------------------------------------
EnumAudioInputSource ScalerAudioGetInputSource(void)
{
    return ((ScalerGetBit(P6_D1_DA_MUTE, _BIT3) == 0x00) ? _DIGITAL_AUDIO : _LINE_IN_AUDIO);
}
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Audio DAC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACInitial(void)
{
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT1 | _BIT0));

#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
    // Power On for Line Out Power
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT5, _BIT5);
#else
    // Power OFF for Line Out Power
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT5, 0x00);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
    // Power On for HeadFone Power
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT4, _BIT4);
#else
    // Power OFF for HeadFone Power
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT4, 0x00);
#endif

    // Set DAC Clock Divider, Enable Depop Clock and Set Depop Clock
    ScalerSetByte(P6_D4_DA_CLK_CTRL, 0x12);

    // Power On Depop Circuit and Set Vcm Voltage as 1.65V
    ScalerSetByte(P6_C1_REG_DAC_POWER1, 0xF1);

    // Set DAC Dither Function
    ScalerSetBit(P6_D0_DA_CTRL, ~(_BIT5 | _BIT4), (_DAC_DITHER_FUNCTION_LEVEL << 4));

    // Mute DAC and Set DAC Clock Source
    ScalerSetBit(P6_D1_DA_MUTE, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

    // Set DAC Volume Of L Ch
    ScalerSetByte(P6_D2_DA_GAIN_L, 0x57);

    // Set DAC Volume Of R Ch
    ScalerSetByte(P6_D3_DA_GAIN_R, 0x57);

    // Set Double Buffer
    ScalerSetBit(P6_D2_DA_GAIN_L, ~_BIT7, _BIT7);

#if(_DAC_SPEAKER_OUTPUT_SWAP == _OFF)
    // Set Speaker L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#else
    // Swap Speaker L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#endif

#if(_DAC_HP_OUTPUT_SWAP == _OFF)
    // Set Headphone L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#else
    // Swap Headphone L/R Output
    ScalerSetBit(P6_E0_REG_MUX_ANA_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
#endif
}

//--------------------------------------------------
// Description  : Switch audio output (AOUT / HPOut)
// Input Value  : enumDACOutput
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputSwitch(EnumAudioDACOutput enumDACOutput)
{
    switch(enumDACOutput)
    {
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _ON) && (_DAC_HP_OUTPUT_SUPPORT == _ON))
        case _AUDIO_DAC_OUTPUT_BOTH:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            break;
#endif

#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        case _AUDIO_DAC_OUTPUT_SPEAKER:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), _BIT5);
            break;
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        case _AUDIO_DAC_OUTPUT_HEADPHONE:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), _BIT4);
            break;
#endif

        default:

            ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT5 | _BIT4), 0x00);

            break;
    }
}

//--------------------------------------------------
// Description  : Change Auido DAC State
// Input Value  : Target Audio DAC State
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetState(EnumAudioDACState enumTargetState)
{
    SET_AUDIO_DAC_STATE(enumTargetState);
    SET_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Get Curretn DAC State
// Input Value  : None
// Output Value : Current DAC State
//--------------------------------------------------
EnumAudioDACState ScalerAudioDACGetState(void)
{
    return GET_AUDIO_DAC_STATE();
}

//--------------------------------------------------
// Description  : Get Curretn DAC State Change
// Input Value  : None
// Output Value : TRUE => State Changed
//--------------------------------------------------
bit ScalerAudioDACGetStateChange(void)
{
    return GET_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Clear DAC State Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACClrStateChange(void)
{
    CLR_AUDIO_DAC_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : When Vcm already charge to AVDD/2, Vo(Output Voltage) should charge as Vcm
// Input Value  : bReady
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetVcmReady(bit bReady)
{
    ScalerSetBit(P6_C5_REG_ANA_CTRL, ~_BIT0, (BYTE) bReady);
}

//--------------------------------------------------
// Description  : Transfer depop mode to Normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACNormalToDepop(void)
{
    ScalerAudioDACSetVcmReady(_OFF);

    // Transfer normal to depop operation for AOUT
    ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~_BIT3, 0x00);

    // Transfer normal to depop operation for HP output
    ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~_BIT3, 0x00);

    // Disable AOUT
    ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Disable HP output
    ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    ScalerAudioDACSetVcmReady(_ON);

    ScalerAudioDACSetState(_AUDIO_DAC_DEPOP);
}

//--------------------------------------------------
// Description  : Transfer depop mode to normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACDepopToNormal(void)
{
    // Transfer depop to normal operation for AOUT
    ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~_BIT3, _BIT3);

    // Transfer depop to normal operation and enable driving current for HP output
    ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~_BIT3, _BIT3);

    // Disable Vcm ready
    ScalerAudioDACSetVcmReady(_OFF);

    ScalerAudioDACSetState(_AUDIO_DAC_READY);
}

//--------------------------------------------------
// Description  : Switch AOUT/HPOUT to Normal Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputEnable(void)
{
    ScalerAudioDACSetVcmReady(_OFF);

#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT5) == _BIT5)
    {
        // Enable AOUT
        ScalerSetBit(P6_C6_REG_AOUT_CTRL, ~(_BIT7 | _BIT6), 0x00);
    }
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT4) == _BIT4)
    {
        // Enable HP Output
        ScalerSetBit(P6_C7_REG_HPOUT_CTRL, ~(_BIT7 | _BIT6), 0x00);
    }
#endif

    ScalerAudioDACSetVcmReady(_ON);
}

//--------------------------------------------------
// Description  : Get Current DAC Output Channel
// Input Value  : None
// Output Value : EnumAudioDACOutput
//--------------------------------------------------
EnumAudioDACOutput ScalerAudioDACGetOutput(void)
{
    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        return _AUDIO_DAC_OUTPUT_BOTH;
    }
    else if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == _BIT5)
    {
        return _AUDIO_DAC_OUTPUT_SPEAKER;
    }
    else if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == _BIT4)
    {
        return _AUDIO_DAC_OUTPUT_HEADPHONE;
    }

    return _AUDIO_DAC_OUTPUT_NONE;
}

//--------------------------------------------------
// Description  : Set DAC Output Gain
// Input Value  : EnumAudioDACOutput, ucOutputGain
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain)
{
    if(enumOutputType == _AUDIO_DAC_OUTPUT_SPEAKER)
    {
        // Set AOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_OUT_GAIN, ~(_BIT6 | _BIT5 | _BIT4), (enumOutputGain << 4));
    }
    else if(enumOutputType == _AUDIO_DAC_OUTPUT_HEADPHONE)
    {
        // Set HPOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_OUT_GAIN, ~(_BIT2 | _BIT1 | _BIT0), enumOutputGain);
    }
    else if(enumOutputType == _AUDIO_DAC_OUTPUT_BOTH)
    {
        // Set AOUT and HPOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_OUT_GAIN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 4) | enumOutputGain));
    }
}
#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Initial DVC Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCInitial(void)
{
    // Enable DVC function and counter
    ScalerSetBit(P8_A0_DVC_EN, ~(_BIT7 | _BIT6), _BIT7);

    // Set DVC ZCD window size
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));

    // Select DVC Volume Adjust Type
    ScalerAudioDVCVolumeAdjustType(_DVC_ADJUST_TYPE);

    // Initial DVC gain = 0
    ScalerAudioDVCAdjustVolume(0x00);

    // Initial DVC Mute Control Status
    SET_AUDIO_DVC_MUTE_CTRL_STATUS(_ON);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _OFF)
    // Set Sampling Frequency "48kHz" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

    // Set Channel Count "2 ch" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E3_AD_SPDIF_CS_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable I2S Output for ADC In
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, _BIT7);
#endif

    // Select SPDIF from DVC path
    ScalerSetBit(P6_E1_AD_SPDIF_CTRL, ~_BIT4, _BIT4);

    // Select I2S from DVC path
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT5, _BIT5);

    // Set I2S and SPDIF From DVC path
    ScalerSetBit(P6F_00_MUX_DIG_OUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_AUDIO_FROM_ADC_PORT << 4) | _AUDIO_FROM_ADC_PORT);
#endif
}

//--------------------------------------------------
// Description  : Select DVC Volume Adjust Type
// Input Value  : _DB_GAIN, _VOLUME_STEP_SIZE
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeAdjustType(bit bAdjustType)
{
    if(bAdjustType == _DB_GAIN)
    {
        // Select value mode and set DB gain setp
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DB_GAIN_DOWN_VALUE << 2) | _DB_GAIN_UP_VALUE));

        // Initial volume step size for DB gain mode
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P8_A2_DVC_VA_LSB, 0x01);
    }
    else // _VOLUME_STEP_SIZE
    {
        // Select value mode
        ScalerSetBit(P8_A0_DVC_EN, ~(_BIT4), _BIT4);

        // Set volume step size
        ScalerSetBit(P8_A1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_VOLUME_STEP_SIZE_VALUE));
        ScalerSetByte(P8_A2_DVC_VA_LSB, LOBYTE(_VOLUME_STEP_SIZE_VALUE));
    }
}

//--------------------------------------------------
// Description  : Adjust digital volume for DVC function
// Input Value  : ucVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCAdjustVolume(WORD usVolume)
{
    // DVC gain MSB
    ScalerSetBit(P8_A5_DVC_GAIN_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usVolume));

    // DVC gain LSB  (double buffer)
    ScalerSetByte(P8_A6_DVC_GAIN_LSB, LOBYTE(usVolume));

    // Set Double Buffer
    ScalerSetBit(P8_A7_DVC_GAIN_READ_MSB, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Mute/Unmute for DVC function
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCVolumeMute(bit bMute, WORD usVolume)
{
    ScalerAudioDVCVolumeAdjustType(_DVC_ADJUST_TYPE);

    ScalerAudioDVCSetMuteZCDTimeout(bMute, usVolume, _DVC_ADJUST_TYPE);

    PDATA_WORD(0) = (((WORD) ScalerGetByte(P8_A7_DVC_GAIN_READ_MSB) << 8) | ScalerGetByte(P8_A8_DVC_GAIN_READ_LSB));

    if(bMute == _ON)
    {
        if(PDATA_WORD(0) != 0)
        {
            ScalerAudioDVCAdjustVolume(0);

            PDATA_WORD(1) = 0;

            do
            {
                ScalerTimerDelayXms(1);
                PDATA_WORD(1)++;
            }
            while((ScalerGetBit(P8_A9_DVC_GAIN_DONE, _BIT7) != _BIT7) && (PDATA_WORD(1) < _DVC_VOLUME_MUTE_TIMER));
        }
    }
    else // Unmute
    {
        if(PDATA_WORD(0) != usVolume)
        {
            ScalerAudioDVCAdjustVolume(usVolume);
        }
    }

    SET_AUDIO_DVC_MUTE_CTRL_STATUS(bMute);
}

//--------------------------------------------------
// Description  : Set ZCD Timeout
// Input Value  : bMute, usVolume, bAdjustType
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCSetMuteZCDTimeout(bit bMute, WORD usVolume, bit bAdjustType)
{
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_NO_AUDIO;

    // Get Sampling Rate
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource() == _LINE_IN_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }
    else
#endif
    {
        enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping());
    }

    if(bAdjustType == _DB_GAIN)
    {
        // Get down or up step
        pData[0] = (bMute == _ON) ? (ScalerGetBit(P8_A0_DVC_EN, (_BIT3 | _BIT2)) >> 2) : ScalerGetBit(P8_A0_DVC_EN, (_BIT1 | _BIT0));

        // Get numbers of the volume step for mute or unmute
        PDATA_WORD(0) = _DVC_DB_STEP_NUMBER << pData[0];
    }
    else
    {
        PDATA_WORD(0) = usVolume / _VOLUME_STEP_SIZE_VALUE + 1;
    }

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DVC_VOLUME_MUTE_TIMER / PDATA_WORD(0);

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
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Set ZCD Timeout, only use the type "_VOLUME_STEP_SIZE"
// Input Value  : usVolume
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCSetVolumeZCDTimeout(WORD usVolume)
{
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_NO_AUDIO;

    ScalerAudioDVCVolumeAdjustType(_VOLUME_STEP_SIZE);

    // Get Sampling Rate
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource() == _LINE_IN_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }
    else
#endif
    {
        enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping());
    }

    // Get Current Volume
    PDATA_WORD(0) = ((WORD)(ScalerGetByte(P8_A5_DVC_GAIN_MSB) & 0x3F) << 8) | ((WORD)ScalerGetByte(P8_A6_DVC_GAIN_LSB));

    PDATA_WORD(0) = (PDATA_WORD(0) > usVolume) ? (PDATA_WORD(0) - usVolume) : (usVolume - PDATA_WORD(0));

    PDATA_WORD(0) = PDATA_WORD(0) / _VOLUME_STEP_SIZE_VALUE + 1;

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DVC_VOLUME_ADJUST_TIMER / PDATA_WORD(0);

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
    ScalerSetBit(P8_A3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(P8_A4_DVC_ZC_WIN_CTRL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Get DVC Mute Status
// Input Value  : None
// Output Value : _ON or _OFF
//--------------------------------------------------
bit ScalerAudioDVCGetVolumeMuteStatus(void)
{
    return GET_AUDIO_DVC_MUTE_CTRL_STATUS();
}

//--------------------------------------------------
// Description  : DVC Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDVCResetProc(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
    {
        // Switch Audio DAC State to _AUDIO_DAC_DEPOP
        ScalerAudioDACNormalToDepop();
    }
#endif

    // Reset DVC Counter
    ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);

    // At Least Delay 2 Cycle of 1 / 256 * FS (= 32KHz)
    DELAY_5US();

    // Enable DVC Counter
    ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);

#if(_DIGITAL_AUDIO_OUTPUT_FIX_I2S_PHASE_DELAY == _ON)
    // Disable I2S Block
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, 0x00);

    // At Least Delay 2 Cycle of 1 / FS (= 32KHz)
    DELAY_XUS(70);

    // Enable I2S Block
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, _BIT7);
#endif
}

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle Smapling Frequency Infomation in SPDIF format
// Input Value  : enumAudioSource, ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifChannelStatusProc(EnumAudioInputSource enumAudioSource, BYTE ucInputPort)
{
    if(enumAudioSource == _DIGITAL_AUDIO)
    {
        ScalerAudioSpdifCheckIfSamplingFrequencyChange(ucInputPort);
    }
    else if(enumAudioSource == _LINE_IN_AUDIO)
    {
        ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);
    }
}

//--------------------------------------------------
// Description  : Detect and Change Smapling Frequency Infomation in SPDIF format
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioSpdifCheckIfSamplingFrequencyChange(BYTE ucInputPort)
{
    switch(ScalerAudioSamplingFreqDetect(ucInputPort))
    {
        case _AUDIO_FREQ_PACKET_32K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_32KHZ);

            break;

        case _AUDIO_FREQ_PACKET_44_1K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_44_1KHZ);

            break;

        case _AUDIO_FREQ_PACKET_48K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

            break;

        case _AUDIO_FREQ_PACKET_88_2K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_88_2KHZ);

            break;

        case _AUDIO_FREQ_PACKET_96K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_96KHZ);

            break;

        case _AUDIO_FREQ_PACKET_176_4K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_176_4KHZ);

            break;

        case _AUDIO_FREQ_PACKET_192K:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_192KHZ);

            break;

        default:

            ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_NOT_INDICATED);

            break;
    }
}
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

