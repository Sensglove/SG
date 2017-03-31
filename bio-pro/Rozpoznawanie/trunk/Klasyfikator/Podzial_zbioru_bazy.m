function [zbior_uczacy zbior_testowy] = Podzial_zbioru_bazy (stosunek)
% PODZIAL_BAZY Funkcja dzielaca cala baze ruchow na zbior uczacy oraz
% testowy
%
% Funkcja ta dzieli z zadanym stosunkiem dostepne pliki pomiarow pomiedzy
% zbior sluzacy do uczenia oraz testowania. wyjsciem tej funkcji sa celle
% w ktorych zapisane sa sciazki do plikow ruchow
%
% Wejscie:
%   stosunek - jest to stosunek liczebnosci zbioru testowego do uczacego
%
% Wyjscie:
%   zbior_uczacy  - Sciezki do plikow zbioru uczacego
%   zbior_testowy - Sciezki do plikow zbioru testowego

global ile_plikow
global ruchy  
global Foldery_ruchow

do_wykozystania_test  =ile_plikow.*stosunek;  % Obliczenie liczeb testowego
do_wykozystania_nauka =ile_plikow-do_wykozystania_test;

zbior_uczacy = cell(length(ruchy), max(ile_plikow));          % Prealokacja
zbior_testowy= cell(length(ruchy), max(ile_plikow));
policz_pliki();

% Podział zaimplementowany jako - na poczatku uczenie, dalsza czesc na test

for i=1:length(ruchy)
    pliki = dir(Foldery_ruchow{i});      % Pobranie listy plikow w katalogu
    
    for j=1:ile_plikow(i)                 
         if j<do_wykozystania_nauka(i)               % Przydzielanie plikow
             zbior_uczacy(i,j)=cellstr(pliki(j+2).name);
         else
             zbior_testowy(i,j)=cellstr(pliki(j+2).name);
         end
    end
end
end
