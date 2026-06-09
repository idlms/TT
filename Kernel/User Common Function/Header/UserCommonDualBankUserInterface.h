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
// ID Code      : UserCommonDualBankUserInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DUAL_BANK_STATE_NONE = 0,
    _DUAL_BANK_STATE_RUN,
    _DUAL_BANK_STATE_VERIFY,
    _DUAL_BANK_STATE_WAIT_SWITCH,
    _DUAL_BANK_STATE_SWITCH,
    _DUAL_BANK_STATE_COPY,
}EnumDualBankState;


typedef enum
{
    _USER_ILLEGAL = 0,
    _USER_VALID,
    _USER_INVALID,
    _USER_VERIFY,
    _USER_WAIT_SWITCH,
    _USER_SWITCH,
    _USER_COPY,
}EnumDualBankUserStatus;

typedef enum
{
    _VERIFY_RESULT_PASS = 0,
    _VERIFY_RESULT_FAIL,
}EnumDualBankVerifyResult;

typedef enum
{
    _COPY_RESULT_PASS = 0,
    _COPY_RESULT_FAIL,
}EnumDualBankCopyResult;

typedef enum
{
    _REGION_NONE = 0,
    _REGION_BOOT,
    _REGION_USER_I,
    _REGION_USER_II,
}EnumDualBankCodeRegion;

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************


//****************************************************************************
// INTERFACE  FUNCTION EXTERN
//****************************************************************************
extern void UserCommonDualBankUserDebug(void);
#endif
