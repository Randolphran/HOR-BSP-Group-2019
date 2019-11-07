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
*     BufferedPulseWidthMeasurement.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Buffered Pulse Width Measurement function.
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

namespace Counter_BufferedPulseWidthMeasurement
{
   class BufferedPulseWidthMeasurement
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

         // Step 1: Create a 'BufferedPwMeterCtrl' for Buffered Pulse Width Measurement function.
         BufferedPwMeterCtrl bfdPwMeterCtrl = new BufferedPwMeterCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively. 
         bfdPwMeterCtrl.DataReady += new EventHandler<BfdCntrEventArgs>(bfdPwMeterCtrl_DataReady);

         try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            bfdPwMeterCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = bfdPwMeterCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 4: Set necessary parameters
            byte[] chEnable = new byte[] { 1, 0, 0, 0 };
            bfdPwMeterCtrl.ChannelMap = chEnable;

            Record record = bfdPwMeterCtrl.Record;
            record.SectionLength = sectionLength;
            record.SectionCount = sectionCount;

            bfdPwMeterCtrl.SampleClkSrc = SignalDrop.SignalNone;

            //Step 5: Set Trigger parameters
            Trigger trigger = bfdPwMeterCtrl.Trigger;
            if (trigger != null)
            {
               trigger.Source = bfdPwMeterCtrl.Features.TriggerSources[0]; // set trigger source to 'SignalNone'.

            }

            //Step 6: Start BufferedPulseWidthMeasurement
            errorCode = bfdPwMeterCtrl.Prepare();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            bfdPwMeterCtrl.Enabled = true;

            // Step 5: Get Pulse Width value.
            Console.WriteLine(" BufferedPulseWidthMeasurement is in progress...\n Connect the input signal to the connector.");
            Console.WriteLine(" Any key to quit !\n\n");
            while (!Console.KeyAvailable)
            {
               Thread.Sleep(1000);
            }

            // Step 6: Stop BufferedPulseWidthMeasurement
            bfdPwMeterCtrl.Enabled = false;
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
            //step 7: Close device and release any allocated resource.
            bfdPwMeterCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }

      static void bfdPwMeterCtrl_DataReady(object sender, BfdCntrEventArgs e)
      {
         Int32 returnedCount = 0;
         BufferedPwMeterCtrl bfdPwMeterCtrl = (BufferedPwMeterCtrl)sender;
         Record record = bfdPwMeterCtrl.Record;
         int sectionLength = record.SectionLength;
         PulseWidth[] dataBuf = new PulseWidth[sectionLength];
         int getDataCount = Math.Min(sectionLength, e.Count);
         Double startTime = 0.0;
         ErrorCode ret = bfdPwMeterCtrl.GetData(e.Channel, getDataCount, dataBuf, 0, out returnedCount, out startTime);
         if (ret == ErrorCode.Success)
         {
            Console.Write("Buffered PwMeter get data count is {0}.\n", returnedCount);
            Console.WriteLine("The first sample for channel {0}: High Period:{1} s, Low Period: {2} s", e.Channel, Math.Round(dataBuf[0].HiPeriod, 6, MidpointRounding.AwayFromZero), Math.Round(dataBuf[0].LoPeriod, 6, MidpointRounding.AwayFromZero));
         }
      }
   }
}
