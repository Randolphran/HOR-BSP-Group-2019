function varargout = DO_DI_Project3(varargin)
% DO_DI_PROJECT3 MATLAB code for DO_DI_Project3.fig
%      DO_DI_PROJECT3, by itself, creates a new DO_DI_PROJECT3 or raises the existing
%      singleton*.
%
%      H = DO_DI_PROJECT3 returns the handle to a new DO_DI_PROJECT3 or the handle to
%      the existing singleton*.
%
%      DO_DI_PROJECT3('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DO_DI_PROJECT3.M with the given input arguments.
%
%      DO_DI_PROJECT3('Property','Value',...) creates a new DO_DI_PROJECT3 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before DO_DI_Project3_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to DO_DI_Project3_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help DO_DI_Project3

% Last Modified by GUIDE v2.5 05-Dec-2019 14:45:26

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @DO_DI_Project3_OpeningFcn, ...
                   'gui_OutputFcn',  @DO_DI_Project3_OutputFcn, ...
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


% --- Executes just before DO_DI_Project3 is made visible.
function DO_DI_Project3_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to DO_DI_Project3 (see VARARGIN)

% Choose default command line output for DO_DI_Project3
handles.output = hObject;

set(handles.slider_frequency,'min',1);
set(handles.slider_frequency,'max',50);
set(handles.slider_frequency,'value',25);

fvalue=25;
handles.fvalue=fvalue;

period=0.04;
handles.period=period;

time=3;
handles.time=time;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes DO_DI_Project3 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = DO_DI_Project3_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in radiobutton1.
function radiobutton1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
choose=get(handles.radiobutton1,'value');
if choose==0
    set(handles.togglebutton2,'backgroundcolor','red');
else set(handles.togglebutton2,'backgroundcolor','green');
end
 
%set(handles.togglebutton2,'backgroundcolor','green');

% Hint: get(hObject,'Value') returns toggle state of radiobutton1
% --- Executes on button press in togglebutton2.
function togglebutton2_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton2


% --- Executes on slider movement.
function slider_frequency_Callback(hObject, eventdata, handles)
% hObject    handle to slider_frequency (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fvalue=get(handles.slider_frequency,'value');
set(handles.edit_fvalue,'string',round(fvalue));
period=roundn(1/fvalue,-2);
handles.fvalue=fvalue;
handles.period=period;
guidata(hObject,handles);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider_frequency_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_frequency (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in pushbutton_start.
function pushbutton_start_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_start (see GCBO)
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



function edit_time_Callback(hObject, eventdata, handles)
% hObject    handle to edit_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
time=str2double(get(handles.edit_time,'value'));
handles.time=time;
guidata(hObject,handles);
% Hints: get(hObject,'String') returns contents of edit_time as text
%        str2double(get(hObject,'String')) returns contents of edit_time as a double


% --- Executes during object creation, after setting all properties.
function edit_time_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_fvalue_Callback(hObject, eventdata, handles)
% hObject    handle to edit_fvalue (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fvalue=str2double(get(handles.edit_fvalue,'string'));
set(handles.slider_frequency,'value',fvalue);
period=roundn(1/fvalue,-2);
handles.fvalue=fvalue;
handles.period=period;
guidata(hObject,handles);
% Hints: get(hObject,'String') returns contents of edit_fvalue as text
%        str2double(get(hObject,'String')) returns contents of edit_fvalue as a double


% --- Executes during object creation, after setting all properties.
function edit_fvalue_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_fvalue (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
