#ifndef GLOBALNE_HPP
#define GLOBALNE_HPP

#include <QObject>
#include <QColor>
#include <QHostAddress>
#include <iostream>

class Ustawienia : public QObject
{
    Q_OBJECT

    public:
        Ustawienia(){zakres = 30; nazwaSerwera = QHostAddress(QHostAddress::LocalHost).toString(); portSerwera = 2666;}
        float zakres;
        QString nazwaSerwera;
        quint16 portSerwera;

};

extern Ustawienia settings;

#endif
