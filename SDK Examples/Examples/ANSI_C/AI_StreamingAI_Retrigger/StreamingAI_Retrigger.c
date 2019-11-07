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
*    StreamingAI_Retrigger.c
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Streaming AI with Retrigger function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*	  7. Set the 'Cycles'to decide the count of a series of data which is continuous in time domain.
*	  8. Set the 'clockRate'as the sampling count per second in Hz.
*    9. Set the 'trigger parameters' to decide trigger property.
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
#define       deviceDescription  L"PCIE-1840,BID#0"
const wchar_t* profilePath = L"../../profile/PCIE-1840.xml";

#define startChannel       0
#define channelCount       1
#define sectionLength      10240
#define sectionCount       0
#define clockRate	         10000
#define cycles					2
// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define USER_BUFFER_SIZE channelCount*sectionLength
double userDataBuffer[USER_BUFFER_SIZE];

// Set trigger parameters
SignalDrop triggerSource = SigExtDigTrigger0;
TriggerAction triggerAction = DelayToStart;
ActiveSignal  triggerEdge   = RisingEdge;
int           triggerDelayCount = 600;
double        triggerLevel = 3.0;

//for trigger1 parameters 
SignalDrop trigger1Source = SigExtDigTrigger1;
TriggerAction trigger1Action = DelayToStop;
ActiveSignal  trigger1Edge   = RisingEdge;
int           trigger1DelayCount = 600;
double        trigger1Level = 3.0;

int32 recordIndex = 0;

void BDAQCALL OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void *userParam);

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
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

   // Step 1: Create a 'waveformAiCtrl' for streaming AI function.
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
	WaveformAiCtrl_addDataReadyHandler(wfAiCtrl, OnDataReadyEvent, NULL);

   do 
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode = ModeWrite;
      devInfo.ModuleIndex = 0;
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
		ret = Conversion_setClockRate(conversion, clockRate);
		CHK_RESULT(ret);
		record = WaveformAiCtrl_getRecord(wfAiCtrl);
		ret = Record_setSectionCount(record, sectionCount);//The 0 means setting 'streaming' mode.
      CHK_RESULT(ret);
      ret = Record_setSectionLength(record, sectionLength);
      CHK_RESULT(ret);
		ret = Record_setCycles(record, cycles);
		CHK_RESULT(ret);

      //Step 5: Trigger parameters setting
		aiFeatures = WaveformAiCtrl_getFeatures(wfAiCtrl);
		if (!AiFeatures_getRetriggerable(aiFeatures))
		{
			printf("This device don't support the retrigger fuction!");
			break;
		}
		//for trigger0
		trigger = WaveformAiCtrl_getTrigger(wfAiCtrl);
      ret = Trigger_setAction(trigger, triggerAction);
      CHK_RESULT(ret);
		/*************************************************************************************************/
		/*The different kinds of devices have different trigger source. The details see manual.
		/*In this example, we use the PCIE-1840 and set 'SigExtDigTrigger0' as the default trigger0 source.
		/**************************************************************************************************/
      ret = Trigger_setSource(trigger, triggerSource);
      CHK_RESULT(ret);
      ret = Trigger_setDelayCount(trigger, triggerDelayCount);
      CHK_RESULT(ret);
      ret = Trigger_setEdge(trigger, triggerEdge);
      CHK_RESULT(ret);
		/***********************************************************************************/
		/* If the triggerSource is 'DigitalSignal', 'setLevel' will not work.*/
		/* If not, please uncomment it.
		/***********************************************************************************/
      //ret = Trigger_setLevel(trigger, triggerLevel);
      //CHK_RESULT(ret);
      
      //for trigger1
      trigger1 = WaveformAiCtrl_getTrigger1(wfAiCtrl);
      ret = Trigger_setAction(trigger1, trigger1Action);
      CHK_RESULT(ret);
		/******************************************************************************************/
		/*Set 'SigExtDigTrigger1' as the default trigger1 source. The details see manual.
		/******************************************************************************************/
      ret = Trigger_setSource(trigger1, trigger1Source);
      CHK_RESULT(ret);
      ret = Trigger_setDelayCount(trigger1, trigger1DelayCount);
      CHK_RESULT(ret);
      ret = Trigger_setEdge(trigger1, trigger1Edge);
      CHK_RESULT(ret);
		/***********************************************************************************/
		/* If the triggerSource is 'DigitalSignal', 'setLevel' will not work.*/
		/* If not, please uncomment it.
		/***********************************************************************************/
      //ret =  Trigger_setLevel(trigger1, trigger1Level);
      //CHK_RESULT(ret);

      // Step 6: start Streaming AI.
		ret = WaveformAiCtrl_Prepare(wfAiCtrl);
		CHK_RESULT(ret);
      ret = WaveformAiCtrl_Start(wfAiCtrl);
      CHK_RESULT(ret);

      // Step 7: The device is acquiring data.
		printf("Streaming AI is in progress.\nplease wait...  any key to quit!\n\n");
		do
      {
         SLEEP(1);
      }while(!kbhit());

      // step 8: stop the operation if it is running.
      ret = WaveformAiCtrl_Stop(wfAiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 9: close device, release any allocated resource before quit.
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

void BDAQCALL OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
	ErrorCode ret = Success;
	double timeStamp = 0;
	int32 returnedCount = 0;
	int i = 0;
   WaveformAiCtrl * waveformAiCtrl = (WaveformAiCtrl *)sender;
	int32 getDataCount = (args->Count < USER_BUFFER_SIZE) ? args->Count : USER_BUFFER_SIZE;
	ret = WaveformAiCtrl_GetDataF64(waveformAiCtrl, getDataCount, userDataBuffer, 0, &returnedCount, &timeStamp, NULL, NULL);
	
	// in this demo, we show only the first sample of each channel's new data
	printf("Streaming AI data get data count is %d\n", returnedCount);
	printf("the first sample for each Channel are:\n");
   for(i = 0; i < channelCount; ++i)
   {
      printf("\nchannel %d:%10.6f\n",(i + startChannel), userDataBuffer[i]);   
   }
  
	if (ret == WarningRecordEnd)
	{
		++recordIndex;
		printf("recordIndex %ld is finished\n", recordIndex);   
	}
}