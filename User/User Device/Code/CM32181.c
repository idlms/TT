

#include "UserCommonInclude.h"
#include "Global.h"
#include "Debug.h"
#include "CM32181.h"
#include "RL6449_Project.h"

#if	(_ENABLE_LIGHT_SENSOR == _ON)
#if(_LIGHT_SENSOR_TYPE == _LIGHT_CM32181)
/*
* Copyright (C) 2013 Capella Microsystems Inc.
* Author: Kevin Tsai <ktsai@capellamicro.com>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License version 2, as published
* by the Free Software Foundation.
*/


static const BYTE als_it_bits[] = { 12, 8, 0, 1, 2, 3 };
static const int als_it_value[] = { 25000, 50000, 100000, 200000, 400000, 800000 };
static WORD command00Reg;
bit InitializeCm3281 = _FALSE;

static bit Cm32181_ReadRegs(BYTE ucAddr, BYTE  *pucBuff, BYTE ucLength)
{

	//ucAddr = ucAddr;
	//pucBuff = pucBuff;

	if (ScalerMcuHwIICRead(CM32181_ADDRESS, 1, ucAddr, ucLength, pucBuff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		//DebugMessageSystem("Cm32181_ReadRegs() = FAIL", _FALSE);
		return _FAIL;
	}
	//DebugMessageSystem("Cm32181_ReadRegs() = SUCCESS", _TRUE);
	return _SUCCESS;
}

static bit Cm32181_WriteRegs(BYTE ucAddr, BYTE  *pucBuff, BYTE  ucLength)
{

	//ucAddr = ucAddr;
	//pucBuff = pucBuff;
	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
	if (ScalerMcuHwIICWrite(CM32181_ADDRESS, 1, ucAddr, ucLength, pucBuff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		
		// Enable EEPROM Write Protect
		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

		return _FAIL;
	}
	
	return _SUCCESS;
}

//static bit Cm32181_ReadReg(BYTE ucAddr, BYTE *pucBuff)
//{
//	return MDrv_IIC_ReadByte(CM32181_ADDRESS, ucAddr, pucBuff);
//}
//
//static bit Cm32181_WriteReg(BYTE  ucAddr, BYTE  ucData)
//{
//	return MDrv_IIC_WriteByte(CM32181_ADDRESS, ucAddr, ucData);
//}

bit SuccessInitialize_CM3281(void)
{
	return InitializeCm3281;
}

static bit Cm32181_Ping(void)
{

	bit bRetVal = _FALSE;
	BYTE ui8Addr = CM32181_REG_ADDR_ID;
	BYTE pui8Buff[1];

	if (Cm32181_ReadRegs(ui8Addr, pui8Buff, 1))
	{
		bRetVal = _TRUE;
	}
	// Check Device ID
	if (pui8Buff[0] != 0x81)
	{
		bRetVal = _FALSE;
		
	}
	//DebugMessageSystem("Cm32181_Ping", pui8Buff[0]);
	return bRetVal;
}

/**
* cm32181_reg_init() - Initialize CM32181 registers
* @cm32181:	pointer of struct cm32181.
*
* Initialize CM32181 ambient light sensor register to default values.
*
* Return: 0 for success; otherwise for error code.
*/
bit Cm32181_init(void)
{
	WORD u16RBuff;
	BYTE pui8Buff[2]= { 0x00, 0x00};
	if (Cm32181_Ping())
	{
		InitializeCm3281 = _TRUE;
	}
	else
	{
		InitializeCm3281 = _FALSE;
		return _FALSE;
	}
	/* Default Values */
	u16RBuff = CM32181_CMD_ALS_ENABLE |	CM32181_CMD_ALS_IT_DEFAULT | CM32181_CMD_ALS_SM_DEFAULT;
	pui8Buff[1] = (BYTE)((u16RBuff & 0xFF00) >> 8);
	pui8Buff[0] = (BYTE)((u16RBuff & 0x00FF));
	command00Reg = u16RBuff;
	Cm32181_WriteRegs(CM32181_REG_ADDR_CMD, pui8Buff, 2);
	//LOG_INFO("CM32181 Initialize Command_Reg(00) : %d\n\r", command00Reg);
	return _TRUE;
}

//bit Cm32181_Shudown(void)
//{
//	WORD u16RBuff;
//	BYTE pui8Buff[2] = { 0x00, 0x00 };
//	if (Cm32181_Ping())
//	{
//		InitializeCm3281 = _TRUE;
//	}
//	else
//	{
//		InitializeCm3281 = _FALSE;
//		return _FALSE;
//	}
//	/* Default Values */
//	u16RBuff = CM32181_SHUTDOWN;
//	pui8Buff[1] = (BYTE)((u16RBuff & 0xFF00) >> 8);
//	pui8Buff[0] = (BYTE)((u16RBuff & 0x00FF));
//	command00Reg = u16RBuff;
//	Cm32181_WriteRegs(CM32181_REG_ADDR_CMD, pui8Buff, 2);
//	//LOG_INFO("CM32181 Shutdown Command_Reg(00) : %d\n\r", command00Reg);
//	return _TRUE;
//}

/**
*  cm32181_read_als_it() - Get sensor integration time (ms)
*  @cm32181:	pointer of struct cm32181
*  @val2:	pointer of int to load the als_it value.
*
*  Report the current integartion time by millisecond.
*
*  Return: IIO_VAL_INT_PLUS_MICRO for success, otherwise -EINVAL.
*/
//DWORD Cm32181_read_als_it(void)
//{
//	int i;
//	DWORD u32Revalue = 0;
//	WORD u16RBuff;
//	BYTE pui8Buff[2] = { 0x00, 0x00 };
//	if (!InitializeCm3281) return 0;
//	Cm32181_ReadRegs(CM32181_REG_ADDR_CMD, pui8Buff, 2);
//
//	u16RBuff = (WORD)(pui8Buff[1] << 8);
//	u16RBuff |= (WORD)pui8Buff[0];
//
//	u16RBuff &= CM32181_CMD_ALS_IT_MASK;
//
//	u16RBuff >>= CM32181_CMD_ALS_IT_SHIFT;
//	for (i = 0; i < (BYTE)ARRAY_SIZE(als_it_bits); i++) {
//		if ((BYTE)u16RBuff == als_it_bits[i]) {
//			u32Revalue = als_it_value[i];
//
//		}
//	}
//	return u32Revalue;
//}

/**
* cm32181_write_als_it() - Write sensor integration time
* @cm32181:	pointer of struct cm32181.
* @val:	integration time by millisecond.
*
* Convert integration time (ms) to sensor value.
*
* Return: i2c_smbus_write_word_data command return value.
*/
//void Cm32181_write_als_it(int val)
//{
//
//	int i, n;
//	WORD u16RBuff;
//	BYTE pui8Buff[2] = { 0x00, 0x00 };
//	if (!InitializeCm3281) return;
//	n = ARRAY_SIZE(als_it_value);
//	for (i = 0; i < n; i++)
//		if (val <= als_it_value[i])
//			break;
//	if (i >= n)
//		i = n - 1;
//	u16RBuff = als_it_bits[i];
//	u16RBuff <<= CM32181_CMD_ALS_IT_SHIFT;
//
//	command00Reg &= ~CM32181_CMD_ALS_IT_MASK;
//	u16RBuff |= command00Reg;
//
//	pui8Buff[0] = (BYTE)((u16RBuff & 0xFF00) >> 8);
//	pui8Buff[1] = (BYTE)((u16RBuff & 0x00FF));
//
//	Cm32181_WriteRegs(CM32181_REG_ADDR_CMD, pui8Buff, 2);
//
//}

/**
* cm32181_get_lux() - report current lux value
* @cm32181:	pointer of struct cm32181.
*
* Convert sensor raw data to lux.  It depends on integration
* time and calibscale variable.
*
* Return: Positive value is lux, otherwise is error code.
*/
DWORD Cm32181_get_lux(void)
{
	//int als_it;
	WORD u16RBuff = 0;
	BYTE pui8Buff[2] = { 0x00, 0x00 };
	//U8 pui8Buff[1] = { 0x00};
	DWORD lux;
	if (!InitializeCm3281) return 0;
	if (Cm32181_ReadRegs(CM32181_REG_ADDR_CMD, pui8Buff, 2))
	{
		u16RBuff = (WORD)(pui8Buff[1] << 8);
		u16RBuff |= (WORD)pui8Buff[0];
		//LOG_INFO("CM32181 Initialize Command_Reg(00),  : %d == %d \n\r", u16RBuff, command00Reg);
	}
	if (command00Reg != u16RBuff)
	{
		u16RBuff = CM32181_CMD_ALS_ENABLE | CM32181_CMD_ALS_IT_DEFAULT | CM32181_CMD_ALS_SM_DEFAULT;
		pui8Buff[1] = (BYTE)((u16RBuff & 0xFF00) >> 8);
		pui8Buff[0] = (BYTE)((u16RBuff & 0x00FF));
		Cm32181_WriteRegs(CM32181_REG_ADDR_CMD, pui8Buff, 2);
	}

	//als_it = Cm32181_read_als_it();
	//if (als_it < 0)
	//	return als_it;
	//als_it = 100000;
	lux = CM32181_MLUX_PER_BIT;
	lux *= CM32181_MLUX_PER_BIT_BASE_IT;
	//DebugMessageSystem("lux *= CM32181_MLUX_PER_BIT_BASE_IT", lux);
	lux /= 1000;
	//DebugMessageSystem("lux = lux/als_it", lux);
	//Cm32181_ReadReg(CM32181_REG_ADDR_ALS, pui8Buff);
	//u16RBuff = (U16)(pui8Buff[0] << 8);
	//Cm32181_ReadReg(CM32181_REG_ADDR_ALS + 1, pui8Buff);
	//u16RBuff |= pui8Buff[0];
	//LOG_INFO("Cm32181_read_als_it : %d , lux == %d \n\r", als_it, lux);
	if (Cm32181_ReadRegs(CM32181_REG_ADDR_ALS, pui8Buff, 2))
	{
		u16RBuff = (WORD)(pui8Buff[1] << 8);
		u16RBuff |=(WORD) pui8Buff[0];
	}
	else
	{
		return 0;
	}
	//DebugMessageSystem("Lux Read pui8Buff[1]", pui8Buff[1]);
	//DebugMessageSystem("Lux Read pui8Buff[0]", pui8Buff[0]);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// als_it = 100000 알수 없는 이유로 한 번에 100000을 나눌수 없어서 1000, 100 으로 두번 나누어 계산 하도록 변경. 
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	lux = lux * u16RBuff / 100;
	 
	lux *= CM32181_CALIBSCALE_DEFAULT;
	lux /= CM32181_CALIBSCALE_RESOLUTION;
	lux /= MLUX_PER_LUX;


	if (lux > 0xFFFF)
		lux = 0xFFFF;
	//DebugMessageSystem("LUX ", lux);
	return lux;
}

//tLightSensorEntry  gstCM32181Driver =
//{
//	.Init = Cm32181_init,
//	.SuccessInitialize = SuccessInitialize_CM3281,
//	.GetLux = Cm32181_get_lux,
//};

#endif
#endif