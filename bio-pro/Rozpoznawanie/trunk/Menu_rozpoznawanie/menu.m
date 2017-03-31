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


%-------------- Inicjacja przed pojawieniem sie GUI -----------------------
function menu_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to menu (see VARARGIN)

% Choose default command line output for menu
handles.output = hObject;

global ruchy
global ile_plikow
global uchwyty
global Stopnie_aktywacji

uchwyty.axes1 = handles.axes1;
uchwyty.axes2 = handles.axes2;
strings = ruchy;

% Update handles structure
set(handles.text1,'string',Stopnie_aktywacji(1));
set(handles.text2,'string',Stopnie_aktywacji(2));
set(handles.text3,'string',Stopnie_aktywacji(3));
set(handles.text4,'string',Stopnie_aktywacji(4));
set(handles.text5,'string',Stopnie_aktywacji(5));
set(handles.text6,'string',Stopnie_aktywacji(6));
set(handles.text7,'string',Stopnie_aktywacji(7));
set(handles.text8,'string',Stopnie_aktywacji(8));
set(handles.text9,'string',Stopnie_aktywacji(9));
set(handles.text10,'string',Stopnie_aktywacji(10));

set(handles.text11,'string',ruchy(1));
set(handles.text12,'string',ruchy(2));
set(handles.text13,'string',ruchy(3));
set(handles.text14,'string',ruchy(4));
set(handles.text15,'string',ruchy(5));
set(handles.text16,'string',ruchy(6));
set(handles.text17,'string',ruchy(7));
set(handles.text18,'string',ruchy(8));
set(handles.text19,'string',ruchy(9));
set(handles.text20,'string',ruchy(10));

set(handles.pushbutton2,'string','start','enable','on')
set(handles.text_rozpoznany_ruch,'string',' ');

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

global ruchy
global ile_plikow
global uchwyty
global Stopnie_aktywacji
global kanaly
global net

if countDown.t < .1
    
    % if  countDown.ch == 0
    set(handles.textCountToBegin,'String','0');
    set(handles.pushbutton2,'string','start','enable','on');
    
    %load ('Baza_ruchow/Cylindryczny_Z/150.mat') 
    %load ('Baza_ruchow/Opuszkowy_O/1.mat')
    started = 0;
    plot(handles.axes2, data)
    grid(handles.axes2);
    
    [~,m] = size(data);
    for j=1:m                          % Usuniecie zadanych kanalow
        if (kanaly(j) == 0)
            data(j,:)=[]
        end
    end
    
    cechy = ekstrakcja_cech(data);
    [Stopnie_aktywacji rozpoznana_klasa]=rozpoznaj(net, cechy)
    
    set(handles.text1,'string',Stopnie_aktywacji(1));
    set(handles.text2,'string',Stopnie_aktywacji(2));
    set(handles.text3,'string',Stopnie_aktywacji(3));
    set(handles.text4,'string',Stopnie_aktywacji(4));
    set(handles.text5,'string',Stopnie_aktywacji(5));
    set(handles.text6,'string',Stopnie_aktywacji(6));
    set(handles.text7,'string',Stopnie_aktywacji(7));
    set(handles.text8,'string',Stopnie_aktywacji(8));
    set(handles.text9,'string',Stopnie_aktywacji(9));
    set(handles.text10,'string',Stopnie_aktywacji(10));
    set(handles.text_rozpoznany_ruch,'string',ruchy(rozpoznana_klasa));
    
    sterowanie(rozpoznana_klasa);
    
else
    set(handles.textCountToBegin,'String',num2str(countDown.t));
    
end

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
    set(handles.text_rozpoznany_ruch,'string',' ');
    
    cla(handles.axes2);
    started = 1;
    
    countDown.t = duration;
    start(countDown.T);
    pomiar();
end

