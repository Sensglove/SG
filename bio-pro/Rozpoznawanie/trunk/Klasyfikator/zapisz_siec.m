function [  ] = zapisz_siec( net, kanaly, path )
% ZAPISZ_SIEC funkcja umozliwiajaca zapis nauczonej sieci do pliku
%
% Wejscie:
%   net    - nauczona siec neuronowa
%   kanaly - Wektor kanalow uzytych do uczenia sieci
%   path   - sciezka pliku do ktorego siec ma zostac zapisana(opcjonalne)

if nargin < 3
    path = './net.m';
end

save(path, net, kanaly);

end
