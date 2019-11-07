% SnapCounter.m
%
% Example Category:
%    Counter
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Snap Counter function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'channel' as the work channel for Snap counter.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function SnapCounter()

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');
% Configure the following parameters before running the demo.
% The default device of project is demo device, users can choose other 
% devices according to their needs. 
deviceDescription = 'PCI-1784,BID#0'; 
channel = int32(0);

global srcID;
srcID = NET.createArray('Automation.BDaq.EventId', 32);

% Step 1: Create a 'UdCounterCtrl' for Snap Counter function.
udCounterCtrl = Automation.BDaq.UdCounterCtrl();

% Step 2: Set the notification event Handler by which we can known the 
% state of operation effectively.
addlistener(udCounterCtrl, 'UdCntrEvent', @udCounterCtrl_SnapCounter);

try
    % Step 3: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    udCounterCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    
    % Step 4: Set necessary parameters for counter operation.
    udCounterCtrl.ChannelCount = 1;
    udCounterCtrl.ChannelStart = channel;
    
    % Step 5: Set counting type for UpDown Counter.
    % counting type : CountingNone,DownCount,UpCount,PulseDirection,
    % TwoPulse,AbPhaseX1,AbPhaseX2,AbPhaseX4.
    signalCountingType = Automation.BDaq.CountingType.AbPhaseX1;
    getChannels = udCounterCtrl.Channels.Get(channel);
    getChannels.CountingType = signalCountingType;
    
    % Step 6: Set snap source and start Snap function. 
    snapSource = udCounterCtrl.Features.UdSnapEventSources;
    for i = 0:(snapSource.Length-1)  
        srcID.Set(i, snapSource.Get(i));  
    end
    udCounterCtrl.SnapStart(snapSource.Get(0));
    
    % Step 7: Start UpDown Counter. 
    udCounterCtrl.Enabled = true;
    
    % Step 8: Read counting value: connect the input signal to channels
    % you selected to get event counter value.
    fprintf(' Snap Counter is in progress...\n');
    fprintf(' Connect the input signal to the connector.\n');
    t = timer('TimerFcn',{@TimerCallback, udCounterCtrl, channel}, ...
        'period', 1, 'executionmode', 'fixedrate', 'StartDelay', 1);
    start(t);
    input(' Press Enter key to quit!\n\n','s');
 
    % Step 9: Stop UpDown Counter.
    udCounterCtrl.SnapStop(snapSource.Get(0));
    
    % Step 10: stop UpDown Counter.
    udCounterCtrl.Enabled = false;
    stop(t);
    delete(t);
catch e
    % Something is wrong. 
    errStr = e.message;
    disp(errStr);
end   

% Step 11: Close device and release any allocated resource.
clear global
udCounterCtrl.Dispose();

end

function TimerCallback(obj, event, udCounterCtrl, channel)

fprintf('\nchannel %d Current  counts  :%d\n', ...
    channel, udCounterCtrl.Value);

end

function udCounterCtrl_SnapCounter(sender, e)

global srcID
length = int32(sender.Features.SnapEventSources.Length);
for srcLen = 0:length - 1
    if srcID.Get(srcLen) == e.Id
        for i = 0:(e.Length - 1)
            data = e.Data.Get(i);
            fprintf('\nSource %s Snap occurs. Snap data is: %d \n', ...
                char(srcID.Get(srcLen)), data);
        end
        break;
    end 
end

end