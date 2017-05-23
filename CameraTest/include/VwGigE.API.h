
//#pragma once
#ifndef VWGIGE_API_H
#define VWGIGE_API_H

#define IN
#define OUT
#define INOUT

#include "VwGigE.Global.h"
#include <Windows.h>

#ifdef _USRDLL
#define FUNCTION_IMPORTEXPORT __declspec(dllexport)
#else if
#define FUNCTION_IMPORTEXPORT __declspec(dllimport)
#endif
 
#ifdef __cplusplus
extern "C"
{
#endif

namespace VWSDK
{

	typedef void* VWGIGE_HANDLE;
	typedef void* HINTERFACE;
	typedef void* HCAMERA;

	FUNCTION_IMPORTEXPORT RESULT OpenVwGigE(VWGIGE_HANDLE* hVwGigE);
	FUNCTION_IMPORTEXPORT RESULT CloseVwGigE(VWGIGE_HANDLE& hVwGigE);
	FUNCTION_IMPORTEXPORT RESULT VwGetNumInterfaces(VWGIGE_HANDLE hVwGigE, UINT* pNumInterfaces);
	FUNCTION_IMPORTEXPORT RESULT VwGetNumCameras(VWGIGE_HANDLE hVwGigE, UINT* aPNumCamera);
	FUNCTION_IMPORTEXPORT RESULT VwOpenCameraByIndex(VWGIGE_HANDLE hVwGigE, UINT nCameraIndex, HCAMERA* phCamera, UINT nNumBuffer, UINT nWidth, UINT nHeight,
		UINT nPacketSize, void* pUserPointer, ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);
	FUNCTION_IMPORTEXPORT RESULT VwOpenCameraByName(VWGIGE_HANDLE hVwGigE, char* pCameraName, HCAMERA* phCamera, UINT nNumBuffer, UINT nWidth, UINT nHeight,
		UINT nPacketSize, void* pUserPointer, ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);
	FUNCTION_IMPORTEXPORT RESULT VwOpenInterfaceByIndex(VWGIGE_HANDLE hVwGigE, UINT aNIndex, HINTERFACE* phInterface);
	FUNCTION_IMPORTEXPORT RESULT VwOpenInterfaceByName(VWGIGE_HANDLE hVwGigE, char* pInterfaceName, HINTERFACE* phInterface);
	
	


	FUNCTION_IMPORTEXPORT RESULT VwDiscovery(VWGIGE_HANDLE hVwGigE);

	FUNCTION_IMPORTEXPORT RESULT VwDiscoveryInterfaceInfo(VWGIGE_HANDLE hVwGigE,UINT nIndex,INTERFACE_INFO_STRUCT* pInterfaceInfoStruct);
	FUNCTION_IMPORTEXPORT RESULT VwDiscoveryCameraInfo(VWGIGE_HANDLE hVwGigE,UINT nIndex,CAMERA_INFO_STRUCT* pCameraInfoStruct);

	FUNCTION_IMPORTEXPORT RESULT VwForceIP(VWGIGE_HANDLE hVwGigE, PBYTE pMAC, DWORD nIP, DWORD nSubnet, DWORD nGateway);

	FUNCTION_IMPORTEXPORT RESULT VwUseMTUOptimize( IN VWGIGE_HANDLE hVwGigE, IN bool bUse );
	FUNCTION_IMPORTEXPORT RESULT VwSetMTUTimeout( IN VWGIGE_HANDLE hVwGigE, IN UINT uTimeout );
	FUNCTION_IMPORTEXPORT RESULT VwGetMTUTimeout( IN VWGIGE_HANDLE hVwGigE, OUT UINT& uTimeout );
	FUNCTION_IMPORTEXPORT RESULT VwSetGVCPTimeout( IN VWGIGE_HANDLE hVwGigE, IN UINT uTimeout );
	FUNCTION_IMPORTEXPORT RESULT VwGetGVCPTimeout( IN VWGIGE_HANDLE hVwGigE, OUT UINT& uTimeout );
	FUNCTION_IMPORTEXPORT RESULT VwSetMultiCastAddress( IN VWGIGE_HANDLE hVwGigE, IN DWORD dwMultiCastAddress );
	FUNCTION_IMPORTEXPORT RESULT VwGetMultiCastAddress( IN VWGIGE_HANDLE hVwGigE, OUT DWORD& dwMultiCastAddress );
	FUNCTION_IMPORTEXPORT RESULT VwSetIgnoreSubnet( IN VWGIGE_HANDLE hVwGigE, IN bool bUse );
	FUNCTION_IMPORTEXPORT RESULT VwGetIgnoreSubnet( IN VWGIGE_HANDLE hVwGigE, OUT bool& bUse );
	FUNCTION_IMPORTEXPORT RESULT VwSetDiscoveryTimeout( IN VWGIGE_HANDLE hVwGigE, IN UINT uTimeout );
	FUNCTION_IMPORTEXPORT RESULT VwGetDiscoveryTimeout( IN VWGIGE_HANDLE hVwGigE, OUT UINT& uTimeout );
	FUNCTION_IMPORTEXPORT RESULT VwSetCCPPrivilege( IN VWGIGE_HANDLE hVwGigE, IN CCP_PRIVILEGE eCCPPrivilige );
	
	FUNCTION_IMPORTEXPORT RESULT InterfaceOpenCameraByIndex(IN HINTERFACE hInstance,IN void* pCallbackParent,IN UINT nDevIndex,HCAMERA* phCamera, UINT nNumBuffer,
		UINT nWidth, UINT nHeight, UINT nPacketSize, ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);

	FUNCTION_IMPORTEXPORT RESULT InterfaceOpenCameraByName(HINTERFACE hInterface, void* pParent, char* pName,HCAMERA* phCamera, UINT nNumBuffer,
		UINT nWidth, UINT nHeight, UINT nPacketSize, ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);
	FUNCTION_IMPORTEXPORT RESULT InterfaceGetNumCameras(HINTERFACE hInterface, UINT* aPNumDevices);
	FUNCTION_IMPORTEXPORT RESULT InterfaceGetCameraName(HINTERFACE hInterface, UINT aNDevIndex, char* aName, size_t* aPNameSize);
	FUNCTION_IMPORTEXPORT RESULT InterfaceGetIPAddress(HINTERFACE hInterface, char* pszIPAddress, size_t* paIPAddress);
	FUNCTION_IMPORTEXPORT RESULT InterfaceGetSubnet(HINTERFACE hInterface, char* pszSubnet, size_t* paSubnet);
	FUNCTION_IMPORTEXPORT RESULT InterfaceUsePacketResend(IN HINTERFACE hInterface, IN BOOL bUse);
	FUNCTION_IMPORTEXPORT RESULT InterfaceUsePacketResendFrequently(IN HINTERFACE hInterface, IN BOOL bUse);
	FUNCTION_IMPORTEXPORT RESULT InterfaceUseLAGMode(IN HINTERFACE hInterface, IN BOOL bUse);
	FUNCTION_IMPORTEXPORT RESULT InterfaceGetImageReceivingTimeout( IN HINTERFACE hInterface, OUT UINT& unTimeout );
	FUNCTION_IMPORTEXPORT RESULT InterfaceSetImageReceivingTimeout( IN HINTERFACE hInterface, IN UINT unTimeout );
	FUNCTION_IMPORTEXPORT RESULT InterfaceGetImageRetransTimeout( IN HINTERFACE hInterface, OUT UINT& unTimeout );
	FUNCTION_IMPORTEXPORT RESULT InterfaceSetImageRetransTimeout( IN HINTERFACE hInterface, IN UINT unTimeout );


	FUNCTION_IMPORTEXPORT RESULT InterfaceCloseInterface(HINTERFACE hInterface);

	FUNCTION_IMPORTEXPORT RESULT InterfaceGetVwGigEHandle(IN HINTERFACE hInterface,OUT VWGIGE_HANDLE* phVwGigEHandle);

	FUNCTION_IMPORTEXPORT RESULT CameraClose(HCAMERA hCamera);
	FUNCTION_IMPORTEXPORT RESULT CameraGrab(HCAMERA hCamera);

	FUNCTION_IMPORTEXPORT RESULT CameraGetGrabData(IN HCAMERA hCamera, OUT IMAGE_INFO* pImageInfo );

	FUNCTION_IMPORTEXPORT RESULT CameraSnap(HCAMERA hCamera, UINT unFrame);
	FUNCTION_IMPORTEXPORT RESULT CameraAbort(HCAMERA hCamera);
	FUNCTION_IMPORTEXPORT RESULT CameraGetGrabCondition(HCAMERA hCamera, BOOL& bIsGrabbing);
	FUNCTION_IMPORTEXPORT RESULT CameraGetWidth(HCAMERA hCamera, UINT* punWidth);
	FUNCTION_IMPORTEXPORT RESULT CameraGetHeight(HCAMERA hCamera, UINT* punHeight);
	FUNCTION_IMPORTEXPORT RESULT CameraSetWidth(HCAMERA hCamera, UINT pnWidth);
	FUNCTION_IMPORTEXPORT RESULT CameraSetHeight(HCAMERA hCamera, UINT pnHeight);
	FUNCTION_IMPORTEXPORT RESULT CameraSetPixelFormat(HCAMERA hCamera, PIXEL_FORMAT pixelFormat);
	FUNCTION_IMPORTEXPORT RESULT CameraGetPixelFormat(HCAMERA hCamera, PIXEL_FORMAT* pPixelFormat);
	FUNCTION_IMPORTEXPORT RESULT CameraGetPixelFormatLineup(HCAMERA hCamera, UINT nIndex, PIXEL_FORMAT* pPixelFormat);
	FUNCTION_IMPORTEXPORT RESULT CameraGetPixelFormatLineupNum(HCAMERA hCamera, UINT* npNum);

	FUNCTION_IMPORTEXPORT RESULT CameraSetPixelSize(HCAMERA hCamera, UINT nPixelSize);
	FUNCTION_IMPORTEXPORT RESULT CameraGetPixelSize(HCAMERA hCamera, UINT* pnPixelSize);
	FUNCTION_IMPORTEXPORT RESULT CameraGetPixelSizeLineup(HCAMERA hCamera, UINT nIndex, UINT* pnPixelSize);
	FUNCTION_IMPORTEXPORT RESULT CameraGetPixelSizeLineupNum(HCAMERA hCamera, UINT* npNum);

	FUNCTION_IMPORTEXPORT RESULT CameraSetTriggerMode(IN HCAMERA hCamera, BOOL bSet);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTriggerMode(HCAMERA hCamera, BOOL* pbSet);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTriggerModeLineup(HCAMERA hCamera, UINT nIndex, UINT* nTriggerMode);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTriggerModeLineupNum(HCAMERA hCamera, UINT* npNum);

	FUNCTION_IMPORTEXPORT RESULT CameraSetTriggerSource(IN HCAMERA hCamera, IN TRIGGER_SOURCE triggerSource);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTriggerSource(IN HCAMERA hCamera, OUT TRIGGER_SOURCE* pTriggerSource);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTriggerSourceLineup(HCAMERA hCamera, UINT nIndex, TRIGGER_SOURCE* pTriggerSoruce);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTriggerSourceLineupNum(HCAMERA hCamera, UINT* npNum);

	FUNCTION_IMPORTEXPORT RESULT CameraSetBinningHorizontal(HCAMERA hCamera, UINT nBinningHorizontal);
	FUNCTION_IMPORTEXPORT RESULT CameraGetBinningHorizontal(HCAMERA hCamera, UINT* pnBinningHorizontal);
	FUNCTION_IMPORTEXPORT RESULT CameraGetBinningHorizontalLineup(HCAMERA hCamera, UINT nIndex, UINT* pnBinningHorizontal);
	FUNCTION_IMPORTEXPORT RESULT CameraGetBinningHorizontalLineupNum(HCAMERA hCamera, UINT* npNum);

	FUNCTION_IMPORTEXPORT RESULT CameraSetBinningVertical(HCAMERA hCamera, UINT nBinningVertical);
	FUNCTION_IMPORTEXPORT RESULT CameraGetBinningVertical(HCAMERA hCamera, UINT* nBinningVertical);
	FUNCTION_IMPORTEXPORT RESULT CameraGetBinningVerticalLineup(HCAMERA hCamera, UINT nIndex, UINT* nBinningVertical);
	FUNCTION_IMPORTEXPORT RESULT CameraGetBinningVerticalLineupNum(HCAMERA hCamera, UINT* npNum);

	FUNCTION_IMPORTEXPORT RESULT CameraGetBinningFactor( HCAMERA hCamera, UINT* pnFactor );
	FUNCTION_IMPORTEXPORT RESULT CameraSetBinningFactor( HCAMERA hCamera, UINT nFactor );

	FUNCTION_IMPORTEXPORT RESULT CameraSetHorizontalStart(HCAMERA hCamera, UINT uStart);
	FUNCTION_IMPORTEXPORT RESULT CameraGetHorizontalStart(HCAMERA hCamera, UINT* puStart);
	FUNCTION_IMPORTEXPORT RESULT CameraSetHorizontalEnd(HCAMERA hCamera, UINT uEnd);
	FUNCTION_IMPORTEXPORT RESULT CameraGetHorizontalEnd(HCAMERA hCamera, UINT* puEnd);
	FUNCTION_IMPORTEXPORT RESULT CameraSetVerticalStart(HCAMERA hCamera, UINT uStart);
	FUNCTION_IMPORTEXPORT RESULT CameraGetVerticalStart(HCAMERA hCamera, UINT* puStart);
	FUNCTION_IMPORTEXPORT RESULT CameraSetVerticalEnd(HCAMERA hCamera, UINT uEnd);
	FUNCTION_IMPORTEXPORT RESULT CameraGetVerticalEnd(HCAMERA hCamera, UINT* puEnd);

	FUNCTION_IMPORTEXPORT RESULT CameraGetFrameCapacity(HCAMERA hCamera, UINT* nFrameCapacity);

	FUNCTION_IMPORTEXPORT RESULT CameraSetStreamHold(HCAMERA hCamera, UINT nStreamHold);
	FUNCTION_IMPORTEXPORT RESULT CameraGetStreamHold(HCAMERA hCamera, UINT* nStreamHold);

	FUNCTION_IMPORTEXPORT RESULT CameraSetSCPSPacketSize(HCAMERA hCamera, UINT nSCPSPacketSize);
	FUNCTION_IMPORTEXPORT RESULT CameraGetSCPSPacketSize(HCAMERA hCamera, UINT* nSCPSPacketSize);

	FUNCTION_IMPORTEXPORT RESULT CameraSetTestImage(HCAMERA hCamera, TESTIMAGE aTestImage);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTestImage(HCAMERA hCamera, TESTIMAGE* pTestImage);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTestImageLineup(HCAMERA hCamera, UINT nIndex, TESTIMAGE* pTestImage);
	FUNCTION_IMPORTEXPORT RESULT CameraGetTestImageLineupNum(HCAMERA hCamera, UINT* npNum);

	FUNCTION_IMPORTEXPORT RESULT CameraSetAcquisitionTimeOut(HCAMERA hCamera, UINT nTimeOut);
	FUNCTION_IMPORTEXPORT RESULT CameraGetAcquisitionTimeOut(HCAMERA hCamera, UINT* pnTimeOut);

	FUNCTION_IMPORTEXPORT RESULT CameraSetReadoutMode(HCAMERA hCamera, READOUT aReadout);
	FUNCTION_IMPORTEXPORT RESULT CameraGetDeviceModelName(IN HCAMERA hCamera, IN int nIndex, OUT char* pInfo, INOUT size_t* pInfoSize);
	FUNCTION_IMPORTEXPORT RESULT CameraGetDeviceVersion(IN HCAMERA hCamera, IN int nIndex, OUT char* pInfo, INOUT size_t* pInfoSize);
	FUNCTION_IMPORTEXPORT RESULT CameraGetDeviceVendorName(IN HCAMERA hCamera, IN int nIndex, OUT char* pInfo, INOUT size_t* pInfoSize);
	FUNCTION_IMPORTEXPORT RESULT CameraGetDeviceID(IN HCAMERA hCamera, IN int nIndex, OUT char* pInfo, INOUT size_t* pInfoSize);
	FUNCTION_IMPORTEXPORT RESULT CameraSetTriggerMode(IN HCAMERA hCamera, BOOL bSet);
	FUNCTION_IMPORTEXPORT RESULT CameraSetTriggerSource(IN HCAMERA hCamera, IN TRIGGER_SOURCE triggerSource);
	FUNCTION_IMPORTEXPORT RESULT CameraSetTriggerActivation(IN HCAMERA hCamera, IN TRIGGER_ACTIVATION triggerActivation);
	FUNCTION_IMPORTEXPORT RESULT CameraSetTriggerSoftware(IN HCAMERA hCamera);
	FUNCTION_IMPORTEXPORT RESULT CameraGetExposureMode(IN HCAMERA hCamera, OUT EXPOSURE_MODE* pexpMode);
	FUNCTION_IMPORTEXPORT RESULT CameraSetExposureMode(IN HCAMERA hCamera, EXPOSURE_MODE aExpmode);
	FUNCTION_IMPORTEXPORT RESULT CameraGetExposureTime(IN HCAMERA hCamera, UINT* paExptime_microsec);
	FUNCTION_IMPORTEXPORT RESULT CameraSetExposureTime(IN HCAMERA hCamera, UINT aExptime_microsec);
	FUNCTION_IMPORTEXPORT RESULT CameraGetGain(IN HCAMERA hCamera, GAIN_SEL* pgainSel, float* pfGainValue);
	FUNCTION_IMPORTEXPORT RESULT CameraSetGain(IN HCAMERA hCamera, GAIN_SEL pgainSel, float fGainValue);
	FUNCTION_IMPORTEXPORT RESULT CameraSetBlackLevel(IN HCAMERA hCamera, BLACKLEVEL_SEL blackLevelSel, UINT aBlacklevelVal);
	FUNCTION_IMPORTEXPORT RESULT CameraSetReverseX(IN HCAMERA hCamera, BOOL aBSet);
	FUNCTION_IMPORTEXPORT RESULT CameraSetStrobeOffset(IN HCAMERA hCamera, UINT nOffset);
	FUNCTION_IMPORTEXPORT RESULT CameraSetStrobePolarity(IN HCAMERA hCamera, STROBE_POLARITY aStrobePolarity);	

	FUNCTION_IMPORTEXPORT RESULT CameraChangeBufferFormat( HCAMERA hCamera, UINT nBufferNum, UINT nWidth, UINT nHeight, PIXEL_FORMAT pixelFormat );
	FUNCTION_IMPORTEXPORT RESULT CameraGetBufferInfo( IN HCAMERA hCamera, OUT UINT& nBufferNum, OUT UINT& nWidth, OUT UINT& nHeight, OUT PIXEL_FORMAT& pixelFormat );
	FUNCTION_IMPORTEXPORT RESULT CameraGetInterfaceHandle(IN HCAMERA hCamera,OUT HINTERFACE* phInterface);

	FUNCTION_IMPORTEXPORT RESULT CameraGigESetCurrentIpConfigurationDHCP(IN HCAMERA hCamera, bool bSet );
	FUNCTION_IMPORTEXPORT RESULT CameraGigESetCurrentIpConfigurationPersistentIP( IN HCAMERA hCamera, bool bSet );

	FUNCTION_IMPORTEXPORT RESULT CameraGigEGetCurrentIpConfigurationDHCP( IN HCAMERA hCamera, bool* pbSet );
	FUNCTION_IMPORTEXPORT RESULT CameraGigEGetCurrentIpConfigurationPersistentIP( IN HCAMERA hCamera, bool* pbSet );

	FUNCTION_IMPORTEXPORT RESULT CameraGigEGetPersistentSubnetMask( IN HCAMERA hCamera, OUT UINT* pnSubnetMask );
	FUNCTION_IMPORTEXPORT RESULT CameraGigEGetCurrentMACAddress( IN HCAMERA hCamera, IN size_t* pNameSize, OUT char* pszMACAddress );

	FUNCTION_IMPORTEXPORT RESULT CameraGigEGetColorRGBGain( IN HCAMERA hCamera, IN int nRGBType, OUT double* dpRGBGainValue );
	FUNCTION_IMPORTEXPORT RESULT CameraGigESetColorRGBGain( IN HCAMERA hCamera, IN int nRGBType, IN double dRGBGainValue );

	FUNCTION_IMPORTEXPORT RESULT CameraGetStreamInfo( IN HCAMERA hCamera, IN STREAM_INFO streamInfo, OUT UINT& nInfo );

	FUNCTION_IMPORTEXPORT RESULT CameraGigEGetTemperature( IN HCAMERA hCamera, OUT double* dpTemperature );
	FUNCTION_IMPORTEXPORT RESULT CameraGigEGetSerialNumber( IN HCAMERA hCamera, char capSerialNumber[], size_t& cbpSerialNumberSize );
	 
	FUNCTION_IMPORTEXPORT RESULT CameraSetCustomCommand( IN HCAMERA hCamera, IN char* pCommand, IN char* pArg, IN BOOL bSyncCMD = TRUE );
	FUNCTION_IMPORTEXPORT RESULT CameraGetCustomCommand( IN HCAMERA hCamera, IN char* pCommand, OUT char* pArg, INOUT size_t* pArgSize, IN int nCmdType = GET_CUSTOM_COMMAND_VALUE );

	FUNCTION_IMPORTEXPORT RESULT CameraGetPropertyCount( IN HCAMERA hCamera, OUT int* pnCount );
	FUNCTION_IMPORTEXPORT RESULT CameraGetPropertyInfo( IN HCAMERA hCamera, IN const char* cpCommand, OUT PROPERTY* ptPropInfo );
	FUNCTION_IMPORTEXPORT RESULT CameraGetPropertyInfoUsingIndex( IN HCAMERA hCamera, IN int nIndex, OUT PROPERTY* ptPropInfo );

	FUNCTION_IMPORTEXPORT RESULT CameraSetUARTCustomCommand( IN HCAMERA hCamera, IN char* pCommand );
	FUNCTION_IMPORTEXPORT RESULT CameraGetUARTCustomCommand( IN HCAMERA hCamera, IN char* pCommand, OUT char* pArg, IN size_t* pArgSize );

	FUNCTION_IMPORTEXPORT RESULT CameraReadData( IN HCAMERA hCamera, void *pBuffer, __int64 Address, __int64* Length );
	FUNCTION_IMPORTEXPORT RESULT CameraWriteData( IN HCAMERA hCamera, void *pBuffer, __int64 Address, size_t* Length );

	FUNCTION_IMPORTEXPORT RESULT CameraSetHeartBeatTimeoutTryCount( IN HCAMERA hCamera, IN int nCount );
	FUNCTION_IMPORTEXPORT RESULT CameraGetHeartBeatTimeoutTryCount( IN HCAMERA hCamera, OUT int& nCount );

	FUNCTION_IMPORTEXPORT RESULT CameraSetEventControl( IN HCAMERA hCamera, IN UINT unEventID, IN const char* pcaEventName, IN size_t szEventName, EventControlCallbackFn* pEventCallback );
	FUNCTION_IMPORTEXPORT RESULT CameraUseIndependentCallback( IN HCAMERA hCamera, IN BOOL bUse );
	FUNCTION_IMPORTEXPORT RESULT CameraSetImageCallback( IN HCAMERA hCamera, IN ImageCallbackFn* pImageCallbackFn );

	FUNCTION_IMPORTEXPORT RESULT CameraReadFileStream( IN HCAMERA hCamera, IN const char* cpFileName, OUT char* cpBuff, INOUT size_t& szBuff  );
	FUNCTION_IMPORTEXPORT RESULT CameraWriteFileStream( IN HCAMERA hCamera, IN const char* cpFileName, IN char* cpBuff, IN size_t szBuff );
	


	void Convert8a_4b_4a_8bTo16_16_MMX_I(BYTE* Src,WORD* Dest,int LenSrcBytes);
	FUNCTION_IMPORTEXPORT void ConvertYUV422_UYVYtoBGR8( const BYTE* pbSrc,  const unsigned int nWidth, const unsigned int nHeight, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertYUV422_YUYVtoBGR8( const BYTE* pbSrc, const unsigned int nWidth, const unsigned int nHeight, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertYUV422toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertYUV422toBGR8Interlaced( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst, bool bOdd, DWORD width, bool blend, bool _signed );
	FUNCTION_IMPORTEXPORT void ConvertYUV422PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertYUV411toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertYUV411PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertRGB12PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertRGB8toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertBGR10V2PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertYUV444toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertMonoPackedToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertMono16PackedToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertBAYGB8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYRG8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGR8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGB10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYRG10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGR10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGB12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYRG12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGR12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGB10ToBGR10(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYRG10ToBGR10(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGR10ToBGR10(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGB12ToBGR12(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYRG12ToBGR12(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertBAYGR12ToBGR12(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
	FUNCTION_IMPORTEXPORT void ConvertMono10PackedToMono16bit( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertMono12PackedToMono16bit( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertMono10ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertMono12ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	FUNCTION_IMPORTEXPORT void ConvertMono14ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );

}//namespace VWSDK

#ifdef __cplusplus
}
#endif

#endif
