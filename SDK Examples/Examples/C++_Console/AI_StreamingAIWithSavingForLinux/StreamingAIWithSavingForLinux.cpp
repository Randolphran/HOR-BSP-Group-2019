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
*    StreamingAIWithSaving.cpp
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Streaming AI With Saving function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "../inc/compatibility.h"
#include "../../../inc/bdaqctrl.h"
using namespace Automation::BDaq;
using namespace std;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define       deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32         startChannel = 0;
const int32   channelCount = 2;
const int32   sectionLength = 1000;
const int32   sectionCount = 0;

const int32   SingleSavingFileSize = 1024  * sizeof(double);
const int32   RequirementFileSize  = 10240 * sizeof(double);

fstream   fileStream;

// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define       USER_BUFFER_SIZE   channelCount*sectionLength
double        userDataBuffer[USER_BUFFER_SIZE]; 

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

inline void openFile()
{
   fileStream.open("..\\C++_Data_Linux.bin", ios::out | ios::in | ios::binary | ios::trunc);
   if (!fileStream)
   {
      cout << "cannot open the file!\n" << endl;
      return;
   }
}

inline int WrittenFileSize()
{
   fileStream.seekg(0, ios::end);
   return fileStream.tellg(); 
}

// This function is used to deal with 'DataReady' Event. 
void BDAQCALL OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   // printf("Streaming AI data ready: count = %d\n",args->Count);
   static int i = 1;
   WaveformAiCtrl * waveformAiCtrl = NULL;
   waveformAiCtrl = (WaveformAiCtrl *)sender;
   int32 getDataCount = min(USER_BUFFER_SIZE, args->Count);
   waveformAiCtrl->GetData(getDataCount, userDataBuffer);
   printf("Ready to save the data...\n\n");

   fileStream.write((char*)userDataBuffer, SingleSavingFileSize);
   printf("The real-time size of file is %d byte\n\n", WrittenFileSize());
   printf("Executed %d time.\n\n", i++);
}
//The function is used to deal with 'OverRun' Event.
void BDAQCALL OnOverRunEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf("Streaming AI Overrun: offset = %d, count = %d\n", args->Offset, args->Count);
}
//The function is used to deal with 'CacheOverflow' Event.
void BDAQCALL OnCacheOverflowEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf(" Streaming AI Cache Overflow: offset = %d, count = %d\n", args->Offset, args->Count);
}
//The function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   printf("Streaming AI stopped: offset = %d, count = %d\n", args->Offset, args->Count);
}

int main(int argc, char* argv[])
{
   ErrorCode        ret = Success;
   // Step 1: Create a 'WaveformAiCtrl' for Buffered AI function.
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();

   //Step 2: Open file
   openFile();

   // Step 3: Set the notification event Handler by which we can known the state of operation effectively.
   wfAiCtrl->addDataReadyHandler(OnDataReadyEvent, NULL);
   wfAiCtrl->addOverrunHandler(OnOverRunEvent, NULL);
   wfAiCtrl->addCacheOverflowHandler(OnCacheOverflowEvent, NULL);
   wfAiCtrl->addStoppedHandler(OnStoppedEvent, NULL);
   do
   {
      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = wfAiCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = wfAiCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 5: Set necessary parameters.
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

      // Step 6: The operation has been started.
		ret = wfAiCtrl->Prepare();
		CHK_RESULT(ret);
		ret = wfAiCtrl->Start();
      CHK_RESULT(ret);

      // Step 7: The device is acquiring data.
      printf("Streaming AI is in progress.\nplease wait...  any key to quit!\n\n");
      do
      {
         SLEEP(1);
      }	while((WrittenFileSize() < RequirementFileSize) ? true : false);
      printf("Saving completely!\n\n");

      // step 8: Stop the operation if it is running.
      ret = wfAiCtrl->Stop(); 
      CHK_RESULT(ret);
   }while(false);

   // Step 9: Close device, release any allocated resource.
   wfAiCtrl->Dispose();
   fileStream.close();

   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();// wait any key to quit!
   }
   return 0;
}