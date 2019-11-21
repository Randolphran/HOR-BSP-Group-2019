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

% Last Modified by GUIDE v2.5 14-Nov-2019 17:15:37

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

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes UserDefinedFcn wait for user response (see UIRESUME)
% uiwait(handles.figure1);


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

% Hint: get(hObject,'Value') returns toggle state of radiobutton_input



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
fcn_in = get(hObject,'String');

syms x
fcn_latex = latex(eval(fcn_in));



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
