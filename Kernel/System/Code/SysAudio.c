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
// ID Code      : SysAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_AUDIO__

#include "SysInclude.h"

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_EMBEDDED_DAC_SUPPORT == _ON)
#define _DAC_VCM_INITIAL_TIME                       SEC(0.1)
#define _DAC_VCM_CHARGE_TIME                        SEC(0.5)
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
StructAudioInfoType g_stAudioInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysAudioHandler(void);
EnumAudioState SysAudioGetAudioState(void);
void SysAudioPowerProc(EnumPowerAction enumSwitch);
void SysAudioMuteProc(bit bMute);
void SysAudioOutputProc(bit bEnable);
void SysAudioAnalogAudioHandler(void);
void SysAudioDigitalAudioHandler(void);
void SysAudioChangeAudioState(EnumAudioState enumAudioState);
void SysAudioInitial(void);
void SysAudioSetUserDefineAudioFrequency(void);

#if(_DP_SUPPORT == _ON)
void SysAudioDpAudioSecDataResetProc(BYTE ucInputPort);
#endif

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
void SysAudioFwTrackingHandler(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
void SysAudioSleepAudioHandler(void);

#if((_LINE_IN_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
bit SysAudioGetSleepAudioStatusForLineIn(void);
#endif
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
void SysAudioInternalGenTestProc(bit bOn);
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
void SysAudioTtsCheckPlaybackAcitveEvent(void);
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Audio handler. Main audio control flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioHandler(void)
{
	if(PCB_HEADPHONE_JACK_DETECT() != g_bHPJackState)	// Headphone detect
	{
		if(PCB_HEADPHONE_JACK_DETECT() == _HP_JACK_ON)
		{
			g_bHPJackState = _HP_JACK_ON;
			PCB_AMP_SHUTDOWN(_AMP_SHUTDOWN_ON);
			printf("HP Jack On\r\n");
		}
		else
		{
			g_bHPJackState = _HP_JACK_OFF;
			PCB_AMP_SHUTDOWN(_AMP_SHUTDOWN_OFF);
			printf("HP Jack Off\r\n");
		}
	}	
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
    {
        return;
    }
#endif

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
    SysAudioFwTrackingHandler();
#endif

    SysAudioAnalogAudioHandler();

    SysAudioDigitalAudioHandler();

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    // Check TTS Event Trigger or Not
    SysAudioTtsCheckPlaybackAcitveEvent();
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

    switch(GET_AUDIO_STATE())
    {
        case _AUDIO_STATUS_PREPARING:

            if(GET_AUDIO_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_STATE_CHANGE();
                SET_AUDIO_PLAYBACK_SEARCH_INDEX(0x0F);
            }

            if(UserCommonInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
#if(_HDMI_SUPPORT == _ON)
                if(ScalerAudioDigitalAudioSourceType() == _SOURCE_HDMI)
                {
                    ScalerAudioHdmiI2sSpdifChannelOutputSelect(_AUDIO_SELECT_BY_CA_MODE, ScalerAudioGetDigitalAudioPortMapping());
                }
#endif

                ScalerAudioDigitalEnable(ScalerAudioGetDigitalAudioPortMapping());
                SysAudioOutputProc(_ENABLE);

                DebugMessageAudio("Switch to Audio Playback", 0x00);
                SysAudioChangeAudioState(_AUDIO_STATUS_PLAYBACK);

                // Update User Define Frequency When No Audio
                SysAudioSetUserDefineAudioFrequency();

                // Set User Define Frequency When No Audio except input port
                ScalerAudioSyncUserDefineFrequency();
            }

            break;

        case _AUDIO_STATUS_PLAYBACK:

            if(GET_AUDIO_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_STATE_CHANGE();
                SET_AUDIO_PLAYBACK_SEARCH_INDEX(g_ucSearchIndex);
            }

            if(UserCommonInterfaceGetAudioReadyToPlayStatus() == _FALSE)
            {
                SysAudioOutputProc(_DISABLE);
                ScalerAudioDigitalReset(ScalerAudioGetDigitalAudioPortMapping());

#if(_HDMI_SUPPORT == _ON)
                if(ScalerAudioDigitalAudioSourceType() == _SOURCE_HDMI)
                {
                    ScalerAudioHdmiI2sSpdifChannelOutputSelect(_AUDIO_DEFAULT_MODE, ScalerAudioGetDigitalAudioPortMapping());
                }
#endif

                DebugMessageAudio("Switch to Audio Preparing", 0x00);
                SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
            }

            break;

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
        case _AUDIO_STATUS_TTS_PLAYBACK:

            // Check TTS Play Fail
            if(ScalerAudioTtsPlaybackStableCheck() == _FALSE)
            {
                // Recover TTS
                ScalerAudioTtsRecoverProc();

                SysAudioOutputProc(_DISABLE);
                ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

                DebugMessageAudio("TTS Back to Audio Preparing", 0x02);
                SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
            }


            // Check TTS Play Done
            if(ScalerAudioTtsGetPlayDoneStatus() == _TRUE)
            {
                // Recover TTS
                ScalerAudioTtsRecoverProc();

                if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
                {
                    DebugMessageAudio("TTS Back to Audio Playback", 0x03);
                    SysAudioChangeAudioState(_AUDIO_STATUS_PLAYBACK);
                }
                else
                {
                    SysAudioOutputProc(_DISABLE);
                    ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

                    // Update User Define Frequency When No Audio
                    SysAudioSetUserDefineAudioFrequency();

                    // Set User Define Frequency When No Audio except input port
                    ScalerAudioSyncUserDefineFrequency();

                    DebugMessageAudio("TTS Back to Audio Preparing", 0x04);
                    SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
                }
            }

            break;

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

        case _AUDIO_STATUS_POWER_OFF:
        default:
            break;
    }

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    SysAudioSleepAudioHandler();
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio
// Input Value  : None
// Output Value : Node
//--------------------------------------------------
EnumAudioState SysAudioGetAudioState(void)
{
    return GET_AUDIO_STATE();
}

//--------------------------------------------------
// Description  : Audio Power Process
// Input Value  : None
// Output Value : Node
//--------------------------------------------------
void SysAudioPowerProc(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // Update User Define Frequency When No Audio
            SysAudioSetUserDefineAudioFrequency();

            SysAudioInitial();

            // Add User interface function
            UserInterfaceAdjustAudioPowerProc(_POWER_STATUS_NORMAL);

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
            UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(UserInterfaceGetAudioSource()));
#endif
            SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

            // Mute Audio
            SysAudioOutputProc(_DISABLE);
            
            // Reset Digital Audio
            ScalerAudioDigitalReset(ScalerAudioGetDigitalAudioPortMapping());

            // Add User interface function
            UserInterfaceAdjustAudioPowerProc(_POWER_STATUS_OFF);

            // Disable Audio
            ScalerAudioDisable();

            SysAudioChangeAudioState(_AUDIO_STATUS_POWER_OFF);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            // Mute Audio
            SysAudioOutputProc(_DISABLE);

            // Reset Digital Audio
            ScalerAudioDigitalReset(ScalerAudioGetDigitalAudioPortMapping());

            // Add User interface function
            UserInterfaceAdjustAudioPowerProc(_POWER_STATUS_SAVING);

            // Disable Audio
            ScalerAudioDisable();

            SysAudioChangeAudioState(_AUDIO_STATUS_POWER_OFF);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Audio Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioMuteProc(bit bMute)
{
    if(bMute == _ON)
    {
        if(ScalerAudioDVCGetVolumeMuteStatus() == _OFF)
        {
            UserInterfaceAdjustAudioAmpMuteProc(_ON);

            ScalerAudioMuteProc(_ON, UserInterfaceGetAudioVolume());
        }
    }
    else
    {
#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        if((ScalerAudioDVCGetVolumeMuteStatus() == _ON) && (UserInterfaceGetAudioMuteStatus() == _OFF))
#else
        if(ScalerAudioDVCGetVolumeMuteStatus() == _ON)
#endif
        {
            ScalerAudioMuteProc(_OFF, UserInterfaceGetAudioVolume());

            UserInterfaceAdjustAudioAmpMuteProc(_OFF);
        }
    }
}

//--------------------------------------------------
// Description  : Audio Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioOutputProc(bit bEnable)
{
    if(bEnable == _DISABLE)
    {
#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        UserInterfaceAudioExternalCodecProc(_ENABLE);
#endif

        SysAudioMuteProc(_OFF);
    }
    else
    {

        SysAudioMuteProc(_ON);

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        UserInterfaceAudioExternalCodecProc(_DISABLE);
#endif
    }
}

//--------------------------------------------------
// Description  : Audio Analog Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioAnalogAudioHandler(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)

    if((ScalerAudioDACGetState() != _AUDIO_DAC_OFF) && (ScalerAudioDACGetState() != _AUDIO_DAC_INITIAL) && (ScalerAudioDACGetState() != _AUDIO_DAC_CHARGE))
    {
        // User want to change DAC Input / Output
        if((ScalerAudioGetAudioInputPortChanged(UserInterfaceGetAudioSource(), SysSourceGetInputPort()) == _TRUE) ||
           (ScalerAudioDACGetOutput() != UserInterfaceGetAudioDACOutput()))
        {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_LINE_IN_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            if(SysAudioGetSleepAudioStatusForLineIn() == _FALSE)
#endif
            {
                SysAudioOutputProc(_DISABLE);
                ScalerAudioDigitalReset(ScalerAudioGetDigitalAudioPortMapping());

                SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
            }

            if(ScalerAudioDACGetOutput() != UserInterfaceGetAudioDACOutput())
            {
                DebugMessageAudio("Audio Dac Switch Output", ScalerAudioDACGetOutput());

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                ScalerAudioDACNormalToDepop();

                ScalerAudioDACSetVcmReady(_OFF);
                ScalerAudioDACSetState(_AUDIO_DAC_CHARGE);
            }
            else
            {
#if(_LINE_IN_SUPPORT == _ON)
                DebugMessageAudio("Audio Switch Input", ScalerAudioGetInputSource());
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_LINE_IN_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
                if(SysAudioGetSleepAudioStatusForLineIn() == _TRUE)
                {
                    ScalerAudioSourceInputSwitch(UserInterfaceGetAudioSource(), SysSourceGetInputPort());
                }
                else
#endif
                {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                    if((GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE) || (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT) ||
                       ((UserInterfaceGetAudioStandAloneStatus() == _TRUE) &&
                        (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO) &&
                        (ScalerAudioGetDpStandaloneAudioStatus(SysSourceGetInputPort()) == _TRUE)))
#elif((_SLEEP_AUDIO_SUPPORT == _ON) && (_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
                    if((GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE) || (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT) ||
                       ((UserInterfaceGetAudioStandAloneStatus() == _TRUE) &&
                        (UserInterfaceGetAudioSource() == _LINE_IN_AUDIO) &&
                        (GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)))
#else
                    if((GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE) || (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT))
#endif
                    {
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                        ScalerAudioDACNormalToDepop();

                        ScalerAudioSourceInputSwitch(UserInterfaceGetAudioSource(), SysSourceGetInputPort());

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
                        UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(UserInterfaceGetAudioSource()));
#endif
                    }
                }
            }
        }
    }

    switch(ScalerAudioDACGetState())
    {
        case _AUDIO_DAC_OFF:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();
            }

            break;

        case _AUDIO_DAC_INITIAL:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("Audio Dac Initial", _AUDIO_DAC_INITIAL);

                ScalerTimerActiveTimerEvent(_DAC_VCM_INITIAL_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL);
            }

            break;

        case _AUDIO_DAC_CHARGE:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("Audio Dac Charge", _AUDIO_DAC_CHARGE);

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);

                ScalerAudioDACOutputSwitch(UserInterfaceGetAudioDACOutput());
                ScalerAudioDACSetVcmReady(_ON);

                ScalerTimerActiveTimerEvent(_DAC_VCM_CHARGE_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);
            }

            break;

        case _AUDIO_DAC_DEPOP:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                DebugMessageAudio("Audio Dac Depop", _AUDIO_DAC_DEPOP);

                if(UserInterfaceGetAudioDACKeepDepopState() == _FALSE)
                {
                    ScalerAudioDACClrStateChange();

                    ScalerAudioDACOutputEnable();

                    ScalerTimerActiveTimerEvent(_DAC_DEPOP_TO_NORMAL_WAIT_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                }
            }

            break;

        case _AUDIO_DAC_READY:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("Audio Dac Ready", _AUDIO_DAC_READY);
            }
            break;

        default:
            break;
    }

#else

    // Change Audio Input Port
    if(ScalerAudioGetAudioInputPortChanged(UserInterfaceGetAudioSource(), SysSourceGetInputPort()) == _TRUE)
    {
        SysAudioOutputProc(_DISABLE);
        ScalerAudioDigitalReset(ScalerAudioGetDigitalAudioPortMapping());

        if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE)
        {
            ScalerAudioSourceInputSwitch(UserInterfaceGetAudioSource(), SysSourceGetInputPort());

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
            UserInterfaceSwapExternalAudioCodecInput(ScalerAudioGetI2sOutputNeedToSwap(UserInterfaceGetAudioSource()));
#endif
        }

        SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
    }

#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Digital Audio Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioDigitalAudioHandler(void)
{
    if(UserInterfaceAudioGetOutputMuteStatus() == _AUDIO_MUTE_ON)
    {
        ScalerAudioDigitalOutputMute(_ON);
    }
    else
    {
        ScalerAudioDigitalOutputMute(_OFF);
    }

    ScalerAudioDigitalDetect();

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    ScalerAudioSpdifChannelStatusProc(UserInterfaceGetAudioSource(), SysSourceGetInputPort());
#endif
}

//--------------------------------------------------
// Description  : Change Audio State
// Input Value  : Target Audio State
// Output Value : None
//--------------------------------------------------
void SysAudioChangeAudioState(EnumAudioState enumAudioState)
{
    SET_AUDIO_STATE(enumAudioState);
    SET_AUDIO_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Audio Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioInitial(void)
{
    ScalerAudioInitial();

    ScalerAudioSourceInputSwitch(UserInterfaceGetAudioSource(), SysSourceGetInputPort());

#if(_EMBEDDED_DAC_SUPPORT == _ON)

    ScalerAudioDACSetVcmReady(_ON);

    ScalerAudioDACSetState(_AUDIO_DAC_INITIAL);
#endif
}

//--------------------------------------------------
// Description  : Audio Frequency Set By User Define
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioSetUserDefineAudioFrequency(void)
{
    // get freq from userinterface
    EnumAudioSamplingFreqType enumAudioFreq = UserCommonInterfaceAudioUpdateUserSamplingFreq();

    ScalerAudioSetUserDefineAudioFrequency(enumAudioFreq);
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Audio Secondary Data Reset Process
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void SysAudioDpAudioSecDataResetProc(BYTE ucInputPort)
{
    if(ScalerAudioDPGetMuteProc(ucInputPort) == _TRUE)
    {
        SysAudioOutputProc(_DISABLE);
        ScalerAudioDigitalReset(ScalerAudioGetDigitalAudioPortMapping());

#if(_EMBEDDED_DAC_SUPPORT == _ON)
        ScalerAudioDACNormalToDepop();
#endif

        SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
    }

    ScalerDpSecDataReset(ucInputPort);
}
#endif

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Fw Tracking Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioFwTrackingHandler(void)
{
    ScalerAudioFwTrackingHandler();
}
#endif


#if(_SLEEP_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Sleep Audio Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioSleepAudioHandler(void)
{
    if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
    {
        if(GET_AUDIO_STATE() == _AUDIO_STATUS_PREPARING)
        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if((UserInterfaceGetAudioSource() == _DIGITAL_AUDIO) &&
               (ScalerAudioGetDigitalAudioSource(SysSourceGetInputPort()) == _DIGITAL_AUDIO_SOURCE_DP))
            {
                SET_AUDIO_PLAYBACK_SEARCH_INDEX(g_ucSearchIndex);

                ScalerAudioDpAudioEnable(_ENABLE, SysSourceGetInputPort());

                DebugMessageAudio("Sleep Audio Playback Index", GET_AUDIO_PLAYBACK_SEARCH_INDEX());
            }
#endif

#if((_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
            SET_AUDIO_PLAYING_ALONE();

            return;
#endif
        }
        else if(GET_AUDIO_STATE() == _AUDIO_STATUS_PLAYBACK)
        {
#if((_LINE_IN_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
            {
                SET_AUDIO_PLAYING_ALONE();

                return;
            }
#endif

#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if((UserInterfaceGetAudioSource() == _DIGITAL_AUDIO) && (ScalerAudioGetDigitalAudioSource(SysSourceGetInputPort()) == _DIGITAL_AUDIO_SOURCE_DP))
            {
                SET_AUDIO_PLAYING_ALONE();

                return;
            }
#endif
        }
    }

    CLR_AUDIO_PLAYING_ALONE();
}

#if((_LINE_IN_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
//--------------------------------------------------
// Description  : Get Sleep Audio Changed for Line in
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysAudioGetSleepAudioStatusForLineIn(void)
{
    return ((UserInterfaceGetAudioSource() == _LINE_IN_AUDIO) && (ScalerAudioGetInputSource() == _LINE_IN_AUDIO) && (GET_AUDIO_PLAYING_ALONE() == _TRUE));
}
#endif
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Internal Audio Gen Test Process
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void SysAudioInternalGenTestProc(bit bOn)
{
    SysAudioOutputProc(_DISABLE);

    if(bOn == _ON)
    {
        ScalerAudioDigitalReset(ScalerAudioGetDigitalAudioPortMapping());

        ScalerAudioInternalAudioGenSwitch(_ON, SysSourceGetInputPort());

        ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, SysSourceGetInputPort());

        ScalerAudioDigitalVolumeMute(_OFF, UserInterfaceGetAudioVolume());
    }
    else
    {
        ScalerAudioInternalAudioGenSwitch(_OFF, SysSourceGetInputPort());

        ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, SysSourceGetInputPort());

        ScalerAudioInternalAudioGenReset(SysSourceGetInputPort());

        SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
    }
}
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
//--------------------------------------------------
// Description  : Check TTS Playback Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioTtsCheckPlaybackAcitveEvent(void)
{
    if(GET_TTS_PLAYBACK_EVENT_ACTIVE() == _TRUE)
    {
        // Active TTS WD Event
        ScalerTimerActiveTimerEvent(_SCALER_WD_TIMER_EVENT_AUDIO_TTS_PLAYBACK_PROC);

        if(SysAudioGetAudioState() == _AUDIO_STATUS_PREPARING)
        {
        }

        SysAudioChangeAudioState(_AUDIO_STATUS_TTS_PLAYBACK);
    }
}
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#endif // End of #if(_AUDIO_SUPPORT == _ON)
