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
* Windows Example:
*    FrequencyMeasurement.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Frequency Measurement function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*    5  Set the 'collectionPeriod' to decide period to measure frequency.
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
double      collectionPeriod = 0;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'FreqMeterCtrl' for Frequency Measurement function.
   FreqMeterCtrl* freqMeterCtrl = FreqMeterCtrl::Create();
   do
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = freqMeterCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = freqMeterCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 3: Set necessary parameters
      int32 channelCountMax = freqMeterCtrl->getFeatures()->getChannelCountMax();
      ret = freqMeterCtrl->setChannelStart(startChannel);
      CHK_RESULT(ret);
      ret = freqMeterCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);
      Array<FmChannel>* fmChs = freqMeterCtrl->getChannels();  
      for (int i = startChannel; i < startChannel + channelCount; i++)
      {
        ret = fmChs->getItem(i % channelCountMax).setCollectionPeriod(collectionPeriod);//0 means automation
        CHK_RESULT(ret);
      }

      // Step 4: Start Frequency Measurement
      ret = freqMeterCtrl->setEnabled(true);
      CHK_RESULT(ret);

      // Step 5: Read frequency value.
      printf(" FrequencyMeasure is in progress...\n");
      printf(" connect the input signal to CNT%d_CLK pin if you choose external clock!\n",channelCount);
      printf(" any key to quit!\n\n");
      while (!kbhit())
      {
         SLEEP(1);
         double value = 0.0;
         ret = freqMeterCtrl->Read(value);
         CHK_RESULT(ret);
         printf("\n channel %d Current frequency: %f Hz\n",channelCount, value);
      }

      // Step 6: Stop Frequency Measurement
      freqMeterCtrl->setEnabled(false);
   }while(false);
  
	// Step 7: Close device and release any allocated resource.
	freqMeterCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf(" Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }   
   return 0;
}

