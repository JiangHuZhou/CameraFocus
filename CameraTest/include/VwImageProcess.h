//#pragma once

#ifndef VWIMAGEPROCESS_H
#define VWIMAGEPROCESS_H
#include <windows.h>


#ifdef _USRDLL
#define CLASS_IMPORTEXPORT __declspec(dllexport)
#else if
#define CLASS_IMPORTEXPORT __declspec(dllimport)
#endif

namespace VWSDK
{

	static BYTE Const1[16] = {0xf0,0x0f,0xff,0x0f,
	0xf0,0x0f,0xff,0x0f,
	0xf0,0x0f,0xff,0x0f,
	0xf0,0x0f,0xff,0x0f};

	static BYTE Const2[16] = {0, 0xf0,0, 0,   
	0, 0xf0,0, 0,
	0, 0xf0,0, 0,
	0, 0xf0,0, 0};


	class CLASS_IMPORTEXPORT VwImageProcess
	{
	public:
		VwImageProcess(void);
	public:
		~VwImageProcess(void);

		void Convert8a_4b_4a_8bTo16_16_MMX_I(BYTE* Src,WORD* Dest,int LenSrcBytes);
		static inline int Clip( int v )
		{
			if( DWORD(v) & 0x80000000 ) return 0;
			else if( DWORD(v) & 0xFFFFFF00  ) return 0xFF;
			else return v;
		}
		static void ConvertYUV422_UYVYtoBGR8( const BYTE* pbSrc,  const unsigned int nWidth, const unsigned int nHeight, BYTE* pbDst );
		static void ConvertYUV422_YUYVtoBGR8( const BYTE* pbSrc, const unsigned int nWidth, const unsigned int nHeight, BYTE* pbDst );
		static void ConvertYUV422toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertYUV422toBGR8Interlaced( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst, bool bOdd, DWORD width, bool blend, bool _signed );
		static void ConvertYUV422PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertYUV411toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertYUV411PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertRGB12PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertRGB8toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertBGR10V2PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertYUV444toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertMonoPackedToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	
		static void ConvertBAYGB8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGB10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGB12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGB10ToBGR10(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGB12ToBGR12(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);

		static void ConvertBAYRG8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYRG10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYRG12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYRG10ToBGR10(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
		static void ConvertBAYRG12ToBGR12(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);

		static void ConvertBAYGR8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGR10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGR12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGR10ToBGR10(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);
		static void ConvertBAYGR12ToBGR12(const WORD* pbSrc, WORD* pbDst, DWORD width, DWORD height);

		static void ConvertMono8ToBGR8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
		static void ConvertMono10PackedToMono8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertMono10PackedToMono16bit( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst );
		static void ConvertMono12PackedToMono16bit( const BYTE* pbSrc, UINT widht, UINT height, BYTE* pbDst );
		static void ConvertMono10ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertMono12ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertMono14ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
		static void ConvertMono16PackedToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	};

}//namespace VWSDK

#endif