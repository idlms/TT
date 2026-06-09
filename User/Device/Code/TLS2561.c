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
// lux equation approximation without floating point calculations
//////////////////////////////////////////////////////////////////////////////
// Routine: SWORD CalculateLux(SWORD ch0, SWORD ch0, int iType)
//
// Description: Calculate the approximate illuminance (lux) given the raw
// channel values of the TSL2560. The equation if implemented
// as a piece−wise linear approximation.
//
// Arguments: SWORD iGain − gain, where 0:1X, 1:16X
// SWORD tInt − integration time, where 0:13.7mS, 1:100mS, 2:402mS,
// 3:Manual
// SWORD ch0 − raw channel value from channel 0 of TSL2560
// SWORD ch1 − raw channel value from channel 1 of TSL2560
// SWORD iType − package type (T or CS)
//
// Return: SWORD − the approximate illuminance (lux)
//
//////////////////////////////////////////////////////////////////////////////

#include "UserCommonInclude.h"
#include "Global.h"
#include "TLS2561.h"
#if	(_ENABLE_LIGHT_SENSOR == _ON)
#if (_LIGHT_SENSOR_TYPE == _LIGHT_TLS2561)
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit TLS2561Read(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
bit TLS2561Write(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

bit retvalue = _FALSE;
//--------------------------------------------------
// Description  : Read data to the System EEPROM by IIC
// Input Value  : usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit TLS2561Read(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;

    // Execute Hardware IIC Read Command
    //if(UserCommonEepromIICRead(_TLS2561_SLAVE_ADDRESS, usSubAddr, 1, usLength, pucReadArray, 0x00, _PCB_SYS_EEPROM_IIC) == _FAIL)
    //{
    //    return _FAIL;
    //}
	if (ScalerMcuHwIICRead(_TLS2561_SLAVE_ADDRESS, 1, usSubAddr, 1, pucReadArray, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		return _FAIL;
	}
	//UARTDebugMessage(8);
	//UARTDebugMessage("ch 0 Low:\n", 1);
	//UARTDebugMessage("ch 0 Low:\n", 2);
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the System EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
//#pragma save
//#pragma OT(8)
bit TLS2561Write(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;

    // Execute Hardware IIC Write Command
	//PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
 //   if(UserCommonEepromIICWrite(_TLS2561_SLAVE_ADDRESS, usSubAddr, 1, usLength, pucWriteArray, 0x00, _PCB_SYS_EEPROM_IIC, WRITE_SIZE_8) == _FAIL)
 //   {
 //       return _FAIL;
 //   }
	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
	if (ScalerMcuHwIICWrite(_TLS2561_SLAVE_ADDRESS, 1, usSubAddr, 1, pucWriteArray, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		// Enable EEPROM Write Protect
		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

		return _FAIL;
	}
	return _SUCCESS;
}
//#pragma restore

bit SuccessInitialize_TLS2561(void)
{
	return retvalue;
}

bit Initialize_TLS2561(void)
{

	BYTE wData[1];
	BYTE rData[1];

	
	retvalue = _FALSE;
	wData[0] = 0x03; // Power On
	//TLS2561Write(0x80, 1, &wData[0]);
	//ScalerTimerDelayXms(20);
	TLS2561Write(_COMMAND_CONTROL, 1, &wData[0]);
	//ScalerTimerDelayXms(20);
	//TLS2561Write(_COMMAND_CONTROL, 1, &wData[0]);
	//ScalerTimerDelayXms(20);

	TLS2561Read(_COMMAND_CONTROL, 1, &rData[0]);
	if (rData[0] != 0) retvalue = _TRUE;

	wData[0] = 0x01; // 101 msec
	TLS2561Write(_COMMAND_TIMING, 1, &wData[0]);
	//wData[0] = 0x00;
	//TLS2561Read(0x80, 1, &wData[0]);
	//UARTDebugMessage(wData[0]);
	return retvalue;
}


DWORD CalculateLux(void)
{
	//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
	// first, scale the channel values depending on the gain and integration time
	// 16X, 402mS is nominal.
	// scale if integration time is NOT 402 msec
	DWORD chScale;
	DWORD channel1;
	DWORD channel0;
	WORD ch0, ch1;
	//BYTE wData[1];
	BYTE pCH0Data[2];
	BYTE pCH1Data[2];
	// find the ratio of the channel values (Channel1/Channel0)
	// protect against divide by zero
	DWORD ratio1 = 0;
	DWORD ratio = 0;

	// is ratio <= eachBreak ?
	SWORD b, m;

	DWORD temp;
	DWORD lux =0;
	bit iGain = _FALSE; BYTE tInt = 1; BYTE iType = 1;

	pCH0Data[0] = 0x00;
	pCH0Data[1] = 0x00;
	pCH1Data[0] = 0x00;
	pCH1Data[1] = 0x00;
	//wData[0] = 0x03; // Power On
	//TLS2561Write(0x80, 1, &wData[0]);
	//ScalerTimerDelayXms(20);
	//wData[0] = 0x07; // 101 msec
	//TLS2561Write(_COMMAND_TIMING, 1, &wData[0]);
	//TLS2561Read(_COMMAND_CONTROL, 1, &wData[0]);
	//UARTDebugMessage(wData[0]);
	//TLS2561Read(_COMMAND_TIMING, 1, &wData[0]);
	//UARTDebugMessage(wData[0]);

	//TLS2561Read(_COMMAND_CH0, 2, pCH0Data);
	//TLS2561Read(_COMMAND_CH1, 2, pCH1Data);
	TLS2561Read(_COMMAND_CH0_LOW, 1, &pCH0Data[0]);
	TLS2561Read(_COMMAND_CH0_HIGHT, 1, &pCH0Data[1]);
	//UARTDebugMessage(pCH0Data[0]);
	//UARTDebugMessage(pCH0Data[1]);
	TLS2561Read(_COMMAND_CH1_LOW, 1, &pCH1Data[0]);
	TLS2561Read(_COMMAND_CH1_HIGHT, 1, &pCH1Data[1]);
	//UARTDebugMessage(pCH1Data[0]);
	//UARTDebugMessage(pCH1Data[1]);
	switch (tInt)
	{
	case 0: // 13.7 msec
		chScale = CHSCALE_TINT0;
		break;
	case 1: // 101 msec
		chScale = CHSCALE_TINT1;
		break;
	default: // assume no scaling
		chScale = (1 << CH_SCALE);
		break;
	}

	ch0 = (256 * pCH0Data[1]) + pCH0Data[0]; // DataHigh + DataLow 
	ch1 = (256 * pCH1Data[1]) + pCH1Data[0]; // DataHigh + DataLow 

	// scale if gain is NOT 16X
	if (!iGain) chScale = chScale << 4; // scale 1X to 16X
										// scale the channel values
	channel0 = (ch0 * chScale) >> CH_SCALE;
	channel1 = (ch1 * chScale) >> CH_SCALE;

	if (channel0 != 0) ratio1 = (channel1 << (RATIO_SCALE + 1)) / channel0;
	// round the ratio value
	ratio = (ratio1 + 1) >> 1;

	switch (iType)
	{
	case 0: // T package
		if ((ratio >= 0) && (ratio <= K1T))
		{
			b = B1T; m = M1T;
		}
		else if (ratio <= K2T)
		{
			b = B2T; m = M2T;
		}
		else if (ratio <= K3T)
		{
			b = B3T; m = M3T;
		}
		else if (ratio <= K4T)
		{
			b = B4T; m = M4T;
		}
		else if (ratio <= K5T)
		{
			b = B5T; m = M5T;
		}
		else if (ratio <= K6T)
		{
			b = B6T; m = M6T;
		}
		else if (ratio <= K7T)
		{
			b = B7T; m = M7T;
		}
		else if (ratio > K8T)
		{
			b = B8T; m = M8T;
		}
		break;
	case 1:// CS package
		if ((ratio >= 0) && (ratio <= K1C))
		{
			b = B1C; m = M1C;
		}
		else if (ratio <= K2C)
		{
			b = B2C; m = M2C;
		}
		else if (ratio <= K3C)
		{
			b = B3C; m = M3C;
		}
		else if (ratio <= K4C)
		{
			b = B4C; m = M4C;
		}
		else if (ratio <= K5C)
		{
			b = B5C; m = M5C;
		}
		else if (ratio <= K6C)
		{
			b = B6C; m = M6C;
		}
		else if (ratio <= K7C)
		{
			b = B7C; m = M7C;
		}
		else if (ratio > K8C)
		{
			b = B8C; m = M8C;
		}
		break;
	}
	temp = ((channel0 * b)-(channel1 * m));
	// do not allow negative lux value
	if (temp < 0) temp = 0;
	// round lsb (2^(LUX_SCALE−1))
	temp += (1 << (LUX_SCALE-1));
	// strip off fractional portion
	lux = temp >> LUX_SCALE;
	return(lux);
}

//tLightSensorEntry  gstTLS2561Driver =
//{
//	.Init = Initialize_TLS2561,
//	.SuccessInitialize = SuccessInitialize_TLS2561,
//	.GetLux = CalculateLux,
//};
#endif
#endif