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

% Last Modified by GUIDE v2.5 14-Nov-2019 14:03:15

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
wavechoose=get(handles.listbox1,'value');

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
amplitude = str2num(get(handles.edit_amplitude,'String'));
% Hints: get(hObject,'String') returns contents of edit_amplitude as text
%        str2double(get(hObject,'String')) returns contents of edit_amplitude as a double


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



function edit_PPP_Callback(hObject, eventdata, handles)
% hObject    handle to edit_PPP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
PPP=str2num(get(handles.edit_PPP,'String'));
% Hints: get(hObject,'String') returns contents of edit_PPP as text
%        str2double(get(hObject,'String')) returns contents of edit_PPP as a double


% --- Executes during object creation, after setting all properties.
function edit_PPP_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_PPP (see GCBO)
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

    dataAO = Signalread(file);
    dataNum = length(dataAO(:,1));
    
    % get data information, namely sampling rate, and have it display in edit box
    fid = fopen(file_info,'r');
    
    
    for i = 1:3
        data_info = fgetl(fid); % get the third line.
    end
    
    Fs_info = data_info;
    Fs = Fs_info(strfind(Fs_info,':')+1:end);
    Fs = str2double(Fs);
    
    fclose(fid);
% % % % % % % % % data import complete % % % % % % % % % % % % % % % % % %
    % start ploting. The first channel data in dataImport is seen as one
    % period integratedly. Two periods will be displayed in axes1 zone.
    
    period = round(1000/Fs); % unit: ms
    totallength = period * dataNum * 2; % display two periods
    
    AxesHandle = handles.axes1;
    AxesHandle.XLim = [0 totallength];
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
    handles.Fs = Fs;
    guidata(hObject,handles);
    set(gcf, 'Name', 'SignalGenerator_Project2');
else
    return; %when file open dialog is closed.
end


% --- Executes on button press in pushbutton_draw.
function pushbutton_draw_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_draw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton_run.
function pushbutton_run_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_run (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton_pause.
function pushbutton_pause_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_pause (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton_stop.
function pushbutton_stop_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit_offset_Callback(hObject, eventdata, handles)
% hObject    handle to edit_offset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
offset=str2num(get(handles.edit_offset,'String'));
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



function edit_PNum_Callback(hObject, eventdata, handles)
% hObject    handle to edit_PNum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
pNum=str2num(get(handles.edit_pNum,'String'));
% Hints: get(hObject,'String') returns contents of edit_PNum as text
%        str2double(get(hObject,'String')) returns contents of edit_PNum as a double


% --- Executes during object creation, after setting all properties.
function edit_PNum_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_PNum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes1
