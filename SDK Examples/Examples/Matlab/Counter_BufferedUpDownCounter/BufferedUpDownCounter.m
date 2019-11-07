% BufferedUpDownCounter.m
%
% Example Category:
%    Counter
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use BufferedUpDown Counter function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'chEnable' to select channel of the counter to operate.
%    3. Set the 'channelCount' to decide how many channels to operate. 
%    4. Set the 'sectionLength'to decide what occasion to signal event;
%    5. Set the 'sectionCount' to decide the count of data section to 
%       acquire,the operation will stop automatically after the specified 
%       count of data section is got.
%    6. Set the 'sampleClkSrc' to set the sampling clock source.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function BufferedUpDownCounter()

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following parameters before running the demo.
% The default device of project is PCIE-1813, users can choose other 
% devices according to their needs. 
deviceDescription = 'PCIE-1813,BID#15';  
channelCount = int32(4);
chEnable = [1,0,0,0]; 
sectionLength = int32(1024); 
sectionCount = int32(0); % "sectionCount" is zero, meaning Streaming Mode.
sampleClkSrc = Automation.BDaq.SignalDrop.SigExtDigClock;

% triggerAction = Automation.BDaq.TriggerAction.DelayToStart;
triggerSource = Automation.BDaq.SignalDrop.SignalNone;
% triggerEdge = Automation.BDaq.ActiveSignal.RisingEdge;
% triggerLevel = double(3.0);

% Step 1: Create a 'bfdUdCounterCtrl' for BufferedUpDown Counter function.
bfdUdCounterCtrl = Automation.BDaq.BufferedUdCounterCtrl();

% Step 2: Set the notification event Handler by which we can known the 
% state of operation effectively. 
addlistener(bfdUdCounterCtrl, 'DataReady', @bfdUdCounterCtrl_DataReady);

try
    % Step 3: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    bfdUdCounterCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
   
    if 	bfdUdCounterCtrl.Features.TriggerCount
    else
        e = MException('DAQError:NotSupport', ...
            'The device do not support trigger function!');
        throw (e);
    end
    
    % Step 4: Set necessary parameters for counter operation.
    bfdUdCounterCtrl.ChannelMap = chEnable;
    
    record = bfdUdCounterCtrl.Record;
    record.SectionLength = sectionLength;
    record.SectionCount = sectionCount;
   
    bfdUdCounterCtrl.SampleClkSrc = sampleClkSrc;
    
    % Setp 5: Trigger parameters setting.
    % Diffenert device with different trigger source, when changing trigger
    % source refer to manual for details.
    trigger = bfdUdCounterCtrl.Trigger;
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
    
    % Step 6: Set counting type for BufferedUpDown Counter.
    % counting type : CountingNone,DownCount,UpCount,PulseDirection,
    % TwoPulse,AbPhaseX1,AbPhaseX2,AbPhaseX4.
    signalCountingType = Automation.BDaq.CountingType.PulseDirection;
    for i = 1 : (channelCount)
        if(chEnable(i))
            getChannels = bfdUdCounterCtrl.Channels.Get(i);
            getChannels.CountingType = signalCountingType;
        end    
    end 

    % Step 7: Start BufferedUpDown Counter. 
    errorCode = bfdUdCounterCtrl.Prepare();
    if BioFailed(errorCode)
        throw Exception(); 
    end
    bfdUdCounterCtrl.Enabled = true;
    
    % Step 8: Read counting value: connect the input signal to channels
    % you selected to get event counter value.
    fprintf('Buffered UpDown Counter is in progress...\n');
    fprintf('Connect the input signal to the connector.\n');
    input('Press Enter key to quit!\n\n','s');
 
    % Step 9: Stop BufferedUpDown Counter.
    bfdUdCounterCtrl.Enabled = false;
catch e
    % Something is wrong. 
    errStr = e.message;
    disp(errStr);
end   

% Step 10: Close device and release any allocated resource.
bfdUdCounterCtrl.Dispose();
end

function result = BioFailed(errorCode)
result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;
end

function bfdUdCounterCtrl_DataReady(sender, e)
bfdUdCounterCtrl = sender;
% buffer section length, when 'DataReady' event been signaled,
% driver renew data count is e.count. 
   dataBuf = NET.createArray('System.Int32', e.Count);
   [errorCode, returnedCount, startTime] = bfdUdCounterCtrl.GetData(e.Channel, e.Count, dataBuf, 0);
   fprintf('BufferedUpDownCounter DataReadyEvent, channel %d Current Buffered UpDown counter counts  :%d\n\n', ...
        e.Channel, dataBuf(1));
end

