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
#include "ScalerFunctionInclude.h"
#include "RTD2014Include.h"

#if (_PANEL_TYPE == _PANEL_NONE)
bit _DISPLAY_DP_TX_PORT_1 = _OFF;
bit _DISPLAY_DP_TX_PORT_2 = _OFF;
bit _DISPLAY_DP_TX_FB_MODE = _OFF;

bit _PANEL_DPTX_FB_SWAP = 0;
bit _PANEL_DPTX_LANE_SWAP = 0;
bit _PANEL_DPTX_LANE_PN_SWAP = 0;
BYTE _DPLL_SSCG_DIV_MODE = _DIV_1;

BYTE _LVDS_PORT_SEL = 0;
bit _LVDS_PORT_MIRROR = 0;
BYTE _LVDS_PORT_AB_SWAP = 0;
BYTE _LVDS_PORT_CD_SWAP = 0;
BYTE _LVDS_PORT_EF_SWAP = 0;
BYTE _LVDS_PORT_GH_SWAP = 0;
BYTE _LVDS_PN_SWAP = 0;

DWORD _PIP_MAIN_BW = 0;

// PANEL DEFINE
//////////////////////////VBY1//////////////////////////
code PanelConfig LW550AQD_OLED = {
    _PANEL_LG_LW550AQD, // PANEL_IDX
    _PANEL_VBO,         // PANEL_STYLE
    _PANEL_PIXEL_LCD,   // PANEL_PIXEL_TYPE

    _VBO_DISP_4_BYTE_MODE,                   // VBO_BYTE_MODE
    _VBO_8_DATA_LANE,                        // VBO_OUTPUT_PORT
    _VBO_DISP_30_BIT,                        // VBO_BIT_MODE
    _VBO_PANEL_1_SECTION,                    // VBO_PANEL_SECTION
    _VBO_HS_NORMAL,                          // VBO_HS_CONTROL
    _VBO_VS_NORMAL,                          // VBO_VS_CONTROL
    _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK, // VBO_VIDEO_TRANSFER_TYPE
    0,                                       // CDR_TRANSFER_ALN_LATENCY

    0, // PANEL_DPTX_LINK_RATE
    0, // PANEL_DPTX_LANE_NUMBER
    0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
    0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
    0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
    0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
    0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

    0, // LVDS_OUTPUT_PORT
    0, // LVDS_PANEL_SECTION
    0, // LVDS_TABLE_TYPE

    _OFF,               // PANEL_EXIST_MULTIPANEL
    _PANEL_LGD,         // PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

    600, // PANEL_TYP_FRAME_RATE
    610, // PANEL_MAX_FRAME_RATE
    475, // PANEL_MIN_FRAME_RATE

    48,   // PANEL_DH_START
    3840, // PANEL_DH_WIDTH
    3888, // PANEL_DH_END

    4400, // PANEL_DH_TOTAL
    4800, // PANEL_DH_TOTAL_MAX
    4240, // PANEL_DH_TOTAL_MIN

    6,    // PANEL_DV_START
    2160, // PANEL_DV_HEIGHT
    2166, // PANEL_DV_END

    2250, // PANEL_DV_TOTAL
    2820, // PANEL_DV_TOTAL_MAX
    2248, // PANEL_DV_TOTAL_MIN

    8, // PANEL_DH_SYNC_WIDTH
    2, // PANEL_DV_SYNC_HEIGHT

    594, // PANEL_PIXEL_CLOCK
    600, // PANEL_PIXEL_CLOCK_MAX
    586, // PANEL_PIXEL_CLOCK_MIN

    400,  // PANEL_POWER_ON_T1
    40,   // PANEL_POWER_ON_T2
    2500, // PANEL_POWER_ON_T3

    2000, // PANEL_POWER_OFF_T4
    50,   // PANEL_POWER_OFF_T5
    500,  // PANEL_POWER_OFF_T6

    4100, // LAST_LINE_TARGET
    20,   // FRAME_SYNC_MARGIN

    0,                // PANEL_ADC_OFFSET_BIAS
    0,                // PANEL_ADC_GAIN_BIAS
    _VBO_8_DATA_LANE, // BYTE DHTOTAL_MULTIPLE;
    _OFF,             // PANEL_POW_SEQ_FAST_MODE
};

code PanelConfig LD490EGE_FHM1 = {
    _PANEL_LG_LD490EGE_FHM1, // PANEL_IDX
    _PANEL_VBO,              // PANEL_STYLE
    _PANEL_PIXEL_LCD,        // PANEL_PIXEL_TYPE

    _VBO_DISP_4_BYTE_MODE,                   // VBO_BYTE_MODE
    _VBO_8_DATA_LANE,                        // VBO_OUTPUT_PORT
    _VBO_DISP_30_BIT,                        // VBO_BIT_MODE
    _VBO_PANEL_1_SECTION,                    // VBO_PANEL_SECTION
    _VBO_HS_NORMAL,                          // VBO_HS_CONTROL
    _VBO_VS_NORMAL,                          // VBO_VS_CONTROL
    _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK, // VBO_VIDEO_TRANSFER_TYPE
    0,                                       // CDR_TRANSFER_ALN_LATENCY

    0, // PANEL_DPTX_LINK_RATE
    0, // PANEL_DPTX_LANE_NUMBER
    0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
    0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
    0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
    0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
    0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

    0, // LVDS_OUTPUT_PORT
    0, // LVDS_PANEL_SECTION
    0, // LVDS_TABLE_TYPE

    _OFF,               // PANEL_EXIST_MULTIPANEL
    _PANEL_LGD,         // PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

    600, // PANEL_TYP_FRAME_RATE
    610, // PANEL_MAX_FRAME_RATE
    590, // PANEL_MIN_FRAME_RATE

    48,   // PANEL_DH_START
    3840, // PANEL_DH_WIDTH
    3888, // PANEL_DH_END

    4400, // PANEL_DH_TOTAL
    4560, // PANEL_DH_TOTAL_MAX
    4240, // PANEL_DH_TOTAL_MIN

    6,    // PANEL_DV_START
    2160, // PANEL_DV_HEIGHT
    2166, // PANEL_DV_END

    2250, // PANEL_DV_TOTAL
    2790, // PANEL_DV_TOTAL_MAX
    2200, // PANEL_DV_TOTAL_MIN

    8, // PANEL_DH_SYNC_WIDTH
    2, // PANEL_DV_SYNC_HEIGHT

    594, // PANEL_PIXEL_CLOCK
    600, // PANEL_PIXEL_CLOCK_MAX
    560, // PANEL_PIXEL_CLOCK_MIN

    5,   // PANEL_POWER_ON_T1
    200, // PANEL_POWER_ON_T2
    500, // PANEL_POWER_ON_T3

    100, // PANEL_POWER_OFF_T4
    50,  // PANEL_POWER_OFF_T5
    500, // PANEL_POWER_OFF_T6

    4100, // LAST_LINE_TARGET
    20,   // FRAME_SYNC_MARGIN

    0,                // PANEL_ADC_OFFSET_BIAS
    0,                // PANEL_ADC_GAIN_BIAS
    _VBO_8_DATA_LANE, // BYTE DHTOTAL_MULTIPLE;
    _OFF,             // PANEL_POW_SEQ_FAST_MODE
};

code PanelConfig M280DGJ_L30 = {
    _PANEL_INNOLUX_28_M280DGJ_L30, // PANEL_IDX
    _PANEL_VBO,                    // PANEL_STYLE
    _PANEL_PIXEL_LCD,              // PANEL_PIXEL_TYPE

    _VBO_DISP_4_BYTE_MODE,                   // VBO_BYTE_MODE
    _VBO_8_DATA_LANE,                        // VBO_OUTPUT_PORT
    _VBO_DISP_30_BIT,                        // VBO_BIT_MODE
    _VBO_PANEL_1_SECTION,                    // VBO_PANEL_SECTION
    _VBO_HS_NORMAL,                          // VBO_HS_CONTROL
    _VBO_VS_NORMAL,                          // VBO_VS_CONTROL
    _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK, // VBO_VIDEO_TRANSFER_TYPE
    0,                                       // CDR_TRANSFER_ALN_LATENCY

    0, // PANEL_DPTX_LINK_RATE
    0, // PANEL_DPTX_LANE_NUMBER
    0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
    0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
    0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
    0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
    0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

    0, // LVDS_OUTPUT_PORT
    0, // LVDS_PANEL_SECTION
    0, // LVDS_TABLE_TYPE

    _OFF,               // PANEL_EXIST_MULTIPANEL
    _PANEL_INNOLUX,     // PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

    600, // PANEL_TYP_FRAME_RATE
    610, // PANEL_MAX_FRAME_RATE
    590, // PANEL_MIN_FRAME_RATE

    48,   // PANEL_DH_START
    3840, // PANEL_DH_WIDTH
    3888, // PANEL_DH_END

    4400, // PANEL_DH_TOTAL
    4560, // PANEL_DH_TOTAL_MAX
    4240, // PANEL_DH_TOTAL_MIN

    6,    // PANEL_DV_START
    2160, // PANEL_DV_HEIGHT
    2166, // PANEL_DV_END

    2250, // PANEL_DV_TOTAL
    2790, // PANEL_DV_TOTAL_MAX
    2200, // PANEL_DV_TOTAL_MIN

    8, // PANEL_DH_SYNC_WIDTH
    2, // PANEL_DV_SYNC_HEIGHT

    594, // PANEL_PIXEL_CLOCK
    600, // PANEL_PIXEL_CLOCK_MAX
    560, // PANEL_PIXEL_CLOCK_MIN

    5,   // PANEL_POWER_ON_T1
    200, // PANEL_POWER_ON_T2
    500, // PANEL_POWER_ON_T3

    100, // PANEL_POWER_OFF_T4
    50,  // PANEL_POWER_OFF_T5
    500, // PANEL_POWER_OFF_T6

    4100, // LAST_LINE_TARGET
    20,   // FRAME_SYNC_MARGIN

    0,                // PANEL_ADC_OFFSET_BIAS
    0,                // PANEL_ADC_GAIN_BIAS
    _VBO_8_DATA_LANE, // BYTE DHTOTAL_MULTIPLE;
    _OFF,             // PANEL_POW_SEQ_FAST_MODE
};

code PanelConfig G270ZAN01_1 = {
    _PANEL_AUO_G270ZAN01_0, // PANEL_IDX
    _PANEL_VBO,             // PANEL_STYLE
    _PANEL_PIXEL_LCD,       // PANEL_PIXEL_TYPE

    _VBO_DISP_4_BYTE_MODE,                   // VBO_BYTE_MODE
    _VBO_8_DATA_LANE,                        // VBO_OUTPUT_PORT
    _VBO_DISP_30_BIT,                        // VBO_BIT_MODE
    _VBO_PANEL_2_SECTION,                    // VBO_PANEL_SECTION
    _VBO_HS_NORMAL,                          // VBO_HS_CONTROL
    _VBO_VS_NORMAL,                          // VBO_VS_CONTROL
    _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK, // VBO_VIDEO_TRANSFER_TYPE
    0,                                       // CDR_TRANSFER_ALN_LATENCY

    0, // PANEL_DPTX_LINK_RATE
    0, // PANEL_DPTX_LANE_NUMBER
    0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
    0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
    0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
    0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
    0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

    0, // LVDS_OUTPUT_PORT
    0, // LVDS_PANEL_SECTION
    0, // LVDS_TABLE_TYPE

    _OFF,               // PANEL_EXIST_MULTIPANEL
    _PANEL_AUO,         // PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

    600, // PANEL_TYP_FRAME_RATE
    610, // PANEL_MAX_FRAME_RATE
    590, // PANEL_MIN_FRAME_RATE

    48,   // PANEL_DH_START
    3840, // PANEL_DH_WIDTH
    3888, // PANEL_DH_END

    4400, // PANEL_DH_TOTAL
    4560, // PANEL_DH_TOTAL_MAX
    4240, // PANEL_DH_TOTAL_MIN

    6,    // PANEL_DV_START
    2160, // PANEL_DV_HEIGHT
    2166, // PANEL_DV_END

    2250, // PANEL_DV_TOTAL
    2790, // PANEL_DV_TOTAL_MAX
    2200, // PANEL_DV_TOTAL_MIN

    8, // PANEL_DH_SYNC_WIDTH
    2, // PANEL_DV_SYNC_HEIGHT

    594, // PANEL_PIXEL_CLOCK
    600, // PANEL_PIXEL_CLOCK_MAX
    560, // PANEL_PIXEL_CLOCK_MIN

    5,   // PANEL_POWER_ON_T1
    200, // PANEL_POWER_ON_T2
    500, // PANEL_POWER_ON_T3

    100, // PANEL_POWER_OFF_T4
    50,  // PANEL_POWER_OFF_T5
    500, // PANEL_POWER_OFF_T6

    4100, // LAST_LINE_TARGET
    20,   // FRAME_SYNC_MARGIN

    0,                // PANEL_ADC_OFFSET_BIAS
    0,                // PANEL_ADC_GAIN_BIAS
    _VBO_8_DATA_LANE, // BYTE DHTOTAL_MULTIPLE;
    _OFF,             // PANEL_POW_SEQ_FAST_MODE
};

code PanelConfig G320ZAN01_0 = {
    _PANEL_AUO_G320ZAN01_0, // PANEL_IDX
    _PANEL_VBO,             // PANEL_STYLE
    _PANEL_PIXEL_LCD,       // PANEL_PIXEL_TYPE

    _VBO_DISP_4_BYTE_MODE,                   // VBO_BYTE_MODE
    _VBO_8_DATA_LANE,                        // VBO_OUTPUT_PORT
    _VBO_DISP_30_BIT,                        // VBO_BIT_MODE
    _VBO_PANEL_2_SECTION,                    // VBO_PANEL_SECTION
    _VBO_HS_NORMAL,                          // VBO_HS_CONTROL
    _VBO_VS_NORMAL,                          // VBO_VS_CONTROL
    _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK, // VBO_VIDEO_TRANSFER_TYPE
    0,                                       // CDR_TRANSFER_ALN_LATENCY

    0, // PANEL_DPTX_LINK_RATE
    0, // PANEL_DPTX_LANE_NUMBER
    0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
    0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
    0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
    0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
    0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

    0, // LVDS_OUTPUT_PORT
    0, // LVDS_PANEL_SECTION
    0, // LVDS_TABLE_TYPE

    _OFF,               // PANEL_EXIST_MULTIPANEL
    _PANEL_AUO,         // PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

    600, // PANEL_TYP_FRAME_RATE
    610, // PANEL_MAX_FRAME_RATE
    590, // PANEL_MIN_FRAME_RATE

    48,   // PANEL_DH_START
    3840, // PANEL_DH_WIDTH
    3888, // PANEL_DH_END

    4400, // PANEL_DH_TOTAL
    4560, // PANEL_DH_TOTAL_MAX
    4240, // PANEL_DH_TOTAL_MIN

    6,    // PANEL_DV_START
    2160, // PANEL_DV_HEIGHT
    2166, // PANEL_DV_END

    2250, // PANEL_DV_TOTAL
    2790, // PANEL_DV_TOTAL_MAX
    2200, // PANEL_DV_TOTAL_MIN

    8, // PANEL_DH_SYNC_WIDTH
    2, // PANEL_DV_SYNC_HEIGHT

    594, // PANEL_PIXEL_CLOCK
    600, // PANEL_PIXEL_CLOCK_MAX
    560, // PANEL_PIXEL_CLOCK_MIN

    5,   // PANEL_POWER_ON_T1
    200, // PANEL_POWER_ON_T2
    500, // PANEL_POWER_ON_T3

    100, // PANEL_POWER_OFF_T4
    50,  // PANEL_POWER_OFF_T5
    500, // PANEL_POWER_OFF_T6

    4100, // LAST_LINE_TARGET
    20,   // FRAME_SYNC_MARGIN

    0,                // PANEL_ADC_OFFSET_BIAS
    0,                // PANEL_ADC_GAIN_BIAS
    _VBO_8_DATA_LANE, // BYTE DHTOTAL_MULTIPLE;
    _OFF,             // PANEL_POW_SEQ_FAST_MODE
};

code PanelConfig P650QVN05_0 = {
    _PANEL_AUO_P650QVN05_0, // PANEL_IDX
    _PANEL_VBO,             // PANEL_STYLE
    _PANEL_PIXEL_LCD,       // PANEL_PIXEL_TYPE

    _VBO_DISP_4_BYTE_MODE,                   // VBO_BYTE_MODE
    _VBO_8_DATA_LANE,                        // VBO_OUTPUT_PORT
    _VBO_DISP_30_BIT,                        // VBO_BIT_MODE
    _VBO_PANEL_2_SECTION,                    // VBO_PANEL_SECTION
    _VBO_HS_NORMAL,                          // VBO_HS_CONTROL
    _VBO_VS_NORMAL,                          // VBO_VS_CONTROL
    _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK, // VBO_VIDEO_TRANSFER_TYPE
    0,                                       // CDR_TRANSFER_ALN_LATENCY

    0, // PANEL_DPTX_LINK_RATE
    0, // PANEL_DPTX_LANE_NUMBER
    0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
    0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
    0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
    0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
    0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

    0, // LVDS_OUTPUT_PORT
    0, // LVDS_PANEL_SECTION
    0, // LVDS_TABLE_TYPE

    _OFF,               // PANEL_EXIST_MULTIPANEL
    _PANEL_AUO,         // PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

    600, // PANEL_TYP_FRAME_RATE
    610, // PANEL_MAX_FRAME_RATE
    590, // PANEL_MIN_FRAME_RATE

    48,   // PANEL_DH_START
    3840, // PANEL_DH_WIDTH
    3888, // PANEL_DH_END

    4400, // PANEL_DH_TOTAL
    4560, // PANEL_DH_TOTAL_MAX
    4240, // PANEL_DH_TOTAL_MIN

    6,    // PANEL_DV_START
    2160, // PANEL_DV_HEIGHT
    2166, // PANEL_DV_END

    2250, // PANEL_DV_TOTAL
    2790, // PANEL_DV_TOTAL_MAX
    2200, // PANEL_DV_TOTAL_MIN

    8, // PANEL_DH_SYNC_WIDTH
    2, // PANEL_DV_SYNC_HEIGHT

    594, // PANEL_PIXEL_CLOCK
    600, // PANEL_PIXEL_CLOCK_MAX
    560, // PANEL_PIXEL_CLOCK_MIN

    5,   // PANEL_POWER_ON_T1
    200, // PANEL_POWER_ON_T2
    500, // PANEL_POWER_ON_T3

    100, // PANEL_POWER_OFF_T4
    50,  // PANEL_POWER_OFF_T5
    500, // PANEL_POWER_OFF_T6

    4100, // LAST_LINE_TARGET
    20,   // FRAME_SYNC_MARGIN

    0,                // PANEL_ADC_OFFSET_BIAS
    0,                // PANEL_ADC_GAIN_BIAS
    _VBO_8_DATA_LANE, // BYTE DHTOTAL_MULTIPLE;
    _OFF,             // PANEL_POW_SEQ_FAST_MODE
};
/////////////////////////EDP/////////////////////////////
code PanelConfig LM270WR3_SSA1 = {
    _PANEL_LG_LM270WR3_SSA1, // PANEL_IDX
    _PANEL_DPTX,             // PANEL_STYLE
    _PANEL_PIXEL_LCD,        // PANEL_PIXEL_TYPE

    0, // VBO_BYTE_MODE
    0, // VBO_OUTPUT_PORT
    0, // VBO_BIT_MODE
    0, // VBO_PANEL_SECTION
    0, // VBO_HS_CONTROL
    0, // VBO_VS_CONTROL
    0, // VBO_VIDEO_TRANSFER_TYPE
    0, // CDR_TRANSFER_ALN_LATENCY

    _PANEL_DPTX_LINK_HBR2,     // PANEL_DPTX_LINK_RATE
    _PANEL_DPTX_LANE_NUMBER_4, // PANEL_DPTX_LANE_NUMBER
    _OFF,                       // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
    _DISABLE,                  // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
    _DISABLE,                  // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
    _DISABLE,                  // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
    _DISABLE,                  // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

    0, // LVDS_OUTPUT_PORT
    0, // LVDS_PANEL_SECTION
    0, // LVDS_TABLE_TYPE

    _OFF,               // PANEL_EXIST_MULTIPANEL
    _PANEL_LGD,         // PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

    600, // PANEL_TYP_FRAME_RATE
    610, // PANEL_MAX_FRAME_RATE
    590, // PANEL_MIN_FRAME_RATE

    48,   // PANEL_DH_START
    3840, // PANEL_DH_WIDTH
    3888, // PANEL_DH_END

    4000, // PANEL_DH_TOTAL
    4040, // PANEL_DH_TOTAL_MAX
    3940, // PANEL_DH_TOTAL_MIN

    6,    // PANEL_DV_START
    2160, // PANEL_DV_HEIGHT
    2166, // PANEL_DV_END

    2222, // PANEL_DV_TOTAL
    2240, // PANEL_DV_TOTAL_MAX
    2180, // PANEL_DV_TOTAL_MIN

    32, // PANEL_DH_SYNC_WIDTH
    5,  // PANEL_DV_SYNC_HEIGHT

    533, // PANEL_PIXEL_CLOCK
    586, // PANEL_PIXEL_CLOCK_MAX
    517, // PANEL_PIXEL_CLOCK_MIN

    10,  // PANEL_POWER_ON_T1
    100, // PANEL_POWER_ON_T2
    50,  // PANEL_POWER_ON_T3

    50,  // PANEL_POWER_OFF_T4
    50,  // PANEL_POWER_OFF_T5
    300, // PANEL_POWER_OFF_T6

    3700, // LAST_LINE_TARGET
    20,   // FRAME_SYNC_MARGIN

    0,   // PANEL_ADC_OFFSET_BIAS
    0,   // PANEL_ADC_GAIN_BIAS
    (4), // BYTE DHTOTAL_MULTIPLE;
    _ON, // PANEL_POW_SEQ_FAST_MODE
};

// /////////////////////////////LVDS////////////////////////
// code PanelConfig LM238WF4_SSA1 = {
//     _PANEL_LG_LM238WF4_SSA1, // PANEL_IDX
//     _PANEL_LVDS,             // PANEL_STYLE
//     _PANEL_PIXEL_LCD,        // PANEL_PIXEL_TYPE

//     0, // VBO_BYTE_MODE
//     0, // VBO_OUTPUT_PORT
//     0, // VBO_BIT_MODE
//     0, // VBO_PANEL_SECTION
//     0, // VBO_HS_CONTROL
//     0, // VBO_VS_CONTROL
//     0, // VBO_VIDEO_TRANSFER_TYPE
//     0, // CDR_TRANSFER_ALN_LATENCY

//     0, // PANEL_DPTX_LINK_RATE
//     0, // PANEL_DPTX_LANE_NUMBER
//     0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
//     0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
//     0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
//     0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
//     0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

//     _LVDS_2_PORT,            // LVDS_OUTPUT_PORT
//     _LVDS_PANEL_1_SECTION,   // LVDS_PANEL_SECTION
//     _LVDS_BIT_MAP_TABLE_1_3, // LVDS_TABLE_TYPE

//     _OFF,               // PANEL_EXIST_MULTIPANEL
//     _PANEL_LGD,         // PANEL_MANUFACTURER
//     _PANEL_DISP_24_BIT, // PANEL_DISP_BIT_MODE

//     600, // PANEL_TYP_FRAME_RATE
//     610, // PANEL_MAX_FRAME_RATE
//     590, // PANEL_MIN_FRAME_RATE

//     48,   // PANEL_DH_START
//     1920, // PANEL_DH_WIDTH
//     1968, // PANEL_DH_END

//     2200, // PANEL_DH_TOTAL
//     2240, // PANEL_DH_TOTAL_MAX
//     2048, // PANEL_DH_TOTAL_MIN

//     6,    // PANEL_DV_START
//     1080, // PANEL_DV_HEIGHT
//     1086, // PANEL_DV_END

//     1125, // PANEL_DV_TOTAL
//     1160, // PANEL_DV_TOTAL_MAX
//     1090, // PANEL_DV_TOTAL_MIN

//     8, // PANEL_DH_SYNC_WIDTH
//     2, // PANEL_DV_SYNC_HEIGHT

//     148, // PANEL_PIXEL_CLOCK
//     190, // PANEL_PIXEL_CLOCK_MAX
//     110, // PANEL_PIXEL_CLOCK_MIN

//     10,  // PANEL_POWER_ON_T1
//     50,  // PANEL_POWER_ON_T2
//     500, // PANEL_POWER_ON_T3

//     200,  // PANEL_POWER_OFF_T4
//     50,   // PANEL_POWER_OFF_T5
//     1000, // PANEL_POWER_OFF_T6

//     1100, // LAST_LINE_TARGET
//     20,   // FRAME_SYNC_MARGIN

//     0,    // PANEL_ADC_OFFSET_BIAS
//     0,    // PANEL_ADC_GAIN_BIAS
//     (4),  //  DHTOTAL_MULTIPLE;
//     _OFF, // PANEL_POW_SEQ_FAST_MODE
// };

// code PanelConfig FHD_8BIT_JEIDA = {
//     _PANEL_LG_LM238WF4_SSA1, // PANEL_IDX
//     _PANEL_LVDS,             // PANEL_STYLE
//     _PANEL_PIXEL_LCD,        // PANEL_PIXEL_TYPE

//     0, // VBO_BYTE_MODE
//     0, // VBO_OUTPUT_PORT
//     0, // VBO_BIT_MODE
//     0, // VBO_PANEL_SECTION
//     0, // VBO_HS_CONTROL
//     0, // VBO_VS_CONTROL
//     0, // VBO_VIDEO_TRANSFER_TYPE
//     0, // CDR_TRANSFER_ALN_LATENCY

//     0, // PANEL_DPTX_LINK_RATE
//     0, // PANEL_DPTX_LANE_NUMBER
//     0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
//     0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
//     0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
//     0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
//     0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

//     _LVDS_2_PORT,            // LVDS_OUTPUT_PORT
//     _LVDS_PANEL_1_SECTION,   // LVDS_PANEL_SECTION
//     _LVDS_BIT_MAP_TABLE_2_4, // LVDS_TABLE_TYPE

//     _OFF,               // PANEL_EXIST_MULTIPANEL
//     _PANEL_LGD,         // PANEL_MANUFACTURER
//     _PANEL_DISP_24_BIT, // PANEL_DISP_BIT_MODE

//     600, // PANEL_TYP_FRAME_RATE
//     610, // PANEL_MAX_FRAME_RATE
//     590, // PANEL_MIN_FRAME_RATE

//     48,   // PANEL_DH_START
//     1920, // PANEL_DH_WIDTH
//     1968, // PANEL_DH_END

//     2200, // PANEL_DH_TOTAL
//     2240, // PANEL_DH_TOTAL_MAX
//     2048, // PANEL_DH_TOTAL_MIN

//     6,    // PANEL_DV_START
//     1080, // PANEL_DV_HEIGHT
//     1086, // PANEL_DV_END

//     1125, // PANEL_DV_TOTAL
//     1160, // PANEL_DV_TOTAL_MAX
//     1090, // PANEL_DV_TOTAL_MIN

//     8, // PANEL_DH_SYNC_WIDTH
//     2, // PANEL_DV_SYNC_HEIGHT

//     148, // PANEL_PIXEL_CLOCK
//     190, // PANEL_PIXEL_CLOCK_MAX
//     110, // PANEL_PIXEL_CLOCK_MIN

//     10,  // PANEL_POWER_ON_T1
//     50,  // PANEL_POWER_ON_T2
//     500, // PANEL_POWER_ON_T3

//     200,  // PANEL_POWER_OFF_T4
//     50,   // PANEL_POWER_OFF_T5
//     1000, // PANEL_POWER_OFF_T6

//     1100, // LAST_LINE_TARGET
//     20,   // FRAME_SYNC_MARGIN

//     0,    // PANEL_ADC_OFFSET_BIAS
//     0,    // PANEL_ADC_GAIN_BIAS
//     (4),  //  DHTOTAL_MULTIPLE;
//     _OFF, // PANEL_POW_SEQ_FAST_MODE
// };
// code PanelConfig G270HAN01_0 = {
//     _PANEL_AUO_G270HAN01_0, // PANEL_IDX
//     _PANEL_LVDS,            // PANEL_STYLE
//     _PANEL_PIXEL_LCD,       // PANEL_PIXEL_TYPE

//     0, // VBO_BYTE_MODE
//     0, // VBO_OUTPUT_PORT
//     0, // VBO_BIT_MODE
//     0, // VBO_PANEL_SECTION
//     0, // VBO_HS_CONTROL
//     0, // VBO_VS_CONTROL
//     0, // VBO_VIDEO_TRANSFER_TYPE
//     0, // CDR_TRANSFER_ALN_LATENCY

//     0, // PANEL_DPTX_LINK_RATE
//     0, // PANEL_DPTX_LANE_NUMBER
//     0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
//     0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
//     0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
//     0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
//     0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

//     _LVDS_2_PORT,            // LVDS_OUTPUT_PORT
//     _LVDS_PANEL_1_SECTION,   // LVDS_PANEL_SECTION
//     _LVDS_BIT_MAP_TABLE_2_4, // LVDS_TABLE_TYPE

//     _OFF,               // PANEL_EXIST_MULTIPANEL
//     _PANEL_AUO,         // PANEL_MANUFACTURER
//     _PANEL_DISP_30_BIT, // PANEL_DISP_BIT_MODE

//     600, // PANEL_TYP_FRAME_RATE
//     610, // PANEL_MAX_FRAME_RATE
//     590, // PANEL_MIN_FRAME_RATE

//     48,   // PANEL_DH_START
//     1920, // PANEL_DH_WIDTH
//     1968, // PANEL_DH_END

//     2200, // PANEL_DH_TOTAL
//     2240, // PANEL_DH_TOTAL_MAX
//     2048, // PANEL_DH_TOTAL_MIN

//     6,    // PANEL_DV_START
//     1080, // PANEL_DV_HEIGHT
//     1086, // PANEL_DV_END

//     1125, // PANEL_DV_TOTAL
//     1160, // PANEL_DV_TOTAL_MAX
//     1090, // PANEL_DV_TOTAL_MIN

//     8, // PANEL_DH_SYNC_WIDTH
//     2, // PANEL_DV_SYNC_HEIGHT

//     148, // PANEL_PIXEL_CLOCK
//     190, // PANEL_PIXEL_CLOCK_MAX
//     110, // PANEL_PIXEL_CLOCK_MIN

//     10,  // PANEL_POWER_ON_T1
//     50,  // PANEL_POWER_ON_T2
//     500, // PANEL_POWER_ON_T3

//     200,  // PANEL_POWER_OFF_T4
//     50,   // PANEL_POWER_OFF_T5
//     1000, // PANEL_POWER_OFF_T6

//     1100, // LAST_LINE_TARGET
//     20,   // FRAME_SYNC_MARGIN

//     0,    // PANEL_ADC_OFFSET_BIAS
//     0,    // PANEL_ADC_GAIN_BIAS
//     (4),  //  DHTOTAL_MULTIPLE;
//     _OFF, // PANEL_POW_SEQ_FAST_MODE
// };

// code PanelConfig G270QAN01_2 = {
//     _PANEL_AUO_G270QAN01_2, // PANEL_IDX
//     _PANEL_LVDS,            // PANEL_STYLE
//     _PANEL_PIXEL_LCD,       // PANEL_PIXEL_TYPE

//     0, // VBO_BYTE_MODE
//     0, // VBO_OUTPUT_PORT
//     0, // VBO_BIT_MODE
//     0, // VBO_PANEL_SECTION
//     0, // VBO_HS_CONTROL
//     0, // VBO_VS_CONTROL
//     0, // VBO_VIDEO_TRANSFER_TYPE
//     0, // CDR_TRANSFER_ALN_LATENCY

//     0, // PANEL_DPTX_LINK_RATE
//     0, // PANEL_DPTX_LANE_NUMBER
//     0, // PANEL_DPTX_FORCE_OUTPUT_SUPPORT
//     0, // PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
//     0, // PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
//     0, // PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
//     0, // PANEL_DPTX_FORCE_ALTERNATE_SR_CAP

//     _LVDS_4_PORT,            // LVDS_OUTPUT_PORT
//     _LVDS_PANEL_1_SECTION,   // LVDS_PANEL_SECTION
//     _LVDS_BIT_MAP_TABLE_1_3, // LVDS_TABLE_TYPE

//     _OFF,               // PANEL_EXIST_MULTIPANEL
//     _PANEL_AUO,         // PANEL_MANUFACTURER
//     _PANEL_DISP_24_BIT, // PANEL_DISP_BIT_MODE

//     600, // PANEL_TYP_FRAME_RATE
//     610, // PANEL_MAX_FRAME_RATE
//     590, // PANEL_MIN_FRAME_RATE

//     48,   // PANEL_DH_START
//     2560, // PANEL_DH_WIDTH
//     2608, // PANEL_DH_END

//     2720, // PANEL_DH_TOTAL
//     2736, // PANEL_DH_TOTAL_MAX
//     2704, // PANEL_DH_TOTAL_MIN

//     6,    // PANEL_DV_START
//     1440, // PANEL_DV_HEIGHT
//     1446, // PANEL_DV_END

//     1481, // PANEL_DV_TOTAL
//     1483, // PANEL_DV_TOTAL_MAX
//     1479, // PANEL_DV_TOTAL_MIN

//     8, // PANEL_DH_SYNC_WIDTH
//     2, // PANEL_DV_SYNC_HEIGHT

//     242, // PANEL_PIXEL_CLOCK
//     280, // PANEL_PIXEL_CLOCK_MAX
//     210, // PANEL_PIXEL_CLOCK_MIN

//     10,  // PANEL_POWER_ON_T1
//     50,  // PANEL_POWER_ON_T2
//     500, // PANEL_POWER_ON_T3

//     200,  // PANEL_POWER_OFF_T4
//     50,   // PANEL_POWER_OFF_T5
//     1000, // PANEL_POWER_OFF_T6

//     1480, // LAST_LINE_TARGET
//     20,   // FRAME_SYNC_MARGIN

//     0,    // PANEL_ADC_OFFSET_BIAS
//     0,    // PANEL_ADC_GAIN_BIAS
//     (4),  //  DHTOTAL_MULTIPLE;
//     _OFF, // PANEL_POW_SEQ_FAST_MODE
// };
//****************************************************************************
//****************************************************************************
PanelConfig panelData;
PanelConfig *activeConfig;
PanelConfig code *g_pActivePanelConfig;

void DipSwitch(void)
{
    BYTE U8DIPSWITCH = 0;
	
//     U8DIPSWITCH = ((bGPIO10 ? 1 : 0) << 0) |
//                   ((bGPIO9 ? 1 : 0) << 1) |
//                   ((bGPIO8 ? 1 : 0) << 2) | // 5V EN
//                   ((bGPIO7 ? 1 : 0) << 3) | // BLU INVERT
//                   ((bGPIO6 ? 1 : 0) << 4) |
//                   ((bGPIO5 ? 1 : 0) << 5) |
//                   ((bGPIO4 ? 1 : 0) << 6) |
//                   ((bGPIO3 ? 1 : 0) << 7);
	
//     U8DIPSWITCH = (~U8DIPSWITCH);
//     DebugMessageScaler("U8DIPSWITCH", U8DIPSWITCH);
// #if(_CUSTOMER_TYPE == _CUSTOMER_AWERONET)
//     switch (U8DIPSWITCH & 0xF3)    //&0xF3 IGNORE bGPIO7, bGPIO8
//     {
//     case 0x12: // 0001XX10 LG EDP 4K
//         g_pActivePanelConfig = &LM270WR3_SSA1;
//         _OGC_FLASH_BANK = 21;
//         break;
//     case 0x90: // 1001XX00 LG VBY1 4K
//         g_pActivePanelConfig = &LD490EGE_FHM1;
//         _OGC_FLASH_BANK = 20;
//         break;
//     case 0x91: // 1001XX01 AUO VBY1 4K
//         g_pActivePanelConfig = &G320ZAN01_0;
//         break;
//     default: // INNOLUX VBY1 4K
//         g_pActivePanelConfig = &_ACTIVE_PANEL_CONFIG;
//         _OGC_FLASH_BANK = 15;
//         break;
//     }
// #else
//     switch (U8DIPSWITCH & 0xF3)    //&0xF3 IGNORE bGPIO7, bGPIO8
//     {
//     case 0x12: // 0001XX10 LG EDP 4K
//         g_pActivePanelConfig = &LM270WR3_SSA1;
//         break;
//     case 0x90: // 1001XX00 LG VBY1 4K
//         g_pActivePanelConfig = &LD490EGE_FHM1;
//         break;
//     case 0x91: // 1001XX01 AUO VBY1 4K
//         g_pActivePanelConfig = &G320ZAN01_0;
//         break;
//     case 0xB8:
//         g_pActivePanelConfig = &LW550AQD_OLED;
//         break;
//     default: 
//         g_pActivePanelConfig = &_ACTIVE_PANEL_CONFIG;
//         break;
//     }
// #endif //(_CUSTOMER_TYPE == _CUSTOMER_AWERONET)
//      //DebugMessageLee("_OGC_FLASH_BANK", _OGC_FLASH_BANK);
    if(MCU_FE27_PORT87_PIN_REG)
        g_pActivePanelConfig = &M280DGJ_L30;
    else
        g_pActivePanelConfig = &LM270WR3_SSA1;
}

void InitPanelSetting(void)
{
    BYTE i;
    DipSwitch();

    activeConfig = &panelData;

    for (i = 0; i < sizeof(PanelConfig); ++i)
    {
        ((BYTE *)activeConfig)[i] = ((BYTE code *)g_pActivePanelConfig)[i];
    }
    DebugMessageScaler("Panel Style", activeConfig->PANEL_IDX);
    if (_PANEL_STYLE == _PANEL_VBO)
        _DPLL_SSCG_DIV_MODE = (_DIV_8);
    else
        _DPLL_SSCG_DIV_MODE = (_DIV_1);

    if(_PANEL_STYLE == _PANEL_DPTX)
    {
        if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
        {
            _PANEL_DPTX_FB_SWAP = _PANEL_DPTX_1_2_FB_SWAP;
            _PANEL_DPTX_LANE_SWAP = _PANEL_DPTX_1_2_LANE_SWAP;
            _PANEL_DPTX_LANE_PN_SWAP = _PANEL_DPTX_1_2_LANE_PN_SWAP;
        }
        else if((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR) || (_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_RBR))
        {
            _PANEL_DPTX_FB_SWAP = _PANEL_DPTX_1_1_FB_SWAP;
            _PANEL_DPTX_LANE_SWAP = _PANEL_DPTX_1_1_LANE_SWAP;
            _PANEL_DPTX_LANE_PN_SWAP = _PANEL_DPTX_1_1_LANE_PN_SWAP;
        }

        if (_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
        {
            _DISPLAY_DP_TX_PORT_1 = _ON;
            _DISPLAY_DP_TX_PORT_2 = _ON;
            _DISPLAY_DP_TX_FB_MODE = (_D_DOMAIN_PATH == _D_DOMAIN_4_PATH) ? _OFF : _ON;

            _DHTOTAL_MULTIPLE = (1 << _PANEL_DPTX_LANE_NUMBER);
        }
        else
        {
            _DISPLAY_DP_TX_PORT_1 = (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX1_PORT) ? _ON : _OFF;
            _DISPLAY_DP_TX_PORT_2 = (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX2_PORT) ? _ON : _OFF;
            _DISPLAY_DP_TX_FB_MODE = _OFF;
            
            if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                _DHTOTAL_MULTIPLE = (8);
            else
                _DHTOTAL_MULTIPLE = (4);
        }
    
    }
}
#endif // End of #if(_PANEL_TYPE == _PANEL_NONE)


