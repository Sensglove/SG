% MAIN_ROZPOZNAWANIE_NAUKA Skrypt do nauki sieci neuronowej
%
% Skrypt sluzacy do nauki zastosowanej sieci neuronowej. Po uruchomieniu
% skryptuastepuje inicjacja zmiennych oraz podzial zbioru uczacego na czesc
% do nauki oraz czesc do testow. nastepnie generowany jest zestaw cech dla
% zbioru uczecego oraz nastepuje uruchomienia procesu nauki sieci. Po
% zakonczeniu tego procesu nastepuje uruchomienie funkcji testujacej
% skutecznosc rozpoznawania

clc
close all, clear all

 %------------------- Obsluga wielowatkowosci -----------------------------
 try         
    cores = maxNumCompThreads;  % sprawdz ilosc rdzeni i uruchom matlabpool
    matlabpool(cores)
catch
end
%{
if (matlabpool('size') > 0) 
    disp('Pomyslnie uruchomiono wielowatkowosc')
end
%}
%------------------------- Zmienne globalne -------------------------------
global ruchy                           % Tablice z nazwami ruchow
global ile_plikow                      % Ilosci ruchow kazdego typu

global Folder_bazy                     % Scierzki do folderow
global Folder_cechy    
global Folder_klasyfikator
global Folder_funkcje_pliki  
global Folder_generator_bazy
global Foldery_ruchow

%------------------- Inicjacja zmiennych oraz struktur --------------------
Conf()                                     % Inicjacja Scierzek do folderow
addpath(Folder_bazy, Folder_cechy, Folder_funkcje_pliki); 
addpath(Folder_generator_bazy, Folder_klasyfikator);
policz_pliki()                             % Zbadanie licznosci bazy ruchow

%---------------------- Uczenie sieci neuronowej --------------------------
stosunek=1/200;         % Stosunek liczebnosci zbioru testowego do uczacego
kanaly = ones (1,15);

[zbior_uczacy zbior_testowy] = Podzial_zbioru_bazy (stosunek);

[net trafienia err] = uczenie(Foldery_ruchow, zbior_uczacy);
disp('Uzyskane trafienia')            % Wyswietlenie wspolczynnikow trafien
disp(trafienia)

%-------------------- Testowanie nauczonej sieci --------------------------
Testowanie (net, zbior_testowy)                   % Testowanie skutecznosci
%save('Siec_neuronowa','net','kanaly');
