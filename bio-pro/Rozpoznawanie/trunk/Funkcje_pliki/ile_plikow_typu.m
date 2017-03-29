function ilosc = ile_plikow_typu (typ)               % Funkcja zwraca ilosc
% ILE_PLIKOW_TYPU funkcja zwracajaca ilosc plikow zadanego typu ruchu
% kozystajac z danych zawartych w tablicy ile_plikow
%
% Wejscie:
%  typ         - Typ ruchu, identyfikator liczbowy
%   ile_plikow - Tablica z aktualna liczebnoscia pomiarow dla kazdej z klas
%
% Wyjscie:
%  ilosc - Ilosc plikow danego typu ruchu
%

  global ile_plikow                                  % plikow zadanego typu
  ilosc=ile_plikow(typ);             % odczytujac ja z tablicy "ile_plikow"
end
