function [net trafienia err] = uczenie(Foldery_ruchow, zbior_uczacy)
% UCZENIE Funkcja uczaca siec za pomoca bazy ruchow
% Wejscie:
%     N - Ilosc probek(plikow) z kazdej klasy do uczenia
% Wyjscie:
%     net       - Nauczona siec neuronowa
%     trafienia - Wektor z procentami trafien
%     err       - Wektor z procentami bledow

[X Y] = wczytaj_baze(Foldery_ruchow, zbior_uczacy);    % Generowanie zbioru
[net trafienia err] = siec(X,Y);                      % Funkcja uczaca siec
end
