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
// ID Code      : UserCommonFwUpdatePassword.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_FW_UPDATE_PASSWORD_TABLE__

#include "UserCommonInclude.h"

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tFwPassword[] =
{
    _FW_UPDATE_PASSWORD_DATA,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit UserCommonFwUpdatePasswordVerify(BYTE ucBank, WORD usAddr);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Fw Update Password Verify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdatePasswordVerify(BYTE ucBank, WORD usAddr)
{
    BYTE pucPasswordTable[sizeof(tFwPassword)];

    // Read BootTable data from Flash
    UserCommonFlashRead(ucBank, usAddr, sizeof(tFwPassword), pucPasswordTable);

    // Check user-defined user/boot code id
    if(memcmp(tFwPassword, pucPasswordTable, sizeof(tFwPassword)) == 0)
    {
        // Check success; return user bank address
        return _TRUE;
    }
    return _FALSE;
}

#endif // End #if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)

#endif  // End #if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

