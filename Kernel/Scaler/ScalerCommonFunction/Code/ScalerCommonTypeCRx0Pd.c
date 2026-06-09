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
// ID Code      : ScalerCommonTypeCRx0Pd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

#if(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN2)
#warning "USB3 Gen2 is NOT Avaliable right now ! ! !"
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _PD_FW_DEBUG                                _OFF

// Status Setting Macros
#define GET_PD_RX0_FW_STATE()                       (g_stPdRx0Status.ucPDState)
#define SET_PD_RX0_FW_STATE(x)                      (g_stPdRx0Status.ucPDState = (x))

#define GET_PD_RX0_SUB_STATE()                      (g_stPdRx0Status.ucPDSubState)
#define SET_PD_RX0_SUB_STATE(x)                     (g_stPdRx0Status.ucPDSubState = (x))

#define GET_PD_RX0_CBL_STATE()                      (g_stPdRx0CableInfo.b4CableState)
#define SET_PD_RX0_CBL_STATE(x)                     (g_stPdRx0CableInfo.b4CableState = (x))

#define GET_PD_RX0_DP_ALT_STATE()                   (g_stPdRx0Status.b6PDDpAltState)
#define SET_PD_RX0_DP_ALT_STATE(x)                  (g_stPdRx0Status.b6PDDpAltState = (x))

#define GET_PD_RX0_LENOVO_ALT_STATE()               (g_stPdRx0Status.b6PDLenovoAltState)
#define SET_PD_RX0_LENOVO_ALT_STATE(x)              (g_stPdRx0Status.b6PDLenovoAltState = (x))

#define GET_PD_RX0_AMS_STATUS()                     (g_stPdRx0Status.b2PDAmsStatus)
#define SET_PD_RX0_AMS_STATUS(x)                    (g_stPdRx0Status.b2PDAmsStatus = (x))

#define GET_PD_RX0_EXPLICIT_CONTRACT()              (g_stPdRx0Status.b1PDPowerContract)
#define SET_PD_RX0_EXPLICIT_CONTRACT()              (g_stPdRx0Status.b1PDPowerContract = _TRUE)
#define CLR_PD_RX0_EXPLICIT_CONTRACT()              (g_stPdRx0Status.b1PDPowerContract = _FALSE)

#define GET_PD_RX0_UNCONSTRAIN_POWER()              (g_stPdRx0Status.b1UnconstrainedPower)
#define SET_PD_RX0_UNCONSTRAIN_POWER(x)             (g_stPdRx0Status.b1UnconstrainedPower = (x))

// Role Setting Macro
#define GET_PD_RX0_POWER_ROLE()                     (BYTE)(g_stPdRx0Status.b1PDPowerRole)
#define SET_PD_RX0_POWER_ROLE(x)                    (g_stPdRx0Status.b1PDPowerRole = (x))

#define GET_PD_RX0_DATA_ROLE()                      (BYTE)(g_stPdRx0Status.b1PDDataRole)
#define SET_PD_RX0_DATA_ROLE(x)                     (g_stPdRx0Status.b1PDDataRole = (x))

#define GET_PD_RX0_VCONN_ROLE()                     (BYTE)(g_stPdRx0Status.b1PDVconnRole)
#define SET_PD_RX0_VCONN_ROLE(x)                    (g_stPdRx0Status.b1PDVconnRole = (x))

#define GET_PD_RX0_SPEC_VER()                       ((BYTE)(g_stPdRx0Status.b2SpecVersion))
#define SET_PD_RX0_SPEC_VER(x)                      (g_stPdRx0Status.b2SpecVersion = (x))

// Cable Info Related Macro
#define GET_PD_RX0_CBL_SPEC_VER()                   ((BYTE)(g_stPdRx0CableInfo.b2CableSpecVer))
#define SET_PD_RX0_CBL_SPEC_VER(x)                  (g_stPdRx0CableInfo.b2CableSpecVer = (x))

#define GET_PD_RX0_CBL_MAX_CUR()                    ((WORD)(g_stPdRx0CableInfo.b10CableMaxCur))
#define SET_PD_RX0_CBL_MAX_CUR(x)                   (g_stPdRx0CableInfo.b10CableMaxCur = (x))

#define GET_PD_RX0_CBL_PD_CAPABILITY()              (g_stPdRx0CableInfo.enumTypeCCablePdCap)
#define SET_PD_RX0_CBL_PD_CAPABILITY(x)             (g_stPdRx0CableInfo.enumTypeCCablePdCap = (x))

#define GET_PD_RX0_CBL_MODAL_OPERATION_SUPPORT()    (g_stPdRx0CableInfo.b1CableModalOperation)
#define SET_PD_RX0_CBL_MODAL_OPERATION_SUPPORT()    (g_stPdRx0CableInfo.b1CableModalOperation = _TRUE)
#define CLR_PD_RX0_CBL_MODAL_OPERATION_SUPPORT()    (g_stPdRx0CableInfo.b1CableModalOperation = _FALSE)

#define GET_PD_RX0_CBL_PRODUCT_TYPE()               (g_stPdRx0CableInfo.enumTypeCCableProductType)
#define SET_PD_RX0_CBL_PRODUCT_TYPE(x)              (g_stPdRx0CableInfo.enumTypeCCableProductType = (x))

#define GET_PD_RX0_CBL_TERMINATION_TYPE()           (g_stPdRx0CableInfo.enumTypeCCableTerminationType)
#define SET_PD_RX0_CBL_TERMINATION_TYPE(x)          (g_stPdRx0CableInfo.enumTypeCCableTerminationType = (x))

#define GET_PD_RX0_CBL_VCONN_REQUIRED()             (g_stPdRx0CableInfo.b1CableVconnRequired)
#define SET_PD_RX0_CBL_VCONN_REQUIRED()             (g_stPdRx0CableInfo.b1CableVconnRequired = _TRUE)
#define CLR_PD_RX0_CBL_VCONN_REQUIRED()             (g_stPdRx0CableInfo.b1CableVconnRequired = _FALSE)

#define GET_PD_RX0_CBL_MAX_VOL()                    (g_stPdRx0CableInfo.b10CableMaxVol)
#define SET_PD_RX0_CBL_MAX_VOL(x)                   (g_stPdRx0CableInfo.b10CableMaxVol = (x))

#define GET_PD_RX0_CBL_SBU_SUPPORT()                (g_stPdRx0CableInfo.b1CableSbuSupport)
#define SET_PD_RX0_CBL_SBU_SUPPORT()                (g_stPdRx0CableInfo.b1CableSbuSupport = _TRUE)
#define CLR_PD_RX0_CBL_SBU_SUPPORT()                (g_stPdRx0CableInfo.b1CableSbuSupport = _FALSE)

#define GET_PD_RX0_CBL_SBU_TYPE()                   (g_stPdRx0CableInfo.enumTypeCCableSbuType)
#define SET_PD_RX0_CBL_SBU_TYPE(x)                  (g_stPdRx0CableInfo.enumTypeCCableSbuType = (x))

#define GET_PD_RX0_CBL_USB_HIGHEST_SPEED()          (g_stPdRx0CableInfo.enumTypeCCableUsbHighestSpeed)
#define SET_PD_RX0_CBL_USB_HIGHEST_SPEED(x)         (g_stPdRx0CableInfo.enumTypeCCableUsbHighestSpeed = (x))

#define GET_PD_RX0_CBL_VBUS_THROUGH()               (g_stPdRx0CableInfo.b1CableVbusThrough)
#define SET_PD_RX0_CBL_VBUS_THROUGH()               (g_stPdRx0CableInfo.b1CableVbusThrough = _TRUE)
#define CLR_PD_RX0_CBL_VBUS_THROUGH()               (g_stPdRx0CableInfo.b1CableVbusThrough = _FALSE)

#define GET_PD_RX0_CBL_SOP_PP_SUPPORT()             (g_stPdRx0CableInfo.b1CableSopPP)
#define SET_PD_RX0_CBL_SOP_PP_SUPPORT()             (g_stPdRx0CableInfo.b1CableSopPP = _TRUE)
#define CLR_PD_RX0_CBL_SOP_PP_SUPPORT()             (g_stPdRx0CableInfo.b1CableSopPP = _FALSE)

#define GET_PD_RX0_CBL_U3_TO_U0_TRANSITION_MODE()   (g_stPdRx0CableInfo.enumTypeCCableU3ToU0TransitionMode)
#define SET_PD_RX0_CBL_U3_TO_U0_TRANSITION_MODE(x)  (g_stPdRx0CableInfo.enumTypeCCableU3ToU0TransitionMode = (x))

#define GET_PD_RX0_CBL_ACTIVE_ELEMENT()             (g_stPdRx0CableInfo.enumTypeCCableActiveElement)
#define SET_PD_RX0_CBL_ACTIVE_ELEMENT(x)            (g_stPdRx0CableInfo.enumTypeCCableActiveElement = (x))

#define GET_PD_RX0_CBL_USB_4_SUPPORT()              (g_stPdRx0CableInfo.b1CableUSB4)
#define SET_PD_RX0_CBL_USB_4_SUPPORT()              (g_stPdRx0CableInfo.b1CableUSB4 = _TRUE)
#define CLR_PD_RX0_CBL_USB_4_SUPPORT()              (g_stPdRx0CableInfo.b1CableUSB4 = _FALSE)

#define GET_PD_RX0_CBL_USB_3_2_SUPPORT()            (g_stPdRx0CableInfo.b1CableUSB3_2)
#define SET_PD_RX0_CBL_USB_3_2_SUPPORT()            (g_stPdRx0CableInfo.b1CableUSB3_2 = _TRUE)
#define CLR_PD_RX0_CBL_USB_3_2_SUPPORT()            (g_stPdRx0CableInfo.b1CableUSB3_2 = _FALSE)

#define GET_PD_RX0_CBL_LANES_SUPPORT()              (g_stPdRx0CableInfo.enumTypeCCableUsbLanesSupport)
#define SET_PD_RX0_CBL_LANES_SUPPORT(x)             (g_stPdRx0CableInfo.enumTypeCCableUsbLanesSupport = (x))

#define GET_PD_RX0_CBL_CHARGE_THROUGH_SUPPORT()     (g_stPdRx0CableInfo.b1ChargeThroughSupport)
#define SET_PD_RX0_CBL_CHARGE_THROUGH_SUPPORT()     (g_stPdRx0CableInfo.b1ChargeThroughSupport = _TRUE)
#define CLR_PD_RX0_CBL_CHARGE_THROUGH_SUPPORT()     (g_stPdRx0CableInfo.b1ChargeThroughSupport = _FALSE)

#define GET_PD_RX0_CBL_SOFT_RESET_REQUIRED()        (g_stPdRx0CableInfo.b1CableSoftRstReq)
#define SET_PD_RX0_CBL_SOFT_RESET_REQUIRED()        (g_stPdRx0CableInfo.b1CableSoftRstReq = _TRUE)
#define CLR_PD_RX0_CBL_SOFT_RESET_REQUIRED()        (g_stPdRx0CableInfo.b1CableSoftRstReq = _FALSE)

// PD EXINT Set Timer Event Macro
#define GET_PD_RX0_TIMER_EVENT_VALID()              (g_stPdTimerEvent.b1Valid)
#define SET_PD_RX0_TIMER_EVENT_VALID()              (g_stPdTimerEvent.b1Valid = _TRUE)
#define CLR_PD_RX0_TIMER_EVENT_VALID()              (g_stPdTimerEvent.b1Valid = _FALSE)

#define GET_PD_RX0_TIMER_EVENT_ID()                 (g_stPdTimerEvent.enumEventID)
#define SET_PD_RX0_TIMER_EVENT_ID(x)                (g_stPdTimerEvent.enumEventID = (x))

#define GET_PD_RX0_TIMER_EVENT_CNT()                (g_stPdTimerEvent.usEventTime)
#define SET_PD_RX0_TIMER_EVENT_CNT(x)               (g_stPdTimerEvent.usEventTime = (x))

// Counter Control Macro
#define GET_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT() (g_stPdRx0CableInfo.b5DiscoverIdRetryFailCnt)
#define ADD_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT() (g_stPdRx0CableInfo.b5DiscoverIdRetryFailCnt += 1)
#define CLR_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT() (g_stPdRx0CableInfo.b5DiscoverIdRetryFailCnt = 0)

#define GET_DP_RX0_SRC_CAP_CNT()                    (g_stPdRx0Status.b6SrcCapCnt)
#define ADD_DP_RX0_SRC_CAP_CNT()                    (g_stPdRx0Status.b6SrcCapCnt += 1)
#define CLR_DP_RX0_SRC_CAP_CNT()                    (g_stPdRx0Status.b6SrcCapCnt = 0)

#define GET_DP_RX0_HARD_RST_CNT()                   (g_stPdRx0Status.b2HardRstCnt)
#define ADD_DP_RX0_HARD_RST_CNT()                   (g_stPdRx0Status.b2HardRstCnt += 1)
#define CLR_DP_RX0_HARD_RST_CNT()                   (g_stPdRx0Status.b2HardRstCnt = 0)

#define GET_DP_RX0_CHECK_VBUS_CNT()                 (g_stPdRx0Status.b4CheckVbusCnt)
#define ADD_DP_RX0_CHECK_VBUS_CNT()                 (g_stPdRx0Status.b4CheckVbusCnt += 1)
#define CLR_DP_RX0_CHECK_VBUS_CNT()                 (g_stPdRx0Status.b4CheckVbusCnt = 0)

// FW Flow Control Macro
#define GET_PD_RX0_HRST_PWR_OFF()                   (g_stPdRx0Status.b1HRST_Pwr_Off)
#define SET_PD_RX0_HRST_PWR_OFF()                   (g_stPdRx0Status.b1HRST_Pwr_Off = _TRUE)
#define CLR_PD_RX0_HRST_PWR_OFF()                   (g_stPdRx0Status.b1HRST_Pwr_Off = _FALSE)

#define GET_PD_RX0_PRS_REJECT()                     (g_stPdRx0Status.b1PDPRSwapReject)
#define SET_PD_RX0_PRS_REJECT()                     (g_stPdRx0Status.b1PDPRSwapReject = _TRUE)
#define CLR_PD_RX0_PRS_REJECT()                     (g_stPdRx0Status.b1PDPRSwapReject = _FALSE)

#define GET_PD_RX0_DRS_REJECT()                     (g_stPdRx0Status.b1PDDRSwapReject)
#define SET_PD_RX0_DRS_REJECT()                     (g_stPdRx0Status.b1PDDRSwapReject = _TRUE)
#define CLR_PD_RX0_DRS_REJECT()                     (g_stPdRx0Status.b1PDDRSwapReject = _FALSE)

#define GET_PD_RX0_VCS_REJECT()                     (g_stPdRx0Status.b1PDVconnSwapReject)
#define SET_PD_RX0_VCS_REJECT()                     (g_stPdRx0Status.b1PDVconnSwapReject = _TRUE)
#define CLR_PD_RX0_VCS_REJECT()                     (g_stPdRx0Status.b1PDVconnSwapReject = _FALSE)

#define GET_PD_RX0_VCS_SENT()                       (g_stPdRx0Status.b1VconnSwapSent)
#define SET_PD_RX0_VCS_SENT()                       (g_stPdRx0Status.b1VconnSwapSent = _TRUE)
#define CLR_PD_RX0_VCS_SENT()                       (g_stPdRx0Status.b1VconnSwapSent = _FALSE)

#define GET_PD_RX0_GET_SNK_CAP_SENT()               (g_stPdRx0Status.b1GetSnkCapSent)
#define SET_PD_RX0_GET_SNK_CAP_SENT()               (g_stPdRx0Status.b1GetSnkCapSent = _TRUE)
#define CLR_PD_RX0_GET_SNK_CAP_SENT()               (g_stPdRx0Status.b1GetSnkCapSent = _FALSE)

#define GET_PD_RX0_RCV_SNK_CAP()                    (g_stPdRx0Status.b1RcvSnkCap)
#define SET_PD_RX0_RCV_SNK_CAP()                    (g_stPdRx0Status.b1RcvSnkCap = _TRUE)
#define CLR_PD_RX0_RCV_SNK_CAP()                    (g_stPdRx0Status.b1RcvSnkCap = _FALSE)

#define GET_PD_RX0_RCV_SRC_CAP()                    (g_stPdRx0Status.b1RcvSrcCap)
#define SET_PD_RX0_RCV_SRC_CAP()                    (g_stPdRx0Status.b1RcvSrcCap = _TRUE)
#define CLR_PD_RX0_RCV_SRC_CAP()                    (g_stPdRx0Status.b1RcvSrcCap = _FALSE)

#define GET_PD_RX0_REQ_WAIT_FLAG()                  (g_stPdRx0Status.b1ReqWait)
#define SET_PD_RX0_REQ_WAIT_FLAG()                  (g_stPdRx0Status.b1ReqWait = _TRUE)
#define CLR_PD_RX0_REQ_WAIT_FLAG()                  (g_stPdRx0Status.b1ReqWait = _FALSE)

#define GET_PD_RX0_PRS_WAIT_FLAG()                  (g_stPdRx0Status.b1PRSwapWait)
#define SET_PD_RX0_PRS_WAIT_FLAG()                  (g_stPdRx0Status.b1PRSwapWait = _TRUE)
#define CLR_PD_RX0_PRS_WAIT_FLAG()                  (g_stPdRx0Status.b1PRSwapWait = _FALSE)

#define GET_PD_RX0_DRS_WAIT_FLAG()                  (g_stPdRx0Status.b1DRSwapWait)
#define SET_PD_RX0_DRS_WAIT_FLAG()                  (g_stPdRx0Status.b1DRSwapWait = _TRUE)
#define CLR_PD_RX0_DRS_WAIT_FLAG()                  (g_stPdRx0Status.b1DRSwapWait = _FALSE)

#define GET_PD_RX0_VCS_WAIT_FLAG()                  (g_stPdRx0Status.b1VCSwapWait)
#define SET_PD_RX0_VCS_WAIT_FLAG()                  (g_stPdRx0Status.b1VCSwapWait = _TRUE)
#define CLR_PD_RX0_VCS_WAIT_FLAG()                  (g_stPdRx0Status.b1VCSwapWait = _FALSE)

#define GET_PD_RX0_CBL_WAIT_FLAG()                  (g_stPdRx0Status.b1CblWait)
#define SET_PD_RX0_CBL_WAIT_FLAG()                  (g_stPdRx0Status.b1CblWait = _TRUE)
#define CLR_PD_RX0_CBL_WAIT_FLAG()                  (g_stPdRx0Status.b1CblWait = _FALSE)

#define GET_PD_RX0_SRC_CAP_SENT_FLAG()              (g_stPdRx0Status.b1SrcCapSent)
#define SET_PD_RX0_SRC_CAP_SENT_FLAG()              (g_stPdRx0Status.b1SrcCapSent = _TRUE)
#define CLR_PD_RX0_SRC_CAP_SENT_FLAG()              (g_stPdRx0Status.b1SrcCapSent = _FALSE)

#define GET_PD_RX0_SNK_CAP_WAIT_FLAG()              (g_stPdRx0Status.b1SnkCapWait)
#define SET_PD_RX0_SNK_CAP_WAIT_FLAG()              (g_stPdRx0Status.b1SnkCapWait = _TRUE)
#define CLR_PD_RX0_SNK_CAP_WAIT_FLAG()              (g_stPdRx0Status.b1SnkCapWait = _FALSE)

#define GET_PD_RX0_VDMMSG_WAIT_FLAG()               (g_stPdRx0Status.b1VdmMsgWait)
#define SET_PD_RX0_VDMMSG_WAIT_FLAG()               (g_stPdRx0Status.b1VdmMsgWait = _TRUE)
#define CLR_PD_RX0_VDMMSG_WAIT_FLAG()               (g_stPdRx0Status.b1VdmMsgWait = _FALSE)

#define GET_PD_RX0_VDM_BUSY_FLAG()                  (g_stPdRx0Status.b1VdmBusy)
#define SET_PD_RX0_VDM_BUSY_FLAG()                  (g_stPdRx0Status.b1VdmBusy = _TRUE)
#define CLR_PD_RX0_VDM_BUSY_FLAG()                  (g_stPdRx0Status.b1VdmBusy = _FALSE)

#define GET_PD_RX0_PRS_PROCESSING()                 (g_stPdRx0Status.b1PRS_Processing)
#define SET_PD_RX0_PRS_PROCESSING()                 (g_stPdRx0Status.b1PRS_Processing = _TRUE)
#define CLR_PD_RX0_PRS_PROCESSING()                 (g_stPdRx0Status.b1PRS_Processing = _FALSE)

#define GET_PD_RX0_INTEROP_S8()                     (g_stPdRx0Status.b1InteropS8)
#define SET_PD_RX0_INTEROP_S8()                     (g_stPdRx0Status.b1InteropS8 = _TRUE)
#define CLR_PD_RX0_INTEROP_S8()                     (g_stPdRx0Status.b1InteropS8 = _FALSE)

#define GET_PD_RX0_ALERT_SENT()                     (g_stPdRx0Status.b1AlertSent)
#define SET_PD_RX0_ALERT_SENT()                     (g_stPdRx0Status.b1AlertSent = _TRUE)
#define CLR_PD_RX0_ALERT_SENT()                     (g_stPdRx0Status.b1AlertSent = _FALSE)

#define GET_PD_RX0_GET_SNK_CAP_WAIT_FLAG()          (g_stPdRx0Status.b1GetSnkCapWait)
#define SET_PD_RX0_GET_SNK_CAP_WAIT_FLAG()          (g_stPdRx0Status.b1GetSnkCapWait = _TRUE)
#define CLR_PD_RX0_GET_SNK_CAP_WAIT_FLAG()          (g_stPdRx0Status.b1GetSnkCapWait = _FALSE)

// Source Capability Macros
#define GET_PD_RX0_SRC_PDO_CNT()                    ((BYTE)g_stPdRx0Status.b3PDNumOfSrcCap)
#define SET_PD_RX0_SRC_PDO_CNT(x)                   (g_stPdRx0Status.b3PDNumOfSrcCap = (x))

#define GET_PD_RX0_SRC_PDO_TYPE(x)                  (g_pstSrcPDO[x].enumPdoType)
#define SET_PD_RX0_SRC_PDO_TYPE(x, y)               (g_pstSrcPDO[x].enumPdoType = (y))

#define GET_PD_RX0_SRC_CAP_VOL_MAX(x)               ((WORD)(g_pstSrcPDO[x].b12MaxVoltage))
#define SET_PD_RX0_SRC_CAP_VOL_MAX(x, y)            (g_pstSrcPDO[x].b12MaxVoltage = (y))

#define GET_PD_RX0_SRC_CAP_VOL_MIN(x)               ((WORD)(g_pstSrcPDO[x].b12MinVoltage))
#define SET_PD_RX0_SRC_CAP_VOL_MIN(x, y)            (g_pstSrcPDO[x].b12MinVoltage = (y))

#define GET_PD_RX0_SRC_CAP_CUR(x)                   ((WORD)(g_pstSrcPDO[x].b10MaxCurrent))
#define SET_PD_RX0_SRC_CAP_CUR(x, y)                (g_pstSrcPDO[x].b10MaxCurrent = (y))

#define GET_PD_RX0_SRC_CAP_PEAK(x)                  (g_pstSrcPDO[x].b2PeakCurrent)
#define SET_PD_RX0_SRC_CAP_PEAK(x, y)               (g_pstSrcPDO[x].b2PeakCurrent = (y))

// Request Macros
#define GET_PD_RX0_REQ_OBJ_POS()                    ((BYTE)(g_stSnkRDO.enumObjPos))
#define SET_PD_RX0_REQ_OBJ_POS(x)                   (g_stSnkRDO.enumObjPos = (x))

#define GET_PD_RX0_REQ_CAP_MIS()                    ((BYTE)(g_stSnkRDO.b1CapMismatch))
#define SET_PD_RX0_REQ_CAP_MIS(x)                   (g_stSnkRDO.b1CapMismatch = (x))

#define GET_PD_RX0_REQ_GIVE_BACK()                  ((BYTE)(g_stSnkRDO.b1GiveBack))
#define SET_PD_RX0_REQ_GIVE_BACK(x)                 (g_stSnkRDO.b1GiveBack = (x))

#define GET_PD_RX0_REQ_INFO_1()                     (g_stSnkRDO.usReqInfo1)
#define SET_PD_RX0_REQ_INFO_1(x)                    (g_stSnkRDO.usReqInfo1 = (x))

#define GET_PD_RX0_REQ_INFO_2()                     (g_stSnkRDO.usReqInfo2)
#define SET_PD_RX0_REQ_INFO_2(x)                    (g_stSnkRDO.usReqInfo2 = (x))

// Sink Capability Macros
#define GET_PD_RX0_SNK_PDO_CNT()                    ((BYTE)g_stPdRx0Status.b3PDNumOfSnkCap)
#define SET_PD_RX0_SNK_PDO_CNT(x)                   (g_stPdRx0Status.b3PDNumOfSnkCap = (x))

#define GET_PD_RX0_SNK_PDO_TYPE(x)                  (g_pstSnkPDO[x].enumPdoType)
#define SET_PD_RX0_SNK_PDO_TYPE(x, y)               (g_pstSnkPDO[x].enumPdoType = (y))

#define GET_PD_RX0_SNK_CAP_VOL_MAX(x)               ((WORD)(g_pstSnkPDO[x].b12MaxVoltage))
#define SET_PD_RX0_SNK_CAP_VOL_MAX(x, y)            (g_pstSnkPDO[x].b12MaxVoltage = (y))

#define GET_PD_RX0_SNK_CAP_VOL_MIN(x)               ((WORD)(g_pstSnkPDO[x].b12MinVoltage))
#define SET_PD_RX0_SNK_CAP_VOL_MIN(x, y)            (g_pstSnkPDO[x].b12MinVoltage = (y))

#define GET_PD_RX0_SNK_CAP_CUR(x)                   ((WORD)(g_pstSnkPDO[x].b10MaxCurrent))
#define SET_PD_RX0_SNK_CAP_CUR(x, y)                (g_pstSnkPDO[x].b10MaxCurrent = (y))

// Port Partner(Other Side) General Info Setting Macros
#define GET_PD_RX0_PARTNER_DRP()                    (g_stPdRx0PartnerInfo.b1DualRolePower)
#define SET_PD_RX0_PARTNER_DRP(x)                   (g_stPdRx0PartnerInfo.b1DualRolePower = (x))

#define GET_PD_RX0_PARTNER_DRD()                    (g_stPdRx0PartnerInfo.b1DualRoleData)
#define SET_PD_RX0_PARTNER_DRD(x)                   (g_stPdRx0PartnerInfo.b1DualRoleData = (x))

#define GET_PD_RX0_PARTNER_SUSPEND()                (g_stPdRx0PartnerInfo.b1SuspendSupport)
#define SET_PD_RX0_PARTNER_SUSPEND(x)               (g_stPdRx0PartnerInfo.b1SuspendSupport = (x))
#define CLR_PD_RX0_PARTNER_SUSPEND()                (g_stPdRx0PartnerInfo.b1SuspendSupport = _FALSE)

#define GET_PD_RX0_PARTNER_EXT_PWR()                (g_stPdRx0PartnerInfo.b1ExtPower)
#define SET_PD_RX0_PARTNER_EXT_PWR(x)               (g_stPdRx0PartnerInfo.b1ExtPower = (x))
#define CLR_PD_RX0_PARTNER_EXT_PWR()                (g_stPdRx0PartnerInfo.b1ExtPower = _FALSE)

#define GET_PD_RX0_PARTNER_USB_CAP()                (g_stPdRx0PartnerInfo.b1UsbCapable)
#define SET_PD_RX0_PARTNER_USB_CAP(x)               (g_stPdRx0PartnerInfo.b1UsbCapable = (x))
#define CLR_PD_RX0_PARTNER_USB_CAP()                (g_stPdRx0PartnerInfo.b1UsbCapable = _FALSE)

#define GET_PD_RX0_PARTNER_UNCHK()                  (g_stPdRx0PartnerInfo.b1UnchkSupport)
#define SET_PD_RX0_PARTNER_UNCHK(x)                 (g_stPdRx0PartnerInfo.b1UnchkSupport = (x))
#define CLR_PD_RX0_PARTNER_UNCHK()                  (g_stPdRx0PartnerInfo.b1UnchkSupport = _FALSE)

#define GET_PD_RX0_PARTNER_ALT_SUPPORT()            (g_stPdRx0PartnerInfo.b1ALTSupport)
#define SET_PD_RX0_PARTNER_ALT_SUPPORT()            (g_stPdRx0PartnerInfo.b1ALTSupport = _TRUE)
#define CLR_PD_RX0_PARTNER_ALT_SUPPORT()            (g_stPdRx0PartnerInfo.b1ALTSupport = _FALSE)

#define GET_PD_RX0_PARTNER_HIGH_CAP()               (g_stPdRx0PartnerInfo.b1HigherCap)
#define SET_PD_RX0_PARTNER_HIGH_CAP(x)              (g_stPdRx0PartnerInfo.b1HigherCap = (x))
#define CLR_PD_RX0_PARTNER_HIGH_CAP()               (g_stPdRx0PartnerInfo.b1HigherCap = _FALSE)

#define GET_PD_RX0_PARTNER_FRS_CUR()                (g_stPdRx0PartnerInfo.b2FrsCurrent)
#define SET_PD_RX0_PARTNER_FRS_CUR(x)               (g_stPdRx0PartnerInfo.b2FrsCurrent = (x))
#define CLR_PD_RX0_PARTNER_FRS_CUR()                (g_stPdRx0PartnerInfo.b2FrsCurrent = 0)

// Port Partner(Other Side) Source Cap Info Setting Macros
#define GET_PD_RX0_PARTNER_SRC_CAP_CNT()            (g_stPdRx0PartnerInfo.b3NumOfSrcCap)
#define SET_PD_RX0_PARTNER_SRC_CAP_CNT(x)           (g_stPdRx0PartnerInfo.b3NumOfSrcCap = (x))
#define CLR_PD_RX0_PARTNER_SRC_CAP_CNT()            (g_stPdRx0PartnerInfo.b3NumOfSrcCap = 0)

#define GET_PD_RX0_PARTNER_SRC_CAP_TYPE(x)          (g_pstPartnerSrcCap[x].enumPdoType)
#define SET_PD_RX0_PARTNER_SRC_CAP_TYPE(x, y)       (g_pstPartnerSrcCap[x].enumPdoType = (y))

#define GET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(x)       (g_pstPartnerSrcCap[x].b12MaxVoltage)
#define SET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(x, y)    (g_pstPartnerSrcCap[x].b12MaxVoltage = (y))

#define GET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(x)       (g_pstPartnerSrcCap[x].b12MinVoltage)
#define SET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(x, y)    (g_pstPartnerSrcCap[x].b12MinVoltage = (y))

#define GET_PD_RX0_PARTNER_SRC_CAP_CUR(x)           (g_pstPartnerSrcCap[x].b10MaxCurrent)
#define SET_PD_RX0_PARTNER_SRC_CAP_CUR(x, y)        (g_pstPartnerSrcCap[x].b10MaxCurrent = (y))

#define GET_PD_RX0_PARTNER_SRC_PEAK_CUR(x)          (g_pstPartnerSrcCap[x].b2PeakCurrent)
#define SET_PD_RX0_PARTNER_SRC_PEAK_CUR(x, y)       (g_pstPartnerSrcCap[x].b2PeakCurrent = (y))

// Port Partner(Other Side) Request Info Setting Macros
#define GET_PD_RX0_PARTNER_OBJ_POS()                (g_stPartnerRDO.b3ObjPos)
#define SET_PD_RX0_PARTNER_OBJ_POS(x)               (g_stPartnerRDO.b3ObjPos = (x))
#define CLR_PD_RX0_PARTNER_OBJ_POS()                (g_stPartnerRDO.b3ObjPos = 0)

#define GET_PD_RX0_PARTNER_CAP_MIS()                (g_stPartnerRDO.b1CapMis)
#define SET_PD_RX0_PARTNER_CAP_MIS(x)               (g_stPartnerRDO.b1CapMis = (x))
#define CLR_PD_RX0_PARTNER_CAP_MIS()                (g_stPartnerRDO.b1CapMis = _FALSE)

#define GET_PD_RX0_PARTNER_GIVE_BACK()              (g_stPartnerRDO.b1GiveBack)
#define SET_PD_RX0_PARTNER_GIVE_BACK(x)             (g_stPartnerRDO.b1GiveBack = (x))
#define CLR_PD_RX0_PARTNER_GIVE_BACK()              (g_stPartnerRDO.b1GiveBack = _FALSE)

#define GET_PD_RX0_PARTNER_REQ_VOL()                (g_stPartnerRDO.b12Voltage)
#define SET_PD_RX0_PARTNER_REQ_VOL(x)               (g_stPartnerRDO.b12Voltage = (x))

#define GET_PD_RX0_PARTNER_OP_CUR()                 (g_stPartnerRDO.b10OpCurrent)
#define SET_PD_RX0_PARTNER_OP_CUR(x)                (g_stPartnerRDO.b10OpCurrent = (x))
#define CLR_PD_RX0_PARTNER_OP_CUR()                 (g_stPartnerRDO.b10OpCurrent = 0)

#define GET_PD_RX0_PARTNER_MAX_CUR()                (g_stPartnerRDO.b10MaxCurrent)
#define SET_PD_RX0_PARTNER_MAX_CUR(x)               (g_stPartnerRDO.b10MaxCurrent = (x))
#define CLR_PD_RX0_PARTNER_MAX_CUR()                (g_stPartnerRDO.b10MaxCurrent = 0)

#define GET_PD_RX0_REQ_VOL_SMALL_STEP()             (g_stPartnerRDO.b1SmallStep)
#define SET_PD_RX0_REQ_VOL_SMALL_STEP(x)            (g_stPartnerRDO.b1SmallStep = (x))
#define CLR_PD_RX0_REQ_VOL_SMALL_STEP()             (g_stPartnerRDO.b1SmallStep = 0)

// Power Contract Negotiated Power Status For User
#define GET_PD_RX0_PDO_STATUS_VOL()                 (g_stPDOStatus.usVoltage)
#define SET_PD_RX0_PDO_STATUS_VOL(x)                (g_stPDOStatus.usVoltage = (x))

#define GET_PD_RX0_PDO_STATUS_CUR()                 (g_stPDOStatus.usCurrent)
#define SET_PD_RX0_PDO_STATUS_CUR(x)                (g_stPDOStatus.usCurrent = (x))

// Port Partner(Other Side) Sink Cap Info Setting Macros
#define GET_PD_RX0_PARTNER_SNK_CAP_CNT()            (g_stPdRx0PartnerInfo.b3NumOfSnkCap)
#define SET_PD_RX0_PARTNER_SNK_CAP_CNT(x)           (g_stPdRx0PartnerInfo.b3NumOfSnkCap = (x))
#define CLR_PD_RX0_PARTNER_SNK_CAP_CNT()            (g_stPdRx0PartnerInfo.b3NumOfSnkCap = 0)

#define GET_PD_RX0_PARTNER_SNK_CAP_TYPE(x)          (g_pstPartnerSnkCap[x].enumPdoType)
#define SET_PD_RX0_PARTNER_SNK_CAP_TYPE(x, y)       (g_pstPartnerSnkCap[x].enumPdoType = (y))

#define GET_PD_RX0_PARTNER_SNK_CAP_VOL_MAX(x)       (g_pstPartnerSnkCap[x].b12MaxVoltage)
#define SET_PD_RX0_PARTNER_SNK_CAP_VOL_MAX(x, y)    (g_pstPartnerSnkCap[x].b12MaxVoltage = (y))

#define GET_PD_RX0_PARTNER_SNK_CAP_VOL_MIN(x)       (g_pstPartnerSnkCap[x].b12MinVoltage)
#define SET_PD_RX0_PARTNER_SNK_CAP_VOL_MIN(x, y)    (g_pstPartnerSnkCap[x].b12MinVoltage = (y))

#define GET_PD_RX0_PARTNER_SNK_CAP_CUR(x)           (g_pstPartnerSnkCap[x].b10MaxCurrent)
#define SET_PD_RX0_PARTNER_SNK_CAP_CUR(x, y)        (g_pstPartnerSnkCap[x].b10MaxCurrent = (y))

// Alt Mode Info Macros
#define GET_PD_RX0_ALT_MODE_FUNCTION()              (g_stPdRx0AltModeInfo.b1AltModeFunc)
#define SET_PD_RX0_ALT_MODE_FUNCTION()              (g_stPdRx0AltModeInfo.b1AltModeFunc = _TRUE)
#define CLR_PD_RX0_ALT_MODE_FUNCTION()              (g_stPdRx0AltModeInfo.b1AltModeFunc = _FALSE)

#define GET_PD_RX0_SRC_INIT_ALT_MODE()              (g_stPdRx0AltModeInfo.b1InitAltMode)
#define SET_PD_RX0_SRC_INIT_ALT_MODE()              (g_stPdRx0AltModeInfo.b1InitAltMode = _TRUE)
#define CLR_PD_RX0_SRC_INIT_ALT_MODE()              (g_stPdRx0AltModeInfo.b1InitAltMode = _FALSE)

#define GET_PD_RX0_PARTNER_INIT_ALT_MODE()          (g_stPdRx0AltModeInfo.b1PartnerInitAltMode)
#define SET_PD_RX0_PARTNER_INIT_ALT_MODE()          (g_stPdRx0AltModeInfo.b1PartnerInitAltMode = _TRUE)
#define CLR_PD_RX0_PARTNER_INIT_ALT_MODE()          (g_stPdRx0AltModeInfo.b1PartnerInitAltMode = _FALSE)

#define GET_PD_RX0_ATTN_TYPE()                      (g_stPdRx0AltModeInfo.enumAttnType)
#define SET_PD_RX0_ATTN_TYPE(x)                     (g_stPdRx0AltModeInfo.enumAttnType = (x))

#define GET_PD_RX0_RCV_VDM_CMD()                    (g_stPdRx0AltModeInfo.ucRcvVdmMsg)
#define GET_PD_RX0_RCV_VDM_CMD_TYPE()               (g_stPdRx0AltModeInfo.ucRcvVdmMsg & (_BIT7 | _BIT6))
#define SET_PD_RX0_RCV_VDM_CMD(x)                   (g_stPdRx0AltModeInfo.ucRcvVdmMsg = (x))
#define CLR_PD_RX0_RCV_VDM_CMD()                    (g_stPdRx0AltModeInfo.ucRcvVdmMsg = 0)

#define GET_PD_RX0_RCV_VDM_TYPE()                   (g_stPdRx0AltModeInfo.b1RcvVdmType)
#define SET_PD_RX0_RCV_VDM_TYPE(x)                  (g_stPdRx0AltModeInfo.b1RcvVdmType = (x))

#define GET_PD_RX0_PARTNER_VDM_NO_RESP_CNT()        (g_stPdRx0AltModeInfo.b2PartnerVdmNoRespCnt)
#define ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT()        (g_stPdRx0AltModeInfo.b2PartnerVdmNoRespCnt += 1)
#define CLR_PD_RX0_PARTNER_VDM_NO_RESP_CNT()        (g_stPdRx0AltModeInfo.b2PartnerVdmNoRespCnt = 0)

#define GET_PD_RX0_CBL_VDM_NO_RESP_CNT()            (g_stPdRx0AltModeInfo.b2CblVdmNoRespCnt)
#define ADD_PD_RX0_CBL_VDM_NO_RESP_CNT()            (g_stPdRx0AltModeInfo.b2CblVdmNoRespCnt += 1)
#define CLR_PD_RX0_CBL_VDM_NO_RESP_CNT()            (g_stPdRx0AltModeInfo.b2CblVdmNoRespCnt = 0)

#define GET_PD_RX0_VDM_BUSY_CNT()                   (g_stPdRx0AltModeInfo.b3VdmBusyCnt)
#define ADD_PD_RX0_VDM_BUSY_CNT()                   (g_stPdRx0AltModeInfo.b3VdmBusyCnt += 1)
#define CLR_PD_RX0_VDM_BUSY_CNT()                   (g_stPdRx0AltModeInfo.b3VdmBusyCnt = 0)

#define GET_PD_RX0_UFP_PRODUCT_TYPE()               (g_stPdRx0AltModeInfo.enumUFPProductType)
#define SET_PD_RX0_UFP_PRODUCT_TYPE(x)              (g_stPdRx0AltModeInfo.enumUFPProductType = (x))

#define GET_PD_RX0_DFP_PRODUCT_TYPE()               (g_stPdRx0AltModeInfo.enumDFPProductType)
#define SET_PD_RX0_DFP_PRODUCT_TYPE(x)              (g_stPdRx0AltModeInfo.enumDFPProductType = (x))

#define GET_PD_RX0_VDM_SVID()                       (((WORD)(g_stPdRx0AltModeInfo.ucVdmSVID_H) << 8) | ((WORD)(g_stPdRx0AltModeInfo.ucVdmSVID_L)))
#define GET_PD_RX0_VDM_SVID_H()                     (g_stPdRx0AltModeInfo.ucVdmSVID_H)
#define GET_PD_RX0_VDM_SVID_L()                     (g_stPdRx0AltModeInfo.ucVdmSVID_L)
#define SET_PD_RX0_VDM_SVID_H(x)                    (g_stPdRx0AltModeInfo.ucVdmSVID_H = (x))
#define SET_PD_RX0_VDM_SVID_L(x)                    (g_stPdRx0AltModeInfo.ucVdmSVID_L = (x))

#define GET_PD_RX0_VDM_OBJ_POS()                    (g_stPdRx0AltModeInfo.b3VdmObjPos)
#define SET_PD_RX0_VDM_OBJ_POS(x)                   (g_stPdRx0AltModeInfo.b3VdmObjPos = (x))
#define CLR_PD_RX0_VDM_OBJ_POS(x)                   (g_stPdRx0AltModeInfo.b3VdmObjPos = 0)

#define GET_PD_RX0_PIN_ASSIGNMENT()                 (g_stPdRx0AltModeInfo.enumDpRxPinAssignment)
#define SET_PD_RX0_PIN_ASSIGNMENT(x)                (g_stPdRx0AltModeInfo.enumDpRxPinAssignment = (x))

#define GET_PD_RX0_PIN_ASSIGNMENT_CAP()             (g_stPdRx0AltModeInfo.enumPinAssignmentCap)
#define SET_PD_RX0_PIN_ASSIGNMENT_CAP(x)            (g_stPdRx0AltModeInfo.enumPinAssignmentCap = (x))

#define GET_PD_RX0_PARTNER_PIN_ASSIGNMENT()         (g_stPdRx0AltModeInfo.ucPartnerPinAssignmentCap)
#define SET_PD_RX0_PARTNER_PIN_ASSIGNMENT(x)        (g_stPdRx0AltModeInfo.ucPartnerPinAssignmentCap = (x))

#define GET_PD_RX0_MULTI_FUNCTION()                 (g_stPdRx0AltModeInfo.b1MultiFunctionBit)
#define SET_PD_RX0_MULTI_FUNCTION()                 (g_stPdRx0AltModeInfo.b1MultiFunctionBit = _TRUE)
#define CLR_PD_RX0_MULTI_FUNCTION()                 (g_stPdRx0AltModeInfo.b1MultiFunctionBit = _FALSE)

#define GET_PD_RX0_ATTENTION_WAIT()                 (g_stPdRx0AltModeInfo.b1AttentionWait)
#define SET_PD_RX0_ATTENTION_WAIT()                 (g_stPdRx0AltModeInfo.b1AttentionWait = _TRUE)
#define CLR_PD_RX0_ATTENTION_WAIT()                 (g_stPdRx0AltModeInfo.b1AttentionWait = _FALSE)

#define GET_PD_RX0_DP_OBJ_POS()                     (g_stPdRx0AltModeInfo.b3DpObjPos)
#define SET_PD_RX0_DP_OBJ_POS(x)                    (g_stPdRx0AltModeInfo.b3DpObjPos = (x))
#define CLR_PD_RX0_DP_OBJ_POS()                     (g_stPdRx0AltModeInfo.b3DpObjPos = 0)

#define GET_PD_RX0_DP_SVID_SEARCH_FINISH()          (g_stPdRx0AltModeInfo.b1DpSvidSearchFinish)
#define SET_PD_RX0_DP_SVID_SEARCH_FINISH()          (g_stPdRx0AltModeInfo.b1DpSvidSearchFinish = _TRUE)
#define CLR_PD_RX0_DP_SVID_SEARCH_FINISH()          (g_stPdRx0AltModeInfo.b1DpSvidSearchFinish = _FALSE)

#define GET_PD_RX0_DP_ALT_MODE_ENTER()              (g_stPdRx0AltModeInfo.b1DpAltModeEnter)
#define SET_PD_RX0_DP_ALT_MODE_ENTER()              (g_stPdRx0AltModeInfo.b1DpAltModeEnter = _TRUE)
#define CLR_PD_RX0_DP_ALT_MODE_ENTER()              (g_stPdRx0AltModeInfo.b1DpAltModeEnter = _FALSE)

#define GET_PD_RX0_DP_ALT_MODE_CONFIG()             (g_stPdRx0AltModeInfo.b1DpAltModeConfig)
#define SET_PD_RX0_DP_ALT_MODE_CONFIG(x)            (g_stPdRx0AltModeInfo.b1DpAltModeConfig = (x))

#define GET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG()      (g_stPdRx0AltModeInfo.b1DpAltModeTargetConfig)
#define SET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG(x)     (g_stPdRx0AltModeInfo.b1DpAltModeTargetConfig = (x))

#define GET_PD_RX0_DP_ALT_MODE_WAIT_CONFIG()        (g_stPdRx0AltModeInfo.b1DpAltModeWaitConfig)
#define SET_PD_RX0_DP_ALT_MODE_WAIT_CONFIG()        (g_stPdRx0AltModeInfo.b1DpAltModeWaitConfig = _TRUE)
#define CLR_PD_RX0_DP_ALT_MODE_WAIT_CONFIG()        (g_stPdRx0AltModeInfo.b1DpAltModeWaitConfig = _FALSE)

#define GET_PD_RX0_DP_ALT_MODE_EXIT_REQ()           (g_stPdRx0AltModeInfo.b1DpAltModeExit)
#define SET_PD_RX0_DP_ALT_MODE_EXIT_REQ()           (g_stPdRx0AltModeInfo.b1DpAltModeExit = _TRUE)
#define CLR_PD_RX0_DP_ALT_MODE_EXIT_REQ()           (g_stPdRx0AltModeInfo.b1DpAltModeExit = _FALSE)

#define GET_PD_RX0_LENOVO_ATTN_SENT_FLAG()          (g_stPdRx0AltModeInfo.b1LenovoAttnSent)
#define SET_PD_RX0_LENOVO_ATTN_SENT_FLAG()          (g_stPdRx0AltModeInfo.b1LenovoAttnSent = _TRUE)
#define CLR_PD_RX0_LENOVO_ATTN_SENT_FLAG()          (g_stPdRx0AltModeInfo.b1LenovoAttnSent = _FALSE)

#define GET_PD_RX0_LENOVO_ATTN_CNT()                (g_stPdRx0AltModeInfo.b3LenovoAttnCnt)
#define ADD_PD_RX0_LENOVO_ATTN_CNT()                (g_stPdRx0AltModeInfo.b3LenovoAttnCnt += 1)
#define CLR_PD_RX0_LENOVO_ATTN_CNT()                (g_stPdRx0AltModeInfo.b3LenovoAttnCnt = 0)

#define GET_PD_RX0_LENOVO_OBJ_POS()                 (g_stPdRx0AltModeInfo.b3LenovoObjPos)
#define SET_PD_RX0_LENOVO_OBJ_POS(x)                (g_stPdRx0AltModeInfo.b3LenovoObjPos = (x))
#define CLR_PD_RX0_LENOVO_OBJ_POS()                 (g_stPdRx0AltModeInfo.b3LenovoObjPos = 0)

#define GET_PD_RX0_LENOVO_DEVICE_TYPE()             (g_stPdRx0AltModeInfo.enumLenovoDeviceType)
#define SET_PD_RX0_LENOVO_DEVICE_TYPE(x)            (g_stPdRx0AltModeInfo.enumLenovoDeviceType = (x))

#define GET_PD_RX0_LENOVO_ALT_MODE_ENTER()          (g_stPdRx0AltModeInfo.b1LenovoAltModeEnter)
#define SET_PD_RX0_LENOVO_ALT_MODE_ENTER()          (g_stPdRx0AltModeInfo.b1LenovoAltModeEnter = _TRUE)
#define CLR_PD_RX0_LENOVO_ALT_MODE_ENTER()          (g_stPdRx0AltModeInfo.b1LenovoAltModeEnter = _FALSE)

#define GET_PD_RX0_LENOVO_DOCK_EVENT()              (g_stPdRx0AltModeInfo.ucLenovoDockingEvent)
#define SET_PD_RX0_LENOVO_DOCK_EVENT(x)             (g_stPdRx0AltModeInfo.ucLenovoDockingEvent = (x))
#define CLR_PD_RX0_LENOVO_DOCK_EVENT()              (g_stPdRx0AltModeInfo.ucLenovoDockingEvent = 0)

#define GET_PD_RX0_LENOVO_SYS_ACKNOWLEDGE()         (g_stPdRx0AltModeInfo.ucLenovoSystemAcknowledge)
#define SET_PD_RX0_LENOVO_SYS_ACKNOWLEDGE(x)        (g_stPdRx0AltModeInfo.ucLenovoSystemAcknowledge = (x))
#define CLR_PD_RX0_LENOVO_SYS_ACKNOWLEDGE()         (g_stPdRx0AltModeInfo.ucLenovoSystemAcknowledge = 0)

#define GET_PD_RX0_LENOVO_SYS_EVENT()               (g_stPdRx0AltModeInfo.ucLenovoSystemEvent)
#define SET_PD_RX0_LENOVO_SYS_EVENT(x)              (g_stPdRx0AltModeInfo.ucLenovoSystemEvent = (x))
#define CLR_PD_RX0_LENOVO_SYS_EVENT()               (g_stPdRx0AltModeInfo.ucLenovoSystemEvent = 0)

// Acer Alt Mode Related Macros
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#define GET_PD_RX0_ACER_ALT_MODE_STATE()            (g_stPdRx0AcerAltModeInfo.b6AcerAltModeState)
#define SET_PD_RX0_ACER_ALT_MODE_STATE(x)           (g_stPdRx0AcerAltModeInfo.b6AcerAltModeState = (x))

#define GET_PD_RX0_ACER_ALT_MODE_ENTER()            (g_stPdRx0AcerAltModeInfo.b1AcerAltModeEnter)
#define SET_PD_RX0_ACER_ALT_MODE_ENTER()            (g_stPdRx0AcerAltModeInfo.b1AcerAltModeEnter = _TRUE)
#define CLR_PD_RX0_ACER_ALT_MODE_ENTER()            (g_stPdRx0AcerAltModeInfo.b1AcerAltModeEnter = _FALSE)

#define GET_PD_RX0_ACER_USER_EVENT()                (g_stPdRx0AcerUserEvent.enumEvent)
#define SET_PD_RX0_ACER_USER_EVENT(x)               (g_stPdRx0AcerUserEvent.enumEvent = (g_stPdRx0AcerUserEvent.enumEvent | (x)))
#define CLR_PD_RX0_ACER_USER_EVENT(x)               (g_stPdRx0AcerUserEvent.enumEvent = (g_stPdRx0AcerUserEvent.enumEvent & (EnumTypeCAcerUserEvent)(~(x))))

#define GET_PD_RX0_ACER_USER_VDM_CNT()              (g_stPdRx0AcerUserEvent.b3VdmCnt)
#define SET_PD_RX0_ACER_USER_VDM_CNT(x)             (g_stPdRx0AcerUserEvent.b3VdmCnt = (x))

#define GET_PD_RX0_ACER_USER_VDM_DATA(x)            (g_stPdRx0AcerUserEvent.pucVdmData[x])
#define SET_PD_RX0_ACER_USER_VDM_DATA(x, y)         (g_stPdRx0AcerUserEvent.pucVdmData[x] = (y))

#define GET_PD_RX0_ACER_SYS_EVENT()                 (g_stPdRx0AcerSysEvent.enumEvent)
#define SET_PD_RX0_ACER_SYS_EVENT(x)                (g_stPdRx0AcerSysEvent.enumEvent = (g_stPdRx0AcerSysEvent.enumEvent | (x)))
#define CLR_PD_RX0_ACER_SYS_EVENT(x)                (g_stPdRx0AcerSysEvent.enumEvent = (g_stPdRx0AcerSysEvent.enumEvent & (EnumTypeCAcerSysEvent)(~(x))))

#define GET_PD_RX0_ACER_SYS_VDM_CNT()               (g_stPdRx0AcerSysEvent.b3VdmCnt)
#define SET_PD_RX0_ACER_SYS_VDM_CNT(x)              (g_stPdRx0AcerSysEvent.b3VdmCnt = (x))

#define GET_PD_RX0_ACER_SYS_VDM_DATA(x)             (g_stPdRx0AcerSysEvent.pucVdmData[x])
#define SET_PD_RX0_ACER_SYS_VDM_DATA(x, y)          (g_stPdRx0AcerSysEvent.pucVdmData[x] = (y))
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

// Hp Alt Mode Related Macros
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#define GET_PD_RX0_HP_ALT_MODE_STATE()              (g_stPdRx0HpAltModeInfo.b6HpAltModeState)
#define SET_PD_RX0_HP_ALT_MODE_STATE(x)             (g_stPdRx0HpAltModeInfo.b6HpAltModeState = (x))

#define GET_PD_RX0_HP_ALT_MODE_ENTER()              (g_stPdRx0HpAltModeInfo.b1HpAltModeEnter)
#define SET_PD_RX0_HP_ALT_MODE_ENTER()              (g_stPdRx0HpAltModeInfo.b1HpAltModeEnter = _TRUE)
#define CLR_PD_RX0_HP_ALT_MODE_ENTER()              (g_stPdRx0HpAltModeInfo.b1HpAltModeEnter = _FALSE)

#define GET_PD_RX0_HP_I2C_ADDR()                    (g_stPdRx0HpAltModeInfo.b7HpI2cAddr)
#define SET_PD_RX0_HP_I2C_ADDR(x)                   (g_stPdRx0HpAltModeInfo.b7HpI2cAddr = (x))
#define CLR_PD_RX0_HP_I2C_ADDR()                    (g_stPdRx0HpAltModeInfo.b7HpI2cAddr = 0)

#define GET_PD_RX0_HP_OWN_AM_ADDR_H()               (g_stPdRx0HpAltModeInfo.b2HpOwnAmAddr_H)
#define SET_PD_RX0_HP_OWN_AM_ADDR_H(x)              (g_stPdRx0HpAltModeInfo.b2HpOwnAmAddr_H = (x))
#define CLR_PD_RX0_HP_OWN_AM_ADDR_H()               (g_stPdRx0HpAltModeInfo.b2HpOwnAmAddr_H = 0)

#define GET_PD_RX0_HP_OWN_AM_ADDR_M()               (g_stPdRx0HpAltModeInfo.ucHpOwnAmAddr_M)
#define SET_PD_RX0_HP_OWN_AM_ADDR_M(x)              (g_stPdRx0HpAltModeInfo.ucHpOwnAmAddr_M = (x))
#define CLR_PD_RX0_HP_OWN_AM_ADDR_M()               (g_stPdRx0HpAltModeInfo.ucHpOwnAmAddr_M = 0)

#define GET_PD_RX0_HP_OWN_AM_ADDR_L()               (g_stPdRx0HpAltModeInfo.ucHpOwnAmAddr_L)
#define SET_PD_RX0_HP_OWN_AM_ADDR_L(x)              (g_stPdRx0HpAltModeInfo.ucHpOwnAmAddr_L = (x))
#define CLR_PD_RX0_HP_OWN_AM_ADDR_L()               (g_stPdRx0HpAltModeInfo.ucHpOwnAmAddr_L = 0)

#define GET_PD_RX0_HP_VWIRE_OP()                    (g_stPdRx0HpAltModeInfo.enumHpVwireOp)
#define SET_PD_RX0_HP_VWIRE_OP(x)                   (g_stPdRx0HpAltModeInfo.enumHpVwireOp = (x))

#define GET_PD_RX0_HP_ATTEN_RETRY_CNT()             (g_stPdRx0HpAltModeInfo.b3HpAttenCnt)
#define ADD_PD_RX0_HP_ATTEN_RETRY_CNT()             (g_stPdRx0HpAltModeInfo.b3HpAttenCnt += 1)
#define CLR_PD_RX0_HP_ATTEN_RETRY_CNT()             (g_stPdRx0HpAltModeInfo.b3HpAttenCnt = 0)

#define GET_PD_RX0_HP_ATTEN_TYPE()                  (((BYTE)g_stPdRx0HpAltModeInfo.enumHpAttenType) & (_BIT2 | _BIT1 | _BIT0))
#define SET_PD_RX0_HP_ATTEN_TYPE(x)                 (g_stPdRx0HpAltModeInfo.enumHpAttenType = (x))

#define GET_PD_RX0_HP_USER_EVENT()                  (g_stPdRx0HpUserEvent.enumEvent)
#define SET_PD_RX0_HP_USER_EVENT(x)                 (g_stPdRx0HpUserEvent.enumEvent = (g_stPdRx0HpUserEvent.enumEvent | (x)))
#define CLR_PD_RX0_HP_USER_EVENT(x)                 (g_stPdRx0HpUserEvent.enumEvent = (g_stPdRx0HpUserEvent.enumEvent & (EnumTypeCHpUserEvent)(~(x))))

#define GET_PD_RX0_HP_USER_VDM_CNT()                (g_stPdRx0HpUserEvent.b3VdmCnt)
#define SET_PD_RX0_HP_USER_VDM_CNT(x)               (g_stPdRx0HpUserEvent.b3VdmCnt = (x))

#define GET_PD_RX0_HP_USER_VDM_DATA(x)              (g_stPdRx0HpUserEvent.pucVdmData[x])
#define SET_PD_RX0_HP_USER_VDM_DATA(x, y)           (g_stPdRx0HpUserEvent.pucVdmData[x] = (y))

// HP SysEvent Queue
#define GET_PD_RX0_HP_SYS_EVENT_QUEUE(x)            (g_stPdRx0HpSysEventQueue.pstSysEvent[x])
#define SET_PD_RX0_HP_SYS_EVENT_QUEUE(x, y)         (g_stPdRx0HpSysEventQueue.pstSysEvent[x] = (y))
#define CLR_PD_RX0_HP_SYS_EVENT_QUEUE(x)            (memset(&g_stPdRx0HpSysEventQueue.pstSysEvent[x], 0, sizeof(StructTypeCHpSysEvent)))

#define GET_PD_RX0_HP_SYS_EVENT_QUEUE_CNT()         (g_stPdRx0HpSysEventQueue.b3SysEventCnt)
#define ADD_PD_RX0_HP_SYS_EVENT_QUEUE_CNT()         (g_stPdRx0HpSysEventQueue.b3SysEventCnt += 1)
#define SUB_PD_RX0_HP_SYS_EVENT_QUEUE_CNT()         (g_stPdRx0HpSysEventQueue.b3SysEventCnt -= 1)
#define CLR_PD_RX0_HP_SYS_EVENT_QUEUE_CNT()         (g_stPdRx0HpSysEventQueue.b3SysEventCnt = 0)

#define GET_PD_RX0_HP_SYS_EVENT_QUEUE_HEAD()        (g_stPdRx0HpSysEventQueue.b3SysEventHead)
#define ADD_PD_RX0_HP_SYS_EVENT_QUEUE_HEAD()        (g_stPdRx0HpSysEventQueue.b3SysEventHead = (g_stPdRx0HpSysEventQueue.b3SysEventHead + 1) % _TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE)
#define CLR_PD_RX0_HP_SYS_EVENT_QUEUE_HEAD()        (g_stPdRx0HpSysEventQueue.b3SysEventHead = 0)

#define GET_PD_RX0_HP_SYS_EVENT_QUEUE_TAIL()        (g_stPdRx0HpSysEventQueue.b3SysEventTail)
#define ADD_PD_RX0_HP_SYS_EVENT_QUEUE_TAIL()        (g_stPdRx0HpSysEventQueue.b3SysEventTail = (g_stPdRx0HpSysEventQueue.b3SysEventTail + 1) % _TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE)
#define CLR_PD_RX0_HP_SYS_EVENT_QUEUE_TAIL()        (g_stPdRx0HpSysEventQueue.b3SysEventTail = 0)
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

// Dell Alt Mode Related Macros
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#define GET_PD_RX0_DELL_ALT_MODE_STATE()            (g_stPdRx0DellAltModeInfo.b6DellAltModeState)
#define SET_PD_RX0_DELL_ALT_MODE_STATE(x)           (g_stPdRx0DellAltModeInfo.b6DellAltModeState = (x))

#define GET_PD_RX0_DELL_ALT_MODE_ENTER()            (g_stPdRx0DellAltModeInfo.b1DellAltModeEnter)
#define SET_PD_RX0_DELL_ALT_MODE_ENTER()            (g_stPdRx0DellAltModeInfo.b1DellAltModeEnter = _TRUE)
#define CLR_PD_RX0_DELL_ALT_MODE_ENTER()            (g_stPdRx0DellAltModeInfo.b1DellAltModeEnter = _FALSE)

#define GET_PD_RX0_DELL_AM_ENTER_TIMEOUT()          (g_stPdRx0DellAltModeInfo.b1DellAMTimeout)
#define SET_PD_RX0_DELL_AM_ENTER_TIMEOUT()          (g_stPdRx0DellAltModeInfo.b1DellAMTimeout = _TRUE)
#define CLR_PD_RX0_DELL_AM_ENTER_TIMEOUT()          (g_stPdRx0DellAltModeInfo.b1DellAMTimeout = _FALSE)

#define GET_PD_RX0_DELL_OBJ_POS()                   (g_stPdRx0DellAltModeInfo.b3DellObjPos)
#define SET_PD_RX0_DELL_OBJ_POS(x)                  (g_stPdRx0DellAltModeInfo.b3DellObjPos = (x))
#define CLR_PD_RX0_DELL_OBJ_POS()                   (g_stPdRx0DellAltModeInfo.b3DellObjPos = 0)

#define GET_PD_RX0_DELL_ATTEN_RETRY_CNT()           (g_stPdRx0DellAltModeInfo.b3DellAttenCnt)
#define ADD_PD_RX0_DELL_ATTEN_RETRY_CNT()           (g_stPdRx0DellAltModeInfo.b3DellAttenCnt += 1)
#define CLR_PD_RX0_DELL_ATTEN_RETRY_CNT()           (g_stPdRx0DellAltModeInfo.b3DellAttenCnt = 0)

#define GET_PD_RX0_DELL_ATTEN_WAIT()                (g_stPdRx0DellAltModeInfo.b1DellAttenWait)
#define SET_PD_RX0_DELL_ATTEN_WAIT()                (g_stPdRx0DellAltModeInfo.b1DellAttenWait = _TRUE)
#define CLR_PD_RX0_DELL_ATTEN_WAIT()                (g_stPdRx0DellAltModeInfo.b1DellAttenWait = _FALSE)

#define GET_PD_RX0_DELL_AM_INIT_COMPLETE()          (g_stPdRx0DellAltModeInfo.b1DellInitComplete)
#define SET_PD_RX0_DELL_AM_INIT_COMPLETE()          (g_stPdRx0DellAltModeInfo.b1DellInitComplete = _TRUE)
#define CLR_PD_RX0_DELL_AM_INIT_COMPLETE()          (g_stPdRx0DellAltModeInfo.b1DellInitComplete = _FALSE)

#define GET_PD_RX0_DELL_USER_EVENT()                (g_stPdRx0DellUserEvent.enumEvent)
#define SET_PD_RX0_DELL_USER_EVENT(x)               (g_stPdRx0DellUserEvent.enumEvent = (g_stPdRx0DellUserEvent.enumEvent | (x)))
#define CLR_PD_RX0_DELL_USER_EVENT(x)               (g_stPdRx0DellUserEvent.enumEvent = (g_stPdRx0DellUserEvent.enumEvent & (EnumTypeCDellUserEvent)(~(x))))

#define GET_PD_RX0_DELL_USER_VDM_CNT()              (g_stPdRx0DellUserEvent.b3VdmCnt)
#define SET_PD_RX0_DELL_USER_VDM_CNT(x)             (g_stPdRx0DellUserEvent.b3VdmCnt = (x))

#define GET_PD_RX0_DELL_USER_VDM_DATA(x)            (g_stPdRx0DellUserEvent.pucVdmData[x])
#define SET_PD_RX0_DELL_USER_VDM_DATA(x, y)         (g_stPdRx0DellUserEvent.pucVdmData[x] = (y))

#define GET_PD_RX0_DELL_SYS_EVENT()                 (g_stPdRx0DellSysEvent.enumEvent)
#define SET_PD_RX0_DELL_SYS_EVENT(x)                (g_stPdRx0DellSysEvent.enumEvent = (g_stPdRx0DellSysEvent.enumEvent | (x)))
#define CLR_PD_RX0_DELL_SYS_EVENT(x)                (g_stPdRx0DellSysEvent.enumEvent = (g_stPdRx0DellSysEvent.enumEvent & (EnumTypeCDellSysEvent)(~(x))))

#define GET_PD_RX0_DELL_SYS_VDM_CNT()               (g_stPdRx0DellSysEvent.b3VdmCnt)
#define SET_PD_RX0_DELL_SYS_VDM_CNT(x)              (g_stPdRx0DellSysEvent.b3VdmCnt = (x))

#define GET_PD_RX0_DELL_SYS_VDM_DATA(x)             (g_stPdRx0DellSysEvent.pucVdmData[x])
#define SET_PD_RX0_DELL_SYS_VDM_DATA(x, y)          (g_stPdRx0DellSysEvent.pucVdmData[x] = (y))
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

// Extended Message Info Macros
#define GET_PD_RX0_CHUNKED_MESSAGE()                (g_stExtMsgInfo.b1Chunked)
#define SET_PD_RX0_CHUNKED_MESSAGE(x)               (g_stExtMsgInfo.b1Chunked = (x))

#define GET_PD_RX0_CHUNK_NUMBER()                   (g_stExtMsgInfo.b4ChunkNum)
#define SET_PD_RX0_CHUNK_NUMBER(x)                  (g_stExtMsgInfo.b4ChunkNum = (x))

#define GET_PD_RX0_CHUNK_REQUEST()                  (g_stExtMsgInfo.b1ChunkRequest)
#define SET_PD_RX0_CHUNK_REQUEST(x)                 (g_stExtMsgInfo.b1ChunkRequest = (x))

#define GET_PD_RX0_EXT_MSG_DATA_SIZE()              (g_stExtMsgInfo.b9DataSize)
#define SET_PD_RX0_EXT_MSG_DATA_SIZE(x)             (g_stExtMsgInfo.b9DataSize = (x))

// FW Message Transmission Macro
#define GET_PD_RX0_TRANSMIT_RESULT()                (g_stPdRx0MsgInfo.b5TxResult)
#define SET_PD_RX0_TRANSMIT_RESULT(x)               (g_stPdRx0MsgInfo.b5TxResult = (x))
#define CLR_PD_RX0_TRANSMIT_RESULT()                (g_stPdRx0MsgInfo.b5TxResult = 0)

#define GET_PD_RX0_TRANSMIT_RESULT_EXINT()          (g_stPdRx0MsgInfo.b5TxResult_EXINT)
#define SET_PD_RX0_TRANSMIT_RESULT_EXINT(x)         (g_stPdRx0MsgInfo.b5TxResult_EXINT = (x))
#define CLR_PD_RX0_TRANSMIT_RESULT_EXINT()          (g_stPdRx0MsgInfo.b5TxResult_EXINT = 0)

#define GET_PD_RX0_INT_OVERWRITE()                  (g_stPdRx0MsgInfo.b1IntOverWrite)
#define SET_PD_RX0_INT_OVERWRITE()                  (g_stPdRx0MsgInfo.b1IntOverWrite = _TRUE)
#define CLR_PD_RX0_INT_OVERWRITE()                  (g_stPdRx0MsgInfo.b1IntOverWrite = _FALSE)

#define GET_PD_RX0_FIFO_ERR_STATUS()                (g_stPdRx0MsgInfo.ucFifoRcvErrStatus)
#define SET_PD_RX0_FIFO_ERR_STATUS(x)               (g_stPdRx0MsgInfo.ucFifoRcvErrStatus = (x))

#define GET_PD_RX0_FIFO_CLR()                       (g_stPdRx0MsgInfo.b1FifoClr)
#define SET_PD_RX0_FIFO_CLR()                       (g_stPdRx0MsgInfo.b1FifoClr = _TRUE)
#define CLR_PD_RX0_FIFO_CLR()                       (g_stPdRx0MsgInfo.b1FifoClr = _FALSE)

#define GET_PD_RX0_BUS_IDLE()                       (g_stPdRx0MsgInfo.b1BusIdle)
#define SET_PD_RX0_BUS_IDLE()                       (g_stPdRx0MsgInfo.b1BusIdle = _TRUE)
#define CLR_PD_RX0_BUS_IDLE()                       (g_stPdRx0MsgInfo.b1BusIdle = _FALSE)

#define GET_PD_RX0_RCV_MSG()                        (g_stPdRx0MsgInfo.ucRcvMsg)
#define SET_PD_RX0_RCV_MSG_TYPE(x)                  (g_stPdRx0MsgInfo.ucRcvMsg = g_stPdRx0MsgInfo.ucRcvMsg | (x))
#define SET_PD_RX0_RCV_MSG(x)                       (g_stPdRx0MsgInfo.ucRcvMsg = g_stPdRx0MsgInfo.ucRcvMsg | (x))
#define CLR_PD_RX0_RCV_MSG()                        (g_stPdRx0MsgInfo.ucRcvMsg = 0)

#define GET_PD_RX0_RCV_NOD_CNT()                    ((BYTE)(g_stPdRx0MsgInfo.b3RcvNodCnt))
#define SET_PD_RX0_RCV_NOD_CNT(x)                   (g_stPdRx0MsgInfo.b3RcvNodCnt = (x))

#define GET_PD_RX0_SRC_INIT_AMS()                   (g_stPdRx0MsgInfo.b1SrcInitAms)
#define SET_PD_RX0_SRC_INIT_AMS()                   (g_stPdRx0MsgInfo.b1SrcInitAms = _TRUE)
#define CLR_PD_RX0_SRC_INIT_AMS()                   (g_stPdRx0MsgInfo.b1SrcInitAms = _FALSE)

// BIST Mode Macro
#define GET_PD_RX0_BIST_MODE()                      (g_stPdRx0Status.b4BistMode)
#define SET_PD_RX0_BIST_MODE(x)                     (g_stPdRx0Status.b4BistMode = (x))

#define GET_PD_RX0_RCV_BIST_MSG_CNT()               (g_stPdRx0Status.b2RcvBistMsgCnt)
#define ADD_PD_RX0_RCV_BIST_MSG_CNT()               (g_stPdRx0Status.b2RcvBistMsgCnt += 1)
#define CLR_PD_RX0_RCV_BIST_MSG_CNT()               (g_stPdRx0Status.b2RcvBistMsgCnt = 0)

// Alt Mode HPD Queue Control Macros
#define GET_PD_RX0_HPD_QUEUE(x)                     (g_stHpdQueue.penumHpdType[x])
#define SET_PD_RX0_HPD_QUEUE(x)                     (g_stHpdQueue.penumHpdType[g_stHpdQueue.b2HpdWptr] = (x))
#define CLR_PD_RX0_HPD_QUEUE()                      (g_stHpdQueue.penumHpdType[g_stHpdQueue.b2HpdRptr] = (_PD_HPD_NONE))

#define GET_PD_RX0_HPD_SPACE_TIME(x)                (g_stHpdQueue.pusHpdSpace[x])
#define SET_PD_RX0_HPD_SPACE_TIME(x)                (g_stHpdQueue.pusHpdSpace[g_stHpdQueue.b2HpdWptr] = (x))
#define CLR_PD_RX0_HPD_SPACE_TIME()                 (g_stHpdQueue.pusHpdSpace[g_stHpdQueue.b2HpdRptr] = 0)

#define GET_PD_RX0_HPD_STATUS()                     (g_stHpdQueue.b1HpdStatus)
#define SET_PD_RX0_HPD_STATUS(x)                    (g_stHpdQueue.b1HpdStatus = (x))

#define GET_PD_RX0_HPD_CNT()                        (g_stHpdQueue.b3HpdCnt)
#define ADD_PD_RX0_HPD_CNT()                        (g_stHpdQueue.b3HpdCnt += 1)
#define SUB_PD_RX0_HPD_CNT()                        (g_stHpdQueue.b3HpdCnt -= 1)
#define CLR_PD_RX0_HPD_CNT()                        (g_stHpdQueue.b3HpdCnt = 0)

#define GET_PD_RX0_HPD_WPTR()                       (g_stHpdQueue.b2HpdWptr)
#define ADD_PD_RX0_HPD_WPTR()                       (g_stHpdQueue.b2HpdWptr = (g_stHpdQueue.b2HpdWptr + 1) % 4)
#define CLR_PD_RX0_HPD_WPTR()                       (g_stHpdQueue.b2HpdWptr = 0)

#define GET_PD_RX0_HPD_RPTR()                       (g_stHpdQueue.b2HpdRptr)
#define ADD_PD_RX0_HPD_RPTR()                       (g_stHpdQueue.b2HpdRptr = (g_stHpdQueue.b2HpdRptr + 1) % 4)
#define CLR_PD_RX0_HPD_RPTR()                       (g_stHpdQueue.b2HpdRptr = 0)

// System Request Event Macros
#define GET_PD_RX0_SYS_EVENT()                      (g_stPdEvent.enumSystemEvent)
#define SET_PD_RX0_SYS_EVENT(x)                     (g_stPdEvent.enumSystemEvent = (g_stPdEvent.enumSystemEvent | (x)))
#define CLR_PD_RX0_SYS_EVENT(x)                     (g_stPdEvent.enumSystemEvent = (g_stPdEvent.enumSystemEvent & (EnumPDSysEvent)(~(x))))

// Port Controller Event Macros
#define GET_PD_RX0_PORT_CTRL_EVENT()                (g_stPdEvent.enumPortCtrlEvent)
#define SET_PD_RX0_PORT_CTRL_EVENT(x)               (g_stPdEvent.enumPortCtrlEvent = (g_stPdEvent.enumPortCtrlEvent | (x)))
#define CLR_PD_RX0_PORT_CTRL_EVENT(x)               (g_stPdEvent.enumPortCtrlEvent = (g_stPdEvent.enumPortCtrlEvent & (EnumPDPortCtrlEvent)(~(x))))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPDStatus g_stPdRx0Status;
StructCableStatus g_stPdRx0CableInfo;
StructMsgInfo g_stPdRx0MsgInfo;
StructPdPartnerInfo g_stPdRx0PartnerInfo;
StructAltModeInfo g_stPdRx0AltModeInfo;
StructExtMsgInfo g_stExtMsgInfo;
StructTypeCPDO g_pstSrcPDO[_MAX_DATA_OBJ_CNT];
StructTypeCPDO g_pstPartnerSrcCap[_MAX_DATA_OBJ_CNT];
StructTypeCPDO g_pstSnkPDO[_MAX_DATA_OBJ_CNT];
StructTypeCPDO g_pstPartnerSnkCap[_MAX_DATA_OBJ_CNT];
StructTypeCUserRDO g_stSnkRDO;
StructSnkRDO g_stPartnerRDO;
StructHpdQueue g_stHpdQueue;
StructPdTimerEvent g_stPdTimerEvent;
StructPdEvent g_stPdEvent;
BYTE g_pucDataObject[_MAX_DATA_OBJ_CNT * 4];
BYTE g_pucDataObj_EXINT[_MAX_DATA_OBJ_CNT * 4];
StructPdoStatus g_stPDOStatus;
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
StructAcerAltModeInfo g_stPdRx0AcerAltModeInfo;
StructTypeCAcerSysEvent g_stPdRx0AcerSysEvent;
StructTypeCAcerUserEvent g_stPdRx0AcerUserEvent;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
StructTypeCHpAltModeInfo g_stPdRx0HpAltModeInfo;
StructTypeCHpUserEvent g_stPdRx0HpUserEvent;
StructTypeCHpSysEventQueue g_stPdRx0HpSysEventQueue;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
StructTypeCDellAltModeInfo g_stPdRx0DellAltModeInfo;
StructTypeCDellSysEvent g_stPdRx0DellSysEvent;
StructTypeCDellUserEvent g_stPdRx0DellUserEvent;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
// PD FW Flow Functions
void ScalerTypeCRx0PdClkSel(BYTE ucClockSel);
void ScalerTypeCRx0PdInitial(void);
void ScalerTypeCRx0PdSetPdoByKernel(EnumTypeCPowerRole enumPowerRole);
void ScalerTypeCRx0PdReset(void);
void ScalerTypeCRx0PdAttachedSetting(void);
void ScalerTypeCRx0PdAttachedSetting_EXINT0(void);
// PD FW Main Flow Functions
void ScalerTypeCRx0PdHandler(void);
void ScalerTypeCRx0PdReadyStateProc(void);
void ScalerTypeCRx0PdSrcReadyProc(void);
void ScalerTypeCRx0PdSnkReadyProc(void);
void ScalerTypeCRx0PdCableProc(void);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
void ScalerTypeCRx0PdAltModeProc(void);
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
void ScalerTypeCRx0PdDpAltModeDfpProc(void);
void ScalerTypeCRx0PdDpAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
void ScalerTypeCRx0PdLenovoAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
void ScalerTypeCRx0PdAcerAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
void ScalerTypeCRx0PdHpAltModeUfpProc(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
void ScalerTypeCRx0PdDellAltModeUfpProc(void);
#endif
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

// PD FW Receive Msg Done Flows
void ScalerTypeCRx0PdIntHandler_EXINT0(void);
BYTE ScalerTypeCRx0PdIntClrCheck_EXINT0(void);
void ScalerTypeCRx0PdIntRcvMsgProc_EXINT0(BYTE ucRxProcFifo);
void ScalerTypeCRx0PdIntSrcRcvMsgNoAmsProc_EXINT0(void);
void ScalerTypeCRx0PdIntSnkRcvMsgNoAmsProc_EXINT0(void);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
void ScalerTypeCRx0PdIntDfpRcvVdmMsgProc_EXINT0(void);
#endif
void ScalerTypeCRx0PdIntUfpRcvVdmMsgProc_EXINT0(void);
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
void ScalerTypeCRx0PdIntUfpRcvDpVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
void ScalerTypeCRx0PdIntUfpRcvLenovoVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
void ScalerTypeCRx0PdIntUfpRcvAcerVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
void ScalerTypeCRx0PdIntUfpRcvHpVdmMsgProc_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
void ScalerTypeCRx0PdIntUfpRcvDellVdmMsgProc_EXINT0(void);
#endif
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
void ScalerTypeCRx0PdIntRcvMsgInAmsProc_EXINT0(BYTE ucRxProcFifo);
void ScalerTypeCRx0PdIntRcvCableMsgProc_EXINT0(BYTE ucRxProcFifo);
// PD FW Send Msg EXINT(Send Msg in Interrupt) Done Flows
void ScalerTypeCRx0PdIntTxDoneProc_EXINT0(void);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
void ScalerTypeCRx0PdIntTxVdmDoneProc_EXINT0(void);
#endif
void ScalerTypeCRx0PdTimerEventProc(EnumScalerTimerEventID enumEventID);
void ScalerTypeCRx0PdOcpOvpProc(void);
void ScalerTypeCRx0PdWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
void ScalerTypeCRx0PdPowerSwitch(EnumPowerAction enumPowerAction);

// PD FW Supplementary Functions
EnumPdoCheck ScalerTypeCRx0PdCheckPdoCountChange(BYTE ucPdoCount);
EnumPdoCheck ScalerTypeCRx0PdCheckPdoChange(BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
void ScalerTypeCRx0PdSetFixPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumPDPeakCurType enumPeakCur);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
void ScalerTypeCRx0PdSetArgumentedPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur);
#endif
void ScalerTypeCRx0PdSetRdo(StructTypeCUserRDO stTypeCUserRdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
void ScalerTypeCRx0PdSetProtectInfo(BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo);
#endif
EnumTypeCUFPProductType ScalerTypeCRx0PdGetUFPProductType(void);
EnumTypeCDFPProductType ScalerTypeCRx0PdGetDFPProductType(void);
void ScalerTypeCRx0PdRxFifoClear(EnumRxFifoIndex enumFifo);
void ScalerTypeCRx0PdRxFifoClear_EXINT0(EnumRxFifoIndex enumFifo);
void ScalerTypeCRx0PdUpdateUnconstrainedPow(void);
void ScalerTypeCRx0PdRxIntControl(bit b1Action);
void ScalerTypeCRx0PdRxIntControl_EXINT0(bit b1Action);
void ScalerTypeCRx0PdRxIntControl_WDINT(bit b1Action);
void ScalerTypeCRx0PdUpdateCableRetryCounter(void);
void ScalerTypeCRx0PdUpdatePortPartnerRetryCounter(void);
void ScalerTypeCRx0PdUpdatePortPartnerRetryCounter_EXINT0(void);
void ScalerTypeCRx0PdUpdateTxFifoMsgHeader(void);
void ScalerTypeCRx0PdUpdateTxFifoMsgHeader_EXINT0(void);
void ScalerTypeCRx0PdBackToReadyState(void);
void ScalerTypeCRx0PdBackToReadyState_EXINT0(void);
void ScalerTypeCRx0PdBackToReadyState_WDINT(void);
void ScalerTypeCRx0PdActiveTimerEvent_EXINT0(WORD usTime, EnumScalerTimerEventID enumEventID);
void ScalerTypeCRx0PdUnattachCancelTimerEvent(void);
bit ScalerTypeCRx0PdTxAvaliable(void);
EnumTypeCPDAltModeUrgentStatus ScalerTypeCRx0PdAltModeUrgentEvent(void);
void ScalerTypeCRx0PdSaveCableDiscoverIdAckInfo_EXINT0(void);
BYTE ScalerTypeCRx0PdCheckPowerContractValid_EXINT0(void);
EnumTypeCPDRebuildPowerContract ScalerTypeCRx0PdCheckRebuildPowerContract_EXINT0(void);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
BYTE ScalerTypeCRx0PdSearchSvid_EXINT0(void);
void ScalerTypeCRx0PdSearchMode_EXINT0(void);
BYTE ScalerTypeCRx0PdDfpJudgePinAssignment_EXINT0(void);
EnumDpStatusCheckResult ScalerTypeCRx0PdCheckDpStatus_EXINT0(void);
BYTE ScalerTypeCRx0PdCheckDpConfig_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
void ScalerTypeCRx0PdCheckLenovoStatus_EXINT0(void);
void ScalerTypeCRx0PdCheckLenovoDeviceId_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
void ScalerTypeCRx0PdCheckAcerSysStatus_EXINT0(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
void ScalerTypeCRx0PdSetHpOwnAddr_EXINT0(void);
BYTE ScalerTypeCRx0PdCheckHpVdmValid_EXINT0(void);
void ScalerTypeCRx0PdGetHpSysStatus_EXINT0(EnumTypeCHpSysEvent enumSysEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
void ScalerTypeCRx0PdGetDellSysInfo_EXINT0(void);
#endif
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
bit ScalerTypeCRx0PdGetAltModeReady(void);
EnumTypeCPinCfgType ScalerTypeCRx0PdGetPinAssignment(void);
EnumTypeCPinCfgType ScalerTypeCRx0PdGetPinAssignment_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
EnumTypeCPinCfgType ScalerTypeCRx0PdGetPinAssignment_WDINT(void);
#endif

void ScalerTypeCRx0PdSetPinAssignmentCapability(EnumTypeCPinCfgCapType enumPinAssignmentCap);
void ScalerTypeCRx0PdSetMultiFunctionBit(EnumTypeCMultiFuncStatus enumMultiFunc);
void ScalerTypeCRx0PdWaitDpConfig(void);
void ScalerTypeCRx0PdPushHpd(EnumPDHpdType enumHpdType, WORD usHpdSpaceTime);
void ScalerTypeCRx0PdPushHpd_EXINT0(EnumPDHpdType enumHpdType, WORD usHpdSpaceTime);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
void ScalerTypeCRx0PdPopHpd(void);
void ScalerTypeCRx0PdPopHpd_EXINT0(void);
#endif
#endif
void ScalerTypeCRx0PdClrHpd(void);

// PD Send Message Functions (Main Loop)
void ScalerTypeCRx0PdSendMsg(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructMsg(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructDataObj(EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructVdmDataObj(EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdSendSoftRst(EnumPDPacketType enumPacketType);
void ScalerTypeCRx0PdConstructSoftReset(EnumPDPacketType enumPacketType);
void ScalerTypeCRx0PdSendHardRst(void);
void ScalerTypeCRx0PdProcHardRst(void);
// PD Send Message Functions (Interrupt)
void ScalerTypeCRx0PdSendMsg_EXINT0(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructMsg_EXINT0(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructDataObj_EXINT0(EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
BYTE ScalerTypeCRx0PdSetVdmDataObjCnt_EXINT0(EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructVdmDataObj_EXINT0(EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdSetProductTypeVDO_EXINT0(void);
void ScalerTypeCRx0PdSendMsg_WDINT(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructMsg_WDINT(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdConstructDataObj_WDINT(EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd);
void ScalerTypeCRx0PdSendSoftRst_EXINT0(EnumPDPacketType enumPacketType);
void ScalerTypeCRx0PdConstructSoftReset_EXINT0(EnumPDPacketType enumPacketType);
void ScalerTypeCRx0PdSendHardRst_EXINT0(void);
void ScalerTypeCRx0PdSendHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
void ScalerTypeCRx0PdProcHardRst_EXINT0(void);
void ScalerTypeCRx0PdProcHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

// PD Receive Message Functions (Interrupt)
void ScalerTypeCRx0PdRxInvlidPktFilter_EXINT0(void);
BYTE ScalerTypeCRx0PdRxFifoSelect_EXINT0(void);
void ScalerTypeCRx0PdRxFifoMsgDecode_EXINT0(BYTE ucRxProcFifo);
void ScalerTypeCRx0PdReadDataObj_EXINT0(BYTE ucRxProcFifo);
void ScalerTypeCRx0PdPrlErrHandle_EXINT0(void);
void ScalerTypeCRx0PdRcvSoftRstProc_EXINT0(void);

// PD.c Extern Function
void ScalerTypeCRx0PdSetMaxPower(WORD usMaxPower);
void ScalerTypeCRx0PdSetPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
BYTE ScalerTypeCRx0PdGetPdoCnt(EnumTypeCPowerRole enumPowerRole);
#endif
BYTE ScalerTypeCRx0PdGetPartnerPdoCnt(EnumTypeCPowerRole enumPowerRole);
StructTypeCUserPDO ScalerTypeCRx0PdGetPartnerPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
void ScalerTypeCRx0PdGetPdoStatus(WORD *pusVoltage, WORD *pusCurrent);
StructTypeCUserPDO ScalerTypeCRx0PdGetRequestedSrcPdo(void);
void ScalerTypeCRx0PdSetSystemEvent(EnumPDSysEvent enumPdSysEvent);
#if(((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) || (_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
void ScalerTypeCRx0PdSetSystemEvent_EXINT0(EnumPDSysEvent enumPdSysEvent);
#endif
#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
void ScalerTypeCRx0PdSetSystemEvent_WDINT(EnumPDSysEvent enumPdSysEvent);
#endif
EnumPDPortCtrlEvent ScalerTypeCRx0PdGetPortCtrlEvent(void);
void ScalerTypeCRx0PdClrPortCtrlEvent(EnumPDPortCtrlEvent enumPdPortCtrlEvent);
void ScalerTypeCRx0PdSetFunctionSupport(EnumTypeCFunctionSupport enumFunctionSupport);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
bit ScalerTypeCRx0PdGetLenovoAltModeReady(void);
EnumTypeCLenovoDeviceType ScalerTypeCRx0PdGetLenovoDeviceType(void);
StructTypeCLenovoSysEvent ScalerTypeCRx0PdGetLenovoSystemEvent(void);
void ScalerTypeCRx0PdSetLenovoDockingEvent(StructTypeCLenovoDockEvent stLenovoDockEvent);
bit ScalerTypeCRx0PdCheckLenovoDockingEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
bit ScalerTypeCRx0PdGetAcerAltModeReady(void);
StructTypeCAcerSysEvent ScalerTypeCRx0PdGetAcerSystemEvent(void);
void ScalerTypeCRx0PdSetAcerUserEvent(StructTypeCAcerUserEvent stAcerUserEvent);
EnumTypeCAcerBusyStatus ScalerTypeCRx0PdCheckAcerUserEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
bit ScalerTypeCRx0PdGetHpAltModeReady(void);
StructTypeCHpSysEvent ScalerTypeCRx0PdGetHpSystemEvent(void);
void ScalerTypeCRx0PdSetHpUserEvent(StructTypeCHpUserEvent stHpUserEvent);
EnumTypeCHpBusyStatus ScalerTypeCRx0PdCheckHpUserEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
bit ScalerTypeCRx0PdGetDellAltModeReady(void);
StructTypeCDellSysEvent ScalerTypeCRx0PdGetDellSystemEvent(void);
void ScalerTypeCRx0PdSetDellUserEvent(StructTypeCDellUserEvent stDellUserEvent);
void ScalerTypeCRx0PdSetDellAltModeInitComplete(EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus);
EnumTypeCDellBusyStatus ScalerTypeCRx0PdCheckDellUserEventBusy(void);
EnumTypeCEnterDellAltModeTimeOut ScalerTypeCRx0PdGetEnterDellAltModeTimeOut(void);
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
void  ScalerTypeCRx0PdGetAltModeBillboardInfo(BYTE *pucBillboardAltModeInfo);
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
bit ScalerTypeCRx0PdGetPowerRole(void);
BYTE ScalerTypeCRx0PdGetPowerRole_EXINT0(void);
void ScalerTypeCRx0PdSetPowerRole(bit bRole);
void ScalerTypeCRx0PdSetPowerRole_EXINT0(bit bRole);
bit ScalerTypeCRx0PdGetPowerRoleSwapProcessing(void);
void ScalerTypeCRx0PdClrInteropS8Flag(void);
EnumPDHpdType ScalerTypeCRx0PdGetHPDQueue(BYTE ucIndex);
BYTE ScalerTypeCRx0PdGetHPDQueReadPointer(void);
bit ScalerTypeCRx0PdGetSRCCapSentStatus(void);
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//--------------------------------------------------
// Description  : Type C Rx0 PD Clk Setting (Always Use IOSC = 28MHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdClkSel(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
        // [0x650B] [7:6] Clk Sel = IOSC 28MHz (b'10) / [3:0] sys_clk_div = b'0001
        ScalerSetBit(P65_0B_PD_SYS_CLK_CFG, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT0));

        // [0x650C] clk_1m_div = 28 (b'0001_1100)
        ScalerSetByte(P65_0C_PD_1M_CLK_CFG, 0x1C);

        // [0x650D-0E] clk_1k_div = 1000 (b'11_11101000)
        ScalerSetBit(P65_0D_PD_1K_CLK_CFG0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetByte(P65_0E_PD_1K_CLK_CFG1, 0xE8);

        // ---------- PD Top Setting ----------
        // [0x6506-07] PHY Idle Config : [7:5]Trans Cnt = 3 / [12:0] Trans Wnd = 12us
        ScalerSetByte(P65_06_PD_PHY_IDLE_CFG0, 0x62);
        ScalerSetByte(P65_07_PD_PHY_IDLE_CFG1, 0x30);

        // ---------- PD Tx Setting ----------
        // [0x65D4-D6] Tx Tbit = 297.87K (Spec = 270 - 330K)
        ScalerSetByte(P65_D4_BMC_TX_FW_HT, 0x30);
        ScalerSetBit(P65_D5_BMC_TX_FW_T1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P65_D6_BMC_TX_FW_T0, 0x5E);

        // [0x65D9] Start Drive Count = 100/28 = 3.57us
        ScalerSetByte(P65_D9_TX_BMC_START_DRIVE_CNT, 0x64);

        // ---------- PD Rx Setting ----------
        // [0x6522] [4:1]BMC Filter Glitch of > 28 / 3 Mhz / [0] Use HW Auto Tracking
        ScalerSetBit(P65_22_BMC_RX_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

        // [0X6523-24] BMC Tbit Lower Bound Setting = 250 K (Spec = 270K)
        ScalerSetBit(P65_23_BMC_TBIT_LOW_BND1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P65_24_BMC_TBIT_LOW_BND0, 0x72);

        // [0X6525-26] BMC Tbit Upper Bound Setting = 350 K (Spec = 330K)
        ScalerSetBit(P65_25_BMC_TBIT_UP_BND1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P65_26_BMC_TBIT_UP_BND0, 0x38);

        // [0X652C] Hard Reset Detect Fail FW Solution, BMC Tbit Initial Set to 0x60
        ScalerSetByte(P65_2C_BMC_RX_FW_TBIT0, 0x60);

        // PD Rx fw_cfg_cnt Setting = 0x0D (270~330K)
        ScalerSetByte(P65_58_RX_FIFO0_DUMMY_CELL, 0x18);
    }
    else if(ucClockSel == _M2PLL_CLK)
    {
        // [0x650B] [7:6] Clk Sel = M2PLL 351MHz (b'01) / [3:0] sys_clk_div = b'0011 (351/3 = 117MHz)
        ScalerSetBit(P65_0B_PD_SYS_CLK_CFG, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT1 | _BIT0));

        // [0x650C] clk_1m_div = 117 (b'0111_0101)
        ScalerSetByte(P65_0C_PD_1M_CLK_CFG, 0x75);

        // [0x650D-0E] clk_1k_div = 1000 (b'11_11101000)
        ScalerSetBit(P65_0D_PD_1K_CLK_CFG0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetByte(P65_0E_PD_1K_CLK_CFG1, 0xE8);

        // ---------- PD Top Setting ----------
        // [0x6506-07] PHY Idle Config : [7:5]Trans Cnt = 3 / [12:0] Trans Wnd = 12us
        ScalerSetByte(P65_06_PD_PHY_IDLE_CFG0, 0x69);
        ScalerSetByte(P65_07_PD_PHY_IDLE_CFG1, 0x24);

        // ---------- PD Tx Setting ----------
        // [0x65D4-D6] Tx Tbit = 300.00K (Spec = 270 - 330K)
        ScalerSetByte(P65_D4_BMC_TX_FW_HT, 0xC3);
        ScalerSetBit(P65_D5_BMC_TX_FW_T1, ~(_BIT1 | _BIT0), _BIT0);
        ScalerSetByte(P65_D6_BMC_TX_FW_T0, 0x86);

        // [0x65D9] Start Drive Count = 255/117 = 2.17us
        ScalerSetByte(P65_D9_TX_BMC_START_DRIVE_CNT, 0xFF);

        // ---------- PD Rx Setting ----------
        // [0x6522] [4:1]BMC Filter Glitch of > 117 / 13 Mhz / [0] Use HW Auto Tracking Mode
        ScalerSetBit(P65_22_BMC_RX_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));

        // [0X6523-24] BMC Tbit Lower Bound Setting = 250 K (Spec = 270K)
        ScalerSetBit(P65_23_BMC_TBIT_LOW_BND1, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetByte(P65_24_BMC_TBIT_LOW_BND0, 0x08);

        // [0X6525-26] BMC Tbit Upper Bound Setting = 350 K (Spec = 330K)
        ScalerSetBit(P65_25_BMC_TBIT_UP_BND1, ~(_BIT1 | _BIT0), _BIT0);
        ScalerSetByte(P65_26_BMC_TBIT_UP_BND0, 0x38);
    }
}

//--------------------------------------------------
// Description  : Type C Rx0 PD AC_ON Initail
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdInitial(void)
{
    // ------------------------ PD TOP Initial Setting ------------------------
    // [0x6502] Disable BMC Tx/Rx
    ScalerSetBit(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6505] PHY Hard Reset Detection Option : PHY Need to be Idle in 5 cycle After Receiving Hard Reset/ CabLe Reset
    ScalerSetBit(P65_05_PD_PHY_IDLE_INT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // [0x650A] [1]Tx Transit Only When PHY Idle / [0] Incorrect K-Code Can Accept Up to 5-bit Error
    ScalerSetBit(P65_0A_PD_PHY_TRANSITION_CFG, ~(_BIT1 | _BIT0), _BIT0);

    // ------------------------ PD Rx Initial Setting ------------------------
    // [0x6527] Rx Tbit Config [7:6] Half Tbit Det Region +-25% / [3:2] Ignore Tbit = 16 / [1:0] Tbit Tracking Len = 16
    ScalerSetBit(P65_27_BMC_RX_TBIT_CFG, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // [0x652F] Rx Receive Timeout Config = 2.0ms
    ScalerSetByte(P65_2F_RX_PHY_RCV_TIMEOUT_CFG, 0xC8);

    // [0x6538] Message ID Check Option : [5:4] Check Msg ID != Old Value / [0] Msg. ID Update When GoodCRC Sent Success
    ScalerSetBit(P65_38_RX_PROTOCOL_CFG, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));

    // [0x6539] Rx FIFO Clear Option : Auto Clear GoodCRC, Invalid Pkt, Incorrect CRC, Abn. End, (CRC Resp Fail) Messages
    ScalerSetByte(P65_39_RX_ERROR_FIFO_CLR_CTRL, 0x78);

    // [0x653A] GoodCRC Response Option : [5]Spec Ver = 0 (Tx Spec Ver) / [4]PR/DR = Tx FIFO / [3:0]Do Not Resp. Incorrect CRC Messages
    // [MQP] PHY tests : BMC-PHY-MSG, Tester Send Abnormal Msg. With Correct CRC + EOP, We Shall Return GoodCRC ( _BIT3 = 1 Only Check CRC Correct )
    ScalerSetByte(P65_3A_RX_CRC_RESPONSE_CTRL, 0x88);

    // ------------------------ PD Tx Initial Setting ------------------------
    // [0x65D3] Tx Tbit Setting : [1] Use FW Tbit Setting / [0] Enable Auto Adjust to Even
    ScalerSetBit(P65_D3_BMC_TX_TBIT_CFG, ~(_BIT1 | _BIT0), _BIT0);

    // [0x65D7] Tx Preamble Length = 64
    ScalerSetByte(P65_D7_BMC_TX_PREAMBLE_LN, 0x40);

    // [0x65D8] [7:5]HW Pre Turn On Tx / [4:0]Hold Low Count = 10us
    ScalerSetByte(P65_D8_TX_BMC_HOLD_LOW_CNT, 0x48);

    // [0x65DA] [2] Disable Arbitration [0]Tx Transit to Discarded When Receive Any Message
    ScalerSetBit(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT2 | _BIT0), _BIT0);

    // [0x65EE] Tx CRCReceiver Timer = 1 ms
    ScalerSetByte(P65_EE_TX_PD_CRC_TIMER_CFG, 0x64);

    // Enable PD Function
    SET_PD_RX0_FUNCTION_EN();

    // Enable Alt. Mode Function (DFP can Start Flow / UFP can Resp. Alt. REQ)
    SET_PD_RX0_ALT_MODE_FUNCTION();

    // Clear All Sys Events
    CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_ALL);

    // Set UFP Product Type
#if(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT)
#if(_DP_USB_HUB_SUPPORT == _ON)
    // With Usb Hub IC, UFP Product Type = PDUSB Hub
    SET_PD_RX0_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_HUB);
#else
    // Otherwise, UFP Product Type = PDUSB Peripheral
    SET_PD_RX0_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL);
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
    SET_PD_RX0_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED);
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_HUB)
    SET_PD_RX0_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_HUB);
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
    SET_PD_RX0_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL);
#endif // End of #if(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT)

    // Set DFP Product Type
    SET_PD_RX0_DFP_PRODUCT_TYPE(_TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED);
}

//--------------------------------------------------
// Description  : Type C Rx0 PD Set Src/Snk PDO
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetPdoByKernel(EnumTypeCPowerRole enumPowerRole)
{
    // ------------------------- NOTE -------------------------
    // * Fix Supply PDO Please Use "ScalerTypeCRx0PdSetFixPdo"
    // * Argumented PDO (PPS) Please Use "ScalerTypeCRx0PdSetArgumentedPdo"
    // * 1st PDO Must Be "FIX SUPPLY" With Voltage 5V
    // * According to PD Spec : Max Voltage = 20V, Max Current = 5A
    // * If Set Current > 3A, and FW Cannot Get Cable 5A Cap, Current Will Be Auto Reduce to 3A
    // * For More Info, Ref to PD Spec 10.2
    // --------------------------------------------------------

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Set Type-C Rx0 PDP (PD Power)[Unit = 0.1 W], PDO Power Cannot > PDP
        SET_RX0_MAX_POWER(270);

        // Set Total Number of PDO
        SET_PD_RX0_SRC_PDO_CNT(2);

        // ----------------------- 1st PDO ------------------------
        // Index = 1 (1st PDO Must Be "FIX SUPPLY" With Voltage 5V)
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 50 * 100mV = 5V
        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
        // --------------------------------------------------------
        ScalerTypeCRx0PdSetFixPdo(enumPowerRole, 1, 50, 300, _PD_PEAK_CUR_NONE);

        // ----------------------- 2nd PDO ------------------------
        // Index = 2
        // PDO Type = Fix Supply PDO (Max = 20V / 5A)
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 90 * 100mV = 9V
        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
        // --------------------------------------------------------
        ScalerTypeCRx0PdSetFixPdo(enumPowerRole, 2, 90, 300, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
        SET_PD_RX0_SRC_PDO_CNT(GET_PD_RX0_SRC_PDO_CNT() + 1);

        // ----------------------- 3rd PDO ------------------------
        // Index = 3
        // PDO Type = Programmable Supply PDO (Max = 20V / 5A)
        // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
        // Min Voltage (Unit = 100mV) : 90 * 100mV = 9V
        // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
        // --------------------------------------------------------
        ScalerTypeCRx0PdSetArgumentedPdo(enumPowerRole, 3, 50, 90, 60);
#endif
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Kernel Default Use 1 Sink PDO
        SET_PD_RX0_SNK_PDO_CNT(1);

        // --------------------- 1st Sink PDO ---------------------
        // Index = 1 (1st PDO Must Be "FIX SUPPLY" With Voltage 5V)
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 50 * 100mV = 5V
        // Max Current (Unit = 10mA)  : 50 *  10mA = 500mA
        // --------------------------------------------------------
        ScalerTypeCRx0PdSetFixPdo(enumPowerRole, 1, 50, 50, _PD_PEAK_CUR_NONE);
    }
}

//--------------------------------------------------
// Description  : PD Rx0 Reset For "Unattach" or "Hard Reset"
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdReset(void)
{
    // -------------------- HW Clear, Disable or Reset to Default Value --------------------
    // [0x6502] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6503] Reset CRCReceiver Timer / Retry Counter & Msg. ID Counter / Protocol and PHY Layer FSM
    ScalerSetBit(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P65_32_RX_MSG_ID_RST, ~_BIT3, 0x00);

    // WS111 GRL 2.1.2.1 PHY_BUSIDLE : Reset Rx/Tx Interframe to Default Value
    // [0x6508] Tx Interframe Setting : [6]Interframe Gap Rst When High to Low [5:0] Interframe Gap = 63us
    ScalerSetByte(P65_08_PD_PHY_INTERFRAME_CFG0, 0x3F);

    // CTS TD.PD.PHY.E5 Collision Avoidance Test (Must less than 8)
    // [0x6509] Rx Interframe Setting : [6]Interframe Gap Rst When High to Low [5:0] Interframe Gap = 6us
    ScalerSetByte(P65_09_PD_PHY_INTERFRAME_CFG1, 0x06);

    // Reset SRC BIST Test Data Mode Reply GoodCRC Fail Counter
    CLR_PD_RX0_RCV_BIST_MSG_CNT();

    // [0x65F0] Turn Off BIST Mode
    ScalerSetBit(P65_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // [0x65F5-F6] Clear BIST Mode Error Counter
    ScalerSetByte(P65_F5_PD_BIST_ERROR_CNT1, 0x01);
    ScalerSetByte(P65_F6_PD_BIST_ERROR_CNT0, 0x01);

    // [0x65DB/DC/DD] Clear and Disable Tx IRQs
    ScalerSetBit(P65_DB_TX_PHY_TRANS_INT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P65_DD_TX_PD_MSG_INT_EN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [0x65E8] Clear Tx FIFO
    ScalerSetByte(P65_E0_TX_PACKET_CFG, 0x00);
    ScalerSetBit(P65_E8_TX_FIFO_CTRL, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

    // [0x652E] Clear and Disable Rx PHY Status IRQ
    ScalerSetBit(P65_2E_RX_PHY_ERR_INT, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [0x6543] Clear and Disable Rx Protocol Receive Status IRQ
    ScalerSetByte(P65_43_RX_RCV_STATUS_INT, 0xAA);

    // Clear Rx FIFO 0/1/2
    ScalerTypeCRx0PdRxFifoClear(_PD_RX_FIFO_0);
    ScalerTypeCRx0PdRxFifoClear(_PD_RX_FIFO_1);
    ScalerTypeCRx0PdRxFifoClear(_PD_RX_FIFO_2);

    // ------------------------- FW State & Counter & Flag Reset -------------------------
    // PD Initial States Setting
    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_NONE);
    CLR_PD_RX0_ATTENTION_WAIT();
    CLR_PD_RX0_DP_ALT_MODE_ENTER();
    SET_PD_RX0_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);
    CLR_PD_RX0_DP_ALT_MODE_EXIT_REQ();
    CLR_PD_RX0_SRC_INIT_ALT_MODE();
    CLR_PD_RX0_PARTNER_INIT_ALT_MODE();
    CLR_PD_RX0_PARTNER_ALT_SUPPORT();
    SET_PD_RX0_HPD_STATUS(_LOW);
    SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
    SET_PD_RX0_LENOVO_ALT_STATE(_PD_ALT_MODE_NONE);
    CLR_PD_RX0_LENOVO_ATTN_SENT_FLAG();
    CLR_PD_RX0_LENOVO_ATTN_CNT();
    CLR_PD_RX0_LENOVO_OBJ_POS();
    SET_PD_RX0_LENOVO_DEVICE_TYPE(_TYPE_C_LENOVO_DEVICE_TYPE_NONE);
    CLR_PD_RX0_LENOVO_ALT_MODE_ENTER();
    CLR_PD_RX0_LENOVO_DOCK_EVENT();
    CLR_PD_RX0_LENOVO_SYS_ACKNOWLEDGE();
    CLR_PD_RX0_LENOVO_SYS_EVENT();

    // Reset Acer Alt Mode Flags
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    SET_PD_RX0_ACER_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
    CLR_PD_RX0_ACER_ALT_MODE_ENTER();
    CLR_PD_RX0_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ALL);
    CLR_PD_RX0_ACER_SYS_EVENT(_TYPE_C_ACER_SYS_EVENT_ALL);
#endif

    // Reset Hp Alt Mode Flags
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
    CLR_PD_RX0_HP_ALT_MODE_ENTER();
    CLR_PD_RX0_HP_ATTEN_RETRY_CNT();
    CLR_PD_RX0_HP_I2C_ADDR();
    CLR_PD_RX0_HP_OWN_AM_ADDR_H();
    CLR_PD_RX0_HP_OWN_AM_ADDR_M();
    CLR_PD_RX0_HP_OWN_AM_ADDR_L();
    CLR_PD_RX0_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ALL);
    CLR_PD_RX0_HP_SYS_EVENT_QUEUE_CNT();
    CLR_PD_RX0_HP_SYS_EVENT_QUEUE_HEAD();
    CLR_PD_RX0_HP_SYS_EVENT_QUEUE_TAIL();
#endif

    // Reset Dell Alt Mode Flags
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
    CLR_PD_RX0_DELL_ALT_MODE_ENTER();
    CLR_PD_RX0_DELL_AM_ENTER_TIMEOUT();
    CLR_PD_RX0_DELL_OBJ_POS();
    CLR_PD_RX0_DELL_ATTEN_RETRY_CNT();
    CLR_PD_RX0_DELL_ATTEN_WAIT();
    CLR_PD_RX0_DELL_AM_INIT_COMPLETE();
    CLR_PD_RX0_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ALL);
    CLR_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ALL);
#endif

    // Swith DP Lane Mapping
    ScalerDpRx0SetDpAltModeLaneMapping(GET_PD_RX0_PIN_ASSIGNMENT(), GET_CC_RX0_ORIENTATION());
    ScalerTypeCRx0PdUnattachCancelTimerEvent();
    ScalerTypeCRx0PdClrHpd();

    // Reset Counters
    CLR_DP_RX0_SRC_CAP_CNT();
    ScalerSetBit(P65_01_PHY_STATE_L, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX0_SRC_CAP_CNT());
    CLR_DP_RX0_HARD_RST_CNT();
    CLR_DP_RX0_CHECK_VBUS_CNT();
    CLR_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT();
    CLR_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
    CLR_PD_RX0_CBL_VDM_NO_RESP_CNT();
    CLR_PD_RX0_VDM_BUSY_CNT();

    // Reset Flags
    CLR_PD_RX0_GET_SNK_CAP_SENT();
    CLR_PD_RX0_PRS_REJECT();
    CLR_PD_RX0_DRS_REJECT();
    CLR_PD_RX0_VCS_REJECT();
    CLR_PD_RX0_VCS_SENT();
    CLR_PD_RX0_RCV_SRC_CAP();
    CLR_PD_RX0_RCV_SNK_CAP();
    SET_PD_RX0_UNCONSTRAIN_POWER(_FALSE);
    CLR_PD_RX0_TIMER_EVENT_VALID();
    CLR_PD_RX0_PRS_WAIT_FLAG();
    CLR_PD_RX0_DRS_WAIT_FLAG();
    CLR_PD_RX0_VCS_WAIT_FLAG();
    CLR_PD_RX0_CBL_WAIT_FLAG();
    CLR_PD_RX0_EXPLICIT_CONTRACT();
    SET_PD_RX0_GET_SNK_CAP_WAIT_FLAG();
    CLR_PD_RX0_VDMMSG_WAIT_FLAG();
    CLR_PD_RX0_VDM_BUSY_FLAG();

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
    SET_PD_RX0_SPEC_VER(_PD_VERSION_3_0);
    SET_PD_RX0_CBL_SPEC_VER(_PD_VERSION_3_0);
#else
    SET_PD_RX0_SPEC_VER(_PD_VERSION_2_0);
    SET_PD_RX0_CBL_SPEC_VER(_PD_VERSION_2_0);
#endif

    // Reset Cable Related Flags
    SET_PD_RX0_CBL_MAX_CUR(_PD_DEFAULT_MAX_CUR);
    SET_PD_RX0_CBL_PD_CAPABILITY(_TYPE_C_CABLE_PD_CAP_UNCONFIRMED);
    CLR_PD_RX0_CBL_MODAL_OPERATION_SUPPORT();
    SET_PD_RX0_CBL_PRODUCT_TYPE(_PD_PRODUCT_TYPE_UNDEFINED);
    SET_PD_RX0_CBL_TERMINATION_TYPE(_PD_CBL_TERMINATION_TYPE_UNDEFINED);
    SET_PD_RX0_CBL_VCONN_REQUIRED();
    SET_PD_RX0_CBL_MAX_VOL(200);
    CLR_PD_RX0_CBL_SBU_SUPPORT();
    SET_PD_RX0_CBL_SBU_TYPE(_PD_CBL_SBU_TYPE_UNDEFINED);
    SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_2_ONLY);
    CLR_PD_RX0_CBL_VBUS_THROUGH();
    CLR_PD_RX0_CBL_SOP_PP_SUPPORT();
    SET_PD_RX0_CBL_U3_TO_U0_TRANSITION_MODE(_PD_CBL_U3_TO_U0_UNDEFINED);
    SET_PD_RX0_CBL_ACTIVE_ELEMENT(_PD_CBL_ACTIVE_ELEMENT_UNDEFINED);
    CLR_PD_RX0_CBL_USB_4_SUPPORT();
    CLR_PD_RX0_CBL_USB_3_2_SUPPORT();
    SET_PD_RX0_CBL_LANES_SUPPORT(_PD_CBL_USB_LANES_SUPPORT_UNDEFINED);
    CLR_PD_RX0_CBL_CHARGE_THROUGH_SUPPORT();
    CLR_PD_RX0_CBL_SOFT_RESET_REQUIRED();

    // Clear All Port Partner Info
    SET_PD_RX0_PARTNER_DRP(_FALSE);
    SET_PD_RX0_PARTNER_DRD(_TRUE);
    CLR_PD_RX0_PARTNER_SUSPEND();
    CLR_PD_RX0_PARTNER_EXT_PWR();
    CLR_PD_RX0_PARTNER_USB_CAP();
    CLR_PD_RX0_PARTNER_UNCHK();
    CLR_PD_RX0_PARTNER_HIGH_CAP();
    CLR_PD_RX0_PARTNER_FRS_CUR();
    CLR_PD_RX0_PARTNER_SRC_CAP_CNT();
    CLR_PD_RX0_PARTNER_SNK_CAP_CNT();

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    CLR_PD_RX0_REQ_VOL_SMALL_STEP();
#endif
}

//--------------------------------------------------
// Description  : Set PD to Default State When Attached or After Hard Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdAttachedSetting(void)
{
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        SET_PD_RX0_DATA_ROLE(_PD_DATA_DFP);
        SET_PD_RX0_VCONN_ROLE(_PD_VCONN_SRC);

        // [0x65E5] Setting Tx FIFO [3] Power Role / [2:1] Spec Ver = 2.0 / [0] Data Role For GoodCRC Response
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

        // [0x6534] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
        ScalerSetByte(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // [0x6535-36] Setup Rx Msg Header Data Role/Cable Plug Golden Pattern
        // [5:4] [3:2] [0x6536] Do Not Check Power Role ('b00) / Cable Plug ('b00) / Spec Ver ('b111)
        // [1:0] Check Rcv. SOP Msg Data Role : UFP ('b10)
        // ScalerSetBit(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
        // Do Not Check Data Role For Interop
        ScalerSetBit(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P65_36_RX_SPEC_VER, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        SET_PD_RX0_FW_STATE(_PD_SRC_START_UP);
    }
    else
    {
        SET_PD_RX0_DATA_ROLE(_PD_DATA_UFP);
        SET_PD_RX0_VCONN_ROLE(_PD_VCONN_NOT_SRC);

        // [0x65E5] Setting Tx FIFO [3] Power Role / [2:1] Spec Ver = 2.0 / [0] Data Role For GoodCRC Response
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

        // [0x6534] Setup Rx Valid Packet Type (Not Vconn SRC : SOP / Hard Reset)
        ScalerSetByte(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

        // [0x6535-36] Setup Rx Msg Header Data Role/Cable Plug Golden Pattern
        // [5:4] [3:2] [0x6536] Do Not Check Power Role ('b00) / Cable Plug ('b00) / Spec Ver ('b111)
        // [1:0] Check Rcv. SOP Msg Data Role : DFP (b'11)
        // ScalerSetBit(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        // Do Not Check Data Role For Interop
        ScalerSetBit(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P65_36_RX_SPEC_VER, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        SET_PD_RX0_FW_STATE(_PD_SNK_START_UP);
    }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_PD_FW_DEBUG == _ON))
    DebugMessageTypeC("    [PD / Attached Setting] FW State : ", GET_PD_RX0_FW_STATE());
    DebugMessageTypeC("    ----> Power Role : SNK(0) / SRC(1)", GET_PD_RX0_POWER_ROLE());
    DebugMessageTypeC("    ----> Data  Role : UFP(0) / DFP(1)", GET_PD_RX0_DATA_ROLE());
    DebugMessageTypeC("    ----> Vconn Role : Vconn SRC (0)", GET_PD_RX0_VCONN_ROLE());
#endif
}

//--------------------------------------------------
// Description  : Set PD to Default State When Attached or After Hard Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdAttachedSetting_EXINT0(void) using 1
{
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        SET_PD_RX0_DATA_ROLE(_PD_DATA_DFP);
        SET_PD_RX0_VCONN_ROLE(_PD_VCONN_SRC);

        // [0x65E5] Setting Tx FIFO [3] Power Role / [2:1] Spec Ver = 2.0 / [0] Data Role For GoodCRC Response
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

        // [0x6534] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
        ScalerSetByte_EXINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // [0x6535-36] Setup Rx Msg Header Data Role/Cable Plug Golden Pattern
        // [5:4] [3:2] [0x6536] Do Not Check Power Role ('b00) / Cable Plug ('b00) / Spec Ver ('b111)
        // [1:0] Check Rcv. SOP Msg Data Role : UFP ('b10)
        // ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
        // Do Not Check Data Role For Interop
        ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P65_36_RX_SPEC_VER, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        SET_PD_RX0_FW_STATE(_PD_SRC_START_UP);
    }
    else
    {
        SET_PD_RX0_DATA_ROLE(_PD_DATA_UFP);
        SET_PD_RX0_VCONN_ROLE(_PD_VCONN_NOT_SRC);

        // [0x65E5] Setting Tx FIFO [3] Power Role / [2:1] Spec Ver = 2.0 / [0] Data Role For GoodCRC Response
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

        // [0x6534] Setup Rx Valid Packet Type (Not Vconn SRC : SOP / Hard Reset)
        ScalerSetByte_EXINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

        // [0x6535-36] Setup Rx Msg Header Data Role/Cable Plug Golden Pattern
        // [5:4] [3:2] [0x6536] Do Not Check Power Role ('b00) / Cable Plug ('b00) / Spec Ver ('b111)
        // [1:0] Check Rcv. SOP Msg Data Role : DFP (b'11)
        // ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        // Do Not Check Data Role For Interop
        ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P65_36_RX_SPEC_VER, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        SET_PD_RX0_FW_STATE(_PD_SNK_START_UP);
    }
}

//--------------------------------------------------
// Description  : Main Flow Of PD Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdHandler(void)
{
    // Update Unconstrained Powered Bit
    ScalerTypeCRx0PdUpdateUnconstrainedPow();

    // CTS: Reset Protocol & PHY FSM and Clear Error Flags if Any PHY Error (Frc End or Rcv Timeout) Exists
    if(ScalerGetBit(P65_2E_RX_PHY_ERR_INT, _BIT0) == _BIT0)
    {
        ScalerSetBit(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);
        ScalerSetBit(P65_2E_RX_PHY_ERR_INT, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
    }

#if(_TYPE_C_EMB_CTS_FLOW == _OFF)
    // Hard Reset Detect Fail FW Sol : For Rcv Hard Reset Before Rcv Any Other Msg.
    if((ScalerGetBit(P65_43_RX_RCV_STATUS_INT, _BIT5) == _BIT5) && (ScalerGetBit(P65_2E_RX_PHY_ERR_INT, _BIT2) == _BIT2))
    {
        // [0x6543] Clear SOP Fail IRQ
        ScalerSetBit(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT5));

        // Set fw_cnt = Tracking Tbit + 3
        ScalerSetByte(P65_2C_BMC_RX_FW_TBIT0, (ScalerGetByte(P65_2A_BMC_RX_HW_T0) + 3));

        // Proc Hard Reset
        ScalerTypeCRx0PdProcHardRst();
    }
#endif

    if(GET_PD_RX0_TIMER_EVENT_VALID() == _TRUE)
    {
        // [0x6543] Disable Rx Rcv Msg IRQ
        ScalerTypeCRx0PdRxIntControl(_DISABLE);

        // Active Timer Event and Clear Timer Event Valid
        ScalerTimerActiveTimerEvent(GET_PD_RX0_TIMER_EVENT_CNT(), GET_PD_RX0_TIMER_EVENT_ID());
        CLR_PD_RX0_TIMER_EVENT_VALID();

        // [0x6543] Enable Rx Rcv Msg IRQ
        ScalerTypeCRx0PdRxIntControl(_ENABLE);
    }

    // Write Real-Time FW Info to Reserved Register For Debug
    ScalerSetByte(P65_14_VENDOR_SPECIFIC_SOP1_CFG1, GET_PD_RX0_PIN_ASSIGNMENT());
    ScalerSetByte(P65_15_VENDOR_SPECIFIC_SOP2_CFG0, GET_PD_RX0_FW_STATE());
    ScalerSetByte(P65_16_VENDOR_SPECIFIC_SOP2_CFG1, GET_PD_RX0_SUB_STATE());
    ScalerSetByte(P65_17_VENDOR_SPECIFIC_SOP3_CFG0, GET_PD_RX0_DP_ALT_STATE());
    ScalerSetBit(P65_18_0X6518, ~(_BIT5 | _BIT4 | _BIT3), (GET_PD_RX0_HPD_CNT() << 3));
    ScalerSetBit(P65_18_0X6518, ~(_BIT2 | _BIT1 | _BIT0), ((GET_PD_RX0_CBL_PD_CAPABILITY() << 1) | (GET_PD_RX0_DP_ALT_MODE_CONFIG())));

    switch(GET_PD_RX0_FW_STATE())
    {
        // ------------------------ Source Establish Power Contract Flow ------------------------
        case _PD_SRC_START_UP:
            // From 1. Unattach to Attach   2. After Hard Reset     3. After PR_SWAP    4. After FR_SWAP

            // [0x6503] Reset PHY / Protocol Layer State
            ScalerSetBit(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);

            // Check Vbus = vSafe5V
            if(ScalerTypeCPowerRx0CheckVbusSafe5V() == _TRUE)
            {
#if((_TYPE_C_PMIC_TYPE != _PMIC_NONE) && (_TYPE_C_PMIC_CHECK_SUPPORT == _ON))
                // Start PMIC Protection
                ScalerTypeCPmicRx0ProtectStart();
#endif

                // Do Cable Proc Only When We Are (Vconn SRC) & (Ra Exist), Otherwise CTS Will Fail
                if((GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC) && (GET_RX0_VCONN_STATUS() == _ON))
                {
                    // PD Start Up State and Flag Settings
                    if(GET_PD_RX0_CBL_SOFT_RESET_REQUIRED() == _TRUE)
                    {
                        CLR_PD_RX0_CBL_SOFT_RESET_REQUIRED();

                        // After VCS + PRS, Do Cable Soft Reset
                        SET_PD_RX0_FW_STATE(_PD_SEND_CBL_SOFT_RESET);
                        SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                        SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
                    }
                    else
                    {
                        // After Attach / Hard Reset, Do Cable Discovery
                        SET_PD_RX0_FW_STATE(_PD_SEND_CBL_DISCOVER_ID);
                        SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                        SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                        // SET Wait Flag, and Set TimerEvent to Clear in 70ms
                        SET_PD_RX0_CBL_WAIT_FLAG();
                        ScalerTimerActiveTimerEvent(70, _SCALER_TIMER_EVENT_PD_RX0_CLR_CBL_WAIT);
                    }
                }
                else
                {
                    SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
                }

                // Update FW Usage Flags
                CLR_PD_RX0_EXPLICIT_CONTRACT();
                ScalerSetBit(P65_18_0X6518, ~_BIT7, (GET_PD_RX0_EXPLICIT_CONTRACT() << 7));

                // [0x6503] Enable Protocol Layer State / Run CRCReceiver Timer, Retry Counter & Msg. ID
                ScalerSetBit(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetBit(P65_32_RX_MSG_ID_RST, ~_BIT3, _BIT3);

                // [0x6543] Enable Rx Rcv Msg IRQ
                ScalerTypeCRx0PdRxIntControl(_ENABLE);

                // [0x6543] Clear and Enable Hard Reset IRQ
                ScalerSetBit(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));

                // [0x6502] Enable PHY Layer BMC Tx/Rx
                ScalerSetBit(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

                if(GET_PD_RX0_PRS_PROCESSING() == _TRUE)
                {
                    // PR_SWAP Done, Clear Flag For Retimer Usage, Wait 20ms Before Sending Src_Cap
                    CLR_PD_RX0_PRS_PROCESSING();
                    ScalerTimerDelayXms(_SWAP_SRC_START_TIMER);
                }

                SET_PD_RX0_PARTNER_REQ_VOL(0);

                CLR_PD_RX0_SRC_CAP_SENT_FLAG();
            }

            break;

        case _PD_SEND_CBL_DISCOVER_ID:
        case _PD_SEND_CBL_SOFT_RESET:

            if(GET_PD_RX0_CBL_WAIT_FLAG() == _FALSE)
            {
                // [0x6543] Disable Rx Rcv Msg IRQ
                ScalerTypeCRx0PdRxIntControl(_DISABLE);

                ScalerTypeCRx0PdCableProc();

                // [0x6543] Enable Rx Rcv Msg IRQ
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SRC_SEND_CAP:

#if(_SRC_CAP_NO_RETRY == _TRUE)
            // Do Not Retry Source Capability When Not Rcv. GoodCRC Resp
            ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
            // PD Merged Test [TEST.PD.PROT.SRC3.1] : All PD Message Should Implement 0.9~1.1ms Retry
            // Update Retry Counter According to Spec Version
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0)
            {
                ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
            }
            else
            {
                ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
            }
#endif

            // Only Send 1st Src_Cap in Main Loop "When Attached" or "After PR_SWAP"
            if(GET_PD_RX0_SRC_CAP_SENT_FLAG() == _FALSE)
            {
                SET_PD_RX0_SRC_CAP_SENT_FLAG();

                // Send (Src_Cap)
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);

                // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
                ScalerSetBit(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

                // [0x6543] Enable Rx Rcv Msg IRQ
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        // ------------------------ Sink Establish Power Contract Flow ------------------------
        case _PD_SNK_START_UP:

            // [0x6503] Reset Protocol Layer State, Enable Counter & Timer
            ScalerSetBit(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Check Vbus = vSafe5V (For Hard Reset and PR_SWAP)
            if(ScalerTypeCPowerRx0CheckVbusSafe5V() == _TRUE)
            {
                // Enable Vbus Detection For CC HW to Detect Unattach Event
                ScalerTypeCRx0CcVbusDetCtrl(_ENABLE);

                // Clear Explicit Power Contract and Flags
                CLR_PD_RX0_EXPLICIT_CONTRACT();
                ScalerSetBit(P65_18_0X6518, ~_BIT7, (GET_PD_RX0_EXPLICIT_CONTRACT() << 7));

                // [0x6532/E4] Enable Msg. ID
                ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetBit(P65_32_RX_MSG_ID_RST, ~_BIT3, 0x00);
                ScalerSetBit(P65_32_RX_MSG_ID_RST, ~_BIT3, _BIT3);

                // [0x6543] Enable Rx Rcv Msg IRQ
                ScalerTypeCRx0PdRxIntControl(_ENABLE);

                // [0x6543] Clear and Enable Hard Reset IRQ
                ScalerSetBit(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));

                // [0x6502] Enable PHY Layer BMC Tx/Rx
                ScalerSetBit(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable FSM and Switch State Only When BMC Bus is Idle
                if(ScalerGetBit(P65_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2)
                {
                    // [0x6503] Enable Protocol Layer State / Run CRCReceiver Timer, Retry Counter
                    ScalerSetBit(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

                    // Transit FW_STATE to _PE_SNK_WAIT_CAP and Start Power Negitiation
                    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                    SET_PD_RX0_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                }
                // Cancel Timer Event Which Activiated During Hard Reset Uesd to Prevent Disable Bus Det Deadlock
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER);

                // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                ScalerTimerActiveTimerEvent(_SINK_WAIT_CAP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
            }

            // PR_SWAP Done, Clear Flag For Retimer Usage
            CLR_PD_RX0_PRS_PROCESSING();

            break;

        // ------------------------ Source / Sink Ready to Initaite AMS Flow ------------------------
        case _PD_SRC_READY:
        case _PD_SNK_READY:

            // Process On-Going AMS Flow or Initiate New AMS According to Latest Status
            ScalerTypeCRx0PdReadyStateProc();
            break;

        // ----------------------------- Source / Sink Hard Reset Flow ------------------------------
        case _PD_HARDRESET:

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // If Vbus Turned Off, Wait 0.66~1s and Turn On Power to vSafe5v
                if((GET_PD_RX0_HRST_PWR_OFF() == _FALSE) && (ScalerTypeCPowerRx0CheckVbusSafe0V() == _TRUE))
                {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
                    // Disable Vbus Discharge
                    ScalerTypeCPmicRx0VbusDischarge(_DISABLE);
#endif

                    // Reset PD : WARNING !!! PD Must Reset Before Avtive TURN_ON_POWER Timer , Otherwise, Timer Would Be Canceled
                    ScalerTypeCRx0PdReset();

                    // Set Hard Reset Turn Off Power Flag (Clr When Send/Rcv Hard Reset), and Turn On Power Later
                    SET_PD_RX0_HRST_PWR_OFF();
                    ScalerTimerActiveTimerEvent(_SRC_RECOVER_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER);
                }
                else if((GET_PD_RX0_HRST_PWR_OFF() == _TRUE) && (ScalerTypeCPowerRx0CheckVbusSafe5V() == _TRUE))
                {
                    // If Vbus Has Been Turned On to vSafe5v, Start from SRC_START_UP
                    ScalerTypeCRx0PdAttachedSetting();
                }
            }
            else
            {
                if(ScalerTypeCPowerRx0CheckVbusSafe5V() == _FALSE)
                {
                    ScalerTypeCRx0PdReset();

                    ScalerTypeCRx0PdAttachedSetting();
                }
            }

            break;

        // --------------------------- Source / Sink Main Loop Idle State ---------------------------
        case _PD_SRC_INT_WAIT_REQ:
        case _PD_SRC_INT_SEND_ACCEPT_REQ:
        case _PD_SRC_INT_SEND_REJECT_REQ:
        case _PD_SRC_INT_SEND_WAIT_REQ:
        case _PD_SRC_INT_TRANSIT_POWER:
        case _PD_SNK_INT_WAIT_SRC_CAP:
        case _PD_SNK_INT_SEND_REQUEST:
        case _PD_SNK_INT_WAIT_REQ_RESP:
        case _PD_SNK_INT_WAIT_PS_RDY:
        case _PD_INT_SEND_SOFTRESET:
        case _PD_INT_WAIT_SOFTRESET_RESP:
        case _PD_INT_SEND_SOFTRESET_RESP:
        case _PD_NO_RESPONSE:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For SRC/SNK_READY State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdReadyStateProc(void)
{   // Wait For Source to do PS_RDY or Alt. Mode Flow, Otherwise, Initiate Certain Flow
    // 1. If (DFP) : DR_Swap => Vconn Swap => Alt. Mode => Get_Snk_Cap => PR_SWAP
    // 2. If (UFP) : Get_Snk_Cap => PR_Swap

    if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) && (GET_PD_RX0_SUB_STATE() != _PD_SUB_SRC_READY))
    {
        // VDM Request Has Been Interrupted Before Sending, Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
        CLR_PD_RX0_SRC_INIT_ALT_MODE();
    }

    switch(GET_PD_RX0_SUB_STATE())
    {
        case _PD_SUB_SRC_READY:

            // Disable Rcv Message Int
            ScalerTypeCRx0PdRxIntControl(_DISABLE);

            if(GET_PD_RX0_AMS_STATUS() == _PD_AMS_NONE)
            {
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                if(ScalerTypeCRx0PdAltModeUrgentEvent() == _PD_ALT_MODE_URGENT)
                {
                    ScalerTypeCRx0PdAltModeProc();
                }
                else
#endif
                {
                    // Src Init Message Only When No AMS is On-Going
                    ScalerTypeCRx0PdSrcReadyProc();
                }
            }

            // Enable Rcv Message Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);

            break;

        case _PD_SUB_SNK_READY:

            // Disable Rcv Message Int
            ScalerTypeCRx0PdRxIntControl(_DISABLE);

            if(GET_PD_RX0_AMS_STATUS() == _PD_AMS_NONE)
            {
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                if(ScalerTypeCRx0PdAltModeUrgentEvent() == _PD_ALT_MODE_URGENT)
                {
                    ScalerTypeCRx0PdAltModeProc();
                }
                else
#endif
                {
                    // Src Init Message Only When No AMS is On-Going
                    ScalerTypeCRx0PdSnkReadyProc();
                }
            }

            // To Fix [TD.PD.PHY.E18]
            // If in BIST Mode, Rcv Message Int will not be Enabled
            if(GET_PD_RX0_SUB_STATE() != _PD_SUB_BIST_MODE)
            {
                // Enable Rcv Message Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_SEND_GET_SRC_CAP:

            // Send Message Only When Tx is Avaliable (PD 2.0:Bus Idle / PD 3.0:Src(TxSinkNG) Snk(TxSinkOk)
            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Get Src Cap"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_GET_SRC_CAP, _PD_VDM_CMD_RESERVED);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                    {
                        SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                        SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_SRC_CAP);

                        // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                        ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                    }
                    else
                    {   // Sink Shoud Transit to Ready State, And Should Rcv. Src_Cap Later
                        SET_PD_RX0_SUB_STATE(_PD_SUB_SNK_READY);
                    }
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_SEND_GET_SNK_CAP:

            // Send Message Only When Tx is Avaliable (PD 2.0:Bus Idle / PD 3.0:Src(TxSinkNG) Snk(TxSinkOk)
            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Get Snk Cap"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_GET_SNK_CAP, _PD_VDM_CMD_RESERVED);

                // Set Get Sink Cap Sent Flag
                SET_PD_RX0_GET_SNK_CAP_SENT();

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_SNK_CAP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_SEND_SRC_CAP:

            // Send Message Only When Tx is Avaliable (PD 2.0:Bus Idle / PD 3.0:Src(TxSinkNG) Snk(TxSinkOk)
            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Src Cap"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);

                // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
                ScalerSetBit(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_CABLE_PROC:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                switch(GET_PD_RX0_CBL_STATE())
                {
                    case _PD_CBL_SEND_SOFT_RST:

                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeCRx0PdUpdateCableRetryCounter();

                        // Send Soft Reset(SOP') to Reset Cable
                        ScalerTypeCRx0PdSendSoftRst(_PD_SOP_P_PKT);

                        // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                        ScalerTypeCRx0PdUpdatePortPartnerRetryCounter();

                        if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                        {
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_PD_RX0_CBL_STATE(_PD_CBL_INT_WAIT_SOFT_RST_RESP);

                            // Active Timer Event For Sender Resp. Timer (24-30ms), Timeout : Back to Ready State
                            ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT);
                        }
                        else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                        {
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeCRx0PdUpdateTxFifoMsgHeader();

                            // Back to Ready State
                            ScalerTypeCRx0PdBackToReadyState();
                            SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                        }
                        else
                        {
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            // Back to Ready State
                            ScalerTypeCRx0PdBackToReadyState();
                            SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                        }

                        // Enable Rcv Msg. Int
                        ScalerTypeCRx0PdRxIntControl(_ENABLE);

                        break;

                    case _PD_CBL_SEND_DISCOVER_ID:

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
                        // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp
                        ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeCRx0PdUpdateCableRetryCounter();
#endif

                        // Send Discover ID (SOP') to Get Cable Info
                        ScalerTypeCRx0PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);

                        // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                        ScalerTypeCRx0PdUpdatePortPartnerRetryCounter();

                        if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                        {
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_PD_RX0_CBL_STATE(_PD_CBL_INT_WAIT_DISCOVER_ID_RESP);

                            // Active Timer Event For Sender Resp. Timer (24-30ms), Timeout : Back to Ready State
                            ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT);
                        }
                        else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                        {
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeCRx0PdUpdateTxFifoMsgHeader();

                            ADD_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

                            if(GET_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT() >= _MAX_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
                            {
                                SET_PD_RX0_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                            }

                            // Back to Ready State
                            ScalerTypeCRx0PdBackToReadyState();
                            SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                        }
                        else
                        {
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            // Back to Ready State
                            ScalerTypeCRx0PdBackToReadyState();
                            SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                        }

                        // Enable Rcv Msg. Int
                        ScalerTypeCRx0PdRxIntControl(_ENABLE);

                        break;

                    default:

                        break;
                }
            }

            break;

        case _PD_SUB_SEND_PR_SWAP:

            // Send Message Only When Tx is Avaliable (PD 2.0:Bus Idle / PD 3.0:Src(TxSinkNG) Snk(TxSinkOk)
            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "PR_SWAP"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_PR_SWAP, _PD_VDM_CMD_RESERVED);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_PRS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "ACCEPT / REJECT / WAIT" @ INT
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_PRS_SRC_OFF:

            // Disable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_DISABLE);

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            // Cancel TimerEvent for PPS PDO
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_PPS_TIMEOUT);
#endif

            // 1. When Vubs is Turned Off, Swith Rp -> Rd
            // 2. Disable Vbus Discharge
            // 3. Send PS_RDY Message
            // 4. Active Timer to Wait Vbus On
            if(ScalerTypeCPowerRx0CheckVbusSafe0V() == _TRUE)
            {
                // 1. Change Rd -> Rp (Set CC State to Sink)
                ScalerTypeCRx0CcVbusDetCtrl(_DISABLE);
                ScalerTypeCRx0CcSwitchPowerRole(_PD_POWER_SNK);

#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
                // 2. Disable Vbus Discharge
                ScalerTypeCPmicRx0VbusDischarge(_DISABLE);
#endif

                // 3. Change Power Role to Sink & Send PS_RDY
                SET_PD_RX0_POWER_ROLE(_PD_POWER_SNK);
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);

                // 4. Start Timer Event to Wait New Src to Turn On Vbus
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    ScalerTimerActiveTimerEvent(_PS_SRC_ON_TIMER, _SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_SRC_ON);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendHardRst();
                }
            }

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);
            break;

        case _PD_SUB_INT_SEND_SRC_ON_PSRDY:

            break;

        case _PD_SUB_SEND_DR_SWAP:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "DR_SWAP"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_DR_SWAP, _PD_VDM_CMD_RESERVED);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_DRS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "ACCEPT / REJECT / WAIT" @ INT
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_SEND_VCONN_SWAP:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Vconn_SWAP"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VCONN_SWAP, _PD_VDM_CMD_RESERVED);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_VCS_SENT();
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VCS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "ACCEPT / REJECT / WAIT" @ INT
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_INT_SEND_VCONN_ON_PSRDY:

            break;

        case _PD_SUB_BIST_MODE:

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // For CTS TD.PD.PHY.E16 Valid Hard Reset Framing : BIST & H-RST Msg too Close to Detect H-RST IRQ
            if(ScalerGetByte(P65_54_RX_FIFO0_RCV_SOP) == _BIT3)
            {
                if((ScalerGetByte(P65_55_RX_FIFO0_KCODE_STATUS) == 0x0F) || (ScalerGetByte(P65_55_RX_FIFO0_KCODE_STATUS) == 0x07) || (ScalerGetByte(P65_55_RX_FIFO0_KCODE_STATUS) == 0x0B) ||
                   (ScalerGetByte(P65_55_RX_FIFO0_KCODE_STATUS) == 0x0D) || (ScalerGetByte(P65_55_RX_FIFO0_KCODE_STATUS) == 0x0E))
                {
                    ScalerTypeCRx0PdProcHardRst();
                }
            }
#endif

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
        case _PD_SUB_SEND_GET_STATUS:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Get_status"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_GET_STATUS, _PD_VDM_CMD_RESERVED);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_STATUS);

                    // Turn On Sender Response Timer 24~30 ms, Wait "ACCEPT / REJECT / WAIT" @ INT
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_SEND_ALERT:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                if((GET_PD_RX0_SYS_EVENT() & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP)) != _PD_SYS_EVENT_NONE)
                {
                    // Active Timer Event For Receiving Subsequent AMS, ex: Get_Status Msg., Timeout : Hard Reset
                    ScalerTimerActiveTimerEvent(_ALERT_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
                }

                // Send "Alert"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_ALERT, _PD_VDM_CMD_RESERVED);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    // Set Macro to Avoid Sending Alert Msg. Repeatedly in ReadyProc()
                    SET_PD_RX0_ALERT_SENT();

                    // Set AMS = None
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeCRx0PdBackToReadyState();
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_INT_SEND_NOT_SUPPORT:
#endif
        case _PD_SUB_STATE_NONE:
        case _PD_SUB_INT_WAIT_SNK_CAP:
        case _PD_SUB_INT_WAIT_SRC_CAP:
        case _PD_SUB_INT_SEND_SRC_CAP:
        case _PD_SUB_INT_SEND_SNK_CAP:

        case _PD_SUB_INT_WAIT_PRS_RESP:
        case _PD_SUB_INT_SEND_ACCEPT_PRS:
        case _PD_SUB_INT_WAIT_SRC_ON:
        case _PD_SUB_INT_WAIT_SRC_OFF:

        case _PD_SUB_INT_WAIT_DRS_RESP:
        case _PD_SUB_INT_SEND_ACCEPT_DRS:

        case _PD_SUB_INT_WAIT_VCS_RESP:
        case _PD_SUB_INT_SEND_ACCEPT_VCS:
        case _PD_SUB_INT_WAIT_VCONN_ON:

        case _PD_SUB_INT_SEND_VDM_RESP:
        case _PD_SUB_INT_WAIT_VDM_RESP:

        case _PD_SUB_INT_SEND_REJECT:

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For SRC_READY State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSrcReadyProc(void)
{   // 1. Get Sink Capability First, To Decide to turn on FAST_ROLE SWAP or not
    // 2. DFP : Try to Discover Cable First ,then Get Sink Capability, Do DR_SWAP, If Un-Avaliable, Initiate Alt. Mode
    // 3. UFP : Ultimate Goal, Wait For Partnrt to Initaite Alt. Mode

    if((GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED) && (GET_PD_RX0_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_E))
    {
        // Chrome Book & Lumia which incorrectly select Pin E if it is exist
        SET_TYPE_C_ERROR_RECOVERY();
    }

    // If PD 3.0 & Not During Init Alt Mode Flow, Change Rp to SinkTxOK
    if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0) && (GET_PD_RX0_SRC_INIT_ALT_MODE() == _FALSE))
    {
        ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_OK);
    }

    if((GET_PD_RX0_SYS_EVENT() & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP)) != _PD_SYS_EVENT_NONE)
    {
        ScalerTypeCRx0PdOcpOvpProc();
        return;
    }

    if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
    {
        if((GET_PD_RX0_VCS_REJECT() == _FALSE) && (GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_NOT_SRC) && (GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
        {
            if(GET_PD_RX0_VCS_WAIT_FLAG() == _FALSE)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
            }
        }
        else if((GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC) && (GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
        {
            if(GET_PD_RX0_CBL_SOFT_RESET_REQUIRED() == _TRUE)
            {
                CLR_PD_RX0_CBL_SOFT_RESET_REQUIRED();

                SET_PD_RX0_SUB_STATE(_PD_SUB_CABLE_PROC);
                SET_PD_RX0_CBL_STATE(_PD_CBL_SEND_SOFT_RST);
            }
            else
            {
                if(GET_PD_RX0_VDM_BUSY_FLAG() == _FALSE)
                {
                    SET_PD_RX0_SUB_STATE(_PD_SUB_CABLE_PROC);
                    SET_PD_RX0_CBL_STATE(_PD_CBL_SEND_DISCOVER_ID);
                }
            }
        }
#if(_DFP_SWAP_TO_UFP == _TRUE)
        else if(GET_PD_RX0_GET_SNK_CAP_SENT() == _FALSE)
        {
            if(GET_PD_RX0_GET_SNK_CAP_WAIT_FLAG() == _FALSE)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_GET_SNK_CAP);
            }
            else
            {
                // [Allion 20210318] Ellisys TD.PD.VNDI3.E3. TD.PD.VNDI3.E5 .TD.PD.VNDI3.E7 : Solution: Wait > 10ms to Avoid Check Point. Timeout : Clear GET_SNK_CAP_WAIT_FLAG
                ScalerTimerActiveTimerEvent(10, _SCALER_TIMER_EVENT_PD_RX0_CLR_GET_SNK_CAP_WAIT);
            }
        }
#if(_REFER_TO_PORT_PARTNER_CAP == _TRUE)
        else if((GET_PD_RX0_PARTNER_DRD() == _TRUE) && (GET_PD_RX0_DRS_REJECT() == _FALSE) && (GET_PD_RX0_DP_ALT_STATE() == _PD_ALT_MODE_NONE))
#else
        else if((GET_PD_RX0_DRS_REJECT() == _FALSE) && (GET_PD_RX0_DP_ALT_STATE() == _PD_ALT_MODE_NONE))
#endif
        {
#if(_TYPE_C_DPAM_VERSION <= _DPAM_VERSION_1_0)
            if((GET_PD_RX0_VCS_REJECT() == _FALSE) && (GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC))
            {
                if(GET_PD_RX0_VCS_WAIT_FLAG() == _FALSE)
                {
                    SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else
            {
                if(GET_PD_RX0_DRS_WAIT_FLAG() == _FALSE)
                {
                    SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_DR_SWAP);
                }
            }
#else
            if(GET_PD_RX0_DRS_WAIT_FLAG() == _FALSE)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_DR_SWAP);
            }
#endif  // End of #if(_TYPE_C_DPAM_VERSION <= _DPAM_VERSION_1_0)
        }
        else
#endif  // End of #if(DFP_SWAP_TO_UFP == _TRUE)
        {
            if((GET_PD_RX0_VCS_REJECT() == _FALSE) && (GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_NOT_SRC))
            {
                if(GET_PD_RX0_VCS_WAIT_FLAG() == _FALSE)
                {
                    SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                }
            }
            // Check if System Request to Send Src Cap
            else if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_SRC_CAP);
            }
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            else
            {
                ScalerTypeCRx0PdAltModeProc();
            }
#endif
        }
    }
    else
    {
        if((GET_PD_RX0_PARTNER_ALT_SUPPORT() == _FALSE) || (GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG))
        {
            if((GET_PD_RX0_VCS_REJECT() == _FALSE) &&
               (((GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_NOT_SRC) && (GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0) && (GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)) ||
                ((GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC) && ((GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0) || (GET_PD_RX0_CBL_PD_CAPABILITY() != _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)))))
            {
                // There are two Conditions to Do Vconn_Swap:
                // 1. If (Vconn Not Source) && (PD 3.0) && (Cable Cap == Unconfirmed), Do Vconn_Swap for Cable Discovery.
                // Note: Lecroy [COMMON.PROC.PD.7 UUT Sent Discover Identity Request], As a UFP, It can't Send SOP' Msg to Cable in PD 2.0.
                // 2. If (Vconn Source) && ((PD 2.0) || (Cable Cap != Unconfirmed)), Do Vconn_Swap for Microsoft Surface Laptop 3 Interop Issue.
                // Note: If the FW don't Send Vconn_Swap here, the Port Partner will not Take any Action afterwards. (MM1AE-1999)
                if(GET_PD_RX0_VCS_WAIT_FLAG() == _FALSE)
                {
                    SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else if((GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC) && (GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0) && (GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
            {
                if(GET_PD_RX0_CBL_SOFT_RESET_REQUIRED() == _TRUE)
                {
                    CLR_PD_RX0_CBL_SOFT_RESET_REQUIRED();

                    SET_PD_RX0_SUB_STATE(_PD_SUB_CABLE_PROC);
                    SET_PD_RX0_CBL_STATE(_PD_CBL_SEND_SOFT_RST);
                }
                else
                {
                    if(GET_PD_RX0_VDM_BUSY_FLAG() == _FALSE)
                    {
                        SET_PD_RX0_SUB_STATE(_PD_SUB_CABLE_PROC);
                        SET_PD_RX0_CBL_STATE(_PD_CBL_SEND_DISCOVER_ID);
                    }
                }
            }
            // Check if System Request to Send Src Cap
            else if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_SRC_CAP);
            }
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            else
            {
                ScalerTypeCRx0PdAltModeProc();
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Process For SNK_READY State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSnkReadyProc(void)
{
    if((GET_PD_RX0_SYS_EVENT() & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP)) != _PD_SYS_EVENT_NONE)
    {
        ScalerTypeCRx0PdOcpOvpProc();
        return;
    }

    // Wait For Source to do PS_RDY or Alt. Mode Flow, Otherwise, Initiate Certain Flow
    if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_UFP)
    {
#if(_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
        if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
        {
            if((GET_PD_RX0_PARTNER_ALT_SUPPORT() == _FALSE) || (GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) || (GET_PD_RX0_PARTNER_INIT_ALT_MODE() == _FALSE))
            {
                if(GET_PD_RX0_GET_SNK_CAP_SENT() == _FALSE)
                {
                    if(GET_PD_RX0_GET_SNK_CAP_WAIT_FLAG() == _FALSE)
                    {
                        SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_GET_SNK_CAP);
                    }
                    else
                    {
                        // [Workshop #114] MQP BMC-PHY-MSG (Rev 2.0):Confirm that repeated incoming MessageID is ignored. Solution: Wait > 40ms to avoid check point.
                        ScalerTimerActiveTimerEvent(40, _SCALER_TIMER_EVENT_PD_RX0_CLR_GET_SNK_CAP_WAIT);
                    }
                }
#if(_REFER_TO_PORT_PARTNER_CAP == _TRUE)
                else if((GET_PD_RX0_PARTNER_DRP() == _TRUE) && (GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE) && (GET_PD_RX0_PRS_REJECT() == _FALSE))
#else
                else if((GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE) && (GET_PD_RX0_PRS_REJECT() == _FALSE))
#endif
                {
                    if((GET_PD_RX0_VCS_REJECT() == _FALSE) && (GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_NOT_SRC))
                    {
                        if(GET_PD_RX0_VCS_WAIT_FLAG() == _FALSE)
                        {
                            SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                        }
                    }
                    else
                    {
                        if(GET_PD_RX0_PRS_WAIT_FLAG() == _FALSE)
                        {
                            SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_PR_SWAP);
                        }
                    }
                }
                else if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
                {
                    // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
                }
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                // Try to Do Alt. Mode Flow (Get HPD Queue)
                else
                {
                    ScalerTypeCRx0PdAltModeProc();
                }
#endif
            }
        }
        else
#endif  // End of #if(_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
        {
            // Snk-Only or DRP Do Not Support PR_SWAP, Check Whether Request Event Exist
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
            {
                // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
            }
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            // Try to Do Alt. Mode Flow (Get HPD Queue)
            else
            {
                ScalerTypeCRx0PdAltModeProc();
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Process For Cable Before Power Contract
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdCableProc(void)
{
    switch(GET_PD_RX0_FW_STATE())
    {
        case _PD_SEND_CBL_DISCOVER_ID:

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
            // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp
            ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
            // Update Retry Counter According to Cable Spec Version
            ScalerTypeCRx0PdUpdateCableRetryCounter();
#endif

            // Send Discover ID (SOP') to Get Cable Info
            ScalerTypeCRx0PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);

            // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
            ScalerTypeCRx0PdUpdatePortPartnerRetryCounter();

            if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
            {
                SET_PD_RX0_FW_STATE(_PD_INT_WAIT_CBL_DISCOVER_ID_RESP);
                SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);

                // Active Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Src_Cap
                ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT);
            }
            else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
            {
                ADD_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

                // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                ScalerTypeCRx0PdUpdateTxFifoMsgHeader();

                // If Retry Fail, Set FW State to Continue On-going PD Flow
                SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);
            }
            else
            {
                ScalerTypeCRx0PdSendHardRst();
            }

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);

            break;

        case _PD_SEND_CBL_SOFT_RESET:

            // Update Retry Counter According to Cable Spec Version
            ScalerTypeCRx0PdUpdateCableRetryCounter();

            ScalerTypeCRx0PdSendSoftRst(_PD_SOP_P_PKT);

            // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
            ScalerTypeCRx0PdUpdatePortPartnerRetryCounter();

            if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
            {
                SET_PD_RX0_FW_STATE(_PD_INT_WAIT_CBL_SOFT_RESET_RESP);
                SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);

                // Active Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Discover ID(SOP')
                ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT);
            }
            else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
            {
                // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                ScalerTypeCRx0PdUpdateTxFifoMsgHeader();

                // Cable Soft Reset Retry Fail, Back to Discover ID
                SET_PD_RX0_FW_STATE(_PD_SEND_CBL_DISCOVER_ID);
            }
            else
            {
                ScalerTypeCRx0PdSendHardRst();
            }

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);

            break;

        default:

            break;
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdAltModeProc(void)
{
    if(GET_PD_RX0_ALT_MODE_FUNCTION() == _TRUE)
    {
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
        // Send Message Only When Data Role = DFP, and Alt Mode Not in Error State
        if((GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP) && (GET_PD_RX0_DP_ALT_STATE() != _PD_ALT_MODE_ERROR) && (GET_PD_RX0_PARTNER_VDM_NO_RESP_CNT() < _MAX_VDM_NO_RESP_CNT))
        {
            if(GET_PD_RX0_VDMMSG_WAIT_FLAG() == _TRUE)
            {
                ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_PD_RX0_CLR_VDMMSG_WAIT);
            }
            else
            {
                ScalerTypeCRx0PdDpAltModeDfpProc();
            }
        }
        else
#endif
        {
            if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_UFP)
            {
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
                if(ScalerTypeCRx0PdGetAltModeReady() == _TRUE)
                {
                    ScalerTypeCRx0PdDpAltModeUfpProc();
                }

                if(GET_PD_RX0_FW_STATE() == _PD_INT_SEND_SOFTRESET)
                {
                    return;
                }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
                if(ScalerTypeCRx0PdGetLenovoAltModeReady() == _TRUE)
                {
                    ScalerTypeCRx0PdLenovoAltModeUfpProc();
                }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
                if(ScalerTypeCRx0PdGetAcerAltModeReady() == _TRUE)
                {
                    ScalerTypeCRx0PdAcerAltModeUfpProc();
                }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
                if(ScalerTypeCRx0PdGetHpAltModeReady() == _TRUE)
                {
                    ScalerTypeCRx0PdHpAltModeUfpProc();
                }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                if(ScalerTypeCRx0PdGetDellAltModeReady() == _TRUE)
                {
                    ScalerTypeCRx0PdDellAltModeUfpProc();
                }
#endif
            }
        }
    }
}

#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For DFP Dp Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdDpAltModeDfpProc(void)
{
    switch(GET_PD_RX0_DP_ALT_STATE())
    {
        case _PD_ALT_MODE_NONE:

            // DFP Waits 50ms then Starts Alt Mode
            ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_PD_RX0_DFP_START_ALT_MODE);

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_ID:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Discover ID REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_ID
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_SVID:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Discover SVID REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_REQ);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_SVID
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_MODE:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Discover Mode REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_REQ);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_MODE
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }

            break;

        case _PD_ALT_MODE_SEND_ENTER_MODE:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Enter Mode REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_REQ);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP);

                    // Turn On VDMModeEntryTimer 40~50 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send ENTER_MODE
                    ScalerTimerActiveTimerEvent(_VDM_MODE_ENTRY_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }

            break;

        case _PD_ALT_MODE_SEND_DP_STATUS:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "DP Status REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send DP_STATUS
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "DP Config REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_11);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send DP_CONFIG
                    ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }

            break;

        case _PD_ALT_MODE_READY:

            if((ScalerTypeCRx0PdGetAltModeReady() == _TRUE) && (GET_PD_RX0_HPD_CNT() > 0) && (GET_PD_RX0_ATTENTION_WAIT() == _FALSE))
            {
                if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
                {
                    // Send "DP Status REQ"
                    ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);

                    // Read Transmit Result
                    if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                    {
                        SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                        SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);

                        // Turn On Sender Response Timer 24~30 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send DP_STATUS
                        ScalerTimerActiveTimerEvent(_SENDER_RESP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                    }
                    else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                    {
                        ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                    }

                    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                    {
                        // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                        CLR_PD_RX0_SRC_INIT_ALT_MODE();
                    }

                    // Enable Rcv Msg. Int
                    ScalerTypeCRx0PdRxIntControl(_ENABLE);
                }
                else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                    SET_PD_RX0_SRC_INIT_ALT_MODE();
                }
            }

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE:

            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Exit Mode REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_REQ);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP);

                    // Turn On VDMModeExitTimer 40~50 ms, Timeout : back to Sub SRC/SNK Ready and Re-Send EXIT_MODE
                    ScalerTimerActiveTimerEvent(_VDM_MODE_EXIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For UFP Dp Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdDpAltModeUfpProc(void)
{
    if((GET_PD_RX0_HPD_CNT() > 0) && (GET_PD_RX0_ATTENTION_WAIT() == _FALSE))
    {
        if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
        {
            SET_PD_RX0_ATTN_TYPE(_PD_DP_ATTENTION);

            // Send "Attention REQ"
            ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

            // Read Transmit Result
            if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
            {
                // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                if(GET_PD_RX0_HPD_SPACE_TIME(GET_PD_RX0_HPD_RPTR()) != 0)
                {
                    SET_PD_RX0_ATTENTION_WAIT();
                    ScalerTimerActiveTimerEvent(GET_PD_RX0_HPD_SPACE_TIME(GET_PD_RX0_HPD_RPTR()), _SCALER_TIMER_EVENT_PD_RX0_CLR_ATTENTION_WAIT);
                }

                // Pop Out One HPD From Queue
                ScalerTypeCRx0PdPopHpd();

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCRx0PdBackToReadyState();
            }
            else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
            {
                ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
            }

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                CLR_PD_RX0_SRC_INIT_ALT_MODE();
            }

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);
        }
        else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
            SET_PD_RX0_SRC_INIT_ALT_MODE();
        }
    }
}
#endif // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Lenovo Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdLenovoAltModeUfpProc(void)
{
    if((GET_PD_RX0_LENOVO_DOCK_EVENT() != 0x00) && (GET_PD_RX0_LENOVO_ATTN_SENT_FLAG() == _FALSE))
    {
        if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
        {
            if(GET_PD_RX0_LENOVO_ATTN_CNT() < _MAX_LENOVO_ATTN_CNT)
            {
                SET_PD_RX0_ATTN_TYPE(_PD_LENOVO_ATTENTION);

                // Send "Lenovo Attention REQ"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_LENOVO_ATTN_SENT_FLAG();
                    ADD_PD_RX0_LENOVO_ATTN_CNT();

                    // Wait 300ms and Re-Send Lenovo Attention
                    ScalerTimerActiveTimerEvent(300, _SCALER_TIMER_EVENT_PD_RX0_LENOVO_RESP_TIMEOUT);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }
            }
            else
            {
                // Send "Lenovo Get_Status ACK (0x50)"
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_LENOVO_CMD_GET_STATUS_ACK);

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    CLR_PD_RX0_LENOVO_ATTN_CNT();
                    CLR_PD_RX0_LENOVO_DOCK_EVENT();
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }
            }

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                CLR_PD_RX0_SRC_INIT_ALT_MODE();
            }

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);
        }
        else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
            SET_PD_RX0_SRC_INIT_ALT_MODE();
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Acer Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdAcerAltModeUfpProc(void)
{
    if((GET_PD_RX0_ACER_USER_EVENT() & _TYPE_C_ACER_USER_EVENT_ATTENTION) == _TYPE_C_ACER_USER_EVENT_ATTENTION)
    {
        if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
        {
            // Send "Attention REQ"
            ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_ACER_CMD_ATTENTION_REQ);

            // Read Transmit Result
            if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
            {
                // Clear Attention Event Once Message Has Been Sent
                CLR_PD_RX0_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ATTENTION);
            }
            else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
            {
                ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
            }

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                CLR_PD_RX0_SRC_INIT_ALT_MODE();
            }

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);
        }
        else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
            SET_PD_RX0_SRC_INIT_ALT_MODE();
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Hp Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdHpAltModeUfpProc(void)
{
    if((GET_PD_RX0_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_ATTEN_CONFIG) == _TYPE_C_HP_USER_EVENT_ATTEN_CONFIG)
    {
        if(GET_PD_RX0_HP_ATTEN_RETRY_CNT() < 3)
        {
            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                // Send "Hp Atten_config"
                SET_PD_RX0_ATTN_TYPE(_PD_HP_ATTENTION);
                SET_PD_RX0_HP_ATTEN_TYPE(_PD_HP_ATTEN_CONFIG);
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                // Retry Fail CNT, for Atten_config
                ADD_PD_RX0_HP_ATTEN_RETRY_CNT();

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    // Clear Attention Event Once Message Has Been Sent
                    CLR_PD_RX0_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_CONFIG);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }
        }
        else
        {
            // If Retry fail > 3, Clear User Event and Atten_retry_CNT
            CLR_PD_RX0_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_CONFIG);
            CLR_PD_RX0_HP_ATTEN_RETRY_CNT();
        }
    }
    else if((GET_PD_RX0_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK) == _TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK)
    {
        if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
        {
            // Send "Hp Set_vwire Sample ACK" (0x52)"
            ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_52);

            // Read Transmit Result
            if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
            {
                // Clear User Event Once Message Has Been Sent
                CLR_PD_RX0_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK);
            }
            else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
            {
                ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
            }

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                CLR_PD_RX0_SRC_INIT_ALT_MODE();
            }

            SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);
        }
        else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
            SET_PD_RX0_SRC_INIT_ALT_MODE();
        }
    }
    else if((GET_PD_RX0_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_ATTEN_VWIRE) == _TYPE_C_HP_USER_EVENT_ATTEN_VWIRE)
    {
        if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
        {
            // Send "Hp Atten_vwire"
            SET_PD_RX0_ATTN_TYPE(_PD_HP_ATTENTION);
            SET_PD_RX0_HP_ATTEN_TYPE(_PD_HP_ATTEN_VWIRE);
            ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

            // Read Transmit Result
            if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
            {
                // Clear Attention Event Once Message Has Been Sent
                CLR_PD_RX0_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_VWIRE);
            }
            else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
            {
                ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
            }

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                CLR_PD_RX0_SRC_INIT_ALT_MODE();
            }

            SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);
        }
        else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
            SET_PD_RX0_SRC_INIT_ALT_MODE();
        }
    }
    else if((GET_PD_RX0_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_ATTEN_DATA) == _TYPE_C_HP_USER_EVENT_ATTEN_DATA)
    {
        if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
        {
            // Send "Hp Atten_data"
            SET_PD_RX0_ATTN_TYPE(_PD_HP_ATTENTION);
            SET_PD_RX0_HP_ATTEN_TYPE(_PD_HP_ATTEN_DATA);
            ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

            // Read Transmit Result
            if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
            {
                // Clear Attention Event Once Message Has Been Sent
                CLR_PD_RX0_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_DATA);
            }
            else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
            {
                ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
            }

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                CLR_PD_RX0_SRC_INIT_ALT_MODE();
            }

            SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

            // Enable Rcv Msg. Int
            ScalerTypeCRx0PdRxIntControl(_ENABLE);
        }
        else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
            SET_PD_RX0_SRC_INIT_ALT_MODE();
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Dell Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdDellAltModeUfpProc(void)
{
    if(((GET_PD_RX0_DELL_USER_EVENT() & _TYPE_C_DELL_USER_EVENT_ATTEN) == _TYPE_C_DELL_USER_EVENT_ATTEN) && (GET_PD_RX0_DELL_ATTEN_WAIT() == _FALSE))
    {
        if(GET_PD_RX0_DELL_ATTEN_RETRY_CNT() < 3)
        {
            if(ScalerTypeCRx0PdTxAvaliable() == _TRUE)
            {
                SET_PD_RX0_ATTN_TYPE(_PD_DELL_ATTENTION);

                // Send "Dell Attention REQ"
                SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_SEND_DELL_ATTEN);
                ScalerTypeCRx0PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                // Set Attention Wait Flag, Avoid Sending Attention all the Time
                SET_PD_RX0_DELL_ATTEN_WAIT();

                // Read Transmit Result
                if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_SUCCESS)
                {
                    SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_WAIT_DELL_0X13);

                    // Active Timer Event For Dell Attention Retry Timer (30ms), Timeout : ADD_PD_RX0_DELL_ATTEN_RETRY_CNT()
                    ScalerTimerActiveTimerEvent(_TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER, _SCALER_TIMER_EVENT_PD_RX0_DELL_ATTEN_RETRY);
                }
                else if(GET_PD_RX0_TRANSMIT_RESULT() == _PD_SENT_RETRY_FAIL)
                {
                    // Clear Dell Related Macros and Set Atten_NoResponse System Event
                    CLR_PD_RX0_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                    CLR_PD_RX0_DELL_ATTEN_RETRY_CNT();
                    CLR_PD_RX0_DELL_ATTEN_WAIT();
                    SET_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_NORESPONSE);
                    SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

                    ScalerTypeCRx0PdSendSoftRst(_PD_SOP_PKT);
                }

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
                    CLR_PD_RX0_SRC_INIT_ALT_MODE();
                }

                // Enable Rcv Msg. Int
                ScalerTypeCRx0PdRxIntControl(_ENABLE);
            }
            else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                // Set Init Alt Mode Flag to Prevent SrcReady From Setting Rp to SinkTxOK
                SET_PD_RX0_SRC_INIT_ALT_MODE();
            }
        }
        else
        {
            // If Retry fail > 3, Clear Dell Related Macros and Set Atten_NoResponse System Event
            CLR_PD_RX0_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
            CLR_PD_RX0_DELL_ATTEN_RETRY_CNT();
            CLR_PD_RX0_DELL_ATTEN_WAIT();
            SET_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_NORESPONSE);
            SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Interrupt Handler For PD Controller
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntHandler_EXINT0(void) using 1
{
    BYTE ucRxProcFifo = _PD_RX_FIFO_RSV;

    if(GET_PD_RX0_FUNCTION_EN() == _TRUE)
    {
        // ==================== "Hard Reset IRQ" =========================
        if(ScalerGetBit_EXINT(P65_43_RX_RCV_STATUS_INT, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // (rx_rcv_hardreset_irq == 1) & (irq_en = Enable)
            ScalerTypeCRx0PdProcHardRst_EXINT0();
        }

        // ================= " Rx FIFO RCV MSG IRQ " =====================
        if(ScalerGetBit_EXINT(P65_43_RX_RCV_STATUS_INT, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // (rx_msg_rcv_done_irq = 1) & (irq_en = Enable)
            // 1. Filter Invalid Packet (invlid_pkt || crc_err || abn_msg || goodcrc_fail || msg_id_err)
            ScalerTypeCRx0PdRxInvlidPktFilter_EXINT0();

            if(ScalerGetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, (_BIT2 | _BIT1 | _BIT0)) != 0x00)
            {
                // Check if BMC Channel and Rx PTCL State are Idle
                if((ScalerGetBit_EXINT(P65_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2) && (ScalerGetByte_EXINT(P65_21_RX_STATE_MACHINE_L) == _BIT0))
                {
                    SET_PD_RX0_BUS_IDLE();
                }
                else
                {
                    CLR_PD_RX0_BUS_IDLE();
                }

                // 2. Select FIFO to Process and Set FIFO Clear Flag
                ucRxProcFifo = ScalerTypeCRx0PdRxFifoSelect_EXINT0();
                SET_PD_RX0_FIFO_CLR();

                // 3. Check Message Header OK
                SET_PD_RX0_FIFO_ERR_STATUS(ScalerGetByte_EXINT(P65_53_RX_FIFO0_MSG_MIS_FLAG + (ucRxProcFifo * 0x20)));

                if(GET_PD_RX0_FIFO_ERR_STATUS() == _PD_RX_MSG_CORRECT)
                {
                    // Notify Main Loop that Send Msg Has Been Interrupted
                    SET_PD_RX0_INT_OVERWRITE();

                    // 4. Decode Rcv. Msg, and Proc According to Current State
                    ScalerTypeCRx0PdRxFifoMsgDecode_EXINT0(ucRxProcFifo);

                    // 5. Process FIFO According to Current State and Rcv. Message
                    if(ScalerGetByte_EXINT(P65_54_RX_FIFO0_RCV_SOP + (ucRxProcFifo * 0x20)) == _BIT0)
                    {
                        // Rcv SOP Packet
                        if(GET_PD_RX0_RCV_MSG() == _PD_CMD_SOFT_RESET)
                        {
                            ScalerTypeCRx0PdRcvSoftRstProc_EXINT0();
                        }
                        else
                        {
                            ScalerTypeCRx0PdIntRcvMsgProc_EXINT0(ucRxProcFifo);
                        }
                    }
                    else if((ScalerGetByte_EXINT(P65_54_RX_FIFO0_RCV_SOP + (ucRxProcFifo * 0x20)) == _BIT1) ||
                            (ScalerGetByte_EXINT(P65_54_RX_FIFO0_RCV_SOP + (ucRxProcFifo * 0x20)) == _BIT2))
                    {   // Rcv SOP'/SOP" Packet
                        ScalerTypeCRx0PdIntRcvCableMsgProc_EXINT0(ucRxProcFifo);
                    }
                }

                // 6. Clear Processed FIFO
                if(GET_PD_RX0_FIFO_CLR() == _TRUE)
                {
                    ScalerTypeCRx0PdRxFifoClear_EXINT0(ucRxProcFifo);
                }
            }

            // 7. Clear PHY Error Flags
            // ScalerSetBit_EXINT(P65_2E_RX_PHY_ERR_INT, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            if((ScalerGetByte_EXINT(P65_42_RX_FIFO_GENERAL_INFO) & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
            {   // 8. Clear rx_msg_rcv_done_irq Only When FIFO0/1/2 Are Empty
                ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);
            }
        }

        // ================ " MSG TRANSMISSION DONE @ INT " ====================
        if((ScalerGetBit_EXINT(P65_DC_TX_PD_MSG_INT, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, _BIT5) == _BIT5))
        {   // (tx_prl_trans_done_irq = TRUE) && (tx_prl_trans_done_irq_en = ENABLE)
            ScalerTypeCRx0PdIntTxDoneProc_EXINT0();
        }
    }
}

//--------------------------------------------------
// Description  : Check If All CC Enabled IRQ is Clear Or Not
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCRx0PdIntClrCheck_EXINT0(void) using 1
{
    // Return False, if Any of PD IRQs is Enable and Has Not Been Processed
    if((ScalerGetBit_EXINT(P65_43_RX_RCV_STATUS_INT, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2)) ||
       (ScalerGetBit_EXINT(P65_43_RX_RCV_STATUS_INT, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) ||
       ((ScalerGetBit_EXINT(P65_DC_TX_PD_MSG_INT, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, _BIT5) == _BIT5)))
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Process When Rcv. Msg. in Interrupt Before Ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntRcvMsgProc_EXINT0(BYTE ucRxProcFifo) using 1
{   // Rcv. Msg. Not Soft Reset or Undefined Message
    switch(GET_PD_RX0_FW_STATE())
    {
        case _PD_SRC_INT_WAIT_REQ:

            // Cancel TimerEvent(from _PD_SRC_SEND_CAP) & WDTimerEvent (from _PD_SUB_INT_SEND_SRC_CAP)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);

            // Hard Reset Detect Fail FW Sol : For Rcv Hard Reset Before Rcv Any Other Msg.
            ScalerSetByte_EXINT(P65_2C_BMC_RX_FW_TBIT0, (ScalerGetByte_EXINT(P65_2A_BMC_RX_HW_T0) + 3));

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_REQUEST)
            {
                // 1. Get Port Partner's Spec Version, and decide the version for communication
                if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0) ||
                   ((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (_BIT7 | _BIT6)) == _BIT6))
                {   // if(Our PD Version is 2.0 || Port Partner Support Only PD 2.0)

                    // Change Spec Vesion to PD 2.0
                    SET_PD_RX0_SPEC_VER(_PD_VERSION_2_0);

                    // Change Cable Spec Vesion to PD 2.0
                    SET_PD_RX0_CBL_SPEC_VER(_PD_VERSION_2_0);
                }
                else
                {
                    // Change Spec Vesion to PD 3.0
                    SET_PD_RX0_SPEC_VER(_PD_VERSION_3_0);
                }

                // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                ScalerTypeCRx0PdUpdatePortPartnerRetryCounter_EXINT0();

                // 2. Get Requested Object Position and Current for Evaluation
                SET_PD_RX0_PARTNER_OBJ_POS((g_pucDataObj_EXINT[0] & (_BIT6 | _BIT5 | _BIT4)) >> 4);

                // 3. Negotiate Requested Power
                // if(Accpet)       => Send Accept and Transit to "_PE_SRC_TRANSIT_POWER"
                // if(Cannot Meet)  => Send Reject, No Pwr. Contract -> "_PE_SRC_SEND_CAP" / Pwr. Contract -> "_PE_SRC_READY"
                if((GET_PD_RX0_PARTNER_OBJ_POS() > 0) && (GET_PD_RX0_PARTNER_OBJ_POS() <= GET_PD_RX0_SRC_PDO_CNT()))
                {
                    if(GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        // Get Fix Supply RDO Operating / Max Current (Unit = 10mA)
                        SET_PD_RX0_PARTNER_OP_CUR((((WORD)(g_pucDataObj_EXINT[1] & 0x0F)) << 6) | (((WORD)(g_pucDataObj_EXINT[2] & 0xFC)) >> 2));
                        SET_PD_RX0_PARTNER_MAX_CUR((((WORD)(g_pucDataObj_EXINT[2] & 0x03)) << 8) | ((WORD)g_pucDataObj_EXINT[3]));

                        // Check if Requested "Operating Current" <= Src PDO Current / Cable Max Current
                        if((GET_PD_RX0_PARTNER_OP_CUR() <= GET_PD_RX0_SRC_CAP_CUR(GET_PD_RX0_PARTNER_OBJ_POS() - 1)) &&
                           (GET_PD_RX0_PARTNER_OP_CUR() <= GET_PD_RX0_CBL_MAX_CUR()))
                        {
                            // Record Requested Voltage and Other Port Partner Info
                            SET_PD_RX0_PARTNER_REQ_VOL(GET_PD_RX0_SRC_CAP_VOL_MAX(GET_PD_RX0_PARTNER_OBJ_POS() - 1));
                            SET_PD_RX0_PARTNER_GIVE_BACK(g_pucDataObj_EXINT[0] >> 3);
                            SET_PD_RX0_PARTNER_CAP_MIS(g_pucDataObj_EXINT[0] >> 2);
                            SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 1);
                            SET_PD_RX0_PARTNER_SUSPEND(~(g_pucDataObj_EXINT[0] >> 0));
                            SET_PD_RX0_PARTNER_UNCHK(g_pucDataObj_EXINT[1] >> 7);

                            // Set OCP Threshlod according to Min(Requested Max Cur, Cable Max Cur)
                            if(GET_PD_RX0_PARTNER_MAX_CUR() <= GET_PD_RX0_CBL_MAX_CUR())
                            {
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
                                SET_RX0_OCP_CURRENT((WORD)(((DWORD)(GET_PD_RX0_PARTNER_MAX_CUR()) * (DWORD)(GET_RX0_OCP_RATIO(GET_PD_RX0_PARTNER_OBJ_POS() - 1))) / 100));
#else
                                SET_RX0_OCP_CURRENT((WORD)((DWORD)(GET_PD_RX0_PARTNER_MAX_CUR()) * _TYPE_C_DEF_OCP_RATIO / 100));
#endif
                            }
                            else
                            {
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
                                SET_RX0_OCP_CURRENT((WORD)(((DWORD)(GET_PD_RX0_CBL_MAX_CUR()) * (DWORD)(GET_RX0_OCP_RATIO(GET_PD_RX0_PARTNER_OBJ_POS() - 1))) / 100));
#else
                                SET_RX0_OCP_CURRENT((WORD)((DWORD)(GET_PD_RX0_CBL_MAX_CUR()) * _TYPE_C_DEF_OCP_RATIO / 100));
#endif
                            }

                            SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                        }
                        else
                        {
                            // Send Reject
                            SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                        }
                    }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    else if(GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        WORD usNewVoltage = 0;

                        // Get PPS RDO Operating / Max Current (Unit = 50mA)
                        SET_PD_RX0_PARTNER_OP_CUR((WORD)(g_pucDataObj_EXINT[3] & 0x7F));
                        SET_PD_RX0_PARTNER_MAX_CUR((WORD)(g_pucDataObj_EXINT[3] & 0x7F));

                        // Request PPS Voltage with Unit 20mV and Convert to 10mV
                        usNewVoltage = (((((WORD)(g_pucDataObj_EXINT[1] & 0x0F)) << 7) | (((WORD)(g_pucDataObj_EXINT[2] & 0xFE)) >> 1)) * 2);

                        if(abs(usNewVoltage - (WORD)GET_PD_RX0_PARTNER_REQ_VOL()) <= 50)
                        {
                            SET_PD_RX0_REQ_VOL_SMALL_STEP(_TRUE);
                        }
                        else
                        {
                            SET_PD_RX0_REQ_VOL_SMALL_STEP(_FALSE);
                        }

                        SET_PD_RX0_PARTNER_REQ_VOL(usNewVoltage);

                        // Check if (Req "Operating Current" <= Source PDO Cur / Cable Max Current) & (Req Voltage is Valid)
                        if((GET_PD_RX0_PARTNER_OP_CUR() <= GET_PD_RX0_SRC_CAP_CUR(GET_PD_RX0_PARTNER_OBJ_POS() - 1)) &&
                           (GET_PD_RX0_PARTNER_OP_CUR() <= (GET_PD_RX0_CBL_MAX_CUR() / 5)) &&
                           (GET_PD_RX0_PARTNER_REQ_VOL() >= GET_PD_RX0_SRC_CAP_VOL_MIN(GET_PD_RX0_PARTNER_OBJ_POS() - 1)) &&
                           (GET_PD_RX0_PARTNER_REQ_VOL() <= GET_PD_RX0_SRC_CAP_VOL_MAX(GET_PD_RX0_PARTNER_OBJ_POS() - 1)))
                        {
                            // Convert Requested Current From 50mA to 10mA (PPS PDO : Max Current = Operating Current)
                            SET_PD_RX0_PARTNER_OP_CUR(GET_PD_RX0_PARTNER_OP_CUR() * 5);
                            SET_PD_RX0_PARTNER_MAX_CUR(GET_PD_RX0_PARTNER_MAX_CUR() * 5);

                            // Record Port Partner Info
                            SET_PD_RX0_PARTNER_GIVE_BACK(g_pucDataObj_EXINT[0] >> 3);
                            SET_PD_RX0_PARTNER_CAP_MIS(g_pucDataObj_EXINT[0] >> 2);
                            SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 1);
                            SET_PD_RX0_PARTNER_SUSPEND(~(g_pucDataObj_EXINT[0] >> 0));
                            SET_PD_RX0_PARTNER_UNCHK(g_pucDataObj_EXINT[1] >> 7);

                            SET_RX0_OCP_CURRENT(GET_PD_RX0_PARTNER_MAX_CUR());
                            SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);

                            // Start Timer Event 13.5 Sec, Sink Should Request PPS PDO every 10 sec
                            ScalerTypeCRx0PdActiveTimerEvent_EXINT0(13500, _SCALER_TIMER_EVENT_PD_RX0_PPS_TIMEOUT);
                        }
                        else
                        {
                            // Send Reject
                            SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                        }
                    }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    else
                    {
                        // Send Reject
                        SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
                else
                {
                    // Send Reject
                    SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {   // TD.PD.SRC.E14 : Receive Unexpected Msg. in "_PD_SRC_INT_WAIT_REQ", Do Soft Reset
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SNK_INT_WAIT_SRC_CAP:

            // Cancel SinkWaitCapTimer (310~620ms) = _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
            if((GET_PD_RX0_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST) && (GET_PD_RX0_TIMER_EVENT_VALID() == _TRUE))
            {
                CLR_PD_RX0_TIMER_EVENT_VALID();
            }

            // Hard Reset Detect Fail FW Sol : For Rcv Hard Reset Before Rcv Any Other Msg.
            ScalerSetByte_EXINT(P65_2C_BMC_RX_FW_TBIT0, (ScalerGetByte_EXINT(P65_2A_BMC_RX_HW_T0) + 3));

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_SRC_CAP)
            {
                // 1. Get Port Partner's Spec Version, and Decide the Version for Communication
                if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0) ||
                   ((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (_BIT7 | _BIT6)) == _BIT6))
                {   // if(Our PD Version is 2.0 || Port Partner Support Only PD 2.0)

                    // Change Spec Vesion to PD 2.0
                    SET_PD_RX0_SPEC_VER(_PD_VERSION_2_0);

                    // Change Cable Spec Vesion to PD 2.0
                    SET_PD_RX0_CBL_SPEC_VER(_PD_VERSION_2_0);
                }
                else
                {
                    // Set Spec Vesion to PD 3.0
                    SET_PD_RX0_SPEC_VER(_PD_VERSION_3_0);
                }

                // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                ScalerTypeCRx0PdUpdatePortPartnerRetryCounter_EXINT0();

                // 2. Store Src_Cap Info from Data Objects
                SET_PD_RX0_PARTNER_DRP(g_pucDataObj_EXINT[0] >> 5);
                SET_PD_RX0_PARTNER_SUSPEND(g_pucDataObj_EXINT[0] >> 4);
                SET_PD_RX0_PARTNER_EXT_PWR(g_pucDataObj_EXINT[0] >> 3);
                SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 2);
                SET_PD_RX0_PARTNER_DRD(g_pucDataObj_EXINT[0] >> 1);
                SET_PD_RX0_PARTNER_UNCHK(g_pucDataObj_EXINT[0] >> 0);

                // Get Number Of Capabilities
                SET_PD_RX0_PARTNER_SRC_CAP_CNT(GET_PD_RX0_RCV_NOD_CNT());

                // Evaluate and Set Request Data Objects
                for(pData_EXINT[0] = 0; pData_EXINT[0] < GET_PD_RX0_PARTNER_SRC_CAP_CNT(); pData_EXINT[0]++)
                {
                    // Set PDO Type
                    SET_PD_RX0_PARTNER_SRC_CAP_TYPE(pData_EXINT[0], ((g_pucDataObj_EXINT[pData_EXINT[0] * 4] & (_BIT7 | _BIT6)) >> 6));

                    if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4] & 0x01)) << 7) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0xFE)) >> 1)) * 10));
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2]) * 10));
                        SET_PD_RX0_PARTNER_SRC_CAP_CUR(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3] & 0x7F) * 5));
                    }
                    else
                    {
                        // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0xFC)) >> 2)) * 5));
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(pData_EXINT[0], GET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0]));
                        SET_PD_RX0_PARTNER_SRC_CAP_CUR(pData_EXINT[0], (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3]));
                        SET_PD_RX0_PARTNER_SRC_PEAK_CUR(pData_EXINT[0], ((g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & (_BIT5 | _BIT4)) >> 4));
                    }
                }

                // 3. Fill in Request Data Object

                // Send Request (Success : Wait Resp / Fail : Hard Reset)
                SET_PD_RX0_RCV_SRC_CAP();
                SET_PD_RX0_FW_STATE(_PD_SNK_INT_SEND_REQUEST);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REQUEST, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Receive Unexpected Msg. in "_PE_SNK_INT_WAIT_CAP", Do Hard Reset
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SNK_INT_WAIT_REQ_RESP:

            // Cancel WDTimerEvent(SENDER_RESP_TIMER)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_ACCEPT)
            {
                // Update PDO Status (Voltage in 10mV / Current in 10mA)
                if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(GET_PD_RX0_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                {
                    // Request to Fix PDO (REQ_INFO_1 = Op. Cur in 10mA / REQ_INFO_2 = Max. Cur in 10mA)
                    SET_PD_RX0_PDO_STATUS_VOL(GET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(GET_PD_RX0_REQ_OBJ_POS() - 1));
                    SET_PD_RX0_PDO_STATUS_CUR(GET_PD_RX0_REQ_INFO_2());
                }
                else
                {
                    // Request to PPS PDO (REQ_INFO_1 = Vol in 20mV / REQ_INFO_2 = Op. Cur in 50mA)
                    SET_PD_RX0_PDO_STATUS_VOL(GET_PD_RX0_REQ_INFO_1() * 2);
                    SET_PD_RX0_PDO_STATUS_CUR(GET_PD_RX0_REQ_INFO_2() * 5);
                }

                // Transit to _PE_SNK_TRANSIT_POWER
                SET_PD_RX0_FW_STATE(_PD_SNK_INT_WAIT_PS_RDY);

                // Source Begin to Transit Power
                SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

                // Active WD Timer Event For PS Transition Timer (450-550ms), Timeout : Hard Reset
                ScalerTimerWDActivateTimerEvent_EXINT0(_PS_TRANSITION_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_PS_TRANSITION_TIMEOUT);
            }
            else if((GET_PD_RX0_RCV_MSG() == _PD_CMD_REJECT) || (GET_PD_RX0_RCV_MSG() == _PD_CMD_WAIT))
            {
                if(GET_PD_RX0_EXPLICIT_CONTRACT() == _TRUE)
                {
                    SET_PD_RX0_FW_STATE(_PD_SNK_READY);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_SNK_READY);
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                    // Re-Evaluate and Send Request After 100 ms if Needed
                    ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_REQ_WAIT);
                }
                else
                {
                    SET_PD_RX0_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);

                    // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                    ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_SINK_WAIT_CAP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
                }
            }
            else
            {
                // Receive Unexpected Msg. in "_PE_SNK_WAIT_REQ_RESP", Do Soft Reset
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SNK_INT_WAIT_PS_RDY:

            // Cancel WDTimerEvent (PS_TRANSITION_TIMER, SEND_HARD_RST)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_RX0_PS_TRANSITION_TIMEOUT);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                SET_PD_RX0_FW_STATE(_PD_SNK_READY);
                SET_PD_RX0_SUB_STATE(_PD_SUB_SNK_READY);
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
                SET_PD_RX0_EXPLICIT_CONTRACT();
                ScalerSetBit_EXINT(P65_18_0X6518, ~_BIT7, (GET_PD_RX0_EXPLICIT_CONTRACT() << 7));

                // Clear OCP and OVP Event and Alert Macro due to New Power Contract Established
                CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP);
                CLR_PD_RX0_ALERT_SENT();

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                // Set PARTNER_ALT_SUPPORT FLAG for Sink in Ready to Wait For Port Partner Initiating Alt Mode Flow
                SET_PD_RX0_PARTNER_ALT_SUPPORT();

                // Sink Start PR_SWAP to Provide Power, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_PARTNER_ALT_SUPPORT);
#endif

                // Adjust Sink Unattach Vth
                ScalerTypeCPowerRx0UnattachVthAdjust_EXINT0(GET_PD_RX0_PDO_STATUS_VOL());
            }
            else
            {
                // Receive Unexpected Msg. in "_PE_SNK_WAIT_CAP", Do Hard Reset
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_INT_WAIT_SOFTRESET_RESP:

            // Cancel TimerEvent(Main Loop Send Soft Rst)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);

            // Cancel WD TimerEvent (INT Send Soft Rst)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);

            // [LECROY] TD PD.LL.E04 Hard Reset Usage : Send SoftReset, Then Rcv. Accept with Msg.ID = 1 Shall Ignore.
            if((GET_PD_RX0_RCV_MSG() == _PD_CMD_ACCEPT) && (ScalerGetBit_EXINT(P65_56_RX_FIFO0_MSG_HEADER0 + (ucRxProcFifo * 0x20), (_BIT3 | _BIT2 | _BIT1)) == 0x00))
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);

                    // Wait 5ms and Send Src_Cap
                    ScalerTimerWDActivateTimerEvent_EXINT0(5, _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG);
                }
                else
                {
                    SET_PD_RX0_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);

                    // Clear Flag, Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                    ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_SINK_WAIT_CAP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
                }
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SRC_READY:

            if((GET_PD_RX0_AMS_STATUS() == _PD_AMS_NONE) || (GET_PD_RX0_AMS_STATUS() == _PD_AMS_INTERRUPTIBLE))
            {
                // Receive Any Message When Not in AMS or in Interruptible AMS
                ScalerTypeCRx0PdIntSrcRcvMsgNoAmsProc_EXINT0();
            }
            else
            {
                // Rcv. Msg. During Non-Interruptible AMS / Power Transition
                ScalerTypeCRx0PdIntRcvMsgInAmsProc_EXINT0(ucRxProcFifo);
            }
            break;

        case _PD_SNK_READY:

            if((GET_PD_RX0_AMS_STATUS() == _PD_AMS_NONE) || (GET_PD_RX0_AMS_STATUS() == _PD_AMS_INTERRUPTIBLE))
            {
                // Receive Any Message When Not in AMS or in Interruptible AMS
                ScalerTypeCRx0PdIntSnkRcvMsgNoAmsProc_EXINT0();
            }
            else
            {
                // Rcv. Msg. During Non-Interruptible AMS / Power Transition
                ScalerTypeCRx0PdIntRcvMsgInAmsProc_EXINT0(ucRxProcFifo);
            }
            break;

        case _PD_SEND_CBL_DISCOVER_ID:
        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:
        case _PD_SEND_CBL_SOFT_RESET:
        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            // Receive Unexpected Msg. Do Soft Reset.
            ScalerTypeCRx0PdPrlErrHandle_EXINT0();

            break;

        // Not Expected to Receive Msg. in These States
        case _PD_SRC_START_UP:
        case _PD_SRC_SEND_CAP:
        case _PD_SRC_INT_SEND_ACCEPT_REQ:
        case _PD_SRC_INT_SEND_REJECT_REQ:
        case _PD_SRC_INT_SEND_WAIT_REQ:
        case _PD_SRC_INT_TRANSIT_POWER:
        case _PD_SRC_INT_SEND_PSRDY:
        case _PD_INT_SEND_SOFTRESET:
        case _PD_INT_SEND_SOFTRESET_RESP:

            ScalerTypeCRx0PdSendHardRst_EXINT0();

            break;

        // Not Ready to Rcv. Message (But May be Possible), Just Ignore
        case _PD_SNK_START_UP:
        case _PD_HARDRESET:
        case _PD_NO_RESPONSE:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SRC_READY During _AMS_NONE/_INTERRUPTIBLE
// Input Value  : ucRxProcFifo : _PD_RX_FIFO_0 / _PD_RX_FIFO_1 / _PD_RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntSrcRcvMsgNoAmsProc_EXINT0(void) using 1
{
    // Receive Any Message When Not in AMS or in Interruptible AMS @ _PE_SRC_READY

    // Clear Init Alt Mode Flag for SrcReady to Set Rp to SinkTxOK
    CLR_PD_RX0_SRC_INIT_ALT_MODE();

    switch(GET_PD_RX0_RCV_MSG())
    {
        case _PD_CMD_REQUEST:

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            // Cancel TimerEvent for PPS PDO
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_PPS_TIMEOUT);
#endif

            SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

            // 1. Get Requested Object Position and Current for Evaluation
            SET_PD_RX0_PARTNER_OBJ_POS((g_pucDataObj_EXINT[0] & (_BIT6 | _BIT5 | _BIT4)) >> 4);

            // 2. Negotiate Requested Power
            // Check if Request Object Position is Valid (Not 0, and <= Num of Src Cap Sent)
            if((GET_PD_RX0_PARTNER_OBJ_POS() > 0) && (GET_PD_RX0_PARTNER_OBJ_POS() <= GET_PD_RX0_SRC_PDO_CNT()))
            {
                if(GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                {
                    // Get Fix Supply RDO Operating / Max Current (Unit = 10mA)
                    SET_PD_RX0_PARTNER_OP_CUR((((WORD)(g_pucDataObj_EXINT[1] & 0x0F)) << 6) | (((WORD)(g_pucDataObj_EXINT[2] & 0xFC)) >> 2));
                    SET_PD_RX0_PARTNER_MAX_CUR((((WORD)(g_pucDataObj_EXINT[2] & 0x03)) << 8) | ((WORD)g_pucDataObj_EXINT[3]));

                    // Check if Requested "Operating Current" <= Src PDO Current / Cable Max Current
                    if((GET_PD_RX0_PARTNER_OP_CUR() <= GET_PD_RX0_SRC_CAP_CUR(GET_PD_RX0_PARTNER_OBJ_POS() - 1)) &&
                       (GET_PD_RX0_PARTNER_OP_CUR() <= GET_PD_RX0_CBL_MAX_CUR()))
                    {
                        // Record Requested Voltage and Other Port Partner Info
                        SET_PD_RX0_PARTNER_REQ_VOL(GET_PD_RX0_SRC_CAP_VOL_MAX(GET_PD_RX0_PARTNER_OBJ_POS() - 1));
                        SET_PD_RX0_PARTNER_GIVE_BACK(g_pucDataObj_EXINT[0] >> 3);
                        SET_PD_RX0_PARTNER_CAP_MIS(g_pucDataObj_EXINT[0] >> 2);
                        SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 1);
                        SET_PD_RX0_PARTNER_SUSPEND(~(g_pucDataObj_EXINT[0] >> 0));
                        SET_PD_RX0_PARTNER_UNCHK(g_pucDataObj_EXINT[1] >> 7);

                        // Set OCP Threshlod according to Min(Requested Max Cur, Cable Max Cur)
                        if(GET_PD_RX0_PARTNER_MAX_CUR() <= GET_PD_RX0_CBL_MAX_CUR())
                        {
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
                            SET_RX0_OCP_CURRENT((WORD)(((DWORD)(GET_PD_RX0_PARTNER_MAX_CUR()) * (DWORD)(GET_RX0_OCP_RATIO(GET_PD_RX0_PARTNER_OBJ_POS() - 1))) / 100));
#else
                            SET_RX0_OCP_CURRENT((WORD)((DWORD)(GET_PD_RX0_PARTNER_MAX_CUR()) * _TYPE_C_DEF_OCP_RATIO / 100));
#endif
                        }
                        else
                        {
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
                            SET_RX0_OCP_CURRENT((WORD)(((DWORD)(GET_PD_RX0_CBL_MAX_CUR()) * (DWORD)(GET_RX0_OCP_RATIO(GET_PD_RX0_PARTNER_OBJ_POS() - 1))) / 100));
#else
                            SET_RX0_OCP_CURRENT((WORD)((DWORD)(GET_PD_RX0_CBL_MAX_CUR()) * _TYPE_C_DEF_OCP_RATIO / 100));
#endif
                        }

                        SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Send Reject
                        SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                else if(GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1) == _PD_3_PROGRAMMABLE_PDO)
                {
                    WORD usNewVoltage = 0;

                    // Get PPS RDO Operating / Max Current (Unit = 50mA)
                    SET_PD_RX0_PARTNER_OP_CUR((WORD)(g_pucDataObj_EXINT[3] & 0x7F));
                    SET_PD_RX0_PARTNER_MAX_CUR((WORD)(g_pucDataObj_EXINT[3] & 0x7F));

                    // Request PPS Voltage with Unit 20mV and Convert to 10mV
                    usNewVoltage = ((((WORD)(g_pucDataObj_EXINT[1] & 0x0F)) << 7) | (((WORD)(g_pucDataObj_EXINT[2] & 0xFE)) >> 1)) * 2;

                    if(abs(usNewVoltage - (WORD)GET_PD_RX0_PARTNER_REQ_VOL()) <= 50)
                    {
                        SET_PD_RX0_REQ_VOL_SMALL_STEP(_TRUE);
                    }
                    else
                    {
                        SET_PD_RX0_REQ_VOL_SMALL_STEP(_FALSE);
                    }

                    SET_PD_RX0_PARTNER_REQ_VOL(usNewVoltage);

                    // // Check if (Req "Operating Current" <= Source PDO Cur / Cable Max Current) & (Req Voltage is Valid)
                    if((GET_PD_RX0_PARTNER_OP_CUR() <= GET_PD_RX0_SRC_CAP_CUR(GET_PD_RX0_PARTNER_OBJ_POS() - 1)) &&
                       (GET_PD_RX0_PARTNER_OP_CUR() <= (GET_PD_RX0_CBL_MAX_CUR() / 5)) &&
                       (GET_PD_RX0_PARTNER_REQ_VOL() >= GET_PD_RX0_SRC_CAP_VOL_MIN(GET_PD_RX0_PARTNER_OBJ_POS() - 1)) &&
                       (GET_PD_RX0_PARTNER_REQ_VOL() <= GET_PD_RX0_SRC_CAP_VOL_MAX(GET_PD_RX0_PARTNER_OBJ_POS() - 1)))
                    {
                        // Convert Requested Current From 50mA to 10mA (PPS PDO : Max Current = Operating Current)
                        SET_PD_RX0_PARTNER_OP_CUR(GET_PD_RX0_PARTNER_OP_CUR() * 5);
                        SET_PD_RX0_PARTNER_MAX_CUR(GET_PD_RX0_PARTNER_MAX_CUR() * 5);

                        // Record Port Partner Info
                        SET_PD_RX0_PARTNER_GIVE_BACK(g_pucDataObj_EXINT[0] >> 3);
                        SET_PD_RX0_PARTNER_CAP_MIS(g_pucDataObj_EXINT[0] >> 2);
                        SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 1);
                        SET_PD_RX0_PARTNER_SUSPEND(~(g_pucDataObj_EXINT[0] >> 0));
                        SET_PD_RX0_PARTNER_UNCHK(g_pucDataObj_EXINT[1] >> 7);

                        SET_RX0_OCP_CURRENT(GET_PD_RX0_PARTNER_MAX_CUR());
                        SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);

                        // Start Timer Event 13.5 Sec, Sink Should Request PPS PDO every 10 sec
                        ScalerTypeCRx0PdActiveTimerEvent_EXINT0(13500, _SCALER_TIMER_EVENT_PD_RX0_PPS_TIMEOUT);
                    }
                    else
                    {
                        // Send Reject
                        SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                else
                {
                    // Send Reject
                    SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send Reject
                SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_GET_SRC_CAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Source Capabilities"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_SRC_CAP);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);

            // FW Solution : Samsung S8 Plug-in then Start, Fail to Light Up
#if((_TYPE_C_EMB_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
            // S8 Send "Get Src Cap" When Start, but Not Trying to Initiate Alt Mode as DFP (Scaler UFP / No Alt Mode)
            if((GET_PD_RX0_DATA_ROLE() == _PD_DATA_UFP) && (GET_PD_RX0_DP_ALT_MODE_CONFIG() != _PD_DP_CONFIG) && (GET_PD_RX0_INTEROP_S8() == _FALSE))
            {
                // Wait 5 sec for other Devices to Enter Alt Mode, Timeout : Hard Reset (Cancel : PD Reset, Rcv Discover ID)
                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(5000, _SCALER_TIMER_EVENT_PD_RX0_S8_HRST);

                // Set Interop Flag to Prevent From "Non-AM Device with Get Src Cap" Device will be Infinitly Triggered
                SET_PD_RX0_INTEROP_S8();
            }
#endif

            break;

        case _PD_CMD_GET_SNK_CAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if((_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                // Send "Sink Capabilities"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_SNK_CAP);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SNK_CAP, _PD_VDM_CMD_RESERVED);
            }
            else
#endif
            {
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_PR_SWAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

#if(_SRC_ACCEPT_SWAP_TO_SNK == _TRUE)
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                if(GET_PD_RX0_GET_SNK_CAP_SENT() == _FALSE)
                {
                    // Send "WAIT"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_WAIT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_WAIT, _PD_VDM_CMD_RESERVED);
                }
                else if(GET_PD_RX0_PARTNER_EXT_PWR() == _TRUE)
                {
                    // Send "ACCEPT"
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_PRS);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // CTS Spec: DRP shall respond with Reject Msg.
                    // Send "Reject"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
#endif
            {
                if((GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY) && (GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0))
                {
                    // CTS Spec: Provider Only shall respond with Not_Supported Msg.
                    // Send "NOT_SUPPORT"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // PD 2.0 Standard Spec: Respond with Reject Msg.
                    // CTS Spec: DRP shall respond with Reject Msg.
                    // Send "Reject"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_DR_SWAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_VENDOR_ALT_MODE_NONE)
            if(GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE)
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_LENOVO_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_ACER_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_HP_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_DELL_ALT_MODE_ENTER() == _FALSE))
#endif
            {
                if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
                {
#if(_DFP_SWAP_TO_UFP == _TRUE)
                    // Accept Swap from DFP -> UFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);

                    // Fix Lecroy [COMMON.CHECK.PD.3 Check GoodCRC]
                    ScalerSetBit_EXINT(P65_3A_RX_CRC_RESPONSE_CTRL, ~(_BIT4), _BIT4);
#else
                    // Reject Swap from UFP -> DFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
                else
                {
#if(_UFP_SWAP_TO_DFP == _TRUE)
                    // Accept Swap from DFP -> UFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
#else
                    // Reject Swap from UFP -> DFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
            }
            else
            {
                // Receive DR_SWAP When in Alt Mode : Hard Reset
                ScalerTypeCRx0PdSendHardRst_EXINT0();
            }

            break;

        case _PD_CMD_VCONN_SWAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

            // Evaluate Vconn Swap : Vconn Source Must "Accept", Not Vconn Source Can "Accept/Reject/Wait"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_VCS);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_BIST:

            // BIST Mode Operate Only in vSafe5v
            if(GET_PD_RX0_PARTNER_REQ_VOL() == 500)
            {
                SET_PD_RX0_BIST_MODE((g_pucDataObj_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

                if(GET_PD_RX0_BIST_MODE() == (_BIT2 | _BIT0))
                {
                    // If Carrier Mode : Output 0101... for 30-60ms
                    // Turn On BIST UUT Carrier Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
                    ScalerSetBit_EXINT(P65_F1_PD_BIST_PATTERN, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeCRx0PdRxIntControl_EXINT0(_DISABLE);

                    SET_PD_RX0_SUB_STATE(_PD_SUB_BIST_MODE);

                    // Begin BIST Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // If BIST Carrier Mode, Back to Ready State After 30-60ms
                    ScalerTimerWDActivateTimerEvent_EXINT0(45, _SCALER_WD_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                }
                else if(GET_PD_RX0_BIST_MODE() == _BIT3)
                {
                    // If Test Data Mode : Do Nothing, Turn Off Rcv. Msg INT and Wait For HardReset
                    // Turn On BIST UUT Test Data Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

                    SET_PD_RX0_SUB_STATE(_PD_SUB_BIST_MODE);

                    // [0x6534] Setup Rx Valid Packet Type (SOP / Hard Reset)
                    ScalerSetByte_EXINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

                    // Begin BIST Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeCRx0PdRxIntControl_EXINT0(_DISABLE);
                }
            }

            // NOTE : WS111 GRL 2.1.2.1 PHY_BUSIDLE was Removed

            break;

        case _PD_CMD_VDM:

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            if(GET_PD_RX0_ALT_MODE_FUNCTION() == _TRUE)
            {
                if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
                {
                    // DFP Rcv Any VDM Resp. or Attention Request When Alt Mode Ready
                    ScalerTypeCRx0PdIntDfpRcvVdmMsgProc_EXINT0();
                }
                else
                {
                    // Receive VDM Request, UFP Responds According to Rcv. VDM Msg.
                    ScalerTypeCRx0PdIntUfpRcvVdmMsgProc_EXINT0();
                }
            }
            else if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }

#else
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        // PD 3.0 Control Message
        case _PD_CMD_GET_SRC_CAP_EXT:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Source Capability Extended"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_SRC_CAP_EXT);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SRC_CAP_EXT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_STATUS:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_STATUS);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_STATUS, _PD_VDM_CMD_RESERVED);

            break;

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
        case _PD_CMD_GET_PPS_STATUS:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_PPS_STATUS);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_PPS_STATUS, _PD_VDM_CMD_RESERVED);

            break;
#endif


        // PD 3.0 Data Message
        case _PD_CMD_ALERT:

            // Check Battery Status
            if((g_pucDataObj_EXINT[0] & (_BIT0)) == _BIT0)
            {
                // Send "Get Battery Status Message" if Needed
            }

            // Check Status
            if((g_pucDataObj_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) != 0x00)
            {
                // Send "Get Status Message"
                // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
            }

            break;

        // PD 3.0 Extended Message
        case _PD_CMD_GET_MFC_INFO:
#if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
#if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
            // Send "Not Support"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
#else
            // Follow Standard Spec.
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // for DRP, PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
            }
#endif // End of #if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
#else
            // Byte 0-1 are Ext. Msg Header
            // Manufacturer Info Target "g_pucDataObj_EXINT[2]" : 0 = Port / 1 = Battery
            if(g_pucDataObj_EXINT[2] == 0x00)
            {
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                // Send "Manufacturer Info"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_MFC_INFO);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_MFC_INFO, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif  // End of #if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            break;

        case _PD_CMD_CHUNK_TEST:

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            if((GET_PD_RX0_CHUNKED_MESSAGE() == _TRUE) && (GET_PD_RX0_CHUNK_REQUEST() == _FALSE))
            {
                // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                if(((GET_PD_RX0_CHUNK_NUMBER() + 1) * 26) < GET_PD_RX0_EXT_MSG_DATA_SIZE())
                {
                    // Set Chunk Message As an Chunk Request
                    SET_PD_RX0_CHUNK_REQUEST(_TRUE);

                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                    // Send "Chunk Test" REQUEST
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_CHK_TEST_REQ);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_FR_SWAP:

            // CTS : For UUT AS SRC, But Not Support FR_Swap
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_NOT_SUPPORT:
        // PD 3.0 Data Message
        // PD 3.0 Extended Message
        case _PD_CMD_STATUS:
        case _PD_CMD_MFC_INFO:

            break;
#endif

        // Receive Unexpected Message in READY State
        case _PD_CMD_RSV:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_WAIT:
        case _PD_CMD_SRC_CAP:
        case _PD_CMD_SNK_CAP:

            ScalerTypeCRx0PdPrlErrHandle_EXINT0();

            break;

        // Receive Redundent Messages in READY State (Ignore)
        case _PD_CMD_GOODCRC:
        case _PD_CMD_PING:

            break;

        // Receive Un-Supported or Un-Recognized Msg. in READY State
        case _PD_CMD_UNDEFINED:
        default:
#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        // PD 3.0 Control Message
        case _PD_CMD_GET_COUNTRY_CODES:

        // PD 3.0 Data Message
        case _PD_CMD_BAT_STATUS:
        case _PD_CMD_GET_COUNTRY_INFO:
#endif
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))

        // PD 3.0 Extended Message
        case _PD_CMD_GET_BAT_CAP:
        case _PD_CMD_GET_BAT_STATUS:
        case _PD_CMD_BAT_CAP:
        case _PD_CMD_SEC_REQ:
        case _PD_CMD_SEC_RESP:
        case _PD_CMD_FW_UPDATE_REQ:
        case _PD_CMD_FW_UPDATE_RESP:
        case _PD_CMD_PPS_STATUS:
        case _PD_CMD_COUNTRY_INFO:
        case _PD_CMD_COUNTRY_CODES:

#if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }
#else
            // Follow Standard Spec.
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY)
            {
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // for DRP, PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
            }
#endif // End of #if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
            break;

#endif
    }
}

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SNK_READY During _AMS_NONE/_INTERRUPTIBLE
// Input Value  : ucRxProcFifo : _PD_RX_FIFO_0 / _PD_RX_FIFO_1 / _PD_RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntSnkRcvMsgNoAmsProc_EXINT0(void) using 1
{
    // Receive Any Message When Not in AMS or in Interruptible AMS @ _PE_SNK_READY

    switch(GET_PD_RX0_RCV_MSG())
    {
        case _PD_CMD_SRC_CAP:

            // 1. Store Src_Cap Info from Data Objects
            SET_PD_RX0_PARTNER_DRP(g_pucDataObj_EXINT[0] >> 5);
            SET_PD_RX0_PARTNER_SUSPEND(g_pucDataObj_EXINT[0] >> 4);
            SET_PD_RX0_PARTNER_EXT_PWR(g_pucDataObj_EXINT[0] >> 3);
            SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 2);
            SET_PD_RX0_PARTNER_DRD(g_pucDataObj_EXINT[0] >> 1);
            SET_PD_RX0_PARTNER_UNCHK(g_pucDataObj_EXINT[0] >> 0);

            // Get Number Of Capabilities (Number Of Data Objects)
            SET_PD_RX0_PARTNER_SRC_CAP_CNT(GET_PD_RX0_RCV_NOD_CNT());

            // Evaluate and Set Request Data Objects
            for(pData_EXINT[0] = 0; pData_EXINT[0] < GET_PD_RX0_PARTNER_SRC_CAP_CNT(); pData_EXINT[0]++)
            {
                // Set PDO Type
                SET_PD_RX0_PARTNER_SRC_CAP_TYPE(pData_EXINT[0], ((g_pucDataObj_EXINT[pData_EXINT[0] * 4] & (_BIT7 | _BIT6)) >> 6));

                if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
                {
                    // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                    SET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4] & 0x01)) << 7) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0xFE)) >> 1)) * 10));
                    SET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2]) * 10));
                    SET_PD_RX0_PARTNER_SRC_CAP_CUR(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3] & 0x7F) * 5));
                }
                else
                {
                    // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                    SET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0xFC)) >> 2)) * 5));
                    SET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(pData_EXINT[0], GET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0]));
                    SET_PD_RX0_PARTNER_SRC_CAP_CUR(pData_EXINT[0], (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3]));
                    SET_PD_RX0_PARTNER_SRC_PEAK_CUR(pData_EXINT[0], ((g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & (_BIT5 | _BIT4)) >> 4));
                }
            }

            SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
            // CTS : TD PD.SNK.E09 GetSinkCap in Place of Accept, Protocol Error Shall Send Soft Reset.
            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send Request (Success : Wait Resp / Fail : Hard Reset)
            SET_PD_RX0_RCV_SRC_CAP();
            SET_PD_RX0_FW_STATE(_PD_SNK_INT_SEND_REQUEST);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REQUEST, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_SRC_CAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // if Able to Become Src, Reply "Src_Cap", Otherwise "Reject"
#if((_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                // Send "Source Capabilities"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_SRC_CAP);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }
            else
#endif
            {
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_GET_SNK_CAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Sink Capabilities"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_SNK_CAP);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SNK_CAP, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_PR_SWAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);
#if(_SNK_ACCEPT_SWAP_TO_SRC == _TRUE)
            if((GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE))
            {
                // Send "ACCEPT"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_PRS);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
            }
            else
#endif
            {
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "NOT_SUPPORT"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "REJECT"
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_DR_SWAP:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_VENDOR_ALT_MODE_NONE)
            if(GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE)
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_LENOVO_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_ACER_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_HP_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            if((GET_PD_RX0_DP_ALT_MODE_ENTER() == _FALSE) && (GET_PD_RX0_DELL_ALT_MODE_ENTER() == _FALSE))
#endif
            {
                if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
                {
#if(_DFP_SWAP_TO_UFP == _TRUE)
                    // Accept Swap from DFP -> UFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
#else
                    // Reject Swap from UFP -> DFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
                else
                {
#if(_UFP_SWAP_TO_DFP == _TRUE)
                    // Accept Swap from DFP -> UFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
#else
                    // Reject Swap from UFP -> DFP
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
            }
            else
            {
                // Receive DR_SWAP When Alt Mode Start : Hard Reset
                ScalerTypeCRx0PdSendHardRst_EXINT0();
            }

            break;

        case _PD_CMD_VCONN_SWAP:

            if(GET_TYPE_C_RX0_PORT_ROLE() != _TYPE_C_PORT_SNK_ONLY)
            {
                SET_PD_RX0_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

                // Evaluate Vconn Swap : Vconn Source Must "Accept", Not Vconn Source Can "Accept/Reject/Wait"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_VCS);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "REJECT" if We Are Not DRP or SRC-Only
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_BIST:

            // BIST Mode Operate Only in vSafe5v
            if(GET_PD_RX0_REQ_OBJ_POS() == 1)
            {
                SET_PD_RX0_BIST_MODE((g_pucDataObj_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
                if(GET_PD_RX0_BIST_MODE() == (_BIT2 | _BIT0))
                {
                    // If Carrier Mode : Output 0101... for 30-60ms
                    // Turn On BIST UUT Carrier Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
                    ScalerSetBit_EXINT(P65_F1_PD_BIST_PATTERN, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeCRx0PdRxIntControl_EXINT0(_DISABLE);

                    SET_PD_RX0_SUB_STATE(_PD_SUB_BIST_MODE);

                    // Begin BIST Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // If BIST Carrier Mode, Back to Ready State After 30-60ms
                    ScalerTimerWDActivateTimerEvent_EXINT0(45, _SCALER_WD_TIMER_EVENT_PD_RX0_STATE_TO_READY);
                }
                else if(GET_PD_RX0_BIST_MODE() == _BIT3)
                {
                    // Lecroy [TEST.PD.PHY.ALL.07]
                    while(ScalerGetBit_EXINT(P65_05_PD_PHY_IDLE_INT, _BIT2) == 0x00)
                    {
                        DELAY_XUS_EXINT(5);
                    }

                    // If Test Data Mode : Do Nothing, Turn Off Rcv. Msg INT and Wait For HardReset
                    // Turn On BIST UUT Test Data Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

                    // [0x6534] Setup Rx Valid Packet Type (SOP / Hard Reset)
                    ScalerSetByte_EXINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

                    // Begin BIST Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeCRx0PdRxIntControl_EXINT0(_DISABLE);

                    SET_PD_RX0_SUB_STATE(_PD_SUB_BIST_MODE);
                }
            }

            break;

        // Receive VDM Message (Alt Mode. Flow)
        case _PD_CMD_VDM:

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            if(GET_PD_RX0_ALT_MODE_FUNCTION() == _TRUE)
            {
                if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
                {
                    // DFP Rcv Any VDM Resp. or Attention Request When Alt Mode Ready
                    ScalerTypeCRx0PdIntDfpRcvVdmMsgProc_EXINT0();
                }
                else
                {
                    // Receive VDM Request, UFP Responds According to Rcv. VDM Msg.
                    ScalerTypeCRx0PdIntUfpRcvVdmMsgProc_EXINT0();
                }
            }
            else if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#else
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))

        // PD 3.0 Control Message
        case _PD_CMD_GET_SRC_CAP_EXT:

            // Follow Standard Spec.
            if(GET_TYPE_C_RX0_PORT_ROLE() != _TYPE_C_PORT_SNK_ONLY)
            {
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                // Send "Source Capability Extended"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_SRC_CAP_EXT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SRC_CAP_EXT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            break;

        case _PD_CMD_GET_STATUS:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_STATUS);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_STATUS, _PD_VDM_CMD_RESERVED);

            break;

        // PD 3.0 Data Message
        case _PD_CMD_ALERT:

            // Check Battery Status
            if((g_pucDataObj_EXINT[0] & (_BIT0)) == _BIT0)
            {
                // Send "Get Battery Status Message" if Needed
            }

            // Check Status
            if((g_pucDataObj_EXINT[0] & (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
            {
                // Send "Get Status Message"
                // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
                SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
            }

            break;

        // PD 3.0 Extended Message
        case _PD_CMD_GET_MFC_INFO:
#if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
#if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
            // Send "Not Support"
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
#else
            // Follow Standard Spec.
            // PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
#endif // End of #if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
#else
            // Byte 0-1 are Ext. Msg Header
            // Manufacturer Info Target "g_pucDataObj_EXINT[2]" : 0 = Port / 1 = Battery
            if(g_pucDataObj_EXINT[2] == 0x00)
            {
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                // Send "Manufacturer Info"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_MFC_INFO);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_MFC_INFO, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif // End of #if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            break;

        case _PD_CMD_CHUNK_TEST:

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            if((GET_PD_RX0_CHUNKED_MESSAGE() == _TRUE) && (GET_PD_RX0_CHUNK_REQUEST() == _FALSE))
            {
                // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                if(((GET_PD_RX0_CHUNK_NUMBER() + 1) * 26) < GET_PD_RX0_EXT_MSG_DATA_SIZE())
                {
                    // Set Chunk Message As an Chunk Request
                    SET_PD_RX0_CHUNK_REQUEST(_TRUE);

                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                    // Send "Chunk Test" REQUEST
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_CHK_TEST_REQ);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_FR_SWAP:

            // CTS : For UUT AS SNK, But Not Support FR_Swap
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_NOT_SUPPORT:
        // PD 3.0 Data Message
        // PD 3.0 Extended Message
        case _PD_CMD_STATUS:
        case _PD_CMD_MFC_INFO:
            break;

#endif

        // Receive Unexpected Message in READY State (Soft Reset)
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_WAIT:
        case _PD_CMD_REQUEST:
        case _PD_CMD_SNK_CAP:

            ScalerTypeCRx0PdPrlErrHandle_EXINT0();

            break;

        // Receive Redundent Message in READY State (Ignore)
        case _PD_CMD_GOODCRC:
        case _PD_CMD_PING:

            break;

        // Receive Un-Supported or Un-Recognized Messages
        case _PD_CMD_RSV:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_UNDEFINED:
        default:
#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        // PD 3.0 Control Message
        case _PD_CMD_GET_PPS_STATUS:
        case _PD_CMD_GET_COUNTRY_CODES:

        // PD 3.0 Data Message
        case _PD_CMD_BAT_STATUS:
        case _PD_CMD_GET_COUNTRY_INFO:
#endif
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        // PD 3.0 Extended Message
        case _PD_CMD_GET_BAT_CAP:
        case _PD_CMD_BAT_CAP:
        case _PD_CMD_GET_BAT_STATUS:
        case _PD_CMD_SEC_REQ:
        case _PD_CMD_SEC_RESP:
        case _PD_CMD_FW_UPDATE_REQ:
        case _PD_CMD_FW_UPDATE_RESP:
        case _PD_CMD_PPS_STATUS:
        case _PD_CMD_COUNTRY_INFO:
        case _PD_CMD_COUNTRY_CODES:
#if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }
#else
            // Follow Standard Spec.
            // PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
#endif // End of #if(_TYPE_C_CTS_SPEC_FOLLOW == _TRUE)
            break;
#endif
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DFP Rcv. SOP VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntDfpRcvVdmMsgProc_EXINT0(void) using 1
{   // Rcv. Any VDM Resp (Attention Message Not Included)
    if(GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_WAIT_VDM_RESP)
    {
        CLR_PD_RX0_PARTNER_VDM_NO_RESP_CNT();

        // Cancel TimerEvent (Sender Response Timer = 24-30ms)
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);

        switch(GET_PD_RX0_DP_ALT_STATE())
        {
            case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_PD_RX0_VDM_SVID() == _PD_SID))
                {
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID);
                }
                else
                {
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_SVID_ACK) && (GET_PD_RX0_VDM_SVID() == _PD_SID))
                {
                    if(ScalerTypeCRx0PdSearchSvid_EXINT0() == _TRUE)
                    {   // If Find DP_SID = 0xFF01, Send Discover Mode
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_MODE);
                    }
                    else
                    {
                        // If Search Fnish = FALSE, Send Discover SVID Again to Get More SVID
                        if(GET_PD_RX0_DP_SVID_SEARCH_FINISH() == _FALSE)
                        {
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID);
                        }
                        else
                        {   // No More SVID and Cannot Find DP_SID, Stop Alt. Mode Flow
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                        }
                    }
                }
                else
                {
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_ACK) && (GET_PD_RX0_VDM_SVID() == _DP_SID))
                {
                    // Search All Modes to Get DP Port Capability (DP_Tx) and Pin Assignment ( C / D / E )
                    ScalerTypeCRx0PdSearchMode_EXINT0();

                    if(GET_PD_RX0_DP_OBJ_POS() == 0)
                    {   // Cannot Find Any Acceptable Configuration, Stop Alt. Mode Flow
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                    }
                    else
                    {   // Use the Object Position Selected in Function to Initiate Enter Mode
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                    }
                }
                else
                {
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_ENTER_MODE_ACK) && (GET_PD_RX0_VDM_SVID() == _DP_SID) && (GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()))
                {
                    // Set DP Enter Mode Flag
                    SET_PD_RX0_DP_ALT_MODE_ENTER();

                    // Push _PD_HPD_LOW into HPD_Queue
                    ScalerTypeCRx0PdPushHpd_EXINT0(_PD_HPD_LOW, 0);

                    // Transit to "DP_STATUS" to Send DP_Status REQ
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_STATUS);
                }
                else
                {
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_ACK) || (GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_NAK))
                {
                    CLR_PD_RX0_DP_ALT_MODE_EXIT_REQ();

                    // Clear Alt. Mode Status
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_NONE);
                    CLR_PD_RX0_DP_ALT_MODE_ENTER();
                    SET_PD_RX0_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);
                    ScalerDpRx0HpdToggleAuxPhyResetProc_EXINT0(_LOW);
                    SET_PD_RX0_HPD_STATUS(_LOW);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_50) && (GET_PD_RX0_VDM_SVID() == _DP_SID) && (GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()))
                {
                    // Pop Out One HPD From Queue
                    ScalerTypeCRx0PdPopHpd_EXINT0();

                    if(ScalerTypeCRx0PdCheckDpStatus_EXINT0() == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG() == _PD_DP_CONFIG)
                        {
                            // Check Avaliable Pin Assignment
                            if(ScalerTypeCRx0PdDfpJudgePinAssignment_EXINT0() == _TRUE)
                            {
                                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }
                        }
                        else
                        {
                            SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                        }
                    }
                    else
                    {
                        if(GET_PD_RX0_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                        {
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                        }
                        else
                        {
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);
                        }
                    }
                }
                else
                {
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_51) && (GET_PD_RX0_VDM_SVID() == _DP_SID) && (GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()))
                {
                    // Swith DP Lane Mapping
                    ScalerDpRx0SetDpAltModeLaneMapping_EXINT0(GET_PD_RX0_PIN_ASSIGNMENT(), GET_CC_RX0_ORIENTATION());
                    SET_PD_RX0_DP_ALT_MODE_CONFIG(GET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG());

                    if(GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
                    {
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_READY);
                    }
                    else
                    {
                        if(GET_PD_RX0_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                        {
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                        }
                        else
                        {
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);
                        }
                    }
                }
                else
                {
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_READY:

                if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_50) && (GET_PD_RX0_VDM_SVID() == _DP_SID) && (GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()))
                {
                    // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                    if(GET_PD_RX0_HPD_SPACE_TIME(GET_PD_RX0_HPD_RPTR()) != 0)
                    {
                        SET_PD_RX0_ATTENTION_WAIT();
                        ScalerTypeCRx0PdActiveTimerEvent_EXINT0(GET_PD_RX0_HPD_SPACE_TIME(GET_PD_RX0_HPD_RPTR()), _SCALER_TIMER_EVENT_PD_RX0_CLR_ATTENTION_WAIT);
                    }

                    // Pop Out One HPD From Queue
                    ScalerTypeCRx0PdPopHpd_EXINT0();

                    if(ScalerTypeCRx0PdCheckDpStatus_EXINT0() == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_PD_RX0_HPD_STATUS() == _LOW)
                        {
                            SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                        }
                        else
                        {
                            // Push _PD_HPD_LOW into HPD_Queue
                            ScalerTypeCRx0PdPushHpd_EXINT0(_PD_HPD_LOW, 0);

                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_STATUS);
                        }
                    }
                }

                break;

            case _PD_ALT_MODE_NONE:
            case _PD_ALT_MODE_ERROR:
            default:
                // Not Expected to Receive Any Message (Except For ALT_MODE_READY Which May Rcv DP_Status ACK)
                break;
        }

        SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

        // Back to "SNK_READY / SRC_READY"
        ScalerTypeCRx0PdBackToReadyState_EXINT0();
    }
    else
    {
        switch(GET_PD_RX0_RCV_VDM_CMD())
        {
            case _PD_VDM_CMD_DISCOVER_ID_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_PD_RX0_VDM_SVID() == _PD_SID) && (GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0))
                {
                    // Send "Discover ID ACK"
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_ACK);
                }
                else
                {
                    // Send "Discover ID NAK" or "Ignore"
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_NAK);
                }

                break;

            case _PD_VDM_CMD_DISCOVER_SVID_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_PD_RX0_VDM_SVID() == _PD_SID) && (GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0))
                {
                    // Send "Discover SVID ACK"
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_ACK);
                }
                else
                {
                    // Send "Discover SVID NAK"  or "Ignore"
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_NAK);
                }

                break;

            case _PD_VDM_CMD_DISCOVER_MODE_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_PD_RX0_VDM_SVID() == _DP_SID) && (GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0))
                {
                    // Send "Discover Mode ACK" to Display Port
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);
                }
                else
                {
                    // Send "Discover Mode NAK" to Uncongnized SID
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_NAK);
                }

                break;

            case _PD_VDM_CMD_ATTENTION_REQ:

                // Check if SVID is correct, and Valid State to Receive Attention (DO Not Check Object Position)
                // if((GET_PD_RX0_VDM_SVID() == _DP_SID) && (GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()) && ((GET_PD_RX0_DP_ALT_STATE() == _PD_ALT_MODE_INT_WAIT_ATTENTION) || (GET_PD_RX0_DP_ALT_STATE() == _PD_ALT_MODE_READY)))
                if((GET_PD_RX0_VDM_SVID() == _DP_SID) && ((GET_PD_RX0_DP_ALT_STATE() == _PD_ALT_MODE_INT_WAIT_ATTENTION) || (GET_PD_RX0_DP_ALT_STATE() == _PD_ALT_MODE_READY)))
                {
                    if(ScalerTypeCRx0PdCheckDpStatus_EXINT0() == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG() == _PD_DP_CONFIG)
                        {
                            // Check Avaliable Pin Assignment
                            if(ScalerTypeCRx0PdDfpJudgePinAssignment_EXINT0() == _TRUE)
                            {
                                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }
                        }
                        else
                        {
                            if(GET_PD_RX0_HPD_STATUS() == _LOW)
                            {
                                SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
                                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                // Push _PD_HPD_LOW into HPD_Queue
                                ScalerTypeCRx0PdPushHpd_EXINT0(_PD_HPD_LOW, 0);

                                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_STATUS);
                            }
                        }
                    }
                    else
                    {
                        if(GET_PD_RX0_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                        {
                            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                        }
                    }
                }

                break;

            default:

                break;
        }
    }
}
#endif  // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : UFP Rcv. SOP VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntUfpRcvVdmMsgProc_EXINT0(void) using 1
{
    // Check if BMC Channel, Rx PTCL State, and BUS are Idle
    if((ScalerGetBit_EXINT(P65_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2) && (ScalerGetByte_EXINT(P65_21_RX_STATE_MACHINE_L) == _BIT0) && (GET_PD_RX0_BUS_IDLE() == _TRUE))
    {
        // UFP Only Response to VDM Request, Ignore All Illegal ACK/NAK/BUSY
        if((GET_PD_RX0_RCV_VDM_TYPE() == _PD_STRUCTURED_VDM) && (GET_PD_RX0_RCV_VDM_CMD_TYPE() == _PD_VDM_CMD_TYPE_REQ))
        {
            if(GET_PD_RX0_VDM_SVID() == _PD_SID)
            {
                switch((EnumVdmCmd)GET_PD_RX0_RCV_VDM_CMD())
                {
                    case _PD_VDM_CMD_DISCOVER_ID_REQ:

                        // FW Solution : Samsung S8 Plug-in then Start, Fail to Light Up
#if((_TYPE_C_EMB_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
                        // If Rcv Discover ID, Cancel S8 HRST, Since Alt Mode Flow Start
                        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_S8_HRST);
                        if((GET_PD_RX0_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_RX0_S8_HRST) && (GET_PD_RX0_TIMER_EVENT_VALID() == _TRUE))
                        {
                            CLR_PD_RX0_TIMER_EVENT_VALID();
                        }

                        // Clear Interop to Enable S8 FW Solution, When Alt Mode Flow Has Been Start
                        CLR_PD_RX0_INTEROP_S8();
#endif

                        SET_PD_RX0_PARTNER_INIT_ALT_MODE();

                        // Send "Discover ID ACK"
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_ACK);

                        break;

                    case _PD_VDM_CMD_DISCOVER_SVID_REQ:

                        if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SNK) && (GET_PD_RX0_DP_ALT_MODE_ENTER() == _TRUE) && (GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_USB_CONFIG))
                        {
                            // FW Solution For Lenovol T480 : Fail To Light Up When Received Twice SVID(Second Svid Received Between Enter Mode and Dp Configure)
                            // Time Out: Do Error Recovery, Start From Unattach.SRC. If Go to DP Configure Successfully in 1s, Cancel WD Timer Event.
                            ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_T480_ERROR_RECOVERY_TIMER, _SCALER_TIMER_EVENT_PD_RX0_T480_ERROR_RECOVERY);
                        }

                        // Send "Discover SVID ACK"
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_ACK);

                        break;

                    default:
                        // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
                        break;
                }
            }
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
            else if(GET_PD_RX0_VDM_SVID() == _DP_SID)
            {   // Receive DP Alt Mode VDM Request, UFP Responds According to Rcv. VDM Msg.
                ScalerTypeCRx0PdIntUfpRcvDpVdmMsgProc_EXINT0();
            }
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            else if(GET_PD_RX0_VDM_SVID() == _LENOVO_VID)
            {   // Receive Lenovo Alt Mode VDM Request, UFP Responds According to Rcv. VDM Msg.
                ScalerTypeCRx0PdIntUfpRcvLenovoVdmMsgProc_EXINT0();
            }
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
            else if(GET_PD_RX0_VDM_SVID() == _ACER_VID)
            {   // Receive Acer Alt Mode VDM Request, UFP Responds According to Rcv. VDM Msg.
                ScalerTypeCRx0PdIntUfpRcvAcerVdmMsgProc_EXINT0();
            }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            else if(GET_PD_RX0_VDM_SVID() == _HP_VID)
            {
                if(ScalerTypeCRx0PdCheckHpVdmValid_EXINT0() == _TRUE)
                {
                    ScalerTypeCRx0PdIntUfpRcvHpVdmMsgProc_EXINT0();
                }
                // If AM Address Don't Match, Bypass Message to Downstream
                // Need to Check the 1st Bit of AM Address (If No Match -> Do Nothing)
            }
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            else if(GET_PD_RX0_VDM_SVID() == _DELL_VID)
            {
                ScalerTypeCRx0PdIntUfpRcvDellVdmMsgProc_EXINT0();
            }
#endif
            else
            {
                // If Attention Command request is an Unrecognized Message it Shall be Ignored
                // Otherwise, Send NAK Command to Uncongnized SVID
                if(!((EnumVdmCmd)GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_ATTENTION_REQ))
                {
                    // Send NAK Command to Uncongnized SVID
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, GET_PD_RX0_RCV_VDM_CMD() | _BIT7);
                }
            }
        }
        else if(GET_PD_RX0_RCV_VDM_TYPE() == _PD_UNSTRUCTURED_VDM)
        {
            // PD Merged Test [TEST.PD.VDM.SNK.7] :
            // For Rcv. Unstructured VDM : PD2.0 Should Ignore, PD3.0 Should Resp. w/ Not Support
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
        }
    }
    else
    {
        CLR_PD_RX0_FIFO_CLR();
    }
}

#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Dp VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntUfpRcvDpVdmMsgProc_EXINT0(void) using 1
{
    switch((EnumVdmDpCmd)GET_PD_RX0_RCV_VDM_CMD())
    {
        case _PD_VDM_DP_CMD_DISCOVER_MODE_REQ:

            // Send "Discover Mode ACK"
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_DP_CMD_ENTER_MODE_REQ:

            // if Obj Pos = DP_Alt_Mode
            if(GET_PD_RX0_VDM_OBJ_POS() == 1)
            {
                // If Source Choose to Enter DP Alt Mode. Set Object Position to 1
                SET_PD_RX0_DP_OBJ_POS(GET_PD_RX0_VDM_OBJ_POS());

                // Send "Enter Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

                // Set PD Sub State to Send VDM Message in INT
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            }
            else
            {   // Send "Enter Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_DP_CMD_EXIT_MODE_REQ:

            // If Obj Pos = DP_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()) || (GET_PD_RX0_VDM_OBJ_POS() == 7)) && (GET_PD_RX0_DP_ALT_MODE_ENTER() == _TRUE))
            {   // Send "Exit Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);

                // Set PD Sub State to Send VDM Message in INT
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            }
            else
            {   // Send "Exit Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_DP_CMD_DP_STATUS_REQ:

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // If Obj Pos = DP_Alt_Mode & Already in Alt_Mode
            // Lecroy [TD.DP.10.2.05] and DP Alt Mode Standard 3.9.2.1 : When DP Alt Mode is not enabled, PD shall not transmit any DisplayPort Status Update Command.
            if((GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()) && (GET_PD_RX0_DP_ALT_MODE_ENTER() == _TRUE))
#endif
            {
                // Send "DP_Status ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_50);
                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_DP_STATUS_ACK);

                // Set PD Sub State to Send VDM Message in INT
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            }

            break;

        case _PD_VDM_DP_CMD_DP_CONFIG_REQ:

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // If Obj Pos = DP_Alt_Mode & Already in Alt_Mode
            if((GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DP_OBJ_POS()) && (GET_PD_RX0_DP_ALT_MODE_ENTER() == _TRUE))
#endif
            {
                // REQ as DP_RX & Pin Assignment C / D / E || Config USB & Pin Assignment NONE
                if(ScalerTypeCRx0PdCheckDpConfig_EXINT0() == _TRUE)
                {
                    // Swith DP Lane Mapping
                    ScalerDpRx0SetDpAltModeLaneMapping_EXINT0(GET_PD_RX0_PIN_ASSIGNMENT(), GET_CC_RX0_ORIENTATION());

                    // Send "DP_Configure ACK"
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_51);
                    SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_DP_CONFIG_ACK);

                    // Set PD Sub State to Send VDM Message in INT
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                }
                else
                {   // Send "DP_Configure NAK"
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_91);
                }
            }

            break;

        default:
            // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
            break;
    }
}
#endif  // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Lenovo VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntUfpRcvLenovoVdmMsgProc_EXINT0(void) using 1
{
    switch((EnumVdmLenovoCmd)GET_PD_RX0_RCV_VDM_CMD())
    {
        case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_REQ:

            // Send "Discover Mode ACK"
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_LENOVO_CMD_ENTER_MODE_REQ:

            // if Obj Pos = Lenovo_Alt_Mode
            if(GET_PD_RX0_VDM_OBJ_POS() == 1)
            {
                // If Source Choose to Enter Lenovo Alt Mode. Set Object Position to 1
                SET_PD_RX0_LENOVO_OBJ_POS(GET_PD_RX0_VDM_OBJ_POS());

                // Send "Enter Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
                SET_PD_RX0_LENOVO_ALT_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

                // Set PD Sub State to Send VDM Message in INT
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            }
            else
            {   // Send "Enter Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_LENOVO_CMD_EXIT_MODE_REQ:

            // If Obj Pos = Lenovo_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_LENOVO_OBJ_POS()) || (GET_PD_RX0_VDM_OBJ_POS() == 7)) && (GET_PD_RX0_LENOVO_ALT_MODE_ENTER() == _TRUE))
            {   // Send "Exit Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
                SET_PD_RX0_LENOVO_ALT_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);

                // Set PD Sub State to Send VDM Message in INT
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            }
            else
            {   // Send "Exit Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_LENOVO_CMD_GET_STATUS_REQ:

            // If Already in Alt_Mode
            if(GET_PD_RX0_LENOVO_ALT_MODE_ENTER() == _TRUE)
            {
                CLR_PD_RX0_LENOVO_ATTN_SENT_FLAG();
                CLR_PD_RX0_LENOVO_ATTN_CNT();

                // Cancel TimerEvent (Lenovo Attention Timer = 300ms)
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_LENOVO_RESP_TIMEOUT);

                // Check Lenovo Get_Status
                ScalerTypeCRx0PdCheckLenovoStatus_EXINT0();

                // Send "Lenovo Get_Status ACK (0x50)"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_LENOVO_CMD_GET_STATUS_ACK);
                SET_PD_RX0_LENOVO_ALT_STATE(_PD_ALT_MODE_INT_SEND_LENOVO_GET_STATUS_ACK);

                // Set PD Sub State to Send VDM Message in INT
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            }

            break;

        case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_REQ:

            // Check Lenovo Device_ID
            ScalerTypeCRx0PdCheckLenovoDeviceId_EXINT0();

            // Send "Lenovo Device ID (0x51)"
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_ACK);

            break;

        default:
            // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Acer VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntUfpRcvAcerVdmMsgProc_EXINT0(void) using 1
{
    switch((EnumVdmAcerCmd)GET_PD_RX0_RCV_VDM_CMD())
    {
        case _PD_VDM_ACER_CMD_DISCOVER_MODE_REQ:

            // Send "Discover Mode ACK"
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_ACER_CMD_ENTER_MODE_REQ:

            // Send "Enter Mode ACK" (Not Check Object Position)
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            SET_PD_RX0_ACER_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

            // Set PD Sub State to Send VDM Message in INT
            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);

            break;

        case _PD_VDM_ACER_CMD_GET_STATUS_REQ:

            // If Already in Alt_Mode
            if(GET_PD_RX0_ACER_ALT_MODE_ENTER() == _TRUE)
            {
                // Check Acer Get_Status
                ScalerTypeCRx0PdCheckAcerSysStatus_EXINT0();

                // Send "Get_Status ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_ACER_CMD_GET_STATUS_ACK);
            }

            break;

        default:
            // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Hp VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntUfpRcvHpVdmMsgProc_EXINT0(void) using 1
{
    switch((EnumTypeCVdmHpCmd)GET_PD_RX0_RCV_VDM_CMD())
    {
        case _PD_VDM_HP_CMD_DISCOVER_MODE_REQ:

            // Send "Discover Mode ACK"
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_HP_CMD_ENTER_MODE_REQ:

            // if Obj Pos = Hp_Alt_Mode
            if(GET_PD_RX0_VDM_OBJ_POS() == 1)
            {
                // If Source Choose to Enter Hp Alt Mode. Set Object Position to 1
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

                // Send "Enter Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                // Send "Enter Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_HP_CMD_EXIT_MODE_REQ:

            // If Obj Pos = Hp_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_PD_RX0_VDM_OBJ_POS() == 1) || (GET_PD_RX0_VDM_OBJ_POS() == 7)) && (GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE))
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);

                // Send "Exit Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                // Send "Exit Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_HP_CMD_SET_CONFIG_REQ:

            if(GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_HP_SET_CONFIG_ACK);

                // Get Hp I2C and AM Address
                ScalerTypeCRx0PdSetHpOwnAddr_EXINT0();

                // Send "Hp Set_config ACK (0x50)"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_HP_CMD_SET_CONFIG_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_GET_CONFIG_REQ:

            if(GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);

                // Send "Hp Get_config ACK (0x51)"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_HP_CMD_GET_CONFIG_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_SET_VWIRE_REQ:

            if(GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeCRx0PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_SET_VWIRE_REQ);

                if(GET_PD_RX0_HP_VWIRE_OP() != _PD_HP_VWIRE_OP_SAMPLE)
                {
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);

                    // Send "Hp Set_vwire ACK (0x52)"
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_HP_CMD_SET_VWIRE_ACK);
                }
            }

            break;

        case _PD_VDM_HP_CMD_GET_VWIRE_REQ:

            if(GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeCRx0PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_GET_VWIRE_REQ);

                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);

                // Send "Hp Get_vwire ACK (0x53)"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_HP_CMD_GET_VWIRE_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_SET_DATA_REQ:

            if(GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeCRx0PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_SET_DATA_REQ);

                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);

                // Send "Hp Set_data ACK (0x54)"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_HP_CMD_SET_DATA_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_GET_DATA_REQ:

            if(GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeCRx0PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_GET_DATA_REQ);

                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);

                // Send "Hp Get_data ACK (0x55)"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_HP_CMD_GET_DATA_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_CMD_REQ:
        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Dell VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntUfpRcvDellVdmMsgProc_EXINT0(void) using 1
{
    switch((EnumTypeCVdmDellCmd)GET_PD_RX0_RCV_VDM_CMD())
    {
        case _PD_VDM_DELL_CMD_DISCOVER_MODE_REQ:

            // Send "Discover Mode ACK"
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_DELL_CMD_ENTER_MODE_REQ:

            // if Obj Pos = Dell_Alt_Mode
            if(GET_PD_RX0_VDM_OBJ_POS() == 1)
            {
                // Cancel WDTimerEvent (_TYPE_C_EMB_DELL_ALT_MODE_ENTER_TIMEOUT_TIMER)
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_RX0_DELL_AM_ENTER_TIMEOUT);

                // If Source Choose to Enter Dell Alt Mode. Set Object Position to 1
                SET_PD_RX0_DELL_OBJ_POS(GET_PD_RX0_VDM_OBJ_POS());

                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

                // Send "Enter Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                // Send "Enter Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_DELL_CMD_EXIT_MODE_REQ:

            // If Obj Pos = Dell_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_PD_RX0_VDM_OBJ_POS() == GET_PD_RX0_DELL_OBJ_POS()) || (GET_PD_RX0_VDM_OBJ_POS() == 7)) && (GET_PD_RX0_DELL_ALT_MODE_ENTER() == _TRUE))
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);

                // Send "Exit Mode ACK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                // Send "Exit Mode NAK"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_DELL_CMD_0X12_REQ:

            if(GET_PD_RX0_DELL_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Dell System Information and Set 0x12 SysEvent
                ScalerTypeCRx0PdGetDellSysInfo_EXINT0();
                SET_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_0X12);

                if(GET_PD_RX0_DELL_USER_EVENT() != _TYPE_C_DELL_USER_EVENT_NONE)
                {
                    if(GET_PD_RX0_DELL_ALT_MODE_STATE() == _PD_ALT_MODE_INT_WAIT_DELL_0X13)
                    {
                        // Cancel TimerEvent (_TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER)
                        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_DELL_ATTEN_RETRY);

                        // If (User Event != None), Set Atten_NoResponse SysEvent to Kernel and Clear User Event
                        CLR_PD_RX0_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                        CLR_PD_RX0_DELL_ATTEN_RETRY_CNT();
                        CLR_PD_RX0_DELL_ATTEN_WAIT();
                        SET_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_NORESPONSE);
                    }
                    else
                    {
                        // If (User Event != None) && (Attention has not Sent by Kernel) , Set Atten_Discard SysEvent to Kernel and Clear User Event
                        CLR_PD_RX0_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                        SET_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_DISCARD);
                    }
                }

                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_DELL_0X12_ACK);

                // Send "Dell 0x12 ACK (0x52)"
                ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumVdmCmd)_PD_VDM_DELL_CMD_0X12_ACK);
            }

            break;

        case _PD_VDM_DELL_CMD_0X13_REQ:

            if(GET_PD_RX0_DELL_ALT_MODE_ENTER() == _TRUE)
            {
                if(GET_PD_RX0_DELL_USER_EVENT() != _TYPE_C_DELL_USER_EVENT_NONE)
                {
                    if(GET_PD_RX0_DELL_ALT_MODE_STATE() == _PD_ALT_MODE_INT_WAIT_DELL_0X13)
                    {
                        // Cancel TimerEvent (_TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER)
                        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_DELL_ATTEN_RETRY);

                        // Clear Dell Related Macros and Set Atten_Success System Event
                        CLR_PD_RX0_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                        CLR_PD_RX0_DELL_ATTEN_RETRY_CNT();
                        CLR_PD_RX0_DELL_ATTEN_WAIT();
                        SET_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_SUCCESS);
                        SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
                    }
                }
            }

            break;

        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SNK_READY During _AMS_NON_INTERRUPTIBLE/_AMS_POWER_TRANSITION
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntRcvMsgInAmsProc_EXINT0(BYTE ucRxProcFifo) using 1
{
    // Rcv. Msg. During Non-Interruptible AMS / Power Transition
    ucRxProcFifo = ucRxProcFifo;

    switch(GET_PD_RX0_SUB_STATE())
    {
        // Get_Src_Cap Msg. Has Been Sent (For SRC Only)
        // Sink Should Transit to Ready after Sending Get_Src_Cap (Fig. 8-57)
        case _PD_SUB_INT_WAIT_SRC_CAP:

            // Cancel TimerEvent(SenderRespTimer)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_SRC_CAP)
            {
                // 1. Store Src_Cap Info from Data Objects
                SET_PD_RX0_PARTNER_DRP(g_pucDataObj_EXINT[0] >> 5);
                SET_PD_RX0_PARTNER_SUSPEND(g_pucDataObj_EXINT[0] >> 4);
                SET_PD_RX0_PARTNER_EXT_PWR(g_pucDataObj_EXINT[0] >> 3);
                SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 2);
                SET_PD_RX0_PARTNER_DRD(g_pucDataObj_EXINT[0] >> 1);
                SET_PD_RX0_PARTNER_UNCHK(g_pucDataObj_EXINT[0] >> 0);

                // Get Number Of Capabilities
                SET_PD_RX0_PARTNER_SRC_CAP_CNT(GET_PD_RX0_RCV_NOD_CNT());

                // Evaluate and Set Request Data Objects
                for(pData_EXINT[0] = 0; pData_EXINT[0] < GET_PD_RX0_PARTNER_SRC_CAP_CNT(); pData_EXINT[0]++)
                {
                    // Set PDO Type
                    SET_PD_RX0_PARTNER_SRC_CAP_TYPE(pData_EXINT[0], ((g_pucDataObj_EXINT[pData_EXINT[0] * 4] & (_BIT7 | _BIT6)) >> 6));

                    if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4] & 0x01)) << 7) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0xFE)) >> 1)) * 10));
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2]) * 10));
                        SET_PD_RX0_PARTNER_SRC_CAP_CUR(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3] & 0x7F) * 5));
                    }
                    else
                    {
                        // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0xFC)) >> 2)) * 5));
                        SET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(pData_EXINT[0], GET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(pData_EXINT[0]));
                        SET_PD_RX0_PARTNER_SRC_CAP_CUR(pData_EXINT[0], (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3]));
                        SET_PD_RX0_PARTNER_SRC_PEAK_CUR(pData_EXINT[0], ((g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & (_BIT5 | _BIT4)) >> 4));
                    }
                }

                // 2. Update Flag and Transit State
                SET_PD_RX0_RCV_SRC_CAP();
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
                SET_PD_RX0_SUB_STATE(_PD_SUB_SRC_READY);
            }
            else if(GET_PD_RX0_RCV_MSG() == _PD_CMD_REJECT)
            {
                SET_PD_RX0_PARTNER_DRP(_FALSE);

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
                SET_PD_RX0_SUB_STATE(_PD_SUB_SRC_READY);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        // Get_Snk_Cap Msg. Has Been Sent
        case _PD_SUB_INT_WAIT_SNK_CAP:

            // Cancel TimerEvent(SenderRespTimer)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_SNK_CAP)
            {
                // 1. Store Snk_Cap Info from Data Objects
                SET_PD_RX0_PARTNER_DRP(g_pucDataObj_EXINT[0] >> 5);
                SET_PD_RX0_PARTNER_HIGH_CAP(g_pucDataObj_EXINT[0] >> 4);
                SET_PD_RX0_PARTNER_EXT_PWR(g_pucDataObj_EXINT[0] >> 3);
                SET_PD_RX0_PARTNER_USB_CAP(g_pucDataObj_EXINT[0] >> 2);
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
                SET_PD_RX0_PARTNER_DRD(g_pucDataObj_EXINT[0] >> 1);
#else
                SET_PD_RX0_PARTNER_DRD(_TRUE);
#endif

                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // [24:23] Fast Role Swap Default Require Current
                    SET_PD_RX0_PARTNER_FRS_CUR(((g_pucDataObj_EXINT[0] & _BIT0) << 1) | ((g_pucDataObj_EXINT[1] & _BIT7) >> 7));
                }

                // Get Number Of Capabilities
                SET_PD_RX0_PARTNER_SNK_CAP_CNT(GET_PD_RX0_RCV_NOD_CNT());

                // Evaluate and Set Request Data Objects
                for(pData_EXINT[0] = 0; pData_EXINT[0] < GET_PD_RX0_PARTNER_SNK_CAP_CNT(); pData_EXINT[0]++)
                {
                    // Set PDO Type
                    SET_PD_RX0_PARTNER_SNK_CAP_TYPE(pData_EXINT[0], ((g_pucDataObj_EXINT[pData_EXINT[0] * 4] & (_BIT7 | _BIT6)) >> 6));

                    if(GET_PD_RX0_PARTNER_SNK_CAP_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                        SET_PD_RX0_PARTNER_SNK_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4] & 0x01)) << 7) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0xFE)) >> 1)) * 10));
                        SET_PD_RX0_PARTNER_SNK_CAP_VOL_MIN(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2]) * 10));
                        SET_PD_RX0_PARTNER_SNK_CAP_CUR(pData_EXINT[0], (((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3] & 0x7F) * 5));
                    }
                    else
                    {
                        // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                        SET_PD_RX0_PARTNER_SNK_CAP_VOL_MAX(pData_EXINT[0], (((((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0xFC)) >> 2)) * 5));
                        SET_PD_RX0_PARTNER_SNK_CAP_VOL_MIN(pData_EXINT[0], GET_PD_RX0_PARTNER_SNK_CAP_VOL_MAX(pData_EXINT[0]));
                        SET_PD_RX0_PARTNER_SNK_CAP_CUR(pData_EXINT[0], (((WORD)(g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucDataObj_EXINT[pData_EXINT[0] * 4 + 3]));
                    }
                }

                // 2. Update Flag and Transit State
                SET_PD_RX0_RCV_SNK_CAP();
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Back to "SNK_READY / SRC_READY"
                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else if(GET_PD_RX0_RCV_MSG() == _PD_CMD_REJECT)
            {
                SET_PD_RX0_PARTNER_DRP(_FALSE);

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Back to "SNK_READY / SRC_READY"
                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else
            {   // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_PRS_RESP:

            // Cancel TimerEvent(SENDER_RESP_TIMER)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_ACCEPT)
            {
                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // 1.  Wait 25-35 ms Before Turning Off Vbus
                    ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_PRS_SRC_OFF);
                }
                else if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SNK)
                {
                    // 1. Turn Off Sink Power
                    // 2. Disable TypeC Vbus Detach Detect Function
                    ScalerTypeCRx0CcVbusDetCtrl_EXINT0(_DISABLE);

                    // 3. Wait 750~920ms For SRC to Turn Off Power and Send PS_RDY
                    // PD Merged Test [TEST.PD.PROT.SNK.12]
                    ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_PS_SRC_OFF_TIMER, _SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_SRC_OFF);
                }

                // Receive Accept to PR_Swap, Set Flag For Retimer Usage
                SET_PD_RX0_PRS_PROCESSING();
            }
            else if((GET_PD_RX0_RCV_MSG() == _PD_CMD_REJECT) || (GET_PD_RX0_RCV_MSG() == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Reject PR Swap
                SET_PD_RX0_PRS_REJECT();

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else if(GET_PD_RX0_RCV_MSG() == _PD_CMD_WAIT)
            {
                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_PD_RX0_PRS_WAIT_FLAG();
                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_PRS_WAIT);

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else
            {   // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_SRC_OFF:

            // Cancel TimerEvent(PS_SRC_OFF_TIMER);
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER);
            if((GET_PD_RX0_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER) && (GET_PD_RX0_TIMER_EVENT_VALID() == _TRUE))
            {
                CLR_PD_RX0_TIMER_EVENT_VALID();
            }

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_SRC_ON_PSRDY);

                // 1. if(PD 3.0), Switch HW Rp to Default Rp [0x6637][7:6]
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
#if(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
                    ScalerSetBit_EXINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_DEF << 6));
#elif(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
                    ScalerSetBit_EXINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_1P5A << 6));
#else
                    ScalerSetBit_EXINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_3P0A << 6));
#endif  // End of #if(_TYPE_C_SRC_DEF_CUR == _SRC_DEF_USB)
                }

                // 2. Change Rd -> Rp (Switch to Power SRC)
                ScalerTypeCRx0CcSwitchPowerRole_EXINT0(_PD_POWER_SRC);

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
                SET_RX0_OCP_CURRENT((WORD)(((DWORD)(GET_CC_RX0_DEF_CUR()) * (DWORD)(GET_RX0_OCP_RATIO(0))) / 100));
#else
                SET_RX0_OCP_CURRENT((WORD)((DWORD)(GET_CC_RX0_DEF_CUR()) * _TYPE_C_DEF_OCP_RATIO / 100));
#endif

                // 3. Turn On Vbus to vSafe5V (500 * 10mV) / Current = Default Current (10mA)
                ScalerTypeCPowerRx0VbusControl_EXINT0(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_RX0_OCP_CURRENT(), _PD_PEAK_CUR_NONE);

                // 4. Check Vbus 35ms Later, Then Start PMIC Protection and Send "PS_RDY" if VbusSafe5V
                ScalerTimerWDActivateTimerEvent_EXINT0(35, _SCALER_WD_TIMER_EVENT_PD_RX0_CHECK_PSRDY);
            }
            else
            {
                // Receive Unexpected Message During Rp-Rd switch
                SET_TYPE_C_ERROR_RECOVERY();
            }

            break;

        case _PD_SUB_INT_WAIT_SRC_ON:

            // Cancel TimerEvent(PS_SRC_ON_TIMER);
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                // Transit to _PE_SNK_START_UP
                SET_PD_RX0_FW_STATE(_PD_SNK_START_UP);

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_DRS_RESP:

            // Cancel TimerEvent(SENDER_RESP_TIMER)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_ACCEPT)
            {
                if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
                {
                    // [0x6535][1:0] Check Rcv. SOP Msg Data Role : DFP ('b11) => Do Not ChecK DR For Interop
                    // ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // [0x65E5] Update FW/HW Data Role to UFP
                    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
                    SET_PD_RX0_DATA_ROLE(_PD_DATA_UFP);

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                    // Set PARTNER_ALT_SUPPORT FLAG to Wait For Port Partner Initiating Alt Mode Flow
                    SET_PD_RX0_PARTNER_ALT_SUPPORT();

                    // DFP DR_SWAP to UFP, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                    ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_PARTNER_ALT_SUPPORT);
#endif
                }
                else
                {
                    // [0x6535][1:0] Check Rcv. SOP Msg Data Role : UFP ('b10) => Do Not ChecK DR For Interop
                    // ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT1 | _BIT0), _BIT1);

                    // [0x65E5] Update FW/HW Data Role to DFP
                    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, _BIT0);
                    SET_PD_RX0_DATA_ROLE(_PD_DATA_DFP);
                }

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else if((GET_PD_RX0_RCV_MSG() == _PD_CMD_REJECT) || (GET_PD_RX0_RCV_MSG() == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Reject DR Swap
                SET_PD_RX0_DRS_REJECT();

                // Data Role Correction For Interop : Some Sources Have Wrong Data Role and Do Not Accept DR_SWAP
                // For Data Role Swap Reject & Data Role Error => Swith Our Data Role to Prevent From Both Side Start Alt Mode
                if(((ScalerGetBit_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20), _BIT5)) >> 5) == (ScalerGetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, _BIT0)))
                {
                    if((ScalerGetBit_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20), _BIT5)) == _BIT5)
                    {
                        // [0x65E5] Update FW/HW Data Role to UFP
                        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
                        SET_PD_RX0_DATA_ROLE(_PD_DATA_UFP);
                    }
                    else
                    {
                        // [0x65E5] Update FW/HW Data Role to DFP
                        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, _BIT0);
                        SET_PD_RX0_DATA_ROLE(_PD_DATA_DFP);
                    }
                }

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else if(GET_PD_RX0_RCV_MSG() == _PD_CMD_WAIT)
            {
                SET_PD_RX0_DRS_WAIT_FLAG();
                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_DRS_WAIT);
                // ScalerTimerActiveTimerEvent_EXINT0(WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_DRS_WAIT);

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_VCS_RESP:

            // Cancel TimerEvent(SENDER_RESP_TIMER)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_ACCEPT)
            {
                if(GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC)
                {
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VCONN_ON);
                    ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_VCONN_ON_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
                }
                else
                {
                    // Turn On Vconn Power
                    ScalerTypeCRx0CcVconnControl_EXINT0(_ENABLE);

                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VCONN_ON_PSRDY);

                    ScalerTimerWDActivateTimerEvent_EXINT0(5, _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG);
                }
            }
            else if(GET_PD_RX0_RCV_MSG() == _PD_CMD_REJECT)
            {
                SET_PD_RX0_VCS_REJECT();

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else if(GET_PD_RX0_RCV_MSG() == _PD_CMD_NOT_SUPPORT)
            {
                if(GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC)
                {
                    // Port Partner Reject Vconn Swap
                    SET_PD_RX0_VCS_REJECT();
                }
                else
                {
                    // Turn On Vconn Power
                    ScalerTypeCRx0CcVconnControl_EXINT0(_ENABLE);

                    // Set Vconn Role to Vconn SRC
                    SET_PD_RX0_VCONN_ROLE(_PD_VCONN_SRC);

                    // [0x6534] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
                    ScalerSetByte_EXINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }

                // Set AMS = None
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else if(GET_PD_RX0_RCV_MSG() == _PD_CMD_WAIT)
            {
                SET_PD_RX0_VCS_WAIT_FLAG();
                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_VCS_WAIT);

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else
            {   // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_VCONN_ON:

            // Cancel TimerEvent(WAIT_VCONN_ON_TIMER)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
            if((GET_PD_RX0_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST) && (GET_PD_RX0_TIMER_EVENT_VALID() == _TRUE))
            {
                CLR_PD_RX0_TIMER_EVENT_VALID();
            }

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                // Turn Off Vconn
                ScalerTypeCRx0CcVconnControl_EXINT0(_OFF);

                // Set Vconn Role to Vconn SNK
                SET_PD_RX0_VCONN_ROLE(_PD_VCONN_NOT_SRC);

                // [0x6534] Setup Rx Valid Packet Type (Not Vconn SRC : SOP / Hard Reset)
                ScalerSetByte_EXINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Reset Discover ID Retry Fail Counter After Vconn_Swap
                CLR_PD_RX0_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_PD_RX0_VCS_WAIT_FLAG();
                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_VCS_WAIT);

                // Vconn Swap Success, Back to SRC/SNK_READY State
                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_SUB_INT_WAIT_CHK_TEST_RESP:

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_CHUNK_TEST)
            {
                // Check If This Ext Msg is Chunked : Ext Message Header [15]
                if((GET_PD_RX0_CHUNKED_MESSAGE() == _TRUE) && (GET_PD_RX0_CHUNK_REQUEST() == _FALSE))
                {
                    // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                    if(((GET_PD_RX0_CHUNK_NUMBER() + 1) * 26) < GET_PD_RX0_EXT_MSG_DATA_SIZE())
                    {
                        // Set Chunk Message As an Chunk Request
                        SET_PD_RX0_CHUNK_REQUEST(_TRUE);

                        SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                        // Send "Chunk Test" REQUEST
                        SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_CHK_TEST_REQ);
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                        SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                        ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                    }
                }
                else
                {
                    // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                    SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_STATUS:

            // Cancel TimerEvent(_SENDER_RESP_TIMER)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY);

            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_STATUS)
            {
                // Receive Status Message, Temporary do nothing, Only Protocol For CTS
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCRx0PdPrlErrHandle_EXINT0();
            }

            break;
#endif

        case _PD_SUB_SEND_GET_SRC_CAP:
        case _PD_SUB_SEND_GET_SNK_CAP:
        case _PD_SUB_INT_SEND_SRC_CAP:
        case _PD_SUB_INT_SEND_SNK_CAP:
        case _PD_SUB_SEND_SRC_CAP:
        case _PD_SUB_INT_SEND_ACCEPT_PRS:
        case _PD_SUB_INT_SEND_SRC_ON_PSRDY:
        case _PD_SUB_PRS_SRC_OFF:
        case _PD_SUB_INT_SEND_ACCEPT_DRS:
        case _PD_SUB_INT_SEND_ACCEPT_VCS:
        case _PD_SUB_INT_SEND_VCONN_ON_PSRDY:
        case _PD_SUB_INT_SEND_REJECT:
        default:

            // Receive Unexpected Message in Unexpected FW State
            ScalerTypeCRx0PdPrlErrHandle_EXINT0();

            break;
    }
}

//--------------------------------------------------
// Description  : Process Rcv. SOP' /SOP" Msg. in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntRcvCableMsgProc_EXINT0(BYTE ucRxProcFifo) using 1
{
    // Cancel TimerEvent(SENDER_RESP_TIMER)
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT);

    // Update PR/DR/Spec Version In Msg Header For SOP Communication.
    ScalerTypeCRx0PdUpdateTxFifoMsgHeader_EXINT0();

    // Update Cable Spec Version
    if(GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
    {
        // Update Cable Spec Version According to Our Spec Version and Cable Spec Version
        if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0) ||
           ((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (_BIT7 | _BIT6)) == _BIT6))
        {
            SET_PD_RX0_CBL_SPEC_VER(_PD_VERSION_2_0);
        }
        else
        {
            SET_PD_RX0_CBL_SPEC_VER(_PD_VERSION_3_0);
        }
    }

    switch(GET_PD_RX0_FW_STATE())
    {
        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:

            if((GET_PD_RX0_RCV_MSG() == _PD_CMD_VDM) && (GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_ACK))
            {
                // Record Cable Info Of Discover ID Ack
                ScalerTypeCRx0PdSaveCableDiscoverIdAckInfo_EXINT0();
                SET_PD_RX0_CBL_PD_CAPABILITY(_TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);
            }

            // Send SRC_CAP After Discover ID NAK/BUSY or Unexpected Msg Received Before Power Contract
            // Send Discover ID to Cable After Power Contract If Discover ID ACK Not Received
            SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);
            SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

            break;

        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            if(GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
            {
                SET_PD_RX0_FW_STATE(_PD_SEND_CBL_DISCOVER_ID);
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
            }
            else
            {
                // PD Transit to On-going PD Flow
                SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
            }

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_PD_RX0_SUB_STATE())
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_PD_RX0_CBL_STATE())
                    {
                        case _PD_CBL_INT_WAIT_SOFT_RST_RESP:

                            // Back to Ready State
                            ScalerTypeCRx0PdBackToReadyState_EXINT0();
                            SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_CBL_INT_WAIT_DISCOVER_ID_RESP:

                            CLR_PD_RX0_CBL_VDM_NO_RESP_CNT();

                            if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_PD_RX0_VDM_SVID() == _PD_SID))
                            {
                                CLR_PD_RX0_VDM_BUSY_CNT();

                                // Record Cable Info Of Discover ID Ack
                                ScalerTypeCRx0PdSaveCableDiscoverIdAckInfo_EXINT0();
                                SET_PD_RX0_CBL_PD_CAPABILITY(_TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);

                                // Re-send SRC Cap since new cable max current get, new power contract is needed, set system event
                                if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                                {
                                    if(ScalerTypeCRx0PdCheckRebuildPowerContract_EXINT0() == _PD_REBUILD_REQUIRED)
                                    {
                                        SET_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);
                                    }
                                }
                            }
                            else if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_NAK) && (GET_PD_RX0_VDM_SVID() == _PD_SID))
                            {
                                CLR_PD_RX0_VDM_BUSY_CNT();
                                SET_PD_RX0_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                            }
                            else if((GET_PD_RX0_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_BUSY) && (GET_PD_RX0_VDM_SVID() == _PD_SID))
                            {
                                ADD_PD_RX0_VDM_BUSY_CNT();

                                if(GET_PD_RX0_VDM_BUSY_CNT() >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_PD_RX0_VDM_BUSY_CNT();
                                    SET_PD_RX0_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                                }
                                else
                                {
                                    SET_PD_RX0_VDM_BUSY_FLAG();

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_VDM_BUSY_FLAG);
                                }
                            }

                            // Back to Ready State
                            ScalerTypeCRx0PdBackToReadyState_EXINT0();
                            SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        default:

                            break;
                    }

                    break;

                default:

                    break;
            }

            break;

        default:

            // Not Expected to Rcv Any SOP'/SOP" Packet

            break;
    }
}

//--------------------------------------------------
// Description  : Process When Tx Transmission Done in Interrupt (After SendMsg_EXINT0)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntTxDoneProc_EXINT0(void) using 1
{
    SET_PD_RX0_TRANSMIT_RESULT_EXINT(ScalerGetBit_EXINT(P65_DC_TX_PD_MSG_INT, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

    switch(GET_PD_RX0_TRANSMIT_RESULT_EXINT())
    {
        case _PD_SENT_SUCCESS:

            switch(GET_PD_RX0_FW_STATE())
            {
                case _PD_SRC_SEND_CAP:

                    // Reset Source Cap Counter and Hard Reset Counter
                    CLR_DP_RX0_SRC_CAP_CNT();
                    CLR_DP_RX0_HARD_RST_CNT();
                    CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);

                    // State Transition, AMS & Timer Setting
                    SET_PD_RX0_FW_STATE(_PD_SRC_INT_WAIT_REQ);
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                    // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
                    ScalerTimerWDActivateTimerEvent_EXINT0(_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);

                    break;

                case _PD_SRC_INT_SEND_ACCEPT_REQ:

                    if(GET_PD_RX0_REQ_VOL_SMALL_STEP() != _TRUE)
                    {
                        // Set WD Timer to Wait 25-35ms, then Turn On Vbus
                        ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER);
                    }
                    else
                    {
                        ScalerTimerWDActivateTimerEvent_EXINT0(5, _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER);
                    }

                    // State Transition
                    SET_PD_RX0_FW_STATE(_PD_SRC_INT_TRANSIT_POWER);

                    break;

                case _PD_SRC_INT_SEND_PSRDY:

                    // FW State Transition, AMS & Sub State Initialize
                    SET_PD_RX0_FW_STATE(_PD_SRC_READY);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_SRC_READY);
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                    // Set Power Contract = TRUE
                    SET_PD_RX0_EXPLICIT_CONTRACT();
                    ScalerSetBit_EXINT(P65_18_0X6518, ~_BIT7, (GET_PD_RX0_EXPLICIT_CONTRACT() << 7));

                    // Clear OCP and OVP Event and Alert Macro due to New Power Contract Established
                    CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP);
                    CLR_PD_RX0_ALERT_SENT();

                    break;

                case _PD_SRC_INT_SEND_REJECT_REQ:
                case _PD_SRC_INT_SEND_WAIT_REQ:

                    if(GET_PD_RX0_EXPLICIT_CONTRACT() == _TRUE)
                    {
                        // If Reject Request & Power Contract Exist,
                        if(ScalerTypeCRx0PdCheckPowerContractValid_EXINT0() == _TRUE)
                        {
                            // If Power Contract Staill Valid, Back to SRC_READY
                            SET_PD_RX0_FW_STATE(_PD_SRC_READY);
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
                        }
                        else
                        {
                            // If Power Contract is no more Valid, Do Hard Reset
                            ScalerTypeCRx0PdSendHardRst_EXINT0();
                        }
                    }
                    else
                    {
                        // If Reject Request & No Power Contract, Wait 120ms and Re-Send Src_Cap
                        SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);
                        SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                        ScalerTimerWDActivateTimerEvent_EXINT0(120, _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG);
                    }

                    break;

                case _PD_SNK_INT_SEND_REQUEST:

                    // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
                    ScalerTimerWDActivateTimerEvent_EXINT0(_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);

                    // Clear System Request Event
                    CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_SEND_REQUEST);
                    SET_PD_RX0_FW_STATE(_PD_SNK_INT_WAIT_REQ_RESP);

                    break;

                case _PD_INT_SEND_SOFTRESET:

                    // Start TimerEvent(SenderResponseTimer 24-30ms)
                    ScalerTimerWDActivateTimerEvent_EXINT0(_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);

                    SET_PD_RX0_FW_STATE(_PD_INT_WAIT_SOFTRESET_RESP);

                    break;

                case _PD_INT_SEND_SOFTRESET_RESP:

                    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);

                    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                    {
                        SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);

                        // Wait 5ms and Send Src_Cap
                        ScalerTimerWDActivateTimerEvent_EXINT0(5, _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG);
                    }
                    else
                    {
                        // ======= FW Solution For SNK Soft Reset Flow (TD.PD.SNK.E9) ======
                        ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);

                        SET_PD_RX0_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);

                        // Clear Flag, Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                        ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_SINK_WAIT_CAP_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);

                        // Release PHY/Protocol FSM
                        ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
                    }

                    break;

                case _PD_SRC_READY:
                case _PD_SNK_READY:

                    switch(GET_PD_RX0_SUB_STATE())
                    {
                        case _PD_SUB_INT_SEND_ACCEPT_PRS:

                            // Port Partner Initiates PR_Swap, which Means It Has the Ability to Change the Power Role, so CLR_PD_RX0_PRS_REJECT().
                            CLR_PD_RX0_PRS_REJECT();

                            // "Accept" Message Has Been Sent Successfully
                            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                            {
                                // 1. Turn Off Power After 25-35ms
                                ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER);
                                SET_PD_RX0_SUB_STATE(_PD_SUB_PRS_SRC_OFF);
                            }
                            else
                            {
                                // 1. Turn Off Sink Power
                                // 2. Disable TypeC Vbus Detach Detect Function
                                ScalerTypeCRx0CcVbusDetCtrl_EXINT0(_DISABLE);

                                // PD Merged Test [TEST.PD.PROT.SNK.12]
                                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_PS_SRC_OFF_TIMER, _SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER);
                                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_SRC_OFF);
                            }
                            // Accept PR_Swap From Port Partner, Set Flag For Retimer Usage
                            SET_PD_RX0_PRS_PROCESSING();
                            break;

                        case _PD_SUB_INT_SEND_SRC_ON_PSRDY:

                            // 5. Transit to _PE_SRC_START_UP, and Send Soft Reset to Cable
                            SET_PD_RX0_FW_STATE(_PD_SRC_START_UP);
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            // Hard Reset Detect Fail FW Sol : Clear SOP Fail IRQ to Prevent From False Process of Cable Reset
                            ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT5));

                            break;

                        case _PD_SUB_INT_SEND_ACCEPT_DRS:

                            // Port Partner Initiates DR_Swap, which Means It Has the Ability to Change the Data Role, so CLR_PD_RX0_DRS_REJECT().
                            CLR_PD_RX0_DRS_REJECT();

#if(_USB3_RETIMER_SUPPORT == _ON)
                            // Disable Retimer for LeCroy CTS4.10.1
                            ScalerUSB3RetimerDisable_EXINT0();
#endif

                            // Swap Data Role
                            if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
                            {
                                // [0x6535][1:0] Check Rcv. SOP Msg Data Role : DFP ('b11) => Do Not Check DR For Interop
                                // ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                                // [0x65E5] Update FW/HW Data Role to UFP
                                ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
                                SET_PD_RX0_DATA_ROLE(_PD_DATA_UFP);

                                // Fix Lecroy [COMMON.CHECK.PD.3 Check GoodCRC]
                                ScalerSetBit_EXINT(P65_3A_RX_CRC_RESPONSE_CTRL, ~(_BIT4), 0x00);

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                                // Set PARTNER_ALT_SUPPORT FLAG to Wait For Port Partner Initiating Alt Mode Flow
                                SET_PD_RX0_PARTNER_ALT_SUPPORT();

                                // DFP DR_SWAP to UFP, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_PARTNER_ALT_SUPPORT);
#endif
                            }
                            else
                            {
                                // [0x6535][1:0] Check Rcv. SOP Msg Data Role : UFP ('b10) => Do Not Check DR For Interop
                                // ScalerSetBit_EXINT(P65_35_RX_PORT_ROLE, ~(_BIT1 | _BIT0), _BIT1);

                                // [0x65E5] Update FW/HW Data Role to DFP
                                ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, _BIT0);
                                SET_PD_RX0_DATA_ROLE(_PD_DATA_DFP);
                            }

                            // AMS Finish
                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            // Back to Ready State
                            ScalerTypeCRx0PdBackToReadyState_EXINT0();

                            break;

                        case _PD_SUB_INT_SEND_ACCEPT_VCS:

                            // Port Partner Initiates Vconn_Swap, which Means It Has the Ability to Change the Vconn Role, so CLR_PD_RX0_VCS_REJECT().
                            CLR_PD_RX0_VCS_REJECT();

                            // "Accept" Message Has Been Sent Successfully
                            if(GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC)
                            {
                                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_VCONN_ON);
                                ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_VCONN_ON_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
                            }
                            else
                            {
                                // Turn On Vconn Power
                                ScalerTypeCRx0CcVconnControl_EXINT0(_ON);

                                SET_PD_RX0_SUB_STATE(_PD_SUB_INT_SEND_VCONN_ON_PSRDY);

                                ScalerTimerWDActivateTimerEvent_EXINT0(5, _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG);
                            }
                            break;

                        case _PD_SUB_INT_SEND_VCONN_ON_PSRDY:

                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            // Back to Ready State (SNK_READY / SRC_READY)
                            ScalerTypeCRx0PdBackToReadyState_EXINT0();

                            // Do Soft Reset to Cable After Vconn_Swap Success & We Are Vconn Src
                            SET_PD_RX0_CBL_SOFT_RESET_REQUIRED();

                            // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                            SET_PD_RX0_VCS_WAIT_FLAG();
                            ScalerTypeCRx0PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_RX0_CLR_VCS_WAIT);

                            break;

                        case _PD_SUB_INT_SEND_SRC_CAP:
                        case _PD_SUB_SEND_SRC_CAP:

                            CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);
                            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
                            {
                                CLR_DP_RX0_SRC_CAP_CNT();
                                SET_PD_RX0_FW_STATE(_PD_SRC_INT_WAIT_REQ);
                                SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                                SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                                ScalerTimerWDActivateTimerEvent_EXINT0(_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);
                            }
                            else
                            {
                                SET_PD_RX0_SUB_STATE(_PD_SUB_SNK_READY);
                                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);
                            }

                            break;

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                        case _PD_SUB_INT_SEND_VDM_RESP:

                            ScalerTypeCRx0PdIntTxVdmDoneProc_EXINT0();

                            break;
#endif

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
                        case _PD_SUB_INT_SEND_CHK_TEST_REQ:

                            SET_PD_RX0_SUB_STATE(_PD_SUB_INT_WAIT_CHK_TEST_RESP);

                            break;
#endif

                        // Send Message @ Int and Back to Ready State When Sent Successfully
                        case _PD_SUB_INT_SEND_SNK_CAP:
                        case _PD_SUB_INT_SEND_REJECT:
                        case _PD_SUB_INT_SEND_WAIT:
#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
                        case _PD_SUB_INT_SEND_SRC_CAP_EXT:
                        case _PD_SUB_INT_SEND_STATUS:
                        case _PD_SUB_INT_SEND_MFC_INFO:
                        case _PD_SUB_INT_SEND_PPS_STATUS:
#endif
                        // Send Message @ Int in Unexpected Sub State (Set Flag For Debug?)
                        case _PD_SUB_STATE_NONE:
                        case _PD_SUB_SNK_READY:
                        case _PD_SUB_SRC_READY:
                        case _PD_SUB_SEND_GET_SNK_CAP:
                        case _PD_SUB_SEND_GET_SRC_CAP:
                        case _PD_SUB_SEND_PR_SWAP:
                        case _PD_SUB_INT_WAIT_SRC_ON:
                        case _PD_SUB_INT_WAIT_SRC_OFF:
                        case _PD_SUB_PRS_SRC_OFF:
                        case _PD_SUB_SEND_DR_SWAP:
                        case _PD_SUB_SEND_VCONN_SWAP:
                        case _PD_SUB_INT_WAIT_VCONN_ON:
                        default:

                            // "Src_Cap" Message Has Been Sent Successfully
                            ScalerTypeCRx0PdBackToReadyState_EXINT0();

                            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                            break;
                    }
                    break;

                default:
                    // Send Message @ Int in Unexpected FW State (Set Flag For Debug?)
                    break;
            }

            break;

        case _PD_SENT_RETRY_FAIL:

            // Sink Does Not Resp to Src Cap
            if(GET_PD_RX0_FW_STATE() == _PD_SRC_SEND_CAP)
            {
                ADD_DP_RX0_SRC_CAP_CNT();

                // Check if Source Capability is sent More than Difined Max Times
                if(GET_DP_RX0_SRC_CAP_CNT() > _MAX_SRC_CAP_CNT)
                {
                    // Transit to PD No-Response, and Disable Rcv Msg. INT
                    SET_PD_RX0_FW_STATE(_PD_NO_RESPONSE);
                    ScalerTypeCRx0PdRxIntControl_EXINT0(_DISABLE);
                }
                else
                {
                    // Wait 120ms and Send Re-Src_Cap
                    ScalerTimerWDActivateTimerEvent_EXINT0(120, _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG);
                }
            }
            else if(GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_SEND_SRC_ON_PSRDY)
            {
                // Retry Fail During PR_SWAP Should Do Error Recovery
                SET_TYPE_C_ERROR_RECOVERY();
            }
            else if((GET_PD_RX0_AMS_STATUS() == _PD_AMS_POWER_TRANSITION) ||
                    (GET_PD_RX0_FW_STATE() == _PD_INT_SEND_SOFTRESET) || (GET_PD_RX0_FW_STATE() == _PD_INT_SEND_SOFTRESET_RESP))
            {
                ScalerTypeCRx0PdSendHardRst_EXINT0();
            }
            else
            {
                ScalerTypeCRx0PdSendSoftRst_EXINT0(_PD_SOP_PKT);
            }

            CLR_PD_RX0_TRANSMIT_RESULT();

            break;

        case _PD_SENT_DISCARDED:
        case _PD_SENT_CONFLICT:

            // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
            ScalerTypeCRx0PdUpdatePortPartnerRetryCounter_EXINT0();

            if((GET_PD_RX0_FW_STATE() != _PD_SRC_READY) && (GET_PD_RX0_FW_STATE() != _PD_SNK_READY))
            {
                ScalerTypeCRx0PdSendHardRst_EXINT0();
            }
            else
            {
                // Set AMS = None
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }

            break;

        case _PD_SENT_HARD_RST:
        default:

            // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
            ScalerTypeCRx0PdUpdatePortPartnerRetryCounter_EXINT0();

            if((GET_PD_RX0_FW_STATE() != _PD_SRC_READY) && (GET_PD_RX0_FW_STATE() != _PD_SNK_READY))
            {
                // if(Hard Reset Sent / Result Undefined), Do Hard Reset
                ScalerTypeCRx0PdSendHardRst_EXINT0();
            }
            else
            {
                // Set AMS = None
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCRx0PdBackToReadyState_EXINT0();
            }

            break;
    }   // End of switch(ScalerGetByte(P65_DC_TX_PD_MSG_INT) & (0x1F))

    // [0x65DC] Clear IRQs
    ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    if(GET_PD_RX0_TRANSMIT_RESULT_EXINT() == _PD_SENT_SUCCESS)
    {
        // [0x65DD] Disable tx_prl_trans_done IRQ
        ScalerSetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, 0x00);
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process When Tx Transmit VDM Msg Success in Interrupt (After SendMsg_EXINT0)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdIntTxVdmDoneProc_EXINT0(void) using 1
{
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
    if(GET_PD_RX0_VDM_SVID() == _DP_SID)
    {
        switch(GET_PD_RX0_DP_ALT_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_PD_RX0_DP_ALT_MODE_ENTER();

                if(GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_USB_CONFIG)
                {
                    // Push _PD_HPD_LOW into HPD_Queue
                    ScalerTypeCRx0PdPushHpd_EXINT0(_PD_HPD_LOW, 0);
                }

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // For DC_OFF Option = Charge Function Only
                if(GET_PD_RX0_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                {
                    // Disable Alt. Mode Resp When DC_OFF
                    CLR_PD_RX0_ALT_MODE_FUNCTION();

                    // Clear Exit Mode Request
                    CLR_PD_RX0_DP_ALT_MODE_EXIT_REQ();
                }

                // Clear DP Alt. Mode Status
                SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_NONE);
                CLR_PD_RX0_DP_ALT_MODE_ENTER();
                SET_PD_RX0_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);
                CLR_PD_RX0_PARTNER_INIT_ALT_MODE();

                ScalerDpRx0HpdToggleAuxPhyResetProc_EXINT0(_LOW);
                SET_PD_RX0_HPD_STATUS(_LOW);

                break;

            case _PD_ALT_MODE_INT_SEND_DP_STATUS_ACK:

                // "DP Status Ack" Only Access HPD Queue when (HPD Count > 0) & (Not Attn Wait)
                if((GET_PD_RX0_HPD_CNT() > 0) && (GET_PD_RX0_ATTENTION_WAIT() == _FALSE))
                {
                    // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                    if(GET_PD_RX0_HPD_SPACE_TIME(GET_PD_RX0_HPD_RPTR()) != 0)
                    {
                        SET_PD_RX0_ATTENTION_WAIT();
                        ScalerTypeCRx0PdActiveTimerEvent_EXINT0(GET_PD_RX0_HPD_SPACE_TIME(GET_PD_RX0_HPD_RPTR()), _SCALER_TIMER_EVENT_PD_RX0_CLR_ATTENTION_WAIT);
                    }

                    // Pop Out One HPD From Queue
                    ScalerTypeCRx0PdPopHpd_EXINT0();
                }

                break;

            case _PD_ALT_MODE_INT_SEND_DP_CONFIG_ACK:

                if(GET_PD_RX0_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_NONE)
                {
                    SET_PD_RX0_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);
                }
                else
                {
                    CLR_PD_RX0_DP_ALT_MODE_WAIT_CONFIG();
                    SET_PD_RX0_DP_ALT_MODE_CONFIG(_PD_DP_CONFIG);

                    // Cancel CLR_PARTNER_ALT_SUPPORT TimerEvent When Already Dp Config
                    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_CLR_PARTNER_ALT_SUPPORT);

                    // Cancel _T480_ERROR_RECOVERY TimerEvent When Already Dp Config
                    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_T480_ERROR_RECOVERY);

                    if(((GET_PD_RX0_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_RX0_CLR_PARTNER_ALT_SUPPORT) || (GET_PD_RX0_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_RX0_T480_ERROR_RECOVERY)) && (GET_PD_RX0_TIMER_EVENT_VALID() == _TRUE))
                    {
                        CLR_PD_RX0_TIMER_EVENT_VALID();
                    }

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                    if(GET_PD_RX0_DELL_ALT_MODE_ENTER() == _FALSE)
                    {
                        CLR_PD_RX0_DELL_AM_ENTER_TIMEOUT();

                        // Active WD Timer Event For Enter_Dell_Alt_Mode Timer (30ms), Timeout : SET_PD_RX0_DELL_AM_ENTER_TIMEOUT()
                        ScalerTimerWDActivateTimerEvent_EXINT0(_TYPE_C_EMB_DELL_ALT_MODE_ENTER_TIMEOUT_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_DELL_AM_ENTER_TIMEOUT);
                    }
#endif
                }

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    if(GET_PD_RX0_VDM_SVID() == _LENOVO_VID)
    {
        switch(GET_PD_RX0_LENOVO_ALT_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_PD_RX0_LENOVO_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // Clear HP Alt. Mode Status
                SET_PD_RX0_LENOVO_ALT_STATE(_PD_ALT_MODE_NONE);
                CLR_PD_RX0_LENOVO_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_LENOVO_GET_STATUS_ACK:

                CLR_PD_RX0_LENOVO_DOCK_EVENT();

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    if(GET_PD_RX0_VDM_SVID() == _ACER_VID)
    {
        switch(GET_PD_RX0_ACER_ALT_MODE_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_PD_RX0_ACER_ALT_MODE_ENTER();

                break;

            default:

                break;
        }
    }
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    if(GET_PD_RX0_VDM_SVID() == _HP_VID)
    {
        switch(GET_PD_RX0_HP_ALT_MODE_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_PD_RX0_HP_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // Clear HP Alt. Mode Status
                SET_PD_RX0_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
                CLR_PD_RX0_HP_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_HP_SET_CONFIG_ACK:

                // Set Atten_config User Event and Clear Retry CNT
                SET_PD_RX0_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_CONFIG);
                CLR_PD_RX0_HP_ATTEN_RETRY_CNT();

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    if(GET_PD_RX0_VDM_SVID() == _DELL_VID)
    {
        switch(GET_PD_RX0_DELL_ALT_MODE_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_PD_RX0_DELL_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // Clear Dell Alt. Mode Status
                SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
                CLR_PD_RX0_DELL_ALT_MODE_ENTER();
                SET_PD_RX0_DELL_AM_ENTER_TIMEOUT();

                break;

            case _PD_ALT_MODE_INT_SEND_DELL_0X12_ACK:

                // Clear Dell Alt. Mode Status
                SET_PD_RX0_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

    // Back to Ready State
    ScalerTypeCRx0PdBackToReadyState_EXINT0();
}
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Timer Event Proc of PD RX0
// Input Value  : enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT:

            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
            ScalerTypeCRx0PdUpdateTxFifoMsgHeader();

            switch(GET_PD_RX0_FW_STATE())
            {
                case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:

                    // Cable Response Discover ID Timeout : Send Src Cap
                    SET_PD_RX0_FW_STATE(_PD_SRC_SEND_CAP);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                    break;

                case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

                    // Cable Response Soft Reset Timeout : Send Discover ID
                    SET_PD_RX0_FW_STATE(_PD_SEND_CBL_DISCOVER_ID);
                    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                    break;

                case _PD_SRC_READY:
                case _PD_SNK_READY:

                    switch(GET_PD_RX0_SUB_STATE())
                    {
                        case _PD_SUB_CABLE_PROC:

                            switch(GET_PD_RX0_CBL_STATE())
                            {
                                case _PD_CBL_INT_WAIT_SOFT_RST_RESP:

                                    // Back to Ready State
                                    ScalerTypeCRx0PdBackToReadyState();
                                    SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                                    break;

                                case _PD_CBL_INT_WAIT_DISCOVER_ID_RESP:

                                    ADD_PD_RX0_CBL_VDM_NO_RESP_CNT();

                                    if(GET_PD_RX0_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                                    {
                                        SET_PD_RX0_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                                    }

                                    // Back to Ready State
                                    ScalerTypeCRx0PdBackToReadyState();
                                    SET_PD_RX0_CBL_STATE(_PD_CBL_STATE_NONE);
                                    SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                                    break;

                                default:

                                    break;
                            }

                            break;

                        default:

                            break;
                    }

                    break;

                default:

                    break;
            }

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT:

            if(GET_PD_RX0_FW_STATE() != _PD_HARDRESET)
            {
                switch(GET_PD_RX0_DP_ALT_STATE())
                {
                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP:

                        ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_ID);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP:

                        ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP:

                        ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP:

                        ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP:

                        ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP:

                        ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_STATUS);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP:

                        ADD_PD_RX0_PARTNER_VDM_NO_RESP_CNT();
                        SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);

                        break;

                    case _PD_ALT_MODE_READY:
                    default:

                        break;
                }

                SET_PD_RX0_VDMMSG_WAIT_FLAG();

                // Set AMS = None
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCRx0PdBackToReadyState();
            }

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY:

            SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

            ScalerTypeCRx0PdBackToReadyState();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER:

            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                // [0x6637][7:6] if(PD 3.0) Switch Rp to Default Rp (36K / 12K / 4.7K)
#if(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
                ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_DEF << 6));
#elif(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
                ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_1P5A << 6));
#else
                ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_3P0A << 6));
#endif  // End of #if(_TYPE_C_SRC_DEF_CUR == _SRC_DEF_USB)
            }

            // Turn On Vconn
            ScalerTypeCRx0CcVconnControl(_ON);

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
            SET_RX0_OCP_CURRENT((WORD)(((DWORD)(GET_CC_RX0_DEF_CUR()) * (DWORD)(GET_RX0_OCP_RATIO(0))) / 100));
#else
            SET_RX0_OCP_CURRENT((WORD)((DWORD)(GET_CC_RX0_DEF_CUR()) * _TYPE_C_DEF_OCP_RATIO / 100));
#endif

            // Turn On Vbus Power to vSafe5V
            ScalerTypeCPowerRx0VbusControl(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_RX0_OCP_CURRENT(), _PD_PEAK_CUR_NONE);

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER:

            // From : 1.Proc Hard Reset
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
            // Enable Vbus Discharge
            ScalerTypeCPmicRx0VbusDischarge(_ENABLE);
#endif

            // Turn Off Vbus Power
            ScalerTypeCPowerRx0VbusControl(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST:

            if(GET_PD_RX0_FW_STATE() == _PD_HARDRESET)
            {
                return;
            }

            // Separate "Normal Flow" & "S8 Interop" TimerEvent Since HRST Event Will be Canceled During Power Contract
            ScalerTypeCRx0PdSendHardRst();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_S8_HRST:

            if(GET_PD_RX0_FW_STATE() == _PD_HARDRESET)
            {
                return;
            }

            // If It is Already in DP Config, No Need to Do Hard Reset
            if(GET_PD_RX0_DP_ALT_MODE_CONFIG() != _PD_DP_CONFIG)
            {
                ScalerTypeCRx0PdSendHardRst();
            }

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER:

            SET_TYPE_C_ERROR_RECOVERY();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_REQ_WAIT:

            CLR_PD_RX0_REQ_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_PARTNER_ALT_SUPPORT:

            CLR_PD_RX0_PARTNER_ALT_SUPPORT();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_T480_ERROR_RECOVERY:

            SET_TYPE_C_ERROR_RECOVERY();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_PRS_WAIT:

            CLR_PD_RX0_PRS_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_DRS_WAIT:

            CLR_PD_RX0_DRS_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_VCS_WAIT:

            CLR_PD_RX0_VCS_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_CBL_WAIT:

            CLR_PD_RX0_CBL_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_DFP_START_ALT_MODE:

            SET_PD_RX0_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_ID);

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_LENOVO_RESP_TIMEOUT:

            CLR_PD_RX0_LENOVO_ATTN_SENT_FLAG();

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _SCALER_TIMER_EVENT_PD_RX0_SET_SRC_INIT_AMS:

            SET_PD_RX0_SRC_INIT_AMS();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_PPS_TIMEOUT:

            // PPS Timeout : Send Hard Reset
            ScalerTypeCRx0PdSendHardRst();

            break;
#endif  // End of #if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_ATTENTION_WAIT:

            CLR_PD_RX0_ATTENTION_WAIT();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_GET_SNK_CAP_WAIT:

            CLR_PD_RX0_GET_SNK_CAP_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_VDMMSG_WAIT:

            CLR_PD_RX0_VDMMSG_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_RX0_CLR_VDM_BUSY_FLAG:

            CLR_PD_RX0_VDM_BUSY_FLAG();

            break;

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
        case _SCALER_TIMER_EVENT_PD_RX0_DELL_ATTEN_RETRY:

            ADD_PD_RX0_DELL_ATTEN_RETRY_CNT();
            CLR_PD_RX0_DELL_ATTEN_WAIT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For OCP / OVP Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdOcpOvpProc(void)
{
    // Always Update Port Controller Event to Inform System / User of Events Occurred
    if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
    {
        SET_PD_RX0_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_OCP);
    }
    else if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
    {
        SET_PD_RX0_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_OVP);
    }

#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_ERROR_RECOVERY)
    // Set Error Recovery
    SET_TYPE_C_ERROR_RECOVERY();
    CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP);
#elif(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
    // Clear OCP/OVP Event when (FW_STATE = _PD_HARDRESET in Main Loop) or (Power Contract Established in EXINT0)
    // PMIC OCP or OVP Triggered : (PD2.0 || Power Contract Not Ready) : Hard Reset, (PD3.0 && Power Contract Ready) : Alert + Hard Reset
    if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0) || (GET_PD_RX0_EXPLICIT_CONTRACT() == _FALSE))
    {
        ScalerTypeCRx0PdSendHardRst();
    }
    else if(GET_PD_RX0_ALERT_SENT() == _FALSE)
    {
        SET_PD_RX0_SUB_STATE(_PD_SUB_SEND_ALERT);
    }
#elif(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
    // User directly Design the Processing Flow. Embedded Do Nothing but will refer to the Port Controller Event!
    CLR_PD_RX0_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP);
#endif
}

//--------------------------------------------------
// Description  : WD Timer Event Proc of PD RX0
// Input Value  : enumEventID, pucActiveWDID, pucActiveWDTime
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime) using 3
{
    // Only Run PD WD Timer Event Proc When CC is Attached
    if(GET_CC_RX0_ATTACHED() == _FALSE)
    {
        return;
    }

    switch(enumEventID)
    {
        case _SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT:

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
            if(GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_WAIT_STATUS)
            {
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                ScalerTypeCRx0PdBackToReadyState_WDINT();
            }
            else
#endif
            {
                // Send Hard Reset
                ScalerTypeCRx0PdSendHardRst_WDINT(pucActiveWDID, pucActiveWDTime);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_RX0_PS_TRANSITION_TIMEOUT:

            if(GET_PD_RX0_FW_STATE() != _PD_HARDRESET)
            {
                // Send Hard Reset when PSTransitionTimer timeout (450 ~ 550ms)
                ScalerTypeCRx0PdSendHardRst_WDINT(pucActiveWDID, pucActiveWDTime);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER:

            // From : 1.SRC Rcv Accpet PRS 2.SRC Send Accept PRS 3.HRST_EXINT 4.HRST_WDINT
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
            // Enable Vbus Discharge
            ScalerTypeCPmicRx0VbusDischarge_WDINT(_ENABLE);
#endif

            // Adjust Power (Turn Off Vbus)
            ScalerTypeCPowerRx0VbusControl_WDINT(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

            break;

        case _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER:

            if(GET_PD_RX0_FW_STATE() != _PD_HARDRESET)
            {
                // Adjust Power (Turn ON Vbus) and Clear Adjust Power Flag
                ScalerTypeCPowerRx0VbusControl_WDINT(_ON, _PD_POWER_SRC, GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1), GET_PD_RX0_PARTNER_REQ_VOL(), GET_RX0_OCP_CURRENT(), GET_PD_RX0_SRC_CAP_PEAK(GET_PD_RX0_PARTNER_OBJ_POS() - 1));

                // Update PDO Status
                SET_PD_RX0_PDO_STATUS_VOL(GET_PD_RX0_PARTNER_REQ_VOL());
                SET_PD_RX0_PDO_STATUS_CUR(GET_PD_RX0_PARTNER_MAX_CUR());

                // State Transition
                SET_PD_RX0_FW_STATE(_PD_SRC_INT_SEND_PSRDY);

                // Active WD Timer to Check Vbus, Then Start PMIC Protection and Send PS_RDY if Vbus Ready
                *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_RX0_CHECK_PSRDY;

                if(GET_PD_RX0_REQ_VOL_SMALL_STEP() != _TRUE)
                {
                    *pucActiveWDTime = _SRC_SEND_PS_RDY_FIX_VOLTAGE_TIMER;
                }
                else
                {
                    *pucActiveWDTime = _SRC_SEND_PS_RDY_PPS_MODE_TIMER;
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_RX0_CHECK_PSRDY:

            if(GET_PD_RX0_FW_STATE() == _PD_SRC_INT_SEND_PSRDY)
            {
                ADD_DP_RX0_CHECK_VBUS_CNT();

                if((ScalerTypeCPowerRx0CheckVbusReady_WDINT(GET_PD_RX0_PDO_STATUS_VOL()) == _TRUE) || (GET_DP_RX0_CHECK_VBUS_CNT() >= 8))
                {
                    CLR_DP_RX0_CHECK_VBUS_CNT();

#if((_TYPE_C_PMIC_TYPE != _PMIC_NONE) && (_TYPE_C_PMIC_CHECK_SUPPORT == _ON))
                    // Start PMIC Protection
                    ScalerTypeCPmicRx0ProtectStart_WDINT();
#endif

                    // Send "PS_RDY" After Accept to Request
                    ScalerTypeCRx0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_RX0_CHECK_PSRDY;

                    if(GET_PD_RX0_REQ_VOL_SMALL_STEP() != _TRUE)
                    {
                        *pucActiveWDTime = _SRC_SEND_PS_RDY_FIX_VOLTAGE_TIMER;
                    }
                    else
                    {
                        *pucActiveWDTime = _SRC_SEND_PS_RDY_PPS_MODE_TIMER;
                    }
                }
            }
            else if((GET_PD_RX0_FW_STATE() == _PD_SNK_READY) && (GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_SEND_SRC_ON_PSRDY))
            {
                ADD_DP_RX0_CHECK_VBUS_CNT();

                if((ScalerTypeCPowerRx0CheckVbusReady_WDINT(500) == _TRUE) || (GET_DP_RX0_CHECK_VBUS_CNT() >= 8))
                {
                    CLR_DP_RX0_CHECK_VBUS_CNT();

#if((_TYPE_C_PMIC_TYPE != _PMIC_NONE) && (_TYPE_C_PMIC_CHECK_SUPPORT == _ON))
                    // Start PMIC Protection
                    ScalerTypeCPmicRx0ProtectStart_WDINT();
#endif

                    // Send "PS_RDY" After PRS to SRC and Vbus Has Been Turned On
                    SET_PD_RX0_POWER_ROLE(_PD_POWER_SRC);
                    ScalerTypeCRx0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_RX0_CHECK_PSRDY;
                    *pucActiveWDTime = 35;
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG:

            if(GET_PD_RX0_FW_STATE() != _PD_HARDRESET)
            {
                if(GET_PD_RX0_FW_STATE() == _PD_SRC_SEND_CAP)
                {
                    // Send "PS_RDY" After Accept to Request
                    ScalerTypeCRx0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
                }
                else if(GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_SEND_VCONN_ON_PSRDY)
                {
                    // Set Vconn Role to Vconn SRC
                    SET_PD_RX0_VCONN_ROLE(_PD_VCONN_SRC);

                    // [0x6534] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
                    ScalerSetByte_EXINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // Send "PS_RDY"
                    ScalerTypeCRx0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_RX0_STATE_TO_READY:

            if(GET_PD_RX0_FW_STATE() != _PD_HARDRESET)
            {
                SET_PD_RX0_AMS_STATUS(_PD_AMS_NONE);

                // If BIST Carrier Mode, Reset PHY State Machine and Turn Off BIST Mode
                if(GET_PD_RX0_SUB_STATE() == _PD_SUB_BIST_MODE)
                {
                    // Reset PHY FSM
                    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~(_BIT0), 0x00);

                    // Turn Off BIST UUT Carrier Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

                    // Begin PHY FSM
                    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~(_BIT0), _BIT0);

                    // Enable Rcv Msg INT
                    ScalerTypeCRx0PdRxIntControl_WDINT(_ENABLE);
                }
                else if(GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_WAIT_VCS_RESP)
                {
                    SET_PD_RX0_VCS_REJECT();
                }
                else if(GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_WAIT_DRS_RESP)
                {
                    SET_PD_RX0_DRS_REJECT();
                }
                else if(GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_WAIT_PRS_RESP)
                {
                    SET_PD_RX0_PRS_REJECT();
                }

                ScalerTypeCRx0PdBackToReadyState_WDINT();
            }

            break;

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
        case _SCALER_WD_TIMER_EVENT_PD_RX0_DELL_AM_ENTER_TIMEOUT:

            SET_PD_RX0_DELL_AM_ENTER_TIMEOUT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Rx0 PD Power Switch Proc
// Input Value  : enumPowerAction : Power Switch Enum
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // Set DP Alt Mode Lane Mapping
            ScalerDpRx0SetDpAltModeLaneMapping(GET_PD_RX0_PIN_ASSIGNMENT(), GET_CC_RX0_ORIENTATION());

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Source Cap Count Change
// Input Value  : ucPdoCount
// Output Value : enumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCRx0PdCheckPdoCountChange(BYTE ucPdoCount)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    if(GET_PD_RX0_SRC_PDO_CNT() != ucPdoCount)
    {
        enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Check Source Cap Change
// Input Value  : ucPdoIndex : 1~7 / stTypeCUserPdo
// Output Value : enumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCRx0PdCheckPdoChange(BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    if(GET_PD_RX0_SRC_PDO_TYPE(ucPdoIndex - 1) != stTypeCUserPdo.enumPdoType)
    {
        enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
    }

    if(GET_PD_RX0_SRC_PDO_TYPE(ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
    {
        if(GET_PD_RX0_SRC_CAP_PEAK(ucPdoIndex - 1) != stTypeCUserPdo.enumPeakCurrent)
        {
            enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
        }

        if((GET_PD_RX0_SRC_CAP_VOL_MAX(ucPdoIndex - 1) / 10) != stTypeCUserPdo.ucMaxVoltage)
        {
            enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
        }

        if(GET_PD_RX0_SRC_CAP_CUR(ucPdoIndex - 1) != stTypeCUserPdo.usMaxCurrent)
        {
            enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
        }
    }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    else if(GET_PD_RX0_SRC_PDO_TYPE(ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
    {
        if((GET_PD_RX0_SRC_CAP_VOL_MAX(ucPdoIndex - 1) / 10) != stTypeCUserPdo.ucMaxVoltage)
        {
            enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
        }

        if((GET_PD_RX0_SRC_CAP_VOL_MIN(ucPdoIndex - 1) / 10) != stTypeCUserPdo.ucMinVoltage)
        {
            enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
        }

        if(GET_PD_RX0_SRC_CAP_CUR(ucPdoIndex - 1) != (stTypeCUserPdo.usMaxCurrent / 5))
        {
            enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
        }
    }
#endif

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Set Source Cap Fix PDO Info
// Input Value  : enumPowerRole(_TYPE_C_POWER_SRC/SNK), ucPdoIndex : 1~7 / enumPdoType / usVoltage (100mV) / usMaxCur (10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetFixPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumPDPeakCurType enumPeakCur)
{
    // Convert Voltage from User 100mV to Fix PDO 10mV
    usVoltage = usVoltage * 10;

    usMaxCur = usMaxCur;

    enumPeakCur = enumPeakCur;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Check Src PDO Index is Valid and PDO Power < Max Power
        if((ucPdoIndex >= 1) && (ucPdoIndex <= 7) && ((WORD)((DWORD)usVoltage * usMaxCur / 1000) <= GET_RX0_MAX_POWER()))
        {
            SET_PD_RX0_SRC_PDO_TYPE((ucPdoIndex - 1), _PD_FIX_SUPPLY_PDO);

            // Set Peak Current
            SET_PD_RX0_SRC_CAP_PEAK((ucPdoIndex - 1), enumPeakCur);

            // -------------------- Voltage Setting --------------------
            if(usVoltage <= 2000)
            {
                // Other PDOs Voltage Cannot More Than 20V
                SET_PD_RX0_SRC_CAP_VOL_MAX((ucPdoIndex - 1), usVoltage);
                SET_PD_RX0_SRC_CAP_VOL_MIN((ucPdoIndex - 1), usVoltage);
            }
            else
            {
                SET_PD_RX0_SRC_CAP_VOL_MAX((ucPdoIndex - 1), 2000);
                SET_PD_RX0_SRC_CAP_VOL_MIN((ucPdoIndex - 1), 2000);
            }

            // -------------------- Current Setting --------------------
            if(usMaxCur <= 500)
            {
                SET_PD_RX0_SRC_CAP_CUR((ucPdoIndex - 1), usMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_PD_RX0_SRC_CAP_CUR((ucPdoIndex - 1), 500);
            }
        }
        else
        {
            if((usVoltage * usMaxCur / 1000) > GET_RX0_MAX_POWER())
            {
                DebugMessageSystem("8. [TYPE C] ==========X Set Fix PDO Error : PDO > Max Power", ucPdoIndex);
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] ==========X Set Fix PDO Index Error", ucPdoIndex);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set Sink Capability
        if((ucPdoIndex >= 1) && (ucPdoIndex <= 7))
        {
            SET_PD_RX0_SNK_PDO_TYPE((ucPdoIndex - 1), _PD_FIX_SUPPLY_PDO);

            // -------------------- Voltage Setting --------------------
            if(usVoltage <= 2000)
            {
                // Other PDOs Voltage Cannot More Than 20V
                SET_PD_RX0_SNK_CAP_VOL_MAX((ucPdoIndex - 1), usVoltage);
                SET_PD_RX0_SNK_CAP_VOL_MIN((ucPdoIndex - 1), usVoltage);
            }
            else
            {
                SET_PD_RX0_SNK_CAP_VOL_MAX((ucPdoIndex - 1), 2000);
                SET_PD_RX0_SNK_CAP_VOL_MIN((ucPdoIndex - 1), 2000);
            }

            // -------------------- Current Setting --------------------
            if(usMaxCur <= 500)
            {
                SET_PD_RX0_SNK_CAP_CUR((ucPdoIndex - 1), usMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_PD_RX0_SNK_CAP_CUR((ucPdoIndex - 1), 500);
            }
        }
    }
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Source Cap Argumented PDO (PPS) Info
// Input Value  : enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 2~7 / ucMaxVol (100mV) / ucMinVol(100mV) / ucMaxCur (50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetArgumentedPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur)
{
    // Convert Voltage from User 100mV to Fix PDO 10mV
    WORD usMaxVoltage = (WORD)ucMaxVol * 10;
    WORD usMinVoltage = (WORD)ucMinVol * 10;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // The 1st PDO Cannot Be Argumented PDO (Must Be Fix PDO with 5V), PDO Power Must < Max Power
        if((ucPdoIndex >= 2) && (ucPdoIndex <= 7))
        {
            SET_PD_RX0_SRC_PDO_TYPE((ucPdoIndex - 1), _PD_3_PROGRAMMABLE_PDO);

            // Reset Peak Current Setting
            SET_PD_RX0_SRC_CAP_PEAK((ucPdoIndex - 1), _PD_PEAK_CUR_NONE);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 21V
            if(usMaxVoltage <= 2100)
            {
                SET_PD_RX0_SRC_CAP_VOL_MAX((ucPdoIndex - 1), (WORD)usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 21V
                SET_PD_RX0_SRC_CAP_VOL_MAX((ucPdoIndex - 1), 2100);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 3V
                if(usMinVoltage < 300)
                {
                    usMinVoltage = 300;
                }

                SET_PD_RX0_SRC_CAP_VOL_MIN((ucPdoIndex - 1), (WORD)usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_PD_RX0_SRC_CAP_VOL_MIN((ucPdoIndex - 1), (WORD)usMaxVoltage);
            }

            // -------------------- Current Setting --------------------
            if(ucMaxCur <= 100)
            {
                SET_PD_RX0_SRC_CAP_CUR((ucPdoIndex - 1), (WORD)ucMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_PD_RX0_SRC_CAP_CUR((ucPdoIndex - 1), 100);
            }
        }
        else
        {
            if(((WORD)ucMaxVol * ucMaxCur / 20) > GET_RX0_MAX_POWER())
            {
                DebugMessageSystem("8. [TYPE C] ==========X Set Fix PDO Error : PDO > Max Power", ucPdoIndex);
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] ==========X Set Fix PDO Index Error", ucPdoIndex);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Sink Capability
        if((ucPdoIndex >= 2) && (ucPdoIndex <= 7))
        {
            SET_PD_RX0_SNK_PDO_TYPE((ucPdoIndex - 1), _PD_3_PROGRAMMABLE_PDO);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 21V
            if(usMaxVoltage <= 2100)
            {
                SET_PD_RX0_SNK_CAP_VOL_MAX((ucPdoIndex - 1), (WORD)usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 21V
                SET_PD_RX0_SNK_CAP_VOL_MAX((ucPdoIndex - 1), 2100);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 3V
                if(usMinVoltage < 300)
                {
                    usMinVoltage = 300;
                }

                SET_PD_RX0_SNK_CAP_VOL_MIN((ucPdoIndex - 1), (WORD)usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_PD_RX0_SNK_CAP_VOL_MIN((ucPdoIndex - 1), (WORD)usMaxVoltage);
            }

            // -------------------- Current Setting --------------------
            if(ucMaxCur <= 100)
            {
                SET_PD_RX0_SNK_CAP_CUR((ucPdoIndex - 1), (WORD)ucMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_PD_RX0_SNK_CAP_CUR((ucPdoIndex - 1), 100);
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Set Request Content to Kernel
// Input Value  : StructTypeCUserRDO(Object Position, ReqInfo1, ReqInfo2, Cap Mismatch)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetRdo(StructTypeCUserRDO stTypeCUserRdo)
{
    SET_PD_RX0_REQ_OBJ_POS(stTypeCUserRdo.enumObjPos);
    SET_PD_RX0_REQ_CAP_MIS(stTypeCUserRdo.b1CapMismatch);

    // Give Back Flag Define By Kernel
    SET_PD_RX0_REQ_GIVE_BACK(_GIVE_BACK);

    if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(GET_PD_RX0_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
    {
        // RDO[19:10] : Fix RDO (Op. Cur in 10mA)
        SET_PD_RX0_REQ_INFO_1((stTypeCUserRdo.usReqInfo1) & 0x3FF);

        // RDO[9:0] : Fix RDO (Max. Cur in 10mA)
        SET_PD_RX0_REQ_INFO_2((stTypeCUserRdo.usReqInfo2) & 0x3FF);
    }
    else
    {
        // RDO[19:9] : PPS RDO (Vol in 20mV)
        SET_PD_RX0_REQ_INFO_1((stTypeCUserRdo.usReqInfo1) & 0x7FF);

        // RDO[6:0] : PPS RDO (Op. Cur in 50mA)
        SET_PD_RX0_REQ_INFO_2((stTypeCUserRdo.usReqInfo2) & 0x7F);
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Set PD Power Protect Info
// Input Value  : ucPdoIndex , stTypeCUserProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetProtectInfo(BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo)
{
    SET_RX0_OCP_RATIO((ucPdoIndex - 1), stTypeCUserProtectInfo.ucOcpCurRatio);
}
#endif

//--------------------------------------------------
// Description  : Get TypeC Product Type when in UFP Data Role
// Input Value  : None
// Output Value : _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_UFP_PRODUCT_TYPE_HUB / _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL
//--------------------------------------------------
EnumTypeCUFPProductType ScalerTypeCRx0PdGetUFPProductType(void)
{
    return GET_PD_RX0_UFP_PRODUCT_TYPE();
}

//--------------------------------------------------
// Description  : Get TypeC Product Type when in DFP Data Role
// Input Value  : None
// Output Value : _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_DFP_PRODUCT_TYPE_HUB / _TYPE_C_DFP_PRODUCT_TYPE_HOST / _TYPE_C_DFP_PRODUCT_TYPE_BRICK
//--------------------------------------------------
EnumTypeCDFPProductType ScalerTypeCRx0PdGetDFPProductType(void)
{
    return GET_PD_RX0_DFP_PRODUCT_TYPE();
}

//--------------------------------------------------
// Description  : Clear and Disable All of Certain Rx FIFO IRQs
// Input Value  : enumFifo : _RX_FIFO_0 / _RX_FIFO_1 / _RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRxFifoClear(EnumRxFifoIndex enumFifo)
{
    BYTE ucRxWaitCnt = 0;

    // Clear FIFO Only When Rx is Idle (H/W 0x6542 fifo_used Can Only Be Cleared When RX PTCL FSM = IDLE)
    while((ScalerGetByte(P65_21_RX_STATE_MACHINE_L) != 0x01) && (ucRxWaitCnt < 20))
    {
        ucRxWaitCnt ++;
        DELAY_XUS(100);
    }

    switch(enumFifo)
    {
        case _PD_RX_FIFO_0:

            ScalerSetByte(P65_50_RX_FIFO0_RCV_MSG_INT, 0xAA);
            ScalerSetByte(P65_51_RX_FIFO0_RCV_ERR_INT, 0x7F);
            ScalerSetByte(P65_52_RX_FIFO0_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte(P65_53_RX_FIFO0_MSG_MIS_FLAG, 0x79);
            ScalerSetByte(P65_60_RX_FIFO0_SP_MSG_INT, 0xAA);
            ScalerSetByte(P65_62_RX_FIFO0_MSG_INT, 0xAA);
            ScalerSetBit(P65_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            break;

        case _PD_RX_FIFO_1:

            ScalerSetByte(P65_70_RX_FIFO1_RCV_MSG_INT, 0xAA);
            ScalerSetByte(P65_71_RX_FIFO1_RCV_ERR_INT, 0x7F);
            ScalerSetByte(P65_72_RX_FIFO1_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte(P65_73_RX_FIFO1_MSG_MIS_FLAG, 0x79);
            ScalerSetByte(P65_80_RX_FIFO1_SP_MSG_INT, 0xAA);
            ScalerSetByte(P65_82_RX_FIFO1_MSG_INT, 0xAA);
            ScalerSetBit(P65_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            break;

        case _PD_RX_FIFO_2:

            ScalerSetByte(P65_90_RX_FIFO2_RCV_MSG_INT, 0xAA);
            ScalerSetByte(P65_91_RX_FIFO2_RCV_ERR_INT, 0x7F);
            ScalerSetByte(P65_92_RX_FIFO2_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte(P65_93_RX_FIFO2_MSG_MIS_FLAG, 0x79);
            ScalerSetByte(P65_A0_RX_FIFO2_SP_MSG_INT, 0xAA);
            ScalerSetByte(P65_A2_RX_FIFO2_MSG_INT, 0xAA);
            ScalerSetBit(P65_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            break;
        default:
            // Should Not Happens
            break;
    }
}

//--------------------------------------------------
// Description  : Clear and Disable All of Certain Rx FIFO IRQs @ Interrupt
// Input Value  : enumFifo : _RX_FIFO_0 / _RX_FIFO_1 / _RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRxFifoClear_EXINT0(EnumRxFifoIndex enumFifo) using 1
{
    BYTE ucRxWaitCnt = 0;

    // Clear FIFO Only When Rx is Idle (H/W 0x6542 fifo_used Can Only Be Cleared When RX PTCL FSM = IDLE)
    while((ScalerGetByte_EXINT(P65_21_RX_STATE_MACHINE_L) != 0x01) && (ucRxWaitCnt < 20))
    {
        ucRxWaitCnt ++;
        DELAY_XUS_EXINT(100);
    }

    switch(enumFifo)
    {
        case _PD_RX_FIFO_0:

            ScalerSetByte_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT, 0xAA);
            ScalerSetByte_EXINT(P65_51_RX_FIFO0_RCV_ERR_INT, 0x7F);
            ScalerSetByte_EXINT(P65_52_RX_FIFO0_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte_EXINT(P65_53_RX_FIFO0_MSG_MIS_FLAG, 0x79);
            ScalerSetByte_EXINT(P65_60_RX_FIFO0_SP_MSG_INT, 0xAA);
            ScalerSetByte_EXINT(P65_62_RX_FIFO0_MSG_INT, 0xAA);
            ScalerSetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            break;

        case _PD_RX_FIFO_1:

            ScalerSetByte_EXINT(P65_70_RX_FIFO1_RCV_MSG_INT, 0xAA);
            ScalerSetByte_EXINT(P65_71_RX_FIFO1_RCV_ERR_INT, 0x7F);
            ScalerSetByte_EXINT(P65_72_RX_FIFO1_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte_EXINT(P65_73_RX_FIFO1_MSG_MIS_FLAG, 0x79);
            ScalerSetByte_EXINT(P65_80_RX_FIFO1_SP_MSG_INT, 0xAA);
            ScalerSetByte_EXINT(P65_82_RX_FIFO1_MSG_INT, 0xAA);
            ScalerSetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            break;

        case _PD_RX_FIFO_2:

            ScalerSetByte_EXINT(P65_90_RX_FIFO2_RCV_MSG_INT, 0xAA);
            ScalerSetByte_EXINT(P65_91_RX_FIFO2_RCV_ERR_INT, 0x7F);
            ScalerSetByte_EXINT(P65_92_RX_FIFO2_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte_EXINT(P65_93_RX_FIFO2_MSG_MIS_FLAG, 0x79);
            ScalerSetByte_EXINT(P65_A0_RX_FIFO2_SP_MSG_INT, 0xAA);
            ScalerSetByte_EXINT(P65_A2_RX_FIFO2_MSG_INT, 0xAA);
            ScalerSetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            break;

        default:
            // Should Not Happens
            break;
    }
}

//--------------------------------------------------
// Description  : PD Update Unconstrained Powered Bit Whenever Power Status Changed
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdUpdateUnconstrainedPow(void)
{
    if(GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE)
    {
        // Check Local Power Off
        if(ScalerTypeCPowerCheckLocPowExist(_OFF) == _TRUE)
        {
            // Update Unconstrained Powered Bit
            SET_PD_RX0_UNCONSTRAIN_POWER(_FALSE);
        }
    }
    else if(GET_PD_RX0_UNCONSTRAIN_POWER() == _FALSE)
    {
        // Check Local Power On
        if(ScalerTypeCPowerCheckLocPowExist(_ON) == _TRUE)
        {
            // Update Unconstrained Powered Bit
            SET_PD_RX0_UNCONSTRAIN_POWER(_TRUE);
        }
    }
}


//--------------------------------------------------
// Description  : Enable / Disable FIFO_0/1/2 Interrupt when Rcv Msg.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRxIntControl(bit b1Action)
{
    if(b1Action == _ENABLE)
    {
        // Enable Rx Rcv Msg IRQ
        ScalerSetBit(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);
    }
    else
    {
        // Disable Rx Rcv Msg IRQ
        ScalerSetBit(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable FIFO_0/1/2 Interrupt when Rcv Msg.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRxIntControl_EXINT0(bit b1Action) using 1
{
    if(b1Action == _ENABLE)
    {
        // Enable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);
    }
    else
    {
        // Disable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable FIFO_0/1/2 WDINT when Rcv Msg.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRxIntControl_WDINT(bit b1Action) using 3
{
    if(b1Action == _ENABLE)
    {
        // Enable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);
    }
    else
    {
        // Disable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdUpdateCableRetryCounter(void)
{
    if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0) && (GET_PD_RX0_CBL_SPEC_VER() == _PD_VERSION_3_0))
    {
        ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
    else
    {
        ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdUpdatePortPartnerRetryCounter(void)
{
    if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0)
    {
        ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        ScalerSetBit(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
}

//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdUpdatePortPartnerRetryCounter_EXINT0(void) using 1
{
    if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0)
    {
        ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
}

//--------------------------------------------------
// Description  : Update PR/DR/Spec Version In Msg Header For SOP Communication.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdUpdateTxFifoMsgHeader(void)
{
    // [3] Power Role / [2:1] Spec Version / [0] Data Role
    ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_PD_RX0_POWER_ROLE() << 3);
    ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_PD_RX0_SPEC_VER() << 1);
    ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_PD_RX0_DATA_ROLE());
}

//--------------------------------------------------
// Description  : Update PR/DR/Spec Version In Msg Header For SOP Communication in Interrupt.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdUpdateTxFifoMsgHeader_EXINT0(void) using 1
{
    // [3] Power Role / [2:1] Spec Version / [0] Data Role
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_PD_RX0_POWER_ROLE() << 3);
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_PD_RX0_SPEC_VER() << 1);
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_PD_RX0_DATA_ROLE());
}

//--------------------------------------------------
// Description  : Go Back To Src/Snk Ready State According to Power Role
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdBackToReadyState(void)
{
    // Back to Ready State
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        SET_PD_RX0_FW_STATE(_PD_SRC_READY);
        SET_PD_RX0_SUB_STATE(_PD_SUB_SRC_READY);
    }
    else
    {
        SET_PD_RX0_FW_STATE(_PD_SNK_READY);
        SET_PD_RX0_SUB_STATE(_PD_SUB_SNK_READY);
    }
}

//--------------------------------------------------
// Description  : Go Back To Src/Snk Ready State According to Power Role In Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdBackToReadyState_EXINT0(void) using 1
{
    // Back to Ready State
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        SET_PD_RX0_FW_STATE(_PD_SRC_READY);
        SET_PD_RX0_SUB_STATE(_PD_SUB_SRC_READY);
    }
    else
    {
        SET_PD_RX0_FW_STATE(_PD_SNK_READY);
        SET_PD_RX0_SUB_STATE(_PD_SUB_SNK_READY);
    }
}

//--------------------------------------------------
// Description  : Go Back To Src/Snk Ready State According to Power Role In WD Timer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdBackToReadyState_WDINT(void) using 3
{
    // Back to Ready State
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        SET_PD_RX0_FW_STATE(_PD_SRC_READY);
        SET_PD_RX0_SUB_STATE(_PD_SUB_SRC_READY);
    }
    else
    {
        SET_PD_RX0_FW_STATE(_PD_SNK_READY);
        SET_PD_RX0_SUB_STATE(_PD_SUB_SNK_READY);
    }
}

//--------------------------------------------------
// Description  : Set Flag & Time in Interrupt For Main Loop to Active Timer Event
// Input Value  : enumEventID : Timer Event / usTime : Timeout Time
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdActiveTimerEvent_EXINT0(WORD usTime, EnumScalerTimerEventID enumEventID) using 1
{
    SET_PD_RX0_TIMER_EVENT_ID(enumEventID);
    SET_PD_RX0_TIMER_EVENT_CNT(usTime);
    SET_PD_RX0_TIMER_EVENT_VALID();
}

//--------------------------------------------------
// Description  : Cancel All Timer Events When CC Unattach
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdUnattachCancelTimerEvent(void)
{
    CLR_PD_RX0_TIMER_EVENT_VALID();

    // Cancel Timer Event
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_VDM_RESP_TIMEOUT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_S8_HRST);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_CLR_CBL_WAIT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_CLR_GET_SNK_CAP_WAIT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_CLR_VDMMSG_WAIT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_CLR_VDM_BUSY_FLAG);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_PPS_TIMEOUT);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_RX0_DELL_ATTEN_RETRY);
#endif

    // Cancel WD Timer Event
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_RX0_PS_TRANSITION_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_RX0_CHECK_PSRDY);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG);
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_RX0_DELL_AM_ENTER_TIMEOUT);
#endif
}

//--------------------------------------------------
// Description  : Check if Tx HW is Avaliable (PD 3.0 : Check TxSinkOK/NG, PD 2.0 : Check PHY Idle)
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCRx0PdTxAvaliable(void)
{
    bit bCheckResult = _FALSE;

    if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
    {
        if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
        {   // SRC Should Change Rp to "SinkTxNG" Before Initiating AMS
            if(ScalerGetBit(P66_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == _PD_SINK_TX_NG)
            {   // Rp = SinkTxNG (Source is OK to Send Message When SRC_INIT_AMS = TRUE)
                bCheckResult = GET_PD_RX0_SRC_INIT_AMS();
            }
            else
            {   // Rp = SinkTxOK, Change Rp to SinkTxNG (CLR_SRC_INIT_AMS, and Set to TRUE After Timer timeout)
                ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_NG);

                CLR_PD_RX0_SRC_INIT_AMS();

                // Source Can Initiate AMS 16-20ms After Change Rp to SinkTxNG
                ScalerTimerActiveTimerEvent(_SRC_INIT_AMS_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SET_SRC_INIT_AMS);

                bCheckResult = _FALSE;
            }
        }
        else
        {
            if(ScalerTypeCRx0CcDetResistor() == _DET_RP_3P0A)
            {   // Rp = SinkTxOK (Rp 3.0A)
                bCheckResult = _TRUE;
            }
            else
            {   // Rp = SinkTxNG (Rp 1.5A)
                bCheckResult = _FALSE;
            }
        }
    }
    else
    {   // Check PHY Idle
        if(ScalerGetBit(P65_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2)
        {   // PHY Idle Flag = 1
            bCheckResult = _TRUE;
        }
        else
        {   // PHY Idle Flag = 0
            bCheckResult = _FALSE;
        }
    }
    return bCheckResult;

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_PD_FW_DEBUG == _ON))
    DebugMessageTypeC("[PD] Tx Avaliable Check : ", bCheckResult);
#endif
}

//--------------------------------------------------
// Description  : Check if Alt Mode is Urgent or not
// Input Value  : None
// Output Value : _PD_ALT_MODE_NOT_URGENT / _PD_ALT_MODE_URGENT
//--------------------------------------------------
EnumTypeCPDAltModeUrgentStatus ScalerTypeCRx0PdAltModeUrgentEvent(void)
{
    EnumTypeCPDAltModeUrgentStatus enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;

    if(GET_PD_RX0_DATA_ROLE() == _PD_DATA_DFP)
    {
        enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;
    }
    else
    {
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
        if((GET_PD_RX0_DELL_AM_INIT_COMPLETE() == _FALSE) && (GET_PD_RX0_DELL_AM_ENTER_TIMEOUT() == _FALSE))
        {
            enumAltModeUrgentStatus = _PD_ALT_MODE_URGENT;
        }
        else
        {
            enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;
        }
#else
        enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;
#endif
    }

    return enumAltModeUrgentStatus;
}

//--------------------------------------------------
// Description  : Record Cable Info Of Discover ID Ack
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSaveCableDiscoverIdAckInfo_EXINT0(void) using 1
{
    // ID Header VDO, Bit[26] Modal Operation Support: Y/N
    if((g_pucDataObj_EXINT[4] & _BIT2) == _BIT2)
    {
        SET_PD_RX0_CBL_MODAL_OPERATION_SUPPORT();
    }

    // Bit[29:27] SOP' Product Type(Passive Cable / Active Cable / VPD)
    if((g_pucDataObj_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == (_BIT4 | _BIT3))
    {
        SET_PD_RX0_CBL_PRODUCT_TYPE(_PD_PASSIVE_CABLE);
    }
    else if((g_pucDataObj_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == _BIT5)
    {
        SET_PD_RX0_CBL_PRODUCT_TYPE(_PD_ACTIVE_CABLE);
    }
    else if((g_pucDataObj_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4))
    {
        SET_PD_RX0_CBL_PRODUCT_TYPE(_PD_VCONN_POWERED_USB_DEVICE);
    }

    // Passive Cable VDO
    if(GET_PD_RX0_CBL_PRODUCT_TYPE() == _PD_PASSIVE_CABLE)
    {
        // Bit[12:11] Cable Termination Type
        if((g_pucDataObj_EXINT[18] & (_BIT4 | _BIT3)) == 0x00)
        {
            CLR_PD_RX0_CBL_VCONN_REQUIRED();
        }

        // Bit[10:9] Max Vbus Voltage
        if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == 0x00)
        {
            // Cable Max Voltage = 20V = 200 * 100mV
            SET_PD_RX0_CBL_MAX_VOL(200);
        }
        else if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == _BIT1)
        {
            SET_PD_RX0_CBL_MAX_VOL(300);
        }
        else if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == _BIT2)
        {
            SET_PD_RX0_CBL_MAX_VOL(400);
        }
        else if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == (_BIT2 | _BIT1))
        {
            SET_PD_RX0_CBL_MAX_VOL(500);
        }

        // Bit[6:5] Cable Max Vbus Current
        if((g_pucDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT5)
        {
            // Cable Max Current = 3.0A = 300 * 10mA
            SET_PD_RX0_CBL_MAX_CUR(300);
        }
        else if((g_pucDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT6)
        {
            SET_PD_RX0_CBL_MAX_CUR(500);
        }

        // Bit[2:0] Cable USB Highest Speed
        if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_2_ONLY);
        }
        else if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3_GEN1);
        }
        else if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3OR4_GEN2);
        }
        else if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_4_GEN3);
        }
    }
    else if(GET_PD_RX0_CBL_PRODUCT_TYPE() == _PD_ACTIVE_CABLE)
    {
        // Active Cable VDO1
        // Bit[12:11] Cable Termination Type
        if((g_pucDataObj_EXINT[18] & (_BIT4 | _BIT3)) == _BIT4)
        {
            SET_PD_RX0_CBL_TERMINATION_TYPE(_PD_CBL_ONE_ACTIVE_ONE_PASSIVE);
        }
        else if((g_pucDataObj_EXINT[18] & (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
        {
            SET_PD_RX0_CBL_TERMINATION_TYPE(_PD_CBL_BOTH_END_ACTIVE);
        }

        // Bit[10:9] Max Vbus Voltage
        if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == 0x00)
        {
            // Cable Max Voltage = 20V = 200 * 100mV
            SET_PD_RX0_CBL_MAX_VOL(200);
        }
        else if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == _BIT1)
        {
            SET_PD_RX0_CBL_MAX_VOL(300);
        }
        else if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == _BIT2)
        {
            SET_PD_RX0_CBL_MAX_VOL(400);
        }
        else if((g_pucDataObj_EXINT[18] & (_BIT2 | _BIT1)) == (_BIT2 | _BIT1))
        {
            SET_PD_RX0_CBL_MAX_VOL(500);
        }

        // Bit[8] SBU Supported :Y/N
        if((g_pucDataObj_EXINT[18] & _BIT0) == 0x00)
        {
            SET_PD_RX0_CBL_SBU_SUPPORT();
        }

        // If Bit[8] == 0, set Bit[7]: SBU Type, otherwise ignore Bit[7]
        if(GET_PD_RX0_CBL_SBU_SUPPORT() == _TRUE)
        {
            if((g_pucDataObj_EXINT[19] & _BIT7) == 0x00)
            {
                SET_PD_RX0_CBL_SBU_TYPE(_PD_CBL_SBU_PASSIVE);
            }
            else if((g_pucDataObj_EXINT[19] & _BIT7) == _BIT7)
            {
                SET_PD_RX0_CBL_SBU_TYPE(_PD_CBL_SBU_ACTIVE);
            }
        }

        // Bit[4] Vbus Through Cable: Y/N.
        if((g_pucDataObj_EXINT[19] & _BIT4) == _BIT4)
        {
            SET_PD_RX0_CBL_VBUS_THROUGH();
        }

        // Bit[3] SOP'' Controller Present : Y/N
        if((g_pucDataObj_EXINT[19] & _BIT3) == _BIT3)
        {
            SET_PD_RX0_CBL_SOP_PP_SUPPORT();
        }

        // Bit[2:0] Cable USB Highest Speed
        if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_2_ONLY);
        }
        else if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3_GEN1);
        }
        else if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3OR4_GEN2);
        }
        else if((g_pucDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            SET_PD_RX0_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_4_GEN3);
        }

        // Active Cable VDO2
        // Bit[11] U3 to U0 Transition Mode
        if((g_pucDataObj_EXINT[22] & _BIT3) == 0x00)
        {
            SET_PD_RX0_CBL_U3_TO_U0_TRANSITION_MODE(_PD_CBL_U3_TO_U0_DIRECT);
        }
        else if((g_pucDataObj_EXINT[22] & _BIT3) == _BIT3)
        {
            SET_PD_RX0_CBL_U3_TO_U0_TRANSITION_MODE(_PD_CBL_U3_TO_U0_THROUGH_U3S);
        }

        // Bit[9] Active Element
        if((g_pucDataObj_EXINT[22] & _BIT1) == 0x00)
        {
            SET_PD_RX0_CBL_ACTIVE_ELEMENT(_PD_CBL_ACTIVE_REDRIVER);
        }
        else if((g_pucDataObj_EXINT[22] & _BIT1) == _BIT1)
        {
            SET_PD_RX0_CBL_ACTIVE_ELEMENT(_PD_CBL_ACTIVE_RETIMER);
        }

        // Bit[8] USB4 Support: Y/N
        if((g_pucDataObj_EXINT[22] & _BIT0) == _BIT0)
        {
            SET_PD_RX0_CBL_USB_4_SUPPORT();
        }

        // Bit[4] USB3.2 Support: Y/N
        if((g_pucDataObj_EXINT[23] & _BIT4) == _BIT4)
        {
            SET_PD_RX0_CBL_USB_3_2_SUPPORT();
        }

        // Bit[3] USB Lanes Supported: One Lane / Two Lanes
        if((g_pucDataObj_EXINT[23] & _BIT3) == 0x00)
        {
            SET_PD_RX0_CBL_LANES_SUPPORT(_PD_CBL_ONE_LANE);
        }
        else if((g_pucDataObj_EXINT[23] & _BIT3) == _BIT3)
        {
            SET_PD_RX0_CBL_LANES_SUPPORT(_PD_CBL_TWO_LANES);
        }

        // If VDO1 Bit[4] == 1, set Bit[6:5]: CBL max Vbus current, otherwise ignore Bit[6:5]
        if(GET_PD_RX0_CBL_VBUS_THROUGH() == _TRUE)
        {
            if((g_pucDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT5)
            {
                // Cable Max Vbus Current = 3.0A = 300 * 10mA
                SET_PD_RX0_CBL_MAX_CUR(300);
            }
            else if((g_pucDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT6)
            {
                SET_PD_RX0_CBL_MAX_CUR(500);
            }
            else if((g_pucDataObj_EXINT[19] & (_BIT6 | _BIT5)) == 0x00)
            {
                // PD 3.0 Spec P150: 500mA USB2, 900mA USB3.2 x1, 1.5A USB3.2 x2.
                if(GET_PD_RX0_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_2_ONLY)
                {
                    SET_PD_RX0_CBL_MAX_CUR(50);
                }
                else if((GET_PD_RX0_CBL_USB_3_2_SUPPORT() == _TRUE) && (GET_PD_RX0_CBL_LANES_SUPPORT() == _PD_CBL_ONE_LANE))
                {
                    SET_PD_RX0_CBL_MAX_CUR(90);
                }
                else if((GET_PD_RX0_CBL_USB_3_2_SUPPORT() == _TRUE) && (GET_PD_RX0_CBL_LANES_SUPPORT() == _PD_CBL_TWO_LANES))
                {
                    SET_PD_RX0_CBL_MAX_CUR(150);
                }
            }
        }
    }
    else if(GET_PD_RX0_CBL_PRODUCT_TYPE() == _PD_VCONN_POWERED_USB_DEVICE)
    {
        // VPD VDO
        // Bit[16:15] Max Vbus Voltage
        if(((g_pucDataObj_EXINT[17] & _BIT0) == 0x00) && ((g_pucDataObj_EXINT[18] & _BIT7) == 0x00))
        {
            // Max Voltage = 20V = 200 * 100mV
            SET_PD_RX0_CBL_MAX_VOL(200);
        }
        else if(((g_pucDataObj_EXINT[17] & _BIT0) == 0x00) && ((g_pucDataObj_EXINT[18] & _BIT7) == _BIT7))
        {
            SET_PD_RX0_CBL_MAX_VOL(300);
        }
        else if(((g_pucDataObj_EXINT[17] & _BIT0) == _BIT0) && ((g_pucDataObj_EXINT[18] & _BIT7) == 0x00))
        {
            SET_PD_RX0_CBL_MAX_VOL(400);
        }
        else if(((g_pucDataObj_EXINT[17] & _BIT0) == _BIT0) && ((g_pucDataObj_EXINT[18] & _BIT7) == _BIT7))
        {
            SET_PD_RX0_CBL_MAX_VOL(500);
        }

        // Bit[0] Charge Through Support
        if((g_pucDataObj_EXINT[19] & _BIT0) == _BIT0)
        {
            SET_PD_RX0_CBL_CHARGE_THROUGH_SUPPORT();
        }

        // Bit[14] Charge Through Current Support; if Bit[0] = 1, Set Max Current Macro
        if(GET_PD_RX0_CBL_CHARGE_THROUGH_SUPPORT() == _TRUE)
        {
            if((g_pucDataObj_EXINT[18] & _BIT6) == 0x00)
            {
                // Charge Through Current = 3.0A = 300 * 10mA
                SET_PD_RX0_CBL_MAX_CUR(300);
            }
            else if((g_pucDataObj_EXINT[18] & _BIT6) == _BIT6)
            {
                SET_PD_RX0_CBL_MAX_CUR(500);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Check if Present Power Contract is still Valid
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCRx0PdCheckPowerContractValid_EXINT0(void) using 1
{
    // Call ScalerTypeCPower Functions to Get Currently Avaliable Power
    // If Power Contract Power is <= Avaliable Power => TRUE; ELSE => FALSE
    return _TRUE;
}

//--------------------------------------------------
// Description  : Check if Power Contract Need to be Rebuild
// Input Value  : None
// Output Value : _PD_REBUILD_REQUIRED / _PD_REBUILD_NOT_REQUIRED
//--------------------------------------------------
EnumTypeCPDRebuildPowerContract ScalerTypeCRx0PdCheckRebuildPowerContract_EXINT0(void) using 1
{
    EnumTypeCPDRebuildPowerContract enumRebuildCheckResult = _PD_REBUILD_NOT_REQUIRED;

    if(GET_PD_RX0_CBL_MAX_CUR() == 500)
    {
        for(pData_EXINT[0] = 0; pData_EXINT[0] < GET_PD_RX0_SRC_PDO_CNT(); pData_EXINT[0] ++)
        {
            if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[0]) == _PD_FIX_SUPPLY_PDO)
            {
                // When Get CBL Max Current = 5A , SRC CAP CUR > 3A, Rebuild is Required
                if(GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[0]) > 300)
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            else if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
            {
                if(((GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[0])) * 5) > 300)
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#endif
        }
    }
    else if(GET_PD_RX0_CBL_MAX_CUR() < 300)
    {
        for(pData_EXINT[0] = 0; pData_EXINT[0] < GET_PD_RX0_SRC_PDO_CNT(); pData_EXINT[0] ++)
        {
            if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[0]) == _PD_FIX_SUPPLY_PDO)
            {
                // When Get CBL Max Current = USB Type-C Default Current(500mA/900mA/1.5A), SRC CAP CUR > CBL MAX CUR, Rebuild is Required
                if(GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[0]) > GET_PD_RX0_CBL_MAX_CUR())
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            else if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
            {
                if(((GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[0])) * 5) > GET_PD_RX0_CBL_MAX_CUR())
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#endif
        }
    }

    return enumRebuildCheckResult;
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Search Through All SVIDs to Check if DP_SID Exist
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCRx0PdSearchSvid_EXINT0(void) using 1
{
    BYTE ucSearchResult = _FALSE;

    CLR_PD_RX0_DP_SVID_SEARCH_FINISH();

    for(pData_EXINT[0] = 0; pData_EXINT[0] < (GET_PD_RX0_RCV_NOD_CNT() * 4); pData_EXINT[0] = pData_EXINT[0] + 2)
    {
        if((g_pucDataObj_EXINT[pData_EXINT[0]] == 0xFF) && (g_pucDataObj_EXINT[pData_EXINT[0] + 1] == 0x01))
        {   // if SVID = DP_SID (0xFF01), Set Result to TRUE
            ucSearchResult = _TRUE;
        }
        else if((g_pucDataObj_EXINT[pData_EXINT[0]] == 0x00) && (g_pucDataObj_EXINT[pData_EXINT[0] + 1] == 0x00))
        {   // if SVID = 0x00, Search Finish
            SET_PD_RX0_DP_SVID_SEARCH_FINISH();
        }
    }

    return ucSearchResult;
}

//--------------------------------------------------
// Description  : Search All Modes to Get DP Port Capability (DP_Tx) and Pin Assignment ( C / D / E )
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSearchMode_EXINT0(void) using 1
{
    CLR_PD_RX0_DP_OBJ_POS();

    for(pData_EXINT[0] = 4; pData_EXINT[0] < (GET_PD_RX0_RCV_NOD_CNT() * 4); pData_EXINT[0] = pData_EXINT[0] + 4)
    {
        // if(Support DP Tx), Get Supported Pin Assignments
        if((g_pucDataObj_EXINT[pData_EXINT[0] + 3] & _BIT1) == _BIT1)
        {
            // If Connect to Receptacle, Refer to UFP Pin Assignment
            if((g_pucDataObj_EXINT[pData_EXINT[0] + 3] & _BIT6) == _BIT6)
            {
                SET_PD_RX0_PARTNER_PIN_ASSIGNMENT(g_pucDataObj_EXINT[pData_EXINT[0] + 2]);
            }
            else
            {
                // If Connect to Receptacle, Refer to DFP Pin Assignment
                SET_PD_RX0_PARTNER_PIN_ASSIGNMENT(g_pucDataObj_EXINT[pData_EXINT[0] + 1]);
            }

            // Check If There is Any Pin Assignment Avaliable (Partner & Our Cap Both Support)
            if((GET_PD_RX0_PARTNER_PIN_ASSIGNMENT() & GET_PD_RX0_PIN_ASSIGNMENT_CAP()) != 0x00)
            {
                SET_PD_RX0_DP_OBJ_POS(pData_EXINT[0] / 4);
            }
        }
        // Else, Keep Target Object Position = 0x00
    }
}

//--------------------------------------------------
// Description  : DFP Judge Target Pin Assignment By Partner Capability
// Input Value  : None
// Output Value : Target Pin Assignment to be Configured
//--------------------------------------------------
BYTE ScalerTypeCRx0PdDfpJudgePinAssignment_EXINT0(void)  using 1
{
    BYTE ucPinAssignment = (GET_PD_RX0_PARTNER_PIN_ASSIGNMENT() & (BYTE)GET_PD_RX0_PIN_ASSIGNMENT_CAP());
    SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);

    if((GET_PD_RX0_MULTI_FUNCTION() == _TRUE) && ((ucPinAssignment & _BIT3) == _BIT3))
    {
        // If "Multi-Function = 1" and "Pin Assignment D Support"
        SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_D);
    }
    else if((ucPinAssignment & _BIT2) == _BIT2)
    {
        // If "Pin Assignment C Support"
        SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_C);
    }
    else if((ucPinAssignment & _BIT3) == _BIT3)
    {
        // If "Pin Assignment D Support"
        SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_D);
    }
    else if((ucPinAssignment & _BIT4) == _BIT4)
    {
        // If "Pin Assignment E Support"
        SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_E);
    }

    if(GET_PD_RX0_PIN_ASSIGNMENT() != _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check if to Send DP Config
// Input Value  : None
// Output Value : _PD_CONFIG_REQUIRED (Send DP Config)/ _PD_CONFIG_NOT_REQUIRED (Maintain Current Config or Exit Mode)
//--------------------------------------------------
EnumDpStatusCheckResult ScalerTypeCRx0PdCheckDpStatus_EXINT0(void) using 1
{
    if((GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && (GET_PD_RX0_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_E))
    {
        // For C to DP Cable, DFP Shall not Send DP Config (Set Config. to USB) and Exit Mode
        CLR_PD_RX0_DP_ALT_MODE_EXIT_REQ();

        return _PD_CONFIG_NOT_REQUIRED;
    }

    SET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG(_PD_DP_CONFIG);

    // Display Port Status : [6] Exit DP Request / [5] USB Config Request / [4] Multi-Func = X
    // [3] Adaptor Func = 1 / [2] Power Low = 0 / [1:0] Connected = 01 (DP_TX)
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    if((g_pucDataObj_EXINT[7] & (_BIT0)) != _BIT0)
    {
        SET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);
    }
#endif

    // DFP Check Exit Mode Bit
    if((g_pucDataObj_EXINT[7] & _BIT6) == _BIT6)
    {
        SET_PD_RX0_DP_ALT_MODE_EXIT_REQ();
        SET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);
    }

    // DFP Check USB Configuration Request Bit
    if((g_pucDataObj_EXINT[7] & _BIT5) == _BIT5)
    {
        SET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);
    }

    // DFP Update UFP Multi-Funtion Bit
    if((g_pucDataObj_EXINT[7] & _BIT4) == _BIT4)
    {
        SET_PD_RX0_MULTI_FUNCTION();
    }
    else
    {
        CLR_PD_RX0_MULTI_FUNCTION();
    }

    if(GET_PD_RX0_DP_ALT_MODE_CONFIG() == GET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG())
    {
        return _PD_CONFIG_NOT_REQUIRED;
    }
    else
    {
        return _PD_CONFIG_REQUIRED;
    }
}

//--------------------------------------------------
// Description  : Check if DP_Config is Valid @ Interrupt
// Input Value  : None
// Output Value : _TRUE(REQ as DP_RX & Pin Assignment C / D / E || Config USB & Pin Assignment NONE)/_FALSE
//--------------------------------------------------
BYTE ScalerTypeCRx0PdCheckDpConfig_EXINT0(void) using 1
{
    BYTE ucCheckResult = _FALSE;

    // Check if Request DP_RX (VDO1[1:0] = b'10)
    if((g_pucDataObj_EXINT[7] & (_BIT1 | _BIT0)) == _BIT1)
    {
        switch(g_pucDataObj_EXINT[6])
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:
            case _TYPE_C_PIN_ASSIGNMENT_D:
            case _TYPE_C_PIN_ASSIGNMENT_E:

                SET_PD_RX0_PIN_ASSIGNMENT(g_pucDataObj_EXINT[6]);
                ucCheckResult = _TRUE;

                break;

            default:

                ucCheckResult = _FALSE;

                break;
        }
    }
    // Check if Request USB Configuration (VDO1[1:0] = b'00)
    else if((g_pucDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
    {
        SET_PD_RX0_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
        ucCheckResult = _TRUE;
    }
    else
    {
        ucCheckResult = _FALSE;
    }
    return ucCheckResult;
}
#endif  // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Check Lenovo Get Status @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdCheckLenovoStatus_EXINT0(void) using 1
{
    SET_PD_RX0_LENOVO_SYS_ACKNOWLEDGE(g_pucDataObj_EXINT[5]);
    SET_PD_RX0_LENOVO_SYS_EVENT(g_pucDataObj_EXINT[6]);
}

//--------------------------------------------------
// Description  : Check Lenovo Device ID @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdCheckLenovoDeviceId_EXINT0(void) using 1
{
    SET_PD_RX0_LENOVO_DEVICE_TYPE(g_pucDataObj_EXINT[7]);
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Check Acer Get Status @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdCheckAcerSysStatus_EXINT0(void) using 1
{
    SET_PD_RX0_ACER_SYS_EVENT(_TYPE_C_ACER_SYS_EVENT_STATUS_REQ);

    // User VDM Data = Rcv Data Object - VDM Header
    SET_PD_RX0_ACER_SYS_VDM_CNT(GET_PD_RX0_RCV_NOD_CNT() - 1);

    // Get Acer VDM Data Contents
    for(pData_EXINT[0] = 0; pData_EXINT[0] < (GET_PD_RX0_ACER_SYS_VDM_CNT() * 4); pData_EXINT[0]++)
    {
        SET_PD_RX0_ACER_SYS_VDM_DATA(pData_EXINT[0], g_pucDataObj_EXINT[pData_EXINT[0] + 4]);
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Set Hp Own I2C Address and AM Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetHpOwnAddr_EXINT0(void) using 1
{
    SET_PD_RX0_HP_I2C_ADDR(((g_pucDataObj_EXINT[4] & (_BIT2 | _BIT1 | _BIT0)) << 4) | ((g_pucDataObj_EXINT[5] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
    SET_PD_RX0_HP_OWN_AM_ADDR_H(g_pucDataObj_EXINT[5] & (_BIT1 | _BIT0));
    SET_PD_RX0_HP_OWN_AM_ADDR_M(g_pucDataObj_EXINT[6]);
    SET_PD_RX0_HP_OWN_AM_ADDR_L(g_pucDataObj_EXINT[7]);
}

//--------------------------------------------------
// Description  : Check if Hp AM Address is Valid @ Interrupt
// Input Value  : None
// Output Value : _TRUE(Ignore AM Address || AM Address is Valid)/_FALSE
//--------------------------------------------------
BYTE ScalerTypeCRx0PdCheckHpVdmValid_EXINT0(void) using 1
{
    BYTE ucCheckResult = _FALSE;

    // Rev. HP AM Address
    BYTE ucHpRevAmAddr_H = (g_pucDataObj_EXINT[5] & (_BIT1 | _BIT0));
    BYTE ucHpRevAmAddr_M = (g_pucDataObj_EXINT[6]);
    BYTE ucHpRevAmAddr_L = (g_pucDataObj_EXINT[7]);

    switch((EnumTypeCVdmHpCmd)GET_PD_RX0_RCV_VDM_CMD())
    {
        // ------------ AM Address Do not Exist ------------
        // AM Address do not Exist, so Return True Directly
        case _PD_VDM_HP_CMD_DISCOVER_MODE_REQ:
        case _PD_VDM_HP_CMD_ENTER_MODE_REQ:
        case _PD_VDM_HP_CMD_EXIT_MODE_REQ:
        case _PD_VDM_HP_CMD_SET_CONFIG_REQ:

            ucCheckResult = _TRUE;

            break;

        // --------------- AM Address Exist ---------------
        // If AM Address Exist, Need to Check Address is Valid or not
        case _PD_VDM_HP_CMD_GET_CONFIG_REQ:
        case _PD_VDM_HP_CMD_SET_DATA_REQ:
        case _PD_VDM_HP_CMD_SET_VWIRE_REQ:

            if (((ucHpRevAmAddr_H == 0x03) && (ucHpRevAmAddr_M == 0xFF) && (ucHpRevAmAddr_L == 0xFF)) || ((GET_PD_RX0_HP_OWN_AM_ADDR_H() == ucHpRevAmAddr_H) && (GET_PD_RX0_HP_OWN_AM_ADDR_M() == ucHpRevAmAddr_M) && (GET_PD_RX0_HP_OWN_AM_ADDR_L() == ucHpRevAmAddr_L)))
            {
                if(((EnumTypeCVdmHpCmd)GET_PD_RX0_RCV_VDM_CMD()) == _PD_VDM_HP_CMD_SET_VWIRE_REQ)
                {
                    // For _PD_VDM_HP_CMD_SET_VWIRE_REQ : Set Vwire Operation
                    SET_PD_RX0_HP_VWIRE_OP(g_pucDataObj_EXINT[11] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
                ucCheckResult = _TRUE;
            }

            break;

        case _PD_VDM_HP_CMD_GET_VWIRE_REQ:
        case _PD_VDM_HP_CMD_GET_DATA_REQ:

            // Get_viwre can't be Broadcast AM Address
            if ((GET_PD_RX0_HP_OWN_AM_ADDR_H() == ucHpRevAmAddr_H) && (GET_PD_RX0_HP_OWN_AM_ADDR_M() == ucHpRevAmAddr_M) && (GET_PD_RX0_HP_OWN_AM_ADDR_L() == ucHpRevAmAddr_L))
            {
                ucCheckResult = _TRUE;
            }

            break;

        case _PD_VDM_HP_CMD_CMD_REQ:
        default:

            break;
    }

    return ucCheckResult;
}

//--------------------------------------------------
// Description  : Get Hp System Event when Rcv. Hp Get Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdGetHpSysStatus_EXINT0(EnumTypeCHpSysEvent enumSysEvent) using 1
{
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    stHpSysEvent.enumEvent = enumSysEvent;

    // User VDM Data = Rcv Data Object - VDM Header - HP Sub Header
    stHpSysEvent.b3VdmCnt = GET_PD_RX0_RCV_NOD_CNT() - 2;

    // Get Hp VDM Data Contents
    for(pData_EXINT[0] = 0; pData_EXINT[0] < (stHpSysEvent.b3VdmCnt * 4); pData_EXINT[0]++)
    {
        stHpSysEvent.pucVdmData[pData_EXINT[0]] = g_pucDataObj_EXINT[pData_EXINT[0] + 8];
    }

    // Check if SysEvent Queue is full or not
    if(GET_PD_RX0_HP_SYS_EVENT_QUEUE_CNT() < _TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE)
    {
        SET_PD_RX0_HP_SYS_EVENT_QUEUE(GET_PD_RX0_HP_SYS_EVENT_QUEUE_TAIL(), stHpSysEvent);
        ADD_PD_RX0_HP_SYS_EVENT_QUEUE_TAIL();
        ADD_PD_RX0_HP_SYS_EVENT_QUEUE_CNT();
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Get Dell System Event Information
// Input Value  : enumSysEvent : _TYPE_C_DELL_SYS_EVENT_NONE/ _TYPE_C_DELL_SYS_EVENT_0X12/ _TYPE_C_DELL_SYS_EVENT_ATTEN_SUCCESS/ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdGetDellSysInfo_EXINT0(void) using 1
{
    // User VDM Data = Rcv Data Object - VDM Header
    SET_PD_RX0_DELL_SYS_VDM_CNT(GET_PD_RX0_RCV_NOD_CNT() - 1);

    // Get Dell VDM Data Contents
    for(pData_EXINT[0] = 0; pData_EXINT[0] < (GET_PD_RX0_DELL_SYS_VDM_CNT() * 4); pData_EXINT[0]++)
    {
        SET_PD_RX0_DELL_SYS_VDM_DATA(pData_EXINT[0], g_pucDataObj_EXINT[pData_EXINT[0] + 4]);
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get DP Alt. Mode Ready Status
// Input Value  : None
// Output Value : DP Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeCRx0PdGetAltModeReady(void)
{
#if(_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && (GET_PD_RX0_DP_ALT_MODE_WAIT_CONFIG() == _FALSE) && ((GET_TYPE_C_RX0_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_PD_RX0_PARTNER_DRP() == _FALSE) || (GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) || (GET_PD_RX0_UNCONSTRAIN_POWER() == _FALSE) || (GET_PD_RX0_PRS_REJECT() == _TRUE)))
#else
    if((GET_PD_RX0_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && (GET_PD_RX0_DP_ALT_MODE_WAIT_CONFIG() == _FALSE))
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get DP Alt. Mode Pin Assignment
// Input Value  : None
// Output Value : Enumeration of Pin Assignment C/D/E
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeCRx0PdGetPinAssignment(void)
{
    return GET_PD_RX0_PIN_ASSIGNMENT();
}

//--------------------------------------------------
// Description  : Get DP Alt. Mode Pin Assignment
// Input Value  : None
// Output Value : Enumeration of Pin Assignment C/D/E
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeCRx0PdGetPinAssignment_EXINT0(void) using 1
{
    return GET_PD_RX0_PIN_ASSIGNMENT();
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Alt. Mode Pin Assignment
// Input Value  : None
// Output Value : Enumeration of Pin Assignment C/D/E
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeCRx0PdGetPinAssignment_WDINT(void) using 3
{
    return GET_PD_RX0_PIN_ASSIGNMENT();
}
#endif

//--------------------------------------------------
// Description  : Set Pin Assignment Capabiliy
// Input Value  : None
// Output Value : Enumeration of Pin Assignment C/D/E
//--------------------------------------------------
void ScalerTypeCRx0PdSetPinAssignmentCapability(EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    SET_PD_RX0_PIN_ASSIGNMENT_CAP(enumPinAssignmentCap);
}

//--------------------------------------------------
// Description  : Set Multi Function Bit
// Input Value  : None
// Output Value : Enumeration of Multi Function
//--------------------------------------------------
void ScalerTypeCRx0PdSetMultiFunctionBit(EnumTypeCMultiFuncStatus enumMultiFunc)
{
    if(enumMultiFunc == _TYPE_C_MULTI_FUNC_PREFER)
    {
        SET_PD_RX0_MULTI_FUNCTION();
    }
    else
    {
        CLR_PD_RX0_MULTI_FUNCTION();
    }
}

//--------------------------------------------------
// Description  : Set Wait DP Config Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdWaitDpConfig(void)
{
    // Set Wait DP Config Flag to trigger Alt Mode Not Ready, Clr when rcv DP Config
    SET_PD_RX0_DP_ALT_MODE_WAIT_CONFIG();
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue
// Input Value  : enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., Hpd Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdPushHpd(EnumPDHpdType enumHpdType, WORD usHpdSpaceTime)
{
    BYTE ucIndex = 0;

    // Push Queue Only Vlid When Alt Mode is Ready
    if(GET_PD_RX0_DP_ALT_MODE_ENTER() != _TRUE)
    {
        return;
    }

    switch(enumHpdType)
    {
        case _PD_HPD_LOW:

            for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
            {
                SET_PD_RX0_HPD_QUEUE(_PD_HPD_NONE);
                SET_PD_RX0_HPD_SPACE_TIME(0);
                ADD_PD_RX0_HPD_WPTR();
            }

            CLR_PD_RX0_HPD_WPTR();
            CLR_PD_RX0_HPD_RPTR();
            CLR_PD_RX0_HPD_CNT();

            SET_PD_RX0_HPD_QUEUE(_PD_HPD_LOW);
            SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

            ADD_PD_RX0_HPD_WPTR();
            ADD_PD_RX0_HPD_CNT();

            break;

        case _PD_HPD_HIGH:

            if((GET_PD_RX0_HPD_CNT() == 0) || (GET_PD_RX0_HPD_QUEUE((GET_PD_RX0_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_HIGH))
            {
                SET_PD_RX0_HPD_QUEUE(_PD_HPD_HIGH);
                SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_PD_RX0_HPD_WPTR();
                ADD_PD_RX0_HPD_CNT();
            }

            break;

        case _PD_HPD_IRQ:

            // Make sure HPD_IRQ has a minumun spacing time of 10ms (DP Alt Mode 5.2.2)
            usHpdSpaceTime = (usHpdSpaceTime < _ATTENTION_SPACING_TIMER) ? _ATTENTION_SPACING_TIMER : usHpdSpaceTime;

            if(GET_PD_RX0_HPD_CNT() <= 1)
            {
                SET_PD_RX0_HPD_QUEUE(_PD_HPD_IRQ);
                SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_PD_RX0_HPD_WPTR();
                ADD_PD_RX0_HPD_CNT();
            }
            else
            {
                // If Last 2 HPDs are Not Both HPD_IRQs, Push New HPD_IRQ
                if((GET_PD_RX0_HPD_QUEUE((GET_PD_RX0_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ) ||
                   (GET_PD_RX0_HPD_QUEUE((GET_PD_RX0_HPD_WPTR() + _HPD_QUEUE_DEPTH - 2) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ))
                {
                    SET_PD_RX0_HPD_QUEUE(_PD_HPD_IRQ);
                    SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

                    ADD_PD_RX0_HPD_WPTR();
                    ADD_PD_RX0_HPD_CNT();
                }
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue @ Interrupt
// Input Value  : enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., Hpd Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdPushHpd_EXINT0(EnumPDHpdType enumHpdType, WORD usHpdSpaceTime) using 1
{
    BYTE ucIndex = 0;

    // Push Queue Only Vlid When Alt Mode is Ready
    if(GET_PD_RX0_DP_ALT_MODE_ENTER() != _TRUE)
    {
        return;
    }

    switch(enumHpdType)
    {
        case _PD_HPD_LOW:

            for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
            {
                SET_PD_RX0_HPD_QUEUE(_PD_HPD_NONE);
                SET_PD_RX0_HPD_SPACE_TIME(0);
                ADD_PD_RX0_HPD_WPTR();
            }

            CLR_PD_RX0_HPD_WPTR();
            CLR_PD_RX0_HPD_RPTR();
            CLR_PD_RX0_HPD_CNT();

            SET_PD_RX0_HPD_QUEUE(_PD_HPD_LOW);
            SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

            ADD_PD_RX0_HPD_WPTR();
            ADD_PD_RX0_HPD_CNT();

            break;

        case _PD_HPD_HIGH:

            if((GET_PD_RX0_HPD_CNT() == 0) || (GET_PD_RX0_HPD_QUEUE((GET_PD_RX0_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_HIGH))
            {
                SET_PD_RX0_HPD_QUEUE(_PD_HPD_HIGH);
                SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_PD_RX0_HPD_WPTR();
                ADD_PD_RX0_HPD_CNT();
            }

            break;

        case _PD_HPD_IRQ:

            // Make sure HPD_IRQ has a minumun spacing time of 10ms (DP Alt Mode 5.2.2)
            usHpdSpaceTime = (usHpdSpaceTime < _ATTENTION_SPACING_TIMER) ? _ATTENTION_SPACING_TIMER : usHpdSpaceTime;

            if(GET_PD_RX0_HPD_CNT() <= 1)
            {
                SET_PD_RX0_HPD_QUEUE(_PD_HPD_IRQ);
                SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_PD_RX0_HPD_WPTR();
                ADD_PD_RX0_HPD_CNT();
            }
            else
            {
                // If Last 2 HPDs are Not Both HPD_IRQs, Push New HPD_IRQ
                if((GET_PD_RX0_HPD_QUEUE((GET_PD_RX0_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ) ||
                   (GET_PD_RX0_HPD_QUEUE((GET_PD_RX0_HPD_WPTR() + _HPD_QUEUE_DEPTH - 2) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ))
                {
                    SET_PD_RX0_HPD_QUEUE(_PD_HPD_IRQ);
                    SET_PD_RX0_HPD_SPACE_TIME(usHpdSpaceTime);

                    ADD_PD_RX0_HPD_WPTR();
                    ADD_PD_RX0_HPD_CNT();
                }
            }

            break;

        default:

            break;
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Pop HPD from HPD Queue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdPopHpd(void)
{
    if(GET_PD_RX0_HPD_CNT() > 0)
    {
        // Update HPD Status For DP Usage
        if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_LOW)
        {
            ScalerDpRx0HpdToggleAuxPhyResetProc(_LOW);
            SET_PD_RX0_HPD_STATUS(_LOW);
        }
        else if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_HIGH)
        {
            ScalerDpRx0HpdToggleAuxPhyResetProc(_HIGH);
            SET_PD_RX0_HPD_STATUS(_HIGH);
        }

        CLR_PD_RX0_HPD_QUEUE();
        CLR_PD_RX0_HPD_SPACE_TIME();

        // Adjust HPD Queue
        ADD_PD_RX0_HPD_RPTR();
        SUB_PD_RX0_HPD_CNT();
    }
}

//--------------------------------------------------
// Description  : Pop HPD from HPD Queue @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdPopHpd_EXINT0(void) using 1
{
    if(GET_PD_RX0_HPD_CNT() > 0)
    {
        // Update HPD Status For DP Usage
        if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_LOW)
        {
            ScalerDpRx0HpdToggleAuxPhyResetProc_EXINT0(_LOW);
            SET_PD_RX0_HPD_STATUS(_LOW);
        }
        else if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_HIGH)
        {
            ScalerDpRx0HpdToggleAuxPhyResetProc_EXINT0(_HIGH);
            SET_PD_RX0_HPD_STATUS(_HIGH);
        }

        CLR_PD_RX0_HPD_QUEUE();
        CLR_PD_RX0_HPD_SPACE_TIME();

        // Adjust HPD Queue
        ADD_PD_RX0_HPD_RPTR();
        SUB_PD_RX0_HPD_CNT();
    }
}
#endif  // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Clear HPD Queue When PD Reset TO Prevent DP Urgent Event DeadLock
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdClrHpd(void)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
    {
        SET_PD_RX0_HPD_QUEUE(_PD_HPD_NONE);
        SET_PD_RX0_HPD_SPACE_TIME(0);
        ADD_PD_RX0_HPD_WPTR();
    }

    ScalerDpRx0HpdToggleAuxPhyResetProc(_LOW);
    SET_PD_RX0_HPD_STATUS(_LOW);
    CLR_PD_RX0_HPD_WPTR();
    CLR_PD_RX0_HPD_RPTR();
    CLR_PD_RX0_HPD_CNT();
}

//--------------------------------------------------
// Description  : Send Power Delivery Message
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT / _CABLE_RESET_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmdType : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendMsg(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd)
{
    // 1. Clear Flags
    CLR_PD_RX0_INT_OVERWRITE();
    CLR_PD_RX0_TRANSMIT_RESULT();

    // 2. Check Valid Msg
    // if(ScalerTypeCRx0PdSendMsgCheck(enumPacketType, enumPdCmd) == _FALSE)

    // 3. Construct Msg.
    ScalerTypeCRx0PdConstructMsg(enumPacketType, enumPdCmd, enumVdmCmd);

    // 4. Only Send Msg. When Tx FIFO Has Not Been Overwritten by INT during Msg. Construct Flow
    if(GET_PD_RX0_INT_OVERWRITE() == _TRUE)
    {
        // Function Has Been Interrupted Before Sending, Set "Send Fail"
        SET_PD_RX0_TRANSMIT_RESULT(_PD_SENT_DISCARDED);
    }
    else
    {
        // Start Disable Rcv Msg.
        ScalerTypeCRx0PdRxIntControl(_DISABLE);

        // [0x65DC] Clear IRQs, Main Loop Do Not Enable [0x65DD], Use Polling
        ScalerSetBit(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // [0x65DB] Clear PHY Error IRQs
        ScalerSetBit(P65_DB_TX_PHY_TRANS_INT, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));

        // [0x65DA] Start Transmit ([1] = 1, Wait For GoodCRC Response After Transmission)
        ScalerSetBit(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

        // 5. For Main Loop : Polling Sending Result (timeout = 1.5*4(msg) + 1.1*3 (CrcTimer) = 10ms)
        if(ScalerTimerPollingFlagProc(_PD_SEND_MSG_TIMEOUT, P65_DC_TX_PD_MSG_INT, _BIT5, _BIT5) == _TRUE)
        {
            // tx_prl_trans_done_irq = 1
            SET_PD_RX0_TRANSMIT_RESULT(ScalerGetByte(P65_DC_TX_PD_MSG_INT) & (0x1F));
        }
        else
        {   // !!! WARNING : NO SENDING RESULT !!!
            SET_PD_RX0_TRANSMIT_RESULT(_PD_SENT_RETRY_FAIL);
        }

        // [0x65E5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
    }
}

//--------------------------------------------------
// Description  : Send Power Delivery Message Not Include Soft Reset and Hard Reset
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmdType : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructMsg(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd)
{
    BYTE ucExtendedBit = 0;
    BYTE ucDataObjectCnt = 0;
    BYTE ucMsgHeader = 0;

    // 1. [0x65E9-EA] Set Up Number of Data Objects(Data Blocks) if Needed
    switch(enumPdCmd)
    {
        // Control Message Has No Data Object
        case _PD_CMD_RSV:
        case _PD_CMD_GOODCRC:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PING:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_GET_SRC_CAP:
        case _PD_CMD_GET_SNK_CAP:
        case _PD_CMD_DR_SWAP:
        case _PD_CMD_PR_SWAP:
        case _PD_CMD_VCONN_SWAP:
        case _PD_CMD_WAIT:
        case _PD_CMD_SOFT_RESET:
#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_NOT_SUPPORT:
#endif
            ucDataObjectCnt = 0;
            break;

        // Data Message Has Different Num of Data Objects According to Different Message
        case _PD_CMD_SRC_CAP:

            ucDataObjectCnt = GET_PD_RX0_SRC_PDO_CNT();

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0)
#endif
            {
                for(pData[0] = GET_PD_RX0_SRC_PDO_CNT() - 1; pData[0] > 0; pData[0]--)
                {
                    if(GET_PD_RX0_SRC_PDO_TYPE(pData[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ucDataObjectCnt --;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;

        case _PD_CMD_REQUEST:

            ucDataObjectCnt = 1;
            break;

        case _PD_CMD_BIST:

            // Data Message For Tester Only
            ucDataObjectCnt = 1;
            break;

        case _PD_CMD_SNK_CAP:

            ucDataObjectCnt = GET_PD_RX0_SNK_PDO_CNT();
            break;

        case _PD_CMD_VDM:

            switch(enumVdmCmd)
            {
                case _PD_VDM_CMD_DISCOVER_ID_REQ:
                case _PD_VDM_CMD_DISCOVER_SVID_REQ:
                case _PD_VDM_CMD_DISCOVER_MODE_REQ:
                case _PD_VDM_CMD_ENTER_MODE_REQ:
                case _PD_VDM_CMD_EXIT_MODE_REQ:
                case _PD_VDM_CMD_15:    // Acer Attention (0x15)

                    ucDataObjectCnt = 1;
                    break;

                case _PD_VDM_CMD_ATTENTION_REQ:

                    if(GET_PD_RX0_ATTN_TYPE() == _PD_DP_ATTENTION)
                    {
                        ucDataObjectCnt = 2;
                    }
                    else if(GET_PD_RX0_ATTN_TYPE() == _PD_LENOVO_ATTENTION)
                    {
                        ucDataObjectCnt = 1;
                    }
                    else if(GET_PD_RX0_ATTN_TYPE() == _PD_HP_ATTENTION)
                    {
                        ucDataObjectCnt = 2;
                    }
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                    else if(GET_PD_RX0_ATTN_TYPE() == _PD_DELL_ATTENTION)
                    {
                        // User VDM Cnt Should be 0~6, plus VDM Header
                        ucDataObjectCnt = GET_PD_RX0_DELL_USER_VDM_CNT() + 1;
                    }
#endif

                    break;

                // If SVID = _DP_SID, CMD_10 = DP_Status REQ and CMD_11 = DP_Config REQ
                case _PD_VDM_CMD_10:
                case _PD_VDM_CMD_11:

                    ucDataObjectCnt = 2;
                    break;

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
                // If SVID = _LENOVO_VID, CMD_50 = GET_STATUS ACK
                case _PD_VDM_CMD_50:

                    ucDataObjectCnt = 3;
                    break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
                // If SVID = _HP_VID, CMD_52 = Set_vwire Sample ACK
                case _PD_VDM_CMD_52:

                    ucDataObjectCnt = GET_PD_RX0_HP_USER_VDM_CNT() + 2;
                    break;
#endif

                case _PD_VDM_CMD_RESERVED:
                default:

                    ucDataObjectCnt = 0;
                    break;
            }

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_BAT_STATUS:        // Not Implemented
        case _PD_CMD_ALERT:
        case _PD_CMD_GET_COUNTRY_INFO:  // Not Implemented

            ucDataObjectCnt = 1;
            break;
#endif
        default:

            ucDataObjectCnt = 0;
            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt != 0)
    {
        ScalerTypeCRx0PdConstructDataObj(enumPdCmd, enumVdmCmd);
    }

    // 3. [0x65E5] Construct Msg. Header 0
    // ===================================================================
    // | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    // |Ext| Num. of DO| PR|  Spec | DR|
    ucMsgHeader = ucMsgHeader | ucExtendedBit;
    ucMsgHeader = ucMsgHeader | (BYTE)(ucDataObjectCnt << 4);

    if(enumPacketType == _PD_SOP_PKT)
    {
        ucMsgHeader = ucMsgHeader | (GET_PD_RX0_POWER_ROLE() << 3);
        ucMsgHeader = ucMsgHeader | (GET_PD_RX0_SPEC_VER() << 1);
        ucMsgHeader = ucMsgHeader | GET_PD_RX0_DATA_ROLE();
    }
    else if((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT))
    {
        ucMsgHeader = ucMsgHeader | (BYTE)(_PD_DEVICE << 3);
        ucMsgHeader = ucMsgHeader | (GET_PD_RX0_CBL_SPEC_VER() << 1);
    }

    // ====================================================================

    // 4. Disable Rcv Msg. INT
    ScalerTypeCRx0PdRxIntControl(_DISABLE);

    // 5. Start to Fill Packet Type, Msg. Header & Data Object
    if(ScalerGetBit(P65_DA_TX_TRANSMIT_CTRL, _BIT7) == 0x00)
    {   // Do Not Write Tx FIFO When Tx is Transmitting During INT

        // [0x65E0] Select Transmission Mode
        // [7:6] b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
        ScalerSetBit(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

        // [0x65E0] Set Packet Type [5:3]
        ScalerSetBit(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

        // [0x65E5] Fill Message Header 0
        ScalerSetByte(P65_E5_TX_FIFO_MSG_HEADER0, ucMsgHeader);

        // [0x65E6] Fill in Msg. Header 1 ( Msg. Header[4:0] : Command Type = enumCtrlMsg )
        ScalerSetBit(P65_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Clear Tx FIFO Addr.
        ScalerSetByte(P65_E9_TX_FIFO_ADDR, 0x00);

        // Fill Data Object into Tx FIFO
        for(pData[0] = 0; pData[0] < (ucDataObjectCnt * 4); pData[0]++)
        {
            ScalerSetByte(P65_EA_TX_FIFO_DATA, g_pucDataObject[pData[0]]);
        }
    }

    // 6. Enable Rcv Msg. INT
    ScalerTypeCRx0PdRxIntControl(_ENABLE);
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT / _CABLE_RESET_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmd : _VDM_CMD_DISCOVER_ID / _VDM_CMD_DISCOVER_SVID ...
//                enumVdmCmdType : _VDM_CMD_TYPE_REQ / _VDM_CMD_TYPE_ACK ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructDataObj(EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd)
{
    // Clear g_pucDataObject_EXINT
    for(pData[0] = 0; pData[0] < _MAX_DATA_OBJ_CNT * 4; pData[0] ++)
    {
        g_pucDataObject[pData[0]] = 0;
    }

    // Process Data Object Fields For FIFO Fill
    switch(enumPdCmd)
    {
        case _PD_CMD_SRC_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
#if((_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                g_pucDataObject[0] = g_pucDataObject[0] | (_BIT5);
            }
#endif

#if(_USB_SUSPEND == _TRUE)
            g_pucDataObject[0] = g_pucDataObject[0] | (_BIT4);
#endif

            if(GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucDataObject[0] = g_pucDataObject[0] | (_BIT3);
            }

#if(_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucDataObject[0] = g_pucDataObject[0] | (_BIT2);
#endif

#if((_DFP_SWAP_TO_UFP == _TRUE) || (_UFP_SWAP_TO_DFP == _TRUE))
            g_pucDataObject[0] = g_pucDataObject[0] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[0] = g_pucDataObject[0] | (_BIT0);
            }
#endif

            for(pData[1] = 0; pData[1] < GET_PD_RX0_SRC_PDO_CNT(); pData[1] ++)
            {
                if(GET_PD_RX0_SRC_PDO_TYPE(pData[1]) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00
                    g_pucDataObject[(pData[1] * 4)] = g_pucDataObject[(pData[1] * 4)] | (((BYTE)GET_PD_RX0_SRC_PDO_TYPE(pData[1]) << 6));

                    // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
                    // |  Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucDataObject[(pData[1] * 4) + 1] = g_pucDataObject[(pData[1] * 4) + 1] | ((BYTE)(GET_PD_RX0_SRC_CAP_PEAK(pData[1]) << 4) & (_BIT5 | _BIT4));
                    g_pucDataObject[(pData[1] * 4) + 1] = g_pucDataObject[(pData[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData[1]) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucDataObject[(pData[1] * 4) + 2] = g_pucDataObject[(pData[1] * 4) + 2] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData[1]) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) && (GET_PD_RX0_SRC_CAP_CUR(pData[1]) > GET_PD_RX0_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucDataObject[(pData[1] * 4) + 2] = g_pucDataObject[(pData[1] * 4) + 2] | ((BYTE)(GET_PD_RX0_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                        g_pucDataObject[(pData[1] * 4) + 3] = g_pucDataObject[(pData[1] * 4) + 3] | ((BYTE)GET_PD_RX0_CBL_MAX_CUR());
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucDataObject[(pData[1] * 4) + 2] = g_pucDataObject[(pData[1] * 4) + 2] | ((BYTE)(GET_PD_RX0_SRC_CAP_CUR(pData[1]) >> 8) & (_BIT1 | _BIT0));
                        g_pucDataObject[(pData[1] * 4) + 3] = g_pucDataObject[(pData[1] * 4) + 3] | ((BYTE)(GET_PD_RX0_SRC_CAP_CUR(pData[1])));
                    }
                }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                else if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0) && (GET_PD_RX0_SRC_PDO_TYPE(pData[1]) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:30] PDO Type = 2'b11 (Programmabl Power Supply)
                    g_pucDataObject[(pData[1] * 4)] = g_pucDataObject[(pData[1] * 4)] | (((BYTE)GET_PD_RX0_SRC_PDO_TYPE(pData[1])) << 6);

                    // [24:17] Max Voltage in 100mV
                    g_pucDataObject[(pData[1] * 4)] = g_pucDataObject[(pData[1] * 4)] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData[1]) / 10) >> 7) & (_BIT0));
                    g_pucDataObject[(pData[1] * 4) + 1] = g_pucDataObject[(pData[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData[1]) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucDataObject[(pData[1] * 4) + 2] = (BYTE)(GET_PD_RX0_SRC_CAP_VOL_MIN(pData[1]) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) && (((GET_PD_RX0_SRC_CAP_CUR(pData[1])) * 5) > GET_PD_RX0_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucDataObject[(pData[1] * 4) + 3] = (((BYTE)(GET_PD_RX0_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucDataObject[(pData[1] * 4) + 3] = (((BYTE)GET_PD_RX0_SRC_CAP_CUR(pData[1])) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_REQUEST:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | 0  |   Obj. Pos   | GB | CM | UC | Sus|
            g_pucDataObject[0] = g_pucDataObject[0] | (GET_PD_RX0_REQ_OBJ_POS() << 4);
            g_pucDataObject[0] = g_pucDataObject[0] | (GET_PD_RX0_REQ_GIVE_BACK() << 3);

#if(_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucDataObject[0] = g_pucDataObject[0] | (_BIT1);
#endif

#if(_USB_SUSPEND == _FALSE)
            g_pucDataObject[0] = g_pucDataObject[0] | (_BIT0);
#endif

            // | 23 | 22 | 21 | 20 | 19 | ... | 16 | 15 | ... | 10 | 09 | 08 | 07 | ... | 00 |
            // | UC | Reserved(0)  |         Info1 [19:10]         |       Info2 [9:0]       |
#if(_UNCHUNK_SUPPORT == _TRUE)
            g_pucDataObject[1] = g_pucDataObject[1] | (_BIT7);
#endif

            if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(GET_PD_RX0_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
            {
                if((WORD)GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) < GET_PD_RX0_REQ_INFO_2())
                {
                    // Set Capability Mismatch Flag
                    g_pucDataObject[0] = g_pucDataObject[0] | (_BIT2);

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucDataObject[1] = g_pucDataObject[1] | ((BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucDataObject[2] = g_pucDataObject[2] | ((BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucDataObject[2] = g_pucDataObject[2] | ((BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) >> 8) & (_BIT1 | _BIT0));
                    g_pucDataObject[3] = g_pucDataObject[3] | (BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1));
                }
                else
                {
                    // Set Capability Mismatch Flag
                    g_pucDataObject[0] = g_pucDataObject[0] | ((GET_PD_RX0_REQ_CAP_MIS() << 2) & (_BIT2));

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucDataObject[1] = g_pucDataObject[1] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucDataObject[2] = g_pucDataObject[2] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucDataObject[2] = g_pucDataObject[2] | ((BYTE)(GET_PD_RX0_REQ_INFO_2() >> 8) & (_BIT1 | _BIT0));
                    g_pucDataObject[3] = g_pucDataObject[3] | (BYTE)(GET_PD_RX0_REQ_INFO_2());
                }
            }
            else
            {
                // Set Capability Mismatch Flag
                g_pucDataObject[0] = g_pucDataObject[0] | ((GET_PD_RX0_REQ_CAP_MIS() << 2) & (_BIT2));

                // RDO[19:9] : PPS (Vol in 20mV)
                g_pucDataObject[1] = g_pucDataObject[1] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() >> 7) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                g_pucDataObject[2] = g_pucDataObject[2] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : PPS (Op. Cur in 50mA)
                g_pucDataObject[3] = g_pucDataObject[3] | ((BYTE)(GET_PD_RX0_REQ_INFO_2()) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }

            break;

        case _PD_CMD_VDM:

            ScalerTypeCRx0PdConstructVdmDataObj(enumVdmCmd);

            break;

        case _PD_CMD_BIST:

            g_pucDataObject[0] = g_pucDataObject[0] | (_BIT7);

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OVP) == _PD_PORT_CTRL_EVENT_POWER_OVP))
            {
                g_pucDataObject[0] = g_pucDataObject[0] | (_BIT6);
            }
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OCP) == _PD_PORT_CTRL_EVENT_POWER_OCP))
            {
                g_pucDataObject[0] = g_pucDataObject[0] | (_BIT2);
            }
#else
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucDataObject[0] = g_pucDataObject[0] | (_BIT6);
            }
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucDataObject[0] = g_pucDataObject[0] | (_BIT2);
            }
#endif

            // Reserved for Future Usage.
            // [31] Rsv., [29] Source Input Change Event, [28] Operating Condition Change Event, [27] OTP Event, [25] Battery Status Change Event, [24] Rsv., [23:20] Fixed Batteries, [19:16] Hot Swappepable Batteries, [15:0] Rsv.

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ Main Loop
// Input Value  : enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmdType : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructVdmDataObj(EnumVdmCmd enumVdmCmd)
{
    switch(enumVdmCmd)
    {
        case _PD_VDM_CMD_DISCOVER_ID_REQ:
        case _PD_VDM_CMD_DISCOVER_SVID_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] PD SID = 0xFF00
            g_pucDataObject[0] = 0xFF;
            g_pucDataObject[1] = 0x00;

            // [15] Struct. VDM = 1, [14:13] VDM Ver , [12:11] Rsv., [10:8] Obj. Pos = b'000
            g_pucDataObject[2] = (_BIT7);

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
            }

            // [7:0] VDM CMD = Discover ID Request (0x01) / Discover SVID Request (0x02)
            g_pucDataObject[3] = enumVdmCmd;

            break;

        case _PD_VDM_CMD_DISCOVER_MODE_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucDataObject[0] = 0xFF;
            g_pucDataObject[1] = 0x01;

            // [15] Struct. VDM = 1, [14:13] VDM Ver , [12:11] Rsv., [10:8] Obj. Pos = b'000
            g_pucDataObject[2] = (_BIT7);

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
            }

            // [7:0] VDM CMD = Discover Mode Request (0x03)
            g_pucDataObject[3] = enumVdmCmd;

            break;

        case _PD_VDM_CMD_ENTER_MODE_REQ:
        case _PD_VDM_CMD_EXIT_MODE_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucDataObject[0] = 0xFF;
            g_pucDataObject[1] = 0x01;

            // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos = b'001-111
            g_pucDataObject[2] = (_BIT7) | (GET_PD_RX0_DP_OBJ_POS());

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
            }

            // [7:0] VDM CMD = Enter / Exit Mode Request (0x04 / 0x05)
            g_pucDataObject[3] = enumVdmCmd;

            break;

        // If SVID = _DP_SID, CMD_10 = DP_Status REQ
        case _PD_VDM_CMD_10:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucDataObject[0] = 0xFF;
            g_pucDataObject[1] = 0x01;

            // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
            g_pucDataObject[2] = (_BIT7) | (GET_PD_RX0_DP_OBJ_POS());

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
            }

            // [7:0] VDM CMD = DP Status Req (0x10)
            g_pucDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Status ---------
            // [31:16] Reserved = 0x00
            g_pucDataObject[4] = 0x00;
            g_pucDataObject[5] = 0x00;

            // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
            // [4] Multi-Func = No, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
            g_pucDataObject[6] = 0x00;
            g_pucDataObject[7] = (0x0A) | (GET_PD_RX0_MULTI_FUNCTION() << 4);

            if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_LOW)
            {
                DebugMessageSystem("8. [PD] HPD LOW : ", 0);
            }
            else
            {
                // HPD = HIGH or IRQ, HPD_High = 1
                g_pucDataObject[7] = (g_pucDataObject[7]) | (_BIT7);

                if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_HIGH)
                {
                    DebugMessageSystem("8. [PD] HPD HIGH : ", 1);
                }
                else
                {
                    g_pucDataObject[6] = _BIT0;

                    DebugMessageSystem("8. [PD] HPD IRQ : ", 1);
                }
            }

            if(GET_PD_RX0_DP_ALT_MODE_EXIT_REQ() == _TRUE)
            {
                g_pucDataObject[7] = g_pucDataObject[7] | (_BIT6);
            }

            break;

        // If SVID = _DP_SID, CMD_11 = DP_Config REQ
        case _PD_VDM_CMD_11:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucDataObject[0] = 0xFF;
            g_pucDataObject[1] = 0x01;

            // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
            g_pucDataObject[2] = (_BIT7) | (GET_PD_RX0_DP_OBJ_POS());

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
            }

            // [7:0] VDM CMD = DP Config Req (0x11)
            g_pucDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Configurations ---------
            // [31:16] Reserved = 0x00
            g_pucDataObject[4] = 0x00;
            g_pucDataObject[5] = 0x00;

            // [15:8] Pin Assignment to be Configured
            g_pucDataObject[6] = GET_PD_RX0_PIN_ASSIGNMENT();

            if(GET_PD_RX0_DP_ALT_MODE_TARGET_CONFIG() == _PD_DP_CONFIG)
            {
                // [7:6] Reserved, [5:2] Signaling : DP 1.3 = b'0001, [1:0] Other Side Config = DP_Tx = b'01
                g_pucDataObject[7] = 0x05;
            }
            else
            {
                // [7:6] Reserved, [5:2] Signaling : Signaling unspecified = b'0000, [1:0] Other Side Config = Config USB = b'00
                g_pucDataObject[7] = 0x00;
            }

            break;

        case _PD_VDM_CMD_ATTENTION_REQ:

            if(GET_PD_RX0_ATTN_TYPE() == _PD_DP_ATTENTION)
            {
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucDataObject[0] = 0xFF;
                g_pucDataObject[1] = 0x01;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObject[2] = (_BIT7) | (GET_PD_RX0_DP_OBJ_POS());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucDataObject[3] = enumVdmCmd;

                // -------- Data Obj 1 : DP Status ---------
                // [31:16] Reserved = 0x00
                g_pucDataObject[4] = 0x00;
                g_pucDataObject[5] = 0x00;

                // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
                // [4] Multi-Func = No, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
                g_pucDataObject[6] = 0x00;
                g_pucDataObject[7] = (0x0A) | (GET_PD_RX0_MULTI_FUNCTION() << 4);

                if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_LOW)
                {
                    DebugMessageSystem("8. [PD] HPD LOW : ", 0);
                }
                else
                {
                    // HPD = HIGH or IRQ, HPD_High = 1
                    g_pucDataObject[7] = (g_pucDataObject[7]) | (_BIT7);

                    if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_HIGH)
                    {
                        DebugMessageSystem("8. [PD] HPD HIGH : ", 1);
                    }
                    else
                    {
                        g_pucDataObject[6] = _BIT0;

                        DebugMessageSystem("8. [PD] HPD IRQ : ", 1);
                    }
                }

                if(GET_PD_RX0_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                {
                    g_pucDataObject[7] = g_pucDataObject[7] | (_BIT6);
                }
            }
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            else if(GET_PD_RX0_ATTN_TYPE() == _PD_LENOVO_ATTENTION)
            {
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucDataObject[0] = 0x17;
                g_pucDataObject[1] = 0xEF;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObject[2] = (_BIT7) | (GET_PD_RX0_LENOVO_OBJ_POS());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucDataObject[3] = enumVdmCmd;
            }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            else if(GET_PD_RX0_ATTN_TYPE() == _PD_HP_ATTENTION)
            {
                // HP Attention (Atten_vwire/ Atten_config/ Atten_data/ Atten_disconnect)
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucDataObject[0] = 0x03;
                g_pucDataObject[1] = 0xF0;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos = Attention Type
                g_pucDataObject[2] = (_BIT7) | (GET_PD_RX0_HP_ATTEN_TYPE());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucDataObject[3] = enumVdmCmd;

                // -------- Data Obj 1 : Hp Attention Payload -----
                // [31:29] Hp Ver = 3b'011, [28:26] Atten_type, [25:24] Rsv.
                g_pucDataObject[4] = (_BIT6 | _BIT5) | (GET_PD_RX0_HP_ATTEN_TYPE() << 2);

                // [23:18] Rsv., [17:0] AM_addr
                g_pucDataObject[5] = (GET_PD_RX0_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
                g_pucDataObject[6] = GET_PD_RX0_HP_OWN_AM_ADDR_M();
                g_pucDataObject[7] = GET_PD_RX0_HP_OWN_AM_ADDR_L();
            }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            else if(GET_PD_RX0_ATTN_TYPE() == _PD_DELL_ATTENTION)
            {
                // DELL Attention
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DELL VID = 0x413C
                g_pucDataObject[0] = (BYTE)(_DELL_VID >> 8);
                g_pucDataObject[1] = (BYTE)_DELL_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObject[2] = (_BIT7) | (GET_PD_RX0_DELL_OBJ_POS());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucDataObject[3] = enumVdmCmd;

                // -------- Data Obj 1~7 : Dell Attention Payload -----
                // Fill in the Data of User Event
                for(pData[0] = 0; pData[0] < (GET_PD_RX0_DELL_USER_VDM_CNT() * 4); pData[0]++)
                {
                    g_pucDataObject[pData[0] + 4] = GET_PD_RX0_DELL_USER_VDM_DATA(pData[0]);
                }
            }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

            break;

        // If SVID = _LENOVO_VID, CMD_50 = GET_STATUS ACK
        case _PD_VDM_CMD_50:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] LENOVO VID = 0x17EF
            g_pucDataObject[0] = 0x17;
            g_pucDataObject[1] = 0xEF;

            // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
            g_pucDataObject[2] = (_BIT7);

            // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
            }

            // [7:0] VDM CMD = Get Status Ack (0x50)
            g_pucDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : Lenovo Get Status Response VDO1-----
            // [31:28] Rsv., [27] Docking Power Button Break, [26] Docking Power Button Make,
            // [25] Wol Request, [24] Event
            g_pucDataObject[4] = GET_PD_RX0_LENOVO_DOCK_EVENT();

            // [23:20] Rsv., [19] System Acknowledge Power Button Break, [18] System Acknowledge Power Button Make,
            // [17] Wol Request, [16] Event Acknowledge
            g_pucDataObject[5] = (GET_PD_RX0_LENOVO_SYS_ACKNOWLEDGE() & 0xFE);

            // [15:13] Rsv., [12] System Power Mode, [11:9] System State, [8] Event
            g_pucDataObject[6] = GET_PD_RX0_LENOVO_SYS_EVENT();

            // [7:5] Rsv., [4] Docking Acknowledge System Power Mode, [3:1] Docking Acknowledge System State, [0] Event Acknowledge
            g_pucDataObject[7] = GET_PD_RX0_LENOVO_SYS_EVENT();

            // -------- Data Obj 2 : Lenovo Get Status Response VDO2-----
            // [31:28] FW Ver. = 0, [27:24] Rsv.
            g_pucDataObject[8] = 0x00;

            // Power Source
            // [23] Supplier Info = 0, [22:21] Src Type : Type-C Adapter, [20] Src Quality = Good, [19:16] Rating = Unknown AC adapter detected
            g_pucDataObject[9] = 0x30;

            // Function Capability
            // [15] Power Button Supported, [14] Wol Supported, [13] Wol Supported,
            // [12] MAC address pass through not Supported, [11] Change charging ability not Supported, [11:8] Rsv.
            g_pucDataObject[10] = 0xC0;

            // [7:0] Reserved = 0x00
            g_pucDataObject[11] = 0x00;

            break;

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
        // Acer VDM Attention
        case _PD_VDM_CMD_15:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] ACER VID = 0x0502
            g_pucDataObject[0] = (BYTE)(_ACER_VID >> 8);
            g_pucDataObject[1] = (BYTE)_ACER_VID;

            // [15] Struct. VDM = 1, [14:13] VDM Ver = 2b'01, [12:11] Rsv., [10:8] Rsv.
            g_pucDataObject[2] = (_BIT7) | (_BIT5);

            // [7:0] VDM CMD = Attention Req (0x15)
            g_pucDataObject[3] = enumVdmCmd;

            break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
        // Hp VDM Set_vwire Sample ACK
        case _PD_VDM_CMD_52:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] HP VID = 0x03F0
            g_pucDataObject[0] = 0x03;
            g_pucDataObject[1] = 0xF0;

            // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
            g_pucDataObject[2] = (_BIT7) | (_BIT0);

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObject[2] = g_pucDataObject[2] | (_BIT5);
            }

            // [7:0] VDM CMD = Set_vwire Sample ACK (0x52)
            g_pucDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : Hp Sub Header -----
            // [31:23] Rsv., [22:20] VDO_CNT
            g_pucDataObject[5] = g_pucDataObject[5] | ((GET_PD_RX0_HP_USER_VDM_CNT() << 4) & (_BIT6 | _BIT5 | _BIT4));

            // [19:18] Rsv., [17:0] AM_addr
            g_pucDataObject[5] = g_pucDataObject[5] | (GET_PD_RX0_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
            g_pucDataObject[6] = GET_PD_RX0_HP_OWN_AM_ADDR_M();
            g_pucDataObject[7] = GET_PD_RX0_HP_OWN_AM_ADDR_L();

            // -------- Data Obj 2 : Hp V-wire VDO1 -----
            // [31:16] Data, [15:8] Index, [7:4] Rsv., [3:0] Operation
            for(pData[0] = 0; pData[0] < (GET_PD_RX0_HP_USER_VDM_CNT() * 4); pData[0]++)
            {
                g_pucDataObject[pData[0] + 8] = GET_PD_RX0_HP_USER_VDM_DATA(pData[0]);
            }

            break;
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Send Soft Reset Message
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendSoftRst(EnumPDPacketType enumPacketType)
{
    // 1. Clear Flags & Reset PRL Layer [0x6503]
    CLR_PD_RX0_TRANSMIT_RESULT();
    ScalerSetBit(P65_03_PD_TOP_RST, ~_BIT0, 0x00);

    // 2. Construct Msg.
    ScalerTypeCRx0PdConstructSoftReset(enumPacketType);

    // 3. [0x65DC] Clear IRQs
    ScalerSetBit(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // 4. Enable PRL Layer & Release Message ID Reset [0x6503/E4]
    ScalerSetBit(P65_03_PD_TOP_RST, ~_BIT0, _BIT0);
    ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
        ScalerSetBit(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

        // 5. [0x65DA] Start Transmit ([1] = 1, Wait For GoodCRC Response After Transmission)
        ScalerSetBit(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

        // 6. Transit State
        SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
        SET_PD_RX0_FW_STATE(_PD_INT_SEND_SOFTRESET);
    }
    else
    {
        // 5. [0x65DA] Start Transmit ([1] = 1, Wait For GoodCRC Response After Transmission)
        ScalerSetBit(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

        // 6. For Main Loop : Polling Sending Result (timeout = 1.5*4(msg) + 1.1*3 (CrcTimer) = 10ms)
        if(ScalerTimerPollingFlagProc(_PD_SEND_MSG_TIMEOUT, P65_DC_TX_PD_MSG_INT, _BIT5, _BIT5) == _TRUE)
        {
            // tx_prl_trans_done_irq = 1
            SET_PD_RX0_TRANSMIT_RESULT(ScalerGetByte(P65_DC_TX_PD_MSG_INT) & (0x1F));
        }
        else
        {   // !!! WARNING : No Transmission Result !!!
            SET_PD_RX0_TRANSMIT_RESULT(_PD_SENT_RETRY_FAIL);
        }
    }
}

//--------------------------------------------------
// Description  : Construct Soft Reset Msg.
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructSoftReset(EnumPDPacketType enumPacketType)
{
    // 1. [0x65E0] Set Transmit Type : b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
    ScalerSetBit(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

    // 2. [0x65E0] Set Packet Type [5:3]
    ScalerSetBit(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

    // 3. [0x65E5] Fill in Msg. Header0
    // [7]   Msg. Header[15]     : Extended Field = 0
    // [6:4] Msg. Header[14:12]  : Number of Data Object = 0
    ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [3]   Msg. Header[8]  : Power Role
    // [0]   Msg. Header[5]  : Data Role
    if(enumPacketType == _PD_SOP_PKT)
    {
        // [3] Power Role / [2:1] Spec Version / [0] Data Role
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, (GET_PD_RX0_POWER_ROLE() << 3));
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2, _BIT1), (GET_PD_RX0_SPEC_VER() << 1));
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_PD_RX0_DATA_ROLE());

        // Reset Message ID [0x65E4]
        ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~_BIT2, 0x00);
    }
    else
    {
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, ((BYTE)_PD_DEVICE << 3));
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2, _BIT1), (GET_PD_RX0_CBL_SPEC_VER() << 1));
        ScalerSetBit(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);

        if(enumPacketType == _PD_SOP_P_PKT)
        {
            // Reset Message ID [0x65E4]
            ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~_BIT1, 0x00);
        }
        else if(enumPacketType == _PD_SOP_PP_PKT)
        {
            // Reset Message ID [0x65E4]
            ScalerSetBit(P65_E4_TX_MSG_ID_RST, ~_BIT0, 0x00);
        }
    }

    // [0x65E6] Fill in Msg. Header1
    // [4:0]  Msg. Header[4:0]    : Command Type = b'0_1101
    ScalerSetBit(P65_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
}

//--------------------------------------------------
// Description  : Initiate Hard Reset When Error Happens
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendHardRst(void)
{
    if(GET_DP_RX0_HARD_RST_CNT() <= _MAX_HARD_RST_CNT)
    {
        // 1. [0x65E0] Select Transmission Mode [7:6] : b'01 = Preamble + SOP
        ScalerSetBit(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), _BIT6);

        // 2. [0x65E0] Set Packet Type [5:3] : b'011 = HARD_RESET
        ScalerSetBit(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

        // 3. [0x65DC] Clear IRQs
        ScalerSetBit(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // 4. [0x65DA] Start Transmit ([1] : Do Not Wait For GoodCRC)
        ScalerSetBit(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
        ADD_DP_RX0_HARD_RST_CNT();

        // 5. Process Hard Reset
        ScalerTypeCRx0PdProcHardRst();
    }
    else
    {
        // Do Type-C Error Recovery
        SET_TYPE_C_ERROR_RECOVERY();
    }
}

//--------------------------------------------------
// Description  : Process Hard Reset When Hard Reset Sent/Rcv.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdProcHardRst(void)
{
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        // Clear Hard Reset Turn Off Power Flag (Set When Power Already Turned Off)
        CLR_PD_RX0_HRST_PWR_OFF();

        // TD.PD.SRC.E6 : Source can Start Changing Power After tSrcTransition = 25-35 ms
        ScalerTimerActiveTimerEvent(_SRC_ADJUST_POWER_TIMER, _SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER);
    }
    else
    {
        // 1. Turn Off Power Draw
        ScalerTypeCPowerRx0VbusControl(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // 2. Turn Off Type-C Unattach Vbus Detection
        ScalerTypeCRx0CcVbusDetCtrl(_DISABLE);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC)
    {
        ScalerTypeCRx0CcVconnControl(_OFF);
    }

    // [0x6502] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6543] Clear and Disable Hard Reset IRQ
    ScalerSetBit(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_PD_RX0_FW_STATE(_PD_HARDRESET);
}

//--------------------------------------------------
// Description  : Send Power Delivery Message in Interrupt
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT / _CABLE_RESET_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmd : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendMsg_EXINT0(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd) using 1
{
    // 1. Clear Flags
    CLR_PD_RX0_TRANSMIT_RESULT_EXINT();

    // 2. Check Valid Msg
    // if(ScalerTypeCRx0PdSendMsgCheck_EXINT0(enumPacketType, enumPdCmd) == _FALSE)

    // 3. Construct Msg.
    ScalerTypeCRx0PdConstructMsg_EXINT0(enumPacketType, enumPdCmd, enumVdmCmd);

    // 4. Send Msg. (Interrupt Does Not Check Overwrite and Disable Rcv Msg.)
    // [0x65DC] Clear IRQs
    ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
    ScalerSetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

    // [0x65DA] Start Transmit ([1] = 0, Wait For GoodCRC Response After Transmission)
    ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

    // [0x65E5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
}

//--------------------------------------------------
// Description  : Send Power Delivery Message @ Interrupt
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT / _CABLE_RESET_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmd : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructMsg_EXINT0(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd) using 1
{
    BYTE ucExtendedBit_EXINT = 0;
    BYTE ucDataObjectCnt_EXINT = 0;

    // 1. [0x65E9-EA] Set Up Number of Data Objects(Data Blocks) if Needed
    switch(enumPdCmd)
    {
        // Control Message Has No Data Object
        case _PD_CMD_RSV:
        case _PD_CMD_GOODCRC:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PING:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_GET_SRC_CAP:
        case _PD_CMD_GET_SNK_CAP:
        case _PD_CMD_DR_SWAP:
        case _PD_CMD_PR_SWAP:
        case _PD_CMD_VCONN_SWAP:
        case _PD_CMD_WAIT:
        case _PD_CMD_SOFT_RESET:
#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_NOT_SUPPORT:
        case _PD_CMD_GET_SRC_CAP_EXT:
        case _PD_CMD_GET_STATUS:
        case _PD_CMD_FR_SWAP:
        case _PD_CMD_GET_PPS_STATUS:
        case _PD_CMD_GET_COUNTRY_CODES:
#endif

            ucDataObjectCnt_EXINT = 0;
            break;

        // Data Message Has Different Num of Data Objects According to Different Message
        case _PD_CMD_SRC_CAP:

            ucDataObjectCnt_EXINT = GET_PD_RX0_SRC_PDO_CNT();

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0)
#endif
            {
                for(pData_EXINT[0] = GET_PD_RX0_SRC_PDO_CNT() - 1; pData_EXINT[0] > 0; pData_EXINT[0]--)
                {
                    if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ucDataObjectCnt_EXINT --;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;

        case _PD_CMD_REQUEST:

            ucDataObjectCnt_EXINT = 1;
            break;

        case _PD_CMD_BIST:

            ucDataObjectCnt_EXINT = 0;
            break;

        case _PD_CMD_SNK_CAP:

            ucDataObjectCnt_EXINT = GET_PD_RX0_SNK_PDO_CNT();
            break;

        case _PD_CMD_VDM:

            ucDataObjectCnt_EXINT = ScalerTypeCRx0PdSetVdmDataObjCnt_EXINT0(enumVdmCmd);
            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_BAT_STATUS:        // Not Implemented
        case _PD_CMD_ALERT:
        case _PD_CMD_GET_COUNTRY_INFO:  // Not Implemented

            ucDataObjectCnt_EXINT = 1;

            break;

        // Extended Message Has Different Num Data Obj. According to Different Message
        case _PD_CMD_SRC_CAP_EXT:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 7;

            break;

        case _PD_CMD_STATUS:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 3;

            break;

        case _PD_CMD_MFC_INFO:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 5;

            break;

        case _PD_CMD_CHUNK_TEST:

            if(GET_PD_RX0_CHUNK_REQUEST() == _TRUE)
            {
                ucExtendedBit_EXINT = 1;
                ucDataObjectCnt_EXINT = 1;
            }

            break;

        case _PD_CMD_PPS_STATUS:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 2;

            break;

        case _PD_CMD_GET_BAT_CAP:
        case _PD_CMD_GET_BAT_STATUS:
        case _PD_CMD_BAT_CAP:
        case _PD_CMD_GET_MFC_INFO:
        case _PD_CMD_SEC_REQ:
        case _PD_CMD_SEC_RESP:
        case _PD_CMD_FW_UPDATE_REQ:
        case _PD_CMD_FW_UPDATE_RESP:
        case _PD_CMD_COUNTRY_INFO:
        case _PD_CMD_COUNTRY_CODES:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 0;
            break;
#endif
        default:

            ucDataObjectCnt_EXINT = 0;
            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt_EXINT != 0)
    {
        ScalerTypeCRx0PdConstructDataObj_EXINT0(enumPdCmd, enumVdmCmd);
    }

    // 3. Start to Fill Packet Type, Msg. Header & Data Object
    // [0x65E0] Select Transmission Mode [7:6] b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
    ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

    // [0x65E0] Set Packet Type [5:3]
    ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

    // 4. [0x65E5] Fill in Msg. Header0
    // [7]   Msg. Header[15]     : Extended Field
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT7, (ucExtendedBit_EXINT << 7));

    // [6:4] Msg. Header[14:12]  : Number of Data Object
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT6 | _BIT5 | _BIT4), ((ucDataObjectCnt_EXINT << 4) & (_BIT6 | _BIT5 | _BIT4)));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // [3]   Msg. Header[8]  : Power Role
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_PD_RX0_POWER_ROLE() << 3);

        // [2:1] Msg. Header[7:6]  : Spec Version
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_PD_RX0_SPEC_VER() << 1);

        // [0]   Msg. Header[5]  : Data Role
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_PD_RX0_DATA_ROLE());
    }
    else
    {
        // [3]   Msg. Header[8]  : Cable Plug = Device (1)
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, ((BYTE)_PD_DEVICE << 3));

        // [2:1] Msg. Header[7:6]  : Cable Spec Version
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_PD_RX0_CBL_SPEC_VER() << 1);
    }

    // [0x65E6] Fill in Msg. Header1
    // [4:0]  Msg. Header[4:0]    : Command Type = enumCtrlMsg
    ScalerSetBit_EXINT(P65_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

    // Clear Tx FIFO Addr.
    ScalerSetByte_EXINT(P65_E9_TX_FIFO_ADDR, 0x00);

    // Fill Data Object into Tx FIFO
    for(pData_EXINT[0] = 0; pData_EXINT[0] < (ucDataObjectCnt_EXINT * 4); pData_EXINT[0]++)
    {
        ScalerSetByte_EXINT(P65_EA_TX_FIFO_DATA, g_pucDataObj_EXINT[pData_EXINT[0]]);
    }
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ Interrupt
// Input Value  : enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmdType : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructDataObj_EXINT0(EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd) using 1
{
    // Clear ucDataObj_EXINT
    for(pData_EXINT[0] = 0; pData_EXINT[0] < _MAX_DATA_OBJ_CNT * 4; pData_EXINT[0] ++)
    {
        g_pucDataObj_EXINT[pData_EXINT[0]] = 0;
    }

    // Process Data Object Fields For FIFO Fill
    switch(enumPdCmd)
    {
        case _PD_CMD_SRC_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
#if((_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT5);
            }
#endif

#if(_USB_SUSPEND == _FALSE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT4);
#endif
            if(GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT3);
            }

#if(_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);
#endif

#if((_DFP_SWAP_TO_UFP == _TRUE) || (_UFP_SWAP_TO_DFP == _TRUE))
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT0);
            }
#endif

            for(pData_EXINT[1] = 0; pData_EXINT[1] < GET_PD_RX0_SRC_PDO_CNT(); pData_EXINT[1] ++)
            {
                if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1]) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | (((BYTE)GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1])) << 6);

                    // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
                    // |  Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)(GET_PD_RX0_SRC_CAP_PEAK(pData_EXINT[1]) << 4) & (_BIT5 | _BIT4));
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) && (GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1]) > GET_PD_RX0_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)(GET_PD_RX0_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] | ((BYTE)GET_PD_RX0_CBL_MAX_CUR());
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)(GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1]) >> 8) & (_BIT1 | _BIT0));
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] | ((BYTE)(GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1])));
                    }
                }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                else if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0) && (GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1]) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:30] PDO Type = 2'b11 (Programmabl Power Supply)
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | (((BYTE)GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1])) << 6);

                    // [24:17] Max Voltage in 100mV
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 10) >> 7) & (_BIT0));
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = (BYTE)(GET_PD_RX0_SRC_CAP_VOL_MIN(pData_EXINT[1]) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) && (((GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1])) * 5) > GET_PD_RX0_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = (((BYTE)(GET_PD_RX0_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = (((BYTE)GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1])) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_REQUEST:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | 0  |   Obj. Pos   | GB | CM | UC | Sus|
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (GET_PD_RX0_REQ_OBJ_POS() << 4);
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (GET_PD_RX0_REQ_GIVE_BACK() << 3);

#if(_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT1);
#endif

#if(_USB_SUSPEND == _FALSE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT0);
#endif

            // | 23 | 22 | 21 | 20 | 19 | ... | 16 | 15 | ... | 10 | 09 | 08 | 07 | ... | 00 |
            // | UC | Reserved(0)  |         Info1 [19:10]         |       Info2 [9:0]       |
#if(_UNCHUNK_SUPPORT == _TRUE)
            g_pucDataObj_EXINT[1] = g_pucDataObj_EXINT[1] | (_BIT7);
#endif

            if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(GET_PD_RX0_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
            {
                if((WORD)GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) < GET_PD_RX0_REQ_INFO_2())
                {
                    // Set Capability Mismatch Flag
                    g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucDataObj_EXINT[1] = g_pucDataObj_EXINT[1] | ((BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | ((BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | ((BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1) >> 8) & (_BIT1 | _BIT0));
                    g_pucDataObj_EXINT[3] = g_pucDataObj_EXINT[3] | (BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1));
                }
                else
                {
                    // Set Capability Mismatch Flag
                    g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | ((GET_PD_RX0_REQ_CAP_MIS() << 2) & (_BIT2));

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucDataObj_EXINT[1] = g_pucDataObj_EXINT[1] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | ((BYTE)(GET_PD_RX0_REQ_INFO_2() >> 8) & (_BIT1 | _BIT0));
                    g_pucDataObj_EXINT[3] = g_pucDataObj_EXINT[3] | (BYTE)(GET_PD_RX0_REQ_INFO_2());
                }
            }
            else
            {
                // Set Capability Mismatch Flag
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | ((GET_PD_RX0_REQ_CAP_MIS() << 2) & (_BIT2));

                // RDO[19:9] : PPS (Vol in 20mV)
                g_pucDataObj_EXINT[1] = g_pucDataObj_EXINT[1] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() >> 7) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | ((BYTE)(GET_PD_RX0_REQ_INFO_1() << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : PPS (Op. Cur in 50mA)
                g_pucDataObj_EXINT[3] = g_pucDataObj_EXINT[3] | ((BYTE)(GET_PD_RX0_REQ_INFO_2()) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }

            break;

        case _PD_CMD_SNK_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| PR | HC | UP | UC | DR | -- |
#if((_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT5);
            }
#endif

#if(_HIGHER_CAP == _TRUE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT4);
#endif

            if(GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT3);
            }

#if(_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);
#endif

#if((_DFP_SWAP_TO_UFP == _TRUE) || (_UFP_SWAP_TO_DFP == _TRUE))
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT1);
#endif

            for(pData_EXINT[1] = 0; pData_EXINT[1] < GET_PD_RX0_SNK_PDO_CNT(); pData_EXINT[1] ++)
            {
                if(GET_PD_RX0_SNK_PDO_TYPE(pData_EXINT[1]) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | (((BYTE)GET_PD_RX0_SNK_PDO_TYPE(pData_EXINT[1])) << 6);

                    // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
                    // | FR | Reserved(0)  | Voltage(50mV)[9:6]|
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SNK_CAP_VOL_MAX(pData_EXINT[1]) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)((GET_PD_RX0_SNK_CAP_VOL_MAX(pData_EXINT[1]) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)(GET_PD_RX0_SNK_CAP_CUR(pData_EXINT[1]) >> 8) & (_BIT1 | _BIT0));
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] | ((BYTE)(GET_PD_RX0_SNK_CAP_CUR(pData_EXINT[1])));
                }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                else if(GET_PD_RX0_SNK_PDO_TYPE(pData_EXINT[1]) == _PD_3_PROGRAMMABLE_PDO)
                {
                    // [31:30] PDO Type = 2'b11 (Programmabl Power Supply)
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | (((BYTE)GET_PD_RX0_SNK_PDO_TYPE(pData_EXINT[1])) << 6);

                    // [24:17] Max Voltage in 100mV
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | ((BYTE)((GET_PD_RX0_SNK_CAP_VOL_MAX(pData_EXINT[1]) / 10) >> 7) & (_BIT0));
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SNK_CAP_VOL_MAX(pData_EXINT[1]) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = (BYTE)(GET_PD_RX0_SNK_CAP_VOL_MIN(pData_EXINT[1]) / 10);

                    // [6:0] Max Current in 50mA
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = (((BYTE)GET_PD_RX0_SNK_CAP_CUR(pData_EXINT[1])) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_BIST:

            break;

        case _PD_CMD_VDM:

            ScalerTypeCRx0PdConstructVdmDataObj_EXINT0(enumVdmCmd);
            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OVP) == _PD_PORT_CTRL_EVENT_POWER_OVP))
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT6);
            }
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OCP) == _PD_PORT_CTRL_EVENT_POWER_OCP))
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);
            }
#else
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT6);
            }
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);
            }
#endif

            // Reserved for Future Usage.
            // [31] Rsv., [29] Source Input Change Event, [28] Operating Condition Change Event, [27] OTP Event, [25] Battery Status Change Event, [24] Rsv., [23:20] Fixed Batteries, [19:16] Hot Swappepable Batteries, [15:0] Rsv.

            break;

        case _PD_CMD_SRC_CAP_EXT:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 25
            g_pucDataObj_EXINT[1] = 25;

            // ---------- SECDB : Source Cap Ext Data Blocks (23 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucDataObj_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucDataObj_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucDataObj_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucDataObj_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 07 :   XID

            // Byte 08 : FW Version
            g_pucDataObj_EXINT[10] = _PD_FW_VERSION;

            // Byte 09 : HW Version
            g_pucDataObj_EXINT[11] = _PD_HW_VERSION;

            // Byte 10 : Voltage Regulation
            // Byte 11 : Holdup Time
            // Byte 12 : Compliance
            // Byte 13 : Touch Current
            // Byte 14 - 15 : Peak Current 1
            // Byte 16 - 17 : Peak Current 2
            // Byte 18 - 19 : Peak Current 3
            // Byte 20 : Touch Temp
            // Byte 21 : Source Input [0] Ext Power / [1] Ext Power Unconstrained / [2] Internal Battery Exist
            g_pucDataObj_EXINT[23] = (_BIT1 | _BIT0);

            // Byte 22 : Battries
            // Byte 23 : SPR Source PDP Rating [Unit = W]
            g_pucDataObj_EXINT[25] = (GET_RX0_MAX_POWER() / 10);

            // Byte 24 : EPR Source PDP Rating [Unit = W]

            break;

        case _PD_CMD_STATUS:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 7
            g_pucDataObj_EXINT[1] = 7;

            // ---------- SDB : Status Data Blocks (6 Bytes) ----------
            // Byte 00 : Internal Temp (Unit = Temp in C / 0 = Not Support)

            // Byte 01 : Present Input [7:5] Reserved
            // [4] Internal Power From Non Battery
            // [3] Internal Power From Battery
            // [2] External Power DC = 0 / AC = 1
            // [1] External Power Exist
            g_pucDataObj_EXINT[3] = g_pucDataObj_EXINT[3] | (_BIT4 | _BIT2 | _BIT1);

            // Byte 02 : Present Battery Input [7:4] : Hot Swappable / [3:0] Fixed Battery
            // Byte 03 : Event Flag [7:5] : Reserved / [4] : CC,CV / [3] : OVP / [2] OTP / [1] OCP / [0] Reserved
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OVP) == _PD_PORT_CTRL_EVENT_POWER_OVP))
            {
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (_BIT3);
            }
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OCP) == _PD_PORT_CTRL_EVENT_POWER_OCP))
            {
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (_BIT1);
            }
#else
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (_BIT3);
            }
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (_BIT1);
            }
#endif

            // Byte 04 : Temperature State
            // Byte 05 : Power Status [1] Source power limited due to cable supported current
            for(pData_EXINT[1] = 0; pData_EXINT[1] < GET_PD_RX0_SRC_PDO_CNT(); pData_EXINT[1] ++)
            {
                if(GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1]) > GET_PD_RX0_CBL_MAX_CUR())
                {
                    g_pucDataObj_EXINT[7] = g_pucDataObj_EXINT[7] | (_BIT1);
                }
            }

            // Byte 06 : Power State Change

            break;

        case _PD_CMD_MFC_INFO:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 4 ~ 26.
            // [MQP] PD3.0 Protocol test (Source) : GPROT-SRC3-MNINF.
            // Rcv. Get_Manu_Info with Invalid Target/Reference Shall Resp. Manu_Info with (VID + PID + Null-Ended "Not Supported" ASCII String).
            g_pucDataObj_EXINT[1] = 18;

            // ---------- MIDB : Manufacturer Into Data Blocks (18 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucDataObj_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucDataObj_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucDataObj_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucDataObj_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 26 :   Manufacturer String
            g_pucDataObj_EXINT[6] = 0x4E; // N
            g_pucDataObj_EXINT[7] = 0x6F; // o

            g_pucDataObj_EXINT[8] = 0x74; // t
            g_pucDataObj_EXINT[9] = 0x20; // " "

            g_pucDataObj_EXINT[10] = 0x53; // S
            g_pucDataObj_EXINT[11] = 0x75; // u

            g_pucDataObj_EXINT[12] = 0x70; // p
            g_pucDataObj_EXINT[13] = 0x70; // p

            g_pucDataObj_EXINT[14] = 0x6F; // o
            g_pucDataObj_EXINT[15] = 0x72; // r

            g_pucDataObj_EXINT[16] = 0x74; // t
            g_pucDataObj_EXINT[17] = 0x65; // e

            g_pucDataObj_EXINT[18] = 0x64; // d
            g_pucDataObj_EXINT[19] = 0x00; // NULL

            break;

        case _PD_CMD_CHUNK_TEST:

            // If More Chunk Resp. Need to  Be Requested
            if(GET_PD_RX0_CHUNK_REQUEST() == _TRUE)
            {
                // ---------- Extended Message Header (2 Bytes) ----------
                // [15] Ext Msg. is Sent in Chunk, [10] Chunk Request, [8:0] Data Size of Chunk Request Should Be 0
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT7 | _BIT2);

                // [14:11] Requested Next Chunk
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | ((GET_PD_RX0_CHUNK_NUMBER() + 1) << 3);
            }

            break;

        case _PD_CMD_PPS_STATUS:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 4
            g_pucDataObj_EXINT[1] = 4;

            // ---------- PPSSDB : PPS Status Data Blocks (4 Bytes) ----------
            // Byte 00 - 01 : Output Voltage in 20mV (0xFFFF Not Support)
            g_pucDataObj_EXINT[2] = 0xFF;
            g_pucDataObj_EXINT[3] = 0xFF;

            // Byte 02 : Output Current in 50mA (0xFF Not Support)
            g_pucDataObj_EXINT[4] = 0xFF;

            // Byte 03 : Real Time Flag
            // [3] OMF (1 : Current Fold Back / 0 : Constant Voltge)
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            if(ScalerTypeCPmicRx0ReadPpsOperationModeStatus_EXINT0() == _TYPE_C_PMIC_CC_MODE_OPERATION)
            {
                // Set Current Limit Mode
                g_pucDataObj_EXINT[5] |= _BIT3;
            }
            else
            {
                // Set Constant Voltage Mode
                g_pucDataObj_EXINT[5] &= ~_BIT3;
            }
#else
            // Set Constant Voltage Mode
            g_pucDataObj_EXINT[5] &= ~_BIT3;
#endif

            break;
#endif  // #if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))

        default:

            break;
    }// End of switch(enumPdCmd)
}

//--------------------------------------------------
// Description  : Set Up Number of VDM Data Objects(Data Blocks) @ Interrupt
// Input Value  : enumVdmCmd
// Output Value : Number of VDM Data Objects
//--------------------------------------------------
BYTE ScalerTypeCRx0PdSetVdmDataObjCnt_EXINT0(EnumVdmCmd enumVdmCmd) using 1
{
    BYTE ucVdmDataObjectCnt_EXINT = 0;

    if(GET_PD_RX0_VDM_SVID() == _PD_SID)
    {
        switch(enumVdmCmd)
        {
            case _PD_VDM_CMD_DISCOVER_ID_NAK:
            case _PD_VDM_CMD_DISCOVER_SVID_NAK:
            case _PD_VDM_CMD_DISCOVER_ID_BUSY:
            case _PD_VDM_CMD_DISCOVER_SVID_BUSY:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_CMD_DISCOVER_SVID_ACK:

                ucVdmDataObjectCnt_EXINT = 1 + (_ALT_MODE_SUPPORT_CNT >> 1) + 1;
                break;

            case _PD_VDM_CMD_DISCOVER_ID_ACK:

                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    if((GET_PD_RX0_UFP_PRODUCT_TYPE() != _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED) && (GET_PD_RX0_DFP_PRODUCT_TYPE() != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED))
                    {
                        ucVdmDataObjectCnt_EXINT = 7;
                    }
                    else if((GET_PD_RX0_UFP_PRODUCT_TYPE() != _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED) || (GET_PD_RX0_DFP_PRODUCT_TYPE() != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED))
                    {
                        ucVdmDataObjectCnt_EXINT = 5;
                    }
                    else
                    {
                        ucVdmDataObjectCnt_EXINT = 4;
                    }
                }
                else
                {
#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
                    ucVdmDataObjectCnt_EXINT = 5;
#else
                    if((GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB) || (GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL) || (GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED))
                    {
                        ucVdmDataObjectCnt_EXINT = 4;
                    }
#endif
                }
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
    else if(GET_PD_RX0_VDM_SVID() == _DP_SID)
    {
        EnumVdmDpCmd enumVdmDpCmd = _PD_VDM_DP_CMD_RESERVED;

        enumVdmDpCmd = (EnumVdmDpCmd)enumVdmCmd;

        switch(enumVdmDpCmd)
        {
            case _PD_VDM_DP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DP_CMD_DP_CONFIG_ACK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DP_CMD_DP_STATUS_NAK:
            case _PD_VDM_DP_CMD_DP_CONFIG_NAK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_BUSY:
            case _PD_VDM_DP_CMD_ENTER_MODE_BUSY:
            case _PD_VDM_DP_CMD_EXIT_MODE_BUSY:
            case _PD_VDM_DP_CMD_DP_STATUS_BUSY:
            case _PD_VDM_DP_CMD_DP_CONFIG_BUSY:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_DP_CMD_DISCOVER_MODE_ACK:
            case _PD_VDM_DP_CMD_DP_STATUS_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _LENOVO_VID)
    {
        EnumVdmLenovoCmd enumVdmLenovoCmd = _PD_VDM_LENOVO_CMD_RESERVED;

        enumVdmLenovoCmd = (EnumVdmLenovoCmd)enumVdmCmd;

        switch(enumVdmLenovoCmd)
        {
            case _PD_VDM_LENOVO_CMD_ENTER_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_ACK:
            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_ENTER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_GET_STATUS_NAK:
            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_NAK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            case _PD_VDM_LENOVO_CMD_GET_STATUS_ACK:

                ucVdmDataObjectCnt_EXINT = 3;
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _ACER_VID)
    {
        EnumVdmAcerCmd enumVdmAcerCmd = (EnumVdmAcerCmd)enumVdmCmd;

        switch(enumVdmAcerCmd)
        {
            case _PD_VDM_ACER_CMD_DISCOVER_MODE_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            case _PD_VDM_ACER_CMD_ENTER_MODE_ACK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_ACER_CMD_GET_STATUS_ACK:

                // "Acer Get Status Ack" Data Object Cnt from User + VDM Header(1 VDO)
                ucVdmDataObjectCnt_EXINT = GET_PD_RX0_ACER_USER_VDM_CNT() + 1;

                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _HP_VID)
    {
        EnumTypeCVdmHpCmd enumVdmHpCmd = (EnumTypeCVdmHpCmd)enumVdmCmd;

        switch(enumVdmHpCmd)
        {
            case _PD_VDM_HP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_HP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_HP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_HP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_HP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_HP_CMD_SET_CONFIG_ACK:
            case _PD_VDM_HP_CMD_SET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_SET_DATA_ACK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_HP_CMD_DISCOVER_MODE_ACK:
            case _PD_VDM_HP_CMD_GET_CONFIG_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            case _PD_VDM_HP_CMD_GET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_GET_DATA_ACK:

                ucVdmDataObjectCnt_EXINT = GET_PD_RX0_HP_USER_VDM_CNT() + 2;
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _DELL_VID)
    {
        EnumTypeCVdmDellCmd enumVdmDellCmd = (EnumTypeCVdmDellCmd)enumVdmCmd;

        switch(enumVdmDellCmd)
        {
            case _PD_VDM_DELL_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DELL_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DELL_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DELL_CMD_0X12_ACK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_DELL_CMD_DISCOVER_MODE_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else
    {
        ucVdmDataObjectCnt_EXINT = 1;
    }

    return ucVdmDataObjectCnt_EXINT;
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ Interrupt
// Input Value  : enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmdType : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructVdmDataObj_EXINT0(EnumVdmCmd enumVdmCmd) using 1
{
    BYTE ucIndex = 0;

    if(GET_PD_RX0_VDM_SVID() == _PD_SID)
    {
        switch(enumVdmCmd)
        {
            case _PD_VDM_CMD_DISCOVER_ID_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] PD SID = 0xFF00
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos = b'000
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Discover ID Ack (0x41)
                g_pucDataObj_EXINT[3] = enumVdmCmd;

                // According to the PD Version, Set Product Type VDO Differently
                ScalerTypeCRx0PdSetProductTypeVDO_EXINT0();

                break;

            case _PD_VDM_CMD_DISCOVER_SVID_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] PD SID = 0xFF00
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Discover SVID Ack (0x42)
                g_pucDataObj_EXINT[3] = enumVdmCmd;

#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
                g_pucDataObj_EXINT[4 + ucIndex] = 0xFF;
                g_pucDataObj_EXINT[5 + ucIndex] = 0x01;
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
                g_pucDataObj_EXINT[4 + ucIndex] = 0x17;
                g_pucDataObj_EXINT[5 + ucIndex] = 0xEF;
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
                g_pucDataObj_EXINT[4 + ucIndex] = (BYTE)(_ACER_VID >> 8);   // _ACER_VID = 0x0502
                g_pucDataObj_EXINT[5 + ucIndex] = (BYTE)(_ACER_VID);
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
                g_pucDataObj_EXINT[4 + ucIndex] = (BYTE)(_HP_VID >> 8);      // _HP_VID = 0x03F0
                g_pucDataObj_EXINT[5 + ucIndex] = (BYTE)(_HP_VID);
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                g_pucDataObj_EXINT[4 + ucIndex] = (BYTE)(_DELL_VID >> 8);    // _DELL_VID = 0x413C
                g_pucDataObj_EXINT[5 + ucIndex] = (BYTE)(_DELL_VID);
                ucIndex = ucIndex + 2;
#endif

                if((_ALT_MODE_SUPPORT_CNT % 2) == 0)
                {
                    g_pucDataObj_EXINT[4 + ucIndex] = 0x00;
                    g_pucDataObj_EXINT[5 + ucIndex] = 0x00;
                    g_pucDataObj_EXINT[6 + ucIndex] = 0x00;
                    g_pucDataObj_EXINT[7 + ucIndex] = 0x00;
                }
                else
                {
                    g_pucDataObj_EXINT[4 + ucIndex] = 0x00;
                    g_pucDataObj_EXINT[5 + ucIndex] = 0x00;
                }

                break;

            case _PD_VDM_CMD_DISCOVER_ID_NAK:
            case _PD_VDM_CMD_DISCOVER_SVID_NAK:
            case _PD_VDM_CMD_DISCOVER_ID_BUSY:
            case _PD_VDM_CMD_DISCOVER_SVID_BUSY:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] SVID
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (GET_PD_RX0_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD
                g_pucDataObj_EXINT[3] = enumVdmCmd;

                break;

            default:

                break;
        }
    }
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
    else if(GET_PD_RX0_VDM_SVID() == _DP_SID)
    {
        EnumVdmDpCmd enumVdmDpCmd = _PD_VDM_DP_CMD_RESERVED;

        enumVdmDpCmd = (EnumVdmDpCmd)enumVdmCmd;

        switch(enumVdmDpCmd)
        {
            case _PD_VDM_DP_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucDataObj_EXINT[3] = enumVdmDpCmd;

                // -------- Data Obj 1 : DP Capability -----
                // [31:24] Reserved = 0x00
                g_pucDataObj_EXINT[4] = 0x00;

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _OFF)
                if(GET_TYPE_C_RX0_PORT_ROLE() != _TYPE_C_PORT_SNK_ONLY)
                {
                    if(GET_PD_RX0_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED)
                    {
                        if(GET_PD_RX0_PIN_ASSIGNMENT_CAP() == _TYPE_C_PIN_ASSIGNMENT_CAP_CDE)
                        {
                            SET_PD_RX0_PIN_ASSIGNMENT_CAP(_TYPE_C_PIN_ASSIGNMENT_CAP_CD);
                        }
                        else if(GET_PD_RX0_PIN_ASSIGNMENT_CAP() == _TYPE_C_PIN_ASSIGNMENT_CAP_CE)
                        {
                            SET_PD_RX0_PIN_ASSIGNMENT_CAP(_TYPE_C_PIN_ASSIGNMENT_CAP_C);
                        }
                    }
                    else
                    {
                        if(GET_PD_RX0_PIN_ASSIGNMENT_CAP() == _TYPE_C_PIN_ASSIGNMENT_CAP_CD)
                        {
                            SET_PD_RX0_PIN_ASSIGNMENT_CAP(_TYPE_C_PIN_ASSIGNMENT_CAP_CDE);
                        }
                        else if(GET_PD_RX0_PIN_ASSIGNMENT_CAP() == _TYPE_C_PIN_ASSIGNMENT_CAP_C)
                        {
                            SET_PD_RX0_PIN_ASSIGNMENT_CAP(_TYPE_C_PIN_ASSIGNMENT_CAP_CE);
                        }
                    }
                }
#endif

                // [23:16] DP_RX Pin Assignment Support
                g_pucDataObj_EXINT[5] = GET_PD_RX0_PIN_ASSIGNMENT_CAP();

                // [15:8] DP_TX Pin Assignment Support (Not Supprt As DP Tx)
                g_pucDataObj_EXINT[6] = 0x00;

                // [7] U2 Not Use = 0, [6] Receptable = 1, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(RX) = b'01
                g_pucDataObj_EXINT[7] = 0x45;

                break;

            case _PD_VDM_DP_CMD_DP_STATUS_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (GET_PD_RX0_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = DP_Status Ack (0x50)
                g_pucDataObj_EXINT[3] = enumVdmDpCmd;

                // -------- Data Obj 1 : DP Status ---------
                // [31:16] Reserved = 0x00
                g_pucDataObj_EXINT[4] = 0x00;
                g_pucDataObj_EXINT[5] = 0x00;

                // [15:9] Reserved, [8] HPD IRQ : No
                g_pucDataObj_EXINT[6] = 0x00;

                // [7] HPD State : LOW, [6] Exit DP : No, [5] USB Config = No, [4] Multi-Func = No,
                // [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
                g_pucDataObj_EXINT[7] = (0x0A) | (GET_PD_RX0_MULTI_FUNCTION() << 4);

                // If (HPD Count != 0) & (Not Attn Wait), Get Status from HPD Queue; else Use Current Status
                if((GET_PD_RX0_HPD_CNT() > 0) && (GET_PD_RX0_ATTENTION_WAIT() == _FALSE))
                {
                    // Check "HPD High/Low" and "HPD Status" from HPD Queue
                    if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) != _PD_HPD_LOW)
                    {
                        g_pucDataObj_EXINT[7] = g_pucDataObj_EXINT[7] | (_BIT7);

                        if(GET_PD_RX0_HPD_QUEUE(GET_PD_RX0_HPD_RPTR()) == _PD_HPD_IRQ)
                        {
                            g_pucDataObj_EXINT[6] = g_pucDataObj_EXINT[6] | (_BIT0);
                        }
                    }
                }
                else
                {
                    // "HPD Count = 0" or "During Attn Wait" (May Cause By DP Source Update Info During Alt Mode), Use Current HPD Status
                    g_pucDataObj_EXINT[7] = g_pucDataObj_EXINT[7] | (GET_PD_RX0_HPD_STATUS() << 7);
                }

                break;

            case _PD_VDM_DP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DP_CMD_DP_CONFIG_ACK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DP_CMD_DP_STATUS_NAK:
            case _PD_VDM_DP_CMD_DP_CONFIG_NAK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_BUSY:
            case _PD_VDM_DP_CMD_ENTER_MODE_BUSY:
            case _PD_VDM_DP_CMD_EXIT_MODE_BUSY:
            case _PD_VDM_DP_CMD_DP_STATUS_BUSY:
            case _PD_VDM_DP_CMD_DP_CONFIG_BUSY:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (GET_PD_RX0_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD
                g_pucDataObj_EXINT[3] = enumVdmDpCmd;

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _LENOVO_VID)
    {
        EnumVdmLenovoCmd enumVdmLenovoCmd = _PD_VDM_LENOVO_CMD_RESERVED;

        enumVdmLenovoCmd = (EnumVdmLenovoCmd)enumVdmCmd;

        switch(enumVdmLenovoCmd)
        {
            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucDataObj_EXINT[3] = enumVdmLenovoCmd;

                // -------- Data Obj 1 : Lenovo Discover Mode Response -----
                g_pucDataObj_EXINT[4] = 0x00;
                g_pucDataObj_EXINT[5] = 0x00;
                g_pucDataObj_EXINT[6] = 0x00;
                g_pucDataObj_EXINT[7] = 0x01;

                break;

            case _PD_VDM_LENOVO_CMD_GET_STATUS_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Get Status Ack (0x50)
                g_pucDataObj_EXINT[3] = enumVdmLenovoCmd;

                // -------- Data Obj 1 : Lenovo Get Status Response VDO1-----
                // [31:28] Rsv., [27] Docking Power Button Break, [26] Docking Power Button Make,
                // [25] Wol Request, [24] Event
                g_pucDataObj_EXINT[4] = GET_PD_RX0_LENOVO_DOCK_EVENT();

                // [23:20] Rsv., [19] System Acknowledge Power Button Break, [18] System Acknowledge Power Button Make,
                // [17] Wol Request, [16] Event Acknowledge
                g_pucDataObj_EXINT[5] = (GET_PD_RX0_LENOVO_SYS_ACKNOWLEDGE() & 0xFE);

                // [15:13] Rsv., [12] System Power Mode, [11:9] System State, [8] Event
                g_pucDataObj_EXINT[6] = GET_PD_RX0_LENOVO_SYS_EVENT();

                // [7:5] Rsv., [4] Docking Acknowledge System Power Mode, [3:1] Docking Acknowledge System State, [0] Event Acknowledge
                g_pucDataObj_EXINT[7] = GET_PD_RX0_LENOVO_SYS_EVENT();

                // -------- Data Obj 2 : Lenovo Get Status Response VDO2-----
                // [31:28] FW Ver. = 0, [27:24] Rsv.
                g_pucDataObj_EXINT[8] = 0x00;

                // Power Source
                // [23] Supplier Info = 0, [22:21] Src Type : Type-C Adapter, [20] Src Quality = Good, [19:16] Rating = Unknown AC adapter detected
                g_pucDataObj_EXINT[9] = 0x30;

                // Function Capability
                // [15] Power Button Supported, [14] Wol Supported, [13] Wol Supported,
                // [12] MAC address pass through not Supported, [11] Change charging ability not Supported, [11:8] Rsv.
                g_pucDataObj_EXINT[10] = 0xC0;

                // [7:0] Reserved = 0x00
                g_pucDataObj_EXINT[11] = 0x00;

                break;

            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_ACK:
            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_NAK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD
                g_pucDataObj_EXINT[3] = enumVdmLenovoCmd;

                break;

            case _PD_VDM_LENOVO_CMD_ENTER_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_ENTER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_GET_STATUS_NAK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
                g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (GET_PD_RX0_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD
                g_pucDataObj_EXINT[3] = enumVdmLenovoCmd;

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _ACER_VID)
    {
        EnumVdmAcerCmd enumVdmAcerCmd = (EnumVdmAcerCmd)enumVdmCmd;

        switch(enumVdmAcerCmd)
        {
            case _PD_VDM_ACER_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] ACER VID = 0x0502
                g_pucDataObj_EXINT[0] = (BYTE)(_ACER_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_ACER_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver = 2b'01, [12:11] Rsv., [10:8] Rsv.
                g_pucDataObj_EXINT[2] = (_BIT7) | (_BIT5);

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucDataObj_EXINT[3] = enumVdmCmd;

                // -------- Data Obj 1 : Acer Discover Mode Response -----
                g_pucDataObj_EXINT[4] = 0x00;
                g_pucDataObj_EXINT[5] = 0x00;
                g_pucDataObj_EXINT[6] = 0x00;
                g_pucDataObj_EXINT[7] = 0x00;

                break;

            case _PD_VDM_ACER_CMD_ENTER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] ACER VID = 0x0502
                g_pucDataObj_EXINT[0] = (BYTE)(_ACER_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_ACER_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver = 2b'01, [12:11] Rsv., [10:8] Rsv.
                g_pucDataObj_EXINT[2] = (_BIT7) | (_BIT5);

                // [7:0] VDM CMD = Enter Mode Ack
                g_pucDataObj_EXINT[3] = enumVdmCmd;

                break;

            case _PD_VDM_ACER_CMD_GET_STATUS_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] ACER VID = 0x0502
                g_pucDataObj_EXINT[0] = (BYTE)(_ACER_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_ACER_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver = 2b'01, [12:11] Rsv., [10:8] Rsv.
                g_pucDataObj_EXINT[2] = (_BIT7) | (_BIT5);

                // [7:0] VDM CMD = Get Status Ack (0x56)
                g_pucDataObj_EXINT[3] = enumVdmCmd;

                // Construct Acer "Get Status Ack" Data Object(0~6)
                for(pData_EXINT[0] = 0; pData_EXINT[0] < (GET_PD_RX0_ACER_USER_VDM_CNT() * 4); pData_EXINT[0]++)
                {
                    g_pucDataObj_EXINT[pData_EXINT[0] + 4] = GET_PD_RX0_ACER_USER_VDM_DATA(pData_EXINT[0]);
                }

                break;

            default:
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _HP_VID)
    {
        EnumTypeCVdmHpCmd enumVdmHpCmd = (EnumTypeCVdmHpCmd)enumVdmCmd;

        switch(enumVdmHpCmd)
        {
            case _PD_VDM_HP_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucDataObj_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucDataObj_EXINT[3] = enumVdmHpCmd;

                // -------- Data Obj 1 : Hp Discover Mode Response -----
                g_pucDataObj_EXINT[4] = 0x60;
                g_pucDataObj_EXINT[5] = 0x00;
                g_pucDataObj_EXINT[6] = 0x00;
                g_pucDataObj_EXINT[7] = 0x00;

                break;

            case _PD_VDM_HP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_HP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_HP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_HP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_HP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_HP_CMD_SET_CONFIG_ACK:
            case _PD_VDM_HP_CMD_SET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_SET_DATA_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucDataObj_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (GET_PD_RX0_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD
                g_pucDataObj_EXINT[3] = enumVdmHpCmd;

                break;

            case _PD_VDM_HP_CMD_GET_CONFIG_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucDataObj_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (_BIT0);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Get_config Ack (0x51)
                g_pucDataObj_EXINT[3] = enumVdmHpCmd;

                // -------- Data Obj 1 : Hp VDO -----
                // [31:27] Rsv., [26:20] I2C Address
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | ((GET_PD_RX0_HP_I2C_ADDR() >> 4) & (_BIT2 | _BIT1 | _BIT0));
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | ((GET_PD_RX0_HP_I2C_ADDR() << 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                // [19:18] Rsv., [17:0] AM_addr
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (GET_PD_RX0_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
                g_pucDataObj_EXINT[6] = GET_PD_RX0_HP_OWN_AM_ADDR_M();
                g_pucDataObj_EXINT[7] = GET_PD_RX0_HP_OWN_AM_ADDR_L();

                break;

            case _PD_VDM_HP_CMD_GET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_GET_DATA_ACK:   // Multi-aprt Need to Develop Later

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucDataObj_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (_BIT0);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Get_vwire Ack (0x53). Get_data Ack (0x55)
                g_pucDataObj_EXINT[3] = enumVdmHpCmd;

                // -------- Data Obj 1 : Hp Sub Header -----
                // [31:23] Rsv., [22:20] VDO_CNT
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | ((GET_PD_RX0_HP_USER_VDM_CNT() << 4) & (_BIT6 | _BIT5 | _BIT4));

                // [19:18] Rsv., [17:0] AM_addr
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (GET_PD_RX0_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
                g_pucDataObj_EXINT[6] = GET_PD_RX0_HP_OWN_AM_ADDR_M();
                g_pucDataObj_EXINT[7] = GET_PD_RX0_HP_OWN_AM_ADDR_L();

                // -------- Data Obj 2 : Hp V-wire VDO1 -----
                // [31:16] Data, [15:8] Index, [7:4] Rsv., [3:0] Operation
                for(pData_EXINT[0] = 0; pData_EXINT[0] < (GET_PD_RX0_HP_USER_VDM_CNT() * 4); pData_EXINT[0]++)
                {
                    g_pucDataObj_EXINT[pData_EXINT[0] + 8] = GET_PD_RX0_HP_USER_VDM_DATA(pData_EXINT[0]);
                }

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else if(GET_PD_RX0_VDM_SVID() == _DELL_VID)
    {
        EnumTypeCVdmDellCmd enumVdmDellCmd = (EnumTypeCVdmDellCmd)enumVdmCmd;

        switch(enumVdmDellCmd)
        {
            case _PD_VDM_DELL_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DELL VID = 0x413C
                g_pucDataObj_EXINT[0] = (BYTE)(_DELL_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_DELL_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucDataObj_EXINT[3] = enumVdmDellCmd;

                // -------- Data Obj 1 : Dell Discover Mode Response -----
                g_pucDataObj_EXINT[4] = 0x00;
                g_pucDataObj_EXINT[5] = 0x00;
                g_pucDataObj_EXINT[6] = 0x00;
                g_pucDataObj_EXINT[7] = 0x01;

                break;

            case _PD_VDM_DELL_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DELL_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DELL_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DELL_CMD_0X12_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DELL VID = 0x413C
                g_pucDataObj_EXINT[0] = (BYTE)(_DELL_VID >> 8);
                g_pucDataObj_EXINT[1] = (BYTE)_DELL_VID;

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucDataObj_EXINT[2] = (_BIT7) | (GET_PD_RX0_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
                }

                // [7:0] VDM CMD
                g_pucDataObj_EXINT[3] = enumVdmDellCmd;

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else
    {
        // -------- Data Obj 0 : VDM Header --------
        // [31:16] SVID
        g_pucDataObj_EXINT[0] = GET_PD_RX0_VDM_SVID_H();
        g_pucDataObj_EXINT[1] = GET_PD_RX0_VDM_SVID_L();

        // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
        g_pucDataObj_EXINT[2] = (_BIT7) | (GET_PD_RX0_VDM_OBJ_POS());

        // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
        if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
        {
            g_pucDataObj_EXINT[2] = g_pucDataObj_EXINT[2] | (_BIT5);
        }

        // [7:0] VDM CMD
        g_pucDataObj_EXINT[3] = enumVdmCmd;
    }
}

//--------------------------------------------------
// Description  : According to the PD Version, Set Product Type VDO Differently
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetProductTypeVDO_EXINT0(void) using 1
{
    BYTE ucIndex = 0;

    switch(GET_PD_RX0_SPEC_VER())
    {
        case _PD_VERSION_3_0:

            // PD Version = 3.0, Products with USB Hub IC, Product Type UFP choose Hub , Product Type DFP choose Undefined;
            // Products without USB Hub IC, Product Type UFP choose Peripheral, Product Type DFP choose Undefined.

            // -------- Data Obj 1 : ID Header ---------
            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // |Host|Dev.|      UFP     |Mode|   DFP   |
#if((_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_HOST_ONLY) || (_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_HOST_DEVICE))
            g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT7);
#endif

#if((_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_DEVICE_ONLY) || (_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_HOST_DEVICE))
            g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT6);
#endif
            // UFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Peripheral
            if(GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] & (~(_BIT5 | _BIT4 | _BIT3));
            }
            else if(GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT3);
            }
            else if(GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT4);
            }

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT2);
#endif

            // [25:23] DFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Host/ 3b'011 Power Brick
            if(GET_PD_RX0_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] & (~(_BIT1 | _BIT0));
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] & (~(_BIT7));
            }
            else if(GET_PD_RX0_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_HUB)
            {
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (_BIT7);
            }
            else if(GET_PD_RX0_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_HOST)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT0);
            }
            else if(GET_PD_RX0_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_BRICK)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT0);
                g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (_BIT7);
            }

            // [22:21] = Connector Type: USB Type-C Receptacle = 2b'10
            g_pucDataObj_EXINT[5] = g_pucDataObj_EXINT[5] | (_BIT6);

            // [15:0] = USB Vender ID 0x0BDA (RealTek)
            g_pucDataObj_EXINT[6] = _USB_VENDOR_ID_H;
            g_pucDataObj_EXINT[7] = _USB_VENDOR_ID_L;

            // -------- Data Obj 2 : Cert State (Reserved)
            g_pucDataObj_EXINT[8] = 0x00;
            g_pucDataObj_EXINT[9] = 0x00;
            g_pucDataObj_EXINT[10] = 0x00;
            g_pucDataObj_EXINT[11] = 0x00;

            // -------- Data Obj 3 : Product -----------
            // [31:16] bcd Device = 0x0300, [15:0] Product ID = _USB_PRODUCT_ID_H / _USB_PRODUCT_ID_L
            g_pucDataObj_EXINT[12] = _USB_PRODUCT_ID_H;
            g_pucDataObj_EXINT[13] = _USB_PRODUCT_ID_L;
            g_pucDataObj_EXINT[14] = 0x03;
            g_pucDataObj_EXINT[15] = 0x00;

            // If (UFP Product Type != Undefined) && (DFP Product Type == Undefined), Product Type VDO [UFP | Pad | Pad].
            // If (UFP Product Type == Undefined) && (DFP Product Type != Undefined), Product Type VDO [DFP | Pad | Pad].
            // If (UFP Product Type != Undefined) && (DFP Product Type != Undefined), Product Type VDO [UFP | Pad | DFP].
            ucIndex = 15;

            if((GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB) || (GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL))
            {
                // -------- Data Obj 4 : UFP VDO ---------
                // [31:29] UFP VDO Ver. : Ver. 1.2 = 3b'010
                g_pucDataObj_EXINT[ucIndex + 1] = g_pucDataObj_EXINT[ucIndex + 1] | (_BIT6);

                // [27:24] Device Cap.
#if((_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN1) || (_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN2))
                // USB3.2 = 4b'0100
                g_pucDataObj_EXINT[ucIndex + 1] = g_pucDataObj_EXINT[ucIndex + 1] | (_BIT2);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_BILLBOARD_ONLY)
                // USB2.0 (Billboard only) = 4b'0010
                g_pucDataObj_EXINT[ucIndex + 1] = g_pucDataObj_EXINT[ucIndex + 1] | (_BIT1);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_2)
                // USB2.0 = 4b'0001
                g_pucDataObj_EXINT[ucIndex + 1] = g_pucDataObj_EXINT[ucIndex + 1] | (_BIT0);
#endif

                // [23:22] Connector Type : USB Type-C Receptacle = 2b'10, [21:16] Reserved = 0x00
                g_pucDataObj_EXINT[ucIndex + 2] = g_pucDataObj_EXINT[ucIndex + 2] | (_BIT7);

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
                // [15:11] Reserved = 0x00, [10:8] Vconn Power
                g_pucDataObj_EXINT[ucIndex + 3] = g_pucDataObj_EXINT[ucIndex + 3] | (_VCONN_POW);

#if(_VCONN_REQUIRE == _TRUE)
                // [7] Vconn Required
                g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (_BIT7);
#endif

                if(GET_PD_RX0_SNK_CAP_CUR(0) != 0x00)
                {
                    // [6] Vbus Required = TRUE when 1st 5V Sink Cap Need More than 0mA
                    g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (_BIT6);
                }

                // [5:3] Alternate Modes;
#if(_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE)
                // [5] Supports Alternate Modes that do not Reconfigure the Signals on the [USB Type-C 2.0] Connector
                g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (_BIT5);
#endif
#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
                // [4] Supports Alternate Modes that Reconfigure the Signals on the [USB Type-C 2.0] Connector
                g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (_BIT4);
#endif
                // [3] Supports TBT3 Alternate Mode (Need to Add in the Future)
#endif

                // [2:0] USB Highest Speed
#if(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN2)
                // USB3.2 Gen2 = 3b'010
                g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (_BIT1);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN1)
                // USB3.2 Gen1 = 3b'001
                g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (_BIT0);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_2)
                // USB2.0 = 3b'000
                g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (0x00);
#endif
                ucIndex = ucIndex + 8;
            }

            if(GET_PD_RX0_DFP_PRODUCT_TYPE() != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED)
            {
                // -------- Data Obj 6 : DFP VDO ---------
                // [31:29] DFP VDO Ver. : Ver. 1.1 = 3b'001
                g_pucDataObj_EXINT[ucIndex + 1] = g_pucDataObj_EXINT[ucIndex + 1] | (_BIT5);

                // [26:24] Host Cap.
#if((_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN1) || (_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN2))
                // USB3.2 = 3b'010
                g_pucDataObj_EXINT[ucIndex + 1] = g_pucDataObj_EXINT[ucIndex + 1] | (_BIT1);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_2)
                // USB2.0 = 3b'001
                g_pucDataObj_EXINT[ucIndex + 1] = g_pucDataObj_EXINT[ucIndex + 1] | (_BIT0);
#endif

                // [23:22] Connector Type: USB Type-C Receptacle = 2b'10
                g_pucDataObj_EXINT[ucIndex + 2] = g_pucDataObj_EXINT[ucIndex + 2] | (_BIT7);

                // [4:0] Port Number: Port 0 = 5b'00001
                g_pucDataObj_EXINT[ucIndex + 4] = g_pucDataObj_EXINT[ucIndex + 4] | (_BIT0);
            }
            break;

        case _PD_VERSION_2_0:
        default:

            // PD Version = 2.0, Products with USB Hub IC, Product Type UFP choose Hub;
            // Products without USB Hub IC, Product Type UFP choose Peripheral.

            // -------- Data Obj 1 : ID Header ---------
            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // |Host|Dev.|      UFP     |Mode|   DFP   |
#if((_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_HOST_ONLY) || (_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_HOST_DEVICE))
            g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT7);
#endif

#if((_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_DEVICE_ONLY) || (_TYPE_C_EMB_USB_ROLE == _TYPE_C_USB_HOST_DEVICE))
            g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT6);
#endif

#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            // For the PD2.0 version, Discover_ID_ACK Responds to AMA
            // (UFP Product Type = AMA) does not Meet the Latest Standard. This setting is for Compatibility.
            // UFP Product Type = 3b'101 (AMA)
            g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT5 | _BIT3);
#else
            // UFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Peripheral
            if(GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] & (~(_BIT5 | _BIT4 | _BIT3));
            }
            else if(GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT3);
            }
            else if(GET_PD_RX0_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
            {
                g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT4);
            }
#endif

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            g_pucDataObj_EXINT[4] = g_pucDataObj_EXINT[4] | (_BIT2);
#endif

            // [15:0] = USB Vender ID 0x0BDA (RealTek)
            g_pucDataObj_EXINT[6] = _USB_VENDOR_ID_H;
            g_pucDataObj_EXINT[7] = _USB_VENDOR_ID_L;

            // -------- Data Obj 2 : Cert State (Reserved)
            g_pucDataObj_EXINT[8] = 0x00;
            g_pucDataObj_EXINT[9] = 0x00;
            g_pucDataObj_EXINT[10] = 0x00;
            g_pucDataObj_EXINT[11] = 0x00;

            // -------- Data Obj 3 : Product -----------
            // [31:16] bcd Device = 0x0300, [15:0] Product ID = _USB_PRODUCT_ID_H / _USB_PRODUCT_ID_L
            g_pucDataObj_EXINT[12] = _USB_PRODUCT_ID_H;
            g_pucDataObj_EXINT[13] = _USB_PRODUCT_ID_L;
            g_pucDataObj_EXINT[14] = 0x03;
            g_pucDataObj_EXINT[15] = 0x00;

#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            // -------- Data Obj 4 : Alt. Mode ---------
            // [31:28] HW Ver. = 0, [27:24] FW Ver. = 0
            g_pucDataObj_EXINT[16] = g_pucDataObj_EXINT[16] | (_PD_HW_VERSION << 4);
            g_pucDataObj_EXINT[16] = g_pucDataObj_EXINT[16] | (_PD_FW_VERSION);

            // [23:16] Reserved = 0x00
            g_pucDataObj_EXINT[17] = 0x00;

            // [15:8] Reserved = 0x00
            g_pucDataObj_EXINT[18] = 0x00;

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
            // [7:5] Vconn Power
            g_pucDataObj_EXINT[19] = g_pucDataObj_EXINT[19] | (_VCONN_POW << 5);

#if(_VCONN_REQUIRE == _TRUE)
            // [4] Vconn Required
            g_pucDataObj_EXINT[19] = g_pucDataObj_EXINT[19] | (_BIT4);
#endif

            if(GET_PD_RX0_SNK_CAP_CUR(0) != 0x00)
            {
                // [3] Vbus Required = TRUE when 1st 5V Sink Cap Need More than 0mA
                g_pucDataObj_EXINT[19] = g_pucDataObj_EXINT[19] | (_BIT3);
            }
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

            // [2:0] USB Highest Speed
#if(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_BILLBOARD_ONLY)
            // Billboard only = 3b'011
            g_pucDataObj_EXINT[19] = g_pucDataObj_EXINT[19] | (_BIT1 | _BIT0);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN2)
            // USB3.2 Gen2 = 3b'010
            g_pucDataObj_EXINT[19] = g_pucDataObj_EXINT[19] | (_BIT1);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_3_GEN1)
            // USB3.2 Gen1 = 3b'001
            g_pucDataObj_EXINT[19] = g_pucDataObj_EXINT[19] | (_BIT0);
#elif(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_2)
            // USB2.0 = 3b'000
            g_pucDataObj_EXINT[19] = g_pucDataObj_EXINT[19] | (0x00);
#endif // End of #if(_TYPE_C_EMB_USB_SPEED == _TYPE_C_USB_BILLBOARD_ONLY)
#endif // End of #if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            break;
    }
}

//--------------------------------------------------
// Description  : Send Power Delivery Message @ WD Timer
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT / _CABLE_RESET_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmd : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendMsg_WDINT(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd) using 3
{
    // 1. Clear Flags
    CLR_PD_RX0_TRANSMIT_RESULT_EXINT();

    // 2. Construct Msg.
    ScalerTypeCRx0PdConstructMsg_WDINT(enumPacketType, enumPdCmd, enumVdmCmd);

    // 3. Send Msg. (Interrupt Does Not Check Overwrite and Disable Rcv Msg.)
    // [0x65DC] Clear IRQs
    ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
    ScalerSetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

    // [0x65DA] Start Transmit ([1] = 0, Wait For GoodCRC Response After Transmission)
    ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

    // [0x65E5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
}

//--------------------------------------------------
// Description  : Send Power Delivery Message @ WD Timer
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT / _CABLE_RESET_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmd : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructMsg_WDINT(EnumPDPacketType enumPacketType, EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd) using 3
{
    BYTE ucExtendedBit_WDINT = 0;
    BYTE ucDataObjectCnt_WDINT = 0;

    // 1. [0x65E9-EA] Set Up Number of Data Objects(Data Blocks) if Needed
    switch(enumPdCmd)
    {
        // Control Message Has No Data Object
        case _PD_CMD_RSV:
        case _PD_CMD_GOODCRC:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PING:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_GET_SRC_CAP:
        case _PD_CMD_GET_SNK_CAP:
        case _PD_CMD_DR_SWAP:
        case _PD_CMD_PR_SWAP:
        case _PD_CMD_VCONN_SWAP:
        case _PD_CMD_WAIT:
        case _PD_CMD_SOFT_RESET:
#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_NOT_SUPPORT:
        case _PD_CMD_GET_SRC_CAP_EXT:
        case _PD_CMD_GET_STATUS:
        case _PD_CMD_FR_SWAP:
        case _PD_CMD_GET_PPS_STATUS:
        case _PD_CMD_GET_COUNTRY_CODES:
#endif
            ucExtendedBit_WDINT = 0;
            ucDataObjectCnt_WDINT = 0;

            break;

        case _PD_CMD_SRC_CAP:

            ucExtendedBit_WDINT = 0;
            ucDataObjectCnt_WDINT = GET_PD_RX0_SRC_PDO_CNT();

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_2_0)
#endif
            {
                for(pData_EXINT[0] = GET_PD_RX0_SRC_PDO_CNT() - 1; pData_EXINT[0] > 0; pData_EXINT[0]--)
                {
                    if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ucDataObjectCnt_WDINT --;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_ALERT:

            ucDataObjectCnt_WDINT = 1;

            break;
#endif

        default:

            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt_WDINT != 0)
    {
        ScalerTypeCRx0PdConstructDataObj_WDINT(enumPdCmd, enumVdmCmd);
    }

    // 3. Start to Fill Packet Type, Msg. Header & Data Object
    // [0x65E0] Select Transmission Mode [7:6] b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
    ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

    // [0x65E0] Set Packet Type [5:3]
    ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

    // 4. [0x65E5] Fill in Msg. Header0
    // [7]   Msg. Header[15]     : Extended Field
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT7, (ucExtendedBit_WDINT << 7));

    // [6:4] Msg. Header[14:12]  : Number of Data Object
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT6 | _BIT5 | _BIT4), ((ucDataObjectCnt_WDINT << 4) & (_BIT6 | _BIT5 | _BIT4)));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // [3]   Msg. Header[8]  : Power Role
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_PD_RX0_POWER_ROLE() << 3);

        // [2:1] Msg. Header[7:6]  : Spec Version
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_PD_RX0_SPEC_VER() << 1);

        // [0]   Msg. Header[5]  : Data Role
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_PD_RX0_DATA_ROLE());
    }
    else
    {
        // [3]   Msg. Header[8]  : Cable Plug = Device (1)
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, ((BYTE)_PD_DEVICE << 3));

        // [2:1] Msg. Header[7:6]  : Cable Spec Version
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_PD_RX0_CBL_SPEC_VER() << 1);

        // [0]   Msg. Header[5]  : Data Role
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
    }

    // [0x65E6] Fill in Msg. Header1
    // [4:0]  Msg. Header[4:0]    : Command Type = enumCtrlMsg
    ScalerSetBit_EXINT(P65_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

    // Clear Tx FIFO Addr.
    ScalerSetByte_EXINT(P65_E9_TX_FIFO_ADDR, 0x00);

    // Fill Data Object into Tx FIFO
    for(pData_EXINT[0] = 0; pData_EXINT[0] < (ucDataObjectCnt_WDINT * 4); pData_EXINT[0]++)
    {
        ScalerSetByte_EXINT(P65_EA_TX_FIFO_DATA, g_pucDataObj_EXINT[pData_EXINT[0]]);
    }
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ WD Timer
// Input Value  : enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REJECT / _PD_CMD_PR_SWAP ...
//                enumVdmCmdType : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructDataObj_WDINT(EnumPDCmd enumPdCmd, EnumVdmCmd enumVdmCmd) using 3
{
    enumPdCmd = enumPdCmd;
    enumVdmCmd = enumVdmCmd;

    // Clear ucDataObj_EXINT
    for(pData_EXINT[0] = 0; pData_EXINT[0] < _MAX_DATA_OBJ_CNT * 4; pData_EXINT[0] ++)
    {
        g_pucDataObj_EXINT[pData_EXINT[0]] = 0;
    }

    // Process Data Object Fields For FIFO Fill
    switch(enumPdCmd)
    {
        case _PD_CMD_SRC_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
#if((_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_RX0_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT5);
            }
#endif

#if(_USB_SUSPEND == _FALSE)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT4);
#endif
            if(GET_PD_RX0_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT3);
            }

#if(_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);
#endif

#if((_DFP_SWAP_TO_UFP == _TRUE) || (_UFP_SWAP_TO_DFP == _TRUE))
            g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT0);
            }
#endif

            for(pData_EXINT[1] = 0; pData_EXINT[1] < GET_PD_RX0_SRC_PDO_CNT(); pData_EXINT[1] ++)
            {
                if(GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1]) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | (((BYTE)GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1])) << 6);

                    // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
                    // |  Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)(GET_PD_RX0_SRC_CAP_PEAK(pData_EXINT[1]) << 4) & (_BIT5 | _BIT4));
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) && (GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1]) > GET_PD_RX0_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)(GET_PD_RX0_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] | ((BYTE)GET_PD_RX0_CBL_MAX_CUR());
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] | ((BYTE)(GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1]) >> 8) & (_BIT1 | _BIT0));
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] | ((BYTE)(GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1])));
                    }
                }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                else if((GET_PD_RX0_SPEC_VER() == _PD_VERSION_3_0) && (GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1]) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:30] PDO Type = 2'b11 (Programmabl Power Supply)
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | (((BYTE)GET_PD_RX0_SRC_PDO_TYPE(pData_EXINT[1])) << 6);

                    // [24:17] Max Voltage in 100mV
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4)] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 10) >> 7) & (_BIT0));
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] = g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 1] | ((BYTE)((GET_PD_RX0_SRC_CAP_VOL_MAX(pData_EXINT[1]) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 2] = (BYTE)(GET_PD_RX0_SRC_CAP_VOL_MIN(pData_EXINT[1]) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) && (((GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1])) * 5) > GET_PD_RX0_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = (((BYTE)(GET_PD_RX0_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucDataObj_EXINT[(pData_EXINT[1] * 4) + 3] = (((BYTE)GET_PD_RX0_SRC_CAP_CUR(pData_EXINT[1])) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OVP) == _PD_PORT_CTRL_EVENT_POWER_OVP))
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT6);
            }
            if(((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP) || ((GET_PD_RX0_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OCP) == _PD_PORT_CTRL_EVENT_POWER_OCP))
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);
            }
#else
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT6);
            }
            if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucDataObj_EXINT[0] = g_pucDataObj_EXINT[0] | (_BIT2);
            }
#endif

            // Reserved for Future Usage.
            // [31] Rsv., [29] Source Input Change Event, [28] Operating Condition Change Event, [27] OTP Event, [25] Battery Status Change Event, [24] Rsv., [23:20] Fixed Batteries, [19:16] Hot Swappepable Batteries, [15:0] Rsv.

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Send Soft Reset Message
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendSoftRst_EXINT0(EnumPDPacketType enumPacketType) using 1
{
    // 1. Clear Flags & Reset PRL Layer [0x6503]
    CLR_PD_RX0_TRANSMIT_RESULT();
    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT0, 0x00);

    // 2. Construct Msg.
    ScalerTypeCRx0PdConstructSoftReset_EXINT0(enumPacketType);

    // 3. [0x65DC] Clear IRQs
    ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // 4. Enable PRL Layer & Release Message ID Reset [0x6503/E4]
    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
    ScalerSetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

    // 5. Start Transmit [0x65DA]
    ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

    // [0x65E5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
    // Lecroy [COMMON.CHECK.PD.3 Check GoodCRC] TEST.PD.PROT.SRC.6_Rev2Src
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));

    // 6. Transit State
    SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
    SET_PD_RX0_FW_STATE(_PD_INT_SEND_SOFTRESET);
}

//--------------------------------------------------
// Description  : Construct Soft Reset Msg.
// Input Value  : enumPacketType : _SOP_PKT / _SOP_P_PKT / _SOP_PP_PKT / _HARD_RESET_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdConstructSoftReset_EXINT0(EnumPDPacketType enumPacketType) using 1
{
    // 1. [0x65E0] Set Transmit Type : b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
    ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

    // 2. [0x65E0] Set Packet Type [5:3]
    ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

    // 3. [0x65E5] Fill in Msg. Header0
    // [7]   Msg. Header[15]     : Extended Field = 0
    // [6:4] Msg. Header[14:12]  : Number of Data Object = 0
    ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [3] Msg. Header[8]  : Power Role
    // [0] Msg. Header[5]  : Data Role
    if(enumPacketType == _PD_SOP_PKT)
    {
        // [3] Power Role / [2:1] Spec Version / [0] Data Role
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_PD_RX0_POWER_ROLE() << 3);
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2, _BIT1), GET_PD_RX0_SPEC_VER() << 1);
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_PD_RX0_DATA_ROLE());

        // Reset Message ID [0x65E4]
        ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~_BIT2, 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, (BYTE)_PD_DEVICE << 3);
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2, _BIT1), GET_PD_RX0_CBL_SPEC_VER() << 1);
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);

        if(enumPacketType == _PD_SOP_P_PKT)
        {
            // Reset Message ID [0x65E4]
            ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~_BIT1, 0x00);
        }
        else if(enumPacketType == _PD_SOP_PP_PKT)
        {
            // Reset Message ID [0x65E4]
            ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~_BIT0, 0x00);
        }
    }

    // [0x65E6] Fill in Msg. Header1
    // [4:0]  Msg. Header[4:0] : Command Type = b'0_1101
    ScalerSetBit_EXINT(P65_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
}

//--------------------------------------------------
// Description  : Initiate Hard Reset When Error Happens
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendHardRst_EXINT0(void) using 1
{
    if(GET_DP_RX0_HARD_RST_CNT() <= _MAX_HARD_RST_CNT)
    {
        // 1. [0x65E0] Select Transmission Mode [7:6] : b'01 = Preamble + SOP
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), _BIT6);

        // 2. [0x65E0] Set Packet Type [5:3] : b'011 = HARD_RESET
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

        // 3. [0x65DC] Clear IRQs
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // 4. [0x65DA] Start Transmit
        ADD_DP_RX0_HARD_RST_CNT();
        ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));

        // 5. Process Hard Reset
        ScalerTypeCRx0PdProcHardRst_EXINT0();
    }
    else
    {
        // Do Type-C Error Recovery
        SET_TYPE_C_ERROR_RECOVERY();
    }
}

//--------------------------------------------------
// Description  : Initiate Hard Reset When Error Happens
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSendHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime) using 3
{
    if(GET_DP_RX0_HARD_RST_CNT() <= _MAX_HARD_RST_CNT)
    {
        // 1. [0x65E0] Select Transmission Mode [7:6] : b'01 = Preamble + SOP
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), _BIT6);

        // 2. [0x65E0] Set Packet Type [5:3] : b'011 = HARD_RESET
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

        // 3. [0x65DC] Clear IRQs
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // 4. [0x65DA] Start Transmit
        ADD_DP_RX0_HARD_RST_CNT();
        ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));

        // 5. Process Hard Reset
        ScalerTypeCRx0PdProcHardRst_WDINT(pucActiveWDID, pucActiveWDTime);
    }
    else
    {
        // Do Type-C Error Recovery
        SET_TYPE_C_ERROR_RECOVERY();
    }
}

//--------------------------------------------------
// Description  : Process Hard Reset When Hard Reset Sent/Rcv.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdProcHardRst_EXINT0(void)  using 1
{
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        // Clear Hard Reset Turn Off Power Flag (Set When Power Already Turned Off)
        CLR_PD_RX0_HRST_PWR_OFF();

        // Source can Start Changing Power After tSrcTransition = 25-35 ms
        ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER);
    }
    else
    {
        // 1. Turn Off Power Draw
        ScalerTypeCPowerRx0VbusControl_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // 2. Turn Off Type-C Unattach Vbus Detection
        ScalerTypeCRx0CcVbusDetCtrl_EXINT0(_DISABLE);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC)
    {
        ScalerTypeCRx0CcVconnControl_EXINT0(_OFF);
    }

    // [0x6502] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit_EXINT(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6543] Clear and Disable Hard Reset IRQ
    ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT);

    // State Transition
    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_PD_RX0_FW_STATE(_PD_HARDRESET);
}

//--------------------------------------------------
// Description  : Process Hard Reset When Hard Reset Sent/Rcv.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdProcHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime) using 3
{
    if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    {
        // Clear Hard Reset Turn Off Power Flag (Set When Power Already Turned Off)
        CLR_PD_RX0_HRST_PWR_OFF();

        *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER;
        *pucActiveWDTime = _SRC_ADJUST_POWER_TIMER;
    }
    else
    {
        // 1. Turn Off Power Draw
        ScalerTypeCPowerRx0VbusControl_WDINT(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // 2. Turn Off Type-C Unattach Vbus Detection
        ScalerTypeCRx0CcVbusDetCtrl_WDINT(_DISABLE);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_PD_RX0_VCONN_ROLE() == _PD_VCONN_SRC)
    {
        ScalerTypeCRx0CcVconnControl_WDINT(_OFF);
    }

    // [0x6502] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit_EXINT(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6543] Clear and Disable Hard Reset IRQ
    ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // State Transition
    SET_PD_RX0_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_PD_RX0_FW_STATE(_PD_HARDRESET);
}

//--------------------------------------------------
// Description  : Filter Un-wanted Msg. Before Selecting FIFO to Process
// Input Value  : FifoUsed : BIT2 (FIFO_0) / BIT1 (FIFO_1) / BIT0 (FIFO_2)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRxInvlidPktFilter_EXINT0(void) using 1
{
    // Check FIFO0 Status (Drop Msg if : Invalid Pkt, CRC Err, Abn Msg, Msg ID Err, CRC Resp Fail)
    if(ScalerGetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, _BIT2) == _BIT2)
    {
        if((ScalerGetByte_EXINT(P65_51_RX_FIFO0_RCV_ERR_INT) & (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
        }
    }

    // Check FIFO1 Status (Drop Msg if : Invalid Pkt, CRC Err, Abn Msg, Msg ID Err, CRC Resp Fail)
    if(ScalerGetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, _BIT1) == _BIT1)
    {
        if((ScalerGetByte_EXINT(P65_71_RX_FIFO1_RCV_ERR_INT) & (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
        }
    }

    // Check FIFO2 Status (Drop Msg if : Invalid Pkt, CRC Err, Abn Msg, Msg ID Err, CRC Resp Fail)
    if(ScalerGetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, _BIT0) == _BIT0)
    {
        if((ScalerGetByte_EXINT(P65_91_RX_FIFO2_RCV_ERR_INT) & (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
        }
    }
}

//--------------------------------------------------
// Description  : Choose One FIFO to Process (If Multiple FIFO Have Msg., Do The Arbitration Mechanism)
// Input Value  : None
// Output Value : FIFO Selected After Arbitration (_PD_RX_FIFO_0 / _PD_RX_FIFO_1 / _PD_RX_FIFO_2)
//--------------------------------------------------
BYTE ScalerTypeCRx0PdRxFifoSelect_EXINT0(void) using 1
{
    pData_EXINT[0] = _PD_RX_FIFO_RSV;
    pData_EXINT[1] = ScalerGetBit_EXINT(P65_42_RX_FIFO_GENERAL_INFO, (_BIT2 | _BIT1 | _BIT0));

    if((pData_EXINT[1] & _BIT2) == _BIT2)
    {   // If _PD_RX_FIFO_0 (_BIT2) Has Msg.
        if((pData_EXINT[1] & _BIT1) == _BIT1)
        {   // Both _PD_RX_FIFO_0 (_BIT2) & _PD_RX_FIFO_1 (_BIT1) have Msg.
            if((ScalerGetByte_EXINT(P65_54_RX_FIFO0_RCV_SOP)) == (ScalerGetByte_EXINT(P65_74_RX_FIFO1_RCV_SOP)))
            {
                // Check whether Both FIFO_0 and FIFO_1 are "Data & VDM Msg" or not.
                if(((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) &&
                   ((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) &&
                   (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM) &&
                   (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))
                {
                    // If Yes, Discard Old Msg FIFO, and Use Lastest Msg FIFO.
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                        pData_EXINT[0] = _PD_RX_FIFO_0;
                    }
                    else
                    {
                        ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                        pData_EXINT[0] = _PD_RX_FIFO_1;
                    }
                }
                // Check wether One of FIFO0 and FIFO1 is VDM Msg or not.
                else if((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)) ||
                        (((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)))
                {
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        if(!((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO0 = Lastest Msg) && (FIFO0 = PD Msg)), Discard FIFO1, and Use FIFO0.
                            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                            pData_EXINT[0] = _PD_RX_FIFO_0;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            pData_EXINT[0] = _PD_RX_FIFO_1;
                        }
                    }
                    else if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        if(!((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO1 = Lastest Msg) && (FFIFO1 = PD Msg)), Discard FIFO0, and Use FIFO1.
                            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                            pData_EXINT[0] = _PD_RX_FIFO_1;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            pData_EXINT[0] = _PD_RX_FIFO_0;
                        }
                    }
                }
                else
                {
                    // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        pData_EXINT[0] = _PD_RX_FIFO_1;
                    }
                    else
                    {
                        pData_EXINT[0] = _PD_RX_FIFO_0;
                    }
                }
            }
            else
            {   // FIFO_0 & FIFO_1 Have Different Packet Type
                if(ScalerGetByte_EXINT(P65_54_RX_FIFO0_RCV_SOP) == 0x01)
                {   // FIFO_0 Has SOP Packet, FIFO_1 Not SOP, Proc FIFO0
                    pData_EXINT[0] = _PD_RX_FIFO_0;
                }
                else
                {
                    pData_EXINT[0] = _PD_RX_FIFO_1;
                }
            }
        }
        else if((pData_EXINT[1] & _BIT0) == _BIT0)
        {   // Both FIFO_0 & FIFO_2 have Msg.
            if((ScalerGetByte_EXINT(P65_54_RX_FIFO0_RCV_SOP)) == (ScalerGetByte_EXINT(P65_94_RX_FIFO2_RCV_SOP)))
            {
                // Check whether Both FIFO_0 and FIFO_2 are "Data & VDM Msg" or not.
                if(((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) &&
                   ((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) &&
                   (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM) &&
                   (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))
                {
                    // If Yes, Discard Old Msg FIFO, and Use Lastest Msg FIFO.
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                        pData_EXINT[0] = _PD_RX_FIFO_0;
                    }
                    else
                    {
                        ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                        pData_EXINT[0] = _PD_RX_FIFO_2;
                    }
                }
                // Check wether One of FIFO0 and FIFO2 is VDM Msg or not.
                else if((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)) ||
                        (((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)))
                {
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        if(!((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO0 = Lastest Msg) && (FIFO0 = PD Msg)), Discard FIFO2, and Use FIFO0.
                            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                            pData_EXINT[0] = _PD_RX_FIFO_0;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            pData_EXINT[0] = _PD_RX_FIFO_2;
                        }
                    }
                    else if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_2)
                    {
                        if(!((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO2 = Lastest Msg) && (FIFO2 = PD Msg)), Discard FIFO0, and Use FIFO2.
                            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                            pData_EXINT[0] = _PD_RX_FIFO_2;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            pData_EXINT[0] = _PD_RX_FIFO_0;
                        }
                    }
                }
                else
                {
                    // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        pData_EXINT[0] = _PD_RX_FIFO_2;
                    }
                    else
                    {
                        pData_EXINT[0] = _PD_RX_FIFO_0;
                    }
                }
            }
            else
            {   // FIFO_0 & FIFO_2 Have Different Packet Type
                if(ScalerGetByte_EXINT(P65_54_RX_FIFO0_RCV_SOP) == 0x01)
                {   // FIFO_0 Has SOP Packet, FIFO_2 Not SOP, Proc FIFO0
                    pData_EXINT[0] = _PD_RX_FIFO_0;
                }
                else
                {
                    pData_EXINT[0] = _PD_RX_FIFO_2;
                }
            }
        }
        else
        {   // Both FIFO1/2 are Clear, Only FIFO0 Has Msg.
            pData_EXINT[0] = _PD_RX_FIFO_0;
        }
    }
    else if((pData_EXINT[1] & _BIT1) == _BIT1)
    {   // FIFO0 Does not have Msg, FIFO1 Has Msg
        if((pData_EXINT[1] & _BIT0) == _BIT0)
        {   // Both FIFO_1 & FIFO_2 have Msg.
            if((ScalerGetByte_EXINT(P65_74_RX_FIFO1_RCV_SOP)) == (ScalerGetByte_EXINT(P65_94_RX_FIFO2_RCV_SOP)))
            {
                // Check whether Both FIFO_1 and FIFO_2 are "Data & VDM Msg" or not.
                if(((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) &&
                   ((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) &&
                   (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM) &&
                   (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))
                {
                    // If Yes, Discard Old Msg FIFO, and Use Lastest Msg FIFO.
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                        pData_EXINT[0] = _PD_RX_FIFO_1;
                    }
                    else
                    {
                        ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                        pData_EXINT[0] = _PD_RX_FIFO_2;
                    }
                }
                // Check wether One of FIFO1 and FIFO2 is VDM Msg or not.
                else if((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)) ||
                        (((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)))
                {
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        if(!((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO1 = Lastest Msg) && (FIFO1 = PD Msg)), Discard FIFO2, and Use FIFO1.
                            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                            pData_EXINT[0] = _PD_RX_FIFO_1;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            pData_EXINT[0] = _PD_RX_FIFO_2;
                        }
                    }
                    else if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_2)
                    {
                        if(!((((ScalerGetBit_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO2 = Lastest Msg) && (FFIFO2 = PD Msg)), Discard FIFO1, and Use FIFO2.
                            ScalerTypeCRx0PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                            pData_EXINT[0] = _PD_RX_FIFO_2;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            pData_EXINT[0] = _PD_RX_FIFO_1;
                        }
                    }
                }
                else
                {
                    // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                    if((ScalerGetByte_EXINT(P65_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        pData_EXINT[0] = _PD_RX_FIFO_2;
                    }
                    else
                    {
                        pData_EXINT[0] = _PD_RX_FIFO_1;
                    }
                }
            }
            else
            {   // FIFO_1 & FIFO_2 Have Different Packet Type
                if(ScalerGetByte_EXINT(P65_74_RX_FIFO1_RCV_SOP) == 0x01)
                {   // FIFO_1 Has SOP Packet, FIFO_2 Not SOP, Proc FIFO0
                    pData_EXINT[0] = _PD_RX_FIFO_1;
                }
                else
                {
                    pData_EXINT[0] = _PD_RX_FIFO_2;
                }
            }
        }
        else
        {   // FIFO2 Does Not Have Msg.
            pData_EXINT[0] = _PD_RX_FIFO_1;
        }
    }
    else
    {   // Only FIFO2 Has Msg
        pData_EXINT[0] = _PD_RX_FIFO_2;
    }

    return pData_EXINT[0];
}

//--------------------------------------------------
// Description  : Filter Un-wanted Msg. Before Selecting FIFO to Process
// Input Value  : ucRxProcFifo : _PD_RX_FIFO_0 / _PD_RX_FIFO_1 / _PD_RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRxFifoMsgDecode_EXINT0(BYTE ucRxProcFifo) using 1
{
    CLR_PD_RX0_RCV_MSG();
    CLR_PD_RX0_RCV_VDM_CMD();

    switch(ScalerGetByte_EXINT(P65_50_RX_FIFO0_RCV_MSG_INT + (ucRxProcFifo * 0x20)) & (_BIT5 | _BIT3 | _BIT1))
    {
        case _BIT5:     // Control Message Irq = 1

            SET_PD_RX0_RCV_MSG_TYPE(_PD_CMD_TYPE_CTRL);
            SET_PD_RX0_RCV_MSG(ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (0x1F));

            break;

        case _BIT3:     // Data Message Irq = 1

            SET_PD_RX0_RCV_MSG_TYPE(_PD_CMD_TYPE_DATA);
            SET_PD_RX0_RCV_MSG(ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (0x1F));

            // Read Data Objects From "Rx FIFO" to "ucDataObj_EXINT[0-28]"
            ScalerTypeCRx0PdReadDataObj_EXINT0(ucRxProcFifo);

            // Get VDM Command Type For VDM Message
            if(GET_PD_RX0_RCV_MSG() == _PD_CMD_VDM)
            {
                // Get Standard & Vender ID : VDM Header[31:16]
                SET_PD_RX0_VDM_SVID_H(g_pucDataObj_EXINT[0]);
                SET_PD_RX0_VDM_SVID_L(g_pucDataObj_EXINT[1]);

                // Check If Rcv. an Structured VDM Message
                if((g_pucDataObj_EXINT[2] & _BIT7) == _BIT7)
                {
                    // Set VDM Type = Structured VDM
                    SET_PD_RX0_RCV_VDM_TYPE(_PD_STRUCTURED_VDM);

                    // Get VDM Object Position : VDM Header[10:8]
                    SET_PD_RX0_VDM_OBJ_POS(g_pucDataObj_EXINT[2] & (_BIT2 | _BIT1 | _BIT0));

                    // Get VDM Command Type : VDM Header[7:0] ([7:6] VDM CMD Type  [4:0] VDM CMD)
                    SET_PD_RX0_RCV_VDM_CMD(g_pucDataObj_EXINT[3]);
                }
                else
                {
                    // Set VDM Type = Unstructured VDM
                    SET_PD_RX0_RCV_VDM_TYPE(_PD_UNSTRUCTURED_VDM);
                }
            }

            break;

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
        case _BIT1:     // Ext. Message Irq = 1

            SET_PD_RX0_RCV_MSG_TYPE(_PD_CMD_TYPE_EXT);
            SET_PD_RX0_RCV_MSG(ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (0x1F));

            // Read Data Objects From "Rx FIFO" to "ucDataObj_EXINT[0-28]"
            ScalerTypeCRx0PdReadDataObj_EXINT0(ucRxProcFifo);

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            SET_PD_RX0_CHUNKED_MESSAGE((g_pucDataObj_EXINT[0] >> 7));

            // Get Ext Msg Chunk Number
            SET_PD_RX0_CHUNK_NUMBER((g_pucDataObj_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

            // Get Ext Msg Chunk Request
            SET_PD_RX0_CHUNK_REQUEST((g_pucDataObj_EXINT[0] >> 2));

            // Get Ext Msg Total Size
            SET_PD_RX0_EXT_MSG_DATA_SIZE(((WORD)(g_pucDataObj_EXINT[0] & _BIT0) << 8) | (WORD)(g_pucDataObj_EXINT[1]));

            break;
#endif
        default:

#if((_HW_PD_SUPPORT_VERSION >= _PD_VERSION_3_0) && (_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0))
            // Control Message
            if((ScalerGetByte_EXINT(P65_56_RX_FIFO0_MSG_HEADER0 + (ucRxProcFifo * 0x20)) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
            {
                SET_PD_RX0_RCV_MSG_TYPE(_PD_CMD_TYPE_CTRL);
                SET_PD_RX0_RCV_MSG(ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (0x1F));
            }
            else if(((ScalerGetByte_EXINT(P65_56_RX_FIFO0_MSG_HEADER0 + (ucRxProcFifo * 0x20)) & _BIT7) == _BIT7) && ((ScalerGetByte_EXINT(P65_57_RX_FIFO0_MSG_HEADER1 + (ucRxProcFifo * 0x20)) & (0x1F)) == 0x1F))
            {
                SET_PD_RX0_RCV_MSG_TYPE(_PD_CMD_TYPE_EXT);
                SET_PD_RX0_RCV_MSG(_PD_CMD_CHUNK_TEST);

                // Read Data Objects From "Rx FIFO" to "ucDataObj_EXINT[0-28]"
                ScalerTypeCRx0PdReadDataObj_EXINT0(ucRxProcFifo);

                // Check If This Ext Msg is Chunked : Ext Message Header [15]
                SET_PD_RX0_CHUNKED_MESSAGE((g_pucDataObj_EXINT[0] >> 7));

                // Get Ext Msg Chunk Number
                SET_PD_RX0_CHUNK_NUMBER((g_pucDataObj_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

                // Get Ext Msg Chunk Request
                SET_PD_RX0_CHUNK_REQUEST((g_pucDataObj_EXINT[0] >> 2));

                // Get Ext Msg Total Size
                SET_PD_RX0_EXT_MSG_DATA_SIZE(((WORD)(g_pucDataObj_EXINT[0] & _BIT0) << 8) | (WORD)(g_pucDataObj_EXINT[1]));
            }
            else
#endif
            {
                SET_PD_RX0_RCV_MSG_TYPE(_PD_CMD_UNDEFINED);
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Read Data Objects From Rx FIFO to g_pucDataObj_EXINT[0~28]
// Input Value  : ucRxProcFifo : _PD_RX_FIFO_0 / _PD_RX_FIFO_1 / _PD_RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdReadDataObj_EXINT0(BYTE ucRxProcFifo) using 1
{   // FIFO_0 : 0x6559/5A, FIFO_1 : 0x6579/7A, FIFO_2 : 0x6599/9A

    // Get Number Of Data Object From Message Header NoD Field
    SET_PD_RX0_RCV_NOD_CNT((ScalerGetByte_EXINT(P65_56_RX_FIFO0_MSG_HEADER0 + (ucRxProcFifo * 0x20)) & (_BIT6 | _BIT5 | _BIT4)) >> 4);

    // Clear FIFO Address to 0
    ScalerSetByte_EXINT(P65_59_RX_FIFO0_ADDR + (ucRxProcFifo * 0x20), 0x00);

    // Start Reading Data Object Contents from FIFO
    for(pData_EXINT[0] = 0; pData_EXINT[0] < (GET_PD_RX0_RCV_NOD_CNT() * 4); pData_EXINT[0]++)
    {
        g_pucDataObj_EXINT[pData_EXINT[0]] = ScalerGetByte_EXINT(P65_5A_RX_FIFO0_DATA + (ucRxProcFifo * 0x20));
    }
    // Data Object 0 [31:24] -> DataObj[0]
    // Data Object 0 [23:16] -> DataObj[1]
    // Data Object 0 [15:8]  -> DataObj[2]
    // Data Object 0 [7:0]   -> DataObj[3] ...
}

//--------------------------------------------------
// Description  : Process For Handling Protocol Error
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdPrlErrHandle_EXINT0(void)  using 1
{
    if((GET_PD_RX0_AMS_STATUS() == _PD_AMS_POWER_TRANSITION) || (GET_PD_RX0_FW_STATE() == _PD_INT_WAIT_SOFTRESET_RESP))
    {   // If  : Rcv Unexpected Msg. in During Power Transition or Soft Reset, Do "HARD RESET"
        ScalerTypeCRx0PdSendHardRst_EXINT0();
    }
    else
    {   // Else : Rcv Unexpected Msg. During Non-Int. AMS or Unexpected Msg. in Ready State
        ScalerTypeCRx0PdSendSoftRst_EXINT0(_PD_SOP_PKT);
    }
}

//--------------------------------------------------
// Description  : Process When Receive Soft Reset Message
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdRcvSoftRstProc_EXINT0(void)  using 1
{
    if(GET_PD_RX0_FW_STATE() != _PD_HARDRESET)
    {
        if((GET_PD_RX0_AMS_STATUS() == _PD_AMS_POWER_TRANSITION) || (GET_PD_RX0_FW_STATE() == _PD_INT_WAIT_SOFTRESET_RESP))
        {   // 1. If Rcv. Soft Reset During Power Transition or Already in Soft Reset => HARD RESET
            ScalerTypeCRx0PdSendHardRst_EXINT0();
        }
        else if((GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_WAIT_DRS_RESP) || (GET_PD_RX0_SUB_STATE() == _PD_SUB_INT_SEND_ACCEPT_DRS))
        {   // 2. If Rcv. Soft Reset During DR_SWAP => Type-C Error Recovery (8.3.3.4.1)
            SET_TYPE_C_ERROR_RECOVERY();
        }
        else
        {   // 3. Else Do Soft Reset, Responese Accept (Include Rcv. Soft Reset Again Before Reply Accept)

            // [0x6503] Reset Protocol Layer State
            ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT0, _BIT0);

            SET_PD_RX0_FW_STATE(_PD_INT_SEND_SOFTRESET_RESP);
            SET_PD_RX0_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Accept"
            ScalerTypeCRx0PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
        }
    }
}

//--------------------------------------------------
// Description  : Set Rx0 PD Max Power
// Input Value  : usMaxPower : Max Power in 0.1W
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetMaxPower(WORD usMaxPower)
{
    if(usMaxPower <= 1000)
    {
        SET_RX0_MAX_POWER(usMaxPower);
    }
    else
    {
        SET_RX0_MAX_POWER(1000);
        DebugMessageSystem("8. [TYPE C] ==========X Max Power > 100W, Clamp to 100W", usMaxPower);
    }
}

//--------------------------------------------------
// Description  : Set Rx0 PD Number of Source Capability want to Provide
// Input Value  : ucPdoCnt : Number of Source Capability
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        SET_PD_RX0_SRC_PDO_CNT(ucPdoCnt);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        SET_PD_RX0_SNK_PDO_CNT(ucPdoCnt);
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Get Rx0 PD Number of Source Capability want to Provide
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : ucPdoCnt : Number of Source Capability
//--------------------------------------------------
BYTE ScalerTypeCRx0PdGetPdoCnt(EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCount = 0x00;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        ucPdoCount = GET_PD_RX0_SRC_PDO_CNT();
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        ucPdoCount = GET_PD_RX0_SNK_PDO_CNT();
    }

    return ucPdoCount;
}
#endif

//--------------------------------------------------
// Description  : Get Rx0 PD Partner Number of Source/Sink PDOs
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : ucPdoCnt : Number of Source Capability
//--------------------------------------------------
BYTE ScalerTypeCRx0PdGetPartnerPdoCnt(EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCount = 0x00;

    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_PD_RX0_RCV_SRC_CAP() == _TRUE))
    {
        ucPdoCount = GET_PD_RX0_PARTNER_SRC_CAP_CNT();
    }
    else if((enumPowerRole == _TYPE_C_POWER_SNK) && (GET_PD_RX0_RCV_SNK_CAP() == _TRUE))
    {
        ucPdoCount = GET_PD_RX0_PARTNER_SNK_CAP_CNT();
    }

    return ucPdoCount;
}

//--------------------------------------------------
// Description  : Get Partner Source/Sink PDO Info
// Input Value  : enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCRx0PdGetPartnerPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_PD_RX0_RCV_SRC_CAP() == _TRUE))
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_PD_RX0_PARTNER_SRC_CAP_CNT()))
        {
            stTypeCPartnerPdo.enumPdoType = GET_PD_RX0_PARTNER_SRC_CAP_TYPE(ucPdoIndex - 1);

            if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPartnerPdo.enumPeakCurrent = (EnumPDPeakCurType)GET_PD_RX0_PARTNER_SRC_PEAK_CUR(ucPdoIndex - 1);
            }

            // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
            stTypeCPartnerPdo.ucMaxVoltage = (BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
            stTypeCPartnerPdo.ucMinVoltage = (BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

            // Get Current in Macro (Unit = 10mA)
            stTypeCPartnerPdo.usMaxCurrent = GET_PD_RX0_PARTNER_SRC_CAP_CUR(ucPdoIndex - 1);
        }
    }
    else if((enumPowerRole == _TYPE_C_POWER_SNK) && (GET_PD_RX0_RCV_SNK_CAP() == _TRUE))
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_PD_RX0_PARTNER_SNK_CAP_CNT()))
        {
            stTypeCPartnerPdo.enumPdoType = GET_PD_RX0_PARTNER_SNK_CAP_TYPE(ucPdoIndex - 1);

            // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
            stTypeCPartnerPdo.ucMaxVoltage = (BYTE)(GET_PD_RX0_PARTNER_SNK_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
            stTypeCPartnerPdo.ucMinVoltage = (BYTE)(GET_PD_RX0_PARTNER_SNK_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

            // Get Current in Macro (Unit = 10mA)
            stTypeCPartnerPdo.usMaxCurrent = GET_PD_RX0_PARTNER_SNK_CAP_CUR(ucPdoIndex - 1);
        }
    }

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get TypeC Negotiated Voltage / Current
// Input Value  : Voltage (10mV) / Current (10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdGetPdoStatus(WORD *pusVoltage, WORD *pusCurrent)
{
    if(GET_CC_RX0_ATTACHED() == _TRUE)
    {
        if(GET_PD_RX0_EXPLICIT_CONTRACT() == _TRUE)
        {
            // CC Attached, PD Power Contract Established : Negotiated Voltage & Current
            *pusVoltage = GET_PD_RX0_PDO_STATUS_VOL();

            *pusCurrent = GET_PD_RX0_PDO_STATUS_CUR();
        }
        else
        {
            // CC Attached, No PD Power Contract : 5V / Current According to Rp Value
            *pusVoltage = 500;

            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                *pusCurrent = GET_CC_RX0_DEF_CUR();
            }
            else
            {
                if(ScalerTypeCRx0CcDetResistor() == _DET_RP_3P0A)
                {
                    // Sink Detect Rp-3.0A, Set Current to 3.0A
                    *pusCurrent = 300;
                }
                else if(ScalerTypeCRx0CcDetResistor() == _DET_RP_1P5A)
                {
                    // Sink Detect Rp-1.5A, Set Current to 1.5A
                    *pusCurrent = 150;
                }
                else
                {
                    // Sink Detect Rp-Default, Set Current to 500mA
                    *pusCurrent = 50;
                }
            }
        }
    }
    else
    {
        // CC Unattached : Set Voltage & Current to 0
        *pusVoltage = 0;
        *pusCurrent = 0;
    }
}

//--------------------------------------------------
// Description  : Get Current Source PDO that Sink Request
// Input Value  : None
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCRx0PdGetRequestedSrcPdo(void)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    // Check if CC Attached and PD Power Contract Established
    if(GET_CC_RX0_ATTACHED() == _TRUE)
    {
        if(GET_PD_RX0_EXPLICIT_CONTRACT() == _TRUE)
        {
            if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
            {
                if((GET_PD_RX0_PARTNER_OBJ_POS() > 0) && (GET_PD_RX0_PARTNER_OBJ_POS() <= GET_PD_RX0_SRC_PDO_CNT()))
                {
                    stTypeCSrcPdo.enumPdoType = GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1);

                    if(GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        stTypeCSrcPdo.enumPeakCurrent = (EnumPDPeakCurType)GET_PD_RX0_SRC_CAP_PEAK(GET_PD_RX0_PARTNER_OBJ_POS() - 1);

                        // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                        stTypeCSrcPdo.ucMaxVoltage = (BYTE)(GET_PD_RX0_SRC_CAP_VOL_MAX(GET_PD_RX0_PARTNER_OBJ_POS() - 1) / 10);
                        stTypeCSrcPdo.ucMinVoltage = (BYTE)(GET_PD_RX0_SRC_CAP_VOL_MIN(GET_PD_RX0_PARTNER_OBJ_POS() - 1) / 10);

                        // Get Fix PDO Current in Macro (Unit = 10mA)
                        stTypeCSrcPdo.usMaxCurrent = GET_PD_RX0_SRC_CAP_CUR(GET_PD_RX0_PARTNER_OBJ_POS() - 1);
                    }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    else if(GET_PD_RX0_SRC_PDO_TYPE(GET_PD_RX0_PARTNER_OBJ_POS() - 1) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                        stTypeCSrcPdo.ucMaxVoltage = (BYTE)(GET_PD_RX0_SRC_CAP_VOL_MAX(GET_PD_RX0_PARTNER_OBJ_POS() - 1) / 10);
                        stTypeCSrcPdo.ucMinVoltage = (BYTE)(GET_PD_RX0_SRC_CAP_VOL_MIN(GET_PD_RX0_PARTNER_OBJ_POS() - 1) / 10);

                        // Get Programmable PDO Current in Macro (Unit = 50mA), and Convert to 10mA
                        stTypeCSrcPdo.usMaxCurrent = (GET_PD_RX0_SRC_CAP_CUR(GET_PD_RX0_PARTNER_OBJ_POS() - 1) * 5);
                    }
#endif
                }
            }
            else
            {
                if((GET_PD_RX0_REQ_OBJ_POS() > 0) && (GET_PD_RX0_REQ_OBJ_POS() <= GET_PD_RX0_PARTNER_SRC_CAP_CNT()))
                {
                    stTypeCSrcPdo.enumPdoType = GET_PD_RX0_PARTNER_SRC_CAP_TYPE(GET_PD_RX0_REQ_OBJ_POS() - 1);

                    if(GET_PD_RX0_PARTNER_SRC_CAP_TYPE(GET_PD_RX0_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        stTypeCSrcPdo.enumPeakCurrent = (EnumPDPeakCurType)GET_PD_RX0_PARTNER_SRC_PEAK_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1);
                    }

                    // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                    stTypeCSrcPdo.ucMaxVoltage = (BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_VOL_MAX(GET_PD_RX0_REQ_OBJ_POS() - 1) / 10);
                    stTypeCSrcPdo.ucMinVoltage = (BYTE)(GET_PD_RX0_PARTNER_SRC_CAP_VOL_MIN(GET_PD_RX0_REQ_OBJ_POS() - 1) / 10);

                    // Get Current in Macro (Unit = 10mA)
                    stTypeCSrcPdo.usMaxCurrent = GET_PD_RX0_PARTNER_SRC_CAP_CUR(GET_PD_RX0_REQ_OBJ_POS() - 1);
                }
            }
        }
    }

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Set Rx0 System Event
// Input Value  : enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetSystemEvent(EnumPDSysEvent enumPdSysEvent)
{
    if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_ERROR_RECOVERY) == _PD_SYS_EVENT_ERROR_RECOVERY)
    {
        SET_TYPE_C_ERROR_RECOVERY();
    }
    else
    {
        SET_PD_RX0_SYS_EVENT(enumPdSysEvent);
    }
}

#if(((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) || (_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
//--------------------------------------------------
// Description  : Set Rx0 System Event
// Input Value  : enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetSystemEvent_EXINT0(EnumPDSysEvent enumPdSysEvent) using 1
{
    if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_ERROR_RECOVERY) == _PD_SYS_EVENT_ERROR_RECOVERY)
    {
        SET_TYPE_C_ERROR_RECOVERY();
    }
    else
    {
        SET_PD_RX0_SYS_EVENT(enumPdSysEvent);
    }
}
#endif

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
//--------------------------------------------------
// Description  : Set Rx0 System Event
// Input Value  : enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetSystemEvent_WDINT(EnumPDSysEvent enumPdSysEvent) using 3
{
    if((GET_PD_RX0_SYS_EVENT() & _PD_SYS_EVENT_ERROR_RECOVERY) == _PD_SYS_EVENT_ERROR_RECOVERY)
    {
        SET_TYPE_C_ERROR_RECOVERY();
    }
    else
    {
        SET_PD_RX0_SYS_EVENT(enumPdSysEvent);
    }
}
#endif

//--------------------------------------------------
// Description  : Get Rx0 Port Controller Event
// Input Value  : None
// Output Value : EnumPDPortCtrlEvent
//--------------------------------------------------
EnumPDPortCtrlEvent ScalerTypeCRx0PdGetPortCtrlEvent(void)
{
    return GET_PD_RX0_PORT_CTRL_EVENT();
}

//--------------------------------------------------
// Description  : Clear Rx0 Port Controller Event
// Input Value  : enumPdPortCtrlEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdClrPortCtrlEvent(EnumPDPortCtrlEvent enumPdPortCtrlEvent)
{
    CLR_PD_RX0_PORT_CTRL_EVENT(enumPdPortCtrlEvent);
}

//--------------------------------------------------
// Description  : Set PD Function Support Option
// Input Value  : enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetFunctionSupport(EnumTypeCFunctionSupport enumFunctionSupport)
{
    switch(enumFunctionSupport)
    {
        case _TYPE_C_SUPPORT_NO_FUNCTION:
        case _TYPE_C_SUPPORT_CC_FUNCTION:

            CLR_PD_RX0_FUNCTION_EN();
            CLR_PD_RX0_ALT_MODE_FUNCTION();

            break;

        case _TYPE_C_SUPPORT_CC_AND_PD_FUNCTION:

            SET_PD_RX0_FUNCTION_EN();
            CLR_PD_RX0_ALT_MODE_FUNCTION();

            break;

        case _TYPE_C_SUPPORT_FULL_FUNCTION:

            SET_PD_RX0_FUNCTION_EN();
            SET_PD_RX0_ALT_MODE_FUNCTION();

            break;

        default:

            break;
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Get Lenovo Alt Mode Ready Status
// Input Value  : None
// Output Value : Lenovo Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeCRx0PdGetLenovoAltModeReady(void)
{
#if(_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_PD_RX0_LENOVO_ALT_MODE_ENTER() == _TRUE) && ((GET_TYPE_C_RX0_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_PD_RX0_PARTNER_DRP() == _FALSE) || (GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) || (GET_PD_RX0_UNCONSTRAIN_POWER() == _FALSE) || (GET_PD_RX0_PRS_REJECT() == _TRUE)))
#else
    if(GET_PD_RX0_LENOVO_ALT_MODE_ENTER() == _TRUE)
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type
// Input Value  : None
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType ScalerTypeCRx0PdGetLenovoDeviceType(void)
{
    return GET_PD_RX0_LENOVO_DEVICE_TYPE();
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event
// Input Value  : None
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent ScalerTypeCRx0PdGetLenovoSystemEvent(void)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};

    stLenovoSysEvent.b3SystemReserved = (GET_PD_RX0_LENOVO_SYS_EVENT() & (_BIT7 | _BIT6 | _BIT5)) >> 5;
    stLenovoSysEvent.enumSystemPowerMode = (GET_PD_RX0_LENOVO_SYS_EVENT() & _BIT4) >> 4;
    stLenovoSysEvent.enumSystemState = (GET_PD_RX0_LENOVO_SYS_EVENT() & (_BIT3 | _BIT2 | _BIT1)) >> 1;
    stLenovoSysEvent.b1SystemEvent = (bit)(GET_PD_RX0_LENOVO_SYS_EVENT() & _BIT0);
    stLenovoSysEvent.ucSystemAcknowlegde = GET_PD_RX0_LENOVO_SYS_ACKNOWLEDGE();

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetLenovoDockingEvent(StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    if(stLenovoDockEvent.b1DockingEvent == _TRUE)
    {
        SET_PD_RX0_LENOVO_DOCK_EVENT(((BYTE)stLenovoDockEvent.b4DockingReserved << 4) | (stLenovoDockEvent.enumDockingPowerSwitch << 2) | ((BYTE)stLenovoDockEvent.b1DockingWolRequest << 1) | ((BYTE)stLenovoDockEvent.b1DockingEvent));
    }
    else
    {
        CLR_PD_RX0_LENOVO_DOCK_EVENT();
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCRx0PdCheckLenovoDockingEventBusy(void)
{
    if(GET_PD_RX0_LENOVO_DOCK_EVENT() == 0x00)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Get Acer Alt Mode Ready Status
// Input Value  : None
// Output Value : Acer Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeCRx0PdGetAcerAltModeReady(void)
{
#if(_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_PD_RX0_ACER_ALT_MODE_ENTER() == _TRUE) && ((GET_TYPE_C_RX0_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_PD_RX0_PARTNER_DRP() == _FALSE) || (GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) || (GET_PD_RX0_UNCONSTRAIN_POWER() == _FALSE) || (GET_PD_RX0_PRS_REJECT() == _TRUE)))
#else
    if(GET_PD_RX0_ACER_ALT_MODE_ENTER() == _TRUE)
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Get System Event
// Input Value  : None
// Output Value : StructTypeCAcerSysEvent
//--------------------------------------------------
StructTypeCAcerSysEvent ScalerTypeCRx0PdGetAcerSystemEvent(void)
{
    StructTypeCAcerSysEvent stAcerSysEvent = {_TYPE_C_ACER_SYS_EVENT_NONE, {0x00}, 0x00};

    if(GET_PD_RX0_ACER_SYS_EVENT() != _TYPE_C_ACER_SYS_EVENT_NONE)
    {
        stAcerSysEvent.enumEvent = GET_PD_RX0_ACER_SYS_EVENT();
        stAcerSysEvent.b3VdmCnt = GET_PD_RX0_ACER_SYS_VDM_CNT();

        for(pData[0] = 0; pData[0] < (GET_PD_RX0_ACER_SYS_VDM_CNT() * 4); pData[0]++)
        {
            stAcerSysEvent.pucVdmData[pData[0]] = GET_PD_RX0_ACER_SYS_VDM_DATA(pData[0]);
        }

        CLR_PD_RX0_ACER_SYS_EVENT(_TYPE_C_ACER_SYS_EVENT_ALL);
    }

    return stAcerSysEvent;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Set User Event
// Input Value  : stAcerUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetAcerUserEvent(StructTypeCAcerUserEvent stAcerUserEvent)
{
    if(stAcerUserEvent.enumEvent != _TYPE_C_ACER_USER_EVENT_NONE)
    {
        SET_PD_RX0_ACER_USER_EVENT(stAcerUserEvent.enumEvent);

        // VDO Cnt Should be 0~6, not including VDM Header
        SET_PD_RX0_ACER_USER_VDM_CNT(stAcerUserEvent.b3VdmCnt);

        for(pData[0] = 0; pData[0] < (stAcerUserEvent.b3VdmCnt * 4); pData[0]++)
        {
            SET_PD_RX0_ACER_USER_VDM_DATA(pData[0], stAcerUserEvent.pucVdmData[pData[0]]);
        }
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Check if Last User Event has been Sent
// Input Value  : None
// Output Value : User Event Busy Status (_TYPE_C_ACER_USER_EVENT_BUSY / _TYPE_C_ACER_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCAcerBusyStatus ScalerTypeCRx0PdCheckAcerUserEventBusy(void)
{
    if(GET_PD_RX0_ACER_USER_EVENT() == _TYPE_C_ACER_USER_EVENT_NONE)
    {
        return _TYPE_C_ACER_USER_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_ACER_USER_EVENT_BUSY;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Get Hp Alt Mode Ready Status
// Input Value  : None
// Output Value : Hp Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeCRx0PdGetHpAltModeReady(void)
{
#if(_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE) && ((GET_TYPE_C_RX0_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_PD_RX0_PARTNER_DRP() == _FALSE) || (GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC) || (GET_PD_RX0_UNCONSTRAIN_POWER() == _FALSE) || (GET_PD_RX0_PRS_REJECT() == _TRUE)))
#else
    if(GET_PD_RX0_HP_ALT_MODE_ENTER() == _TRUE)
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Get System Event
// Input Value  : None
// Output Value : StructTypeCHpSysEvent
//--------------------------------------------------
StructTypeCHpSysEvent ScalerTypeCRx0PdGetHpSystemEvent(void)
{
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    // Check if Sys Event Queue is Empty
    if(GET_PD_RX0_HP_SYS_EVENT_QUEUE_CNT() > 0)
    {
        // Update Sys Event Struct For Kernel Usage
        stHpSysEvent = GET_PD_RX0_HP_SYS_EVENT_QUEUE(GET_PD_RX0_HP_SYS_EVENT_QUEUE_HEAD());

        CLR_PD_RX0_HP_SYS_EVENT_QUEUE(GET_PD_RX0_HP_SYS_EVENT_QUEUE_HEAD());
        ADD_PD_RX0_HP_SYS_EVENT_QUEUE_HEAD();
        SUB_PD_RX0_HP_SYS_EVENT_QUEUE_CNT();
    }

    return stHpSysEvent;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Set User Event
// Input Value  : stHpUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetHpUserEvent(StructTypeCHpUserEvent stHpUserEvent)
{
    if(stHpUserEvent.enumEvent != _TYPE_C_HP_USER_EVENT_NONE)
    {
        SET_PD_RX0_HP_USER_EVENT(stHpUserEvent.enumEvent);

        // VDO Cnt Should be 0~5, not including VDM Header
        SET_PD_RX0_HP_USER_VDM_CNT(stHpUserEvent.b3VdmCnt);

        for(pData[0] = 0; pData[0] < (stHpUserEvent.b3VdmCnt * 4); pData[0]++)
        {
            SET_PD_RX0_HP_USER_VDM_DATA(pData[0], stHpUserEvent.pucVdmData[pData[0]]);
        }
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Check if Last User Event has been Sent
// Input Value  : None
// Output Value : User Event Busy Status (_TYPE_C_HP_USER_EVENT_BUSY / _TYPE_C_HP_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCHpBusyStatus ScalerTypeCRx0PdCheckHpUserEventBusy(void)
{
    if(GET_PD_RX0_HP_USER_EVENT() == _TYPE_C_HP_USER_EVENT_NONE)
    {
        return _TYPE_C_HP_USER_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_HP_USER_EVENT_BUSY;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Get Dell Alt Mode Ready Status
// Input Value  : None
// Output Value : Dell Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeCRx0PdGetDellAltModeReady(void)
{
    if(GET_PD_RX0_DELL_ALT_MODE_ENTER() == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Get System Event from Kernel
// Input Value  : None
// Output Value : StructTypeCDellSysEvent
//--------------------------------------------------
StructTypeCDellSysEvent ScalerTypeCRx0PdGetDellSystemEvent(void)
{
    StructTypeCDellSysEvent stDellSysEvent = {_TYPE_C_DELL_SYS_EVENT_NONE, {0x00}, 0x00};

    if(GET_PD_RX0_DELL_SYS_EVENT() != _TYPE_C_DELL_SYS_EVENT_NONE)
    {
        stDellSysEvent.enumEvent = GET_PD_RX0_DELL_SYS_EVENT();

        if((GET_PD_RX0_DELL_SYS_EVENT() & _TYPE_C_DELL_SYS_EVENT_0X12) == _TYPE_C_DELL_SYS_EVENT_0X12)
        {
            stDellSysEvent.b3VdmCnt = GET_PD_RX0_DELL_SYS_VDM_CNT();

            for(pData[0] = 0; pData[0] < (stDellSysEvent.b3VdmCnt * 4); pData[0]++)
            {
                stDellSysEvent.pucVdmData[pData[0]] = GET_PD_RX0_DELL_SYS_VDM_DATA(pData[0]);
            }
        }

        CLR_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ALL);
    }

    return stDellSysEvent;
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set User Event to Kernel
// Input Value  : stDellUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetDellUserEvent(StructTypeCDellUserEvent stDellUserEvent)
{
    if(stDellUserEvent.enumEvent != _TYPE_C_DELL_USER_EVENT_NONE)
    {
        if((GET_PD_RX0_DELL_SYS_EVENT() & _TYPE_C_DELL_SYS_EVENT_0X12) == _TYPE_C_DELL_SYS_EVENT_0X12)
        {
            // If (System Event == 0x12) , Set Atten_Discard SysEvent and Don't Set User Event to Kernel.
            SET_PD_RX0_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_DISCARD);
        }
        else
        {
            SET_PD_RX0_DELL_USER_EVENT(stDellUserEvent.enumEvent);

            // VDO Cnt Should be 0~6, not including VDM Header
            SET_PD_RX0_DELL_USER_VDM_CNT(stDellUserEvent.b3VdmCnt);

            for(pData[0] = 0; pData[0] < (stDellUserEvent.b3VdmCnt * 4); pData[0]++)
            {
                SET_PD_RX0_DELL_USER_VDM_DATA(pData[0], stDellUserEvent.pucVdmData[pData[0]]);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set Initial Complete Status to Kernel
// Input Value  : enumDellInitCompleteStatus
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdSetDellAltModeInitComplete(EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus)
{
    if(enumDellInitCompleteStatus == _TYPE_C_DELL_INIT_COMPLETE)
    {
        SET_PD_RX0_DELL_AM_INIT_COMPLETE();
    }
    else
    {
        CLR_PD_RX0_DELL_AM_INIT_COMPLETE();
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Check if Last User Event has been Sent
// Input Value  : None
// Output Value : User Event Busy Status (_TYPE_C_DELL_USER_EVENT_BUSY / _TYPE_C_DELL_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCDellBusyStatus ScalerTypeCRx0PdCheckDellUserEventBusy(void)
{
    if(GET_PD_RX0_DELL_USER_EVENT() == _TYPE_C_DELL_USER_EVENT_NONE)
    {
        return _TYPE_C_DELL_USER_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_DELL_USER_EVENT_BUSY;
    }
}

//--------------------------------------------------
// Description  : Type C Get Enter Dell Alt Mode Time Out Result
// Input Value  : None
// Output Value : Enter Dell Alt Mode Time Out Result (_TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT/ _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT)
//--------------------------------------------------
EnumTypeCEnterDellAltModeTimeOut ScalerTypeCRx0PdGetEnterDellAltModeTimeOut(void)
{
    if(GET_PD_RX0_DELL_AM_ENTER_TIMEOUT() == _TRUE)
    {
        return _TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT;
    }
    else
    {
        return _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type C Alt Mode Related Info for Billboard Display
// Input Value  : Pointer of Billboard Info
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdGetAltModeBillboardInfo(BYTE *pucBillboardAltModeInfo)
{
    // Call Example : ScalerTypeRx0PdGetAltModeBillboardInfo((BYTE *)(&Array))
    // Note : Array Size Should be _ALT_MODE_SUPPORT_CNT

    pucBillboardAltModeInfo = pucBillboardAltModeInfo;

#if(_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON)
    if(ScalerTypeCRx0PdGetAltModeReady() == _TRUE)
    {
        *pucBillboardAltModeInfo++ = 0x03;                              // Alt Mode Status
    }
    else
    {
        *pucBillboardAltModeInfo++ = 0x00;                              // Alt Mode Status
    }
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID);                       // Alt Mode SVID_Low
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID >> 8);                  // Alt Mode SVID_High
    *pucBillboardAltModeInfo++ = 0x00;                                  // Mode of SVID
    *pucBillboardAltModeInfo++ = _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX;     // URL Index
    *pucBillboardAltModeInfo++ = 0x45;                                  // Discover Mode Ack VDO1[7:0]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[15:8] : DP Tx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = GET_PD_RX0_PIN_ASSIGNMENT_CAP();       // Discover Mode Ack VDO1[23:16] : DP Rx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[31:24] : Rsv
    *pucBillboardAltModeInfo++ = _TRUE;                                 // Current altmode active
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    if(ScalerTypeCRx0PdGetLenovoAltModeReady() == _TRUE)
    {
        *pucBillboardAltModeInfo++ = 0x03;                              // Alt Mode Status
    }
    else
    {
        *pucBillboardAltModeInfo++ = 0x00;                              // Alt Mode Status
    }
    *pucBillboardAltModeInfo++ = (BYTE)(_LENOVO_VID);                   // Alt Mode SVID_Low
    *pucBillboardAltModeInfo++ = (BYTE)(_LENOVO_VID >> 8);              // Alt Mode SVID_High
    *pucBillboardAltModeInfo++ = 0x00;                                  // Mode of SVID
    *pucBillboardAltModeInfo++ = _TYPE_C_EMB_LENOVO_ALT_MODE_URL_INDEX; // URL Index
    *pucBillboardAltModeInfo++ = 0x01;                                  // Discover Mode Ack VDO1[7:0]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[15:8]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[23:16]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[31:24]
    *pucBillboardAltModeInfo++ = _TRUE;                                 // Current altmode active
#endif
}
#endif  // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Rx0 PD Power Role
// Input Value  : None
// Output Value : PD HPD Status
//--------------------------------------------------
bit ScalerTypeCRx0PdGetPowerRole(void)
{
    return GET_PD_RX0_POWER_ROLE();
}

//--------------------------------------------------
// Description  : Get Rx0 PD Power Role
// Input Value  : None
// Output Value : PD HPD Status
//--------------------------------------------------
BYTE ScalerTypeCRx0PdGetPowerRole_EXINT0(void) using 1
{
    return GET_PD_RX0_POWER_ROLE();
}

//--------------------------------------------------
// Description  : Set Rx0 PD Power Role
// Input Value  : None
// Output Value : PD HPD Status
//--------------------------------------------------
void ScalerTypeCRx0PdSetPowerRole(bit bRole)
{
    SET_PD_RX0_POWER_ROLE(bRole);
}

//--------------------------------------------------
// Description  : Set Rx0 PD Power Role
// Input Value  : None
// Output Value : PD HPD Status
//--------------------------------------------------
void ScalerTypeCRx0PdSetPowerRole_EXINT0(bit bRole) using 1
{
    SET_PD_RX0_POWER_ROLE(bRole);
}

//--------------------------------------------------
// Description  : Get Rx0 Power Role Swap Processing
// Input Value  : None
// Output Value : Processing
//--------------------------------------------------
bit ScalerTypeCRx0PdGetPowerRoleSwapProcessing(void)
{
    return GET_PD_RX0_PRS_PROCESSING();
}

//--------------------------------------------------
// Description  : Clear Interop S8 Flag to Enable FW Solution
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0PdClrInteropS8Flag(void)
{
    CLR_PD_RX0_INTEROP_S8();
}

//--------------------------------------------------
// Description  : Get Rx0 PD HPD Queue(index)
// Input Value  : None
// Output Value : PD HPD Status
//--------------------------------------------------
EnumPDHpdType ScalerTypeCRx0PdGetHPDQueue(BYTE ucIndex)
{
    return GET_PD_RX0_HPD_QUEUE(ucIndex);
}

//--------------------------------------------------
// Description  : Get Rx0 PD HPD Que Read Pointer
// Input Value  : None
// Output Value : Que Read Pointer
//--------------------------------------------------
BYTE ScalerTypeCRx0PdGetHPDQueReadPointer(void)
{
    return GET_PD_RX0_HPD_RPTR();
}

//--------------------------------------------------
// Description  : Get Rx0 PD SRC Cap Sent Status
// Input Value  : None
// Output Value : PD SRC Cap Sent Status
//--------------------------------------------------
bit ScalerTypeCRx0PdGetSRCCapSentStatus(void)
{
    return GET_PD_RX0_SRC_CAP_SENT_FLAG();
}

#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
