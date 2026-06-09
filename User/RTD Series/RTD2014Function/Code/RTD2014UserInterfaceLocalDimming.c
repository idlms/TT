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
// ID Code      : RTD2014UserInterfaceLocalDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_LOCAL_DIMMING__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD) && (_LOCAL_DIMMING_SUPPORT == _ON))

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
EnumLDActionMode UserInterfaceGetLocaldimmingActionMode(void);
EnumLDStatus UserInterfaceGetLocalDimmingStatus(void);
WORD UserInterfaceGetLocalDimmingPWMSmoothLevel(void);
EnumLDSDRColorMode UserInterfaceGetLocalDimmingColorMode(void);
#if(_OGC_SUPPORT == _ON)
BYTE UserInterfaceGetLocalDimmingGammaIndex(void);
#endif
void UserInterfaceLocalDimmingAdjustPCM(void);

EnumLDStatus UserInterfaceGetLocalDimmingNoSupportStatus(void);
EnumPCHDRMode UserInterfaceGetPCHDRMode(void);
#if(_UNIFORMITY_SUPPORT == _ON)
EnumUniformityStatus UserInterfaceGetUniformityStatus(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : System (1P only)
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumLDActionMode UserInterfaceGetLocaldimmingActionMode(void)
{
    if(ScalerOsdGetOsdEnable() == _ON)
    {
        return _LD_ACTION_MODE_NORNAL;
    }

    return _LD_ACTION_MODE_DIMMING;
}

//--------------------------------------------------
// Description  : Get Local Dimming OSD Status
// Input Value  : void
// Output Value : On or OFF
//--------------------------------------------------
EnumLDStatus UserInterfaceGetLocalDimmingStatus(void)
{
    // if sdr don't support local dimming, user should return _LD_DISABLE in sdr case.
    if(GET_OSD_LOCAL_DIMMING() == _ON)
    {
        return _LD_ENABLE;
    }

    return _LD_DISABLE;
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Frequency
// Input Value  : None
// Output Value : 0 ~ 100
//--------------------------------------------------
WORD UserInterfaceGetLocalDimmingPWMSmoothLevel(void)
{
    return GET_OSD_LD_ADJ();
}

#if(_OGC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Led Driver Pwm Frequency
// Input Value  : None
// Output Value : 0 ~ 100
//--------------------------------------------------
BYTE UserInterfaceGetLocalDimmingGammaIndex(void)
{
    return (GET_OSD_GAMMA() - 1);
}
#endif

//--------------------------------------------------
// Description  : Get SDR code to Lv gamma type
// Input Value  : None
// Output Value : EnumLDColorMode
//--------------------------------------------------

EnumLDSDRColorMode UserInterfaceGetLocalDimmingColorMode(void)
{
#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        switch(GET_OSD_PCM_STATUS())
        {
            #if(_OCC_SUPPORT == _ON)
            case _PCM_OSD_SRGB:
                return _LD_PCM_SRGB;
                break;

            case _PCM_OSD_ADOBE_RGB:
                return _LD_GAMMA_22;
                break;
            #endif

            default:
                break;
        }
    }
    else
#endif // End of #if(_PCM_FUNCTION == _ON)
    {
        switch(GET_OSD_GAMMA())
        {
            case _GAMMA_OFF:
                break;

            case _GAMMA_18:
                return _LD_GAMMA_18;
                break;

            case _GAMMA_20:
                return _LD_GAMMA_20;
                break;

            case _GAMMA_22:
                return _LD_GAMMA_22;
                break;

            case _GAMMA_24:
                return _LD_GAMMA_24;
                break;

            default:
                break;
        }
    }

    return _LD_GAMMA_22;
}

//--------------------------------------------------
// Description  : Adjust PCM in Local Dimming Mode
// Input Value  : None
// Output Value : void
//--------------------------------------------------
void UserInterfaceLocalDimmingAdjustPCM(void)
{
#if(_SDR_TO_HDR_SUPPORT == _ON)
    UserAdjustSDRToHDR(GET_OSD_SDR_TO_HDR());
#else
#if(_PCM_FUNCTION == _ON)
    OsdFuncColorPcmAdjust();
#endif
#endif
}

//--------------------------------------------------
// Description  : Local Dimming must support in OGC/OCC
// Input Value  : None
// Output Value : _LD_DISABLE /_LD_ENABLE
//--------------------------------------------------
EnumLDStatus UserInterfaceGetLocalDimmingNoSupportStatus(void)
{
#if(_SDR_TO_HDR_SUPPORT == _ON)
    // SDRtoHDR can support local dimming
    if(GET_OSD_SDR_TO_HDR() == _ON)
    {
        return _LD_ENABLE;
    }
#endif

    // Non OCC/OGC Mode can't supprt local dimming(Ex. user define gamma/ X-rite)
    if((GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE) &&
       (GET_OSD_GAMMA() == _GAMMA_OFF))
    {
        return _LD_DISABLE;
    }

    return _LD_ENABLE;
}

//--------------------------------------------------
// Description  : Get PCHDR Mode
// Input Value  : None
// Output Value : PCHDR mode/ normal mode
//--------------------------------------------------
EnumPCHDRMode UserInterfaceGetPCHDRMode(void)
{
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        return _LD_PCHDR_MODE;
    }
    else
#endif
    {
        return _LD_NONE_PCHDR_MODE;
    }
}

#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get uniformity OSD ON/OFF
// Input Value  : None
// Output Value : _PANEL_UNIFORMITY_ON/ _PANEL_UNIFORMITY_OFF
//--------------------------------------------------
EnumUniformityStatus UserInterfaceGetUniformityStatus(void)
{
    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
    {
        return _PANEL_UNIFORMITY_ON;
    }
    else
    {
        return _PANEL_UNIFORMITY_OFF;
    }
}
#endif

#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD) && (_LOCAL_DIMMING_SUPPORT == _ON))

