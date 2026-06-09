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
//-------------------------------------------------------------------------------------//
// ID Code      : RL6449_Series_ColorConvertHueSat.c
// Update Note  :
//-------------------------------------------------------------------------------------//
#include "RL6449_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
// 1->1024
SWORD code tYUV2RGB_CONVERT[][3] =
{
    { 4096,       0,    5744,  },
    { 4096,   -1408,   -2924,  },
    { 4096,    7260,       0,  }
};


// 1->1024
SWORD code tRGB2YUV_CONVERT[][3] =
{
    {  1224,    2405,    467,  },
    {  -691,   -1357,   2048,  },
    {  2048,   -1715,   -333,  }
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
// use color convert
void ScalerColorConvertMatrixMultiply(SWORD(*ppshArrayA)[3], SWORD(*ppshArrayB)[3], SDWORD(*pplArrayC)[3]);
void ScalerColorConvertSetGlobalHueSat(SWORD shDeltaHue, WORD usDeltaSat);
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Do matrix multiply(3x3)  C = A*B
// Input Value  : shArrayA, shArrayB
// Output Value : shArrayC (SDWORD)
//--------------------------------------------------
void ScalerColorConvertMatrixMultiply(SWORD(*ppshArrayA)[3], SWORD(*ppshArrayB)[3], SDWORD(*pplArrayC)[3])
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    SDWORD plTempBuff[3] = {0};
    for(ucJ = 0; ucJ < 3; ucJ++)
    {
        for(ucI = 0; ucI < 3; ucI++)
        {
            plTempBuff[ucI] = (((SDWORD)ppshArrayA[ucI][0] * ppshArrayB[0][ucJ] + 2) >> 4) +
                              (((SDWORD)ppshArrayA[ucI][1] * ppshArrayB[1][ucJ] + 2) >> 4) +
                              (((SDWORD)ppshArrayA[ucI][2] * ppshArrayB[2][ucJ] + 2) >> 4);
        }

        for(ucI = 0; ucI < 3; ucI++)
        {
            pplArrayC[ucI][ucJ] = (SDWORD)((plTempBuff[ucI] + 256) >> 9);
        }
    }
}

//--------------------------------------------------
// Description  : use color convertion to set global Hue&Sat
// Input Value  : DeltaHue(-180~180), DeltaSat(0-330)
// Default Value: Delta Hue = 0, Delta Sat = 100;
// Notice !! Rightnow the Hue/Sat value is saved to NVRAM as BYTE, if you
// want to expand the Range, please edit relative functions and parameters.
// Output Value : pColorMatrix(3x3, set to Color Convert Matrix)
//--------------------------------------------------
void ScalerColorConvertSetGlobalHueSat(SWORD shDeltaHue, WORD usDeltaSat)
{
    SWORD ppshTempBuff[3][3] = {{0}};
    SDWORD pplTempBuff2[3][3] = {{0}};
    BYTE ucI = 0;
    BYTE ucJ = 0;
    memset(ppshTempBuff, 0, sizeof(ppshTempBuff));
    memset(pplTempBuff2, 0, sizeof(pplTempBuff2));

    if((shDeltaHue == 0) && (usDeltaSat == 100))
    {
        ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT5 | _BIT4), 0x00);
        ScalerGlobalDDomainDBApply(_DB_APPLY_NO_POLLING);
        return;
    }

    if(_TRUE)
    {
        SWORD ppshMATRIX[3][3];
        memset(ppshMATRIX, 0, sizeof(ppshMATRIX));

        ppshMATRIX[0][0] = 4096;
        ppshMATRIX[0][1] = 0;
        ppshMATRIX[0][2] = 0;
        ppshMATRIX[1][0] = 0;
        ppshMATRIX[1][1] = (DWORD)usDeltaSat * 4096 / 100;
        ppshMATRIX[1][2] = 0;
        ppshMATRIX[2][0] = 0;
        ppshMATRIX[2][1] = 0;
        ppshMATRIX[2][2] = ppshMATRIX[1][1];

        ScalerColorSRGBMatrixMultiply(ppshMATRIX, tRGB2YUV_CONVERT, ppshTempBuff);

        ppshMATRIX[0][0] = 4096;
        ppshMATRIX[0][1] = 0;
        ppshMATRIX[0][2] = 0;
        ppshMATRIX[1][0] = 0;
        ppshMATRIX[1][1] = ScalerColorSRGBCosine(shDeltaHue);
        ppshMATRIX[1][2] = ((SWORD)(-1) * (SWORD)ScalerColorSRGBSine(shDeltaHue));
        ppshMATRIX[2][0] = 0;
        ppshMATRIX[2][1] = ((SWORD)(-1) * (SWORD)ppshMATRIX[1][2]);
        ppshMATRIX[2][2] = ppshMATRIX[1][1];

        ScalerColorSRGBMatrixMultiply(ppshMATRIX, ppshTempBuff, ppshTempBuff);
        ScalerColorSRGBMatrixMultiply(tYUV2RGB_CONVERT, ppshTempBuff, ppshTempBuff);

        for (ucI = 0; ucI < 3; ucI++)
        {
            for (ucJ = 0; ucJ < 3; ucJ++)
            {
                ppshTempBuff[ucI][ucJ] = ppshTempBuff[ucI][ucJ] << 1;
            }
        }
        ScalerRead(P14_A2_SR_YCC2RGB_COEF_K11_MSB, 10, pData, _AUTOINC);

        ppshMATRIX[0][0] = ((pData[0] & 0x0F) << 11) | (pData[1] << 3) | ((pData[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        ppshMATRIX[0][1] = 0;
        ppshMATRIX[0][2] = ((pData[2] & 0x0F) << 11) | (pData[3] << 3) | ((pData[2] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        ppshMATRIX[1][0] = ppshMATRIX[0][0];
        ppshMATRIX[1][1] = ((SWORD)(-1) * (SWORD)(((pData[4] & 0x0F) << 11) | (pData[5] << 3) | ((pData[4] & (_BIT7 | _BIT6 | _BIT5)) >> 5)));
        ppshMATRIX[1][2] = ((SWORD)(-1) * (SWORD)(((pData[6] & 0x0F) << 11) | (pData[7] << 3) | ((pData[6] & (_BIT7 | _BIT6 | _BIT5)) >> 5)));
        ppshMATRIX[2][0] = ppshMATRIX[0][0];
        ppshMATRIX[2][1] = ((pData[8] & 0x0F) << 11) | (pData[9] << 3) | ((pData[8] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        ppshMATRIX[2][2] = 0;

        ScalerColorConvertMatrixMultiply(ppshTempBuff, ppshMATRIX, pplTempBuff2);
    }

    if(_TRUE)
    {
        BYTE pucColorMatrix[27];
        memset(pucColorMatrix, 0, sizeof(pucColorMatrix));
        for (ucI = 0; ucI < 3; ucI++)
        {
            for (ucJ = 0; ucJ < 3; ucJ++)
            {
                pucColorMatrix[3 * (3 * ucI + ucJ)] = (((pplTempBuff2[ucJ][ucI] < 0) ? 1 : 0) << 3) | ((pplTempBuff2[ucJ][ucI] >> 13) & (_BIT2 | _BIT1 | _BIT0)); // [3] sign
                pucColorMatrix[3 * (3 * ucI + ucJ) + 1] = ((pplTempBuff2[ucJ][ucI] >> 5) & 0xFF); // bit5~12
                pucColorMatrix[3 * (3 * ucI + ucJ) + 2] = ((pplTempBuff2[ucJ][ucI] & 0x1F) << 3); // bit0~4
            }
        }
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerWrite(P14_40_SR_BT2020_COEF_H11_HSB, 27, pucColorMatrix, _AUTOINC);
        ScalerSetByte(P14_6D_SR_BT2020_COEF_CB_THD_MSB, 0xFF);
        ScalerSetByte(P14_6E_SR_BT2020_COEF_CB_THD_LSB, 0xFF);
        ScalerSetByte(P14_6F_SR_BT2020_COEF_CR_THD_MSB, 0xFF);
        ScalerSetByte(P14_70_SR_BT2020_COEF_CR_THD_LSB, 0xFF);
        ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT5 | _BIT4), _BIT5);
        ScalerGlobalDDomainDBApply(_DB_APPLY_NO_POLLING);
    }
}

