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
 * Klasa zajmująca się przesyłem danych z programu odbierającego je do wizualizujacego poprzez łącze TCP.
 */
class Socket : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Socket Konstruktor obiektu klasy Socket.
     * \param parent
     */
    Socket(QObject *parent = 0);
    /*!
     * \brief write
     * Funkcja przekazująca gniazdom treść do wysłania.
     * \param tmp
     */
    void write(string tmp);
    /*!
     * \brief close - funkcja zamykająca połączenie
     */
    void close();
    /*!
     * \brief connected Funkcja zwracająca informację, czy gniazda są ze sobą połączone.
     * \return true - jest połączony, false - nie jest
     */
    bool connected(){ return connect_flag;}

signals:

public slots:
    /*!
   * \brief newConnection Slot inicjujący połączenie.
   */
  void newConnection();

private:
  /*!
     * \brief server Serwer nasłuchujący na podanym kanale.
     */
    QTcpServer *server;
    /*!
     * \brief socket Gniazdo nadające wiadomości na server.
     */
    QTcpSocket *socket;
    /*!
     * \brief connect_flag Flaga połączenia. true - połączony, false - niepołączony
     */
    bool connect_flag;
};

#endif // SOCKET_HH
