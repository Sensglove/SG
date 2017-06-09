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

/*!
 * \brief The Socket class
 */
class Socket : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Socket
     * \param parent
     *
     * konstruktor obiektu klasy Socket
     */
    Socket(QObject *parent = 0);
    /*!
     * \brief write - funkcja przekazująca socketowi treść do wysłania
     * \param tmp
     */
    void write(string tmp);
    /*!
     * \brief close - funkcja zamykająca połączenie
     */
    void close();
    bool connected(){ return connect_flag;}

signals:

public slots:
    /*!
   * \brief newConnection - slot inicjujący połączenie
   */
  void newConnection();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    bool connect_flag;
};

#endif // SOCKET_HH
