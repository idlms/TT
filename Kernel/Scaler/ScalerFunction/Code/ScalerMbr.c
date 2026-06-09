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
// ID Code      : ScalerMbr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MBR__

#include "ScalerFunctionInclude.h"

//--------------------------------------------------
// Note Message For RTK Adv MBR Enable
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#warning "NOTE: RTK Adv MBR support is ON, Memory BW may be affected. Please check with SD!!!"
#endif
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define SET_MBR_DRR_TCON_PARAM_EN_STROBE(x)                     (g_stMbrDrrTconParam.b1StrobeEn = (x))
#define SET_MBR_DRR_TCON_PARAM_VSTART_STROBE(x)                 (g_stMbrDrrTconParam.usStrobeVStart = (x))
#define SET_MBR_DRR_TCON_PARAM_VEND_STROBE(x)                   (g_stMbrDrrTconParam.usStrobeVEnd = (x))
#define SET_MBR_DRR_TCON_PARAM_EN_COMP(x)                       (g_stMbrDrrTconParam.b1CompEn = (x))
#define SET_MBR_DRR_TCON_PARAM_VSTART_COMP(x)                   (g_stMbrDrrTconParam.usCompVStart = (x))
#define SET_MBR_DRR_TCON_PARAM_VEND_COMP(x)                     (g_stMbrDrrTconParam.usCompVEnd = (x))

#define GET_MBR_DRR_TCON_PARAM_EN_STROBE_EXINT0()               (g_stMbrDrrTconParam.b1StrobeEn)
#define GET_MBR_DRR_TCON_PARAM_VSTART_STROBE_EXINT0()           (g_stMbrDrrTconParam.usStrobeVStart)
#define GET_MBR_DRR_TCON_PARAM_VEND_STROBE_EXINT0()             (g_stMbrDrrTconParam.usStrobeVEnd)
#define GET_MBR_DRR_TCON_PARAM_EN_COMP_EXINT0()                 (g_stMbrDrrTconParam.b1CompEn)
#define GET_MBR_DRR_TCON_PARAM_VSTART_COMP_EXINT0()             (g_stMbrDrrTconParam.usCompVStart)
#define GET_MBR_DRR_TCON_PARAM_VEND_COMP_EXINT0()               (g_stMbrDrrTconParam.usCompVEnd)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
typedef struct
{
    BYTE b1StrobeEn : 1;
    BYTE b1CompEn : 1;
    WORD usStrobeVStart;
    WORD usStrobeVEnd;
    WORD usCompVStart;
    WORD usCompVEnd;
} StructMbrDrrTconParam;
#endif
#endif


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
WORD g_usMbrDVTotal;
EnumMbrBacklightMode g_enumMbrBacklightMode = _BACKLIGHT_MODE_CONSTANT;

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
EnumMbrDrrBacklightMode g_enumMbrDrrBacklightMode = _MBR_DRR_MODE_OFF;
EnumMbrDrrTransitionSequence g_enumMbrDrrTransSeqType = _MBR_DRR_TRANS_NONE;
EnumMbrDrrTransitionEvent g_enumMbrDrrTransEventNext = _MBR_DRR_EVENT_NONE;
StructMbrDrrTconParam g_stMbrDrrTconParam;
WORD g_pusMbrDrrVFreq[_MBR_DRR_AVG_IVF_FRAME_CNT];
volatile WORD g_usMbrDrrSafeCount;
volatile WORD g_usMbrDrrVFreq_avg;
BYTE g_ucMbrDrrStepChangeCnt;
BYTE g_ucMbrDrrVFreqIndex;
BYTE g_ucMbrDrrTconToggleTime;
bit g_bMbrDrrHWSupport;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
EnumMbrBacklightMode ScalerMbrCheckBacklightMode(EnumMbrBacklightMode enumBacklightMode);
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
void ScalerMbrDrrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
void ScalerMbrSetTconToggleSequence(BYTE ucTconEnd, WORD usDuty, WORD usHTotal);
void ScalerMbrDrrStepChange(BYTE ucTcon, WORD usStrobePeriod, WORD usStrobePeriod_prev, BYTE ucDuty, BYTE ucPosition);
void ScalerMbrDrrAdjust(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
void ScalerMbrDrrClearSetting(BYTE ucTcon);
void ScalerMbrSetIntEnable(EnumIRQ enumIRQType, bit bEnable);
WORD ScalerMbrGetDHFreq(void);
void ScalerMbrIntHandlerDVS_EXINT0(void);
void ScalerMbrIntHandlerDENStop_EXINT0(void);
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
void ScalerMbrRtkAdvMbrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Kernel check/overwrite backlight mode if the mode
//                doesn't even support
// Input Value  : enumBacklightMode - user MBR backlight mode
// Output Value : altered backlight mode
//--------------------------------------------------
EnumMbrBacklightMode ScalerMbrCheckBacklightMode(EnumMbrBacklightMode enumBacklightMode)
{
    // If DRR enable but DRR MBR not supported, use constant backlight
#if((_FREESYNC_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _OFF))
    if(enumBacklightMode != _BACKLIGHT_MODE_CONSTANT)
    {
        if(ScalerSyncGetFREESYNCEnable() == _TRUE)
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
    }
#endif

    // If DRR MBR is selected but FW/DRR status/HW do not support, use constant backlight
    if(enumBacklightMode == _BACKLIGHT_MODE_STROBE_DRR_MBR)
    {
#if((_FREESYNC_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        if((ScalerSyncGetFREESYNCEnable() == _DISABLE) || (GET_MBR_DRR_HW_SUPPORT() == _FALSE))
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
#else
        return _BACKLIGHT_MODE_CONSTANT;
#endif
    }

    // If RTK Adv MBR is selected but FW/kernel status do not support, use constant backlight
    if(enumBacklightMode == _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR)
    {
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        if(ScalerMbrGetAdvMbrStatus() == _DISABLE)
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
#else
        return _BACKLIGHT_MODE_CONSTANT;
#endif
    }

    return enumBacklightMode;
}
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate & Set TCON Parameters for DRR MBR
// Input Value  : ucTcon - TCON Number
//                ucBacklightDuty - User OSD Backlight Duty Setting
//                ucBacklightPos - User OSD Backlight Position Setting
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        WORD usDVTotal = 0;
        WORD usDENStop = 0;
        WORD usStrobeVWidth = 0;
        WORD usStrobeVPos = 0;
        WORD usDHTotal = 0;
        WORD usDuty = 0;

        usDVTotal = GET_MBR_DVTOTAL() + 1; // to prevent compensation to pop-up too early
        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H, 2, &pData[0], _AUTOINC);
        usDENStop = ((pData[0] & 0x1F) << 8) | (pData[1]);
        usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * GET_MBR_DVTOTAL() / 100L);
        usStrobeVPos = MINOF((WORD)((DWORD)ucBacklightPos * GET_MBR_DVTOTAL() / 100L), usDENStop - usStrobeVWidth); // we dont want the strobe to exceed DEN Stop

        // Toggle Setting
        usDHTotal = GET_DIS_TIMING_GEN_H_TOTAL();
        usDuty = (WORD)ucBacklightDuty * 10 + _DRR_MOTION_BLUR_REDUCTION_COMP_DUTY_OFFSET; // compensation fine-tuned duty
        ScalerMbrSetTconToggleSequence(ucTcon - 2, usDuty, usDHTotal);

        // Check if current input VFreq is valid for strobe mode
        if(GET_INPUT_TIMING_VFREQ() >= _MBR_DRR_FLICKER_IVF_LO)
        {
            // Compensation Setting
            ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, usDVTotal);
            ScalerTconInvEnableByIndex(ucTcon - 1, _ENABLE);
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _ENABLE);


            // Strobe Setting
            if(ucBacklightDuty == 100)
            {
                ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
            }
            else
            {
                ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));
            }
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _ENABLE);

            // Enable control
            ScalerTconEnableByIndex(ucTcon - 1, _ENABLE);
            ScalerTconEnableByIndex(ucTcon, _ENABLE);

            SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_STROBE);
        }
        else // constant mode
        {
            // Compensation Setting
            ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, 0x0000);
            ScalerTconInvEnableByIndex(ucTcon - 1, _ENABLE);
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _ENABLE);

            // Strobe Setting
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x0000);
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _ENABLE);

            // Enable control
            ScalerTconEnableByIndex(ucTcon - 1, _DISABLE);
            ScalerTconEnableByIndex(ucTcon, _DISABLE);

            SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_CONSTANT);
        }
    }
    else
    {
        // Setting in _LIGHT_CONTROL_OFF case
        ScalerTconEnableByIndex(ucTcon, _DISABLE);
        SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_OFF);
        DebugMessageScaler("MBR: DRR Ctrl OFF", 0);
    }
}

//--------------------------------------------------
// Description  : Calculate TCON Setting for Division of Frequency
// Input Value  : enumOutputTcon - Selected TCON Number
//                usDuty - Final Output Duty Ratio (x/1000)
//                usHTotal - Current Timing HTotal
//                usHFreq - Current Timing H-frequency
//                usMaxFreq - Current Timing(DRR) Max Frequency
// Output Value : None
//--------------------------------------------------
void ScalerMbrSetTconToggleSequence(BYTE ucTconEnd, WORD usDuty, WORD usHTotal)
{
    BYTE ucToggleTimeTotal = 0;
    BYTE ucToggleTime = 0;
    BYTE ucTconStart = ucTconEnd;

    ucToggleTimeTotal = GET_MBR_DRR_TCON_TOGGLE_TIME();

    DebugMessageScaler("MBR: ucToggleTimeTotal", ucToggleTimeTotal);

    // Calculate & Set Toggle Operation Sequence
    for(ucToggleTime = 0; ucToggleTime < ucToggleTimeTotal; ucToggleTime++)
    {
        if(ucTconStart < _TCON3)
        {
            break;
        }

        if(usDuty == 500)
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_NORMAL, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
        }
        else if(usDuty < 500)
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_AND, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
            usDuty *= 2;
        }
        else // ucDuty > 50
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_OR, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
            usDuty = 2 * (usDuty - 500);
        }
        ScalerTconAdjustByIndex(ucTconStart, 0x0000, 0x0000, 0x0000, 0x0000);
        DebugMessageScaler("MBR: ucTconStart", ucTconStart);
        ucTconStart--;
    }

    // Set the Original TCON
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_NORMAL, _DISABLE);
    ScalerTconAdjustByIndex(ucTconStart, 0x0000, (DWORD)usHTotal * usDuty / 1000L, 0x0000, 0x3FFF);
    ScalerTconEnableByIndex(ucTconStart, _ENABLE);
}

//--------------------------------------------------
// Description  : By step change the backlight parameters
// Input Value  : ucTcon - Output TCON number
//                enumMode - Backlight mode(change direction)
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrStepChange(BYTE ucTcon, WORD usStrobePeriod, WORD usStrobePeriod_prev, BYTE ucDuty, BYTE ucPosition)
{
    WORD usStrobeVWidth = 0; // Backlight ON lines
    WORD usStrobeVPos = 0; // Backlight ON Position (lines)
    WORD usDENStop = 0;

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H, 2, &pData[0], _AUTOINC);
    usDENStop = ((pData[0] & 0x1F) << 8) | (pData[1]);

    // Calculate parameters
    usStrobeVWidth = (WORD)((DWORD)ucDuty * usStrobePeriod / 100L);
    usStrobeVPos = MINOF((WORD)((DWORD)ucPosition * usStrobePeriod / 100L), MINOF(usStrobePeriod, usDENStop) - usStrobeVWidth);

    // If duty = 100, then the whole backlight control signal is always high, no need to be adjusted
    if(ucDuty == 100)
    {
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        SET_MBR_DRR_TRANS_SEQ(_MBR_DRR_TRANS_NONE);
        SET_MBR_DRR_EVENT_NEXT(_MBR_DRR_EVENT_NONE);
        return;
    }

    /*            _____________                    _____________
    // ______|___|             |______________|___|             |_____|
    //                         ^              ^
    //                     DEN_Stop          DVS
    //               _______                          _______
    // Strobe_______|       |________________________|       |_________
    //        ____________________             ____________________
    // Comp  |                    |___________|                    |___
    */

    if(usStrobePeriod == 0) // going to constant this time
    {
        // We use TCON local enable/disable to turn on/off strobe/compensation because changing VStart/VEnd in such case is challenging using FW

        // If StrobePeriod_prev < DEN_Stop, when polling at DEN_Stop, both strobe & compensation TCON are finished
        /*            _____________                    _____________
        // ______|___|             |______________|___|             |_____|
        //                         ^              ^
        //                    *DEN_Stop*         DVS
        //           _______
        // Strobe___|       |_____________________________________________
        //                   ^^^^^^^^^^^^^^^^^^^^^^^^                     (available set time for disable)
        //        _____________
        // Comp  |             |__________________________________________
        //                      ^^^^^^^^^^^^^^^^^^                        (available set time for disable)
        */
        if(usStrobePeriod_prev < usDENStop)
        {
            SET_MBR_DRR_TCON_PARAM_EN_STROBE(_DISABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_STROBE(0x0000);
            SET_MBR_DRR_TCON_PARAM_VEND_STROBE(0x0000);
            SET_MBR_DRR_TCON_PARAM_EN_COMP(_DISABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_COMP(0x0000);
            SET_MBR_DRR_TCON_PARAM_VEND_COMP(0x0000);

            // Turn off Strobe/Compensation @ DEN_Stop IRQ
            SET_MBR_DRR_TRANS_SEQ(_MBR_DRR_TRANS_DEN_STOP);
            SET_MBR_DRR_EVENT_NEXT(_MBR_DRR_EVENT_DEN_STOP);
        }
        // This case may not happen in real scenario
        /*            _____________                    _____________
        // ______|___|             |______________|___|             |_____|
        //                         ^              ^
        //                    *DEN_Stop*        "DVS"
        //               _______
        // Strobe_______|       |__________________________________________
        //                       ^^^^^^^^^^^^^^^^^^^^^                     (available set time for disable)
        //        ____________________
        // Comp  |                    |____________________________________
        //                             ^^^^^^^^^^^                         (available set time for disable)
        */
        else
        {
            SET_MBR_DRR_TCON_PARAM_EN_STROBE(_DISABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_STROBE(0x0000);
            SET_MBR_DRR_TCON_PARAM_VEND_STROBE(0x0000);
            SET_MBR_DRR_TCON_PARAM_EN_COMP(_DISABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_COMP(0x0000);
            SET_MBR_DRR_TCON_PARAM_VEND_COMP(0x0000);

            // Turn off Strobe/Compensation @ DEN_Stop IRQ
            SET_MBR_DRR_TRANS_SEQ(_MBR_DRR_TRANS_DEN_STOP);
            SET_MBR_DRR_EVENT_NEXT(_MBR_DRR_EVENT_DEN_STOP);
        }
    }
    else if(usStrobePeriod_prev == 0) // recover from constant this time
    {
        /*            _____________                    _____________           _____________
        // ______|___|             |______________|___|             |_____|___|             |_____|
        //                         ^              ^                 ^
        //                                      *DVS*           *DEN_Stop*
        //                                                                       _______
        // Strobe_______________________________________________________________|       |_________
        //                                                           ^^^^^^^^^^^                   (available set time for enable)
        //                                                                 ____________________
        // Comp  _________________________________________________________|                    |___
        //                                          ^^^^^^^^^^^^^^^^^^^^^^                         (available set time for enable)
        */

        // Pre-adjust Strobe & Compensation Parameters
        SET_MBR_DRR_TCON_PARAM_EN_STROBE(_ENABLE);
        SET_MBR_DRR_TCON_PARAM_VSTART_STROBE(usStrobeVPos);
        SET_MBR_DRR_TCON_PARAM_VEND_STROBE(usStrobeVPos + usStrobeVWidth);
        SET_MBR_DRR_TCON_PARAM_EN_COMP(_ENABLE);
        SET_MBR_DRR_TCON_PARAM_VSTART_COMP(0x0000);
        SET_MBR_DRR_TCON_PARAM_VEND_COMP(usStrobePeriod);

        // Adjust Strobe & Compensation Parameters(not effective)
        ScalerTconAdjustByIndex((ucTcon - 1), 0x0000, 0x1FFF, 0x0000, usStrobePeriod);
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));

        // First stop DVS, make sure the enable of compensation is set after DVS (won't be effective until next frame)
        // Next stop DEN_Stop enable the strobe (will be enable on next frame)
        SET_MBR_DRR_TRANS_SEQ(_MBR_DRR_TRANS_DVS_DEN_STOP);
        SET_MBR_DRR_EVENT_NEXT(_MBR_DRR_EVENT_DVS);
    }
    // If the current step of transition is not the "first(usStrobePeriod_prev == 0) from constant" or "last(usStrobePeriod == 0) from strobe"
    // we still adjust strobe/compensation by VStart/VEnd
    else
    {
        /*            _____________                    _____________
        // ______|___|             |______________|___|             |_____|
        //                         ^              ^
        //                    *DEN_Stop*         DVS
        // ----Case 1----(toward strobe)
        //           ___                                  _______
        // Strobe___|   |________________________________|       |________
        //          ^   ^                                ^       ^        (adjusted)
        //        _________                        ___________________
        // Comp  |         |______________________|                   |___
        //                 ^                                          ^   (adjusted)
        //
        // ----Case 2---- (toward constant)
        //           ___                             __
        // Strobe___|   |___________________________|  |__________________
        //          ^   ^                           ^  ^                  (adjusted)
        //        _________                        _____
        // Comp  |         |______________________|     |_________________
        //                 ^                            ^                 (adjusted)
        */
        if(usStrobePeriod_prev < usDENStop)
        {
            SET_MBR_DRR_TCON_PARAM_EN_STROBE(_ENABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_STROBE(usStrobeVPos);
            SET_MBR_DRR_TCON_PARAM_VEND_STROBE(usStrobeVPos + usStrobeVWidth);
            SET_MBR_DRR_TCON_PARAM_EN_COMP(_ENABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_COMP(0x0000);
            SET_MBR_DRR_TCON_PARAM_VEND_COMP(usStrobePeriod);


            // Adjust Strobe/Comp @ DEN_Stop
            SET_MBR_DRR_TRANS_SEQ(_MBR_DRR_TRANS_DEN_STOP);
            SET_MBR_DRR_EVENT_NEXT(_MBR_DRR_EVENT_DEN_STOP);
        }
        // If StrobePeriod_prev >= DEN_Stop, only strobe can be set when polling at DEN_Stop
        // Compensation needs to be set at/after DVS
        // Plus, when the timing is tight, polling at DEN_Stop may exceed next DVS
        // so we need to keep track of DVS counter
        /*            _____________                    _____________
        // ______|___|             |______________|___|             |_____|
        //                         ^              ^
        //                    *DEN_Stop*        "DVS"
        // ----Case1----(toward strobe)
        //               ______                            _______
        // Strobe_______|      |__________________________|       |________
        //              ^      ^                          ^       ^        (adjusted)
        //        ____________________             _______________________
        // Comp  |                    |___________|                       |
        //                            ^                                   ^(adjusted)
        // ----Case2----(toward constant)
        //               ______                       ___
        // Strobe_______|      |_____________________|   |________________
        //              ^       ^                    ^   ^                (adjusted)
        //        ____________________             _________
        // Comp  |                    |___________|         |_____________
        //                            ^                     ^             (adjusted)
        */
        else
        {
            SET_MBR_DRR_TCON_PARAM_EN_STROBE(_ENABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_STROBE(usStrobeVPos);
            SET_MBR_DRR_TCON_PARAM_VEND_STROBE(usStrobeVPos + usStrobeVWidth);
            SET_MBR_DRR_TCON_PARAM_EN_COMP(_ENABLE);
            SET_MBR_DRR_TCON_PARAM_VSTART_COMP(0x0000);
            SET_MBR_DRR_TCON_PARAM_VEND_COMP(usStrobePeriod);

            // First stop DEN_Stop, adjust strobe
            // Next stop DVS adjust comp
            SET_MBR_DRR_TRANS_SEQ(_MBR_DRR_TRANS_DEN_STOP_DVS);
            SET_MBR_DRR_EVENT_NEXT(_MBR_DRR_EVENT_DEN_STOP);
        }
    }

    // Enable DEN_Stop IRQ for mode switch
    ScalerMbrSetIntEnable(_IRQ_DEN_STOP, _ENABLE);
}

//--------------------------------------------------
// Description  : Adjust DRR MBR Parameters
// Input Value  : ucTcon - TCON Number
//                ucBacklightDuty - User OSD Backlight Duty Setting
//                ucBacklightPos - User OSD Backlight Position Setting
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrAdjust(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        WORD usDENStop = 0;
        WORD usStrobeVWidth = 0;
        WORD usStrobeVPos = 0;
        WORD usDHTotal = 0;
        WORD usDuty = 0;

        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H, 2, &pData[0], _AUTOINC);
        usDENStop = ((pData[0] & 0x1F) << 8) | (pData[1]);
        usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * (GET_MBR_DVTOTAL() + 1) / 100L);
        usStrobeVPos = MINOF((WORD)((DWORD)ucBacklightPos * (GET_MBR_DVTOTAL() + 1) / 100L), usDENStop - usStrobeVWidth); // we dont want the strobe to exceed DEN Stop

        // Adjust Toggle Setting
        usDHTotal = GET_DIS_TIMING_GEN_H_TOTAL();
        usDuty = (WORD)ucBacklightDuty * 10 + _DRR_MOTION_BLUR_REDUCTION_COMP_DUTY_OFFSET; // compensation fine-tuned duty
        ScalerMbrSetTconToggleSequence(ucTcon - 2, usDuty, usDHTotal);

        // Adjust Strobe
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        if(ucBacklightDuty == 100)
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        }
        else
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));
        }
    }
    else
    {
        ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x0000, 0x0000, 0x0000);
    }
}

//--------------------------------------------------
// Description  : Disable DRR MBR unused setting
// Input Value  : ucTcon -> PCB output TCON pin
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrClearSetting(BYTE ucTcon)
{
    BYTE ucIndex = 0;

    // Disable interrupt to clear the shared variable
    ScalerMbrSetIntEnable(_IRQ_DVS, _DISABLE);
    ScalerMbrSetIntEnable(_IRQ_DEN_STOP, _DISABLE);

    // Reset Toggle Setting
    // Clear all setting from smallest possible TCON
    ScalerTconAdjustByIndex(_TCON2, 0x0000, 0x0000, 0x0000, 0x0000);
    ScalerTconEnableByIndex(_TCON2, _DISABLE);
    for(ucIndex = _TCON3; ucIndex < (ucTcon - 1); ucIndex++)
    {
        ScalerTconEnableByIndex(ucIndex, _DISABLE);
        ScalerTconAdjustByIndex(ucIndex, 0x0000, 0x0000, 0x0000, 0x0000);
        ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucIndex, _TCON_TOGGLE_OP_NORMAL, _DISABLE);
    }

    // Reset Compensation Setting
    ScalerTconEnableByIndex((ucTcon - 1), _DISABLE);
    ScalerTconAdjustByIndex((ucTcon - 1), 0x0000, 0x0000, 0x0000, 0x0000);
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _DISABLE);
    ScalerTconInvEnableByIndex((ucTcon - 1), _DISABLE);

    // Reset Strobe Setting
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _OFF)
    ScalerTconEnableByIndex(ucTcon, _DISABLE);
    ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x0000, 0x0000, 0x0000);
#endif
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _DISABLE);

    // Reset MBR global variables
    CLR_MBR_DRR_SAFE_CNT();
    SET_MBR_DRR_VFREQ_AVG(_MBR_DRR_FLICKER_IVF_HI);
    SET_MBR_DRR_STEP_CHG_CNT(0);
    for(ucIndex = 0; ucIndex < _MBR_DRR_AVG_IVF_FRAME_CNT; ucIndex++)
    {
        SET_MBR_DRR_VFREQ(ucIndex, _MBR_DRR_FLICKER_IVF_HI);
    }
    SET_MBR_DRR_TRANS_SEQ(_MBR_DRR_TRANS_NONE);
    SET_MBR_DRR_EVENT_NEXT(_MBR_DRR_EVENT_NONE);
    memset(&g_stMbrDrrTconParam, 0x00, sizeof(StructMbrDrrTconParam));
}

//--------------------------------------------------
// Description  : Enable interrupt according to backlight mode
// Input Value  : enumMbrBacklightMode - MBR backlight mode
// Output Value : None
//--------------------------------------------------
void ScalerMbrSetIntEnable(EnumIRQ enumIRQType, bit bEnable)
{
    // MBR DRR only uses DVS and DEN_Stop IRQ
    if((enumIRQType == _IRQ_DVS) || (enumIRQType == _IRQ_DEN_STOP))
    {
        ScalerGlobalSetInterrupt(enumIRQType, bEnable);
    }
}

//--------------------------------------------------
// Description  : Get D-HFreq
// Input Value  : None
// Output Value : D-HFreq
//--------------------------------------------------
WORD ScalerMbrGetDHFreq(void)
{
    return (WORD)(GET_D_CLK_FREQ() / GET_DIS_TIMING_GEN_H_TOTAL());
}

//--------------------------------------------------
// Description  : DRR MBR handler interrupt process (EXINT0 only)
//                Recording & calculating input & average framerate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrIntHandlerDVS_EXINT0(void) using 1
{
    // DVS event
    if(ScalerGetBit_EXINT(P0_08_IRQ_CTRL2, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // Clear DVS IRQ flag
        ScalerSetBit_EXINT(P0_08_IRQ_CTRL2, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);

        if(GET_MBR_BACKLIGHT_MODE_EXINT0() == _BACKLIGHT_MODE_STROBE_DRR_MBR)
        {
            WORD usMbrVFreq_avg = 0;
            BYTE ucCnt = 0;

            // DRR MBR Transition
            if(GET_MBR_DRR_EVENT_NEXT_EXINT0() == _MBR_DRR_EVENT_DVS)
            {
                // Adjust Compensation
                // Extract from ScalerTconEnableByIndex and ScalerTconAdjustByIndex
                ScalerSetDataPortBit_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + ((_PCB_MBR_TCON_PIN - 1) << 4), ~(_BIT7), ((BYTE)GET_MBR_DRR_TCON_PARAM_EN_COMP_EXINT0() << 7));
                ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_10_TC0_VS_MSB + ((_PCB_MBR_TCON_PIN - 1) << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_COMP_EXINT0()));
                ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_11_TC0_VS_LSB + ((_PCB_MBR_TCON_PIN - 1) << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_COMP_EXINT0()));
                ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_12_TC0_VE_MSB + ((_PCB_MBR_TCON_PIN - 1) << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VEND_COMP_EXINT0()));
                ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_13_TC0_VE_LSB + ((_PCB_MBR_TCON_PIN - 1) << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VEND_COMP_EXINT0()));

                // Check if it is the last move
                if(GET_MBR_DRR_TRANS_SEQ_EXINT0() == _MBR_DRR_TRANS_DEN_STOP_DVS)
                {
                    SET_MBR_DRR_TRANS_SEQ_EXINT0(_MBR_DRR_TRANS_NONE);
                    SET_MBR_DRR_EVENT_NEXT_EXINT0(_MBR_DRR_EVENT_NONE);

                    if(GET_MBR_DRR_BACKLIGHT_MODE_EXINT0() == _MBR_DRR_MODE_STROBE_TO_CONSTANT)
                    {
                        if(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() == _MBR_DRR_TRANSITION_FRAME_CNT_LO)
                        {
                            SET_MBR_DRR_BACKLIGHT_MODE_EXINT0(_MBR_DRR_MODE_CONSTANT);
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(0);
                        }
                        else
                        {
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() + 1);
                        }
                    }
                    else
                    {
                        if(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() == _MBR_DRR_TRANSITION_FRAME_CNT_HI)
                        {
                            SET_MBR_DRR_BACKLIGHT_MODE_EXINT0(_MBR_DRR_MODE_STROBE);
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(0);
                        }
                        else
                        {
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() + 1);
                        }
                    }
                }
                else if(GET_MBR_DRR_TRANS_SEQ_EXINT0() == _MBR_DRR_TRANS_DVS_DEN_STOP)
                {
                    SET_MBR_DRR_EVENT_NEXT_EXINT0(_MBR_DRR_EVENT_DEN_STOP);
                }
            }

            // Calculate average framerate
            ucCnt = g_ucMbrDrrVFreqIndex % _MBR_DRR_AVG_IVF_FRAME_CNT;

            SET_MBR_DRR_VFREQ_EXINT0(ucCnt, GET_INPUT_TIMING_VFREQ());
            for(ucCnt = 0; ucCnt < _MBR_DRR_AVG_IVF_FRAME_CNT; ucCnt++)
            {
                usMbrVFreq_avg += GET_MBR_DRR_VFREQ(ucCnt);
            }
            SET_MBR_DRR_VFREQ_AVG_EXINT0(usMbrVFreq_avg / _MBR_DRR_AVG_IVF_FRAME_CNT);

            if(GET_MBR_DRR_VFREQ_AVG() < _MBR_DRR_FLICKER_IVF_LO)
            {
                CLR_MBR_DRR_SAFE_CNT_EXINT0();
            }
            else
            {
                SET_MBR_DRR_SAFE_CNT_EXINT0();
            }

            g_ucMbrDrrVFreqIndex++;
        }
    }
}

//--------------------------------------------------
// Description  : DRR MBR handler interrupt process (EXINT0 only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrIntHandlerDENStop_EXINT0(void) using 1
{
    // DEN_Stop event
    if(ScalerGetBit_EXINT(P0_05_IRQ_CTRL1, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // Set DEN_START flag
        SET_EVENT_DEN_STOP_INT(_TRUE);

        // Clear DEN_START IRQ flag
        ScalerSetBit_EXINT(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);

        if(GET_MBR_BACKLIGHT_MODE_EXINT0() == _BACKLIGHT_MODE_STROBE_DRR_MBR)
        {
            bit bLastMove = _FALSE;
            // DRR MBR Transition
            if(GET_MBR_DRR_EVENT_NEXT_EXINT0() == _MBR_DRR_EVENT_DEN_STOP)
            {
                if(GET_MBR_DRR_TRANS_SEQ_EXINT0() == _MBR_DRR_TRANS_DVS_DEN_STOP)
                {
                    // Adjust strobe
                    // Extract from ScalerTconEnableByIndex and ScalerTconAdjustByIndex
                    ScalerSetDataPortBit_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (_PCB_MBR_TCON_PIN << 4), ~(_BIT7), ((BYTE)GET_MBR_DRR_TCON_PARAM_EN_STROBE_EXINT0() << 7));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_10_TC0_VS_MSB + (_PCB_MBR_TCON_PIN << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_11_TC0_VS_LSB + (_PCB_MBR_TCON_PIN << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_12_TC0_VE_MSB + (_PCB_MBR_TCON_PIN << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VEND_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_13_TC0_VE_LSB + (_PCB_MBR_TCON_PIN << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VEND_STROBE_EXINT0()));
                    bLastMove = _TRUE;
                }
                else if(GET_MBR_DRR_TRANS_SEQ_EXINT0() == _MBR_DRR_TRANS_DEN_STOP)
                {
                    // Adjust strobe/compenation
                    // Extract from ScalerTconEnableByIndex and ScalerTconAdjustByIndex
                    ScalerSetDataPortBit_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (_PCB_MBR_TCON_PIN << 4), ~(_BIT7), ((BYTE)GET_MBR_DRR_TCON_PARAM_EN_STROBE_EXINT0() << 7));
                    ScalerSetDataPortBit_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + ((_PCB_MBR_TCON_PIN - 1) << 4), ~(_BIT7), ((BYTE)GET_MBR_DRR_TCON_PARAM_EN_COMP_EXINT0() << 7));

                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_10_TC0_VS_MSB + (_PCB_MBR_TCON_PIN << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_11_TC0_VS_LSB + (_PCB_MBR_TCON_PIN << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_12_TC0_VE_MSB + (_PCB_MBR_TCON_PIN << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VEND_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_13_TC0_VE_LSB + (_PCB_MBR_TCON_PIN << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VEND_STROBE_EXINT0()));

                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_10_TC0_VS_MSB + ((_PCB_MBR_TCON_PIN - 1) << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_COMP_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_11_TC0_VS_LSB + ((_PCB_MBR_TCON_PIN - 1) << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_COMP_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_12_TC0_VE_MSB + ((_PCB_MBR_TCON_PIN - 1) << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VEND_COMP_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_13_TC0_VE_LSB + ((_PCB_MBR_TCON_PIN - 1) << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VEND_COMP_EXINT0()));
                    bLastMove = _TRUE;
                }
                else if(GET_MBR_DRR_TRANS_SEQ_EXINT0() == _MBR_DRR_TRANS_DEN_STOP_DVS)
                {
                    // Adjust strobe/compenation
                    // Extract from ScalerTconEnableByIndex and ScalerTconAdjustByIndex
                    ScalerSetDataPortBit_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_18_TC0_CTRL + (_PCB_MBR_TCON_PIN << 4), ~(_BIT7), ((BYTE)GET_MBR_DRR_TCON_PARAM_EN_STROBE_EXINT0() << 7));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_10_TC0_VS_MSB + (_PCB_MBR_TCON_PIN << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_11_TC0_VS_LSB + (_PCB_MBR_TCON_PIN << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VSTART_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_12_TC0_VE_MSB + (_PCB_MBR_TCON_PIN << 4), HIBYTE(GET_MBR_DRR_TCON_PARAM_VEND_STROBE_EXINT0()));
                    ScalerSetDataPortByte_EXINT0(P15_A3_TCON_ADDR, _P15_A4_PT_13_TC0_VE_LSB + (_PCB_MBR_TCON_PIN << 4), LOBYTE(GET_MBR_DRR_TCON_PARAM_VEND_STROBE_EXINT0()));
                }

                // Check if it is the last move
                if(bLastMove == _TRUE)
                {
                    SET_MBR_DRR_TRANS_SEQ_EXINT0(_MBR_DRR_TRANS_NONE);
                    SET_MBR_DRR_EVENT_NEXT_EXINT0(_MBR_DRR_EVENT_NONE);

                    if(GET_MBR_DRR_BACKLIGHT_MODE_EXINT0() == _MBR_DRR_MODE_STROBE_TO_CONSTANT)
                    {
                        if(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() == _MBR_DRR_TRANSITION_FRAME_CNT_LO)
                        {
                            SET_MBR_DRR_BACKLIGHT_MODE_EXINT0(_MBR_DRR_MODE_CONSTANT);
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(0);
                        }
                        else
                        {
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() + 1);
                        }
                    }
                    else
                    {
                        if(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() == _MBR_DRR_TRANSITION_FRAME_CNT_HI)
                        {
                            SET_MBR_DRR_BACKLIGHT_MODE_EXINT0(_MBR_DRR_MODE_STROBE);
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(0);
                        }
                        else
                        {
                            SET_MBR_DRR_STEP_CHG_CNT_EXINT0(GET_MBR_DRR_STEP_CHG_CNT_EXINT0() + 1);
                        }
                    }
                }
                else
                {
                    SET_MBR_DRR_EVENT_NEXT_EXINT0(_MBR_DRR_EVENT_DVS);
                }
            }
        }
    }
}

#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Prepare & set the necessary parameters for RTK Adv MBR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrRtkAdvMbrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    StructRtkAdvMbrTimingInfo stTimingInfo;
    memset(&stTimingInfo, 0, sizeof(StructRtkAdvMbrTimingInfo));

    DebugMessageScaler("MBR Adv: bLightCtrl", bLightCtrl);
    DebugMessageScaler("MBR Adv: VTotal", GET_MBR_DVTOTAL());
    DebugMessageScaler("MBR Adv: ucBacklightDuty", ucBacklightDuty);
    DebugMessageScaler("MBR Adv: ucBacklightPos", ucBacklightPos);

    stTimingInfo.usDclk = GET_D_CLK_FREQ();
    stTimingInfo.usHTotal = GET_MDOMAIN_OUTPUT_HTOTAL();
    stTimingInfo.usVTotal = GET_MBR_DVTOTAL(); // from measure result
    stTimingInfo.usVFreq = g_usDVFreq;

    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        ScalerMbrRtkAdvMbrAdjust(&stTimingInfo, ucTcon, ucBacklightDuty, ucBacklightPos, _ENABLE);
    }
    else
    {
        ScalerMbrRtkAdvMbrAdjust(&stTimingInfo, ucTcon, ucBacklightDuty, ucBacklightPos, _DISABLE);
    }
}
#endif // End of #if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#endif // End of #if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)

