//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#define _A0_EDID_TYPE_SEL                               _EDID_VGA_1920_1200_60HZ


//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || ((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_A0[] =
{
#if(_A0_EDID_TYPE_SEL == _EDID_VGA_1920_1200_60HZ)
//#include "./EDID/EdidVga/EDID_VGA_1920x1200@60.h"	// VGA EDID Change Point => Kernel\User Common Function\Header\EDID
#include "./EDID/EdidVga/EDID_VGA_1920x1080@60_VEGA.h"	// VGA 1080p EDID
#endif
};

#endif
