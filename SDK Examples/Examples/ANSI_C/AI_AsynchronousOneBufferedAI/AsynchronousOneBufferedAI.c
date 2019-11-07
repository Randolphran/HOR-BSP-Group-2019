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
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
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
#define sectionCount  1
// // user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define USER_BUFFER_SIZE (channelCount*sectionLength*sectionCount)
double  Data[USER_BUFFER_SIZE];

void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void *userParam);

void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   Conversion * conversion = NULL;
   Record * record = NULL;

   // Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   WaveformAiCtrl_addStoppedHandler(wfAiCtrl, OnStoppedEvent, NULL);
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

      // Step 4: Set necessary parameters
      conversion = WaveformAiCtrl_getConversion(wfAiCtrl);
      ret = Conversion_setChannelStart(conversion, startChannel);
      CHK_RESULT(ret);
      ret = Conversion_setChannelCount(conversion, channelCount);
      CHK_RESULT(ret);
		record = WaveformAiCtrl_getRecord(wfAiCtrl);
		ret = Record_setSectionCount(record, sectionCount);//The sectionCount is nonzero value, which means 'One Buffered' mode.
      CHK_RESULT(ret);
      ret = Record_setSectionLength(record, sectionLength);
      CHK_RESULT(ret);
      printf("Asynchronous finite acquisition is in progress.\n");
      printf("Please wait... any key to quit !\n\n");

      // Step 5: start Asynchronous Buffered AI, 'Asynchronous' means the method returns immediately
      // after the acquisition has been started. The StoppedHandler's 'BfdAiEvent' method will be called
      // after the acquisition is completed.
		ret = WaveformAiCtrl_Prepare(wfAiCtrl);
		CHK_RESULT(ret);
      ret = WaveformAiCtrl_Start(wfAiCtrl);
      CHK_RESULT(ret);

      // Step 6: The device is acquiring data.
      do
      {
         SLEEP(1);
      }while(!kbhit());

      // step 7: stop the operation if it is running.
      ret = WaveformAiCtrl_Stop(wfAiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 8: close device, release any allocated resource before quit.
   WaveformAiCtrl_Dispose(wfAiCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();// wait any key to quit!
   }
   return 0;
}

//The function is used to deal with 'Stoppped Event'
void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   int i = 0;
	int32 returnedCount = 0;
   int32 getDataCount = 0;
   WaveformAiCtrl * waveformAiCtrl = NULL;
   waveformAiCtrl = (WaveformAiCtrl *)sender;
   getDataCount = min(USER_BUFFER_SIZE, args->Count);
   WaveformAiCtrl_GetDataF64(waveformAiCtrl, getDataCount, Data, 0, &returnedCount, NULL, NULL, NULL);
	printf("Asynchronous One Buffered AI get data count is  %d\n", returnedCount);
   printf("the first sample each channel are:\n\n");
   for(i = 0; i < channelCount; ++i)
   {
      printf("channel %d:%10.6f \n",i + startChannel, Data[i]);   
   }
}