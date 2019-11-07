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
*    PatternMatchInterrupt.c
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use DI snap function with a pattern match interrupt event
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startPort' as the first port for Di scanning.
*    4. Set the 'portCount' to decide how many sequential ports to operate Di scanning.
*    5. Set pattern match channels and values for supported ports in system device manager configuration.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "../inc/compatibility.h"
#include "../../../inc/bdaqctrl.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define  deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32    startPort = 0; 
int32    portCount = 1; 

//This is function declaration. the function is used to deal with 'pattern match' Event.
void BDAQCALL OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam);

void waitAnyKey()
{
	do {SLEEP(1);} while (!kbhit());
}

int main(int argc, char* argv[])
{
	ErrorCode ret = Success;

   DiPmintPort * diPmintPort = NULL;
	IArray * pmintPort = NULL;
	
   // Step 1: Create a 'InstantDiCtrl' for DI function.
	InstantDiCtrl * instantDiCtrl = InstantDiCtrl_Create();
	
   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
      InstantDiCtrl_addPatternMatchHandler(instantDiCtrl, OnDiSnapEvent, NULL);

	do 
	{	
		// Step 3: Select a device by device number or device description and specify the access mode.
		// in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
		DeviceInformation devInfo;
		devInfo.DeviceNumber = -1;
		devInfo.DeviceMode = ModeWrite;
		devInfo.ModuleIndex = 0;
		wcscpy(devInfo.Description, deviceDescription);
		ret = InstantDiCtrl_setSelectedDevice(instantDiCtrl, &devInfo);
		CHK_RESULT(ret);
      ret = InstantDiCtrl_LoadProfile(instantDiCtrl, profilePath);//Loads a profile to initialize the device.

		// Step 4: Set necessary parameters
		pmintPort = InstantDiCtrl_getDiPmintPorts(instantDiCtrl);
		if (pmintPort == NULL)
		{
			printf(" The device doesn't support DI interrupt!\n");
			waitAnyKey();
			return 0;
		}
		// In this demo, we are using the first available one.
      diPmintPort = (DiPmintPort *)Array_getItem(pmintPort, 0);
		printf(" DI channel %d is used to detect interrupt!\n\n", DiPmintPort_getPort(diPmintPort));
      
      // Using 'pmEnableChans' mask to choose which channels to be enabled DI Pattern Match Interrupt.
      // ret = DiPmintPort_setMask(diPmintPort, pmEnableChans); 
      // Using 'pmValue' to set which port value to be triggered DI Pattern Match Interrupt.
      // ret = DiPmintPort_setPattern(diPmintPort, pmValue);

		// Step 5: Start DIInterrupt.
		ret =  InstantDiCtrl_SnapStart(instantDiCtrl);
		CHK_RESULT(ret);

		// Step 6: The device is working.
		printf(" Snap has start, any key to quit !\n");
		do 
		{
			SLEEP(1);
		} while (!kbhit());

		// Step 7: Stop DIInterrupt.
		ret = InstantDiCtrl_SnapStop(instantDiCtrl);
		CHK_RESULT(ret);
	} while (FALSE);

	// Step 8: Close device, release any allocated resource.
	InstantDiCtrl_Dispose(instantDiCtrl);

	// If something wrong in this execution, print the error code on screen for tracking.
	if(BioFailed(ret))
	{
		printf("Some error occurred. And the last error code is 0x%X.\n", ret);
		waitAnyKey();
	} 
	return 0;
}

void BDAQCALL OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void *userParam)
{
	int i;
   unsigned char bufferForSnap[MAX_DIO_PORT_COUNT];
   memcpy(bufferForSnap, args->PortData, MAX_DIO_PORT_COUNT);
   //show snap data.
	printf(" DI Interrupt channel is %d\n", args->SrcNum);
	for ( i = startPort; i < startPort + portCount; ++i )
	{
		printf(" DI port %d status: 0x%X\n\n", i, bufferForSnap[i - startPort]);
	}
}
