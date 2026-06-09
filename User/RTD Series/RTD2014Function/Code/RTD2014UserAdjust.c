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
// ID Code      : RTD2014UserAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST__
#define __USER_PANEL__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
#define _HLWIN_TYPE5_MOVE_TIME                      SEC(0.01)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// IR TABLE
//----------------------------------------------------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE code tIR_INITIAL_TABLE[] =
{
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
    #include "IRRemote/NEC_DTV328.h"
#elif(_IR_PROTOCAL == _IR_NEC_TYPE1)
	#include "IRRemote/NEC_DTV328.h"
#elif(_IR_PROTOCAL == _IR_SONY_B102P)
    #include "IRRemote/SONY_B102P.h"

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
    #include "IRRemote/PHILIPS_RC6.h"

#elif(_IR_PROTOCAL == _IR_LG_TYPE)
	#include "IRRemote/NEC_DTV328.h"
#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
bit g_bHLWinRLMove = _RIGHT;
WORD g_usHLWinHPos;
WORD g_usHLWinHWidth;
WORD g_usHLWinVPos;
WORD g_usHLWinVHeight;
#endif


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//-------------------------------------------------------
// Adjust Backlight
//-------------------------------------------------------
void UserAdjustBacklight(WORD usBacklight);

//-------------------------------------------------------
// Dp Load Edid Related
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort);
#endif

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
void UserAdjustAudioMuteSwitch(void);
void UserAdjustAudioVolume(BYTE ucVolume);
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// DCC
//-------------------------------------------------------
#if(_DCC_FUNCTION == _ON)
void UserAdjustDCC(BYTE ucColorEffect);
#endif // End of #if(_DCC_FUNCTION == _ON)

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
#if(_ICM_SUPPORT == _ON)
void UserAdjustICM(BYTE ucColorEffect);
#endif

#if(_SCM_SUPPORT == _ON)
void UserAdjustSCM(BYTE ucColorEffect);
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
void UserAdjustColorEffectMode(void);
#endif

//-------------------------------------------------------
// CTS / BRI
//-------------------------------------------------------
#if(_CONTRAST_SUPPORT == _ON)
void UserAdjustContrast(WORD usContrast);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
void UserAdjustBrightness(WORD usBrightness);
#endif

//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION == _ON)
void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat);
#endif

//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------

//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_SUPPORT == _ON)
void UserAdjustOD(void);
#endif

//-------------------------------------------------------
// Highlight window
//-------------------------------------------------------
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
void UserAdjustHLWinType(BYTE ucHLWinType);
void UserAdjustHLWinType5Move(void);
void UserAdjustHighLightWindowEffectSpace(void);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
void UserAdjustFREESYNCODMeasure(void);
#endif


//-------------------------------------------------------
// HW IR Mode
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
void UserAdjusIR(void);
#endif

//-------------------------------------------------------
// DP
//-------------------------------------------------------
#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
void UserAdjustEmbeddedDpSwitch(void);
#endif

//-------------------------------------------------------
// Pixel Shift
//-------------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
void UserAdjustPixelShifting(BYTE ucPixelShift);
#endif

//-------------------------------------------------------
// SDRToHDR
//-------------------------------------------------------
#if(_SDR_TO_HDR_SUPPORT == _ON)
void UserAdjustSDRToHDR(bit bOn);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#define BACKLIGHT_NON_LINEAR_CURVE_GAMMA                   2.33f

void UserAdjustBacklight(WORD usBacklight)
{
    if(GET_OSD_BACKLIGHT_CONTROL())
		usBacklight = _BACKLIGHT_MAX() - usBacklight;
		
        // Adjust backlight by changing PWM duty
		PCB_BACKLIGHT_PWM(usBacklight);
	DebugMessageSystem("usBacklight",usBacklight);
}

//----------------------------------------------------------------------------
// Not Kernel Related Function
//----------------------------------------------------------------------------

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : ucInputPort
// Output Value : Edid Index
//--------------------------------------------------
EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort)
{
    BYTE ucIndex = 0;
    BYTE ucDpResolution = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((GET_OSD_FREE_SYNC_STATUS() == _ON))
    {
        ucIndex += ((_DP_HDR10_SUPPORT == _ON) ? 0x06 : 0x03);
    }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
    if((UserInterfaceHDRGetHDR10ModeStatus(ucInputPort) != _HDR10_MODE_OFF))
    {
        ucIndex += 0x03;
    }
#endif

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);
            break;
        case _D1_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D1_SELECT);
            break;
        case _D2_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D2_SELECT);
            break;
        case _D6_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D6_SELECT);
            break;
        default:
            break;
    }

    switch(ucDpResolution)
    {
        case _DP_EDID_1080P:
            break;

        case _DP_EDID_2560_1440:
            ucIndex += 0x01;
            break;

        case _DP_EDID_4K2K_60HZ:
            ucIndex += 0x02;
            break;

        default:
            break;
    }

    return ucIndex;
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mute/Unmute Aduio Volume
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserAdjustAudioMuteSwitch(void)
{
    SysAudioMuteProc(UserInterfaceGetAudioMuteStatus());
}

//--------------------------------------------------
// Description  : Adjust Aduio Volume
// Input Value  : ucVolume
// Output Value : Node
//--------------------------------------------------
void UserAdjustAudioVolume(BYTE ucVolume)
{
	//if(ucVolume < 15)
	//{
	//	ucVolume = ucVolume *3;	//171213

	//}
	//else
	//{
	//	ucVolume = ucVolume *3;	//171213
	//	ucVolume += 10; 
	//}	

    ScalerAudioDigitalAdjustVolume(UserAdjustAudioVolumeMapping(ucVolume));

	ScalerAudioExternAdjVolume(GET_OSD_VOLUME()); //Eric_171009_02
}

//--------------------------------------------------
// Description  : OSD Volume Mapping to Real Value
// Input Value  : usVolume
// Output Value : usVolume
//--------------------------------------------------
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
    {
        return (UserCommonAdjustPercentToRealValue(ucVolume, _LINE_IN_VOLUME_MAX, _LINE_IN_VOLUME_MIN, _LINE_IN_VOLUME_CENTER));
    }
    else
#endif // End of #if(_LINE_IN_SUPPORT == _ON)
    {
        return (UserCommonAdjustPercentToRealValue(ucVolume, _DIGITAL_VOLUME_MAX, _DIGITAL_VOLUME_MIN, _DIGITAL_VOLUME_CENTER));
    }
}
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set DCC Table
// Input Value  : Request DCC Table
// Output Value : None
//--------------------------------------------------
void UserAdjustDCC(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorDCCAdjust(tDCC_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_DCC_FUNCTION == _ON)


#if(_ICM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set ICM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustICM(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorICMLoadTable(tICM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_ICM_SUPPORT == _ON)

#if(_SCM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SCM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSCM(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorSCMLoadTable(tSCM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_SCM_SUPPORT == _ON)

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustColorEffectMode(void)
{
    BYTE ucIndex = 0;
    BYTE ucBackupSixColor = 0;
    BYTE ucBackupHue = 0;
    BYTE ucBackupSaturation = 0;

    ucBackupSixColor = GET_OSD_SIX_COLOR();
    ucBackupHue = GET_OSD_SIX_COLOR_HUE();
    ucBackupSaturation = GET_OSD_SIX_COLOR_SATURATION();

    switch(GET_OSD_COLOR_EFFECT())
    {
        case _COLOREFFECT_STANDARD:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif
            break;

        case _COLOREFFECT_USER:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(ucIndex);
                ScalerColorSixColorAdjust(ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial();
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:
 //       case _COLOREFFECT_FPS :
 //       case _COLOREFFECT_RTS:

            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(GET_OSD_COLOR_EFFECT());
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(GET_OSD_COLOR_EFFECT());
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(GET_OSD_COLOR_EFFECT());
#endif


#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_ON);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_ON);
#endif
            break;

        default:
            break;
    }

    SET_OSD_SIX_COLOR(ucBackupSixColor);
    SET_OSD_SIX_COLOR_HUE(ucBackupHue);
    SET_OSD_SIX_COLOR_SATURATION(ucBackupSaturation);
}
#endif // End of #if(_SIX_COLOR_SUPPORT == _ON)

#if(_CONTRAST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Contrast
// Input Value  : 12 bit input, old 8 bit contrast input value must left shift 4 bit
//                0 (00h) ~ 1(800h) ~  2(FFFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustContrast(WORD usContrast)
{
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    WORD pusData[6] = {0};

#if(_TECNINT_DICOM)
	if(GET_OSD_GAMMA() > _GAMMA_24)
		return;
#endif
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    pusData[3] = 0x800;
    pusData[4] = 0x800;
    pusData[5] = 0x800;
#else
    pusData[3] = 0x80;
    pusData[4] = 0x80;
    pusData[5] = 0x80;
#endif

#else
    WORD pusData[3] = {0};
#endif

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    pusData[0] = (WORD)(((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048);
    pusData[1] = (WORD)(((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048);
    pusData[2] = (WORD)(((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048);

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // 10-bit Panel
        pusData[0] = UserCommonAdjust10bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust10bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust10bitPanelCompensate(pusData[2]);
    }

#else
    pusData[0] = (WORD)(((DWORD)g_stColorProcData.usColorTempR * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempR * usContrast / 128);
    pusData[1] = (WORD)(((DWORD)g_stColorProcData.usColorTempG * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempG * usContrast / 128);
    pusData[2] = (WORD)(((DWORD)g_stColorProcData.usColorTempB * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempB * usContrast / 128);

#endif

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
        ScalerColorContrastAdjust(_CONTRAST_COEF_B, &pusData[3]);
    }
    else
    {
        ScalerColorContrastAdjust(_CONTRAST_COEF_B, pusData);
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, &pusData[3]);
    }
#else
    ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
#endif

    ScalerColorContrastEnable(_FUNCTION_ON);
}
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Brightness
// Input Value  : 10 bit input, old 8 bit brightness input value must left shift 2 bit
//                -2048(00h) ~ 0(200h) ~  +2044(3FFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustBrightness(WORD usBrightness)
{
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    WORD pusData[6] = {0};

#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
    pusData[3] = 0x200;
    pusData[4] = 0x200;
    pusData[5] = 0x200;
#else
    pusData[3] = 0x80;
    pusData[4] = 0x80;
    pusData[5] = 0x80;
#endif

#else
    WORD pusData[3] = {0};
#endif

    pusData[0] = usBrightness;
    pusData[1] = usBrightness;
    pusData[2] = usBrightness;

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusData);
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, &pusData[3]);
    }
    else
    {
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, pusData);
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, &pusData[3]);
    }
#else
    ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusData);
#endif

    ScalerColorBrightnessEnable(_FUNCTION_ON);
}
#endif


#if(_GLOBAL_HUE_SATURATION == _ON)
//--------------------------------------------------
// Description  : Adjust Global Hue Saturation
// Input Value  : Hue and Saturation
// Output Value : None
//--------------------------------------------------
void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat)  // for OSD Adjust & Dianliang:  Display Off & ON
{
    UserCommonAdjustGlobalHueSat(_DEFAULT_HUE - shHue, usSat);
}
#endif  // Enf of #if(_GLOBAL_HUE_SATURATION == _ON)

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load OD LUT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustOD(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
    {
        ScalerODLoadLUT(tOD_FREESYNC_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
    else
#endif
    {
        ScalerODLoadLUT(tOD_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
}
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust High Light Window
// Input Value  : HLWinType
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType(BYTE ucHLWinType)
{
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

    if(ucHLWinType == _HL_WIN_OFF)
    {
        return;
    }

    if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)
    {
        g_usHLWinHPos = 0;
    }
    else
    {
        g_usHLWinHPos = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
    }

    if(GET_MDOMAIN_OUTPUT_VHEIGHT() == _PANEL_DV_HEIGHT)
    {
        g_usHLWinVPos = 0;
    }
    else
    {
        g_usHLWinVPos = (_PANEL_DV_HEIGHT - GET_MDOMAIN_OUTPUT_VHEIGHT()) / 2;
    }

    switch(ucHLWinType)
    {
        case _HL_WIN_1:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;

            break;

        case _HL_WIN_2:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;

            break;

        case _HL_WIN_3:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;

            break;

        case _HL_WIN_4:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;
            g_usHLWinHPos = ((GET_MDOMAIN_OUTPUT_HWIDTH() - g_usHLWinHWidth) / 2) + ((_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2) - 1;
            g_usHLWinVPos = (GET_MDOMAIN_OUTPUT_VHEIGHT() - g_usHLWinVHeight) / 2 - 1;

            break;

        case _HL_WIN_5:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 6;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;
            g_usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() - g_usHLWinHWidth) / 2;

            ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

            break;

        default:

            break;
    }

    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NONE);
}

//--------------------------------------------------
// Description  : High Light Window Type5 Move
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType5Move(void)
{
    WORD usNonFullScreenOffset = 0;

    if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)
    {
        // Full screen
        usNonFullScreenOffset = 0;
    }
    else
    {
        // Non full screen
        usNonFullScreenOffset = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
    }

    if(g_bHLWinRLMove == _RIGHT)
    {
        g_usHLWinHPos++;

        if((GET_MDOMAIN_OUTPUT_HWIDTH() + usNonFullScreenOffset) <= (g_usHLWinHPos + g_usHLWinHWidth + _HL_WIN_BORDER_SIZE))
        {
            g_bHLWinRLMove = _LEFT;
            g_usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() + usNonFullScreenOffset) - (g_usHLWinHWidth + _HL_WIN_BORDER_SIZE);
        }
    }
    else // _LEFT
    {
        g_usHLWinHPos--;

        if(g_usHLWinHPos <= usNonFullScreenOffset)
        {
            g_bHLWinRLMove = _RIGHT;
            g_usHLWinHPos = usNonFullScreenOffset;
        }
    }

    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NO_POLLING);

    ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
}

//--------------------------------------------------
// Description  : Adjust All High Light Window Effect Space
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHighLightWindowEffectSpace(void)
{
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
    ScalerColorHLWBRICTSAdjust(_BRI_CON_B_ON_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_DCC_FUNCTION == _ON)
    ScalerColorHLWDCCAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_GAMMA_FUNCTION == _ON)
    ScalerColorHLWOutputGammaAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
    ScalerColorHLWSRGBAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_IAPS_SUPPORT == _ON)
    ScalerColorHLWIAPSGainAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_ICM_SUPPORT == _ON)
    ScalerColorHLWICMAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
    ScalerColorHLWDCRAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWUltraVividAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_YPEAKING_SUPPORT == _ON)
    ScalerColorHLWYpeakingAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorHLWPanelUniformityAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_PCM_FUNCTION == _ON)
    ScalerColorHLWPCMAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_RGB_3D_GAMMA == _ON)
    ScalerColorHLWRGB3DGammaAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif
}
#endif // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set FREESYNC OD Measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void UserAdjustFREESYNCODMeasure(void)
{
    // Set Backlight
    UserAdjustBacklight(100);

    // Enable Backlight
    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

    // Disable OSD
    ScalerOsdDisableOsd();

    // Disable D-domain Pattern Gen.
    ScalerDDomainPatternGenEnable(_DISABLE);

    // According FREESYNC setting to set accurate Htotal/ Dclk
    ScalerMDomainFREESYNCODSetDisplayFormat(((WORD)_PANEL_DH_TOTAL), ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ), ((WORD)_PANEL_FREESYNC_MIN_FRAME_RATE));

    while(_TRUE)
    {
        ScalerDebug();
        ScalerDDomainFREESYNCODSetBackgroundGrayLevel();
    }
}
#endif


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : Set IR Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjusIR(void)
{
    ScalerIRHWModeDecoder(tIR_INITIAL_TABLE, GET_CURRENT_BANK_NUMBER());
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : Set embedded DP switch status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustEmbeddedDpSwitch(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D0_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D0_INPUT_PORT);
        }
        return;
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D1_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D1_INPUT_PORT);
        }
        return;
    }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D2_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D2_INPUT_PORT);
        }
        return;
    }
#endif
}
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Pixel orbiting step as following
//  -2->
// ^    |
// |    3
// 1    |
// |    v
// < -0- <-7-
//      |     |
//      4     6
//      |     |
//      v -5->
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelShifting(BYTE ucPixelShift)
{
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
    //BYTE ucPixelShift = 0;

    WORD usVdelay = 0;
    WORD usHdelay = 0;
    BYTE ucVstep = 4;
    BYTE ucHstep = 4;

	static WORD usNoVdelay = 0; // Pixel Shift Off �� ��, ���� ���� Vdelay �� 
	static WORD usNoHdelay = 0; // Pixel Shift Off �� ��, ���� ���� Hdelay �� 

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        ucVstep = (ucVstep + 1) & 0xFE;
    }
#endif

    ScalerGlobalWatchDog(_DISABLE);

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        usHdelay = ScalerVgaTopGetCaptureHDelay();
        usVdelay = ScalerVgaTopGetCaptureVDelay();
    }
    else
#endif
    {
        usHdelay = ScalerVgipGetCaptureHDelay();
        usVdelay = ScalerVgipGetCaptureVDelay();
    }
	if (ucPixelShift == 9) //�ʱ�ȭ
	{

		usNoVdelay = usVdelay;
		usNoHdelay = usHdelay;
		//DebugMessageYHJ("*SET usHdelay before", usNoHdelay);
		//DebugMessageYHJ("*SET usVdelay before", usNoVdelay);
		ScalerGlobalWatchDog(_ENABLE);
		return;
	}
	//DebugMessageYHJ("*ucPixelShift", ucPixelShift);
	//DebugMessageYHJ("*usHdelay before", usNoHdelay);
	//DebugMessageYHJ("*usVdelay before", usNoVdelay);
    //for(ucPixelShift = 0; ucPixelShift < 8; ucPixelShift++)
    //{
        ScalerTimerDelayXms(200);

        switch(ucPixelShift)
        {
            case 0: // _PIXEL0_TURN_LEFT:
            case 7: // _PIXEL1_TURN_LEFT:
                usHdelay += ucHstep;
                break;

            case 2: // _PIXEL0_TURN_RIGHT:
            case 5: // _PIXEL1_TURN_RIGHT:
                if(usHdelay >= ucHstep)
                {
                    usHdelay -= ucHstep;
                }
                else
                {
                    usHdelay = 0;
                }
                break;

            case 1: // _PIXEL0_TURN_UP:
            case 6: // _PIXEL1_TURN_UP:
                usVdelay += ucVstep;
                break;

            case 3: // _PIXEL0_TURN_DOWN:
            case 4: // _PIXEL1_TURN_DOWN:
                if(usVdelay >= ucVstep)
                {
                    usVdelay -= ucVstep;
                }
                else
                {
                    usVdelay = 0;
                }
                break;

            default:
				usVdelay = usNoVdelay;
				usHdelay = usNoHdelay;
                break;
        }

#if(_VGA_SUPPORT == _ON)
        if(SysSourceGetSourceType() == _SOURCE_VGA)
        {
            ScalerVgaTopSetCaptureHDelay(usHdelay);
            ScalerVgaTopSetCaptureVDelay(usVdelay);
            ScalerVgaTopDoubleBufferApply();
        }
        else
#endif
        {
            ScalerVgipSetCaptureHDelay(usHdelay);
            ScalerVgipSetCaptureVDelay(usVdelay);
            ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);
        }
    //}
		//DebugMessageYHJ("ucPixelShift", ucPixelShift);
		//DebugMessageYHJ("usHdelay after", usHdelay);
		//DebugMessageYHJ("usVdelay after", usVdelay);

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerGlobalWatchDog(_ENABLE);

#endif

#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
    BYTE ucPixelShift = 0;
    WORD usDHstart = ScalerMDomainGetDisplayTimingGenActiveRegionHStart();
    WORD usDHend = ScalerMDomainGetDisplayTimingGenActiveRegionHEnd();
    WORD usDVstart = ScalerMDomainGetDisplayTimingGenActiveRegionVStart();
    WORD usDVend = ScalerMDomainGetDisplayTimingGenActiveRegionVEnd();
    WORD usDVBGstart = GET_MDOMAIN_OUTPUT_VBSTART();
    WORD usDVBGend = GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT();
    WORD usDisplayHstart = usDHstart;
    WORD usDisplayVstart = usDVstart;

    // usDVBGstart/usDVBGend
    ScalerMDomainSetDisplayTimingGenBackgroundVStart(HIBYTE(usDVBGstart), LOBYTE(usDVBGstart), _DB_APPLY_NONE);
    ScalerMDomainSetDisplayTimingGenBackgroundVEnd(HIBYTE(usDVBGend), LOBYTE(usDVBGend), _DB_APPLY_NO_POLLING);

    // capture H start/end
    ScalerMDomainSetCaptureWindowHStart(HIBYTE(usDHstart), LOBYTE(usDHstart));
    ScalerMDomainSetCaptureWindowHEnd(HIBYTE(usDHend), LOBYTE(usDHend));
    // capture V start/end
    ScalerMDomainSetCaptureWindowVStart(HIBYTE(usDVstart), LOBYTE(usDVstart));
    ScalerMDomainSetCaptureWindowVEnd(HIBYTE(usDVend), LOBYTE(usDVend));

    ScalerMDomainSetCaptureWindowEnable(_ENABLE);

    //for(ucPixelShift = 0; ucPixelShift < 8; ucPixelShift++)
    //{
        ScalerTimerDelayXms(200);
        switch(ucPixelShift)
        {
            // H <-
            case 0: // _PIXEL0_TURN_LEFT:
                usDHend -= 1;
                usDisplayHstart -= 1;
                break;

            // V ^
            case 1: // _PIXEL0_TURN_UP:
                usDVstart += 1;
                usDVBGstart += 1;
                usDVBGend += 1;
                break;

            // H ->
            case 2: // _PIXEL0_TURN_RIGHT:
                usDHend += 1;
                usDisplayHstart += 1;
                break;

            // V v
            case 3: // _PIXEL0_TURN_DOWN:
                usDVstart -= 1;
                usDVBGstart -= 1;
                usDVBGend -= 1;
                break;

            // V v
            case 4: // _PIXEL1_TURN_DOWN:
                usDisplayVstart += 1;
                usDVstart += 1;
                break;

            // H ->
            case 5: // _PIXEL1_TURN_RIGHT:
                usDisplayHstart += 1;
                usDHstart += 1;
                break;

            // V ^
            case 6: // _PIXEL1_TURN_UP:
                usDisplayVstart -= 1;
                usDVstart -= 1;
                break;

            // H <-
            case 7: // _PIXEL1_TURN_LEFT:
                usDisplayHstart -= 1;
                usDHstart -= 1;
                break;

            default:
                break;
        }

        switch(ucPixelShift)
        {
            case 0: // _PIXEL0_TURN_LEFT:
            case 2: // _PIXEL0_TURN_RIGHT:
            case 5: // _PIXEL1_TURN_RIGHT:
            case 7: // _PIXEL1_TURN_LEFT:
                // Display H active start setting
                ScalerMDomainSetDisplayTimingGenActiveRegionHStart(HIBYTE(usDisplayHstart), LOBYTE(usDisplayHstart), _DB_APPLY_POLLING);
                // Capture window H start setting
                ScalerMDomainSetCaptureWindowHStart(HIBYTE(usDHstart), LOBYTE(usDHstart));
                // Capture window H end setting
                ScalerMDomainSetCaptureWindowHEnd(HIBYTE(usDHend), LOBYTE(usDHend));

                break;

            case 1: // _PIXEL0_TURN_UP:
            case 3: // _PIXEL0_TURN_DOWN:
            case 4: // _PIXEL1_TURN_DOWN:
            case 6: // _PIXEL1_TURN_UP:
                // Display V active start setting
                ScalerMDomainSetDisplayTimingGenActiveRegionVStart(HIBYTE(usDisplayVstart), LOBYTE(usDisplayVstart), _DB_APPLY_POLLING);
                // Capture window V start setting
                ScalerMDomainSetCaptureWindowVStart(HIBYTE(usDVstart), LOBYTE(usDVstart));
                // Display V background start setting
                ScalerMDomainSetDisplayTimingGenBackgroundVStart(HIBYTE(usDVBGstart), LOBYTE(usDVBGstart), _DB_APPLY_POLLING);
                // Display V background end setting
                ScalerMDomainSetDisplayTimingGenBackgroundVEnd(HIBYTE(usDVBGend), LOBYTE(usDVBGend), _DB_APPLY_POLLING);
                break;

            default:
                break;
        }
    //}

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerMDomainSetCaptureWindowEnable(_DISABLE);
#endif
}
#endif

#if(_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SDRToHDR parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSDRToHDR(bit bOn)
{
    if(bOn == _ON)
    {
#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        UserCommonAdjustSDRToHDR(tSDRTOHDR_INPUTGAMMA, tSDRTOHDR_ICM, tSDRTOHDR_DCC, GET_CURRENT_BANK_NUMBER());
    }
    else
    {
        UserAdjustColorEffectMode();
        OsdFuncColorPcmAdjust();
    }
}
#endif // End of #if(_SDR_TO_HDR_SUPPORT == _ON)
#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
