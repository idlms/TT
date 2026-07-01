/*!
 * @file DFRobot_ADT7470.cpp
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
#include "Debug.h"
#include "Global.h"
#include "ADT7470.h"
#include "RL6449_Project.h"
#if	(_ENABLE_FAN_CONTROL == _ON && _FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)

bit _ADT7470Initialised;///<init flag.
bit _setconfigADT7470;
bit WriteReg_ADT7470(BYTE ui8Addr, BYTE ui8Value);
bit ReadReg_ADT7470(BYTE ui8Addr, BYTE *pui8Wbuff);
//bit Write_ADT7470(BYTE ui8Addr, BYTE *pui8Wbuff, WORD ui16WriteLength);
//bit Read_ADT7470(BYTE ui8Addr, BYTE *pui8Rbuff, WORD ui16ReadLength);
BYTE tempSensorCount = 0;
SBYTE tempData[5];

//ADT7470 : Single write
bit WriteReg_ADT7470(BYTE ui8Addr, BYTE ui8Value)
{
	//ui8Addr = ui8Addr;
	//ui8Value = ui8Value;

	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
	if (ScalerMcuHwIICWrite(ADT7470_SLAVE_ADDRESS, 1, ui8Addr, 1, &ui8Value, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		// Enable EEPROM Write Protect
		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

		return _FAIL;
	}
	return _SUCCESS;
}

//ADT7470 : Single write
bit ReadReg_ADT7470(BYTE ui8Addr, BYTE *pui8Wbuff)
{
	//ui8Addr = ui8Addr;
	//pui8Wbuff = pui8Wbuff;
	if (ScalerMcuHwIICRead(ADT7470_SLAVE_ADDRESS, 1, ui8Addr, 1, pui8Wbuff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		
		return _FAIL;
	}
	return _SUCCESS;
}

//ADT7470 : Burst write
//bit Write_ADT7470(BYTE ui8Addr, BYTE *pui8Wbuff, WORD ui16WriteLength)
//{
//	return MDrv_IIC_WriteBytes(ADT7470_SLAVE_ADDRESS, 1, &ui8Addr, ui16WriteLength, pui8Wbuff);
//}
//
////ADT7470 : Burst read
//bit Read_ADT7470(BYTE ui8Addr, BYTE *pui8Rbuff, WORD ui16ReadLength)
//{
//	return MDrv_IIC_ReadBytes(ADT7470_SLAVE_ADDRESS, 1, &ui8Addr, ui16ReadLength, pui8Rbuff);
//}


bit SuccessInitialize_ADT7470(void)
{
	return _ADT7470Initialised;
}

BYTE GetTempCount(void)
{
	return tempSensorCount;
}

void _Get_TempSensorCount(void)
{
	BYTE i, u8sensor = 0;
	WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
	ScalerTimerDelayXms(1000); // Temperature Sensors MAX 5 * 200
	WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);
	for (i = 0; i < 5; i++)
	{
		ReadReg_ADT7470((ADT7470_TEMP1_STATUS + i), &u8sensor);
		if (!(u8sensor == 0 || u8sensor == 0xA6))tempSensorCount++;
	}
}

bit Initialize_ADT7470(void)
{
	BYTE reg[2] = { 0,0 };
	_ADT7470Initialised = _FALSE;
	_setconfigADT7470 = _FALSE;
	/* Make sure we're actually connected */
	ReadReg_ADT7470(ADT7470_ID, &reg[0]);
	ReadReg_ADT7470(ADT7470_ID + 1, &reg[1]);

	if ((reg[0] != 0x70) && (reg[1] != 0x41))
	{
		return _FALSE;
	}
	_Get_TempSensorCount();
	_ADT7470Initialised = _TRUE;

	return _TRUE;
}

////////////////////////////////////////
// Temperature Sensor Count 
///////////////////////////////////////
bit GetADT7470Config(void)
{
	return _setconfigADT7470;
}
///////////////////////////////////////////////////
// Temperature Measure 
//////////////////////////////////////////////////
void SetADT7470Configration(void)// 온도 측정 설정. Measure 설정 후 Fan 당 200ms 후에 Normal 변경 후 측정.
{
	if (_setconfigADT7470)
	{
		WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
		_setconfigADT7470 = _FALSE;
	}
	else
	{
		WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);
		_setconfigADT7470 = _TRUE;
	}
}

SBYTE Get_ADT7470Temperature(void)
{
	BYTE i, errorCount = 0;
	BYTE temp = 0;
	SWORD tempSum = 0;
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
	//msAPI_Timer_Delayms(1000); // Temperature Sensors MAX 5 * 200
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);
	for (i = 0; i < tempSensorCount; i++)
	{
		ReadReg_ADT7470((ADT7470_TEMP1_STATUS + i), &temp);
		if (temp == 0 || temp == 0xA6)
		{
			errorCount++;
		}
		else
		{
			tempData[i] = (SBYTE)temp;
			tempSum += (SBYTE)temp;
		}
	}
	//DebugMessageSystem("TEMP 1", tempData[0]);
	//DebugMessageSystem("TEMP 2", tempData[1]);
	//DebugMessageSystem("TEMP 3", tempData[2]);
	//DebugMessageSystem("TEMP 4", tempData[3]);
	//DebugMessageSystem("TEMP 5", tempData[4]);
	tempSum = tempSum /(tempSensorCount - errorCount);
	//LOG_INFO("tempSum == %d, tempSensorCount == %d, errorCount == %d\n\r", tempSum, tempSensorCount, errorCount);
	return tempSum;
}

SBYTE Get_ADT7470Temp1(void)
{
	//BYTE temp = 0;
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
	//msAPI_Timer_Delayms(200); // Temperature Sensors MAX 5 * 200
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);

	//ReadReg_ADT7470(ADT7470_TEMP1_STATUS, &temp);
	if(_ADT7470Initialised) return (SBYTE)tempData[0];
	else return 0;
}

SBYTE Get_ADT7470Temp2(void)
{
	//BYTE temp = 0;
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
	//msAPI_Timer_Delayms(200); // Temperature Sensors MAX 5 * 200
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);

	//ReadReg_ADT7470(ADT7470_TEMP2_STATUS, &temp);
	if (_ADT7470Initialised) return (SBYTE)tempData[1];
	else return 0;
}

SBYTE Get_ADT7470Temp3(void)
{
	//BYTE temp = 0;
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
	//msAPI_Timer_Delayms(200); // Temperature Sensors MAX 5 * 200
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);

	//ReadReg_ADT7470(ADT7470_TEMP3_STATUS, &temp);
	if (_ADT7470Initialised) return (SBYTE)tempData[2];
	else return 0;
}

SBYTE Get_ADT7470Temp4(void)
{
	//BYTE temp = 0;
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
	//msAPI_Timer_Delayms(200); // Temperature Sensors MAX 5 * 200
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);

	//ReadReg_ADT7470(ADT7470_TEMP4_STATUS, &temp);
	if (_ADT7470Initialised) return (SBYTE)tempData[3];
	else return 0;
}

SBYTE Get_ADT7470Temp5(void)
{
	//BYTE temp = 0;
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_START_MEASURE);
	//msAPI_Timer_Delayms(200); // Temperature Sensors MAX 5 * 200
	//WriteReg_ADT7470(ADT7470_CONFIG, ADT7470_NORMAL);

	//ReadReg_ADT7470(ADT7470_TEMP5_STATUS, &temp);
	if (_ADT7470Initialised) return (SBYTE)tempData[4];
	else return 0;
}
/////////////////////////////////////////////
// Fan PWM Control.
/////////////////////////////////////////////
void SetFanAllPWM(BYTE u8pwm)
{
	BYTE i;
	for (i = 0; i < 4; i++)
	{
		WriteReg_ADT7470((ADT7470_PWM1_MAX_DUTY + i), u8pwm);
	}
}

void SetFanPWM1(BYTE u8pwm)
{
	WriteReg_ADT7470(ADT7470_PWM1_MAX_DUTY, u8pwm);
}

void SetFanPWM2(BYTE u8pwm)
{
	WriteReg_ADT7470(ADT7470_PWM2_MAX_DUTY, u8pwm);
}

void SetFanPWM3(BYTE u8pwm)
{
	WriteReg_ADT7470(ADT7470_PWM3_MAX_DUTY, u8pwm);
}

void SetFanPWM4(BYTE u8pwm)
{
	WriteReg_ADT7470(ADT7470_PWM4_MAX_DUTY, u8pwm);
}

#endif