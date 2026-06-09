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
// ID Code      : ScalerCommonDataPortAccess_EXINT0.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerCommonRegLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE ScalerEnableAccessPort_EXINT0(WORD usAddr, BYTE ucValue);
void ScalerDisableAccessPort_EXINT0(WORD usAddr);
void ScalerSetDataPortByte_EXINT0(WORD usAddr, BYTE ucValue1, BYTE ucValue2);
void ScalerSetDataPortBit_EXINT0(WORD usAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable Access Port
// Input Value  : usAddr    --> Start address of register
//                ucValue   --> Data Port Value we want to set
// Output Value : Return Access Port Value
//--------------------------------------------------
BYTE ScalerEnableAccessPort_EXINT0(WORD usAddr, BYTE ucValue) using 1
{
    usAddr = usAddr;
    return ucValue;
}

//--------------------------------------------------
// Description  : Disable Access Port
// Input Value  : usAddr   --> Start address of register
// Output Value : None
//--------------------------------------------------
void ScalerDisableAccessPort_EXINT0(WORD usAddr) using 1
{
    usAddr = usAddr;
}

//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                ucValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortByte_EXINT0(WORD usAddr, BYTE ucValue1, BYTE ucValue2) using 1
{
    ScalerSetByte_EXINT(usAddr, ScalerEnableAccessPort_EXINT0(usAddr, ucValue1));
    ScalerSetByte_EXINT(usAddr + 1, ucValue2);

    ScalerDisableAccessPort_EXINT0(usAddr);
}

//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortBit_EXINT0(WORD usAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr) using 1
{
    BYTE ucValueTemp = 0;

    // backup port addr
    BYTE ucBackupPortAddr = ScalerGetByte_EXINT(usAddr);

    ScalerSetByte_EXINT(usAddr, ScalerEnableAccessPort_EXINT0(usAddr, ucValue));
    ucValueTemp = ScalerGetByte_EXINT(usAddr + 1);

    ucValueTemp = (ucValueTemp & ucAnd) | ucOr;

    ScalerSetByte_EXINT(usAddr, ScalerEnableAccessPort_EXINT0(usAddr, ucValue));
    ScalerSetByte_EXINT(usAddr + 1, ucValueTemp);

    ScalerDisableAccessPort_EXINT0(usAddr);

    // return backup port addr
    ScalerSetByte_EXINT(usAddr, ucBackupPortAddr);
}
