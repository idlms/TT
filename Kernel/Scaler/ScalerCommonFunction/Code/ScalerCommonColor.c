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
// ID Code      : ScalerCommonColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_COLOR__

#include "ScalerCommonFunctionInclude.h"

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
StructColorInfo g_pstColorInfo[_COLOR_INFO_NUM];
StructColorInfo *g_pstColorInfoPointer = &g_pstColorInfo[0];
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
void ScalerColorSwitchColorInfoArray(EnumColorInfo enumColorInfo);
void ScalerColorSwitchColorInfoArray_EXINT0(EnumColorInfo enumColorInfo);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************


#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Change ColorInfoPointer
// Input Value  : EnumColorInfo _COLOR_INFO_SYSTEM or COLOR_INFO_BG_DETECT
// Output Value : None
//--------------------------------------------------
void ScalerColorSwitchColorInfoArray(EnumColorInfo enumColorInfo)
{
    g_pstColorInfoPointer = &g_pstColorInfo[enumColorInfo % _COLOR_INFO_NUM];
}

//--------------------------------------------------
// Description  : Change ColorInfoPointer
// Input Value  : EnumColorInfo _COLOR_INFO_SYSTEM or COLOR_INFO_BG_DETECT
// Output Value : None
//--------------------------------------------------
void ScalerColorSwitchColorInfoArray_EXINT0(EnumColorInfo enumColorInfo) using 1
{
    g_pstColorInfoPointer = &g_pstColorInfo[enumColorInfo];
}

#endif

