//*****************************************************************************
//
// CA310.c - Prototypes for the CA-310 or CA-210 driver.
//
// CA-310 and CA-210 is konica minolta measuring equiment.
//  -. measure luminance and CIE-xye coordinate.
//
// Added by kmshim, Serial Image Co.,Ltd.
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#if	(_ENABLE_LIGHT_SENSOR == _ON)
#if(_LIGHT_SENSOR_TYPE == _LIGHT_CM32181)
#ifndef __CM32181_H__
#define __CM32181_H__


#define CM32181_ADDRESS				0x20 // 0x10 //Mstar driver use 8bit address.
	/* Registers Address */
#define CM32181_REG_ADDR_CMD		0x00
#define CM32181_REG_ADDR_ALS		0x04
#define CM32181_REG_ADDR_STATUS		0x06
#define CM32181_REG_ADDR_ID			0x07

	/* Number of Configurable Registers */
#define CM32181_CONF_REG_NUM		0x01

	/* CMD register */
#define CM32181_CMD_ALS_ENABLE		0x00
#define CM32181_CMD_ALS_DISABLE		0x01
#define CM32181_CMD_ALS_INT_EN		0x02

#define CM32181_CMD_ALS_IT_SHIFT	6
#define CM32181_CMD_ALS_IT_MASK		(0x0F << CM32181_CMD_ALS_IT_SHIFT)
#define CM32181_CMD_ALS_IT_DEFAULT	(0x00 << CM32181_CMD_ALS_IT_SHIFT)

#define CM32181_CMD_ALS_SM_SHIFT	11
#define CM32181_CMD_ALS_SM_MASK		(0x03 << CM32181_CMD_ALS_SM_SHIFT)
#define CM32181_CMD_ALS_SM_DEFAULT	(0x01 << CM32181_CMD_ALS_SM_SHIFT)

#define CM32181_SHUTDOWN			0x01	/* Power Shutdown */

#define CM32181_MLUX_PER_BIT		5	/* ALS_SM=01 IT=800ms */
#define CM32181_MLUX_PER_BIT_BASE_IT	800000	/* Based on IT=800ms */
#define	CM32181_CALIBSCALE_DEFAULT	1000
#define CM32181_CALIBSCALE_RESOLUTION	1000
#define MLUX_PER_LUX			1000	
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

	bit Cm32181_init(void);
	//bit Cm32181_Shudown(void);
	//DWORD Cm32181_read_als_it(void);
	//void Cm32181_write_als_it(int val);
	DWORD Cm32181_get_lux(void);
	bit SuccessInitialize_CM3281(void);

	//extern tLightSensorEntry  gstCM32181Driver;
#endif //

#endif
#endif