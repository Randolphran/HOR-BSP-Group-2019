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
*     UpDownCounter.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use UpDown Counter function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define     deviceDescription L"PCI-1784,BID#0"
const wchar_t* profilePath = L"../../profile/PCI-1784.xml";
int32       channelStart = 0;
int32       channelCount = 1;

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
}

int main(int argc, char *argv[])
{
   ErrorCode ret = Success;
   IArray * channels = 0;
   int index = 0;
   UdChannel * udChannel = 0;
   int32 value = 0;
   
   // Step 1: Create a 'UdCounterCtrl' for UpDown Counter function.
   UdCounterCtrl * udCounterCtrl = UdCounterCtrl_Create();

   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode = ModeWriteWithReset;
      devInfo.ModuleIndex = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = UdCounterCtrl_setSelectedDevice(udCounterCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = UdCounterCtrl_LoadProfile(udCounterCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);
      
      // Step 3: Set necessary parameters
      ret = UdCounterCtrl_setChannelStart(udCounterCtrl, channelStart);
      CHK_RESULT(ret);
      ret = UdCounterCtrl_setChannelCount(udCounterCtrl, channelCount);
      CHK_RESULT(ret);

      // Step 4: Set counting type for UpDown Counter 
		/******************************************************************************************************************/
		/*In this example, we use the PCIE-1784 and set 'PulseDirection' as the default CountingType.The details see manual.
		/******************************************************************************************************************/
      channels = UdCounterCtrl_getChannels(udCounterCtrl);
      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         udChannel = (UdChannel*)Array_getItem(channels, index);
         ret = UdChannel_setCountingType(udChannel, PulseDirection);
         CHK_RESULT(ret);
      }

      // Step 5: Start UpDown Counter 
      ret = UdCounterCtrl_setEnabled(udCounterCtrl, TRUE);
      CHK_RESULT(ret);

      // Step 6: Read counting value: connect the input signal to channels you selected to get UpDown counter value.
      printf("UpDown counter is in progress...\nconnect the input signal to ");
      printf("any key will stop UpDown counter!\n\n");
      while ( !kbhit())
      {
         SLEEP(1);//get event UpDown count value per second
         ret = UdCounterCtrl_Read(udCounterCtrl, 1, &value);
         CHK_RESULT(ret);
         printf("\n channel %u Current UpDown count: %u\n", channelStart, value);
      }

      // Step 7: stop UpDown Counter
      UdCounterCtrl_setEnabled(udCounterCtrl, FALSE);
   } while (FALSE);

   // Step 8: Close device and release any allocated resource.
   UdCounterCtrl_Dispose(udCounterCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("\nSome error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }  
   return 0;
}