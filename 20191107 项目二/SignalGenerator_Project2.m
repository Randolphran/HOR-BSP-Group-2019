function varargout = SignalGenerator_Project2(varargin)
% SIGNALGENERATOR_PROJECT2 MATLAB code for SignalGenerator_Project2.fig
%      SIGNALGENERATOR_PROJECT2, by itself, creates a new SIGNALGENERATOR_PROJECT2 or raises the existing
%      singleton*.
%
%      H = SIGNALGENERATOR_PROJECT2 returns the handle to a new SIGNALGENERATOR_PROJECT2 or the handle to
%      the existing singleton*.
%
%      SIGNALGENERATOR_PROJECT2('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SIGNALGENERATOR_PROJECT2.M with the given input arguments.
%
%      SIGNALGENERATOR_PROJECT2('Property','Value',...) creates a new SIGNALGENERATOR_PROJECT2 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SignalGenerator_Project2_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SignalGenerator_Project2_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SignalGenerator_Project2

% Last Modified by GUIDE v2.5 21-Nov-2019 17:23:39

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SignalGenerator_Project2_OpeningFcn, ...
                   'gui_OutputFcn',  @SignalGenerator_Project2_OutputFcn, ...
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


% --- Executes just before SignalGenerator_Project2 is made visible.
function SignalGenerator_Project2_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SignalGenerator_Project2 (see VARARGIN)

% Choose default command line output for SignalGenerator_Project2
handles.output = hObject;

amplitude=5;
handles.amplitude=amplitude;

ppp=512;
handles.ppp=ppp;

offset=2.5;
handles.offset=offset;

dutycycle=0.5;
handles.dutycycle=dutycycle;

frequency=10;
handles.frequency=frequency;

wavechosen=1;
handles.wavechosen=wavechosen;

dataAO=zeros(512,1);
handles.dataAO=dataAO;
guidata(hObject,handles);

contiflag=1;
handles.contiflag=contiflag;

periodNum=2;
handles.periodNum=periodNum;

i=0;
handles.i=i;

periodcount=0;
handles.periodcount=periodcount;

set(handles.listbox1,'value',1);

set(handles.text_dutycycle,'visible','off');
set(handles.edit_dutycycle,'visible','off');
set(handles.text9,'visible','off');
set(handles.radiobutton_continuous,'value',1);
set(handles.radiobutton_specified,'value',0);

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes SignalGenerator_Project2 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = SignalGenerator_Project2_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in listbox1.
function listbox1_Callback(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
wavechosen=get(handles.listbox1,'value');
handles.wavechosen=wavechosen;

set(handles.edit_ppp,'enable','on');
set(handles.edit_amplitude,'enable','on');
set(handles.edit_frequency,'enable','on');
set(handles.edit_offset,'enable','on');
set(handles.edit_dutycycle,'enable','on');
switch wavechosen
    case 1   %Sine
        set(handles.text_dutycycle,'visible','off');
        set(handles.edit_dutycycle,'visible','off');
        set(handles.text_amplitude,'visible','on');
        set(handles.edit_amplitude,'visible','on');
        set(handles.text9,'visible','off');
    case 2    %Sawtooth
        set(handles.text_dutycycle,'visible','off');
        set(handles.edit_dutycycle,'visible','off');
        set(handles.text_amplitude,'visible','on');
        set(handles.edit_amplitude,'visible','on');
        set(handles.text9,'visible','off');
    case 3     %Square
        set(handles.text_dutycycle,'visible','on');
        set(handles.edit_dutycycle,'visible','on');
        set(handles.text_amplitude,'visible','on');
        set(handles.edit_amplitude,'visible','on');
        set(handles.text9,'visible','on');
    case 4     %Level
        set(handles.text_dutycycle,'visible','off');
        set(handles.edit_dutycycle,'visible','off');
        set(handles.text_amplitude,'visible','off');
        set(handles.edit_amplitude,'visible','off');
        set(handles.text9,'visible','off');
end  
amplitude=handles.amplitude;
offset=handles.offset;
dutycycle=handles.dutycycle;
ppp=handles.ppp;
style=handles.wavechosen;
frequency=handles.frequency;
dataAO=GenerateWaveform(amplitude, offset, dutycycle, ppp, style);
totallength=2*ppp;
data_to_plot = zeros(2*ppp,1);
data_to_plot(1:ppp,1) = dataAO;
data_to_plot(ppp+1:2*ppp,1) = dataAO;  
handles.dataAO=dataAO;
axes(handles.axes1);
plot(data_to_plot,'black');
set(handles.axes1,'XLim',[0,totallength]);
xticks(handles.axes1,[0 totallength/8 totallength/4 totallength*3/8 totallength/2 totallength*5/8 totallength*3/4 totallength*7/8 totallength]);
xticklabels(handles.axes1,{'0',...
    [num2str(1/(frequency*4)),' s'],...
    [num2str(1/(frequency*2)),' s'],...
    [num2str(3/(frequency*4)),' s'],...
    [num2str(1/(frequency)),' s'],...
    [num2str(5/(frequency*4)),' s'],...
    [num2str(2/(frequency*3)),' s'],...
    [num2str(7/(frequency*4)),' s'],...
    [num2str(2/frequency),' s']});
guidata(hObject,handles);


% Hints: contents = cellstr(get(hObject,'String')) returns listbox1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox1


% --- Executes during object creation, after setting all properties.
function listbox1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function edit_frequency_Callback(hObject, eventdata, handles)
% hObject    handle to edit_frequency (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
frequency=str2double(get(handles.edit_frequency,'String'));
handles.frequency=frequency;
guidata(hObject,handles);

%在画面上对信号进行两个周期的预览
amplitude=handles.amplitude;
offset=handles.offset;
dutycycle=handles.dutycycle;
ppp=handles.ppp;
style=handles.wavechosen;
dataAO=GenerateWaveform(amplitude, offset, dutycycle, ppp, style);
totallength=2*ppp;
data_to_plot = zeros(2*ppp,1);
data_to_plot(1:ppp,1) = dataAO;
data_to_plot(ppp+1:2*ppp,1) = dataAO;  
handles.dataAO=dataAO;
axes(handles.axes1);
plot(data_to_plot,'black');
set(handles.axes1,'XLim',[0,totallength]);
xticks(handles.axes1,[0 totallength/8 totallength/4 totallength*3/8 totallength/2 totallength*5/8 totallength*3/4 totallength*7/8 totallength]);
xticklabels(handles.axes1,{'0',...
    [num2str(1/(frequency*4)),' s'],...
    [num2str(1/(frequency*2)),' s'],...
    [num2str(3/(frequency*4)),' s'],...
    [num2str(1/(frequency)),' s'],...
    [num2str(5/(frequency*4)),' s'],...
    [num2str(2/(frequency*3)),' s'],...
    [num2str(7/(frequency*4)),' s'],...
    [num2str(2/frequency),' s']});
guidata(hObject,handles);

% Hints: get(hObject,'String') returns contents of edit_frequency as text
%        str2double(get(hObject,'String')) returns contents of edit_frequency as a double


% --- Executes during object creation, after setting all properties.
function edit_frequency_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_frequency (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_amplitude_Callback(hObject, eventdata, handles)
% hObject    handle to edit_amplitude (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
amplitude=str2double(get(handles.edit_amplitude,'String'));
handles.amplitude=amplitude;
guidata(hObject,handles);

%在画面上对信号进行两个周期的预览
offset=handles.offset;
dutycycle=handles.dutycycle;
ppp=handles.ppp;
style=handles.wavechosen;
frequency=handles.frequency;
dataAO=GenerateWaveform(amplitude, offset, dutycycle, ppp, style);
totallength=2*ppp;
data_to_plot = zeros(2*ppp,1);
data_to_plot(1:ppp,1) = dataAO;
data_to_plot(ppp+1:2*ppp,1) = dataAO;  
handles.dataAO=dataAO;
axes(handles.axes1);
plot(data_to_plot,'black');
set(handles.axes1,'XLim',[0,totallength]);
xticks(handles.axes1,[0 totallength/8 totallength/4 totallength*3/8 totallength/2 totallength*5/8 totallength*3/4 totallength*7/8 totallength]);
xticklabels(handles.axes1,{'0',...
    [num2str(1/(frequency*4)),' s'],...
    [num2str(1/(frequency*2)),' s'],...
    [num2str(3/(frequency*4)),' s'],...
    [num2str(1/(frequency)),' s'],...
    [num2str(5/(frequency*4)),' s'],...
    [num2str(2/(frequency*3)),' s'],...
    [num2str(7/(frequency*4)),' s'],...
    [num2str(2/frequency),' s']});
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_amplitude_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_amplitude (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');    
end


function edit_ppp_Callback(hObject, eventdata, handles)
% hObject    handle to edit_ppp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
ppp=str2double(get(handles.edit_ppp,'String'));
handles.ppp=ppp;
guidata(hObject,handles);

amplitude=handles.amplitude;
offset=handles.offset;
dutycycle=handles.dutycycle;
style=handles.wavechosen;
frequency=handles.frequency;
dataAO=GenerateWaveform(amplitude, offset, dutycycle, ppp, style);
totallength=2*ppp;
data_to_plot = zeros(2*ppp,1);
data_to_plot(1:ppp,1) = dataAO;
data_to_plot(ppp+1:2*ppp,1) = dataAO;  
handles.dataAO=dataAO;
axes(handles.axes1);
plot(data_to_plot,'black');
set(handles.axes1,'XLim',[0,totallength]);
xticks(handles.axes1,[0 totallength/8 totallength/4 totallength*3/8 totallength/2 totallength*5/8 totallength*3/4 totallength*7/8 totallength]);
xticklabels(handles.axes1,{'0',...
    [num2str(1/(frequency*4)),' s'],...
    [num2str(1/(frequency*2)),' s'],...
    [num2str(3/(frequency*4)),' s'],...
    [num2str(1/(frequency)),' s'],...
    [num2str(5/(frequency*4)),' s'],...
    [num2str(2/(frequency*3)),' s'],...
    [num2str(7/(frequency*4)),' s'],...
    [num2str(2/frequency),' s']});
guidata(hObject,handles);

% Hints: get(hObject,'String') returns contents of edit_ppp as text
%        str2double(get(hObject,'String')) returns contents of edit_ppp as a double


% --- Executes during object creation, after setting all properties.
function edit_ppp_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_ppp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton_import.
function pushbutton_import_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_import (see GCBO)
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
        fprintf('Import Erro! Cannot find data informative document');
        return
    end
    
    set(gcf, 'Name', '正在导入......');
    
    % get data information, namely Fs.
    fid = fopen(file_info,'r');
   
    for i = 1:3
        data_info = fgetl(fid); % get the third line.
    end
    
    Fs_info = data_info;
    Fs = Fs_info(strfind(Fs_info,':')+1:end);
    Fs_in = str2double(Fs);
    
    fclose(fid);
    
    % check for import compatibility.
    ppp = handles.ppp;
    dataAO_temp = Signalread(file);
    dataAO = dataAO_temp(:,1);
    dataNum = length(dataAO(:,1));
    
    if dataNum > ppp
        fprintf('Warning! Import data size exceeds the numner of Point Per Period. Margin data will be discarded');
        dataNum = ppp;
        temp = dataAO;
        clear dataAO
        dataAO = temp(1:dataNum,4);        
    else
        ppp = dataNum;
        set(handles.edit_ppp,'string',num2str(ppp));
    end
    
     set(handles.edit_ppp,'enable','off');
     set(handles.edit_amplitude,'enable','off');
     set(handles.edit_dutycycle,'enable','off');
% % % % % % % % % data import complete % % % % % % % % % % % % % % % % % %
    % start ploting. The first channel data in dataImport is seen as one
    % period integratedly. Two periods will be displayed in axes1 zone.
    
    period = round(1000/Fs_in); % unit: ms
    totallength = period * dataNum * 2; % display two periods
    
    AxesHandle = handles.axes1;
    AxesHandle.XLim = [0 totallength];
    AxesHandle.YLim = [0 inf];
    AxesHandle.XTick = [0 round(dataNum/2) dataNum totallength];
    AxesHandle.XTickLabel = {'0',...
        [num2str(round(dataNum/2)),' ms'],...
        [num2str(dataNum),' ms'],...
        [num2str(totallength),' ms']};
    
    data_to_plot = zeros(2*dataNum,1);
    data_to_plot(1:dataNum,1) = dataAO(:,1);
    data_to_plot(dataNum+1:2*dataNum,1) = dataAO(:,1);
    
    plot(AxesHandle,data_to_plot,'black');
% % % % % % % % % data plot complete % % % % % % % % % % % % % % % % % %
    % set enable status TODO


    % upload import data file to gui workspace
    handles.dataNum = dataNum;
    handles.dataAO = dataAO;
    handles.data_info = data_info;
    handles.Fs_in = Fs_in;
    handles.ppp = ppp;
    
    set(gcf, 'Name', 'SignalGenerator_Project2');
    
    guidata(hObject,handles);
else
    return; %when file open dialog is closed.
end

% --- Executes on button press in pushbutton_draw.
function pushbutton_draw_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_draw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[figure2,handles] = UserDefinedFcn(handles);

guidata(hObject,handles)

if any(dataAO) %any: if any element in dataAO is nonzero, return 1.
    
end

% --- Executes on button press in pushbutton_run.
function pushbutton_run_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_run (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
StaticAO(handles.figure1,handles);

% --- Executes on button press in pushbutton_pause.
function pushbutton_pause_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_pause (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global t;
stop(t);

% --- Executes on button press in pushbutton_stop.
function pushbutton_stop_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global t;
stop(t);
delete(t);
clear global t;
uiresume(handles.figure1);
i=0;
handles.i=i;
guidata(hObject,handles);
end

function edit_offset_Callback(hObject, eventdata, handles)
% hObject    handle to edit_offset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
offset=str2double(get(handles.edit_offset,'String'));
handles.offset=offset;
guidata(hObject,handles);

amplitude=handles.amplitude;
dutycycle=handles.dutycycle;
ppp=handles.ppp;
style=handles.wavechosen;
frequency=handles.frequency;
dataAO=GenerateWaveform(amplitude, offset, dutycycle, ppp, style);
totallength=2*ppp;
data_to_plot = zeros(2*ppp,1);
data_to_plot(1:ppp,1) = dataAO;
data_to_plot(ppp+1:2*ppp,1) = dataAO;  
handles.dataAO=dataAO;
axes(handles.axes1);
plot(data_to_plot,'black');
set(handles.axes1,'XLim',[0,totallength]);
xticks(handles.axes1,[0 totallength/8 totallength/4 totallength*3/8 totallength/2 totallength*5/8 totallength*3/4 totallength*7/8 totallength]);
xticklabels(handles.axes1,{'0',...
    [num2str(1/(frequency*4)),' s'],...
    [num2str(1/(frequency*2)),' s'],...
    [num2str(3/(frequency*4)),' s'],...
    [num2str(1/(frequency)),' s'],...
    [num2str(5/(frequency*4)),' s'],...
    [num2str(2/(frequency*3)),' s'],...
    [num2str(7/(frequency*4)),' s'],...
    [num2str(2/frequency),' s']});
guidata(hObject,handles);

% Hints: get(hObject,'String') returns contents of edit_offset as text
%        str2double(get(hObject,'String')) returns contents of edit_offset as a double

% --- Executes during object creation, after setting all properties.
function edit_offset_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_offset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function edit_PeriodNum_Callback(hObject, eventdata, handles)
% hObject    handle to edit_PeriodNum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
periodNum=str2double(get(handles.edit_PeriodNum,'String'));
handles.periodNum=periodNum;
guidata(hObject,handles);
% Hints: get(hObject,'String') returns contents of edit_PeriodNum as text
%        str2double(get(hObject,'String')) returns contents of edit_PeriodNum as a double

% --- Executes during object creation, after setting all properties.
function edit_PeriodNum_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_PeriodNum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function edit_dutycycle_Callback(hObject, eventdata, handles)
% hObject    handle to edit_dutycycle (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
dutycycle=str2double(get(handles.edit_dutycycle,'String'));
handles.dutycycle=dutycycle;
guidata(hObject,handles);

amplitude=handles.amplitude;
offset=handles.offset;
ppp=handles.ppp;
style=handles.wavechosen;
frequency=handles.frequency;
dataAO=GenerateWaveform(amplitude, offset, dutycycle, ppp, style);
totallength=2*ppp;
data_to_plot = zeros(2*ppp,1);
data_to_plot(1:ppp,1) = dataAO;
data_to_plot(ppp+1:2*ppp,1) = dataAO;  
handles.dataAO=dataAO;
axes(handles.axes1);
plot(data_to_plot,'black');
set(handles.axes1,'XLim',[0,totallength]);
xticks(handles.axes1,[0 totallength/8 totallength/4 totallength*3/8 totallength/2 totallength*5/8 totallength*3/4 totallength*7/8 totallength]);
xticklabels(handles.axes1,{'0',...
    [num2str(1/(frequency*4)),' s'],...
    [num2str(1/(frequency*2)),' s'],...
    [num2str(3/(frequency*4)),' s'],...
    [num2str(1/(frequency)),' s'],...
    [num2str(5/(frequency*4)),' s'],...
    [num2str(2/(frequency*3)),' s'],...
    [num2str(7/(frequency*4)),' s'],...
    [num2str(2/frequency),' s']});
guidata(hObject,handles);

% Hints: get(hObject,'String') returns contents of edit_dutycycle as text
%        str2double(get(hObject,'String')) returns contents of edit_dutycycle as a double

% --- Executes during object creation, after setting all properties.
function edit_dutycycle_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_dutycycle (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in radiobutton_specified.
function radiobutton_specified_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_specified (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
contiflag=0;
handles.contiflag=contiflag;
guidata(hObject,handles);

% Hint: get(hObject,'Value') returns toggle state of radiobutton_continuous

% --- Executes on button press in radiobutton_continuous.
function radiobutton_continuous_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_continuous (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
contiflag=1;
handles.contiflag=contiflag;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_continuous

% --- Executes during object creation, after setting all properties.
function text5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes during object creation, after setting all properties.
function figure1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
