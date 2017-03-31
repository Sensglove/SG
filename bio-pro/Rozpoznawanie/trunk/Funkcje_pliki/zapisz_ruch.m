function zapisz_ruch (typ_ruchu)
% ZAPISZ_RUCH funkcja zapisujaca ruch do bazy pomiarow
%
% Wejscie:
%  typ_ruchu   - Typ zapisywanego ruchu, identyfikator liczbowy
%  ruchy       - Tablica nazw ruchow
%  ile_plikow  - Tablica z aktualna iloscia zapisanych ruchow
%  Folder_bazy - Scierzka do folderu z baza pomiarow

global ruchy
global data
global ile_plikow
global Folder_bazy

if (exist(Folder_bazy,'dir') == 0)     % Jesli nie ma katalogu bazy - mkdir
    mkdir(Folder_bazy);
end
old_dir = cd (Folder_bazy);                      % Wejscie do katalogu bazy

if (ispc)
    lista = ls (ruchy{typ_ruchu});  % Utwozenie listy plikow zadanego ruchu
elseif (isunix)
else
    disp('Nie rozpoznano systemu');
end

lista = lista (3:end,:);
[ilosc_plikow ~] = size(lista);

if ilosc_plikow==0                % Gdy folder jest pusty plik ma nazwe "1"
    nazwa_pliku=1;
else                                             % Gdy folder jest niepusty
    for i=1:ilosc_plikow
        pozycja = strfind(lista(i,:), '.');
        lista_nr(i) = str2num(lista(i,1:pozycja-1));
    end
    lista_nr=sort(lista_nr);
    if (lista_nr(1) ~= 1)              % Gdy jedyny plik nie nazywa sie "1"
        nazwa_pliku=1;
    else                                     % Przypadek kontynuacji zapisu
        lista_nr=diff(lista_nr)-1;
        lista_nr=[lista_nr 1];
        nazwa_pliku = find(lista_nr, 1, 'first') +1;
    end
end

cd(strcat(Folder_bazy, '/', ruchy{typ_ruchu})); %Wejscie do katalogu zapisu

if exist(strcat(num2str(nazwa_pliku),'.mat'),'file') == 2
    disp ('Proba nadpisania pliku w zapisie')
end

save(num2str(nazwa_pliku),'data');                                  % Zapis
ile_plikow(typ_ruchu)=ile_plikow(typ_ruchu)+1;
cd (old_dir);                               % Wyjscie do katalogu roboczego

end
