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

//****************************************************************************
//
// Copyright  2004−2005 TAOS, Inc.
//
// THIS CODE AND INFORMATION IS PROVIDED ”AS IS” WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// Module Name:
// lux.cpp
//
//****************************************************************************
#if (_ENABLE_MENU_OLED == _ON)
#define _AMOLED_I2C_ADDR							       0xF0	//OLED

#define _AMOLED_APL1_TPC_OFFRS_REG          (0x01)
#define _AMOLED_APL2_REG                    (0x02)
#define _AMOLED_LEA_HDR_REG                 (0x0B)
#define _AMOLED_LUMINANCE_REG               (0x16)
#define _AMOLED_VLC_PARAM_ON_WIN_REG        (0x40)
#define _AMOLED_VLC_PARAM_HYS_THRESH_REG    (0x41)
#define _AMOLED_VLC_PARAM_MID_MSB_REG       (0x48)
#define _AMOLED_VLC_PARAM_MID_LSB_REG       (0x49)
#define _AMOLED_VLC_PARAM_PID_MSB_REG       (0x4A)
#define _AMOLED_VLC_PARAM_PID_LSB_REG       (0x4B)
#define _AMOLED_VLC_PARAM_PEAK_MSB_REG      (0x4C)
#define _AMOLED_VLC_PARAM_PEAK_LSB_REG      (0x4D)
#define _AMOLED_VLC_PARAM_TX_CNT_MSB_REG    (0x4E)
#define _AMOLED_VLC_PARAM_TX_CNT_LSB_REG    (0x4F)
#define _AMOLED_VLC_PARAM_INIT_ACL_MSB_REG  (0x50)
#define _AMOLED_VLC_PARAM_INIT_ACL_LSB_REG  (0x51)
#define _AMOLED_JB_REG                      (0x5D)
#define _AMOLED_TEMPER1_HI_REG              (0x5E)
#define _AMOLED_TEMPER1_LO_REG              (0x5F)
#define _AMOLED_TEMPER2_HI_REG              (0x60)
#define _AMOLED_TEMPER2_LO_REG              (0x61)




void AMOLED_WriteByte(BYTE B_RegAddr, BYTE B_Data);
BYTE AMOLED_ReadByte(BYTE B_RegAddr);
void Initialize_AMOLED(void);

void Excute_OLED_OFFRS(bit bEnable);
void Excute_OLED_JB(bit bEnable);

BYTE GET_OFF_RS_STATUS(void);
BYTE GET_JB_COMP_STATUS(void);
BYTE GetWaitingToRunOFFRS(void);
void CancelWaitingToRunOFFRS(void);
BYTE GetWaitingToRunJB(void);
void CancelWaitingToRunJB(void);
void ResetOffRSTime(void);
void ResetJBTime(void);

#endif
