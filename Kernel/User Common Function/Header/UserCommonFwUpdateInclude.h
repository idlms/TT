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
// ID Code      : UserCommonFwUpdateInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _FW_UPDATE_SLAVE_ADDRESS                    0x3A
#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)
#define _FW_UPDATE_SHA256_RESULT_SIZE               32
#define _FW_UPDATE_SHA256_ARRAY_SIZE                64
#endif

#define _FW_UPDATE_SUBADDRESS_INDEX                 0
#define _FW_UPDATE_DATA_START_INDEX                 1
#define _FW_UPDATE_OPCODE_INDEX                     1

#define GET_FW_UPDATE_VERIFY_ID_PASS()              (g_stFwUpdateUserCommonInfo.b1VerifyIDPass)
#define SET_FW_UPDATE_VERIFY_ID_PASS(x)             (g_stFwUpdateUserCommonInfo.b1VerifyIDPass = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE ucUserDataBank;
    BYTE ucUserDataSectorStart;
    BYTE ucUserDataSectorEnd;
    WORD usKeyStartAddress;
    WORD usKeyLen;
    WORD usFlagStartAddress;
    WORD usSignatureStartAddress;
    WORD usSignatureLen;
} StructFwUpdateUserDataInfo;

typedef struct
{
    BYTE b1IspStartFlag : 1;
    BYTE b1VerifyIDPass : 1;
    BYTE ucLastBank;
    BYTE ucLastSector;
    BYTE ucFwCrc;
    BYTE ucCalCrc;
    WORD usIspPageCount;
    DWORD ulFwStartAddress;
    DWORD ulFwEndAddress;
    DWORD ulFwCurrentAddress;
    DWORD ulReceivedKeyAndSigLen;
    WORD usIspKeyLen;
    WORD usIspSigLen;
    StructFwUpdateUserDataInfo stUserDataInfo;
} StructFwUpdateUserCommonInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructFwUpdateUserCommonInfo    g_stFwUpdateUserCommonInfo;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonFwUpdateHandler(void);
extern bit UserCommonFwUpdateWriteDoneFlag(void);
extern BYTE UserCommonFwUpdateCalculateCrc(WORD usLen, BYTE *pucData, BYTE ucCrc);
extern void UserCommonFwUpdateGetFwVersion(BYTE *pucVersionReply);
extern bit UserCommonFwUpdateGetFwStartAddressAndFlagAddress(DWORD *pulFwStartAddress, StructFwUpdateUserDataInfo *pstUserDataInfo);

#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)
extern bit UserCommonFwUpdatePasswordVerify(BYTE ucBank, WORD usAddr);
#endif

#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)
extern bit UserCommonFwUpdateRTKRsa2048SignatureVerify(void);
extern bit UserCommonFwUpdateRTKRsa2048Calculate(BYTE *pucResult);
extern bit UserCommonFwUpdateHwHashCalculateBasedSHA256(BYTE *pucResult);
extern bit UserCommonFwUpdateCompareHashResult(BYTE *pucCurHash, BYTE *pucOrgHash);
extern bit UserCommonFwUpdateRTKRsa2048LoadKeyAndSignature(StructSignKeyInfoType *pstHdcp2SignKeyInfoType);
#endif

#endif

