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
*    AsynOneBufferedAI_TDtp.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Asynchronous One Buffered AI with Delay to Stop Trigger function.
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

namespace AI_AsynchronousOneBufferedAI
{
   class AsynchronousOneBufferedAI
   {
      // set which trigger be used for this demo, trigger0(0) or trigger1(1).
      static int triggerUsed = 0;

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

         // Set trigger parameters
         TriggerAction triggerAction = TriggerAction.DelayToStop;
         ActiveSignal triggerEdge = ActiveSignal.RisingEdge;
         int triggerDelayCount = 1000;
         double triggerLevel = 3.0;

         //for trigger1 parameters
         TriggerAction trigger1Action = TriggerAction.DelayToStop;
         ActiveSignal trigger1Edge = ActiveSignal.RisingEdge;
         int trigger1DelayCount = 1000;
         double trigger1Level = 3.0;

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

            //Step 5: Trigger parameters setting
            if (triggerUsed == 0)
            {
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
               }
               else
               {
                  throw new Exception("The device do not support trigger function! \n any key to quit.");
               } 
            } 
            else if(triggerUsed == 1)
            {
               Trigger trigger1 = waveformAiCtrl.Trigger1;
               if (trigger1 != null)
               {
                  trigger1.Action = trigger1Action;
						trigger1.Source = waveformAiCtrl.Features.Trigger1Sources[1];
                  trigger1.DelayCount = trigger1DelayCount;
                  trigger1.Edge = trigger1Edge;
                  trigger1.Level = trigger1Level;
               }
               else
               {
                  throw new Exception("The device do not support trigger1 function! \n any key to quit.");
               }
            }

            // Step 6: prepare the buffered AI. 
            errorCode = waveformAiCtrl.Prepare();
            if (BioFailed(errorCode))
            {
                throw new Exception();
            }

            // Step 7: start Asynchronous Buffered AI, 'Asynchronous' means the method returns immediately
            // after the acquisition has been started. The 'bufferedAiCtrl_Stopped' method will be called
            // after the acquisition is completed.
            errorCode = waveformAiCtrl.Start();
            if (BioFailed(errorCode))
            {
                throw new Exception();
            }
            Console.WriteLine(" AsynchronousOneBufferedAI is in progress...\n");

            // Step 8: The device is acquiring data.
            do 
            {
               Thread.Sleep(1000);
            } while (!Console.KeyAvailable);

            // step 9: Stop the operation if it is running.
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
            // Step 10: close device, release any allocated resource before quit.
            waveformAiCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      //  process the acquired data
      static void waveformAiCtrl_Stopped(object sender, BfdAiEventArgs e)
      {
         Console.Write(" Acquisition has completed, all channel sample count is " + e.Count.ToString() + ".\n");
         WaveformAiCtrl waveformAiCtrl = (WaveformAiCtrl)sender;

         int channelCountMax = waveformAiCtrl.Features.ChannelCountMax;
         int startChan = waveformAiCtrl.Conversion.ChannelStart;
         int chanCount = waveformAiCtrl.Conversion.ChannelCount;
         Int32 sectionLength = waveformAiCtrl.Record.SectionLength;
         Int32 getDataCount = sectionLength * chanCount;
         // e.Count notifies that how many samples had been gathered in the 'Stopped' event. 
         double[] allChanData = new double[getDataCount];
         getDataCount = Math.Min(getDataCount, e.Count);
			Int32 returnedCount = 0;
         waveformAiCtrl.GetData(getDataCount, allChanData, 0, out returnedCount);
         int triggerPoint = 0;
         if (triggerUsed == 0)
         {
            triggerPoint = returnedCount/chanCount - waveformAiCtrl.Trigger.DelayCount;
         }else if (triggerUsed == 1)
         {
				triggerPoint = returnedCount / chanCount - waveformAiCtrl.Trigger1.DelayCount;
         }
         Console.Write(" The total data count is {0}, trigger point is {1}\n",returnedCount,triggerPoint);
         Console.WriteLine(" The first sample each channel are:\n");
         for (int i = 0; i < chanCount; ++i)
         {
             Console.WriteLine(" Channel {0}: {1,13:f8}", (i % chanCount + startChan) % channelCountMax,allChanData[i]);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
