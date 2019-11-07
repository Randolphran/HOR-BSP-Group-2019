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
#include <stdio.h>
#include <stdlib.h>
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define     deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32  channelStart = 0;
int32  channelCount = 1;

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   IArray *  channels = 0;
   FmChannel * fmChannel = 0;
   CntrFeatures * cntrFeatures = 0;
   int index = 0;
   int channelCountMax = 0;
	double collectionPeriod = 0;
	double value = 0;

   // Step 1: Create a 'FreqMeterCtrl' for Frequency Measurement function.
   FreqMeterCtrl* freqMeterCtrl = FreqMeterCtrl_Create();
   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode = ModeWrite;
      devInfo.ModuleIndex = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = FreqMeterCtrl_setSelectedDevice(freqMeterCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = FreqMeterCtrl_LoadProfile(freqMeterCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 3: Set necessary parameters.
      cntrFeatures = FreqMeterCtrl_getFeatures(freqMeterCtrl);
      channelCountMax = CntrFeatures_getChannelCountMax(cntrFeatures);
      ret = FreqMeterCtrl_setChannelStart(freqMeterCtrl, channelStart);
      CHK_RESULT(ret);
      ret = FreqMeterCtrl_setChannelCount(freqMeterCtrl, channelCount);
      CHK_RESULT(ret);
      channels = FreqMeterCtrl_getChannels(freqMeterCtrl);
      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         fmChannel = (FmChannel *)Array_getItem(channels, index % channelCountMax);
         ret = FmChannel_setCollectionPeriod(fmChannel, collectionPeriod);//0 means automation
         CHK_RESULT(ret);
      }

      // Step 4: Start Frequency Measurement
      ret = FreqMeterCtrl_setEnabled(freqMeterCtrl, TRUE);
      CHK_RESULT(ret);

      // Step 5: Read frequency value.
      printf("FrequencyMeasurement is in progress...\n");
      printf("connect the input signal to CNT%d_CLK pin if you choose external clock!\n", channelStart);
      printf("any key to quit!\n\n");
      while (!kbhit())
      {
         SLEEP(1);
			ret = FreqMeterCtrl_Read(freqMeterCtrl, 1, &value);
			CHK_RESULT(ret);
         printf("\n channel %d Current frequency: %f Hz\n", channelStart, value);
      }

      // Step 6: Stop Frequency Measurement
      ret = FreqMeterCtrl_setEnabled(freqMeterCtrl, FALSE);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 7: Close device and release any allocated resource.
   FreqMeterCtrl_Dispose(freqMeterCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf(" Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }   
   return 0;
}
