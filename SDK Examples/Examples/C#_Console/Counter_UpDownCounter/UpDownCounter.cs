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
*     UpDownCounter.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use  UpDown Counter function.
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
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Reflection;
using System.Runtime.InteropServices;
using Automation.BDaq;

namespace Counter_UpDownCounter
{
   class UpDownCounter
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
			string deviceDescription = "PCI-1784,BID#0";
         string profilePath = "../../../profile/PCI-1784.xml";
			int channelStart = 0;
			int channelCount = 1;
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'UdCounterCtrl' for UpDown Counter function.
         UdCounterCtrl udCounterCtrl = new UdCounterCtrl();

         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
				// in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            udCounterCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = udCounterCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 3: Set necessary parameters.
				udCounterCtrl.ChannelStart = channelStart;
				udCounterCtrl.ChannelCount = channelCount;

            // Step 4: Set counting type for UpDown Counter
				int channelCountMax = udCounterCtrl.Features.ChannelCountMax; 
				for (int i = channelStart; i < channelStart + channelCount; i++)
				{
					udCounterCtrl.Channels[i % channelCountMax].CountingType = CountingType.AbPhaseX1;
				}
            // Step 5: Start UpDown Counter 
            udCounterCtrl.Enabled = true;

            // Step 6: Read counting value: connect the input signal to channels you selected to get event counter value.
            Console.WriteLine(" UpDown Counter is in progress...\nconnect the input signal to");
            Console.WriteLine(" any key to quit!\n\n");
            while (!Console.KeyAvailable)
            {
               Thread.Sleep(1000);
               int[] buffer = {0};
               udCounterCtrl.Read(1, buffer);
               Console.WriteLine(" channel {0} Current UpDown conter counts  :{1}\n", channelStart, buffer[0]);
            }

            // Step 6: stop UpDown Counter
            udCounterCtrl.Enabled = false;
         }
         catch(Exception e)
         {
            // Something is wrong
            string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                          : e.Message;
            Console.WriteLine(errStr);
         }
         finally
         {
            // Step 7: Close device and release any allocated resource.
            udCounterCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
