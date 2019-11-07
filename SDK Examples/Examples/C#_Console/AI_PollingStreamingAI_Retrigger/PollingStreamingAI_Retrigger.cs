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
*    PollingStreamingAI_Retrigger.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Polling Streaming AI with retrigger function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples  
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    5. Set the 'sectionLength' as the length of data section for Buffered AI.
*	  6. Set the 'sectionCount' as the count of data section for Buffered AI.
*	  7. Set the 'Cycles'to decide the count of a series of data which is continuous in time domain.
*	  8. Set the 'clockRate' to define the sampling count per second in Hz. 
*    9. Set the 'trigger parameters' to decide trigger property.
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


namespace PollingStreamingAI_Retrigger
{
   class PollingStreamingAI_Retrigger
   {
      static void Main(string[] args)
      {
         ErrorCode errorCode = ErrorCode.Success;
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         string deviceDescription = "PCIE-1840,BID#0";
			string profilePath = "../../../profile/PCIE-1840.xml";
         int startChannel = 0;
         int channelCount = 1;
			int sectionLength = 10240;
			int sectionCount = 0;
			int cycles = 2;
         double convertClkRate = 10000.0;
			
			// Set trigger parameters
			SignalDrop triggerSource = SignalDrop.SigExtDigTrigger0;
			TriggerAction triggerAction = TriggerAction.DelayToStart;
			ActiveSignal triggerEdge = ActiveSignal.RisingEdge;
			int triggerDelayCount = 600;
			double triggerLevel = 3.0;

			//for trigger1 parameters
			SignalDrop trigger1Source = SignalDrop.SigExtDigTrigger1;
			TriggerAction trigger1Action = TriggerAction.DelayToStop;
			ActiveSignal trigger1Edge = ActiveSignal.RisingEdge;
			int trigger1DelayCount = 600;
			double trigger1Level = 3.0;

         // Step 1: Create a 'WaveformAiCtrl' for Buffered AI function.
         WaveformAiCtrl waveformAiCtrl = new WaveformAiCtrl();

         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use ModesWrite mode so that we can fully control the device, including configuring, sampling, etc.
            waveformAiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = waveformAiCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

				if (!waveformAiCtrl.Features.Retriggerable)
				{
					throw new Exception("The device do not support Retrigger function! \n any key to quit.");
				}

            // Step 3: Set necessary parameters.
            Conversion conversion = waveformAiCtrl.Conversion;
            conversion.ChannelStart = startChannel;
            conversion.ChannelCount = channelCount;
            conversion.ClockRate = convertClkRate;
				Record record = waveformAiCtrl.Record;
				record.SectionCount = sectionCount;//The 0 means setting 'streaming' mode.
            record.SectionLength = sectionLength;
				record.Cycles = cycles;

            //Step 4: Trigger parameters setting
            Trigger trigger = waveformAiCtrl.Trigger;
            if (trigger != null)
            {
               trigger.Action = triggerAction;
					/*************************************************************************************************/
					/*The different kinds of devices have different trigger source. The details see manual.
					/*In this example, we use the PCIE-1840 and set 'SigExtDigTrigger0' as the default trigger0 source.
					/**************************************************************************************************/
					trigger.Source = triggerSource;
               trigger.DelayCount = triggerDelayCount;
               trigger.Edge = triggerEdge;
					/***********************************************************************************/
					/* If the triggerSource is 'DigitalSignal', 'trigger.Level' will not work.*/
					/* If not, please uncomment it.
					/***********************************************************************************/
               //trigger.Level = triggerLevel;
            }
            else
            {
               throw new Exception("The device do not support trigger function! \n any key to quit.");
            }

            //for trigger1
				if (waveformAiCtrl.Features.TriggerCount > 1)
				{
					Trigger trigger1 = waveformAiCtrl.Trigger1;
					trigger1.Action = trigger1Action;
					/******************************************************************************************/
					/*Set 'SigExtDigTrigger1' as the default trigger1 source. The details see manual.
					/******************************************************************************************/
					trigger1.Source = trigger1Source;
					trigger1.DelayCount = trigger1DelayCount;
					trigger1.Edge = trigger1Edge;
					/***********************************************************************************/
					/* If the triggerSource is 'DigitalSignal', 'trigger1.Level' will not work.*/
					/* If not, please uncomment it.
					/***********************************************************************************/
					//trigger1.Level = trigger1Level;
				} 
				else
				{
               throw new Exception("The device do not support trigger1 function! \n any key to quit.");
				}

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
				Console.WriteLine(" Polling infinite acquisition is in progress...\n");

            // Step 7:GetData with Polling Style 
				Int32 userBufferSize = channelCount * sectionLength;
				double[] dataBuffer = new double[userBufferSize];
				int recordIndex = 0;
				Int32 returnedCount = 0;
				do
            {
					errorCode = waveformAiCtrl.GetData(userBufferSize, dataBuffer, -1, out returnedCount);//The timeout value is -1, meaning infinite waiting.
					if (BioFailed(errorCode))
					{
						throw new Exception();
					}
					Console.Write("Polling Streaming AI get data count is {0}", returnedCount);
               Console.WriteLine(" The first sample each channel are:\n");
               for (int i = 0; i < channelCount; ++i)
               {
                  Console.WriteLine(" Channel {0}: {1,13:f8}", (i % channelCount + startChannel), dataBuffer[i]);
               }

					if (errorCode == ErrorCode.WarningRecordEnd)
					{
						Console.WriteLine("\nrecordIndex {0} is finished\n", ++recordIndex);
					}
				} while (errorCode != ErrorCode.WarningFuncStopped);

            // step 8: Stop the operation if it is running.
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
            // Step 9: close device, release any allocated resource before quit.
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
