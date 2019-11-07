/*******************************************************************************
Copyright (c) 1983-2016 Advantech Co., Ltd.
********************************************************************************
THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY INFORMATION
WHICH IS THE PROPERTY OF ADVANTECH CORP., ANY DISCLOSURE, USE, OR REPRODUCTION,
WITHOUT WRITTEN AUTHORIZATION FROM ADVANTECH CORP., IS STRICTLY PROHIBITED.

================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log:  $
--------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows Example:
*    InstantAI.cpp
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Instant AI function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define        deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32          startChannel = 0;
const int32    channelCount = 2;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 
int main(int argc, char* argv[])
{
   ErrorCode        ret = Success;

   // Step 1: Create a 'instantAiCtrl' for InstantAI function.
   InstantAiCtrl * instantAiCtrl = InstantAiCtrl::Create();

   do
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = instantAiCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = instantAiCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 3: Read samples and do post-process, we show data here.
      printf("Acquisition is in progress, any key to quit!\n\n");
      double scaledData[channelCount] = {0};//the count of elements in this array should not be less than the value of the variable channelCount
      int32 channelCountMax = instantAiCtrl->getFeatures()->getChannelCountMax();

      do
      {
         //read samples and save to buffer 'scaledData'.
         ret = instantAiCtrl->Read(startChannel, channelCount, scaledData);
         CHK_RESULT(ret);

         // process the acquired data. only show data here.
         for (int32 i = startChannel; i< startChannel+channelCount;++i)
         {
            printf("Channel %d data: %10.6f\n\n", i % channelCountMax, scaledData[i-startChannel]);
         }
         SLEEP(1);
      } while(!kbhit());
   }while(false);

	// Step 4 : Close device and release any allocated resource.
	instantAiCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
	if(BioFailed(ret))
	{
		printf("Some error occurred. And the last error code is 0x%X.\n", ret);
		waitAnyKey();// wait any key to quit!
	}
   return 0;
}



