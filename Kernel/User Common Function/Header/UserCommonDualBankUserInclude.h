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
// ID Code      : UserCommonDualBankUserInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)

//------------------------------------------------------
// debug op code
//------------------------------------------------------
#define _SCALER_BOOT_ENABLE_ISP_CHANNEL_OP_CODE                     0x01
#define _SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE                     0x02
#define _SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE                  0x03
#define _SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE                 0x04
#define _SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE                 0x05
#define _SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE                 0x06
#define _SCALER_BOOT_SWITCH_CODE_OP_CODE                            0x07
#define _SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE               0x08
#define _SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE                     0x09
#define _SCALER_BOOT_GET_DUAL_BANK_BUNDLE_VERSION_OP_CODE           0x0A
#define _SCALER_BOOT_SET_DUAL_BANK_BUNDLE_VERSION_OP_CODE           0x0B

//------------------------------------------------------
// Flag Data in User FW
//------------------------------------------------------
#if(_DUAL_BANK_TYPE == _DUAL_BANK_DIGITAL_SIGNATURE_ONLY)
#define _DUALBANK_FILL_LENGTH                                       4 // 1 Secter 4K (Unit: K bytes)
#else
#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_ONE_SECTOR)
#define _DUALBANK_FILL_LENGTH                                       4 // 1 Secter 4K (Unit: K bytes)
#else
#define _DUALBANK_FILL_LENGTH                                       12 // 3 Secter 12K (Unit: K bytes)
#endif
#endif

//------------------------------------------------------
// Flag setting
//------------------------------------------------------
#define _USER_FLAG_ISP_TAG                                          0
#define _USER_FLAG_VERIFY_TAG                                       1
#define _USER_FLAG_SWITCH_TAG                                       2
#define _USER_FLAG_RUN_TAG                                          3
#define _USER_FLAG_COPY_TAG                                         4

//------------------------------------------------------
// ISP Tag
//------------------------------------------------------
#define _TAG_UPDATE_FW_PASS                                         0xAA
#define _TAG_UPDATE_FW_FAIL                                         0xFF


//------------------------------------------------------
// Verify Tag
//------------------------------------------------------
#define _TAG_VERIFY_FW_PASS                                         0xAA
#define _TAG_VERIFY_FW_FAIL                                         0x55
#define _TAG_VERIFY_FW_NONE                                         0xFF


//------------------------------------------------------
// Switch Tag
//------------------------------------------------------
#define _TAG_SWITCH_CODE_NONE                                       0xFF
#define _TAG_SWITCH_CODE_INCOMPLETE                                 0xAF
#define _TAG_SWITCH_CODE_COMPLETE                                   0xAA


//------------------------------------------------------
// Run Tag
//------------------------------------------------------
#define _TAG_CAN_BE_EXECUTED                                        0xFF
#define _TAG_CAN_NOT_BE_EXECUTED                                    0x55


//------------------------------------------------------
// Copy Tag
//------------------------------------------------------
#define _TAG_COPY_FW_PASS                                           0xAA
#define _TAG_COPY_FW_NONE                                           0xFF

//------------------------------------------------------
// Key address setting
// Public Key Content Offset Address from @0x_000(Nkey + RRmodN + Npinv + EKey)
//------------------------------------------------------
#define _DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE                        (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)
#define _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE                      (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)
#define _DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE                       4
#define _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_SIZE                     (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)

#define _DIGITAL_SIGNATURE_RSA_KEY_NKEY_OFFSET                      0
#define _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_OFFSET                    (_DIGITAL_SIGNATURE_RSA_KEY_NKEY_OFFSET + _DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE)
#define _DIGITAL_SIGNATURE_RSA_KEY_NPINV_OFFSET                     (_DIGITAL_SIGNATURE_RSA_KEY_RRMODN_OFFSET + _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE)
#define _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_OFFSET                   (_DIGITAL_SIGNATURE_RSA_KEY_NPINV_OFFSET + _DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE)

// 4 Byte MagicWord + 4 Byte Version + 4BYte Type + 4 Byte Key Len + 4 Byte Signature len
#define _DIGITAL_SIGNATURE_INFO_HEADER_SIZE                         20

//------------------------------------------------------
// User Flag length setting
//------------------------------------------------------
#define _DUAL_BANK_USER_KEY_LENGTH                                  (_DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE + _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE + _DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE + _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_SIZE)
#define _DUAL_BANK_USER_FLAG_LENGTH                                 5
#define _DUAL_BANK_USER_SIGNATURE_LENGTH                            (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)

//------------------------------------------------------
// User I/II setting
//------------------------------------------------------
#define _DUAL_BANK_USER_I_FW_BANK_START                             _DUAL_BANK_USER_FW_START_BANK
#define _DUAL_BANK_USER_I_FW_BANK_END                               (_DUAL_BANK_USER_I_FW_BANK_START + _DUAL_BANK_USER_FW_CODE_SIZE - 1)

#define _DUAL_BANK_USER_II_FW_BANK_START                            (_DUAL_BANK_USER_FW_START_BANK + _DUAL_BANK_USER_FW_CODE_SIZE)
#define _DUAL_BANK_USER_II_FW_BANK_END                              (_DUAL_BANK_USER_II_FW_BANK_START + _DUAL_BANK_USER_FW_CODE_SIZE - 1)


#if((_DUAL_BANK_SUPPORT == _ON) && (_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_USER))
#define _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR                       (_DUAL_BANK_USER_I_FW_BANK_START + _DUAL_BANK_USER_I_FLAG_LOCATE_BANK)
#define _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR                      (_DUAL_BANK_USER_II_FW_BANK_START + _DUAL_BANK_USER_II_FLAG_LOCATE_BANK)
#else
#define _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR                       _DUAL_BANK_USER_I_FLAG_LOCATE_BANK
#define _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR                      _DUAL_BANK_USER_II_FLAG_LOCATE_BANK
#endif

#if(_DUAL_BANK_TYPE == _DUAL_BANK_DIGITAL_SIGNATURE_ONLY)
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                         0x0F
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                        0x0F
#else
#if(_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR == _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR)
#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                         0x0A
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                        0x0D
#else
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                         0x0E
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                        0x0F
#endif
#else
#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                         0x0D
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                        0x0D
#else
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                         0x0F
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                        0x0F
#endif
#endif
#endif

#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_I_KEY_START_ADDR                            ((WORD)_DUAL_BANK_USER_I_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_I_FLAG_START_ADDR                           ((WORD)(_DUAL_BANK_USER_I_DATA_SECTOR_START + 1) << 12)
#define _DUAL_BANK_USER_I_SIGNATURE_START_ADDR                      (((WORD)_DUAL_BANK_USER_I_DATA_SECTOR_START + 2) << 12)
#define _DUAL_BANK_USER_I_DATA_SECTOR_END                           (_DUAL_BANK_USER_I_DATA_SECTOR_START + 2)
#else
#define _DUAL_BANK_USER_I_KEY_START_ADDR                            ((WORD)_DUAL_BANK_USER_I_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_I_FLAG_START_ADDR                           ((WORD)(_DUAL_BANK_USER_I_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH)
#define _DUAL_BANK_USER_I_SIGNATURE_START_ADDR                      ((WORD)(_DUAL_BANK_USER_I_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH + _DUAL_BANK_USER_FLAG_LENGTH)
#define _DUAL_BANK_USER_I_DATA_SECTOR_END                           _DUAL_BANK_USER_I_DATA_SECTOR_START
#endif

#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_II_KEY_START_ADDR                           ((WORD)_DUAL_BANK_USER_II_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_II_FLAG_START_ADDR                          ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START + 1) << 12)
#define _DUAL_BANK_USER_II_SIGNATURE_START_ADDR                     ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START + 2) << 12)
#define _DUAL_BANK_USER_II_DATA_SECTOR_END                          (_DUAL_BANK_USER_II_DATA_SECTOR_START + 2)
#else
#define _DUAL_BANK_USER_II_KEY_START_ADDR                           ((WORD)_DUAL_BANK_USER_II_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_II_FLAG_START_ADDR                          ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH)
#define _DUAL_BANK_USER_II_SIGNATURE_START_ADDR                     ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH + _DUAL_BANK_USER_FLAG_LENGTH)
#define _DUAL_BANK_USER_II_DATA_SECTOR_END                          _DUAL_BANK_USER_II_DATA_SECTOR_START
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonDualBankUserEnableISPChannel(void);
extern void UserCommonDualBankUserGetFwInfo(BYTE *pucArry);

#if(_DUAL_BANK_TYPE != _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)
#if(_DUAL_BANK_TYPE != _DUAL_BANK_DIGITAL_SIGNATURE_ONLY)
extern BYTE UserCommonDualBankUserGetIspStartBank(void);
extern DWORD UserCommonDualBankUserGetIspFlagAddr(void);
extern BYTE UserCommonDualBankUserGetVerifyCopyResult(void);
#endif

extern DWORD UserCommonDualBankUserGetIspKeyAddr(void);
extern DWORD UserCommonDualBankUserGetIspSignatureAddr(void);
extern DWORD UserCommonDualBankUserGetCurrentKeyAddr(void);
#endif

#endif
