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

#define __USER_INTERFACE_GLOBAL_DIMMING__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD) && (_GLOBAL_DIMMING_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
WORD code tGDPWMLUT[_GD_PANEL_PWM_MAX + 1] =
{
#ifdef _GD_PWM_LUT_TABLE
#include _GD_PWM_LUT_TABLE
#else
    0
#endif
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceGlobalDimmingAdjustPWM(WORD usPWMValue);
void UserInterfaceGlobalDimmingAdjustPCM(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value :
//--------------------------------------------------
void UserInterfaceGlobalDimmingAdjustPWM(WORD usPWMValue)
{
    WORD usNormPWM = 0;
#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    {
        usNormPWM = ((DWORD)usPWMValue * _DEVICE_LED_DRIVER_PWM_MAX) / _GD_PANEL_PWM_MAX;
        DeviceInterfaceLedDriverPwm(_PANEL_PWM_LOCAL_ALL, usPWMValue);
    }
#else
    {
        WORD usTempPWM = tGDPWMLUT[usPWMValue];
        usNormPWM = ((DWORD)usTempPWM * _BACKLIGHT_MAX()) / _GD_PANEL_PWM_MAX;
        UserAdjustBacklight(usNormPWM);
    }
#endif
}

//--------------------------------------------------
// Description  : Adjust PCM in Global Dimming Mode
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserInterfaceGlobalDimmingAdjustPCM(void)
{
#if(_SDR_TO_HDR_SUPPORT == _ON)

    UserAdjustSDRToHDR(GET_OSD_SDR_TO_HDR());

#else

#if(_PCM_FUNCTION == _ON)
    UserAdjustPCM(GET_OSD_PCM_STATUS());
#endif

#endif
}
#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD) && (_LOCAL_DIMMING_SUPPORT == _ON))

