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
// ID Code      : ColorTempDefaultNo.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// COLOR TEMP DEFAULT DATA
//****************************************************************************
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)

#define _CT9300_RED                                 (512)//(0x62 << 4)	//10000	//  ColorTemp(max1024) 
#define _CT9300_GREEN                               (543)//(0x68 << 4)
#define _CT9300_BLUE                                (461)//(0x6F << 4)

#define _CT7500_RED                                 (512)//(0x68 << 4)	//9300
#define _CT7500_GREEN                               (676)//(0x69 << 4)
#define _CT7500_BLUE                                (461)//(0x6B << 4)

#define _CT6500_RED                                 (686)//(0x71 << 4)	//7500
#define _CT6500_GREEN                               (655)//(0x70 << 4)
#define _CT6500_BLUE                                (307)//(0x68 << 4)

#define _CT5800_RED                                 (676)//(0x7A << 4)	//6500
#define _CT5800_GREEN                               (666)//(0x77 << 4)
#define _CT5800_BLUE                                (102)//(0x69 << 4)

#define _CTSRGB_RED                                 (512)//(0x80 << 4)
#define _CTSRGB_GREEN                               (512)//(0x80 << 4)
#define _CTSRGB_BLUE                                (512)//(0x80 << 4)

//#define _CTUSER_RED                                 (512)//(0x80 << 4)	
//#define _CTUSER_GREEN                               (512)//(0x80 << 4)
//#define _CTUSER_BLUE                                (512)//(0x80 << 4)

#else

#define _CT9300_RED                                 (196/2)//0x62				//  ColorTemp(max256) [0x062/0x080*256=196]
#define _CT9300_GREEN                               (208/2)//0x68
#define _CT9300_BLUE                                (222/2)//0x6F

#define _CT7500_RED                                 (208/2)//0x68
#define _CT7500_GREEN                               (210/2)//0x69
#define _CT7500_BLUE                                (214/2)//0x6B

#define _CT6500_RED                                 (226/2)//0x71
#define _CT6500_GREEN                               (224/2)//0x70
#define _CT6500_BLUE                                (208/2)//0x68

#define _CT5800_RED                                 (244/2)//0x7A
#define _CT5800_GREEN                               (238/2)//0x77
#define _CT5800_BLUE                                (210/2)//0x69

#define _CTSRGB_RED                                 (128/2)//0x80
#define _CTSRGB_GREEN                               (128/2)//0x80
#define _CTSRGB_BLUE                                (128/2)//0x80

//#define _CTUSER_RED                                 (128/2)//0x80	
//#define _CTUSER_GREEN                               (128/2)//0x80
//#define _CTUSER_BLUE                                (128/2)//0x80

#endif

//------------------------------------------------------------------ 
#define _CT_D56_RED                                 (0x81 << 4)
#define _CT_D56_GREEN                               (0x81 << 4)
#define _CT_D56_BLUE                                (0x79 << 4)

#define _CT_D65_RED                                 (0x80 << 4)
#define _CT_D65_GREEN                               (0x80 << 4)
#define _CT_D65_BLUE                                (0x80 << 4)

#define _CT_D93_RED                                 (0x79 << 4)
#define _CT_D93_GREEN                               (0x80 << 4)
#define _CT_D93_BLUE                                (0x81 << 4)

#define _CTUSER_RED                                 (0x80 << 4)
#define _CTUSER_GREEN                               (0x80 << 4)
#define _CTUSER_BLUE                                (0x80 << 4)
//------------------------------------------------------------------

