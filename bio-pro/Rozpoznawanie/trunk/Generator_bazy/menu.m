% Skrypt z funkcjami obslugujacymi interfejs graficzny generatora bazy

function varargout = menu(varargin)
% MENU MATLAB code for menu.fig
%      MENU, by itself, creates a new MENU or raises the existing
%      singleton*.
%
%      H = MENU returns the handle to a new MENU or the handle to
%      the existing singleton*.
%
%      MENU('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MENU.M with the given input arguments.
%
%      MENU('Property','Value',...) creates a new MENU or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before menu_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to menu_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help menu
% Last Modified by GUIDE v2.5 22-Apr-2013 15:02:12
% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @menu_OpeningFcn, ...
    'gui_OutputFcn',  @menu_OutputFcn, ...
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


% --- Executes just before menu is made visible.
function menu_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to menu (see VARARGIN)

% Choose default command line output for menu
handles.output = hObject;

global ruchy;
global ile_plikow;
global uchwyty;

uchwyty.axes1 = handles.axes1;
uchwyty.axes2 = handles.axes2;
strings = ruchy;

% Update handles structure
set(handles.togglebutton1,'string',strings{1},'enable','on')
set(handles.togglebutton2,'string',strings{2},'enable','on')
set(handles.togglebutton3,'string',strings{3},'enable','on')
set(handles.togglebutton4,'string',strings{4},'enable','on')
set(handles.togglebutton5,'string',strings{5},'enable','on')
set(handles.togglebutton6,'string',strings{6},'enable','on')
set(handles.togglebutton7,'string',strings{7},'enable','on')
set(handles.togglebutton8,'string',strings{8},'enable','on')
set(handles.togglebutton9,'string',strings{9},'enable','on')
set(handles.togglebutton10,'string',strings{10},'enable','on')

set(handles.pushbutton2,'string','start','enable','on')
set(handles.pushbutton3,'string','zapisz','enable','off')

set(handles.text1,'string',ile_plikow(1));
set(handles.text2,'string',ile_plikow(2));
set(handles.text3,'string',ile_plikow(3));
set(handles.text4,'string',ile_plikow(4));
set(handles.text5,'string',ile_plikow(5));
set(handles.text6,'string',ile_plikow(6));
set(handles.text7,'string',ile_plikow(7));
set(handles.text8,'string',ile_plikow(8));
set(handles.text9,'string',ile_plikow(9));
set(handles.text10,'string',ile_plikow(10));

% globalna zmienna countDown
global countDown;
global duration;

countDown.dt = .1; % rozdzielczosc timera
countDown.tBegin = duration; %czas do zliczenia do momentu rozpoczecia ruchu
countDown.t = duration;
countDown.T = timer('ExecutionMode','fixedDelay','TimerFcn',...
    {@textCountToBeginUpdate,hObject,handles},'TasksToExecute',...
    countDown.tBegin / countDown.dt,'period',countDown.dt);%timer
countDown.ch = 0;

%set(handles.textCountToEnd,'String',num2str(countDown.t));
set(handles.textCountToBegin,'String',num2str(countDown.t));

guidata(hObject, handles);

% UIWAIT makes menu wait for user response (see UIRESUME)
% uiwait(handles.figure1);

function setStopButton(obj, hObject, eventdata, handles)
set(handles.pushbutton2,'string','start','enable','on')

% --- Outputs from this function are returned to the command line.
function varargout = menu_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Metoda wyswietlajaca stan timera odliczajacego do czasu rozpoczecia
% ruch w kontrolce textcountDown
function textCountToBeginUpdate(obj,event,hObject,handles)
global countDown;
global started;
global data;
if countDown.t < .1
    
    % if  countDown.ch == 0
    set(handles.textCountToBegin,'String','0');
    set(handles.pushbutton2,'string','start','enable','on');
    set(handles.pushbutton3,'enable','on')
    
    started = 0;
    
    plot(handles.axes2, data)
    grid(handles.axes2);
else
    
    set(handles.textCountToBegin,'String',num2str(countDown.t));
    
    
end

%end
countDown.t = countDown.t - countDown.dt;

% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global started;
global countDown;
global duration;

if started == 1
    countDown.t = duration;
    started = 0;
else
    set(handles.pushbutton2,'string','start','enable','off')
    set(handles.pushbutton3,'enable','off')
    cla(handles.axes2);
    started = 1;
    
    countDown.t = duration;
    start(countDown.T);
    pomiar();
    
end

% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global ile_plikow;
type = 0;

if(get(handles.togglebutton1, 'Value') == 1)
    type = 1;
    zapisz_ruch(type);
    set(handles.text1,'string',ile_plikow(type));
    
elseif(get(handles.togglebutton2, 'Value') == 1)
    type = 2;
    zapisz_ruch(type);
    set(handles.text2,'string',ile_plikow(type));
    
elseif(get(handles.togglebutton3, 'Value') == 1)
    type = 3;
    zapisz_ruch(type);
    set(handles.text3,'string',ile_plikow(type));
    
elseif(get(handles.togglebutton4, 'Value') == 1)
    type = 4;
    zapisz_ruch(type);
    set(handles.text4,'string',ile_plikow(type));
    
elseif(get(handles.togglebutton5, 'Value') == 1)
    type = 5;
    zapisz_ruch(type);
    set(handles.text5,'string',ile_plikow(type));
    
elseif(get(handles.togglebutton6, 'Value') == 1)
    type = 6;
    zapisz_ruch(type);
    set(handles.text6,'string',ile_plikow(type));
    
elseif(get(handles.togglebutton7, 'Value') == 1)
    type = 7;
    zapisz_ruch(type);
    set(handles.text7,'string',ile_plikow(type));
    
elseif(get(handles.togglebutton8, 'Value') == 1)
    type = 8;
    zapisz_ruch(type);
    set(handles.text8,'string',ile_plikow(type));
elseif(get(handles.togglebutton9, 'Value') == 1)
    type = 9;
    zapisz_ruch(type);
    set(handles.text9,'string',ile_plikow(type));
elseif(get(handles.togglebutton10, 'Value') == 1)
    type = 10;
    zapisz_ruch(type);
    set(handles.text10,'string',ile_plikow(type));
    
end
set(handles.pushbutton3,'enable','off')
