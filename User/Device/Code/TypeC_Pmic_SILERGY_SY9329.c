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
// ID Code      : TypeC_Pmic_SILERGY_SY9329.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_SY9329)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC SY9329
//--------------------------------------------------
#define _SY9329_SUBADDR_LENGTH              0x01
#define _SY9329_CTRL_REG1                   0x00
#define _SY9329_CTRL_REG2                   0x01
#define _SY9329_PROTECT_REG1                0x02
#define _SY9329_PROTECT_REG2                0x03
#define _SY9329_STATE_REG                   0x04
#define _SY9329_INT_REG                     0x05
#define _SY9329_BAT_VALUE_REG               0x06
#define _SY9329_VBUS_VALUE_REG              0x07
#define _SY9329_CURRENT_VALUE_REG           0x08

//--------------------------------------------------
// Definitions of Voltage and Current
//--------------------------------------------------
#define _VBUS_VOLTAGE_5V                    100
#define _VBUS_VOLTAGE_7V                    140
#define _VBUS_VOLTAGE_9V                    180
#define _VBUS_VOLTAGE_12V                   240
#define _VBUS_VOLTAGE_15V                   300
#define _VBUS_VOLTAGE_20V                   400

//--------------------------------------------------
// Definitions of Pmic SY9329 Control
//--------------------------------------------------
#define _TUNE_RISE                          0
#define _TUNE_FALL                          1
#define _PMIC_SOURCE                        0
#define _PMIC_SINK                          1

//--------------------------------------------------
// Definitions of PMIC DEBUG FUNCTION
//--------------------------------------------------
#define _TYPE_C_PMIC_DEBUG                   _OFF

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------
#define GET_PMIC_BIDIR_MODE()               (g_stPMICData.b1BiDirSetting)
#define GET_PMIC_OUTPUT_ENABLE()            (g_stPMICData.b1PMICEnable)

//--------------------------------------------------
// Macros of PMIC VOLTAGE TRACKING START
//--------------------------------------------------
#define GET_PMIC_VOL_TRACK_START()          (g_bPmicTrackingStart)
#define SET_PMIC_VOL_TRACK_START()          (g_bPmicTrackingStart = _TRUE)
#define CLR_PMIC_VOL_TRACK_START()          (g_bPmicTrackingStart = _FALSE)

//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _LOW_BAT_VOLTAGE_SETTING                0x00
#define _SWITCH_FREQ                            0x01
#define _VBUS_OVP_SETTING                       0x02
#define _VBUS_UVP_SETTING                       0x02
#define _LOCP_SETTING                           0x00
#define _LOCP_MODE                              0x00
#define _VBUS_UVP_MODE                          0x00
#define _OTP_MODE                               0x00


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1CR1Reserved : 1;
    BYTE b1VBUSDischarge : 1;
    BYTE b1ADCMode : 1;
    BYTE b1ADCEnable : 1;
    BYTE b3LowBATVoltageSetting : 3;
    BYTE b1PMICEnable : 1;

    BYTE b3VBUSAdjust : 3;
    BYTE b3VBUSSetting : 3;
    BYTE b2SwitchFreq : 2;

    BYTE b1PS1Reserved : 1;
    BYTE b2UVPSetting : 2;
    BYTE b2OVPSetting : 2;
    BYTE b3VOCPSetting : 3;

    BYTE b2PS2Reserved : 2;
    BYTE b1BiDirSetting : 1;
    BYTE b1OTPMode : 1;
    BYTE b1UVPMode : 1;
    BYTE b1LOCPMode : 1;
    BYTE b2LOCPSetting : 2;

    BYTE b5SRReserved : 5;
    BYTE b1BATStatus : 1;
    BYTE b1BATVBUSRelation : 1;
    BYTE b1PowerGoodState : 1;

    BYTE b3IRReserved : 3;
    BYTE b1OTPFlag : 1;
    BYTE b1UVPFlag : 1;
    BYTE b1LOCPFlag : 1;
    BYTE b1VOCPFlag : 1;
    BYTE b1ADCReady : 1;

    BYTE ucBATValue;
    BYTE ucVBUSValue;
    BYTE ucVBUSCurrentValue;
} StructSY9329RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructSY9329RegisterMap code g_stPmicInitialData =
{
    0x00,                              // Reserved
    0x01,                              // Discharge Disable
    0x00,                              // ADC Mode select single detect mode
    0x00,                              // ADC Disable
    _LOW_BAT_VOLTAGE_SETTING,          // Low Battery setting by define
    0x00,                              // Regulator Disable

    0x02,                              // VBUS Adjust 0%
    0x00,                              // VBUS Output 5V
    _SWITCH_FREQ,                      // Switching Freq by define

    0x00,                              // Reserved
    _VBUS_UVP_SETTING,                 // UVP Threshold by define
    _VBUS_OVP_SETTING,                 // OVP Threshold by define
    0x03,                              // OCP 2.5A

    0x00,                              // Reserved
    0x00,                              // Direction is source mode
    _OTP_MODE,                         // OTP mode by define
    _VBUS_UVP_MODE,                    // UVP mode by define
    _LOCP_MODE,                        // LOCP mode by define
    _LOCP_SETTING,                     // LOCP by define

    0x00,                              // Reserved
    0x00,                              // BAT Power status (Read Only)
    0x00,                              // BAT/VBUS relation (Read Only)
    0x00,                              // Power Good Status (Read Only)

    0x00,                              // Reserved
    0x00,                              // OTP Flag (Read Only)
    0x00,                              // UVP Flag (Read Only)
    0x00,                              // LOCP Flag (Read Only)
    0x00,                              // OCP Flag (Read Only)
    0x00,                              // ADC Data Ready (Read Only)

    0x00,                              // BAT Voltage Value (Read Only)
    0x00,                              // VBUS Voltage Value (Read Only)
    0x00,                              // VBUS Current Value (Read Only)
};



//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSY9329RegisterMap g_stPMICData;
bit g_bPmicTrackingStart = _FALSE;

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
    // Set PMIC Data initial value
    g_stPMICData = g_stPmicInitialData;

    PCB_PMIC_POWER(_POWER_ON);

    // Initial Pmic Value
    ScalerTypeCPmicIICWrite(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void DeviceInterfaceTypeCPmicReset(BYTE ucSlaveAddr)
{
    ucSlaveAddr = ucSlaveAddr;

    CLR_PMIC_VOL_TRACK_START();
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
    if(bAction == _ON)
    {
        g_stPMICData.b1BiDirSetting = !bPowerDirection;

        // Set VBUS Voltage
        switch(usVoltage)
        {
            case _VBUS_VOLTAGE_5V:
                g_stPMICData.b3VBUSSetting = 0x00;
                g_stPMICData.b3VBUSAdjust = 5;
                break;

            case _VBUS_VOLTAGE_7V:
                g_stPMICData.b3VBUSSetting = 0x03;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_9V:
                g_stPMICData.b3VBUSSetting = 0x04;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_12V:
                g_stPMICData.b3VBUSSetting = 0x05;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_15V:
                g_stPMICData.b3VBUSSetting = 0x06;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_20V:
                g_stPMICData.b3VBUSSetting = 0x07;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            default:

                break;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 100)
        {
            g_stPMICData.b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 150)
        {
            g_stPMICData.b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 200)
        {
            g_stPMICData.b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 250)
        {
            g_stPMICData.b3VOCPSetting = 0x03;
        }
        else if(usCurrent <= 300)
        {
            g_stPMICData.b3VOCPSetting = 0x04;
        }
        else if(usCurrent <= 400)
        {
            g_stPMICData.b3VOCPSetting = 0x05;
        }
        else
        {
            g_stPMICData.b3VOCPSetting = 0x06;
        }

        if(g_stPMICData.b1PMICEnable == _OFF)
        {
            g_stPMICData.b1PMICEnable = bAction;

#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
            if(GET_PMIC_BIDIR_MODE() == _PMIC_SOURCE)
            {
                SET_PMIC_VOL_TRACK_START();
            }
#endif

            // Enable PMIC
            if(ScalerTypeCPmicIICWrite(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
            {
                return _FAIL;
            }
        }
        else
        {
            if(ScalerTypeCPmicIICWrite(ucSlaveAddr, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG2) == _FAIL)
            {
                return _FAIL;
            }
        }
    }
    else
    {
        g_stPMICData.b1PMICEnable = bAction;

        // Disable PMIC
        if(ScalerTypeCPmicIICWrite(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _FAIL;
        }
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
    if(bAction == _ON)
    {
        g_stPMICData.b1BiDirSetting = !bPowerDirection;

        // Set VBUS Voltage
        switch(usVoltage)
        {
            case _VBUS_VOLTAGE_5V:
                g_stPMICData.b3VBUSSetting = 0x00;
                g_stPMICData.b3VBUSAdjust = 5;
                break;

            case _VBUS_VOLTAGE_7V:
                g_stPMICData.b3VBUSSetting = 0x03;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_9V:
                g_stPMICData.b3VBUSSetting = 0x04;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_12V:
                g_stPMICData.b3VBUSSetting = 0x05;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_15V:
                g_stPMICData.b3VBUSSetting = 0x06;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_20V:
                g_stPMICData.b3VBUSSetting = 0x07;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            default:

                break;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 100)
        {
            g_stPMICData.b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 150)
        {
            g_stPMICData.b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 200)
        {
            g_stPMICData.b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 250)
        {
            g_stPMICData.b3VOCPSetting = 0x03;
        }
        else if(usCurrent <= 300)
        {
            g_stPMICData.b3VOCPSetting = 0x04;
        }
        else if(usCurrent <= 400)
        {
            g_stPMICData.b3VOCPSetting = 0x05;
        }
        else
        {
            g_stPMICData.b3VOCPSetting = 0x06;
        }

        if(g_stPMICData.b1PMICEnable == _OFF)
        {
            g_stPMICData.b1PMICEnable = bAction;

#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
            if(GET_PMIC_BIDIR_MODE() == _PMIC_SOURCE)
            {
                SET_PMIC_VOL_TRACK_START();
            }
#endif

            // Enable PMIC
            if(ScalerTypeCPmicIICWrite_EXINT0(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
            {
                return _FAIL;
            }
        }
        else
        {
            if(ScalerTypeCPmicIICWrite_EXINT0(ucSlaveAddr, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG2) == _FAIL)
            {
                return _FAIL;
            }
        }
    }
    else
    {
        g_stPMICData.b1PMICEnable = bAction;

        // Disable PMIC
        if(ScalerTypeCPmicIICWrite_EXINT0(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _FAIL;
        }
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
    if(bAction == _ON)
    {
        g_stPMICData.b1BiDirSetting = !bPowerDirection;

        // Set VBUS Voltage
        switch(usVoltage)
        {
            case _VBUS_VOLTAGE_5V:
                g_stPMICData.b3VBUSSetting = 0x00;
                g_stPMICData.b3VBUSAdjust = 5;
                break;

            case _VBUS_VOLTAGE_7V:
                g_stPMICData.b3VBUSSetting = 0x03;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_9V:
                g_stPMICData.b3VBUSSetting = 0x04;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_12V:
                g_stPMICData.b3VBUSSetting = 0x05;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_15V:
                g_stPMICData.b3VBUSSetting = 0x06;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            case _VBUS_VOLTAGE_20V:
                g_stPMICData.b3VBUSSetting = 0x07;
                g_stPMICData.b3VBUSAdjust = 2;
                break;

            default:

                break;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 100)
        {
            g_stPMICData.b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 150)
        {
            g_stPMICData.b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 200)
        {
            g_stPMICData.b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 250)
        {
            g_stPMICData.b3VOCPSetting = 0x03;
        }
        else if(usCurrent <= 300)
        {
            g_stPMICData.b3VOCPSetting = 0x04;
        }
        else if(usCurrent <= 400)
        {
            g_stPMICData.b3VOCPSetting = 0x05;
        }
        else
        {
            g_stPMICData.b3VOCPSetting = 0x06;
        }

        if(g_stPMICData.b1PMICEnable == _OFF)
        {
            g_stPMICData.b1PMICEnable = bAction;

#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
            if(GET_PMIC_BIDIR_MODE() == _PMIC_SOURCE)
            {
                SET_PMIC_VOL_TRACK_START();
            }
#endif

            // Enable PMIC
            if(ScalerTypeCPmicIICWrite_WDINT(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
            {
                return _FAIL;
            }
        }
        else
        {
            if(ScalerTypeCPmicIICWrite_WDINT(ucSlaveAddr, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG2) == _FAIL)
            {
                return _FAIL;
            }
        }
    }
    else
    {
        g_stPMICData.b1PMICEnable = bAction;

        // Disable PMIC
        if(ScalerTypeCPmicIICWrite_WDINT(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _FAIL;
        }
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
    g_stPMICData.b1VBUSDischarge = !bEn;

    // Disable Pmic VBUS Discharge
    return ScalerTypeCPmicIICWrite(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1);
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
    g_stPMICData.b1VBUSDischarge = !bEn;

    // Disable Pmic VBUS Discharge
    return ScalerTypeCPmicIICWrite_WDINT(ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1);
}

#if(_TYPE_C_PMIC_TRACKING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Tracking Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit DeviceInterfaceTypeCPmicTrackingStart(BYTE ucSlaveAddr)
{
    ucSlaveAddr = ucSlaveAddr;

#if(_TYPE_C_PMIC_DEBUG == _ON)
    DeviceInterfaceTypeCPmicStatus(ucSlaveAddr);
#endif

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Tracking
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit DeviceInterfaceTypeCPmicTracking(BYTE ucSlaveAddr)
{
    ucSlaveAddr = ucSlaveAddr;

#if(_TYPE_C_PMIC_DEBUG == _ON)
    DeviceInterfaceTypeCPmicStatus(ucSlaveAddr);
#endif

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

    ucResult = ScalerTypeCPmicIICRead(ucSlaveAddr, _SY9329_STATE_REG, _SY9329_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY9329_STATE_REG);

    DebugMessageTypeC("0.Pmic:Power Good Status", g_stPMICData.b1PowerGoodState);
    DebugMessageTypeC("0.Pmic:Relation Status", g_stPMICData.b1BATVBUSRelation);
    DebugMessageTypeC("0.Pmic:Battery Status", g_stPMICData.b1BATStatus);
    DebugMessageTypeC("0.Pmic:VBUS OCP Flag", g_stPMICData.b1VOCPFlag);
    DebugMessageTypeC("0.Pmic:Inductor OCP Flag", g_stPMICData.b1LOCPFlag);
    DebugMessageTypeC("0.Pmic:VBUS UVP Flag", g_stPMICData.b1UVPFlag);
    DebugMessageTypeC("0.Pmic:OTP Flag", g_stPMICData.b1OTPFlag);
    DebugMessageTypeC("0.Pmic:Battery Voltage Value", g_stPMICData.ucBATValue);
    DebugMessageTypeC("0.Pmic:VBUS Voltage Value", g_stPMICData.ucVBUSValue);
    DebugMessageTypeC("0.Pmic:VBUS Current Value", g_stPMICData.ucVBUSCurrentValue);

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
}
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SY9329)

