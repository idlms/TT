/*!
 * @file DFRobot_TCS34725.cpp
 * @brief color sensor
 * @n Header file for DFRobot's color sensors
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [carl](carl.xu@dfrobot.com)
 * @version  V1.0
 * @date  2016-07-12
 */
 /**************************************************************************/

#include "UserCommonInclude.h"
#include "Global.h"
#include "TCS34725.h"
#include "RL6410_Project.h"

#if	(_ENABLE_SELF_CHECK == _ON)
bit _tcs34725Initialised;///<init flag.
static tcs34725Gain_t _tcs34725Gain;///<gain time.
static tcs34725IntegrationTime_t _tcs34725IntegrationTime;
bit WriteReg_TCS34725(BYTE ui8Addr, BYTE ui8Value);
bit ReadReg_TCS34725(BYTE ui8Addr, BYTE *pui8ReadData);
//bit Write_TCS34725(BYTE ui8Addr, BYTE *pui8Wbuff, WORD ui16WriteLength);
bit Read_TCS34725(BYTE ui8Addr, BYTE *pui8Rbuff, WORD ui16ReadLength);
void SetIntegrationTime_TCS34725(tcs34725IntegrationTime_t it);
void SetGain_TCS34725(tcs34725Gain_t gain);
void GetRGBC_TCS34725(WORD *r, WORD *g, WORD *b, WORD *c);
//float powf(const float x, const float y)
//{
//	return (float)(pow((double)x, (double)y));
//}


//TCS34725 : Single write
bit WriteReg_TCS34725(BYTE ui8Addr, BYTE ui8Value)
{
	if (ScalerMcuHwIICRead(TCS34725_SLAVE_ADDRESS, 1, TCS34725_COMMAND_BIT | ui8Addr, 1, &ui8Value, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		return _FAIL;
	}
}

//TCS34725 : Single write
bit ReadReg_TCS34725(BYTE ui8Addr, BYTE *pui8Rbuff)
{
	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
	if (ScalerMcuHwIICWrite(TCS34725_SLAVE_ADDRESS, 1, TCS34725_COMMAND_BIT | ui8Addr, 1, pui8Rbuff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		// Enable EEPROM Write Protect
		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

		return _FAIL;
	}
	return _SUCCESS;
}

//TCS34725 : Burst write
//bit Write_TCS34725(BYTE ui8Addr, BYTE *pui8Wbuff, WORD ui16WriteLength)
//{
//	BYTE addr = TCS34725_COMMAND_BIT | ui8Addr;
//	return MDrv_IIC_WriteBytes(TCS34725_SLAVE_ADDRESS, 1, &addr, ui16WriteLength, pui8Wbuff);
//}

//TCS34725 : Burst read
bit Read_TCS34725(BYTE ui8Addr, BYTE *pui8Rbuff, WORD ui16ReadLength)
{
	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
	if (ScalerMcuHwIICWrite(TCS34725_SLAVE_ADDRESS, 1, TCS34725_COMMAND_BIT | ui8Addr, ui16ReadLength, pui8Rbuff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		// Enable EEPROM Write Protect
		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

		return _FAIL;
	}
	return _SUCCESS;
}



void Enable_TCS34725(void)
{
	BYTE reg;
	WriteReg_TCS34725(TCS34725_ENABLE, TCS34725_ENABLE_PON);
	ScalerTimerDelayXms(3);
	reg = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
	WriteReg_TCS34725(TCS34725_ENABLE, reg);
}


//void Disable_TCS34725(void)
//{
//	/* Turn the device off to save power */
//	BYTE reg = 0;
//	ReadReg_TCS34725 (TCS34725_ENABLE, &reg);
//	reg = reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
//	WriteReg_TCS34725(TCS34725_ENABLE, reg);
//}

bit SuccessInitialize_TCS34725(void)
{
	return _tcs34725Initialised;
}

bit Initialize_TCS34725(void)
{
	BYTE reg = 0;
	BYTE x;
	_tcs34725Initialised = _FALSE;
	_tcs34725IntegrationTime = TCS34725_INTEGRATIONTIME_50MS;
	_tcs34725Gain = TCS34725_GAIN_4X;

	/* Make sure we're actually connected */
	ReadReg_TCS34725(TCS34725_ID, &reg);
	x = reg;
	if ((x != 0x44) && (x != 0x10))
	{
		return _FALSE;
	}
	_tcs34725Initialised = _TRUE;

	/* Set default integration time and gain */
	SetIntegrationTime_TCS34725(_tcs34725IntegrationTime);
	SetGain_TCS34725(_tcs34725Gain);

	///* Note: by default, the device is in power down mode on bootup */
	Enable_TCS34725();

	return _TRUE;
}


void SetIntegrationTime_TCS34725(tcs34725IntegrationTime_t it)
{

	if (!_tcs34725Initialised) Initialize_TCS34725();
	if (_tcs34725Initialised)
	{
		BYTE reg = it;
		/* Update the timing register */
		WriteReg_TCS34725(TCS34725_ATIME, reg);

		/* Update value placeholders */
		_tcs34725IntegrationTime = it;
	}
}


void SetGain_TCS34725(tcs34725Gain_t gain)
{

	if (!_tcs34725Initialised) Initialize_TCS34725();
	if (_tcs34725Initialised)
	{
		BYTE reg = gain;
		/* Update the timing register */
		WriteReg_TCS34725(TCS34725_CONTROL, reg);
		/* Update value placeholders */
		_tcs34725Gain = gain;
	}
}


void GetRGBC_TCS34725(WORD *r, WORD *g, WORD *b, WORD *c)
{
	if (!_tcs34725Initialised) Initialize_TCS34725();
	if (_tcs34725Initialised)
	{
		BYTE reg[2] = { 0, 0 };
		WORD wdata = 0;
		Read_TCS34725(TCS34725_CDATAL, reg, 2);
		wdata = reg[1] << 8;
		wdata |= reg[0];
		*c = wdata;
		Read_TCS34725(TCS34725_RDATAL, reg, 2);
		wdata = reg[1] << 8;
		wdata |= reg[0];
		*r = wdata;
		Read_TCS34725(TCS34725_GDATAL, reg, 2);
		wdata = reg[1] << 8;
		wdata |= reg[0];
		*g = wdata;
		Read_TCS34725(TCS34725_BDATAL, reg, 2);
		wdata = reg[1] << 8;
		wdata |= reg[0];
		*b = wdata;

		/* Set a delay for the integration time */
		switch (_tcs34725IntegrationTime)
		{
		case TCS34725_INTEGRATIONTIME_2_4MS:
			ScalerTimerDelayXms(3);
			break;
		case TCS34725_INTEGRATIONTIME_24MS:
			ScalerTimerDelayXms(24);
			break;
		default:
		case TCS34725_INTEGRATIONTIME_50MS:
			ScalerTimerDelayXms(50);
			break;
		case TCS34725_INTEGRATIONTIME_101MS:
			ScalerTimerDelayXms(101);
			break;
		case TCS34725_INTEGRATIONTIME_154MS:
			ScalerTimerDelayXms(154);
			break;
		case TCS34725_INTEGRATIONTIME_700MS:
			ScalerTimerDelayXms(700);
			break;
		}
	}
}

//WORD CalculateColorTemperature_TCS34725(WORD r, WORD g, WORD b)
//{
//	float X, Y, Z;      /* RGB to XYZ correlation      */
//	float xc, yc;       /* Chromaticity co-ordinates   */
//	float n;            /* McCamy's formula            */
//	float cct;
//
//	/* 1. Map RGB values to their XYZ counterparts.    */
//	/* Based on 6500K fluorescent, 3000K fluorescent   */
//	/* and 60W incandescent values for a wide range.   */
//	/* Note: Y = Illuminance or lux                    */
//	X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
//	Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
//	Z = (-0.68202F * r) + (0.77073F * g) + (0.56332F * b);
//
//	/* 2. Calculate the chromaticity co-ordinates      */
//	xc = (X) / (X + Y + Z);
//	yc = (Y) / (X + Y + Z);
//
//	/* 3. Use McCamy's formula to determine the CCT    */
//	n = (xc - 0.3320F) / (0.1858F - yc);
//
//	/* Calculate the final CCT */
//	cct = (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;
//
//	/* Return the results in degrees Kelvin */
//	return (WORD)cct;
//}


//WORD CalculateLux_TCS34725(WORD r, WORD g, WORD b)
//{
//	float illuminance;
//
//	/* This only uses RGB ... how can we integrate clear or calculate lux */
//	/* based exclusively on clear since this might be more reliable?      */
//	illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
//
//	return (WORD)illuminance;
//}

void Lock_TCS34725(void)
{
	BYTE reg = 0;
	ReadReg_TCS34725(TCS34725_ENABLE, &reg);
	reg |= TCS34725_ENABLE_AIEN;

	WriteReg_TCS34725(TCS34725_ENABLE, reg);
}

//void Unlock_TCS34725(void)
//{
//	BYTE reg = 0;
//	ReadReg_TCS34725(TCS34725_ENABLE, &reg);
//	reg &= ~TCS34725_ENABLE_AIEN;
//
//	WriteReg_TCS34725(TCS34725_ENABLE, reg);
//}


//void Clear_TCS34725(void)
//{
//	WriteReg_TCS34725(0x66, 0);
//}


//void SetIntLimits_TCS34725 (WORD low, WORD high) 
//{
//	BYTE reg[2] = { 0,0 };
//	reg[0] = low & 0xFF;
//	reg[1] = low >> 8;
//	WriteReg_TCS34725(0x04, reg[0]);
//	WriteReg_TCS34725(0x05, reg[1]);
//
//	reg[0] = high & 0xFF;
//	reg[1] = high >> 8;
//	WriteReg_TCS34725(0x04, reg[0]);
//	WriteReg_TCS34725(0x05, reg[1]);
//}
#endif