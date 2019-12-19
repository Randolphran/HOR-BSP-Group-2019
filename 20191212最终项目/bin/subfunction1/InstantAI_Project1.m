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
% Editter : Yuncong Ran 2019/10/21
%   Modified InstantAI& TimeCallBack function, added input hObjct & handles
%   to convey parameters. Struct Handles consists of following vars:
% 
%     LineHandle: Convey animation line handle to TimeCallBack,to draw the real-time signal.
%     dataAI: Data storage in the Main function. 
%     dataNum: Inidicate sample number, which is given by the timecallback
%              function
%     Samplingrate: Sampling Rate, known as the input para 'period' of
%                   Timer object.
% 
%   The funtion will display input signal in real-time in the axes area which are determined by LineHandle, 
%   and return dataAI& dataNum to handles struct once finished.
%   
%   Modified TimerCallBack Fcn termination mode, activition of "STOP"
%   button in GUI is needed. 
% 
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % 
function InstantAI_Project1(hObject,handles)
% hObject should be the handles of main GUI figure,eg. handles.figure1, to
% convey data between InstantAI and guidata.

% % % % % % % % % % % % %another way % % % % % % % % % % % %
% global handlesconvey 
% handlesconvey = handles;

% make timer object t global to realize timer stop in another function.
global t;


% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq');

% Configure the following three parameters before running the demo.
% The default device of project is demo device, users can choose other 
% devices according to their needs. 
deviceDescription = 'USB-4704,BID#0'; 
startChannel = int32(0);
channelCount = int32(handles.ChannelCount); %default channel number is 4.

% initialize plotting set.
AxesHandles = handles.AxesHandles;
sr = handles.Fs;
period = 1/sr;

timestep = 1000/handles.Fs; % unit: ms
totallength = timestep * 100; % unit: ms %initial amount of displayed data is 100.
for j = 0:channelCount-1
    set(AxesHandles(j+1),'XLim',[0,100]);
    xticks(AxesHandles(j+1),[0 25 75 100]);
    xticklabels(AxesHandles(j+1),{'0',...
        [num2str(totallength*0.25),' ms'],...
        [num2str(totallength*0.75),' ms'],...
        [num2str(totallength),' ms']});
end
% Initial data number is 1.Run Initialization each time "BEGIN" is pressed.

% Pre-assigned memeroy, Attention this might be insufficient.
% Simultaneously change the value in "BEGIN" callback function and stop condition when change happens here.

% get stop command via global varible.


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
%     Try to assign an output for TimerFcn:
%     t = timer( 'period', 1, 'executionmode', 'fixedrate', ...
%         'StartDelay', 1);
%     t.TimerFcn = @TimerCallback;
%     [dataAI,dataNum] = TimerFcn(t,instantAiCtrl, startChannel, ...
%         channelCount, data, dataAI, dataNum, linehandle);
 
      t  = timer('TimerFcn', {@TimerCallback, instantAiCtrl, startChannel, ...
         channelCount, data,hObject}, 'period', period, 'executionmode', 'fixedrate', ...
         'StartDelay', 1);


% 
    % edittor: Ran, 2019/10/14
    % Changed Time class Instantiation format.
    % Added new varibles here: dataAI, dataNum,linehandles.  
    i = 1;
    start(t);

      uiwait(handles.figure1);
%     stop(t);
%     guidata(hObject,handles);
    
   
   
    
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
% handlesret = handlesconvey;
% 
% clear global handlesconvey
end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

function TimerCallback(obj, event, instantAiCtrl, startChannel, ...
    channelCount, data, hObject)
% % % % % % % % % %another way % % % % % % % % % % %
% global handlesconvey
% handles = handlesconvey;
% tic
handles = guidata(hObject);

dataAI = handles.dataAI; 
dataNum = handles.dataNum;
LineHandles = handles.LineHandles;
AxesHandles = handles.AxesHandles;
beishu = handles.beishu;
% timescale = handles.timescale;

errorCode = instantAiCtrl.Read(startChannel, channelCount, data); 
if BioFailed(errorCode)
    throw Exception();
end
% fprintf('\n');

% get data
for j=0:(channelCount - 1)
    temp = data.Get(j);
%     fprintf('channel %d : %10f ', j, temp);   
    dataAI(dataNum,j+1) = temp;
    
% plotting in axes areas.    
    addpoints(LineHandles(1,j+1),dataNum,temp);
    drawnow limitrate
    
    % set axes pattern when necessary
    if dataNum > (100*beishu) % 2019/10/31
        
        timestep = 1000/handles.Fs; % unit: ms
        
        set(AxesHandles(j+1),'XLim',[dataNum-90*beishu,dataNum+10]);
        xticks(AxesHandles(j+1),[dataNum-90*beishu dataNum+10]);
        xticklabels(AxesHandles(j+1),{...
            [num2str(timestep * (dataNum-90*beishu)),' ms'],...
            [num2str(timestep * (dataNum+10)),' ms']});    
    end
    
    % fill in disabled channel data with zeros.
    if channelCount < 4
        for k = channelCount+1 : 4
            dataAI(dataNum,k) = 0;
        end
    end
    
end

dataNum = dataNum + 1;

% upload input data
handles.dataAI = dataAI;
handles.dataNum = dataNum;
% handlesconvey = handles;
guidata(hObject,handles);  
% toc
end