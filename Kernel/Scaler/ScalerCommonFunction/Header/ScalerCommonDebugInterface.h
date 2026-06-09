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
// ID Code      : ScalerCommonDebugInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
#define _SMBUS_BLOCK_READ_WRITE_EXIT_TIMER_COUNT       60000
#endif

// Switch to FwUpdae command Define
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#define _SCALER_FW_UPDATE_CMD                          0x31
#endif

//--------------------------------------------------
// Macros of SMbus Block Read/Write
//--------------------------------------------------
#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
#define SET_SMBUS_BLOCK_RW_STATUS(x)                   (g_stSmbusBlockRWCmd.b1SmbusEnable = (x))
#define GET_SMBUS_BLOCK_RW_STATUS()                    (g_stSmbusBlockRWCmd.b1SmbusEnable)
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
extern bit g_bDdcciSwitchState;
#endif

#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
extern StructSmbusBlockRWCmd g_stSmbusBlockRWCmd;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern void ScalerDebugMessage(BYTE *pucArray1, DWORD ulArray2);
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

extern void ScalerDebugIntProc_EXINT1(void);
extern void ScalerDebug(void);
extern BYTE ScalerDebugDualBankGetDebugInfo(BYTE *pucOpCode, BYTE *pucSubOpCode);
extern void ScalerDebugSendData(BYTE ucLen, BYTE *pucSendArray);
extern void ScalerDebugDualBankSetDebugInfo(BYTE ucRevCmd, BYTE ucOpCode, BYTE ucSubOpCode);

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
extern BYTE ScalerDebugGetDdcciSwitchState_EXINT1(void);
extern BYTE ScalerDebugGetDdcciSwitchState(void);
extern void ScalerDebugSetDdcciSwitchState(void);
#endif

#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
extern EnumISPBundleVerResult ScalerDebugUpdateBundleVersion(void);
#endif


