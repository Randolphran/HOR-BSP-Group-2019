/*******************************************************************************
Copyright (c) 1983-2016 Advantech Co., Ltd.
********************************************************************************
THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY INFORMATION
WHICH IS THE PROPERTY OF ADVANTECH CORP., ANY DISCLOSURE, USE, OR REPRODUCTION,
WITHOUT WRITTEN AUTHORIZATION FROM ADVANTECH CORP., IS STRICTLY PROHIBITED. 
================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log: $
--------------------------------------------------------------------------------
 $NoKeywords:  $
*/
/******************************************************************************
*
* Windows Example:
*    SynchronousOneWaveformAO.cs
*
* Example Category:
*    AO
*
* Description:
*    This example demonstrates how to use Synchronous One Waveform AO function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device.     
*    3  Set the 'channelStart' as the first channel for analog data Output.
*    4  Set the 'channelCount' to decide how many sequential channels to output analog data.
*    5  Set the 'sampleCount' to decide the capacity of buffer in kernel 
*    6  Set the 'convertClkRate' to define the sampling count per second in Hz.
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

namespace AO_SynchronousOneWaveformAO
{
   class SynchronousOneWaveformAO
   {
      const int oneWavePointCount = 1024*128; //define how many data to makeup a waveform period.
      enum WaveStyle
      {
         Sine = 0,
         Sawtooth,
         Square
      };

      static void Main(string[] args)
      {

         //-----------------------------------------------------------------------------------
         // Configure the following parameters before running the demo
         //-----------------------------------------------------------------------------------
         //The default device of project is demo device, users can choose other devices according to their needs. 
         string deviceDescription = "DemoDevice,BID#0";
         string profilePath = "../../../profile/DemoDevice.xml";
         int channelStart = 0;
         int channelCount = 1;
         int sampleCount = oneWavePointCount;
         int convertClkRate = 1000;

         ErrorCode errorCode = ErrorCode.Success;

         // Step 1: Create a 'BufferedAoCtrl' for buffered AO function.
         BufferedAoCtrl bufferedAoCtrl = new BufferedAoCtrl();

         try
         {
            // Step 2: Select a device by device number or device description and specify the access mode.
				// in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
            bufferedAoCtrl.SelectedDevice = new DeviceInformation(deviceDescription);
				errorCode = bufferedAoCtrl.LoadProfile(profilePath);//Loads a profile to initialize the device.
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }

            // Step 3: Set necessary parameters.
            ScanChannel scanChannel = bufferedAoCtrl.ScanChannel;
            scanChannel.ChannelStart = channelStart;
            scanChannel.ChannelCount = channelCount;
            scanChannel.Samples = sampleCount;
            scanChannel.IntervalCount = sampleCount;

            bufferedAoCtrl.ConvertClock.Rate = convertClkRate;
            
            // Step 4: prepare the buffered AO. 
            bufferedAoCtrl.Prepare();
            // Generate waveform data
            int userBufferLength = channelCount * sampleCount;
            double[] scaledWaveForm = new double[userBufferLength];
            errorCode = GenerateWaveform(bufferedAoCtrl, channelStart, channelCount, scaledWaveForm, userBufferLength, WaveStyle.Sine);
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
            bufferedAoCtrl.SetData(scaledWaveForm.Length, scaledWaveForm);

            
          
            // Step 5: Start Synchronous One Waveform AO, 'Synchronous' indicates using synchronous mode,
            // which means the method will not return until the operation is completed.
            Console.WriteLine("\n Outputting data, please wait...\n");
            errorCode = bufferedAoCtrl.RunOnce();
            if (BioFailed(errorCode))
            {
               throw new Exception();
            }
           
            Console.WriteLine("\n Buffered AO is completed. any key to quit !");
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
            // Step 6: Close device, release any allocated resource.
            bufferedAoCtrl.Dispose();
            Console.ReadKey(false);
         }
      }

      static bool BioFailed(ErrorCode err)
      {
         return err < ErrorCode.Success && err >= ErrorCode.ErrorHandleNotValid;
      }

      static ErrorCode GenerateWaveform(BufferedAoCtrl buffAoCtrl, int channelStart, int channelCount, double[] waveBuffer, int SamplesCount, WaveStyle style)
      {
         ErrorCode ret = ErrorCode.Success;
         int channel = 0;
         int chanCountMax = buffAoCtrl.Features.ChannelCountMax;
         int oneWaveSamplesCount = SamplesCount / channelCount;

         StringBuilder description = new StringBuilder();
         ValueUnit unit;
         MathInterval[] ranges = new MathInterval[chanCountMax];
         ValueRange valRange;

         //get every channel's value range ,include external reference voltage value range which you should key it in manually.
         for (int i = 0; i < chanCountMax; i++)
         {
             valRange = buffAoCtrl.Channels[i].ValueRange;
             if (ValueRange.V_ExternalRefBipolar == valRange || valRange == ValueRange.V_ExternalRefUnipolar)
             {
                 if (buffAoCtrl.Features.ExternalRefAntiPolar)
                 {
                     double referenceValue;

                     if (valRange == ValueRange.V_ExternalRefBipolar)
                     {
								 referenceValue = buffAoCtrl.Channels[i].ExtRefBipolar;
                         if (referenceValue >= 0)
                         {
                             ranges[i].Max = referenceValue;
                             ranges[i].Min = 0 - referenceValue;
                         }
                         else
                         {
                             ranges[i].Max = 0 - referenceValue;
                             ranges[i].Min = referenceValue;
                         }
                     }
                     else
                     {
								 referenceValue = buffAoCtrl.Channels[i].ExtRefUnipolar;
                         if (referenceValue >= 0)
                         {
                             ranges[i].Max = 0;
                             ranges[i].Min = 0 - referenceValue;
                         }
                         else
                         {
                             ranges[i].Max = 0 - referenceValue;
                             ranges[i].Min = 0;
                         }
                     }
                 }
                 else
                 {
                     double referenceValue;

                     if (valRange == ValueRange.V_ExternalRefBipolar)
                     {
								 referenceValue = buffAoCtrl.Channels[i].ExtRefBipolar;
                         if (referenceValue >= 0)
                         {
                             ranges[i].Max = referenceValue;
                             ranges[i].Min = 0 - referenceValue;
                         }
                         else
                         {
                             ranges[i].Max = 0 - referenceValue;
                             ranges[i].Min = referenceValue;
                         }
                     }
                     else
                     {
								 referenceValue = buffAoCtrl.Channels[i].ExtRefUnipolar;
                         if (referenceValue >= 0)
                         {
                             ranges[i].Max = referenceValue;
                             ranges[i].Min = 0;
                         }
                         else
                         {
                             ranges[i].Max = 0;
                             ranges[i].Min = 0 - referenceValue;
                         }
                     }
                 }
             }
             else
             {
                 ret = BDaqApi.AdxGetValueRangeInformation(valRange, 0, description, out ranges[i], out unit);
                 if (BioFailed(ret))
                 {
                     return ret;
                 }
             }
         }

         //generate waveform data and put them into the buffer which the parameter 'waveBuffer' give in, the Amplitude these waveform
         for (int i = 0; i < oneWaveSamplesCount; i++)
         {
             for (int j = channelStart; j < channelStart + channelCount; j++)
             {
                 //pay attention to channel rollback(when startChannel+channelCount>chanCountMax)
                 channel = j % (chanCountMax);

                 double amplitude = (ranges[channel].Max - ranges[channel].Min) / 2;
                 double offset = (ranges[channel].Max + ranges[channel].Min) / 2;
                 unsafe
                 {
                     switch (style)
                     {
                         case WaveStyle.Sine:
                             waveBuffer[i * channelCount + j - channelStart] = amplitude * (Math.Sin((double)i * 2.0 * Math.PI / oneWaveSamplesCount)) + offset;
                             break;

                         case WaveStyle.Sawtooth:
                             if ((i >= 0) && (i < (oneWaveSamplesCount / 4.0)))
                             {
                                 waveBuffer[i * channelCount + j - channelStart] = amplitude * (i / (oneWaveSamplesCount / 4.0)) + offset;
                             }
                             else
                             {
                                 if ((i >= (oneWaveSamplesCount / 4.0)) && (i < 3 * (oneWaveSamplesCount / 4.0)))
                                 {
                                     waveBuffer[i * channelCount + j - channelStart] = amplitude * ((2.0 * (oneWaveSamplesCount / 4.0) - i) / (oneWaveSamplesCount / 4.0)) + offset;
                                 }
                                 else
                                 {
                                     waveBuffer[i * channelCount + j - channelStart] = amplitude * ((i - oneWaveSamplesCount) / (oneWaveSamplesCount / 4.0)) + offset;
                                 }
                             }
                             break;

                         case WaveStyle.Square:
                             if ((i >= 0) && (i < (oneWaveSamplesCount / 2)))
                             {
                                 waveBuffer[i * channelCount + j - channelStart] = amplitude * 1 + offset;
                             }
                             else
                             {
                                 waveBuffer[i * channelCount + j - channelStart] = amplitude * (-1) + offset;
                             }
                             break;
                     }
                 }
             }
         }
         return ret;
      }
   }
}
