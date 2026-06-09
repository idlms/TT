/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary                    */
/*                                                                              */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

#if (_PANEL_TYPE == _PANEL_NONE)

// PANEL IDX
#define _PANEL_INNOLUX_28_M280DGJ_L30 0
#define _PANEL_INNOLUX_42_V420DK01_DK1 1
#define _PANEL_INNOLUX_50_S500DJ2_KS5 2
#define _PANEL_AUO_M320QAN01_0 3
#define _PANEL_AUO_G320ZAN01_0 4
#define _PANEL_LG_LM270WR5_SSA1 5
#define _PANEL_LG_LC430EQE_FHA1 6
#define _PANEL_LG_LD490EGE_FHM1 7
#define _PANEL_LG_LD650EGE_FHM1 8
#define _PANEL_AUO_P430QVN02_0 9
#define _PANEL_LG_LM340UW1_SSA3 10
#define _PANEL_SAMSUNG_LTI460HF01 11
#define _PANEL_LG_LM238WR2_SPA1 12
#define _PANEL_LG_LM265SQ1 13
#define _PANEL_LG_LM300WQ6_SLC1 14
#define _PANEL_LG_LD880DEN 15
#define _PANEL_SAMSUNG_LTI750HF01 16
#define _PANEL_LG_LB213QX1_SL01 17
#define _PANEL_NEC_NL204153AC21_09 18
#define _PANEL_AUO_P750QVN02_1 19
#define _PANEL_LG_LW550JUL_HMA1 20
#define _PANEL_LG_LD490DUN_THC4 21
#define _PANEL_AUO_M270QAN01_0 31
#define _PANEL_INNOLUX_10_4_G104ACJ_L01 32
#define _PANEL_LG_LD860EQN_PMG2 33
#define _PANEL_TIANMA_NL256204AC16_01 34
#define _PANEL_AUO_G150XTN06_B 35
#define _PANEL_TOVIS_T430TLLAB0 36
#define _PANEL_SAMSUNG_LTI650FN01 37
#define _PANEL_INNOLUX_M315DJJ_K31_V3 38
#define _PANEL_AUO_P550QVN06_3 39
#define _PANEL_LG_LM238WF4_SSA1 40
#define _PANEL_AUO_G270HAN01_0 41
#define _PANEL_AUO_G270ZAN01_0 42
#define _PANEL_LG_LM270WR3_SSA1 43
#define _PANEL_AUO_P650QVN05_0 44
#define _PANEL_LG_LW550AQD 45
#define _PANEL_AUO_G270QAN01_2  46
#define _PANEL_INNOLUX_GK133VB_01B  47

// PANEL TYPE
#define _PANEL_IDX activeConfig->PANEL_IDX
#define _PANEL_STYLE activeConfig->PANEL_STYLE
#define _PANEL_PIXEL_TYPE activeConfig->PANEL_PIXEL_TYPE

// VBO
#define _VBO_BYTE_MODE activeConfig->VBO_BYTE_MODE
#define _VBO_OUTPUT_PORT activeConfig->VBO_OUTPUT_PORT
#define _VBO_BIT_MODE activeConfig->VBO_BIT_MODE
#define _VBO_PANEL_SECTION activeConfig->VBO_PANEL_SECTION
#define _VBO_HS_CONTROL activeConfig->VBO_HS_CONTROL
#define _VBO_VS_CONTROL activeConfig->VBO_VS_CONTROL
#define _VBO_VIDEO_TRANSFER_TYPE activeConfig->VBO_VIDEO_TRANSFER_TYPE
#define _CDR_TRANSFER_ALN_LATENCY activeConfig->CDR_TRANSFER_ALN_LATENCY

// DPTx
#define _PANEL_DPTX_LINK_RATE activeConfig->PANEL_DPTX_LINK_RATE
#define _PANEL_DPTX_LANE_NUMBER activeConfig->PANEL_DPTX_LANE_NUMBER
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT activeConfig->PANEL_DPTX_FORCE_OUTPUT_SUPPORT
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING activeConfig->PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD activeConfig->PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP activeConfig->PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP activeConfig->PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

// LVDS
#define _LVDS_OUTPUT_PORT activeConfig->LVDS_OUTPUT_PORT
#define _LVDS_PANEL_SECTION activeConfig->LVDS_PANEL_SECTION
#define _LVDS_TABLE_TYPE activeConfig->LVDS_TABLE_TYPE

// COMMON
#define _PANEL_MANUFACTURER activeConfig->PANEL_MANUFACTURER
#define _PANEL_DISP_BIT_MODE activeConfig->PANEL_DISP_BIT_MODE

#define _PANEL_TYP_FRAME_RATE activeConfig->PANEL_TYP_FRAME_RATE
#define _PANEL_MAX_FRAME_RATE activeConfig->PANEL_MAX_FRAME_RATE
#define _PANEL_MIN_FRAME_RATE activeConfig->PANEL_MIN_FRAME_RATE

// Panel Parameter
#define _PANEL_DH_START activeConfig->PANEL_DH_START
#define _PANEL_DH_WIDTH activeConfig->PANEL_DH_WIDTH
#define _PANEL_DH_END activeConfig->PANEL_DH_END

#define _PANEL_DH_TOTAL activeConfig->PANEL_DH_TOTAL
#define _PANEL_DH_TOTAL_MAX activeConfig->PANEL_DH_TOTAL_MAX
#define _PANEL_DH_TOTAL_MIN activeConfig->PANEL_DH_TOTAL_MIN

#define _PANEL_DV_START activeConfig->PANEL_DV_START
#define _PANEL_DV_HEIGHT activeConfig->PANEL_DV_HEIGHT
#define _PANEL_DV_END activeConfig->PANEL_DV_END

#define _PANEL_DV_TOTAL activeConfig->PANEL_DV_TOTAL
#define _PANEL_DV_TOTAL_MAX activeConfig->PANEL_DV_TOTAL_MAX
#define _PANEL_DV_TOTAL_MIN activeConfig->PANEL_DV_TOTAL_MIN

#define _PANEL_DH_SYNC_WIDTH activeConfig->PANEL_DH_SYNC_WIDTH
#define _PANEL_DV_SYNC_HEIGHT activeConfig->PANEL_DV_SYNC_HEIGHT

#define _PANEL_PIXEL_CLOCK activeConfig->PANEL_PIXEL_CLOCK
#define _PANEL_PIXEL_CLOCK_MAX activeConfig->PANEL_PIXEL_CLOCK_MAX
#define _PANEL_PIXEL_CLOCK_MIN activeConfig->PANEL_PIXEL_CLOCK_MIN

#define _PANEL_POWER_ON_T1 activeConfig->PANEL_POWER_ON_T1
#define _PANEL_POWER_ON_T2 activeConfig->PANEL_POWER_ON_T2
#define _PANEL_POWER_ON_T3 activeConfig->PANEL_POWER_ON_T3

#define _PANEL_POWER_OFF_T4 activeConfig->PANEL_POWER_OFF_T4
#define _PANEL_POWER_OFF_T5 activeConfig->PANEL_POWER_OFF_T5
#define _PANEL_POWER_OFF_T6 activeConfig->PANEL_POWER_OFF_T6

#define _LAST_LINE_TARGET activeConfig->LAST_LINE_TARGET
#define _FRAME_SYNC_MARGIN activeConfig->FRAME_SYNC_MARGIN

#define _PANEL_ADC_OFFSET_BIAS activeConfig->PANEL_ADC_OFFSET_BIAS
#define _PANEL_ADC_GAIN_BIAS activeConfig->PANEL_ADC_GAIN_BIAS

//
#define _DHTOTAL_MULTIPLE activeConfig->DHTOTAL_MULTIPLE
#define _PANEL_POW_SEQ_FAST_MODE activeConfig->PANEL_POW_SEQ_FAST_MODE

#define _PANEL_PIXEL_CLOCK_UNIT _PANEL_CLOCK_MHZ
#define _PANEL_EXIST_MULTIPANEL _OFF

typedef struct
{
    BYTE PANEL_IDX;
    //////////////////
    // General Info //
    //////////////////
    BYTE PANEL_STYLE : 4;
    BYTE PANEL_PIXEL_TYPE : 4;
    ////////////////////////////
    // VBO Panel Configuration
    ////////////////////////////
    BYTE VBO_BYTE_MODE : 4;
    BYTE VBO_OUTPUT_PORT : 4;
    BYTE VBO_BIT_MODE : 4;
    BYTE VBO_PANEL_SECTION : 4;
    BYTE VBO_HS_CONTROL : 4;
    BYTE VBO_VS_CONTROL : 4;
    BYTE VBO_VIDEO_TRANSFER_TYPE : 1;
    BYTE CDR_TRANSFER_ALN_LATENCY;

    ////////////////////////////
    // DPTx Panel Configuration
    ////////////////////////////
    BYTE PANEL_DPTX_LINK_RATE;
    BYTE PANEL_DPTX_LANE_NUMBER : 4;
    BYTE PANEL_DPTX_FORCE_OUTPUT_SUPPORT : 1;
    BYTE PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING : 1;
    BYTE PANEL_DPTX_FORCE_MSA_DOWN_SPREAD : 1;
    BYTE PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP : 1;
    BYTE PANEL_DPTX_FORCE_ALTERNATE_SR_CAP : 1;

    ////////////////////////////
    // LVDS Panel Configuration
    ////////////////////////////
    BYTE LVDS_OUTPUT_PORT : 4;
    BYTE LVDS_PANEL_SECTION : 4;
    BYTE LVDS_TABLE_TYPE : 2;

    ////////////////////////////
    // MultiPanel & Manufacturer
    ////////////////////////////
    BYTE PANEL_EXIST_MULTIPANEL : 1;
    BYTE PANEL_MANUFACTURER;
    BYTE PANEL_DISP_BIT_MODE : 4;

    ////////////////////////
    // Frame Rate (0.1 Hz)
    ////////////////////////
    WORD PANEL_TYP_FRAME_RATE;
    WORD PANEL_MAX_FRAME_RATE;
    WORD PANEL_MIN_FRAME_RATE;

    ///////////////
    // Parameter //
    ///////////////
    WORD PANEL_DH_START;
    WORD PANEL_DH_WIDTH;
    WORD PANEL_DH_END;

    WORD PANEL_DH_TOTAL;
    WORD PANEL_DH_TOTAL_MAX;
    WORD PANEL_DH_TOTAL_MIN;

    WORD PANEL_DV_START;
    WORD PANEL_DV_HEIGHT;
    WORD PANEL_DV_END;

    WORD PANEL_DV_TOTAL;
    WORD PANEL_DV_TOTAL_MAX;
    WORD PANEL_DV_TOTAL_MIN;

    WORD PANEL_DH_SYNC_WIDTH;
    WORD PANEL_DV_SYNC_HEIGHT;

    WORD PANEL_PIXEL_CLOCK;
    WORD PANEL_PIXEL_CLOCK_MAX;
    WORD PANEL_PIXEL_CLOCK_MIN;

    WORD PANEL_POWER_ON_T1;
    WORD PANEL_POWER_ON_T2;
    WORD PANEL_POWER_ON_T3;

    WORD PANEL_POWER_OFF_T4;
    WORD PANEL_POWER_OFF_T5;
    WORD PANEL_POWER_OFF_T6;

    ///////////////
    // Display //
    ///////////////
    WORD LAST_LINE_TARGET;
    WORD FRAME_SYNC_MARGIN;

    /////////////////////
    // VGA Auto Color //
    /////////////////////
    BYTE PANEL_ADC_OFFSET_BIAS;
    BYTE PANEL_ADC_GAIN_BIAS;
    // ETC
    BYTE DHTOTAL_MULTIPLE : 4;
    BYTE PANEL_POW_SEQ_FAST_MODE : 4;
} PanelConfig;

/////////////////////////
// Color Default Table //
/////////////////////////
extern PanelConfig *activeConfig;
//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _PANEL_NONE)

//--------------------------------------------------
// Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
// #define _FRAME_SYNC_MARGIN                      0

