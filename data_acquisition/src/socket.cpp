#include "socket.hh"

Socket::Socket(QObject *parent) : QObject(parent)
{
server=new QTcpServer(this);
connect(server,SIGNAL(newConnection()),this, SLOT(newConnection()));
if(!server->listen(QHostAddress::Any,8888)){
    qDebug()<<"Server could not start!";
}else{
    qDebug()<<"Server started!";
}
}
Socket::Socket(QObject *parent,string data) : QObject(parent)
{
    data1=data;
server=new QTcpServer(this);
connect(server,SIGNAL(newConnection()),this, SLOT(newConnection()));
if(!server->listen(QHostAddress::Any,2666)){
    qDebug()<<"Server could not start!";
}else{
    qDebug()<<"Server started!";
}

}
void Socket::newConnection(){
    const char * bufor=data1.c_str();

    qDebug()<<bufor;

    QTcpSocket *socket=server->nextPendingConnection();
        socket->write(bufor);
        socket->flush();
        socket->waitForBytesWritten(3000);
        socket->close();
}
