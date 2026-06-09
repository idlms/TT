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
// ID Code      : RTD2014UserInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE__

#include "UserCommonInclude.h"
#include "RTD2014UserHDMIEdid.h"
#include "RTD2014UserDPEdid.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _USER_SHOW_LOGO_STEP                    18 // frames

#define _EDID_VENDOR_SPEC_0                     160
#define _EDID_CHKSUM                            255

//-------------------------------------------------------
//  Definitions of RCP Key Codes
//-------------------------------------------------------
#define _MHL_RCP_VOLUME_UP                      0x41
#define _MHL_RCP_VOLUME_DOWN                    0x42
#define _MHL_RCP_MUTE                           0x43
#define _MHL_RCP_MUTE_FUNCTION                  0x65
#define _MHL_RCP_RESTORE_VOLUME_FUNCTION        0x66

//--------------------------------------------------
// Definitions of DCR THD Setting
//--------------------------------------------------
#define _DCR_THESHOLD1                          0x20
#define _DCR_THESHOLD2                          0x180

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#if(_DP_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_1080P[] =
{
#include "./EDID/EdidDp/EDID_DP_1920_1080_60HZ.h"
};
BYTE code tEDID_TABLE_DP_1920x1080_120[] =
{
#include "./EDID/EdidDp/EDID_DP_1920_1080_120HZ.h"
};

BYTE code tEDID_TABLE_DP_2048x1536[] =
{
#include "./EDID/EdidDp/EDID_DP_2048x1536@60.h"
};

BYTE code tEDID_TABLE_DP_2256x1504[] =
{
#include "./EDID/EdidDp/EDID_DP_2256x1504@60.h"
};

BYTE code tEDID_TABLE_DP_2K1K[] =
{
#include "./EDID/EdidDp/EDID_DP_2560_1440_60HZ_DELL.h"
};

BYTE code tEDID_TABLE_DP_2K1K_HDR[] =
{
#include "./EDID/EdidDp/EDID_DP_2560_1440_60HZ_HDR.h"
};

BYTE code tEDID_TABLE_DP_WQXGA_60[] =
{
#include "./EDID/EdidDp/EDID_DP_2560x1600@60.h"
};

BYTE code tEDID_TABLE_DP_WQHD_60[] =
{
#include "./EDID/EdidDp/EDID_DP_3440x1440@60.h"
};

BYTE code tEDID_TABLE_DP_4K2K_30[] =
{
#if(_CUSTOMER_TYPE == _CUSTOMER_THRUPUT || _CUSTOMER_TYPE == _CUSTOMER_ATECH)   // THRUPUT ���� ���������� ���� ���� EDID ����. ���� ��.
#include "./EDID/EdidDp/EDID_DP_3840_2160_60HZ_RTK.h"
#else

#include "./EDID/EdidDp/EDID_DP_3840_2160_30HZ_DELL.h"

#endif
};

BYTE code tEDID_TABLE_DP_4K2K_60[] =
{

#include "./EDID/EdidDp/EDID_DP_3840_2160_60HZ_RTK.h"

};

BYTE code tEDID_TABLE_DP_4K2K_60_HDR[] =
{
#include "./EDID/EdidDp/EDID_DP_3840_2160_60HZ_HDR.h"
};

#if (_ENABLE_RESET_EDID_MODE == _ON)
BYTE code tEDID_TABLE_PBP_3840x1080_60[] =
{
#include "./EDID/PBP_3840_1080_60HZ.h"
};
BYTE code tEDID_TABLE_PBP_3840x540_60[] =
{
#include "./EDID/PBP_3840_540_60HZ.h"
};
BYTE code tEDID_TABLE_PBP_1920x2160_60[] =
{
#include "./EDID/PBP_1920_2160_60HZ.h"
};
BYTE code tEDID_TABLE_PBP_1920x1080_60[] =
{
#include "./EDID/PBP_1920_1080_60HZ.h"
};
BYTE code tEDID_TABLE_PBP_1920x540_60[] =
{
#include "./EDID/PBP_1920_540_60HZ.h"
};
#endif

#endif

#if(_D0_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D0[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D0[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D0[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D1_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D1[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D1[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D1[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D2_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D2[] =
{

	#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"

	//#endif
};

BYTE code tHDMI20_EDID_TABLE_D2[] =
{

#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_WITH_420.h"  
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif

};

BYTE code tHDMI20_HDR_EDID_TABLE_D2[] =
{
	//#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
	#include ".\EDID\EdidHdmi\EDID_HDMI2_3840x2160@60_HFVSDB_WITH420_HDR.h"			

};

#endif

#if(_D3_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D3[] =
{
	//#if (_PANEL_TYPE == _LG_LCD_VBO_88_DFHD ) // 3840x1080
	//#include ".\EDID\EdidHdmi\EDID_HDMI2_3840x1080@60.h"
	//#else

	#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"

	//#endif
};

BYTE code tHDMI20_EDID_TABLE_D3[] =
{

#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif

};

BYTE code tHDMI20_HDR_EDID_TABLE_D3[] =
{

	//#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
	#include ".\EDID\EdidHdmi\EDID_HDMI2_3840x2160@60_HFVSDB_WITH420_HDR.h"	

};

#endif

#if(_D4_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D4[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D4[] =
{

#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif

};

BYTE code tHDMI20_HDR_EDID_TABLE_D4[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D5_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D5[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D5[] =
{

#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif

};

BYTE code tHDMI20_HDR_EDID_TABLE_D5[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif


#if(_SHARPNESS_SUPPORT == _ON)
#if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable0.h"
};

BYTE code tSU_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable2.h"
};

BYTE code tSU_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable4.h"
};

BYTE code tSU_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable6.h"
};

BYTE code tSU_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable8.h"
};

code BYTE *tSCALE_128TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_128_TAPS_0,        tSU_COEF_128_TAPS_2,        tSU_COEF_128_TAPS_4,        tSU_COEF_128_TAPS_6,        tSU_COEF_128_TAPS_8,
};
#endif // End of #if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))

#if(_HSU_128TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table8.h"
};

code BYTE *tSCALE_128TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_128_TAPS_0,        tSU_1to1_COEF_128_TAPS_2,        tSU_1to1_COEF_128_TAPS_4,        tSU_1to1_COEF_128_TAPS_6,        tSU_1to1_COEF_128_TAPS_8,
};
#endif // End of #if(_HSU_128TAPS_SUPPORT == _ON)

#if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable0.h"
};

BYTE code tSU_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable2.h"
};

BYTE code tSU_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable4.h"
};

BYTE code tSU_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable6.h"
};

BYTE code tSU_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable8.h"
};

code BYTE *tSCALE_96TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_96_TAPS_0,        tSU_COEF_96_TAPS_2,        tSU_COEF_96_TAPS_4,        tSU_COEF_96_TAPS_6,        tSU_COEF_96_TAPS_8,
};
#endif // End of #if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))

#if(_HSU_96TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table8.h"
};

code BYTE *tSCALE_96TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_96_TAPS_0,        tSU_1to1_COEF_96_TAPS_2,        tSU_1to1_COEF_96_TAPS_4,        tSU_1to1_COEF_96_TAPS_6,        tSU_1to1_COEF_96_TAPS_8,
};
#endif // End of #if(_HSU_96TAPS_SUPPORT == _ON)
#endif // End of #if(_SHARPNESS_SUPPORT == _ON)

#if(_ULTRA_VIVID_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ULTRAVIVID TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tCOLOR_ULTRAVIVID_SETTING_L[] =
{
#include "./UltraVivid/UltraVividTableL.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_M[] =
{
#include "./UltraVivid/UltraVividTableM.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_H[] =
{
#include "./UltraVivid/UltraVividTableH.h"
};

code BYTE *tCOLOR_ULTRAVIVID_SETTING_TABLE[] =
{
    tCOLOR_ULTRAVIVID_SETTING_L,
    tCOLOR_ULTRAVIVID_SETTING_M,
    tCOLOR_ULTRAVIVID_SETTING_H,
};

#if(_HDR10_SUPPORT == _ON)
BYTE code tCOLOR_ULTRAVIVID_SETTING_HDR[] =
{
#include "./UltraVivid/UltraVividTableHDR.h"
};
#endif
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if(_YPEAKING_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Ypeaking Coefficient Table
//----------------------------------------------------------------------------------------------------
#include "YPeakingTable.h"

code BYTE *tYPEAKING_TABLE[] =
{
    tYPK_COEF_1,
};
#endif // End of #if(_YPEAKING_SUPPORT == _ON)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_UART_SUPPORT == _ON)
//BYTE g_pucUartData[5];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// for RTD Tool IIC Debug
//-------------------------------------------------------
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
bit UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue);
#endif

//-------------------------------------------------------
// INT
//-------------------------------------------------------
#if(_INSTANT_TIMER_EVENT_0 == _ON)
void UserInterfaceTimer0InstantAccess_EXINT(void);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
void UserInterfaceTimer1InstantAccess_EXINT(void);
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
void UserInterfaceTimer2InstantAccess_EXINT(void);
#endif

#if(_UART_SUPPORT == _ON)
//void UserInterfaceUartIntHandler_SERIALPORT(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
BYTE UserInterfaceGetDdcciStatus_EXINT1(void);
BYTE UserInterfaceGetFactoryCommand_EXINT1(void);
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(void);
#endif
#endif

//-------------------------------------------------------
// EDID & HDCP
//-------------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
EnumHdmiEdidLocation UserInterfaceGetMultiHdmiEdidLocated(BYTE ucInputport, BYTE ucEdidIndex);
EnumEdidSelection UserInterfaceGetMultiHdmiEdidIndex(BYTE ucInputPort);
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort);
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
EnumUSB3RetimerPSPDSupportStatus UserInterfaceGetUSB3RetimerPSPDSupportStatus(void);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_DP_TX_SUPPORT == _ON)
void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
void UserInterfaceGetDpTxHdcp2RRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetDpTxHdcp2DcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetDpTxHdcp2EKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetDpTxHdcp2NPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif
#endif


//-------------------------------------------------------
// Wait for Panel Power Sequence Delay
//-------------------------------------------------------
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
void UserInterfacePanelPowerAction(BYTE ucEvent);
#endif

void UserInterfaceAdjustWaitPanelT1(void);
void UserInterfaceAdjustWaitPanelT2(void);
void UserInterfaceAdjustWaitPanelT3(void);
void UserInterfaceAdjustWaitPanelT4(void);
void UserInterfaceAdjustWaitPanelT5(void);

//-------------------------------------------------------
//
//-------------------------------------------------------
void UserInterfaceUncallFunction(void);
void UserInterfaceInitial(void);

void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed);

//-------------------------------------------------------
// User Information
//-------------------------------------------------------
bit UserInterfaceGetLogoStatus(void);
bit UserInterfaceGetdNoSupportStatus(void);
bit UserInterfaceGetDclkNoSupportStatus(void);
bit UserInterfaceGetActiveByPassStatus(void);
bit UserInterfaceGetCableResetStatus(void);
bit UserInterfaceGetForcePSStatus(void);
bit UserInterfaceGetIntoPSStatus(void);
EnumUserForceFakePS UserInterfaceGetFakePSStatus(void);
EnumUserForceFakePowerOff UserInterfaceGetFakePowerOffStatus(void);
bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType);
bit UserInterfaceGetDisplaySettingBacklightAction(void);

EnumColorSpace UserInterfaceGetColorFormat(void);

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
BYTE UserInterfaceGetHpSourceSwitchOsdEventTime(BYTE ucSourceScanType);
#endif

#if(_OVERSCAN_SUPPORT == _ON)
bit UserInterfaceGetOverScanStatus(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
EnumAspectRatioType UserInterfaceGetAspectRatioType(void);
void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio);
void UserInterfaceAdjustAspectRatio(void);
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
WORD UserInterfaceGetAspectRatioMinDVHeight(void);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
BYTE UserInterfaceGetAspectRatioOriginalRatio(void);
BYTE UserInterfaceGetAspectRatioOriginalRatioSmall(void);
#endif

#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
EnumRotationType UserInterfaceGetRotationDegree(void);
EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
BYTE UserInterfaceGetDisplayLatencyRatio(void);
#endif

#if(_FRC_SUPPORT == _ON)
void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

#if(_OD_SUPPORT == _ON)
EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void);
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
void UserInterfaceUpdateDDR3PhaseData(void);
#endif

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
bit UserInterfaceSystemEepromReadCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
bit UserInterfaceSystemEepromWriteCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
void UserInterfaceDisplayInitialization(void);
void UserInterfaceAdjustInputTiming(void);

#if(_UNDERSCAN_SUPPORT == _ON)
bit UserInterfaceAdjustUnderScan(void);
#endif

void UserInterfaceAdjustDisplayTiming(void);

//-------------------------------------------------------
// Color
//-------------------------------------------------------
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumColorYCCQuantization enumColorYCCQuantization);
#endif

void UserInterfaceAdjustActiveByPassColorProc(void);
void UserInterfaceAdjustColorProc(void);



#if(_ULTRA_VIVID_SUPPORT == _ON)
void UserInterfaceAdjustUltraVivid(void);
void UserInterfaceAdjustUltraVividProc(EnumDBApply enumDBApply);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSourceSearchPort enumSourceSearchPort);
BYTE UserInterfaceGetSharpnessCoefBankNum(void);
bit UserInterfaceSharpnessBypassCheck(void);
#endif

#if(_DCR_SUPPORT == _ON)
void UserInterfaceAdjustDCRHandler(void);
#endif

#if(_DCC_HISTOGRM_INFO == _ON)
void UserInterfaceDCCHistogramHandler(void);
#endif

#if(_IAPS_SUPPORT == _ON)
void UserInterfaceAdjustIAPSHandler(void);
#endif

//-------------------------------------------------------
// Osd
//-------------------------------------------------------
void UserInterfaceAdjustOsdPowerOnInitial(void);
void UserInterfaceAdjustOsdActiveProc(void);
void UserInterfaceAdjustOsdResetProc(void);

//-------------------------------------------------------
// Interfaces
//-------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex);
bit UserInterfaceGetLoadModeTableDefaultStatus(void);
bit UserInterfaceGetFirstAutoConfigStatus(void);
void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage);

#if(_VGA_FORCE_DISPLAY == _ON)
BYTE UserInterfaceModeSearchModeVGA(void);
#endif

bit UserInterfaceSkipAutoVpos(void);
bit UserInterfaceSkipAutoHpos(void);
#endif

#if(_MHL_SUPPORT == _ON)
bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort);

#if(_DP_SUPPORT == _ON)
EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
bit UserInterfaceGetDpCloneOutputStatus(void);
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) || (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
BYTE UserInterfaceGetDpSwitchSelectPort(void);
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
void UserInterfaceEmbeddedDpSwitch(void);
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
bit UserInterfaceGetHdmi5VStatus(BYTE ucInputPort);
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
bit UserInterfaceAdjustOsdCheckTotalSearchFinish(void);
void UserInterfaceAdjustSourceSearchTime(void);
WORD UserInterfaceGetEizoSearchFinishTime(void);
#endif

//-------------------------------------------------------
// AUDIO
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
bit UserInterfaceGetAudioReadyToPlayStatus(void);
EnumAudioInputSource UserInterfaceGetAudioSource(void);
bit UserInterfaceGetAudioMuteStatus(void);
bit UserInterfaceGetAudioNonLPCMStatus(void);
WORD UserInterfaceGetAudioVolume(void);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void);
bit UserInterfaceGetAudioDACKeepDepopState(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

void UserInterfaceAdjustAudioResetProc(void);
void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
void UserInterfaceSwapExternalAudioCodecInput(bit bSwap);
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
void UserInterfaceAdjustBacklight(BYTE ucBacklight);
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
void UserInterfaceAdjustBeforeDimmingCalibration(void);
void UserInterfaceAdjustAfterDimmingCalibration(void);
#endif

#if(_YPEAKING_SUPPORT == _ON)
void UserInterfaceAdjustYpeaking(void);
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
EnumDDCCIDebugMode UserInterfaceGetDdcciMode(void);
#endif

#if	(_ENABLE_LIGHT_SENSOR == _ON)
void UserInterfaceCheckBacklight(void);
//extern WORD CalculateLux(void);
#endif

#if (_ENABLE_SELF_CHECK == _ON)
static EnumSelfCheckPattern u8SelfCheckPattern = SC_RED;
EnumSelfCheckStatus u8SelfCheckStatus = SC_STATUS_NORMAL;
void UserInterfaceSelfCheck(void);
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
void AutoFanControl(SBYTE t);
SBYTE MeasureTemperature(void);
bit SuccessInitializeFanControl(void)
{
#if (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
	return SuccessInitialize_ADT7470();
#elif(_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
	return SuccessInitialize_MAX31785();
#else
	return false;
#endif
}
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User timer event process
// Input Value  : Event ID
// Output Value : None
//--------------------------------------------------
#if (_ENABLE_MENU_OLED == _ON)
static bit sbBlink = 0;
static BYTE ucTime = 0;
#endif

#if(_CUSTOMER_TYPE == _CUSTOMER_HUBIT)
WORD ustempBacklight = 0;
#endif

void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID)
{
	switch (enumEventID)
	{
	case _USER_TIMER_EVENT_KEY_REPEAT_ENABLE:
		SET_KEYREPEATSTART();
		break;

	case _USER_TIMER_EVENT_KEY_SCAN_READY:
		SET_KEYSCANREADY();
		break;

	case _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO:
		OsdDispDisableOsd();
		SET_OSD_LOGO_ON(_OFF);

#if(_INSTANT_TIMER_EVENT_0 == _ON)
		ScalerTimer0SetTimerCount(_TIMER_OFF);
#endif

#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
		UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
#else
#if (_ENABLE_MENU_OLED == _OFF)
		UserCommonInterfacePanelPowerAction(_PANEL_OFF);
#endif
#endif
		ScalerDDomainBackgroundEnable(_ENABLE);
		ScalerDDomainPatternGenEnable(_DISABLE);
		break;

	case _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE:
#if (_CUSTOMER_TYPE != _CUSTOMER_VIDEOTREE)
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOCABLE_MSG);
#endif
		break;

	case _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL:
#if (_CUSTOMER_TYPE != _CUSTOMER_VIDEOTREE)
		SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSIGNAL_MSG);
#endif
		break;

	case _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING:
#if (_CUSTOMER_TYPE != _CUSTOMER_VIDEOTREE)
	{
		if (GET_OSD_POWER_SAVE() < POWER_SAVE_1MIN)
		{
			SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG);
		}
		else
		{
			BYTE pst = 0;
			switch (GET_OSD_POWER_SAVE())
			{
			default:
			case POWER_SAVE_1MIN: pst = 1; break;
			case POWER_SAVE_2MIN: pst = 2; break;
			case POWER_SAVE_5MIN: pst = 5; break;
			case POWER_SAVE_30MIN: pst = 30; break;
			case POWER_SAVE_60MIN: pst = 60; break;
			case POWER_SAVE_120MIN: pst = 120; break;
				
			}
			if (psTimecount == pst)
			{
				psTimecount = 0;
				SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG);
			}
			else
			{
				psTimecount++;
				ScalerTimerActiveTimerEvent(MIN(1), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
			}
		}
	}
#endif
            break;

        case _USER_TIMER_EVENT_GO_TO_POWER_SAVING:
#if (_CUSTOMER_TYPE != _CUSTOMER_VIDEOTREE)
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG);
#endif
            break;

        case _USER_TIMER_EVENT_OSD_DISABLE:
            OsdDispDisableOsd();
            break;

        case _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON:
            SET_PANELPOWERSTATUS(_READY_FOR_BACKLIGHT);
            break;

        case _USER_TIMER_EVENT_PANEL_POWER_OFF:
            SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);

#if (_ENABLE_MENU_OLED == _ON)
			//**********************************************//
			ScalerTimerDelayXms(3000);
			//**********************************************//

			if (GET_COMP_RUN_RESTART() == _ON)
			{
				DebugMessageOsd("T:**** Restart Compensation **** ", 0);
				SET_OSD_STATE(_MENU_NONE);
				SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
				SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
				SET_COMP_RUN_RESTART(_OFF);
			}
#endif
            break;

#if(_VGA_SUPPORT == _ON)
        case _USER_TIMER_EVENT_DO_AUTO_COLOR:
            CLR_KEY_HOLD();
            OsdDisplayAutoBalanceProc();
            break;
#endif

        case _USER_TIMER_EVENT_PANEL_USED_TIMER:
            RTDFactoryPanelUsedTimer();
            break;

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
        case _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE:
            UserAdjustHLWinType5Move();
            break;
#endif

        case _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT:
//            OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNHIGHLIGHT); //180306_Delete
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT:
            CLR_KEY_HOLD();

            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_TRUE);
				if (GET_OSD_POWER_SAVE() != POWER_SAVE_OFF)ScalerTimerActiveTimerEvent(UserInterfacePowerSaveTimes(), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
            }
            else
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DP_VERSIOM_MSG);
            }

            break;

		case _USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT:
			CLR_KEY_HOLD();
			// Display mode
			if (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
			{
				//SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(_TRUE);

				if (SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
				{
					SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
				}
			}
			//else if (SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
			//{
				//                OsdDispHotKeyDisplayModeMenu();
			//}
			break;

#if(_FREESYNC_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ:
//Eric_020180307 : Delete
//                if((GET_OSD_STATE() == _MENU_INFORMATION) && (ScalerSyncGetFREESYNCEnable() == _TRUE))
//                {
//                    g_ucFontPointer1 = GET_FREESYNC_OSD_ADDRESS();
//                    OsdPropPutString(ROW(14 + 1), COL(16), _PFONT_PAGE_1, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
//                    ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
//                }
            break;
#endif
#if(_FREEZE_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG:
            OsdFuncDisableOsd();
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_STATE() != _MENU_NONE))
            {
                OsdFuncShowOSDAfterClosedFreezeMsg();
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
                SET_FREEZE_DISABLE_MSG_STATE(_OFF);
#endif
            }
            break;
#endif
#if	(_ENABLE_LIGHT_SENSOR == _ON)
		case _USER_TIMER_EVENT_CHECK_BACKLIGHT:
			ScalerTimerActiveTimerEvent(SEC(0.3), _USER_TIMER_EVENT_CHECK_BACKLIGHT);
#if(_LIGHT_SENSOR_TYPE == _LIGHT_CM32181)
			if (SuccessInitialize_CM3281() && GET_OSD_LIGHT_SENSOR_STATUS() == _ON)
			{
				UserInterfaceCheckBacklight();
			}
#elif (_LIGHT_SENSOR_TYPE == _LIGHT_TLS2561)
			if (SuccessInitialize_TLS2561() && GET_OSD_LIGHT_SENSOR_STATUS() == _ON)
			{
				UserInterfaceCheckBacklight();
			}
#else
#endif
			break;
#endif
#if	(_ENABLE_FAN_CONTROL == _ON)
		case _USER_TIMER_EVENT_CHECK_FANCONTROL:
			ScalerTimerActiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_CHECK_FANCONTROL);
			ApplyFanControl(_FALSE);
			if(GET_OSD_STATE() == _MENU_OTHERS_TEMP) COsdShowChooseOtherText(_STRING_OTHER_TEMP);
			break;
#endif
#if	(_ENABLE_SELF_CHECK == _ON)
		case _USER_TIMER_EVENT_CHECK_SELF:
			ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_CHECK_SELF);
			if (SuccessInitialize_TCS34725() && GET_OSD_STATE () == _MENU_NONE && (GET_OSD_SELF_CHECK_STATUS() == _ON))
			{
				UserInterfaceSelfCheck();
			}
			else
			{
				u8SelfCheckStatus = SC_STATUS_PAUSE;
			}

			break;
#endif

#if (_ENABLE_MENU_OLED == _ON)
		case _USER_TIMER_EVENT_OSD_JB_RUN: //JB Run => On
			CLR_KEY_HOLD();

			// Display mode
			DebugMessageOsd("T:#JB Execute => On# ", 0);
			////////////////////////////////////////
			UserInterfaceKeyPadLedControl(_LED_POWER_OFF);
			SET_WAIT_TO_RUN_JB(_ON);
			SET_COMP_RUN_RESTART(_ON);
			SysPowerSetTargetPowerStatus(_POWER_STATUS_COMPENSATION_JB_TO_ON);
			////////////////////////////////////////
			break;

		case _USER_TIMER_EVENT_OSD_OFF_RS_RUN: //OFF-RS Run => On
			CLR_KEY_HOLD();

			// Display mode
			DebugMessageOsd("T:#OFF_RS Execute => On# ", 0);
			////////////////////////////////////////
			SET_WAIT_TO_RUN_OFFRS(_ON);	//OFF RS
			// SET_COMP_RUN_RESTART(_ON);
			SysPowerSetTargetPowerStatus(_POWER_STATUS_COMPENSATION_OFF_RS);
			////////////////////////////////////////
			break;

		case _USER_TIMER_EVENT_LED_BLINKING_TIMER:
			if (sbBlink) UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);
			else UserInterfaceKeyPadLedControl(_LED_TYPE_FLASH);

			sbBlink ^= 1;

			ScalerTimerActiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_LED_BLINKING_TIMER);
			break;

		case _USER_TIMER_EVENT_JB_END_TIMER:			//JB Disable Command
			DebugMessageOsd("T:JB Command Disable", GET_WAIT_TO_RUN_JB());
			AMOLED_WriteByte(_AMOLED_JB_REG, 0x00);
			break;

		case _USER_TIMER_EVENT_OFFRS_END_TIMER:
			DebugMessageOsd("T:_USER_TIMER_EVENT_OFFRS_END_TIMER", ucTime);
			//if(ucTime == 3)
			if (ucTime == 6)
			{
				if (GET_OFF_RS_STATUS() == _ON)
				{
					DebugMessageOsd("T:OFF_RS Timer DONE", PIN_JB_OFF_RS_DONE);
					CancelWaitingToRunOFFRS();
					Excute_OLED_OFFRS(_OFF);
					ResetOffRSTime();

					//ucExecute = 0;
					ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_LED_BLINKING_TIMER);

					RTDNVRamSaveOSDData();

					ScalerTimerDelayXms(3000);

					SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);

					ucTime = 0;
				}
			}
			else
			{
				ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_OFFRS_END_TIMER);
				ucTime++;
				DebugMessageOsd("T:ucTime", ucTime);
			}
			break;

		case _USER_TIMER_EVENT_OSD_POWER_OFF:
			CLR_KEY_HOLD();
			// Display mode
			DebugMessageOsd("T:#_USER_TIMER_EVENT_OSD_POWER_OFF# ", GET_KEYMESSAGE());
			SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);

			break;


#endif
#if(_CUSTOMER_TYPE == _CUSTOMER_HUBIT)
		case _USER_TIMER_EVENT_BOOT_PWMSET:
		{
			if (ustempBacklight >= GET_OSD_BACKLIGHT())
			{
				UserAdjustBacklight(GET_OSD_BACKLIGHT());
				ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BOOT_PWMSET);
				DebugMessageSystem("---Boot Backlight SET END---", ustempBacklight);
			}
			else
			{
				ScalerTimerActiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_BOOT_PWMSET);
				UserAdjustBacklight(ustempBacklight);
				DebugMessageSystem("Boot Backlight", ustempBacklight);
				ustempBacklight += 2;
			}
		}
			break;
#endif
//#if (_PANEL_IDX_NAME == _PANEL_DV550QUM_N10	)
//		case _USER_TIMER_EVENT_PANEL_I2C:
//			UserPanel_DV550QUM_N10_Initialize();
//			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
//			break;
//#endif
#if(_CUSTOMER_TYPE == _CUSTOMER_MRK)
		case _USER_TIMER_EVENT_BOOT_GPIO1_DELAY:
			EANBLE_GPIO1(_ON);
			break;
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
		case _USER_TIMER_EVENT_PIXEL_SHIFT:
			if (GET_OSD_PIXEL_SHIFT_STATUS() == _ON)
			{
				if (pixShiftTime == ((GET_OSD_PIXEL_SHIFT_TIME()+1) * 5))
				{
					pixShiftTime = 0;
					if (setShift == 8) setShift = 0;
					UserAdjustPixelShifting(setShift++);
					ScalerTimerActiveTimerEvent(MIN(1), _USER_TIMER_EVENT_PIXEL_SHIFT);
					DebugMessageYHJ("==PIXEL SHIFT==", _USER_TIMER_EVENT_PIXEL_SHIFT);
				}
				else
				{
					pixShiftTime++;
					ScalerTimerActiveTimerEvent(MIN(1), _USER_TIMER_EVENT_PIXEL_SHIFT);
				}
			}
			break;
#endif
        default:
            break;
    }
}

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
//--------------------------------------------------
// Description  : User Debug Tool Page IIC
// Input Value  : Event ID
// Output Value : None
//--------------------------------------------------
bit UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue)
{
    bit bDebugMode = _FALSE;

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    if(bDebugMode == _FALSE)
    {
        bDebugMode = DeviceInterfaceLedDriverDebug(ucType, pucDdcciArray, pucReturnValue);
    }
#endif

    return bDebugMode;

    ucType = *pucDdcciArray;
    ucType = *pucReturnValue;
}
#endif

#if(_INSTANT_TIMER_EVENT_0 == _ON)
//--------------------------------------------------
// Description  : Action in Timer0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer0InstantAccess_EXINT(void)
{
    if(GET_OSD_LOGO_ON() == _ON)
    {
        if(g_ucLogoTimerCounter != 0xFF)
        {
            g_ucLogoTimerCounter++;
        }

        switch(g_ucLogoTimerCounter)
        {
            case _USER_SHOW_LOGO_STEP:
            case (_USER_SHOW_LOGO_STEP * 2):
            case (_USER_SHOW_LOGO_STEP * 3):
            case (_USER_SHOW_LOGO_STEP * 4):
            case (_USER_SHOW_LOGO_STEP * 5):
            case (_USER_SHOW_LOGO_STEP * 6):
            case (_USER_SHOW_LOGO_STEP * 7):

                ScalerOsdSetTransparency_EXINT(0xFF - (g_ucLogoTimerCounter / _USER_SHOW_LOGO_STEP) * 36);

                break;

            default:

                break;
        }
    }
}
#pragma restore
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
//--------------------------------------------------
// Description  : Action in Timer1 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer1InstantAccess_EXINT(void)
{
}
#pragma restore
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
//--------------------------------------------------
// Description  : Action in Timer2 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer2InstantAccess_EXINT(void)
{
}
#pragma restore
#endif

#if(_UART_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Action in Serial Port0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
//void UserInterfaceUartIntHandler_SERIALPORT(void)
//{
//    if(GET_UART_RECEIVE_STATUS() == _TRUE)
//    {
//        g_pucUartData[0] = GET_UART_DATA();
//
//        CLR_UART_RECEIVE_STATUS();
//    }
//}
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get DDC-CI Status for Int1
// Input Value  : ucDataType --> Data Type in StructSystemData
// Output Value : ucValue --> Value of the Input Data Type
//--------------------------------------------------
BYTE UserInterfaceGetDdcciStatus_EXINT1(void) using 2
{
    return GET_OSD_DDCCI_STATUS();
}

//--------------------------------------------------
// Description  : Get Data from DDCCI Buffer defined by user
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetFactoryCommand_EXINT1(void) using 2
{
    return _FALSE;
}

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get Source Opcode is HDMI freesync
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(void) using 2
{
    if(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE] == _HDMI_FREESYNC_MCCS_VCP)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif // #if(_HDMI_FREESYNC_SUPPORT == _ON)

#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get the HDMI Port Edid location
// Input Value  : EDID Index
// Output Value : External/ Embedded Edid
//--------------------------------------------------
EnumHdmiEdidLocation UserInterfaceGetMultiHdmiEdidLocated(BYTE ucInputport, BYTE ucEdidIndex)
{
    return tEdidMultiLocatedTable[ucInputport][ucEdidIndex];
}

//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : ucInputPort
// Output Value : Edid Index Enum
//--------------------------------------------------
EnumEdidSelection UserInterfaceGetMultiHdmiEdidIndex(BYTE ucInputPort)
{
    EnumEdidSelection enumIndex = _EDID_INDEX_0;
    BYTE ucHdmiVer = OsdFuncGetHdmiPortVersion(ucInputPort);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    if((GET_OSD_FREE_SYNC_STATUS() == _ON))
    {
        enumIndex += ((_HDMI_HDR10_SUPPORT == _ON) ? 0x06 : 0x03);
    }
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
    if((UserInterfaceHDRGetHDR10ModeStatus(ucInputPort) != _HDR10_MODE_OFF))
    {
        enumIndex += 0x03;
    }
#endif

    switch(ucHdmiVer)
    {
        case _HDMI_1P4:
            break;

        case _HDMI_2P0:
            enumIndex += 0x01;
            break;

        case _HDMI_2P1:
            enumIndex += 0x02;
            break;

        default:
            break;
    }
    return enumIndex;
}
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Embedded EDID Data
// Input Value  : Input Port EDID Select
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort)
{
    switch(enumInputPort)
    {
        case _A0_INPUT_PORT_EDID:
            break;


        case _D0_INPUT_PORT_EDID:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
			if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_1080P)
			{
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_1080P, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_1920_1080_120)
			{
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_1920x1080_120, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_2048_1536)
			{
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_2048x1536, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_2256_1504)
			{
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_2256x1504, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_2560_1440)
			{
#if(_HDR10_SUPPORT == _ON)
				if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
				{
					memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_2K1K_HDR, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
				}
				else
				{
					memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_2K1K, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
				}
#else
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_2K1K, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
	}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_2560_1600)
			{
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_WQXGA_60, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_3440_1440)
			{
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_WQHD_60, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_4K2K_30HZ)
			{
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_30, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_4K2K_60HZ)
			{
#if (_ENABLE_RESET_EDID_MODE == _ON)		
				UserInterfaceInitialEDID(_D0_INPUT_PORT_EDID);
#else

#if(_HDR10_SUPPORT == _ON)
				if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
				{
					memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_60_HDR, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
				}
				else
				{
					memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_60, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
				}
#else
				memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_60, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
#endif
			}

#elif(_D0_HDMI_SUPPORT == _ON)

			if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _HDMI_EDID_0)
			{
#if((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D0, tHDMI14_EDID_TABLE_D0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _HDMI_EDID_1)
			{
#if((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D0, tHDMI20_EDID_TABLE_D0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _HDMI_EDID_2)
			{
#if((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D0, tHDMI20_HDR_EDID_TABLE_D0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}
#endif
            break;

        case _D1_INPUT_PORT_EDID:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
			if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_1080P)
			{
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_1080P, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_1920_1080_120)
			{
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_1920x1080_120, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
			}

			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_2048_1536)
			{
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_2048x1536, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_2256_1504)
			{
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_2256x1504, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_2560_1440)
			{
#if(_HDR10_SUPPORT == _ON)
				if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
				{
					memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_2K1K_HDR, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
				}
				else
				{
					memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_2K1K, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
				}
#else
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_2K1K, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_2560_1600)
			{
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_WQXGA_60, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_3440_1440)
			{
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_WQHD_60, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_4K2K_30HZ)
			{
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_30, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_4K2K_60HZ)
			{
#if (_ENABLE_RESET_EDID_MODE == _ON)		
				UserInterfaceInitialEDID(_D1_INPUT_PORT_EDID);
#else

#if(_HDR10_SUPPORT == _ON)
				if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
				{
					memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_60_HDR, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
				}
				else
				{
					memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_60, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
				}
#else
				memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_60, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

				//memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_60, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}

#elif(_D1_HDMI_SUPPORT == _ON)

			if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _HDMI_EDID_0)
			{
#if((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D1, tHDMI14_EDID_TABLE_D1, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _HDMI_EDID_1)
			{
#if((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D1, tHDMI20_EDID_TABLE_D1, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _HDMI_EDID_2)
			{
#if((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D1, tHDMI20_HDR_EDID_TABLE_D1, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
			}
#endif
            break;

        case _D2_INPUT_PORT_EDID:
#if(_D2_HDMI_SUPPORT == _ON)

			if (UserCommonNVRamGetSystemData(_EDID_D2_SELECT) == _HDMI_EDID_0)
			{
				DebugMessageSystem("D2 HDMI 1.4", 1);
//#if((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D2, tHDMI14_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
//#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D2_SELECT) == _HDMI_EDID_1)
			{
//#if((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
				DebugMessageSystem("D2 HDMI 2.0", 1);
#if (_ENABLE_RESET_EDID_MODE == _ON)		
				UserInterfaceInitialEDID(_D2_INPUT_PORT_EDID);
#else
#if(_HDR10_SUPPORT == _ON)
				if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
				{
					DebugMessageYHJ("EDID HDR ON", UserCommonHDRGetHDR10Status());
					memcpy(MCU_DDCRAM_D2, tHDMI20_HDR_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
				}
				else
				{
					DebugMessageYHJ("EDID HDR OFF", UserCommonHDRGetHDR10Status());
					memcpy(MCU_DDCRAM_D2, tHDMI20_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
				}
#else
				memcpy(MCU_DDCRAM_D2, tHDMI20_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
#endif

#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D2_SELECT) == _HDMI_EDID_2)
			{
//#if((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
				//DebugMessageYHJ("EDID HDR ON 2", UserCommonHDRGetHDR10Status());
				memcpy(MCU_DDCRAM_D2, tHDMI20_HDR_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
//#endif
			}
//#endif
            break;

        case _D3_INPUT_PORT_EDID:
#if(_D3_HDMI_SUPPORT == _ON)

			if (UserCommonNVRamGetSystemData(_EDID_D3_SELECT) == _HDMI_EDID_0)
			{
//#if((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D3, tHDMI14_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
//#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D3_SELECT) == _HDMI_EDID_1)
			{
//#if((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))

#if (_ENABLE_RESET_EDID_MODE == _ON)		
				UserInterfaceInitialEDID(_D3_INPUT_PORT_EDID);
#else
#if(_HDR10_SUPPORT == _ON)
				if (GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
				{
					memcpy(MCU_DDCRAM_D3, tHDMI20_HDR_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
				}
				else
				{
					memcpy(MCU_DDCRAM_D3, tHDMI20_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
				}
#else
				memcpy(MCU_DDCRAM_D3, tHDMI20_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
#endif

//#endif
			}
			else if (UserCommonNVRamGetSystemData(_EDID_D3_SELECT) == _HDMI_EDID_2)
			{
//#if((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
				memcpy(MCU_DDCRAM_D3, tHDMI20_HDR_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
//#endif
			}
#endif
            break;


#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D4_INPUT_PORT_EDID:

#if(_D4_HDMI_SUPPORT == _ON)

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D4_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D4_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memcpy(MCU_DDCRAM_D4, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D4_INPUT_PORT)], _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memcpy(MCU_DDCRAM_D4, tHDMI_EDID_FHD_TABLE, _D4_EMBEDDED_DDCRAM_MAX_SIZE);

#endif

#endif
            break;
#endif // #if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D5_INPUT_PORT_EDID:

#if(_D5_HDMI_SUPPORT == _ON)

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D5_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D5_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memcpy(MCU_DDCRAM_D5, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D5_INPUT_PORT)], _D5_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memcpy(MCU_DDCRAM_D5, tHDMI_EDID_FHD_TABLE, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

#endif
            break;
#endif // #if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D6_INPUT_PORT_EDID:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

            memcpy(MCU_DDCRAM_D6, tDP_EDID_TABLE[UserAdjustGetDpEdidIndex(_D6_INPUT_PORT)], _D6_EMBEDDED_DDCRAM_MAX_SIZE);

#endif
            break;
#endif // #if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

        case _D0_INPUT_PORT_MHL_EDID:
            break;

        case _D1_INPUT_PORT_MHL_EDID:
            break;

        case _D2_INPUT_PORT_MHL_EDID:
            break;

        case _D3_INPUT_PORT_MHL_EDID:
            break;

        case _D4_INPUT_PORT_MHL_EDID:
            break;

        case _D5_INPUT_PORT_MHL_EDID:
            break;

        default:
            break;
    }
}
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get USB3 Retimer PS/PD Support Status
// Input Value  : void
// Output Value : EnumUSB3RetimerPSPDSupportStatus
//--------------------------------------------------
EnumUSB3RetimerPSPDSupportStatus UserInterfaceGetUSB3RetimerPSPDSupportStatus(void)
{
    if(GET_OSD_USB3_RETIMER_PS_PD_WAKEUP() == _TRUE)
    {
        return _USB3_RETIMER_PS_PD_ENABLE;
    }

    return _USB3_RETIMER_PS_PD_ENABLE;
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
//--------------------------------------------------
// Description  : Get HDCP Bksv By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Tx HDCP Aksv By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2RRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2DcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2EKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2NPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
//--------------------------------------------------
// Description  : Power Power On/Off Sequence
// Input Value  : ucEvent --> _PANEL_ON
//                            _PANEL_OFF
//                            _BACKLIGHT_ON
//                            _BACKLIGHT_OFF
// Output Value : None
//--------------------------------------------------
void UserInterfacePanelPowerAction(BYTE ucEvent)
{
    ucEvent = ucEvent;
}
#endif

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT1(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_ON_T1);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT2(void)
{

if(_PANEL_STYLE == _PANEL_VBO)
{
    ScalerDisplayVboPollingHotPlug(_PANEL_POWER_ON_T2);
}
else if(_PANEL_STYLE == _PANEL_DPTX)
{
    ScalerDisplayDPTxPollingHotPlug(_PANEL_POWER_ON_T2);
}

}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT3(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_ON_T3);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T4
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT4(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_OFF_T4);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T5
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT5(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_OFF_T5);
}

//--------------------------------------------------
// Description  : Uncall Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUncallFunction(void)
{
    bit bUncall = _FALSE;

    if(bUncall == _TRUE)
    {
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
        bUncall = tFLASH_PARTITION_BOOTTABLE[0];
#endif

        UserInterfaceGetDisplaySettingBacklightAction();

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
        DeviceInterfaceLedDriverPwm(_DEVICE_LED_DRIVER_PWM_ALL, 0);
        DeviceInterfaceLedDriverPwmArray(0);
        DeviceInterfaceLedDriverPwmEnable(_ENABLE);
        DeviceInterfaceLedDriverBacklight(0);
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        UserInterfaceTypeCGetOsdU3ModeSelection(_D0_INPUT_PORT);
        UserInterfaceTypeCGetPinConfigType(_D0_INPUT_PORT, _TYPE_C_U3_ON);
#endif
    }
}

//--------------------------------------------------
// Description  : User Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceInitial(void)
{
	RTDNVRamStartup();
	PWM_SETTINGS();
	PCB_PWM_SETTING();

    UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), UserCommonNVRamGetSystemData(_SEARCH_PORT));
    RTDKeyInitial();
    SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);

    // Adjust Backlight
    UserAdjustBacklight(GET_OSD_BACKLIGHT());

    // Adjust IR Decode
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    UserAdjusIR();
#endif
#if   (_CUSTOMER_TYPE == _CUSTOMER_THRUPUT)
	SET_OSD_DOUBLE_SIZE(_OFF);
#elif (_CUSTOMER_TYPE == _CUSTOMER_VIMSE)
	SET_OSD_DOUBLE_SIZE(_OFF);
#elif(_CUSTOMER_TYPE == _CUSTOMER_BAYTEK)
	SET_OSD_DOUBLE_SIZE(_OFF);
#elif(_CUSTOMER_TYPE == _CUSTOMER_VIDEOTREE)
	SET_OSD_DOUBLE_SIZE(_ON);
#elif(_CUSTOMER_TYPE == _CUSTOMER_STANDARD)
	if ((_PANEL_DH_WIDTH >= 3840) && (_PANEL_DV_HEIGHT >= 2160))
	{
		SET_OSD_DOUBLE_SIZE(_ON);
	}
	else if ((_PANEL_DH_WIDTH <= 1920) && (_PANEL_DV_HEIGHT <= 1080))
	{
		SET_OSD_DOUBLE_SIZE(_OFF);
	}
#elif(_CUSTOMER_TYPE == _CUSTOMER_SKYDEFINITION)
	SET_OSD_DOUBLE_SIZE(_ON);
#else
	SET_OSD_DOUBLE_SIZE(_OFF);
#endif

}

//--------------------------------------------------
// Description  : User Power Switch
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_ON);

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_ON);

            // Set Monitor Power On Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _ON);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
			DebugMessageOsd("_POWER_ACTION_AC_ON_TO_OFF _PANEL_OFF", _CUSTOMER_TYPE);
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
			DebugMessageOsd("_POWER_ACTION_NORMAL_TO_OFF _PANEL_OFF", _CUSTOMER_TYPE);
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;
		
        case _POWER_ACTION_PS_TO_OFF:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;
		case _POWER_ACTION_NORMAL_TO_FAKE_PS:
        case _POWER_ACTION_NORMAL_TO_PS:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_SAVING);

            // Panel pown down.
			DebugMessageOsd("_POWER_ACTION_NORMAL_TO_PS _PANEL_OFF", _CUSTOMER_TYPE);
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            break;
        default:

            break;
    }

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    ScalerTimer0SetTimerCount(_TIMER_OFF);
#endif
}

//--------------------------------------------------
// Description  : Keypad Led Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed)
{
	DebugMessageOsd("KEY PAD LED", ucKeyPadLed);
    switch(ucKeyPadLed)
    {
        case _LED_POWER_ON:
            PCB_LED_ON();
#if(_CUSTOMER_TYPE == _CUSTOMER_MRK)
			ScalerTimerDelayXms(5000);
			EANBLE_GPIO1(_ON);
#endif
            break;

        case _LED_POWER_ACTIVE:
            PCB_LED_ACTIVE();
            break;

        case _LED_POWER_SEARCH:
            PCB_LED_IDLE();
            break;

        case _LED_POWER_SAVING:
            PCB_LED_POWER_SAVING();
            break;

        case _LED_POWER_NOSUPPORT:
            PCB_LED_ACTIVE();
            break;

        case _LED_POWER_NOSUPPORT_SAVING:
            PCB_LED_POWER_SAVING();
            break;

        case _LED_POWER_OFF:
            PCB_LED_OFF();
            break;

        case _LED_ALL_OFF:
            PCB_LED_OFF();
            break;

        case _LED_TYPE_1:
            PCB_LED_TYPE1();
            break;

        case _LED_TYPE_2:
            PCB_LED_TYPE2();
            break;

        case _LED_TYPE_3:
            PCB_LED_TYPE3();
            break;

        case _LED_TYPE_4:
            PCB_LED_TYPE4();
            break;

        case _LED_TYPE_5:
            PCB_LED_TYPE5();
            break;

        case _LED_TYPE_FLASH:
            PCB_LED_TYPE_FLASH();
            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  : User OSD Get LogoOn
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetLogoStatus(void)
{
    return (GET_OSD_LOGO_ON());
}

//--------------------------------------------------
// Description  : Check Whther to support this timing
// Input Value  : None
// Output Value : TRUE => Go to No Support State
//--------------------------------------------------
bit UserInterfaceGetdNoSupportStatus(void)
{
    // Add User No Support Check
    return _FALSE;
}

//--------------------------------------------------
// Description  : For User to Check Whether to Support Current DCLK
// Input Value  : None
// Output Value : _TRUE => No Support
//--------------------------------------------------
bit UserInterfaceGetDclkNoSupportStatus(void)
{
    if((GET_D_MAX_CLK_FREQ() > ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ)) ||
       (GET_D_MIN_CLK_FREQ() < ((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ)))
    {
        DebugMessageScaler("D Clock Exceed Panel Supported Range", GET_D_CLK_FREQ());
        return _TRUE;
    }

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_DOSMODE_ONLY_SUPPORT == _ON))
    if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)
    {
        if((GET_INPUT_TIMING_HWIDTH() > 800) ||
           (GET_INPUT_TIMING_VHEIGHT() > 600))
        {
            DebugMessageScaler("FRC only supports dos-mode timing", 0);
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get whether to by pass normal active process
// Input Value  : None
// Output Value : _TRUE => By pass normal active process
//--------------------------------------------------
bit UserInterfaceGetActiveByPassStatus(void)
{
//Eric_20180307 : Delete
//        if((GET_OSD_STATE() == _MENU_COLOR_FORMAT) || (GET_OSD_STATE() == _MENU_COLOR_FORMAT_ADJUST))
//        {
//            return _FALSE;
//        }

    if(GET_OSD_STATE() != _MENU_NONE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Define Whether Cable Status Should Reset
// Input Value  : None
// Output Value : _TRUE => Reset
//--------------------------------------------------
bit UserInterfaceGetCableResetStatus(void)
{
    if((SysSourceGetCableStatusChange(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE) &&
       ((!(SysModeGetModeState() == _MODE_STATUS_SEARCH)) || (SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE)))
    {
        SET_FORCE_POW_SAV_STATUS(_FALSE);

        if(SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT)
        {
            SysSourceSwitchInputPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Forced Power Saving Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetForcePSStatus(void)
{
    return (GET_FORCE_POW_SAV_STATUS());
}

//--------------------------------------------------
// Description  : User Check Into Power Saving
// Input Value  : None
// Output Value : True --> User Check Ready to Power Saving
//--------------------------------------------------
bit UserInterfaceGetIntoPSStatus(void)
{
    if(ScalerOsdGetOsdEnable() == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : User Setting Fake Power Saving
// Input Value  : None
// Output Value : _USER_FORCE_FAKE_PS --> User Set Power Status into Fake Power Saving
//                _USER_FORCE_POWER_SAVING    --> User Set Power Status into Power saving
//--------------------------------------------------
EnumUserForceFakePS UserInterfaceGetFakePSStatus(void)
{
    return _USER_FORCE_POWER_SAVING;
}

//--------------------------------------------------
// Description  : User Setting Fake Power Status
// Input Value  : None
// Output Value : _USER_FORCE_FAKE_POWER_OFF ==> Fake Power Off
//                _USER_FORCE_POWER_OFF ==> Power off
//--------------------------------------------------
EnumUserForceFakePowerOff UserInterfaceGetFakePowerOffStatus(void)
{
    return _USER_FORCE_POWER_OFF;
}

//--------------------------------------------------
// Description  : Check Whther ADC Data is Reasonable
// Input Value  : LOAD or SAVE
// Output Value : _TRUE => Reasonable
//--------------------------------------------------
bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType)
{
    switch(enumNvramCheckType)
    {
#if(_VGA_SUPPORT == _ON)
        case _CHECK_ADC_LOAD:

            if(g_stAdcData.ucAdcPGA >= 0xF0)
            {
                // Assign Prefered Value
                g_stAdcData.ucAdcPGA = 8;
            }

            break;

        case _CHECK_ADC_SAVE:

            if(g_stAdcData.ucAdcPGA >= 0xF0)
            {
                return _FAIL;
            }
            break;
#endif

        case _CHECK_SYSTEM_DATA_LOAD:
        case _CHECK_SYSTEM_DATA_SAVE:
        case _CHECK_MODE_USER_DATA_LOAD:
        case _CHECK_MODE_USER_DATA_SAVE:

            break;

        default:
            break;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get backlight staus when performing display setting
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserInterfaceGetDisplaySettingBacklightAction(void)
{
if((_PANEL_STYLE == _PANEL_DPTX) || (_PANEL_STYLE == _PANEL_VBO))
    return _DISABLE;

else
{
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() != UserInterfaceGetRotationDegree()) ||
       (GET_ROT_DISP_SIZE() != UserInterfaceGetRotationDisplayType()))
    {
        return _DISABLE;
    }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_ROT_TYPE() != _ROT_DISABLE)
#endif
    {
        if(GET_DISP_LATENCY_RATIO() != UserInterfaceGetDisplayLatencyRatio())
        {
            return _DISABLE;
        }
    }
#endif

    return _ENABLE;

}
}

//--------------------------------------------------
// Description  : Get OSD Color Format
// Input Value  : None
// Output Value : Color Format
//--------------------------------------------------
EnumColorSpace UserInterfaceGetColorFormat(void)
{
    EnumColorSpace enumColorSpace = ScalerColorGetColorSpace();

#if(_COLOR_FORMAT_CONVERT == _ON)
    switch(SysSourceGetSourceType())
    {
        case _SOURCE_VGA:
        case _SOURCE_DVI:
            enumColorSpace = GET_OSD_COLOR_FORMAT();
            break;

        default:
            break;
    }
#endif

    if(ScalerColorGetColorSpaceRGB(enumColorSpace) == _TRUE)
    {
        return _COLOR_SPACE_RGB;
    }
    else
    {
        return _COLOR_SPACE_YPBPR;
    }
}

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HP Source Switch Event Time
// Input Value  : Source Scan Type
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetHpSourceSwitchOsdEventTime(BYTE ucSourceScanType)
{
    ucSourceScanType = ucSourceScanType;
    return 0;
}
#endif

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Overscan
// Input Value  : Current Input Timing
// Output Value : Modified Input Timing
//--------------------------------------------------
bit UserInterfaceGetOverScanStatus(void)
{
    bit bDoOverScan = _FALSE;
    BYTE ucTemp = 0;
    WORD code tusOverscanEnTable[][3] =
    {
        // VFreq, HWidth, VHeight,
        {600,  640,  480},    // 480p
        {600,  720,  480},    // 480p
        {600,  960,  480},    // 480p
        {600, 1440,  480},    // 480p

        {500,  720,  576},    // 576p
        {500,  768,  576},    // 576p
        {500,  960,  576},    // 576p
        {500, 1280,  576},    // 576p
        {500, 1440,  576},    // 576p
        {500, 1280,  720},    // 720p
        {600, 1280,  720},    // 720p
        {500, 1920,  1080},   // 1080p
        {600, 1920,  1080},   // 1080p

        // Don't delete it, and place it at last.
        {  0,    0,    0},
    };

    if(GET_OSD_OVERSCAN_STATUS() == _OFF)
    {
        return _FALSE;
    }

    // Decide whether to do over scan
    switch(SysSourceGetSourceType())
    {
#if(_OVERSCAN_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Interlaced and YUV Timing Always do overscan
            if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
            {
                bDoOverScan = _TRUE;
                break;
            }

            if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_RGB)
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(GET_INPUT_TIMING_VFREQ() - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(GET_INPUT_TIMING_HWIDTH() - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (GET_INPUT_TIMING_VHEIGHT() == tusOverscanEnTable[ucTemp][2]))
                {
                    bDoOverScan = _TRUE;
                    break;
                }

                ucTemp++;
            }

            break;
#endif // End of #if(_OVERSCAN_VGA_SUPPORT == _ON)

#if(_OVERSCAN_DVI_SUPPORT != _ON)
        case _SOURCE_DVI:
            break;
#endif

#if(_OVERSCAN_HDMI_SUPPORT != _ON)
        case _SOURCE_HDMI:
            break;
#endif

#if(_OVERSCAN_DP_SUPPORT != _ON)
        case _SOURCE_DP:
            break;
#endif

        default:
#if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))
            // Interlaced and YUV Timing Always do overscan
            if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
            {
                bDoOverScan = _TRUE;
                break;
            }

            if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _TRUE)
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(GET_INPUT_TIMING_VFREQ() - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(GET_INPUT_TIMING_HWIDTH() - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (GET_INPUT_TIMING_VHEIGHT() == tusOverscanEnTable[ucTemp][2]))
                {
                    bDoOverScan = _TRUE;
                    break;
                }

                ucTemp++;
            }
#endif // End of #if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))
            break;
    }

    return bDoOverScan;
}
#endif // End of #if(_OVERSCAN_SUPPORT == _ON)

#if(_ASPECT_RATIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Aspect Ratio
// Input Value  : None
// Output Value : aspect ration type
//--------------------------------------------------
EnumAspectRatioType UserInterfaceGetAspectRatioType(void)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE())
    {
        case _OSD_ASPECT_RATIO_16_BY_9:
        case _OSD_ASPECT_RATIO_4_BY_3:
        case _OSD_ASPECT_RATIO_5_BY_4:

            return _ASPECT_RATIO_FIXED;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
        case _OSD_ASPECT_RATIO_ORIGIN:

            return _ASPECT_RATIO_ORIGIN;
        case _OSD_ASPECT_RATIO_USER:
            return _ASPECT_RATIO_ORIGIN;
#endif

        default:
        case _OSD_ASPECT_RATIO_FULL:

            return _ASPECT_RATIO_FULL;
    }
}

//--------------------------------------------------
// Description  : Get user H/V aspect ratio values
// Input Value  : enumSelRegion --> select region
//                usHRatio, usVRatio --> aspect ratio
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE())
    {
        default:
            break;

        case _OSD_ASPECT_RATIO_16_BY_9:
            *pusHRatio = 16;
            *pusVRatio = 9;
            break;

        case _OSD_ASPECT_RATIO_4_BY_3:
            *pusHRatio = 4;
            *pusVRatio = 3;
            break;

        case _OSD_ASPECT_RATIO_5_BY_4:
            *pusHRatio = 5;
            *pusVRatio = 4;
            break;
    }
}

//--------------------------------------------------
// Description  : User defined aspect ratio process
// Input Value  : select region
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAspectRatio(void)
{
}

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//--------------------------------------------------
// Description  : User defined minimum dvheight for aspect ratio
//                use 1:1 for example
// Input Value  : None
// Output Value : usMinDvheight
//--------------------------------------------------
WORD UserInterfaceGetAspectRatioMinDVHeight(void)
{
    WORD usMinDvheight = (GET_INPUT_TIMING_VHEIGHT() < GET_MDOMAIN_OUTPUT_VHEIGHT()) ? GET_INPUT_TIMING_VHEIGHT() : GET_MDOMAIN_OUTPUT_VHEIGHT();
    // return 0 if disable the function
    return usMinDvheight;
}
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get aspect original mode ratio
// Input Value  : select region
// Output Value : Retion display ratio in aspect ratio original mode (0x00 ~ 0xFF)
//--------------------------------------------------
BYTE UserInterfaceGetAspectRatioOriginalRatio(void)
{
    return 0xFF;
}

//--------------------------------------------------
// Description  : Get reduced aspect ratio in original mode
// Input Value  : select region
// Output Value : Retion display ratio in aspect ratio original mode (0x00 ~ 0xFF)
//--------------------------------------------------
BYTE UserInterfaceGetAspectRatioOriginalRatioSmall(void)
{
    if(GET_OSD_ASPECT_RATIO_TYPE() == _OSD_ASPECT_RATIO_USER)
    {
        return 0xCC;
    }
    else
    {
        return 0xFF;
    }
}
#endif
#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get current rotation degree
// Input Value  : None
// Output Value : rotation degree
//--------------------------------------------------
EnumRotationType UserInterfaceGetRotationDegree(void)
{
    switch(GET_OSD_DISP_ROTATE())
    {
        default:
        case _DISP_ROTATE_0:
            return _ROT_DISABLE;

#if (_DISPLAY_ROTATION_90_SUPPORT == _ON)
        case _DISP_ROTATE_90:
            return _ROT_CW90;
#endif
#if (_DISPLAY_ROTATION_180_SUPPORT == _ON)
        case _DISP_ROTATE_180:
            return _ROT_CW180;
#endif
#if (_DISPLAY_ROTATION_270_SUPPORT == _ON)
        case _DISP_ROTATE_270:
            return _ROT_CW270;
#endif
#if (_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_HOR_MIRROR:
            return _ROT_HOR_MIRROR;
#endif
#if (_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_VER_MIRROR:
            return _ROT_VER_MIRROR;
#endif
    }
}

//--------------------------------------------------
// Description  : Get current rotation type
// Input Value  : None
// Output Value : rotation type
//--------------------------------------------------
EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void)
{
    switch(GET_OSD_DISP_ROTATION_SIZE_TYPE())
    {
        default:
        case _OSD_ROTATE_DISPLAY_FULL:
            return _ROT_FULL;

        case _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL:
            return _ROT_PIXEL_BY_PIXEL;

        case _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO:
            return _ROT_KEEP_SRC_ASPECT_RATIO;
    }
}
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Display Latency Ratio
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetDisplayLatencyRatio(void)
{
    switch(GET_OSD_LATENCY())
    {
        default:
            break;

        case _LATENCY_L:
            return 0;   // 0%

        case _LATENCY_M:
            return 50;  // 50%

        case _LATENCY_H:
            return 100; // 100%
    }

    return 0;
}
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Max/Min Freq according to latency
// Input Value  : None
// Output Value : max/min freq
//--------------------------------------------------
void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq)
{
    pstDVCustomizedFreq = pstDVCustomizedFreq;

#if(_MN_FINE_TUNE_LASTLINE_SUPPORT == _ON)
    if((SysSourceGetInputPort() == _A0_INPUT_PORT) ||
       (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
        pstDVCustomizedFreq->b1FORCETOFREERUN = _ENABLE;
    }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    switch (GET_OSD_LATENCY())
    {
        default:
        case _LATENCY_H:
        case _LATENCY_M:
        case _LATENCY_L:

            pstDVCustomizedFreq->usMaxFreq = _PANEL_MAX_FRAME_RATE;
            pstDVCustomizedFreq->usTypFreq = _PANEL_TYP_FRAME_RATE;
            pstDVCustomizedFreq->usMinFreq = _PANEL_MIN_FRAME_RATE;
            break;
    }
#endif
}
#endif

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OD enable status
// Input Value  : None
// Output Value : function enable status
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void)
{
    return GET_OSD_OD_STATUS();
}
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
//--------------------------------------------------
// Description  : Get DDR3 Phase From GPIO or DDCCI command
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUpdateDDR3PhaseData(void)
{
    StructDDR3PhaseInfo stUserVedorDdr3PhaseData = {_DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1, _DDR3_READ_DQ_DLYN_TAP};
    ScalerPLLGetDDR3PhaseData(&stUserVedorDdr3PhaseData);
}
#endif

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
//--------------------------------------------------
// Description  : User Custom Check Proc when System Eeprom Read
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserInterfaceSystemEepromReadCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : User Custom Check Proc when System Eeprom Write
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserInterfaceSystemEepromWriteCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;
    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Modify display Timing Based on User Requirement
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayInitialization(void)
{
}

//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustInputTiming(void)
{
}

#if(_UNDERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceAdjustUnderScan(void)
{
    if((GET_INPUT_TIMING_HWIDTH() == 640) && (GET_INPUT_TIMING_VHEIGHT() == 350))
    {
        SET_UNDERSCAN_VHEIGHT(400);
        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Modify Display Timing Based on User Requirement
// Input Value  : Current Display Timing Info
// Output Value : Modified Display Timing
//--------------------------------------------------
void UserInterfaceAdjustDisplayTiming(void)
{
    if (_PANEL_STYLE == _PANEL_LVDS)
    {
        // Check display format resolution according to LVDS port count
        SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + (GET_MDOMAIN_OUTPUT_HSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
        SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() - (GET_MDOMAIN_OUTPUT_HWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
        SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HBSTART() + (GET_MDOMAIN_OUTPUT_HBSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
        SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HBWIDTH() - (GET_MDOMAIN_OUTPUT_HBWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    }
}

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
//--------------------------------------------------
// Description  : User Judge if Quantization Range is Full or Limited
// Input Value  : EnumDisplayRegion --> display region
//                ucQuanRange --> quantization status
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization)
{
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        switch(enumColorRGBQuantization)
        {
            case _RGB_QUANTIZATION_FULL_RANGE:
            default:

                return _FALSE;

            case _RGB_QUANTIZATION_LIMIT_RANGE:
            case _RGB_QUANTIZATION_DEFAULT_RANGE:
            case _RGB_QUANTIZATION_RESERVED:

                return _TRUE;
        }
    }
    else
#endif
    {
        switch(enumColorRGBQuantization)
        {
            case _RGB_QUANTIZATION_FULL_RANGE:
            case _RGB_QUANTIZATION_DEFAULT_RANGE:
            case _RGB_QUANTIZATION_RESERVED:
            default:

                return _FALSE;

            case _RGB_QUANTIZATION_LIMIT_RANGE:

                return _TRUE;
        }
    }
}
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Judge if YCC Quantization Range is Full or Limited
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumColorYCCQuantization enumColorYCCQuantization)
{
    return (enumColorYCCQuantization == _YCC_QUANTIZATION_FULL_RANGE);
}
#endif

//--------------------------------------------------
// Description  : Set Color in pass normal active process
// Input Value  : None
// Output Value : void
//--------------------------------------------------
void UserInterfaceAdjustActiveByPassColorProc(void)
{
    return;
}

//--------------------------------------------------
// Description  : Set User Required Color Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustColorProc(void)
{
//    if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_OTHER_RESET))
    if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_SETUP_RESET))
    {
        // Set Color Conversion
        switch(SysSourceGetInputPort())
        {
            case _A0_INPUT_PORT:

                SET_OSD_COLOR_FORMAT(GET_VGA_COLOR_FORMAT_STATUS());

                break;

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
            case _D0_INPUT_PORT:
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
            case _D1_INPUT_PORT:
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DVI_PORT)
            case _D2_INPUT_PORT:
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DVI_PORT)
            case _D3_INPUT_PORT:
#endif
#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) ||\
    (_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DVI_PORT))
                SET_OSD_COLOR_FORMAT(GET_DVI_COLOR_FORMAT_STATUS());
                break;
#endif

            default:

                if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _TRUE)
                {
                    SET_OSD_COLOR_FORMAT(_COLOR_SPACE_RGB);
                }
                else
                {
                    SET_OSD_COLOR_FORMAT(_COLOR_SPACE_YPBPR);
                }

                break;
        }
    }

    // Adjust Color Space
    SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);

    // Adjust UltraVivid
#if(_ULTRA_VIVID_SUPPORT == _ON)
    UserInterfaceAdjustUltraVividProc(_DB_APPLY_NO_POLLING);
#else

    // Adjust Y-Peaking
#if(_YPEAKING_SUPPORT == _ON)
    UserInterfaceAdjustYpeaking();
#endif

#endif

    // Adjust Sharpness
#if(_SHARPNESS_SUPPORT == _ON)
    UserCommonAdjustSharpness(SysSourceGetInputPort());
#endif

    // Adjust Backlight
    UserAdjustBacklight(GET_OSD_BACKLIGHT());

    // Adjust Brightness & Contrast
    RTDNVRamLoadBriCon(SysSourceGetSourceType());

    // Adjust Transparency
    ScalerOsdSetTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // User Adjust Background Color
    ScalerDDomainBackgroundSetColor(0, 0, 0);

#if(_PCM_FUNCTION == _ON)
#if(_HDR10_SUPPORT == _ON)
    if((GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE) || (GET_OSD_HDR_MODE() == _HDR10_MODE_FORCE_2084))
#else
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
#endif
    {
#if(_BRIGHTNESS_SUPPORT == _ON)
        ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
        {
            ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
        }
        else
        {
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
        }
#endif  // End of #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))

    }
    else
#endif  // End of #if(_PCM_FUNCTION == _ON)
    {

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

        // Adjust Gamma On/Off
#if(_GAMMA_FUNCTION == _ON)
        if(GET_OSD_GAMMA() == _GAMMA_OFF)
        {
            UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

#if(_RGB_GAMMA_FUNCTION == _ON)
            ScalerColorRGBOutputGammaEnable(_FUNCTION_OFF);
#endif
        }
        else
        {
            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);

#if(_RGB_GAMMA_FUNCTION == _ON)
            ScalerColorRGBOutputGammaEnable(_FUNCTION_ON);
#endif
        }
#endif  // End of #if(_GAMMA_FUNCTION == _ON)

        // Adjust Hue & Saturation
#if(_GLOBAL_HUE_SATURATION == _ON)
        if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_VIVID)
        {
            UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), 140);
        }
        else
        {
            UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
        }
#endif  // End of #if(_GLOBAL_HUE_SATURATION == _ON)

        // Adjuset Brightness & Contrast
#if(_BRIGHTNESS_SUPPORT == _ON)
        UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(GET_OSD_CONTRAST());
#endif
    }

    // Adjust ICM On/Off
#if(_ICM_SUPPORT == _ON)
    if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_STANDARD)
    {
        ScalerColorICMEnable(_FUNCTION_OFF);
    }
    else
    {
        ScalerColorICMEnable(_FUNCTION_ON);
    }
#endif

    // Adjust DCC On/Off
#if(_DCC_FUNCTION == _ON)
    if((GET_OSD_COLOR_EFFECT() == _COLOREFFECT_STANDARD) || (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_USER))
    {
        ScalerColorDCCEnable(_FUNCTION_OFF);
    }
    else
    {
        ScalerColorDCCEnable(_FUNCTION_ON);
    }
#endif

#if(_OD_SUPPORT == _ON)
    ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
    ScalerODEnable(GET_OSD_OD_STATUS());
#endif

    // Adjust DCC Table
#if(_DCC_FUNCTION == _ON)
    UserAdjustDCC(GET_OSD_COLOR_EFFECT());
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    if(GET_OSD_PANEL_UNIFORMITY() == _OFF)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
    }
    else
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
    }
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    // Adjust Highlight Window Effect Space
    UserAdjustHighLightWindowEffectSpace();

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    if(GET_OSD_ASPECT_RATIO_TYPE() != _OSD_ASPECT_RATIO_ORIGIN)
#endif
    {
        if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
        {
            ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_NONE);
        }
        else
        {
            UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
            ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_NONE);
        }
    }
#endif  // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_CIZGI_ENABLE_DICOM_CALIBRATION == _ON)	
if(g_stOsdUserData.b1CalibFlag == 1)
	{
		UserAdjustGamma(GET_OSD_GAMMA());
	}
#endif
}


#if(_ULTRA_VIVID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustUltraVivid(void)
{
    BYTE ucUltraVividStatus = GET_OSD_ULTRA_VIVID_STATUS();

    // Wait for D-domain DB apply ready
    ScalerColorWaitDDomainDBApply();

#if(_HDR10_SUPPORT == _ON)
    if((UserCommonHDRGetHDR10Status() == _HDR10_ON) && (GET_OSD_HDR_SHARPNESS() == _ON))
    {
        ScalerColorUltraVividAdjust(tCOLOR_ULTRAVIVID_SETTING_HDR, GET_CURRENT_BANK_NUMBER());
    }
    else
#endif
    {
        if(ucUltraVividStatus != _ULTRA_VIVID_OFF)
        {
            ScalerColorUltraVividAdjust(tCOLOR_ULTRAVIVID_SETTING_TABLE[ucUltraVividStatus - 1], GET_CURRENT_BANK_NUMBER());
        }
        else
        {
            ScalerColorUltraVividEnable(_FUNCTION_OFF, _DB_APPLY_NONE);
        }
    }
}

//--------------------------------------------------
// Description  : UltraVivid Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustUltraVividProc(EnumDBApply enumDBApply)
{
#if(_HDR10_SUPPORT == _ON)
    if((UserCommonHDRGetHDR10Status() == _HDR10_ON) && (GET_OSD_HDR_SHARPNESS() == _ON))
    {
        UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), enumDBApply);
    }
    else
#endif
    {
        if(GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_OFF)
        {
            UserCommonAdjustUltraVivid(_FUNCTION_OFF, UserCommonInterfaceGetColorFormat(), enumDBApply);
        }
        else
        {
            UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), enumDBApply);
        }
    }
}
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Sharpness Coef
// Input Value  : SU Coef Type
// Output Value : SU Coef
//--------------------------------------------------
code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    switch(enumSUCoefType)
    {
#if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))
        case _H_V_SU_128TAPS_NORMAL:
            return tSCALE_128TAPS_NORMAL_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif

#if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
        case _H_V_SU_96TAPS_NORMAL:
            return tSCALE_96TAPS_NORMAL_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif

#if(_HSU_128TAPS_SUPPORT == _ON)
        case _H_SU_128TAPS_1_TO_1:
            return tSCALE_128TAPS_1to1_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif

#if(_HSU_96TAPS_SUPPORT == _ON)
        case _H_SU_96TAPS_1_TO_1:
            return tSCALE_96TAPS_1to1_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif
        default:
            return _NULL_POINTER;
    }
}

//--------------------------------------------------
// Description  : Get Sharpness Coef BankNum
// Input Value  : None
// Output Value : BankNum
//--------------------------------------------------
BYTE UserInterfaceGetSharpnessCoefBankNum(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

//--------------------------------------------------
// Description  : User Bypass Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSharpnessBypassCheck(void)
{
    return _FALSE;
}
#endif

#if(_DCR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust DCR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustDCRHandler(void)
{
    if(GET_OSD_DCR_STATUS() == _ON)
    {
#if(_LOCAL_DIMMING_SUPPORT == _ON)
        if(UserInterfaceGetLocalDimmingStatus() == _LD_ENABLE)
        {
            BYTE pucDCRResult[_TOTAL_REGION];
            memset(pucDCRResult, 255UL, _TOTAL_REGION);
            ScalerColorDCRLocalDimmingReadResult(pucDCRResult);
        }
        else
#endif
        {
            PDATA_DWORD(0) = ScalerColorDCRReadResult(_DCR_ABOVE_TH1_NUM);
        }
    }
}
#endif // End of #if(_DCR_SUPPORT == _ON)

#if(_DCC_HISTOGRM_INFO == _ON)
//--------------------------------------------------
// Description  : User Adjust DCC Histogram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDCCHistogramHandler(void)
{
}
#endif // End of #if(_DCC_HISTOGRM_INFO == _ON)

#if(_IAPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust IAPS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustIAPSHandler(void)
{
}
#endif // End of #if(_IAPS_SUPPORT == _ON)

//--------------------------------------------------
// Description  : OSD Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdPowerOnInitial(void)
{
#if(_SIX_COLOR_SUPPORT == _ON)
    BYTE ucIndex = 0;
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    // Uniformity parameters setting
    ScalerColorPanelUniformityInitial(_PANEL_UNIFORMITY_MULTI_LUT_MODE);

    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
    {
        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
    }
#endif

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);

#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        UserAdjustPCM(GET_OSD_PCM_STATUS());
    }
    else
#endif
    {
#if(_GAMMA_FUNCTION == _ON)
        // Adjust Gamma Table
        UserAdjustGamma(GET_OSD_GAMMA());
#endif
    }

#if(_RGB_3D_GAMMA == _ON)
    UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
    UserAdjustSCM(GET_OSD_COLOR_EFFECT());
#endif

    // Adjust ICM Table
#if(_ICM_SUPPORT == _ON)
    UserAdjustICM(GET_OSD_COLOR_EFFECT());
#endif

    // Adjust DCR Threshold & Source
#if(_DCR_SUPPORT == _ON)

#if(_DCR_BIT_MODE == _DCR_GEN_1_0_10BIT)
    ScalerColorDCRAdjust(_DCR_THESHOLD1, _DCR_THESHOLD2, _MEASURE_AVERAGE);
#elif((_DCR_BIT_MODE == _DCR_GEN_0_0_8BIT) || (_DCR_BIT_MODE == _DCR_GEN_0_1_8BIT))
    ScalerColorDCRAdjust((_DCR_THESHOLD1 >> 2), (_DCR_THESHOLD2 >> 2), _MEASURE_AVERAGE);
#endif

#endif

    // Adjust Six Color Hue / Saturation
#if(_SIX_COLOR_SUPPORT == _ON)
    if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_USER)
    {
        for(ucIndex = 0; ucIndex < 6; ucIndex++)
        {
            SET_OSD_SIX_COLOR(ucIndex);
            OsdDisplaySixColorGetOneColor(ucIndex);
            ScalerColorSixColorAdjust(ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
        }

        ScalerColorSixColorInitial();
    }
#endif

#if(_OD_SUPPORT == _ON)
    UserAdjustOD();
#endif

    // Adjust Highlight Window Border
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWBorderAdjust(_HL_WIN_BORDER_SIZE, 255, 0, 0);

    ScalerColorHLWBorderEnable(_ON, _ON, _ON, _ON);
#endif

#if(_SDR_TO_HDR_SUPPORT == _ON)
    UserAdjustSDRToHDR(GET_OSD_SDR_TO_HDR());
#endif
}


//--------------------------------------------------
// Description  : OSD Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdActiveProc(void)
{
    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
    {
        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        UserCommonNVRamSaveSystemData();
    }

    if(UserInterfaceGetActiveByPassStatus() == _FALSE)
    {
        // DDCCI switch to active port
        UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());

        if(GET_FAIL_SAFE_MODE() == _TRUE)
        {
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG);
        }
        else
        {
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_ACTIVE_DO_ONE_TIME_MSG);
        }
    }

#if((_OD_SUPPORT == _ON) && (_FREESYNC_SUPPORT == _ON))
    UserAdjustOD();
#endif

#if(_FREEZE_SUPPORT == _ON)
    UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
#endif

    ScalerDDomainBackgroundEnable(_DISABLE);
}

//--------------------------------------------------
// Description  : OSD Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdResetProc(void)
{
    // Disable OSD
    if(GET_OSD_LOGO_ON() == _OFF)
    {
        OsdDispDisableOsd();
    }

    SET_OSD_LOGO_ON(_OFF);

    // Cancel Timer Events
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_AUTO_COLOR);
#if (_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
#endif
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
	ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);
}


#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check ModeIndex
// Input Value  : System ModeIndex
// Output Value : ModeIndex
//--------------------------------------------------
BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex)
{
    if((ucModeIndex == _MODE_640x480_60HZ) || (ucModeIndex == _MODE_720x480_60HZ_GTF) || (ucModeIndex == _MODE_720x480p_60HZ))
    {
        if(GET_INPUT_TIMING_VSYNCWIDTH() <= 4)
        {
            ucModeIndex = _MODE_640x480_60HZ;

            DebugMessageAnalog("Detected by Special Case to 640x480-60", _MODE_640x480_60HZ);
        }
        else if((GET_INPUT_TIMING_H_POLARITY() == _FALSE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_720x480_60HZ_GTF;

            DebugMessageAnalog("Detected by Special Case to 720x480-60_GTF", _MODE_720x480_60HZ_GTF);
        }
        else
        {
            ucModeIndex = _MODE_720x480p_60HZ;

            DebugMessageAnalog("Detected by Special Case to 720x480-60", _MODE_720x480p_60HZ);
        }
    }

    if((ucModeIndex == _MODE_720x400_70HZ) || (ucModeIndex == _MODE_640x400_70HZ))
    {
        if((GET_INPUT_TIMING_H_POLARITY() == _TRUE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_640x350_70HZ;

            DebugMessageAnalog("Detected by Special Case to _MODE_640x350_70HZ", _MODE_640x350_70HZ);
        }
    }

    if((ucModeIndex == _MODE_640x400_85HZ) || (ucModeIndex == _MODE_720x400_85HZ))
    {
        if((GET_INPUT_TIMING_H_POLARITY() == _TRUE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_640x350_85HZ;
        }

        DebugMessageAnalog("Detected by Special Case to _MODE_640x350_85HZ", _MODE_640x350_85HZ);
    }

    return ucModeIndex;
}

//--------------------------------------------------
// Description  : Check Load Mode Table Value
// Input Value  : None
// Output Value : _TURE -> Force Load Mode Table Value
//--------------------------------------------------
bit UserInterfaceGetLoadModeTableDefaultStatus(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check VGA First Auto Config
// Input Value  : None
// Output Value : _TRUE => Do Auto Config
//--------------------------------------------------
bit UserInterfaceGetFirstAutoConfigStatus(void)
{
    if((GET_VGA_MODE_DO_FIRST_AUTO() == _TRUE) &&
       (GET_INPUT_TIMING_HWIDTH() > 720))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Percentage of AutoConfig
// Input Value  : Percentage
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage)
{
    ucAutoPercentage = ucAutoPercentage;
    g_usAdjustValue = ucAutoPercentage;
}

#if(_VGA_FORCE_DISPLAY == _ON)
//--------------------------------------------------
// Description  : VGA Mode Search User Flow
// Input Value  : None
// Output Value : Mode Number
//--------------------------------------------------
BYTE UserInterfaceModeSearchModeVGA(void)
{
    return 0;
}
#endif

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for V position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSkipAutoVpos(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for H position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSkipAutoHpos(void)
{
    return _FALSE;
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#if(_MHL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User RCP Handler
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode)
{
    // Check RCP Key Code
    switch(ucKeyCode)
    {
#if(_AUDIO_SUPPORT == _ON)
        case _MHL_RCP_VOLUME_UP:

            if(GET_OSD_VOLUME() < 100)
            {
                SET_OSD_VOLUME(GET_OSD_VOLUME() + 1);
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;

        case _MHL_RCP_VOLUME_DOWN:

            if(GET_OSD_VOLUME() > 0)
            {
                SET_OSD_VOLUME(GET_OSD_VOLUME() - 1);
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;

        case _MHL_RCP_MUTE:
        case _MHL_RCP_MUTE_FUNCTION:

            SET_OSD_VOLUME_MUTE(!GET_OSD_VOLUME_MUTE());

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioMuteSwitch();
            }
            break;

        case _MHL_RCP_RESTORE_VOLUME_FUNCTION:

            SET_OSD_VOLUME(50);

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;
#endif

        default:
            return _FALSE;
    }

    return _TRUE;
}
#endif // End of #if(_MHL_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Decide whether to Enable FREESYNC Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort)
{
    enumSourcePort = enumSourcePort;

#if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
    if(GET_OSD_FREE_SYNC_STATUS() == _TRUE)
    {
        return _FREESYNC_SUPPORT_ON;
    }
#endif
    return _FREESYNC_SUPPORT_OFF;
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : RCP Key Code
// Output Value : DP_VERSION_1_1 or DP_VERSION_1_2
//--------------------------------------------------
EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D0)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_3;
            }
            break;

#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D1)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_3;
            }
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D1)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_3;
            }
            break;
#endif


#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D6)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_3;
            }
            break;
#endif
        default:

            break;
    }

    return _DP_VERSION_1_1;
}

//--------------------------------------------------
// Description  : Get DP Lane Count
// Input Value  : InputPort
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            return UserCommonNVRamGetSystemData(_DP_D0_LANES);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            return UserCommonNVRamGetSystemData(_DP_D1_LANES);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:
            return UserCommonNVRamGetSystemData(_DP_D2_LANES);
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:
            return UserCommonNVRamGetSystemData(_DP_D6_LANES);
#endif

        default:
            break;
    }

    return _DP_LINK_4_LANE;
}

//--------------------------------------------------
// Description  : Get Dp MST Capable Port
// Input Value  : None
// Output Value : _DP_MST_RX0 or _DP_MST_RX1
//--------------------------------------------------
EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void)
{
#if(_DP_MST_SUPPORT == _OFF)

    return _DP_MST_NO_PORT;

#endif

    if((SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT) && (GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP))
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        if((GET_OSD_DP_MST() == _MST_D0) && (SysSourceGetInputPort() == _D0_INPUT_PORT))
        {
            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_MST(_MST_OFF);

                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX0_PORT;
            }
        }
        else
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        if((GET_OSD_DP_MST() == _MST_D1) && (SysSourceGetInputPort() == _D1_INPUT_PORT))
        {
            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_MST(_MST_OFF);

                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX1_PORT;
            }
        }
        else
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
        if((GET_OSD_DP_MST() == _MST_D6) && (SysSourceGetInputPort() == _D6_INPUT_PORT))
        {
            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_MST(_MST_OFF);

                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX6_PORT;
            }
        }
        else
#endif
        {
            return _DP_MST_NO_PORT;
        }
    }

    return _DP_MST_NO_PORT;
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetDpCloneOutputStatus(void)
{
    if(GET_OSD_CLONE_MODE() == _OFF)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) || (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
//--------------------------------------------------
// Description  : User Select Externel DP Switch
// Input Value  : None
// Output Value : Only Return _D0_INPUT_PORT or _D6_INPUT_PORT
//--------------------------------------------------
BYTE UserInterfaceGetDpSwitchSelectPort(void)
{
    return _D0_INPUT_PORT;
}
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : User flow for embedded DP switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceEmbeddedDpSwitch(void)
{
    UserAdjustEmbeddedDpSwitch();
}
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : User Report HDMI +5V Status
// Input Value  : D0/D1/D2 Port
// Output Value : _TURE --> +5V exist
//--------------------------------------------------
bit UserInterfaceGetHdmi5VStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _TRUE;
        case _D1_INPUT_PORT:
            return _TRUE;
        case _D2_INPUT_PORT:
            return _TRUE;
        default:
            return _TRUE;
    }
}
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
//--------------------------------------------------
// Description  : User check search is finish or not
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit UserInterfaceAdjustOsdCheckTotalSearchFinish(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Determine the search time of each source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustSourceSearchTime(void)
{
}

//--------------------------------------------------
// Description  : User Report Eizo Search Finish Time
// Input Value  : None
// Output Value : Search Finish Time
//--------------------------------------------------
WORD UserInterfaceGetEizoSearchFinishTime(void)
{
    return 0;
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Determine whether to User is Ready to play audio
// Input Value  : None
// Output Value : _TRUE => Free to Play
//--------------------------------------------------
bit UserInterfaceGetAudioReadyToPlayStatus(void)
{
    if(UserInterfaceGetAudioMuteStatus() != _ON)
    {
#if(_EMBEDDED_DAC_SUPPORT == _ON)
        if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
#endif
        {
#if(_LINE_IN_SUPPORT == _ON)
            if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
            {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
                {
#if((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN))
                    return _TRUE;
#endif
                }
#endif
                if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) ||
                   ((SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING) && (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK)))
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(UserInterfaceGetAudioSource() == _DIGITAL_AUDIO)
                {
                    if(ScalerAudioGetAudioDetected(SysSourceGetInputPort()) == _TRUE)
                    {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                        if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
                        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                            if(ScalerAudioGetDigitalAudioSource(SysSourceGetInputPort()) == _DIGITAL_AUDIO_SOURCE_DP)
                            {
                                // When Fixed Port, should not play DP Audio at different port
                                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetAudioPlaybackPort() == SysSourceGetInputPort()))
                                {
                                    return _TRUE;
                                }
                            }
#endif
                        }
#endif
                        if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) || (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK))
                        {
                            return _TRUE;
                        }
                    }
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User OSD Get Audio Source
// Input Value  : None
// Output Value : _DIGITAL_AUDIO or _LINE_IN_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserInterfaceGetAudioSource(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
    {
        return _DIGITAL_AUDIO;
    }
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        return _LINE_IN_AUDIO;
    }
#endif

    switch(SysSourceGetInputPort())
    {
        case _A0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
        case _D0_INPUT_PORT:
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
        case _D1_INPUT_PORT:
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
        case _D2_INPUT_PORT:
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
        case _D3_INPUT_PORT:
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
        case _D4_INPUT_PORT:
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
        case _D5_INPUT_PORT:
#endif

#if(_LINE_IN_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            if(UserInterfaceGetAudioStandAloneStatus() == _FALSE)
#endif
            {
                // Don't switch audio source if input source is not found
                if(SysSourceGetSourceType() == _SOURCE_NONE)
                {
                    return ScalerAudioGetInputSource();
                }
            }

            return _LINE_IN_AUDIO;
#else
            return _NO_AUDIO_SOURCE;
#endif // End of #if(_LINE_IN_SUPPORT == _ON)

        default:

#if(_LINE_IN_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            // Don't Switch Audio Source if Line In is Currently Playing unless Digital Source is found
            if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
            {
                if((SysSourceGetSourceType() == _SOURCE_NONE) && (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK) && (ScalerAudioGetInputSource() == _LINE_IN_AUDIO))
                {
                    return _LINE_IN_AUDIO;
                }
            }
#endif
            return GET_OSD_AUDIO_SOURCE();
#else
            return _DIGITAL_AUDIO;
#endif // End of #if(_LINE_IN_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : Get Current Audio Mute Status
// Input Value  : Node
// Output Value : Node
//--------------------------------------------------
bit UserInterfaceGetAudioMuteStatus(void)
{
    return GET_OSD_VOLUME_MUTE();
}

//--------------------------------------------------
// Description  : User Decide whether to play non-LPCM Audio
// Input Value  : None
// Output Value : _ON => Mute Audio
//--------------------------------------------------
bit UserInterfaceGetAudioNonLPCMStatus(void)
{
    if(ScalerAudioLPCMCheckData(SysSourceGetInputPort()) == _TRUE)
    {
#if(_HDMI_SUPPORT == _ON)
        if(SysSourceGetSourceType() == _SOURCE_HDMI)
        {
            if(ScalerAudioLPCMCheckInfo(SysSourceGetInputPort()) == _TRUE)
            {
                return _OFF;
            }
            else
            {
                return _ON;
            }
        }
#endif

        return _OFF;
    }

    return _ON;
}

//--------------------------------------------------
// Description  : Get Current Audio Volume
// Input Value  : None
// Output Value : Current Volume
//--------------------------------------------------
WORD UserInterfaceGetAudioVolume(void)
{
    return UserAdjustAudioVolumeMapping(GET_OSD_VOLUME());
}


#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DAC Output Switch
// Input Value  : None
// Output Value : EnumAudioDACOutput
//--------------------------------------------------
EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void)
{
    return _AUDIO_DAC_OUTPUT_BOTH;
}

//--------------------------------------------------
// Description  : Get if Keep Audio Depop State
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceGetAudioDACKeepDepopState(void)
{
    return _FALSE;
}
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current Audio Stand Alone Status
// Input Value  : enumPowStatus
// Output Value : Node
//--------------------------------------------------
bit UserInterfaceGetAudioStandAloneStatus(void)
{
    return GET_OSD_AUDIO_STAND_ALONE();
}
#endif

//--------------------------------------------------
// Description  : User Audio Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAudioResetProc(void)
{
#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
    {
        // if Currently playing digital audio
        if((SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK) && (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO))
        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if(SysSourceGetAudioPlaybackPort() != SysSourceGetInputPort())
#endif
            {
                DebugMessageAudio("User Audio Reset Process", 0x00);

                SysAudioMuteProc(_ON);
                ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

                SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
            }
        }
    }
    else
#endif
    {
        if(SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK)
        {
            DebugMessageAudio("User Audio Reset Process", 0x00);

            SysAudioMuteProc(_ON);
            ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

            SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
        }
    }
}

//--------------------------------------------------
// Description  : Audio Power Process
// Input Value  : enumPowStatus
// Output Value : Node
//--------------------------------------------------
void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus)
{
    if(enumPowStatus == _POWER_STATUS_NORMAL)
    {
        // Add User interface function

    }
    else if(enumPowStatus == _POWER_STATUS_SAVING)
    {
        // Add User interface function
    }
    else
    {
        // Add User interface function
    }
}

//--------------------------------------------------
// Description  : Control User Audio Mute Process
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAudioAmpMuteProc(bit bMute)
{
    bMute = bMute;

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(UserInterfaceGetAudioDACOutput() == _AUDIO_DAC_OUTPUT_BOTH)
    {
                // External Amp Mute
        PCB_AMP_MUTE((bMute == _ON) ? _AMP_MUTE_ON : _AMP_MUTE_OFF);
        DebugMessageAudio("[Ext.Amp]NormalMuteProc", bMute);
    }
#endif
}


#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
//--------------------------------------------------
// Description  : Swap External Audio Codec Input for Line in
// Input Value  : _TRUE or _FALSE
// Output Value : None
//--------------------------------------------------
void UserInterfaceSwapExternalAudioCodecInput(bit bSwap)
{
    if(bSwap == _TRUE)
    {
        // Swap External Audio Codec Input(L/R)
    }
    else
    {
        // No Swap External Audio Codec Input(L/R)
    }
}
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : User function Before Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // OGC/OCC/DICOM
    {
    }
}

//--------------------------------------------------
// Description  : User function After Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // OGC/OCC/DICOM
    {
    }
}
//--------------------------------------------------
// Description  : User function Backlight Adjust for Calibration
// Input Value  : 0(Min Backlight) ~ 255(Max Backlight)
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBacklight(BYTE ucBacklight)
{
    UserAdjustBacklight(_BACKLIGHT_MIN + ((DWORD)(_BACKLIGHT_MAX() - _BACKLIGHT_MIN) * ucBacklight) / 255);
}
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function Before Calibration Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBeforeDimmingCalibration(void)
{
}

//--------------------------------------------------
// Description  : User function After Calibration Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAfterDimmingCalibration(void)
{
}
#endif

#if(_YPEAKING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Ypeaking Table
// Input Value  : Request Ypeaking Table
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustYpeaking(void)
{
#if(_ULTRA_VIVID_SUPPORT == _ON)
    switch(GET_OSD_ULTRA_VIVID_STATUS())
    {
        case _ULTRA_VIVID_L:
            ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x0E, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
            break;

        case _ULTRA_VIVID_M:
            ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x41, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
            break;

        case _ULTRA_VIVID_H:
        default:
            ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x7E, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
            break;
    }
#else
    // ScalerColorYpeakingAdjust(_YPEAKING_TABLE_MODE, 0x00, _YPEAKING_NO_DIV, tYPEAKING_TABLE[0], _YPEAKING_TABLE_SIZE, GET_CURRENT_BANK_NUMBER());
    ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x41, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
#endif
}
#endif // End of #if(_YPEAKING_SUPPORT == _ON)

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : Get DDC-CI Mode
// Input Value  : None
// Output Value : EnumDDCCIDebugMode:_DEBUG_MODE / _DDCCI_MODE
//--------------------------------------------------
EnumDDCCIDebugMode UserInterfaceGetDdcciMode(void)
{
    return GET_OSD_DDCCI_STATUS();
}
#endif
DWORD UserInterfacePowerSaveTimes(void)
{
	DWORD retTimes = POWER_SAVE_OFF;
	switch (GET_OSD_POWER_SAVE())
	{
	default:
	case POWER_SAVE_5SEC:	retTimes = SEC(5); break;
	case POWER_SAVE_30SEC:	retTimes = SEC(30); break;
	case POWER_SAVE_1MIN:	
	case POWER_SAVE_2MIN:	
	case POWER_SAVE_5MIN:	
	case POWER_SAVE_30MIN:	
	case POWER_SAVE_60MIN:	
	case POWER_SAVE_120MIN:	retTimes = MIN(1); break;
	}
	return retTimes;
}

#if	(_ENABLE_LIGHT_SENSOR == _ON)
bit SuccessInitilizeLightSensor(void)
{
	bit ret = _FALSE;
#if(_LIGHT_SENSOR_TYPE == _LIGHT_TLS2561)
	ret = SuccessInitialize_TLS2561();
#elif(_LIGHT_SENSOR_TYPE == _LIGHT_CM32181)
	ret = SuccessInitialize_CM3281();
#endif
	return ret;
}


void UserInterfaceCheckBacklight(void)
{
	static BYTE wBeforeLux = 0;
	static BYTE u8CheckCount = 0;
	static bit bChangestate = _FALSE;
	WORD realLux = 0;
	BYTE uCurrentLux = 0;
	DWORD uLux = 0;

#if (_LIGHT_SENSOR_TYPE == _LIGHT_CM32181)
	WORD uLuxStep = 260; // 66535 * 0.04 = 2621.4 == 2621 �� 10���.
	uLux = Cm32181_get_lux();
	if (uLux > uLuxStep * 10) uCurrentLux = 100;
	else if (uLux > (uLuxStep * 8)) uCurrentLux = 90;
	else if (uLux > (uLuxStep * 7)) uCurrentLux = 80;
	else if (uLux > (uLuxStep * 6)) uCurrentLux = 70;
	else if (uLux > (uLuxStep * 5)) uCurrentLux = 60;
	else if (uLux > (uLuxStep * 4)) uCurrentLux = 50;
	else if (uLux > (uLuxStep * 3)) uCurrentLux = 40;
	else if (uLux > (uLuxStep * 2)) uCurrentLux = 30;
	else if (uLux > uLuxStep) uCurrentLux = 20;
	else  uCurrentLux = 10;
#elif (_LIGHT_SENSOR_TYPE == _LIGHT_TLS2561)
	uLux = CalculateLux();
	if (uLux > 1000) uCurrentLux = 100;
	else if (uLux > 900) uCurrentLux = 95;
	else if (uLux > 800) uCurrentLux = 90;
	else if (uLux > 700) uCurrentLux = 80;
	else if (uLux > 600) uCurrentLux = 70;
	else if (uLux > 500) uCurrentLux = 60;
	else if (uLux > 400) uCurrentLux = 50;
	else if (uLux > 300) uCurrentLux = 40;
	else if (uLux > 200) uCurrentLux = 30;
	else if (uLux > 100) uCurrentLux = 25;
	else if (uLux > 50)	 uCurrentLux = 20;
	else  uCurrentLux = 10;
#else
#endif
	if (wBeforeLux == uCurrentLux)
	{
		if (u8CheckCount++ > 10)
		{
			bChangestate = _TRUE;
			u8CheckCount = 0;
}
	}
	else
	{
		wBeforeLux = uCurrentLux;
	}
	if (bChangestate)
	{
		realLux = UserCommonAdjustPercentToRealValue(uCurrentLux, _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
		if (GET_OSD_BACKLIGHT() < realLux)
		{
			SET_OSD_BACKLIGHT(GET_OSD_BACKLIGHT() + 6);
			if (GET_OSD_BACKLIGHT() >= realLux)
			{
				SET_OSD_BACKLIGHT(realLux);
				bChangestate = _FALSE;
			}
		}
		else if (GET_OSD_BACKLIGHT() > realLux)
		{
			SET_OSD_BACKLIGHT(GET_OSD_BACKLIGHT() - 6);
			if (GET_OSD_BACKLIGHT() <= realLux)
			{
				SET_OSD_BACKLIGHT(realLux);
				bChangestate = _FALSE;
			}
		}
		else
		{
			SET_OSD_BACKLIGHT(realLux);
			bChangestate = _FALSE;
		}
		UserAdjustBacklight(GET_OSD_BACKLIGHT());
	}
}
#endif

#if (_ENABLE_FAN_CONTROL == _ON)
SBYTE MeasureTemperature(void)
{
	SBYTE tmpAvg = 0;
#if (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
	if (SuccessInitializeFanControl())
	{
		SetADT7470Configration();
		if (GetADT7470Config()) //1ȸ ���� 1�� Delay�� �ѹ� ���� �Ҷ� ���� Ȱ��ȭ ��Ȱ��ȭ�� �˻� �Ŀ� �µ��� ���� �մϴ�.
		{
			Get_ADT7470Temperature();
		}
		return tmpAvg;
	}
#elif (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
	if (SuccessInitializeFanControl())
	{
		Get_MAX31785Temperature();
		return tmpAvg;
	}
#endif
	return tmpAvg;
}

void AutoFanControl(SBYTE t)
{
#if (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
	bit fshutdown = _FALSE;

	if (GET_OSD_SHUTDOWN_STATUS() == _ON)
	{
		if (Get_ADT7470Temp1() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else if (Get_ADT7470Temp2() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else if (Get_ADT7470Temp3() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else if (Get_ADT7470Temp4() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else if (Get_ADT7470Temp5() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else { fshutdown = _FALSE; }
		if (fshutdown)
		{
			SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
#if (_ENABLE_MENU_OLED == _OFF)
			SMPS_POWER(_OFF);
#endif
			//printf("Over Temperature  Power ShutDown. %d \n\r", t);
			//printf("Get_ADT7470Temp1. %d \n\r", Get_ADT7470Temp1());
			//printf("Get_ADT7470Temp2. %d \n\r", Get_ADT7470Temp2());
			//printf("Get_ADT7470Temp3. %d \n\r", Get_ADT7470Temp3());
			//printf("Get_ADT7470Temp4. %d \n\r", Get_ADT7470Temp4());
			//printf("Get_ADT7470Temp5. %d \n\r", Get_ADT7470Temp5());
		}

	}
	if (t > 70) SetFanAllPWM(255); // Max FAN 255/8
	else if (65 < t && t <= 68) SetFanAllPWM(223);
	else if (60 < t && t <= 63) SetFanAllPWM(191);
	else if (55 < t && t <= 58) SetFanAllPWM(159);
	else if (50 < t && t <= 52) SetFanAllPWM(127);
	else if (45 < t && t <= 48) SetFanAllPWM(96);
	else if (40 < t && t <= 43) SetFanAllPWM(64);
	else if (t <= 38) SetFanAllPWM(30); //

#elif (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
	bit fshutdown = _FALSE;
	if (GET_OSD_SHUTDOWN_STATUS() == _ON)
	{
		if (Get_MAX31785Temp1() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else if (Get_MAX31785Temp2() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else if (Get_MAX31785Temp3() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else if (Get_MAX31785Temp4() > GET_OSD_SHUTDOWN_TEMP()) fshutdown = _TRUE;
		else { fshutdown = _FALSE; }
		if (fshutdown)
		{
			SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
#if (_ENABLE_MENU_OLED == _OFF)
			SMPS_POWER(_OFF);
#endif
			//printf("Over Temperature  Power ShutDown. %d \n\r", t);
			//printf("Get_ADT7470Temp1. %d \n\r", Get_ADT7470Temp1());
			//printf("Get_ADT7470Temp2. %d \n\r", Get_ADT7470Temp2());
			//printf("Get_ADT7470Temp3. %d \n\r", Get_ADT7470Temp3());
			//printf("Get_ADT7470Temp4. %d \n\r", Get_ADT7470Temp4());
			//printf("Get_ADT7470Temp5. %d \n\r", Get_ADT7470Temp5());
		}

	}
	if (t > 70) SetFanAllPWM(255); // Max FAN 255/8
	else if (65 < t && t <= 68) SetFanAllPWM(223);
	else if (60 < t && t <= 63) SetFanAllPWM(191);
	else if (55 < t && t <= 58) SetFanAllPWM(159);
	else if (50 < t && t <= 52) SetFanAllPWM(127);
	else if (45 < t && t <= 48) SetFanAllPWM(96);
	else if (40 < t && t <= 43) SetFanAllPWM(64);
	else if (t <= 38) SetFanAllPWM(30); //

#endif
}


void SetFan1(BYTE u8pwm)
{
	if (SuccessInitializeFanControl())
		SetFanPWM1(u8pwm);
}
void SetFan2(BYTE u8pwm)
{
	if (SuccessInitializeFanControl())
		SetFanPWM2(u8pwm);
}
void SetFan3(BYTE u8pwm)
{
	if (SuccessInitializeFanControl())
		SetFanPWM3(u8pwm);
}
void SetFan4(BYTE u8pwm)
{
#if (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
	if (SuccessInitializeFanControl())
		SetFanPWM4(u8pwm);
#elif (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
	if (SuccessInitializeFanControl())
	{
		SetFanPWM4(u8pwm);
		SetFanPWM5(u8pwm);
		SetFanPWM6(u8pwm);
	}
#endif
}

void ApplyFanControl(bit bSet)
{
	if (SuccessInitializeFanControl())
	{
		BYTE temp = 0;
		temp = MeasureTemperature();
		switch (GET_OSD_FAN_STATUS())
		{
		default:
		case _AUTO:
#if (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
			if (bSet)
			{
				MAX31785_EanbleFan();
			}
#endif
			AutoFanControl(temp);
			break;
		case _ON:
#if (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
			if (bSet)
			{
				MAX31785_EanbleFan();
			}
#endif
			SetFan1(GET_OSD_FAN_PWM1());
			SetFan2(GET_OSD_FAN_PWM2());
			SetFan3(GET_OSD_FAN_PWM3());
			SetFan4(GET_OSD_FAN_PWM4());
			break;
		case _OFF:
#if (_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)
			if (bSet)
			{
				MAX31785_DisableFan();
			}
#elif (_FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)
			SetFanAllPWM(0);
#endif
			break;
		}
	}
}

#endif

#if (_ENABLE_SELF_CHECK == _ON)
void SetColorPanttern(EnumSelfCheckPattern pattern)
{
	OsdDispDisableOsd();
	OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);

	switch (pattern)
	{
	default:
	case SC_RED:
		OsdFuncApplySelfCheckMap(WIDTH(1), HEIGHT(3), COLOR(_LOGO_CP_RED, _LOGO_CP_RED));
		break;
	case SC_GREEN:
		OsdFuncApplySelfCheckMap(WIDTH(1), HEIGHT(3), COLOR(_LOGO_CP_GREEN, _LOGO_CP_GREEN));
		break;
	case SC_BLUE:
		OsdFuncApplySelfCheckMap(WIDTH(1), HEIGHT(3), COLOR(_LOGO_CP_BLUE, _LOGO_CP_BLUE));
		break;
	}
	
	OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
	OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);

	OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, 0, 0);
	OsdFuncEnableOsd();
}

void ChangePattern(void)
{
	if (u8SelfCheckPattern++ == SC_BLUE) u8SelfCheckPattern = SC_RED;
}

void SetPattern(void)
{
	if (GET_OSD_STATE() == _MENU_NONE)
	{
		switch (u8SelfCheckPattern)
		{
		default:
		case SC_RED:
			SetColorPanttern(SC_RED);
			break;
		case SC_GREEN:
			SetColorPanttern(SC_GREEN);
			break;
		case SC_BLUE:
			SetColorPanttern(SC_BLUE);
			break;
		}
	}
}
/////////////////////////////////////////////////
// Check Red, Green, Blue Pattern
// Panel samsung LTM170ET01, Innolux M280DGJ-L30(Rev. C2) Measure.
//
//
/////////////////////////////////////////////////
bit CheckPattern(BYTE red, BYTE green, BYTE blue)
{
#if 0
	float average, r, g, b;
	average = (red + green + blue) / 3.0f;
	r = red / average;
	g = green / average;
	b = blue / average;
	switch (u8SelfCheckPattern)
	{

	case SC_RED:
		if (((SC_DEFAULT_RED_R_DATA_MIN <= r) && (r <= SC_DEFAULT_RED_R_DATA_MAX)) \
			&& ((SC_DEFAULT_RED_G_DATA_MIN <= g) && (g <= SC_DEFAULT_RED_G_DATA_MAX)) \
			&& ((SC_DEFAULT_RED_B_DATA_MIN <= b) && (b <= SC_DEFAULT_RED_B_DATA_MAX)))
		{
			//LOG_INFO(" ==TRUE==  RED == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _TRUE;
		}
		else
		{
			//LOG_INFO(" ==FALSE== RED == RED %d, GREEN %d, BLUE %d \n\r", red, green, blue);
			return _FALSE;
		}
		break;
	case SC_GREEN:
		if (((SC_DEFAULT_GREEN_R_DATA_MIN <= r) && (r <= SC_DEFAULT_GREEN_R_DATA_MAX)) \
			&& ((SC_DEFAULT_GREEN_G_DATA_MIN <= g) && (g <= SC_DEFAULT_GREEN_G_DATA_MAX)) \
			&& ((SC_DEFAULT_GREEN_B_DATA_MIN <= b) && (b <= SC_DEFAULT_GREEN_B_DATA_MAX)))
		{
			//LOG_INFO(" ==TRUE== GREEN == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _TRUE;
		}
		else
		{
			//LOG_INFO(" ==FALSE== GREEN == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _FALSE;
		}
		break;
	case SC_BLUE:
		if (((SC_DEFAULT_BLUE_R_DATA_MIN <= r) && (r <= SC_DEFAULT_BLUE_R_DATA_MAX)) \
			&& ((SC_DEFAULT_BLUE_G_DATA_MIN <= g) && (g <= SC_DEFAULT_BLUE_G_DATA_MAX)) \
			&& ((SC_DEFAULT_BLUE_B_DATA_MIN <= b) && (b <= SC_DEFAULT_BLUE_B_DATA_MAX)))
		{
			//LOG_INFO(" ==TRUE== BLUE == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _TRUE;
		}
		else
		{
			//LOG_INFO(" ==FALSE== BLUE == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _FALSE;
		}
		break;
	default:
		return _FALSE;
	}
#endif
	switch (u8SelfCheckPattern)
	{

	case SC_RED:
		if (((SC_DEFAULT_RED_R_DATA - SC_DATA_TOLERANCE <= red) && (red <= SC_DEFAULT_RED_R_DATA + SC_DATA_TOLERANCE)) \
			&& ((SC_DEFAULT_RED_G_DATA - SC_DATA_TOLERANCE <= green) && (green <= SC_DEFAULT_RED_G_DATA + SC_DATA_TOLERANCE)) \
			&& ((SC_DEFAULT_RED_B_DATA - SC_DATA_TOLERANCE <= blue) && (blue <= SC_DEFAULT_RED_B_DATA + SC_DATA_TOLERANCE)))
		{
			//LOG_INFO(" ==TRUE==  RED == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _TRUE;
		}
		else
		{
			//LOG_INFO(" ==FALSE== RED == RED %d, GREEN %d, BLUE %d \n\r", red, green, blue);
			return _FALSE;
		}
		break;
	case SC_GREEN:
		if (((SC_DEFAULT_GREEN_R_DATA - SC_DATA_TOLERANCE <= red) && (red <= SC_DEFAULT_GREEN_R_DATA + SC_DATA_TOLERANCE)) \
			&& ((SC_DEFAULT_GREEN_G_DATA - SC_DATA_TOLERANCE <= green) && (green <= SC_DEFAULT_GREEN_G_DATA + SC_DATA_TOLERANCE)) \
			&& ((SC_DEFAULT_GREEN_B_DATA - SC_DATA_TOLERANCE <= blue) && (blue <= SC_DEFAULT_GREEN_B_DATA + SC_DATA_TOLERANCE)))
		{
			//LOG_INFO(" ==TRUE== GREEN == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _TRUE;
		}
		else
		{
			//LOG_INFO(" ==FALSE== GREEN == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _FALSE;
		}
		break;

	case SC_BLUE:
		if (((SC_DEFAULT_BLUE_R_DATA - SC_DATA_TOLERANCE <= red) && (red <= SC_DEFAULT_BLUE_R_DATA + SC_DATA_TOLERANCE)) \
			&& ((SC_DEFAULT_BLUE_G_DATA - SC_DATA_TOLERANCE <= green) && (green <= SC_DEFAULT_BLUE_G_DATA + SC_DATA_TOLERANCE)) \
			&& ((SC_DEFAULT_BLUE_B_DATA - SC_DATA_TOLERANCE <= blue) && (blue <= SC_DEFAULT_BLUE_B_DATA + SC_DATA_TOLERANCE)))
		{
			//LOG_INFO(" ==TRUE== BLUE == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _TRUE;
		}
		else
		{
			//LOG_INFO(" ==FALSE== BLUE == RED %d, GREEN %d, BLUE %d\n\r", red, green, blue);
			return _FALSE;
		}
		break;
	default:
		return _FALSE;
	}
}


/////////////////////////////////////////////////
// TCS34725 Sensor Check Red, Green, Blue Pattern
/////////////////////////////////////////////////
void UserInterfaceSelfCheck(void)
{
	static BYTE u8ErrCheckCount; // Error count.
	static BYTE u8PatternCount; // Pattern change time.
	WORD clear, red, green, blue;
	DWORD sum = clear;
	float r, g, b;
	EnumSelfCheckPattern currentPattern = u8SelfCheckPattern;
	if (SuccessInitialize_TCS34725())
	{
		if (u8PatternCount++ == 4) // 3sec
		{
			ChangePattern(); //RGB Pattern change.
			currentPattern = u8SelfCheckPattern;
			u8PatternCount = 0;
		}
		SetPattern();
		//LOG_INFO("=== %s ==\n\r", currentPattern == SC_RED ? "RED" : (currentPattern == SC_GREEN ? "GREEN" : "BLUE"));
	
		GetRGBC_TCS34725(&red, &green, &blue, &clear);
		Lock_TCS34725();  // turn off LED
		//LOG_INFO("\tR: %d\t", red);
		//LOG_INFO("\tG: %d\t", green);
		//LOG_INFO("\tB: %d\t", blue);
		//LOG_INFO("C: %d \t", clear);

		// Figure out some basic hex code for visualization

		r = red; r /= sum;
		g = green; g /= sum;
		b = blue; b /= sum;
		r *= 256; g *= 256; b *= 256;
		//LOG_INFO("\n\r");
		//LOG_INFO(" R : %d(0x%x)\t, G : %d(0x%x)\t, B : %d(0x%x)\n\r",(U8)r, (U8)r, (U8)g, (U8)g, (U8)b, (U8)b);

		if (CheckPattern(r, g, b))
		{
			if (u8SelfCheckStatus == SC_STATUS_ERR)
			{
				if (u8ErrCheckCount-- < 1) u8SelfCheckStatus = SC_STATUS_NORMAL;
			}
			else
			{
				u8SelfCheckStatus = SC_STATUS_NORMAL;
				u8ErrCheckCount = 0;
				//LOG_INFO("NORMAL \n\r");
			}
		}
		else
		{
			if (u8ErrCheckCount == 10 || u8ErrCheckCount++ > 10) // 10 �̻��� Err ���� ȭ�� ���� �ҷ��� �۵� ��ŵ�ϴ�. ERR MAX Over �ȵǰ� ��.
			{
				u8SelfCheckStatus = SC_STATUS_ERR;
				//LOG_INFO("ERROR \n\r");
			}
		}
	}
	else
	{
		u8SelfCheckStatus = SC_STATUS_NOT_CONNECTED;
		//LOG_INFO("Not TCS34725 Connected\n\r");
	}
}

#endif

//#if (_PANEL_IDX_NAME == _PANEL_DV550QUM_N10	)
//void UserPanel_DV550QUM_N10_Initialize(void)
//{
//	BYTE _temp;
//	BYTE _controlValue1 = 0x12;
//	BYTE _controlValue2 = 0xFF;
//	BYTE _controlValue3 = 0x0A;
//
//	//ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue1); // Step1 Reset
//	//ScalerTimerDelayXms(50); // 50ms
//	//ScalerMcuIICRead(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x01, 1, &_temp); // Step2 Read VCOM
//	//ScalerTimerDelayXms(1); // 1ms
//	//ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x01, 1, &_controlValue2); // Step3 Adjust VCOM
//	//ScalerTimerDelayXms(1); // 1ms
//	//ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue3); // Step4 Write VCOM
//	//ScalerTimerDelayXms(500); // 1ms
//	//ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue1); // Step5 Reset
//
//	if (ScalerMcuHwIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue1, _HW_IIC_PIN_149_150) == _FAIL) // Step1 Reset
//	{
//		DebugMessageSystem("Panel Test1 Fail", _FAIL);
//	}
//	else
//	{
//		DebugMessageSystem("Panel Test1 Success", _SUCCESS);
//	}
//	ScalerTimerDelayXms(50); // 50ms
//	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
//	if(ScalerMcuHwIICRead(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x01, 1, &_temp, _HW_IIC_PIN_149_150) == _FAIL) // Step2 Read VCOM
//	{
//		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
//		DebugMessageSystem("Panel Test2 Fail", _FAIL);
//	}
//	else
//	{
//		DebugMessageSystem("Panel Test2 Success", _SUCCESS);
//	}
//	ScalerTimerDelayXms(1); // 1ms
//	if(ScalerMcuHwIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x01, 1, &_controlValue2, _HW_IIC_PIN_149_150) == _FAIL) // Step3 Adjust VCOM
//	{
//		DebugMessageSystem("Panel Test3 Fail", _FAIL);
//	}
//	else
//	{
//		DebugMessageSystem("Panel Test3 Success", _SUCCESS);
//	}
//	ScalerTimerDelayXms(1); // 1ms
//	if(ScalerMcuHwIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue3, _HW_IIC_PIN_149_150) == _FAIL)// Step4 Write VCOM
//	{
//		DebugMessageSystem("Panel Test4 Fail", _FAIL);
//	}
//	else
//	{
//		DebugMessageSystem("Panel Test4 Success", _SUCCESS);
//	}
//	ScalerTimerDelayXms(500); // 1ms
//	if(ScalerMcuHwIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue1, _HW_IIC_PIN_149_150) == _FAIL) // Step5 Reset
//	{
//		DebugMessageSystem("Panel Test5 Fail", _FAIL);
//	}
//	else
//	{
//		DebugMessageSystem("Panel Test5 Success", _SUCCESS);
//	}
//
//	//if (ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue1) == _FAIL) // Step1 Reset
//	//{
//	//	DebugMessageSystem("Panel Test1 Fail", _FAIL);
//	//}
//	//else
//	//{
//	//	DebugMessageSystem("Panel Test1 Success", _SUCCESS);
//	//}
//	//ScalerTimerDelayXms(50); // 50ms
//	//if (ScalerMcuIICRead(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x01, 1, &_temp) == _FAIL) // Step2 Read VCOM
//	//{
//	//	DebugMessageSystem("Panel Test2 Fail", _FAIL);
//	//}
//	//else
//	//{
//	//	DebugMessageSystem("Panel Test2 Success", _SUCCESS);
//	//}
//	//ScalerTimerDelayXms(1); // 1ms
//	//if (ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x01, 1, &_controlValue2) == _FAIL) // Step3 Adjust VCOM
//	//{
//	//	DebugMessageSystem("Panel Test3 Fail", _FAIL);
//	//}
//	//else
//	//{
//	//	DebugMessageSystem("Panel Test3 Success", _SUCCESS);
//	//}
//	//ScalerTimerDelayXms(1); // 1ms
//	//if (ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue3) == _FAIL)// Step4 Write VCOM
//	//{
//	//	DebugMessageSystem("Panel Test4 Fail", _FAIL);
//	//}
//	//else
//	//{
//	//	DebugMessageSystem("Panel Test4 Success", _SUCCESS);
//	//}
//	//ScalerTimerDelayXms(500); // 1ms
//	//if (ScalerMcuIICWrite(DV550QUM_N10_SLAVE_ADDRESS, 1, 0x00, 1, &_controlValue1) == _FAIL) // Step5 Reset
//	//{
//	//	DebugMessageSystem("Panel Test5 Fail", _FAIL);
//	//}
//	//else
//	//{
//	//	DebugMessageSystem("Panel Test5 Success", _SUCCESS);
//	//}
//}
//#endif


#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
