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
// ID Code      : RTD2014UserAdjustOutputGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_OUTPUT_GAMMA__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

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
#if (_CIZGI_ENABLE_DICOM_CALIBRATION == _ON)
extern BYTE ucBackupDB;
BYTE xdata *g_pucDISP_CALIBRATION_FLASHxx = _OGC_FLASH_PAGE * _FLASH_PAGE_SIZE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_GAMMA_FUNCTION == _ON)
void UserAdjustGamma(BYTE ucGamma);
#endif


//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
void UserAdjustPCM(BYTE ucPCM);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_GAMMA_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------

void UserAdjustGamma(BYTE ucGamma)
{
    //EnumSelRegion enumGammaSelRegion = enumSelRegion;

    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;

    BYTE check[2];
    BYTE ucDICOMIndex = 0;
    BYTE ucBank = 0;


#if ((_PCM_FUNCTION == _ON) && (_PCM_TABLE_TYPE == _PCM_GEN_0))
//    enumGammaSelRegion = ScalerColorPCMCheckPCMRegion(enumSelRegion);
#endif

    switch (ucGamma)
    {
    case _GAMMA_OFF:
        break;
    case _GAMMA_DICOM:
        ucDICOMIndex = _DICOM1_TYPE;
        ucGammaBankNum = UserCommonAdjustDICOMBank(ucDICOMIndex);
        pucGammaBankAddr = UserCommonAdjustDICOMAddr(ucDICOMIndex);

        ScalerFlashRead(ucGammaBankNum, _OGC_DICOM_ADDRESS, 2, check);
        if (check[0] != 0xFF && check[1] != 0xFF) // Check if DICOM table is empty
        {
            // Set DICOM
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            //ScalerColorGammaSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
            ScalerColorOutputGammaAdjust(pucGammaBankAddr, ucGammaBankNum);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            //ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);

// #if (_PCM_FUNCTION == _ON)
//             ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
// #endif

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorSRGBEnable(_FUNCTION_OFF);

#if (_UNIFORMITY_SUPPORT == _ON)
            //ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
#endif
#if (_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
            return;
        }
        break;
    case _GAMMA_22:
        ucDICOMIndex = _DICOM2_TYPE;
        ucGammaBankNum = UserCommonAdjustDICOMBank(ucDICOMIndex);
        pucGammaBankAddr = UserCommonAdjustDICOMAddr(ucDICOMIndex);

        ScalerFlashRead(ucGammaBankNum, _OGC_DICOM2_ADDRESS, 2, check);
        if (check[0] != 0xFF && check[1] != 0xFF) // Check if DICOM table is empty
        {
            // Set DICOM
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            //ScalerColorGammaSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
            ScalerColorOutputGammaAdjust(pucGammaBankAddr, ucGammaBankNum);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            //ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);

// #if (_PCM_FUNCTION == _ON)
//             ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
// #endif

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorSRGBEnable(_FUNCTION_OFF);

#if (_UNIFORMITY_SUPPORT == _ON)
            //ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
#endif
#if (_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
            return;
        }
    break;
#if((_CUSTOMER_TYPE != _CUSTOMER_MEDICAL) && (_CUSTOMER_TYPE != _CUSTOMER_TECNNIT))
    case _GAMMA_20:
        ucDICOMIndex = _DICOM3_TYPE;
        ucGammaBankNum = UserCommonAdjustDICOMBank(ucDICOMIndex);
        pucGammaBankAddr = UserCommonAdjustDICOMAddr(ucDICOMIndex);

        ScalerFlashRead(ucGammaBankNum, _OGC_DICOM3_ADDRESS, 2, check);
        if (check[0] != 0xFF && check[1] != 0xFF) // Check if DICOM table is empty
        {
            // Set DICOM
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            //ScalerColorGammaSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
            ScalerColorOutputGammaAdjust(pucGammaBankAddr, ucGammaBankNum);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            //ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);

// #if (_PCM_FUNCTION == _ON)
//             ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
// #endif

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorSRGBEnable(_FUNCTION_OFF);

#if (_UNIFORMITY_SUPPORT == _ON)
            //ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
#endif
#if (_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
            return;
        }
        break;
    case _GAMMA_24:
        ucDICOMIndex = _DICOM4_TYPE;
        ucGammaBankNum = UserCommonAdjustDICOMBank(ucDICOMIndex);
        pucGammaBankAddr = UserCommonAdjustDICOMAddr(ucDICOMIndex);

        ScalerFlashRead(ucGammaBankNum, _OGC_DICOM4_ADDRESS, 2, check);
        if (check[0] != 0xFF && check[1] != 0xFF) // Check if DICOM table is empty
        {
            // Set DICOM
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            //ScalerColorGammaSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
            ScalerColorOutputGammaAdjust(pucGammaBankAddr, ucGammaBankNum);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            //ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);

// #if (_PCM_FUNCTION == _ON)
//             ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
// #endif

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorSRGBEnable(_FUNCTION_OFF);

#if (_UNIFORMITY_SUPPORT == _ON)
            //ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
#endif
#if (_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
            return;
        }
        break;
        break;
#endif
    }

#if (_OGC_SUPPORT == _ON)
    ucGammaBankNum = UserCommonAdjustOGCBank(ucGamma - 1, _OGC_NORMAL_TYPE);
    pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGamma - 1, _OGC_NORMAL_TYPE);

    UserCommonAdjustGamma(pucGammaBankAddr, ucGammaBankNum);

    RTDNVRamLoadColorSetting();

#if (_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#else
    UserCommonAdjustGamma(tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());

#if (_RGB_GAMMA_FUNCTION == _ON)
    UserAdjustRGBGamma(ucGamma);
#endif

#endif // End of #if(_OGC_SUPPORT == _ON)
}

#endif


#if(_PCM_FUNCTION == _ON)
extern BYTE code tSRGBByPass[];

// BYTE code tSRGBHalf[] =
// {
//     0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
// };

BYTE code tSRGBTest[] =
{
    0x00,0x00, 0x01,0x05, 0x00,0x00,
    0x00,0x00, 0x01,0x05, 0x00,0x00,
    0x00,0x00, 0x00,0x00, 0x01,0x10,
};

//--------------------------------------------------
// Description  : Adjust PCM
// Input Value  : ucPCM
// Output Value : None
//--------------------------------------------------
// void UserAdjustPCM(BYTE ucPCM)
// {
//     if(ucPCM != _PCM_OSD_NATIVE)
//     {
// #if(_OCC_SUPPORT == _ON)
//         if(ucPCM == _PCM_OSD_SRGB)
//         {
//             UserCommonAdjustPCM(_PCM_SRGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
//         }
//         else if(ucPCM == _PCM_OSD_ADOBE_RGB)
//         {
//             UserCommonAdjustPCM(_PCM_ADOBE_RGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
//         }

// #if(_RGB_3D_GAMMA == _ON)
//         else if(ucPCM == _PCM_OSD_SOFT_PROFT)
//         {
//             UserCommonAdjustPCM(_PCM_SOFT_PROFT, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
//         }
// #endif // End of #if(_RGB_3D_GAMMA == _ON)

//         else
// #endif // End of #if(_OCC_SUPPORT == _ON)
//         {
//             UserCommonAdjustPCM(_PCM_USER_MODE, tPCM_USER_TABLE[(ucPCM - _PCM_OSD_USER) * 3], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 1], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 2], GET_CURRENT_BANK_NUMBER(), _OCC_COLORMATRIX_TABLE_SIZE);
//         }
//     }
// }
void UserAdjustPCM(BYTE ucPCM)
{
#if (_GAMMA_FUNCTION == _ON)
        // Adjust Gamma Table
        UserAdjustGamma(GET_OSD_GAMMA());
#endif

    if (ucPCM == _PCM_OSD_NATIVE)
    {
        ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, tSRGBByPass, GET_CURRENT_BANK_NUMBER(), 18);
        //ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorSRGBEnable(_FUNCTION_ON);    
    }
    else if(ucPCM == _PCM_OSD_BT709)
    {
        //ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, tSRGBTest, GET_CURRENT_BANK_NUMBER(), 18);
        ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorSRGBEnable(_FUNCTION_ON);
    }

#if (_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif
    DebugMessageOsd("_OCC_REC709_ADDRESS",_OCC_REC709_ADDRESS);
}
#endif  // End of #if(_PCM_FUNCTION == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
