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
// ID Code      : ScalerCommonFwCheck.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_FWCHECK__

#include "ScalerCommonFunctionInclude.h"


#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
// User Should Be Define 12 Byte Strings For Every Project In Order To Tool Isp Checking
BYTE code tFwProjectIDTable[] =
{
    _ISP_FW_CHECK_PROJECT_ID_DATA
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumProjectIDVerifyResult ScalerFwCheckProjectIDVerify(BYTE *pucBuf);
void ScalerFwCheckGetProjectIDAddress(BYTE *pucArray);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Verify Project ID
// Input Value  : Project ID Data Buffer
// Output Value : Verify Result
//--------------------------------------------------
EnumProjectIDVerifyResult ScalerFwCheckProjectIDVerify(BYTE *pucBuf)
{
    if(CHECK_FW_PROJECT_ID(pucBuf, tFwProjectIDTable, sizeof(tFwProjectIDTable)) == _TRUE)
    {
        return _ISP_FW_CHECK_VERIFY_SUCCESS;
    }

    return _ISP_FW_CHECK_VERIFY_FAIL;
}

//--------------------------------------------------
// Description  : Get Project ID Address
// Input Value  : None
// Output Value : Project ID Address
//--------------------------------------------------
void ScalerFwCheckGetProjectIDAddress(BYTE *pucArray)
{
    // 4 byte Flash Address
    pucArray[0] = 0x00;
    pucArray[1] = _ISP_FW_CHECK_PROJECT_ID_LOCATION_BANK;
    pucArray[2] = ((WORD)_ISP_FW_CHECK_PROJECT_ID_LOCATION_ADDRESS >> 8) & 0xFF;
    pucArray[3] = ((WORD)_ISP_FW_CHECK_PROJECT_ID_LOCATION_ADDRESS) & 0xFF;
    pucArray[4] = sizeof(tFwProjectIDTable);
}
#endif // End of #if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
