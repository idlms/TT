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
// ID Code      : ScalerCommonFwInfo.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_FW_INFO__
#include "ScalerCommonFunctionInclude.h"

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tFwVersionTable[] =
{
    _CUSTOMER_FW_VERSION,
    _CUSTOMER_FW_SUB_VERSION,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerFwInfoGetCurrentVersion(BYTE *pucArray);
void ScalerFwInfoGetFwVersionAddress(BYTE *pucArray);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Currten Fw Version
// Input Value  : None
// Output Value : Version Info
//--------------------------------------------------
void ScalerFwInfoGetCurrentVersion(BYTE *pucArray)
{
    // Set FW Version
    pucArray[0] = _CUSTOMER_FW_VERSION;
    pucArray[1] = _CUSTOMER_FW_SUB_VERSION;
}

//--------------------------------------------------
// Description  : Get Fw Version locate in Bin File
// Input Value  : None
// Output Value : Version Info
//--------------------------------------------------
void ScalerFwInfoGetFwVersionAddress(BYTE *pucArray)
{
    // 4 byte Flash Address
    pucArray[0] = 0x00;
    pucArray[1] = _CUSTOMER_FW_VERSION_LOCATE_BANK;
    pucArray[2] = ((WORD)_CUSTOMER_FW_VERSION_LOCATE_ADDRESS >> 8) & 0xFF;
    pucArray[3] = ((WORD)_CUSTOMER_FW_VERSION_LOCATE_ADDRESS) & 0xFF;
    pucArray[4] = sizeof(tFwVersionTable);
}
#endif
