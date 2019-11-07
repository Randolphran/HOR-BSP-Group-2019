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
*    DelayedPulseGeneration.cs
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Delayed Pulse Generation function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the start channel of the counter to operate
*	  4  Set the 'channelCount' as the channel count of the counter to operate.
*    5  set the 'delayCount' to decide delay time for selected channel.
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

namespace Counter_DelayedPulseGeneration
{
   class DelayedPulseGeneration
   {
      static int delayedPulseOccursCount = 0;

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
         int delayCount = 10;
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'OneShotCtrl' for Delayed Pulse Generation function.
         OneShotCtrl oneShotCtrl = new OneShotCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
         oneShotCtrl.OneShot += new EventHandler<CntrEventArgs>(oneShotCtrl_OneShot);

         try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            oneShotCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = oneShotCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 4: Set necessary parameters
            oneShotCtrl.ChannelStart = channelStart;
				oneShotCtrl.ChannelCount = channelCount;
				int channelCountMax = oneShotCtrl.Features.ChannelCountMax;
				for (int i = 0; i < channelStart + channelCount; i++)
				{
					oneShotCtrl.Channels[i % channelCountMax].DelayCount = delayCount;					
				}

            // Step 5: Start DelayedPulseGeneration. 
            Console.WriteLine(" DelayedPulseGeneration is in progress...");
            Console.WriteLine(" give a low level signal to Gate pin and Test the pulse signal on the Out pin !");
            Console.WriteLine(" any key to quit !");
            oneShotCtrl.Enabled = true;

            // Step 6: Do anything you are interesting while the device is working.
            while( !Console.KeyAvailable )
            {
               Thread.Sleep(1000);
            }

            // Step 7: stop DelayedPulseGeneration function
            oneShotCtrl.Enabled = false;

         } catch(Exception e)
         {
            // Something is wrong
            string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                          : e.Message;
            Console.WriteLine(errStr);
         }
         finally
         {
            // Step 8: Close device and release any allocated resource.
            oneShotCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
     
      static void oneShotCtrl_OneShot(object sender, CntrEventArgs e)
      {  
         Console.WriteLine("\n Channel{0}'s Delayed Pulse occurs {1} time(times)\n", e.Channel, ++delayedPulseOccursCount);
      }
   }
}
