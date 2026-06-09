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
// ID Code      : UserCommonFwUpdateForegroundInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
// Sub Address
#define _FW_UPDATE_FOREGROUND_CMD_SUB_ADDREESS                  0x33
/// Op Code
#define _FW_UPDATE_FOREGROUND_OPCODE_SET_HIGH_PRI_REQ           0x01
#define _FW_UPDATE_FOREGROUND_OPCODE_GET_PROJECT_ID_ADDR_REQ    0x02
#define _FW_UPDATE_FOREGROUND_OPCODE_VERIFY_PROJECT_ID_REQ      0x03
#define _FW_UPDATE_FOREGROUND_OPCODE_GET_ACFWVER_REQ            0x04
#define _FW_UPDATE_FOREGROUND_OPCODE_START_REQ                  0x05
#define _FW_UPDATE_FOREGROUND_OPCODE_FINISH_REQ                 0x06
#define _FW_UPDATE_FOREGROUND_OPCODE_EXIT_REQ                   0x07
#define _FW_UPDATE_FOREGROUND_OPCODE_CHANGE_MODE_REQ            0x08

#define _FW_UPDATE_FOREGROUND_SUBADDRESS_INDEX                  0
#define _FW_UPDATE_FOREGROUND_DATA_START_INDEX                  1
#define _FW_UPDATE_FOREGROUND_OPCODE_INDEX                      1

#define GET_FW_UPDATE_FOREGROUND_STATUS()                       (g_stFwUpdateForegroundInfo.enumFwUpdateStatus)
#define SET_FW_UPDATE_FOREGROUND_STATUS(x)                      (g_stFwUpdateForegroundInfo.enumFwUpdateStatus = (x))

#define GET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY()                (g_stFwUpdateForegroundInfo.b1HighPriority)
#define SET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY(x)               (g_stFwUpdateForegroundInfo.b1HighPriority = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Foreground Fw Update State
//--------------------------------------------------
typedef enum
{
    _IDLE_STATUS = 0,
    _VERIFY_STATUS,
    _FW_UPDATE_STATUS,
} EnumFwUpdateForegroundStatus;

//--------------------------------------------------
// Struct of FwUpdate
//--------------------------------------------------
typedef struct
{
    BYTE b1HighPriority : 1;
    EnumFwUpdateForegroundStatus enumFwUpdateStatus;
} StructFwUpdateForgroundScalerInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructFwUpdateForgroundScalerInfo g_stFwUpdateForegroundInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserCommonFwUpdateForegroundHandler(void);

#endif

