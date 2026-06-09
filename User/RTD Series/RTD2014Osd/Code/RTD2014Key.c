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
//#define _RELEASE_KEY_MASK                           0x00
//#define _POWER_KEY_MASK                             0x01
//#define _MENU_KEY_MASK                              0x02
//#define _RIGHT_KEY_MASK                             0x04
//#define _LEFT_KEY_MASK                              0x08
//#define _SELECT_KEY_MASK                              0x10
//#define _KEY5_MASK                                  0x20
//#define _KEY6_MASK                                  0x40
//#define _KEY7_MASK                                  0x80

//#define _POWER_RIGHT_KEY_MASK                       (_POWER_KEY_MASK | _RIGHT_KEY_MASK)
//#define _POWER_MENU_KEY_MASK                        (_POWER_KEY_MASK | _MENU_KEY_MASK)
//#define _POWER_LEFT_RIGHT_KEY_MASK                  (_POWER_KEY_MASK | _LEFT_KEY_MASK | _RIGHT_KEY_MASK)

typedef enum
{
	_RELEASE_KEY_MASK,
	_POWER_KEY_MASK,
	_MENU_KEY_MASK,
	_RIGHT_KEY_MASK,
	_LEFT_KEY_MASK,
	_SELECT_KEY_MASK,
	_UP_KEY_MASK,
	_DOWN_KEY_MASK,
	
//	IR Message
	_SOURCE_IR_MASK,

	_UP_IR_MASK,
	_DOWN_IR_MASK,
	_RIGHT_IR_MASK,
	_LEFT_IR_MASK,

	_F1_IR_MASK,
	_F2_IR_MASK,
	_F3_IR_MASK,

	_MUTE_IR_MASK,
	_VOL_P_IR_MASK,
	_VOL_M_IR_MASK,
#if		1	// 2017.03.24 - ERIC-ADD
	_SELECT_IR_MASK,
#endif
	_KEY_MASK_AMOUNT ,
}EnumIRMaskType;



//--------------------------------------------------
// Definitions of IR Key Code
//--------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
#if(_IR_PROTOCAL == _IR_NEC_DTV328)

#define _IR_CODE_KEY_POWER                          0xFFFB
#define _IR_CODE_KEY_MENU                           0xFDFB
#define _IR_CODE_KEY_RIGHT                          0xF5FB
#define _IR_CODE_KEY_LEFT                           0xF7FB
#define _IR_CODE_KEY_UP                        	   0xFAFB
#define _IR_CODE_KEY_DOWN                           0xF2FB
#define _IR_CODE_KEY_SOURCE                           0xEDFB
#define _IR_CODE_KEY_EXIT                           0xF6FB


#define _IR_CODE_KEY_F1                           0xE4FB
#define _IR_CODE_KEY_F2                           0xF9FB
//#define _IR_CODE_KEY_F3                           0xE6FB

#elif(_IR_PROTOCAL == _IR_NEC_TYPE1)
#define _IR_CUSTOMER_CODE_H					0x79
#define _IR_CUSTOMER_CODE_L					0x84

				

#define _IR_CODE_KEY_POWER                          0xED
#define _IR_CODE_KEY_MENU                           0xCD
#define _IR_CODE_KEY_RIGHT                          0xF6
#define _IR_CODE_KEY_LEFT                           0xF8
#define _IR_CODE_KEY_UP                        	   0xFA
#define _IR_CODE_KEY_DOWN                         0xFF
#define _IR_CODE_KEY_EXIT                           0xf7
#define _IR_CODE_KEY_SOURCE                           0xCB

#define _IR_CODE_KEY_MUTE                           0xCE
#define _IR_CODE_KEY_F1                           0xE4
#define _IR_CODE_KEY_F2                           0xF9
#define _IR_CODE_KEY_F3                           0xE5

#define _IR_CODE_KEY_VOL_P                           0xEF 
#define _IR_CODE_KEY_VOL_M                          0xF0


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

#elif(_IR_PROTOCAL == _IR_LG_TYPE)
#define _IR_CUSTOMER_CODE_H					0xFB
#define _IR_CUSTOMER_CODE_L					0x04


#define _IR_CODE_KEY_POWER                        0xF7 //
#define _IR_CODE_KEY_MENU                         0xBC //
#define _IR_CODE_KEY_RIGHT                        0xF9 //
#define _IR_CODE_KEY_LEFT                         0xF8 //
#define _IR_CODE_KEY_UP                        	  0xBF //
#define _IR_CODE_KEY_DOWN                         0xBE //
#define _IR_CODE_KEY_EXIT                         0xA4 //
#define _IR_CODE_KEY_SOURCE                       0xF4 //

#define _IR_CODE_KEY_MUTE                         0xF6 //
#define _IR_CODE_KEY_F1                           0x00
#define _IR_CODE_KEY_F2                           0x01
#define _IR_CODE_KEY_F3                           0x02

#define _IR_CODE_KEY_VOL_P                        0xFD //
#define _IR_CODE_KEY_VOL_M                        0xFC //
#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)




#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

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
BYTE g_ucIRKeyStatePrev;
BYTE g_ucIRKeyStateCurr;

#if(_AD_KEY_SUPPORT == _ON)
BYTE g_ucBackupKeyState = 0xFF;
#endif


#if(_CIZGI_ENABLE_DICOM_KEY == _ON)
BYTE patternIndex = 0;
BYTE pattern2Index = 0;
BYTE pattern[5] = {1, 1, 0, 1, 0};
BYTE pattern2[5] = {0, 0, 1, 0, 1};
#endif	
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
void RTDIRKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg);

bit RTDKeySpecialProc(BYTE ucKeyMask);

void RTDKeyHoldKeyTimerCancel(void);
void RTDKeyHoldKeyCheck(void);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE RTDIRKeyScan(void);
#endif

//extern void SysUartSetTxCommand(BYTE ucTxCmd, BYTE ucTxStatus, BYTE ucTxData);
//extern void SysUartSendBluetoothOff(void) ;
//extern void SysUartSendBluetoothTest1(void) ;
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
    // Clear the key message
    if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)
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
		
#if 0//(_IR_SUPPORT == _IR_HW_SUPPORT)

	if(GET_KEYMESSAGE() ==  _NONE_KEY_MESSAGE)
	{
	        g_ucIRKeyStatePrev = g_ucIRKeyStateCurr;
	
		g_ucIRKeyStateCurr = RTDIRKeyScan();

		// Power key process, return if power key is pressed
//		if(RTDIRKeyPowerKeyProc() == _TRUE)
		{
//		    return;
		}		
		RTDIRKeyMessageProc();
	}
#endif	
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
        ScalerTimerReactiveTimerEvent(SEC(0.01), _USER_TIMER_EVENT_KEY_SCAN_READY);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE					RTDKeyScan(void)
{
	BYTE				ucVoltage0 = 0;
	BYTE				ucVoltage1 = 0;
	BYTE				ucVoltage2 = 0;
	BYTE				ucVoltage3 = 0;
	BYTE				ucKeyState = 0;

#if		(_AD_KEY_SUPPORT == _ON)
 //	ucVoltage0 = PCB_ADKEY0();
	ucVoltage1 = PCB_ADKEY1();	// KEY1
	ucVoltage2 = PCB_ADKEY2();	// KEY2
 //	ucVoltage3 = PCB_ADKEY3();

	PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);

 //	if ( ucVoltage0 < 0xf6 )
 //		DebugMessageSystem(" ucVoltage0  " , ucVoltage0);
	// if ( ucVoltage1 < 0xF0 )		// 0xF6
	// 	DebugMessageSystem(" ucVoltage1  " , ucVoltage1);
	// if ( ucVoltage2 < 0xF0 )		// 0xF6
	// 	DebugMessageSystem(" ucVoltage2  " , ucVoltage2);
//	if ( ucVoltage3 < 0xf6 )
//		DebugMessageSystem(" ucVoltage3  " , ucVoltage3);

  #if		(_IR_SUPPORT == _IR_HW_SUPPORT)
	if (ucKeyState == 0x00)
	{
		ucKeyState = RTDIRKeyScan();
		if ( ucKeyState != 0 )
		{
			RTDKeyInitial();
//			DebugMessageSystem(" remote  " , ucKeyState);

//			g_ucKeyStatePrev = ucKeyState;
			return ucKeyState;
		}
//		else
//		{
//			DebugMessageSystem(" not remote  " , ucKeyState);
//		}
	}
  #endif		// End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

	if (g_ucBackupKeyState == ucKeyState)
	{
		if (GET_KEYREPEATENABLE() != _ON)
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
#endif		// End of #if(_AD_KEY_SUPPORT == _ON)

#if		(_IR_SUPPORT == _IR_HW_SUPPORT)
//	if (ucKeyState == 0x00)
//	{
//		ucKeyState = RTDIRKeyScan();
//	}
#endif	// End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

	if (ucKeyState != 0)
	{
		RTDKeyInitial();
	}

	return ucKeyState;
}


//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit RTDKeyPowerKeyProc(void)
{
//    if((g_ucKeyStateCurr & _POWER_KEY_MASK) != 0)
    if((g_ucKeyStateCurr == _POWER_KEY_MASK))

    {
        if(((g_ucKeyStatePrev ^ g_ucKeyStateCurr) & _POWER_KEY_MASK) != 0)
        {
            RTDKeyPowerKeyMix();

            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
                SET_OSD_STATE(_MENU_NONE);
                SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
#if (_ENABLE_MENU_OLED == _OFF)
				SMPS_POWER(_SMPS_ON); // SMPS Active LoW
#endif
#if(_CUSTOMER_TYPE == _CUSTOMER_MRK)
				ScalerTimerActiveTimerEvent(SEC(7), _USER_TIMER_EVENT_BOOT_GPIO1_DELAY);
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
				setShift = 0;
				pixShiftTime = 0;
				ScalerTimerActiveTimerEvent(MIN(1), _USER_TIMER_EVENT_PIXEL_SHIFT);
#endif
            }
            else
            {
#if (_ENABLE_MENU_OLED == _ON)
				if (GetWaitingToRunOFFRS() == _ON)
				{
					DebugMessageOsd("T:^^^ IR PowerKey Off RS => PowerOff ^^^", g_ucKeyStateCurr);

					OsdDispOsdMessage(_OSD_DISP_OFF_RS_MSG);
					ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_OFF_RS_RUN);
					SET_COMP_RUN_RESTART(_OFF);
				}
				else //if(GetOffRSStatus()==_OFF)
#endif
				{
#if	(_ENABLE_LIGHT_SENSOR == _ON)
					ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_CHECK_BACKLIGHT);
#endif
#if	(_ENABLE_FAN_CONTROL == _ON)
					ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_CHECK_FANCONTROL);
#if (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
					SetFanAllPWM(0);
#elif (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
					MAX31785_DisableFan();
#endif
#endif
#if	(_ENABLE_SELF_CHECK == _ON)
					ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_CHECK_SELF);
#endif
					SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
#if (_ENABLE_MENU_OLED == _OFF)
					SMPS_POWER(_SMPS_OFF); //
#endif

				}
#if(_CUSTOMER_TYPE == _CUSTOMER_MRK)
				EANBLE_GPIO1(_FALSE);
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
				setShift = 0;
				pixShiftTime = 0;
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PIXEL_SHIFT);
#endif
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
//        case _POWER_RIGHT_KEY_MASK:
//            break;

//        case _POWER_MENU_KEY_MASK:
//            break;

//        case _POWER_LEFT_RIGHT_KEY_MASK:
//            break;

        default:
            break;
    }
}

//180103
//extern bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
//extern bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
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
			//DebugMessageYHJ("MENU KEY", g_ucKeyStateCurr);
            RTDKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
            break;

        case _RIGHT_KEY_MASK:
			//DebugMessageYHJ("RIGHT KEY", g_ucKeyStateCurr);
            RTDKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            break;

        case _LEFT_KEY_MASK:
			//DebugMessageYHJ("LEFT KEY", g_ucKeyStateCurr);
            RTDKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
            break;

        case _SELECT_KEY_MASK:
            CLR_KEYREPEATENABLE();
			//DebugMessageYHJ("SELECT KEY", g_ucKeyStateCurr);
			//DebugMessageYHJ("KEY GET_OSD_STATE ", GET_OSD_STATE());
            RTDKeyMessageConvert(_SELECT_KEY_MASK, _SELECT_KEY_MESSAGE);
            break;

        case _UP_KEY_MASK:
            //CLR_KEYREPEATENABLE();
			//DebugMessageYHJ("UP KEY", g_ucKeyStateCurr);
            RTDKeyMessageConvert(_UP_KEY_MASK, _UP_KEY_MESSAGE);
            break;

        case _DOWN_KEY_MASK:
            //CLR_KEYREPEATENABLE();
			//DebugMessageYHJ("DOWN KEY", g_ucKeyStateCurr);
            RTDKeyMessageConvert(_DOWN_KEY_MASK, _DOWN_KEY_MESSAGE);
            break;

	case _SOURCE_IR_MASK :
		CLR_KEYREPEATENABLE();
		RTDKeyMessageConvert(_SOURCE_IR_MASK, _SOURCE_IR_MESSAGE);
		break;	

        case _UP_IR_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_UP_IR_MASK, _UP_IR_MESSAGE);
            break;
        case _DOWN_IR_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_DOWN_IR_MASK, _DOWN_IR_MESSAGE);
            break;
        case _LEFT_IR_MASK:
            CLR_KEYREPEATENABLE();
			RTDKeyMessageConvert(_LEFT_IR_MESSAGE, _LEFT_IR_MESSAGE);
            break; //
        case _RIGHT_IR_MASK:
//            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_RIGHT_IR_MASK, _RIGHT_IR_MESSAGE);
            break;	

        case _F1_IR_MASK:
            CLR_KEYREPEATENABLE();
		RTDIRKeyMessageConvert(_F1_IR_MASK, _F1_IR_MESSAGE);
            break;	
        case _F2_IR_MASK:
            CLR_KEYREPEATENABLE();
		RTDIRKeyMessageConvert(_F2_IR_MASK, _F2_IR_MESSAGE);
            break;	
		case _F3_IR_MASK:
			CLR_KEYREPEATENABLE();
			RTDIRKeyMessageConvert(_F3_IR_MASK, _F3_IR_MESSAGE);
			break;
        case _MUTE_IR_MASK:
            CLR_KEYREPEATENABLE();
		RTDIRKeyMessageConvert(_MUTE_IR_MASK, _MUTE_IR_MESSAGE);

            break;	
        case _VOL_P_IR_MASK:
 //           CLR_KEYREPEATENABLE();
		RTDIRKeyMessageConvert(_VOL_P_IR_MASK, _VOL_P_IR_MESSAGE);

            break;				
		case _VOL_M_IR_MASK :
//			CLR_KEYREPEATENABLE();
			RTDIRKeyMessageConvert(_VOL_M_IR_MASK, _VOL_M_IR_MESSAGE);
			break;				

#if		1	// 2017.03.24 - ERIC-ADD
		case _SELECT_IR_MASK :
			CLR_KEYREPEATENABLE();
			if (GET_OSD_STATE() != _MENU_NONE)
				RTDIRKeyMessageConvert(_SELECT_IR_MASK, _SELECT_KEY_MESSAGE);
//			else
//				RTDIRKeyMessageConvert(_SELECT_IR_MASK, _SOURCE_IR_MESSAGE);
			break;				
#endif

		default :
			if (	(g_ucKeyStateCurr == _RELEASE_KEY_MASK) &&
				(g_ucKeyStatePrev != _RELEASE_KEY_MASK) )
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
//    DebugMessageSystem("ucKeyMsg ", ucKeyMsg);

    if((g_ucKeyStatePrev != g_ucKeyStateCurr) && (ucKeyMask == g_ucKeyStateCurr))
    {
    	    //DebugMessageSystem("RTDKeyMessageConvert ", ucKeyMask);

        // KeyLock function
        if (RTDKeySpecialProc(ucKeyMask) == _FALSE)
        {
            SET_KEYMESSAGE(ucKeyMsg);
            RTDKeyHoldKeyTimerCancel();
#if(_CIZGI_ENABLE_DICOM_KEY == _ON)
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
					g_stOsdUserData.b1CalibFlag = 0;
					RTDNVRamSaveOSDData();//RTDEepromSaveOsdUserData();
			}
			if(pattern2Index == 5){
					g_stOsdUserData.b1CalibFlag = 1;
					RTDNVRamSaveOSDData();//RTDEepromSaveOsdUserData();
			}						
#endif			
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
                // Set repeat key after 500ms.
                ScalerTimerActiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void RTDIRKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg)
{
    // Key different
//Eric_020170125 : dELETE

        if((g_ucIRKeyStatePrev != g_ucIRKeyStateCurr) && (ucKeyMask == g_ucIRKeyStateCurr))
        {
            // KeyLock function
            if (RTDKeySpecialProc(ucKeyMask) == _FALSE)
            {
	                SET_KEYMESSAGE(ucKeyMsg);
//                RTDKeyHoldKeyTimerCancel();
            }
        }
        else // Key the same
        {
            if(GET_KEYREPEATENABLE() == _TRUE)
            {
                if(GET_KEYREPEATSTART() == _TRUE)
                {
     //               SET_KEYMESSAGE(ucKeyMsg);
                }
                else
                {
                    // Set repeat key after 20ms.
                    ScalerTimerActiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
                }
            }
        }

//	ucKeyMask = 0;
//	SET_KEYMESSAGE(ucKeyMsg);




}

//--------------------------------------------------
// Description  :  for special key check
// Input Value  : scan Key data
// Output Value : None
//--------------------------------------------------
bit RTDKeySpecialProc(BYTE ucKeyMask)
{
    if((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _LEFT_KEY_MASK))
    {
#if(_DP_SUPPORT == _ON)
        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
        SET_KEY_HOLD();
        CLR_KEYREPEATENABLE();
        return _TRUE;
#endif
    }
    else if((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _RIGHT_KEY_MASK))
    {
        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);
        SET_KEY_HOLD();
        CLR_KEYREPEATENABLE();
        return _TRUE;
    }
	else if ((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _UP_KEY_MASK))
	{
		ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);
		SET_KEY_HOLD();
		CLR_KEYREPEATENABLE();
		return _TRUE;
	}
	else if ((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _DOWN_KEY_MASK))
	{
		ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);
		SET_KEY_HOLD();
		CLR_KEYREPEATENABLE();
		return _TRUE;
	}
#if(_VGA_SUPPORT == _ON)
    // Press Exit key for 3 sec to do Auto color
    else if((GET_OSD_STATE() == _MENU_NONE) &&
            (GET_FAIL_SAFE_MODE() == _FALSE))
    {
        if (ucKeyMask == _SELECT_KEY_MASK)
        {
            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_DO_AUTO_COLOR);
            SET_KEY_HOLD();
            CLR_KEYREPEATENABLE();
            return _TRUE;
        }
    }
#endif

    return _FALSE;
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

        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);
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
        switch (g_ucKeyStatePrev)
        {
            case _SELECT_KEY_MASK:
                SET_KEYMESSAGE(_SELECT_KEY_MESSAGE);
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
			case _UP_KEY_MASK:
				SET_KEYMESSAGE(_UP_KEY_MESSAGE);
				break;
			case _DOWN_KEY_MASK:
				SET_KEYMESSAGE(_DOWN_KEY_MESSAGE);
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
	BYTE				pucIRCodeBuffer[8] = {0};
	WORD				usKeyCode = 0;
	BYTE				ucKeyState = 0;

	if (ScalerIRHWModeGetData(pucIRCodeBuffer) == _TRUE)
	{
		DebugMessageSystem(" pucIRCodeBuffer[0]  ", pucIRCodeBuffer[0]);
		DebugMessageSystem(" pucIRCodeBuffer[1]  ", pucIRCodeBuffer[1]);
		DebugMessageSystem(" pucIRCodeBuffer[2]  ", pucIRCodeBuffer[2]);
		DebugMessageSystem(" pucIRCodeBuffer[3]  ", pucIRCodeBuffer[3]);


#if(_IR_PROTOCAL == _IR_NEC_DTV328)
		if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (pucIRCodeBuffer[2] == ~(pucIRCodeBuffer[3])))
		{
		    usKeyCode = (((WORD)pucIRCodeBuffer[0]) << 8) + pucIRCodeBuffer[2];
		}
#elif	(_IR_PROTOCAL == _IR_NEC_TYPE1 || _IR_PROTOCAL == _IR_LG_TYPE  )
		if ( (pucIRCodeBuffer[2] == _IR_CUSTOMER_CODE_H) && (pucIRCodeBuffer[3] == _IR_CUSTOMER_CODE_L) )
		{
			if (pucIRCodeBuffer[7] == 0x80)
			{
				usKeyCode = pucIRCodeBuffer[0];
				pucIRCodeBuffer[7] = 0x00;
				if (	usKeyCode != _IR_CODE_KEY_LEFT &&
					usKeyCode != _IR_CODE_KEY_RIGHT &&
					usKeyCode != _IR_CODE_KEY_VOL_M &&
					usKeyCode != _IR_CODE_KEY_VOL_P )
					usKeyCode = 0;
			}
			else
			if (pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1]))
			{
				usKeyCode = pucIRCodeBuffer[0];
			}
		}	

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
		usKeyCode = (((WORD)pucIRCodeBuffer[0]) << 8) + pucIRCodeBuffer[1];

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
		usKeyCode = (((WORD)pucIRCodeBuffer[2]) << 8) + pucIRCodeBuffer[3];

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
		DebugMessageSystem("usKeyCode", pucIRCodeBuffer[1]);

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

			case _IR_CODE_KEY_EXIT:
#if		1	// 2017.03.24 - ERIC-EDIT
				ucKeyState = _SELECT_IR_MASK;
#else
				ucKeyState = _SELECT_KEY_MASK;
#endif
			break;

			case _IR_CODE_KEY_UP:
				ucKeyState = _UP_KEY_MASK;
			break;
			case _IR_CODE_KEY_DOWN:
				ucKeyState = _DOWN_KEY_MASK;
			break;
			case _IR_CODE_KEY_SOURCE:
				ucKeyState = _SOURCE_IR_MASK;	
			break;
			case _IR_CODE_KEY_MUTE:
				ucKeyState = _MUTE_IR_MASK;
			break;
			case _IR_CODE_KEY_VOL_P:
				ucKeyState = _VOL_P_IR_MASK;
			break;
			case _IR_CODE_KEY_VOL_M:
				ucKeyState = _VOL_M_IR_MASK;
			break;

#ifdef _IR_CODE_KEY_F1
			case _IR_CODE_KEY_F1:
				ucKeyState = _F1_IR_MASK;
			break;
#endif

#ifdef _IR_CODE_KEY_F2
			case _IR_CODE_KEY_F2:
				ucKeyState = _F2_IR_MASK;
			break;
#endif			
#ifdef _IR_CODE_KEY_F3
			case _IR_CODE_KEY_F3:
				ucKeyState = _F3_IR_MASK;
				//UARTDebugMessage(0x01);
				break;
#endif	

			default:
				ucKeyState = 0x00;
			break;
		}


		//if((ucKeyState != _LEFT_KEY_MASK) && (ucKeyState != _RIGHT_KEY_MASK)&& (ucKeyState != _VOL_P_IR_MASK)&& (ucKeyState != _VOL_M_IR_MASK))
		//{	
		//	if(ucKeyState != 0x00) ScalerTimerDelayXms(50); // Eric170327
		//}

	}

        g_ucIRKeyStatePrev = g_ucIRKeyStateCurr;
        // Get current key state
        g_ucIRKeyStateCurr = ucKeyState;

	return ucKeyState;

}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
