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
*     BufferedUpDownCounter.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Bufferde UpDown Counter function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'chEnable' to enabled channel of the counter to operate
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

namespace Counter_BufferedUpDownCounter
{
   class BufferedUpDownCounter
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is pcie-1813.
         string deviceDescription = "PCIE-1813,BID#15";
         string profilePath = "../../../profile/PCIE-1813.xml";
         int sectionLength = 1024;
         int sectionCount = 0;
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'BufferedUdCounterCtrl' for Buffered UpDown Counter function.
         BufferedUdCounterCtrl bfdUdCounterCtrl = new BufferedUdCounterCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively. 
         bfdUdCounterCtrl.DataReady += new EventHandler<BfdCntrEventArgs>(bfdUdCounterCtrl_DataReady);

         try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
				// in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            bfdUdCounterCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = bfdUdCounterCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 3: Set necessary parameters.
            byte[] chEnable = new byte[] { 1, 0, 0, 0 };
            bfdUdCounterCtrl.ChannelMap = chEnable;

            Record record = bfdUdCounterCtrl.Record;
            record.SectionLength = sectionLength;
            record.SectionCount = sectionCount;

            bfdUdCounterCtrl.SampleClkSrc = SignalDrop.SigExtDigClock;

            // Step 4: Set trigger parameters
            Trigger trigger = bfdUdCounterCtrl.Trigger;
            if (trigger != null)
            {
               trigger.Source = bfdUdCounterCtrl.Features.TriggerSources[0]; // set trigger source to 'SignalNone'.
            }

            // Step 5: Set counting type for Buffered UpDown Counter
				int channelCountMax = bfdUdCounterCtrl.Features.ChannelCountMax; 
				for (int i = 0; i < channelCountMax; i++)
				{
               if(chEnable[i] == 1){
                  bfdUdCounterCtrl.Channels[i % channelCountMax].CountingType = CountingType.PulseDirection;
               }
				}
            // Step 6: Start Buffered UpDown Counter 
            bfdUdCounterCtrl.Prepare();

            bfdUdCounterCtrl.Enabled = true;

            // Step 6: Read counting value: connect the input signal to channels you selected to get value.
            Console.WriteLine(" Buffered UpDown Counter is in progress...\n Connect the input signal to channels you selected to get value!");
            Console.WriteLine(" any key to quit!\n\n");
            while (!Console.KeyAvailable)
            {
               Thread.Sleep(1000);
            }

            // Step 6: stop Buffered UpDown Counter
            bfdUdCounterCtrl.Enabled = false;
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
            bfdUdCounterCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }

      static void bfdUdCounterCtrl_DataReady(object sender, BfdCntrEventArgs e)
      {
         int returnedCount = 0;
         BufferedUdCounterCtrl bfdUdCounterCtrl = (BufferedUdCounterCtrl)sender;
         Record record = bfdUdCounterCtrl.Record;
         int sectionLength = record.SectionLength;
         Int32[] dataBuf = new Int32[sectionLength];
         Int32 getDataCount = Math.Min(sectionLength, e.Count);
         Double starTime = 0.0;
         ErrorCode ret = bfdUdCounterCtrl.GetData(e.Channel, getDataCount, dataBuf, 0, out returnedCount, out starTime);
         if (ret == ErrorCode.Success)
         {
            Console.WriteLine("Buffered Updown Counter get data count is {0}\n", returnedCount);
            Console.WriteLine(" The first sample for channel {0} is {1}\n", e.Channel, dataBuf[0]);
         }
      }
   }
}
