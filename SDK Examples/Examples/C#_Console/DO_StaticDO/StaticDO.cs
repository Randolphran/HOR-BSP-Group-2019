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
*    StaticDO.cs
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use Static DO function.
*
* Instructions for Running:
*    1. Set the 'deviceDescription' for opening the device.
*	  2. Set the 'profilePath' to save the profile path of being initialized device. 
*    3. Set the 'startPort'as the first port for Do .
*    4. Set the 'portCount'to decide how many sequential ports to operate Do.
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

namespace DO_StaticDO
{
   class StaticDO
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

         // Step 1: Create a 'InstantDoCtrl' for DO function.
         InstantDoCtrl instantDoCtrl = new InstantDoCtrl();
         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
            // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            instantDoCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = instantDoCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 3: Write DO ports
            //DioPort[] dioPort = instantDoCtrl.Ports;
            //dioPort[0].DirectionMask = 0xFF; //Setting port0 direction
            byte[] bufferForWriting = new byte[64];
            //byte dataForWriteBit = 0;//data is used to the 'WriteBit'.
				//int bit = 1;//the bit is used to the 'WriteBit'.

            for (int i = 0; i < portCount; ++i)
            {
               Console.WriteLine("Input a hexadecimal number for DO port {0} to output(for example, 0x11): ", startPort + i);
               string data = Console.ReadLine();
               bufferForWriting[i] = byte.Parse(data.Contains("0x")? data.Remove(0,2):data, System.Globalization.NumberStyles.HexNumber);
              /*
               //for WriteBit
               Console.WriteLine(" Input a hexadecimal number for DO port {0} to output(for example, 0x1 or 0x00): ", startPort + i);
               string data = Console.ReadLine();
               dataForWriteBit = byte.Parse(data.Contains("0x") ? data.Remove(0, 2) : data, System.Globalization.NumberStyles.HexNumber);
              */
            }
            errorCode = instantDoCtrl.Write(startPort, portCount, bufferForWriting);
            /************************************************************************/
            //errorCode = instantDoCtrl.WriteBit(startPort, bit, dataForWriteBit); 
            //NOTE:
            //Every channel has 8 bits, which be used to control 0--7 bit of anyone channel.
            //argument1:which port you want to contrl? For example, startPort is 0.
            //argument2:which bit you want to control? You can write 0--7, any number you want.
            //argument3:What status you want, open or close? 1 menas open, 0 means close.*/
            /************************************************************************/
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            Console.WriteLine("DO output completed !");
            // Read back the DO status. 
            // Note: 
            // For relay output, the read back must be deferred until the relay is stable.
            // The delay time is decided by the HW SPEC.
            // byte[] bufferForReading = new byte[64];
            // instantDoCtrl.DoRead(startPort, portCount, bufferForReading);
            // if (BioFailed(errorCode))
            // {
            //    throw new Exception();
            // }
            // Show DO ports' status
            // for (int i = startPort; i < portCount + startPort; ++i)
            // {
            //    Console.WriteLine("Now, DO port {0} status is:  0x{1:x}", i, bufferForReading[i - startPort]);
            // }
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
            instantDoCtrl.Dispose();
            Console.ReadKey(false);
         }

      }
      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }
   }
}
