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
// ID Code      : UserCommonDdcciFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DDCCI_FUNCTION__

#include "UserCommonInclude.h"

#if(_DDCCI_CODE_REDUCTION == _OFF)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of DDCCI Capabilities Request
//--------------------------------------------------
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
// I2C Speed = 20k, DDCCI Buffer = _DDCCI_RXBUF_LENGTH
// (1/20K)*_DDCCI_RXBUF_LENGTH*8
#define _CLR_DDCCI_CMD_RECEIVE_NOT_FINISH_TIMEOUT       (((_DDCCI_RXBUF_LENGTH * 9) / 20) + 1)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _OFF)
#if(_VGA_PORT_EXIST == _ON)
BYTE code tCP_STRING_DSUB[] =
{
    _CAPABILITIES_STRING_VGA
};
#endif

#if(_DVI_PORT_EXIST == _ON)
BYTE code tCP_STRING_DVI[] =
{
    _CAPABILITIES_STRING_DVI
};
#endif

#if(_HDMI_PORT_EXIST == _ON)
BYTE code tCP_STRING_HDMI[] =
{
    _CAPABILITIES_STRING_HDMI
};
#endif

#if(_DP_PORT_EXIST == _ON)
BYTE code tCP_STRING_DP[] =
{
    _CAPABILITIES_STRING_DP
};
#endif
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonDdcciHandler(void);
void UserCommonDdcciInitTx(void);
void UserCommonDdcciInitRx(void);
BYTE UserCommonDdcciCalCheckSum(void);
void UserCommonDdcciSetVCPReplyValue(BYTE ucTypeOpcode, WORD usMax, WORD usPresent);
void UserCommonDdcciGetTimingReport(void);
void UserCommonDdcciGetCapabilitiesRequest(void);
void UserCommonDdcciGetCpStringData(BYTE *pucDest, EnumInputPortType enumPortType, WORD usStartIndex, WORD usLength);
WORD UserCommonDdcciGetCpStringSize(EnumInputPortType enumPortType);
void UserCommonDdcciGetFwInfoRequest(void);
bit UserCommonDdcciKernelHandler(void);
#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
void UserCommonDdcciSetSmbusBlockReadWrite(void);
#endif

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
void UserCommonDdcciFwCheck(BYTE *pucCmdArry);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User Common DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciHandler(void)
{
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
    if(GET_RUN_DDCCI_COMMAND() == _FAIL)
    {
        if(GET_RECEIVE_DDCCI_CMD_NOT_FINISH() == _SUCCESS)
        {
            // Polling User Ddcci Cmd Finished
            ScalerTimerActiveTimerEvent(_CLR_DDCCI_CMD_RECEIVE_NOT_FINISH_TIMEOUT, _SYSTEM_TIMER_EVENT_CLR_DDCCI_RECEIVE_COMMAND_NOT_FINISH);
        }
        else
        {
            if(GET_DDCCI_AUTO_SWITCH() == _FALSE)
            {
                // Enable DDCCI Channel Auto Switch
                SET_DDCCI_AUTO_SWITCH();

                // Set Other DDC Enable
                ScalerMcuDdcciAutoSwitchInactiveChannel(_ENABLE);
            }
        }
    }
#endif
    if(UserCommonDdcciKernelHandler() == _TRUE)
    {
        return;
    }
    UserDdcciHandler();
}
//--------------------------------------------------
// Description  : Initial TX variables and Send Null-Message
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciInitTx(void)
{
    // Send Null-Message
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = UserCommonDdcciCalCheckSum();

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC() == _DDCCI_CMD_SRC_I2C)
#endif
    {
        ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    }
}

//--------------------------------------------------
// Description  : Initial RX variables
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciInitRx(void)
{
    // Clear buffer for new message
    memset(g_pucDdcciRxBuf, 0, _DDCCI_RXBUF_LENGTH);
}

//--------------------------------------------------
// Description  : Caculate checksum
// Input Value  : None
// Output Value : ucSum --> Checksum value
//--------------------------------------------------
BYTE UserCommonDdcciCalCheckSum(void)
{
    BYTE ucCount = 0;
    BYTE ucCheckLen = 0;
    BYTE ucSum = _DDCCI_VIRTUAL_HOST_ADDRESS;

    ucCheckLen = (g_pucDdcciTxBuf[_DDCCI_LENGTH] & 0x7F) + 2;

    for(ucCount = 0; ucCount < ucCheckLen; ucCount++)
    {
        ucSum = ucSum ^ g_pucDdcciTxBuf[ucCount];
    }

    return ucSum;
}

//--------------------------------------------------
// Description  : DDCCI VCP Feature Reply Max and Present Value
// Input Value  : ucOpcode --> OPCODE
//                  usMax --> Maximum Value
//                  usPresent --> Present Value
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciSetVCPReplyValue(BYTE ucTypeOpcode, WORD usMax, WORD usPresent)
{
    g_pucDdcciTxBuf[_DDCCI_TYPE_CODE] = ucTypeOpcode;
    g_pucDdcciTxBuf[_DDCCI_MAX_HIGH_BYTE] = HIBYTE(usMax);
    g_pucDdcciTxBuf[_DDCCI_MAX_LOW_BYTE] = LOBYTE(usMax);
    g_pucDdcciTxBuf[_DDCCI_PRESENT_HIGH_BYTE] = HIBYTE(usPresent);
    g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE] = LOBYTE(usPresent);
}

//--------------------------------------------------
// Description  : DDCCI Get and Reply Timing Report
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetTimingReport(void)
{
    BYTE ucPolarity = 0;

    ucPolarity = (GET_INPUT_TIMING_H_POLARITY() | (GET_INPUT_TIMING_V_POLARITY() << 1));

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_TIMING_MSG_COMMAND] = _DDCCI_CMD_REPLY_TIMING_MESSAGE;
    g_pucDdcciTxBuf[_DDCCI_TIMING_MSG_OPCODE] = _DDCCI_OPCODE_TIMING_MSG;
    g_pucDdcciTxBuf[_DDCCI_TIMING_STATUS] = 0x00;

    // H sync pol :Bit 1 = 1:positive H-sync polarity
    if((bit)(ucPolarity & _BIT0) == _TRUE)
    {
        g_pucDdcciTxBuf[_DDCCI_TIMING_STATUS] |= _BIT1;
    }

    // V sync pol :Bit 0 = 1:positive V-sync polarity
    if((bit)(ucPolarity & _BIT1) == _TRUE)
    {
        g_pucDdcciTxBuf[_DDCCI_TIMING_STATUS] |= _BIT0;
    }

    g_pucDdcciTxBuf[_DDCCI_TIMING_HFREQ_HBYTE] = HIBYTE(GET_INPUT_TIMING_HFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_HFREQ_LBYTE] = LOBYTE(GET_INPUT_TIMING_HFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_VFREQ_HBYTE] = HIBYTE(GET_INPUT_TIMING_VFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_VFREQ_LBYTE] = LOBYTE(GET_INPUT_TIMING_VFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_VFREQ_LBYTE + 1] = UserCommonDdcciCalCheckSum();

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC() == _DDCCI_CMD_SRC_I2C)
#endif
    {
        ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    }
}

//--------------------------------------------------
// Description  : DDCCI Capabilities Request & Reply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetCapabilitiesRequest(void)
{
    WORD usOffset = 0;
    BYTE ucSendLen = 0;
    EnumInputPortType enumPortType = _PORT_NONE;
    WORD usCreqLen = 0;

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC() == _DDCCI_CMD_SRC_MST)
    {
        enumPortType = GET_PORT_TYPE(SysSourceGetInputPortType(ScalerDpRxMstGetInputPort(ScalerDpRxMstGetCapablePort())));
    }
    else
#endif
    {
        enumPortType = GET_PORT_TYPE(SysSourceGetInputPortType(ScalerMcuDdcciGetInputPort()));
    }

    usCreqLen = UserCommonDdcciGetCpStringSize(enumPortType);

    usOffset = ((((WORD)g_pucDdcciRxBuf[_DDCCI_OFS_HIGH_BYTE]) << 8) & 0xFF00) | (g_pucDdcciRxBuf[_DDCCI_OFS_LOW_BYTE]);

    if(usOffset >= usCreqLen)
    {
        ucSendLen = 0;
    }
    else if(usCreqLen > (usOffset + ScalerMcuDdcciGetBufferSize() - 6))
    {
        ucSendLen = ScalerMcuDdcciGetBufferSize() - 6;
    }
    else
    {
        ucSendLen = usCreqLen - usOffset;
    }

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | (ucSendLen + 3);
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_CAPABILITIES_REQUEST_REPLY;
    g_pucDdcciTxBuf[_DDCCI_OFS_HIGH_BYTE] = g_pucDdcciRxBuf[_DDCCI_OFS_HIGH_BYTE];
    g_pucDdcciTxBuf[_DDCCI_OFS_LOW_BYTE] = g_pucDdcciRxBuf[_DDCCI_OFS_LOW_BYTE];

    UserCommonDdcciGetCpStringData(&g_pucDdcciTxBuf[_DDCCI_OFS_LOW_BYTE + 1], enumPortType, usOffset, ucSendLen);

    g_pucDdcciTxBuf[_DDCCI_OFS_LOW_BYTE + 1 + ucSendLen] = UserCommonDdcciCalCheckSum();

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC() == _DDCCI_CMD_SRC_I2C)
#endif
    {
        ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    }
}

//--------------------------------------------------
// Description  : Get capability string data
// Input Value  : pucDest -> destination
//                enumPortType -> port type
//                usStartIndex -> data offset
//                usLength -> data length
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetCpStringData(BYTE *pucDest, EnumInputPortType enumPortType, WORD usStartIndex, WORD usLength)
{
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)

    UserInterfaceDdcciGetCpStringData(pucDest, enumPortType, usStartIndex, usLength);

#else

    switch(enumPortType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _PORT_VGA:
            memcpy(pucDest, &tCP_STRING_DSUB[usStartIndex], usLength);
            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _PORT_DVI:
        case _PORT_DUAL_DVI:
            memcpy(pucDest, &tCP_STRING_DVI[usStartIndex], usLength);
            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _PORT_HDMI:
        case _PORT_MHL:
        case _PORT_HDMI20:
            memcpy(pucDest, &tCP_STRING_HDMI[usStartIndex], usLength);
            break;
#endif

#if(_DP_PORT_EXIST == _ON)
        case _PORT_DP:
            memcpy(pucDest, &tCP_STRING_DP[usStartIndex], usLength);
            break;
#endif

        default:
            break;
    }

#endif
}

//--------------------------------------------------
// Description  : Get capability string size
// Input Value  : enumPortType -> port type
// Output Value : size
//--------------------------------------------------
WORD UserCommonDdcciGetCpStringSize(EnumInputPortType enumPortType)
{
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)

    return UserInterfaceDdcciGetCpStringSize(enumPortType);

#else

    switch(enumPortType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _PORT_VGA:
            return (sizeof(tCP_STRING_DSUB) - 1);
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _PORT_DVI:
        case _PORT_DUAL_DVI:
            return (sizeof(tCP_STRING_DVI) - 1);
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _PORT_HDMI:
        case _PORT_MHL:
        case _PORT_HDMI20:
            return (sizeof(tCP_STRING_HDMI) - 1);
#endif

#if(_DP_PORT_EXIST == _ON)
        case _PORT_DP:
            return (sizeof(tCP_STRING_DP) - 1);
#endif

        default:
            return 0;
    }

#endif
}

//--------------------------------------------------
// Description  : Get Fw Info Requeset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetFwInfoRequest(void)
{
    BYTE ucSendLen = 0;
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_FW_INFO_REQUEST;

    switch(g_pucDdcciRxBuf[_DDCCI_SINK_OPCODE])
    {
#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
        case _DDCCI_OPCODE_GET_CURRENT_FW_VER_REQUEST:
            ucSendLen = 3;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLen;
            ScalerFwInfoGetCurrentVersion(&g_pucDdcciTxBuf[3]);
            g_pucDdcciTxBuf[5] = UserCommonDdcciCalCheckSum();
            break;
        case _DDCCI_OPCODE_GET_FW_VER_LOCATE_REQUEST:
            ucSendLen = 6;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLen;
            ScalerFwInfoGetFwVersionAddress(&g_pucDdcciTxBuf[3]);
            g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();
            break;
#endif

        case _DDCCI_OPCODE_GET_DUAL_BANK_INFO_REQUEST:
            ucSendLen = 11;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLen;
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
            UserCommonDualBankUserGetFwInfo(&g_pucDdcciTxBuf[3]);
#else
            // Byte Count
            g_pucDdcciTxBuf[3] = 9;

            // Dual bank Support
            g_pucDdcciTxBuf[4] = _DUAL_BANK_SUPPORT;

            // Dual bank Type
            g_pucDdcciTxBuf[5] = 0xFF;

            // Active User(1)
            g_pucDdcciTxBuf[6] = 0xFF;

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
            ScalerFwInfoGetCurrentVersion(&g_pucDdcciTxBuf[7]);
            memset(&g_pucDdcciTxBuf[9], 0xFFU, 4);
#else
            // User1 Version(2) + User2 Version(2) + Reserved(2)
            memset(&g_pucDdcciTxBuf[7], 0xFFU, 6);
#endif

#endif
            g_pucDdcciTxBuf[13] = UserCommonDdcciCalCheckSum();
            break;

        default:
            UserCommonDdcciInitTx();
            break;
    }
#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
    g_stSmbusBlockRWCmd.ucDataLen = ucSendLen + 3;
#endif
    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
}
//--------------------------------------------------
// Description  : RTK DDCCI  Handler for dual bank
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonDdcciKernelHandler(void)
{
    BYTE ucOpCode = 0;

    if(GET_OSD_DDCCI_STATUS() == _ON)
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
        {
            if((g_pucDdcciRxBuf[_DDCCI_SOURCE] == _DDCCI_SRC_RTK_ADDRESS))
            {
                if(g_pucDdcciRxBuf[_DDCCI_COMMAND] == _DDCCI_RTK_CMD_TYPE)
                {
                    ucOpCode = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE];
                }
                // compatible  For Old Tool (0x6E, 0x51, 0xAA);
                // New Tool 0x6E, 0x71, 0xAA
                else if(g_pucDdcciRxBuf[_DDCCI_COMMAND] == _DDCCI_CMD_SWITCH_DEBUG_SALVE_REQUEST)
                {
                    ucOpCode = g_pucDdcciRxBuf[_DDCCI_COMMAND];
                }
                else
                {
                    return _FALSE;
                }
                switch(ucOpCode)
                {
                    case _DDCCI_CMD_GET_FW_INFO_REQUEST:
                        UserCommonDdcciGetFwInfoRequest();
                        break;
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
                    case _DDCCI_CMD_SWITCH_DEBUG_SALVE_REQUEST:
                        ScalerDebugSetDdcciSwitchState();
                        // Switch DDCCI to Debug Mode, No Matter Which Port as Auto-Switch
                        ScalerMcuDdcciSwitchPort(_DEBUG_MODE, _A0_INPUT_PORT);
                        break;
#endif

#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
                    case _DDCCI_CMD_SET_SMBUS_BLOCK_REQUEST:
                        UserCommonDdcciSetSmbusBlockReadWrite();
                        break;
#endif
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
                    case _SCALER_FW_UPDATE_CMD:
                        ScalerFwUpdateSwitchState(_DDCCI_MODE, g_pucDdcciRxBuf[4]);
                        break;
#endif
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
                    case _SCALER_FW_CHECK_CMD:
                        UserCommonDdcciFwCheck(&g_pucDdcciRxBuf[_DDCCI_SINK_OPCODE]);
                        break;
#endif

                    default:
                        UserCommonDdcciInitTx();
                        break;
                }

#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
                if(GET_SMBUS_BLOCK_RW_STATUS() == _TRUE)
                {
                    ScalerTimerReactiveTimerEvent(_SMBUS_BLOCK_READ_WRITE_EXIT_TIMER_COUNT, _SCALER_TIMER_EVENT_SMBUS_BLOCK_READ_WRITE);
                }
#endif
                UserCommonDdcciInitRx();
                SET_RUN_DDCCI_COMMAND(_FAIL);
                return _TRUE;
            }
        }
    }
    return _FALSE;
}
#endif  // #if(_DDCCI_CODE_REDUCTION == _OFF)

#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : set Smbus Block Read Write Requeset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciSetSmbusBlockReadWrite(void)
{
    BYTE ucSendLen = 0;

    if(g_pucDdcciRxBuf[_DDCCI_SINK_OPCODE] != 0)
    {
        SET_SMBUS_BLOCK_RW_STATUS(_TRUE);
    }

    g_stSmbusBlockRWCmd.ucDataLen = 5;
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_SET_SMBUS_BLOCK_REQUEST;
    ucSendLen = 2;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLen;
    g_pucDdcciTxBuf[3] = 0; // Success
    g_pucDdcciTxBuf[4] = UserCommonDdcciCalCheckSum();
    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

    if(g_pucDdcciRxBuf[_DDCCI_SINK_OPCODE] == 0)
    {
        SET_SMBUS_BLOCK_RW_STATUS(_FALSE);
    }
}
#endif

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FW check Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciFwCheck(BYTE *pucCmdArry)
{
    g_pucDdcciTxBuf[0] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _SCALER_FW_CHECK_CMD;

    switch(pucCmdArry[0])
    {
        case _SCALER_FW_CHECK_SUB_OP_GET_ADDR:
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x07;
            ScalerFwCheckGetProjectIDAddress(&g_pucDdcciTxBuf[3]);
            break;

        case _SCALER_FW_CHECK_SUB_OP_VERIFY:
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x03;
            g_pucDdcciTxBuf[3] = ScalerFwCheckProjectIDVerify(&pucCmdArry[1]);
            break;

        default:
            UserCommonDdcciInitTx();
            break;
    }
    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
}
#endif


