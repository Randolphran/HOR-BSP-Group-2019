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
*    SynchronousOneBufferedAI.c
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Synchronous One Buffered AI function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' which can get from system device manager for opening the device. 
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
#define startChannel       0
#define channelCount       2
#define sectionLength      1024
#define sectionCount       1
// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define USER_BUFFER_SIZE   channelCount*sectionLength*sectionCount
double Data[USER_BUFFER_SIZE];

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode    ret           = Success;
   Conversion * conversion    = NULL;
   Record *     record        = NULL;
   AiFeatures * aiFeatures    = NULL;
   int32        i             = 0;
	int32        returnedCount = 0;

   // Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl_Create();

   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
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
      
      // Step 3: Set necessary parameters.
      conversion = WaveformAiCtrl_getConversion(wfAiCtrl);
      ret = Conversion_setChannelStart(conversion, startChannel);
      CHK_RESULT(ret);
      ret = Conversion_setChannelCount(conversion, channelCount);
      CHK_RESULT(ret);
		record = WaveformAiCtrl_getRecord(wfAiCtrl);
      ret = Record_setSectionLength(record, sectionLength);
      CHK_RESULT(ret);
      ret = Record_setSectionCount(record, sectionCount);//The sectionCount is nonzero value, which means 'One Buffered' mode.
      CHK_RESULT(ret);

      // Step 4: The operation has been started.
		printf("Polling finite acquisition is in progress.\n");
		ret = WaveformAiCtrl_Prepare(wfAiCtrl);
		CHK_RESULT(ret);
      ret = WaveformAiCtrl_Start(wfAiCtrl);
      CHK_RESULT(ret);

      //Step 5: GetData
      ret = WaveformAiCtrl_GetDataF64(wfAiCtrl, USER_BUFFER_SIZE, Data, -1, &returnedCount, NULL, NULL, NULL);//The timeout value is -1, meaning infinite waiting.
      CHK_RESULT(ret);
		printf("Polling One Buffered AI get data count is  %d\n", returnedCount);
		if (ret == Success)
		{
			printf("The first sample each channel are:\n");
			for(i = 0; i < channelCount; ++i)
			{
				printf("channel %d: %10.6f \n", (i + startChannel), Data[i]);
			}
		}
      printf("Acquisition has completed!\n\n");
      
      // step 6: stop the operation if it is running.
      ret = WaveformAiCtrl_Stop(wfAiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   //Step 7: close device, release any allocated resource before quit.
   WaveformAiCtrl_Dispose(wfAiCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
   }
   waitAnyKey();
   return 0;
}