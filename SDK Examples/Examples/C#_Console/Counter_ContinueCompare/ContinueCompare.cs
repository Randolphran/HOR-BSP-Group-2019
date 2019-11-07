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
*     ContinueCompare.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use  Continue Compare Counter function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*    5  Set the 'comValueTab' as the comparison value table.
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
      static int[][] comValueTab = new int[2][];

      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
			string deviceDescription = "PCI-1784,BID#0";
         string profilePath = "../../../profile/PCI-1784.xml";
			int channelStart = 0;
			int channelCount = 1;

         // initialize the compare value table.
         comValueTab[0] = new int []{ 500, 3125, 8520 };
         comValueTab[1] = new int []{ 10000, 13040, 17550 };

			ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'UdCounterCtrl' for UpDown Counter function.
         UdCounterCtrl udCounterCtrl = new UdCounterCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
         udCounterCtrl.UdCntrEvent += new EventHandler<UdCntrEventArgs>(udCounterCtrl_ConCmpValue);

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
				for (int i = channelStart; i < channelStart + channelCount; i++)
				{
					udCounterCtrl.Channels[i % channelCountMax].CountingType = CountingType.AbPhaseX1;
				}

            //Step 6: Set compare table
            udCounterCtrl.CompareSetTable(channelStart, comValueTab[0].Length, (int[])comValueTab[0].Clone());

            // Step 7: Start UpDown Counter 
            udCounterCtrl.Enabled = true;

            // Step 8: Read counting value: connect the input signal to channels you selected to get event counter value.
            Console.WriteLine(" UpDown Counter is in progress...\nconnect the input signal to");
            Console.WriteLine(" any key to quit!\n\n");
            while (!Console.KeyAvailable)
            {
               Thread.Sleep(1000);
               int [] buffer = {0};
               udCounterCtrl.Read(1, buffer);
               Console.WriteLine("channel {0} Current  counts  :{1}", channelStart, buffer[0]);
            }

            // Step 9: stop UpDown Counter
            udCounterCtrl.CompareClear(channelStart);
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
            // Step 10: Close device and release any allocated resource.
            udCounterCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static int conCmpOccursCount = 0;
      static int tabIndex = 0;
      static EventId[] evntID = new EventId[]{EventId.EvtCntCompareTableEnd0,EventId.EvtCntCompareTableEnd1,EventId.EvtCntCompareTableEnd2,EventId.EvtCntCompareTableEnd3,
                                  EventId.EvtCntCompareTableEnd4,EventId.EvtCntCompareTableEnd5,EventId.EvtCntCompareTableEnd6,EventId.EvtCntCompareTableEnd7};
      static EventId[] evntCompID = new EventId[]{EventId.EvtCntPatternMatch0,EventId.EvtCntPatternMatch1,EventId.EvtCntPatternMatch2,EventId.EvtCntPatternMatch3,
                                          EventId.EvtCntPatternMatch4,EventId.EvtCntPatternMatch5,EventId.EvtCntPatternMatch6,EventId.EvtCntPatternMatch7};

      static void udCounterCtrl_ConCmpValue(object sender, UdCntrEventArgs e)
      {
         int channel = ((UdCounterCtrl)sender).ChannelStart;
         UdCounterCtrl udCounterCtrl = (UdCounterCtrl)sender;
         if (evntCompID[channel] == e.Id || evntID[channel] == e.Id)
         {
            Console.WriteLine("Channel {0} Compare occurs {1} time(times)", channel, ++conCmpOccursCount);
            Console.WriteLine("Compare value is {0}.\n", comValueTab[tabIndex % 2][(conCmpOccursCount-1) % 3]);
         }
         // Change the compare value table.
         if (evntID[channel] == e.Id)
         {
            tabIndex++;
            udCounterCtrl.CompareSetTable(channel, comValueTab[tabIndex % 2].Length, (int[])comValueTab[tabIndex % 2].Clone());
         } 
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}

