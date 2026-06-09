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
// ID Code      : ScalerDPRx1_SeptPhyInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_HDCP14_REPEATER_BIT_DISABLE_FOR_TX_CLONE_OFF == _ON)
#define GET_DP_RX1_HDCP14_REPEATER_SUPPORT()                         (g_bDpRx1HdcpRepeaterBit)
#define SET_DP_RX1_HDCP14_REPEATER_SUPPORT(x)                        (g_bDpRx1HdcpRepeaterBit = (x))
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_HDCP14_REPEATER_BIT_DISABLE_FOR_TX_CLONE_OFF == _ON)
extern bit g_bDpRx1HdcpRepeaterBit;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_D1_DP_EXIST == _ON)

extern void ScalerDpRx1AuxSet(void);
extern void ScalerDpRx1SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
extern void ScalerDpRx1HDCPBlockReset(void);

#endif

