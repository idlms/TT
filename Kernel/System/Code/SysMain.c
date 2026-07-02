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
#include "RTD2014Include.h"
#include "RTD2014UserInclude.h"
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
//--------------------------------------------------
// DIP Switch Definitions
//--------------------------------------------------
#define SW0001_ADJ_PWM_197   MCU_FE2B_PORT93_PIN_REG
#define SW0002_NOR_INV_196   MCU_FE2A_PORT92_PIN_REG
#define SW0003_4Ln_8Ln_195   MCU_FE29_PORT91_PIN_REG
#define SW0004_Vx1_eDP_193   MCU_FE27_PORT87_PIN_REG

// 개별 스위치 상태 매크로 (LOW Active: 0=ON)
#define GET_SW0001_ADJ_PWM()  (SW0001_ADJ_PWM_197 == 0)  // 0=ADJ,   1=PWM
#define GET_SW0002_NOR_INV()  (SW0002_NOR_INV_196 == 0)  // 0=NOR,   1=INV
#define GET_SW0003_4Ln_8Ln()  (SW0003_4Ln_8Ln_195 == 0)  // 0=4Lane, 1=8Lane
#define GET_SW0004_Vx1_eDP()  (SW0004_Vx1_eDP_193 == 0)  // 0=Vx1,   1=eDP

// 전체 상태를 1바이트로 읽기
#define GET_SW_ALL()    ((BYTE)( \
    (GET_SW0001_ADJ_PWM() ? _BIT3 : 0) | \
    (GET_SW0002_NOR_INV() ? _BIT2 : 0) | \
    (GET_SW0003_4Ln_8Ln() ? _BIT1 : 0) | \
    (GET_SW0004_Vx1_eDP() ? _BIT0 : 0) ))


// 이전 상태 저장 변수 (0xFF = 미초기화)
static BYTE g_ucDipSwPrev = 0xFF;
//--------------------------------------------------
// Description  : DIP Switch 변경 감지 및 처리
//                메인 루프에서 주기적으로 호출
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserDipSwitchHandler(void)
{
    BYTE ucSwCurr = GET_SW_ALL();

    // 이전 상태와 동일하면 아무것도 안 함
    if(ucSwCurr == g_ucDipSwPrev)
    {
        return;
    }

    // 변경된 스위치 감지 및 출력
    DebugMessageSystem("===== DIP Switch Changed =====", ucSwCurr);

    //--------------------------------------------------
    // SW0001 : ADJ / PWM
    //--------------------------------------------------
    if((ucSwCurr & _BIT3) != (g_ucDipSwPrev & _BIT3))
    {
        if(ucSwCurr & _BIT3)
        {
            DebugMessageSystem("[SW0001] ADJ_PWM : ADJ --> PWM", 1);
            // TODO: PWM 모드 전환 처리
            SET_OSD_BACKLIGHT_FREQ(3000);
            //PWM Frq over 3khz
        }
        else
        {
            DebugMessageSystem("[SW0001] ADJ_PWM : PWM --> ADJ", 0);
            // TODO: ADJ 모드 전환 처리
            SET_OSD_BACKLIGHT_FREQ(180);
             //PWR Frq over180hz
        }
        PCB_PWM_SETTING();

    }

    //--------------------------------------------------
    // SW0002 : NOR / INV
    //--------------------------------------------------
    if((ucSwCurr & _BIT2) != (g_ucDipSwPrev & _BIT2))
    {
        if(ucSwCurr & _BIT2)
        {
            DebugMessageSystem("[SW0002] NOR_INV : NOR --> INV", 1);
            // TODO: INV 모드 전환 처리
            SET_OSD_BACKLIGHT_INVERT(_ON);
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
            //PWM duty inverse
        }
        else
        {
            DebugMessageSystem("[SW0002] NOR_INV : INV --> NOR", 0);
            // TODO: NOR 모드 전환 처리
            SET_OSD_BACKLIGHT_INVERT(_OFF);
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
            //PWM duty normal
        }
        
    }
//패널 선택은 전원 켜질때만 가능합니다.
    // //--------------------------------------------------
    // // SW0003 : 4Lane / 8Lane
    // //--------------------------------------------------
    // if((ucSwCurr & _BIT1) != (g_ucDipSwPrev & _BIT1))
    // {
    //     if(ucSwCurr & _BIT1)
    //     {
    //         DebugMessageSystem("[SW0003] 4Ln_8Ln : 4Lane --> 8Lane", 1);
    //         // TODO: 8Lane 전환 처리
    //     }
    //     else
    //     {
    //         DebugMessageSystem("[SW0003] 4Ln_8Ln : 8Lane --> 4Lane", 0);
    //         // TODO: 4Lane 전환 처리
    //     }
    // }

    // //--------------------------------------------------
    // // SW0004 : Vx1 / eDP
    // //--------------------------------------------------
    // if((ucSwCurr & _BIT0) != (g_ucDipSwPrev & _BIT0))
    // {
    //     if(ucSwCurr & _BIT0)
    //     {
    //         DebugMessageSystem("[SW0004] Vx1_eDP : Vx1 --> eDP", 1);
    //         // TODO: eDP 전환 처리
    //     }
    //     else
    //     {
    //         DebugMessageSystem("[SW0004] Vx1_eDP : eDP --> Vx1", 0);
    //         // TODO: Vx1 전환 처리
    //     }
    // }
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    // 현재 상태 저장
    g_ucDipSwPrev = ucSwCurr;
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
            //UserDipSwitchHandler();
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

