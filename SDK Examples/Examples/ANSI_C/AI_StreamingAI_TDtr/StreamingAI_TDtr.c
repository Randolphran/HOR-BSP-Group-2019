/*******************************************************************************
Copyright (c) 1983-2016 Advantech Co., Ltd.
********************************************************************************
THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY INFORMATION
WHICH IS THE PROPERTY OF ADVANTECH CORP., ANY DISCLOSURE, USE, OR REPRODUCTION,
WITHOUT WRITTEN AUTHORIZATION FROM ADVANTECH CORP., IS STRICTLY PROHIBITED. 

================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log:  $
--------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows Example:
*    StreamingAIwithTrigger.c
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Streaming AI with Trigger Delay to Start function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*    7. Set the 'trigger parameters' to decide trigger property.
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
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
#define startChannel  0
#define channelCount  2
#define sectionLength 1024
#define sectionCount  0

// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define USER_BUFFER_SIZE  channelCount*sectionLength
double  Data[USER_BUFFER_SIZE]; 

void BDAQCALL OnDataReadyEvent         (void * sender, BfdAiEventArgs * args, void *userParam);
void BDAQCALL OnOverRunEvent           (void * sender, BfdAiEventArgs * args, void *userParam);
void BDAQCALL OnOverCacheOverflowEvent (void * sender, BfdAiEventArgs * args, void *userParam);
void BDAQCALL OnStoppedEvent           (void * sender, BfdAiEventArgs * args, void *userParam);

// Set trigger parameters
TriggerAction triggerAction     = DelayToStart;
ActiveSignal  triggerEdge       = RisingEdge;
int           triggerDelayCount = 600;
double        triggerLevel      = 2.0;

//for trigger1 parameters 
TriggerAction trigger1Action     = DelayToStart;
ActiveSignal  trigger1Edge       = RisingEdge;
int           trigger1DelayCount = 600;
double        trigger1Level      = 2.0;

void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   Conversion * conversion = NULL;
   Record *     record     = NULL;
   Trigger *    trigger    = NULL;
   Trigger *    trigger1   = NULL; 
   IArray *     srcs       = NULL;
   AiFeatures * aiFeatures = NULL;
   
   // Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   WaveformAiCtrl_addDataReadyHandler     (wfAiCtrl, OnDataReadyEvent,         NULL);
   WaveformAiCtrl_addOverrunHandler       (wfAiCtrl, OnOverRunEvent,           NULL);
   WaveformAiCtrl_addCacheOverflowHandler (wfAiCtrl, OnOverCacheOverflowEvent, NULL);
   WaveformAiCtrl_addStoppedHandler       (wfAiCtrl, OnStoppedEvent,           NULL);

   do 
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = WaveformAiCtrl_setSelectedDevice(wfAiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = WaveformAiCtrl_LoadProfile(wfAiCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters. 
      conversion = WaveformAiCtrl_getConversion(wfAiCtrl);
      ret = Conversion_setChannelStart(conversion, startChannel);
      CHK_RESULT(ret);
      ret= Conversion_setChannelCount(conversion, channelCount);
      CHK_RESULT(ret);
		record = WaveformAiCtrl_getRecord(wfAiCtrl);
      ret = Record_setSectionCount(record, sectionCount);//The 0 means setting 'streaming' mode.
      CHK_RESULT(ret);
      ret = Record_setSectionLength(record, sectionLength);
      CHK_RESULT(ret);

      //Step 5: Trigger parameters setting
      aiFeatures = WaveformAiCtrl_getFeatures(wfAiCtrl);
      //for trigger0
      trigger = WaveformAiCtrl_getTrigger(wfAiCtrl);
      if (trigger != NULL)
      {
         ret = Trigger_setAction(trigger, triggerAction);
         CHK_RESULT(ret);
			/******************************************************************************************/
			/*The different kinds of devices have different trigger source. The details see manual.
			/*In this example, we use the DemoDevice and set 'Ai channel 0' as the default trigger source.
			/******************************************************************************************/
         srcs = AiFeatures_getTriggerSources(aiFeatures);
         ret = Trigger_setSource(trigger, *(SignalDrop*)Array_getItem(srcs, 1));//To DemoDevice, the 1 means 'Ai channel 0'.
         CHK_RESULT(ret);
         ret = Trigger_setDelayCount(trigger, triggerDelayCount);   
         CHK_RESULT(ret);
         ret = Trigger_setEdge(trigger, triggerEdge);
         CHK_RESULT(ret);
         ret = Trigger_setLevel(trigger, triggerLevel);
         CHK_RESULT(ret);
      }
      else
      {
         printf("The device can not support trigger function! \n any key to quit.");
         break;
      }
      //for trigger1
      if (AiFeatures_getTriggerCount(aiFeatures) > 1)
      {
         trigger1 = WaveformAiCtrl_getTrigger1(wfAiCtrl);
         ret = Trigger_setAction(trigger1, trigger1Action);
         CHK_RESULT(ret);
         srcs = AiFeatures_getTrigger1Sources(aiFeatures);
         ret = Trigger_setSource(trigger1, *(SignalDrop*)Array_getItem(srcs, 1));
         CHK_RESULT(ret);
         ret = Trigger_setDelayCount(trigger1, trigger1DelayCount);
         CHK_RESULT(ret);
         ret = Trigger_setEdge(trigger1, trigger1Edge);
         CHK_RESULT(ret);
         ret =  Trigger_setLevel(trigger1, trigger1Level);
         CHK_RESULT(ret);
      }
      
		// Step 6: The operation has been started.
		// We can get samples via event handlers.
		ret = WaveformAiCtrl_Prepare(wfAiCtrl);
		CHK_RESULT(ret);
      ret = WaveformAiCtrl_Start(wfAiCtrl);  
      CHK_RESULT(ret);
      
      // Step 7: The device is acquiring data.
		printf("Streaming AI is in progress.\nplease wait...  any key to quit!\n\n");
      do
      {
         SLEEP(1);
      }	while(!kbhit());
      
      // step 8: Stop the operation if it is running.
      ret = WaveformAiCtrl_Stop(wfAiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 9: Close device, release any allocated resource.
   WaveformAiCtrl_Dispose(wfAiCtrl);
   
   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();// wait any key to quit!
   }
   waitAnyKey();
   return 0;
}

// This function is used to deal with 'DataReady' Event.
void BDAQCALL OnDataReadyEvent (void * sender, BfdAiEventArgs * args, void *userParam)
{
   int i = 0;
	int32 returnedCount = 0;
   int32 getDataCount = 0;
   WaveformAiCtrl * waveformAiCtrl = NULL;
   waveformAiCtrl = (WaveformAiCtrl *)sender;
   getDataCount = min(USER_BUFFER_SIZE, args->Count);
   WaveformAiCtrl_GetDataF64(waveformAiCtrl, getDataCount, Data, 0, &returnedCount, NULL, NULL, NULL);
	printf("Streaming AI get data count is  %d\n", returnedCount);
	printf("the first sample for each Channel are:\n");
   // in this demo, we show only the first sample of each channel's new data
   printf("the first sample for each Channel are:\n");
   for(i = 0; i < channelCount; ++i)
   {
      printf("channel %d:%10.6f \n",i + startChannel, Data[i]);   
   }

}

// This function is used to deal with 'Overrun' Event.
void BDAQCALL OnOverRunEvent (void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf("Streaming AI Overrun: offset = %d, count = %d\n", args->Offset, args->Count);
}

// This function is used to deal with 'CacheOverflow' Event.
void BDAQCALL OnOverCacheOverflowEvent (void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf(" Streaming AI Cache Overflow: offset = %d, count = %d\n", args->Offset, args->Count);
}

// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent (void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf("Streaming AI stopped: offset = %d, count = %d\n", args->Offset, args->Count);
}