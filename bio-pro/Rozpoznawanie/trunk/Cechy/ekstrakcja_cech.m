function y = wektor_cech(X)
% WEKTOR_CECH funkcja konstuujaca wektor cech dla pojedynczego pomiaru
% Wektor cech jest konstruoowany po wyznaczeniu cech, z wykorzystaniem 
% algortymu MFCC, dla kazdego kanalu z osobna i sklejenia otrzymanych 
% wektorow w jeden wektor.
%
% Wejscie:
%   X - macierz pojedynczego pomiaru n x ch, n - ilosc probek, ch - ilosc
% kanalow
%
% Wyjscie:
%   y - wektor otrzymanych cech charakterystycznych sygnalu   
%
[~,ch] = size(X);                                 % Pobranie ilosci kanalow
y =[];                                                        % Prealokacja

for i=1:ch  
    y_i = cechy_MFCC(X(:,i));                     % Ekstrakcha cech sygnalu       
    y = [y;y_i];                 % Dokleneijnie kolejnego konalu do wektora
end

end
