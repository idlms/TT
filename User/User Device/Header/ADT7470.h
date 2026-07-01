/*!
 * @file DFRobot_ADT7470.h
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
#if	(_ENABLE_FAN_CONTROL == _ON &&  _FANCONTROL_SENSOR_TYPE == _FAN_ADT7470)

#ifndef _DFRobot_ADT7470_H_
#define _DFRobot_ADT7470_H_

#define ADT7470_SLAVE_ADDRESS     0x5C // 0x2E

#define ADT7470_CONFIG           (0x40)
#define ADT7470_START_MEASURE	 (0x80 | ADT7470_NORMAL)
#define ADT7470_NORMAL			 (0x01) 	
#define ADT7470_ID               (0x3D)    ///< 0x3D Device ID Register (0x70),  0x3E Company ID Number (0x41)

#define ADT7470_TEMP1_STATUS     (0x20)	// Temperature 1 Reading
#define ADT7470_TEMP2_STATUS     (0x21)	// Temperature 2 Reading
#define ADT7470_TEMP3_STATUS     (0x22)	// Temperature 3 Reading
#define ADT7470_TEMP4_STATUS     (0x23)	// Temperature 4 Reading
#define ADT7470_TEMP5_STATUS     (0x24)	// Temperature 5 Reading

#define ADT7470_PWM1_MAX_DUTY    (0x38)	// PWM MAX 1 Duty
#define ADT7470_PWM2_MAX_DUTY    (0x39)	// PWM MAX 2 Duty
#define ADT7470_PWM3_MAX_DUTY    (0x3A)	// PWM MAX 3 Duty
#define ADT7470_PWM4_MAX_DUTY    (0x3B)	// PWM MAX 4 Duty


bit Initialize_ADT7470(void);
BYTE GetTempCount(void);
SBYTE Get_ADT7470Temperature(void);
SBYTE Get_ADT7470Temp1(void);
SBYTE Get_ADT7470Temp2(void);
SBYTE Get_ADT7470Temp3(void);
SBYTE Get_ADT7470Temp4(void);
SBYTE Get_ADT7470Temp5(void);

bit SuccessInitialize_ADT7470(void);
void SetFanAllPWM(BYTE u8pwm);
void SetFanPWM1(BYTE u8pwm);
void SetFanPWM2(BYTE u8pwm);
void SetFanPWM3(BYTE u8pwm);
void SetFanPWM4(BYTE u8pwm);
bit GetADT7470Config(void);
void SetADT7470Configration(void);

#endif
#endif