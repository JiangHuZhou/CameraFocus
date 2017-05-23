//#pragma once 
#ifndef VWGIGE_ERROR_H
#define VWGIGE_ERROR_H
#include <tchar.h>

namespace VWSDK
{

	enum RESULT
	{
		RESULT_SUCCESS,											// Success.
	
		RESULT_ERROR,											// Unspecified runtime error.
		RESULT_ERROR_OPENED_ALREADY,							// The module handle to open already opened.
		RESULT_ERROR_INVALID_HANDLE,							// Given handle does not support the operation; e.g. function call on wrong handle or NULL pointer.
		RESULT_ERROR_TL_HANDLE,									// Internal error. GenTL Transport handle is invalid.
		RESULT_ERROR_TLOPEN,									// Internal error. GenTL TLOpen function returned error.
		RESULT_ERROR_IF_HANDLE,									// Internal error. GenTL Interface handle is invalid.
		RESULT_ERROR_INITIALIZATION,							// Module was not initialized
		RESULT_ERROR_INVALID_PARAMETER,							// One of the parameter given was not valid or out of range and none of the error codes about fits.
		RESULT_ERROR_DISCOVERY,									// There was an error on the discovery.
		RESULT_ERROR_NO_CAMERAS,								// There are no cameras.
		RESULT_ERROR_CAMERA_NAME_DOES_NOT_EXIST,				// The camera name of which you are trying to open does not exist.
		RESULT_ERROR_ABORTED_ALREADY,							// The Abort command was already completed.
		RESULT_ERROR_ACCESS_DENIED,								// Access to the camera is denied.
		RESULT_ERROR_RESOURCE_IN_USE,							// The handle or resource has already been used.

		RESULT_ERROR_CANNOT_FIND_INTERFACE,						// Failed to find the interface.

		RESULT_ERROR_XML_UNKNOWN_ARGUMENT,						// The argument value is out of range or cannot be recognized.
		RESULT_ERROR_XML_NODE_ACCESS_FAILED,					// The Node map is abnormal or AccessMode for the node is NI/NA. 
		RESULT_ERROR_XML_NOT_EXIST_NODE,						// The node does not exist.
		RESULT_ERROR_XML_ENTERED_NODE_DOESNT_HAVE_ANY_VALUE,	// The node doesn't have any value like COMMAND, CATEGORY.
		RESULT_ERROR_XML_UNSUPPORTED_COMMAND,					// Unknown command.

		RESULT_ERROR_INVALID_WIDTH,								// Width is not multiples of 4.
		RESULT_ERROR_INVALID_ADDRESS,							// Unknown address.

		RESULT_ERROR_VWINTERFACE_NO_NIC,						// There is no interface card.
		RESULT_ERROR_VWINTERFACE_GETINTERFACENAME,				// Failed to retrieve a interface name.
		RESULT_ERROR_VWINTERFACE_OPENINTERFACE,					// OpenInterface function returned an error.
		RESULT_ERROR_VWINTERFACE_CLOSEINTERFACE,				// CloseInterface function returned an error.
		RESULT_ERROR_VWINTERFACE_GETNUMDEVICES,					// GetNumDevices function returned an error.
		RESULT_ERROR_VWINTERFACE_CANNOT_FIND_DEVICE,			// Failed to find a device.

		RESULT_ERROR_VWCAMERA_INTERFACE_HANDLE,					// The interface handle is invalid.
		RESULT_ERROR_VWCAMERA_CAMERAINDEX_OVER,					// The camera index is over the maximum number of cameras.
		RESULT_ERROR_VWCAMERA_GETXML,							// There is a problem with the XML that was retrieved from the camera.
		RESULT_ERROR_VWCAMERA_IMAGE_NOT4DIVIDE,					// Width must divide by 4.
		RESULT_ERROR_VWCAMERA_IMAGE_NOT2DIVIDE,					// Width must divide by 2.
		RESULT_ERROR_VWCAMERA_READ_ONLY,						// The node is read only.
		RESULT_ERROR_VWCAMERA_EVENTCONTROL_DOESNOT_INIT,		// Event control function did not initialize.
		RESULT_ERROR_VWCAMERA_GRAB_TIMEOUT,						// Time-out is occurred in grab routine.
		RESULT_ERROR_VWCAMERA_CALLBACK_NOT_NULL,				// Callback function pointer is not null.


		RESULT_ERROR_DEVCREATEDATASTREAM,						// Internal error. GenTL DevCreateDataStream function returned error.

		RESULT_ERROR_DATASTREAM_MTU,							// Internal error. The MTU of the NIC is too small to get a image.

		RESULT_ERROR_TLGETNUMINTERFACES,						// Internal error. GenTL TLGetNumInterfaces function returned error.
		RESULT_ERROR_TLOPENINTERFACE,							// Internal error. GenTL TLOpenInterface function returns error.
		RESULT_ERROR_TLCLOSEINTERFACE,							// Internal error. GenTL TLCloseInterface function returns error.
		RESULT_ERROR_TLGETINTERFACENAME,						// Internal error. GenTL TLGetInterfaceName function returned error.
		RESULT_ERROR_TLGETNUMDEVICES,							// Internal error. GenTL TLGetNumDevices function returns error.
		RESULT_ERROR_TLGETDEVICENAME,							// Internal error. GenTL TLGetDeviceName function returns error.
		RESULT_ERROR_TLOPENDEVICE,								// Internal error. GenTL TLOpenDevice function returns error.

		RESULT_ERROR_INSUFFICIENT_RESOURCES,					// Insufficient system resources. Unable to allocate memory as many as defined the number of buffers.
		RESULT_ERROR_MEMORY_ALLOCATION,							// Unable to allocate memory.

		RESULT_ERROR_FILE_STREAM_OPEN_FAILURE,					// Failed to open File stream.
		RESULT_ERROR_FILE_STREAM_READ_FAILURE,					// Failed to read File stream.
		RESULT_ERROR_FILE_STREAM_WRITE_FAILURE,					// Failed to write File stream.
		RESULT_ERROR_FILE_STREAM_CLOSE_FAILURE,					// Failed to close File stream.
		RESULT_ERROR_FILE_STREAM_NOT_CORRECT_FILE_LENGTH,		// File length is incorrect.

		RESULT_ERROR_EXCEPTION,									// An exception is occurred.

		RESULT_LAST												// The count of error items. Don't use it.
	};


	const int MAX_ERROR_DESCRIPTION = 256;

	static const TCHAR ERROR_DESCRIPTION[RESULT_LAST][MAX_ERROR_DESCRIPTION] =
	{
		{_T("SUCCESS\0")},

		{_T("ERROR : Default error code returned\0")},
		{_T("ERROR_OPENED_ALREADY\0")},
		{_T("ERROR_INVALID_HANDLE\0")},
		{_T("ERROR_TL_HANDLE\0")},
		{_T("ERROR_TLOPEN\0")},
		{_T("ERROR_IF_HANDLE\0")},
		{_T("ERROR_VWGIGE_INITIALIZATION\0")},
		{_T("ERROR_INVALID_PARAMETER\0")},
		{_T("ERROR_DISCOVERY\0")},
		{_T("ERROR : RESULT_ERROR_NO_CAMERAS was returned \\ CHECK : NIC properties\0")},
		{_T("ERROR_CAMERA_NAME_DOES_NOT_EXIST\0")},
		{_T("ERROR_ABORTED_ALREADY\0")},
		{_T("ERROR_ACCESS_DENIED\0")},
		{_T("ERROR_RESOURCE_IN_USE\0")},
		{_T("ERROR_CANNOT_FIND_INTERFACE\0")}
		,
		{_T("ERROR_XML_UNKNOWN_ARGUMENT\0")},
		{_T("ERROR_XML_NODE_ACCESS_FAILED\0")},
		{_T("ERROR_XML_NOT_EXIST_NODE\0")},
		{_T("ERROR_XML_ENTERED_NODE_DOESNT_HAVE_ANY_VALUE\0")},
		{_T("ERROR_XML_UNSUPPORTED_COMMAND\0")},

		{_T("ERROR_INVALID_WIDTH\0")},
		{_T("ERROR_INVALID_ADDRESS\0")},

		{_T("ERROR_VWINTERFACE_NO_NIC\0")},
		{_T("ERROR_VWINTERFACE_GETINTERFACENAME\0")},
		{_T("ERROR_VWINTERFACE_OPENINTERFACE\0")},
		{_T("ERROR_VWINTERFACE_CLOSEINTERFACE\0")},
		{_T("ERROR_VWINTERFACE_GETNUMDEVICES\0")},
		{_T("ERROR_VWINTERFACE_CANNOT_FIND_DEVICE,\0")},

		{_T("ERROR_VWCAMERA_INTERFACE_HANDLE\0")},
		{_T("ERROR : RESULT_ERROR_VWCAMERA_CAMERAINDEX_OVER was returned \\ CHECK : Zero-based camera index\0")},
		{_T("ERROR_VWCAMERA_GETXML\0")},
		{_T("ERROR_VWCAMERA_IMAGE_NOT4DIVIDE\0")},
		{_T("ERROR_VWCAMERA_IMAGE_NOT2DIVIDE\0")},
		{_T("ERROR_VWCAMERA_READ_ONLY\0")},
		{_T("RESULT_ERROR_VWCAMERA_EVENTCONTROL_DOESNOT_INIT\0")},
		{_T("ERROR : Time-out is occurred in grab routine \0")},
		{_T("ERROR : Callback function pointer is not null \0")},

		{_T("ERROR : RESULT_ERROR_DEVCREATESTREAM was returned\0")},

		{_T("ERROR : RESULT_ERROR_STREAM_MTU was returned \\ CHECK : Check NIC MTU\0")},

		{_T("ERROR_TLGETNUMINTERFACES\0")},
		{_T("ERROR_TLOPENINTERFACE\0")},
		{_T("ERROR_TLCLOSEINTERFACE\0")},
		{_T("ERROR_TLGETINTERFACENAME\0")},
		{_T("ERROR_TLGETNUMDEVICES\0")},
		{_T("ERROR_TLGETDEVICENAME\0")},
		{_T("ERROR_TLOPENDEVICE\0")},

		{_T("ERROR : RESULT_ERROR_INSUFFICIENT_RESOURCES was returned \\ CHECK : Check system resources\0")},
		{_T("ERROR : RESULT_ERROR_MEMORY_ALLOCATION was returned \\ CHECK : Check system resources\0")},

		{_T("ERROR_FILE_STREAM_OPEN_FAILURE\0")},
		{_T("ERROR_FILE_STREAM_READ_FAILURE\0")},
		{_T("ERROR_FILE_STREAM_WRITE_FAILURE\0")},
		{_T("ERROR_FILE_STREAM_CLOSE_FAILURE\0")},
		{_T("ERROR_FILE_STREAM_NOT_CORRECT_FILE_LENGTH\0")},

		{_T("RESULT_ERROR_EXCEPTION\0")}

	};



	inline const TCHAR* VwErrorReport(RESULT result)
	{
		if( result >= RESULT_LAST || result < RESULT_SUCCESS )
			return 0;

		return ERROR_DESCRIPTION[result];
	}


}//namespace VWSDK

#endif