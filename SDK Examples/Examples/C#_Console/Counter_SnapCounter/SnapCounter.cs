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
*     SnapCounter.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Ssnap Counter function.
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
      static EventId [] srcID = new EventId[32];
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

         // Step 1: Create a 'UdCounterCtrl' for Snap Counter function.
         UdCounterCtrl udCounterCtrl = new UdCounterCtrl();
         
         // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
         udCounterCtrl.UdCntrEvent += new EventHandler<UdCntrEventArgs>(udCounterCtrl_SnapCounter); 
         try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            udCounterCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = udCounterCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 4: Set necessary parameters.
            udCounterCtrl.ChannelStart = channelStart;
				udCounterCtrl.ChannelCount = channelCount;

            // Step 5: Set counting type for UpDown Counter 
				int channelCountMax = udCounterCtrl.Features.ChannelCountMax;
				for (int i = channelStart; i < channelStart + channelCount; i++ )
				{
					udCounterCtrl.Channels[i % channelCountMax].CountingType = CountingType.AbPhaseX1;
				}
           
            // Step 6: Set snap source and start Snap function 
            EventId[] snapSource = udCounterCtrl.Features.UdSnapEventSources;

            for (int i = 0; i < snapSource.Length; ++i ){
               srcID[i] = snapSource[i];}
            udCounterCtrl.SnapStart(snapSource[0]);

            // Step 7: Start UpDown Counter 
            udCounterCtrl.Enabled = true;

            // Step 8: Read counting value: connect the input signal to channels you selected to get event counter value.
            Console.WriteLine(" Snap Counter is in progress...\nconnect the input signal to");
            Console.WriteLine(" any key to quit!\n\n");
            while (!Console.KeyAvailable)
            {
               Thread.Sleep(1000);
               int[] buffer = { 0 };
               udCounterCtrl.Read(1, buffer);
               Console.WriteLine("\nchannel {0} Current counts  :{1}\n", channelStart, buffer[0]);
            }

            //Step 9: Stop Snap function
            udCounterCtrl.SnapStop(snapSource[0]);

            // Step 10: stop UpDown Counter
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
            // Step 11: Close device and release any allocated resource.
            udCounterCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      // Event handler for Snap function 
      static void udCounterCtrl_SnapCounter(object sender, UdCntrEventArgs e)
      {
         int length = ((UdCounterCtrl)sender).Features.UdSnapEventSources.Length;
         for (int srcLen = 0; srcLen < length; ++srcLen )
         {
            if (srcID[srcLen] == e.Id)
            {
               UInt32 data = 0;
               for (int i = 0; i < e.Length; ++i)
               {
                  data = (UInt32)e.Data[i];
                  Console.WriteLine("\nSource {0} Snap occurs. Snap data is: {1}", srcID[srcLen].ToString(), data);
               }
               break;
            }
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
