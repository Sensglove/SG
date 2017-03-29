function Testowanie (net, zbior_testowy, kanaly)
% TESTOWANIE Funkcja testujaca skutecznosc sieci neuronowej
%
% Wejscie:
%   net           - Siec neuronwa 
%   zbior_testowy - Zbior z plikami ruchow to testu skutecznosci
%   kanaly        - Tablica z informacja ktore kanaly zostaly uzyte do
%                   nauki sieci

if (nargin < 3)                              % Zabezpieczenie przed brakiem
    kanaly = ones (1, 16);                          % informacji o kanalach
end

global ruchy                                     % Tablica z nazwami ruchow
global Foldery_ruchow                        % Scierzki do plikow z ruchami
ilosc_klas = length(Foldery_ruchow);          % Pobranie liczby klas ruchow

parfor c = 1:ilosc_klas                                 % Petla wspolbiezna
    
    for i=1:ile_plikow_typu(c)
         if (~isempty(zbior_testowy{c,i}))         % Jesli plik uczestniczy 
            f = load(strcat(Foldery_ruchow{c},zbior_testowy{c,i}));
            
            disp(strcat('Wczytuje plik', zbior_testowy{c,i}, ...
                '   z folderu  /',ruchy{c},'  do testu'))
            
            data = f.data;
            [~,m] = size(data);                   % Pobranie ilosci kanalow
            
            for j=1:m                          % Usuniecie zadanych kanalow
                if (kanaly(j) == 0)
                    data(j,:)=[]
                end
            end
            
            x = ekstrakcja_cech(data);                    % Ekstrakcja cech
            y = net(x)                                  % Rozpoznanie gestu            
        end
    end
end
end
