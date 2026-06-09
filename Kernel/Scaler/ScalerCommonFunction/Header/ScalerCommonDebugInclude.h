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
// ID Code      : ScalerCommonDebugInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
#define _SMBUS_BLOCK_READ_WRITE_EXIT_TIMER_COUNT                 60000
#endif

// Switch to FwUpdae command Define
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#define _SCALER_FW_UPDATE_CMD                                    0x31
#endif

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
// True : DDCCI  Swicth to Debug Mode; Ignore OSD Falg.
// FALSE :  Refer to OSD Flag
#define GET_DDCCI_SWITCH_STATE()                                 (g_bDdcciSwitchState)
#define SET_DDCCI_SWITCH_STATE()                                 (g_bDdcciSwitchState = _TRUE)
#define CLR_DDCCI_SWITCH_STATE()                                 (g_bDdcciSwitchState = _FALSE)
#endif

//--------------------------------------------------
// Macros of SMbus Block Read/Write
//--------------------------------------------------
#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
#define SET_SMBUS_BLOCK_RW_STATUS(x)                             (g_stSmbusBlockRWCmd.b1SmbusEnable = (x))
#define GET_SMBUS_BLOCK_RW_STATUS()                              (g_stSmbusBlockRWCmd.b1SmbusEnable)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
extern bit g_bDdcciSwitchState;
#endif

#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
extern StructSmbusBlockRWCmd g_stSmbusBlockRWCmd;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDebugSelectDDCCIDebugMode(EnumDDCCIDebugMode enumMode);
extern EnumDDCCIDebugMode ScalerDebugGetDDCCIDebugMode(void);

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern bit ScalerDebugCheckDebugPort(BYTE ucInputPort);
#endif

extern void ScalerDebug(void);

#if((_DUAL_BANK_SUPPORT == _ON) || (_DIGITAL_SIGNATURE_SUPPORT == _ON))
extern void ScalerDebugDualBankSetDebugInfo(BYTE ucRevCmd, BYTE ucOpCode, BYTE ucSubOpCode);
extern BYTE ScalerDebugDualBankGetDebugInfo(BYTE *pucOpCode, BYTE *pucSubOpCode);
#endif


