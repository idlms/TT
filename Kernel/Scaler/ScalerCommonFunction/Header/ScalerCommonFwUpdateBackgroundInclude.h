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
// ID Code      : ScalerCommonFwUpdateBackgroundInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
#if(_DP_TX_SUPPORT == _ON)
    BYTE b1DpTxBusyStatus : 1;
#endif
#if(_DP_SUPPORT == _ON)
    BYTE b1DpRxBusyStatus : 1;
#endif
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    BYTE b1TypeCBusyStatus : 1;
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
    BYTE b1MCCSBusyStatus : 1;
#endif
    BYTE b1HdcpBusyStatus : 1;
} StructSysBusyStatusInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructSysBusyStatusInfo g_stFwUpdateBackgroundSysStatusInfo;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern EnumBusyStatusInfo ScalerFwUpdateBackgroundGetSystemStatus(void);
extern void ScalerFwUpdateBackgroundSetBusyStatus(EnumBackgroundFwUpdateAffectedIp enumIp, EnumBusyStatusInfo enumStatus, WORD usTime);

#endif
