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
*     BufferedEventCounter.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use  Buffered Event Counter function.
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

namespace Counter_BufferedEventCounter
{
   class BufferedEventCounter
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

         // Step 1: Create a 'BufferedEventCounterCtrl' for Buffered Event Counter function.
         BufferedEventCounterCtrl bfdEventCounterCtrl = new BufferedEventCounterCtrl();
         
         // Step 2: Set the notification event Handler by which we can known the state of operation effectively. 
         bfdEventCounterCtrl.DataReady += new EventHandler<BfdCntrEventArgs>(bfdEventCounterCtrl_DataReady);

         try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            bfdEventCounterCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = bfdEventCounterCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 4: Set necessary parameters.
            byte[] chEnable = new byte[] { 1, 0, 0, 0 };
            bfdEventCounterCtrl.ChannelMap = chEnable;

            Record record = bfdEventCounterCtrl.Record;
            record.SectionLength = sectionLength;
            record.SectionCount = sectionCount;

            bfdEventCounterCtrl.SampleClkSrc = SignalDrop.SigExtDigClock;

            // Step5:  Set trigger parameters
            Trigger trigger = bfdEventCounterCtrl.Trigger;
            if (trigger != null)
            {
               trigger.Source = bfdEventCounterCtrl.Features.TriggerSources[0]; // set trigger source to 'SignalNone'.
            }

            // Step 6: Start Buffered Event Counter 
            errorCode = bfdEventCounterCtrl.Prepare();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            bfdEventCounterCtrl.Enabled = true;

            // Step 7: Read counting value: connect the input signal to channels you selected to get event counter value.
            Console.WriteLine(" BufferedEvenCounter is in progress...\n Connect the input signal to CNT#_CLK pin if you choose external clock!\n");
            Console.WriteLine(" any key to quit!\n");
            while (!Console.KeyAvailable)
            {
               Thread.Sleep(1000);
            }

            // Step 8: stop Buffered Event Counter
            bfdEventCounterCtrl.Enabled = false;
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
            // Step 9: Close device and release any allocated resource.
            bfdEventCounterCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static void bfdEventCounterCtrl_DataReady(object sender, BfdCntrEventArgs e)
      {
         Int32 returnedCount = 0;
         BufferedEventCounterCtrl bfdEventCounterCtrl = (BufferedEventCounterCtrl)sender;
         Record record = bfdEventCounterCtrl.Record;
         int sectionLength = record.SectionLength;
         Int32[] dataBuf = new Int32[sectionLength];
         int getDataCount = Math.Min(sectionLength, e.Count);
         Double starTime = 0.0;
         ErrorCode ret = bfdEventCounterCtrl.GetData(e.Channel, getDataCount, dataBuf, 0, out returnedCount, out starTime);
         if (ret == ErrorCode.Success)
         {
            Console.WriteLine(" Buffered Event Counting get data count is {0}", returnedCount);
            Console.WriteLine(" The first sample for channel {0} is {1}\n", e.Channel, dataBuf[0]);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
