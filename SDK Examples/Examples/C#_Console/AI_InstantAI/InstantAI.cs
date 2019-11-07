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
*    InstantAI.cs
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Instant AI function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startChannel' as the first channel for scan analog samples
*    4. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
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

namespace AI_InstantAI
{
   class InstantAI
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
         const int channelCount = 2;

         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'InstantAiCtrl' for Instant AI function.
         InstantAiCtrl instantAIContrl = new InstantAiCtrl();
      
         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            instantAIContrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = instantAIContrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            Console.WriteLine(" Snap has started, any key to quit!\n");

            // Step 3: Read samples and do post-process, we show data here.
            Console.WriteLine(" InstantAI is in progress... any key to quit !\n");
            int channelCountMax = instantAIContrl.Features.ChannelCountMax;
            double[] scaledData = new double[channelCount];//the count of elements in this array should not be less than the value of the variable channelCount
            for (int i = 0; i < channelCount; ++i)
            {
               Console.Write("    channel: {0}", (i % channelCount + startChannel) % channelCountMax);
            }
            Console.WriteLine();
            do
            {
               // read samples, just scaled data in this demo
               errorCode = instantAIContrl.Read(startChannel, channelCount, scaledData);
               if (BioFailed(errorCode))
               {
                  throw new Exception();
               }
               // process the acquired samples
               for (int i = 0; i < channelCount; ++i)
               {
                  Console.Write(" {0,13:f8}", scaledData[i]);
               }
               Console.Write("\n");
               Thread.Sleep(1000);
            } while (!Console.KeyAvailable);
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
            // Step 4: Close device and release any allocated resource.
            instantAIContrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
