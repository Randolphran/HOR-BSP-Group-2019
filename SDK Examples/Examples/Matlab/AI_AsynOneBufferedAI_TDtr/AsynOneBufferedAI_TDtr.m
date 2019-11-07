% AsynOneBufferedAI_TDtr.cs
%
% Example Category:
%    AI
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Asynchronous One Buffered AI with 
%    Delay to Start Trigger function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'startChannel' as the first channel for scan analog samples  
%    3. Set the 'channelCount' to decide how many sequential channels to 
%       scan analog samples.
%    4. Set the 'sectionLength' to decide what occasion to signal event.In
%       addtion, one channel is formed by many sectionLengths.
%    5. Set the 'convertClkRate' to tell driver sample data rate for each 
%       channel.    
%    6. Set 'trigger parameters' to decide trigger property.
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function AsynOneBufferedAI_TDtr()

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following four parameters before running the demo.
% The default device of project is demo device, users can choose other 
% devices according to their needs. 
deviceDescription = 'DemoDevice,BID#0'; 
startChannel = int32(0);
channelCount = int32(2);
sectionLength = int32(1024);  
sectionCount = int32(1);%1 meas one buffered mode.
% For each channel.  
convertClkRate = double(1000.0);

% Set trigger parameters.
% Diffenert device with different trigger source, when changing trigger
% source refer to manual for details.
triggerAction = Automation.BDaq.TriggerAction.DelayToStart;
triggerSource = Automation.BDaq.SignalDrop.SigExtDigClock;
triggerEdge = Automation.BDaq.ActiveSignal.RisingEdge;
triggerDelayCount = int32(1000);
triggerLevel = double(5.0);

errorCode = Automation.BDaq.ErrorCode.Success;

% Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
waveformAiCtrl = Automation.BDaq.WaveformAiCtrl();

% Step 2: Set the notification event Handler by which we can known the 
% state of operation effectively.
addlistener(waveformAiCtrl, 'Stopped', @waveformAiCtrl_Stopped);

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
    record.SectionCount = sectionCount;
    record.SectionLength = sectionLength;
    
    % Step 5: Trigger parameters setting.
    trigger = waveformAiCtrl.Trigger;
    if ~isempty(trigger)
        trigger.Action = triggerAction;
        trigger.Source = triggerSource;
        trigger.DelayCount = triggerDelayCount;
        trigger.Edge = triggerEdge;
        trigger.Level = triggerLevel;
    else
        e = MException('DAQError:NotSupport',...
            'The device do not support trigger function!');
        throw (e);
    end

    % Step 6: Prepare the buffered AI.   
    errorCode =  waveformAiCtrl.Prepare();
    if BioFailed(errorCode)
        throw Exception();
    end
    
    % Step 7: Start Asynchronous Buffered AI, 'Asynchronous' means the
    % method returns immediately after the acquisition has been started. 
    % The 'bufferedAiCtrl_Stopped' method will be called after the 
    % acquisition is completed.
    errorCode = waveformAiCtrl.Start();
    if BioFailed(errorCode)
        throw Exception();
    end
    
    % Step 8: Do anything you are interesting while the device is acquiring
    % data.
    fprintf('AsynchronousOneBufferedAI is in progress...');
    input('Press Enter key to quit!', 's');
    
    % step 9: Stop the operation if it is running.
    errorCode = waveformAiCtrl.Stop();
    pause(1);
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

% Step 10: Close device, release any allocated resource before quit.
waveformAiCtrl.Dispose();

end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

function waveformAiCtrl_Stopped(sender, e)

fprintf('Acquisition has completed, all channel sample count is %d.\n', ...
    e.Count);
waveformAiCtrl = sender;

% e.Count notifys that how many samples had been gathered in the 'Stopped'
% event. 
if e.Count <= 0
else
allChanData = NET.createArray('System.Double', e.Count);
waveformAiCtrl.GetData(e.Count, allChanData, 0);
figure('NumberTitle', 'off', 'Name', 'AsynOneBufferedAI_TDtr');
plot(allChanData);
end

end
