/*******************************************************************************
Copyright (c) 1983-2017 Advantech Co., Ltd.
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
*     BufferedUpDownCounter.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Buffered UpDown Counter function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "../inc/compatibility.h"
#include "../../../inc/bdaqctrl.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define     deviceDescription L"PCIE-1813,BID#15"
const wchar_t* profilePath = L"../../profile/PCIE-1813.xml";
#define     sectionLength 1024
#define     sectionCount  0

// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define    USER_BUFFER_SIZE   sectionLength
int32      userDataBuffer[USER_BUFFER_SIZE];

void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

void BDAQCALL OnDataReadyEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{	
	int32 returnedCount = 0;
   ErrorCode ret = Success;
	BufferedUdCounterCtrl *ctrl = (BufferedUdCounterCtrl *)sender;
   int32 getDataCount = min(USER_BUFFER_SIZE, args->Count);
	ret = BufferedUdCounterCtrl_GetDataI32(ctrl, args->Channel, getDataCount, userDataBuffer, 0, &returnedCount, NULL);
	// in this demo, we show only the first sample of each channel's new data
   if(!BioFailed(ret)) {
      printf("Buffered Up-down Counting get data count is  %d\n", returnedCount);
      printf("the first sample for Channel %d is: %d\n", args->Channel, userDataBuffer[0]);
   }
}
// This function is used to deal with 'Overrun' Event.
void BDAQCALL OnOverRunEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
	printf("Buffered Up-down Counting Overrun: channel = %d, offset = %d, count = %d\n", args->Channel, args->Offset, args->Count);
}
// This function is used to deal with 'CacheOverflow' Event.
void BDAQCALL OnCacheOverflowEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
	printf("Buffered Up-down Counting Cache Overflow: channel = %d, offset = %d, count = %d\n", args->Channel, args->Offset, args->Count);
}
// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
   printf("Buffered Up-down Counting stopped: channel = %d, offset = %d, count = %d\n", args->Channel, args->Offset, args->Count);
}

int main(int argc, char* argv[])
{
   ErrorCode ret     = Success;
   IArray* channels  = NULL;
   int32 chCount     = 4;
   int8  chEnabled[] = {1, 0, 0, 0};
   Trigger*  trigger = NULL;
   Record*   record  = NULL;
   UdChannel * udChannel = NULL;
   int i = 0;

   // Step 1: Create a 'BufferedUdCounterCtrl' for Buffered UpDown Counter function.
   BufferedUdCounterCtrl* bfdUdCounterCtrl = BufferedUdCounterCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   BufferedUdCounterCtrl_addDataReadyHandler(bfdUdCounterCtrl, OnDataReadyEvent, NULL);
   BufferedUdCounterCtrl_addOverrunHandler(bfdUdCounterCtrl, OnOverRunEvent, NULL);
   BufferedUdCounterCtrl_addCacheOverflowHandler(bfdUdCounterCtrl, OnCacheOverflowEvent, NULL);
   BufferedUdCounterCtrl_addStoppedHandler(bfdUdCounterCtrl, OnStoppedEvent, NULL);
   do
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = BufferedUdCounterCtrl_setSelectedDevice(bfdUdCounterCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = BufferedUdCounterCtrl_LoadProfile(bfdUdCounterCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      ret = BufferedUdCounterCtrl_setChannelMap(bfdUdCounterCtrl, chCount, chEnabled);
	   CHK_RESULT(ret);

      ret = BufferedUdCounterCtrl_setSampleClkSrc(bfdUdCounterCtrl, SigExtDigClock);
      CHK_RESULT(ret);

      record = BufferedUdCounterCtrl_getRecord(bfdUdCounterCtrl);
      {
         ret = Record_setSectionCount(record, sectionCount); //The 0 means setting 'streaming' mode
         CHK_RESULT(ret);
         ret = Record_setSectionLength(record, sectionLength);
         CHK_RESULT(ret);
      }

      trigger = BufferedUdCounterCtrl_getTrigger(bfdUdCounterCtrl); //Setting trigger
      if(trigger) {
         ret = Trigger_setSource(trigger, SignalNone); // The "SignalNone" means doing without trigger.
         CHK_RESULT(ret);
      }

      // Step 5: Set counting type for  Buffered UpDown Counter
		/******************************************************************************************************************/
		/*In this example, we use the PCIE-1813 and set 'PulseDirection' as the default CountingType.See manual for details.
		/******************************************************************************************************************/
      channels = BufferedUdCounterCtrl_getChannels(bfdUdCounterCtrl);
      for (i = 0; i < chCount; i++)
      {
         udChannel = (UdChannel*)Array_getItem(channels, i);
         ret = UdChannel_setCountingType(udChannel, PulseDirection);
         CHK_RESULT(ret);
      }
      // Step 6: Start Buffered UpDown Counter 
      ret = BufferedUdCounterCtrl_Prepare(bfdUdCounterCtrl);
      CHK_RESULT(ret);

	   ret= BufferedUdCounterCtrl_setEnabled(bfdUdCounterCtrl, TRUE);
	   CHK_RESULT(ret);

	   // Step 7: Read counting value: connect the input signal to channels you selected to get value.
	   printf("Buffered UpDown Counter is in progress...\nconnect the input signal to channels you selected to get value!\n");
	   printf("any key will stop Buffered UpDown Counter!\n\n");
	   while ( !kbhit()) {
         SLEEP(1);
      }

	   // step 8: Stop the operation if it is running.
	   ret= BufferedUdCounterCtrl_setEnabled(bfdUdCounterCtrl, FALSE);
	   CHK_RESULT(ret);
   }while(FALSE);

   // Step 9: Close device, release any allocated resource.
	BufferedUdCounterCtrl_Dispose(bfdUdCounterCtrl);

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("\nSome error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }  
   return 0;
}
