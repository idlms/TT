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
// ID Code      : ScalerSyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
extern BYTE code tVIC_VFREQ_TABLE[];
extern WORD code tVIC_HACTIVE_TABLE[];
extern WORD code tVIC_HBLANK_TABLE[];
extern WORD code tVIC_VACTIVE_TABLE[];
extern WORD code tVIC_PIXEL_RATE_TABLE[];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_FREESYNC_SUPPORT == _ON) || (_EMBEDDED_EDID_SUPPORT == _ON))
extern void ScalerSyncGetCtaExtDbAddress(WORD *pusCtaDataBlockAddr, BYTE *pucDdcRamAddr);
extern void ScalerSyncGetDidExtDbAddress(WORD *pusDidDataBlockAddr, BYTE *pucDdcRamAddr);
#endif

#if(_DP_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_ALL)
extern void ScalerSyncDpMeasureCountInitial(void);
#endif
#endif

#if(_ADC_SUPPORT == _ON)
extern void ScalerSyncAdcApllPowerDown(void);
extern void ScalerSyncAdcPowerProc(EnumPowerAction enumPowerAction);
#endif

#if(_DDR_BURN_IN_TEST == _ON)
extern void ScalerSyncDDRBurnInCRCTest(void);
#endif
