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
// ID Code      : ScalerCommonFwUpdate.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_FW_UPDATE__

#include "ScalerCommonFunctionInclude.h"

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
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
volatile  BYTE g_pucFwUpdateRxBuf[_FW_UPDATE_BUF_LEN];
volatile WORD g_usFwUpdateDdcciCountEXINT;
volatile StructFwUpdateScalerInfo g_stFwUpdateScalerInfo =
{
    _FALSE, _FALSE, _DEBUG_MODE, _INVALID_MODE
};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerFwUpdateSwitchState(EnumDDCCIDebugMode enumDdcciMode, BYTE ucOpCode);
void ScalerFwUpdateSendReply(BYTE ucResult);
void ScalerFwUpdateSendData(BYTE ucLen, BYTE *pucData);
void ScalerFwUpdateInitRxBuf(void);
void ScalerFwUpdateExit(void);
void ScalerFwUpdateIntProc_EXINT1(void);
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)
void ScalerFwUpdateDdcci0SwitchState(void);
void ScalerFwUpdateDdcci0IntProc_EXINT1(void);
void ScalerFwUpdateDdcci0SendReply(BYTE ucResult);
void ScalerFwUpdateDdcci0SendData(BYTE ucLen, BYTE *pucData);
bit ScalerFwUpdateGetState(void);
#endif
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
void ScalerFwUpdateDdcci1SwitchState(void);
void ScalerFwUpdateDdcci1IntProc_EXINT1(void);
void ScalerFwUpdateDdcci1SendReply(BYTE ucResult);
void ScalerFwUpdateDdcci1SendData(BYTE ucLen, BYTE *pucData);
#endif
BYTE ScalerFwUpdateGetState_EXINT1(void);

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
bit ScalerFwUpdateForegroundGetStatus(void);
#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)
bit ScalerFwUpdateDeRsaCalculateforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usRsaMode, WORD usSigSize, WORD usRRModNSize, WORD usNKeySize, WORD usEKeySize, WORD usNPivSize);
void ScalerFwUpdateReadoutRsaforSign(BYTE *pucArray, WORD usRsaSize);
bit ScalerFwUpdateSha256CalculateforSign(BYTE *pucInputArray, BYTE ucCalCount);
void ScalerFwUpdateDownLoadCalculateKeyforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usLength, BYTE *pucReadArray, EnumSignKeyInfo enumRSAType);
void ScalerFwUpdateReadoutHashforSign(BYTE *pucArray);
void ScalerFwUpdateReleaseRsaforSign(void);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : enumIp, enumStatus, ultimeout
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateSwitchState(EnumDDCCIDebugMode enumDdcciMode, BYTE ucOpCode)
{
    SET_FW_UPDATE_STATE_BACKUPDDCCIMODE(enumDdcciMode);
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)
    ScalerFwUpdateDdcci0SwitchState();
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
    ScalerFwUpdateDdcci1SwitchState();
#endif

    SET_FW_UPDATE_STATUS();
    if(ucOpCode == _FW_UPDATE_BACKGROUND_SUB_OP_CODE)
    {
        SET_FW_UPDATE_MODE(_BACKGROUND_MODE);
    }
    else if(ucOpCode == _FW_UPDATE_FOREGROUND_SUB_OP_CODE)
    {
        SET_FW_UPDATE_MODE(_FOREGROUND_MODE);
    }
    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    if(ucOpCode == _FW_UPDATE_FOREGROUND_SUB_OP_CODE)
    {
        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
    }
#endif
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateSendReply(BYTE ucResult)
{
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)
    ScalerFwUpdateDdcci0SendReply(ucResult);
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
    ScalerFwUpdateDdcci1SendReply(ucResult);
#endif
    ScalerFwUpdateInitRxBuf();
    CLR_FW_UPDATE_RUN_COMMAND();
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateSendData(BYTE ucLen, BYTE *pucData)
{
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)
    ScalerFwUpdateDdcci0SendData(ucLen, pucData);
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
    ScalerFwUpdateDdcci1SendData(ucLen, pucData);
#endif
    ScalerFwUpdateInitRxBuf();
    CLR_FW_UPDATE_RUN_COMMAND();
}

//---------------------------------------------------------
// Description  : Background Fw Update Init Rx Buffer
// Input Value  : ucFwBank, *pucArry
// Output Value : None
//---------------------------------------------------------
void ScalerFwUpdateInitRxBuf(void)
{
    // Clear buffer for new message
    memset(g_pucFwUpdateRxBuf, 0, _FW_UPDATE_BUF_LEN);
}

//--------------------------------------------------
// Description  : Exit Fw Update
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateExit(void)
{
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
    // Disable DDCCI 1
    MCU_FE87_IIC_1_SET_SLAVE = 0x3D;
    MCU_FE86_IIC_1_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
#endif

    ScalerMcuDdcciSwitchPort(GET_FW_UPDATE_STATE_BACKUPDDCCIMODE(), _D0_INPUT_PORT);
    ScalerFwUpdateInitRxBuf();
    CLR_FW_UPDATE_STATUS();
    SET_FW_UPDATE_MODE(_INVALID_MODE);
}

//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateIntProc_EXINT1(void) using 2
{
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)
    ScalerFwUpdateDdcci0IntProc_EXINT1();
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
    ScalerFwUpdateDdcci1IntProc_EXINT1();
#endif
}
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci0SwitchState(void)
{
    // Change Slave Address and Interrupt setting
    MCU_FF28_IIC_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    MCU_FF23_IIC_SET_SLAVE = 0x3A;

    // Clear IRQ FLag
    MCU_FF27_IIC_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FF25_IIC_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FF26_IIC_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
    // Reset IIC Buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;
}

//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDdcci0IntProc_EXINT1(void) using 2
{
    BYTE ucTempBuf = 0;
    BYTE ucIndex = 0;
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
    // Clear status
    if(GET_FW_UPDATE_RUN_COMMAND() == _TRUE)
    {
        // Clear sub,data_in, stop    Flag
        MCU_FF27_IIC_STATUS &= ~(_BIT4 | _BIT1 | _BIT0);
        if((MCU_FF27_IIC_STATUS & _BIT2) == _BIT2)
        {
            ucTempBuf = MCU_FF25_IIC_DATA_IN;
        }

        return;
    }

    ucTempBuf = MCU_FF27_IIC_STATUS;

    if((ucTempBuf & _BIT1) == _BIT1)
    {
        // Clear SUB_I Flag
        MCU_FF27_IIC_STATUS = ~_BIT1;
        g_usFwUpdateDdcciCountEXINT = 0;
        g_pucFwUpdateRxBuf[0] = MCU_FF24_IIC_SUB_IN;
        // Host write Enable
        MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
    }

    if((ucTempBuf & _BIT2) == _BIT2)
    {
        while((MCU_FF29_IIC_STATUS2 & _BIT1) == 0)
        {
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
            if(g_pucFwUpdateRxBuf[0] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT) < (_FW_UPDATE_FOREGROUND_RESET_MAX_ISP_LEN))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                pucIspXram[g_usFwUpdateDdcciCountEXINT - 1] = MCU_FF25_IIC_DATA_IN;
            }
            else
#endif
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT + 1) < sizeof(g_pucFwUpdateRxBuf))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                g_pucFwUpdateRxBuf[g_usFwUpdateDdcciCountEXINT] = MCU_FF25_IIC_DATA_IN;
            }
        }
        // Clear D_IN_I Flag
        MCU_FF27_IIC_STATUS = ~_BIT2;
    }

    if((ucTempBuf & _BIT4) == _BIT4)
    {
        MCU_FF27_IIC_STATUS = ~_BIT4;

        if(g_usFwUpdateDdcciCountEXINT > 0)
        {
            SET_FW_UPDATE_RUN_COMMAND();

            g_usFwUpdateDdcciCountEXINT = 0;
            // Host Write Disable
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT5;
            // Reset IIC Data Buffer
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

            for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex = ucIndex + 1)
            {
                MCU_FF26_IIC_DATA_OUT = _FW_UPDATE_RESULT_BUSY;
            }
            // Disable mcu write
            MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;

            // Reset data buffer
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
        }
    }
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci0SendReply(BYTE ucResult)
{
    BYTE ucIndex = 0;

    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex++)
    {
        MCU_FF26_IIC_DATA_OUT = ucResult;
    }
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateDdcci0SendData(BYTE ucLen, BYTE *pucData)
{
    BYTE ucIndex = 0;
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        MCU_FF26_IIC_DATA_OUT = pucData[ucIndex];
    }
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

//------------------------------------------------------------
// Description  : Get Current Background Fw Update State
// Input Value  : None
// Output Value : Bit State
//------------------------------------------------------------
bit ScalerFwUpdateGetState(void)
{
    return GET_FW_UPDATE_STATUS();
}

#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci1SwitchState(void)
{
    // Disable DDCCI 1
    MCU_FE87_IIC_1_SET_SLAVE = 0x3A;
    MCU_FE86_IIC_1_CH_SEL = MCU_FF22_IIC_CH_SEL;

    // Disable Hw DDCCI0 Auto-select
    CLR_DDCCI_AUTO_SWITCH()
    MCU_FF22_IIC_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    // Enable Hw DDCCI0 Auto-select
    SET_DDCCI_AUTO_SWITCH()

    // Change Slave Address and Interrupt setting
    MCU_FE8C_IIC_1_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    // Clear IRQ FLag
    MCU_FE8B_IIC_1_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FE89_IIC_1_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FE8A_IIC_1_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FE8D_IIC_1_STATUS2 &= ~(_BIT5 | _BIT4);
    // Reset IIC Buffer
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FE8C_IIC_1_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;
}

//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDdcci1IntProc_EXINT1(void) using 2
{
    BYTE ucTempBuf = 0;
    BYTE ucIndex = 0;
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif

    MCU_FE8D_IIC_1_STATUS2 &= ~(_BIT4 | _BIT5);
    // Clear status
    if(GET_FW_UPDATE_RUN_COMMAND() == _TRUE)
    {
        // Clear sub,data_in, stop    Flag
        MCU_FE8B_IIC_1_STATUS &= ~(_BIT4 | _BIT1 | _BIT0);
        if((MCU_FE8B_IIC_1_STATUS & _BIT2) == _BIT2)
        {
            ucTempBuf = MCU_FE89_IIC_1_DATA_IN;
        }

        return;
    }

    ucTempBuf = MCU_FE8B_IIC_1_STATUS;

    if((ucTempBuf & _BIT1) == _BIT1)
    {
        // Clear SUB_I Flag
        MCU_FE8B_IIC_1_STATUS = ~_BIT1;
        g_usFwUpdateDdcciCountEXINT = 0;
        g_pucFwUpdateRxBuf[0] = MCU_FE88_IIC_1_SUB_IN;
        // Host write Enable
        MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
    }

    if((ucTempBuf & _BIT2) == _BIT2)
    {
        while((MCU_FE8D_IIC_1_STATUS2 & _BIT1) == 0)
        {
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
            if(g_pucFwUpdateRxBuf[0] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT) < (_FW_UPDATE_FOREGROUND_RESET_MAX_ISP_LEN))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                pucIspXram[g_usFwUpdateDdcciCountEXINT - 1] = MCU_FE89_IIC_1_DATA_IN;
            }
            else
#endif
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT + 1) < sizeof(g_pucFwUpdateRxBuf))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                g_pucFwUpdateRxBuf[g_usFwUpdateDdcciCountEXINT] = MCU_FE89_IIC_1_DATA_IN;
            }
        }
        // Clear D_IN_I Flag
        MCU_FE8B_IIC_1_STATUS = ~_BIT2;
    }

    if((ucTempBuf & _BIT4) == _BIT4)
    {
        MCU_FE8B_IIC_1_STATUS = ~_BIT4;
        if(g_usFwUpdateDdcciCountEXINT > 0)
        {
            SET_FW_UPDATE_RUN_COMMAND();

            g_usFwUpdateDdcciCountEXINT = 0;
            // Host Write Disable
            MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT5;
            // Reset IIC Data Buffer
            MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

            for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex = ucIndex + 1)
            {
                MCU_FE8A_IIC_1_DATA_OUT = _FW_UPDATE_RESULT_BUSY;
            }
            // Disable mcu write
            MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;

            // Reset data buffer
            MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;
        }
    }
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci1SendReply(BYTE ucResult)
{
    BYTE ucIndex = 0;

    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex++)
    {
        MCU_FE8A_IIC_1_DATA_OUT = ucResult;
    }
    MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateDdcci1SendData(BYTE ucLen, BYTE *pucData)
{
    BYTE ucIndex = 0;
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        MCU_FE8A_IIC_1_DATA_OUT = pucData[ucIndex];
    }
    MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
}
#endif

//------------------------------------------------------------
// Description  : Get Current Background Fw Update State
// Input Value  : None
// Output Value : Bit State
//------------------------------------------------------------
BYTE ScalerFwUpdateGetState_EXINT1(void) using 2
{
    return GET_FW_UPDATE_STATUS();
}

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
bit ScalerFwUpdateForegroundGetStatus(void)
{
    if((GET_FW_UPDATE_STATUS() == _TRUE) && (GET_FW_UPDATE_MODE() == _FOREGROUND_MODE))
    {
        return _TRUE;
    }
    return _FALSE;
}

#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)
//--------------------------------------------------
// Description  : For Signature, DeRsa Calc
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFwUpdateDeRsaCalculateforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usRsaMode, WORD usSigSize, WORD usRRModNSize, WORD usNKeySize, WORD usEKeySize, WORD usNPivSize)
{
    // Enable HDCP 2.2 RSA Module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT7 | _BIT5));

    // RSA Clock Select
    ScalerSetBit(P63_92_HDCP_DUMMY1, ~_BIT7, _BIT7);
    if(usRsaMode == _DIGITAL_SIGNATURE_RSA_3072)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    }
    else if(usRsaMode == _DIGITAL_SIGNATURE_RSA_2048)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT6);
    }
    else if(usRsaMode == _DIGITAL_SIGNATURE_RSA_1024)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);
    }
    else if(usRsaMode == _DIGITAL_SIGNATURE_RSA_512)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    // Load Signature to RSA Module as cipher text
    for(pData[0] = 0; pData[0] < (usSigSize / 8); pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, ((usSigSize / 8 - 1) - pData[0]));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignFile[pData[0] << 3], 8);
    }
    for(pData[0] = 0; pData[0] < (usRRModNSize / 8); pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load RRmodN
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + ((usRRModNSize / 8 - 1) - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignRrmodn[pData[0] << 3], 8);
    }

    for(pData[0] = 0; pData[0] < (usNKeySize / 8); pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + ((usNKeySize / 8 - 1) - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignNKey[(pData[0] << 3)], 8);
    }

    for(pData[0] = 0; pData[0] < (usEKeySize / 8); pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load E Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + ((usEKeySize / 8 - 1) - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignEKey[pData[0] << 3], 8);
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &pstHdcp2SignKeyInfoType->pucSignNpinv, usNPivSize);

    // Set RSA Write key done
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT0), 0x00);
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : For Signature, Readout RSA result
// Input Value  : None
// Output Value : *pucArray
//--------------------------------------------------
void ScalerFwUpdateReadoutRsaforSign(BYTE *pucArray, WORD usRsaSize)
{
    // Read Out RSA Message
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(pData[0] = 0; pData[0] < (usRsaSize / 8); pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, pData[0]);
            memcpy(&pucArray[((usRsaSize / 8 - 1) - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(pData[0] = 0; pData[0] < (usRsaSize / 8); pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 | pData[0]));
            memcpy(&pucArray[((usRsaSize / 8 - 1) - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
}

//--------------------------------------------------
// Description  : For Signature, Sha256 Calc
// Input Value  : *pucInputArray, ucCalCount
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFwUpdateSha256CalculateforSign(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Set 1, Then Set 0 for Reset SHA256 Module
    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT3 | _BIT0), _BIT3);

    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT3 | _BIT0), 0x00);

    // Write SHA256 Input Data, Total 512 bits
    for(pData[1] = 0; pData[1] < 16; pData[1]++)
    {
        ScalerSetByte(P63_31_HDCP_SHA_DATA1, pucInputArray[pData[1] * 4]);
        ScalerSetByte(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + pData[1] * 4]);
        ScalerSetByte(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + pData[1] * 4]);
        ScalerSetByte(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + pData[1] * 4]);

        // Inform HW SHA data Has been set first 32 bit
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    if(ucCalCount == 0)
    {
        // Set First Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Enable SHA256 Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT0), _BIT2);
    }
    else
    {
        // Disable First Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable SHA256 Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT0), _BIT2);
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------------------------------------------------------------------------------
// Description  : For Signature, Down Load RSA Key and Sign File
// Input Value  : pstHdcp2SignKeyInfoType, usLength, *pucReadArray, ucRSAType
// Output Value : None
//--------------------------------------------------------------------------------------------------------------------------
void ScalerFwUpdateDownLoadCalculateKeyforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usLength, BYTE *pucReadArray, EnumSignKeyInfo enumRSAType)
{
    switch(enumRSAType)
    {
        case _SIGN_FILE:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignFile, pucReadArray, usLength);
            break;

        case _SIGN_NKEY:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignNKey, pucReadArray, usLength);
            break;

        case _SIGN_RRMODN:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignRrmodn, pucReadArray, usLength);
            break;

        case _SIGN_NPINV:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignNpinv, pucReadArray, usLength);
            break;

        case _SIGN_EKEY:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignEKey, pucReadArray, usLength);
            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  : For Signature, Readout HASH result
// Input Value  : None
// Output Value : *pucArray
//--------------------------------------------------
void ScalerFwUpdateReadoutHashforSign(BYTE *pucArray)
{
    memcpy(pucArray, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
}

//--------------------------------------------------
// Description  : For Signature, Release RSA Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateReleaseRsaforSign(void)
{
    // release HDCP RSA
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT3 | _BIT0), _BIT3);
}


#endif // #if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)

#endif
#endif
