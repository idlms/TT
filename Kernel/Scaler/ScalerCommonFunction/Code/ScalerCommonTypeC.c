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
// ID Code      : ScalerCommonTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
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
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
bit g_bTypeC5400LenovoAltModeUrgentEvent = _FALSE;
#endif
#endif

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTypeCHandler(BYTE ucInputPort);
EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort);
#if(_USB3_RETIMER_SUPPORT == _ON)
EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void);
#endif
EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort);
EnumTypeCOrientation ScalerTypeCGetOrientation(BYTE ucInputPort);
bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
EnumTypeCPowerRole ScalerTypeCGetPowerRole(BYTE ucInputPort);
bit ScalerTypeCReconnect(BYTE ucInputPort);
void ScalerTypeCWaitDpConfigUpdate(BYTE ucInputPort);
bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
void ScalerTypeCIntHandler_EXINT0(void);
void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction);
void ScalerTypeCSetPdoByKernel(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower);
void ScalerTypeCSetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
#endif
BYTE ScalerTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
StructTypeCUserPDO ScalerTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
void ScalerTypeCGetPdoStatus(BYTE ucInputPort, WORD *pusVoltage, WORD *pusCurrent);
StructTypeCUserPDO ScalerTypeCGetRequestedSrcPdo(BYTE ucInputPort);
EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount);
EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
void ScalerTypeCSetFixPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucVoltage, WORD usMaxCur, EnumPDPeakCurType enumPeakCur);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
void ScalerTypeCSetPpsPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur);
#endif
void ScalerTypeCSetRdo(BYTE ucInputPort, StructTypeCUserRDO stTypeCUserRdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo);
#endif
EnumTypeCUFPProductType ScalerTypeCGetUFPProductType(BYTE ucInputPort);
EnumTypeCDFPProductType ScalerTypeCGetDFPProductType(BYTE ucInputPort);
void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent);
EnumPDPortCtrlEvent ScalerTypeCGetPortCtrlEvent(BYTE ucInputPort);
void ScalerTypeCClrPortCtrlEvent(BYTE ucInputPort, EnumPDPortCtrlEvent enumPdPortCtrlEvent);
bit ScalerTypeCPowerControl(BYTE ucInputPort, EnumTypeCPowerControlStatus enumPowerControlStatus);
void ScalerTypeCCcFunctionControl(BYTE ucInputPort, EnumTypeCCcFunction enumCcFunction);
void ScalerTypeCSetFunctionSupport(BYTE ucInputPort, EnumTypeCFunctionSupport enumFunctionSupport);
void ScalerTypeCSetOperationMode(BYTE ucInputPort, EnumTypeCOperationMode enumOperationMode);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
EnumTypeCLenovoAltModeStatus ScalerTypeCGetLenovoAltModeReady(BYTE ucInputPort);
EnumTypeCLenovoDeviceType ScalerTypeCGetLenovoDeviceType(BYTE ucInputPort);
StructTypeCLenovoSysEvent ScalerTypeCGetLenovoSystemEvent(BYTE ucInputPort);
void ScalerTypeCSetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
bit ScalerTypeCCheckLenovoDockingEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
EnumTypeCAcerAltModeStatus ScalerTypeCGetAcerAltModeReady(BYTE ucInputPort);
StructTypeCAcerSysEvent ScalerTypeCGetAcerSystemEvent(BYTE ucInputPort);
void ScalerTypeCSetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent stAcerUserEvent);
EnumTypeCAcerBusyStatus ScalerTypeCCheckAcerUserEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
EnumTypeCHpAltModeStatus ScalerTypeCGetHpAltModeReady(BYTE ucInputPort);
StructTypeCHpSysEvent ScalerTypeCGetHpSystemEvent(BYTE ucInputPort);
void ScalerTypeCSetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent stHpUserEvent);
EnumTypeCHpBusyStatus ScalerTypeCCheckHpUserEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
EnumTypeCDellAltModeStatus ScalerTypeCGetDellAltModeReady(BYTE ucInputPort);
StructTypeCDellSysEvent ScalerTypeCGetDellSystemEvent(BYTE ucInputPort);
void ScalerTypeCSetDellUserEvent(BYTE ucInputPort, StructTypeCDellUserEvent stDellUserEvent);
void ScalerTypeCSetDellAltModeInitComplete(BYTE ucInputPort, EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus);
EnumTypeCDellBusyStatus ScalerTypeCCheckDellUserEventBusy(BYTE ucInputPort);
EnumTypeCEnterDellAltModeTimeOut ScalerTypeCGetEnterDellAltModeTimeOut(BYTE ucInputPort);
#endif
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
void ScalerTypeCGetAltModeBillboardInfo(BYTE ucInputPort, BYTE *pucBillboardAltModeInfo);
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Type C Handler Process
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void ScalerTypeCHandler(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0CcHandler();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller CC Attach Status to SysTypeC
// Input Value  : None
// Output Value : CC Attach Status (_TYPE_C_ATTACH / _TYPE_C_UNATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort)
{
    EnumTypeCAttachStatus enumCcAttach = _TYPE_C_UNATTACH;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(GET_CC_RX0_ATTACHED() == _TRUE)
            {
                enumCcAttach = _TYPE_C_ATTACH;
            }
            else
            {
                enumCcAttach = _TYPE_C_UNATTACH;
            }

            break;
#endif

        default:

            break;
    }

    return enumCcAttach;
}

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Ready Status to SysTypeC
// Input Value  : None
// Output Value : CC Attach (_TYPE_C_ATTACH / _TYPE_C_UNATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void)
{
    EnumTypeCAttachStatus enumCcAttach = _TYPE_C_UNATTACH;

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    enumCcAttach = (enumCcAttach | (EnumTypeCAttachStatus)GET_CC_RX0_ATTACHED());

#endif

    return enumCcAttach;
}
#endif

//--------------------------------------------------
// Description  : Return Port Controller DP Alt Mode Ready Status to SysTypeC
// Input Value  : None
// Output Value : DP Alt Mode Ready Status (_TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetAltModeReady() == _TRUE)
            {
                return _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                return _TYPE_C_ALT_MODE_NOT_READY;
            }
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller Orientation to SysTypeC
// Input Value  : None
// Output Value : _TYPE_C_ORIENTATION_NONE / _TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP
//--------------------------------------------------
EnumTypeCOrientation ScalerTypeCGetOrientation(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            return GET_CC_RX0_ORIENTATION();
#endif

        default:

            return _TYPE_C_ORIENTATION_NONE;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Pin Assignment to SysTypeC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            *penumPinAssignment = ScalerTypeCRx0PdGetPinAssignment();
            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller Power Role to SysTypeC
// Input Value  : ucInputPort
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_ROLE_NONE / _TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole ScalerTypeCGetPowerRole(BYTE ucInputPort)
{
    EnumTypeCPowerRole enumTypeCPowerRole = _TYPE_C_POWER_ROLE_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC)
            {
                enumTypeCPowerRole = _TYPE_C_POWER_SRC;
            }
            else
            {
                enumTypeCPowerRole = _TYPE_C_POWER_SNK;
            }

            break;
#endif

        default:

            break;
    }

    return enumTypeCPowerRole;
}

//--------------------------------------------------
// Description  : Type C Reconnect Process
// Input Value  : ucInputPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCReconnect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            SET_TYPE_C_ERROR_RECOVERY();

            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Ask Embedded PD to Wait for DP Config Update
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCWaitDpConfigUpdate(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdWaitDpConfig();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Configuration Update
// Input Value  : ucInputPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPinAssignmentCapability(enumPinAssignmentCap);
            ScalerTypeCRx0PdSetMultiFunctionBit(enumMultiFunc);

            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type C Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCIntHandler_EXINT0(void) using 1
{
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCPowerIntHandler_EXINT0();
    ScalerTypeCRx0CcIntHandler_EXINT0();
    ScalerTypeCRx0PdIntHandler_EXINT0();

    if((ScalerTypeCRx0CcIntClrCheck_EXINT0() == _TRUE) && (ScalerTypeCRx0PdIntClrCheck_EXINT0() == _TRUE))
    {
        MCU_FD29_UFP_DPF_IRQ_STATUS |= _BIT7;

        // Toggle Type C IRQ En to Prevent from IRQ Miss
        ScalerSetBit_EXINT(P6F_10_ADI_IRQ_CTRL, ~_BIT1, 0x00);
        ScalerSetBit_EXINT(P6F_10_ADI_IRQ_CTRL, ~_BIT1, _BIT1);
    }
#endif
}


//--------------------------------------------------
// Description  : Type C Power Switch Process
// Input Value  : enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction)
{
    enumPowerAction = enumPowerAction;

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCRx0CcPowerSwitch(enumPowerAction);
    ScalerTypeCRx0PdPowerSwitch(enumPowerAction);
#endif
}

//--------------------------------------------------
// Description  : Type C Set PDO By Kernel
// Input Value  : ucInputPort --> Inputput
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdoByKernel(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPdoByKernel(enumPowerRole);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Set Source Max Supply Power
// Input Value  : ucInputPort, usMaxPower in 0.1W
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetMaxPower(usMaxPower);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Set Number of PDO Counts
// Input Value  : ucInputPort, Number of PDO Counts (1~7)
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    enumPowerRole = enumPowerRole;
    ucPdoCnt = ucPdoCnt;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPdoCnt(enumPowerRole, ucPdoCnt);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Get Number of PDOs in PD FW (May Be User/Kernel-Defined)
// Input Value  : ucInputPort
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0;
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ucPdoCnt = ScalerTypeCRx0PdGetPdoCnt(enumPowerRole);

            break;
#endif

        default:

            break;
    }

    return ucPdoCnt;
}
#endif  // End of #if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)

//--------------------------------------------------
// Description  : Get Number of Partner Src/Snk PDOs
// Input Value  : ucInputPort
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE ScalerTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0x00;
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ucPdoCnt = ScalerTypeCRx0PdGetPartnerPdoCnt(enumPowerRole);

            break;
#endif

        default:

            break;
    }

    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Get Partner Source/Sink PDO Info
// Input Value  : ucInputPort, enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stTypeCPartnerPdo = ScalerTypeCRx0PdGetPartnerPdo(enumPowerRole, ucPdoIndex);

            break;
#endif

        default:

            break;
    }

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get TypeC Negotiated Voltage / Current
// Input Value  : ucInputPort, Voltage (10mV) / Current (10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCGetPdoStatus(BYTE ucInputPort, WORD *pusVoltage, WORD *pusCurrent)
{
    ucInputPort = ucInputPort;
    *pusVoltage = *pusVoltage;
    *pusCurrent = *pusCurrent;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdGetPdoStatus(pusVoltage, pusCurrent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Current Source PDO that Sink Request
// Input Value  : ucInputPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCGetRequestedSrcPdo(BYTE ucInputPort)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    ucInputPort = ucInputPort;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stTypeCSrcPdo = ScalerTypeCRx0PdGetRequestedSrcPdo();

            break;
#endif

        default:

            break;
    }

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Type C Check PDO Count Change
// Input Value  : ucInputPort, ucPdoCount
// Output Value : EnumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumSrcCapPdoChange = ScalerTypeCRx0PdCheckPdoCountChange(ucPdoCount);

            break;
#endif

        default:

            enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Type C Check PDO Change
// Input Value  : ucInputPort, ucPdoIndex, stTypeCUserPdo
// Output Value : EnumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumSrcCapPdoChange = ScalerTypeCRx0PdCheckPdoChange(ucPdoIndex, stTypeCUserPdo);

            break;
#endif

        default:

            enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Type C Set Fix Supply PDO
// Input Value  : ucInputPort, ucPdoIndex, ucVoltage(100mV), usMaxCur(10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetFixPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucVoltage, WORD usMaxCur, EnumPDPeakCurType enumPeakCur)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetFixPdo(enumPowerRole, ucPdoIndex, (WORD)ucVoltage, usMaxCur, enumPeakCur);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type C Set PPS PDO
// Input Value  : ucInputPort, ucPdoIndex, ucVoltage(100mV), ucMaxCur(50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPpsPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetArgumentedPdo(enumPowerRole, ucPdoIndex, ucMinVol, ucMaxVol, ucMaxCur);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Set Request Content to Kernel
// Input Value  : StructTypeCUserRDO(Object Position, ReqInfo1, ReqInfo2, Cap Mismatch)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetRdo(BYTE ucInputPort, StructTypeCUserRDO stTypeCUserRdo)
{
    stTypeCUserRdo = stTypeCUserRdo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetRdo(stTypeCUserRdo);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Type C Set Protect Info
// Input Value  : ucInputPort, ucPdoIndex, StructTypeCUserProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo)
{
    ucPdoIndex = ucPdoIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetProtectInfo(ucPdoIndex, stTypeCUserProtectInfo);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get TypeC Product Type when in UFP Data Role
// Input Value  : ucInputPort
// Output Value : TypeC Product Type UFP (_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_UFP_PRODUCT_TYPE_HUB / _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
//--------------------------------------------------
EnumTypeCUFPProductType ScalerTypeCGetUFPProductType(BYTE ucInputPort)
{
    EnumTypeCUFPProductType enumTypeCUFPProductType = _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumTypeCUFPProductType = ScalerTypeCRx0PdGetUFPProductType();

            break;
#endif

        default:

            break;
    }

    return enumTypeCUFPProductType;
}

//--------------------------------------------------
// Description  : Get TypeC Product Type when in DFP Data Role
// Input Value  : ucInputPort
// Output Value : TypeC Product Type DFP (_TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_DFP_PRODUCT_TYPE_HUB / _TYPE_C_DFP_PRODUCT_TYPE_HOST / _TYPE_C_DFP_PRODUCT_TYPE_BRICK)
//--------------------------------------------------
EnumTypeCDFPProductType ScalerTypeCGetDFPProductType(BYTE ucInputPort)
{
    EnumTypeCDFPProductType enumTypeCDFPProductType = _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumTypeCDFPProductType = ScalerTypeCRx0PdGetDFPProductType();

            break;
#endif

        default:

            break;
    }

    return enumTypeCDFPProductType;
}

//--------------------------------------------------
// Description  : Type C Set Source Capability Change Flag
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetSystemEvent(enumPdSysEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Embedded Port Controller Event
// Input Value  : ucInputPort
// Output Value : EnumPDPortCtrlEvent (_PD_PORT_CTRL_EVENT_POWER_OCP / _PD_PORT_CTRL_EVENT_POWER_OVP...)
//--------------------------------------------------
EnumPDPortCtrlEvent ScalerTypeCGetPortCtrlEvent(BYTE ucInputPort)
{
    EnumPDPortCtrlEvent enumPortCtrlEvent = _PD_PORT_CTRL_EVENT_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumPortCtrlEvent = ScalerTypeCRx0PdGetPortCtrlEvent();

            break;
#endif

        default:

            break;
    }

    return enumPortCtrlEvent;
}

//--------------------------------------------------
// Description  : Clear Embedded Port Controller Event
// Input Value  : ucInputPort, enumPdPortCtrlEvent (_PD_PORT_CTRL_EVENT_POWER_OCP / _PD_PORT_CTRL_EVENT_POWER_OVP...)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCClrPortCtrlEvent(BYTE ucInputPort, EnumPDPortCtrlEvent enumPdPortCtrlEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdClrPortCtrlEvent(enumPdPortCtrlEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Control Type-C Power Off/On
// Input Value  : ucInputPort, enumPowerControlStatus
// Output Value : Control Power Result (_SUCCESS / _FAIL)
//--------------------------------------------------
bit ScalerTypeCPowerControl(BYTE ucInputPort, EnumTypeCPowerControlStatus enumPowerControlStatus)
{
    bit bControlResult = _FAIL;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(enumPowerControlStatus == _TYPE_C_POWER_OFF)
            {
                // Judge CC Attach Status
                if(ScalerTypeCGetCcAttach(_D0_INPUT_PORT) == _TYPE_C_ATTACH)
                {
                    // Set CC Disconnect Before Power Cut
                    ScalerTypeCCcFunctionControl(_D0_INPUT_PORT, _TYPE_C_CC_FUNCTION_DISABLE);
                }
                else
                {
                    // Power Cut TypeC
                    // Group Type-C isolation control
                    ScalerPowerGroupTPCUFPIsolation(_ON);

                    // Group Type-C power control
                    ScalerPowerGroupTPCUFPPowerCut(_ON);

                    // =================
                    // Type-C SARADC
                    // =================
                    // Disable SARADC Auto Mode & Conversion
                    ScalerSetBit(P7F_00_10B_ADC_CTL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                    // Disable SARADC LDO
                    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT0, 0x00);

                    bControlResult = _SUCCESS;
                }
            }
            else if(enumPowerControlStatus == _TYPE_C_POWER_ON)
            {
                // Power On TypeC
                // Group TPCUFP Power Cut block Reset
                ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT0, _BIT0);

                // Group Type-C power control
                ScalerPowerGroupTPCUFPPowerCut(_OFF);

                // Group Type-C isolation control
                ScalerPowerGroupTPCUFPIsolation(_OFF);

                // Group TPCUFP Power Cut Release
                ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT0, 0x00);

                // =================
                // Type-C SARADC
                // =================
                // Enable SARADC LDO
                ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT0, _BIT0);

                ScalerTimerDelayXms(2);

                // Enable SARADC Auto Mode & Conversion
                ScalerSetBit(P7F_00_10B_ADC_CTL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

                bControlResult = _SUCCESS;
            }

            break;
#endif

        default:

            break;
    }

    return bControlResult;
}

//--------------------------------------------------
// Description  : Control TypeC CC Function
// Input Value  : ucInputPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCCcFunctionControl(BYTE ucInputPort, EnumTypeCCcFunction enumCcFunction)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0CcFunctionControl(enumCcFunction);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Type-C Function Support Option to PD/CC FW
// Input Value  : ucInputPort, enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetFunctionSupport(BYTE ucInputPort, EnumTypeCFunctionSupport enumFunctionSupport)
{
    enumFunctionSupport = enumFunctionSupport;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0CcSetFunctionSupport(enumFunctionSupport);
            ScalerTypeCRx0PdSetFunctionSupport(enumFunctionSupport);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set User-Defined Type-C Operation Mode to CC FW
// Input Value  : ucInputPort, enumOperationMode
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetOperationMode(BYTE ucInputPort, EnumTypeCOperationMode enumOperationMode)
{
    enumOperationMode = enumOperationMode;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0CcSetOperationMode(enumOperationMode);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Return Port Controller Lenovo Alt Mode Ready Status to SysTypeC
// Input Value  : ucInputPort
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus ScalerTypeCGetLenovoAltModeReady(BYTE ucInputPort)
{
    EnumTypeCLenovoAltModeStatus enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetLenovoAltModeReady() == _TRUE)
            {
                enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_READY;
            }
            else
            {
                enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif

        default:

            break;
    }

    return enumLenovoAltModeStatus;
}

//--------------------------------------------------
// Description  : Return Port Controller Partner Lenovo Device Type
// Input Value  : ucInputPort
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType ScalerTypeCGetLenovoDeviceType(BYTE ucInputPort)
{
    EnumTypeCLenovoDeviceType enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumLenovoDeviceType = ScalerTypeCRx0PdGetLenovoDeviceType();

            break;
#endif

        default:

            break;
    }

    return enumLenovoDeviceType;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent ScalerTypeCGetLenovoSystemEvent(BYTE ucInputPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stLenovoSysEvent = ScalerTypeCRx0PdGetLenovoSystemEvent();

            break;
#endif

        default:

            break;
    }

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : ucInputPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetLenovoDockingEvent(stLenovoDockEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : ucInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCCheckLenovoDockingEventBusy(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            return ScalerTypeCRx0PdCheckLenovoDockingEventBusy();

            break;
#endif

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Controller Acer Alt Mode Ready Status
// Input Value  : ucInputPort
// Output Value : Acer Alt Mode Ready Status (_TYPE_C_ACER_ALT_MODE_READY / _TYPE_C_ACER_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAcerAltModeStatus ScalerTypeCGetAcerAltModeReady(BYTE ucInputPort)
{
    EnumTypeCAcerAltModeStatus enumAcerAltModeStatus = _TYPE_C_ACER_ALT_MODE_NOT_READY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetAcerAltModeReady() == _TRUE)
            {
                enumAcerAltModeStatus = _TYPE_C_ACER_ALT_MODE_READY;
            }
            else
            {
                enumAcerAltModeStatus = _TYPE_C_ACER_ALT_MODE_NOT_READY;
            }

            break;
#endif

        default:

            break;
    }

    return enumAcerAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCAcerSysEvent
//--------------------------------------------------
StructTypeCAcerSysEvent ScalerTypeCGetAcerSystemEvent(BYTE ucInputPort)
{
    StructTypeCAcerSysEvent stAcerSysEvent = {_TYPE_C_ACER_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stAcerSysEvent = ScalerTypeCRx0PdGetAcerSystemEvent();

            break;
#endif

        default:

            break;
    }

    return stAcerSysEvent;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Set User Event
// Input Value  : ucInputPort, stAcerUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent stAcerUserEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetAcerUserEvent(stAcerUserEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Check if Last User Event has been Sent
// Input Value  : ucInputPort
// Output Value : User Event Busy Status (_TYPE_C_ACER_USER_EVENT_BUSY / _TYPE_C_ACER_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCAcerBusyStatus ScalerTypeCCheckAcerUserEventBusy(BYTE ucInputPort)
{
    EnumTypeCAcerBusyStatus enumCheckBusyResult = _TYPE_C_ACER_USER_EVENT_NOT_BUSY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumCheckBusyResult = ScalerTypeCRx0PdCheckAcerUserEventBusy();

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Hp Alt Mode Ready Status
// Input Value  : ucInputPort
// Output Value : Hp Alt Mode Ready Status (_TYPE_C_HP_ALT_MODE_READY / _TYPE_C_HP_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCHpAltModeStatus ScalerTypeCGetHpAltModeReady(BYTE ucInputPort)
{
    EnumTypeCHpAltModeStatus enumHpAltModeStatus = _TYPE_C_HP_ALT_MODE_NOT_READY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetHpAltModeReady() == _TRUE)
            {
                enumHpAltModeStatus = _TYPE_C_HP_ALT_MODE_READY;
            }
            else
            {
                enumHpAltModeStatus = _TYPE_C_HP_ALT_MODE_NOT_READY;
            }

            break;
#endif

        default:

            break;
    }

    return enumHpAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCHpSysEvent
//--------------------------------------------------
StructTypeCHpSysEvent ScalerTypeCGetHpSystemEvent(BYTE ucInputPort)
{
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stHpSysEvent = ScalerTypeCRx0PdGetHpSystemEvent();

            break;
#endif

        default:

            break;
    }

    return stHpSysEvent;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Set User Event
// Input Value  : ucInputPort, stHpUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent stHpUserEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetHpUserEvent(stHpUserEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Check if Last User Event has been Sent
// Input Value  : ucInputPort
// Output Value : User Event Busy Status (_TYPE_C_HP_USER_EVENT_BUSY / _TYPE_C_HP_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCHpBusyStatus ScalerTypeCCheckHpUserEventBusy(BYTE ucInputPort)
{
    EnumTypeCHpBusyStatus enumCheckBusyResult = _TYPE_C_HP_USER_EVENT_NOT_BUSY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumCheckBusyResult = ScalerTypeCRx0PdCheckHpUserEventBusy();

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Dell Alt Mode Ready Status
// Input Value  : ucInputPort
// Output Value : Dell Alt Mode Ready Status (_TYPE_C_DELL_ALT_MODE_READY / _TYPE_C_DELL_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCDellAltModeStatus ScalerTypeCGetDellAltModeReady(BYTE ucInputPort)
{
    EnumTypeCDellAltModeStatus enumDellAltModeStatus = _TYPE_C_DELL_ALT_MODE_NOT_READY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumDellAltModeStatus = (ScalerTypeCRx0PdGetDellAltModeReady() == _TRUE ? _TYPE_C_DELL_ALT_MODE_READY : _TYPE_C_DELL_ALT_MODE_NOT_READY);

            break;
#endif

        default:

            break;
    }

    return enumDellAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCDellSysEvent
//--------------------------------------------------
StructTypeCDellSysEvent ScalerTypeCGetDellSystemEvent(BYTE ucInputPort)
{
    StructTypeCDellSysEvent stDellSysEvent = {_TYPE_C_DELL_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stDellSysEvent = ScalerTypeCRx0PdGetDellSystemEvent();

            break;
#endif

        default:

            break;
    }

    return stDellSysEvent;
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set User Event
// Input Value  : ucInputPort, stDellUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetDellUserEvent(BYTE ucInputPort, StructTypeCDellUserEvent stDellUserEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetDellUserEvent(stDellUserEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set Initial Complete Status
// Input Value  : ucInputPort, enumDellInitCompleteStatus (_TYPE_C_DELL_INIT_COMPLETE / _TYPE_C_DELL_INIT_NOT_COMPLETE)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetDellAltModeInitComplete(BYTE ucInputPort, EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetDellAltModeInitComplete(enumDellInitCompleteStatus);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Check if Last User Event has been Sent
// Input Value  : ucInputPort
// Output Value : User Event Busy Status (_TYPE_C_DELL_USER_EVENT_BUSY / _TYPE_C_DELL_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCDellBusyStatus ScalerTypeCCheckDellUserEventBusy(BYTE ucInputPort)
{
    EnumTypeCDellBusyStatus enumCheckBusyResult = _TYPE_C_DELL_USER_EVENT_NOT_BUSY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumCheckBusyResult = ScalerTypeCRx0PdCheckDellUserEventBusy();

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}

//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Enter Dell Alt Mode Time Out Result
// Input Value  : ucInputPort
// Output Value : Enter Dell Alt Mode Time Out Result (_TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT/ _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT)
//--------------------------------------------------
EnumTypeCEnterDellAltModeTimeOut ScalerTypeCGetEnterDellAltModeTimeOut(BYTE ucInputPort)
{
    EnumTypeCEnterDellAltModeTimeOut enumEnterDellAMTimeOutResult = _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumEnterDellAMTimeOutResult = ScalerTypeCRx0PdGetEnterDellAltModeTimeOut();

            break;
#endif

        default:

            break;
    }

    return enumEnterDellAMTimeOutResult;
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type C Alt Mode Related Info for Billboard Display
// Input Value  : ucInputPort , Pointer of Billboard Info
// Output Value : None
//--------------------------------------------------
void ScalerTypeCGetAltModeBillboardInfo(BYTE ucInputPort, BYTE *pucBillboardAltModeInfo)
{
    pucBillboardAltModeInfo = pucBillboardAltModeInfo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            ScalerTypeCRx0PdGetAltModeBillboardInfo(pucBillboardAltModeInfo);
#endif

            break;
#endif

        default:

            break;
    }
}
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)

#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
