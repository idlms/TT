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
// ID Code      : UserCommonPortControllerRts5400.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLER5400__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definition of Type-C 5400 Related Macro
//--------------------------------------------------
#define GET_TYPE_C_5400_DATA_ROLE(x)                        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumDataRole)
#define SET_TYPE_C_5400_DATA_ROLE(x, y)                     (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumDataRole = (y))

#define GET_TYPE_C_5400_POWER_ROLE(x)                       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumPowerRole)
#define SET_TYPE_C_5400_POWER_ROLE(x, y)                    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumPowerRole = (y))

#define GET_TYPE_C_5400_PORT_PARTNER_FLAG(x)                (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucPortPartnerFlag)
#define SET_TYPE_C_5400_PORT_PARTNER_FLAG(x, y)             (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucPortPartnerFlag = (y))

#define GET_TYPE_C_5400_DETECT_STATUS(x)                    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectStatusFlag)
#define SET_TYPE_C_5400_DETECT_STATUS(x)                    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectStatusFlag = _TRUE)
#define CLR_TYPE_C_5400_DETECT_STATUS(x)                    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectStatusFlag = _FALSE)

// Rts 5400 I2C Write Cmd Extend Info
#define GET_TYPE_C_5400_I2C_WR_EXTEND_INFO(x)               (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucI2CWrExtendInfo)
#define SET_TYPE_C_5400_I2C_WR_EXTEND_INFO(x, y)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucI2CWrExtendInfo = (y))
#define CLR_TYPE_C_5400_I2C_WR_EXTEND_INFO(x)               (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucI2CWrExtendInfo = 0)

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
// Currently Negotiated Request Info Macro
#define GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3ReqObjPos)
#define SET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(x, y)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3ReqObjPos = (y))
#define CLR_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3ReqObjPos = 0)

#define GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(x)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo0)
#define SET_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(x, y)         (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo0 = (y))
#define CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(x)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo0 = 0)

#define GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(x)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo1)
#define SET_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(x, y)         (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo1 = (y))
#define CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(x)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo1 = 0)

#define GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(x)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo2)
#define SET_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(x, y)         (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo2 = (y))
#define CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(x)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucReqInfo2 = 0)

// 5400 Source Capability Macros
#define GET_TYPE_C_5400_SRC_CAP_CNT(x)                      (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfSrcCap)
#define SET_TYPE_C_5400_SRC_CAP_CNT(x, y)                   (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfSrcCap = (y))

#define GET_TYPE_C_5400_SRC_CAP_TYPE(x, y)                  (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].enumPdoType)
#define SET_TYPE_C_5400_SRC_CAP_TYPE(x, y, z)               (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].enumPdoType = (z))

#define GET_TYPE_C_5400_SRC_CAP_VOL_MAX(x, y)               (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].ucMaxVoltage)
#define SET_TYPE_C_5400_SRC_CAP_VOL_MAX(x, y, z)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].ucMaxVoltage = (z))

#define GET_TYPE_C_5400_SRC_CAP_VOL_MIN(x, y)               (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].ucMinVoltage)
#define SET_TYPE_C_5400_SRC_CAP_VOL_MIN(x, y, z)            (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].ucMinVoltage = (z))

#define GET_TYPE_C_5400_SRC_CAP_CUR(x, y)                   (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].usMaxCurrent)
#define SET_TYPE_C_5400_SRC_CAP_CUR(x, y, z)                (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].usMaxCurrent = (z))

#define GET_TYPE_C_5400_SRC_CAP_PEAK_CUR(x, y)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].enumPeakCurrent)
#define SET_TYPE_C_5400_SRC_CAP_PEAK_CUR(x, y, z)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstSrcPdo[y].enumPeakCurrent = (z))

// Port Partner(Other Side) Source Capability Macros
#define GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfPartnerSrcCap)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(x, y)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfPartnerSrcCap = (y))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(x, y)          (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPdoType)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(x, y, z)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPdoType = (z))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(x, y)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].ucMaxVoltage)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(x, y, z)    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].ucMaxVoltage = (z))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(x, y)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].ucMinVoltage)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(x, y, z)    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].ucMinVoltage = (z))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(x, y)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMaxCurrent)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(x, y, z)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].usMaxCurrent = (z))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_PEAK_CUR(x, y)      (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPeakCurrent)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_PEAK_CUR(x, y, z)   (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerSrcPdo[y].enumPeakCurrent = (z))

// Power Contract Negotiated Power Status
#define GET_TYPE_C_5400_PDO_STATUS_VOL(x)                   (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].usPdoStatusVoltage)
#define SET_TYPE_C_5400_PDO_STATUS_VOL(x, y)                (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].usPdoStatusVoltage = (y))

#define GET_TYPE_C_5400_PDO_STATUS_CUR(x)                   (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].usPdoStatusCurrent)
#define SET_TYPE_C_5400_PDO_STATUS_CUR(x, y)                (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].usPdoStatusCurrent = (y))
#endif

#define GET_TYPE_C_5400_I2C_ENABLED_FLG(x)                  (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1I2CEnabledFlag)
#define SET_TYPE_C_5400_I2C_ENABLED_FLG(x)                  (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1I2CEnabledFlag = _TRUE)
#define CLR_TYPE_C_5400_I2C_ENABLED_FLG(x)                  (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1I2CEnabledFlag = _FALSE)

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoAltModeFlag)
#define SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoAltModeFlag = _TRUE)
#define CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoAltModeFlag = _FALSE)

#define GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(x)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag)
#define SET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(x)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag = _TRUE)
#define CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(x)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag = _FALSE)

#define GET_TYPE_C_5400_LENOVO_VDM_RECEIVED(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1LenovoVdmReceived)
#define SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1LenovoVdmReceived = _TRUE)
#define CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1LenovoVdmReceived = _FALSE)

#define GET_TYPE_C_5400_LENOVO_DOCK_EVENT(x)                (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucLenovoDockingEvent)
#define SET_TYPE_C_5400_LENOVO_DOCK_EVENT(x, y)             (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucLenovoDockingEvent = (y))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Type-C Get 5400 Info
//--------------------------------------------------
typedef enum
{
    _GET_5400_CC_ATTACH = 0x00,
    _GET_5400_ALT_MODE_READY = 0x01,
    _GET_5400_ORIENTATION = 0x02,
    _GET_5400_DATA_ROLE = 0x03,
    _GET_5400_PIN_ASSIGNMENT = 0x04,
    _GET_5400_CONNECT_FUJITSU = 0x05,
    _GET_5400_CABLE_VID = 0x06,
    _GET_5400_CABLE_PID = 0x07,
    _GET_5400_LENOVO_ALT_MODE_STATUS = 0x08,
    _GET_5400_LENOVO_DEVICE_TYPE = 0x09,
    _GET_5400_LENOVO_SYSTEM_EVENT = 0x0A,
    _SET_5400_CC_DISCONNECT = 0x0B,
    _SET_5400_POWER_MODE = 0x0C,
}Enum5400InfoType;

typedef struct
{
    EnumTypeCDataRole enumDataRole;
    EnumTypeCPowerRole enumPowerRole;
    BYTE ucPortPartnerFlag;
    BYTE ucI2CWrExtendInfo;
#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
    StructTypeCUserPDO pstSrcPdo[7];
    StructTypeCUserPDO pstPartnerSrcPdo[7];
    WORD usPdoStatusVoltage;
    WORD usPdoStatusCurrent;
    BYTE ucReqInfo0;
    BYTE ucReqInfo1;
    BYTE ucReqInfo2;
    BYTE b3ReqObjPos : 3;
    BYTE b3NumOfSrcCap : 3;
    BYTE b3NumOfPartnerSrcCap : 3;
#endif
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    BYTE b1DetectLenovoAltModeFlag : 1;
    BYTE b1DetectLenovoDeviceTypeFlag : 1;
    BYTE ucLenovoDockingEvent;
    BYTE b1LenovoVdmReceived : 1;
#endif
    BYTE b1DetectStatusFlag : 1;
    BYTE b1I2CEnabledFlag : 1;
}StructPortController5400Info;

//****************************************************************************
// CODE TABLES
//****************************************************************************
// Write Command && Read Command
#if(_TYPE_C_RTS5400_SERIES_SPEC_VER_SEL >= _RTS5400_SERIES_FW_SPEC_VERSION_V0D7)
code StructSMBusWRGetICStatus tSMBusWrCmdGetICStatus[1] = {{0x3A, 0x03, 0x08, 0x00, 0x01}};
code StructSMBusRDGetICStatus tSMBusRdCmdGetICStatus[1] = {{0x80, 0x02, 0x00}};

code StructSMBusWRReadDPLanes tSMBusWrCmdReadDpCapVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0C}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDpCapVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0C}};
code StructSMBusRDReadDPLanesCfg tSMBusRdCmdDPCapVdo[1] = {{0x80, 0x05, 0x45, 0x04, 0x00, 0x00}};

code StructSMBusWRGetStatus tSMBusWrGetStatus[1] = {{0x09, 0x03, 0x00, 0x00, 0x0E}};
code StructSMBusRDGetStatus tSMBusRDGetStatus[1] = {{0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPCfgVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0E}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPCfgVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0E}};
code StructSMBusRDReadDPLanesCfg tSMBusRdCmdReadDPCfgVdo[1] = {{0x80, 0x05, 0x06, 0x04, 0x00, 0x00}};
#else
code StructSMBusWRGetICStatus tSMBusWrCmdGetICStatus[1] = {{0x3A, 0x01, 0x14}};
code StructSMBusRDGetICStatus tSMBusRdCmdGetICStatus[1] = {{0x80, 0x15, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif

code StructSMBusWRSetDPLanes tSMBusWrCmdSetDPCapVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0C, 0x45, 0x00, 0x08, 0x00}};

code StructSMBusWRSetDPLanes tSMBusWrCmdSetDPCfgVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0E, 0x05, 0x04, 0x00, 0x00}};

code StructSMBusWRSetDPMultiFunction tSMBusWrCmdSetDPMultiFunction[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0D, 0x18, 0x00, 0x00, 0x00}};
code StructSMBusWRReadDPMultiFunction tSMBusWrCmdReadDPMultiFunction[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0D}};
code StructSMBusRDReadDPMultiFunction tSMBusRdCmdDPMultiFunction[1] = {{0x80, 0x05, 0x08, 0x00, 0x00, 0x00}};

code StructSMBusWRReconnect tSMBusWrCmdSetReconnect[1] = {{0x08, 0x03, 0x1F, 0x00, 0x01}};
code StructSMBusWRDisconnect tSMBusWrCmdSetDisconnect[1] = {{0x08, 0x02, 0x23, 0x00}};
code StructSMBusWROperation tSMBusWrCmdSetOperationMode[1] = {{0x08, 0x03, 0x1D, 0x00, 0x00}};

code StructSMBusRDCommandReadyStatus tSMBusRdCmdCommandReadyStatus[1] = {{0x00, 0x00}};

code StructSMBusRDReadDPLanes tSMBusRdCmdDPlanes[1] = {{0x80, 0x05, 0x45, 0x00, 0x08, 0x00}};

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
code StructSMBusWRGetPdo tSMBusWrCmdGetSelfSrcPdo[1] = {{0x08, 0x03, 0x83, 0x00, 0xE1}};
code StructSMBusWRGetPdo tSMBusWrCmdGetPartnerSrcPdo[1] = {{0x08, 0x03, 0x83, 0x00, 0xE3}};
code StructSMBusRDGetPdo tSMBusRdCmdGetPdo[1] = {{0x80, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif

code StructSMBusWRGetCableInfo tSMBusWrCmdGetCableInfo[1] = {{0x08, 0x01, 0xA8}};
code StructSMBusRDGetCableInfo tSMBusRdCmdGetCableInfo[1] = {{0x80, 0x05, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWREnableVenderCommand tSMBusWrCmdEnableVenderCommand[1] = {{0x01, 0x03, 0xDA, 0x0B, 0x01}};

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
code StructSMBusWRGetLenovoInfo tSMBusWrCmdGetLenovoInfo[1] = {{0x08, 0x02, 0xE0, 0x00}};
code StructSMBusRDGetLenovoInfo tSMBusRdCmdGetLenovoInfo[1] = {{0x80, 0x03, 0x00, 0x00}};

code StructSMBusWRGetLenovoVdm tSMBusWrCmdGetLenovoVdm[1] = {{0x08, 0x02, 0x99, 0x00}};
code StructSMBusRDGetLenovoVdm tSMBusRdCmdGetLenovoVdm[1] = {{0x80, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSendLenovoVdmAck tSMBusWrCmdSendLenovoVdmAck[1] = {{0x08, 0x0E, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSendLenovoVdmReq tSMBusWrCmdSendLenovoVdmReq[1] = {{0x08, 0x06, 0x19, 0x00, 0x00, 0x00, 0xEF, 0x17}};
#endif

code StructSMBusWRAckCCCI tSMBusWrCmdAckCCCI[1] = {{0x0A, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPortController5400Info g_pstTypeC5400Info[_TYPE_C_PORT_VALID];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit UserCommonPortControllerGet5400I2CEnabledFlag(BYTE ucInputPort);
void UserCommonPortControllerSet5400I2CEnabledFlag(BYTE ucInputPort);
void UserCommonPortControllerClr5400I2CEnabledFlag(BYTE ucInputPort);
bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void);
#endif
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void);
#endif
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void);
#endif
#endif

void UserCommonPortController5400Reset(BYTE ucInputPort);
void UserCommonPortControllerSet5400StatusDetection(BYTE ucInputPort);
void UserCommonPortControllerUpdate5400Status(BYTE ucInputPort);
bit UserCommonPortControllerUpdate5400PowerRole(BYTE ucInputPort);
EnumTypeCPowerRole UserCommonPortControllerGet5400PowerRole(BYTE ucInputPort);
BYTE UserCommonPortControllerGet5400PortPartnerFlag(BYTE ucInputPort);
#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
bit UserCommonPortControllerUpdate5400SrcPdo(BYTE ucInputPort);
bit UserCommonPortControllerUpdate5400PartnerSrcPdo(BYTE ucInputPort);
void UserCommonPortControllerUpdate5400PdoStatus(BYTE ucInputPort);
BYTE UserCommonPortControllerGet5400PartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
StructTypeCUserPDO UserCommonPortControllerGet5400PartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
void UserCommonPortControllerGet5400PdoStatus(BYTE ucInputPort, WORD *pusVoltage, WORD *pusCurrent);
StructTypeCUserPDO UserCommonPortControllerGet5400RequestedSrcPdo(BYTE ucInputPort);
#endif

#if(_EXT_PORT_CTRL_LANE_SWAP_BY_SCALER_SUPPORT == _ON)
EnumTypeCOrientation UserCommonPortControllerGet5400Orientation(BYTE ucInputPort);
#endif
bit UserCommonPortControllerGet5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
void UserCommonPortController5400CcFunctionControl(BYTE ucInputPort, EnumTypeCCcFunction enumCcFunction);
void UserCommonPortControllerSet5400TargetPowerMode(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort);
bit UserCommonPortControllerSet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType);
bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo);
bit UserCommonPortControllerWrite5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType);
bit UserCommonPortControllerRead5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType);
EnumTypeCPinCfgType UserCommonPortControllerDecode5400PinAssignment(BYTE ucPdInfo);

bit UserCommonPortController5400Reconnect(BYTE ucInputPort);
bit UserCommonPortControllerConfig5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
bit UserCommonPortControllerConfig5400MultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
void UserCommonPortControllerSet5400LenovoAltModeDetection(BYTE ucInputPort);
void UserCommonPortControllerSet5400LenovoDeviceTypeDetection(BYTE ucInputPort);
EnumTypeCLenovoAltModeStatus UserCommonPortControllerGet5400LenovoAltModeReady(BYTE ucInputPort);
EnumTypeCLenovoDeviceType UserCommonPortControllerGet5400LenovoDeviceType(BYTE ucInputPort);
StructTypeCLenovoSysEvent UserCommonPortControllerGet5400LenovoSystemEvent(BYTE ucInputPort);
void UserCommonPortControllerSet5400LenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
bit UserCommonPortControllerCheck5400LenovoDockingEventBusy(BYTE ucInputPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get 5400 Port Controller I2C Communication Enabled Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
bit UserCommonPortControllerGet5400I2CEnabledFlag(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            return GET_TYPE_C_5400_I2C_ENABLED_FLG(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            return GET_TYPE_C_5400_I2C_ENABLED_FLG(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            return GET_TYPE_C_5400_I2C_ENABLED_FLG(_D6_INPUT_PORT);

            break;
#endif

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set 5400 Port Controller I2C Communication Enabled Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400I2CEnabledFlag(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            SET_TYPE_C_5400_I2C_ENABLED_FLG(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            SET_TYPE_C_5400_I2C_ENABLED_FLG(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            SET_TYPE_C_5400_I2C_ENABLED_FLG(_D6_INPUT_PORT);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clr 5400 Port Controller I2C Communication Enabled Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerClr5400I2CEnabledFlag(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            CLR_TYPE_C_5400_I2C_ENABLED_FLG(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            CLR_TYPE_C_5400_I2C_ENABLED_FLG(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            CLR_TYPE_C_5400_I2C_ENABLED_FLG(_D6_INPUT_PORT);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable 5400 Port Controller Vender Command
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdEnableVenderCommand[0].ucCommandCode, 1, tSMBusWrCmdEnableVenderCommand[0].ucDataLength + 1, &(tSMBusWrCmdEnableVenderCommand[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D0 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ATTACH;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D0_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        if(SysTypeCGetCcAttach(_D0_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D0_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _GET_5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D0 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D0 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D0_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        if(SysTypeCGetAltModeReady(_D0_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D0_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _GET_5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D0 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif  // End of #if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D1 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Current Lit Up Port is _D1_INPUT_PORT,
    if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TRUE;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D1_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        if(SysTypeCGetCcAttach(_D1_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D1_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _GET_5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D1 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D1 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D1_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        if(SysTypeCGetAltModeReady(_D1_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D1_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _GET_5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D1 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif // End of #if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D6 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Current Lit Up Port is _D6_INPUT_PORT,
    if((SysSourceGetInputPort() == _D6_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ATTACH;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D6_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        if(SysTypeCGetCcAttach(_D6_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D6_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _GET_5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D6 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D6 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D6_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D6_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        if(SysTypeCGetAltModeReady(_D6_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D6_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _GET_5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D6 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif // End of #if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

//--------------------------------------------------
// Description  : 5400 Port Controller Info Reset
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortController5400Reset(BYTE ucInputPort)
{
    SET_TYPE_C_5400_POWER_ROLE(ucInputPort, _TYPE_C_POWER_ROLE_NONE);
    SET_TYPE_C_5400_PORT_PARTNER_FLAG(ucInputPort, 0x00);
    SET_TYPE_C_5400_DETECT_STATUS(ucInputPort);

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
    CLR_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort);
    CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(ucInputPort);
    CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(ucInputPort);
    CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(ucInputPort);
    SET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort, 0);
    SET_TYPE_C_5400_PDO_STATUS_VOL(ucInputPort, 0);
    SET_TYPE_C_5400_PDO_STATUS_CUR(ucInputPort, 0);
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    // Reset Lenovo Alt Mode Info
    SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(ucInputPort);
    SET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(ucInputPort);
    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(ucInputPort);
    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Set 5400 Port Controller Status I2C Detection Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400StatusDetection(BYTE ucInputPort)
{
    SET_TYPE_C_5400_DETECT_STATUS(ucInputPort);
}

//--------------------------------------------------
// Description  : Update 5400 Port Controller Status (Including Power Role and PDO Info)
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerUpdate5400Status(BYTE ucInputPort)
{
    if(SysTypeCGetCcAttach(ucInputPort) == _FALSE)
    {
        return;
    }

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            // Update Power Status Every _TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME (500ms/ 1000ms/ 1500ms/ 2000ms)
            if(GET_TYPE_C_5400_DETECT_STATUS(_D0_INPUT_PORT) == _FALSE)
            {
                return;
            }

            // Clr Detect Power Status Flag, Wait At Least _TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME (500ms/ 1000ms/ 1500ms/ 2000ms) to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_STATUS(_D0_INPUT_PORT);
            ScalerTimerActiveTimerEvent(_TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME, _SYSTEM_TIMER_EVENT_D0_TYPE_C_STATUS_DETECT);

            // 1. Update 5400 Power Role / Port Partner Flag / Currently Negotiated Request Info and Set to Macro
            if(UserCommonPortControllerUpdate5400PowerRole(_D0_INPUT_PORT) == _FAIL)
            {
                return;
            }

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
            // 2. Update SRC PDO and Set to Macro
            if(GET_TYPE_C_5400_POWER_ROLE(_D0_INPUT_PORT) == _TYPE_C_POWER_SRC)
            {
                // Update RTS SRC PDO and Set to Macro
                if(UserCommonPortControllerUpdate5400SrcPdo(_D0_INPUT_PORT) == _FAIL)
                {
                    return;
                }
            }
            else if(GET_TYPE_C_5400_POWER_ROLE(_D0_INPUT_PORT) == _TYPE_C_POWER_SNK)
            {
                // Update Partner SRC PDO and Set to Macro
                if(UserCommonPortControllerUpdate5400PartnerSrcPdo(_D0_INPUT_PORT) == _FAIL)
                {
                    return;
                }
            }

            // 3. Get Negotiated Voltage & Current and Set to Macro
            UserCommonPortControllerUpdate5400PdoStatus(_D0_INPUT_PORT);
#endif

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            // Update Power Status Every _TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME (500ms/ 1000ms/ 1500ms/ 2000ms)
            if(GET_TYPE_C_5400_DETECT_STATUS(_D1_INPUT_PORT) == _FALSE)
            {
                return;
            }

            // Clr Detect Power Status Flag, Wait At Least _TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME (500ms/ 1000ms/ 1500ms/ 2000ms) to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_STATUS(_D1_INPUT_PORT);
            ScalerTimerActiveTimerEvent(_TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME, _SYSTEM_TIMER_EVENT_D1_TYPE_C_STATUS_DETECT);

            // 1. Update 5400 Power Role / Port Partner Flag / Currently Negotiated Request Info and Set to Macro
            if(UserCommonPortControllerUpdate5400PowerRole(_D1_INPUT_PORT) == _FAIL)
            {
                return;
            }

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
            // 2. Update SRC PDO and Set to Macro
            if(GET_TYPE_C_5400_POWER_ROLE(_D1_INPUT_PORT) == _TYPE_C_POWER_SRC)
            {
                // Update RTS SRC PDO and Set to Macro
                if(UserCommonPortControllerUpdate5400SrcPdo(_D1_INPUT_PORT) == _FAIL)
                {
                    return;
                }
            }
            else if(GET_TYPE_C_5400_POWER_ROLE(_D1_INPUT_PORT) == _TYPE_C_POWER_SNK)
            {
                // Update Partner SRC PDO and Set to Macro
                if(UserCommonPortControllerUpdate5400PartnerSrcPdo(_D1_INPUT_PORT) == _FAIL)
                {
                    return;
                }
            }

            // 3. Get Negotiated Voltage & Current and Set to Macro
            UserCommonPortControllerUpdate5400PdoStatus(_D1_INPUT_PORT);
#endif

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            // Update Power Status Every _TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME (500ms/ 1000ms/ 1500ms/ 2000ms)
            if(GET_TYPE_C_5400_DETECT_STATUS(_D6_INPUT_PORT) == _FALSE)
            {
                return;
            }

            // Clr Detect Power Status Flag, Wait At Least _TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME (500ms/ 1000ms/ 1500ms/ 2000ms) to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_STATUS(_D6_INPUT_PORT);
            ScalerTimerActiveTimerEvent(_TYPE_C_RTS5400_SERIES_STATUS_POLL_TIME, _SYSTEM_TIMER_EVENT_D6_TYPE_C_STATUS_DETECT);

            // 1. Update 5400 Power Role / Port Partner Flag / Currently Negotiated Request Info and Set to Macro
            if(UserCommonPortControllerUpdate5400PowerRole(_D6_INPUT_PORT) == _FAIL)
            {
                return;
            }

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
            // 2. Update SRC PDO and Set to Macro
            if(GET_TYPE_C_5400_POWER_ROLE(_D6_INPUT_PORT) == _TYPE_C_POWER_SRC)
            {
                // Update RTS SRC PDO and Set to Macro
                if(UserCommonPortControllerUpdate5400SrcPdo(_D6_INPUT_PORT) == _FAIL)
                {
                    return;
                }
            }
            else if(GET_TYPE_C_5400_POWER_ROLE(_D6_INPUT_PORT) == _TYPE_C_POWER_SNK)
            {
                // Update Partner SRC PDO and Set to Macro
                if(UserCommonPortControllerUpdate5400PartnerSrcPdo(_D6_INPUT_PORT) == _FAIL)
                {
                    return;
                }
            }

            // 3. Get Negotiated Voltage & Current and Set to Macro
            UserCommonPortControllerUpdate5400PdoStatus(_D6_INPUT_PORT);
#endif

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Update 5400 Port Controller Power Role
// Input Value  : ucInputPort --> Input Port
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerUpdate5400PowerRole(BYTE ucInputPort)
{
    StructSMBusWRGetStatus stGetStatus;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    memcpy(&stGetStatus, &tSMBusWrGetStatus[0], tSMBusWrGetStatus[0].ucDataLength + 2);

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
    stGetStatus.ucOffset = 0x04;
    stGetStatus.ucStatusLen = 0x06;
#else
    stGetStatus.ucOffset = 0x04;
    stGetStatus.ucStatusLen = 0x02;
#endif

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stGetStatus.ucCommandCode, 1, stGetStatus.ucDataLength + 1, &stGetStatus.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRDGetStatus[0].ucCommandCode, 1, stGetStatus.ucStatusLen + 1, &(g_unSMBusRdDataPool.stRdGetStatus.ucByte3), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    g_unSMBusRdDataPool.stRdGetStatus.ucCommandCode = tSMBusRDGetStatus[0].ucCommandCode;

    // 1.1 Get RTS Power Role and Set to Macro
    // Power Direction Field is Only Valid when Connect Status Field is set to one
    if((g_unSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT7)) == _BIT7)
    {
        if((g_unSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT6)) == _BIT6)
        {
            SET_TYPE_C_5400_POWER_ROLE(ucInputPort, _TYPE_C_POWER_SRC);
        }
        else
        {
            SET_TYPE_C_5400_POWER_ROLE(ucInputPort, _TYPE_C_POWER_SNK);
        }
    }
    else
    {
        SET_TYPE_C_5400_POWER_ROLE(ucInputPort, _TYPE_C_POWER_ROLE_NONE);
    }

    // 1.2 Get Port Partner Flag and Set to Macro
    // Port Partner Flag Field is Only Valid when Connect Status Field is set to one
    if((g_unSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT7)) == _BIT7)
    {
        SET_TYPE_C_5400_PORT_PARTNER_FLAG(ucInputPort, g_unSMBusRdDataPool.stRdGetStatus.ucByte5_PortPartnerFlag);
    }
    else
    {
        SET_TYPE_C_5400_PORT_PARTNER_FLAG(ucInputPort, 0x00);
    }

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
    // 1.3 Get Currently Negotiated Request Info and Set to Macro
    // RDO Field is Only Valid when Connect Status Field is Set to One and Power Operation Mode Field is Set to PD
    // Byte4[7] Connect Status (Attached:1 / Unattached:0), Byte4[3:1] Port Operation Mode (PD:3)
    if(((g_unSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT7)) == _BIT7) && ((g_unSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT3 | _BIT2 | _BIT1)) == (_BIT2 | _BIT1)))
    {
        SET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort, ((g_unSMBusRdDataPool.stRdGetStatus.ucByte9 & (_BIT6 | _BIT5 | _BIT4)) >> 4));

        // Request Data Object[7:0]
        SET_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(ucInputPort, g_unSMBusRdDataPool.stRdGetStatus.ucByte6);

        // Request Data Object[15:8]
        SET_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(ucInputPort, g_unSMBusRdDataPool.stRdGetStatus.ucByte7);

        // Request Data Object[23:16]
        SET_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(ucInputPort, g_unSMBusRdDataPool.stRdGetStatus.ucByte8);
    }
    else
    {
        CLR_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort);
        CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(ucInputPort);
        CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(ucInputPort);
        CLR_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(ucInputPort);
        SET_TYPE_C_5400_PDO_STATUS_VOL(ucInputPort, 0);
        SET_TYPE_C_5400_PDO_STATUS_CUR(ucInputPort, 0);
    }
#endif

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Return 5400 Port Controller Power Role
// Input Value  : ucInputPort --> Input Port
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_ROLE_NONE / _TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole UserCommonPortControllerGet5400PowerRole(BYTE ucInputPort)
{
    return GET_TYPE_C_5400_POWER_ROLE(ucInputPort);
}

//--------------------------------------------------
// Description  : Return 5400 Port Controller Port Partner Flag (Current Operating Mode)
// Input Value  : ucInputPort --> Input Port
// Output Value : Port Partner Flag (BIT0 : USB / BIT1 : Alt Mode)
//--------------------------------------------------
BYTE UserCommonPortControllerGet5400PortPartnerFlag(BYTE ucInputPort)
{
    // BIT0 : Port Controller is Operating in USB Mode
    // BIT1 : Port Controller is operating in Alt Mode
    return GET_TYPE_C_5400_PORT_PARTNER_FLAG(ucInputPort);
}

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Update 5400 Port Controller Src PDOs
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerUpdate5400SrcPdo(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);
    BYTE ucIndex = 0;
    BYTE pucData[30];
    memset(pucData, 0, sizeof(pucData));

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetSelfSrcPdo[0].ucCommandCode, 1, tSMBusWrCmdGetSelfSrcPdo[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetSelfSrcPdo[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetPdo[0].ucCommandCode, 1, tSMBusRdCmdGetPdo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetPdo.ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    g_unSMBusRdDataPool.stRdGetPdo.ucCommandCode = tSMBusRdCmdGetPdo[0].ucCommandCode;

    // Set Number Of RTS SRC PDO
    SET_TYPE_C_5400_SRC_CAP_CNT(ucInputPort, g_unSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);

    memcpy(pucData, &g_unSMBusRdDataPool.stRdGetPdo, g_unSMBusRdDataPool.stRdGetPdo.ucDataLength + 2);

    for(ucIndex = 0; ucIndex < GET_TYPE_C_5400_SRC_CAP_CNT(ucInputPort); ucIndex++)
    {
        // Set PDO Type
        SET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, ucIndex, ((pucData[ucIndex * 4 + 5] & (_BIT7 | _BIT6)) >> 6));

        if(GET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, ucIndex) == _PD_FIX_SUPPLY_PDO)
        {
            // Set Peak Current
            SET_TYPE_C_5400_SRC_CAP_PEAK_CUR(ucInputPort, ucIndex, ((pucData[ucIndex * 4 + 4] & (_BIT5 | _BIT4)) >> 4));

            // Set PDO Voltage (Unit 50mV to 100mV) and Current (Unit 10mA)
            SET_TYPE_C_5400_SRC_CAP_VOL_MAX(ucInputPort, ucIndex, (BYTE)(((((WORD)(pucData[ucIndex * 4 + 4] & 0x0F)) << 6) | (((WORD)(pucData[ucIndex * 4 + 3] & 0xFC)) >> 2)) / 2));
            SET_TYPE_C_5400_SRC_CAP_VOL_MIN(ucInputPort, ucIndex, GET_TYPE_C_5400_SRC_CAP_VOL_MAX(ucInputPort, ucIndex));
            SET_TYPE_C_5400_SRC_CAP_CUR(ucInputPort, ucIndex, ((((WORD)(pucData[ucIndex * 4 + 3] & 0x03)) << 8) | ((WORD)pucData[ucIndex * 4 + 2])));
        }
        else if(GET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, ucIndex) == _PD_3_PROGRAMMABLE_PDO)
        {
            // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
            SET_TYPE_C_5400_SRC_CAP_VOL_MAX(ucInputPort, ucIndex, (((pucData[ucIndex * 4 + 5] & 0x01) << 7) | ((pucData[ucIndex * 4 + 4] & 0xFE) >> 1)));
            SET_TYPE_C_5400_SRC_CAP_VOL_MIN(ucInputPort, ucIndex, pucData[ucIndex * 4 + 3]);
            SET_TYPE_C_5400_SRC_CAP_CUR(ucInputPort, ucIndex, pucData[ucIndex * 4 + 2] & 0x7F);
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Update 5400 Port Controller Partner Src PDOs
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerUpdate5400PartnerSrcPdo(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);
    BYTE ucIndex = 0;
    BYTE pucData[30];
    memset(pucData, 0, sizeof(pucData));

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetPartnerSrcPdo[0].ucCommandCode, 1, tSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetPdo[0].ucCommandCode, 1, tSMBusRdCmdGetPdo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetPdo.ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    g_unSMBusRdDataPool.stRdGetPdo.ucCommandCode = tSMBusRdCmdGetPdo[0].ucCommandCode;

    // Set Number Of Partner SRC PDO
    SET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort, g_unSMBusRdDataPool.stRdGetPdo.ucDataLength / 4);

    memcpy(pucData, &g_unSMBusRdDataPool.stRdGetPdo, g_unSMBusRdDataPool.stRdGetPdo.ucDataLength + 2);

    for(ucIndex = 0; ucIndex < GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort); ucIndex++)
    {
        // Set PDO Type
        SET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucIndex, ((pucData[ucIndex * 4 + 5] & (_BIT7 | _BIT6)) >> 6));

        if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucIndex) == _PD_FIX_SUPPLY_PDO)
        {
            // Set Peak Current
            SET_TYPE_C_5400_PARTNER_SRC_CAP_PEAK_CUR(ucInputPort, ucIndex, ((pucData[ucIndex * 4 + 4] & (_BIT5 | _BIT4)) >> 4));

            // Set PDO Voltage (Unit 50mV to 100mV) and Current (Unit 10mA)
            SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucIndex, (BYTE)(((((WORD)(pucData[ucIndex * 4 + 4] & 0x0F)) << 6) | (((WORD)(pucData[ucIndex * 4 + 3] & 0xFC)) >> 2)) / 2));
            SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(ucInputPort, ucIndex, GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucIndex));
            SET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, ucIndex, ((((WORD)(pucData[ucIndex * 4 + 3] & 0x03)) << 8) | ((WORD)pucData[ucIndex * 4 + 2])));
        }
        else if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucIndex) == _PD_3_PROGRAMMABLE_PDO)
        {
            // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
            SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucIndex, (((pucData[ucIndex * 4 + 5] & 0x01) << 7) | ((pucData[ucIndex * 4 + 4] & 0xFE) >> 1)));
            SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(ucInputPort, ucIndex, pucData[ucIndex * 4 + 3]);
            SET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, ucIndex, pucData[ucIndex * 4 + 2] & 0x7F);
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Update 5400 Port Controller PDO Status
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerUpdate5400PdoStatus(BYTE ucInputPort)
{
    if(GET_TYPE_C_5400_POWER_ROLE(ucInputPort) == _TYPE_C_POWER_SRC)
    {
        // Check if Object Position is Valid
        if((GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) > 0) && (GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) <= GET_TYPE_C_5400_SRC_CAP_CNT(ucInputPort)))
        {
            if(GET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                // Convert Voltage From 100mV to 10mV
                SET_TYPE_C_5400_PDO_STATUS_VOL(ucInputPort, (WORD)GET_TYPE_C_5400_SRC_CAP_VOL_MAX(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) * 10);

                // Current in 10mA
                SET_TYPE_C_5400_PDO_STATUS_CUR(ucInputPort, ((((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(ucInputPort) & 0x03)) << 8) | ((WORD)GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(ucInputPort))));
            }
            else if(GET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Convert Voltage From 20mV to 10mV
                SET_TYPE_C_5400_PDO_STATUS_VOL(ucInputPort, (((((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(ucInputPort) & 0x0F)) << 7) | (((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(ucInputPort) & 0xFE)) >> 1)) * 2));

                // Convert Current From 50mA to 10mA
                SET_TYPE_C_5400_PDO_STATUS_CUR(ucInputPort, ((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(ucInputPort) & 0x7F) * 5));
            }
        }
    }
    else if(GET_TYPE_C_5400_POWER_ROLE(ucInputPort) == _TYPE_C_POWER_SNK)
    {
        // Check if Object Position is Valid
        if((GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) > 0) && (GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) <= GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort)))
        {
            if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                // Convert Voltage From 100mV to 10mV
                SET_TYPE_C_5400_PDO_STATUS_VOL(ucInputPort, (WORD)GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) * 10);

                // Current in 10mA
                SET_TYPE_C_5400_PDO_STATUS_CUR(ucInputPort, ((((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(ucInputPort) & 0x03)) << 8) | ((WORD)GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(ucInputPort))));
            }
            else if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Convert Voltage From 20mV to 10mV
                SET_TYPE_C_5400_PDO_STATUS_VOL(ucInputPort, (((((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_2(ucInputPort) & 0x0F)) << 7) | (((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_1(ucInputPort) & 0xFE)) >> 1)) * 2));

                // Convert Current From 50mA to 10mA
                SET_TYPE_C_5400_PDO_STATUS_CUR(ucInputPort, ((WORD)(GET_TYPE_C_5400_NEGOTIATED_REQ_INFO_0(ucInputPort) & 0x7F) * 5));
            }
        }
    }
}

//--------------------------------------------------
// Description  : Return 5400 Port Controller Number of Partner Src/Snk PDOs
// Input Value  : ucInputPort, enumPowerRole(Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE UserCommonPortControllerGet5400PartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        ucPdoCnt = GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // To-Do Daisy : Update Number of Port Partner SNK PDO if Needed
        ucPdoCnt = 0;
    }

    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Return 5400 Port Controller Partner Source/Sink PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonPortControllerGet5400PartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort)))
        {
            stTypeCPartnerPdo.enumPdoType = GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucPdoIndex - 1);

            if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPartnerPdo.enumPeakCurrent = GET_TYPE_C_5400_PARTNER_SRC_CAP_PEAK_CUR(ucInputPort, ucPdoIndex - 1);

                // Get Current in Macro (Unit = 10mA)
                stTypeCPartnerPdo.usMaxCurrent = GET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, ucPdoIndex - 1);
            }
            else if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCPartnerPdo.usMaxCurrent = (GET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, ucPdoIndex - 1) * 5);
            }

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCPartnerPdo.ucMaxVoltage = GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucPdoIndex - 1);
            stTypeCPartnerPdo.ucMinVoltage = GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(ucInputPort, ucPdoIndex - 1);
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // To-Do Daisy : Update Port Partner SNK PDO if Needed
    }

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Return 5400 Port Controller PDO Status
// Input Value  : ucInputPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerGet5400PdoStatus(BYTE ucInputPort, WORD *pusVoltage, WORD *pusCurrent)
{
    // Voltage in 10mV
    *pusVoltage = GET_TYPE_C_5400_PDO_STATUS_VOL(ucInputPort);

    // Current in 10mA
    *pusCurrent = GET_TYPE_C_5400_PDO_STATUS_CUR(ucInputPort);
}

//--------------------------------------------------
// Description  : Return 5400 Port Controller Current Source PDO that Sink Request
// Input Value  : ucInputPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonPortControllerGet5400RequestedSrcPdo(BYTE ucInputPort)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    if(GET_TYPE_C_5400_POWER_ROLE(ucInputPort) == _TYPE_C_POWER_SRC)
    {
        if((GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) > 0) && (GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) <= GET_TYPE_C_5400_SRC_CAP_CNT(ucInputPort)))
        {
            stTypeCSrcPdo.enumPdoType = GET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);

            if(GET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCSrcPdo.enumPeakCurrent = GET_TYPE_C_5400_SRC_CAP_PEAK_CUR(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);

                // Get Current in Macro (Unit = 10mA)
                stTypeCSrcPdo.usMaxCurrent = GET_TYPE_C_5400_SRC_CAP_CUR(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);
            }
            else if(GET_TYPE_C_5400_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCSrcPdo.usMaxCurrent = (GET_TYPE_C_5400_SRC_CAP_CUR(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) * 5);
            }

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCSrcPdo.ucMaxVoltage = GET_TYPE_C_5400_SRC_CAP_VOL_MAX(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);
            stTypeCSrcPdo.ucMinVoltage = GET_TYPE_C_5400_SRC_CAP_VOL_MIN(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);
        }
    }
    else if(GET_TYPE_C_5400_POWER_ROLE(ucInputPort) == _TYPE_C_POWER_SNK)
    {
        if((GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) > 0) && (GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) <= GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort)))
        {
            stTypeCSrcPdo.enumPdoType = GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);

            if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCSrcPdo.enumPeakCurrent = GET_TYPE_C_5400_PARTNER_SRC_CAP_PEAK_CUR(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);

                // Get Current in Macro (Unit = 10mA)
                stTypeCSrcPdo.usMaxCurrent = GET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);
            }
            else if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCSrcPdo.usMaxCurrent = (GET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1) * 5);
            }

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCSrcPdo.ucMaxVoltage = GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);
            stTypeCSrcPdo.ucMinVoltage = GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(ucInputPort, GET_TYPE_C_5400_NEGOTIATED_REQ_OBJ_POS(ucInputPort) - 1);
        }
    }

    return stTypeCSrcPdo;
}
#endif // End of #if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)

#if(_EXT_PORT_CTRL_LANE_SWAP_BY_SCALER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Port Controller Orientation to SysTypeC
// Input Value  : ucInputPort
// Output Value : Orientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation UserCommonPortControllerGet5400Orientation(BYTE ucInputPort)
{
    BYTE ucOrientation = 0x00;

    // Get Orientation Info
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _GET_5400_ORIENTATION, &ucOrientation) == _SUCCESS)
    {
        DebugMessageSystem("8. Get 5400 Orientation = ", ucOrientation);

        if(ucOrientation == _TYPE_C_ORIENTATION_UNFLIP)
        {
            return _TYPE_C_ORIENTATION_UNFLIP;
        }
        else if(ucOrientation == _TYPE_C_ORIENTATION_FLIP)
        {
            return _TYPE_C_ORIENTATION_FLIP;
        }
    }
    else
    {
        DebugMessageSystem("8. Get 5400 Orientation By IIC Fail", 0);

        return _TYPE_C_ORIENTATION_NONE;
    }

    return _TYPE_C_ORIENTATION_NONE;
}
#endif

//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Pin Assignment to SysTypeC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonPortControllerGet5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    BYTE ucDataRole = 0x00;
    BYTE ucPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    // Get Data Role Info
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _GET_5400_DATA_ROLE, &ucDataRole) == _FAIL)
    {
        return _FAIL;
    }

    // Set Data Role
    DebugMessageSystem("8. Get 5400 Data Role = ", ucDataRole);

    if(ucDataRole == _TYPE_C_DFP_U)
    {
        SET_TYPE_C_5400_DATA_ROLE(ucInputPort, _TYPE_C_DFP_U);
    }
    else
    {
        SET_TYPE_C_5400_DATA_ROLE(ucInputPort, _TYPE_C_UFP_U);
    }

    // Get Pin Assignment
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _GET_5400_PIN_ASSIGNMENT, &ucPinAssignment) == _FAIL)
    {
        return _FAIL;
    }

    *penumPinAssignment = (EnumTypeCPinCfgType)ucPinAssignment;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Update CC Function Control to 5400 Port Ctrl (Connect / Disconnect)
// Input Value  : ucInputPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void UserCommonPortController5400CcFunctionControl(BYTE ucInputPort, EnumTypeCCcFunction enumCcFunction)
{
    if(enumCcFunction == _TYPE_C_CC_FUNCTION_DISABLE)
    {
        if(UserCommonPortControllerSet5400InfoByI2C(ucInputPort, _SET_5400_CC_DISCONNECT) == _FAIL)
        {
            DebugMessageSystem("8. Set 5400 Port Ctrl CC Disconnect Fail", 0);
        }
    }
    else if(enumCcFunction == _TYPE_C_CC_FUNCTION_ENABLE)
    {
        if(UserCommonPortController5400Reconnect(ucInputPort) == _FAIL)
        {
            DebugMessageSystem("8. Set 5400 Port Ctrl CC Reconnect Fail", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Set Power Mode to 5400 Port Ctrl
// Input Value  : ucInputPort, enumPowerRole
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400TargetPowerMode(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    // Use Rts Extend Info Macro to Store Power Status
    SET_TYPE_C_5400_I2C_WR_EXTEND_INFO(ucInputPort, (BYTE)(enumPowerRole));

    if(UserCommonPortControllerSet5400InfoByI2C(ucInputPort, _SET_5400_POWER_MODE) == _FAIL)
    {
        DebugMessageSystem("8. Set 5400 Port Ctrl Power Mode Fail", 0);
    }
}

//--------------------------------------------------
// Description  : Get Port Controller Slave Address
// Input Value  : ucInputPort --> Input Port
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        case _D1_INPUT_PORT:
            return _D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        case _D6_INPUT_PORT:
            return _D6_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        default:
            break;
    }

    return _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;
}

//--------------------------------------------------
// Description  : Write 5400/5411 Info by SMBus
// Input Value  : ucInputPort, enum5400InfoType
// Output Value : Writing result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerSet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Write Command to Port Ctrl According to Different Required Info Type
    if(UserCommonPortControllerWrite5400Command(ucInputPort, ucSlaveAddr, enum5400InfoType) == _FAIL)
    {
        DebugMessageSystem("8. IIC Write Command to 5400 Fail", 0);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        DebugMessageSystem("8. IIC Polling 5400 Fail", 0);

        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read 5400/5411 Info by SMBus
// Input Value  : None
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Write Command to 5400 According to Different Required Info Type
    if(UserCommonPortControllerWrite5400Command(ucInputPort, ucSlaveAddr, enum5400InfoType) == _FAIL)
    {
        DebugMessageSystem("8. IIC Write Command to 5400 Fail", 0);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        DebugMessageSystem("8. IIC Polling 5400 Fail", 0);

        return _FAIL;
    }

    // Read Info From 5400 According to Different Required Info Type
    if(UserCommonPortControllerRead5400Command(ucInputPort, ucSlaveAddr, enum5400InfoType) == _FAIL)
    {
        DebugMessageSystem("8. IIC Read 5400 Info Fail", 0);

        return _FAIL;
    }

    // Decode Required Info According to Required Info
    switch(enum5400InfoType)
    {
        case _GET_5400_CC_ATTACH:

            if((g_unSMBusRdDataPool.stRdGetICStatus.ucPDTypeCStatus & _BIT3) == _BIT3)
            {
                *pucReadInfo = _TYPE_C_ATTACH;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UNATTACH;
            }

            break;

        case _GET_5400_ALT_MODE_READY:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & 0x07) == 0x06)
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_NOT_READY;
            }

            break;

#if(_EXT_PORT_CTRL_LANE_SWAP_BY_SCALER_SUPPORT == _ON)
        case _GET_5400_ORIENTATION:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte11_Orientation & _BIT5) == _BIT5)
            {
                *pucReadInfo = _TYPE_C_ORIENTATION_UNFLIP;
            }
            else
            {
                *pucReadInfo = _TYPE_C_ORIENTATION_FLIP;
            }

            break;
#endif

        case _GET_5400_DATA_ROLE:

            if(((g_unSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT2) || ((g_unSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT1))
            {
                *pucReadInfo = _TYPE_C_DFP_U;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UFP_U;
            }

            break;

        case _GET_5400_CONNECT_FUJITSU:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & _BIT7) == _BIT7)
            {
                *pucReadInfo = _TRUE;
            }
            else
            {
                *pucReadInfo = _FALSE;
            }

            break;

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        // Required Info Include Lenovo Alt Mode Status and VDM Received Info
        case _GET_5400_LENOVO_ALT_MODE_STATUS:

            // Lenovo Mode Entered or Not
            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & _BIT7) == _BIT7)
            {
                *pucReadInfo = _TYPE_C_LENOVO_ALT_MODE_READY;
            }
            else
            {
                *pucReadInfo = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            // VDM Received or Not
            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte3 & _BIT1) == _BIT1)
            {
                *(pucReadInfo + 1) = _TRUE;
            }
            else
            {
                *(pucReadInfo + 1) = _FALSE;
            }

            break;

        case _GET_5400_LENOVO_DEVICE_TYPE:

            *pucReadInfo = g_unSMBusRdDataPool.stRdGetLenovoInfo.ucByte0_DeviceType;

            break;

        case _GET_5400_LENOVO_SYSTEM_EVENT:

            // Only Response to SOP Get Status Request
            if(((g_unSMBusRdDataPool.stRdGetLenovoVdm.ucByte0 & 0x03) == 0x00) && (g_unSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader0 == 0x10) && (g_unSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader2 == 0xEF) && (g_unSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader3 == 0x17))
            {
                *pucReadInfo = g_unSMBusRdDataPool.stRdGetLenovoVdm.ucByte6;
                *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetLenovoVdm.ucByte7;
            }
            else
            {
                return _FAIL;
            }

            break;
#endif

        case _GET_5400_PIN_ASSIGNMENT:

            *pucReadInfo = (BYTE)(UserCommonPortControllerDecode5400PinAssignment(g_unSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgPinConfig));

            if(*pucReadInfo == _TYPE_C_PIN_ASSIGNMENT_NONE)
            {
                return _FAIL;
            }

            break;

        case _GET_5400_CABLE_VID:

            // ========================= Example ===========================
            // BYTE ucVidInfo[2] = {0x00, 0x00};
            // UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _GET_5400_CABLE_VID, &ucVidInfo);
            // ucVidInfo[0] = Vid_High / ucVidInfo[1] = Vid_Low
            // =============================================================
            *pucReadInfo = g_unSMBusRdDataPool.stRdGetCableInfo.ucVid_High;
            *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetCableInfo.ucVid_Low;

            break;

        case _GET_5400_CABLE_PID:

            *pucReadInfo = g_unSMBusRdDataPool.stRdGetCableInfo.ucPid_High;
            *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetCableInfo.ucPid_Low;

            break;

        default:

            return _FAIL;

            break;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write SMBus Command to 5400
// Input Value  : ucInputPort, ucSlaveAddr, enum5400InfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerWrite5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType)
{
    bit bResult = _FAIL;
    StructSMBusWROperation stSetOperationMode;

    switch(enum5400InfoType)
    {
        case _GET_5400_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetICStatus[0].ucCommandCode, 1, tSMBusWrCmdGetICStatus[0].ucDataLength + 1, &(tSMBusWrCmdGetICStatus[0].ucDataLength), ucInputPort);

            break;

        case _GET_5400_ALT_MODE_READY:
        case _GET_5400_DATA_ROLE:
        case _GET_5400_CONNECT_FUJITSU:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrGetStatus[0].ucCommandCode, 1, tSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrGetStatus[0].ucDataLength), ucInputPort);

            break;

#if(_EXT_PORT_CTRL_LANE_SWAP_BY_SCALER_SUPPORT == _ON)
        case _GET_5400_ORIENTATION:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrGetStatus[0].ucCommandCode, 1, tSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrGetStatus[0].ucDataLength), ucInputPort);

            break;
#endif

        case _SET_5400_CC_DISCONNECT:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdSetDisconnect[0].ucCommandCode, 1, tSMBusWrCmdSetDisconnect[0].ucDataLength + 1, &(tSMBusWrCmdSetDisconnect[0].ucDataLength), ucInputPort);

            break;

        case _SET_5400_POWER_MODE:

            memcpy(&stSetOperationMode, &tSMBusWrCmdSetOperationMode[0], tSMBusWrCmdSetOperationMode[0].ucDataLength + 2);

            if(GET_TYPE_C_5400_I2C_WR_EXTEND_INFO(ucInputPort) == (BYTE)(_TYPE_C_POWER_SRC))
            {
                // Operation Mode = DRP with Try.SRC
                stSetOperationMode.ucByte2 = 0x09;
            }
            else if(GET_TYPE_C_5400_I2C_WR_EXTEND_INFO(ucInputPort) == (BYTE)(_TYPE_C_POWER_SNK))
            {
                // Operation Mode = Sink Only
                stSetOperationMode.ucByte2 = 0x00;
            }

            CLR_TYPE_C_5400_I2C_WR_EXTEND_INFO(ucInputPort);

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, stSetOperationMode.ucCommandCode, 1, stSetOperationMode.ucDataLength + 1, &(stSetOperationMode.ucDataLength), ucInputPort);

            break;

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _GET_5400_LENOVO_ALT_MODE_STATUS:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrGetStatus[0].ucCommandCode, 1, tSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrGetStatus[0].ucDataLength), ucInputPort);

            break;

        case _GET_5400_LENOVO_DEVICE_TYPE:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetLenovoInfo[0].ucCommandCode, 1, tSMBusWrCmdGetLenovoInfo[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetLenovoInfo[0].ucDataLength), ucInputPort);

            break;

        case _GET_5400_LENOVO_SYSTEM_EVENT:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetLenovoVdm[0].ucCommandCode, 1, tSMBusWrCmdGetLenovoVdm[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetLenovoVdm[0].ucDataLength), ucInputPort);

            break;
#endif

        case _GET_5400_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            if(GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_DFP_U)
            {
                bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdReadDPCfgVdoSelf[0].ucCommandCode, 1, tSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength), ucInputPort);
            }
            else
            {
                bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdReadDPCfgVdoPartner[0].ucCommandCode, 1, tSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength), ucInputPort);
            }

            break;

        case _GET_5400_CABLE_VID:
        case _GET_5400_CABLE_PID:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetCableInfo[0].ucCommandCode, 1, tSMBusWrCmdGetCableInfo[0].ucDataLength + 1, &(tSMBusWrCmdGetCableInfo[0].ucDataLength), ucInputPort);

            break;

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Read Info From 5400
// Input Value  : ucInputPort, ucSlaveAddr, enum5400InfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerRead5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType)
{
    bit bResult = _FAIL;

    switch(enum5400InfoType)
    {
        case _GET_5400_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetICStatus[0].ucCommandCode, 1, tSMBusRdCmdGetICStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetICStatus.ucByte7), ucInputPort);

            g_unSMBusRdDataPool.stRdGetICStatus.ucCommandCode = tSMBusRdCmdGetICStatus[0].ucCommandCode;

            break;

        case _GET_5400_ALT_MODE_READY:
        case _GET_5400_DATA_ROLE:
        case _GET_5400_CONNECT_FUJITSU:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRDGetStatus[0].ucCommandCode, 1, tSMBusRDGetStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetStatus.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetStatus.ucCommandCode = tSMBusRDGetStatus[0].ucCommandCode;

            break;

#if(_EXT_PORT_CTRL_LANE_SWAP_BY_SCALER_SUPPORT == _ON)
        case _GET_5400_ORIENTATION:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRDGetStatus[0].ucCommandCode, 1, tSMBusRDGetStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetStatus.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetStatus.ucCommandCode = tSMBusRDGetStatus[0].ucCommandCode;

            break;
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _GET_5400_LENOVO_ALT_MODE_STATUS:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRDGetStatus[0].ucCommandCode, 1, tSMBusRDGetStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetStatus.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetStatus.ucCommandCode = tSMBusRDGetStatus[0].ucCommandCode;

            break;

        case _GET_5400_LENOVO_DEVICE_TYPE:

            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetLenovoInfo[0].ucCommandCode, 1, tSMBusRdCmdGetLenovoInfo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetLenovoInfo.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetLenovoInfo.ucCommandCode = tSMBusRdCmdGetLenovoInfo[0].ucCommandCode;

            break;

        case _GET_5400_LENOVO_SYSTEM_EVENT:

            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetLenovoVdm[0].ucCommandCode, 1, tSMBusRdCmdGetLenovoVdm[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetLenovoVdm.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetLenovoVdm.ucCommandCode = tSMBusRdCmdGetLenovoVdm[0].ucCommandCode;

            break;
#endif

        case _GET_5400_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdReadDPCfgVdo[0].ucCommandCode, 1, tSMBusRdCmdReadDPCfgVdo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdDPlanesCfg.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdDPlanesCfg.ucCommandCode = tSMBusRdCmdReadDPCfgVdo[0].ucCommandCode;

            break;

        case _GET_5400_CABLE_VID:
        case _GET_5400_CABLE_PID:

            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetCableInfo[0].ucCommandCode, 1, tSMBusRdCmdGetCableInfo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetCableInfo.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetCableInfo.ucCommandCode = tSMBusRdCmdGetCableInfo[0].ucCommandCode;

            break;

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Decode Pin Assignment According to 5400 PD Info
// Input Value  : ucPdInfo --> Data Role BYTE From PD Info
// Output Value : EnumTypeCPinCfgtType : _TYPE_C_PIN_ASSIGNMENT_C / D / E
//--------------------------------------------------
EnumTypeCPinCfgType UserCommonPortControllerDecode5400PinAssignment(BYTE ucPdInfo)
{
    // Is it possible to Merge DFP/UFP Flow together, and maybe use "Switch case"
    if((ucPdInfo & _BIT5) == _BIT5) // Pin Assignment F 2 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_F;
    }
    else if((ucPdInfo & _BIT4) == _BIT4) // Pin Assignment E (google cable case)
    {
        return _TYPE_C_PIN_ASSIGNMENT_E;
    }
    else if((ucPdInfo & _BIT3) == _BIT3) // Pin Assignment D 2 lane only, Spec require sink report capability include C  mode
    {
        return _TYPE_C_PIN_ASSIGNMENT_D;
    }
    else if((ucPdInfo & _BIT2) == _BIT2) // Pin Assignment C 4 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_C;
    }
    else
    {
        DebugMessageSystem("8. Decode 5400 Pin Assignment Info Error", ucPdInfo);
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

//--------------------------------------------------
// Description  : Ask User Port Controller to Reconnect
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortController5400Reconnect(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdSetReconnect[0].ucCommandCode, 1, tSMBusWrCmdSetReconnect[0].ucDataLength + 1, &(tSMBusWrCmdSetReconnect[0].ucDataLength), ucInputPort) == _FAIL)
    {
        DebugMessageSystem("ReConnet Fail Wr fail", 1);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 500, ucInputPort) == _FAIL)
    {
        DebugMessageSystem("ReConnet Polling Fail ", 1);

        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Config Pin Assignment to 5400 Port Controller
// Input Value  : ucInputPort / ucPinAssignment / ucDataRole
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfig5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    StructSMBusWRSetDPLanes stDpLaneConfigPar;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_DFP_U)
    {
        memcpy(&stDpLaneConfigPar, &tSMBusWrCmdSetDPCfgVdoSelf[0], tSMBusWrCmdSetDPCfgVdoSelf[0].ucDataLength + 2);

        stDpLaneConfigPar.ucDPCapVDOByte1 = enumPinAssignment;
    }
    else
    {
        memcpy(&stDpLaneConfigPar, &tSMBusWrCmdSetDPCapVdoSelf[0], tSMBusWrCmdSetDPCapVdoSelf[0].ucDataLength + 2);

        stDpLaneConfigPar.ucDPCapVDOByte2 = enumPinAssignment;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stDpLaneConfigPar.ucCommandCode, 1, stDpLaneConfigPar.ucDataLength + 1, &stDpLaneConfigPar.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Config Multi-Function Bit to 5400 Port Controller
// Input Value  : ucInputPort / Nulti-Function Bit
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfig5400MultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    StructSMBusWRSetDPMultiFunction stMultiFunction;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    memcpy(&stMultiFunction, &tSMBusWrCmdSetDPMultiFunction[0], tSMBusWrCmdSetDPMultiFunction[0].ucDataLength + 2);

    // Only UFP Shoud Set Multi Function Preferred Bit
    // BIT[7:5] Reserved, BIT[6] : Exit Mode, BIT[5] USB Config Req, BIT[4] Multi-Function, BIT[3] DP Enable, BIT[2] Power Low, BIT[1:0] Connect Status (b'10 UFP_D Connected)
    if((GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_UFP_U) && (enumMultiFunction == _TYPE_C_MULTI_FUNC_PREFER))
    {
        // Set to Multifunction Prefer
        stMultiFunction.ucDPCapVDOByte0 = 0x1A;
    }
    else
    {
        // Set to Multifunction Not Prefer
        stMultiFunction.ucDPCapVDOByte0 = 0x0A;
    }

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
            {
                // Set to HPD High
                stMultiFunction.ucDPCapVDOByte0 = stMultiFunction.ucDPCapVDOByte0 | (_BIT7);
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
            {
                // Set to HPD High
                stMultiFunction.ucDPCapVDOByte0 = stMultiFunction.ucDPCapVDOByte0 | (_BIT7);
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            if(PCB_D6_HOTPLUG_DETECT() == _D6_HOT_PLUG_HIGH)
            {
                // Set to HPD High
                stMultiFunction.ucDPCapVDOByte0 = stMultiFunction.ucDPCapVDOByte0 | (_BIT7);
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

        default:

            break;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stMultiFunction.ucCommandCode, 1, stMultiFunction.ucDataLength + 1, &stMultiFunction.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
//--------------------------------------------------
// Description  : Set 5400 Port Controller Lenovo Alt Mode I2C Detection Flag
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400LenovoAltModeDetection(BYTE ucInputPort)
{
    SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(ucInputPort);
}

//--------------------------------------------------
// Description  : Set 5400 Port Controller Lenovo Device Type I2C Detection Flag
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400LenovoDeviceTypeDetection(BYTE ucInputPort)
{
    SET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(ucInputPort);
}

//--------------------------------------------------
// Description  : Get 5400 Port Controller Lenovo Alt Mode Ready Info
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus UserCommonPortControllerGet5400LenovoAltModeReady(BYTE ucInputPort)
{
    BYTE pucModeInfo[2] = {0x00, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D0_INPUT_PORT) == _FALSE)
            {
                return SysTypeCGetLenovoAltModeReady(_D0_INPUT_PORT);
            }

            // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
            if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
            {
                // Clr Type-C Detect Lenovo Alt Mode Flag, Wait At Least 50ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D0_INPUT_PORT);
                ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_ALT_MODE_DETECT);
            }

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _GET_5400_LENOVO_ALT_MODE_STATUS, pucModeInfo) == _SUCCESS)
            {
                if(pucModeInfo[0] == _TYPE_C_LENOVO_ALT_MODE_READY)
                {
                    if(pucModeInfo[1] == _TRUE)
                    {
                        SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D0_INPUT_PORT);
                    }
                    else
                    {
                        CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D0_INPUT_PORT);
                    }

                    return _TYPE_C_LENOVO_ALT_MODE_READY;
                }
                else
                {
                    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D0_INPUT_PORT);
                    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(_D0_INPUT_PORT, 0x00);

                    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                DebugMessageSystem("8. Read 5400 D0 Lenovo Alt Mode Ready By IIC Fail", 0);

                return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D1_INPUT_PORT) == _FALSE)
            {
                return SysTypeCGetLenovoAltModeReady(_D1_INPUT_PORT);
            }

            // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
            if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
            {
                // Clr Type-C Detect Lenovo Alt Mode Flag, Wait At Least 50ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D1_INPUT_PORT);
                ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_ALT_MODE_DETECT);
            }

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _GET_5400_LENOVO_ALT_MODE_STATUS, pucModeInfo) == _SUCCESS)
            {
                if(pucModeInfo[0] == _TYPE_C_LENOVO_ALT_MODE_READY)
                {
                    if(pucModeInfo[1] == _TRUE)
                    {
                        SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D1_INPUT_PORT);
                    }
                    else
                    {
                        CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D1_INPUT_PORT);
                    }

                    return _TYPE_C_LENOVO_ALT_MODE_READY;
                }
                else
                {
                    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D1_INPUT_PORT);
                    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(_D1_INPUT_PORT, 0x00);

                    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                DebugMessageSystem("8. Read 5400 D1 Lenovo Alt Mode Ready By IIC Fail", 0);

                return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D6_INPUT_PORT) == _FALSE)
            {
                return SysTypeCGetLenovoAltModeReady(_D6_INPUT_PORT);
            }

            // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
            if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
            {
                // Clr Type-C Detect Lenovo Alt Mode Flag, Wait At Least 50ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D6_INPUT_PORT);
                ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D6_TYPE_C_LENOVO_ALT_MODE_DETECT);
            }

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _GET_5400_LENOVO_ALT_MODE_STATUS, pucModeInfo) == _SUCCESS)
            {
                if(pucModeInfo[0] == _TYPE_C_LENOVO_ALT_MODE_READY)
                {
                    if(pucModeInfo[1] == _TRUE)
                    {
                        SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D6_INPUT_PORT);
                    }
                    else
                    {
                        CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D6_INPUT_PORT);
                    }

                    return _TYPE_C_LENOVO_ALT_MODE_READY;
                }
                else
                {
                    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D6_INPUT_PORT);
                    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(_D6_INPUT_PORT, 0x00);

                    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                DebugMessageSystem("8. Read 5400 D6 Lenovo Alt Mode Ready By IIC Fail", 0);

                return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

        default:

            return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;

            break;
    }

    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type from 5400 Port Controller
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType UserCommonPortControllerGet5400LenovoDeviceType(BYTE ucInputPort)
{
    BYTE ucDeviceType = 0x00;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D0_INPUT_PORT) == _FALSE)
            {
                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D0_INPUT_PORT);
            ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _GET_5400_LENOVO_DEVICE_TYPE, &ucDeviceType) == _SUCCESS)
            {
                return (EnumTypeCLenovoDeviceType)ucDeviceType;
            }
            else
            {
                DebugMessageSystem("8. Read 5400 Lenovo Device Type By IIC Fail", 0);

                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D1_INPUT_PORT) == _FALSE)
            {
                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D1_INPUT_PORT);
            ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _GET_5400_LENOVO_DEVICE_TYPE, &ucDeviceType) == _SUCCESS)
            {
                return (EnumTypeCLenovoDeviceType)ucDeviceType;
            }
            else
            {
                DebugMessageSystem("8. Read 5400 Lenovo Device Type By IIC Fail", 0);

                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D6_INPUT_PORT) == _FALSE)
            {
                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D6_INPUT_PORT);
            ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D6_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _GET_5400_LENOVO_DEVICE_TYPE, &ucDeviceType) == _SUCCESS)
            {
                return (EnumTypeCLenovoDeviceType)ucDeviceType;
            }
            else
            {
                DebugMessageSystem("8. Read 5400 Lenovo Device Type By IIC Fail", 0);

                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

        default:

            return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;

            break;
    }

    return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : ucInputPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent UserCommonPortControllerGet5400LenovoSystemEvent(BYTE ucInputPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};
    StructSMBusWRAckCCCI stAckCCCI;
    StructSMBusWRSendLenovoVdmAck stSendGetStatusAck;
    BYTE pucSystemInfo[2] = {0x00, 0x00};
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(GET_TYPE_C_5400_LENOVO_VDM_RECEIVED(ucInputPort) == _TRUE)
    {
        if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _GET_5400_LENOVO_SYSTEM_EVENT, pucSystemInfo) == _SUCCESS)
        {
            if(pucSystemInfo[0] == 0xFF)
            {
                pucSystemInfo[0] = 0x00;
            }

            if(pucSystemInfo[1] == 0xFF)
            {
                pucSystemInfo[1] = 0x00;
            }

            stLenovoSysEvent.b1SystemEvent = (bit)(pucSystemInfo[0] & _BIT0);
            stLenovoSysEvent.enumSystemState = (pucSystemInfo[0] & (_BIT3 | _BIT2 | _BIT1)) >> 1;
            stLenovoSysEvent.enumSystemPowerMode = (pucSystemInfo[0] & _BIT4) >> 4;
            stLenovoSysEvent.b3SystemReserved = (pucSystemInfo[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5;
            stLenovoSysEvent.ucSystemAcknowlegde = pucSystemInfo[1];

            memcpy(&stSendGetStatusAck, &tSMBusWrCmdSendLenovoVdmAck[0], tSMBusWrCmdSendLenovoVdmAck[0].ucDataLength + 2);

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] Lenovo VID = 0x17EF
            // [15] Struct. VDM = 1, [14:13] VDM Ver = 2b'01 , [12:11] Rsv., [10:8] Obj. Pos = b'000, [7:0] VDM CMD = Get Status Acl (0x50)
            stSendGetStatusAck.ucVdmHeader0 = 0x50;
            stSendGetStatusAck.ucVdmHeader1 = 0xA0;
            stSendGetStatusAck.ucVdmHeader2 = 0xEF;
            stSendGetStatusAck.ucVdmHeader3 = 0x17;

            // -------- Data Obj 1 : Get Status Ack VDO1-----
            // [31:24] Docking Event, [23:16] System Acknowledge
            // [15:8] System Event, [7:0] Docking Acknowledge
            stSendGetStatusAck.ucByte4 = pucSystemInfo[0];
            stSendGetStatusAck.ucByte5 = pucSystemInfo[0];
            stSendGetStatusAck.ucByte6 = pucSystemInfo[1] & 0xFE;
            stSendGetStatusAck.ucByte7 = GET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort);

            // -------- Data Obj 2 : Get Status Ack VDO2-----
            // [31:28] FW Ver. = 0, [27:24] Rsv., [23:16] Power Source
            // [15:12] Function Capability, [11:0] Rsv.
            stSendGetStatusAck.ucByte8 = 0x00;
            stSendGetStatusAck.ucByte9 = 0xC0;
            stSendGetStatusAck.ucByte10 = 0x30;
            stSendGetStatusAck.ucByte11 = 0x00;

            // Ask 5400 to Send Get Status Ack
            // Execute Write Command
            if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stSendGetStatusAck.ucCommandCode, 1, stSendGetStatusAck.ucDataLength + 1, &stSendGetStatusAck.ucDataLength, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            // Polling Write Command Operation Status
            if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            SET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort, 0x00);
            CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(ucInputPort);

            // Cancel Lenovo Alt Mode Urgent Event if System Acknowledge Received
            if((pucSystemInfo[1] & _BIT0) == _BIT0)
            {
                if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _TRUE)
                {
                    CLR_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT();
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_TYPE_C_LENOVO_ALT_MODE_URGENT_EVENT_TIMEOUT);
                }
            }

            memcpy(&stAckCCCI, &tSMBusWrCmdAckCCCI[0], tSMBusWrCmdAckCCCI[0].ucDataLength + 2);

            stAckCCCI.ucByte3 = 0x02;

            // Acknowledge 5400 that VDM Has been Received and Processed
            // Execute Write Command
            if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stAckCCCI.ucCommandCode, 1, stAckCCCI.ucDataLength + 1, &stAckCCCI.ucDataLength, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            // Polling Write Command Operation Status
            if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }
        }
    }

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : ucInputPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400LenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    StructSMBusWRSendLenovoVdmReq stSendAttn;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(stLenovoDockEvent.b1DockingEvent == _TRUE)
    {
        SET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort, (((BYTE)stLenovoDockEvent.b4DockingReserved << 4) | (stLenovoDockEvent.enumDockingPowerSwitch << 2) | ((BYTE)stLenovoDockEvent.b1DockingWolRequest << 1) | (BYTE)stLenovoDockEvent.b1DockingEvent));

        memcpy(&stSendAttn, &tSMBusWrCmdSendLenovoVdmReq[0], tSMBusWrCmdSendLenovoVdmReq[0].ucDataLength + 2);

        stSendAttn.ucVdmHeader0 = 0x06;
        stSendAttn.ucVdmHeader1 = 0xA1;

        // Execute Write Command
        if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stSendAttn.ucCommandCode, 1, stSendAttn.ucDataLength + 1, &stSendAttn.ucDataLength, ucInputPort) == _FAIL)
        {
            return;
        }

        // Polling Write Command Operation Status
        if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
        {
            return;
        }

        SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(ucInputPort);
        SET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT();
        ScalerTimerActiveTimerEvent(300, _SYSTEM_TIMER_EVENT_TYPE_C_LENOVO_ALT_MODE_URGENT_EVENT_TIMEOUT);
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : ucInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonPortControllerCheck5400LenovoDockingEventBusy(BYTE ucInputPort)
{
    if(GET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort) == 0x00)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}
#endif // End of #if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#endif // End of #if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

