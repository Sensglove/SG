function [net, trafienia, mserr] = siec(X,Y, n)
% SIEC - kontruktor klasyfikatora z wykorzystaniem sieci neuronowej z 1 ukryta warstwa.
% Konstruuje nauczona siec neuronowa. Proces uczenia wykorzystuje
% Levenberg–Marquardt algorithm (LMA).
%
% Wejscie:
%   X - dane wejsciowe zbioru uczacego(w. cech)
%   Y - dane wyjsciowe zbioru uczacego(klasy)
%   n -  ilosc hidden neurons, domyslnie 10
%
% Wyjscie:
%   net - wytrenowana siec neuronowa
%   trafienia - wektor zawierajacy udzial poprawnie sklasyfikowanych
%   probek dla kazdej z klas.
%   mserr - blad sredniokwadratowy
%

if nargin < 3
    n = 10;
end
inputs = X;
targets = Y;

%[n,~] = size(X);

% Create a Pattern Recognition Network
hiddenLayerSize = n;
net = patternnet(hiddenLayerSize);

% Setup Division of Data for Training, Validation, Testing
net.divideParam.trainRatio = 70/100;
net.divideParam.valRatio = 15/100;
net.divideParam.testRatio = 15/100;

% Train the Network
[net, tr] = train(net,inputs,targets);

% Test the Network
outputs = net(inputs);
errors = gsubtract(targets,outputs);
mserr = mse(net, targets, outputs);
[c, lx] = size(Y);
lxi = lx / c;
trafienia = ones(c,1) * lxi;
l = 1;
r = lxi;

for i=1:c
    [~, ind] = max(outputs(:,l:r));
    ind = find(ind ~= i);
    trafienia(i) = trafienia(i) - length(ind);
    
    l = l + lxi;
    r = r + lxi;
end

trafienia = trafienia ./ lxi;

%performance = perform(net,targets,outputs)
%view(net)
%figure, plotperform(tr)
%figure, plottrainstate(tr)
%figure, plotconfusion(targets,outputs)
%figure, ploterrhist(errors)
