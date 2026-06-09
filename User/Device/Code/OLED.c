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


#include "UserCommonInclude.h"
#include "Global.h"
#include "OLED.h"
#if (_ENABLE_MENU_OLED == _ON)
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
BYTE g_ucOffRSRunning = 0;
BYTE g_ucJBRunning = 0;
//--------------------------------------------------
// Description  : Read data to the AMOLED by IIC
// Output Value : Reading result
//--------------------------------------------------
BYTE AMOLED_ReadByte(BYTE B_RegAddr)
{
	BYTE Ba_Temp[1];

	Ba_Temp[0] = 0;

	// DebugMessageOsd("T:AMOLED Read = ", B_RegAddr);

	if(ScalerMcuHwIICRead(_AMOLED_I2C_ADDR, 1, B_RegAddr, 1, Ba_Temp, _HW_IIC_PIN_149_150) == _FAIL)
	{
		DebugMessageOsd("T:AMOLED I2C R Fail", _AMOLED_I2C_ADDR);
		return(0);
	}

	return	Ba_Temp[0];

}

//--------------------------------------------------
// Description  : Write data to the AMOLED Panel by IIC
//--------------------------------------------------

void AMOLED_WriteByte(BYTE B_RegAddr, BYTE B_Data)
{
	BYTE Ba_Temp[1];

	Ba_Temp[0] = B_Data;

	if(ScalerMcuHwIICWrite(_AMOLED_I2C_ADDR, 1, B_RegAddr, 1, Ba_Temp, _HW_IIC_PIN_149_150) == _FAIL)
		{
			DebugMessageOsd("T:AMOLED I2C W Fail ", _AMOLED_I2C_ADDR);
		}

}



void Initialize_AMOLED(void)
{

	//BYTE  B_Temp;

	// AMOLED_WriteByte(_AMOLED_VLC_PARAM_ON_WIN_REG, (GET_VLC_PEAK_GAIN()<<2)|GET_VLC_ENABLE()*3);
	// AMOLED_WriteByte(_AMOLED_VLC_PARAM_MID_MSB_REG, GET_VLC_MODULE_ID()>>8&0x00ff);
	// AMOLED_WriteByte(_AMOLED_VLC_PARAM_MID_LSB_REG, GET_VLC_MODULE_ID()&0x00ff);
	// AMOLED_WriteByte(_AMOLED_VLC_PARAM_PID_MSB_REG, GET_VLC_PICTURE_ID()>>8&0x00ff);
	// AMOLED_WriteByte(_AMOLED_VLC_PARAM_PID_LSB_REG, GET_VLC_PICTURE_ID()&0x00ff);
	// AMOLED_WriteByte(_AMOLED_VLC_PARAM_INIT_ACL_MSB_REG,0x3);
	// AMOLED_WriteByte(_AMOLED_VLC_PARAM_INIT_ACL_LSB_REG,0xff);

  // DebugMessageOsd("T:_AMOLED_APL1_TPC_OFFRS_REG =", AMOLED_ReadByte(_AMOLED_APL1_TPC_OFFRS_REG));
  // DebugMessageOsd("T:_AMOLED_APL2_REG =", AMOLED_ReadByte(_AMOLED_APL2_REG));

	AMOLED_ReadByte(_AMOLED_APL1_TPC_OFFRS_REG);
	AMOLED_ReadByte(_AMOLED_APL2_REG);
// #if(_TPC_CONTROL == _ON)
//   if(GET_TPC_ENABLE()==_OFF)
//   {
//     AMOLED_WriteByte(_AMOLED_APL1_TPC_OFFRS_REG,(AMOLED_ReadByte(_AMOLED_APL1_TPC_OFFRS_REG)&~_BIT6)|0x00);
//   }
// #endif
//
// #if(_HDR_OLED == _ON)
//   AMOLED_WriteByte(_AMOLED_LEA_HDR_REG,(AMOLED_ReadByte(_AMOLED_LEA_HDR_REG)&~_BIT3)|_BIT3);
// #endif
}


void Excute_OLED_OFFRS(bit bEnable)
{
	BYTE B_Temp;
	B_Temp = AMOLED_ReadByte(_AMOLED_APL1_TPC_OFFRS_REG);
	DebugMessageOsd("T:off-rs",B_Temp);


	if(bEnable)
	{
//	   AMOLED_WriteByte(_AMOLED_APL1_TPC_OFFRS_REG, 0x52);
	   B_Temp = (B_Temp&~_BIT4)|_BIT4;

	   g_ucOffRSRunning = 1;
     DebugMessageOsd("T:on",B_Temp);
	}
	else
	{
//	   AMOLED_WriteByte(_AMOLED_APL1_TPC_OFFRS_REG, 0x42);
	   B_Temp = (B_Temp&~_BIT4)|0x00;
	   g_ucOffRSRunning = 0;
     DebugMessageOsd("T:off",B_Temp);
	}

	AMOLED_WriteByte(_AMOLED_APL1_TPC_OFFRS_REG,B_Temp);
}

void Excute_OLED_JB(bit bEnable)
{
	if(bEnable)
	{
	   AMOLED_WriteByte(_AMOLED_JB_REG, 0x80);
		 DebugMessageOsd("T:JB on",1);
	   g_ucJBRunning = 1;
	}
	else
	{
	  AMOLED_WriteByte(_AMOLED_JB_REG, 0x00);
		DebugMessageOsd("T:JB off",0);
	   g_ucJBRunning = 0;
	}
	DebugMessageOsd("Osd: JB Read ", AMOLED_ReadByte(_AMOLED_JB_REG));

}


BYTE GET_OFF_RS_STATUS(void)
{
	return g_ucOffRSRunning;
}

BYTE GET_JB_COMP_STATUS(void)
{
	return g_ucJBRunning;
}


BYTE GetWaitingToRunOFFRS(void)
{
	return GET_WAIT_TO_RUN_OFFRS();
}

void CancelWaitingToRunOFFRS(void)
{
	SET_WAIT_TO_RUN_OFFRS(_OFF);
}


BYTE GetWaitingToRunJB(void)
{
	return GET_WAIT_TO_RUN_JB();
}

void CancelWaitingToRunJB(void)
{
	SET_WAIT_TO_RUN_JB(_OFF);
}

void ResetOffRSTime(void)
{
	SET_OFF_RS_HOUR(0);
	SET_OFF_RS_MIN(0);
}
void ResetJBTime(void)
{
	SET_JB_HOUR(0);
	SET_JB_MIN(0);
}
#endif
