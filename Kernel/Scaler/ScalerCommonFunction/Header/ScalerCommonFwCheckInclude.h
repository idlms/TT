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
// ID Code      : ScalerCommonFwCheckInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _SCALER_FW_CHECK_CMD                                    0xCB
#define _SCALER_FW_CHECK_SUB_OP_GET_ADDR                        0x01
#define _SCALER_FW_CHECK_SUB_OP_VERIFY                          0x02

#define _ISP_FW_CHECK_COMMAND_BUF_LEN                           0x10

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// Enumerations of Project ID Verify Result
//--------------------------------------------------
typedef enum
{
    _ISP_FW_CHECK_VERIFY_FAIL = _FALSE,
    _ISP_FW_CHECK_VERIFY_SUCCESS = _TRUE,
} EnumProjectIDVerifyResult;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumProjectIDVerifyResult ScalerFwCheckProjectIDVerify(BYTE *pucBuf);
extern void ScalerFwCheckGetProjectIDAddress(BYTE *pucArray);

#endif // End of #if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)

