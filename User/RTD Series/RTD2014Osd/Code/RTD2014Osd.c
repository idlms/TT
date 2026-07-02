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
// ID Code      : RTD2014Osd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSD__

#include "UserCommonInclude.h"
#include "RL6449_Series_Common_RegCommonInclude.h"
#if(_OSD_TYPE == _REALTEK_2014_OSD)

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
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    _DVI_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
    _DVI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
    _DVI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
    _DVI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
    _DVI_D4,
#endif
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
    _DVI_D5,
#endif

    _HDMI = 0x10,
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
    _HDMI_D0,
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
    _HDMI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    _HDMI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    _HDMI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    _HDMI_D4,
#endif
#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    _HDMI_D5,
#endif
}EnumOsdSourceTypeTMDS;

typedef enum
{
    _DP = 0x0E,
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    _DP_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    _DP_D1,
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    _DP_D2,
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    _DP_D6,
#endif
} EnumOsdSourceTypeDP;


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructOsdInfo g_stOsdInfo;

WORD g_usAdjustValue;
WORD g_usBackupValue;
BYTE g_ucLogoTimerCounter;
bit g_bLogoOn = 0;
bit g_bLedToggle;	
bit g_bHPJackState;	
BYTE g_ucBackupColorTempType;	
BYTE g_ucBurnInCnt;



//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserOsdHandler(void);
BYTE GetHpdMode(void);	

void RTDOsdSystemFlowProc(void);
void RTDOsdEventMsgProc(void);
void MenuBacklightLeftRight(void);

void OsdDispOsdReset(void);
BYTE OsdDispJudgeSourceType(void);

void HotKeyContrastSelect(void);
void HotKeyBrightnessSelect(void);
void HotKeyVolumeSelect(void);
void HotKeyBacklightSelect(void);
void HotKeyMuteSelect(void);
//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#define TO_ENTER_INTO_SERVICE_CLERA_0_STATE 0
#define TO_ENTER_INTO_SERVICE_MENU_1_STATE 1
#define TO_ENTER_INTO_SERVICE_DOWN_2_STATE 2
#define TO_ENTER_INTO_SERVICE_DOWN_3_STATE 3
#define TO_ENTER_INTO_SERVICE_DOWN_4_STATE 4
#define TO_ENTER_INTO_SERVICE_UP_5_STATE 5
#define TO_ENTER_INTO_SERVICE_UP_6_STATE 6
#define TO_ENTER_INTO_SERVICE_UP_7_STATE 7
#define TO_ENTER_INTO_SERVICE_DOWN_8_STATE 8
#define TO_ENTER_INTO_SERVICE_UP_9_STATE 9
#define TO_ENTER_INTO_SERVICE_DOWN_10_STATE 10

BYTE ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;

bit IsServiceMenu(BYTE ui8KeyMask)
{
	bit bRetVal = _FALSE;
	if (GET_OSD_STATE() == _MENU_NONE)
		ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
	switch (ui8EnterIntoServiceMenuState)
	{
	case TO_ENTER_INTO_SERVICE_CLERA_0_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _MENU_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_MENU_1_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_MENU_1_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_2_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_2_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_3_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_3_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_4_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_4_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_5_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_5_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_6_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_6_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_7_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_7_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_8_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_8_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_9_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_9_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_10_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_10_STATE:
		// DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		if (ui8KeyMask == _SELECT_KEY_MESSAGE)
			bRetVal = _TRUE;
		ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	default:
		ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	}
	return bRetVal;
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

    OsdDispDisableOsd();
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

    g_bLogoOn = _ON;
}
#endif
//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserOsdHandler(void)
{
    RTDOsdSystemFlowProc();
    RTDOsdEventMsgProc();
}

BYTE GetHpdMode(void)	
{
	if(GET_OSD_HPD_MODE()==_HPD_MODE1)
		return 0;
	else if(GET_OSD_HPD_MODE()==_HPD_MODE2)
		return 1;
	else if(GET_OSD_HPD_MODE()==_HPD_MODE3)
		return 2;
	else if(GET_OSD_HPD_MODE()==_HPD_MODE4)
		return 3;
	else
		return 0;
}
//--------------------------------------------------
// Description  : OSD system flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdSystemFlowProc(void)	
{
    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            break;

        case _MODE_STATUS_INITIAL:
/*
            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREESYNC_OD_MEASURE == _ON)
                UserAdjustFREESYNCODMeasure();
#endif

#if(_ENABLE_SHOW_LOGO == _ON)		
                OsdDispShowLogo();
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
				printf("OsdDispShowLogo()\n\r");	
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
#else
				ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
#endif
            }
*/
			if (SysModeGetModeStateChange() == _TRUE)
			{
#if (_FREESYNC_OD_MEASURE == _ON)
				UserAdjustFREESYNCODMeasure();
#endif
	
#if (_ENABLE_SHOW_LOGO == _ON)
				if (GET_OSD_LOGO_ON())
				{
#if (_ENABLE_MENU_OLED == _ON)
					if (GetWaitingToRunOFFRS() == _OFF)
#endif
					{
#if (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
						SET_OSD_DOUBLE_SIZE(_ON);
						OsdDispShowLogo();
						DebugMessageOsd("3 _BACKLIGHT_ON", 0);
#if (_ENABLE_MENU_OLED == _ON)
						UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
						ScalerTimerActiveTimerEvent(SEC(7), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
						SET_OSD_DOUBLE_SIZE(_OFF);
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
						SET_OSD_DOUBLE_SIZE(_OFF);
						OsdDispShowMainLogo();
						DebugMessageOsd("4 _BACKLIGHT_ON", _CUSTOMER_TYPE);
#if (_ENABLE_MENU_OLED == _ON)
						UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
						//			ScalerTimerActiveTimerEvent(SEC(40), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
						//			ScalerTimerDelayXms(20000); 	// 20 sec Delay
						ScalerTimerDelayXms(4000); // 4 sec Delay
			
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
						ScalerTimerDelayXms(1000); // 1 sec Delay
			
						OsdDispShowLogo();
						DebugMessageOsd("5 _BACKLIGHT_ON", 0);
#if (_ENABLE_MENU_OLED == _ON)
						UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
			
						OsdDispShowLogoColor();
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
						OsdDispDisableOsd();
						ScalerTimerActiveTimerEvent(100, _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
			
						SET_OSD_DOUBLE_SIZE(_ON);
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
						SET_OSD_DOUBLE_SIZE(_ON);
						OsdDispShowLogo();
						DebugMessageOsd("6 _BACKLIGHT_ON", _CUSTOMER_TYPE);
#if (_ENABLE_MENU_OLED == _ON)
						UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
						ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
						SET_OSD_DOUBLE_SIZE(_OFF);
#elif (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)
						SET_OSD_DOUBLE_SIZE(_ON);
						OsdDispShowLogo();
						DebugMessageOsd("3 _BACKLIGHT_ON", 0);
#if (_ENABLE_MENU_OLED == _ON)
						UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
						ScalerTimerActiveTimerEvent(SEC(7), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
						SET_OSD_DOUBLE_SIZE(_ON);
#else //
			/*(_CUSTOMER_TYPE == _CUSTOMER_STANDARD)
						SET_OSD_DOUBLE_SIZE(_ON);
						OsdDispShowLogo();
						DebugMessageOsd("7 _BACKLIGHT_ON", _CUSTOMER_TYPE);
#if (_ENABLE_MENU_OLED == _ON)
						UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
						UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
						ScalerTimerActiveTimerEvent(SEC(7), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
						SET_OSD_DOUBLE_SIZE(_ON);
			*/
#endif // #if(_CUSTOMER_TYPE	== _CUSTOMER_THRUPUT)
						//UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
					} // logo end
				}
				else
					ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);

			if ((_PANEL_DH_WIDTH >= 3840) && (_PANEL_DV_HEIGHT >= 2160))
			{
				SET_OSD_DOUBLE_SIZE(_ON);
			}
			else
			{
				SET_OSD_DOUBLE_SIZE(_OFF);
			}
#else
				ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
#endif
			}
           break;

        case _MODE_STATUS_SEARCH:

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREEZE_SUPPORT == _ON)
                if(GET_OSD_FREEZE_STATUS() == _ON)
                {
                    SET_OSD_FREEZE_STATUS(_OFF);
                }
#endif
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);	
                }
            }

            break;

        case _MODE_STATUS_DISPLAY_SETTING:	
            break;

        case _MODE_STATUS_ACTIVE:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);	
                }
            }

            break;

        case _MODE_STATUS_NOSUPPORT:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSUPPORT_MSG);
                    UserInterfaceKeyPadLedControl(_LED_POWER_NOSUPPORT);	
                }
            }

            break;

        case _MODE_STATUS_NOSIGNAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE)
                {
                    ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                }
            }

            break;

        case _MODE_STATUS_POWER_SAVING:

            if(SysSourceGetCableDetect(SysSourceGetInputPort()) == _FALSE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if(GET_OSD_POWER_SAVING_SHOW_SOURCE() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_SOURCE(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
                }
                else if(GET_OSD_WAKE_UP_SWITCH_DDCCI_PORT() == _TRUE)
                {
                    SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG);
                }
				else if (GET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE() == _TRUE)
				{
					SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(_FALSE);

					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_DISPLAY_MODE_MENU_MSG);
				}
#if(_DP_SUPPORT == _ON)
                else if(GET_OSD_POWER_SAVING_SHOW_DP_OPTION() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_FALSE);
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_DP_VERSIOM_MSG);
                }
#endif
#if(_DP_DEBUG_MSG == _ON)
                else if(GET_OSD_POWER_SAVING_SHOW_DP_INFO() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DP_INFO(_FALSE);

                    OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                }
#endif
            }

            break;

        case _MODE_STATUS_FACTORY:

            break;

        default:

            break;
    }

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
    // Check embedded DP switch status
    UserCommonAdjustEmbeddedDpSwitch();
#endif

    if(GET_KEYMESSAGE() < _KEY_AMOUNT)
    {
        // hot key
        if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) ||
           (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) ||
           (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
           (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
        {
			if((GET_OSD_STATE() != _MENU_NONE) &&
            	((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) 
            	||((GET_KEYMESSAGE() == _VOL_P_KEY_MESSAGE) || (GET_KEYMESSAGE() == _VOL_M_KEY_MESSAGE)) 	// Volume Repeat Key Enable
				||((GET_KEYMESSAGE() == _UP_KEY_MESSAGE) || (GET_KEYMESSAGE() == _DOWN_KEY_MESSAGE))	// OSD KEY UP/DOWN Repeat Disable
				||((GET_KEYMESSAGE() == _IR_UP_KEY_MESSAGE) || (GET_KEYMESSAGE() == _IR_DOWN_KEY_MESSAGE)))		// IR KEY UP/DOWN Repeat Enable	
            {
                SET_KEYREPEATENABLE();
            }

			if(GET_KEYMESSAGE() == _IR_UP_KEY_MESSAGE)	// IR KEY UP/DOWN Convert OSD KEY
				SET_KEYMESSAGE(_UP_KEY_MESSAGE);
			if(GET_KEYMESSAGE() == _IR_DOWN_KEY_MESSAGE)
				SET_KEYMESSAGE(_DOWN_KEY_MESSAGE);
        }

		if (IsServiceMenu(GET_KEYMESSAGE()))
			{
				SET_OSD_SERVICE(_ON);
				OsdDispDisableOsd();
				SET_OSD_STATE(_MENU_SERVICE1);
				OsdDispMainMenu();
				return;
			}

		if (GET_OSD_LCD_TEST_STATUS() == _ON)
		{
			// DebugMessageSystem("GET_OSD_LCD_TEST_MODE",GET_OSD_LCD_TEST_MODE());
			if (GET_OSD_LCD_TEST_MODE() < 5)
			{
				SET_OSD_LCD_TEST_MODE(GET_OSD_LCD_TEST_MODE() + 1);
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_LCD_TEST);
				LCDtest_ShowBurninPicture(GET_OSD_LCD_TEST_MODE());
			}
			else
			{
				SET_OSD_LCD_TEST_MODE(0);
				SET_OSD_LCD_TEST_STATUS(_OFF);
				ScalerDDomainBackgroundEnable(_DISABLE);
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_LCD_TEST);
			}
			return;
		}

        if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
        {
            //RTDFactoryMenuOperation();
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
        }
        else
        {
#if(_FREEZE_SUPPORT == _ON)
#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG) == _TRUE)
            {
                return;
            }
#else
            if(GET_FREEZE_DISABLE_MSG_STATE() == _ON)
            {
                return;
            }
#endif
#endif
            // back up previous OSD State
            SET_OSD_STATE_PREVIOUS(GET_OSD_STATE());

#if(_FREEZE_SUPPORT == _ON)
            if(GET_OSD_FREEZE_STATUS() == _ON) // Confirm whether disable the freeze status
            {
                if(OsdFuncCheckFreezeDisable() == _TRUE)
                {
                    return;
                }
            }
#endif
			if (!GET_OSD_KEYLOCK())	
			{	
				// /OsdDispHotKeyProcess(GET_KEYMESSAGE());	
				//OsdFactoryEnterKeyProcess(GET_KEYMESSAGE());	
				
	            //(*OperationTable[GET_OSD_STATE()])();	
				if(GET_KEYMESSAGE() < _NAVI_KEY_AMOUNT)
					(*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();	//  OperationTable

				if((GET_OSD_IN_FACTORY_MENU_STATUS() == _FALSE)&&
					(GET_OSD_STATE() != _MENU_HOTKEY_VOLUME) && 
					(GET_OSD_STATE() != _MENU_HOTKEY_BACKLIGHT) && 
					(GET_OSD_STATE() != _MENU_HOTKEY_CONTRAST) && 
					(GET_OSD_STATE() != _MENU_HOTKEY_BRIGHTNESS) && 
					(GET_OSD_STATE() != _MENU_HOTKEY_MUTE) &&
					(GET_OSD_STATE() != _MENU_HOTKEY_DISPLAY_MODE) &&
					(GET_OSD_STATE() != _MENU_HOTKEY_PIP_SWAP) &&
					(GET_OSD_STATE() != _MENU_DIALOG_MESSAGE ) &&		
					(GET_OSD_STATE() != _MENU_HOTKEY_BLK_ONOFF))	
				{
					//if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)		
					{
						if(GET_OSD_TIME_OUT() < _OSD_TIMEOUT_MIN)
						{
							ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
						}
						else
						{
							if((GET_OSD_STATE() >= _MENU_NONE)&&(GET_OSD_STATE() <= _MENU_INFO_SERIAL_NUM))	// Main Menu + Source Menu Timeout 
							ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);	
						}
					}
				}
			}
			
/*
            if((GET_OSD_STATE() >= _MENU_NONE) &&
                (GET_OSD_STATE() < _MENU_END) &&
                ((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)))
            {
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            else//(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
            }

            if(GET_OSD_IN_FACTORY_MENU_STATUS())
            {
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            }
*/
        }
    }

	if(!ScalerOsdGetOsdEnable())
	{
		if(GET_OSD_POWER_SAVING_SHOW_MENU()==_TRUE)
		{
			SET_OSD_POWER_SAVING_SHOW_MENU(_FALSE); // Reactive Power Saving Message flag
			printf("Reactive Power Save Message\n\r");
			ScalerTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
		}
		
	}
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdEventMsgProc(void)
{
	if(GET_OSD_BURNIN_MODE()==_ON)	// Disable Show Event
	{
		if((GET_OSD_EVENT_MESSAGE()>=_OSDEVENT_SHOW_NOSIGNAL_MSG)&&(GET_OSD_EVENT_MESSAGE()<=_OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG))  
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
			
	}
		
    switch(GET_OSD_EVENT_MESSAGE())
    {
        case _OSDEVENT_SHOW_NOSIGNAL_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            if (GET_OSD_POWERSAVE_TIME() != _POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOCABLE_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOCABLE_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            if (GET_OSD_POWERSAVE_TIME() != _POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOSUPPORT_MSG:

            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            OsdDispOsdMessage(_OSD_DISP_NOSUPPORT_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
			if (GET_OSD_POWERSAVE_TIME() != _POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG:
            OsdDispOsdMessage(_OSD_DISP_FAIL_SAFE_MODE_MSG);
            break;

        case _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
            OsdFuncSetOsdItemFlag();
            g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();

			#if(_ENABLE_MENU_VGA != _ON)				
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	// When Wakeup Signal
					if(g_usBackupValue >= _OSD_INPUT_A0)g_usBackupValue -= 1; 
				#else
					if(g_usBackupValue >= _OSD_INPUT_D0)g_usBackupValue -= 2; 
				#endif
			#else
				if(g_usBackupValue >= _OSD_INPUT_A0)g_usBackupValue -= 1; 
			#endif	
			printf("_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG\n\r");	
			
			SET_OSD_ITEM_INDEX(g_usBackupValue);
			OsdDispHotKeySourceMenu();

            //ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);	
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            break;
		case _OSDEVENT_SHOW_DISPLAY_MODE_MENU_MSG: // wake up show display mode
			ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
			ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
			ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

			OsdDispDisableOsd();
			SET_OSD_STATE(_MENU_INFO);
			OsdFuncSetOsdItemFlag();
			OsdDispMainMenu();
			// OsdSubMenuPageDraw(_MENU_PICTURE);
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

			if (GET_OSD_POWERSAVE_TIME() != _POWER_SAVE_OFF)
				ScalerTimerReactiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);

			DebugMessageOsd("11 _BACKLIGHT_ON", 0);
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

			break;

        case _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG:

            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            SET_OSD_STATE(_MENU_HOTKEY_DDCCI);

            ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

            break;

        case _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG:		
			if((GET_OSD_POWERSAVE_TIME() != _POWER_SAVE_OFF) && (( GET_OSD_STATE() == _MENU_NONE )||( GET_OSD_STATE() == _MENU_DIALOG_MESSAGE)))
			{
				OsdDispDisableOsd();
	            OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);
#if (_ENABLE_MENU_OLED == _ON)
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
#else				
	            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
				ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
#endif
			}
            break;

        case _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG:
#if (_ENABLE_MENU_OLED == _ON)
			if ((GET_OSD_OLED_OFFRS_STATUS() == _OFFRS_END_RUN) && GET_WAIT_TO_RUN_OFFRS())
			{
				sbPowerSaveOffRS = _TRUE;
				_bPowerOnOffRS = _TRUE;
				OsdDispDisableOsd();
				UserInterfaceOLEDSequenceTimes();
				OsdDispOsdMessage(_OSD_DISP_OFF_RS_30SEC_MSG);
				ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_POWER_SAVING);
				//DebugMessageLee("T:g_ulRemainingTimeMs", g_ulRemainingTimeMs);
			}
			else if (GET_OSD_OLED_OFFRS_STATUS() == _OFFRS_AUTO)
			{
				if (GET_WAIT_TO_RUN_OFFRS())
				{
					OsdDispDisableOsd();
					OsdDispOsdMessage(_OSD_DISP_OFF_RS_PWR_SUPPLY_MSG);
					DebugMessageOsd("T:_OSD_DISP_OFF_RS_5MIN_MSG", GetWaitingToRunOFFRS());
					ScalerTimerActiveTimerEvent(SEC(10), _USER_TIMER_EVENT_OSD_POWER_SAVING);
				}
				else
					SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
			}
			else
				SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
#else
			OsdDispDisableOsd();	
			SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
#endif

            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_DO_AUTO_CONFIG_MSG:
#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif
            OsdDispAutoConfigProc();
            break;
#endif

        case _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG:

#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(UserInterfaceGetFirstAutoConfigStatus() == _TRUE)
                {
                    OsdDispAutoConfigProc();
                }
            }
#endif

            if(GET_OSD_STATE() == _MENU_NONE)
            {
				//if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING))	
				//	ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
				
                OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
				//ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
				ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);	
            }
            break;

        case _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG:
            UserCommonNVRamSaveSystemData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG:
            UserCommonNVRamSaveModeUserData();
            break;
#endif
        case _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG:
            RTDNVRamSaveOSDData();
			RTDNVRamSaveOsdServiceData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG:
            if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
            }
            else
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            break;
#endif

        case _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG:
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _OSDEVENT_SAVE_NVRAM_BRICON_MSG:
            RTDNVRamSaveBriCon(SysSourceGetSourceType());
            break;

        case _OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG:
            RTDNVRamSaveSixColorData();
            break;

#if(_DP_SUPPORT == _ON)
        case _OSDEVENT_DP_VERSIOM_MSG:
            SET_OSD_STATE(_MENU_HOTKEY_DP_OPTION);

            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            break;
#endif

			
        default:
            break;
    }

    SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}

WORD code tBURN_IN_10BIT_PATTERN_TABLE[][3] =
{
    {1023,  	0,  	0},	//0
	{0,		 1023, 		0},	//1
	{0,  		0,   1023}, //2
	{1023,   1023, 		0}, //3
	{1023,      0,   1023}, //4
	{0,      1023,   1023}, //5
	{1023,   1023,   1023}, //6
};

void BurnInModeProcess(void)	
{
	static BYTE fgOneTimeAction = _FALSE;
	
	if(GET_OSD_BURNIN_MODE()==_ON)	
	{
		g_ucBurnInCnt++;
		if(g_ucBurnInCnt > 6)
			g_ucBurnInCnt = 0;
		
		//ScalerDDomainPatternGenAdjustColor(255, 255, 255);
		//ScalerDDomainPatternGenAdjustColor10bit(1023, 1023, 1023);
		ScalerDDomainPatternGenAdjustColor10bit(tBURN_IN_10BIT_PATTERN_TABLE[g_ucBurnInCnt][0],tBURN_IN_10BIT_PATTERN_TABLE[g_ucBurnInCnt][1],tBURN_IN_10BIT_PATTERN_TABLE[g_ucBurnInCnt][2]);
        ScalerDDomainPatternGenEnable(_ENABLE);
        ScalerDDomainBackgroundEnable(_DISABLE);

		//printf("BurnIn Process On \n\r");
				
		fgOneTimeAction = _TRUE;
	}
	else
	{
		if(fgOneTimeAction == _TRUE )
		{
			fgOneTimeAction = _FALSE; 

			ScalerDDomainPatternGenEnable(_DISABLE);	
	
			//printf("BurnIn Process Off \n\r");
		}
		
	}
}
void BurnInModeOff(void)	
{
	SET_OSD_BURNIN_MODE(_OFF);
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
}


#if(_DISTECK_UART_SUPPORT==_ON)	
extern void SysUartSetTxCommand(BYTE ucTxCmd, BYTE ucTxStatus, BYTE ucTxData);

extern BYTE g_ucUartRxBuf[_UART_RXBUF_LENGTH];
extern BYTE g_ucUartTxBuf[_UART_TXBUF_LENGTH];

BYTE GetUartDataToInputSource(BYTE ucUartData)	
{
	BYTE ucConvertData;
	
	switch(ucUartData)
	{
		case 0x01:	// D0:DP2
			ucConvertData = _OSD_INPUT_D0;
			break;
		case 0x02:	// D1:DP1
			ucConvertData = _OSD_INPUT_D1;
			break;
		case 0x03:	// D2:HDMI2
			ucConvertData = _OSD_INPUT_D2;
			break;
		case 0x04:	// D3:HDMI1
			ucConvertData = _OSD_INPUT_D3;
			break;
	}
	return ucConvertData;
	
}
BYTE GetInputSourceToUartData(BYTE ucInputPort)
{
	BYTE ucConvertData;
	
	switch(ucInputPort)
	{
		case _OSD_INPUT_D0:	// D0:DP2
			ucConvertData = 0x01;
			break;
		case _OSD_INPUT_D1:	// D1:DP1
			ucConvertData = 0x02;
			break;
		case _OSD_INPUT_D2:	// D2:HDMI2
			ucConvertData = 0x03;
			break;
		case _OSD_INPUT_D3:	// D3:HDMI1
			ucConvertData = 0x04;
			break;
	}
	return ucConvertData;
	
}
extern BYTE g_ucKeyStateSkip;




void RTDOsdUartMsgProc(BYTE ucUartCmd, BYTE ucUartData)	
{
	BYTE ucUartCmdAction = _FALSE;
	BYTE ucConvertData;

	switch (ucUartCmd)
	{
		
	case _UART_CMD2_POWER:
		if ((ucUartData == 0x00) && (SysPowerGetPowerStatus() != _POWER_STATUS_OFF))
		{
			SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
		}
		else if ((ucUartData == 0x01) && (SysPowerGetPowerStatus() == _POWER_STATUS_OFF))
			SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
		else if (ucUartData == 0xff)
		{
			if (SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
				SysUartSetTxCommand(_UART_CMD2_POWER, _SUCCESS, 0x00); // OFF
			else
				SysUartSetTxCommand(_UART_CMD2_POWER, _SUCCESS, 0x01); // ON
		}
		break;

	case _UART_CMD2_DISPLAYMODE:
		break;
	
	case _UART_CMD2_P1_INPUT_SEL:
		if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_P1_INPUT_SEL, _SUCCESS, GetInputSourceToUartData(GET_OSD_INPUT_PORT_OSD_ITEM())); // OFF
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_FORCE_POW_SAV_STATUS(_FALSE);

			ucConvertData = GetUartDataToInputSource(ucUartData); // matching protocol

			g_usAdjustValue = ucConvertData;
			DirectSourceSelect();	
		}
		break;
	
	case _UART_CMD2_P2_INPUT_SEL:
		break;
	case _UART_CMD2_P3_INPUT_SEL:
		break;
	case _UART_CMD2_P4_INPUT_SEL:
		break;

	case _UART_CMD2_ASPECT:
		if (ucUartData == 0x00)
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_16_BY_9);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_4_BY_3);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_5_BY_4);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
		{
			/*
			if (_PANEL_IDX == _PANEL_SAMSUNG_LTI650FN01) // original ?? ??? ???.
			{
				SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
				ucUartCmdAction = _SUCCESS;
			}
			else
			*/
			{
				SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_ORIGIN);
				ucUartCmdAction = _SUCCESS;
			}
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _SUCCESS, GET_OSD_ASPECT_RATIO_TYPE()); // OFF
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;
	case _UART_CMD2_BACKLIGHT:
		if (ucUartData == 0xff)
		{
			ucUartData = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			SysUartSetTxCommand(_UART_CMD2_BACKLIGHT, _SUCCESS, ucUartData); // OFF
		}
		else
		{
			SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(ucUartData, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
			UserAdjustBacklight(GET_OSD_BACKLIGHT());
			//RTDNVRamSaveOSDData();
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;
	case _UART_CMD2_CONTRAST:
		if (ucUartData == 0xff)
		{
			ucUartData = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
			SysUartSetTxCommand(_UART_CMD2_CONTRAST, _SUCCESS, ucUartData); // OFF
		}
		else
		{

			SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(ucUartData, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
			UserAdjustContrast(GET_OSD_CONTRAST());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
		}
		break;
	case _UART_CMD2_BRIGHTNESS:
		if (ucUartData == 0xff)
		{
			ucUartData = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
			SysUartSetTxCommand(_UART_CMD2_BRIGHTNESS, _SUCCESS, ucUartData); // OFF
		}
		else
		{
			SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(ucUartData, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
			UserAdjustBrightness(GET_OSD_BRIGHTNESS());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
		}
		break;
	case _UART_CMD2_SHARPNESS:
		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_SHARPNESS, _SUCCESS, GET_OSD_SHARPNESS());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_SHARPNESS(ucUartData);
			UserCommonAdjustSharpness(SysSourceGetInputPort());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;
	case _UART_CMD2_GAMMA:
		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_GAMMA, _SUCCESS, GET_OSD_GAMMA());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_GAMMA(ucUartData);
#if(_GAMMA_FUNCTION == _ON)
			ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
			UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
			if(GET_OSD_GAMMA() != _GAMMA_OFF)
			{
				UserAdjustGamma(GET_OSD_GAMMA());
				ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
				UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
			}
	#if(((_OGC_SUPPORT == _ON) || (_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)) && (_CONTRAST_SUPPORT == _ON))
			else
			{
				RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
				ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
				UserAdjustContrast(GET_OSD_CONTRAST());
			}
	#endif
#endif			
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

		}
		break;
	case _UART_CMD2_TEMP:
		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_TEMP, _SUCCESS, GET_COLOR_TEMP_TYPE());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_COLOR_TEMP_TYPE(ucUartData);
			RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
#if(_CONTRAST_SUPPORT == _ON)
   			UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;
	case _UART_CMD2_COLOR_EFFECT:
		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_COLOR_EFFECT, _SUCCESS, GET_OSD_COLOR_EFFECT());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_COLOR_EFFECT(ucUartData);
		#if(_HDR10_SUPPORT == _ON)
			if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
			{
				UserCommonHDRAdjustHDR10ColorEffect();
			}
			else
		#endif
			{
		#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
				UserAdjustColorEffectMode();
		#endif
		#if (_CONTRAST_SUPPORT == _ON)
				UserAdjustContrast(GET_OSD_CONTRAST());
		#endif
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			RTDEepromSaveBriCon(SysSourceGetSourceType());
			
		}
		break;

	case _UART_CMD2_AUDIO_SELSEL:

		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			ucUartCmdAction = _SUCCESS;
		}

		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_AUDIO_SELSEL, _SUCCESS, GET_OSD_AUDIO_SOURCE());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_AUDIO_SOURCE(ucUartData);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;

	case _UART_CMD2_SCREEN_MUTE:
		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_SCREEN_MUTE, _SUCCESS, GET_OSD_SCREEN_MUTE());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_SCREEN_MUTE(ucUartData);
			if (ucUartData == 0x01)
			{
				//					UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
				ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
				//					ScalerDisplayVboForceVideoOutput(_DISABLE);
			}
			else
			{
				//					UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
				ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);
				//					ScalerDisplayVboForceVideoOutput(_ENABLE);
			}
		}
		break;

	case _UART_CMD2_AUDIO_MUTE:
		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_AUDIO_MUTE, _SUCCESS, GET_OSD_VOLUME_MUTE());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_VOLUME_MUTE(ucUartData);
#if (_AUDIO_SUPPORT == _ON)
			UserAdjustAudioMuteSwitch();
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;

	case _UART_CMD2_AUDIO_VOL:
		if (ucUartData == 0xff)
		{
			ucUartData = GET_OSD_VOLUME();
			SysUartSetTxCommand(_UART_CMD2_AUDIO_VOL, _SUCCESS, ucUartData);
		}
		else
		{
			SET_OSD_VOLUME_MUTE(0);
			SET_OSD_VOLUME(ucUartData);
#if (_AUDIO_SUPPORT == _ON)
			UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;

	case _UART_CMD2_FAST_SWAP:
		break;
	case _UART_CMD2_PIP_TRANSPARENCY:
		break;
	case _UART_CMD2_PIP_SIZE:
		break;

	case _UART_CMD2_DP_FORMAT:
		if (ucUartData == 0x00 || ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_DP_FORMAT, _SUCCESS, GET_OSD_DP_D0_VERSION());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			if (ucUartData == 0x00)
			{
				SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_1);
				SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_1);
			}
			else
			{
				SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_2);
				SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_2);
			}
			if ((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && ((GET_OSD_DP_MST() == _MST_D0) || (GET_OSD_DP_MST() == _MST_D1)))
			{
				SET_OSD_DP_MST(_MST_OFF);
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
			ScalerDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
		}
		break;
	case _UART_CMD2_DP_MST:
		if (ucUartData == 0x00 || ucUartData == 0x01 || ucUartData == 0x02)
		{
			if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
			{
				OsdDispOsdMessage(_OSD_DISP_MST_WARNING_MSG);
				ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
			}
			else
			{
				if (SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT)
				{
					if (ucUartData != 0x00)
						SET_OSD_CLONE_MODE(_OFF);
					ucUartCmdAction = _SUCCESS;
				}
			}
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_DP_MST, _SUCCESS, GET_OSD_DP_MST());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_DP_MST(ucUartData);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if (_DP_MST_SUPPORT == _ON)
			ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
		}
		break;
	case _UART_CMD2_DP_CLONE:
		if (ucUartData == 0x00 || ucUartData == 0x01)
		{
			if (ucUartData == 0x01)
				SET_OSD_DP_MST(_MST_OFF);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_DP_CLONE, _SUCCESS, GET_OSD_CLONE_MODE());
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_CLONE_MODE(ucUartData);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;

	default:
		break;
	}
}


void RTDOsdUartMsgProc_2(BYTE ucUartCmd, BYTE ucUartData)	
{
	BYTE ucUartCmdAction = _FALSE;
	switch (ucUartCmd)
	{
	case _UART_CMD2_P1_ASPECT:
	{
		if (ucUartData == 0x00)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x02)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_P1_ASPECT, _SUCCESS, GET_OSD_ASPECT_RATIO_TYPE());  // OFF
		}
		if (ucUartCmdAction == _SUCCESS)
		{

			SET_OSD_ASPECT_RATIO_TYPE(ucUartData);
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
	}
	break;

	case _UART_CMD2_P2_ASPECT:
		break;
	case _UART_CMD2_P3_ASPECT:
		break;
	case _UART_CMD2_P4_ASPECT:
		break;

	default:
		break;
	}
}

#endif //#if(_DISTECK_UART_SUPPORT==_ON)

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdReset(void)	
{
    BYTE ucIndex = GET_OSD_LANGUAGE();
	OsdDispDisableOsd();
	
	RTDEepromBackupColorCon();		// Backup Color Control
	RTDEepromBackupSetId();			// Backup SetID
		
	RTDEepromWholeRestore();

	RTDEepromRecoveryColorCon();	// Recovery Color Control
	RTDEepromRecoverySetId(); 		// Recovery SetID

	RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

    SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_AUTO);
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
    if(GET_OSD_DP_MST() != _MST_OFF)
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
    SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    
}

void OsdDispOsdFactoryReset(void)	
{
    BYTE ucIndex = GET_OSD_LANGUAGE();
	OsdDispDisableOsd();

	//RTDEepromBackupColorCon();	// Backup Color Control
	//RTDEepromBackupSetId();		// Backup SetID
	
	RTDEepromWholeRestore();

	//RTDEepromRecoveryColorCon();	// Recovery Color Control
	//RTDEepromRecoverySetId();		// Recovery SetID
    SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_AUTO);
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
    if(GET_OSD_DP_MST() != _MST_OFF)
    {
        SET_OSD_DP_MST(_MST_OFF);
    }
#endif
    SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
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

    switch(SysSourceGetInputPort())
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            ucOsdSourcePort = _VGA_A0;
            return ucOsdSourcePort;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
            ucOsdSourcePort = _DVI_D0;
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            ucOsdSourcePort = _HDMI_D0;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ucOsdSourcePort = _DP_D0;
#endif
            return ucOsdSourcePort;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
            ucOsdSourcePort = _DVI_D1;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            ucOsdSourcePort = _HDMI_D1;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ucOsdSourcePort = _DP_D1;
#endif
            return ucOsdSourcePort;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
            if(_DVI_D2 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D2;
            }
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if(_HDMI_D2 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D2;
            }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(_DP_D2 > 0x10)
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

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
            if(_DVI_D3 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D3;
            }
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if(_HDMI_D3 > 0x12)
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

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
            if(_DVI_D4 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D4;
            }
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if(_HDMI_D4 > 0x12)
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

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
            if(_DVI_D5 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D5;
            }
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if(_HDMI_D5 > 0x12)
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

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            if(_DP_D6 > 0x10)
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
// Description  : Logo showing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowLogo(void)
{
    g_ucLogoTimerCounter = 0;
    //	SET_OSD_DOUBLE_SIZE(_ON);

    ScalerDDomainPatternGenAdjustColor(0, 0, 0);

    ScalerDDomainPatternGenEnable(_ENABLE);
    ScalerDDomainBackgroundEnable(_DISABLE);

    OsdDispDisableOsd();
    OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);
#if (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
if(GET_OSD_LOGO_LIST() == 0)
    OsdFuncApplyMap(WIDTH(0x4c), HEIGHT(7), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
else if(GET_OSD_LOGO_LIST() == 1)
	OsdFuncApplyMap(WIDTH(0x32), HEIGHT(0x0B), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG)); // SABB
else
	OsdFuncApplyMap(WIDTH(0x13), HEIGHT(0x1C), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG)); //ATG x 1
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
    //	OsdFuncApplyMap(WIDTH(12*4+16*3), HEIGHT(9), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));	// 0x0C
#if 0
	OsdFuncApplyMap(WIDTH(12*4+44*3), HEIGHT(9), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));	// 0x0C
#else
    OsdFuncApplyMap(WIDTH(12 * 4 + 16 * 3), HEIGHT(9), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG)); // 0x0C
#endif
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
    // OsdFuncApplyMap(WIDTH(57), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
    OsdFuncApplyMap(WIDTH(57), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
#elif (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)

if(GET_OSD_LOGO_LIST() == 0)
{
    ScalerDDomainPatternGenAdjustColor(0, 0, 0);
    // OsdFuncApplyMap(WIDTH(57), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
    OsdFuncApplyMap(WIDTH(82), HEIGHT(12), COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
}
else if(GET_OSD_LOGO_LIST() == 1)
{
    ScalerDDomainPatternGenAdjustColor(255, 255, 255);
    // OsdFuncApplyMap(WIDTH(57), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
    OsdFuncApplyMap(WIDTH(41), HEIGHT(8), COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
}
else
{
    ScalerDDomainPatternGenAdjustColor(255, 255, 255);
    // OsdFuncApplyMap(WIDTH(57), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));
    OsdFuncApplyMap(WIDTH(84), HEIGHT(11), COLOR(_LOGO_CP_WHITE, _LOGO_CP_WHITE));
}

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
if(GET_OSD_LOGO_LIST() == 0)
{
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_THRUPUT0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_THRUPUT1);
}
else if(GET_OSD_LOGO_LIST() == 1)
{
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_SABB0);
}
else
{
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_ATG0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_ATG1); 
}
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);
#elif (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)
if(GET_OSD_LOGO_LIST() == 0)
{
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_ALPHACLIN_0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_ALPHACLIN_1);
}
else if(GET_OSD_LOGO_LIST() == 1)
{
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_ARTHREX_0);
}
else
{
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_RIWOLINK_0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_RIWOLINK_1);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO_RIWOLINK_2);
}

#else
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);
#endif

#if (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
if(GET_OSD_LOGO_LIST() == 0)
{
    OsdFontPut1BitTable2(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO_THRUPUT0, COLOR(_LOGO_CP_RED_1, _LOGO_CP_BG), 0x00);
    OsdFontPut1BitTable2(ROW(0), COL(0x2c), tiOSD_REALTEK_1BIT_LOGO_THRUPUT1, COLOR(_LOGO_CP_RED_1, _LOGO_CP_BG), 0x55);
    //OsdWindowDrawing(_OSD_WINDOW_0, XSTART(1), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BG);
}
else if(GET_OSD_LOGO_LIST() == 1)
{
    OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO_SABB_0, COLOR(_LOGO_CP_BLACK_2,_LOGO_CP_BLACK));
}
else
{
	ScalerDDomainPatternGenAdjustColor(255, 255, 255); //
	OsdFontPut1BitTable2(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO_ATG_0, COLOR(_LOGO_CP_WHITE,_LOGO_CP_BLACK_2), 0x00);
    OsdFontPut1BitTable2(ROW(0x10), COL(0), tiOSD_REALTEK_1BIT_LOGO_ATG_1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK_2), 0x4D);
}

#elif (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)

    OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO2, COLOR(_LOGO_CP_COLOR1, _LOGO_CP_BLACK));
    OsdFontPut1BitTable(ROW(0), COL(28), tiOSD_REALTEK_1BIT_LOGO3, COLOR(_LOGO_CP_COLOR2, _LOGO_CP_BLACK));
    OsdFontPut1BitTable(ROW(0), COL(56), tiOSD_REALTEK_1BIT_LOGO4, COLOR(_LOGO_CP_COLOR3, _LOGO_CP_BLACK));
    OsdFontPut1BitTable(ROW(0), COL(84), tiOSD_REALTEK_1BIT_LOGO5, COLOR(_LOGO_CP_COLOR4, _LOGO_CP_BLACK));

    OsdWindowDrawing(_OSD_WINDOW_0, XSTART(0), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BG);
#elif (_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
    OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLUE));
    OsdFontPut1BitTable(ROW(0), COL(14), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
    // OsdWindowDrawing(_OSD_WINDOW_0, XSTART(0), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_WHITE);
#elif (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)
if(GET_OSD_LOGO_LIST() == 0)
{
    OsdFontPut1BitTable2(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO_ALPHACLIN_0, COLOR(_LOGO_CP_BLACK, _LOGO_CP_RED), 0x00);
    OsdFontPut1BitTable2(ROW(0), COL(50), tiOSD_REALTEK_1BIT_LOGO_ALPHACLIN_1, COLOR(_LOGO_CP_BLACK, _LOGO_CP_WHITE), 0x76);
    // OsdWindowDrawing(_OSD_WINDOW_0, XSTART(0), YSTART(0), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_WHITE);
}
else if(GET_OSD_LOGO_LIST() == 1)
{
    OsdFontPut1BitTable2(ROW(0), COL(0),tiOSD_REALTEK_1BIT_LOGO_ARTHREX_0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_GRAY_1),0x00);
}
else
{
    OsdFontPut1BitTable2(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO_RIWOLINK_0, COLOR(_LOGO_CP_WHITE, _LOGO_CP_RED_2),0x00);
    OsdFontPut1BitTable2(ROW(0), COL(43), tiOSD_REALTEK_1BIT_LOGO_RIWOLINK_1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_GRAY_2),0x44);
    OsdFontPut1BitTable2(ROW(7), COL(50), tiOSD_REALTEK_1BIT_LOGO_RIWOLINK_2, COLOR(_LOGO_CP_WHITE, _LOGO_CP_RED_2),0x44+0x44);
}

#else  // #if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
    OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdFontPut1BitTable(ROW(0), COL(19), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    OsdWindowDrawing(_OSD_WINDOW_0, XSTART(1), YSTART(1), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BLUE);
#endif // #if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
    //	ScalerOsdChange1BitColor(ROW(0),  COL(19),LENGTH(_ITEM_WIDTH), HEIGHT(1), FG_COLOR(_CP_ORANGE), BG_COLOR(_CP_BG));//
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    OsdFuncEnableOsd();

#if (_INSTANT_TIMER_EVENT_0 == _ON)
    ScalerTimer0SetTimerCount(16);
#endif

    g_bLogoOn = _ON;
}

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

        // if (++u8_IDX > 19)
        if (++u8_IDX > 12)
            u8_IDX = 2;

        if (++u16_COUNT > 100) // 10 sec // 45 sec
            break;
    } while (1);

    // OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
    // OsdFontPut1BitTable(ROW(0), COL(28), tiOSD_REALTEK_1BIT_LOGO2, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
    // OsdFontPut1BitTable(ROW(0), COL(56), tiOSD_REALTEK_1BIT_LOGO3, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));
    // OsdFontPut1BitTable(ROW(0), COL(84), tiOSD_REALTEK_1BIT_LOGO4, COLOR(_LOGO_CP_WHITE, _LOGO_CP_BLACK));

    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
}
#endif


void MenuInputSource(void)
{

    if((SysPowerGetPowerStatus() != _POWER_STATUS_AC_ON)&&(SysModeGetModeState() != _MODE_STATUS_INITIAL))	
	{
		
		if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
	    {
	        SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);
			
	        if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
	        {
	            SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);	// Wakeup
	        }
	    }
		else if((SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
	    {
	        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
	    }
	    else// if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
	    {	
		    
			

			if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING)
				|| ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE)
				|| ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL))
			{
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
				//SET_OSD_POWER_SAVING_SHOW_MENU(_TRUE);		// Reactive Power Saving Message flag
			}
			
			OsdDispDisableOsd();
				
			SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
	        OsdFuncSetOsdItemFlag();
	        
	        g_usAdjustValue = GET_OSD_INPUT_PORT_OSD_ITEM();		

			printf("#1GET_OSD_INPUT_PORT_OSD_ITEM():%d\n\r",(int)GET_OSD_INPUT_PORT_OSD_ITEM());	
			
			#if(_ENABLE_MENU_VGA != _ON)	
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)		// When On Signal
					if(g_usAdjustValue >= _OSD_INPUT_A0)g_usAdjustValue -= 1; 
				#else
					if(g_usAdjustValue >= _OSD_INPUT_D0)g_usAdjustValue -= 2; 
				#endif
			#else
				if(g_usAdjustValue >= _OSD_INPUT_A0)g_usAdjustValue -= 1; 
			#endif	

			printf("#2GET_OSD_INPUT_PORT_OSD_ITEM():%d\n\r",(int)g_usAdjustValue);	
			
	        g_usBackupValue = g_usAdjustValue;
			SET_OSD_ITEM_INDEX(g_usBackupValue);	

	        OsdDispHotKeySourceMenu();
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);		 
		}
	}
}
void MenuNoneMenu(void)	
{
	if ((SysPowerGetPowerStatus() != _POWER_STATUS_AC_ON) && (SysModeGetModeState() != _MODE_STATUS_INITIAL))
	{
		// if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
		if (SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
		{
			if (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING) || ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE) || ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL))
			{
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
				// SET_OSD_POWER_SAVING_SHOW_MENU(_TRUE);
			}

			OsdDispDisableOsd();
			SET_OSD_STATE(_MENU_INFO);
			OsdFuncSetOsdItemFlag();
			OsdDispMainMenu();
			// OsdSubMenuPageDraw(_MENU_PICTURE);
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
		}
		else if (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
		{

			SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(_TRUE);
			// DebugMessageSystem("Power Normal 1- Select Key", SysPowerGetPowerStatus());
			if ((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING))
			{
				DebugMessageSystem("Power Normal 3- Select Key", 0);
				SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
			}
		}
	}
}

void OsdUserBackupConfig(void)
{
	UserCommonFlashSaveCustomerUserData();
}

void OsdUserRestoreConfig(void)
{
	BYTE ucIndex = 0;

	UserCommonFlashCustomerUserData();
	
	RTDNVRamSaveOSDData();
	for(ucIndex = 0; ucIndex <= _CT_COLORTEMP_AMOUNT; ++ucIndex)
	{
		RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
	}
	RTDNVRamSaveSixColorData();

	for(ucIndex = 0; ucIndex <= _SOURCE_AMOUNT; ++ucIndex)
	{
		RTDNVRamSaveBriCon(ucIndex);
	}

	RTDNVRamSaveSixColorData();

	UserInterfaceAdjustOsdPowerOnInitial();
	SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
}

void MenuExit(void)	
{
	
	OsdDispDisableOsd();
	SET_OSD_SERVICE(_OFF);
	OsdDispReactiveOsdMessage();	
	
}	
void MenuSubMenuClear(void)	
{
	int i;
	/*
	ScalerOsdWindowDisable(_MENU_SECTION_1_TITLE_WINDOW);	
	ScalerOsdWindowDisable(_MENU_SECTION_1_WINDOW);	
		*/
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	ScalerTimerWaitForEvent(_EVENT_DVS);	
	for(i=0; i<_OSD_MAIN_MENU_HEIGHT; i++)
		OsdFuncClearOsd(ROW(i), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 1);	// Clear Item	

	//OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, _OSD_MAIN_MENU_HEIGHT);	// Clear Item
	ScalerOsdWindowDisable(_MENU_SECTION_1_TITLE_WINDOW);	
	ScalerOsdWindowDisable(_MENU_SECTION_1_WINDOW);	
	//OsdMainMenuItemDraw();
}

void MenuInputSubExit(void)
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_INPUT);
	//MenuSubMenuClear();
}

void MenuPictureSubExit(void)	
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_PICTURE);
	//MenuSubMenuClear();				
}
void MenuColorSubExit(void)		
{
	//OsdMainMenuPageDraw();
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_COLOR);
	//MenuSubMenuClear();
}
void MenuScreenSubExit(void)
{
	//OsdMainMenuPageDraw();
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_SCREEN);
	//MenuSubMenuClear();
}

//void MenuDisplaySubExit(void)		
//{
//	ClearFocus(_MENU_SECTION_1, _ITEM_1);
//	SET_OSD_STATE(_MENU_DISPLAY);
//	MenuSubMenuClear();
//}
//void MenuOsdSubExit(void)		
//{
//	ClearFocus(_MENU_SECTION_1, _ITEM_1);
//	SET_OSD_STATE(_MENU_OSD_SETTING);
//	MenuSubMenuClear();
//}
void MenuAudioSubExit(void)		
{
	//OsdMainMenuPageDraw();
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_AUDIO);
	//MenuSubMenuClear();
}
//void MenuDpOptionSubExit(void)		
//{
//	ClearFocus(_MENU_SECTION_1, _ITEM_1);
//	SET_OSD_STATE(_MENU_DP_OPTION);
//	MenuSubMenuClear();
//}
void MenuSetupSubExit(void)		
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_SETUP);
	//MenuSubMenuClear();
}
#if(_ENABLE_MENU_VGA == _ON)	
void MenuVgaSubExit(void)		
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_VGA);
	MenuSubMenuClear();
}
#endif
#if(_ENABLE_MENU_EXPAND == _ON)
//void MenuHeatConSubExit(void)		
//{
//	ClearFocus(_MENU_SECTION_1, _ITEM_1);
//	SET_OSD_STATE(_MENU_HEAT_CONTROL);
//	MenuSubMenuClear();
//}
//void MenuDimConSubExit(void)		
//{
//	ClearFocus(_MENU_SECTION_1, _ITEM_1);
//	SET_OSD_STATE(_MENU_DIM_CONTROL);
//	MenuSubMenuClear();
//}
//void MenuVideoWallSubExit(void)		
//{
//	ClearFocus(_MENU_SECTION_1, _ITEM_1);
//	SET_OSD_STATE(_MENU_VIDEO_WALL);
//	MenuSubMenuClear();
//}
#endif
void MenuInfoSubExit(void)		
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_INFO);
	MenuSubMenuClear();
}

void MenuService1SubExit(void)
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_SERVICE1);
	MenuSubMenuClear();
}
void MenuService2SubExit(void)
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_SERVICE2);
	MenuSubMenuClear();
}
void MenuService3SubExit(void)
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_SERVICE3);
	MenuSubMenuClear();
}

void MenuServiceUserAssignSubExit(void)
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_SERVICE_USERASSIGN);
	MenuSubMenuClear();
}

void MenuServiceOLEDSubExit(void)
{
	ClearFocus(_MENU_SECTION_1);
	SET_OSD_STATE(_MENU_SERVICE_OLED);
	MenuSubMenuClear();
}

void MenuSection3ItemClear(void)	
{
	int i;
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH + 5), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	ScalerTimerWaitForEvent(_EVENT_DVS);	
	ScalerOsdWindowDisable(_MENU_SECTION_2_WINDOW);	
	for(i=0; i<_OSD_MAIN_MENU_HEIGHT; i++)
		OsdFuncClearOsd(ROW(i), COL(_MENU_SECTION_2_WIN_X), _MENU_SECTION_2_WIDTH + 5 , 1);	// Clear Item

	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);							   // _MENU_SECTION_TRANSPARENT_WINDOW GABEGE REMOVE
}

void MenuSection3Exit(void)
{
	ClearFocus(_MENU_SECTION_2);
	MenuSection3ItemClear();
	switch (GET_OSD_STATE())
	{
	case _MENU_INPUT_SOURCE1_ADJ:
		SET_OSD_STATE(_MENU_INPUT_SOURCE1);
		break;
	case _MENU_INPUT_SOURCE2_ADJ:
		SET_OSD_STATE(_MENU_INPUT_SOURCE2);
		break;
	case _MENU_INPUT_SOURCE3_ADJ:
		SET_OSD_STATE(_MENU_INPUT_SOURCE3);
		break;
	case _MENU_INPUT_SOURCE4_ADJ:
		SET_OSD_STATE(_MENU_INPUT_SOURCE4);
		break;
	case _MENU_PICTURE_GAMMA_ADJ:
		SET_OSD_STATE(_MENU_PICTURE_GAMMA);
		break;
#if (_ENABLE_MENU_REGION == _ON)
	case _MENU_PICTURE_REGION_ADJ:
		SET_OSD_STATE(_MENU_PICTURE_REGION);
		break;
#endif
	case _MENU_COLOR_EFFECT_ADJ:
		SET_OSD_STATE(_MENU_COLOR_EFFECT);
		// OsdSubMenuPageDraw(_MENU_COLOR);//test
		break;
	case _MENU_COLOR_GAMMA_ADJ:
		SET_OSD_STATE(_MENU_COLOR_GAMMA);
		break;
	case _MENU_COLOR_TEMPERATURE_ADJ:
		SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
		break;
	case _MENU_COLOR_SURGICAL_ADJ:
		SET_OSD_STATE(_MENU_COLOR_SURGICAL);
		break;
#if (_ENABLE_MENU_REGION == _ON)
	case _MENU_COLOR_REGION_ADJ:
		SET_OSD_STATE(_MENU_COLOR_REGION);
		break;
#endif
	case _MENU_SCREEN_OVERSCAN_ADJ:
		SET_OSD_STATE(_MENU_SCREEN_OVERSCAN);
		break;
	case _MENU_SCREEN_ASPECT_ADJ:
		SET_OSD_STATE(_MENU_SCREEN_ASPECT);
		break;
	case _MENU_SCREEN_MONO_COLOR_ADJ:
		SET_OSD_STATE(_MENU_SCREEN_MONO_COLOR);
		break;
	case _MENU_SCREEN_ROTATE_ADJ:
		SET_OSD_STATE(_MENU_SCREEN_ROTATE);
		break;
//	case _MENU_SCREEN_DISPLAY_MODE_ADJ:
//		SET_OSD_STATE(_MENU_SCREEN_DISPLAY_MODE);
//		break;
//	case _MENU_SCREEN_PIP_POSITION_ADJ:
//		SET_OSD_STATE(_MENU_SCREEN_PIP_POSITION);
//		break;

///	case _MENU_OSD_ROTATE_ADJ:
//		SET_OSD_STATE(_MENU_OSD_ROTATE);
//		break;
//	case _MENU_OSD_LANGUAGE_ADJ:
//		SET_OSD_STATE(_MENU_OSD_LANGUAGE);
//		break;
	case _MENU_AUDIO_MUTE_ADJ:
		SET_OSD_STATE(_MENU_AUDIO_MUTE);
		break;
	case _MENU_AUDIO_SOURCE_ADJ:
		SET_OSD_STATE(_MENU_AUDIO_SOURCE);
		break;
//	case _MENU_DP_OPTION_VERSION_ADJ:
//		SET_OSD_STATE(_MENU_DP_OPTION_VERSION);
//		break;
//	case _MENU_DP_OPTION_MST_ADJ:
//		SET_OSD_STATE(_MENU_DP_OPTION_MST);
//		break;
//	case _MENU_DP_OPTION_RESOLUTION_ADJ:
//		SET_OSD_STATE(_MENU_DP_OPTION_RESOLUTION);
//		break;
//	case _MENU_DP_OPTION_CLONE_ADJ:
//		SET_OSD_STATE(_MENU_DP_OPTION_CLONE);
//		break;
	case _MENU_SETUP_KEYLOCK_ADJ:
		SET_OSD_STATE(_MENU_SETUP_KEYLOCK);
		break;
	case _MENU_SETUP_BACKLIGHT_CONTROL_ADJ:
		SET_OSD_STATE(_MENU_SETUP_BACKLIGHT_CONTROL);
		break;
	case _MENU_SETUP_POWERSAVE_ADJ:
		SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
		break;
	case _MENU_SETUP_RESET_ADJ:
		SET_OSD_STATE(_MENU_SETUP_RESET);
		break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
	case _MENU_SETUP_STABILIZER_CONTROL_ADJ:
		SET_OSD_STATE(_MENU_SETUP_STABILIZER_CONTROL);
		break;
#endif
#if (_ENABLE_MENU_VGA == _ON)
	case _MENU_VGA_AUTO_ADJ:
		SET_OSD_STATE(_MENU_VGA_AUTO);
		SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
#endif
		break;
	case _MENU_SERVICE_D0NAME_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_D0NAME);
		break;
	case _MENU_SERVICE_D1NAME_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_D1NAME);
		break;
	case _MENU_SERVICE_D2NAME_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_D2NAME);
		break;
	case _MENU_SERVICE_D3NAME_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_D3NAME);
		break;
	case _MENU_SERVICE_BACKLIGHT_INVERT_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
		break;
	case _MENU_SERVICE_LOGO_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_LOGO);
		break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
	case _MENU_SERVICE_STABILUX_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_STABILUX);
		break;
#endif
	case _MENU_SERVICE_DP_OPTION_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_DP_OPTION);
		break;
	case _MENU_SERVICE_LIGHTSENSOR_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_LIGHTSENSOR);
		break;
	case _MENU_SERVICE_FAN_OPTION_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_FAN_OPTION);
		break;
	case _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_USER_BACKUP_CONFIG);
		break;	
	case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_RESTORE_FACTORY_DEFAULT);
		break;	
	case _MENU_SERVICE_USERASSIGN_UP_ADJ:
		SET_OSD_USER_ASSIGN_UP(g_usBackupValue);
		SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_UP);
		break;
	case _MENU_SERVICE_USERASSIGN_DOWN_ADJ:
		SET_OSD_USER_ASSIGN_DOWN(g_usBackupValue);
		SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_DOWN);
		break;
	case _MENU_SERVICE_USERASSIGN_LEFT_ADJ:
		SET_OSD_USER_ASSIGN_LEFT(g_usBackupValue);
		SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_LEFT);
		break;
	case _MENU_SERVICE_USERASSIGN_RIGHT_ADJ:
		SET_OSD_USER_ASSIGN_RIGHT(g_usBackupValue);
		SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_RIGHT);
		break;
	case _MENU_SERVICE_OLED_OFFRS_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_OLED_OFFRS);
		break;
	case _MENU_SERVICE_OLED_JB_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_OLED_JB);
		break;
	case _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ:
		SET_OSD_STATE(_MENU_SERVICE_OLED_SEQUENCE_TIME);
		break;
	}
}

void MenuInputSource1Select(void)
{

/*
#if(_ENABLE_MENU_VGA != _ON)		
	#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-1);
	#else
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-2);
	#endif
#else
	#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D3);
	#else
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-1);
	#endif
#endif
*/

	SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_INPUT_SOURCE1_ADJ);
	OsdSection3ItemPageDraw(_MENU_INPUT_SOURCE1_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuInputSource2Select(void)
{

#if (_ENABLE_MENU_VGA != _ON)
	if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D4 - 1);
	else
		SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM() - 1);
#else
	if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D4);
	else
		SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());
#endif

	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_INPUT_SOURCE2_ADJ);
	OsdSection3ItemPageDraw(_MENU_INPUT_SOURCE2_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuInputSource3Select(void)
{

#if (_ENABLE_MENU_VGA != _ON)
	if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D4 - 1);
	else
		SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM() - 1);
#else
	if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D4);
	else
		SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());
#endif

	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_INPUT_SOURCE3_ADJ);
	OsdSection3ItemPageDraw(_MENU_INPUT_SOURCE3_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuInputSource4Select(void)
{

#if (_ENABLE_MENU_VGA != _ON)
	if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D4 - 1);
	else
		SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM() - 1);
#else
	if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
		SET_OSD_ITEM_INDEX(_OSD_INPUT_D4);
	else
		SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());
#endif
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_INPUT_SOURCE4_ADJ);
	OsdSection3ItemPageDraw(_MENU_INPUT_SOURCE4_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
// BLACKLEVEL ADJUST
void MenuPictureBlacklevelSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL_ADJ);
}
void MenuPictureBlacklevelAdjExit(void)
{
	SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(g_usBackupValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
	OsdDispNumberAndText(_MENU_PICTURE_BLACKLEVEL, GET_OSD_BRIGHTNESS(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBrightness(GET_OSD_BRIGHTNESS());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL);
}
void MenuPictureBlacklevelAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL);
}
// CONTRAST ADJUST
void MenuPictureContrastSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_PICTURE_CONTRAST_ADJ);
}
void MenuPictureContrastAdjExit(void)
{
	SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_usBackupValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
	OsdDispNumberAndText(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustContrast(GET_OSD_CONTRAST());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
}
void MenuPictureContrastAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
}
// CHROMA ADJUST
void MenuPictureChromaSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_OSD_SATURATION(), _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_PICTURE_CHROMA_ADJ);
}
void MenuPictureChromaAdjExit(void)
{
	SET_OSD_SATURATION(UserCommonAdjustPercentToRealValue(g_usBackupValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER));
	OsdDispNumberAndText(_MENU_PICTURE_CHROMA, GET_OSD_SATURATION(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustGlobalHueSat(GET_OSD_HUE(), GET_OSD_SATURATION()); // Set Global hue/sat
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_PICTURE_CHROMA);
}
void MenuPictureChromaAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_PICTURE_CHROMA);
}
// SHARPNESS ADJUST
void MenuPictureSharpnessSelect(void)
{
	g_usBackupValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _OFF);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_PICTURE_SHARPNESS_ADJ);
}
void MenuPictureSharpnessAdjExit(void)
{
	SET_OSD_SHARPNESS(g_usBackupValue);
	OsdDispNumberAndText(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(), COLOR(_CP_WHITE, _CP_BG));
	UserCommonAdjustSharpness(SysSourceGetInputPort());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
}
void MenuPictureSharpnessAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
}
void MenuPictureGammaSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_GAMMA());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_PICTURE_GAMMA_ADJ);
	OsdSection3ItemPageDraw(_MENU_PICTURE_GAMMA_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuPictureResetToDefaultSelect(void)	
{
	// RESTORE PICTURE
	//  SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
	// SET_OSD_STATE(_MENU_INFO_FW_VERSION);
	SET_OSD_BRIGHTNESS(_DEFAULT_BRIGHTNESS);
	SET_OSD_CONTRAST(_DEFAULT_CONTRAST);
	SET_OSD_SATURATION(_DEFAULT_SATURATION);
	SET_OSD_SHARPNESS(_DEFAULT_SHARPNESS);
	// SET_OSD_GAMMA(_DEFAULT_GAMMA);

	UserAdjustBrightness(GET_OSD_BRIGHTNESS());
	UserAdjustContrast(GET_OSD_CONTRAST());
	UserAdjustGlobalHueSat(GET_OSD_HUE(), GET_OSD_SATURATION()); // Set Global hue/sat
	// UserCommonAdjustSharpness(UserAdjustGetSelectRegionPort(), GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()));
	UserCommonAdjustSharpness(SysSourceGetInputPort());
	// UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
	SET_OSD_GAMMA(_DEFAULT_GAMMA);
	
#if(_GAMMA_FUNCTION == _ON)
	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
	
	if(GET_OSD_GAMMA() != _GAMMA_OFF)
	{
		UserAdjustGamma(GET_OSD_GAMMA());
		ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
		UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
	}
#if(((_OGC_SUPPORT == _ON) || (_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)) && (_CONTRAST_SUPPORT == _ON))
	else
	{
		RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
		ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
		UserAdjustContrast(GET_OSD_CONTRAST());
	}
#endif
#endif

	OsdSubMenuPageDraw(_MENU_PICTURE);
	RTDEepromSaveOSDData();
	RTDEepromRestoreColorSetting();
	RTDEepromSaveBriCon(SysSourceGetSourceType());
}
// COLOR

// BIAS R G B
void MenuColorBIASRSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_COLOR_BIAS_R(), _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_COLOR_BIAS_R_ADJ);
}
void MenuColorBIASRAdjExit(void)
{
	SET_COLOR_BIAS_R(UserCommonAdjustPercentToRealValue(g_usBackupValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER));
	OsdDispNumberAndText(_MENU_COLOR_BIAS_R, GET_COLOR_BIAS_R(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBrightness(GET_OSD_BRIGHTNESS());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_COLOR_BIAS_R);
}
void MenuColorBIASRAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_COLOR_BIAS_R);
}

void MenuColorBIASGSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_COLOR_BIAS_G(), _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_COLOR_BIAS_G_ADJ);
}
void MenuColorBIASGAdjExit(void)
{
	SET_COLOR_BIAS_G(UserCommonAdjustPercentToRealValue(g_usBackupValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER));
	OsdDispNumberAndText(_MENU_COLOR_BIAS_G, GET_COLOR_BIAS_G(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBrightness(GET_OSD_BRIGHTNESS());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_COLOR_BIAS_G);
}
void MenuColorBIASGAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_COLOR_BIAS_G);
}

void MenuColorBIASBSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_COLOR_BIAS_B(), _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_COLOR_BIAS_B_ADJ);
}
void MenuColorBIASBAdjExit(void)
{
	SET_COLOR_BIAS_B(UserCommonAdjustPercentToRealValue(g_usBackupValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER));
	OsdDispNumberAndText(_MENU_COLOR_BIAS_B, GET_COLOR_BIAS_B(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBrightness(GET_OSD_BRIGHTNESS());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_COLOR_BIAS_B);
}
void MenuColorBIASBAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_COLOR_BIAS_B);
}
// GAIN R G B
void MenuColorGainRSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_COLOR_GAIN_R(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_5);
	SET_OSD_STATE(_MENU_COLOR_GAIN_R_ADJ);
}
void MenuColorGainRAdjExit(void)
{
	SET_COLOR_GAIN_R(UserCommonAdjustPercentToRealValue(g_usBackupValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER));
	OsdDispNumberAndText(_MENU_COLOR_GAIN_R, GET_COLOR_GAIN_R(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustContrast(GET_OSD_CONTRAST());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
	SET_OSD_STATE(_MENU_COLOR_GAIN_R);
}
void MenuColorGainRAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
	SET_OSD_STATE(_MENU_COLOR_GAIN_R);
}
void MenuColorGainGSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_COLOR_GAIN_G(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_COLOR_GAIN_G_ADJ);
}
void MenuColorGainGAdjExit(void)
{
	SET_COLOR_GAIN_G(UserCommonAdjustPercentToRealValue(g_usBackupValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER));
	OsdDispNumberAndText(_MENU_COLOR_GAIN_G, GET_COLOR_GAIN_G(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustContrast(GET_OSD_CONTRAST());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_COLOR_GAIN_G);
}
void MenuColorGainGAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_COLOR_GAIN_G);
}
void MenuColorGainBSelect(void)
{
	g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_COLOR_GAIN_B(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_7);
	SET_OSD_STATE(_MENU_COLOR_GAIN_B_ADJ);
}
void MenuColorGainBAdjExit(void)
{
	SET_COLOR_GAIN_B(UserCommonAdjustPercentToRealValue(g_usBackupValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER));
	OsdDispNumberAndText(_MENU_COLOR_GAIN_B, GET_COLOR_GAIN_B(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustContrast(GET_OSD_CONTRAST());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
	SET_OSD_STATE(_MENU_COLOR_GAIN_B);
}
void MenuColorGainBAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
	SET_OSD_STATE(_MENU_COLOR_GAIN_B);
}

#if (_ENABLE_MENU_REGION == _ON)
void MenuPictureRegionSelect(void)
{

	/*
	switch(GET_OSD_DISPLAY_MODE())
	{
		case _OSD_DM_1P:
			SET_OSD_SELECT_REGION(_OSD_SR_1P_FULL);
			break;
		case _OSD_DM_2P_LR:
			SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_FULL);
			break;
		case _OSD_DM_2P_TB:
			SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_FULL);
			break;
		case _OSD_DM_2P_PIP:
			SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_FULL);
			break;
		case _OSD_DM_3P:
			SET_OSD_SELECT_REGION(_OSD_SR_3P_FULL);
			break;
		case _OSD_DM_4P:
			SET_OSD_SELECT_REGION(_OSD_SR_4P_FULL);
			break;
	}
	*/
	SET_OSD_ITEM_INDEX();
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_PICTURE_REGION_ADJ);
	OsdSection3ItemPageDraw(_MENU_PICTURE_REGION_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
#endif
void MenuColorEffectSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_COLOR_EFFECT());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE_PREVIOUS(_MENU_COLOR_EFFECT);
	SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_EFFECT_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuColorGammaSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_GAMMA());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_GAMMA_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuColorTemperatureSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_COLOR_TEMP_TYPE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_TEMPERATURE_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuColorSurgicalSelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SET_OSD_ITEM_INDEX(GET_OSD_PCM_STATUS());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_COLOR_SURGICAL_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_SURGICAL_ADJ);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

#if (_ENABLE_MENU_REGION == _ON)
void MenuColorRegionSelect(void)
{

	SET_OSD_ITEM_INDEX();
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_COLOR_REGION_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_REGION_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
#endif
// SCREEN
void MenuScreenOverscanSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_OVERSCAN_STATUS());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SCREEN_OVERSCAN_ADJ);
	OsdSection3ItemPageDraw(_MENU_SCREEN_OVERSCAN_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuScreenAspectSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_ASPECT_RATIO_TYPE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SCREEN_ASPECT_ADJ);
	OsdSection3ItemPageDraw(_MENU_SCREEN_ASPECT_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuScreenMonoColorSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_COLOR_EFFECT());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SCREEN_MONO_COLOR_ADJ);
	OsdSection3ItemPageDraw(_MENU_SCREEN_MONO_COLOR_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuScreenRotateSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_DISP_ROTATE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SCREEN_ROTATE_ADJ);
	OsdSection3ItemPageDraw(_MENU_SCREEN_ROTATE_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
/*
void MenuScreenModeSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_DISPLAY_MODE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SCREEN_DISPLAY_MODE_ADJ);
	OsdSection3ItemPageDraw(_MENU_SCREEN_DISPLAY_MODE_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
*/
//void MenuPictureAspectSelect(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_ASPECT_RATIO_TYPE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_4 + GET_OSD_ITEM_INDEX());	
//	
//	SET_OSD_STATE(_MENU_PICTURE_ASPECT_ADJ);
//	OsdSection3ItemPageDraw(_MENU_PICTURE_ASPECT_ADJ);	
//}
#if(_ENABLE_MENU_OVERSCAN == _ON)	
void MenuPictureOverscanSelect(void)		
{
	SET_OSD_ITEM_INDEX(GET_OSD_OVERSCAN_STATUS());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_5 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_PICTURE_OVERSCAN_ADJ);
	OsdSection3ItemPageDraw(_MENU_PICTURE_OVERSCAN_ADJ);
}
#endif
#if(_ENABLE_MENU_REGION == _ON)
void MenuPictureRegionSelect(void)		
{
	/*
	switch(GET_OSD_DISPLAY_MODE())
	{
		case _OSD_DM_1P:
			SET_OSD_SELECT_REGION(_OSD_SR_1P_FULL);
			break;
		case _OSD_DM_2P_LR:
			SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_FULL);
			break;
		case _OSD_DM_2P_TB:
			SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_FULL);
			break;
		case _OSD_DM_2P_PIP:
			SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_FULL);
			break;
		case _OSD_DM_3P:
			SET_OSD_SELECT_REGION(_OSD_SR_3P_FULL);
			break;
		case _OSD_DM_4P:
			SET_OSD_SELECT_REGION(_OSD_SR_4P_FULL);
			break;
	}
	*/
	SET_OSD_ITEM_INDEX(GET_OSD_SELECT_REGION());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_6 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_PICTURE_REGION_ADJ);
	OsdSection3ItemPageDraw(_MENU_PICTURE_REGION_ADJ);
}
#endif
/*
void MenuColorEffectSelect(void)		
{
	SET_OSD_ITEM_INDEX(GET_OSD_COLOR_EFFECT());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_EFFECT_ADJ);
}
void MenuColorGammaSelect(void)		
{
	SET_OSD_ITEM_INDEX(GET_OSD_GAMMA());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_2 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_GAMMA_ADJ);
}
void MenuColorTemperatureSelect(void)		
{
	SET_OSD_ITEM_INDEX(GET_COLOR_TEMP_TYPE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_3 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_TEMPERATURE_ADJ);
}
*/
#if(_ENABLE_MENU_REGION == _ON)
void MenuColorRegionSelect(void)		
{
	SET_OSD_ITEM_INDEX(GET_OSD_SELECT_REGION());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_4 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_COLOR_REGION_ADJ);
	OsdSection3ItemPageDraw(_MENU_COLOR_REGION_ADJ);
}
#endif
//void MenuDisplayRotateSelect(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_DISP_ROTATE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DISPLAY_ROTATE_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_ROTATE_ADJ);
//}
//void MenuDisplaySource1Select(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());
//	
//#if(_ENABLE_MENU_VGA != _ON)	
//	#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
//	if(GET_OSD_INPUT_PORT_OSD_ITEM() >= _OSD_INPUT_A0)
//		SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
//	#else
//	if(GET_OSD_INPUT_PORT_OSD_ITEM() >= _OSD_INPUT_D0)
//		SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-2);
//	#endif
//#else
//	if(GET_OSD_INPUT_PORT_OSD_ITEM() >= _OSD_INPUT_A0)
//		SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
//	#endif
//#endif

//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_2 + GET_OSD_ITEM_INDEX());

//	SET_OSD_STATE(_MENU_DISPLAY_SOURCE1_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_SOURCE1_ADJ);
//}
//void MenuDisplaySource2Select(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());

//#if(_ENABLE_MENU_VGA != _ON)
//		if(GET_OSD_INPUT_PORT_OSD_ITEM() >= _OSD_INPUT_A0)
//			SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
//#endif

//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_3 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DISPLAY_SOURCE2_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_SOURCE2_ADJ);
//}
//void MenuDisplaySource3Select(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());

//#if(_ENABLE_MENU_VGA != _ON)	
//		if(GET_OSD_INPUT_PORT_OSD_ITEM() >= _OSD_INPUT_A0)
//			SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
//#endif

//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_4 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DISPLAY_SOURCE3_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_SOURCE3_ADJ);
//}
//void MenuDisplaySource4Select(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_INPUT_PORT_OSD_ITEM());

//#if(_ENABLE_MENU_VGA != _ON)	
//		if(GET_OSD_INPUT_PORT_OSD_ITEM() >= _OSD_INPUT_A0)
//			SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
//#endif

//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_5 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DISPLAY_SOURCE4_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_SOURCE4_ADJ);
//}
//void MenuDisplayModeSelect(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_DISPLAY_MODE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_6 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DISPLAY_MODE_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_MODE_ADJ);
//}
//void MenuDisplayPipPosiSelect(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_PIP_POSITION_TYPE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_7 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DISPLAY_PIP_POSITION_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_PIP_POSITION_ADJ);
//}
//void MenuDisplayInputSwapSelect(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_INPUT_SWAP());
//	//SET_OSD_ITEM_INDEX(0);
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_9 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DISPLAY_INPUT_SWAP_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DISPLAY_INPUT_SWAP_ADJ);
//}
//void MenuOsdRotateSelect(void)				
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_ROTATE_STATUS());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_5 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_OSD_ROTATE_ADJ);
//	OsdSection3ItemPageDraw(_MENU_OSD_ROTATE_ADJ);
//}
//void MenuOsdLanguageSelect(void)		
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_LANGUAGE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_6 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_OSD_LANGUAGE_ADJ);
//	OsdSection3ItemPageDraw(_MENU_OSD_LANGUAGE_ADJ);
//}
void MenuAudioMuteSelect(void)
{
	SET_OSD_ITEM_INDEX(GET_OSD_VOLUME_MUTE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_3 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_AUDIO_MUTE_ADJ);
	OsdSection3ItemPageDraw(_MENU_AUDIO_MUTE_ADJ);
}
void MenuAudioSourceSelect(void)
{
	SET_OSD_ITEM_INDEX(GET_OSD_AUDIO_SOURCE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_3 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_AUDIO_SOURCE_ADJ);
	OsdSection3ItemPageDraw(_MENU_AUDIO_SOURCE_ADJ);
}
//void MenuDpVersionSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_DP_D0_VERSION());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DP_OPTION_VERSION_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DP_OPTION_VERSION_ADJ);
//}
//void MenuDpMstSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_DP_MST());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_2 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DP_OPTION_MST_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DP_OPTION_MST_ADJ);
//}
//void MenuDpResolutionSelect(void)
//{
//	SET_OSD_ITEM_INDEX(UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_3 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DP_OPTION_RESOLUTION_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DP_OPTION_RESOLUTION_ADJ);
//}
//void MenuDpCloneSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_CLONE_MODE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_4 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DP_OPTION_CLONE_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DP_OPTION_CLONE_ADJ);
//}
//void MenuDpCloneSrcSelect(void)	
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_CLONE_SRC());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_5 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DP_OPTION_CLONE_SRC_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DP_OPTION_CLONE_SRC_ADJ);
//}
void MenuSetupResetSelect(void)
{
	SET_OSD_ITEM_INDEX(GET_OSD_RESET_MODE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_5 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_SETUP_RESET_ADJ);
	OsdSection3ItemPageDraw(_MENU_SETUP_RESET_ADJ);
}

#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
void MenuSetupStabilizerSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_STABILIZER());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_SETUP_STABILIZER_CONTROL_ADJ);
	OsdSection3ItemPageDraw(_MENU_SETUP_STABILIZER_CONTROL_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
#endif

void MenuSetupPowerSaveSelect(void)
{
	SET_OSD_ITEM_INDEX(GET_OSD_POWERSAVE_TIME());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_SETUP_POWERSAVE_ADJ);
	OsdSection3ItemPageDraw(_MENU_SETUP_POWERSAVE_ADJ);
}

void MenuSetupKeyLockSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_KEYLOCK());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_SETUP_KEYLOCK_ADJ);
	OsdSection3ItemPageDraw(_MENU_SETUP_KEYLOCK_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceScreenTestSelect(void)
{
	MenuExit();
	SET_OSD_LCD_TEST_MODE(0);
	LCDtest_ShowBurninPicture(GET_OSD_LCD_TEST_MODE());
}

void MenuServiceWhiteBalranceSelect(void)
{
	// MenuExit();
	ScalerColorOutputGammaEnable(_FUNCTION_OFF);
	ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
	ScalerColorBrightnessEnable(_FUNCTION_OFF);
	ScalerColorContrastEnable(_FUNCTION_OFF);
	ScalerColorSRGBEnable(_FUNCTION_OFF);
	ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
	ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
	ScalerColorDCCEnable(_FUNCTION_OFF);
	ScalerColorRingingFilterOff();
	// ScalerColorUltraVividEnable(_FUNCTION_OFF);
}
void MenuServiceD0NameSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_D0_NAME());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_D0NAME_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_D0NAME_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceD1NameSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_D1_NAME());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_D1NAME_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_D1NAME_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceD2NameSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_D2_NAME());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_D2NAME_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_D2NAME_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuServiceD3NameSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_D3_NAME());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_7 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_D3NAME_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_D3NAME_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuServiceBacklightMinSelect(void)
{
	g_usBackupValue = GET_BACKLIGHT_MIN();
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN_ADJ);
}
void MenuServiceBacklightMinAdjExit(void)
{
	SET_BACKLIGHT_MIN(g_usBackupValue);
	OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_MIN, g_usBackupValue, COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBacklight(GET_OSD_BACKLIGHT());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN);
}
void MenuServiceBacklightMinAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	RTDNVRamSaveOsdServiceData();	
	MenuBacklightLeftRight();
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN);
}

void MenuServiceBacklightMaxSelect(void)
{

	g_usBackupValue = GET_BACKLIGHT_MAX();	
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MAX_ADJ);
}
void MenuServiceBacklightMaxAdjExit(void)
{

	SET_BACKLIGHT_MAX(g_usBackupValue); 	
	OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_MAX, g_usBackupValue, COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBacklight(GET_OSD_BACKLIGHT());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MAX);
}
void MenuSerivceBacklightMaxAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	RTDNVRamSaveOsdServiceData();	
	MenuBacklightLeftRight();
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MAX);
}

void MenuServiceBacklightInvertSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_BACKLIGHT_INVERT());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_BACKLIGHT_INVERT_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceBacklightFreqSelect(void)
{
	g_usBackupValue = GET_OSD_BACKLIGHT_FREQ();
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ_ADJ);
}
void MenuServiceBacklightFreqAdjExit(void)
{
	SET_OSD_BACKLIGHT_FREQ(g_usBackupValue);
	OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_FREQ, g_usBackupValue, COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBacklight(GET_OSD_BACKLIGHT());
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
}
void MenuSerivceBacklightFreqAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
}

void MenuServiceLogoSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_LOGO_ON());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_LOGO_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_LOGO_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceLogoListSelect(void)
{
	g_usBackupValue = GET_OSD_LOGO_LIST();
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_SERVICE_LOGO_LIST_ADJ);
}

void MenuServiceLogoListAdjExit(void)
{
	SET_OSD_LOGO_LIST(g_usBackupValue);
	OsdDispNumberAndText(_MENU_SERVICE_LOGO_LIST, g_usBackupValue, COLOR(_CP_WHITE, _CP_BG));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_SERVICE_LOGO_LIST);
}

void MenuServiceLogoListAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	MenuBacklightLeftRight();
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_SERVICE_LOGO_LIST);
}

#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
void MenuServiceStabiluxSelect(void)
{
	g_usBackupValue = GET_OSD_STABILUX();
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_SERVICE_STABILUX_ADJ);
}
void MenuServiceStabiluxAdjExit(void)
{
	SET_OSD_STABILUX(g_usBackupValue);
	OsdDispNumberAndText(_MENU_SERVICE_STABILUX, g_usBackupValue, COLOR(_CP_WHITE, _CP_BG));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_SERVICE_STABILUX);
}
void MenuSerivceStabiluxAdjSelect(void)
{
	UserAdjustStabilux(g_usAdjustValue);
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
	SET_OSD_STATE(_MENU_SERVICE_STABILUX);
}
#endif
void MenuServiceDPSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_DP_MST());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_DP_OPTION_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_DP_OPTION_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceLSSelect(void)
{

#if (_ENABLE_LIGHT_SENSOR == _ON)
	SET_OSD_ITEM_INDEX(GET_OSD_LIGHT_SENSOR_STATUS());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_LIGHTSENSOR_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_LIGHTSENSOR_ADJ);
#endif
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceFANSelect(void)
{

#if (_ENABLE_FAN_CONTROL == _ON)
	SET_OSD_ITEM_INDEX(GET_OSD_FAN_STATUS());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_FAN_OPTION_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_FAN_OPTION_ADJ);
#endif
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuServiceFanSpeedSelect(void)
{
#if (_ENABLE_FAN_CONTROL == _ON)
	//ApplyFanControl(_TRUE);
	g_usBackupValue = GET_OSD_FAN_PWM();
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_SERVICE_FAN_SPEED_ADJ);
#endif
}
void MenuServiceFanSpeedAdjExit(void)
{
#if (_ENABLE_FAN_CONTROL == _ON)
	SET_OSD_FAN_PWM(g_usBackupValue);
	OsdDispNumberAndText(_MENU_SERVICE_FAN_SPEED, g_usBackupValue, COLOR(_CP_WHITE, _CP_BG));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_SERVICE_FAN_SPEED);
#endif
}
void MenuSerivceFanSpeedAdjSelect(void)
{
#if (_ENABLE_FAN_CONTROL == _ON)
	SET_OSD_FAN_PWM(g_usAdjustValue);
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_SERVICE_FAN_SPEED);
#endif
}
void MenuServiceUserBackupConfigSelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SET_OSD_ITEM_INDEX(_OFF);
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_USER_BACKUP_CONFIG_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_USER_BACKUP_CONFIG_ADJ);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceRestoreFactoryDefaultSelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SET_OSD_ITEM_INDEX(_OFF);
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}


void MenuServiceUserAssignUpKeySelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH + 5), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SET_OSD_ITEM_INDEX(GET_OSD_USER_ASSIGN_UP());
	SetFocus(_MENU_SECTION_USERASSIGN, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_UP_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_UP_ADJ);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}	
void MenuServiceUserAssignDownKeySelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH + 5), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SET_OSD_ITEM_INDEX(GET_OSD_USER_ASSIGN_DOWN());
	SetFocus(_MENU_SECTION_USERASSIGN, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_DOWN_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_DOWN_ADJ);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuServiceUserAssignLeftKeySelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH + 5), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SET_OSD_ITEM_INDEX(GET_OSD_USER_ASSIGN_LEFT());
	SetFocus(_MENU_SECTION_USERASSIGN, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_LEFT_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_LEFT_ADJ);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuServiceUserAssignRightKeySelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH + 5), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SET_OSD_ITEM_INDEX(GET_OSD_USER_ASSIGN_RIGHT());
	SetFocus(_MENU_SECTION_USERASSIGN, ROW_OFFSET + _ITEM_4);
	SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_RIGHT_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_RIGHT_ADJ);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuServiceOFFRSSelect(void)
{
#if (_ENABLE_MENU_OLED == _ON)

	SET_OSD_ITEM_INDEX(GET_OSD_OLED_OFFRS_STATUS());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_OLED_OFFRS_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_OLED_OFFRS_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
#endif
}
void MenuServiceJBSelect(void)
{
#if (_ENABLE_MENU_OLED == _ON)

	SET_OSD_ITEM_INDEX(GET_OSD_OLED_JB_STATUS());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
	SET_OSD_STATE(_MENU_SERVICE_OLED_JB_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_OLED_JB_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
#endif
}
void MenuServiceTimeSelect(void)
{
#if (_ENABLE_MENU_OLED == _ON)

	SET_OSD_ITEM_INDEX(GET_OSD_OLED_SEQUENCE_TIME());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX() - _POWER_SAVE_30SEC);
	SET_OSD_STATE(_MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ);
	OsdSection3ItemPageDraw(_MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
#endif
}

void MenuSetupBacklightSelect(void)
{
	if (GET_OSD_BACKLIGHT_CONTROL() == _ON)
	{
		g_usBackupValue = GET_OSD_BACKLIGHT();
	}
	else
	{
		g_usBackupValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
	}
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_SETUP_BACKLIGHT_ADJ);
}

void MenuSetupBacklightAdjExit(void)
{
	if (GET_OSD_BACKLIGHT_CONTROL() == _ON)
	{
		SET_OSD_BACKLIGHT(g_usBackupValue);
	}
	else
	{
		SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usBackupValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
	}
	OsdDispNumberAndText(_MENU_SETUP_BACKLIGHT, GET_OSD_BACKLIGHT(), COLOR(_CP_WHITE, _CP_BG));
	UserAdjustBacklight(GET_OSD_BACKLIGHT());

	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_SETUP_BACKLIGHT);
}
void MenuSetupBacklightAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
	SET_OSD_STATE(_MENU_SETUP_BACKLIGHT);
}

void MenuSetupBacklightControlSelect(void)
{

	SET_OSD_ITEM_INDEX(GET_OSD_BACKLIGHT_CONTROL());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());

	SET_OSD_STATE(_MENU_SETUP_BACKLIGHT_CONTROL_ADJ);
	OsdSection3ItemPageDraw(_MENU_SETUP_BACKLIGHT_CONTROL_ADJ);
//	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

#if(_ENABLE_MENU_HPD_MODE == _ON)
//void MenuSetupHpdModeSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_HPD_MODE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_4 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_SETUP_HPD_MODE_ADJ);
//	OsdSection3ItemPageDraw(_MENU_SETUP_HPD_MODE_ADJ);
//}
#endif
#if(_ENABLE_MENU_VGA == _ON)	
void MenuVgaAutoAdjustSelect(void)
{
	SET_OSD_ITEM_INDEX(GET_VGA_AUTOADJ_MODE());
	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
	
	SET_OSD_STATE(_MENU_VGA_AUTO_ADJ);
	OsdSection3ItemPageDraw(_MENU_VGA_AUTO_ADJ);
}
#endif
#if(_ENABLE_MENU_EXPAND == _ON)
//void MenuHeatConFanSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_FAN_CONTROL());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_HEATCON_FAN_ADJ);
//	OsdSection3ItemPageDraw(_MENU_HEATCON_FAN_ADJ);
//}
//void MenuHeatConShutdownSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_SHUTDOWN_MODE());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_5 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_HEATCON_SHUTDOWN_ADJ);
//	OsdSection3ItemPageDraw(_MENU_HEATCON_SHUTDOWN_ADJ);
//}
//void MenuDimConAutoSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_AUTO_DIMMING());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_DIMCON_AUTO_ADJ);
//	OsdSection3ItemPageDraw(_MENU_DIMCON_AUTO_ADJ);
//}
//void MenuVideoWallEnSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_VIDEO_WALL());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_1 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_VIDEOWALL_VIDEOWALL_ADJ);
//	OsdSection3ItemPageDraw(_MENU_VIDEOWALL_VIDEOWALL_ADJ);
//}
//void MenuVideoWallReverseSelect(void)
//{
//	SET_OSD_ITEM_INDEX(GET_OSD_REVERSE_SCAN());
//	SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_7 + GET_OSD_ITEM_INDEX());
//	
//	SET_OSD_STATE(_MENU_VIDEOWALL_REVERSE_ADJ);
//	OsdSection3ItemPageDraw(_MENU_VIDEOWALL_REVERSE_ADJ);
//}
#endif

void MenuSection3ItemSelect(void)
{
	BYTE ucPortTemp = 0;
	g_usAdjustValue = GET_OSD_ITEM_INDEX();

	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_INPUT_SOURCE1_ADJ:
			
// #if(_ENABLE_MENU_VGA != _ON)		
// 		#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
// 			if(g_usAdjustValue >= _OSD_INPUT_A0)g_usAdjustValue += 1; 
// 		#else
// 			if(g_usAdjustValue >= _OSD_INPUT_D0)g_usAdjustValue += 2; 
// 		#endif
// #else
// 			if(g_usAdjustValue >= _OSD_INPUT_A0)g_usAdjustValue += 1; 
// #endif	

/*
			_OSD_INPUT_AUTO = 0,
			_OSD_INPUT_A0,	// VGA 1
			_OSD_INPUT_D0,	// DP2 2
			_OSD_INPUT_D1,	// DP1 3
			_OSD_INPUT_D2,	// HDMI2 4
			_OSD_INPUT_D3,	// HDMI1 5
*/			
			if(GET_OSD_INPUT_PORT_OSD_ITEM() != g_usAdjustValue)	
			{
				//SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);
				//g_usBackupValue = g_usAdjustValue;		
				//MenuSourceSelect(); 
				DirectSourceSelect();
				OsdDispNumberAndText(_MENU_INPUT_SOURCE1, GET_OSD_INPUT_PORT_OSD_ITEM(), COLOR(_CP_WHITE, _CP_BG));
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}

			break;

		case _MENU_PICTURE_GAMMA_ADJ:

			if(GET_OSD_GAMMA() != g_usAdjustValue)	
			{
				SET_OSD_GAMMA(g_usAdjustValue);
				OsdDispNumberAndText(_MENU_PICTURE_GAMMA, GET_OSD_GAMMA(), COLOR(_CP_WHITE, _CP_BG));
#if(_GAMMA_FUNCTION == _ON)
	            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	            UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
			#if(_MEDICAL_SURGICAL == _ON)
			if (GET_OSD_GAMMA() != _GAMMA_OFF)
			{
				UserAdjustPCM(GET_OSD_PCM_STATUS());
				UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
			}
			#else
	            if(GET_OSD_GAMMA() != _GAMMA_OFF)
	            {
	                UserAdjustGamma(GET_OSD_GAMMA());
	                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	                UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
	            }
#if(((_OGC_SUPPORT == _ON) || (_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)) && (_CONTRAST_SUPPORT == _ON))
	            else
	            {
	                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
	                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	                UserAdjustContrast(GET_OSD_CONTRAST());
	            }
#endif
#endif
#endif			
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
			break;

#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_PICTURE_REGION_ADJ:

			break;
#endif
		case _MENU_COLOR_EFFECT_ADJ:
			SET_OSD_COLOR_EFFECT(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_COLOR_EFFECT, GET_OSD_COLOR_EFFECT(), COLOR(_CP_WHITE, _CP_BG));

#if (_HDR10_SUPPORT == _ON)
			if (UserCommonHDRGetHDR10Status() == _HDR10_ON)
			{
				UserCommonHDRAdjustHDR10ColorEffect();
			}
			else
#endif
			{
#if ((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
				UserAdjustColorEffectMode();
#endif
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;

		case _MENU_COLOR_TEMPERATURE_ADJ:	
			SET_COLOR_TEMP_TYPE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_COLOR_TEMPERATURE, GET_COLOR_TEMP_TYPE(), COLOR(_CP_WHITE, _CP_BG));	
			RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if (_CONTRAST_SUPPORT == _ON)
			UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_COLOR_SURGICAL_ADJ:

			SET_OSD_PCM_STATUS(g_usAdjustValue);
#if (_GAMMA_FUNCTION == _ON)
			UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
			UserAdjustPCM(GET_OSD_PCM_STATUS());
			
			if (GET_OSD_GAMMA() != _GAMMA_OFF)
				UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
#endif
			OsdDispNumberAndText(_MENU_COLOR_SURGICAL, GET_OSD_PCM_STATUS(), COLOR(_CP_WHITE, _CP_BG));
			
#if (_CONTRAST_SUPPORT == _ON)
			UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_COLOR_REGION_ADJ:

			break;
#endif
		case _MENU_SCREEN_OVERSCAN_ADJ:
			if(GET_OSD_OVERSCAN_STATUS() != g_usAdjustValue)	
			{
				SET_OSD_OVERSCAN_STATUS(g_usAdjustValue);
				OsdDispNumberAndText(_MENU_SCREEN_OVERSCAN, GET_OSD_OVERSCAN_STATUS(), COLOR(_CP_WHITE, _CP_BG));
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
			break;
		case _MENU_SCREEN_ASPECT_ADJ:	
			if(GET_OSD_ASPECT_RATIO_TYPE() != g_usAdjustValue)	
			{
				SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
				OsdDispNumberAndText(_MENU_SCREEN_ASPECT, GET_OSD_ASPECT_RATIO_TYPE(), COLOR(_CP_WHITE, _CP_BG));
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
			break;
		case _MENU_SCREEN_MONO_COLOR_ADJ:	
			if(GET_OSD_COLOR_EFFECT() != g_usAdjustValue)
			{
				SET_OSD_COLOR_EFFECT(g_usAdjustValue);
				OsdDispNumberAndText(_MENU_SCREEN_MONO_COLOR, GET_OSD_COLOR_EFFECT(), COLOR(_CP_WHITE, _CP_BG));
			#if(_HDR10_SUPPORT == _ON)
				if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
				{
					UserCommonHDRAdjustHDR10ColorEffect();
				}
				else
			#endif
				{
			#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
					UserAdjustColorEffectMode();
			#endif
			#if (_CONTRAST_SUPPORT == _ON)
				UserAdjustContrast(GET_OSD_CONTRAST());
			#endif
				}
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
				RTDEepromSaveBriCon(SysSourceGetSourceType());
			}
			break;
		case _MENU_SCREEN_ROTATE_ADJ:	
			if(GET_OSD_DISP_ROTATE() != g_usAdjustValue)
			{
				SET_OSD_DISP_ROTATE(g_usAdjustValue);	
				printf("GET_OSD_DISP_ROTATE():%d\r\n",(int)GET_OSD_DISP_ROTATE());
				
				OsdDispNumberAndText(_MENU_SCREEN_ROTATE, GET_OSD_DISP_ROTATE(), COLOR(_CP_WHITE, _CP_BG));
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
			break;

		case _MENU_AUDIO_MUTE_ADJ:
			SET_OSD_VOLUME_MUTE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_AUDIO_MUTE, GET_OSD_VOLUME_MUTE(), COLOR(_CP_WHITE, _CP_BG));
#if (_AUDIO_SUPPORT == _ON)
			UserAdjustAudioMuteSwitch();
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_AUDIO_SOURCE_ADJ:
			/*
#if (_ENABLE_MENU_VGA != _ON)
			if (g_usAdjustValue >= _OSD_AUDIO_SOURCE_ANALOG)
				g_usAdjustValue += 1;
#endif
			SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_AUDIO_SOURCE, GET_OSD_AUDIO_SOURCE(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
			*/
			if(GET_OSD_AUDIO_SOURCE() != g_usAdjustValue)	
			{
				SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
				OsdDispNumberAndText(_MENU_AUDIO_SOURCE, GET_OSD_AUDIO_SOURCE(), COLOR(_CP_WHITE, _CP_BG));
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
			break;
//		case _MENU_DP_OPTION_VERSION_ADJ:
//			SET_OSD_DP_D0_VERSION(g_usAdjustValue);
//			SET_OSD_DP_D1_VERSION(g_usAdjustValue);
//			SetMenuDp2D0Version();
//			SetMenuDp1D1Version();

//			OsdDispNumberAndText(_MENU_DP_OPTION_VERSION, GET_OSD_DP_D0_VERSION(), COLOR(_CP_WHITE, _CP_BG)); // D0-DP2
//			// OsdDispNumberAndText(_MENU_DP_OPTION_VERSION, GET_OSD_DP_D1_VERSION(), COLOR(_CP_WHITE, _CP_BG));	// D1-DP1
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			break;
//		case _MENU_DP_OPTION_MST_ADJ:
//			/*
//			SET_OSD_DP_MST(g_usAdjustValue);
//#if (_DP_MST_SUPPORT == _ON)
//			// ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//			UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());

//			if (GET_PORT_TYPE(SysSourceGetInputPortType(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()))) == _PORT_DP)
//			{
//				UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
//			}
//#endif
//			OsdDispNumberAndText(_MENU_DP_OPTION_MST, GET_OSD_DP_MST(), COLOR(_CP_WHITE, _CP_BG));
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DP_OPTION_RESOLUTION_ADJ:
//			UserCommonNVRamSetSystemData(_DP_EDID_SELECT, g_usAdjustValue);

//#if ((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//			UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
//			UserCommonInterfaceDPSwitchEdid(_D1_INPUT_PORT);
//			UserCommonInterfaceDPSwitchEdid(_D2_INPUT_PORT);
//			UserCommonInterfaceDPSwitchEdid(_D6_INPUT_PORT);
//#endif
//			OsdDispNumberAndText(_MENU_DP_OPTION_RESOLUTION, UserCommonNVRamGetSystemData(_DP_EDID_SELECT), COLOR(_CP_WHITE, _CP_BG));
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//			break;
//		case _MENU_DP_OPTION_CLONE_ADJ:
//			/*
//#if (_MULTI_DISPLAY_MAX != 0x01)
//			if (GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
//			{
//				// g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_CLONE_MODE_MTP(), _OSD_CLONE_MTP_D1, _OSD_CLONE_MTP_OFF, _OFF);
//#if (_ENABLE_MENU_VGA != _ON)
//				if (g_usAdjustValue >= _OSD_CLONE_MTP_A0)
//					g_usAdjustValue += 1;
//#endif
//				SET_OSD_CLONE_MODE_MTP(g_usAdjustValue);
//				OsdDispNumberAndText(_MENU_DP_OPTION_CLONE, GET_OSD_CLONE_MODE_MTP(), COLOR(_CP_WHITE, _CP_BG));
//#if (_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
//				if (GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_OFF)
//				{
//					UserCommonInterfaceCloneModeSwitch(_OFF);
//				}
//				else
//				{
//					UserCommonInterfaceCloneModeSwitch(_ON);
//				}
//#endif
//			}
//			else
//#endif
//			{
//				// g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_CLONE_MODE_1P(), _OSD_CLONE_1P_ON, _OSD_CLONE_1P_OFF, _OFF);
//				SET_OSD_CLONE_MODE_1P(g_usAdjustValue);
//				OsdDispNumberAndText(_MENU_DP_OPTION_CLONE, GET_OSD_CLONE_MODE_1P(), COLOR(_CP_WHITE, _CP_BG));
//#if (_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
//				UserCommonInterfaceCloneModeSwitch(GET_OSD_CLONE_MODE_1P());
//#endif
//			}
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;

		case _MENU_SETUP_POWERSAVE_ADJ:
			SET_OSD_POWERSAVE_TIME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SETUP_POWERSAVE, GET_OSD_POWERSAVE_TIME(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SETUP_KEYLOCK_ADJ:
			SET_OSD_KEYLOCK(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SETUP_KEYLOCK, GET_OSD_KEYLOCK(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			if (GET_OSD_KEYLOCK())
				MenuExit();
			break;
		case _MENU_SETUP_BACKLIGHT_CONTROL_ADJ:
			SET_OSD_BACKLIGHT_CONTROL(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SETUP_BACKLIGHT_CONTROL, GET_OSD_BACKLIGHT_CONTROL(), COLOR(_CP_WHITE, _CP_BG));
			OsdDispNumberAndText(_MENU_SETUP_BACKLIGHT, GET_OSD_BACKLIGHT(), COLOR(_CP_WHITE, _CP_BG));
			UserAdjustBacklight(GET_OSD_BACKLIGHT());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SETUP_RESET_ADJ:
			// SET_OSD_RESET_MODE(g_usAdjustValue);
			if (g_usAdjustValue == _ON)
				OsdUserRestoreConfig();
			break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
		case _MENU_SETUP_STABILIZER_CONTROL_ADJ:
			SET_OSD_STABILIZER(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SETUP_STABILIZER_CONTROL, GET_OSD_STABILIZER(), COLOR(_CP_WHITE, _CP_BG));
			UserAdjustStabilizer(GET_OSD_STABILIZER());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
#endif

		case _MENU_SERVICE_D0NAME_ADJ:
			SET_OSD_D0_NAME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_D0NAME, GET_OSD_D0_NAME(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SERVICE_D1NAME_ADJ:
			SET_OSD_D1_NAME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_D1NAME, GET_OSD_D1_NAME(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SERVICE_D2NAME_ADJ:
			SET_OSD_D2_NAME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_D2NAME, GET_OSD_D2_NAME(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SERVICE_D3NAME_ADJ:
			SET_OSD_D3_NAME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_D3NAME, GET_OSD_D3_NAME(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;

		case _MENU_SERVICE_BACKLIGHT_INVERT_ADJ:
			SET_OSD_BACKLIGHT_INVERT(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_INVERT, GET_OSD_BACKLIGHT_INVERT(), COLOR(_CP_WHITE, _CP_BG));
			UserAdjustBacklight(GET_OSD_BACKLIGHT());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;

		case _MENU_SERVICE_LOGO_ADJ:
			SET_OSD_LOGO_ON(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_LOGO, GET_OSD_LOGO_ON(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
		case _MENU_SERVICE_STABILUX_ADJ:
			break;
#endif
		case _MENU_SERVICE_DP_OPTION_ADJ:	

			SET_OSD_DP_MST(g_usAdjustValue);
			if (GET_OSD_DP_MST() == _MST_OFF)	// Clone
			{
				SET_OSD_CLONE_MODE(_ON);	// Clone ON
				#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
            		UserCommonInterfaceCloneModeSwitch(GET_OSD_CLONE_MODE());
				#endif
			}
			else
			{
				SET_OSD_CLONE_MODE(_OFF);	// Clone OFF
				#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
            		UserCommonInterfaceCloneModeSwitch(GET_OSD_CLONE_MODE());
				#endif
				
				#if(_DP_MST_SUPPORT == _ON)
					UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
					if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
					{
						SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
					}
				#endif
			}
			OsdDispNumberAndText(_MENU_SERVICE_DP_OPTION, GET_OSD_DP_MST(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

			break;
#if (_ENABLE_LIGHT_SENSOR == _ON)
		case _MENU_SERVICE_LIGHTSENSOR_ADJ:
			SET_OSD_LIGHT_SENSOR_STATUS(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_LIGHTSENSOR, GET_OSD_LIGHT_SENSOR_STATUS(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
#endif
#if (_ENABLE_FAN_CONTROL == _ON)
		case _MENU_SERVICE_FAN_OPTION_ADJ:
			SET_OSD_FAN_STATUS(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_FAN_OPTION, GET_OSD_FAN_STATUS(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
#endif
		case _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ:
			// SET_OSD_RESET_MODE(g_usAdjustValue);
			if (g_usAdjustValue == _ON)
				OsdUserBackupConfig();
			break;
		case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ:
			// SET_OSD_RESET_MODE(g_usAdjustValue);
			if (g_usAdjustValue == _ON)
				OsdDispOsdFactoryReset();
			break;

		case _MENU_SERVICE_USERASSIGN_UP_ADJ:
			OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_UP, GET_OSD_USER_ASSIGN_UP(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SERVICE_USERASSIGN_DOWN_ADJ:
			OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_DOWN, GET_OSD_USER_ASSIGN_DOWN(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SERVICE_USERASSIGN_LEFT_ADJ:
			OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_LEFT, GET_OSD_USER_ASSIGN_LEFT(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_SERVICE_USERASSIGN_RIGHT_ADJ:
			OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_RIGHT, GET_OSD_USER_ASSIGN_RIGHT(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
#if (_ENABLE_MENU_OLED == _ON)
		case _MENU_SERVICE_OLED_OFFRS_ADJ:
			if (g_usAdjustValue == _OFFRS_NOW_RUN)
			{
				OsdDispDisableOsd();
				OsdDispOsdMessage(_OSD_DISP_OFF_RS_MSG);
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_OFF_RS_RUN);
				SET_COMP_RUN_RESTART(_ON);
			}
			else
			{
				SET_OSD_OLED_OFFRS_STATUS(g_usAdjustValue);
				OsdDispNumberAndText(_MENU_SERVICE_OLED_OFFRS, GET_OSD_OLED_OFFRS_STATUS(), COLOR(_CP_WHITE, _CP_BG));
				//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
				RTDEepromSaveOsdServiceData();	
			}
			break;
		case _MENU_SERVICE_OLED_JB_ADJ:
			if (g_usAdjustValue == _ON)
			{
				OsdDispDisableOsd();
				OsdDispOsdMessage(_OSD_DISP_JB_MSG);
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_JB_RUN);
				g_usBackupValue = _FALSE;
			}
			break;
		case _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ:
			SET_OSD_OLED_SEQUENCE_TIME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SERVICE_OLED_SEQUENCE_TIME, GET_OSD_OLED_SEQUENCE_TIME(), COLOR(_CP_WHITE, _CP_BG));
			//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			RTDEepromSaveOsdServiceData();	
			break;

#endif
		}
		MenuSection3Exit();
		break;
	}
}

void MenuSourceItemUpDown(void)	
{
	switch(GET_KEYMESSAGE())
	{
		case _UP_KEY_MESSAGE:
			if(GET_OSD_ITEM_INDEX() > _OSD_INPUT_AUTO)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
			else
			#if(_ENABLE_MENU_VGA != _ON)	
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-1);
				#else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-2);
				#endif
			#else
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3);
				#else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-1);
				#endif
			#endif
					
			SetFocus(_MENU_SECTION_SOURCE, _ITEM_4 + GET_OSD_ITEM_INDEX());	
			break;
			
		case _DOWN_KEY_MESSAGE:
			#if(_ENABLE_MENU_VGA != _ON)
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3-1)
				#else
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3-2)
				#endif
			#else
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3)
				#else
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3-1)
				#endif
			#endif
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()+1); 
				else
					SET_OSD_ITEM_INDEX(_OSD_INPUT_AUTO);
	
				
			SetFocus(_MENU_SECTION_SOURCE, _ITEM_4 + GET_OSD_ITEM_INDEX());	
			break;
	}
}
void MenuSection3ItemUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_INPUT_SOURCE1_ADJ:

			if(GET_OSD_ITEM_INDEX() > _OSD_INPUT_AUTO)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1);
			else
			#if(_ENABLE_MENU_VGA != _ON)	
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-1);
				#else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-2);
				#endif
			#else
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3);
				#else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D3-1);
				#endif
			#endif
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_INPUT_SOURCE2_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OSD_INPUT_A0)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
#if (_ENABLE_MENU_VGA != _ON)
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D4 - 1);
#else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D4);
#endif
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_INPUT_SOURCE3_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OSD_INPUT_A0)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
#if (_ENABLE_MENU_VGA != _ON)
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D4 - 1);
#else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D4);
#endif

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_INPUT_SOURCE4_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OSD_INPUT_A0)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
#if (_ENABLE_MENU_VGA != _ON)
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D4 - 1);
#else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_D4);
#endif
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_PICTURE_GAMMA_ADJ:
			if (GET_OSD_ITEM_INDEX() > _GAMMA_OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_GAMMA_DICOM);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;

#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_PICTURE_REGION_ADJ:
			switch (GET_OSD_DISPLAY_MODE())
			{
			case _OSD_DM_1P:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_1P_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_1P_FULL);
				break;
			case _OSD_DM_2P_LR:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_2P_LR_L)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_LR_FULL);
				break;
			case _OSD_DM_2P_TB:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_2P_TB_T)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_TB_FULL);
				break;
			case _OSD_DM_2P_PIP:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_2P_PIP_MAIN)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_PIP_FULL);
				break;
			case _OSD_DM_3P:
/*
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_3P_LT_INSIDE)
				{
					if ((GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_INSIDE) || (GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_OUTSIDE))
						SET_OSD_ITEM_INDEX(_OSD_SR_3P_LT_OUTSIDE);
					else
						SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				}
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_3P_FULL);
*/
				break;
			case _OSD_DM_4P:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_4P_LT_INSIDE)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_4P_FULL);
				break;
			}
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
#endif

		case _MENU_COLOR_EFFECT_ADJ:
			if (GET_OSD_ITEM_INDEX() > _COLOREFFECT_STANDARD)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_COLOREFFECT_VIVID);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_COLOR_GAMMA_ADJ:
			if (GET_OSD_ITEM_INDEX() > _GAMMA_OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_GAMMA_DICOM);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_COLOR_TEMPERATURE_ADJ:
			if (GET_OSD_ITEM_INDEX() > _CT_D56)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_CT_USER);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_COLOR_SURGICAL_ADJ:
			if (GET_OSD_ITEM_INDEX() == _PCM_OSD_NATIVE)
				SET_OSD_ITEM_INDEX(_PCM_OSD_BT709);
			else
				SET_OSD_ITEM_INDEX(_PCM_OSD_NATIVE);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_COLOR_REGION_ADJ:
			switch (GET_OSD_DISPLAY_MODE())
			{
			case _OSD_DM_1P:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_1P_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_1P_FULL);
				break;
			case _OSD_DM_2P_LR:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_2P_LR_L)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_LR_FULL);
				break;
			case _OSD_DM_2P_TB:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_2P_TB_T)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_TB_FULL);
				break;
			case _OSD_DM_2P_PIP:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_2P_PIP_MAIN)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_PIP_FULL);
				break;
			case _OSD_DM_3P:
/*
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_3P_LT_INSIDE)
				{
					if ((GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_INSIDE) || (GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_OUTSIDE))
						SET_OSD_ITEM_INDEX(_OSD_SR_3P_LT_OUTSIDE);
					else
						SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				}
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_3P_FULL);
*/
				break;
			case _OSD_DM_4P:
				if (GET_OSD_ITEM_INDEX() > _OSD_SR_4P_LT_INSIDE)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_4P_FULL);
				break;
			}
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
#endif
		case _MENU_SCREEN_OVERSCAN_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OSD_OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_ASPECT_ADJ:	
			if (GET_OSD_ITEM_INDEX() > _OSD_ASPECT_RATIO_FULL)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_ASPECT_RATIO_ORIGIN);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_MONO_COLOR_ADJ:
			if (GET_OSD_ITEM_INDEX() > _COLOREFFECT_STANDARD)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_COLOREFFECT_NIGHT);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_ROTATE_ADJ:
			if (GET_OSD_ITEM_INDEX() > _DISP_ROTATE_0)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_DISP_ROTATE_180);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
/*
		case _MENU_SCREEN_DISPLAY_MODE_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OSD_DM_1P)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_DM_4P);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_PIP_POSITION_ADJ:
			if (GET_OSD_ITEM_INDEX() > _PIP_POSITON_LT)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_PIP_POSITON_RB);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
*/
//		case _MENU_OSD_ROTATE_ADJ:
//			if (GET_OSD_ITEM_INDEX() > _OSD_ROTATE_DEGREE_0)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
//			else
//				SET_OSD_ITEM_INDEX(_OSD_ROTATE_DEGREE_180);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_OSD_LANGUAGE_ADJ:
//#if (_ENABLE_ENGLIGH_ONLY == _ON)
//			SET_OSD_ITEM_INDEX(_ENGLISH);
//#else
//			if (GET_OSD_ITEM_INDEX() > _ENGLISH)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
//			else
//				SET_OSD_ITEM_INDEX(_CHINESE_T);
//#endif
//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
//			break;
		case _MENU_AUDIO_MUTE_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_AUDIO_SOURCE_ADJ:
			if(GET_OSD_ITEM_INDEX() > _LINE_IN_AUDIO)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()-1); 
			else
				SET_OSD_ITEM_INDEX(_DIGITAL_AUDIO);
			
			SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_4 + GET_OSD_ITEM_INDEX());
/*
			switch (GET_OSD_DISPLAY_MODE())
			{
			case _OSD_DM_1P:
				if (GET_OSD_ITEM_INDEX() > _OSD_AUDIO_SOURCE_ANALOG)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
#if (_ENABLE_MENU_VGA != _ON)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_1 - 1);
#else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_1);
#endif
				break;
			case _OSD_DM_2P_LR:
			case _OSD_DM_2P_TB:
			case _OSD_DM_2P_PIP:
				if (GET_OSD_ITEM_INDEX() > _OSD_AUDIO_SOURCE_ANALOG)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
#if (_ENABLE_MENU_VGA != _ON)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_2 - 1);
#else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_2);
#endif
				break;
			case _OSD_DM_3P:
				if (GET_OSD_ITEM_INDEX() > _OSD_AUDIO_SOURCE_ANALOG)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
#if (_ENABLE_MENU_VGA != _ON)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_4 - 1);
#else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_4);
#endif

#if (_ENABLE_MENU_VGA != _ON)
				if (GET_OSD_ITEM_INDEX() == _OSD_AUDIO_SOURCE_DIGITAL_REGION_1)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_ANALOG);
#else
				if (GET_OSD_ITEM_INDEX() == _OSD_AUDIO_SOURCE_DIGITAL_REGION_2)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_1);
#endif

				break;

			case _OSD_DM_4P:
				if (GET_OSD_ITEM_INDEX() > _OSD_AUDIO_SOURCE_ANALOG)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
				else
#if (_ENABLE_MENU_VGA != _ON)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_4 - 1);
#else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_4);
#endif
				break;
			}
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
*/
			break;
//		case _MENU_DP_OPTION_VERSION_ADJ:
//			if (GET_OSD_ITEM_INDEX() > _DP_VER_1_DOT_1)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
//			else
//				SET_OSD_ITEM_INDEX(_DP_VER_1_DOT_3);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_DP_OPTION_MST_ADJ:
//			if (GET_OSD_ITEM_INDEX() > _OFF)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
//			else
//				SET_OSD_ITEM_INDEX(_MST_D1);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_DP_OPTION_RESOLUTION_ADJ:
//			if (GET_OSD_ITEM_INDEX() > _DP_EDID_1080P)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
//			else
//				SET_OSD_ITEM_INDEX(_DP_EDID_4K2K_60HZ);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_DP_OPTION_CLONE_ADJ:
///*
//#if (_MULTI_DISPLAY_MAX != 0x01)
//			if (GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
//			{
//				if (GET_OSD_ITEM_INDEX() > _OSD_CLONE_MTP_OFF)
//					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
//				else
//#if (_ENABLE_MENU_VGA != _ON)
//					SET_OSD_ITEM_INDEX(_OSD_CLONE_MTP_D3 - 1);
//#else
//					SET_OSD_ITEM_INDEX(_OSD_CLONE_MTP_D3);
//#endif
//			}
//			else
//#endif
//			{
//				if (GET_OSD_ITEM_INDEX() > _OSD_CLONE_1P_OFF)
//					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
//				else
//					SET_OSD_ITEM_INDEX(_OSD_CLONE_1P_ON);
//			}

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
//*/
//			break;

		case _MENU_SETUP_POWERSAVE_ADJ:
			if (GET_OSD_ITEM_INDEX() > _POWER_SAVE_OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_POWER_SAVE_1MIN); // SET_OSD_ITEM_INDEX(_POWER_SAVE_120MIN);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SETUP_KEYLOCK_ADJ:
			if (GET_OSD_ITEM_INDEX() > _KEY_UNLOCK)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_KEY_LOCK);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SETUP_BACKLIGHT_CONTROL_ADJ:
			if (GET_OSD_ITEM_INDEX() > _LINEAR)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_CORVED);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SETUP_RESET_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
		case _MENU_SETUP_STABILIZER_CONTROL_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
#endif
#if (_ENABLE_MENU_VGA == _ON)
		case _MENU_VGA_AUTO_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
#endif
		case _MENU_SERVICE_D0NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() > _SOURCE_NAME_DP)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_PC);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_D1NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() > _SOURCE_NAME_DP1)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_PC);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_D2NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() > _SOURCE_NAME_HDMI)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_PC2);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_D3NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() > _SOURCE_NAME_HDMI)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_DVI);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_7 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_BACKLIGHT_INVERT_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_LOGO_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_DP_OPTION_ADJ:
			if (GET_OSD_ITEM_INDEX() > _MST_OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_MST_D1);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_LIGHTSENSOR_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_FAN_OPTION_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_AUTO);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_USERASSIGN_UP_ADJ:
			if(GET_OSD_USER_ASSIGN_UP() <= _USERASSIGN_NONE)
				SET_OSD_USER_ASSIGN_UP(_USERASSIGN_AMOUNT);
			else
				SET_OSD_USER_ASSIGN_UP(GET_OSD_USER_ASSIGN_UP() - 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_UP_ADJ);
			break;
		case _MENU_SERVICE_USERASSIGN_DOWN_ADJ:
			if(GET_OSD_USER_ASSIGN_DOWN() <= _USERASSIGN_NONE)
				SET_OSD_USER_ASSIGN_DOWN(_USERASSIGN_AMOUNT);
			else
				SET_OSD_USER_ASSIGN_DOWN(GET_OSD_USER_ASSIGN_DOWN() - 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_DOWN_ADJ);
			break;
		case _MENU_SERVICE_USERASSIGN_LEFT_ADJ:
			if(GET_OSD_USER_ASSIGN_LEFT() <= _USERASSIGN_NONE)
				SET_OSD_USER_ASSIGN_LEFT(_USERASSIGN_AMOUNT);
			else
				SET_OSD_USER_ASSIGN_LEFT(GET_OSD_USER_ASSIGN_LEFT() - 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_LEFT_ADJ);
			break;
		case _MENU_SERVICE_USERASSIGN_RIGHT_ADJ:
			if(GET_OSD_USER_ASSIGN_RIGHT() <= _USERASSIGN_NONE)
				SET_OSD_USER_ASSIGN_RIGHT(_USERASSIGN_AMOUNT);
			else
				SET_OSD_USER_ASSIGN_RIGHT(GET_OSD_USER_ASSIGN_RIGHT() - 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_RIGHT_ADJ);
			break;
#if (_ENABLE_MENU_OLED == _ON)
		case _MENU_SERVICE_OLED_OFFRS_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFFRS_AUTO)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_OFFRS_NOW_RUN);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_OLED_JB_ADJ:
			if (GET_OSD_ITEM_INDEX() > _OFF)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_ON);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ:
			if (GET_OSD_ITEM_INDEX() > _POWER_SAVE_30SEC)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
			else
				SET_OSD_ITEM_INDEX(_POWER_SAVE_120MIN);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX() - _POWER_SAVE_30SEC);
			break;
#endif
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_INPUT_SOURCE1_ADJ:
/*
#if (_ENABLE_MENU_VGA != _ON)
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4 - 1)
#else
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4)
#endif
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_A0);
*/
			#if(_ENABLE_MENU_VGA != _ON)
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3-1)
				#else
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3-2)
				#endif
			#else
				#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3)
				#else
				if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_D3-1)
				#endif
			#endif
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()+1); 
				else
					SET_OSD_ITEM_INDEX(_OSD_INPUT_AUTO);
				
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_INPUT_SOURCE2_ADJ:
#if (_ENABLE_MENU_VGA != _ON)
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4 - 1)
#else
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4)
#endif
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_A0);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_INPUT_SOURCE3_ADJ:
#if (_ENABLE_MENU_VGA != _ON)
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4 - 1)
#else
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4)
#endif
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_A0);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_INPUT_SOURCE4_ADJ:
#if (_ENABLE_MENU_VGA != _ON)
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4 - 1)
#else
			if (GET_OSD_ITEM_INDEX() < _OSD_INPUT_D4)
#endif
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_INPUT_A0);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_PICTURE_GAMMA_ADJ:
			if (GET_OSD_ITEM_INDEX() < _GAMMA_DICOM)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_GAMMA_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_PICTURE_REGION_ADJ:
			switch (GET_OSD_DISPLAY_MODE())
			{
			case _OSD_DM_1P:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_1P_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_1P_FULL);
				break;
			case _OSD_DM_2P_LR:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_2P_LR_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_LR_L);
				break;
			case _OSD_DM_2P_TB:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_2P_TB_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_TB_T);
				break;
			case _OSD_DM_2P_PIP:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_2P_PIP_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_PIP_MAIN);
				break;
			case _OSD_DM_3P:
/*
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_3P_FULL)
				{
					if ((GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_INSIDE) || (GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_OUTSIDE))
						SET_OSD_ITEM_INDEX(_OSD_SR_3P_RT_INSIDE);
					else
						SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				}
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_3P_LT_INSIDE);
				break;
*/
			case _OSD_DM_4P:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_4P_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_4P_LT_INSIDE);
				break;
			}
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
#endif
		case _MENU_COLOR_EFFECT_ADJ:
			if (GET_OSD_ITEM_INDEX() < _COLOREFFECT_VIVID)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_COLOREFFECT_STANDARD);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_COLOR_GAMMA_ADJ:
			if (GET_OSD_ITEM_INDEX() < _GAMMA_DICOM)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_GAMMA_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_COLOR_TEMPERATURE_ADJ:
			if (GET_OSD_ITEM_INDEX() < _CT_USER)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_CT_D56);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_COLOR_SURGICAL_ADJ:
			if (GET_OSD_ITEM_INDEX() == _PCM_OSD_BT709)
				SET_OSD_ITEM_INDEX(_PCM_OSD_NATIVE);
			else
				SET_OSD_ITEM_INDEX(_PCM_OSD_BT709);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_COLOR_REGION_ADJ:
			switch (GET_OSD_DISPLAY_MODE())
			{
			case _OSD_DM_1P:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_1P_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_1P_FULL);
				break;
			case _OSD_DM_2P_LR:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_2P_LR_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_LR_L);
				break;
			case _OSD_DM_2P_TB:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_2P_TB_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_TB_T);
				break;
			case _OSD_DM_2P_PIP:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_2P_PIP_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_2P_PIP_MAIN);
				break;
			case _OSD_DM_3P:
/*
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_3P_FULL)
				{
					if ((GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_INSIDE) || (GET_OSD_ITEM_INDEX() == _OSD_SR_3P_LB_OUTSIDE))
						SET_OSD_ITEM_INDEX(_OSD_SR_3P_RT_INSIDE);
					else
						SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				}
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_3P_LT_INSIDE);
*/
				break;

			case _OSD_DM_4P:
				if (GET_OSD_ITEM_INDEX() < _OSD_SR_4P_FULL)
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_SR_4P_LT_INSIDE);
				break;
			}
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
#endif
		case _MENU_SCREEN_OVERSCAN_ADJ:
			if (GET_OSD_ITEM_INDEX() < _OSD_ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_ASPECT_ADJ:	
			if (GET_OSD_ITEM_INDEX() < _OSD_ASPECT_RATIO_ORIGIN)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_ASPECT_RATIO_FULL);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_MONO_COLOR_ADJ:
			if (GET_OSD_ITEM_INDEX() < _COLOREFFECT_NIGHT)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_COLOREFFECT_STANDARD);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_ROTATE_ADJ:
			if (GET_OSD_ITEM_INDEX() < _DISP_ROTATE_180)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_DISP_ROTATE_0);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
/*
		case _MENU_SCREEN_DISPLAY_MODE_ADJ:
			if (GET_OSD_ITEM_INDEX() < _OSD_DM_4P)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OSD_DM_1P);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SCREEN_PIP_POSITION_ADJ:
			if (GET_OSD_ITEM_INDEX() < _PIP_POSITON_RB)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_PIP_POSITON_LT);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
*/
//		case _MENU_OSD_ROTATE_ADJ:
//			if (GET_OSD_ITEM_INDEX() < _OSD_ROTATE_DEGREE_180)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
//			else
//				SET_OSD_ITEM_INDEX(_OSD_ROTATE_DEGREE_0);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_OSD_LANGUAGE_ADJ:
//#if (_ENABLE_ENGLIGH_ONLY == _ON)
//			SET_OSD_ITEM_INDEX(_ENGLISH);
//#else
//			if (GET_OSD_ITEM_INDEX() < _CHINESE_T)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
//			else
//				SET_OSD_ITEM_INDEX(_ENGLISH);
//#endif

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
//			break;
		case _MENU_AUDIO_MUTE_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_AUDIO_SOURCE_ADJ:
			if(GET_OSD_ITEM_INDEX() < _DIGITAL_AUDIO)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX()+1); 
			else
				SET_OSD_ITEM_INDEX(_LINE_IN_AUDIO);
					
			SetFocus(_MENU_SECTION_2, ROW_OFFSET+_ITEM_4 + GET_OSD_ITEM_INDEX());
/*
			switch (GET_OSD_DISPLAY_MODE())
			{
			case _OSD_DM_1P:
#if (_ENABLE_MENU_VGA != _ON)
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_1 - 1)
#else
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_1)
#endif
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_ANALOG);
				break;
			case _OSD_DM_2P_LR:
			case _OSD_DM_2P_TB:
			case _OSD_DM_2P_PIP:
#if (_ENABLE_MENU_VGA != _ON)
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_2 - 1)
#else
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_2)
#endif
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_ANALOG);
				break;
			case _OSD_DM_3P:
#if (_ENABLE_MENU_VGA != _ON)
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_4 - 1)
#else
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_4)
#endif
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_ANALOG);

#if (_ENABLE_MENU_VGA != _ON)
				if (GET_OSD_ITEM_INDEX() == _OSD_AUDIO_SOURCE_DIGITAL_REGION_1)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_2);
#else
				if (GET_OSD_ITEM_INDEX() == _OSD_AUDIO_SOURCE_DIGITAL_REGION_2)
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_DIGITAL_REGION_3);
#endif
				break;
			case _OSD_DM_4P:
#if (_ENABLE_MENU_VGA != _ON)
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_4 - 1)
#else
				if (GET_OSD_ITEM_INDEX() < _OSD_AUDIO_SOURCE_DIGITAL_REGION_4)
#endif
					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
				else
					SET_OSD_ITEM_INDEX(_OSD_AUDIO_SOURCE_ANALOG);
				break;
			}
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
*/
			break;

//		case _MENU_DP_OPTION_VERSION_ADJ:
//			if (GET_OSD_ITEM_INDEX() < _DP_VER_1_DOT_3)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
//			else
//				SET_OSD_ITEM_INDEX(_DP_VER_1_DOT_1);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_DP_OPTION_MST_ADJ:
//			if (GET_OSD_ITEM_INDEX() < _MST_D1)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
//			else
//				SET_OSD_ITEM_INDEX(_OFF);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_DP_OPTION_RESOLUTION_ADJ:
//			if (GET_OSD_ITEM_INDEX() < _DP_EDID_4K2K_60HZ)
//				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
//			else
//				SET_OSD_ITEM_INDEX(_DP_EDID_1080P);

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
//			break;
//		case _MENU_DP_OPTION_CLONE_ADJ:
///*
//#if (_MULTI_DISPLAY_MAX != 0x01)
//			if (GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
//			{
//#if (_ENABLE_MENU_VGA != _ON)
//				if (GET_OSD_ITEM_INDEX() < _OSD_CLONE_MTP_D3 - 1)
//#else
//				if (GET_OSD_ITEM_INDEX() < _OSD_CLONE_MTP_D3)
//#endif
//					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
//				else
//					SET_OSD_ITEM_INDEX(_OSD_CLONE_MTP_OFF);
//			}
//			else
//#endif
//			{
//				if (GET_OSD_ITEM_INDEX() < _OSD_CLONE_1P_ON)
//					SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
//				else
//					SET_OSD_ITEM_INDEX(_OSD_CLONE_1P_OFF);
//			}

//			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
//*/
//			break;

		case _MENU_SETUP_POWERSAVE_ADJ:
			if (GET_OSD_ITEM_INDEX() < _POWER_SAVE_1MIN) // if(GET_OSD_ITEM_INDEX() < _POWER_SAVE_120MIN)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_POWER_SAVE_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SETUP_KEYLOCK_ADJ:
			if (GET_OSD_ITEM_INDEX() < _KEY_LOCK)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_KEY_UNLOCK);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SETUP_BACKLIGHT_CONTROL_ADJ:
			if (GET_OSD_ITEM_INDEX() < _CORVED)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_LINEAR);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SETUP_RESET_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
		case _MENU_SETUP_STABILIZER_CONTROL_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
#endif
#if (_ENABLE_MENU_VGA == _ON)
		case _MENU_VGA_AUTO_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
#endif
		case _MENU_SERVICE_D0NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() < _SOURCE_NAME_PC)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_DP1);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_4 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_D1NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() < _SOURCE_NAME_PC)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_DP1);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_D2NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() < _SOURCE_NAME_PC2)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_HDMI1);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_D3NAME_ADJ:
			if (GET_OSD_ITEM_INDEX() < _SOURCE_NAME_DVI)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_SOURCE_NAME_HDMI1);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_7 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_BACKLIGHT_INVERT_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_LOGO_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_DP_OPTION_ADJ:
			if (GET_OSD_ITEM_INDEX() < _MST_D1)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_MST_OFF);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_LIGHTSENSOR_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_FAN_OPTION_ADJ:
			if (GET_OSD_ITEM_INDEX() < _AUTO)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_5 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_6 + GET_OSD_ITEM_INDEX());
			break;

		case _MENU_SERVICE_USERASSIGN_UP_ADJ:
			if(GET_OSD_USER_ASSIGN_UP() >= _USERASSIGN_AMOUNT)
				SET_OSD_USER_ASSIGN_UP(_USERASSIGN_NONE);
			else
				SET_OSD_USER_ASSIGN_UP(GET_OSD_USER_ASSIGN_UP() + 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_UP_ADJ);
			break;
		case _MENU_SERVICE_USERASSIGN_DOWN_ADJ:
			if(GET_OSD_USER_ASSIGN_DOWN() >= _USERASSIGN_AMOUNT)
				SET_OSD_USER_ASSIGN_DOWN(_USERASSIGN_NONE);
			else
				SET_OSD_USER_ASSIGN_DOWN(GET_OSD_USER_ASSIGN_DOWN() + 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_DOWN_ADJ);
			break;
		case _MENU_SERVICE_USERASSIGN_LEFT_ADJ:
			if(GET_OSD_USER_ASSIGN_LEFT() >= _USERASSIGN_AMOUNT)
				SET_OSD_USER_ASSIGN_LEFT(_USERASSIGN_NONE);
			else
				SET_OSD_USER_ASSIGN_LEFT(GET_OSD_USER_ASSIGN_LEFT() + 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_LEFT_ADJ);
			break;
		case _MENU_SERVICE_USERASSIGN_RIGHT_ADJ:
			if(GET_OSD_USER_ASSIGN_RIGHT() >= _USERASSIGN_AMOUNT)
				SET_OSD_USER_ASSIGN_RIGHT(_USERASSIGN_NONE);
			else
				SET_OSD_USER_ASSIGN_RIGHT(GET_OSD_USER_ASSIGN_RIGHT() + 1);

			OsdSection3ItemPageDraw(_MENU_SERVICE_USERASSIGN_RIGHT_ADJ);
			break;
#if (_ENABLE_MENU_OLED == _ON)
		case _MENU_SERVICE_OLED_OFFRS_ADJ:
			if (GET_OSD_ITEM_INDEX() < _OFFRS_NOW_RUN)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFFRS_AUTO);

			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_1 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_OLED_JB_ADJ:
			if (GET_OSD_ITEM_INDEX() < _ON)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_OFF);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_2 + GET_OSD_ITEM_INDEX());
			break;
		case _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ:
			if (GET_OSD_ITEM_INDEX() < _POWER_SAVE_120MIN)
				SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
			else
				SET_OSD_ITEM_INDEX(_POWER_SAVE_30SEC);
			SetFocus(_MENU_SECTION_2, ROW_OFFSET + _ITEM_3 + GET_OSD_ITEM_INDEX() - _POWER_SAVE_30SEC);
			break;
#endif
		}
		break;
	}
}


void MenuInputSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_INPUT_SOURCE1:
			if ((GET_OSD_DISPLAY_MODE() == _OSD_DM_4P) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P))
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE4);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			}
			else if ((GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE2);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			}
			break;
		case _MENU_INPUT_SOURCE2:
			SET_OSD_STATE(_MENU_INPUT_SOURCE1);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_INPUT_SOURCE3:
			if (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P)
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE1);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			}
			else
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE2);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			}
			break;
		case _MENU_INPUT_SOURCE4:
			SET_OSD_STATE(_MENU_INPUT_SOURCE3);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_INPUT_SOURCE1:
			if ((GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_4P))
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE2);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			}
			else if (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P)
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE3);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			}
			break;
		case _MENU_INPUT_SOURCE2:
			if ((GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE1);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			}
			else if (GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
			{
				SET_OSD_STATE(_MENU_INPUT_SOURCE3);
				SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			}
			break;

		case _MENU_INPUT_SOURCE3:
			SET_OSD_STATE(_MENU_INPUT_SOURCE4);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);

			break;

		case _MENU_INPUT_SOURCE4:
			SET_OSD_STATE(_MENU_INPUT_SOURCE1);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
	}
}
/*
void MenuPictureSubUpDown(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _UP_KEY_MESSAGE:
			switch(GET_OSD_STATE())
			{
#if(_ENABLE_MENU_REGION == _ON)
	#if(_ENABLE_MENU_OVERSCAN == _ON)
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_REGION);	
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);	
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_PICTURE_OVERSCAN:
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);
					SetFocus(_MENU_SECTION_1,ROW_OFFSET+ _ITEM_4);
					break;	
				case _MENU_PICTURE_REGION:	
					SET_OSD_STATE(_MENU_PICTURE_OVERSCAN);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
					break;
	#else
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_REGION);	
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);		
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_PICTURE_REGION:	
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
	#endif
	
#else

	#if(_ENABLE_MENU_OVERSCAN == _ON)
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_OVERSCAN);	
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);		
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;	
				case _MENU_PICTURE_OVERSCAN:
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);
					SetFocus(_MENU_SECTION_1,ROW_OFFSET+ _ITEM_4);
					break;	
	#else
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);	
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);		
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;	
	#endif
#endif
			}
			break;

		case _DOWN_KEY_MESSAGE:
			switch(GET_OSD_STATE())
			{
#if(_ENABLE_MENU_REGION == _ON)
	#if(_ENABLE_MENU_OVERSCAN == _ON)
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_OVERSCAN);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
					break;	
				case _MENU_PICTURE_OVERSCAN:
					SET_OSD_STATE(_MENU_PICTURE_REGION);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
					break;
				case _MENU_PICTURE_REGION:	
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
	#else
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_REGION);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
					break;	
				case _MENU_PICTURE_REGION:	
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
	#endif

#else

	#if(_ENABLE_MENU_OVERSCAN == _ON)
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_OVERSCAN);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
					break;	
				case _MENU_PICTURE_OVERSCAN:
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
	#else
				case _MENU_PICTURE_BRIGHTNESS:
					SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_PICTURE_CONTRAST:
					SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_PICTURE_SHARPNESS:
					SET_OSD_STATE(_MENU_PICTURE_ASPECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
				case _MENU_PICTURE_ASPECT:
					SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;	
	#endif
#endif
			}
			break;
			
	}
}
*/
void MenuPictureSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_PICTURE_BLACKLEVEL:
			SET_OSD_STATE(_MENU_PICTURE_REGION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_PICTURE_CONTRAST:
			SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_PICTURE_CHROMA:
			SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_PICTURE_SHARPNESS:
			SET_OSD_STATE(_MENU_PICTURE_CHROMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_PICTURE_GAMMA:
			SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_PICTURE_RESETTODEFAULT:
			SET_OSD_STATE(_MENU_PICTURE_GAMMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_PICTURE_REGION:
			SET_OSD_STATE(_MENU_PICTURE_OVERSCAN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
#else
		case _MENU_PICTURE_BLACKLEVEL:
			SET_OSD_STATE(_MENU_PICTURE_RESETTODEFAULT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_PICTURE_CONTRAST:
			SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_PICTURE_CHROMA:
			SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_PICTURE_SHARPNESS:
			SET_OSD_STATE(_MENU_PICTURE_CHROMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_PICTURE_GAMMA:
			SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_PICTURE_RESETTODEFAULT:
			SET_OSD_STATE(_MENU_PICTURE_GAMMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
#endif
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_PICTURE_BLACKLEVEL:
			SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_PICTURE_CONTRAST:
			SET_OSD_STATE(_MENU_PICTURE_CHROMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_PICTURE_CHROMA:
			SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_PICTURE_SHARPNESS:
			SET_OSD_STATE(_MENU_PICTURE_GAMMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_PICTURE_GAMMA:
			SET_OSD_STATE(_MENU_PICTURE_RESETTODEFAULT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_PICTURE_RESETTODEFAULT:
			SET_OSD_STATE(_MENU_PICTURE_GAMMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_PICTURE_REGION:
			SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
#else
		case _MENU_PICTURE_BLACKLEVEL:
			SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_PICTURE_CONTRAST:
			SET_OSD_STATE(_MENU_PICTURE_CHROMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_PICTURE_CHROMA:
			SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_PICTURE_SHARPNESS:
			SET_OSD_STATE(_MENU_PICTURE_GAMMA);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_PICTURE_GAMMA:
			SET_OSD_STATE(_MENU_PICTURE_RESETTODEFAULT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_PICTURE_RESETTODEFAULT:
			SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
#endif
		}
		break;
	}
}
/*
void MenuColorSubUpDown(void)	
{
	switch(GET_KEYMESSAGE())
	{
		case _UP_KEY_MESSAGE:
			switch(GET_OSD_STATE())
			{
#if(_ENABLE_MENU_REGION == _ON)
				case _MENU_COLOR_EFFECT:
					if(GET_COLOR_TEMP_TYPE()==_CT_USER)
					{
						SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_8);	
					}else
					{
						SET_OSD_STATE(_MENU_COLOR_REGION);
						SetFocus(_MENU_SECTION_1,ROW_OFFSET+_ITEM_4);
					}
					break;
				case _MENU_COLOR_GAMMA:
					SET_OSD_STATE(_MENU_COLOR_EFFECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_COLOR_TEMPERATURE:
					SET_OSD_STATE(_MENU_COLOR_GAMMA);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;	
				case _MENU_COLOR_REGION:
					SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;	
				case _MENU_COLOR_TEMP_USER_R:
					SET_OSD_STATE(_MENU_COLOR_REGION);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;	
				case _MENU_COLOR_TEMP_USER_G:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
					break;	
				case _MENU_COLOR_TEMP_USER_B:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);
					break;	
#else
				case _MENU_COLOR_EFFECT:
					if(GET_COLOR_TEMP_TYPE()==_CT_USER)
					{
						SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_8);	
					}else
					{
						SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					}
					break;
				case _MENU_COLOR_GAMMA:
					SET_OSD_STATE(_MENU_COLOR_EFFECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_COLOR_TEMPERATURE:
					SET_OSD_STATE(_MENU_COLOR_GAMMA);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;	
				case _MENU_COLOR_TEMP_USER_R:
					SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;	
				case _MENU_COLOR_TEMP_USER_G:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
					break;	
				case _MENU_COLOR_TEMP_USER_B:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);
					break;	
#endif

			}
			break;

		case _DOWN_KEY_MESSAGE:
			switch(GET_OSD_STATE())
			{
#if(_ENABLE_MENU_REGION == _ON)
				case _MENU_COLOR_EFFECT:
					SET_OSD_STATE(_MENU_COLOR_GAMMA);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_COLOR_GAMMA:
					SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_COLOR_TEMPERATURE:
					SET_OSD_STATE(_MENU_COLOR_REGION);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
				case _MENU_COLOR_REGION:
					if(GET_COLOR_TEMP_TYPE()==_CT_USER)
					{
						SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
					}else
					{
						SET_OSD_STATE(_MENU_COLOR_EFFECT);
						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					}
					break;
				case _MENU_COLOR_TEMP_USER_R:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);
					break;	
				case _MENU_COLOR_TEMP_USER_G:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_8);
					break;
				case _MENU_COLOR_TEMP_USER_B:
					SET_OSD_STATE(_MENU_COLOR_EFFECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
#else
				case _MENU_COLOR_EFFECT:
					SET_OSD_STATE(_MENU_COLOR_GAMMA);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_COLOR_GAMMA:
					SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_COLOR_TEMPERATURE:
					if(GET_COLOR_TEMP_TYPE()==_CT_USER)
					{
						SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
					}else
					{
						SET_OSD_STATE(_MENU_COLOR_EFFECT);
						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					}
					break;
				case _MENU_COLOR_TEMP_USER_R:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);
					break;	
				case _MENU_COLOR_TEMP_USER_G:
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_8);
					break;
				case _MENU_COLOR_TEMP_USER_B:
					SET_OSD_STATE(_MENU_COLOR_EFFECT);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
#endif
			}
			break;
			
	}
}
*/
void MenuColorSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_COLOR_TEMPERATURE:
			SET_OSD_STATE(_MENU_COLOR_REGION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_8);
			break;
		case _MENU_COLOR_BIAS_R:
			SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_COLOR_BIAS_G:
			SET_OSD_STATE(_MENU_COLOR_BIAS_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_COLOR_BIAS_B:
			SET_OSD_STATE(_MENU_COLOR_BIAS_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_COLOR_GAIN_R:
			SET_OSD_STATE(_MENU_COLOR_BIAS_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_COLOR_GAIN_G:
			SET_OSD_STATE(_MENU_COLOR_GAIN_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_COLOR_GAIN_B:
			SET_OSD_STATE(_MENU_COLOR_GAIN_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_COLOR_REGION:
			SET_OSD_STATE(_MENU_COLOR_GAIN_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
#else
		case _MENU_COLOR_TEMPERATURE:
			SET_OSD_STATE(_MENU_COLOR_GAIN_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_COLOR_SURGICAL:
			SET_OSD_STATE(_MENU_COLOR_GAIN_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_COLOR_BIAS_R:
			SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_COLOR_BIAS_G:
			SET_OSD_STATE(_MENU_COLOR_BIAS_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_COLOR_BIAS_B:
			SET_OSD_STATE(_MENU_COLOR_BIAS_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_COLOR_GAIN_R:
			SET_OSD_STATE(_MENU_COLOR_BIAS_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_COLOR_GAIN_G:
			SET_OSD_STATE(_MENU_COLOR_GAIN_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_COLOR_GAIN_B:
			SET_OSD_STATE(_MENU_COLOR_GAIN_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;

#endif
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
#if (_ENABLE_MENU_REGION == _ON)
		case _MENU_COLOR_TEMPERATURE:
			SET_OSD_STATE(_MENU_COLOR_BIAS_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_COLOR_BIAS_R:
			SET_OSD_STATE(_MENU_COLOR_BIAS_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_COLOR_BIAS_G:
			SET_OSD_STATE(_MENU_COLOR_BIAS_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_COLOR_BIAS_B:
			SET_OSD_STATE(_MENU_COLOR_GAIN_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_COLOR_GAIN_R:
			SET_OSD_STATE(_MENU_COLOR_GAIN_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_COLOR_GAIN_G:
			SET_OSD_STATE(_MENU_COLOR_GAIN_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_COLOR_GAIN_B:
			SET_OSD_STATE(_MENU_COLOR_REGION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_8);
			break;
		case _MENU_COLOR_REGION:
			SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
#else
		case _MENU_COLOR_TEMPERATURE:
			SET_OSD_STATE(_MENU_COLOR_BIAS_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_COLOR_SURGICAL:
			SET_OSD_STATE(_MENU_COLOR_BIAS_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_COLOR_BIAS_R:
			SET_OSD_STATE(_MENU_COLOR_BIAS_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_COLOR_BIAS_G:
			SET_OSD_STATE(_MENU_COLOR_BIAS_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_COLOR_BIAS_B:
			SET_OSD_STATE(_MENU_COLOR_GAIN_R);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_COLOR_GAIN_R:
			SET_OSD_STATE(_MENU_COLOR_GAIN_G);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_COLOR_GAIN_G:
			SET_OSD_STATE(_MENU_COLOR_GAIN_B);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_COLOR_GAIN_B:
			SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;

#endif
		}
		break;
	}
}

void MenuScreenSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SCREEN_OVERSCAN:
			SET_OSD_STATE(_MENU_SCREEN_ROTATE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SCREEN_ASPECT:
			SET_OSD_STATE(_MENU_SCREEN_OVERSCAN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SCREEN_MONO_COLOR:
			SET_OSD_STATE(_MENU_SCREEN_ASPECT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SCREEN_ROTATE:
			SET_OSD_STATE(_MENU_SCREEN_MONO_COLOR);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		/*	
		case _MENU_SCREEN_DISPLAY_MODE:
			SET_OSD_STATE(_MENU_SCREEN_ROTATE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SCREEN_PIP_POSITION:
			SET_OSD_STATE(_MENU_SCREEN_DISPLAY_MODE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SCREEN_PIP_SIZE:
			SET_OSD_STATE(_MENU_SCREEN_PIP_POSITION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		*/
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SCREEN_OVERSCAN:
			SET_OSD_STATE(_MENU_SCREEN_ASPECT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SCREEN_ASPECT:
			SET_OSD_STATE(_MENU_SCREEN_MONO_COLOR);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SCREEN_MONO_COLOR:
			SET_OSD_STATE(_MENU_SCREEN_ROTATE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SCREEN_ROTATE:
			SET_OSD_STATE(_MENU_SCREEN_OVERSCAN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		/*	
		case _MENU_SCREEN_DISPLAY_MODE:
			SET_OSD_STATE(_MENU_SCREEN_PIP_POSITION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SCREEN_PIP_POSITION:
			SET_OSD_STATE(_MENU_SCREEN_PIP_SIZE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_SCREEN_PIP_SIZE:
			SET_OSD_STATE(_MENU_SCREEN_OVERSCAN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		*/	
		}
		break;
	}
}

//void MenuDisplaySubUpDown(void)	
//{
//	switch(GET_KEYMESSAGE())
//	{
//		case _UP_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_DISPLAY_ROTATE:
//					SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//			
//				case _MENU_DISPLAY_SOURCE1:
//					SET_OSD_STATE(_MENU_DISPLAY_ROTATE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//					
//				case _MENU_DISPLAY_SOURCE2:
//					break;
//				case _MENU_DISPLAY_SOURCE3:
//					break;
//				case _MENU_DISPLAY_SOURCE4:
//					break;
//				case _MENU_DISPLAY_MODE:
//					break;
//				case _MENU_DISPLAY_PIP_POSITION:
//					break;
//				case _MENU_DISPLAY_PIP_SIZE:
//					break;
//				case _MENU_DISPLAY_INPUT_SWAP:
//					break;	
//				/*
//				case _MENU_DISPLAY_ROTATE:			
//					if((GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_LR)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_TB)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_PIP))
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_INPUT_SWAP);	
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_9);		
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_MODE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					}
//					break;
//				case _MENU_DISPLAY_SOURCE1:
//					if(GET_OSD_DISPLAY_MODE()==_OSD_DM_1P)	
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_ROTATE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					}
//					else
//					{
//						if((GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_LR)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_TB)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_PIP))
//						{
//							SET_OSD_STATE(_MENU_DISPLAY_INPUT_SWAP);	
//							SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_9);	
//						}
//						else
//						{
//							SET_OSD_STATE(_MENU_DISPLAY_MODE);
//							SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//						}
//					}
//					break;
//				case _MENU_DISPLAY_SOURCE2:
//					SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_DISPLAY_SOURCE3:
//					SET_OSD_STATE(_MENU_DISPLAY_SOURCE2);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_DISPLAY_SOURCE4:
//					SET_OSD_STATE(_MENU_DISPLAY_SOURCE3);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_DISPLAY_MODE:
//					if(GET_OSD_DISPLAY_MODE()==_OSD_DM_4P)	
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE4);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					}
//					else if(GET_OSD_DISPLAY_MODE()==_OSD_DM_3P)
//					{

//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE3);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					}
//					else if((GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_LR)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_TB)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_PIP))
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE2);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					}
//					else if(GET_OSD_DISPLAY_MODE()==_OSD_DM_1P)
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);	
//					}
//					break;
//				case _MENU_DISPLAY_PIP_POSITION:
//					SET_OSD_STATE(_MENU_DISPLAY_MODE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					break;
//				case _MENU_DISPLAY_PIP_SIZE:
//					SET_OSD_STATE(_MENU_DISPLAY_PIP_POSITION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);
//					break;
//				case _MENU_DISPLAY_INPUT_SWAP:	
//					if(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_PIP)
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_PIP_SIZE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_8);
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_MODE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					}
//					break;
//				*/
//			}
//			break;
//			
//		case _DOWN_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_DISPLAY_ROTATE:
//					SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//			
//				case _MENU_DISPLAY_SOURCE1:
//					SET_OSD_STATE(_MENU_DISPLAY_ROTATE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//					
//				case _MENU_DISPLAY_SOURCE2:
//					break;
//				case _MENU_DISPLAY_SOURCE3:
//					break;
//				case _MENU_DISPLAY_SOURCE4:
//					break;
//				case _MENU_DISPLAY_MODE:
//					break;
//				case _MENU_DISPLAY_PIP_POSITION:
//					break;
//				case _MENU_DISPLAY_PIP_SIZE:
//					break;
//				case _MENU_DISPLAY_INPUT_SWAP:
//					break;	
//					
//				/*
//				case _MENU_DISPLAY_ROTATE:
//					SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//			
//				case _MENU_DISPLAY_SOURCE1:
//					if((GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_LR)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_TB)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_PIP)	
//						||(GET_OSD_DISPLAY_MODE()==_OSD_DM_3P)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_4P))
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE2);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_MODE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					}
//					break;
//				case _MENU_DISPLAY_SOURCE2:
//					if((GET_OSD_DISPLAY_MODE()==_OSD_DM_3P)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_4P))
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE3);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_MODE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					}
//					break;
//					
//				case _MENU_DISPLAY_SOURCE3:
//					if(GET_OSD_DISPLAY_MODE()==_OSD_DM_4P)
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE4);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_MODE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					}
//					break;
//					
//				case _MENU_DISPLAY_SOURCE4:
//					SET_OSD_STATE(_MENU_DISPLAY_MODE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					break;
//					
//				case _MENU_DISPLAY_MODE:
//					if(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_PIP)
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_PIP_POSITION);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);
//					}
//					else
//					{
//						if((GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_LR)||(GET_OSD_DISPLAY_MODE()==_OSD_DM_2P_TB))
//						{
//							SET_OSD_STATE(_MENU_DISPLAY_INPUT_SWAP);
//							SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_9);
//						}
//						else
//						{
//							if(GET_OSD_DISPLAY_MODE()==_OSD_DM_1P)	
//							{
//								SET_OSD_STATE(_MENU_DISPLAY_ROTATE);
//								SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//							}
//							else
//							{
//								SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//								SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//							}
//						}
//					}
//					break;
//				case _MENU_DISPLAY_PIP_POSITION:
//					SET_OSD_STATE(_MENU_DISPLAY_PIP_SIZE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_8);
//					break;
//				case _MENU_DISPLAY_PIP_SIZE:
//					SET_OSD_STATE(_MENU_DISPLAY_INPUT_SWAP);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_9);
//					break;
//				case _MENU_DISPLAY_INPUT_SWAP:	
//					if(GET_OSD_DISPLAY_MODE()==_OSD_DM_1P)	
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_ROTATE);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					}
//					break;	
//				*/
//				
//			}
//			break;	
//	}
//}

//void MenuOsdSubUpDown(void)
//{
//	switch(GET_KEYMESSAGE())
//	{
//		case _UP_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_OSD_H_POSITION:		
//				SET_OSD_STATE(_MENU_OSD_LANGUAGE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);	
//					break;
//				case _MENU_OSD_V_POSITION:
//					SET_OSD_STATE(_MENU_OSD_H_POSITION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//				case _MENU_OSD_TRANSPARENCY:
//					SET_OSD_STATE(_MENU_OSD_V_POSITION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_OSD_TIMEOUT:
//					SET_OSD_STATE(_MENU_OSD_TRANSPARENCY);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_OSD_ROTATE:
//					SET_OSD_STATE(_MENU_OSD_TIMEOUT);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_OSD_LANGUAGE:
//					SET_OSD_STATE(_MENU_OSD_ROTATE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					break;
//			}
//			break;
//			
//		case _DOWN_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_OSD_H_POSITION:
//					SET_OSD_STATE(_MENU_OSD_V_POSITION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_OSD_V_POSITION:
//					SET_OSD_STATE(_MENU_OSD_TRANSPARENCY);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_OSD_TRANSPARENCY:
//					SET_OSD_STATE(_MENU_OSD_TIMEOUT);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_OSD_TIMEOUT:
//					SET_OSD_STATE(_MENU_OSD_ROTATE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					break;
//				case _MENU_OSD_ROTATE:
//					SET_OSD_STATE(_MENU_OSD_LANGUAGE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					break;
//				case _MENU_OSD_LANGUAGE:
//					SET_OSD_STATE(_MENU_OSD_H_POSITION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//			}
//			break;	
//	}
//}

void MenuAudioVolumeSelect(void)
{
	g_usBackupValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF);
	SetFocus(_MENU_SECTION_1_SUB, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_AUDIO_VOLUME_ADJ);
}

void MenuAudioVolumeAdjExit(void)
{
	SET_OSD_VOLUME(g_usBackupValue);
	OsdDispNumberAndText(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME(), COLOR(_CP_WHITE, _CP_BG));
	if (GET_OSD_VOLUME_MUTE() == _ON)
	{
		SET_OSD_VOLUME_MUTE(_OFF);
	}
#if (_AUDIO_SUPPORT == _ON)
	UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_AUDIO_VOLUME);
}

void MenuAudioVolumAdjSelect(void)
{
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
	SET_OSD_STATE(_MENU_AUDIO_VOLUME);
}

void MenuAudioSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_AUDIO_INFO:
			SET_OSD_STATE(_MENU_AUDIO_MUTE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_AUDIO_VOLUME:
			SET_OSD_STATE(_MENU_AUDIO_INFO);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_AUDIO_MUTE:
			SET_OSD_STATE(_MENU_AUDIO_VOLUME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_AUDIO_INFO:
			SET_OSD_STATE(_MENU_AUDIO_VOLUME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_AUDIO_VOLUME:
			SET_OSD_STATE(_MENU_AUDIO_MUTE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_AUDIO_MUTE:
			SET_OSD_STATE(_MENU_AUDIO_INFO);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
	}
}

//void MenuDpOptionSubUpDown(void)	
//{
//	switch(GET_KEYMESSAGE())
//	{
//		case _UP_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_DP_OPTION_VERSION:			
//					//SET_OSD_STATE(_MENU_DP_OPTION_CLONE_SRC);
//					//SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					SET_OSD_STATE(_MENU_DP_OPTION_CLONE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_DP_OPTION_MST:
//					SET_OSD_STATE(_MENU_DP_OPTION_VERSION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//				case _MENU_DP_OPTION_RESOLUTION:
//					SET_OSD_STATE(_MENU_DP_OPTION_MST);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_DP_OPTION_CLONE:
//					SET_OSD_STATE(_MENU_DP_OPTION_RESOLUTION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_DP_OPTION_CLONE_SRC:		
//					SET_OSD_STATE(_MENU_DP_OPTION_CLONE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//			}
//			break;
//			
//		case _DOWN_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_DP_OPTION_VERSION:
//					SET_OSD_STATE(_MENU_DP_OPTION_MST);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_DP_OPTION_MST:
//					SET_OSD_STATE(_MENU_DP_OPTION_RESOLUTION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_DP_OPTION_RESOLUTION:
//					SET_OSD_STATE(_MENU_DP_OPTION_CLONE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_DP_OPTION_CLONE:
//					//SET_OSD_STATE(_MENU_DP_OPTION_CLONE_SRC);
//					//SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					SET_OSD_STATE(_MENU_DP_OPTION_VERSION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//				case _MENU_DP_OPTION_CLONE_SRC:
//					SET_OSD_STATE(_MENU_DP_OPTION_VERSION);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//			}
//			break;	
//	}
//}
/*
void MenuSetupSubUpDown(void)	
{
	switch(GET_KEYMESSAGE())
	{
		case _UP_KEY_MESSAGE:
			switch(GET_OSD_STATE())			
			{
#if(_ENABLE_MENU_HPD_MODE == _ON)
				case _MENU_SETUP_RESET:			
					SET_OSD_STATE(_MENU_SETUP_HPD_MODE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);	
					break;
				case _MENU_SETUP_POWERSAVE:
					SET_OSD_STATE(_MENU_SETUP_RESET);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_SETUP_SETID:
					SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
			
				case _MENU_SETUP_HPD_MODE:
					SET_OSD_STATE(_MENU_SETUP_SETID);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
#else
				case _MENU_SETUP_RESET:			
					SET_OSD_STATE(_MENU_SETUP_SETID);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);	
					break;
				case _MENU_SETUP_POWERSAVE:
					SET_OSD_STATE(_MENU_SETUP_RESET);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_SETUP_SETID:
					SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
#endif
			}
			break;
			
		case _DOWN_KEY_MESSAGE:
			switch(GET_OSD_STATE())			
			{
#if(_ENABLE_MENU_HPD_MODE == _ON)
				case _MENU_SETUP_RESET:
					SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_SETUP_POWERSAVE:
					SET_OSD_STATE(_MENU_SETUP_SETID);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_SETUP_SETID:
					SET_OSD_STATE(_MENU_SETUP_HPD_MODE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
				case _MENU_SETUP_HPD_MODE:
					SET_OSD_STATE(_MENU_SETUP_RESET);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
#else
				case _MENU_SETUP_RESET:
					SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_SETUP_POWERSAVE:
					SET_OSD_STATE(_MENU_SETUP_SETID);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_SETUP_SETID:
					SET_OSD_STATE(_MENU_SETUP_RESET);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
#endif
			}
			break;	
	}
}
*/
void MenuSetupSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{

		case _MENU_SETUP_POWERSAVE:
			SET_OSD_STATE(_MENU_SETUP_STABILIZER_CONTROL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SETUP_KEYLOCK:
			SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SETUP_BACKLIGHT:
			SET_OSD_STATE(_MENU_SETUP_KEYLOCK);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SETUP_BACKLIGHT_CONTROL:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SETUP_RESET:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT_CONTROL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SETUP_STABILIZER_CONTROL:
			SET_OSD_STATE(_MENU_SETUP_RESET);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SETUP_POWERSAVE:
			SET_OSD_STATE(_MENU_SETUP_KEYLOCK);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SETUP_KEYLOCK:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SETUP_BACKLIGHT:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT_CONTROL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SETUP_BACKLIGHT_CONTROL:
			SET_OSD_STATE(_MENU_SETUP_RESET);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SETUP_RESET:
			SET_OSD_STATE(_MENU_SETUP_STABILIZER_CONTROL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SETUP_STABILIZER_CONTROL:
			SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
#else
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{

		case _MENU_SETUP_POWERSAVE:
			SET_OSD_STATE(_MENU_SETUP_RESET);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SETUP_KEYLOCK:
			SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SETUP_BACKLIGHT:
			SET_OSD_STATE(_MENU_SETUP_KEYLOCK);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SETUP_BACKLIGHT_CONTROL:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SETUP_RESET:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT_CONTROL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SETUP_POWERSAVE:
			SET_OSD_STATE(_MENU_SETUP_KEYLOCK);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SETUP_KEYLOCK:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SETUP_BACKLIGHT:
			SET_OSD_STATE(_MENU_SETUP_BACKLIGHT_CONTROL);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SETUP_BACKLIGHT_CONTROL:
			SET_OSD_STATE(_MENU_SETUP_RESET);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SETUP_RESET:
			SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
#endif
	}
}

#if(_ENABLE_MENU_VGA == _ON)	
void MenuVgaSubUpDown(void)	
{
	switch(GET_KEYMESSAGE())
	{
		case _UP_KEY_MESSAGE:
			switch(GET_OSD_STATE())			
			{
				case _MENU_VGA_AUTO:
					SET_OSD_STATE(_MENU_VGA_PHASE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);	
					break;
				case _MENU_VGA_H_POSI:
					SET_OSD_STATE(_MENU_VGA_AUTO);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
				case _MENU_VGA_V_POSI:
					SET_OSD_STATE(_MENU_VGA_H_POSI);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_VGA_CLOCK:
					SET_OSD_STATE(_MENU_VGA_V_POSI);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_VGA_PHASE:
					SET_OSD_STATE(_MENU_VGA_CLOCK);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
			}
			break;
			
		case _DOWN_KEY_MESSAGE:
			switch(GET_OSD_STATE())			
			{
				case _MENU_VGA_AUTO:
					SET_OSD_STATE(_MENU_VGA_H_POSI);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
					break;
				case _MENU_VGA_H_POSI:
					SET_OSD_STATE(_MENU_VGA_V_POSI);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
					break;
				case _MENU_VGA_V_POSI:
					SET_OSD_STATE(_MENU_VGA_CLOCK);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
					break;
				case _MENU_VGA_CLOCK:
					SET_OSD_STATE(_MENU_VGA_PHASE);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
					break;
				case _MENU_VGA_PHASE:
					SET_OSD_STATE(_MENU_VGA_AUTO);
					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
					break;
			}
			break;	
	}
}
#endif
void MenuService1SubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_SCREENTEST:
			SET_OSD_STATE(_MENU_SERVICE_D3NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_SERVICE_TEMPERATURE:
			SET_OSD_STATE(_MENU_SERVICE_SCREENTEST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SERVICE_WHITEBALANCE:
			SET_OSD_STATE(_MENU_SERVICE_TEMPERATURE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_D0NAME:
			SET_OSD_STATE(_MENU_SERVICE_WHITEBALANCE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_D1NAME:
			SET_OSD_STATE(_MENU_SERVICE_D0NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_D2NAME:
			SET_OSD_STATE(_MENU_SERVICE_D1NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SERVICE_D3NAME:
			SET_OSD_STATE(_MENU_SERVICE_D2NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_SCREENTEST:
			SET_OSD_STATE(_MENU_SERVICE_TEMPERATURE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_TEMPERATURE:
			SET_OSD_STATE(_MENU_SERVICE_WHITEBALANCE);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_WHITEBALANCE:
			SET_OSD_STATE(_MENU_SERVICE_D0NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_D0NAME:
			SET_OSD_STATE(_MENU_SERVICE_D1NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SERVICE_D1NAME:
			SET_OSD_STATE(_MENU_SERVICE_D2NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SERVICE_D2NAME:
			SET_OSD_STATE(_MENU_SERVICE_D3NAME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_7);
			break;
		case _MENU_SERVICE_D3NAME:
			SET_OSD_STATE(_MENU_SERVICE_SCREENTEST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
	}
}

void MenuService2SubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_BACKLIGHT_MIN:
			SET_OSD_STATE(_MENU_SERVICE_STABILUX);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SERVICE_BACKLIGHT_MAX:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SERVICE_BACKLIGHT_INVERT:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MAX);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_BACKLIGHT_FREQ:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_LOGO:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_STABILUX:
			SET_OSD_STATE(_MENU_SERVICE_LOGO);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_BACKLIGHT_MIN:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MAX);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_BACKLIGHT_MAX:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_BACKLIGHT_INVERT:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_BACKLIGHT_FREQ:
			SET_OSD_STATE(_MENU_SERVICE_LOGO);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SERVICE_LOGO:
			SET_OSD_STATE(_MENU_SERVICE_STABILUX);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SERVICE_STABILUX:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
#else
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_BACKLIGHT_MIN:
			SET_OSD_STATE(_MENU_SERVICE_LOGO_LIST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SERVICE_BACKLIGHT_MAX:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SERVICE_BACKLIGHT_INVERT:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MAX);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_BACKLIGHT_FREQ:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_LOGO:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_LOGO_LIST:
			SET_OSD_STATE(_MENU_SERVICE_LOGO);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_BACKLIGHT_MIN:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MAX);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_BACKLIGHT_MAX:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_BACKLIGHT_INVERT:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_BACKLIGHT_FREQ:
			SET_OSD_STATE(_MENU_SERVICE_LOGO);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SERVICE_LOGO:
			SET_OSD_STATE(_MENU_SERVICE_LOGO_LIST);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SERVICE_LOGO_LIST:
			SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
#endif
	}
}

void MenuService3SubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_DP_OPTION:
			SET_OSD_STATE(_MENU_SERVICE_RESTORE_FACTORY_DEFAULT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SERVICE_LIGHTSENSOR:
			SET_OSD_STATE(_MENU_SERVICE_DP_OPTION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SERVICE_FAN_OPTION:
			SET_OSD_STATE(_MENU_SERVICE_LIGHTSENSOR);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_FAN_SPEED:
			SET_OSD_STATE(_MENU_SERVICE_FAN_OPTION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_USER_BACKUP_CONFIG:
			SET_OSD_STATE(_MENU_SERVICE_FAN_SPEED);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT:
			SET_OSD_STATE(_MENU_SERVICE_USER_BACKUP_CONFIG);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_DP_OPTION:
			SET_OSD_STATE(_MENU_SERVICE_LIGHTSENSOR);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_LIGHTSENSOR:
			SET_OSD_STATE(_MENU_SERVICE_FAN_OPTION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_FAN_OPTION:
			SET_OSD_STATE(_MENU_SERVICE_FAN_SPEED);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_FAN_SPEED:
			SET_OSD_STATE(_MENU_SERVICE_USER_BACKUP_CONFIG);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_5);
			break;
		case _MENU_SERVICE_USER_BACKUP_CONFIG:
			SET_OSD_STATE(_MENU_SERVICE_RESTORE_FACTORY_DEFAULT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_6);
			break;
		case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT:
			SET_OSD_STATE(_MENU_SERVICE_DP_OPTION);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
	}
}

void MenuServiceUserAssignSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_USERASSIGN_UP:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_RIGHT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_USERASSIGN_DOWN:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_UP);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SERVICE_USERASSIGN_LEFT:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_DOWN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_USERASSIGN_RIGHT:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_LEFT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_USERASSIGN_UP:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_DOWN);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_USERASSIGN_DOWN:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_LEFT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_USERASSIGN_LEFT:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_RIGHT);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_4);
			break;
		case _MENU_SERVICE_USERASSIGN_RIGHT:
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_UP);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
	}
}


void MenuServiceOledSubUpDown(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_OLED_OFFRS:
			SET_OSD_STATE(_MENU_SERVICE_OLED_SEQUENCE_TIME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_OLED_JB:
			SET_OSD_STATE(_MENU_SERVICE_OLED_OFFRS);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		case _MENU_SERVICE_OLED_SEQUENCE_TIME:
			SET_OSD_STATE(_MENU_SERVICE_OLED_JB);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE_OLED_OFFRS:
			SET_OSD_STATE(_MENU_SERVICE_OLED_JB);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_2);
			break;
		case _MENU_SERVICE_OLED_JB:
			SET_OSD_STATE(_MENU_SERVICE_OLED_SEQUENCE_TIME);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_3);
			break;
		case _MENU_SERVICE_OLED_SEQUENCE_TIME:
			SET_OSD_STATE(_MENU_SERVICE_OLED_OFFRS);
			SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
			break;
		}
		break;
	}
}


void ExcuteUserAssign(BYTE bUserAssign)
{
	DebugMessageOsd("bUserAssign", bUserAssign);
	switch (bUserAssign)
	{

	case _USERASSIGN_CONTRAST:
		HotKeyContrastSelect();
		break;
	case _USERASSIGN_VOLUME:
		HotKeyVolumeSelect();
		break;
	case _USERASSIGN_BACKLIGHT:
		HotKeyBacklightSelect();
		break;
	case _USERASSIGN_MUTE:
		HotKeyMuteSelect();
		break;
	case _USERASSIGN_ROTATE:
		if (GET_OSD_DISP_ROTATE() == _DISP_ROTATE_0)
			SET_OSD_DISP_ROTATE(_DISP_ROTATE_180);
		else
			SET_OSD_DISP_ROTATE(_DISP_ROTATE_0);

		SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
		break;
	case _USERASSIGN_SCAN:
		if (SysModeGetModeState() == _MODE_STATUS_ACTIVE)
		{
			g_usAdjustValue = GET_OSD_ASPECT_RATIO_TYPE() + 1;
			if(g_usAdjustValue > _OSD_ASPECT_RATIO_AMOUNT)
				g_usAdjustValue = _OSD_ASPECT_RATIO_FULL;

			if (g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE())
			{
				SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
#if (_ASPECT_RATIO_SUPPORT == _ON)
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
#endif
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
		}
		break;
	case _USERASSIGN_MONO_COLOR:
			if (GET_OSD_COLOR_EFFECT() > _COLOREFFECT_STANDARD)
				SET_OSD_COLOR_EFFECT(GET_OSD_COLOR_EFFECT() - 1);
			else
				SET_OSD_COLOR_EFFECT(_COLOREFFECT_NIGHT);

#if (_HDR10_SUPPORT == _ON)
			if (UserCommonHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
			{
				UserCommonHDRAdjustHDR10ColorEffect(GET_OSD_SYSTEM_DISPLAY_REGION());
			}
			else
#endif
			{
#if ((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
				UserAdjustColorEffectMode();
#endif
#if (_CONTRAST_SUPPORT == _ON)
				UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _USERASSIGN_MONO:
		if(GET_OSD_COLOR_EFFECT() != _COLOREFFECT_MONO)
		{
			SET_OSD_COLOR_EFFECT(_COLOREFFECT_MONO);
		}
		else
		{
			SET_OSD_COLOR_EFFECT(_COLOREFFECT_STANDARD);
		}
#if (_HDR10_SUPPORT == _ON)
		if (UserCommonHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
		{
			UserCommonHDRAdjustHDR10ColorEffect(GET_OSD_SYSTEM_DISPLAY_REGION());
		}
		else
#endif
		{
#if ((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
			UserAdjustColorEffectMode();
#endif
#if (_CONTRAST_SUPPORT == _ON)
			UserAdjustContrast(GET_OSD_CONTRAST());
#endif
		}
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _USERASSIGN_DP1:
		SET_FORCE_POW_SAV_STATUS(_FALSE);
		SysSourceSwitchInputPort(_D0_INPUT_PORT);
		SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
		SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _USERASSIGN_DP2:
		SET_FORCE_POW_SAV_STATUS(_FALSE);
		SysSourceSwitchInputPort(_D1_INPUT_PORT);
		SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
		SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _USERASSIGN_HDMI1:
		SET_FORCE_POW_SAV_STATUS(_FALSE);
		SysSourceSwitchInputPort(_D2_INPUT_PORT);
		SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
		SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _USERASSIGN_HDMI2:
		SET_FORCE_POW_SAV_STATUS(_FALSE);
		SysSourceSwitchInputPort(_D3_INPUT_PORT);
		SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
		SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	case _USERASSIGN_REDMODE:
		if (GET_OSD_COLOR_EFFECT() != _COLOREFFECT_NIGHT)
			SET_OSD_COLOR_EFFECT(_COLOREFFECT_NIGHT);
		else
			SET_OSD_COLOR_EFFECT(_COLOREFFECT_STANDARD);

		{
#if ((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
			UserAdjustColorEffectMode();
#endif
#if (_CONTRAST_SUPPORT == _ON)
			UserAdjustContrast(GET_OSD_CONTRAST());
#endif
		}
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	default:
		break;
	}
	return;
}

void HotKeyUserAssignSelect(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		ExcuteUserAssign(GET_OSD_USER_ASSIGN_UP());
		break;
	case _DOWN_KEY_MESSAGE:
		ExcuteUserAssign(GET_OSD_USER_ASSIGN_DOWN());
		break;
	case _LEFT_KEY_MESSAGE:
		ExcuteUserAssign(GET_OSD_USER_ASSIGN_LEFT());
		break;
	case _RIGHT_KEY_MESSAGE:
		ExcuteUserAssign(GET_OSD_USER_ASSIGN_RIGHT());
		break;
	}

}

void HotKeyVolumeSelect(void)
{
	OsdDispHotKeyOsdMessage(_MENU_HOTKEY_VOLUME);
	SET_OSD_STATE(_MENU_HOTKEY_VOLUME);
	ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
}

void HotKeyVolumeSubLeftRight(void)
{
	if (GET_OSD_STATE() == _MENU_HOTKEY_VOLUME)
	{
		// switch(GET_KEYMESSAGE())
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF);
		SET_OSD_VOLUME(g_usAdjustValue);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);
		OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));

		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);

		if (GET_OSD_VOLUME_MUTE() == _ON)
		{
			SET_OSD_VOLUME_MUTE(_OFF);
		}
#if (_AUDIO_SUPPORT == _ON)
		UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	}
}


void HotKeyBacklightSelect(void)
{
	OsdDispHotKeyOsdMessage(_MENU_HOTKEY_BACKLIGHT);
	SET_OSD_STATE(_MENU_HOTKEY_BACKLIGHT);
	ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
}
void HotKeyBlkSubLeftRight(void)
{
	if (GET_OSD_STATE() == _MENU_HOTKEY_BACKLIGHT)
	{
		if (GET_OSD_BACKLIGHT_CONTROL() == _ON)
		{
			g_usAdjustValue = GET_OSD_BACKLIGHT();
			g_usAdjustValue = OsdDisplayDetOverRange_Curved(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _OFF);
			SET_OSD_BACKLIGHT(g_usAdjustValue);
			g_usAdjustValue = UserCommonAdjustRealValueToPercentCurved(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			OsdPropShowNumberFloat(ROW(4), COL(10), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_3, COLOR(_CP_WHITE, _CP_BG));
		}
		else
		{
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
			SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
			OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_3, COLOR(_CP_WHITE, _CP_BG));
		}

		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
		OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);

		UserAdjustBacklight(GET_OSD_BACKLIGHT());

		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
	}
}

void HotKeyContrastSelect(void)
{
	DebugMessageOsd("_MENU_HOTKEY_CONTRAST", 0);
	OsdDispHotKeyOsdMessage(_MENU_HOTKEY_CONTRAST);
	SET_OSD_STATE(_MENU_HOTKEY_CONTRAST);
	ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
}
void HotKeyContrastSubLeftRight(void)
{
	if (GET_OSD_STATE() == _MENU_HOTKEY_CONTRAST)
	{

		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		
		SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
		OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_3, COLOR(_CP_WHITE, _CP_BG));
		OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);
		//g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
		

		UserAdjustContrast(GET_OSD_CONTRAST());
		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		
		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
	}
}

void HotKeyBrightnessSelect(void)
{
	OsdDispHotKeyOsdMessage(_MENU_HOTKEY_BRIGHTNESS);
	SET_OSD_STATE(_MENU_HOTKEY_BRIGHTNESS);
	ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
}
void HotKeyBrightnessSubLeftRight(void)
{
	if (GET_OSD_STATE() == _MENU_HOTKEY_BRIGHTNESS)
	{

		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);

		SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
		OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_3, COLOR(_CP_WHITE, _CP_BG));
		OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);
		//g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);

		UserAdjustBrightness(GET_OSD_BRIGHTNESS());
		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
	}
}

#if(_ENABLE_MENU_EXPAND == _ON)
//void MenuHeatConSubUpDown(void)
//{
//	switch(GET_KEYMESSAGE())
//	{
//		case _UP_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_HEATCON_FAN:			
//					SET_OSD_STATE(_MENU_HEATCON_SHUTDOWN_TEMP);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);	
//					break;
//				case _MENU_HEATCON_ACTIVE_TEMP:
//					SET_OSD_STATE(_MENU_HEATCON_FAN);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//				case _MENU_HEATCON_HYSTERESIS:
//					SET_OSD_STATE(_MENU_HEATCON_ACTIVE_TEMP);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_HEATCON_CUR_TEMP:
//					SET_OSD_STATE(_MENU_HEATCON_HYSTERESIS);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_HEATCON_SHUTDOWN:
//					//SET_OSD_STATE(_MENU_HEATCON_CUR_TEMP);				
//					//SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					SET_OSD_STATE(_MENU_HEATCON_HYSTERESIS);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_HEATCON_SHUTDOWN_TEMP:
//					SET_OSD_STATE(_MENU_HEATCON_SHUTDOWN);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					break;
//			}
//			break;
//			
//		case _DOWN_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_HEATCON_FAN:
//					SET_OSD_STATE(_MENU_HEATCON_ACTIVE_TEMP);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_HEATCON_ACTIVE_TEMP:
//					SET_OSD_STATE(_MENU_HEATCON_HYSTERESIS);				
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_HEATCON_HYSTERESIS:
//					//SET_OSD_STATE(_MENU_HEATCON_CUR_TEMP);				
//					//SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					SET_OSD_STATE(_MENU_HEATCON_SHUTDOWN);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					break;
//				case _MENU_HEATCON_CUR_TEMP:
//					SET_OSD_STATE(_MENU_HEATCON_SHUTDOWN);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					break;
//				case _MENU_HEATCON_SHUTDOWN:
//					SET_OSD_STATE(_MENU_HEATCON_SHUTDOWN_TEMP);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					break;
//				case _MENU_HEATCON_SHUTDOWN_TEMP:
//					SET_OSD_STATE(_MENU_HEATCON_FAN);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//			}
//			break;	
//	}
//}

//void MenuDimConSubUpDown(void)
//{
//	switch(GET_KEYMESSAGE())
//	{
//		case _UP_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_DIMCON_AUTO:			
//					//SET_OSD_STATE(_MENU_DIMCON_CUR_LUX);
//					//SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);	
//					SET_OSD_STATE(_MENU_DIMCON_MIN_AMBIENT);			
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_DIMCON_DIMMING:
//					SET_OSD_STATE(_MENU_DIMCON_AUTO);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//				case _MENU_DIMCON_MAX_AMBIENT:
//					if(GET_OSD_AUTO_DIMMING()==_ON)	
//					{
//						SET_OSD_STATE(_MENU_DIMCON_AUTO);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DIMCON_DIMMING);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					}
//					break;
//				case _MENU_DIMCON_MIN_AMBIENT:
//					SET_OSD_STATE(_MENU_DIMCON_MAX_AMBIENT);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_DIMCON_CUR_LUX:
//					SET_OSD_STATE(_MENU_DIMCON_MIN_AMBIENT);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//			}
//			break;
//			
//		case _DOWN_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_DIMCON_AUTO:
//					if(GET_OSD_AUTO_DIMMING()==_ON)	
//					{
//						SET_OSD_STATE(_MENU_DIMCON_MAX_AMBIENT);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					}
//					else
//					{
//						SET_OSD_STATE(_MENU_DIMCON_DIMMING);
//						SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					}
//					break;
//				case _MENU_DIMCON_DIMMING:
//					SET_OSD_STATE(_MENU_DIMCON_MAX_AMBIENT);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_DIMCON_MAX_AMBIENT:
//					SET_OSD_STATE(_MENU_DIMCON_MIN_AMBIENT);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_DIMCON_MIN_AMBIENT:
//					//SET_OSD_STATE(_MENU_DIMCON_CUR_LUX);
//					//SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					SET_OSD_STATE(_MENU_DIMCON_AUTO);				
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//				case _MENU_DIMCON_CUR_LUX:
//					SET_OSD_STATE(_MENU_DIMCON_AUTO);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//			}
//			break;	
//	}
//}

//void MenuVideoWallSubUpDown(void)
//{
//	switch(GET_KEYMESSAGE())
//	{
//		case _UP_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_VIDEOWALL_VIDEOWALL:		
//					SET_OSD_STATE(_MENU_VIDEOWALL_REVERSE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);	
//					break;
//				case _MENU_VIDEOWALL_DISPLAY_NUM:
//					SET_OSD_STATE(_MENU_VIDEOWALL_VIDEOWALL);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//				case _MENU_VIDEOWALL_H_SET:
//					SET_OSD_STATE(_MENU_VIDEOWALL_DISPLAY_NUM);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_VIDEOWALL_V_SET:
//					SET_OSD_STATE(_MENU_VIDEOWALL_H_SET);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_VIDEOWALL_H_EDGE:
//					SET_OSD_STATE(_MENU_VIDEOWALL_V_SET);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_VIDEOWALL_V_EDGE:
//					SET_OSD_STATE(_MENU_VIDEOWALL_H_EDGE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					break;
//				case _MENU_VIDEOWALL_REVERSE:
//					SET_OSD_STATE(_MENU_VIDEOWALL_V_EDGE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					break;
//			}
//			break;
//			
//		case _DOWN_KEY_MESSAGE:
//			switch(GET_OSD_STATE())			
//			{
//				case _MENU_VIDEOWALL_VIDEOWALL:
//					SET_OSD_STATE(_MENU_VIDEOWALL_DISPLAY_NUM);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//					break;
//				case _MENU_VIDEOWALL_DISPLAY_NUM:
//					SET_OSD_STATE(_MENU_VIDEOWALL_H_SET);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_3);
//					break;
//				case _MENU_VIDEOWALL_H_SET:
//					SET_OSD_STATE(_MENU_VIDEOWALL_V_SET);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_4);
//					break;
//				case _MENU_VIDEOWALL_V_SET:
//					SET_OSD_STATE(_MENU_VIDEOWALL_H_EDGE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);
//					break;
//				case _MENU_VIDEOWALL_H_EDGE:
//					SET_OSD_STATE(_MENU_VIDEOWALL_V_EDGE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_6);
//					break;
//				case _MENU_VIDEOWALL_V_EDGE:
//					SET_OSD_STATE(_MENU_VIDEOWALL_REVERSE);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_7);
//					break;
//				case _MENU_VIDEOWALL_REVERSE:
//					SET_OSD_STATE(_MENU_VIDEOWALL_VIDEOWALL);
//					SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//					break;
//			}
//			break;	
//	}
//}
#endif


void HotKeyMuteSelect(void)
{
    if (GET_OSD_VOLUME_MUTE() == _ON)
    {
        SET_OSD_VOLUME_MUTE(_OFF);
    }
    else
    {
        SET_OSD_VOLUME_MUTE(_ON);
    }

	OsdDispHotKeyMuteMessage();
	SET_OSD_STATE(_MENU_HOTKEY_MUTE);
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
}


void HotKeyMuteSubLeftRight(void)	
{
	if(GET_OSD_STATE()==_MENU_HOTKEY_MUTE)
	{
		if(GET_OSD_VOLUME_MUTE() == _OFF)
		{
			SET_OSD_VOLUME_MUTE(_ON);
		}
		else
		{
			SET_OSD_VOLUME_MUTE(_OFF);
		}
		OsdDispHotKeyOsdMessage(_MENU_HOTKEY_MUTE);

#if(_AUDIO_SUPPORT == _ON)
		UserAdjustAudioMuteSwitch();
#endif
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

		ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
	}

}
/*
void MenuPictureSubLeftRight(void)	
{
	switch(GET_OSD_STATE())
	{
		case _MENU_PICTURE_BRIGHTNESS:
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
			OsdDispNumberAndText(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS(), COLOR(_CP_WHITE, _CP_BG));
			UserAdjustBrightness(GET_OSD_BRIGHTNESS());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
			break;
		case _MENU_PICTURE_CONTRAST:
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
			OsdDispNumberAndText(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(), COLOR(_CP_WHITE, _CP_BG));
			UserAdjustContrast(GET_OSD_CONTRAST());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
			break;
		case _MENU_PICTURE_SHARPNESS:
			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _OFF);
            SET_OSD_SHARPNESS(g_usAdjustValue);
            OsdDispNumberAndText(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(), COLOR(_CP_WHITE, _CP_BG));
			UserCommonAdjustSharpness(SysSourceGetInputPort());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_PICTURE_ASPECT:	
			
			g_usBackupValue = GET_OSD_ASPECT_RATIO_TYPE();	
			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_OSD_ASPECT_RATIO_TYPE(), _OSD_ASPECT_RATIO_ORIGIN, _OSD_ASPECT_RATIO_FULL, _OFF);
			if(g_usBackupValue == g_usAdjustValue)
				break;
            SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_PICTURE_ASPECT, GET_OSD_ASPECT_RATIO_TYPE(), COLOR(_CP_WHITE, _CP_BG));
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			
			break;
#if(_ENABLE_MENU_OVERSCAN == _ON)		
		case _MENU_PICTURE_OVERSCAN:	
			
			g_usBackupValue = GET_OSD_OVERSCAN_STATUS();	
			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_OSD_OVERSCAN_STATUS(), _OSD_ON, _OSD_OFF, _OFF);
			if(g_usBackupValue == g_usAdjustValue)
				break;
            SET_OSD_OVERSCAN_STATUS(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_PICTURE_OVERSCAN, GET_OSD_OVERSCAN_STATUS(), COLOR(_CP_WHITE, _CP_BG));
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			
			break;
#endif
#if(_ENABLE_MENU_REGION == _ON)
		case _MENU_PICTURE_REGION:	
			switch(GET_OSD_DISPLAY_MODE())
			{
				case _OSD_DM_1P:
					//SET_OSD_SELECT_REGION(_OSD_SR_1P_FULL);
					g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_1P_FULL, _OSD_SR_1P_FULL, _ON);
					SET_OSD_SELECT_REGION(g_usAdjustValue);
					break;
				case _OSD_DM_2P_LR:
					//SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_FULL);
					g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_2P_LR_FULL, _OSD_SR_2P_LR_L, _ON);
					SET_OSD_SELECT_REGION(g_usAdjustValue);
					break;
				case _OSD_DM_2P_TB:
					//SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_FULL);
					g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_2P_TB_FULL, _OSD_SR_2P_TB_T, _ON);
					SET_OSD_SELECT_REGION(g_usAdjustValue);
					break;
				case _OSD_DM_2P_PIP:
					//SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_FULL);
					g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_2P_PIP_FULL, _OSD_SR_2P_PIP_MAIN, _ON);
					SET_OSD_SELECT_REGION(g_usAdjustValue);
					break;
				case _OSD_DM_3P:
					//SET_OSD_SELECT_REGION(_OSD_SR_3P_FULL);
					g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_3P_FULL, _OSD_SR_3P_1P, _ON);
					SET_OSD_SELECT_REGION(g_usAdjustValue);
					break;
				case _OSD_DM_4P:
					//SET_OSD_SELECT_REGION(_OSD_SR_4P_FULL);
					g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_4P_FULL, _OSD_SR_4P_LT_INSIDE, _ON);
					SET_OSD_SELECT_REGION(g_usAdjustValue);
					break;
			}
			break;
#endif
	}
}
*/
void MenuPictureSubLeftRight(void)
{
	switch (GET_OSD_STATE())
	{
	case _MENU_PICTURE_BLACKLEVEL_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_OSD_BRIGHTNESS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
		OsdDispNumberAndText(_MENU_PICTURE_BLACKLEVEL, GET_OSD_BRIGHTNESS(), COLOR(_CP_WHITE, _CP_BG));
		UserAdjustBrightness(GET_OSD_BRIGHTNESS());
		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
		break;
	case _MENU_PICTURE_CONTRAST_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
		OsdDispNumberAndText(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(), COLOR(_CP_WHITE, _CP_BG));
		UserAdjustContrast(GET_OSD_CONTRAST());
		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
		break;
	case _MENU_PICTURE_CHROMA_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SATURATION(), _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_OSD_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER));
		OsdDispNumberAndText(_MENU_PICTURE_CHROMA, GET_OSD_SATURATION(), COLOR(_CP_WHITE, _CP_BG));
		UserAdjustGlobalHueSat(GET_OSD_HUE(), GET_OSD_SATURATION()); // Set Global hue/sat
		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _MENU_PICTURE_SHARPNESS_ADJ:
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _OFF);
		SET_OSD_SHARPNESS(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(), COLOR(_CP_WHITE, _CP_BG));
		UserCommonAdjustSharpness(SysSourceGetInputPort());
		//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
#if (_ENABLE_MENU_REGION == _ON)
	case _MENU_PICTURE_REGION:
		/*
		switch(GET_OSD_DISPLAY_MODE())
		{
			case _OSD_DM_1P:
				//SET_OSD_SELECT_REGION(_OSD_SR_1P_FULL);
				g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_1P_FULL, _OSD_SR_1P_FULL, _ON);
				SET_OSD_SELECT_REGION(g_usAdjustValue);
				break;
			case _OSD_DM_2P_LR:
				//SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_FULL);
				g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_2P_LR_FULL, _OSD_SR_2P_LR_L, _ON);
				SET_OSD_SELECT_REGION(g_usAdjustValue);
				break;
			case _OSD_DM_2P_TB:
				//SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_FULL);
				g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_2P_TB_FULL, _OSD_SR_2P_TB_T, _ON);
				SET_OSD_SELECT_REGION(g_usAdjustValue);
				break;
			case _OSD_DM_2P_PIP:
				//SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_FULL);
				g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_2P_PIP_FULL, _OSD_SR_2P_PIP_MAIN, _ON);
				SET_OSD_SELECT_REGION(g_usAdjustValue);
				break;
			case _OSD_DM_3P:
				//SET_OSD_SELECT_REGION(_OSD_SR_3P_FULL);
				g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_3P_FULL, _OSD_SR_3P_LT_INSIDE, _ON);
				SET_OSD_SELECT_REGION(g_usAdjustValue);
				break;
			case _OSD_DM_4P:
				//SET_OSD_SELECT_REGION(_OSD_SR_4P_FULL);
				g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SELECT_REGION(), _OSD_SR_4P_FULL, _OSD_SR_4P_LT_INSIDE, _ON);
				SET_OSD_SELECT_REGION(g_usAdjustValue);
				break;
		}
		*/
		break;
#endif
	}
}
/*
void MenuColorSubLeftRight(void)	
{
	switch(GET_OSD_STATE())
	{
		case _MENU_COLOR_EFFECT:	
			
			g_usBackupValue = GET_OSD_COLOR_EFFECT();
			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_OSD_COLOR_EFFECT(), _COLOREFFECT_VIVID, _COLOREFFECT_STANDARD, _OFF);
			if(g_usBackupValue == g_usAdjustValue)
				break;
            SET_OSD_COLOR_EFFECT(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_COLOR_EFFECT, GET_OSD_COLOR_EFFECT(), COLOR(_CP_WHITE, _CP_BG));
			
#if(_HDR10_SUPPORT == _ON)
			if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
			{
				UserCommonHDRAdjustHDR10ColorEffect();
			}
			else
#endif
			{
#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
				UserAdjustColorEffectMode();
#endif
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			
			break;
			
		case _MENU_COLOR_GAMMA:
			
			g_usBackupValue = GET_OSD_GAMMA();
			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_OSD_GAMMA(), _GAMMA_AMOUNT, _GAMMA_OFF, _OFF);
			if(g_usBackupValue == g_usAdjustValue)
				break;
			SET_OSD_GAMMA(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_COLOR_GAMMA, GET_OSD_GAMMA(), COLOR(_CP_WHITE, _CP_BG));
#if(_GAMMA_FUNCTION == _ON)
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
            if(GET_OSD_GAMMA() != _GAMMA_OFF)
            {
                UserAdjustGamma(GET_OSD_GAMMA());
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
            }
#if(((_OGC_SUPPORT == _ON) || (_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)) && (_CONTRAST_SUPPORT == _ON))
            else
            {
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserAdjustContrast(GET_OSD_CONTRAST());
            }
#endif
#endif			
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			
			break;
			
		case _MENU_COLOR_TEMPERATURE:
			
			g_usBackupValue = GET_COLOR_TEMP_TYPE();
			g_usAdjustValue = OsdDisplayDetOverRange(GET_COLOR_TEMP_TYPE(), _CT_USER, _CT_9300, _OFF);
			if(g_usBackupValue == g_usAdjustValue)
				break;
			
            SET_COLOR_TEMP_TYPE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_COLOR_TEMPERATURE, GET_COLOR_TEMP_TYPE(), COLOR(_CP_WHITE, _CP_BG));
		    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

			if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			{
#if(_DYNAMIC_OSD_WINDOW ==_ON)	
				OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(6+2), _CP_DARKGRAY);
#endif					
				OsdSubMenuItemText(_MENU_COLOR,_MENU_COLOR_TEMP_USER_R,COLOR(_CP_WHITE, _CP_BG));
				OsdSubMenuItemText(_MENU_COLOR,_MENU_COLOR_TEMP_USER_G,COLOR(_CP_WHITE, _CP_BG));
				OsdSubMenuItemText(_MENU_COLOR,_MENU_COLOR_TEMP_USER_B,COLOR(_CP_WHITE, _CP_BG));
			}
			else
			{
#if(_DYNAMIC_OSD_WINDOW ==_ON)	
				OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(3+2), _CP_DARKGRAY);
#endif			
				OsdFuncClearOsd(ROW(_ITEM_4), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH, 1);	// Clear Item
				OsdFuncClearOsd(ROW(_ITEM_5), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH, 1);
				OsdFuncClearOsd(ROW(_ITEM_6), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH, 1);
			}
			
			break;
		case _MENU_COLOR_TEMP_USER_R:	
			
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
			OsdDispNumberAndText(_MENU_COLOR_TEMP_USER_R, g_usAdjustValue, COLOR(_CP_WHITE, _CP_BG));
			SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER));
			
			g_usAdjustValue = UserCommonAdjustRealValueTo255(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN);	
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 255, 0, _OFF);
			OsdDispNumberAndText(_MENU_COLOR_TEMP_USER_R, g_usAdjustValue, COLOR(_CP_WHITE, _CP_BG));
			SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjust255ToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN));
			
#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
			break;	
		case _MENU_COLOR_TEMP_USER_G:	
			
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
			OsdDispNumberAndText(_MENU_COLOR_TEMP_USER_G, g_usAdjustValue, COLOR(_CP_WHITE, _CP_BG));
			SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER));
			
			g_usAdjustValue = UserCommonAdjustRealValueTo255(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN);	
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 255, 0, _OFF);
			OsdDispNumberAndText(_MENU_COLOR_TEMP_USER_G, g_usAdjustValue, COLOR(_CP_WHITE, _CP_BG));
			SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjust255ToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN));
			
#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
			break;
		case _MENU_COLOR_TEMP_USER_B:
			
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
			OsdDispNumberAndText(_MENU_COLOR_TEMP_USER_B, g_usAdjustValue, COLOR(_CP_WHITE, _CP_BG));
			SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER));
			
			g_usAdjustValue = UserCommonAdjustRealValueTo255(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN);	
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 255, 0, _OFF);
			OsdDispNumberAndText(_MENU_COLOR_TEMP_USER_B, g_usAdjustValue, COLOR(_CP_WHITE, _CP_BG));
			SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjust255ToRealValue(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN));
			
#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
			break;
	}
}
*/
void MenuColorSubLeftRight(void)
{
	switch (GET_OSD_STATE())
	{
	case _MENU_COLOR_EFFECT:
		break;
	case _MENU_COLOR_GAMMA:
		break;
	case _MENU_COLOR_TEMPERATURE:
		break;
	case _MENU_COLOR_SURGICAL:
		break;
	case _MENU_COLOR_BIAS_R_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_BIAS_R(), _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_COLOR_BIAS_R(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER));
		OsdDispNumberAndText(_MENU_COLOR_BIAS_R, GET_COLOR_BIAS_R(), COLOR(_CP_WHITE, _CP_BG));
#if (_BRIGHTNESS_SUPPORT == _ON)
		UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif

		break;
	case _MENU_COLOR_BIAS_G_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_BIAS_G(), _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_COLOR_BIAS_G(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER));
		OsdDispNumberAndText(_MENU_COLOR_BIAS_G, GET_COLOR_BIAS_G(), COLOR(_CP_WHITE, _CP_BG));
#if (_BRIGHTNESS_SUPPORT == _ON)
		UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif

		break;
	case _MENU_COLOR_BIAS_B_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_BIAS_B(), _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_COLOR_BIAS_B(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER));
		OsdDispNumberAndText(_MENU_COLOR_BIAS_B, GET_COLOR_BIAS_B(), COLOR(_CP_WHITE, _CP_BG));
#if (_BRIGHTNESS_SUPPORT == _ON)
		UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif

		break;

	case _MENU_COLOR_GAIN_R_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_GAIN_R(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_COLOR_GAIN_R(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _OFF);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_COLOR_GAIN_R(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER));
		OsdDispNumberAndText(_MENU_COLOR_GAIN_R, GET_COLOR_GAIN_R(), COLOR(_CP_WHITE, _CP_BG));
#if (_CONTRAST_SUPPORT == _ON)
		UserAdjustContrast(GET_OSD_CONTRAST());
#endif

		break;
	case _MENU_COLOR_GAIN_G_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_GAIN_G(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_COLOR_GAIN_G(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _OFF);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_COLOR_GAIN_G(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER));
		OsdDispNumberAndText(_MENU_COLOR_GAIN_G, GET_COLOR_GAIN_G(), COLOR(_CP_WHITE, _CP_BG));
#if (_CONTRAST_SUPPORT == _ON)
		UserAdjustContrast(GET_OSD_CONTRAST());
#endif

		break;
	case _MENU_COLOR_GAIN_B_ADJ:
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_GAIN_B(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
		// g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_COLOR_GAIN_B(), _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _OFF);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_COLOR_GAIN_B(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER));
		OsdDispNumberAndText(_MENU_COLOR_GAIN_B, GET_COLOR_GAIN_B(), COLOR(_CP_WHITE, _CP_BG));
#if (_CONTRAST_SUPPORT == _ON)
		UserAdjustContrast(GET_OSD_CONTRAST());
#endif

		break;
	}
}

void MenuScreenSubLeftRight(void)
{
	/*
	switch (GET_OSD_STATE())
	{
	case _MENU_SCREEN_PIP_SIZE_ADJ:
		g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_PIP_SIZE(), 10, 0, _OFF);
		SET_OSD_PIP_SIZE(g_usAdjustValue);

		if (SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
		{
			OsdDispNumberAndText(_MENU_SCREEN_PIP_SIZE, GET_OSD_PIP_SIZE(), COLOR(_CP_WHITE, _CP_BG));

#if (_PIP_DISPLAY_SUPPORT == _ON)
			if (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
			{
				UserCommonAdjustPipSubTimingFormat();
			}
#endif
		}
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _MENU_SCREEN_OVERSCAN:
	case _MENU_SCREEN_ASPECT:
	case _MENU_SCREEN_MONO_COLOR:
	case _MENU_SCREEN_ROTATE:
	//case _MENU_SCREEN_DISPLAY_MODE:
	//case _MENU_SCREEN_PIP_POSITION:
	//case _MENU_SCREEN_PIP_SIZE:
		break;
	}
	*/
}

//void MenuDisplaySubLeftRight(void)
//{
//	switch(GET_OSD_STATE())			
//	{
//		case _MENU_DISPLAY_ROTATE:		
//			/*
//			//g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_DISP_ROTATE(), _DISP_ROTATE_180, _DISP_ROTATE_0, _OFF);
//			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_DISP_ROTATE(), _DISP_ROTATE_VER_MIRROR, _DISP_ROTATE_0, _OFF); 
//			SET_OSD_DISP_ROTATE(g_usAdjustValue);	
//			OsdDispNumberAndText(_MENU_DISPLAY_ROTATE, GET_OSD_DISP_ROTATE(), COLOR(_CP_WHITE, _CP_BG));
//			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DISPLAY_SOURCE1:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), _OSD_INPUT_D3, _OSD_INPUT_AUTO, _ON);
//			SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_DISPLAY_SOURCE1, GET_OSD_INPUT_PORT_OSD_ITEM(), COLOR(_CP_WHITE, _CP_BG));
//			//MenuSourceSelect();	// need to check 
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DISPLAY_SOURCE2:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), _OSD_INPUT_D3, _OSD_INPUT_AUTO, _ON);
//			SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_DISPLAY_SOURCE2, GET_OSD_INPUT_PORT_OSD_ITEM(), COLOR(_CP_WHITE, _CP_BG));
//			//MenuSourceSelect();
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DISPLAY_SOURCE3:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), _OSD_INPUT_D3, _OSD_INPUT_AUTO, _ON);
//			SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_DISPLAY_SOURCE3, GET_OSD_INPUT_PORT_OSD_ITEM(), COLOR(_CP_WHITE, _CP_BG));
//			//MenuSourceSelect();
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DISPLAY_SOURCE4:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), _OSD_INPUT_D3, _OSD_INPUT_AUTO, _ON);
//			SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_DISPLAY_SOURCE4, GET_OSD_INPUT_PORT_OSD_ITEM(), COLOR(_CP_WHITE, _CP_BG));
//			//MenuSourceSelect();
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DISPLAY_MODE:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_DISPLAY_MODE(), _OSD_DM_4P, _OSD_DM_1P, _ON);
//			SET_OSD_DISPLAY_MODE(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_DISPLAY_MODE, GET_OSD_DISPLAY_MODE(), COLOR(_CP_WHITE, _CP_BG));
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DISPLAY_PIP_POSITION:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_PIP_POSITION_TYPE(), _PIP_POSITON_RB, _PIP_POSITON_LT, _ON);
//			SET_OSD_PIP_POSITION_TYPE(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_DISPLAY_PIP_POSITION, GET_OSD_PIP_POSITION_TYPE(), COLOR(_CP_WHITE, _CP_BG));
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DISPLAY_PIP_SIZE:
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_PIP_SIZE(), 10, 0, _OFF);
//			SET_OSD_PIP_SIZE(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_DISPLAY_PIP_SIZE, GET_OSD_PIP_SIZE(), COLOR(_CP_WHITE, _CP_BG));
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			break;
//		case _MENU_DISPLAY_INPUT_SWAP:
//			break;
//		//case _MENU_DISPLAY_REGION:	
//		//	break;	
//	}

//}

//void MenuOsdSubLeftRight(void)
//{
//	BYTE hPosi,vPosi;	
//	
//	switch(GET_OSD_STATE())			
//	{
//		case _MENU_OSD_H_POSITION:			
//			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_HPOS(), _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
//            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
//            SET_OSD_HPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER));
//			OsdDispNumberAndText(_MENU_OSD_H_POSITION, GET_OSD_HPOS(), COLOR(_CP_WHITE, _CP_BG));
//			//OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

//			switch(GET_OSD_ROTATE_STATUS())
//			{
//				case _OSD_ROTATE_DEGREE_0:
//					hPosi = GET_OSD_HPOS();
//					vPosi = GET_OSD_VPOS();
//					break;
//				case _OSD_ROTATE_DEGREE_90:
//					hPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
//					vPosi = GET_OSD_HPOS();
//					break;
//				case _OSD_ROTATE_DEGREE_180:
//					hPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
//					vPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
//					break;
//				case _OSD_ROTATE_DEGREE_270:
//					hPosi = GET_OSD_VPOS();
//					vPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
//					break;
//				default:
//					hPosi = GET_OSD_HPOS();
//					vPosi = GET_OSD_VPOS();
//					break;
//			}
//			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, hPosi, vPosi);
//			
//			break;
//		case _MENU_OSD_V_POSITION:	
//			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VPOS(), _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
//            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
//            SET_OSD_VPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER));
//			OsdDispNumberAndText(_MENU_OSD_V_POSITION, GET_OSD_VPOS(), COLOR(_CP_WHITE, _CP_BG));
//			//OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			
//			switch(GET_OSD_ROTATE_STATUS())
//			{
//				case _OSD_ROTATE_DEGREE_0:
//					hPosi = GET_OSD_HPOS();
//					vPosi = GET_OSD_VPOS();
//					break;
//				case _OSD_ROTATE_DEGREE_90:
//					hPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
//					vPosi = GET_OSD_HPOS();
//					break;
//				case _OSD_ROTATE_DEGREE_180:
//					hPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
//					vPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
//					break;
//				case _OSD_ROTATE_DEGREE_270:
//					hPosi = GET_OSD_VPOS();
//					vPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
//					break;
//				default:
//					hPosi = GET_OSD_HPOS();
//					vPosi = GET_OSD_VPOS();
//					break;
//			}
//			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, hPosi, vPosi);
//			
//			break;
//		case _MENU_OSD_TRANSPARENCY:
//			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_OSD_TRANSPARENCY_STATUS(), _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OFF);
//            SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_OSD_TRANSPARENCY, GET_OSD_TRANSPARENCY_STATUS(), COLOR(_CP_WHITE, _CP_BG));
//			OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			break;
//		case _MENU_OSD_TIMEOUT:
//			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_TIME_OUT(), _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OFF);
//            SET_OSD_TIME_OUT(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_OSD_TIMEOUT, GET_OSD_TIME_OUT(), COLOR(_CP_WHITE, _CP_BG));
//			ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			break;
//		case _MENU_OSD_ROTATE:	
//			/*
//#if(_OSD_ROTATE_CW180_SUPPORT == _ON)
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_180, _OSD_ROTATE_DEGREE_0, _ON);	
//#else
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_270, _OSD_ROTATE_DEGREE_0, _ON);
//#endif
//			SET_OSD_ROTATE_STATUS(g_usAdjustValue);
//			//OsdDispNumberAndText(_MENU_OSD_ROTATE, GET_OSD_ROTATE_STATUS(), COLOR(_CP_WHITE, _CP_BG));	

//			//------------------------------------------------------------------------------------------------------------------- 
//			//SET_OSD_HPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER));
//			//OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//			//-------------------------------------------------------------------------------------------------------------------
//#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//			OsdDispOsdRotateSwitch();
//#endif
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_OSD_LANGUAGE:
//			/*
//			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_LANGUAGE(), _CHINESE_T, _ENGLISH, _OFF);
//			SET_OSD_LANGUAGE(g_usAdjustValue);
//			OsdDispNumberAndText(_MENU_OSD_LANGUAGE, GET_OSD_LANGUAGE(), COLOR(_CP_WHITE, _CP_BG));
//			OsdMainMenuPageDraw();	
//			OsdSubMenuPageDraw(_MENU_OSD_SETTING);
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//	}
//}

void MenuAudioSubLeftRight(void)	
{
	switch(GET_OSD_STATE())			
	{
		case _MENU_AUDIO_VOLUME_ADJ:			
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF);
            SET_OSD_VOLUME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME(), COLOR(_CP_WHITE, _CP_BG));
			if(GET_OSD_VOLUME_MUTE() == _ON)
            {
                SET_OSD_VOLUME_MUTE(_OFF);
            }
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
			//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
		case _MENU_AUDIO_MUTE:
			/*
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME_MUTE(), _ON, _OFF, _ON);
			SET_OSD_VOLUME_MUTE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_AUDIO_MUTE, GET_OSD_VOLUME_MUTE(), COLOR(_CP_WHITE, _CP_BG));
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioMuteSwitch();
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			*/
			break;
		case _MENU_AUDIO_SOURCE:
			/*
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_AUDIO_SOURCE(), _DIGITAL_AUDIO, _LINE_IN_AUDIO, _ON);
			SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_AUDIO_SOURCE, GET_OSD_AUDIO_SOURCE(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			*/
			break;
	}
}

void SetMenuDp2D0Version(void)	
{
	if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
	{
		SET_OSD_DP_MST(_MST_OFF);
	}

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))

	// Disable HDR Function, if DP Version Switch to 1.1/1.2
	if((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
	{
		SET_OSD_HDR_MODE(_HDR10_MODE_OFF);
		// Switch DP D0 Port Edid
		UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
	}
#endif
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
	// Disable AdaptiveSync by Port
	if((GET_OSD_DP_D0_VERSION() < _DP_VER_1_DOT_3) && (SysSourceGetInputPort() == _D0_INPUT_PORT))
	{
		SET_OSD_DP_ADAPTIVE_SYNC_STATUS(_OFF);
		UserCommonInterfaceDpAdaptiveSyncSupportSwitch();
	}
#endif

#if(_DP_SUPPORT == _ON)
	UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());

	if(SysSourceGetInputPort() == _D0_INPUT_PORT)
	{
		//SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
	}
#endif

}
void SetMenuDp1D1Version(void)	
{
	if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
	{
		SET_OSD_DP_MST(_MST_OFF);
	}

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))

	// Disable HDR Function, if DP Version Switch to 1.1/1.2
	if((GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
	{
		SET_OSD_HDR_MODE(_HDR10_MODE_OFF);
		// Switch DP D1 Port Edid
		UserCommonInterfaceDPSwitchEdid(_D1_INPUT_PORT);
	}
#endif
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
	// Disable AdaptiveSync by Port
	if((GET_OSD_DP_D1_VERSION() < _DP_VER_1_DOT_3) && (SysSourceGetInputPort() == _D1_INPUT_PORT))
	{
		SET_OSD_DP_ADAPTIVE_SYNC_STATUS(_OFF);
		UserCommonInterfaceDpAdaptiveSyncSupportSwitch();
	}
#endif

#if(_DP_SUPPORT == _ON)
	UserCommonInterfaceDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());

	if(SysSourceGetInputPort() == _D1_INPUT_PORT)
	{
		//SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
	}
#endif

}

//void MenuDpOptionSubLeftRight(void)
//{
//	switch(GET_OSD_STATE())			
//	{
//		case _MENU_DP_OPTION_VERSION:			
//			/*
//			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_DP_D0_VERSION(), _DP_VER_1_DOT_3, _DP_VER_1_DOT_1, _OFF);
//			SET_OSD_DP_D0_VERSION(g_usAdjustValue);
//			SET_OSD_DP_D1_VERSION(g_usAdjustValue);
//			SetMenuDp2D0Version();
//			SetMenuDp1D1Version();
//			
//			OsdDispNumberAndText(_MENU_DP_OPTION_VERSION, GET_OSD_DP_D0_VERSION(), COLOR(_CP_WHITE, _CP_BG));	// D0-DP2
//			//OsdDispNumberAndText(_MENU_DP_OPTION_VERSION, GET_OSD_DP_D1_VERSION(), COLOR(_CP_WHITE, _CP_BG));	// D1-DP1
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DP_OPTION_MST:
//			/*
//			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_DP_MST(), _MST_D1, _MST_OFF, _OFF);
//			SET_OSD_DP_MST(g_usAdjustValue);
//#if(_DP_MST_SUPPORT == _ON)
//			UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());

//			if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
//			{
//				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//			}
//#endif
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			*/
//			break;
//		case _MENU_DP_OPTION_RESOLUTION:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(UserCommonNVRamGetSystemData(_DP_EDID_SELECT), _DP_EDID_4K2K_60HZ, _DP_EDID_1080P, _OFF);
//			UserCommonNVRamSetSystemData(_DP_EDID_SELECT, g_usAdjustValue);
//			
//#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//                UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
//                UserCommonInterfaceDPSwitchEdid(_D1_INPUT_PORT);
//                UserCommonInterfaceDPSwitchEdid(_D2_INPUT_PORT);
//                UserCommonInterfaceDPSwitchEdid(_D6_INPUT_PORT);
//#endif
//			OsdDispNumberAndText(_MENU_DP_OPTION_RESOLUTION, UserCommonNVRamGetSystemData(_DP_EDID_SELECT), COLOR(_CP_WHITE, _CP_BG));
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//			*/
//			break;
//		case _MENU_DP_OPTION_CLONE:
//			/*
//			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_CLONE_MODE(), _OSD_CLONE_ON, _OSD_CLONE_OFF, _ON);
//			SET_OSD_CLONE_MODE(g_usAdjustValue);
//#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
//            UserCommonInterfaceCloneModeSwitch(GET_OSD_CLONE_MODE());
//#endif
//			OsdDispNumberAndText(_MENU_DP_OPTION_CLONE, GET_OSD_CLONE_MODE(), COLOR(_CP_WHITE, _CP_BG));
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//			*/
//			break;
//	}
//}
/*
void MenuSetupSubLeftRight(void)	
{
	switch(GET_OSD_STATE())			
	{
		case _MENU_SETUP_RESET:			
			
			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_RESET_MODE(), _ON , _OFF, _OFF);	
			//SET_OSD_RESET_MODE(g_usAdjustValue);
			if(g_usAdjustValue == _ON)
				OsdDispOsdReset();
			
			break;
		case _MENU_SETUP_POWERSAVE:
			
			//g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_POWERSAVE_TIME(), _POWER_SAVE_120MIN , _POWER_SAVE_OFF, _OFF);
			SET_OSD_POWERSAVE_TIME(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SETUP_POWERSAVE, GET_OSD_POWERSAVE_TIME(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			
			break;
		case _MENU_SETUP_SETID:
			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SETID(), _OSD_SETID_MAX , _OSD_SETID_MIN, _OFF);
			SET_OSD_SETID(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SETUP_SETID, GET_OSD_SETID(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;
#if(_ENABLE_MENU_HPD_MODE == _ON)	
		case _MENU_SETUP_HPD_MODE:
			
			g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_HPD_MODE(), _HPD_MODE4, _HPD_MODE1, _OFF);
			SET_OSD_HPD_MODE(g_usAdjustValue);
			OsdDispNumberAndText(_MENU_SETUP_HPD_MODE, GET_OSD_HPD_MODE(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			
			break;
#endif
	}
}
*/
void MenuSetupSubLeftRight(void)
{
	switch (GET_OSD_STATE())
	{
	case _MENU_SETUP_RESET:
		/*
		g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_RESET_MODE(), _ON , _OFF, _OFF);
		//SET_OSD_RESET_MODE(g_usAdjustValue);
		if(g_usAdjustValue == _ON)
			OsdDispOsdReset();
		*/
		break;
	case _MENU_SETUP_POWERSAVE:
		/*
		g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_POWERSAVE_TIME(), _POWER_SAVE_120MIN , _POWER_SAVE_OFF, _OFF);
		SET_OSD_POWERSAVE_TIME(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_SETUP_POWERSAVE, GET_OSD_POWERSAVE_TIME(), COLOR(_CP_WHITE, _CP_BG));
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		*/
		break;
	case _MENU_SETUP_SETID:
		g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_SETID(), _OSD_SETID_MAX, _OSD_SETID_MIN, _OFF);
		SET_OSD_SETID(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_SETUP_SETID, GET_OSD_SETID(), COLOR(_CP_WHITE, _CP_BG));
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _MENU_SETUP_BACKLIGHT_ADJ:
		if (GET_OSD_BACKLIGHT_CONTROL() == _ON)
		{
			g_usAdjustValue = GET_OSD_BACKLIGHT();
			g_usAdjustValue = OsdDisplayDetOverRange_Curved(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _OFF);
			SET_OSD_BACKLIGHT(g_usAdjustValue);
		}
		else
		{
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
			SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
		}

		OsdDispNumberAndText(_MENU_SETUP_BACKLIGHT, GET_OSD_BACKLIGHT(), COLOR(_CP_WHITE, _CP_BG));
		UserAdjustBacklight(GET_OSD_BACKLIGHT());

		// SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	}
}

void MenuBacklightLeftRight(void)
{
	if (GET_OSD_BACKLIGHT_CONTROL() == _ON)
	{
		g_usAdjustValue = GET_OSD_BACKLIGHT();
		g_usAdjustValue = OsdDisplayDetOverRange_Curved(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _OFF);
		SET_OSD_BACKLIGHT(g_usAdjustValue);
	}
	else
	{
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
		SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
	}
	UserAdjustBacklight(GET_OSD_BACKLIGHT());
}

#if(_ENABLE_MENU_VGA == _ON)	
void MenuVgaSubLeftRight(void)	
{
	if(SysSourceGetSourceType() != _SOURCE_VGA)
		return;

	switch(GET_OSD_STATE())			
	{
		case _MENU_VGA_AUTO:
			/*
			g_usAdjustValue = OsdDisplayDetOverRange(GET_VGA_AUTOADJ_MODE(), _ON , _OFF, _OFF);
			//SET_OSD_AUTOADJ_MODE(g_usAdjustValue);
			if(g_usAdjustValue == _ON)
			{
					// Option 1
				//OsdDispOsdMessage(_OSD_DISP_AUTO_CONFIG_MSG);		
	    		//UserCommonAutoConfig();
	    		//OsdDispDisableOsd();
				
					// Option 2
				OsdDispMainSubString(_AUTO_CONFIG_DO);	
				g_usAdjustValue = 0;
	            UserCommonAutoConfig();
	            OsdDispMainSubString(_AUTO_CONFIG_RESULT);
				OsdDispMainSubString(_AUTO_CONFIG_CLOSE_WIN);

				
				OsdDispNumberAndText(_MENU_VGA_H_POSI, GET_VGA_MODE_ADJUST_H_POSITION(), COLOR(_CP_WHITE, _CP_BG));
				OsdDispNumberAndText(_MENU_VGA_V_POSI, GET_VGA_MODE_ADJUST_V_POSITION(), COLOR(_CP_WHITE, _CP_BG));
				OsdDispNumberAndText(_MENU_VGA_CLOCK, GET_VGA_MODE_ADJUST_CLOCK(), COLOR(_CP_WHITE, _CP_BG));
				OsdDispNumberAndText(_MENU_VGA_PHASE, GET_VGA_MODE_ADJUST_PHASE(), COLOR(_CP_WHITE, _CP_BG));
			}
			*/
			break;
		case _MENU_VGA_H_POSI:
			g_usAdjustValue = OsdDisplayDetOverRange(GET_VGA_MODE_ADJUST_H_POSITION(), 100 , 0, _OFF);
			SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
			UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
			OsdDispNumberAndText(_MENU_VGA_H_POSI, GET_VGA_MODE_ADJUST_H_POSITION(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
			break;
		case _MENU_VGA_V_POSI:
			g_usAdjustValue = OsdDisplayDetOverRange(GET_VGA_MODE_ADJUST_V_POSITION(), 100 , 0, _OFF);
			SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
			UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
			OsdDispNumberAndText(_MENU_VGA_V_POSI, GET_VGA_MODE_ADJUST_V_POSITION(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
			break;
		case _MENU_VGA_CLOCK:
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            g_usAdjustValue = OsdDisplayDetOverRange(GET_VGA_MODE_ADJUST_CLOCK(), 100, 0, _OFF);
            SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
			UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
           	OsdDispNumberAndText(_MENU_VGA_CLOCK, GET_VGA_MODE_ADJUST_CLOCK(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                g_usAdjustValue = OsdDisplayDetOverRange(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, _OFF);
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
				UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
                //OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _SELECT);
                OsdDispNumberAndText(_MENU_VGA_CLOCK, usUserIHTotal, COLOR(_CP_WHITE, _CP_BG));
            }
#endif
			break;
		case _MENU_VGA_PHASE:
			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_VGA_MODE_ADJUST_PHASE(), _OSD_PHASE_MAX, _OSD_PHASE_MIN, _OFF);
            SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
			UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
			OsdDispNumberAndText(_MENU_VGA_PHASE, GET_VGA_MODE_ADJUST_PHASE(), COLOR(_CP_WHITE, _CP_BG));
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
			break;
	}
}
#endif

void MenuServiceSubLeftRight(void)
{
	switch (GET_OSD_STATE())
	{
	case _MENU_SERVICE_BACKLIGHT_MIN_ADJ:
		g_usAdjustValue = GET_BACKLIGHT_MIN();
		g_usAdjustValue = OsdDisplayDetOverRange_Long(g_usAdjustValue, 4095, 0, _OFF);
		SET_BACKLIGHT_MIN(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_MIN, GET_BACKLIGHT_MIN(), COLOR(_CP_WHITE, _CP_BG));
		// SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _MENU_SERVICE_BACKLIGHT_MAX_ADJ:
		g_usAdjustValue = GET_BACKLIGHT_MAX();
		g_usAdjustValue = OsdDisplayDetOverRange_Long(g_usAdjustValue, 4095, 0, _OFF);
		SET_BACKLIGHT_MAX(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_MAX, GET_BACKLIGHT_MAX(), COLOR(_CP_WHITE, _CP_BG));
		// SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	case _MENU_SERVICE_BACKLIGHT_FREQ_ADJ:
		g_usAdjustValue = GET_OSD_BACKLIGHT_FREQ();
		g_usAdjustValue = OsdDisplayDetOverRange_Freq(g_usAdjustValue, 10000, 60, _OFF);
		ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, g_usAdjustValue);
		SET_OSD_BACKLIGHT_FREQ(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_FREQ, GET_OSD_BACKLIGHT_FREQ(), COLOR(_CP_WHITE, _CP_BG));
		// OsdPropShowNumberRight(ROW(_ITEM_7), COL(_MENU_SECTION_0_SUB_NUM_X), GET_OSD_BACKLIGHT_FREQ(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
		break;
	case _MENU_SERVICE_LOGO_LIST_ADJ:
		g_usAdjustValue = GET_OSD_LOGO_LIST();
		g_usAdjustValue = OsdDisplayDetOverRange_Long(g_usAdjustValue, 2, 0, _OFF);
		SET_OSD_LOGO_LIST(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_SERVICE_LOGO_LIST, GET_OSD_LOGO_LIST(), COLOR(_CP_WHITE, _CP_BG));
		break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
	case _MENU_SERVICE_STABILUX_ADJ:
		g_usAdjustValue = GET_OSD_STABILUX();
		g_usAdjustValue = OsdDisplayDetOverRange_Freq(g_usAdjustValue, _DEFAULT_STABILUX_MAX, _DEFAULT_STABILUX_MIN, _OFF);
		SET_OSD_STABILUX(g_usAdjustValue);
		OsdDispNumberAndText(_MENU_SERVICE_STABILUX, GET_OSD_STABILUX(), COLOR(_CP_WHITE, _CP_BG));
		// OsdPropShowNumberRight(ROW(_ITEM_7), COL(_MENU_SECTION_0_SUB_NUM_X), GET_OSD_BACKLIGHT_FREQ(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
		break;
#endif
	case _MENU_SERVICE_FAN_SPEED_ADJ:
#if (_ENABLE_FAN_CONTROL == _ON)
		g_usAdjustValue = GET_OSD_FAN_PWM();
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 255, 0, _OFF);

		SET_OSD_FAN_PWM(g_usAdjustValue);
#endif
		OsdDispNumberAndText(_MENU_SERVICE_FAN_SPEED, GET_OSD_FAN_PWM(), COLOR(_CP_WHITE, _CP_BG));
		// OsdPropShowNumberRight(ROW(_ITEM_7), COL(_MENU_SECTION_0_SUB_NUM_X), GET_OSD_BACKLIGHT_FREQ(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
		break;
	}
}

#if (_CUSTOMER_TYPE == _CUSTOMER_AWERONET)

EnumOSDInputPortDef GetNextActivePort(EnumOSDInputPortDef currentPort)
{
	BYTE offset;

	for (offset = 1; offset <= 3; offset++)
	{
		EnumOSDInputPortDef next = (currentPort - _OSD_INPUT_D0 + offset) % 4 + _OSD_INPUT_D0;

		switch (next)
		{
		case _OSD_INPUT_D0:
			if (GET_D0_CABLE_STATUS())
				return _OSD_INPUT_D0;
			break;
		case _OSD_INPUT_D1:
			if (GET_D1_CABLE_STATUS())
				return _OSD_INPUT_D1;
			break;
		case _OSD_INPUT_D2:
			if (GET_D2_CABLE_STATUS())
				return _OSD_INPUT_D2;
			break;
		case _OSD_INPUT_D3:
			if (GET_D3_CABLE_STATUS())
				return _OSD_INPUT_D3;
			break;
		}
	}
	return currentPort;
}

void HotKeySourceChange(void)
{

		EnumOSDInputPortDef ucPortTemp = GET_OSD_INPUT_PORT_OSD_ITEM();
		if (_OSD_INPUT_AUTO == ucPortTemp)
		{
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
			ucPortTemp = _OSD_INPUT_D0;
		}
		ucPortTemp = GetNextActivePort(ucPortTemp);

		SET_FORCE_POW_SAV_STATUS(_FALSE);
		SET_OSD_INPUT_PORT_OSD_ITEM(ucPortTemp);
		
		DirectSourceSelect();
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

}
#else
void HotKeySourceChange(void) 
{
	EnumOSDInputPortDef ucStart = GET_OSD_INPUT_PORT_OSD_ITEM();
	EnumOSDInputPortDef ucPortTemp = ucStart;

	if (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
	{

		SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(_TRUE);
		// DebugMessageSystem("Power Normal 1- Select Key", SysPowerGetPowerStatus());
		if ((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING))
		{
			DebugMessageSystem("Power Normal 3- Select Key", 0);
			SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
		}
		return;
	}

	ucPortTemp++;

	if (ucPortTemp > _OSD_INPUT_D3)
	{
		ucPortTemp = _OSD_INPUT_AUTO;
	}

	SET_OSD_INPUT_PORT_OSD_ITEM(ucPortTemp);
	//DebugMessageOsd("HotKeySourceChange", ucPortTemp);

	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	OsdDispOsdMessage(_OSD_DISP_INPUTSOURCE_CHANGE_MSG);
	ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_HOTKEY_SOURCE_CHANGE);

	if (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING) == _TRUE)
	{
		ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
	}
	//DirectSourceSelect();
}
#endif //(_CUSTOMER_TYPE == _CUSTOMER_AWERONET)

void MenuMainUpDown(void)
{
	int i = 0;
	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_INFO:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_7);
			SET_OSD_STATE(_MENU_SETUP);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_SETUP);
			
			break;
		case _MENU_INPUT:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_1);
			SET_OSD_STATE(_MENU_INFO);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_INFO);
			
			break;
		case _MENU_PICTURE:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_2);
			SET_OSD_STATE(_MENU_INPUT);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_INPUT);
			
			break;
		case _MENU_COLOR:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_3);
			SET_OSD_STATE(_MENU_PICTURE);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_PICTURE);
			
			break;
		case _MENU_SCREEN:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_4);
			SET_OSD_STATE(_MENU_COLOR);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_COLOR);
			
			break;
		case _MENU_AUDIO:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_5);
			SET_OSD_STATE(_MENU_SCREEN);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_SCREEN);
			
			break;
		case _MENU_SETUP:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_6);
			SET_OSD_STATE(_MENU_AUDIO);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_AUDIO);
			
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_INFO:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_2);
			SET_OSD_STATE(_MENU_INPUT);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_INPUT);
			break;
		case _MENU_INPUT:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_3);
			SET_OSD_STATE(_MENU_PICTURE);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_PICTURE);
			break;
		case _MENU_PICTURE:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_4);
			SET_OSD_STATE(_MENU_COLOR);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_COLOR);
			break;
		case _MENU_COLOR:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_5);
			SET_OSD_STATE(_MENU_SCREEN);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_SCREEN);
			break;
		case _MENU_SCREEN:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_6);
			SET_OSD_STATE(_MENU_AUDIO);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_AUDIO);
			break;
		case _MENU_AUDIO:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_7);
			SET_OSD_STATE(_MENU_SETUP);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_SETUP);
			break;
		case _MENU_SETUP:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_1);
			SET_OSD_STATE(_MENU_INFO);
			OsdFuncClearOsd(ROW(0), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 12);	// Clear Item	
			OsdSubMenuPageDraw(_MENU_INFO);
			break;

		}
		break;
	}
}

void MenuServiceUpDown(void)
{

	switch (GET_KEYMESSAGE())
	{
	case _UP_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE1:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_5);
			SET_OSD_STATE(_MENU_SERVICE_OLED);
			break;
		case _MENU_SERVICE2:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_1);
			SET_OSD_STATE(_MENU_SERVICE1);
			break;
		case _MENU_SERVICE3:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_2);
			SET_OSD_STATE(_MENU_SERVICE2);
			break;
		case _MENU_SERVICE_USERASSIGN:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_3);
			SET_OSD_STATE(_MENU_SERVICE3);
			break;
		case _MENU_SERVICE_OLED:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_4);
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN);
			break;
		}
		break;

	case _DOWN_KEY_MESSAGE:
		switch (GET_OSD_STATE())
		{
		case _MENU_SERVICE1:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_2);
			SET_OSD_STATE(_MENU_SERVICE2);
			break;
		case _MENU_SERVICE2:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_3);
			SET_OSD_STATE(_MENU_SERVICE3);
			break;
		case _MENU_SERVICE3:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_4);
			SET_OSD_STATE(_MENU_SERVICE_USERASSIGN);
			break;
		case _MENU_SERVICE_USERASSIGN:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_5);
			SET_OSD_STATE(_MENU_SERVICE_OLED);
			break;
		case _MENU_SERVICE_OLED:
			SetFocus(_MENU_SECTION_0, ROW_OFFSET + _ITEM_1);
			SET_OSD_STATE(_MENU_SERVICE1);
			break;
		}
		break;
	}
}

void MenuInputSelect(void)
{
	//OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_INPUT_SOURCE1);
	//OsdSubMenuPageDraw(_MENU_INPUT);
	//OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuPictureSelect(void)	
{
	//OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
	SET_OSD_STATE(_MENU_PICTURE_BLACKLEVEL);
	//OsdSubMenuPageDraw(_MENU_PICTURE);				

	//sdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuColorSelect(void)	
{
	//OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
#if(_MEDICAL_SURGICAL == _ON)
	SET_OSD_STATE(_MENU_COLOR_SURGICAL);
	OsdSubMenuPageDraw(_MENU_COLOR);
#else
	SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
	//OsdSubMenuPageDraw(_MENU_COLOR);
#endif
	//OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

void MenuScreenSelect(void)
{
	//OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SCREEN_OVERSCAN);

	//OsdSubMenuPageDraw(_MENU_SCREEN);
	//OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}

//void MenuDisplaySelect(void)	
//{
//	if(GET_OSD_DISPLAY_MODE()==_OSD_DM_1P)	
//	{
//		SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//		SET_OSD_STATE(_MENU_DISPLAY_ROTATE);
//	}
//	else
//	{
//		SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_2);
//		SET_OSD_STATE(_MENU_DISPLAY_SOURCE1);
//	}
//	OsdSubMenuPageDraw(_MENU_DISPLAY);
//}
//void MenuOsdSelect(void)	
//{
//	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//	SET_OSD_STATE(_MENU_OSD_H_POSITION);
//	OsdSubMenuPageDraw(_MENU_OSD_SETTING);
//}
void MenuAudioSelect(void)	
{
	//OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
	SET_OSD_STATE(_MENU_AUDIO_INFO);
	//OsdSubMenuPageDraw(_MENU_AUDIO);
	//OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
//void MenuDpOptionSelect(void)	
//{
//	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//	SET_OSD_STATE(_MENU_DP_OPTION_VERSION);
//	OsdSubMenuPageDraw(_MENU_DP_OPTION);
//}
void MenuSetupSelect(void)	
{
	//OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SETUP_POWERSAVE);
	//OsdSubMenuPageDraw(_MENU_SETUP);
	//OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
#if(_ENABLE_MENU_VGA == _ON)	
void MenuVgaSelect(void)	
{
	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
	SET_OSD_STATE(_MENU_VGA_AUTO);
	//OsdSubMenuPageDraw(_MENU_VGA);
}
#endif
#if(_ENABLE_MENU_EXPAND == _ON)
//void MenuHeatControlSelect(void)	
//{
//	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//	SET_OSD_STATE(_MENU_HEATCON_FAN);
//	OsdSubMenuPageDraw(_MENU_HEAT_CONTROL);
//}
//void MenuDimControlSelect(void)	
//{
//	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//	SET_OSD_STATE(_MENU_DIMCON_AUTO);
//	OsdSubMenuPageDraw(_MENU_DIM_CONTROL);
//}
//void MenuVideoWallSelect(void)	
//{
//	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);
//	SET_OSD_STATE(_MENU_VIDEOWALL_VIDEOWALL);
//	OsdSubMenuPageDraw(_MENU_VIDEO_WALL);
//}
#endif
void MenuInfoSelect(void)	
{
	//OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	//SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_1);	
	//SET_OSD_STATE(_MENU_INFO_FW_VERSION);
	//OsdSubMenuPageDraw(_MENU_INFO);
	//OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuService1Select(void)	
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_SCREENTEST);
	OsdSubMenuPageDraw(_MENU_SERVICE1);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuService2Select(void) 
{
OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_MIN);
	OsdSubMenuPageDraw(_MENU_SERVICE2);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuService3Select(void) 
{
OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_DP_OPTION);
	OsdSubMenuPageDraw(_MENU_SERVICE3);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuServiceUserAssignSelect(void)
{
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_USERASSIGN_UP);
	OsdSubMenuPageDraw(_MENU_SERVICE_USERASSIGN);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
}
void MenuServiceOledSelect(void)
{
#if (_ENABLE_MENU_OLED == _ON)
	OsdWindowDrawingByFontHighlight(_MENU_SECTION_TRANSPARENT_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH), HEIGHT(ROW_OFFSET + 10 + 2), _CP_DARKGRAY, FG_COLOR(_CP_WHITE), BGCOLOR(0));
	SetFocus(_MENU_SECTION_1, ROW_OFFSET + _ITEM_1);
	SET_OSD_STATE(_MENU_SERVICE_OLED_OFFRS);
	OsdSubMenuPageDraw(_MENU_SERVICE_OLED);
	OsdFuncCloseWindow(_MENU_SECTION_TRANSPARENT_WINDOW);
#endif
}

void SetFocus(BYTE ucSection, BYTE ucRow)	
{
	
	if(ucSection == _MENU_SECTION_0)
	{
		ScalerOsdWindowDisable(_MENU_SECTION_0_SELECT_WINDOW);	
		OsdWindowDrawingByFontOrg(_MENU_SECTION_0_SELECT_WINDOW, ROW(ucRow), COL(_MENU_SECTION_0_WIN_X), WIDTH(_MENU_SECTION_0_WIDTH), HEIGHT(1), _CP_GRAY );	
	}
	else if(ucSection == _MENU_SECTION_1)
	{
		ScalerOsdWindowDisable(_MENU_SECTION_1_SELECT_WINDOW);
		OsdWindowDrawingByFontOrg(_MENU_SECTION_1_SELECT_WINDOW, ROW(ucRow), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(1), _CP_GRAY);
	}
	else if (ucSection == _MENU_SECTION_1_SUB)
	{
		ScalerOsdWindowDisable(_MENU_SECTION_1_SELECT_WINDOW);
		OsdWindowDrawingByFontOrg(_MENU_SECTION_1_SELECT_WINDOW, ROW(ucRow), COL(_MENU_SECTION_1_WIN_X + 12), WIDTH(_MENU_SECTION_1_WIDTH - 12), HEIGHT(1), _CP_GRAY);
	}
	else if(ucSection == _MENU_SECTION_2)
	{
		ScalerOsdWindowDisable(_MENU_SECTION_2_SELECT_WINDOW);
		OsdWindowDrawingByFontOrg(_MENU_SECTION_2_SELECT_WINDOW, ROW(ucRow), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(1), _CP_GRAY);
	}
	else if(ucSection == _MENU_SECTION_SOURCE)
	{
		ScalerOsdWindowDisable(_MENU_SECTION_2_SELECT_WINDOW);
		OsdWindowDrawingByFontOrg(_MENU_SECTION_2_SELECT_WINDOW, ROW(ucRow), COL(0), WIDTH(_MENU_SOURCE_WIDTH), HEIGHT(1), _CP_GRAY);
	}
	else if(ucSection == _MENU_SECTION_DIALOG)	
	{
		ScalerOsdWindowDisable(_MENU_SECTION_2_SELECT_WINDOW);
		OsdWindowDrawingByFontOrg(_MENU_SECTION_2_SELECT_WINDOW, ROW(ucRow), COL(0), WIDTH(_OSD_DIALOG_BOX_WIDTH), HEIGHT(1), _CP_GRAY);
	}
	else if (ucSection == _MENU_SECTION_USERASSIGN)
	{
		ScalerOsdWindowDisable(_MENU_SECTION_2_SELECT_WINDOW);
		OsdWindowDrawingByFontOrg(_MENU_SECTION_2_SELECT_WINDOW, ROW(ucRow), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH+5), HEIGHT(1), _CP_GRAY);
	}
}
void ClearFocus(BYTE ucSection)	
{
	if(ucSection == _MENU_SECTION_0)
		//ScalerOsdWindowDisable(_OSD_WINDOW_5_1);
		ScalerOsdWindowDisable(_MENU_SECTION_0_SELECT_WINDOW);
	else if(ucSection == _MENU_SECTION_1)
		//ScalerOsdWindowDisable(_OSD_WINDOW_5_2);
		ScalerOsdWindowDisable(_MENU_SECTION_1_SELECT_WINDOW);
	else if(ucSection == _MENU_SECTION_2)
		//ScalerOsdWindowDisable(_OSD_WINDOW_5_3);
		ScalerOsdWindowDisable(_MENU_SECTION_2_SELECT_WINDOW);
	else if(ucSection == _MENU_SECTION_SOURCE)
		//ScalerOsdWindowDisable(_OSD_WINDOW_5_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
}

void MenuSourceSelect(void)	
{	
	
	g_usAdjustValue = GET_OSD_ITEM_INDEX();
	printf("#1SourceSelect:%d\n\r",(int)g_usAdjustValue);	
	
	#if(_ENABLE_MENU_VGA != _ON)	
		#if(_ENABLE_MENU_SOURCE_AUTO == _ON)	
			if(g_usAdjustValue >= _OSD_INPUT_A0)g_usAdjustValue += 1; 
		#else
			if(g_usAdjustValue >= _OSD_INPUT_AUTO)g_usAdjustValue += 2;
		#endif
	#else
		if(g_usAdjustValue >= _OSD_INPUT_AUTO)g_usAdjustValue += 1;
	#endif	
	printf("#2SourceSelect:%d\n\r",(int)g_usAdjustValue);	
	

	
	g_usBackupValue = g_usAdjustValue;				
	
	if(GET_OSD_DP_VERSION_HOTKEY_DISP() == _OFF)
    {
        if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
        {
        	SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);	 
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);	 
			
            if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
            {
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
                if(GET_OSD_DP_MST() != _MST_OFF)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }
#endif
                SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
				{
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_A0)
			{
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_A0_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D0)
			{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D0_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D1)
			{
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D1_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D2)
			{
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D2_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D3)
			{
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D3_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D4)
			{
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D4_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D5)
			{
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D5_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D6)
			{
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D6_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
#if(_DP_MST_SUPPORT == _ON)
			UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
			RTDNVRamSaveOSDData();
#endif
		}
		else
		{
			/*
			if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
			(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
			(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
			{
				ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);	
			}
			else
			{
				OsdDispDisableOsd();
			}
			*/
			OsdDispReactiveOsdMessage();	
		}
		SET_OSD_STATE(_MENU_NONE);		
	}
}

void DirectSourceSwitchInputPort(BYTE ucInputPort)
{

	if(ucInputPort == _OSD_INPUT_AUTO)
	{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
		if(GET_OSD_DP_MST() != _MST_OFF)
		{
			SET_OSD_DP_MST(_MST_OFF);
		}
#endif
		SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
		SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

		if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
		{
			UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
			UserCommonNVRamSaveSystemData();//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
		}
	}
	else
	{		
		SET_FORCE_POW_SAV_STATUS(_FALSE);
		SysSourceSwitchInputPort(ucInputPort + 1);
		SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
		SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

		if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
		(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
		{
			UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
			UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
			UserCommonNVRamSaveSystemData();//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
		}
	}
#if(_DP_MST_SUPPORT == _ON)
		UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
		RTDNVRamSaveOSDData();
#endif
	SET_OSD_STATE(_MENU_NONE);
	//------------------------------------------------------------------------------
}

void DirectSourceSelect(void)	
{	
	/*
	g_usAdjustValue = GET_OSD_ITEM_INDEX();
	#if(_ENABLE_MENU_VGA != _ON)	
		if(g_usAdjustValue >= _OSD_INPUT_A0)g_usAdjustValue += 1; 
	#endif	
	*/
	g_usBackupValue = g_usAdjustValue;				
	
	
	if(GET_OSD_DP_VERSION_HOTKEY_DISP() == _OFF)
    {
        if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
        {
        	SET_OSD_INPUT_PORT_OSD_ITEM(g_usAdjustValue);	 
			//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);	 
			RTDNVRamSaveOSDData();
			
            if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
            {
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
                if(GET_OSD_DP_MST() != _MST_OFF)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }
#endif
                SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
				{
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					UserCommonNVRamSaveSystemData();
				}
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_A0)
			{
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_A0_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D0)
			{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D0_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					UserCommonNVRamSaveSystemData();
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D1)
			{
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D1_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					UserCommonNVRamSaveSystemData();
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D2)
			{
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D2_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					UserCommonNVRamSaveSystemData();
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D3)
			{
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D3_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					//SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					UserCommonNVRamSaveSystemData();
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D4)
			{
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D4_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D5)
			{
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D5_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
			else if(GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D6)
			{
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D6_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#else
				return;
#endif
			}
#if(_DP_MST_SUPPORT == _ON)
			UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
			RTDNVRamSaveOSDData();
#endif
		}
		else
		{
			/*
			if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
			(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
			(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
			{
				ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
			}
			else
			{
				OsdDispDisableOsd();
			}
			*/
			OsdDispReactiveOsdMessage();	
		}
		SET_OSD_STATE(_MENU_NONE);
	}
}

void MenuSourceExit(void)	
{
	if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
	{
		SET_OSD_INPUT_PORT_OSD_ITEM(g_usBackupValue);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	}

	OsdDispDisableOsd();

	OsdDispReactiveOsdMessage();	
/*	
	if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
	(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
	(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
	{
		ScalerTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);		
		//SET_OSD_POWER_SAVING_SHOW_MENU(_FALSE);		//  Reactive Power Saving Message flag
	}
*/	
	
}

void NoOperation (void){}
	

code void (*OperationTable[][8])(void) =		// OperationTable
{
	// MENU                   // SELECT                   // LEFT                    // RIGHT                   // UP                      // DOWN                    // EXIT                    // SOURCE
    { MenuNoneMenu,           HotKeySourceChange,         HotKeyUserAssignSelect,  	 HotKeyUserAssignSelect,    HotKeyUserAssignSelect,    HotKeyUserAssignSelect,    MenuExit,                  MenuInputSource           },	//_MENU_NONE	
    { MenuNoneMenu,           NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_DIALOG_MESSAGE	
	{ MenuSourceExit,         MenuSourceSelect,           NoOperation,               NoOperation,               MenuSourceItemUpDown,      MenuSourceItemUpDown,      MenuExit,                  MenuSourceExit     	   },	//_MENU_HOTKEY_SOURCE	 
   	{ MenuExit,               NoOperation,                HotKeyVolumeSubLeftRight,  HotKeyVolumeSubLeftRight,  NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_HOTKEY_VOLUME	
   	//{ MenuExit,               NoOperation,                HotKeyMuteSubLeftRight,    HotKeyMuteSubLeftRight,    NoOperation,               NoOperation,               MenuExit,                  MenuInputSource         },	//_MENU_HOTKEY_MUTE		
   	{ MenuExit,               NoOperation,                HotKeyMuteSelect,          HotKeyMuteSelect,          NoOperation,          NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_HOTKEY_MUTE	
	{ MenuExit, 			  NoOperation,                HotKeyBlkSubLeftRight,     HotKeyBlkSubLeftRight,     HotKeyBlkSubLeftRight,     HotKeyBlkSubLeftRight,     MenuExit,                  NoOperation			},//_MENU_HOTKEY_BACKLIGHT
	{ MenuExit,               NoOperation,                HotKeyContrastSubLeftRight,HotKeyContrastSubLeftRight,HotKeyContrastSubLeftRight,HotKeyContrastSubLeftRight,MenuExit,                  NoOperation		   	},//_MENU_HOTKEY_CONTRAST
	{ MenuExit,               NoOperation,                HotKeyBrightnessSubLeftRight,HotKeyBrightnessSubLeftRight,HotKeyBrightnessSubLeftRight,HotKeyBrightnessSubLeftRight, MenuExit,         NoOperation	           },//_MENU_HOTKEY_BRIGHTNESS	
	{ MenuExit,               NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_HOTKEY_DISPLAY_MODE	
   	{ MenuExit,               NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_HOTKEY_PIP_SWAP	
   	{ MenuExit,               NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_HOTKEY_BLK_ONOFF	


   	{ MenuExit,               MenuInfoSelect,             NoOperation,               MenuInfoSelect,            MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  MenuInputSource           },	//_MENU_INFO
	{ MenuExit,               MenuInputSelect,            MenuExit,                  MenuInputSelect,           MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  NoOperation               },	//_MENU_INPUT	
	{ MenuExit,               MenuPictureSelect,          MenuExit,                  MenuPictureSelect,         MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  NoOperation               },   //_MENU_PICTURE
	{ MenuExit,               MenuColorSelect,            MenuExit,                  MenuColorSelect,           MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  NoOperation               },   //_MENU_COLOR
	{ MenuExit,               MenuScreenSelect,           MenuExit,                  MenuScreenSelect,          MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  NoOperation               },   //_MENU_SCREEN
	{ MenuExit,               MenuAudioSelect,            MenuExit,                  MenuAudioSelect,           MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  NoOperation               },   //_MENU_AUDIO
	{ MenuExit,               MenuSetupSelect,            MenuExit,                  MenuSetupSelect,           MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  NoOperation               },   //_MENU_SETUP
	{ MenuExit,               MenuSetupSelect,            MenuExit,                  MenuSetupSelect,           MenuMainUpDown,            MenuMainUpDown,            MenuExit,                  NoOperation               },   //_MENU_VGA

	{ MenuExit,               MenuService1Select,         MenuExit,                  MenuService1Select,        MenuServiceUpDown,         MenuServiceUpDown,         MenuExit,                  NoOperation               },   //_MENU_SERVICE1
	{ MenuExit,               MenuService2Select,         MenuExit,                  MenuService2Select,        MenuServiceUpDown,         MenuServiceUpDown,         MenuExit,                  NoOperation               },   //_MENU_SERVICE2
	{ MenuExit,               MenuService3Select,         MenuExit,                  MenuService3Select,        MenuServiceUpDown,         MenuServiceUpDown,         MenuExit,                  NoOperation               },   //_MENU_SERVICE3
	{ MenuExit,               MenuServiceUserAssignSelect,MenuExit,                  MenuServiceUserAssignSelect, MenuServiceUpDown,         MenuServiceUpDown,         MenuExit,                  NoOperation               },   //_MENU_SERVICE_USERASSIGN
	{ MenuExit,               MenuServiceOledSelect,      MenuExit,                  MenuServiceOledSelect,     MenuServiceUpDown,         MenuServiceUpDown,         MenuExit,                  NoOperation               },   //_MENU_SERVICE_OLED//_MENU_INPUT	
	{ MenuInputSubExit,       MenuInputSource1Select,     MenuInputSubExit,          MenuInputSource1Select,    MenuInputSubUpDown,        MenuInputSubUpDown,        MenuExit,                  NoOperation               },   //_MENU_INPUT_SOURCE1
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               }, 	//_MENU_INPUT_SOURCE1_ADJ
	{ MenuInputSubExit,       MenuInputSource2Select,     MenuInputSubExit,          MenuInputSource2Select,    MenuInputSubUpDown,        MenuInputSubUpDown,        MenuExit,                  NoOperation               }, 	//_MENU_INPUT_SOURCE2
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               }, 	//_MENU_INPUT_SOURCE2_ADJ
	{ MenuInputSubExit,       MenuInputSource3Select,     MenuInputSubExit,          MenuInputSource3Select,    MenuInputSubUpDown,        MenuInputSubUpDown,        MenuExit,                  NoOperation               }, 	//_MENU_INPUT_SOURCE3
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               }, 	//_MENU_INPUT_SOURCE3_ADJ
	{ MenuInputSubExit,       MenuInputSource4Select,     MenuInputSubExit,          MenuInputSource4Select,    MenuInputSubUpDown,        MenuInputSubUpDown,        MenuExit,                  NoOperation               }, 	//_MENU_INPUT_SOURCE4
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               }, 	//_MENU_INPUT_SOURCE4_ADJ
//_MENU_PICTURE
	{ MenuPictureSubExit,     MenuPictureBlacklevelSelect,MenuPictureSubExit,        MenuPictureBlacklevelSelect,MenuPictureSubUpDown,     MenuPictureSubUpDown,      MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_BLACKLEVEL
	{ MenuPictureBlacklevelAdjExit, MenuPictureBlacklevelAdjSelect, MenuPictureSubLeftRight, MenuPictureSubLeftRight, MenuPictureSubLeftRight,MenuPictureSubLeftRight,MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_BLACKLEVEL_ADJ
	{ MenuPictureSubExit,     MenuPictureContrastSelect,  MenuPictureSubExit,        MenuPictureContrastSelect, MenuPictureSubUpDown,      MenuPictureSubUpDown,      MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_CONTRAST
	{ MenuPictureContrastAdjExit, MenuPictureContrastAdjSelect, MenuPictureSubLeftRight, MenuPictureSubLeftRight,MenuPictureSubLeftRight,  MenuPictureSubLeftRight,   MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_CONTRAST_ADJ
	{ MenuPictureSubExit,     MenuPictureChromaSelect,    MenuPictureSubExit,        MenuPictureChromaSelect,   MenuPictureSubUpDown,      MenuPictureSubUpDown,      MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_CHROMA
	{  MenuPictureChromaAdjExit, MenuPictureChromaAdjSelect,MenuPictureSubLeftRight,   MenuPictureSubLeftRight, MenuPictureSubLeftRight,   MenuPictureSubLeftRight,   MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_CHROMA_ADJ
	{ MenuPictureSubExit,     MenuPictureSharpnessSelect, MenuPictureSubExit,        MenuPictureSharpnessSelect,MenuPictureSubUpDown,      MenuPictureSubUpDown,      MenuExit,                  NoOperation               },	//_MENU_PICTURE_SHARPNESS
	{ MenuPictureSharpnessAdjExit, MenuPictureSharpnessAdjSelect, MenuPictureSubLeftRight, MenuPictureSubLeftRight, MenuPictureSubLeftRight,MenuPictureSubLeftRight,  MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_SHARPNESS_ADJ
	{ MenuPictureSubExit,     MenuPictureGammaSelect,     MenuPictureSubExit,        MenuPictureGammaSelect,    MenuPictureSubUpDown,      MenuPictureSubUpDown,      MenuPictureSubUpDown,      NoOperation               }, 	//_MENU_PICTURE_GAMMA
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuPictureSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_PICTURE_GAMMA_ADJ
	{ MenuPictureSubExit,     MenuPictureResetToDefaultSelect, MenuPictureSubExit,   MenuPictureSubLeftRight,   MenuPictureSubUpDown,      MenuPictureSubUpDown,      MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_RESETTODEFAULT
#if (_ENABLE_MENU_REGION == _ON)
	{ MenuPictureSubExit,     MenuPictureRegionSelect,    MenuPictureSubLeftRight,   MenuPictureSubLeftRight,   MenuPictureSubUpDown,      MenuPictureSubUpDown,      MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_REGION
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuPictureSubLeftRight,   MenuPictureSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               }, 	//_MENU_PICTURE_REGION_ADJ
#endif
//_MENU_COLOR
	{ MenuColorSubExit,       MenuColorTemperatureSelect, MenuColorSubExit,          MenuColorTemperatureSelect,MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },  	//_MENU_COLOR_TEMPERATURE
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuColorSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_COLOR_TEMPERATURE_ADJ
	{ MenuColorSubExit, 	  MenuColorSurgicalSelect,    MenuColorSubExit,          MenuColorTemperatureSelect,MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation			   },	//_MENU_COLOR_SURGICAL
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuColorSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation			   },	//_MENU_COLOR_SURGICAL_ADJ
	{ MenuColorSubExit,       MenuColorBIASRSelect,       MenuColorSubExit,          MenuColorBIASRSelect,      MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },  	//_MENU_COLOR_BIAS_R
	{ MenuColorBIASRAdjExit,  MenuColorBIASRAdjSelect,    MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuExit,                  NoOperation               }, 	//_MENU_COLOR_BIAS_R_ADJ
	{ MenuColorSubExit,       MenuColorBIASGSelect,       MenuColorSubExit,          MenuColorBIASGSelect,      MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },  	//_MENU_COLOR_BIAS_G
	{ MenuColorBIASGAdjExit,  MenuColorBIASGAdjSelect,    MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuExit,                  NoOperation               }, 	//_MENU_COLOR_BIAS_G_ADJ
	{ MenuColorSubExit,       MenuColorBIASBSelect,       MenuColorSubExit,          MenuColorBIASBSelect,      MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },  	//_MENU_COLOR_BIAS_B
	{ MenuColorBIASBAdjExit,  MenuColorBIASBAdjSelect,    MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuExit,                  NoOperation               }, 	//_MENU_COLOR_BIAS_B_ADJ
	{ MenuColorSubExit,       MenuColorGainRSelect,       MenuColorSubExit,          MenuColorGainRSelect,      MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },  	//_MENU_COLOR_GAIN_R
	{ MenuColorGainRAdjExit,  MenuColorGainRAdjSelect,    MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuExit,                  NoOperation               }, 	//_MENU_COLOR_GAIN_R_ADJ
	{ MenuColorSubExit,       MenuColorGainGSelect,       MenuColorSubExit,          MenuColorGainGSelect,      MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },  	//_MENU_COLOR_GAIN_G
	{ MenuColorGainGAdjExit,  MenuColorGainGAdjSelect,    MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuExit,                  NoOperation               }, 	//_MENU_COLOR_GAIN_G_ADJ
	{ MenuColorSubExit,       MenuColorGainBSelect,       MenuColorSubExit,          MenuColorGainBSelect,      MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               }, 	//_MENU_COLOR_GAIN_B
	{ MenuColorGainBAdjExit,  MenuColorGainBAdjSelect,    MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuExit,                  NoOperation               }, 	//_MENU_COLOR_GAIN_B_ADJ
	{ MenuColorSubExit,       MenuColorEffectSelect,      MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },   //_MENU_COLOR_EFFECT
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_COLOR_EFFECT_ADJ
	{ MenuColorSubExit,       MenuColorGammaSelect,       MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               },  	//_MENU_COLOR_GAMMA
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuColorSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_COLOR_GAMMA_ADJ
#if (_ENABLE_MENU_REGION == _ON)
	{ MenuColorSubExit,       MenuColorRegionSelect,      MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuColorSubUpDown,        MenuColorSubUpDown,        MenuExit,                  NoOperation               }, 	//_MENU_COLOR_REGION
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuColorSubLeftRight,     MenuColorSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               }, 	//_MENU_COLOR_REGION_ADJ
#endif
//_MENU_SCREEN
	{ MenuScreenSubExit,      MenuScreenOverscanSelect,   MenuScreenSubExit,         MenuScreenOverscanSelect,  MenuScreenSubUpDown,       MenuScreenSubUpDown,       MenuExit,                  NoOperation               },  	//_MENU_SCREEN_OVERSCAN,
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuScreenSubLeftRight,    MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_SCREEN_OVERSCAN_ADJ,
	{ MenuScreenSubExit,      MenuScreenAspectSelect,     MenuScreenSubExit,         MenuScreenAspectSelect,    MenuScreenSubUpDown,       MenuScreenSubUpDown,       MenuExit,                  NoOperation               },  	//_MENU_SCREEN_ASPECT,
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuScreenSubLeftRight,    MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_SCREEN_ASPECT_ADJ,
	{ MenuScreenSubExit,      MenuScreenMonoColorSelect,  MenuScreenSubExit,         MenuScreenMonoColorSelect, MenuScreenSubUpDown,       MenuScreenSubUpDown,       MenuExit,                  NoOperation               },  	//_MENU_SCREEN_MONO_COLOR,
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuScreenSubLeftRight,    MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_SCREEN_MONO_COLOR_ADJ,
	{ MenuScreenSubExit,      MenuScreenRotateSelect,     MenuScreenSubExit,         MenuScreenRotateSelect,    MenuScreenSubUpDown,       MenuScreenSubUpDown,       MenuExit,                  NoOperation               },  	//_MENU_SCREEN_ROTATE,
	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuScreenSubLeftRight,    MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_SCREEN_ROTATE_ADJ,
//	{ MenuScreenSubExit,      MenuScreenModeSelect,       MenuScreenSubExit,         MenuScreenModeSelect,      MenuScreenSubUpDown,       MenuScreenSubUpDown,       MenuExit,                  NoOperation               },  	//_MENU_SCREEN_DISPLAY_MODE,
//	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuScreenSubLeftRight,    MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_SCREEN_DISPLAY_MODE_ADJ,
//	{ MenuScreenSubExit,      MenuScreenPIPPositionSelect,MenuScreenSubExit,         MenuScreenPIPPositionSelect, MenuScreenSubUpDown,     MenuScreenSubUpDown,       MenuExit,                  NoOperation               },  	//_MENU_SCREEN_PIP_POSITION,
//	{ MenuSection3Exit,       MenuSection3ItemSelect,     MenuSection3Exit,          MenuScreenSubLeftRight,    MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },  	//_MENU_SCREEN_PIP_POSITION_ADJ,
//	{ MenuScreenSubExit,      MenuScreenPIPSizeSelect,    MenuScreenSubExit,         MenuScreenPIPSizeSelect,   MenuScreenSubUpDown,       MenuScreenSubUpDown,       MenuExit,                  NoOperation               },  	//_MENU_SCREEN_PIP_SIZE,
//	{ MenuScreenPIPSizeAdjExit,MenuScreenPIPSizeAdjSelect,MenuScreenSubLeftRight,    MenuScreenSubLeftRight,    MenuScreenSubLeftRight,    MenuScreenSubLeftRight,    MenuExit,                  NoOperation               }, 	//_MENU_SCREEN_PIP_SIZE_ADJ,

	{MenuAudioSubExit,        NoOperation,                MenuAudioSubExit,          NoOperation,               MenuAudioSubUpDown,        MenuAudioSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_AUDIO_INFO
	{MenuAudioSubExit,        MenuAudioVolumeSelect,      MenuAudioSubExit,          MenuAudioVolumeSelect,     MenuAudioSubUpDown,        MenuAudioSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_AUDIO_VOLUME
	{MenuAudioVolumeAdjExit,  MenuAudioVolumAdjSelect,    MenuAudioSubLeftRight,     MenuAudioSubLeftRight,     MenuAudioSubLeftRight,     MenuAudioSubLeftRight,     MenuExit,                  NoOperation               },	//_MENU_AUDIO_VOLUME_ADJ
	{MenuAudioSubExit,        MenuAudioMuteSelect,        MenuAudioSubExit,          MenuAudioMuteSelect,       MenuAudioSubUpDown,        MenuAudioSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_AUDIO_MUTE
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuAudioSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_AUDIO_MUTE_ADJ
	{MenuAudioSubExit,        MenuAudioSourceSelect,      MenuAudioSubLeftRight,     MenuAudioSubLeftRight,     MenuAudioSubUpDown,        MenuAudioSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_AUDIO_SOURCE
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuAudioSubLeftRight,     MenuAudioSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_AUDIO_SOURCE_ADJ

	{MenuSetupSubExit,        MenuSetupPowerSaveSelect,   MenuSetupSubExit,          MenuSetupPowerSaveSelect,  MenuSetupSubUpDown,        MenuSetupSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_SETUP_POWERSAVE
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuSetupSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SETUP_POWERSAVE_ADJ
	{MenuSetupSubExit,        MenuSetupKeyLockSelect,     MenuSetupSubExit,          MenuSetupKeyLockSelect,    MenuSetupSubUpDown,        MenuSetupSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_SETUP_KEYLOCK
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuSetupSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SETUP_KEYLOCK_ADJ
	{MenuSetupSubExit,        MenuSetupBacklightSelect,   MenuSetupSubExit,          MenuSetupBacklightSelect,  MenuSetupSubUpDown,        MenuSetupSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_SETUP_BACKLIGHT
	{MenuSetupBacklightAdjExit, MenuSetupBacklightAdjSelect, MenuSetupSubLeftRight,  MenuSetupSubLeftRight,     MenuSetupSubLeftRight,     MenuSetupSubLeftRight,     MenuExit,                  NoOperation               },	//_MENU_SETUP_BACKLIGHT_ADJ
	{MenuSetupSubExit,        MenuSetupBacklightControlSelect, MenuSetupSubExit,     MenuSetupBacklightControlSelect, MenuSetupSubUpDown,  MenuSetupSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_SETUP_BACKLIGHT_CONTROL
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuSetupSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SETUP_BACKLIGHT_CONTROL_ADJ
	{MenuSetupSubExit,        MenuSetupResetSelect,       MenuSetupSubExit,          MenuSetupResetSelect,      MenuSetupSubUpDown,        MenuSetupSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_SETUP_RESET
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuSetupSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SETUP_RESET_ADJ
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
	{MenuSetupSubExit,        MenuSetupStabilizerSelect,  MenuSetupSubExit,          NoOperation,               MenuSetupSubUpDown,        MenuSetupSubUpDown,        MenuExit,                  NoOperation               },	//_MENU_SETUP_STABILIZER_CONTROL
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuSetupSubLeftRight,     MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               }, 	//_MENU_SETUP_STABILIZER_CONTROL_ADJ
#endif
	{MenuSetupSubExit,        NoOperation,                MenuSetupSubLeftRight,     MenuSetupSubLeftRight,     MenuSetupSubUpDown,        MenuSetupSubUpDown,        MenuExit,                  NoOperation               },   //_MENU_SETUP_SETID
																																																			
	{MenuService1SubExit,     MenuServiceScreenTestSelect,MenuService1SubExit,       MenuServiceScreenTestSelect, MenuService1SubUpDown,   MenuService1SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_SCREENTEST
	{MenuService1SubExit,     NoOperation,                MenuService1SubExit,       NoOperation,               MenuService1SubUpDown,     MenuService1SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_TEMPERATURE
	{MenuService1SubExit,     MenuServiceWhiteBalranceSelect, MenuService1SubExit,   MenuServiceWhiteBalranceSelect, MenuService1SubUpDown,MenuService1SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_WHITEBALANCE
	{MenuService1SubExit,     MenuServiceD0NameSelect,    MenuService1SubExit,       MenuServiceD0NameSelect,   MenuService1SubUpDown,     MenuService1SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_D0NAME
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },   //_MENU_SERVICE_D0NAME_ADJ
	{MenuService1SubExit,     MenuServiceD1NameSelect,    MenuService1SubExit,       MenuServiceD1NameSelect,   MenuService1SubUpDown,     MenuService1SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_D1NAME
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },   //_MENU_SERVICE_D1NAME_ADJ
	{MenuService1SubExit,     MenuServiceD2NameSelect,    MenuService1SubExit,       MenuServiceD2NameSelect,   MenuService1SubUpDown,     MenuService1SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_D2NAME
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },   //_MENU_SERVICE_D2NAME_ADJ
	{MenuService1SubExit,     MenuServiceD3NameSelect,    MenuService1SubExit,       MenuServiceD3NameSelect,   MenuService1SubUpDown,     MenuService1SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_D3NAME 
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },   //_MENU_SERVICE_D3NAME_ADJ
	
	{MenuService2SubExit,     MenuServiceBacklightMinSelect, MenuService2SubExit,    MenuServiceBacklightMinSelect, MenuService2SubUpDown, MenuService2SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_BACKLIGHT_MIN
	{MenuServiceBacklightMinAdjExit, MenuServiceBacklightMinAdjSelect, MenuServiceSubLeftRight, MenuServiceSubLeftRight,  MenuServiceSubLeftRight, MenuServiceSubLeftRight, MenuExit,            NoOperation               },   //_MENU_SERVICE_BACKLIGHT_MIN_ADJ
	{MenuService2SubExit,     MenuServiceBacklightMaxSelect, MenuService2SubExit,    MenuServiceBacklightMaxSelect, MenuService2SubUpDown, MenuService2SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_BACKLIGHT_MAX
	{MenuServiceBacklightMaxAdjExit, MenuSerivceBacklightMaxAdjSelect, MenuServiceSubLeftRight, MenuServiceSubLeftRight,  MenuServiceSubLeftRight, MenuServiceSubLeftRight, MenuExit,            NoOperation               },   //_MENU_SERVICE_BACKLIGHT_MAX_ADJ
	{MenuService2SubExit,     MenuServiceBacklightInvertSelect, MenuService2SubExit, MenuServiceBacklightInvertSelect, MenuService2SubUpDown, MenuService2SubUpDown,  MenuExit,                  NoOperation               },   //_MENU_SERVICE_BACKLIGHT_INVERT
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },   //_MENU_SERVICE_BACKLIGHT_INVERT_ADJ
	{MenuService2SubExit,     MenuServiceBacklightFreqSelect, MenuService2SubExit,   MenuServiceBacklightFreqSelect, MenuService2SubUpDown,MenuService2SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_BACKLIGHT_FREQ //SERVICE1
	{MenuServiceBacklightFreqAdjExit, MenuSerivceBacklightFreqAdjSelect, MenuServiceSubLeftRight, MenuServiceSubLeftRight,  MenuServiceSubLeftRight, MenuServiceSubLeftRight,MenuExit,           NoOperation               }, 	//_MENU_SERVICE_BACKLIGHT_FREQ_ADJ
	{MenuService2SubExit,     MenuServiceLogoSelect,      MenuService2SubExit,       MenuServiceLogoSelect,     MenuService2SubUpDown,     MenuService2SubUpDown,     MenuExit,                  NoOperation               },   //_MENU_SERVICE_LOGO //SERVICE1
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          NoOperation,               MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },   //_MENU_SERVICE_LOGO_ADJ
	{MenuService2SubExit, MenuServiceLogoListSelect, MenuService2SubExit, MenuServiceLogoListSelect, MenuService2SubUpDown, MenuService2SubUpDown, MenuExit, NoOperation},														//_MENU_SERVICE_LOGO_LIST //SERVICE1
	{MenuServiceLogoListAdjExit, MenuServiceLogoListAdjSelect, MenuServiceSubLeftRight, MenuServiceSubLeftRight, MenuServiceSubLeftRight, MenuServiceSubLeftRight, MenuExit, NoOperation},										//_MENU_SERVICE_LOGO_LIST_ADJ
	
	#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
	{MenuService2SubExit,     MenuServiceStabiluxSelect,  MenuService2SubExit,       NoOperation,               MenuService2SubUpDown,     MenuService2SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_STABILUX
	{MenuServiceStabiluxAdjExit, MenuSerivceStabiluxAdjSelect, MenuServiceSubLeftRight, MenuServiceSubLeftRight,MenuServiceSubLeftRight,   MenuServiceSubLeftRight,   MenuExit,                  NoOperation               }, 	//_MENU_SERVICE_STABILUX_ADJ
#endif

	{MenuService3SubExit,     MenuServiceDPSelect,        MenuService3SubExit,       MenuServiceDPSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_DP_OPTION,
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuServiceSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SERVICE_DP_OPTION_ADJ,
	{MenuService3SubExit,     MenuServiceLSSelect,        MenuService3SubExit,       MenuServiceLSSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_LIGHTSENSOR,
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuServiceSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SERVICE_LIGHTSENSOR_ADJ,
	{MenuService3SubExit,     MenuServiceFANSelect,       MenuService3SubExit,       MenuServiceFANSelect,      MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_FAN_OPTION,
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuServiceSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SERVICE_FAN_OPTION_ADJ,
	{MenuService3SubExit,     MenuServiceFanSpeedSelect,  MenuService3SubExit,       MenuServiceFanSpeedSelect, MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_FAN_SPEED,
	{MenuServiceFanSpeedAdjExit, MenuSerivceFanSpeedAdjSelect, MenuServiceSubLeftRight, MenuServiceSubLeftRight,MenuServiceSubLeftRight,   MenuServiceSubLeftRight,   MenuExit,                  NoOperation               },	//_MENU_SERVICE_FAN_SPEED_ADJ,
	{MenuService3SubExit, MenuServiceUserBackupConfigSelect, MenuService3SubExit, MenuServiceUserBackupConfigSelect, MenuService3SubUpDown, MenuService3SubUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USER_BACKUP_CONFIG
	{MenuSection3Exit, MenuSection3ItemSelect, MenuSection3Exit, MenuServiceSubLeftRight, MenuSection3ItemUpDown, MenuSection3ItemUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USER_BACKUP_CONFIG_ADJ
	{MenuService3SubExit, MenuServiceRestoreFactoryDefaultSelect, MenuService3SubExit, MenuServiceRestoreFactoryDefaultSelect, MenuService3SubUpDown, MenuService3SubUpDown, MenuExit, NoOperation},//_MENU_SERVICE_RESTORE_FACTORY_DEFAULT
	{MenuSection3Exit, MenuSection3ItemSelect, MenuSection3Exit, MenuServiceSubLeftRight, MenuSection3ItemUpDown, MenuSection3ItemUpDown, MenuExit, NoOperation},//_MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ
		//USERASSIGN
	{MenuServiceUserAssignSubExit, MenuServiceUserAssignUpKeySelect, MenuServiceUserAssignSubExit, MenuServiceUserAssignUpKeySelect, MenuServiceUserAssignSubUpDown, MenuServiceUserAssignSubUpDown, MenuExit, NoOperation}, //_MENU_SERVICE_USERASSIGN_UP,
	{MenuSection3Exit, MenuSection3ItemSelect, MenuSection3Exit, MenuServiceSubLeftRight, MenuSection3ItemUpDown, MenuSection3ItemUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USERASSIGN_UP_ADJ,
	{MenuServiceUserAssignSubExit, MenuServiceUserAssignDownKeySelect, MenuServiceUserAssignSubExit, MenuServiceUserAssignDownKeySelect, MenuServiceUserAssignSubUpDown, MenuServiceUserAssignSubUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USERASSIGN_DOWN,
	{MenuSection3Exit, MenuSection3ItemSelect, MenuSection3Exit, MenuServiceSubLeftRight, MenuSection3ItemUpDown, MenuSection3ItemUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USERASSIGN_DOWN_ADJ,
	{MenuServiceUserAssignSubExit, MenuServiceUserAssignLeftKeySelect, MenuServiceUserAssignSubExit, MenuServiceUserAssignLeftKeySelect, MenuServiceUserAssignSubUpDown, MenuServiceUserAssignSubUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USERASSIGN_LEFT,
	{MenuSection3Exit, MenuSection3ItemSelect, MenuSection3Exit, MenuServiceSubLeftRight, MenuSection3ItemUpDown, MenuSection3ItemUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USERASSIGN_LEFT_ADJ,
	{MenuServiceUserAssignSubExit, MenuServiceUserAssignRightKeySelect, MenuServiceUserAssignSubExit, MenuServiceUserAssignRightKeySelect, MenuServiceUserAssignSubUpDown, MenuServiceUserAssignSubUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USERASSIGN_RIGHT,
	{MenuSection3Exit, MenuSection3ItemSelect, MenuSection3Exit, MenuServiceSubLeftRight, MenuSection3ItemUpDown, MenuSection3ItemUpDown, MenuExit, NoOperation},//_MENU_SERVICE_USERASSIGN_RIGHT_ADJ,
	{MenuServiceOLEDSubExit,     MenuServiceOFFRSSelect,     MenuServiceOLEDSubExit,       MenuServiceOFFRSSelect,    MenuServiceOledSubUpDown,     MenuServiceOledSubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_OLED_OFFRS,
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuServiceSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SERVICE_OLED_OFFRS_ADJ,
	{MenuServiceOLEDSubExit,     MenuServiceJBSelect,        MenuServiceOLEDSubExit,       MenuServiceJBSelect,       MenuServiceOledSubUpDown,     MenuServiceOledSubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_OLED_JB,
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuServiceSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SERVICE_OLED_JB_ADJ,
	{MenuServiceOLEDSubExit,     MenuServiceTimeSelect,      MenuServiceOLEDSubExit,       MenuServiceTimeSelect,     MenuServiceOledSubUpDown,     MenuServiceOledSubUpDown,     MenuExit,                  NoOperation               },	//_MENU_SERVICE_OLED_SEQUENCE_TIME,
	{MenuSection3Exit,        MenuSection3ItemSelect,     MenuSection3Exit,          MenuServiceSubLeftRight,   MenuSection3ItemUpDown,    MenuSection3ItemUpDown,    MenuExit,                  NoOperation               },	//_MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ,

	{MenuService3SubExit,     MenuServiceDPSelect,        MenuService3SubExit,       MenuServiceDPSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_VGA_AUTO
	{MenuService3SubExit,     MenuServiceDPSelect,        MenuService3SubExit,       MenuServiceDPSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_VGA_AUTO_ADJ
	{MenuService3SubExit,     MenuServiceDPSelect,        MenuService3SubExit,       MenuServiceDPSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_VGA_H_POSI
	{MenuService3SubExit,     MenuServiceDPSelect,        MenuService3SubExit,       MenuServiceDPSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_VGA_V_POSI
	{MenuService3SubExit,     MenuServiceDPSelect,        MenuService3SubExit,       MenuServiceDPSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_VGA_CLOCK
	{MenuService3SubExit,     MenuServiceDPSelect,        MenuService3SubExit,       MenuServiceDPSelect,       MenuService3SubUpDown,     MenuService3SubUpDown,     MenuExit,                  NoOperation               },	//_MENU_VGA_PHASE
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	{ MenuInfoSubExit,        MenuInfoSubExit,            MenuInfoSubExit,           MenuInfoSubExit,           MenuInfoSubExit,           MenuInfoSubExit,           MenuExit,                  MenuInputSource           },	//_MENU_INFO_FW_VERSION	 
	{ MenuInfoSubExit,        MenuInfoSubExit,            NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_INFO_SERIAL_NUM
	
	{ NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_INFO_MODEL		
    { NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_INFO_INPUT
    { NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_INFO_FORAMT
    { NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },  	//_MENU_INFO_RANGE
    { NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_INFO_COLOR_TEMP
    { NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_HOTKEY_INFORMATION
#if (_ENABLE_MENU_OLED == _ON)
    { NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_HOTKEY_OFFRS
#endif	

	
	{ NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU_END
	{ NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU
	{ NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU
	{ NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU
	{ NoOperation,            NoOperation,                NoOperation,               NoOperation,               NoOperation,               NoOperation,               MenuExit,                  MenuInputSource           },	//_MENU


};

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
