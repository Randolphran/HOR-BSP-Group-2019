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
*    StreamingAIwithTrigger.cpp
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
#include "../inc/compatibility.h"
#include "../../../inc/bdaqctrl.h"
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define       deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32         startChannel = 0;
const int32   channelCount = 2;
const int32   sectionLength = 1024;
const int32   sectionCount = 0;
// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define		  USER_BUFFER_SIZE    channelCount*sectionLength 
double        userDataBuffer[USER_BUFFER_SIZE]; 

// Set trigger parameters
TriggerAction triggerAction = DelayToStart;
ActiveSignal  triggerEdge = RisingEdge;
int    triggerDelayCount = 600;
double triggerLevel = 2.0;

//for trigger1 parameters 
TriggerAction trigger1Action = DelayToStart;
ActiveSignal  trigger1Edge = RisingEdge;
int    trigger1DelayCount = 600;
double trigger1Level = 2.0;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 
// This function is used to deal with 'DataReady' Event.
void BDAQCALL OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
	int32 returnedCount = 0;
	WaveformAiCtrl * waveformAiCtrl = NULL;
   waveformAiCtrl = (WaveformAiCtrl *)sender;
   int32 getDataCount = min(USER_BUFFER_SIZE, args->Count);
   waveformAiCtrl->GetData(getDataCount, userDataBuffer, 0, &returnedCount);
   // in this demo, we show only the first sample of each channel's new data
	printf("Streaming AI get data count is  %d\n", returnedCount);
   printf("the first sample for each Channel are:\n");
   for(int i = 0; i < channelCount; ++i)
   {
      printf("channel %d:%10.6f \n", i + startChannel, userDataBuffer[i]);   
   }
}
// This function is used to deal with 'Overrun' Event.
void BDAQCALL OnOverRunEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf("Streaming AI Overrun: offset = %d, count = %d\n", args->Offset, args->Count);
}
// This function is used to deal with 'CacheOverflow' Event.
void BDAQCALL OnOverCacheOverflowEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf(" Streaming AI Cache Overflow: offset = %d, count = %d\n", args->Offset, args->Count);
}
// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf("Streaming AI stopped: offset = %d, count = %d\n", args->Offset, args->Count);
}

int main(int argc, char* argv[])
{
   ErrorCode        ret = Success;

   // Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();

	// Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   wfAiCtrl->addDataReadyHandler(OnDataReadyEvent, NULL);
   wfAiCtrl->addOverrunHandler(OnOverRunEvent, NULL);
   wfAiCtrl->addCacheOverflowHandler(OnOverRunEvent, NULL);
   wfAiCtrl->addStoppedHandler(OnStoppedEvent, NULL);
   do
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = wfAiCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = wfAiCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

		// Step 4: Set necessary parameters. 
		Conversion * conversion = wfAiCtrl->getConversion();
		ret = conversion->setChannelStart(startChannel);
		CHK_RESULT(ret);
		ret = conversion->setChannelCount(channelCount);
		CHK_RESULT(ret);
		Record * record = wfAiCtrl->getRecord();
		ret = record->setSectionCount(sectionCount);//The 0 means setting 'streaming' mode.
		CHK_RESULT(ret);
		ret = record->setSectionLength(sectionLength);
		CHK_RESULT(ret);
		
		//Step 5: Trigger parameters setting
      //for trrgger0
      Trigger* trigger = wfAiCtrl->getTrigger();
		if (trigger != NULL)
		{
			ret = trigger->setAction(triggerAction);
         CHK_RESULT(ret);
			/******************************************************************************************/
			/*The different kinds of devices have different trigger source. The details see manual.
			/*In this example, we use the DemoDevice and set 'Ai channel 0' as the default trigger source.
			/******************************************************************************************/
         Array<SignalDrop>*  srcs = wfAiCtrl->getFeatures()->getTriggerSources();
			//int sourceCount = srcs->getLength();//Uncomment this line, user can get the count of supported trigger source.
			ret = trigger->setSource(srcs->getItem(1));//To DemoDevice, the 1 means 'Ai channel 0'.
         CHK_RESULT(ret);
			ret = trigger->setDelayCount(triggerDelayCount);
         CHK_RESULT(ret);
			ret = trigger->setEdge(triggerEdge);
         CHK_RESULT(ret);
			ret = trigger->setLevel(triggerLevel);
         CHK_RESULT(ret);
		}
		else
		{
			printf("The device can not support trigger function! \n any key to quit.");
			break;
		} 

      //for trigger1
      if (wfAiCtrl->getFeatures()->getTriggerCount() > 1)
      {
         Trigger* trigger1 = wfAiCtrl->getTrigger1();
         ret = trigger1->setAction(trigger1Action);
         CHK_RESULT(ret);
         Array<SignalDrop>*  srcs = wfAiCtrl->getFeatures()->getTrigger1Sources();
         ret = trigger1->setSource(srcs->getItem(1));
         CHK_RESULT(ret);
         ret = trigger1->setDelayCount(trigger1DelayCount) ;
         CHK_RESULT(ret);
         ret = trigger1->setEdge(trigger1Edge);
         CHK_RESULT(ret);
         ret = trigger1->setLevel(trigger1Level);
         CHK_RESULT(ret);
      }

      // Step 6: The operation has been started.
      // We can get samples via event handlers.
		ret = wfAiCtrl->Prepare();
		CHK_RESULT(ret);
      ret = wfAiCtrl->Start();
      CHK_RESULT(ret);

      // Step 7: The device is acquiring data.
		printf("Streaming AI is in progress.\nplease wait...  any key to quit!\n\n");
      do
      {
         SLEEP(1);
      }	while(!kbhit());

      // step 8: Stop the operation if it is running.
      ret = wfAiCtrl->Stop(); 
      CHK_RESULT(ret);
   }while(false);

	// Step 9: Close device, release any allocated resource.
	wfAiCtrl->Dispose(); 

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();// wait any key to quit!
   }
   waitAnyKey();
   return 0;
}



