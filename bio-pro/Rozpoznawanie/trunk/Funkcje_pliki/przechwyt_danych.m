function przechwyt_danych(src,event)
% PRZECHWYT_DANYCH funkcja przechwytujaca dane z przetwornika
%
% Wejscie:
%  src         - Zrodlo uruchomienia
%  Przetwornik - Event pomiarowy
% Uchwyty      - Struktura uchwytow do wyswietlania wykresu pomiaru
%
% Wyjscie:
%  data - Macierz zawierajaca wynik pomiaru

global data
global uchwyty

plot(uchwyty.axes1, event.TimeStamps, event.Data)       % Plotowanie danych
data=[data; event.Data];                                 % Sklejanie danych
end
