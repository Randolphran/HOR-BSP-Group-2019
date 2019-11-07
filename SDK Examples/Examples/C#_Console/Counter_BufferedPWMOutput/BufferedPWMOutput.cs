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
* Windows  Example:
*    BufferedPWMOutput.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Buffered PWM Output function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'chEnable' to enabled channel of the counter to operate
*    4  set the 'pulseWidth' to decide the period of pulse for selected channel.
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

namespace Counter_BufferedPWMOutput
{
   class BufferedPWMOutput
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is demo device, users can choose other devices according to their needs. 
         string deviceDescription = "PCIE-1813,BID#15";
         string profilePath = "../../../profile/PCIE-1813.xml";
         int intervalCount = 2048;
         int samples = 4096;
         int userBufLength = 4096;
         PulseWidth []dataBuf = new PulseWidth[userBufLength];
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'BufferedPwModulatorCtrl' for Buffered PWM Output function.
         BufferedPwModulatorCtrl bfdPwModulatorCtrl = new BufferedPwModulatorCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively. 
         bfdPwModulatorCtrl.DataTransmitted += new EventHandler<BfdCntrEventArgs>(bfdPwModulatorCtrl_DataTransmitted);

          try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            bfdPwModulatorCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = bfdPwModulatorCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 4: Set necessary parameters.
            int channelCountMax = bfdPwModulatorCtrl.Features.ChannelCountMax;
            byte[] chEnable = new byte[] { 1, 0, 0, 0 };
            bfdPwModulatorCtrl.ChannelMap = chEnable;

            bfdPwModulatorCtrl.SampleClkSrc = SignalDrop.SignalNone;

            bfdPwModulatorCtrl.IntervalCount = intervalCount;
            bfdPwModulatorCtrl.Samples = samples;
            bfdPwModulatorCtrl.Streaming = true;
            
             // Step 5: Set Trigger parameters
            Trigger trigger = bfdPwModulatorCtrl.Trigger;
            if (trigger != null)
            {
               trigger.Source = bfdPwModulatorCtrl.Features.TriggerSources[0];// set trigger source to 'SignalNone'.
            }

            for (int i = 0; i < userBufLength; i++)
            {
               dataBuf[i].HiPeriod = 0.8;
               dataBuf[i].LoPeriod = 0.2;
            }
            for (int i = 0; i < channelCountMax; i++ )
            {
               if (chEnable[i] == 1){
                  bfdPwModulatorCtrl.SetData(i, userBufLength, dataBuf);
               }
            }

            // Step 6: start BufferedPWMOutput
            Console.WriteLine(" BufferedPWMOutput is in progress...\n Test signal to the Out pin !");
            Console.WriteLine(" Any key to quit !\n");
            
            bfdPwModulatorCtrl.Prepare();

            bfdPwModulatorCtrl.Enabled = true;

		      while(!Console.KeyAvailable)
		      {
			      Thread.Sleep(1000);         
		      }

            // Step 7: Stop BufferedPWMOutput
            bfdPwModulatorCtrl.Enabled = false;
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
            //Step 6: Close device and release any allocated resource.
            bfdPwModulatorCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }

      static void bfdPwModulatorCtrl_DataTransmitted(object sender, BfdCntrEventArgs e)
      {
         Console.WriteLine(" BufferedPWMOut Data Transmitted: channel:{0}, count:{1}", e.Channel, e.Count);
      }
   }
}
