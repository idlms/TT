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
// ID Code      : RTD2014Key.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_KEY__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Key Mask
//--------------------------------------------------
#define _RELEASE_KEY_MASK                           0x00
#define _POWER_KEY_MASK                             0x80
#define _MENU_KEY_MASK                              0x01
#define _RIGHT_KEY_MASK                             0x02
#define _LEFT_KEY_MASK                              0x03
#define _EXIT_KEY_MASK                              0x04
#define _UP_KEY_MASK                                0x05	
#define _DOWN_KEY_MASK                              0x06
#define _SOURCE_KEY_MASK                            0x07
#define _SELECT_KEY_MASK                           	0x08	

#define _MUTE_KEY_MASK                           	0x09	
#define _FUNC_KEY_MASK                           	0x0A
#define _F1_KEY_MASK                           		0x0B
#define _F2_KEY_MASK                           		0x0C
#define _F3_KEY_MASK                           		0x0D
#define _VOL_P_KEY_MASK                           	0x0E	
#define _VOL_M_KEY_MASK                           	0x0F

#define _IR_UP_KEY_MASK                        		0x10	
#define _IR_DOWN_KEY_MASK                      		0x12


#define _POWER_RIGHT_KEY_MASK                       (_POWER_KEY_MASK | _RIGHT_KEY_MASK)
#define _POWER_MENU_KEY_MASK                        (_POWER_KEY_MASK | _MENU_KEY_MASK)
#define _POWER_LEFT_RIGHT_KEY_MASK                  (_POWER_KEY_MASK | _LEFT_KEY_MASK | _RIGHT_KEY_MASK)

//--------------------------------------------------
// Definitions of IR Key Code
//--------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
#if(_IR_PROTOCAL == _IR_NEC_DTV328)

#define _IR_CODE_KEY_POWER                          0x8412//0x0408 // IR Code ( custom(79) << 8 | data(84) ) 
#define _IR_CODE_KEY_MENU                           0x8432//0x0443 // MENU 84 79 32 CD
#define _IR_CODE_KEY_RIGHT                          0x8409//0x0406
#define _IR_CODE_KEY_LEFT                           0x8407//0x0407
//#define _IR_CODE_KEY_EXIT                           0x7796//0x045B
#define _IR_CODE_KEY_SELECT                         0x8408//0x045B	// OK button

#define _IR_CODE_KEY_FUNC                      	   	0x8433
#define _IR_CODE_KEY_UP                        	   	0x8405
#define _IR_CODE_KEY_DOWN                         	0x8400
#define _IR_CODE_KEY_SOURCE                         0x8434
#define _IR_CODE_KEY_MUTE                           0x8431
#define _IR_CODE_KEY_F1                           	0x841B
#define _IR_CODE_KEY_F2                           	0x8406
#define _IR_CODE_KEY_F3                           	0x841A

#define _IR_CODE_KEY_VOL_P                          0x8410
#define _IR_CODE_KEY_VOL_M                          0x840F

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
#define _IR_CODE_KEY_POWER                          0x0950
#define _IR_CODE_KEY_MENU                           0x0A50
#define _IR_CODE_KEY_RIGHT                          0x0920
#define _IR_CODE_KEY_LEFT                           0x0930
#define _IR_CODE_KEY_EXIT                           0x0940

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
#define _IR_CODE_KEY_POWER                          0x000C
#define _IR_CODE_KEY_MENU                           0x005C
#define _IR_CODE_KEY_RIGHT                          0x005B
#define _IR_CODE_KEY_LEFT                           0x005A
#define _IR_CODE_KEY_EXIT                           0x000A

#endif
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
BYTE g_ucKeyStatePrev;
BYTE g_ucKeyStateCurr;
BYTE g_ucKeyStateSkip;
BYTE g_ucKeyRs232;	

#if(_AD_KEY_SUPPORT == _ON)
BYTE g_ucBackupKeyState = 0xFF;
#endif

BYTE patternIndex = 0;
BYTE pattern2Index = 0;
BYTE pattern[5] = {1, 1, 0, 1, 0};
BYTE pattern2[5] = {0, 0, 1, 0, 1};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceKeyHandler(void);
void RTDKeyInitial(void);
bit RTDKeyScanReady(void);
BYTE RTDKeyScan(void);
bit RTDKeyPowerKeyProc(void);
void RTDKeyPowerKeyMix(void);
void RTDKeyMessageProc(void);
void RTDKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg);


void RTDKeyHoldKeyTimerCancel(void);
void RTDKeyHoldKeyCheck(void);


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE RTDIRKeyScan(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Key Handler, executed in the main loop.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyHandler(void)
{
    // Skip key status update for tool
    if(g_ucKeyStateSkip != 0)
    {
        g_ucKeyStateSkip = 0;
        return;
    }

    // Clear the key message
    //if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)	//  Not used _HOLD_KEY_MESSAGE
    {
        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
    }

    if(RTDKeyScanReady() == _TRUE)
    {
        // Store previous key state
        g_ucKeyStatePrev = g_ucKeyStateCurr;

        // Get current key state
        g_ucKeyStateCurr = RTDKeyScan();

        // Power key process, return if power key is pressed
        if(RTDKeyPowerKeyProc() == _TRUE)
        {
            return;
        }

        // Convert key state to key message, store in (ucKeyNotify)
        RTDKeyMessageProc();
    }
}

//--------------------------------------------------
// Description  : Key intial.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyInitial(void)
{
    CLR_KEYSCANREADY();
    CLR_KEYSCANSTART();
}

//--------------------------------------------------
// Description  : Key scan ready process. We wait 0.02 sec in order to keep the keypad debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDKeyScanReady(void)
{
    if((GET_KEYSCANSTART() == _TRUE) &&
       (GET_KEYSCANREADY() == _TRUE))
    {
        return _TRUE;
    }
    else if(GET_KEYSCANSTART() == _FALSE)
    {
        // Set Scan start flag.
        SET_KEYSCANSTART();

        // SET_KEYSCANREADY();
        // Wait 0.02 sec in order to keep the keypad debounce
        ScalerTimerReactiveTimerEvent(SEC(0.02), _USER_TIMER_EVENT_KEY_SCAN_READY);	

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE RTDKeyScan(void)
{
    BYTE ucKeyState = 0;
    BYTE ucVoltage0 = 0;
    BYTE ucVoltage1 = 0;
    BYTE ucVoltage2 = 0;
    BYTE ucVoltage3 = 0;
	
	static BYTE BkucVoltage1 = 0;
    static BYTE BkucVoltage2 = 0;

#if(_AD_KEY_SUPPORT == _ON)
    //ucVoltage0 = PCB_ADKEY0();
    ucVoltage1 = PCB_ADKEY1();
    ucVoltage2 = PCB_ADKEY2();
    //ucVoltage3 = PCB_ADKEY3();

    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);

	/* // Key debug
	if(BkucVoltage1 != ucVoltage1)	//  Key ADC Debug
	{
		BkucVoltage1 = ucVoltage1;
		printf("ucVoltage1:%X \n\r",(int)ucVoltage1);
	}
	if(BkucVoltage2 != ucVoltage2)
	{
		BkucVoltage2 = ucVoltage2;
		printf("ucVoltage2:%X \n\r",(int)ucVoltage2);
	}
	*/
	if(BkucVoltage1 != ucVoltage1)	
	{
		BkucVoltage1 = ucVoltage1;
		//DebugMessageOsd("ADC0_KEY", ucVoltage1);	
	}
	if(BkucVoltage2 != ucVoltage2)
	{
		BkucVoltage2 = ucVoltage2;
		//DebugMessageOsd("ADC1_KEY", ucVoltage2);
	}

	//----------------------------------------------
	
    if((g_ucBackupKeyState == ucKeyState) && (ucKeyState != 0))
    {
        if(GET_KEYREPEATENABLE() != _ON)
        {
            RTDKeyInitial();
        }

        return g_ucBackupKeyState;
    }
    else
    {
        g_ucBackupKeyState = ucKeyState;
        ucKeyState = 0;
    }

#else
    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);
#endif // End of #if(_AD_KEY_SUPPORT == _ON)

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    if(ucKeyState == 0x00)
    {
        ucKeyState = RTDIRKeyScan();
    }
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

    if(ucKeyState != 0)
    {
        RTDKeyInitial();
    }

    return ucKeyState;
}

extern void SicpIrTransferSend(BYTE ucId, BYTE uc08, BYTE uc09, BYTE uc10 ); 

//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit RTDKeyPowerKeyProc(void)
{
    if((g_ucKeyStateCurr & _POWER_KEY_MASK) != 0)
    {
        if(((g_ucKeyStatePrev ^ g_ucKeyStateCurr) & _POWER_KEY_MASK) != 0)
        {
            RTDKeyPowerKeyMix();

            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
#if (_ENABLE_MENU_OLED == _ON)
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_POWER_OFF_OFFRS_RUN);
				CancelWaitingToRunOFFRS(); //When turn on with Power BTN, Dont Start OFFRS
#endif				
                SET_OSD_STATE(_MENU_NONE);
                SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
            }
            else
            {
#if (_ENABLE_MENU_OLED == _ON)
				if(GET_OSD_OLED_OFFRS_STATUS() == _OFFRS_END_RUN)
				{
					if( GET_OSD_STATE() == _MENU_HOTKEY_OFFRS)
					{
						OsdDispDisableOsd();
						ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_POWER_OFF);
						SET_WAIT_TO_RUN_OFFRS(_ON);

						if (GetWaitingToRunOFFRS() == _ON)// && GET_OSD_OLED_OFFRS_STATUS() != _OFFRS_START_RUN) // OFF_RS Auto Run or Start Run.
						{
							_bPowerOnOffRS = _FALSE;
							OsdDispOsdMessage(_OSD_DISP_OFF_RS_MSG);
							ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_OFF_RS_RUN);
							SET_COMP_RUN_RESTART(_OFF);
						}
					}
					else // 
					{
						OsdDispDisableOsd();
						SET_OSD_STATE(_MENU_HOTKEY_OFFRS);
						g_usBackupValue = _TRUE;
						OsdDispHotKeyOffRSMenu();
						ScalerTimerActiveTimerEvent(SEC(10), _USER_TIMER_EVENT_OSD_POWER_OFF);
						/*
						SET_WAIT_TO_RUN_OFFRS(_ON);
				
						if (GetWaitingToRunOFFRS() == _ON)// && GET_OSD_OLED_OFFRS_STATUS() != _OFFRS_START_RUN) // OFF_RS Auto Run or Start Run.
						{
							DebugMessageOsd("T:^^^ IR PowerKey Off RS => PowerOff ^^^", g_ucKeyStateCurr);

							OsdDispOsdMessage(_OSD_DISP_OFF_RS_MSG);
							ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_OFF_RS_RUN);
							SET_COMP_RUN_RESTART(_OFF);
							
						}*/
					}
				}
				else if(GET_OSD_OLED_OFFRS_STATUS() == _OFFRS_AUTO)
				{
					if (GetWaitingToRunOFFRS() == _ON)
					{
						OsdDispDisableOsd();
						OsdDispOsdMessage(_OSD_DISP_OFF_RS_PWR_SUPPLY_MSG);
						DebugMessageOsd("T:_OSD_DISP_OFF_RS_PWR_SUPPLY_MSG", GetWaitingToRunOFFRS());
						ScalerTimerActiveTimerEvent(SEC(10), _USER_TIMER_EVENT_OSD_POWER_OFF);
					}
					else
						SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
				}
				else //if(GetOffRSStatus()==_OFF)
#endif

                SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
            }

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : We can add some settings here while combo key with power key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyPowerKeyMix(void)
{
    switch(g_ucKeyStateCurr)
    {
        case _POWER_RIGHT_KEY_MASK:
            break;

        case _POWER_MENU_KEY_MASK:
            break;

        case _POWER_LEFT_RIGHT_KEY_MASK:
            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  : Convert keypad status into key message, stores in ucKeyNotify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyMessageProc(void)
{
    switch(g_ucKeyStateCurr)
    {
        case _MENU_KEY_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
            break;

        case _RIGHT_KEY_MASK:
            RTDKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            break;

        case _LEFT_KEY_MASK:
            RTDKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
            break;

        case _EXIT_KEY_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_EXIT_KEY_MASK, _EXIT_KEY_MESSAGE);
            break;
		
		case _SELECT_KEY_MASK:		
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_SELECT_KEY_MASK, _SELECT_KEY_MESSAGE);
            break;
		
		case _SOURCE_KEY_MASK:		
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_SOURCE_KEY_MASK, _SOURCE_KEY_MESSAGE);
            break;
		
		case _UP_KEY_MASK:			
            RTDKeyMessageConvert(_UP_KEY_MASK, _UP_KEY_MESSAGE);
            break;
		
		case _DOWN_KEY_MASK:		
            RTDKeyMessageConvert(_DOWN_KEY_MASK, _DOWN_KEY_MESSAGE);
            break;

		case _MUTE_KEY_MASK:	
			CLR_KEYREPEATENABLE();			
            RTDKeyMessageConvert(_MUTE_KEY_MASK, _MUTE_KEY_MESSAGE);
            break;
		
		case _FUNC_KEY_MASK:
			CLR_KEYREPEATENABLE();			
            RTDKeyMessageConvert(_FUNC_KEY_MASK, _FUNC_KEY_MESSAGE);
            break;
			
		case _F1_KEY_MASK:		
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_F1_KEY_MASK, _F1_KEY_MESSAGE);
            break;
		
		case _F2_KEY_MASK:		
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_F2_KEY_MASK, _F2_KEY_MESSAGE);
            break;
		
		case _F3_KEY_MASK:		
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_F3_KEY_MASK, _F3_KEY_MESSAGE);
            break;

		case _VOL_P_KEY_MASK:		
            RTDKeyMessageConvert(_VOL_P_KEY_MASK, _VOL_P_KEY_MESSAGE);
            break;

		case _VOL_M_KEY_MASK:		
            RTDKeyMessageConvert(_VOL_M_KEY_MASK, _VOL_M_KEY_MESSAGE);
            break;

	
		case _IR_UP_KEY_MASK:			
            RTDKeyMessageConvert(_IR_UP_KEY_MASK, _IR_UP_KEY_MESSAGE);
            break;
		
		case _IR_DOWN_KEY_MASK:		
            RTDKeyMessageConvert(_IR_DOWN_KEY_MASK, _IR_DOWN_KEY_MESSAGE);
            break;	
        default:
            if((g_ucKeyStateCurr == _RELEASE_KEY_MASK) &&
               (g_ucKeyStatePrev != _RELEASE_KEY_MASK))
            {
                RTDKeyHoldKeyCheck(); // Check key release
            }

            CLR_KEYREPEATSTART();
            CLR_KEYREPEATENABLE();
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
            break;
    }
}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void RTDKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg)
{
    // Key different
    if((g_ucKeyStatePrev != g_ucKeyStateCurr) && (ucKeyMask == g_ucKeyStateCurr))
    {
        // KeyLock function
        //if (RTDKeySpecialProc(ucKeyMask) == _FALSE)	//  Disable Special Key 
        {
            SET_KEYMESSAGE(ucKeyMsg);
		//------------------ Key Debug ---------------- 
			/*
			switch(ucKeyMsg)
			{
				case _MENU_KEY_MESSAGE:
					printf("_MENU_KEY_MESSAGE\n\r");
					break;
				case _EXIT_KEY_MESSAGE:
					printf("_EXIT_KEY_MESSAGE\n\r");
					break;
				case _SOURCE_KEY_MESSAGE:
					printf("_SOURCE_KEY_MESSAGE\n\r");
					break;
				case _LEFT_KEY_MESSAGE:
					printf("_LEFT_KEY_MESSAGE\n\r");
					break;
				case _RIGHT_KEY_MESSAGE:
					printf("_RIGHT_KEY_MESSAGE\n\r");
					break;
				case _UP_KEY_MESSAGE:
					printf("_UP_KEY_MESSAGE\n\r");
					break;
				case _DOWN_KEY_MESSAGE:
					printf("_DOWN_KEY_MESSAGE\n\r");
					break;
				case _SELECT_KEY_MESSAGE:
					printf("_SELECT_KEY_MESSAGE\n\r");
					break;

				case _FUNC_KEY_MESSAGE:	
					printf("_FUNC_KEY_MESSAGE\n\r");
					break;
				case _MUTE_KEY_MESSAGE:	
					printf("_MUTE_KEY_MESSAGE\n\r");
					break;
				case _F1_KEY_MESSAGE:
					printf("_F1_KEY_MESSAGE\n\r");
					break;
				case _F2_KEY_MESSAGE:
					printf("_F2_KEY_MESSAGE\n\r");
					break;
				case _F3_KEY_MESSAGE:
					printf("_F3_KEY_MESSAGE\n\r");
					break;
				case _VOL_P_KEY_MESSAGE:
					printf("_VOL_P_KEY_MESSAGE\n\r");
					break;
				case _VOL_M_KEY_MESSAGE:
					printf("_VOL_M_KEY_MESSAGE\n\r");
					break;
					
				case _IR_UP_KEY_MESSAGE:
					printf("_IR_UP_KEY_MESSAGE\n\r");
					break;
				case _IR_DOWN_KEY_MESSAGE:
					printf("_IR_DOWN_KEY_MESSAGE\n\r");
					break;	
			}
			*/
				
		//----------------------------------------------
            RTDKeyHoldKeyTimerCancel();

			if(ucKeyMask == _UP_KEY_MASK){
					if(pattern[patternIndex] == 1)patternIndex++;	
					else patternIndex = 0; 	
					if(pattern2[pattern2Index] == 1)pattern2Index++;
					else pattern2Index = 0; 
			}
			else if(ucKeyMask == _DOWN_KEY_MASK){
					if(pattern[patternIndex] == 0)patternIndex++;
					else patternIndex = 0; 	
					if(pattern2[pattern2Index] == 0)pattern2Index++;
					else pattern2Index = 0; 								
			}
			else {
					patternIndex = 0;
					pattern2Index = 0; 	
			}
			if(patternIndex == 5){
					g_stOSDUserData.b1KeyLock = 0; // KEY UNLOCK
					RTDEepromSaveOSDData();
			}
			if(pattern2Index == 5){
					g_stOSDUserData.b1KeyLock = 0; // KEY LOCK
					RTDEepromSaveOSDData();
			}		
        }
    }
    else // Key the same
    {
        if(GET_KEYREPEATENABLE() == _TRUE)
        {
            if(GET_KEYREPEATSTART() == _TRUE)
            {
                SET_KEYMESSAGE(ucKeyMsg);
            }
            else
            {
                // Set repeat key after 100ms.
                ScalerTimerActiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_KEY_REPEAT_ENABLE); 
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyHoldKeyTimerCancel(void)
{
    if(GET_KEY_HOLD() == _TRUE)
    {
        CLR_KEY_HOLD();

        // list all off hold key timer event here!!!
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_AUTO_COLOR);
#if(_DP_SUPPORT == _ON)
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
#endif
    }
}

//--------------------------------------------------
// Description  : Hold Key check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyHoldKeyCheck(void)
{
    if(GET_KEY_HOLD() == _TRUE)
    {
        switch(g_ucKeyStatePrev)
        {
            case _EXIT_KEY_MASK:
                SET_KEYMESSAGE(_EXIT_KEY_MESSAGE);
                break;

            case _MENU_KEY_MASK:
                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
                break;
            case _RIGHT_KEY_MASK:
                SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
                break;
            case _LEFT_KEY_MASK:
                SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
                break;
            default:
                break;
        }
        RTDKeyHoldKeyTimerCancel();
    }
}


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : IR Key Scan
// Input Value  : None
// Output Value : Key Mask
//--------------------------------------------------
BYTE RTDIRKeyScan(void)
{
    BYTE pucIRCodeBuffer[8] = {0};
    WORD usKeyCode = 0;
    BYTE ucKeyState = 0;

    if(ScalerIRHWModeGetData(pucIRCodeBuffer) == _TRUE)
    {
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
        //if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (pucIRCodeBuffer[2] == ~(pucIRCodeBuffer[3])))
        if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (pucIRCodeBuffer[2] == (~(pucIRCodeBuffer[3])-2)))	// ex) MENU 84[3] 7B-2=>79[2] 32[1] CD[0]
        {
            usKeyCode = (((WORD)pucIRCodeBuffer[3]) << 8) + pucIRCodeBuffer[1];
        }

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
        usKeyCode = (((WORD)pucIRCodeBuffer[0]) << 8) + pucIRCodeBuffer[1];

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
        usKeyCode = (((WORD)pucIRCodeBuffer[2]) << 8) + pucIRCodeBuffer[3];

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
				
		if(ScalerIRHWModeGetNECIRStatus()==_NEC_IR_REPEAT)	//  Disable Repeat Key 
		{
			switch(usKeyCode)
			{
				case _IR_CODE_KEY_MENU:
				case _IR_CODE_KEY_SELECT:
				case _IR_CODE_KEY_SOURCE: 	
				case _IR_CODE_KEY_FUNC:			
				case _IR_CODE_KEY_MUTE:
				case _IR_CODE_KEY_F1:
				case _IR_CODE_KEY_F2:
				case _IR_CODE_KEY_F3:
				//case _IR_CODE_KEY_VOL_P:	//  Volume Repeat key Enable
				//case _IR_CODE_KEY_VOL_M:
				//printf("Clear IR Repeat\n\r");
					usKeyCode = 0;
				break;
			}
		}
						
        switch(usKeyCode)
        {
            case _IR_CODE_KEY_POWER:
                ucKeyState = _POWER_KEY_MASK;
                break;

            case _IR_CODE_KEY_MENU:
                ucKeyState = _MENU_KEY_MASK;
                break;

            case _IR_CODE_KEY_RIGHT:
                ucKeyState = _RIGHT_KEY_MASK;
                break;

            case _IR_CODE_KEY_LEFT:
                ucKeyState = _LEFT_KEY_MASK;
                break;

            //case _IR_CODE_KEY_EXIT:
            //    ucKeyState = _EXIT_KEY_MASK;
            //    break;
			
			case _IR_CODE_KEY_SELECT:							
				ucKeyState = _SELECT_KEY_MASK;
                break;
				
			case _IR_CODE_KEY_SOURCE:   
				ucKeyState = _SOURCE_KEY_MASK;
                break;
		
			case _IR_CODE_KEY_UP:
				ucKeyState = _IR_UP_KEY_MASK;//_UP_KEY_MASK;	
                break;

			case _IR_CODE_KEY_DOWN:
				ucKeyState = _IR_DOWN_KEY_MASK;//_DOWN_KEY_MASK;	
                break;


			case _IR_CODE_KEY_FUNC:	
				ucKeyState = _FUNC_KEY_MASK;
                break;

			case _IR_CODE_KEY_MUTE:	
				ucKeyState = _MUTE_KEY_MASK;
                break;
				
			case _IR_CODE_KEY_F1:	
				ucKeyState = _F1_KEY_MASK;
                break;
			
			case _IR_CODE_KEY_F2:
				ucKeyState = _F2_KEY_MASK;
                break;
			
			case _IR_CODE_KEY_F3:	// MUTE
				ucKeyState = _F3_KEY_MASK;
                break;
				
			case _IR_CODE_KEY_VOL_P:
				ucKeyState = _VOL_P_KEY_MASK;
                break;
			
			case _IR_CODE_KEY_VOL_M:
				ucKeyState = _VOL_M_KEY_MASK;
                break;
            default:
                ucKeyState = 0x00;
                break;
        }
    }

    return ucKeyState;
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
