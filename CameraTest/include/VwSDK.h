 
//#pragma once

#ifndef VWSDK_H
#define VWSDK_H

#include "VwSDK.Error.h"

#include <vector>
using namespace std;

#define IN
#define OUT
#define INOUT

typedef unsigned int UINT;

namespace VWSDK
{

	enum PIXEL_FORMAT
	{
		PIXEL_FORMAT_MONO8					= 0x01080001,
		PIXEL_FORMAT_MONO8_SIGNED			= 0x01080002,
		PIXEL_FORMAT_MONO10					= 0x01100003 ,
		PIXEL_FORMAT_MONO10_PACKED			= 0x010C0004,
		PIXEL_FORMAT_MONO12					= 0x01100005,
		PIXEL_FORMAT_MONO12_PACKED			= 0x010C0006,
		PIXEL_FORMAT_MONO14					= 0x01100025,
		PIXEL_FORMAT_MONO16					= 0x01100007,
		PIXEL_FORMAT_BAYGR8					= 0x01080008,
		PIXEL_FORMAT_BAYRG8					= 0x01080009,
		PIXEL_FORMAT_BAYGB8					= 0x0108000A,
		PIXEL_FORMAT_BAYBG8					= 0x0108000B,
		PIXEL_FORMAT_BAYGR10 				= 0x0110000C,
		PIXEL_FORMAT_BAYRG10 				= 0x0110000D,
		PIXEL_FORMAT_BAYGB10 				= 0x0110000E,
		PIXEL_FORMAT_BAYBG10 				= 0x0110000F,
		PIXEL_FORMAT_BAYGR10_PACKED			= 0x010C0026,
		PIXEL_FORMAT_BAYGR12_PACKED			= 0x010C002A,
		PIXEL_FORMAT_BAYGR12 				= 0x01100010,
		PIXEL_FORMAT_BAYRG12 				= 0x01100011,
		PIXEL_FORMAT_BAYGB12 				= 0x01100012,
		PIXEL_FORMAT_BAYBG12 				= 0x01100013,
		PIXEL_FORMAT_BAYRG10_PACKED			= 0x010C0027,
		PIXEL_FORMAT_BAYRG12_PACKED			= 0x010C002B,
		PIXEL_FORMAT_RGB8_PACKED			= 0x02180014,
		PIXEL_FORMAT_BGR8_PACKED			= 0x02180015,
		PIXEL_FORMAT_YUV422_UYVY			= 0x0210001F,
		PIXEL_FORMAT_YUV422_YUYV			= 0x02100032,
		PIXEL_FORMAT_YUV422_10_PACKED		= 0x80180001,
		PIXEL_FORMAT_YUV422_12_PACKED		= 0x80180002,
		PIXEL_FORMAT_YUV411					= 0x020C001E,
		PIXEL_FORMAT_YUV411_10_PACKED		= 0x80120004,
		PIXEL_FORMAT_YUV411_12_PACKED		= 0x80120005,
		PIXEL_FORMAT_BGR10V1_PACKED			= 0x0220001C,
		PIXEL_FORMAT_BGR10V2_PACKED			= 0x0220001D,
		PIXEL_FORMAT_RGB12_PACKED			= 0x0230001A,
		PIXEL_FORMAT_BGR12_PACKED			= 0x0230001B,
		PIXEL_FORMAT_YUV444					= 0x02180020,
		PIXEL_FORMAT_PAL_INTERLACED			= 0x02100001,
		PIXEL_FORMAT_NTSC_INTERLACED		= 0x02100002
	};

}//namespace VWSDK

#ifdef __cplusplus
extern "C"
{
#endif

namespace VWSDK
{
	enum GET_CUSTOM_COMMAND
	{
		GET_CUSTOM_COMMAND_VALUE	= 0xF0,			// Value
		GET_CUSTOM_COMMAND_NUM,						// Entry Num
		GET_CUSTOM_COMMAND_MIN,						// Minimum
		GET_CUSTOM_COMMAND_MAX,						// Maximum
		GET_CUSTOM_COMMAND_INC,						// Increment
		GET_CUSTOM_COMMAND_INDEX
	};

	typedef enum
	{
		ATTR_VALUE		= 0,
		ATTR_BASE		= 1,
		ATTR_INT		= 2,
		ATTR_BOOLEAN	= 3,
		ATTR_COMMAND	= 4,
		ATTR_FLOAT		= 5,
		ATTR_STRING		= 6,
		ATTR_REGISTER	= 7,
		ATTR_CATEGORY	= 8,
		ATTR_ENUM		= 9,
		ATTR_ENUM_ENTRY	= 10,
		ATTR_PORT		= 11
	} PROPERTY_TYPE;



	typedef enum
	{
		NOT_IMPLEMENT			= 0,				// Not implemented
		NOT_AVAILABLE			= 1,				// Not available
		WRITE_ONLY				= 2,				// Write Only
		READ_ONLY				= 3,				// Read Only
		READ_WRITE				= 4,				// Read and Write
		ACC_UNDIFINE			= 5,				// Object is not yetinitialized
		_CycleDetectAccesMode	= 6					// used internally for AccessMode cycle detection
	} PROPERTY_ACCESS_MODE;



	typedef enum 
	{
		BEGINNER				= 0,				// Always visible
		EXPERT					= 1,				// Visible for experts or Gurus
		GURU					= 2,				// Visible for Gurus
		INVISIBLE				= 3,				// Not Visible
		VISI_UNDEFINE			= 99				// Object is not yetinitialized

	} PROPERTY_VISIBILITY;



	typedef enum 
	{
		REP_LINEAR,									// Slider with linear behavior
		REP_LOGARITHMIC,							// Slider with logarithmic behavior
		REP_BOOLEAN,								// Check box
		REP_PURENUMBER,								// Decimal number in an edit control
		REP_HEXNUMBER,								// Hex number in an edit control
		REP_IPV4ADDRESS,							// IP-Address
		REP_MACADDRESS,								// MAC-Address
		REP_UNDEFINE
	} PROPERTY_REPRESENTATION;

	typedef struct _PROPERTY
	{
	public:
		PROPERTY_TYPE			ePropType;  
		PROPERTY_ACCESS_MODE	eAccessMode;
		PROPERTY_VISIBILITY		eVisibility;
		PROPERTY_REPRESENTATION eRepresentation;
		UINT					unPollingTime;

		char					caName[256];
 		char 					caDisplay[256];		
 		char					caDescription[2048];
 		
		_PROPERTY()
		{
			ePropType			= ATTR_VALUE;
			eAccessMode			= ACC_UNDIFINE;
			eVisibility			= VISI_UNDEFINE;
			eRepresentation		= REP_UNDEFINE;

			unPollingTime		= 0;

			memset(caName,			NULL, sizeof(caName));
			memset(caDisplay,		NULL, sizeof(caDisplay));
			memset(caDescription,	NULL, sizeof(caDescription));
		}
	} PROPERTY;

	typedef std::vector<PROPERTY> PROPERTY_LIST;	

}//namespace VWSDK

#ifdef __cplusplus
}
#endif


#endif
