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
// ID Code      : ScalerCommonFwUpdateForeground.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_FOREGROUND_FW_UPDATE__

#include "ScalerCommonFunctionInclude.h"

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)

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
#if((_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE) && (_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
BYTE g_pucFwUpdateForegroundIspXramData[_FW_UPDATE_FOREGROUND_RESTORE_SCENE_MAX_ISP_LEN];
bit g_bFwUpdateForegroundDdcciStatus = _FALSE;
#endif

// Reserved Xdata for isp program Sram
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
BYTE xdata g_pucProgamBuffer[128]              _at_ _HW_FLASH_PROG_USING_XRAM_START_ADDR;
#endif
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
BYTE xdata g_pucProgamBuffer2[128]             _at_ (_HW_FLASH_PROG_USING_XRAM_START_ADDR + 128);
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)
void ScalerFwUpdateForegroundReset(void);
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
void ScalerFwUpdateForegroundRestoreScene(void);
void ScalerFwUpdateForegroundSceneBackup(void);
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)
//--------------------------------------------------
// Description  : Reset Foreground Fw Update
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateForegroundReset(void)
{
    // Reset MCU
    MCU_FFEE_MCU_CLOCK_CONTROL |= _BIT1;
}
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
//--------------------------------------------------
// Description  : Foreground Fw Update Restore Scene
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateForegroundRestoreScene(void)
{
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
    // Restore data 0f address 0xE000~0xE032
    memcpy(GET_ISP_XRAM_BUFFER(0), g_pucFwUpdateForegroundIspXramData, _FW_UPDATE_FOREGROUND_RESTORE_SCENE_MAX_ISP_LEN);
    if(g_bFwUpdateForegroundDdcciStatus == _FALSE)
    {
        // Restore Force nack Ddc Channel
        ScalerSyncSetDdcForceNack(_A0_INPUT_PORT, g_bFwUpdateForegroundDdcciStatus);
    }
#endif
}

//--------------------------------------------------
// Description  : Foreground Fw Update Scene Backup
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateForegroundSceneBackup(void)
{
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
    // Backup DDC status
    g_bFwUpdateForegroundDdcciStatus = ScalerSyncGetDdcForceNackStatus(_A0_INPUT_PORT);

    if(g_bFwUpdateForegroundDdcciStatus == _FALSE)
    {
        // Check for Ddc Busy Set DDCCI NACK
        ScalerSyncVGADdcCheckBusyAndForceNack();
    }
    memset(g_pucFwUpdateForegroundIspXramData, 0, _FW_UPDATE_FOREGROUND_RESTORE_SCENE_MAX_ISP_LEN);
    memcpy(g_pucFwUpdateForegroundIspXramData, GET_ISP_XRAM_BUFFER(0), _FW_UPDATE_FOREGROUND_RESTORE_SCENE_MAX_ISP_LEN);
#endif
}
#endif

#endif
