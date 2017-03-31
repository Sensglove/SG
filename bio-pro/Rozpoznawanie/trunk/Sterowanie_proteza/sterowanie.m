function [ stop ] = sterowanie(Ruch)
% STEROWANIE Funkcja sterowania krokowego protezy z pomiarem naciskow
%
% Sterowanie odbywa sie krokowo, w 20 rownych krokach.
% Po wykonaniu kazdego z krokow, odczytywany jest pomiar z czujnikow
% tensometrycznych. Jesli nacisk zmierzony na kt�rymkolwiek z nich \
% przekroczy warto�� graniczny ruch zostaje zatrzymany.
%
%  Wejscia:
%     comReka - uchwyt do portu szeregowego, do kt�rego podlaczony jest
%           sterownik protezy
%     comCzujniki - uchwyt do portu szeregowego, do ktorego podlaczony jest
%           modul czujnikow
%     Ruch - typ ruchu:
%       0 - najpierw kciuk
%       1 - najpierw palce 1-3
%       2 - wszystkie jednocze�nie
%
%  Wyjscie:
%     stop:
%       0 - kontynuuj ruch
%       1 - przerwij ruch



global com1;                  % Port szeregowy do komunikacji z reka
global com2;                  % Port szeregowy do komunikacji z czujnikami
global MR0;
global MR1;                   % Macierze z katami reprezetujacymi
global MR2;                   % Zadane ruchy
global MR3;
global MR4;
global MR5;

comReka=com1;                 %Przypisanie zmienych do
comCzujniki=com2;

switch Ruch
    case 1
        MR=MR1;               %Cylindryczny
        R=2;
    case 3
        MR=MR2;               %Opuszkowy
        R=2;
    case 5
        MR=MR3;               %Koncentryczny
        R=2;
    case 7
        MR=MR4;               % Hakowy
        R=2;
    case 9
        MR=MR5;               % Cylindryczny
        R=2;
    otherwise
        MR=MR0;
        R=2;
end

nacisk = 0;
MK = MR ./ 20;
MT = zeros(4,4);

for i = 1 : 20
    if nacisk == 0                  % Wykonanie jednego kroku i sprawdzenie
        MT = MT + MK;                                    % czy prog nacisku
        nacisk = krok(MT, comReka, comCzujniki, R)     % zostal przkroczony
    end
end
end

