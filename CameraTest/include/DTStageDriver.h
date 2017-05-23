////// Version 6.00.00		 2014-6-10 
//

//include <windef.h>
//#include <afx.h>
//#include <comdef.h>
///// ===== 宏定义 =====
//
	#define TEST_HANDSHACK		0
	#define TEST_STAGE_AREA		1
	#define TEST_FINGER_SWITCH	100

	#define QUIT_LV_SPEED		1000
	#define ENTER_LV1_SPEED		-1000


//#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
//DECLARE_HANDLE            (HWND);
//struct _HWND__ {int unused;};
//typedef struct _HWND__ *HWND;


///// ===== 功能函数 =====
//
extern"C" void DTMoveSteps(char chXYZ, int nSteps);
extern"C" void DTStop(char chX, char chY, char chZ);
extern"C" void DTSpeed(int nSpeed);
extern"C" int DTReadStatus(int nOption);
extern"C" void DTSetComm(int nComm);
extern"C" void DTLensWheel(int nLens);
extern"C" int DTInitStage(int nComm, unsigned long * phAppWnd);
extern"C" void DTMoveDistance(char chXY, double dDistance);
extern"C" void MoveStage(char chXYZ, int nDirection, unsigned int nSteps);
extern"C" void DTCloseComm();
extern"C" void DTFree(bool bFree);
extern"C" void DTBuzzing(int nBeep);
extern"C" void DTHomeLimit(char chXAxis, char chYAxis);
//extern"C" int DTHomeOrigin(CString* pszXOffset, CString* pszYOffset);
extern"C" int DTGetPulsesTotal(char chAxis);
extern"C" int DTGetPulses(char chAxis);
extern"C" int DTGetPosition();
extern"C" void DTClearPulses(char chAxis);
extern"C" long DTTestConnect(int n);
//extern"C" void DTTrigger( CString *pszEvent, int n=1);
//extern"C" BSTR DTGetInfo(CString* pszEvent);
