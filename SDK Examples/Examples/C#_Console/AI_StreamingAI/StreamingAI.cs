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
*    StreamingAI.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Streaming AI function.
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

namespace AI_StreamAI
{
   class StreamAI
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is demo device, users can set other devices according to their needs. 
         string deviceDescription = "DemoDevice,BID#0";
			string profilePath = "../../../profile/DemoDevice.xml";
         int startChannel = 0;       
         int channelCount = 2;
         int sectionLength = 1024;
			int sectionCount = 0;
			double convertClkRate = 1000.0;
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'WaveformAiCtrl' for Streaming AI function.
         WaveformAiCtrl waveformAiCtrl = new WaveformAiCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively. 
         waveformAiCtrl.DataReady += new EventHandler<BfdAiEventArgs>(waveformAiCtrl_DataReady);
         waveformAiCtrl.Overrun += new EventHandler<BfdAiEventArgs>(waveformAiCtrl_Overrun);

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

            // Step 4: Set necessary parameter
            Conversion conversion = waveformAiCtrl.Conversion;
            conversion.ChannelStart = startChannel;
            conversion.ChannelCount = channelCount;
            conversion.ClockRate = convertClkRate;
				Record record = waveformAiCtrl.Record;
				record.SectionCount = sectionCount;//The 0 means setting 'streaming' mode.
            record.SectionLength = sectionLength;

            // Step 5: prepare the Streaming AI. 
            errorCode = waveformAiCtrl.Prepare();
            if (BioFailed(errorCode))
            {
                throw new Exception();
            }

            // Step 6: The operation has been started
            // We can get samples via event handlers.
            errorCode = waveformAiCtrl.Start();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            Console.WriteLine(" StreamingAI is in progress... any key to quit !\n");

            // Step 7: The device is acquiring data.
            do 
            {
               Thread.Sleep(1000);
            } while (!Console.KeyAvailable);// any key to quit. 

            // step 8: Stop the operation if it is running.
            errorCode = waveformAiCtrl.Stop();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
         }
         catch(Exception e)
         {
            // If something wrong in this execution, print the error code on screen for tracking.
             string errStr = BioFailed(errorCode) ? " Some error occurred. And the last error code is " + errorCode.ToString()
                                                     : e.Message;
             Console.WriteLine(errStr);
         }
         finally
         {
            // Step 9: Close device and release any allocated resource.
            waveformAiCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static void waveformAiCtrl_Overrun(object sender, BfdAiEventArgs e)
      {
         Console.WriteLine("Streaming AI is Over run ! ");
         //throw new Exception("Maybe one method or operation is busy.");
      }

      static void waveformAiCtrl_DataReady(object sender, BfdAiEventArgs e)
      {
         Console.WriteLine(" Streaming AI data ready:count = {0},offset = {1} ", e.Count, e.Offset);
			Int32 returnedCount = 0;
         WaveformAiCtrl waveformAiCtrl = (WaveformAiCtrl)sender;
         Conversion conversion = waveformAiCtrl.Conversion;
         Record record = waveformAiCtrl.Record;
         int channelCountMax = waveformAiCtrl.Features.ChannelCountMax;
         int startChan = conversion.ChannelStart;
         int channelCount = conversion.ChannelCount;
         int sectionLengt = record.SectionLength;
         int getDataCount = sectionLengt * channelCount;

         // buffer section length, when 'DataReady' event been signaled, driver renew data count is e.count. 
        if (e.Count > channelCount)
         {
            double[] sectionBuffer = new double[getDataCount];
            getDataCount = Math.Min(getDataCount, e.Count);
				waveformAiCtrl.GetData(getDataCount, sectionBuffer, 0, out returnedCount);
				Console.Write("Streaming AI get data count is {0}", returnedCount);
            Console.WriteLine(" The first sample for each channel are:");
             for (int j = 0; j < channelCount; ++j)
            {
               Console.WriteLine("  channel {0}: {1}", (j % channelCount + startChan) % channelCountMax, sectionBuffer[j]);
            }
            Console.WriteLine();
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
