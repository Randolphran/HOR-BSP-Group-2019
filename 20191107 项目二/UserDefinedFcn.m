function varargout = UserDefinedFcn(varargin)
% USERDEFINEDFCN MATLAB code for UserDefinedFcn.fig
%      USERDEFINEDFCN, by itself, creates a new USERDEFINEDFCN or raises the existing
%      singleton*.
%
%      H = USERDEFINEDFCN returns the handle to a new USERDEFINEDFCN or the handle to
%      the existing singleton*.
%
%      USERDEFINEDFCN('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in USERDEFINEDFCN.M with the given input arguments.
%
%      USERDEFINEDFCN('Property','Value',...) creates a new USERDEFINEDFCN or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before UserDefinedFcn_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to UserDefinedFcn_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help UserDefinedFcn

% Last Modified by GUIDE v2.5 21-Nov-2019 16:20:07

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @UserDefinedFcn_OpeningFcn, ...
                   'gui_OutputFcn',  @UserDefinedFcn_OutputFcn, ...
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


% --- Executes just before UserDefinedFcn is made visible.
function UserDefinedFcn_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to UserDefinedFcn (see VARARGIN)

% Choose default command line output for UserDefinedFcn
handles.output = hObject;

handles.mouse_enable = 0;
handles.mouse_num = 0;
handles.mouse_p = zeros(1,2);

set(handles.edit1,'Enable','off');
set(handles.axes3,'Visible','off');


% Update handles structure
guidata(hObject, handles);

% UIWAIT makes UserDefinedFcn wait for user response (see UIRESUME)
% uiwait(handles.figure2);


% --- Outputs from this function are returned to the command line.
function varargout = UserDefinedFcn_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in radiobutton_input.
function radiobutton_input_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.radiobutton2,'value',0);
set(handles.edit1,'Enable','on');
set(handles.axes3,'visible','off');
% Hint: get(hObject,'Value') returns toggle state of radiobutton_input



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
syms x 

fcn_in = get(hObject,'String');

fcn_calc = @(x)eval(fcn_in);
fcn_latex = latex(str2sym(fcn_in));

% display latex input for user in axes area.
axeshandles = handles.axes2;
cla(axeshandles);
text('String','f(x) = ','Position',[0,0.8],'FontSize',26);
len_txt = length(fcn_in);
if len_txt < 25
    
    text(axeshandles,'Interpreter','latex','String',['$',fcn_latex,'$'],...
        'Position',[0.2 0.7],'FontSize',26);
else
    if len_txt < 55
        text(axeshandles,'Interpreter','latex','String',['$',latex(str2sym(fcn_in(1:24))),'$'],...
            'Position',[0.2 0.7],'FontSize',26);
        text(axeshandles,'Interpreter','latex','String',['$',latex(str2sym(fcn_in(24:end))),'$'],...
            'Position',[0 0.4],'FontSize',26);
    else
        text(axeshandles,'Interpreter','latex','String',['$',latex(str2sym(fcn_in(1:24))),'$'],...
            'Position',[0.2 0.7],'FontSize',26);
        text(axeshandles,'Interpreter','latex','String',['$',latex(str2sym(fcn_in(24:54))),'$'],...
            'Position',[0 0.4],'FontSize',26);
        text(axeshandles,'Interpreter','latex','String',['$',latex(str2sym(fcn_in(55:end))),'$'],...
            'Position',[0 0.1],'FontSize',26);
    end
end

handles.fcn_calc = fcn_calc;
handles.fcn_latex = fcn_latex;
guidata(hObject,handles);



% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function axes2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
axis off;
text('String','f(x) = ','Position',[0,0.8],'FontSize',26);


% Hint: place code in OpeningFcn to populate axes2


% --- Executes on button press in radiobutton2.
function radiobutton2_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.radiobutton_input,'value',0);
set(handles.edit1,'Enable','off');
set(handles.axes3,'Visible','on');
% Hint: get(hObject,'Value') returns toggle state of radiobutton2


% --- Executes on mouse press over axes background.
function axes3_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to axes3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
mouse_enable = 1;
mouse_num = 1;

if mouse_enable
    posi = get(handles.axes3,'CurrentPoint');
    mouse_p(mouse_num,1) = posi(1);
    mouse_p(mouse_num,2) = posi(3);
end

handles.mouse_enable = mouse_enable;
handles.mouse_p = mouse_p;
handles.mouse_num = mouse_num;

guidata(hObject,handles);


% --- Executes on mouse motion over figure - except title and menu.
function figure2_WindowButtonMotionFcn(hObject, eventdata, handles)
% hObject    handle to figure2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
posi = get(handles.axes3,'CurrentPoint');
mouse_num = handles.mouse_num + 1;
mouse_p = handles.mouse_p;

if handles.mouse_enable
    
    mouse_p(mouse_num,1) = posi(1);
    mouse_p(mouse_num,2) = posi(3);
    
%     h1 = line(handles.axes3,x,y,'EraseMode','xor','LineWidth',1,'color','black');
    
end


handles.mouse_p = mouse_p;
handles.mouse_num = mouse_num;
guidata(hObject,handles);


% --- Executes on mouse press over figure background, over a disabled or
% --- inactive control, or over an axes background.
function figure2_WindowButtonUpFcn(hObject, eventdata, handles)
% hObject    handle to figure2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.mouse_enable = 0;
guidata(hObject,handles);
