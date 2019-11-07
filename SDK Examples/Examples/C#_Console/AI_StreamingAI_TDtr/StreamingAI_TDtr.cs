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
*    StreamingAI_TDtr.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Streaming AI with Delay to Start Trigger function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*    7. Set the 'convertClkRate' to define the sampling count per second in Hz. 	  
*    8. Set the 'trigger parameters' to decide trigger property.
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
         //The default device of project is demo device, users can choose other devices according to their needs. 
         string deviceDescription = "DemoDevice,BID#0";
			string profilePath = "../../../profile/DemoDevice.xml";
         int startChannel = 0;
         int channelCount = 2;
			int sectionCount = 0;
         int sectionLength = 1024; 
			double convertClkRate = 1000.0;

         // Set trigger parameters
         TriggerAction triggerAction = TriggerAction.DelayToStart;
         ActiveSignal triggerEdge = ActiveSignal.RisingEdge;
         int triggerDelayCount = 1000;
         double triggerLevel = 3.0;

         //for trigger1 parameters
         TriggerAction trigger1Action = TriggerAction.DelayToStart;
         ActiveSignal trigger1Edge = ActiveSignal.RisingEdge;
         int trigger1DelayCount = 1000;
         double trigger1Level = 3.0;

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

            if (!waveformAiCtrl.Features.TriggerSupported)
            {
               throw new Exception("The device can not support trigger function! \n any key to quit.");
            }
            
            // Step 4: Set necessary parameters 
            Conversion conversion = waveformAiCtrl.Conversion;
            conversion.ChannelStart = startChannel;
            conversion.ChannelCount = channelCount;
            conversion.ClockRate = convertClkRate;
				Record record = waveformAiCtrl.Record;
				record.SectionCount = sectionCount;//The 0 means setting 'streaming' mode.
            record.SectionLength = sectionLength;

            //Step 5: Trigger parameters setting
            Trigger trigger = waveformAiCtrl.Trigger;
             if (trigger != null)
             {
                trigger.Action = triggerAction;
					 /******************************************************************************************/
					 /*The different kinds of devices have different trigger source. The details see manual.
					 /*In this example, we use the DemoDevice and set 'Ai channel 0' as the default trigger source.
					 /******************************************************************************************/
					 trigger.Source = waveformAiCtrl.Features.TriggerSources[1];//To DemoDevice, the 1 means 'Ai channel 0'.
                trigger.DelayCount = triggerDelayCount;
                trigger.Edge = triggerEdge;
                trigger.Level = triggerLevel;
             }else{
                throw new Exception("The device do not support Trigger function ! \n any key to quit.");
             }

             Trigger trigger1 = waveformAiCtrl.Trigger1;
             if (trigger1 != null)
             {
                trigger1.Action = trigger1Action;
                trigger1.Source = waveformAiCtrl.Features.Trigger1Sources[1];
                trigger1.DelayCount = trigger1DelayCount;
                trigger1.Edge = trigger1Edge;
                trigger1.Level = trigger1Level;
             }

            // Step 6: prepare the streaming AI. 
             errorCode = waveformAiCtrl.Prepare();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 7: The operation has been started.
            errorCode = waveformAiCtrl.Start();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            Console.WriteLine(" Streaming AI with Trigger is in progress... any key to quit !\n");

            // Step 8: The device is acquiring data.
            do 
            {
               Thread.Sleep(1000);

            } while (!Console.KeyAvailable);

            // step 9: Stop the operation if it is running.
            errorCode = waveformAiCtrl.Stop();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
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
            // Step 10: Close device and release any allocated resource.
            waveformAiCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static void waveformAiCtrl_Overrun(object sender, BfdAiEventArgs e)
      {
         Console.WriteLine("bufferedAi Overrun ! ");
         throw new Exception("The method or operation is not implemented.");
      }

      static void waveformAiCtrl_DataReady(object sender, BfdAiEventArgs e)
      {
         Console.WriteLine(" Buffered AI data ready:count = {0} ", e.Count);
         // in this demo, we show only ten sample for each channel's new data
         WaveformAiCtrl waveformAiCtrl = (WaveformAiCtrl)sender;
         int channelCountMax = waveformAiCtrl.Features.ChannelCountMax;
         int startChan = waveformAiCtrl.Conversion.ChannelStart;
         int channelCount = waveformAiCtrl.Conversion.ChannelCount;
         Int32 sectionLength = waveformAiCtrl.Record.SectionLength;
         Int32 getDataCount = sectionLength * channelCount;
			Int32 returnedCount = 0;

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