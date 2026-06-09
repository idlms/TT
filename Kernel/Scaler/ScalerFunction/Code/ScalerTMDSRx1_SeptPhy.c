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
// ID Code      : ScalerTMDSRx1_SeptPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D1_TMDS_SUPPORT == _ON)
void ScalerTMDSRx1FirstActiveProc(BYTE ucSourceType);
void ScalerTMDSRx1SetDeOnlyModeConfig(EnumDeOnlyConfig enumDeonlyConfig);
EnumDeOnlyConfig ScalerTMDSRx1GetDeOnlyModeConfig(void);
void ScalerTMDSRx1PowerOffProc(void);
void ScalerTMDSRx1TMDSVideoDetectEvent(void);

#if(_D1_HDMI_SUPPORT == _ON)
bit ScalerTMDSRx1HdmiAviPixelRepInfoChanged(void);
bit ScalerTMDSRx1HdmiDeepColorProc(WORD usTmdsClkCnt);
void ScalerTMDSRx1HdmiPacketDetectEvent(void);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
void ScalerTMDSRx1Hdmi2FormatResetEvent(void);
void ScalerTMDSRx1ScrambleStatusReset(void);
void ScalerTMDSRx1ScrambleDetectTimeoutTimerEvent(void);
void ScalerTMDSRx1ScrambleDetectDisable(void);
#endif

#endif

void ScalerTMDSRx1HotPlugLowProc(void);
void ScalerTMDSRx1HotPlugHighProc(WORD usHpdTime);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D1_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1FirstActiveProc(BYTE ucSourceType)
{
    ucSourceType = ucSourceType;
}

//--------------------------------------------------
// Description  : Set Config of TMDS Mac Deonly mode
// Input Value  : None
// Output Value : enumInputPort, enumDeonlyConfig
//--------------------------------------------------
void ScalerTMDSRx1SetDeOnlyModeConfig(EnumDeOnlyConfig enumDeonlyConfig)
{
    // De only enable?
    if((enumDeonlyConfig & _DE_ONLY_DISABLE) == _DE_ONLY_DISABLE)
    {
        ScalerSetBit(P71_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
    }
    else if((enumDeonlyConfig & _DE_ONLY_ENABLE) == _DE_ONLY_ENABLE)
    {
        ScalerSetBit(P71_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
    }

    // Set HS
    if((enumDeonlyConfig & _DE_ONLY_HS_8T) == _DE_ONLY_HS_8T)
    {
        ScalerSetBit(P71_AB_TMDS_ACC2, ~_BIT7, _BIT7);
    }
    else if((enumDeonlyConfig & _DE_ONLY_HS_72T) == _DE_ONLY_HS_72T)
    {
        ScalerSetBit(P71_AB_TMDS_ACC2, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get Config of TMDS Mac Deonly mode
// Input Value  : None
// Output Value : EnumDeOnlyConfig
//--------------------------------------------------
EnumDeOnlyConfig ScalerTMDSRx1GetDeOnlyModeConfig(void)
{
    EnumDeOnlyConfig enumDeConfig = _DE_NO_INDICATED;

    if(ScalerGetBit(P71_A7_TMDS_PWDCTL, _BIT7) == _BIT7)
    {
        enumDeConfig = _DE_ONLY_ENABLE;
    }
    else
    {
        enumDeConfig = _DE_ONLY_DISABLE;
    }

    if(ScalerGetBit(P71_AB_TMDS_ACC2, _BIT7) == _BIT7)
    {
        enumDeConfig |= _DE_ONLY_HS_8T;
    }
    else
    {
        enumDeConfig |= _DE_ONLY_HS_72T;
    }

    return enumDeConfig;
}

//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1PowerOffProc(void)
{
    // Disable EDID read/ SCL toggle IRQ
    MCU_FFE5_DDC1_EDID_IRQ = ((MCU_FFE5_DDC1_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));

    ScalerTMDSRx1FreqDetectDisable();

#if(_D1_HDMI_2_0_SUPPORT == _ON)
    ScalerTMDSRx1ScrambleDetectDisable();
#endif
}
//--------------------------------------------------
// Description  : TMDS video Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1TMDSVideoDetectEvent(void)
{
    CLR_TMDS_RX1_RGBHV_DETECTING();
}

#if(_D1_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect HDMI AVI pixel repetition
// Input Value  : None
// Output Value : _TRUE => Current Info is different from previous setting
//--------------------------------------------------
bit ScalerTMDSRx1HdmiAviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_TMDS_RX1_AVI_PIXEL_REPETITION())
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : HDMI Deep Color Proc
// Input Value  : void
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx1HdmiDeepColorProc(WORD usTmdsClkCnt)
{
    // Setting Deep Color PLL
    if(ScalerTMDSRx1HdmiSetDeepColorPll(usTmdsClkCnt, GET_COLOR_DEPTH()) == _FALSE)
    {
        return _FALSE;
    }

    // Wait for Phase lock
    if(ScalerTMDSRx1HdmiWaitDeepColorPllLock() == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1HdmiPacketDetectEvent(void)
{
    CLR_HDMI_RX1_PACKET_DETECTING();
}

#if(_D1_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Format Reset Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1Hdmi2FormatResetEvent(void)
{
    CLR_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING();
}

//--------------------------------------------------
// Description  : Scramble Status Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1ScrambleStatusReset(void)
{
    // Set Scramble Detect Manual Mode
    ScalerSetBit(P71_38_HDMI_CTRL_38, ~(_BIT4 | _BIT2 | _BIT1), 0x00);

    // Disable Scrambling Status
    ScalerSetDataPortBit(P71_39_HDMI_CTRL_39, _P71_3A_PT_21_PORT_PAGE71_HDMI_SCDC_21, ~_BIT0, 0x00);

    // Clear Scrambling Detection Flag
    ScalerSetBit(P71_01_HDMI_CTRL_01, ~_BIT3, _BIT3);

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_HDMI2_SCRAMBLE_DETECT_TIMEOUT);
}

//--------------------------------------------------
// Description  : Scramble Detect timeout event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1ScrambleDetectTimeoutTimerEvent(void)
{
    // Set Scramble Detect Auto Mode
    ScalerSetBit(P71_38_HDMI_CTRL_38, ~(_BIT4 | _BIT2 | _BIT1), _BIT4);

    ScalerTMDSRx1ScrambleDetectDisable();
}

//--------------------------------------------------
// Description  : TMDS Scramble Detection IRQ Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1ScrambleDetectDisable(void)
{
    // Disable SCDC 0x20 Change IRQ
    ScalerSetBit(P71_26_HDMI_CTRL_26, ~_BIT4, 0x00);
}
#endif

#endif

//--------------------------------------------------
// Description  : HPD Low Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx1HotPlugLowProc(void)
{
    // MHL mode of MHL PORT can not pull HPD
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE))
#endif
    {
        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_EIZO_PS_WAKEUP)
#endif
        {
            ScalerTMDSRx1SwitchSlaveAddr();
        }
    }
}

//--------------------------------------------------
// Description  : HPD High Process
// Input Value  : usHpdTime
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx1HotPlugHighProc(WORD usHpdTime)
{
    // MHL mode of MHL PORT can not pull HPD
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE))
#endif
    {
        ScalerTimerDelayXms(usHpdTime);

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
    }
}
#endif
