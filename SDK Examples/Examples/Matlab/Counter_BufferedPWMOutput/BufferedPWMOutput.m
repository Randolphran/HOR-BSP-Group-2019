% BufferedPWMOutput.m
%
% Example Category:
%    Counter
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Buffered PWM Output function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'chEnable' to select channel of the counter to operate.
%    3. Set the 'channelCount' to decide how many channels to operate. 
%    4. Set the 'samplesCount' to set the total sample count to be
%       outputted.
%    5. Set the 'intervalCount' to how many samples of each channel should
%       be outputted before sending the DataTransmitted event.
%    6. Set the 'poHiPeriod' to decide the high level pulse width for 
%       selected channel. 
%    7. Set the 'poLoPeriod' to decide the low level pulse width for 
%       selected channel.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function BufferedPWMOutput()

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following four parameters before running the demo.
% The default device of project is PCIE-1813, users can choose other 
% devices according to their needs. 
deviceDescription = 'PCIE-1813,BID#15'; 
channelCount = int32(4);
chEnable = [1,0,0,0]; 
sampleClkSrc = Automation.BDaq.SignalDrop.SignalNone;
intervalCount = int32(2048);
samplesCount = int32(4096);

% Triggrt settings
% Set trigger parameters.
% Remove comment marker if use Trigger.
% triggerAction = Automation.BDaq.TriggerAction.DelayToStart;
triggerSource = Automation.BDaq.SignalDrop.SignalNone;
% triggerEdge = Automation.BDaq.ActiveSignal.RisingEdge;
% triggerLevel = double(3.0);

% Step 1: Create a 'bfdPwModulatorCtrl' for BufferedPWMOutput function.
bfdPwModulatorCtrl = Automation.BDaq.BufferedPwModulatorCtrl();

% Step 2: Set the notification event Handler by which we can known the 
% state of operation effectively. 
addlistener(bfdPwModulatorCtrl, 'DataTransmitted', @bfdPwModulatorCtrl_Transmitted);

try
    % Step 3: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    bfdPwModulatorCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    
    if 	bfdPwModulatorCtrl.Features.TriggerCount
    else
        e = MException('DAQError:NotSupport', ...
            'The device do not support trigger function!');
        throw (e);
    end
    
    % Step 4: Set necessary parameters for counter operation.
    bfdPwModulatorCtrl.ChannelMap = chEnable;
    bfdPwModulatorCtrl.SampleClkSrc = sampleClkSrc;
    
    dataBuf = NET.createArray('Automation.BDaq.PulseWidth', samplesCount);
    for i = 1:(samplesCount)
        dataBuf(i).HiPeriod = 0.08;
        dataBuf(i).LoPeriod = 0.02;
    end
    bfdPwModulatorCtrl.IntervalCount = intervalCount;
    bfdPwModulatorCtrl.Samples = samplesCount;
    bfdPwModulatorCtrl.Streaming = true;
    
    % Setp 5: Trigger parameters setting.
    % Diffenert device with different trigger source, when changing trigger
    % source refer to manual for details.
    trigger = bfdPwModulatorCtrl.Trigger;
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
        
    for i = 1 : (channelCount)
        if(chEnable(i))
            bfdPwModulatorCtrl.SetData(i, samplesCount, dataBuf);
        end    
    end
    
    % Step 6: Start BufferedPWMOutput 
    fprintf('Buffered PWMOutput is in progress...\nTest signal to the Out pin!');
    errorCode = bfdPwModulatorCtrl.Prepare();
    if BioFailed(errorCode)
        throw Exception(); 
    end
    bfdPwModulatorCtrl.Enabled = true;
    
    % Step 7: Stop BufferedPWMOutput
    input('\nPress Enter key to quit!\n','s');
    bfdPwModulatorCtrl.Enabled = false;
catch e
    % Something is wrong. 
    errStr = e.message;
    disp(errStr);
end   

% Step 8: Close device and release any allocated resource.
bfdPwModulatorCtrl.Dispose();
end

function result = BioFailed(errorCode)
result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;
end

function bfdPwModulatorCtrl_Transmitted(sender, e)
fprintf('BufferedPWMOutput TransmittedEvent, channel %d transmitted counts  :%d\n',e.Channel, e.Count);
end


























