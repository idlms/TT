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
// ID Code      : ScalerCommonTMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_TMDS__

#include "ScalerCommonFunctionInclude.h"

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
BYTE ScalerTMDSHdmiGetAVIInfo(BYTE ucInputPort, EnumAviInfoContent enumContent);
void ScalerTMDSSetPsWakeupHpdToggle(BYTE ucInputPort);

void ScalerTMDSSetAcOnHpdToggle(BYTE ucInputPort);
void ScalerTMDSSetDcOnHpdToggle(BYTE ucInputPort);
void ScalerTMDSClearHpdFlag(BYTE ucInputPort);
void ScalerTMDSSetHpdTimeNormal(BYTE ucInputPort);


#if((_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
void ScalerTMDSHDMI2HPDRRIRQEnable(BYTE ucInputPort, bit bEnable);
#endif


#if(_HDMI_MAC_PAGE2_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
void ScalerTMDSRx0GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
void ScalerTMDSRx0GetHDR10Data(BYTE *pucHDRData);
#endif

#endif

#if(_HDMI_MAC_PAGE71_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
void ScalerTMDSRx2GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
void ScalerTMDSRx2GetHDR10Data(BYTE *pucHDRData);
#endif

#endif

#if(_HDMI_MAC_PAGE72_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
void ScalerTMDSRx3GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
void ScalerTMDSRx3GetHDR10Data(BYTE *pucHDRData);
#endif
#endif

#if(_HDMI_MAC_PAGE73_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
void ScalerTMDSRx4GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
void ScalerTMDSRx4GetHDR10Data(BYTE *pucHDRData);
#endif
#endif

#if(_HDMI_MAC_PAGE74_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
void ScalerTMDSRx5GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
void ScalerTMDSRx5GetHDR10Data(BYTE *pucHDRData);
#endif
#endif
#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_DVI_SUPPORT == _ON)
void ScalerTMDSRxAcOnInitial(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSHdmiGetAVIInfo(BYTE ucInputPort, EnumAviInfoContent enumContent)
{
    ucInputPort = ucInputPort;

    switch(ucInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            return ScalerTMDSRx0HdmiGetAVIInfo(enumContent);
#else
            return ScalerTMDSRx0HdmiGetAVIInfo(enumContent);
#endif

#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            return ScalerTMDSRx0HdmiGetAVIInfo(enumContent);
#else
            return ScalerTMDSRx1HdmiGetAVIInfo(enumContent);
#endif

#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            return ScalerTMDSRx0HdmiGetAVIInfo(enumContent);
#else
            return ScalerTMDSRx2HdmiGetAVIInfo(enumContent);
#endif

#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            return ScalerTMDSRx0HdmiGetAVIInfo(enumContent);
#else
            return ScalerTMDSRx3HdmiGetAVIInfo(enumContent);
#endif

#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            return ScalerTMDSRx0HdmiGetAVIInfo(enumContent);
#else
            return ScalerTMDSRx4HdmiGetAVIInfo(enumContent);
#endif

#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            return ScalerTMDSRx0HdmiGetAVIInfo(enumContent);
#else
            return ScalerTMDSRx5HdmiGetAVIInfo(enumContent);
#endif

#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
void ScalerTMDSSetPsWakeupHpdToggle(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            SET_TMDS_RX0_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            SET_TMDS_RX1_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_TMDS_RX2_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_TMDS_RX3_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            SET_TMDS_RX4_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            SET_TMDS_RX5_PS_WAKEUP_HPD_TOGGLE();
            break;
#endif

        default:
            break;
    }
}

void ScalerTMDSSetAcOnHpdToggle(BYTE ucInputPort)
{
    switch(ucInputPort)
    {

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_TMDS_RX2_AC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_TMDS_RX3_AC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

        default:
            break;
    }
}

void ScalerTMDSSetDcOnHpdToggle(BYTE ucInputPort)
{
    switch(ucInputPort)
    {

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_TMDS_RX2_DC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_TMDS_RX3_DC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

        default:
            break;
    }
}

void ScalerTMDSClearHpdFlag(BYTE ucInputPort)
{
    switch(ucInputPort)
    {

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            CLR_TMDS_RX2_PS_WAKEUP_HPD_TOGGLE();
			CLR_TMDS_RX2_AC_ON_HPD_TOGGLE_EVENT();
			CLR_TMDS_RX2_DC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            CLR_TMDS_RX3_PS_WAKEUP_HPD_TOGGLE();
			CLR_TMDS_RX3_AC_ON_HPD_TOGGLE_EVENT();
		 	CLR_TMDS_RX3_DC_ON_HPD_TOGGLE_EVENT();
            break;
#endif

        default:
            break;
    }
}

void ScalerTMDSSetHpdTimeNormal(BYTE ucInputPort)
{
    switch(ucInputPort)
    {

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            break;
#endif

        default:
            break;
    }
}

#if((_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS HPD IRQ Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHDMI2HPDRRIRQEnable(BYTE ucInputPort, bit bEnable)
{
    ucInputPort = ucInputPort;

    switch(ucInputPort)
    {
#if(_D0_HDMI_2_0_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            ScalerTMDSRx0HDMI2HPDRRIRQEnable(bEnable);
#else
            ScalerTMDSRx0HDMI2HPDRRIRQEnable(bEnable);
#endif
            break;
#endif

#if(_D1_HDMI_2_0_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            ScalerTMDSRx0HDMI2HPDRRIRQEnable(bEnable);
#else
            ScalerTMDSRx1HDMI2HPDRRIRQEnable(bEnable);
#endif
            break;
#endif

#if(_D2_HDMI_2_0_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            ScalerTMDSRx0HDMI2HPDRRIRQEnable(bEnable);
#else
            ScalerTMDSRx2HDMI2HPDRRIRQEnable(bEnable);
#endif

            break;
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            ScalerTMDSRx0HDMI2HPDRRIRQEnable(bEnable);
#else
            ScalerTMDSRx3HDMI2HPDRRIRQEnable(bEnable);
#endif

            break;
#endif

#if(_D4_HDMI_2_0_SUPPORT == _ON)
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            ScalerTMDSRx0HDMI2HPDRRIRQEnable(bEnable);
#else
            ScalerTMDSRx4HDMI2HPDRRIRQEnable(bEnable);
#endif
            break;
#endif

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
            ScalerTMDSRx0HDMI2HPDRRIRQEnable(bEnable);
#else
            ScalerTMDSRx5HDMI2HPDRRIRQEnable(bEnable);
#endif

            break;
#endif

        default:
            break;
    }
}
#endif

#if(_HDMI_MAC_PAGE2_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx0GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
    ScalerGetDataPortByte(P2_CD_HDMI_PSAP, _TMDS_INFO_RSV2_DB0, 11, &pucFreeSyncIIData[0], _AUTOINC);
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx0GetHDR10Data(BYTE *pucHDRData)
{
    ScalerGetDataPortByte(P2_CD_HDMI_PSAP, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P2_CD_HDMI_PSAP, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P2_CD_HDMI_PSAP, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#endif

#if(_HDMI_MAC_PAGE71_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, _TMDS_INFO_RSV2_DB0, 11, &pucFreeSyncIIData[0], _AUTOINC);
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2GetHDR10Data(BYTE *pucHDRData)
{
    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#endif

#if(_HDMI_MAC_PAGE72_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx3GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
    ScalerGetDataPortByte(P72_CD_HDMI_PSAP, _TMDS_INFO_RSV2_DB0, 11, &pucFreeSyncIIData[0], _AUTOINC);
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx3GetHDR10Data(BYTE *pucHDRData)
{
    ScalerGetDataPortByte(P72_CD_HDMI_PSAP, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P72_CD_HDMI_PSAP, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P72_CD_HDMI_PSAP, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#endif

#if(_HDMI_MAC_PAGE73_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
    ScalerGetDataPortByte(P73_CD_HDMI_PSAP, _TMDS_INFO_RSV2_DB0, 11, &pucFreeSyncIIData[0], _AUTOINC);
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4GetHDR10Data(BYTE *pucHDRData)
{
    ScalerGetDataPortByte(P73_CD_HDMI_PSAP, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P73_CD_HDMI_PSAP, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P73_CD_HDMI_PSAP, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#endif

#if(_HDMI_MAC_PAGE74_USE == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS FreeSync II Data
// Input Value  : pucFreeSyncIIData --> FreeSync II data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5GetFreeSyncIIData(BYTE *pucFreeSyncIIData)
{
    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, _TMDS_INFO_RSV2_DB0, 11, &pucFreeSyncIIData[0], _AUTOINC);
}
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5GetHDR10Data(BYTE *pucHDRData)
{
    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, _HDR10_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, _HDR10_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);
}
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#endif

#endif

#if(_DVI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Mac AC On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRxAcOnInitial(void)
{
    // On Measure Initial to prevent stable flag need twice the time
#if(_D0_TMDS_SUPPORT == _ON)
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_TMDS_RX0_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif

#if(_D1_TMDS_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);
#else
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);
#endif

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_TMDS_RX1_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif

#if(_D2_TMDS_SUPPORT == _ON)
#if(_D2_INPUT_PORT_TMDS_MAC_PAGE == _PAGE2)
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);
#else
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);
#endif

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_TMDS_RX2_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_TMDS_RX3_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif

#if(_D4_TMDS_SUPPORT == _ON)
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_TMDS_RX4_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif

#if(_D5_TMDS_SUPPORT == _ON)
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT2), _BIT7);

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
    SET_TMDS_RX5_AC_ON_HPD_TOGGLE_EVENT();
#endif
#endif
}
#endif
