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
*    AsynchronousOneBufferedAI.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Asynchronous One Buffered AI function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*	  7. Set the 'convertClkRate' to define the sampling count per second in Hz. 	
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

namespace AI_AsynchronousOneBufferedAI
{
   class AsynchronousOneBufferedAI
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

         // Step 1: Create a 'WaveformAiCtrl' for Streaming AI function.
         WaveformAiCtrl waveformAiCtrl = new WaveformAiCtrl();
         
         // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
         waveformAiCtrl.Stopped += new EventHandler<BfdAiEventArgs>(waveformAiCtrl_Stopped);

         try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            waveformAiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = waveformAiCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 4: Set necessary parameters. 
            Conversion conversion = waveformAiCtrl.Conversion;
            conversion.ChannelStart = startChannel;
            conversion.ChannelCount = channelCount;
            conversion.ClockRate = convertClkRate;
				Record record = waveformAiCtrl.Record;
				record.SectionCount = sectionCount;//The sectionCount is nonzero value, which means 'One Buffered' mode.
            record.SectionLength = sectionLength;

            // Step 5: prepare the buffered AI. 
            errorCode = waveformAiCtrl.Prepare();
            if (BioFailed(errorCode))
            {
                throw new Exception();
            }

            // Step 6: start Asynchronous Buffered AI, 'Asynchronous' means the method returns immediately
            // after the acquisition has been started. The 'bufferedAiCtrl_Stopped' method will be called
            // after the acquisition is completed.
            errorCode = waveformAiCtrl.Start();
            if (BioFailed(errorCode))
            {
                throw new Exception();
            }
            Console.WriteLine(" AsynchronousOneBufferedAI is in progress...\n");

            // Step 7: The device is acquiring data.
            do 
            {
               Thread.Sleep(1000);
            } while (!Console.KeyAvailable);

            // step 8: Stop the operation if it is running.
            waveformAiCtrl.Stop();
         }
         catch (Exception e)
         {
            // Something is wrong
            string errStr = BioFailed(errorCode)? " Some error occurred. And the last error code is " + errorCode.ToString()
                                                   :e.Message;
            Console.WriteLine(errStr);
         }
         finally
         {
            // Step 9: close device, release any allocated resource before quit.
            waveformAiCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      //  process the acquired data
      static void waveformAiCtrl_Stopped(object sender, BfdAiEventArgs e)
      {
         Console.Write(" Acquisition has completed, sample count is " + e.Count.ToString() + ".\n");
         WaveformAiCtrl waveformAiCtrl = (WaveformAiCtrl)sender;
         int channelCountMax = waveformAiCtrl.Features.ChannelCountMax;
         int startChan = waveformAiCtrl.Conversion.ChannelStart;
         int channelCount = waveformAiCtrl.Conversion.ChannelCount;
         Int32 sectionLength = waveformAiCtrl.Record.SectionLength;
         Int32 getDataCount = sectionLength * channelCount;
			Int32 returnedCount = 0;
         // e.Count notifys that how many samples had been gathered in the 'Stopped' event. 
         double[] allChanData = new double[getDataCount];
         getDataCount = Math.Min(getDataCount, e.Count);
         waveformAiCtrl.GetData(getDataCount, allChanData, 0, out returnedCount);
			Console.Write("Asynchronous One Buffered AI get data count is {0}", returnedCount);
         Console.WriteLine(" The first sample each channel are:\n");
         for (int i = 0; i < channelCount; ++i)
         {
             Console.WriteLine(" Channel {0}: {1,13:f8}", (i % channelCount + startChan) % channelCountMax,allChanData[i]);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
