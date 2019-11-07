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
*    PulseOutputwithTimerInterrupt.cpp
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
#include <stdlib.h>
#include <stdio.h>
#include "../inc/compatibility.h"
#include "../../../inc/bdaqctrl.h"
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define     deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32       startChannel = 0;
int32       channelCount = 1;
double      frequency  = 10;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'TimerPulseCtrl' for Pulse Output with Timer Interrupt function.
   TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();

   do
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = timerPulseCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = timerPulseCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);
		
      // Step 3: Set necessary parameters.
      int32 channelCountMax = timerPulseCtrl->getFeatures()->getChannelCountMax();
      ret = timerPulseCtrl->setChannelStart(startChannel);
      CHK_RESULT(ret);
      ret = timerPulseCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);
      Array<TmrChannel>*tmrChannel = timerPulseCtrl->getChannels();
      for (int32 i = startChannel; i < startChannel + channelCount; ++i)
      {
         ret = tmrChannel->getItem(i % channelCountMax).setFrequency(frequency);
         CHK_RESULT(ret);
      }
      
      // Step 4: Start PulseOutputwithTimerInterrupt
      printf(" PulseOutputwithTimerInterrupt is in progress...\n Test signal to the Out pin !\n");
      printf(" Any key to quit !\n");
      ret = timerPulseCtrl->setEnabled(true);
      CHK_RESULT(ret);
       
      while(!kbhit())
      {
         SLEEP(1);         
      }

      // Step 5: Stop PulseOutputwithTimerInterrupt
      timerPulseCtrl->setEnabled(false);
   }while(false);

	// Step 6: Close device and release any allocated resource.
	timerPulseCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }
   return 0;
}