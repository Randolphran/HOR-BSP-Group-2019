/*******************************************************************************
Copyright (c) 1983-2016 Advantech Co., Ltd.
********************************************************************************
THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY INFORMATION
WHICH IS THE PROPERTY OF ADVANTECH CORP., ANY DISCLOSURE, USE, OR REPRODUCTION,
WITHOUT WRITTEN AUTHORIZATION FROM ADVANTECH CORP., IS STRICTLY PROHIBITED. 

================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log:  $ 
--------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows Example:
*    SynchronousOneBufferedAI.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Synchronous One Buffered AI.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' which can get from system device manager for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*    7. Set the 'convertClkRate' to define the sampling count per second in Hz.  
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
using System.Linq;

namespace PollingOneBufferedAI
{
   class PollingOneBufferedAI
   {
      static void Main(string[] args)
      {
         ErrorCode errorCode = ErrorCode.Success;
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //----------------------------------------------------------------------------------- 
			string deviceDescription = "DemoDevice,BID#0";
			string profilePath = "../../../profile/DemoDevice.xml";
         int startChannel = 0;
         int channelCount = 2;
			int sectionLength = 1024;
			int sectionCount = 1;
         double convertClkRate = 1000.0;

         // Step 1: Create a 'WaveformAiCtrl' for Buffered AI function.
         WaveformAiCtrl waveformAiCtrl = new WaveformAiCtrl();
         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            waveformAiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = waveformAiCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 3: Set necessary parameters.
            Conversion conversion = waveformAiCtrl.Conversion;
            conversion.ChannelStart = startChannel;
            conversion.ChannelCount = channelCount;
            conversion.ClockRate = convertClkRate;
				Record record = waveformAiCtrl.Record;
				record.SectionCount = sectionCount;//The sectionCount is nonzero value, which means 'One Buffered' mode.
            record.SectionLength = sectionLength;

            // Step 4: prepare the buffered AI. 
            errorCode = waveformAiCtrl.Prepare();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

				// Step 5: The operation has been started.
            errorCode = waveformAiCtrl.Start();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            Console.WriteLine("Polling One Buffered AI is in progress...\n");

            // Step 6: GetData
				Int32 userBufferSize = channelCount * sectionLength * sectionCount;
				double[] dataBuffer = new double[userBufferSize];
				Int32 returnedCount = 0;
				errorCode = waveformAiCtrl.GetData(userBufferSize, dataBuffer, -1, out returnedCount);//The timeout value is -1, meaning infinite waiting.
				if (errorCode == ErrorCode.Success)
				{
					Console.Write("Acquisition has completed, all channel sample count is {0}\n", returnedCount);               						
					Console.WriteLine("The first sample each channel are:");
					for (int i = 0; i < channelCount; i++)
					{
						Console.WriteLine("Channel {0}: {1,13:f8}", (i % channelCount + startChannel), dataBuffer[i]);
					}
				}

            // step 7: Stop the operation if it is running.
            waveformAiCtrl.Stop();
         }
         catch (System.Exception e)
         {
            // Something is wrong
            string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                                   : e.Message;
            Console.WriteLine(errStr);
         }
         finally
         {
            // Step 8: close device, release any allocated resource before quit.
            waveformAiCtrl.Dispose();
            Console.ReadKey(false);
         }
      }
      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
