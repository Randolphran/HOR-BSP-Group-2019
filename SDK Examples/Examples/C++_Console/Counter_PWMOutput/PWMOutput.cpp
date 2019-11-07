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
*    PWMOutput.cpp
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
PulseWidth pulseWidth = {0.08,0.02};

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'PwModulatorCtrl' for PWMOutput function.
   PwModulatorCtrl* pwModulatorCtrl = PwModulatorCtrl::Create();

   do
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = pwModulatorCtrl ->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = pwModulatorCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 3: Set necessary parameters.
      int32 channelCountMax = pwModulatorCtrl->getFeatures()->getChannelCountMax();
      pwModulatorCtrl->setChannelStart(startChannel);
      CHK_RESULT(ret);
      pwModulatorCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);
      Array<PoChannel>*poChannel = pwModulatorCtrl->getChannels();
      for (int i = startChannel; i < startChannel + channelCount; i++)
      {
         poChannel->getItem(i % channelCountMax).setPulseWidth(pulseWidth);
      }
      
      // Step 4: start PWMOutput
      printf("PWMOutput is in progress...\n test signal to the Out pin !\n");
      printf("any key to quit !\n");
      ret = pwModulatorCtrl->setEnabled(true);
      CHK_RESULT(ret);
      while(!kbhit())
      {
         SLEEP(1);         
      }

      // Step 5: Stop PWMOutput
      pwModulatorCtrl->setEnabled(false);
   }while(false);

	//Step 6: Close device and release any allocated resource.
	pwModulatorCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf(" Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }
   return 0;
}

