% MAIN_ROZPOZNAWANIE Skrypt do rozpoznawania ruchu On-Line
%
% Skrypt sluzacy do rozpoznawania ruchu, ktorego sygnal pochodzi wprast z
% przetwornika. Po uruchomieniu nastepuje  inicjacja wszystkich zmiennych,
% inicjacja przetwornika oraz uruchomienie GUI sluzacego do rozpoznania
% ruchu

clc
close all, clear all

%------------------------- Zmienne globalne -------------------------------
global ruchy                           % Tablice z nazwami ruchow
global Przetwornik                     % Obiekt przetwornika
global data                            % Pobrany sygnal
global lh                              % Event pomiarowy
global rate                            % Czestotliwosc probkowania
global duration                        % Dlugosc pomiaru

global Stopnie_aktywacji               % Stopnie aktywacji sieci neuronowej
global net
global kanaly

global Folder_cechy                    % Sciezki do folderow
global Folder_klasyfikator
global Folder_rozpoznawanie
global Folder_funkcje_pliki
global Folder_sterowanie

global com1                          % Port szeregowy do komunikacji z reka
global com2                    % Port szeregowy do komunikacji z czujnikami
global MR0                      % Wektory z wartosciami katow na przegubach
global MR1                      % reki pozwalajacymi na otrzymanie zadanych
global MR2                                                         % ruchow
global MR3
global MR4
global MR5

%------------------- Inicjacja zmiennych oraz struktur --------------------
Conf();                                    % Inicjacja Scierzek do folderow
addpath(Folder_cechy, Folder_klasyfikator, Folder_sterowanie)
addpath(Folder_funkcje_pliki, Folder_rozpoznawanie);
init();                 % Inicjowanie portu szeregowego oraz wektorow katow

f  = load('Siec_neuronowa');           % Wczytanie pliku z siecia neuronowa
net    = f.net;                                            % Ekstrakcja pol
kanaly = f.kanaly;                                 % Wektor uzytych kanalow
Stopnie_aktywacji = zeros (1,10);                             % Prealokacja

rate = 2000;                                    % Czestotliwosc probkowania
duration = 3;                                       % Dlugosc pomiaru [sec]
Przetwornik = daq.createSession('ni');        % Tworzy obiekt przetwornika
inicjacja_przetwornika(duration, false, rate);    % Inicjacja przetwornika

menu()                                      % Uruchomienie menu graficznego
