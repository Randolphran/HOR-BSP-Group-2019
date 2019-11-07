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
*     BufferedPulseWidthMeasurement.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Buffered Pulse Width Measurement function.
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
PulseWidth userDataBuffer[USER_BUFFER_SIZE];

void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

void BDAQCALL OnDataReadyEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{	
   ErrorCode ret = Success;
	int32 returnedCount = 0;
	BufferedPwMeterCtrl *ctrl = (BufferedPwMeterCtrl *)sender;
   int32 getDataCount = min(USER_BUFFER_SIZE, args->Count); 
	ret = BufferedPwMeterCtrl_GetData(ctrl, args->Channel, getDataCount, userDataBuffer, 0, &returnedCount, NULL);
	// in this demo, we show only the first sample of each channel's new data
   if(!BioFailed(ret)) {
      printf("Buffered PulseWidth Measurement get data count is  %d\n", returnedCount);
      printf("the first sample for Channel %d is: Pulse Width: HiPeriod=%f s  LoPeriod=%f s\n", args->Channel, userDataBuffer[0].HiPeriod, userDataBuffer[0].LoPeriod);
   }
}
// This function is used to deal with 'Overrun' Event.
void BDAQCALL OnOverRunEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
	printf("Buffered PulseWidth Measurement Overrun: channel = %d, offset = %d, count = %d\n", args->Channel, args->Offset, args->Count);
}
// This function is used to deal with 'CacheOverflow' Event.
void BDAQCALL OnCacheOverflowEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
	printf("Buffered PulseWidth Measurement Cache Overflow: channel = %d, offset = %d, count = %d\n", args->Channel, args->Offset, args->Count);
}
// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
   printf("Buffered PulseWidth Measurement stopped: channel = %d, offset = %d, count = %d\n", args->Channel, args->Offset, args->Count);
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   int32     chCount     = 4;
   int8      chEnabled[] = {1, 0, 0, 0};
   Trigger*  trigger     = NULL;
   Record*   record      = NULL;

   // Step 1: Create a 'BufferedPwMeterCtrl' for Buffered PulseWidth Measurement function.
   BufferedPwMeterCtrl* bfdPwMeterCtrl = BufferedPwMeterCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   BufferedPwMeterCtrl_addDataReadyHandler(bfdPwMeterCtrl, OnDataReadyEvent, NULL);
   BufferedPwMeterCtrl_addOverrunHandler(bfdPwMeterCtrl, OnOverRunEvent, NULL);
   BufferedPwMeterCtrl_addCacheOverflowHandler(bfdPwMeterCtrl, OnCacheOverflowEvent, NULL);
   BufferedPwMeterCtrl_addStoppedHandler(bfdPwMeterCtrl, OnStoppedEvent, NULL);
   do
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = BufferedPwMeterCtrl_setSelectedDevice(bfdPwMeterCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = BufferedPwMeterCtrl_LoadProfile(bfdPwMeterCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      ret = BufferedPwMeterCtrl_setChannelMap(bfdPwMeterCtrl, chCount, chEnabled);
	   CHK_RESULT(ret);

      ret = BufferedPwMeterCtrl_setSampleClkSrc(bfdPwMeterCtrl, SignalNone);
      CHK_RESULT(ret);

      record = BufferedPwMeterCtrl_getRecord(bfdPwMeterCtrl);
      {
         ret = Record_setSectionCount(record, sectionCount); //The 0 means setting 'streaming' mode
         CHK_RESULT(ret);
         ret = Record_setSectionLength(record, sectionLength);
         CHK_RESULT(ret);
      }

      trigger = BufferedPwMeterCtrl_getTrigger(bfdPwMeterCtrl); //Setting trigger
      if(trigger) {
         ret = Trigger_setSource(trigger, SignalNone); // The "SignalNone" means doing without trigger.
         CHK_RESULT(ret);
      }

      // Step 5: Start Buffered PulseWidth Measurement Counter 
      ret = BufferedPwMeterCtrl_Prepare(bfdPwMeterCtrl);
      CHK_RESULT(ret);

	   ret= BufferedPwMeterCtrl_setEnabled(bfdPwMeterCtrl, TRUE);
	   CHK_RESULT(ret);

	   // Step 6: The device is acquiring PulseWidth data.
	   printf("Pulse Width Measurement is in progress... any key to quit !\n");
	   while ( !kbhit()) {
         SLEEP(1);
      }

	   // step 7: Stop the operation if it is running.
	  ret= BufferedPwMeterCtrl_setEnabled(bfdPwMeterCtrl, FALSE);
     CHK_RESULT(ret);
   }while(FALSE);

   // Step 8: Close device, release any allocated resource.
	BufferedPwMeterCtrl_Dispose(bfdPwMeterCtrl);

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("\nSome error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }  
   return 0;
}
