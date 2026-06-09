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
// ID Code      : RTD2014OsdFunc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFUNC__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

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
WORD g_usFontSelectStart;
WORD g_usFontTableStart;
BYTE g_ucOsdWidth;
BYTE g_ucOsdHeight;
BYTE g_ucOsdWidthB;
BYTE g_ucOsdHeightB;
BYTE g_ucFontPointer0 = _OSD_PAGE_0_START;
BYTE g_ucFontPointer1 = _OSD_PAGE_1_START;
BYTE g_ucFontPointer2 = _OSD_PAGE_2_START;
BYTE g_ucFontPointer3 = 0;
BYTE g_ucFontPointer4 = 0;
BYTE g_ucFontPointer5 = 0;
BYTE g_ucFontPointer6 = 0;
BYTE g_ucFontPointer7 = 0;
BYTE g_ucFontPointer8 = 0;
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
void OsdFuncTransparency(BYTE ucTrans);
void OsdFuncBlending(BYTE ucType);



void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
void OsdFuncDisableOsd(void);
void OsdFuncEnableOsd(void);
//void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
//void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
void OsdFuncSet2BitIconOffset(BYTE ucOffset);
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
#if(_SIX_COLOR_SUPPORT == _ON)
//void OsdFuncSixColorAdjust(void);
#endif
//void OsdFuncColorFormatAdjust(void);
#if(_SDR_TO_HDR_SUPPORT == _ON)
void OsdFuncColorPcmAdjust(void);
#endif
void OsdFuncSetOsdItemFlag(void);

#if(_FREEZE_SUPPORT == _ON)
bit OsdFuncCheckFreezeDisable(void);
void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE OsdFuncGetHdmiPortVersion(EnumSourceSearchPort enumSearchPort);
void OsdFuncSetHdmiPortVersion(EnumSourceSearchPort enumSearchPort,BYTE ucValue);
#endif

void OsdFuncShowSourceMenuCheck(void);
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum);
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    BYTE ucI = 0;
    BYTE ucTmp = 17; // Row Height = 18

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
    {
        ucI = ucWidth;
        ucWidth = ucHeight;
        ucHeight = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif

    // Row Command
    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidth);
    }

    // Row Command end
    ScalerOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);
    ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // Character Command initial
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
    {
        ucTmp = 0x4E;  // 18 Pixel
    }
    else
#endif
    {
        ucTmp = 0x4C;  // 12 Pixel
    }

    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColor, (WORD)ucWidth * ucHeight);

    g_ucOsdWidth = ucWidth; // for calculation (unit: word count)
    g_ucOsdHeight = ucHeight;
    SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));

    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    WORD usShiftValue = 0;
    BYTE ucXdouble = 1;
    WORD usTemp = 0;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucXdouble = 2;
    }

    if(ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_4_PIXEL)
    {
        // change horizontal delay step to 1 pixel for FB shift
        ScalerOsdHorizontalDelayStep(_OSD_HORIZONTAL_DELAY_STEP_1_PIXEL);
        usX *= 4;
    }

    if(enumOsdPositionType == _OSD_POSITION_GLOBAL_A)
    {
        if((usX * ucXdouble) <= 100)
        {
//            ScalerOsdPosition(enumOsdPositionType, (usX * ucXdouble), usY);
            ScalerOsdPosition(enumOsdPositionType, (usX), usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, 0);
        }
        else if((usX * ucXdouble) <= (4094 + 100))
        {
            ScalerOsdPosition(enumOsdPositionType, 100 / ucXdouble, usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, (usX * ucXdouble) - 100);
        }
        else // > 4095+100
        {
            ScalerOsdPosition(enumOsdPositionType, ((usX * ucXdouble) - 4094) / ucXdouble, usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, 4094);
        }

        ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_INSIDE, 0x00);
        ScalerOsdFBShiftBoundarySize(0x00, 0x00);
        ScalerOsdFBShiftEn(_ENABLE);
    }
    else if(enumOsdPositionType == _OSD_POSITION_GLOBAL_B)
    {
        usShiftValue = ScalerOsdGetFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE);

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            usTemp = g_ucOsdWidthB * 12;
        }
        else
        {
            usTemp = g_ucOsdHeightB * 18;
        }

        // if HPOS over halt of Panel width + shift value, adjust to adaptable HPOS
        if((usX * ucXdouble) > ((_PANEL_DH_WIDTH / 2 + usShiftValue) - (usTemp * ucXdouble)))
        {
            ScalerOsdPosition(enumOsdPositionType, (((_PANEL_DH_WIDTH / 2 + usShiftValue) - (usTemp * ucXdouble)) / ucXdouble), usY);
        }
        else
        {
            ScalerOsdPosition(enumOsdPositionType, ((usX * ucXdouble) - usShiftValue) / ucXdouble, usY);
        }
    }
#else
    ScalerOsdPosition(enumOsdPositionType, usX, usY);
#endif

    ScalerTimerWaitForEvent(_EVENT_DVS);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncTransparency(BYTE ucTrans)
{
    ScalerOsdSetTransparency(ucTrans);
}

//--------------------------------------------------
// Description  :
// Input Value  : Blending type1:Only windows blending.
//                Blending type2:All blending.
//                Blending type3:Windows & Character background blending.
// Output Value : None
//--------------------------------------------------
void OsdFuncBlending(BYTE ucType)
{
    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdWindow7SpecialFunction(_OSD_WINDOW_7_FUNCTION_MASK_REGION_TRANSPARENT_ALL);
    ScalerOsdSetTransparencyType(ucType);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex)
{
    ScalerOsdWindowDisable(enumWinIndex);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncDisableOsd(void)
{
    ScalerOsdDisableOsd();
	ScalerOsd2FontFunction(_DISABLE);
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
        SysAudioInternalGenTestProc(_OFF);
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncEnableOsd(void)
{
    ScalerOsdEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
//void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
//{
//    // BYTE ucRow;
//    BYTE ucCol = 3;
//
//    if((ucRow == 18) || (ucRow == 8))
//    {
//        OsdFuncChangeColor1Bit(ucRow, ucCol, 8, ucHeight, (ucColor << 4) & 0xF0, _FONTFROM_256_512);
//    }
//    else
//    {
//        ucCol = COL(4) + ((ucItem % 4) * 10) - 2;
//        OsdFuncChangeColor1Bit(ucRow, ucCol, ucWidth, ucHeight, (ucColor << 4) & 0xF0, _FONTFROM_0_255);
//    }
//}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
//void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom)
//{
//    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
//    BYTE ucHeightCount = 0;
//
//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//    BYTE ucWidthCount = 0;
//
//    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
//    {
//        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
//        {
//            usOsdAddr = (WORD)(g_ucOsdWidth - ucRow - ucHeight) + g_ucOsdWidth * (ucCol + ucWidthCount) + g_usFontSelectStart;
//            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4E | ucFontSelectFrom), ucHeight);
//            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
//        }
//    }
//    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
//    {
//        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
//        {
//            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
//            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4E | ucFontSelectFrom), ucHeight);
//            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
//        }
//    }
//    else
//#endif
//    {
//        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
//        {
//            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4C | ucFontSelectFrom), ucWidth);
//            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucWidth);
//            usOsdAddr += g_ucOsdWidth;
//        }
//    }
//}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSet2BitIconOffset(BYTE ucOffset)
{
    ScalerOsd2BitFontOffset(ucOffset);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    BYTE ucWidthCount = 0;

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdWidth - ucRow - ucHeight) + g_ucOsdWidth * (ucCol + ucWidthCount) + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucHeight);
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            // 1 Bit Font
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4C, ucWidth);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
//void OsdFuncSixColorAdjust(void)
//{
//    ScalerColorSixColorAdjust(GET_OSD_SIX_COLOR(), GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
//}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
//void OsdFuncColorFormatAdjust(void)
//{
//    switch(SysSourceGetInputPort())
//    {
//        case _A0_INPUT_PORT:
//
//            if(GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
//            {
//                SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
//            }
//            else
//            {
//                SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
//            }
//
//            break;
//
//#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
//        case _D0_INPUT_PORT:
//#endif
//
//#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
//        case _D1_INPUT_PORT:
//#endif
//
//#if(_D2_INPUT_PORT_TYPE == _D2_DVI_PORT)
//        case _D2_INPUT_PORT:
//#endif
//
//#if(_D3_INPUT_PORT_TYPE == _D3_DVI_PORT)
//        case _D3_INPUT_PORT:
//#endif
//
//            if(GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
//            {
//                SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
//            }
//            else
//            {
//                SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
//            }
//
//            break;
//
//        default:
//            break;
//    }
//
//#if(_OVERSCAN_SUPPORT == _ON)
//    if(GET_OSD_OVERSCAN_STATUS() == _ON)
//    {
//        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//    }
//    else
//#endif
//    {
//        SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_POLLING);
//    }
//}
#if(_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncColorPcmAdjust(void)
{
#if(_PCM_FUNCTION == _ON)
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);

#endif
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
        {
            UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
        }
#endif
        UserAdjustPCM(GET_OSD_PCM_STATUS());
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_BRIGHTNESS_SUPPORT == _ON)
        ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
        {
            ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
        }
#endif
    }
    else
    {
#if(_GAMMA_FUNCTION == _ON)
        UserAdjustGamma(GET_OSD_GAMMA());
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
        UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif

#if((_GAMMA_FUNCTION == _ON) || (_GLOBAL_HUE_SATURATION == _ON))
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_GAMMA_FUNCTION == _ON)
        if(GET_OSD_GAMMA() != _GAMMA_OFF)
        {
            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);

#if(_RGB_GAMMA_FUNCTION == _ON)
            ScalerColorRGBOutputGammaEnable(_FUNCTION_ON);
#endif
        }
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
        ScalerColorSRGBEnable(_FUNCTION_ON);
#endif

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
        UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
#endif  // End of #if((_GAMMA_FUNCTION == _ON) || (_GLOBAL_HUE_SATURATION == _ON))

    }
#endif  // End of #if(_PCM_FUNCTION == _ON)
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetOsdItemFlag(void)
{
    // input port
    if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
    {
        SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_AUTO);
    }
    else
    {
        switch(SysSourceGetInputPort())
        {
            case _A0_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_A0);
                break;

            case _D0_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D0);
                break;

            case _D1_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D1);
                break;

            case _D2_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D2);
                break;

            case _D3_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D3);
                break;

            case _D4_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D4);
                break;

            case _D5_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D5);
                break;

            case _D6_INPUT_PORT:
                SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_D6);
                break;

            default:
                break;
        }
    }
}

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFreezeDisable(void)
{
//Eric_020180307 : delete
//        if(((((GET_OSD_STATE() >= _MENU_DISPLAY_AUTO) &&
//              (GET_OSD_STATE() <= _MENU_DISPLAY_PHASE)) ||
//             (GET_OSD_STATE() == _MENU_COLOR_FORMAT) ||
//             (GET_OSD_STATE() == _MENU_ADVANCE_ITEM) ||
//             (GET_OSD_STATE() == _MENU_OTHER_RESET) ||
//             (GET_OSD_STATE() == _MENU_DISPLAY_LATENCY)) &&
//            (GET_KEYMESSAGE() == _MENU_KEY_MESSAGE)) ||
//           ((GET_OSD_STATE() == _MENU_ADVANCE_ULTRA_VIVID_ADJUST) && (GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_OFF) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
//           ((GET_OSD_STATE() == _MENU_ADVANCE_ULTRA_VIVID_ADJUST) && (GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_L) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
//        {
//            OsdDispOsdMessage(_OSD_DISP_DISABLE_FREEZE_MSG);
//            ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
//            SET_OSD_STATE(GET_OSD_STATE_PREVIOUS());
//            SET_OSD_FREEZE_STATUS(_OFF);
//            UserCommonAdjustDisplayFreeze(_OFF);
//    #if(_URGENT_EVENT_CHECK_MODE == _OFF)
//            SET_FREEZE_DISABLE_MSG_STATE(_ON);
//    #endif
//            return _TRUE;
//        }
    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowOSDAfterClosedFreezeMsg(void)
{
    OsdDispMainMenu();
//Eric_20180306 : Delete
//        switch(GET_OSD_STATE())
//        {
//    #if(_VGA_SUPPORT == _ON)
//            case _MENU_DISPLAY_AUTO:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSliderAndNumber();
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            case _MENU_DISPLAY_HPOS:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_VGA_MODE_ADJUST_H_POSITION());
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            case _MENU_DISPLAY_VPOS:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS, GET_VGA_MODE_ADJUST_V_POSITION());
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            case _MENU_DISPLAY_CLOCK:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_DISPLAY_CLOCK, GET_VGA_MODE_ADJUST_CLOCK());
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            case _MENU_DISPLAY_PHASE:
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                OsdDispSliderAndNumber(_MENU_DISPLAY_PHASE, GET_VGA_MODE_ADJUST_PHASE());
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//    #endif
//            case _MENU_COLOR_FORMAT:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            case _MENU_ADVANCE_ITEM:
//                OsdDispAdvanceMenuReDraw(_HIGH);
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            case _MENU_ADVANCE_ULTRA_VIVID_ADJUST:
//                if(GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_OFF)
//                {
//                    OsdDispAdvanceMenuReDraw(_HIGH);
//                    SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                    SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
//                }
//                else if(GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_L)
//                {
//                    OsdDispAdvanceMenuReDraw(_HIGH);
//                    SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                    SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
//                }
//                break;
//            case _MENU_DISPLAY_DISP_ROTATE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            case _MENU_DISPLAY_LATENCY:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
//                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
//                break;
//            default:
//                break;
//        }
}
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncGetHdmiPortVersion(EnumSourceSearchPort enumSearchPort)
{
    switch(enumSearchPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return (GET_OSD_D0_HDMI_VER());
            break;
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return (GET_OSD_D1_HDMI_VER());
            break;
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return (GET_OSD_D2_HDMI_VER());
            break;
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return (GET_OSD_D3_HDMI_VER());
            break;
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return (GET_OSD_D4_HDMI_VER());
            break;
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return (GET_OSD_D5_HDMI_VER());
            break;
#endif

        default:
            return 0;
            break;
    }
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetHdmiPortVersion(EnumSourceSearchPort enumSearchPort,BYTE ucValue)
{
    ucValue = ucValue;

    switch(enumSearchPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_OSD_D0_HDMI_VER(ucValue);
            break;
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_OSD_D1_HDMI_VER(ucValue);
            break;
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_OSD_D2_HDMI_VER(ucValue);
            break;
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_OSD_D3_HDMI_VER(ucValue);
            break;
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_OSD_D4_HDMI_VER(ucValue);
            break;
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            SET_OSD_D5_HDMI_VER(ucValue);
            break;
#endif
        default:
            break;
    }
}
#endif


//--------------------------------------------------
// Description  : 
// Input Value  : None
// Output Value : None
//--------------------------------------------------

void OsdFontPut1ChooseIcon(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucForeground, BYTE ucBackground)
	{
		WORD xdata usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
		BYTE xdata ucByte0 = 0x4C;
		BYTE xdata ucByte2 = 0;
		BYTE ucLength2 = 16, ucHeight2 = 2;
		BYTE ucLength1 = 2, ucHeight1 = 1;
		BYTE ucOsdRotateStatus = _OSD_ROTATE_DEGREE_0;
		WORD windowcountmax=0;
//ScalerOsdHardwareVLC(tFONT1_MAIN_ICON_TABLE_1[10], VLC_TABLE_SIZE(tFONT1_MAIN_ICON_TABLE_1[10]), GET_CURRENT_BANK_NUMBER(), ucIcon , g_usFontTableStart, ucOsdRotateStatus);




#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
		if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
		{
			usOsdAddr = (WORD)((g_ucOsdWidth-ucRow-1) + g_ucOsdWidth * ucCol) ; 	   
			ucByte0 = 0x4E; 
		}	 
		else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
		{
			usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol) * g_ucOsdWidth + ucRow;
			ucByte0 = 0x4E; 
		}
#endif

		
		ucForeground &= 0x0F;
		
		ucByte2 = ((ucForeground  << 4) | ucBackground);

	
	//20140207 Abel Modify	  
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) 
		if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
		{
					 
				for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
				{				   
						usOsdAddr = (WORD)(g_ucOsdWidth- ucRow - ucHeight2 - 1)+ g_ucOsdWidth * (ucCol+ucLength2);
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
					ucIcon++;		 
				}				 
				 
	
		}	 
		else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
		{	 
				 
				for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
				{
					usOsdAddr = (WORD)(g_ucOsdHeight - 1 - (ucCol+ucLength2)) * g_ucOsdWidth + (ucRow+ucHeight2); 			   
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
					ucIcon++;		 
				}				 
				 
		}
		else  
#endif        
		{	 
				 
				for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
				{
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart + ucLength2, ucByte0, ucIcon, ucByte2);	  
					ucIcon++;		 
				}	 
			
			 
		}
	}


//--------------------------------------------------
// Description  : 
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1FuncHLine(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucLength,BYTE ucForeground, BYTE ucBackground)
	{
		WORD xdata usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
		BYTE xdata ucByte0 = 0x4C;
		BYTE xdata ucByte2 = 0;
		BYTE ucLength2 = 16, ucHeight2 = 2;
		BYTE ucLength1 = ucLength, ucHeight1 = 0;
		BYTE ucOsdRotateStatus = _OSD_ROTATE_DEGREE_0;
		WORD windowcountmax=0;
//ScalerOsdHardwareVLC(tFONT1_MAIN_ICON_TABLE_1[10], VLC_TABLE_SIZE(tFONT1_MAIN_ICON_TABLE_1[10]), GET_CURRENT_BANK_NUMBER(), ucIcon , g_usFontTableStart, ucOsdRotateStatus);



#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
		if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
		{
			usOsdAddr = (WORD)((g_ucOsdWidth-ucRow-1) + g_ucOsdWidth * ucCol) ; 	   
			ucByte0 = 0x4E; 
		}	 
		else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
		{
			usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol) * g_ucOsdWidth + ucRow;
			ucByte0 = 0x4E; 
		}
#endif

		
		ucForeground &= 0x0F;
		
		ucByte2 = ((ucForeground  << 4) | ucBackground);

	
	//20140207 Abel Modify	  
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) 
		if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
		{
					 
				for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
				{				   
						usOsdAddr = (WORD)(g_ucOsdWidth- ucRow - ucHeight2 - 1)+ g_ucOsdWidth * (ucCol+ucLength2);
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
					ucIcon++;		 
				}				 
				 
	
		}	 
		else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
		{	 
				 
				for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
				{
					usOsdAddr = (WORD)(g_ucOsdHeight - 1 - (ucCol+ucLength2)) * g_ucOsdWidth + (ucRow+ucHeight2); 			   
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
					ucIcon++;		 
				}				 
				 
		}
		else  
#endif        
		{	 
				 
				for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
				{
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart + ucLength2, ucByte0, ucIcon, ucByte2);	  
							 
				}	 
			
			 
		}
	}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------

void OsdThreeColorChooseTableForm(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucbox,BYTE ucType)
	{
					WORD xdata usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
					BYTE xdata ucByte0 = 0x4C;
					BYTE xdata ucByte2 = 0,ucaimByte2 = 0;
					BYTE ucLength2 = 16, ucHeight2 = 2;
					BYTE ucLength1 = 0, ucHeight1 = 0;
					BYTE ucOsdRotateStatus = _OSD_ROTATE_DEGREE_0;
					WORD windowcountmax=0;
					WORD linenumber=0;
					WORD linenumberaddr=0;
			//ScalerOsdHardwareVLC(tFONT1_MAIN_ICON_TABLE_1[10], VLC_TABLE_SIZE(tFONT1_MAIN_ICON_TABLE_1[10]), GET_CURRENT_BANK_NUMBER(), ucIcon , g_usFontTableStart, ucOsdRotateStatus);
			
			
			
			
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
					if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
					{
						usOsdAddr = (WORD)((g_ucOsdWidth-ucRow-1) + g_ucOsdWidth * ucCol) ; 	   
						ucByte0 = 0x4E; 
					}	 
					else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
					{
						usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol) * g_ucOsdWidth + ucRow;
						ucByte0 = 0x4E; 
					}
#endif
			
					
					ucForeground &= 0x0F;
					
					ucByte2 = ((ucForeground  << 4) | ucBackground);
					
					ucbox &= 0x0F;
					
					ucaimByte2 = ((ucbox  << 4) | ucbox);
	
				
				//20140207 Abel Modify	  
		/*#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) 
					if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
					{
								 
							for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
							{				   
									usOsdAddr = (WORD)(g_ucOsdWidth- ucRow - ucHeight2 - 1)+ g_ucOsdWidth * (ucCol+ucLength2);
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
								ucIcon++;		 
							}				 
							 
				
					}	 
					else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
					{	 
							 
							for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
							{
								usOsdAddr = (WORD)(g_ucOsdHeight - 1 - (ucCol+ucLength2)) * g_ucOsdWidth + (ucRow+ucHeight2);			   
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
								ucIcon++;		 
							}				 
							 
					}
					else  
#endif   */  
		
		if(ucType==0)
		{	 
			for(ucHeight1=0; ucHeight1 < ucHeight+2;ucHeight1++)
			{
	
	
				if(ucHeight1==0)
				{
					for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
					{
						if(ucLength1==0)
						{
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon, ucByte2); 
						}
						
						else if(ucLength1==ucLength+1)
						{
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);
							ucRow++;
							usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
	
						}
	
	
						
						else
						{
						//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
					//	ucRow++;	
						}
					}
				}
				
	
				else if(ucHeight1==ucHeight+1)
				{
						for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
						{
							if(ucLength1==0)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+4, ucByte2); 
							}
							else if(ucLength1==ucLength+1)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+3, ucByte2);
								//ucRow++;
								//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
	
							}
							else
							{
							//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
						//	ucRow++;	
							}
						}
	
	
				}
	
				else
				{
						for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
						{
							if(ucLength1==0)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-2, ucByte2); 
							}
							if(ucLength1==ucLength+1)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-6, ucByte2);
								ucRow++;
								usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
	
							}
	
							if(ucLength1>0 && ucLength1<ucLength+1)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-14, ucaimByte2);
							}
								
							
							
						}
	
	
	
				}
	
	
			}
			
			 
		}		
	
	}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1FuncAimTableForm(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucbox,BYTE ucType)
{
				WORD xdata usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
				BYTE xdata ucByte0 = 0x4C;
				BYTE xdata ucByte2 = 0,ucaimByte2 = 0;
				BYTE ucLength2 = 16, ucHeight2 = 2;
				BYTE ucLength1 = 0, ucHeight1 = 0;
				BYTE ucOsdRotateStatus = _OSD_ROTATE_DEGREE_0;
				WORD windowcountmax=0;
				WORD linenumber=0;
				WORD linenumberaddr=0;
		//ScalerOsdHardwareVLC(tFONT1_MAIN_ICON_TABLE_1[10], VLC_TABLE_SIZE(tFONT1_MAIN_ICON_TABLE_1[10]), GET_CURRENT_BANK_NUMBER(), ucIcon , g_usFontTableStart, ucOsdRotateStatus);
		
		
		
		
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
				if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
				{
					usOsdAddr = (WORD)((g_ucOsdWidth-ucRow-1) + g_ucOsdWidth * ucCol) ; 	   
					ucByte0 = 0x4E; 
				}	 
				else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
				{
					usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol) * g_ucOsdWidth + ucRow;
					ucByte0 = 0x4E; 
				}
#endif
		
				
				ucForeground &= 0x0F;
				
				ucByte2 = ((ucForeground  << 4) | ucBackground);
				
				ucbox &= 0x0F;
				
				ucaimByte2 = ((ucbox  << 4) | ucbox);

			
			//20140207 Abel Modify	  
	/*#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) 
				if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
				{
							 
						for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
						{				   
								usOsdAddr = (WORD)(g_ucOsdWidth- ucRow - ucHeight2 - 1)+ g_ucOsdWidth * (ucCol+ucLength2);
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
							ucIcon++;		 
						}				 
						 
			
				}	 
				else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
				{	 
						 
						for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
						{
							usOsdAddr = (WORD)(g_ucOsdHeight - 1 - (ucCol+ucLength2)) * g_ucOsdWidth + (ucRow+ucHeight2);			   
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
							ucIcon++;		 
						}				 
						 
				}
				else  
#endif   */  
	
	if(ucType==0)
	{	 
		for(ucHeight1=0; ucHeight1 < ucHeight+2;ucHeight1++)
		{


			if(ucHeight1==0)
			{
				for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
				{
					if(ucLength1==0)
					{
						ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon, ucByte2); 
					}
					
					else if(ucLength1==ucLength+1)
					{
						ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);
						ucRow++;
						usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

					}


					
					else
					{
					//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
						ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
				//	ucRow++;	
					}
				}
			}
			

			else if(ucHeight1==ucHeight+1)
			{
					for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
					{
						if(ucLength1==0)
						{
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+4, ucByte2); 
						}
						else if(ucLength1==ucLength+1)
						{
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+3, ucByte2);
							//ucRow++;
							//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

						}
						else
						{
						//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
					//	ucRow++;	
						}
					}


			}

			else
			{
					for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
					{
						if(ucLength1==0)
						{
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-2, ucByte2); 
						}
						if(ucLength1==ucLength+1)
						{
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-6, ucByte2);
							ucRow++;
							usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

						}

						if(ucLength1>0 && ucLength1<ucLength+1)
						{
							ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-14, ucaimByte2);
						}
							
						
						
					}



			}


		}
		
		 
	}		

}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
//OsdFontPut1FuncAimTableForm

void OsdFontPut1NumberTableForm(BYTE ucRow, BYTE ucCol, BYTE ucNumberIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucnumber)
	{
		WORD xdata usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
		BYTE xdata ucByte0 = 0x4C;
		BYTE xdata ucByte2 = 0;
		BYTE ucLength1 = 0, ucHeight1 = 0;
		BYTE ucLength2 = 0, ucHeight2 = 0;
		BYTE ucIcon;
		ucIcon =ucNumberIcon+ ucnumber*6;
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
		if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
		{
			usOsdAddr = (WORD)((g_ucOsdWidth-ucRow-1) + g_ucOsdWidth * ucCol) ; 	   
			ucByte0 = 0x4E; 
		}	 
		else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
		{
			usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol) * g_ucOsdWidth + ucRow;
			ucByte0 = 0x4E; 
		}
#endif
	
		ucForeground &= 0x0F;
		
		ucByte2 = ((ucForeground  << 4) | ucBackground);
	
	//20140207 Abel Modify	  
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) 
		if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
		{
			for(ucHeight1 = 0; ucHeight1 < ucHeight; ucHeight1++)
			{					 
				for(ucLength1=0; ucLength1 < ucLength; ucLength1++)
				{				   
						usOsdAddr = (WORD)(g_ucOsdWidth- ucRow - ucHeight1 - 1)+ g_ucOsdWidth * (ucCol+ucLength1);
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
					ucIcon++;		 
				}				 
			}	 
	
		}	 
		else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
		{	 
			for(ucHeight1 = 0; ucHeight1 < ucHeight; ucHeight1++)
			{					 
				for(ucLength1=0; ucLength1 < ucLength; ucLength1++)
				{
					usOsdAddr = (WORD)(g_ucOsdHeight - 1 - (ucCol+ucLength1)) * g_ucOsdWidth + (ucRow+ucHeight1); 			   
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
					ucIcon++;		 
				}				 
			}	 
		}
		else  
#endif        
		{	 
			for(ucHeight1 = 0; ucHeight1 < ucHeight; ucHeight1++)
			{					 
				for(ucLength1=0; ucLength1 < ucLength; ucLength1++)
				{
					ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart + ucLength1, ucByte0, ucIcon, ucByte2);	  
					ucIcon++;		 
				}	 
				usOsdAddr += g_ucOsdWidth;
			}	 
		}
	}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------


void OsdFontPut1FuncTableForm(BYTE ucRow, BYTE ucCol, BYTE ucIcon,BYTE ucLength ,BYTE ucHeight,BYTE ucForeground, BYTE ucBackground,BYTE ucType)
{
			WORD xdata usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
			BYTE xdata ucByte0 = 0x4C;
			BYTE xdata ucByte2 = 0;
			BYTE ucHeight2 = 2;
			BYTE ucLength1 = 0, ucHeight1 = 0;
			WORD windowcountmax=0;
			WORD linenumber=0;
			WORD linenumberaddr=0;
	//ScalerOsdHardwareVLC(tFONT1_MAIN_ICON_TABLE_1[10], VLC_TABLE_SIZE(tFONT1_MAIN_ICON_TABLE_1[10]), GET_CURRENT_BANK_NUMBER(), ucIcon , g_usFontTableStart, ucOsdRotateStatus);
	
	
	
	
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
			if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
			{
				usOsdAddr = (WORD)((g_ucOsdWidth-ucRow-1) + g_ucOsdWidth * ucCol) ; 	   
				ucByte0 = 0x4E; 
			}	 
			else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
			{
				usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol) * g_ucOsdWidth + ucRow;
				ucByte0 = 0x4E; 
			}
#endif
	
			
			ucForeground &= 0x0F;
			
			ucByte2 = ((ucForeground  << 4) | ucBackground);
	
		
		//20140207 Abel Modify	  
/*#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) 
			if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
			{
						 
					for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
					{				   
							usOsdAddr = (WORD)(g_ucOsdWidth- ucRow - ucHeight2 - 1)+ g_ucOsdWidth * (ucCol+ucLength2);
						ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
						ucIcon++;		 
					}				 
					 
		
			}	 
			else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
			{	 
					 
					for(ucLength2=0; ucLength2 < ucLength1; ucLength2++)
					{
						usOsdAddr = (WORD)(g_ucOsdHeight - 1 - (ucCol+ucLength2)) * g_ucOsdWidth + (ucRow+ucHeight2);			   
						ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);    
						ucIcon++;		 
					}				 
					 
			}
			else  
#endif   */  

		if(ucType==3)
			{	 
				for(ucHeight1=0; ucHeight1 < ucHeight+2;ucHeight1++)
				{


					if(ucHeight1==0)
					{
						for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
						{
							if(ucLength1==0)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon, ucByte2); 
							}
							
							else if(ucLength1==ucLength+1)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);
								ucRow++;
								usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

							}


							
							else
							{
							//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
						//	ucRow++;	
							}
						}
					}
					

					else if(ucHeight1==ucHeight+1)
					{
							for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
							{
								if(ucLength1==0)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+4, ucByte2); 
								}
								else if(ucLength1==ucLength+1)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+3, ucByte2);
									//ucRow++;
									//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

								}
								else
								{
								//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
							//	ucRow++;	
								}
							}


					}

					else
					{
							for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
							{
								if(ucLength1==0)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-2, ucByte2); 
								}
								if(ucLength1==ucLength+1)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-6, ucByte2);
									ucRow++;
									usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

								}

								if(ucLength1>0 && ucLength1<ucLength+1)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-14, ucByte2);
								}
									
								
								
							}



					}


				}
				
				 
			}		



		if(ucType==_QUADRANGLE_WINDOW_0)
			{	 
				for(ucHeight1=0; ucHeight1 < ucHeight+2;ucHeight1++)
				{

					if(ucHeight1==0)
					{
						for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
						{
							if(ucLength1==0)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon, ucByte2); 
							}
							else if(ucLength1==ucLength+1)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+2, ucByte2);
								ucRow++;
								usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

							}
							else
							{
							//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);   
						//	ucRow++;	
							}
						}
					}

					else if(ucHeight1==ucHeight+1)
					{
					
							for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
							{
								if(ucLength1==0)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+4, ucByte2); 
								}
								else if(ucLength1==ucLength+1)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+3, ucByte2);
									//ucRow++;
									//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

								}
								else
								{
								//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);   
							//	ucRow++;	
								}
							}
                                         

					}

					else
					{
							for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
							{
								if(ucLength1==0)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1+1 , ucByte0, ucIcon+1, ucByte2); 
								}
								if(ucLength1==ucLength+1 )
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1-1 , ucByte0, ucIcon+1, ucByte2);
									ucRow++;
									usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

								}
								else
								{
								//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
									//ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);   
							//	ucRow++;	
								}

							}

					}


				}
				
				 
			}


		if(ucType==2)
			{	 
							for(ucHeight1=0; ucHeight1 < ucHeight+2;ucHeight1++)
							{

								

								
							
								
								if(ucHeight1==0)
								{
									for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
									{
										if(ucLength1==0)
										{
											ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon, ucByte2); 
										}
										else if(ucLength1==ucLength+1)
										{
											ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);
											ucRow++;
											usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
			
										}
										else
										{
										//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
											ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
									//	ucRow++;	
										}
									}
								}
			
								else if(ucHeight1==ucHeight+1)
								{
										for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
										{
											if(ucLength1==0)
											{
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+4, ucByte2); 
											}
											else if(ucLength1==ucLength+1)
											{
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+3, ucByte2);
												//ucRow++;
												//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
			
											}
											else
											{
											//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
										//	ucRow++;	
											}
										}
			
			
								}
								else if(ucHeight1%3==0 && ucHeight1>0 && ucHeight1< 22)
								{
								
																
										for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
										{
											if(ucLength1==0)
											{
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+5, ucByte2); 
											}
											if(ucLength1==ucLength+1)
											{
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+2, ucByte2);
												ucRow++;
												usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
											
											}
											else
											{
											//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1+1 , ucByte0, ucIcon-1, ucByte2);   
												//	ucRow++;	
											}
											
										}
								
								}





			
								else
								{
										for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
										{
											if(ucLength1==0)
											{
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-2, ucByte2); 
											}
											if(ucLength1==ucLength+1)
											{
												ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-6, ucByte2);
												ucRow++;
												usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
			
											}
			
										}
			
								}
								
			
			
			}
							
							 
		}


		
		if(ucType==_ARC_WINDOW_0)
			{	 
				for(ucHeight1=0; ucHeight1 < ucHeight+2;ucHeight1++)
				{

					if(ucHeight1==0)
					{
						for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
						{
							if(ucLength1==0)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon, ucByte2); 
							}
							else if(ucLength1==ucLength+1)
							{
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+1, ucByte2);
								ucRow++;
								usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

							}
							else
							{
							//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
								ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
						//	ucRow++;	
							}
						}
					}

					else if(ucHeight1==ucHeight+1)
					{
							for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
							{
								if(ucLength1==0)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+4, ucByte2); 
								}
								else if(ucLength1==ucLength+1)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon+3, ucByte2);
									//ucRow++;
									//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

								}
								else
								{
								//usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-1, ucByte2);   
							//	ucRow++;	
								}
							}


					}

					else
					{
							for(ucLength1=0; ucLength1 < ucLength+2;ucLength1++)
							{
								if(ucLength1==0)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-2, ucByte2); 
								}
								if(ucLength1==ucLength+1)
								{
									ScalerOsdCommandAllByte(usOsdAddr + g_usFontSelectStart+ucLength1 , ucByte0, ucIcon-6, ucByte2);
									ucRow++;
									usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

								}

							}

					}


				}
				
				 
			}		
		}

void OsdFuncShowSourceMenuCheck(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
	if (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING) == _TRUE)
	{
		if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF) ScalerTimerReactiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
	}
	else if ((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING) == _TRUE))
	{
		if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF) ScalerTimerReactiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
	}
#else
	if (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
	{
		if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF) ScalerTimerReactiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
	}
#endif
}

		//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum)
{
	BYTE ucCheckloop = 0;
	do
	{
		switch (GET_KEYMESSAGE())
		{
		case _RIGHT_KEY_MESSAGE:
		case _DOWN_KEY_MESSAGE:
#if	(_ENABLE_MENU_VGA == _ON)
			if (ucOsdInputNum == _OSD_INPUT_AUTO)
			{
				ucOsdInputNum = _OSD_INPUT_A0;
			}
			else if (ucOsdInputNum == _OSD_INPUT_D3)
			{
				ucOsdInputNum = _OSD_INPUT_AUTO;
			}
			else
			{
				ucOsdInputNum++;
			}
#else
			if (ucOsdInputNum == _OSD_INPUT_D3)
			{
				ucOsdInputNum = _OSD_INPUT_AUTO;
			}
			else
			{
				ucOsdInputNum++;
			}
#endif
			break;
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
#if (_ENABLE_MENU_VGA == _ON)
			if (ucOsdInputNum == _OSD_INPUT_A0)
			{
				ucOsdInputNum = _OSD_INPUT_AUTO;
			}
			else if (ucOsdInputNum == _OSD_INPUT_AUTO)
			{
				ucOsdInputNum = _OSD_INPUT_D3;
			}
			else
			{
				ucOsdInputNum--;
			}
#else
			if (ucOsdInputNum == _OSD_INPUT_AUTO)
			{
				ucOsdInputNum = _OSD_INPUT_D3;
			}
			else
			{
				ucOsdInputNum--;
			}
#endif
			break;

		default:
			break;
		}

		switch (ucOsdInputNum)
		{
		case _OSD_INPUT_A0:
			ucCheckloop = (_A0_INPUT_TYPE - _OPTION_ICON_END);
			break;
		case _OSD_INPUT_D0:
			ucCheckloop = (_D0_INPUT_TYPE - _OPTION_ICON_END);
			break;
		case _OSD_INPUT_D1:
			ucCheckloop = (_D1_INPUT_TYPE - _OPTION_ICON_END);
			break;
		case _OSD_INPUT_D2:
			ucCheckloop = (_D2_INPUT_TYPE - _OPTION_ICON_END);
			break;
		case _OSD_INPUT_D3:
			ucCheckloop = (_D3_INPUT_TYPE - _OPTION_ICON_END);
			break;
		case _OSD_INPUT_D4:
			ucCheckloop = (_D4_INPUT_TYPE - _OPTION_ICON_END);
			break;
		case _OSD_INPUT_D5:
			ucCheckloop = (_D5_INPUT_TYPE - _OPTION_ICON_END);
			break;
		case _OSD_INPUT_D6:
			ucCheckloop = (_D6_INPUT_TYPE - _OPTION_ICON_END);
			break;

		case _OSD_INPUT_AUTO:
			ucCheckloop = 0x01;
			break;
		default:
			break;
		}
	} while (ucCheckloop == 0x00); // 0x00=>NO PORT

	return ucOsdInputNum;
}
#if (_ENABLE_SELF_CHECK == _ON)
////////////////////////////////////////////////////////////////////
// SELF CHECK Pattern
////////////////////////////////////////////////////////////////////
void OsdFuncApplySelfCheckMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
	BYTE ucI = 0;
	BYTE ucTmp = 3; // Row Height = 18

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
		(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
	{
		ucI = ucWidth;
		ucWidth = ucHeight;
		ucHeight = ucI;
		ucTmp = 11;  // Row Height = 12
	}
#endif

	// Row Command
	for (ucI = 0; ucI < ucHeight; ucI++)
	{
		ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidth);
	}

	// Row Command end
	ScalerOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

	// Frame Control (set font start address)
	g_usFontSelectStart = ucHeight + 1;
	g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);
	ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

	// Character Command initial
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
		(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
	{
		ucTmp = 0x4E;  // 18 Pixel
	}
	else
#endif
	{
		ucTmp = 0x4C;  // 12 Pixel
	}

	ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColor, (WORD)ucWidth * ucHeight);

	g_ucOsdWidth = ucWidth; // for calculation (unit: word count)
	g_ucOsdHeight = ucHeight;
	SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));

	ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
	ScalerOsdDoubleFunction(_OFF, _OFF);
}
#endif
#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)

