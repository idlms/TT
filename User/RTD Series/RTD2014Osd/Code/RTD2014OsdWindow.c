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
// ID Code      : RTD2014OsdWindow.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDWINDOW__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdWindowDrawingByFontOrg(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);

void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
void OsdWindowSliderDisable(void);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor)
{
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    WORD xdata usTemp = 0;
    WORD xdata usTemp1 = 0;
    WORD xdata usTemp2 = 0;
    usTemp  = usXEnd - usXStart;
    usTemp1 = usYEnd - usYStart;
    usTemp2 = usXStart;

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        usXEnd = (g_ucOsdWidth * 18 - usYStart);
        usXStart = usXEnd - usTemp1;
        usYStart = usTemp2;
        usYEnd = usYStart + usTemp;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        usXStart = usYStart;
        usYStart = (g_ucOsdHeight * 12) - usXEnd;
        usXEnd = usXStart + usTemp1;
        usYEnd = usYStart + usTemp;
    }
    else
    {
    }

#elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    WORD xdata usTemp = 0;
    WORD xdata usTemp1 = 0;
    WORD xdata usTemp2 = 0;
    usTemp  = usXEnd - usXStart;
    usTemp1 = usYEnd - usYStart;
    usTemp2 = usXStart;

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        usXEnd = (g_ucOsdHeight * 18 - usYStart);
        usXStart = usXEnd - usTemp1;
        usYStart = usTemp2;
        usYEnd = usYStart + usTemp;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        usXStart = usYStart;
        usYStart = (g_ucOsdWidth * 12) - usXEnd;
        usXEnd = usXStart + usTemp1;
        usYEnd = usYStart + usTemp;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        usXStart = (g_ucOsdWidth * 12) - usTemp - usXStart;
        usXEnd = usXStart + usTemp;
        usYStart = (g_ucOsdHeight * 18) - usTemp1 - usYStart;
        usYEnd = usYStart + usTemp1;
    }
    else
    {
    }

#else // #if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)


#endif

    SET_OSD_WINDOW_NUMBER(ucWindow);
    SET_OSD_WINDOW_COLOR(ucColor);

    SET_OSD_WINDOW_BLEND_ENABLE(_ENABLE);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
	
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = ((ucRow) * 18);
    }
    usVend = usVstart + (18 * (ucHeight - 2 ));

    OsdWindowDrawing(ucWindow, usHstart, usVstart, usHend, usVend, ucColor);
	

	// OsdWindowDrawing(ucWindow, XSTART(ucCol*12), YSTART(ucRow*18+9), XEND((ucCol+ucWidth)*12), YEND((ucRow+ucHeight)*18-9), ucColor);	
	// ScalerOsdRoundedWindowOnOff(ucWindow, _ON,_ON,_ON,_ON,_ON);

	// if((ucWindow == _MENU_SECTION_0_TITLE_WINDOW)||(ucWindow == _MENU_SECTION_1_TITLE_WINDOW))
	// {
	// 	ScalerOsdRoundedWindowOnOff(ucWindow, _ON,_ON,_OFF,_ON,_OFF);
	// }
	// else
	// {
	// 	ScalerOsdRoundedWindowOnOff(ucWindow, _ON,_ON,_ON,_ON,_ON);
	// }

	// ScalerOsdRoundedWindowSize(ucWindow,_OSD_ROUNDED_WIN_SIZE_16X16);
	
	// ScalerOsdRoundedWindowPattern16x16(0,10);
	// ScalerOsdRoundedWindowPattern16x16(1,12);
	// ScalerOsdRoundedWindowPattern16x16(2,13);
	// ScalerOsdRoundedWindowPattern16x16(3,14);
	// ScalerOsdRoundedWindowPattern16x16(4,14);
	// ScalerOsdRoundedWindowPattern16x16(5,15);
	// ScalerOsdRoundedWindowPattern16x16(6,15);
	// ScalerOsdRoundedWindowPattern16x16(7,15);
	// ScalerOsdRoundedWindowPattern16x16(8,15);
	// ScalerOsdRoundedWindowPattern16x16(9,15);
	// ScalerOsdRoundedWindowPattern16x16(10,15);
	// ScalerOsdRoundedWindowPattern16x16(11,15);
	// ScalerOsdRoundedWindowPattern16x16(12,15);
	// ScalerOsdRoundedWindowPattern16x16(13,15);
	// ScalerOsdRoundedWindowPattern16x16(14,15);
	// ScalerOsdRoundedWindowPattern16x16(15,15);

}
void OsdWindowDrawingByFontOrg(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
    }
    usVend = usVstart + (18 * ucHeight);

    OsdWindowDrawing(ucWindow, usHstart, usVstart, usHend, usVend, ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
    }
    usVend = usVstart + (18 * ucHeight);

    OsdWindowDrawing(ucWindow, usHstart, usVstart, usHend, usVend, ucColor);

    ScalerOsdWindowHighlightFunction(_ENABLE, ucWindow, ucForegroundColor, ucBackgroundColor, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;
    WORD usSliderPixel = 0;
    BYTE ucSliderBarWindow = 0;
    BYTE ucSliderBoderWindow = 0;
    BYTE ucSliderBackgroundWindow = 0;
    BYTE ucSliderColor = 0;
    BYTE ucSliderBackgroundColor = 0;
    BYTE ucSliderBoderColor = 0;

    usSliderPixel = (WORD)(_SLIDER_LENGHT * ucPercentValue) / 100;

    usHstart = ((WORD)ucCol * 12) + _SLIDER_OFFSET;
    usHend = usHstart + _SLIDER_LENGHT;

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
        usVend = usVstart + _SLIDER_HIGH;
    }
    else
    {
        usVstart = (ucRow * 18);
        usVend = usVstart + _SLIDER_HIGH;
    }

    if(ucSliderNumber == _SLIDER_0)
    {
        ucSliderBarWindow = _SLIDER_0_BAR_WINDOW;
        ucSliderBoderWindow = _SLIDER_0_BORDER_WINDOW;
        ucSliderBackgroundWindow = _SLIDER_0_BG_WINDOW;
    }
    else
    {
        ucSliderBarWindow = _SLIDER_1_BAR_WINDOW;
        ucSliderBoderWindow = _SLIDER_1_BORDER_WINDOW;
        ucSliderBackgroundWindow = _SLIDER_1_BG_WINDOW;
    }

    if(bSelectState == _TRUE)
    {
        ucSliderColor = _SLIDER_SELECT_COLOR;
        ucSliderBackgroundColor = _SLIDER_SELECT_BG_COLOR;
        ucSliderBoderColor = _SLIDER_SELECT_BORDER_COLOR;
    }
    else
    {
        ucSliderColor = _SLIDER_UNSELECT_COLOR;
        ucSliderBackgroundColor = _SLIDER_UNSELECT_BG_COLOR;
        ucSliderBoderColor = _SLIDER_UNSELECT_BORDER_COLOR;
    }

    SET_OSD_WINDOW_BUTTON_ENABLE(_DISABLE);
    // Slider Boder Window
    // Slider BG Color
    OsdWindowDrawing(ucSliderBoderWindow, usHstart - _SLIDER_BORDER_PIXEL, usVstart - _SLIDER_BORDER_PIXEL, usHend + _SLIDER_BORDER_PIXEL, usVend + _SLIDER_BORDER_PIXEL, ucSliderBoderColor);

    // Slider BG Window
    OsdWindowDrawing(ucSliderBackgroundWindow, usHstart, usVstart, usHend, usVend, ucSliderBackgroundColor);

    if(usSliderPixel == 0)// Slider Window
    {
        ScalerOsdWindowDisable(ucSliderBarWindow);
    }
    else
    {
        OsdWindowDrawing(ucSliderBarWindow, usHstart, usVstart, usHstart + usSliderPixel, usVend, ucSliderColor);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowSliderDisable(void)
{
    ScalerOsdWindowDisable(_SLIDER_0_BAR_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_0_BORDER_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_0_BG_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_1_BAR_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_1_BORDER_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_1_BG_WINDOW);
}
#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)

