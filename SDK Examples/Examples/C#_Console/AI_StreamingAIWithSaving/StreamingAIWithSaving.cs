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
*    StreamingAIWithSaving.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Streaming AI With Saving function.
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
using System.IO;
using Automation.BDaq;

namespace AI_StreamingAIWithSaving
{
   class Program
   {
     static  string savingFilePath = "..\\C#_Data.bin";
     static  FileStream fileStream = null;
     static  int i = 1;
     static  int RealFileSize = 0;
     static  int SingleSavingFileSize = 1024 * sizeof(double);
     static  int RequirementFileSize = 10240 * sizeof(double);

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
         openFile();

         // Step 2: Set the notification event Handler by which we can kownn the state of operation effectively.
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

            // Step 4: Set necessary parameters for Streaming AI operation, 
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
            errorCode = waveformAiCtrl.Start();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            Console.WriteLine(" StreamingAI is in progress... any key to quit !\n");
            
            // Step 7: Tthe device is acquiring data.
            do
            {
               Thread.Sleep(1000);
            } while ((sizeOfFile() < RequirementFileSize) ? true : false);// any key to quit.

            // step 8: Stop the operation if it is running.
            errorCode = waveformAiCtrl.Stop();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
         }
         catch (System.Exception e)
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
            fileStream.Close();
            fileStream.Dispose();
         }
      }

      static void waveformAiCtrl_Overrun(object sender, BfdAiEventArgs e)
      {
         Console.WriteLine("Streaming AI is Over run ! ");
         //throw new Exception("Maybe one method or operation is busy.");
      }

      static void waveformAiCtrl_DataReady(object sender, BfdAiEventArgs e)
      {
         //Console.WriteLine(" Streaming AI data ready:count = {0},offset = {1} ", e.Count, e.Offset);
         WaveformAiCtrl waveformAiCtrl = (WaveformAiCtrl)sender;
         Conversion conversion = waveformAiCtrl.Conversion;
         int channelCount = conversion.ChannelCount;
         Int32 sectionLength = waveformAiCtrl.Record.SectionLength;
         Int32 getDataCount = channelCount * sectionLength;
         // buffer section length, when 'DataReady' event been signaled, driver renew data count is e.count. 
         if (e.Count > channelCount)
         {
            double[] Data = new double[getDataCount];
            getDataCount = Math.Min(getDataCount, e.Count);
            byte[] savingBuffer = new byte[SingleSavingFileSize];
            waveformAiCtrl.GetData(getDataCount, Data);
            Buffer.BlockCopy(Data, 0, savingBuffer, 0, SingleSavingFileSize);
            fileStream.Write(savingBuffer, 0, SingleSavingFileSize);
            RealFileSize += SingleSavingFileSize;
            Console.WriteLine("The real-time size of file is {0} byte\n\n", RealFileSize);
				Console.WriteLine("Executed {0} time!\n\n", i++);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }

      static void openFile()
      {
         if (File.Exists(savingFilePath))
         {
            fileStream = new FileStream(savingFilePath, FileMode.Truncate);
         }
         else
         {
            fileStream = File.OpenWrite(savingFilePath);
         }
      }

      static long sizeOfFile()
      {
         long size = fileStream.Seek(0, SeekOrigin.End);
         Console.WriteLine("File Size is {0}", size);
         return size;
      }
   }
}
