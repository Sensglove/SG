#include "inc/socket.hh"

Socket::Socket(QObject *parent) : QObject(parent)
{
server=new QTcpServer(this);
connect(server,SIGNAL(newConnection()),this, SLOT(newConnection()));
if(!server->listen(QHostAddress::Any,2666)){
    qDebug()<<"Server could not start!";
}else{
    qDebug()<<"Server started!";
}
connect_flag=false;
}


void Socket::write(string tmp)
{
    tmp=tmp+"\n";
    const char * data=tmp.c_str();
    char ping[1];

    socket->write(data);
    socket->flush();
    socket->waitForBytesWritten(300);
    //socket->read(ping,1);
    //if(ping[0]=='0') connect_flag=false;
}

void Socket::close()
{
   socket->close();

}

void Socket::newConnection(){

    socket=server->nextPendingConnection();
    cout<<"Client connected"<<endl;
    connect_flag=true;


}
