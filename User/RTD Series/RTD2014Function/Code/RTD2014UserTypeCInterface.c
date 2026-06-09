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
// ID Code      : RTD2014UserTypeCInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_TYPECINTERFACE__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Usb Hub Polling Par
//--------------------------------------------------
#define _USB_D0_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D1_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D2_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D6_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_DX_HUB_POLLING_DEVICE_STEP         500 // Unit: ms

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort);

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
bit UserInterfaceTypeCPDO(BYTE ucInputPort);
#endif

EnumTypeCPinCfgCapType UserInterfaceTypeCGetPinConfigType(BYTE ucInputPort, EnumTypeCU3ModeType enumU3ModeSel);

#if(_DP_USB_HUB_SUPPORT == _ON)
bit UserInterfaceTypeCUSBSupport(BYTE ucInputPort);
bit UserInterfaceTypeCGetUSBSupportStatus(BYTE ucInputPort);
void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort, BYTE ucUsbHubInfo);
WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort);
bit UserInterfaceTypeCUsbHubU3InfoDectectUserFlow(BYTE ucInputPort);
bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
BYTE UserInterfaceTypeCUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort);
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort);
EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype);
#endif // End of #if(_USB_HUB_USERDECITION_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get OSD Type-C U3 Mode Selection
// Input Value  : ucInputPort --> Input Port
// Output Value : Return Type-C U3 Mode Selection
//--------------------------------------------------
EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort)
{
    EnumTypeCU3ModeType enumTypeCMode = _TYPE_C_U3_OFF;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumTypeCMode = GET_OSD_D0_TYPEC_U3_MODE();
            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumTypeCMode = GET_OSD_D1_TYPEC_U3_MODE();
            break;
#endif

#if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumTypeCMode = GET_OSD_D2_TYPEC_U3_MODE();
            break;
#endif


#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:
            enumTypeCMode = GET_OSD_D6_TYPEC_U3_MODE();
            break;
#endif
        default:
            break;
    }

    return enumTypeCMode;
}

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : 5400 PD current & voltage calculate
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCPDO(BYTE ucInputPort)
{
    WORD usTemp = 0;

    if(SysTypeCGetAltModeReady(ucInputPort) == _TRUE)
    {
        if(UserCommonPortControllerGetPDOStatus(ucInputPort) == _FAIL)
        {
            return _FAIL;
        }
    }
    else
    {
        return _FALSE;
    }

    // All Filed Element of g_unSMBusRdDataPool.stRdGetPDOStatus can be used here
    // For example:
    /*
    g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte0
    usTemp = (g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte0 + ((g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte1 & 0x03) << 8)) * 10;
    SET_OSDINFO_TYPEC_CURRENT(usTemp);

    usTemp = ((((g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte1 & 0xFC) >> 2)+ ((g_unSMBusRdDataPool.stRdGetPDOStatus.ucByte2 & 0xFF) << 6)) * 50);
    SET_OSDINFO_TYPEC_VOLTAGE(usTemp);
    */

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : User Decide Sink Pin Config Type
// Input Value  : ucInputPort --> Input Port
// Output Value : Pin Config Capability Type
//--------------------------------------------------
EnumTypeCPinCfgCapType UserInterfaceTypeCGetPinConfigType(BYTE ucInputPort, EnumTypeCU3ModeType enumU3ModeSel)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            switch(enumU3ModeSel)
            {
                case _TYPE_C_U3_ON:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CDE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;

                default:
                case _TYPE_C_U3_OFF:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
            }
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            switch(enumU3ModeSel)
            {
                case _TYPE_C_U3_ON:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CDE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;

                default:
                case _TYPE_C_U3_OFF:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
            }
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            switch(enumU3ModeSel)
            {
                case _TYPE_C_U3_ON:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CDE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;

                default:
                case _TYPE_C_U3_OFF:

                    // Decide Sink Pin Config Type Capability is _TYPE_C_PIN_ASSIGNMENT_CAP_CE
                    return _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
            }
#endif

        default:
            break;
    }
}

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Decide Wether Support USB Hub
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCUSBSupport(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_OSD_D0_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            if(GET_OSD_D1_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

#if(_D2_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_OSD_D2_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            if(GET_OSD_D6_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceTypeCGetUSBSupportStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_USB_HUB_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_OSD_D0_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _ON;
            }

            break;
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            if(GET_OSD_D1_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _ON;
            }

            break;

#endif

#if(_D2_DP_USB_HUB_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_OSD_D2_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _ON;
            }

            break;

#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
        case _D6_INPUT_PORT:
            if(GET_OSD_D6_TYPEC_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _ON;
            }

            break;

#endif

        default:
            break;
    }

    return _OFF;
}

//--------------------------------------------------
// Description  : User decided how many lanes to switch
// Input Value  : ucInputPort --> Input Port
//                ucUsbHubInfo:
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort, BYTE ucUsbHubInfo)
{
    ucUsbHubInfo = ucUsbHubInfo;

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Can Use "ucUsbHubInfo" Info to Create Draw Notice U3 Device Menu Event
            break;

        case _D1_INPUT_PORT:
            // Here: User Can Use "ucUsbHubInfo" Info to Create Draw Notice U3 Device Menu Event
            break;

        case _D6_INPUT_PORT:
            // Here: User Can Use "ucUsbHubInfo" Info to Create Draw Notice U3 Device Menu Event
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : User Set Usb Hub Polling SS Device Step
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Polling Step Par.
//--------------------------------------------------
WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
        return _USB_D0_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
        return _USB_D1_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
        return _USB_D2_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D6_INPUT_PORT)
    {
        return _USB_D6_HUB_POLLING_DEVICE_STEP;
    }
    else
    {
        return _USB_DX_HUB_POLLING_DEVICE_STEP;
    }
}

//--------------------------------------------------
// Description  : Usb Hub RTS5400 Series User Flow Support
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE: User Flow, _FALSE: Kernal Flow
//--------------------------------------------------
bit UserInterfaceTypeCUsbHubU3InfoDectectUserFlow(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_USB_HUB_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return _FALSE;
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return _FALSE;
#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            return _FALSE;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Usb Hub into SS Mode
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn)
{
    ucInputPort = ucInputPort;
    bEn = bEn;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect Usb Hub SS Device Plug In
// Input Value  : ucInputPort --> Input Port
// Output Value : Return SS Device Info.
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
//--------------------------------------------------
BYTE UserInterfaceTypeCUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return 0x00;
}
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Port Controller Reconnect
// Input Value  : ucInputPort --> Input Port
// Output Value : return _TRUE / __FALSE
//--------------------------------------------------
bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Port Controller Config Type
// Input Value  : ucInputPort --> Input Port
//                penumPinCfgtype --> Pin Assignment Type
// Output Value : return failure type
//--------------------------------------------------
EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype)
{
    ucInputPort = ucInputPort; // Avoiding Warning
    *penumPinCfgtype = _TYPE_C_PIN_ASSIGNMENT_C;

    // Example:
    /*
        if(UserGetPortcontrollerConfigPinAssignmentTypeFunc(penumPinCfgtype) == _TRUE)
        {
            return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_SUCCESS;
        }
        else
        {
            return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL;
        }
    */

    return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL;
}
#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
