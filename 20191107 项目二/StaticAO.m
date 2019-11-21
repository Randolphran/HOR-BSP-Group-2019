% StaticAO.m
%
% Example Category:
%    AO
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Static AO  voltage function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'channelStart' as the first channel for  analog data
%       Output. 
%    3. Set the 'channelCount' to decide how many sequential channels to
%       output analog data. 
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function StaticAO(hObject,handles)

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq');

% Define how many data to makeup a waveform period.
% oneWavePointCount = int32(512);

% Configure the following three parameters before running the demo.
% The default device of project is demo device, users can set other devices 
% according to their needs. 
deviceDescription = 'USB-4704,BID#0';

global t;
channelStart = int32(0);
channelCount = int32(1);
ppp=handles.ppp;
f=handles.frequency;
period=1/(f*ppp);
scaledWaveForm=handles.dataAO;

% Declare the type of signal. If you want to specify the type of output 
% signal, please change 'style' parameter in the GenerateWaveform function.
parent_id = H5T.copy('H5T_NATIVE_UINT');
WaveStyle = H5T.enum_create(parent_id);
H5T.enum_insert(WaveStyle, 'Sine', 0);
H5T.enum_insert(WaveStyle, 'Sawtooth', 1);
H5T.enum_insert(WaveStyle, 'Square', 2);
H5T.close(parent_id);

errorCode = Automation.BDaq.ErrorCode.Success;

% Step 1: Create a 'InstantAoCtrl' for Instant AO function.
instantAoCtrl = Automation.BDaq.InstantAoCtrl();

try
    % Step 2: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    instantAoCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    
    % Step 3: Output data. 
    % Generate waveform data.
%     scaledWaveForm = NET.createArray('System.Double', channelCount * ...
%         oneWavePointCount);
%     errorCode = GenerateWaveform(instantAoCtrl, channelStart, ...
%         channelCount, scaledWaveForm, channelCount * oneWavePointCount, ...
%         H5T.enum_nameof(WaveStyle, int32(0)));
%         % here int32(0) defined the wavestyle, which is listed upward.
%         % oneWavePointCount is also an editable property.
%     if BioFailed(errorCode)    
%         throw Exception();
%     end

    % Output data
    scaleData = NET.createArray('System.Double', int32(64));
    
    t = timer('TimerFcn',{@TimerCallback, instantAoCtrl, ...
        ppp, scaleData, scaledWaveForm, channelStart, ...
        channelCount,hObject}, 'period',period, 'executionmode', 'fixedrate', ...
        'StartDelay', 1);
    start(t);
    uiwait(handles.figure1);
%     input('Outputting data...Press Enter key to quit!', 's');
%     if isvalid(t)
%     disp('StaticAO is completed compulsorily!');    
%     stop(t);
%     delete(t); 
%     end
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
instantAoCtrl.Dispose();
H5T.close(WaveStyle);

end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

function TimerCallback(obj, event, instantAoCtrl, oneWavePointCount, ...
    scaleData, scaledWaveForm, channelStart, channelCount, hObject)
handles = guidata(hObject);

contiflag=handles.contiflag;
periodNum=handles.periodNum;
i=handles.i;
i = i + 1;
handles.i=i;
j = 0;
if i <=oneWavePointCount
    if j <= (channelCount - 1)
        scaleData.Set(j, scaledWaveForm(i));
        errorCode = instantAoCtrl.Write(channelStart,...
            channelCount, scaleData);
        if BioFailed(errorCode)
            e = MException('DAQWarning:Notcompleted', ...
                'StaticAO is completed compulsorily!');
            throw (e);
        end
    end
else if contiflag==1
    i=0; % constant output mode
    handles.i=i;
    else
    periodcount=handles.periodcount;
    periodcount=periodcount+1;% x-shot output mode
    handles.periodcount=periodcount;
    if periodcount<=periodNum
        i=0;
        handles.i=i;
    else
%         clear functions;
        stop(obj);
        delete(obj);
       fprintf('\nStaticAO is completed, and press Enter key to quit!');
    end
    end
end
guidata(hObject,handles);
end