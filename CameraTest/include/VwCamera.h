#pragma once

#ifndef VWCAMERA_H
#define VWCAMERA_H

#include "VwGigE.Global.h"
#include "VwInterface.h"
#include "VwSerial.h"
#include <string.h>
#include <list>

#pragma warning (disable:4251)

#ifdef _USRDLL
#define CLASS_IMPORTEXPORT __declspec(dllexport)
#else if
#define CLASS_IMPORTEXPORT __declspec(dllimport)
#endif

namespace GenApi
{
	class CNodeMapRef;
	struct INode;
}


namespace VWSDK
{


	// Forward declaration
	class VwInterface;
	class MyPort;



	//+++++++++++++++++++++++++++++++++++++++++++++++
	// class VwCamera
	//+++++++++++++++++++++++++++++++++++++++++++++++
	class CLASS_IMPORTEXPORT VwCamera
	{
	protected:
		VwInterface*		pInterface;
		VwGenICam::DEV_HANDLE			hCamera;
		VwGenICam::DS_HANDLE			hStream;
		GenApi::CNodeMapRef*		pNodeMap;					// Node map from XML to R/W camera parameters
		MyPort*				port;

		VwSerial			m_Serial;

		BOOL				m_bGrabRunning;			// Flag : Grab thread On/Off
		HANDLE				m_hEvtGigaLinx[2];
		HANDLE				m_hEvtWaitGrabThread;

		HANDLE				m_hEvtGrab;				// Event : Check Grab/Abort

		HANDLE				m_hEvtGrabDataIsCome;
		HANDLE				m_hEvtGrabDataIsDone;


		VwGenICam::EVENT_HANDLE		hEventNewBuffer;
		UINT				m_nCurBufIdx;				// Current Buffer Index	// m_curbufferindex;
		void**				m_ppGigaBuffer;
		void*				m_pImageBufferForCallback;
		OBJECT_INFO			m_ObjectInfo;
		IMAGE_INFO			m_ImageInfo;
		ImageCallbackFn*	m_pImageCallbackFn;
		DisconnectCallbackFn*	m_pDisconnectCallbackFn;	// When the connection has been lost, this function will be called.
		GeneralEventCallbackFn* m_pGeneralEventCallbackFn;
		VwGenICam::EVENT_TYPE			m_eEventType;
		void*				m_pUserPointer;				// for Callback Function

		HANDLE				m_pGrabCallback;
		HANDLE				m_pThrGrabCallback;

		HANDLE				m_pThrGrab;
		list<VwGenICam::BUFFER_HANDLE> m_lstBuffers;
		UINT				m_nBufferNum;
		UINT				m_nPaketsMissing;
	
		BOOL				m_bIsVXDevice;				// Flag : Vx Device 
		UINT				m_nEvtGetDataTimeOut;		// EventGetData() Timeout Value
		UINT				m_unFilterType;

		HANDLE				m_pThrDisconnect;			// Check to connect condition.
		BOOL				m_bExit;
		VwGenICam::EVENT_HANDLE m_hEventError;
		__int64				m_nFrameCount;				// Frame count

		PROPERTY_LIST		m_PropList;

		HANDLE				m_pThrGeneralEvent;			// Check to general event callback thread.


	protected:
		BOOL				_bInitEventControl;

		BOOL				_bForcedAcquisitionMode;
		BOOL				_bUseCallbackThread;
		BOOL				_bMonitorMode;
		BOOL				_bClearBuffer;
		UINT64				_unLostImage;
		UINT64				_unCorruptedPacket;
		UINT64				_unResendPacket;
		UINT64				_unLostFrame;
		BOOL				_bUseQueueManager;
		BOOL				_bAlive;
		CCP_PRIVILEGE		_eCCPPrivilege;

		list<VwGenICam::EVENT_DATA>			_lstEventCallback;

	protected:
		VwCamera(void);

		// protected method
	protected:
		void Initialize(void);
		RESULT CreateBuffer( IN const UINT nImageWidth, IN const UINT nImageHeight, IN const UINT nBitsPerPixel, IN const UINT nBufferNumber, 
			IN list<VwGenICam::BUFFER_HANDLE>& lstBuffers, IN const VwGenICam::DS_HANDLE hStream, OUT void*** pppGigaBuffer );
		RESULT DeleteBuffer();

		static RESULT RearrangeQueue( IN list<VwGenICam::BUFFER_HANDLE>& lstBuffers, IN const VwGenICam::DS_HANDLE hStream );

		static RESULT StartAcquisition( IN const VwGenICam::DS_HANDLE hStream );
		static RESULT StopAcquisition( IN const VwGenICam::DS_HANDLE hStream );

		static RESULT SetRegisterEvent( IN const VwGenICam::DS_HANDLE hStream, IN HANDLE* m_hEvtGigaLicx, OUT VwGenICam::EVENT_HANDLE m_hEventNewBuffer );

		RESULT GetPixelFormatFromString( std::string strPixelFormat, PIXEL_FORMAT* pPixelFormat );
		RESULT GetPixelFormatName( IN PIXEL_FORMAT pixelFormat, std::string* strPixelFormat );

		RESULT IsValidPixelSize( IN UINT nPixelSize, OUT BOOL* pbValid );

		BOOL GetVxDevice();
		void SetVxDevice( BOOL bVal );

		void LoadPropertyList(  );
		void RetrieveNode(GenApi::INode* pNode);

		void SetImage( OBJECT_INFO* pObjectInfo, IMAGE_INFO* pImageInfo );
		static void EventControlCallback(char* pcaEventName, VwGenICam::EVENT_DATA* ptEventData);

	protected:
	#ifdef USE_TL_12
	#else
		BOOL LockCheckHeartBeatError();
		BOOL UnlockCheckHeartBeatError();
	#endif

	#ifdef USE_TL_12
		UINT ThrGrabContinuosOpt();
	#endif
		UINT ThrGrabContinuos();
		UINT ErrorCheckThread();
		UINT GeneralEventCheckThread();
		UINT GrabCallbackThread();
		static unsigned int WINAPI myGrabContinuosThread (LPVOID me); 
		static unsigned int WINAPI thCheckConnection (LPVOID me); 
		static unsigned int WINAPI ThrGrabCallbackThread (LPVOID me); 
		static unsigned int WINAPI thGeneralEventCallback (LPVOID me);

		DWORD StrIP2dwIP( char* strIPAddress );

	public:
		RESULT GetPixelFormatEntry( OUT list<std::string>* plstPixelFormat );
		RESULT ChangeBufferFormat( IN UINT nBufferNum, IN UINT nWidth, IN UINT nHeight, IN PIXEL_FORMAT pixelFormat );

	public:
		VwCamera(VwInterface* _pInterface, UINT _unFilterType);
		~VwCamera(void);

		RESULT GetVwInterface( OUT VwInterface** pVwInterface );

		RESULT GetDeviceHandle( OUT VwGenICam::DEV_HANDLE* pDevHandle );

		RESULT OpenCamera(char* name,UINT nNumBuffer,UINT nWidth, UINT nHeight, UINT nPacketSize, void* pUserPointer,
						  ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);
		RESULT CloseCamera();

		

		RESULT Snap(UINT nFrameCount);
		RESULT Grab();
		RESULT GetGrabData(IMAGE_INFO* pImageInfo);

		RESULT Abort();
		RESULT GetGrabCondition( BOOL& bIsGrabbing )		{	bIsGrabbing = m_bGrabRunning; return RESULT_SUCCESS; };

		RESULT GetWidth(UINT* pWidth);
		RESULT GetHeight(UINT* pHeight);
		RESULT SetWidth(UINT width);
		RESULT SetHeight(UINT height);

		RESULT SetPixelFormat(PIXEL_FORMAT format);
		RESULT GetPixelFormat( PIXEL_FORMAT* pPixelFormat );
		RESULT GetPixelFormatLineup( IN UINT nIndex, PIXEL_FORMAT* pPixelFormat );
		RESULT GetPixelFormatLineupNum( OUT UINT* pnIndex );

		RESULT SetPixelSize( UINT pnPixelSize );
		RESULT GetPixelSize( UINT* pnPixelSize );
		RESULT GetPixelSizeType( IN UINT nIndex, OUT UINT* pnPixelSize );
		RESULT GetPixelSizeTypeNum( OUT UINT* pnNum );

		RESULT SetTriggerMode( BOOL bTriggerMode );
		RESULT GetTriggerMode( BOOL* pbTriggerMode );
		RESULT GetTriggerModeLineup( IN UINT nIndex, OUT UINT* unValue );
		RESULT GetTriggerModeLineupNum( OUT UINT* pnIndex );

		RESULT GetTriggerSource( TRIGGER_SOURCE* pTriggerSoruce );
		RESULT GetTriggerSourceLineup( IN UINT nIndex, OUT TRIGGER_SOURCE* pTriggerSoruce );
		RESULT GetTriggerSourceLineupNum( OUT UINT* pnIndex );

		RESULT SetBinningHorizontal( UINT pnBinningHorizontal );
		RESULT GetBinningHorizontal( UINT* pnBinningHorizontal );
		RESULT GetBinningHorizontalLineup( IN UINT nIndex, OUT UINT* unValue );
		RESULT GetBinningHorizontalLineupNum( OUT UINT* pnIndex );

		RESULT SetBinningVertical( UINT pnBinningVertical );
		RESULT GetBinningVertical( UINT* pnBinningVertical );
		RESULT GetBinningVerticalLineup( IN UINT nIndex, OUT UINT* unValue );
		RESULT GetBinningVerticalLineupNum( OUT UINT* pnIndex );

		RESULT GetBinningFactor( UINT* pnFactor );
		RESULT SetBinningFactor( UINT nFactor );

		RESULT SetTriggerSoftware();
		RESULT GetFrameCapacity( UINT* pnFrameCapacity );
	
		RESULT SetStreamHold( UINT pnStreamHold );
		RESULT GetStreamHold( UINT* pnStreamHold );

		RESULT SetSCPSPacketSize( UINT pnSCPSPacketSize );
		RESULT GetSCPSPacketSize( UINT* pnSCPSPacketSize );

		RESULT SetTestImage( TESTIMAGE aTestImage );
		RESULT GetTestImage( TESTIMAGE* pTestImage );
		RESULT GetTestImageLineup( IN UINT nIndex, OUT TESTIMAGE* pTestImage );
		RESULT GetTestImageLineupNum( OUT UINT* pnIndex );

		RESULT SetAcquisitionTimeOut( IN UINT nTimeOut );
		RESULT GetAcquisitionTimeOut( OUT UINT* pnTimeOut );

		RESULT GetDeviceModelName( IN int nIndex, OUT  char* pName, OUT size_t* pNameSize );
		RESULT GetDeviceVersion( IN int nIndex, char* pVersion, size_t* pVersionSize );
		RESULT GetDeviceVendorName( IN int nIndex, OUT char* pInfo, OUT size_t* pInfoSize );
		RESULT GetDeviceID( IN int nIndex, char* pInfo, size_t* pInfoSize );
		static RESULT GetDeviceIP( IN VwGenICam::DEV_HANDLE hCamera, OUT char* pInfo, OUT size_t* pInfoSize );
		RESULT GetDeviceIP( IN int nIndex, OUT char* pInfo, OUT size_t* pInfoSize );
		static RESULT GetDeviceMAC( IN VwGenICam::DEV_HANDLE hCamera, OUT char* pInfo, OUT size_t* pInfoSize );
		RESULT GetDeviceMAC( IN int nIndex, OUT char* pInfo, OUT size_t* pInfoSize );

		RESULT GetBufferInfo( OUT UINT& nBufferNum, OUT UINT& nWidth, OUT UINT& nHeight, OUT PIXEL_FORMAT& pixelFormat );

		RESULT GetStreamInfo( IN STREAM_INFO streamInfo, OUT UINT& nInfo );

		RESULT SetReadoutMode( READOUT aReadout );
		RESULT GetReadoutMode( READOUT* paReadout );
		RESULT SetHorizontalStart(UINT uStart);
		RESULT GetHorizontalStart(UINT* puStart);
		RESULT SetHorizontalEnd(UINT uEnd);
		RESULT GetHorizontalEnd(UINT* puEnd);
		RESULT SetVerticalStart(UINT uStart);
		RESULT GetVerticalStart(UINT* puStart);
		RESULT SetVerticalEnd(UINT uEnd);
		RESULT GetVerticalEnd(UINT* puEnd);

		RESULT SetTriggerSource(TRIGGER_SOURCE aSource);
		RESULT SetTriggerActivation(TRIGGER_ACTIVATION aActivation);
		RESULT GetExposureMode(EXPOSURE_MODE* paExpmode);
		RESULT SetExposureMode(EXPOSURE_MODE aExpmode);
		RESULT GetExposureTime(UINT* aExptime_microsec);
		RESULT SetExposureTime(UINT aExptime_microsec);
		RESULT GetGain(GAIN_SEL* aGainSel, float* fGainVal);
		RESULT SetGain(GAIN_SEL aGainSel, float fGainVal);
		RESULT SetBlackLevel(BLACKLEVEL_SEL blackLevelSel, UINT aBlacklevelVal);
		RESULT SetReverseX(BOOL aBSet);
		RESULT SetStrobeOffset(UINT aOffsetVal);
		RESULT SetStrobePolarity(STROBE_POLARITY aStrobePolarity);	

		RESULT GigEGetCurrentIpConfigurationDHCP( bool* pbSet );
		RESULT GigEGetCurrentIpConfigurationPersistentIP( bool* pbSet );
		RESULT GigEGetPersistentSubnetMask( UINT* pnSubnetMask );
		RESULT GigEGetCurrentMACAddress( char* pszMACAddress, size_t* pNameSize );

		RESULT GigESetCurrentIpConfigurationDHCP( bool bSet );
		RESULT GigESetCurrentIpConfigurationPersistentIP( bool bSet );

		RESULT GigEGetColorRGBGain( int nRGBType, double* dpGainValue );
		RESULT GigESetColorRGBGain( int nRGBType, double dGainValue );

		RESULT GigEGetTemperature( double* dpTemperature );
		RESULT GigEGetSerialNumber( char* capSerialNumber, size_t* cbpSerialNumberSize );
		RESULT GigEGetSerialNumber( char capSerialNumber[], size_t& cbpSerialNumberSize );
		RESULT ReadData( void *pBuffer, __int64 Address, __int64* Length );
		RESULT WriteData( void *pBuffer, __int64 Address, size_t* Length );

		void SetFilterType( UINT unFilterType );
		BOOL GetFilterType();

		RESULT InvalidateNodes();
		RESULT SetCustomCommand( IN char* pCommand, IN char* pArg, IN BOOL bSyncCMD = TRUE );
		RESULT GetCustomCommand( IN char* cpCommand, OUT char* cpArg, INOUT size_t* cbpArgSize, IN int nCmdType = GET_CUSTOM_COMMAND_VALUE );

		RESULT SetUARTCustomCommand( IN char* pCommand );
		RESULT GetUARTCustomCommand( IN char* pCommand, OUT char* pArg, IN size_t* pArgSize );

		RESULT GetHeartBeatTimeoutTryCount( OUT int& nCount );
		RESULT SetHeartBeatTimeoutTryCount( IN int nCount );

		RESULT InitEventControl();
		RESULT SetEventControlCallback( IN UINT unEventID, IN const char* pcaEventName, IN size_t szEventName, IN EventControlCallbackFn* pEventCallback, void* pUserPointer = NULL );

		RESULT GetPropertyCount(OUT int* pCount);
		RESULT GetPropertyInfo(IN int nIndex, OUT PROPERTY* pPropInfo);
		RESULT GetPropertyInfo(IN const char* cpCommand, OUT PROPERTY* pPropInfo);

		RESULT ReadFileStream( IN const char* cpFileName, OUT char* cpBuff, INOUT size_t& szBuff );
		RESULT WriteFileStream( IN const char* cpFileName, IN char* cpBuff, IN size_t szBuff );

		RESULT SetImageCallback( ImageCallbackFn* pImageCallbackFn );

		RESULT SetGeneralEventCallback( GeneralEventCallbackFn* pGeneralEventCallbackFn );
	
		RESULT GetFileAccessControlStatus( char* pStatus );

		RESULT GetPollingTime( GenApi::INode* pNode, __int64& nPollingTime );
		void ftoa( double dInput, char* chRet, int digit );

		RESULT GetNumCorruptedImage( UINT64& nCorruptImage );
		RESULT GetNumDeliveredFrame( UINT64& nFrameCount );
		RESULT GetNumLostImage( UINT64& nLostPacket );
		RESULT GetNumResendSuccessfulPackets( UINT64& nResendPacket );
		RESULT GetNumQueuedBuffer( UINT64& nQueuedBuffer );
		RESULT GetNumAnnouncedBuffer( UINT64& nAnnouncedBuffer );

		DWORD WaitGrabThread( UINT dwTimeOut );

		RESULT AcquisitionStop();

		RESULT AcquisitionModeOpt( BOOL bUse );
	
		RESULT UseIndependentCallback( BOOL bUse )	{	_bUseCallbackThread = bUse;		return RESULT_SUCCESS;	};

		BOOL IsValidEventType( UINT unEventType );

		RESULT SetClearBuffer( BOOL bOn );

		RESULT UseQueueManager( BOOL bUse )			{	_bUseQueueManager	=	bUse;	return RESULT_SUCCESS;	};

		RESULT SetCCPPrivilege( CCP_PRIVILEGE ePrivilege )	{	_eCCPPrivilege	=	ePrivilege;	return RESULT_SUCCESS;	};

		BOOL GetXML(void* hPort, char** pBuffer, size_t& cbBuffer, BOOL bIsDevice, BOOL& bZip);
	protected:
		void PrintBufferStateInWindowsEvent( UINT64& nPrevCorruptedImage, UINT64& nPrevResendPacket, UINT nBlockID );
		void ExecuteEventCallback( int nResultAll );
	};

}//namespace VWSDK


#endif
