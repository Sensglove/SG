% INIT inicjalizacja obslugi portu szeregowego
% 1. Skrypt zapiuje tablice sterowan dla roznych gestow w zmiennych 
% globalnych MRx(x - numer gestu).
% 2. Skrypt otwiera 2 porty szeregowe i zapisuje uchwyty do nich do
% zmiennych globalnych: com1 - port do sterowania reka, com2 port do
% odczytu pomiarow tensometrycznych

global com1                         % Port szeregowy do komunickacji z reka
global com2                   % Port szeregowy do komunickacji z czujnikami
global MR0                      % Wektory z wartosciami katow na przegubach
global MR1                      % reki pozwalajacymi na otrzymanie zadanych
global MR2                                                         % ruchow
global MR3
global MR4
global MR5

MR0=[0,0,0,0;0,0,0,0;10,0,0,0;0,0,0,0];                      % Otwarta reka
MR1=[80,10,-20,60;10,60,50,0;10,60,50,0;-5,60,50,0];         % Cylindryczny
MR2=[80,10,-20,60;10,60,50,0;10,60,50,0;-5,0,0,0];             % Szczypcowy
MR3=[65,0,0,60;5,60,70,0;10,60,60,0;0,60,80,0];                 % Opuszkowy
MR4=[60,-10,10,60;10,45,70,0;10,60,60,0;0,45,80,0];                % Hakowy
MR5=[40,70,20,0;30,60,50,0;0,60,60,0;20,70,80,0];           % Koncentryczny

com1 = serial('COM1');                                % Com sterowania reki  
fopen(com1);                                % Otwarcie Com sterujacego reka
com2 = serial('COM6');                            % Com sprzeenia zwrotnego   
fopen(com2);                            % Otwarcie Com sprzezenia zwrotnego  
