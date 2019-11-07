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
*    PWMOutput.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use PWM Output function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*    5  set the 'pulseWidth' to decide the period of pulse for selected channel.
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

namespace Counter_PWMOutput
{
   class PWMOutput
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
         PulseWidth pulseWidth = new PulseWidth(0.08, 0.02);
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'PwModulatorCtrl' for PWM Output function.
         PwModulatorCtrl pwModulatorCtrl = new PwModulatorCtrl();

          try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            pwModulatorCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = pwModulatorCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 3: Set necessary parameters.
            pwModulatorCtrl.ChannelStart = channelStart;
				pwModulatorCtrl.ChannelCount = channelCount;
				int channelCountMax = pwModulatorCtrl.Features.ChannelCountMax;
				for (int i = 0; i < channelStart + channelCount; i++)
				{
					pwModulatorCtrl.Channels[i % channelCountMax].PulseWidth = pulseWidth;					
				}

            // Step 4: start PWMOutput
            Console.WriteLine(" PWMOutput is in progress...\n Test signal to the Out pin !");
            Console.WriteLine(" Any key to quit !\n");
            pwModulatorCtrl.Enabled = true;

		      while(!Console.KeyAvailable)
		      {
			      Thread.Sleep(1000);         
		      }

            // Step 5: Stop PWMOutput
            pwModulatorCtrl.Enabled = false;
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
            pwModulatorCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
