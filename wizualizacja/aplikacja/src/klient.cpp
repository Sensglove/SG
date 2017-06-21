#include <QtNetwork>
#include "inc/klient.hpp"
#include "inc/globalne.hpp"

bool stop = false;

Klient::Klient(QObject *rodzic) : QThread(rodzic), quit(false)
{
}

Klient::~Klient()
{
    quit = true;
    wait();
}

void Klient::run()
{
    QString serverName = settings.nazwaSerwera;
    quint16 serverPort = settings.portSerwera;
    int i = 0;

    socket = new QTcpSocket;

    while (!quit)
    {
        const int Timeout = 5 * 1000;

        socket->connectToHost(serverName, serverPort);

        while (!socket->waitForConnected(5000) && !quit)
        {
            QThread::sleep(3);
            serverName = settings.nazwaSerwera;
            serverPort = settings.portSerwera;
            socket->connectToHost(serverName, serverPort);
            qDebug() << "Brak polaczenia z serwerem.";
        }

        QString wiadomosc;
        while ((socket->waitForReadyRead(Timeout) || socket->canReadLine()) && !quit)
        {
            wiadomosc = socket->readLine(110);

            if (i % 10 == 0)
            {
                emit nowaWiadomosc(wiadomosc);
            }
            ++i;
        }

    }
    socket->close();
}

void Klient::poinformujSerwer()
{
    if (socket->state() == QTcpSocket::ConnectedState)
    {
        socket->write("0",1);
        socket->flush();
    }
}
