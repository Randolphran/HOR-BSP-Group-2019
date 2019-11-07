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
*    DIInterrupt.cpp
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use DI snap function with a channel interrupt event
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startPort' as the first port for Di scanning.
*    4. Set the 'portCount' to decide how many sequential ports to operate Di scanning.

* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
//typedef unsigned char byte;
#define  deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32    startPort = 0;
int32    portCount = 1;

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 
// This class is used to deal with 'DIInterrupt' Event, we should overwrite the virtual function DiSnapEvent.
void BDAQCALL OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void *userParam)
{
 //show snap data.
   printf(" DI Interrupt channel is %d\n",args->SrcNum);
   for ( int32 i = startPort;i < startPort + portCount; ++i )
   {
      printf(" DI port %d status:  0x%X\n\n", i, args->PortData[i-startPort]);
   }
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'InstantDiCtrl' for DI function.
   InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();

	// Step 2: Set the notification event Handler by which we can known the state of operation effectively.
	instantDiCtrl->addInterruptHandler(OnDiSnapEvent, NULL);
   do
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = instantDiCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = instantDiCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
       Array<DiintChannel>* interruptChans = instantDiCtrl->getDiintChannels();
		if (interruptChans == NULL)
		{
			printf(" The device doesn't support DI interrupt!\n");
			waitAnyKey();
			return 0;
		}
		// In this demo, we are using the first available one.
      interruptChans->getItem(0).setEnabled(true);
      printf(" DI channel %d is used to detect interrupt!\n\n", interruptChans->getItem(0).getChannel());

      // Step 5: Start DIInterrupt
      ret = instantDiCtrl->SnapStart();
      CHK_RESULT(ret);

      // Step 6: The device is working.
      printf(" Snap has started, any key to quit !\n");
      do
      {
         SLEEP(1);
      }while (!kbhit());

      // Step 7: Stop DIInterrupt
      ret = instantDiCtrl->SnapStop();
      CHK_RESULT(ret);
   }while(false);
  
	// Step 8: Close device, release any allocated resource.
	instantDiCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();
   } 
   return 0;
}


