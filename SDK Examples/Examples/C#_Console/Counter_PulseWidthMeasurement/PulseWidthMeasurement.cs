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
*     PulseWidthMeasurement.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Pulse Width Measurement function.
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

namespace Counter_PulseWidthMeasurement
{
   class PulseWidthMeasurement
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is demo device, users can choose other devices according to their needs. 
			string deviceDescription = "DemoDevice,BID#0";
			string profilePath = "../../../profile/DemoDevice.xml";
			int channelStart = 0;
			int channelCount = 1;
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'PwMeterCtrl' for Pulse Width Measurement function.
         PwMeterCtrl pwMterCtrl = new PwMeterCtrl();

         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            pwMterCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = pwMterCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 3: Set necessary parameters
            pwMterCtrl.ChannelStart = channelStart;
				pwMterCtrl.ChannelCount = channelCount;

            //Step 4:Start PulseWidthMeasurement
            pwMterCtrl.Enabled = true;

            // Step 5: Get Pulse Width value.
            Console.WriteLine(" PulseWidthMeasurement is in progress...\n Connect the input signal to the connector.");
            Console.WriteLine(" Any key to quit !\n\n");
            while (!Console.KeyAvailable)
            {
               Thread.Sleep(1000);
               //get event count value per second  Math.Round( 3.455, 2, MidpointRounding.AwayFromZero)
               Console.WriteLine(" High Period:{0} s, Low Period: {1} s", Math.Round(pwMterCtrl.Value.HiPeriod, 6, MidpointRounding.AwayFromZero), Math.Round(pwMterCtrl.Value.LoPeriod, 6, MidpointRounding.AwayFromZero));
            }

            // Step 6: Stop PulseWidthMeasurement
            pwMterCtrl.Enabled = false;
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
            pwMterCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
