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
*    StaticDI.cs
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use Static DI function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device. 
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startPort' as the first port for Di scanning.
*    4. Set the 'portCount' to decide how many sequential ports to operate Di scanning.
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

namespace DI_StaticDI
{
   class StaticDI
   {
      static void Main(string[] args)
      {
         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is demo device, users can choose other devices according to their needs. 
         string deviceDescription = "DemoDevice,BID#0";
         string profilePath = "../../../profile/DemoDevice.xml";
         int startPort = 0;
         int portCount = 1;
         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'InstantDiCtrl' for DI function.
         InstantDiCtrl instantDiCtrl = new InstantDiCtrl();

         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            instantDiCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = instantDiCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            // read DI ports' status and show.
            //set prot direction
            //DioPort[] dioPort = instantDiCtrl.Ports;
            //dioPort[0].DirectionMask = 0x00;//Setting port0 direction
            Console.WriteLine("Reading ports' status is in progress..., any key to quit!\n");
            byte[] buffer = new byte[64];
            //byte data = 0;//data is used to the API ReadBit.
            //int  bit = 0;//bit is used to the API ReadBit.
            do
            {
               // Step 3: Read DI ports' status and show.
               errorCode = instantDiCtrl.Read(startPort, portCount, buffer);
               //errorCode = instantDiCtrl.ReadBit(startPort, bit, out data);
               if (BioFailed(errorCode))
               {
                  throw new Exception();
               }
               //Show ports' status
               for (int i = 0; i < portCount; ++i)
               {
                  Console.WriteLine(" DI port {0} status : 0x{1:x}\n", startPort + i, buffer[i]);
                  /************************************************************************/
                  //Console.WriteLine(" DI port {0} status : 0x{1:x}\n", startPort + i, data);
                  //NOTE:
                  //argument1:which port you want to control? For example, startPort is 0.
                  //argument2:which bit you want to control? You can write 0--7, any number you want.
                  //argument3:data is used to save the result.                                                                     
                  /************************************************************************/
               }
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
            instantDiCtrl.Dispose();
            Console.ReadKey(false);
         }
      }
      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
