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
*    InstantAI.c
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
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define        deviceDescription  L"DemoDevice,BID#0"
#define        channelCount 2
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32          startChannel = 0;

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
}

int main(int argc, char* argv[])
{
   int32 i = 0;
   double scaledData[channelCount] = {0};
   int channelCountMax = 0; 
   ErrorCode  ret = Success;

   // Step 1: Create a 'instantAiCtrl' for InstantAI function.
   InstantAiCtrl * instantAiCtrl = InstantAiCtrl_Create();
   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = InstantAiCtrl_setSelectedDevice(instantAiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = InstantAiCtrl_LoadProfile(instantAiCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      printf("Acquisition is in progress, any key to quit!\n\n");
      channelCountMax = InstantAiCtrl_getChannelCount(instantAiCtrl);
      do 
      {
         //read samples and save to buffer 'scaledData'.
         ret = InstantAiCtrl_ReadAny(instantAiCtrl, startChannel, channelCount, 0, scaledData);
         CHK_RESULT(ret);
         
         // process the acquired data. only show data here.
         for (i = startChannel; i < startChannel + channelCount; ++i)
         {
            printf("Channel %d data: %10.6f\n\n", i % channelCountMax, scaledData[i-startChannel]);
         }
         SLEEP(1);
      } while (!kbhit());
   } while (FALSE);
   
   // Step 4 : Close device and release any allocated resource.
   InstantAiCtrl_Dispose(instantAiCtrl);
   
   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();// wait any key to quit!
   }
   return 0;
}