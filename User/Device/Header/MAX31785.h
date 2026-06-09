/*!
 * @file DFRobot_MAX31785.h
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
#if	(_ENABLE_FAN_CONTROL == _ON &&  _FANCONTROL_SENSOR_TYPE == _FAN_MAX31785)

#ifndef _FanControl_MAX31785_H_
#define _FanControl_MAX31785_H_

#define MAX31785_SLAVE_ADDRESS						0xA4  //(E_I2C_BUS_SYS<<8 | (0x52<<1))

#define MAX31785_TEMP_MAX							4

#define MAX31785_SET_PAGE_							(0x00)
#define MAX31785_START_MEASURE						(0x80 | MAX31785_NORMAL)
#define MAX31785_NORMAL								(0x01) 	
#define MAX31785_RESTORE_DEFAULT_ALL				(0x12)    ///

#define MAX31785_FAN_CONFIG_1_2						(0x3A)	
#define MAX31785_FAN_COMMAND_1						(0x3B)

#define MAX31785_READ_TEMPERATURE_1					(0x8D)

#define MAX31785_TEMP0_PAGE							(0x0D)	// Temperature 1 Reading
#define MAX31785_TEMP1_PAGE							(0x0E)	// Temperature 2 Reading
#define MAX31785_TEMP2_PAGE							(0x0F)	// Temperature 3 Reading
#define MAX31785_TEMP3_PAGE							(0x10)	// Temperature 4 Reading

#define MAX31785_FAN_PWM0_PAGE						(0x00)	// PWM0  
#define MAX31785_FAN_PWM1_PAGE						(0x01)	// PWM1  
#define MAX31785_FAN_PWM2_PAGE						(0x02)	// PWM2  
#define MAX31785_FAN_PWM3_PAGE						(0x03)	// PWM3  
#define MAX31785_FAN_PWM4_PAGE						(0x04)	// PWM4 
#define MAX31785_FAN_PWM5_PAGE						(0x05)	// PWM5



#define MAX31785_REG_MFR_ID							(0x99) 
#define MAX31785_REG_MFR_MODEL						(0x9A)
#define MAX31785_MFR_TEMP_SENSOR_CONFIG			    (0xF0)
#define MAX31785_REG_MFR_FAN_CONFIG					(0xF1)	
#define MAX31785_REG_READ_FAN_PWM					(0xF3)

#define MAX31785_FAN_CFG_PWM_ENABLE					(0x80)
#define MAX31785_FAN_CFG_CONTROL_MODE_RPM			(0x40)

typedef struct
{
	BYTE tempState : 1;
	SWORD tempData;
}TEMPSENSORSTAUS;

void MAX31785_EanbleFan(void);
void MAX31785_DisableFan(void);
bit Initialize_MAX31785(void);
bit SuccessInitialize_MAX31785(void);
SBYTE Get_MAX31785Temperature(void);
SBYTE Get_MAX31785Temp1(void);
SBYTE Get_MAX31785Temp2(void);
SBYTE Get_MAX31785Temp3(void);
SBYTE Get_MAX31785Temp4(void);


void SetFanAllPWM(BYTE u8pwm);
void SetFanPWM1(BYTE u8pwm);
void SetFanPWM2(BYTE u8pwm);
void SetFanPWM3(BYTE u8pwm);
void SetFanPWM4(BYTE u8pwm);
void SetFanPWM5(BYTE u8pwm);
void SetFanPWM6(BYTE u8pwm);
//extern tFanControlEntry fanControlMAX31785Driver;
extern TEMPSENSORSTAUS MAX31785TempSensor[MAX31785_TEMP_MAX];
#endif

#endif //_FANCONTROL_SENSOR_TYPE == _FAN_MAX31785