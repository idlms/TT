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
// ID Code      : SysMain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __MAIN__

#include "SysInclude.h"

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
void main(void);
void SysMainSystemInitial(void);
bit SysMainSytemPowerDetect(void);

extern void FanHandler(void);
extern void LightSensorHandler(void);
extern void BurnInModeOff(void);

#if((_DUAL_BANK_SUPPORT == _ON) &&\
   ((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF) ||\
   ((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON) && (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_USER))))
void SysMainStartUserCode(BYTE ucBankAddress);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
void DpmsLedToggle(void)	// DPMS Toggle
{
	if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
	{
		if(g_bLedToggle)
		{
			g_bLedToggle = _FALSE;
			UserInterfaceKeyPadLedControl(_LED_TYPE_RED);
		}
		else
		{
			g_bLedToggle = _TRUE;
			UserInterfaceKeyPadLedControl(_LED_TYPE_OFF);
		}
	}
	
}


//extern void SysPowerIsolation(EnumPowerAction enumSwitch);

void main(void)
{
    do
    {
        SysMainSystemInitial();
		
		printf("SysMainSystemInitial \n\r");	//  use printf Test
	
        while(SysMainSytemPowerDetect() == _TRUE)
        {
			UserInterfaceKeyHandler();
			SysPowerHandler();
			SysJudgeHandler();
			
#if(_AUDIO_SUPPORT == _ON)
            SysAudioHandler();
#endif
            SysTimerHandler();
            SysSourceHandler();
            SysModeHandler();

#if(_MHL_SUPPORT == _ON)
            SysMHLMscHandler();
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCHandler();

#endif

#if(_DP_SUPPORT == _ON)
            SysDpRxHandler();
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
            SysTMDSRxHandler();

#if(_HDMI_CEC_SUPPORT == _ON)
            SysCecHandler();
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
            SysDpTxHandler();
#endif

#if(_EMBEDDED_DP_TX_SUPPORT == _ON)
            SysDpEmbeddedTxHandler();
#endif

#if(_DP_MST_SUPPORT == _ON)
            SysDpMstHandler();
#endif

#if(_HDMI_TX_SUPPORT == _ON)
            SysHdmiTxHandler();
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
            ScalerHdcp2Handler();
#endif

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
            ScalerBBHandler();
#endif

#if(_AUTO_TEST_SUPPORT == _ON)
            SysAutotestHandler();
#endif
#if(_DISTECK_UART_SUPPORT == _ON)
            SysUartHandler();
#endif

            UserCommonInterfaceOsdHandler();

#if(_DDCCI_CODE_REDUCTION == _OFF)
            UserCommonDdcciHandler();
#endif
            SysColorHandler();
            ScalerDebug();

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
            UserCommonDualBankUserDebug();
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
			FanHandler();
#endif

#if (_ENABLE_LIGHT_SENSOR == _ON)
			LightSensorHandler();
#endif

        }
    }
    while(_TRUE);
}

//--------------------------------------------------
// Description  : System AC on initial flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainSystemInitial(void)
{
    ScalerMcuInitial();

    ScalerPinshareInitial();
#if((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON) &&\
    ((_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOOT) ||\
    (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOTH)))
#if(_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOTH)
    if(GET_CURRENT_BANK_NUMBER() == 0x00)
#endif
    {
        UserCommonDualBankProcess();
    }
#endif
    ScalerTimerInitialTimerEvent();

    UserCommonInterfaceInitial();

    ScalerMcuDdcRamEnable();

    SysSourceInitial();
    DebugMessageOsd("_SEARCH_PORT", SysSourceGetInputPort());
    DebugMessageOsd("_SOURCE_SCAN_TYPE", SysSourceGetScanType());

    SysPowerInitial();

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    ScalerIRHWModeInitial();
#endif

    SET_POWER_STATUS(_POWER_STATUS_AC_ON);

    if(UserCommonNVRamGetSystemData(_MONITOR_POWER_STATUS) == _ON)
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
    }
    else
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
    }
	
	SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL); // Power On LastPower( Always On )
	
    SET_MODE_STATE(_MODE_STATUS_POWER_OFF);

	g_bHPJackState = !PCB_HEADPHONE_JACK_DETECT();	// Headphone detect
		
	BurnInModeOff();	// Release AC Off->On 
	PCB_FAN(_FAN_OFF);	// 

}

//--------------------------------------------------
// Description  : System power detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysMainSytemPowerDetect(void)
{
    return PCB_POWER_5V_DETECT();
}
#if((_DUAL_BANK_SUPPORT == _ON) &&\
   ((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF) ||\
   ((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON) && (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_USER))))
//--------------------------------------------------
// Description  : Switch bank and jump to user code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainStartUserCode(BYTE ucBankAddress)
{
#if(_DUAL_BANK_COMPATIBLE_WITH_OLD_BOOT_SUPPORT == _OFF)
    // Set bank offset for user code
    SET_BANK_SWITCH_OFFSET(ucBankAddress);

    // Disable Global INT
    EA = _DISABLE;
#endif

    // Switch current bank
    MCU_FFFF_PBANK_SWITCH = ucBankAddress;

    // The below code is used here to ignore the pre-read code of mcu
    _nop_();
    _nop_();
    _nop_();
    _nop_();

#if((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON) && (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOTH))
    if(GET_CURRENT_BANK_NUMBER() != 0x00)
#endif
    {
        // Reset FW after switched to user code
        ((void (*)(void))0x0000)();
    }
}
#endif

