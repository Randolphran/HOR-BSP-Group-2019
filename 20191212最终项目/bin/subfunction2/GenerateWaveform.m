function waveBuffer = GenerateWaveform(amplitude, offset, dutycycle, ...
    oneWavePointCount, style)

% errorcode = Automation.BDaq.ErrorCode.Success;
% chanCountMax = int32(instantAoCtrl.Features.ChannelCountMax);
% oneWavePointCount = int32(SamplesCount / channelCount);

% description = System.Text.StringBuilder();
% unit = Automation.BDaq.ValueUnit;
% ranges = NET.createArray('Automation.BDaq.MathInterval', chanCountMax); 

% get every channel's value range ,include external reference voltage
% value range which you should key it in manually.
% channels = instantAoCtrl.Channels;
% for i = 1:chanCountMax
%     channel = channels.Get(i - 1);
%     valRange = channel.ValueRange;
%     if Automation.BDaq.ValueRange.V_ExternalRefBipolar == valRange ...
%             || valRange == Automation.BDaq.ValueRange.V_ExternalRefUnipolar
%         if instantAoCtrl.Features.ExternalRefAntiPolar
%             if valRange == Automation.BDaq.ValueRange.V_ExternalRefBipolar
%                 referenceValue = double(...
%                     instantAoCtrl.ExtRefValueForBipolar);
%                 if referenceValue >= 0
%                     ranges(i).Max = referenceValue;
%                     ranges(i).Min = 0 - referenceValue;
%                 else
%                     ranges(i).Max = 0 - referenceValue;
%                     ranges(i).Min = referenceValue;                    
%                 end
%             else
%                referenceValue = double(...
%                    instantAoCtrl.ExtRefValueForUnipolar); 
%                if referenceValue >= 0
%                    ranges(i).Max = 0;
%                    ranges(i).Min = 0 - referenceValue;
%                else
%                    ranges(i).Max = 0 - referenceValue;
%                    ranges(i).Min = 0;
%                end 
%             end
%         else
%             if valRange == Automation.BDaq.ValueRange.V_ExternalRefBipolar
%                 referenceValue = double(...
%                     instantAoCtrl.ExtRefValueForBipolar);
%                 if referenceValue >= 0
%                     ranges(i).Max = referenceValue;
%                     ranges(i).Min = 0 - referenceValue;
%                 else
%                     ranges(i).Max = 0 - referenceValue;
%                     ranges(i).Min = referenceValue;                    
%                 end
%             else
%                 referenceValue = double(...
%                     instantAoCtrl.ExtRefValueForUnipolar);
%                 if referenceValue >= 0
%                     ranges(i).Max = referenceValue;
%                     ranges(i).Min = 0;
%                 else
%                     ranges(i).Max = 0;
%                     ranges(i).Min = 0 - referenceValue;
%                 end
%             end
%         end
%     else     
%         [errorcode, ranges(i), unit] = ...
%             Automation.BDaq.BDaqApi.AdxGetValueRangeInformation(...
%             valRange, int32(0), description);
%         if BioFailed(errorcode)
%             return
%         end
%     end
% end

% generate waveform data and put them into the buffer which the parameter
% 'waveBuffer' give in, the Amplitude these waveform
waveBuffer = zeros(oneWavePointCount,1);
amplitude=amplitude/2;
for i = 1:oneWavePointCount
%     for j = channelStart:(channelStart + channelCount - 1)
        % pay attention to channel rollback(when startChannel+
        % channelCount>chanCountMax)
%         channel = int32(rem(j, chanCountMax));
%         amplitude = double((ranges.Get(channel).Max -...
%             ranges.Get(channel).Min) / 2);
%         offset = double((ranges.Get(channel).Max + ...
%             ranges.Get(channel).Min) / 2);
        switch style
            case 1
                waveBuffer(i)=amplitude * sin(double(i) * 2.0 * pi / ...
                    double(oneWavePointCount)) + offset;
            case 2
                if (i >= 0) && (i < (oneWavePointCount / 4.0))
                    waveBuffer(i)=amplitude * (double(i) / ...
                        (double(oneWavePointCount) / 4.0)) + offset;
                else
                    if (i >= (oneWavePointCount / 4.0)) && ...
                            (i < 3 * (oneWavePointCount / 4.0))
                        waveBuffer(i)= amplitude * ((2.0 * ...
                            (double(oneWavePointCount) / 4.0) - ...
                            double(i)) / (double(oneWavePointCount) ...
                            / 4.0)) + offset;
                    else
                        waveBuffer(i)= amplitude * ((double(i) - ...
                            double(oneWavePointCount)) / ...
                            (double(oneWavePointCount) / 4.0)) + offset;
                    end
                end
            case 3
                if (i >= 0) && (i < (oneWavePointCount*dutycycle))
                    waveBuffer(i)=amplitude * 1.0 + offset;
                else
                     waveBuffer(i)=amplitude * (-1.0) + offset;
                end
            case 4
               waveBuffer(i)= amplitude;
        end
    end
end
