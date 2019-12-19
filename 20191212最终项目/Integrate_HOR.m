function varargout = Integrate_HOR(varargin)
% INTEGRATE_HOR MATLAB code for Integrate_HOR.fig
%      INTEGRATE_HOR, by itself, creates a new INTEGRATE_HOR or raises the existing
%      singleton*.
%
%      H = INTEGRATE_HOR returns the handle to a new INTEGRATE_HOR or the handle to
%      the existing singleton*.
%
%      INTEGRATE_HOR('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in INTEGRATE_HOR.M with the given input arguments.
%
%      INTEGRATE_HOR('Property','Value',...) creates a new INTEGRATE_HOR or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Integrate_HOR_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Integrate_HOR_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Integrate_HOR

% Last Modified by GUIDE v2.5 19-Dec-2019 10:42:33

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Integrate_HOR_OpeningFcn, ...
                   'gui_OutputFcn',  @Integrate_HOR_OutputFcn, ...
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


% --- Executes just before Integrate_HOR is made visible.
function Integrate_HOR_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Integrate_HOR (see VARARGIN)

% Choose default command line output for Integrate_HOR
handles.output = hObject;

% filepath operations
filepath = mfilename('fullpath'); 
[pathstr,~]=fileparts(filepath);
cd(pathstr);  % set current matlab path to where .m file stores.
addpath(genpath(pathstr)); % add all subfolders to search path.

% initialization
a1=imread([pathstr,'\source','\Oscilloscope1.jpg']);
set(handles.pushbutton_p1,'cData',a1);
b1=imread([pathstr,'\source','\SignalGenerator1.jpg']);
set(handles.pushbutton_p2,'cData',b1);
c1=imread([pathstr,'\source','\DO_DI1.jpg']);
set(handles.pushbutton_p3,'cData',c1);

% Update handles structure
handles.pathstr = pathstr;


guidata(hObject, handles);

% UIWAIT makes Integrate_HOR wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Integrate_HOR_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton_p1.
function pushbutton_p1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_p1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
a2=imread([handles.pathstr,'\source','\Oscilloscope2.jpg']);
set(handles.pushbutton_p1,'cData',a2);
pause(0.1);
a1=imread([handles.pathstr,'\source','\Oscilloscope1.jpg']);
set(handles.pushbutton_p1,'cData',a1);

Oscilloscope_Project4(handles.figure1);


% --- Executes on button press in pushbutton_p2.
function pushbutton_p2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_p2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
b2=imread([handles.pathstr,'\source','\SignalGenerator2.jpg']);
set(handles.pushbutton_p2,'cData',b2);
pause(0.1);
b1=imread([handles.pathstr,'\source','\SignalGenerator1.jpg']);
set(handles.pushbutton_p2,'cData',b1);
set(Integrate_HOR,'visible','off');

SignalGenerator_Project4(handles.figure1);

% --- Executes on button press in pushbutton_p3.
function pushbutton_p3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_p3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
c2=imread([handles.pathstr,'\source','\DO_DI2.jpg']);
set(handles.pushbutton_p3,'cData',c2);
pause(0.1);
c1=imread([handles.pathstr,'\source','\DO_DI1.jpg']);
set(handles.pushbutton_p3,'cData',c1);
set(Integrate_HOR,'visible','off');
DO_DI_Project4(handles.figure1);
