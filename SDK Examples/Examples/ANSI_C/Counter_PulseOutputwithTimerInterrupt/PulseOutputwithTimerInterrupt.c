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
*    PulseOutputwithTimerInterrupt.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Pulse Output with Timer Interrupt function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*    5  set the 'frequency' to decide the frequency of pulse for selected channel.
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
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32 channelStart = 0;
int32 channelCount = 1;
double frequency = 10;

void waitAnyKey()
{
   do 
   {SLEEP(1);} while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   IArray * channels = 0;
   TmrChannel * tmrChannel = 0;
   CntrFeatures * cntrFeatures = 0;
   int index = 0;
	int channelCountMax = 0;

   // Step 1: Create a 'TimerPulseCtrl' for Pulse Output with Timer Interrupt function.
   TimerPulseCtrl * timerPulseCtrl = TimerPulseCtrl_Create();

   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode = ModeWrite;
      devInfo.ModuleIndex = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = TimerPulseCtrl_setSelectedDevice(timerPulseCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = TimerPulseCtrl_LoadProfile(timerPulseCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 3: Set necessary parameters.
      cntrFeatures = TimerPulseCtrl_getFeatures(timerPulseCtrl);
      channelCountMax = CntrFeatures_getChannelCountMax(cntrFeatures);    
      ret = TimerPulseCtrl_setChannelStart(timerPulseCtrl, channelStart);
      CHK_RESULT(ret);
      ret = TimerPulseCtrl_setChannelCount(timerPulseCtrl, channelCount);
      CHK_RESULT(ret);
      channels = TimerPulseCtrl_getChannels(timerPulseCtrl);
      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         tmrChannel = (TmrChannel *)Array_getItem(channels, index % channelCountMax);
         ret = TmrChannel_setFrequency(tmrChannel, frequency);
      }
      // Step 4: Start PulseOutputwithTimerInterrupt
      printf(" PulseOutputwithTimerInterrupt is in progress...\n Test signal to the Out pin !\n");
      printf(" Any key to quit !\n");
      ret = TimerPulseCtrl_setEnabled(timerPulseCtrl, TRUE);
      CHK_RESULT(ret);

      while (!kbhit())
      {
         SLEEP(1);
      }

      // Step 5: Stop PulseOutputwithTimerInterrupt
      ret = TimerPulseCtrl_setEnabled(timerPulseCtrl, FALSE);
      CHK_RESULT(ret);
   } while (FALSE);
   
   // Step 6: Close device and release any allocated resource.
   TimerPulseCtrl_Dispose(timerPulseCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }
   return 0;
}