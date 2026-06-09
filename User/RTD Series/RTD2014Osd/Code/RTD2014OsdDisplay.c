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
// ID Code      : RTD2014OsdDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDDISPLAY__

#include "UserCommonInclude.h"

#if (_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
	_VGA_A0 = 0x01,
} EnumOsdSourceTypeVga;

typedef enum
{
	_DVI = 0x02,
#if (_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
	_DVI_D0,
#endif
#if (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
	_DVI_D1,
#endif
#if ((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
	_DVI_D2,
#endif
#if ((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
	_DVI_D3,
#endif
#if ((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
	_DVI_D4,
#endif
#if (_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
	_DVI_D5,
#endif

	_HDMI = 0x10,
#if ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
	_HDMI_D0,
#endif
#if ((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
	_HDMI_D1,
#endif
#if ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
	_HDMI_D2,
#endif
#if ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
	_HDMI_D3,
#endif
#if ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
	_HDMI_D4,
#endif
#if ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
	_HDMI_D5,
#endif
} EnumOsdSourceTypeTMDS;

typedef enum
{
	_DP = 0x0E,
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
	_DP_D0,
#endif
#if (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
	_DP_D1,
#endif
#if (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
	_DP_D2,
#endif
#if (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
	_DP_D6,
#endif
} EnumOsdSourceTypeDP;

//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Definitions of Advance OSD ITEM
//--------------------------------------------------

typedef enum
{
	_OSD_ADVANCE_ASPECT,
	_OSD_ADVANCE_OVERSCAN,
	_OSD_ADVANCE_OVERDRIVE,
	_OSD_ADVANCE_DDCCI,
	_OSD_ADVANCE_ULTRAVIVID,
	_OSD_ADVANCE_DCR,
	_OSD_ADVANCE_DPOPTION,
	_OSD_ADVANCE_DPMST,
	_OSD_ADVANCE_DP_RESOLUTION,
	_OSD_ADVANCE_CLONE,
	_OSD_ADVANCE_HDMI_VERSIONS,
	_OSD_ADVANCE_FREESYNC,
	_OSD_ADVANCE_TYPEC_MODE,
	_OSD_ADVANCE_HDR,
	_OSD_ADVANCE_LOCALDIMMING,
	_OSD_ADVANCE_PIXELSHIFT,
	_OSD_ADVANCE_SDR_TO_HDR,

	_OSD_ADVANCE_NONE,

} EnumOsdAdvanceItem;

// following order could modify by User
BYTE code OSD_ADVANCE_ITEM_PRI[] =
	{
#if (_ASPECT_RATIO_SUPPORT == _ON)
		_OSD_ADVANCE_ASPECT,
#endif

#if (_OVERSCAN_SUPPORT == _ON)
		_OSD_ADVANCE_OVERSCAN,
#endif

#if (_OD_SUPPORT == _ON)
		_OSD_ADVANCE_OVERDRIVE,
#endif
		_OSD_ADVANCE_DDCCI,

#if (_ULTRA_VIVID_SUPPORT == _ON)
		_OSD_ADVANCE_ULTRAVIVID,
#endif

#if (_DCR_SUPPORT == _ON)
		_OSD_ADVANCE_DCR,
#endif

#if (_DP_SUPPORT == _ON)
		_OSD_ADVANCE_DPOPTION,
#if (_DP_MST_SUPPORT == _ON)
		_OSD_ADVANCE_DPMST,
#endif
		_OSD_ADVANCE_DP_RESOLUTION,
		_OSD_ADVANCE_CLONE,
#endif

#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
		_OSD_ADVANCE_HDMI_VERSIONS,
#endif

#if ((_FREESYNC_II_SUPPORT == _ON) || (_FREESYNC_SUPPORT == _ON))
		_OSD_ADVANCE_FREESYNC,
#endif

#if (_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
		_OSD_ADVANCE_TYPEC_MODE,
#endif

#if (_HDR10_SUPPORT == _ON)
		_OSD_ADVANCE_HDR,
#endif

#if (_OSD_LOCAL_DIMMING_SUPPORT == _ON)
		_OSD_ADVANCE_LOCALDIMMING,
#endif

#if (_SDR_TO_HDR_SUPPORT == _ON)
		_OSD_ADVANCE_SDR_TO_HDR,
#endif

#if (_PIXEL_SHIFT_SUPPORT == _ON)
		_OSD_ADVANCE_PIXELSHIFT,
#endif

		_OSD_ADVANCE_NONE,
};
#define _OSD_ADVANCE_ITEM_AMOUNT (sizeof(OSD_ADVANCE_ITEM_PRI) - 1)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE OsdDisplayGetSourcePortString(void);

#if (_ENABLE_VIDEO_WALL == _ON)
BYTE GetVideoWallDisplayNumber(void);
#endif
BYTE OsdDispJudgeSourceType(void);
void OsdDispDisableOsd(void);
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor);

void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState);

void OsdDispMainMenu(void);

void OsdDispHotKeyVolumeMenu(void); // 170928_02
void OsdDispHotKeyMuteMenu(void);
// void OsdDispHotKeyAudioMode(void);
// void OsdDispHotKeyPictureMode(void); //Eric_171010

WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle, bit bNumberic);
WORD OsdDisplayDetOverRange_Curved(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
void OsdDisplaySixColorGetOneColor(BYTE ucColor);
// void OsdDisplaySixColorSetOneColor(BYTE ucColor);

void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);

#if (_VGA_SUPPORT == _ON)
void OsdDispAutoConfigProc(void);
void OsdDisplayAutoBalanceProc(void);
#endif

void OsdDispOsdReset(void);
#if (_CUSTOMER_TYPE != _CUSTOMER_STANDARD)
void OsdDispShowLogo(void);
#endif
void COsdShowPageText(BYTE PageNo);
void OsdDispHotKeyBacklightMenu(void);

// Eric_20180306_Delete : Start ---------------------------------
// WORD OsdDispDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
// void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState);
// void OsdDispMainMenuItemIndication2(BYTE ucItem, BYTE ucAmount, BYTE ucState);//add for New Advance Menu flow
// void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
// void OsdDispClearSelectColor(BYTE ucUpDown);

//    #if(_VGA_SUPPORT == _ON)
//    void OsdDispMainSubString(BYTE ucState);
//    #endif
//
//    void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor);
void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState);
void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState);
// void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption);
// void OsdDispClearArrow(BYTE ucUpDown);
// void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious);
// void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary);

void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue);
// WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
// void OsdDispClearSliderAndNumber(void);
// void OsdDispHotKeyOptionMenu(BYTE ucOption);
void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption);
void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
void OsdDispHotKeySourceMenu(void);
// void OsdDispPanelUniformityMsgSwitch(void);

// void OsdDispShowInformation(void);
#if ((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
void OsdDispOsdRotateSwitch(void);
#endif
// void OsdDispAdvanceMenuReDraw(bit bRedrawLevel);
// bit OsdDispAdvanceItemCountbyKeyMessage(void);
// BYTE OsdDispAdvanceIconGet(BYTE ucIndex);
// void OsdDispAdvanceItemSwitch(BYTE ucIndex);
// void OsdDispAdvanceItemSelect(BYTE ucIndex);

// Eric_20180306_Delete : End ---------------------------------

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
BYTE OsdDisplayGetSourcePortString(void)
{
	switch (SysSourceGetInputPort())
	{
#if (_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
	case _A0_INPUT_PORT:
		return _STRING_A0_PORT;
#endif
#if (_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
	case _D0_INPUT_PORT:
		return _STRING_D0_PORT;
#endif
#if (_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
	case _D1_INPUT_PORT:
		return _STRING_D1_PORT;
#endif
#if (_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
	case _D2_INPUT_PORT:
		return _STRING_D2_PORT;
#endif
#if (_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
	case _D3_INPUT_PORT:
		return _STRING_D3_PORT;
#endif
#if (_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
	case _D4_INPUT_PORT:
		return _STRING_D4_PORT;
#endif
#if (_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
	case _D5_INPUT_PORT:
		return _STRING_D5_PORT;
#endif
#if (_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
	case _D6_INPUT_PORT:
		return _STRING_D6_PORT;
#endif
	default:
		return _STRING_A0_PORT;
	}
}

//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : Source Port Number
//--------------------------------------------------
BYTE OsdDispJudgeSourceType(void)
{
	BYTE ucOsdSourcePort = _VGA_A0;

	switch (SysSourceGetInputPort())
	{
#if (_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
	case _A0_INPUT_PORT:
		ucOsdSourcePort = _VGA_A0;
		return ucOsdSourcePort;
#endif

#if (_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
	case _D0_INPUT_PORT:
#if (_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
		ucOsdSourcePort = _DVI_D0;
#endif

#if ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
		ucOsdSourcePort = _HDMI_D0;
#endif

#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
		ucOsdSourcePort = _DP_D0;
#endif
		return ucOsdSourcePort;
#endif

#if (_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
	case _D1_INPUT_PORT:
#if (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
		ucOsdSourcePort = _DVI_D1;
#endif

#if ((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
		ucOsdSourcePort = _HDMI_D1;
#endif

#if (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
		ucOsdSourcePort = _DP_D1;
#endif
		return ucOsdSourcePort;
#endif

#if (_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
	case _D2_INPUT_PORT:
#if ((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
		if (_DVI_D2 > 0x04)
		{
			ucOsdSourcePort = 0x03;
		}
		else
		{
			ucOsdSourcePort = _DVI_D2;
		}
#endif

#if ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
		if (_HDMI_D2 > 0x12)
		{
			ucOsdSourcePort = 0x11;
		}
		else
		{
			ucOsdSourcePort = _HDMI_D2;
		}
#endif

#if (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
		if (_DP_D2 > 0x10)
		{
			ucOsdSourcePort = 0x0F;
		}
		else
		{
			ucOsdSourcePort = _DP_D2;
		}
#endif
		return ucOsdSourcePort;
#endif

#if (_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
	case _D3_INPUT_PORT:
#if ((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
		if (_DVI_D3 > 0x04)
		{
			ucOsdSourcePort = 0x03;
		}
		else
		{
			ucOsdSourcePort = _DVI_D3;
		}
#endif

#if ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
		if (_HDMI_D3 > 0x12)
		{
			ucOsdSourcePort = 0x11;
		}
		else
		{
			ucOsdSourcePort = _HDMI_D3;
		}
#endif
		return ucOsdSourcePort;
#endif

#if (_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
	case _D4_INPUT_PORT:
#if ((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
		if (_DVI_D4 > 0x04)
		{
			ucOsdSourcePort = 0x03;
		}
		else
		{
			ucOsdSourcePort = _DVI_D4;
		}
#endif

#if ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
		if (_HDMI_D4 > 0x12)
		{
			ucOsdSourcePort = 0x11;
		}
		else
		{
			ucOsdSourcePort = _HDMI_D4;
		}
#endif
		return ucOsdSourcePort;
#endif

#if (_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
	case _D5_INPUT_PORT:
#if (_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
		if (_DVI_D5 > 0x04)
		{
			ucOsdSourcePort = 0x03;
		}
		else
		{
			ucOsdSourcePort = _DVI_D5;
		}
#endif

#if ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
		if (_HDMI_D5 > 0x12)
		{
			ucOsdSourcePort = 0x11;
		}
		else
		{
			ucOsdSourcePort = _HDMI_D5;
		}
#endif
		return ucOsdSourcePort;
#endif

#if (_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
	case _D6_INPUT_PORT:
#if (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
		if (_DP_D6 > 0x10)
		{
			ucOsdSourcePort = 0x0F;
		}
		else
		{
			ucOsdSourcePort = _DP_D6;
		}
#endif
		return ucOsdSourcePort;
#endif

	default:
		return ucOsdSourcePort;
	}
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispDisableOsd(void)
{

	SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
	SET_OSD_STATE(_MENU_NONE);
	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	OsdFuncDisableOsd();
	OsdFuncCloseWindow(_OSD_WINDOW_ALL);
	g_ucOsdWidth = 0;
	g_ucOsdHeight = 0;
	g_ucOsdWidthB = 0;
	g_ucOsdHeightB = 0;
	SET_OSD_DOUBLE_SIZE(_OFF);
}
#if (_CUSTOMER_TYPE != _CUSTOMER_STANDARD)
void OsdDispDisableOsd2(void) // LOGO ��
{
	SET_OSD_STATE(_MENU_NONE);
	SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	OsdFuncDisableOsd();
	OsdFuncCloseWindow(_OSD_WINDOW_ALL);
	g_ucOsdWidth = 0;
	g_ucOsdHeight = 0;
	g_ucOsdWidthB = 0;
	g_ucOsdHeightB = 0;
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
// void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
//{
//    WORD usx, usy;
//
//    if(ucType == _POS_PERCENT)
//    {
// #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//        {
//            usx = 5 + ((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdWidth * 18) / 4) * usHPos) / _OSD_H_POS_MAX;
//            usy = 3 + ((DWORD)(_PANEL_DV_HEIGHT - (WORD)g_ucOsdHeight * 12) * usVPos ) / _OSD_V_POS_MAX;
//        }
//        else
//        {
//            usx = 5 + ((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdWidth * 12) / 4) * usHPos) / _OSD_H_POS_MAX;
//            usy = 3 + ((DWORD)(_PANEL_DV_HEIGHT - (WORD)g_ucOsdHeight * 18) * usVPos ) / _OSD_V_POS_MAX;
//        }
// #elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
// #if 1//(_PCB_TYPE == _RL6432_SANC2785_1A1DP1HDMI1DUALDVI_DPTX_LVDS)
//        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//        {
//            usx =  ((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdHeight * 18) / 4) * usHPos) / _OSD_H_POS_MAX;
//            usy =  ((DWORD)(_PANEL_DV_HEIGHT - (WORD)g_ucOsdWidth * 12) * usVPos ) / _OSD_V_POS_MAX;
//        }
//        else
//        {
//           if(usHPos == 0)
//            {
//               usx =  (((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdWidth * 12) / 4 *2 ) * usHPos) / _OSD_H_POS_MAX)-1;
//            }
//           else
//            {
//               usx =  (((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdWidth * 12 *2) / 4) * usHPos) / _OSD_H_POS_MAX);
//            }
//
//               usy =  ((DWORD)(_PANEL_DV_HEIGHT - (WORD)g_ucOsdHeight * 18 * 2) * usVPos ) / _OSD_V_POS_MAX;
//        }
//
// #else
//        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//        {
//            usx = 5 + ((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdHeight * 18) / 4) * usHPos) / _OSD_H_POS_MAX;
//            usy = 3 + ((DWORD)(_PANEL_DV_HEIGHT - (WORD)g_ucOsdWidth * 12) * usVPos ) / _OSD_V_POS_MAX;
//        }
//        else
//        {
//            usx = 5 + ((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdWidth * 12) / 4) * usHPos) / _OSD_H_POS_MAX;
//            usy = 3 + ((DWORD)(_PANEL_DV_HEIGHT - (WORD)g_ucOsdHeight * 18) * usVPos ) / _OSD_V_POS_MAX;
//        }
// #endif
// #else
//        usx = 5 + ((DWORD)((_PANEL_DH_WIDTH - (WORD)g_ucOsdWidth * 12) / 4) * usHPos) / _OSD_H_POS_MAX;
//        usy = 3 + ((DWORD)(_PANEL_DV_HEIGHT - (WORD)g_ucOsdHeight * 18) * usVPos ) / _OSD_V_POS_MAX;
//
// #endif
//
//    }
//    else
//    {
//        usx = usHPos;
//        usy = usVPos;
//    }
//// Lee add for osd mute     20141015 start//
////    if(usVPos<50)//
////    {
//        //if(GET_OSD_BACKLIGHT()>95)
////        {
////            ScalerTimerDelayXms(100);
// //       }
////    }
//// Lee add for osd mute     20141015 end//
//    OsdFuncSetPosition(enumOsdPositionType, usx, usy);
//}

void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
{
	DWORD ulX = 0;
	DWORD ulY = 0;
	BYTE ucFonWidth = 12;
	BYTE ucFonHeight = 18;
	BYTE ucHorizontalDelayStep = 4;
	BYTE ucTempWidth = g_ucOsdWidth;
	BYTE ucTempHeight = g_ucOsdHeight;

	if ((enumOsdPositionType == _OSD_POSITION_GLOBAL_B) ||
		(enumOsdPositionType == _OSD_POSITION_FONT_B))
	{
		ucTempWidth = g_ucOsdWidthB;
		ucTempHeight = g_ucOsdHeightB;
	}

	if (ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_1_PIXEL)
	{
		ucHorizontalDelayStep = 1;
	}

	if (GET_OSD_DOUBLE_SIZE() == _ON)
	{
		ucFonWidth *= 2;
		ucFonHeight *= 2;
	}

	if (ucType == _POS_PERCENT)
	{
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
		if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
			(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
		{
			ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
			ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
		}
		else
		{
			ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
			ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
		}
#elif (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)

		if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
		{
			ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempHeight * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
			ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempWidth * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
		}
		else
		{
			ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
			ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
		}

#else
		ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MA
																													  ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;

#endif
	}
	else
	{
		// Notice!!! if osd set double size need to chek real position
		ulX = usHPos;
		ulY = usVPos;
	}
	if (GET_OSD_DOUBLE_SIZE() == _ON)
	{
		ulX = ulX / 2;
		ulY = ulY / 2;
	}

	OsdFuncSetPosition(enumOsdPositionType, ulX, ulY);

	// DebugMessageYHJ("g_ucOsdWidth", g_ucOsdWidth);
	// DebugMessageYHJ("g_ucOsdHeight", g_ucOsdHeight);
	// DebugMessageYHJ("usHPos", usHPos);
	// DebugMessageYHJ("usVPos", usVPos);
	// DebugMessageYHJ("ulX", ulX);
	// DebugMessageYHJ("ulY", ulY);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor)
{
	BYTE ucRow = 4;
	BYTE ucCol = 4;
	BYTE ucFontPage = _PFONT_PAGE_0;
	WORD usIconLoad = 0;

	ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
	ucCol = COL(4) + ((ucIconPos % 4) * 10);

	if (usIcon == _MENU_NONE)
	{
		OsdFuncClearOsd(ucRow, (ucCol - 2), WIDTH(10), HEIGHT(5));
		return;
	}

	// icon
	if ((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D6_PORT))
	{
		switch (usIcon)
		{
		case _ICON_A0_PORT:
			usIconLoad = _A0_INPUT_TYPE;
			break;
		case _ICON_D0_PORT:
			usIconLoad = _D0_INPUT_TYPE;
			break;
		case _ICON_D1_PORT:
			usIconLoad = _D1_INPUT_TYPE;
			break;
		case _ICON_D2_PORT:
			usIconLoad = _D2_INPUT_TYPE;
			break;
		case _ICON_D3_PORT:
			usIconLoad = _D3_INPUT_TYPE;
			break;
		case _ICON_D4_PORT:
			usIconLoad = _D4_INPUT_TYPE;
			break;
		case _ICON_D5_PORT:
			usIconLoad = _D5_INPUT_TYPE;
			break;
		case _ICON_D6_PORT:
			usIconLoad = _D6_INPUT_TYPE;
			break;
		default:
			break;
		}

		OsdFontVLCDynamicLoadIcon(ucIconPos, usIconLoad);
	}
	else
	{
		OsdFontVLCDynamicLoadIcon(ucIconPos, usIcon);
	}
	OsdFontPut1BitMainMenuIcon(ucRow, ucCol, (_1DYNAMIC_ICON_START + (ucIconPos * 24)), ucColor, _CP_BG);

	// string
	ucRow += 4;
	ucCol -= 2;
	OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));

	if ((ucIconPos / 4) > 0)
	{
		ucFontPage = _PFONT_PAGE_1;
	}

	if ((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D6_PORT))
	{
		OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, (usIcon - _ICON_INPUT_END + _STRIN_END), COLOR(ucColor, _CP_BG), _ENGLISH);
	}
	else
	{
		OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, usIcon - 1, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
	}
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState)
{
	BYTE ucRow, ucCol;
	BYTE ucWin = _OSD_WINDOW_8;		  //_OSD_WINDOW_4_1;
	BYTE ucWinColor = _CP_ORANGE;	  //_CP_BLUE;
	BYTE ucForegroundColor = _CP_RED; //_CP_ORANGE;

	ucCol = 2; // ((ucIconPos / 4) ? ROW(14) : ROW(4));

	ucRow = 2 + ucIconPos * 4;

	if (ucState == _OSD_UNSELECT)
	{
		ucWinColor = _CP_GREEN_119;
		ucForegroundColor = _CP_BLUE_65;
	}
	else if (ucState == _OSD_PRE_SELECT)
	{
		ucForegroundColor = _CP_BLUE_120;
	}
	else if (ucState == _OSD_SELECT_ADJUST)
	{
		ucForegroundColor = _CP_ORANGE_DARK;
	}

	// OsdFontPut1FuncTableForm(2, 2, _EDGE_LINE,g_ucOsdWidth/5-1 ,3,ucForegroundColor,_CP_BLUE_65,_ARC_WINDOW_0);
	// OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(21), HEIGHT(10), ucWinColor, ucForegroundColor, _CP_ORANGE);

	OsdFontPut1FuncTableForm(ucRow, ucCol, _EDGE_LINE, _OSD_MAIN_MENU_LV1_LINE_WIDTH, 3, ucForegroundColor, _CP_BLUE_65, _ARC_WINDOW_0);
	// OsdFontPut1FuncTableForm(ucRow, ucCol, _EDGE_LINE,g_ucOsdWidth/5-1 ,3,ucForegroundColor,_CP_BLUE_65,_ARC_WINDOW_0);
}

void OsdDispMainMenukeySlideAndOption(BYTE ucOsdPositionState, BYTE OSDState, BYTE SlideNum, BYTE MenuExit, BYTE type)
{

	BYTE ucrow, uccol, ucFontPoint;

	// WORD g_usAdjustValueNum = 0;

	ucrow = 0;
	uccol = 0;
	ucFontPoint = SlideNum + 3;
	// OSDstate=GET_OSD_STATE();

	if (type == 0)
	{
		switch (ucOsdPositionState / 3)
		{
		case 0:
			ucrow = _OSD_NUMBER_1_ROW;
			break;

		case 1:
			ucrow = _OSD_NUMBER_2_ROW;

			break;
		case 2:
			ucrow = _OSD_NUMBER_3_ROW;

			break;
		default:
			break;
		}
		switch (ucOsdPositionState % 3)
		{
		case 0:
			uccol = _OSD_NUMBER_2_COL;
			break;

		case 1:
			uccol = _OSD_NUMBER_4_COL;

			break;
		case 2:
			uccol = _OSD_NUMBER_6_COL;

			break;
		default:
			break;
		}
	switch (OSDState)
	{
	case _MENU_PICTURE_BACKLIGHT_ADJUST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
		// if (MenuExit == 1)
		// {
		// 	OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue / 100, SlideNum, _UNSELECT);
		// 	OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET - 5), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		// }
		// else
		// {
		// 	OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue / 100, SlideNum, _SELECT);
		// 	OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET - 5), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		// }
		break;

	case _MENU_PICTURE_BRIGHTNESS_ADJUST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
		break;

	case _MENU_PICTURE_CONTRAST_ADJUST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
		// DebugMessageSystem(" @   GET_OSD_CONTRAST  ",GET_OSD_CONTRAST () );
		break;

	case _MENU_PICTURE_SHARPNESS_ADJUST:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _OFF, _ON);
		SET_OSD_SHARPNESS(g_usAdjustValue);

		if (MenuExit == 1)
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		}
		else
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_SELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		}
		return;

	case _MENU_PICTURE_HUE_ADJUST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_HUE(), _HUE_MAX, _HUE_MIN, _HUE_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_HUE(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER));
		break;

	case _MENU_PICTURE_SATURATION_ADJUST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SATURATION(), _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER));
		break;

	case _MENU_OSDSETTINGS_OSD_HPOS_ADJUST:

		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_HPOS(), _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OFF, _ON);
		SET_OSD_HPOS(g_usAdjustValue);
		g_usAdjustValue = GET_OSD_HPOS();
		break;

	case _MENU_OSDSETTINGS_OSD_VPOS_ADJUST:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VPOS(), _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OFF, _ON);
		SET_OSD_VPOS(g_usAdjustValue);
		g_usAdjustValue = GET_OSD_VPOS();
		break;
	case _MENU_OSDSETTINGS_TRNASPARENCY_ADJUST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_TRANSPARENCY_STATUS(), _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
		// g_usAdjustValue =( (BYTE)OsdDisplayDetOverRange((g_usAdjustValue/10), 10, 0, _OFF)*10);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_TRANSPARENCY_STATUS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER));
		break;

	case _MENU_OSDSETTINGS_MENU_TIME_ADJUST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_TIME_OUT(), _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
		break;

	case _MENU_COLOR_TEMP_USER_ADJUST_R:
		// g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		// SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER));
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER));
		DebugMessageSystem(" @   GET_COLOR_TEMP_TYPE_USER_R  ", GET_COLOR_TEMP_TYPE_USER_R());
		break;

	case _MENU_COLOR_TEMP_USER_ADJUST_G:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER));
		DebugMessageSystem(" @   GET_COLOR_TEMP_TYPE_USER_G  ", GET_COLOR_TEMP_TYPE_USER_G());
		break;

	case _MENU_COLOR_TEMP_USER_ADJUST_B:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER));
		//_MENU_COLOR_TEMP_USER_ADJUST_G
		DebugMessageSystem(" @   GET_COLOR_TEMP_TYPE_USER_B  ", GET_COLOR_TEMP_TYPE_USER_B());
		break;

	case _MENU_AUDIO_ADJUST:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF, _ON);
		SET_OSD_VOLUME(g_usAdjustValue);
		break;

#if (_ENABLE_VIDEO_WALL == _ON)
	case _MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VIDEO_WALL_DISP_NUM(), GetVideoWallDisplayNumber(), _VIDEO_WALL_DISP_NUM_MIN, _OFF, _ON);
		SET_OSD_VIDEO_WALL_DISP_NUM(g_usAdjustValue);
		if (MenuExit == 1)
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_DISP_NUM(), GetVideoWallDisplayNumber(), _VIDEO_WALL_DISP_NUM_MIN, _VIDEO_WALL_DISP_NUM_CENTER());
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		}
		else
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_DISP_NUM(), GetVideoWallDisplayNumber(), _VIDEO_WALL_DISP_NUM_MIN, _VIDEO_WALL_DISP_NUM_CENTER());
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		}
		return;

	case _MENU_OTHERS_VIDEO_WALL_HNUM_ADJ:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VIDEO_WALL_H_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _OFF, _ON);
		SET_OSD_VIDEO_WALL_H_NUM(g_usAdjustValue);
		if (MenuExit == 1)
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_H_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _VIDEO_WALL_HV_NUM_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		}
		else
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_H_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _VIDEO_WALL_HV_NUM_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		}
		return;

	case _MENU_OTHERS_VIDEO_WALL_VNUM_ADJ:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VIDEO_WALL_V_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _OFF, _ON);
		SET_OSD_VIDEO_WALL_V_NUM(g_usAdjustValue);
		if (MenuExit == 1)
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_V_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _VIDEO_WALL_HV_NUM_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		}
		else
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_V_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _VIDEO_WALL_HV_NUM_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		}
		return;

	case _MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VIDEO_WALL_RS232ID(), GetVideoWallDisplayNumber(), _VIDEO_WALL_RS232ID_MIN, _OFF, _ON);
		SET_OSD_VIDEO_WALL_RS232ID(g_usAdjustValue);
		if (MenuExit == 1)
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_RS232ID(), GetVideoWallDisplayNumber(), _VIDEO_WALL_RS232ID_MIN, _VIDEO_WALL_RS232ID_CENTER());
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		}
		else
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_RS232ID(), GetVideoWallDisplayNumber(), _VIDEO_WALL_RS232ID_MIN, _VIDEO_WALL_RS232ID_CENTER());
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		}
		return;
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
	case _MENU_OTHERS_FAN_PWM1_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM1(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_FAN_PWM1(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER));
		// if (MenuExit == 1)
		//{
		//  OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		//  OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		//}
		// else
		//{
		// OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		// OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		//}
		break;

	case _MENU_OTHERS_FAN_PWM2_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM2(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_FAN_PWM2(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER));
		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_FAN_PWM2(), 100, 0, _OFF, _ON);
		// SET_OSD_FAN_PWM2(g_usAdjustValue);
		// if (MenuExit == 1)
		//{
		//  OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		//  g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM2(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		//  OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		//}
		// else
		//{
		// OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		// g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM2(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		// OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		//}
		break;

	case _MENU_OTHERS_FAN_PWM3_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM3(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_FAN_PWM3(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER));

		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_FAN_PWM3(), 100, 0, _OFF, _ON);
		// SET_OSD_FAN_PWM3(g_usAdjustValue);
		// if (MenuExit == 1)
		//{
		//  OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		//  g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM3(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		//  OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		//}
		// else
		//{
		// OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		// g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM3(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		// OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		//}
		break;

	case _MENU_OTHERS_FAN_PWM4_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM4(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
		SET_OSD_FAN_PWM4(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER));

		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_FAN_PWM4(), 100, 0, _OFF, _ON);
		// SET_OSD_FAN_PWM4(g_usAdjustValue);
		// if (MenuExit == 1)
		//{
		//  OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		//  g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM4(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		//  OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		//}
		// else
		//{
		// OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		// g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM4(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		// OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		//}
		break;

	case _MENU_OTHERS_SHUTDOWN_TEMP_ADJ:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_SHUTDOWN_TEMP(), 85, 60, _OFF, _ON);
		SET_OSD_SHUTDOWN_TEMP(g_usAdjustValue);
		if (MenuExit == 1)
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHUTDOWN_TEMP(), _SHUTDOWN_TEMP_MAX, _SHUTDOWN_TEMP_MIN, _SHUTDOWN_TEMP_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		}
		else
		{
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHUTDOWN_TEMP(), _SHUTDOWN_TEMP_MAX, _SHUTDOWN_TEMP_MIN, _SHUTDOWN_TEMP_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		}
		return;
#endif
		// case _MENU_SERVICE_BACKLIGHT_FREQ_ADJ:
		//  g_usAdjustValue = OsdDisplayDetOverRange_Frequency(GET_OSD_BACKLIGHT_FREQ(), _BACKLIGHT_FREQ_MAX, _BACKLIGHT_FREQ_MIN, _OFF);
		//  SET_OSD_BACKLIGHT_FREQ(g_usAdjustValue);

		// if (MenuExit == 1)
		// {
		//  OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET - 4), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
		//  g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT_FREQ(), _BACKLIGHT_FREQ_MAX, _BACKLIGHT_FREQ_MIN, _BACKLIGHT_FREQ_CENTER);
		//  OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);

		// }
		// else
		// {
		//  OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET - 4), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), ucFontPoint, _OSD_NUMBER_SELECT_COLOR);
		//  g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT_FREQ(), _BACKLIGHT_FREQ_MAX, _BACKLIGHT_FREQ_MIN, _BACKLIGHT_FREQ_CENTER);
		//  OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		// }
		// return;
	default:
		break;
	}

	// if(((GET_KEYMESSAGE()) ==_SELECT_KEY_MESSAGE)||(MenuExit==1))
	if (MenuExit == 1)
	{
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_UNSELECT_COLOR);
	}
	else
	{
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, SlideNum, _SELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontPoint, _OSD_NUMBER_SELECT_COLOR);
	}
}
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenu(void)
{
	BYTE ucTest = 0;

	g_ucFontPointer0 = _OSD_PAGE_0_START;
	g_ucFontPointer1 = _OSD_PAGE_1_START;
	g_ucFontPointer2 = _OSD_PAGE_2_START;

	if (ucTest == 1)
	{
		//        ScalerDDomainPatternGenAdjustColor(0, 0, 0);
		//        OsdDispDetOverRange(0, 0, 0, 0);

		//        RTDFactoryPanelUsedTimer();
		//        OsdFontPut2BitTable(0, 0, tOSD_iREALTEK, 0, 0, 0, 0);

		//        OsdWindowDrawingHighlight(0, 0, 0, 0, 0, 0, 0, 0);
		//        OsdFuncChangeIconColor1Bit(0, 0, 0, 0, 0);

		ScalerOsdDataPort(0);

		// #if(_DIGITAL_PORT_SUPPORT == _ON)
		//         ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort());
		// #endif
	}

	OsdFuncDisableOsd();
	// #if(_PANEL_IDX_NAME ==_PANEL_LG_LW550JUL_HMA1)
	//	SET_OSD_DOUBLE_SIZE(_OFF);
	// #else
	//	SET_OSD_DOUBLE_SIZE(_ON);
	// #endif
	if ((_PANEL_DH_WIDTH <= 1920) && (_PANEL_DV_HEIGHT <= 1080))
	{
		SET_OSD_DOUBLE_SIZE(_OFF);
	}
	else
	{
		SET_OSD_DOUBLE_SIZE(_ON);
	}
	OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_BLUE_120, _CP_BG));

// 20140304 Abel
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

	OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
	OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

	// Adjust Color Palette
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

	// Load Font & Icon
	OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

	OsdFontVLCLoadFont(_FONT1_GLOBAL);
	// OsdFontVLCLoadFont(_FONT2_ICON_MENU);
	OsdFontVLCLoadFont(_FOUR_CORNER);
	OsdFontVLCLoadFont(_MAIN_MENU_2BIT_ICON);

	// Background window
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
		(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
	}
	else
#endif
	{
		// OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( g_ucOsdHeight/2), _CP_BLUE_120);
		// OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( g_ucOsdHeight/2+1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)), _CP_BLUE_120 );//_CP_LIGHTBLUE
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(1), COL(1), WIDTH(g_ucOsdWidth - 2), HEIGHT((g_ucOsdHeight - 2)), _CP_BLUE_65);
		OsdFontPut1FuncTableForm(0, 0, _LEFT_CORNER_0, g_ucOsdWidth - 2, g_ucOsdHeight - 2, _CP_BLUE_65, _CP_BG, _QUADRANGLE_WINDOW_0);
		OsdFontPut1FuncHLine(1, 0, _WHITE_EDGE_1, g_ucOsdWidth, _CP_WHITE, _CP_BLUE_65);
		OsdFontPut1FuncHLine(24, 0, _WHITE_EDGE_1, g_ucOsdWidth, _CP_WHITE, _CP_BLUE_65);
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		// OsdFontPut1FuncTableForm(2, 54, _EDGE_LINE,16 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
	}

	//	OsdFontPut2BitTable(ROW(8), COL(8), tiOSD_MAIN_COLORTEMP_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_120) ,COLOR1(_CP_BLACK) ,COLOR2(_CP_YELLOW) ,COLOR3(_CP_WHITE));

	OsdFontPut2BitTable(ROW(_OSD_NUMBER_5_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_BIR_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_BLACK), COLOR2(_CP_YELLOW), COLOR3(_CP_WHITE));
	OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(4), COL(7), _PFONT_PAGE_0, _STRING_PICTURE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(_OSD_NUMBER_6_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_COLORTEMP_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_GREEN_66), COLOR2(_CP_GREEN_119), COLOR3(_CP_RED));
	OsdFontPut1FuncHLine(10, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(8), COL(7), _PFONT_PAGE_0, _STRING_COLOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(11), COL(2), tiOSD_MAIN_OSDSETTING_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLUE_65), COLOR3(_CP_LIGHTBLUE));
	OsdFontPut1FuncHLine(14, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(12), COL(7), _PFONT_PAGE_0, _STRING_ADVANCE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(15), COL(2), tiOSD_MAIN_MISC_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_GREEN_66), COLOR3(_CP_BLUE_65));
	OsdFontPut1FuncHLine(18, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(16), COL(7), _PFONT_PAGE_0, _STRING_SETUP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(19), COL(2), tiOSD_MAIN_RESET_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLACK), COLOR3(_CP_GREEN_66));
	OsdFontPut1FuncHLine(22, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(20), COL(7), _PFONT_PAGE_0, _STRING_OTHER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	// OsdPropPutString(ROW(_OSD_NUMBER_13_ROW + 3), COL(_OSD_NUMBER_1_COL + 20), _PFONT_PAGE_0, _STRING_VERSION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL+36), _PFONT_PAGE_0, _STRING_NOW_RESOLUTION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	// OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL+36), _PFONT_PAGE_0, _STRING_VERSION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

	// switch(SysSourceGetInputPort())
	//	{
	//
	// #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
	//				case _A0_INPUT_PORT:
	//					break;
	// #endif
	//
	// #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
	//				case _D0_INPUT_PORT:
	//					OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_DP, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	//					break;
	// #endif
	//
	// #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
	//				case _D1_INPUT_PORT:
	//					OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_DP, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	//					break;
	//			// return _STRING_D1_PORT;
	// #endif
	//
	// #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
	//				case _D2_INPUT_PORT:
	//					OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_HDMI, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	//					break;
	//				  //  return _STRING_D2_PORT;
	// #endif
	//
	// #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
	//				case _D3_INPUT_PORT:
	//					OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_HDMI, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	//					break;
	//			//	return _STRING_D3_PORT;
	// #endif
	// #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
	//				case _D4_INPUT_PORT:
	//					 break;
	//			//	return _STRING_D4_PORT;
	// #endif
	//
	// #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
	//				case _D5_INPUT_PORT:
	//					break;
	// #endif
	//
	// #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
	//				case _D6_INPUT_PORT:
	//					break;
	//
	// #endif
	//				default:
	//				break ;
	//				  // return _STRING_A0_PORT;
	//	}

	COsdShowPageText(_MENU_PICTURE);

	OsdDispMainMenuItemSelection(0, _OSD_SELECT);

	ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());

	if (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
	{
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, (_OSD_H_POS_MAX - GET_OSD_HPOS()), (_OSD_V_POS_MAX - GET_OSD_VPOS()));
	}
	else
	{
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
	}

	// Osd Enable
	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	OsdFuncEnableOsd();
}

#if 0
void OsdDispLeftMenu(void)
{
    BYTE ucTest = 0;

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    if(ucTest == 1)
    {
     //   ScalerDDomainPatternGenAdjustColor(0, 0, 0);

     //   OsdDispDetOverRange(0, 0, 0, 0);

      //  OSTARFactoryPanelUsedTimer();
      //  OsdFontPut2BitTable(0, 0, tOSD_iREALTEK, 0, 0, 0, 0);
        
//        OsdWindowDrawingHighlight(0, 0, 0, 0, 0, 0, 0, 0);
//        OsdFuncChangeIconColor1Bit(0, 0, 0 , 0, 0);

       ScalerOsdDataPort(0);

//#if(_DIGITAL_PORT_SUPPORT == _ON)
       // ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort());
//#endif

    }

    OsdFuncDisableOsd();

    OsdFuncApplyMap(WIDTH(_OSD_LEFT_KEY_WIDTH), HEIGHT(_OSD_LEFT_KEY_HEIGHT), COLOR(_CP_BLUE_120, _CP_BG));

//20140304 Abel
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_LEFT_KEY_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    //OsdFontVLCLoadFont(_FONT2_ICON_MENU);
	 OsdFontVLCLoadFont(_LEFT_MENU_TIME_ICON);
	 OsdFontVLCLoadFont(_LEFT_MENU_AIM_ICON);
	 OsdFontVLCLoadFont(_FOUR_CORNER);
	 OsdFontVLCLoadFont(_LEFT_MENU_NUMBER_ICON);
   // Background window
   //20140210 Abel Modify
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
   
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( (g_ucOsdHeight/2)-1), _CP_GREEN_119);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( (g_ucOsdHeight/2)-1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)+1), _CP_GRAY_1 );//_CP_LIGHTBLUE
	 }
    else
#endif
    {
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight)), _CP_BLUE_65 );
		OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_MENU, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		if(GET_OSD_Left_Menu_Choose()==_LEFT_AIM)
		{

			SET_OSD_STATE(_Menu_LEFTKEY_GAME);
			OsdThreeColorChooseTableForm(7, 13,_EDGE_LINE,22 ,10,_CP_WHITE, _CP_BLUE_65,_CP_WHITE,0);
			OsdThreeColorChooseTableForm(7, 40,_EDGE_LINE,22 ,10,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
			OsdFontPut1BitMainMenuIcon(11, 22, _LEFT_MENU_AIM_ICON_START , _CP_ORANGE_H, _CP_WHITE);	 
			OsdFontPut1BitMainMenuIcon(11, 49, _LEFT_MENU_TIME_ICON_START , _CP_WHITE, _CP_BG);
		}
		else 
		{

			SET_OSD_STATE(_Menu_LEFTKEY_TIMER);
			OsdThreeColorChooseTableForm(7, 13,_EDGE_LINE,22 ,10,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
			OsdThreeColorChooseTableForm(7, 40,_EDGE_LINE,22 ,10,_CP_WHITE, _CP_BLUE_65,_CP_WHITE,0);
			OsdFontPut1BitMainMenuIcon(11, 22, _LEFT_MENU_AIM_ICON_START , _CP_WHITE, _CP_BG);	 
			OsdFontPut1BitMainMenuIcon(11, 49, _LEFT_MENU_TIME_ICON_START , _CP_ORANGE_H, _CP_WHITE);

		}
  //background    
    }

	
	

if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
  {
       OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, (_OSD_H_POS_MAX-GET_OSD_HPOS()), (_OSD_V_POS_MAX-GET_OSD_VPOS()));
  }  
else
  {
       OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,GET_OSD_HPOS(), GET_OSD_VPOS());
}



    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();

}

 void OsdDispLeftAimMenu(void)
 {
	 BYTE ucTest = 0;
 
	 g_ucFontPointer0 = _OSD_PAGE_0_START;
	 g_ucFontPointer1 = _OSD_PAGE_1_START;
	 g_ucFontPointer2 = _OSD_PAGE_2_START;
 
	 if(ucTest == 1)
	 {
	  //   ScalerDDomainPatternGenAdjustColor(0, 0, 0);
 
	  //   OsdDispDetOverRange(0, 0, 0, 0);
 
	   //  OSTARFactoryPanelUsedTimer();
	   //  OsdFontPut2BitTable(0, 0, tOSD_iREALTEK, 0, 0, 0, 0);
		 
 // 	   OsdWindowDrawingHighlight(0, 0, 0, 0, 0, 0, 0, 0);
 // 	   OsdFuncChangeIconColor1Bit(0, 0, 0 , 0, 0);
 
		ScalerOsdDataPort(0);
 
 //#if(_DIGITAL_PORT_SUPPORT == _ON)
		// ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort());
 //#endif
 
	 }
 
	 OsdFuncDisableOsd();
 
	 OsdFuncApplyMap(WIDTH(_OSD_LEFT_KEY_AIM_WIDTH), HEIGHT(_OSD_LEFT_KEY_AIM_HEIGHT), COLOR(_CP_BG, _CP_BG));
 
 //20140304 Abel
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	 ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_LEFT_KEY_AIM_HEIGHT), _DISABLE, 0, _ENABLE);
#endif
 
	 //OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
	 OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
 
	 // Adjust Color Palette
	 OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
	 
	 OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);	
	 OsdFuncTransparency(255); 
	 // Load Font & Icon
	 OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
 
	 OsdFontVLCLoadFont(_FONT1_GLOBAL);
	 //OsdFontVLCLoadFont(_FONT2_ICON_MENU);
	  OsdFontVLCLoadFont(_LEFT_MENU_TIME_ICON);
	  OsdFontVLCLoadFont(_LEFT_MENU_AIM_ICON);
	  OsdFontVLCLoadFont(_FOUR_CORNER);
 
	// Background window
	//20140210 Abel Modify
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	 if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
	 {

		 OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( (g_ucOsdHeight/2)-1), _CP_GREEN_119);
		 OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( (g_ucOsdHeight/2)-1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)+1), _CP_GRAY_1 );//_CP_LIGHTBLUE
	  }
	 else
#endif
	 {
	 OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight)), _CP_BG );
	 
	 //OsdFontPut1BitMainMenuIcon(0, 0, _LEFT_MENU_AIM_ICON_START+24 , _CP_BG, _CP_BG);
	 //OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
	 
	 switch(GET_OSD_AIM())
	 {
		 case _AIM_1:
			 
	 
	 
			 OsdFontPut1BitMainMenuIcon(0, 1, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
			 
			 //OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
			 break;
		 case _AIM_2:
			 
	 
			 OsdFontPut1BitMainMenuIcon(0, 1, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);
			 
			 //OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
			 break;
		 case _AIM_3:
	 
	 
			 OsdFontPut1BitMainMenuIcon(0, 1, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);
			 
			 //OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
			 break;
		 case _AIM_4:
	 
	 
			 OsdFontPut1BitMainMenuIcon(0, 1, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);
			 
			 //OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
			 break;
			 
		  default:
			  break;
	 }
 
   //background    
	 }
 
	 
	 
 
	 OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,50, 50);
 
 
 
	 // Osd Enable
	 ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	 OsdFuncEnableOsd();
 
 }
#endif
// OsdDispLeftTimerMenuAdjust

// void OsdDispRightMenu(void)
//{
//     BYTE ucTest = 0;
//
//     g_ucFontPointer0 = _OSD_PAGE_0_START;
//     g_ucFontPointer1 = _OSD_PAGE_1_START;
//     g_ucFontPointer2 = _OSD_PAGE_2_START;
//
//     if(ucTest == 1)
//     {
//      //   ScalerDDomainPatternGenAdjustColor(0, 0, 0);
//
//      //   OsdDispDetOverRange(0, 0, 0, 0);
//
//       //  OSTARFactoryPanelUsedTimer();
//       //  OsdFontPut2BitTable(0, 0, tOSD_iREALTEK, 0, 0, 0, 0);
//
////        OsdWindowDrawingHighlight(0, 0, 0, 0, 0, 0, 0, 0);
////        OsdFuncChangeIconColor1Bit(0, 0, 0 , 0, 0);
//
//       ScalerOsdDataPort(0);
//
////#if(_DIGITAL_PORT_SUPPORT == _ON)
//       // ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort());
////#endif
//
//    }
//
//    OsdFuncDisableOsd();
//
//    OsdFuncApplyMap(WIDTH(_OSD_RIGHT_KEY_WIDTH), HEIGHT(_OSD_RIGHT_KEY_HEIGHT), COLOR(_CP_BLUE_120, _CP_BG));
//
////20140304 Abel
// #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//     ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_RIGHT_KEY_HEIGHT), _DISABLE, 0, _ENABLE);
// #endif
//
//     OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
//     OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//
//     // Adjust Color Palette
//     OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
//
//     // Load Font & Icon
//     OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
//
//     OsdFontVLCLoadFont(_FONT1_GLOBAL);
//     //OsdFontVLCLoadFont(_FONT2_ICON_MENU);
//	 OsdFontVLCLoadFont(_FOUR_CORNER);
//	OsdFontVLCLoadFont(_MAIN_MENU_2BIT_ICON);
//
//    // Background window
//    //20140210 Abel Modify
// #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//     if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//     {
//
//         OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( (g_ucOsdHeight/2)-1), _CP_GREEN_119);
//         OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( (g_ucOsdHeight/2)-1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)+1), _CP_GRAY_1 );//_CP_LIGHTBLUE
//	 }
//     else
// #endif
//     {
//		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(1), COL(0), WIDTH(g_ucOsdWidth-1), HEIGHT((g_ucOsdHeight-2)), _CP_BLUE_65 );
//		OsdFontPut1FuncTableForm(0, 0, _LEFT_CORNER_0,g_ucOsdWidth -2,g_ucOsdHeight-2,_CP_BLUE_65,_CP_BG,_QUADRANGLE_WINDOW_0);
//		OsdFontPut1FuncHLine(1, 0, _WHITE_EDGE_1, g_ucOsdWidth ,_CP_WHITE, _CP_BLUE_65);
//		OsdFontPut1FuncHLine(8, 0, _WHITE_EDGE_1, g_ucOsdWidth ,_CP_WHITE, _CP_BLUE_65);
//
//
//
//
//     }
//
//
//
//
//
//     OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
//
//
//
//     // Osd Enable
//     ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//     OsdFuncEnableOsd();
//
// }

// VLC
// font put 1 bit
// font put 1 bit table
// font put 2 bit
// font put 2 bit table
// font put 4 bit
// font put 4 bit color

// Prop
// font put prop string

// window
// draw window

// 170928_02
void OsdDispHotKeyVolumeMenu(void)
{
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	EnumOsdRotateType tempRotateStatus = GET_OSD_ROTATE_STATUS();
#endif
	OsdDispDisableOsd();

	g_ucFontPointer0 = _OSD_PAGE1_0_START;
	g_ucFontPointer1 = _OSD_PAGE1_1_START;
	g_ucFontPointer2 = _OSD_PAGE1_2_START;

	OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(6), COLOR(_CP_WHITE, _CP_BG));

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(6), _DISABLE, 0, _ENABLE);
#endif

	OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
	//    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);

	OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

	// Adjust Color Palette
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

	// Load Font & Icon
	OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

	OsdFontVLCLoadFont(_FONT1_GLOBAL);

	// Background window Modify
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
	}
	else
#endif
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(7), g_ucOsdHeight, _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(7), WIDTH(g_ucOsdWidth - 7), HEIGHT(g_ucOsdHeight), _CP_LIGHTBLUE);
	}

	if (GET_OSD_VOLUME_MUTE() == _OFF)
	{
		//           OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_VOLUME);
		//		OsdFontPut1BitBackLightIcon(ROW(1), COL(2), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_ORANGE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_VOLUME);
		OsdFontPut1BitMainMenuIcon(ROW(1), COL(1), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_ORANGE, _CP_BG);

		// icon
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _SELECT);
		OsdPropShowNumber(ROW(2), COL(31), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_SELECT_COLOR);

		SET_OSD_STATE(_MENU_HOTKEY_VOLUME);
	}
	else // MUTE
	{
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_MUTE);
		OsdFontPut1BitMainMenuIcon(ROW(1), COL(1), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_ORANGE, _CP_BG);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _UNSELECT);
		// icon
		OsdPropShowNumber(ROW(2), COL(31), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_GRAY, _CP_BG));

		SET_OSD_STATE(_MENU_HOTKEY_MUTE);
	}

	ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	switch (tempRotateStatus)
	{
	case _OSD_ROTATE_DEGREE_90:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 5, 50);
		break;
	case _OSD_ROTATE_DEGREE_270:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 95, 50);
		break;
	case _OSD_ROTATE_DEGREE_180:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 5);
		break;
	default:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);
		break;
	}
	// OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

#else
	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);
#endif

	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

	OsdFuncEnableOsd();
}

void OsdDispHotKeyMuteMenu(void)
{
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	EnumOsdRotateType tempRotateStatus = GET_OSD_ROTATE_STATUS();
#endif
	OsdDispDisableOsd();

	g_ucFontPointer0 = _OSD_PAGE1_0_START;
	g_ucFontPointer1 = _OSD_PAGE1_1_START;
	g_ucFontPointer2 = _OSD_PAGE1_2_START;

	OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(6), COLOR(_CP_WHITE, _CP_BG));

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(6), _DISABLE, 0, _ENABLE);
#endif

	OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
	OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

	// Adjust Color Palette
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

	// Load Font & Icon
	OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

	OsdFontVLCLoadFont(_FONT1_GLOBAL);

	// Background window Modify
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
	}
	else
#endif
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(7), g_ucOsdHeight, _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(7), WIDTH(g_ucOsdWidth - 7), HEIGHT(g_ucOsdHeight), _CP_LIGHTBLUE);
	}

	OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_MUTE);
	OsdFontPut1BitMainMenuIcon(ROW(1), COL(1), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_GRAY, _CP_BG);

	g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
	OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _UNSELECT);
	// icon
	//	OsdDispSliderAndNumber(_MENU_HOTKEY_MUTE, GET_OSD_VOLUME());
	OsdPropShowNumber(ROW(2), COL(31), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_GRAY, _CP_BG));

	SET_OSD_STATE(_MENU_HOTKEY_MUTE);

	ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	switch (tempRotateStatus)
	{
	case _OSD_ROTATE_DEGREE_90:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 5, 50);
		break;
	case _OSD_ROTATE_DEGREE_270:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 95, 50);
		break;
	case _OSD_ROTATE_DEGREE_180:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 5);
		break;
	default:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);
		break;
	}
	// OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

#else
	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);
#endif

	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

	OsdFuncEnableOsd();
}

// void OsdDispHotKeyAudioMode(void) //Eric_171010
//{
//     OsdDispDisableOsd();
//
//     g_ucFontPointer0 = _OSD_PAGE_0_START;
//     g_ucFontPointer1 = _OSD_PAGE_1_START;
//     g_ucFontPointer2 = _OSD_PAGE_2_START;
//
//     OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));
//
// #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//     ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
// #endif
//
//     OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
////    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
//
//    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//
//    // Adjust Color Palette
//    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
//
//    // Load Font & Icon
//    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
//
//    OsdFontVLCLoadFont(_FONT1_GLOBAL);
//
//
//
//    // Background window Modify
// #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//    {
//        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
//        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
//    }
//    else
// #endif
//    {
//            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(10),HEIGHT (3 ), _CP_BLUE);
// //           OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(8), WIDTH(g_ucOsdWidth - 8), HEIGHT(g_ucOsdHeight -2), _CP_LIGHTBLUE);
//    }
//
//
//
// // OsdPropPutString(ROW(1), COL(2), _PFONT_PAGE_0, (GET_OSD_AUDIO_MODE()+_STRING_AUDIO_STANDARD), COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);
//    OsdPropPutStringCenter(ROW(1), COL(1), WIDTH(8), _PFONT_PAGE_0, (GET_OSD_AUDIO_MODE()+_STRING_AUDIO_STANDARD), COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);
//
//
//    SET_OSD_STATE(_MENU_HOTKEY_AUDIOMODE);
//   ScalerOsdDoubleFunction(_ON, _ON);
//    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 42, 45);
//
//    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//
//
//    OsdFuncEnableOsd();
//
//}
// void OsdDispHotKeyPictureMode(void) //Eric_171010
//{
//    OsdDispDisableOsd();
//
//    g_ucFontPointer0 = _OSD_PAGE_0_START;
//    g_ucFontPointer1 = _OSD_PAGE_1_START;
//    g_ucFontPointer2 = _OSD_PAGE_2_START;
//
//    OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));
//
// #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
// #endif
//
//    OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
////    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
//
//    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//
//    // Adjust Color Palette
//    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
//
//    // Load Font & Icon
//    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
//
//    OsdFontVLCLoadFont(_FONT1_GLOBAL);
//
//
//
//    // Background window Modify
// #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//    {
//        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
//        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
//    }
//    else
// #endif
//    {
//            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(10),HEIGHT (3 ), _CP_BLUE);
// //           OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(8), WIDTH(g_ucOsdWidth - 8), HEIGHT(g_ucOsdHeight -2), _CP_LIGHTBLUE);
//    }
//
//
//
// // OsdPropPutString(ROW(1), COL(2), _PFONT_PAGE_0, (GET_OSD_AUDIO_MODE()+_STRING_AUDIO_STANDARD), COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);
//    OsdPropPutStringCenter(ROW(1), COL(1), WIDTH(8), _PFONT_PAGE_0, (GET_OSD_COLOR_EFFECT()+_STRING_COLOREFFECT_STANDARD), COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);
//
//    SET_OSD_STATE(_MENU_HOTKEY_PICTUREMODE);
//   ScalerOsdDoubleFunction(_ON, _ON);
//    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 42, 45);
//
//    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//
//
//    OsdFuncEnableOsd();
//
//}
//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle, bit bNumberic)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		if (!bNumberic && GET_KEYMESSAGE() == _UP_KEY_MESSAGE)
		{
			if (usValue <= usMin)
			{
				if (bCycle == _ON)
				{
					return usMax;
				}
				else
				{
					return usMin;
				}
			}
			else
			{
				usValue--;
			}
		}
		else
		{
			if (usValue >= usMax)
			{
				if (bCycle == _ON)
				{
					return usMin;
				}
				else
				{
					return usMax;
				}
			}
			else
			{
				usValue++;
			}
		}
		break;
	case _DOWN_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		if (!bNumberic && GET_KEYMESSAGE() == _DOWN_KEY_MESSAGE)
		{
			if (usValue >= usMax)
			{
				if (bCycle == _ON)
				{
					return usMin;
				}
				else
				{
					return usMax;
				}
			}
			else
			{
				usValue++;
			}
		}
		else
		{
			if (usValue <= usMin)
			{
				if (bCycle == _ON)
				{
					return usMax;
				}
				else
				{
					return usMin;
				}
			}
			else
			{
				usValue--;
			}
		}
		break;
	default:

		break;
	}

	return usValue;
}

WORD OsdDisplayDetOverRange_Curved(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
	switch (GET_KEYMESSAGE())
	{
	case _RIGHT_KEY_MESSAGE:
		if (usValue >= usMax)
		{
			if (bCycle == _ON)
			{
				return usMin;
			}
			else
			{
				return usMax;
			}
		}
		else
		{
			if (GET_KEYREPEATSTART())
			{
				if (usValue > usMax - 3)
					usValue = usMax;
				else
					usValue = usValue + 3;
			}
			else
			{
				usValue++;
			}
		}

		break;

	case _LEFT_KEY_MESSAGE:
		if (usValue <= usMin)
		{
			if (bCycle == _ON)
			{
				return usMax;
			}
			else
			{
				return usMin;
			}
		}
		else
		{
			if (GET_KEYREPEATSTART())
			{
				if (usValue < 3)
					usValue = usMin;
				else
					usValue = usValue - 3;
			}
			else
			{
				usValue--;
			}
		}
		break;

	default:
		break;
	}

	return usValue;
}
//--------------------------------------------------
// Description  : Six Color Get One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorGetOneColor(BYTE ucColor)
{
	switch (ucColor)
	{
	case _SIXCOLOR_R:
		SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueR);
		SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationR);
		break;

	case _SIXCOLOR_Y:
		SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueY);
		SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationY);
		break;

	case _SIXCOLOR_G:
		SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueG);
		SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationG);
		break;

	case _SIXCOLOR_C:
		SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueC);
		SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationC);
		break;

	case _SIXCOLOR_B:
		SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueB);
		SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationB);
		break;

	case _SIXCOLOR_M:
		SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueM);
		SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationM);
		break;

	default:
		break;
	}
}

//--------------------------------------------------
// Description  : Six Color Set One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
// void OsdDisplaySixColorSetOneColor(BYTE ucColor)
//{
//    switch(ucColor)
//    {
//        case _SIXCOLOR_R:
//            g_stSixColorData.ucSixColorHueR = GET_OSD_SIX_COLOR_HUE();
//            g_stSixColorData.ucSixColorSaturationR = GET_OSD_SIX_COLOR_SATURATION();
//            break;
//
//        case _SIXCOLOR_Y:
//            g_stSixColorData.ucSixColorHueY = GET_OSD_SIX_COLOR_HUE();
//            g_stSixColorData.ucSixColorSaturationY = GET_OSD_SIX_COLOR_SATURATION();
//            break;
//
//        case _SIXCOLOR_G:
//            g_stSixColorData.ucSixColorHueG = GET_OSD_SIX_COLOR_HUE();
//            g_stSixColorData.ucSixColorSaturationG = GET_OSD_SIX_COLOR_SATURATION();
//            break;
//
//        case _SIXCOLOR_C:
//            g_stSixColorData.ucSixColorHueC = GET_OSD_SIX_COLOR_HUE();
//            g_stSixColorData.ucSixColorSaturationC = GET_OSD_SIX_COLOR_SATURATION();
//            break;
//
//        case _SIXCOLOR_B:
//            g_stSixColorData.ucSixColorHueB = GET_OSD_SIX_COLOR_HUE();
//            g_stSixColorData.ucSixColorSaturationB = GET_OSD_SIX_COLOR_SATURATION();
//            break;
//
//        case _SIXCOLOR_M:
//            g_stSixColorData.ucSixColorHueM = GET_OSD_SIX_COLOR_HUE();
//            g_stSixColorData.ucSixColorSaturationM = GET_OSD_SIX_COLOR_SATURATION();
//            break;
//
//        default:
//            break;
//    }
//}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage)
{
	OsdDispDisableOsd();
	// SET_OSD_DOUBLE_SIZE(_OFF)
	g_ucFontPointer0 = _OSD_PAGE1_0_START;
	g_ucFontPointer1 = _OSD_PAGE1_1_START;
	g_ucFontPointer2 = _OSD_PAGE1_2_START;

#if 0
	if (enumMessage == _OSD_DISP_CONNECT_BLUETOOTH_YESNO_MSG)
	{
		OsdFuncApplyMap(WIDTH(42), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));  //170928_01
	}
	else
#endif
	if (enumMessage == _OSD_DISP_INPUT_SIGNAL_MSG)
	{
		OsdFuncApplyMap(WIDTH(18), HEIGHT(5), COLOR(_CP_BLUE_65, _CP_BG)); // HEIGHT(5) -> 4 ���̸� ROTATE 180������ ȭ�� ����
	}
	else if (enumMessage == _OSD_DISP_MST_WARNING_MSG)
	{
		OsdFuncApplyMap(WIDTH(36), HEIGHT(8), COLOR(_CP_BLUE_65, _CP_BG));
	}
	else
	{
		OsdFuncApplyMap(WIDTH(36), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));
	}

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	if (enumMessage == _OSD_DISP_INPUT_SIGNAL_MSG)
	{
		ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(5), _DISABLE, 0, _ENABLE);
	}
	else
	{
		ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
	}
#endif

	OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
	OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

	// Adjust Color Palette
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

	// Load Font & Icon
	OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

	OsdFontVLCLoadFont(_FONT1_GLOBAL);

	// Background window Modify
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
		(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
	}
	else
#endif
	{
		if (enumMessage == _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG)
		{
			OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), g_ucOsdHeight, _CP_LIGHTBLUE);
		}
#if 0
		else if((enumMessage == _OSD_DISP_CONNECT_BLUETOOTH_YESNO_MSG) ||(enumMessage == _OSD_DISP_DISCONNECT_BLUETOOTH_YESNO_MSG) )//170928_00
		{
		    OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), g_ucOsdHeight, _CP_LIGHTBLUE);
		}
#endif
		else if (enumMessage == _OSD_DISP_INPUT_SIGNAL_MSG)
		{
			OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), g_ucOsdHeight, _CP_BLUE_65);
		}
		else
		{
			OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
			OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdWidth - 12), g_ucOsdHeight, _CP_LIGHTBLUE);
		}
	}

	//==== Show page item =======
	switch (enumMessage)
	{
	case _OSD_DISP_NOSIGNAL_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SIGNAL);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SIGNAL_TEXT_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SIGNAL_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		break;

	case _OSD_DISP_NOCABLE_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_CABLE);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_CABLE_TEXT_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_CABLE_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		break;

	case _OSD_DISP_NOSUPPORT_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SUPPORT);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SUPPORT_TEXT_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SUPPORT_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		break;

	case _OSD_DISP_FAIL_SAFE_MODE_MSG:
		OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_NO_SUPPORT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;

	case _OSD_DISP_AUTO_CONFIG_MSG:
		// itle
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_AUTO_ADJUST);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_ADJUST_TEXT_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_ADJUST_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_ADJUST_TEXT_2);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

		break;

	case _OSD_DISP_INPUT_SIGNAL_MSG:
	{
		OsdPropPutStringCenter(ROW(1), COL(0), WIDTH(18), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		OsdPropPutStringCenter(ROW(2), COL(0), WIDTH(18), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		// OsdPropPutStringCenter(ROW(2 + 2), COL(0), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_ENABLE, _OSD_DOUBLE_HEIGHT_ENABLE);
		switch (GET_OSD_ROTATE_STATUS())
		{
		case _OSD_ROTATE_DEGREE_90:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 47, 42);
			break;
		case _OSD_ROTATE_DEGREE_270:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 2, 2);
			break;
		case _OSD_ROTATE_DEGREE_180:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 2, 45);
			break;
		default:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 45, 3);
			break;
		}
		ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
		OsdFuncEnableOsd();
		ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);
	}
		return;
	case _OSD_DISP_AUTO_COLOR_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _MENU_COLOR);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_COLOR_TEXT_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_COLOR_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_COLOR_TEXT_2);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

		break;

	case _OSD_DISP_POWER_SAVING_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_POWER_SAVING);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_POWER_SAVING_TEXT_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_POWER_SAVING_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_POWER_SAVING_TEXT_2);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
		break;
	case _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_TRUN_OFF_PANEL_UNI_TEXT0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_TRUN_OFF_PANEL_UNI_TEXT1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + 6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_YES);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_NO);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(27), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

		break;
#if (_FREEZE_SUPPORT == _ON)
	case _OSD_DISP_DISABLE_FREEZE_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_FREEZE);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_FREEZE_DISABLE_TEXT_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_FREEZE_DISABLE_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_FREEZE_DISABLE_TEXT_2);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
		break;
#endif
#if (_DP_MST_SUPPORT == _ON)
	case _OSD_DISP_MST_WARNING_MSG:
		// OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DP_MST);
		// OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_MST_WARNING_MSG_0);
		// OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		// OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_MST_WARNING_MSG_1);
		// OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		// OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_MST_WARNING_MSG_2);
		// OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DP_MST);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_MST_WARNING_MSG_0);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_MST_WARNING_MSG_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_MST_WARNING_MSG_2);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
		break;
#endif
#if 0
       case _OSD_DISP_CONNECT_BLUETOOTH_YESNO_MSG:
            // title

                OsdPropPutString(ROW(3), COL(1), _PFONT_PAGE_0, _STRING_CONNECT_BLUETOOTH_MSG0, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
		  OsdPropPutString(ROW(4), COL(1), _PFONT_PAGE_1, _STRING_CONNECT_BLUETOOTH_MSG1, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
	

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_YES );
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(27 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
           ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_ENABLE, _OSD_DOUBLE_HEIGHT_ENABLE);
            break;
        case _OSD_DISP_DISCONNECT_BLUETOOTH_YESNO_MSG:
            // title
                OsdPropPutString(ROW(3), COL(1), _PFONT_PAGE_0, _STRING_DISCONNECT_BLUETOOTH_MSG0, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
		  OsdPropPutString(ROW(4), COL(1), _PFONT_PAGE_1, _STRING_DISCONNECT_BLUETOOTH_MSG1, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

//            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DISCONNECT_BLUETOOTH_TEXT0);
 //           OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_BLUE, _CP_BG);
//            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISCONNECT_BLUETOOTH_TEXT1);
//            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + 6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO );
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_YES);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(27), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
           ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_ENABLE, _OSD_DOUBLE_HEIGHT_ENABLE);
            break;
#endif
#if (_ENABLE_MENU_OLED == _ON)
	case _OSD_DISP_OFF_RS_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_OFFRS);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISP_OFFRS_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_DISP_OFFRS_TEXT_2);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		break;

	case _OSD_DISP_JB_MSG:
		// title
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_JBCOMP);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
		// icon
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISP_JB_TEXT_1);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_DISP_JB_TEXT_2);
		OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
		break;
#endif
	default:
		break;
	}

	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

	OsdFuncEnableOsd();
}

#if (_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispAutoConfigProc(void)
{
	OsdDispOsdMessage(_OSD_DISP_AUTO_CONFIG_MSG);
	UserCommonAutoConfig();
	OsdDispDisableOsd();
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayAutoBalanceProc(void)
{
	OsdDispDisableOsd();
	OsdDispOsdMessage(_OSD_DISP_AUTO_COLOR_MSG);

	if (SysSourceGetSourceType() == _SOURCE_VGA)
	{
		if (GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
		{
			// Perform auto-color for RGB
			if (ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
			{
				ScalerAutoGetAutoColorResult(&g_stAdcData);
				UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if ((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
				// Calculate YPbPr gain/offset using formula
				g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
				UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

				// Restore RGB gain/offset
				ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
			}
			else
			{
				UserCommonNVRamRestoreADCSetting();
			}
		}
#if ((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
		else
		{
			// Perform auto-color for YPbPr
			if (ScalerAutoDoWhiteBalance(_AUTO_TUNE_YPBPR) == _AUTO_SUCCESS)
			{
				ScalerAutoGetAutoColorResult(&g_stAdcData);
				UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
			}
			else
			{
				UserCommonNVRamRestoreADCSetting();
			}
		}
#endif
	}

	OsdDispDisableOsd();
	// SET_KEYMESSAGE(_HOLD_KEY_MESSAGE);
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdReset(void)
{

	BYTE ucIndex = GET_OSD_LANGUAGE();
#if (_HDR10_SUPPORT == _ON)
	int port;
#endif
#if (_HIGHLIGHT_WINDOW_SUPPORT == _ON)
	ScalerColorHLWDDomainEnable(_FUNCTION_OFF);
#endif

	OsdDispDisableOsd();

	UserCommonNVRamRestoreSystemData();
	RTDNVRamRestoreOSDData();

	RTDNVRamRestoreUserColorSetting();
	RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
	RTDNVRamRestoreSixColorData();

	RTDNVRamRestoreBriCon();
	RTDNVRamRestoreBacklight();

#if (_VGA_SUPPORT == _ON)
	UserCommonNVRamRestoreModeUserData();

	if (SysSourceGetSourceType() == _SOURCE_VGA)
	{
		SET_VGA_MODE_DO_FIRST_AUTO(_TRUE);
		UserCommonModeSearchInitalUserAndCenterData(g_stVGAModeUserData.ucModeNumber);
		UserCommonNVRamSaveModeUserData();
	}
#endif

#if (_DP_SUPPORT == _ON)
	// Set Aux Diff mode & Resistance Setting
	SET_DP_AUX_DIFF_MODE();

	SET_DP_AUX_ADJR_SETTING(UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING));

	UserCommonInterfaceDpAuxSet();
#endif

	if (ucIndex != GET_OSD_LANGUAGE())
	{
		SET_OSD_LANGUAGE(ucIndex);
		RTDNVRamSaveOSDData();
	}
	OsdFuncSetOsdItemFlag();
#if (_HDR10_SUPPORT == _ON)
	for (port = _D0_INPUT_PORT; port < _D4_INPUT_PORT; port++)
	{
		UserInterfaceGetEmbeddedEDIDData(port);
	}

	UserCommonInterfaceSetHPD(SysSourceGetInputPort());
	UserCommonHDR10SupportSwitch();
	UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
#endif

	SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

	SET_OSD_STATE(_MENU_NONE);

#if (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
	UserCommonInterfaceDataExchangeAllDataReset();
#endif
}

//--------------------------------------------------
// Description  : Logo showing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if (_CUSTOMER_TYPE == _CUSTOMER_VIMSE) // 2017.03.22 SUH-EDIT
void OsdDispShowMainLogo(void)
{
	g_ucLogoTimerCounter = 0;
	//	SET_OSD_DOUBLE_SIZE(_OFF);

	ScalerDDomainPatternGenAdjustColor(0, 0, 0);
	ScalerDDomainPatternGenEnable(_ENABLE);
	ScalerDDomainBackgroundEnable(_DISABLE);

	OsdDispDisableOsd2();
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
	//	OsdFuncApplyMap(WIDTH(30), HEIGHT(9), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));	// 0x0C
	OsdFuncApplyMap(WIDTH(60), HEIGHT(17), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG)); // 0x0C

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, g_ucOsdHeight, _DISABLE, 0, _ENABLE);
#endif
	OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
	OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);

	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(30), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	OsdWindowDrawing(_OSD_WINDOW_0, XSTART(0), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BG);

	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
	OsdFuncEnableOsd();

#if (_INSTANT_TIMER_EVENT_0 == _ON)
	ScalerTimer0SetTimerCount(16);
#endif

	SET_OSD_LOGO_ON(_ON);
}
#endif

#if (_CUSTOMER_TYPE != _CUSTOMER_STANDARD) // 2017.03.28 SUH-EDIT
void OsdDispShowLogo(void)
{
	g_ucLogoTimerCounter = 0;
	//	SET_OSD_DOUBLE_SIZE(_ON);

	ScalerDDomainPatternGenAdjustColor(0, 0, 0);
	ScalerDDomainPatternGenEnable(_ENABLE);
	ScalerDDomainBackgroundEnable(_DISABLE);

	OsdDispDisableOsd2();
	OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);
#if (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	OsdFuncApplyMap(WIDTH(0x4c), HEIGHT(7), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
	//	OsdFuncApplyMap(WIDTH(12*4+16*3), HEIGHT(9), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));	// 0x0C
#if 1
	OsdFuncApplyMap(WIDTH(12 * 4 + 44 * 3), HEIGHT(9), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG)); // 0x0C
#else
	OsdFuncApplyMap(WIDTH(12 * 4 + 16 * 3), HEIGHT(9), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG)); // 0x0C
#endif
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
	// OsdFuncApplyMap(WIDTH(57), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
	OsdFuncApplyMap(WIDTH(57), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
	// OsdFuncApplyMap(WIDTH(80), HEIGHT(18), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
	OsdFuncApplyMap(WIDTH(60), HEIGHT(20), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
#else  // #if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	OsdFuncApplyMap(WIDTH(70), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
#endif // #if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, g_ucOsdHeight, _DISABLE, 0, _ENABLE);
#endif
	OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
	OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);
#if (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO2);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO3);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO4);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO5);
#elif (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
	OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);

#endif

#if (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_RED_1, _LOGO_CP_BG));
	OsdFontPut1BitTable(ROW(0), COL(0x2c), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_RED_1, _LOGO_CP_BG));
	OsdWindowDrawing(_OSD_WINDOW_0, XSTART(1), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BG);
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
#if 1
	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO2, COLOR(_LOGO_CP_COLOR1, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(56), tiOSD_REALTEK_1BIT_LOGO3, COLOR(_LOGO_CP_COLOR2, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(112), tiOSD_REALTEK_1BIT_LOGO4, COLOR(_LOGO_CP_COLOR3, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(168), tiOSD_REALTEK_1BIT_LOGO5, COLOR(_LOGO_CP_COLOR4, _LOGO_CP_BLACK));
#elif 1
	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO2, COLOR(_LOGO_CP_COLOR1, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(28), tiOSD_REALTEK_1BIT_LOGO3, COLOR(_LOGO_CP_COLOR2, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(56), tiOSD_REALTEK_1BIT_LOGO4, COLOR(_LOGO_CP_COLOR3, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(84), tiOSD_REALTEK_1BIT_LOGO5, COLOR(_LOGO_CP_COLOR4, _LOGO_CP_BLACK));
#else
	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_COLOR1, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(28), tiOSD_REALTEK_1BIT_LOGO2, COLOR(_LOGO_CP_COLOR2, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(56), tiOSD_REALTEK_1BIT_LOGO3, COLOR(_LOGO_CP_COLOR3, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(84), tiOSD_REALTEK_1BIT_LOGO4, COLOR(_LOGO_CP_COLOR4, _LOGO_CP_BLACK));
#endif
	OsdWindowDrawing(_OSD_WINDOW_0, XSTART(0), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BG);
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLUE));
	OsdFontPut1BitTable(ROW(0), COL(14), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	// OsdWindowDrawing(_OSD_WINDOW_0, XSTART(0), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_WHITE);
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
	// OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	// OsdFontPut1BitTable(ROW(0), COL(42), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK)); //47
	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(44), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK)); // 47

#else  // #if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_RED_1, _LOGO_CP_BG));
	OsdFontPut1BitTable(ROW(0), COL(19), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
	OsdWindowDrawing(_OSD_WINDOW_0, XSTART(1), YSTART(1), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BLUE);
#endif // #if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)

	//	ScalerOsdChange1BitColor(ROW(0),  COL(19),LENGTH(_ITEM_WIDTH), HEIGHT(1), FG_COLOR(_CP_ORANGE), BG_COLOR(_CP_BG));//
#if (_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
	// ScalerOsdHorizontalDelayStep(_OSD_HORIZONTAL_DELAY_STEP_1_PIXEL);
	// OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, 0, 0);
	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
#else
	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
#endif

	OsdFuncEnableOsd();

#if (_INSTANT_TIMER_EVENT_0 == _ON)
	ScalerTimer0SetTimerCount(16);
#endif

	SET_OSD_LOGO_ON(_ON);
}
#endif

#if (_CUSTOMER_TYPE == _CUSTOMER_VIMSE) // 2017.03.22 SUH-EDIT
BYTE u8_Table[20][4] =
	{
		{1, 0, 0, 0}, // 0
		{2, 0, 0, 0}, // 1
		{3, 0, 0, 0}, // 2 - repeat start
		{2, 1, 0, 0}, // 3
		{1, 2, 0, 0}, // 4
		{0, 3, 0, 0}, // 5
		{0, 2, 1, 0}, // 6
		{0, 1, 2, 0}, // 7
		{0, 0, 3, 0}, // 8
		{0, 0, 2, 1}, // 9
		{0, 0, 1, 2}, // 10
		{0, 0, 0, 3}, // 11
		{0, 0, 1, 2}, // 12
		{0, 0, 2, 1}, // 13
		{0, 0, 3, 0}, // 14
		{0, 1, 2, 0}, // 15
		{0, 2, 1, 0}, // 16
		{0, 3, 0, 0}, // 17
		{1, 2, 0, 0}, // 18
		{2, 1, 0, 0}  // 19 -repeat ended
};
BYTE u8_Palette[4][3] =
	{
		{0xFF, 0xFF, 0xFF},
		{0xBB, 0xBA, 0xBA},
		{0x86, 0x85, 0x85},
		{0x4D, 0x4D, 0x4D}};
BYTE u8_Table_RGB[20][4] =
	{
		{_LOGO_CP_COLOR2, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 0
		{_LOGO_CP_COLOR3, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 1
		{_LOGO_CP_COLOR4, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 2 - repeat start
		{_LOGO_CP_COLOR3, _LOGO_CP_COLOR2, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 3
		{_LOGO_CP_COLOR2, _LOGO_CP_COLOR3, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 4
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR4, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 5
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR3, _LOGO_CP_COLOR2, _LOGO_CP_COLOR1}, // 6
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR2, _LOGO_CP_COLOR3, _LOGO_CP_COLOR1}, // 7
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR4, _LOGO_CP_COLOR1}, // 8
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR3, _LOGO_CP_COLOR2}, // 9
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR2, _LOGO_CP_COLOR3}, // 10
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR4}, // 11
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR2, _LOGO_CP_COLOR3}, // 12
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR3, _LOGO_CP_COLOR2}, // 13
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR1, _LOGO_CP_COLOR4, _LOGO_CP_COLOR1}, // 14
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR2, _LOGO_CP_COLOR3, _LOGO_CP_COLOR1}, // 15
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR3, _LOGO_CP_COLOR2, _LOGO_CP_COLOR1}, // 16
		{_LOGO_CP_COLOR1, _LOGO_CP_COLOR4, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 17
		{_LOGO_CP_COLOR2, _LOGO_CP_COLOR3, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}, // 18
		{_LOGO_CP_COLOR3, _LOGO_CP_COLOR2, _LOGO_CP_COLOR1, _LOGO_CP_COLOR1}  // 19 -repeat ended
};

void OsdDispShowLogoColor(void)
{
	BYTE u8_IDX;
	BYTE u8_Temp;
	WORD u16_COUNT;

	//	ScalerTimerDelayXms(500);		// 500 ms Delay

	u16_COUNT = 0;
	do
	{
		u8_Temp = u8_Table[u8_IDX][0];
		ScalerOsdSetColorPalette(7, u8_Palette[u8_Temp][0], u8_Palette[u8_Temp][1], u8_Palette[u8_Temp][2]);
		u8_Temp = u8_Table[u8_IDX][1];
		ScalerOsdSetColorPalette(8, u8_Palette[u8_Temp][0], u8_Palette[u8_Temp][1], u8_Palette[u8_Temp][2]);
		u8_Temp = u8_Table[u8_IDX][2];
		ScalerOsdSetColorPalette(9, u8_Palette[u8_Temp][0], u8_Palette[u8_Temp][1], u8_Palette[u8_Temp][2]);
		u8_Temp = u8_Table[u8_IDX][3];
		ScalerOsdSetColorPalette(10, u8_Palette[u8_Temp][0], u8_Palette[u8_Temp][1], u8_Palette[u8_Temp][2]);
		ScalerTimerDelayXms(95); // 95ms Delay

		if (++u8_IDX > 19)
			u8_IDX = 2;

		if (++u16_COUNT > 450) // 45 sec
			break;
	} while (1);

	OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(28), tiOSD_REALTEK_1BIT_LOGO2, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(56), tiOSD_REALTEK_1BIT_LOGO3, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
	OsdFontPut1BitTable(ROW(0), COL(84), tiOSD_REALTEK_1BIT_LOGO4, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));

	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
}
#endif

void COsdShowPageText(BYTE PageNo)
{
	CLR_KEYREPEATENABLE();
	switch (PageNo)
	{
	case _MENU_PICTURE:

		// Picture
		// ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		// ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		// ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		// if(GET_OSD_COLOR_EFFECT()==_PICTURE_RTS)
		//			if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_RTS)
		{
#if (_ENABLE_MENU_OLED == _ON)
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_BACKLIGHT, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#else
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_BACKLIGHT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#endif
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_BRIGHTNESS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_CONTRAST, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SHARPNESS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_HUE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SATURATION, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#if (_ENABLE_MENU_OLED == _ON)
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OLED_SETTINGS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#endif
			//				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_ECO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		}
		// Eric_020180307 : Delete
		//     			else
		//     			{
		//     				OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_BACKLIGHT, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		//     				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_CONTRAST, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		//     				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_ECO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		//     			}

		// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_MAINSR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutStringCenter( ROW(4), COL(2),15, _PFONT_PAGE_2, _STRING_COLOR, COLOR(_CP_GRAY, _CP_BG) , GET_OSD_LANGUAGE());

		//			 OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST());
		// OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_DCR, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
		// OsdPropPutOptionString(ROW(_OSD_NUMBER_1_ROW),COL(_OSD_NUMBER_6_COL), _PFONT_PAGE_1,_STRING_OFF,COLOR(_CP_BLUE, _CP_BG), _ENGLISH); //�趨��	DCRON/OFF

		break;
#if (_ENABLE_MENU_OLED == _ON)
	case _MENU_PICTURE_OLED_SETTINGS:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OLED_OFFRS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OLED_JB, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;
#endif
	case _MENU_COLOR:

		// Color
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
#if (_HDR10_SUPPORT == _ON)
		if (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF)
		{
			if (GET_COLOR_TEMP_TYPE() == _CT_USER)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_RED, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_GREEN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_BLUE, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_RED, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_GREEN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_BLUE, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLORTEMP, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#if (_HDR10_SUPPORT == _ON)
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_HDR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_EFFECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_GAMMA, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#else
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_EFFECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_GAMMA, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#endif
		}
		else
#endif
		{
			if (GET_COLOR_TEMP_TYPE() == _CT_USER)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_RED, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_GREEN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_BLUE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_RED, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_GREEN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_BLUE, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLORTEMP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#if (_HDR10_SUPPORT == _ON)
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_HDR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_EFFECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_GAMMA, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#else
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_EFFECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_GAMMA, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#endif
		}
		break;

	case _MENU_OSDSETTINGS:
		// OSDSETTINGS
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OSDSET_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		//  OsdPropPutOptionString(ROW(_OSD_NUMBER_1_ROW),COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_1,_STRING_Language_TABLE1,COLOR(_CP_LIGHTBLUE, _CP_BG), GET_OSD_LANGUAGE()); //��ȷ��	 LANGUAGE

		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OSDSET_HORIZONTAL, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		//  OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());//

		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OSDSET_VERTICAL, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		//  OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());//

		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OSDSET_TRANSPARENCY, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		//	OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());//

		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OSDSET_OSDTIMEOUT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		//  OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());//

		OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OSDSET_ROTATE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		//  OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());//
		break;

	case _MENU_SETUP:
		// SETUP
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SETUP_INPUT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SETUP_AUDIOMUTE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SETUP_AUDIO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SETUP_RESET, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_DP_FORMAT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// if (GET_OSD_DP_MST() != _MST_OFF)
		// {
		// 	OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_DP_MST, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 	OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_CLONE, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// }
		// else if (GET_OSD_CLONE_MODE() != _OSD_CLONE_OFF)
		// {
		// 	OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_DP_MST, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 	OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_CLONE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// }
		// else
		// {
		// 	OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_DP_MST, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 	OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_CLONE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// }

		// OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SETUP_RESET, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;

	case _MENU_OTHER:
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_DISPLAY_SIZE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_DISPLAY_ROTATE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_LOW_BLUE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_OVER_DRIVE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		break;
		// #if (_ENABLE_VIDEO_WALL == _ON)
		// 			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_VIDEO_WALL_SETTINGS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// #else
		// 			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_VIDEO_WALL_SETTINGS, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// #endif
		// #if (_ENABLE_LIGHT_SENSOR == _ON)
		// 			if (SuccessInitilizeLightSensor())
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_LIGHT_SENSOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 			}
		// 			else
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_LIGHT_SENSOR, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 			}
		// #else
		// 			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_LIGHT_SENSOR, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// #endif
		// #if (_ENABLE_FAN_CONTROL == _ON)
		// 			if (SuccessInitializeFanControl())
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_CONTROLS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 			}
		// 			else
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_CONTROLS, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 			}
		// #else
		// 			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_CONTROLS, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// #endif
		// #if(_ENABLE_SELF_CHECK == _ON)
		// 			if (SuccessInitialize_TCS34725())
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SELF_CHECK, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 			}
		// 			else
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SELF_CHECK, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 			}
		// #else
		// 			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SELF_CHECK, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// #endif
		// //#if(_AUO_PANEL_ALCW_SUPPORT == _ON)
		// //			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_ALCW_SETTING, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// //#else
		// //			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_ALCW_SETTING, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// //#endif

		// #if(_FREESYNC_SUPPORT==_ON)

		// 			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FREESYNC, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// #endif
		// 			break;
		// #if (_ENABLE_VIDEO_WALL == _ON)
		// 		case _MENU_OTHERS_VIDEO_WALL_SETTINGS:
		// 			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_VIDEO_WALL, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_DISPLAY_NUMBER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_HORIZONTAL_NUMBER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_VERTICAL_NUMBER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_RS232_ID, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 		  break;
		// #endif
		// #if (_ENABLE_FAN_CONTROL == _ON)
		// 		case _MENU_OTHERS_FAN_CONTROLS:
		// 			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		// 			if (SuccessInitializeFanControl())
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 				if (GET_OSD_FAN_STATUS() == _ON)
		// 				{
		// 					OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 					OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 					OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 					OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM4, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 				}
		// 				else
		// 				{
		// 					OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM1, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 					OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 					OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 					OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				}
		// 				OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		// 				if (GET_OSD_SHUTDOWN_STATUS() == _ON)
		// 				{
		// 					OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// 				}
		// 				else
		// 				{
		// 					OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				}
		// 			}
		// 			else
		// 			{
		// 				OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM1, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		// 				OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());

		// 			}
		// 			break;
		// #endif

	case _MENU_SERVICE:
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SERVICE_PWM_RES, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SERVICE_CONTROL, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#if (_PIXEL_SHIFT_SUPPORT == _ON)
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SERVICE_PIXEL_SHIFT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SERVICE_PIXEL_SHIFT_TIME, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#endif
		// OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SERVICE_INVERT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_SERVICE_FREQ, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		break;

	default:
		break;
	}
}

void COsdShowChoosePictureText(BYTE number)
{
	CLR_KEYREPEATENABLE();
	/*		_Countstar=0,
			_LANGUAGE,
			_HORIZONTAL,
			_VERTICAL,
			_TRANSPARENCY,
			_OSDTIMEOUT,
			_FONT_AMOUNT,
	*/

	switch (number)
	{
	case _STRING_BACKLIGHT:
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
			OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;
	case _STRING_BRIGHTNESS:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_1, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_1 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;
	case _STRING_CONTRAST:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_2, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_2 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;
	case _STRING_SHARPNESS:
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), GET_OSD_SHARPNESS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_3 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_3, _UNSELECT);

		break;
	case _STRING_HUE:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_HUE(), _HUE_MAX, _HUE_MIN, _HUE_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_4, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_4 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;
	case _STRING_SATURATION:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SATURATION(), _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_5, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_5 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;
#if (_ENABLE_MENU_OLED == _ON)
	case _STRING_OLED_SETTINGS:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OLED_OFFRS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OLED_JB, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;
	case _STRING_OLED_OFFRS:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_OLED_OFFRS_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
	case _STRING_OLED_JB:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_OLED_JB_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
#endif

	default:
		break;
	}
}

void COsdShowChooseColorText(BYTE number)
{
	CLR_KEYREPEATENABLE();
	/*		_Countstar=0,
			_LANGUAGE,
			_HORIZONTAL,
			_VERTICAL,
			_TRANSPARENCY,
			_OSDTIMEOUT,
			_FONT_AMOUNT,
	*/

	switch (number)
	{
	case _STRING_COLORTEMP:
		// if(GET_COLOR_TEMP_TYPE()==_CT_6500)
		//{
		//	OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);

		//}
		// else if(GET_COLOR_TEMP_TYPE()==_CT_9300)
		//{
		//	OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);

		//}
		// else if(GET_COLOR_TEMP_TYPE()==_CT_USER)
		//{
		//	OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);

		//}
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW + (3 * GET_COLOR_TEMP_TYPE())), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_9300K, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_7500K, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_6500K, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_5800K, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_SRGB, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_USER_DEFINE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;

	case _STRING_COLOR_RED:
		// g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		// g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);

		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_6, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_6 + 3, _OSD_NUMBER_UNSELECT_COLOR);

		break;

	case _STRING_COLOR_GREEN:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_7, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_7 + 3, _OSD_NUMBER_UNSELECT_COLOR);

		break;

	case _STRING_COLOR_BLUE:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_8, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_8 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;

#if (_HDR10_SUPPORT == _ON)
	case _STRING_HDR:

		if (GET_OSD_HDR_MODE() == _HDR10_MODE_OFF)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		// else if(GET_OSD_HDR_MODE()==_HDR10_MODE_FORCE_2084)
		//{
		//	OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);

		//}
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_AUTO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_SMPTE2084, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;
#endif
	case _STRING_COLOR_EFFECT:
		if (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_STANDARD)
		{
			// OsdFontPut1ChooseIcon(_OSD_NUMBER_1_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_WHITE, _CP_BLUE_65);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_GAME)
		{
			// OsdFontPut1ChooseIcon(_OSD_NUMBER_2_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_WHITE, _CP_BLUE_65);
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_MOVIE)
		{
			// OsdFontPut1ChooseIcon(_OSD_NUMBER_3_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_WHITE, _CP_BLUE_65);
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_PHOTO)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_VIVID)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		// else if (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_USER)
		//{
		//	//OsdFontPut1ChooseIcon(_OSD_NUMBER_11_ROW, _OSD_NUMBER_11_COL, _CHOOSE_ICON,_CP_WHITE, _CP_BLUE_65);
		//	OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		// }

		// Eric_020180307 : Delete
		//     					else if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_FPS)
		//     					{
		//     						//OsdFontPut1ChooseIcon(_OSD_NUMBER_12_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_WHITE, _CP_BLUE_65);
		//     						OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		//     					}
		//     					else if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_RTS)
		//     					{
		//     						//OsdFontPut1ChooseIcon(_OSD_NUMBER_13_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_WHITE, _CP_BLUE_65);
		//     						OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		//     					}
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_STANDARD, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_GAME, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_MOVIE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_PHOTO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_VIVID, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_PICTURE_FPS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_PICTURE_RTS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_COLOR_USER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;
	case _STRING_GAMMA:
		if (GET_OSD_GAMMA() == _GAMMA_OFF)
		{
			// OsdFontPut1ChooseIcon(_OSD_NUMBER_1_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_WHITE, _CP_BLUE_65);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_GAMMA() == _GAMMA_18)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_GAMMA() == _GAMMA_20)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_GAMMA() == _GAMMA_22)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_GAMMA() == _GAMMA_24)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
#if (_TECNINT_DICOM)
		else if (GET_OSD_GAMMA() == _GAMMA_RC2)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
		else if (GET_OSD_GAMMA() == _GAMMA_RC3)
		{
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		}
#endif
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_GAMMA_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_GAMMA_18, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_GAMMA_20, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_GAMMA_22, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_GAMMA_24, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#if (_TECNINT_DICOM)
		OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_GAMMA_RC2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_GAMMA_RC3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#endif
		break;

	default:
		break;
	}
}

void COsdShowChooseOSDSetText(BYTE number)
{
	CLR_KEYREPEATENABLE();
	/*		_Countstar=0,
			_LANGUAGE,
			_HORIZONTAL,
			_VERTICAL,
			_TRANSPARENCY,
			_OSDTIMEOUT,
			_FONT_AMOUNT,
	*/

	switch (number)
	{
	case _STRING_OSDSET_LANGUAGE:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
#if (_ENABLE_MENU_OLED == _ON)
		if (GET_OSD_LANGUAGE() == _ENGLISH)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _CHINESE_T)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _ESPANA)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _FRENCH)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _GERMAN)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL - 1), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _ITALIANO)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _RUSSIAN)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		// else if(GET_OSD_LANGUAGE()==_KOREAN)
		//{
		//	ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL+9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		// }

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _ESPANA);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _FRENCH);
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _GERMAN);
		OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _ITALIANO);
		OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _RUSSIAN);
		// OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _KOREAN);

#else
		if (GET_OSD_LANGUAGE() == _ENGLISH)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _ESPANA)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _FRENCH)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _GERMAN)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL - 1), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _ITALIANO)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL + 9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _NEDERLAND)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else if (GET_OSD_LANGUAGE() == _RUSSIAN)
		{
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		// else if(GET_OSD_LANGUAGE()==_KOREAN)
		//{
		//	ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL+9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		// }
		// else if(GET_OSD_LANGUAGE()==_CHINESE_T)
		//{
		//	ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW),  COL(_OSD_NUMBER_2_COL+9), WIDTH(4), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		// }
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _ESPANA);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _FRENCH);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _GERMAN);
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _ITALIANO);
		OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _NEDERLAND);
		OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _RUSSIAN);
		// OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _KOREAN);
		// OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _CHOOSE_LANGUAGE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
#endif

		break;

	case _STRING_OSDSET_HORIZONTAL:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_HPOS(), _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_2, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;

	case _STRING_OSDSET_VERTICAL:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VPOS(), _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_3, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;

	case _STRING_OSDSET_TRANSPARENCY:

		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_TRANSPARENCY_STATUS(), _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_4, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;

	case _STRING_OSDSET_OSDTIMEOUT:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_TIME_OUT(), _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_5, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		break;

	case _STRING_OSDSET_ROTATE:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_0_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_90_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_270_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_180_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ROTATE_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ROTATE_STATUS())), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_WHITE, _CP_BG), _CHINESE_T);
		break;
	default:
		break;
	}
}

void COsdShowChooseSetupText(BYTE number)
{
	CLR_KEYREPEATENABLE();

	switch (number)
	{
	case _STRING_SETUP_INPUT:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
		{
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_INPUT_PORT_OSD_ITEM())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else
		{
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * (GET_OSD_INPUT_PORT_OSD_ITEM()))), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		break;
	case _STRING_SETUP_AUDIOMUTE:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_VOLUME_MUTE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;

	case _STRING_SETUP_AUDIO:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), GET_OSD_VOLUME(), _SLIDER_3, _UNSELECT);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_3, _OSD_NUMBER_UNSELECT_COLOR);
		break;

	case _STRING_DP_FORMAT:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_DP_D0_VERSION())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_DP1_1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_DP1_2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;
	case _STRING_DP_MST:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_DP_MST())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_DP1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_DP2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;
	case _STRING_CLONE:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_CLONE_MODE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;
	default:
		break;
	}
}

void COsdShowChooseOtherText(BYTE number)
{
	CLR_KEYREPEATENABLE();
	/*		_Countstar=0,
			_LANGUAGE,
			_HORIZONTAL,
			_VERTICAL,
			_TRANSPARENCY,
			_OSDTIMEOUT,
			_FONT_AMOUNT,
	*/

	switch (number)
	{
	case _STRING_OTHER_DISPLAY_SIZE:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FULLSCREEN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_AUTO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_4_3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_5_4, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_1_1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ASPECT_RATIO_TYPE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;

	// case _STRING_OTHER_LOW_BLUE :
	//	OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
	//	OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
	//	OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
	//	OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
	//	OsdPropPutString(ROW(_OSD_NUMBER_5_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

	//	OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	//	OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_WEAK, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	//	OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_MEDIAN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	//	OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_STRONG, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	//	OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_STRONGEST, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3* GET_OSD_LOWBLUELIGHT_STATUS())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
	//	OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
	//	OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
	//	break;
	case _STRING_OTHER_DISPLAY_ROTATE:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_0_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_90_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_180_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_270_DEGREE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_DISP_ROTATE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);

		break;
	case _STRING_OTHER_OVER_DRIVE:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_OD_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;

	case _STRING_OTHER_FREESYNC:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_FREE_SYNC_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;

#if (_ENABLE_VIDEO_WALL == _ON)
	case _STRING_OTHER_VIDEO_WALL_SETTINGS:
		// OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		// OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_VIDEO_WALL, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_DISPLAY_NUMBER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_HORIZONTAL_NUMBER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_VERTICAL_NUMBER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_RS232_ID, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;

	case _STRING_OTHER_VIDEO_WALL:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_VIDEO_WALL_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
	case _STRING_OTHER_DISPLAY_NUMBER:
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), GET_OSD_VIDEO_WALL_DISP_NUM(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_DISP_NUM(), GetVideoWallDisplayNumber(), _VIDEO_WALL_DISP_NUM_MIN, _VIDEO_WALL_DISP_NUM_CENTER());
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
		break;
	case _STRING_OTHER_HORIZONTAL_NUMBER:
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), GET_OSD_VIDEO_WALL_H_NUM(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_1 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_H_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _VIDEO_WALL_HV_NUM_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_1, _UNSELECT);
		break;
	case _STRING_OTHER_VERTICAL_NUMBER:
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), GET_OSD_VIDEO_WALL_V_NUM(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_2 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_V_NUM(), _VIDEO_WALL_HV_NUM_MAX, _VIDEO_WALL_HV_NUM_MIN, _VIDEO_WALL_HV_NUM_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_2, _UNSELECT);
		break;
	case _STRING_OTHER_RS232_ID:
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), GET_OSD_VIDEO_WALL_RS232ID(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_3 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VIDEO_WALL_RS232ID(), GetVideoWallDisplayNumber(), _VIDEO_WALL_RS232ID_MIN, _VIDEO_WALL_RS232ID_CENTER());
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_3, _UNSELECT);
		break;
#endif
#if (_ENABLE_LIGHT_SENSOR == _ON)
	case _STRING_LIGHT_SENSOR:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		if (SuccessInitilizeLightSensor())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_LIGHT_SENSOR_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_LIGHT_SENSOR_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		}
		break;
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
	case _STRING_OTHER_FAN_CONTROLS:
		if (SuccessInitializeFanControl())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM4, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_SHUTDOWN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM1, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_FAN_PWM4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_SHUTDOWN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		}
		break;
	case _STRING_OTHER_FAN_CONTROLS2:
		if (SuccessInitializeFanControl())
		{
			if (GET_OSD_FAN_STATUS() == _ON)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM4, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM1, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			if (GET_OSD_SHUTDOWN_STATUS() == _ON)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}

			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_TEMP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM1, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_PWM4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SHUTDOWN_TEMP, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_TEMP, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		}
		break;

	case _STRING_OTHER_FAN:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		if (SuccessInitializeFanControl())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_AUTO, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_FAN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_AUTO, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_FAN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		}
		break;
	case _STRING_OTHER_FAN_PWM1:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM1(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
		break;
	case _STRING_OTHER_FAN_PWM2:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM2(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_1 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
		break;
	case _STRING_OTHER_FAN_PWM3:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM3(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_2 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
		break;
	case _STRING_OTHER_FAN_PWM4:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM4(), _FAN_PWM_MAX, _FAN_PWM_MIN, _FAN_PWM_CENTER);
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_3 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
		break;
	case _STRING_OTHER_SHUTDOWN:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		if (SuccessInitializeFanControl())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SHUTDOWN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SHUTDOWN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		}
		break;
	case _STRING_OTHER_SHUTDOWN_TEMP:
		OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET), GET_OSD_SHUTDOWN_TEMP(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_FAN_PWM4(), _SHUTDOWN_TEMP_MAX, _SHUTDOWN_TEMP_MIN, _SHUTDOWN_TEMP_CENTER);
		OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
		break;
	case _STRING_OTHER_TEMP:
#if (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
		if (SuccessInitializeFanControl())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp1(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			if (GetTempCount() >= 2)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropShowNumberTemp(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp2(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			if (GetTempCount() >= 3)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropShowNumberTemp(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp3(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			if (GetTempCount() >= 3)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP4, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropShowNumberTemp(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp4(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			if (GetTempCount() >= 3)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP5, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropShowNumberTemp(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp5(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP5, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP1, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp1(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp2(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp3(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp4(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP5, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_ADT7470Temp5(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
		}
#elif (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
		if (SuccessInitializeFanControl())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp1(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			if (MAX31785TempSensor[1].tempState)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropShowNumberTemp(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp2(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			if (MAX31785TempSensor[2].tempState)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropShowNumberTemp(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp3(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
			if (MAX31785TempSensor[3].tempState)
			{
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP4, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
				OsdPropShowNumberTemp(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp4(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			}
			else
			{
				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			}
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP1, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp1(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP2, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp2(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp3(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OTHER_TEMP4, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropShowNumberTemp(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL + 8), Get_MAX31785Temp4(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_2, _OSD_NUMBER_UNSELECT_COLOR);
		}
#endif
		break;

#endif

#if (_ENABLE_SELF_CHECK == _ON)
	case _STRING_OTHER_SELF_CHECK:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		if (SuccessInitialize_TCS34725())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SELF_CHECK_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SELF_CHECK_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		}
		break;
#endif

#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
	case _STRING_OTHER_ALCW_SETTING:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ALCW())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
#endif

	case _STRING_OTHER_MENU:
		ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_DISPLAY_ROTATE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_OVER_DRIVE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

#if (_ENABLE_VIDEO_WALL == _ON)
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_VIDEO_WALL_SETTINGS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#else
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_VIDEO_WALL_SETTINGS, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#endif
#if (_ENABLE_LIGHT_SENSOR == _ON)
		if (SuccessInitilizeLightSensor())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_LIGHT_SENSOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_LIGHT_SENSOR, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		}
#else
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_LIGHT_SENSOR, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#endif
#if (_ENABLE_FAN_CONTROL == _ON)
		if (SuccessInitializeFanControl())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_CONTROLS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_CONTROLS, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		}
#else
		OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_CONTROLS, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#endif
#if (_ENABLE_SELF_CHECK == _ON)
		if (SuccessInitialize_TCS34725())
		{
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SELF_CHECK, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		}
		else
		{
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SELF_CHECK, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		}
#else
		OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SELF_CHECK, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#endif
#if(_AUO_PANEL_ALCW_SUPPORT == _ON)
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_ALCW_SETTING, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#else 
			OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_ALCW_SETTING, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
#endif 
#if (_FREESYNC_SUPPORT == _ON)

		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FREESYNC, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#endif
		break;
	default:
		break;
	}
}

void COsdShowChooseServiceText(BYTE number)
{
	CLR_KEYREPEATENABLE();
	/*		_Countstar=0,
			_LANGUAGE,
			_HORIZONTAL,
			_VERTICAL,
			_TRANSPARENCY,
			_OSDTIMEOUT,
			_FONT_AMOUNT,
	*/

	switch (number)
	{
	case _STRING_SERVICE_PWM_RES:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SERVICE_255, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SERVICE_4095, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_BACKLIGHT_PWM_RES())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
	case _STRING_SERVICE_CONTROL:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SERVICE_LINEAR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SERVICE_CURVE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_BACKLIGHT_CONTROL())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
#if (_PIXEL_SHIFT_SUPPORT == _ON)
	case _STRING_SERVICE_PIXEL_SHIFT:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_PIXEL_SHIFT_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
	case _STRING_SERVICE_PIXEL_SHIFT_TIME:
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_5MIN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_10MIN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_15MIN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_20MIN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_PIXEL_SHIFT_TIME())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		break;
#endif
	// case _STRING_SERVICE_INVERT:
	//	OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
	//	OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

	//	OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_OFF, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	//	OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_ON, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_BACKLIGHT_INVERT())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
	//	break;
	// case _STRING_SERVICE_FREQ:
	//	OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW - 2), COL(_OSD_NUMBER_10_COL + _OSD_SLIDE_VALUE_OFFSET - 4), GET_OSD_BACKLIGHT_FREQ(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _SLIDER_0 + 3, _OSD_NUMBER_UNSELECT_COLOR);
	//	g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT_FREQ(), _BACKLIGHT_FREQ_MAX, _BACKLIGHT_FREQ_MIN, _BACKLIGHT_FREQ_CENTER);
	//	OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
	//	break;
	default:
		break;
	}
}
#if 0
void COsdShowChooseLeftMenuText(BYTE number)
{
			CLR_KEYREPEATENABLE();
	/*		_Countstar=0,
			_LANGUAGE,
			_HORIZONTAL,
			_VERTICAL,
			_TRANSPARENCY,
			_OSDTIMEOUT,
			_FONT_AMOUNT,
	*/
		
			switch(number)
			{
				case _STRING_LEFT_MENU_AIM:
					OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE_H, _CP_WHITE);
					//OsdFontPut1FuncTableForm(8, 6, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);
					OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
					
					OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE_H, _CP_BG);
					OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	
					
					OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE_H, _CP_BG);	
					OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	
					
					OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE_H, _CP_BG);	
					OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);  
	
					break;
	
	
		
				case _STRING_LEFT_MENU_TIMER :
					OsdFontPut1FuncAimTableForm(7,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,1);	
					OsdFontPut1NumberTableForm(8, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,10);
					OsdFontPut1NumberTableForm(8, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);	
					OsdFontPut1NumberTableForm(8, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					
					OsdFontPut1FuncAimTableForm(7,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,2); 	
					OsdFontPut1NumberTableForm(8, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,10);
					OsdFontPut1NumberTableForm(8, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);	
					OsdFontPut1NumberTableForm(8, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);

					OsdFontPut1FuncAimTableForm(7,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,3); 	
					OsdFontPut1NumberTableForm(8, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,10);
					OsdFontPut1NumberTableForm(8, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);	
					OsdFontPut1NumberTableForm(8, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);

					OsdFontPut1FuncAimTableForm(7,8+53, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 8+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,4); 	
					OsdFontPut1NumberTableForm(8, 10+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(8, 12+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,10);
					OsdFontPut1NumberTableForm(8, 14+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);	
					OsdFontPut1NumberTableForm(8, 16+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);

					OsdFontPut1FuncAimTableForm(13,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(14, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,5); 	
					OsdFontPut1NumberTableForm(14, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(14, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,10);
					OsdFontPut1NumberTableForm(14, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);	
					OsdFontPut1NumberTableForm(14, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);

					OsdFontPut1FuncAimTableForm(13,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(14, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,6); 	
					OsdFontPut1NumberTableForm(14, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(14, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,10);
					OsdFontPut1NumberTableForm(14, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);	
					OsdFontPut1NumberTableForm(14, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);

					OsdFontPut1FuncAimTableForm(13,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(14, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,9); 	
					OsdFontPut1NumberTableForm(14, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
					OsdFontPut1NumberTableForm(14, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,10);
					OsdFontPut1NumberTableForm(14, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);	
					OsdFontPut1NumberTableForm(14, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_WHITE,_CP_BLUE_65,0);
	
					break;
	
				default:
					 break;
			}
}
#endif

void COsdShowPageInputString(BYTE InputOsd, BYTE InputType, BYTE NUM, BYTE MAINOSDINF)
{
	BYTE NUMchar, NUMinput, cnt, DVISUM, HDMISUM, DPSUM;
	NUMchar = 0;
	NUMinput = 0;
	cnt = 0;
	DVISUM = 0;
	HDMISUM = 0;
	DPSUM = 0;

	MAINOSDINF = MAINOSDINF;

#if (_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
	DVISUM++;
#endif
#if ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
	HDMISUM++;
#endif
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
	DPSUM++;
#endif

#if (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
	DVISUM++;
#endif
#if ((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
	HDMISUM++;
#endif
#if (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
	DPSUM++;
#endif

#if ((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
	DVISUM++;
#endif
#if ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
	HDMISUM++;
#endif
#if (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
	DPSUM++;
#endif

#if ((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
	DVISUM++;
#endif
#if ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
	HDMISUM++;
#endif

#if ((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
	DVISUM++;
#endif
#if ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
	HDMISUM++;
#endif

#if (_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
	DVISUM++;
#endif
#if ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
	HDMISUM++;
#endif

#if (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
	DPSUM++;
#endif

	switch (NUM)
	{
	case 2:
		NUMchar = _2_;
		break;
	case 3:
		NUMchar = _3_;
		break;
	case 4:
		NUMchar = _4_;
		break;
	case 5:
		NUMchar = _5_;
		break;
	case 6:
		NUMchar = _6_;
		break;
	default:
		break;
	}

#if (_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
	switch (InputOsd)
	{
		/*
		case 0:
			NUMinput=_0_;
			break;
		case 1:
			NUMinput=_1_;
			break;
			*/

	case 2:
		NUMinput = _0_;
		break;
	case 3:
		NUMinput = _1_;
		break;
	case 4:
		NUMinput = _2_;
		break;
	case 5:
		NUMinput = _3_;
		break;
	case 6:
		NUMinput = _4_;
		break;
	case 7:
		NUMinput = _5_;
		break;
	case 8:
		NUMinput = _6_;
		break;
	default:
		break;
	}
#else
	switch (InputOsd)
	{
	/*
	case 0:
		NUMinput=_0_;
		break;
			*/
	case 1:
		NUMinput = _0_;
		break;
	case 2:
		NUMinput = _1_;
		break;
	case 3:
		NUMinput = _2_;
		break;
	case 4:
		NUMinput = _3_;
		break;
	case 5:
		NUMinput = _4_;
		break;
	case 6:
		NUMinput = _5_;
		break;
	case 7:
		NUMinput = _6_;
		break;
	default:
		break;
	}
#endif
	/*
		if(InputType == _A0_PORT)
		{
			g_pucModeInfoData[cnt++] = _A_;
			g_pucModeInfoData[cnt++] = _0_;
		}
		else
		{
			g_pucModeInfoData[cnt++] = _D_;
			g_pucModeInfoData[cnt++] = NUMinput;
		}
		if(MAINOSDINF==0)
		{
		   g_pucModeInfoData[cnt++] =0;
		g_pucModeInfoData[cnt++] =0;
		}
		g_pucModeInfoData[cnt++] =0;

	*/

	switch (InputType)
	{
	case _INPUT_OSD_VGA:
		//  g_pucModeInfoData[cnt++] = ___;
		g_pucModeInfoData[cnt++] = _V_;
		g_pucModeInfoData[cnt++] = _G_;
		g_pucModeInfoData[cnt++] = _A_;
		// g_pucModeInfoData[cnt++] = ___;
		g_pucModeInfoData[cnt++] = _END_;
		break;

	case _INPUT_OSD_DVI:
		//   g_pucModeInfoData[cnt++] = ___;
		g_pucModeInfoData[cnt++] = _D_;
		g_pucModeInfoData[cnt++] = _V_;
		g_pucModeInfoData[cnt++] = _I_;
		if (NUM >= 2)
		{
			g_pucModeInfoData[cnt++] = NUMchar;
		}
		else
		{
			if (DVISUM >= 2)
			{
				g_pucModeInfoData[cnt++] = _1_;
			}
			else
			{
				// g_pucModeInfoData[cnt++] = ___;
			}
		}
		g_pucModeInfoData[cnt++] = _END_;
		break;

	case _INPUT_OSD_HDMI:
		g_pucModeInfoData[cnt++] = _H_;
		g_pucModeInfoData[cnt++] = _D_;
		g_pucModeInfoData[cnt++] = _M_;
		g_pucModeInfoData[cnt++] = _I_;
		if (NUM >= 2)
		{
			g_pucModeInfoData[cnt++] = NUMchar;
		}
		else
		{
			if (HDMISUM >= 2)
			{
				g_pucModeInfoData[cnt++] = _1_;
			}
			else
			{
				// g_pucModeInfoData[cnt++] = ___;
			}
		}
		g_pucModeInfoData[cnt++] = _END_;
		break;

	case _INPUT_OSD_DP:
		if (DPSUM < 2)
		{
			g_pucModeInfoData[cnt++] = ___;
		}
		g_pucModeInfoData[cnt++] = ___;
		g_pucModeInfoData[cnt++] = ___;
		g_pucModeInfoData[cnt++] = _D_;
		g_pucModeInfoData[cnt++] = _P_;
		if (NUM >= 2)
		{
			g_pucModeInfoData[cnt++] = NUMchar;
		}
		else
		{
			if (DPSUM >= 2)
			{
				g_pucModeInfoData[cnt++] = _1_;
			}
			else
			{
				// g_pucModeInfoData[cnt++] = ___;
			}
		}
		g_pucModeInfoData[cnt++] = _END_;
		break;

	default:
		break;
	}
}

void COsdShowPageInputTextSelect(BYTE InputOsd, BYTE InputType, BYTE NUM)
{
	BYTE ucrow, uccol;
	if (GET_OSD_STATE() == _MENU_HOT_INPUT_ADJUST)
	{
		ucrow = 2;
		//  g_usItemNum=InputType;
		uccol = 4 + (11 * InputOsd);

		COsdShowPageInputString(InputOsd, InputType, NUM, 0);

		OsdPropPutString(ROW(ucrow), COL(uccol), _PFONT_PAGE_2, _STRING_INPUT_SELECT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	}
	else
	{
		uccol = _OSD_NUMBER_2_COL;
		//  g_usItemNum=InputType;

		switch (InputOsd)
		{
		case 0:
			ucrow = _OSD_NUMBER_1_ROW;
			break;

		case 1:
			ucrow = _OSD_NUMBER_2_ROW;

			break;
		case 2:
			ucrow = _OSD_NUMBER_3_ROW;

			break;
		case 3:
			ucrow = _OSD_NUMBER_4_ROW;

			break;
		case 4:
			ucrow = _OSD_NUMBER_11_ROW;

			break;

		default:
			break;
		}
		COsdShowPageInputString(InputOsd, InputType, NUM, 0);

		OsdPropPutString(ROW(ucrow), COL(uccol), _PFONT_PAGE_2, _STRING_INPUT_SELECT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	}
}

void COsdShowPageInputText(void)
{
	OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_AUTO_SELECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SETUP_VGA, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SETUP_DP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SETUP_HDMI, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_SETUP_DVI, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	// 	BYTE  DVInum,HDMInum,DPnum;
	// 	    DVInum=0;
	// 	    HDMInum=0;
	// 	    DPnum=0;
	// 	    if(GET_OSD_STATE() == _MENU_HOT_INPUT_ADJUST)
	// 	    {
	// 	      OsdPropPutString(ROW(2), COL(4), _PFONT_PAGE_2, _STRING_AUTO_SELECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	// 	    }
	// 	    else
	// 	    {
	// 	      OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), _PFONT_PAGE_2, _STRING_AUTO_SELECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	// 	    }
	// #if((_A0_INPUT_PORT_TYPE !=_A0_NO_PORT) )
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_A0,_INPUT_OSD_VGA,0);
	// 	 #endif

	// #if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT))
	// 	DVInum++;
	// 	COsdShowPageInputTextSelect(_OSD_INPUT_D0,_INPUT_OSD_DVI,DVInum);
	// #endif
	// #if(((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)||(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)))
	// 	HDMInum++;
	// 	COsdShowPageInputTextSelect(_OSD_INPUT_D0,_INPUT_OSD_HDMI,HDMInum);
	// #endif
	// #if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
	// 	DPnum++;
	// 	COsdShowPageInputTextSelect(_OSD_INPUT_D0 - _OSD_INPUT_A0,_INPUT_OSD_DP,DPnum);
	// #endif

	// #if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
	// 	DVInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D1,_INPUT_OSD_DVI,DVInum);
	// #endif
	// #if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)||(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
	// 	HDMInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D1,_INPUT_OSD_HDMI,HDMInum);
	// #endif
	// #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
	// 	DPnum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D1 - _OSD_INPUT_A0,_INPUT_OSD_DP,DPnum);
	// #endif

	// #if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT)||(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
	// 	  DVInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D2,_INPUT_OSD_DVI,DVInum);
	// #endif
	// #if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)||(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
	// 	HDMInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D2 - _OSD_INPUT_A0,_INPUT_OSD_HDMI,HDMInum);
	// #endif
	// #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
	// 	DPnum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D2,_INPUT_OSD_DP,DPnum);
	// #endif

	// #if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT)||(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
	// 	  DVInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D3,_INPUT_OSD_DVI,DVInum);
	// #endif
	// #if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)||(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
	// 	 HDMInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D3 - _OSD_INPUT_A0,_INPUT_OSD_HDMI,HDMInum);
	// #endif

	// #if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT)||(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
	// 	  DVInum++;
	// 	COsdShowPageInputTextSelect(_OSD_INPUT_D4,_INPUT_OSD_DVI,DVInum);
	// #endif
	// #if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)||(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
	// 	 HDMInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D4,_INPUT_OSD_HDMI,HDMInum);
	// #endif

	// #if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
	// 	  DVInum++;
	// 	COsdShowPageInputTextSelect(_OSD_INPUT_D5,_INPUT_OSD_DVI,DVInum);
	// #endif
	// #if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)||(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
	// 	 HDMInum++;
	// 	 COsdShowPageInputTextSelect(_OSD_INPUT_D5,_INPUT_OSD_HDMI,HDMInum);
	// #endif

	// #if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
	// 	DPnum++;
	// 	COsdShowPageInputTextSelect(_OSD_INPUT_D6,_INPUT_OSD_DP,DPnum);
	// #endif
}

void OsdDispHotKeyBacklightMenu(void)
{
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	EnumOsdRotateType tempRotateStatus = GET_OSD_ROTATE_STATUS();
#endif
	OsdDispDisableOsd();

	g_ucFontPointer0 = _OSD_PAGE1_0_START;
	g_ucFontPointer1 = _OSD_PAGE1_1_START;
	g_ucFontPointer2 = _OSD_PAGE1_2_START;

	OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(5), COLOR(_CP_WHITE, _CP_BG));

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(5), _DISABLE, 0, _ENABLE);
#endif

	OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
	OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

	// Adjust Color Palette
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

	// Load Font & Icon
	OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

	OsdFontVLCLoadFont(_FONT1_GLOBAL);

	// Background window Modify
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
	}
	else
#endif
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(7), g_ucOsdHeight, _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(7), WIDTH(g_ucOsdWidth - 7), HEIGHT(g_ucOsdHeight), _CP_LIGHTBLUE);
	}

	OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_BACKLIGHT);
	OsdFontPut1BitBackLightIcon(ROW(1), COL(2), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_ORANGE, _CP_BG);
	// icon
	// OsdDispSliderAndNumber(_MENU_HOTKEY_BACKLIGHT, GET_OSD_BACKLIGHT());

	g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
	OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _SELECT);
	OsdPropShowNumber(ROW(2), COL(31), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SUB_PAGE_ITEM_1, COLOR(_CP_ORANGE, _CP_BG));
	SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
	SET_OSD_STATE(_MENU_HOTKEY_BACKLIGHT);

	ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	switch (tempRotateStatus)
	{
	case _OSD_ROTATE_DEGREE_90:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 5, 50);
		break;
	case _OSD_ROTATE_DEGREE_270:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 95, 50);
		break;
	case _OSD_ROTATE_DEGREE_180:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 5);
		break;
	default:
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);
		break;
	}
	// OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

#else
	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 95);
#endif
	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

	OsdFuncEnableOsd();
}

// Eric_20180306_Delete : Start ---------------------------------
//     //--------------------------------------------------
//     // Description  :
//     // Input Value  :
//     // Output Value :
//     //--------------------------------------------------
//     WORD OsdDispDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
//     {
//         usValue = usValue;
//         usMax = usMax;
//         usMin = usMin;
//         bCycle = bCycle;
//         return 0;
//     }

//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState)
//    {
//        BYTE ucI = 0;
//        BYTE ucRow = 10;
//        BYTE ucCol = 4;
//        BYTE ucColor = 0;
//
//        if(ucState == _OSD_REJECT)
//        {
//            OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));
//            return;
//        }
//
//        for(ucI = 0; ucI < ucAmount; ucI++)
//        {
//            if((ucState == _OSD_SELECT) && (ucI == ucItem))
//            {
//                ucColor = COLOR(_CP_PINK, _CP_BG);
//            }
//            else
//            {
//                ucColor = COLOR(_CP_GRAY, _CP_BG);
//            }
//
//            OsdFontPut1Bit(ucRow, ucCol + ucI, _iINDICATE, ucColor);
//        }
//
//        if(ucAmount < 20)
//        {
//            OsdFuncClearOsd(ucRow, ucCol + ucAmount, WIDTH(20 - ucAmount), HEIGHT(1));
//        }
//    }
//    //--------------------------------------------------
//    // Description :draw Item indication
//    // Input Value :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainMenuItemIndication2(BYTE ucItem, BYTE ucAmount, BYTE ucState)
//    {
//        BYTE ucI = 0;
//        BYTE ucRow = 10;
//        BYTE ucCol = 4;
//        BYTE ucColor = 0;
//
//        if(ucState == _OSD_REJECT)
//        {
//            OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));
//            return;
//        }
//        switch (ucAmount)
//        {
//            case _MENU_ADVANCE_ITEM:
//                ucI = 0;
//                while((OSD_ADVANCE_ITEM_PRI[ucI] != _OSD_ADVANCE_NONE) &&(ucI < _OSD_ADVANCE_ITEM_AMOUNT))
//                {
//                    if((ucState == _OSD_SELECT) && (ucI == ucItem))
//                    {
//                        ucColor = COLOR(_CP_PINK, _CP_BG);
//                    }
//                    else
//                    {
//                        ucColor = COLOR(_CP_GRAY, _CP_BG);
//                    }
//
//                    OsdFontPut1Bit(ucRow, ucCol + ucI, _iINDICATE, ucColor);
//                    ucI++;
//                }
//
//                break;
//        }
//
//
//        if(ucI < 20)
//        {
//            OsdFuncClearOsd(ucRow, ucCol + ucI, WIDTH(20 - ucI), HEIGHT(1));
//        }
//    }
//
//    //--------------------------------------------------
//    // Description :
//    // Input Value :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState)
//    {
//        // _KEY_INFO_ALL
//        BYTE ucColor = COLOR(_CP_BLUE, _CP_BG);
//        BYTE ucRow = 20;
//        BYTE ucCol = 22;
//        BYTE ucInterval = 5;
//        BYTE ucIsMainMenu = _FALSE;
//
//    #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
//           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//        {
//            if((g_ucOsdWidth == _OSD_MAIN_MENU_HEIGHT) && (g_ucOsdHeight == _OSD_MAIN_MENU_WIDTH))
//            {
//                ucIsMainMenu = _TRUE;
//            }
//        }
//        else
//    #endif
//        {
//            if((g_ucOsdWidth == _OSD_MAIN_MENU_WIDTH) && (g_ucOsdHeight == _OSD_MAIN_MENU_HEIGHT))
//            {
//                ucIsMainMenu = _TRUE;
//            }
//        }
//
//        if(ucIsMainMenu == _FALSE)
//        {
//            return;
//        }
//
//
//        if((ucState == _OSD_SELECT) || (ucState == _OSD_HIGHLIGHT))
//        {
//            ucColor = COLOR(_CP_PINK, _CP_BG);
//            ScalerTimerReactiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT);
//        }
//
//        switch(ucItem)
//        {
//            case _KEY_INFO_ENTER:
//                if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
//                {
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
//                }
//                else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
//                {
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                }
//                else
//                {
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
//                }
//
//                break;
//
//            case _KEY_INFO_EXIT:
//                if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
//                {
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
//                }
//                else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
//                {
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                }
//                else
//                {
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
//                }
//                break;
//
//            case _KEY_INFO_LEFT:
//                if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
//                {
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
//                }
//                else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
//                {
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                }
//                else
//                {
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
//                }
//                break;
//
//            case _KEY_INFO_RIGHT:
//                if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
//                {
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
//                }
//                else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
//                {
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                }
//                else
//                {
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
//                }
//                break;
//
//            case _KEY_INFO_BACK:
//                if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
//                {
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_BACK, ucColor);
//                }
//                else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
//                {
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                }
//                else
//                {
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
//                }
//                break;
//
//            case _KEY_INFO_ALL:
//                if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
//                {
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
//                    OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
//                }
//                else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
//                {
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                    OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
//                }
//                else
//                {
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
//                    OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
//                }
//                break;
//
//            default:
//                break;
//        }
//    }
//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
// void OsdDispClearSelectColor(BYTE ucUpDown)
//{
//    if(ucUpDown == _UP)
//    {
//        ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
//    }
//    else
//    {
//        ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
//        // ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
//    }
//}
//
//    #if(_VGA_SUPPORT == _ON)
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainSubString(BYTE ucState)
//    {
//        switch(ucState)
//        {
//            case _AUTO_CONFIG_DO:
//                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_RED, _CP_BG);
//                OsdPropPutString(ROW(14), COL(19), _PFONT_PAGE_1, _STRING_AUTO_ADJUST, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
//                OsdPropPutString(ROW(16), COL(19), _PFONT_PAGE_1, _STRING_PLEASE_WAIT, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
//                break;
//
//            case _AUTO_CONFIG_RESULT:
//                if(g_usAdjustValue != 100)
//                {
//                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_RED, _CP_BG);
//                    OsdPropPutStringCenter(ROW(15), COL(0), WIDTH(_OSD_MAIN_MENU_WIDTH), _PFONT_PAGE_1, _STRING_FAIL, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
//                }
//                else
//                {
//                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_GREEN_119, _CP_BG);
//                    OsdPropPutStringCenter(ROW(15), COL(0), WIDTH(_OSD_MAIN_MENU_WIDTH), _PFONT_PAGE_1, _STRING_PASS, COLOR(_CP_BG, _CP_BG), GET_OSD_LANGUAGE());
//                }
//                break;
//
//            default:
//                break;
//        }
//    }
//    #endif
//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor)
//    {
//        BYTE ucRow = 4;
//        BYTE ucCol = 4;
//
//        ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
//        ucCol = COL(4) + ((ucIconPos % 4) * 10);
//
//        if(ucIcon == _ICON_NONE)
//        {
//            OsdFuncClearOsd(ucRow, (ucCol - 2), WIDTH(10), HEIGHT(5));
//            return;
//        }
//
//        // icon
//        OsdFontVLCDynamicLoadIcon(ucIconPos, ucIcon);
//        OsdFontPut1BitMainMenuIcon(ucRow, ucCol, (_1DYNAMIC_ICON_START + (ucIconPos * 24)), ucColor, _CP_BG);
//    }
//

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState)
{
	BYTE pucOsdItemColor[4];
	BYTE ucI = 0;

	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	//
	//        // color selection
	if (ucUpDown == _UP)
	{
		// up
		for (ucI = 0; ucI < 4; ucI++)
		{
			pucOsdItemColor[ucI] = _CP_LIGHTBLUE;
		}
	}
	else
	{
		// down
		for (ucI = 0; ucI < 4; ucI++)
		{
			pucOsdItemColor[ucI] = _CP_BLUE;
		}
	}
	//
	//        // Arrow
	if (ucUpDown == _UP)
	{
		// switch(ucState)
		//{
		//                case _ICON_PAGE_CLEAR:
		//                    OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
		//                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
		//                    break;
		//
		//                case _ICON_PAGE_DISPLAY_0:
		//                case _ICON_PAGE_COLOR_0:
		//                case _ICON_PAGE_AUDIO_0:
		//                case _ICON_PAGE_OTHER_0:
		//                case _ICON_PAGE_EDID_PORT_0:
		//    #if(_HDR10_SUPPORT == _ON)
		//                case _ICON_PAGE_HDR_ADJUST:
		//    #endif
		//
		//                    OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
		//                    if((SysSourceGetSourceType() != _SOURCE_VGA) && (ucState == _ICON_PAGE_DISPLAY_0))
		//                    {
		//                        OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
		//                    }
		//                    else
		//                    {
		//                        OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);
		//                    }
		//                    break;
		//
		//                case _ICON_PAGE_MAIN_0:
		//                case _ICON_PAGE_MAIN_1:
		//                case _ICON_PAGE_MAIN_2:
		//                case _ICON_PAGE_COLOR_1:
		//                    OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);
		//                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);
		//                    break;
		//                case _ICON_PAGE_ADVANCE:
		//                    if((GET_OSD_ITEM_INDEX()/4) == 0)
		//                        OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
		//                    else
		//                        OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);
		//
		//                    if((GET_OSD_ITEM_INDEX()/4) >= ((_OSD_ADVANCE_ITEM_AMOUNT-1)/4))
		//                        OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
		//                    else
		//                        OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);
		//
		//                    break;
		//
		//                case _ICON_PAGE_DISPLAY_1:
		//                case _ICON_PAGE_COLOR_2:
		//                case _ICON_PAGE_AUDIO_1:
		//                case _ICON_PAGE_OTHER_1:
		//    #if(_HDR10_SUPPORT == _ON)
		//                case _ICON_PAGE_HDR_ADJUST_1:
		//    #endif
		//                case _ICON_PAGE_EDID_PORT_1:
		//                    OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);
		//                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
		//                    break;
		//
		//                default:
		//                    OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
		//                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
		//                    break;
		//}
	}
	else
	{
		switch (ucState)
		{
			//                case _ICON_PAGE_CLEAR:
			//                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
			//                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
			//                    break;
			//
			//                case _ICON_PAGE_DISPLAY_0:
			//                case _ICON_PAGE_COLOR_0:
			//                case _ICON_PAGE_AUDIO_0:
			//                case _ICON_PAGE_OTHER_0:
			//                case _ICON_PAGE_GAMMA_0:
			//                case _ICON_PAGE_TEMPRATURE_0:
			//                case _ICON_PAGE_COLOR_EFFECT_0:
			//                case _ICON_PAGE_COLOR_DEMO_0:
			//                case _ICON_PAGE_COLOR_EFFECT_USER_0:
			//                case _ICON_PAGE_ASPECT_RATIO_0:
			//                case _ICON_PAGE_DISP_ROTATE_0:
			//                case _ICON_PAGE_EDID_PORT_0:
			//                    if(_DISP_ROTATE_AMOUNT <= 4)
			//                    {
			//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
			//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
			//                        break;
			//                    }
			//                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
			//
			//                    if((SysSourceGetSourceType() != _SOURCE_VGA) && (ucState == _ICON_PAGE_DISPLAY_0))
			//                    {
			//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
			//                    }
			//                    else
			//                    {
			//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
			//                    }
			//                    break;
			//
			//                case _ICON_PAGE_COLOR_1:
			//
			//                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
			//                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
			//                    break;
			//
			//                case _ICON_PAGE_COLOR_PCM_0:
			//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
			//                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
			//    #endif
			//                    break;
			//
			//                case _ICON_PAGE_DISPLAY_1:
			//                case _ICON_PAGE_COLOR_2:
			//                case _ICON_PAGE_AUDIO_1:
			//                case _ICON_PAGE_OTHER_1:
			//                case _ICON_PAGE_GAMMA_1:
			//                case _ICON_PAGE_TEMPRATURE_1:
			//                case _ICON_PAGE_COLOR_EFFECT_1:
			//                case _ICON_PAGE_COLOR_DEMO_1:
			//                case _ICON_PAGE_COLOR_PCM_1:
			//                case _ICON_PAGE_COLOR_EFFECT_USER_1:
			//                case _ICON_PAGE_ASPECT_RATIO_1:
			//                case _ICON_PAGE_DISP_ROTATE_1:
			//                case _ICON_PAGE_EDID_PORT_1:
			//
			//                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
			//                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
			//                    break;
		case _ICON_PAGE_INPUT_0:
		case _ICON_PAGE_INPUT_1:
		case _ICON_PAGE_INPUT_2:
			OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
			OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
			break;
		default:
			OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
			OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
			break;
		}
	}

	ucUpDown *= _ICON_POS_DOWN_0;

	switch (ucState)
	{
		//            case _ICON_PAGE_CLEAR:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_MAIN_0:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PICTURE, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DISPLAY, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_ADVANCE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_MAIN_1:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_INPUT, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_AUDIO, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_OTHER, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_INFORMATION, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_MAIN_2:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_FACTORY, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_PICTURE_0:
		//    #if(_HDR10_SUPPORT == _ON)
		//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
		//                {
		//                    pucOsdItemColor[0] = _CP_GRAY;
		//                    pucOsdItemColor[1] = _CP_GRAY;
		//                    pucOsdItemColor[2] = _CP_GRAY;
		//                }
		//    #endif
		//    #if(_FREESYNC_II_SUPPORT == _ON)
		//                if(UserCommonHDRGetFreesynIIStatus() == _ON)
		//                {
		//                    pucOsdItemColor[0] = _CP_GRAY;
		//                    pucOsdItemColor[1] = _CP_GRAY;
		//                    pucOsdItemColor[2] = _CP_GRAY;
		//                }
		//    #endif
		//
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_BACKLIGHT, pucOsdItemColor[0]);
		//    #if(_BRIGHTNESS_SUPPORT == _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_BRIGHTNESS, pucOsdItemColor[1]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_BRIGHTNESS, _CP_GRAY);
		//    #endif
		//
		//    #if(_CONTRAST_SUPPORT == _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_CONTRAST, pucOsdItemColor[2]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_CONTRAST, _CP_GRAY);
		//    #endif
		//
		//    #if(_SHARPNESS_SUPPORT == _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_SHARPNESS, pucOsdItemColor[3]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_SHARPNESS, _CP_GRAY);
		//    #endif
		//                break;
		//
		//            case _ICON_PAGE_DISPLAY_0:
		//                if(SysSourceGetSourceType() != _SOURCE_VGA)
		//                {
		//                    for(ucI = 0; ucI < 4; ucI++)
		//                    {
		//                        pucOsdItemColor[ucI] = _CP_GRAY;
		//                    }
		//                }
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_HPOS, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_VPOS, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_AUTO_ADJUST, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_CLOCK, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_DISPLAY_1:
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DISP_ROTATE, pucOsdItemColor[1]);
		//
		//    #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
		//    #if(_DISPLAY_ROTATION_SUPPORT == _ON)
		//                if(GET_OSD_DISP_ROTATE() != _DISP_ROTATE_0)
		//                {
		//                    pucOsdItemColor[2] = _CP_GRAY;
		//                }
		//    #endif
		//    #else
		//                pucOsdItemColor[2] = _CP_GRAY;
		//    #endif // End of #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
		//
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_LANTENCY, pucOsdItemColor[2]);
		//
		//    #if(_FREEZE_SUPPORT == _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_FREEZE, pucOsdItemColor[3]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_FREEZE, _CP_GRAY);
		//    #endif
		//
		//                if(SysSourceGetSourceType() != _SOURCE_VGA)
		//                {
		//                    pucOsdItemColor[0] = _CP_GRAY;
		//                }
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PHASE, pucOsdItemColor[0]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_0:
		//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
		//                if(GET_OSD_LOCAL_DIMMING()== _ON)
		//                {
		//                    pucOsdItemColor[0] = _CP_GRAY;
		//                }
		//    #endif
		//    #if(_FREESYNC_II_SUPPORT == _ON)
		//                if(UserCommonHDRGetFreesynIIStatus() == _ON)
		//                {
		//                    pucOsdItemColor[0] = _CP_GRAY;
		//                    pucOsdItemColor[1] = _CP_GRAY;
		//                    pucOsdItemColor[2] = _CP_GRAY;
		//                }
		//    #endif
		//
		//    #if(_HDR10_SUPPORT == _ON)
		//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
		//                {
		//                    pucOsdItemColor[0] = _CP_GRAY;
		//                    pucOsdItemColor[1] = _CP_GRAY;
		//                    pucOsdItemColor[2] = _CP_GRAY;
		//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
		//                    if(GET_OSD_HDR_LIGHT_ENHANCE() != 0)
		//                        pucOsdItemColor[3] = _CP_GRAY;
		//    #endif
		//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
		//                    if(GET_OSD_HDR_COLOR_ENHANCE() != 0)
		//                        pucOsdItemColor[3] = _CP_GRAY;
		//    #endif
		//
		//                }
		//    #endif
		//    #if(_SDR_TO_HDR_SUPPORT == _ON)
		//                if(GET_OSD_SDR_TO_HDR() == _ON)
		//                {
		//                    pucOsdItemColor[0] = _CP_GRAY;
		//                    pucOsdItemColor[1] = _CP_GRAY;
		//                    pucOsdItemColor[2] = _CP_GRAY;
		//                    pucOsdItemColor[3] = _CP_GRAY;
		//                }
		//    #endif
		//
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PANEL_UNIFORMITY, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_GAMMA, pucOsdItemColor[1]);
		//    #if(_CONTRAST_SUPPORT == _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR_TEMPERATURE, pucOsdItemColor[2]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR_TEMPERATURE, _CP_GRAY);
		//    #endif
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_COLOR_EFFECT, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_1:
		//    #if(_HDR10_SUPPORT == _ON)
		//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
		//                {
		//                    pucOsdItemColor[1] = _CP_GRAY;
		//                    pucOsdItemColor[2] = _CP_GRAY;
		//                    pucOsdItemColor[3] = _CP_GRAY;
		//                }
		//    #endif
		//
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_COLOR_DEMO, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_PCM, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_HUE, pucOsdItemColor[3]);
		//
		//    #if(_COLOR_FORMAT_CONVERT == _ON)
		//                if((SysSourceGetSourceType() == _SOURCE_VGA) || (SysSourceGetSourceType() == _SOURCE_DVI))
		//                {
		//                    OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR_FORMAT, pucOsdItemColor[1]);
		//                }
		//                else
		//    #endif
		//                {
		//                    OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR_FORMAT, _CP_GRAY);
		//                }
		//                break;
		//
		//            case _ICON_PAGE_COLOR_2:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_SATURATION, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//            case _ICON_PAGE_ADVANCE:
		//                OsdDispMainMenuIconString((ucUpDown + 0), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+0), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+0)))? pucOsdItemColor[0] : _CP_GRAY);
		//                OsdDispMainMenuIconString((ucUpDown + 1), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+1), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+1)))? pucOsdItemColor[1] : _CP_GRAY);
		//                OsdDispMainMenuIconString((ucUpDown + 2), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+2), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+2)))? pucOsdItemColor[2] : _CP_GRAY);
		//                OsdDispMainMenuIconString((ucUpDown + 3), OsdDispAdvanceIconGet((GET_OSD_ITEM_INDEX()/4)*4+3), (OsdDispAdvanceItemCheck(((GET_OSD_ITEM_INDEX()/4)*4+3)))? pucOsdItemColor[3] : _CP_GRAY);
		//                break;
		//
		//
		//
	case _ICON_PAGE_INPUT_0:
		OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D0_PORT, pucOsdItemColor[0]);
		OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D1_PORT, pucOsdItemColor[1]);
		OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D2_PORT, pucOsdItemColor[2]);
		OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D3_PORT, pucOsdItemColor[3]);
		break;

	case _ICON_PAGE_INPUT_1:
		OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D3_PORT, pucOsdItemColor[0]);
		OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D4_PORT, pucOsdItemColor[1]);
		OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D5_PORT, pucOsdItemColor[2]);
		OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D6_PORT, pucOsdItemColor[3]);
		break;

	case _ICON_PAGE_INPUT_2:

		OsdDispMainMenuIconString((ucUpDown + 0), _ICON_INPUT_AUTO, pucOsdItemColor[0]);
		OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		break;
		//
		//            case _ICON_PAGE_AUDIO_0:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_VOLUME, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_MUTE, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_STAND_ALONG, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_AUDIO_SOURCE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_AUDIO_1:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_SOUND_MODE, pucOsdItemColor[0]);
		//    #if(_INTERNAL_AUDIO_TEST_SUPPORT== _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_AUDIO_SELF_TEST, pucOsdItemColor[1]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//    #endif
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_OTHER_0:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_RESET, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_MENU_TIME, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_OSD_HPOS, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_OSD_VPOS, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_OTHER_1:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_LANGUAGE, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_TRNASPARENCY, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_ROTATE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_INFORMATION_0:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_ON_OFF:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ON, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_OFF, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_ASPECT_RATIO_0:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AS_RATIO_FULL, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_AS_RATIO_16_9, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_AS_RATIO_4_3, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_AS_RATIO_5_4, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_ASPECT_RATIO_1:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_PCM_USER, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_AS_RATIO_ORIGINAL, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_AUDIO_SOURCE:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AUDIO_ANALOG, pucOsdItemColor[0]);
		//
		//                if((SysSourceGetSourceType() == _SOURCE_VGA) ||
		//                   (SysSourceGetSourceType() == _SOURCE_DVI))
		//                {
		//                    OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//                }
		//                else
		//                {
		//                    OsdDispMainOptionIcon((ucUpDown + 1), _ICON_AUDIO_DIGITAL, pucOsdItemColor[1]);
		//                }
		//
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_ULTRA_VIVID:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ULTRA_VIVID_L, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_ULTRA_VIVID_M, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_ULTRA_VIVID_H, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_GAMMA_0:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_8, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_2_DOT_0, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_2_DOT_2, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_GAMMA_1:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_2_DOT_4, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_TEMPRATURE_0:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_9300, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_7500, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_6500, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_TEMP_5800, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_TEMPRATURE_1:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_SRGB, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_USER, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_EFFECT_0:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_EFF_STD, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_GAME, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_EFF_MOVIE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_EFF_PHOTO, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_EFFECT_1:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_EFF_VIVID, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_DEMO_0:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_DEMO_TYPE1, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_DEMO_TYPE2, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_DEMO_TYPE3, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_DEMO_1:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_DEMO_TYPE4, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_DEMO_TYPE5, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_FORMAT:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_FORMAT_RGB, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_FORMAT_YUV, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_TEMPERATURE_USER:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_R, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_USER_G, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_USER_B, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_PCM_0:
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_PCM_USER, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_PCM_NACTIVE, pucOsdItemColor[3]);
		//    #if(_OCC_SUPPORT == _ON)
		//                for(ucI = 0; ucI < 4; ucI++)
		//                {
		//                    pucOsdItemColor[ucI] = _CP_BLUE;
		//                }
		//    #else
		//                for(ucI = 0; ucI < 4; ucI++)
		//                {
		//                    pucOsdItemColor[ucI] = _CP_GRAY;
		//                }
		//    #endif
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_PCM_SRGB, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_PCM_ADOBE_RGB, pucOsdItemColor[1]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_PCM_1:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_PCM_SOFT_PROFT, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_EFFECT_USER_0:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_R, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER_Y, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_USER_G, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_EFF_USER_C, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_EFFECT_USER_1:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_B, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER_M, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_COLOR_RGBYCM_HUE_SAT:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_HUE, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_SATURATION, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_PCM_SOFT_PROFT:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_MODE1, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_MODE2, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_OSD_ROTATE:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_0_DEGREE, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_90_DEGREE, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_270_DEGREE, pucOsdItemColor[2]);
		//    #if(_OSD_ROTATE_CW180_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_180_DEGREE, pucOsdItemColor[3]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_180_DEGREE, _CP_GRAY);
		//    #endif
		//                break;
		//
		//            case _ICON_PAGE_OD_ADJUST:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ONOFF, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_OD_GAIN, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_DP_OPTION:
		//    #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, pucOsdItemColor[0]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, _CP_GRAY);
		//    #endif
		//
		//    #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, pucOsdItemColor[1]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, _CP_GRAY);
		//    #endif
		//
		//    #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D2, pucOsdItemColor[2]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D2, _CP_GRAY);
		//    #endif
		//
		//    #if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, pucOsdItemColor[3]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, _CP_GRAY);
		//    #endif
		//                break;
		//
		//            case _ICON_PAGE_DP_1_DOT_X:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_1, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_2, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_1_DOT_3, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_DP_MST:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
		//    #if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D0, pucOsdItemColor[1]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D0, _CP_GRAY);
		//    #endif
		//
		//    #if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D1, pucOsdItemColor[2]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D1, _CP_GRAY);
		//    #endif
		//
		//    #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&
		//        ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, pucOsdItemColor[3]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, _CP_GRAY);
		//    #endif
		//                break;
		//
		//            case _ICON_PAGE_DISP_ROTATE_0:
		//                OsdDispMainOptionIcon((ucUpDown++), _ICON_0_DEGREE, pucOsdItemColor[0]);
		//    #if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown++), _ICON_90_DEGREE, pucOsdItemColor[0]);
		//    #endif
		//    #if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown++), _ICON_180_DEGREE, pucOsdItemColor[0]);
		//    #endif
		//    #if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown++), _ICON_270_DEGREE, pucOsdItemColor[0]);
		//    #endif
		//    #if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
		//                if(_DISP_ROTATE_HOR_MIRROR <= 3)
		//                {
		//                    OsdDispMainOptionIcon((ucUpDown++), _ICON_LR_MIRROR, pucOsdItemColor[0]);
		//                }
		//    #endif
		//    #if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
		//                if(_DISP_ROTATE_VER_MIRROR <= 3)
		//                {
		//                    OsdDispMainOptionIcon((ucUpDown++), _ICON_UD_MIRROR, pucOsdItemColor[0]);
		//                }
		//    #endif
		//                break;
		//
		//            case _ICON_PAGE_DISP_ROTATE_1:
		//
		//    #if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
		//                if(_DISP_ROTATE_HOR_MIRROR > 3)
		//                {
		//                    OsdDispMainOptionIcon((ucUpDown++), _ICON_LR_MIRROR, pucOsdItemColor[0]);
		//                }
		//    #endif
		//    #if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
		//                if(_DISP_ROTATE_VER_MIRROR > 3)
		//                {
		//                    OsdDispMainOptionIcon((ucUpDown++), _ICON_UD_MIRROR, pucOsdItemColor[0]);
		//                }
		//    #endif
		//                OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[3]);
		//                if(_DISP_ROTATE_AMOUNT < 6)
		//                {
		//                    OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[0]);
		//                }
		//
		//
		//                break;
		//
		//            case _ICON_PAGE_LATENCY:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ULTRA_VIVID_L, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ULTRA_VIVID_M, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_ULTRA_VIVID_H, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_RESOLUTION:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_DP_1080P, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_DP_2560_1440, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_DP_4K2K_60HZ, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//            case _ICON_PAGE_EDID_PORT_0:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D0_PORT, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D1_PORT, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D2_PORT, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D3_PORT, pucOsdItemColor[3]);
		//                break;
		//            case _ICON_PAGE_EDID_PORT_1:
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D4_PORT, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D5_PORT, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//            case _ICON_PAGE_HDMI_VERSIONS:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_4, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_2_DOT_0, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_2_DOT_1, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//
		//                break;
		//            case _ICON_PAGE_CLONE_0:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ON, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
		//            case _ICON_PAGE_TYPEC_MODE:
		//    #if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, pucOsdItemColor[0]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, _CP_GRAY);
		//    #endif
		//
		//    #if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, pucOsdItemColor[2]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, _CP_GRAY);
		//    #endif
		//    #if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D2, pucOsdItemColor[2]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D2, _CP_GRAY);
		//    #endif
		//
		//    #if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, pucOsdItemColor[3]);
		//    #else
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, _CP_GRAY);
		//    #endif
		//                break;
		//            case _ICON_PAGE_TYPEC_MODE_U3_ONOFF:
		//
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_U3_ON, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_U3_OFF, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//    #endif
		//
		//    #if(_HDR10_SUPPORT == _ON)
		//            case _ICON_PAGE_HDR_ADJUST:
		//                if(UserCommonHDRGetHDR10Status() == _HDR10_OFF)
		//                {
		//                    pucOsdItemColor[1]=pucOsdItemColor[2]=pucOsdItemColor[3]=_CP_GRAY;
		//                }
		//
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_HDR_MODE, pucOsdItemColor[0]);
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DARK_ENHANCE, pucOsdItemColor[1]);
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_HDR_SHARPNESS, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_CONTRAST, pucOsdItemColor[3]);
		//                break;
		//            case _ICON_PAGE_HDR_ADJUST_1:
		//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_COLOR_ENHANCE, pucOsdItemColor[0]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_COLOR_ENHANCE, _CP_GRAY);
		//    #endif
		//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_LIGHT_ENHANCE, pucOsdItemColor[1]);
		//    #else
		//                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_LIGHT_ENHANCE, _CP_GRAY);
		//    #endif
		//                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//
		//            case _ICON_PAGE_HDR_MODE:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_INPUT_AUTO, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_HDR10_MODE_FORCE_2084, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//    #endif
		//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
		//            case _ICON_PAGE_LOCAL_DIMMING:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ONOFF, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_LD_SMOOTHADJ, pucOsdItemColor[1]);
		//                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
		//                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
		//                break;
		//    #endif
		//
		//            case _ICON_PAGE_OSD_LANGUAGE:
		//                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ENGLISH, pucOsdItemColor[0]);
		//                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_CHINESE_T, pucOsdItemColor[1]);
		//
		//                break;
		//
		//
	default:
		break;
	}
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState)
{
	BYTE ucIcon = _iLEFT_00;
	BYTE ucColor = COLOR(_CP_WHITE, _CP_BG);
	BYTE ucCol = 1;
	BYTE ucRow = 5;

	if (ucUpDown == _DOWN)
	{
		ucRow = 15;
		ucColor = COLOR(_CP_BLUE, _CP_BG);
	}

	if (ucLeftRight == _RIGHT)
	{
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
		if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
			(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
		{
			ucCol = g_ucOsdHeight - 2;
		}
		else
#endif
		{
			ucCol = g_ucOsdWidth - 2;
		}
		ucIcon = _iRIGHT_00;
	}

	if (ucState == _OSD_SELECT)
	{
		ucColor = COLOR(_CP_ORANGE, _CP_BG);
	}

	if (ucState == _OSD_REJECT)
	{
		OsdFontPut1Bit(ucRow, ucCol, ___, ucColor);
		OsdFontPut1Bit(ucRow + 1, ucCol, ___, ucColor);
	}
	else
	{
		OsdFontPut1Bit(ucRow, ucCol, ucIcon, ucColor);
		OsdFontPut1Bit(ucRow + 1, ucCol, ucIcon + 1, ucColor);
	}
}
//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption)
//    {
//        BYTE ucRow = 0;
//        BYTE ucCol = 0;
//        BYTE ucWin = _OSD_WINDOW_4_2;
//        BYTE ucWinColor = _CP_LIGHTBLUE;
//        BYTE ucForegroundColor = _CP_ORANGE;
//
//        ucRow = ROW(14);
//
//        if(ucSelectState == _SELECT)
//        {
//            ucForegroundColor = _CP_ORANGE;
//        }
//        else
//        {
//            ucForegroundColor = _CP_WHITE;
//        }
//
//        switch(ucItem)
//        {
//            case _OPTION_OVERSCAN_ONOFF:
//            case _OPTION_OVERDRIVE_ONOFF:
//            case _OPTION_DCR_ONOFF:
//            case _OPTION_DDCCI_ONOFF:
//            case _OPTION_MUTE_ONOFF:
//            case _OPTION_STAND_ALONG_ONOFF:
//            case _OPTION_PANEL_UNIFORMITY_ONOFF:
//            case _OPTION_COLOR_EFFC_USER_RGBYCM:
//            case _OPTION_FREESYNC_ONOFF_TYPE:
//            case _OPTION_ON_OFF:
//                if(ucOption == _ON)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_AUDIO_SOURCE:
//                if(ucOption == _LINE_IN_AUDIO)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else // digital
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_ASPECT_RATIO_TYPE:
//                if((ucOption == _OSD_ASPECT_RATIO_FULL) ||
//                   (ucOption == _OSD_ASPECT_RATIO_USER))
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if((ucOption == _OSD_ASPECT_RATIO_16_BY_9)||(ucOption == _OSD_ASPECT_RATIO_ORIGIN))
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _OSD_ASPECT_RATIO_4_BY_3)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _OSD_ASPECT_RATIO_5_BY_4)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                if(GET_OSD_STATE() == _MENU_ADVANCE_ASPECT_ADJUST)
//                {
//                    if(ucOption >= _OSD_ASPECT_RATIO_USER)
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
//                    }
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_ULTRA_VIVID_TYPE:
//                if(ucOption == _ULTRA_VIVID_OFF)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _ULTRA_VIVID_L)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _ULTRA_VIVID_M)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _ULTRA_VIVID_H)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_GAMMA_TYPE:
//                if((ucOption == _GAMMA_OFF) || (ucOption == _GAMMA_24))
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _GAMMA_18)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _GAMMA_20)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _GAMMA_22)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                if(GET_OSD_STATE() == _MENU_COLOR_GAMMA_ADJUST)
//                {
//                    if(ucOption >= _GAMMA_24)
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
//                    }
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_TEMPRATURE_TYPE:
//                if((ucOption == _CT_9300) || (ucOption == _CT_SRGB))
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if((ucOption == _CT_7500) || (ucOption == _CT_USER))
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _CT_6500)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _CT_5800)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                if(GET_OSD_STATE() == _MENU_COLOR_TEMPERATURE_ADJUST)
//                {
//                    if(ucOption >= _CT_SRGB)
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
//                    }
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_COLOR_EFFECT_TYPE:
//                if((ucOption == _COLOREFFECT_STANDARD) || (ucOption == _COLOREFFECT_VIVID))
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if((ucOption == _COLOREFFECT_GAME) || (ucOption == _COLOREFFECT_USER))
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//
//                else if(ucOption == _COLOREFFECT_MOVIE)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _COLOREFFECT_PHOTO)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                if(GET_OSD_STATE() == _MENU_COLOR_EFFECT_ADJUST)
//                {
//                    if(ucOption >= _COLOREFFECT_VIVID)
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
//                    }
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_COLOR_DEMO_TYPE:
//                if((ucOption == _HL_WIN_OFF) || (ucOption == _HL_WIN_4))
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if((ucOption == _HL_WIN_1) || (ucOption == _HL_WIN_5))
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _HL_WIN_2)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _HL_WIN_3)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                if(GET_OSD_STATE() == _MENU_COLOR_DEMO_ADJUST)
//                {
//                    if(ucOption >= _HL_WIN_4)
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
//                        OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
//                    }
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_COLOR_FORMAT_TYPE:
//                if(ucOption == _COLOR_SPACE_RGB)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else
//                {
//                    // digital
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_COLOR_PCM_TYPE:
//    #if(_OCC_SUPPORT == _ON)
//    #if(_RGB_3D_GAMMA == _ON)
//                if((ucOption == _PCM_OSD_SRGB) || (ucOption == _PCM_OSD_SOFT_PROFT))
//    #else
//                if(ucOption == _PCM_OSD_SRGB)
//    #endif
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _PCM_OSD_ADOBE_RGB)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _PCM_OSD_USER)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _PCM_OSD_NATIVE)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//    #else
//                if(ucOption == _PCM_OSD_USER)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _PCM_OSD_NATIVE)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//    #endif
//
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                if(ucOption >= _PCM_OSD_SOFT_PROFT)
//                {
//                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
//                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
//                }
//                else
//                {
//                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
//                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
//                }
//    #endif
//
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_COLOR_PCM_SOFT_PROFT_TYPE:
//
//                if(ucOption == _PCM_SOFT_MODE_1)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _PCM_SOFT_MODE_2)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_TEMPRATURE_USER_ADJUST:
//                ucWin = _OSD_WINDOW_4_1;
//                ucWinColor = _CP_BLUE;
//                ucRow = ROW(4);
//                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                ucForegroundColor = _CP_BLUE_120;
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_COLOR_EFFC_USER_ADJUST:
//                ucWin = _OSD_WINDOW_4_1;
//                ucWinColor = _CP_BLUE;
//                ucRow = ROW(4);
//                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                ucForegroundColor = _CP_BLUE_120;
//
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_COLOR_RGBYCM_HUE_STA:
//
//                if(ucOption == _COLOR_HUE)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _COLOR_SATURATION)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_LANGUAGE_ADJUST:
//                if(ucOption == _ENGLISH)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _CHINESE_T)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_ROTATE_ADJUST:
//                if(ucOption == _OSD_ROTATE_DEGREE_0)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _OSD_ROTATE_DEGREE_90)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _OSD_ROTATE_DEGREE_270)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _OSD_ROTATE_DEGREE_180)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_INPUT_SOURCE_TYPE:
//                if(ucOption == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else
//                {
//                    if(SysSourceGetInputPort() == _A0_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                    }
//                    else if(SysSourceGetInputPort() == _D0_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                    }
//                    else if(SysSourceGetInputPort() == _D1_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                    }
//                    else if(SysSourceGetInputPort() == _D2_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                    }
//                    else if(SysSourceGetInputPort() == _D3_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                    }
//                    else if(SysSourceGetInputPort() == _D4_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                    }
//                    else if(SysSourceGetInputPort() == _D5_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                    }
//                    else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
//                    {
//                        ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                    }
//                }
//
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_DP_PORT_VERSION:
//                if(ucOption == _DP_VER_1_DOT_1)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _DP_VER_1_DOT_2)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _DP_VER_1_DOT_3)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_DP_MST_TYPE:
//                if(ucOption == _MST_OFF)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _MST_D0)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _MST_D1)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _MST_D6)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//
//                break;
//
//            case _OPTION_DP_EDID_TYPE:
//                if(ucOption == _DP_EDID_1080P)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _DP_EDID_2560_1440)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _DP_EDID_4K2K_60HZ)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else //if(ucOption == _DP_EDID_4K2K_30HZ)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//
//                break;
//
//            case _OPTION_CLONE_TYPE:
//                ucCol = COL(4) + ((GET_OSD_CLONE_MODE() % 4) * 10) - 2;
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//
//            case _OPTION_DISP_ROTATE_TYPE:
//                if((ucOption % 4) == _DISP_ROTATE_0)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//
//                else if((ucOption % 4) == _DISP_ROTATE_0 + 1)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if((ucOption % 4) == _DISP_ROTATE_0 + 2)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if((ucOption % 4) == _DISP_ROTATE_0 + 3)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//
//                break;
//
//            case _OPTION_LATENCY_TYPE:
//                if(ucOption == _LATENCY_L)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _LATENCY_M)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _LATENCY_H)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//
//                break;
//
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//            case _OPTION_TYPEC_MODE_SELECT:
//                if(ucOption == _TYPE_C_U3_ON)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                if(ucOption == _TYPE_C_U3_OFF)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//    #endif
//
//    #if(_HDR10_SUPPORT == _ON)
//            case _OPTION_HDR_MODE_SELECT:
//                if(ucOption == _HDR10_MODE_OFF)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                if(ucOption == _HDR10_MODE_AUTO)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _HDR10_MODE_FORCE_2084)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//    #endif
//            case _OPTION_LEVEL_TYPE:
//                if(ucOption == _LEVEL_OFF)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _LEVEL_L)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _LEVEL_M)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                else if(ucOption == _LEVEL_H)
//                {
//                    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                }
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//                break;
//            case _OPTION_HDMI_VERSIONS_TYPE:
//                if(ucOption == _EDID_INDEX_0)
//                {
//                    ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
//                }
//                else if(ucOption == _EDID_INDEX_1)
//                {
//                    ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
//                }
//                else if(ucOption == _EDID_INDEX_2)
//                {
//                    ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
//                }
//                //else if(ucOption == _HDMI_EDID_3)
//                //{
//                //    ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
//                //}
//                OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
//
//                break;
//
//            default:
//                break;
//        }
//
//        if(ucItem == _OPTION_COLOR_PCM_TYPE)
//        {
//    #if(_OCC_SUPPORT == _ON)
//            OsdFuncChangeIconColor1Bit(ROW(14), _ITEM_6, WIDTH(g_ucOsdWidth), HEIGHT(4), _CP_BLUE);
//    #endif
//        }
//        else if(ucItem == _OPTION_DP_MST_TYPE)
//        {
//        }
//        else if(ucItem == _OPTION_DISP_ROTATE_TYPE)
//        {
//        }
//        else
//        {
//            OsdFuncChangeIconColor1Bit(ROW(14), _ITEM_4, WIDTH(g_ucOsdWidth), HEIGHT(4), _CP_BLUE);
//        }
//    }

//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispClearArrow(BYTE ucUpDown)
//    {
//        OsdDispMainMenuArrow(ucUpDown, _LEFT, _OSD_REJECT);
//        OsdDispMainMenuArrow(ucUpDown, _RIGHT, _OSD_REJECT);
//    }
//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious)
//    {
//        BYTE ucItemPrev = 0;
//        BYTE ucItemCurr = 0;
//        switch(ucItem)
//        {
//            case _ICON_SUB_SEL_INPUT:
//                // previous state
//                if((usOsdStatePrevious >= _MENU_INPUT_AUTO) &&
//                   (usOsdStatePrevious <= _MENU_INPUT_D6_PORT))
//                {
//                    ucItemPrev = usOsdStatePrevious - _MENU_INPUT_AUTO;
//                }
//                // current state
//                if((usOsdState >= _MENU_INPUT_AUTO) && (usOsdState <= _MENU_INPUT_D6_PORT))
//                {
//                    ucItemCurr = usOsdState - _MENU_INPUT_AUTO;
//                }
//                break;
//
//            default:
//                break;
//        }
//
//        OsdDispMainMenuItemSelection((ucItemPrev % 4) + 4, _OSD_UNSELECT);
//        OsdDispMainMenuItemSelection((ucItemCurr % 4) + 4, _OSD_SELECT);
//    }
//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary)
//    {
//        BYTE ucItem = 0;
//        BYTE ucAmount = 0;
//        WORD usOsdCount = 0;
//
//        if(bInSubsidiary == _OUTSUBSET)
//        {
//            usOsdCount = usOsdState;
//        }
//        else
//        {
//            usOsdCount = usOsdStatePrevious;
//        }
//
//            if((usOsdCount >= _MENU_PICTURE) && (usOsdCount <= _MENU_FACTORY))
//            {
//                ucItem = usOsdCount - _MENU_PICTURE;
//                ucAmount = (_MENU_FACTORY - _MENU_PICTURE + 1);
//            }
//            else if((usOsdCount >= _MENU_PICTURE_BACKLIGHT) &&
//                    (usOsdCount <= _MENU_PICTURE_SHARPNESS))
//            {
//                ucItem = usOsdCount - _MENU_PICTURE_BACKLIGHT;
//                ucAmount = (_MENU_PICTURE_SHARPNESS - _MENU_PICTURE_BACKLIGHT + 1);
//            }
//            else if((usOsdCount >= _MENU_DISPLAY_AUTO) && (usOsdCount <= _MENU_DISPLAY_FREEZE))
//            {
//                ucItem = usOsdCount - _MENU_DISPLAY_AUTO;
//                ucAmount = (_MENU_DISPLAY_FREEZE - _MENU_DISPLAY_AUTO + 1);
//            }
//            else if((usOsdCount >= _MENU_COLOR_PANEL_UNIFORMITY) && (usOsdCount <= _MENU_COLOR_SATURATION))
//            {
//                ucItem = usOsdCount - _MENU_COLOR_PANEL_UNIFORMITY;
//                ucAmount = (_MENU_COLOR_SATURATION - _MENU_COLOR_PANEL_UNIFORMITY + 1);
//            }
//
//            else if((usOsdCount >= _MENU_INPUT_AUTO) && (usOsdCount <= _MENU_INPUT_D1_PORT))
//            {
//                ucItem = usOsdCount - _MENU_INPUT_AUTO;
//                ucAmount = (_MENU_INPUT_D1_PORT - _MENU_INPUT_AUTO + 1);
//            }
//        #if(_INTERNAL_AUDIO_TEST_SUPPORT== _ON)
//            else if((usOsdCount >= _MENU_AUDIO_VOLUME) && (usOsdCount <= _MENU_AUDIO_AUDIO_SELF_TEST))
//            {
//                ucItem = usOsdCount - _MENU_AUDIO_VOLUME;
//                ucAmount = (_MENU_AUDIO_AUDIO_SELF_TEST - _MENU_AUDIO_VOLUME + 1);
//            }
//        #else
//            else if((usOsdCount >= _MENU_AUDIO_VOLUME) && (usOsdCount <= _MENU_AUDIO_SOUND_MODE))
//            {
//                ucItem = usOsdCount - _MENU_AUDIO_VOLUME;
//                ucAmount = (_MENU_AUDIO_SOUND_MODE - _MENU_AUDIO_VOLUME + 1);
//            }
//        #endif
//            else if((usOsdCount >= _MENU_OTHER_RESET) && (usOsdCount <= _MENU_OTHER_ROTATE))
//            {
//                ucItem = usOsdCount - _MENU_OTHER_RESET;
//                ucAmount = (_MENU_OTHER_ROTATE - _MENU_OTHER_RESET + 1);
//            }
//            else if(usOsdCount == _MENU_COLOR_EFFECT_ADJUST)
//            {
//                ucItem = GET_OSD_COLOR_EFFECT() - _COLOREFFECT_STANDARD;
//                ucAmount = _COLOREFFECT_AMOUNT;
//            }
//            else if((usOsdCount >= _MENU_COLOR_TEMP_USER_R) && (usOsdCount <= _MENU_COLOR_TEMP_USER_B))
//            {
//                ucItem = usOsdCount - _MENU_COLOR_TEMP_USER_R;
//                ucAmount = (_MENU_COLOR_TEMP_USER_B - _MENU_COLOR_TEMP_USER_R + 1);
//            }
//            else if((usOsdCount >= _MENU_COLOR_EFF_USER_R) && (usOsdCount <= _MENU_COLOR_EFF_USER_M))
//            {
//                ucItem = usOsdCount - _MENU_COLOR_EFF_USER_R;
//                ucAmount = (_MENU_COLOR_EFF_USER_M - _MENU_COLOR_EFF_USER_R + 1);
//            }
//
//            else if((usOsdCount >= _MENU_ADVANCE_OVER_DRIVE_ONOFF) && (usOsdCount <= _MENU_ADVANCE_OVER_DRIVE_GAIN))
//            {
//                ucItem = usOsdCount - _MENU_ADVANCE_OVER_DRIVE_ONOFF;
//                ucAmount = (_MENU_ADVANCE_OVER_DRIVE_GAIN - _MENU_ADVANCE_OVER_DRIVE_ONOFF + 1);
//            }
//            else if((usOsdCount >= _MENU_ADVANCE_DP_OPTION_D0) && (usOsdCount <= _MENU_ADVANCE_DP_OPTION_D6))
//            {
//                ucItem = usOsdCount - _MENU_ADVANCE_DP_OPTION_D0;
//                ucAmount = (_MENU_ADVANCE_DP_OPTION_D6 - _MENU_ADVANCE_DP_OPTION_D0 + 1);
//            }
//        #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//            else if((usOsdCount >= _MENU_ADVANCE_TYPEC_MODE_D0) && (usOsdCount <= _MENU_ADVANCE_TYPEC_MODE_D6))
//            {
//                ucItem = usOsdCount - _MENU_ADVANCE_TYPEC_MODE_D0;
//                ucAmount = (_MENU_ADVANCE_TYPEC_MODE_D6 - _MENU_ADVANCE_TYPEC_MODE_D0 + 1);
//            }
//        #endif
//        #if(_HDR10_SUPPORT == _ON)
//            else if((usOsdCount >= _MENU_ADVANCE_HDR_MODE) && (usOsdCount <= _MENU_ADVANCE_HDR_LIGHT_ENHANCE))
//            {
//                ucItem = usOsdCount - _MENU_ADVANCE_HDR_MODE;
//                ucAmount = (_MENU_ADVANCE_HDR_LIGHT_ENHANCE - _MENU_ADVANCE_HDR_MODE + 1);
//            }
//        #endif
//        #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//            else if((usOsdCount >= _MENU_ADVANCE_HDR_LD_ONOFF) && (usOsdCount <= _MENU_ADVANCE_HDR_LD_SMOOTH_ADJ))
//            {
//                ucItem = usOsdCount - _MENU_ADVANCE_HDR_LD_ONOFF;
//                ucAmount = (_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ - _MENU_ADVANCE_HDR_LD_ONOFF + 1);
//            }
//        #endif
//            else if(usOsdCount == _MENU_ADVANCE_EDID_ADJUST)
//            {
//                ucItem = g_usAdjustValue;
//                ucAmount = (_D5_INPUT_PORT - _D0_INPUT_PORT + 1);
//            }
//        #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//            else if(usOsdCount == _MENU_ADVANCE_HDMI_VERSION_ADJUST)
//            {
//                ucItem = g_usAdjustValue;
//                usOsdCount = (_D5_INPUT_PORT-_D0_INPUT_PORT+1);
//            }
//        #endif
//            // Selection
//            if(bInSubsidiary == _OUTSUBSET)
//            {
//                OsdDispMainMenuItemSelection((ucItem % 4), _OSD_SELECT);
//            }
//            else if(bInSubsidiary == _INSUBSET)
//            {
//                OsdDispMainMenuItemSelection((ucItem % 4), _OSD_PRE_SELECT);
//            }
//
//            // indicate
//            if(bInSubsidiary == _OUTSUBSET)
//            {
//                OsdDispMainMenuItemIndication(ucItem, ucAmount, _OSD_SELECT);
//            }
//    }

//    //--------------------------------------------------
//    // Description    :
//    // Input Value    : None
//    // Output Value : None
//    //--------------------------------------------------
// void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue)
//{
//        BYTE ucDone = _FALSE;
//
//        g_usAdjustValue = usValue;
//
//        switch(usOsdState)
//        {
////            case _MENU_PICTURE_BACKLIGHT:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_PICTURE_BRIGHTNESS:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_PICTURE_CONTRAST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_PICTURE_SHARPNESS:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_PICTURE_BACKLIGHT_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_PICTURE_BRIGHTNESS_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_PICTURE_CONTRAST_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_PICTURE_SHARPNESS_ADJUST:
////                g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _SHARPNESS_MAX, _SHARPNESS_MIN, _OFF);
////                SET_OSD_SHARPNESS(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_DISPLAY_HPOS:
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_DISPLAY_VPOS:
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_DISPLAY_CLOCK:
////    #if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////    #else
////                {
////                    WORD usClockRangeMax = 0;
////                    WORD usClockRangeMin = 0;
////                    WORD usUserIHTotal = 0;
////
////                    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
////                    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
////                    usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
////
////                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
////                }
////    #endif
////
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_DISPLAY_PHASE:
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_DISPLAY_AUTO:
////    #if(_VGA_SUPPORT == _ON)
////                g_usAdjustValue = 0;
////                UserCommonAutoConfig();
////    #endif
////                break;
////
////            case _MENU_DISPLAY_HPOS_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////
////    #if(_VGA_SUPPORT == _ON)
////                if(SysSourceGetSourceType() == _SOURCE_VGA)
////                {
////                    SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
////                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_H_POSITION(), _SLIDER_0, _SELECT);
////                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                }
////                else
////    #endif
////                {
////                    SET_DIGITAL_H_POSITION(g_usAdjustValue);
////                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_H_POSITION(), _SLIDER_0, _SELECT);
////                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                }
////                break;
////
////            case _MENU_DISPLAY_VPOS_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////
////    #if(_VGA_SUPPORT == _ON)
////                if(SysSourceGetSourceType() == _SOURCE_VGA)
////                {
////                    SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
////                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_V_POSITION(), _SLIDER_0, _SELECT);
////                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                }
////                else
////    #endif
////                {
////                    SET_DIGITAL_V_POSITION(g_usAdjustValue);
////                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_V_POSITION(), _SLIDER_0, _SELECT);
////                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                }
////                break;
////
////    #if(_VGA_SUPPORT == _ON)
////            case _MENU_DISPLAY_CLOCK_ADJUST:
////    #if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_CLOCK(), _SLIDER_0, _SELECT);
////    #else
////                {
////                    WORD usClockRangeMax = 0;
////                    WORD usClockRangeMin = 0;
////                    WORD usUserIHTotal = 0;
////
////                    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
////                    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
////                    g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, usClockRangeMax, usClockRangeMin, _OFF);
////                    SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
////                    usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
////                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _SELECT);
////                }
////    #endif
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_DISPLAY_PHASE_ADJUST:
////                g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PHASE_MAX, _OSD_PHASE_MIN, _OFF);
////                SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_PHASE(), _SLIDER_0, _SELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////    #endif
////
////            case _MENU_DISPLAY_DISP_ROTATE_ADJUST:
////                SET_OSD_DISP_ROTATE(OsdDisplayDetOverRange(GET_OSD_DISP_ROTATE(), (_DISP_ROTATE_AMOUNT - 1), _DISP_ROTATE_0, _OFF));
////                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _SELECT, GET_OSD_DISP_ROTATE());
////                break;
////
////            case _MENU_DISPLAY_LATENCY_ADJUST:
////                SET_OSD_LATENCY(OsdDisplayDetOverRange(GET_OSD_LATENCY(), _LATENCY_AMOUNT, _LATENCY_L, _OFF));
////                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _SELECT, GET_OSD_LATENCY());
////                break;
////
////            case _MENU_COLOR_HUE:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_COLOR_SATURATION:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////    #if(_GAMMA_FUNCTION == _ON)
////            case _MENU_COLOR_GAMMA_ADJUST:
////
////                SET_OSD_GAMMA(OsdDisplayDetOverRange(GET_OSD_GAMMA(), _GAMMA_AMOUNT, _GAMMA_OFF, _OFF));
////                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA());
////
////                break;
////    #endif // End of #if(_GAMMA_FUNCTION == _ON)
////
////            case _MENU_COLOR_TEMPERATURE_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _CT_USER, _CT_9300, _OFF);
////                SET_COLOR_TEMP_TYPE(g_usAdjustValue);
////                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
////                break;
////
////            case _MENU_COLOR_EFFECT_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _COLOREFFECT_AMOUNT, _COLOREFFECT_STANDARD, _OFF);
////                SET_OSD_COLOR_EFFECT(g_usAdjustValue);
////
////                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
////                break;
////
////            case _MENU_COLOR_DEMO_ADJUST:
////                SET_OSD_HLWIN_TYPE(OsdDisplayDetOverRange(GET_OSD_HLWIN_TYPE(), _HL_WIN_AMOUNT, _HL_WIN_OFF, _OFF));
////                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _SELECT, GET_OSD_HLWIN_TYPE());
////                break;
////
////            case _MENU_COLOR_PCM_ADJUST:
////    #if(_OCC_SUPPORT == _ON)
////                SET_OSD_PCM_STATUS(OsdDisplayDetOverRange(GET_OSD_PCM_STATUS(), _PCM_OSD_AMOUNT, _PCM_OSD_SRGB, _OFF));
////                g_usAdjustValue = GET_OSD_PCM_STATUS();
////    #else
////                SET_OSD_PCM_STATUS(OsdDisplayDetOverRange(GET_OSD_PCM_STATUS(), _PCM_OSD_AMOUNT, _PCM_OSD_USER, _OFF));
////    #endif
////                break;
////
////            case _MENU_COLOR_HUE_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                SET_OSD_HUE(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER));
////                break;
////
////            case _MENU_COLOR_SATURATION_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                SET_OSD_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER));
////                break;
////
////            case _MENU_ADVANCE_ASPECT_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_ASPECT_RATIO_AMOUNT, _OSD_ASPECT_RATIO_FULL, _OFF);
////                break;
////
////            case _MENU_ADVANCE_OVER_SCAN_ADJUST:
////                SET_OSD_OVERSCAN_STATUS(OsdDisplayDetOverRange(GET_OSD_OVERSCAN_STATUS(), _ON, _OFF, _ON));
////                OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _SELECT, GET_OSD_OVERSCAN_STATUS());
////                break;
////
////
////            case _MENU_ADVANCE_ULTRA_VIVID_ADJUST:
////                SET_OSD_ULTRA_VIVID_STATUS(OsdDisplayDetOverRange(GET_OSD_ULTRA_VIVID_STATUS(), _ULTRA_VIVID_AMOUNT, _ULTRA_VIVID_OFF, _OFF));
////                OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _SELECT, GET_OSD_ULTRA_VIVID_STATUS());
////                break;
////
////            case _MENU_ADVANCE_DP_MST_ADJUST:
////
////                if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
////                {
////                    switch(GET_OSD_DP_MST())
////                    {
////                        case _MST_OFF:
////                            break;
////
////                        case _MST_D0:
////
////                            if(ucDone == _FALSE)
////                            {
////                                SET_OSD_DP_MST(_MST_OFF);
////                            }
////
////                            break;
////
////                        case _MST_D1:
////
////    #if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
////
////                            if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D0);
////                                ucDone = _TRUE;
////                            }
////    #endif
////                            if(ucDone == _FALSE)
////                            {
////                                SET_OSD_DP_MST(_MST_OFF);
////                            }
////
////                            break;
////
////                        case _MST_D6:
////
////    #if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
////
////                            if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D1);
////                                ucDone = _TRUE;
////                            }
////    #endif
////
////    #if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
////
////                            if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D0);
////                                ucDone = _TRUE;
////                            }
////    #endif
////                            if(ucDone == _FALSE)
////                            {
////                                SET_OSD_DP_MST(_MST_OFF);
////                            }
////
////                            break;
////
////                        default:
////                            break;
////                    }
////                }
////                else if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
////                {
////                    switch(GET_OSD_DP_MST())
////                    {
////                        case _MST_OFF:
////
////    #if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
////
////                            if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D0);
////                                ucDone = _TRUE;
////                            }
////    #endif
////
////    #if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
////                            if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D1);
////                                ucDone = _TRUE;
////                            }
////    #endif
////
////    #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&
////        ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
////
////                            if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D6);
////                                ucDone = _TRUE;
////                            }
////    #endif
////                            break;
////
////                        case _MST_D0:
////
////    #if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
////
////                            if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D1);
////                                ucDone = _TRUE;
////                            }
////    #endif
////
////    #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&
////        ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
////
////                            if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D6);
////                                ucDone = _TRUE;
////                            }
////    #endif
////                            if(ucDone == _FALSE)
////                            {
////                                SET_OSD_DP_MST(_MST_OFF);
////                            }
////
////                            break;
////
////                        case _MST_D1:
////
////    #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&
////        ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
////                            if((GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) && (ucDone == _FALSE))
////                            {
////                                SET_OSD_DP_MST(_MST_D6);
////                                ucDone = _TRUE;
////                            }
////    #endif
////                            if(ucDone == _FALSE)
////                            {
////                                SET_OSD_DP_MST(_MST_OFF);
////                            }
////
////                            break;
////
////                        case _MST_D6:
////                            break;
////
////                        default:
////                            break;
////                    }
////                }
////
////                OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _SELECT, GET_OSD_DP_MST());
////                break;
////
////            case _MENU_ADVANCE_DP_EDID_ADJUST:
////                UserCommonNVRamSetSystemData(_DP_EDID_SELECT, OsdDisplayDetOverRange(UserCommonNVRamGetSystemData(_DP_EDID_SELECT), _DP_EDID_4K2K_60HZ, _DP_EDID_1080P, _OFF));
////                OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
////                break;
////
////            case _MENU_ADVANCE_FREESYNC_ADJUST:
////                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREE_SYNC_STATUS());
////                break;
////
////            case _MENU_ADVANCE_CLONE_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_CLONE_MODE(), _OSD_CLONE_ON, _OSD_CLONE_OFF, _ON);
////                SET_OSD_CLONE_MODE(g_usAdjustValue);
////                break;
////
////            case _MENU_AUDIO_VOLUME:
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_AUDIO_VOLUME_ADJUST:
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF);
////                SET_OSD_VOLUME(g_usAdjustValue);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _SELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////
////            case _MENU_AUDIO_MUTE_ON_OFF:
////                SET_OSD_VOLUME_MUTE(OsdDisplayDetOverRange(GET_OSD_VOLUME_MUTE(), _ON, _OFF, _ON));
////                OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _SELECT, GET_OSD_VOLUME_MUTE());
////                break;
////
////            case _MENU_AUDIO_AUDIO_SOURCE_SELECT:
////                SET_OSD_AUDIO_SOURCE(OsdDisplayDetOverRange(GET_OSD_AUDIO_SOURCE(), _DIGITAL_AUDIO, _LINE_IN_AUDIO, _ON));
////                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _SELECT, GET_OSD_AUDIO_SOURCE());
////                break;
////
////            case _MENU_AUDIO_SOUND_MODE_SELECT:
////                break;
////
////            case _MENU_OTHER_MENU_TIME:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_OTHER_OSD_HPOS:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_OTHER_OSD_VPOS:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_OTHER_TRNASPARENCY:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_OTHER_MENU_TIME_ADJUST:
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OFF);
////                SET_OSD_TIME_OUT(g_usAdjustValue);
////                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_OTHER_OSD_HPOS_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
////                g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                SET_OSD_HPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER));
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_OTHER_OSD_VPOS_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
////                g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                SET_OSD_VPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER));
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_OTHER_LANGUAGE_ADJUST:
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_LANGUAGE(), _CHINESE_T, _ENGLISH, _OFF);
////
////                break;
////
////            case _MENU_OTHER_TRNASPARENCY_ADJUST:
////                g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OFF);
////                SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_OTHER_ROTATE_ADJUST:
////    #if(_OSD_ROTATE_CW180_SUPPORT == _ON)
////                g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_180, _OSD_ROTATE_DEGREE_0, _OFF);
////    #else
////                g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_270, _OSD_ROTATE_DEGREE_0, _OFF);
////    #endif
////                break;
////
////            case _MENU_COLOR_TEMP_USER_R:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_COLOR_TEMP_USER_G:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_COLOR_TEMP_USER_B:
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                break;
////
////            case _MENU_COLOR_TEMP_USER_ADJUST_R:
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
////                SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_COLOR_TEMP_USER_ADJUST_G:
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
////                SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_COLOR_TEMP_USER_ADJUST_B:
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
////                SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_COLOR_EFF_USER_R_HUE_ADJUST:
////            case _MENU_COLOR_EFF_USER_Y_HUE_ADJUST:
////            case _MENU_COLOR_EFF_USER_G_HUE_ADJUST:
////            case _MENU_COLOR_EFF_USER_C_HUE_ADJUST:
////            case _MENU_COLOR_EFF_USER_B_HUE_ADJUST:
////            case _MENU_COLOR_EFF_USER_M_HUE_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SIX_COLOR_HUE_MAX, _SIX_COLOR_HUE_MIN, _SIX_COLOR_HUE_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                SET_OSD_SIX_COLOR_HUE(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SIX_COLOR_HUE_MAX, _SIX_COLOR_HUE_MIN, _SIX_COLOR_HUE_CENTER));
////                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_COLOR_EFF_USER_R_SAT_ADJUST:
////            case _MENU_COLOR_EFF_USER_Y_SAT_ADJUST:
////            case _MENU_COLOR_EFF_USER_G_SAT_ADJUST:
////            case _MENU_COLOR_EFF_USER_C_SAT_ADJUST:
////            case _MENU_COLOR_EFF_USER_B_SAT_ADJUST:
////            case _MENU_COLOR_EFF_USER_M_SAT_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SIX_COLOR_SATURATION_MAX, _SIX_COLOR_SATURATION_MIN, _SIX_COLOR_SATURATION_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                SET_OSD_SIX_COLOR_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SIX_COLOR_SATURATION_MAX, _SIX_COLOR_SATURATION_MIN, _SIX_COLOR_SATURATION_CENTER));
////                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                break;
////
////            case _MENU_ADVANCE_OD_GAIN_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                SET_OSD_OD_GAIN(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER));
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////
////                break;
////
////    #if(_HDR10_SUPPORT == _ON)
////            case _MENU_ADVANCE_HDR_MODE_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _HDR10_MODE_FORCE_2084, _HDR10_MODE_OFF, _OFF);
////                SET_OSD_HDR_MODE(g_usAdjustValue);
////                OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _SELECT, GET_OSD_HDR_MODE());
////                break;
////
////            case _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST:
////                SET_OSD_DARK_ENHANCE_STATUS(OsdDisplayDetOverRange(GET_OSD_DARK_ENHANCE_STATUS(), _ON, _OFF, _ON));
////                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
////                break;
////
////            case _MENU_ADVANCE_HDR_CONTRAST:
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////            case _MENU_ADVANCE_HDR_CONTRAST_ADJUST:
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                SET_OSD_HDR_CONTRAST(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
////            case _MENU_ADVANCE_HDR_COLOR_ENHANCE:
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_COLOR_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////            case _MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LEVEL_H, _LEVEL_OFF, _OFF);
////                SET_OSD_HDR_COLOR_ENHANCE(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_COLOR_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), (g_usAdjustValue*100/_LEVEL_H), _SLIDER_0, _SELECT);
////                break;
////    #endif
////    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
////            case _MENU_ADVANCE_HDR_LIGHT_ENHANCE:
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_LIGHT_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                break;
////            case _MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST:
////                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _LEVEL_H, _LEVEL_OFF, _OFF);
////                SET_OSD_HDR_LIGHT_ENHANCE(g_usAdjustValue);
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_LIGHT_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), (g_usAdjustValue*100/_LEVEL_H), _SLIDER_0, _SELECT);
////                break;
////    #endif
////    #endif
////    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
////            case _MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST:
////                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, 100, 0, 50);
////                g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
////                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
////                SET_OSD_LD_ADJ(UserCommonAdjustPercentToRealValue(g_usAdjustValue, 100, 0, 50));
////                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSELECT_COLOR);
////
////                break;
////    #endif
//		case _MENU_HOTKEY_BACKLIGHT:	// 170308
//			g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
//			OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_0, _SELECT);
//			OsdPropShowNumber(ROW(2), COL(31), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_ORANGE, _CP_BG));
//			SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
//			break;
//            default:
//                break;
//        }
//    }
//
//    //--------------------------------------------------
//    // Description    :
//    // Input Value    : None
//    // Output Value : None
//    //--------------------------------------------------
//    WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _RIGHT_KEY_MESSAGE:
//                if(usValue >= usMax)
//                {
//                    if(bCycle == _ON)
//                    {
//                        return usMin;
//                    }
//                    else
//                    {
//                        return usMax;
//                    }
//                }
//                else
//                {
//                    usValue++;
//                }
//
//                break;
//
//            case _LEFT_KEY_MESSAGE:
//                if (usValue <= usMin)
//                {
//                    if(bCycle == _ON)
//                    {
//                        return usMax;
//                    }
//                    else
//                    {
//                        return usMin;
//                    }
//                }
//                else
//                {
//                    usValue--;
//                }
//                break;
//
//            default:
//                break;
//        }
//
//        return usValue;
//    }

//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  : None
//    // Output Value : None
//    //--------------------------------------------------
//    void OsdDispClearSliderAndNumber(void)
//    {
//        OsdWindowSliderDisable();
//        OsdFuncClearOsd(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_ucOsdWidth, 1);
//    }
//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispHotKeyOptionMenu(BYTE ucOption)
//    {
//        BYTE uctemp = 0;
//
//        OsdFuncCloseWindow(_OSD_WINDOW_ALL);
//        OsdFuncDisableOsd();
//        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//
//        OsdFuncApplyMap(WIDTH(36), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));
//
//    #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//        ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
//    #endif
//
//        OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
//        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//
//        // Adjust Color Palette
//        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
//
//        // Load Font & Icon
//        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
//
//        OsdFontVLCLoadFont(_FONT1_GLOBAL);
//        // OsdFontVLCLoadFont(_FONT2_ICON_MENU);
//
//        // Background window
//    #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
//           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//        {
//            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
//            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
//        }
//        else
//    #endif
//        {
//            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
//            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdHeight, _CP_LIGHTBLUE);
//        }
//
//        // title
//        switch(ucOption)
//        {
//            case _HOTKEY_DDCCI:
//                // icon
//                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DDCCI);
//
//                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
//                // string
//                OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_DDCCI, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
//
//
//                (GET_OSD_DDCCI_STATUS() == _ON) ? (uctemp = 1) : (uctemp = 2);
//
//                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//
//                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_ON);
//                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
//
//                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_OFF);
//                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
//                break;
//
//            case _HOTKEY_DP_D0_OPTION:
//            case _HOTKEY_DP_D1_OPTION:
//            case _HOTKEY_DP_D2_OPTION:
//            case _HOTKEY_DP_D6_OPTION:
//
//                g_usAdjustValue=ucOption;
//                // icon
//                if(ucOption == _HOTKEY_DP_D0_OPTION)
//                {
//                    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D0);
//                    (GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//                else if(ucOption == _HOTKEY_DP_D1_OPTION)
//                {
//                    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D1);
//                    (GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//                else if(ucOption == _HOTKEY_DP_D2_OPTION)
//                {
//                    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D2);
//                    (GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//                else if(ucOption == _HOTKEY_DP_D6_OPTION)
//                {
//                    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_D6);
//                    (GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//
//                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
//                // string
//                OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_DP_OPTION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
//                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_1_DOT_1);
//                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
//                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_1_DOT_2);
//                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
//                break;
//
//            default:
//                break;
//        }
//        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
//
//        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//
//        OsdFuncEnableOsd();
//    }
//
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption)
//    {
//        BYTE uctemp = 0;
//
//        switch(ucOption)
//        {
//            case _HOTKEY_DDCCI:
//                SET_OSD_DDCCI_STATUS(~(GET_OSD_DDCCI_STATUS()));
//                (GET_OSD_DDCCI_STATUS() == _ON) ? (uctemp = 1) : (uctemp = 2);
//                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
//                break;
//
//            case _HOTKEY_DP_D0_OPTION:
//            case _HOTKEY_DP_D1_OPTION:
//            case _HOTKEY_DP_D2_OPTION:
//            case _HOTKEY_DP_D6_OPTION:
//                if(ucOption == _HOTKEY_DP_D0_OPTION)
//                {
//                    SET_OSD_DP_D0_VERSION(~(GET_OSD_DP_D0_VERSION()));
//                    (GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//                else if(ucOption == _HOTKEY_DP_D1_OPTION)
//                {
//                    SET_OSD_DP_D1_VERSION(~(GET_OSD_DP_D1_VERSION()));
//                    (GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//                else if(ucOption == _HOTKEY_DP_D2_OPTION)
//                {
//                    SET_OSD_DP_D2_VERSION(~(GET_OSD_DP_D2_VERSION()));
//                    (GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//                else if(ucOption == _HOTKEY_DP_D6_OPTION)
//                {
//                    SET_OSD_DP_D6_VERSION(~(GET_OSD_DP_D6_VERSION()));
//                    (GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) ? (uctemp = 1) : (uctemp = 2);
//                }
//                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                break;
//
//            default:
//                break;
//        }
//
//        RTDNVRamSaveOSDData();
//    }
//
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuIcon(BYTE ucPort)
{
	BYTE ucCol = 5;

	if (GET_OSD_STATE() == _MENU_HOTKEY_SOURCE)
	{
		OsdFuncClearOsd(ROW(6), COL(13), WIDTH(47), HEIGHT(1));
		OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_SETUP, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

		// Left & Right Arrow
		OsdFontPut1Bit(ROW(3), COL(13), _iLEFT_00, COLOR(_CP_BLUE, _CP_BG));
		OsdFontPut1Bit(ROW(3) + 1, COL(13), _iLEFT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

		OsdFontPut1Bit(ROW(3), COL(62), _iRIGHT_00, COLOR(_CP_BLUE, _CP_BG));
		OsdFontPut1Bit(ROW(3) + 1, COL(62), _iRIGHT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

#if (_ENABLE_MENU_VGA == _ON)
		if (_OSD_INPUT_A0 <= ucPort && ucPort <= _OSD_INPUT_D3)
#else
		if ((_OSD_INPUT_D0 <= ucPort) && (ucPort <= _OSD_INPUT_D3))
#endif
		{
			// A0
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _A0_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_A0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// D0
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D0_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// // D1
			// OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D1_INPUT_TYPE);
			// OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
			// OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D1_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// D2
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D2_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D2_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// D3
			OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D3_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D3_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
		}
		else if ((ucPort > _OSD_INPUT_D3) && (ucPort <= _OSD_INPUT_D6))
		{
			// D3
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D3_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D3_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// D4
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D4_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D4_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// D5
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D5_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D5_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// D6
			OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D6_INPUT_TYPE);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D6_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
		}
		else
		{

			// auto
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_INPUT_AUTO);
			OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
			OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_AUTOSELECT_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

			// None
			OsdFuncClearOsd(ROW(2), COL(3 + (12 * 2)), WIDTH(32), HEIGHT(4));
		}
	}
	else
	{

		if ((ucPort >= _OSD_INPUT_D6) && (ucPort <= _OSD_INPUT_AUTO))
		{
			OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
		}
		else if ((ucPort >= _OSD_INPUT_A0) && (ucPort <= _OSD_INPUT_D3))
		{
			OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
		}
		else if ((ucPort >= _OSD_INPUT_D5) && (ucPort <= _OSD_INPUT_D6))
		{
			OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
		}
	}
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenu(void)
{
	if (SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
	{
		SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_AUTO);
	}
	// else if (GET_OSD_INPUT_PORT_OSD_ITEM() != _OSD_INPUT_AUTO)
	//{
	//	SET_OSD_INPUT_PORT_OSD_ITEM(SysRegionGetPortType(_DISPLAY_RGN_1P));
	// }
	// if (GET_OSD_INPUT_PORT_OSD_ITEM () == _OSD_INPUT_AUTO)
	{
		g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
	}
	// else // EnumSourceSearchPort �� EnumOSDInputPortDef ���� ���� �մϴ�.
	//{
	//	g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM() ;//
	// }
	SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
	OsdFuncDisableOsd();
	OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_SOURCE_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_SOURCE_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_HOTKEY_SOURCE_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

	OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
	OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

	// Adjust Color Palette
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

	// Load Font & Icon
	OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

	OsdFontVLCLoadFont(_FONT1_GLOBAL);

	// Background window
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdWidth, _CP_LIGHTBLUE);
	}
	else
#endif
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdHeight, _CP_LIGHTBLUE);
	}

	// title
	// icon
	// _MENU_INPUT
	OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INPUT);

	OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

	// highligh window
	OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
	OsdDispHotKeySourceMenuIcon(g_usBackupValue);

	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

	OsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuSwitch(BYTE ucPort)
{

#if (_ENABLE_MENU_VGA == _ON)
	if (GET_OSD_STATE() == _MENU_HOTKEY_SOURCE)
	{
		if (ucPort == _OSD_INPUT_AUTO)
		{
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (ucPort + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
		}
		else
		{
			ucPort -= _OSD_INPUT_A0;
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (ucPort + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
		}
	}
	else
	{
		if (!(ucPort == _OSD_INPUT_AUTO))
			ucPort -= 1;

		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(4 + ((ucPort % 4) * 10) - 2), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
	}
#else
	if (GET_OSD_STATE() == _MENU_HOTKEY_SOURCE)
	{
		if (ucPort == _OSD_INPUT_AUTO)
		{
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (ucPort + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
		}
		else
		{
			ucPort -= _OSD_INPUT_D0;
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (ucPort + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
		}
	}
	else
	{
		if (ucPort != _OSD_INPUT_A0)
			ucPort -= 1;

		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(4 + ((ucPort % 4) * 10) - 2), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
	}
#endif
}
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispPanelUniformityMsgSwitch(void)
//    {
//        BYTE uctemp = 0;
//        SET_OSD_PANEL_UNIFORMITY(~(GET_OSD_PANEL_UNIFORMITY()));
//        (GET_OSD_PANEL_UNIFORMITY() == _ON) ? (uctemp = 1) : (uctemp = 0);
//        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(18 + (9 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//    }

//
//
//    //--------------------------------------------------
//    // Description  : OSD information function
//    // Input Value  : None
//    // Output Value : None
//    //--------------------------------------------------
//    void OsdDispShowInformation(void)
//    {
//    #if(_FREESYNC_SUPPORT == _ON)
//        if(ScalerSyncGetFREESYNCEnable() == _TRUE)
//        {
//            ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
//        }
//    #endif
//
//        OsdPropPutString(ROW(14), COL(16), _PFONT_PAGE_1, OsdDisplayGetSourcePortString(), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
//
//    #if(_FREESYNC_SUPPORT == _ON)
//        SET_FREESYNC_OSD_ADDRESS(g_ucFontPointer1);
//    #endif
//
//        OsdPropPutString(ROW(14 + 1), COL(16), _PFONT_PAGE_1, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
//        OsdPropPutString(ROW(14 + 2), COL(16), _PFONT_PAGE_1, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
//
//    #if(_VGA_SUPPORT == _ON)
//        if(SysSourceGetSourceType() == _SOURCE_VGA)
//        {
//            OsdPropPutString(ROW(14 + 3), COL(16), _PFONT_PAGE_1, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
//            OsdPropShowNumber(ROW(14 + 3), COL(16 + 8), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, COLOR(_CP_BLUE, _CP_BG));
//        }
//    #endif
//
//    #if(_DIGITAL_PORT_SUPPORT == _ON)
//        if((SysSourceGetInputPort() == _D0_INPUT_PORT) ||
//           (SysSourceGetInputPort() == _D1_INPUT_PORT) ||
//           (SysSourceGetInputPort() == _D2_INPUT_PORT) ||
//           (SysSourceGetInputPort() == _D3_INPUT_PORT) ||
//           (SysSourceGetInputPort() == _D4_INPUT_PORT) ||
//           (SysSourceGetInputPort() == _D5_INPUT_PORT))
//        {
//            OsdPropPutString(ROW(14 + 3), COL(16), _PFONT_PAGE_1, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
//        }
//    #endif
//    #if(_FREESYNC_SUPPORT == _ON)
//        if(ScalerSyncGetFREESYNCEnable() == _TRUE)
//        {
//            OsdPropPutString(ROW(14 + 4), COL(16), _PFONT_PAGE_1, _STRING_FREESYNC_SUPPORT_V_RANGE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
//        }
//    #endif
//    }
//
#if ((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdRotateSwitch(void)
{
	BYTE ucTest = 0;

	g_ucFontPointer0 = _OSD_PAGE_0_START;
	g_ucFontPointer1 = _OSD_PAGE_1_START;
	g_ucFontPointer2 = _OSD_PAGE_2_START;

	if (ucTest == 1)
	{
		//        ScalerDDomainPatternGenAdjustColor(0, 0, 0);
		//        OsdDispDetOverRange(0, 0, 0, 0);

		//        RTDFactoryPanelUsedTimer();
		//        OsdFontPut2BitTable(0, 0, tOSD_iREALTEK, 0, 0, 0, 0);

		//        OsdWindowDrawingHighlight(0, 0, 0, 0, 0, 0, 0, 0);
		//        OsdFuncChangeIconColor1Bit(0, 0, 0, 0, 0);

		ScalerOsdDataPort(0);

		// #if(_DIGITAL_PORT_SUPPORT == _ON)
		//         ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort());
		// #endif
	}

	OsdFuncDisableOsd();

	SET_OSD_DOUBLE_SIZE(_ON);

	OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_BLUE_120, _CP_BG));

	// 20140304 Abel
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
	ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

	OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
	OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

	// Adjust Color Palette
	OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

	// Load Font & Icon
	OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

	OsdFontVLCLoadFont(_FONT1_GLOBAL);
	// OsdFontVLCLoadFont(_FONT2_ICON_MENU);
	OsdFontVLCLoadFont(_FOUR_CORNER);
	OsdFontVLCLoadFont(_MAIN_MENU_2BIT_ICON);

	// Background window
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
	if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
		(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
	{
		OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
	}
	else
#endif
	{
		// OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( g_ucOsdHeight/2), _CP_BLUE_120);
		// OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( g_ucOsdHeight/2+1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)), _CP_BLUE_120 );//_CP_LIGHTBLUE
		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(1), COL(1), WIDTH(g_ucOsdWidth - 2), HEIGHT((g_ucOsdHeight - 2)), _CP_BLUE_65);
		OsdFontPut1FuncTableForm(0, 0, _LEFT_CORNER_0, g_ucOsdWidth - 2, g_ucOsdHeight - 2, _CP_BLUE_65, _CP_BG, _QUADRANGLE_WINDOW_0);
		OsdFontPut1FuncHLine(1, 0, _WHITE_EDGE_1, g_ucOsdWidth, _CP_WHITE, _CP_BLUE_65);
		OsdFontPut1FuncHLine(24, 0, _WHITE_EDGE_1, g_ucOsdWidth, _CP_WHITE, _CP_BLUE_65);
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		// OsdFontPut1FuncTableForm(2, 54, _EDGE_LINE, 16, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
	}

	OsdFontPut2BitTable(ROW(_OSD_NUMBER_5_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_BIR_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_BLACK), COLOR2(_CP_YELLOW), COLOR3(_CP_WHITE));
	OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(4), COL(7), _PFONT_PAGE_0, _STRING_PICTURE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(_OSD_NUMBER_6_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_COLORTEMP_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_GREEN_66), COLOR2(_CP_GREEN_119), COLOR3(_CP_RED));
	OsdFontPut1FuncHLine(10, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(8), COL(7), _PFONT_PAGE_0, _STRING_COLOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(11), COL(2), tiOSD_MAIN_OSDSETTING_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLUE_65), COLOR3(_CP_LIGHTBLUE));
	OsdFontPut1FuncHLine(14, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(12), COL(7), _PFONT_PAGE_0, _STRING_ADVANCE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(15), COL(2), tiOSD_MAIN_MISC_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_GREEN_66), COLOR3(_CP_BLUE_65));
	OsdFontPut1FuncHLine(18, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(16), COL(7), _PFONT_PAGE_0, _STRING_SETUP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	OsdFontPut2BitTable(ROW(19), COL(2), tiOSD_MAIN_RESET_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLACK), COLOR3(_CP_GREEN_66));
	OsdFontPut1FuncHLine(22, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(20), COL(7), _PFONT_PAGE_0, _STRING_OTHER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

	// OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL + 36), _PFONT_PAGE_0, _STRING_NOW_RESOLUTION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	// OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL + 36), _PFONT_PAGE_0, _STRING_VERSION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	// OsdPropPutString(ROW(_OSD_NUMBER_13_ROW + 3), COL(_OSD_NUMBER_1_COL + 20), _PFONT_PAGE_0, _STRING_VERSION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

	ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
	COsdShowPageText(_MENU_OSDSETTINGS);

	OsdDispMainMenuItemSelection(_MENU_OSDSETTINGS - 1, _OSD_SELECT);
	SET_OSD_STATE(_MENU_OSDSETTINGS_ROTATE_ADJUST);
	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
	COsdShowChooseOSDSetText(_STRING_OSDSET_ROTATE);
	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ROTATE_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

	ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());

	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

	// Osd Enable
	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	OsdFuncEnableOsd();
}
#endif

#if (_ENABLE_VIDEO_WALL == _ON)
// H, V Number �� Display Number �ڵ� ���.
BYTE GetVideoWallDisplayNumber(void)
{
	BYTE returnVaule = 1;

	if (GET_OSD_VIDEO_WALL_H_NUM() == 0 || GET_OSD_VIDEO_WALL_V_NUM() == 0)
	{
		returnVaule = GET_OSD_VIDEO_WALL_H_NUM() + GET_OSD_VIDEO_WALL_V_NUM();
		if (returnVaule == 0)
			returnVaule = 1; // Min = 1
	}
	else
	{
		returnVaule = GET_OSD_VIDEO_WALL_H_NUM() * GET_OSD_VIDEO_WALL_V_NUM();
	}
	return returnVaule;
}

BYTE GetVideoWallStatus(void)
{
	return GET_OSD_VIDEO_WALL_STATUS();
}
BYTE GetVideoWallRS232ID(void)
{
	return GET_OSD_VIDEO_WALL_RS232ID();
}
#endif

//    //--------------------------------------------------
//    // Description : re-draw Advance Menu
//    // Input Value  : High: clean all & redraw ;  Low: Change selected color only
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispAdvanceMenuReDraw(bit bRedrawLevel)
//    {
//        SET_OSD_STATE(_MENU_ADVANCE_ITEM);
//        OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX() % 4), _OSD_SELECT);
//        OsdDispMainMenuItemIndication2(GET_OSD_ITEM_INDEX(), GET_OSD_STATE(), _OSD_SELECT);
//        if(bRedrawLevel == _HIGH)
//        {
//            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE);
//            OsdDispClearSliderAndNumber();
//            OsdDispClearSelectColor(_DOWN);
//            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//        }
//        OsdDispAdvanceItemSwitch(GET_OSD_ITEM_INDEX());
//    }
//
//    //--------------------------------------------------
//    // Description  : Check Advance Sub Item exist or not
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    bit OsdDispAdvanceItemCheck(BYTE ucIndex)
//    {
//            switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
//            {
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//                case _OSD_ADVANCE_ASPECT:
//                    break;
//    #endif
//    #if(_OVERSCAN_SUPPORT == _ON)
//                case _OSD_ADVANCE_OVERSCAN:
//                    break;
//    #endif
//    #if(_OD_SUPPORT == _ON)
//                case _OSD_ADVANCE_OVERDRIVE:
//                    break;
//    #endif
//                case _OSD_ADVANCE_DDCCI:
//                    break;
//
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//                case _OSD_ADVANCE_ULTRAVIVID:
//    #if(_HDR10_SUPPORT == _ON)
//                    if((UserCommonHDRGetHDR10Status() == _HDR10_ON) && (GET_OSD_HDR_SHARPNESS() == _ON))
//                        return _FALSE;
//    #endif
//                    break;
//    #endif
//    #if(_DCR_SUPPORT == _ON)
//                case _OSD_ADVANCE_DCR:
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//                    if(GET_OSD_LOCAL_DIMMING() == _ON)
//                    {
//                        return _FALSE;
//                    }
//    #endif
//                    break;
//    #endif
//    #if(_DP_SUPPORT == _ON)
//                case _OSD_ADVANCE_DPOPTION:
//                    break;
//    #if(_DP_MST_SUPPORT == _ON)
//                case _OSD_ADVANCE_DPMST:
//                    break;
//    #endif
//                case _OSD_ADVANCE_DP_RESOLUTION:
//                    break;
//                case _OSD_ADVANCE_CLONE:
//                    break;
//    #endif
//    #if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
//                case _OSD_ADVANCE_FREESYNC:
//                    break;
//    #endif
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                case _OSD_ADVANCE_TYPEC_MODE:
//                    break;
//    #endif
//    #if(_HDR10_SUPPORT == _ON)
//                case _OSD_ADVANCE_HDR:
//                    break;
//    #endif
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//                case _OSD_ADVANCE_LOCALDIMMING:
//                    break;
//    #endif
//    #if(_PIXEL_SHIFT_SUPPORT == _ON)
//                case _OSD_ADVANCE_PIXELSHIFT:
//                    break;
//    #endif
//    #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//                case _OSD_ADVANCE_HDMI_VERSIONS:
//                    break;
//    #endif
//    #if (_SDR_TO_HDR_SUPPORT == _ON)
//                case _OSD_ADVANCE_SDR_TO_HDR:
//    #if(_HDR10_SUPPORT == _ON)
//                    if((UserCommonHDRGetHDR10Status() == _HDR10_ON))
//                        return _FALSE;
//    #endif
//    #if(_FREESYNC_II_SUPPORT == _ON)
//                    if(UserCommonHDRGetFreesynIIStatus() == _ON)
//                    {
//                        return _FALSE;
//                    }
//    #endif
//
//                    break;
//    #endif
//
//
//                case _OSD_ADVANCE_NONE:
//                default:
//                    return _FALSE;
//                    break;
//            }
//            return _TRUE;
//    }
//    //--------------------------------------------------
//    // Description  :
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    bit OsdDispAdvanceItemCountbyKeyMessage(void)
//    {
//        BYTE ucBackup = GET_OSD_ITEM_INDEX();
//        do
//        {
//            if(GET_OSD_ITEM_INDEX() > _OSD_ADVANCE_ITEM_AMOUNT)
//                return _FALSE;
//
//            if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
//            {
//                if(GET_OSD_ITEM_INDEX() >= (_OSD_ADVANCE_ITEM_AMOUNT-1))
//                {
//                    SET_OSD_ITEM_INDEX(ucBackup);
//                    return _FALSE;
//                }
//
//                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()+1);
//            }
//            if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
//            {
//                if(GET_OSD_ITEM_INDEX() <= 0)
//                {
//                    SET_OSD_ITEM_INDEX(ucBackup);
//                    return _FALSE;
//                }
//
//                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
//
//            }
//        }while (OsdDispAdvanceItemCheck(GET_OSD_ITEM_INDEX()) == _FALSE) ;
//        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
//        {
//            if(((ucBackup % 4) == 3)||((GET_OSD_ITEM_INDEX() % 4) == 0))
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE);
//        }
//        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
//        {
//            if(((ucBackup % 4) == 0) || ((GET_OSD_ITEM_INDEX() % 4) == 3))
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE);
//
//        }
//
//        return _TRUE;
//
//    }
//    //--------------------------------------------------
//    // Description  : Get Advance Sub item Icon
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    BYTE OsdDispAdvanceIconGet(BYTE ucIndex)
//    {
//        if(ucIndex < _OSD_ADVANCE_ITEM_AMOUNT)
//        {
//            switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
//            {
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//                case _OSD_ADVANCE_ASPECT:
//                    return _ICON_ASPECT;
//                    break;
//    #endif
//    #if(_OVERSCAN_SUPPORT == _ON)
//                case _OSD_ADVANCE_OVERSCAN:
//                    return _ICON_OVER_SCAN;
//                    break;
//    #endif
//    #if(_OD_SUPPORT == _ON)
//                case _OSD_ADVANCE_OVERDRIVE:
//                    return _ICON_OVER_DRIVE;
//                    break;
//    #endif
//                case _OSD_ADVANCE_DDCCI:
//                    return _ICON_DDCCI;
//                    break;
//
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//                case _OSD_ADVANCE_ULTRAVIVID:
//                    return _ICON_ULTRAVIVID;
//                    break;
//    #endif
//    #if(_DCR_SUPPORT == _ON)
//                case _OSD_ADVANCE_DCR:
//                    return _ICON_DCR;
//                    break;
//    #endif
//    #if(_DP_SUPPORT == _ON)
//                case _OSD_ADVANCE_DPOPTION:
//                    return _ICON_DP_OPTION;
//                    break;
//    #if(_DP_MST_SUPPORT == _ON)
//                case _OSD_ADVANCE_DPMST:
//                    return _ICON_DP_MST;
//                    break;
//    #endif
//                case _OSD_ADVANCE_DP_RESOLUTION:
//                    return _ICON_RESOLUTION;
//                    break;
//                case _OSD_ADVANCE_CLONE:
//                    return _ICON_CLONE;
//                    break;
//    #endif
//    #if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
//                case _OSD_ADVANCE_FREESYNC:
//                    return _ICON_FREESYNC;
//                    break;
//    #endif
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                case _OSD_ADVANCE_TYPEC_MODE:
//                    return _ICON_TYPEC_MODE;
//                    break;
//    #endif
//    #if(_HDR10_SUPPORT == _ON)
//                case _OSD_ADVANCE_HDR:
//                    return _ICON_HDR;
//                    break;
//    #endif
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//                case _OSD_ADVANCE_LOCALDIMMING:
//                    return _ICON_LOCAL_DIMMING;
//                    break;
//    #endif
//    #if(_PIXEL_SHIFT_SUPPORT == _ON)
//                case _OSD_ADVANCE_PIXELSHIFT:
//                    return _ICON_PIXEL_SHIFT;
//                    break;
//    #endif
//    #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//                case _OSD_ADVANCE_HDMI_VERSIONS:
//                    return _ICON_HDMI_VERSIONS;
//                    break;
//    #endif
//    #if (_SDR_TO_HDR_SUPPORT == _ON)
//                case _OSD_ADVANCE_SDR_TO_HDR:
//                    return _ICON_SDR_TO_HDR;
//                    break;
//    #endif
//
//                case _OSD_ADVANCE_NONE:
//                default:
//                    break;
//            }
//        }
//        return _ICON_NONE;
//    }
//    //--------------------------------------------------
//    // Description  :Advane sub Item switcht
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispAdvanceItemSwitch(BYTE ucIndex)
//    {
//        switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
//        {
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//            case _OSD_ADVANCE_ASPECT:
//                OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _UNSELECT, GET_OSD_ASPECT_RATIO_TYPE());
//               if(GET_OSD_ASPECT_RATIO_TYPE() == _OSD_ASPECT_RATIO_ORIGIN)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
//                }
//                break;
//    #endif
//    #if(_OVERSCAN_SUPPORT == _ON)
//            case _OSD_ADVANCE_OVERSCAN:
//                OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _UNSELECT, GET_OSD_OVERSCAN_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    #endif
//    #if(_OD_SUPPORT == _ON)
//            case _OSD_ADVANCE_OVERDRIVE:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OD_ADJUST);
//                break;
//    #endif
//            case _OSD_ADVANCE_DDCCI:
//                OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _UNSELECT, GET_OSD_DDCCI_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//            case _OSD_ADVANCE_ULTRAVIVID:
//                OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, GET_OSD_ULTRA_VIVID_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ULTRA_VIVID);
//                break;
//    #endif
//    #if(_DCR_SUPPORT == _ON)
//            case _OSD_ADVANCE_DCR:
//                OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _UNSELECT, GET_OSD_DCR_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    #endif
//    #if(_DP_SUPPORT == _ON)
//            case _OSD_ADVANCE_DPOPTION:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
//                break;
//    #if(_DP_MST_SUPPORT == _ON)
//            case _OSD_ADVANCE_DPMST:
//                OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _UNSELECT, GET_OSD_DP_MST());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_MST);
//                break;
//    #endif
//            case _OSD_ADVANCE_DP_RESOLUTION:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                g_usAdjustValue=0;
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_EDID_PORT_0);
//                break;
//            case _OSD_ADVANCE_CLONE:
//                    OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
//                break;
//    #endif
//    #if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
//            case _OSD_ADVANCE_FREESYNC:
//                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREE_SYNC_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    #endif
//
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//            case _OSD_ADVANCE_TYPEC_MODE:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TYPEC_MODE);
//                break;
//    #endif
//    #if(_HDR10_SUPPORT == _ON)
//            case _OSD_ADVANCE_HDR:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_ADJUST);
//                break;
//    #endif
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//            case _OSD_ADVANCE_LOCALDIMMING:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LOCAL_DIMMING);
//                break;
//    #endif
//    #if(_PIXEL_SHIFT_SUPPORT == _ON)
//            case _OSD_ADVANCE_PIXELSHIFT:
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, _OFF);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    #endif
//    #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//            case _OSD_ADVANCE_HDMI_VERSIONS:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                g_usAdjustValue=0;
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_EDID_PORT_0);
//                break;
//    #endif
//    #if (_SDR_TO_HDR_SUPPORT == _ON)
//            case _OSD_ADVANCE_SDR_TO_HDR:
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_SDR_TO_HDR());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    #endif
//
//            case _OSD_ADVANCE_NONE:
//            default:
//                break;
//        }
//    }
//    //--------------------------------------------------
//    // Description  :Advance sub item select
//    // Input Value  :
//    // Output Value :
//    //--------------------------------------------------
//    void OsdDispAdvanceItemSelect(BYTE ucIndex)
//    {
//        switch(OSD_ADVANCE_ITEM_PRI[ucIndex])
//        {
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//            case _OSD_ADVANCE_ASPECT:
//                g_usBackupValue = GET_OSD_ASPECT_RATIO_TYPE();
//                SET_OSD_STATE(_MENU_ADVANCE_ASPECT_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE());
//                break;
//    #endif
//    #if(_OVERSCAN_SUPPORT == _ON)
//            case _OSD_ADVANCE_OVERSCAN:
//                g_usBackupValue = GET_OSD_OVERSCAN_STATUS();
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_SCAN_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _SELECT, GET_OSD_OVERSCAN_STATUS());
//                break;
//    #endif
//    #if(_OD_SUPPORT == _ON)
//            case _OSD_ADVANCE_OVERDRIVE:
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OD_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    #endif
//            case _OSD_ADVANCE_DDCCI:
//                g_usBackupValue = GET_OSD_DDCCI_STATUS();
//                SET_OSD_STATE(_MENU_ADVANCE_DDCCI_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
//                break;
//
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//            case _OSD_ADVANCE_ULTRAVIVID:
//                g_usBackupValue = GET_OSD_ULTRA_VIVID_STATUS();
//                SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _SELECT, GET_OSD_ULTRA_VIVID_STATUS());
//                break;
//    #endif
//    #if(_DCR_SUPPORT == _ON)
//            case _OSD_ADVANCE_DCR:
//                g_usBackupValue = GET_OSD_DCR_STATUS();
//                SET_OSD_STATE(_MENU_ADVANCE_DCR_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
//                break;
//    #endif
//    #if(_DP_SUPPORT == _ON)
//            case _OSD_ADVANCE_DPOPTION:
//    #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//    #elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//    #elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//    #elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//    #endif
//
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_OPTION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//    #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
//    #elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
//    #elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
//    #elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
//    #endif
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_1_DOT_X);
//
//                break;
//    #if(_DP_MST_SUPPORT == _ON)
//            case _OSD_ADVANCE_DPMST:
//                // when Auto Search is disable, MST can be selected
//                if((SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT))
//                {
//                    g_usBackupValue = GET_OSD_DP_MST();
//                    SET_OSD_STATE(_MENU_ADVANCE_DP_MST_ADJUST);
//                    OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _SELECT, GET_OSD_DP_MST());
//                }
//                else
//                {
//                    OsdDispOsdMessage(_OSD_DISP_MST_WARNING_MSG);
//                    SET_OSD_STATE(_MENU_NONE);
//                    ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
//                }
//                break;
//    #endif
//            case _OSD_ADVANCE_DP_RESOLUTION:
//                g_usAdjustValue=0;
//                SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT+g_usAdjustValue)))
//                {
//                    case _PORT_DP:
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_RESOLUTION);
//                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT+g_usAdjustValue));
//                        break;
//
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                    default:
//                        break;
//                }
//                break;
//            case _OSD_ADVANCE_CLONE:
//                SET_OSD_STATE(_MENU_ADVANCE_CLONE_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                g_usBackupValue = GET_OSD_CLONE_MODE();
//                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE());
//                break;
//    #endif
//    #if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
//            case _OSD_ADVANCE_FREESYNC:
//                SET_OSD_STATE(_MENU_ADVANCE_FREESYNC_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREE_SYNC_STATUS());
//                g_usBackupValue=GET_OSD_FREE_SYNC_STATUS();
//                break;
//    #endif
//
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//            case _OSD_ADVANCE_TYPEC_MODE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    #if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
//                g_usBackupValue = GET_OSD_D0_TYPEC_U3_MODE();
//    #elif(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
//                g_usBackupValue = GET_OSD_D1_TYPEC_U3_MODE();
//    #elif(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
//                g_usBackupValue = GET_OSD_D2_TYPEC_U3_MODE();
//    #elif(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
//                g_usBackupValue = GET_OSD_D6_TYPEC_U3_MODE();
//    #endif
//
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_OPTION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, g_usBackupValue);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TYPEC_MODE_U3_ONOFF);
//                break;
//    #endif
//
//    #if(_HDR10_SUPPORT == _ON)
//            case _OSD_ADVANCE_HDR:
//                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                {
//                    g_usBackupValue = _FROM_STATE_HDR;
//                    g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
//                    OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
//                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                    SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
//                }
//                else
//                {
//                    SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
//                    OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_MODE);
//                }
//                break;
//    #endif
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//            case _OSD_ADVANCE_LOCALDIMMING:
//                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                {
//                    g_usBackupValue = _FROM_STATE_LD;
//                    g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
//                    OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
//                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                    SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
//                }
//                else
//                {
//                    SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_LOCAL_DIMMING);
//                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                }
//                break;
//    #endif
//    #if(_PIXEL_SHIFT_SUPPORT == _ON)
//            case _OSD_ADVANCE_PIXELSHIFT:
//                SET_OSD_STATE(_MENU_ADVANCE_PIXEL_SHIFT_ADJUST);
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
//                break;
//    #endif
//    #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//             case _OSD_ADVANCE_HDMI_VERSIONS:
//                g_usAdjustValue=0;
//                SET_OSD_STATE(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT+g_usAdjustValue)))
//                {
//                    case _PORT_DP:
//                         break;
//
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_VERSIONS );
//                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
//                        break;
//
//                    default:
//                        break;
//                }
//                break;
//    #endif
//    #if (_SDR_TO_HDR_SUPPORT == _ON)
//            case _OSD_ADVANCE_SDR_TO_HDR:
//                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                {
//                    g_usBackupValue = _FROM_STATE_SDRTOHDR;
//                    g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
//                    OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
//                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                    SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
//                }
//                else
//                {
//                    SET_OSD_STATE(_MENU_ADVANCE_SDR_TO_HDR_ADJUST);
//                    OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX()% 4), _OSD_PRE_SELECT);
//                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_SDR_TO_HDR());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                    g_usBackupValue = GET_OSD_SDR_TO_HDR();
//                }
//                break;
//    #endif
//            case _OSD_ADVANCE_NONE:
//            default:
//                break;
//        }
//    }

// Eric_20180306_Delete : End ---------------------------------

#endif // #if(_OSD_TYPE == _REALTEK_2014_OSD)
