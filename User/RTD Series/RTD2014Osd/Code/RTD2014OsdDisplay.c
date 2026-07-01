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
// ID Code      : RTD2014OsdDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDDISPLAY__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

extern BYTE code tsOsdClearText6[];

extern BYTE code tsOsdTestString[];	

extern BYTE code tsOsdPicture[];	
extern BYTE code tsOsdColor[];
extern BYTE code tsOsdDisplay[];
extern BYTE code tsOsdOsdSetting[]; 
extern BYTE code tsOsdAudio[]; 
extern BYTE code tsOsdDpOption[]; 
extern BYTE code tsOsdSetup[];
extern BYTE code tsOsdHeatControl[];
extern BYTE code tsOsdDimControl[];
extern BYTE code tsOsdVideoWall[];
extern BYTE code tsOsdInfo[];

extern BYTE code tsOsdBlacklevel[];
extern BYTE code tsOsdChroma[];

extern BYTE code tsOsdBrightness[];	
extern BYTE code tsOsdContrast[];
extern BYTE code tsOsdSharpness[];
extern BYTE code tsOsdAspectRatio[];
extern BYTE code tsOsdOverScan[];

extern BYTE code tsOsdMonoColor[];
extern BYTE code tsOsdStd[];
extern BYTE code tsOsdMono[];
extern BYTE code tsOsdNight[];

extern BYTE code tsOsdLock[];
extern BYTE code tsOsdUnLock[];
extern BYTE code tsOsdCorved[];
extern BYTE code tsOsdLinear[];
extern BYTE code tsOsdBacklightControl[];
extern BYTE code tsOsdBacklight[];
extern BYTE code tsOsdClone[];
extern BYTE code tsOsdLightSensor[];
extern BYTE code tsOsdFanControl[];
extern BYTE code tsOsdFanSpeed[];
extern BYTE code tsOsdKeyLock[];

extern BYTE code tsUserAssign_UpKey[];
extern BYTE code tsUserAssign_DownKey[];
extern BYTE code tsUserAssign_LeftKey[];
extern BYTE code tsUserAssign_RightKey[];
extern BYTE code tsUserAssign_NOT_USE[];

extern BYTE code tsOsdColorEffect[];
extern BYTE code tsOsdGamma[];
extern BYTE code tsOsdTemperature[];
extern BYTE code tsOsdColorGamut[];
extern BYTE code tsOsdRed[];
extern BYTE code tsOsdGreen[];
extern BYTE code tsOsdBlue[];

extern BYTE code tsOsdRedBIAS[];
extern BYTE code tsOsdGreenBIAS[];
extern BYTE code tsOsdBlueBIAS[];
extern BYTE code tsOsdRedGain[];
extern BYTE code tsOsdGreenGain[];
extern BYTE code tsOsdBlueGain[];


extern BYTE code tsOsdDispRotate[];
extern BYTE code tsOsdSource1[];
extern BYTE code tsOsdSource2[];
extern BYTE code tsOsdSource3[];
extern BYTE code tsOsdSource4[];
extern BYTE code tsOsdDispMode[];
extern BYTE code tsOsdPipPosition[];
extern BYTE code tsOsdPipSize[];
extern BYTE code tsOsdInputSwap[];
extern BYTE code tsOsdRegion[];			

extern BYTE code tsOsdOsdHPosition[];
extern BYTE code tsOsdOsdVPosition[];

extern BYTE code tsOsdTransparency[];
extern BYTE code tsOsdOsdTimeout[];
extern BYTE code tsOsdOsdRotate[];
extern BYTE code tsOsdLanguage[];

extern BYTE code tsOsdVolume[];
extern BYTE code tsOsdMute[];
extern BYTE code tsOsdUnmute[];
extern BYTE code tsOsdAudioSource[];

extern BYTE code tsOsdDpVersion[];
extern BYTE code tsOsdDpMst[];
extern BYTE code tsOsdDpResolution[];

extern BYTE code tsOsdDpCloneMode[];
extern BYTE code tsOsdDpCloneSource[];	

extern BYTE code tsOsdPowerSave[];
extern BYTE code tsOsdSetId[];
extern BYTE code tsOsdHpdMode[];

extern BYTE code tsOsdReset[];
extern BYTE code tsOsdPowerSave[];
extern BYTE code tsOsdSetId[];
extern BYTE code tsOsdHpdMode[];
extern BYTE code tsOsdAutoAdjust[];
extern BYTE code tsOsdHPosition[];
extern BYTE code tsOsdVPosition[];
extern BYTE code tsOsdClock[];
extern BYTE code tsOsdPhase[];

extern BYTE code tsOsdFanControl[];
extern BYTE code tsOsdActiveTemp[];
extern BYTE code tsOsdHysteresis[];
extern BYTE code tsOsdCurrentTemp[];
extern BYTE code tsOsdShutdownMode[];
extern BYTE code tsOsdShutdownTemp[];

extern BYTE code tsOsdAutoDimming[];
extern BYTE code tsOsdDimming[];
extern BYTE code tsOsdMaxAmbient[];
extern BYTE code tsOsdMinAmbient[];
extern BYTE code tsOsdCurrntLux[];

extern BYTE code tsOsdVideoWallMode[];
extern BYTE code tsOsdDisplayNum[];
extern BYTE code tsOsdHSetCount[];
extern BYTE code tsOsdVSetCount[];
extern BYTE code tsOsdHEdgeAdjust[];
extern BYTE code tsOsdVEdgeAdjust[];
extern BYTE code tsOsdReverseScan[];

extern BYTE code tsOsdFirmwareVersion[];
extern BYTE code tsOsdSerialNumber[];

extern BYTE code tsOsdSourcePc[];
extern BYTE code tsOsdSourceSDI[];
extern BYTE code tsOsdSource10GSFP[];

//----------------------------------------------------------------------
extern BYTE code tsOsdService1[];	
extern BYTE code tsOsdService2[];
extern BYTE code tsOsdService3[];
extern BYTE code tsOsdService4[];
extern BYTE code tsOsdService_UserAssign[];
extern BYTE code tsOsdScreenTest[];

extern BYTE code tsOsdWhiteBalance[];
extern BYTE code tsOsdD0Name[];
extern BYTE code tsOsdD1Name[];
extern BYTE code tsOsdD2Name[];
extern BYTE code tsOsdD3Name[];
extern BYTE code tsOsdBacklightMin[];
extern BYTE code tsOsdBacklightMax[];
extern BYTE code tsOsdBLUFreq[];
extern BYTE code tsOsdBLUInvert[];
extern BYTE code tsOsdLOGO[];
extern BYTE code tsOsdLogoSelect[];
#if(_CUSTOMER_TYPE == _CUSTOMER_TECNNIT )
extern BYTE code tsOsdStabilux[];
extern BYTE code tsOsdStabilizer[];
#endif
extern BYTE code tsOsdModel[];
extern BYTE code tsOsdFormat[];
extern BYTE code tsOsdColorTemp[];	

extern BYTE code tsOsdRange[];

extern BYTE code tsOsdInput[];
extern BYTE code tsOsdScreen[];

extern BYTE code tsOsdOLED[];
extern BYTE code tsOsdOFFRS[];
extern BYTE code tsOsdJB[];
extern BYTE code tsOsdSequenceTime[];
extern BYTE code tsBACKUP_USER_CONFIG[];

extern BYTE code tsOsdOLEDAutoRun[];		
extern BYTE code tsOsdOLEDEndRun[];		
extern BYTE code tsOsdOLEDNow[];		

//----------------------------------------------------------------------

BYTE code tsOsdON[];
BYTE code tsOsdOFF[];
BYTE code tsOsdOFF2[];	
BYTE code tsOsdOFF3[];


extern BYTE code tsOsdFull[];
extern BYTE code tsOsdFill[];

extern BYTE code tsOsd16_9[];
extern BYTE code tsOsd4_3[];
extern BYTE code tsOsd5_4[];
extern BYTE code tsOsdOrigin[];
extern BYTE code tsOsdUser[];
extern BYTE code tsOsdClearText[];
extern BYTE code tsOsdClearLongText[];


extern BYTE code tsOsdStandard[];		
extern BYTE code tsOsdGame[];
extern BYTE code tsOsdMovie[];
extern BYTE code tsOsdPhoto[];
extern BYTE code tsOsdVidid[];
extern BYTE code tsOsdGammaOff[];
extern BYTE code tsOsdGammaBypass[];
extern BYTE code tsOsdGammaNative[];
extern BYTE code tsOsdResettoDefault[];

extern BYTE code tsOsdGamma18[];
extern BYTE code tsOsdGamma20[];
extern BYTE code tsOsdGamma22[];
extern BYTE code tsOsdGamma24[];

extern BYTE code tsOsdGammaDicom[];	
extern BYTE code tsOsdGammaRC2[];
extern BYTE code tsOsdGammaRC3[];
extern BYTE code tsOsdTempD56[];
extern BYTE code tsOsdTempD65[];
extern BYTE code tsOsdTempD93[];
extern BYTE code tsOsdTempUser[];
extern BYTE code tsOsdBT709[];
extern BYTE code tsOsdDCI_P3[];
extern BYTE code tsOsdBT2020[];


extern BYTE code tsOsdTemp9300[];
extern BYTE code tsOsdTemp7500[];
extern BYTE code tsOsdTemp6500[];
extern BYTE code tsOsdTemp5800[];
extern BYTE code tsOsdTempSRGB[];

extern BYTE code tsOsdRotate[];
extern BYTE code tsOsdRotate0[];	
extern BYTE code tsOsdRotate90[];
extern BYTE code tsOsdRotate180[];
extern BYTE code tsOsdRotate270[];
extern BYTE code tsOsdRotateHFlip[];	
extern BYTE code tsOsdRotateVFlip[];
extern BYTE code tsOsdRotateHVFlip[];
extern BYTE code tsOsdRotateNOFlip[];



extern BYTE code tsOsdSourceAuto[];
extern BYTE code tsOsdSourceA0VGA[];
extern BYTE code tsOsdSourceD0DP2[];
extern BYTE code tsOsdSourceD1DP1[];
extern BYTE code tsOsdSourceD2HDMI2[];
extern BYTE code tsOsdSourceD3HDMI1[];
extern BYTE code tsOsdSourceDVI[];

extern BYTE code tsOsd1P[];			
extern BYTE code tsOsd2PLR[];
extern BYTE code tsOsd2PTB[];
extern BYTE code tsOsd2PPIP[];
extern BYTE code tsOsd3P[];
extern BYTE code tsOsd4P[];
extern BYTE code tsOsdPipRB[];
extern BYTE code tsOsdPipRT[];
extern BYTE code tsOsdPipLB[];
extern BYTE code tsOsdPipLT[];

extern BYTE code tsOsdEnglish[];
extern BYTE code tsOsdChinese[];

extern BYTE code tsOsdAudioLineIn[];	
extern BYTE code tsOsdAudioDigital[];
extern BYTE code tsOsdVga[];			

extern BYTE code tsOsdDpVer1_1[];		
extern BYTE code tsOsdDpVer1_2[];
extern BYTE code tsOsdDpVer1_3[];
extern BYTE code tsOsd1080P[];
extern BYTE code tsOsd1440P[];
extern BYTE code tsOsd2160P[];

extern BYTE code tsOsdPowerSaveOff[];			
extern BYTE code tsOsdPowerSave5Sec[];
extern BYTE code tsOsdPowerSave30Sec[];
extern BYTE code tsOsdPowerSave60Sec[];	

extern BYTE code tsOsdPowerSave30Sec_1[];

extern BYTE code tsOsdPowerSave1Min[];
extern BYTE code tsOsdPowerSave2Min[];
extern BYTE code tsOsdPowerSave5Min[];
extern BYTE code tsOsdPowerSave30Min[];
extern BYTE code tsOsdPowerSave60Min[];
extern BYTE code tsOsdPowerSave120Min[];
extern BYTE code tsOsdHpdMode1[];	
extern BYTE code tsOsdHpdMode2[];	
extern BYTE code tsOsdHpdMode3[];	
extern BYTE code tsOsdHpdMode4[];	


extern BYTE code tsOsdAutoPass[];		
extern BYTE code tsOsdAutoFail[];

extern BYTE code tsOsdFanAuto[];		


extern BYTE code tsOsd1PFull[];	
extern BYTE code tsOsd2PLRL[];	
extern BYTE code tsOsd2PLRR[];	
extern BYTE code tsOsd2PLRFull[];	
extern BYTE code tsOsd2PTBT[];	
extern BYTE code tsOsd2PTBB[];	
extern BYTE code tsOsd2PTBFull[];	
extern BYTE code tsOsd2PPipMain[];	
extern BYTE code tsOsd2PPipSub[];	
extern BYTE code tsOsd2PPipFull[];	
extern BYTE code tsOsd3P1P[];	
extern BYTE code tsOsd3P2P[];	
extern BYTE code tsOsd3P3P[];
extern BYTE code tsOsd3PFull[];	

extern BYTE code tsOsd4PLT[];	
extern BYTE code tsOsd4PLB[];	
extern BYTE code tsOsd4PRT[];	
extern BYTE code tsOsd4PRB[];	
extern BYTE code tsOsd4PFull[];	

extern BYTE code tsOsdSource[];	
extern BYTE code tsOsdYES[];	
extern BYTE code tsOsdNO[];

extern BYTE code tsOsdMenu[];			
extern BYTE code tsOsdNotice[];	

extern BYTE code tsOsdNull[]; 	
extern BYTE code tsOsdTestLength[];	

extern BYTE code tsOsdMstD0DP2[];
extern BYTE code tsOsdMstD1DP1[];	

extern BYTE code tsOsdIrTransfer[];	
extern BYTE code tsOsdTransferId[];	
extern BYTE code tsOsdAll[];	


extern void OsdPropGetShowResolutionStringAddress(void);
extern void OsdPropShowFreeSyncVFreqRange(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropGetShowDpInfoStringAddress(BYTE Index);
extern void OsdPropGetShowVFreqStringAddress(void);
extern void OsdPropGetShowHFreqPClkStringAddress(void);
extern void OsdPropGetShowRangeStringAddress(void);
extern void OsdPropGetShowAudioStringAddress(void);
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Definitions of Advance OSD ITEM
//--------------------------------------------------

typedef enum
{
    _OSD_ADVANCE_ASPECT,
    _OSD_ADVANCE_OVERSCAN,
    _OSD_ADVANCE_OVERDRIVE,
    _OSD_ADVANCE_DDCCI,
    _OSD_ADVANCE_ULTRAVIVID,
    _OSD_ADVANCE_DCR,
    _OSD_ADVANCE_DPOPTION,
    _OSD_ADVANCE_DPMST,
    _OSD_ADVANCE_DP_RESOLUTION,
    _OSD_ADVANCE_CLONE,
    _OSD_ADVANCE_HDMI_VERSIONS,
    _OSD_ADVANCE_FREESYNC,
    _OSD_ADVANCE_DP_ADAPTIVESYNC,
    _OSD_ADVANCE_TYPE_C_MODE,
    _OSD_ADVANCE_HDR,
    _OSD_ADVANCE_LOCALDIMMING,
    _OSD_ADVANCE_PIXELSHIFT,
    _OSD_ADVANCE_SDR_TO_HDR,
    _OSD_ADVANCE_MBR,
    _OSD_ADVANCE_NONE,

}EnumOsdAdvanceItem;

//following order could modify by User
BYTE code tOSD_ADVANCE_ITEM_PRI[]=
{
#if(_ASPECT_RATIO_SUPPORT == _ON)
    _OSD_ADVANCE_ASPECT,
#endif

#if(_OVERSCAN_SUPPORT == _ON)
    _OSD_ADVANCE_OVERSCAN,
#endif

#if(_OD_SUPPORT == _ON)
    _OSD_ADVANCE_OVERDRIVE,
#endif
    _OSD_ADVANCE_DDCCI,

#if(_ULTRA_VIVID_SUPPORT == _ON)
    _OSD_ADVANCE_ULTRAVIVID,
#endif

#if(_DCR_SUPPORT == _ON)
    _OSD_ADVANCE_DCR,
#endif

#if(_DP_SUPPORT == _ON)
    _OSD_ADVANCE_DPOPTION,
#if(_DP_MST_SUPPORT == _ON)
    _OSD_ADVANCE_DPMST,
#endif
    _OSD_ADVANCE_DP_RESOLUTION,
    _OSD_ADVANCE_CLONE,
#endif

#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
    _OSD_ADVANCE_HDMI_VERSIONS,
#endif

#if((_FREESYNC_II_SUPPORT == _ON)||(_FREESYNC_SUPPORT == _ON))
    _OSD_ADVANCE_FREESYNC,
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    _OSD_ADVANCE_DP_ADAPTIVESYNC,
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    _OSD_ADVANCE_TYPE_C_MODE,
#endif

#if(_HDR10_SUPPORT == _ON)
    _OSD_ADVANCE_HDR,
#endif

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    _OSD_ADVANCE_LOCALDIMMING,
#endif

#if (_SDR_TO_HDR_SUPPORT == _ON)
    _OSD_ADVANCE_SDR_TO_HDR,
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
    _OSD_ADVANCE_PIXELSHIFT,
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _OSD_ADVANCE_MBR,
#endif

    _OSD_ADVANCE_NONE,
};
#define _OSD_ADVANCE_ITEM_AMOUNT    (sizeof(tOSD_ADVANCE_ITEM_PRI)-1)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if (_ENABLE_MENU_OLED == _ON)
BYTE *OsdDisplayGetSequenceTimeP(void);
#endif

BYTE OsdDisplayGetSourcePortString(void);

#if(_VGA_SUPPORT == _ON)
BYTE OsdDisplayGetVGAModeString(bit bUserMode);
#endif

void OsdDispDisableOsd(void);
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
void OsdDispClearSelectColor(BYTE ucUpDown);

void OsdDispMainMenu(void);
void OsdSubMenuPageDraw(BYTE ucMainItem);	

void OsdDispNumberAndText(WORD usOsdState, WORD usValue, BYTE ucColor);	

WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
WORD OsdDisplayDetOverRange_Long(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
WORD OsdDisplayDetOverRange_Curved(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
WORD OsdDisplayDetOverRange_Freq(WORD usValue, WORD usMax, WORD usMin, bit bCycle);


void OsdDisplaySixColorGetOneColor(BYTE ucColor);
void OsdDisplaySixColorSetOneColor(BYTE ucColor);


void OsdDispHotKeySourceMenu(void);

void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);

#if (_ENABLE_MENU_OLED == _ON)
void OsdDispHotKeyOffRSMenu(void);
#endif

#if(_VGA_SUPPORT == _ON)
void OsdDispAutoConfigProc(void);
void OsdDisplayAutoBalanceProc(void);
#endif

void OsdDispClearSliderAndNumber(void);
void OsdDispOsdReset(void);
void OsdDispOsdFactoryReset(void);	

#if(_DP_SUPPORT == _ON)
void OsdDispResetDpCapabilitySwitch(void);
#endif

void OsdDispShowLogo(void);
void OsdDispShowInformation(void);
void OsdDispTransferId(BYTE AdjValue);	


#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
void OsdDispOsdRotateSwitch(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
BYTE OsdDisplayGetSourcePortString(void)
{
    switch(SysSourceGetInputPort())
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return _STRING_A0_PORT;
#endif
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return _STRING_D0_PORT;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return _STRING_D1_PORT;
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return _STRING_D2_PORT;
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return _STRING_D3_PORT;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return _STRING_D4_PORT;
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return _STRING_D5_PORT;
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
            return _STRING_D6_PORT;
#endif
        default:
            return _STRING_A0_PORT;
    }
}

//-----------------------------------------
BYTE *OsdDisplayGetSourcePortStringP(EnumSourceSearchPort enumSourceSearchPort)
{
    BYTE *pucArray = tsOsdNull;


    switch (enumSourceSearchPort)
    {
#if (_ENABLE_MENU_VGA == _ON)
#if (_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
    case _A0_INPUT_PORT:
        pucArray = tsOsdSourceA0VGA;
        break;
#endif
#endif
#if (_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    case _D0_INPUT_PORT:
        // pucArray = tsOsdSourceD0DP2;
        switch (GET_OSD_D0_NAME())
        {
        case _SOURCE_NAME_DP1:
            pucArray = tsOsdSourceD1DP1;
            break;
        case _SOURCE_NAME_DP2:
            pucArray = tsOsdSourceD0DP2;
            break;
        case _SOURCE_NAME_PC:
            pucArray = tsOsdSourcePc;
            break;
        }
        break;
#endif
#if (_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    case _D1_INPUT_PORT:
        switch (GET_OSD_D1_NAME())
        {
        case _SOURCE_NAME_DP1:
            pucArray = tsOsdSourceD1DP1;
            break;
        case _SOURCE_NAME_DP2:
            pucArray = tsOsdSourceD0DP2;
            break;
        case _SOURCE_NAME_PC:
            pucArray = tsOsdSourcePc;
            break;
        }
        break;
#endif
#if (_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
    case _D2_INPUT_PORT:
        switch (GET_OSD_D2_NAME())
        {
        case _SOURCE_NAME_HDMI1:
            pucArray = tsOsdSourceD3HDMI1;
            break;
        case _SOURCE_NAME_HDMI2:
            pucArray = tsOsdSourceD2HDMI2;
            break;
        case _SOURCE_NAME_PC2:
            pucArray = tsOsdSourcePc;
            break;
        }
        break;
#endif
#if (_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
    case _D3_INPUT_PORT:
        switch (GET_OSD_D3_NAME())
        {
        case _SOURCE_NAME_HDMI1:
            pucArray = tsOsdSourceD3HDMI1;
            break;
        case _SOURCE_NAME_HDMI2:
            pucArray = tsOsdSourceD2HDMI2;
            break;
        case _SOURCE_NAME_PC2:
            pucArray = tsOsdSourcePc;
            break;
        case _SOURCE_NAME_SDI:
            pucArray = tsOsdSourceSDI;
            break;
        case _SOURCE_NAME_10GSFP:
            pucArray = tsOsdSource10GSFP;
            break;
        case _SOURCE_NAME_DVI:
            pucArray = tsOsdSourceDVI;
            break;
        }
        break;
#endif
/*
#if (_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
    case _D4_INPUT_PORT:
        pucArray = tsOsdNull;
        break;
#endif
#if (_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
    case _D5_INPUT_PORT:
        pucArray = tsOsdNull;
        break;
#endif
#if (_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
    case _D6_INPUT_PORT:
        pucArray = tsOsdNull;
        break;
#endif
#if (_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
    case _D7_INPUT_PORT:
        pucArray = tsOsdNull;
        break;
#endif
*/
    default:
        break;
    }

    return pucArray;
}
/*
BYTE *OsdDisplayGetSourcePortStringP(void)	
{
	BYTE *pucArray = tsOsdNull;
	
    switch(SysSourceGetInputPort())
    {
#if(_ENABLE_MENU_VGA == _ON)	
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
			pucArray = tsOsdSourceA0VGA;
            break;
#endif
#endif
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
			pucArray = tsOsdSourceD0DP2;
            break;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
			pucArray = tsOsdSourceD1DP1;
            break;
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
			pucArray = tsOsdSourceD2HDMI2;
            break;
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
			pucArray = tsOsdSourceD3HDMI1;
            break;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
			pucArray = tsOsdNull;
            break;
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
			pucArray = tsOsdNull;
            break;
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
			pucArray = tsOsdNull;
            break;
#endif
        default:
            break;
			
    }

	return pucArray;
}
*/

BYTE *OsdGetBoardModel(void)	
{
    BYTE *pucArray = tsOsdNull;
    static BYTE xdata tTemp[14];
    BYTE i;

    strcpy(&tTemp[0], BOARD_MODEL); // 0-3
    // strcpy(&tTemp[0], _PANEL_NAME); // 0-3

    for (i = 0; i < 13; i++)
    {
        if ((tTemp[i] >= '0') && (tTemp[i] <= '9'))
            tTemp[i] = (tTemp[i] - '0' + _0_);
        else if ((tTemp[i] >= 'A') && (tTemp[i] <= 'W'))
            tTemp[i] = (tTemp[i] - 'A') + _A_;
        else if ((tTemp[i] >= 'X') && (tTemp[i] <= 'Z'))
            tTemp[i] = (tTemp[i] - 'X') + _X_;
        else if ((tTemp[i] >= 'a') && (tTemp[i] <= 'z'))
            tTemp[i] = (tTemp[i] - 'a') + _a_;
        else if (tTemp[i] == '-')
            tTemp[i] = _SLINE_;
        else
            tTemp[i] = _END_;
    }

    // tTemp[13] = _END_;
    pucArray = tTemp;

    return pucArray;
}



BYTE *OsdGetBoardVersionString(void)	
{
    BYTE *pucArray = tsOsdNull;
    static BYTE xdata tTemp[20];
    BYTE i;

    strcpy(&tTemp[0], BOARD_FWPART);
    tTemp[4] = '-';
    strcpy(&tTemp[5], CUSTOMER_CODE);
    tTemp[11] = '-';
    strcpy(&tTemp[12], BOARD_OPTION1);
    strcpy(&tTemp[13], BOARD_OPTION2);
    strcpy(&tTemp[15], BOARD_OPTION3);
    strcpy(&tTemp[16], BOARD_OPTION4);
    strcpy(&tTemp[17], BOARD_OPTION5);

    for (i = 0; i < 19; i++)
    {
        if ((tTemp[i] >= '0') && (tTemp[i] <= '9'))
            tTemp[i] = (tTemp[i] - '0' + _0_);
        else if ((tTemp[i] >= 'A') && (tTemp[i] <= 'W'))
            tTemp[i] = (tTemp[i] - 'A') + _A_;
        else if ((tTemp[i] >= 'X') && (tTemp[i] <= 'Z'))
            tTemp[i] = (tTemp[i] - 'X') + _X_;
        else if ((tTemp[i] >= 'a') && (tTemp[i] <= 'z'))
            tTemp[i] = (tTemp[i] - 'a') + _a_;
        else if (tTemp[i] == '-')
            tTemp[i] = _SLINE_;
        else
            tTemp[i] = _FONT_SPACE_1;
    }
    tTemp[19] = _END_;
    pucArray = tTemp;

    return pucArray;
}

BYTE *OsdDisplayGetResolutionStringP(void)	
{
	BYTE *pucArray = tsOsdNull;
	
	OsdPropGetShowResolutionStringAddress();
    pucArray = g_pucModeInfoData;

	return pucArray;
}

BYTE *OsdDisplayGetRangeStringP(void)
{
    BYTE *pucArray = tsOsdNull;

    OsdPropGetShowRangeStringAddress();
    pucArray = g_pucModeInfoData;

    return pucArray;
}

BYTE *OsdDisplayGetAudioStringP(void)	
{
    BYTE *pucArray = tsOsdNull;

    OsdPropGetShowAudioStringAddress();
    pucArray = g_pucModeInfoData;

    return pucArray;
}

BYTE *OsdDisplayGetHFreqPClkStringP(void)	
{
	BYTE *pucArray = tsOsdNull;
	
	OsdPropGetShowHFreqPClkStringAddress();
    pucArray = g_pucModeInfoData;

	return pucArray;
}

BYTE *OsdDisplayGetVFreqStringP(void)	
{
	BYTE *pucArray = tsOsdNull;
	
	OsdPropGetShowVFreqStringAddress();
    pucArray = g_pucModeInfoData;

	return pucArray;
}


BYTE *OsdDisplayGetUserAssignStringP(EnumUserAssign ucUserAssign)
{
    BYTE *pucArray = tsOsdNull;

    switch(ucUserAssign)
    {
        case _USERASSIGN_MUTE:
            pucArray = tsOsdMute;
            break;
        case _USERASSIGN_ROTATE:
            pucArray = tsOsdRotate;
            break;
        case _USERASSIGN_SCAN:
            pucArray = tsOsdAspectRatio;
            break;
        case _USERASSIGN_CONTRAST:
            pucArray = tsOsdContrast;
            break;
        case _USERASSIGN_VOLUME:
            pucArray = tsOsdVolume;
            break;
        case _USERASSIGN_BACKLIGHT:
            pucArray = tsOsdBacklight;
            break;
        case _USERASSIGN_MONO_COLOR:
            pucArray = tsOsdMonoColor;
            break;
        case _USERASSIGN_MONO:
            pucArray = tsOsdMono;
            break;
        case _USERASSIGN_DP1:
            pucArray = tsOsdSourceD1DP1;
            break;
        case _USERASSIGN_DP2:
            pucArray = tsOsdSourceD0DP2;
            break;
        case _USERASSIGN_HDMI1:
            pucArray = tsOsdSourceD3HDMI1;
            break;
        case _USERASSIGN_HDMI2:
            pucArray = tsOsdSourceD2HDMI2;
            break;
        case _USERASSIGN_REDMODE:
            pucArray = tsOsdNight;
            break;
        case _USERASSIGN_BRIGHTNESS:
            pucArray = tsOsdBrightness;
            break;
        default:
            pucArray = tsUserAssign_NOT_USE;
            break;
    }

    return pucArray;
}
//-----------------------------------------
#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
BYTE OsdDisplayGetVGAModeString(bit bUserMode)
{
    if(bUserMode == _USER_MODE_TYPE)
    {
        return _STRING_VGA_USER_MODE;
    }
    else
    {
        return _STRING_VGA_PRESET_MODE;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispDisableOsd(void)
{
#if (_ENABLE_MENU_OLED == _ON)
    bEnable_OFF_RS_Message = _FALSE;
#endif	
    SET_OSD_STATE(_MENU_NONE);
    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncDisableOsd();
    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    g_ucOsdWidth = 0;
    g_ucOsdHeight = 0;
    g_ucOsdWidthB = 0;
    g_ucOsdHeightB = 0;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
{
    DWORD ulX  = 0;		//  WORD -> DWORD
    DWORD ulY = 0;
    BYTE ucFonWidth = 12;
    BYTE ucFonHeight = 18;
    BYTE ucHorizontalDelayStep = 4;
    BYTE ucTempWidth = g_ucOsdWidth;
    BYTE ucTempHeight = g_ucOsdHeight;

    if((enumOsdPositionType == _OSD_POSITION_GLOBAL_B) ||
       (enumOsdPositionType == _OSD_POSITION_FONT_B))
    {
        ucTempWidth = g_ucOsdWidthB;
        ucTempHeight = g_ucOsdHeightB;
    }

    if(ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_1_PIXEL)
    {
        ucHorizontalDelayStep = 1;
    }

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth *= 2;
        ucFonHeight *= 2;
    }

    if(ucType == _POS_PERCENT)
    {
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempHeight * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempWidth * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#else
        ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
        ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
#endif
    }
    else
    {
        // Notice!!! if osd set double size need to chek real position
        ulX = usHPos;
        ulY = usVPos;
    }
	if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ulX = ulX / 2;
        ulY = ulY / 2;
    }
    OsdFuncSetPosition(enumOsdPositionType, ulX, ulY);
}

/*
BYTE FactoryKeyBuf[11]={0,0,0,0,0,0,0,0,0,0,0};	
BYTE Fcnt=0xff;
bit fgFctoryTimeCheck=0; 
bit fgFactoryOK=0;		

//MENU ->DOWN ->DOWN->DOWN-> UP->UP->UP-> DOWN->UP->DOWN->SELECT(EXIT)

//code BYTE tFACTRY_CODE[]={_MENU_KEY_MESSAGE,_FUNC_KEY_MESSAGE,_UP_KEY_MESSAGE,_SELECT_KEY_MESSAGE}; 
code BYTE tFACTRY_CODE[]={	_MENU_KEY_MESSAGE,
							_DOWN_KEY_MESSAGE,_DOWN_KEY_MESSAGE,_DOWN_KEY_MESSAGE,
							_UP_KEY_MESSAGE,_UP_KEY_MESSAGE,_UP_KEY_MESSAGE,
							_DOWN_KEY_MESSAGE,_UP_KEY_MESSAGE,_DOWN_KEY_MESSAGE,
							_SELECT_KEY_MESSAGE
						};


void OsdFactoryEnterKeyProcess(BYTE ucKeyMessage)	
{
	int i;
	
	if(ucKeyMessage==_MENU_KEY_MESSAGE) 
		Fcnt = 0;

	if(g_usTimerFactoryKeyTimeOut == 0) 	// clear Buffer
	{
		Fcnt = 0;

		for(i=0; i<11; i++)
			FactoryKeyBuf[i] = 0;
	}

	switch(Fcnt)
	{
		case 0:
			FactoryKeyBuf[0] = ucKeyMessage;
			Fcnt = 1;
			//printf("Input Key#1\n");
			
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 1:
			//if(FactoryKeyBuf[0] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[1] = ucKeyMessage;
				Fcnt = 2;
				//printf("Input Key#2\n");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 2:
			//if(FactoryKeyBuf[1] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[2] = ucKeyMessage;
				Fcnt = 3;
				//printf("Input Key#3\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 3:
			//if(FactoryKeyBuf[2] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[3] = ucKeyMessage;
				Fcnt = 4;
				//printf("Input Key#3\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 4:
			//if(FactoryKeyBuf[3] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[4] = ucKeyMessage;
				Fcnt = 5;
				//printf("Input Key#4\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 5:
			//if(FactoryKeyBuf[4] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[5] = ucKeyMessage;
				Fcnt = 6;
				//printf("Input Key#5\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 6:
			//if(FactoryKeyBuf[5] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[6] = ucKeyMessage;
				Fcnt = 7;
				//printf("Input Key#6\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 7:
			//if(FactoryKeyBuf[6] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[7] = ucKeyMessage;
				Fcnt = 8;
				//printf("Input Key#7\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 8:
			//if(FactoryKeyBuf[7] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[8] = ucKeyMessage;
				Fcnt = 9;
				//printf("Input Key#8\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 9:
			//if(FactoryKeyBuf[8] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[9] = ucKeyMessage;
				Fcnt = 10;
				//printf("Input Key#9\n\r");
			}
			g_usTimerFactoryKeyTimeOut = 700; // 700ms
			break;
		case 10:
			//if(FactoryKeyBuf[9] != ucKeyMessage)	// Repeat Key Blocking
			{
				FactoryKeyBuf[10] = ucKeyMessage;
				Fcnt=0xff;
				//printf("Input Key#10\n\r");
			
				for(i=0; i<11; i++)
				{
					if(FactoryKeyBuf[i] ==  tFACTRY_CODE[i])
						fgFactoryOK=1;
					else
					{
						fgFactoryOK=0;
						break;	
					}
				}
			}

			if(fgFactoryOK)
			{
				printf("Factory Key OK!!\n\r");
				//RTDFactoryMainMenu();
				SET_OSD_SERVICE(_ON);
				OsdDispDisableOsd();
				SET_OSD_STATE(_MENU_SERVICE1);
				OsdDispMainMenu();
				fgFactoryOK = 0;
			}
			
			break;
	}
}
*/

extern void SicpIrTransferSend(BYTE ucId, BYTE uc08, BYTE uc09, BYTE uc10 ); 	


void OsdDispHotKeyProcess(BYTE ucKeyMessage)	//  Hot Key	
{
	switch(ucKeyMessage)
	{
		case _VOL_P_KEY_MESSAGE: // _VOL_P_IR_MESSAGE:
		case _VOL_M_KEY_MESSAGE: // _VOL_M_IR_MESSAGE:
		
			if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) /*&& (GET_OSD_STATE() == _MENU_NONE)*/)
			{
				if(GET_OSD_STATE() == _MENU_HOTKEY_VOLUME)
				{
					if(GET_KEYMESSAGE() == _VOL_P_KEY_MESSAGE)		// Change Key Message
						SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
					else if(GET_KEYMESSAGE() == _VOL_M_KEY_MESSAGE)
						SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
				}
				else
				{
					OsdDispHotKeyOsdMessage(_MENU_HOTKEY_VOLUME);
				}
				
				if(GET_OSD_VOLUME_MUTE() == _ON)	// Mute Off
				{
					SET_OSD_VOLUME_MUTE(_OFF);
					UserAdjustAudioMuteSwitch();
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
				}
				
				ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
	        }
			break;
			
		case _LEFT_KEY_MESSAGE:
		case _RIGHT_KEY_MESSAGE:

#if(_ENABLE_LEFT_RIGHT_KEY_VOLUME == _ON)	
			if(GET_OSD_STATE()!=_MENU_HOTKEY_VOLUME)
			{
				if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_STATE() == _MENU_NONE))
				{
					OsdDispHotKeyOsdMessage(_MENU_HOTKEY_VOLUME);

					if(GET_OSD_VOLUME_MUTE() == _ON)	// Mute Off
					{
						SET_OSD_VOLUME_MUTE(_OFF);
						UserAdjustAudioMuteSwitch();
						SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
					}
				}
				ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
			}
			
#else
			if(GET_OSD_STATE() == _MENU_HOTKEY_VOLUME)	// Hold Key _LEFT_KEY_MESSAGE / _RIGHT_KEY_MESSAGE
			{
				SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
			}
#endif
			break;

		
		case _MUTE_KEY_MESSAGE: // (Mute hot key )_F1_KEY_MESSAGE => _F3_KEY_MESSAGE
	
			if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) /*&& (GET_OSD_STATE() == _MENU_NONE)*/)
			{
				/*
				if(GET_OSD_STATE()==_MENU_HOTKEY_MUTE)
				{
					if(GET_KEYMESSAGE() == _F3_KEY_MESSAGE)		// Change Key Message	
						SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
				}
				else
				*/
				{
					if(GET_OSD_VOLUME_MUTE() == _ON)	// Toggle Mute
						SET_OSD_VOLUME_MUTE(_OFF);
					else
						SET_OSD_VOLUME_MUTE(_ON);
					
					UserAdjustAudioMuteSwitch();
					SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
					
					OsdDispHotKeyOsdMessage(_MENU_HOTKEY_MUTE);
				}
				ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);	 
			}
			break;

		/*
		case _SETID_KEY_MESSAGE: // _F1_IR_MESSAGE:	//  Not Used
		
			if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) )
			{
					//OsdDispHotKeyOsdMessage(_MENU_HOTKEY_DISPLAY_MODE);
					//OsdDispHotKeyOsdMessage(_MENU_HOTKEY_PIP_SWAP);
					//OsdDispHotKeyOsdMessage(_MENU_HOTKEY_BLK_ONOFF);
					
					if(GET_OSD_STATE()==_MENU_IR_BLASTER)
					{
						if(GET_OSD_STATE()==_MENU_IR_BLASTER)
							SicpIrTransferSend(0, 'E', 'X', 'I' );	
							
						OsdDispDisableOsd();
						ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
					}
					else
					{
						OsdDispHotKeyOsdMessage(_MENU_IR_BLASTER);
						//SetFocus(_MENU_SECTION_DIALOG, ROW_OFFSET+_ITEM_3);
						ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);	
					}
			}
			break;
		*/
	}
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispClearSelectColor(BYTE ucUpDown)
{
    if(ucUpDown == _UP)
    {
        ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
    }
    else
    {
        ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
        // ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
    }
}



//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------

void OsdSection3ItemPageDraw(BYTE ucMainItem)
{
    int i;

    ScalerTimerWaitForEvent(_EVENT_DVS);
    for (i = 0; i < _OSD_MAIN_MENU_HEIGHT; i++)
        OsdFuncClearOsd(ROW(i), COL(_MENU_SECTION_2_WIN_X), _MENU_SECTION_2_WIDTH, 1); // Clear Item

    switch (ucMainItem)
    {
    case _MENU_INPUT_SOURCE1_ADJ:
        OsdSubMenuItemText(_MENU_INPUT, _MENU_INPUT_SOURCE1_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_INPUT_SOURCE2_ADJ:
        OsdSubMenuItemText(_MENU_INPUT, _MENU_INPUT_SOURCE2_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_INPUT_SOURCE3_ADJ:
        OsdSubMenuItemText(_MENU_INPUT, _MENU_INPUT_SOURCE3_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_INPUT_SOURCE4_ADJ:
        OsdSubMenuItemText(_MENU_INPUT, _MENU_INPUT_SOURCE4_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_PICTURE_GAMMA_ADJ:
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_GAMMA_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
#if (_ENABLE_MENU_REGION == _ON)
    case _MENU_PICTURE_REGION_ADJ:
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_REGION_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
#endif
    case _MENU_COLOR_EFFECT_ADJ:
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_EFFECT_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;

    case _MENU_COLOR_GAMMA_ADJ:
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_GAMMA_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;

    case _MENU_COLOR_TEMPERATURE_ADJ:
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_TEMPERATURE_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_COLOR_SURGICAL_ADJ:
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_SURGICAL_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
#if (_ENABLE_MENU_REGION == _ON)
    case _MENU_COLOR_REGION_ADJ:
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_REGION_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
#endif
    case _MENU_SCREEN_OVERSCAN_ADJ:
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_OVERSCAN_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SCREEN_ASPECT_ADJ:
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_ASPECT_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SCREEN_MONO_COLOR_ADJ:
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_MONO_COLOR_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SCREEN_ROTATE_ADJ:
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_ROTATE_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    //case _MENU_SCREEN_DISPLAY_MODE_ADJ:
    //    OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_DISPLAY_MODE_ADJ, COLOR(_CP_WHITE, _CP_BG));
    //    break;
    //case _MENU_SCREEN_PIP_POSITION_ADJ:
    //    OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_PIP_POSITION_ADJ, COLOR(_CP_WHITE, _CP_BG));
    //    break;
    //case _MENU_SCREEN_PIP_SIZE_ADJ:
    //    break;
//    case _MENU_OSD_ROTATE_ADJ:
//        OsdSubMenuItemText(_MENU_SETUP, _MENU_OSD_ROTATE_ADJ, COLOR(_CP_WHITE, _CP_BG));
//        break;

//    case _MENU_OSD_LANGUAGE_ADJ:
//        OsdSubMenuItemText(_MENU_SETUP, _MENU_OSD_LANGUAGE_ADJ, COLOR(_CP_WHITE, _CP_BG));
//        break;

    case _MENU_AUDIO_MUTE_ADJ:
        OsdSubMenuItemText(_MENU_AUDIO, _MENU_AUDIO_MUTE_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;

    case _MENU_AUDIO_SOURCE_ADJ:
        OsdSubMenuItemText(_MENU_AUDIO, _MENU_AUDIO_SOURCE_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;

//    case _MENU_DP_OPTION_VERSION_ADJ:
//        OsdSubMenuItemText(_MENU_SETUP, _MENU_DP_OPTION_VERSION_ADJ, COLOR(_CP_WHITE, _CP_BG));
//        break;

//    case _MENU_DP_OPTION_MST_ADJ:
//        OsdSubMenuItemText(_MENU_SETUP, _MENU_DP_OPTION_MST_ADJ, COLOR(_CP_WHITE, _CP_BG));
//        break;

//    case _MENU_DP_OPTION_RESOLUTION_ADJ:
//        OsdSubMenuItemText(_MENU_SETUP, _MENU_DP_OPTION_RESOLUTION_ADJ, COLOR(_CP_WHITE, _CP_BG));
//        break;

//    case _MENU_DP_OPTION_CLONE_ADJ:
//        OsdSubMenuItemText(_MENU_SETUP, _MENU_DP_OPTION_CLONE_ADJ, COLOR(_CP_WHITE, _CP_BG));
//        break;
    case _MENU_SETUP_POWERSAVE_ADJ:
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_POWERSAVE_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SETUP_KEYLOCK_ADJ:
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_KEYLOCK_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SETUP_BACKLIGHT_CONTROL_ADJ:
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_BACKLIGHT_CONTROL_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SETUP_RESET_ADJ:
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_RESET_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
    case _MENU_SETUP_STABILIZER_CONTROL_ADJ:
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_STABILIZER_CONTROL_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
#endif
#if (_ENABLE_MENU_VGA == _ON)
    case _MENU_VGA_AUTO_ADJ:
        OsdSubMenuItemText(_MENU_VGA, _MENU_VGA_AUTO_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
#endif
    case _MENU_SERVICE_D0NAME_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D0NAME_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_D1NAME_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D1NAME_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_D2NAME_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D2NAME_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_D3NAME_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D3NAME_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_BACKLIGHT_INVERT_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_INVERT_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_LOGO_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_LOGO_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_DP_OPTION_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_DP_OPTION_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_LIGHTSENSOR_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_LIGHTSENSOR_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_FAN_OPTION_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_FAN_OPTION_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;    
    case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_USERASSIGN_UP_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_UP_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_USERASSIGN_DOWN_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_DOWN_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_USERASSIGN_LEFT_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_LEFT_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_USERASSIGN_RIGHT_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_RIGHT_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_OLED_OFFRS_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE_OLED, _MENU_SERVICE_OLED_OFFRS_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_OLED_JB_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE_OLED, _MENU_SERVICE_OLED_JB_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ:
        OsdSubMenuItemText(_MENU_SERVICE_OLED, _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ, COLOR(_CP_WHITE, _CP_BG));
        break;
    default:
        break;
    }
}



void OsdSourcePageDraw(void)
{
    int i;
    for (i = 4; i < _MENU_SOURCE_HEIGHT; i++)
        OsdFuncClearOsd(ROW(i), COL(0), _MENU_SOURCE_WIDTH, 1); // Clear Item

#if (_ENABLE_MENU_VGA == _ON)
	OsdPropPutpString(ROW(_ITEM_4), COL(4), _PFONT_PAGE_3, tsOsdSourceAuto, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_5), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_6), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_7), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_8), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_9), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
#else
	OsdPropPutpString(ROW(_ITEM_4), COL(4), _PFONT_PAGE_3, tsOsdSourceAuto, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    // OsdPropPutpString(ROW(_ITEM_4), COL(4), _PFONT_PAGE_3, tsOsdSourceA0VGA, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_5), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_6), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_7), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    OsdPropPutpString(ROW(_ITEM_8), COL(4), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    
#endif
}




void OsdMainMenuPageDraw(void)	
{
    int i;
	if (GET_OSD_SERVICE())
    {
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(_MENU_SECTION_0_WIN_X), WIDTH(_MENU_SECTION_0_WIDTH + _MENU_SECTION_1_WIDTH), HEIGHT(5 + 2), _CP_DARKGRAY);
#endif
        OsdPropPutpString(ROW(_ITEM_1), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdService1, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_2), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdService2, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_3), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdService3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_4), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdService_UserAssign, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_5), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdOLED, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    }
    else
    {
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(_MENU_SECTION_0_WIN_X), WIDTH(_MENU_SECTION_0_WIDTH + _MENU_SECTION_1_WIDTH), HEIGHT(7 + 2), _CP_DARKGRAY);
        //OsdWindowDrawingByFont(_OSD_WINDOW_3, ROW(1), COL(_MENU_SECTION_0_WIN_X), WIDTH(_MENU_SECTION_0_WIDTH + _MENU_SECTION_1_WIDTH), HEIGHT(7), _CP_DARKGRAY);
#endif

        OsdPropPutpString(ROW(_ITEM_1), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdInfo, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_2), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdInput, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_3), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdPicture, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_4), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdColor, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_5), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdScreen, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_6), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdAudio, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        OsdPropPutpString(ROW(_ITEM_7), COL(_MENU_SECTION_0_STR_X), _PFONT_PAGE_0, tsOsdSetup, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());


        //OsdMainMenuItemDraw();
        for(i=0; i<_OSD_MAIN_MENU_HEIGHT; i++)
            OsdFuncClearOsd(ROW(i), COL(_MENU_SECTION_1_WIN_X), _MENU_SECTION_1_WIDTH+_MENU_SECTION_2_WIDTH, 1);	// Clear Item	

        OsdSubMenuPageDraw(_MENU_INFO);
    }
	

}
void OsdMainMenuItemDraw(void)
{

    switch (GET_OSD_INPUT_PORT_OSD_ITEM())
    {
        case _OSD_INPUT_D0:
            OsdPropPutpStringRight(ROW(_ITEM_2), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _OSD_INPUT_D1:
            OsdPropPutpStringRight(ROW(_ITEM_2), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _OSD_INPUT_D2:
            OsdPropPutpStringRight(ROW(_ITEM_2), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _OSD_INPUT_D3:
            OsdPropPutpStringRight(ROW(_ITEM_2), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _OSD_INPUT_AUTO:
            OsdPropPutpStringRight(ROW(_ITEM_2), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdSourceAuto, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
    }

    OsdPropPutpStringRight(ROW(_ITEM_1), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, OsdDisplayGetResolutionStringP(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

    OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdClearText, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    #if(_MEDICAL_SURGICAL == _ON)
    OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdClearText, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    if (GET_OSD_PCM_STATUS() == _PCM_OSD_BT709)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdBT709, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    else if (GET_OSD_PCM_STATUS() == _PCM_OSD_DCI_P3)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdDCI_P3, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    else if (GET_OSD_PCM_STATUS() == _PCM_OSD_BT2020)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdBT2020, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    else if (GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdGammaNative, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

    #else
    OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdClearText, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    if (GET_COLOR_TEMP_TYPE() == _CT_D56)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdTempD56, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    else if (GET_COLOR_TEMP_TYPE() == _CT_D65)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdTempD65, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    else if (GET_COLOR_TEMP_TYPE() == _CT_D93)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdTempD93, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    else if (GET_COLOR_TEMP_TYPE() == _CT_USER)
        OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdTempUser, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    #endif
    // OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdClearText, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    switch (GET_OSD_ASPECT_RATIO_TYPE())
    {
    case _OSD_ASPECT_RATIO_FULL:
        OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdFill, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        break;
    case _OSD_ASPECT_RATIO_16_BY_9:
        OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsd16_9, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        break;
    case _OSD_ASPECT_RATIO_4_BY_3:
        OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsd4_3, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        break;
    case _OSD_ASPECT_RATIO_5_BY_4:
        OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsd5_4, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        break;
    case _OSD_ASPECT_RATIO_ORIGIN:
        OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdOrigin, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        break;
    case _OSD_ASPECT_RATIO_USER:
        OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_0_SUB_STR_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_0, tsOsdSourceAuto, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
        break;
    }
  
    // OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_0_SUB_STR_WIDTH), WIDTH(8), _PFONT_PAGE_0, tsOsdGamma18, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    OsdPropShowNumberRight(ROW(_ITEM_6), COL(_MENU_SECTION_0_SUB_NUM_X), GET_OSD_VOLUME(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_0, COLOR(_CP_WHITE, _CP_BG));
}


void OsdSubMenuPageDraw(BYTE ucMainItem)
{
    ScalerTimerWaitForEvent(_EVENT_DVS);

#if (_DYNAMIC_OSD_WINDOW != _ON)
    // OsdWindowDrawingByFont(_MENU_SECTION1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), _CP_DARKGRAY);
#endif
    switch (ucMainItem)
    {

	case _MENU_INFO:

        /*
        #if(_DYNAMIC_OSD_WINDOW ==_ON)
                    OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET+2+2), _CP_DARKGRAY);
        #endif
                    OsdPropPutpString(ROW(1), COL(_MENU_SECTION_1_STR_X+5+1+2), _PFONT_PAGE_ITEM_10, tsOsdInfo, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
                    OsdSubMenuItemText(_MENU_INFO,_MENU_INFO_FW_VERSION,COLOR(_CP_WHITE, _CP_BG));
                    OsdSubMenuItemText(_MENU_INFO,_MENU_INFO_SERIAL_NUM,COLOR(_CP_WHITE, _CP_BG));
        */
        OsdDispShowInformation();
        break;
	
    case _MENU_INPUT:
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 1 + 2), _CP_DARKGRAY);
#endif
            OsdSubMenuItemText(_MENU_INPUT, _MENU_INPUT_SOURCE1, COLOR(_CP_WHITE, _CP_BG));
            break;

        break;
    case _MENU_PICTURE:
        // OsdPropPutpString(ROW(1), COL(_MENU_SECTION_1_STR_X+5+1), _PFONT_PAGE_ITEM_10, tsOsdPicture, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
#if (_DYNAMIC_OSD_WINDOW == _ON)
#if (_ENABLE_MENU_REGION == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 7 + 2), _CP_DARKGRAY);
#else
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 6 + 2), _CP_DARKGRAY);
#endif
#endif
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_BLACKLEVEL, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_CONTRAST, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_CHROMA, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_SHARPNESS, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_GAMMA, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_RESETTODEFAULT, COLOR(_CP_WHITE, _CP_BG));
#if (_ENABLE_MENU_REGION == _ON)
        OsdSubMenuItemText(_MENU_PICTURE, _MENU_PICTURE_REGION, COLOR(_CP_WHITE, _CP_BG));
#endif
        break;
    case _MENU_COLOR:
        // OsdPropPutpString(ROW(1), COL(_MENU_SECTION_1_STR_X + 5 + 1), _PFONT_PAGE_1, tsOsdColor, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
#if (_DYNAMIC_OSD_WINDOW == _ON)
#if (_ENABLE_MENU_REGION == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 8 + 2), _CP_DARKGRAY);
#else
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 7 + 2), _CP_DARKGRAY);
#endif
#endif
#if(_MEDICAL_SURGICAL == _ON)
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_SURGICAL, COLOR(_CP_WHITE, _CP_BG));
#else
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_TEMPERATURE, COLOR(_CP_WHITE, _CP_BG));
#endif
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_BIAS_R, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_BIAS_G, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_BIAS_B, COLOR(_CP_WHITE, _CP_BG));

        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_GAIN_R, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_GAIN_G, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_GAIN_B, COLOR(_CP_WHITE, _CP_BG));
#if (_ENABLE_MENU_REGION == _ON)
        OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_REGION, COLOR(_CP_WHITE, _CP_BG));
#endif
        /*
                if (GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) == _CT_USER) //  Change Region -> Redraw User Color Item
                {
        #if (_DYNAMIC_OSD_WINDOW == _ON)
                    OsdWindowDrawingByFont(_OSD_WINDOW_5, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 8 + 2), _CP_DARKGRAY);
        #endif
                    OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_TEMP_USER_R, COLOR(_CP_WHITE, _CP_BG));
                    OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_TEMP_USER_G, COLOR(_CP_WHITE, _CP_BG));
                    OsdSubMenuItemText(_MENU_COLOR, _MENU_COLOR_TEMP_USER_B, COLOR(_CP_WHITE, _CP_BG));
                }
                else
                {
        #if (_DYNAMIC_OSD_WINDOW == _ON)
        #if (_ENABLE_MENU_REGION == _ON)
                    OsdWindowDrawingByFont(_OSD_WINDOW_5, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 4 + 2), _CP_DARKGRAY);
        #else
                    OsdWindowDrawingByFont(_OSD_WINDOW_5, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 3 + 2), _CP_DARKGRAY);
        #endif
        #endif
                    OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH, 1); // Clear Item
                    OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH, 1);
                    OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH, 1);
                }
                */
        break;
    case _MENU_SCREEN:
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 4 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_OVERSCAN, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_ASPECT, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_ROTATE, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_MONO_COLOR, COLOR(_CP_WHITE, _CP_BG));
        //OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_DISPLAY_MODE, COLOR(_CP_WHITE, _CP_BG));
        //OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_PIP_POSITION, COLOR(_CP_WHITE, _CP_BG));
        //OsdSubMenuItemText(_MENU_SCREEN, _MENU_SCREEN_PIP_SIZE, COLOR(_CP_WHITE, _CP_BG));

        break;
    case _MENU_AUDIO:
        // OsdPropPutpString(ROW(1), COL(_MENU_SECTION_1_STR_X + 5 + 1 + 1), _PFONT_PAGE_ITEM_10, tsOsdAudio, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 3 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_AUDIO, _MENU_AUDIO_INFO, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_AUDIO, _MENU_AUDIO_VOLUME, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_AUDIO, _MENU_AUDIO_MUTE, COLOR(_CP_WHITE, _CP_BG));
        break;
        /*
                case _MENU_DP_OPTION:
                    OsdPropPutpString(ROW(1), COL(_MENU_SECTION_1_STR_X+5-1+2), _PFONT_PAGE_ITEM_10, tsOsdDpOption, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
        #if(_DYNAMIC_OSD_WINDOW ==_ON)
                    OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET+4+2), _CP_DARKGRAY);
        #endif
                    OsdSubMenuItemText(_MENU_DP_OPTION,_MENU_DP_OPTION_VERSION,COLOR(_CP_WHITE, _CP_BG));
                    OsdSubMenuItemText(_MENU_DP_OPTION,_MENU_DP_OPTION_MST,COLOR(_CP_WHITE, _CP_BG));
                    OsdSubMenuItemText(_MENU_DP_OPTION,_MENU_DP_OPTION_RESOLUTION,COLOR(_CP_WHITE, _CP_BG));
                    OsdSubMenuItemText(_MENU_DP_OPTION,_MENU_DP_OPTION_CLONE,COLOR(_CP_WHITE, _CP_BG));
                    break;
        */
    case _MENU_SETUP:
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 6 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_POWERSAVE, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_KEYLOCK, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_BACKLIGHT, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_BACKLIGHT_CONTROL, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_RESET, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_STABILIZER_CONTROL, COLOR(_CP_WHITE, _CP_BG));
#else
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 5 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_POWERSAVE, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_KEYLOCK, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_BACKLIGHT, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_BACKLIGHT_CONTROL, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SETUP, _MENU_SETUP_RESET, COLOR(_CP_WHITE, _CP_BG));
#endif
        break;

#if (_ENABLE_MENU_VGA == _ON)
    case _MENU_VGA:
        OsdPropPutpString(ROW(1), COL(_MENU_SECTION_1_STR_X + 5 + 1 + 1), _PFONT_PAGE_ITEM_10, tsOsdVga, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 5 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_VGA, _MENU_VGA_AUTO, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_VGA, _MENU_VGA_H_POSI, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_VGA, _MENU_VGA_V_POSI, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_VGA, _MENU_VGA_CLOCK, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_VGA, _MENU_VGA_PHASE, COLOR(_CP_WHITE, _CP_BG));
        break;
#endif

    
    case _MENU_SERVICE1:
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 7 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_SCREENTEST, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_TEMPERATURE, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_WHITEBALANCE, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D0NAME, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D1NAME, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D2NAME, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE1, _MENU_SERVICE_D3NAME, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE2:
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 6 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_MIN, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_MAX, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_INVERT, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_FREQ, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_LOGO, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_STABILUX, COLOR(_CP_WHITE, _CP_BG));
        break;
#else
#if (_DYNAMIC_OSD_WINDOW == _ON)
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 6 + 2), _CP_DARKGRAY);
#endif
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_MIN, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_MAX, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_INVERT, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_BACKLIGHT_FREQ, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_LOGO, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE2, _MENU_SERVICE_LOGO_LIST, COLOR(_CP_WHITE, _CP_BG));
        break;
#endif
    case _MENU_SERVICE3:
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 6 + 2), _CP_DARKGRAY);
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_DP_OPTION, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_LIGHTSENSOR, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_FAN_OPTION, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_FAN_SPEED, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_USER_BACKUP_CONFIG, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE3, _MENU_SERVICE_RESTORE_FACTORY_DEFAULT, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_USERASSIGN:
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 4 + 2), _CP_DARKGRAY);
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_UP, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_DOWN, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_LEFT, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE_USERASSIGN, _MENU_SERVICE_USERASSIGN_RIGHT, COLOR(_CP_WHITE, _CP_BG));
        break;
    case _MENU_SERVICE_OLED:
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 3 + 2), _CP_DARKGRAY);
        OsdSubMenuItemText(_MENU_SERVICE_OLED, _MENU_SERVICE_OLED_OFFRS, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE_OLED, _MENU_SERVICE_OLED_JB, COLOR(_CP_WHITE, _CP_BG));
        OsdSubMenuItemText(_MENU_SERVICE_OLED, _MENU_SERVICE_OLED_SEQUENCE_TIME, COLOR(_CP_WHITE, _CP_BG));
        break;
    default:
        break;
    }
}
void OsdSubMenuItemText(BYTE ucMainItem, BYTE ucSubItem, BYTE ucColor)
{

    switch (ucMainItem)
    {
    case _MENU_INPUT:
        switch (ucSubItem)
        {
        case _MENU_INPUT_SOURCE1:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdSource, ucColor, GET_OSD_LANGUAGE());
            OsdFuncSetOsdItemFlag();
            OsdDispNumberAndText(_MENU_INPUT_SOURCE1,  GET_OSD_INPUT_PORT_OSD_ITEM()/*OsdDisplayGetSourcePortStringP(SysSourceGetInputPort())*/, ucColor);
            break;
        case _MENU_INPUT_SOURCE1_ADJ:
#if (_ENABLE_MENU_VGA == _ON)

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(6 + 2), _CP_DARKGRAY);

			OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            
#else

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5 + 2), _CP_DARKGRAY);

			OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
            // OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceA0VGA, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            
#endif
            break;
        case _MENU_INPUT_SOURCE2:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdSource2, ucColor, GET_OSD_LANGUAGE());
            OsdFuncSetOsdItemFlag();
            OsdDispNumberAndText(_MENU_INPUT_SOURCE2, GET_OSD_INPUT_PORT_OSD_ITEM(), ucColor);
            break;
        case _MENU_INPUT_SOURCE2_ADJ:
#if (_ENABLE_MENU_VGA == _ON)

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(6 + 2), _CP_DARKGRAY);

            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
#else

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5 + 2), _CP_DARKGRAY);

            // OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceA0VGA, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
#endif
            break;
        case _MENU_INPUT_SOURCE3:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdSource3, ucColor, GET_OSD_LANGUAGE());
            OsdFuncSetOsdItemFlag();
            OsdDispNumberAndText(_MENU_INPUT_SOURCE3, GET_OSD_INPUT_PORT_OSD_ITEM(), ucColor);
            break;
        case _MENU_INPUT_SOURCE3_ADJ:
#if (_ENABLE_MENU_VGA == _ON)

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(6 + 2), _CP_DARKGRAY);

            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
#else

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5 + 2), _CP_DARKGRAY);

            // OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceA0VGA, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
#endif
            break;
        case _MENU_INPUT_SOURCE4:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdSource4, ucColor, GET_OSD_LANGUAGE());
            OsdFuncSetOsdItemFlag();
            OsdDispNumberAndText(_MENU_INPUT_SOURCE4, GET_OSD_INPUT_PORT_OSD_ITEM(), ucColor);
            break;
        case _MENU_INPUT_SOURCE4_ADJ:
#if (_ENABLE_MENU_VGA == _ON)

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(6 + 2), _CP_DARKGRAY);

            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
#else

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5 + 2), _CP_DARKGRAY);

            // OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceA0VGA, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
#endif
            break;
        }
        break;
    case _MENU_PICTURE:
        switch (ucSubItem)
        {
        case _MENU_PICTURE_BLACKLEVEL:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBlacklevel, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_PICTURE_BLACKLEVEL, GET_OSD_BRIGHTNESS(), ucColor);
            break;
        case _MENU_PICTURE_CONTRAST:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdContrast, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(), ucColor);
            break;
        case _MENU_PICTURE_CHROMA:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdChroma, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_PICTURE_CHROMA, GET_OSD_SATURATION(), ucColor);
            break;
        case _MENU_PICTURE_SHARPNESS:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdSharpness, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(), ucColor);
            break;
        case _MENU_PICTURE_GAMMA:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdGamma, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_PICTURE_GAMMA, GET_OSD_GAMMA(), ucColor);
            break;
        case _MENU_PICTURE_GAMMA_ADJ:
#if (_CUSTOMER_TYPE == _CUSTOMER_MEDICAL)
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma22, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaDicom, ucColor, GET_OSD_LANGUAGE());
#elif (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT) // RC2, RC3
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaRC2, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaRC3, ucColor, GET_OSD_LANGUAGE());
#else
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma20, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma22, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma24, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaDicom, ucColor, GET_OSD_LANGUAGE());
#endif
            break;
        case _MENU_PICTURE_RESETTODEFAULT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdResettoDefault, ucColor, GET_OSD_LANGUAGE());
            break;
#if (_ENABLE_MENU_REGION == _ON)
/*
        case _MENU_PICTURE_REGION:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdRegion, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_PICTURE_REGION, GET_OSD_SELECT_REGION(), ucColor);
            break;
        case _MENU_PICTURE_REGION_ADJ:
            switch (GET_OSD_DISPLAY_MODE())
            {
            case _OSD_DM_1P:

                OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(1), _CP_DARKGRAY);
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd1PFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_2P_LR:

                OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PLRL, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PLRR, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PLRFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_2P_TB:

                OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PTBT, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PTBB, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PTBFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_2P_PIP:

                OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PPipMain, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PPipSub, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PPipFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_3P:

                OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(9), _CP_DARKGRAY);


                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_10), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_11), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_12), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_13), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_14), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_15), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_4P:

                OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(9), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_10), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_11), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_12), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_13), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_14), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_15), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
                break;
            }
            break;
*/
#endif
        }
        break;

    case _MENU_COLOR:
        switch (ucSubItem)
        {

        case _MENU_COLOR_TEMPERATURE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdColorTemp, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_TEMPERATURE, GET_COLOR_TEMP_TYPE(), ucColor);
            break;
        case _MENU_COLOR_TEMPERATURE_ADJ:
#if 0//(_CUSTOMER_TYPE == _CUSTOMER_MEDICAL) 
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(4 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdBT709, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdDCI_P3, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdBT2020, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
#else
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(4 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdTempD56, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdTempD65, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdTempD93, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdTempUser, ucColor, GET_OSD_LANGUAGE());
#endif
            break;
        case _MENU_COLOR_SURGICAL:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdColorGamut, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_SURGICAL, GET_OSD_PCM_STATUS(), ucColor);
            break;
        case _MENU_COLOR_SURGICAL_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(4 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdBT709, ucColor, GET_OSD_LANGUAGE());
            // OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdDCI_P3, ucColor, GET_OSD_LANGUAGE());
            // OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdBT2020, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdDCI_P3, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdBT2020, COLOR(_CP_GRAY, _CP_BG), GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_COLOR_BIAS_R:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdRedBIAS, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_BIAS_R, GET_COLOR_BIAS_R(), ucColor);
            // GET_COLOR_TEMP_TYPE_USER_R()
            break;
        case _MENU_COLOR_BIAS_G:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdGreenBIAS, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_BIAS_G, GET_COLOR_BIAS_G(), ucColor);
            break;
        case _MENU_COLOR_BIAS_B:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBlueBIAS, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_BIAS_B, GET_COLOR_BIAS_B(), ucColor);
            break;
        case _MENU_COLOR_GAIN_R:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdRedGain, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_GAIN_R, GET_COLOR_GAIN_R(), ucColor);
            break;
        case _MENU_COLOR_GAIN_G:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdGreenGain, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_GAIN_G, GET_COLOR_GAIN_G(), ucColor);
            break;
        case _MENU_COLOR_GAIN_B:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBlueGain, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_GAIN_B, GET_COLOR_GAIN_B(), ucColor);
            break;
#if (_ENABLE_MENU_REGION == _ON)
/*
        case _MENU_COLOR_REGION:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM8), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdRegion, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_REGION, GET_OSD_SELECT_REGION(), ucColor);
            break;
        case _MENU_COLOR_REGION_ADJ:
            switch (GET_OSD_DISPLAY_MODE())
            {
            case _OSD_DM_1P:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(1), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd1PFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_2P_LR:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PLRL, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PLRR, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PLRFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_2P_TB:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PTBT, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PTBB, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PTBFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_2P_PIP:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PPipMain, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PPipSub, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PPipFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_3P:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(9), _CP_DARKGRAY);


                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_10), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_11), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_12), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
                break;
            case _OSD_DM_4P:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(9), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_10), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_11), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_12), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
                break;
            }
            break;
            */
#endif
            // NOT USE
        case _MENU_COLOR_EFFECT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdColorEffect, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_EFFECT, GET_OSD_COLOR_EFFECT(), ucColor);
            break;
        case _MENU_COLOR_EFFECT_ADJ:

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5), _CP_DARKGRAY);

            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdStandard, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGame, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdMovie, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPhoto, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdVidid, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_COLOR_GAMMA:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdGamma, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_COLOR_GAMMA, GET_OSD_GAMMA(), ucColor);
            break;
        case _MENU_COLOR_GAMMA_ADJ:

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5), _CP_DARKGRAY);

            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGammaOff, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma18, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma20, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma22, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdGamma24, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
    case _MENU_SCREEN:
        switch (ucSubItem)
        {
        case _MENU_SCREEN_OVERSCAN:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdOverScan, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SCREEN_OVERSCAN, GET_OSD_OVERSCAN_STATUS(), ucColor);
            break;

        case _MENU_SCREEN_ASPECT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdAspectRatio, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SCREEN_ASPECT, GET_OSD_ASPECT_RATIO_TYPE(), ucColor);
            break;
        case _MENU_SCREEN_MONO_COLOR:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdMonoColor, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SCREEN_MONO_COLOR, GET_OSD_COLOR_EFFECT(), ucColor);
            break;
        case _MENU_SCREEN_ROTATE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdDispRotate, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SCREEN_ROTATE, GET_OSD_DISP_ROTATE(), ucColor);
            break;
		/*
        case _MENU_SCREEN_DISPLAY_MODE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdDispMode, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SCREEN_DISPLAY_MODE, GET_OSD_DISPLAY_MODE(), ucColor);
            break;
        case _MENU_SCREEN_PIP_POSITION:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdPipPosition, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SCREEN_PIP_POSITION, GET_OSD_PIP_POSITION_TYPE(), ucColor);
            break;
        case _MENU_SCREEN_PIP_SIZE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdPipSize, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SCREEN_PIP_SIZE, GET_OSD_PIP_SIZE(), ucColor);
            break;
		*/
        case _MENU_SCREEN_OVERSCAN_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SCREEN_ASPECT_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5 + 2), _CP_DARKGRAY);
            //OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
            //OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd16_9, ucColor, GET_OSD_LANGUAGE());
            //OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4_3, ucColor, GET_OSD_LANGUAGE());
            //OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdFill, ucColor, GET_OSD_LANGUAGE());

			OsdPropPutpStringLeft(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdFill, ucColor, GET_OSD_LANGUAGE());
			OsdPropPutpStringLeft(ROW(ROW_OFFSET+_ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd16_9, ucColor, GET_OSD_LANGUAGE());
			OsdPropPutpStringLeft(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4_3, ucColor, GET_OSD_LANGUAGE());
			OsdPropPutpStringLeft(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd5_4, ucColor, GET_OSD_LANGUAGE());
			OsdPropPutpStringLeft(ROW(ROW_OFFSET+_ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOrigin, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SCREEN_MONO_COLOR_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdStd, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdMono, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdNight, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SCREEN_ROTATE_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdRotate0, ucColor, GET_OSD_LANGUAGE());
            //OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdRotate90, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdRotate180, ucColor, GET_OSD_LANGUAGE());
            //OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdRotate270, ucColor, GET_OSD_LANGUAGE());
            break;
		/*
        case _MENU_SCREEN_DISPLAY_MODE_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(6 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd1P, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PLR, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PTB, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2PPIP, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd3P, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_10), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd4P, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SCREEN_PIP_POSITION_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(4 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPipLT, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPipRT, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPipLB, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPipRB, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SCREEN_PIP_SIZE_ADJ:
            break;
			
		*/	
        }
        break;

    case _MENU_AUDIO:
        switch (ucSubItem)
        {
        case _MENU_AUDIO_INFO:
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, OsdDisplayGetAudioStringP(), ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_AUDIO_VOLUME:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdVolume, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME(), ucColor);
            break;
        case _MENU_AUDIO_MUTE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdMute, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_AUDIO_MUTE, GET_OSD_VOLUME_MUTE(), ucColor);
            break;
        case _MENU_AUDIO_MUTE_ADJ:

            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
    /*
    case _MENU_DP_OPTION:
        switch(ucSubItem)
        {
            case _MENU_DP_OPTION_VERSION:
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdDpVersion, ucColor, GET_OSD_LANGUAGE());
                OsdDispNumberAndText(_MENU_DP_OPTION_VERSION, GET_OSD_DP_D0_VERSION(), ucColor);	// D0-DP2
                //OsdDispNumberAndText(_MENU_DP_OPTION_VERSION, GET_OSD_DP_D1_VERSION(), ucColor);	// D1-DP1
                break;
            case _MENU_DP_OPTION_VERSION_ADJ:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET+_ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdDpVer1_1, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdDpVer1_2, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdDpVer1_3, ucColor, GET_OSD_LANGUAGE());
                break;
            case _MENU_DP_OPTION_MST:
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdDpMst, ucColor, GET_OSD_LANGUAGE());
                OsdDispNumberAndText(_MENU_DP_OPTION_MST, GET_OSD_DP_MST(), ucColor);
                break;
            case _MENU_DP_OPTION_MST_ADJ:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdMstD0DP2, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdMstD1DP1, ucColor, GET_OSD_LANGUAGE());
                break;
            case _MENU_DP_OPTION_RESOLUTION:
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdDpResolution, ucColor, GET_OSD_LANGUAGE());
                OsdDispNumberAndText(_MENU_DP_OPTION_RESOLUTION, UserCommonNVRamGetSystemData(_DP_EDID_SELECT), ucColor);
                break;
            case _MENU_DP_OPTION_RESOLUTION_ADJ:

                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET+_ITEM_3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3), _CP_DARKGRAY);

                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd1080P, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd1440P, ucColor, GET_OSD_LANGUAGE());
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsd2160P, ucColor, GET_OSD_LANGUAGE());
                break;
            case _MENU_DP_OPTION_CLONE:
                OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdDpCloneMode, ucColor, GET_OSD_LANGUAGE());
#if(_MULTI_DISPLAY_MAX != 0x01)
                if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
                {
                    OsdDispNumberAndText(_MENU_DP_OPTION_CLONE, GET_OSD_CLONE_MODE_MTP(), ucColor);
                }
                else
#endif
                {
                    OsdDispNumberAndText(_MENU_DP_OPTION_CLONE, GET_OSD_CLONE_MODE_1P(), ucColor);
                }
                break;
            case _MENU_DP_OPTION_CLONE_ADJ:
#if(_MULTI_DISPLAY_MAX != 0x01)
                if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
                {

                #if(_ENABLE_MENU_VGA == _ON)

                    OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(6), _CP_DARKGRAY);

                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_STR_X+1), _PFONT_PAGE_3, tsOsdOFF2, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceA0VGA, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD0DP2, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD1DP1, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD2HDMI2, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD3HDMI1, ucColor, GET_OSD_LANGUAGE());
                #else

                    OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(5), _CP_DARKGRAY);

                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_STR_X+1), _PFONT_PAGE_3, tsOsdOFF2, ucColor, GET_OSD_LANGUAGE());
                    //OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceA0VGA, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD0DP2, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD1DP1, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD2HDMI2, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD3HDMI1, ucColor, GET_OSD_LANGUAGE());
                #endif
                }
                else
#endif
                {

                    OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2), _CP_DARKGRAY);

                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
                    OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
                }
                break;
        }
        break;
    */
    case _MENU_SETUP:

        switch (ucSubItem)
        {
        case _MENU_SETUP_POWERSAVE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdPowerSave, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_POWERSAVE, GET_OSD_POWERSAVE_TIME(), ucColor);
            break;
        case _MENU_SETUP_POWERSAVE_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(4 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSaveOff, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave5Sec, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave30Sec, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave60Sec, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SETUP_KEYLOCK:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdKeyLock, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_KEYLOCK, GET_OSD_KEYLOCK(), ucColor);
            break;
        case _MENU_SETUP_KEYLOCK_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdUnLock, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdLock, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SETUP_BACKLIGHT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBacklight, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_BACKLIGHT, GET_OSD_BACKLIGHT(), ucColor);
            break;
        case _MENU_SETUP_BACKLIGHT_ADJ:
            break;
        case _MENU_SETUP_BACKLIGHT_CONTROL:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBacklightControl, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_BACKLIGHT_CONTROL, GET_OSD_BACKLIGHT_CONTROL(), ucColor);
            break;
        case _MENU_SETUP_BACKLIGHT_CONTROL_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdLinear, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdCorved, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SETUP_RESET:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdResettoDefault, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SETUP_RESET_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdNO, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdYES, ucColor, GET_OSD_LANGUAGE());
            break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
        case _MENU_SETUP_STABILIZER_CONTROL:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdStabilizer, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_STABILIZER_CONTROL, GET_OSD_STABILIZER(), ucColor);
            break;
        case _MENU_SETUP_STABILIZER_CONTROL_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
#endif
            /*
        case _MENU_SETUP_RESET:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdReset, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_RESET, GET_OSD_RESET_MODE(), ucColor);
            break;
        case _MENU_SETUP_RESET_ADJ:

            OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2), _CP_DARKGRAY);

            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdNO, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdYES, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SETUP_POWERSAVE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdPowerSave, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_POWERSAVE, GET_OSD_POWERSAVE_TIME(), ucColor);
            break;
        case _MENU_SETUP_POWERSAVE_ADJ:

            OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(4), _CP_DARKGRAY);

            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSaveOff, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave5Sec, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave30Sec, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave60Sec, ucColor, GET_OSD_LANGUAGE());

            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave1Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave2Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave5Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave30Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave60Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_10), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave120Min, ucColor, GET_OSD_LANGUAGE());

            break;
        case _MENU_SETUP_SETID:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdSetId, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_SETID, GET_OSD_SETID(), ucColor);
            break;
        case _MENU_SETUP_BACKLIGHT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBacklight, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SETUP_BACKLIGHT, GET_OSD_BACKLIGHT(), ucColor);
            break;
            */
        }
        break;
#if (_ENABLE_MENU_VGA == _ON)
    case _MENU_VGA:
        switch (ucSubItem)
        {
        case _MENU_VGA_AUTO:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdAutoAdjust, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_VGA_AUTO, GET_VGA_AUTOADJ_MODE(), ucColor);
            break;
        case _MENU_VGA_AUTO_ADJ:

            OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2), _CP_DARKGRAY);

            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_VGA_H_POSI:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdHPosition, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_VGA_H_POSI, GET_VGA_MODE_ADJUST_H_POSITION(), ucColor);
            break;
        case _MENU_VGA_V_POSI:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdVPosition, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_VGA_V_POSI, GET_VGA_MODE_ADJUST_V_POSITION(), ucColor);
            break;
        case _MENU_VGA_CLOCK:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdClock, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_VGA_CLOCK, GET_VGA_MODE_ADJUST_CLOCK(), ucColor);
            break;
        case _MENU_VGA_PHASE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdPhase, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_VGA_PHASE, GET_VGA_MODE_ADJUST_PHASE(), ucColor);
            break;
        }
        break;
#endif
    case _MENU_INFO:
        switch (ucSubItem)
        {
        case _MENU_INFO_MODEL:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_INFORMATION, tsOsdModel, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_INFO_INPUT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_INFORMATION, tsOsdInput, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_INFO_FORAMT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_INFORMATION, tsOsdFormat, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_INFO_COLOR_TEMP:
        #if(_MEDICAL_SURGICAL == _ON)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_INFORMATION, tsOsdColorGamut, ucColor, GET_OSD_LANGUAGE());
        #else
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_INFORMATION, tsOsdColorTemp, ucColor, GET_OSD_LANGUAGE());
        #endif
            break;
        case _MENU_INFO_RANGE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_INFORMATION, tsOsdRange, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_INFO_FW_VERSION:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_INFORMATION, OsdGetBoardVersionString(), ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
    case _MENU_SERVICE1:
        switch (ucSubItem)
        {

        case _MENU_SERVICE_SCREENTEST:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdScreenTest, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_TEMPERATURE:
#if (_ENABLE_FAN_CONTROL == _ON)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdTemperature, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_TEMPERATURE, GET_OSD_MAX_TEMP(), ucColor);
#endif
            break;
        case _MENU_SERVICE_WHITEBALANCE:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdWhiteBalance, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_D0NAME:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdD0Name, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_D0NAME, GET_OSD_D0_NAME(), ucColor);
            break;
        case _MENU_SERVICE_D0NAME_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD1DP1, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD0DP2, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourcePc, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_D1NAME:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdD1Name, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_D1NAME, GET_OSD_D1_NAME(), ucColor);
            break;
        case _MENU_SERVICE_D1NAME_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD1DP1, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD0DP2, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourcePc, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_D2NAME:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdD2Name, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_D2NAME, GET_OSD_D2_NAME(), ucColor);
            break;
        case _MENU_SERVICE_D2NAME_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD3HDMI1, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD2HDMI2, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourcePc, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_D3NAME:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdD3Name, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_D3NAME, GET_OSD_D3_NAME(), ucColor);
            break;
        case _MENU_SERVICE_D3NAME_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(6 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD3HDMI1, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceD2HDMI2, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourcePc, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_10), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceSDI, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_11), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSource10GSFP, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_12), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdSourceDVI, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
    case _MENU_SERVICE2:
        switch (ucSubItem)
        {
        case _MENU_SERVICE_BACKLIGHT_MIN:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBacklightMin, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_MIN, GET_BACKLIGHT_MIN(), ucColor);
            break;
        case _MENU_SERVICE_BACKLIGHT_MIN_ADJ:
            break;
        case _MENU_SERVICE_BACKLIGHT_MAX:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBacklightMax, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_MAX, GET_BACKLIGHT_MAX(), ucColor);
            break;
        case _MENU_SERVICE_BACKLIGHT_MAX_ADJ:
            break;
        case _MENU_SERVICE_BACKLIGHT_INVERT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBLUInvert, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_INVERT, GET_OSD_BACKLIGHT_INVERT(), ucColor);
            break;
        case _MENU_SERVICE_BACKLIGHT_INVERT_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_BACKLIGHT_FREQ:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdBLUFreq, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_BACKLIGHT_FREQ, GET_OSD_BACKLIGHT_FREQ(), ucColor);
            break;
        case _MENU_SERVICE_BACKLIGHT_FREQ_ADJ:
            break;
        case _MENU_SERVICE_LOGO:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdLOGO, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_LOGO, GET_OSD_LOGO_ON(), ucColor);
            break;
        case _MENU_SERVICE_LOGO_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_LOGO_LIST:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdLogoSelect, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_LOGO_LIST, GET_OSD_LOGO_LIST(), ucColor);
            break;
        case _MENU_SERVICE_LOGO_LIST_ADJ:
            break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
        case _MENU_SERVICE_STABILUX:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdStabilux, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_STABILUX, GET_OSD_STABILUX(), ucColor);
            break;
        case _MENU_SERVICE_STABILUX_ADJ:
            break;
#endif
        }
        break;
    case _MENU_SERVICE3:
        switch (ucSubItem)
        {
        case _MENU_SERVICE_DP_OPTION:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdDpOption, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_DP_OPTION, GET_OSD_DP_MST(), ucColor);
            break;
        case _MENU_SERVICE_DP_OPTION_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdClone, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdMstD0DP2, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdMstD1DP1, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_LIGHTSENSOR:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdLightSensor, ucColor, GET_OSD_LANGUAGE());
#if (_ENABLE_LIGHT_SENSOR == _ON)
            OsdDispNumberAndText(_MENU_SERVICE_LIGHTSENSOR, GET_OSD_LIGHT_SENSOR_STATUS(), ucColor);
#endif
            break;
        case _MENU_SERVICE_LIGHTSENSOR_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_FAN_OPTION:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdFanControl, ucColor, GET_OSD_LANGUAGE());
#if (_ENABLE_FAN_CONTROL == _ON)
            OsdDispNumberAndText(_MENU_SERVICE_FAN_OPTION, GET_OSD_FAN_STATUS(), ucColor);
#endif
            break;
        case _MENU_SERVICE_FAN_OPTION_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdFanAuto, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_FAN_SPEED:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdFanSpeed, ucColor, GET_OSD_LANGUAGE());
#if (_ENABLE_FAN_CONTROL == _ON)
            OsdDispNumberAndText(_MENU_SERVICE_FAN_SPEED, GET_OSD_FAN_PWM(), ucColor);
#endif
            break;
        case _MENU_SERVICE_FAN_SPEED_ADJ:
            break;
        case _MENU_SERVICE_USER_BACKUP_CONFIG:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsBACKUP_USER_CONFIG, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_USER_BACKUP_CONFIG_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdNO, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdYES, ucColor, GET_OSD_LANGUAGE());
            break;  
        case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdResettoDefault, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_RESTORE_FACTORY_DEFAULT_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdNO, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdYES, ucColor, GET_OSD_LANGUAGE());
            break;  

        }
        break;
    case _MENU_SERVICE_USERASSIGN:
        switch (ucSubItem)
        {
        case _MENU_SERVICE_USERASSIGN_UP:
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH, 1);
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsUserAssign_UpKey, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_UP, GET_OSD_USER_ASSIGN_UP(), ucColor);
            break;
        case _MENU_SERVICE_USERASSIGN_UP_ADJ:
            g_usAdjustValue = GET_OSD_USER_ASSIGN_UP();
            g_usBackupValue = GET_OSD_USER_ASSIGN_UP();
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), _MENU_SECTION_2_WIDTH + 5, 1); // Clear Item
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH+5), HEIGHT(1 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_USERASSIGN_DOWN:
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH, 1);
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsUserAssign_DownKey, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_DOWN, GET_OSD_USER_ASSIGN_DOWN(), ucColor);
            break;
        case _MENU_SERVICE_USERASSIGN_DOWN_ADJ:
            g_usAdjustValue = GET_OSD_USER_ASSIGN_DOWN();
            g_usBackupValue = GET_OSD_USER_ASSIGN_DOWN();
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), _MENU_SECTION_2_WIDTH + 5, 1); // Clear Item
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH+5), HEIGHT(1 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;  
        case _MENU_SERVICE_USERASSIGN_LEFT:
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH, 1);
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsUserAssign_LeftKey, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_LEFT, GET_OSD_USER_ASSIGN_LEFT(), ucColor);
            break;
        case _MENU_SERVICE_USERASSIGN_LEFT_ADJ:
            g_usAdjustValue = GET_OSD_USER_ASSIGN_LEFT();
            g_usBackupValue = GET_OSD_USER_ASSIGN_LEFT();
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_WIN_X), _MENU_SECTION_2_WIDTH + 5, 1); // Clear Item
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH+5), HEIGHT(1 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;  
        case _MENU_SERVICE_USERASSIGN_RIGHT:
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _MENU_SECTION_1_WIDTH + _MENU_SECTION_2_WIDTH, 1);
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsUserAssign_RightKey, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_USERASSIGN_RIGHT, GET_OSD_USER_ASSIGN_RIGHT(), ucColor);
            break;
        case _MENU_SERVICE_USERASSIGN_RIGHT_ADJ:
            g_usAdjustValue = GET_OSD_USER_ASSIGN_RIGHT();
            g_usBackupValue = GET_OSD_USER_ASSIGN_RIGHT();
            OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_WIN_X), _MENU_SECTION_2_WIDTH + 5, 1); // Clear Item
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH+5), HEIGHT(1 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
            break;
            default:
                break;  
        }
    break;
#if (_ENABLE_MENU_OLED == _ON)
    case _MENU_SERVICE_OLED:
        switch (ucSubItem)
        {
        case _MENU_SERVICE_OLED_OFFRS:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdOFFRS, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_OLED_OFFRS, GET_OSD_OLED_OFFRS_STATUS(), ucColor);
            break;
        case _MENU_SERVICE_OLED_OFFRS_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET ), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(3 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOLEDAutoRun, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOLEDEndRun, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOLEDNow, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_OLED_JB:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdJB, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_OLED_JB_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(2 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MENU_SERVICE_OLED_SEQUENCE_TIME:
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_STR_X), _PFONT_PAGE_1, tsOsdSequenceTime, ucColor, GET_OSD_LANGUAGE());
            OsdDispNumberAndText(_MENU_SERVICE_OLED_SEQUENCE_TIME, GET_OSD_OLED_SEQUENCE_TIME(), ucColor);
            break;
        case _MENU_SERVICE_OLED_SEQUENCE_TIME_ADJ:
            OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(7 + 2), _CP_DARKGRAY);
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave30Sec, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave1Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave2Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave5Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave30Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_8), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave60Min, ucColor, GET_OSD_LANGUAGE());
            OsdPropPutpStringLeft(ROW(ROW_OFFSET + _ITEM_9), COL(_MENU_SECTION_2_STR_X), _PFONT_PAGE_3, tsOsdPowerSave120Min, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
#endif
    default:
        break;
    }
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenu(void)	
{
	BYTE hPosi,vPosi;	
	
	g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;
	g_ucFontPointer3 = _OSD_PAGE_3_START;	
	
	OsdFuncCloseWindow(_OSD_WINDOW_ALL);	//  Menu->Source garbege
    OsdFuncDisableOsd();

	//------------------------------------------------------------------------------
	//SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);	//  OSD Rotate Test
	//SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_90);
	//SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_180);
	//SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_270);

	//SET_OSD_TRANSPARENCY_STATUS(30);				//  OSD Transparency Test ( 0~255 )
		
	//------------------------------------------------------------------------------
	
    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    //OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncBlending(_OSD_TRANSPARENCY_DISABLE);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
    {
		//OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(_MENU_SECTION_0_WIN_X), WIDTH(_MENU_SECTION_0_WIDTH), HEIGHT(g_ucOsdHeight), _CP_DARKGRAY);
		//OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(g_ucOsdHeight), _CP_DARKGRAY); 
		//OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(0), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(g_ucOsdHeight), _CP_DARKGRAY);
 
    }

    // Realtek Mark
    //OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));

	OsdMainMenuPageDraw();	

	//OsdWindowDrawingByFont(_OSD_WINDOW_5_1, ROW(_ITEM_1), COL(_MENU_SECTION_0_WIN_X), WIDTH(_MENU_SECTION_0_WIDTH), HEIGHT(1), _CP_GRAY);	// Focus Window
	//OsdWindowDrawingByFont(_OSD_WINDOW_5_2, ROW(_ITEM_1), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(1), _CP_GRAY);
	//OsdWindowDrawingByFont(_OSD_WINDOW_5_3, ROW(_ITEM_1), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(1), _CP_GRAY);
	SetFocus(_MENU_SECTION_0, ROW_OFFSET+_ITEM_1);	

	
		
	//ScalerOsdWindowDisable(_MENU_SECTION_0_WINDOW);	//  Disable Window Test
	//ScalerOsdWindowDisable(_MENU_SECTION_1_WINDOW);
	//ScalerOsdWindowDisable(_MENU_SECTION_2_WINDOW);
	//-------------------------------------------------------------------------------- //  OSD Slider And Number Test
	/*

	//OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
	
	g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);	
    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
	OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
	*/
	//--------------------------------------------------------------------------------
	

	//OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
	
	switch(GET_OSD_ROTATE_STATUS())	//  OSD Rotate
	{
		case _OSD_ROTATE_DEGREE_0:
			hPosi = GET_OSD_HPOS();
			vPosi = GET_OSD_VPOS();
			break;
		case _OSD_ROTATE_DEGREE_90:
			hPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
			vPosi = GET_OSD_HPOS();
			break;
		case _OSD_ROTATE_DEGREE_180:
			hPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
			vPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
			break;
		case _OSD_ROTATE_DEGREE_270:
			hPosi = GET_OSD_VPOS();
			vPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
			break;
		default:
			hPosi = GET_OSD_HPOS();
			vPosi = GET_OSD_VPOS();
			break;		
	}
	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, hPosi, vPosi);
	
    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}

// VLC
// font put 1 bit
// font put 1 bit table
// font put 2 bit
// font put 2 bit table
// font put 4 bit
// font put 4 bit color

// Prop
// font put prop string

// window
// draw window

void OsdDispNumberAndText(WORD usOsdState, WORD usValue, BYTE ucColor)
{
    BYTE ucDone = _FALSE;

    g_usAdjustValue = usValue;

    switch (usOsdState)
    {
    //-----------INPUT
    case _MENU_INPUT_SOURCE1:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _OSD_INPUT_AUTO)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_A0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D1)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D2)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D3)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;

    case _MENU_INPUT_SOURCE2:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _OSD_INPUT_AUTO)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_A0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D1)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D2)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D3)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;

    case _MENU_INPUT_SOURCE3:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _OSD_INPUT_AUTO)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_A0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D1)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D2)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D3)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;

    case _MENU_INPUT_SOURCE4:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _OSD_INPUT_AUTO)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_A0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, OsdDisplayGetSourcePortStringP(_A0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D0)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D1)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D2)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_INPUT_D3)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;

    //--------------------------------------------------------------------------------------------------------------------------------- PICTURE
    case _MENU_PICTURE_BLACKLEVEL:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_1, ucColor);
        break;
    case _MENU_PICTURE_CONTRAST:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_2, ucColor);
        break;
    case _MENU_PICTURE_CHROMA:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_3, ucColor);
        break;
    case _MENU_PICTURE_SHARPNESS:
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_4, ucColor);
        break;
    case _MENU_PICTURE_GAMMA:
		OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
#if (_CUSTOMER_TYPE == _CUSTOMER_MEDICAL)
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdClearText6, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _GAMMA_OFF)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_22)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGamma22, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_DICOM)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGammaDicom, ucColor, GET_OSD_LANGUAGE());
        break;
#elif (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdClearText6, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _GAMMA_OFF)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_22)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGammaRC2, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_DICOM)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGammaRC3, ucColor, GET_OSD_LANGUAGE());
        break;
#else
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdClearText6, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _GAMMA_OFF)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_20)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGamma20, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_22)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGamma22, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_24)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGamma24, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_DICOM)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdGammaDicom, ucColor, GET_OSD_LANGUAGE());
        break;
#endif
#if (_ENABLE_MENU_REGION == _ON)
/*
    case _MENU_PICTURE_REGION:
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        switch (GET_OSD_DISPLAY_MODE())
        {
        case _OSD_DM_1P:
            if (g_usAdjustValue == _OSD_SR_1P_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd1PFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_LR:
            if (g_usAdjustValue == _OSD_SR_2P_LR_L)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PLRL, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_LR_R)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PLRR, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_LR_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PLRFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_TB:
            if (g_usAdjustValue == _OSD_SR_2P_TB_T)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PTBT, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_TB_B)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PTBB, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_TB_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PTBFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_PIP:
            if (g_usAdjustValue == _OSD_SR_2P_PIP_MAIN)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PPipMain, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_PIP_SUB)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PPipSub, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_PIP_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd2PPipFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_3P:
			if (g_usAdjustValue == _OSD_SR_3P_LT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_LT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_LB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_LB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_4P:
            if (g_usAdjustValue == _OSD_SR_4P_LT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_LT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_LB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_LB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
*/
#endif
    //---------------------------------------------------------------------------------------------------------------------------------- COLOR
    case _MENU_COLOR_EFFECT:
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _COLOREFFECT_STANDARD)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdStandard, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _COLOREFFECT_GAME)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdGame, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _COLOREFFECT_MOVIE)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdMovie, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _COLOREFFECT_PHOTO)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdPhoto, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _COLOREFFECT_VIVID)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdVidid, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _COLOREFFECT_USER)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdUser, ucColor, GET_OSD_LANGUAGE());

        break;
    case _MENU_COLOR_GAMMA:
#if (_CUSTOMER_TYPE == _CUSTOMER_MEDICAL)
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _GAMMA_OFF)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_22)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGamma22, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_DICOM)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGammaDicom, ucColor, GET_OSD_LANGUAGE());
        break;
#elif (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _GAMMA_OFF)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_22)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGammaRC2, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_DICOM)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGammaRC3, ucColor, GET_OSD_LANGUAGE());
        break;
#else
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _GAMMA_OFF)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_20)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGamma18, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_22)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGamma20, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_24)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGamma22, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _GAMMA_DICOM)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdGamma24, ucColor, GET_OSD_LANGUAGE());
        break;
#endif
    case _MENU_COLOR_TEMPERATURE:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _CT_D56)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdTempD56, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _CT_D65)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdTempD65, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _CT_D93)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdTempD93, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _CT_USER)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdTempUser, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_COLOR_SURGICAL:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR + 1), _MENU_SECTION_1_SUB_STR_WIDTH - 1, 1); // Clear Item
        if (g_usAdjustValue == _PCM_OSD_BT709)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR + 1), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH - 1), _PFONT_PAGE_ITEM_1, tsOsdBT709, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _PCM_OSD_DCI_P3)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR + 1), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH - 1), _PFONT_PAGE_ITEM_1, tsOsdDCI_P3, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _PCM_OSD_BT2020)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR + 1), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH - 1), _PFONT_PAGE_ITEM_1, tsOsdBT2020, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _PCM_OSD_NATIVE)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR + 1), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH - 1), _PFONT_PAGE_ITEM_1, tsOsdGammaNative, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_COLOR_BIAS_R:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_2, ucColor);
        break;
    case _MENU_COLOR_BIAS_G:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_3, ucColor);
        break;
    case _MENU_COLOR_BIAS_B:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _COLOR_BIAS_MAX, _COLOR_BIAS_MIN, _COLOR_BIAS_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_4, ucColor);
        break;
    case _MENU_COLOR_GAIN_R:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_5, ucColor);
        break;
    case _MENU_COLOR_GAIN_G:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_6, ucColor);
        break;
    case _MENU_COLOR_GAIN_B:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _COLOR_GAIN_MAX, _COLOR_GAIN_MIN, _COLOR_GAIN_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_7, ucColor);
        break;
#if (_ENABLE_MENU_REGION == _ON)
    case _MENU_COLOR_REGION:
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        switch (GET_OSD_DISPLAY_MODE())
        {
        case _OSD_DM_1P:
            if (g_usAdjustValue == _OSD_SR_1P_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd1PFull, ucColor, GET_OSD_LANGUAGE());
            break;
		/*	
        case _OSD_DM_2P_LR:
            if (g_usAdjustValue == _OSD_SR_2P_LR_L)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PLRL, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_LR_R)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PLRR, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_LR_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PLRFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_TB:
            if (g_usAdjustValue == _OSD_SR_2P_TB_T)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PTBT, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_TB_B)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PTBB, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_TB_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PTBFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_PIP:
            if (g_usAdjustValue == _OSD_SR_2P_PIP_MAIN)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PPipMain, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_PIP_SUB)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PPipSub, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_2P_PIP_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd2PPipFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_3P:
            if (g_usAdjustValue == _OSD_SR_3P_LT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_LT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_LB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_LB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_RB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_3P_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_4P:
            if (g_usAdjustValue == _OSD_SR_4P_LT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_LT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_LB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_LB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PLBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RT_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRTIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RT_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRTOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RB_INSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRBIn, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_RB_OUTSIDE)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PRBOut, ucColor, GET_OSD_LANGUAGE());
            else if (g_usAdjustValue == _OSD_SR_4P_FULL)
                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsd4PFull, ucColor, GET_OSD_LANGUAGE());
            break;
        */    
        }
        break;
#endif
    //---------------------------------------------------------------------------------------------------------------------------------- SCREEN
    case _MENU_SCREEN_OVERSCAN:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _OSD_ON)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdON, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_OFF)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SCREEN_ASPECT:	
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR + 2), _MENU_SECTION_1_SUB_STR_WIDTH , 1);	// Clear Item
        switch (g_usAdjustValue)
        {
        case _OSD_ASPECT_RATIO_FULL:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdFill, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_ASPECT_RATIO_16_BY_9:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsd16_9, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_ASPECT_RATIO_4_BY_3:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsd4_3, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_ASPECT_RATIO_5_BY_4:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsd5_4, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_ASPECT_RATIO_ORIGIN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdOrigin, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_ASPECT_RATIO_USER:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdSourceAuto, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
    case _MENU_SCREEN_MONO_COLOR:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        switch (g_usAdjustValue)
        {
        case _COLOREFFECT_STANDARD:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdStd, ucColor, GET_OSD_LANGUAGE());
            break;
        case _COLOREFFECT_MONO:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdMono, ucColor, GET_OSD_LANGUAGE());
            break;
        case _COLOREFFECT_NIGHT:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdNight, ucColor, GET_OSD_LANGUAGE());
            break;
        }

        break;
    case _MENU_SCREEN_ROTATE:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        switch (g_usAdjustValue)
        {
        case _DISP_ROTATE_0:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, tsOsdRotate0, ucColor, GET_OSD_LANGUAGE());
            break;
        //case _DISP_ROTATE_90:
        //    OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, tsOsdRotate90, ucColor, GET_OSD_LANGUAGE());
        //    break;
        case _DISP_ROTATE_180:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, tsOsdRotate180, ucColor, GET_OSD_LANGUAGE());
            break;
        //case _DISP_ROTATE_270:
        //    OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, tsOsdRotate270, ucColor, GET_OSD_LANGUAGE());
        //    break;
        }
        break;
	/*	
    case _MENU_SCREEN_DISPLAY_MODE:
        switch (g_usAdjustValue)
        {
        case _OSD_DM_1P:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsd1P, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_LR:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsd2PLR, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_TB:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsd2PTB, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_2P_PIP:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsd2PPIP, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_3P:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsd3P, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OSD_DM_4P:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsd4P, ucColor, GET_OSD_LANGUAGE());
            break;
        }
    case _MENU_SCREEN_PIP_POSITION:
        switch (GET_OSD_PIP_POSITION_TYPE())
        {
        case _PIP_POSITON_LT:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_6, tsOsdPipLT, ucColor, GET_OSD_LANGUAGE());
            break;
        case _PIP_POSITON_RT:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_6, tsOsdPipRT, ucColor, GET_OSD_LANGUAGE());
            break;
        case _PIP_POSITON_LB:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_6, tsOsdPipLB, ucColor, GET_OSD_LANGUAGE());
            break;
        case _PIP_POSITON_RB:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_6, tsOsdPipRB, ucColor, GET_OSD_LANGUAGE());
            break;
        case _PIP_POSITON_MIDDLE:
        case _PIP_POSITON_USER:
            break;
        }
        break;
    case _MENU_SCREEN_PIP_SIZE:
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_7, ucColor);
        break;
	*/
    //---------------------------------------------------------------------------------------------------------------------------------- OSD SETTING
//    case _MENU_OSD_H_POSITION:
//        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
//        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_1, ucColor);
//        break;
//    case _MENU_OSD_V_POSITION:
//        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
//        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_2, ucColor);
//        break;
//    case _MENU_OSD_TRANSPARENCY:
//        // g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
//        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_3, ucColor);
//        break;
//    case _MENU_OSD_TIMEOUT:
//        // g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
//        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_4, ucColor);
//        break;
//    case _MENU_OSD_ROTATE:
//        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_5, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
//        if (g_usAdjustValue == _OSD_ROTATE_DEGREE_0)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_5, tsOsdRotate0, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _OSD_ROTATE_DEGREE_90)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_5, tsOsdRotate90, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _OSD_ROTATE_DEGREE_180)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_5, tsOsdRotate180, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _OSD_ROTATE_DEGREE_270)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_5, tsOsdRotate270, ucColor, GET_OSD_LANGUAGE());
//        break;
//    case _MENU_OSD_LANGUAGE:
//        // g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_LANGUAGE(), _CHINESE_T, _ENGLISH, _OFF);
//        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
//        if (g_usAdjustValue == _ENGLISH)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsdEnglish, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _CHINESE_T)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_6, tsOsdChinese, ucColor, GET_OSD_LANGUAGE());
//        break;
    //---------------------------------------------------------------------------------------------------------------------------------- AUDIO
    case _MENU_AUDIO_VOLUME:
        g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_1, ucColor);
        break;
    case _MENU_AUDIO_MUTE:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        // OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _ON)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdON, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OFF)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_AUDIO_SOURCE:
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
		/*
        if (g_usAdjustValue == _OSD_AUDIO_SOURCE_ANALOG)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsdAudioLineIn, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_AUDIO_SOURCE_DIGITAL_REGION_1)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsdAudioDigital1, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_AUDIO_SOURCE_DIGITAL_REGION_2)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsdAudioDigital2, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_AUDIO_SOURCE_DIGITAL_REGION_3)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsdAudioDigital3, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _OSD_AUDIO_SOURCE_DIGITAL_REGION_4)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsdAudioDigital4, ucColor, GET_OSD_LANGUAGE());
        */    
        break;
    //---------------------------------------------------------------------------------------------------------------------------------- DP OPTION
//    case _MENU_DP_OPTION_VERSION:
//        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
//        if (g_usAdjustValue == _DP_VER_1_DOT_1)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdDpVer1_1, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _DP_VER_1_DOT_2)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdDpVer1_2, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _DP_VER_1_DOT_3)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdDpVer1_3, ucColor, GET_OSD_LANGUAGE());
//        break;
//    case _MENU_DP_OPTION_MST:
//        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
//        if (g_usAdjustValue == _MST_OFF)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
// 
//        else if (g_usAdjustValue == _MST_D0) // D0-DP2
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdMstD0DP2, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _MST_D1) // D1-DP1
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdMstD1DP1, ucColor, GET_OSD_LANGUAGE());
// 
//        break;
//    case _MENU_DP_OPTION_RESOLUTION:
//        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
//        if (g_usAdjustValue == _DP_EDID_1080P)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsd1080P, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _DP_EDID_2560_1440)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsd1440P, ucColor, GET_OSD_LANGUAGE());
//        else if (g_usAdjustValue == _DP_EDID_4K2K_60HZ)
//            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_3, tsOsd2160P, ucColor, GET_OSD_LANGUAGE());
//        break;
//    case _MENU_DP_OPTION_CLONE:
//        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
//		/*
//#if (_MULTI_DISPLAY_MAX != 0x01)
//        if (GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
//        {
//            if (g_usAdjustValue == _OSD_CLONE_MTP_OFF)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
//            else if (g_usAdjustValue == _OSD_CLONE_MTP_A0)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdSourceA0VGA, ucColor, GET_OSD_LANGUAGE());
//            else if (g_usAdjustValue == _OSD_CLONE_MTP_D0)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdCloneD0DP2, ucColor, GET_OSD_LANGUAGE());
//            else if (g_usAdjustValue == _OSD_CLONE_MTP_D1)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdCloneD1DP1, ucColor, GET_OSD_LANGUAGE());
//            else if (g_usAdjustValue == _OSD_CLONE_MTP_D2)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdCloneD2HDMI2, ucColor, GET_OSD_LANGUAGE());
//            else if (g_usAdjustValue == _OSD_CLONE_MTP_D3)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdCloneD3HDMI1, ucColor, GET_OSD_LANGUAGE());
//        }
//        else
//#endif
//        {
//            if (g_usAdjustValue == _OSD_CLONE_1P_OFF)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
//            else if (g_usAdjustValue == _OSD_CLONE_1P_ON)
//                OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_4, tsOsdON, ucColor, GET_OSD_LANGUAGE());
//        }
//		*/
//        break;
    //---------------------------------------------------------------------------------------------------------------------------------- SETUP
    case _MENU_SETUP_POWERSAVE:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _POWER_SAVE_OFF)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdPowerSaveOff, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _POWER_SAVE_5SEC)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdPowerSave5Sec, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _POWER_SAVE_30SEC)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdPowerSave30Sec, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _POWER_SAVE_1MIN)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdPowerSave60Sec, ucColor, GET_OSD_LANGUAGE());
        /*
        else if(g_usAdjustValue ==_POWER_SAVE_1MIN)
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdPowerSave1Min, ucColor, GET_OSD_LANGUAGE());
        else if(g_usAdjustValue ==_POWER_SAVE_2MIN)
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdPowerSave2Min, ucColor, GET_OSD_LANGUAGE());
        else if(g_usAdjustValue ==_POWER_SAVE_5MIN)
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdPowerSave5Min, ucColor, GET_OSD_LANGUAGE());
        else if(g_usAdjustValue ==_POWER_SAVE_30MIN)
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdPowerSave30Min, ucColor, GET_OSD_LANGUAGE());
        else if(g_usAdjustValue ==_POWER_SAVE_60MIN)
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdPowerSave60Min, ucColor, GET_OSD_LANGUAGE());
        else if(g_usAdjustValue ==_POWER_SAVE_120MIN)
            OsdPropPutpString(ROW(ROW_OFFSET+_ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_2, tsOsdPowerSave120Min, ucColor, GET_OSD_LANGUAGE());
        */
        break;
    case _MENU_SETUP_KEYLOCK:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _KEY_UNLOCK)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdUnLock, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _KEY_LOCK)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdLock, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SETUP_BACKLIGHT:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (GET_OSD_BACKLIGHT_CONTROL() == _CORVED)
        {
            g_usAdjustValue = UserCommonAdjustRealValueToPercentCurved(g_usAdjustValue,_BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
			OsdPropShowNumberFloat(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_SUB_NUM_X - 2), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_3, ucColor);
        }
        else
        {
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_3, ucColor);
        }
        break;
    case _MENU_SETUP_BACKLIGHT_CONTROL:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR + 2), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item    
        if (g_usAdjustValue == _LINEAR)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, tsOsdLinear, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _CORVED)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, tsOsdCorved, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SETUP_RESET:
        break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
    case _MENU_SETUP_STABILIZER_CONTROL:
        if (g_usAdjustValue == _OFF)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_6, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _ON)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_6, tsOsdON, ucColor, GET_OSD_LANGUAGE());
        break;
#endif
        //---------------------------------------------------------------------------------------------------------------------------------- VGA
#if (_ENABLE_MENU_VGA == _ON)
    case _MENU_VGA_AUTO:
        OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdClearText, ucColor, GET_OSD_LANGUAGE());
        if (g_usAdjustValue == _OFF)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
        else if (g_usAdjustValue == _ON)
            OsdPropPutpString(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _PFONT_PAGE_ITEM_1, tsOsdON, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_VGA_H_POSI:
        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_2, ucColor);
        break;
    case _MENU_VGA_V_POSI:
        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_3, ucColor);
        break;
    case _MENU_VGA_CLOCK:
        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_4, ucColor);
        break;
    case _MENU_VGA_PHASE:
        OsdPropShowNumber(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_ITEM_5, ucColor);
        break;
#endif

    //---------------------------------------------------------------------------------------------------------------------------------- INFO
    case _MENU_INFO_FW_VERSION:
        break;
    case _MENU_INFO_SERIAL_NUM:
        break;

    //----------------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------------------------- SERVICE
    case _MENU_SERVICE_TEMPERATURE:
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_2, ucColor);
        break;
    case _MENU_SERVICE_D0NAME:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SERVICE_D1NAME:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SERVICE_D2NAME:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_6, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SERVICE_D3NAME:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_7), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_7, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), ucColor, GET_OSD_LANGUAGE());
        break;
    //----------------------------------------------------------------------------------------------------------------------------------
    // SERVICE2
    case _MENU_SERVICE_BACKLIGHT_MIN:
        OsdPropShowNumberRightBig(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_SUB_NUM_X - 3), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_1, ucColor);
        break;
    case _MENU_SERVICE_BACKLIGHT_MAX:
        OsdPropShowNumberRightBig(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_SUB_NUM_X - 3), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_2, ucColor);
        break;
    case _MENU_SERVICE_BACKLIGHT_INVERT:
        if (g_usAdjustValue == _ON)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
        else
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SERVICE_BACKLIGHT_FREQ:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item       
        OsdPropShowNumberRightFreq(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_SUB_NUM_X - 3), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_4, ucColor);
        break;
    case _MENU_SERVICE_LOGO:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _ON)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdON, ucColor, GET_OSD_LANGUAGE());
        else
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_5), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_5, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
        break;
#if (_CUSTOMER_TYPE == _CUSTOMER_TECNNIT)
    case _MENU_SERVICE_STABILUX:
        OsdPropShowNumberRightBig(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_SUB_NUM_X - 3), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_6, ucColor);
        break;
#endif
    case _MENU_SERVICE_LOGO_LIST:
        OsdPropShowNumberRightBig(ROW(ROW_OFFSET + _ITEM_6), COL(_MENU_SECTION_1_SUB_NUM_X - 3), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_6, ucColor);
        break;
    case _MENU_SERVICE_DP_OPTION:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item    
        switch (g_usAdjustValue)
        {
        case _MST_OFF:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdClone, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MST_D0:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdMstD0DP2, ucColor, GET_OSD_LANGUAGE());
            break;
        case _MST_D1:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdMstD1DP1, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
#if (_ENABLE_LIGHT_SENSOR == _ON)
    case _MENU_SERVICE_LIGHTSENSOR:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        if (g_usAdjustValue == _ON)
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdON, ucColor, GET_OSD_LANGUAGE());
        else
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2, tsOsdOFF, ucColor, GET_OSD_LANGUAGE());
        break;
#endif
#if (_ENABLE_FAN_CONTROL == _ON)
    case _MENU_SERVICE_FAN_OPTION:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR + 2), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        switch (GET_OSD_FAN_STATUS())
        {
        case _AUTO:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdFanAuto, ucColor, GET_OSD_LANGUAGE());
            break;
        case _ON:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdON, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OFF:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdOFF3, ucColor, GET_OSD_LANGUAGE());
            break;
        }

        break;
    case _MENU_SERVICE_FAN_SPEED:
        OsdPropShowNumberRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_SUB_NUM_X), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_PAGE_ITEM_4, ucColor);
        break;
#endif
    case _MENU_SERVICE_USERASSIGN_UP:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1); // Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1,  OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SERVICE_USERASSIGN_DOWN:
         OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1); // Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_2), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_2,  OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SERVICE_USERASSIGN_LEFT:
         OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1); // Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3,  OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
        break;
    case _MENU_SERVICE_USERASSIGN_RIGHT:
         OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1); // Clear Item
        OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_4), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_4,  OsdDisplayGetUserAssignStringP(g_usAdjustValue), ucColor, GET_OSD_LANGUAGE());
        break;
#if (_ENABLE_MENU_OLED == _ON)
    case _MENU_SERVICE_OLED_OFFRS:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        switch (g_usAdjustValue)
        {
        case _OFFRS_AUTO:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdOLEDAutoRun, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OFFRS_END_RUN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdOLEDEndRun, ucColor, GET_OSD_LANGUAGE());
            break;
        case _OFFRS_NOW_RUN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_1), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_1, tsOsdOLEDNow, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
    case _MENU_SERVICE_OLED_SEQUENCE_TIME:
        OsdFuncClearOsd(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR + 2), _MENU_SECTION_1_SUB_STR_WIDTH, 1);	// Clear Item
        switch (g_usAdjustValue)
        {
			/*
        case _POWER_SAVE_OFF:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSaveOff, ucColor, GET_OSD_LANGUAGE());
            break;
        case _POWER_SAVE_5SEC:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave5Sec, ucColor, GET_OSD_LANGUAGE());
            break;
            */
        case _POWER_SAVE_30SEC:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave30Sec_1, ucColor, GET_OSD_LANGUAGE());
            break;
        case _POWER_SAVE_1MIN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave1Min, ucColor, GET_OSD_LANGUAGE());
            break;
        case _POWER_SAVE_2MIN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave2Min, ucColor, GET_OSD_LANGUAGE());
            break;
        case _POWER_SAVE_5MIN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave5Min, ucColor, GET_OSD_LANGUAGE());
            break;
        case _POWER_SAVE_30MIN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave30Min, ucColor, GET_OSD_LANGUAGE());
            break;
        case _POWER_SAVE_60MIN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave60Min, ucColor, GET_OSD_LANGUAGE());
            break;
        case _POWER_SAVE_120MIN:
            OsdPropPutpStringRight(ROW(ROW_OFFSET + _ITEM_3), COL(_MENU_SECTION_1_NUM_X_STR), WIDTH(_MENU_SECTION_1_SUB_STR_WIDTH), _PFONT_PAGE_ITEM_3, tsOsdPowerSave120Min, ucColor, GET_OSD_LANGUAGE());
            break;
        }
        break;
#endif
    default:
        break;
    }
}


//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch(GET_KEYMESSAGE())
    {
        case _UP_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            if(usValue >= usMax)
            {
                if(bCycle == _ON)
                {
                    return usMin;
                }
                else
                {
                    return usMax;
                }
            }
            else
            {
                usValue++;
            }

            break;
        case _DOWN_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if (usValue <= usMin)
            {
                if(bCycle == _ON)
                {
                    return usMax;
                }
                else
                {
                    return usMin;
                }
            }
            else
            {
                usValue--;
            }
            break;

        default:
            break;
    }

    return usValue;
}

WORD OsdDisplayDetOverRange_Long(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch (GET_KEYMESSAGE())
    {
    case _RIGHT_KEY_MESSAGE:
    case _UP_KEY_MESSAGE:
        if (usValue >= usMax)
        {
            if (bCycle == _ON)
            {
                return usMin;
            }
            else
            {
                return usMax;
            }
        }
        else
        {
            if (GET_KEYREPEATSTART())
            {
                if (usValue > usMax - 30)
                    usValue = usMax;
                else
                    usValue = usValue + 30;
            }
            else
            {
                usValue++;
            }
        }

        break;

    case _LEFT_KEY_MESSAGE:
    case _DOWN_KEY_MESSAGE:
        if (usValue <= usMin)
        {
            if (bCycle == _ON)
            {
                return usMax;
            }
            else
            {
                return usMin;
            }
        }
        else
        {
            if (GET_KEYREPEATSTART())
            {
                if (usValue < 30)
                    usValue = usMin;
                else
                    usValue = usValue - 30;
            }
            else
            {
                usValue--;
            }
        }
        break;

    default:
        break;
    }

    return usValue;
}

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayDetOverRange_Curved(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch (GET_KEYMESSAGE())
    {
        
    case _RIGHT_KEY_MESSAGE:
    case _UP_KEY_MESSAGE:
        if (usValue >= usMax)
        {
            if (bCycle == _ON)
            {
                return usMin;
            }
            else
            {
                return usMax;
            }
        }
        else
        {
            if (GET_KEYREPEATSTART())
            {
                if (usValue > usMax - 30)
                    usValue = usMax;
                else
                    usValue = usValue + 30;
            }
            else
            {
                usValue++;
            }
        }

        break;

    case _LEFT_KEY_MESSAGE:
    case _DOWN_KEY_MESSAGE:
        if (usValue <= usMin)
        {
            if (bCycle == _ON)
            {
                return usMax;
            }
            else
            {
                return usMin;
            }
        }
        else
        {
            if (GET_KEYREPEATSTART())
            {
                if (usValue < (usMin + 30))
                    usValue = usMin;
                else
                    usValue = usValue - 30;
            }
            else
            {
                usValue--;
            }
        }
        break;

    default:
        break;
    }

    return usValue;
}

WORD OsdDisplayDetOverRange_Freq(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch (GET_KEYMESSAGE())
    {
    case _RIGHT_KEY_MESSAGE:
    case _UP_KEY_MESSAGE:
        if (usValue >= usMax)
        {
            if (bCycle == _ON)
            {
                return usMin;
            }
            else
            {
                return usMax;
            }
        }
        else
        {
            if (GET_KEYREPEATSTART())
            {
                if (usValue > usMax - 100)
                    usValue = usMax;
                else if (usValue < 1000)
                {
                    usValue = usValue + 100;
                    if (usValue > 1000)
                        usValue = 1000;
                }
                else
                {
                    usValue = usValue + 1000;
                }
            }
            else
            {
                if (usValue < 1000)
                    usValue = usValue + 10;
                else
                    usValue = usValue + 1000;
            }
        }

        break;

    case _LEFT_KEY_MESSAGE:
    case _DOWN_KEY_MESSAGE:
        if (usValue <= usMin)
        {
            if (bCycle == _ON)
            {
                return usMax;
            }
            else
            {
                return usMin;
            }
        }
        else
        {
            if (GET_KEYREPEATSTART())
            {
                if (usValue < 100)
                    usValue = usMin;
                else if (usValue <= 1000)
                    usValue = usValue - 100;
                else
                {
                    usValue = usValue - 1000;
                }
            }
            else
            {
                if (usValue <= 1000)
                    usValue = usValue - 10;
                else
                    usValue = usValue - 1000;
            }
        }
        break;

    default:
        break;
    }

    return usValue;
}

//--------------------------------------------------
// Description  : Six Color Get One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorGetOneColor(BYTE ucColor)
{
    switch(ucColor)
    {
        case _SIXCOLOR_R:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueR);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationR);
            break;

        case _SIXCOLOR_Y:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueY);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationY);
            break;

        case _SIXCOLOR_G:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueG);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationG);
            break;

        case _SIXCOLOR_C:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueC);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationC);
            break;

        case _SIXCOLOR_B:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueB);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationB);
            break;

        case _SIXCOLOR_M:
            SET_OSD_SIX_COLOR_HUE(g_stSixColorData.ucSixColorHueM);
            SET_OSD_SIX_COLOR_SATURATION(g_stSixColorData.ucSixColorSaturationM);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Six Color Set One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorSetOneColor(BYTE ucColor)
{
    switch(ucColor)
    {
        case _SIXCOLOR_R:
            g_stSixColorData.ucSixColorHueR = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationR = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_Y:
            g_stSixColorData.ucSixColorHueY = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationY = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_G:
            g_stSixColorData.ucSixColorHueG = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationG = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_C:
            g_stSixColorData.ucSixColorHueC = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationC = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_B:
            g_stSixColorData.ucSixColorHueB = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationB = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_M:
            g_stSixColorData.ucSixColorHueM = GET_OSD_SIX_COLOR_HUE();
            g_stSixColorData.ucSixColorSaturationM = GET_OSD_SIX_COLOR_SATURATION();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------

void OsdDispHotKeySourceMenu(void)	
{
	OsdFuncCloseWindow(_OSD_WINDOW_ALL);	//  Menu->Source garbege

    OsdFuncDisableOsd();
    OsdFuncApplyMap(WIDTH(_MENU_SOURCE_WIDTH), HEIGHT(_MENU_SOURCE_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_MENU_SOURCE_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_MENU_SECTION_1_TITLE_WINDOW, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);	
        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(12), WIDTH(52), g_ucOsdWidth, _CP_LIGHTBLUE);	
    }
    else
#endif
    {
		OsdWindowDrawingByFont(_MENU_SECTION_1_TITLE_WINDOW, ROW(0), COL(0), WIDTH(_MENU_SOURCE_WIDTH), HEIGHT(3), _CP_LIGHTBLUE);	
        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(0), WIDTH(_MENU_SOURCE_WIDTH), HEIGHT(g_ucOsdHeight), _CP_DARKGRAY);	
    }

	OsdPropPutpString(ROW(1), COL(3), _PFONT_PAGE_3, tsOsdSource, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());

	OsdSourcePageDraw();

	SetFocus(_MENU_SECTION_SOURCE, _ITEM_4 + GET_OSD_ITEM_INDEX());	
	
    //OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
	//OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 90);	

	switch(GET_OSD_ROTATE_STATUS())	//  OSD Rotate
	{
		case _OSD_ROTATE_DEGREE_0:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 90);
			break;
		case _OSD_ROTATE_DEGREE_90:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_V_POS_MAX-90, 50);
			break;
		case _OSD_ROTATE_DEGREE_180:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_H_POS_MAX-50, _OSD_V_POS_MAX-90);
			break;
		case _OSD_ROTATE_DEGREE_270:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 90, _OSD_H_POS_MAX-50);
			break;
		default:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 90);
			break;
	}
	
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------

void OsdDispReactiveOsdMessage(void)	
{
	if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||		//  Menu -> Power Save Message
	(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
	(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
	{
		//ScalerTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
		//SET_OSD_POWER_SAVING_SHOW_MENU(_FALSE);		//  Reactive Power Saving Message flag
		if(GET_OSD_BURNIN_MODE()!=_ON)
		{
			if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)	
	        {
				OsdDispDisableOsd();
	            OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);	
	            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
				//ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
				
				printf("MenuExit-_OSD_DISP_POWER_SAVING_MSG\n\r");	
				ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
	        }
			else if(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)
			{
				if(SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE)
				{
					OsdDispDisableOsd();
		            OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);	
		            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
					ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
					printf("MenuExit-_OSD_DISP_NOSIGNAL_MSG\n\r");
				}
				else
				{
					OsdDispDisableOsd();
		            OsdDispOsdMessage(_OSD_DISP_NOCABLE_MSG);	
		            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
					ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
					printf("MenuExit-_OSD_DISP_NOCABLE_MSG\n\r");
				}

				
			}
			else if(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)
			{
				OsdDispDisableOsd();
	            OsdDispOsdMessage(_MODE_STATUS_NOSUPPORT);	
	            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
				ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);

				printf("MenuExit-_MODE_STATUS_NOSUPPORT\n\r");
			}
		}
		else
		{
			if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)	
			SysModeSetResetTarget(_MODE_ACTION_RESET_TO_NOSIGNAL);
			
			ScalerDDomainPatternGenEnable(_ENABLE);
	        ScalerDDomainBackgroundEnable(_DISABLE);

			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

			
		}
				
			
	}
	else
	{
		OsdDispDisableOsd();
	}
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyMuteMessage(void)
{
    OsdDispDisableOsd();

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;
    g_ucFontPointer3 = _OSD_PAGE_3_START;

    OsdFuncApplyMap(WIDTH(10), HEIGHT(3), COLOR(_CP_WHITE, _CP_BG));

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(3), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window Modify

    {
        {
            // OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
            // OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdWidth - 12), g_ucOsdHeight, _CP_LIGHTBLUE);
            // OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(_OSD_DIALOG_BOX_WIDTH), HEIGHT(_OSD_DIALOG_BOX_HEIGHT+1), _CP_DARKGRAY);
        }
    }
    // Background window Modify
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
        (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
    OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(1), HEIGHT(12), _CP_DARKGRAY);
    }
    else
#endif
    OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(10), HEIGHT(3), _CP_DARKGRAY);


    if (GET_OSD_VOLUME_MUTE() == _ON)
    {
        OsdPropPutpString(ROW(1), COL(2), _PFONT_PAGE_0, tsOsdMute, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    }
    else
    {
        OsdPropPutpString(ROW(1), COL(2), _PFONT_PAGE_0, tsOsdUnmute, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
    }


    // OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    switch (GET_OSD_ROTATE_STATUS())
    {
    case _OSD_ROTATE_DEGREE_0:
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 100, 0);
        break;
    case _OSD_ROTATE_DEGREE_90:
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_V_POS_MAX - 100, 0);
        break;
    case _OSD_ROTATE_DEGREE_180:
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_H_POS_MAX - 0, _OSD_V_POS_MAX - 100);
        break;
    case _OSD_ROTATE_DEGREE_270:
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 90, _OSD_H_POS_MAX - 0);
        break;
    default:
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 0, 100);
        break;
    }

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

void OsdDispHotKeyOsdMessage(BYTE ucHotKeyItem)			
{
    OsdDispDisableOsd();

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;
	g_ucFontPointer3 = _OSD_PAGE_3_START;	

    OsdFuncApplyMap(WIDTH(_OSD_DIALOG_BOX_WIDTH), HEIGHT(_OSD_DIALOG_BOX_HEIGHT+2), COLOR(_CP_WHITE, _CP_BG));	

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_DIALOG_BOX_HEIGHT+2), _DISABLE, 0, _ENABLE);	
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_MENU_SECTION_1_TITLE_WINDOW, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);	
        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);	
    }
    else
#endif
    {
        {
            //OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
            //OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(12), WIDTH(g_ucOsdWidth - 12), g_ucOsdHeight, _CP_LIGHTBLUE);
            OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(0), WIDTH(_OSD_DIALOG_BOX_WIDTH), HEIGHT(_OSD_DIALOG_BOX_HEIGHT+1), _CP_DARKGRAY);	
        }
    }
	
	OsdWindowDrawingByFont(_MENU_SECTION_1_TITLE_WINDOW, ROW(0), COL(0), WIDTH(_OSD_DIALOG_BOX_WIDTH), HEIGHT(3), _CP_LIGHTBLUE);		

	//------------------------------------------------------------- just test
	//OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_VOLUME);
    //OsdFontPut1BitMainMenuIcon(ROW(3), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
	//OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_MUTE);
    //OsdFontPut1BitMainMenuIcon(ROW(3), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
	//--------------------------------------------------------
	switch(ucHotKeyItem)
	{
        case _MENU_HOTKEY_BRIGHTNESS:
            OsdPropPutpString(ROW(1), COL(10), _PFONT_PAGE_0, tsOsdBrightness, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);
            OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
            SET_OSD_STATE(_MENU_HOTKEY_BRIGHTNESS);
            break;
        case _MENU_HOTKEY_CONTRAST:
            OsdPropPutpString(ROW(1), COL(10), _PFONT_PAGE_0, tsOsdContrast, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);
            OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
            SET_OSD_STATE(_MENU_HOTKEY_CONTRAST);
            break;
        case _MENU_HOTKEY_VOLUME:
            OsdPropPutpString(ROW(1), COL(10), _PFONT_PAGE_0, tsOsdVolume, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OSD_VOLUME_CENTER);
            OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);
            OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
            SET_OSD_STATE(_MENU_HOTKEY_VOLUME);
            break;
        case _MENU_HOTKEY_BACKLIGHT:
            OsdPropPutpString(ROW(1), COL(10), _PFONT_PAGE_0, tsOsdBacklight, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
            if (GET_OSD_BACKLIGHT_CONTROL() == _ON)
            {
                g_usAdjustValue = GET_OSD_BACKLIGHT();
                g_usAdjustValue = UserCommonAdjustRealValueToPercentCurved(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
                OsdPropShowNumberFloat(ROW(4), COL(10), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
            }
            else
            {
                g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
                OsdPropShowNumber(ROW(4), COL(15), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_WHITE, _CP_BG));
            }

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            OsdWindowSlider(ROW(6), COL(2), g_usAdjustValue, _SLIDER_1, _SELECT);

            SET_OSD_STATE(_MENU_HOTKEY_BACKLIGHT);
            break;

		case _MENU_HOTKEY_MUTE:		
			OsdPropPutpString(ROW(1), COL(11), _PFONT_PAGE_0, tsOsdMute, COLOR(_CP_DARKGRAY, _CP_BG), GET_OSD_LANGUAGE());
			if(GET_OSD_VOLUME_MUTE() == _ON)
			{
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_MUTE);
	    		OsdFontPut1BitMainMenuIcon(ROW(4), COL(10), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
			}
			else
			{
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_VOLUME);
	    		OsdFontPut1BitMainMenuIcon(ROW(4), COL(10), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
			}
			SET_OSD_STATE(_MENU_HOTKEY_MUTE);
			break;
		case _MENU_HOTKEY_DISPLAY_MODE:
			SET_OSD_STATE(_MENU_HOTKEY_DISPLAY_MODE);
			break;

			
	}
	
    //OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
	switch(GET_OSD_ROTATE_STATUS())	
	{
		case _OSD_ROTATE_DEGREE_0:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 90);
			break;
		case _OSD_ROTATE_DEGREE_90:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_V_POS_MAX-90, 50);
			break;
		case _OSD_ROTATE_DEGREE_180:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, _OSD_H_POS_MAX-50, _OSD_V_POS_MAX-90);
			break;
		case _OSD_ROTATE_DEGREE_270:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 90, _OSD_H_POS_MAX-50);
			break;
		default:
			OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 90);
			break;
	}
	
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage)		
{
    OsdDispDisableOsd();

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;
	g_ucFontPointer3 = _OSD_PAGE_3_START;	

#if (_ENABLE_MENU_OLED == _ON)
	if ((enumMessage == _OSD_DISP_JB_MSG) || (enumMessage == _OSD_DISP_OFF_RS_MSG) || (enumMessage == _OSD_DISP_OFF_RS_PWR_SUPPLY_MSG) || (enumMessage == _OSD_DISP_OFF_RS_30SEC_MSG))
		OsdFuncApplyMap(WIDTH(24), HEIGHT(8), COLOR(_CP_BG, _CP_BG));
	else
#endif
	    OsdFuncApplyMap(WIDTH(_OSD_DIALOG_BOX_WIDTH), HEIGHT(_OSD_DIALOG_BOX_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_DIALOG_BOX_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_MENU_SECTION_1_TITLE_WINDOW, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);	
        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        if(enumMessage == _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG)
        {
            OsdWindowDrawingByFont(_MENU_SECTION_1_TITLE_WINDOW, ROW(0), COL(0), WIDTH(g_ucOsdWidth), g_ucOsdHeight, _CP_LIGHTBLUE);	
        }
        else
        {
			if(enumMessage != _OSD_DISP_INPUT_SIGNAL_MSG)
            	OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(0+2), WIDTH(_OSD_DIALOG_BOX_WIDTH-6), HEIGHT(_OSD_DIALOG_BOX_HEIGHT-2), _CP_DARKGRAY);	
			else
				OsdWindowDrawingByFont(_OSD_WINDOW_4_1 , ROW(0), COL(3+2), WIDTH(_OSD_INFO_BOX_WIDTH), HEIGHT(_OSD_INFO_BOX_HEIGHT), _CP_DARKGRAY);
        }

		
    }
		
    //==== Show page item =======
    switch(enumMessage)
    {
        
		case _OSD_DISP_INPUT_SIGNAL_MSG:
			/*
			OsdFuncClearOsd(ROW(3), COL(0), _OSD_DIALOG_BOX_WIDTH, _OSD_DIALOG_BOX_HEIGHT-3);	// Clear Item	
			OsdPropPutpStringCenter(ROW(4), COL(3), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(SysSourceGetInputPort()), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);	
			OsdPropPutpStringCenter(ROW(5 + 1), COL(3), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetResolutionStringP(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
			*/
			OsdPropPutpStringCenter(ROW(3), COL(3+2), WIDTH(20), _PFONT_PAGE_INFORMATION, tsOsdClearLongText, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
			OsdPropPutpStringCenter(ROW(2), COL(3+2), WIDTH(20), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortStringP(SysSourceGetInputPort()), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
			OsdPropPutpStringCenter(ROW(3), COL(3+2), WIDTH(20), _PFONT_PAGE_INFORMATION, OsdDisplayGetResolutionStringP(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
			break;

		case _OSD_DISP_NOSIGNAL_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SIGNAL_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(7-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SIGNAL_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(7 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
			OsdPropPutpStringCenter(ROW(2), COL(3-1), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(SysSourceGetInputPort()), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);	
            break;

        case _OSD_DISP_NOCABLE_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_CABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(7-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_CABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(7 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
			OsdPropPutpStringCenter(ROW(2), COL(3-1), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(SysSourceGetInputPort()), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);	
            break;

        case _OSD_DISP_NOSUPPORT_MSG:
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SUPPORT_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(7-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SUPPORT_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(7 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
			OsdPropPutpStringCenter(ROW(2), COL(3-1), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(SysSourceGetInputPort()), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);	
            break;
			
        case _OSD_DISP_FAIL_SAFE_MODE_MSG:
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_NO_SUPPORT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_AUTO_CONFIG_MSG:
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_ADJUST_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_ADJUST_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_ADJUST_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6 + 6-1), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_WHITE, _CP_BG);
            break;

        case _OSD_DISP_AUTO_COLOR_MSG:
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_COLOR_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_COLOR_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_COLOR_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6 + 6-1), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_WHITE, _CP_BG);
            break;

        case _OSD_DISP_POWER_SAVING_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_POWER_SAVING_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_POWER_SAVING_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_POWER_SAVING_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6 + 6-1), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_WHITE, _CP_BG);
            break;
        case _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG:
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_TRUN_OFF_PANEL_UNI_TEXT0);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(3-1), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_TRUN_OFF_PANEL_UNI_TEXT1);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(3 + 6-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            
            break;
#if(_FREEZE_SUPPORT == _ON)
        case _OSD_DISP_DISABLE_FREEZE_MSG:
			OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_FREEZE_DISABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_FREEZE_DISABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_FREEZE_DISABLE_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6 + 6-1), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_WHITE, _CP_BG);
            break;
#endif
#if(_DP_MST_SUPPORT == _ON)
        case _OSD_DISP_MST_WARNING_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_MST_WARNING_MSG_0);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5-1), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_MST_WARNING_MSG_1);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6-1), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_MST_WARNING_MSG_2);
            OsdFontPut1BitMainMenuIcon(ROW(1), COL(5 + 6 + 6-1), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_WHITE, _CP_BG);
            break;
#endif
#if (_ENABLE_MENU_OLED == _ON)
			case _OSD_DISP_OFF_RS_MSG:
				bEnable_OFF_RS_Message = _TRUE;
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
				if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
					(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
				{
				   // OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
				}
				else
#endif
				{
					//OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(24), g_ucOsdHeight, _CP_BG);
				}
				// title
				//OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_OFFRS);
				//OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
				// icon
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISP_OFFRS_TEXT_1);
				OsdFontPut1BitMainMenuIcon(ROW(2), COL(6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_DISP_OFFRS_TEXT_2);
				OsdFontPut1BitMainMenuIcon(ROW(2), COL(6 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
				break;
		
			case _OSD_DISP_JB_MSG:
				bEnable_OFF_RS_Message = _TRUE;
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
				if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
					(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
				{
				   // OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
				}
				else
#endif
				{
					//OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(24), g_ucOsdHeight, _CP_BG);
				}
				// title
				//OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_JBCOMP);
				//OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
				// icon
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISP_JB_TEXT_1);
				OsdFontPut1BitMainMenuIcon(ROW(2), COL(6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_DISP_JB_TEXT_2);
				OsdFontPut1BitMainMenuIcon(ROW(2), COL(6 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
				break;
			case _OSD_DISP_OFF_RS_PWR_SUPPLY_MSG:
				bEnable_OFF_RS_Message = _TRUE;
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
				if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
					(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
				{
				   // OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
				}
				else
#endif
				{
					//OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(24), g_ucOsdHeight, _CP_BG);
				}
				// title
				//OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_OFFRS);
				//OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
				// icon
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISP_OFFRS_PWR_SUPPLY_TEXT_1);
				OsdFontPut1BitMainMenuIcon(ROW(2), COL(6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_DISP_OFFRS_PWR_SUPPLY_TEXT_2);
				OsdFontPut1BitMainMenuIcon(ROW(2), COL(6 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
				// OsdPropPutStringCenter(ROW(3), COL(12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_5MIN_AFTER, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
				// OsdPropPutStringCenter(ROW(4), COL(12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_START_OFFRS, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
				break;
			case _OSD_DISP_OFF_RS_30SEC_MSG:
				bEnable_OFF_RS_Message = _TRUE;
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
				if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
					(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
				{
				   // OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
				}
				else
#endif
				{
					//OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
					OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(24), g_ucOsdHeight, _CP_BG);
				}
				// title
				//OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_OFFRS);
				//OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
				// OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_END_RUN, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
				//	icon
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISP_OFFRS_SEQUENCE_TIME_TEXT_1);
				OsdFontPut1BitMainMenuIcon(ROW(1), COL(6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_WHITE, _CP_BG);
				OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_DISP_OFFRS_SEQUENCE_TIME_TEXT_2);
				OsdFontPut1BitMainMenuIcon(ROW(1), COL(6 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_WHITE, _CP_BG);
		
				//OsdDisplayGetSequenceTimeP();
				OsdPropPutpStringCenter(ROW(6), COL(6), WIDTH(12), _PFONT_PAGE_INFORMATION, OsdDisplayGetSequenceTimeP(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
				// OsdPropPutStringCenter(ROW(3), COL(12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_5MIN_AFTER, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
				// OsdPropPutStringCenter(ROW(4), COL(12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_START_OFFRS, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
				OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, ScalerTimerGetTimerCounter() % 101, ((ScalerTimerGetTimerCounter() >> 3) ^ (ScalerTimerGetTimerCounter() * 31)) % 101);
				ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
				OsdFuncEnableOsd();
				return;
#endif

        case _OSD_DISP_INPUTSOURCE_CHANGE_MSG:
        OsdWindowDrawingByFont(_OSD_WINDOW_4_1, ROW( 0), COL( 3), WIDTH(_OSD_INFO_BOX_WIDTH), HEIGHT(_OSD_INFO_BOX_HEIGHT), _CP_DARKGRAY);

		switch (GET_OSD_INPUT_PORT_OSD_ITEM())
		{
            case _OSD_INPUT_D0:
                OsdPropPutpStringCenter(ROW(2), COL(3), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D0_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                break;
            case _OSD_INPUT_D1:
                OsdPropPutpStringCenter(ROW(2), COL(3), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D1_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                break;
            case _OSD_INPUT_D2:
                OsdPropPutpStringCenter(ROW(2), COL(3), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D2_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                break;
            case _OSD_INPUT_D3:
                OsdPropPutpStringCenter(ROW(2), COL(3), WIDTH(20), _PFONT_PAGE_0, OsdDisplayGetSourcePortStringP(_D3_INPUT_PORT), COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                break;

            default:
                OsdPropPutpStringCenter(ROW(2), COL(3), WIDTH(20), _PFONT_PAGE_0, tsOsdSourceAuto, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                break;
		}
		//OsdPropPutStringCenter(ROW(3), COL(3), WIDTH(20), _PFONT_PAGE_0, _STRING_RESOLUTION, 0, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		//OsdPropPutStringCenter(ROW(4), COL(17), WIDTH(5), _PFONT_PAGE_0, _STRING_MAX_FREQUENCY, 0, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 100, 0);
        //ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        OsdFuncEnableOsd();
        return;
		break;
        default:
            break;
    }

	if(enumMessage != _OSD_DISP_INPUT_SIGNAL_MSG)
		OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
	else
	    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 100, 0);
	
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

	//SET_OSD_STATE(_MENU_DIALOG_MESSAGE);	
	
    OsdFuncEnableOsd();
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispAutoConfigProc(void)
{
    OsdDispOsdMessage(_OSD_DISP_AUTO_CONFIG_MSG);
    UserCommonAutoConfig();
    OsdDispDisableOsd();
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayAutoBalanceProc(void)
{
    OsdDispDisableOsd();
    OsdDispOsdMessage(_OSD_DISP_AUTO_COLOR_MSG);

    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(GET_OSD_COLOR_FORMAT() == _COLOR_SPACE_RGB)
        {
            // Perform auto-color for RGB
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                // Calculate YPbPr gain/offset using formula
                g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                // Restore RGB gain/offset
                ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        else
        {
            // Perform auto-color for YPbPr
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_YPBPR) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#endif
    }

    OsdDispDisableOsd();
    // SET_KEYMESSAGE(_HOLD_KEY_MESSAGE);
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispClearSliderAndNumber(void)
{
    OsdWindowSliderDisable();
    OsdFuncClearOsd(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_ucOsdWidth, 1);
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Osd Display Reset Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispResetDpCapabilitySwitch(void)
{
    // Set Aux Diff mode & Resistance Setting
    SET_DP_AUX_DIFF_MODE();

    SET_DP_AUX_ADJR_SETTING(UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING));

    UserCommonInterfaceDpAuxSet();

    // Switch All DP Port Dp Version
    UserCommonInterfaceDPSwitchAllPortDpVersion();

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    // Switch All DP Port Dp Edid
    UserCommonInterfaceDPSwitchAllPortEdid();
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    // Switch All DP Port Dp Lane Count Capability
    UserCommonInterfaceTypeCU3ModeAllPortCapabilitySwitch();
#endif

#if(_DP_MST_SUPPORT == _ON)
    // Switch DP Mst Capability
    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
#endif
}
#endif



void OsdDispTransferId(BYTE AdjValue)	
{
	if(AdjValue == 0)		// All Set
		OsdPropPutpString(ROW(6), COL(17), _PFONT_PAGE_ITEM_1, tsOsdAll, COLOR(_CP_YELLOW, _CP_BG), GET_OSD_LANGUAGE());	
	//else if(AdjValue == 101)// Off
	//	OsdPropPutpString(ROW(6), COL(17), _PFONT_PAGE_ITEM_1, tsOsdOFF, COLOR(_CP_YELLOW, _CP_BG), GET_OSD_LANGUAGE());
	else					// 1~100
		OsdPropShowNumber(ROW(6), COL(20), AdjValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, COLOR(_CP_YELLOW, _CP_BG));
}

//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowInformation(void)	
{

#if (_DYNAMIC_OSD_WINDOW == _ON)
	OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(ROW_OFFSET + 6 + 2), _CP_DARKGRAY);
#endif
	OsdSubMenuItemText(_MENU_INFO, _MENU_INFO_MODEL, COLOR(_CP_WHITE, _CP_BG));
	OsdPropPutpStringRight(ROW(_ITEM_1), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, OsdGetBoardModel(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	OsdSubMenuItemText(_MENU_INFO, _MENU_INFO_INPUT, COLOR(_CP_WHITE, _CP_BG));
	OsdPropPutpStringRight(ROW(_ITEM_2), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortStringP(SysSourceGetInputPort()), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	OsdSubMenuItemText(_MENU_INFO, _MENU_INFO_FORAMT, COLOR(_CP_WHITE, _CP_BG));
	OsdPropPutpStringRight(ROW(_ITEM_3), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, OsdDisplayGetResolutionStringP(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	OsdSubMenuItemText(_MENU_INFO, _MENU_INFO_COLOR_TEMP, COLOR(_CP_WHITE, _CP_BG));
	{
#if(_MEDICAL_SURGICAL == _ON)
        {
            switch (GET_OSD_PCM_STATUS())
            {
            case _PCM_OSD_BT709:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdBT709, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _PCM_OSD_DCI_P3:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdDCI_P3, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _PCM_OSD_BT2020:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdBT2020, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _PCM_OSD_NATIVE:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdGammaNative, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            default:
                break;
            }
        }
#else
        {
            switch (GET_COLOR_TEMP_TYPE())
            {
            case _CT_D56:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdTempD56, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _CT_D65:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdTempD65, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _CT_D93:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdTempD93, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _CT_USER:
                OsdPropPutpStringRight(ROW(_ITEM_4), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, tsOsdTempUser, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            default:
                break;
            }
        }
#endif
	}
	OsdSubMenuItemText(_MENU_INFO, _MENU_INFO_RANGE, COLOR(_CP_WHITE, _CP_BG));
	OsdPropPutpStringRight(ROW(_ITEM_5), COL(_MENU_SECTION_INFO_X), WIDTH(_MENU_SECTION_0_SUB_STR_WIDTH), _PFONT_PAGE_INFORMATION, OsdDisplayGetRangeStringP(), COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
	
	OsdSubMenuItemText(_MENU_INFO, _MENU_INFO_FW_VERSION, COLOR(_CP_WHITE, _CP_BG));


}


#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdRotateSwitch(void)	
{
//	BYTE hPosi,vPosi;
//			
//	OsdFuncCloseWindow(_OSD_WINDOW_ALL);
//    OsdFuncDisableOsd();

//	OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

////20140304 Abel
//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
//#endif

//    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
//    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

//    // Adjust Color Palette
//    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

//    // Load Font & Icon
//    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

//    OsdFontVLCLoadFont(_FONT1_GLOBAL);
//    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

//    // Background window
//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
//    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
//       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
//    {
//        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
//        OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
//    }
//    else
//#endif
//    {
//        OsdWindowDrawingByFont(_MENU_SECTION_0_WINDOW, ROW(0), COL(_MENU_SECTION_0_WIN_X), WIDTH(_MENU_SECTION_0_WIDTH), HEIGHT(g_ucOsdHeight), _CP_DARKGRAY);	
//		//OsdWindowDrawingByFont(_MENU_SECTION_1_WINDOW, ROW(0), COL(_MENU_SECTION_1_WIN_X), WIDTH(_MENU_SECTION_1_WIDTH), HEIGHT(g_ucOsdHeight), _CP_DARKGRAY);	
//		//OsdWindowDrawingByFont(_MENU_SECTION_2_WINDOW, ROW(0), COL(_MENU_SECTION_2_WIN_X), WIDTH(_MENU_SECTION_2_WIDTH), HEIGHT(g_ucOsdHeight), _CP_DARKGRAY);
// 
//    }


//    // Realtek Mark
//    //OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));

//	OsdMainMenuPageDraw();	

//	SetFocus(_MENU_SECTION_0, ROW_OFFSET+_ITEM_4);	

//	OsdSubMenuPageDraw(_MENU_OSD_SETTING);
//	SET_OSD_STATE(_MENU_OSD_ROTATE);
//	SetFocus(_MENU_SECTION_1, ROW_OFFSET+_ITEM_5);	

//	//OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
//	
//	switch(GET_OSD_ROTATE_STATUS())	
//	{
//		case _OSD_ROTATE_DEGREE_0:
//			hPosi = GET_OSD_HPOS();
//			vPosi = GET_OSD_VPOS();
//			break;
//		case _OSD_ROTATE_DEGREE_90:
//			hPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
//			vPosi = GET_OSD_HPOS();
//			break;
//		case _OSD_ROTATE_DEGREE_180:
//			hPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
//			vPosi = _OSD_V_POS_MAX - GET_OSD_VPOS();
//			break;
//		case _OSD_ROTATE_DEGREE_270:
//			hPosi = GET_OSD_VPOS();
//			vPosi = _OSD_H_POS_MAX - GET_OSD_HPOS();
//			break;
//		default:
//			hPosi = GET_OSD_HPOS();
//			vPosi = GET_OSD_VPOS();
//			break;
//				
//	}
//	OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, hPosi, vPosi);

//    // Osd Enable
//    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
//    OsdFuncEnableOsd();
}
#endif

#if(_ENABLE_REVERSE_SCAN == _ON)	
void OsdDispOsdReverseScanSwitch(void)	
{
/*	
	if(GET_OSD_REVERSE_SCAN()==_ON)	
	{
		PCB_PANEL_REVERSE(_PANEL_REVERSE_ON);	//  Panel Reverse Scan
	#if(_ENABLE_REVERSE_SCAN_BOE == _ON)		
		SET_OSD_DISP_ROTATE(_DISP_ROTATE_VER_MIRROR);	// V-Flip ( BOE Panel )
		SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
	#else
		SET_OSD_DISP_ROTATE(_DISP_ROTATE_180);			// HV-Flip( LG Panel  )
		SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_180);
	#endif
	}
	else
	{
		PCB_PANEL_REVERSE(_PANEL_REVERSE_OFF);
		SET_OSD_DISP_ROTATE(_DISP_ROTATE_0);			// NO-Flip
		SET_OSD_ROTATE_STATUS(_OSD_ROTATE_DEGREE_0);
	}

	OsdDispOsdRotateSwitch();
	SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
*/
	if(GET_OSD_REVERSE_SCAN()==_ON)
	{
		//PCB_PANEL_REVERSE(_PANEL_REVERSE_ON); 
	}
	else
	{
		//PCB_PANEL_REVERSE(_PANEL_REVERSE_OFF); 
	}

}
#endif

#if (_ENABLE_MENU_OLED == _ON)

void OsdDispHotKeyOffRSMenu()
{
    BYTE uctemp = 0;

    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    OsdFuncDisableOsd();
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncApplyMap(WIDTH(36), HEIGHT(8), COLOR(_CP_WHITE, _CP_BG));

#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if ((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
        (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdHeight, _CP_LIGHTBLUE);
    }

    // icon
    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_OFFRS);

    OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
    // string
    //			OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_END_RUN, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

    // uctemp = 1;

    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_DISP_POWEROFF_OFFRS_TEXT_1);
    OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_DISP_POWEROFF_OFFRS_TEXT_2);
    OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
    /*
                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_YES);
                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);

                OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO);
                OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
    */
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

void uint_to_str(DWORD value, BYTE *str)
{
    BYTE temp[10];
    BYTE i = 0, j = 0;

    if (value == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (value > 0)
    {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    for (j = 0; j < i; ++j)
    {
        str[j] = temp[i - j - 1];
    }
    str[i] = '\0';
}

void uint_to_str2digit(DWORD value, BYTE *str)
{
    str[0] = (value / 10) + '0';
    str[1] = (value % 10) + '0';
    str[2] = '\0';
}

BYTE *OsdDisplayGetSequenceTimeP(void)
{
    static BYTE xdata tTemp[13];  
    BYTE temp[10];
    BYTE i;

    DWORD minutes = g_ulRemainingTimeMs / 60000;
    DWORD seconds = (g_ulRemainingTimeMs % 60000) / 1000;

    uint_to_str(minutes, temp);
    strcpy(tTemp, temp);
    strcat(tTemp, ":");
    uint_to_str2digit(seconds, temp);  
    strcat(tTemp, temp);

    for (i = 0; i < 12; i++)
    {
        if ((tTemp[i] >= '0') && (tTemp[i] <= '9'))
            tTemp[i] = (tTemp[i] - '0' + _0_);
        else if (tTemp[i] == ':')
            tTemp[i] = _COLON_;
        else
            tTemp[i] = _FONT_SPACE_1;
    }
    tTemp[12] = _END_;

    return tTemp;
}
#endif

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
