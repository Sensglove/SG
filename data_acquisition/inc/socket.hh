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
    bool connected(){ return connect_flag;}

signals:

public slots:
  void newConnection();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    bool connect_flag;
};

#endif // SOCKET_HH
