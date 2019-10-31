
function varargout = Oscilloscope_Project1(varargin)
% OSCILLOSCOPE_PROJECT1 MATLAB code for Oscilloscope_Project1.fig
%      OSCILLOSCOPE_PROJECT1, by itself, creates a new OSCILLOSCOPE_PROJECT1 or raises the existing
%      singleton*.
%
%      H = OSCILLOSCOPE_PROJECT1 returns the handle to a new OSCILLOSCOPE_PROJECT1 or the handle to
%      the existing singleton*.
%
%      OSCILLOSCOPE_PROJECT1('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in OSCILLOSCOPE_PROJECT1.M with the given input arguments.
%
%      OSCILLOSCOPE_PROJECT1('Property','Value',...) creates a new OSCILLOSCOPE_PROJECT1 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Oscilloscope_Project1_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Oscilloscope_Project1_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Oscilloscope_Project1

% Last Modified by GUIDE v2.5 31-Oct-2019 00:05:45

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @Oscilloscope_Project1_OpeningFcn, ...
    'gui_OutputFcn',  @Oscilloscope_Project1_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT
end

% --- Executes just before Oscilloscope_Project1 is made visible.
function Oscilloscope_Project1_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Oscilloscope_Project1 (see VARARGIN)

% Choose default command line output for Oscilloscope_Project1
handles.output = hObject;

% initialize button& check box status.
set(handles.radiobutton_fft,'value',0);
set(handles.radiobutton_filter,'value',0);
set(handles.radiobutton_highpass,'value',0);
set(handles.radiobutton_lowpass,'value',0);
set(handles.radiobutton_channel0,'value',0);
set(handles.radiobutton_channel1,'value',0);
set(handles.radiobutton_channel2,'value',0);
set(handles.radiobutton_channel3,'value',0);
set(handles.checkbox_Ch0,'value',1);
set(handles.checkbox_Ch1,'value',1);
set(handles.checkbox_Ch2,'value',1);
set(handles.checkbox_Ch3,'value',1);

% initial y-axes interval.
y_high = 1.5;
y_low = -1.5;
handles.y_high = y_high;
handles.y_low = y_low;

%Slider5 的滑动条初始化
set(handles.slider5,'min',0);
set(handles.slider5,'max',10);
set(handles.slider5,'value',5);

% Pre-assign value for data structure.
dataAI = zeros(1,4);% Pre-assigned memeroy,Simultaneously change the value in "BEGIN" callback function when change happens here.
dataNum=1;
ChannelCount = 4;
ChannelSelect = [1,1,1,1];
val = zeros(4,1);  %滑动条的值
timeaxesflag = 0;
beishu = 1;


handles.timeaxesflag = timeaxesflag;
handles.beishu = beishu;
handles.ChannelCount = ChannelCount;
handles.ChannelSelect = ChannelSelect;
handles.dataAI = dataAI;
handles.dataNum = dataNum;
handles.val = val;

guidata(hObject,handles);
end


% --- Outputs from this function are returned to the command line.
function varargout = Oscilloscope_Project1_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
end


function edit_y_high_Callback(hObject, eventdata, handles)
% hObject    handle to edit_y_high (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
y_high = str2double(get(handles.edit_y_high,'string'));  %为什么只能是str2double，而不能是str2num？
handles.y_high=y_high;
guidata(hObject,handles);
axes(handles.axes1);
%set(handles.axes1,'XLim',[0,10],'YLim',[y_low,y_high]);
y_low=handles.y_low;
set(handles.axes1,'YLim',[y_low,y_high]);
set(handles.axes2,'YLim',[y_low,y_high]);
set(handles.axes3,'YLim',[y_low,y_high]);
set(handles.axes4,'YLim',[y_low,y_high]);

% Hints: get(hObject,'String') returns contents of edit_y_high as text
%        str2double(get(hObject,'String')) returns contents of edit_y_high as a double
end

% --- Executes during object creation, after setting all properties.
function edit_y_high_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

function edit_y_low_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

function edit_y_low_Callback(hObject, eventdata, handles)
y_low = str2double(get(handles.edit_y_low,'string'));
handles.y_low=y_low;
guidata(hObject,handles);
axes(handles.axes1);
%set(handles.axes1,'XLim',[0,10],'YLim',[y_low,y_high]);
y_high=handles.y_high;
set(handles.axes1,'YLim',[y_low,y_high]);
set(handles.axes2,'YLim',[y_low,y_high]);
set(handles.axes3,'YLim',[y_low,y_high]);
set(handles.axes4,'YLim',[y_low,y_high]);
end


% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
% --- Executes on button press in pushbutton_begin.
% Edittor:YCRan 2019/10/17
% Button: Start Sampling
% This function initilize the sampling process by reseting axes areas and
% calling InstantAI_Project1.
%
% InstantAI_Project1 calls a timer function that get data from AI Channel 0 ~
% Channel 3 of Device USB-4704,BID#0, the outputs are dataAI, dataNum, and
% Realtime Plots. dataAI and dataNum are stored in GUIDATA.
function pushbutton_begin_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_begin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Axes area initilization.
AxesHandles = handles.AxesHandles;
% Aviod calling axes() within a loop, which will bring extra cost of time.
axes(AxesHandles(1));
xlim auto
ylim auto
xlabel('time');ylabel('voltage/V');
axes(AxesHandles(2));
xlim auto
ylim auto
xlabel('time');ylabel('voltage/V');
axes(AxesHandles(3));
xlim auto
ylim auto
xlabel('time');ylabel('voltage/V');
axes(AxesHandles(4));
xlim auto
ylim auto
xlabel('time');ylabel('voltage/V');

% hide sliders when initilizing.
set(handles.slider1,'visible','off');
set(handles.slider2,'visible','off');
set(handles.slider3,'visible','off');
set(handles.slider4,'visible','off');

% set up animatedline in axes areas.
for i = 1:4
    cla(AxesHandles(i)); % clear exsisted data in graphs.
    line = animatedline(AxesHandles(i)); % build/re-build animatedline.
    
    handles.LineHandles(i) = line;
    
end

% set up initial property for sampling
handles.dataNum = 1;
handles.dataAI = zeros(1,4);
handles.ChannelCount = length(find(handles.ChannelSelect == 1));
handles.timeaxesflag=0;


% end initilization
guidata(hObject,handles);

% Execute Sampling
InstantAI_Project1(handles.figure1,handles);



% guidata(hObject,handles); performed in InstantAI(). DO NOT upload guidata
% here.

end
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

% --- Executes on button press in pushbutton_stop.
function pushbutton_stop_Callback(hObject, eventdata, handles)
% Stop timer callback
global t
% if isvalid(t)
    stop(t);
    delete(t);
    clear global t;
% end

uiresume(handles.figure1);

%initilize sliders and axes-zoom control.
dataNum= handles.dataNum;
timestep = 1000/handles.Fs; %unit:ms
% Fs = handles.Fs;

if dataNum > 100
   
    %slider初始值赋值
    val=handles.val;
    val=val+dataNum*ones(4,1);
    handles.val=val;
    guidata(hObject,handles);
    %channel 1的滑动条初始化
    set(handles.slider1,'min',100);
    set(handles.slider1,'max',dataNum);
    set(handles.slider1,'value',dataNum);
    %channel 2的滑动条初始化
    set(handles.slider2,'min',100);
    set(handles.slider2,'max',dataNum);
    set(handles.slider2,'value',dataNum);
    %channel 3的滑动条初始化
    set(handles.slider3,'min',100);
    set(handles.slider3,'max',dataNum);
    set(handles.slider3,'value',dataNum);
    %channel 4的滑动条初始化
    set(handles.slider4,'min',100);
    set(handles.slider4,'max',dataNum);
    set(handles.slider4,'value',dataNum);
  
    % Sliders visiblity set
    set(handles.slider1,'visible','on');
    set(handles.slider2,'visible','on');
    set(handles.slider3,'visible','on');
    set(handles.slider4,'visible','on');

    
    
    %采集结束后刷新
    dataAI=handles.dataAI;
    %channel 1刷新
    if handles.ChannelCount >= 1
        axes(handles.axes1);
        plot(dataAI(:,1),'-black');
        set(handles.axes1,'XLim',[dataNum-90,dataNum+10]);
        xticks(handles.axes1,[dataNum-90 dataNum-65 dataNum-15 dataNum+10]);
        xticklabels(handles.axes1,{...
            [num2str(timestep * (dataNum-90)),' ms'],...
            [num2str(timestep * (dataNum-65)),' ms'],...
            [num2str(timestep * (dataNum-15)),' ms'],...
            [num2str(timestep * (dataNum+10)),' ms']});
    end
    %     plot(1/Fs:1/Fs:length(dataAI(:,1))/Fs,dataAI(:,1));
    
    %     xlabel('时间/s');ylabel('voltage/V');
    %channel 2刷新
    if handles.ChannelCount >= 2
        axes(handles.axes2);
        plot(dataAI(:,2),'-black');
        set(handles.axes2,'XLim',[dataNum-90,dataNum+10]);
        xticks(handles.axes2,[dataNum-90 dataNum-65 dataNum-15 dataNum+10]);
        xticklabels(handles.axes2,{...
            [num2str(timestep * (dataNum-90)),' ms'],...
            [num2str(timestep * (dataNum-65)),' ms'],...
            [num2str(timestep * (dataNum-15)),' ms'],...
            [num2str(timestep * (dataNum+10)),' ms']});
    end
    %     plot(1/Fs:1/Fs:length(dataAI(:,2))/Fs,dataAI(:,2));
    
    %     xlabel('时间/s');ylabel('voltage/V');
    %channel 3刷新
    if handles.ChannelCount >= 3
        axes(handles.axes3);
        plot(dataAI(:,3),'-black');
        set(handles.axes3,'XLim',[dataNum-90,dataNum+10]);
        xticks(handles.axes3,[dataNum-90 dataNum-65 dataNum-15 dataNum+10]);
        xticklabels(handles.axes3,{...
            [num2str(timestep * (dataNum-90)),' ms'],...
            [num2str(timestep * (dataNum-65)),' ms'],...
            [num2str(timestep * (dataNum-15)),' ms'],...
            [num2str(timestep * (dataNum+10)),' ms']});
    end
    %     plot(1/Fs:1/Fs:length(dataAI(:,3))/Fs,dataAI(:,3));
    
    %     xlabel('时间/s');ylabel('voltage/V');
    %channel 4刷新
    if handles.ChannelCount == 4
        axes(handles.axes4);
        plot(dataAI(:,4),'-black');
        set(handles.axes4,'XLim',[dataNum-90,dataNum+10]);
        xticks(handles.axes4,[dataNum-90 dataNum-65 dataNum-15 dataNum+10]);
        xticklabels(handles.axes4,{...
            [num2str(timestep * (dataNum-90)),' ms'],...
            [num2str(timestep * (dataNum-65)),' ms'],...
            [num2str(timestep * (dataNum-15)),' ms'],...
            [num2str(timestep * (dataNum+10)),' ms']});
    end
    
    
    %     plot(1/Fs:1/Fs:length(dataAI(:,4))/Fs,dataAI(:,4));
    %     xlabel('时间/s');ylabel('voltage/V');
end
% %设置voltage轴范围
% y_high=handles.y_high;
% y_low=handles.y_low;
% set(handles.axes1,'YLim',[y_low,y_high]);
% set(handles.axes2,'YLim',[y_low,y_high]);
% set(handles.axes3,'YLim',[y_low,y_high]);
% set(handles.axes4,'YLim',[y_low,y_high]);
handles.timeaxesflag = 1;
guidata(hObject,handles);
end


function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double
end

% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

% --- Executes on button press in pushbutton_getcoordinate.
function pushbutton_getcoordinate_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_getcoordinate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
datacursormode toggle;
% set(dcm_obj,'Enable','
% dcm_obj=datacursormode(gcf);
% set(dcm_obj,'DisplayStyle','datatip','Enable','on')
% for i=1:10
%     disp('click')
%     pause
%     c_info=getCursorInfo(dcm_obj);
%     pos=c_info.Position;
%     set(handles.edit4,'string',pos(1));
%     set(handles.edit5,'string',pos(2));
% end
end

function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double
end

% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
v1 = get(handles.slider1,'value');      %v1是滑动条的值，一开始是dataNum，横坐标的最大值是v1+50
handles.val(1)=v1;
guidata(hObject,handles);
gainvalue = get(handles.slider5,'value');   %得到缩放滑动条的值
Fs=handles.Fs;
x=handles.dataAI(:,1);
N=length(x);
xmin=v1-100-(5-gainvalue)*10;
xmax=v1+15-gainvalue;
if xmax>N+10
    xmax=N+10;end
if xmin<0
    xmin=0;end
set(handles.axes1,'XLim',[xmin,xmax]);
end



% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
v2 = get(handles.slider2,'value');
handles.val(2)=v2;
guidata(hObject,handles);
if v2>=100
    set(handles.axes2,'XLim',[v2-100,v2+10]);
else set(handles.axes2,'XLim',[0,110]);
end
end

% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end

function slider3_Callback(hObject, eventdata, handles)
v3 = get(handles.slider3,'value');
handles.val(3)=v3;
guidata(hObject,handles);
if v3>=100
    set(handles.axes3,'XLim',[v3-100,v3+10]);
else
    set(handles.axes3,'XLim',[0,110]);
end
end

% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end

% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end

% --- Executes on slider movement.
function slider4_Callback(hObject, eventdata, handles)
v4 = get(handles.slider4,'value');
handles.val(4)=v4;
guidata(hObject,handles);
if v4>=100
    set(handles.axes4,'XLim',[v4-100,v4+10]);
else set(handles.axes4,'XLim',[0,110]);
end
end

% --- Executes during object creation, after setting all properties.
function slider4_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end


function slider5_Callback(hObject, eventdata, handles)
timeaxesflag=handles.timeaxesflag;
gainvalue=get(handles.slider5,'value');
Fs=handles.Fs;
if gainvalue<=1
    beishu=10;
else
    if gainvalue<=3
        beishu = 5;
    else
        if gainvalue<5
            beishu = 2;
        else
            if gainvalue == 5
                beishu = 1;
            else
                if gainvalue<=7
                    beishu = 0.5;
                else
                    if gainvalue<=9
                        beishu = 0.2;
                    else
                        if gainvalue<=10
                            beishu = 0.1;
                        end
                    end
                end
            end
        end
    end
end

handles.beishu=beishu;
guidata(hObject,handles);

if timeaxesflag == 1
    v1=handles.val(1);
    N=handles.dataNum;
    if N<=90
        xmin=0;xmax=100*beishu;
    else
        xmin=v1-90*beishu;
        xmax=v1+10*beishu;
        if xmax>N+10
            xmax=N+10;end
        if xmin<0
            xmin=0;end
    end
    %时间轴待设置
    set(handles.axes1,'XLim',[xmin,xmax]);
end

end

% --- Executes during object creation, after setting all properties.
function slider5_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end





function edit_sample_Callback(hObject, eventdata, handles)
% hObject    handle to edit_sample (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Fs=str2double(get(handles.edit_sample,'string'));
handles.Fs=Fs;
guidata(hObject,handles);
% Hints: get(hObject,'String') returns contents of edit_sample as text
%        str2double(get(hObject,'String')) returns contents of edit_sample as a double
end

% --- Executes during object creation, after setting all properties.
function edit_sample_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_sample (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
set(hObject,'string','1');
handles.Fs = 1;
guidata(hObject,handles);
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

% --- Executes on button press in pushbutton_process.
function pushbutton_process_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_process (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
dataAI=handles.dataAI;
Fs=handles.Fs;
fc=handles.fc;
choose_channel=handles.choose_channel;
process=handles.process;
x=dataAI(:,choose_channel);
N=length(x);
switch process
    case 1
        [n,y]=filter_highpass(Fs,x,fc);
        axes(handles.axes5);plot(n/Fs,y);
        xlabel('时间/s');ylabel('voltage/V');grid on;
        [f,yy]=signal_fft(y,Fs);
        axes(handles.axes8);
        % %单边显示格式
        plot(f(1:N/2),yy(1:N/2)*2/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
    case 2
        [n,y]=filter_lowpass(Fs,x,fc);
        axes(handles.axes5);plot(n/Fs,y);
        xlabel('时间/s');ylabel('voltage/V');grid on;
        [f,yy]=signal_fft(y,Fs);
        axes(handles.axes8);
        % %单边显示格式
        plot(f(1:N/2),yy(1:N/2)*2/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
    case 3
        [f,y]=signal_fft(x,Fs);
        axes(handles.axes5);
        %双边显示格式
        plot(f,y/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
        %单边显示格式
        axes(handles.axes8);
        plot(f(1:N/2),y(1:N/2)*2/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
end
end


function edit_fc_Callback(hObject, eventdata, handles)
% hObject    handle to edit_fc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_fc as text
%        str2double(get(hObject,'String')) returns contents of edit_fc as a double
fc = str2num(get(handles.edit_fc,'string'));
handles.fc=fc;
guidata(hObject,handles);
end

% --- Executes during object creation, after setting all properties.
function edit_fc_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_fc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end

% --- Executes on button press in pushbutton_import.
function pushbutton_import_Callback(hObject, eventdata, handles)
[filename,pathname] = uigetfile(...
    {'*.*', 'All Files (*.*)';...
    '*.m;*.mlx;*.fig;*.mat;*.slx;*.mdl','MATLAB Files (*.m,*.mlx,*.fig,*.mat,*.slx,*.mdl)';...
    '*.csv','CSV(逗号分隔文件) (*.csv)'; ...
    '*.txt','文本文档 (*.txt)'; ...
    '*.xls','Excel电子文档 (*.xls)';});


file = [pathname,filename];

if ischar(filename)
    dataAI = Signalread(file);
    dataNum = length(dataAI(:,1));
    handles.dataNum = dataNum;
    handles.dataAI = dataAI;
    guidata(hObject,handles);
end

% Initilization.
AxesHandles = handles.AxesHandles;
% Aviod calling axes() within a loop, which will bring extra cost of time.
axes(AxesHandles(1));
xlim auto
ylim auto
xlabel('Samples');ylabel('voltage/V');
axes(AxesHandles(2));
xlim auto
ylim auto
xlabel('Samples');ylabel('voltage/V');
axes(AxesHandles(3));
xlim auto
ylim auto
xlabel('Samples');ylabel('voltage/V');
axes(AxesHandles(4));
xlim auto
ylim auto
xlabel('Samples');ylabel('voltage/V');

% hide sliders when initilizing.
set(handles.slider1,'visible','off');
set(handles.slider2,'visible','off');
set(handles.slider3,'visible','off');
set(handles.slider4,'visible','off');

%设置横坐标和滑动条的初始化
%channel 1
N1=length(dataAI(:,1));
if N1 > 100
   
    set(handles.axes1,'XLim',[0,N1*1.1]);
    set(handles.slider1,'min',100)
    set(handles.slider1,'max',N1);
    set(handles.slider1,'value',N1);
    set(handles.slider1,'visible','on');
end

%channel 2
N2 = length(dataAI(:,2));
if N2 > 100

    set(handles.axes2,'XLim',[0,N2*1.1]);
    set(handles.slider2,'min',100)
    set(handles.slider2,'max',N2);
    set(handles.slider2,'value',N2);
    set(handles.slider2,'visible','on');
end

%channel 3
N3 = length(dataAI(:,3));
if N3 > 100
   
    set(handles.axes3,'XLim',[0,N3*1.1]);
    set(handles.slider3,'min',100)
    set(handles.slider3,'max',N3);
    set(handles.slider3,'value',N3);
    set(handles.slider3,'visible','on');
end

%channel 4
N4 = length(dataAI(:,4));
if N4 > 100

    set(handles.axes1,'XLim',[0,N4*1.1]);
    set(handles.slider4,'min',100)
    set(handles.slider4,'max',N4);
    set(handles.slider4,'value',N4);
    set(handles.slider4,'visible','on');
end
%channel 1的收缩滑动条初始化-只有放大没有缩小
set(handles.slider5,'min',0)
set(handles.slider5,'max',10);
set(handles.slider5,'value',5);

% Fs=handles.Fs;
% display data read on axes areas.
if ischar(filename)
    AxesHandles = handles.AxesHandles;
    for i = 1:4
        cla(AxesHandles(i)); % clear exsisted data in graphs.
        plot(AxesHandles(i),dataAI(:,i),'-black');
%         plot(AxesHandles(i),1/Fs:1/Fs:length(dataAI(:,i))/Fs,dataAI(:,i));
        xlabel('时间/s');ylabel('voltage/V');
    end
end

%设置voltage轴范围
% y_high=handles.y_high;
% y_low=handles.y_low;
% set(handles.axes1,'YLim',[y_low,y_high]);
% set(handles.axes2,'YLim',[y_low,y_high]);
% set(handles.axes3,'YLim',[y_low,y_high]);
% set(handles.axes4,'YLim',[y_low,y_high]);

guidata(hObject,handles);
end

% --- Executes on button press in pushbutton_save.
function pushbutton_save_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_save (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

datasave = handles.dataAI;

[filename, pathname, filterindex] = uiputfile( ...
    {'*.mat','MATLAB Data (*.m)';
    '*.csv','CSV(逗号分隔)(*.csv)';...
    '*.txt','Unicode文本(*.txt)';...
    '*.xls','Excel 工作簿(*.xls)'});
% call windows explorer to save the file.
% if the explorer is closed without confirming save, filename will be 0.


file = [pathname,filename];

filesave = Signalwrite;
% filesave = [filewrite,suffix(filterindex)];
if ischar(filename)
    %     if explorer is closed without confirming save, filename will be 0.
    switch filterindex
        case 1 %.mat
            filesave.mat(datasave,file);
        case 2 %.csv
            filesave.csv(datasave,file);
        case 3 %.txt
            filesave.txt(datasave,file);
        case 4 %.xls
            filesave.xls(datasave,file);
        otherwise
            fprintf('Save Failled! Unexpected erro occurred!');
    end
    
    fprintf('/nSave Succeeded!');
    
end
end

% --- Executes on button press in radiobutton_filter.
function radiobutton_filter_Callback(hObject, eventdata, handles)
filt=1;
handles.filt=filt;
guidata(hObject,handles);
end

% --- Executes on button press in radiobutton_highpass.
function radiobutton_highpass_Callback(hObject, eventdata, handles)
filt=handles.filt;
process=1;
handles.process=process;
guidata(hObject,handles);
if filt==0
    errordlg('未选择“滤波”操作方式');
end
end

% --- Executes on button press in radiobutton_lowpass.
function radiobutton_lowpass_Callback(hObject, eventdata, handles)
filt=handles.filt;
process=2;
handles.process=process;
guidata(hObject,handles);
if filt==0
    errordlg('未选择“滤波”操作方式');
end
end

% --- Executes on button press in radiobutton_fft.
function radiobutton_fft_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_fft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
process=3;
handles.process=process;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_fft
end

% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(1) = AxesHandles;
guidata(hObject,handles);
% Hint: place code in OpeningFcn to populate axes1
end
% --- Executes during object creation, after setting all properties.


% --- Executes during object creation, after setting all properties.
function axes2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(2) = AxesHandles;
guidata(hObject,handles);
% Hint: place code in OpeningFcn to populate axes2
end


% --- Executes during object creation, after setting all properties.
function axes3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(3) = AxesHandles;
guidata(hObject,handles);
% Hint: place code in OpeningFcn to populate axes3
end

% --- Executes during object creation, after setting all properties.
function axes4_CreateFcn(hObject, eventdata, handles)
AxesHandles = gca;
handles.AxesHandles(4) = AxesHandles;
guidata(hObject,handles);
end

%
% % --- Executes on button press in checkbox4.
% function checkbox4_Callback(hObject, eventdata, handles)
% % hObject    handle to checkbox4 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% LineActivity =  get(hObject,'Value');
% handles.LineActivity(1) = LineActivity;
% guidata(hObject,handles);
% end
% % Hint: get(hObject,'Value') returns toggle state of checkbox4
%


% --- Executes during object creation, after setting all properties.
function radiobutton_channel0_CreateFcn(hObject, eventdata, handles)
end
% --- Executes on button press in radiobutton_channel0.
function radiobutton_channel0_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_channel0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
choose_channel=1;
handles.choose_channel=choose_channel;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_channel0
end

% --- Executes during object creation, after setting all properties.
function radiobutton_channel1_CreateFcn(hObject, eventdata, handles)
end
% --- Executes on button press in radiobutton_channel1.
function radiobutton_channel1_Callback(hObject, eventdata, handles)
choose_channel=2;
handles.choose_channel=choose_channel;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_channel1
end
% --- Executes during object creation, after setting all properties.
function radiobutton_channel2_CreateFcn(hObject, eventdata, handles)
end
% --- Executes on button press in radiobutton_channel2.
function radiobutton_channel2_Callback(hObject, eventdata, handles)
choose_channel=3;
handles.choose_channel=choose_channel;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_channel2
end
% --- Executes during object creation, after setting all properties.
function radiobutton_channel3_CreateFcn(hObject, eventdata, handles)
end
% --- Executes on button press in radiobutton_channel3.
function radiobutton_channel3_Callback(hObject, eventdata, handles)
choose_channel=4;
handles.choose_channel=choose_channel;
guidata(hObject,handles);
end

% --- Executes during object deletion, before destroying properties.
function pushbutton_stop_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
end

% --- Executes during object deletion, before destroying properties.
function pushbutton_stop_CreateFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
end



% --- Executes on button press in checkbox_Ch0.
function checkbox_Ch0_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
flag = get(hObject,'Value');
if flag
    set(handles.checkbox_Ch1,'Enable','on');
else
    set(handles.checkbox_Ch1,'Enable','off');
    set(handles.checkbox_Ch2,'Enable','off');
    set(handles.checkbox_Ch3,'Enable','off');
    set(handles.checkbox_Ch1, 'Value',0);
    set(handles.checkbox_Ch2, 'Value',0);
    set(handles.checkbox_Ch3, 'Value',0);
    handles.ChannelSelect(2) = 0;
    handles.ChannelSelect(3) = 0;
    handles.ChannelSelect(4) = 0;
end


handles.ChannelSelect(1) = flag;
guidata(hObject,handles);
end
% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch0


% --- Executes on button press in checkbox_Ch1.
function checkbox_Ch1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
flag = get(hObject,'Value');
if flag
    set(handles.checkbox_Ch2,'Enable','on');
else
    set(handles.checkbox_Ch2,'Enable','off');
    set(handles.checkbox_Ch3,'Enable','off');
    set(handles.checkbox_Ch2,'Value',0);
    set(handles.checkbox_Ch3,'Value',0);
    handles.ChannelSelect(3) = 0;
    handles.ChannelSelect(4) = 0;
end

handles.ChannelSelect(2) = flag;
guidata(hObject,handles);
end
% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch1


% --- Executes on button press in checkbox_Ch2.
function checkbox_Ch2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
flag = get(hObject,'Value');
if flag
    set(handles.checkbox_Ch3,'Enable','on');
else
    set(handles.checkbox_Ch3,'Enable','off');
    set(handles.checkbox_Ch3,'Value',0);
    handles.ChannelSelect(4) = 0;
end

handles.ChannelSelect(3) = flag;
guidata(hObject,handles);
end
% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch2


% --- Executes on button press in checkbox_Ch3.
function checkbox_Ch3_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
flag = get(hObject,'Value');

handles.ChannelSelect(4) = flag;
guidata(hObject,handles);
end
% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch3
