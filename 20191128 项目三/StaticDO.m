% StaticDO.m
%
% Example Category:
%    DIO
% Matlab(2010 or 2010 above)
%
% Description:
%    This example demonstrates how to use Static DO function.
%
% Instructions for Running:
%    1. Set the 'deviceDescription' for opening the device. 
%    2. Set the 'startPort' as the first port for Do.
%    3. Set the 'portCount' to decide how many sequential ports to 
%       operate Do.
%
% I/O Connections Overview:
%    Please refer to your hardware reference manual.

function StaticDO(hObject,handles)

% Make Automation.BDaq assembly visible to MATLAB.
BDaq = NET.addAssembly('Automation.BDaq4');

% Configure the following three parameters before running the demo.
% The default device of project is demo device, users can choose other 
% devices according to their needs. 
deviceDescription = 'USB-4704,BID#0'; 
% startPort = int32(0);
% portCount = int32(1);
global t1;

contiflag=handles.contiflag;
period=handles.period;
period=period/2;
f=handles.fvalue;
time=handles.time;
N=time*f;

errorCode = Automation.BDaq.ErrorCode.Success;

% Step 1: Create a 'InstantDoCtrl' for DO function.
instantDoCtrl = Automation.BDaq.InstantDoCtrl();

try
    % Step 2: Select a device by device number or device description and 
    % specify the access mode. In this example we use 
    % ModeWrite(default) mode so that we can fully control the 
    % device, including configuring, sampling, etc.
    instantDoCtrl.SelectedDevice = Automation.BDaq.DeviceInformation(...
        deviceDescription);
    
    % Step 3: Write DO ports
    bufferForWriting = NET.createArray('System.Byte', int32(64));
    t1 = timer('TimerFcn', {@TimerCallback_DO, instantDoCtrl, ...
        bufferForWriting, N, contiflag, hObject},'period', period, ...
        'executionmode', 'fixedrate', 'StartDelay', 1);
    start(t1);
    uiwait(handles.figure1);
%     for i = 0:(portCount - 1)
%         fprintf('Input a hexadecimal number for DO port %d to output', ...
%             startPort + i);
%         strData = input('(for example, 0x11)\n', 's'); 
%         strData = System.String(strData);
%         if strData.Substring(0, 2) == '0x'
%             strData = strData.Remove(0, 2);
%         end
%         strData = hex2dec(char(strData));      
%         bufferForWriting.Set(i, strData); 
%     end
%     errorCode = instantDoCtrl.Write(startPort, portCount, ...
%         bufferForWriting);
%     if BioFailed(errorCode)
%         throw  Exception();
%     end
%     disp('DO output completed!');
    % Read back the DO status.
    % Note:
    % For relay output, the read back must be deferred until 
    % the relay is stable.
    % The delay time is decided by the HW SPEC.
%     bufferForReading = NET.createArray('System.Byte', int32(64));
%     instantDoCtrl.Read(startPort, portCount, bufferForReading);
%     if BioFailed(errorCode)
%         throw  Exception();
%    end
%     % Show DO ports' status
%     for i = startPort:(portCount + startPort - 1)
%        fprintf('Now, DO port %d status is:  0x%X\n', i, ...
%             bufferForReading.Get(i - startPort));
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
instantDoCtrl.Dispose();

end

function result = BioFailed(errorCode)

result =  errorCode < Automation.BDaq.ErrorCode.Success && ...
    errorCode >= Automation.BDaq.ErrorCode.ErrorHandleNotValid;

end

function TimerCallback_DO(obj, event, instantDoCtrl, bufferForWriting, N,...
    contiflag,hObject)
handles = guidata(hObject);
i=handles.i;
i=i+1;
if mod(i,2)==0
    strData = 0;   
else 
    strData = 1;
end
    bufferForWriting.Set(0, strData); 
    errorCode = instantDoCtrl.Write(0, 1 , ...
        bufferForWriting);
    if BioFailed(errorCode)
        throw  Exception();
    end
    
if contiflag==0
   if i==N
       i=0;
       stop(obj);
       delete(obj);
       uiresume(handles.figure1);
   end
end
handles.i=i;
guidata(hObject,handles);
end





















