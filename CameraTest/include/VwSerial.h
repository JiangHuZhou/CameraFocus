#pragma once

// FILE //////////////////////////////////////////////////////////////////////
// 1. NAME		  : CVWGigESerial class
// 2. Desc.		  : User can control camera gain,exposure time,offset and so on using this class.
// 3. Ver.		  : 1.4
// 4. Date		  : 20110623
// 5. Design	  : Dave Park
// 6. Rev. History
//    1) 1.0 - 20100617 - First Release
//	  2) 1.1 - 20100715 - Error code was changed.
//	  3) 1.3 - 20100826 - Multi Byte , Unicode division
//	  4) 1.3 - 20100826 - Add WriteDataInner , ReadDataInner Function.
//						  Change return type
//    5) 1.4 - 20110623 - Modify Readdata , ReadDataInner function.
//////////////////////////////////////////////////////////////////////////////

#ifndef VWSERIAL_H
#define VWSERIAL_H

#include "VwGigE.Global.h"
#include "VwSerial.h"
#include "tchar.h"


#ifdef _USRDLL
#define CLASS_IMPORTEXPORT __declspec(dllexport)
#else if
#define CLASS_IMPORTEXPORT __declspec(dllimport)
#endif

namespace VWSDK
{

	//+++++++++++++++++++++++++++++++++++++++++++++++
	// class VwSerial
	//+++++++++++++++++++++++++++++++++++++++++++++++
	class CLASS_IMPORTEXPORT VwSerial
	{
	public:
		VwSerial(void);
		~VwSerial(void);

	private:
		void*					m_hGigECam;
		RESULT					m_errorcode;

	private:
		int			   clSerialRead				(CHAR    *buffer,				VwGenICam::uint64_t* bufferSize        );
		int			   clSerialWrite			(CHAR    *buffer,				VwGenICam::uint64_t* bufferSize        );
		int			   Align32					(VwGenICam::uint32_t param,     VwGenICam::uint32_t alignment, bool up );
		int			   WriteDataInner			(CHAR    *data							         );
		int			   ReadDataInner			(CHAR    *data,      int buffersize   		     );

	public:
		/************************************ User API ************************************/
		void		SetCamHandle(void* vphCam);
		void*		GetCamHandle(void);
		int			WriteData(char* cpData);
		int			ReadData(char* cpData, int nBufSize);
		RESULT	GetLastErrorCode(void);


		//Send software trigger command to camera 
		//Duration - us
		BOOL		   Send_GTrigger			(int  duration   ); 

		//Format:
		//grm 
		//Response:
		//<0|1|2>
		//Example: 
		//[Command] grm   
		//[Response] 2       : The Readout mode of the camera is currently set as the Binning mode.
		//Description:
		//Reads the currently set Readout mode value.
		//Format:
		//grm 
		//Response:
		//<0|1|2>
		//Example: 
		//[Command] grm   
		//[Response] 2       : The Readout mode of the camera is currently set as the Binning mode.
		//Description:
		//Reads the currently set Readout mode value.
		BOOL		   GetReadoutMode			(int *mode		 ); 

		//Format :
		//srm <0|1|2>
		//Parameter 1:
		//0                                 : Normal Mode.
		//1                                 : AOI (Area Of Interest) Mode.
		//2                                 : Binning (2 or 4) Mode.
		//Example:
		//srm 1     : Sets the Readout mode to AOI Mode
		//Description:
		//Sets the Readout mode value.  The horizontal and vertical spaces in the AOI mode are set using the “sha” and “sva” commands respectively.
		//(Refer to 4.2 Area Of Interest) In the Binning mode, the Binning Factor is set with the “sbf” command. (Refer to 4.3.1 Set Binning Factor)
		BOOL		   SetReadoutMode			(int  mode		 ); 

		//Format:
		//gha
		//Response:
		//<h1> <h2>
		//Example:
		//[Command] gha
		//[Response] 200 800                : The horizontal AOI Space of the camera is set between 200 and 800.
		//Description:
		//Reads the AOI horizontal range currently set in the camera.
		BOOL		   GetHorizontalArea		(int *start_point,  int *end_point);

		//Format:
		//sha <h1> <h2>
		//Parameter 1:
		//h1                              : Start point of the horizontal direction
		//Parameter 2:
		//h2                              : End point of the horizontal direction
		//Example:
		//sha 500 1500          : Sets the range of the horizontal direction of the image between 500 and 1500.
		//Description:
		//The horizontal length of the image is h2 ? h1 + 1. Please refer to Tabel 2.2 for the possible range determination. 
		BOOL		   SetHorizontalArea		(int  start_point,  int  end_point);

		//Format:
		//gva
		//Response:
		//<v1> <v2>
		//Example:
		//[Command] gva
		//[Response] 200 800                : The vertical AOI Space of the camera is set between 200 and 800.
		//Description:
		//Reads the AOI vertical range currently set in the camera.
		BOOL		   GetVerticalArea			(int *start_point,  int *end_point);

		//Format:
		//sha <v1> <v2>
		//Parameter 1:
		//v1 : Start point of the vertical direction
		//Parameter 2:
		//h2 : End point of the vertical direction
		//Example:
		//sva 500 1500          : Sets the vertical direction range of the image between 500 and 1500.
		//Description:
		//The length of the displayed vertical direction is v2 ? v1 + 1. Please refer to each camera model for the possible range determination. 
		BOOL		   SetVerticalArea			(int  start_point,  int  end_point);
	
		//Format:
		//gbf
		//Response:
		//<2|4>
		//Example:
		//[Command] gbf
		//[Response] 2           : The Binning Factor of the camera is set as 2.
		//Description:
		//Reads the Binning Factor currently set in the camera.
		BOOL		   GetBinningFactor			(int *factor);

		//Format:
		//sbf <2|4>
		//Parameter 1 :
		//2                                : 2 by 2 binning
		//4                                : 4 by 4 binning
		//Example:
		//sbf 2                         : Sets the Binning Factor of the camera as 2.
		//Description:
		//Sets the Binning Factor when the camera operates in the Binning mode. 
		BOOL		   SetBinningFactor			(int  factor);

		//Format:
		//gec
		//Response:
		//<0|1>                         : Reads the activation status of the exposure control function.
		//Example:
		//[Command] gec
		//[Response] 0            : The exposure control function is deactivated.
		BOOL		   GetExposureControl		(int *activation);

		//Format:
		//sec <0|1>
		//Parameter 1:
		//0                                 : Activates the exposure control function.
		//1                                 : Deactivates the exposure control function.
		//Example:
		//sec 1                          : Activates the exposure control function.
		//Description:
		//When the camera is operating under the Free-Run mode, it determines the use of the exposure control function.
		//When it determines not to use the exposure control function, the exposure time is identical to the readout time of a frame.
		//In case of using the exposure control function, a desired exposure time can be set using the “set” command.
		BOOL		   SetExposureControl		(int  activation);

		//Format:
		//get
		//Response:
		//<t>                             : Reads the exposure time value currently set under the Free-Run mode.
		//Example:
		//[Command] get
		//[Response] 1000    : The set exposure time of the camera is 1000 us.
		BOOL		   GetExposureTime			(int *time);

		//Format:
		//set <t>
		//Parameter 1:
		//t                                 : The minimum value that can be set varies slightly depending on camera model. The maximum value is usually 7 s.
		//                                    The time is set by an increment of 10 us. For example, a time value of 23173 actually applies 23170 us.
		//Example:
		//set 1052  : Sets the exposure time to 1050 us.
		BOOL		   SetExposureTime			(int  time);

		//Format:
		//gcm
		//Response:
		//<1|2>
		//Example:
		//[Command] gcm
		//[Response] 2        : Set as dual channel output.
		//Description:
		//Reads the Channel Mode value currently set in the camera.
		BOOL		   GetChannelMode			(int *mode); 

		//Format: 
		//scm <1|2>
		//Parameter 1:
		//1                                : Single Channel
		//2                                : Dual Channel
		//Example:
		//scm 2                        : Sets as the dual channel output.
		//Description:
		//Image data from the CCD can be read through a single or double channel.
		//When the dual channel is selected, the frame rate is about twice that of the single channel.
		BOOL		   SetChannelMode			(int  mode);

		//Format:
		//stm <0|1|2|3>
		//Parameter 1:
		//0                                : Free-Run Mode
		//1                                : Standard Mode
		//2                                 : Fast Mode
		//3                                 : Double Exposure Mode
		//4                                 : Overlap Trigger Mode
		//Example:
		//stm 1                        : Sets the Trigger mode as Standard mode.
		//Description:
		//Sets the detailed mode of the Trigger mode.
		BOOL		   SetTriggerMode			(int  mode);

		//Format:
		//gtm
		//Response:
		//<0|1|2|3>
		//Example:
		//[Command] gtm
		//[Response] 2           : The Trigger mode is set as the Fast mode.
		//Description:
		//Reads the detailed mode of the Trigger mode currently set in the camera.
		BOOL		   GetTriggerMode			(int *mode); 

		//Format:
		//sts <1|2>
		//Parameter 1:
		//1                                : CameraLink CC1 
		//2                                : External Trigger
		//Example:
		//sts 1                          : Uses the CC1 of the CameraLink as the Trigger input source.
		//Description:
		//Selects a subject for trigger input. The CC1 terminal of the CameraLink connector or the TRIGGER_IN terminal of the power connector can be used as an input.
		BOOL		   SetTriggerSource			(int  mode);

		//Format:
		//gts
		//Response:
		//<1|2>
		//Example:
		//[Command] gts
		//[Response] 1           : The CC1 of the CameraLink is set as the trigger input source.
		//Description:
		//Reads the Trigger Source value currently set in the camera.
		BOOL		   GetTriggerSource			(int *mode); 

		//Format:
		//sfn <n>
		//Parameter 1:
		//n                                 : 0 or 1 to 255 frames can be selected.
		//Example:
		//sfn 5                          : Receives 5 images upon trigger input.
		//Description:
		//This sets the operating condition of the camera after the trigger input under the Standard Trigger mode.
		//If the frame number is set to‘0,’ the camera is synchronized upon trigger input and retrieves one image and then runs under the Free-Run mode.
		//If the frame number is set to ‘1,’ although the camera is synchronized upon trigger input and only retrieves one image,
		//it does not run under the Free-Run mode but waits for the next trigger input.
		//In addition, if the frame number is set to any number between 2 and 255 as ‘n,’ only one image is retrieved,
		//and then retrieves ‘n-1’ images under the Free-Run mode and waits for the next trigger input.
		BOOL		   SetFrameNumber			(int  number);

		//Format:
		//gfn
		//Response:
		//<n>
		//Example:
		//[Command] gfn
		//[Response] 0           : Synchronized with the trigger input, it retrieves one image and runs under the Free-Run mode.
		//Description:
		//Returns a value between 0 and 255, depending on the currently set value.
		BOOL		   GetFrameNumber			(int *number);

		//Format:
		//ses <0|1>
		//Parameter 1:
		//0                                 : The exposure time is controlled by the pre-input time value.
		//1                                : The exposure time is controlled by the pulse-width of the trigger input.
		//Example:
		//ses 0                          : Upon trigger input, only exposes for the duration same as the value set by the “ste” command.
		//Description:
		//When the Exposure Source is ‘0,’ sets a desired exposure time with the “ste” command. When the exposure source is ‘1,’
		//the pulse-width of the trigger input determine the exposure time.
		BOOL		   SetExposureSource		(int  source);

		//Format:
		//ges
		//Response:
		//<0|1>
		//Example:
		//[Command] ges
		//[Response] 0           : The factor determining the exposure time under the Trigger mode is pre-programmed values.
		//Description:
		//Reads the Exposure Source from the Trigger mode currently set in the camera.
		BOOL		   GetExposureSource		(int *source);

		//Format:
		//ste <t>
		//Parameter 1:
		//t                                 : Exposure Time
		//Example:
		//ste 1044                   : Sets the exposure time to 1040 us.
		//Description:
		//This command is used to set the desired time when the exposure time under the Trigger mode is pre-programmed.
		//The possible minimum exposure time is 10us and the maximum time is 2s.
		//The time is set by an increment of 10 us. For example, a time value of 1325 actually applies 1320 us.
		BOOL		   SetTriggerExposure		(int  time);

		//Format:
		//gte
		//Response:
		//<t>
		//Example:
		//[Command] get
		//[Response] 2000    : The programmed exposure time is 2000 us.
		//Description:
		//Reads the pre-programmed exposure time under the Trigger mode.
		BOOL		   GetTriggerExposure		(int *time);

		//Format:
		//stp <0|1>
		//Parameter 1:
		//0                                : Active Low
		//1                                : Active High
		//Example:
		//stp 1                          : Sets the polarity of the trigger as Active High.
		//Description:
		//Sets the polarity of the trigger input.
		BOOL		   SetTriggerPolarity		(int  polarity);

		//Format:
		//gtp
		//Response:
		//<0|1>
		//Example:
		//[Command] gtp
		//[Response] 1           : The polarity of the trigger is set as Active High.
		BOOL		   GetTriggerPolarity		(int *polarity);

		//Format:
		//sar <0|1>
		//Parameter 1:
		//0                                 : Deactivates the Async Reset.
		//1                                 : Activates the Async Reset.
		//Example:
		//sar 1                           : Activates the Async Reset.
		//Description:
		//Sets the On/Off status of the Asynchronous Reset function. 
		//Please refer to 2.4.4 Asynchronous Reset for the Asynchronous Reset function.
		BOOL		   SetAsyncReset			(int  activity);

		//Format:
		//gar
		//Response:
		//<0|1>
		//Example:
		//[Command] gar
		//[Response] 1                              : The Async Reset is activated.
		BOOL		   GetAsyncReset			(int *activity);

		//Format:
		//sag <0|1|2> <n>
		//Parameter 1:
		//0                                : Applies the input value to both channels.
		//1                                : Applies the input value to Channel 1.
		//2                                : Applies the input value to Channel 2.
		//Parameter 2:
		//n                                :  gain value. 0~1023
		//Example: 
		//sag 0  100              : Sets the gain register of both AFEs to 100. 
		//Description:
		//When n is '0,' the gain is 6 dB, and when n is ‘1023,' the gain is 40 dB. 
		//When n is increased by ‘1,’ the gain is also increased by 0.035 dB.
		BOOL		   SetAnalogGain			(int  channel,int  gain);

		//Format:
		//gag <0|1|2>
		//Parameter 1:
		//0                                : Reads the set values from both channels.
		//1                                : Reads the set values from Channel 1.
		//2                                : Reads the set values from Channel 2.
		//Response:
		//<n1> <n2>
		//Example:
		//[Command] gag 1
		//[Response] 100      : The gain register value of Channel 1 AFE is set to 100.
		//Description:
		//If Parameter 1 is 0, n1 and n2 are returned, 
		//which represents the gain value of Channel 1 and Channel 2, respectively.
		//When Parameter 1 is either 1 or 2, 
		//only one value is returned, which represents the gain value of the channel indicated by Parameter 1.
		BOOL		   GetAnalogGain			(int  channel,int *channel1,int *channel2);

		//Format: 
		//sao <0|1|2> <n> 
		//Parameter 1:
		//0                                : Applies the input value to both channels. 
		//1                                : Applies the input value to Channel 1.
		//2                                : Applies the input value to Channel 2.
		//Parameter 2:
		//n                                :  offset value. 0~255
		//Example: 
		//sao 0  100              : Sets the offset register of both AFEs to 100.
		BOOL		   SetAnalogOffset			(int  channel,int  offset);

		//Format:
		//gao <0|1|2>
		//Parameter 1:
		//0                                : Reads the set value from both channels.
		//1                                : Reads the set value from Channel 1.
		//2                                : Reads the set value from Channel 2.
		//Response:
		//<n1> <n2>
		//Example:
		//[Command] gao 1
		//[Response] 100      : The offset register value of Channel 1 AFE is set to 100.
		//Description:
		//If Parameter 1 is 0, n1 and n2 are returned, 
		//which represents the offset value of Channel 1 and Channel 2, respectively.
		//When Parameter 1 is either 1 or 2, 
		//only one value is returned, which represents the offset value of the channel indicated by Parameter 1.
		BOOL		   GetAnalogOffset			(int  channel,int *channel1,int *channel2);

		//Format: 
		//sdb <8|10|12>
		//Parameter 1:
		//8                               : 8 bit Output.
		//10                              : 10 bit Output.
		//12                              : 12 bit Output.
		//Example:
		//sdb 8                         : Sets the data output width of the camera to 8 bits.
		//Description:
		//Determines the output data width of the camera.
		BOOL		   SetDataBits				(int  bit);

		//Format:
		//gdb
		//Response:
		//<8|10|12>
		//Example:
		//[Command] gdb
		//[Response] 10         : The output data width of the camera is set as 10 bits.
		//Description:
		//Reads the output data width currently set in the camera.
		BOOL		   GetDataBits				(int *bit);

		//Format: 
		//sti <0|1|2|3> 
		//Parameter 1:
		//0                                : Test Image Off.
		//1                                : Test Image 1 Output.
		//2                                : Test Image 2 Output.
		//3                                : Test Image 3 Output.
		//Example:
		//sti 2                           : Outputs the Test Image 2 rather than the image obtained from the CCD.
		//Description:
		//Outputs the Test Image rather than the image obtained from the CCD.
		//There are three different Test Images. If 0 is selected, the original CCD image is the output.
		// If a number between 1 and 3 is selected, Test Image corresponding to each number is the output.
		BOOL		   SetTestImage				(int  image);

		//Format:
		//gti
		//Response:
		//<0|1|2|3>
		//Example:
		//[Command] gti
		//[Response] 3           : The camera is currently releasing Test Image 3 for output.
		//Description:
		//Reads the current Test Image setting of the camera.
		BOOL		   GetTestImage				(int *image);

		//Format: 
		//sdc
		//<0|1>
		//0                                : Deactivates the Defect Correction function.
		//1                                : Activates the Defect Correction function.
		//Example:
		//sdc 1                         : Activates the Defect Correction function.
		//Description:
		//Activates or deactivates the Defect Correction function. 
		//In order to utilize the Defect Correction function, a Defect map must be pre-stored within the camera.
		//The Defect Correction function is not applied in the Binning mode. 
		BOOL		   SetDefectCorrection		(int  activity);

		//Format:
		//gdc
		//Response:
		//<0|1>
		//Example:
		//[Command] gdc
		//[Response] 1           : The Defect Correction function of the camera is activated.
		//Description:
		//Reads the activation status of Defect Correction.
		BOOL		   GetDefectCorrection		(int *activity);

		//Format: 
		//sls <0|1|2>
		//Parameter 1:
		//0                                : Does not apply LUT.
		//1                                : Applies LUT 1.
		//2                                : Applies LUT 2.
		//Example:
		//sls 1                           : Applies LUT 1.
		//Description:
		//Sets the Look-UP Table of the camera. 
		//In order to utilize the LUT function, an LUT with the corresponding number must be stored in the camera in advance.
		BOOL		   SetLUTSelect				(int  mode);

		//Format:
		//gls
		//Response:
		//<0|1|2>
		//Example:
		//[Command] gls
		//[Response] 0           : LUT is deactivated.
		//Description:
		//Reads the LUT setting of the camera.
		BOOL		   GetLUTSelect				(int *mode);

		//Format:
		//gfd
		//Description:
		//Activates the Flat Field Generator. 
		//Generating Flat Field data requires several frames of images internally thus it takes several seconds until the “OK” response is retrieved.
		BOOL		   GenerateFlatFieldData	(void);

		//Format:
		//sfd
		//Description:
		//The Flat Field data generated through the “gfd” command is stored on the Frame Buffer, a volatile memory.
		//This erases the data when the camera is turned off. 
		//To avoid data loss, data must be stored onto the Flash, a non-volatile memory, using the “sfd” command.
		BOOL		   SaveFlatFieldData		(void);

		//Format:
		//lfd
		//Description:
		//This command is used to apply the Flat Field Correction function, 
		//by restoring the flat field data from the FLASH to the Frame Buffer.
		BOOL		   LoadFlatFieldData		(void);

		//Format:
		//sfi <n>
		//Parameter 1:
		//n                                 : 0 ~ 4. The utilized images are 2n frames.
		//Example:
		//sfi 3                            : Uses 8 images during the generation of Flat Field data.
		//Description:
		//Sets how many images should be averaged to generate Flat Field data.
		//The lesser the selected images are, 
		//the shorter it takes for the data generation. However, the accuracy of the data could be lowered relatively.
		BOOL		   SetFlatFieldIteration	(int  parameter);

		//Format:
		//gfi
		//Response:
		//<n>                            : 0 ~ 4
		//Example:
		//[Command] gfi
		//[Response] 2                              : Set to use 4 images when generating Flat Field data.
		//Description:
		//Reads the setting on the number of images required to generate Flat Field data.
		BOOL		   GetFlatFieldIteration	(int *parameter);

		//Format:
		//sfc <0|1>
		//Parameter 1:
		//0                                : Turns OFF the Flat Field Correction function.
		//1                                : Turns ON the Flat Field Correction function.
		//Example:
		//sfc 1                          : Turns ON the Flat Field Correction function of the camera.
		//Description:
		//Sets whether to utilize the Flat Field Correction function.
		BOOL		   SetFlatFieldCorrection	(int  on);

		//Format:
		//gfc
		//Response:
		//<0|1>
		//Example:
		//[Command] gfc
		//[Response] 1           : The Flat Field Correction function of the camera is activated.
		BOOL		   GetFlatFieldCorrecton	(int *on);

		//Format:
		//sfo m
		//Parameter 1:
		//m                               : Offset value of the corrected image
		//Example: 
		//sfo 1000                  : Sets the offset value of the Flat Field Correction to 1000.
		//Description:
		//Sets the offset value of the image after Flat Field Correction.
		//The offset values are based on the single channel under the Normal mode, 
		//thus the offset values of the actual image varies when the camera setting is changed.
		BOOL		   SetFlatFieldOffset		(int  offset);

		//Format:
		//gfo
		//Response
		//m
		//Example:
		//[Command] gfo
		//[Response] 1000     : The Flat field Offset value is set as 1000.
		BOOL		   GetFlatFieldOffset		(int *offset);

		//Format:
		//shf <0|1>
		//Parameter 1:
		//0                                : Deactivates the Horizontal Flip function.
		//1                                : Activates the Horizontal Flip function.
		//Example:
		//shf 1                         : Activates the Horizontal Flip function.
		//Description:
		//Sets whether to activate the Horizontal Flip function. 
		BOOL		   SetHorizontalFlip		(int  activity);

		//Format:
		//ghf
		//Response:
		//<0|1>
		//Example:
		//[Command] ghf
		//[Response] 1           : The Horizontal Flip function is activated.
		//Description:
		//Reads the setting of the Horizontal Flip function.
		BOOL		   GetHorizontalFlip		(int *activity);

		//Format: 
		//sii <0|1>
		//Parameter 1:
		//0                                : Deactivates the Image Invert function.
		//1                                : Activates the Image Invert function.
		//Example:
		//sii 1                           : Activates the Image Invert function.
		//Description:
		//Sets whether to activate the Image Invert function. 
		BOOL		   SetImageInvert			(int  activity);

		//Format:
		//gii
		//Response:
		//<0|1>
		//Example:
		//[Command] gii
		//[Response] 1           : The Image Invert function is activated.
		//Description:
		//Reads the setting of the Image Invert function.
		BOOL		   GetImageInvert			(int *activity);

		//Format:
		//sso <t>
		//Parameter 1:
		//t                                 : 0 or 10 ~ 10000. If 0, the strobe signal is not used. 
		//									  It can also be set between 10 us and 10 ms by an increment of 10 us. 
		//									  For example, if t is 103, the actually applied value is 100 us.
		//Example:
		//sso 123   : Sets the Strobe Offset value to 120 us.
		BOOL		   SetStrobeOffset			(int  offset);

		//Format:
		//gso
		//Response:
		//<t>
		//Example:
		//[Command] gso
		//[Response] 120      : The Strobe Offset value is set as 120 us.
		//Description: 
		//Reads the Strobe Offset value currently set in the camera.
		BOOL		   GetStrobeOffset			(int *offset);

		//Format:
		//ssp <0|1>
		//Parameter 1:
		//0                                 : Sets as Active-Low.
		//1                                 : Sets as Active-High.
		//Description:
		//Sets the polarity of the Strobe signal output.
		BOOL		   SetStrobePolarity		(int  activity);

		//Format:
		//gsp
		//Response:
		//<0|1>
		//Example:
		//[Command] gsp
		//[Response] 1           : The Strobe signal output is set as Active-High.
		//Description: 
		//Reads the polarity of the Strobe signal output set in the camera.
		BOOL		   GetStrobePolarity		(int *activity);

		//Format: 
		//sci <0|1|2>
		//Parameter 1:
		//0                                : Reads the set value stored in the Factory Space during the boot.
		//1                                : Reads the set value stored in the User Space 1 during the boot.
		//2                                : Reads the set value stored in the User Space 2 during the boot.
		//Example:
		//sci 2                          : Loads the set value of the User Space 2 to the Work Space during the boot.
		//Description:
		//When the camera is switched on, 
		//this command is used to determine which parameter value from which space will be applied. During the shipping process, 
		//it is required to apply the set value in the factory space.
		BOOL		   SetConfigInitialization	(int  mode);

		//Format:
		//gci
		//Response:
		//<0|1|2>
		//Example:
		//[Command] gci
		//[Response] 2           : It is required to apply the set value in the User Space 2 during the boot.
		//Description:
		//When the camera is switched on, 
		//this command is used to read the configuration initialization variable, 
		//indicating which set value to be used.
		BOOL		   GetConfigInitialization	(int *mode);

		//Format:
		//lcf <0|1|2>
		//Parameter 1:
		//0                                : Resets the camera with the set value stored in the Factory Space.
		//1                                : Resets the camera with the set value stored in the User Space 1.
		//2                                : Resets the camera with the set value stored in the User Space 2.
		//Example:
		//lcf 1                          : Resets the camera with the set value stored in the User Space 1.
		//lcf 
		//Description:
		//This command is used to reset the camera with the set value stored in an ad-hoc space while the camera is running without turning it off and on again. 
		//Although the “sci” command has the set value applied after the next boot, the “lcf” command has the set value applied immediately. 
		BOOL		   LoadConfigFrom			(int  mode);

		//Format: 
		//sct <0|1|2>
		//Parameter 1:
		//0                                : Stores the current set value into the Factory Space. The access to this space is restricted.
		//1                                : Stores the current set value into the User Space 1.
		//2                                : Stores the current set value into the User Space 2.
		//Example:
		//sct 1                          : Stores the current set value (existing in the work space) into the User Space 1.
		//Description:
		//This command is used to store the set values set in the work space to the parameter storage space to accommodate the convenience of users. 
		//Users can only store the values in either the User Space 1 or 2.
		BOOL		   SaveConfigTo				(int  mode);

		//Format: 
		//gct 
		//Response: 
		//<t>
		//Example:
		//[Command] gct
		//[Response] 45.35   : The current temperature of the camera is 45.35 ℃.
		//Description: 
		//Reads the current temperature of the camera. 
		//The temperature is presented in Celsius (℃) and is accurate down to 2 decimal places.
		TCHAR*		   GetCameraTemperature		(void);

		//Format: 
		//gmn
		//Description :
		//Reads the camera model information.
		TCHAR*		   GetCamModelNumber		(void);

		//Format:
		//gmv
		//Description :
		//Reads the firmware version information of MCU.
		TCHAR*		   GetMCUVersion			(void);

		//Format:
		//gfv
		//Description :
		//Reads the version information of the FPGA Logic.
		TCHAR*		   GetFPGAVersion			(void);
	};

}//namespace VWSDK

#endif