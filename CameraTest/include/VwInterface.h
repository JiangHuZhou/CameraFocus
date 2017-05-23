#pragma once

#ifndef VWINTERFACE_H
#define VWINTERFACE_H

// #ifdef USE_TLI_V7
// #include "GenTL_v1_3.h"
// #else
// #include "GenTL.V1.2.h"
// #endif

#include "VwGigE.Global.h" 
#include "VwCamera.h"
#include <list>
#include <map>
#include <string>

struct INFO_DATATYPE;

// Needs to have dll-interface to be used by clients of class 'VwInterface'
#pragma warning ( disable : 4251 )

#ifdef _USRDLL
#define CLASS_IMPORTEXPORT __declspec(dllexport)
#else if
#define CLASS_IMPORTEXPORT __declspec(dllimport)
#endif

using namespace std;


namespace VWSDK
{


	// forward declaration
	class VwCamera;
	class VwGigE;



	//+++++++++++++++++++++++++++++++++++++++++++++++
	// class VwInterface
	//+++++++++++++++++++++++++++++++++++++++++++++++
	class CLASS_IMPORTEXPORT VwInterface
	{
		protected:
			VwGenICam::TL_HANDLE	hTL;
			VwGenICam::IF_HANDLE	hInterface;
			map<string, VwCamera*>	vwCameraList;
	
			char		caName[128];
			VwGigE*		m_pVwGigE;

			UINT		m_unFilterType;
			DWORD		_dwMultiCastAddress;
			BOOL		_bUseQueueManager;
			CCP_PRIVILEGE	_eCCPPrivilege;

		protected:
			VwInterface(void);

		public:
			VwInterface( VwGenICam::TL_HANDLE _hTL, UINT unFilterType );
			~VwInterface(void);

		public:
			VwGenICam::IF_HANDLE GetInterfaceHandle()	{	return hInterface;	}
			std::map<std::string, VwCamera*>* GetCameraList()	{	return &vwCameraList; }
			RESULT GetVwGigE( VwGigE* pVwGigE );
			RESULT OpenInterface(char* name, IN VwGigE* pVwGigE );
			RESULT CloseInterface();
			RESULT RemoveCameraList();
			RESULT GetNumCameras(UINT* pNumDevices);
			RESULT GetCameraName(UINT unDevIndex, char* pcaName,size_t* pcbNameSize);
			RESULT GetCameraID(UINT unDevIndex, char* pcaID,size_t* pcbNameSize);
			RESULT GetSubnet( char* pszSubnet, size_t* paSubnet);
			RESULT GetIPAddress( char* pszIPAddress, size_t* paIPAddress );
			RESULT OpenCamera(char* name,VwCamera** ppVwCamera,UINT nNumBuffer,UINT nWidth, UINT nHeight, UINT nPacketSize,
							  void* pUserPointer,ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL );
			RESULT OpenCamera(UINT nIndex,VwCamera** ppVwCamera,UINT nNumBuffer,UINT nWidth, UINT nHeight, UINT nPacketSize,
							  void* pUserPointer,ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL );
			RESULT GetInterfaceInfo( const char* sIfaceID, VwGenICam::INTERFACE_INFO_CMD_LIST iInfoCmd, VwGenICam::INFO_DATATYPE* piType, void* pBuffer, size_t* piSize );

			RESULT GetFilterType( UINT* unpFilterType );
			RESULT SetFilterType( UINT unFilterType );
			RESULT GetMultiCastAddress( DWORD& dwMultiCastAddress )		{	dwMultiCastAddress = _dwMultiCastAddress;	return RESULT_SUCCESS;	};
			RESULT SetMultiCastAddress( DWORD dwMultiCastAddress )		{	_dwMultiCastAddress = dwMultiCastAddress;	return RESULT_SUCCESS;	};

			RESULT SetImageReceivingTimeout( UINT unTimeout );
			RESULT GetImageReceivingTimeout( UINT& unTimeout );

			RESULT SetImageRetransTimeout( UINT unTimeout );
			RESULT GetImageRetransTimeout( UINT& unTimeout );
			RESULT UsePacketResend( BOOL bUse );
			RESULT UseLAGMode( BOOL bUse );
			RESULT UsePacketResendFrequently( BOOL bUse );

			RESULT UseQueueManager( BOOL bUse )							{	_bUseQueueManager	=	bUse;				return RESULT_SUCCESS;	};
			RESULT SetCCPPrivilege( IN CCP_PRIVILEGE eCCPPrivilege )	{	_eCCPPrivilege		=	eCCPPrivilege;		return RESULT_SUCCESS;	};
	};

}//namespace VWSDK
#endif