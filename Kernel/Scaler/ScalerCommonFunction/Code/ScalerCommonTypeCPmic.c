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
// ID Code      : ScalerCommonTypeCPmic.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_TYPE_C_PMIC__

#include "ScalerFunctionInclude.h"

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#warning "NOTE: Type-C Peak_Current OCP is NOT protect! Please make sure PDO_Peak_Current is set to '_PD_PEAK_CUR_NONE', otherwise User_OCP protection must be support!"
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of TYPE C Hardware IIC
//--------------------------------------------------
#define _TYPE_C_HW_IIC_BUFFER_SIZE          24
#define _TYPE_C_HW_IIC_READ_SIZE            _TYPE_C_HW_IIC_BUFFER_SIZE
#define _TYPE_C_HW_IIC_WRITE_SIZE           (_TYPE_C_HW_IIC_BUFFER_SIZE - 1) // Slave_Addr + 23-Data = 24-Buffer

#if(_TYPE_C_PMIC_HW_IIC_SPEED == _HW_IIC_LOW_SPEED_100K)
#define _TYPE_C_HW_IIC_SLPC_14318K          0x26 // 38
#define _TYPE_C_HW_IIC_SHPC_14318K          0x22 // 34
#define _TYPE_C_HW_IIC_SLPC_28000K          0x2F // 47
#define _TYPE_C_HW_IIC_SHPC_28000K          0x2F // 47
#define _TYPE_C_HW_IIC_STA_SUGPIO_C         0x36 // 54
#define _TYPE_C_HW_IIC_TOR                  0x47 // 71
#else
#define _TYPE_C_HW_IIC_SLPC_14318K          0x0C // 12
#define _TYPE_C_HW_IIC_SHPC_14318K          0x04 // 4
#define _TYPE_C_HW_IIC_SLPC_28000K          0x0E // 14
#define _TYPE_C_HW_IIC_SHPC_28000K          0x06 // 6
#define _TYPE_C_HW_IIC_STA_SUGPIO_C         0x09 // 9
#define _TYPE_C_HW_IIC_TOR                  0x23 // 35
#endif

#define _TYPE_C_HW_IIC_FTPC                 0x03 // 3
#define _TYPE_C_HW_IIC_FD10_14318K          0x01 // 1
#define _TYPE_C_HW_IIC_FD10_28000K          0x02 // 2

//--------------------------------------------------
// Definitions of PMIC FUNCTION
//--------------------------------------------------
#define _TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD   295    // unit: 0.01V
#define _TYPE_C_ADC_MAX_CURRENT             800UL  // unit: 0.01A
#define _TYPE_C_ADC_MAX_VOLTAGE             2400UL // unit: 0.01V
#define _TYPE_C_PMIC_SHORT_VOLTAGE          30UL   // unit: 0.1V

//--------------------------------------------------
// Definitions of PMIC Protection Process Method
//--------------------------------------------------
#define _TYPE_C_PMIC_ERROR_RECOVERY         0
#define _TYPE_C_PMIC_HARD_RESET             1
#define _TYPE_C_PMIC_PROTECTION_METHOD      _TYPE_C_PMIC_HARD_RESET

//--------------------------------------------------
// Definitions of PMIC Minimum Current
//--------------------------------------------------
#define _TYPE_C_PMIC_MIN_CURRENT            85     // unit: 10mA
#define _TYPE_C_PMIC_MIN_PPS_CURRENT        60     // unit: 10mA

//--------------------------------------------------
// Definitions of PMIC Voltage Compesation
//--------------------------------------------------
#define _VOLTAGE_COMPESATION_CURRENT_UNIT   50     // unit: 10mA, R_comp = 0.1V / _VOLTAGE_COMPESATION_CURRENT_UNIT

//--------------------------------------------------
// Definitions of PMIC FW OCP Polling Function
//--------------------------------------------------
#define _TYPE_C_PMIC_HW_OCP_MAX             (_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE + 66)    // unit: %, should multiply with PMIC setting current to get the real OCP value

//--------------------------------------------------
// Definitions of PMIC Test FUNCTION
//--------------------------------------------------
#define _TYPE_C_PMIC_FORCE_OUTPUT           _OFF
#define _TYPE_C_PMIC_FORCE_VOLTAGE          1200   // unit: 10mV
#define _TYPE_C_PMIC_FORCE_CURRENT          100    // unit: 10mA

#if(_TYPE_C_PMIC_FORCE_OUTPUT == _ON)
#warning "Pmic would force output, typec port don't connect anything."
#endif

//--------------------------------------------------
// Macros of PMIC IIC Set Srart
//--------------------------------------------------
#define GET_PMIC_IIC_SET_START()            (g_stPMICControl.b1PmicIICSetStart)
#define SET_PMIC_IIC_SET_START()            (g_stPMICControl.b1PmicIICSetStart = _TRUE)
#define CLR_PMIC_IIC_SET_START()            (g_stPMICControl.b1PmicIICSetStart = _FALSE)

//--------------------------------------------------
// Macros of PMIC IIC Status
//--------------------------------------------------
#define GET_PMIC_IIC_IN_MAIN_LOOP()         (g_stPMICControl.b1PmicIICMainLoop)
#define SET_PMIC_IIC_IN_MAIN_LOOP()         (g_stPMICControl.b1PmicIICMainLoop = _TRUE)
#define CLR_PMIC_IIC_IN_MAIN_LOOP()         (g_stPMICControl.b1PmicIICMainLoop = _FALSE)
#define GET_PMIC_IIC_IN_EXINT0_LOOP()       (g_stPMICControl.b1PmicIICExint0Loop)
#define SET_PMIC_IIC_IN_EXINT0_LOOP()       (g_stPMICControl.b1PmicIICExint0Loop = _TRUE)
#define CLR_PMIC_IIC_IN_EXINT0_LOOP()       (g_stPMICControl.b1PmicIICExint0Loop = _FALSE)
#define GET_PMIC_IIC_IN_WDINT_LOOP()        (g_stPMICControl.b1PmicIICWdintLoop)
#define SET_PMIC_IIC_IN_WDINT_LOOP()        (g_stPMICControl.b1PmicIICWdintLoop = _TRUE)
#define CLR_PMIC_IIC_IN_WDINT_LOOP()        (g_stPMICControl.b1PmicIICWdintLoop = _FALSE)
#define GET_PMIC_IIC_EVER_IN_EXINT0_LOOP()  (g_stPMICControl.b1PmicIICExint0EverLoop)
#define SET_PMIC_IIC_EVER_IN_EXINT0_LOOP()  (g_stPMICControl.b1PmicIICExint0EverLoop = _TRUE)
#define CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP()  (g_stPMICControl.b1PmicIICExint0EverLoop = _FALSE)
#define GET_PMIC_IIC_EVER_IN_WDINT_LOOP()   (g_stPMICControl.b1PmicIICWdintEverLoop)
#define SET_PMIC_IIC_EVER_IN_WDINT_LOOP()   (g_stPMICControl.b1PmicIICWdintEverLoop = _TRUE)
#define CLR_PMIC_IIC_EVER_IN_WDINT_LOOP()   (g_stPMICControl.b1PmicIICWdintEverLoop = _FALSE)

//--------------------------------------------------
// Macros of PMIC OCP Check Flag
//--------------------------------------------------
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#define GET_PMIC_FW_OCP_PROTECT_LEVEL()     (g_ucOcpLevel)
#define SET_PMIC_FW_OCP_PROTECT_LEVEL(x)    (g_ucOcpLevel = (x))

#define GET_PMIC_FW_OCP_CURRENT(x)          (g_pusOcpCurrent[x])
#define SET_PMIC_FW_OCP_CURRENT(x, y)       (g_pusOcpCurrent[x] = (y))

#define GET_PMIC_FW_OCP_DELAY(x)            (g_pusOcpDelay[x])
#define SET_PMIC_FW_OCP_DELAY(x, y)         (g_pusOcpDelay[x] = (y))

#define GET_PMIC_PEAK_CURRENT_TYPE()        (g_enumTypeCPDPeakCurType)
#define SET_PMIC_PEAK_CURRENT_TYPE(x)       (g_enumTypeCPDPeakCurType = (x))

#define GET_PMIC_SHORT_VOLTAGE()            ((WORD)(g_usShortVoltage))
#define SET_PMIC_SHORT_VOLTAGE(x)           (g_usShortVoltage = ScalerTypeCPowerRx0CorrectionToRawData(x))

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
#define GET_PMIC_SAFETY_CURRENT_VALUE()     (g_usSafetyCurrent)
#define SET_PMIC_SAFETY_CURRENT_VALUE(x)    (g_usSafetyCurrent = (x))

#define GET_PMIC_SAFETY_PROTECT_TRIGGER()   (g_bSafetyProtectFlag)
#define SET_PMIC_SAFETY_PROTECT_TRIGGER()   (g_bSafetyProtectFlag = _TRUE)
#define CLR_PMIC_SAFETY_PROTECT_TRIGGER()   (g_bSafetyProtectFlag = _FALSE)
#endif

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#define GET_PMIC_OCP_PROTECT_TRIGGER()      (g_bPmicFwOcpProtectFlag)
#define SET_PMIC_OCP_PROTECT_TRIGGER()      (g_bPmicFwOcpProtectFlag = _TRUE)
#define CLR_PMIC_OCP_PROTECT_TRIGGER()      (g_bPmicFwOcpProtectFlag = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC Check Operating Status
//--------------------------------------------------
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#define GET_PMIC_GET_OMF_INFO_START()       (g_bPmicGetOmfInfoFlag)
#define SET_PMIC_GET_OMF_INFO_START()       (g_bPmicGetOmfInfoFlag = _TRUE)
#define CLR_PMIC_GET_OMF_INFO_START()       (g_bPmicGetOmfInfoFlag = _FALSE)

#define GET_PMIC_OMF_INFO()                 (g_enumPmicOMFInfo)
#define SET_PMIC_OMF_INFO(x)                (g_enumPmicOMFInfo = (x))
#endif

//--------------------------------------------------
// Macros of PMIC Check Flag
//--------------------------------------------------
#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
#define GET_PMIC_OUTPUT_ENABLE()            (g_bPmicOutputEnable)
#define SET_PMIC_OUTPUT_ENABLE()            (g_bPmicOutputEnable = _ON)
#define CLR_PMIC_OUTPUT_ENABLE()            (g_bPmicOutputEnable = _OFF)

#define GET_PMIC_BIDIR_MODE()               (g_bPmicBiDirMode)
#define SET_PMIC_BIDIR_SRC()                (g_bPmicBiDirMode = _PD_POWER_SRC)
#define SET_PMIC_BIDIR_SNK()                (g_bPmicBiDirMode = _PD_POWER_SNK)

#define GET_PMIC_PROTECT_VALID()            (g_bPmicProtectValidFlag)
#define SET_PMIC_PROTECT_VALID()            (g_bPmicProtectValidFlag = _TRUE)
#define CLR_PMIC_PROTECT_VALID()            (g_bPmicProtectValidFlag = _FALSE)

#define GET_PMIC_PROTECT_TIMER_CHECK()      (g_bPmicProtectTimerCheckFlag)
#define SET_PMIC_PROTECT_TIMER_CHECK()      (g_bPmicProtectTimerCheckFlag = _TRUE)
#define CLR_PMIC_PROTECT_TIMER_CHECK()      (g_bPmicProtectTimerCheckFlag = _FALSE)

#define GET_PMIC_PROTECT_TIMER_START()      (g_bPmicProtectTimerStartFlag)
#define SET_PMIC_PROTECT_TIMER_START()      (g_bPmicProtectTimerStartFlag = _TRUE)
#define CLR_PMIC_PROTECT_TIMER_START()      (g_bPmicProtectTimerStartFlag = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC Output Mode Flag
//--------------------------------------------------
#define GET_PMIC_OUTPUT_MODE_STATUS()       (g_enumPmicOutputPdoType)
#define SET_PMIC_OUTPUT_MODE_STATUS(x)      (g_enumPmicOutputPdoType = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPmicControl g_stPMICControl;

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE)
BYTE g_ucOcpLevel;
WORD g_pusOcpCurrent[4];
WORD g_pusOcpDelay[4];
EnumPDPeakCurType g_enumTypeCPDPeakCurType;
WORD g_usShortVoltage;

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
WORD g_usSafetyCurrent;
bit g_bSafetyProtectFlag = _FALSE;
#endif

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
bit g_bPmicFwOcpProtectFlag = _FALSE;
#endif
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
bit g_bPmicGetOmfInfoFlag = _FALSE;
EnumTypeCPmicOperationMode g_enumPmicOMFInfo = _TYPE_C_PMIC_CV_MODE_OPERATION;
#endif

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
bit g_bPmicOutputEnable = _OFF;
bit g_bPmicBiDirMode = _PD_POWER_SNK;
bit g_bPmicProtectValidFlag = _FALSE;
bit g_bPmicProtectTimerCheckFlag = _FALSE;
bit g_bPmicProtectTimerStartFlag = _FALSE;
#endif

EnumPDPdoType g_enumPmicOutputPdoType = _PD_NONE_SETTING_PDO;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
void ScalerTypeCPmicHwIICInitial(void);
void ScalerTypeCPmicHwIICSetFreqDiv(EnumClkSel enumClock);
bit ScalerTypeCPmicHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
BYTE ScalerTypeCPmicHwIICRead_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
#endif
bit ScalerTypeCPmicHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicHwIICWrite_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicHwIICWrite_WDINT(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
bit ScalerTypeCPmicHwIICSetStartCheck(void);
BYTE ScalerTypeCPmicHwIICSetStartCheck_EXINT0(void);
BYTE ScalerTypeCPmicHwIICSetStartCheck_WDINT(void);

bit ScalerTypeCPmicIICRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
BYTE ScalerTypeCPmicIICRead_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#endif
bit ScalerTypeCPmicIICWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicIICWrite_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicIICWrite_WDINT(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
void ScalerTypeCPmicIICReset(void);
#endif

void ScalerTypeCPmicRx0Initial(void);
void ScalerTypeCPmicRx0Reset(void);
void ScalerTypeCPmicRx0Handler(void);
void ScalerTypeCPmicRx0TimerEventProc(EnumScalerTimerEventID enumEventID);
bit ScalerTypeCPmicRx0Setting(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumPDPeakCurType enumPeakCurrent);
BYTE ScalerTypeCPmicRx0Setting_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumPDPeakCurType enumPeakCurrent);
BYTE ScalerTypeCPmicRx0Setting_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumPDPeakCurType enumPeakCurrent);
bit ScalerTypeCPmicRx0VbusDischarge(bit bEn);
BYTE ScalerTypeCPmicRx0VbusDischarge_EXINT0(bit bEn);
BYTE ScalerTypeCPmicRx0VbusDischarge_WDINT(bit bEn);
bit ScalerTypeCPmicRx0SwitchControl(bit bEn, bit bPowerDirection);
BYTE ScalerTypeCPmicRx0SwitchControl_EXINT0(bit bEn, bit bPowerDirection);
BYTE ScalerTypeCPmicRx0SwitchControl_WDINT(bit bEn, bit bPowerDirection);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
EnumTypeCPmicOperationMode ScalerTypeCPmicRx0ReadPpsOperationModeStatus_EXINT0(void);
#endif
#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
void ScalerTypeCPmicRx0ProtectStart(void);
void ScalerTypeCPmicRx0ProtectStart_WDINT(void);
bit ScalerTypeCPmicRx0ProtectTracking(void);
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
void ScalerTypeCPmicRx0FwOcpIntHandler_EXINT0(void);
void ScalerTypeCPmicRx0WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID);
#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
BYTE ScalerTypeCPmicRx0TrackingSafetyProtect(void);
void ScalerTypeCPmicRx0SafetyProtect(void);
#endif
#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
BYTE ScalerTypeCPmicRx0TrackingPollingOcp(void);
void ScalerTypeCPmicRx0OcpProtect(void);
#endif
#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
bit ScalerTypeCPmicRx0TrackingVoltageCompensation(void);
#endif
#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
BYTE ScalerTypeCPmicRx0TrackingIntPin(void);
#endif
#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
void ScalerTypeCPmicRx0OvpUvpIntHandler_EXINT0(void);
#endif
#endif // End of #if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TypeC Hardware IIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicHwIICInitial(void)
{
    // Reset IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module and disable TOR
    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT7 | _BIT0), _BIT7);

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    ScalerSetByte(P7F_61_I2CM_CR1, _TYPE_C_HW_IIC_TOR);

    // Disable burst mode
    ScalerSetByte(P7F_62_I2CM_CR2, 0x00);

    // Clear interrupts
    ScalerSetByte(P7F_63_I2CM_CR3, 0x00);

    // Set fall time period count
    ScalerSetByte(P7F_64_I2CM_STR0, _TYPE_C_HW_IIC_FTPC);

    // Set STA setup time period count
    ScalerSetByte(P7F_65_I2CM_STR1, _TYPE_C_HW_IIC_STA_SUGPIO_C);

    // Set SCL high period count
    ScalerSetByte(P7F_66_I2CM_STR2, _TYPE_C_HW_IIC_SHPC_28000K);

    // Set SCL low period count
    ScalerSetByte(P7F_67_I2CM_STR3, _TYPE_C_HW_IIC_SLPC_28000K);

    // Set frequency divisor: ref = xtal/(FD10+1)
    ScalerSetByte(P7F_6A_I2CM_CCR, _TYPE_C_HW_IIC_FD10_28000K);

    // Clear Pmic related control flag
    CLR_PMIC_IIC_SET_START();

    CLR_PMIC_IIC_IN_MAIN_LOOP();

    CLR_PMIC_IIC_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_IN_WDINT_LOOP();

    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicHwIICSetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        ScalerSetByte(P7F_6A_I2CM_CCR, _TYPE_C_HW_IIC_FD10_14318K);

        // Set STA setup time period count
        ScalerSetByte(P7F_65_I2CM_STR1, _TYPE_C_HW_IIC_STA_SUGPIO_C);

        // Set SCL high period count
        ScalerSetByte(P7F_66_I2CM_STR2, _TYPE_C_HW_IIC_SHPC_14318K);

        // Set SCL low period count
        ScalerSetByte(P7F_67_I2CM_STR3, _TYPE_C_HW_IIC_SLPC_14318K);
    }
    else
    {
        // Set freq. divisor: ref = IOSC/(FD10+1) = 9.3M(ref should be approx 10MHz)
        ScalerSetByte(P7F_6A_I2CM_CCR, _TYPE_C_HW_IIC_FD10_28000K);

        // Set STA setup time period count
        ScalerSetByte(P7F_65_I2CM_STR1, _TYPE_C_HW_IIC_STA_SUGPIO_C);

        // Set SCL high period count
        ScalerSetByte(P7F_66_I2CM_STR2, _TYPE_C_HW_IIC_SHPC_28000K);

        // Set SCL low period count
        ScalerSetByte(P7F_67_I2CM_STR3, _TYPE_C_HW_IIC_SLPC_28000K);
    }
}

//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _TYPE_C_HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck() == _FAIL)
    {
        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // If int happened while this I2C setting, then return.
    if((GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // IIC command Start
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT6, _BIT6);

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte(P7F_69_I2CM_TD);
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetBit(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Clear Pmic I2C set start flag
    CLR_PMIC_IIC_SET_START();

    // If int happened while this I2C setting, then return.
    if((GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    CLR_PMIC_IIC_IN_MAIN_LOOP();

    return _SUCCESS;
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICRead_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray) using 1
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _TYPE_C_HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck_EXINT0() == _FAIL)
    {
        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // IIC command Start
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT6, _BIT6);

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_68_I2CM_SR, _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte_EXINT(P7F_69_I2CM_TD);
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Clear Pmic I2C set start flag
    CLR_PMIC_IIC_SET_START();

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    CLR_PMIC_IIC_IN_EXINT0_LOOP();

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    if((ucDataLength + ucSubAddrLength) > _TYPE_C_HW_IIC_WRITE_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck() == _FAIL)
    {
        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    pData[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData[0]; ucI++)
    {
        ScalerSetByte(P7F_69_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if((GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte(P7F_60_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    CLR_PMIC_IIC_IN_MAIN_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICWrite_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray) using 1
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    if((ucDataLength + ucSubAddrLength) > _TYPE_C_HW_IIC_WRITE_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck_EXINT0() == _FAIL)
    {
        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    pData_EXINT[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData_EXINT[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData_EXINT[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData_EXINT[0] + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData_EXINT[0]; ucI++)
    {
        ScalerSetByte_EXINT(P7F_69_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte_EXINT(P7F_60_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // If interrupt form other process, then wait until transmit finished.
    if((GET_PMIC_IIC_IN_MAIN_LOOP() == _TRUE) || (GET_PMIC_IIC_IN_WDINT_LOOP() == _TRUE))
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            CLR_PMIC_IIC_IN_EXINT0_LOOP();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _SUCCESS;
    }

    CLR_PMIC_IIC_IN_EXINT0_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICWrite_WDINT(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray) using 3
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    if((ucDataLength + ucSubAddrLength) > _TYPE_C_HW_IIC_WRITE_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck_WDINT() == _FAIL)
    {
        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_WDINT(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    pData_EXINT[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData_EXINT[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData_EXINT[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData_EXINT[0] + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData_EXINT[0]; ucI++)
    {
        ScalerSetByte_EXINT(P7F_69_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte_EXINT(P7F_60_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // If interrupt form other process, then wait until transmit finished.
    if((GET_PMIC_IIC_IN_MAIN_LOOP() == _TRUE) || (GET_PMIC_IIC_IN_EXINT0_LOOP() == _TRUE))
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_WDINT(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            CLR_PMIC_IIC_IN_WDINT_LOOP();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();

        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _SUCCESS;
    }

    CLR_PMIC_IIC_IN_WDINT_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicHwIICSetStartCheck(void)
{
    SET_PMIC_IIC_IN_MAIN_LOOP();

    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICSetStartCheck_EXINT0(void) using 1
{
    SET_PMIC_IIC_IN_EXINT0_LOOP();

    SET_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICSetStartCheck_WDINT(void) using 3
{
    SET_PMIC_IIC_IN_WDINT_LOOP();

    SET_PMIC_IIC_EVER_IN_WDINT_LOOP();

    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_WDINT(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicIICRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Receive 24 bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ScalerTypeCPmicHwIICRead(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            return _FAIL;
        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicIICRead_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray) using 1
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Receive 24 bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ScalerTypeCPmicHwIICRead_EXINT0(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            return _FAIL;
        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicIICWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_TYPE_C_HW_IIC_WRITE_SIZE + 2];

    if(usLength <= 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_WRITE_SIZE - ucSubAddrLength;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeCPmicHwIICWrite(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicIICWrite_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray) using 1
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_TYPE_C_HW_IIC_WRITE_SIZE + 2];

    if(usLength <= 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_WRITE_SIZE - ucSubAddrLength;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeCPmicHwIICWrite_EXINT0(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicIICWrite_WDINT(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray) using 3
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_TYPE_C_HW_IIC_WRITE_SIZE + 2];

    if(usLength <= 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_WRITE_SIZE - ucSubAddrLength;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeCPmicHwIICWrite_WDINT(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Reset Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicIICReset(void)
{
    CLR_PMIC_IIC_IN_MAIN_LOOP();
    CLR_PMIC_IIC_IN_EXINT0_LOOP();
    CLR_PMIC_IIC_IN_WDINT_LOOP();
    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();
    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return;
        }

        // Clear all flags
        ScalerSetBit(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }
}
#endif // End of #if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Rx0 PMIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0Initial(void)
{
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
    ScalerTypeCPmicHwIICInitial();

    ScalerTypeCPmicIICReset();
#endif

    ExternalDeviceInterfaceTypeCPmicACOnInitial();

    // Reset PMIC Output Type
    SET_PMIC_OUTPUT_MODE_STATUS(_PD_NONE_SETTING_PDO);

#if(_TYPE_C_PMIC_FORCE_OUTPUT == _ON)
    ScalerTypeCPmicRx0Setting(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, _TYPE_C_PMIC_FORCE_VOLTAGE, _TYPE_C_PMIC_FORCE_CURRENT, _PD_PEAK_CUR_NONE);
    ScalerTimerDelayXms(3000);

#if(_TYPE_C_PMIC_DEBUG == _ON)
    if(ExternalDeviceInterfaceTypeCPmicDebugCheckStatus() == _TYPE_C_PMIC_CONTROL_FAIL)
    {
        DebugMessageTypeC("PMIC Check Fail!", 0x00);
    }
#endif

    ScalerTypeCPmicRx0Setting(_OFF, _PD_POWER_SRC, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif
}

//--------------------------------------------------
// Description  : Rx0 PMIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0Reset(void)
{
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
    ScalerTypeCPmicHwIICInitial();

    ScalerTypeCPmicIICReset();
#endif

    ExternalDeviceInterfaceTypeCPmicUnattachReset();

    // Reset PMIC Output Type
    SET_PMIC_OUTPUT_MODE_STATUS(_PD_NONE_SETTING_PDO);

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // Disable INT & Clear INT Flag
    ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _DISABLE);
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    SET_PMIC_PEAK_CURRENT_TYPE(_PD_PEAK_CUR_NONE);

    // Set Vbus Short Voltage
    SET_PMIC_SHORT_VOLTAGE(_TYPE_C_PMIC_SHORT_VOLTAGE);

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
    CLR_PMIC_SAFETY_PROTECT_TRIGGER();
#endif

    // Disable INT & Clear INT Flag
    ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _DISABLE);
#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    CLR_PMIC_OCP_PROTECT_TRIGGER();
#endif

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
    CLR_PMIC_OUTPUT_ENABLE();
    SET_PMIC_BIDIR_SNK();
    CLR_PMIC_PROTECT_VALID();
    CLR_PMIC_PROTECT_TIMER_CHECK();
    CLR_PMIC_PROTECT_TIMER_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    CLR_PMIC_GET_OMF_INFO_START();
    SET_PMIC_OMF_INFO(_TYPE_C_PMIC_CV_MODE_OPERATION);
#endif
}

//--------------------------------------------------
// Description  : Rx0 PMIC Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0Handler(void)
{
#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
    // Check if Start PMIC Protection Tracking Timer
    if(GET_PMIC_PROTECT_TIMER_START() == _TRUE)
    {
        CLR_PMIC_PROTECT_TIMER_START();

        // Active PMIC Protection Tracking Timer
        ScalerTimerReactiveTimerEvent(40, _SCALER_TIMER_EVENT_PMIC_TRACKING);
    }
#endif
}

//--------------------------------------------------
// Description  : RX0 PMIC Timer Event Proc
// Input Value  : enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0TimerEventProc(EnumScalerTimerEventID enumEventID)
{
    enumEventID = enumEventID;

    switch(enumEventID)
    {
#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_PMIC_TRACKING:

            ScalerTypeCPmicRx0ProtectTracking();

            break;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_PMIC_SAFETY_PROTECT:

            ScalerTypeCPmicRx0SafetyProtect();

            break;
#endif // End of #if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON))

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        case _SCALER_TIMER_EVENT_PMIC_POLLING_OCP:

            ScalerTypeCPmicRx0OcpProtect();

            break;
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Control Rx0 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0Setting(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumPDPeakCurType enumPeakCurrent)
{
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    // Avoid Warning
    enumPeakCurrent = enumPeakCurrent;

    // ========================================================
    // CTS Parameter Adjustment
    // ========================================================

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_PMIC_MIN_PPS_CURRENT);
    }
    else
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_PMIC_MIN_CURRENT);
    }

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Setting Flow
    // ========================================================

    // Caculate OVP & UVP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        WORD usOVPThreshold = 0x0000;
        WORD usUVPThreshold = 0x0000;

        // Translate Voltage to SARADC Value
        usOVPThreshold = ((WORD)(((DWORD)usVoltage * 1024) / _TYPE_C_ADC_MAX_VOLTAGE));
        usUVPThreshold = usOVPThreshold;

        // Set Threshold for OVP
        usOVPThreshold = ((WORD)((((DWORD)(usOVPThreshold)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100));

        if(usOVPThreshold >= 0x3FF)
        {
            usOVPThreshold = 0x3FE;
        }

        // Set Threshold for UVP
        if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
        {
            usUVPThreshold = ((WORD)(((DWORD)_TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD * 1024) / _TYPE_C_ADC_MAX_VOLTAGE));
        }
        else
        {
            usUVPThreshold = ((WORD)((((DWORD)(usUVPThreshold)) * _TYPE_C_PMIC_FW_UVP_THRESHOLD) / 100));
        }

        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _DISABLE);

        // Set OVP/UVP range
        ScalerTypeCPowerRangeIntSetting(_TYPE_C_UFP_VMON, usOVPThreshold, usUVPThreshold, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _DISABLE);
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // ========================================================
    // OCP by SARADC Setting Flow
    // ========================================================

    // Set Peak Current Mode
    SET_PMIC_PEAK_CURRENT_TYPE(enumPeakCurrent);

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
    // Clear PMIC Safety Protect Trigger Flag
    CLR_PMIC_SAFETY_PROTECT_TRIGGER();
#endif

    // Caculate OCP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        BYTE ucCount = 0;
        BYTE pucOcpThreshold[3] = {0, 0, 0};
        WORD usCurrentTemp = 0;
        WORD usDelayTemp = 0;

        // ====================================================
        // Set OCP Threshold
        // ====================================================

        // Clear OCP Protect Level
        SET_PMIC_FW_OCP_PROTECT_LEVEL(0);

        // Calculate current to 10-bit SARADC Code Value
        SET_PMIC_FW_OCP_CURRENT(0, ((WORD)((((DWORD)usCurrent * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
        SET_PMIC_FW_OCP_DELAY(0, _TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);


        // ====================================================
        // Check Peak Current Format
        // ====================================================

        // OCP Threshold Sorting from small to big
        if(enumPeakCurrent != _PD_PEAK_CUR_NONE)
        {
            // Peak Current Setting from Spec
            if(enumPeakCurrent == _PD_PEAK_CUR_1)
            {
                // Peak Current Threshold 1: 110%(10ms)
                pucOcpThreshold[0] = 110;

                // Peak Current Threshold 2: 125%(2ms)
                pucOcpThreshold[1] = 125;

                // Peak Current Threshold 3: 150%(1ms)
                pucOcpThreshold[2] = 150;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_2)
            {
                // Peak Current Threshold 1: 125%(10ms)
                pucOcpThreshold[0] = 125;

                // Peak Current Threshold 2: 150%(2ms)
                pucOcpThreshold[1] = 150;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_3)
            {
                // Peak Current Threshold 1: 150%(10ms)
                pucOcpThreshold[0] = 150;

                // Peak Current Threshold 2: 175%(2ms)
                pucOcpThreshold[1] = 175;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }

            // Peak Current Threshold 1
            SET_PMIC_FW_OCP_CURRENT(1, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[0] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(1, 10);

            // Peak Current Threshold 2
            SET_PMIC_FW_OCP_CURRENT(2, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[1] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(2, 2);

            // Peak Current Threshold 3
            SET_PMIC_FW_OCP_CURRENT(3, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[2] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(3, 1);

            // Sorting OCP Level
            for(ucCount = 0; ucCount < 3; ucCount++)
            {
                if(GET_PMIC_FW_OCP_CURRENT(ucCount) > GET_PMIC_FW_OCP_CURRENT(ucCount + 1))
                {
                    usCurrentTemp = GET_PMIC_FW_OCP_CURRENT(ucCount);
                    usDelayTemp = GET_PMIC_FW_OCP_DELAY(ucCount);

                    SET_PMIC_FW_OCP_CURRENT((ucCount), GET_PMIC_FW_OCP_CURRENT(ucCount + 1));
                    SET_PMIC_FW_OCP_DELAY((ucCount), GET_PMIC_FW_OCP_DELAY(ucCount + 1));

                    SET_PMIC_FW_OCP_CURRENT((ucCount + 1), usCurrentTemp);
                    SET_PMIC_FW_OCP_DELAY((ucCount + 1), usDelayTemp);
                }
            }
        }
        else
        {
            SET_PMIC_FW_OCP_CURRENT(1, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(1, 0);
            SET_PMIC_FW_OCP_CURRENT(2, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(2, 0);
            SET_PMIC_FW_OCP_CURRENT(3, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(3, 0);
        }

        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _DISABLE);

        // Set Range to check if Vbus current will be triggered OCP Current.
        // Do not enable INT immediately for avoiding inrush current.
        ScalerTypeCPowerRangeIntSetting(_TYPE_C_UFP_IMON, 0xFFFF, GET_PMIC_FW_OCP_CURRENT(0), _TYPE_C_ADC_WITHIN_RANGE);

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
        // ====================================================
        // Safety Protect Setting Flow
        // ====================================================

        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();

        // Set Safety Current Value
        SET_PMIC_SAFETY_CURRENT_VALUE((WORD)(((DWORD)_TYPE_C_PMIC_SAFETY_POWER_LIMIT * 10000) / usVoltage));

        // Minimum Output Current Assurance
        SET_PMIC_SAFETY_CURRENT_VALUE(MAXOF(usCurrent, GET_PMIC_SAFETY_CURRENT_VALUE()));
#endif // #if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)


        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Add more 66% OCP value in order to avoid triggering the PMIC self OCP
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _DISABLE);
    }

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    // ========================================================
    // OCP by Polling PMIC's ADC Value Setting Flow
    // ========================================================

    // Clear PMIC OCP Protect Trigger Flag
    CLR_PMIC_OCP_PROTECT_TRIGGER();

    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();

        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Set PMIC OVP threshold to Max
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
    // ========================================================
    // Vbus Voltage Compensation Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
    // ========================================================
    // PMIC INT_Pin Checking Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    // ========================================================
    // PD 3.0 PPS Support Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_PMIC_GET_OMF_INFO_START();
    }
    else
    {
        CLR_PMIC_GET_OMF_INFO_START();
    }
#endif

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
#if(_TYPE_C_PMIC_DEBUG == _ON)
    // ========================================================
    // PMIC Debug Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

    // ========================================================
    // PMIC Check Support Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_PMIC_OUTPUT_ENABLE();
        SET_PMIC_BIDIR_SRC();
    }
    else
    {
        CLR_PMIC_OUTPUT_ENABLE();
        SET_PMIC_BIDIR_SNK();

        // Clear PMIC Protection Timer Check Flag When Turn off Vbus Power
        CLR_PMIC_PROTECT_TIMER_CHECK();
    }

    CLR_PMIC_PROTECT_VALID();
#endif

    // ====================================================
    // PMIC Setting Flow
    // ====================================================
    if(bAction == _ON)
    {
        ScalerTypeCPmicRx0SwitchControl(_ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
        }

        if(GET_PMIC_OUTPUT_MODE_STATUS() != enumPdoType)
        {
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(enumDirection, usVoltage, usCurrent);
    }
    else
    {
        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff();

        // Reset PMIC Output Type
        SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
    }

    // ====================================================
    // Check PMIC Control Result
    // ====================================================
    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Control Rx0 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0Setting_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumPDPeakCurType enumPeakCurrent) using 1
{
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    // Avoid Warning
    enumPeakCurrent = enumPeakCurrent;

    // ========================================================
    // CTS Parameter Adjustment
    // ========================================================

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_PMIC_MIN_PPS_CURRENT);
    }
    else
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_PMIC_MIN_CURRENT);
    }

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Setting Flow
    // ========================================================

    // Caculate OVP & UVP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        WORD usOVPThreshold = 0x0000;
        WORD usUVPThreshold = 0x0000;

        // Translate Voltage to SARADC Value
        usOVPThreshold = ((WORD)(((DWORD)usVoltage * 1024) / _TYPE_C_ADC_MAX_VOLTAGE));
        usUVPThreshold = usOVPThreshold;

        // Set Threshold for OVP
        usOVPThreshold = ((WORD)((((DWORD)(usOVPThreshold)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100));

        if(usOVPThreshold >= 0x3FF)
        {
            usOVPThreshold = 0x3FE;
        }

        // Set Threshold for UVP
        if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
        {
            usUVPThreshold = ((WORD)(((DWORD)_TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD * 1024) / _TYPE_C_ADC_MAX_VOLTAGE));
        }
        else
        {
            usUVPThreshold = ((WORD)((((DWORD)(usUVPThreshold)) * _TYPE_C_PMIC_FW_UVP_THRESHOLD) / 100));
        }

        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_VMON, _DISABLE);

        // Set OVP/UVP range
        ScalerTypeCPowerRangeIntSetting_EXINT0(_TYPE_C_UFP_VMON, usOVPThreshold, usUVPThreshold, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_VMON, _DISABLE);
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // ========================================================
    // OCP by SARADC Setting Flow
    // ========================================================

    // Set Peak Current Mode
    SET_PMIC_PEAK_CURRENT_TYPE(enumPeakCurrent);

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
    // Clear PMIC Safety Protect Trigger Flag
    CLR_PMIC_SAFETY_PROTECT_TRIGGER();
#endif

    // Caculate OCP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        BYTE ucCount = 0;
        BYTE pucOcpThreshold[3] = {0, 0, 0};
        WORD usCurrentTemp = 0;
        WORD usDelayTemp = 0;

        // ====================================================
        // Set OCP Threshold
        // ====================================================

        // Clear OCP Protect Level
        SET_PMIC_FW_OCP_PROTECT_LEVEL(0);

        // Calculate current to 10-bit SARADC Code Value
        SET_PMIC_FW_OCP_CURRENT(0, ((WORD)((((DWORD)usCurrent * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
        SET_PMIC_FW_OCP_DELAY(0, _TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);


        // ====================================================
        // Check Peak Current Format
        // ====================================================

        // OCP Threshold Sorting from small to big
        if(enumPeakCurrent != _PD_PEAK_CUR_NONE)
        {
            // Peak Current Setting from Spec
            if(enumPeakCurrent == _PD_PEAK_CUR_1)
            {
                // Peak Current Threshold 1: 110%(10ms)
                pucOcpThreshold[0] = 110;

                // Peak Current Threshold 2: 125%(2ms)
                pucOcpThreshold[1] = 125;

                // Peak Current Threshold 3: 150%(1ms)
                pucOcpThreshold[2] = 150;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_2)
            {
                // Peak Current Threshold 1: 125%(10ms)
                pucOcpThreshold[0] = 125;

                // Peak Current Threshold 2: 150%(2ms)
                pucOcpThreshold[1] = 150;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_3)
            {
                // Peak Current Threshold 1: 150%(10ms)
                pucOcpThreshold[0] = 150;

                // Peak Current Threshold 2: 175%(2ms)
                pucOcpThreshold[1] = 175;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }

            // Peak Current Threshold 1
            SET_PMIC_FW_OCP_CURRENT(1, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[0] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(1, 10);

            // Peak Current Threshold 2
            SET_PMIC_FW_OCP_CURRENT(2, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[1] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(2, 2);

            // Peak Current Threshold 3
            SET_PMIC_FW_OCP_CURRENT(3, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[2] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(3, 1);

            // Sorting OCP Level
            for(ucCount = 0; ucCount < 3; ucCount++)
            {
                if(GET_PMIC_FW_OCP_CURRENT(ucCount) > GET_PMIC_FW_OCP_CURRENT(ucCount + 1))
                {
                    usCurrentTemp = GET_PMIC_FW_OCP_CURRENT(ucCount);
                    usDelayTemp = GET_PMIC_FW_OCP_DELAY(ucCount);

                    SET_PMIC_FW_OCP_CURRENT((ucCount), GET_PMIC_FW_OCP_CURRENT(ucCount + 1));
                    SET_PMIC_FW_OCP_DELAY((ucCount), GET_PMIC_FW_OCP_DELAY(ucCount + 1));

                    SET_PMIC_FW_OCP_CURRENT((ucCount + 1), usCurrentTemp);
                    SET_PMIC_FW_OCP_DELAY((ucCount + 1), usDelayTemp);
                }
            }
        }
        else
        {
            SET_PMIC_FW_OCP_CURRENT(1, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(1, 0);
            SET_PMIC_FW_OCP_CURRENT(2, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(2, 0);
            SET_PMIC_FW_OCP_CURRENT(3, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(3, 0);
        }

        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_IMON, _DISABLE);

        // Set Range to check if Vbus current will be triggered OCP Current.
        // Do not enable INT immediately for avoiding inrush current.
        ScalerTypeCPowerRangeIntSetting_EXINT0(_TYPE_C_UFP_IMON, 0xFFFF, GET_PMIC_FW_OCP_CURRENT(0), _TYPE_C_ADC_WITHIN_RANGE);

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
        // ====================================================
        // Safety Protect Setting Flow
        // ====================================================

        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();

        // Set Safety Current Value
        SET_PMIC_SAFETY_CURRENT_VALUE((WORD)(((DWORD)_TYPE_C_PMIC_SAFETY_POWER_LIMIT * 10000) / usVoltage));

        // Minimum Output Current Assurance
        SET_PMIC_SAFETY_CURRENT_VALUE(MAXOF(usCurrent, GET_PMIC_SAFETY_CURRENT_VALUE()));
#endif // #if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)


        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Add more 66% OCP value in order to avoid triggering the PMIC self OCP
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_IMON, _DISABLE);
    }

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    // ========================================================
    // OCP by Polling PMIC's ADC Value Setting Flow
    // ========================================================

    // Clear PMIC OCP Protect Trigger Flag
    CLR_PMIC_OCP_PROTECT_TRIGGER();

    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();

        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Set PMIC OVP threshold to Max
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
    // ========================================================
    // Vbus Voltage Compensation Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
    // ========================================================
    // PMIC INT_Pin Checking Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    // ========================================================
    // PD 3.0 PPS Support Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_PMIC_GET_OMF_INFO_START();
    }
    else
    {
        CLR_PMIC_GET_OMF_INFO_START();
    }
#endif

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
#if(_TYPE_C_PMIC_DEBUG == _ON)
    // ========================================================
    // PMIC Debug Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

    // ========================================================
    // PMIC Check Support Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_PMIC_OUTPUT_ENABLE();
        SET_PMIC_BIDIR_SRC();
    }
    else
    {
        CLR_PMIC_OUTPUT_ENABLE();
        SET_PMIC_BIDIR_SNK();

        // Clear PMIC Protection Timer Check Flag When Turn off Vbus Power
        CLR_PMIC_PROTECT_TIMER_CHECK();
    }

    CLR_PMIC_PROTECT_VALID();
#endif

    // ====================================================
    // PMIC Setting Flow
    // ====================================================
    if(bAction == _ON)
    {
        ScalerTypeCPmicRx0SwitchControl_EXINT0(_ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
        }

        if(GET_PMIC_OUTPUT_MODE_STATUS() != enumPdoType)
        {
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(enumDirection, usVoltage, usCurrent);
    }
    else
    {
        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0();

        // Reset PMIC Output Type
        SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
    }

    // ====================================================
    // Check PMIC Control Result
    // ====================================================
    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Control Rx0 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0Setting_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumPDPeakCurType enumPeakCurrent) using 3
{
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    // Avoid Warning
    enumPeakCurrent = enumPeakCurrent;

    // ========================================================
    // CTS Parameter Adjustment
    // ========================================================

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_PMIC_MIN_PPS_CURRENT);
    }
    else
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_PMIC_MIN_CURRENT);
    }

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Setting Flow
    // ========================================================

    // Caculate OVP & UVP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        WORD usOVPThreshold = 0x0000;
        WORD usUVPThreshold = 0x0000;

        // Translate Voltage to SARADC Value
        usOVPThreshold = ((WORD)(((DWORD)usVoltage * 1024) / _TYPE_C_ADC_MAX_VOLTAGE));
        usUVPThreshold = usOVPThreshold;

        // Set Threshold for OVP
        usOVPThreshold = ((WORD)((((DWORD)(usOVPThreshold)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100));

        if(usOVPThreshold >= 0x3FF)
        {
            usOVPThreshold = 0x3FE;
        }

        // Set Threshold for UVP
        if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
        {
            usUVPThreshold = ((WORD)(((DWORD)_TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD * 1024) / _TYPE_C_ADC_MAX_VOLTAGE));
        }
        else
        {
            usUVPThreshold = ((WORD)((((DWORD)(usUVPThreshold)) * _TYPE_C_PMIC_FW_UVP_THRESHOLD) / 100));
        }

        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_VMON, _DISABLE);

        // Set OVP/UVP range
        ScalerTypeCPowerRangeIntSetting_WDINT(_TYPE_C_UFP_VMON, usOVPThreshold, usUVPThreshold, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_VMON, _DISABLE);
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // ========================================================
    // OCP by SARADC Setting Flow
    // ========================================================

    // Set Peak Current Mode
    SET_PMIC_PEAK_CURRENT_TYPE(enumPeakCurrent);

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
    // Clear PMIC Safety Protect Trigger Flag
    CLR_PMIC_SAFETY_PROTECT_TRIGGER();
#endif

    // Caculate OCP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        BYTE ucCount = 0;
        BYTE pucOcpThreshold[3] = {0, 0, 0};
        WORD usCurrentTemp = 0;
        WORD usDelayTemp = 0;

        // ====================================================
        // Set OCP Threshold
        // ====================================================

        // Clear OCP Protect Level
        SET_PMIC_FW_OCP_PROTECT_LEVEL(0);

        // Calculate current to 10-bit SARADC Code Value
        SET_PMIC_FW_OCP_CURRENT(0, ((WORD)((((DWORD)usCurrent * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
        SET_PMIC_FW_OCP_DELAY(0, _TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);


        // ====================================================
        // Check Peak Current Format
        // ====================================================

        // OCP Threshold Sorting from small to big
        if(enumPeakCurrent != _PD_PEAK_CUR_NONE)
        {
            // Peak Current Setting from Spec
            if(enumPeakCurrent == _PD_PEAK_CUR_1)
            {
                // Peak Current Threshold 1: 110%(10ms)
                pucOcpThreshold[0] = 110;

                // Peak Current Threshold 2: 125%(2ms)
                pucOcpThreshold[1] = 125;

                // Peak Current Threshold 3: 150%(1ms)
                pucOcpThreshold[2] = 150;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_2)
            {
                // Peak Current Threshold 1: 125%(10ms)
                pucOcpThreshold[0] = 125;

                // Peak Current Threshold 2: 150%(2ms)
                pucOcpThreshold[1] = 150;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_3)
            {
                // Peak Current Threshold 1: 150%(10ms)
                pucOcpThreshold[0] = 150;

                // Peak Current Threshold 2: 175%(2ms)
                pucOcpThreshold[1] = 175;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }

            // Peak Current Threshold 1
            SET_PMIC_FW_OCP_CURRENT(1, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[0] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(1, 10);

            // Peak Current Threshold 2
            SET_PMIC_FW_OCP_CURRENT(2, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[1] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(2, 2);

            // Peak Current Threshold 3
            SET_PMIC_FW_OCP_CURRENT(3, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[2] / 100) * 1024) / _TYPE_C_ADC_MAX_CURRENT)));
            SET_PMIC_FW_OCP_DELAY(3, 1);

            // Sorting OCP Level
            for(ucCount = 0; ucCount < 3; ucCount++)
            {
                if(GET_PMIC_FW_OCP_CURRENT(ucCount) > GET_PMIC_FW_OCP_CURRENT(ucCount + 1))
                {
                    usCurrentTemp = GET_PMIC_FW_OCP_CURRENT(ucCount);
                    usDelayTemp = GET_PMIC_FW_OCP_DELAY(ucCount);

                    SET_PMIC_FW_OCP_CURRENT((ucCount), GET_PMIC_FW_OCP_CURRENT(ucCount + 1));
                    SET_PMIC_FW_OCP_DELAY((ucCount), GET_PMIC_FW_OCP_DELAY(ucCount + 1));

                    SET_PMIC_FW_OCP_CURRENT((ucCount + 1), usCurrentTemp);
                    SET_PMIC_FW_OCP_DELAY((ucCount + 1), usDelayTemp);
                }
            }
        }
        else
        {
            SET_PMIC_FW_OCP_CURRENT(1, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(1, 0);
            SET_PMIC_FW_OCP_CURRENT(2, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(2, 0);
            SET_PMIC_FW_OCP_CURRENT(3, 0x03FF);
            SET_PMIC_FW_OCP_DELAY(3, 0);
        }

        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_IMON, _DISABLE);

        // Set Range to check if Vbus current will be triggered OCP Current.
        // Do not enable INT immediately for avoiding inrush current.
        ScalerTypeCPowerRangeIntSetting_WDINT(_TYPE_C_UFP_IMON, 0xFFFF, GET_PMIC_FW_OCP_CURRENT(0), _TYPE_C_ADC_WITHIN_RANGE);

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
        // ====================================================
        // Safety Protect Setting Flow
        // ====================================================

        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();

        // Set Safety Current Value
        SET_PMIC_SAFETY_CURRENT_VALUE((WORD)(((DWORD)_TYPE_C_PMIC_SAFETY_POWER_LIMIT * 10000) / usVoltage));

        // Minimum Output Current Assurance
        SET_PMIC_SAFETY_CURRENT_VALUE(MAXOF(usCurrent, GET_PMIC_SAFETY_CURRENT_VALUE()));
#endif // #if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)


        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Add more 66% OCP value in order to avoid triggering the PMIC self OCP
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_IMON, _DISABLE);
    }

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    // ========================================================
    // OCP by Polling PMIC's ADC Value Setting Flow
    // ========================================================

    // Clear PMIC OCP Protect Trigger Flag
    CLR_PMIC_OCP_PROTECT_TRIGGER();

    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();

        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Set PMIC OVP threshold to Max
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
    // ========================================================
    // Vbus Voltage Compensation Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
    // ========================================================
    // PMIC INT_Pin Checking Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    // ========================================================
    // PD 3.0 PPS Support Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_PMIC_GET_OMF_INFO_START();
    }
    else
    {
        CLR_PMIC_GET_OMF_INFO_START();
    }
#endif

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
#if(_TYPE_C_PMIC_DEBUG == _ON)
    // ========================================================
    // PMIC Debug Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

    // ========================================================
    // PMIC Check Support Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_PMIC_OUTPUT_ENABLE();
        SET_PMIC_BIDIR_SRC();
    }
    else
    {
        CLR_PMIC_OUTPUT_ENABLE();
        SET_PMIC_BIDIR_SNK();

        // Clear PMIC Protection Timer Check Flag When Turn off Vbus Power
        CLR_PMIC_PROTECT_TIMER_CHECK();
    }

    CLR_PMIC_PROTECT_VALID();
#endif

    // ====================================================
    // PMIC Setting Flow
    // ====================================================
    if(bAction == _ON)
    {
        ScalerTypeCPmicRx0SwitchControl_WDINT(_ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
        }

        if(GET_PMIC_OUTPUT_MODE_STATUS() != enumPdoType)
        {
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(enumDirection, usVoltage, usCurrent);
    }
    else
    {
        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT();

        // Reset PMIC Output Type
        SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
    }

    // ====================================================
    // Check PMIC Control Result
    // ====================================================
    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Discharge Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0VbusDischarge(bit bEn)
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCPmicRx0SwitchControl(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge(enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Discharge Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0VbusDischarge_EXINT0(bit bEn) using 1
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCPmicRx0SwitchControl_EXINT0(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Discharge Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0VbusDischarge_WDINT(bit bEn) using 3
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCPmicRx0SwitchControl_WDINT(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC Switch Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0SwitchControl(bit bEn, bit bPowerDirection)
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl(enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC Switch Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0SwitchControl_EXINT0(bit bEn, bit bPowerDirection) using 1
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC Switch Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0SwitchControl_WDINT(bit bEn, bit bPowerDirection) using 3
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : None
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ScalerTypeCPmicRx0ReadPpsOperationModeStatus_EXINT0(void) using 1
{
    if(PCB_PMIC_ALERT_DETECT() == _PMIC_ALERT_ON)
    {
        if(ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0() == _TYPE_C_PMIC_CC_MODE_OPERATION)
        {
            SET_PMIC_OMF_INFO(_TYPE_C_PMIC_CC_MODE_OPERATION);
        }
        else
        {
            SET_PMIC_OMF_INFO(_TYPE_C_PMIC_CV_MODE_OPERATION);
        }
    }

    return GET_PMIC_OMF_INFO();
}
#endif

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C PMIC Protection Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0ProtectStart(void)
{
    // Enable PMIC Protection Int
#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // Enable OVP/UVP Int
    ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _ENABLE);
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // Enable OCP Int
    ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _ENABLE);
#endif

    // Check if Any PMIC Protection Timer Needs to be Actived
    if(GET_PMIC_PROTECT_TIMER_CHECK() == _TRUE)
    {
        CLR_PMIC_PROTECT_TIMER_CHECK();

        // Set PMIC Protection Timer Start Flag to Active PMIC Protection Tracking Timer in Main Loop
        SET_PMIC_PROTECT_TIMER_START();
    }

    SET_PMIC_PROTECT_VALID();
}

//--------------------------------------------------
// Description  : Type-C PMIC Protection Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0ProtectStart_WDINT(void) using 3
{
    // Enable PMIC Protection Int
#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // Enable OVP/UVP Int
    ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_VMON, _ENABLE);
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // Enable OCP Int
    ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_IMON, _ENABLE);
#endif

    // Check if Any PMIC Protection Timer Needs to be Actived
    if(GET_PMIC_PROTECT_TIMER_CHECK() == _TRUE)
    {
        CLR_PMIC_PROTECT_TIMER_CHECK();

        // Set PMIC Protection Timer Start Flag to Active PMIC Protection Tracking Timer in Main Loop
        SET_PMIC_PROTECT_TIMER_START();
    }

    SET_PMIC_PROTECT_VALID();
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Check
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0ProtectTracking(void)
{
    BYTE ucResult = _SUCCESS;
    BYTE ucTimerEvent = 0x00;

    // Check if PMIC Protection Valid
    if(GET_PMIC_PROTECT_VALID() == _TRUE)
    {
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
        ucTimerEvent |= ScalerTypeCPmicRx0TrackingSafetyProtect();
#endif

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        ucTimerEvent |= ScalerTypeCPmicRx0TrackingPollingOcp();
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
        // Set 200ms Timer Event for Voltage Compensation Tracking
        ucTimerEvent |= 0x02;

        ucResult = ScalerTypeCPmicRx0TrackingVoltageCompensation();
#endif // End of #if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
        ucTimerEvent |= ScalerTypeCPmicRx0TrackingIntPin();
#endif // End of #if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)

#if(_TYPE_C_PMIC_DEBUG == _ON)
        ucTimerEvent |= 0x10;

        ExternalDeviceInterfaceTypeCPmicDebugCheckStatus();
#endif // End of #if(_TYPE_C_PMIC_DEBUG == _ON)
    }

    // Reactive PMIC Protection Tracking Timer Event
    if(ucTimerEvent != 0x00)
    {
        if((ucTimerEvent & 0x01) != 0x00)
        {
            ScalerTimerReactiveTimerEvent(10, _SCALER_TIMER_EVENT_PMIC_TRACKING);
        }
        else
        {
            ScalerTimerReactiveTimerEvent(200, _SCALER_TIMER_EVENT_PMIC_TRACKING);
        }
    }

    return ucResult;
}

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
//--------------------------------------------------
// Description  : RX0 PMIC FW Ocp interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0FwOcpIntHandler_EXINT0(void) using 1
{
    WORD usCurrentValue = 0;
    WORD usOcpDelay = GET_PMIC_FW_OCP_DELAY(0);
    BYTE ucCount = 0;

    // ====================================================
    // Check Comparator INT Flag
    // ====================================================
    if(ScalerTypeCPowerRangeIntCheck_EXINT0(_TYPE_C_UFP_IMON) == _FALSE)
    {
        return;
    }


    // ====================================================
    // Vbus Shorting Detect
    // ====================================================

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT != _ON)
    // Only when not support OVP/UVP for avoiding repeated protection
    for(ucCount = 0; ucCount < 2; ucCount++)
    {
        // Compare value in "ADC Ideal Data" Form
        if(ScalerTypeCPowerRx0CorrectionToIdealData_EXINT0(ScalerTypeCPowerGetAdcOutput_EXINT0(_TYPE_C_UFP_VMON)) < GET_PMIC_SHORT_VOLTAGE())
        {
            // Disable Pmic
            ScalerTypeCPmicRx0Setting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

            // Set OCP Event
            ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OCP);

            return;
        }
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT != _ON)


    // ====================================================
    // Determine OCP Trigger Level
    // ====================================================

    // Get Vbus Current in Ideal Value
    usCurrentValue = ScalerTypeCPowerRx0CorrectionToIdealData_EXINT0(ScalerTypeCPowerGetAdcOutput_EXINT0(_TYPE_C_UFP_IMON));

    // Use Ocp Threshold to Determine Delay Time
    for(ucCount = 0; ucCount < 4; ucCount++)
    {
        // Compare value in "ADC Ideal Data" Form
        if(usCurrentValue > GET_PMIC_FW_OCP_CURRENT(ucCount))
        {
            // Record Trigger Level
            SET_PMIC_FW_OCP_PROTECT_LEVEL(ucCount);

            // Set Delay Time
            usOcpDelay = GET_PMIC_FW_OCP_DELAY(ucCount);
        }
    }


    // ====================================================
    // Set OCP Delay
    // ====================================================

    if(usOcpDelay == 0)
    {
        // Disable Pmic
        ScalerTypeCPmicRx0Setting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // Set OCP Event
        ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OCP);
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_IMON, _DISABLE);

        // Check OCP triggers highest level or not
        if(GET_PMIC_FW_OCP_PROTECT_LEVEL() < 3)
        {
            // Set to next OCP level
            ScalerTypeCPowerRangeIntSetting_EXINT0(_TYPE_C_UFP_IMON, 0xFFFF, GET_PMIC_FW_OCP_CURRENT(GET_PMIC_FW_OCP_PROTECT_LEVEL() + 1), _TYPE_C_ADC_WITHIN_RANGE);

            // Enable INT & Clear INT Flag
            ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_IMON, _ENABLE);
        }

        // Set WD Timer to Delay Shutdown Pmic
        ScalerTimerWDActivateTimerEvent_EXINT0(usOcpDelay, _SCALER_WD_TIMER_EVENT_PMIC_RX0_FW_OCP_DELAY);
    }
}

//--------------------------------------------------
// Description  : PMIC FW Ocp Delay interrupt handler
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID) using 3
{
    switch(enumEventID)
    {
        case _SCALER_WD_TIMER_EVENT_PMIC_RX0_FW_OCP_DELAY:

            // ====================================================
            // OCP Shutdown Judgment
            // ====================================================

            // Compare OCP Trigger Level with Vbus current in "ADC Ideal Data" Form
            if(ScalerTypeCPowerRx0CorrectionToIdealData_WDINT(ScalerTypeCPowerGetAdcOutput_WDINT(_TYPE_C_UFP_IMON)) >= GET_PMIC_FW_OCP_CURRENT(GET_PMIC_FW_OCP_PROTECT_LEVEL()))
            {
                // Disable Pmic
                ScalerTypeCPmicRx0Setting_WDINT(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

                // Set OCP Event
                ScalerTypeCRx0PdSetSystemEvent_WDINT(_PD_SYS_EVENT_POWER_OCP);
            }
            else
            {
                // Disable INT & Clear INT Flag
                ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_IMON, _DISABLE);

                // Set to lowest OCP level
                ScalerTypeCPowerRangeIntSetting_WDINT(_TYPE_C_UFP_IMON, 0xFFFF, GET_PMIC_FW_OCP_CURRENT(0), _TYPE_C_ADC_WITHIN_RANGE);

                // Clear flag and enable INT
                ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_IMON, _ENABLE);

                // Clear Trigger Level
                SET_PMIC_FW_OCP_PROTECT_LEVEL(0);
            }

            break;

        default:

            break;
    }
}

#if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX0 PMIC Safety Protect Tracking
// Input Value  : None
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0TrackingSafetyProtect(void)
{
    if(GET_PMIC_SAFETY_PROTECT_TRIGGER() == _FALSE)
    {
        WORD usCurrentValue = 0x0000;
        WORD usOcpDelay = 0x0000;

        DebugMessageTypeC("Pmic Safety Protect Tracking", 0x00);

        // Translate Current of 10-Bit_ADC to 10mA/bit
        usCurrentValue = ((WORD)((((DWORD)ScalerTypeCPowerRx0CorrectionToIdealData(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_IMON))) * _TYPE_C_ADC_MAX_CURRENT) / 1024));

        // Debounce when current > OCP threshold
        if(usCurrentValue >= GET_PMIC_SAFETY_CURRENT_VALUE())
        {
            ScalerTimerDelayXms(2);

            // Read again after 10-Bit_ADC stable
            usCurrentValue = ((WORD)((((DWORD)ScalerTypeCPowerRx0CorrectionToIdealData(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_IMON))) * _TYPE_C_ADC_MAX_CURRENT) / 1024));
        }

        // OCP judgment
        if(usCurrentValue >= GET_PMIC_SAFETY_CURRENT_VALUE())
        {
            // Start Protection Delay
            usOcpDelay = MAXOF(_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN, 10);
            ScalerTimerReactiveTimerEvent(usOcpDelay, _SCALER_TIMER_EVENT_PMIC_SAFETY_PROTECT);

            DebugMessageTypeC("Pmic: Safety Protect Trigger", 0x00);

            SET_PMIC_SAFETY_PROTECT_TRIGGER();

            // Already in Safety Protect State
            return 0x00;
        }

        // Set 10ms Timer Event for Tracking Safety Protect
        return 0x01;
    }

    // Already in Safety Protect State
    return 0x00;
}

//--------------------------------------------------
// Description  : RX0 PMIC Safety Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0SafetyProtect(void)
{
    WORD usCurrentValue = 0x0000;

    if(GET_PMIC_SAFETY_PROTECT_TRIGGER() == _TRUE)
    {
        // Translate Current of 10-Bit_ADC to 10mA/bit
        usCurrentValue = ((WORD)((((DWORD)ScalerTypeCPowerRx0CorrectionToIdealData(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_IMON))) * _TYPE_C_ADC_MAX_CURRENT) / 1024));

        // Debounce when current > OCP threshold
        if(usCurrentValue >= GET_PMIC_SAFETY_CURRENT_VALUE())
        {
            ScalerTimerDelayXms(2);

            // Read again after 10-Bit_ADC stable
            usCurrentValue = ((WORD)((((DWORD)ScalerTypeCPowerRx0CorrectionToIdealData(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_IMON))) * _TYPE_C_ADC_MAX_CURRENT) / 1024));
        }

        // OCP judgment
        if(usCurrentValue >= GET_PMIC_SAFETY_CURRENT_VALUE())
        {
            DebugMessageTypeC("Pmic turn-off for Safety Protect", 0x00);

            // Disable PMIC
            ScalerTypeCPmicRx0Setting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

            // Set OCP Event
            ScalerTypeCRx0PdSetSystemEvent(_PD_SYS_EVENT_POWER_OCP);
        }
        else
        {
            DebugMessageTypeC("Pmic Safety Protect Cancel!", 0x00);

            CLR_PMIC_SAFETY_PROTECT_TRIGGER();

            ScalerTimerReactiveTimerEvent(10, _SCALER_TIMER_EVENT_PMIC_TRACKING);
        }
    }
}
#endif // End of #if(_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT == _ON)

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
//--------------------------------------------------
// Description  : RX0 PMIC Polling Ocp Tracking
// Input Value  : None
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0TrackingPollingOcp(void)
{
    if(GET_PMIC_OCP_PROTECT_TRIGGER() == _FALSE)
    {
        WORD usCurrentValue = 0x0000;
        WORD usCurrent = 0x0000;
        WORD usOcpThreshold = 0x0000;
        WORD usOcpDelay = 0x0000;

        DebugMessageTypeC("Pmic Tracking", 0x00);

        // Read current value from PMIC's ADC
        usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue();

        // Minimum Current Setting for different PDO type
        usCurrent = GET_RX0_OUTPUT_CUR();
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_CURRENT ? _TYPE_C_PMIC_MIN_CURRENT : usCurrent);

        // Calculate OCP threshold
        usOcpThreshold = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE) / 100));

        // Debounce when current > OCP threshold
        if(usCurrentValue >= usOcpThreshold)
        {
            ScalerTimerDelayXms(2);
            usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue();
        }

        // OCP judgment
        if(usCurrentValue >= usOcpThreshold)
        {
            usOcpDelay = MAXOF(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN, 10);
            ScalerTimerReactiveTimerEvent(usOcpDelay, _SCALER_TIMER_EVENT_PMIC_POLLING_OCP);
            DebugMessageTypeC("Pmic:Output Current OCP", 0x00);
            SET_PMIC_OCP_PROTECT_TRIGGER();

            // Already in Ocp Protect State
            return 0x00;
        }

        // Set 10ms Timer Event for Tracking Polling Ocp
        return 0x01;
    }

    // Already in Ocp Protect State
    return 0x00;
}

//--------------------------------------------------
// Description  : RX0 PMIC FW Ocp Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0OcpProtect(void)
{
    if(GET_PMIC_OCP_PROTECT_TRIGGER() == _TRUE)
    {
        DebugMessageTypeC("Pmic turn-off", 0x00);

        ScalerTypeCPmicRx0Setting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // Set OCP Event
        ScalerTypeCRx0PdSetSystemEvent(_PD_SYS_EVENT_POWER_OCP);
    }
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
//--------------------------------------------------
// Description  : RX0 PMIC Voltage Compensation Tracking
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0TrackingVoltageCompensation(void)
{
    BYTE ucResult = _SUCCESS;
    WORD usCurrent = 0x0000;
    WORD usCurrentValue = 0x0000;
    WORD usVoltageValue = 0x0000;
    WORD usSchmittVIL = 0x0000;
    WORD usSchmittVIH = 0x0000;

    // Translate Current of 10-Bit_ADC to 10mA/bit
    usCurrentValue = ((WORD)((((DWORD)ScalerTypeCPowerRx0CorrectionToIdealData(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_IMON))) * _TYPE_C_ADC_MAX_CURRENT) / 1024));

    // Calculate VIL of compesation voltage (10mV)
    usSchmittVIL = GET_RX0_OUTPUT_VOL() + ((usCurrentValue * 10) / _VOLTAGE_COMPESATION_CURRENT_UNIT);

    // Calculate VIH of compesation voltage (10mV)
    usSchmittVIH = GET_RX0_OUTPUT_VOL() + (((usCurrentValue + 5) * 10) / _VOLTAGE_COMPESATION_CURRENT_UNIT);

    // Minimum Current Setting for different PDO type
    usCurrent = GET_RX0_OUTPUT_CUR();
    usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_CURRENT ? _TYPE_C_PMIC_MIN_CURRENT : usCurrent);

    // Translate Voltage of 10-Bit_ADC to 10mV/bit
    usVoltageValue = ((WORD)(((DWORD)ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) * _TYPE_C_ADC_MAX_VOLTAGE) / 1024));

    // Voltage compensation detect
    if(usVoltageValue < usSchmittVIL)
    {
        DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
        DebugMessageTypeC("0.Pmic:Voltage Change", usSchmittVIL);

        if(ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(_TYPE_C_PMIC_DIRECTION_SRC, usSchmittVIL, usCurrent) == _TYPE_C_PMIC_CONTROL_FAIL)
        {
            ucResult = _FAIL;
        }
    }
    else if(usVoltageValue > usSchmittVIH)
    {
        DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
        DebugMessageTypeC("0.Pmic:Voltage Change", usSchmittVIH);

        if(ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(_TYPE_C_PMIC_DIRECTION_SRC, usSchmittVIH, usCurrent) == _TYPE_C_PMIC_CONTROL_FAIL)
        {
            ucResult = _FAIL;
        }
    }

    return ucResult;
}
#endif // End of #if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
//--------------------------------------------------
// Description  : RX0 PMIC INT Pin Tracking
// Input Value  : None
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0TrackingIntPin(void)
{
    // Check GPIO status
    if(PCB_PMIC_INTERRUPT_DETECT() == _PMIC_INTERRUPT_ON)
    {
        ScalerTypeCPmicRx0Setting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        DebugMessageTypeC("Pmic GPIO interrupt!", PCB_PMIC_INTERRUPT_DETECT());

#if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
        // Set Recovery
        SET_TYPE_C_ERROR_RECOVERY();
#else
        // Reset PMIC
        ExternalDeviceInterfaceTypeCPmicUnattachReset();

        // Send Hard reset
        ScalerTypeCRx0PdSendHardRst();
#endif
    }

    // Set 200ms Timer Event for Int Pin Tracking
    return 0x04;
}
#endif // End of #if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX0 PMIC OVP interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0OvpUvpIntHandler_EXINT0(void) using 1
{
    // Check Comparator INT Flag
    if(ScalerTypeCPowerRangeIntCheck_EXINT0(_TYPE_C_UFP_VMON) == _FALSE)
    {
        return;
    }

    // Disable PMIC
    ScalerTypeCPmicRx0Setting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

    // Set OVP Event
    ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OVP);
}
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
