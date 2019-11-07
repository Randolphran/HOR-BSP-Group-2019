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
*    AsynOneBufferedAI_TDtrtp.cpp
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Asynchronous One Buffered AI with Trigger Delay to
*    Start and delay to stop function together.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*    7. Set 'trigger parameters' to decide trigger property.
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
#define      deviceDescription  L"PCIE-1810,BID#0"
const wchar_t* profilePath = L"../../profile/PCIE-1810.xml";

int32        startChannel = 0;
const int32  channelCount = 2;
const int32  sectionLength = 1024;
const int32  sectionCount = 1;
// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define		 USER_BUFFER_SIZE    channelCount*sectionLength*sectionCount 
double       Data[USER_BUFFER_SIZE];

// Set trigger parameters
TriggerAction triggerAction = DelayToStart;
ActiveSignal  triggerEdge = RisingEdge;
int           triggerDelayCount = 1000;
double        triggerLevel = 3.0;

//for trigger1 parameters
TriggerAction trigger1Action = DelayToStop;
ActiveSignal  trigger1Edge = RisingEdge;
int           trigger1DelayCount = 1000;
double        trigger1Level = 3.0;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

// This function is used to deal with 'StoppedEvent'.
void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   WaveformAiCtrl * wfAiCtrl = (WaveformAiCtrl *)sender;
	int32 returnedCount = 0;
   int32 getDataCount = min(USER_BUFFER_SIZE, args->Count);
   printf("Waveform AI data ready: count = %d\n", args->Count);
   wfAiCtrl->GetData(getDataCount, Data, 0, &returnedCount);
   Trigger * trigger = wfAiCtrl->getTrigger1();
   if (trigger != NULL)
   {
      int delayCount = wfAiCtrl->getTrigger1()->getDelayCount();
		int triggerPointIndex = returnedCount/channelCount - delayCount;
      printf("The data count each channel:%d,  trigger point each channel: %d\n",returnedCount/channelCount, triggerPointIndex);
   }
   // in this example, we show only one sample of each channel's new data
   printf("the first data each channel are:\n\n");
   for(int32 i = 0; i < channelCount; ++i)
   {
      printf("channel %d: %10.6f \n",(i + startChannel), Data[i]);   
   }
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;

   // Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();

	// Step 2: Set the notification event Handler by which we can known the state of operation effectively.
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
      if (!(wfAiCtrl->getFeatures()->getTriggerCount() > 1))
      {
         printf("The device does not support this demo\n");
         break;
      }

      // Step 4: Set necessary parameters. 
      Conversion * conversion = wfAiCtrl->getConversion();
      ret = conversion->setChannelStart(startChannel);
      CHK_RESULT(ret);
      ret = conversion->setChannelCount(channelCount);
      CHK_RESULT(ret);
		Record * record = wfAiCtrl->getRecord();
      ret = record->setSectionCount(sectionCount);//The sectionCount is nonzero value, which means 'One Buffered' mode.
      CHK_RESULT(ret);
      ret = record->setSectionLength(sectionLength);
      CHK_RESULT(ret);
      
      //Step 5: Trigger parameters setting
		Trigger* trigger = wfAiCtrl->getTrigger();
		if (trigger != NULL)
		{
         ret = trigger->setAction(triggerAction);
         CHK_RESULT(ret);
			/******************************************************************************************/
			/*The different kinds of devices have different trigger source. The details see manual.
			/*In this example, we use the PCIE-1810 and set 'SigExtDigClock' as the default trigger source.
			/******************************************************************************************/
         Array<SignalDrop>*  srcs = wfAiCtrl->getFeatures()->getTriggerSources();
			//int sourceCount = srcs->getLength();//Uncomment this line, user can get the count of supported trigger source.
			ret = trigger->setSource(srcs->getItem(1));//To PCIE-1810, the 1 means 'SigExtDigClock'.
         CHK_RESULT(ret);
         ret = trigger->setDelayCount(triggerDelayCount) ;
         CHK_RESULT(ret);
         ret = trigger->setEdge(triggerEdge);
         CHK_RESULT(ret);
         ret = trigger->setLevel(triggerLevel);
         CHK_RESULT(ret);
		}

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

      // Step 6: start Asynchronous Buffered AI, 'Asynchronous' means the method returns immediately
      // after the acquisition has been started. The StoppedHandler's 'OnStoppedEvent' method will be called
      // after the acquisition is completed.
      printf("Asynchronous finite acquisition is in progress.\n");
		ret = wfAiCtrl->Prepare();
		CHK_RESULT(ret);
      ret = wfAiCtrl->Start();
      CHK_RESULT(ret);

      // Step 7: The device is acquiring data.
      do
      {
         SLEEP(1);
      }while(!kbhit());

      // step 8: stop the operation if it is running.
      ret = wfAiCtrl->Stop();  
      CHK_RESULT(ret);
   }
   while(false);

	// Step 9: close device, release any allocated resource before quit.
	wfAiCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
	if(BioFailed(ret))
	{
		printf("Some error occurred. And the last error code is 0x%X.\n", ret);
		waitAnyKey();// wait any key to quit!
	}
   return 0;   
}
