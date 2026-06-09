/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonFwUpdateForegroundInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS              0x34
#define _FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT                  60000
#define _FW_UPDATE_FOREGROUND_RESTORE_SCENE_MAX_ISP_LEN         32
#define _FW_UPDATE_FOREGROUND_RESET_MAX_ISP_LEN                 256

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern bit ScalerFwUpdateForegroundGetStatus(void);
#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)
extern void ScalerFwUpdateForegroundReset(void);
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
extern void ScalerFwUpdateForegroundRestoreScene(void);
extern void ScalerFwUpdateForegroundSceneBackup(void);
#endif

#endif
