#ifndef KLIENT_HPP
#define KLIENT_HPP

#include <QThread>
#include <QMutex>
#include <QtNetwork>
#include <QWaitCondition>

extern bool stop;

class Klient : public QThread
{
    Q_OBJECT

    public:
        Klient(QObject *rodzic = 0);
        ~Klient();

        void run() override;

        public slots:
            void poinformujSerwer();

        signals:
            void nowaWiadomosc(const QString &wiadomosc);

        private:
            QTcpSocket *socket;
            bool koniec;
            bool sprSumy(QString);
            bool quit;
            QMutex mutex;
            QWaitCondition cond;
};

#endif
