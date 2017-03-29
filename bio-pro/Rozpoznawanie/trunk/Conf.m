function Conf ()
% CONF Funkcja inicjujaca zmienne globalne
%
%Funkcja inicjujaca wiekszosc zmiennych globalnych, a wsrod nich
% wszystkie scierzki do wszystkich katalogow oraz wektory z typami ruchow

global ruchy                                 % Wektor z nazwami klas ruchow
global Folder_bazy                                    % Sciezki do folderow
global Folder_cechy
global Folder_klasyfikator
global Folder_funkcje_pliki
global Folder_generator_bazy
global Folder_rozpoznawanie
global Foldery_ruchow
global Folder_sterowanie

ruchy     = cell (1,10);                         % Inicjowanie nazw ruchow
ruchy(1)  = cellstr('Cylindryczny_Z');
ruchy(2)  = cellstr('Cylindryczny_O');
ruchy(3)  = cellstr('Szczypcowy_Z');
ruchy(4)  = cellstr('Szczypcowy_O');
ruchy(5)  = cellstr('Opuszkowy_Z');
ruchy(6)  = cellstr('Opuszkowy_O');
ruchy(7)  = cellstr('Hakowy_Z');
ruchy(8)  = cellstr('Hakowy_O');
ruchy(9)  = cellstr('Koncentryczny_Z');
ruchy(10) = cellstr('Koncentryczny_O');

Folder_bazy           = strcat(pwd, '/Baza_ruchow');
Folder_cechy          = strcat(pwd, '/Cechy');
Folder_funkcje_pliki  = strcat(pwd, '/Funkcje_pliki');
Folder_generator_bazy = strcat(pwd, '/Generator_bazy');
Folder_klasyfikator   = strcat(pwd, '/Klasyfikator');
Folder_rozpoznawanie  = strcat(pwd, '/Menu_rozpoznawanie');
Folder_sterowanie     = strcat(pwd, '/Sterowanie_proteza');

Foldery_ruchow={ strcat(Folder_bazy, '/', ruchy{1}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{2}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{3}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{4}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{5}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{6}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{7}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{8}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{9}, '/'), ...
    strcat(Folder_bazy, '/', ruchy{10}, '/')};
end
