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
*    DelayedPulseGeneration.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Delayed Pulse Generation function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*    5  set the 'delayCount' to decide delay time for selected channel.
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
#define     deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32       channelStart = 0;
int32       channelCount = 1;
int32       delayCount = 50;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

int32 delayedPulseOccursCount = 0;
// This function is used to deal with 'Cntr' Event.
void BDAQCALL OnCounterEvent(void * sender, CntrEventArgs * args, void * userParam)
{
   printf("\n Channel %d's Delayed Pulse occurs %d time(s)\n",args->Channel,++delayedPulseOccursCount);
}
int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'OneShotCtrl' for Delayed Pulse Generation function.
   OneShotCtrl * oneShotCtrl = OneShotCtrl::Create();
   
  	// Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   oneShotCtrl->addOneShotHandler(OnCounterEvent, NULL);
   do
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = oneShotCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = oneShotCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      int32 channelCountMax = oneShotCtrl->getFeatures()->getChannelCountMax();
      ret = oneShotCtrl->setChannelStart(channelStart);
      CHK_RESULT(ret);
      ret = oneShotCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);
      Array<OsChannel>*osChannel = oneShotCtrl->getChannels();
      for (int32 i = channelStart; i < channelStart + channelCount; i++)
      {
         ret = osChannel->getItem(i % channelCountMax).setDelayCount(delayCount);
         CHK_RESULT(ret);
      }
 
      // Step 5: Start DelayedPulseGeneration. 
      printf(" Delayed Pulse Generation is in progress...\n");
      printf(" give a low level signal to Gate pin and Test the pulse signal on the Out pin !\n\n");
      printf(" any key to quit !\n\n");
      ret = oneShotCtrl->setEnabled(true);
      CHK_RESULT(ret);

      // Step 6:The device is working.
      while( !kbhit() )
      {
         SLEEP(1);
      }

      // Step 7: stop DelayedPulseGeneration function
      oneShotCtrl->setEnabled(false);
   }while(false);
  
	// Step 8: Close device and release any allocated resource.
	oneShotCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   } 
   return 0;
}

