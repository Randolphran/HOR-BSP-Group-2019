% InstantAI.m
%
% Example Category:
%    AI
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Instant AI function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'startChannel' as the first channel for scan analog samples  
%    3. Set the 'channelCount' to decide how many sequential channels to 
%       scan analog samples.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % 
% Editter : Yuncong Ran 2019/10/13
%   Modified TimeCallBack function, added input linehandle, dataAI, dataNum.
%     linehandle: Pass animation line handle to TimeCallBack,to draw the real-time signal.
%     dataAI: Data storage in the Main function. 
%     dataNum: Inidicate sample number, which is given by the timecallback
%              function
%   The funtion will display input signal in real-time in the axes area which are determined by linehandle, 
%   and return dataAI& dataNum once finished. 
%   
%   Modified TimerCallBack Fcn termination mode, activition of "STOP"
%   button in GUI is needed. If reaching the maximum of pre-assigned
%   memeroy, Timer will terminate, too, reporting an Error.
% 
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % 
function [dataAI, dataNum] = InstantAI_Project1(linehandle)

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq');

% Configure the following three parameters before running the demo.
% The default device of project is demo device, users can choose other 
% devices according to their needs. 
deviceDescription = 'USB-4704,BID#0'; 
startChannel = int32(0);
channelCount = int32(4);

% Initial data number is 1.Run Initialization each time "BEGIN" is pressed.
dataNum = 1;       
dataAI = zeros(1024,4); 
% Pre-assigned memeroy, Attention this might be insufficient.
% Simultaneously change the value in "BEGIN" callback function and stop condition when change happens here.

% get stop command via global varible.
global stopflag;


% Step 1: Create a 'InstantAiCtrl' for Instant AI function.
instantAiCtrl = Automation.BDaq.InstantAiCtrl();

try
    % Step 2: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % AccessWriteWithReset(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    instantAiCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    data = NET.createArray('System.Double', channelCount);
    
    % Step 3: Read samples and do post-process, we show data here.
    errorCode = Automation.BDaq.ErrorCode();
    t = timer( 'period', 1, 'executionmode', 'fixedrate', ...
        'StartDelay', 1);
    t.TimerFcn = @TimerCallback;
    [dataAI,dataNum] = t.TimerFcn(instantAiCtrl, startChannel, ...
        channelCount, data, dataAI, dataNum, linehandle);
    % edittor: Ran, 2019/10/14
    % Changed Time class Instantiation format.
    % Added new varibles here: dataAI, dataNum,linehandles.  
    
    start(t);
%     input('InstantAI is in progress...Press Enter key to quit!');
    while (dataNum < 1024) % Simultaneously change the value in "BEGIN" callback function and initilization when change happens here.
        
        if dataNum >= 1024;
            stop(t);
            fprintf('Error! Input data exceeds the memeroy distribution!');
            break;
        end
        
        if stopflag == -1
            stop(t);
            break;
        end
    end
    
    delete(t);
   
    
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

% Step 4: Close device and release any allocated resource.
instantAiCtrl.Dispose();

end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

function [dataAI, dataNum] = TimerCallback(obj, event, instantAiCtrl, startChannel, ...
    channelCount, data,dataAI,dataNum,linehandle)


errorCode = instantAiCtrl.Read(startChannel, channelCount, data); 
if BioFailed(errorCode)
    throw Exception();
end
fprintf('\n');

% get data
for j=0:(channelCount - 1)
    temp = data.Get(j);
    fprintf('channel %d : %10f ', j, temp);
    
    dataAI(dataNum,j+1) = temp;
    Realtimeplot(dataNum,temp,linehandle);
    
end

dataNum = dataNum + 1;

end