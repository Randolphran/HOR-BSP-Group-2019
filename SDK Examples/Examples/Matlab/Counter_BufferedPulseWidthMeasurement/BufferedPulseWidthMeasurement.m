% Buffered PulseWidthMeasurement.m
%
% Example Category:
%    Counter
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Buffered Pulse Width Measurement function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'chEnable' to select channel of the counter to operate.
%    3. Set the 'sectionLength'to decide what occasion to signal event; 
%    4. Set the 'sectionCount' to decide the count of data section to 
%       acquire,the operation will stop automatically after the specified 
%       count of data section is got.  
%    5. Set the 'sampleClkSrc' to set sampling clock source.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function BufferedPulseWidthMeasurement()

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following three parameters before running the demo.
% The default device of project is PCIE-1813, users can choose other 
% devices according to their needs.
% General settings
deviceDescription = 'PCIE-1813,BID#15';
chEnable = [1,0,0,0]; 
sectionLength = int32(1024); 
sectionCount = int32(0); % "sectionCount" is zero, meaning Streaming Mode.
sampleClkSrc = Automation.BDaq.SignalDrop.SignalNone;

% Triggrt settings
% Set trigger parameters.
% Remove comment marker if use Trigger.
% triggerAction = Automation.BDaq.TriggerAction.DelayToStart;
triggerSource = Automation.BDaq.SignalDrop.SignalNone;
% triggerEdge = Automation.BDaq.ActiveSignal.RisingEdge;
% triggerLevel = double(3.0);

% Step 1: Create a 'BufferedPwMeterCtrl' for Buffered Pulse Width Measurement function.
bfdPwMterCtrl = Automation.BDaq.BufferedPwMeterCtrl();

% Step 2: Set the notification event Handler by which we can known the 
% state of operation effectively. 
addlistener(bfdPwMterCtrl, 'DataReady', @bfdPwMterCtrl_DataReady);

try
    % Step 3: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    bfdPwMterCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    
    if 	bfdPwMterCtrl.Features.TriggerCount
    else
        e = MException('DAQError:NotSupport', ...
            'The device do not support trigger function!');
        throw (e);
    end
    
    % Step 4: Set necessary parameters for counter operation.
    bfdPwMterCtrl.ChannelMap = chEnable;

    record = bfdPwMterCtrl.Record;
    record.SectionLength = sectionLength;
    record.SectionCount = sectionCount;
    bfdPwMterCtrl.SampleClkSrc = sampleClkSrc;
    
    % Setp 5: Trigger parameters setting.
    % Diffenert device with different trigger source, when changing trigger
    % source refer to manual for details.
    trigger = bfdPwMterCtrl.Trigger;
    if ~isempty(trigger)
        trigger.Source = triggerSource;
        %trigger.Action = triggerAction;
        %trigger.Edge = triggerEdge;
        %trigger.Level = triggerLevel;
    else
        e = MException('DAQError:NotSupport',...
            'The device do not support trigger function!');
        throw (e);
    end
    
    % Step 6: Start BufferedPulseWidthMeasurement
    errorCode = bfdPwMterCtrl.Prepare();
    if BioFailed(errorCode)
        throw Exception(); 
    end
    bfdPwMterCtrl.Enabled = true;
    
    % Step 7: Get Pulse Width value.
    fprintf('BufferedPulseWidthMeasurement is in progress...\n');
    fprintf('Connect the input signal to the connector.\n');
    input('Press Enter key to quit!\n\n','s');
 
    % Step 8: Stop BufferedPulseWidthMeasurement
    bfdPwMterCtrl.Enabled = false;
catch e
    % Something is wrong. 
    errStr = e.message;
    disp(errStr);
end   

% Step 9: Close device and release any allocated resource.
bfdPwMterCtrl.Dispose();

end

function result = BioFailed(errorCode)
result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;
end

function bfdPwMterCtrl_DataReady(sender, e)
bfdPwMterCtrl = sender;
dataBuf = NET.createArray('Automation.BDaq.PulseWidth', e.Count);
[errorCode, returnedCount, startTime] = bfdPwMterCtrl.GetData(e.Channel, e.Count, dataBuf, 0);
fprintf('BufferedPulseWidthMeasurement DataReadyEvent, channel %d  High Period:%f s, Low Period: %f s\n', ...
    e.Channel, dataBuf(1).HiPeriod, dataBuf(1).LoPeriod);
end

























