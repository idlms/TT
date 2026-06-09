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
#include "RL6449_Series_GlobalInclude.h"

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
StructOsdInfo g_stOsdInfo;

WORD g_usAdjustValue;
WORD g_usBackupValue;
BYTE g_ucLogoTimerCounter;
BYTE g_usItemNum = 0;
bit b1BlueToothStatus = _OFF ;	//Eric_170929
//#if	(_ENABLE_LIGHT_SENSOR == _ON)
//extern bit Initialize_TLS2561(void);
//#endif
#if( _ENABLE_VIDEO_WALL == _ON)
// H, V Number 로 Display Number 자동 계산.
BYTE GetVideoWallDisplayNumber(void);
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserOsdHandler(void);
void RTDOsdSystemFlowProc(void);
void RTDOsdEventMsgProc(void);
//void RTDOsdHotKeyProc(void) ; //Eric_171009_01
void DispServiceMenu(void);
#if(_PIXEL_SHIFT_SUPPORT == _ON)
BYTE setShift = 0;
BYTE pixShiftTime = 0;
#endif

BYTE psTimecount = 0; //Power Save 1Min 이상 count 용.
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define TO_ENTER_INTO_SERVICE_CLERA_0_STATE   0
#define TO_ENTER_INTO_SERVICE_MENU_1_STATE    1
#define TO_ENTER_INTO_SERVICE_DOWN_2_STATE    2
#define TO_ENTER_INTO_SERVICE_DOWN_3_STATE    3
#define TO_ENTER_INTO_SERVICE_DOWN_4_STATE    4
#define TO_ENTER_INTO_SERVICE_UP_5_STATE      5
#define TO_ENTER_INTO_SERVICE_UP_6_STATE      6
#define TO_ENTER_INTO_SERVICE_UP_7_STATE      7
#define TO_ENTER_INTO_SERVICE_DOWN_8_STATE    8
#define TO_ENTER_INTO_SERVICE_UP_9_STATE      9
#define TO_ENTER_INTO_SERVICE_DOWN_10_STATE   10

BYTE ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit IsServiceMenu(BYTE ui8KeyMask)
{
	bit bRetVal = _FALSE;
	if (GET_OSD_STATE() == _MENU_NONE)ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
	switch (ui8EnterIntoServiceMenuState)
	{
	case TO_ENTER_INTO_SERVICE_CLERA_0_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _MENU_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_MENU_1_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_MENU_1_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_2_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_2_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_3_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_3_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_4_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_4_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_5_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_5_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_6_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_6_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_7_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_7_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_8_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_8_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _UP_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_UP_9_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_UP_9_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		ui8EnterIntoServiceMenuState = (ui8KeyMask == _DOWN_KEY_MESSAGE) ? TO_ENTER_INTO_SERVICE_DOWN_10_STATE : TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	case TO_ENTER_INTO_SERVICE_DOWN_10_STATE:
		//DebugMessageSystem("ServiceMenuState", ui8EnterIntoServiceMenuState);
		if (ui8KeyMask == _SELECT_KEY_MESSAGE) bRetVal = _TRUE;
		ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	default:
		ui8EnterIntoServiceMenuState = TO_ENTER_INTO_SERVICE_CLERA_0_STATE;
		break;
	}
	return bRetVal;
}

void UserOsdHandler(void)
{
    RTDOsdSystemFlowProc();
    RTDOsdEventMsgProc();
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

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREESYNC_OD_MEASURE == _ON)
                UserAdjustFREESYNCODMeasure();
#endif
				
#if(_CUSTOMER_TYPE	== _CUSTOMER_THRUPUT)
				//SET_OSD_DOUBLE_SIZE(_ON);
				//OsdDispShowLogo();
				//UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
				//ScalerTimerActiveTimerEvent(SEC(7), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
				SET_OSD_DOUBLE_SIZE(_OFF);
#elif(_CUSTOMER_TYPE	== _CUSTOMER_VIMSE)
				SET_OSD_DOUBLE_SIZE(_OFF);
				OsdDispShowMainLogo();
#if (_ENABLE_MENU_OLED == _ON)
				UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
				UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
				//			ScalerTimerActiveTimerEvent(SEC(40), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
				//			ScalerTimerDelayXms(20000);		// 20 sec Delay
				ScalerTimerDelayXms(4000);		// 4 sec Delay

				UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
				ScalerTimerDelayXms(100);		// 1 sec Delay

				OsdDispShowLogo();
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
#elif(_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
				SET_OSD_DOUBLE_SIZE(_ON);
				OsdDispShowLogo();
#if (_ENABLE_MENU_OLED == _ON)
				UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
				UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
				SET_OSD_DOUBLE_SIZE(_OFF);
#elif(_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
				SET_OSD_DOUBLE_SIZE(_OFF);
				OsdDispShowLogo();
#if (_ENABLE_MENU_OLED == _ON)
				UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
				UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
				SET_OSD_DOUBLE_SIZE(_OFF);
#else
#if (_ENABLE_MENU_OLED == _ON)
				UserCommonInterfacePanelPowerAction(_PANEL_ON);
#endif
				SET_OSD_DOUBLE_SIZE(_OFF);
#endif //#if(_CUSTOMER_TYPE	== _CUSTOMER_THRUPUT)
            }

#if	(_ENABLE_LIGHT_SENSOR == _ON)
			//InitLightSensor();
			//gpstLightSensorDriver->Init();
			//if (gpstLightSensorDriver->SuccessInitialize())
			//{
			//	ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_CHECK_BACKLIGHT);
			//}
#if(_LIGHT_SENSOR_TYPE == _LIGHT_CM32181)
			Cm32181_init();
			//DebugMessageYHJ("SuccessInitialize_CM3281()", SuccessInitialize_CM3281());
			DebugMessageSystem("SuccessInitialize_CM3281_1", SuccessInitialize_CM3281());
			if (SuccessInitialize_CM3281())
			{
				DebugMessageSystem("SuccessInitialize_CM3281_2", SuccessInitialize_CM3281());
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_CHECK_BACKLIGHT);
			}
			//DebugMessageYHJ("SuccessInitialize_CM3281()", SuccessInitialize_CM3281());
#elif (_LIGHT_SENSOR_TYPE == _LIGHT_TLS2561)
			Initialize_TLS2561();
			if (SuccessInitialize_TLS2561())
			{
				ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_CHECK_BACKLIGHT);
			}
#else
#endif

#endif

#if	(_ENABLE_FAN_CONTROL == _ON)
#if (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
			Initialize_ADT7470();
#elif (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
			//DebugMessageOsd("FAN-CONTROL", _CUSTOMER_TYPE);
			Initialize_MAX31785();
#endif
			if (SuccessInitializeFanControl())
			{
				ApplyFanControl(_TRUE);
				ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_CHECK_FANCONTROL);
			}
#endif

#if	(_ENABLE_SELF_CHECK == _ON)
			Initialize_TCS34725();
			if (SuccessInitialize_TCS34725())
			{
				ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_CHECK_SELF);
			}
#endif
//#if (_PANEL_IDX_NAME == _PANEL_DV550QUM_N10	)
//			ScalerTimerActiveTimerEvent(SEC(1000), _USER_TIMER_EVENT_PANEL_I2C);
//#endif
#if(_CUSTOMER_TYPE == _CUSTOMER_MRK)
			ScalerTimerActiveTimerEvent(SEC(10), _USER_TIMER_EVENT_BOOT_GPIO1_DELAY);
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
			if (GET_OSD_PIXEL_SHIFT_STATUS() == _ON)
			{
				ScalerTimerActiveTimerEvent(MIN(1), _USER_TIMER_EVENT_PIXEL_SHIFT);
			}
#endif

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
					OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
#if(_PIXEL_SHIFT_SUPPORT == _ON)
					setShift = 0;
					pixShiftTime = 0;
					UserAdjustPixelShifting(9); // 초기화
#endif
				}
            }
			// //DebugMessageYHJ(" MODE ", GET_AUDIO_DET());
			// if ((GET_AUDIO_DET & _EANBLE_AUDIO_DET) == _EANBLE_AUDIO_DET)
			// {
			// 	PCB_AMP_MUTE(_AMP_MUTE_ON);
			// }
			// else
			// {
			// 	PCB_AMP_MUTE(_AMP_MUTE_OFF);
			// }
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
                    ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
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
#if (_ENABLE_MENU_OLED == _ON)
					UserCommonInterfacePanelPowerAction(_PANEL_ON);
#else
					UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
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
//#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
//            if((GET_OSD_STATE() != _MENU_NONE) &&
//               ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) &&
//               (GET_OSD_STATE() != _MENU_HOT_INPUT_ADJUST))
//#else
			if ((GET_OSD_STATE() != _MENU_NONE) && ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _UP_KEY_MESSAGE) || (GET_KEYMESSAGE() == _DOWN_KEY_MESSAGE)))
//#endif
            {
                SET_KEYREPEATENABLE();
            }
		//if(GET_KEYMESSAGE() >= _PC_POWER_IR_MESSAGE) //Eric_171009_01
		//{
		//	RTDOsdHotKeyProc();
		//}
			if (IsServiceMenu(GET_KEYMESSAGE()))
			{
				//DebugMessageSystem("=DISPLAY SERVICE MENU=", GET_KEYMESSAGE());
				DispServiceMenu();
				return;
			}
        }

        if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
        {
            RTDFactoryMenuOperation();
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

// 180306_Delete
//            if((GET_OSD_STATE() >= _MENU_PICTURE) && (GET_OSD_STATE() <= _MENU_COLOR_PCM_SOFT_PROFT_ADJUST))
//            {
//                OsdDispMainMenuKeyInfo(GET_KEYMESSAGE(), _OSD_HIGHLIGHT);
//            }

            (*OperationTable[GET_OSD_STATE()])();

            if(GET_OSD_IN_FACTORY_MENU_STATUS() == _FALSE)
            {
                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
                {
                    if(GET_OSD_TIME_OUT() <= 10)
                    {
                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
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
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdEventMsgProc(void)
{
    switch(GET_OSD_EVENT_MESSAGE())
    {
        case _OSDEVENT_SHOW_NOSIGNAL_MSG:
#if (_ENABLE_MENU_OLED == _ON)
			ScalerDisplayVboMac(_OFF);
#endif
            OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);
#if (_ENABLE_MENU_OLED == _ON)
			DebugMessageOsd("_OSDEVENT_SHOW_NOSIGNAL_MSG", PCB_AC_DETECT());
			ScalerTimerDelayXms(50);
			ScalerDisplayVboMac(_ON);
#else
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
			if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOCABLE_MSG:
#if (_ENABLE_MENU_OLED == _ON)
			ScalerDisplayVboMac(_OFF);
#endif
            OsdDispOsdMessage(_OSD_DISP_NOCABLE_MSG);
#if (_ENABLE_MENU_OLED == _ON)
			ScalerTimerDelayXms(50);
			ScalerDisplayVboMac(_ON);
#else
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
			if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOSUPPORT_MSG:
#if (_ENABLE_MENU_OLED == _ON)
			ScalerDisplayVboMac(_OFF);
#endif
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            OsdDispOsdMessage(_OSD_DISP_NOSUPPORT_MSG);
#if (_ENABLE_MENU_OLED == _ON)
			ScalerTimerDelayXms(50);
			ScalerDisplayVboMac(_ON);
#else
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
			if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG:
            OsdDispOsdMessage(_OSD_DISP_FAIL_SAFE_MODE_MSG);
            break;

        case _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            //SET_OSD_STATE(_MENU_HOT_INPUT_ADJUST);
            OsdFuncSetOsdItemFlag();
            g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
			OsdDispHotKeySourceMenu();

			if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
#if (_ENABLE_MENU_OLED == _OFF)
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
            break;

        case _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG:

            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
//            SET_OSD_STATE(_MENU_HOTKEY_DDCCI);
//            OsdDispHotKeyOptionMenu(_HOTKEY_DDCCI);
			if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
#if (_ENABLE_MENU_OLED == _OFF)
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif

            break;

        case _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG:
#if (_ENABLE_MENU_OLED == _ON)
			if ((GET_JB_COMP_STATUS() == _ON) || (GET_OFF_RS_STATUS() == _ON))
			{
				DebugMessageOsd("Compensation Running & Restart", 0);
				// ScalerTimerReactiveTimerEvent(SEC(10), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
				ScalerTimerReactiveTimerEvent(SEC(10), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);


			}
			else
#endif
			{
#if (_ENABLE_MENU_OLED == _OFF)
				OsdDispDisableOsd();
#endif
				OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);

#if (_ENABLE_MENU_OLED == _OFF)
				UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif

				ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
			}
            break;

        case _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG:

            OsdDispDisableOsd();
            SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
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

#if(_CUSTOMER_TYPE != _CUSTOMER_MAO_00 )
            if(GET_OSD_STATE() == _MENU_NONE)
            {
 //               OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
 //               ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
#endif 			
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
//            SET_OSD_STATE(_MENU_HOTKEY_DP_OPTION);

            if(SysSourceGetSourceType() == _SOURCE_DP)
            {
                if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                {
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
                }
                else if(SysSourceGetInputPort() == _D1_INPUT_PORT)
                {
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
                }
                else if(SysSourceGetInputPort() == _D2_INPUT_PORT)
                {
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
                }
                else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                {
 //                   OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
                }
            }
            else
            {
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
 //               OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
#elif (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
 //               OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
#elif (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
 //               OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
#elif (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
 //               OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
#else
                SET_OSD_STATE(_MENU_NONE);
#endif
            }

#if (_ENABLE_MENU_OLED == _OFF)
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
            break;
#endif
#if 0
        case _OSDEVENT_SHOW_CONNECT_BLUETOOTH_MSG:// Eric_170928_00
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);

//		OsdDispDisableOsd();
            OsdDispOsdMessage(_OSD_DISP_CONNECT_BLUETOOTH_YESNO_MSG);
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27+6 - 9), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
            SET_OSD_STATE(_MENU_CONNECT_BLUETOOTH_ADJUST);
	
 //           ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
#if (_ENABLE_MENU_OLED == _OFF)
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif
					g_usAdjustValue = _OFF;		
            break;
        case _OSDEVENT_SHOW_DISCONNECT_BLUETOOTH_MSG:// Eric_170928_00
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);

//		OsdDispDisableOsd();

            OsdDispOsdMessage(_OSD_DISP_DISCONNECT_BLUETOOTH_YESNO_MSG);
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27 - 9), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
            SET_OSD_STATE(_MENU_DISCONNECT_BLUETOOTH_ADJUST);
			
 //           ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
		 b1BlueToothStatus = _OFF;

#if (_ENABLE_MENU_OLED == _OFF)
		 UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
#endif   
 			g_usAdjustValue = _OFF;		
            break;
#endif
        default:
            break;
    }

    SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}

extern void SysUartSetTxCommand(BYTE ucTxCmd, BYTE ucTxStatus, BYTE ucTxData);
void RTDOsdUartMsgProc(BYTE ucUartCmd, BYTE ucUartData)
{
	BYTE ucUartCmdAction = _FALSE;
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
				SysUartSetTxCommand(_UART_CMD2_POWER, _SUCCESS, 0x00);  // OFF
			else SysUartSetTxCommand(_UART_CMD2_POWER, _SUCCESS, 0x01); // ON
		}
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
		else if (ucUartData == 0x05)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_P1_INPUT_SEL, _SUCCESS, GET_OSD_INPUT_PORT_OSD_ITEM());  // OFF
		}
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			if (ucUartData == 0x01)
			{
				SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_AUTO);
			}
			else
			{
				SET_OSD_INPUT_PORT_OSD_ITEM(ucUartData);
			}
			switch (GET_OSD_INPUT_PORT_OSD_ITEM())
			{
			case _OSD_INPUT_AUTO: // auto
				SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
				{
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#if(_DP_MST_SUPPORT == _ON)
				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif                            
				break;
#if(_A0_INPUT_PORT_TYPE !=_A0_NO_PORT) 
			case _OSD_INPUT_A0: // A0
				SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_A0);
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_A0_INPUT_PORT);

				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)
				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif                            


				break;
#endif

#if(_D0_INPUT_PORT_TYPE !=_D0_NO_PORT) 
			case _OSD_INPUT_D0: // D0
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
				g_usVolumePowerForPopo = _ON;
				PCB_AMP_MUTE(_AMP_MUTE_ON);
				DebugMessageAudio("PCB_AMP_MUTE(D2Port)   0000000", 0);
#endif					 
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D0_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
				if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
				{
					ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
					RTDNVRamSaveOSDData();
				}
#else
				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif
#endif
				break;

#endif


#if(_D1_INPUT_PORT_TYPE !=_D1_NO_PORT) 
			case _OSD_INPUT_D1:	//D1
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
				g_usVolumePowerForPopo = _ON;
				PCB_AMP_MUTE(_AMP_MUTE_ON);
				DebugMessageAudio("PCB_AMP_MUTE(D2Port)   1111111", 0);
#endif	
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D1_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
				if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
				{
					ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
					RTDNVRamSaveOSDData();
				}
#else
				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif
#endif
				break;

#endif

#if(_D2_INPUT_PORT_TYPE !=_D2_NO_PORT) 
			case _OSD_INPUT_D2:	//D2
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
				g_usVolumePowerForPopo = _ON;
				PCB_AMP_MUTE(_AMP_MUTE_ON);
				DebugMessageAudio("PCB_AMP_MUTE(D2Port)   22222", 0);
#endif				
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D2_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
				if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
				{
					ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
					RTDNVRamSaveOSDData();
				}
#else
				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif
#endif
				break;

#endif

#if(_D3_INPUT_PORT_TYPE !=_D3_NO_PORT) 
			case _OSD_INPUT_D3:	//D3
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
				g_usVolumePowerForPopo = _ON;
				PCB_AMP_MUTE(_AMP_MUTE_ON);
				DebugMessageAudio("PCB_AMP_MUTE(D2Port)   333333", 0);
#endif	
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D3_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)

				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif
				break;
#endif

#if(_D4_INPUT_PORT_TYPE !=_D4_NO_PORT) 
			case _OSD_INPUT_D4:	//D4
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D4_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)

				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif

				break;

#endif

#if(_D5_INPUT_PORT_TYPE !=_D5_NO_PORT) 
			case _OSD_INPUT_D5:	//D5
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D5_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)
				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif


				break;
#endif

#if(_D6_INPUT_PORT_TYPE !=_D6_NO_PORT) 
			case _OSD_INPUT_D6:	//D6
				SET_FORCE_POW_SAV_STATUS(_FALSE);
				SysSourceSwitchInputPort(_D6_INPUT_PORT);
				SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
					(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
				{
					UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}

#if(_DP_MST_SUPPORT == _ON)
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
				if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
				{
					ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
					RTDNVRamSaveOSDData();
				}
#else
				ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				RTDNVRamSaveOSDData();
#endif
#endif

				break;
#endif

			default:
				break;
			}
#if(_DP_MST_SUPPORT == _ON)
			ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#endif
		}
		break;
	
	case _UART_CMD2_ASPECT:
		//			if((ucUartData == 0x00) && (GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort() != _OSD_ASPECT_RATIO_FULL)))
		if (ucUartData == 0x00)
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x01)
			//			else if((ucUartData == 0x01) && (GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort() != _OSD_ASPECT_RATIO_16_BY_9)))
		{
			SET_OSD_ASPECT_RATIO_TYPE( _OSD_ASPECT_RATIO_16_BY_9);
			ucUartCmdAction = _SUCCESS;

		}
		else if (ucUartData == 0x02)
			//			else if((ucUartData == 0x02) && (GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort() != _OSD_ASPECT_RATIO_4_BY_3)))
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_4_BY_3);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x03)
			//			else if((ucUartData == 0x03) && (GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort() != _OSD_ASPECT_RATIO_5_BY_4)))
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_5_BY_4);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0x04)
			//			else if((ucUartData == 0x04) && (GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort() != _OSD_ASPECT_RATIO_ORIGIN)))
		{
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_ORIGIN);
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == 0xff)
		{
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _SUCCESS, GET_OSD_ASPECT_RATIO_TYPE());  // OFF
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
			ucUartData = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			SysUartSetTxCommand(_UART_CMD2_BACKLIGHT, _SUCCESS, ucUartData);  // OFF
		}
		else
		{
			SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(ucUartData, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
			UserAdjustBacklight(GET_OSD_BACKLIGHT());
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;
	case _UART_CMD2_CONTRAST:
		if (ucUartData == 0xff)
		{
			ucUartData = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
			SysUartSetTxCommand(_UART_CMD2_CONTRAST, _SUCCESS, ucUartData);  // OFF
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
			SysUartSetTxCommand(_UART_CMD2_BRIGHTNESS, _SUCCESS, ucUartData);  // OFF
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
#if(_TECNINT_DICOM)
		else if (ucUartData == _GAMMA_RC2)
		{
			ucUartCmdAction = _SUCCESS;
		}
		else if (ucUartData == _GAMMA_RC3)
		{
			ucUartCmdAction = _SUCCESS;
		}
#endif
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

			if (GET_OSD_GAMMA() != _GAMMA_OFF)
			{
				UserAdjustGamma(GET_OSD_GAMMA());
				ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
				UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#endif
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
#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
			UserAdjustColorEffectMode();
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;

		// 2017.04.11 - SUH-ADD
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
#if (_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
		if (ucUartData == 0x99)
		{
			ucUartCmdAction = _SUCCESS;

			ucUartData = 0x01;
		}
		if (ucUartData == 0x01 && ucUartCmdAction == _FALSE)
		{
			ucUartCmdAction = _SUCCESS;
			ucUartData = 0x00;
		}
#else
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
#endif
		if (ucUartCmdAction == _SUCCESS)
		{
			SET_OSD_VOLUME_MUTE(ucUartData);
#if(_AUDIO_SUPPORT == _ON)
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
#if(_AUDIO_SUPPORT == _ON)
			UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		break;
#if (_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE) 
	case _UART_CMD2_AUDIO_VOL_P:
	{
		//BYTE vol = GET_OSD_VOLUME();
		//if(vol < 100)vol++;
		//SET_OSD_VOLUME_MUTE(_FALSE);
		//SET_OSD_VOLUME(vol);
#if(_AUDIO_SUPPORT == _ON)
			//UserAdjustAudioVolume(GET_OSD_VOLUME());
		SET_KEYMESSAGE(_VOL_P_IR_MESSAGE);
		//RTDNVRamSaveOsdUserData();
		//OsdDispHotKeyVolumeMenu();
#endif
	}
	break;
	case _UART_CMD2_AUDIO_VOL_M:
	{
		//BYTE vol = GET_OSD_VOLUME();
		//if (vol > 0)vol--;
		//SET_OSD_VOLUME_MUTE(_FALSE);
		//SET_OSD_VOLUME(vol);

#if(_AUDIO_SUPPORT == _ON)
			//UserAdjustAudioVolume(GET_OSD_VOLUME());
		SET_KEYMESSAGE(_VOL_M_IR_MESSAGE);
		//OsdDispHotKeyVolumeMenu();
		//RTDNVRamSaveOsdUserData();
#endif
	}
	break;
	case _UART_CMD2_HDMI1:
	case _UART_CMD2_HDMI2:
	case _UART_CMD2_DP1:
	case _UART_CMD2_DP2:
	{
		EnumOSDInputPortDef port;
		port = _OSD_INPUT_D0;
		switch (ucUartCmd)
		{
		case _UART_CMD2_HDMI1: port = _OSD_INPUT_D2; break;
		case _UART_CMD2_HDMI2: port = _OSD_INPUT_D3; break;
		case _UART_CMD2_DP1: port = _OSD_INPUT_D0; break;
		case _UART_CMD2_DP2: port = _OSD_INPUT_D1; break;
		default:
			break;
		}
		SET_FORCE_POW_SAV_STATUS(_FALSE);
		SET_OSD_INPUT_PORT_OSD_ITEM(port);

		switch (GET_OSD_INPUT_PORT_OSD_ITEM())
		{
		case _OSD_INPUT_AUTO: // auto
			SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
			{
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}
#if(_DP_MST_SUPPORT == _ON)
			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif                            
			break;
#if(_A0_INPUT_PORT_TYPE !=_A0_NO_PORT) 
		case _OSD_INPUT_A0: // A0
			SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_A0);
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_A0_INPUT_PORT);

			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)
			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif                            


			break;
#endif

#if(_D0_INPUT_PORT_TYPE !=_D0_NO_PORT) 
		case _OSD_INPUT_D0: // D0
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
			g_usVolumePowerForPopo = _ON;
			PCB_AMP_MUTE(_AMP_MUTE_ON);
			DebugMessageAudio("PCB_AMP_MUTE(D2Port)   0000000", 0);
#endif					 
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_D0_INPUT_PORT);
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
			if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
			{
				ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
				RTDNVRamSaveOSDData();
			}
#else
			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif
#endif
			break;

#endif


#if(_D1_INPUT_PORT_TYPE !=_D1_NO_PORT) 
		case _OSD_INPUT_D1:	//D1
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
			g_usVolumePowerForPopo = _ON;
			PCB_AMP_MUTE(_AMP_MUTE_ON);
			DebugMessageAudio("PCB_AMP_MUTE(D2Port)   1111111", 0);
#endif	
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_D1_INPUT_PORT);
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
			if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
			{
				ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
				RTDNVRamSaveOSDData();
			}
#else
			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif
#endif
			break;

#endif

#if(_D2_INPUT_PORT_TYPE !=_D2_NO_PORT) 
		case _OSD_INPUT_D2:	//D2
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
			g_usVolumePowerForPopo = _ON;
			PCB_AMP_MUTE(_AMP_MUTE_ON);
			DebugMessageAudio("PCB_AMP_MUTE(D2Port)   22222", 0);
#endif				
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_D2_INPUT_PORT);
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
			if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
			{
				ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
				RTDNVRamSaveOSDData();
			}
#else
			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif
#endif
			break;

#endif

#if(_D3_INPUT_PORT_TYPE !=_D3_NO_PORT) 
		case _OSD_INPUT_D3:	//D3
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
			g_usVolumePowerForPopo = _ON;
			PCB_AMP_MUTE(_AMP_MUTE_ON);
			DebugMessageAudio("PCB_AMP_MUTE(D2Port)   333333", 0);
#endif	
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_D3_INPUT_PORT);
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)

			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif
			break;
#endif

#if(_D4_INPUT_PORT_TYPE !=_D4_NO_PORT) 
		case _OSD_INPUT_D4:	//D4
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_D4_INPUT_PORT);
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)

			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif

			break;

#endif

#if(_D5_INPUT_PORT_TYPE !=_D5_NO_PORT) 
		case _OSD_INPUT_D5:	//D5
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_D5_INPUT_PORT);
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)
			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif


			break;
#endif

#if(_D6_INPUT_PORT_TYPE !=_D6_NO_PORT) 
		case _OSD_INPUT_D6:	//D6
			SET_FORCE_POW_SAV_STATUS(_FALSE);
			SysSourceSwitchInputPort(_D6_INPUT_PORT);
			SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

			if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
				(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
			{
				UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
				UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
			}

#if(_DP_MST_SUPPORT == _ON)
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
			if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
			{
				ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
				RTDNVRamSaveOSDData();
			}
#else
			ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
			RTDNVRamSaveOSDData();
#endif
#endif

			break;
#endif

		default:
			break;
		}
#if(_DP_MST_SUPPORT == _ON)
		ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#endif
	}
	break;
#if (_ENABLE_SELF_CHECK == _ON)
		case _UART_CMD2_SELF_CHECK:
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
				SysUartSetTxCommand(_UART_CMD2_SELF_CHECK, _SUCCESS, u8SelfCheckStatus);
			}
			if (ucUartCmdAction == _SUCCESS)
			{
				if (ucUartData == 0x01)
				{
					SET_OSD_SELF_CHECK_STATUS(_TRUE);
				}
				else
				{
					SET_OSD_SELF_CHECK_STATUS(_FALSE);
				}
			}
			break;
#endif
//	case _UART_CMD2_SPLIT:
//#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
//	{
//		if (GET_OSD_DISPLAY_MODE() != _OSD_DM_2P_LR)	SET_OSD_DISPLAY_MODE(_OSD_DM_2P_LR);
//		else SET_OSD_DISPLAY_MODE(_OSD_DM_1P);
//		UserAdjustDisplayMode();
//#if(_DP_MST_SUPPORT == _ON)
//		ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//#endif
//		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//	}
//#endif
//	break;
//	case _UART_CMD2_QUAD:
//#if(_4P_DISPLAY_SUPPORT == _ON)
//	{
//		if (GET_OSD_DISPLAY_MODE() != _OSD_DM_4P)
//		{
//			SET_OSD_DISPLAY_MODE(_OSD_DM_4P);
//			UserAdjustDisplayMode();
//#if(_DP_MST_SUPPORT == _ON)
//			ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//#endif
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//		}
//		else
//		{
//			if (ucUartData == 0)
//			{
//				SET_OSD_DISPLAY_MODE(_OSD_DM_1P);
//				UserAdjustDisplayMode();
//#if(_DP_MST_SUPPORT == _ON)
//				ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//#endif
//				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			}
//
//		}
//		switch (ucUartData)
//		{
//		case 1:
//		{
//			SET_FORCE_POW_SAV_STATUS(_FALSE);
//			port = GET_OSD_1P_INPUT_SOURCE();
//			if (++port > _D3_INPUT_PORT) port = _D0_INPUT_PORT;
//			SET_OSD_1P_INPUT_SOURCE(port);
//			SysRegionUpdateInterface(_DISPLAY_RGN_LT, port);
//#if(_4P_DISPLAY_SUPPORT == _ON)
//			UserAdjustRegionInputPort(_DISPLAY_RGN_LT, port);
//#endif
//#if(_DP_MST_SUPPORT == _ON)
//			ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//			RTDNVRamSaveOSDData();
//#endif
//		}
//		break;
//		case 2:
//		{
//			SET_FORCE_POW_SAV_STATUS(_FALSE);
//			port = GET_OSD_2P_INPUT_SOURCE();
//			if (++port > _D3_INPUT_PORT) port = _D0_INPUT_PORT;
//			SET_OSD_2P_INPUT_SOURCE(port);
//#if(_4P_DISPLAY_SUPPORT == _ON)
//			UserAdjustRegionInputPort(_DISPLAY_RGN_LB, port);
//#endif
//			RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
//		}
//		break;
//		case 3:
//		{
//			SET_FORCE_POW_SAV_STATUS(_FALSE);
//			port = GET_OSD_3P_INPUT_SOURCE();
//			if (++port > _D3_INPUT_PORT) port = _D0_INPUT_PORT;
//			SET_OSD_3P_INPUT_SOURCE(port);
//#if(_4P_DISPLAY_SUPPORT == _ON)
//			UserAdjustRegionInputPort(_DISPLAY_RGN_RT, port);
//#endif
//			RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
//		}
//		break;
//		case 4:
//		{
//			SET_FORCE_POW_SAV_STATUS(_FALSE);
//			port = GET_OSD_4P_INPUT_SOURCE();
//			if (++port > _D3_INPUT_PORT) port = _D0_INPUT_PORT;
//			SET_OSD_4P_INPUT_SOURCE(port);
//#if(_4P_DISPLAY_SUPPORT == _ON)
//			UserAdjustRegionInputPort(_DISPLAY_RGN_RB, port);
//#endif
//			RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
//		}
//		break;
//		default:
//			break;
//		}
//
//	}
//#endif
//	break;
#endif

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
					if(ucUartData != 0x00) SET_OSD_CLONE_MODE(_OSD_CLONE_OFF);
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
#if(_DP_MST_SUPPORT == _ON)

			ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif	
		}
		break;
	case _UART_CMD2_DP_CLONE:
		if (ucUartData == 0x00 || ucUartData == 0x01)
		{
			if (ucUartData == 0x01) SET_OSD_DP_MST(_MST_OFF);
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

//void RTDOsdHotKeyProc(void)
//{
//	OsdDispDisableOsd();
//
//	switch(GET_KEYMESSAGE())
//	{
//		//case _PC_POWER_IR_MESSAGE:
////			ScalerIRSendNEC(0xff00, 0xBf40);
////			ScalerTimerDelayXms(100);
//			//break;
//
//
////Eric_020180308 : Delete
////            case _PC_IR_MESSAGE:
////    #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
////                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D3_INPUT_PORT))
////                {
////                    SET_FORCE_POW_SAV_STATUS(_FALSE);
////                    SysSourceSwitchInputPort(_D3_INPUT_PORT);
////     //               SET_OSD_STATE(_MENU_INPUT);
////                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
////                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
////    
////                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
////                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
////                    {
////                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
////                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
////                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
////                    }
////    
////    #if(_DP_MST_SUPPORT == _ON)
////                    ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
////                    RTDNVRamSaveOSDData();
////    #endif
////                }
////    #endif // #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
////    
////    		{
////              BYTE pucTempData[0x01];
////    			pucTempData[0] = 0x50;
////    //		ScalerMcuIICWrite(0xc8, 0x01, 0x09, 0x01, pucTempData);
////    	                ScalerMcuHwIICWrite(_EP9461_SLAVE_ADDRESS, 0x01, 0x09, 0x01, pucTempData, _PCB_SYS_EP9461_IIC);
////     					
////             	}
////    		break;
////    
////    
////    		case _HDMI1_IR_MESSAGE:
////    #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
////                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D2_INPUT_PORT))
////                {
////                    SET_FORCE_POW_SAV_STATUS(_FALSE);
////                    SysSourceSwitchInputPort(_D2_INPUT_PORT);
////    //                SET_OSD_STATE(_MENU_INPUT);
////                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
////                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
////    
////                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
////                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
////                    {
////                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
////                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
////                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
////                    }
////    
////    #if(_DP_MST_SUPPORT == _ON)
////                    ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
////                    RTDNVRamSaveOSDData();
////    #endif //#if(_DP_MST_SUPPORT == _ON)
////                }
////    #endif // #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
////    		break;
////    
////            case _HDMI2_IR_MESSAGE:
////    #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
////                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D3_INPUT_PORT))
////                {
////                    SET_FORCE_POW_SAV_STATUS(_FALSE);
////                    SysSourceSwitchInputPort(_D3_INPUT_PORT);
////     //               SET_OSD_STATE(_MENU_INPUT);
////                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
////                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
////    
////                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
////                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
////                    {
////                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
////                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
////                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
////                    }
////    
////    #if(_DP_MST_SUPPORT == _ON)
////                    ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
////                    RTDNVRamSaveOSDData();
////    #endif
////                }
////    #endif // #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
////    
////    		{
////              BYTE pucTempData[0x01];
////    			pucTempData[0] = 0x53;
////    //		ScalerMcuIICWrite(0xc8, 0x01, 0x09, 0x01, pucTempData);
////    	                ScalerMcuHwIICWrite(_EP9461_SLAVE_ADDRESS, 0x01, 0x09, 0x01, pucTempData, _PCB_SYS_EP9461_IIC);
////     					
////             	}
////    		break;
////    
////            case _HDMI3_IR_MESSAGE:
////    #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
////                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D3_INPUT_PORT))
////                {
////                    SET_FORCE_POW_SAV_STATUS(_FALSE);
////                    SysSourceSwitchInputPort(_D3_INPUT_PORT);
////     //               SET_OSD_STATE(_MENU_INPUT);
////                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
////                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
////    
////                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
////                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
////                    {
////                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
////                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
////                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
////                    }
////    
////    #if(_DP_MST_SUPPORT == _ON)
////                    ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
////                    RTDNVRamSaveOSDData();
////    #endif
////                }
////    #endif // #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
////    
////    		{
////              BYTE pucTempData[0x01];
////    			pucTempData[0] = 0x52;
////    //		ScalerMcuIICWrite(0xc8, 0x01, 0x09, 0x01, pucTempData);
////    	                ScalerMcuHwIICWrite(_EP9461_SLAVE_ADDRESS, 0x01, 0x09, 0x01, pucTempData, _PCB_SYS_EP9461_IIC);
////     					
////             	}
////    		break;
////    
////            case _SOURCE_IR_MESSAGE:
////    //Eric_020180307 : Delete
////    //    		CLR_KEYREPEATENABLE();
////    //    
////    //    		if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
////    //    		{
////    //    		    SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);
////    //    
////    //    		    if((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) || (SysPowerGetPowerStatus() == _POWER_STATUS_NOSUPPORT_SAVING))
////    //    		    {
////    //    		        SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
////    //    		    }
////    //    		}
////    //    		else if((SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
////    //    		{
////    //    		    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
////    //    		}
////    //    		else if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
////    //    		{
////    //    		    SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
////    //    		    OsdFuncSetOsdItemFlag();
////    //    		    g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
////    //    		    OsdDispHotKeySourceMenu();
////    //    		}
////    		break;
//
//         //case _HDR_IR_MESSAGE:
//         //   if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//         //   {
// //               SET_OSD_STATE(_MENU_PICTURE);
////                OsdFuncSetOsdItemFlag();
////                OsdDispHDRMenu();
//
//            //}
//            break;
// 
//	
//        default:
//            break;
//
//	}
//}
	
void MenuNone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                SET_OSD_STATE(_MENU_PICTURE);
                OsdFuncSetOsdItemFlag();
                OsdDispMainMenu();
            }
            break;

        case _RIGHT_KEY_MESSAGE:
#if (_ENABLE_MENU_OLED == _OFF)
			if ((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE))
			{
				OsdDispHotKeyBacklightMenu();
			}
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if (_ENABLE_MENU_OLED == _OFF)
			if ((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE))
			{
				OsdDispHotKeyBacklightMenu();
			}
#endif
            break;
		case _UP_KEY_MESSAGE:
			if ((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE))
			{
				OsdDispHotKeyVolumeMenu();
			}
			//setShift = 8;
			//UserAdjustPixelShifting(setShift); // Pixel Shift OFF
			break;

		case _DOWN_KEY_MESSAGE:
			if ((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE))
			{
				OsdDispHotKeyVolumeMenu();
			}
			//if (setShift == 8) setShift = 0;
			//UserAdjustPixelShifting(setShift);
			//setShift++;
			break;
		case _SOURCE_IR_MESSAGE:
        case _SELECT_KEY_MESSAGE:
            // auto adjust
//#if(_VGA_SUPPORT == _ON)
//            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE) && (SysSourceGetSourceType() == _SOURCE_VGA))
//            {
//#if(_FREEZE_SUPPORT == _ON)
//                if(GET_OSD_FREEZE_STATUS() == _ON)
//                {
//                    SET_OSD_FREEZE_STATUS(_OFF);
//                    UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
//                    OsdDispOsdMessage(_OSD_DISP_DISABLE_FREEZE_MSG);
//                    ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
//                }
//#endif
//
//                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
//            }
//#endif
//            // ddcci
//            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
//            {
//                SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(_TRUE);
//
//                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
//                {
//                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
//                }
//            }
//            else if((SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
//            {
// //               SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG);
//            }
			CLR_KEYREPEATENABLE();
			//DebugMessageYHJ("POWER MODE STATE ", SysModeGetModeState());
			if (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) // _MODE_STATUS_POWER_SAVING = 6
			{
				SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);
				//DebugMessageYHJ("GET POWER STATUS ", SysPowerGetPowerStatus());
				if (SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) //_POWER_STATUS_SAVING = 3
				{
					SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL); // _POWER_STATUS_NORMAL = 2
				}
			}
			else if (SysModeGetModeState() == _MODE_STATUS_ACTIVE || SysModeGetModeState() == _MODE_STATUS_NOSIGNAL || SysModeGetModeState() == _MODE_STATUS_NOSUPPORT || SysModeGetModeState() == _MODE_STATUS_SEARCH)
			{
				//DebugMessageYHJ("ACTIVE ", SysModeGetModeState());
				OsdFuncShowSourceMenuCheck();

				OsdDispHotKeySourceMenu();
			}
			//DebugMessageYHJ("GET_OSD_STATE ", GET_OSD_STATE());
			break;

        case _VOL_P_IR_MESSAGE: //170928_02
        case _VOL_M_IR_MESSAGE:					
               if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
    		{			
    			OsdDispDisableOsd();
    			OsdDispHotKeyVolumeMenu();
    		}
			break;
        case _MUTE_IR_MESSAGE:
               if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
    		{			
	    			OsdDispDisableOsd();

			if(GET_OSD_VOLUME_MUTE() == _OFF)
			{
				SET_OSD_VOLUME_MUTE(_ON);
    				OsdDispHotKeyMuteMenu();

			}
			else 
			{
				SET_OSD_VOLUME_MUTE(_OFF);
	    			OsdDispHotKeyVolumeMenu();
			}

#if(_AUDIO_SUPPORT == _ON)
			UserAdjustAudioMuteSwitch();
#endif			
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

    		}
		break;
  //      case _AUDIO_MODE_IR_MESSAGE:
  //             if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
  //  		{			
  //  			OsdDispDisableOsd();
  //  			OsdDispHotKeyAudioMode();
  //  		}

		//break;
  //      case _PICTURE_MODE_IR_MESSAGE:
  //             if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
  //  		{			
  //  			OsdDispDisableOsd();
  //  			OsdDispHotKeyPictureMode();
  //  		}

		//break;
        default:
            break;
    }



	if(GET_KEYMESSAGE() == 0x99)
	{
//		UserCommonHDR10SupportSwitch();
//		UserAdjustAudioMuteSwitch();
//		UserAdjustRGBGamma(0x00);
//		OsdDispHotKeySourceMenuSwitch();

//		OsdDispClearArrow(_DOWN);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//		OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_SHARPNESS());
//                OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DDCCI);
//		OsdDispPanelUniformityMsgSwitch();
//		 OsdDispOsdReset();	
//		 OsdDispShowInformation();
//		OsdDispOsdRotateSwitch();
//		 OsdDispAdvanceMenuReDraw(_HIGH);
//		 OsdDispAdvanceItemCountbyKeyMessage();
//		OsdDispAdvanceItemSelect(GET_OSD_ITEM_INDEX());
//                OsdFuncSixColorAdjust();
//		OsdFuncColorFormatAdjust();
	}	
}

void MenuPicture(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
//			if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_RTS)
			{
				SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
				COsdShowChoosePictureText(_STRING_BACKLIGHT);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
//Eric_020180307 : Delete
//    			else 
//    			{
//    				SET_OSD_STATE(_MENU_PICTURE_ECO);
//    				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//    				ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
//    				ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
//    				ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
//    				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
//    				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
//    				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL-1), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//    				COsdShowChoosePictureText(_STRING_COLOR_EFFECT);
//    			}
			
	//OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BRIGHTNESS());
			break;

		
		case _DOWN_KEY_MESSAGE:        	
        SET_OSD_STATE(_MENU_COLOR);
			
		OsdDispMainMenuItemSelection(_MENU_COLOR-2, _OSD_UNSELECT);	
		OsdDispMainMenuItemSelection(_MENU_COLOR-1, _OSD_SELECT);
		OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
    	COsdShowPageText(_MENU_COLOR);

            break;
        case _UP_KEY_MESSAGE:
           SET_OSD_STATE(_MENU_OTHER);
		   OsdDispMainMenuItemSelection(_MENU_PICTURE-1, _OSD_UNSELECT);
		   OsdDispMainMenuItemSelection(_MENU_OTHER-1, _OSD_SELECT);       		//OsdDispMainMenukeyCursor(_MENU_OTHER-1,0);
		   OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH,_CP_WHITE, _CP_BLUE_65);
		   OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		   OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
           COsdShowPageText(_MENU_OTHER);

            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            OsdDispDisableOsd();
			OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
            break;

        default:
            break;
    }
}


void MenuColor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
#if (_HDR10_SUPPORT == _ON)
			if (GET_OSD_HDR_MODE()!= _HDR10_MODE_OFF)
			{
				SET_OSD_STATE(_MENU_COLOR_HDR);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
				//        OsdWindowDrawingSelect(_OSD_WINDOW_9, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(15), HEIGHT(1), _CP_ORANGE);
				COsdShowChooseColorText(_STRING_HDR);
			}
			else
#endif
			{
				SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
				//        OsdWindowDrawingSelect(_OSD_WINDOW_9, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(15), HEIGHT(1), _CP_ORANGE);
				COsdShowChooseColorText(_STRING_COLORTEMP);
			}
        break;
            
        case _DOWN_KEY_MESSAGE:
		{
			SET_OSD_STATE(_MENU_OSDSETTINGS);
			OsdDispMainMenuItemSelection(_MENU_OSDSETTINGS - 2, _OSD_UNSELECT);
			OsdDispMainMenuItemSelection(_MENU_OSDSETTINGS - 1, _OSD_SELECT);
			OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
			OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);

			COsdShowPageText(_MENU_OSDSETTINGS);

		}
		break;
			
        case _UP_KEY_MESSAGE:
        
				SET_OSD_STATE(_MENU_PICTURE);
				
				OsdDispMainMenuItemSelection(_MENU_COLOR-1, _OSD_UNSELECT);
				OsdDispMainMenuItemSelection(_MENU_PICTURE-1, _OSD_SELECT); 
				OsdFontPut1FuncHLine(10, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH,_CP_WHITE, _CP_BLUE_65);
				OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			    COsdShowPageText(_MENU_PICTURE);
				break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            OsdDispDisableOsd();
			OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
            break;

        default:
            break;                   
    }
}


void MenuOsdSettings(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_OSDSETTINGS_LANGUAGE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
		COsdShowChooseOSDSetText(_STRING_OSDSET_LANGUAGE);
	//	_STRING_OSDSET_LANGUAGE
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

	   // OsdWindowDrawingSelect(_OSD_WINDOW_9, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(15), HEIGHT(1), _CP_ORANGE);
		break;
			
        case _DOWN_KEY_MESSAGE:
       	
			SET_OSD_STATE(_MENU_SETUP);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			OsdDispMainMenuItemSelection(_MENU_SETUP-2, _OSD_UNSELECT);
			OsdDispMainMenuItemSelection(_MENU_SETUP-1, _OSD_SELECT);
			OsdFontPut1FuncHLine(10, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH,_CP_WHITE, _CP_BLUE_65);
			OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			COsdShowPageText(_MENU_SETUP);
			
				 break;
			
        case _UP_KEY_MESSAGE:
       
			SET_OSD_STATE(_MENU_COLOR);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			OsdDispMainMenuItemSelection(_MENU_OSDSETTINGS-1, _OSD_UNSELECT);
			OsdDispMainMenuItemSelection(_MENU_COLOR-1, _OSD_SELECT);
			OsdFontPut1FuncHLine(14, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH,_CP_WHITE, _CP_BLUE_65);
			OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			COsdShowPageText(_MENU_COLOR);
			
				 break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			OsdDispDisableOsd();
			OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
			break;

		default:
			break;
	}
}

void MenuSetup(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
        SET_OSD_STATE(_MENU_SETUP_INPUT);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);

		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowPageInputText();
		COsdShowChooseSetupText(_STRING_SETUP_INPUT);

		//COsdShowChooseSetupText(_STRING_SETUP_INPUT);
       //  OsdWindowDrawingSelect(_OSD_WINDOW_9, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(15), HEIGHT(1), _CP_ORANGE);
            break;
            
        case _DOWN_KEY_MESSAGE:
	
			 SET_OSD_STATE(_MENU_OTHER);
			
			 OsdDispMainMenuItemSelection(_MENU_OTHER-2, _OSD_UNSELECT);
			 OsdDispMainMenuItemSelection(_MENU_OTHER-1, _OSD_SELECT);
			 OsdFontPut1FuncHLine(14, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH,_CP_WHITE, _CP_BLUE_65);
			 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			 COsdShowPageText(_MENU_OTHER);
			 break;
			
        case _UP_KEY_MESSAGE:
        
			 SET_OSD_STATE(_MENU_OSDSETTINGS);
			 OsdDispMainMenuItemSelection(_MENU_SETUP-1, _OSD_UNSELECT);
			 OsdDispMainMenuItemSelection(_MENU_OSDSETTINGS-1, _OSD_SELECT);
			 OsdFontPut1FuncHLine(18, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH,_CP_WHITE, _CP_BLUE_65);
			 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			 COsdShowPageText(_MENU_OSDSETTINGS);
				 break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            OsdDispDisableOsd();
			OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
            break;

        default:
            break;
    }
}

void MenuOther(void)
{
    switch(GET_KEYMESSAGE())
    {

		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		   SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		   OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		   OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
	   	   COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		   OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

                //    OsdFuncChangeColor1Bit(ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_GRAY, _CP_BG);

		break;

          case _DOWN_KEY_MESSAGE:
		  {
			  SET_OSD_STATE(_MENU_PICTURE);

			  OsdDispMainMenuItemSelection(_MENU_OTHER - 1, _OSD_UNSELECT);
			  OsdDispMainMenuItemSelection(_MENU_PICTURE - 1, _OSD_SELECT);
			  OsdFontPut1FuncHLine(18, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
			  OsdFontPut1FuncHLine(22, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
			  OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			  OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			  COsdShowPageText(_MENU_PICTURE);
		  }
            break;

        case _UP_KEY_MESSAGE:
		{
			SET_OSD_STATE(_MENU_SETUP);
			OsdDispMainMenuItemSelection(_MENU_OTHER - 1, _OSD_UNSELECT);
			OsdDispMainMenuItemSelection(_MENU_SETUP - 1, _OSD_SELECT);
			OsdFontPut1FuncHLine(22, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
			OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			COsdShowPageText(_MENU_SETUP);
		}
           break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            OsdDispDisableOsd();	
			OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
            break;

        default:
            break;
    }
}

void MenuService(void)
{
	switch (GET_KEYMESSAGE())
	{

	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		COsdShowChooseServiceText(_STRING_SERVICE_PWM_RES);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

		break;

	case _DOWN_KEY_MESSAGE:
	{
		SET_OSD_STATE(_MENU_PICTURE);
		OsdFontPut2BitTable(ROW(_OSD_NUMBER_5_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_BIR_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_BLACK), COLOR2(_CP_YELLOW), COLOR3(_CP_WHITE));
		//OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(4), COL(7), _PFONT_PAGE_0, _STRING_PICTURE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(_OSD_NUMBER_6_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_COLORTEMP_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_GREEN_66), COLOR2(_CP_GREEN_119), COLOR3(_CP_RED));
		//OsdFontPut1FuncHLine(10, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(8), COL(7), _PFONT_PAGE_0, _STRING_COLOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(11), COL(2), tiOSD_MAIN_OSDSETTING_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLUE_65), COLOR3(_CP_LIGHTBLUE));
		//OsdFontPut1FuncHLine(14, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(12), COL(7), _PFONT_PAGE_0, _STRING_ADVANCE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(15), COL(2), tiOSD_MAIN_MISC_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_GREEN_66), COLOR3(_CP_BLUE_65));
		//OsdFontPut1FuncHLine(18, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(16), COL(7), _PFONT_PAGE_0, _STRING_SETUP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(19), COL(2), tiOSD_MAIN_RESET_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLACK), COLOR3(_CP_GREEN_66));
		//OsdFontPut1FuncHLine(22, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(20), COL(7), _PFONT_PAGE_0, _STRING_OTHER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		//OsdDispMainMenuItemSelection(_MENU_SERVICE - 1, _OSD_UNSELECT);
		OsdDispMainMenuItemSelection(_MENU_PICTURE - 1, _OSD_SELECT);

		OsdFontPut1FuncHLine(18, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdFontPut1FuncHLine(22, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		COsdShowPageText(_MENU_PICTURE);
	}
	break;

	case _UP_KEY_MESSAGE:
	{
		SET_OSD_STATE(_MENU_OTHER);
		OsdFontPut2BitTable(ROW(_OSD_NUMBER_5_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_BIR_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_BLACK), COLOR2(_CP_YELLOW), COLOR3(_CP_WHITE));
		//OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(4), COL(7), _PFONT_PAGE_0, _STRING_PICTURE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(_OSD_NUMBER_6_ROW), COL(_OSD_NUMBER_7_COL), tiOSD_MAIN_COLORTEMP_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_GREEN_66), COLOR2(_CP_GREEN_119), COLOR3(_CP_RED));
		//OsdFontPut1FuncHLine(10, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(8), COL(7), _PFONT_PAGE_0, _STRING_COLOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(11), COL(2), tiOSD_MAIN_OSDSETTING_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLUE_65), COLOR3(_CP_LIGHTBLUE));
		//OsdFontPut1FuncHLine(14, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(12), COL(7), _PFONT_PAGE_0, _STRING_ADVANCE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(15), COL(2), tiOSD_MAIN_MISC_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_GREEN_66), COLOR3(_CP_BLUE_65));
		//OsdFontPut1FuncHLine(18, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(16), COL(7), _PFONT_PAGE_0, _STRING_SETUP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdFontPut2BitTable(ROW(19), COL(2), tiOSD_MAIN_RESET_ICON, (_PALETTE_INDEX0 << 4) | COLOR0(_CP_BLUE_65), COLOR1(_CP_WHITE), COLOR2(_CP_BLACK), COLOR3(_CP_GREEN_66));
		//OsdFontPut1FuncHLine(22, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdPropPutString(ROW(20), COL(7), _PFONT_PAGE_0, _STRING_OTHER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

		OsdDispMainMenuItemSelection(_MENU_PICTURE - 1, _OSD_UNSELECT);
		OsdDispMainMenuItemSelection(_MENU_OTHER - 1, _OSD_SELECT);
		OsdFontPut1FuncHLine(14, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		COsdShowPageText(_MENU_OTHER);
	}
	break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispDisableOsd();
		OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
		break;

	default:
		break;
	}
}

void MenuPictureBacklight(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
#if (_ENABLE_MENU_OLED == _OFF)
		  g_usBackupValue = GET_OSD_BACKLIGHT();
			
		   SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT_ADJUST);
		 // OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BRIGHTNESS());
		 
		 OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_BACKLIGHT_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_BACKLIGHT_ADJUST,_SLIDER_0,_OFF,0);
#endif
			break;
			
        case _DOWN_KEY_MESSAGE:
  	
//			if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_RTS)
			{
//Eric_020180502 : Delete
    				SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
					//ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
    				//ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
    				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
    				//ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
    				//ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
    				//ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
    				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
    				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
    				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
    				COsdShowChoosePictureText(_STRING_BRIGHTNESS);
			}
//			else 
//			{
//			}

			
			break;

        case _UP_KEY_MESSAGE:
		{
#if (_ENABLE_MENU_OLED == _ON)
			SET_OSD_STATE(_MENU_PICTURE_OLED_SETTINGS);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChoosePictureText(_STRING_OLED_SETTINGS);
#else


			SET_OSD_STATE(_MENU_PICTURE_SATURATION);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChoosePictureText(_STRING_SATURATION);


#endif
		}
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_PICTURE);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			//ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			break;

		default:
			break;
	}
}

void MenuPictureBrightness(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = GET_OSD_BRIGHTNESS();
		SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS_ADJUST);
		// OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BRIGHTNESS());

		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_BRIGHTNESS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_BRIGHTNESS_ADJUST, _SLIDER_1, _OFF, 0);


		break;

	case _DOWN_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);		
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_CONTRAST);

	break;

	case _UP_KEY_MESSAGE:
	
		SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_BACKLIGHT);
	break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}
}

void MenuPictureContrast(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_CONTRAST();
		   SET_OSD_STATE(_MENU_PICTURE_CONTRAST_ADJUST);
		   OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_CONTRAST_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_PICTURE_CONTRAST_ADJUST,_SLIDER_2,_OFF,0);
		break;
			
        case _DOWN_KEY_MESSAGE:
        
	
//			if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_RTS)
			{
				SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65, _ARC_WINDOW_0);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChoosePictureText(_STRING_SHARPNESS);
			}
//			else 
//			{
//			}

			break;

        case _UP_KEY_MESSAGE:
         
//			if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_RTS)
			{
				SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				//ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
				//ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
				//ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				//ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChoosePictureText(_STRING_BRIGHTNESS);
			}
//			else 
//			{
//			}
	  //  OsdDispMainMenukeyCursor(_MENU_PICTURE_CONTRAST-_MENU_PICTURE_BACKLIGHT,1);
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_PICTURE);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			break;

		default:
			break;					 
	}
}

void MenuPictureSharpness(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = GET_OSD_SHARPNESS();
		SET_OSD_STATE(_MENU_PICTURE_SHARPNESS_ADJUST);
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_SHARPNESS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_SHARPNESS_ADJUST, _SLIDER_3, _OFF, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	
	{
		SET_OSD_STATE(_MENU_PICTURE_HUE);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_HUE);
	}
	break;

	case _UP_KEY_MESSAGE:
	
	{
		SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_CONTRAST);
	}
	break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}
}

void MenuPictureHue(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = GET_OSD_HUE();
		SET_OSD_STATE(_MENU_PICTURE_HUE_ADJUST);
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_HUE_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_HUE_ADJUST, _SLIDER_4, _OFF, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	
	{
		SET_OSD_STATE(_MENU_PICTURE_SATURATION);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_SATURATION);
	}
	break;

	case _UP_KEY_MESSAGE:
	
	{
		SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_SHARPNESS);
	}
	break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}
}

void MenuPictureSaturation(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = GET_OSD_SATURATION();
		SET_OSD_STATE(_MENU_PICTURE_SATURATION_ADJUST);
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_SATURATION_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_SATURATION_ADJUST, _SLIDER_4, _OFF, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	{
#if (_ENABLE_MENU_OLED == _ON)
		SET_OSD_STATE(_MENU_PICTURE_OLED_SETTINGS);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_OLED_SETTINGS);
#else
		SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_BACKLIGHT);

#endif
	}
	break;

	case _UP_KEY_MESSAGE:
	{
		SET_OSD_STATE(_MENU_PICTURE_HUE);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_HUE);
	}
	break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}
}
#if (_ENABLE_MENU_OLED == _ON)
void MenuPictureOLEDSettings(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		//g_usBackupValue = GET_OSD_ALCW();
		SET_OSD_STATE(_MENU_PICTURE_OLED_SETTINGS);
		//OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		COsdShowPageText(_MENU_PICTURE_OLED_SETTINGS);


		SET_OSD_STATE(_MENU_PICTURE_OLED_OFFRS);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);

		COsdShowChoosePictureText(_STRING_OLED_OFFRS);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_BACKLIGHT);
		break;

	case _UP_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_SATURATION);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_SATURATION);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}

}


void MenuPictureOLED_OffRs(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = _FALSE;
		SET_OSD_STATE(_MENU_PICTURE_OLED_OFFRS_ADJ);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_OLED_JB);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_OLED_JB);
		break;

	case _UP_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_OLED_JB);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_OLED_JB);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_OLED_SETTINGS);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		//OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		COsdShowPageText(_MENU_PICTURE);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_OLED_SETTINGS);
		break;

	default:
		break;
	}
}

void MenuPictureOLED_JB(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = _FALSE;
		SET_OSD_STATE(_MENU_PICTURE_OLED_JB_ADJ);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_OLED_OFFRS);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_OLED_OFFRS);
		break;

	case _UP_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_OLED_OFFRS);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_OLED_OFFRS);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_PICTURE_OLED_SETTINGS);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		//OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		COsdShowPageText(_MENU_PICTURE);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChoosePictureText(_STRING_OLED_SETTINGS);
		break;

	default:
		break;
	}
}
#endif

 void MenuColorTemperature(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		{
			g_usBackupValue = GET_COLOR_TEMP_TYPE();
			SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);

			//if (GET_COLOR_TEMP_TYPE() == _CT_6500)
			//{
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//}
			//else if (GET_COLOR_TEMP_TYPE() == _CT_9300)
			//{
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//}
			//else if (GET_COLOR_TEMP_TYPE() == _CT_USER)
			//{
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//}
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_COLOR_TEMP_TYPE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		}
     //      OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMPERATURE_ADJUST-_MENU_COLOR_TEMPERATURE_ADJUST,_MENU_COLOR_TEMPERATURE_ADJUST,_SLIDER_1,_OFF,1);
            break;
            
        case _DOWN_KEY_MESSAGE:      
	
			if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			{
				SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0); 		
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_RED);
				//OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_6,_ON,0);
			}
			else 
			{

#if (_HDR10_SUPPORT == _ON)
			SET_OSD_STATE(_MENU_COLOR_HDR);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseColorText(_STRING_HDR);
#else

				SET_OSD_STATE(_MENU_COLOR_ECO);

				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));

				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_EFFECT);


#endif 

			}
            break;

        case _UP_KEY_MESSAGE:     
#if (_HDR10_SUPPORT == _ON)
			SET_OSD_STATE(_MENU_COLOR_GAMMA);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseColorText(_STRING_GAMMA);
#else

			//if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			//{
			//	SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
			//	OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			//	OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0); 		
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(10), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//	COsdShowChooseColorText(_STRING_COLOR_BLUE);
			//}
			//else
			//{
			//	SET_OSD_STATE(_MENU_COLOR_ECO);

			//	OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));

			//	OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//	COsdShowChooseColorText(_STRING_COLOR_EFFECT);

			//}
			SET_OSD_STATE(_MENU_COLOR_GAMMA);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseColorText(_STRING_GAMMA);
#endif
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65, _ARC_WINDOW_0);
            break;

        default:
            break;                   
    }
}

void MenuColortempUserR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_R();
        SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_R);
		// OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_0,_OFF,0);
  //     OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_0,_OFF,0);
		OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_6,_OFF,0);

	  break;
            
        case _DOWN_KEY_MESSAGE:
        
			if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			{
				SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0); 		
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_GREEN);
				//OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_7,_ON,0);
			}
			else 
			{
			}
            break;
        case _UP_KEY_MESSAGE:
        
			if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			{
				SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65, _GRID_WINDOW_0);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLORTEMP);
			}
			else 
			{
			}
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
           SET_OSD_STATE(_MENU_COLOR);	   
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		   OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		   OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
         break;

        default:
            break;                   
    }
}

void MenuColortempUserG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_G();
       SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_G);
	   OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_7,_OFF,0);
  //     OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_1,_OFF,0);
        break;
            
        case _DOWN_KEY_MESSAGE:
        
			if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			{
				SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0); 		
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_BLUE);
				//OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_8,_ON,0);
			}
			else 
			{
			}
            break;
        case _UP_KEY_MESSAGE:
       
			if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			{
				SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0); 		
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_RED);
				//OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_0,_ON,0);
			}
			else 
			{
			}
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
           SET_OSD_STATE(_MENU_COLOR);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		   OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		   OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
            break;

        default:
            break;                   
    }
}

void MenuColortempUserB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_B();
       SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_B);
	   OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_8,_OFF,0);
    //   OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_2,_OFF,0);
            break;
            
        case _DOWN_KEY_MESSAGE:
        
#if (_HDR10_SUPPORT == _ON)
			
			SET_OSD_STATE(_MENU_COLOR_HDR);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);			
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65, _GRID_WINDOW_0);
			
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseColorText(_STRING_HDR);
#else
				SET_OSD_STATE(_MENU_COLOR_ECO);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_EFFECT);



#endif
			
            break;
        case _UP_KEY_MESSAGE:
        
			if(GET_COLOR_TEMP_TYPE()==_CT_USER)
			{
				SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0); 		
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_GREEN);
				//OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_7,_ON,0);
			}
			else 
			{
			
			}
           break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
           SET_OSD_STATE(_MENU_COLOR);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		   OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		   OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
           break;

        default:
            break;                   
    }
}
#if (_HDR10_SUPPORT == _ON)
 void MenuColorHDR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_HDR_MODE();
    		SET_OSD_STATE(_MENU_COLOR_HDR_ADJUST);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
			if(GET_OSD_HDR_MODE()==_HDR10_MODE_OFF)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if(GET_OSD_HDR_MODE()==_HDR10_MODE_AUTO)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if(GET_OSD_HDR_MODE()==_HDR10_MODE_FORCE_2084)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}            

	
               break;
            
        case _DOWN_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_COLOR_ECO);

			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseColorText(_STRING_COLOR_EFFECT);

            break;

        case _UP_KEY_MESSAGE:
			if (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF)
			{
				SET_OSD_STATE(_MENU_COLOR_ECO);

				OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));

				OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				COsdShowChooseColorText(_STRING_COLOR_EFFECT);
			}
			else
			{
				if (GET_COLOR_TEMP_TYPE() == _CT_USER)
				{
					SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
					OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
					OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
					ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
					OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
					COsdShowChooseColorText(_STRING_COLOR_BLUE);
					//OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_8,_ON,0);
				}
				else
				{
					SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);

					OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));

					OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
					ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
					OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
					COsdShowChooseColorText(_STRING_COLORTEMP);

				}
			}
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65, _ARC_WINDOW_0);
            break;

        default:
            break;                   
    }
}
#endif
 void MenuColorECO(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_COLOR_EFFECT();
		 //Eric_020180308 : delete
		     SET_OSD_STATE(_MENU_COLOR_ECO_ADJUST);
		     OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
		     OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
		     OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
		     OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
		     OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
		     OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
		     //OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
		     
		     
			 switch (GET_OSD_COLOR_EFFECT())
			 {
			 case _COLOREFFECT_STANDARD:
				 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				 break;
			 case _COLOREFFECT_GAME:
				 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				 break;
			 case _COLOREFFECT_MOVIE:
				 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

				 break;
			 case _COLOREFFECT_PHOTO:
				 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

				 break;
			 case _COLOREFFECT_VIVID:
				 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				 break;
			 //case _COLOREFFECT_USER:
				// ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				// OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				// break;
				 //Eric_020180307 : Delete
				 //    			   case _COLOREFFECT_FPS:
				 //    				   ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 //    				   OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				 //    				   
				 //    				   break;
				 //    			   case _COLOREFFECT_RTS:
				 //    					ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 //    					OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				 //    				   break;
			 default:
				 break;
			 }
			 break;
	 case _DOWN_KEY_MESSAGE:
#if (_HDR10_SUPPORT == _ON)
		 if (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF)
		 {
			 SET_OSD_STATE(_MENU_COLOR_HDR);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseColorText(_STRING_HDR);
		 }
		 else
		 {
			 SET_OSD_STATE(_MENU_COLOR_GAMMA);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseColorText(_STRING_GAMMA);

		 }
#else
		 SET_OSD_STATE(_MENU_COLOR_GAMMA);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseColorText(_STRING_GAMMA);

#endif
	 break;

	 case _UP_KEY_MESSAGE:
#if (_HDR10_SUPPORT == _ON)
		 SET_OSD_STATE(_MENU_COLOR_HDR);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseColorText(_STRING_HDR);
#else

		 if (GET_COLOR_TEMP_TYPE() == _CT_USER)
		 {
			 SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseColorText(_STRING_COLOR_BLUE);
		 }
		 else
		 {
			 SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);

			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 //ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			 //ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			 //ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseColorText(_STRING_COLORTEMP);

		 }
#endif
	 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_COLOR);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
//#if (_HDR10_SUPPORT == _ON)
//		 //OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_EFFECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
//#else
//		 //OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_COLOR_EFFECT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
//#endif
		 break;

	 default:
		 break;
	 }
 }

 void MenuColorGamma(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_GAMMA();
		 //Eric_020180308 : delete
		 SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJUST);
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 //OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);	
#if(_TECNINT_DICOM)
		 OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
#endif
		 switch (GET_OSD_GAMMA())
		 {
		 case _GAMMA_OFF:
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 break;
		 case _GAMMA_18:
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 break;
		 case _GAMMA_20:
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

			 break;
		 case _GAMMA_22:
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

			 break;
		 case _GAMMA_24:
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 break;
#if(_TECNINT_DICOM)
		 case _GAMMA_RC2:
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 break;
		 case _GAMMA_RC3:
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 break;
#endif
		 default:
			 break;
		 }
		 break;

		 break;
	 case _DOWN_KEY_MESSAGE:
		 {
			 SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseColorText(_STRING_COLORTEMP);
		 }
		 break;

	 case _UP_KEY_MESSAGE:
#if (_HDR10_SUPPORT == _ON)
		 SET_OSD_STATE(_MENU_COLOR_ECO);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseColorText(_STRING_COLOR_EFFECT);
#else

		 SET_OSD_STATE(_MENU_COLOR_ECO);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseColorText(_STRING_COLOR_EFFECT);
#endif

		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_COLOR);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_7);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
//#if (_HDR10_SUPPORT == _ON)
//		 //OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_GAMMA, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
//#else
//		 //OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_GAMMA, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_7, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
//#endif
		 break;

	 default:
		 break;
	 }
 }


void MenuOsdSettingsLanguage(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_LANGUAGE();
			SET_OSD_STATE(_MENU_OSDSETTINGS_LANGUAGE_ADJUST);
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
				//	OsdFontPut1ChooseIcon(_OSD_NUMBER_1_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if(GET_OSD_LANGUAGE()==_CHINESE_T)
			{
				//OsdFontPut1ChooseIcon(_OSD_NUMBER_13_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if (GET_OSD_LANGUAGE() == _ESPANA)
			{
				//	OsdFontPut1ChooseIcon(_OSD_NUMBER_2_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if (GET_OSD_LANGUAGE() == _FRENCH)
			{
				//	OsdFontPut1ChooseIcon(_OSD_NUMBER_3_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if (GET_OSD_LANGUAGE() == _GERMAN)
			{
				//	OsdFontPut1ChooseIcon(_OSD_NUMBER_4_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if (GET_OSD_LANGUAGE() == _ITALIANO)
			{
				//	OsdFontPut1ChooseIcon(_OSD_NUMBER_11_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if (GET_OSD_LANGUAGE() == _RUSSIAN)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			//else if(GET_OSD_LANGUAGE()==_KOREAN)
			//{
			////	OsdFontPut1ChooseIcon(_OSD_NUMBER_12_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//}
		 //OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_3, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_SLIDE_VALUE_OFFSET+2), HEIGHT(2), _CP_GRAY_1, _CP_ORANGE_H, _CP_BG);
#else
			if(GET_OSD_LANGUAGE()==_ENGLISH)
			{
			//	OsdFontPut1ChooseIcon(_OSD_NUMBER_1_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if(GET_OSD_LANGUAGE()==_ESPANA)
			{
			//	OsdFontPut1ChooseIcon(_OSD_NUMBER_2_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if(GET_OSD_LANGUAGE()==_FRENCH)
			{
			//	OsdFontPut1ChooseIcon(_OSD_NUMBER_3_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if(GET_OSD_LANGUAGE()==_GERMAN)
			{
			//	OsdFontPut1ChooseIcon(_OSD_NUMBER_4_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if(GET_OSD_LANGUAGE()==_ITALIANO)
			{
			//	OsdFontPut1ChooseIcon(_OSD_NUMBER_11_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if (GET_OSD_LANGUAGE() == _NEDERLAND)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else if (GET_OSD_LANGUAGE() == _RUSSIAN)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			//else if(GET_OSD_LANGUAGE()==_KOREAN)
			//{
			////	OsdFontPut1ChooseIcon(_OSD_NUMBER_12_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//}
			//else if(GET_OSD_LANGUAGE()==_CHINESE_T)
			//{
			////	OsdFontPut1ChooseIcon(_OSD_NUMBER_13_ROW, _OSD_NUMBER_2_COL+10, _CHOOSE_ICON,_CP_RED, _CP_BLUE_65);
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//}
		 //OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_3, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_SLIDE_VALUE_OFFSET+2), HEIGHT(2), _CP_GRAY_1, _CP_ORANGE_H, _CP_BG);
#endif
			break;
			
        case _DOWN_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_HPOS);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOSDSetText(_STRING_OSDSET_HORIZONTAL);
			break;
        case _UP_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_ROTATE);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOSDSetText(_STRING_OSDSET_ROTATE);
			break;


		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_OSDSETTINGS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
		//OsdDispMainMenukeyCursor(_MENU_OTHER_LANGUAGE-_MENU_OTHER_LANGUAGE,1);
			break;

		default:
			break;					 
	}
}



void MenuOsdSettingsHPos(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_HPOS();
			SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_HPOS_ADJUST);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_HPOS_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_OSD_HPOS_ADJUST,_SLIDER_2,_OFF,0);
			
		break;
			
        case _DOWN_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_VPOS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	//	  OsdDispMainMenukeyCursor(_MENU_OTHER_OSD_HPOS-_MENU_OTHER_LANGUAGE,1);
			COsdShowChooseOSDSetText(_STRING_OSDSET_VERTICAL);
			break;

        case _UP_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_LANGUAGE);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOSDSetText(_STRING_OSDSET_LANGUAGE);
	 //   OsdDispMainMenukeyCursor(_MENU_OTHER_OSD_HPOS-_MENU_OTHER_LANGUAGE,1);
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_OSDSETTINGS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
  //	  OsdDispMainMenukeyCursor(_MENU_OTHER_OSD_HPOS-_MENU_OTHER_LANGUAGE,1);
			break;

		default:
			break;					 
	}
}


void MenuOsdSettingsVPos(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_VPOS();
			SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_VPOS_ADJUST);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_VPOS_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_OSD_VPOS_ADJUST,_SLIDER_3,_OFF,0);
			break;
			
        case _DOWN_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_TRNASPARENCY);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		  OsdDispMainMenukeyCursor(_MENU_OTHER_OSD_VPOS-_MENU_OTHER_LANGUAGE,1);
			COsdShowChooseOSDSetText(_STRING_OSDSET_TRANSPARENCY);
			break;

        case _UP_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_HPOS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
   //	  OsdDispMainMenukeyCursor(_MENU_OTHER_OSD_VPOS-_MENU_OTHER_LANGUAGE,1);
			COsdShowChooseOSDSetText(_STRING_OSDSET_HORIZONTAL);
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_OSDSETTINGS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//		  OsdDispMainMenukeyCursor(_MENU_OTHER_OSD_VPOS-_MENU_OTHER_LANGUAGE,1);
			break;

		default:
			break;					 
	}
}

void MenuOsdSettingsTransparency(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_TRANSPARENCY_STATUS();
			SET_OSD_STATE(_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST,_SLIDER_4,_OFF,0);
		break;
			
        case _DOWN_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_MENU_TIME);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_11_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
  //	  OsdDispMainMenukeyCursor(_MENU_OTHER_TRNASPARENCY-_MENU_OTHER_LANGUAGE,1);
			COsdShowChooseOSDSetText(_STRING_OSDSET_OSDTIMEOUT);
			break;

        case _UP_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_VPOS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	//	  OsdDispMainMenukeyCursor(_MENU_OTHER_TRNASPARENCY-_MENU_OTHER_LANGUAGE,1);
			COsdShowChooseOSDSetText(_STRING_OSDSET_VERTICAL);
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_OSDSETTINGS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
	 //   OsdDispMainMenukeyCursor(_MENU_OTHER_TRNASPARENCY-_MENU_OTHER_LANGUAGE,1);
			break;

		default:
			break;					 
	}
}

void MenuOsdSettingsMenuTime(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_TIME_OUT();
			SET_OSD_STATE(_MENU_OSDSETTINGS_MENU_TIME_ADJUST);
				g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_TIME_OUT(), _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
				OsdWindowSlider(ROW(_OSD_NUMBER_10_ROW), COL(_OSD_NUMBER_10_COL),g_usAdjustValue, _SLIDER_5, _SELECT);
				OsdPropShowNumber(ROW(_OSD_NUMBER_10_ROW-2), COL(_OSD_NUMBER_10_COL+_OSD_SLIDE_VALUE_OFFSET), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF| _SHOW_3), _SLIDER_5+3, _OSD_NUMBER_SELECT_COLOR); 
//			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_MENU_TIME_ADJUST-_MENU_PICTURE_BRIGHTNESS_ADJUST,_MENU_OSDSETTINGS_MENU_TIME_ADJUST,_SLIDER_5,_OFF,0);
			break;
			
        case _DOWN_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_ROTATE);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOSDSetText(_STRING_OSDSET_ROTATE);
			break;

        case _UP_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_OSDSETTINGS_TRNASPARENCY);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOSDSetText(_STRING_OSDSET_TRANSPARENCY);
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_OSDSETTINGS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
	//	  OsdDispMainMenukeyCursor(_MENU_OTHER_MENU_TIME-_MENU_OTHER_LANGUAGE,1);
			break;

		default:
			break;					 
	}
}

void MenuOsdSettingsRotate(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		g_usBackupValue = GET_OSD_ROTATE_STATUS();
		SET_OSD_STATE(_MENU_OSDSETTINGS_ROTATE_ADJUST);
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ROTATE_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:

		SET_OSD_STATE(_MENU_OSDSETTINGS_LANGUAGE);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseOSDSetText(_STRING_OSDSET_LANGUAGE);
		break;

	case _UP_KEY_MESSAGE:

		SET_OSD_STATE(_MENU_OSDSETTINGS_MENU_TIME);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		//	  OsdDispMainMenukeyCursor(_MENU_OTHER_TRNASPARENCY-_MENU_OTHER_LANGUAGE,1);
		COsdShowChooseOSDSetText(_STRING_OSDSET_OSDTIMEOUT);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_OSDSETTINGS);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		//OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OSDSET_ROTATE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		break;

	default:
		break;
	}
}


void MenuSetupInput(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		{
			//Eric_020180308 : Delete
			SET_OSD_STATE(_MENU_INPUT_ADJUST);
			OsdFuncSetOsdItemFlag();
			g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
			if (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO)
			{
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_INPUT_PORT_OSD_ITEM())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			else // // EnumSourceSearchPort 과 EnumOSDInputPortDef 값이 같게 합니다.
			{
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * (GET_OSD_INPUT_PORT_OSD_ITEM()))), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			}
			//g_usBackupValue = SysSourceGetInputPort();
		}
		break;

        case _DOWN_KEY_MESSAGE:
        
#if(_AUDIO_SUPPORT == _ON)
			 SET_OSD_STATE(_MENU_SETUP_AUDIOMUTE);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseSetupText(_STRING_SETUP_AUDIOMUTE);

			
#else
			SET_OSD_STATE(_MENU_SETUP_RESET);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

#endif
			 break;
        case _UP_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_SETUP_RESET);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SETUP);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
           // OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

//MenuSetupAudioMute  MenuSetupAudio
void MenuSetupAudioMute(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_AUDIO_AUDIOMUTE_ON_OFF);
			  OsdFuncSetOsdItemFlag();
			  g_usBackupValue = GET_OSD_VOLUME_MUTE();
			  OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			  OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			  OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*g_usBackupValue)),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);



			break;
			
        case _DOWN_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_SETUP_AUDIO);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseSetupText(_STRING_SETUP_AUDIO);
			break;

        case _UP_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_SETUP_INPUT);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowPageInputText();
			COsdShowChooseSetupText(_STRING_SETUP_INPUT);
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_SETUP);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			break;

		default:
			break;					 
	}
}

void MenuSetupAudio(void)
{
	switch(GET_KEYMESSAGE())
	{
		case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_VOLUME();
			SET_OSD_STATE(_MENU_AUDIO_ADJUST);
			OsdDispMainMenukeySlideAndOption(_MENU_AUDIO_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_AUDIO_ADJUST, _SLIDER_3,_OFF,0);
			
		break;
			
        case _DOWN_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_SETUP_RESET);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

        case _UP_KEY_MESSAGE:
        
			SET_OSD_STATE(_MENU_SETUP_AUDIOMUTE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);			
			COsdShowChooseSetupText(_STRING_SETUP_AUDIOMUTE);
			break;

		case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_SETUP); 
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);			
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			break;

		default:
			break;					 
	}
}

void MenuSetupDPFormat(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP_DP_FORMAT_ADJ);
		g_usBackupValue = GET_OSD_DP_D0_VERSION();
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
		if (GET_OSD_CLONE_MODE() == _OSD_CLONE_OFF)
		{
			SET_OSD_STATE(_MENU_SETUP_DP_MST);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseSetupText(_STRING_DP_MST);
		}
		else
		{
			SET_OSD_STATE(_MENU_SETUP_CLONE_MODE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseSetupText(_STRING_CLONE);
		}
		break;

	case _UP_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP_AUDIO);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseSetupText(_STRING_SETUP_AUDIO);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}
}
void MenuSetupDPMST(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		if (GET_OSD_INPUT_PORT_OSD_ITEM() != _OSD_INPUT_AUTO)
		{
			SET_OSD_STATE(_MENU_SETUP_DP_MST_ADJ);
			g_usBackupValue = GET_OSD_DP_MST();
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		}
		else
		{
			OsdDispOsdMessage(_OSD_DISP_MST_WARNING_MSG);
			SET_OSD_STATE(_MENU_NONE);
			ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);

		}
		break;

	case _DOWN_KEY_MESSAGE:
		if ((GET_OSD_DP_MST() == _MST_OFF))
		{
			SET_OSD_STATE(_MENU_SETUP_CLONE_MODE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseSetupText(_STRING_CLONE);
		}
		else
		{
			SET_OSD_STATE(_MENU_SETUP_RESET);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		}
		break;

	case _UP_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP_DP_FORMAT);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseSetupText(_STRING_DP_FORMAT);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}
}
void MenuSetupCloneMode(void) 
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP_CLONE_MODE_ADJ);
		g_usBackupValue = GET_OSD_CLONE_MODE();
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP_RESET);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _UP_KEY_MESSAGE:
		if (GET_OSD_CLONE_MODE() == _OSD_CLONE_OFF)
		{
			SET_OSD_STATE(_MENU_SETUP_DP_MST);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseSetupText(_STRING_DP_MST);
		}
		else
		{
			SET_OSD_STATE(_MENU_SETUP_DP_FORMAT);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseSetupText(_STRING_DP_FORMAT);
		}
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SETUP);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		break;

	default:
		break;
	}
}

void MenuSetupReset(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
            OsdDispOsdReset(); 
            break;
            
        case _DOWN_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_SETUP_INPUT);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowPageInputText();
			COsdShowChooseSetupText(_STRING_SETUP_INPUT);
			break;
        case _UP_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_SETUP_AUDIO);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseSetupText(_STRING_SETUP_AUDIO);
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SETUP);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
            break;

        default:
            break;                   
    }
}



 void MenuOthersDisplaySize(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_ASPECT_RATIO_TYPE();
            SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE_ADJUST);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_ASPECT_RATIO_TYPE())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);			
			break;
            
        case _DOWN_KEY_MESSAGE:  
			SET_OSD_STATE(_MENU_OTHERS_DISPLAY_ROTATE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_ROTATE);
			break;

        case _UP_KEY_MESSAGE:
#if(_AUO_PANEL_ALCW_SUPPORT == _ON)
			SET_OSD_STATE(_MENU_OTHERS_ALCW);
			OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowChooseOtherText(_STRING_OTHER_MENU);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);
#elif(_ENABLE_SELF_CHECK == _ON)
			SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
#elif (_ENABLE_FAN_CONTROL == _ON)
			SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
#elif (_ENABLE_LIGHT_SENSOR == _ON)
			SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
#elif(_ENABLE_VIDEO_WALL == _ON)
			SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
#else
//			SET_OSD_STATE(_MENU_OTHERS_OD);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
#endif
           break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);			
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			//OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_DISPLAY_SIZE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());	 

			//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
			
			//      OsdDispMainMenukeyCursor(_MENU_ADVANCE_ASPECT-_MENU_ADVANCE_ULTRA_VIVID,1);
            break;

        default:
            break;                   
    }
}

 void MenuOthersDisplayRotate(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_DISP_ROTATE();
		 SET_OSD_STATE(_MENU_OTHERS_DISPLAY_ROTATE_ADJUST);
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_DISP_ROTATE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;

	 case _DOWN_KEY_MESSAGE:

//		 SET_OSD_STATE(_MENU_OTHERS_OD);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
		 break;

	 case _UP_KEY_MESSAGE:

		 SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHER);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 //OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_DISPLAY_ROTATE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		 //OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		 break;

	 default:
		 break;
	 }
 }

#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON) 

  void MenuOthersLowBlueLight(void)
{
 
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_LOWBLUELIGHT_STATUS();
            SET_OSD_STATE(_MENU_OTHERS_LOW_BLUE_LIGHT_ADJUST);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_LOWBLUELIGHT_STATUS())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
        break;
            
        case _DOWN_KEY_MESSAGE:
        
            SET_OSD_STATE(_MENU_OTHERS_OD);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	   		COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
            break;

        case _UP_KEY_MESSAGE:
        
            SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	   		COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_LOW_BLUE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());	 
            break;

        default:
            break;                   
    }
}   


#endif

#if(_OD_SUPPORT == _ON) 

 void MenuOthersOverDrive(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
			g_usBackupValue = GET_OSD_OD_STATUS();
            SET_OSD_STATE(_MENU_OTHERS_OD_ADJUST);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_OD_STATUS())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
             break;
            
        case _DOWN_KEY_MESSAGE:
#if (_ENABLE_VIDEO_WALL == _ON)
			SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
#elif (_ENABLE_LIGHT_SENSOR == _ON)
			SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
#elif (_ENABLE_FAN_CONTROL == _ON)
			SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
#elif(_ENABLE_SELF_CHECK == _ON)
			SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
#elif (_AUO_PANEL_ALCW_SUPPORT == _ON)
			SET_OSD_STATE(_MENU_OTHERS_ALCW);
			OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowChooseOtherText(_STRING_OTHER_MENU);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);
#else
            SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	   		COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
#endif 

             break;

        case _UP_KEY_MESSAGE:
        
#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)

			SET_OSD_STATE(_MENU_OTHERS_LOW_BLUE_LIGHT);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	   		COsdShowChooseOtherText(_STRING_OTHER_LOW_BLUE);
#else
            SET_OSD_STATE(_MENU_OTHERS_DISPLAY_ROTATE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	   		COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_ROTATE);
#endif

            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			//OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_OVER_DRIVE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());	 
			//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
            break;

        default:
            break;                   
    }
}

#endif

#if (_ENABLE_VIDEO_WALL == _ON)
 void MenuOthersVideoWallSettings(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 //g_usBackupValue = GET_OSD_ALCW();
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 COsdShowPageText(_MENU_OTHERS_VIDEO_WALL_SETTINGS);

		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;

	 case _DOWN_KEY_MESSAGE:
#if (_ENABLE_LIGHT_SENSOR == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
#elif (_ENABLE_FAN_CONTROL == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
#elif(_ENABLE_SELF_CHECK == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
#elif(_AUO_PANEL_ALCW_SUPPORT == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_ALCW);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowChooseOtherText(_STRING_OTHER_MENU);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);
#else
		 SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
#endif
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_OD);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHER);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 //OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_VIDEO_WALL_SETTINGS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		 break;

	 default:
		 break;
	 }
 }

 void MenuOthersVideoWall(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_VIDEO_WALL_STATUS();
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_ADJ);
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_VIDEO_WALL_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_DISP_NUM);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_NUMBER);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_RS232ID);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_RS232_ID);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
		 break;

	 default:
		 break;
	 }
 }

 void MenuOthersVideoWall_DispNum(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_VIDEO_WALL_DISP_NUM();
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_HNUM);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_HORIZONTAL_NUMBER);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
		 break;

	 default:
		 break;
	 }
 }

 void MenuOthersVideoWall_HNum(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_VIDEO_WALL_H_NUM();
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_HNUM_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_HNUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_HNUM_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_VNUM);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VERTICAL_NUMBER);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_DISP_NUM);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_NUMBER);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
		 break;

	 default:
		 break;
	 }
 }

 void MenuOthersVideoWall_VNum(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_VIDEO_WALL_V_NUM();
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_VNUM_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_VNUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_VNUM_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_RS232ID);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_RS232_ID);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_HNUM);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_HORIZONTAL_NUMBER);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
		 break;

	 default:
		 break;
	 }
 }

 void MenuOthersVideoWall_RS232Id(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_VIDEO_WALL_RS232ID();
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_VNUM);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VERTICAL_NUMBER);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);	 
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
		 break;

	 default:
		 break;
	 }
 }
#endif

#if (_ENABLE_LIGHT_SENSOR == _ON)
 void MenuOthersLightSensor(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 if (SuccessInitilizeLightSensor())
		 {
			 g_usBackupValue = GET_OSD_LIGHT_SENSOR_STATUS();
			 SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR_ADJ);
			 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_LIGHT_SENSOR_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 }
		 break;

	 case _DOWN_KEY_MESSAGE:
#if (_ENABLE_FAN_CONTROL == _ON)
		SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
#elif(_ENABLE_SELF_CHECK == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
#elif(_AUO_PANEL_ALCW_SUPPORT == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_ALCW);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowChooseOtherText(_STRING_OTHER_MENU);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);
#else
		 SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
#endif
		 break;

	 case _UP_KEY_MESSAGE:
#if (_ENABLE_VIDEO_WALL == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
#else
		 SET_OSD_STATE(_MENU_OTHERS_OD);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
#endif

		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHER);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 //OsdPropPutString(ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_LIGHT_SENSOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		 //if(SuccessInitilizeLightSensor())
			//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		 //else
			//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		 
		 break;

	 default:
		 break;
	 }
 }
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
 void MenuOthersFanControls(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 if (SuccessInitializeFanControl())
		 {
			 //g_usBackupValue = GET_OSD_ALCW();
			 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
			 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
			 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 COsdShowPageText(_MENU_OTHERS_FAN_CONTROLS);

			 SET_OSD_STATE(_MENU_OTHERS_FAN);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 COsdShowChooseOtherText(_STRING_OTHER_FAN);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 }
		 break;

	 case _DOWN_KEY_MESSAGE:
#if (_ENABLE_SELF_CHECK == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);

#elif (_AUO_PANEL_ALCW_SUPPORT == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_ALCW);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowChooseOtherText(_STRING_OTHER_MENU);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);

#else
		 SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
#endif
		 break;

	 case _UP_KEY_MESSAGE:
#if (_ENABLE_LIGHT_SENSOR == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
#elif (_ENABLE_VIDEO_WALL == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
#else
		 SET_OSD_STATE(_MENU_OTHERS_OD);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
#endif
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHER);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 //OsdPropPutString(ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FAN_CONTROLS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		 //if (SuccessInitialize_ADT7470())
			// OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		 //else
			// OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		 break;

	 default:
		 break;
	 }
 }

 void MenuOthersFan(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_FAN_STATUS();
		 SET_OSD_STATE(_MENU_OTHERS_FAN_ADJ);
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_FAN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 if (GET_OSD_FAN_STATUS() == _ON)
		 {
			 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM1);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM1);
		 }
		 else
		 {
			 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN);
		 }
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_TEMP);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS2);
		 COsdShowChooseOtherText(_STRING_OTHER_TEMP);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;

	 default:
		 break;
	 }
 }

 void MenuOthersFanPWM1(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_FAN_PWM1();
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM1_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM1_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM1_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM2);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM2);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;
	 default:
		 break;
	 }
 }

 void MenuOthersFanPWM2(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_FAN_PWM2();
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM2_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM2_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM2_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM3);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM3);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM1);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM1);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;
	 default:
		 break;
	 }
 }

 void MenuOthersFanPWM3(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_FAN_PWM3();
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM3_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM3_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM3_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM4);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM4);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM2);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM2);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;
	 default:
		 break;
	 }
 }

 void MenuOthersFanPWM4(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_FAN_PWM4();
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM4_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM4_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM4_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);

		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM3);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM3);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;
	 default:
		 break;
	 }
 }

 void MenuOthersShutDown(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_SHUTDOWN_STATUS();
		 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN_ADJ);
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SHUTDOWN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 if (GET_OSD_SHUTDOWN_STATUS() == _ON)
		 {
			 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN_TEMP);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN_TEMP);
		 }
		 else
		 {
			 SET_OSD_STATE(_MENU_OTHERS_TEMP);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);

			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS2);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_TEMP);
		 }
		 break;

	 case _UP_KEY_MESSAGE:
		 if (GET_OSD_FAN_STATUS() == _ON)
		 {
			 SET_OSD_STATE(_MENU_OTHERS_FAN_PWM4);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_FAN_PWM4);
		 }
		 else
		 {
			 SET_OSD_STATE(_MENU_OTHERS_FAN);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_FAN);
		 }
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;
	 default:
		 break;
	 }
 }

 void MenuOthersShutDownTemp(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_SHUTDOWN_TEMP();
		 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN_TEMP_ADJ);
		 OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_SHUTDOWN_TEMP_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_SHUTDOWN_TEMP_ADJ, _SLIDER_0, _OFF, 0);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_TEMP);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS2);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_TEMP);
		 break;

	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;
	 default:
		 break;
	 }
 }

 void MenuOthersTemperature(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN);
		 
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);

		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowPageText(_MENU_OTHERS_FAN_CONTROLS);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);	 
		 COsdShowChooseOtherText(_STRING_OTHER_FAN);
		 break;

	 case _UP_KEY_MESSAGE:
		 if (GET_OSD_SHUTDOWN_STATUS() == _ON)
		 {
			 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN_TEMP);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
			 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 COsdShowPageText(_MENU_OTHERS_FAN_CONTROLS);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN_TEMP);
		 }
		 else
		 {
			 SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN);	 
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
			 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 COsdShowPageText(_MENU_OTHERS_FAN_CONTROLS);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN);
		 }
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFontPut1FuncHLine(6, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
		 break;
	 default:
		 break;
	 }
 }
#endif

#if (_ENABLE_SELF_CHECK == _ON)
 void MenuOthersSelfCheck(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 if (SuccessInitialize_TCS34725())
		 {
			 g_usBackupValue = GET_OSD_SELF_CHECK_STATUS();
			 SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK_ADJ);
			 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SELF_CHECK_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 }
		 break;

	 case _DOWN_KEY_MESSAGE:
#if(_AUO_PANEL_ALCW_SUPPORT == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_ALCW);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowChooseOtherText(_STRING_OTHER_MENU);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);
#else
		 SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
#endif
		 break;

	 case _UP_KEY_MESSAGE:
#if (_ENABLE_FAN_CONTROL == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0); 
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
#elif (_ENABLE_LIGHT_SENSOR == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
#elif(_ENABLE_VIDEO_WALL == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
#else
		 SET_OSD_STATE(_MENU_OTHERS_OD);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
#endif

		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHER);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 //OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_SELF_CHECK, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		 //if (SuccessInitialize_TCS34725())
			// OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		 //else
			// OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		 break;

	 default:
		 break;
	 }
 }
#endif

#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
 void MenuOthersALCW(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 g_usBackupValue = GET_OSD_ALCW();
		 SET_OSD_STATE(_MENU_OTHERS_ALCW_ADJ);
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ALCW())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;

	 case _DOWN_KEY_MESSAGE:
//#if(_ENABLE_SELF_CHECK == _ON)
//		 SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
//		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
//		 COsdShowPageText(_MENU_OTHER);
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		 COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
//#else
		 SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
//#endif
		 break;

	 case _UP_KEY_MESSAGE:
#if(_ENABLE_SELF_CHECK == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
#elif (_ENABLE_FAN_CONTROL == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_FAN_CONTROLS);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_FAN_CONTROLS);
#elif (_ENABLE_LIGHT_SENSOR == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
#elif(_ENABLE_VIDEO_WALL == _ON)
		 SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_SETTINGS);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL_SETTINGS);
#else
		 SET_OSD_STATE(_MENU_OTHERS_OD);
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowPageText(_MENU_OTHER);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
#endif

		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_OTHER);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 //OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_ALCW_SETTING, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
		 COsdShowPageText(_MENU_OTHER);
		 break;

	 default:
		 break;
	 }
 }
#endif

 void MenuOthersFreeSync(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHERS_FREE_SYNC_ADJUST);
			OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);  
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_FREE_SYNC_STATUS())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
             break;
            
        case _DOWN_KEY_MESSAGE:       

            SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	   		COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
             break;

        case _UP_KEY_MESSAGE:

//			SET_OSD_STATE(_MENU_OTHERS_OD);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_GRID_WINDOW_0);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
	   		COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
         			//OsdDispMainMenukeyCursor(_MENU_ADVANCE_OD-_MENU_ADVANCE_ULTRA_VIVID,1);
            break;

        case _MENU_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE,13 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_1, _STRING_OTHER_FREESYNC, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
     //    OsdDispMainMenukeyCursor(_MENU_ADVANCE_OD-_MENU_ADVANCE_ULTRA_VIVID,1);
            break;

        default:
            break;                   
    }
}

void MenuServiceBacklightPwmRes(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES_ADJ);
		 g_usBackupValue = GET_OSD_BACKLIGHT_PWM_RES();
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;

	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_CONTROL);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseServiceText(_STRING_SERVICE_CONTROL);
		 break;
#if(_PIXEL_SHIFT_SUPPORT == _ON)
	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT_TIME);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT_TIME);
		 break;
#else
	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_CONTROL);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseServiceText(_STRING_SERVICE_CONTROL);
		 break;
#endif
	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 break;

	 default:
		 break;
	 }
 }

void MenuServiceBacklightControl(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_CONTROL_ADJ);
		 g_usBackupValue = GET_OSD_BACKLIGHT_CONTROL();
		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 break;
#if(_PIXEL_SHIFT_SUPPORT == _ON)
	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT);
		 break;
#else
	 case _DOWN_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseServiceText(_STRING_SERVICE_PWM_RES);
		 break;
#endif
	 case _UP_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 COsdShowChooseServiceText(_STRING_SERVICE_PWM_RES);
		 break;

	 case _MENU_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_MENU_SERVICE);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		 break;

	 default:
		 break;
	 }
 }
#if(_PIXEL_SHIFT_SUPPORT == _ON)
void MenuServicePixelShift(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT_ADJ);
		g_usBackupValue = GET_OSD_PIXEL_SHIFT_STATUS();
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT_TIME);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT_TIME);
		break;

	case _UP_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_CONTROL);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseServiceText(_STRING_SERVICE_CONTROL);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		break;

	default:
		break;
	}
}

void MenuServicePixelShiftTime(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT_TIME_ADJ);
		g_usBackupValue = GET_OSD_PIXEL_SHIFT_TIME();
		OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseServiceText(_STRING_SERVICE_PWM_RES);
		break;

	case _UP_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT);
		break;

	case _MENU_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_STATE(_MENU_SERVICE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
		OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
		break;

	default:
		break;
	}
}
#endif

//void MenuServiceBacklightInvert(void)
// {
//	 switch (GET_KEYMESSAGE())
//	 {
//	 case _SELECT_KEY_MESSAGE:
//	 case _RIGHT_KEY_MESSAGE:
//		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT_ADJ);
//		 g_usBackupValue = GET_OSD_BACKLIGHT_INVERT();
//		 OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
//		 OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_11_COL), _PFONT_PAGE_2, _ICON_CHOOSE, COLOR(_CP_BLUE_65, _CP_BG), _CHINESE_T);
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		 break;
//
//	 case _DOWN_KEY_MESSAGE:
//		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
//		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		 COsdShowChooseServiceText(_STRING_SERVICE_FREQ);
//		 break;
//
//	 case _UP_KEY_MESSAGE:
//		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_CONTROL);
//		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		 COsdShowChooseServiceText(_STRING_SERVICE_CONTROL);
//		 break;
//
//	 case _MENU_KEY_MESSAGE:
//	 case _LEFT_KEY_MESSAGE:
//		 SET_OSD_STATE(_MENU_SERVICE);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
//		 break;
//
//	 default:
//		 break;
//	 }
// }
//
//void MenuServiceBacklightFreq(void)
// {
//	 switch (GET_KEYMESSAGE())
//	 {
//	 case _SELECT_KEY_MESSAGE:
//	 case _RIGHT_KEY_MESSAGE:
//		 g_usBackupValue = GET_OSD_BACKLIGHT_FREQ();
//		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ_ADJ);
//		 OsdDispMainMenukeySlideAndOption(_MENU_SERVICE_BACKLIGHT_FREQ_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_SERVICE_BACKLIGHT_FREQ_ADJ, _SLIDER_0, _OFF, 0);
//		 break;
//
//	 case _DOWN_KEY_MESSAGE:
//		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES);
//		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		 COsdShowChooseServiceText(_STRING_SERVICE_PWM_RES);
//		 break;
//
//	 case _UP_KEY_MESSAGE:
//		 SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
//		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_8, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2 + 1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		 COsdShowChooseServiceText(_STRING_SERVICE_INVERT);
//		 break;
//
//	 case _MENU_KEY_MESSAGE:
//	 case _LEFT_KEY_MESSAGE:
//		 SET_OSD_STATE(_MENU_SERVICE);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_5);
//		 OsdFuncClearOsd(ROW(2), COL(37), WIDTH(15), HEIGHT(22));
//		 OsdFontPut1FuncTableForm(2, 37, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _ARC_WINDOW_0);
//		 ScalerOsdWindowDisable(_OSD_WINDOW_4_8);
//		 break;
//
//	 default:
//		 break;
//	 }
// }
 
void MenuPictureBacklightAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_BACKLIGHT())
			{
				//backlight is OSDUSER data
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
              SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
			  OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_BACKLIGHT_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_BACKLIGHT_ADJUST,_SLIDER_0,_ON,0);
            break;
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
  			  OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_BACKLIGHT_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_BACKLIGHT_ADJUST,_SLIDER_0,_OFF,0);

#if (_BACKLIGHT_SELECT == _BACKLIGHT_ADJ)
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
#else
    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_BACKLIGHT())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_BACKLIGHT(g_usAdjustValue);
				UserAdjustBacklight(GET_OSD_BACKLIGHT());
			}
             //brightness is BRICON data
             SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
             SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
			 COsdShowChoosePictureText(_STRING_BACKLIGHT);
            break;

        default:
            break;                   
    }
}

void MenuPictureBrightnessAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:

		if (g_usBackupValue != GET_OSD_BRIGHTNESS())
		{
			//brightness is BRICON data
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
		}
		SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_BRIGHTNESS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_BRIGHTNESS_ADJUST, _SLIDER_1, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_BRIGHTNESS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_BRIGHTNESS_ADJUST, _SLIDER_1, _OFF, 0);

		UserAdjustBrightness(GET_OSD_BRIGHTNESS());

		break;

	case _MENU_KEY_MESSAGE:
		//OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_BRIGHTNESS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_BRIGHTNESS_ADJUST,_SLIDER_0,_OFF,0);
		if (g_usBackupValue != GET_OSD_BRIGHTNESS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_BRIGHTNESS(g_usAdjustValue);
			UserAdjustBrightness(GET_OSD_BRIGHTNESS());
		}
	//brightness is BRICON data
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
		SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
		COsdShowChoosePictureText(_STRING_BRIGHTNESS);
		break;

	default:
		break;
	}
}

void MenuPictureContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_CONTRAST())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
			}
			SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
			OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_CONTRAST_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_PICTURE_CONTRAST_ADJUST,_SLIDER_2,_ON,0);
        break;

		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_CONTRAST_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_PICTURE_CONTRAST_ADJUST,_SLIDER_2,_OFF,0);
            UserAdjustContrast(GET_OSD_CONTRAST());
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_CONTRAST())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_CONTRAST(g_usAdjustValue);
				UserAdjustContrast(GET_OSD_CONTRAST());
			}
            //OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_CONTRAST_ADJUST-_MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_PICTURE_CONTRAST_ADJUST,_SLIDER_1,_OFF,0);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
			SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
			COsdShowChoosePictureText(_STRING_CONTRAST);
            break;

        default:
            break;                   
    }
}

void MenuPictureSharpnessAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SHARPNESS())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_SHARPNESS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_SHARPNESS_ADJUST, _SLIDER_3, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_SHARPNESS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_SHARPNESS_ADJUST, _SLIDER_3, _OFF, 0);
		UserCommonAdjustSharpness(SysSourceGetInputPort());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SHARPNESS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_SHARPNESS(g_usAdjustValue);
			UserCommonAdjustSharpness(SysSourceGetInputPort());
		}

		//OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_CONTRAST_ADJUST-_MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_PICTURE_CONTRAST_ADJUST,_SLIDER_1,_OFF,0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
		COsdShowChoosePictureText(_STRING_SHARPNESS);
		break;

	default:
		break;
	}
}

void MenuPictureHueAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_HUE())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_PICTURE_HUE);
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_HUE_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_HUE_ADJUST, _SLIDER_4, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_HUE_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_HUE_ADJUST, _SLIDER_4, _OFF, 0);
		UserAdjustGlobalHueSat(GET_OSD_HUE(), GET_OSD_SATURATION());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_HUE())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_HUE(g_usAdjustValue);
			UserAdjustGlobalHueSat(GET_OSD_HUE(), GET_OSD_SATURATION());
		}
		//OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_CONTRAST_ADJUST-_MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_PICTURE_CONTRAST_ADJUST,_SLIDER_1,_OFF,0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		SET_OSD_STATE(_MENU_PICTURE_HUE);
		COsdShowChoosePictureText(_STRING_HUE);
		break;

	default:
		break;
	}
}

void MenuPictureSaturationAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SATURATION())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_PICTURE_SATURATION);
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_SATURATION_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_SATURATION_ADJUST, _SLIDER_5, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_SATURATION_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_PICTURE_SATURATION_ADJUST, _SLIDER_5, _OFF, 0);
		UserAdjustGlobalHueSat(GET_OSD_HUE(), GET_OSD_SATURATION());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SATURATION())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_SATURATION(g_usAdjustValue);
			UserAdjustGlobalHueSat(GET_OSD_HUE(), GET_OSD_SATURATION());
		}
		//OsdDispMainMenukeySlideAndOption(_MENU_PICTURE_CONTRAST_ADJUST-_MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_PICTURE_CONTRAST_ADJUST,_SLIDER_1,_OFF,0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		SET_OSD_STATE(_MENU_PICTURE_SATURATION);
		COsdShowChoosePictureText(_STRING_SATURATION);
		break;

	default:
		break;
	}
}
#if (_ENABLE_MENU_OLED == _ON)
void MenuPictureOLED_OffRsAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue == _TRUE)
		{
			OsdDispDisableOsd();
			OsdDispOsdMessage(_OSD_DISP_OFF_RS_MSG);
			ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);
			DebugMessageOsd("Activate OFF RS", AMOLED_ReadByte(_AMOLED_APL1_TPC_OFFRS_REG));
			ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_OFF_RS_RUN);
			SET_COMP_RUN_RESTART(_ON);
			g_usBackupValue = _FALSE;
		}
		else
		{
			SET_OSD_STATE(_MENU_PICTURE_OLED_OFFRS);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//COsdShowChoosePictureText(_STRING_OLED_OFFRS);
		}
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		g_usBackupValue = OsdDisplayDetOverRange(g_usBackupValue, _ON, _OFF, _ON, _OFF);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		g_usBackupValue = _FALSE;
		SET_OSD_STATE(_MENU_PICTURE_OLED_OFFRS);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChoosePictureText(_STRING_OLED_OFFRS);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	default:
		break;
	}

}

void MenuPictureOLED_JBAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue == _TRUE)
		{
			OsdDispDisableOsd();
			OsdDispOsdMessage(_OSD_DISP_JB_MSG);
			ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);
			DebugMessageOsd("Activate JB", AMOLED_ReadByte(_AMOLED_JB_REG));
			ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_JB_RUN);
			g_usBackupValue = _FALSE;
		}
		else
		{
			SET_OSD_STATE(_MENU_PICTURE_OLED_JB);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//COsdShowChoosePictureText(_STRING_OLED_JB);
		}
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		g_usBackupValue = OsdDisplayDetOverRange(g_usBackupValue, _ON, _OFF, _ON, _OFF);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usBackupValue)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		g_usBackupValue = _FALSE;
		SET_OSD_STATE(_MENU_PICTURE_OLED_JB);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChoosePictureText(_STRING_OLED_JB);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;
	default:
		break;
	}
}
#endif

void MenuColortempAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
           SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
		   if(GET_COLOR_TEMP_TYPE()==_CT_USER)
		   {
			   ScalerOsdWindowDisable(_OSD_WINDOW_4_4);
			   ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			   ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
		   }
		   
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		   COsdShowChooseColorText(_STRING_COLORTEMP);
		   COsdShowPageText(_MENU_COLOR);
              
            break;
            
        case _DOWN_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
        case _UP_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
			CLR_KEYREPEATENABLE();
			SET_COLOR_TEMP_TYPE(OsdDisplayDetOverRange(GET_COLOR_TEMP_TYPE(), _CT_USER, _CT_9300, _ON, _OFF));
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW +(3* GET_COLOR_TEMP_TYPE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            UserAdjustContrast(GET_OSD_CONTRAST());

            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_COLOR_TEMP_TYPE(g_usAdjustValue);
				RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
				UserAdjustContrast(GET_OSD_CONTRAST());
			}
           SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		   COsdShowChooseColorText(_STRING_COLORTEMP);
		   COsdShowPageText(_MENU_COLOR);
     //  OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMPERATURE_ADJUST-_MENU_COLOR_TEMPERATURE_ADJUST,_MENU_COLOR_TEMPERATURE_ADJUST,_SLIDER_1,_OFF,1);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            
            break;

        default:
            break;                   
    }
}

void MenuColortempUserAdjustR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
			}
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_6,_ON,0);
     //  OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_0,_ON,0);
                
        break;
            
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_6,_OFF,0);
     //  OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_0,_OFF,0);
	 		UserAdjustContrast(GET_OSD_CONTRAST());
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);
				UserAdjustContrast(GET_OSD_CONTRAST());
			}

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_R- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_R,_SLIDER_6,_ON,0);
			//COsdShowChooseColorText(_STRING_COLOR_RED);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            break;

        default:
            break;                   
    }
}

void MenuColortempUserAdjustG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
			}
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_7,_ON,0);
      // OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_1,_ON,0);
            break;
            
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_7,_OFF,0);
      // OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_1,_OFF,0);
            UserAdjustContrast(GET_OSD_CONTRAST());
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);
				UserAdjustContrast(GET_OSD_CONTRAST());
			}

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_G- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_G,_SLIDER_7,_ON,0);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            break;

        default:
            break;                   
    }
}

void MenuColortempUserAdjustB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
			}
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_8,_ON,0);
     //  OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_2,_ON,0);
        break;
            
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_8,_OFF,0);
   //    OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B-_MENU_COLOR_TEMP_USER_ADJUST_R,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_2,_OFF,0);
            UserAdjustContrast(GET_OSD_CONTRAST());
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);
				UserAdjustContrast(GET_OSD_CONTRAST());
			}

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
			OsdDispMainMenukeySlideAndOption(_MENU_COLOR_TEMP_USER_ADJUST_B- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_COLOR_TEMP_USER_ADJUST_B,_SLIDER_8,_ON,0);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            break;

        default:
            break;                   
    }
}
#if(_HDR10_SUPPORT == _ON)
void MenuColorHDRAdjust(void)
{
	int port;
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_HDR_MODE())
		{

			//RTDNVRamSaveOSDData();
			for (port = _D0_INPUT_PORT; port < _D4_INPUT_PORT; port++)
			{
				UserInterfaceGetEmbeddedEDIDData(port);
			}
			
			UserCommonInterfaceSetHPD(SysSourceGetInputPort());
#if(_HDR10_SUPPORT == _ON)
			UserCommonHDR10SupportSwitch();
#endif
			UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
			if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
			{
				UserAdjustBacklight(_BACKLIGHT_MAX());
			}
			else
			{
				UserAdjustBacklight(GET_OSD_BACKLIGHT());
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}

		SET_OSD_STATE(_MENU_COLOR_HDR);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseColorText(_STRING_HDR);
		COsdShowPageText(_MENU_COLOR);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
	{
		CLR_KEYREPEATENABLE();
		SET_OSD_HDR_MODE(OsdDisplayDetOverRange(GET_OSD_HDR_MODE(), _HDR10_MODE_AUTO, _HDR10_MODE_OFF, _ON , _OFF));

		switch (GET_OSD_HDR_MODE())
		{
		case _HDR10_MODE_OFF:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _HDR10_MODE_AUTO:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _HDR10_MODE_FORCE_2084:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		default:
			break;
		}
	}
           break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_HDR_MODE())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_HDR_MODE(g_usAdjustValue);
				for (port = _D0_INPUT_PORT; port < _D4_INPUT_PORT; port++)
				{
					UserInterfaceGetEmbeddedEDIDData(port);
				}

				UserCommonInterfaceSetHPD(SysSourceGetInputPort());
#if(_HDR10_SUPPORT == _ON)
				UserCommonHDR10SupportSwitch();
#endif
				UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
				if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
				{
					UserAdjustBacklight(_BACKLIGHT_MAX());
				}
				else
				{
					UserAdjustBacklight(GET_OSD_BACKLIGHT());
				}
			}
           SET_OSD_STATE(_MENU_COLOR_HDR);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		   COsdShowChooseColorText(_STRING_HDR);
		   COsdShowPageText(_MENU_COLOR);
           SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            
            break;

        default:
            break;                   
    }

}
#endif
void MenuColorECOAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_COLOR_EFFECT())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_COLOR_ECO);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseColorText(_STRING_COLOR_EFFECT);
		COsdShowPageText(_MENU_COLOR);	
		//  OsdDispMainMenukeySlideAndOption(_MENU_COLOR_EFFECT_ADJUST-_MENU_COLOR_TEMPERATURE_ADJUST,_MENU_COLOR_EFFECT_ADJUST,_SLIDER_1,_ON,1);
		

		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_COLOR_EFFECT(OsdDisplayDetOverRange(GET_OSD_COLOR_EFFECT(), _COLOREFFECT_USER, _COLOREFFECT_STANDARD, _ON, _OFF));
		//==== Show page item=======   
//			if(GET_OSD_COLOR_EFFECT()==_COLOREFFECT_RTS)
		{
			//OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_2, _STRING_BACKLIGHT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			//OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_2, _STRING_CONTRAST, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());	
			//ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
			//ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
			//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);

		}
		//Eric_020180307 : Delete
		//    			else 
		//    			{
		//    				//OsdPropPutString(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_2, _STRING_BACKLIGHT, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
		//    				//OsdPropPutString(ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), _PFONT_PAGE_2, _STRING_CONTRAST, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());	
		//    				ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		//    				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		//    				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_1_COL-1), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		//    				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_1_COL-1), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_GRAY, _CP_BG);
		//    			}


		switch (GET_OSD_COLOR_EFFECT())
		{
		case _COLOREFFECT_STANDARD:

			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _COLOREFFECT_GAME:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _COLOREFFECT_MOVIE:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _COLOREFFECT_PHOTO:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _COLOREFFECT_VIVID:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		//case _COLOREFFECT_USER:
		//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		//	break;
			//Eric_020180307 : Delete
			//    			   case _COLOREFFECT_FPS:
			//    				  ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//    				   OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//    				   break;
			//    			   case _COLOREFFECT_RTS:
			//    				   ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//    				   OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//    				   break;
		default:
			break;
		}

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
		UserAdjustColorEffectMode();
#endif


		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_COLOR_EFFECT())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_COLOR_EFFECT(g_usAdjustValue);
			UserAdjustColorEffectMode();
		}
		SET_OSD_STATE(_MENU_COLOR_ECO);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseColorText(_STRING_COLOR_EFFECT);
		//  OsdDispMainMenukeySlideAndOption(_MENU_COLOR_EFFECT_ADJUST-_MENU_COLOR_TEMPERATURE_ADJUST,_MENU_COLOR_EFFECT_ADJUST,_SLIDER_1,_OFF,1);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

		break;

	default:
		break;
	}
}

void MenuColorGammaAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_GAMMA())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_COLOR_GAMMA);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseColorText(_STRING_GAMMA);
		COsdShowPageText(_MENU_COLOR);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_GAMMA(OsdDisplayDetOverRange(GET_OSD_GAMMA(), _GAMMA_AMOUNT, _GAMMA_OFF, _ON, _OFF));
		//ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
		//ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
		//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_WHITE, _CP_BG);
		switch (GET_OSD_GAMMA())
		{
		case _GAMMA_OFF:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _GAMMA_18:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _GAMMA_20:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

			break;
		case _GAMMA_22:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _GAMMA_24:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
#if(_TECNINT_DICOM)
		case _GAMMA_RC2:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
		case _GAMMA_RC3:
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			break;
#endif
		default:
			break;
		}
		ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
    
        if(GET_OSD_GAMMA() != _GAMMA_OFF)
        {
            UserAdjustGamma(GET_OSD_GAMMA());
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        }
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_GAMMA())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_GAMMA(g_usAdjustValue);
			UserAdjustGamma(GET_OSD_GAMMA());
			ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
			UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
		}
		SET_OSD_STATE(_MENU_COLOR_GAMMA);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseColorText(_STRING_GAMMA);
		//  OsdDispMainMenukeySlideAndOption(_MENU_COLOR_EFFECT_ADJUST-_MENU_COLOR_TEMPERATURE_ADJUST,_MENU_COLOR_EFFECT_ADJUST,_SLIDER_1,_OFF,1);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

		break;

	default:
		break;
	}
}

void MenuOsdSettingsLanguageAdjust(void)
{
BYTE   Icon=0;
BYTE   Lengh1=0,High1=0,Lengh2=5,High2=1;
BYTE   LaungageChoose=0;
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			SET_OSD_STATE(_MENU_OSDSETTINGS_LANGUAGE);
			for(Lengh1=1;Lengh1<6;Lengh1++)
			{
				OsdFuncClearOsd(ROW(4*Lengh1), COL(7), WIDTH(13), HEIGHT(1));
			}
			
			for(Lengh2=1;Lengh2<6;Lengh2++)
			{
				OsdFuncClearOsd(ROW(_OSD_NUMBER_1_ROW+(Lengh2-1)*3), COL(_OSD_NUMBER_1_COL), WIDTH(13), HEIGHT(1));
			}
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//OsdFuncClearOsd(ROW(2), COL(54), WIDTH(15), HEIGHT(20));
			//OsdFontPut1FuncTableForm(2, 54, _EDGE_LINE,16 ,20,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
			OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
			COsdShowPageText(_MENU_OSDSETTINGS);
			OsdPropPutString(ROW(4), COL(7), _PFONT_PAGE_0, _STRING_PICTURE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE()); 		
			OsdPropPutString(ROW(8), COL(7), _PFONT_PAGE_0, _STRING_COLOR, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());			   
			OsdPropPutString(ROW(12), COL(7), _PFONT_PAGE_0, _STRING_ADVANCE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());		
			OsdPropPutString(ROW(16), COL(7), _PFONT_PAGE_0, _STRING_SETUP, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			OsdPropPutString(ROW(20), COL(7), _PFONT_PAGE_0, _STRING_OTHER, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
			//OsdPropPutString(ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_1_COL + 36), _PFONT_PAGE_0, _STRING_NOW_RESOLUTION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
			//OsdPropPutString(ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_1_COL + 36), _PFONT_PAGE_0, _STRING_VERSION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
			//OsdPropPutString(ROW(_OSD_NUMBER_13_ROW + 3), COL(_OSD_NUMBER_1_COL + 20), _PFONT_PAGE_0, _STRING_VERSION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
			COsdShowChooseOSDSetText(_STRING_OSDSET_LANGUAGE);
			OsdDispMainMenuItemSelection(_MENU_OSDSETTINGS-1, _OSD_SELECT);

//		switch(SysSourceGetInputPort())
//		{
//#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
//			case _A0_INPUT_PORT:
//				break;		
//#endif   
//
//#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
//			case _D0_INPUT_PORT:
//				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_DP, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);  
//				break;
//#endif 
//
//#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
//			case _D1_INPUT_PORT:
//				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_DP, COLOR(_CP_WHITE, _CP_BG), _ESPANA);  
//				break;
//		// return _STRING_D1_PORT;
//#endif 
//
//#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
//			case _D2_INPUT_PORT:
//				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_HDMI, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);  
//				break;
//			  //  return _STRING_D2_PORT;
//#endif   
//
//#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
//			case _D3_INPUT_PORT:
//				OsdPropPutString(ROW(_OSD_NUMBER_4_ROW-2), COL(_OSD_NUMBER_1_COL+38), _PFONT_PAGE_0, _STRING_SETUP_HDMI, COLOR(_CP_WHITE, _CP_BG), _ESPANA);	
//				break;
//		//	return _STRING_D3_PORT;
//#endif        
//#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
//			case _D4_INPUT_PORT:
//				 break;
//		//	return _STRING_D4_PORT;
//#endif  
//
//#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
//			case _D5_INPUT_PORT:
//				break;
//#endif
//
//#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
//			case _D6_INPUT_PORT:
//				break;
//
//#endif 
//			default:
//			break ;
//			  // return _STRING_A0_PORT;
//}


			
		// OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_3, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_SLIDE_VALUE_OFFSET+2), HEIGHT(1), _CP_GRAY_1, _CP_LIGHTBLUE, _CP_BG);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
        break;
            
        case _DOWN_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
        case _UP_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
			CLR_KEYREPEATENABLE();
			LaungageChoose = OsdDisplayDetOverRange(GET_OSD_LANGUAGE() , _LANGUAGE_AMOUNT, _ENGLISH, _ON, _OFF);
#if (_ENABLE_MENU_OLED == _ON)
			if(LaungageChoose==_ENGLISH)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_ENGLISH);
			}
			else if(LaungageChoose==_CHINESE_T)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_CHINESE_T);
			}
			else if(LaungageChoose==_ESPANA)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_ESPANA);
			}
			else if(LaungageChoose==_FRENCH)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_FRENCH);
			}
			else if(LaungageChoose==_GERMAN)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_GERMAN);
			}
			else if(LaungageChoose==_ITALIANO)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_ITALIANO);
			}
			else if (LaungageChoose == _RUSSIAN)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_RUSSIAN);
			}
			//else if(LaungageChoose==_KOREAN)
			//{
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//	SET_OSD_LANGUAGE(_KOREAN);
			//}

#else
			if (LaungageChoose == _ENGLISH)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_ENGLISH);
			}
			else if (LaungageChoose == _ESPANA)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_2_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_ESPANA);
			}
			else if (LaungageChoose == _FRENCH)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_3_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_FRENCH);
			}
			else if (LaungageChoose == _GERMAN)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_4_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_GERMAN);
			}
			else if (LaungageChoose == _ITALIANO)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_11_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_ITALIANO);
			}
			else if (LaungageChoose == _NEDERLAND)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_NEDERLAND);
			}
			else if (LaungageChoose == _RUSSIAN)
			{
				ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
				ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
				SET_OSD_LANGUAGE(_RUSSIAN);
			}
			//else if(LaungageChoose==_KOREAN)
			//{
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_12_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//	SET_OSD_LANGUAGE(_KOREAN);
			//}
			//else if(LaungageChoose==_CHINESE_T)
			//{
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
			//	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			//	OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_13_ROW),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			//	SET_OSD_LANGUAGE(_CHINESE_T);
			//}
#endif
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OSDSETTINGS_LANGUAGE);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowPageText(_MENU_OSDSETTINGS);
			COsdShowChooseOSDSetText(_STRING_OSDSET_LANGUAGE);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
        break;

        default:
            break;                   
    }
}


void MenuOsdSettingsHPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_HPOS())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
            SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_HPOS);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_HPOS_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_OSD_HPOS_ADJUST,_SLIDER_2,_ON,0);
            
            break;
            
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
	     OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_HPOS_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_OSD_HPOS_ADJUST,_SLIDER_2,_OFF,0);
              if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
                {
                     OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A,(_OSD_H_POS_MAX - GET_OSD_HPOS()), (_OSD_V_POS_MAX - GET_OSD_VPOS()));
                }  
              else
                {
                     OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,GET_OSD_HPOS(), GET_OSD_VPOS());
                }
              
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_HPOS())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_HPOS(g_usAdjustValue);
				if (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
				{
					OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, (_OSD_H_POS_MAX - GET_OSD_HPOS()), (_OSD_V_POS_MAX - GET_OSD_VPOS()));
				}
				else
				{
					OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
				}
			}
            SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_HPOS);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_HPOS_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_OSD_HPOS_ADJUST,_SLIDER_2,_ON,0);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            break;

        default:
            break;                   
    }
}

void MenuOsdSettingsVPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_VPOS())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
            SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_VPOS);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_VPOS_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_OSD_VPOS_ADJUST,_SLIDER_3,_ON,0);
           break;
            
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_VPOS_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_OSD_VPOS_ADJUST,_SLIDER_3,_OFF,0);
       //     ScalerTimerDelayXms(20);
              if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
                {
                     OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,(_OSD_H_POS_MAX-GET_OSD_HPOS()), (_OSD_V_POS_MAX-GET_OSD_VPOS()));
                }  
              else
                {
                     OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
                }
            break;

        case _MENU_KEY_MESSAGE:
		{
			if (g_usBackupValue != GET_OSD_VPOS())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_VPOS(g_usAdjustValue);
				if (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
				{
					OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, (_OSD_H_POS_MAX - GET_OSD_HPOS()), (_OSD_V_POS_MAX - GET_OSD_VPOS()));
				}
				else
				{
					OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
				}
			}
			SET_OSD_STATE(_MENU_OSDSETTINGS_OSD_VPOS);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_OSD_VPOS_ADJUST - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OSDSETTINGS_OSD_VPOS_ADJUST, _SLIDER_3, _ON, 0);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
            break;

        default:
            break;                   
    }
}

void MenuOsdSettingsTransparencyAdjust(void)
{
  switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
            SET_OSD_STATE(_MENU_OSDSETTINGS_TRNASPARENCY);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST,_SLIDER_4,_ON,0);
          break;
            
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST,_SLIDER_4,_OFF,0);
            OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
				OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
			}
            SET_OSD_STATE(_MENU_OSDSETTINGS_TRNASPARENCY);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_TRNASPARENCY_ADJUST,_SLIDER_4,_ON,0);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            break;

        default:
            break;                   
    }

}


void MenuOsdSettingsMenuTimeAdjust(void)
{
  switch(GET_KEYMESSAGE())
    {

        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_TIME_OUT())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}

           SET_OSD_STATE(_MENU_OSDSETTINGS_MENU_TIME);
		   OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_MENU_TIME_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_MENU_TIME_ADJUST,_SLIDER_5,_ON,0);
            break;

			
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(GET_OSD_TIME_OUT(), _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OFF, _ON);
			SET_OSD_TIME_OUT(g_usAdjustValue);
			OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_MENU_TIME_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_MENU_TIME_ADJUST,_SLIDER_5,_OFF,0);
                  //  ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                   break;
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_TIME_OUT())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_TIME_OUT(g_usAdjustValue);
			}
           SET_OSD_STATE(_MENU_OSDSETTINGS_MENU_TIME);
		   OsdDispMainMenukeySlideAndOption(_MENU_OSDSETTINGS_MENU_TIME_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_OSDSETTINGS_MENU_TIME_ADJUST,_SLIDER_5,_ON,0);
           SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
           break;

        default:
            break;                   
    }
}

void MenuOsdSettingsRotateAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_ROTATE_STATUS())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OSDSETTINGS_ROTATE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOSDSetText(_STRING_OSDSET_ROTATE);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_ROTATE_STATUS(OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_180, _OSD_ROTATE_DEGREE_0, _ON, _OFF));
		//OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ROTATE_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
		OsdDispOsdRotateSwitch();
#endif
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_ROTATE_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_ROTATE_STATUS(g_usAdjustValue);
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
			OsdDispOsdRotateSwitch();
#endif
		}
		SET_OSD_STATE(_MENU_OSDSETTINGS_ROTATE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOSDSetText(_STRING_OSDSET_ROTATE);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
#if 0
  void MenuLeftKeyGame(void)
 {
	  CLR_KEYREPEATENABLE();
	 switch(GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
		 SET_OSD_STATE(_Menu_LEFTKEY_GAME_ADJUST);
		 //ScalerOsdWindowDisable(_OSD_WINDOW_1);
		 OsdFontPut1FuncTableForm(0, 0, _EDGE_LINE,g_ucOsdWidth-2,g_ucOsdHeight-2,_CP_BG,_CP_BG,3);
		 OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
		 if( GET_OSD_LANGUAGE()==_KOREAN)
		 {		 
			 OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_CURSOR, COLOR(_CP_WHITE, _CP_BG), _KOREAN);
		 }
		 else
		 {
			 OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_CURSOR, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		 }
		 COsdShowChooseLeftMenuText(_STRING_LEFT_MENU_AIM);
	 	{
			 if(GET_OSD_AIM()==_AIM_1)
			 	{
				 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);
				 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_WHITE);
				 
				 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);
				 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
				 
				 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	 
				 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
				 
				 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);	 
				 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	
			 	}
			 else if(GET_OSD_AIM()==_AIM_2)
			 	{
				 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
				 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
				 
				 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);	 
				 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_WHITE);
				 
				 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	 
				 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
				 
				 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);	 
				 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			 	}
			 else if(GET_OSD_AIM()==_AIM_3)
			 	{
				 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
				 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
				 
				 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE_H, _CP_BG);
				 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
				 
				 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);	 
				 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_WHITE);	 
				 
				 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE_H, _CP_BG);	 
				 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
			 	}
			 else if(GET_OSD_AIM()==_AIM_4)
			 	{
				 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
				 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
				 
				 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);
				 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
				 
				 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	 
				 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
				 
				 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);	 
				 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_WHITE);
			 	}
	 	
		 }
		 
	 
 
	 break;
	 case _DOWN_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
	 case _UP_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_STATE(_Menu_LEFTKEY_TIMER);	 
		 SET_OSD_Left_Menu_Choose(OsdDisplayDetOverRange(GET_OSD_Left_Menu_Choose() , _LEFT_MENU_END, _LEFT_AIM, _ON, _OFF));
		 OsdFontPut1FuncAimTableForm(7,13, _EDGE_LINE,22,10,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		 OsdFontPut1FuncAimTableForm(7,40, _EDGE_LINE,22,10,_CP_WHITE,_CP_BLUE_65,_CP_WHITE,0);
		 OsdFontPut1BitMainMenuIcon(11, 22, _LEFT_MENU_AIM_ICON_START , _CP_ORANGE_H, _CP_BG);	  
		 OsdFontPut1BitMainMenuIcon(11, 49, _LEFT_MENU_TIME_ICON_START , _CP_ORANGE_H, _CP_WHITE);
		 
	 break;
		

	//(BYTE)OsdDisplayDetOverRange(GET_OSD_HPOS(), _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OFF);	
	 case _MENU_KEY_MESSAGE:
		 OsdDispDisableOsd();
	 break;
		 
		 default:
			 break; 				  
	 }
 }

//MenuLeftKeyTimer
   void MenuLeftKeyTimer(void)
  {
	CLR_KEYREPEATENABLE();
	  switch(GET_KEYMESSAGE())
	  {
	  case _SELECT_KEY_MESSAGE:
		  SET_OSD_STATE(_Menu_LEFTKEY_TIMER_ADJUST);
		  OsdFontPut1FuncTableForm(0, 0, _EDGE_LINE,g_ucOsdWidth-2,g_ucOsdHeight-2,_CP_BG,_CP_BG,3);
		  OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
		  if( GET_OSD_LANGUAGE()==_KOREAN)
		  {
			  OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_TIME, COLOR(_CP_WHITE, _CP_BG), _KOREAN);
		  }
		  else
		  {
			  OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_TIME, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		  }
		  COsdShowChooseLeftMenuText(_STRING_LEFT_MENU_TIMER);
		  //ScalerOsdWindowDisable(_OSD_WINDOW_1);
		 // OsdFontPut1FuncTableForm(0, 0, _EDGE_LINE,g_ucOsdWidth-2,g_ucOsdHeight-2,_CP_BG,_CP_BG,3);
		 // OsdFuncClearOsd(ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight));
		  {

		  
			  if(GET_OSD_Timer()==_TIMER_10)
			  	{
				  OsdFontPut1FuncAimTableForm(7,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,1);	  
				  OsdFontPut1NumberTableForm(8, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(8, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);   
				  OsdFontPut1NumberTableForm(8, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  else if(GET_OSD_Timer()==_TIMER_20)
			  	{
				  OsdFontPut1FuncAimTableForm(7,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,2);	  
				  OsdFontPut1NumberTableForm(8, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(8, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	  
				  OsdFontPut1NumberTableForm(8, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  else if(GET_OSD_Timer()==_TIMER_30)
			  	{
				  OsdFontPut1FuncAimTableForm(7,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,3);	  
				  OsdFontPut1NumberTableForm(8, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(8, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	  
				  OsdFontPut1NumberTableForm(8, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  else if(GET_OSD_Timer()==_TIMER_40)
			  	{
				  OsdFontPut1FuncAimTableForm(7,8+53, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 8+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,4);	  
				  OsdFontPut1NumberTableForm(8, 10+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 12+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(8, 14+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	  
				  OsdFontPut1NumberTableForm(8, 16+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  else if(GET_OSD_Timer()==_TIMER_50)
			  	{
				  OsdFontPut1FuncAimTableForm(13,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(14, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,5);   
				  OsdFontPut1NumberTableForm(14, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(14, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(14, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);  
				  OsdFontPut1NumberTableForm(14, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  else if(GET_OSD_Timer()==_TIMER_60)
			  	{
				  OsdFontPut1FuncAimTableForm(13,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(14, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,6);	  
				  OsdFontPut1NumberTableForm(14, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(14, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(14, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);   
				  OsdFontPut1NumberTableForm(14, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  else if(GET_OSD_Timer()==_TIMER_90)
			  	{
				  OsdFontPut1FuncAimTableForm(13,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(14, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,9);	  
				  OsdFontPut1NumberTableForm(14, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(14, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(14, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);   
				  OsdFontPut1NumberTableForm(14, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  else
			  	{
				  SET_OSD_Timer(_TIMER_10);
				  OsdFontPut1FuncAimTableForm(7,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,1);	  
				  OsdFontPut1NumberTableForm(8, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
				  OsdFontPut1NumberTableForm(8, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
				  OsdFontPut1NumberTableForm(8, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);   
				  OsdFontPut1NumberTableForm(8, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  	}
			  
				  
		  }
		  
	  
  
	  break;
		  
	  case _DOWN_KEY_MESSAGE:
	  case _RIGHT_KEY_MESSAGE:
	  case _UP_KEY_MESSAGE:
	  case _LEFT_KEY_MESSAGE:
	  SET_OSD_STATE(_Menu_LEFTKEY_GAME);
	  SET_OSD_Left_Menu_Choose(OsdDisplayDetOverRange(GET_OSD_Left_Menu_Choose() , _LEFT_MENU_END, _LEFT_AIM, _ON, _OFF));
		  OsdFontPut1FuncAimTableForm(7,13, _EDGE_LINE,22,10,_CP_WHITE,_CP_BLUE_65,_CP_WHITE,0);
		  OsdFontPut1FuncAimTableForm(7,40, _EDGE_LINE,22,10,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		  OsdFontPut1BitMainMenuIcon(11, 22, _LEFT_MENU_AIM_ICON_START , _CP_ORANGE_H, _CP_WHITE);	   
		  OsdFontPut1BitMainMenuIcon(11, 49, _LEFT_MENU_TIME_ICON_START , _CP_ORANGE_H, _CP_BG);
		  
  	  break;
	 //(BYTE)OsdDisplayDetOverRange(GET_OSD_HPOS(), _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OFF);	 
	  
	  case _MENU_KEY_MESSAGE:
		  OsdDispDisableOsd();
	  break;
		  
		  default:
			  break;				   
	  }
  }
  
 void MenuLeftKeyGameAdjust(void)
{
	 CLR_KEYREPEATENABLE();

	switch(GET_KEYMESSAGE())
	{


	case _SELECT_KEY_MESSAGE:
		SET_OSD_STATE(_Menu_LEFTKEY_GAME);
		OsdDispDisableOsd();
		OsdDispLeftAimMenu();

	break;
		
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		SET_OSD_AIM(OsdDisplayDetOverRange(GET_OSD_AIM() , _AIM_END, 0, _ON, _OFF));


		
		switch(GET_OSD_AIM())
		{
			case _AIM_1:

				OsdFontPut1FuncAimTableForm(8, 12, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_WHITE,0);
				//OsdFontPut1FuncTableForm(8, 6, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);
				OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_WHITE);

				OsdFontPut1FuncAimTableForm(8,28, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);
				
				OsdFontPut1FuncAimTableForm(8,44, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	

				OsdFontPut1FuncAimTableForm(8,60, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);	
				break;
			case _AIM_2:
				OsdFontPut1FuncAimTableForm(8,12, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
				
				OsdFontPut1FuncAimTableForm(8,28, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_WHITE,0);
				OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_WHITE);

				OsdFontPut1FuncAimTableForm(8,44, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	

				OsdFontPut1FuncAimTableForm(8,60, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);	
				break;
			case _AIM_3:
				OsdFontPut1FuncAimTableForm(8,12, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);

				OsdFontPut1FuncAimTableForm(8,28, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);
				
				//OsdFontPut1FuncTableForm(8, 38, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);
				OsdFontPut1FuncAimTableForm(8,44, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_WHITE,0);
				OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_WHITE); 

				OsdFontPut1FuncAimTableForm(8,60, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);	
				break;
			case _AIM_4:
				OsdFontPut1FuncAimTableForm(8,12, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);

				OsdFontPut1FuncAimTableForm(8,28, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);

				OsdFontPut1FuncAimTableForm(8,44, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
				OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	
				
				OsdFontPut1FuncAimTableForm(8,60, _EDGE_LINE,8,6,_CP_WHITE,_CP_BLUE_65,_CP_WHITE,0);
				OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_WHITE);
				break;
				
			 default:
				 break;
		}
		
		break;



	
	case _MENU_KEY_MESSAGE:
		OsdFuncSetOsdItemFlag();
		OsdDispLeftMenu();
	break;
		
		default:
			break;					 
	}
}

void MenuLeftKeyTimerAdjust(void)
{

	BYTE ucForeground1=0;
	BYTE ucBackground1=0;
	BYTE ucForeground2=0;
	BYTE ucBackground2=0;
	BYTE ucForeground3=0;
	BYTE ucBackground3=0;
	BYTE ucForeground4=0;
	BYTE ucBackground4=0;
	BYTE ucForeground5=0;
	BYTE ucBackground5=0;
	BYTE ucForeground6=0;
	BYTE ucBackground6=0;
	BYTE ucForeground7=0;
	BYTE ucBackground7=0;
	BYTE uchpos=0;
	BYTE ucvpos=0;
	CLR_KEYREPEATENABLE();
 switch(GET_KEYMESSAGE())
 {
 case _SELECT_KEY_MESSAGE:
	 SET_OSD_STATE(_OSD_DISPLEFT_TIMER_MENU_POSITION);
	//OsdDispDisableOsd();
	 //OsdDispLeftTimerMenu();
	OsdFontPut1FuncHLine(18, 8, _WHITE_EDGE_1, g_ucOsdWidth-8 ,_CP_WHITE, _CP_BLUE_65);
	OsdPropPutString(ROW(20), COL(8), _PFONT_PAGE_2, _STRING_GAME_TIMER_POSITION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	OsdFontPut1ChooseIcon(20, 18, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
	OsdFontPut1ChooseIcon(21, 28, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
	OsdFontPut1ChooseIcon(22, 38, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
	switch(GET_OSD_Left_Timer_Position())
	{
		case _LEFT_TIMER_POSITION_1:
			OsdThreeColorChooseTableForm(19, 17,_EDGE_LINE,2 ,1,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
			OsdFontPut1ChooseIcon(20, 18, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
			
			break;
		case _LEFT_TIMER_POSITION_2:
			OsdThreeColorChooseTableForm(20, 27,_EDGE_LINE,2 ,1,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
			OsdFontPut1ChooseIcon(21, 28, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
			break;
		case _LEFT_TIMER_POSITION_3:
			OsdThreeColorChooseTableForm(21, 37,_EDGE_LINE,2 ,1,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
			OsdFontPut1ChooseIcon(22, 38, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
			break;
		 default:
		 	SET_OSD_Left_Timer_Position(_LEFT_TIMER_POSITION_1);
			OsdThreeColorChooseTableForm(19, 17,_EDGE_LINE,2 ,1,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
			OsdFontPut1ChooseIcon(20, 18, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
			 break;
	}
 break;
	 
 case _DOWN_KEY_MESSAGE:
 case _RIGHT_KEY_MESSAGE:
 case _UP_KEY_MESSAGE:
 case _LEFT_KEY_MESSAGE:
	 SET_OSD_Timer(OsdDisplayDetOverRange(GET_OSD_Timer() , _TIMER_END, _TIMER_10, _ON, _OFF));

	 switch(GET_OSD_Timer())
	 {
	 case _TIMER_10:
	 
		ucForeground1=_CP_RED;
		ucForeground2=_CP_WHITE;
		ucForeground7=_CP_WHITE;
		OsdFontPut1FuncAimTableForm(7,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,1);	
		OsdFontPut1NumberTableForm(8, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);

		 OsdFontPut1FuncAimTableForm(7,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(8, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,2);	 
		 OsdFontPut1NumberTableForm(8, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(8, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,10);
		 OsdFontPut1NumberTableForm(8, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);	 
		 OsdFontPut1NumberTableForm(8, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);

		 OsdFontPut1FuncAimTableForm(13,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(14, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,9);	 
		 OsdFontPut1NumberTableForm(14, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(14, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,10);
		 OsdFontPut1NumberTableForm(14, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);	 
		 OsdFontPut1NumberTableForm(14, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);
		 break;

	 
	case _TIMER_20:
	
		ucForeground2=_CP_RED;
		ucForeground1=_CP_WHITE;
		ucForeground3=_CP_WHITE;
		OsdFontPut1FuncAimTableForm(7,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,1);	
		OsdFontPut1NumberTableForm(8, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);
		
		
		
		
		
		 OsdFontPut1FuncAimTableForm(7,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(8, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,2);	 
		 OsdFontPut1NumberTableForm(8, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(8, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,10);
		 OsdFontPut1NumberTableForm(8, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);	 
		 OsdFontPut1NumberTableForm(8, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);
		
		 
		 OsdFontPut1FuncAimTableForm(7,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(8, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,3);	 
		 OsdFontPut1NumberTableForm(8, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);
		 OsdFontPut1NumberTableForm(8, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,10);
		 OsdFontPut1NumberTableForm(8, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);	 
		 OsdFontPut1NumberTableForm(8, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);
		
		break;
	case _TIMER_30:
		ucForeground3=_CP_RED;
		ucForeground2=_CP_WHITE;
		ucForeground4=_CP_WHITE;
		OsdFontPut1FuncAimTableForm(7,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,2); 	
		OsdFontPut1NumberTableForm(8, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground2,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(7,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,3); 	
		OsdFontPut1NumberTableForm(8, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(7,8+53, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,4); 	
		OsdFontPut1NumberTableForm(8, 10+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);
		
		break;
	case _TIMER_40:
		ucForeground4=_CP_RED;
		ucForeground3=_CP_WHITE;
		ucForeground5=_CP_WHITE;
		OsdFontPut1FuncAimTableForm(7,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,3); 	
		OsdFontPut1NumberTableForm(8, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground3,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(7,8+53, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,4); 	
		OsdFontPut1NumberTableForm(8, 10+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(13,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,5);	
		OsdFontPut1NumberTableForm(14, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);
		
		
		break;
	case _TIMER_50:
		ucForeground5=_CP_RED;
		ucForeground4=_CP_WHITE;
		ucForeground6=_CP_WHITE;
		OsdFontPut1FuncAimTableForm(7,8+53, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,4); 	
		OsdFontPut1NumberTableForm(8, 10+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground4,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(13,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,5);	
		OsdFontPut1NumberTableForm(14, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(13,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,6);	
		OsdFontPut1NumberTableForm(14, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);
		
	
	break;
	case _TIMER_60:
		ucForeground6=_CP_RED;
		ucForeground5=_CP_WHITE;
		ucForeground7=_CP_WHITE;
		OsdFontPut1FuncAimTableForm(13,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,5);	
		OsdFontPut1NumberTableForm(14, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground5,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(13,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,6);	
		OsdFontPut1NumberTableForm(14, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(13,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,9);	
		OsdFontPut1NumberTableForm(14, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);
		break;
	case _TIMER_90:
		ucForeground7=_CP_RED;
		ucForeground6=_CP_WHITE;
		ucForeground1=_CP_WHITE;
		OsdFontPut1FuncAimTableForm(13,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,6);	
		OsdFontPut1NumberTableForm(14, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground6,_CP_BLUE_65,0);
		
		
		OsdFontPut1FuncAimTableForm(13,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,9);	
		OsdFontPut1NumberTableForm(14, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(14, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(14, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(14, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground7,_CP_BLUE_65,0);
		OsdFontPut1FuncAimTableForm(7,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,1);	
		OsdFontPut1NumberTableForm(8, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);
		OsdFontPut1NumberTableForm(8, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,10);
		OsdFontPut1NumberTableForm(8, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);	
		OsdFontPut1NumberTableForm(8, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,ucForeground1,_CP_BLUE_65,0);
		break;
		default:
			break;
	 	}

	 break;



 
 case _MENU_KEY_MESSAGE:
 	
	//OsdDispDisableOsd();
	OsdFuncSetOsdItemFlag();
	OsdDispLeftMenu();
 break;
	 
	 default:
		 break; 				  
 }
}

void OsdDispLeftTimerMenu(void)
{
    BYTE ucTest = 0;

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    if(ucTest == 1)
    {

       ScalerOsdDataPort(0);


    }

    OsdFuncDisableOsd();

    OsdFuncApplyMap(WIDTH(_OSD_LEFT_KEY_TIMER_WIDTH+1), HEIGHT(_OSD_LEFT_KEY_TIMER_HEIGHT+1), COLOR(_CP_BLUE_120, _CP_BG));

//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_LEFT_KEY_TIMER_HEIGHT+1), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(255);

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
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
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
		

		
	
	  //background	  
		}
	if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
	  {
		switch(GET_OSD_Left_Timer_Position())
		{
			case _LEFT_TIMER_POSITION_1:
				OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_H_POS_MAX-0, _OSD_V_POS_MAX-0);
				break;
			case _LEFT_TIMER_POSITION_2:
				OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,_OSD_H_POS_MAX-0, _OSD_V_POS_MAX-50);
				break;
			case _LEFT_TIMER_POSITION_3:
				OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,_OSD_H_POS_MAX-0, _OSD_V_POS_MAX-90);
				break;
			 default:
				 break;
		}
	  }  
	else
	  {
		switch(GET_OSD_Left_Timer_Position())
		{
			case _LEFT_TIMER_POSITION_1:
				OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 0, 0);
				break;
			case _LEFT_TIMER_POSITION_2:
				OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 0, 50);
				break;
			case _LEFT_TIMER_POSITION_3:
				OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 0, 90);
				break;
			 default:
				 break;
		}
	}



	


    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();

}	

//void OsdDispLeftTimerCountDown(void)
//{
//	WORD gu_Timer = 0;
//		 switch(GET_OSD_Timer())
//		 {
//		 case _TIMER_10:
//			 gu_Timer=10 * 60;
//			 break;
//		
//		 
//		case _TIMER_20:
//		
//			gu_Timer=20 * 60;
//			break;
//		case _TIMER_30:
//			gu_Timer=30 * 60;
//			break;
//		case _TIMER_40:
//			gu_Timer=40 * 60;
//			
//			break;
//		case _TIMER_50:
//			gu_Timer=50 * 60;
//		break;
//		case _TIMER_60:
//			gu_Timer=60 * 60;
//			break;
//		case _TIMER_90:
//			gu_Timer=90 * 60;
//	
//			break;
//			default:
//				break;
//			}
//
////Eric_020180307 : delete
////    			OsdFontPut1NumberTableForm(1, 1, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BG,(gu_Timer-g_usTimeUse)/60/10); 
////    			OsdFontPut1NumberTableForm(1, 3, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BG,(gu_Timer-g_usTimeUse)/60%10);
////    			OsdFontPut1NumberTableForm(1, 5, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BG,10);
////    			OsdFontPut1NumberTableForm(1, 7, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BG,(gu_Timer-g_usTimeUse)%60/10); 
////    			OsdFontPut1NumberTableForm(1, 9, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BG,(gu_Timer-g_usTimeUse)%60%10);
////		 if( (gu_Timer-g_usTimeUse==0)) 
//		 {
//				SET_OSD_STATE(_Menu_LEFTKEY_TIMER_ADJUST);
//		 }
//}
void OsdDispLeftTimerMenuAdjust(void)
	{
		BYTE ucTest = 0;
	
		g_ucFontPointer0 = _OSD_PAGE_0_START;
		g_ucFontPointer1 = _OSD_PAGE_1_START;
		g_ucFontPointer2 = _OSD_PAGE_2_START;
	
		if(ucTest == 1)
		{
	
		   ScalerOsdDataPort(0);
	
	
		}
	
		OsdFuncDisableOsd();
	
		OsdFuncApplyMap(WIDTH(_OSD_LEFT_KEY_WIDTH), HEIGHT(_OSD_LEFT_KEY_HEIGHT), COLOR(_CP_BLUE_120, _CP_BG));
	
	//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
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
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
		if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
		{
    
			OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( (g_ucOsdHeight/2)-1), _CP_GREEN_119);
			OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( (g_ucOsdHeight/2)-1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)+1), _CP_GRAY_1 );//_CP_LIGHTBLUE
		 }
		else
#endif
    {
	OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight)), _CP_BG );
	if( GET_OSD_LANGUAGE()==_KOREAN)
	{
		OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_TIME, COLOR(_CP_WHITE, _CP_BG), _KOREAN);
	}
	else
	{
		OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_TIME, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	}
	COsdShowChooseLeftMenuText(_STRING_LEFT_MENU_TIMER);
		
	
    }
	{
	
	  
		  if(GET_OSD_Timer()==_TIMER_10)
			{
			  OsdFontPut1FuncAimTableForm(7,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,1);	  
			  OsdFontPut1NumberTableForm(8, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
			  OsdFontPut1NumberTableForm(8, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	
			  OsdFontPut1NumberTableForm(8, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			}
		  else if(GET_OSD_Timer()==_TIMER_20)
			{
			  OsdFontPut1FuncAimTableForm(7,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,2);   
			  OsdFontPut1NumberTableForm(8, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
			  OsdFontPut1NumberTableForm(8, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	  
			  OsdFontPut1NumberTableForm(8, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			}
		  else if(GET_OSD_Timer()==_TIMER_30)
			{
			  OsdFontPut1FuncAimTableForm(7,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,3);   
			  OsdFontPut1NumberTableForm(8, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
			  OsdFontPut1NumberTableForm(8, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	  
			  OsdFontPut1NumberTableForm(8, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			}
		  else if(GET_OSD_Timer()==_TIMER_40)
			{
			  OsdFontPut1FuncAimTableForm(7,8+53, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 8+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,4);   
			  OsdFontPut1NumberTableForm(8, 10+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(8, 12+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
			  OsdFontPut1NumberTableForm(8, 14+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	  
			  OsdFontPut1NumberTableForm(8, 16+54, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			}
		  else if(GET_OSD_Timer()==_TIMER_50)
			{
			  OsdFontPut1FuncAimTableForm(13,7, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(14, 8, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,5);	
			  OsdFontPut1NumberTableForm(14, 10, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(14, 12, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
			  OsdFontPut1NumberTableForm(14, 14, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	
			  OsdFontPut1NumberTableForm(14, 16, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			}
		  else if(GET_OSD_Timer()==_TIMER_60)
			{
			  OsdFontPut1FuncAimTableForm(13,8+17, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(14, 8+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,6);	  
			  OsdFontPut1NumberTableForm(14, 10+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(14, 12+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
			  OsdFontPut1NumberTableForm(14, 14+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	
			  OsdFontPut1NumberTableForm(14, 16+18, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			}
		  else if(GET_OSD_Timer()==_TIMER_90)
			{
			  OsdFontPut1FuncAimTableForm(13,8+35, _EDGE_LINE,11,3,_CP_WHITE,_CP_BLUE_65,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(14, 8+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,9);	  
			  OsdFontPut1NumberTableForm(14, 10+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			  OsdFontPut1NumberTableForm(14, 12+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,10);
			  OsdFontPut1NumberTableForm(14, 14+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);	
			  OsdFontPut1NumberTableForm(14, 16+36, _LEFT_MENU_NUMBER_ICON_START,2 ,3,_CP_RED,_CP_BLUE_65,0);
			}
					  
	  }
	
		
		
	
	if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
	  {
		   OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,(_OSD_H_POS_MAX-GET_OSD_HPOS()), (_OSD_V_POS_MAX-GET_OSD_VPOS()));
	  }  
	else
	  {
		   OsdDispSetPosition(_POS_PERCENT,  _OSD_POSITION_GLOBAL_A,GET_OSD_HPOS(), GET_OSD_VPOS());
	}
	
	
	
		// Osd Enable
		ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
		OsdFuncEnableOsd();
	
}

//void OsdDispLeftAimMenuAdjust(void)
//	{
//		BYTE ucTest = 0;
//	
//		g_ucFontPointer0 = _OSD_PAGE_0_START;
//		g_ucFontPointer1 = _OSD_PAGE_1_START;
//		g_ucFontPointer2 = _OSD_PAGE_2_START;
//	
//		if(ucTest == 1)
//		{
//	
//		   ScalerOsdDataPort(0);
//	
//	
//		}
//	
//		OsdFuncDisableOsd();
//	
//		OsdFuncApplyMap(WIDTH(_OSD_LEFT_KEY_WIDTH), HEIGHT(_OSD_LEFT_KEY_HEIGHT), COLOR(_CP_BLUE_120, _CP_BG));
//	
//	//20140304 Abel
//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//		ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_LEFT_KEY_HEIGHT), _DISABLE, 0, _ENABLE);
//#endif
//	
//		OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
//		OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//	
//		// Adjust Color Palette
//		OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
//	
//		// Load Font & Icon
//		OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
//	
//		OsdFontVLCLoadFont(_FONT1_GLOBAL);
//		//OsdFontVLCLoadFont(_FONT2_ICON_MENU);
//		 OsdFontVLCLoadFont(_LEFT_MENU_TIME_ICON);
//		 OsdFontVLCLoadFont(_LEFT_MENU_AIM_ICON);
//		 OsdFontVLCLoadFont(_FOUR_CORNER);
//		 OsdFontVLCLoadFont(_LEFT_MENU_NUMBER_ICON);
//	   // Background window
//	   //20140210 Abel Modify
//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//		if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//		{
// 
//			OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( (g_ucOsdHeight/2)-1), _CP_GREEN_119);
//			OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( (g_ucOsdHeight/2)-1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)+1), _CP_GRAY_1 );//_CP_LIGHTBLUE
//		 }
//		else
//#endif
//		
//		OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight)), _CP_BG );
//	if( GET_OSD_LANGUAGE()==_KOREAN)
//	{		
//		OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_CURSOR, COLOR(_CP_WHITE, _CP_BG), _KOREAN);
//	}
//	else
//	{
//		OsdPropPutString(ROW(4), COL(34), _PFONT_PAGE_2, _STRING_GAME_CURSOR, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
//	}
//	 COsdShowChooseLeftMenuText(_STRING_LEFT_MENU_AIM);
//	{
//		 if(GET_OSD_AIM()==_AIM_1)
//			{
//			 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);
//			 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_WHITE);
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);
//			 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	 
//			 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);  
//			 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	
//			}
//		 else if(GET_OSD_AIM()==_AIM_2)
//			{
//			 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
//			 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//			 
//			 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);	 
//			 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_WHITE);
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	 
//			 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_BG);  
//			 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//			}
//		 else if(GET_OSD_AIM()==_AIM_3)
//			{
//			 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
//			 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE_H, _CP_BG);
//			 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//			 
//			 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);	 
//			 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_WHITE);	 
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE_H, _CP_BG);	 
//			 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//			}
//		 else if(GET_OSD_AIM()==_AIM_4)
//			{
//			 OsdFontPut1BitMainMenuIcon(10, 14, _LEFT_MENU_AIM_ICON_START+24 , _CP_GREEN_119, _CP_BG);
//			 OsdFontPut1FuncTableForm(8, 12, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 30, _LEFT_MENU_AIM_ICON_START+24 , _CP_ORANGE, _CP_BG);
//			 OsdFontPut1FuncTableForm(8, 28, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);	 
//			 
//			 OsdFontPut1BitMainMenuIcon(10, 46, _LEFT_MENU_AIM_ICON_START+48 , _CP_GREEN_119, _CP_BG);	 
//			 OsdFontPut1FuncTableForm(8, 44, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,_ARC_WINDOW_0);
//			 
//			 OsdFontPut1FuncTableForm(8, 60, _EDGE_LINE,8 ,6,_CP_WHITE,_CP_BLUE_65,3);	 
//			 OsdFontPut1BitMainMenuIcon(10, 62, _LEFT_MENU_AIM_ICON_START+48 , _CP_ORANGE, _CP_WHITE);
//			}
//	
//	 }
//		
//	
//		
//		
//	
//	if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
//	  {
//		   OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, (_OSD_H_POS_MAX-GET_OSD_HPOS()), (_OSD_V_POS_MAX-GET_OSD_VPOS()));
//	  }  
//	else
//	  {
//		   OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//	}
//	
//	
//	
//		// Osd Enable
//		ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//		OsdFuncEnableOsd();
//	
//	}

//OsdDispLeftTimerMenuPosition
  void OsdDispLeftTimerMenuPosition(void)
 {
 
	  CLR_KEYREPEATENABLE();
 
	 switch(GET_KEYMESSAGE())
	 {
 
 
	 case _SELECT_KEY_MESSAGE:
		 OsdDispDisableOsd();
		 OsdDispLeftTimerMenu();
		 //OsdDispLeftMenu();
	 break;
	 case _DOWN_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
	 case _UP_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
		 SET_OSD_Left_Timer_Position(OsdDisplayDetOverRange(GET_OSD_Left_Timer_Position() , _LEFT_TIMER_POSITION_END, _LEFT_TIMER_POSITION_1, _ON, _OFF));
 
 
		 
		 switch(GET_OSD_Left_Timer_Position())
		 {
			 case _LEFT_TIMER_POSITION_1:
				 OsdThreeColorChooseTableForm(19, 17,_EDGE_LINE,2 ,1,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdThreeColorChooseTableForm(20, 27,_EDGE_LINE,2 ,1,_CP_BLUE_65, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdThreeColorChooseTableForm(21, 37,_EDGE_LINE,2 ,1,_CP_BLUE_65, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdFontPut1ChooseIcon(20, 18, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 OsdFontPut1ChooseIcon(21, 28, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 OsdFontPut1ChooseIcon(22, 38, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 break;
			 case _LEFT_TIMER_POSITION_2:
				 OsdThreeColorChooseTableForm(19, 17,_EDGE_LINE,2 ,1,_CP_BLUE_65, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdThreeColorChooseTableForm(20, 27,_EDGE_LINE,2 ,1,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdThreeColorChooseTableForm(21, 37,_EDGE_LINE,2 ,1,_CP_BLUE_65, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdFontPut1ChooseIcon(20, 18, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 OsdFontPut1ChooseIcon(21, 28, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 OsdFontPut1ChooseIcon(22, 38, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 break;
			 case _LEFT_TIMER_POSITION_3:
				 OsdThreeColorChooseTableForm(19, 17,_EDGE_LINE,2 ,1,_CP_BLUE_65, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdThreeColorChooseTableForm(20, 27,_EDGE_LINE,2 ,1,_CP_BLUE_65, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdThreeColorChooseTableForm(21, 37,_EDGE_LINE,2 ,1,_CP_WHITE, _CP_BLUE_65,_CP_BLUE_65,0);
				 OsdFontPut1ChooseIcon(20, 18, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 OsdFontPut1ChooseIcon(21, 28, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 OsdFontPut1ChooseIcon(22, 38, _LEFT_CORNER_0+1,_CP_WHITE, _CP_BLUE_65);
				 break;
			  default:
				  break;
		 }
		 
		 break;
 
 
 
	 
	 case _MENU_KEY_MESSAGE:
	 	
		 SET_OSD_STATE(_Menu_LEFTKEY_TIMER_ADJUST);
		 ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
		 OsdFuncDisableOsd();
		 OsdFuncCloseWindow(_OSD_WINDOW_ALL);
		 
		 OsdDispLeftTimerMenuAdjust();
		 
		 
	 break;
		 
		 default:
			 break; 				  
	 }
 }
 void MenuHotkeyECOAdjust(void)
 {
 
   switch(GET_KEYMESSAGE())
	 {
		 case _SELECT_KEY_MESSAGE:
			 OsdDispDisableOsd();
		 break;
			 
        case _DOWN_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
        case _UP_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
//_PICTURE_STANDARD			 
				 SET_OSD_COLOR_EFFECT(OsdDisplayDetOverRange(GET_OSD_COLOR_EFFECT() , _COLOREFFECT_USER, _COLOREFFECT_STANDARD, _ON, _OFF));
		 
		 switch(GET_OSD_COLOR_EFFECT())
		 {
			 case _COLOREFFECT_STANDARD:
				 OsdFuncClearOsd(ROW(5), COL(22), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1));
				 OsdPropPutString(ROW(5), COL(22), _PFONT_PAGE_2, _STRING_COLOR_STANDARD, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());
				 break;
			 case _COLOREFFECT_GAME:
				 OsdFuncClearOsd(ROW(5), COL(22), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1));
				 OsdPropPutString(ROW(5), COL(22), _PFONT_PAGE_2, _STRING_COLOR_MOVIE, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());
				 break;
			 case _COLOREFFECT_MOVIE:
				 OsdFuncClearOsd(ROW(5), COL(22), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1));
				 OsdPropPutString(ROW(5), COL(22), _PFONT_PAGE_2, _STRING_COLOR_PHOTO, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());
				 break;
			 case _COLOREFFECT_PHOTO:
				 OsdFuncClearOsd(ROW(5), COL(22), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1));
				 OsdPropPutString(ROW(5), COL(22), _PFONT_PAGE_2, _STRING_COLOR_GAME, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());
				 break;
			//case _COLOREFFECT_USER:
			//	OsdFuncClearOsd(ROW(5), COL(22), WIDTH(10), HEIGHT(1));
			//	OsdPropPutString(ROW(5), COL(22), _PFONT_PAGE_2, _STRING_COLOR_USER, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());
			//	break;
//Eric_020180307 : Delete
//    			case _COLOREFFECT_FPS:
//    				OsdFuncClearOsd(ROW(5), COL(22), WIDTH(10), HEIGHT(1));
//    				OsdPropPutString(ROW(5), COL(22), _PFONT_PAGE_2, _STRING_PICTURE_RTS, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());
//    				break;
//    			case _COLOREFFECT_RTS:
//    				OsdFuncClearOsd(ROW(5), COL(22), WIDTH(10), HEIGHT(1));
//    				OsdPropPutString(ROW(5), COL(22), _PFONT_PAGE_2, _STRING_PICTURE_USER, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());
//    				break;
			  default:
				  break;
		 }
		   
     #if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
			  UserAdjustColorEffectMode();
     #endif
			 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		 break;
 
		 case _MENU_KEY_MESSAGE:
			 OsdDispDisableOsd();
		 break;
 
		 default:
			 break; 				  
	 }
 
 }
#endif


 void MenuSetupInputAdjust(void)
 {
	 switch (GET_KEYMESSAGE())
	 {
	 case _SELECT_KEY_MESSAGE:
		 if (GET_OSD_DP_VERSION_HOTKEY_DISP() == _OFF)
		 {

			 if (g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
			 {

				 switch (GET_OSD_INPUT_PORT_OSD_ITEM())
				 {
				 case _OSD_INPUT_AUTO: // auto
					 SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
					 {
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }
#if(_DP_MST_SUPPORT == _ON)
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif                            
					 break;
#if(_A0_INPUT_PORT_TYPE !=_A0_NO_PORT) 
				 case _OSD_INPUT_A0: // A0
					 SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_A0);
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_A0_INPUT_PORT);

					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif                            


					 break;
#endif

#if(_D0_INPUT_PORT_TYPE !=_D0_NO_PORT) 
				 case _OSD_INPUT_D0: // D0
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   0000000", 0);
#endif					 
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D0_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif
					 break;

#endif


#if(_D1_INPUT_PORT_TYPE !=_D1_NO_PORT) 
				 case _OSD_INPUT_D1:	//D1
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   1111111", 0);
#endif	
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D1_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif
					 break;

#endif

#if(_D2_INPUT_PORT_TYPE !=_D2_NO_PORT) 
				 case _OSD_INPUT_D2:	//D2
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   22222", 0);
#endif				
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D2_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif
					 break;

#endif

#if(_D3_INPUT_PORT_TYPE !=_D3_NO_PORT) 
				 case _OSD_INPUT_D3:	//D3
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   333333", 0);
#endif	
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D3_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)

					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
					 break;
#endif

#if(_D4_INPUT_PORT_TYPE !=_D4_NO_PORT) 
				 case _OSD_INPUT_D4:	//D4
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D4_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)

					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif

					 break;

#endif

#if(_D5_INPUT_PORT_TYPE !=_D5_NO_PORT) 
				 case _OSD_INPUT_D5:	//D5
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D5_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif


					 break;
#endif

#if(_D6_INPUT_PORT_TYPE !=_D6_NO_PORT) 
				 case _OSD_INPUT_D6:	//D6
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D6_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif

					 break;
#endif

				 default:
					 break;
				 }
			 }
			 else
			 {
				 if (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)
				 {
					 //	 SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
				 }
				 else if ((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
				 {
					 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
				 }
				 else
				 {
					 OsdDispDisableOsd();
				 }
			 }
			 SET_OSD_STATE(_MENU_NONE);
		 }

		 break;

	 case _DOWN_KEY_MESSAGE:
	 case _RIGHT_KEY_MESSAGE:
	 {
		 CLR_KEYREPEATENABLE();
		 g_usItemNum = GET_OSD_INPUT_PORT_OSD_ITEM();
		 if (g_usItemNum == _OSD_INPUT_AMOUNT)
		 {
			 g_usItemNum = _OSD_INPUT_AUTO;
		 }
		 else
		 {
			 g_usItemNum++;
		 }

		 SET_OSD_INPUT_PORT_OSD_ITEM(g_usItemNum);
		 DebugMessageSystem("SET_OSD_INPUT_PORT_OSD_ITEM", g_usItemNum);
		 if (g_usItemNum == _OSD_INPUT_AUTO) // 
		 {
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usItemNum)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 }
		 else // // EnumSourceSearchPort 과 EnumOSDInputPortDef 값이 같게 합니다.
		 {
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * (g_usItemNum))), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 }
		 if ((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
		 {
			 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
		 }
		 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

	 }
	 break;


	 case _UP_KEY_MESSAGE:
	 case _LEFT_KEY_MESSAGE:
	 {
		 CLR_KEYREPEATENABLE();
		 g_usItemNum = GET_OSD_INPUT_PORT_OSD_ITEM();
		 if (g_usItemNum == _OSD_INPUT_AUTO)
		 {
			 g_usItemNum = _OSD_INPUT_AMOUNT;
		 }
		 else
		 {
			 g_usItemNum--;
		 }

		 SET_OSD_INPUT_PORT_OSD_ITEM(g_usItemNum);
		 if (g_usItemNum == _OSD_INPUT_AUTO)
		 {
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * g_usItemNum)), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 }
		 else // // EnumSourceSearchPort 과 EnumOSDInputPortDef 값이 같게 합니다.
		 {
			 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * (g_usItemNum))), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		 }
		 if ((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
		 {
			 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
		 }
		 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	 }
	 break;

	 case _MENU_KEY_MESSAGE:
		 if (g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
		 {
			 SET_OSD_INPUT_PORT_OSD_ITEM(g_usBackupValue);
			 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		 }

		 if (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)
		 {
			 //				 SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
		 }
		 else if ((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
		 {
			 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
		 }
		 else
		 {
			 SET_OSD_STATE(_MENU_SETUP_INPUT);
			 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			 COsdShowChooseSetupText(_STRING_SETUP_INPUT);
		 }

		 break;

	 default:
		 break;
	 }
 }


void MenuSetupAudioMuteonoff(void)
{
   switch(GET_KEYMESSAGE())
   {
	   case _SELECT_KEY_MESSAGE:
		   if (g_usBackupValue != GET_OSD_VOLUME_MUTE())
		   {
			   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		   }
		   SET_OSD_STATE(_MENU_SETUP_AUDIOMUTE);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		   COsdShowChooseSetupText(_STRING_SETUP_AUDIOMUTE);
	  break;
		   
        case _DOWN_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:	 
        case _UP_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
		   CLR_KEYREPEATENABLE();
		   SET_OSD_VOLUME_MUTE(OsdDisplayDetOverRange(GET_OSD_VOLUME_MUTE() , _ON, _OFF, _ON, _OFF));
		   g_usAdjustValue = GET_OSD_VOLUME_MUTE();
		   OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3* g_usAdjustValue)),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
#if(_AUDIO_SUPPORT == _ON)
		   UserAdjustAudioMuteSwitch();
#endif
		   break;

	   case _MENU_KEY_MESSAGE:
		   if (g_usBackupValue != GET_OSD_VOLUME_MUTE())
		   {
			   g_usAdjustValue = g_usBackupValue;
			   SET_OSD_VOLUME_MUTE(g_usAdjustValue);
			   UserAdjustAudioMuteSwitch();
		   }
		   SET_OSD_STATE(_MENU_SETUP_AUDIOMUTE);
		   ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		   COsdShowChooseSetupText(_STRING_SETUP_AUDIOMUTE);
		   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
	   break;

	   default:
		   break;					
   }
}
					   
//MenuAudioAdjust

void MenuSetupAudioAdjust(void)
{
   switch(GET_KEYMESSAGE())
   {
	   case _SELECT_KEY_MESSAGE:
		   if (g_usBackupValue != GET_OSD_VOLUME())
		   {
			   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		   }
		   SET_OSD_STATE(_MENU_SETUP_AUDIO);
		   OsdDispMainMenukeySlideAndOption(_MENU_AUDIO_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_AUDIO_ADJUST, _SLIDER_3,_ON,0);
		  
		   break;
		   
	   case _DOWN_KEY_MESSAGE:
	   case _RIGHT_KEY_MESSAGE:
	   case _UP_KEY_MESSAGE:
	   case _LEFT_KEY_MESSAGE:

	 OsdDispMainMenukeySlideAndOption(_MENU_AUDIO_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_AUDIO_ADJUST, _SLIDER_3,_OFF,0);
	  if((GET_OSD_VOLUME_MUTE() == _ON) && (g_usAdjustValue == GET_OSD_VOLUME()))
		   {
			   SET_OSD_VOLUME_MUTE(_OFF);
		   }			
#if(_AUDIO_SUPPORT == _ON)
		   UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
	  
		   
		   break;

	   case _MENU_KEY_MESSAGE:
		   if (g_usBackupValue != GET_OSD_VOLUME())
		   {
			   g_usAdjustValue = g_usBackupValue;
			   SET_OSD_VOLUME(g_usAdjustValue);
			   if ((GET_OSD_VOLUME_MUTE() == _ON) && (g_usBackupValue == GET_OSD_VOLUME()))
			   {
				   SET_OSD_VOLUME_MUTE(_OFF);
			   }
#if(_AUDIO_SUPPORT == _ON)
			   UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
		   }
		   SET_OSD_STATE(_MENU_SETUP_AUDIO);
		   OsdDispMainMenukeySlideAndOption(_MENU_AUDIO_ADJUST- _MENU_PICTURE_BACKLIGHT_ADJUST,_MENU_AUDIO_ADJUST, _SLIDER_3,_ON,0);
		   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		   break;

	   default:
		   break;					
   }
}
//MenuAudioMuteonoff

void MenuSetupDPFormatAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_DP_D0_VERSION())
		{
			if ((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && ((GET_OSD_DP_MST() == _MST_D0) || (GET_OSD_DP_MST() == _MST_D1)))
			{
				SET_OSD_DP_MST(_MST_OFF);
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
			ScalerDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
		}
		
		SET_OSD_STATE(_MENU_SETUP_DP_FORMAT);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseSetupText(_STRING_DP_FORMAT);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_DP_D0_VERSION(OsdDisplayDetOverRange(GET_OSD_DP_D0_VERSION(), _DP_VER_1_DOT_2, _DP_VER_1_DOT_1, _ON, _OFF));
		SET_OSD_DP_D1_VERSION(GET_OSD_DP_D0_VERSION());
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_DP_D0_VERSION())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_DP_D0_VERSION())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_DP_D0_VERSION(g_usAdjustValue);
			SET_OSD_DP_D1_VERSION(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_SETUP_DP_FORMAT);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_DP_FORMAT);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
void MenuSetupDPMSTAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_DP_MST())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if(_DP_MST_SUPPORT == _ON)

			ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif	
		}
		SET_OSD_STATE(_MENU_SETUP_DP_MST);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseSetupText(_STRING_DP_MST);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		if (SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT)
		{
			CLR_KEYREPEATENABLE();
			SET_OSD_DP_MST(OsdDisplayDetOverRange(GET_OSD_DP_MST(), _MST_D1, _MST_OFF, _ON, _OFF));
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_DP_MST())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		}
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_DP_MST())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_DP_MST(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_SETUP_DP_MST);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_DP_MST);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
void MenuSetupCloneModeAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_CLONE_MODE())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

		}
		SET_OSD_STATE(_MENU_SETUP_CLONE_MODE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseSetupText(_STRING_CLONE);
		COsdShowPageText(_MENU_SETUP);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_CLONE_MODE(OsdDisplayDetOverRange(GET_OSD_CLONE_MODE(), _OSD_CLONE_ON, _OSD_CLONE_OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_CLONE_MODE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_CLONE_MODE())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_CLONE_MODE(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_SETUP_CLONE_MODE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseSetupText(_STRING_CLONE);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}


void MenuOthersDisplaySizeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if(_ASPECT_RATIO_SUPPORT == _ON)
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
			}

			SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
		    ScalerOsdWindowDisable(_OSD_WINDOW_4_3);            
			COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
			break;
            
        case _DOWN_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
        case _UP_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
               SET_OSD_ASPECT_RATIO_TYPE(OsdDisplayDetOverRange(GET_OSD_ASPECT_RATIO_TYPE() ,_OSD_ASPECT_RATIO_AMOUNT,_OSD_ASPECT_RATIO_FULL, _ON, _OFF));
               OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_ASPECT_RATIO_TYPE())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
#if(_ASPECT_RATIO_SUPPORT == _ON)
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
			}
            SET_OSD_STATE(_MENU_OTHERS_DISPLAY_SIZE);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_SIZE);
            break;

        default:
            break;                   
    }
}

void MenuOthersDisplayRotateAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_DISP_ROTATE())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
		}
		SET_OSD_STATE(_MENU_OTHERS_DISPLAY_ROTATE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_ROTATE);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_DISP_ROTATE(OsdDisplayDetOverRange(GET_OSD_DISP_ROTATE(), (_DISP_ROTATE_AMOUNT - 1), _DISP_ROTATE_0, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_DISP_ROTATE())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_DISP_ROTATE())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_DISP_ROTATE(g_usAdjustValue);
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
		}
		SET_OSD_STATE(_MENU_OTHERS_DISPLAY_ROTATE);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_DISPLAY_ROTATE);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
void MenuOthersLowBlueLightAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_LOWBLUELIGHT_STATUS())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}
            SET_OSD_STATE(_MENU_OTHERS_LOW_BLUE_LIGHT);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowChooseOtherText(_STRING_OTHER_LOW_BLUE);
            break;
            
		case _DOWN_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:
		case _UP_KEY_MESSAGE:
		case _LEFT_KEY_MESSAGE:
			CLR_KEYREPEATENABLE();
			SET_OSD_LOWBLUELIGHT_STATUS(OsdDisplayDetOverRange(GET_OSD_LOWBLUELIGHT_STATUS() , _LOWBLUE_STRONGEST, _LOWBLUE_OFF, _ON, _OFF));
			OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_LOWBLUELIGHT_STATUS())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
            UserAdjustColorLowBlueLight(GET_OSD_LOWBLUELIGHT_STATUS());
            break;

        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_LOWBLUELIGHT_STATUS())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_LOWBLUELIGHT_STATUS(g_usAdjustValue);
				UserAdjustColorLowBlueLight(GET_OSD_LOWBLUELIGHT_STATUS());
			}
			SET_OSD_STATE(_MENU_OTHERS_LOW_BLUE_LIGHT);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowChooseOtherText(_STRING_OTHER_LOW_BLUE);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            break;

        default:
            break;
    }
}
#endif

#if(_OD_SUPPORT == _ON)        	
void MenuOthersOverDriveAdjust(void)
{
	
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_OD_STATUS())
			{
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			}

            SET_OSD_STATE(_MENU_OTHERS_OD);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;



        case _DOWN_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:        
        case _UP_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
			CLR_KEYREPEATENABLE();
	  SET_OSD_OD_STATUS(OsdDisplayDetOverRange(GET_OSD_OD_STATUS() , _ON, _OFF, _ON, _OFF));
          OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_OD_STATUS())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
    #if(_OD_SUPPORT == _ON)    
            ScalerODEnable(GET_OSD_OD_STATUS());
	        ScalerTimerWaitForEvent(_EVENT_DVS);

    #endif
    
       break;
        case _MENU_KEY_MESSAGE:
			if (g_usBackupValue != GET_OSD_OD_STATUS())
			{
				g_usAdjustValue = g_usBackupValue;
				SET_OSD_OD_STATUS(g_usAdjustValue);
#if(_OD_SUPPORT == _ON)    
				ScalerODEnable(GET_OSD_OD_STATUS());
				ScalerTimerWaitForEvent(_EVENT_DVS);

#endif
			}
            SET_OSD_STATE(_MENU_OTHERS_OD);
			ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
			COsdShowChooseOtherText(_STRING_OTHER_OVER_DRIVE);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			break;

        default:
            break;                   
    }
}

#endif

#if (_ENABLE_VIDEO_WALL == _ON)
void MenuOthersVideoWallAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_VIDEO_WALL_STATUS())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			if (GET_OSD_VIDEO_WALL_STATUS() == _ON)
			{
				SET_OSD_CLONE_MODE(_OSD_CLONE_ON);
			}
		}

		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_VIDEO_WALL_STATUS(OsdDisplayDetOverRange(GET_OSD_VIDEO_WALL_STATUS(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_VIDEO_WALL_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_VIDEO_WALL_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_VIDEO_WALL_STATUS(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_VIDEO_WALL);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuOthersVideoWall_DispNumAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:

		if (g_usBackupValue != GET_OSD_VIDEO_WALL_DISP_NUM())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			if (GET_OSD_VIDEO_WALL_STATUS() == _ON)
			{
				SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			}
		}
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_DISP_NUM);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ, _SLIDER_0, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_DISP_NUM_ADJ, _SLIDER_0, _OFF, 0);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_VIDEO_WALL_DISP_NUM())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_VIDEO_WALL_DISP_NUM(g_usAdjustValue);
		}
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_DISP_NUM);
		COsdShowChoosePictureText(_STRING_OTHER_DISPLAY_NUMBER);
		break;

	default:
		break;
	}
}

void MenuOthersVideoWall_HNumAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:

		if (g_usBackupValue != GET_OSD_VIDEO_WALL_H_NUM())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			if (GET_OSD_VIDEO_WALL_DISP_NUM() > GetVideoWallDisplayNumber())
			{
				SET_OSD_VIDEO_WALL_DISP_NUM(GetVideoWallDisplayNumber());
				COsdShowChoosePictureText(_STRING_OTHER_DISPLAY_NUMBER);
				SET_OSD_VIDEO_WALL_RS232ID(GetVideoWallDisplayNumber());
				COsdShowChoosePictureText(_STRING_OTHER_RS232_ID);
			}
			if (GET_OSD_VIDEO_WALL_STATUS() == _ON)
			{
				SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			}
		}
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_HNUM);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_HNUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_HNUM_ADJ, _SLIDER_1, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_HNUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_HNUM_ADJ, _SLIDER_1, _OFF, 0);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_VIDEO_WALL_H_NUM())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_VIDEO_WALL_H_NUM(g_usAdjustValue);
		}
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_HNUM);
		COsdShowChoosePictureText(_STRING_OTHER_HORIZONTAL_NUMBER);
		break;

	default:
		break;
	}
}

void MenuOthersVideoWall_VNumAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:

		if (g_usBackupValue != GET_OSD_VIDEO_WALL_V_NUM())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			if (GET_OSD_VIDEO_WALL_DISP_NUM() > GetVideoWallDisplayNumber())
			{
				SET_OSD_VIDEO_WALL_DISP_NUM(GetVideoWallDisplayNumber());
				COsdShowChoosePictureText(_STRING_OTHER_DISPLAY_NUMBER);
				SET_OSD_VIDEO_WALL_RS232ID(GetVideoWallDisplayNumber());
				COsdShowChoosePictureText(_STRING_OTHER_RS232_ID);
			}
			if (GET_OSD_VIDEO_WALL_STATUS() == _ON)
			{
				SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
			}
		}
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_VNUM);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_VNUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_VNUM_ADJ, _SLIDER_2, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_VNUM_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_VNUM_ADJ, _SLIDER_2, _OFF, 0);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_VIDEO_WALL_V_NUM())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_VIDEO_WALL_V_NUM(g_usAdjustValue);
		}
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_VNUM);
		COsdShowChoosePictureText(_STRING_OTHER_VERTICAL_NUMBER);
		break;

	default:
		break;
	}
}

void MenuOthersVideoWall_RS232IdAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:

		if (g_usBackupValue != GET_OSD_VIDEO_WALL_RS232ID())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_RS232ID);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ, _SLIDER_3, _ON, 0);
		break;
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_VIDEO_WALL_RS232ID_ADJ, _SLIDER_3, _OFF, 0);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_VIDEO_WALL_RS232ID())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_VIDEO_WALL_RS232ID(g_usAdjustValue);
		}
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		SET_OSD_STATE(_MENU_OTHERS_VIDEO_WALL_RS232ID);
		COsdShowChoosePictureText(_STRING_OTHER_RS232_ID);
		break;

	default:
		break;
	}
}
#endif

#if (_ENABLE_LIGHT_SENSOR == _ON)
void MenuOthersLightSensorAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_LIGHT_SENSOR_STATUS())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}

		SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_LIGHT_SENSOR_STATUS(OsdDisplayDetOverRange(GET_OSD_LIGHT_SENSOR_STATUS(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_LIGHT_SENSOR_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_LIGHT_SENSOR_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_LIGHT_SENSOR_STATUS(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_OTHERS_LIGHT_SENSOR);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_LIGHT_SENSOR);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
void MenuOthersFanAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_STATUS())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			ApplyFanControl(_TRUE);
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_FAN);
		COsdShowPageText(_MENU_OTHERS_FAN_CONTROLS);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_FAN_STATUS(OsdDisplayDetOverRange(GET_OSD_FAN_STATUS(), _AUTO, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_FAN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_FAN_STATUS(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_FAN);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuOthersFanPWM1Adj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM1())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM1);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM1_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM1_ADJ, _SLIDER_3, _ON, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:

		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM1_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM1_ADJ, _SLIDER_3, _OFF, 0);
		SetFan1(GET_OSD_FAN_PWM1());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM1())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_FAN_PWM1(g_usAdjustValue);
			SetFan1(GET_OSD_FAN_PWM1());
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM1);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM1_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM1_ADJ, _SLIDER_3, _ON, 0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuOthersFanPWM2Adj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM2())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM2);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM2_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM2_ADJ, _SLIDER_3, _ON, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:

		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM2_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM2_ADJ, _SLIDER_3, _OFF, 0);
		SetFan2(GET_OSD_FAN_PWM2());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM2())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_FAN_PWM2(g_usAdjustValue);
			SetFan2(GET_OSD_FAN_PWM2());
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM2);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM2_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM2_ADJ, _SLIDER_3, _ON, 0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuOthersFanPWM3Adj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM3())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM3);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM3_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM3_ADJ, _SLIDER_3, _ON, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:

		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM3_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM3_ADJ, _SLIDER_3, _OFF, 0);
		SetFan3(GET_OSD_FAN_PWM3());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM3())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_FAN_PWM3(g_usAdjustValue);
			SetFan3(GET_OSD_FAN_PWM3());
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM3);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM3_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM3_ADJ, _SLIDER_3, _ON, 0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuOthersFanPWM4Adj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM4())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM4);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM4_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM4_ADJ, _SLIDER_3, _ON, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:

		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM4_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM4_ADJ, _SLIDER_3, _OFF, 0);
		SetFan4(GET_OSD_FAN_PWM4());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_FAN_PWM4())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_FAN_PWM4(g_usAdjustValue);
			SetFan4(GET_OSD_FAN_PWM4());
		}
		SET_OSD_STATE(_MENU_OTHERS_FAN_PWM4);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_FAN_PWM4_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_FAN_PWM4_ADJ, _SLIDER_3, _ON, 0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuOthersShutDownAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SHUTDOWN_STATUS())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}

		SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN);
		COsdShowPageText(_MENU_OTHERS_FAN_CONTROLS);
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(_OSD_NUMBER_12_ROW), COL(_OSD_NUMBER_1_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_2), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_SHUTDOWN_STATUS(OsdDisplayDetOverRange(GET_OSD_SHUTDOWN_STATUS(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SHUTDOWN_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SHUTDOWN_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_SHUTDOWN_STATUS(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_SHUTDOWN);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuOthersShutDownTempAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SHUTDOWN_TEMP())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN_TEMP);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_SHUTDOWN_TEMP_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_SHUTDOWN_TEMP_ADJ, _SLIDER_3, _ON, 0);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_SHUTDOWN_TEMP_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_SHUTDOWN_TEMP_ADJ, _SLIDER_3, _OFF, 0);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SHUTDOWN_TEMP())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_SHUTDOWN_TEMP(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_OTHERS_SHUTDOWN_TEMP);
		OsdDispMainMenukeySlideAndOption(_MENU_OTHERS_SHUTDOWN_TEMP_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_OTHERS_SHUTDOWN_TEMP_ADJ, _SLIDER_3, _ON, 0);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
#endif

#if (_ENABLE_SELF_CHECK == _ON)
void MenuOthersSelfCheckAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SELF_CHECK_STATUS())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_SELF_CHECK_STATUS(OsdDisplayDetOverRange(GET_OSD_SELF_CHECK_STATUS(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_SELF_CHECK_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_SELF_CHECK_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_SELF_CHECK_STATUS(g_usAdjustValue);
	}
		SET_OSD_STATE(_MENU_OTHERS_SELF_CHECK);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_SELF_CHECK);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
#endif

#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
void MenuOthersALCWAdjust(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_ALCW())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}

		SET_OSD_STATE(_MENU_OTHERS_ALCW);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_ALCW(OsdDisplayDetOverRange(GET_OSD_ALCW(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_ALCW())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		ENABLE_ALCW(GET_OSD_ALCW());
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_OD_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_ALCW(g_usAdjustValue);
			ENABLE_ALCW(GET_OSD_ALCW());
		}
		SET_OSD_STATE(_MENU_OTHERS_ALCW);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseOtherText(_STRING_OTHER_ALCW_SETTING);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
#endif


void MenuOthersFreeSyncAdjust(void)
{
	
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHERS_FREE_SYNC);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowChooseOtherText(_STRING_OTHER_FREESYNC);

				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
               #if(_FREESYNC_SUPPORT == _ON)
                               ScalerSyncSetFREESYNCSupport(GET_OSD_FREE_SYNC_STATUS());
                #endif
				
        break;



        case _DOWN_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE: 
            
        case _UP_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE: 
			CLR_KEYREPEATENABLE();
	        SET_OSD_FREE_SYNC_STATUS(OsdDisplayDetOverRange(GET_OSD_FREE_SYNC_STATUS() , _ON, _OFF, _ON, _OFF));
          OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW+(3*GET_OSD_FREE_SYNC_STATUS())),  COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);

//Eric_20180307 : Delete
//    	#if((_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//             	if(GET_OSD_FREE_SYNC_STATUS() == _ON)
//                       {
//                          UserCommonRestoreEmbeddedEDIDData();
//             	  }
//             	else
//                       {
//                          UserCommonRestoreEmbeddedEDIDDataNoFreesync();
//             	   }
//    	
//            #endif
//    		       OsdDispEepromWriteProtectOff(); // tdy add for ostar osd 20170306 //

       break;




        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHERS_FREE_SYNC);
		 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		 COsdShowChooseOtherText(_STRING_OTHER_FREESYNC);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
               #if(_FREESYNC_SUPPORT == _ON)
                               ScalerSyncSetFREESYNCSupport(GET_OSD_FREE_SYNC_STATUS());
                #endif
				
        break;

        default:
            break;                   
    }
}

void MenuServiceBacklightPwmResAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_BACKLIGHT_PWM_RES())
		{
			if (GET_OSD_BACKLIGHT_PWM_RES() == _OFF)
			{
				SET_BACKLIGHT_MAX(_PWM_8BIT - 1);
				SET_OSD_BACKLIGHT(GET_OSD_BACKLIGHT() / 16);
			}
			else
			{
				SET_BACKLIGHT_MAX(_PWM_12BIT - 1);
				SET_OSD_BACKLIGHT(GET_OSD_BACKLIGHT() * 16);
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			PWM_SETTINGS();
			PCB_PWM_SETTING();
		}
		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_PWM_RES);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_BACKLIGHT_PWM_RES(OsdDisplayDetOverRange(GET_OSD_BACKLIGHT_PWM_RES(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_BACKLIGHT_PWM_RES())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);



		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_BACKLIGHT_PWM_RES())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_BACKLIGHT_PWM_RES(g_usAdjustValue);
			SET_BACKLIGHT_MAX(GET_OSD_BACKLIGHT_PWM_RES() == _OFF ? _PWM_8BIT - 1 : _PWM_12BIT - 1);
		}
		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_PWM_RES);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_PWM_RES);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuServiceBacklightControlAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_BACKLIGHT_CONTROL())
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}

		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_CONTROL);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_CONTROL);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_BACKLIGHT_CONTROL(OsdDisplayDetOverRange(GET_OSD_BACKLIGHT_CONTROL(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_BACKLIGHT_CONTROL())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_BACKLIGHT_CONTROL())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_BACKLIGHT_CONTROL(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_CONTROL);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_CONTROL);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

#if(_PIXEL_SHIFT_SUPPORT == _ON)
void MenuServicePixelShiftAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_PIXEL_SHIFT_STATUS())
		{
			if (GET_OSD_PIXEL_SHIFT_STATUS() == _ON)
			{
				pixShiftTime = 0;
				if (setShift == 8) setShift = 0;
				UserAdjustPixelShifting(setShift++);
				ScalerTimerActiveTimerEvent(MIN(1), _USER_TIMER_EVENT_PIXEL_SHIFT);
			}
			else
			{
				pixShiftTime = 0;
				setShift = 8; // 
				UserAdjustPixelShifting(setShift); // Pixel Shift OFF
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PIXEL_SHIFT);
			}
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}

		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_PIXEL_SHIFT_STATUS(OsdDisplayDetOverRange(GET_OSD_PIXEL_SHIFT_STATUS(), _ON, _OFF, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_PIXEL_SHIFT_STATUS())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_PIXEL_SHIFT_STATUS())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_PIXEL_SHIFT_STATUS(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}

void MenuServicePixelShiftTimeAdj(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_PIXEL_SHIFT_TIME())
		{
			pixShiftTime = 0;
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		}
		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT_TIME);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT_TIME);
		break;

	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _UP_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		CLR_KEYREPEATENABLE();
		SET_OSD_PIXEL_SHIFT_TIME(OsdDisplayDetOverRange(GET_OSD_PIXEL_SHIFT_TIME(), PIXEL_SHIFT_20MIN, PIXEL_SHIFT_5MIN, _ON, _OFF));
		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_PIXEL_SHIFT_TIME())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
		break;

	case _MENU_KEY_MESSAGE:
		if (g_usBackupValue != GET_OSD_PIXEL_SHIFT_TIME())
		{
			g_usAdjustValue = g_usBackupValue;
			SET_OSD_PIXEL_SHIFT_TIME(g_usAdjustValue);
		}
		SET_OSD_STATE(_MENU_SERVICE_PIXEL_SHIFT_TIME);
		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
		COsdShowChooseServiceText(_STRING_SERVICE_PIXEL_SHIFT_TIME);
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
		break;

	default:
		break;
	}
}
#endif

//void MenuServiceBacklightInvertAdj(void)
//{
//	switch (GET_KEYMESSAGE())
//	{
//	case _SELECT_KEY_MESSAGE:
//		if (g_usBackupValue != GET_OSD_BACKLIGHT_INVERT())
//		{
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//		}
//
//		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
//		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		COsdShowChooseServiceText(_STRING_SERVICE_INVERT);
//		break;
//
//	case _DOWN_KEY_MESSAGE:
//	case _RIGHT_KEY_MESSAGE:
//	case _UP_KEY_MESSAGE:
//	case _LEFT_KEY_MESSAGE:
//		CLR_KEYREPEATENABLE();
//		SET_OSD_BACKLIGHT_INVERT(OsdDisplayDetOverRange(GET_OSD_BACKLIGHT_INVERT(), _ON, _OFF, _ON, _OFF));
//		OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(_OSD_NUMBER_1_ROW + (3 * GET_OSD_BACKLIGHT_INVERT())), COL(_OSD_NUMBER_2_COL), WIDTH(_OSD_WINDOW_CHOOSE_WIDTH_1), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//		break;
//
//	case _MENU_KEY_MESSAGE:
//		if (g_usBackupValue != GET_OSD_BACKLIGHT_INVERT())
//		{
//			g_usAdjustValue = g_usBackupValue;
//			SET_OSD_BACKLIGHT_INVERT(g_usAdjustValue);
//		}
//		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_INVERT);
//		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		COsdShowChooseServiceText(_STRING_SERVICE_INVERT);
//		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//		break;
//
//	default:
//		break;
//	}
//}
//
//void MenuServiceBacklightFreqAdj(void)
//{
//	switch (GET_KEYMESSAGE())
//	{
//	case _SELECT_KEY_MESSAGE:
//		if (g_usBackupValue != GET_OSD_BACKLIGHT_FREQ())
//		{
//			//backlight is OSDUSER data
//			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//			PWM_SETTINGS();
//			PCB_PWM_SETTING();
//		}
//		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
//		OsdDispMainMenukeySlideAndOption(_MENU_SERVICE_BACKLIGHT_FREQ_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_SERVICE_BACKLIGHT_FREQ_ADJ, _SLIDER_0, _ON, 0);
//		break;
//	case _DOWN_KEY_MESSAGE:
//	case _RIGHT_KEY_MESSAGE:
//	case _UP_KEY_MESSAGE:
//	case _LEFT_KEY_MESSAGE:
//		OsdDispMainMenukeySlideAndOption(_MENU_SERVICE_BACKLIGHT_FREQ_ADJ - _MENU_PICTURE_BACKLIGHT_ADJUST, _MENU_SERVICE_BACKLIGHT_FREQ_ADJ, _SLIDER_0, _OFF, 0);
//		break;
//
//	case _MENU_KEY_MESSAGE:
//		if (g_usBackupValue != GET_OSD_BACKLIGHT_FREQ())
//		{
//			g_usAdjustValue = g_usBackupValue;
//			SET_OSD_BACKLIGHT_FREQ(g_usAdjustValue);
//		}
//		//brightness is BRICON data
//		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//		SET_OSD_STATE(_MENU_SERVICE_BACKLIGHT_FREQ);
//		ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
//		COsdShowChooseServiceText(_STRING_SERVICE_FREQ);
//		break;
//
//	default:
//		break;
//	}
//}

// void MenuHotInput(void)
// {
//	 BYTE ucTest = 0;
// 
//	 g_ucFontPointer0 = _OSD_PAGE_0_START;
//	 g_ucFontPointer1 = _OSD_PAGE_1_START;
//	 g_ucFontPointer2 = _OSD_PAGE_2_START;
// 
//	 if(ucTest == 1)
//	 {
//	  //   ScalerDDomainPatternGenAdjustColor(0, 0, 0);
// 
//	  //   OsdDispDetOverRange(0, 0, 0, 0);
// 
//	   //  OSTARFactoryPanelUsedTimer();
//	   //  OsdFontPut2BitTable(0, 0, tOSD_iREALTEK, 0, 0, 0, 0);
//		 
// // 	   OsdWindowDrawingHighlight(0, 0, 0, 0, 0, 0, 0, 0);
// // 	   OsdFuncChangeIconColor1Bit(0, 0, 0 , 0, 0);
// 
//		ScalerOsdDataPort(0);
// 
// //#if(_DIGITAL_PORT_SUPPORT == _ON)
//		// ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort());
// //#endif
// 
//	 }
// 
//	 OsdFuncDisableOsd();
// 
//	 OsdFuncApplyMap(WIDTH(_OSD_MENU_HOT_INPUT_WIDTH), HEIGHT(_OSD_MENU_HOT_INPUT_HEIGHT), COLOR(_CP_BG, _CP_BG));
// 
// //20140304 Abel
//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//	 ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MENU_HOT_INPUT_HEIGHT), _DISABLE, 0, _ENABLE);
//#endif
// 
//	 //OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
//	 OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
// 
//	 // Adjust Color Palette
//	 OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
//	 
//	 OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);	
//	 OsdFuncTransparency(0); 
//	 // Load Font & Icon
//	 OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
// 
//	 OsdFontVLCLoadFont(_FONT1_GLOBAL);
//	 //OsdFontVLCLoadFont(_FONT2_ICON_MENU);
//	  OsdFontVLCLoadFont(_LEFT_MENU_TIME_ICON);
//	  OsdFontVLCLoadFont(_LEFT_MENU_AIM_ICON);
//	  OsdFontVLCLoadFont(_FOUR_CORNER);
// 
//	// Background window
//	//20140210 Abel Modify
//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//	 if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)||(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//	 {
// 
//		 OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT( (g_ucOsdHeight/2)-1), _CP_GREEN_119);
//		 OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW( (g_ucOsdHeight/2)-1), COL(0), WIDTH(g_ucOsdWidth), HEIGHT((g_ucOsdHeight/2)+1), _CP_GRAY_1 );//_CP_LIGHTBLUE
//	  }
//	 else
//#endif
//	 {
//		if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
//		{
//			OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(1), WIDTH(g_ucOsdWidth-2), HEIGHT((g_ucOsdHeight-1)), _CP_BLUE_65 );
//		}	 
//		else 
//		{
//			OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(1), COL(1), WIDTH(g_ucOsdWidth-2), HEIGHT((g_ucOsdHeight-1)), _CP_BLUE_65 );
//		}
//	OsdFontPut1FuncTableForm(0, 0, _LEFT_CORNER_0,g_ucOsdWidth -2,g_ucOsdHeight-2,_CP_BLUE_65,_CP_BG,_QUADRANGLE_WINDOW_0);
//
//	COsdShowPageInputText();
//
//
//
//	  g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
//	 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(2), COL(3+(11*GET_OSD_INPUT_PORT_OSD_ITEM())), WIDTH(8), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
//
//   //background    
//	 }
// 
//	 
//	 
// 
//	 OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
// 
// 
// 
//	 // Osd Enable
//	 ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//	 OsdFuncEnableOsd();
// 
// }

 void MenuHotInputAdjust(void)
 {
	 switch(GET_KEYMESSAGE())
	 {
		 case _SELECT_KEY_MESSAGE:
  if(GET_OSD_DP_VERSION_HOTKEY_DISP() == _OFF)
			 {
 
 
				 if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
				 {		 
 
					 switch(GET_OSD_INPUT_PORT_OSD_ITEM())
					 {
						 case _OSD_INPUT_AUTO: // auto
							 SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
							 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
 
							 if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
							 {
								 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
								 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
							 }	   
#if(_DP_MST_SUPPORT == _ON)
							 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
							 RTDNVRamSaveOSDData();  
#endif                            
							 break;
#if(_A0_INPUT_PORT_TYPE !=_A0_NO_PORT) 
			 case _OSD_INPUT_A0: // A0
						 SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_A0);
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
 
#if(_DP_MST_SUPPORT == _ON)
							 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
							 RTDNVRamSaveOSDData();  
#endif                            
 
									  
							 break;
#endif
 
#if(_D0_INPUT_PORT_TYPE !=_D0_NO_PORT) 
				 case _OSD_INPUT_D0: // D0
                                 #if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
                                         g_usVolumePowerForPopo= _ON;
                                 	  PCB_AMP_MUTE(_AMP_MUTE_ON);
                                        DebugMessageAudio("PCB_AMP_MUTE(D2Port)   0000000", 0);
                                 #endif					
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
	 
#if(_DP_MST_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
					 if(UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();					   
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					RTDNVRamSaveOSDData();
#endif
#endif
								 break;
	 
#endif
 
 
#if(_D1_INPUT_PORT_TYPE !=_D1_NO_PORT) 
			  case _OSD_INPUT_D1:	//D1
                                #if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
                                       g_usVolumePowerForPopo= _ON;
                                       PCB_AMP_MUTE(_AMP_MUTE_ON);
                                      DebugMessageAudio("PCB_AMP_MUTE(D2Port)   1111111", 0);
                               #endif	

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
 
#if(_DP_MST_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
				 if(UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
				 {
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
					 RTDNVRamSaveOSDData();					   
				 }
#else
				 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				 RTDNVRamSaveOSDData();
#endif
#endif
						  break;
 
#endif
 
#if(_D2_INPUT_PORT_TYPE !=_D2_NO_PORT) 
		   case _OSD_INPUT_D2:	//D2
                          #if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
                                  g_usVolumePowerForPopo= _ON;
                          	  PCB_AMP_MUTE(_AMP_MUTE_ON);	
                                 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   22222", 0);
                          #endif							 
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
 
#if(_DP_MST_SUPPORT == _ON)
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
				 if(UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
				 {
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
					 RTDNVRamSaveOSDData();					   
				 }
#else
				 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				 RTDNVRamSaveOSDData();
#endif
#endif
							 break;
 
#endif
 
 
#if(_D3_INPUT_PORT_TYPE !=_D3_NO_PORT) 
			  case _OSD_INPUT_D3:	//D3
                           #if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
                                   g_usVolumePowerForPopo= _ON;
                           	  PCB_AMP_MUTE(_AMP_MUTE_ON);	
                                  DebugMessageAudio("PCB_AMP_MUTE(D2Port)   333333", 0);
                           #endif	
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
 
#if(_DP_MST_SUPPORT == _ON)
 
				 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				 RTDNVRamSaveOSDData();
#endif
							 break;
#endif
 
 
 
#if(_D4_INPUT_PORT_TYPE !=_D4_NO_PORT) 
						 case _OSD_INPUT_D4:	//D4
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
 
#if(_DP_MST_SUPPORT == _ON)
 
				 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				 RTDNVRamSaveOSDData();
#endif
									
							 break;
 
#endif
 
 
 
#if(_D5_INPUT_PORT_TYPE !=_D5_NO_PORT) 
						 case _OSD_INPUT_D5:	//D5
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
 
#if(_DP_MST_SUPPORT == _ON)
				 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				 RTDNVRamSaveOSDData();
#endif
 
 
							 break;
#endif
 
 
#if(_D6_INPUT_PORT_TYPE !=_D6_NO_PORT) 
						 case _OSD_INPUT_D6:	//D6
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
 
#if(_DP_MST_SUPPORT == _ON)
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
				 if(UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
				 {
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
					 RTDNVRamSaveOSDData();					   
				 }
#else
				 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
				 RTDNVRamSaveOSDData();
#endif
#endif
 
							 break;
#endif
 
						 default:
							 break;
					 }
				 }		
				 else
				 {
					 if(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)
					 {
//						 SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
					 }
					 else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
					 {
						 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
					 }
					 else
					 {
						 OsdDispDisableOsd();
					 }
				 } 
				 SET_OSD_STATE(_MENU_NONE);
			 }
 
			 break;
			 
		 case _RIGHT_KEY_MESSAGE: 
		 	
			CLR_KEYREPEATENABLE();
			 g_usItemNum=GET_OSD_INPUT_PORT_OSD_ITEM();
		 if(g_usItemNum==(_OSD_INPUT_AMOUNT-1))
			 {
			 g_usItemNum=_OSD_INPUT_AUTO;
			 }
		 else 
			 {
				  g_usItemNum++;
			 }
 
		 SET_OSD_INPUT_PORT_OSD_ITEM(g_usItemNum);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(2), COL(3+(11*GET_OSD_INPUT_PORT_OSD_ITEM())), WIDTH(8), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
			 {
				 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
			 }	 
			 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
 
 
			 break;
 
		 case _LEFT_KEY_MESSAGE: 
			 CLR_KEYREPEATENABLE();
		 g_usItemNum=GET_OSD_INPUT_PORT_OSD_ITEM();
		 if(g_usItemNum==_OSD_INPUT_AUTO)
			 {
			 g_usItemNum=(_OSD_INPUT_AMOUNT-1);
			 }
		 else 
					{
					g_usItemNum--;
			 }
 
		 SET_OSD_INPUT_PORT_OSD_ITEM(g_usItemNum);
		 OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_6, ROW(2), COL(3+(11*GET_OSD_INPUT_PORT_OSD_ITEM())), WIDTH(8), HEIGHT(1), _CP_BLACK, _CP_RED, _CP_BG);
			 if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
			 {
				 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
			 }	 
			 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
 
			 break;
 
		 case _MENU_KEY_MESSAGE:
			 if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
			 {
				 SET_OSD_INPUT_PORT_OSD_ITEM(g_usBackupValue);
				 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			 }
 
			 if(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)
			 {
//				 SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
			 }
			 else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
			 {
				 if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
			 }
			 else
			 {
				 SET_OSD_STATE(_MENU_NONE);
				 ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
				 //COsdShowChooseSetupText(_STRING_SETUP_INPUT);
				 OsdDispDisableOsd();
			 }			  
 
			 break;
 
		 default:
			 break; 				  
	 }
 }

void MenuHotKeyVolume(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

#if(_CUSTOMER_TYPE == _CUSTOMER_MAO_00)
        case _UP_KEY_MESSAGE: //170928_02
        case _DOWN_KEY_MESSAGE:
		if(GET_KEYMESSAGE() ==_UP_KEY_MESSAGE) SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
		else if(GET_KEYMESSAGE() ==_DOWN_KEY_MESSAGE) SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
#endif
        case _VOL_P_IR_MESSAGE:
        case _VOL_M_IR_MESSAGE:
		if(GET_KEYMESSAGE() ==_VOL_P_IR_MESSAGE) SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
		else if(GET_KEYMESSAGE() ==_VOL_M_IR_MESSAGE) SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);

		
        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
			

	    g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF , _ON);
		SET_OSD_VOLUME(g_usAdjustValue);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _SELECT);
		OsdPropShowNumber(ROW(2), COL(31), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1,_OSD_NUMBER_SELECT_COLOR);
		
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);			
#if(_AUDIO_SUPPORT == _ON)
		UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
            break;

        case _MUTE_IR_MESSAGE  :
		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_MUTE);
		OsdFontPut1BitMainMenuIcon(ROW(1), COL(1), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_GRAY, _CP_BG);

		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _UNSELECT);
	
		OsdPropShowNumber(ROW(2), COL(31), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1,COLOR(_CP_GRAY, _CP_BG));

		SET_OSD_VOLUME_MUTE(_ON);
  		SET_OSD_STATE(_MENU_HOTKEY_MUTE);		
#if(_AUDIO_SUPPORT == _ON)
		UserAdjustAudioMuteSwitch();
#endif
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            break;


        case _MENU_KEY_MESSAGE:

            OsdDispDisableOsd();
            break;

        default:
            break;
    }

//    OsdFuncShowSourceMenuCheck();
}


void MenuHotKeyMute(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

#if(_CUSTOMER_TYPE == _CUSTOMER_MAO_00)
        case _UP_KEY_MESSAGE: //170928_02
        case _DOWN_KEY_MESSAGE:
		if(GET_KEYMESSAGE() ==_UP_KEY_MESSAGE) SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
		else if(GET_KEYMESSAGE() ==_DOWN_KEY_MESSAGE) SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
#endif			
        case _VOL_P_IR_MESSAGE:
        case _VOL_M_IR_MESSAGE:
		if(GET_KEYMESSAGE() ==_VOL_P_IR_MESSAGE) SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
		else if(GET_KEYMESSAGE() ==_VOL_M_IR_MESSAGE) SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
//		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_VOLUME);
//		OsdFontPut1BitBackLightIcon(ROW(1), COL(2), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_ORANGE, _CP_BG);

		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_VOLUME);
		OsdFontPut1BitMainMenuIcon(ROW(1), COL(1), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_ORANGE, _CP_BG);
		
		SET_OSD_VOLUME_MUTE(_OFF);
	
			
		g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF, _ON);
		SET_OSD_VOLUME(g_usAdjustValue);
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _SELECT);
		OsdPropShowNumber(ROW(2), COL(31), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1,_OSD_NUMBER_SELECT_COLOR);

   
  		SET_OSD_STATE(_MENU_HOTKEY_VOLUME);
#if(_AUDIO_SUPPORT == _ON)
		UserAdjustAudioMuteSwitch();
#endif
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            break;

        case _MUTE_IR_MESSAGE  :
		SET_OSD_VOLUME_MUTE(_OFF);
  		SET_OSD_STATE(_MENU_HOTKEY_VOLUME);

		OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_VOLUME);
			OsdFontPut1BitMainMenuIcon(ROW(1), COL(1), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_ORANGE, _CP_BG);

//		OsdDispSliderAndNumber(_MENU_HOTKEY_VOLUME, GET_OSD_VOLUME());
		g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
		OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _SELECT);
		OsdPropShowNumber(ROW(2), COL(31), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1,_OSD_NUMBER_SELECT_COLOR);



#if(_AUDIO_SUPPORT == _ON)
		UserAdjustAudioMuteSwitch();
#endif

		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            break;

        case _MENU_KEY_MESSAGE:

            OsdDispDisableOsd();
            break;

        default:
            break;
    }

//    OsdFuncShowSourceMenuCheck();
}

void MenuHotKeyAudioMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;


	//case _AUDIO_MODE_IR_MESSAGE:
	//	g_usAdjustValue = GET_OSD_AUDIO_MODE() +1;
	//	if(g_usAdjustValue > _AUDIO_MODE_MAX) g_usAdjustValue = 0;
	//	SET_OSD_AUDIO_MODE(g_usAdjustValue);
	//	OsdFuncClearOsd(ROW(1), COL(1), 8, 3);

 //		OsdPropPutStringCenter(ROW(1), COL(1), WIDTH(8), _PFONT_PAGE_0, (GET_OSD_AUDIO_MODE()+_STRING_AUDIO_STANDARD), COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);
	//	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);			

	//	UserCommonAudioMode(GET_OSD_AUDIO_MODE() );



	//	ScalerTimerDelayXms(100);

 //           break;
			
        case _VOL_P_IR_MESSAGE:
        case _VOL_M_IR_MESSAGE:
        case _MENU_KEY_MESSAGE:

            OsdDispDisableOsd();
            break;

        default:
            break;
    }

//    OsdFuncShowSourceMenuCheck();
}

void MenuHotKeyPictureMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

//	case _PICTURE_MODE_IR_MESSAGE:
//		g_usAdjustValue = GET_OSD_COLOR_EFFECT() +1;
//		if(g_usAdjustValue > _COLOREFFECT_USER) g_usAdjustValue = 0;
//		SET_OSD_COLOR_EFFECT(g_usAdjustValue);
//		OsdFuncClearOsd(ROW(1), COL(1), 8, 3);
//
//   		OsdPropPutStringCenter(ROW(1), COL(1), WIDTH(8), _PFONT_PAGE_0, (GET_OSD_COLOR_EFFECT()+_STRING_COLOREFFECT_STANDARD), COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);
//		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);			
//
//#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//                UserAdjustColorEffectMode();
//#endif
//            break;

        case _MENU_KEY_MESSAGE:

            OsdDispDisableOsd();
            break;

        default:
            break;
    }

//    OsdFuncShowSourceMenuCheck();
}
#if 0
void MenuConnectBluetoothAdjust(void) //170928_00
{

    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
//Eric_020170929 : Delete
    			if(g_usAdjustValue == _ON) 
    			{

					   UserCommonAudioAmpIICWrite(0x03,0x03);

					   b1BlueToothStatus = _ON;
         			   UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);

    			}
    			else
    			{
				UserCommonAudioAmpIICWrite(0x03,0x00);
//				SysUartSendBluetoothOff();
    			}
                OsdDispDisableOsd();
            break;


        case _LEFT_KEY_MESSAGE:
	            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27+6), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
			g_usAdjustValue = _ON;
			
		
            break;

        case _RIGHT_KEY_MESSAGE:
			
	            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27+6 - 9), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
			g_usAdjustValue = _OFF;		
			
				
            break;



        case _MENU_KEY_MESSAGE:
//		SysUartSendBluetoothOff();

                OsdDispDisableOsd();
            break;

        default:
            break;
    }
}
void MenuDisconnectBluetoothAdjust(void)//170928_00
{
    switch(GET_KEYMESSAGE())
    {
        case _SELECT_KEY_MESSAGE:
    			if(g_usAdjustValue == _ON) 
    			{
//    				ScalerIRSendNEC(0xff00, 0x1EE1) ; // 170925
//    				ScalerTimerDelayXms(100);
//    				ScalerIRSendNEC(0xff00, 0x1EE1) ; // 170925
//    				ScalerTimerDelayXms(100);
    
//    				ScalerIRSendNEC(0xff00, 0x1EE1) ; // 170925
        			b1BlueToothStatus= _OFF;
					SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
    			}
    			else
    			{
					UserCommonAudioAmpIICWrite(0x03,0x00);
        			b1BlueToothStatus= _OFF;         
    			}
              	  OsdDispDisableOsd();
            break;


        case _LEFT_KEY_MESSAGE:
	            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
			g_usAdjustValue = _ON;		
            break;

        case _RIGHT_KEY_MESSAGE:			
	            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27 - 9), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
			g_usAdjustValue = _OFF;		
				
            break;



        case _MENU_KEY_MESSAGE:
  
                OsdDispDisableOsd();
            break;

        default:
            break;
    }
}
#endif

void MenuHotKeyBacklight(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		OsdDispDisableOsd();
		break;

	case _RIGHT_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
			g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF, _ON);
			OsdWindowSlider(ROW(2), COL(9), g_usAdjustValue, _SLIDER_9, _SELECT);
			OsdPropShowNumber(ROW(2), COL(31), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _SUB_PAGE_ITEM_1, _OSD_NUMBER_SELECT_COLOR);
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
			SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
			UserAdjustBacklight(GET_OSD_BACKLIGHT());
		break;

	case _MENU_KEY_MESSAGE:
		OsdDispDisableOsd();
		break;

	default:
		break;
	}

	//    OsdFuncShowSourceMenuCheck();
}

void MenuHotKeySource(void)
{
	switch (GET_KEYMESSAGE())
	{
	case _SELECT_KEY_MESSAGE:
		//DebugMessageYHJ("GET_OSD_INPUT_PORT_OSD_ITEM()", GET_OSD_INPUT_PORT_OSD_ITEM()); //Eric_170116_Test
		if (g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
		{
			DebugMessageSystem("g_usBackupValue 2 ", g_usBackupValue); //Eric_170116_Test
			SET_OSD_INPUT_PORT_OSD_ITEM(g_usBackupValue);
			switch (g_usBackupValue)
			{

#if(_A0_INPUT_PORT_TYPE !=_A0_NO_PORT) 
				 case _OSD_INPUT_A0: // A0
					 SET_OSD_INPUT_PORT_OSD_ITEM(_OSD_INPUT_A0);
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_A0_INPUT_PORT);

					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif                            


					 break;
#endif

#if(_D0_INPUT_PORT_TYPE !=_D0_NO_PORT) 
				 case _OSD_INPUT_D0: // D0
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   0000000", 0);
#endif					 
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D0_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif
					 break;

#endif


#if(_D1_INPUT_PORT_TYPE !=_D1_NO_PORT) 
				 case _OSD_INPUT_D1:	//D1
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   1111111", 0);
#endif	
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D1_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif
					 break;

#endif

#if(_D2_INPUT_PORT_TYPE !=_D2_NO_PORT) 
				 case _OSD_INPUT_D2:	//D2
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   22222", 0);
#endif				
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D2_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif
					 break;

#endif

#if(_D3_INPUT_PORT_TYPE !=_D3_NO_PORT) 
				 case _OSD_INPUT_D3:	//D3
#if 0//(_PCB_TYPE == _RL6449_SM2795A) //tdy add for popo
					 g_usVolumePowerForPopo = _ON;
					 PCB_AMP_MUTE(_AMP_MUTE_ON);
					 DebugMessageAudio("PCB_AMP_MUTE(D2Port)   333333", 0);
#endif	
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D3_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)

					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
					 break;
#endif

#if(_D4_INPUT_PORT_TYPE !=_D4_NO_PORT) 
				 case _OSD_INPUT_D4:	//D4
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D4_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)

					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif

					 break;

#endif

#if(_D5_INPUT_PORT_TYPE !=_D5_NO_PORT) 
				 case _OSD_INPUT_D5:	//D5
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D5_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif


					 break;
#endif

#if(_D6_INPUT_PORT_TYPE !=_D6_NO_PORT) 
				 case _OSD_INPUT_D6:	//D6
					 SET_FORCE_POW_SAV_STATUS(_FALSE);
					 SysSourceSwitchInputPort(_D6_INPUT_PORT);
					 SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

					 SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

					 if ((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
						 (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
					 {
						 UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
						 UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
						 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
					 }

#if(_DP_MST_SUPPORT == _ON)
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
					 if (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)
					 {
						 ScalerDpRxMstRx0Rx1switch(_DP_MST_RX0_PORT);
						 RTDNVRamSaveOSDData();
					 }
#else
					 ScalerDpRxMstRx0Rx1switch(_DP_MST_NO_PORT);
					 RTDNVRamSaveOSDData();
#endif
#endif

					 break;
#endif
			case _OSD_INPUT_AUTO: // Auto
				SET_FORCE_POW_SAV_STATUS(_FALSE);

				SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
				SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

				if (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
				{
					UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
				}
#if(_DP_MST_SUPPORT == _ON)
				if (GET_OSD_DP_MST() != _MST_OFF)
				{
					SET_OSD_DP_MST(_MST_OFF);
				}
#endif
				break;

			default:
				break;
			}

#if(_DP_MST_SUPPORT == _ON)
			ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
			RTDNVRamSaveOSDData();

#endif
			}

		OsdDispDisableOsd();
		break;
	
	case _UP_KEY_MESSAGE:
	case _DOWN_KEY_MESSAGE:
	case _RIGHT_KEY_MESSAGE:
	case _LEFT_KEY_MESSAGE:
		g_usBackupValue = OsdFuncCheckInputPortType(g_usBackupValue);
		DebugMessageSystem("INPUT PORT ", g_usBackupValue);
		OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
		OsdDispHotKeySourceMenuIcon(g_usBackupValue);
		break;

	case _MENU_KEY_MESSAGE:
		OsdDispDisableOsd();

		switch (SysModeGetModeState())
		{
		case _MODE_STATUS_NOSIGNAL:

			if (SysModeGetModeStateChange() == _TRUE)
			{
				if (SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE)
				{
					ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
				}
				else
				{
					ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
				}
			}
			break;
		default:
			break;
		}
		// Perform display state change actions
		//switch (SysRegionGetDisplayState(_DISPLAY_RGN_1P))
		//{
		//case _DISPLAY_STATE_NO_SIGNAL:

		//	// Check NSG to PS condition in single display
		//	if (SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) == _TRUE)
		//	{
		//		ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
		//	}
		//	else
		//	{
		//		ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
		//	}
		//	break;

		//case _DISPLAY_STATE_OOR:

		//	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSUPPORT_MSG);
		//	break;

		//default:
		//	break;
		//}

		break;

	default:
		break;
}

	OsdFuncShowSourceMenuCheck();
}

void DispServiceMenu(void)
{
	BYTE   Lengh1 = 0, Lengh2 = 5;
	SET_OSD_STATE(_MENU_SERVICE);

	//for (Lengh1 = 1; Lengh1 < 6; Lengh1++)
	//{
	//	OsdFuncClearOsd(ROW(_OSD_NUMBER_5_ROW * Lengh1), COL(_OSD_NUMBER_7_COL), WIDTH(15), HEIGHT(1));
	//}
	for (Lengh1 = 1; Lengh1 < 6; Lengh1++)
	{
		OsdFuncClearOsd(ROW(4 * Lengh1), COL(7), WIDTH(13), HEIGHT(1));
	}
	for (Lengh2 = 1; Lengh2 < 6; Lengh2++)
	{
		OsdFuncClearOsd(ROW(_OSD_NUMBER_1_ROW + (Lengh2 - 1) * 3), COL(_OSD_NUMBER_1_COL), WIDTH(13), HEIGHT(1));
	}
	ScalerOsdWindowDisable(_OSD_WINDOW_4_6);
	OsdDispMainMenuItemSelection(_MENU_COLOR - 1, _OSD_UNSELECT);
	OsdFontPut1FuncHLine(10, 2, _WHITE_EDGE_2, _OSD_MAIN_MENU_LV1_LINE_WIDTH, _CP_WHITE, _CP_BLUE_65);
	OsdFuncClearOsd(ROW(2), COL(20), WIDTH(15), HEIGHT(22));
	OsdFontPut1FuncTableForm(2, 20, _EDGE_LINE, 13, 20, _CP_WHITE, _CP_BLUE_65, _GRID_WINDOW_0);
	OsdPropPutString(ROW(4), COL(7), _PFONT_PAGE_0, _STRING_SERVICE, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
	OsdPropPutString(ROW(_OSD_NUMBER_13_ROW + 3), COL(_OSD_NUMBER_1_COL + 20), _PFONT_PAGE_0, _STRING_VERSION, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	COsdShowPageText(_MENU_SERVICE);
	COsdShowChooseOSDSetText(_STRING_SERVICE_PWM_RES);
	OsdDispMainMenuItemSelection(_MENU_PICTURE - 1, _OSD_SELECT);
	
}

//Eric_20180306_Delete : Start --------------------------------- 
//    
//    void MenuPicture(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_HDR10_SUPPORT == _ON)
//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                {
//    #if (_SHARPNESS_SUPPORT == _ON)
//                    SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
//                    OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_SHARPNESS());
//    #endif
//                    return;
//                }
//    #endif
//    #if(_FREESYNC_II_SUPPORT == _ON)
//                if(UserCommonHDRGetFreesynIIStatus() == _ON)
//                {
//    #if (_SHARPNESS_SUPPORT == _ON)
//                    SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
//                    OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_SHARPNESS());
//    #endif
//                    return;
//                }
//    #endif
//                SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
//    
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
//    
//                // OsdDispMainMenuKeyInfo(_KEY_INFO_BACK, _OSD_UNSELECT);
//                OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY);
//    
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_FACTORY);
//    
//    #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//                if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
//                   (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//                {
//                    OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdHeight, 5);
//                }
//                else
//    #endif
//                {
//                    OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdWidth, 5);
//                }
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FACTORY_0);
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplay(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_AUTO);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                }
//                else
//    #endif
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//                    if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                    }
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//    
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_PICTURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColor(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_HDR10_SUPPORT == _ON)
//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                {
//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//                    if(GET_OSD_HDR_LIGHT_ENHANCE() != 0)
//                        break;
//    #endif
//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//                    if(GET_OSD_HDR_COLOR_ENHANCE() != 0)
//                        break;
//    #endif
//                    SET_OSD_STATE(_MENU_COLOR_EFFECT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
//    
//                    if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                    }
//                    break;
//                }
//    #endif
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//                if(GET_OSD_LOCAL_DIMMING() == _ON)
//                {
//                    SET_OSD_STATE(_MENU_COLOR_GAMMA);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//                    OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
//                    if(GET_OSD_GAMMA() == _GAMMA_24)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
//                    }
//                    break;
//                }
//    #endif
//    #if(_SDR_TO_HDR_SUPPORT == _ON)
//                if(GET_OSD_SDR_TO_HDR() == _ON)
//                {
//                    break;
//                }
//    #endif
//    #if(_FREESYNC_II_SUPPORT == _ON)
//                if(UserCommonHDRGetFreesynIIStatus() == _ON)
//                {
//                    SET_OSD_STATE(_MENU_COLOR_EFFECT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
//    
//                    if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                    }
//                    break;
//                }
//    #endif
//    
//                SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvance(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_ITEM_INDEX(0);
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                if((SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP) || (SysSourceGetInputPort() <= _D1_INPUT_PORT))
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                }
//                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuInput(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = SysSourceGetInputPort();
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    SET_OSD_STATE(_MENU_INPUT_AUTO);
//                }
//                else
//                {
//                    switch(SysSourceGetInputPort())
//                    {
//                        case _A0_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_A0_PORT);
//                            break;
//    
//                        case _D0_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_D0_PORT);
//                            break;
//    
//                        case _D1_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_D1_PORT);
//                            break;
//    
//                        case _D2_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_D2_PORT);
//                            break;
//    
//                        case _D3_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_D3_PORT);
//                            break;
//    
//                        case _D4_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_D4_PORT);
//                            break;
//    
//                        case _D5_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_D5_PORT);
//                            break;
//    
//                        case _D6_INPUT_PORT:
//                            SET_OSD_STATE(_MENU_INPUT_D6_PORT);
//                            break;
//    
//                        default:
//                            break;
//                    }
//                }
//    
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _SELECT, SysSourceGetScanType());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudio(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_VOLUME);
//    
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_0);
//                OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                if((SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP) || (SysSourceGetInputPort() <= _D1_INPUT_PORT))
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                }
//                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOther(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER_RESET);
//    
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_0);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INFORMATION);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INFORMATION_0);
//                OsdDispShowInformation();
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuInformation(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_FACTORY);
//    
//    #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//                if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
//                   (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//                {
//                    OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdHeight, 5);
//                }
//                else
//    #endif
//                {
//                    OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdWidth, 5);
//                }
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FACTORY_0);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER);
//    
//    #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//                if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
//                   (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//                {
//                    OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdHeight, 5);
//                }
//                else
//    #endif
//                {
//                    OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdWidth, 5);
//                }
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuFactory(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                ScalerOsdMapRotation(0, _ENABLE, HEIGHT(_FACTORY_OSD_ROW), _DISABLE, 0, _DISABLE);
//                RTDFactoryMainMenu();
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_PICTURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INFORMATION);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INFORMATION_0);
//                OsdDispShowInformation();
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispDisableOsd();
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureBacklight(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_BACKLIGHT();
//    
//                SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if (_BRIGHTNESS_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS());
//    #elif (_CONTRAST_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST());
//    #elif (_SHARPNESS_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS());
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_PICTURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
//                OsdDispMainMenuKeyInfo(_KEY_INFO_EXIT, _OSD_UNSELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureBrightness(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_BRIGHTNESS();
//    
//                SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if (_CONTRAST_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST());
//    #elif (_SHARPNESS_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS());
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_PICTURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureContrast(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_CONTRAST();
//    
//                SET_OSD_STATE(_MENU_PICTURE_CONTRAST_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_SHARPNESS_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS());
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if (_BRIGHTNESS_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS());
//    #else
//                SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_PICTURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureSharpness(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_SHARPNESS();
//    
//                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_HDR10_SUPPORT == _ON)
//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                {
//                    break;
//                }
//    #endif
//    #if(_FREESYNC_II_SUPPORT == _ON)
//                if(UserCommonHDRGetFreesynIIStatus() == _ON)
//                {
//                    break;
//                }
//    #endif
//    
//    #if (_CONTRAST_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST());
//    #elif (_BRIGHTNESS_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS());
//    #else
//                SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_PICTURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayAuto(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                    OsdDispMainSubString(_AUTO_CONFIG_DO);
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_AUTO, 0);
//                    OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
//                    OsdDispMainSubString(_AUTO_CONFIG_RESULT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                OsdDispClearSelectColor(_DOWN);
//                OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
//                SET_OSD_STATE(_MENU_DISPLAY_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_VGA_MODE_ADJUST_H_POSITION());
//                }
//                else
//    #endif
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_DIGITAL_H_POSITION());
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    
//    
//    void MenuDisplayHPos(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    g_usBackupValue = GET_VGA_MODE_ADJUST_H_POSITION();
//                }
//                else
//    #endif
//                {
//                    g_usBackupValue = GET_DIGITAL_H_POSITION();
//                }
//    
//                SET_OSD_STATE(_MENU_DISPLAY_HPOS_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS, GET_VGA_MODE_ADJUST_V_POSITION());
//                }
//                else
//    #endif
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS, GET_DIGITAL_V_POSITION());
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_AUTO);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispClearSliderAndNumber();
//                }
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayVPos(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    g_usBackupValue = GET_VGA_MODE_ADJUST_V_POSITION();
//                }
//                else
//    #endif
//                {
//                    g_usBackupValue = GET_DIGITAL_V_POSITION();
//                }
//    
//                SET_OSD_STATE(_MENU_DISPLAY_VPOS_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_CLOCK, GET_VGA_MODE_ADJUST_CLOCK());
//                }
//                else
//    #endif
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                    OsdDispClearSliderAndNumber();
//                    OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//                    if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                    }
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_VGA_MODE_ADJUST_H_POSITION());
//                }
//                else
//    #endif
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_DIGITAL_H_POSITION());
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayClock(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                g_usBackupValue = GET_VGA_MODE_ADJUST_CLOCK();
//                SET_OSD_STATE(_MENU_DISPLAY_CLOCK_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//    #if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usBackupValue, _SLIDER_0, _SELECT);
//    #else
//                {
//                    WORD usClockRangeMax = 0;
//                    WORD usClockRangeMin = 0;
//                    WORD usUserIHTotal = 0;
//    
//                    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
//                    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
//                    usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usBackupValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
//    
//                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _SELECT);
//                }
//    #endif
//    
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_PHASE);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_PHASE, GET_VGA_MODE_ADJUST_PHASE());
//                }
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_DISPLAY_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS, GET_VGA_MODE_ADJUST_V_POSITION());
//                }
//    #endif
//    
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayPhase(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                g_usBackupValue = GET_VGA_MODE_ADJUST_PHASE();
//    
//                SET_OSD_STATE(_MENU_DISPLAY_PHASE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                // OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//    
//                if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_CLOCK, GET_VGA_MODE_ADJUST_CLOCK());
//                }
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayDispRotate(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_DISPLAY_ROTATION_SUPPORT == _ON)
//                g_usBackupValue = GET_OSD_DISP_ROTATE();
//                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _SELECT, GET_OSD_DISP_ROTATE());
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//                if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_0)
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
//                }
//    #elif(_FREEZE_SUPPORT == _ON)
//    
//                SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//    
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_DISPLAY_PHASE);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_PHASE, GET_VGA_MODE_ADJUST_PHASE());
//                }
//    #endif
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayLatency(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//                g_usBackupValue = GET_OSD_LATENCY();
//                SET_OSD_STATE(_MENU_DISPLAY_LATENCY_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _SELECT, GET_OSD_LATENCY());
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_FREEZE_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                // OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//                if((GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4)))
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDislayFreeze(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_FREEZE_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_DISPLAY_FREEZE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREEZE_STATUS());
//                g_usBackupValue = GET_OSD_FREEZE_STATUS();
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//                if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_0)
//                {
//                    SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
//                }
//    #else
//                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//                if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                }
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorPanelUniformity(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_PANEL_UNIFORMITY();
//                SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_GAMMA);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
//    
//                if(GET_OSD_GAMMA() == _GAMMA_24)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    
//    void MenuColorGamma(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                {
//                    g_usBackupValue = _FROM_STATE_GAMMA;
//                    g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
//                    OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
//                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                    SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
//                }
//                else
//                {
//                    g_usBackupValue = GET_OSD_GAMMA();
//    
//                    SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJUST);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA());
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_CONTRAST_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());
//                if(GET_COLOR_TEMP_TYPE() >= _CT_SRGB)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
//                }
//    #else
//                SET_OSD_STATE(_MENU_COLOR_EFFECT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
//    
//                if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                }
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//                if(GET_OSD_LOCAL_DIMMING() == _ON)
//                {
//                    break;
//                }
//    #endif
//                SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorTemperature(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_COLOR_TEMP_TYPE();
//    
//                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFFECT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
//    
//                if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_GAMMA);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
//    
//                if(GET_OSD_GAMMA() == _GAMMA_24)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorEffect(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_EFFECT();
//    
//                SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_HDR10_SUPPORT == _ON)
//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                {
//                    break;
//                }
//    #endif
//    #if(_FREESYNC_II_SUPPORT == _ON)
//                if(UserCommonHDRGetFreesynIIStatus() == _ON)
//                {
//                    break;
//                }
//    #endif
//    
//                SET_OSD_STATE(_MENU_COLOR_DEMO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
//                if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_HDR10_SUPPORT == _ON)
//                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                {
//                    break;
//                }
//    #endif
//    #if(_FREESYNC_II_SUPPORT == _ON)
//                if(UserCommonHDRGetFreesynIIStatus() == _ON)
//                {
//                    break;
//                }
//    #endif
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());
//    
//    
//                if(GET_COLOR_TEMP_TYPE() >= _CT_SRGB)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
//                }
//    #else
//                SET_OSD_STATE(_MENU_COLOR_GAMMA);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
//    
//                if(GET_OSD_GAMMA() == _GAMMA_24)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
//                }
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorDemo(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HLWIN_TYPE();
//    
//                SET_OSD_STATE(_MENU_COLOR_DEMO_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _SELECT, GET_OSD_HLWIN_TYPE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_COLOR_FORMAT_CONVERT == _ON)
//                if((SysSourceGetSourceType() == _SOURCE_VGA) || (SysSourceGetSourceType() == _SOURCE_DVI))
//                {
//                    SET_OSD_STATE(_MENU_COLOR_FORMAT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
//                }
//                else
//    #endif
//                {
//                    SET_OSD_STATE(_MENU_COLOR_PCM);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                    if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//                    }
//                    else
//    #endif
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                    }
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFFECT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
//    
//                if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorFormat(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_FORMAT();
//    
//                SET_OSD_STATE(_MENU_COLOR_FORMAT_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_PCM);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//                }
//                else
//    #endif
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_DEMO);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorPCM(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                {
//                    g_usBackupValue = _FROM_STATE_PCM;
//                    g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
//                    OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
//                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
//                    SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
//                }
//                else
//                {
//                    g_usBackupValue = GET_OSD_PCM_STATUS();
//                    SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE());
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_COLOR_FORMAT_CONVERT == _ON)
//                if((SysSourceGetSourceType() == _SOURCE_VGA) || (SysSourceGetSourceType() == _SOURCE_DVI))
//                {
//                    SET_OSD_STATE(_MENU_COLOR_FORMAT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
//                }
//                else
//    #endif
//                {
//                    SET_OSD_STATE(_MENU_COLOR_DEMO);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
//    
//                    if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
//                    }
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorHue(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HUE();
//    
//                SET_OSD_STATE(_MENU_COLOR_HUE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_SATURATION, GET_OSD_SATURATION());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_COLOR_PCM);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//    
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//                }
//                else
//    #endif
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorSaturation(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_SATURATION();
//    
//                SET_OSD_STATE(_MENU_COLOR_SATURATION_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_HUE);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_COLOR);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    void MenuAdvanceItem(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                OsdDispAdvanceItemSelect(GET_OSD_ITEM_INDEX());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(OsdDispAdvanceItemCountbyKeyMessage() == _FALSE)
//                    break;
//    
//                OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX() % 4), _OSD_SELECT);
//                OsdDispMainMenuItemIndication2(GET_OSD_ITEM_INDEX(), GET_OSD_STATE(), _OSD_SELECT);
//                OsdDispClearSliderAndNumber();
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispAdvanceItemSwitch(GET_OSD_ITEM_INDEX());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
//                SET_OSD_ITEM_INDEX(0);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuInputAuto(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(SysSourceGetScanType() != _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
//                    {
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                OsdDispClearSelectColor(_DOWN);
//                SET_OSD_STATE(_MENU_INPUT_A0_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() != _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuInputA0Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _A0_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_A0_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D0_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_AUTO);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                else if(SysSourceGetInputPort() != _A0_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuInputD0Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D0_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_D0_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D1_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_A0_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                else if(SysSourceGetInputPort() != _D0_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuInputD1Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D1_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_D1_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D2_PORT);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D0_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                else if(SysSourceGetInputPort() != _D1_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuInputD2Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D2_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_D2_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D3_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D1_PORT);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                }
//                else if(SysSourceGetInputPort() != _D2_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuInputD3Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D3_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_D3_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D4_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D2_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                }
//                else if(SysSourceGetInputPort() != _D3_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuInputD4Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D4_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_D4_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D5_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D3_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                }
//                else if(SysSourceGetInputPort() != _D4_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuInputD5Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D5_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_D5_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D6_PORT);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D4_PORT);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//    
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                }
//                else if(SysSourceGetInputPort() != _D5_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuInputD6Port(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
//                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D6_INPUT_PORT))
//                {
//                    SET_FORCE_POW_SAV_STATUS(_FALSE);
//                    SysSourceSwitchInputPort(_D6_INPUT_PORT);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                    {
//                        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                    }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                    RTDNVRamSaveOSDData();
//    #endif
//                }
//                else
//                {
//                    OsdDispClearSelectColor(_DOWN);
//                    SET_OSD_STATE(_MENU_INPUT);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_INPUT_D5_PORT);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                }
//                else if(SysSourceGetInputPort() != _D6_INPUT_PORT)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                    if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
//                    }
//                    else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
//                    }
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
//                }
//                SET_OSD_STATE(_MENU_INPUT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioVolume(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_VOLUME();
//    
//                SET_OSD_STATE(_MENU_AUDIO_VOLUME_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME_ADJUST, GET_OSD_VOLUME());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_AUDIO_MUTE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioMute(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_VOLUME_MUTE();
//    
//                SET_OSD_STATE(_MENU_AUDIO_MUTE_ON_OFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _SELECT, GET_OSD_VOLUME_MUTE());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                SET_OSD_STATE(_MENU_AUDIO_VOLUME);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioStandAlong(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_AUDIO_STAND_ALONE();
//    
//                SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG_SELECT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//    
//                if((SysSourceGetSourceType() == _SOURCE_VGA) ||
//                   (SysSourceGetSourceType() == _SOURCE_DVI))
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, _LINE_IN_AUDIO);
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
//                }
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_SOURCE);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_MUTE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioAudioSource(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if((SysSourceGetSourceType() != _SOURCE_VGA) &&
//                   (SysSourceGetSourceType() != _SOURCE_DVI))
//                {
//                    g_usBackupValue = GET_OSD_AUDIO_SOURCE();
//    
//                    SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE_SELECT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _SELECT, GET_OSD_AUDIO_SOURCE());
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioSoundMode(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE_SELECT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SELF_TEST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, _OFF);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_0);
//    
//                if((SysSourceGetSourceType() == _SOURCE_VGA) ||
//                   (SysSourceGetSourceType() == _SOURCE_DVI))
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, _LINE_IN_AUDIO);
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
//                }
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_SOURCE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//    void MenuAudioAudioSelfTest(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SELF_TEST_SELECT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
//                g_usBackupValue = _OFF;
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #endif
//    
//    void MenuOtherReset(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                OsdDispOsdReset();
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherMenuTime(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_TIME_OUT();
//    
//                SET_OSD_STATE(_MENU_OTHER_MENU_TIME_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME_ADJUST, GET_OSD_TIME_OUT());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER_RESET);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherOsdHPos(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HPOS();
//    
//                SET_OSD_STATE(_MENU_OTHER_OSD_HPOS_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS_ADJUST, GET_OSD_HPOS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherOsdVPos(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_VPOS();
//    
//                SET_OSD_STATE(_MENU_OTHER_OSD_VPOS_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS_ADJUST, GET_OSD_VPOS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
//                OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_LANGUAGE);
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherLanguage(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_LANGUAGE();
//    
//                SET_OSD_STATE(_MENU_OTHER_LANGUAGE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _SELECT, GET_OSD_LANGUAGE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_0);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherTransparency(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_TRANSPARENCY_STATUS();
//    
//                SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY_ADJUST, GET_OSD_TRANSPARENCY_STATUS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER_ROTATE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_ROTATE);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_LANGUAGE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispClearSliderAndNumber();
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherRotate(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_ROTATE_STATUS();
//    
//                SET_OSD_STATE(_MENU_OTHER_ROTATE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_OTHER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureBacklightAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_BACKLIGHT())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT_ADJUST, GET_OSD_BACKLIGHT());
//                UserAdjustBacklight(GET_OSD_BACKLIGHT());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_BACKLIGHT())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_BACKLIGHT(g_usAdjustValue);
//                    UserAdjustBacklight(GET_OSD_BACKLIGHT());
//                }
//                SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureBrightnessAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_BRIGHTNESS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS_ADJUST, GET_OSD_BRIGHTNESS());
//    
//    #if(_BRIGHTNESS_SUPPORT == _ON)
//                UserAdjustBrightness(GET_OSD_BRIGHTNESS());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_BRIGHTNESS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_BRIGHTNESS(g_usAdjustValue);
//    
//    #if(_BRIGHTNESS_SUPPORT == _ON)
//                    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureContrastAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_CONTRAST())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST_ADJUST, GET_OSD_CONTRAST());
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_CONTRAST())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_CONTRAST(g_usAdjustValue);
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuPictureSharpnessAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS_ADJUST, GET_OSD_SHARPNESS());
//                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//    #if(_SHARPNESS_SUPPORT == _ON)
//                UserCommonAdjustSharpness(SysSourceGetInputPort());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SHARPNESS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_SHARPNESS(g_usAdjustValue);
//    #if(_SHARPNESS_SUPPORT == _ON)
//                    UserCommonAdjustSharpness(SysSourceGetInputPort());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_SHARPNESS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    void MenuDisplayHPosAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
//                    {
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
//                    }
//                }
//                else
//    #endif
//                {
//                    if(g_usBackupValue != GET_DIGITAL_H_POSITION())
//                    {
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
//                    }
//                }
//    
//                SET_OSD_STATE(_MENU_DISPLAY_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS_ADJUST, GET_VGA_MODE_ADJUST_H_POSITION());
//                    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
//                }
//                else
//    #endif
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS_ADJUST, GET_DIGITAL_H_POSITION());
//                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
//                    {
//                        g_usAdjustValue = g_usBackupValue;
//                        SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
//                        UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
//                    }
//                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_H_POSITION(), _SLIDER_0, _UNSELECT);
//                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                }
//                else
//    #endif
//                {
//                    if(g_usBackupValue != GET_DIGITAL_H_POSITION())
//                    {
//                        g_usAdjustValue = g_usBackupValue;
//                        SET_DIGITAL_H_POSITION(g_usAdjustValue);
//                        UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
//                    }
//                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_H_POSITION(), _SLIDER_0, _UNSELECT);
//                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                }
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayVPosAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
//                    {
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
//                    }
//                }
//                else
//    #endif
//                {
//                    if(g_usBackupValue != GET_DIGITAL_V_POSITION())
//                    {
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
//                    }
//                }
//    
//                SET_OSD_STATE(_MENU_DISPLAY_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS_ADJUST, GET_VGA_MODE_ADJUST_V_POSITION());
//                    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
//                }
//                else
//    #endif
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS_ADJUST, GET_DIGITAL_V_POSITION());
//                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_VGA_SUPPORT == _ON)
//                if(SysSourceGetSourceType() == _SOURCE_VGA)
//                {
//                    if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
//                    {
//                        g_usAdjustValue = g_usBackupValue;
//                        SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
//                        UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
//                    }
//                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_V_POSITION(), _SLIDER_0, _UNSELECT);
//                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                }
//                else
//    #endif
//                {
//                    if(g_usBackupValue != GET_DIGITAL_V_POSITION())
//                    {
//                        g_usAdjustValue = g_usBackupValue;
//                        SET_DIGITAL_V_POSITION(g_usAdjustValue);
//                        UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
//                    }
//                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_V_POSITION(), _SLIDER_0, _UNSELECT);
//                    OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                }
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayClockAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
//                }
//    #endif
//                SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    #else
//                {
//                    WORD usClockRangeMax = 0;
//                    WORD usClockRangeMin = 0;
//                    WORD usUserIHTotal = 0;
//    
//                    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
//                    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
//                    usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
//    
//                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
//                }
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                OsdDispSliderAndNumber(_MENU_DISPLAY_CLOCK_ADJUST, GET_VGA_MODE_ADJUST_CLOCK());
//                UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
//                    UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
//                }
//                SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    #if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_CLOCK(), _SLIDER_0, _UNSELECT);
//    #else
//                {
//                    WORD usClockRangeMax = 0;
//                    WORD usClockRangeMin = 0;
//                    WORD usUserIHTotal = 0;
//    
//                    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
//                    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
//                    usUserIHTotal = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
//    
//                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
//                }
//    #endif
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    #endif
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayPhaseAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
//                }
//    #endif
//                SET_OSD_STATE(_MENU_DISPLAY_PHASE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                OsdDispSliderAndNumber(_MENU_DISPLAY_PHASE_ADJUST, GET_VGA_MODE_ADJUST_PHASE());
//                UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    #if(_VGA_SUPPORT == _ON)
//                if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
//                    UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
//                }
//                SET_OSD_STATE(_MENU_DISPLAY_PHASE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_PHASE(), _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    #endif
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuDisplayDispRotateAdjust(void)
//    {
//    #if(_DISPLAY_ROTATION_SUPPORT == _ON)
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DISP_ROTATE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                // OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_DISP_ROTATE() != (_DISP_ROTATE_AMOUNT - 1)))
//                {
//                    if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 3))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
//                    }
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_DISP_ROTATE_ADJUST, GET_OSD_DISP_ROTATE());
//    
//    #if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
//                    if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 1))
//                    {
//                        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                    }
//    #endif
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_DISP_ROTATE() != _DISP_ROTATE_0))
//                {
//                    if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 4))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                    }
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_DISP_ROTATE_ADJUST, GET_OSD_DISP_ROTATE());
//    
//    #if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
//                    if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0))
//                    {
//                        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//                    }
//    #endif
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(g_usBackupValue != GET_OSD_DISP_ROTATE())
//                    {
//                        SET_OSD_DISP_ROTATE(g_usBackupValue);
//    
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//    
//                        if(GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4))
//                        {
//                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
//                        }
//                        else
//                        {
//                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
//                        }
//                    }
//                    SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
//    #if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
//    #endif
//                }
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    
//    void MenuDisplayLatencyAdjust(void)
//    {
//    #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//                if(g_usBackupValue != GET_OSD_LATENCY())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_LATENCY() != _LATENCY_H))
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_LATENCY_ADJUST, GET_OSD_LATENCY());
//    
//                    // Set Backlight OFF to prevent garbage
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//                if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_LATENCY() != _LATENCY_L))
//                {
//                    OsdDispSliderAndNumber(_MENU_DISPLAY_LATENCY_ADJUST, GET_OSD_LATENCY());
//    
//                    // Set Backlight OFF to prevent garbage
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(g_usBackupValue != GET_OSD_LATENCY())
//                    {
//                        SET_OSD_LATENCY(g_usBackupValue);
//    
//                        // Set Backlight OFF to prevent garbage
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//                    }
//                    SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
//                }
//    
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    
//    void MenuDisplayFreezeAdjust(void)
//    {
//    #if(_FREEZE_SUPPORT == _ON)
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//                if(GET_OSD_FREEZE_STATUS() != _OFF)
//                {
//                    SET_OSD_FREEZE_STATUS(_OFF);
//                    OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, _OFF);
//                    UserCommonAdjustDisplayFreeze(_OFF);
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//                if(GET_OSD_FREEZE_STATUS() != _ON)
//                {
//                    SET_OSD_FREEZE_STATUS(_ON);
//                    OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, _ON);
//                    UserCommonAdjustDisplayFreeze(_ON);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                if(g_usBackupValue != GET_OSD_FREEZE_STATUS())
//                {
//                    SET_OSD_FREEZE_STATUS(g_usBackupValue);
//                    UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
//                }
//    
//                SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    
//    void MenuColorPanelUniformityAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_PANEL_UNIFORMITY())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_PANEL_UNIFORMITY(_OFF);
//    
//    #if(_UNIFORMITY_SUPPORT == _ON)
//                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
//                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                {
//                    ScalerTimerWaitForEvent(_EVENT_DVS);
//                    ScalerTimerDelayXms(2);
//    
//                    UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
//                    ScalerColorPanelUniformityEnable(_FUNCTION_ON);
//                }
//    #endif
//    
//                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY());
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//    
//                if(GET_OSD_PANEL_UNIFORMITY() != _ON)
//                {
//                    SET_OSD_PANEL_UNIFORMITY(_ON);
//    
//    #if(_UNIFORMITY_SUPPORT == _ON)
//                    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        ScalerTimerWaitForEvent(_EVENT_DVS);
//                        ScalerTimerDelayXms(2);
//    
//                        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
//                        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
//                    }
//    #endif
//                }
//    
//                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_PANEL_UNIFORMITY())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_PANEL_UNIFORMITY(g_usAdjustValue);
//    
//    #if(_UNIFORMITY_SUPPORT == _ON)
//                    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        ScalerTimerWaitForEvent(_EVENT_DVS);
//                        ScalerTimerDelayXms(2);
//    
//                        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
//                        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
//                    }
//    #endif
//                }
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorGammaAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_GAMMA())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_GAMMA);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_GAMMA() != _GAMMA_24)
//                {
//                    if(GET_OSD_GAMMA() == _GAMMA_22)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
//                    }
//    
//                    OsdDispSliderAndNumber(_MENU_COLOR_GAMMA_ADJUST, GET_OSD_GAMMA());
//    
//    #if(_GAMMA_FUNCTION == _ON)
//                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
//    
//                    if(GET_OSD_GAMMA() != _GAMMA_OFF)
//                    {
//                        UserAdjustGamma(GET_OSD_GAMMA());
//                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
//                    }
//    #endif
//                }
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_GAMMA() != _GAMMA_OFF)
//                {
//                    if(GET_OSD_GAMMA() == _GAMMA_24)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
//                    }
//    
//                    OsdDispSliderAndNumber(_MENU_COLOR_GAMMA_ADJUST, GET_OSD_GAMMA());
//    
//    #if(_GAMMA_FUNCTION == _ON)
//                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
//    
//                    if(GET_OSD_GAMMA() != _GAMMA_OFF)
//                    {
//                        UserAdjustGamma(GET_OSD_GAMMA());
//                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
//                    }
//    #endif
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                if(g_usBackupValue != GET_OSD_GAMMA())
//                {
//                    SET_OSD_GAMMA(g_usBackupValue);
//    
//    #if(_GAMMA_FUNCTION == _ON)
//                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
//                    if(GET_OSD_GAMMA() != _GAMMA_OFF)
//                    {
//                        UserAdjustGamma(GET_OSD_GAMMA());
//                        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
//                    }
//    #endif
//                }
//    
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_GAMMA);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
//                if(GET_OSD_GAMMA() >= _GAMMA_24)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
//                }
//    
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorTempAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                if(GET_COLOR_TEMP_TYPE() == _CT_USER)
//                {
//                    g_usBackupValue = GET_COLOR_TEMP_TYPE();
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                    SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
//                    OsdDispClearSelectColor(_UP);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispClearArrow(_DOWN);
//                    OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());
//                }
//                else
//                {
//                    OsdDispClearArrow(_DOWN);
//                    SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
//                {
//                    if(GET_COLOR_TEMP_TYPE() == _CT_5800)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
//                    }
//                    OsdDispSliderAndNumber(_MENU_COLOR_TEMPERATURE_ADJUST, GET_COLOR_TEMP_TYPE());
//                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                }
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_COLOR_TEMP_TYPE() != _CT_9300)
//                {
//                    if(GET_COLOR_TEMP_TYPE() == _CT_SRGB)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
//                    }
//                    OsdDispSliderAndNumber(_MENU_COLOR_TEMPERATURE_ADJUST, GET_COLOR_TEMP_TYPE());
//                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE())
//                {
//                    SET_COLOR_TEMP_TYPE(g_usBackupValue);
//    
//                    // Adjust Color
//                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                }
//    
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());
//    
//                if(GET_COLOR_TEMP_TYPE() >= _CT_SRGB)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
//                }
//    
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffectAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_COLOR_EFFECT())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_USER)
//                {
//                    g_usBackupValue = GET_OSD_COLOR_EFFECT();
//                    OsdDispClearSelectColor(_UP);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//                    SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispClearSelectColor(_DOWN);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                    OsdDispClearArrow(_DOWN);
//                }
//                else
//                {
//                    OsdDispClearArrow(_DOWN);
//                    SET_OSD_STATE(_MENU_COLOR_EFFECT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
//                    if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                    }
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_COLOR_EFFECT() != _COLOREFFECT_AMOUNT)
//                {
//                    if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_PHOTO)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                    }
//                    OsdDispSliderAndNumber(_MENU_COLOR_EFFECT_ADJUST, GET_OSD_COLOR_EFFECT());
//    
//    #if(_HDR10_SUPPORT == _ON)
//                    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                    {
//                        UserCommonHDRAdjustHDR10ColorEffect();
//                    }
//                    else
//    #endif
//                    {
//    #if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//                        UserAdjustColorEffectMode();
//    #endif
//                    }
//                }
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_COLOR_EFFECT() != _COLOREFFECT_STANDARD)
//                {
//                    if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_VIVID)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                    }
//    
//                    OsdDispSliderAndNumber(_MENU_COLOR_EFFECT_ADJUST, GET_OSD_COLOR_EFFECT());
//    
//    #if(_HDR10_SUPPORT == _ON)
//                    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                    {
//                        UserCommonHDRAdjustHDR10ColorEffect();
//                    }
//                    else
//    #endif
//                    {
//    #if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//                        UserAdjustColorEffectMode();
//    #endif
//                    }
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                if(g_usBackupValue != GET_OSD_COLOR_EFFECT())
//                {
//                    SET_OSD_COLOR_EFFECT(g_usBackupValue);
//    
//    #if(_HDR10_SUPPORT == _ON)
//                    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
//                    {
//                        UserCommonHDRAdjustHDR10ColorEffect();
//                    }
//                    else
//    #endif
//                    {
//    #if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//                        UserAdjustColorEffectMode();
//    #endif
//                    }
//                }
//    
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_EFFECT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
//                if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
//                }
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorDemoAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_DEMO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_HLWIN_TYPE() != _HL_WIN_5)
//                {
//                    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_3)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
//                    }
//                    OsdDispSliderAndNumber(_MENU_COLOR_DEMO_ADJUST, GET_OSD_HLWIN_TYPE());
//    
//    #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//                    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
//                    {
//                        ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
//                    }
//                    else
//                    {
//                        UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
//                        ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
//                    }
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//    
//    #if(_BRIGHTNESS_SUPPORT == _ON)
//                    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
//    #endif
//    #endif
//    
//    #if(_DCC_FUNCTION == _ON)
//                    ScalerColorDCCNormalizeFactorAdjust();
//    #endif
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
//                {
//                    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_4)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
//                    }
//                    OsdDispSliderAndNumber(_MENU_COLOR_DEMO_ADJUST, GET_OSD_HLWIN_TYPE());
//    
//    #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//                    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
//                    {
//                        ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
//                    }
//                    else
//                    {
//                        UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
//                        ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
//                    }
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//    
//    #if(_BRIGHTNESS_SUPPORT == _ON)
//                    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
//    #endif
//    #endif
//    
//    #if(_DCC_FUNCTION == _ON)
//                    ScalerColorDCCNormalizeFactorAdjust();
//    #endif
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HLWIN_TYPE(g_usAdjustValue);
//                    // Adjust HLWIN
//    #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//                    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
//                    {
//                        UserAdjustHLWinType(_HL_WIN_OFF);
//                        ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
//                    }
//                    else
//                    {
//                        UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
//                        ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
//                    }
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//    #endif
//    
//    #if(_DCC_FUNCTION == _ON)
//                    ScalerColorDCCNormalizeFactorAdjust();
//    #endif
//                }
//                OsdDispClearArrow(_DOWN);
//                SET_OSD_STATE(_MENU_COLOR_DEMO);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
//                if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
//                }
//                else
//                {
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
//                }
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorFormatAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_COLOR_FORMAT())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_COLOR_FORMAT);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(GET_OSD_COLOR_FORMAT() != _COLOR_SPACE_YPBPR)
//                    {
//                        SET_OSD_COLOR_FORMAT(_COLOR_SPACE_YPBPR);
//                        OsdFuncColorFormatAdjust();
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT());
//                    }
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(GET_OSD_COLOR_FORMAT() != _COLOR_SPACE_RGB)
//                    {
//                        SET_OSD_COLOR_FORMAT(_COLOR_SPACE_RGB);
//                        OsdFuncColorFormatAdjust();
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT());
//                    }
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(g_usBackupValue != GET_OSD_COLOR_FORMAT())
//                    {
//                        g_usAdjustValue = g_usBackupValue;
//                        SET_OSD_COLOR_FORMAT(g_usAdjustValue);
//                        OsdFuncColorFormatAdjust();
//                    }
//                    SET_OSD_STATE(_MENU_COLOR_FORMAT);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
//                }
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorPCMAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
//                {
//                    g_usBackupValue = GET_OSD_PCM_STATUS();
//                    OsdDispClearArrow(_UP);
//                    OsdDispClearArrow(_DOWN);
//                    SET_OSD_STATE(_MENU_COLOR_PCM_SOFT_PROFT_ADJUST);
//                    // SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_1);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                    OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_PCM_1);
//    
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PCM_SOFT_PROFT);
//                }
//                else
//    #endif
//                {
//                    if(g_usBackupValue != GET_OSD_PCM_STATUS())
//                    {
//                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                    }
//    
//                    SET_OSD_STATE(_MENU_COLOR_PCM);
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//    #if(_OCC_SUPPORT == _ON)
//    #if(_RGB_3D_GAMMA == _ON)
//                if(GET_OSD_PCM_STATUS() != _PCM_OSD_SOFT_PROFT)
//    #else
//                if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
//    #endif
//                {
//                    OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());
//    
//    #if(_RGB_3D_GAMMA == _ON)
//                    if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                    }
//    #else
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//    #endif
//                    OsdFuncColorPcmAdjust();
//                }
//    #else    // #if(_OCC_SUPPORT == _ON)
//                if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
//                {
//                    OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());
//                }
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                OsdFuncColorPcmAdjust();
//    #endif
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//    #if(_OCC_SUPPORT == _ON)
//                if(GET_OSD_PCM_STATUS() != _PCM_OSD_SRGB)
//                {
//                    OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());
//    
//                    if(GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                    }
//                    OsdFuncColorPcmAdjust();
//                }
//    #else   //#if(_OCC_SUPPORT == _ON)
//                if(GET_OSD_PCM_STATUS() != _PCM_OSD_USER)
//                {
//                    OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());
//                    if(GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                    }
//                    OsdFuncColorPcmAdjust();
//                }
//    #endif
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_PCM_STATUS())
//                {
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                    if(g_usBackupValue == _PCM_OSD_SOFT_PROFT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    }
//    #endif
//    
//                    SET_OSD_PCM_STATUS(g_usBackupValue);
//    
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                    if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
//                    {
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//                    }
//                    else if((g_usAdjustValue == _PCM_OSD_SOFT_PROFT) && (GET_OSD_PCM_STATUS() != _PCM_OSD_SOFT_PROFT))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                    }
//    #else
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//    #endif
//                    OsdFuncColorPcmAdjust();
//                }
//                else
//                {
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//                }
//    
//                SET_OSD_STATE(_MENU_COLOR_PCM);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorHueAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HUE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_COLOR_HUE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_HUE_ADJUST, GET_OSD_HUE());
//    #if(_GLOBAL_HUE_SATURATION == _ON)
//                UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HUE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HUE(g_usAdjustValue);
//    #if(_GLOBAL_HUE_SATURATION == _ON)
//                    UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_HUE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_HUE(), _HUE_MAX, _HUE_MIN, _HUE_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorSaturationAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_COLOR_SATURATION);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_SATURATION_ADJUST, GET_OSD_SATURATION());
//    #if(_GLOBAL_HUE_SATURATION == _ON)
//                UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SATURATION())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_SATURATION(g_usAdjustValue);
//    #if(_GLOBAL_HUE_SATURATION == _ON)
//                    UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_SATURATION);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SATURATION(), _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceAspectAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                OsdDispClearArrow(_DOWN);
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//                    if(GET_OSD_LOCAL_DIMMING() == _ON)
//                    {
//                        break;
//                    }
//    #endif
//    
//                    if((GET_OSD_ASPECT_RATIO_TYPE()%4) == 3)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
//                    }
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_ASPECT_ADJUST, GET_OSD_ASPECT_RATIO_TYPE());
//    
//                    if(g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE())
//                    {
//                        SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
//                        OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE());
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//    #if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
//    #else
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//    #endif
//    #endif
//                    }
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(((GET_OSD_ASPECT_RATIO_TYPE()%4) == 0)&&(GET_OSD_ASPECT_RATIO_TYPE() != 0))
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
//                    }
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_ASPECT_ADJUST, GET_OSD_ASPECT_RATIO_TYPE());
//    
//                    if(g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE())
//                    {
//                        SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
//                        OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE());
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//    #if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
//    #else
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//    #endif
//    #endif
//                    }
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE())
//                    {
//                        g_usAdjustValue = g_usBackupValue;
//                        SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
//                        // Adjust HLW
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//    #if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
//    #else
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//    #endif
//    #endif
//                    }
//    
//                    OsdDispClearArrow(_DOWN);
//                    OsdDispAdvanceMenuReDraw(_LOW);
//                }
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceOverScanAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_OVER_SCAN_ADJUST, GET_OSD_OVERSCAN_STATUS());
//    
//    #if(_OVERSCAN_SUPPORT == _ON)
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//    #endif
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
//                {
//                    if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS())
//                    {
//                        g_usAdjustValue = g_usBackupValue;
//                        SET_OSD_OVERSCAN_STATUS(g_usAdjustValue);
//    #if(_OVERSCAN_SUPPORT == _ON)
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
//    #endif
//                    }
//    
//                    OsdDispAdvanceMenuReDraw(_LOW);
//                }
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceOverDriveOnOff(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_OD_STATUS();
//                SET_OSD_STATE(_MENU_ADVANCE_OD_ONOFF_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuAdvanceOverDriveGain(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_OD_GAIN();
//                SET_OSD_STATE(_MENU_ADVANCE_OD_GAIN_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDCRAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DCR_STATUS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_DCR_STATUS() != _OFF)
//                {
//                    SET_OSD_DCR_STATUS(_OFF);
//                    OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
//                }
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_DCR_STATUS() != _ON)
//                {
//                    SET_OSD_DCR_STATUS(_ON);
//                    OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DCR_STATUS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_DCR_STATUS(g_usAdjustValue);
//                }
//    
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDdcciAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_DDCCI_STATUS() != _OFF)
//                {
//                    SET_OSD_DDCCI_STATUS(_OFF);
//                    OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
//                    UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_DDCCI_STATUS() != _ON)
//                {
//                    SET_OSD_DDCCI_STATUS(_ON);
//                    OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
//                    UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_DDCCI_STATUS(g_usAdjustValue);
//                    UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
//                }
//    
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceUltraVividAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(((GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_H) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
//                   ((GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_OFF) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
//                {
//                }
//                else
//                {
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_ULTRA_VIVID_ADJUST, GET_OSD_ULTRA_VIVID_STATUS());
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//                    UserInterfaceAdjustUltraVividProc(_DB_APPLY_POLLING);
//    #endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_ULTRA_VIVID_STATUS(g_usAdjustValue);
//    
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//                    UserInterfaceAdjustUltraVividProc(_DB_APPLY_POLLING);
//    #endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
//                }
//    
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDpOptionD0(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                g_usBackupValue = GET_OSD_DP_D0_VERSION();
//                SET_OSD_STATE(_MENU_ADVANCE_DP_D0_VERSION_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//    #elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//    #elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//    #else
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//    #endif
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDpOptionD1(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                g_usBackupValue = GET_OSD_DP_D1_VERSION();
//                SET_OSD_STATE(_MENU_ADVANCE_DP_D1_VERSION_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//    #elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//    #else
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//    #endif
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//    #else
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//    #endif
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDpOptionD2(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                g_usBackupValue = GET_OSD_DP_D2_VERSION();
//                SET_OSD_STATE(_MENU_ADVANCE_DP_D2_VERSION_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//    #else
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//    #endif
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//    #elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//    #else
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//    #endif
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDpOptionD6(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                g_usBackupValue = GET_OSD_DP_D6_VERSION();
//                SET_OSD_STATE(_MENU_ADVANCE_DP_D6_VERSION_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//    #elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//    #elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//    #else
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//    #endif
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDPMstAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_MST())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                    UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//    
//                    if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
//                    {
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//                    }
//    #endif
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_DP_MST() != _MST_D1)
//                {
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_DP_MST_ADJUST, GET_OSD_DP_MST());
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_DP_MST() != _MST_OFF)
//                {
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_DP_MST_ADJUST, GET_OSD_DP_MST());
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_MST())
//                {
//                    // g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_DP_MST(g_usBackupValue);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDPEdidAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_EDID_SELECT))
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//    #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//                    UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
//                    UserCommonInterfaceDPSwitchEdid(_D1_INPUT_PORT);
//                    UserCommonInterfaceDPSwitchEdid(_D2_INPUT_PORT);
//                    UserCommonInterfaceDPSwitchEdid(_D6_INPUT_PORT);
//    #endif
//                }
//    
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(UserCommonNVRamGetSystemData(_DP_EDID_SELECT) != _DP_EDID_4K2K_60HZ)
//                {
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(UserCommonNVRamGetSystemData(_DP_EDID_SELECT) != _DP_EDID_1080P)
//                {
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_EDID_SELECT))
//                {
//                    UserCommonNVRamSetSystemData(_DP_EDID_SELECT, g_usBackupValue);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceCloneAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_CLONE_MODE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE());
//    
//                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE());
//                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceFreeSyncAdjust(void)
//    {
//    #if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
//                {
//                    SET_OSD_FREE_SYNC_STATUS(g_usBackupValue);
//    
//    #if(_FREESYNC_SUPPORT == _ON)
//                    UserCommonInterfaceFreeSyncSupportSwitch();
//    #endif
//    
//    #if((_HDMI_MULTI_EDID_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
//                    // Switch Edid for All HDMI Port
//                    UserCommonInterfaceHDMISwitchAllPortEdid();
//    #endif
//    
//    #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//                    // Switch All DP Port Edid
//                    UserCommonInterfaceDPSwitchAllPortEdid();
//    #endif
//    
//    #if(_FREESYNC_II_SUPPORT == _ON)
//                    UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_FREESYNC_ADJUST);
//                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//                OsdDispAdvanceMenuReDraw(_LOW);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//                if(g_usBackupValue != _OFF)
//                {
//                    g_usBackupValue = _OFF;
//                    OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, g_usBackupValue);
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//                if(g_usBackupValue != _ON)
//                {
//                    g_usBackupValue = _ON;
//                    OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, g_usBackupValue);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
//                {
//                    SET_OSD_FREE_SYNC_STATUS(g_usBackupValue);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_FREESYNC_ADJUST);
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//    void MenuAdvanceTypeCModeD0(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                g_usBackupValue = GET_OSD_D0_TYPEC_U3_MODE();
//                SET_OSD_STATE(_MENU_ADVANCE_D0_TYPEC_MODE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//    #endif
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPEC_U3_MODE());
//    #elif(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D2_TYPEC_U3_MODE());
//    #elif(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceTypeCModeD1(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                g_usBackupValue = GET_OSD_D1_TYPEC_U3_MODE();
//    
//                SET_OSD_STATE(_MENU_ADVANCE_D1_TYPEC_MODE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D2_TYPEC_U3_MODE());
//    #elif(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceTypeCModeD2(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                g_usBackupValue = GET_OSD_D2_TYPEC_U3_MODE();
//                SET_OSD_STATE(_MENU_ADVANCE_D2_TYPEC_MODE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPEC_U3_MODE());
//    #elif(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceTypeCModeD6(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    #if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                g_usBackupValue = GET_OSD_D6_TYPEC_U3_MODE();
//                SET_OSD_STATE(_MENU_ADVANCE_D6_TYPEC_MODE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D2_TYPEC_U3_MODE());
//    #elif(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPEC_U3_MODE());
//    #elif(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #endif
//    
//    #if(_HDR10_SUPPORT == _ON)
//    void MenuAdvanceHdrMode(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HDR_MODE();
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _SELECT, GET_OSD_HDR_MODE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//                if(UserCommonHDRGetHDR10Status() == _HDR10_OFF)
//                    return;
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceHdrDarkEnhanceOnOff(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_DARK_ENHANCE_STATUS();
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_MODE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    void MenuAdvanceHdrSharpnessOnOff(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HDR_SHARPNESS();
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_HDR_SHARPNESS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST, GET_OSD_HDR_CONTRAST());
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    void MenuAdvanceHdrContrast(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HDR_CONTRAST();
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_HDR_CONTRAST(), _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if((_HDR10_COLOR_ENHANCE_SUPPORT == _ON)||(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON))
//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST_1);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_COLOR_ENHANCE, GET_OSD_HDR_COLOR_ENHANCE());
//    #elif(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST_1);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LIGHT_ENHANCE, GET_OSD_HDR_LIGHT_ENHANCE());
//    #endif
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    void MenuAdvanceHdrColorEnhance(void)
//    {
//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HDR_COLOR_ENHANCE();
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _SELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LIGHT_ENHANCE, GET_OSD_HDR_LIGHT_ENHANCE());
//    #endif
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST, GET_OSD_HDR_CONTRAST());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    void MenuAdvanceHdrLightEnhance(void)
//    {
//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_HDR_LIGHT_ENHANCE();
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_COLOR_ENHANCE, GET_OSD_HDR_COLOR_ENHANCE());
//    #else
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST, GET_OSD_HDR_CONTRAST());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    
//    
//    
//    #endif
//    
//    void MenuAdvanceEdidAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_DP:
//                        SET_OSD_STATE(_MENU_ADVANCE_EDID_DX_ADJUST);
//                        OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_PRE_SELECT);
//                        g_usBackupValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue);
//                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
//                        break;
//    
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                    default:
//                        break;
//                }
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(g_usAdjustValue == 3)
//                {
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_1);
//                }
//    
//                if(g_usAdjustValue < 5) // D0-D6
//                {
//                    g_usAdjustValue++;
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                    {
//                        case _PORT_DP:
//                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_RESOLUTION);
//                            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
//                            break;
//    
//                        case _PORT_HDMI20:
//                        case _PORT_HDMI:
//                        case _PORT_MHL:
//                        default:
//                            break;
//                    }
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(g_usAdjustValue == 4)
//                {
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
//                }
//                if(g_usAdjustValue > 0) // D0-D6
//                {
//                    g_usAdjustValue--;
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                    {
//                        case _PORT_DP:
//                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_RESOLUTION);
//                            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
//                            break;
//    
//                        case _PORT_HDMI20:
//                        case _PORT_HDMI:
//                        case _PORT_MHL:
//                        default:
//                            break;
//                    }
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceEdidDXAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
//                OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_DP:
//                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, g_usBackupValue);
//                        if(g_usBackupValue != UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue))
//                        {
//                            UserCommonNVRamSetSystemData(_EDID_D0_SELECT + g_usAdjustValue, g_usBackupValue);
//                            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//    #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//                            UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT + g_usAdjustValue);
//    #endif
//                        }
//                        break;
//    
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                    default:
//                        break;
//                }
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_DP:
//                        if(g_usBackupValue < _DP_EDID_4K2K_60HZ)
//                        {
//                            g_usBackupValue++;
//                        }
//    
//                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
//                        break;
//    
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                    default:
//                        break;
//                }
//    
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_DP:
//                        if(g_usBackupValue > _DP_EDID_1080P)
//                        {
//                            g_usBackupValue--;
//                        }
//    
//                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
//                        break;
//    
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                    default:
//                        break;
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
//                OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_DP:
//                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
//                        break;
//    
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                    default:
//                        break;
//                }
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//    void MenuAdvanceHDMIVersionAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//    
//    #if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                        if(g_usAdjustValue == 0)
//                        {
//                            break;
//                        }
//    #endif
//    #if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                        if(g_usAdjustValue == 1)
//                        {
//                            break;
//                        }
//    #endif
//    #if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                        if(g_usAdjustValue == 2)
//                        {
//                            break;
//                        }
//    #endif
//    #if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                        if(g_usAdjustValue == 3)
//                        {
//                            break;
//                        }
//    #endif
//    #if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                        if(g_usAdjustValue == 4)
//                        {
//                            break;
//                        }
//    #endif
//    #if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                        if(g_usAdjustValue == 5)
//                        {
//                            break;
//                        }
//    #endif
//    
//                        SET_OSD_STATE(_MENU_ADVANCE_DX_HDMI_VERSION_ADJUST);
//                        OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_PRE_SELECT);
//                        g_usBackupValue = OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue);// UserCommonNVRamGetSystemData(_EDID_D0_SELECT + );
//                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _SELECT, g_usBackupValue);
//                        break;
//    
//                    default:
//                        break;
//                }
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(g_usAdjustValue == 3)
//                {
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_1);
//                }
//    
//                if(g_usAdjustValue < 5) // D0-D5
//                {
//                    g_usAdjustValue++;
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                    {
//                        case _PORT_HDMI20:
//                        case _PORT_HDMI:
//                        case _PORT_MHL:
//    #if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 0)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 1)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 2)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 3)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 4)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 5)
//                            {
//                                break;
//                            }
//    #endif
//                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_VERSIONS );
//                            OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
//                            break;
//                        default:
//                            break;
//                    }
//                }
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(g_usAdjustValue == 4)
//                {
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
//                }
//                if(g_usAdjustValue > 0) // D0-D6
//                {
//                    g_usAdjustValue--;
//                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                    switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                    {
//                        case _PORT_HDMI20:
//                        case _PORT_HDMI:
//                        case _PORT_MHL:
//    #if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 0)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 1)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 2)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 3)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 4)
//                            {
//                                break;
//                            }
//    #endif
//    #if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
//                            if(g_usAdjustValue == 5)
//                            {
//                                break;
//                            }
//    #endif
//                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_VERSIONS );
//                            OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
//                            break;
//                        default:
//                            break;
//                    }
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispAdvanceMenuReDraw(_HIGH);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDxHDMIVersionAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
//                OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, g_usBackupValue);
//                        if(g_usBackupValue != OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue))
//                        {
//                            //UserCommonNVRamSetSystemData(_EDID_D0_SELECT + g_usAdjustValue, g_usBackupValue);
//                            OsdFuncSetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue, g_usBackupValue);
//                            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//                            // Add EDID DDCRAM Switch & HPD event
//                            UserCommonInterfaceHDMISwitchEdid(_D0_INPUT_PORT + g_usAdjustValue, UserInterfaceGetMultiHdmiEdidIndex(_D0_INPUT_PORT + g_usAdjustValue));
//                        }
//                        break;
//                    default:
//                        break;
//                }
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                        if(g_usBackupValue < _EDID_INDEX_2)
//                        {
//                            g_usBackupValue++;
//                        }
//                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _SELECT, g_usBackupValue);
//                        break;
//                    default:
//                        break;
//                }
//    
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                        if(g_usBackupValue > _EDID_INDEX_0)
//                        {
//                            g_usBackupValue--;
//                        }
//                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _SELECT, g_usBackupValue);
//                        break;
//                    default:
//                        break;
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
//                OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
//                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
//                {
//                    case _PORT_HDMI20:
//                    case _PORT_HDMI:
//                    case _PORT_MHL:
//                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
//                        break;
//                    default:
//                        break;
//                }
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #endif
//    #if(_PIXEL_SHIFT_SUPPORT == _ON)
//    void MenuAdvancePixelShifAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                OsdDispAdvanceMenuReDraw(_LOW);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//    
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _ON);
//                UserAdjustPixelShifting();
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispAdvanceMenuReDraw(_LOW);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    #endif
//    #if (_SDR_TO_HDR_SUPPORT == _ON)
//    void MenuAdvanceSdrToHdrAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SDR_TO_HDR())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_SDR_TO_HDR() != _OFF)
//                {
//                    SET_OSD_SDR_TO_HDR(_OFF);
//                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_SDR_TO_HDR());
//                    UserAdjustSDRToHDR(_OFF);
//                }
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_SDR_TO_HDR() != _ON)
//                {
//                    SET_OSD_SDR_TO_HDR(_ON);
//                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_SDR_TO_HDR());
//                    UserAdjustSDRToHDR(_ON);
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SDR_TO_HDR())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_SDR_TO_HDR(g_usAdjustValue);
//                }
//    
//                OsdDispAdvanceMenuReDraw(_LOW);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #endif
//    
//    void MenuAudioVolumeAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_VOLUME())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_AUDIO_VOLUME);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME_ADJUST, GET_OSD_VOLUME());
//    
//                if((GET_OSD_VOLUME_MUTE() == _ON) && (g_usBackupValue == GET_OSD_VOLUME()))
//                {
//                    // RTDOsdDispOsdFunctionAdjust(_MENU_AUDIO_MUTE_ON_OFF);
//                    SET_OSD_VOLUME_MUTE(_OFF);
//                }
//    #if(_AUDIO_SUPPORT == _ON)
//                UserAdjustAudioVolume(GET_OSD_VOLUME());
//    #endif
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_VOLUME())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_VOLUME(g_usAdjustValue);
//    #if(_AUDIO_SUPPORT == _ON)
//                    UserAdjustAudioVolume(GET_OSD_VOLUME());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_AUDIO_VOLUME);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioMuteOnOff(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_AUDIO_MUTE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_AUDIO_MUTE_ON_OFF, GET_OSD_VOLUME_MUTE());
//    #if(_AUDIO_SUPPORT == _ON)
//                UserAdjustAudioMuteSwitch();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_VOLUME_MUTE(g_usAdjustValue);
//    #if(_AUDIO_SUPPORT == _ON)
//                    UserAdjustAudioMuteSwitch();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_AUDIO_MUTE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioStandAlongSelect(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_AUDIO_STAND_ALONE() == _ON)
//                {
//                    SET_OSD_AUDIO_STAND_ALONE(_OFF);
//                    OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_AUDIO_STAND_ALONE() == _OFF)
//                {
//                    SET_OSD_AUDIO_STAND_ALONE(_ON);
//                    OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_AUDIO_STAND_ALONE(g_usAdjustValue);
//                }
//                SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioAudioSourceSelect(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_AUDIO_AUDIO_SOURCE_SELECT, GET_OSD_AUDIO_SOURCE());
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
//                }
//                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAudioSoundModeSelect(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//    void MenuAudioAudioSelfTestSelect(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//            case _SELECT_KEY_MESSAGE:
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//                if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
//                    SysAudioInternalGenTestProc(_OFF);
//    #endif
//                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SELF_TEST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, _OFF);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(g_usBackupValue == _ON)
//                {
//                    g_usBackupValue = _OFF;
//                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
//                    SysAudioInternalGenTestProc(_OFF);
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(g_usBackupValue == _OFF)
//                {
//                    g_usBackupValue = _ON;
//                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _ON);
//    
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//                    SysAudioInternalGenTestProc(_ON);
//                    SysAudioMuteProc(_OFF);
//    #endif
//                }
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #endif
//    void MenuOtherMenuTimeAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_TIME_OUT())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME_ADJUST, GET_OSD_TIME_OUT());
//                ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_TIME_OUT())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_TIME_OUT(g_usAdjustValue);
//                    ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
//                }
//                SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherOsdHPosAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HPOS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS_ADJUST, GET_OSD_HPOS());
//                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HPOS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HPOS(g_usAdjustValue);
//                    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//                }
//                SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherOsdVPosAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_VPOS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS_ADJUST, GET_OSD_VPOS());
//                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_VPOS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_VPOS(g_usAdjustValue);
//                    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//                }
//                SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherLanguageAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_LANGUAGE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_OTHER_LANGUAGE_ADJUST, g_usAdjustValue);
//                if(g_usAdjustValue != GET_OSD_LANGUAGE())
//                {
//                    SET_OSD_LANGUAGE(g_usAdjustValue);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
//                    OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _SELECT, GET_OSD_LANGUAGE());
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_LANGUAGE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_LANGUAGE(g_usAdjustValue);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
//                }
//    
//                SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherTransparencyAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY_ADJUST, GET_OSD_TRANSPARENCY_STATUS());
//                OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
//                    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
//                }
//                SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuOtherRotateAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != g_usAdjustValue)
//                {
//                    SET_OSD_ROTATE_STATUS(g_usAdjustValue);
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_OTHER_ROTATE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_OTHER_ROTATE_ADJUST, GET_OSD_ROTATE_STATUS());
//                if(g_usAdjustValue != GET_OSD_ROTATE_STATUS())
//                {
//                    SET_OSD_ROTATE_STATUS(g_usAdjustValue);
//    #if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//                    OsdDispOsdRotateSwitch();
//    #endif
//                    OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_ROTATE_STATUS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_ROTATE_STATUS(g_usAdjustValue);
//    
//    #if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//                    OsdDispOsdRotateSwitch();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_OTHER_ROTATE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColortempUserR(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_R();
//    
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_R);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_R, GET_COLOR_TEMP_TYPE_USER_R());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
//                break;
//            case _LEFT_KEY_MESSAGE:
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = _CT_USER;
//                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
//                OsdDispClearSliderAndNumber();
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
//                OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColortempUserG(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_G();
//    
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_G, GET_COLOR_TEMP_TYPE_USER_G());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_B, GET_COLOR_TEMP_TYPE_USER_B());
//                break;
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = _CT_USER;
//                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
//                OsdDispClearSliderAndNumber();
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
//                OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorColortempUserB(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_B();
//    
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_B);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_B, GET_COLOR_TEMP_TYPE_USER_B());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = _CT_USER;
//                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
//                OsdDispClearSliderAndNumber();
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
//                OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColortempUserAdjustR(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_R, GET_COLOR_TEMP_TYPE_USER_R());
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_R(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColortempUserAdjustG(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_G, GET_COLOR_TEMP_TYPE_USER_G());
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_G(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColortempUserAdjustB(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_B, GET_COLOR_TEMP_TYPE_USER_B());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_B, GET_COLOR_TEMP_TYPE_USER_B());
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);
//    
//    #if(_CONTRAST_SUPPORT == _ON)
//                    UserAdjustContrast(GET_OSD_CONTRAST());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_B(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserR(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
//                SET_OSD_SIX_COLOR(_SIXCOLOR_R);
//                OsdDisplaySixColorGetOneColor(_SIXCOLOR_R);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//            case _LEFT_KEY_MESSAGE:
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_EFFECT();
//                SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserY(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
//                SET_OSD_SIX_COLOR(_SIXCOLOR_Y);
//                OsdDisplaySixColorGetOneColor(_SIXCOLOR_Y);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_EFFECT();
//                SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserG(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
//                SET_OSD_SIX_COLOR(_SIXCOLOR_G);
//                OsdDisplaySixColorGetOneColor(_SIXCOLOR_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_EFFECT();
//                SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorColorEffcUserC(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
//                SET_OSD_SIX_COLOR(_SIXCOLOR_C);
//                OsdDisplaySixColorGetOneColor(_SIXCOLOR_C);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_EFFECT();
//                SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserB(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
//                SET_OSD_SIX_COLOR(_SIXCOLOR_B);
//                OsdDisplaySixColorGetOneColor(_SIXCOLOR_B);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_EFFECT();
//                SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorColorEffcUserM(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
//                SET_OSD_SIX_COLOR(_SIXCOLOR_M);
//                OsdDisplaySixColorGetOneColor(_SIXCOLOR_M);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_COLOR_EFFECT();
//                SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
//                OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorColorEffcUserRHue(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//                OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserRSat(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//                OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserYHue(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//                OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserYSat(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//                OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserGHue(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//                OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserGSat(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//                OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorColorEffcUserCHue(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//                OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserCSat(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//                OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserBHue(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//                OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserBSat(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//                OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserMHue(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//                OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserMSat(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT_ADJUST);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//                OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSelectColor(_DOWN);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserRHueAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//    
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserRSatAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserYHueAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserYSatAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorColorEffcUserGHueAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserGSatAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuColorColorEffcUserCHueAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserCSatAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserBHueAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserBSatAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserMHueAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
//                {
//                    SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorEffcUserMSatAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                OsdFuncSixColorAdjust();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
//                {
//                    SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
//                    OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
//    #if(_SIX_COLOR_SUPPORT == _ON)
//                    OsdFuncSixColorAdjust();
//    #endif
//                }
//                SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_UP);
//                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
//    
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
//                OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuColorColorPCMSoftProftAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_PCM_SOFT_PROFT_MODE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_PCM_SOFT_PROFT_MODE() == _PCM_SOFT_MODE_1)
//                {
//                    SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_2);
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
//                    UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
//                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                    ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
//    #endif
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
//                }
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_PCM_SOFT_PROFT_MODE() == _PCM_SOFT_MODE_2)
//                {
//                    SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_1);
//    
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
//                    UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
//                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                    ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
//    #endif
//                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
//                }
//                break;
//    
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_PCM_SOFT_PROFT_MODE())
//                {
//                    SET_OSD_PCM_SOFT_PROFT_MODE(g_usBackupValue);
//                }
//                SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
//                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
//    
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuAdvanceODOnOffAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_OD_STATUS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_OD_STATUS() != _OFF)
//                {
//                    SET_OSD_OD_STATUS(_OFF);
//                    OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
//    #if(_OD_SUPPORT == _ON)
//                    ScalerODEnable(GET_OSD_OD_STATUS());
//    #endif
//                }
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_OD_STATUS() != _ON)
//                {
//                    SET_OSD_OD_STATUS(_ON);
//                    OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
//    #if(_OD_SUPPORT == _ON)
//                    ScalerODEnable(GET_OSD_OD_STATUS());
//    #endif
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_OD_STATUS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_OD_STATUS(g_usAdjustValue);
//    #if(_OD_SUPPORT == _ON)
//                    ScalerODEnable(GET_OSD_OD_STATUS());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuAdvanceODGainAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_OD_GAIN())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_ADVANCE_OD_GAIN_ADJUST, GET_OSD_OD_GAIN());
//    #if(_OD_SUPPORT == _ON)
//                ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_OD_GAIN())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_OD_GAIN(g_usAdjustValue);
//    #if(_OD_SUPPORT == _ON)
//                    ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
//    #endif // End of #if(_OD_SUPPORT == _ON)
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//    
//    
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDpD0VersionAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D0_VERSION())
//                {
//                    if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//    #if(_DP_SUPPORT == _ON)
//                    UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//    
//                    if(SysSourceGetInputPort() == _D0_INPUT_PORT)
//                    {
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//                    }
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if((GET_OSD_DP_D0_VERSION() + 1) > _DP_VER_AMOUNT)
//                {
//                    SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
//                }
//                else
//                {
//                    SET_OSD_DP_D0_VERSION(GET_OSD_DP_D0_VERSION() + 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
//                }
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
//                {
//                    SET_OSD_DP_D0_VERSION(_DP_VER_AMOUNT);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
//                }
//                else
//                {
//                    SET_OSD_DP_D0_VERSION(GET_OSD_DP_D0_VERSION() - 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D0_VERSION())
//                {
//                    SET_OSD_DP_D0_VERSION(g_usBackupValue);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    
//    void MenuAdvanceDpD1VersionAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D1_VERSION())
//                {
//                    if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//    #if(_DP_SUPPORT == _ON)
//                    UserCommonInterfaceDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//    
//                    if(SysSourceGetInputPort() == _D1_INPUT_PORT)
//                    {
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//                    }
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if((GET_OSD_DP_D1_VERSION() + 1) > _DP_VER_AMOUNT)
//                {
//                    SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
//                }
//                else
//                {
//                    SET_OSD_DP_D1_VERSION(GET_OSD_DP_D1_VERSION() + 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
//                }
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
//                {
//                    SET_OSD_DP_D1_VERSION(_DP_VER_AMOUNT);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
//                }
//                else
//                {
//                    SET_OSD_DP_D1_VERSION(GET_OSD_DP_D1_VERSION() - 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D1_VERSION())
//                {
//                    SET_OSD_DP_D1_VERSION(g_usBackupValue);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDpD2VersionAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D2_VERSION())
//                {
//                    if((GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//    #if(_DP_SUPPORT == _ON)
//                    UserCommonInterfaceDpVersionSwitch(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//    
//                    if(SysSourceGetInputPort() == _D2_INPUT_PORT)
//                    {
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//                    }
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if((GET_OSD_DP_D2_VERSION() + 1) > _DP_VER_AMOUNT)
//                {
//                    SET_OSD_DP_D2_VERSION(_DP_VER_1_DOT_1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
//                }
//                else
//                {
//                    SET_OSD_DP_D2_VERSION(GET_OSD_DP_D2_VERSION() + 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
//                }
//                break;
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1)
//                {
//                    SET_OSD_DP_D2_VERSION(_DP_VER_AMOUNT);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
//                }
//                else
//    
//                {
//                    SET_OSD_DP_D2_VERSION(GET_OSD_DP_D2_VERSION() - 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D2_VERSION())
//                {
//                    SET_OSD_DP_D2_VERSION(g_usBackupValue);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceDpD6VersionAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D6_VERSION())
//                {
//                    if((GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D6))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//    #if(_DP_SUPPORT == _ON)
//                    UserCommonInterfaceDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//    
//                    if(SysSourceGetInputPort() == _D6_INPUT_PORT)
//                    {
//                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//                    }
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if((GET_OSD_DP_D6_VERSION() + 1) > _DP_VER_AMOUNT)
//                {
//                    SET_OSD_DP_D6_VERSION(_DP_VER_1_DOT_1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
//                }
//                else
//                {
//                    SET_OSD_DP_D6_VERSION(GET_OSD_DP_D6_VERSION() + 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
//                }
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
//                {
//                    SET_OSD_DP_D6_VERSION(_DP_VER_AMOUNT);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
//                }
//                else
//    
//                {
//                    SET_OSD_DP_D6_VERSION(GET_OSD_DP_D6_VERSION() - 1);
//                    OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DP_D6_VERSION())
//                {
//                    SET_OSD_DP_D6_VERSION(g_usBackupValue);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//    void MenuAdvanceD0TypeCModeAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                if(g_usBackupValue != GET_OSD_D0_TYPEC_U3_MODE())
//                {
//                    if(g_usBackupValue == _TYPE_C_U3_ON)
//                    {
//                        SET_OSD_D0_TYPEC_U3_MODE(_TYPE_C_U3_ON);
//                    }
//                    else if(g_usBackupValue == _TYPE_C_U3_OFF)
//                    {
//                        SET_OSD_D0_TYPEC_U3_MODE(_TYPE_C_U3_OFF);
//                    }
//    
//                    UserCommonInterfaceTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT);
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, g_usBackupValue);
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//    
//                if(g_usBackupValue == _TYPE_C_U3_ON)
//                {
//                    g_usBackupValue = _TYPE_C_U3_OFF;
//                }
//                else
//                {
//                    g_usBackupValue = _TYPE_C_U3_ON;
//                }
//    
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceD1TypeCModeAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                if(g_usBackupValue != GET_OSD_D1_TYPEC_U3_MODE())
//                {
//                    if(g_usBackupValue == _TYPE_C_U3_ON)
//                    {
//                        SET_OSD_D1_TYPEC_U3_MODE(_TYPE_C_U3_ON);
//                    }
//                    else
//                    {
//                        SET_OSD_D1_TYPEC_U3_MODE(_TYPE_C_U3_OFF);
//                    }
//    
//    
//                    UserCommonInterfaceTypeCSetCapabilityChangeFlag(_D1_INPUT_PORT);
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, g_usBackupValue);
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(g_usBackupValue == _TYPE_C_U3_ON)
//                {
//                    g_usBackupValue = _TYPE_C_U3_OFF;
//                }
//                else
//                {
//                    g_usBackupValue = _TYPE_C_U3_ON;
//                }
//    
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPEC_U3_MODE());
//    #endif
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceD2TypeCModeAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                if(g_usBackupValue != GET_OSD_D2_TYPEC_U3_MODE())
//                {
//                    if(g_usBackupValue == _TYPE_C_U3_ON)
//                    {
//                        SET_OSD_D2_TYPEC_U3_MODE(_TYPE_C_U3_ON);
//                    }
//                    else
//                    {
//                        SET_OSD_D2_TYPEC_U3_MODE(_TYPE_C_U3_OFF);
//                    }
//    
//    
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, g_usBackupValue);
//    #endif
//    
//                break;
//    
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(g_usBackupValue == _TYPE_C_U3_ON)
//                {
//                    g_usBackupValue = _TYPE_C_U3_OFF;
//                }
//                else
//                {
//                    g_usBackupValue = _TYPE_C_U3_ON;
//                }
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D2_TYPEC_U3_MODE());
//    #endif
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceD6TypeCModeAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//    
//    #if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                if(g_usBackupValue != GET_OSD_D6_TYPEC_U3_MODE())
//                {
//                    if(g_usBackupValue == _TYPE_C_U3_ON)
//                    {
//                        SET_OSD_D6_TYPEC_U3_MODE(_TYPE_C_U3_ON);
//                    }
//                    else
//                    {
//                        SET_OSD_D6_TYPEC_U3_MODE(_TYPE_C_U3_OFF);
//                    }
//    
//                    UserCommonInterfaceTypeCSetCapabilityChangeFlag(_D6_INPUT_PORT);
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, g_usBackupValue);
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(g_usBackupValue == _TYPE_C_U3_ON)
//                {
//                    g_usBackupValue = _TYPE_C_U3_OFF;
//                }
//                else
//                {
//                    g_usBackupValue = _TYPE_C_U3_ON;
//                }
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _SELECT, g_usBackupValue);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//    
//    #if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//                OsdDispMainMenuOptionSetting(_OPTION_TYPEC_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPEC_U3_MODE());
//    #endif
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//    
//    #if(_HDR10_SUPPORT == _ON)
//    void MenuAdvanceHdrModeAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_MODE())
//                {
//                    if(((g_usBackupValue == _HDR10_MODE_OFF) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF)) ||
//                       ((g_usBackupValue != _HDR10_MODE_OFF) && (GET_OSD_HDR_MODE() == _HDR10_MODE_OFF)))
//                    {
//    #if(_EDID_HDR10_AUTO_SWITCH == _ON)
//    
//    #if((_HDMI_MULTI_EDID_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
//                        // Switch All HDMI Port Edid
//                        UserCommonInterfaceHDMISwitchAllPortEdid();
//    #endif
//    
//    #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//                        // Switch All DP Port Edid
//                        UserCommonInterfaceDPSwitchAllPortEdid();
//    #endif
//    
//    #if(_HDR10_SUPPORT == _ON)
//                        UserCommonHDR10SupportSwitch();
//    #endif
//    
//    #endif
//                    }
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());
//                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(((GET_OSD_HDR_MODE() == _HDR10_MODE_FORCE_2084) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
//                   ((GET_OSD_HDR_MODE() == _HDR10_MODE_OFF) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
//                {
//                }
//                else
//                {
//                    OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_MODE_ADJUST, GET_OSD_HDR_MODE());
//    
//                    UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_MODE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HDR_MODE(g_usAdjustValue);
//    
//                    UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuAdvanceHdrDarkEnhanceOnOffAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DARK_ENHANCE_STATUS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
//                {
//                    if(GET_OSD_DARK_ENHANCE_STATUS() != _OFF)
//                    {
//                        SET_OSD_DARK_ENHANCE_STATUS(_OFF);
//                        OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
//                    }
//                }
//                else
//                {
//                    if(GET_OSD_DARK_ENHANCE_STATUS() != _ON)
//                    {
//                        SET_OSD_DARK_ENHANCE_STATUS(_ON);
//                        OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
//                    }
//                }
//    
//                UserCommonHDRAdjust(_HDR_FLOW_OSD_DARK_ENHANCE);
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_DARK_ENHANCE_STATUS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_DARK_ENHANCE_STATUS(g_usAdjustValue);
//    
//                    UserCommonHDRAdjust(_HDR_FLOW_OSD_DARK_ENHANCE);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    void MenuAdvanceHdrSharpnessOnOffAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_SHARPNESS())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
//                {
//                    if(GET_OSD_HDR_SHARPNESS() != _OFF)
//                    {
//                        SET_OSD_HDR_SHARPNESS(_OFF);
//                        OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_HDR_SHARPNESS());
//                    }
//                }
//                else
//                {
//                    if(GET_OSD_HDR_SHARPNESS() != _ON)
//                    {
//                        SET_OSD_HDR_SHARPNESS(_ON);
//                        OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_HDR_SHARPNESS());
//                    }
//                }
//    
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//                UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_SHARPNESS())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HDR_SHARPNESS(g_usAdjustValue);
//    
//    #if(_ULTRA_VIVID_SUPPORT == _ON)
//                    UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceHdrContrastAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_CONTRAST())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST_ADJUST, GET_OSD_HDR_CONTRAST());
//    
//    #if((_CONTRAST_SUPPORT == _ON) && (_HDR10_SUPPORT == _ON))
//                UserCommonHDRAdjustHDR10Contrast(GET_OSD_HDR_CONTRAST());
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_CONTRAST())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HDR_CONTRAST(g_usAdjustValue);
//    
//    #if((_CONTRAST_SUPPORT == _ON) && (_HDR10_SUPPORT == _ON))
//                    UserCommonHDRAdjustHDR10Contrast(GET_OSD_HDR_CONTRAST());
//    #endif
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    void MenuAdvanceHdrColorEnhanceAdjust(void)
//    {
//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_COLOR_ENHANCE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST, GET_OSD_HDR_COLOR_ENHANCE());
//    
//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//                UserCommonHDRAdjustHDR10ColorEffect();
//    #endif
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_COLOR_ENHANCE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HDR_COLOR_ENHANCE(g_usAdjustValue);
//                }
//    
//    #if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
//                UserCommonHDRAdjustHDR10ColorEffect();
//    #endif
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_COLOR_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    void MenuAdvanceHdrLightEnhanceAdjust(void)
//    {
//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_LIGHT_ENHANCE())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST, GET_OSD_HDR_LIGHT_ENHANCE());
//    
//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//                UserCommonHDRAdjustHDR10ColorEffect();
//    #endif
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_HDR_LIGHT_ENHANCE())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_HDR_LIGHT_ENHANCE(g_usAdjustValue);
//                }
//    
//    #if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//                UserCommonHDRAdjustHDR10ColorEffect();
//    #endif
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_LIGHT_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                break;
//    
//            default:
//                break;
//        }
//    #endif
//    }
//    
//    
//    #endif
//    
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//    void MenuAdvanceHdrLDOnOff(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_LOCAL_DIMMING();
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_LOCAL_DIMMING());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                OsdDispClearSelectColor(_DOWN);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_LD_ADJ(), 100, 0, 50);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuAdvanceHdrLDSmoothAdj(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                g_usBackupValue = GET_OSD_OD_GAIN();
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispClearSliderAndNumber();
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
//                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//    
//                OsdDispAdvanceMenuReDraw(_HIGH);
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuAdvanceHdrLDOnOffAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_LOCAL_DIMMING())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                if(GET_OSD_LOCAL_DIMMING() != _OFF)
//                {
//                    SET_OSD_LOCAL_DIMMING(_OFF);
//                    OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_LOCAL_DIMMING());
//    #if(_LOCAL_DIMMING_SUPPORT == _ON)
//                    UserCommonLocalDimmingEnable(_DISABLE);
//                    UserAdjustBacklight(GET_OSD_BACKLIGHT());
//    #endif
//                }
//    
//                break;
//            case _LEFT_KEY_MESSAGE:
//    #if(_ASPECT_RATIO_SUPPORT == _ON)
//                if(GET_OSD_ASPECT_RATIO_TYPE() != _ASPECT_RATIO_FULL)
//                {
//                    break;
//                }
//    #endif
//    
//                if(GET_OSD_LOCAL_DIMMING() != _ON)
//                {
//                    SET_OSD_LOCAL_DIMMING(_ON);
//                    OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_LOCAL_DIMMING());
//    #if(_LOCAL_DIMMING_SUPPORT == _ON)
//                    UserCommonLocalDimmingEnable(_ENABLE);
//    #endif
//                }
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_LOCAL_DIMMING())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_LOCAL_DIMMING(g_usAdjustValue);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuAdvanceHdrLDSmoothAdjAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_LD_ADJ())
//                {
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_LD_ADJ(), 100, 0, 50);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST, GET_OSD_LD_ADJ());
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_LD_ADJ())
//                {
//                    g_usAdjustValue = g_usBackupValue;
//                    SET_OSD_LD_ADJ(g_usAdjustValue);
//                }
//                SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ);
//                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_LD_ADJ(), 100, 0, 50);
//                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
//                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
//                break;
//    
//            default:
//                break;
//        }
//    }
//    #endif
//    
//    void MenuHotKeyDdcci(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
//                {
//                    ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                }
//                else
//                {
//                    OsdDispDisableOsd();
//                }
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DDCCI);
//    
//                if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
//                {
//                    ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
//                {
//                    ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                }
//                else
//                {
//                    OsdDispDisableOsd();
//                }
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    void MenuHotKeySource(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(GET_OSD_DP_VERSION_HOTKEY_DISP() == _OFF)
//                {
//                    if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
//                    {
//                        switch(GET_OSD_INPUT_PORT_OSD_ITEM())
//                        {
//                            case _OSD_INPUT_AUTO: // auto
//    #if(_DP_MST_SUPPORT == _ON)
//                                if(GET_OSD_DP_MST() != _MST_OFF)
//                                {
//                                    SET_OSD_DP_MST(_MST_OFF);
//                                }
//    #endif
//                                SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
//                                {
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//    
//                                break;
//    
//                            case _OSD_INPUT_A0: // A0
//    #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_A0_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//                                break;
//    #else
//                                return;
//    #endif
//    
//    
//                            case _OSD_INPUT_D0: // D0
//    #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_D0_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//    
//                                break;
//    #else
//                                return;
//    #endif
//    
//                            case _OSD_INPUT_D1:    // D1
//    #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_D1_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//    
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//    
//                                break;
//    #else
//                                return;
//    #endif
//    
//                            case _OSD_INPUT_D2:    // D2
//    #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_D2_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//    
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//    
//                                break;
//    #else
//                                return;
//    #endif
//    
//                            case _OSD_INPUT_D3:    // D3
//    #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_D3_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//    
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//    
//                                break;
//    #else
//                                return;
//    #endif
//    
//                            case _OSD_INPUT_D4:    // D4
//    #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_D4_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//    
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//    
//                                break;
//    #else
//                                return;
//    #endif
//    
//                            case _OSD_INPUT_D5:    // D5
//    #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_D5_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//    
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//    
//                                break;
//    #else
//                                return;
//    #endif
//    
//                            case _OSD_INPUT_D6:    // D6
//    #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
//                                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                                SysSourceSwitchInputPort(_D6_INPUT_PORT);
//                                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//    
//                                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                                {
//                                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                                }
//                                break;
//    #else
//                                return;
//    #endif
//    
//                            default:
//                                break;
//                        }
//    
//    #if(_DP_MST_SUPPORT == _ON)
//                        UserCommonInterfaceMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
//                        RTDNVRamSaveOSDData();
//    #endif
//                    }
//                    else
//                    {
//                        if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
//                           (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
//                           (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
//                        {
//                            ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                        }
//                        else
//                        {
//                            OsdDispDisableOsd();
//                        }
//                    }
//                    SET_OSD_STATE(_MENU_NONE);
//                }
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//                SET_OSD_INPUT_PORT_OSD_ITEM(OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), 8, 0, _ON));
//                OsdDispHotKeySourceMenuSwitch();
//                if((GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D2) ||
//                   (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D6) ||
//                   (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO))
//                {
//                    OsdDispHotKeySourceMenuIcon();
//                }
//    
//                if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
//                {
//                    ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                }
//                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//                break;
//    
//            case _LEFT_KEY_MESSAGE:
//    
//                SET_OSD_INPUT_PORT_OSD_ITEM(OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), 8, 0, _ON));
//                OsdDispHotKeySourceMenuSwitch();
//                if((GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D5) ||
//                   (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D1) ||
//                   (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D6))
//                {
//                    OsdDispHotKeySourceMenuIcon();
//                }
//                if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
//                {
//                    ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                }
//                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//    
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
//                {
//                    SET_OSD_INPUT_PORT_OSD_ITEM(g_usBackupValue);
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
//                }
//    
//                if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
//                   (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
//                {
//                    ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                }
//                else
//                {
//                    OsdDispDisableOsd();
//                }
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuHotKeyDpOption(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _MENU_KEY_MESSAGE:
//                if(g_usAdjustValue == _HOTKEY_DP_D0_OPTION)
//                {
//    #if(_DP_SUPPORT == _ON)
//                    if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//                    SysSourceSwitchInputPort(_D0_INPUT_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    #endif
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D1_OPTION)
//                {
//    #if(_DP_SUPPORT == _ON)
//                    if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    UserCommonInterfaceDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//                    SysSourceSwitchInputPort(_D1_INPUT_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    #endif
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D6_OPTION)
//                {
//    #if(_DP_SUPPORT == _ON)
//                    if((GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D6))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    UserCommonInterfaceDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//                    SysSourceSwitchInputPort(_D6_INPUT_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    #endif
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D2_OPTION)
//                {
//    #if(_DP_SUPPORT == _ON)
//                    if((GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D6))
//                    {
//                        SET_OSD_DP_MST(_MST_OFF);
//                    }
//    
//                    UserCommonInterfaceDpVersionSwitch(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
//                    SysSourceSwitchInputPort(_D2_INPUT_PORT);
//                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    #endif
//                }
//    
//                SET_FORCE_POW_SAV_STATUS(_FALSE);
//                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
//                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
//    
//                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
//                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
//                {
//                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
//                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
//                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
//                }
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//    
//                if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
//                {
//                    ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
//                }
//    
//                if(g_usAdjustValue == _HOTKEY_DP_D0_OPTION)
//                {
//                    OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D0_OPTION);
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D1_OPTION)
//                {
//                    OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D1_OPTION);
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D2_OPTION)
//                {
//                    OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D2_OPTION);
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D6_OPTION)
//                {
//                    OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D6_OPTION);
//                }
//                break;
//    
//            case _SELECT_KEY_MESSAGE:
//                if(g_usAdjustValue == _HOTKEY_DP_D0_OPTION)
//                {
//    #if (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
//    #elif (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
//    #elif (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
//    #endif
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D1_OPTION)
//                {
//    #if (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
//    #elif (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
//    #elif (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
//    #endif
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D2_OPTION)
//                {
//    #if (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
//    #elif (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
//    #elif (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
//    #endif
//                }
//                else if(g_usAdjustValue == _HOTKEY_DP_D6_OPTION)
//                {
//    #if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
//    #elif (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
//    #elif (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
//                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
//    #endif
//                }
//                // SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_FALSE);
//                // OsdDispDisableOsd();
//                // SET_OSD_STATE(_MENU_HOT_INPUT_ADJUST);
//                // OsdDispHotKeySourceMenu();
//    
//                break;
//    
//            default:
//                break;
//        }
//    }
//    
//    
//    void MenuPanelUniformityMsgAdjust(void)
//    {
//        switch(GET_KEYMESSAGE())
//        {
//            case _SELECT_KEY_MESSAGE:
//                if(g_usAdjustValue != GET_OSD_PANEL_UNIFORMITY())
//                {
//                    SET_OSD_PANEL_UNIFORMITY(g_usAdjustValue);
//    
//    #if(_UNIFORMITY_SUPPORT == _ON)
//                    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        ScalerTimerWaitForEvent(_EVENT_DVS);
//                        ScalerTimerDelayXms(2);
//                        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
//    
//                        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
//                    }
//    #endif
//                }
//                break;
//    
//            case _MENU_KEY_MESSAGE:
//                RTDNVRamSaveOSDData();
//                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//                OsdFuncDisableOsd();
//                OsdFuncCloseWindow(_OSD_WINDOW_ALL);
//                OsdDispMainMenu();
//    
//                if(g_usBackupValue == _FROM_STATE_GAMMA)
//                {
//                    OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
//                    OsdDispMainMenuItemIndication(_ITEM_1, 9, _OSD_SELECT);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
//    
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        SET_OSD_STATE(_MENU_COLOR_GAMMA);
//                        OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                        OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
//                    }
//                    else
//                    {
//                        SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJUST);
//                        g_usBackupValue = GET_OSD_GAMMA();
//                        OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA());
//                    }
//    
//                    if(GET_OSD_GAMMA() == _GAMMA_24)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
//                    }
//                    else
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
//                    }
//                }
//                else if(g_usBackupValue == _FROM_STATE_PCM)
//                {
//                    OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
//                    OsdDispMainMenuItemIndication(_ITEM_7, 9, _OSD_SELECT);
//                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
//    
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        SET_OSD_STATE(_MENU_COLOR_PCM);
//                        OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
//                    }
//                    else
//                    {
//                        SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
//                        g_usBackupValue = GET_OSD_PCM_STATUS();
//                        OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
//                    }
//    
//    #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
//                    if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
//                    }
//                    else
//    #endif
//                    {
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
//                    }
//                }
//    #if(_HDR10_SUPPORT == _ON)
//                else if(g_usBackupValue == _FROM_STATE_HDR)
//                {
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        OsdDispAdvanceMenuReDraw(_HIGH);
//                    }
//                    else
//                    {
//                        OsdDispAdvanceMenuReDraw(_HIGH);
//                    }
//                }
//    #endif
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//                else if(g_usBackupValue == _FROM_STATE_LD)
//                {
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        OsdDispAdvanceMenuReDraw(_HIGH);
//                    }
//                    else
//                    {
//                        //OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
//                        //OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
//                        SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
//                        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
//                        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_LOCAL_DIMMING);
//                        OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
//                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
//                        OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
//                    }
//                }
//    #endif
//    #if(_SDR_TO_HDR_SUPPORT == _ON)
//                else if(g_usBackupValue == _FROM_STATE_SDRTOHDR)
//                {
//                    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                    {
//                        OsdDispAdvanceMenuReDraw(_HIGH);
//                    }
//                    else
//                    {
//                        OsdDispAdvanceMenuReDraw(_HIGH);
//                    }
//                }
//    #endif
//    
//                break;
//    
//            case _RIGHT_KEY_MESSAGE:
//            case _LEFT_KEY_MESSAGE:
//                OsdDispPanelUniformityMsgSwitch();
//    
//    #if(_UNIFORMITY_SUPPORT == _ON)
//                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
//                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
//                {
//                    ScalerTimerWaitForEvent(_EVENT_DVS);
//                    ScalerTimerDelayXms(2);
//                    UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
//    
//                    ScalerColorPanelUniformityEnable(_FUNCTION_ON);
//                }
//    #endif
//                break;
//    
//            default:
//                break;
//        }
//    }
//Eric_20180306_Delete : End --------------------------------- 

code void (*OperationTable[])(void) =
{
    MenuNone,

    // main
    MenuPicture,
    MenuColor,
    MenuOsdSettings,
    MenuSetup,
    MenuOther,
	MenuService,
    
    // picture
    MenuPictureBacklight,
	MenuPictureBrightness,
    MenuPictureContrast,
	MenuPictureSharpness,
	MenuPictureHue,
	MenuPictureSaturation,
#if (_ENABLE_MENU_OLED == _ON)
    MenuPictureOLEDSettings,
	MenuPictureOLED_OffRs,
	MenuPictureOLED_JB,
#endif
  
    // color
    MenuColorTemperature,
    MenuColortempUserR,
    MenuColortempUserG,
    MenuColortempUserB,
#if (_HDR10_SUPPORT == _ON)
	MenuColorHDR,
#endif
	MenuColorECO,
	MenuColorGamma,


   //OSD Settings
    MenuOsdSettingsLanguage,
    MenuOsdSettingsHPos,
    MenuOsdSettingsVPos,
    MenuOsdSettingsTransparency,
    MenuOsdSettingsMenuTime,
	MenuOsdSettingsRotate,

   //Setup 
    MenuSetupInput,
	MenuSetupAudioMute,
	MenuSetupAudio,
	MenuSetupDPFormat,
	MenuSetupDPMST,
	MenuSetupCloneMode,
    MenuSetupReset,

  //Others
    MenuOthersDisplaySize,
	MenuOthersDisplayRotate,
#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
    MenuOthersLowBlueLight,
#endif
#if(_OD_SUPPORT == _ON)
    MenuOthersOverDrive,
#endif

#if(_ENABLE_VIDEO_WALL == _ON)
	MenuOthersVideoWallSettings,
	MenuOthersVideoWall,
	MenuOthersVideoWall_DispNum,
	MenuOthersVideoWall_HNum,
	MenuOthersVideoWall_VNum,
	MenuOthersVideoWall_RS232Id,
#endif

#if (_ENABLE_LIGHT_SENSOR == _ON)
	MenuOthersLightSensor,
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
	MenuOthersFanControls,
	MenuOthersFan,
	MenuOthersFanPWM1,
	MenuOthersFanPWM2,
	MenuOthersFanPWM3,
	MenuOthersFanPWM4,
	MenuOthersShutDown,
	MenuOthersShutDownTemp,
	MenuOthersTemperature,
#endif

#if (_ENABLE_SELF_CHECK == _ON)
	MenuOthersSelfCheck,
#endif

#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
	MenuOthersALCW,
#endif
    MenuOthersFreeSync,

	MenuServiceBacklightPwmRes,
	MenuServiceBacklightControl,
	//MenuServicePixelShift,
	//MenuServicePixelShiftTime,
	//MenuServiceBacklightInvert,
	//MenuServiceBacklightFreq,

    // picture adjust
    MenuPictureBacklightAdjust,
	MenuPictureBrightnessAdjust,
    MenuPictureContrastAdjust,
	MenuPictureSharpnessAdjust,
	MenuPictureHueAdjust,
	MenuPictureSaturationAdjust,
#if (_ENABLE_MENU_OLED == _ON)
	MenuPictureOLED_OffRsAdj,
	MenuPictureOLED_JBAdj,
#endif

    //color
    MenuColortempAdjust,
    MenuColortempUserAdjustR,
    MenuColortempUserAdjustG,
    MenuColortempUserAdjustB,
#if (_HDR10_SUPPORT == _ON)
    MenuColorHDRAdjust,
#endif
	MenuColorECOAdjust,
	MenuColorGammaAdjust,

   //Osd Setting 
    MenuOsdSettingsLanguageAdjust,
    MenuOsdSettingsHPosAdjust,
    MenuOsdSettingsVPosAdjust,
    MenuOsdSettingsTransparencyAdjust,
    MenuOsdSettingsMenuTimeAdjust,
	MenuOsdSettingsRotateAdjust,
  ///
#if 0
    MenuHotkeyECOAdjust,
    
 //   MenuHotkeyGameArm,	
    MenuLeftKeyGame,
   // MenuHotkeyGameArmAdjust,
    MenuLeftKeyGameAdjust,
    MenuLeftKeyTimer,
    MenuLeftKeyTimerAdjust,
    OsdDispLeftTimerMenu,
    OsdDispLeftTimerMenuAdjust,
    OsdDispLeftTimerMenuPosition,
#endif

    //setup
    MenuSetupInputAdjust,
	MenuSetupAudioMuteonoff,
    MenuSetupAudioAdjust,
	MenuSetupDPFormatAdj,
	MenuSetupDPMSTAdj,
	MenuSetupCloneModeAdj,

   //others
    MenuOthersDisplaySizeAdjust,
	MenuOthersDisplayRotateAdjust,
#if(_USER_FUNCTION_LOW_BLUE_LIGHT==_ON)
    MenuOthersLowBlueLightAdjust,
#endif
#if(_OD_SUPPORT == _ON)        	    
    MenuOthersOverDriveAdjust,
#endif

#if(_ENABLE_VIDEO_WALL == _ON)
	MenuOthersVideoWallAdj,
	MenuOthersVideoWall_DispNumAdj,
	MenuOthersVideoWall_HNumAdj,
	MenuOthersVideoWall_VNumAdj,
	MenuOthersVideoWall_RS232IdAdj,
#endif

#if (_ENABLE_LIGHT_SENSOR == _ON)
	MenuOthersLightSensorAdj,
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
	MenuOthersFanAdj,
	MenuOthersFanPWM1Adj,
	MenuOthersFanPWM2Adj,
	MenuOthersFanPWM3Adj,
	MenuOthersFanPWM4Adj,
	MenuOthersShutDownAdj,
	MenuOthersShutDownTempAdj,
#endif

#if (_ENABLE_SELF_CHECK == _ON)
	MenuOthersSelfCheckAdj,
#endif

#if (_AUO_PANEL_ALCW_SUPPORT == _ON)
	MenuOthersALCWAdjust,
#endif
    MenuOthersFreeSyncAdjust,

	MenuServiceBacklightPwmResAdj,
	MenuServiceBacklightControlAdj,
	//MenuServicePixelShiftAdj,
	//MenuServicePixelShiftTimeAdj,
	//MenuServiceBacklightInvertAdj,
	//MenuServiceBacklightFreqAdj,

	MenuHotInputAdjust,


    MenuHotKeyVolume, //170928_02
    MenuHotKeyMute,
    MenuHotKeyAudioMode, //Eric_171010_01
    MenuHotKeyPictureMode, //Eric_171010_01

    // ask turn off/on panel uniformity msg
#if 0
    MenuConnectBluetoothAdjust,
    MenuDisconnectBluetoothAdjust,	
#endif
	MenuHotKeyBacklight,
	MenuHotKeySource,
//Eric_20180306_Delete : Start --------------------------------- 
//    
//        // main
//        MenuPicture,
//        MenuDisplay,
//        MenuColor,
//        MenuAdvance,
//        MenuInput,
//        MenuAudio,
//        MenuOther,
//        MenuInformation,
//        MenuFactory,
//    
//        // picture
//        MenuPictureBacklight,
//        MenuPictureBrightness,
//        MenuPictureContrast,
//        MenuPictureSharpness,
//    
//        // display
//        MenuDisplayAuto,
//        MenuDisplayHPos,
//        MenuDisplayVPos,
//        MenuDisplayClock,
//        MenuDisplayPhase,
//        MenuDisplayDispRotate,
//        MenuDisplayLatency,
//        MenuDislayFreeze,
//    
//        // color
//        MenuColorPanelUniformity,
//        MenuColorGamma,
//        MenuColorTemperature,
//        MenuColorEffect,
//        MenuColorDemo,
//        MenuColorFormat,
//        MenuColorPCM,
//        MenuColorHue,
//        MenuColorSaturation,
//    
//        // advance
//        MenuAdvanceItem,
//    
//        // input
//        MenuInputAuto,
//        MenuInputA0Port,
//        MenuInputD0Port,
//        MenuInputD1Port,
//        MenuInputD2Port,
//        MenuInputD3Port,
//        MenuInputD4Port,
//        MenuInputD5Port,
//        MenuInputD6Port,
//    
//        // audio
//        MenuAudioVolume,
//        MenuAudioMute,
//        MenuAudioStandAlong,
//        MenuAudioAudioSource,
//        MenuAudioSoundMode,
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//        MenuAudioAudioSelfTest,
//    #endif
//        // other
//        MenuOtherReset,
//        MenuOtherMenuTime,
//        MenuOtherOsdHPos,
//        MenuOtherOsdVPos,
//        MenuOtherLanguage,
//        MenuOtherTransparency,
//        MenuOtherRotate,
//    
//        // picture adjust
//        MenuPictureBacklightAdjust,
//        MenuPictureBrightnessAdjust,
//        MenuPictureContrastAdjust,
//        MenuPictureSharpnessAdjust,
//    
//        // display adjust
//        MenuDisplayHPosAdjust,
//        MenuDisplayVPosAdjust,
//        MenuDisplayClockAdjust,
//        MenuDisplayPhaseAdjust,
//        MenuDisplayDispRotateAdjust,
//        MenuDisplayLatencyAdjust,
//        MenuDisplayFreezeAdjust,
//    
//        // color adjust
//        MenuColorPanelUniformityAdjust,
//        MenuColorGammaAdjust,
//        MenuColorColorTempAdjust,
//        MenuColorColorEffectAdjust,
//        MenuColorColorDemoAdjust,
//        MenuColorColorFormatAdjust,
//        MenuColorColorPCMAdjust,
//        MenuColorColorHueAdjust,
//        MenuColorColorSaturationAdjust,
//    
//        // advance adjust
//        MenuAdvanceAspectAdjust,
//        MenuAdvanceOverScanAdjust,
//        MenuAdvanceOverDriveOnOff,
//        MenuAdvanceOverDriveGain,
//        MenuAdvanceDCRAdjust,
//        MenuAdvanceDdcciAdjust,
//        MenuAdvanceUltraVividAdjust,
//        MenuAdvanceDpOptionD0,
//        MenuAdvanceDpOptionD1,
//        MenuAdvanceDpOptionD2,
//        MenuAdvanceDpOptionD6,
//        MenuAdvanceDPMstAdjust,
//        MenuAdvanceDPEdidAdjust,
//        MenuAdvanceCloneAdjust,
//        MenuAdvanceFreeSyncAdjust,
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//        MenuAdvanceTypeCModeD0,
//        MenuAdvanceTypeCModeD1,
//        MenuAdvanceTypeCModeD2,
//        MenuAdvanceTypeCModeD6,
//    #endif
//    
//    #if(_HDR10_SUPPORT == _ON)
//        MenuAdvanceHdrMode,
//        MenuAdvanceHdrDarkEnhanceOnOff,
//        MenuAdvanceHdrSharpnessOnOff,
//        MenuAdvanceHdrContrast,
//        MenuAdvanceHdrColorEnhance,
//        MenuAdvanceHdrLightEnhance,
//    #endif
//        MenuAdvanceEdidAdjust,
//        MenuAdvanceEdidDXAdjust,
//    #if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//        MenuAdvanceHDMIVersionAdjust,
//        MenuAdvanceDxHDMIVersionAdjust,
//    #endif
//    #if(_PIXEL_SHIFT_SUPPORT == _ON)
//        MenuAdvancePixelShifAdjust,
//    #endif
//    #if (_SDR_TO_HDR_SUPPORT == _ON)
//        MenuAdvanceSdrToHdrAdjust,
//    #endif
//    
//        // Audio adjust
//        MenuAudioVolumeAdjust,
//        MenuAudioMuteOnOff,
//        MenuAudioStandAlongSelect,
//        MenuAudioAudioSourceSelect,
//        MenuAudioSoundModeSelect,
//    #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//        MenuAudioAudioSelfTestSelect,
//    #endif
//    
//        // other adjust
//        MenuOtherMenuTimeAdjust,
//        MenuOtherOsdHPosAdjust,
//        MenuOtherOsdVPosAdjust,
//        MenuOtherLanguageAdjust,
//        MenuOtherTransparencyAdjust,
//        MenuOtherRotateAdjust,
//    
//        // color temp user RGB
//        MenuColorColortempUserR,
//        MenuColorColortempUserG,
//        MenuColorColortempUserB,
//    
//        // color temp user adjust RGB
//        MenuColorColortempUserAdjustR,
//        MenuColorColortempUserAdjustG,
//        MenuColorColortempUserAdjustB,
//    
//        // color effect user adjust
//        MenuColorColorEffcUserR,
//        MenuColorColorEffcUserY,
//        MenuColorColorEffcUserG,
//        MenuColorColorEffcUserC,
//        MenuColorColorEffcUserB,
//        MenuColorColorEffcUserM,
//    
//        MenuColorColorEffcUserRHue,
//        MenuColorColorEffcUserRSat,
//    
//        MenuColorColorEffcUserYHue,
//        MenuColorColorEffcUserYSat,
//    
//        MenuColorColorEffcUserGHue,
//        MenuColorColorEffcUserGSat,
//    
//        MenuColorColorEffcUserCHue,
//        MenuColorColorEffcUserCSat,
//    
//        MenuColorColorEffcUserBHue,
//        MenuColorColorEffcUserBSat,
//    
//        MenuColorColorEffcUserMHue,
//        MenuColorColorEffcUserMSat,
//    
//        // color effect user adjust Hue & Sat
//        MenuColorColorEffcUserRHueAdjust,
//        MenuColorColorEffcUserRSatAdjust,
//    
//        MenuColorColorEffcUserYHueAdjust,
//        MenuColorColorEffcUserYSatAdjust,
//    
//        MenuColorColorEffcUserGHueAdjust,
//        MenuColorColorEffcUserGSatAdjust,
//    
//        MenuColorColorEffcUserCHueAdjust,
//        MenuColorColorEffcUserCSatAdjust,
//    
//        MenuColorColorEffcUserBHueAdjust,
//        MenuColorColorEffcUserBSatAdjust,
//    
//        MenuColorColorEffcUserMHueAdjust,
//        MenuColorColorEffcUserMSatAdjust,
//    
//        MenuColorColorPCMSoftProftAdjust,
//    
//        MenuAdvanceODOnOffAdjust,
//        MenuAdvanceODGainAdjust,
//    
//        MenuAdvanceDpD0VersionAdjust,
//        MenuAdvanceDpD1VersionAdjust,
//        MenuAdvanceDpD2VersionAdjust,
//        MenuAdvanceDpD6VersionAdjust,
//    
//    #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
//        MenuAdvanceD0TypeCModeAdjust,
//        MenuAdvanceD1TypeCModeAdjust,
//        MenuAdvanceD2TypeCModeAdjust,
//        MenuAdvanceD6TypeCModeAdjust,
//    #endif
//    
//    #if(_HDR10_SUPPORT == _ON)
//        MenuAdvanceHdrModeAdjust,
//        MenuAdvanceHdrDarkEnhanceOnOffAdjust,
//        MenuAdvanceHdrSharpnessOnOffAdjust,
//        MenuAdvanceHdrContrastAdjust,
//        MenuAdvanceHdrColorEnhanceAdjust,
//        MenuAdvanceHdrLightEnhanceAdjust,
//    #endif
//    #if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
//        MenuAdvanceHdrLDOnOff,
//        MenuAdvanceHdrLDSmoothAdj,
//        MenuAdvanceHdrLDOnOffAdjust,
//        MenuAdvanceHdrLDSmoothAdjAdjust,
//    #endif
//    
//        // ddcci
//        MenuHotKeyDdcci,
//    
//        // hotkey source
//        MenuHotKeySource,
//    
//        // hotkey dp version
//        MenuHotKeyDpOption,
//    
//        // ask turn off/on panel uniformity msg
//        MenuPanelUniformityMsgAdjust,
//Eric_20180306_Delete : End --------------------------------- 

};

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
