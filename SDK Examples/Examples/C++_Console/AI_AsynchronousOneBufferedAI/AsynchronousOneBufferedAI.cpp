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
*    AsynchronousOneBufferedAI.cpp
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Asynchronous One Buffered AI function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.

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
#define      deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32        startChannel = 0;
const int32  channelCount = 2;
const int32  sectionLength = 1024; // for each channel, to decide the capacity of buffer in kernel.
const int32  sectionCount = 1;
// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define		 USER_BUFFER_SIZE    channelCount*sectionLength*sectionCount 
double       Data[USER_BUFFER_SIZE];

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

// This function is used to deal with 'StoppedEvent'.
void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   WaveformAiCtrl * waveformAiCtrl = NULL;
   waveformAiCtrl = (WaveformAiCtrl *)sender;
	int32 returnedCount = 0;
   int32 getDataCount = min(USER_BUFFER_SIZE, args->Count);
   waveformAiCtrl->GetData(getDataCount, Data, 0, &returnedCount);
	printf("Asynchronous One Buffered AI: data count = %d\n", returnedCount);
   printf("the first sample each channel are:\n\n");
   for(int i = 0; i < channelCount; ++i)
   {
      printf("channel %d:%10.6f \n",i + startChannel, Data[i]);   
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

		// Step 4: Set necessary parameters for Buffered AI operation, 
      Conversion* conversion = wfAiCtrl->getConversion();
      ret = conversion->setChannelStart(startChannel);
      CHK_RESULT(ret);
      ret = conversion->setChannelCount(channelCount);
      CHK_RESULT(ret);
		Record* record = wfAiCtrl->getRecord();
      ret = record->setSectionLength(sectionLength);
      CHK_RESULT(ret);
      ret = record->setSectionCount(sectionCount);//The sectionCount is nonzero value, which means 'One Buffered' mode.
      CHK_RESULT(ret);
		
      // Step 5: start Asynchronous Buffered AI, 'Asynchronous' means the method returns immediately
      // after the acquisition has been started. The StoppedHandler's 'StoppedEvent' method will be called
      // after the acquisition is completed.
      printf("Asynchronous finite acquisition is in progress.\n");
      ret = wfAiCtrl->Prepare();
		CHK_RESULT(ret);
		ret = wfAiCtrl->Start();
      CHK_RESULT(ret);

      // Step 6: The device is acquiring data.
      do
      {
         SLEEP(1);
      }while(!kbhit());

      // step 7: stop the operation if it is running.
      ret = wfAiCtrl->Stop();  
      CHK_RESULT(ret);
   }
   while(false);
   
   // Step 8: close device, release any allocated resource before quit.
   wfAiCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
	if(BioFailed(ret))
	{
		printf("Some error occurred. And the last error code is 0x%X.\n", ret);
		waitAnyKey();// wait any key to quit!
	}
   return 0;   
}