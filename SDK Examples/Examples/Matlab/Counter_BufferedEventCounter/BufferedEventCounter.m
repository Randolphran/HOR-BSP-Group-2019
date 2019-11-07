% BufferedEventCounter.m
%
% Example Category:
%    Counter
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Buffered Event Counter function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'chEnable' to select channel of the counter to operate.
%    3. Set the 'sectionLength'to decide what occasion to signal event.
%    4. Set the 'sectionCount' to decide the count of data section to 
%       acquire,the operation will stop automatically after the specified 
%       count of data section is got.
%    5. Set the 'sampleClkSrc' to select the sampling clock source.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function BufferedEventCounter()

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following parameters before running the demo.
% The default device of project is PCIE-1813, users can choose other 
% devices according to their needs. 

% Device general settings.
deviceDescription = 'PCIE-1813,BID#15'; 
chEnable = [1,0,0,0];
sectionLength = int32(1024); 
sectionCount = int32(0); % "sectionCount" is zero, meaning Streaming Mode.
sampleClkSrc = Automation.BDaq.SignalDrop.SigExtDigClock;

% Triggrt settings
% Set trigger parameters.
% Remove comment marker if use Trigger.
% triggerAction = Automation.BDaq.TriggerAction.DelayToStart;
triggerSource = Automation.BDaq.SignalDrop.SignalNone;
% triggerEdge = Automation.BDaq.ActiveSignal.RisingEdge;
% triggerLevel = double(3.0);

errorCode = Automation.BDaq.ErrorCode.Success;

% Step 1: Create a 'BufferedEventCounterCtrl' for Buffered Event Counter function.
bfdEventCounterCtrl = Automation.BDaq.BufferedEventCounterCtrl();

% Step 2: Set the notification event Handler by which we can known the 
% state of operation effectively. 
addlistener(bfdEventCounterCtrl, 'DataReady', @bfdEventCounterCtrl_DataReady);

try
    % Step 3: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    bfdEventCounterCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    
    if 	bfdEventCounterCtrl.Features.TriggerCount
    else
        e = MException('DAQError:NotSupport', ...
            'The device do not support trigger function!');
        throw (e);
    end
    
    % Step 4: Set necessary parameters for Buffered Event Counter operation.
    bfdEventCounterCtrl.ChannelMap = chEnable;
    
    record = bfdEventCounterCtrl.Record;
    record.SectionLength = sectionLength;
    record.SectionCount = sectionCount;
    
    bfdEventCounterCtrl.SampleClkSrc = sampleClkSrc;
    
    % Setp 5: Trigger parameters setting.
    % Diffenert device with different trigger source, when changing trigger
    % source refer to manual for details.
    trigger = bfdEventCounterCtrl.Trigger;
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
    
    % Step 6: Start BufferedEventCounter 
    errorCode = bfdEventCounterCtrl.Prepare();
    if BioFailed(errorCode)
        throw Exception(); 
    end
    bfdEventCounterCtrl.Enabled = true;
    
    % Step 7: Read counting value: connect the input signal to channels 
    % you selected to get event counter value.
    fprintf('BufferedEventCounter is in progress...\nConnect the input signal');
    fprintf(' to CNT#_CLK pin if you choose external clock!\n');
    input('Press Enter key to quit!\n','s');
    
    % Step 8: stop BufferedEventCounter
    bfdEventCounterCtrl.Enabled = false;
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
bfdEventCounterCtrl.Dispose();
end

function result = BioFailed(errorCode)
result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;
end

function bfdEventCounterCtrl_DataReady(sender, e)
bfdEventCounterCtrl = sender;
dataBuf = NET.createArray('System.Int32', e.Count);
[errorCode, returnedCount, startTime] = bfdEventCounterCtrl.GetData(e.Channel, e.Count, dataBuf, 0);
fprintf('Buffered Event Counter DataReadyEvent, channel %d Current Event counts  :%d\n',e.Channel, dataBuf(1));
end






















