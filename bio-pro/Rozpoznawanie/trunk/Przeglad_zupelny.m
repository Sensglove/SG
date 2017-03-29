% PRZEGLAD_ZUPELNY Skrypt do przegladu zypelnego w celu eliminacji kanalow
%
% Skrypt sluzy do sprawdzenia ktore kanaly pomiarowe mozna wyeliminowac z
% rozpoznawania w celu przespieszenia calego procesu.
%
% Po uruchomieniu inicjowane sa wszystkie zmienne, nastepnie gererowana
% jest tablica wszystkich mozliwych zbiorow kanalow, zaczynajac od nika
% ilosci, konczac na maksymalnej dostepnej licznie kanalow.
%
% Nastepnie wczytywane sa wszystkie dostepne probki ruchow, obliczane sa
% ich cechy charakterystyczne, które zapisywane sa w tablicy "Tablica_cech
%
% Stryktura tej tablicy to
% {Cechy_kanalu_1} {Cechy_kanalu_2} ... {Cechy_kanalu_15} {Klasa_ruchu}
% {Cechy_kanalu_1} {Cechy_kanalu_2} ... {Cechy_kanalu_15} {Klasa_ruchu}
% ...
% {Cechy_kanalu_1} {Cechy_kanalu_2} ... {Cechy_kanalu_15} {Klasa_ruchu}
%
% Rozmiar tej tablicy to Calkowita liczba plikow na liczba kanalow +1
%
% Nastepnie konstrulowane sa wektory cech do nauki sieci zgodnie z
% informacjami z tablicy permutacji, ktorej warotsci mowia jakie kanaly
% powinny zostac uzyte w danej iteracji.
%
% Po tym nastepuje proces uczenia sieci nauronowej oraz jej testowania,
% wyniki kazdej iteracji zapisywane sa do pliku Przeglad_zupelny.txt, na
% jego podstawie mozna wybrac najefektywniejszy zestaw kanalow

clc
clear all, close all

%---------------------- Inicjacja parametrow ------------------------------
global ruchy                                     % Tablice z nazwami ruchow
global ile_plikow                              % Ilosci ruchow kazdego typu

global Folder_bazy                                    % Sciezki do folderow
global Folder_cechy
global Folder_funkcje_pliki
global Folder_klasyfikator
global Folder_rozpoznawanie
global Foldery_ruchow

Conf()                                     % Inicjacja Scierzek do folderow
addpath(Folder_cechy, Folder_klasyfikator, Folder_rozpoznawanie);
addpath(Folder_bazy,  Folder_funkcje_pliki);
policz_pliki()

Liczba_kanalow =15;                              % Calkowita liczba kanalow
Zakres_od      =10;               % Najmnijesza rozpatrywana liczba kanalow

%------------------ Generowanie permutacji kanalow ------------------------
wszystkie=0;                                    % Licznik ilosci kombinacji
for ile_elem=Zakres_od:Liczba_kanalow        % Obliczenie ilosci wszystkich
    combos = combntns (1:Liczba_kanalow, ile_elem);            % kombinacji
    [y ~]=size(combos);
    wszystkie=wszystkie+y;
end

Tablica_kombinacji=zeros(wszystkie,15);     % Alokacja tablicy z permutacja
y_p=0;                                            % Przesuniecie poczatkowe

for ile_elem=Zakres_od:Liczba_kanalow               % Przygotowanie tablicy
    combos = combntns (1:Liczba_kanalow, ile_elem);% z informacja o kanalch
    [y x]=size(combos);                       % Po wygenerowaniu permutacji
    for j=1:y                              % Aktywacja wylosowanych kanalow
        for i=1:x
            Tablica_kombinacji(y_p+j ,combos(j,i))=1;
        end
    end
    y_p=y_p+j;                      % Zwiekszenie poczatkowego przesuniecia
end
Tablica_kombinacji=flipud(Tablica_kombinacji);      % Odwrocenie kolejnosci

%----------- Wczytanie calej bazy ruchow oraz ekstrakcja cech -------------
wszystkich_plikow=sum(ile_plikow);               % Zsumowanie liczby plikow
Tablica_cech=cell(wszystkich_plikow, Liczba_kanalow+1);

[~, ilosc_klas] = size(Foldery_ruchow);                % Liczba klas ruchow
Klasy = eye(ilosc_klas);

ptr=1;
for c = 1:ilosc_klas
    files = dir(Foldery_ruchow{c});                 % Pobranie listy plików
    [n,~] = size(files);                           % Pobranie ilosci plikow
    
    for i=3:n                          % Od 3 elem by pominac '.' oraz '..'
        f = load(strcat(Foldery_ruchow{c},files(i).name));    % Zaladowanie
        data = f.data;                                              % pliku
        [~,m] = size(data);                                 % Ilosc kanalow
        
        disp(strcat('Wczytuje plik', files(i).name, ...      % Wyswietlenie
            '   z folderu  /',ruchy{c}))           % akt wczytywanego pliku
        
        for kanal=1:m                             % OBLICZENIE CECH SYGNALU
            Tablica_cech{ptr,kanal}={cechy_MFCC(data(:,kanal))};
        end
        Tablica_cech{ptr,16}={Klasy(:,c)};    % Dodanie informacji o klasie
        ptr=ptr+1;
    end
end
%--------------------------- Sprzetanie -----------------------------------
clear combos K Klasy Zakres_od c data f files ile_elem ile_plikow
clear ilosc_klas kanal m n ptr wszystkich_plikow wszystkie y_p x y


%--------------- Konstrukcja zbioru uczacego oraz uczenie -----------------
[ilosc_prob   ~]=size(Tablica_kombinacji);        % Pobranie ilosc iteracji
[ilosc_probek ~]=size(Tablica_cech);          % Pobranie liczebnosci zbioru
fid = fopen('Przeglad_zupelny.txt','w');  % Otwarcie pliku do zapisu danych

for iteracja=1:ilosc_prob
    disp(strcat('Iteracja-',num2str(iteracja)))
    X=[];                            % Wyczyszczenie zmiennych na wejscie i
    Y=[];                                        % Wyjscie sieci neuronowej
    attr=[];
    
    for j=1:ilosc_probek                      % Konstrulowanie wektory cech
        for i=1:Liczba_kanalow
            if (Tablica_kombinacji(iteracja,i) == 1)
                attr = [attr cell2mat(Tablica_cech{j,i})'];
            end
        end
        X = [X attr'];                                            % Wejscia
        Y = [Y cell2mat(Tablica_cech{j,16})];                     % Wyjscia
        attr=[];
    end
    
    [net trafienia err] = siec(X,Y);                        % Uczenie sieci
    
    for i=1:Liczba_kanalow                    % Zapis do pliku konfiguracji
        fprintf(fid, '%d ',Tablica_kombinacji(iteracja,i));       % kanalow
    end
    
    for i=1:length(trafienia)                      % Zapis do pliku trafien
        fprintf(fid, '%3.4f ',trafienia(i));
    end
    fprintf(fid, '\n');
    clear net                                             % Usuniecie sieci
end
