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

% Last Modified by GUIDE v2.5 05-Dec-2019 16:34:59

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
set(handles.text3,'visible','off');
set(handles.edit_time,'visible','off');
set(handles.text13,'visible','off');

set(handles.radiobutton_continue,'value',1);

fvalue=25;
handles.fvalue=fvalue;

period=0.04;
handles.period=period;

time=1;
handles.time=time;d

contiflag=1;
handles.contiflag=contiflag;


% Start DI monitor
Project3_StaticDI(hObject);
xlabel(handles.axes1,'time /sec');
ylabel(handles.axes1,'voltage /V');


% %画圆
% r=2; theta=0:pi/100:2*pi;
% x=r*cos(theta); y=r*sin(theta);
% rho=r*sin(theta);
% plot(handles.axes2,x,y,'-');
% hold on; axis equal;
% fill(handles.axes2,x,y,'red');

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


% % --- Executes on button press in radiobutton1.
% function radiobutton1_Callback(hObject, eventdata, handles)
% % hObject    handle to radiobutton1 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% choose=get(handles.radiobutton1,'value');
% if choose==0
%     set(handles.togglebutton2,'backgroundcolor','red');
% else set(handles.togglebutton2,'backgroundcolor','green');
% end
%  
% %set(handles.togglebutton2,'backgroundcolor','green');

% % Hint: get(hObject,'Value') returns toggle state of radiobutton1
% % --- Executes on button press in togglebutton2.
% function togglebutton2_Callback(hObject, eventdata, handles)
% % hObject    handle to togglebutton2 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% 
% % Hint: get(hObject,'Value') returns toggle state of togglebutton2


% --- Executes on slider movement.
function slider_frequency_Callback(hObject, eventdata, handles)
% hObject    handle to slider_frequency (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fvalue=round(get(handles.slider_frequency,'value'));
set(handles.edit_fvalue,'string',fvalue);
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
i=0;
handles.i=i;
guidata(hObject,handles);
StaticDO(handles.figure1,handles);

% --- Executes on button press in pushbutton_pause.
function pushbutton_pause_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_pause (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global t1;
stop(t1);

% --- Executes on button press in pushbutton_stop.
function pushbutton_stop_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global t1;
stop(t1);
delete(t1);
clear global t1;

uiresume(handles.figure1);

function edit_time_Callback(hObject, eventdata, handles)
% hObject    handle to edit_time (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
time=str2double(get(handles.edit_time,'string'));
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
fvalue1=str2double(get(handles.edit_fvalue,'string'));
if (fvalue1-round(fvalue1) ~= 0)
    errordlg('请输入整数');
else if fvalue1>50
        errordlg('请输入不超过50的整数');
    else if fvalue1<1
            errordlg('请输入大于1的整数');
        else fvalue=fvalue1;
            set(handles.slider_frequency,'value',fvalue);
            period=roundn(1/fvalue,-2);
            handles.fvalue=fvalue;
            handles.period=period;
        end
    end
end
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


% --- Executes on button press in radiobutton_fixtime.
function radiobutton_fixtime_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_fixtime (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
contiflag=0;
set(handles.text3,'visible','on');
set(handles.edit_time,'visible','on');
set(handles.text13,'visible','on');
handles.contiflag=contiflag;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_fixtime


% --- Executes on button press in radiobutton_continue.
function radiobutton_continue_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_continue (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
contiflag=1;
set(handles.text3,'visible','off');
set(handles.edit_time,'visible','off');
set(handles.text13,'visible','off');
handles.contiflag=contiflag;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of radiobutton_continue

% % --- Executes during object creation, after setting all properties.
% function togglebutton2_CreateFcn(hObject, eventdata, handles)
% % hObject    handle to togglebutton2 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    empty - handles not created until after all CreateFcns called


% --- Executes during object deletion, before destroying properties.
function figure1_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global t2
uiresume(handles.figure1);
stop(t2);
delete(t2);

clear global t2;

