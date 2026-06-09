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
// ID Code      : UserPTN3460Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _PTN3460_DEVICE_ADDR            0x40    // DEV_CFG (lOW:0x40 , HIGH:0xC0)

#define _EDID_ROM                       0x00    // 128 byte
#define _DP_INTERFACE_CONTROL           0x80
#define _LVDS_INTERFACE_CONTROL1        0x81
#define _LVDS_INTERFACE_CONTROL2        0x82
#define _LVDS_INTERFACE_CONTROL3        0x83
#define _EDID_EMULATION_CONTROL         0x84
#define _EDID_ACCESS_CONTROL            0x85
#define _PWM_MIN_FREQUENCY              0x86
#define _PWM_MAX_FREQUENCY              0x89
#define _FAST_LINK_TRAINING_CON         0x8C
#define _PIN_CONFIG_CONTROL1            0x8D
#define _PIN_CONFIG_CONTROL2            0x8E
#define _PWM_DEFAULT_BITCOUNT           0x8F
#define _PWM_VALUE                      0x90    //0x90~0x91 (2byte)
#define _PWM_DEFAULT_FREQUENCY          0x92
#define _PANEL_T3_TIMING                0x93
#define _PANEL_T12_TIMING               0x94
#define _BACKLIGHT_CONTROL              0x95
#define _PANEL_T2_DELAY                 0x96
#define _PANEL_T4_TIMING                0x97
#define _PANEL_T5_DELAY                 0x98
#define _FIRMWARE_PLL_RANGE             0x99
#define _FoA_MAILBOX                    0xD7    //0xD7~0xE7 (16byte)
#define _FLASH_COMMAND                  0xE8
#define _FLASH_MAGIC_NUMBER             0xE9
#define _FLASH_TRIGGER                  0xEB
#define _CONFIGURATION_MAGIC_NUM        0xEC    //0xEC~0xEF (4byte)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//extern EnumGDStatus UserCommonGlobalDimmingGetEnableStatus(void);
//extern void UserCommonGlobalDimmingInitialSetting(bit bEn);

