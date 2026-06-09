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
// ID Code      : UserCommonFwUpdate.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_FW_UPDATE__

#include "UserCommonInclude.h"

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
// idata
StructFwUpdateUserCommonInfo    g_stFwUpdateUserCommonInfo =
{
    _FALSE,
    _FALSE,
    0xFF,
    0xFF,
    0x00,
    0x00,
    32,
    0xFFFFFF,
    0xFFFFFF,
    0xFFFFFF,
    0,
    0,
    0,
    {0xFF, 0xFF, 0xFF,   0xFFFF, 0, 0xFFFF, 0xFF, 0},
};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonFwUpdateHandler(void);
bit UserCommonFwUpdateWriteDoneFlag(void);
BYTE UserCommonFwUpdateCalculateCrc(WORD usLen, BYTE *pucData, BYTE ucCrc);
void UserCommonFwUpdateGetFwVersion(BYTE *pucVersionReply);
bit UserCommonFwUpdateGetFwStartAddressAndFlagAddress(DWORD *pulFwStartAddress, StructFwUpdateUserDataInfo *pstUserDataInfo);
void UserCommonFwUpdateIntProc_EXINT1(void);
BYTE UserCommonFwUpdateGetStatus_EXINT1(void);
#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)
bit UserCommonFwUpdateRTKRsa2048SignatureVerify(void);
bit UserCommonFwUpdateRTKRsa2048LoadKeyAndSignature(StructSignKeyInfoType *pstHdcp2SignKeyInfoType);
bit UserCommonFwUpdateRTKRsa2048Calculate(BYTE *pucResult);
bit UserCommonFwUpdateCompareHashResult(BYTE *pucCurHash, BYTE *pucOrgHash);
bit UserCommonFwUpdateHwHashCalculateBasedSHA256(BYTE *pucResult);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :  Fw Update Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateHandler(void)
{
#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)
    if(UserCommonFwUpdateBackgroundHandler() == _TRUE)
    {
        return;
    }
#endif

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    if(UserCommonFwUpdateForegroundHandler() == _TRUE)
    {
        return;
    }
#endif
}

//--------------------------------------------------
// Description  : Fw Update Write Done Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateWriteDoneFlag(void)
{
    WORD usFlagDoneAddr = (WORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress;
    BYTE pucReadFlag[5];
    BYTE pucISPDoneFlagRef[5] = {_TAG_UPDATE_FW_PASS, _TAG_VERIFY_FW_NONE, _TAG_SWITCH_CODE_COMPLETE, _TAG_CAN_BE_EXECUTED, _TAG_COPY_FW_NONE};
    // Write Done Flag
    UserCommonFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataBank, usFlagDoneAddr, 5, pucISPDoneFlagRef);
    memset(pucReadFlag, 0, sizeof(pucReadFlag));
    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataBank, usFlagDoneAddr, 5, pucReadFlag);
    if(memcmp(pucISPDoneFlagRef, pucReadFlag, sizeof(pucISPDoneFlagRef)) != 0)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Fw Update Calculate Crc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonFwUpdateCalculateCrc(WORD usLen, BYTE *pucData, BYTE ucCrc)
{
    DWORD  ulIndex = 0;
    BYTE ucCrcTmp = ucCrc;
    while(usLen--)
    {
        ucCrcTmp ^= *pucData++;
        for(ulIndex = 8; ulIndex > 0; --ulIndex)
        {
            if(ucCrcTmp & 0x80)
            {
                ucCrcTmp = (ucCrcTmp << 1) ^ 0x07;
            }
            else
            {
                ucCrcTmp = (ucCrcTmp << 1);
            }
        }
    }

    return ucCrcTmp;
}

//---------------------------------------------------------
// Description  : Fw Update Get Active Fw Version
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateGetFwVersion(BYTE *pucVersionReply)
{
    BYTE pucTmpData[6] = {0};
#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
    ScalerFwInfoGetCurrentVersion(pucTmpData);
#endif
    pucVersionReply[0] = _FW_UPDATE_RESULT_IDLE_AND_SUCCESS;
    pucVersionReply[1] = pucTmpData[0];
    pucVersionReply[2] = pucTmpData[1];
}

//---------------------------------------------------------------------------------
// Description  : Background Fw Update Get Program Fw Start Address and Flag Address
// Input Value  : pulFwStartAddress, pstUserDataInfo
// Output Value : None
//---------------------------------------------------------------------------------
bit UserCommonFwUpdateGetFwStartAddressAndFlagAddress(DWORD *pulFwStartAddress, StructFwUpdateUserDataInfo *pstUserDataInfo)
{
    BYTE ucCurBank = GET_CURRENT_BANK_NUMBER();
    // if run User 1
    if((ucCurBank >= _DUAL_BANK_USER_I_FW_BANK_START) && (ucCurBank <= _DUAL_BANK_USER_I_FW_BANK_END))
    {
        *pulFwStartAddress = ((DWORD)_DUAL_BANK_USER_II_FW_BANK_START << 16) | 0x00;
        pstUserDataInfo->ucUserDataBank = _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR;
        pstUserDataInfo->ucUserDataSectorStart = _DUAL_BANK_USER_II_DATA_SECTOR_START;
        pstUserDataInfo->ucUserDataSectorEnd = _DUAL_BANK_USER_II_DATA_SECTOR_END;
        pstUserDataInfo->usFlagStartAddress = _DUAL_BANK_USER_II_FLAG_START_ADDR;
        pstUserDataInfo->usKeyStartAddress = _DUAL_BANK_USER_II_KEY_START_ADDR;
        pstUserDataInfo->usKeyLen = _DUAL_BANK_USER_KEY_LENGTH;
        pstUserDataInfo->usSignatureStartAddress = _DUAL_BANK_USER_II_SIGNATURE_START_ADDR;
        pstUserDataInfo->usSignatureLen = _DUAL_BANK_USER_SIGNATURE_LENGTH;
        return _TRUE;
    }
    else if((ucCurBank >= _DUAL_BANK_USER_II_FW_BANK_START) && (ucCurBank <= _DUAL_BANK_USER_II_FW_BANK_END))
    {
        *pulFwStartAddress = ((DWORD)_DUAL_BANK_USER_I_FW_BANK_START << 16) | 0x00;
        pstUserDataInfo->ucUserDataBank = _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR;
        pstUserDataInfo->ucUserDataSectorStart = _DUAL_BANK_USER_I_DATA_SECTOR_START;
        pstUserDataInfo->ucUserDataSectorEnd = _DUAL_BANK_USER_I_DATA_SECTOR_END;
        pstUserDataInfo->usFlagStartAddress = _DUAL_BANK_USER_I_FLAG_START_ADDR;
        pstUserDataInfo->usKeyStartAddress = _DUAL_BANK_USER_I_KEY_START_ADDR;
        pstUserDataInfo->usKeyLen = _DUAL_BANK_USER_KEY_LENGTH;
        pstUserDataInfo->usSignatureStartAddress = _DUAL_BANK_USER_I_SIGNATURE_START_ADDR;
        pstUserDataInfo->usSignatureLen = _DUAL_BANK_USER_SIGNATURE_LENGTH;
        return _TRUE;
    }
    else
    {
        *pulFwStartAddress = 0xFFFFFF;
        pstUserDataInfo->ucUserDataBank = 0xFF;
        pstUserDataInfo->ucUserDataSectorStart = 0xFF;
        pstUserDataInfo->ucUserDataSectorEnd = 0xFF;
        pstUserDataInfo->usFlagStartAddress = 0xFFFF;
        pstUserDataInfo->usKeyStartAddress = 0xFFFF;
        pstUserDataInfo->usKeyLen = 0;
        pstUserDataInfo->usSignatureStartAddress = 0xFFFF;
        pstUserDataInfo->usSignatureLen = 0;
    }
    return _FALSE;
}


//--------------------------------------------------
// Description  : Get DDC-CI Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateIntProc_EXINT1(void) using 2
{
    ScalerFwUpdateIntProc_EXINT1();
}

//--------------------------------------------------
// Description  : Get DDC-CI Status in Interrupt Process
// Input Value  : None
// Output Value : _TURE or _False
//--------------------------------------------------
BYTE UserCommonFwUpdateGetStatus_EXINT1(void) using 2
{
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
    if((ScalerFwUpdateGetState_EXINT1() == _TRUE) && (GET_DDCCI1_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
#else
    if((ScalerFwUpdateGetState_EXINT1() == _TRUE) && (GET_DDCCI_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
#endif
    {
        return _TRUE;
    }
    return _FALSE;
}

#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)
//--------------------------------------------------
// Description  : Fw Update RTK RSA2048 Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateRTKRsa2048SignatureVerify(void)
{
    BYTE pucCurHash[_FW_UPDATE_SHA256_RESULT_SIZE] = {0};
    BYTE pucOrgHash[_FW_UPDATE_RSA_RESULT_SIZE] = {0};

    ScalerFwUpdateReleaseRsaforSign();

    // step 1: calculate fw bin data hash based on SHA-256
    if(UserCommonFwUpdateHwHashCalculateBasedSHA256(pucCurHash) == _FALSE)
    {
        return _FALSE;
    }

    // step 2: load signature and key, then calculate original hash based RSA-1024/2048/3072
    if(UserCommonFwUpdateRTKRsa2048Calculate(pucOrgHash) == _FALSE)
    {
        return _FALSE;
    }
    if(UserCommonFwUpdateCompareHashResult(pucCurHash, pucOrgHash) == _FALSE)
    {
        return _FALSE;
    }
    return _TRUE;
}
//--------------------------------------------------
// Description  : Fw Update RTK RSA2048 Load Key And Signautre
// Input Value  : pstHdcp2SignKeyInfoType
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateRTKRsa2048LoadKeyAndSignature(StructSignKeyInfoType *pstHdcp2SignKeyInfoType)
{
    BYTE pucTemp[_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8] = {0};
    BYTE ucBank = (BYTE)((g_stFwUpdateUserCommonInfo.ulFwStartAddress >> 16) + _DUAL_BANK_USER_FW_CODE_SIZE - 1);

    memset(pucTemp, 0, sizeof(pucTemp));

    ScalerSyncHdcpEnableDownLoadKey(_ENABLE);
    // load Signature file
    UserCommonFlashRead(ucBank, (WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_SIGNATURE_OFFESET, _FW_UPDATE_RSA_SIGNATURE_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_SIGNATURE_SIZE, pucTemp, _SIGN_FILE);

    // load N key
    UserCommonFlashRead(ucBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_NKEY_OFFSET), _FW_UPDATE_RSA_KEY_NKEY_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_NKEY_SIZE, pucTemp, _SIGN_NKEY);

    // load RRMODN
    UserCommonFlashRead(ucBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_RRMODN_OFFSET), _FW_UPDATE_RSA_KEY_RRMODN_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_RRMODN_SIZE, pucTemp, _SIGN_RRMODN);

    // load NPINV
    UserCommonFlashRead(ucBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_NPINV_OFFSET), _FW_UPDATE_RSA_KEY_NPINV_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_NPINV_SIZE, pucTemp, _SIGN_NPINV);

    // load E key
    UserCommonFlashRead(ucBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_EXORKEY_OFFSET), _FW_UPDATE_RSA_KEY_EXORKEY_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_EXORKEY_SIZE, pucTemp, _SIGN_EKEY);

    return _TRUE;
}
//--------------------------------------------------
// Description  : Fw Update RTK RSA2048 Caculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateRTKRsa2048Calculate(BYTE *pucResult)
{
    StructSignKeyInfoType stHdcp2SignKeyInfoType;
    UserCommonFwUpdateRTKRsa2048LoadKeyAndSignature(&stHdcp2SignKeyInfoType);
    if(ScalerFwUpdateDeRsaCalculateforSign(&stHdcp2SignKeyInfoType, _FW_UPDATE_RTK_SIGATURE_RSA_TYPE, _FW_UPDATE_RSA_SIGNATURE_SIZE, _FW_UPDATE_RSA_KEY_RRMODN_SIZE, _FW_UPDATE_RSA_KEY_NKEY_SIZE, _FW_UPDATE_RSA_KEY_EXORKEY_SIZE, _FW_UPDATE_RSA_KEY_NPINV_SIZE) == _FALSE)
    {
        return _FALSE;
    }
    ScalerFwUpdateReadoutRsaforSign(pucResult, _FW_UPDATE_RSA_RESULT_SIZE);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Fw Update Compare Hash Result
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateCompareHashResult(BYTE *pucCurHash, BYTE *pucOrgHash)
{
    WORD usIndex = 0;

    for(usIndex = 0; usIndex <= (_FW_UPDATE_RSA_RESULT_SIZE - _FW_UPDATE_SHA256_RESULT_SIZE); usIndex++)
    {
        if(memcmp(pucCurHash, &pucOrgHash[usIndex], _FW_UPDATE_SHA256_RESULT_SIZE) == 0)
        {
            DebugMessageSystem("signature verify success", 0);
            return _TRUE;
        }
    }

    DebugMessageSystem("signature verify fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Fw Update Hw hash Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateHwHashCalculateBasedSHA256(BYTE *pucResult)
{
    DWORD ulIndex = 0;
    DWORD ulFwAddr = g_stFwUpdateUserCommonInfo.ulFwStartAddress;
    DWORD ulFwLength = (DWORD)_DUAL_BANK_USER_FW_CODE_SIZE << 16;
    DWORD ulCount = ulFwLength / _FW_UPDATE_SHA256_ARRAY_SIZE;
    BYTE pucArray[_FW_UPDATE_SHA256_ARRAY_SIZE] = {0};
    BYTE ucBank = (BYTE)((g_stFwUpdateUserCommonInfo.ulFwStartAddress >> 16) + _DUAL_BANK_USER_FW_CODE_SIZE - 1);
    WORD usAddr = 0;
    bit bReturn = _TRUE;
    DWORD ulRTKSignDataStartAddr = ((DWORD)ucBank << 16) + ((DWORD)_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS);
    DWORD ulRTKSignDataDataEndAddr = ((DWORD)ucBank << 16) + ((DWORD)_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS + _FLASH_PAGE_SIZE);

    DWORD ulUserDataStartAddr = ((DWORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataBank << 16) + ((DWORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorStart << 12);
    DWORD ulUserDataEndAddr = ((DWORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataBank << 16) + ((DWORD)(g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorEnd + 1) << 12);

    for(ulIndex = 0; ulIndex < ulCount; ++ulIndex)
    {
        ucBank = ((ulFwAddr >> 16) & 0xFF);
        usAddr = ulFwAddr & 0xFFFF;

        if(((ulFwAddr >= ulUserDataStartAddr) && (ulFwAddr < ulUserDataEndAddr)) || ((ulFwAddr >= ulRTKSignDataStartAddr) && (ulFwAddr < ulRTKSignDataDataEndAddr)))
        {
            memset(pucArray, 0xFFU, sizeof(pucArray));
        }
        else
        {
            memset(pucArray, 0xFFU, sizeof(pucArray));
            UserCommonFlashRead(ucBank, usAddr, _FW_UPDATE_SHA256_ARRAY_SIZE, pucArray);
        }
        if(ulIndex == 0)
        {
            bReturn = ScalerFwUpdateSha256CalculateforSign(pucArray, 0);
        }
        else
        {
            bReturn = ScalerFwUpdateSha256CalculateforSign(pucArray, 1);
        }

        if(!bReturn)
        {
            DebugMessageSystem("HASH error, fw addr:", ulFwAddr);
            return bReturn;
        }

        ulFwAddr += _FW_UPDATE_SHA256_ARRAY_SIZE;
    }

    // Hash last package

    memset(pucArray, 0, sizeof(pucArray));
    pucArray[0] = 0x80;
    pucArray[61] = (BYTE)(((8 * ulFwLength) >> 16) & 0xFF);
    pucArray[62] = (BYTE)(((8 * ulFwLength) >> 8) & 0xFF);
    pucArray[63] = (BYTE)((8 * ulFwLength) & 0xFF);

    bReturn = ScalerFwUpdateSha256CalculateforSign(pucArray, 1);
    if(!bReturn)
    {
        DebugMessageSystem("HASH error, last data", 0);
        return bReturn;
    }

    // read out hash result
    ScalerFwUpdateReadoutHashforSign(pucResult);

    return _TRUE;
}
#endif


#endif

