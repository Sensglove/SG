% MAIN_BAZA Skrypt do generowania bazy ruchow
%
% Skrypt sluzacy do generowania bazy ruchow, po uruchomieniu nastepuje
% inicjacja wszystkich zmiennych, inicjacja przetwornika oraz uruchomienie
% GUI generatora bazy

clc
close all, clear all

%------------------------- Zmienne globalne -------------------------------
global ruchy                           % Tablice z nazwami ruchow
global ile_plikow                      % Ilosci ruchow kazdego typu
global typ_ruchu                       % Typ aktualnie zapisywanego ruchu
global Przetwornik                     % Obiekt przetwornika
global data                            % Pobrany sygnal
global lh                              % Event pomiarowy
global rate                            % Czestotliwosc probkowania
global duration                        % Dlugosc pomiaru

global Folder_bazy                     % Sciezki do folderow z baza
global Folder_cechy                
global Folder_funkcje_pliki  
global Folder_generator_bazy

%------------------------- Inicjacja zmiennych ----------------------------
rate = 2000;                                   % Czestotliwosc probkowania
duration = 3;                                       % Dlugosc pomiaru [sec]

Conf()                                                   % Inicjuje zmianne
addpath(Folder_bazy, Folder_cechy);             % Dodanie sciezek do plikow
addpath(Folder_funkcje_pliki, Folder_generator_bazy);

policz_pliki()                                   % Zlicza pliki w folderach
Przetwornik = daq.createSession('ni');         % Tworzy obiekt przetwornika
inicjacja_przetwornika(duration, false, rate);     % Inicjacja przetwornika

menu()                              % Uruchomienie funkcji menu graficznego
