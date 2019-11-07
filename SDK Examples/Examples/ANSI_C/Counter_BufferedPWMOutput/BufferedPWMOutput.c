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
*     BufferedPWMOutput.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Buffered PWM Output function.
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

#define  IntervalCount  2048
#define  Samples        4096     
#define  UserBufLength  Samples     
void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

// This function is used to deal with 'DataTransmitted' Event.
void BDAQCALL OnDataTransmittedEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
   printf("BufferedPWMOut Data Transmitted: channel = %d, count = %d, offset = %d\n", args->Channel, args->Count, args->Offset);
}
// This function is used to deal with 'TransStopped' Event.
void BDAQCALL OnTransStoppedEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
   printf("BufferedPWMOutput Transmit Stopped: channel = %d, count = %d, offset = %d\n", args->Channel, args->Count, args->Offset);
}
// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void * sender, BfdCntrEventArgs * args, void *userParam)
{
   printf("BufferedPWMOutput stopped: channel = %d, count = %d, offset = %d\n", args->Channel, args->Count, args->Offset);
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   Trigger* trigger = NULL;
   int32 chCount     = 4;
   int8  chEnabled[] = {1, 0, 0, 0};
   int i = 0;
   PulseWidth userData[UserBufLength] = {0};

   // Step 1: Create a 'BufferedPwModulatorCtrl' for Buffered PWM Output function.
   BufferedPwModulatorCtrl* bfdPwModulatorCtrl = BufferedPwModulatorCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   BufferedPwModulatorCtrl_addDataTransmittedHandler(bfdPwModulatorCtrl, OnDataTransmittedEvent, NULL);
   BufferedPwModulatorCtrl_addTransitStoppedHandler(bfdPwModulatorCtrl, OnTransStoppedEvent, NULL);
   BufferedPwModulatorCtrl_addStoppedHandler(bfdPwModulatorCtrl, OnStoppedEvent, NULL);

   do
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = BufferedPwModulatorCtrl_setSelectedDevice(bfdPwModulatorCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = BufferedPwModulatorCtrl_LoadProfile(bfdPwModulatorCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      ret = BufferedPwModulatorCtrl_setChannelMap(bfdPwModulatorCtrl, chCount, chEnabled);
	   CHK_RESULT(ret);

      ret = BufferedPwModulatorCtrl_setSampleClkSrc(bfdPwModulatorCtrl, SignalNone);
      CHK_RESULT(ret);

      ret = BufferedPwModulatorCtrl_setIntervalCount(bfdPwModulatorCtrl, IntervalCount);
      CHK_RESULT(ret);
      ret = BufferedPwModulatorCtrl_setSamples(bfdPwModulatorCtrl, Samples);
      CHK_RESULT(ret);
      ret = BufferedPwModulatorCtrl_setStreaming(bfdPwModulatorCtrl, TRUE);
      CHK_RESULT(ret);

      trigger = BufferedPwModulatorCtrl_getTrigger(bfdPwModulatorCtrl); //Setting trigger
      if(trigger) {
         ret = Trigger_setSource(trigger, SignalNone); // The "SignalNone" means doing without trigger.
         CHK_RESULT(ret);
      }

      for(i = 0; i < UserBufLength; i++) {
         userData[i].HiPeriod = 0.5;
         userData[i].LoPeriod = 0.5;
      }

      for(i = 0; i < chCount; i++) { 
         if(chEnabled[i]) {
            ret = BufferedPwModulatorCtrl_SetData(bfdPwModulatorCtrl, i, UserBufLength, userData);
            CHK_RESULT(ret);
         }
      }

      // Step 5: Start Buffered PWM Out Counter 
      ret = BufferedPwModulatorCtrl_Prepare(bfdPwModulatorCtrl);
      CHK_RESULT(ret);

	   ret= BufferedPwModulatorCtrl_setEnabled(bfdPwModulatorCtrl, TRUE);
	   CHK_RESULT(ret);

	   printf("PWMOutput is in progress... any key to quit !\n");
	   while ( !kbhit()) {
         SLEEP(1);
      }

	   // step 6: Stop the operation if it is running.
	   ret= BufferedPwModulatorCtrl_setEnabled(bfdPwModulatorCtrl, FALSE);
	   CHK_RESULT(ret);
   }while(FALSE);

   // Step 7: Close device, release any allocated resource.
	BufferedPwModulatorCtrl_Dispose(bfdPwModulatorCtrl);

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("\nSome error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }  
   return 0;
}
