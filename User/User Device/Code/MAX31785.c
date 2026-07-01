
 /**************************************************************************/

#include "UserCommonInclude.h"
#include "Debug.h"
#include "Global.h"
#include "MAX31785.h"
#include "RL6449_Project.h"

#if	(_ENABLE_FAN_CONTROL == _ON &&  _FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)


bit _MAX31785Initialised;///<init flag.
bit _setconfigMAX31785;
bit WriteReg_MAX31785(BYTE ui8Addr, BYTE ui8Value);
bit ReadReg_MAX31785(BYTE ui8Addr, BYTE *pui8Wbuff);
bit WriteRegs_MAX31785(BYTE ui8Addr, WORD u16WBuff);
WORD ReadRegs_MAX31785(BYTE ui8Addr);
//BYTE MAX31785_tempSensorCount = 0;

TEMPSENSORSTAUS MAX31785TempSensor[MAX31785_TEMP_MAX];

//MAX31785 : Single write
bit WriteReg_MAX31785(BYTE ui8Addr, BYTE ui8Value)
{

	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
	if (ScalerMcuHwIICWrite(MAX31785_SLAVE_ADDRESS, 1, ui8Addr, 1, &ui8Value, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		// Enable EEPROM Write Protect
		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
		_MAX31785Initialised = _FALSE;
		return _FAIL;
	}
	return _SUCCESS;
}

//MAX31785 : Single write
bit ReadReg_MAX31785(BYTE ui8Addr, BYTE *pui8Wbuff)
{
	if (ScalerMcuHwIICRead(MAX31785_SLAVE_ADDRESS, 1, ui8Addr, 1, pui8Wbuff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		//DebugMessageSystem("MAX31785_ReadReg(1) = FAIL", pui8Wbuff[0]);
		return _FAIL;
	}
	return _SUCCESS;
}

//MAX31785 : Burst write
bit WriteRegs_MAX31785(BYTE ui8Addr, WORD u16WBuff)
{
	BYTE pui8Buff[2] = { 0x00, 0x00 };
	pui8Buff[1] = (BYTE)((u16WBuff & 0xFF00) >> 8);
	pui8Buff[0] = (BYTE)((u16WBuff & 0x00FF));

	PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
	if (ScalerMcuHwIICWrite(MAX31785_SLAVE_ADDRESS, 1, ui8Addr, 2, pui8Buff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		// Enable EEPROM Write Protect
		PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

		return _FAIL;
	}
	return _SUCCESS;
}

//MAX31785 : Burst read
WORD ReadRegs_MAX31785(BYTE ui8Addr)
{
	BYTE pui8Buff[2] = { 0x00, 0x00 };
	WORD u16RBuff = 0;

	if (ScalerMcuHwIICRead(MAX31785_SLAVE_ADDRESS, 1, ui8Addr, 2, pui8Buff, _PCB_SYS_EEPROM_IIC) == _FAIL)
	{
		//DebugMessageSystem("MAX31785_ReadRegs(2) = FAIL", _FALSE);
		return _FAIL;
	}
	//DebugMessageSystem("MAX31785_ReadRegs(2) = SUCCESS", _TRUE);
	u16RBuff = (WORD)(pui8Buff[1] << 8);
	u16RBuff |= (WORD)pui8Buff[0];
	//DebugMessageSystem("ReadRegs_MAX31785 (2) addr = SUCCESS", ui8Addr);
	//DebugMessageSystem("ReadRegs_MAX31785 (2) buff = SUCCESS", u16RBuff);
	return u16RBuff;
}

bit SuccessInitialize_MAX31785(void)
{
	return _MAX31785Initialised;
}

void _Get_MAX31785_tempSensorCount(void)
{
	BYTE i;
	WORD u16RBuff = 0;
	for (i = 0; i < 4; i++)
	{
		WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_TEMP0_PAGE + i);
		
		WriteRegs_MAX31785(MAX31785_MFR_TEMP_SENSOR_CONFIG, 0x8000);
		//ScalerTimerDelayXms(50);
		u16RBuff = ReadRegs_MAX31785(MAX31785_READ_TEMPERATURE_1);

		//DebugMessageSystem("_Get_TempSensor ", u16RBuff);

		if (u16RBuff == 0x7FFF)
		{
			//MAX31785_tempSensorCount++; // Temp Sensor error 시에 0x7FFF 반환.
			MAX31785TempSensor[i].tempState = _FALSE;
		}
		else
		{
			MAX31785TempSensor[i].tempState = _TRUE;
		}
	}
}
void MAX31785_EanbleFan(void)
{
	BYTE i;
	for (i = 0; i < 6; i++) // FAN Initialize. PWM0 ~ PWM5
	{
		WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM0_PAGE + i);
		//ScalerTimerDelayXms(50);
		WriteReg_MAX31785(MAX31785_FAN_CONFIG_1_2, MAX31785_FAN_CFG_PWM_ENABLE);
	}
}
void MAX31785_DisableFan(void)
{
	BYTE i;
	for (i = 0; i < 6; i++) // FAN Initialize. PWM0 ~ PWM5
	{
		WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM0_PAGE + i);
		//ScalerTimerDelayXms(50);
		WriteReg_MAX31785(MAX31785_FAN_CONFIG_1_2, 0x00);
	}
}

bit Initialize_MAX31785(void)
{
	WORD i = 0;
	WORD u16RBuff = 0;
	BYTE reg[2] = { 0,0 };
	_MAX31785Initialised = _FALSE;

	WriteReg_MAX31785(MAX31785_SET_PAGE_, 0x00); // 이부분이 없으면 ID를 정상적으로 읽지 못함.
	ReadReg_MAX31785(MAX31785_REG_MFR_ID, &reg[0]);
	WriteReg_MAX31785(MAX31785_SET_PAGE_, 0x00); // 이부분이 없으면 MODEL을 정상적으로 읽지 못함.
	ReadReg_MAX31785(MAX31785_REG_MFR_MODEL, &reg[1]);

	if ((reg[0] != 0x4D) && (reg[1] != 0x53))  // MFR_ID(0x99)-0x4D, MFR_MODEL(0x9A)-0x53 
	{
		return _FALSE;
	}

	MAX31785_EanbleFan();
	_Get_MAX31785_tempSensorCount();
	_MAX31785Initialised = _TRUE;

	return _TRUE;
}
/////////////////////////////////////
// MAX31785 - Page20 참조
// m =1, Y = Register, R =2, b =0
// X = (1/m)*(Y*(10^-R)-b)
//////////////////////////////////////
SBYTE Get_MAX31785_TemperatureValue(WORD temp)
{
	SBYTE s8Retvalue = 0;
	//double tem = 0;

	if (temp == 0x7FFF) return 0;
	s8Retvalue = (SBYTE)(temp * pow(10, -2));
	//tem = floor(temp * pow(10, -2));

	//DebugMessageSystem("Get_MAX31785_TemperatureValue \n\r", tem);
	return s8Retvalue;
}

/////////////////////////////////////
// MAX31785 - Page20 참조
//m =1, Y = Register, R =2, b =0
// X = (1/m)*(Y*(10^-R)-b)
//////////////////////////////////////
WORD Get_MAX31785_PWMValue(BYTE pwm)
{
	float value, temppwm = 0;
	temppwm = pwm;
	value = (temppwm / 255) * 100 * 100;
	return (WORD)value;
}

///////////////////////////////////////////////////
// Temperature Measure 
//////////////////////////////////////////////////

SBYTE Get_MAX31785Temperature(void)
{
	BYTE i, errorCount = 0;
	WORD u16RBuff = 0;
	SBYTE temp = 0;
	SWORD tempSum = 0;

	for (i = 0; i < MAX31785_TEMP_MAX; i++)
	{
		WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_TEMP0_PAGE + i);
		u16RBuff = ReadRegs_MAX31785(MAX31785_READ_TEMPERATURE_1);
		ScalerTimerDelayXms(50); // PAGE 설정 후 Write, Read 후 다음 PAGE Write, Read 할 때 오동작하는 경우가 있어서 추가.
		if (u16RBuff == 0x7FFF)
		{
			MAX31785TempSensor[i].tempState = _FALSE;
			errorCount++;
		}
		else
		{
			MAX31785TempSensor[i].tempState = _TRUE;
			temp = Get_MAX31785_TemperatureValue(u16RBuff);
			//if (i == 2)
			//{
			//	DebugMessageSystem("temp == \n\r", temp);
			//	DebugMessageSystem("u16RBuff == \n\r", u16RBuff);
			//}
			MAX31785TempSensor[i].tempData = (SBYTE)temp;
			tempSum += (SBYTE)temp;
		}
	}
	//tempSum = tempSum /(MAX31785_TEMP_MAX - errorCount);
	tempSum = MAX31785TempSensor[0].tempData;
	for (i = 1; i < MAX31785_TEMP_MAX; i++)
	{
		if(MAX31785TempSensor[i].tempData > tempSum)
			tempSum = MAX31785TempSensor[i].tempData;
	}

	//LOG_INFO("tempSum == %d, MAX31785_tempSensorCount == %d, errorCount == %d\n\r", tempSum, MAX31785_TEMP_MAX, errorCount);
	return tempSum;
}

SBYTE Get_MAX31785Temp1(void)
{
	if(MAX31785TempSensor[0].tempState) return (SBYTE)MAX31785TempSensor[0].tempData;
	else return 0;
}

SBYTE Get_MAX31785Temp2(void)
{
	if (MAX31785TempSensor[1].tempState) return (SBYTE)MAX31785TempSensor[1].tempData;
	else return 0;
}

SBYTE Get_MAX31785Temp3(void)
{
	if (MAX31785TempSensor[2].tempState) return (SBYTE)MAX31785TempSensor[2].tempData;
	else return 0;
}

SBYTE Get_MAX31785Temp4(void)
{
	if (MAX31785TempSensor[3].tempState) return (SBYTE)MAX31785TempSensor[3].tempData;
	else return 0;
}

/////////////////////////////////////////////
// Fan PWM Control.
/////////////////////////////////////////////
void SetFanAllPWM(BYTE u8pwm)
{
	BYTE i;
	WORD setpwm = 0;
	setpwm = Get_MAX31785_PWMValue(u8pwm);

	for (i = 0; i < 6; i++) // FAN Initialize. PWM0 ~ PWM5
	{
		WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM0_PAGE + i);
		//ScalerTimerDelayXms(50);
		WriteRegs_MAX31785(MAX31785_FAN_COMMAND_1, setpwm);
	}
}

void SetFanPWM1(BYTE u8pwm)
{
	WORD setpwm = 0;
	WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM0_PAGE);
	//ScalerTimerDelayXms(50);
	setpwm = Get_MAX31785_PWMValue(u8pwm);
	WriteRegs_MAX31785(MAX31785_FAN_COMMAND_1, setpwm);
}

void SetFanPWM2(BYTE u8pwm)
{
	WORD setpwm = 0;
	WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM1_PAGE);
	//ScalerTimerDelayXms(50);
	setpwm = Get_MAX31785_PWMValue(u8pwm);
	WriteRegs_MAX31785(MAX31785_FAN_COMMAND_1, setpwm);
}

void SetFanPWM3(BYTE u8pwm)
{
	WORD setpwm = 0;
	WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM2_PAGE);
	//ScalerTimerDelayXms(50);
	setpwm = Get_MAX31785_PWMValue(u8pwm);
	WriteRegs_MAX31785(MAX31785_FAN_COMMAND_1, setpwm);
}

void SetFanPWM4(BYTE u8pwm)
{
	WORD setpwm = 0;
	WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM3_PAGE);
	//ScalerTimerDelayXms(50);
	setpwm = Get_MAX31785_PWMValue(u8pwm);
	WriteRegs_MAX31785(MAX31785_FAN_COMMAND_1, setpwm);
}

void SetFanPWM5(BYTE u8pwm)
{
	WORD setpwm = 0;
	WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM4_PAGE);
	//ScalerTimerDelayXms(50);
	setpwm = Get_MAX31785_PWMValue(u8pwm);
	WriteRegs_MAX31785(MAX31785_FAN_COMMAND_1, setpwm);
}

void SetFanPWM6(BYTE u8pwm)
{
	WORD setpwm = 0;
	WriteReg_MAX31785(MAX31785_SET_PAGE_, MAX31785_FAN_PWM5_PAGE);
	//ScalerTimerDelayXms(50);
	setpwm = Get_MAX31785_PWMValue(u8pwm);
	WriteRegs_MAX31785(MAX31785_FAN_COMMAND_1, setpwm);
}

#endif //_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785
