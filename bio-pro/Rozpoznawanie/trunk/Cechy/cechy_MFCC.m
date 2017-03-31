function cechy_badanego=cechy_MFCC (data)
%% CECHY_MFCC funkcja implementujaca algortym MFCC dla wyznaczania w. cech
%
% Funkcja wyznacza wektor cech wykorzystujac algortym MFCC dla wektora
% probek.
%
% Wejscie:
%   data - wektor probek sygnalu.
%
% Wyjscie:
%   cechy_badanego - wektor cech dla badanego sygnalu.
%

wielkosc_ramki=256;     % Okreslamy para z jakimi bedzie analizowany sygnal
nMel=8;              % Ilosc filtrow melowych, a co za tym idzie ilosc cech
nakladanie=64;
typ_okna=@hamming;
inv=0;
fp=2000;
fs=10000;

r=size(data);
if r(1)>(2*fs)
  data=data(floor(r(1)/2)-fs+1:ceil(r(1)/2)+fs);
end

w=fp/(2*fs);
filtr=fir1(512,w);
data=filter(filtr,1,data);
data=data(1:fs/fp:size(data));
wynik=analiza(data,wielkosc_ramki,nMel,fp,nakladanie,typ_okna,inv);

cechy_badanego=[];
for n=1:nMel
  cechy_badanego=[cechy_badanego; median(wynik(n,:)); sqrt(var(wynik(n,:)))];
  
end
end

function [cechy fil ] = analiza(syg,ramka,iloscMel,fp,nakladanie,okno,inv)
%% ANALIZA Fukcja analiza realizuje algorytm MFCC na otrzymanym sygnale. 
%
%Najpierw przygotowujemy badany sygnal i tniemy go na mniejsze ramki i
%nakladamy okna
%
% Wejscie:
%   syg        - wektor sygnalu wejsciowego   
%   ramka      - obudowanie sygnalu w ramke
%   iloscMel   - ilosc filtrow melowych
%   fp         - czestotliwosc probkowania
%   nakladanie - jak bardzie maja nakladac sie sosiednie filtry
%   okno       - typ zastosowanego okna
%   inv        - czy obrocic dane w filtrach
%
% Wyjscie:
%   cechy - wyekstrachowane cechy sygnalu

syg=syg(:);
if ~exist('nakladanie','var')
    nakladanie=0;
end

wind=okno(ramka);
koniec=length(syg')-ramka; 

syg_pociety=[];                       %Pusta macierz, gotowa do wypelnienia
t=1;

syg=syg';
while t < koniec
   syg_pociety=[syg_pociety (syg(t:t+ramka-1).*wind')']; 
   t=t+ramka-nakladanie-1;
end

syg=syg';

%plot(syg_pociety)
sygf=fft(syg_pociety);   % Pociete fragmety sygnalu sa poddawane trans four
%plot(sygf)

% Nastepnie bierzemy tylko polowe otrzymanej transformaty, gdyz druga
sygf=sygf(1:ramka/2,:);                        % polowa jest tylko odbiciem
%plot(sygf)
% Podnoscimy do kwadratu otrzymane widmo aby uzyskac widmo mocy
sygm=abs(sygf).^2;
%plot(sygm)

filtry=melfiltr(ramka/2,iloscMel,fp/2);     %Tworzymy bank filtrow melowych
if exist('inv','var')
    if inv==1
        filtry=filtry(end:-1:1,end:-1:1);
    end
end

ilosc_ramek=size(syg_pociety,2);
cechy=zeros(iloscMel,ilosc_ramek);

% Przemnazamy odpowiednio widmo mocy kazdego sygnalu przez kazdy filtr
for i=1:ilosc_ramek
    cechy(:,i)=sygm(:,i)'*filtry;
end
%plot(cechy)
%Otrzymane wartosci sa logarytmowane a nastepnie poddawane dyskretnej
%trnsformacji kosinusowej
cechy=dct(log(cechy));
%plot(cechy)
end

function bank = melfiltr(dlugsc,ilosc,fp)
%% MELFILTR funkcja tworzaca bank filtrow melowych
%
% Fukcja melfiltr tworzy bank filtrow o zadanej dlugosci
% Dodatkowo funkcja dostaje na wejsciu czestotliwosc probkowania sygnalu
% azeby odpowiednio wyskalowac czestotliwosci srodkowe
%
% Wejscie:
%   dlugosc - dlugosc otrzymanego filtru 
%   ilosc   - ilosc otrzymanych filtrow 
%   fp      - czestotliwosc probkawania sygnalu
%
% Wyjscie:
%   bank - otrzymany zbior filtrow

fMel = linspace(0, 1127*log(fp/700+1),dlugsc);% Skalujemy os czestotliwosci        
melStep = floor(fMel(end)/(ilosc+1));                    %generujemy wektor
melCenFreq = 0:floor(melStep):fMel(end);                % czestotliwosci od 

linCenFreq = 700*(exp(melCenFreq/1127)-1);     % zera do 1127*log(fp/700+1)
fLin = linspace(0,fp,dlugsc);

cntFreqIdx = [];
for i=1:numel(linCenFreq)                       % Znajdujemy czestotliwosci
    tmp = find( fLin <= linCenFreq(i) );                  % srodkowe filtru
    cntFreqIdx = [cntFreqIdx tmp(end)];
end

bank = zeros(dlugsc,ilosc);
for i=1:ilosc                                           % Tworzenie filtrow
    k=numel(cntFreqIdx(i):cntFreqIdx(i+2));
    bank(cntFreqIdx(i):cntFreqIdx(i+2),i) = triang(k)';
end

end
