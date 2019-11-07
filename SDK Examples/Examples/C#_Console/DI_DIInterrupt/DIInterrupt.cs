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

/******************************************************************************
*
* Windows Example:
*    DIInterrupt.cs
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use DI Interrupt
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
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

namespace DI_DIInterrupt
{
   class DIInterrupt
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following  parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is demo device, users can choose other devices according to their needs. 
         string deviceDescription = "DemoDevice,BID#0";
         string profilePath = "../../../profile/DemoDevice.xml";
			ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'InstantDiCtrl' for DI function.
         InstantDiCtrl instantDiCtrl = new InstantDiCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
         instantDiCtrl.Interrupt += new EventHandler<DiSnapEventArgs>(instantDiCtrl_Interrupt);
         try
         {
            // Step 3: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            instantDiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = instantDiCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            DiintChannel[] diintChannels = instantDiCtrl.DiintChannels;
            if (diintChannels != null)
            {
               Console.WriteLine(" DI channel {0} is used to detect interrupt!\n", diintChannels[0].Channel);
            }
            else{
               Console.WriteLine(" The device doesn't support DI channel interrupt!\n");
               return;
            }

            // Step 4: Set necessary parameters.
            diintChannels[0].Enabled = true;

            // Step 5: Start DIInterrupt
            errorCode = instantDiCtrl.SnapStart();
            if (BioFailed(errorCode))
            {
                throw new Exception();
            }
            Console.WriteLine(" DI Snap has started, any key to quit !");

            // Step 6: The device is working.
            do 
            {
               Thread.Sleep(1000);
            } while (!Console.KeyAvailable);

            // Step 7: Stop DIInterrupt
            diintChannels[0].Enabled = false;
            errorCode = instantDiCtrl.SnapStop();
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
            // Step 8: Close device, release any allocated resource.
            instantDiCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static void instantDiCtrl_Interrupt(object sender, DiSnapEventArgs e)
      {
         Console.WriteLine(" DI channel {0} interrupt occurred!", e.SrcNum);
         InstantDiCtrl instantDiCtrl = (InstantDiCtrl)sender;
               
         for (int j = 0; j < instantDiCtrl.Features.PortCount; ++j)
         {
            Console.WriteLine(" DI port {0} status is 0x: {1:x}", j, e.PortData[j]);
         }
         Console.WriteLine("\n");
      }

      static bool BioFailed(ErrorCode err)
      {
        return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}