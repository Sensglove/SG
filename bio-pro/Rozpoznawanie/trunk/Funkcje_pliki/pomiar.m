function pomiar ()                              % Funkcja inicjujaca pomiar
% POMIAR funkcja inicjujaca pomiar z przetwornika
%
% Wejscie:
%  lh          - Event pomiarowy
%  Przetwornik - Struktura przetwornika
%
% Wyjscie:
%  data - Macierz zawierajaca wynik pomiaru

global lh
global data
global Przetwornik

data = double.empty;                              % Ustalenie typu zmiennej
data =[];                                                     % Prealokacja

Przetwornik.startBackground();                 % Uruchomienie pomiaru w tle
end
