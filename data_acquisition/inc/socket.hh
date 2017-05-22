#ifndef SOCKET_HH
#define SOCKET_HH

#include <QObject>

#include <QDebug>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <string>
#include <iostream>

using namespace std;


class Socket : public QObject
{
    Q_OBJECT
public:
    Socket(QObject *parent = 0);
   //  Socket(QObject *parent, string data);

    void write(string tmp);
    void close();

signals:

public slots:
  void newConnection();

private:
    QTcpServer *server;
    QTcpSocket *socket;
};

#endif // SOCKET_HH
