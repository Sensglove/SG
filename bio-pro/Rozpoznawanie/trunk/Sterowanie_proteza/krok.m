function nacisk = krok(MR,comReka, comCzujniki, R)
% KROK Wykonanie mikro ruchu w postaci kroku
% Funkcja przesyla intrukcje wykonania ruchu oraz wykonuje pomiar
% nacisku na wszystkich tensometrach. W przypadku przekorczenia
% wartosci granicznej zwraca 1. Domy�lnie zwraca 0.
%  Wejscie:
%
%    MR - macierz sterowa� 4x4
%    comReka - uchwyt do portu szeregowego, do ktorego podlaczony jest
%           sterownik protezy
%    comCzujniki - uchwyt do portu szeregowego, do ktorego podlaczony jest
%           modul czujnikow
%    R - typ ruchu:
%       0 - najpierw kciuk
%       1 - najpierw palce 1-3
%       2 - wszystkie jednocze�nie
%
%  Wyjscie:
%    nacisk:
%       0 - wartosc graniczna nie przekroczona
%       1 - wartosc graniczna przekroczona

com = comReka;
if (R==0) | (R==2)
    for i=0:1:3
        
        S=252;
        Q=16+i;
        MSB=fix((MR(1,i+1)*10+1000)/256);
        LSB=mod((MR(1,i+1)*10+1000),256);
        SUM=mod(MSB+LSB+Q+S,256);
        
        A=[S;Q;MSB;LSB;SUM];
        fwrite(com, uint8(A));
    end
    
    if (R~=2)
        pause(1);
    end
    
    for i=0:3:6
        for j=1:1:3
            
            S=252;
            Q=19+i+j;
            MSB=fix((MR((i/3+2),j)*10+1000)/256);
            LSB=mod((MR((i/3+2),j)*10+1000),256);
            SUM=mod(MSB+LSB+Q+S,256);
            
            A=[S;Q;MSB;LSB;SUM];
            fwrite(com, uint8(A));
            
        end
    end
    
end

if (R==1)
    
    for i=0:3:6
        for j=1:1:3
            
            S=252;
            Q=19+i+j;
            MSB=fix((MR((i/3+2),j)*10+1000)/256);
            LSB=mod((MR((i/3+2),j)*10+1000),256);
            SUM=mod(MSB+LSB+Q+S,256);
            
            A=[S;Q;MSB;LSB;SUM];
            fwrite(com, uint8(A));
            
        end
    end
    
    pause(1);
    
    for i=0:1:3
        
        S=252;
        Q=16+i;
        MSB=fix((MR(1,i+1)*10+1000)/256);
        LSB=mod((MR(1,i+1)*10+1000),256);
        SUM=mod(MSB+LSB+Q+S,256);
        
        A=[S;Q;MSB;LSB;SUM];
        fwrite(com, uint8(A));
        
    end
end
[dane, err] = odbior(comCzujniki);    % Pomiar nacisku, progowanie wartosci

if any(dane > 25)                   % Procedura sprawdzania poziomu nacisku
    nacisk = 1;
else
    nacisk = 0;
end
end
