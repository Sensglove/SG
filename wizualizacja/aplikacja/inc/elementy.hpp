#ifndef ELEMENTY_HPP
#define ELEMENTY_HPP

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <vector>
#include "inc/qcustomplot.h"
#include "inc/globalne.hpp"

class Wykres : public QLabel
{
    Q_OBJECT

    public:
        Wykres(int, QWidget *wRodzic = 0);
        void aktualizuj(float);
        float ostatniaWartosc;
        float nowaWartosc;
        QCustomPlot * customPlot;
        int id;
    protected:
        void mouseReleaseEvent(QMouseEvent *event) override;

    signals:
        void zaznaczonyWykres(int);

};

class WykresyNacisk : public QWidget
{
    Q_OBJECT

    public:
        WykresyNacisk(QWidget *wRodzic = 0);
        int idWykresSpecjalny;
        std::vector <Wykres*> listaWykresow;

    private:
        QTimer *dataTimer;
        Wykres *wykresGlowny;

    public slots:
        void aktualizuj(QStringList);
        void timeDataSlot();
        void zmianaWykresuGlownego(int);
};

class WykresyZgiecie : public QWidget
{
    Q_OBJECT

    public:
        WykresyZgiecie(QWidget *wRodzic = 0);
        int idWykresSpecjalny;
        std::vector <Wykres*> listaWykresow;

    private:
        QTimer *dataTimer;
        Wykres *wykresGlowny;

    public slots:
        void aktualizuj(QStringList);
        void timeDataSlot();
        void zmianaWykresuGlownego(int);
};

class WykresyElektrody : public QWidget
{
    Q_OBJECT

    public:
        WykresyElektrody(QWidget *wRodzic = 0);
        std::vector <Wykres*> listaWykresow;

    private:
        QTimer *dataTimer;

    public slots:
        void aktualizuj(QStringList);
        void timeDataSlot();
};

class WidokReki : public QWidget
{
    Q_OBJECT

    public:
        WidokReki(QWidget *wRodzic = 0);

    private:
      QImage  Reka;
      QStringList list;
      int wybranyCzujnik;

      void paintEvent( QPaintEvent * event );

     public slots:
        void zmianaWybranegoCzujnika(int);
      void aktualizuj(QStringList);
};

#endif
