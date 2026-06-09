//----------------------------------------------------------------------------------------------------
// ID Code      : SysUart.c No.0000		
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_UART__

#include "SysInclude.h"
#include "RTD2014Include.h"



#if(_DISTECK_UART_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _UART_STB		0xaa
#define _UART_MID		0x20
#define _UART_ACK		'\x06'
#define _UART_NAK		'\x15'
#define _UART_RFACK		'\x6e'


#define _UART_ASCII_SPACE		0x20
#define _UART_ASCII_0		0x30
#define _UART_ASCII_CR		0x0D





//#define TX_BUFFER_SIZE		40		// tx buffer size
//#define RX_BUFFER_SIZE		16		// rx buffer size

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructUartType idata g_stUartData = {0};


//****************************************************************************
// CODE TABLES
//****************************************************************************


///*
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucUartRxBuf[_UART_RXBUF_LENGTH];
BYTE g_ucUartTxBuf[_UART_TXBUF_LENGTH];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
void SysUartInitRx(void)
{
    // Clear buffer for new message
    memset(g_ucUartRxBuf, 0, _UART_RXBUF_LENGTH);
    g_stUartData.g_ucUartRxConunt = 0;
}

//Eric_20170308 : Delete
//    void SysUartInitTx(void)
//    {
//        // Clear buffer for new message
//    	memset(g_ucUartTxBuf, 0, _UART_TXBUF_LENGTH);
//    	g_stUartData.g_ucUartTxConunt = 0;
//    	SET_UART_TX_COMMAND(_DISABLE);
//    
//    }

//----------------------------------------------------------------------------------------
// Extern functions from SysPower.c
//----------------------------------------------------------------------------------------
extern BYTE SysPowerGetPowerStatus(void);
extern void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus);
//#if(_DISTECK_UART_SUPPORT==_ON)
//extern void RTDOsdUartGetSetMsgProc(BYTE ucUartCmd, BYTE ucUartRw, BYTE ucUartData);	
extern void RTDOsdUartMsgProc(BYTE ucUartCmd, BYTE ucUartData);
extern void RTDOsdUartMsgProc_2(BYTE ucUartCmd, BYTE ucUartData);
extern BYTE g_ucKeyStateSkip;

//#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysUartHandler(void);
//void SysUartDebugMessage(unsigned char *string);
//void CUartTransferNumToScr(WORD ch, BYTE mode );
void SysUartSetTxCommand(BYTE ucTxCmd, BYTE ucTxStatus, BYTE ucTxData);

void SysUartGetCommand(void)
{
	// if (g_stUartData.g_ucUartRxConunt > 8)
	//{
	//	//DebugMessageSystem(" _UART_RX_ID_09  ", g_ucUartRxBuf[_UART_RX_ID_09]);
	//	//DebugMessageSystem(" _UART_RX_ID_10  ", g_ucUartRxBuf[_UART_RX_ID_10]);
	// }

	switch (g_ucUartRxBuf[_UART_RX_CMD2_01])
	{
	case _UART_CMD2_POWER:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_POWER, 0x00);
			SysUartSetTxCommand(_UART_CMD2_POWER, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_POWER, 0x01);
			SysUartSetTxCommand(_UART_CMD2_POWER, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_POWER, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_POWER, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_DISPLAYMODE:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DISPLAYMODE, 0x00);
			SysUartSetTxCommand(_UART_CMD2_DISPLAYMODE, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DISPLAYMODE, 0x01);
			SysUartSetTxCommand(_UART_CMD2_DISPLAYMODE, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DISPLAYMODE, 0x02);
			SysUartSetTxCommand(_UART_CMD2_DISPLAYMODE, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DISPLAYMODE, 0x03);
			SysUartSetTxCommand(_UART_CMD2_DISPLAYMODE, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DISPLAYMODE, 0x04);
			SysUartSetTxCommand(_UART_CMD2_DISPLAYMODE, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '5'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DISPLAYMODE, 0x05);
			SysUartSetTxCommand(_UART_CMD2_DISPLAYMODE, _SUCCESS, 0x05);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DISPLAYMODE, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_DISPLAYMODE, _FALSE, 0x01);
		}
		break;

	case _UART_CMD2_P1_INPUT_SEL:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P1_INPUT_SEL, 0x01);
			SysUartSetTxCommand(_UART_CMD2_P1_INPUT_SEL, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P1_INPUT_SEL, 0x02);
			SysUartSetTxCommand(_UART_CMD2_P1_INPUT_SEL, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P1_INPUT_SEL, 0x03);
			SysUartSetTxCommand(_UART_CMD2_P1_INPUT_SEL, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P1_INPUT_SEL, 0x04);
			SysUartSetTxCommand(_UART_CMD2_P1_INPUT_SEL, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P1_INPUT_SEL, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P1_INPUT_SEL, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_P2_INPUT_SEL:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P2_INPUT_SEL, 0x01);
			SysUartSetTxCommand(_UART_CMD2_P2_INPUT_SEL, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P2_INPUT_SEL, 0x02);
			SysUartSetTxCommand(_UART_CMD2_P2_INPUT_SEL, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P2_INPUT_SEL, 0x03);
			SysUartSetTxCommand(_UART_CMD2_P2_INPUT_SEL, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P2_INPUT_SEL, 0x04);
			SysUartSetTxCommand(_UART_CMD2_P2_INPUT_SEL, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P2_INPUT_SEL, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P2_INPUT_SEL, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_P3_INPUT_SEL:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P3_INPUT_SEL, 0x01);
			SysUartSetTxCommand(_UART_CMD2_P3_INPUT_SEL, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P3_INPUT_SEL, 0x02);
			SysUartSetTxCommand(_UART_CMD2_P3_INPUT_SEL, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P3_INPUT_SEL, 0x03);
			SysUartSetTxCommand(_UART_CMD2_P3_INPUT_SEL, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P3_INPUT_SEL, 0x04);
			SysUartSetTxCommand(_UART_CMD2_P3_INPUT_SEL, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P3_INPUT_SEL, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P3_INPUT_SEL, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_P4_INPUT_SEL:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P4_INPUT_SEL, 0x01);
			SysUartSetTxCommand(_UART_CMD2_P4_INPUT_SEL, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P4_INPUT_SEL, 0x02);
			SysUartSetTxCommand(_UART_CMD2_P4_INPUT_SEL, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P4_INPUT_SEL, 0x03);
			SysUartSetTxCommand(_UART_CMD2_P4_INPUT_SEL, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P4_INPUT_SEL, 0x04);
			SysUartSetTxCommand(_UART_CMD2_P4_INPUT_SEL, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_P4_INPUT_SEL, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P4_INPUT_SEL, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_ASPECT:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_ASPECT, 0x00);
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_ASPECT, 0x01);
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_ASPECT, 0x02);
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_ASPECT, 0x03);
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_ASPECT, 0x04);
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_ASPECT, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_ASPECT, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_BACKLIGHT:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA1_06] <= '6'))
		{
			BYTE ucUartlowTemp;
			BYTE ucUartUpperTemp;

			ucUartUpperTemp = (g_ucUartRxBuf[_UART_RX_DATA1_06] - '0') * 0x10;
			if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= '9'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - '0';
			}
			else if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= 'a') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= 'f'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - 'a' + 10;
			}
			ucUartUpperTemp = ucUartUpperTemp + ucUartlowTemp;
			if (ucUartUpperTemp <= 100)
			{
				RTDOsdUartMsgProc(_UART_CMD2_BACKLIGHT, ucUartUpperTemp);
				SysUartSetTxCommand(_UART_CMD2_BACKLIGHT, _SUCCESS, ucUartUpperTemp);
			}
			else
				SysUartSetTxCommand(_UART_CMD2_BACKLIGHT, _FALSE, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_BACKLIGHT, 0xff);
		}
		else
			SysUartSetTxCommand(_UART_CMD2_BACKLIGHT, _FALSE, 0x01);
		break;
	case _UART_CMD2_CONTRAST:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA1_06] <= '6'))
		{
			BYTE ucUartlowTemp;
			BYTE ucUartUpperTemp;

			ucUartUpperTemp = (g_ucUartRxBuf[_UART_RX_DATA1_06] - '0') * 0x10;
			if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= '9'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - '0';
			}
			else if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= 'a') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= 'f'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - 'a' + 10;
			}
			ucUartUpperTemp = ucUartUpperTemp + ucUartlowTemp;
			if (ucUartUpperTemp <= 100)
			{
				RTDOsdUartMsgProc(_UART_CMD2_CONTRAST, ucUartUpperTemp);
				SysUartSetTxCommand(_UART_CMD2_CONTRAST, _SUCCESS, ucUartUpperTemp);
			}
			else
				SysUartSetTxCommand(_UART_CMD2_CONTRAST, _FALSE, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_CONTRAST, 0xff);
		}
		else
			SysUartSetTxCommand(_UART_CMD2_CONTRAST, _FALSE, 0x01);

		break;
	case _UART_CMD2_BRIGHTNESS:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA1_06] <= '6'))
		{
			BYTE ucUartlowTemp;
			BYTE ucUartUpperTemp;

			ucUartUpperTemp = (g_ucUartRxBuf[_UART_RX_DATA1_06] - '0') * 0x10;
			if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= '9'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - '0';
			}
			else if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= 'a') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= 'f'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - 'a' + 10;
			}
			ucUartUpperTemp = ucUartUpperTemp + ucUartlowTemp;
			if (ucUartUpperTemp <= 100)
			{
				RTDOsdUartMsgProc(_UART_CMD2_BRIGHTNESS, ucUartUpperTemp);
				SysUartSetTxCommand(_UART_CMD2_BRIGHTNESS, _SUCCESS, ucUartUpperTemp);
			}
			else
				SysUartSetTxCommand(_UART_CMD2_BRIGHTNESS, _FALSE, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_BRIGHTNESS, 0xff);
		}
		else
			SysUartSetTxCommand(_UART_CMD2_BRIGHTNESS, _FALSE, 0x01);
		break;

	case _UART_CMD2_SHARPNESS:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SHARPNESS, 0x00);
			SysUartSetTxCommand(_UART_CMD2_SHARPNESS, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SHARPNESS, 0x01);
			SysUartSetTxCommand(_UART_CMD2_SHARPNESS, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SHARPNESS, 0x02);
			SysUartSetTxCommand(_UART_CMD2_SHARPNESS, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SHARPNESS, 0x03);
			SysUartSetTxCommand(_UART_CMD2_SHARPNESS, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SHARPNESS, 0x04);
			SysUartSetTxCommand(_UART_CMD2_SHARPNESS, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SHARPNESS, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_SHARPNESS, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_GAMMA:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_GAMMA, 0x00);
			SysUartSetTxCommand(_UART_CMD2_GAMMA, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_GAMMA, 0x01);
			SysUartSetTxCommand(_UART_CMD2_GAMMA, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_GAMMA, 0x02);
			SysUartSetTxCommand(_UART_CMD2_GAMMA, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_GAMMA, 0x03);
			SysUartSetTxCommand(_UART_CMD2_GAMMA, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_GAMMA, 0x04);
			SysUartSetTxCommand(_UART_CMD2_GAMMA, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_GAMMA, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_GAMMA, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_TEMP:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_TEMP, 0x00);
			SysUartSetTxCommand(_UART_CMD2_TEMP, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_TEMP, 0x01);
			SysUartSetTxCommand(_UART_CMD2_TEMP, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_TEMP, 0x02);
			SysUartSetTxCommand(_UART_CMD2_TEMP, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_TEMP, 0x03);
			SysUartSetTxCommand(_UART_CMD2_TEMP, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_TEMP, 0x04);
			SysUartSetTxCommand(_UART_CMD2_TEMP, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_TEMP, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_TEMP, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_COLOR_EFFECT:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_COLOR_EFFECT, 0x00);
			SysUartSetTxCommand(_UART_CMD2_COLOR_EFFECT, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_COLOR_EFFECT, 0x01);
			SysUartSetTxCommand(_UART_CMD2_COLOR_EFFECT, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_COLOR_EFFECT, 0x02);
			SysUartSetTxCommand(_UART_CMD2_COLOR_EFFECT, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_COLOR_EFFECT, 0x03);
			SysUartSetTxCommand(_UART_CMD2_COLOR_EFFECT, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_COLOR_EFFECT, 0x04);
			SysUartSetTxCommand(_UART_CMD2_COLOR_EFFECT, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_COLOR_EFFECT, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_COLOR_EFFECT, _FALSE, 0x01);
		}
		break;

	case _UART_CMD2_AUDIO_SELSEL:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_SELSEL, 0x01);
			SysUartSetTxCommand(_UART_CMD2_AUDIO_SELSEL, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_SELSEL, 0x02);
			SysUartSetTxCommand(_UART_CMD2_AUDIO_SELSEL, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '3'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_SELSEL, 0x03);
			SysUartSetTxCommand(_UART_CMD2_AUDIO_SELSEL, _SUCCESS, 0x03);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '4'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_SELSEL, 0x04);
			SysUartSetTxCommand(_UART_CMD2_AUDIO_SELSEL, _SUCCESS, 0x04);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_SELSEL, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_AUDIO_SELSEL, _FALSE, 0x01);
		}
		break;

	case _UART_CMD2_SCREEN_MUTE:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SCREEN_MUTE, 0x00);
			SysUartSetTxCommand(_UART_CMD2_SCREEN_MUTE, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SCREEN_MUTE, 0x01);
			SysUartSetTxCommand(_UART_CMD2_SCREEN_MUTE, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_SCREEN_MUTE, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_SCREEN_MUTE, _FALSE, 0x01);
		}

		break;

	case _UART_CMD2_AUDIO_MUTE:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_MUTE, 0x00);
			SysUartSetTxCommand(_UART_CMD2_AUDIO_MUTE, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_MUTE, 0x01);
			SysUartSetTxCommand(_UART_CMD2_AUDIO_MUTE, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_MUTE, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_AUDIO_MUTE, _FALSE, 0x01);
		}

		break;

	case _UART_CMD2_AUDIO_VOL:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA1_06] <= '6'))
		{
			BYTE ucUartlowTemp;
			BYTE ucUartUpperTemp;

			ucUartUpperTemp = (g_ucUartRxBuf[_UART_RX_DATA1_06] - '0') * 0x10;
			if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= '9'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - '0';
			}
			else if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= 'a') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= 'f'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - 'a' + 10;
			}
			ucUartUpperTemp = ucUartUpperTemp + ucUartlowTemp;
			if (ucUartUpperTemp <= 100)
			{
				RTDOsdUartMsgProc(_UART_CMD2_AUDIO_VOL, ucUartUpperTemp);
				SysUartSetTxCommand(_UART_CMD2_AUDIO_VOL, _SUCCESS, ucUartUpperTemp);
			}
			else
				SysUartSetTxCommand(_UART_CMD2_AUDIO_VOL, _FALSE, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_AUDIO_VOL, 0xff);
		}
		else
			SysUartSetTxCommand(_UART_CMD2_AUDIO_VOL, _FALSE, 0x01);
		break;

	case _UART_CMD2_FAST_SWAP: // 'q'
		if (g_ucUartRxBuf[_UART_RX_NULL_03] == '0' &&
			g_ucUartRxBuf[_UART_RX_NULL_04] == '0' &&
			g_ucUartRxBuf[_UART_RX_DATA1_06] == '0' &&
			g_ucUartRxBuf[_UART_RX_DATA2_07] == '0')
		{
			BYTE u8_CurrentMode = GET_OSD_DISPLAY_MODE();
			if (u8_CurrentMode == _OSD_DM_2P_LR ||
				u8_CurrentMode == _OSD_DM_2P_TB ||
				u8_CurrentMode == _OSD_DM_2P_PIP)
			{
				RTDOsdUartMsgProc(_UART_CMD2_FAST_SWAP, 0x00);
			}
			else
			{
				SysUartSetTxCommand(_UART_CMD2_FAST_SWAP, _FALSE, 0x00);
			}
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_FAST_SWAP, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_PIP_SIZE:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA1_06] <= '2'))
		{
			BYTE ucUartlowTemp;
			BYTE ucUartUpperTemp;

			ucUartUpperTemp = (g_ucUartRxBuf[_UART_RX_DATA1_06] - '0') * 0x10;
			if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= '9'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - '0';
			}
			else if ((g_ucUartRxBuf[_UART_RX_DATA2_07] >= 'a') && (g_ucUartRxBuf[_UART_RX_DATA2_07] <= 'f'))
			{
				ucUartlowTemp = g_ucUartRxBuf[_UART_RX_DATA2_07] - 'a' + 10;
			}
			ucUartUpperTemp = ucUartUpperTemp + ucUartlowTemp;
			if (ucUartUpperTemp <= 10)
			{
				RTDOsdUartMsgProc(_UART_CMD2_PIP_SIZE, ucUartUpperTemp);
				SysUartSetTxCommand(_UART_CMD2_PIP_SIZE, _SUCCESS, ucUartUpperTemp);
			}
			else
				SysUartSetTxCommand(_UART_CMD2_PIP_SIZE, _FALSE, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_BACKLIGHT, 0xff);
		}
		else
			SysUartSetTxCommand(_UART_CMD2_BACKLIGHT, _FALSE, 0x01);
		break;
#if 0
		case _UART_CND2_SLOW_SWAP :	// 's'
			if (	g_ucUartRxBuf[_UART_RX_NULL_03] == '0' &&
				g_ucUartRxBuf[_UART_RX_NULL_04] == '0' &&
				g_ucUartRxBuf[_UART_RX_DATA1_06] == '0' &&
				g_ucUartRxBuf[_UART_RX_DATA2_07] == '0' )
			{
				if(	(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) ||
					(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) ||
					(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP) )
				{
					RTDOsdUartMsgProc(_UART_CND2_SLOW_SWAP, 0x00);
					SysUartSetTxCommand(_UART_CND2_SLOW_SWAP, _SUCCESS, 0x00);
				}
				else
				{
					SysUartSetTxCommand(_UART_CND2_SLOW_SWAP, _FALSE, 0x00);
				}
			}
			else
			{
				SysUartSetTxCommand(_UART_CND2_SLOW_SWAP, _FALSE, 0x01);
			}
			break;
#endif

#if (_ENABLE_LIGHT_SENSOR == _ON)
	case _UART_CMD2_LIGHT_SENSOR:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_LIGHT_SENSOR, 0x00);
			SysUartSetTxCommand(_UART_CMD2_LIGHT_SENSOR, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_LIGHT_SENSOR, 0x01);
			SysUartSetTxCommand(_UART_CMD2_LIGHT_SENSOR, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_LIGHT_SENSOR, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_LIGHT_SENSOR, _FALSE, 0x01);
		}
		break;
#endif
	case _UART_CMD2_DP_FORMAT:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_FORMAT, 0x00);
			SysUartSetTxCommand(_UART_CMD2_DP_FORMAT, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_FORMAT, 0x01);
			SysUartSetTxCommand(_UART_CMD2_DP_FORMAT, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_FORMAT, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_DP_FORMAT, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_DP_MST:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_MST, 0x00);
			SysUartSetTxCommand(_UART_CMD2_DP_MST, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_MST, 0x01);
			SysUartSetTxCommand(_UART_CMD2_DP_MST, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '2'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_MST, 0x01);
			SysUartSetTxCommand(_UART_CMD2_DP_MST, _SUCCESS, 0x02);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_MST, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_DP_MST, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_DP_CLONE:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_CLONE, 0x00);
			SysUartSetTxCommand(_UART_CMD2_DP_CLONE, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_CLONE, 0x01);
			SysUartSetTxCommand(_UART_CMD2_DP_CLONE, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_DP_CLONE, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_DP_CLONE, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_VIDEO_WALL:
		if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '0'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_VIDEO_WALL, 0x00);
			SysUartSetTxCommand(_UART_CMD2_VIDEO_WALL, _SUCCESS, 0x00);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == '0') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == '1'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_VIDEO_WALL, 0x01);
			SysUartSetTxCommand(_UART_CMD2_VIDEO_WALL, _SUCCESS, 0x01);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc(_UART_CMD2_VIDEO_WALL, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_VIDEO_WALL, _FALSE, 0x01);
		}
		break;
	}
}


void SysUartGetCommand_2(void)
{
	
	switch (g_ucUartRxBuf[_UART_RX_CMD2_01])
	{
	case _UART_CMD2_P1_ASPECT:
		if (g_ucUartRxBuf[_UART_RX_DATA1_06] == '0')
		{		
			BYTE ucData = 0xff;
			switch (g_ucUartRxBuf[_UART_RX_DATA2_07])
			{
			case '0': ucData = 0x00; break;
			case '1': ucData = 0x01; break;
			case '2': ucData = 0x02; break;
			case '3': ucData = 0x03; break;
			case '4': ucData = 0x04; break;
			default:
				SysUartSetTxCommand(_UART_CMD2_P1_ASPECT, _FALSE, 0x01); return;

			}
			RTDOsdUartMsgProc_2(_UART_CMD2_P1_ASPECT, ucData);
			SysUartSetTxCommand(_UART_CMD2_P1_ASPECT, _SUCCESS, ucData);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc_2(_UART_CMD2_P1_ASPECT, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P1_ASPECT, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_P2_ASPECT:
		if (g_ucUartRxBuf[_UART_RX_DATA1_06] == '0')
		{
			BYTE ucData = 0xff;
			switch (g_ucUartRxBuf[_UART_RX_DATA2_07])
			{
			case '0': ucData = 0x00; break;
			case '1': ucData = 0x01; break;
			case '2': ucData = 0x02; break;
			case '3': ucData = 0x03; break;
			case '4': ucData = 0x04; break;
			default:
				SysUartSetTxCommand(_UART_CMD2_P2_ASPECT, _FALSE, 0x01); return;

			}
			RTDOsdUartMsgProc_2(_UART_CMD2_P2_ASPECT, ucData);
			SysUartSetTxCommand(_UART_CMD2_P2_ASPECT, _SUCCESS, ucData);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc_2(_UART_CMD2_P2_ASPECT, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P2_ASPECT, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_P3_ASPECT:
		if (g_ucUartRxBuf[_UART_RX_DATA1_06] == '0')
		{
			BYTE ucData = 0xff;
			switch (g_ucUartRxBuf[_UART_RX_DATA2_07])
			{
			case '0': ucData = 0x00; break;
			case '1': ucData = 0x01; break;
			case '2': ucData = 0x02; break;
			case '3': ucData = 0x03; break;
			case '4': ucData = 0x04; break;
			default:
				SysUartSetTxCommand(_UART_CMD2_P3_ASPECT, _FALSE, 0x01); return;

			}
			RTDOsdUartMsgProc_2(_UART_CMD2_P3_ASPECT, ucData);
			SysUartSetTxCommand(_UART_CMD2_P3_ASPECT, _SUCCESS, ucData);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc_2(_UART_CMD2_P3_ASPECT, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P3_ASPECT, _FALSE, 0x01);
		}
		break;
	case _UART_CMD2_P4_ASPECT:
		if (g_ucUartRxBuf[_UART_RX_DATA1_06] == '0')
		{
			BYTE ucData = 0xff;
			switch (g_ucUartRxBuf[_UART_RX_DATA2_07])
			{
			case '0': ucData = 0x00; break;
			case '1': ucData = 0x01; break;
			case '2': ucData = 0x02; break;
			case '3': ucData = 0x03; break;
			case '4': ucData = 0x04; break;
			default:
				SysUartSetTxCommand(_UART_CMD2_P4_ASPECT, _FALSE, 0x01); return;

			}
			RTDOsdUartMsgProc_2(_UART_CMD2_P4_ASPECT, ucData);
			SysUartSetTxCommand(_UART_CMD2_P4_ASPECT, _SUCCESS, ucData);
		}
		else if ((g_ucUartRxBuf[_UART_RX_DATA1_06] == 'f') && (g_ucUartRxBuf[_UART_RX_DATA2_07] == 'f'))
		{
			RTDOsdUartMsgProc_2(_UART_CMD2_P4_ASPECT, 0xff);
		}
		else
		{
			SysUartSetTxCommand(_UART_CMD2_P4_ASPECT, _FALSE, 0x01);
		}
		break;
	default:

		break;
	}
}

void SysUartGetKeyMsg(void)
{
	if(g_ucUartRxBuf[_UART_RX_CMD2_01] == 'k')
	{
		switch(g_ucUartRxBuf[_UART_RX_DATA2_07])
		{
			case _UART_CMD2_POWER_KEY : 
				{
			       if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
						SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
					else
						SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
					
					SysUartSetTxCommand('k', _SUCCESS, 0x00);
				}
			break;
			case _UART_CMD2_MENU_KEY : 
				{
					g_ucKeyStateSkip = 1;
					SET_KEYMESSAGE(_MENU_KEY_MESSAGE);

					SysUartSetTxCommand('k', _SUCCESS, 0x01);
				}
			break;
			case _UART_CMD2_LEFT_KEY: 
				{
					g_ucKeyStateSkip = 1;
					SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
					SysUartSetTxCommand('k', _SUCCESS, 0x02);
				}
			break;
			case _UART_CMD2_RIGHT_KEY: 
				{
					g_ucKeyStateSkip = 1;
					SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
					SysUartSetTxCommand('k', _SUCCESS, 0x03);
				}
			break;		
			case _UART_CMD2_DOWN_KEY : 
				{
					g_ucKeyStateSkip = 1;
					SET_KEYMESSAGE(_DOWN_KEY_MESSAGE);
					SysUartSetTxCommand('k', _SUCCESS, 0x04);
				}
			break;
			case _UART_CMD2_UP_KEY : 
				{
					g_ucKeyStateSkip = 1;
					SET_KEYMESSAGE(_UP_KEY_MESSAGE);
					SysUartSetTxCommand('k', _SUCCESS, 0x05);
				}
			break;		
			case _UART_CMD2_SOURCE_KEY : 
				{
					g_ucKeyStateSkip = 1;
					SET_KEYMESSAGE(_SELECT_KEY_MESSAGE);
					SysUartSetTxCommand('k', _SUCCESS, 0x06);
				}
			break;	
			default :
					SysUartSetTxCommand('k', _FALSE, 0x01);
			break;	
		}
	}
	else 
	{
		SysUartSetTxCommand('k', _FALSE, 0x01);

	}
}

void SysUartSetTxCommand(BYTE ucTxCmd, BYTE ucTxStatus, BYTE ucTxData)
{
	BYTE ucTxCount = 0;
	BYTE ucRowData = 0;
	BYTE ucUpperData = 0;

	g_ucUartTxBuf[_UART_TX_CMD2_00] = ucTxCmd;
	g_ucUartTxBuf[_UART_TX_SPACE_01] = _UART_ASCII_SPACE;
	g_ucUartTxBuf[_UART_TX_NULL_02] = _UART_ASCII_0;
	g_ucUartTxBuf[_UART_TX_NULL_03] = _UART_ASCII_0;
	g_ucUartTxBuf[_UART_TX_SPACE_04] = _UART_ASCII_SPACE;

	if (ucTxStatus == _SUCCESS)
	{
		g_ucUartTxBuf[_UART_TX_STATUS1_05] = 'O';
		g_ucUartTxBuf[_UART_TX_STATUS2_06] = 'K';
	}
	else
	{
		g_ucUartTxBuf[_UART_TX_STATUS1_05] = 'N';
		g_ucUartTxBuf[_UART_TX_STATUS2_06] = 'G';
	}

	ucUpperData = ucTxData >> 4 & 0x0F;
	ucRowData = ucTxData & 0x0F;
	if (ucUpperData > 9) g_ucUartTxBuf[_UART_TX_DATA1_07] = ucUpperData + 'A' - 10;
	else g_ucUartTxBuf[_UART_TX_DATA1_07] = ucUpperData + '0';
	if (ucRowData > 9)  g_ucUartTxBuf[_UART_TX_DATA2_08] = ucRowData + 'A' - 10;
	else  g_ucUartTxBuf[_UART_TX_DATA2_08] = ucRowData + '0';
/*
#if( _ENABLE_VIDEO_WALL == _ON)

	if (GetVideoWallStatus() == _ON)
	{
		//BYTE ucUartlowTemp;
		//BYTE ucUartUpperTemp;

		//ucUartUpperTemp = (g_ucUartRxBuf[_UART_RX_ID_09] - '0') * 0x10;
		//if ((g_ucUartRxBuf[_UART_RX_ID_10] >= '0') && (g_ucUartRxBuf[_UART_RX_ID_10] <= '9'))
		//{
		//	ucUartlowTemp = g_ucUartRxBuf[_UART_RX_ID_10] - '0';
		//}
		//else if ((g_ucUartRxBuf[_UART_RX_ID_10] >= 'a') && (g_ucUartRxBuf[_UART_RX_ID_10] <= 'f'))
		//{
		//	ucUartlowTemp = g_ucUartRxBuf[_UART_RX_ID_10] - 'a' + 10;
		//}
		//ucUartUpperTemp = ucUartUpperTemp + ucUartlowTemp;
		g_ucUartTxBuf[_UART_TX_SPACE_09] = _UART_ASCII_SPACE;
		g_ucUartTxBuf[_UART_TX_ID_10] = g_ucUartRxBuf[_UART_RX_ID_09];
		g_ucUartTxBuf[_UART_TX_ID_11] = g_ucUartRxBuf[_UART_RX_ID_10];
		g_ucUartTxBuf[_UART_TX_ASC_X_12] = 'x';
		g_ucUartTxBuf[_UART_TX_CR_13] = (BYTE)_UART_ASCII_CR;
		for (ucTxCount = 0; ucTxCount <= _UART_TX_CR_13; ucTxCount++)
		{
			ScalerMcuUartWrite(g_ucUartTxBuf[ucTxCount]);
		}
	}
	else
	{
		g_ucUartTxBuf[_UART_TX_SPACE_09] = 'x';
		g_ucUartTxBuf[_UART_TX_ID_10] = _UART_ASCII_CR;

		for (ucTxCount = 0; ucTxCount <= _UART_TX_ID_10; ucTxCount++)
		{
			ScalerMcuUartWrite(g_ucUartTxBuf[ucTxCount]);
		}
}


#else
*/
	g_ucUartTxBuf[_UART_TX_ASC_X_09] = 'x';
	g_ucUartTxBuf[_UART_TX_CR_10] = _UART_ASCII_CR;

	for (ucTxCount = 0; ucTxCount <= _UART_TX_CR_10; ucTxCount++)
	{
		ScalerMcuUartWrite(g_ucUartTxBuf[ucTxCount]);
	}
//#endif
}

void SysUartHandler(void)
{
	if (GET_RUN_UART_COMMAND() == _SUCCESS)
	{
		switch (g_ucUartRxBuf[_UART_RX_CMD1_00])
		{
		case 'k':
			SysUartGetCommand();
			break;
		case 'i':
			SysUartGetCommand_2();
			break;
		case 'm':
			SysUartGetKeyMsg();
			break;
		default:
			break;
		}
		SysUartInitRx();
		SET_RUN_UART_COMMAND(_FAIL);
		//		SET_UART_TX_COMMAND(_ENABLE);

		g_bFgUartTimeOutClearEn = _FALSE; // UartTimeOut
	}

	if ((g_usTimerUartTimeOut <= 0) && (g_bFgUartTimeOutClearEn)) // UartTimeOut
	{
		SysUartInitRx();
		g_bFgUartTimeOutClearEn = _FALSE;
		// printf("SysUartInitRx()\n\r");
	}

	//	if(GET_UART_TX_COMMAND() == _ENABLE)
	{
		//		SysUartInitTx();
	}
}


/*
void put_Hex(unsigned char c)
{
	unsigned char hi,lo;
	hi = c>>4 & 0x0F;
	lo = c & 0x0F;
	if(hi>9) put_data('A'+hi-10);
	else put_data('0' + hi);
	if(lo>9) put_data('A'+lo-10);
	else put_data('0' + lo);
}
*/


//Eric_20170308 : Delete
//    void SysUartDebugMessage(unsigned char *string)
//    {
//    	while(*string != 0)
//    	{
//    //		put_data(*string);
//    		ScalerMcuUartWrite(*string);
//    		if(*string == '\n')
//    		{
//    			ScalerMcuUartWrite('\r');
//    			ScalerMcuUartWrite('\n');
//    
//    		}
//    		string++;
//    	}
//    }

 

//Eric_020170308 : Delete
//    void CUartTransferNumToScr(WORD ch, BYTE mode )
//    {
//        BYTE NUMBUFFER[4], i, time;
//    
//    
//        ES = 0;
//    
//        if (mode == 0)
//        {
//            TI = 0;
//            SBUF = ch; // transfer UART
//            while (!TI)
//            {
//                ;        // wait buffer completing.
//            }
//        }
//        else if (mode == 1)
//        {
//            //dec
//            NUMBUFFER[3] = ch / 1000;
//            NUMBUFFER[2] = (ch % 1000) / 100;
//            NUMBUFFER[1] = ((ch % 1000) % 100) / 10;
//            NUMBUFFER[0] = ((ch % 1000) % 100) % 10;
//    /*
//            NUMBUFFER[2] = ch / 100;
//            NUMBUFFER[1] = (ch % 100) / 10;
//            NUMBUFFER[0] = (ch % 100) % 10;
//    */
//            if (NUMBUFFER[3] != 0)
//            {
//                time = 4;
//            }
//            else if (NUMBUFFER[2] != 0)
//            {
//                time = 3;
//            }
//            else if (NUMBUFFER[1] != 0)
//            {
//                time = 2;
//            }
//            else
//            {
//                time = 1;
//            }
//    
//            for (i = 0; i < time; i++)
//            {
//                TI = 0;
//                SBUF = NUMBUFFER[time - i - 1] + '0'; // transfer UART
//                while (!TI)
//                {
//                    ;   // wait buffer completing.
//                }
//            }
//        }
//        else if (mode == 2)
//        {
//            //hex
//            NUMBUFFER[3] = (ch & 0x0F);
//            NUMBUFFER[2] = ((ch >> 4) & 0x0F);
//            NUMBUFFER[1] = ((ch >> 8) & 0x0F);
//            NUMBUFFER[0] = ((ch >> 12) & 0x0F);
//    
//            for (i = 0; i < 4; i++)
//            {
//                TI = 0;
//    
//                if (NUMBUFFER[i] > 9)
//                {
//                    SBUF = NUMBUFFER[i] - 10 + 'A';
//                }
//                else
//                {
//                    SBUF = NUMBUFFER[i] + '0';      // transfer UART
//                }
//                while (!TI)
//                {
//                    ;                    // wait buffer completing.
//                }
//            }
//        }
//    
//        ES = 1;
//    
//    }

#endif //#if(_DISTECK_UART_SUPPORT == _ON)




