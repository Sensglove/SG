#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>

#define CZUJNIKI 23

using namespace std;

void error(string wiadomosc)
{
    cerr << wiadomosc << endl;
    exit(0);
}

string losowaRamka()
{
    string ramka = "X";
    string pomiary = "";
    char hex[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    char suma_kontrolna[2];
    int suma = 0;

    for (int i = 0; i < CZUJNIKI*4; ++i)
    {
        if ((i % 4) == 0)
        {
            pomiary = pomiary + "0";
        }

        else
            pomiary = pomiary + hex[rand() % 16];
    }
    //suma kontrolna
    for (int i = 0; i < CZUJNIKI*2; ++i)
    {
        string str = pomiary.substr(i*2,2);
        const char *hexstring = str.c_str();
        suma = suma + (int)strtol(hexstring, NULL, 16);
    }
    suma = suma % 256;
    sprintf(suma_kontrolna,"%02x",suma);

    return ramka + pomiary + suma_kontrolna + "\r\n";
}

int main(int argc, char *argv[])
{
    int socket_desc, new_socket;
    int port, iter, freq;
    float stop;
    socklen_t clilen;
    struct sockaddr_in server, client;
    char buffer[256];
    int n;
    int yes = 1;
    string wiadomosc;

    srand (time(NULL));

    //odczytanie numeru portu
    if (argc < 2)
    {
     error("Nie podano portu");
     return 1;
    }
    port = atoi(argv[1]);

    if (argc == 2)
    {
        cerr << "Nie podano ilości powtorzeń" << endl;
        iter = 50;
    }
    else iter = atoi(argv[2]);

    if (argc < 3)
    {
        cerr << "Nie podano częstotliwości" << endl;
        freq = 1000;
    }
    else freq = atoi(argv[3]);
    stop = 1.0 / freq;
    stop *=1000;

    //utworzenie socketu
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) error("Blad podczas próby utworzenia socketu");

    //przygotowanie struktury sockaddr_in
    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    //pozbycie sie bledu przy ponownym uzyciu portu 
    if (setsockopt(socket_desc,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) { 
        perror("setsockopt"); 
        exit(1); 
    }

    //połaczenie socketu i porut
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
        error("Bład połaczenia z portem");

    //słuchanie, czekanie na klienta
    listen(socket_desc,5);

    //ustanowienie połączenia z klientem
    clilen = sizeof(client);
    new_socket= accept(socket_desc, (struct sockaddr *) &client, &clilen);
    if (new_socket < 0) error("Blad przy przyjmowaniu połaczenia");

    for (int i = 0; i < iter; ++i)
    {
       // cout << "Przesylam wiadomosc nr: "<< i + 1 << endl;
        wiadomosc = losowaRamka();
        n = write(new_socket, wiadomosc.c_str(), wiadomosc.size());
        if (n < 0) error("ERROR writing to socket");
        //cout << wiadomosc << endl;
        usleep(stop*1000);
    }

    close(new_socket);
    close(socket_desc);
    return 0;
}
