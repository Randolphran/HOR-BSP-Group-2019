% StreamingAI.m
%
% Example Category:
%    AI
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Streaming AI function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' which can get from system device 
%       manager for opening the device. 
%    2. Set the 'startChannel' as the first channel for scan analog 
%       samples.  
%    3. Set the 'channelCount' to decide how many sequential channels to 
%       scan analog samples.
%    4. Set the 'sectionLength'to decide what occasion to signal event; 
%       when one section it is capacity decided by 
%       'sectionLength*channelCount' in kernel buffer(the capacity decided
%       by 'sampleCount*channelCount' )is filled, driver signal a 
%       'DataReady' event to notify APP.
%       ( ***Notes: the buffer is divided up with many sections begin with 
%                   buffer's head, the last section may not be equal to 
%                   'intervalCount*channelCount' if the 'sampleCount' is 
%                   not an integer multiple of 'intervalCount',but the last 
%                   section is filled, driver signal 'DataReady' event too. 
%                   ***)
%    5. Set the 'convertClkRate' to to tell driver sample data rate for 
%       each channel.  
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function StreamingAI()
% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following six parameters before running the demo.
% The default device of project is demo device, users can set other devices 
% according to their needs. 
deviceDescription = 'DemoDevice,BID#0'; 
startChannel = int32(0);
channelCount = int32(2);
% For each channel, to decide the capacity of buffer in kernel.
sectionLength = int32(1024);

% For each channel. Recommend: sampleCount is an integer multiple of 
% intervalCount, and equal to twice or greater.
convertClkRate = double(1000.0);
errorCode = Automation.BDaq.ErrorCode.Success;
% Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
waveformAiCtrl = Automation.BDaq.WaveformAiCtrl();

% Step 2: Set the notification event Handler by which we can known the 
% state of operation effectively. 
addlistener(waveformAiCtrl, 'DataReady', @waveformAiCtrl_DataReady);
addlistener(waveformAiCtrl, 'Overrun', @waveformAiCtrl_Overrun);

try
    % Step 3: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.    
    waveformAiCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);

    % Step 4: Set necessary parameters for Asynchronous One Buffered AI 
    % operation.
    conversion = waveformAiCtrl.Conversion;
    record = waveformAiCtrl.Record;
    
    conversion.ChannelStart = startChannel;
    conversion.ChannelCount = channelCount;
    conversion.ClockRate = convertClkRate;
    record.SectionCount = 0;%0 means streaming mode.
    record.SectionLength = sectionLength;

    % Step 5: Prepare the buffered AI. 
    errorCode = waveformAiCtrl.Prepare();
    if BioFailed(errorCode)
        throw Exception();
    end

    % Step 6: Start buffered AI, the method will return immediately after 
    % the operation has been started in streaming buffered mode.
    errorCode = waveformAiCtrl.Start();
    if BioFailed(errorCode)
        throw Exception();
    end

    % Step 7: Do anything you are interesting while the device is acquiring 
    % data.
    input(' StreamingAI is in progress... any key to quit !', 's');
    
    % step 8: Stop the operation if it is running.
    errorCode = waveformAiCtrl.Stop();
    if BioFailed(errorCode)
        throw Exception();
    end
catch e
    % Something is wrong.
    if BioFailed(errorCode)    
        errStr = 'Some error occurred. And the last error code is ' ... 
            + errorCode.ToString();
    else
        errStr = e.message;
    end
    disp(errStr);
end

% Step 9: Close device and release any allocated resource.
clear functions
waveformAiCtrl.Dispose();

end

function waveformAiCtrl_DataReady(sender, e)
persistent handle;
if isempty(handle) || ~ishghandle(handle)
    handle = figure('NumberTitle', 'off', 'Name', 'StreamingAI');
end

waveformAiCtrl = sender;
conversion = waveformAiCtrl.Conversion;
channelCount = conversion.ChannelCount;
if e.Count > channelCount
   sectionBuffer = NET.createArray('System.Double', e.Count);
   waveformAiCtrl.GetData(e.Count, sectionBuffer);
   for i=1:(e.Count / channelCount)
       for j=1:channelCount
           Y(i,j) = sectionBuffer((i - 1) * channelCount+j);
       end
   end 
   plot(Y); 
end

end

function waveformAiCtrl_Overrun(sender, e)
disp('Streaming AI is Over run ! ');

end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

