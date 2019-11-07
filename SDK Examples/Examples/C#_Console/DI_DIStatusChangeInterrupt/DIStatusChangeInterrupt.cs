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
*    DIStatusChangeInterrupt.cs
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use DI Status Change Interrupt
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'enabledChannels' to decide which port is used.
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
namespace Dio_DIStatusChangeInterrupt
{
   class DIStatusChangeInterrupt
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is demo device, users can choose other devices according to their needs. 
         string deviceDescription = "DemoDevice,BID#0";
         string profilePath = "../../../profile/DemoDevice.xml";
         byte enabledChannels = 0xFF;
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'InstantDiCtrl' for DI function.
         InstantDiCtrl instantDiCtrl = new InstantDiCtrl();

         // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
         instantDiCtrl.ChangeOfState += new EventHandler<DiSnapEventArgs>(instantDiCtrl_ChangeOfState);

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
            Console.WriteLine(" Snap has started, any key to quit!\n");

            DiCosintPort[] diCosintPorts = instantDiCtrl.DiCosintPorts;
            if (diCosintPorts != null)
            {
               Console.WriteLine(" DI Port {0} is used to detect status change interrupt!", diCosintPorts[0].Port);
            }else{
               Console.WriteLine(" The device doesn't support status change interrupt!\n");
               return;
            }
            // Step 4: Set necessary parameters.
            // Using 'enabledChannels' mask to choose what port value to be enabled DI Status Change Interrupt.
            diCosintPorts[0].Mask = enabledChannels;

            // Step 5: Start StatusChangeInterrupt
            errorCode = instantDiCtrl.SnapStart();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 6: The device is working.
            Console.WriteLine(" Snap has started, any key to quit !");
            do
            {
               Thread.Sleep(1000);
            } while (!Console.KeyAvailable);

            // Step 7: Stop StatusChangeInterrupt
            diCosintPorts[0].Mask = 0x0;
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

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }

      static void instantDiCtrl_ChangeOfState(object sender, DiSnapEventArgs e)
      {
         Console.WriteLine("\n DI port {0} status change interrupt occurred!",e.SrcNum);

         InstantDiCtrl instantDiCtrl = (InstantDiCtrl)sender;
         for (int i = 0; i < instantDiCtrl.Features.PortCount; ++i)
         {
            Console.WriteLine("   DI port {0} status : 0x{1:x}", i, e.PortData[i]);
         }
      }
   }
}
