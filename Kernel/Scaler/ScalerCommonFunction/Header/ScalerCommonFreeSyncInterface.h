/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonFreeSyncInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
typedef struct
{
    BYTE ucColorSapce;
    WORD usHtotal;
    WORD usHtotalMargin;
} StructFreeSyncSourceInfo;

typedef struct
{
    WORD usIHwidth;
    WORD usIVheight;
    WORD usIHtotal;
    WORD usPixelClk;
    WORD usIVfreq;
} StructDrrFreeSyncTimingInfo;

//--------------------------------------------------
// Enum for FreeSync IVF Max from Table Search
//--------------------------------------------------
typedef enum
{
    _TABLE_SEARCHING_WITH_IVF_MAX = 0x00,
    _TABLE_SEARCHING_WITHOUT_IVF_MAX,
} EnumGetIVFFromTableSearch;

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Enum for DP FreeSync IVF Max
//--------------------------------------------------
typedef enum
{
    _DP_FREESYNC_WITH_IVF_MAX = 0x00,
    _DP_FREESYNC_WITHOUT_IVF_MAX,
} EnumDrrFreeSyncDpGetIVF;
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Enum for HDMI FreeSync IVF Max
//--------------------------------------------------
typedef enum
{
    _HDMI_FREESYNC_WITH_IVF_MAX = 0x00,
    _HDMI_FREESYNC_WITHOUT_IVF_MAX,
} EnumDrrFreeSyncHdmiGetIVF;
#endif
#endif


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
extern WORD ScalerFreeSyncGetFreeSyncInfo(EnumSourceSearchPort enumSearchPort, EnumAmdSpdInfoContent enumContent);
extern void ScalerFreeSyncSPDInfoReceive(EnumSourceSearchPort enumSearchPort);
extern bit ScalerFreeSyncVfreqMaxInfoEnable(EnumSourceSearchPort enumInputPort, BYTE ucPortType);
extern void ScalerFreeSyncGetSourceInfo(EnumSourceSearchPort enumSearchPort, BYTE ucPortType, StructFreeSyncSourceInfo *pstSourceInfo);
extern EnumGetIVFFromTableSearch ScalerFreeSyncEdidAnalysisGetVfreqMax(BYTE *pucReadArray, WORD usPixelClk, const StructFreeSyncSourceInfo *pstSourceInfo, WORD *pusVfreqMax);

#if(_TRANSLATOR_SUPPORT == _OFF)
extern void ScalerFreeSyncSupportSwitch(EnumSourceSearchPort enumSourcePort, EnumFreeSyncSupport enumSupport);
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) &&\
    (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern EnumFreeSyncSupport ScalerFreeSyncHDMIGetFreeSyncSupport_EXINT1(EnumSourceSearchPort enumSourcePort);
#endif
#endif
#endif

#endif

