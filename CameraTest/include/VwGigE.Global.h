 
//#pragma once

#ifndef VWGIGE_GLOBAL_H
#define VWGIGE_GLOBAL_H

#include "VwSDK.h"

#include "windows.h"

#include <vector>
using namespace std;

namespace VWSDK
{

	#define IN
	#define OUT
	#define INOUT

	// Event types for GeneralEventCallback
	#define VWDEF_EVENT_TYPE_FRAME_DROP					0X00000001
	#define VWDEF_EVENT_TYPE_TEMP_EXCEED_LIMIT			0x00000002

	enum EventType
	{
		EVENT_TYPE_FRAME_DROP				=	0x0000001,
		EVENT_TYPE_SENSOR_MASTER			=	0x0000002,
		EVENT_TYPE_SENSOR_SLAVE				=	0x0000003,
		EVENT_TYPE_LINK_SPEED				=	0x0000004,
		EVENT_TYPE_TEMP_EXCEED_LIMIT		=	0x0000005
	};



	enum TESTIMAGE
	{
		TESTIMAGE_OFF, 
		TESTIMAGE_BLACK, 
		TESTIMAGE_WHITE, 
		TESTIMAGE_GREYHORIZONTALRAMP, 
		TESTIMAGE_GREYVERTICALRAMP, 
		TESTIMAGE_GREYHORIZONTALRAMPMOVING, 
		TESTIMAGE_GREYVERTICALRAMPMOVING,
		TESTIMAGE_GREYCROSSRAMP,
		TESTIMAGE_GREYCROSSRAMPMOVING
	};

	enum STROBE_POLARITY
	{
		STROBE_POLARITY_ACTIVEHIGH, 
		STROBE_POLARITY_ACTIVELOW
	};


	enum BLACKLEVEL_SEL
	{
		BLACKLEVEL_SEL_ALL,
		BLACKLEVEL_SEL_TAP1, 
		BLACKLEVEL_SEL_TAP2, 
		BLACKLEVEL_SEL_TAP3, 
		BLACKLEVEL_SEL_TAP4,
		BLACKLEVEL_SEL_GREEN = 9,
		BLACKLEVEL_SEL_RED,
		BLACKLEVEL_SEL_BLUE

	};

	enum EXPOSURE_MODE
	{
		EXPOSURE_MODE_TIMED, 
		EXPOSURE_MODE_TRIGGERWIDTH
	};

	enum READOUT
	{
		READOUT_NORMAL,
		READOUT_AOI, 
		READOUT_BINNING, 
		READOUT_HORIZONTALSTART, 
		READOUT_HORIZONTALEND, 
		READOUT_VERTICALSTART, 
		READOUT_VERTICALEND, 
		READOUT_BINNINGFATOR
	};

	enum GAIN_SEL
	{
		GAIN_ANALOG_ALL, 
		GAIN_ANALOG_TAP1, 
		GAIN_ANALOG_TAP2, 
		GAIN_ANALOG_TAP3, 
		GAIN_ANALOG_TAP4,
		GAIN_DIGITAL_GREEN = 9,
		GAIN_DIGITAL_RED,
		GAIN_DIGITAL_BLUE,
		GAIN_DIGITAL_ALL
	};

	enum TRIGGER_SOURCE
	{
		TRIGGER_SOURCE_SW, 
		TRIGGER_SOURCE_EXT
	};

	enum TRIGGER_ACTIVATION
	{
		TRIGGER_ACTIVATION_RISINGEDGE,
		TRIGGER_ACTIVATION_FALLINGEDGE
	};

	enum GAIN_COLOR
	{
		GAIN_COLOR_RED,
		GAIN_COLOR_GREEN,
		GAIN_COLOR_BLUE
	};

	enum STREAM_INFO
	{
		STREAM_INFO_NUM_OF_FRAMES_LOST,
		STREAM_INFO_NUM_PACKETS_MISSING
	};

	enum FILTER_TYPE
	{
		FILTER_TYPE_DIRECT = 1,	
		FILTER_TYPE_WPCAB
	};

	enum MTU_SETTING
	{
		GVCP_SETTING_TIMEOUT	= 0x00000002,
		MTU_SETTING_OPTIMIZE	= 0x00000003,
		MTU_SETTING_TIMEOUT		= 0x00000004
	};

}//namespace VWSDK


#ifdef __cplusplus
extern "C"
{
#endif

namespace VWSDK
{

	
	struct OBJECT_INFO
	{
		void*		pUserPointer;
		void*		pVwCamera;
		OBJECT_INFO()
		{
			pUserPointer	= NULL;
			pVwCamera		= NULL;
		}
	};

	struct IMAGE_INFO
	{
		RESULT			callbackResult;
		unsigned int	bufferIndex;
		PIXEL_FORMAT	pixelFormat;
		unsigned int	width;
		unsigned int	height;
		UINT64			unTimeStamp;
		UINT			ImageStatus;
		void*			pImage;
	};

	struct CAMERA_INFO_STRUCT
	{
		BOOL				error;
		RESULT				errorResult;
		unsigned int		index;
		char				name[256];
		char				vendor[128];
		char				model[128];
		char				ip[32];
		char				mac[32];

	public:
		CAMERA_INFO_STRUCT()
		{
			error			= FALSE;
			errorResult		= RESULT_ERROR;
			index			= 0;
			// hCam = NULL;
			memset(name,0,sizeof(name));
			memset(vendor,0,sizeof(vendor));
			memset(model,0,sizeof(model));
			memset(ip,0,sizeof(ip));
			memset(mac,0,sizeof(mac));
		}
	};

	struct INTERFACE_INFO_STRUCT
	{
		BOOL				error;
		RESULT				errorCause;
		unsigned int		index;
		char				name[256];
	};

	struct PIXEL_FORMAT_INFO
	{
		char				szName[256];
		PIXEL_FORMAT		pixelFormat;
		unsigned int		nSize;
	};

	struct DISCONNECT_INFO
	{
		int					nCurrHeartBeatTimeOut;	//	Current heartbeat timeout millisecond. 
		int					nTimeOutTryCount;		//	Heartbeat timeout try count.
	};


	typedef enum 
	{
		CCP_NOCONTEXT		= 0,		// 
		PRIVILEGE_EXCLUSIVE = 1,		//!< Exclusive control privilege (read-write)
		PRIVILEGE_CONTROL	= 2,		//!< Control privilege (read-write)
		PRIVILEGE_MONITOR	= 3		//!< Monitor privilege (read-only)
	} CCP_PRIVILEGE;

}//namespace VWSDK

#ifdef __cplusplus
}
#endif

namespace VwGenICam
{
	typedef unsigned __int64 uint64_t;
	typedef unsigned __int32 uint32_t;
	typedef void *      TL_HANDLE;
	typedef void *      IF_HANDLE;
	typedef void *      DEV_HANDLE; 
	typedef void *      DS_HANDLE;  
	typedef void *      PORT_HANDLE;
	typedef void *      EVENT_HANDLE;
	typedef void *      BUFFER_HANDLE;
	typedef __int32		INFO_DATATYPE;
	typedef __int32		EVENT_TYPE;

	struct EVENT_DATA
	{
		__int64		llnBlockID;
		__int64		llnTimestamp;
		WORD			wEventID;
		WORD			wStreamChannelIndex;
		WORD			wBlockID;
		void*			pDeviceHandle;
		void*			pUserPointer;
	};

	enum INTERFACE_INFO_CMD_LIST
	{
		INTERFACE_INFO_ID              = 0,     /* STRING     Unique ID of the interface. */
		INTERFACE_INFO_DISPLAYNAME     = 1,     /* STRING     User readable name of the interface. */
		INTERFACE_INFO_TLTYPE          = 2,     /* STRING     Transport layer technology that is supported. */

		INTERFACE_INFO_CUSTOM_ID       = 1000,   /* Starting value for GenTL Producer custom IDs. */
		INTERFACE_INFO_MAC			   = INTERFACE_INFO_CUSTOM_ID + 1,		/* STRING     MAC address of the interface as array of 6 bytes. */
		INTERFACE_INFO_MAC_STRING	   = INTERFACE_INFO_CUSTOM_ID + 2,		/* STRING	  MAC address of the interface as string */
		INTERFACE_INFO_IP			   = INTERFACE_INFO_CUSTOM_ID + 3,
		INTERFACE_INFO_SUBNET		   = INTERFACE_INFO_CUSTOM_ID + 4,
		INTERFACE_INFO_PORT_ID		   = INTERFACE_INFO_CUSTOM_ID + 5
	};
}//namespace VwGenICam

	typedef void (ImageCallbackFn)(VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::IMAGE_INFO* pImageInfo);

	typedef void (DisconnectCallbackFn)( VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::DISCONNECT_INFO tDisconnectInfo );

	typedef void (EventControlCallbackFn)( char* pcaEventName, VwGenICam::EVENT_DATA* ptEventData);

	typedef void (GeneralEventCallbackFn)( VWSDK::EventType eEventType );



#endif
