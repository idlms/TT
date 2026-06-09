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
// ID Code      : TypeC_Pmic_ONSEMI_NCP81239.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC NCP81239
//--------------------------------------------------
#define _NCP81239_SUBADDR_LENGTH            0x01
#define _NCP81239_CTRL_REG00                0x00
#define _NCP81239_CTRL_REG01                0x01
#define _NCP81239_CTRL_REG02                0x02
#define _NCP81239_CTRL_REG03                0x03
#define _NCP81239_CTRL_REG04                0x04
#define _NCP81239_CTRL_REG05                0x05
#define _NCP81239_CTRL_REG06                0x06
#define _NCP81239_CTRL_REG07                0x07
#define _NCP81239_CTRL_REG08                0x08
#define _NCP81239_CTRL_REG09                0x09
#define _NCP81239_CTRL_REG0A                0x0A
#define _NCP81239_CTRL_REG10                0x10
#define _NCP81239_CTRL_REG11                0x11
#define _NCP81239_CTRL_REG12                0x12
#define _NCP81239_CTRL_REG13                0x13
#define _NCP81239_CTRL_REG14                0x14
#define _NCP81239_CTRL_REG15                0x15

//--------------------------------------------------
// Definitions of Pmic NCP81239 Control
//--------------------------------------------------
#define _TUNE_RISE                          0
#define _TUNE_FALL                          1
#define _PMIC_SOURCE                        1
#define _PMIC_SINK                          0

//--------------------------------------------------
// NCP81239 Initial Setting
//--------------------------------------------------
#define _SLEW_RATE                          0x00
#define _PWM_FREQ                           0x00
#define _OCP_CLIM_POS                       0x00
#define _OCP_CLIM_NEG                       0x00
#define _INT_MASK_CS_CLIND                  0x00
#define _INT_MASK_OVP                       0x00
#define _INT_MASK_OCP_P                     0x00
#define _INT_MASK_PG_INT                    0x00
#define _INT_MASK_TSD                       0x00
#define _INT_MASK_UVP                       0x00
#define _INT_MASK_VCHN                      0x00
#define _INT_MASK_IIC_ACK                   0x00
#define _INT_MASK_SHUT_DOWN                 0x00

//--------------------------------------------------
// Definitions of PMIC FUNCTION
//--------------------------------------------------
#define _TYPE_C_PMIC_DEBUG                  _OFF
#define _TYPE_C_PMIC_VOLTAGE_OFFSET         0  // unit: 0.1V
#define _VOLTAGE_COMPESATION_CURRENT_UNIT   50 // unit: 10mA, 0.1V / _VOLTAGE_COMPESATION_CURRENT_UNIT
#define _TYPE_C_PMIC_FW_OVP_THRESHOLD       120  // unit: %
#define _TYPE_C_PMIC_FW_OCP_THRESHOLD       125  // unit: %

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------
#define GET_PMIC_BIDIR_MODE()               (g_stPMICData.b1CR0BPmicDirection)
#define GET_PMIC_OUTPUT_ENABLE()            (PCB_PMIC_POWER_DETECT())

//--------------------------------------------------
// Macros of PMIC VOLTAGE TRACKING START
//--------------------------------------------------
#define GET_PMIC_VOL_TRACK_START()          (g_bPmicTrackingStart)
#define SET_PMIC_VOL_TRACK_START()          (g_bPmicTrackingStart = _TRUE)
#define CLR_PMIC_VOL_TRACK_START()          (g_bPmicTrackingStart = _FALSE)

#if(_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON)
//--------------------------------------------------
// Macros of PMIC FW OCP Debounce
//--------------------------------------------------
#define GET_PMIC_FW_OCP_DEBOUNCE()          (g_bPmicFwOcpDebounceFlag)
#define SET_PMIC_FW_OCP_DEBOUNCE()          (g_bPmicFwOcpDebounceFlag = _TRUE)
#define CLR_PMIC_FW_OCP_DEBOUNCE()          (g_bPmicFwOcpDebounceFlag = _FALSE)
#endif

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
//--------------------------------------------------
// Macros of PMIC FW OVP Debounce
//--------------------------------------------------
#define GET_PMIC_FW_VBUS_DECREASE()         (g_bPmicFwVbusDecreaseFlag)
#define SET_PMIC_FW_VBUS_DECREASE()         (g_bPmicFwVbusDecreaseFlag = _TRUE)
#define CLR_PMIC_FW_VBUS_DECREASE()         (g_bPmicFwVbusDecreaseFlag = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b2CR00Reserved : 2;
    BYTE b1CR00EnMask : 1;
    BYTE b1CR00EnInternal : 1;
    BYTE b4CR00Reserved : 4;

    BYTE ucCR01DacTarget;

    BYTE b2CR02SlewRate : 2;
    BYTE b6CR02Reserved : 6;

    BYTE b3CR03PwmFreq : 3;
    BYTE b1CR03Reserved : 1;
    BYTE b1CR03DacLsb : 1;
    BYTE b3CR03Reserved : 3;

    BYTE b1CR04Pfet : 1;
    BYTE b1CR04Cfet : 1;
    BYTE b3CR04Reserved : 3;
    BYTE b1CR04Cs2DisCharge : 1;
    BYTE b2CR04Reserved : 2;

    BYTE b2CR05OcpClimPos : 2;
    BYTE b2CR05Reserved1 : 2;
    BYTE b2CR05OcpClimNeg : 2;
    BYTE b2CR05Reserved2 : 2;

    BYTE b2CR06Cs1Clind : 2;
    BYTE b2CR06Cs2Clind : 2;
    BYTE b4CR06Reserved : 4;

    BYTE b3CR07LoGmAmpSetting : 3;
    BYTE b1CR07GmManual : 1;
    BYTE b3CR07HiGmAmpSetting : 3;
    BYTE b1CR07GmAmpConfig : 1;

    BYTE b2CR08AmuxTrigger : 2;
    BYTE b3CR08AmuxSel : 3;
    BYTE b1CR08DisAdc : 1;
    BYTE b2CR08Reserved : 2;

    BYTE b1CR09IntMaskCsClind : 1;
    BYTE b1CR09IntMaskOvp : 1;
    BYTE b1CR09IntMaskOcpP : 1;
    BYTE b1CR09IntMaskPgInt : 1;
    BYTE b1CR09IntMaskTsd : 1;
    BYTE b1CR09IntMaskUvp : 1;
    BYTE b1CR09IntMaskVchn : 1;
    BYTE b1CR09IntMaskI2cAck : 1;

    BYTE b1CR0AIntMaskShutDown : 1;
    BYTE b7CR0AReserved : 7;

    BYTE b1CR0BPmicDirection : 1;
    BYTE b7CR0BReserved : 7;
    BYTE ucCR0CReserved;
    BYTE ucCR0DReserved;
    BYTE ucCR0EReserved;
    BYTE ucCR0FReserved;

    BYTE ucCR10VfbValue;
    BYTE ucCR11VinValue;
    BYTE ucCR12Cs2Value;
    BYTE ucCR13Cs1Value;

    BYTE b1CR14IntCsClindFlag : 1;
    BYTE b1CR14IntOvpFlag : 1;
    BYTE b1CR14IntOcpPFlag : 1;
    BYTE b1CR14IntPgIntFlag : 1;
    BYTE b1CR14IntTsdFlag : 1;
    BYTE b1CR14IntUvpFlag : 1;
    BYTE b1CR14IntVchnFlag : 1;
    BYTE b1CR14IntI2cAckFlag : 1;

    BYTE b1CR15IntShutDownFlag : 1;
    BYTE b7CR15Reserved : 7;
} StructNCP81239RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructNCP81239RegisterMap code g_stPmicInitialData =
{
    0x00,                              // Reserved
    0x00,                              // Hardware enable selected
    0x00,                              // Software control disable
    0x00,                              // Reserved

    0x32,                              // VBUS setting is 5V

    _SLEW_RATE,                        // Slwe rate by define
    0x00,                              // Reserved

    _PWM_FREQ,                         // by define
    0x00,                              // PWM freq Reserved
    0x00,                              // DAC resolution is 10mV
    0x00,                              // Reserved

    0x00,                              // PFET is disable
    0x00,                              // CFET is disable
    0x00,                              // Reserved
    0x00,                              // CS2 discharge is disable
    0x00,                              // Reserved

    _OCP_CLIM_POS,                     // internal positive current limit by define
    0x00,                              // Reserved
    _OCP_CLIM_NEG,                     // internal negative current limit by define
    0x00,                              // Reserved

    0x00,                              // CS1 positive current limit
    0x00,                              // CS2 positive current limit
    0x00,                              // Reserved

    0x01,                              // Low Amp GM value
    0x01,                              // register of amp gm settings
    0x05,                              // High Amp GM value
    0x00,                              // register of amp gm config

    0x00,                              // ADC Trigger
    0x00,                              // ADC MUX select
    0x00,                              // ADC is enable
    0x00,                              // Reserved

    _INT_MASK_CS_CLIND,                // cs_clind int flag enable by define
    _INT_MASK_OVP,                     // OVP int flag enable by define
    _INT_MASK_OCP_P,                   // OCP_P int flag enable by define
    _INT_MASK_PG_INT,                  // PG int flag enable by define
    _INT_MASK_TSD,                     // TSD int flag enable by define
    _INT_MASK_UVP,                     // UVP int flag enable by define
    _INT_MASK_VCHN,                    // VCHN int flag enable by define
    _INT_MASK_IIC_ACK,                 // IIC_ACK int flag enable by define

    _INT_MASK_SHUT_DOWN,               // SHUT_DOWN int flag enable by define
    0x00,                              // Reserved

    _PMIC_SINK,                        // Source/Sink status
    0x00,                              // Reserved
    0x00,                              // Reserved
    0x00,                              // Reserved
    0x00,                              // Reserved
    0x00,                              // Reserved

    0x00,                              // Vfb value(Read Only)
    0x00,                              // Vin value(Read Only)
    0x00,                              // CS2 value(Read Only)
    0x00,                              // CS1 value(Read Only)

    0x00,                              // CsClind flag(Read Only)
    0x00,                              // OVP flag(Read Only)
    0x00,                              // OCP_P flag(Read Only)
    0x00,                              // PG flag(Read Only)
    0x00,                              // TSD flag(Read Only)
    0x00,                              // UVP flag(Read Only)
    0x00,                              // VCHN flag(Read Only)
    0x00,                              // IIC_ACK flag(Read Only)

    0x00,                              // SHUT_DOWN flag(Read Only)
    0x00,                              // Reserved
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructNCP81239RegisterMap g_stPMICData;
bit g_bPmicTrackingStart = _FALSE;
#if(_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON)
bit g_bPmicFwOcpDebounceFlag = _FALSE;
#endif
#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
bit g_bPmicFwVbusDecreaseFlag = _FALSE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void DeviceInterfaceTypeCPmicInitial(BYTE ucSlaveAddr);
void DeviceInterfaceTypeCPmicReset(BYTE ucSlaveAddr);
bit DeviceInterfaceTypeCPmicSetting(BYTE ucSlaveAddr, bit bAction, bit bPowerDirection, WORD usVoltage, WORD usCurrent);
BYTE DeviceInterfaceTypeCPmicSetting_EXINT0(BYTE ucSlaveAddr, bit bAction, bit bPowerDirection, WORD usVoltage, WORD usCurrent);
BYTE DeviceInterfaceTypeCPmicSetting_WDINT(BYTE ucSlaveAddr, bit bAction, bit bPowerDirection, WORD usVoltage, WORD usCurrent);
bit DeviceInterfaceTypeCPmicVbusDischarge(BYTE ucSlaveAddr, bit bEn);
BYTE DeviceInterfaceTypeCPmicVbusDischarge_WDINT(BYTE ucSlaveAddr, bit bEn);
#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
bit DeviceInterfaceTypeCPmicTrackingStart(BYTE ucSlaveAddr);
bit DeviceInterfaceTypeCPmicTracking(BYTE ucSlaveAddr);
#if(_TYPE_C_PMIC_DEBUG == _ON)
bit DeviceInterfaceTypeCPmicStatus(BYTE ucSlaveAddr);
#endif
#endif
#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
void DeviceInterfaceTypeCPmicOvpIntHandler_EXINT0(BYTE ucSlaveAddr);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void DeviceInterfaceTypeCPmicInitial(BYTE ucSlaveAddr)
{
    ucSlaveAddr = ucSlaveAddr;

    g_stPMICData = g_stPmicInitialData;
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void DeviceInterfaceTypeCPmicReset(BYTE ucSlaveAddr)
{
    ucSlaveAddr = ucSlaveAddr;

    PCB_PMIC_POWER(_POWER_OFF);

    CLR_PMIC_VOL_TRACK_START();

#if(_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON)
    CLR_PMIC_FW_OCP_DEBOUNCE();
#endif

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
    CLR_PMIC_FW_VBUS_DECREASE();

    // Disable INT
    ScalerTypeCPowerRangeIntControl(_TYPEC_UFP_VMON, _DISABLE);
#endif
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 400 (Unit = 50mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit DeviceInterfaceTypeCPmicSetting(BYTE ucSlaveAddr, bit bAction, bit bPowerDirection, WORD usVoltage, WORD usCurrent)
{
    usCurrent = usCurrent;

    if(usVoltage > 400)
    {
        return _FAIL;
    }

    if(bAction == _ON)
    {
        if(bPowerDirection == _PMIC_SOURCE)
        {
            g_stPMICData.b1CR0BPmicDirection = _PMIC_SOURCE;
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            g_stPMICData.b1CR0BPmicDirection = _PMIC_SINK;
            PCB_PMIC_POWER(_POWER_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
            return _SUCCESS;
        }

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        if((((BYTE)((usVoltage / 2) + _TYPE_C_PMIC_VOLTAGE_OFFSET)) < g_stPMICData.ucCR01DacTarget) && (PCB_PMIC_POWER_DETECT() == _POWER_ON))
        {
            SET_PMIC_FW_VBUS_DECREASE();
        }
        else
        {
            CLR_PMIC_FW_VBUS_DECREASE();
        }
#endif

        // Set VBUS Voltage
        g_stPMICData.ucCR01DacTarget = (BYTE)((usVoltage / 2) + _TYPE_C_PMIC_VOLTAGE_OFFSET);

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        // Translate Voltage to SARADC Value
        usVoltage = (((DWORD)(usVoltage)) * 5 * 1024 / 2400);

        // Set Threshold for OVP
        usVoltage = ((((DWORD)(usVoltage)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100);

        if(usVoltage >= 0x3FF)
        {
            usVoltage = 0x3FE;
        }

        // Disable INT
        ScalerTypeCPowerRangeIntControl(_TYPEC_UFP_VMON, _DISABLE);

        // Set OVP range
        ScalerTypeCPowerRangeIntSetting(_TYPEC_UFP_VMON, usVoltage, 0x0000, _TYPEC_ADC_WITHOUT_RANGE);

        if(GET_PMIC_FW_VBUS_DECREASE() == _FALSE)
        {
            // Clear flag and enable INT
            ScalerTypeCPowerRangeIntControl(_TYPEC_UFP_VMON, _ENABLE);
        }
#endif

        if(PCB_PMIC_POWER_DETECT() == _POWER_OFF)
        {
#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
            if(GET_PMIC_BIDIR_MODE() == _PMIC_SOURCE)
            {
                SET_PMIC_VOL_TRACK_START();
            }
#endif

            if(ScalerTypeCPmicIICWrite(ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _FAIL;
            }

            PCB_PMIC_POWER(_POWER_ON);
        }
        else
        {
            if(ScalerTypeCPmicIICWrite(ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _FAIL;
            }
        }
    }
    else
    {
#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        // Disable INT
        ScalerTypeCPowerRangeIntControl(_TYPEC_UFP_VMON, _DISABLE);
#endif
        PCB_PMIC_POWER(_POWER_OFF);
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 400 (Unit = 50mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE DeviceInterfaceTypeCPmicSetting_EXINT0(BYTE ucSlaveAddr, bit bAction, bit bPowerDirection, WORD usVoltage, WORD usCurrent) using 1
{
    usCurrent = usCurrent;

    if(usVoltage > 400)
    {
        return _FAIL;
    }

    if(bAction == _ON)
    {
        if(bPowerDirection == _PMIC_SOURCE)
        {
            g_stPMICData.b1CR0BPmicDirection = _PMIC_SOURCE;
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            g_stPMICData.b1CR0BPmicDirection = _PMIC_SINK;
            PCB_PMIC_POWER(_POWER_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
            return _SUCCESS;
        }
#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        if((((BYTE)((usVoltage / 2) + _TYPE_C_PMIC_VOLTAGE_OFFSET)) < g_stPMICData.ucCR01DacTarget) && (PCB_PMIC_POWER_DETECT() == _POWER_ON))
        {
            SET_PMIC_FW_VBUS_DECREASE();
        }
        else
        {
            CLR_PMIC_FW_VBUS_DECREASE();
        }
#endif
        // Set VBUS Voltage
        g_stPMICData.ucCR01DacTarget = (BYTE)((usVoltage / 2) + _TYPE_C_PMIC_VOLTAGE_OFFSET);

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        // Translate Voltage to SARADC Value
        usVoltage = (((DWORD)(usVoltage)) * 5 * 1024 / 2400);

        // Set Threshold for OVP
        usVoltage = ((((DWORD)(usVoltage)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100);

        if(usVoltage >= 0x3FF)
        {
            usVoltage = 0x3FE;
        }

        // Disable INT
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPEC_UFP_VMON, _DISABLE);

        // Set OVP range
        ScalerTypeCPowerRangeIntSetting_EXINT0(_TYPEC_UFP_VMON, usVoltage, 0x0000, _TYPEC_ADC_WITHOUT_RANGE);

        if(GET_PMIC_FW_VBUS_DECREASE() == _FALSE)
        {
            // Clear flag and enable INT
            ScalerTypeCPowerRangeIntControl_EXINT0(_TYPEC_UFP_VMON, _ENABLE);
        }
#endif

        if(PCB_PMIC_POWER_DETECT() == _POWER_OFF)
        {
#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
            if(GET_PMIC_BIDIR_MODE() == _PMIC_SOURCE)
            {
                SET_PMIC_VOL_TRACK_START();
            }
#endif

            if(ScalerTypeCPmicIICWrite_EXINT0(ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _FAIL;
            }

            PCB_PMIC_POWER(_POWER_ON);
        }
        else
        {
            if(ScalerTypeCPmicIICWrite_EXINT0(ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _FAIL;
            }
        }
    }
    else
    {
#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        // Disable INT
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPEC_UFP_VMON, _DISABLE);
#endif
        PCB_PMIC_POWER(_POWER_OFF);
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 400 (Unit = 50mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE DeviceInterfaceTypeCPmicSetting_WDINT(BYTE ucSlaveAddr, bit bAction, bit bPowerDirection, WORD usVoltage, WORD usCurrent) using 3
{
    usCurrent = usCurrent;

    if(usVoltage > 400)
    {
        return _FAIL;
    }

    if(bAction == _ON)
    {
        if(bPowerDirection == _PMIC_SOURCE)
        {
            g_stPMICData.b1CR0BPmicDirection = _PMIC_SOURCE;
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            g_stPMICData.b1CR0BPmicDirection = _PMIC_SINK;
            PCB_PMIC_POWER(_POWER_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
            return _SUCCESS;
        }

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        if((((BYTE)((usVoltage / 2) + _TYPE_C_PMIC_VOLTAGE_OFFSET)) < g_stPMICData.ucCR01DacTarget) && (PCB_PMIC_POWER_DETECT() == _POWER_ON))
        {
            SET_PMIC_FW_VBUS_DECREASE();
        }
        else
        {
            CLR_PMIC_FW_VBUS_DECREASE();
        }
#endif

        // Set VBUS Voltage
        g_stPMICData.ucCR01DacTarget = (BYTE)((usVoltage / 2) + _TYPE_C_PMIC_VOLTAGE_OFFSET);

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        // Translate Voltage to SARADC Value
        usVoltage = (((DWORD)(usVoltage)) * 5 * 1024 / 2400);

        // Set Threshold for OVP
        usVoltage = ((((DWORD)(usVoltage)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100);

        if(usVoltage >= 0x3FF)
        {
            usVoltage = 0x3FE;
        }

        // Disable INT
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPEC_UFP_VMON, _DISABLE);

        // Set OVP range
        ScalerTypeCPowerRangeIntSetting_WDINT(_TYPEC_UFP_VMON, usVoltage, 0x0000, _TYPEC_ADC_WITHOUT_RANGE);

        if(GET_PMIC_FW_VBUS_DECREASE() == _FALSE)
        {
            // Clear flag and enable INT
            ScalerTypeCPowerRangeIntControl_WDINT(_TYPEC_UFP_VMON, _ENABLE);
        }
#endif

        if(PCB_PMIC_POWER_DETECT() == _POWER_OFF)
        {
#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
            if(GET_PMIC_BIDIR_MODE() == _PMIC_SOURCE)
            {
                SET_PMIC_VOL_TRACK_START();
            }
#endif

            if(ScalerTypeCPmicIICWrite_WDINT(ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _FAIL;
            }

            PCB_PMIC_POWER(_POWER_ON);
        }
        else
        {
            if(ScalerTypeCPmicIICWrite_WDINT(ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _FAIL;
            }
        }
    }
    else
    {
#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
        // Disable INT
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPEC_UFP_VMON, _DISABLE);
#endif
        PCB_PMIC_POWER(_POWER_OFF);
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit DeviceInterfaceTypeCPmicVbusDischarge(BYTE ucSlaveAddr, bit bEn)
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1CR04Pfet = bEn;

    // Disable Pmic VBUS Discharge
    return ScalerTypeCPmicIICWrite(ucSlaveAddr, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG04);
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE DeviceInterfaceTypeCPmicVbusDischarge_WDINT(BYTE ucSlaveAddr, bit bEn) using 3
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1CR04Pfet = bEn;

    // Disable Pmic VBUS Discharge
    return ScalerTypeCPmicIICWrite_WDINT(ucSlaveAddr, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG04);
}

#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC VBUS Check
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit DeviceInterfaceTypeCPmicTrackingStart(BYTE ucSlaveAddr)
{
    ucSlaveAddr = ucSlaveAddr;

#if(_TYPE_C_PMIC_DEBUG == _ON)
    DeviceInterfaceTypeCPmicStatus(ucSlaveAddr);
#endif

    // If change VBUS just recently, reactive timer event.
    if(GET_PMIC_VOL_TRACK_START() == _TRUE)
    {
        CLR_PMIC_VOL_TRACK_START();
#if(_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON)
        CLR_PMIC_FW_OCP_DEBOUNCE();
#endif
        ScalerTimerReactiveTimerEvent(100, _SCALER_TIMER_EVENT_PMIC_VOLTGAE_CHECK);
        return _SUCCESS;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Check
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit DeviceInterfaceTypeCPmicTracking(BYTE ucSlaveAddr)
{
    WORD usCurrentValue = 0x0000;
    WORD usTemp1 = 0x0000;
    WORD usTemp2 = 0x0000;

    ucSlaveAddr = ucSlaveAddr;

#if(_TYPE_C_PMIC_DEBUG == _ON)
    DeviceInterfaceTypeCPmicStatus(ucSlaveAddr);
#endif

    // If VBUS is source output, then keep tracking
    if((GET_PMIC_BIDIR_MODE() == _PMIC_SOURCE) && (GET_PMIC_OUTPUT_ENABLE() == _ON))
    {
        // Only source mode need to check VBUS
        ScalerTimerReactiveTimerEvent(220, _SCALER_TIMER_EVENT_PMIC_VOLTGAE_CHECK);
    }
    else
    {
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PMIC_VOLTGAE_CHECK);
        return _SUCCESS;
    }

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
    if(GET_PMIC_FW_VBUS_DECREASE() == _TRUE)
    {
        // Clear flag and enable INT
        ScalerTypeCPowerRangeIntControl(_TYPEC_UFP_VMON, _ENABLE);
    }

    CLR_PMIC_FW_VBUS_DECREASE();
#endif

#if((_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON) || (_TYPE_C_PMIC_VOLTAGE_COMPESATION == _ON))
    // Translate Current of 10bSARADC to 10mA/bit
    usCurrentValue = ((WORD)((((DWORD)ScalerTypeCPowerGetAdcOutput(_TYPEC_UFP_IMON)) * 8 * 1000) / 1024 / 10));

#if(_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON)
    // Calculate Max current value
    usTemp1 = ((WORD)((((DWORD)GET_RX0_OUTPUT_CUR()) * _TYPE_C_PMIC_FW_OCP_THRESHOLD) / 100));

    if(GET_PMIC_FW_OCP_DEBOUNCE() == _FALSE)
    {
        if(usCurrentValue > usTemp1)
        {
            DebugMessageTypeC("0.Pmic:OCP Fitst time", usCurrentValue);

            // Calculate current to SARADC
            usTemp1 = ((WORD)((((DWORD)usTemp1) * 1024 * 10) / 1000 / 8));

            // Disable IMON int
            ScalerTypeCPowerRangeIntControl(_TYPEC_UFP_IMON, _DISABLE);

            // Set Range to check if current will be lower than max currnet value
            ScalerTypeCPowerRangeIntSetting(_TYPEC_UFP_IMON, 0xFFFF, usTemp1, _TYPEC_ADC_WITHOUT_RANGE);

            // Clear IMON flag
            ScalerTypeCPowerClearAdcIntFlag(_TYPEC_UFP_IMON);

            // Set debounce flag
            SET_PMIC_FW_OCP_DEBOUNCE();

            return _SUCCESS;
        }
    }
    else
    {
        // If OCP don't release after debounce time, then disable Pmic
        if(ScalerTypeCPowerGetAdcIntFlag(_TYPEC_UFP_IMON) == _FALSE)
        {
            DebugMessageTypeC("0.Pmic:OCP Second time", usCurrentValue);

            CLR_PMIC_FW_OCP_DEBOUNCE();

            PCB_PMIC_POWER(_POWER_OFF);

            SET_TYPEC_ERROR_RECOVERY();

            return _SUCCESS;
        }
        else
        {
            CLR_PMIC_FW_OCP_DEBOUNCE();

            DebugMessageTypeC("0.Pmic:Release OCP Second time", usCurrentValue);

            if(usCurrentValue > usTemp1)
            {
                DebugMessageTypeC("0.Pmic:OCP Fitst time", usCurrentValue);

                // Calculate current to SARADC
                usTemp1 = ((WORD)((((DWORD)usTemp1) * 1024 * 10) / 1000 / 8));

                // Disable IMON int
                ScalerTypeCPowerRangeIntControl(_TYPEC_UFP_IMON, _DISABLE);

                // Set Range to check if current will be lower than max currnet value
                ScalerTypeCPowerRangeIntSetting(_TYPEC_UFP_IMON, 0xFFFF, usTemp1, _TYPEC_ADC_WITHOUT_RANGE);

                // Clear IMON flag
                ScalerTypeCPowerClearAdcIntFlag(_TYPEC_UFP_IMON);

                // Set debounce flag
                SET_PMIC_FW_OCP_DEBOUNCE();

                return _SUCCESS;
            }
        }
    }
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON)

#if(_TYPE_C_PMIC_VOLTAGE_COMPESATION == _ON)
    // Calculate compesation of voltag
    usTemp1 = (GET_RX0_OUTPUT_VOL() / 2) + (usCurrentValue / _VOLTAGE_COMPESATION_CURRENT_UNIT) + _TYPE_C_PMIC_VOLTAGE_OFFSET;

    // Schmitt 50mA for decrease VBUS
    usTemp2 = (GET_RX0_OUTPUT_VOL() / 2) + ((usCurrentValue + 5) / _VOLTAGE_COMPESATION_CURRENT_UNIT) + _TYPE_C_PMIC_VOLTAGE_OFFSET;

    if(g_stPMICData.ucCR01DacTarget < usTemp1)
    {
        g_stPMICData.ucCR01DacTarget = usTemp1;

        ScalerTimerReactiveTimerEvent(100, _SCALER_TIMER_EVENT_PMIC_VOLTGAE_CHECK);

        DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
        DebugMessageTypeC("0.Pmic:Voltage Change", usTemp1);

        if(ScalerTypeCPmicIICWrite(ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
        {
            return _FAIL;
        }
    }
    else if(g_stPMICData.ucCR01DacTarget > usTemp2)
    {
        g_stPMICData.ucCR01DacTarget = usTemp2;

        ScalerTimerReactiveTimerEvent(100, _SCALER_TIMER_EVENT_PMIC_VOLTGAE_CHECK);

        DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
        DebugMessageTypeC("0.Pmic:Voltage Change", usTemp2);

        if(ScalerTypeCPmicIICWrite(ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
        {
            return _FAIL;
        }
    }
#endif // End of #if(_TYPE_C_PMIC_VOLTAGE_COMPESATION == _ON)
#endif // End of #if((_TYPE_C_PMIC_FW_OCP_SUPPORT == _ON) || (_TYPE_C_PMIC_VOLTAGE_COMPESATION == _ON))

    return _SUCCESS;
}

#if(_TYPE_C_PMIC_DEBUG == _ON)
//--------------------------------------------------
// Description  : PMIC Status
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit DeviceInterfaceTypeCPmicStatus(BYTE ucSlaveAddr)
{
    BYTE ucResult = 0;

    ucResult = ScalerTypeCPmicIICRead(ucSlaveAddr, _NCP81239_CTRL_REG10, _NCP81239_SUBADDR_LENGTH, 6, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG10);

    DebugMessageTypeC("0.Pmic:VFB Value", g_stPMICData.ucCR10VfbValue);
    DebugMessageTypeC("0.Pmic:Vin Value", g_stPMICData.ucCR11VinValue);
    DebugMessageTypeC("0.Pmic:CS2 Value", g_stPMICData.ucCR12Cs2Value);
    DebugMessageTypeC("0.Pmic:CS1 Value", g_stPMICData.ucCR13Cs1Value);
    DebugMessageTypeC("0.Pmic:Cs Clind Flag", g_stPMICData.b1CR14IntCsClindFlag);
    DebugMessageTypeC("0.Pmic:VBUS OVP Flag", g_stPMICData.b1CR14IntOvpFlag);
    DebugMessageTypeC("0.Pmic:OCP_P Flag", g_stPMICData.b1CR14IntOcpPFlag);
    DebugMessageTypeC("0.Pmic:Power Good Flag", g_stPMICData.b1CR14IntPgIntFlag);
    DebugMessageTypeC("0.Pmic:Thermal Sensor Flag", g_stPMICData.b1CR14IntTsdFlag);
    DebugMessageTypeC("0.Pmic:VBUS UVP Flag", g_stPMICData.b1CR14IntUvpFlag);
    DebugMessageTypeC("0.Pmic:Vchn Flag", g_stPMICData.b1CR14IntVchnFlag);
    DebugMessageTypeC("0.Pmic:IIC ACK Flag", g_stPMICData.b1CR14IntI2cAckFlag);
    DebugMessageTypeC("0.Pmic:Shut Down Flag", g_stPMICData.b1CR15IntShutDownFlag);

    return ucResult;
}
#endif // End of #if(_TYPE_C_PMIC_DEBUG == _ON)
#endif // End of #if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)

#if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Status
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
void DeviceInterfaceTypeCPmicOvpIntHandler_EXINT0(BYTE ucSlaveAddr) using 1
{
    ucSlaveAddr = ucSlaveAddr;

    if(ScalerTypeCPowerOvpIntProcess_EXINT0() == _TRUE)
    {
        // Disable Pmic
        PCB_PMIC_POWER(_POWER_OFF);
    }
}
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)

