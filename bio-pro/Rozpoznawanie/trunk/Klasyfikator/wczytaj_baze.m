function [X Y] = wczytaj_baze(Foldery_ruchow, zbior, kanaly)
% WCZYTAJ_BAZE Funckja do wczytywania zbioru uczacego z bazy probek
% Zbio uczacy jest budowany 2-etapowo:
% 1. Funckja przeszukuje katalogi z probkami dla klazdej z klas, do ktorych
% sciezki sa zapisane w parametrze Foldery_ruchow
% 2. Kazda ze znalezionych probek w postaci pliku nr_probki.m jest
% wczytywana oraz obliczany jest dla niej wektor cech i doklejany do danych
% wejsciowych zbioru uczacego. Rownoczesnie konstruowana jest macierz
% wyjsciowa zbioru uczacego w postaci wektorow zer z 1 na pozycji
% reprezentujaca odp. klase ruchu.
%
% Funkcja wykorzystuje wielowatkowosc.
%
% parametry:
% N - ilosc probek kazdej z klas do pobrania
% dirs - struktura zaw. sciezki do katalog�w z pr�bkami dla roznych klas.
%
% dane na wyjsciu:
% X - dane wejsciowe zbioru uczacego w postaci macierzy n x m, gdzie:
%       n - d�ugosc wektora cech * ilosc kana��w
%       m - ilosc pr�bek
%
% Y - dane wyjsciowe zbioru uczacego w postaci macierzy c x m, gdzie:
%       c - ilosc dostopnych cech
%       m - ilosc probek
%       Przyklad: jezeli probka nr 12 reprezentowala klase nr 3(na 4
%       mozliwe) to Y(12,:) = [0;0;1;0];

if (nargin < 3)                               % Zabezpieczenie przed brakie
    kanaly = ones (1, 16);                          % informacji o kanalach
end
global ruchy                            % Globalna tablica z nazwami ruchow

X = [];                                % Macierz wejsciowa do uczenia sieci
Y = [];                               % Macierz wyjsciowa  do uczenia sieci

ilosc_klas = length(Foldery_ruchow);                    % Ilosc klas ruchow
classes = eye(ilosc_klas);                         % Klasy do rozpoznawnaia

parfor c = 1:ilosc_klas                                % Petla wspolbierzna
    attr = [];                                                % Prealokacja
    class = classes(:,c);    % Pobraneie informacji o przynaleznosci probki
    
    for i=1:ile_plikow_typu(c)
        
        if (~isempty(zbior{c,i}))                             % Zaladowanie
            f = load(strcat(Foldery_ruchow{c},zbior{c,i}));         % pliku
            
            disp(strcat('Wczytuje plik', zbior{c,i}, ...
                '   z folderu  /',ruchy{c},'  do nauki'))
            
            data = f.data;
            [~,m] = size(data);                   % Pobranie ilosci kanalow
            
            for j=1:m                          % Usuniecie zadanych kanalow
                if (kanaly(j) == 0)
                    data(j,:)=[];
                end
            end
            
            attr = ekstrakcja_cech(data);         % Ekstrakcja cech sygnalu
            
            X = [X attr];                % Sklejanie wejscia z wektrow cech
            Y = [Y class];                              % Sklejanie wyjscia
            
            attr = [];                              % Wyczyszczenie wektora
        end
    end
end
end

