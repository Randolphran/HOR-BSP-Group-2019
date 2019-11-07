/*******************************************************************************
Copyright (c) 1983-2016 Advantech Co., Ltd.
********************************************************************************
THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY INFORMATION
WHICH IS THE PROPERTY OF ADVANTECH CORP., ANY DISCLOSURE, USE, OR REPRODUCTION,
WITHOUT WRITTEN AUTHORIZATION FROM ADVANTECH CORP., IS STRICTLY PROHIBITED. 
================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log: $
 --------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows  Example:
*    PWMOutput.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use PWM Output function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*    5  set the 'pulseWidth' to decide the period of pulse for selected channel.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define     deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32 channelStart = 0;
int32 channelCount = 1;
PulseWidth pulseWidth = {0.08,0.02};

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   IArray * channels = 0;
   PoChannel * poChannel = 0;
   CntrFeatures * cntrFeatures = 0;
   int index = 0;
	int32 channelCountMax = 0;

   // Step 1: Create a 'PwModulatorCtrl' for PWMOutput function.
   PwModulatorCtrl * pwMoulatorCtrl = PwModulatorCtrl_Create();

   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can ully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode = ModeWrite;
      devInfo.ModuleIndex = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = PwModulatorCtrl_setSelectedDevice(pwMoulatorCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = PwModulatorCtrl_LoadProfile(pwMoulatorCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);
      
      // Step 3: Set necessary parameters.
      cntrFeatures = PwModulatorCtrl_getFeatures(pwMoulatorCtrl);
      channelCountMax = CntrFeatures_getChannelCountMax(cntrFeatures);
      ret = PwModulatorCtrl_setChannelStart(pwMoulatorCtrl, channelStart);
      CHK_RESULT(ret);
      ret = PwModulatorCtrl_setChannelCount(pwMoulatorCtrl, channelCount);
      CHK_RESULT(ret);
      ret = PwModulatorCtrl_setPulseWidth(pwMoulatorCtrl, &pulseWidth);
      CHK_RESULT(ret);
      channels = PwModulatorCtrl_getChannels(pwMoulatorCtrl);
      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         poChannel = (PoChannel *)Array_getItem(channels, index % channelCountMax);
         ret = PoChannel_setPulseWidth(poChannel, &pulseWidth); 
      }
      
      // Step 4: start PWMOutput
      printf(" PWMOutput is in progress...\n test signal to the Out pin !\n");
      printf(" any key to quit !\n");

      // Step 5: Stop PWMOutput
      ret = PwModulatorCtrl_setEnabled(pwMoulatorCtrl, TRUE);
      CHK_RESULT(ret);
      while (!kbhit())
      {
         SLEEP(1);
      }
      PwModulatorCtrl_setEnabled(pwMoulatorCtrl, FALSE);
   } while (FALSE);

   //Step 6: Close device and release any allocated resource.
   PwModulatorCtrl_Dispose(pwMoulatorCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf(" Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }
   return 0;


}