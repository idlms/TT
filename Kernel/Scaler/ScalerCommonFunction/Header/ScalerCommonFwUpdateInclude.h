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
// ID Code      : ScalerCommonFwUpdateInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _FW_UPDATE_BACKGROUND_SUB_OP_CODE        0x02
#define _FW_UPDATE_FOREGROUND_SUB_OP_CODE        0x03
#define _FW_UPDATE_RESULT_BUSY                   0xBB

#define _FW_UPDATE_BUF_LEN                       (_HW_DDCCI_BUF_SIZE + 1)

#define _FW_UPDATE_RESULT_IDLE                   0x10
#define _FW_UPDATE_RESULT_SUCCESS                0x01
#define _FW_UPDATE_RESULT_FAIL                   0x02
#define _FW_UPDATE_RESULT_IDLE_AND_SUCCESS       (_FW_UPDATE_RESULT_IDLE | _FW_UPDATE_RESULT_SUCCESS)
#define _FW_UPDATE_RESULT_IDLE_AND_FAIL          (_FW_UPDATE_RESULT_IDLE | _FW_UPDATE_RESULT_FAIL)

#if((_FW_UPDATE_PROCESS_SUPPORT == _ON) && (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048))
#define _FW_UPDATE_RTK_SIGATURE_RSA_TYPE         _DIGITAL_SIGNATURE_RSA_2048
#define _FW_UPDATE_RSA_SIGNATURE_SIZE            (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)
#define _FW_UPDATE_RSA_RESULT_SIZE               (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)

#define _FW_UPDATE_RSA_KEY_NKEY_SIZE             (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)
#define _FW_UPDATE_RSA_KEY_RRMODN_SIZE           (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)
#define _FW_UPDATE_RSA_KEY_NPINV_SIZE            4
#define _FW_UPDATE_RSA_KEY_EXORKEY_SIZE          (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)

#define _FW_UPDATE_RSA_SIGNATURE_OFFESET         0
#define _FW_UPDATE_PUBLIC_KEY_OFFESET            ((_FW_UPDATE_RSA_SIGNATURE_OFFESET) + (_FW_UPDATE_RSA_SIGNATURE_SIZE))
#define _FW_UPDATE_RSA_KEY_NKEY_OFFSET           _FW_UPDATE_PUBLIC_KEY_OFFESET
#define _FW_UPDATE_RSA_KEY_RRMODN_OFFSET         (_FW_UPDATE_RSA_KEY_NKEY_OFFSET + _FW_UPDATE_RSA_KEY_NKEY_SIZE)
#define _FW_UPDATE_RSA_KEY_NPINV_OFFSET          (_FW_UPDATE_RSA_KEY_RRMODN_OFFSET + _FW_UPDATE_RSA_KEY_RRMODN_SIZE)
#define _FW_UPDATE_RSA_KEY_EXORKEY_OFFSET        (_FW_UPDATE_RSA_KEY_NPINV_OFFSET + _FW_UPDATE_RSA_KEY_NPINV_SIZE)

#define _HDCP2_SIGNATURE_FILE_MAX_SIZE           _FW_UPDATE_RSA_SIGNATURE_SIZE
#define _HDCP2_NKEY_MAX_SIZE                     _FW_UPDATE_RSA_KEY_NKEY_SIZE
#define _HDCP2_RRMODN_MAX_SIZE                   _FW_UPDATE_RSA_KEY_RRMODN_SIZE
#define _HDCP2_NPINV_MAX_SIZE                    _FW_UPDATE_RSA_KEY_NPINV_SIZE
#define _HDCP2_EKEY_MAX_SIZE                     _FW_UPDATE_RSA_KEY_EXORKEY_SIZE
#endif

#define GET_FW_UPDATE_STATUS()                   (g_stFwUpdateScalerInfo.b1FwUpdateStatus)
#define SET_FW_UPDATE_STATUS()                   (g_stFwUpdateScalerInfo.b1FwUpdateStatus = _TRUE)
#define CLR_FW_UPDATE_STATUS()                   (g_stFwUpdateScalerInfo.b1FwUpdateStatus = _FALSE)


#define GET_FW_UPDATE_STATE_BACKUPDDCCIMODE()    (g_stFwUpdateScalerInfo.enumBackupDDCCIMode)
#define SET_FW_UPDATE_STATE_BACKUPDDCCIMODE(x)   (g_stFwUpdateScalerInfo.enumBackupDDCCIMode = (x))

#define GET_FW_UPDATE_RUN_COMMAND()              (g_stFwUpdateScalerInfo.b1FwUpdateRunCommand)
#define SET_FW_UPDATE_RUN_COMMAND()              (g_stFwUpdateScalerInfo.b1FwUpdateRunCommand = _TRUE)
#define CLR_FW_UPDATE_RUN_COMMAND()              (g_stFwUpdateScalerInfo.b1FwUpdateRunCommand = _FALSE)

#define GET_FW_UPDATE_MODE()                     (g_stFwUpdateScalerInfo.enumFwUpdateMode)
#define SET_FW_UPDATE_MODE(x)                    (g_stFwUpdateScalerInfo.enumFwUpdateMode = (x))

#define GET_ISP_XRAM_BUFFER(x)                   ((volatile BYTE xdata *)(_HW_FLASH_PROG_USING_XRAM_START_ADDR + (x)))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Fw Update Type
//--------------------------------------------------
typedef enum
{
    _INVALID_MODE = 0x00,
    _BACKGROUND_MODE,
    _FOREGROUND_MODE
} EnumFwUpdateMode;

//--------------------------------------------------
// Struct of FwUpdate
//--------------------------------------------------
typedef struct
{
    BYTE b1FwUpdateStatus : 1;
    BYTE b1FwUpdateRunCommand : 1;
    EnumDDCCIDebugMode enumBackupDDCCIMode;
    EnumFwUpdateMode enumFwUpdateMode;
} StructFwUpdateScalerInfo;

#if((_FW_UPDATE_PROCESS_SUPPORT == _ON) && (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048))
typedef struct
{
    BYTE pucSignFile[_HDCP2_SIGNATURE_FILE_MAX_SIZE];
    BYTE pucSignNKey[_HDCP2_NKEY_MAX_SIZE];
    BYTE pucSignRrmodn[_HDCP2_RRMODN_MAX_SIZE];
    BYTE pucSignNpinv[_HDCP2_NPINV_MAX_SIZE];
    BYTE pucSignEKey[_HDCP2_EKEY_MAX_SIZE];
}StructSignKeyInfoType;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructFwUpdateScalerInfo g_stFwUpdateScalerInfo;
extern volatile BYTE g_pucFwUpdateRxBuf[_FW_UPDATE_BUF_LEN];
extern volatile WORD g_usFwUpdateDdcciCountEXINT;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
extern bit ScalerFwUpdateForegroundGetStatus(void);
#endif
extern void ScalerFwUpdateSwitchState(EnumDDCCIDebugMode enumDdcciMode, BYTE ucOpCode);
extern void ScalerFwUpdateSendReply(BYTE ucResult);
extern void ScalerFwUpdateSendData(BYTE ucLen, BYTE *pucData);
extern void ScalerFwUpdateInitRxBuf(void);

#endif
