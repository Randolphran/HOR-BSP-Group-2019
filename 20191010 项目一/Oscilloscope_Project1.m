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

% Last Modified by GUIDE v2.5 15-Oct-2019 01:05:17

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

% Update handles structure
guidata(hObject, handles);



global filt
filt=0;
global process
process=0;

% Edittor: Ran 2019/10/14
dataAI = zeros(1024,4); 
dataNum = 1;
% Pre-assigned memeroy, Attention this might be insufficient.
% Simultaneously change the value in "BEGIN" callback function when change happens here.
% LineHandles = zeros(4,1);
LineActivity = zeros(4,1);

handles.LineActivity = LineActivity;
% handles.LineHandles = LineHandles;
handles.dataAI = dataAI;
handles.dataNum = dataNum;

guidata(hObject,handles);

end

% UIWAIT makes Oscilloscope_Project1 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


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
global y_high
global y_low
y_high = str2double(get(handles.edit_y_high,'string'));  %为什么只能是str2double，而不能是str2num？
axes(handles.axes1);
%set(handles.axes1,'XLim',[0,10],'YLim',[y_low,y_high]);
set(handles.axes1,'YLim',[y_low,y_high]);

% Hints: get(hObject,'String') returns contents of edit_y_high as text
%        str2double(get(hObject,'String')) returns contents of edit_y_high as a double
end

% --- Executes during object creation, after setting all properties.
function edit_y_high_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end


function edit_y_low_Callback(hObject, eventdata, handles)

global y_high
global y_low
y_low = str2double(get(handles.edit_y_low,'string'));  
axes(handles.axes1);
%set(handles.axes1,'XLim',[0,10],'YLim',[y_low,y_high]);
set(handles.axes1,'YLim',[y_low,y_high]);
end

function edit_y_low_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
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

% Initilization.
AxesHandles = handles.AxesHandles;
for i = 1:4
    cla(AxesHandles(i)); % clear exsisted data in graphs.
    line = animatedline(AxesHandles(i)); % build/re-build animatedline.
    handles.LineHandles(i) = line;
end

guidata(hObject,handles);

InstantAI_Project1(hObject,handles);% Start sampling in all axes areas.
    
% test code:
% LineHandles = handles.LineHandles;
%       for i = 1:4
%             Realtimeplot_Project1(1:100,1:100,LineHandles(i));
%       end
% end

guidata(hObject,handles);
% submit new input signal to database.

end
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %



% --- Executes during object creation, after setting all properties.
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
axes(handles.axes1)
datacursormode on;
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

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
end

% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end

% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
end

% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end

function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end

% --- Executes on slider movement.
function slider4_Callback(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
end

% --- Executes during object creation, after setting all properties.
function slider4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end



function slider5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
end

% --- Executes on button press in pushbutton_stop.
function pushbutton_stop_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


uiresume(handles.figure1);
end


function edit_sample_Callback(hObject, eventdata, handles)
% hObject    handle to edit_sample (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% Hints: get(hObject,'String') returns contents of edit_sample as text
%        str2double(get(hObject,'String')) returns contents of edit_sample as a double
end

% --- Executes during object creation, after setting all properties.
function edit_sample_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_sample (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
set(hObject,'string','100');
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
end


function edit_fc_Callback(hObject, eventdata, handles)
% hObject    handle to edit_fc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_fc as text
%        str2double(get(hObject,'String')) returns contents of edit_fc as a double
global fc
fc = str2num(get(handles.edit_fc,'string'));
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
% hObject    handle to pushbutton_import (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[filename,pathname] = uigetfile;
% call windows explorer to open the file.
% if the explorer is closed without confirming import, filename will be 0.

file = [pathname,filename];

if ischar(filename)
    dataread = Signalread(file); 
end

handles.dataread = dataread;
guidata(hObject,handles);


% display data read on axes areas.
AxesHandles = handles.AxesHandles;
for i = 1:4
    cla(AxesHandles(i)); % clear exsisted data in graphs.
    plot(AxesHandles(i),dataread(:,i));
end


end

% --- Executes on button press in pushbutton_save.
function pushbutton_save_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_save (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

datasave = handles.dataAI;
% savedialog(datasave); % call saving dialog;
% uiwait(handles.figure1);

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
    
    fprintf('Save Succeeded!');
    
end

end

% --- Executes on button press in radiobutton_filter.
function radiobutton_filter_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_filter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global filt
filt=1;
% Hint: get(hObject,'Value') returns toggle state of radiobutton_filter
end

% --- Executes on button press in radiobutton_highpass.
function radiobutton_highpass_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_highpass (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global filt
global process
process=1;
if filt==0
    errordlg('未选择“滤波”操作方式');
end
% Hint: get(hObject,'Value') returns toggle state of radiobutton_highpass
end

% --- Executes on button press in radiobutton_lowpass.
function radiobutton_lowpass_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_lowpass (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global filt
global process
process=2;
if filt==0
    errordlg('未选择“滤波”操作方式');
end
% Hint: get(hObject,'Value') returns toggle state of radiobutton_lowpass
end

% --- Executes on button press in radiobutton_fft.
function radiobutton_fft_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_fft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global process
process=3;
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
% hObject    handle to axes4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
AxesHandles = gca;
handles.AxesHandles(4) = AxesHandles;


guidata(hObject,handles);
end
% Hint: place code in OpeningFcn to populate axes4


% --- Executes during object deletion, before destroying properties.
function pushbutton_stop_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
clear global 
end


% --- Executes on button press in checkbox4.
function checkbox4_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
LineActivity =  get(hObject,'Value'); 
handles.LineActivity(1) = LineActivity;
guidata(hObject,handles);
end
% Hint: get(hObject,'Value') returns toggle state of checkbox4


% --- Executes on button press in checkbox6.
function checkbox6_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
LineActivity =  get(hObject,'Value'); 
handles.LineActivity(2) = LineActivity;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of checkbox6
end

% --- Executes on button press in checkbox7.
function checkbox7_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
LineActivity =  get(hObject,'Value'); 
handles.LineActivity(3) = LineActivity;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of checkbox7
end

% --- Executes on button press in checkbox8.
function checkbox8_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
LineActivity =  get(hObject,'Value'); 
handles.LineActivity(4) = LineActivity;
guidata(hObject,handles);
% Hint: get(hObject,'Value') returns toggle state of checkbox8
end
