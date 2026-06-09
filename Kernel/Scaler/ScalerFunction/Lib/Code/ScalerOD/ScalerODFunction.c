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
// ID Code      : ScalerODFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerODLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// OD parameter default value
#define _OD_PRE_SRC_RES_DEFAULT             _OD_PRE_SRC_RES_8_BIT
#define _OD_CUR_SRC_RES_DEFAULT             _OD_CUR_SRC_RES_8_BIT
#define _OD_CMP_METHOD_DEFAULT              _OD_CMP_METHOD_444_TO_422
#define _OD_CMP_MODE_DEFAULT                _OD_CMP_MODE_AVG
#define _OD_DECMP_MODE_DEFAULT              _OD_DECMP_MODE_INTERP

#define GET_OD_USE_PARAM()                  ((GET_OD_USE_BIT() == _OD_SUPERPIXEL1X2_75BIT_BIT_NUM) ? _OD_PARAM_7_5_BPP :\
                                             ((GET_OD_USE_BIT() == _OD_SUPERPIXEL1X4_60BIT_BIT_NUM) ? _OD_PARAM_6_0_BPP : _OD_PARAM_OFF))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _OD_PARAM_OFF,
    _OD_PARAM_6_0_BPP,
    _OD_PARAM_7_5_BPP,
} EnumOdParamIndex;

typedef enum
{
    _OD_PRE_SRC_RES_8_BIT = 0x00,
    _OD_PRE_SRC_RES_6_BIT = _BIT0,
    _OD_PRE_SRC_RES_5_BIT = _BIT1,
    _OD_PRE_SRC_RES_4_BIT = (_BIT1 | _BIT0),
} EnumOdPreSrcRes;

typedef enum
{
    _OD_CUR_SRC_RES_8_BIT = 0x00,
    _OD_CUR_SRC_RES_6_BIT = _BIT6,
    _OD_CUR_SRC_RES_5_BIT = _BIT7,
    _OD_CUR_SRC_RES_4_BIT = (_BIT7 | _BIT6),
} EnumOdCurSrcRes;

typedef enum
{
    _OD_CMP_METHOD_444_TO_422 = 0x00,
    _OD_CMP_METHOD_444_TO_411 = _BIT1,
    _OD_CMP_METHOD_SP_1X2 = _BIT2,
    _OD_CMP_METHOD_SP_1X3 = (_BIT2 | _BIT1),
    _OD_CMP_METHOD_SP_1X4 = _BIT3,
} EnumOdCmpMethod;

typedef enum
{
    _OD_CMP_MODE_AVG = 0x00,
    _OD_CMP_MODE_DROP = _BIT6,
} EnumOdCmpMode;

typedef enum
{
    _OD_DECMP_MODE_INTERP = 0x00,
    _OD_DECMP_MODE_DUP = (_BIT6 | _BIT2),
} EnumOdDecmpMode;

typedef enum
{
    _OD_EST_RANGE_BYPASS = 0x00,
    _OD_EST_RANGE_8 = _BIT4,
    _OD_EST_RANGE_16 = _BIT5,
    _OD_EST_RANGE_32 = (_BIT5 | _BIT4),
} EnumOdEstRange;

typedef struct
{
    BYTE ucOdBit10x;
    EnumOdCmpMethod enumCmpMethod;
    EnumOdPreSrcRes enumPreSrcRes;
    EnumOdCurSrcRes enumCurSrcRes;
    EnumOdCmpMode enumCmpMode;
    EnumOdDecmpMode enumDecmpMode;
    BYTE ucNRThreshold;
    BYTE ucLvlEstValue;
} StructOdParam;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructOdParam code tOdCmpParam[] =
{
    // OD_BIT_10X   CMP_METHOD    PRE_SOURCE_RES           CUR_SOURCE_RES           CMP_MODE              DECMP_MODE          NR_TH  EST_VALUE
    // |                |         |                        |                        |                     |                       |  |
    { 0U, _OD_CMP_METHOD_DEFAULT, _OD_PRE_SRC_RES_DEFAULT, _OD_CUR_SRC_RES_DEFAULT, _OD_CMP_MODE_DEFAULT, _OD_DECMP_MODE_DEFAULT, 0, 0}, // _OD_PARAM_OFF
    {60U, _OD_CMP_METHOD_SP_1X4,  _OD_PRE_SRC_RES_8_BIT,   _OD_CUR_SRC_RES_8_BIT,   _OD_CMP_MODE_AVG,     _OD_DECMP_MODE_DUP,     2, 2}, // _OD_PARAM_6_0_BPP
    {75U, _OD_CMP_METHOD_SP_1X2,  _OD_PRE_SRC_RES_5_BIT,   _OD_CUR_SRC_RES_5_BIT,   _OD_CMP_MODE_AVG,     _OD_DECMP_MODE_DUP,     4, 4}, // _OD_PARAM_7_5_BPP
};

StructOdParam code tOdCmpParam_6_0_BitImproved[] =
{
    // OD_BIT_10X   CMP_METHOD    PRE_SOURCE_RES           CUR_SOURCE_RES           CMP_MODE              DECMP_MODE          NR_TH  EST_VALUE
    // |                |         |                        |                        |                     |                       |  |
    { 0U, _OD_CMP_METHOD_DEFAULT, _OD_PRE_SRC_RES_DEFAULT, _OD_CUR_SRC_RES_DEFAULT, _OD_CMP_MODE_DEFAULT, _OD_DECMP_MODE_DEFAULT, 0, 0}, // _OD_PARAM_OFF
    {60U, _OD_CMP_METHOD_SP_1X2,  _OD_PRE_SRC_RES_4_BIT,   _OD_CUR_SRC_RES_5_BIT,   _OD_CMP_MODE_AVG,     _OD_DECMP_MODE_INTERP,  5, 5}, // _OD_PARAM_6_0_BPP
    {75U, _OD_CMP_METHOD_SP_1X2,  _OD_PRE_SRC_RES_5_BIT,   _OD_CUR_SRC_RES_5_BIT,   _OD_CMP_MODE_AVG,     _OD_DECMP_MODE_DUP,     4, 4}, // _OD_PARAM_7_5_BPP
};

StructOdParam * code tOdCmpParamList[] =
{
    tOdCmpParam, // _OD_CMP_PARAM_MODE_DEFAULT
    tOdCmpParam_6_0_BitImproved, // _OD_CMP_PARAM_MODE_6_0_BIT_IMPROVE
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucMemoryODUseBit;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerODCompressionSetting(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : OD compression, level estimation, noise reduction setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODCompressionSetting(void)
{
    StructOdParam stOdParam;
    stOdParam = tOdCmpParamList[ScalerODGetCmpParamMode()][GET_OD_USE_PARAM()];

    // Enable level estimation, delta gain. Set previous frame source pixel resolution
    ScalerSetByte(P3_A1_LS_CTRL0, (_BIT5 | _BIT3 | stOdParam.enumPreSrcRes));

    // Current path: enable compression, set compression mode/method
    ScalerSetByte(P3_B0_LS_FRAME0, (stOdParam.enumCmpMode | _BIT4 | stOdParam.enumCmpMethod));

    // Enable previous/current frame decompression, set decompression mode
    ScalerSetByte(P3_B1_LS_FRAME1, (_BIT7 | _BIT3 | stOdParam.enumDecmpMode));

    // Set current frame source pixel resolution
    ScalerSetByte(P3_B2_LS_FRAME2, (stOdParam.enumCurSrcRes));

    // Set level estimation range, level estimation gain
    ScalerSetByte(P3_B3_LS_FRAME4, (_OD_EST_RANGE_BYPASS | 0x00));

    // Set level estimation value
    ScalerSetByte(P3_B4_LS_FRAME5, (stOdParam.ucLvlEstValue & 0x3F));

    // Set OD apply on full window
    ScalerODHLWinSetting(_HLW_FULL_WINDOW, _DB_APPLY_NO_POLLING);

    // Set noise reduction threshold
    {
        BYTE ucNrEn = (stOdParam.ucNRThreshold > 1) ? _ENABLE : _DISABLE;
        BYTE ucNrThd_B_3 = 0;
        BYTE ucNrThd_B_2_0 = 0;

        if(ucNrEn == _ENABLE)
        {
            ucNrThd_B_3 = ((stOdParam.ucNRThreshold - 1) & 0x08) >> 3;
            ucNrThd_B_2_0 = (stOdParam.ucNRThreshold - 1) & 0x07;
        }
        ScalerSetByte(P3_A2_LS_CTRL1, ((ucNrThd_B_3 << 5) | (ucNrEn << 4) | _BIT3 | ucNrThd_B_2_0));
    }

    // Clear flag
    ScalerSetByte(P3_A4_LS_STATUS0, _BIT0);
}

