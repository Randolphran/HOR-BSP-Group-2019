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

% Last Modified by GUIDE v2.5 28-Nov-2019 15:34:31

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
