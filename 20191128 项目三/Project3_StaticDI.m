% StaticDI.m
%
% Example Category:
%    DIO
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Static DI function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'startPort' as the first port for Di scanning.
%    3. Set the 'portCount' to decide how many sequential ports to 
%       operate Di scanning.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function Project3_StaticDI(hObject)
global t2;
% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq');

% Configure the following three parameters before running the demo.
% The default device of project is demo device, users can choose other 
% devices according to their needs. 
deviceDescription = 'USB-4704,BID#0';
startPort = int32(0);
portCount = int32(1);
errorCode = Automation.BDaq.ErrorCode.Success;

% Step 1: Create a 'InstantDiCtrl' for DI function.
% and initialize from guidata.
instantDiCtrl = Automation.BDaq.InstantDiCtrl();

handles = guidata(hObject);


try
    % Step 2: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    instantDiCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    
    % Step 3: read DI ports' status and show.
    buffer = NET.createArray('System.Byte', int32(64));
    t2 = timer('TimerFcn', {@TimerCallback_DI, instantDiCtrl, startPort, ...
        portCount, buffer, hObject}, 'period', 1, 'executionmode', 'fixedrate', ...
        'StartDelay', 1);
    start(t2);
%      fprintf('Reading ports'' status is in progress...');
%     input('Press Enter key to quit!', 's');    
%     stop(t);
%     delete(t); 

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


uiwait(handles.figure1);
% Step 4: Close device and release any allocated resource.
instantDiCtrl.Dispose();

end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

function TimerCallback_DI(obj, event, instantDiCtrl, startPort, ...
    portCount, buffer, hObject)
% Initialize from guidata.
handles = guidata(hObject);

str_handles = handles.text_input;
enable_handles = handles.text_onoff;
amplitude_handles = handles.text_amplitude;
frequency_handles = handles.text_frequency;
axes_handles = handles.axes1;


errorCode = instantDiCtrl.Read(startPort, portCount, buffer); 
if BioFailed(errorCode)
    throw Exception();
end
% USB-4704 only support one port DI input(portCount always =1), so for loop is unecessart here.
% temp = zeros(4,1);
% for i=0:(portCount - 1)
%     temp(i) = buffer.Get(i);
%     fprintf('\nDI port %d status : 0x%X', startPort + i, ...
%        temp(i));
% end

temp = buffer.Get(0);

DI_Input = dec2bin(temp,8); % DI_Input is a 1x8(Nx8) char array. 
enable_DI = bin2dec(DI_Input(1,8));
amplitude_DI = bin2dec(DI_Input(1,6:7));
frequency_DI = bin2dec(DI_Input(1,1:5));

% refresh gui text display.
set(str_handles,'String',DI_Input(1,:));
set(amplitude_handles,'String',num2str(amplitude_DI));
set(frequency_handles,'String',num2str(frequency_DI));
if enable_DI
    set(enable_handles,'String','¿ªÊ¼');
else
    set(enable_handles,'String','Í£Ö¹');
end

% refresh axes graphic display
cla(axes_handles);
%set axis labels
xlabel(handles.axes1,'time /sec');
ylabel(handles.axes1,'voltage /V');

if enable_DI
    x = linspace(0,1,1000); % display range: 0~1 second. Pi will be reducted.
    sqwave = square(2*pi*frequency_DI*x) * amplitude_DI; %period: a/2*pi. square(a*x + b);
    plot(axes_handles,x,sqwave);
    set(axes_handles,'Ylim',[-amplitude_DI-0.5 amplitude_DI+0.5]);
end

    
    
% upload guidata
handles.DI_Input = DI_Input;
handles.enable_DI = enable_DI;
handles.amplitude_DI = amplitude_DI;
handles.frequency_DI = frequency_DI;
guidata(hObject,handles);
end