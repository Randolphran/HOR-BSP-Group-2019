% SynchronousOneBufferedAI.m
%
% Example Category: 
%    AI
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Synchronous One Buffered AI 
%    function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'startChannel' as the first channel for scan analog 
%       samples.  
%    3. Set the 'channelCount' to decide how many sequential channels to 
%       scan analog samples.
%    4. Set the 'convertClkRate' to to tell driver sample data rate for 
%       each channel.  
%    5. Set the 'sectionLength' to decide what occasion to signal event.In
%    addtion, many sectionLengths form the one channel.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function SynchronousOneBufferedAI()
% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following four parameters before running the demo.
% The default device of project is demo device, users can choose other 
% devices according to their needs. 
deviceDescription = 'DemoDevice,BID#0'; 
startChannel = int32(0);
channelCount = int32(2);
convertClkRate = int32(1000);
sectionLength = int32(1024);
sectionCount = int32(1);%1 meas one buffered mode.

errorCode = Automation.BDaq.ErrorCode.Success;

% Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
waveformAiCtrl = Automation.BDaq.WaveformAiCtrl();

try
    % Step 2: Select a device by device number or device description and
    % specify the access mode. in this example we use 
    % ModeWrite(default) mode so that we can 
    % fully control the device, including configuring, sampling, etc.
    waveformAiCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);

    % Step 3: Set necessary parameters for Asynchronous One Buffered AI
    % operation.
    conversion = waveformAiCtrl.Conversion;
    record = waveformAiCtrl.Record;
    
    conversion.ChannelStart = startChannel;
    conversion.ChannelCount = channelCount;
    conversion.ClockRate = convertClkRate;
    record.SectionCount = sectionCount;
    record.SectionLength = sectionLength;
    

    % Step 4: Prepare the buffered AI. 
    errorCode =  waveformAiCtrl.Prepare();
    if BioFailed(errorCode)
        throw Exception();
    end
    
    % Step 5: Start buffered AI, 'RunOnce' indicates using synchronous 
    % mode, which means the method will not return until the acquisition is
    % completed.
    disp('SynchronousOneBufferedAI is in progress.');
    disp('Please wait, until acquisition complete.');
    errorCode = waveformAiCtrl.Start();
    if BioFailed(errorCode)
        throw Exception();
    end
    
    % Step 6: Read samples and do post-process.
    scaledData = NET.createArray('System.Double', sectionLength*sectionCount*channelCount);
    errorCode = waveformAiCtrl.GetData(sectionLength*sectionCount*channelCount,scaledData,-1);%-1 means waiting for filling up the buffer.
    disp('Acquisition has completed!');
    figure('NumberTitle', 'off', 'Name', 'SynchronousOneBufferedAI');
    plot(scaledData);
catch e
    % Something is wrong.
    if BioFailed(errorCode)    
        errStr = 'Some error occurred. And the last error code is ' + ...
            errorCode.ToString();
    else
        errStr = e.message;
    end
    disp(errStr); 
end

% Step 7: Close device, release any allocated resource.
  waveformAiCtrl.Dispose();

end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

