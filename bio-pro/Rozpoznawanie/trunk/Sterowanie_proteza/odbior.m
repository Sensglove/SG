function [data err] = odbior(com)
% ODBIOR Funkcja dokonujaca pomiaru z czujnik�w tensometrycznych
%
% Wejscia:
%   com - uchwyt do otwartego portu szeregowego, do ktorego podlaczony jest
%       sterownik protezy
%
% Wyjscia:
%   err - 1 w przypadku b��du odczytu
%   data - wektor pomiar�w z czujnik�w
%

fwrite(com,100);
err  =0;
znak =0;

while(znak ~= 60)
    znak = fread(com,1);
end

data = fread(com,17)
data = data(1:7);

znak = fread(com,1);
if(znak ~= 62)
    err = 1;
end
end