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
*    StaticAO.c
*
* Example Category:
*    AO
*
* Description:
*    This example demonstrates how to use Static AO voltage function.
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define ONE_WAVE_POINT_COUNT 512 //define how many data to makeup a waveform period.

#define  deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32 channelStart = 0;
int32 channelCount = 1;

typedef enum tagWaveStyle{ Sine, Sawtooth, Square }WaveStyle;
//function GenerateWaveform: generate one waveform for each selected analog data output channel
ErrorCode GenerateWaveform(InstantAoCtrl * instantAoCtrl, int32 channelStart, int32 channelCount, double * waveBuffer, int32 SamplesCount, WaveStyle style);

void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   double  * waveform = NULL;
   int       enforce  = FALSE;

   // Step 1: Create a 'InstantAoCtrl' for Static AO function.
   InstantAoCtrl * instantAoCtrl = InstantAoCtrl_Create();
   do 
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode = ModeWrite;
      devInfo.ModuleIndex = 0;
      wcscpy(devInfo.Description, deviceDescription);
      ret = InstantAoCtrl_setSelectedDevice(instantAoCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = InstantAoCtrl_LoadProfile(instantAoCtrl, profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 3: Output data
      // Generate waveform data
      waveform = (double *)malloc(channelCount*ONE_WAVE_POINT_COUNT*sizeof(double));
      if (NULL == waveform)
      {
         printf("Insufficient memory available\n");
         break;
      }
      
      ret = GenerateWaveform(instantAoCtrl, channelStart, channelCount, waveform, channelCount*ONE_WAVE_POINT_COUNT, Sine);
      CHK_RESULT(ret);

      printf("\n Outputting data... any key to quit!\n");
     do 
     {
         int32 i;
         for (i = 0; i < ONE_WAVE_POINT_COUNT; i++)
         {
            ret = InstantAoCtrl_WriteAny(instantAoCtrl, channelStart, channelCount, NULL, &waveform[channelCount*i]);
            CHK_RESULT(ret);
            SLEEP(1);
            if (kbhit())
            {
               printf("\n Static AO is over compulsorily");
               enforce = TRUE;
               break;
            }
         }
     } while (FALSE);
     free(waveform);
     if (!enforce)
     {
        printf("\n Static AO is over, press any key to quit!\n");
     }
   } while (FALSE);

   // Step 4: Close device and release any allocated resource.
   InstantAoCtrl_Dispose(instantAoCtrl);

   if (BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();//Wait any key to quit!.
   }
   waitAnyKey();//Wait any key to quit!.
   return 0;
}

ErrorCode GenerateWaveform(InstantAoCtrl * instantAoCtrl, int32 channelStart, int32 channelCount, double * waveBuffer, int32 SamplesCount, WaveStyle style)
{
   ErrorCode ret                = Success;
   int32     channel            = 0;
   int32     channelCountMax    = 0;
   int32     oneWaveSamplesCount = SamplesCount / channelCount;
   int32     i                  = 0;

   MathInterval    ranges[64];
   ValueRange      valRange;
   AoChannel *     aoChannel = NULL;

   channelCountMax = AoFeatures_getChannelCountMax(InstantAoCtrl_getFeatures(instantAoCtrl));
   for (i = 0; i < channelCountMax; i++)
   {
      aoChannel = (AoChannel *)Array_getItem(InstantAoCtrl_getChannels(instantAoCtrl),i);
      valRange  = AoChannel_getValueRange(aoChannel);
      if (V_ExternalRefBipolar == valRange || valRange == V_ExternalRefUnipolar)
      {
         if (AoFeatures_getExternalRefAntiPolar(InstantAoCtrl_getFeatures(instantAoCtrl)))
         {
            double referenceValue;
            if (valRange == V_ExternalRefBipolar)
            {
					referenceValue = AoChannel_getExtRefBipolar(aoChannel);
               if (referenceValue >= 0){
                  ranges[i].Max = referenceValue;
                  ranges[i].Min = 0 - referenceValue;
               }else{
                  ranges[i].Max = 0 - referenceValue;
                  ranges[i].Min = referenceValue;
               }
            }
            else
            {
					referenceValue = AoChannel_getExtRefUnipolar(aoChannel);
               if (referenceValue > 0){
                  ranges[i].Max = 0;
                  ranges[i].Min = 0 - referenceValue;
               }else{
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
               if (referenceValue >= 0){
                  ranges[i].Max = referenceValue;
                  ranges[i].Min = 0 - referenceValue;
               } else{
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
                  ranges[i].Min =referenceValue;
               }
            }
         }
      }
      else{
         ret = AdxGetValueRangeInformation(valRange, 0, NULL, &ranges[i], NULL);
         if (BioFailed(ret))
         {
            return ret;
         }
      }
   }

   //generate waveform data and put them into the buffer which the parameter 'waveBuffer' give in, the Amplitude these waveform
   for(i = 0; i < oneWaveSamplesCount; i++ )
   {
      int32 j;
      for( j = channelStart; j < channelStart+channelCount; j++ )
      {
         double amplitude;
         double offset;
         //pay attention to channel rollback(when startChannel+channelCount>chNumberMax+1)
         channel = j%channelCountMax;

         amplitude = (ranges[channel].Max - ranges[channel].Min) / 2;
         offset = (ranges[channel].Max + ranges[channel].Min) / 2;

         switch ( style)
         {
         case Sine:
            *waveBuffer++ = amplitude*(sin((double)i*2.0*( 3.14159 )/oneWaveSamplesCount )) + offset;
            break;
         case  Sawtooth:
            if ((i >= 0) && (i < (oneWaveSamplesCount / 4.0)))
            {
               *waveBuffer++ =  amplitude*( i/(oneWaveSamplesCount/4.0)) + offset;
            }
            else
            {
               if ((i >= (oneWaveSamplesCount / 4.0)) && (i < 3 * (oneWaveSamplesCount/4.0)))
               {
                  *waveBuffer++ = amplitude* ((2.0*(oneWaveSamplesCount/4.0)-i)/(oneWaveSamplesCount/4.0)) + offset;
               }
               else
               {
                  *waveBuffer++ = amplitude* ((i-oneWaveSamplesCount)/(oneWaveSamplesCount/4.0)) + offset;
               }
            }
            break;
         case  Square:
            if ((i >= 0) && (i < (oneWaveSamplesCount / 2)))
            {
               *waveBuffer++ = amplitude * 1 + offset;
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
