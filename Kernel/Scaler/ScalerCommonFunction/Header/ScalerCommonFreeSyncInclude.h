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
// ID Code      : ScalerCommonFreeSyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
#define _EDID_ANALYSIS_CLK_MARGIN                        (1)
#define _EDID_ANALYSIS_HTOTAL_MARGIN                     (2)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Struct for FREESYNC Ver from Edid
//--------------------------------------------------
typedef struct
{
    BYTE b3D0FreeSyncVerbyEdid : 3;
    BYTE b3D1FreeSyncVerbyEdid : 3;
    BYTE b3D2FreeSyncVerbyEdid : 3;
    BYTE b3D3FreeSyncVerbyEdid : 3;
    BYTE b3D4FreeSyncVerbyEdid : 3;
    BYTE b3D5FreeSyncVerbyEdid : 3;
} StructDrrFreesyncVerByEdid;

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

typedef struct
{
    WORD usHwidth;
    WORD usVheight;
    WORD usHblank;
    WORD usPixelClk;
    WORD usHtotal;
    WORD usVtotal;
} StructFreeSyncEdidInfo;

typedef struct
{
    WORD usRefHwidth;
    WORD usRefVheight;
    WORD usRefHblankHBound;
    WORD usRefHblankLBound;
    WORD usPixelClkHBound;
    WORD usPixelClkLBound;
} StructFreeSyncEdidRefInfo;

//--------------------------------------------------
// Enum for FreeSync IVF Max from Table Search
//--------------------------------------------------
typedef enum
{
    _TABLE_SEARCHING_WITH_IVF_MAX = 0x00,
    _TABLE_SEARCHING_WITHOUT_IVF_MAX,
} EnumGetIVFFromTableSearch;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
extern WORD ScalerFreeSyncGetFreeSyncInfo(EnumSourceSearchPort enumSearchPort, EnumAmdSpdInfoContent enumContent);

#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
extern WORD ScalerFreeSyncDpGetHSPeriod(EnumSourceSearchPort enumSourceSearchPort);
extern WORD ScalerFreeSyncDpGetHSW(EnumSourceSearchPort enumSourceSearchPort);
extern WORD ScalerFreeSyncDpGetVFreq(EnumSourceSearchPort enumSourceSearchPort);
extern WORD ScalerFreeSyncDpGetVSPeriod(EnumSourceSearchPort enumSourceSearchPort);

#if(_D0_DP_EXIST == _ON)
extern WORD ScalerFreeSyncDpRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern WORD ScalerFreeSyncDpRx0GetBStoHSDelay(WORD usDpHtotal);
extern void ScalerFreeSyncDpRx0GetSPDVfreqMaxMin(void);
#endif

#if(_D1_DP_EXIST == _ON)
extern WORD ScalerFreeSyncDpRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern WORD ScalerFreeSyncDpRx1GetBStoHSDelay(WORD usDpHtotal);
extern void ScalerFreeSyncDpRx1GetSPDVfreqMaxMin(void);
#endif
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_MAC_PAGE2_USE == _ON)
extern WORD ScalerFreeSyncHDMIRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE71_USE == _ON)
extern WORD ScalerFreeSyncHDMIRx2GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, bit bD1Combo);
#endif

#if(_HDMI_MAC_PAGE72_USE == _ON)
extern WORD ScalerFreeSyncHDMIRx3GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE73_USE == _ON)
extern WORD ScalerFreeSyncHDMIRx4GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE74_USE == _ON)
extern WORD ScalerFreeSyncHDMIRx5GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)
#endif // End of #if(_HDMI_SUPPORT == _ON)

#endif
