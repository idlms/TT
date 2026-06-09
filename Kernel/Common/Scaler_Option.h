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
// ID Code      : Scaler_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_OPTION_H__
#define __SCALER_OPTION_H__

//--------------------------------------------------
// MN DPLL Phase Swallow Path Type
//--------------------------------------------------
#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F))
#define _MN_DPLL_PATH_TYPE                                  _MN_DPLL_PATH1
#define _MN_DPLL_FREQ_UP                                    ((_PANEL_STYLE == _PANEL_DPTX) || (_PANEL_STYLE == _PANEL_LVDS))
#endif

//-------------------------------------------------
// MN MPLL Phase Swallow Path Type
//-------------------------------------------------
#if(_MPLL_STRUCT_TYPE == _MPLL_STRUCT_M_N)
#define _MN_MPLL_PATH_TYPE                                  _MN_MPLL_PATH1
#define _MN_MPLL_FREQ_UP                                    _ON
#endif
//--------------------------------------------------
// LC_Tank Clock Frequncy Define
//--------------------------------------------------
#if(_LC_TANK_SUPPORT == _ON)
#define _LC_TANK_XTAL_FREQUENCY                             _LCTANK27000K
#endif

//--------------------------------------------------
// Memory Type Option
//--------------------------------------------------
#if(_MEMORY_TYPE == _EXTERNAL_MEMORY)

#define _MEMORY_TYPE_CONFIG                                 (_EXTERNAL_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK)
#define _MEMORY_SIZE_CONFIG                                 _EXTERNAL_MEMORY_SIZE_CONFIG

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_MODE_NONE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_FRC_MODE
#endif

#elif(_MEMORY_TYPE == _EMBEDDED_MEMORY)

#define _MEMORY_TYPE_CONFIG                                 (_EMBEDDED_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK)
#define _MEMORY_SIZE_CONFIG                                 _EMBEDDED_MEMORY_SIZE_CONFIG

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_MODE_NONE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
#if(_SCALER_TYPE == _RL6851_SERIES)
#define _SDRAM_PHASE_CALIBRATION                            _OFF
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_MCU_MODE
#else
#define _SDRAM_PHASE_CALIBRATION                            _ON
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_MCU_MODE
#define _SDRAM_PHASE_ON_LINE_ADDRESS                        (0x1FFDF7) // 2047 row, Bank1, 248 column (remain 8 cell)
#endif
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#define _DDR1_PHASE_CALIBRATION                             _ON
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_MCU_MODE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#define _DDR2_PHASE_CALIBRATION                             _ON
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_MCU_MODE
#endif

#elif(_MEMORY_TYPE == _GEN_NONE)

#define _MEMORY_TYPE_CONFIG                                 _NO_MEMORY
#define _MEMORY_PHASE_CALIBRATION_MODE                      _MEMORY_PHASE_CALIBRATION_MODE_NONE

#endif // End of #if(_MEMORY_TYPE == _EXTERNAL_MEMORY)

#if(_MEMORY_TYPE_CONFIG != _MEMORY_SDRAM)
#define _SDRAM_PHASE_CALIBRATION                            _OFF
#endif

#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR1)
#define _DDR1_PHASE_CALIBRATION                             _OFF
#endif

#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR2)
#define _DDR2_PHASE_CALIBRATION                             _OFF
#endif

//--------------------------------------------------
// D Domain 4 Path for FrameSync Line Buffer Option
//--------------------------------------------------
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#undef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT                     _ON
#endif


//--------------------------------------------------
// CEC Related Define
//--------------------------------------------------
#define _HDMI_CEC_SUPPORT                                   ((_HW_HDMI_CEC_GEN != _HW_CEC_GEN_NONE) &&\
                                                             ((_D0_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D1_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D2_HDMI_CEC_PIN == _HDMI_CEC_0) ||\
                                                             (_D3_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D4_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D5_HDMI_CEC_PIN == _HDMI_CEC_0)))


//--------------------------------------------------
// AUDIO Related Define
//--------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
#define _AUDIO_FW_TRACKING_MODE_SUPPORT                     (_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _OFF)
#undef _DIGITAL_AUDIO_OUTPUT_FIX_I2S_PHASE_DELAY
#define _DIGITAL_AUDIO_OUTPUT_FIX_I2S_PHASE_DELAY           _OFF
#endif

#else

#undef _AUDIO_TTS_SUPPORT_TYPE
#define _AUDIO_TTS_SUPPORT_TYPE                             _AUDIO_TTS_NOT_SUPPORT

#undef _AUDIO_TTS_CONTENT_BIT_FORMAT
#define _AUDIO_TTS_CONTENT_BIT_FORMAT                       _AUDIO_TTS_CONTENT_8_BIT

#undef _AUDIO_TTS_CONTENT_FREQUENCY
#define _AUDIO_TTS_CONTENT_FREQUENCY                        _AUDIO_TTS_CONTENT_8_KHZ

#undef _HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT
#define _HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT                _OFF

#undef _HDMI_AUDIO_SPREAD_PCODE_SUPPORT
#define _HDMI_AUDIO_SPREAD_PCODE_SUPPORT                    _OFF

#undef _EMBEDDED_DAC_SUPPORT
#define _EMBEDDED_DAC_SUPPORT                               _OFF

#undef _DAC_SPEAKER_OUTPUT_SUPPORT
#define _DAC_SPEAKER_OUTPUT_SUPPORT                         _OFF

#undef _DAC_HP_OUTPUT_SUPPORT
#define _DAC_HP_OUTPUT_SUPPORT                              _OFF

#undef _DAC_SPEAKER_OUTPUT_SWAP
#define _DAC_SPEAKER_OUTPUT_SWAP                            _OFF

#undef _DAC_HP_OUTPUT_SWAP
#define _DAC_HP_OUTPUT_SWAP                                 _OFF

#undef _DAC_DEPOP_TO_NORMAL_WAIT_TIME
#define _DAC_DEPOP_TO_NORMAL_WAIT_TIME                      SEC(0.1)

#undef _DAC_DITHER_FUNCTION_LEVEL
#define _DAC_DITHER_FUNCTION_LEVEL                          _AUDIO_DAC_DITHER_LEVEL_OFF

#undef _LINE_IN_SUPPORT
#define _LINE_IN_SUPPORT                                    _OFF

#undef _LINE_IN_DAC_AOUT_GAIN_DB
#define _LINE_IN_DAC_AOUT_GAIN_DB                           _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)

#undef _LINE_IN_DAC_HPOUT_GAIN_DB
#define _LINE_IN_DAC_HPOUT_GAIN_DB                          _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)

#undef _LINE_IN_BOOST_GAIN_DB
#define _LINE_IN_BOOST_GAIN_DB                              0x17 // 0dB, 1.5dB for each step, Max Gain: 0x3F(30dB)

#undef _LINE_IN_VOLUME_MAX
#define _LINE_IN_VOLUME_MAX                                 0x3FFF // MAX: 0x3FFF

#undef _LINE_IN_VOLUME_MIN
#define _LINE_IN_VOLUME_MIN                                 0x0000

#undef _LINE_IN_AA_PATH_SUPPORT
#define _LINE_IN_AA_PATH_SUPPORT                            _OFF

#undef _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT
#define _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT                  _OFF

#undef _DIGITAL_DAC_AOUT_GAIN_DB
#define _DIGITAL_DAC_AOUT_GAIN_DB                           _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)

#undef _DIGITAL_DAC_HPOUT_GAIN_DB
#define _DIGITAL_DAC_HPOUT_GAIN_DB                          _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)

#undef _DIGITAL_VOLUME_MAX
#define _DIGITAL_VOLUME_MAX                                 0x3FFF // MAX: 0x3FFF

#undef _DIGITAL_VOLUME_MIN
#define _DIGITAL_VOLUME_MIN                                 0x0000

#undef _SLEEP_AUDIO_SUPPORT
#define _SLEEP_AUDIO_SUPPORT                                _OFF

#undef _PS_AUDIO_INPUT
#define _PS_AUDIO_INPUT                                     _PS_AUDIO_DP

#undef _DVC_ADJUST_TYPE
#define _DVC_ADJUST_TYPE                                    _DB_GAIN

#undef _DB_GAIN_DOWN_VALUE
#define _DB_GAIN_DOWN_VALUE                                 _DB_GAIN_1_8_DB   // For _DB_GAIN

#undef _DB_GAIN_UP_VALUE
#define _DB_GAIN_UP_VALUE                                   _DB_GAIN_1_8_DB   // For _DB_GAIN

#undef _VOLUME_STEP_SIZE_VALUE
#define _VOLUME_STEP_SIZE_VALUE                             (0x0040 & 0x3FFF) // For _VOLUME_STEP_SIZE

#undef _DVC_VOLUME_MUTE_TIMER
#define _DVC_VOLUME_MUTE_TIMER                              400 // ms

#undef _DP_DVC_ADJUST_TYPE
#define _DP_DVC_ADJUST_TYPE                                 _DB_GAIN

#undef _DP_DB_GAIN_DOWN_VALUE
#define _DP_DB_GAIN_DOWN_VALUE                              _DB_GAIN_1_8_DB   // For _DB_GAIN Mode

#undef _DP_DB_GAIN_UP_VALUE
#define _DP_DB_GAIN_UP_VALUE                                _DB_GAIN_1_8_DB   // For _DB_GAIN Mode

#undef _DP_VOLUME_STEP_SIZE_VALUE
#define _DP_VOLUME_STEP_SIZE_VALUE                          (0x40 & 0xFF) // For _VOLUME_STEP Mode

#undef _DP_DVC_VOLUME_MUTE_TIMER
#define _DP_DVC_VOLUME_MUTE_TIMER                           400 // ms

#undef _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT
#define _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT                 _OFF

#undef _FIX_SAMPLING_FREQ_TYPE
#define _FIX_SAMPLING_FREQ_TYPE                             _FIX_FREQ_48KHZ

#undef _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE
#define _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE       _OFF

#undef _NO_MUTE_LINE_IN_AUDIO_WHILE_SWITCHING_DIGITAL_PORT
#define _NO_MUTE_LINE_IN_AUDIO_WHILE_SWITCHING_DIGITAL_PORT _OFF

#undef _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT
#define _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT                 _OFF

#undef _LINE_IN_HARD_GAIN_VALUE
#define _LINE_IN_HARD_GAIN_VALUE                            _HARD_GAIN_0_DB

#undef _DIGITAL_HARD_GAIN_VALUE
#define _DIGITAL_HARD_GAIN_VALUE                            _HARD_GAIN_0_DB

#undef _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT
#define _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT         _OFF

#undef _DIGITAL_AUDIO_OUTPUT_FIX_I2S_PHASE_DELAY
#define _DIGITAL_AUDIO_OUTPUT_FIX_I2S_PHASE_DELAY           _OFF

#undef _AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT
#define _AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT            _OFF

#undef _INTERNAL_AUDIO_TEST_SUPPORT
#define _INTERNAL_AUDIO_TEST_SUPPORT                        _OFF

#endif

//--------------------------------------------------
// HDMI2.0 YCbCr420 Option
//--------------------------------------------------
#if(_HDMI_2_0_SUPPORT == _ON)

#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RLE0779_SERIES))
#define _HDMI_2_0_YCBCR420_SUPPORT                          _ON
#else
#define _HDMI_2_0_YCBCR420_SUPPORT                          _OFF
#endif

#else

#define _HDMI_2_0_YCBCR420_SUPPORT                          _OFF

#endif

//--------------------------------------------------
// TMDS Support Macro Option
//--------------------------------------------------
#if(_D0_TMDS_SUPPORT == _ON)
#define _D0_INPUT_PORT_TMDS_MAC_PAGE                        _D0_TMDS_MAC_USE
#else
#define _D0_INPUT_PORT_TMDS_MAC_PAGE                        _PAGE_NONE
#endif

#if(_D1_TMDS_SUPPORT == _ON)
#define _D1_INPUT_PORT_TMDS_MAC_PAGE                        _D1_TMDS_MAC_USE
#else
#define _D1_INPUT_PORT_TMDS_MAC_PAGE                        _PAGE_NONE
#endif

#if(_D2_TMDS_SUPPORT == _ON)
#define _D2_INPUT_PORT_TMDS_MAC_PAGE                        _D2_TMDS_MAC_USE
#else
#define _D2_INPUT_PORT_TMDS_MAC_PAGE                        _PAGE_NONE
#endif

#if(_D3_TMDS_SUPPORT == _ON)
#define _D3_INPUT_PORT_TMDS_MAC_PAGE                        _D3_TMDS_MAC_USE
#else
#define _D3_INPUT_PORT_TMDS_MAC_PAGE                        _PAGE_NONE
#endif

#if(_D4_TMDS_SUPPORT == _ON)
#define _D4_INPUT_PORT_TMDS_MAC_PAGE                        _D4_TMDS_MAC_USE
#else
#define _D4_INPUT_PORT_TMDS_MAC_PAGE                        _PAGE_NONE
#endif

#if(_D5_TMDS_SUPPORT == _ON)
#define _D5_INPUT_PORT_TMDS_MAC_PAGE                        _D5_TMDS_MAC_USE
#else
#define _D5_INPUT_PORT_TMDS_MAC_PAGE                        _PAGE_NONE
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE2) + (_D1_TMDS_MAC_USE == _PAGE2) + (_D2_TMDS_MAC_USE == _PAGE2) +\
    (_D3_TMDS_MAC_USE == _PAGE2) + (_D4_TMDS_MAC_USE == _PAGE2) + (_D5_TMDS_MAC_USE == _PAGE2)) >= 2)
#define _TMDS_PAGE2_COMBO_EXIST                             _ON
#else
#define _TMDS_PAGE2_COMBO_EXIST                             _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE70) + (_D1_TMDS_MAC_USE == _PAGE70) + (_D2_TMDS_MAC_USE == _PAGE70) +\
    (_D3_TMDS_MAC_USE == _PAGE70) + (_D4_TMDS_MAC_USE == _PAGE70) + (_D5_TMDS_MAC_USE == _PAGE70)) >= 2)
#define _TMDS_PAGE70_COMBO_EXIST                            _ON
#else
#define _TMDS_PAGE70_COMBO_EXIST                            _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE71) + (_D1_TMDS_MAC_USE == _PAGE71) + (_D2_TMDS_MAC_USE == _PAGE71) +\
    (_D3_TMDS_MAC_USE == _PAGE71) + (_D4_TMDS_MAC_USE == _PAGE71) + (_D5_TMDS_MAC_USE == _PAGE71)) >= 2)
#define _TMDS_PAGE71_COMBO_EXIST                            _ON
#else
#define _TMDS_PAGE71_COMBO_EXIST                            _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE72) + (_D1_TMDS_MAC_USE == _PAGE72) + (_D2_TMDS_MAC_USE == _PAGE72) +\
    (_D3_TMDS_MAC_USE == _PAGE72) + (_D4_TMDS_MAC_USE == _PAGE72) + (_D5_TMDS_MAC_USE == _PAGE72)) >= 2)
#define _TMDS_PAGE72_COMBO_EXIST                            _ON
#else
#define _TMDS_PAGE72_COMBO_EXIST                            _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE73) + (_D1_TMDS_MAC_USE == _PAGE73) + (_D2_TMDS_MAC_USE == _PAGE73) +\
    (_D3_TMDS_MAC_USE == _PAGE73) + (_D4_TMDS_MAC_USE == _PAGE73) + (_D5_TMDS_MAC_USE == _PAGE73)) >= 2)
#define _TMDS_PAGE73_COMBO_EXIST                            _ON
#else
#define _TMDS_PAGE73_COMBO_EXIST                            _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE74) + (_D1_TMDS_MAC_USE == _PAGE74) + (_D2_TMDS_MAC_USE == _PAGE74) +\
    (_D3_TMDS_MAC_USE == _PAGE74) + (_D4_TMDS_MAC_USE == _PAGE74) + (_D5_TMDS_MAC_USE == _PAGE74)) >= 2)
#define _TMDS_PAGE74_COMBO_EXIST                            _ON
#else
#define _TMDS_PAGE74_COMBO_EXIST                            _OFF
#endif

#if((_TMDS_PAGE2_COMBO_EXIST == _ON) || (_TMDS_PAGE70_COMBO_EXIST == _ON) || (_TMDS_PAGE71_COMBO_EXIST == _ON) ||\
    (_TMDS_PAGE72_COMBO_EXIST == _ON) || (_TMDS_PAGE73_COMBO_EXIST == _ON) || (_TMDS_PAGE74_COMBO_EXIST == _ON))
#define _TMDS_COMBO_EXIST                                   _ON
#else
#define _TMDS_COMBO_EXIST                                   _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE2)))
#define _HDMI_MAC_PAGE2_USE                                 _ON
#else
#define _HDMI_MAC_PAGE2_USE                                 _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE_NONE) && (_D2_TMDS_MAC_USE == _PAGE71))) // RL6432 D1 is special case)
#define _HDMI_MAC_PAGE71_USE                                _ON
#else
#define _HDMI_MAC_PAGE71_USE                                _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE72)))
#define _HDMI_MAC_PAGE72_USE                                _ON
#else
#define _HDMI_MAC_PAGE72_USE                                _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE73)))
#define _HDMI_MAC_PAGE73_USE                                _ON
#else
#define _HDMI_MAC_PAGE73_USE                                _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE74)))
#define _HDMI_MAC_PAGE74_USE                                _ON
#else
#define _HDMI_MAC_PAGE74_USE                                _OFF
#endif

//--------------------------------------------------
// DP Support Macro Option
//--------------------------------------------------
#if(_HW_DP_AUX_ADJR_BIT_WIDTH == 0x05)
#define _DP_AUX_ADJR_DEFAULT_VALUE                          0x01
#elif(_HW_DP_AUX_ADJR_BIT_WIDTH == 0x04)
#define _DP_AUX_ADJR_DEFAULT_VALUE                          0x03
#endif

#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE)

#define _D0_DP_EXIST                                        (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _D1_DP_EXIST                                        (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _D2_DP_EXIST                                        (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)

#define _D0_DP_EXIST                                        (_DP_SUPPORT == _ON)
#define _D1_DP_EXIST                                        _OFF
#define _D2_DP_EXIST                                        _OFF

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)

#define _D0_DP_EXIST                                        (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _D1_DP_EXIST                                        ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
#define _D2_DP_EXIST                                        _OFF

#endif

#if(((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) && (_D0_DP_ASSR_MODE_SUPPORT == _ON)) ||\
    ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2) && (_D0_DP_ASSR_MODE_SUPPORT == _ON)) ||\
    ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL) && ((_D0_DP_ASSR_MODE_SUPPORT == _ON) || (_D1_DP_ASSR_MODE_SUPPORT == _ON) || (_D2_DP_ASSR_MODE_SUPPORT == _ON))))
#define _DP_RX0_ASSR_MODE_SUPPORT                           _ON
#else
#define _DP_RX0_ASSR_MODE_SUPPORT                           _OFF
#endif

#if(((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) && (_D1_DP_ASSR_MODE_SUPPORT == _ON)) ||\
    ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2) && ((_D1_DP_ASSR_MODE_SUPPORT == _ON) || (_D2_DP_ASSR_MODE_SUPPORT == _ON))))
#define _DP_RX1_ASSR_MODE_SUPPORT                           _ON
#else
#define _DP_RX1_ASSR_MODE_SUPPORT                           _OFF
#endif

#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE)

#define _HW_DP_MAC0_INPUT_CLOCK_MAX                         _HW_D0_INPUT_CLOCK_MAX
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                         _HW_D1_INPUT_CLOCK_MAX

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                         _HW_D0_INPUT_CLOCK_MAX
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                         _HW_D1_INPUT_CLOCK_MAX
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                         _HW_D2_INPUT_CLOCK_MAX
#else
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                         _HW_D0_INPUT_CLOCK_MAX
#endif

#define _HW_DP_MAC1_INPUT_CLOCK_MAX                         _INPUT_NONE

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)

#define _HW_DP_MAC0_INPUT_CLOCK_MAX                         _HW_D0_INPUT_CLOCK_MAX

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                         _HW_D1_INPUT_CLOCK_MAX
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                         _HW_D2_INPUT_CLOCK_MAX
#else
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                         _HW_D1_INPUT_CLOCK_MAX
#endif

#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MAC_USE == _PAGEB5)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MAC_USE == _PAGEB5)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_MAC_USE == _PAGEB5)))
#define _DP_MAC_PAGEB5_USE                                  _ON
#else
#define _DP_MAC_PAGEB5_USE                                  _OFF
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MAC_USE == _PAGEB8)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MAC_USE == _PAGEB8)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_MAC_USE == _PAGEB8)))
#define _DP_MAC_PAGEB8_USE                                  _ON
#else
#define _DP_MAC_PAGEB8_USE                                  _OFF
#endif

#if((_DP_SUPPORT == _ON) &&\
    ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) ||\
     (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)))
#if((((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && !((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))) +\
     ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && !((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))) +\
     ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT))) == 0)
#undef _DP_IRQ_HPD_MODE
#define _DP_IRQ_HPD_MODE                                    _DP_IRQ_HPD_PD_MODE
#endif
#endif


//--------------------------------------------------
// DP Not Support Close DP Related Macro Option
//--------------------------------------------------
#if(_DP_SUPPORT == _OFF)

#undef _OVERSCAN_DP_SUPPORT
#define _OVERSCAN_DP_SUPPORT                                _OFF

#undef _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE             SEC(3)

#undef _SOURCE_DP_SWITCH_TIMEOUT_TIME
#define _SOURCE_DP_SWITCH_TIMEOUT_TIME                      SEC(4)

#undef _DP_MST_SUPPORT
#define _DP_MST_SUPPORT                                     _OFF

#undef _DP_TX_SUPPORT
#define _DP_TX_SUPPORT                                      _OFF

#undef _DP_FREESYNC_SUPPORT
#define _DP_FREESYNC_SUPPORT                                _OFF

#undef _DP_ADAPTIVESYNC_SUPPORT
#define _DP_ADAPTIVESYNC_SUPPORT                            _OFF

#undef _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK
#define _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK                  _OFF

#undef _DP_HBR2_MARGIN_LINK_SUPPORT
#define _DP_HBR2_MARGIN_LINK_SUPPORT                        _OFF

#undef _DP_LT_TP2_RETRY_FOR_S2P1_S3P0
#define _DP_LT_TP2_RETRY_FOR_S2P1_S3P0                      _OFF

#undef _DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL
#define _DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL            _OFF

#undef _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT
#define _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT                    _OFF

#undef _D0_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                             _OFF

#undef _D1_DP_MST_PORT_SUPPORT
#define _D1_DP_MST_PORT_SUPPORT                             _OFF

#undef _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT
#define _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT                  _OFF

#undef _DP_DVC_ADJUST_TYPE
#define _DP_DVC_ADJUST_TYPE                                 _DB_GAIN

#undef _DP_DB_GAIN_DOWN_VALUE
#define _DP_DB_GAIN_DOWN_VALUE                              _DB_GAIN_1_8_DB   // For _DB_GAIN Mode

#undef _DP_DB_GAIN_UP_VALUE
#define _DP_DB_GAIN_UP_VALUE                                _DB_GAIN_1_8_DB   // For _DB_GAIN Mode

#undef _DP_VOLUME_STEP_SIZE_VALUE
#define _DP_VOLUME_STEP_SIZE_VALUE                          (0x40 & 0xFF) // For _VOLUME_STEP Mode

#undef _DP_DVC_VOLUME_MUTE_TIMER
#define _DP_DVC_VOLUME_MUTE_TIMER                           400 // ms

#undef _DP_DELL_D3_TEST_SUPPORT
#define _DP_DELL_D3_TEST_SUPPORT                            _OFF

#undef _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT
#define _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT                _OFF

#undef _DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT
#define _DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT             _COLOR_DEPTH_8_BITS

#undef _DP_SINK_VER11_OUI_SUPPORT
#define _DP_SINK_VER11_OUI_SUPPORT                          _OFF

#undef _DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT
#define _DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT           _OFF

#undef _DP_HDCP14_REPEATER_BIT_DISABLE_FOR_TX_CLONE_OFF
#define _DP_HDCP14_REPEATER_BIT_DISABLE_FOR_TX_CLONE_OFF    _OFF

#undef _DP_SINK_RTK_IEEE_OUI_L
#define _DP_SINK_RTK_IEEE_OUI_L                             0x00

#undef _DP_SINK_RTK_IEEE_OUI_M
#define _DP_SINK_RTK_IEEE_OUI_M                             0xE0

#undef _DP_SINK_RTK_IEEE_OUI_H
#define _DP_SINK_RTK_IEEE_OUI_H                             0x4C

#undef _DP_SINK_RTK_ID_STRING_0
#define _DP_SINK_RTK_ID_STRING_0                            0x44

#undef _DP_SINK_RTK_ID_STRING_1
#define _DP_SINK_RTK_ID_STRING_1                            0x70

#undef _DP_SINK_RTK_ID_STRING_2
#define _DP_SINK_RTK_ID_STRING_2                            0x31

#undef _DP_SINK_RTK_ID_STRING_3
#define _DP_SINK_RTK_ID_STRING_3                            0x2E

#undef _DP_SINK_RTK_ID_STRING_4
#define _DP_SINK_RTK_ID_STRING_4                            0x32

#undef _DP_SINK_RTK_ID_STRING_5
#define _DP_SINK_RTK_ID_STRING_5                            0x00

#undef _DP_SINK_RTK_HW_VERSION
#define _DP_SINK_RTK_HW_VERSION                             0x00

#undef _DP_SINK_RTK_FW_VERSION_H
#define _DP_SINK_RTK_FW_VERSION_H                           0x00

#undef _DP_SINK_RTK_FW_VERSION_L
#define _DP_SINK_RTK_FW_VERSION_L                           0x00

#undef _DP_BRANCH_RTK_IEEE_OUI_L
#define _DP_BRANCH_RTK_IEEE_OUI_L                           0x00

#undef _DP_BRANCH_RTK_IEEE_OUI_M
#define _DP_BRANCH_RTK_IEEE_OUI_M                           0xE0

#undef _DP_BRANCH_RTK_IEEE_OUI_H
#define _DP_BRANCH_RTK_IEEE_OUI_H                           0x4C

#undef _DP_BRANCH_RTK_ID_STRING_0
#define _DP_BRANCH_RTK_ID_STRING_0                          0x44

#undef _DP_BRANCH_RTK_ID_STRING_1
#define _DP_BRANCH_RTK_ID_STRING_1                          0x70

#undef _DP_BRANCH_RTK_ID_STRING_2
#define _DP_BRANCH_RTK_ID_STRING_2                          0x31

#undef _DP_BRANCH_RTK_ID_STRING_3
#define _DP_BRANCH_RTK_ID_STRING_3                          0x2E

#undef _DP_BRANCH_RTK_ID_STRING_4
#define _DP_BRANCH_RTK_ID_STRING_4                          0x32

#undef _DP_BRANCH_RTK_ID_STRING_5
#define _DP_BRANCH_RTK_ID_STRING_5                          0x00

#undef _DP_BRANCH_RTK_HW_VERSION
#define _DP_BRANCH_RTK_HW_VERSION                           0x00

#undef _DP_BRANCH_RTK_FW_VERSION_H
#define _DP_BRANCH_RTK_FW_VERSION_H                         0x00

#undef _DP_BRANCH_RTK_FW_VERSION_L
#define _DP_BRANCH_RTK_FW_VERSION_L                         0x00

#undef _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER
#define _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER\
                                                            _OFF

#undef _DP_RX_DPCD_TRAINING_AUX_RD_INTERVAL
#define _DP_RX_DPCD_TRAINING_AUX_RD_INTERVAL                (0x00 & 0x7F)

#undef _DP_PORT_DISCONNECT_TERMINATION_AT_HDMI_MODE
#define _DP_PORT_DISCONNECT_TERMINATION_AT_HDMI_MODE\
                                                            _OFF

#undef _D0_DP_Z0_IMPEDANCE_OPTION
#define _D0_DP_Z0_IMPEDANCE_OPTION                          _BY_CONNECTOR

#undef _D1_DP_Z0_IMPEDANCE_OPTION
#define _D1_DP_Z0_IMPEDANCE_OPTION                          _BY_CONNECTOR

#undef _D2_DP_Z0_IMPEDANCE_OPTION
#define _D2_DP_Z0_IMPEDANCE_OPTION                          _BY_CONNECTOR

#undef _DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT
#define _DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT              _OFF

#undef _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2
#define _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2                 _OFF

#undef _DP_RX_MI_DONGLE_SUPPORT
#define _DP_RX_MI_DONGLE_SUPPORT                            _OFF

#undef _DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE
#define _DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE                  _FINE_TUNE_DFE_BY_1_LANE

#undef _DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE
#define _DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE                  _FINE_TUNE_DFE_BY_1_LANE

#undef _D0_DP_ASSR_MODE_SUPPORT
#define _D0_DP_ASSR_MODE_SUPPORT                            _OFF

#undef _D1_DP_ASSR_MODE_SUPPORT
#define _D1_DP_ASSR_MODE_SUPPORT                            _OFF

#undef _D2_DP_ASSR_MODE_SUPPORT
#define _D2_DP_ASSR_MODE_SUPPORT                            _OFF

#undef _DP_AUX_REPLY_TIMEOUT_BY_USER
#define _DP_AUX_REPLY_TIMEOUT_BY_USER                       _OFF

#undef _DP_AUX_REPLY_TIMEOUT_USER_SETTING
#define _DP_AUX_REPLY_TIMEOUT_USER_SETTING                  0x0D

#undef _DP_AUX_I2C_REPLY_TIMEOUT_SETTING
#define _DP_AUX_I2C_REPLY_TIMEOUT_SETTING                   0x0D

#undef _DP_AUX_REPLY_CLK_SEL_FROM
#define _DP_AUX_REPLY_CLK_SEL_FROM                          _DP_AUX_REPLY_SEL_IOSC

#undef _DP_POWER_OFF_HDCP_SUPPORT
#define _DP_POWER_OFF_HDCP_SUPPORT                          _OFF

#undef _DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT
#define _DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT               _OFF

#undef _DP_RX_INTERLACE_NEW_MODE_SUPPORT
#define _DP_RX_INTERLACE_NEW_MODE_SUPPORT                   _OFF

#undef _DP_IRQ_HPD_MODE
#define _DP_IRQ_HPD_MODE                                    _DP_IRQ_HPD_T2_MODE

#undef _DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT
#define _DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT                   _OFF

#undef _DP_DRR_GET_IVF_TYPE
#define _DP_DRR_GET_IVF_TYPE                                _OFF

#undef _DP_CRC_TEST_VISUAL_CHECK
#define _DP_CRC_TEST_VISUAL_CHECK                           _OFF

#if(_HDMI_SUPPORT == _OFF)
#undef _DP_HDMI_COMPATIBLE_MODE
#define _DP_HDMI_COMPATIBLE_MODE                            _OFF
#endif

#undef _DP_SINK_STREAM_CLK_USING_M_N_TRACKNG
#define _DP_SINK_STREAM_CLK_USING_M_N_TRACKNG               _OFF

#undef _DP_1_1_DOWN_STREAM_PORT_COUNT
#define _DP_1_1_DOWN_STREAM_PORT_COUNT                      0x00

#undef _DP_1_2_DOWN_STREAM_PORT_COUNT
#define _DP_1_2_DOWN_STREAM_PORT_COUNT                      0x00

#undef _DP_1_1_SINK_RTK_IEEE_OUI_L
#define _DP_1_1_SINK_RTK_IEEE_OUI_L                         0x00

#undef _DP_1_1_SINK_RTK_IEEE_OUI_M
#define _DP_1_1_SINK_RTK_IEEE_OUI_M                         0xE0

#undef _DP_1_1_SINK_RTK_IEEE_OUI_H
#define _DP_1_1_SINK_RTK_IEEE_OUI_H                         0x4C

#undef _DP_1_1_SINK_RTK_ID_STRING_0
#define _DP_1_1_SINK_RTK_ID_STRING_0                        0x44

#undef _DP_1_1_SINK_RTK_ID_STRING_1
#define _DP_1_1_SINK_RTK_ID_STRING_1                        0x70

#undef _DP_1_1_SINK_RTK_ID_STRING_2
#define _DP_1_1_SINK_RTK_ID_STRING_2                        0x31

#undef _DP_1_1_SINK_RTK_ID_STRING_3
#define _DP_1_1_SINK_RTK_ID_STRING_3                        0x2E

#undef _DP_1_1_SINK_RTK_ID_STRING_4
#define _DP_1_1_SINK_RTK_ID_STRING_4                        0x31

#undef _DP_1_1_SINK_RTK_ID_STRING_5
#define _DP_1_1_SINK_RTK_ID_STRING_5                        0x00

#undef _DP_1_1_SINK_RTK_HW_VERSION
#define _DP_1_1_SINK_RTK_HW_VERSION                         0x10

#undef _DP_1_1_SINK_RTK_FW_VERSION_H
#define _DP_1_1_SINK_RTK_FW_VERSION_H                       0x01

#undef _DP_1_1_SINK_RTK_FW_VERSION_L
#define _DP_1_1_SINK_RTK_FW_VERSION_L                       0x00

#undef _DP_1_2_SINK_RTK_IEEE_OUI_L
#define _DP_1_2_SINK_RTK_IEEE_OUI_L                         0x00

#undef _DP_1_2_SINK_RTK_IEEE_OUI_M
#define _DP_1_2_SINK_RTK_IEEE_OUI_M                         0xE0

#undef _DP_1_2_SINK_RTK_IEEE_OUI_H
#define _DP_1_2_SINK_RTK_IEEE_OUI_H                         0x4C

#undef _DP_1_2_SINK_RTK_ID_STRING_0
#define _DP_1_2_SINK_RTK_ID_STRING_0                        0x44

#undef _DP_1_2_SINK_RTK_ID_STRING_1
#define _DP_1_2_SINK_RTK_ID_STRING_1                        0x70

#undef _DP_1_2_SINK_RTK_ID_STRING_2
#define _DP_1_2_SINK_RTK_ID_STRING_2                        0x31

#undef _DP_1_2_SINK_RTK_ID_STRING_3
#define _DP_1_2_SINK_RTK_ID_STRING_3                        0x2E

#undef _DP_1_2_SINK_RTK_ID_STRING_4
#define _DP_1_2_SINK_RTK_ID_STRING_4                        0x32

#undef _DP_1_2_SINK_RTK_ID_STRING_5
#define _DP_1_2_SINK_RTK_ID_STRING_5                        0x00

#undef _DP_1_2_SINK_RTK_HW_VERSION
#define _DP_1_2_SINK_RTK_HW_VERSION                         0x10

#undef _DP_1_2_SINK_RTK_FW_VERSION_H
#define _DP_1_2_SINK_RTK_FW_VERSION_H                       0x01

#undef _DP_1_2_SINK_RTK_FW_VERSION_L
#define _DP_1_2_SINK_RTK_FW_VERSION_L                       0x00

#undef _DP_FREESYNC_II_SUPPORT
#define _DP_FREESYNC_II_SUPPORT                             _OFF

#undef _DP_HDR10_SUPPORT
#define _DP_HDR10_SUPPORT                                   _OFF

#undef _DP_HDCP_2_2_SUPPORT
#define _DP_HDCP_2_2_SUPPORT                                _OFF

#undef _DP_HDCP14_CTS_SUPPORT
#define _DP_HDCP14_CTS_SUPPORT                              _OFF

#undef _DP_DPCD_DFP_PRESENT_REF_TO
#define _DP_DPCD_DFP_PRESENT_REF_TO                         _DP_MST_CAPABILITY

#undef _DP_TX_SSC_SUPPORT
#define _DP_TX_SSC_SUPPORT                                  _OFF

#undef _DP_LINK_RATE_CHANGE_WO_LT_SUPPORT
#define _DP_LINK_RATE_CHANGE_WO_LT_SUPPORT                  _OFF

#undef _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI
#define _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI\
                                                            _OFF

#undef _DP_LT_TP1_TP2_S2P0_PERMIT_PASS
#define _DP_LT_TP1_TP2_S2P0_PERMIT_PASS                     _OFF

#undef _DP_MST_CAP_ON_TO_OFF_NO_HPD
#define _DP_MST_CAP_ON_TO_OFF_NO_HPD                        _OFF

#undef _DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW
#define _DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW                _OFF

#undef _DP_TX_CONFIG_BY_USER_SUPPORT
#define _DP_TX_CONFIG_BY_USER_SUPPORT                       _OFF

#undef _DP_MST_AUTO_SEARCH_SUPPORT
#define _DP_MST_AUTO_SEARCH_SUPPORT                         _OFF

#undef _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX
#define _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX           4

#undef _DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT
#define _DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT           _OFF

#undef _DP_1_4_SINK_RTK_IEEE_OUI_L
#define _DP_1_4_SINK_RTK_IEEE_OUI_L                         0x00

#undef _DP_1_4_SINK_RTK_IEEE_OUI_M
#define _DP_1_4_SINK_RTK_IEEE_OUI_M                         0xE0

#undef _DP_1_4_SINK_RTK_IEEE_OUI_H
#define _DP_1_4_SINK_RTK_IEEE_OUI_H                         0x4C

#undef _DP_1_4_SINK_RTK_ID_STRING_0
#define _DP_1_4_SINK_RTK_ID_STRING_0                        0x44

#undef _DP_1_4_SINK_RTK_ID_STRING_1
#define _DP_1_4_SINK_RTK_ID_STRING_1                        0x70

#undef _DP_1_4_SINK_RTK_ID_STRING_2
#define _DP_1_4_SINK_RTK_ID_STRING_2                        0x31

#undef _DP_1_4_SINK_RTK_ID_STRING_3
#define _DP_1_4_SINK_RTK_ID_STRING_3                        0x2E

#undef _DP_1_4_SINK_RTK_ID_STRING_4
#define _DP_1_4_SINK_RTK_ID_STRING_4                        0x34

#undef _DP_1_4_SINK_RTK_ID_STRING_5
#define _DP_1_4_SINK_RTK_ID_STRING_5                        0x00

#undef _DP_1_4_SINK_RTK_HW_VERSION
#define _DP_1_4_SINK_RTK_HW_VERSION                         0x20

#undef _DP_1_4_SINK_RTK_FW_VERSION_H
#define _DP_1_4_SINK_RTK_FW_VERSION_H                       0x01

#undef _DP_1_4_SINK_RTK_FW_VERSION_L
#define _DP_1_4_SINK_RTK_FW_VERSION_L                       0x00

#undef _DP_1_1_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_L                       0x00

#undef _DP_1_1_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_M                       0xE0

#undef _DP_1_1_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_H                       0x4C

#undef _DP_1_1_BRANCH_RTK_ID_STRING_0
#define _DP_1_1_BRANCH_RTK_ID_STRING_0                      0x44

#undef _DP_1_1_BRANCH_RTK_ID_STRING_1
#define _DP_1_1_BRANCH_RTK_ID_STRING_1                      0x70

#undef _DP_1_1_BRANCH_RTK_ID_STRING_2
#define _DP_1_1_BRANCH_RTK_ID_STRING_2                      0x31

#undef _DP_1_1_BRANCH_RTK_ID_STRING_3
#define _DP_1_1_BRANCH_RTK_ID_STRING_3                      0x2E

#undef _DP_1_1_BRANCH_RTK_ID_STRING_4
#define _DP_1_1_BRANCH_RTK_ID_STRING_4                      0x31

#undef _DP_1_1_BRANCH_RTK_ID_STRING_5
#define _DP_1_1_BRANCH_RTK_ID_STRING_5                      0x00

#undef _DP_1_1_BRANCH_RTK_HW_VERSION
#define _DP_1_1_BRANCH_RTK_HW_VERSION                       0x20

#undef _DP_1_1_BRANCH_RTK_FW_VERSION_H
#define _DP_1_1_BRANCH_RTK_FW_VERSION_H                     0x01

#undef _DP_1_1_BRANCH_RTK_FW_VERSION_L
#define _DP_1_1_BRANCH_RTK_FW_VERSION_L                     0x00

#undef _DP_1_2_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_L                       0x00

#undef _DP_1_2_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_M                       0xE0

#undef _DP_1_2_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_H                       0x4C

#undef _DP_1_2_BRANCH_RTK_ID_STRING_0
#define _DP_1_2_BRANCH_RTK_ID_STRING_0                      0x44

#undef _DP_1_2_BRANCH_RTK_ID_STRING_1
#define _DP_1_2_BRANCH_RTK_ID_STRING_1                      0x70

#undef _DP_1_2_BRANCH_RTK_ID_STRING_2
#define _DP_1_2_BRANCH_RTK_ID_STRING_2                      0x31

#undef _DP_1_2_BRANCH_RTK_ID_STRING_3
#define _DP_1_2_BRANCH_RTK_ID_STRING_3                      0x2E

#undef _DP_1_2_BRANCH_RTK_ID_STRING_4
#define _DP_1_2_BRANCH_RTK_ID_STRING_4                      0x32

#undef _DP_1_2_BRANCH_RTK_ID_STRING_5
#define _DP_1_2_BRANCH_RTK_ID_STRING_5                      0x00

#undef _DP_1_2_BRANCH_RTK_HW_VERSION
#define _DP_1_2_BRANCH_RTK_HW_VERSION                       0x20

#undef _DP_1_2_BRANCH_RTK_FW_VERSION_H
#define _DP_1_2_BRANCH_RTK_FW_VERSION_H                     0x01

#undef _DP_1_2_BRANCH_RTK_FW_VERSION_L
#define _DP_1_2_BRANCH_RTK_FW_VERSION_L                     0x00

#undef _DP_1_4_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_4_BRANCH_RTK_IEEE_OUI_L                       0x00

#undef _DP_1_4_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_4_BRANCH_RTK_IEEE_OUI_M                       0xE0

#undef _DP_1_4_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_4_BRANCH_RTK_IEEE_OUI_H                       0x4C

#undef _DP_1_4_BRANCH_RTK_ID_STRING_0
#define _DP_1_4_BRANCH_RTK_ID_STRING_0                      0x44

#undef _DP_1_4_BRANCH_RTK_ID_STRING_1
#define _DP_1_4_BRANCH_RTK_ID_STRING_1                      0x70

#undef _DP_1_4_BRANCH_RTK_ID_STRING_2
#define _DP_1_4_BRANCH_RTK_ID_STRING_2                      0x31

#undef _DP_1_4_BRANCH_RTK_ID_STRING_3
#define _DP_1_4_BRANCH_RTK_ID_STRING_3                      0x2E

#undef _DP_1_4_BRANCH_RTK_ID_STRING_4
#define _DP_1_4_BRANCH_RTK_ID_STRING_4                      0x34

#undef _DP_1_4_BRANCH_RTK_ID_STRING_5
#define _DP_1_4_BRANCH_RTK_ID_STRING_5                      0x00

#undef _DP_1_4_BRANCH_RTK_HW_VERSION
#define _DP_1_4_BRANCH_RTK_HW_VERSION                       0x20

#undef _DP_1_4_BRANCH_RTK_FW_VERSION_H
#define _DP_1_4_BRANCH_RTK_FW_VERSION_H                     0x01

#undef _DP_1_4_BRANCH_RTK_FW_VERSION_L
#define _DP_1_4_BRANCH_RTK_FW_VERSION_L                     0x00

#undef _DP_EXTEND_DELAY_TO_REBUILD_PHY
#define _DP_EXTEND_DELAY_TO_REBUILD_PHY                     _OFF

#undef _TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _TYPE_C_EMB_DP_ALT_MODE_SUPPORT                     _OFF

#undef _DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT
#define _DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT              _OFF

#undef _DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT
#define _DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT                _OFF

#undef _DP_TX_HPD_HIGH_DEBOUNCE_SUPPORT
#define _DP_TX_HPD_HIGH_DEBOUNCE_SUPPORT                    _OFF

#else

#if(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
#undef _D0_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                             _OFF
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_DP_PORT)
#undef _D1_DP_MST_PORT_SUPPORT
#define _D1_DP_MST_PORT_SUPPORT                             _OFF
#endif

#endif

#if(_DP_MST_SUPPORT == _OFF)
#undef _DP_MST_TX_FORCE_REBUILD_TOPOLOGY_TIMEOUT
#endif

//--------------------------------------------------
// DP DownStream Count Option
//--------------------------------------------------
#if(_DP_TX_SUPPORT == _OFF)
#undef _DP_1_1_DOWN_STREAM_PORT_COUNT
#undef _DP_1_2_DOWN_STREAM_PORT_COUNT
#define _DP_1_1_DOWN_STREAM_PORT_COUNT                      0x00
#define _DP_1_2_DOWN_STREAM_PORT_COUNT                      0x00
#endif

//--------------------------------------------------
// DP VSC SDP Option
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_HW_DP_VSC_SDP_EXT_CAPABILITY_SUPPORT == _ON) && (_DP_ULTRA_HDR_SUPPORT == _ON))
#define _DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT             _ON
#else
#define _DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT             _OFF
#endif

//--------------------------------------------------
// MHL PS Without Power Cut Option
//--------------------------------------------------
#define _MHL_PS_WITHOUT_POWERCUT_SUPPORT                    _OFF

//--------------------------------------------------
// Type C Embedded Port Controller Not Support Close Type C Embedded Port Controller Related Macro Option
//--------------------------------------------------
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _OFF)
#undef _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX
#define _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX                   _TYPE_C_BILLBOARD_URL_INDEX_DP

#undef _TYPE_C_EMB_LENOVO_ALT_MODE_URL_INDEX
#define _TYPE_C_EMB_LENOVO_ALT_MODE_URL_INDEX               _TYPE_C_BILLBOARD_URL_INDEX_LENOVO

#undef _TYPE_C_EMB_DELL_ALT_MODE_ENTER_TIMEOUT_TIMER
#define _TYPE_C_EMB_DELL_ALT_MODE_ENTER_TIMEOUT_TIMER       30 // 30ms

#undef _TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER
#define _TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER         30 // 30ms

#undef _TYPE_C_EMB_PORT_ROLE
#define _TYPE_C_EMB_PORT_ROLE                               _TYPE_C_PORT_DRP

#undef _TYPE_C_EMB_DRP_PREFER
#define _TYPE_C_EMB_DRP_PREFER                              _TYPE_C_DRP_NO_PREFERENCE

#undef _TYPE_C_EMB_POWER_SOURCE
#define _TYPE_C_EMB_POWER_SOURCE                            _TYPE_C_SELF_POWER_ONLY

#undef _TYPE_C_EMB_VBUS_PROTECT_MODE
#define _TYPE_C_EMB_VBUS_PROTECT_MODE                       _VBUS_PROTECT_BY_KERNEL

#undef _TYPE_C_EMB_PD_VERSION
#define _TYPE_C_EMB_PD_VERSION                              _PD_VERSION_2_0

#undef _TYPE_C_EMB_USB_ROLE
#define _TYPE_C_EMB_USB_ROLE                                _TYPE_C_USB_NOT_SUPPORT

#undef _TYPE_C_EMB_USB_SPEED
#define _TYPE_C_EMB_USB_SPEED                               _TYPE_C_USB_BILLBOARD_ONLY

#undef _TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _TYPE_C_EMB_DP_ALT_MODE_SUPPORT                     _OFF

#undef _TYPE_C_EMB_PD3_PPS_SUPPORT
#define _TYPE_C_EMB_PD3_PPS_SUPPORT                         _OFF

#undef _TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _TYPE_C_EMB_PD3_FRSWAP_SUPPORT                      _OFF

#undef _TYPE_C_EMB_CTS_FORCE_POWER_NORMAL
#define _TYPE_C_EMB_CTS_FORCE_POWER_NORMAL                  _OFF

#undef _TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA
#define _TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA             _FALSE

#undef _TYPE_C_EMB_UFP_PRODUCT_TYPE
#define _TYPE_C_EMB_UFP_PRODUCT_TYPE                        _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT

#undef _TYPE_C_EMB_BRAND_OPTION
#define _TYPE_C_EMB_BRAND_OPTION                            _TYPE_C_EMB_BRAND_NONE

#undef _TYPE_C_EMB_CTS_FLOW
#define _TYPE_C_EMB_CTS_FLOW                                _OFF
#endif

//--------------------------------------------------
// TypeC AC ON RECONNECT Option
//--------------------------------------------------
#if((_TYPE_C_EMB_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_D0_DP_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) && (_TYPE_C_EMB_CTS_FLOW == _OFF))
#define _TYPE_C_CC_AC_ON_RECONNECT                          _ON
#else
#define _TYPE_C_CC_AC_ON_RECONNECT                          _OFF
#endif

//--------------------------------------------------
// TypeC Alt Mode Support Option
//--------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define _TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT           ((_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))
#endif

#if(_DP_SUPPORT == _OFF)
#undef _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX
#define _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX                   _TYPE_C_BILLBOARD_URL_INDEX_DP
#endif

//--------------------------------------------------
// Billboard String Dp Option (if Support ON, Users Have To Provide DP String Table)
//--------------------------------------------------
#if(_DP_SUPPORT == _OFF)
#undef _USER_TYPE_C_BB_STRING_DP_SUPPORT
#define _USER_TYPE_C_BB_STRING_DP_SUPPORT                   _OFF
#endif

//--------------------------------------------------
// Low Power FW Flow Option
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6463_SERIES) || (_SCALER_TYPE == _RL6851_SERIES))
#define _SYSTEM_LOW_POWER_GEN                               _POWER_FLOW_GEN_2
#else
#define _SYSTEM_LOW_POWER_GEN                               _POWER_FLOW_GEN_1
#endif

//--------------------------------------------------
// Watch Dog Timer Event Option
//--------------------------------------------------
#if((_HDMI_2_0_SUPPORT == _ON) ||\
    (_MHL_3_0_SUPPORT == _ON) ||\
    (_DP_SUPPORT == _ON) ||\
    (_HDCP_2_2_SUPPORT == _ON) ||\
    ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
#define _WD_TIMER_INT_SUPPORT                               _ON
#else
#define _WD_TIMER_INT_SUPPORT                               _OFF
#endif

//--------------------------------------------------
// Record Timer Option
//--------------------------------------------------
#if(_MHL_3_0_SUPPORT == _ON)
#define _RECORD_TIMER_SUPPORT                               _ON
#else
#define _RECORD_TIMER_SUPPORT                               _OFF
#endif

//--------------------------------------------------
// Timer Event ID Enumeration & Structure
//--------------------------------------------------
#include _USER_TIMER_INCLUDE

typedef enum
{
    _SCALER_TIMER_EVENT_INVALID = 0x00,

#include _USER_TIMER_EVENT_ID_INCLUDE
    _USER_TIMER_EVENT_END,

#include "TimerEventIDSystem.h"
    _SYSTEM_TIMER_EVENT_END,

#include "TimerEventIDScaler.h"
    _SCALER_TIMER_EVENT_END,
} EnumScalerTimerEventID;

typedef struct
{
    EnumScalerTimerEventID enumEventID;
    WORD usTime;
} StructTimerEventTableType;

//--------------------------------------------------
// HW IIC Speed Parameters Enumeration & Structure
//--------------------------------------------------
#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
#include _USER_HWIIC_INCLUDE
#endif

typedef enum
{
    _KERNAL_PAR_100K = 0x00,
    _KERNAL_PAR_400K,

#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
// Incldue User Paramters Type
#include _USER_HW_IIC_PAR_TYPE
#endif
}EnumHWIICParType;

//****************************************************************************
// HW IIC Speed Parameters Structure
//****************************************************************************
typedef struct
{
    BYTE ucSLPC_14318K;
    BYTE ucSHPC_14318K;
    BYTE ucSLPC_28000K;
    BYTE ucSHPC_28000K;
    BYTE ucSTA_SUGPIO_C;
    BYTE ucTOR;
    BYTE ucFTPC;
    BYTE ucFD10_14318K;
    BYTE ucFD10_28000K;
} StructHwI2cSettingData;

//--------------------------------------------------
// Timer Event Count
//--------------------------------------------------
#if((_HP_SOURCE_SCAN_SUPPORT == _ON) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE))
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT                    5
#else
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT                    4
#endif

#if(_DP_SUPPORT == _ON)
#define _SCALER_DP_EVENT_COUNT                              (6 + _DP_RX_MI_DONGLE_SUPPORT)
#define _BACKGROUND_FW_UPDATE_DPRX_EVENT_COUNT              1
#else
#define _SCALER_DP_EVENT_COUNT                              0
#define _BACKGROUND_FW_UPDATE_DPRX_EVENT_COUNT              0
#endif

#if(_DP_MST_SUPPORT == _ON)
#define _SCALER_DP_MST_EVENT_COUNT                          (3 + _DP_PORT_VALID)
#else
#define _SCALER_DP_MST_EVENT_COUNT                          0
#endif

#if(_DP_TX_SUPPORT == _ON)
#define _SCALER_DP_TX_EVENT_COUNT                           3
#define _BACKGROUND_FW_UPDATE_DPTX_EVENT_COUNT              1
#else
#define _SCALER_DP_TX_EVENT_COUNT                           0
#define _BACKGROUND_FW_UPDATE_DPTX_EVENT_COUNT              0
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#define _RX0_MHL_SCALER_EVENT_COUNT                         3
#else
#define _RX0_MHL_SCALER_EVENT_COUNT                         0
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#define _RX1_MHL_SCALER_EVENT_COUNT                         3
#else
#define _RX1_MHL_SCALER_EVENT_COUNT                         0
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#define _RX2_MHL_SCALER_EVENT_COUNT                         3
#else
#define _RX2_MHL_SCALER_EVENT_COUNT                         0
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#define _RX3_MHL_SCALER_EVENT_COUNT                         3
#else
#define _RX3_MHL_SCALER_EVENT_COUNT                         0
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define _RX4_MHL_SCALER_EVENT_COUNT                         3
#else
#define _RX4_MHL_SCALER_EVENT_COUNT                         0
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
#define _RX5_MHL_SCALER_EVENT_COUNT                         3
#else
#define _RX5_MHL_SCALER_EVENT_COUNT                         0
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define _BACKGROUND_FW_UPDATE_TYPEC_EVENT_COUNT             1
#else
#define _BACKGROUND_FW_UPDATE_TYPEC_EVENT_COUNT             0
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#define _BACKGROUND_FW_UPDATE_MCCS_EVENT_COUNT              1
#else
#define _BACKGROUND_FW_UPDATE_MCCS_EVENT_COUNT              0
#endif


#if(_SMBUS_BLOCK_READ_WRITE_COMMAND_SUPPORT == _ON)
#define _SCALER_SMBUS_BLOCK_PROTOCOL_EVENT_COUNT            1
#else
#define _SCALER_SMBUS_BLOCK_PROTOCOL_EVENT_COUNT            0
#endif

#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)
#define _BACKGROUND_FW_UPDATE_HDCP_EVENT_COUNT              1
#define _SCALER_BACKGROUND_FW_UPDATE_EVENT_COUNT            (_BACKGROUND_FW_UPDATE_HDCP_EVENT_COUNT + _BACKGROUND_FW_UPDATE_TYPEC_EVENT_COUNT +\
                                                             _BACKGROUND_FW_UPDATE_DPRX_EVENT_COUNT + _BACKGROUND_FW_UPDATE_DPTX_EVENT_COUNT +\
                                                             _BACKGROUND_FW_UPDATE_MCCS_EVENT_COUNT)
#else
#define _SCALER_BACKGROUND_FW_UPDATE_EVENT_COUNT            0
#endif

#define _SIMULTANEOUS_SCALER_EVENT_COUNT                    (_SCALER_DP_EVENT_COUNT + _SCALER_DP_MST_EVENT_COUNT + _SCALER_DP_TX_EVENT_COUNT +\
                                                             _RX0_MHL_SCALER_EVENT_COUNT + _RX1_MHL_SCALER_EVENT_COUNT +\
                                                             _RX2_MHL_SCALER_EVENT_COUNT + _RX3_MHL_SCALER_EVENT_COUNT +\
                                                             _RX4_MHL_SCALER_EVENT_COUNT + _RX5_MHL_SCALER_EVENT_COUNT +\
                                                             _SCALER_SMBUS_BLOCK_PROTOCOL_EVENT_COUNT + _SCALER_BACKGROUND_FW_UPDATE_EVENT_COUNT)

#define _TIMER_EVENT_COUNT                                  (_SIMULTANEOUS_USER_EVENT_COUNT + _SIMULTANEOUS_SYSTEM_EVENT_COUNT + _SIMULTANEOUS_SCALER_EVENT_COUNT)

//--------------------------------------------------
// M2PLL is 243M
// Enumerations of Flash / MCU Speed
// Power Normal:           Flash = 40.5M,  MCU = 81M
// Power Normal Flash Low Speed:
//                         Flash = 20.25M, MCU = 40.5M
//
// M2PLL is 351M
// Enumerations of Flash / MCU Speed
// Power Normal:           Flash = 44M,    MCU = 88M
// Power Normal Flash Low Speed:
//                         Flash = 22M,    MCU = 44M
//
// Power Sav/Down 27:      Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Saving DP:        Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Saving Precision: Flash = 14.318M,  MCU = 14.318M
// Power Initial:       Flash = 14.3M,  MCU = 14.3M
//--------------------------------------------------
typedef enum
{
#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_3,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_6,
    _FLASH_CLK_FAST_DIV = _DIV_3,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else

#if(_CACHE_PS_SWITCH == _ENABLE)
    _FLASH_CLK_PS_DIV = _DIV_1,
#elif(_CACHE_PS_SWITCH == _DISABLE)
    _FLASH_CLK_PS_DIV = _DIV_4,
#endif

#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M) // Else Of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_MCU_SPEED_UP_SUPPORT == _ON)
#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_2,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
    _FLASH_CLK_FAST_DIV = _DIV_2,
#endif

#else

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_8,
    _FLASH_CLK_FAST_DIV = _DIV_4,
#endif

#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M) // Else Of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_8,
    _FLASH_CLK_FAST_DIV = _DIV_4,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_200M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_2,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
    _FLASH_CLK_FAST_DIV = _DIV_2,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_189M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_2,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
    _FLASH_CLK_FAST_DIV = _DIV_2,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif

#endif // End of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SOURCE == _FLASH_IOSC_CLK)
    _FLASH_CLK_IN_DIV = _DIV_2,
    _FLASH_CLK_PS_FAST_DIV = _DIV_1,
#else
    _FLASH_CLK_IN_DIV = _DIV_1,
    _FLASH_CLK_PS_FAST_DIV = _DIV_1, // for DP
#endif
} EnumFlashClkDiv;

typedef enum
{
    _FLASH_2_CLK_IN_DIV = _DIV_1,

#if(_MCU_SPEED_UP_SUPPORT == _ON)
    _FLASH_2_CLK_DIV = _DIV_4,
#else
    _FLASH_2_CLK_DIV = _DIV_2,
#endif

#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_CACHE_PS_SWITCH == _ENABLE)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#elif(_CACHE_PS_SWITCH == _DISABLE)
    _FLASH_2_CLK_PS_DIV = _DIV_1,
#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_200M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_189M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#endif

} EnumFlash2ClkDiv;

typedef enum
{
    _MCU_CLK_DIV = _DIV_1,
#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_200M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_189M)
    _MCU_CLK_PS_DIV = _DIV_1,
#endif

    _MCU_CLK_IN_DIV = _DIV_1,
} EnumMcuClkDiv;

typedef enum
{
    _IOSC_DELAY6US_CNT = 3, // Using IOSC/XTAL/M2PLL CLK To Get base 6us delay on the counter
    _IOSC_DELAY4US_CNT = 6, // Using IOSC/XTAL/M2PLL CLK To Get base Xus delay on the counter
    _XTAL_DELAY6US_CNT = 2,
    _XTAL_DELAY4US_CNT = 2,

#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)
    _M2PLL_DELAY6US_CNT = 23,
    _M2PLL_DELAY4US_CNT = 19,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
#if(_MCU_SPEED_UP_SUPPORT == _ON)
    _M2PLL_DELAY6US_CNT = 53,
    _M2PLL_DELAY4US_CNT = 44,
#else
    _M2PLL_DELAY6US_CNT = 26,
    _M2PLL_DELAY4US_CNT = 21,
#endif
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)
    _M2PLL_DELAY6US_CNT = 28,
    _M2PLL_DELAY4US_CNT = 22,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_200M)
    _M2PLL_DELAY6US_CNT = 20,
    _M2PLL_DELAY4US_CNT = 15,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_189M)
    _M2PLL_DELAY6US_CNT = 28,
    _M2PLL_DELAY4US_CNT = 22,
#endif
}EnumDelay5usTuneCnt;

//--------------------------------------------------
// Timer 0/1 Max Delay Timer(MS)
//--------------------------------------------------
#if(_MCU_SPEED_UP_SUPPORT == _ON)
#define _TIMER01_STEP_TIME_MS                               4
#else
#define _TIMER01_STEP_TIME_MS                               8
#endif

//--------------------------------------------------
// Urgent Event Check Mode
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) || (_HDCP_2_2_SUPPORT == _ON))
#undef _URGENT_EVENT_CHECK_MODE
#define _URGENT_EVENT_CHECK_MODE                            _ON
#else
#undef _URGENT_EVENT_CHECK_MODE
#define _URGENT_EVENT_CHECK_MODE                            _OFF
#endif

//--------------------------------------------------
// DP HPD Implementation Mode
//--------------------------------------------------
#if((_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) || (_DP_MST_AUTO_SEARCH_SUPPORT == _ON) || (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
#define _DP_LONG_HPD_MODE                                   _DP_LONG_HPD_TIMEREVENT_MODE
#else
#define _DP_LONG_HPD_MODE                                   _DP_LONG_HPD_DELAY_MODE
#endif

#endif // End of #ifndef __SCALER_OPTION_H__
