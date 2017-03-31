function [ aktywacje klasa ] = rozpoznaj( net, x )
% ROZPOZNAJ Funkcja rozpoznajaca wykonany gest za pomoca nauczonej sieci
%
% Rozpoznanie wykonanego gestu z uzyciem nauczonej sieci
% Funckcja umozliwia przpeprowadzenie klasyfikacji nowego pomiaru/grupy
% pomiarow na podstawie wektora cech wyznaczonego algorytmem MFCC i odp
% zlozonym w funkcji ekstrakcja_cech
%
% Wejscie:
%   net - wytrenowana siec neuronowa
%   x   - wektor cech nowego pomiaru
%
% Wyjscie:
%   aktywacja - wektor wartosci aktywacji dla kazdej z klas
%   klasa     - nr klasy o najwyzszym wspolczynniku aktywacji

aktywacje = net(x);
[~, i] = max(aktywacje);
klasa = i;

end

