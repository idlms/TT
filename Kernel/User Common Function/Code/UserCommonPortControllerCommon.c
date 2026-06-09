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
// ID Code      : UserCommonPortControllerCommon.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLER_COMMON__

#include "UserCommonInclude.h"

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
#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
StructPortControllerCommonInfo g_stTypeCPortControllerD0CommonInfo;
#endif

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
StructPortControllerCommonInfo g_stTypeCPortControllerD1CommonInfo;
#endif

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
StructPortControllerCommonInfo g_stTypeCPortControllerD6CommonInfo;
#endif
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumTypeCPinCfgCapType UserCommonPortControllerGetPinAssignmentConfig(BYTE ucInputPort);
EnumTypeCMultiFuncStatus UserCommonPortControllerGetMultiFuncConfig(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignmentCap);
EnumTypeCPinMismatchAction UserCommonPortControllerGetPinAssignmentMismatchAction(BYTE ucInputPort);
EnumTypeCAltModeWaitStatus UserCommonPortControllerGetDpAltModeWaitStatus(BYTE ucInputPort);
EnumTypeCFunctionSupport UserCommonPortControllerGetFunctionSupport(BYTE ucInputPort);
EnumTypeCOperationMode UserCommonPortControllerGetOperationMode(BYTE ucInputPort);

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
EnumTypeCAttachStatus UserCommonPortControllerGetCcAttach(BYTE ucInputPort);
EnumTypeCAltModeStatus UserCommonPortControllerGetAltModeReady(BYTE ucInputPort);
bit UserCommonPortControllerUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);

#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
void UserCommonPortControllerSetD0I2CDetection(void);
void UserCommonPortControllerRestartD0I2CDetection(WORD usTime);
#endif

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
void UserCommonPortControllerSetD1I2CDetection(void);
void UserCommonPortControllerRestartD1I2CDetection(WORD usTime);
#endif

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
void UserCommonPortControllerSetD6I2CDetection(void);
void UserCommonPortControllerRestartD6I2CDetection(WORD usTime);
#endif

void UserCommonPortControllerPinMappingSetting(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
EnumTypeCPortCtrlReconnectStatus UserCommonPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch);
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Define Pin Assignment According to U3 Mode
// Input Value  : ucInputPort --> Input Port
// Output Value : Pin Config Capability Type
//--------------------------------------------------
EnumTypeCPinCfgCapType UserCommonPortControllerGetPinAssignmentConfig(BYTE ucInputPort)
{
    // Default Set Pin Assignment E Support Status to ON
    EnumTypeCU3ModeType enumU3ModeSel = _TYPE_C_U3_OFF;
    EnumTypeCPinCfgCapType enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_NONE;
    EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON;

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    // Update Pin Assignment E Support Capability (From User)
    if(UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(ucInputPort) == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF)
    {
        enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF;
    }
#endif

    // Update U3 Mode (From OSD)
    enumU3ModeSel = (UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_ON) ? _TYPE_C_U3_ON : _TYPE_C_U3_OFF;

    enumPinAssignmentCap = UserInterfaceTypeCGetPinConfigType(ucInputPort, enumU3ModeSel, enumPinAssignmentESupportStatus);

    if(enumPinAssignmentCap == _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT)
    {
        if(SysTypeCGetExtPortCtrlAcOnFlag(ucInputPort) == _TRUE)
        {
            // If (Ext Port Ctrl AC ON == _TRUE), Set Pin Assignment Cap to None
            enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_NONE;
        }
        else
        {
            // Use Kernal Default Setting if User Select Follow Kernel Setting
            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportStatus == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportStatus == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }
        }
    }

    return enumPinAssignmentCap;
}

//--------------------------------------------------
// Description  : User Define Multi Function According to U3 Mode
// Input Value  : ucInputPort --> Input Port
//                enumPinAssignmentCap --> _TYPE_C_PIN_ASSIGNMENT_CAP_NONE / _TYPE_C_PIN_ASSIGNMENT_CAP_C / ...
// Output Value : Multi Function Status
//--------------------------------------------------
EnumTypeCMultiFuncStatus UserCommonPortControllerGetMultiFuncConfig(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    EnumTypeCU3ModeType enumU3ModeSel = _TYPE_C_U3_OFF;
    EnumTypeCMultiFuncStatus enumMultiFunc = _TYPE_C_MULTI_FUNC_NOT_PREFER;
    enumPinAssignmentCap = enumPinAssignmentCap;

    // Update U3 Mode (From OSD)
    enumU3ModeSel = (UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_ON) ? _TYPE_C_U3_ON : _TYPE_C_U3_OFF;

    enumMultiFunc = UserInterfaceTypeCGetMultiFuncConfig(ucInputPort, enumU3ModeSel);

    if(enumMultiFunc == _TYPE_C_MULTI_FUNC_DEFAULT)
    {
        // Default Setting, Set Multi-Function Prefer according to Pin Assignment-D Exist or not
        enumMultiFunc = ((enumPinAssignmentCap & _BIT3) == _BIT3) ? _TYPE_C_MULTI_FUNC_PREFER : _TYPE_C_MULTI_FUNC_NOT_PREFER;
    }

    return enumMultiFunc;
}

//--------------------------------------------------
// Description  : Check Action for Pin Assignment Mismatch
// Input Value  : ucInputPort --> Input Port
// Output Value : return _TYPE_C_PIN_ASSIGNMENT_MISMATCH_NO_ACTION / _TYPE_C_PIN_ASSIGNMENT_MISMATCH_RECONNECT
//--------------------------------------------------
EnumTypeCPinMismatchAction UserCommonPortControllerGetPinAssignmentMismatchAction(BYTE ucInputPort)
{
    return UserInterfaceTypeCGetPinAssignmentMismatchAction(ucInputPort);
}

//--------------------------------------------------
// Description  : TypeC Get Dp Alt Mode Wait Status
// Input Value  : ucInputPort --> Input Port
// Output Value : Dp Alt Mode Wait Status (_TYPE_C_ALT_MODE_WAIT / _TYPE_C_ALT_MODE_NOT_WAIT)
//--------------------------------------------------
EnumTypeCAltModeWaitStatus UserCommonPortControllerGetDpAltModeWaitStatus(BYTE ucInputPort)
{
    return UserInterfaceTypeCGetDpAltModeWaitStatus(ucInputPort);
}

//--------------------------------------------------
// Description  : Get Type-C Function Support Option
// Input Value  : ucInputPort --> Input Port
// Output Value : Type-C Function Support Option (_TYPE_C_SUPPORT_NO_FUNCTION / _TYPE_C_SUPPORT_CC_FUNCTION / _TYPE_C_SUPPORT_CC_AND_PD_FUNCTION...)
//--------------------------------------------------
EnumTypeCFunctionSupport UserCommonPortControllerGetFunctionSupport(BYTE ucInputPort)
{
    EnumTypeCFunctionSupport enumFunctionSupport = _TYPE_C_SUPPORT_DEFAULT_FUNCTION;

    enumFunctionSupport = UserInterfaceTypeCGetFunctionSupport(ucInputPort);

    if(enumFunctionSupport == _TYPE_C_SUPPORT_DEFAULT_FUNCTION)
    {
        enumFunctionSupport = _TYPE_C_SUPPORT_FULL_FUNCTION;
    }

    return enumFunctionSupport;
}

//--------------------------------------------------
// Description  : Get Type-C Operation Mode
// Input Value  : ucInputPort --> Input Port
// Output Value : Type-C Operation Mode (_TYPE_C_SRC_ONLY_MODE / _TYPE_C_SNK_ONLY_MODE / _TYPE_C_DRP_NO_PREFERENCE_MODE...)
//--------------------------------------------------
EnumTypeCOperationMode UserCommonPortControllerGetOperationMode(BYTE ucInputPort)
{
    EnumTypeCOperationMode enumOperationMode = _TYPE_C_DEFAULT_OPERATION_MODE;

    enumOperationMode = UserInterfaceTypeCGetOperationMode(ucInputPort);

    if(enumOperationMode == _TYPE_C_DEFAULT_OPERATION_MODE)
    {
        enumOperationMode = SysTypeCGetDefaultOperationMode(ucInputPort);
    }

    return enumOperationMode;
}

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get D0 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetCcAttach(BYTE ucInputPort)
{
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
    if(UserCommonPortControllerGet5400I2CEnabledFlag(ucInputPort) == _FALSE)
    {
        // 5400 Port Ctrl  : Enable Vender Command
        if(UserCommonPortControllerEnable5400VenderCommand(ucInputPort) == _SUCCESS)
        {
            // 5400 Port Ctrl : Set I2C Communication Enabled Flag
            UserCommonPortControllerSet5400I2CEnabledFlag(ucInputPort);
        }
        else
        {
            DebugMessageSystem("8. Enable Vender Command Fail ! ! !", 0);
            return _TYPE_C_UNATTACH;
        }
    }
#endif

    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO)
            return ((PCB_D0_CC_ATTACH_PIN() == _PCB_DP_TYPE_C_CC_ATTACHED_LEVEL) ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)
            return UserInterfaceTypeCGetPortControllerCcAttach(ucInputPort);
#elif(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            return UserCommonPortControllerGetD0CcAttachByI2C();
#endif
            break;
#endif  // End of #if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO)
            return ((PCB_D1_CC_ATTACH_PIN() == _PCB_DP_TYPE_C_CC_ATTACHED_LEVEL) ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)
            return UserInterfaceTypeCGetPortControllerCcAttach(ucInputPort);
#elif(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            return UserCommonPortControllerGetD1CcAttachByI2C();
#endif
            break;
#endif  // End of #if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO)
            return ((PCB_D6_CC_ATTACH_PIN() == _PCB_DP_TYPE_C_CC_ATTACHED_LEVEL) ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);
#elif(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)
            return UserInterfaceTypeCGetPortControllerCcAttach(ucInputPort);
#elif(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            return UserCommonPortControllerGetD6CcAttachByI2C();
#endif
            break;
#endif  // End of #if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

        default:

            return _TYPE_C_UNATTACH;

            break;
    }

    return _TYPE_C_UNATTACH;
}

//--------------------------------------------------
// Description  : Get DP Alt. Mode Ready Status
// Input Value  : ucInputPort --> Inputput
// Output Value : DP Alt Mode Ready Status (_TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO)
            return ((PCB_D0_ALT_MODE_PIN() == _PCB_DP_TYPE_C_ALTMODE_LEVEL) ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)
            return UserInterfaceTypeCGetPortControllerAltModeReady(ucInputPort);
#elif(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            return UserCommonPortControllerGetD0AltModeReadyByI2C();
#endif
            break;
#endif  // End of #if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))


#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO)
            return ((PCB_D1_ALT_MODE_PIN() == _PCB_DP_TYPE_C_ALTMODE_LEVEL) ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)
            return UserInterfaceTypeCGetPortControllerAltModeReady(ucInputPort);
#elif(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            return UserCommonPortControllerGetD1AltModeReadyByI2C();
#endif
            break;
#endif // End of #if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO)
            return ((PCB_D6_ALT_MODE_PIN() == _PCB_DP_TYPE_C_ALTMODE_LEVEL) ? _TYPE_C_ALT_MODE_READY : _TYPE_C_ALT_MODE_NOT_READY);
#elif(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)
            return UserInterfaceTypeCGetPortControllerAltModeReady(ucInputPort);
#elif(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            return UserCommonPortControllerGetD6AltModeReadyByI2C();
#endif
            break;
#endif  // End of #if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

        default:

            return _TYPE_C_ALT_MODE_NOT_READY;

            break;
    }

    return _TYPE_C_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Update Port Controller Pin Assignment & Multi Function Configuration
// Input Value  : ucInputPort --> Inputput
// Output Value : Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit UserCommonPortControllerUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // 1. Config Pin Assignment
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerConfig5400PinAssignment(_D0_INPUT_PORT, enumPinAssignmentCap) == _FAIL)
#else
            if(UserCommonPortControllerConfigUserPinAssignment(_D0_INPUT_PORT, enumPinAssignmentCap) == _FAIL)
#endif
            {
                DebugMessageSystem("8. Type-C Reconnect : Config Pin Assignment Fail. ", 0);

                return _FAIL;
            }

            // 2. Config Multi-Function Bit
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerConfig5400MultiFunction(_D0_INPUT_PORT, enumMultiFunc) == _FAIL)
#else
            if(UserCommonPortControllerConfigUserMultiFunction(_D0_INPUT_PORT, enumMultiFunc) == _FAIL)
#endif
            {
                DebugMessageSystem("8. Type-C Reconnect : Config Multi-Function Bit Fail", 0);

                return _FAIL;
            }

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // 1. Config Pin Assignment
#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerConfig5400PinAssignment(_D1_INPUT_PORT, enumPinAssignmentCap) == _FAIL)
#else
            if(UserCommonPortControllerConfigUserPinAssignment(_D1_INPUT_PORT, enumPinAssignmentCap) == _FAIL)
#endif
            {
                DebugMessageSystem("8. Type-C Reconnect : Config Pin Assignment Fail. ", 0);

                return _FAIL;
            }

            // 2. Config Multi-Function Bit
#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerConfig5400MultiFunction(_D1_INPUT_PORT, enumMultiFunc) == _FAIL)
#else
            if(UserCommonPortControllerConfigUserMultiFunction(_D1_INPUT_PORT, enumMultiFunc) == _FAIL)
#endif
            {
                DebugMessageSystem("8. Type-C Reconnect : Config Multi-Function Bit Fail", 0);

                return _FAIL;
            }

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            // 1. Config Pin Assignment
#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerConfig5400PinAssignment(_D6_INPUT_PORT, enumPinAssignmentCap) == _FAIL)
#else
            if(UserCommonPortControllerConfigUserPinAssignment(_D6_INPUT_PORT, enumPinAssignmentCap) == _FAIL)
#endif
            {
                DebugMessageSystem("8. Type-C Reconnect : Config Pin Assignment Fail. ", 0);

                return _FAIL;
            }

            // 2. Config Multi-Function Bit
#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerConfig5400MultiFunction(_D6_INPUT_PORT, enumMultiFunc) == _FAIL)
#else
            if(UserCommonPortControllerConfigUserMultiFunction(_D6_INPUT_PORT, enumMultiFunc) == _FAIL)
#endif
            {
                DebugMessageSystem("8. Type-C Reconnect : Config Multi-Function Bit Fail", 0);

                return _FAIL;
            }

            break;
#endif

        default:

            DebugMessageSystem("8. Type-C Reconnect : Update Config with Invalid Input Port", ucInputPort);

            return _FAIL;

            break;
    }

    return _SUCCESS;
}

#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Set D0 I2C Detection Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSetD0I2CDetection(void)
{
    SET_D0_DP_TYPE_C_DETECT_CC_ATTACH();
    SET_D0_DP_TYPE_C_DETECT_ALT_MODE();
}

//--------------------------------------------------
// Description  : Disable I2C Detection and Restart Later
// Input Value  : usTime --> Time counter
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerRestartD0I2CDetection(WORD usTime)
{
    CLR_D0_DP_TYPE_C_DETECT_CC_ATTACH();
    CLR_D0_DP_TYPE_C_DETECT_ALT_MODE();

    ScalerTimerReactiveTimerEvent(usTime, _SYSTEM_TIMER_EVENT_D0_TYPE_C_CABLE_DETECT);
}
#endif

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Set D1 I2C Detection Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSetD1I2CDetection(void)
{
    SET_D1_DP_TYPE_C_DETECT_CC_ATTACH();
    SET_D1_DP_TYPE_C_DETECT_ALT_MODE();
}

//--------------------------------------------------
// Description  : Disable I2C Detection and Restart Later
// Input Value  : usTime --> Time counter
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerRestartD1I2CDetection(WORD usTime)
{
    CLR_D1_DP_TYPE_C_DETECT_CC_ATTACH();
    CLR_D1_DP_TYPE_C_DETECT_ALT_MODE();

    ScalerTimerReactiveTimerEvent(usTime, _SYSTEM_TIMER_EVENT_D1_TYPE_C_CABLE_DETECT);
}
#endif

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Set D0 I2C Detection Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSetD6I2CDetection(void)
{
    SET_D6_DP_TYPE_C_DETECT_CC_ATTACH();
    SET_D6_DP_TYPE_C_DETECT_ALT_MODE();
}

//--------------------------------------------------
// Description  : Disable I2C Detection and Restart Later
// Input Value  : usTime --> Time counter
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerRestartD6I2CDetection(WORD usTime)
{
    CLR_D6_DP_TYPE_C_DETECT_CC_ATTACH();
    CLR_D6_DP_TYPE_C_DETECT_ALT_MODE();

    ScalerTimerReactiveTimerEvent(usTime, _SYSTEM_TIMER_EVENT_D6_TYPE_C_CABLE_DETECT);
}
#endif

//--------------------------------------------------
// Description  : Pin assignment mapping
// Input Value  : ucInputPort     --> Input Port
//                ucPinAssignType --> Pin Assignment Type
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerPinMappingSetting(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) || (_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON))
        case _D0_INPUT_PORT:
        case _D6_INPUT_PORT:
            ScalerDpRx0SetDpLaneMapping(enumPinAssignment, enumOrientation);
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            ScalerDpRx1SetDpLaneMapping(enumPinAssignment, enumOrientation);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Power Off Flag to set Capability Change Flag
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
EnumTypeCPortCtrlReconnectStatus UserCommonPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            return _TYPE_C_PORT_CTRL_RECONNECT;

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            return UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(_POWER_ACTION_OFF_TO_NORMAL);
#else
            return _TYPE_C_PORT_CTRL_RECONNECT;
#endif  // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)

            break;

        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_FAKE_PS_TO_NORMAL:

#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            return UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(_POWER_ACTION_PS_TO_NORMAL);
#else
            return _TYPE_C_PORT_CTRL_RECONNECT;
#endif  // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)

            break;

        case _POWER_ACTION_OFF_TO_FAKE_OFF:

#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            return _TYPE_C_PORT_CTRL_NO_RECONNECT;
#else
            return _TYPE_C_PORT_CTRL_RECONNECT;
#endif  // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)

            break;

        default:

            return _TYPE_C_PORT_CTRL_RECONNECT;

            break;
    }

    return _TYPE_C_PORT_CTRL_RECONNECT;
}
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
