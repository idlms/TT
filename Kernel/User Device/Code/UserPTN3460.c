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

//----------------------------------------------------------------------------------------------------
// ID Code      : UserPTN3460.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserDeviceInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
/*
WORD code tLDHDRToneMappingLv540[256] =
{
#include _LD_HDR_TONE_MAPPING_LV540
};
*/

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//void UserCommonLocalDimmingHandler(void);
bit UserExternalDeviceIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
//bit UserExternalDeviceIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
/*
void UserCommonLocalDimmingHandler(void)
{
    if(UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE)
    {
        if(UserInterfaceGetLocaldimmingActionMode() == _LD_ACTION_MODE_DIMMING)
        {
            UserCommonLocalDimmingAdjust();
            SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_DIMMING);
        }
        else
        {
            if(GET_LD_ACTION_MODE_STATUS() == _LD_ACTION_MODE_DIMMING)
            {
                UserCommonLocalDimmingStepToGDHDR();
                SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_NORNAL);
            }
        }
    }
}
*/

//--------------------------------------------------
// Description  : Read data to the External External Device by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserExternalDeviceIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    ucSWIICStatus = ucSWIICStatus;

    while(ulLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0xFF00) >> 7);
        }
        else if(ucSubAddrLength == 2)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0x00FF0000) >> 15);
        }

        // Receive 24 bytes each time
        ucDataCnt = _EEPROM_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(ulLength > ucDataCnt)
        {
            ulLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = ulLength;
            ulLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICRead(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucReadArray) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICRead(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucReadArray, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        ulSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}
/*
//--------------------------------------------------
// Description  : Write data to the System External Device by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
//                enumWriteSize --> 8 or 16 or 32
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit UserExternalDeviceIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE ucTimeOutCnt = _EEPROM_TIMEOUT_LIMIT;
    BYTE pucTempData[32];

    ucSWIICStatus = ucSWIICStatus;

    if(ulLength <= 0)
    {
        return _FAIL;
    }

    while(ulLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0xFF00) >> 7);
        }
        else if(ucSubAddrLength == 2)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((ulSubAddr & 0x00FF0000) >> 15);
        }

        // Transmit 8, 16 or 32 bytes each time
        ucDataCnt = enumWriteSize;

        // Check if more than 8, 16 or 32 bytes are needed to be transmitted
        if(enumWriteSize == _WRITE_SIZE_32)
        {
            if(((ulSubAddr & 0x001F) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x001F);
            }
        }
        else if(enumWriteSize == _WRITE_SIZE_16)
        {
            if(((ulSubAddr & 0x000F) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x000F);
            }
        }
        else if(enumWriteSize == _WRITE_SIZE_8)
        {
            if(((ulSubAddr & 0x0007) + ulLength - 1) >= enumWriteSize)
            {
                ucDataCnt = enumWriteSize - (ulSubAddr & 0x0007);
            }
        }

        if(ulLength > ucDataCnt)
        {
            ulLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = ulLength;
            ulLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Disable EEPROM Write Protect
        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

        // Execute Hardware IIC Write Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICWrite(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucTempData) == _FAIL)
            {
                // Enable EEPROM Write Protect
                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICWrite(ucSlaveAddress, ucSubAddrLength, (WORD)ulSubAddr, ucDataCnt, pucTempData, ucHwIICPinNum) == _FAIL)
            {
                // Enable EEPROM Write Protect
                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        // Increment Sub-Addr for next Write
        ulSubAddr += ucDataCnt;

        // Need to delay until internal write cycle is finished
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            while(ScalerMcuIICWritePolling(ucSlaveAddress) == _FAIL)
            {
                ucTimeOutCnt--;

                ScalerDelay5us();

                if(ucTimeOutCnt == 0x00)
                {
                    // Enable EEPROM Write Protect
                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                    return _FAIL;
                }
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)

        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            while(ScalerMcuHwIICWritePolling(ucSlaveAddress, ucSubAddrLength, ucHwIICPinNum) == _FAIL)
            {
                ucTimeOutCnt--;

                ScalerDelay5us();

                if(ucTimeOutCnt == 0x00)
                {
                    // Enable EEPROM Write Protect
                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                    return _FAIL;
                }
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

        }

        ucTimeOutCnt = _EEPROM_TIMEOUT_LIMIT;

        // Enable EEPROM Write Protect
        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
    }

    return _SUCCESS;
}
#pragma restore
*/


