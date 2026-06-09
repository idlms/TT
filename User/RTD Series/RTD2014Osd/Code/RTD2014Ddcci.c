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
// ID Code      : RTD2014Ddcci.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_DDCCI__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#define _DDCCI_FIRMWARE_VERSION                     0x01

#define _DDCCI_BLACKLEVEL_DEFAULT                   0x50

// RC
#define _DDCCI_CMD_GETVCP_RC_NO_ERROR               0x00
#define _DDCCI_CMD_GETVCP_RC_UNSUPPORTED            0x01

// TP
#define _DDCCI_CMD_GETVCP_TP_SET_PARAMETER          0x00
#define _DDCCI_CMD_GETVCP_TP_MOMENTARY              0x01

//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _COLORTEMP_USER_MAX                         255
#define _COLORTEMP_USER_MIN                         0
#define _COLORTEMP_USER_CENTER                      (((_COLORTEMP_USER_MAX - _COLORTEMP_USER_MIN) / 2) + _COLORTEMP_USER_MIN)

//--------------------------------------------------
// For DDCCI Set Input Port
//--------------------------------------------------
#define _VGA_1                                      _A0_INPUT_PORT
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D0_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                     _D2_INPUT_PORT


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
BYTE code tCOLORPRESET_VALUE[] = {0x08, 0x06, 0x05, 0x04, 0x01, 0x0B, 0x02};

BYTE code tLANGUAGEDEFINE[] = {0x02, 0x03, 0x04, 0x0a, 0x01, 0x0d, 0x06};



//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucDdcciRedBlackLevel   = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciGreenBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciBlueBlackLevel  = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciNewControlValue = 1;
BYTE g_ucDdcciActiveValue;
BYTE g_ucColorTempUnSupport;

bit g_bForcePowSavStatus = _FALSE;
bit	g_bScreenMuteSatus = _FALSE;

//****************************************************************************
// CIZGI DECLARATIONS
//****************************************************************************
#if(_CIZGI_ENABLE_DICOM_CALIBRATION == _ON)	
BYTE Czg_Gamma_TablePointer = 0x0;
BYTE Czg_RGBTable = 0;
BYTE Czg_AutoIncrement = 0;
WORD Czg_Gamma_Table = 0x00; 
BYTE Czg_WriteCmd = 0;
BYTE tLUTGAMMA[132];
BYTE Czg_GammaValue = 0x0;
BYTE Czg_GolorTempValue = 0x0;
WORD  GammaValue = 0;

WORD usLastLUT = 0;
WORD usCurrLUT = 0;
WORD usInto = 0;
BYTE ucJ = 0;

WORD printCnt = 0;
BYTE gammaLow = 0;
BYTE gammaHigh = 0;
BYTE bufferCnt = 0;

BYTE ucBackupDB = 0;

BYTE BoardModel = 1;

BYTE xdata *g_pucDISP_CALIBRATION_FLASHx = _OGC_FLASH_PAGE * _FLASH_PAGE_SIZE;
	
#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserDdcciHandler(void);
void RTDDdcciGetVCPFeature(void);
bit RTDDdcciSetVCPFeatureCheck(void);
void RTDDdcciSetVCPFeature(void);
void RTDDdcciResetAllSettings(void);
void RTDDdcciColorReset(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserDdcciHandler(void)
{
    if(GET_OSD_DDCCI_STATUS() == _ON)
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
        {
            switch(g_pucDdcciRxBuf[_DDCCI_COMMAND])
            {
                case _DDCCI_CMD_GET_VCP_FEATURE:
                    RTDDdcciGetVCPFeature();
                    break;

                case _DDCCI_CMD_SET_VCP_FEATURE:
                    RTDDdcciSetVCPFeature();
                    break;

                case _DDCCI_CMD_GET_TIMING_REPORT:
                    UserCommonDdcciGetTimingReport();
                    break;

                case _DDCCI_CMD_SAVE_CURRENT_SETTINGS:
                    break;

                case _DDCCI_CMD_CAPABILITIES_REQUEST:
                    UserCommonDdcciGetCapabilitiesRequest();
                    break;

                default:
                    UserCommonDdcciInitTx();
                    break;
            }

            UserCommonDdcciInitRx();

            SET_RUN_DDCCI_COMMAND(_FAIL);
        }
    }
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    else
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if((GET_RUN_DDCCI_COMMAND() == _SUCCESS) && (UserInterfaceGetDpMSTCapablePort() != _DP_MST_NO_PORT))
        {
#if(_CIZGI_ENABLE_DICOM_CALIBRATION == _OFF)										
                    UserCommonDdcciInitTx();
#endif	
            SET_RUN_DDCCI_COMMAND(_FAIL);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : DDCCI Get VCP Feature & VCP Feature Reply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciGetVCPFeature(void)
{
    BYTE pucTemp[2] = {0};

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x08;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY;
    g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_NO_ERROR;
    g_pucDdcciTxBuf[_DDCCI_SINK_OPCODE] = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE];

    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
    {
        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0002, g_ucDdcciNewControlValue);
            break;

        case _DDCCI_OPCODE_VCP_FACTORY_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_TEMP_INCREMENT:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0000, 100);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_TEMP_REQUEST:
            switch(GET_COLOR_TEMP_TYPE())
            {
                case _CT_SRGB:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (40 - 30));
                    break;

                case _CT_9300:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (93 - 30));
                    break;

                case _CT_7500:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (75 - 30));
                    break;

                case _CT_6500:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (65 - 30));
                    break;

                case _CT_5800:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (50 - 30));
                    break;

                default:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (65 - 30));
                    break;
            }
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK:

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_CLOCK());
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                BYTE ucClock = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                ucClock = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, ucClock);
            }
#endif
            break;

#endif // End of #if(_VGA_SUPPORT == _ON)

        case _DDCCI_OPCODE_VCP_BACKLIGHT:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,
                                            (WORD)UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
            break;

        case _DDCCI_OPCODE_VCP_CONTRAST:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,
                                            (WORD)UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x000B,
                                            tCOLORPRESET_VALUE[GET_COLOR_TEMP_TYPE()]);
            break;

        case _DDCCI_OPCODE_VCP_RED_GAIN:
            pucTemp[0] = GET_COLOR_TEMP_TYPE();

            if(GET_COLOR_TEMP_TYPE() != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(_CT_USER);

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }

            pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, pucTemp[1]);

            SET_COLOR_TEMP_TYPE(pucTemp[0]);

            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _DDCCI_OPCODE_VCP_GREEN_GAIN:
            pucTemp[0] = GET_COLOR_TEMP_TYPE();

            if(GET_COLOR_TEMP_TYPE() != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(_CT_USER);

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }

            pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, pucTemp[1]);

            SET_COLOR_TEMP_TYPE(pucTemp[0]);

            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _DDCCI_OPCODE_VCP_BLUE_GAIN:
            pucTemp[0] = GET_COLOR_TEMP_TYPE();

            if(GET_COLOR_TEMP_TYPE() != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(_CT_USER);

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }

            pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, pucTemp[1]);

            SET_COLOR_TEMP_TYPE(pucTemp[0]);

            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_AUTO_COLOR:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, 0x01);
            break;
#endif

        case _DDCCI_OPCODE_VCP_HPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_H_POSITION());
            }
            else
#endif
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_DIGITAL_H_POSITION());
            }

            break;

        case _DDCCI_OPCODE_VCP_VPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_V_POSITION());
            }
            else
#endif
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_DIGITAL_V_POSITION());
            }
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK_PHASE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_PHASE());
            break;
#endif

        case _DDCCI_OPCODE_VCP_ACTIVE_CONTROL:
            break;

        case _DDCCI_OPCODE_VCP_INPUT_SOURCE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x03, OsdDispJudgeSourceType());
            break;

#if(_AUDIO_SUPPORT == _ENABLE)
        case _DDCCI_OPCODE_VCP_AUDIO_VOLUME:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_OSD_VOLUME());
            break;
#endif

        case _DDCCI_OPCODE_VCP_RED_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciRedBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_GREEN_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciGreenBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_BLUE_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciBlueBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_PRODUCTKEY:
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 9;
            g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY;
            break;

        case _DDCCI_OPCODE_VCP_HFREQ:
            // PDATA_DWORD(0) = (DWORD)GET_INPUT_TIMING_HFREQ() * 100;
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, LOWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)), HIWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)));
            break;

        case _DDCCI_OPCODE_VCP_VFREQ:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, GET_INPUT_TIMING_VFREQ()*10);
            break;

        case _DDCCI_OPCODE_VCP_PANEL_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, 1);
            break;

        case _DDCCI_OPCODE_VCP_MONITOR_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x05, 3);
            break;

        case _DDCCI_OPCODE_VCP_APPLICATION_ENABLE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFF, 0x5a);
            break;

        case _DDCCI_OPCODE_VCP_CONTROLLER_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0000, 0x0009);
            break;

        case _DDCCI_OPCODE_VCP_FW_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, _DDCCI_FIRMWARE_VERSION);
            break;

        case _DDCCI_OPCODE_VCP_OSD_ON_OFF:
#if(_TRANSLATOR_SUPPORT == _OFF)
            if(ScalerOsdGetOsdEnable() == _TRUE)
            {
                pucTemp[0] = 2;
            }
            else
#endif
            {
                pucTemp[0] = 1;
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x02, pucTemp[0]);
            break;

        case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0D, tLANGUAGEDEFINE[GET_OSD_LANGUAGE()]);
            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:
            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
                pucTemp[0] = 4;
            }
            else if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
            {
                pucTemp[0] = 2;
            }
            else
            {
                pucTemp[0] = 1;
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0005, pucTemp[0]);
            break;

        case _DDCCI_OPCODE_VCP_VERSION:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, 0x0202);
            break;

        case _DDCCI_OPCODE_VCP_SHARPNESS:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0004, GET_OSD_SHARPNESS());
            break;
#if(_CIZGI_ENABLE_DICOM_CALIBRATION == _ON)	
        case _DDCCI_OPCODE_VCP_DICOM_PRESET_ADDRESS:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, (WORD)((((Czg_AutoIncrement<<7) | (Czg_RGBTable) | (Czg_Gamma_Table << 4) | (Czg_WriteCmd<< 2)) << 8) | Czg_Gamma_TablePointer));
            break;
			
        case _DDCCI_OPCODE_VCP_DICOM_PRESET_VALUE:
						UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, (WORD)((gammaHigh << 8) | gammaLow));
            break;

        case _DDCCI_OPCODE_VCP_DICOM_GAMMA_TABLE_OP:
						UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, Czg_Gamma_Table);
            break;
				
        case _DDCCI_OPCODE_VCP_DICOM_INFO:
						UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, (WORD) (BoardModel));
            break;				
#endif
        default:
            g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_UNSUPPORTED;
            break;
    }
    g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE + 1] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
}

//--------------------------------------------------
// Description  : Check DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDDdcciSetVCPFeatureCheck(void)
{
    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
    {
        case _DDCCI_OPCODE_VCP_FACTORY_RESET:
        case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
        case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:
        case _DDCCI_OPCODE_VCP_COLOR_RESET:

            if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0)
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
        case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
        case _DDCCI_OPCODE_VCP_AUTO_COLOR:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 3))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x0E))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x26))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x06))
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciSetVCPFeature(void)
{
    BYTE ucTemp = 0;

    if(RTDDdcciSetVCPFeatureCheck() == _FAIL)
    {
#if(_CIZGI_ENABLE_DICOM_CALIBRATION == _OFF)										
                    UserCommonDdcciInitTx();
#endif	
    }
    else
    {
        switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
        {
            case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    g_ucDdcciNewControlValue = 0x01;
                }

                break;

#if(_SHARPNESS_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_SHARPNESS:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 4)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 4;
                }
                SET_OSD_SHARPNESS(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserCommonAdjustSharpness(SysSourceGetInputPort());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;
#endif

            case _DDCCI_OPCODE_VCP_INPUT_SOURCE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_VGA_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x03)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DVI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x04)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DVI_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x0F)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DP_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x10)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_DP_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x11)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_HDMI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x12)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                    SysSourceSwitchInputPort(_HDMI_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                break;

            case _DDCCI_OPCODE_VCP_FACTORY_RESET:

                RTDDdcciResetAllSettings();

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    UserCommonAutoConfig();
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(50);
                    SET_DIGITAL_V_POSITION(50);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

            case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:

                RTDNVRamRestoreBriCon();
                RTDNVRamRestoreBacklight();

                UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
                break;

            case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    UserCommonAutoConfig();
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(50);
                    SET_DIGITAL_V_POSITION(50);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

            case _DDCCI_OPCODE_VCP_COLOR_RESET:

                RTDDdcciColorReset();

                break;

            case _DDCCI_OPCODE_VCP_COLOR_TEMP_REQUEST:

                g_ucColorTempUnSupport = (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] + 30);
                if(g_ucColorTempUnSupport >= 93)
                {
                    SET_COLOR_TEMP_TYPE(_CT_9300);
                }
                else if((g_ucColorTempUnSupport < 85) && (g_ucColorTempUnSupport >= 75))
                {
                    SET_COLOR_TEMP_TYPE(_CT_7500);
                }
                else if((g_ucColorTempUnSupport < 75) && (g_ucColorTempUnSupport >= 65))
                {
                    SET_COLOR_TEMP_TYPE(_CT_6500);
                }
                else if((g_ucColorTempUnSupport < 60) && (g_ucColorTempUnSupport >= 50))
                {
                    SET_COLOR_TEMP_TYPE(_CT_5800);
                }
                else
                {
                    SET_COLOR_TEMP_TYPE(_CT_SRGB);
                }

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
                OsdDispDisableOsd();

                break;

            case _DDCCI_OPCODE_VCP_CLOCK:

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
                    SET_VGA_MODE_ADJUST_CLOCK(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#else
                    {
                        WORD usClockRangeMax = 0;
                        WORD usClockRangeMin = 0;

                        usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                        usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);

                        SET_VGA_MODE_ADJUST_CLOCK(UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin)));
                    }
#endif
                    UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
#endif // End of #if(_VGA_SUPPORT == _ON)

                break;

            case _DDCCI_OPCODE_VCP_BACKLIGHT:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE], _BACKLIGHT_MAX(), _BACKLIGHT_MIN, _BACKLIGHT_CENTER));

                UserAdjustBacklight(GET_OSD_BACKLIGHT());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;

            case _DDCCI_OPCODE_VCP_CONTRAST:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_CONTRAST(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE], _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);

                break;

            case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x0B:
                        SET_COLOR_TEMP_TYPE(_CT_USER);
                        break;

                    case 0x05:
                        SET_COLOR_TEMP_TYPE(_CT_6500);
                        break;

                    case 0x08:
                        SET_COLOR_TEMP_TYPE(_CT_9300);
                        break;

                    case 0x01:
                        SET_COLOR_TEMP_TYPE(_CT_SRGB);
                        break;

                    case 0x04:
                        SET_COLOR_TEMP_TYPE(_CT_5800);
                        break;

                    case 0x06:
                        SET_COLOR_TEMP_TYPE(_CT_7500);
                        break;
                    /*
                    case 0x02:
                        SET_COLOR_TEMP_TYPE(_CT_OFF);
                        break;
                    */
                    default:
                        break;
                }

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
                OsdDispDisableOsd();

                break;

            case _DDCCI_OPCODE_VCP_RED_GAIN:
                // Only write at customer color
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();

                    SET_COLOR_TEMP_TYPE(_CT_USER);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE(ucTemp);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));
#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

            case _DDCCI_OPCODE_VCP_GREEN_GAIN:
                // Only write at customer color
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();

                    SET_COLOR_TEMP_TYPE(_CT_USER);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE(ucTemp);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));
#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

            case _DDCCI_OPCODE_VCP_BLUE_GAIN:
                // Only write at customer color
                if(GET_COLOR_TEMP_TYPE() != _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();

                    SET_COLOR_TEMP_TYPE(_CT_USER);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());

                    SET_COLOR_TEMP_TYPE(ucTemp);

                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX,
                                                                                  _COLORTEMP_USER_MIN,
                                                                                  _COLORTEMP_USER_CENTER));
#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUTO_SET_UP:

                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] != 0)
                    {
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
                    }
                }

                break;
#endif

            case _DDCCI_OPCODE_VCP_HPOSITION:
#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    SET_VGA_MODE_ADJUST_H_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                }
                break;

            case _DDCCI_OPCODE_VCP_VPOSITION:
#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(abs(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] - GET_VGA_MODE_ADJUST_V_POSITION()) > 50)
                    {
                        SET_VGA_MODE_ADJUST_V_POSITION(50);
                    }
                    SET_VGA_MODE_ADJUST_V_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_V_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_CLOCK_PHASE:

                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

                    SET_VGA_MODE_ADJUST_PHASE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                    UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }

                break;
#endif

            case _DDCCI_OPCODE_VCP_ACTIVE_CONTROL:

                g_ucDdcciActiveValue = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];

                break;

#if(_AUDIO_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUDIO_VOLUME:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_VOLUME(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserAdjustAudioVolume(GET_OSD_VOLUME());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            case _DDCCI_OPCODE_VCP_RED_BLACK_LEVEL:

                g_ucDdcciRedBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciRedBlackLevel);                            // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_GREEN_BLACK_LEVEL:

                g_ucDdcciGreenBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciGreenBlackLevel);                             // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_BLUE_BLACK_LEVEL:

                g_ucDdcciBlueBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciGreenBlackLevel);                             // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_POWER_MODE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 5)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 4)
                {
                    SET_FORCE_POW_SAV_STATUS(_TRUE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 1)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }

                break;

            case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x01:
                        SET_OSD_LANGUAGE(_CHINESE_T);
                        break;

                    case 0x02:
                        SET_OSD_LANGUAGE(_ENGLISH);
                        break;

                    case 0x03:
                        SET_OSD_LANGUAGE(_FRENCH);
                        break;

                    case 0x04:
                        SET_OSD_LANGUAGE(_GERMAN);
                        break;

                    case 0x0A:
//                        SET_OSD_LANGUAGE(_SPANISH);
                        break;

                    case 0x06:
 //                       SET_OSD_LANGUAGE(_JAPAN);
                        break;

                    case 0x0D:
 //                       SET_OSD_LANGUAGE(_CHINESE_S);
                        break;

                    default:
                        break;
                }

                OsdDispDisableOsd();
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;
#if(_CIZGI_ENABLE_DICOM_CALIBRATION == _ON)	
            case _DDCCI_OPCODE_VCP_DICOM_PRESET_ADDRESS:						
								Czg_Gamma_TablePointer = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
								Czg_RGBTable = g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] & 0x0f;
								if(g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] & 0x80){
									Czg_AutoIncrement = 1;									
								}
								else
									Czg_AutoIncrement = 0;			
								Czg_Gamma_Table = ((g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] & 0x7f) >> 4);	

								if((Czg_RGBTable == 0) && (Czg_Gamma_TablePointer == 0)){
									usCurrLUT = 0;
								//	SET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION(), _COLOREFFECT_STANDARD);
								//	UserAdjustColorEffectMode(GET_OSD_SYSTEM_SELECT_REGION());
									ucBackupDB = ScalerGetByte(P31_B0_D_DB_CTRL0);
									ScalerSetByte(P31_B0_D_DB_CTRL0, 0x00);
									UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE);
									UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 1);											
								}
			break;
				
            case _DDCCI_OPCODE_VCP_DICOM_GAMMA_TABLE_OP:	
									Czg_GammaValue = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
									Czg_GolorTempValue = g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE];

										printCnt = 0;
										bufferCnt = 0;
										usCurrLUT = 0;	
										switch (Czg_GolorTempValue)
										{	
											case 0:	// Color Temp is D50	
												SET_COLOR_TEMP_TYPE( _CT_USER);
												break;
											case 58:	// Color Temp is D56	
												SET_COLOR_TEMP_TYPE( _CT_5800);
												break;		
											case 65:	// Color Temp is D65	
												SET_COLOR_TEMP_TYPE( _CT_6500);
												break;	
											case 75:	// Color Temp is D75	
												SET_COLOR_TEMP_TYPE( _CT_7500);
												break;	
											case 93:	// Color Temp is D93	
												SET_COLOR_TEMP_TYPE( _CT_9300);
												break;																				
											default:				
												break;
										}

										if((Czg_GammaValue >= 9)&&(Czg_GammaValue <= 60))	//	Set Gamma Value
										{

											if(Czg_GammaValue == 36)	//	Set Gamma Value  GAMMA 1.8
											{
												SET_OSD_GAMMA( _GAMMA_18);
											}
											
											if(Czg_GammaValue == 40)	//	Set Gamma Value GAMMA 2.0
											{
												SET_OSD_GAMMA( _GAMMA_20);
											}			
											else if(Czg_GammaValue == 44)	//	Set Gamma Value GAMMA 2.2
											{
												SET_OSD_GAMMA( _GAMMA_22);
											}		
											/*
											else if(Czg_GammaValue == 48)	//	Set Gamma Value GAMMA 2.2
											{
												SET_OSD_GAMMA( 3);
											}		
											*/
										}
#if(_TECNINT_DICOM)
										else if(Czg_GammaValue == 255)						//	 Select DICOM calibration
										{
											SET_OSD_GAMMA( _GAMMA_RC2);
										}	
#endif					
							/*			SET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION(), _COLOREFFECT_STANDARD);
										
										RTDNVRamSaveOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());*/

//										g_stOsdUserData.b1CalibFlag = 1;
//										RTDEepromSaveOsdUserData();
//										printCnt = 0;
//									}
/*									UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING, _OFF);
									if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
									{
										UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
										UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
									}*/

                break;

            case _DDCCI_OPCODE_VCP_DICOM_PRESET_VALUE:
							gammaLow = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
							gammaHigh = g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE];
						
							usLastLUT = (g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] << 8) | g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];							
							for(ucJ = 1; ucJ < 4; ucJ++)
							{
									usInto = usLastLUT - ((usLastLUT - usCurrLUT) * (4-ucJ) + 2) / 4; 
									tLUTGAMMA[ucJ*2+Czg_Gamma_TablePointer*8-2-bufferCnt*128] = usInto >> 8;
									tLUTGAMMA[ucJ*2+1+Czg_Gamma_TablePointer*8-2-bufferCnt*128] = usInto & 0xFF;
							}									
							tLUTGAMMA[(Czg_Gamma_TablePointer+1)*8-2-bufferCnt*128] = g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE];
							tLUTGAMMA[(Czg_Gamma_TablePointer+1)*8+1-2-bufferCnt*128] = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
							usCurrLUT = usLastLUT;				
							
							if(((Czg_Gamma_TablePointer + 1) % 16) == 0){
									if(Czg_Gamma_TablePointer == 255){
											tLUTGAMMA[128] = tLUTGAMMA[126];
											tLUTGAMMA[129] = tLUTGAMMA[127];
											tLUTGAMMA[130] = 0;
											tLUTGAMMA[131] = 0;	//_OGC_RGB_GAIN_ADDRESS
											UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (_OGC_DICOM_ADDRESS + Czg_RGBTable*2052 + bufferCnt*128), 132, tLUTGAMMA);
											//UserCommonFlashWrite(_OGC_FLASH_BANK + (ucGammaIndex-1), ((WORD)_OGC_FLASH_PAGE << 12) + (_OGC_DICOM_ADDRESS + Czg_RGBTable*2052 + bufferCnt*128) + (ucColorTempIndex  * 0x1810), 132, tLUTGAMMA);
											//UserCommonFlashWrite(_OGC_FLASH_BANK+ (ucGammaIndex-1), ((WORD)(_OGC_FLASH_PAGE+(ucColorTempIndex*2) << 12)) + (_OGC_DICOM_ADDRESS + Czg_RGBTable*2052 + bufferCnt*128), 132, tLUTGAMMA);
											bufferCnt = 0;
											usCurrLUT = 0;
											if(Czg_RGBTable == 2){ //0 R 1 G 2 BLUE
													printCnt++;
													if(printCnt == 1){
													//	SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_6500);
														RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
														UserAdjustContrast( GET_OSD_CONTRAST());
													//	SET_OSD_GAMMA(GET_OSD_SELECT_REGION(), 5);
														//UserAdjustGammaRegionEnable(GET_OSD_SELECT_REGION(), _DB_APPLY_POLLING, _OFF);
														UserAdjustGamma( GET_OSD_GAMMA());
														//UserAdjustGammaRegionEnable(GET_OSD_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
														SET_OSD_COLOR_EFFECT(_COLOREFFECT_STANDARD);
														UserAdjustColorEffectMode();
														//RTDNVRamSaveOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());
														g_stOsdUserData.b1CalibFlag = 1;
														RTDEepromSaveOSDData();
													}
													else {
														printCnt = 0;
													}
													//ScalerColorOutputGammaAdjust(&g_pucDISP_CALIBRATION_FLASH[tGAMMA_INDEX[ucGammaIndex]], _OGC_FLASH_BANK);
													
													
													ScalerColorOutputGammaEnable(_FUNCTION_OFF);
													ScalerColorOutputGammaAdjust( g_pucDISP_CALIBRATION_FLASHx + _OGC_DICOM_ADDRESS, _OGC_FLASH_BANK);
													//ScalerColorOutputGammaAdjust( g_pucDISP_CALIBRATION_FLASHx + _OGC_DICOM_ADDRESS + ((ucGammaIndex -1) * 2052*3*4)+ (ucColorTempIndex  * 2052*3), _OGC_FLASH_BANK);
        												//ScalerColorOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASHx + tCIZIGGAMMA_INDEX[ucColorTempIndex], _OGC_FLASH_BANK+(ucGammaIndex-1));
													//ScalerColorOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASHx +  _OGC_FLASH_PAGE+(ucColorTempIndex*2) * _FLASH_PAGE_SIZE + _OGC_DICOM_ADDRESS ,  _OGC_FLASH_BANK+(ucGammaIndex-1));	
													ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
													ScalerColorBrightnessEnable(_FUNCTION_OFF);
													ScalerColorContrastEnable(_FUNCTION_OFF);
													ScalerColorSRGBEnable(_FUNCTION_OFF);

													ScalerColorOutputGammaEnable(_FUNCTION_ON);	
														
													//ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
//													RTDNVRamLoadColorSetting(UserAdjustGetOSDSelectRegion(_1P_NORMAL_FULL_REGION));
//													UserAdjustContrast(_1P_NORMAL_FULL_REGION, GET_OSD_CONTRAST(UserAdjustGetOSDSelectRegion(_1P_NORMAL_FULL_REGION)));
													
													ScalerSetByte(P31_B0_D_DB_CTRL0, ucBackupDB);
													ScalerMcuDdcciReleaseScl();
												//	SET_OSD_PANEL_UNIFORMITY_TYPE(8);
//													g_stOsdUserData.b1CalibFlag = 1;
//													RTDEepromSaveOsdUserData();
										//			RTDFlashSaveOSDData();

			//									}
											}										
									}
									else {
										UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (_OGC_DICOM_ADDRESS + Czg_RGBTable*2052 + bufferCnt*128), 128, tLUTGAMMA);
										//UserCommonFlashWrite(_OGC_FLASH_BANK+ (ucGammaIndex-1), ((WORD)_OGC_FLASH_PAGE << 12) + (_OGC_DICOM_ADDRESS + Czg_RGBTable*2052 + bufferCnt*128) + (ucColorTempIndex  * 0x1810), 128, tLUTGAMMA);
										//UserCommonFlashWrite(_OGC_FLASH_BANK+ (ucGammaIndex-1), ((WORD)(_OGC_FLASH_PAGE+(ucColorTempIndex*2) << 12)) + (_OGC_DICOM_ADDRESS + Czg_RGBTable*2052 + bufferCnt*128), 128, tLUTGAMMA);
											bufferCnt++;
									}
							}	

								if (Czg_AutoIncrement)
								{
										if (Czg_Gamma_TablePointer == 0xff)
										{
											Czg_RGBTable++;
											bufferCnt = 0;
											if (Czg_RGBTable > 2)
												Czg_RGBTable = 0;
										}
										Czg_Gamma_TablePointer++;
								}	
	
                break;
#endif

            case _DDCCI_OPCODE_VCP_OSD_ON_OFF:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 1)
                {
                    OsdDispDisableOsd();
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 2)
                {
                    OsdFuncEnableOsd();
                }

                break;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
            case _DDCCI_OPCODE_VCP_DISP_CALIBRATION:

                UserCommonDdcciDispCalibProcess();

                break;
#endif

            default:
#if(_CIZGI_ENABLE_DICOM_CALIBRATION == _OFF)										
                    UserCommonDdcciInitTx();
#endif	
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Reset monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciResetAllSettings(void)
{
    UserCommonNVRamRestoreSystemData();
    RTDNVRamRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();
#endif

    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
    {
        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        UserCommonNVRamSaveSystemData();
    }

    RTDDdcciColorReset();
}

//--------------------------------------------------
// Description  : Reset color to default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciColorReset(void)
{
    g_ucDdcciRedBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
    g_ucDdcciGreenBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
    g_ucDdcciBlueBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;

    RTDNVRamRestoreUserColorSetting();
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

    RTDNVRamRestoreBriCon();
    RTDNVRamRestoreBacklight();

    UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
}
#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
