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
*     EventCounter.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Event Counter function.
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
#define deviceDesription L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32   channelStart = 0;
int32   channelCount = 1;

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
}
int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
	int32   value = 0;

   // Step 1: Create a 'EventCounterCtrl' for Event Counter function.
   EventCounterCtrl * eventCounterCtrl = EventCounterCtrl_Create();

   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceMode = -1;
      devInfo.DeviceMode = ModeWrite;
      devInfo.ModuleIndex = 0;
      wcscpy(devInfo.Description, deviceDesription);
      ret = EventCounterCtrl_setSelectedDevice(eventCounterCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = EventCounterCtrl_LoadProfile(eventCounterCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);
      
      // Step 3: Set necessary parameters. 
      ret = EventCounterCtrl_setChannelStart(eventCounterCtrl, channelStart);
      CHK_RESULT(ret);
      ret = EventCounterCtrl_setChannelCount(eventCounterCtrl, channelCount);
      CHK_RESULT(ret);

      // Step 4: Start EventCounter 
      ret = EventCounterCtrl_setEnabled(eventCounterCtrl, TRUE);
      CHK_RESULT(ret);

      // Step 5: Read counting value: connect the input signal to channels you selected to get event counter value.
      printf("Event counter is in progress...\nconnect the input signal to ");
      printf("CNT%d_CLK pin if you choose external clock!\n",channelStart);
      printf("any key will stop event counter!\n\n");

      while (!kbhit())
      {
         SLEEP(1);//get event count value per second       
         ret = EventCounterCtrl_Read(eventCounterCtrl, 1, &value);
         CHK_RESULT(ret);
         printf("\n channel %u Current Event count: %u\n", channelStart, value);
      }
      
      // Step 6: stop EventCounter
      ret = EventCounterCtrl_setEnabled(eventCounterCtrl, FALSE);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 7: Close device and release any allocated resource.
   EventCounterCtrl_Dispose(eventCounterCtrl);
   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("\nSome error occurred. And the last error code is Ox%X.\n", ret);
      waitAnyKey();
   }  
   return 0;
}