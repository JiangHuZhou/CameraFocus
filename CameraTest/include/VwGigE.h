#pragma once 

//#include <Client.h>

#include "VwGigE.Global.h"

// #include "VwInterface.h"		// remove dependency
// #include "VwCamera.h"		// remove dependency

#include <list>
#include <map>

#ifdef _USRDLL
	#define CLASS_IMPORTEXPORT __declspec(dllexport)
#else if
	#define CLASS_IMPORTEXPORT __declspec(dllimport)
#endif

// Needs to have dll-interface to be used by clients of class 'VwInterface'
#pragma warning ( disable : 4251 )

using namespace std;

namespace VWSDK
{

	class VwInterface;
	class VwCamera;

	class VWCAMERA_INFO
	{
	public:
		BOOL				error;
		RESULT				errorResult;
		UINT				index;
		// CAMERA_HANDLE	hCam;
		char				name[256];
		char				vendor[128];
		char				model[128];
		char				ip[32];
		char				mac[32];
	
	public:
		VWCAMERA_INFO()
		{
			error = FALSE;
			errorResult = RESULT_LAST;
			index	= 0;
			// hCam = NULL;
			memset(name,0,sizeof(name));
			memset(vendor,0,sizeof(vendor));
			memset(model,0,sizeof(model));
			// Add::2014721, 김은표, 초기화 코드 추가
			memset(vendor, 0, sizeof(vendor));
			memset(ip, 0, sizeof(ip));
			memset(mac, 0, sizeof(mac));
		}
	};

	class CLASS_IMPORTEXPORT VWINTERFACE_INFO
	{
	public:
		BOOL				error;
		RESULT				errorCause;
		UINT				index;
		char				name[256];
		list<VWCAMERA_INFO*>	cameraInfoList;
	public:
		VWINTERFACE_INFO()
		{
			error			= FALSE;
			index			= 0;
			memset(name,0,sizeof(name));
			cameraInfoList.clear();
		}
		~VWINTERFACE_INFO()
		{
			if(cameraInfoList.size() == 0)
				return;

			for(list<VWCAMERA_INFO*>::iterator iterCam = cameraInfoList.begin(); iterCam != cameraInfoList.end(); )
			{
				if ( (*iterCam) != NULL )
				{
					delete (*iterCam);
					(*iterCam) = NULL;
					iterCam = cameraInfoList.erase( iterCam );
				}
				else
				{
					iterCam ++;
				}
			}
		}

		void AddCameraInfo(VWCAMERA_INFO* pCameraInfo)
		{
			cameraInfoList.push_back(pCameraInfo);
		}
	};


	class DISCOVERY_INFO
	{
	public:
		DISCOVERY_INFO()
		{

		}
		~DISCOVERY_INFO()
		{
		}
	public:
		list<VWINTERFACE_INFO*>	interfaceInfoList;
	public:
		VWINTERFACE_INFO*	GetInterfaceInfo(UINT nIndex)
		{
			UINT ifCount = 0;
			list<VWINTERFACE_INFO*>::iterator ifInfoIter;
			for(ifInfoIter = interfaceInfoList.begin(); ifInfoIter != interfaceInfoList.end(); ifInfoIter++)
			{
				if(nIndex == ifCount)
				{
					VWINTERFACE_INFO** pInterfaceInfo = (&(*ifInfoIter));
					return *pInterfaceInfo;
				}
				ifCount ++;
			}
			return NULL;
		}
		UINT GetNumInterfaces()
		{
			return (UINT)interfaceInfoList.size();
		}

		void Clear()
		{
			for(list<VWINTERFACE_INFO*>::iterator iterDis = interfaceInfoList.begin(); iterDis != interfaceInfoList.end();)
			{
				if ( (*iterDis) != NULL )
				{
					VWINTERFACE_INFO* pInterfaceInfo = (VWINTERFACE_INFO*)(*iterDis);
					if(pInterfaceInfo)
					{
						/*
						for(list<VWCAMERA_INFO*>::iterator iterCam = pInterfaceInfo->cameraInfoList.begin(); iterCam != pInterfaceInfo->cameraInfoList.end(); )
						{
							if ( (*iterCam) != NULL )
							{
								delete (*iterCam);
								iterCam = pInterfaceInfo->cameraInfoList.erase( iterCam );

							}
							else
							{
								iterCam ++;
							}
						}
						*/
						delete pInterfaceInfo;
						iterDis = interfaceInfoList.erase( iterDis );

					}
				}
				else
				{
					iterDis ++;
				}
			}
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++
	// class VwGigE
	//+++++++++++++++++++++++++++++++++++++++++++++++
	class CLASS_IMPORTEXPORT VwGigE
	{
		private:
			VwGenICam::TL_HANDLE		hTL;					// System handle for GigaLinx
			DISCOVERY_INFO	discoveryInfo;			// After calling Discovery() 
			BOOL			isDiscovered;			// Discover completed?
			std::map<string, VwInterface*>	vwInterfaceList;
		
			UINT			m_unFilterType;
			DWORD			_dwMultiCastAddress;
			bool			_bIgnoreSubnet;

			INT64			_nDiscoveryTimeout;

			BOOL			_bUseQueueManager;
			CCP_PRIVILEGE	_eCCPPrivilege;

		protected:
			BOOL IsValidIP( string strInterfaceSubnet, string strInterfaceIP, string strDeviceIP );

		public:
			VwGigE();
			~VwGigE();
	
			// FUNCTION Open() --------------------------------------
			// 1. Description 
			// (1) Open hTL for GenTL TL_HANDLE
			// (2) Class relationship is
			// VwGigE (Wrapping TL_HANDLE) -> VwInterface (Wrapping IF_HANDLE) -> VwCamera (Wrapping DEV_HANDLE)
			// (3) It must be called to use VwGigE
			// 2. Parameters
			// None
			// 3. Return 
			// RESULT
			// 4. Activity
			// (1) Open TL_HANDLE
			// (2) If discovery didn't called, it calls discovery function
			RESULT Open();

			// FUNCTION Open() --------------------------------------
			// 1. Description 
			// (1) Close hTL for GenTL TL_HANDLE
			// (2) Close all of the interfaces and delete VwInterface objects
			// (3) Close all of the cameras and delete VwCamera objects
			// 2. Parameters
			// None
			// 3. Return 
			// RESULT
			// 4. Activity
			// (1) Delete discovery info.
			RESULT Close();
	
			// Get the number of cameras connected
			RESULT Discovery();
			RESULT GetDiscoveryInfo( OUT DISCOVERY_INFO& DiscoveryInfo );
			RESULT GetNumCameras(UINT* pNumCameras);
			RESULT GetNumInterfaces(UINT* pNumInterfaces);
			RESULT OpenInterface(UINT nIndex,VwInterface** pVwInterface);
			RESULT OpenInterface( char* name, VwInterface** ppVwInterface );
			RESULT CloseCamera( VwCamera* pVwCamera );
			RESULT OpenCamera(UINT nCameraIndex,OUT VwCamera** ppCamera,UINT nNumBuffer,UINT nWidth, UINT nHeight, UINT nPacketSize,
								void* pUserPointer, ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);
			RESULT OpenCamera(char* pCameraName,OUT VwCamera** ppCamera,UINT nNumBuffer,UINT nWidth, UINT nHeight, UINT nPacketSize,
								void* pUserPointer, ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);
			RESULT OpenCamera(OUT VwCamera** ppCamera, UINT width,UINT height, UINT nPacketSize, UINT nNumBuffer,
								ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn);
			RESULT OpenCamera( char* pInterfaceName, UINT nCameraIndex,OUT VwCamera** ppCamera,UINT nNumBuffer,UINT nWidth, UINT nHeight,
								UINT nPacketSize, void* pUserPointer, ImageCallbackFn* pImageCallbackFn,
								DisconnectCallbackFn* pDisconnectCallbackFn = NULL);
			RESULT GetCameraInfo( IN UINT nIndex, OUT VWCAMERA_INFO* pCameraInfo );
			RESULT GetCameraInfo( IN char* pCameraName, OUT VWCAMERA_INFO* pCameraInfo );
			RESULT GetInterfaceInfo( IN UINT nIndex, OUT VWINTERFACE_INFO* pInterfaceInfo );
			RESULT GetInterfaceInfo( IN char* pInterfaceName, OUT VWINTERFACE_INFO* pInterfaceInfo );
			RESULT SetForceIP( IN PBYTE mac, IN DWORD nIP, IN DWORD nSubnet, IN DWORD nGateway );

			RESULT GetFilterType( UINT* unpFilterType );
			RESULT SetFilterType( UINT unFilterType );

			RESULT UseMTUOptimize( IN BOOL bUse );
			RESULT SetMTUTimeout( IN UINT uTimeout );
			RESULT GetMTUTimeout( OUT UINT& uTimeout );
			RESULT SetGVCPTimeout( IN UINT uTimeout );
			RESULT GetGVCPTimeout( OUT UINT& uTimeout );

			RESULT SetMultiCastAddress( DWORD dwMultiCastAddress )		{	_dwMultiCastAddress= dwMultiCastAddress;	return RESULT_SUCCESS;	};
			RESULT GetMultiCastAddress( DWORD& dwMultiCastAddress )		{	dwMultiCastAddress = _dwMultiCastAddress;	return RESULT_SUCCESS;	};

			RESULT SetIgnoreSubnet( IN bool bUse )						{	_bIgnoreSubnet	=	bUse;					return RESULT_SUCCESS;	};
			RESULT GetIgnoreSubnet( OUT bool& bUse )					{	bUse			=	_bIgnoreSubnet;			return RESULT_SUCCESS;	};

			RESULT SetDiscoveryTimeout( IN UINT uTimeOut )				{   _nDiscoveryTimeout = uTimeOut;				return RESULT_SUCCESS;	};
			RESULT GetDiscoveryTimeout( OUT UINT& uTimeOut )			{   uTimeOut		   = _nDiscoveryTimeout;	return RESULT_SUCCESS;	};

			RESULT UseQueueManager( IN BOOL bUse )						{	_bUseQueueManager	=	bUse;				return RESULT_SUCCESS;	};
			RESULT SetCCPPrivilege( IN CCP_PRIVILEGE eCCPPrivilege )	{	_eCCPPrivilege		=	eCCPPrivilege;		return RESULT_SUCCESS;	};
	};

}//namespace VWSDK