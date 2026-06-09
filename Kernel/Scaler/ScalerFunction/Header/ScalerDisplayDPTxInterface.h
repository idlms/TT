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
// ID Code      : ScalerDisplayDPTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

#if(_PANEL_DPTX_HPD_DETECT == _ON)
#define GET_DISPLAY_DP_TX1_FORCE_TO_LT()                            (g_bDisplayDpTx1ForceLT)
#define SET_DISPLAY_DP_TX1_FORCE_TO_LT()                            (g_bDisplayDpTx1ForceLT = _TRUE)
#define CLR_DISPLAY_DP_TX1_FORCE_TO_LT()                            (g_bDisplayDpTx1ForceLT = _FALSE)
#endif



#if(_PANEL_DPTX_HPD_DETECT == _ON)
#define GET_DISPLAY_DP_TX2_FORCE_TO_LT()                            (g_bDisplayDpTx2ForceLT)
#define SET_DISPLAY_DP_TX2_FORCE_TO_LT()                            (g_bDisplayDpTx2ForceLT = _TRUE)
#define CLR_DISPLAY_DP_TX2_FORCE_TO_LT()                            (g_bDisplayDpTx2ForceLT = _FALSE)
#endif


#if(_PANEL_DPTX_HPD_DETECT == _ON)
#if((_DISPLAY_DP_TX_PORT_1 == _ON) && (_DISPLAY_DP_TX_PORT_2 == _ON))
#define GET_DISPLAY_DP_TX_FORCE_TO_LT()                             ((GET_DISPLAY_DP_TX1_FORCE_TO_LT() == _TRUE) || (GET_DISPLAY_DP_TX2_FORCE_TO_LT() == _TRUE))
#define CLR_DISPLAY_DP_TX_FORCE_TO_LT()                             {\
                                                                        CLR_DISPLAY_DP_TX1_FORCE_TO_LT();\
                                                                        CLR_DISPLAY_DP_TX2_FORCE_TO_LT();\
                                                                    }
#elif(_DISPLAY_DP_TX_PORT_1 == _ON)
#define GET_DISPLAY_DP_TX_FORCE_TO_LT()                             (GET_DISPLAY_DP_TX1_FORCE_TO_LT() == _TRUE)
#define CLR_DISPLAY_DP_TX_FORCE_TO_LT()                             {\
                                                                        CLR_DISPLAY_DP_TX1_FORCE_TO_LT();\
                                                                    }
#elif(_DISPLAY_DP_TX_PORT_2 == _ON)
#define GET_DISPLAY_DP_TX_FORCE_TO_LT()                             (GET_DISPLAY_DP_TX2_FORCE_TO_LT() == _TRUE)
#define CLR_DISPLAY_DP_TX_FORCE_TO_LT()                             {\
                                                                        CLR_DISPLAY_DP_TX2_FORCE_TO_LT();\
                                                                    }
#endif
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

#if(_PANEL_DPTX_HPD_DETECT == _ON)
extern volatile bit g_bDisplayDpTx1ForceLT;
#endif



#if(_PANEL_DPTX_HPD_DETECT == _ON)
extern volatile bit g_bDisplayDpTx2ForceLT;
#endif


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayDPTxAnalogPhyConrol(bit bEnable);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
extern bit ScalerDisplayDPTxStableDetect(void);
#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
void ScalerDisplayDPTxIrqIntHandler_EXINT0(void);
#endif
#endif


