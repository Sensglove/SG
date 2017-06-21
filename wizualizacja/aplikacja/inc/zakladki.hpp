#ifndef ZAKLADKI_HPP
#define ZAKLADKI_HPP

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QDialog>
#include <QQueue>
#include <QPushButton>
#include "inc/klient.hpp"
#include "inc/elementy.hpp"
#include "inc/reka3d.hpp"


class StosDanych : public QObject
{
    Q_OBJECT

    public slots:
        void dodajWiadomosc(QString data){
            sMutex.lock();
            fifo.enqueue(data);
            sMutex.unlock();
        }
        QString usunWiadomosc(){
            QMutexLocker locker(&sMutex);
            return fifo.dequeue();
        }
    public:
        bool czyPusty(){
            return fifo.isEmpty();
        }
    private:
        QMutex sMutex;
        QQueue<QString> fifo;
};



class TabCzujnikiNacisku : public QWidget
{
    Q_OBJECT

    public:
        TabCzujnikiNacisku(QWidget *wRodzic = 0);
        WykresyNacisk *wykresy;
        WidokReki * reka;
};

class TabCzujnikiZgiecia : public QWidget
{
    Q_OBJECT

    public:
        TabCzujnikiZgiecia(QWidget *wRodzic = 0);
        WykresyZgiecie * wykresy;
        Viewer * reka;
};

class TabWszystkieCzujniki : public QWidget
{
    Q_OBJECT

    public:
        TabWszystkieCzujniki(QWidget *wRodzic = 0);
};

class TabElektrody : public QWidget
{
    Q_OBJECT

    public:
        TabElektrody(QWidget *wRodzic = 0);
        WykresyElektrody *wykresy;
};

class Zakladki : public QWidget
{
    Q_OBJECT

    public:
        Zakladki(QWidget *wRodzic = 0);
        void interpretuj(QString);
        TabCzujnikiNacisku * tab1;
        TabCzujnikiZgiecia * tab2;
        TabElektrody * tab4;
        Klient thread;

    signals:
        void gotowyZestawPomiarow(QStringList);

    public slots:
        void wyswietlWiadomosc();
        void toggleWyswietlanie();

    private:

        StosDanych stos;
        QPushButton *START;
};

class OknoUstawien : public QDialog
{
    Q_OBJECT

    public:
        OknoUstawien(QWidget *wRodzic = 0);
        QLineEdit * lineEditZakres;
        QLineEdit * lineEditNazwa;
        QLineEdit * lineEditPort;

    public slots:
        void zapiszZmiany();

};

class OknoGlowne : public QMainWindow
{
    Q_OBJECT

    public:
        OknoGlowne(QWidget *wRodzic = 0);
        void closeEvent( QCloseEvent * event );

    public slots:
        void otworzOknoUstawien();

    private:
        void createActions();
        void createMenus();

        Zakladki * zakladki;
        QMenu *ustawienia;
        QMenu *info;
        QAction * zmienUstawienia;
        QAction * wyswitlInfo;

};

#endif
