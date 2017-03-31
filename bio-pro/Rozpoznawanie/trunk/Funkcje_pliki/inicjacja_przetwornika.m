function inicjacja_przetwornika (duration, iscontinuous, rate)
% INICJACJA_PRZETWORNIKA funkcja inicjujaca przetwornik
%
% Wejscie:
%  duration     - Dlugosc pomiaru w sekundach
%  iscontinuous - Czy pomiar ma miec charakter ciagly
%  rate         - Czestotliwosc probkowania

global Przetwornik
global lh
kanaly={'ai0','ai1','ai2','ai3','ai4','ai5','ai6','ai7','ai8',...
  'ai9','ai10','ai11','ai12','ai13','ai14'};                 % Uzyte kanaly

Przetwornik.addAnalogInputChannel('Dev1',kanaly, 'Voltage');      % Dodanie
Przetwornik.Channels                               % i wyswietlenie kanalow

Przetwornik.IsContinuous = iscontinuous;               % Czy pomiar ciagly?
Przetwornik.Rate = rate;                        % Czestotliwosc probkawania
Przetwornik.DurationInSeconds = duration;            % CZas trwania pomiaru

lh=Przetwornik.addlistener('DataAvailable', @przechwyt_danych);
end
