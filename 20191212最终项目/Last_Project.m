function varargout = Last_Project(varargin)
% LAST_PROJECT MATLAB code for Last_Project.fig
%      LAST_PROJECT, by itself, creates a new LAST_PROJECT or raises the existing
%      singleton*.
%
%      H = LAST_PROJECT returns the handle to a new LAST_PROJECT or the handle to
%      the existing singleton*.
%
%      LAST_PROJECT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in LAST_PROJECT.M with the given input arguments.
%
%      LAST_PROJECT('Property','Value',...) creates a new LAST_PROJECT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Last_Project_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Last_Project_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Last_Project

% Last Modified by GUIDE v2.5 19-Dec-2019 12:28:42

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Last_Project_OpeningFcn, ...
                   'gui_OutputFcn',  @Last_Project_OutputFcn, ...
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


% --- Executes just before Last_Project is made visible.
function Last_Project_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Last_Project (see VARARGIN)

% Choose default command line output for Last_Project
handles.output = hObject;
set(handles.uipanel1,'visible','off');
set(handles.uipanel2,'visible','off');

%------------------------------------------------------------------------------%
%------------------------Oscilloscope_Project1的初始化--------------------------%
%-------------------------------------------------------------------------------%
set(handles.radiobutton_fft1,'value',0);
set(handles.radiobutton_filter1,'value',0);
set(handles.radiobutton_highpass1,'value',0);
set(handles.radiobutton_lowpass1,'value',0);
set(handles.radiobutton_highpass1,'Enable','off');
set(handles.radiobutton_lowpass1,'Enable','off');
set(handles.radiobutton_channel0,'value',0);
set(handles.radiobutton_channel1,'value',0);
set(handles.radiobutton_channel2,'value',0);
set(handles.radiobutton_channel3,'value',0);
set(handles.checkbox_Ch0,'value',1);
set(handles.checkbox_Ch1,'value',1);
set(handles.checkbox_Ch2,'value',1);
set(handles.checkbox_Ch3,'value',1);
process = 0;
choose_channel = 0;

% initialize edit boxes status.
set(handles.edit_sample1,'string','1');
set(handles.edit_fc1,'string','1');
Fs = 1; % Sampling rate
fc = 1; % Cut-off frequncy

% initialize pushbutton status.
set(handles.pushbutton_process1,'Enable','off');

% initial y-axes interval.
y_high = 1.5;
y_low = -1.5;

%滑动条初始化
val = zeros(4,1);  %滑动条的值
set(handles.slider5,'min',0);
set(handles.slider5,'max',10);
set(handles.slider5,'value',5);

timeaxesflag = 0;
beishu = 1;

% Pre-assign value for data structure.
dataAI = zeros(1,4);% Pre-assigned memeroy,Simultaneously change the value in "BEGIN" callback function when change happens here.
dataNum = 1;

ChannelCount = 4;
ChannelSelect = [1,1,1,1];

handles.y_high = y_high;
handles.y_low = y_low;
handles.timeaxesflag = timeaxesflag;
handles.beishu = beishu;
handles.ChannelCount = ChannelCount;
handles.ChannelSelect = ChannelSelect;
handles.Fs = Fs;
handles.fc=fc;
handles.dataAI = dataAI;
handles.dataNum = dataNum;
handles.val = val;
handles.process = process;
handles.choose_channel = choose_channel;
%------------------------------------------------------------------------------%
%------------------------Oscilloscope_Project1的初始化结束--------------------------%
%-------------------------------------------------------------------------------%

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Last_Project wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = Last_Project_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --------------------------------------------------------------------
function DO_DI_Callback(hObject, eventdata, handles)
% hObject    handle to DO_DI (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.uipanel1,'visible','on');
set(handles.uipanel2,'visible','off');

% --- Executes on slider movement.
function slider_frequency3_Callback(hObject, eventdata, handles)
% hObject    handle to slider_frequency3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider_frequency3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_frequency3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --------------------------------------------------------------------
function Oscilloscope_Callback(hObject, eventdata, handles)
% hObject    handle to Oscilloscope (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%Oscilloscope_Project1;
set(handles.uipanel1,'visible','off');
set(handles.uipanel2,'visible','on');

% --------------------------------------------------------------------
function Signal_Generator_Callback(hObject, eventdata, handles)
% hObject    handle to Signal_Generator (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_y_high1_Callback(hObject, eventdata, handles)
y_high = str2double(get(handles.edit_y_high1,'string'));  %为什么只能是str2double，而不能是str2num？
handles.y_high=y_high;
guidata(hObject,handles);
axes(handles.axes1);
%set(handles.axes1,'XLim',[0,10],'YLim',[y_low,y_high]);
y_low=handles.y_low;
set(handles.axes1,'YLim',[y_low,y_high]);
set(handles.axes2,'YLim',[y_low,y_high]);
set(handles.axes3,'YLim',[y_low,y_high]);
set(handles.axes4,'YLim',[y_low,y_high]);
% Hints: get(hObject,'String') returns contents of edit_y_high1 as text
%        str2double(get(hObject,'String')) returns contents of edit_y_high1 as a double


% --- Executes during object creation, after setting all properties.
function edit_y_high1_CreateFcn(hObject, eventdata, handles)
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function edit_y_low1_Callback(hObject, eventdata, handles)
y_low = str2double(get(handles.edit_y_low1,'string'));
handles.y_low=y_low;
guidata(hObject,handles);
axes(handles.axes1);
%set(handles.axes1,'XLim',[0,10],'YLim',[y_low,y_high]);
y_high=handles.y_high;
set(handles.axes1,'YLim',[y_low,y_high]);
set(handles.axes2,'YLim',[y_low,y_high]);
set(handles.axes3,'YLim',[y_low,y_high]);
set(handles.axes4,'YLim',[y_low,y_high]);
% Hints: get(hObject,'String') returns contents of edit_y_low1 as text
%        str2double(get(hObject,'String')) returns contents of edit_y_low1 as a double


% --- Executes during object creation, after setting all properties.
function edit_y_low1_CreateFcn(hObject, eventdata, handles)

%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton_begin1.
function pushbutton_begin1_Callback(hObject, eventdata, handles)
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

% x-axes zooming reset
set(handles.slider5,'Value',5);
handles.beishu = 1;

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

% --- Executes on button press in pushbutton_coordinate1.
function pushbutton_coordinate1_Callback(hObject, eventdata, handles)
datacursormode toggle;

% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
v1 = get(handles.slider1,'value');      %v1是滑动条的值，一开始是dataNum，横坐标的最大值是v1+50
handles.val(1)=v1;
guidata(hObject,handles);

beishu=handles.beishu;   %得到缩放滑动条的值
Fs=handles.Fs;
N=handles.dataNum;

timestep = 1000/handles.Fs;

xmin=v1-90*beishu;
xmax=v1+10*beishu;

if xmax>N+10
    xmax=N+10;end
if xmin<0
    xmin=0;end

set(handles.axes1,'XLim',[xmin,xmax]);
 xticks(handles.axes1,[xmin,xmax]);
    xticklabels(handles.axes1,{...
        [num2str(round(timestep * xmin)),' ms'],...
        [num2str(round(timestep * xmax)),' ms']});


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider3_Callback(hObject, eventdata, handles)
v3 = get(handles.slider3,'value');
handles.val(3)=v3;
guidata(hObject,handles);

timestep = 1000/handles.Fs;

if v3>=90
    set(handles.axes3,'XLim',[v3-90,v3+10]);
    xticks(handles.axes3,[v3-90,v3+10]);
    xticklabels(handles.axes3,{...
        [num2str(round(timestep * (v3-90))),' ms'],...
        [num2str(round(timestep * (v3+10))),' ms']});
else
    set(handles.axes3,'XLim',[0,100]);
end

% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)

if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)

v2 = get(handles.slider2,'value');
handles.val(2)=v2;
guidata(hObject,handles);

timestep = 1000/handles.Fs;

if v2>=90
    set(handles.axes2,'XLim',[v2-90,v2+10]);
    xticks(handles.axes2,[v2-90,v2+10]);
    xticklabels(handles.axes2,{...
        [num2str(round(timestep * (v2-90))),' ms'],...
        [num2str(round(timestep * (v2+10))),' ms']});
else
    set(handles.axes2,'XLim',[0,100]);
end


% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in pushbutton_stop1.
function pushbutton_stop1_Callback(hObject, eventdata, handles)
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
dataAI = handles.dataAI;
timestep = 1000/handles.Fs; %unit:ms
beishu = handles.beishu;
% Fs = handles.Fs;

if dataNum > 100*beishu
   
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
    %channel 1刷新
    if handles.ChannelCount >= 1
        axes(handles.axes1);
        plot(dataAI(:,1),'-black');
        set(handles.axes1,'XLim',[dataNum-90*beishu,dataNum+10]);
        xticks(handles.axes1,[dataNum-90*beishu dataNum+10]);
        xticklabels(handles.axes1,{...
            [num2str(timestep * (dataNum-90*beishu)),' ms'],...
            [num2str(timestep * (dataNum+10)),' ms']});
    end
    %     plot(1/Fs:1/Fs:length(dataAI(:,1))/Fs,dataAI(:,1));
    
    %     xlabel('时间/s');ylabel('voltage/V');
    %channel 2刷新
    if handles.ChannelCount >= 2
        axes(handles.axes2);
        plot(dataAI(:,2),'-black');
        set(handles.axes2,'XLim',[dataNum-90*beishu,dataNum+10]);
        xticks(handles.axes2,[dataNum-90*beishu dataNum+10]);
        xticklabels(handles.axes2,{...
            [num2str(timestep * (dataNum-90*beishu)),' ms']...
            [num2str(timestep * (dataNum+10)),' ms']});
    end
    %     plot(1/Fs:1/Fs:length(dataAI(:,2))/Fs,dataAI(:,2));
    
    %     xlabel('时间/s');ylabel('voltage/V');
    %channel 3刷新
    if handles.ChannelCount >= 3
        axes(handles.axes3);
        plot(dataAI(:,3),'-black');
        set(handles.axes3,'XLim',[dataNum-90*beishu,dataNum+10]);
        xticks(handles.axes3,[dataNum-90*beishu dataNum+10]);
        xticklabels(handles.axes3,{...
            [num2str(timestep * (dataNum-90*beishu)),' ms'],...
            [num2str(timestep * (dataNum+10)),' ms']});
    end
    %     plot(1/Fs:1/Fs:length(dataAI(:,3))/Fs,dataAI(:,3));
    
    %     xlabel('时间/s');ylabel('voltage/V');
    %channel 4刷新
    if handles.ChannelCount == 4
        axes(handles.axes4);
        plot(dataAI(:,4),'-black');
        set(handles.axes4,'XLim',[dataNum-90*beishu,dataNum+10]);
        xticks(handles.axes4,[dataNum-90*beishu dataNum+10]);
        xticklabels(handles.axes4,{...
            [num2str(timestep * (dataNum-90*beishu)),' ms'],...
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


function edit_sample1_Callback(hObject, eventdata, handles)
Fs=str2double(get(handles.edit_sample,'string'));
handles.Fs=Fs;
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_sample1_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton_process1.
function pushbutton_process1_Callback(hObject, eventdata, handles)
set(gcf, 'Name', '正在处理......');

dataAI = handles.dataAI;
Fs = handles.Fs;
fc = handles.fc;
choose_channel = handles.choose_channel;
process = handles.process;
x = dataAI(:,choose_channel);
N = length(x);

round_1 = round(N/2);

switch process
    case 1
        [n,y]=filter_highpass(Fs,x,fc);
        axes(handles.axes5);plot(n/Fs,y);
        xlabel('时间/s');ylabel('voltage/V');grid on;
        [f,yy]=signal_fft(y,Fs);
        axes(handles.axes6);
        % %单边显示格式
        plot(f(1:round_1),yy(1:round_1)*2/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
    case 2
        [n,y]=filter_lowpass(Fs,x,fc);
        axes(handles.axes5);plot(n/Fs,y);
        xlabel('时间/s');ylabel('voltage/V');grid on;
        [f,yy]=signal_fft(y,Fs);
        axes(handles.axes6);
        % %单边显示格式
        plot(f(1:round_1),yy(1:round_1)*2/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
    case 3
        [f,y]=signal_fft(x,Fs);
        axes(handles.axes5);
        %双边显示格式
        plot(f,y/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
        %单边显示格式
        axes(handles.axes6);
        plot(f(1:round_1),y(1:round_1)*2/N);
        xlabel('频率/Hz');ylabel('振幅');grid on;
end

set(gcf, 'Name', 'Oscilloscope_Project1.fig');


% --- Executes on button press in pushbutton_import1.
function pushbutton_import1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_import1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename,pathname] = uigetfile(...
    {'*.*', 'All Files (*.*)';...
    '*.m;*.mlx;*.fig;*.mat;*.slx;*.mdl','MATLAB Files (*.m,*.mlx,*.fig,*.mat,*.slx,*.mdl)';...
    '*.csv','CSV(逗号分隔文件) (*.csv)'; ...
    '*.txt','文本文档 (*.txt)'; ...
    '*.xls','Excel电子文档 (*.xls)';});


file = [pathname,filename];
file_info = [pathname,filename,'_info.txt'];

if ischar(filename)
    isexist = exist(file_info,'file');
    
    if isexist == 0
        fprintf('Import Erro! Can not find data informative document');
        return
    end
    
    set(gcf, 'Name', '正在导入......');

    dataAI = Signalread(file);
    dataNum = length(dataAI(:,1));
    
    % get data information, namely sampling rate, and have it display in edit box
    fid = fopen(file_info,'r');
    
    
    for i = 1:3
        data_info = fgetl(fid); % get the third line.
    end
    
    Fs_info = data_info;
    Fs = Fs_info(strfind(Fs_info,':')+1:end);
    Fs = str2double(Fs);
    set(handles.edit_sample1,'Value',Fs);
    fclose(fid);
    
    % upload import data file to workspace
    handles.dataNum = dataNum;
    handles.dataAI = dataAI;
    handles.data_info = data_info;
    handles.Fs = Fs;
    guidata(hObject,handles);
    
    % Initilizatio for plotting
    AxesHandles = handles.AxesHandles;
    timestep = 1000/Fs; % unit: ms
    totallength = timestep * dataNum;
    
    % Fs=handles.Fs;
    % display data read on axes areas.
    
    for i = 1:4
        cla(AxesHandles(i)); % clear exsisted data in graphs.
        plot(AxesHandles(i),dataAI(:,i),'-black');
        
        set(AxesHandles(i),'XLim',[0 dataNum]);
        xlabel(AxesHandles(i),'time');
        ylabel(AxesHandles(i),'voltage/V');
        set(AxesHandles(i),'XTick',[0 dataNum*0.25 dataNum*0.75 dataNum]);
        set(AxesHandles(i),'XTickLabel',{'0',...
            [num2str(totallength*0.25),' ms'],...
            [num2str(totallength*0.75),' ms'],...
            [num2str(totallength),' ms']});
    end
else
    return; %when file open dialog is closed.
end


% hide sliders when initilizing.
set(handles.slider1,'visible','off');
set(handles.slider1,'visible','off');
set(handles.slider3,'visible','off');
set(handles.slider2,'visible','off');

%设置横坐标和滑动条的初始化
%channel 1
N1=length(dataAI(:,1));
if N1 > 100   
    set(handles.axes1,'XLim',[0,N1]);
    set(handles.slider1,'min',100)
    set(handles.slider1,'max',N1);
    set(handles.slider1,'value',N1);
    set(handles.slider1,'visible','on');
end

%channel 2
N2 = length(dataAI(:,2));
if N2 > 100   
    set(handles.axes2,'XLim',[0,N2]);
    set(handles.slider1,'min',100)
    set(handles.slider1,'max',N2);
    set(handles.slider1,'value',N2);
    set(handles.slider1,'visible','on');
end

%channel 3
N3 = length(dataAI(:,3));
if N3 > 100
    
    set(handles.axes3,'XLim',[0,N3]);
    set(handles.slider3,'min',100)
    set(handles.slider3,'max',N3);
    set(handles.slider3,'value',N3);
    set(handles.slider3,'visible','on');
end

%channel 4
N4 = length(dataAI(:,4));
if N4 > 100
    
    set(handles.axes1,'XLim',[0,N4]);
    set(handles.slider2,'min',100)
    set(handles.slider2,'max',N4);
    set(handles.slider2,'value',N4);
    set(handles.slider2,'visible','on');
end

%channel 1的收缩滑动条初始化-只有放大没有缩小
set(handles.slider3,'min',0)
set(handles.slider3,'max',10);
set(handles.slider3,'value',5);

set(gcf, 'Name', 'Oscilloscope_Project1.fig');

% --- Executes on button press in pushbutton_save1.
function pushbutton_save1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_save1 (see GCBO)
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
    % if explorer is closed without confirming save, filename will be 0.
    set(gcf, 'Name', '正在保存......');
    
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
            fprintf('\nSave Failled! Unexpected erro occurred!');
    end
    
    % print informative document.
    fid = fopen([pathname,filename,'_info.txt'],'w');
    
    fprintf(fid,'time:\t%s\n',datestr(now,31));
    fprintf(fid,'ChannelCount:\t%d\n',handles.ChannelCount);
    fprintf(fid,'SamplingRate:\t%d\n',handles.Fs);   
    
    fclose(fid);
    fprintf('\nSave Succeeded!');
    
    set(gcf, 'Name', 'Oscilloscope_Project1.fig');
end

% --- Executes on slider movement.
function slider5_Callback(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
timeaxesflag = handles.timeaxesflag;
gainvalue = get(handles.slider5,'value');

gainvalue = int32(round(gainvalue));

if gainvalue<=1
    beishu=10;
    set(handles.slider5,'value',0);
else
    if gainvalue<=3
        beishu = 5;
        set(handles.slider5,'value',2);
    else
        if gainvalue<5
            beishu = 2;
            set(handles.slider5,'value',4);
        else
            if gainvalue == 5
                beishu = 1;
                 set(handles.slider5,'value',5);
            else
                if gainvalue<=7
                    beishu = 0.5;
                    set(handles.slider5,'value',6);
                else
                    if gainvalue<=9
                        beishu = 0.2;
                        set(handles.slider5,'value',8);
                    else
                        if gainvalue<=10
                            beishu = 0.1;
                            set(handles.slider5,'value',10);
                        end
                    end
                end
            end
        end
    end
end

handles.beishu=beishu;
guidata(hObject,handles);

if timeaxesflag == 1 % 停止采集后
    
    v1=handles.val(1);
    N=handles.dataNum;
    timestep = 1000/handles.Fs;
    
    if N<=90*beishu
        xmin=0;
        xmax=100*beishu;
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
    xticks(handles.axes1,[xmin xmax]);
    xticklabels(handles.axes1,{...
        [num2str(timestep * xmin),' ms'],...
        [num2str(timestep * xmax),' ms']});
end
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider4_Callback(hObject, eventdata, handles)
% hObject    handle to slider4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
v4 = get(handles.slider4,'value');
handles.val(4)=v4;
guidata(hObject,handles);

timestep = 1000/handles.Fs;

if v4>=90
    set(handles.axes4,'XLim',[v4-90,v4+10]);
    xticks(handles.axes4,[v4-90,v4+10]);
    xticklabels(handles.axes1,{...
        [num2str(round(timestep * (v4-90))),' ms'],...
        [num2str(round(timestep * (v4+10))),' ms']});
    
else
    set(handles.axes4,'XLim',[0,100]);
end

% --- Executes during object creation, after setting all properties.
function slider4_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in checkbox_Ch0.
function checkbox_Ch0_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch0


% --- Executes on button press in checkbox_Ch1.
function checkbox_Ch1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch1


% --- Executes on button press in checkbox_Ch2.
function checkbox_Ch2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch2


% --- Executes on button press in checkbox_Ch3.
function checkbox_Ch3_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_Ch3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_Ch3


% --- Executes on button press in radiobutton_channel0.
function radiobutton_channel0_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_channel0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
choose_channel = 1;
handles.choose_channel = choose_channel;

if choose_channel && handles.process 
    set(handles.pushbutton_process1,'Enable','on');
end
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_channel0



function edit_fc1_Callback(hObject, eventdata, handles)
% hObject    handle to edit_fc1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fc = str2double(get(handles.edit_fc1,'string'));
handles.fc = fc;
guidata(hObject,handles);
% Hints: get(hObject,'String') returns contents of edit_fc1 as text
%        str2double(get(hObject,'String')) returns contents of edit_fc1 as a double


% --- Executes during object creation, after setting all properties.
function edit_fc1_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in radiobutton_fft1.
function radiobutton_fft1_Callback(hObject, eventdata, handles)
process=3;
handles.process=process;

if handles.choose_channel && process 
    set(handles.pushbutton_process1,'Enable','on');
end

set(handles.radiobutton_highpass1,'Enable','off');
set(handles.radiobutton_lowpass1,'Enable','off');

guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_fft1


% --- Executes on button press in radiobutton_filter1.
function radiobutton_filter1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_filter1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if get(hObject,'Value')
    set(handles.radiobutton_highpass1,'Enable','on');
    set(handles.radiobutton_lowpass1,'Enable','on');
else
    set(handles.radiobutton_highpass1,'Enable','off');
    set(handles.radiobutton_lowpass1,'Enable','off');
end
% Hint: get(hObject,'Value') returns toggle state of radiobutton_filter1


% --- Executes on button press in radiobutton_highpass1.
function radiobutton_highpass1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_highpass1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
process=1;
handles.process=process;

if handles.choose_channel && process 
    set(handles.pushbutton_process1,'Enable','on');
end

guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_highpass1


% --- Executes on button press in radiobutton_lowpass1.
function radiobutton_lowpass1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_lowpass1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
process=2;
handles.process=process;

if handles.choose_channel && process 
    set(handles.pushbutton_process1,'Enable','on');
end
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_lowpass1


% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(1) = AxesHandles;
guidata(hObject,handles);
% Hint: place code in OpeningFcn to populate axes1


% --- Executes during object creation, after setting all properties.
function axes2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(2) = AxesHandles;
guidata(hObject,handles);
% Hint: place code in OpeningFcn to populate axes2


% --- Executes during object creation, after setting all properties.
function axes3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(3) = AxesHandles;
guidata(hObject,handles);
% Hint: place code in OpeningFcn to populate axes3


% --- Executes during object creation, after setting all properties.
function axes4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(4) = AxesHandles;
guidata(hObject,handles);
% Hint: place code in OpeningFcn to populate axes4
