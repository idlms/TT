//----------------------------------------------------------------------------------------------------
// ID Code      : UserExternalDeviceIIC.h No.0000	
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserExternalDeviceIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
extern bit UserExternalDeviceIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize);

