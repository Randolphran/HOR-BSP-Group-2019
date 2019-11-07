/*******************************************************************************
Copyright (c) 1983-2016 Advantech Co., Ltd.
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
*     ContinueCompare.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Continue Compare Counter function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
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
#define     deviceDescription L"PCI-1784,BID#0"
const wchar_t* profilePath = L"../../profile/PCI-1784.xml";
int32       channelStart = 0;
int32       channelCount = 1;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

int comValueTab[2][3] = {{50, 100, 150},{1000, 1304, 1755}};

int conCmpOccursCount = 0;
int tabIndex = 0;
int const evntID[8] = {EvtCntCompareTableEnd0,EvtCntCompareTableEnd1,EvtCntCompareTableEnd2,EvtCntCompareTableEnd3,
                       EvtCntCompareTableEnd4,EvtCntCompareTableEnd5,EvtCntCompareTableEnd6,EvtCntCompareTableEnd7};
int const evntCompID[8] = {EvtCntPatternMatch0,EvtCntPatternMatch1,EvtCntPatternMatch2,EvtCntPatternMatch3,
                           EvtCntPatternMatch4,EvtCntPatternMatch5,EvtCntPatternMatch6,EvtCntPatternMatch7};
// This function is used to deal with 'Cntr' Event.
void BDAQCALL OnCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam)
{
   UdCounterCtrl *udCounterCtrl = (UdCounterCtrl*)sender;
   int channel = udCounterCtrl->getChannelStart();
   if (evntCompID[channel] == args->Id || evntID[channel] == args->Id)
   {
      printf("Channel %d Compare occurs %d time(times)\n", channel, ++conCmpOccursCount);
      printf("Compare value is %d\n\n",comValueTab[tabIndex % 2][(conCmpOccursCount-1) % 3]);
   }
   if (evntID[channel] == args->Id)
   {
      printf("Channel %d Compare end\n", channel);
      tabIndex++;
      udCounterCtrl->CompareSetTable(channel, 3, comValueTab[tabIndex % 2]);
   }
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'UdCounterCtrl' for UpDown Counter function.
   UdCounterCtrl * udCounterCtrl = UdCounterCtrl::Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   udCounterCtrl->addUdCntrEventHandler(OnCounterEvent, NULL);

   do
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = udCounterCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = udCounterCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);
      
      // Step 4: Set necessary parameters.
      ret = udCounterCtrl->setChannelStart(channelStart);
      CHK_RESULT(ret);
      ret = udCounterCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);

      // Step 5: Set counting type for UpDown Counter 
      /******************************************************************************************************************/
		/*In this example, we use the PCIE-1784 and set 'PulseDirection' as the default CountingType.The details see manual.
		/******************************************************************************************************************/
      Array<UdChannel>* udChannel = udCounterCtrl->getChannels();
      for (int32 i = channelStart; i < channelStart + channelCount; i++)
      {
         ret = udChannel->getItem(i).setCountingType(PulseDirection);
			CHK_RESULT(ret);
      }

      //Step 6: Set compare table
      ret = udCounterCtrl->CompareSetTable(udCounterCtrl->getChannelStart(), 3, &comValueTab[0][0]);
      CHK_RESULT(ret);

      // Step 7: Start UpDown Counter 
      ret= udCounterCtrl->setEnabled(true);
      CHK_RESULT(ret);

      // Step 8: Read counting value: connect the input signal to channels you selected to get UpDown counter value.
      printf("UnDown counter is in progress...\nconnect the input signal to\n ");
      printf("any key will stop UnDown counter!\n\n");
      while ( !kbhit())
      {
         SLEEP(1);//get event UpDown count value per second
         int32 value = 0;
         ret = udCounterCtrl->Read(value);
         CHK_RESULT(ret);
         printf("channel %d Current UpDown count: %u \n\n", channelStart, value);
      }
      
      // Step 9: stop UpDown Counter
      ret = udCounterCtrl->CompareClear();
      CHK_RESULT(ret);
      ret = udCounterCtrl->setEnabled(false);
      CHK_RESULT(ret);
   }while(false);

	// Step 10: Close device and release any allocated resource.
	udCounterCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("\nSome error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   }  
   return 0;
}
