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
*    StaticAO.cpp
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
*    3  Set the 'channelStart' as the first channel for analog data output.
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
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define     ONE_WAVE_POINT_COUNT  512 //define how many data to makeup a waveform period.

#define     deviceDescription  L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";
int32       channelStart = 0;
int32       channelCount = 1;

enum WaveStyle{ Sine, Sawtooth, Square };
//function GenerateWaveform: generate one waveform for each selected analog data output channel 
ErrorCode GenerateWaveform( InstantAoCtrl * instantAoCtrl,int32 channelStart,int32 channelCount,  double * waveBuffer, int32 SamplesCount,WaveStyle style);

inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
} 

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'InstantAoCtrl' for Static AO function.
   InstantAoCtrl * instantAoCtrl = InstantAoCtrl::Create();
   do
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = instantAoCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = instantAoCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 3: Output data 
      // Generate waveform data
      double *waveform = (double*)malloc( channelCount*ONE_WAVE_POINT_COUNT*sizeof(double));
      if( NULL  == waveform )
      {
         printf( "Insufficient memory available\n" );
         break;
      }
      ret = GenerateWaveform( instantAoCtrl,channelStart,channelCount, waveform,channelCount*ONE_WAVE_POINT_COUNT,Sine);
      CHK_RESULT(ret);

      printf("\n Outputting data...  any key to quit!\n");
      bool enforced = false;
      do 
      {
         for( int32 i = 0; i < ONE_WAVE_POINT_COUNT; i++ ) 
         { 
            ret = instantAoCtrl->Write(channelStart, channelCount, &waveform[channelCount*i]);
            CHK_RESULT(ret);
            SLEEP(1);
            if(kbhit())
            {
               printf("\n Static AO is over compulsorily");
               enforced = true;
               break;
            }
         } 
      } while (false);
      free(waveform);
      if (!enforced)
      {
         printf("\n Static AO is over, press any key to quit!\n");
      }
   }while(false);
   
	// Step 4: Close device and release any allocated resource.
	instantAoCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is 0x%X.\n", ret);
      waitAnyKey();// Wait any key to quit!.
   }

   waitAnyKey();// Wait any key to quit !
   return 0;
}


ErrorCode GenerateWaveform( InstantAoCtrl * instantAoCtrl, int32 channelStart,int32 channelCount,double * waveBuffer,int32 SamplesCount,WaveStyle style)
{
   ErrorCode ret = Success;
   int32    channel = 0;
   int32    channelCountMax = 0;
   int32    oneWaveSamplesCount = SamplesCount/channelCount;
   int32    i = 0;

   MathInterval  ranges[64] ;
   ValueRange valRange;
   channelCountMax =  instantAoCtrl->getFeatures()->getChannelCountMax();
   for(i = 0;i < channelCountMax ;i++ )
   {
      valRange = instantAoCtrl->getChannels()->getItem(i).getValueRange();
      if ( V_ExternalRefBipolar == valRange || valRange == V_ExternalRefUnipolar )
      {
		 if (instantAoCtrl->getFeatures()->getExternalRefAntiPolar())
		 {
			double referenceValue;

			if (valRange == V_ExternalRefBipolar)
			{
				referenceValue = instantAoCtrl->getChannels()->getItem(i).getExtRefBipolar();
				if (referenceValue >= 0) {
					ranges[i].Max = referenceValue;
					ranges[i].Min = 0 - referenceValue;
				} else {
					ranges[i].Max = 0 - referenceValue; 
					ranges[i].Min = referenceValue;
				}
			}
			else
			{
				referenceValue = instantAoCtrl->getChannels()->getItem(i).getExtRefUnipolar();
				if (referenceValue >= 0) {
					ranges[i].Max = 0;
					ranges[i].Min = 0 - referenceValue;
				} else {
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
				referenceValue = instantAoCtrl->getChannels()->getItem(i).getExtRefBipolar();
				if (referenceValue >= 0) {
					ranges[i].Max = referenceValue;
					ranges[i].Min = 0 - referenceValue;
				} else {
					ranges[i].Max = 0 - referenceValue; 
					ranges[i].Min = referenceValue;
				}
			}
			else
			{
				referenceValue = instantAoCtrl->getChannels()->getItem(i).getExtRefUnipolar();
				if (referenceValue >= 0) {
					ranges[i].Max = referenceValue;
					ranges[i].Min = 0;
				} else {
					ranges[i].Max = 0; 
					ranges[i].Min = referenceValue;
				}
			}	
		 }
      } 
	  else {
         ret = AdxGetValueRangeInformation( valRange,0,NULL,&ranges[i],NULL);
         if(BioFailed(ret))
         {
            return ret;
         }
      }
   }

   //generate waveform data and put them into the buffer which the parameter 'waveBuffer' give in, the Amplitude these waveform
   for(i = 0; i < oneWaveSamplesCount; i++ ) 
   { 
      for( int32 j = channelStart; j < channelStart+channelCount; j++ )
      {
         //pay attention to channel rollback(when startChannel+channelCount>chNumberMax+1)
         channel = j%channelCountMax;
		
		 double amplitude = (ranges[channel].Max - ranges[channel].Min) / 2;
		 double offset = (ranges[channel].Max + ranges[channel].Min) / 2; 

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
};