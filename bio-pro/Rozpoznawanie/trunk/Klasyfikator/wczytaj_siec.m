function [ net kanaly ] = wczytaj_siec(path)
% WCZYTAJ_SIEC funkcja umozliwiajaca wczytanie poprzednio wytrenowanej sieci
%
% Wejscie:
%   path - sciezka do pliku(opcjonalne)
%
% Wyjscie:
%   net    - odczytana z pliku siec neuronowa
%   kanaly - Wektor z informacja dla ktorych kanalow siec zostala nauczona

if nargin < 1
    path = './net.m';
end

f = load(path);
net = f.net;
kanaly = f.kanaly;

% Przykład użycia sieci:
% X = wczytaj_baze(10);
% y = net(X);
%

end