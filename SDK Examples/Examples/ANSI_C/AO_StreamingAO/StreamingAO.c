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
*    StreamingAO.cpp
*
* Example Category:
*    AO
*
* Description:
*    This example demonstrates how to use Streaming AO voltage function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device. 
*	  2  Set the 'profilePath' to save the profile path of being initialized device. 
*    3  Set the 'channelStart' as the first channel for analog data Output.
*    4  Set the 'channelCount' to decide how many sequential channels to output analog data.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../inc/compatibility.h"
#include "../../../inc/bdaqctrl.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define  ONE_WAVE_POINT_COUNT  2048 //define how many data points to makeup a waveform period.
#define  SAMPLES_PER_CHAN ONE_WAVE_POINT_COUNT*4
#define  RATE_PER_CHAN  1000
#define  action 1

#define  deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32    startChannel = 0;
int32    channelCount = 1;

typedef enum tagWaveStyle{ Sine, Sawtooth, Square }WaveStyle;

//function GenerateWaveform: generate one waveform for each selected analog data output channel 
ErrorCode GenerateWaveform( BufferedAoCtrl *, int32, int32, double *, int32, WaveStyle);
ErrorCode FillWaveBuffer( BufferedAoCtrl *, double *);

// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void * sender, BfdAoEventArgs * args, void *userParam);

// This function is used to deal with 'DataTransmitted' Event.
void BDAQCALL OnDataTransmittedEvent(void * sender, BfdAoEventArgs * args, void *userParam);

// This function is used to deal with 'TransStopped' Event.
void BDAQCALL OnTransStoppedEvent(void * sender, BfdAoEventArgs * args, void *userParam);

void waitAnyKey()
{
   do {SLEEP(1);} while (!kbhit());
}

int main(int argc, char*argv[])
{
   ErrorCode ret = Success;
   ScanChannel * scanChannel = NULL;
   ConvertClock * convertClock = NULL;
   int32 waveBufferLen = 0;
   double * waveBuffer = NULL;
   
   // Step 1: Create a 'BufferedAoCtrl' for buffered AO function.
   BufferedAoCtrl * bfdAoCtrl = BufferedAoCtrl_Create();
   
   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   BufferedAoCtrl_addDataTransmittedHandler(bfdAoCtrl, OnDataTransmittedEvent, NULL);
   BufferedAoCtrl_addTransitStoppedHandler(bfdAoCtrl, OnTransStoppedEvent, NULL);
   BufferedAoCtrl_addStoppedHandler(bfdAoCtrl, OnStoppedEvent, NULL);

   do 
   {
      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode = ModeWrite;
      devInfo.ModuleIndex = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = BufferedAoCtrl_setSelectedDevice(bfdAoCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = BufferedAoCtrl_setStreaming(bfdAoCtrl, TRUE);
      CHK_RESULT(ret);
      ret = BufferedAoCtrl_LoadProfile(bfdAoCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);
      
      // Step 4: Set necessary parameters.
      scanChannel = BufferedAoCtrl_getScanChannel(bfdAoCtrl);
      convertClock = BufferedAoCtrl_getConvertClock(bfdAoCtrl);
      ret = ScanChannel_setChannelStart(scanChannel, startChannel);
      CHK_RESULT(ret);
      ret = ScanChannel_setChannelCount(scanChannel, channelCount);
      CHK_RESULT(ret);
      ret = ScanChannel_setSamples(scanChannel, SAMPLES_PER_CHAN);
      CHK_RESULT(ret);
      ret = ScanChannel_setIntervalCount(scanChannel, ONE_WAVE_POINT_COUNT);
      CHK_RESULT(ret);
      ret = ConvertClock_setRate(convertClock, RATE_PER_CHAN);
      CHK_RESULT(ret);

      // Step 5: Prepare the buffered AO. 
      ret = BufferedAoCtrl_Prepare(bfdAoCtrl);
      CHK_RESULT(ret);

      // Generate waveform data
      waveBufferLen = channelCount*SAMPLES_PER_CHAN*sizeof(double);
      waveBuffer = (double *)malloc(waveBufferLen);
      if (NULL == waveBuffer)
      {
         printf("Insufficient memory available\n");
         break;
      }
      FillWaveBuffer(bfdAoCtrl, waveBuffer);
      ret = BufferedAoCtrl_SetDataF64(bfdAoCtrl, channelCount*SAMPLES_PER_CHAN, waveBuffer);
      free(waveBuffer);
      CHK_RESULT(ret);
      
      // Step 6: Start streaming AO, 'streaming' indicates using asynchronous streaming mode,
      // which means the method returns immediately and output data continue to stop enforced.
      printf("Streaming AO is in progress.\n");
      printf("Please wait... any key to quit !\n");
      ret = BufferedAoCtrl_Start(bfdAoCtrl);
      CHK_RESULT(ret);

      // Step 7: The device is outputting data.
      do 
      {
         SLEEP(1);
      } while (!kbhit());
      
      // step 8: Stop the operation if it is running.
      ret = BufferedAoCtrl_Stop(bfdAoCtrl, action);
      CHK_RESULT(ret);
   } while (FALSE);
   
   // Step 9: Close device, release any allocated resource.
   BufferedAoCtrl_Dispose(bfdAoCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();// Wait any key to quit !
   }
   return 0;
}

void BDAQCALL OnStoppedEvent(void * sender, BfdAoEventArgs * args, void *userParam)
{
   printf("\nBufferedAO stopped: offset = %d, count = %d\n", args->Offset, args->Count);
}
void BDAQCALL OnDataTransmittedEvent(void * sender, BfdAoEventArgs * args, void *userParam)
{
   printf("data transmitted: offset = %d, count = %d\n", args->Offset, args->Count);
}
void BDAQCALL OnTransStoppedEvent(void * sender, BfdAoEventArgs * args, void *userParam)
{
   printf("\nEvtBufferedAo Transmit Stopped: offset = %d, count = %d\n", args->Offset, args->Count);
}

ErrorCode GenerateWaveform(BufferedAoCtrl * bfdAoCtrl, int32 channelStart, int32 channelCount, double * waveBuffer, int32 SamplesCount, WaveStyle style)
{
   ErrorCode ret                = Success;
   int32     channel            = 0;
   int32     channelCountMax    = 0;
   int32     oneWaveSampleCount = SamplesCount / channelCount;
   int32     i                  = 0;

   MathInterval   ranges[64];
   ValueRange     valRange;
   AnalogChannel * aoChannel = NULL;

   channelCountMax = AoFeatures_getChannelCountMax(BufferedAoCtrl_getFeatures(bfdAoCtrl));
   for (i = 0; i < channelCountMax; i++)
   {
      aoChannel = (AnalogChannel *)Array_getItem(BufferedAoCtrl_getChannels(bfdAoCtrl), i);

      valRange  = AoChannel_getValueRange(aoChannel);
      if (V_ExternalRefBipolar == valRange || valRange == V_ExternalRefUnipolar)
      {
         if (AoFeatures_getExternalRefAntiPolar(BufferedAoCtrl_getFeatures(bfdAoCtrl)))
         {
            double referenceValue;
            if (valRange == V_ExternalRefBipolar)
            {
					referenceValue = AoChannel_getExtRefBipolar(aoChannel);
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
					referenceValue = AoChannel_getExtRefUnipolar(aoChannel);
               if (referenceValue > 0)
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
            if (valRange == V_ExternalRefBipolar)
            {
               referenceValue = AoChannel_getExtRefBipolar(aoChannel);
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
               referenceValue = AoChannel_getExtRefUnipolar(aoChannel);
               if (referenceValue >= 0)
               {
                  ranges[i].Max = referenceValue;
                  ranges[i].Min = 0;
               } 
               else
               {
                  ranges[i].Max = 0;
                  ranges[i].Min = referenceValue;
               }
            }
         }
      }
      else
      {
         ret = AdxGetValueRangeInformation(valRange, 0, NULL, &ranges[i], NULL);
         if (BioFailed(ret))
         {
            return ret;
         }
      }
   }

   //generate waveform data and put them into the buffer which the parameter 'waveBuffer' give in, the Amplitude these waveform
   for (i = 0; i < oneWaveSampleCount; i++)
   {
      int32 j;
      for (j = channelStart; j < channelStart + channelCount; j++)
      {
         double amplitude;
         double offset;
         //pay attention to channel rollback(when startChannel+channelCount>chNumberMax+1)
         channel = j % channelCountMax;
         amplitude = (ranges[channel].Max - ranges[channel].Min) / 2;
         offset = (ranges[channel].Max + ranges[channel].Min) / 2;

         switch (style)
         {
         case Sine:
            *waveBuffer++ = amplitude*(sin((double)i*2.0*( 3.14159 )/oneWaveSampleCount )) + offset;
            break;
         case Sawtooth:
            if ((i >= 0) && (i < (oneWaveSampleCount / 4.0)))
            {
               *waveBuffer++ = amplitude*(i/(oneWaveSampleCount/4.0)) + offset;
            }
            else
            {
               if ((i >= (oneWaveSampleCount / 4.0)) && (i < 3 *(oneWaveSampleCount / 4.0)))
               {
                  *waveBuffer++ = amplitude* ((2.0*(oneWaveSampleCount/4.0)-i)/(oneWaveSampleCount/4.0)) + offset;
               } 
               else
               {
                  *waveBuffer++ = amplitude* ((i-oneWaveSampleCount)/(oneWaveSampleCount/4.0)) + offset;
               }
            }
            break;
         case Square:
            if ((i >= 0) && (i < (oneWaveSampleCount /2)))
            {
               *waveBuffer++ = amplitude * 1 +offset;
            } 
            else
            {
               *waveBuffer++ = amplitude * (-1) + offset;
            }
            break;
         default:
            printf("invalid wave style,generate waveform error !");
            ret = ErrorUndefined;
         }
      }
   }
   return ret;
}

ErrorCode FillWaveBuffer( BufferedAoCtrl * BfdAoCtrl,double * scaleWaveBuffer)
{
   ErrorCode ret = Success;
   int i;
   int32 pointCount = channelCount*ONE_WAVE_POINT_COUNT;
   ret = GenerateWaveform( BfdAoCtrl, startChannel, channelCount, scaleWaveBuffer, pointCount, Sawtooth);
   if(BioFailed(ret) || ret == ErrorUndefined)
   {
      return ret;
   }

   for(i = 1; i < 4; ++i)
   {
      memcpy(scaleWaveBuffer + pointCount*i, scaleWaveBuffer,pointCount*sizeof(double));
   }
   return ret;
}