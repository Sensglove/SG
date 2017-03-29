function policz_pliki ()                            % Funkcja liczaca pliki
% POLICZ_PLIKI funkcja obliczajaca liczebnosc bazy pomiarow
% Funkcja ta listuje zawartosci wszystkich katalogow w ktroych znajduja sie
% zapisane pomiary
%
% Wejscie:
%  ruchy       - Typ ruchu, identyfikator liczbowy
%  Folder_bazy - Sciezka do folderu z baza ruchow
%
% Wyjscie:
%  ile_plikow - Tablica z aktualna liczebnoscia pomiarow dla kazdej z klas

global ruchy
global ile_plikow
global Folder_bazy

if (exist(Folder_bazy,'dir') == 0)   % Sprawdzenie czy istnieje folder bazy
    mkdir(Folder_bazy);                                % jesli nie to mkdir
end
old_dir = cd (Folder_bazy);                      % Wejscie do katalogu bazy

for i=1:length(ruchy)             % Sprawdzenie czy zadane foldery istnieja
    if (exist(ruchy{i},'dir') == 0)                    % jesli nie to mkdir
        mkdir(ruchy{i});
    end
end

ile_plikow=zeros(1,length(ruchy));
for i=1:length(ruchy)                                   % Policzenie plikow
    [ ile_plikow(i) ~] = size( dir(ruchy{i}));
    ile_plikow(i)=ile_plikow(i)-2;                  % Odjecie "." oraz ".."
end

cd (old_dir);                            % Wyjscie do poczatkowego katalogu
end