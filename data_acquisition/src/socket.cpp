#include "socket.hh"

Socket::Socket(QObject *parent) : QObject(parent)
{
server=new QTcpServer(this);
connect(server,SIGNAL(newConnection()),this, SLOT(newConnection()));
if(!server->listen(QHostAddress::Any,2666)){
    qDebug()<<"Server could not start!";
}else{
    qDebug()<<"Server started!";
}
}
/*
Socket::Socket(QObject *parent,string data) : QObject(parent)
{
   // data1=data;
server=new QTcpServer(this);
connect(server,SIGNAL(newConnection()),this, SLOT(newConnection()));
if(!server->listen(QHostAddress::Any,2666)){
    qDebug()<<"Server could not start!";
}else{
    qDebug()<<"Server started!";
}

}*/

void Socket::write(string tmp)
{
   // if(server->hasPendingConnections()){
    tmp=tmp+"\n";
   // if(server->isListening())
    const char * data=tmp.c_str();

    socket->write(data);
    socket->flush();
    socket->waitForBytesWritten(300);

//}
    //else cout<<"nikt nie odbiera."<<endl;
}

void Socket::close()
{
   socket->close();

}

void Socket::newConnection(){

    socket=server->nextPendingConnection();
    cout<<"POŁączony"<<endl;


}

