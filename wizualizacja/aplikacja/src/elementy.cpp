#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include "inc/elementy.hpp"
#include "inc/klient.hpp"
#include <QDebug>

Ustawienia settings;

int R[35] = {0, 15, 30, 45, 60, 75, 90, 105, 120, 135,
             150, 165, 180, 195, 210, 225, 240, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255};

int G[35] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
             255, 255, 255, 255, 255, 255, 255, 255, 240, 225,
             210, 195, 180, 165, 150, 135, 120, 105, 90, 75,
             60, 45, 30, 15, 0};

QColor kolor(QString a)
{
    float wartosc = a.toFloat();
    float dzialka = 3.3/35.0;
    int przedzial = wartosc/dzialka;
    if (przedzial > 34) przedzial = 34;

    return QColor(R[przedzial],G[przedzial],0, 80);
}

Wykres::Wykres(int ID, QWidget *wRodzic) : QLabel(wRodzic)
{
    id = ID;
    customPlot = new QCustomPlot(this);

    customPlot->addGraph();
    QPen blueDotPen;
    blueDotPen.setColor(QColor(34,86,145));
    blueDotPen.setWidthF(2);
    customPlot->graph(0)->setPen(blueDotPen);
    //customPlot->graph(0)->setPen(QPen(QColor(34, 86, 145)));
    //customPlot->setBackground(QColor(87, 95, 102));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setLabel(tr("C Z U J N I K %1").arg(id+1));
    customPlot->yAxis->setLabelFont(QFont(QFont().family(), 10, QFont::Bold));
    customPlot->yAxis->setLabelColor(QColor(34, 86, 145));
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setLabelPadding(1);
    customPlot->yAxis->setRange(0, 3.3);

    customPlot->setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout * lay = new QVBoxLayout;
    lay->addWidget(customPlot);
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    setLayout(lay);
}

void Wykres::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit zaznaczonyWykres(id);
    }
}

/////////////////////////////
//WYKRESY Z CZUJNIKOW NACISKU
WykresyNacisk::WykresyNacisk(QWidget *wRodzic) : QWidget(wRodzic)
{
    idWykresSpecjalny = 0;
    dataTimer = new QTimer(this);
    setStyleSheet("Wykres { border: 1px solid gray; }");

    wykresGlowny = new Wykres(idWykresSpecjalny,this);
    wykresGlowny->setStyleSheet("border: 5px solid #1EACD3;");

    for (int i = 0; i < 10; ++i)
    {
        Wykres * wykres = new Wykres(i, this);
        listaWykresow.push_back(wykres);
        connect(listaWykresow[i],SIGNAL(zaznaczonyWykres(int)),this, SLOT(zmianaWykresuGlownego(int)));
    }

    listaWykresow[idWykresSpecjalny]->setStyleSheet("border: 5px solid #58D3F7;");

    QGridLayout * lay = new QGridLayout;
    lay->addWidget(wykresGlowny,0,0,2,2);
    lay->addWidget(listaWykresow[0],2,0,1,1);
    lay->addWidget(listaWykresow[5],2,1,1,1);
    lay->addWidget(listaWykresow[1],3,0,1,1);
    lay->addWidget(listaWykresow[6],3,1,1,1);
    lay->addWidget(listaWykresow[2],4,0,1,1);
    lay->addWidget(listaWykresow[7],4,1,1,1);
    lay->addWidget(listaWykresow[3],5,0,1,1);
    lay->addWidget(listaWykresow[8],5,1,1,1);
    lay->addWidget(listaWykresow[4],6,0,1,1);
    lay->addWidget(listaWykresow[9],6,1,1,1);

    lay->setVerticalSpacing(0);
    lay->setHorizontalSpacing(0);

    connect(dataTimer, SIGNAL(timeout()), this, SLOT(timeDataSlot()));
    dataTimer->start(100);

    setLayout(lay);
}

void WykresyNacisk::zmianaWykresuGlownego(int id)
{
    listaWykresow[idWykresSpecjalny]->setStyleSheet("border: 1px solid gray;");
    listaWykresow[id]->setStyleSheet("border: 5px solid #58D3F7;");
    idWykresSpecjalny = id;
    wykresGlowny->id = id;
}

void WykresyNacisk::aktualizuj(QStringList lista)
{
    for (int i = 0; i <10; ++i)
    {
        listaWykresow[i]->nowaWartosc = lista[i].toFloat();
    }
}

void WykresyNacisk::timeDataSlot()
{
    static QTime time(QTime::currentTime());

    //w podstwie czas od rozpoczecia programu
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if (stop == false)
    {
        if (key-lastPointKey > 0.001)
        {
            for (int i = 0; i <10; i++)
            {
                listaWykresow[i]->customPlot->graph(0)->addData(key, listaWykresow[i]->nowaWartosc);
            }
            wykresGlowny->customPlot->graph(0)->data()->clear();
            wykresGlowny->customPlot->graph(0)->data()->set(*listaWykresow[idWykresSpecjalny]->customPlot->graph(0)->data());
            wykresGlowny->customPlot->yAxis->setLabel(tr("C Z U J N I K %1").arg(idWykresSpecjalny+1));

            lastPointKey = key;
        }

        for (int i = 0; i <10; i++)
        {
            listaWykresow[i]->customPlot->xAxis->setRange(key, settings.zakres, Qt::AlignRight);
            listaWykresow[i]->customPlot->replot();
            listaWykresow[i]->ostatniaWartosc = listaWykresow[i]->nowaWartosc;
        }

        wykresGlowny->customPlot->xAxis->setRange(key, settings.zakres, Qt::AlignRight);
        wykresGlowny->customPlot->replot();
    }
}

/////////////////////////////
//WYKRESY Z CZUJNIKOW ZGIECIA
WykresyZgiecie::WykresyZgiecie(QWidget *wRodzic) : QWidget(wRodzic)
{
    idWykresSpecjalny = 10;
    dataTimer = new QTimer(this);
    setStyleSheet("Wykres { border: 1px solid gray; }");

    wykresGlowny = new Wykres(idWykresSpecjalny,this);
    wykresGlowny->setStyleSheet("border: 5px solid #1EACD3;");

    for (int i = 10; i < 15; ++i)
    {
        Wykres * wykres = new Wykres(i, this);
        listaWykresow.push_back(wykres);
        connect(listaWykresow[i-10],SIGNAL(zaznaczonyWykres(int)),this, SLOT(zmianaWykresuGlownego(int)));
    }

    listaWykresow[idWykresSpecjalny-10]->setStyleSheet("border: 5px solid #58D3F7;");

    QGridLayout * lay = new QGridLayout;
    lay->addWidget(wykresGlowny,0,0,2,2);
    lay->addWidget(listaWykresow[0],2,0,1,2);
    lay->addWidget(listaWykresow[1],3,0,1,2);
    lay->addWidget(listaWykresow[2],4,0,1,2);
    lay->addWidget(listaWykresow[3],5,0,1,2);
    lay->addWidget(listaWykresow[4],6,0,1,2);

    lay->setVerticalSpacing(0);
    lay->setHorizontalSpacing(0);

    connect(dataTimer, SIGNAL(timeout()), this, SLOT(timeDataSlot()));
    dataTimer->start(100);

    setLayout(lay);
}

void WykresyZgiecie::zmianaWykresuGlownego(int id)
{
    listaWykresow[idWykresSpecjalny-10]->setStyleSheet("border: 1px solid gray;");
    listaWykresow[id-10]->setStyleSheet("border: 5px solid #58D3F7;");
    idWykresSpecjalny = id;
    wykresGlowny->id = id;
}

void WykresyZgiecie::aktualizuj(QStringList lista)
{
    for (int i = 0; i <5; ++i)
    {
        listaWykresow[i]->nowaWartosc = lista[i+10].toFloat();
    }
}

void WykresyZgiecie::timeDataSlot()
{
    static QTime time(QTime::currentTime());

    //w podstwie czas od rozpoczecia programu
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if (stop == false)// && wykres11->ostatniaWartosc != wykres11->nowaWartosc
    {
        if (key-lastPointKey > 0.001)
        {

            for (int i = 0; i <5; i++)
            {
                listaWykresow[i]->customPlot->graph(0)->addData(key, listaWykresow[i]->nowaWartosc);
            }
            wykresGlowny->customPlot->graph(0)->data()->clear();
            wykresGlowny->customPlot->graph(0)->data()->set(*listaWykresow[idWykresSpecjalny-10]->customPlot->graph(0)->data());
            wykresGlowny->customPlot->yAxis->setLabel(tr("C Z U J N I K %1").arg(idWykresSpecjalny+1));

            lastPointKey = key;
        }

        for (int i = 0; i <5; i++)
        {
            listaWykresow[i]->customPlot->xAxis->setRange(key, settings.zakres, Qt::AlignRight);
            listaWykresow[i]->customPlot->replot();
            listaWykresow[i]->ostatniaWartosc = listaWykresow[i]->nowaWartosc;
        }

        wykresGlowny->customPlot->xAxis->setRange(key, settings.zakres, Qt::AlignRight);
        wykresGlowny->customPlot->replot();
    }
}

////////////////////////
//WYKRESY Z BIOSYGNALOW
WykresyElektrody::WykresyElektrody(QWidget *wRodzic) : QWidget(wRodzic)
{
    dataTimer = new QTimer(this);
    setStyleSheet("Wykres { border: 1px solid gray; }");

    for (int i = 15; i < 23; ++i)
    {
        Wykres * wykres = new Wykres(i, this);
        listaWykresow.push_back(wykres);
    }

    QGridLayout * lay = new QGridLayout;
    lay->addWidget(listaWykresow[0],1,0,1,1);
    lay->addWidget(listaWykresow[4],1,1,1,1);
    lay->addWidget(listaWykresow[1],2,0,1,1);
    lay->addWidget(listaWykresow[5],2,1,1,1);
    lay->addWidget(listaWykresow[2],3,0,1,1);
    lay->addWidget(listaWykresow[6],3,1,1,1);
    lay->addWidget(listaWykresow[3],4,0,1,1);
    lay->addWidget(listaWykresow[7],4,1,1,1);

    lay->setVerticalSpacing(0);
    lay->setHorizontalSpacing(0);

    connect(dataTimer, SIGNAL(timeout()), this, SLOT(timeDataSlot()));
    dataTimer->start(100);

    setLayout(lay);
}

void WykresyElektrody::aktualizuj(QStringList lista)
{
    for (int i = 0; i <8; ++i)
    {
        listaWykresow[i]->nowaWartosc = lista[i+15].toFloat();
    }
}

void WykresyElektrody::timeDataSlot()
{
    static QTime time(QTime::currentTime());

    //w podstwie czas od rozpoczecia programu
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if (stop == false)
    {
        if (key-lastPointKey > 0.001)
        {
            for (int i = 0; i <8; i++)
            {
                listaWykresow[i]->customPlot->graph(0)->addData(key, listaWykresow[i]->nowaWartosc);
            }

            lastPointKey = key;
        }

        for (int i = 0; i <8; i++)
        {
            listaWykresow[i]->customPlot->xAxis->setRange(key, settings.zakres, Qt::AlignRight);
            listaWykresow[i]->customPlot->replot();
            listaWykresow[i]->ostatniaWartosc = listaWykresow[i]->nowaWartosc;
        }
    }
}

////////////////
//WIDGET REKI 2D
WidokReki::WidokReki(QWidget *wRodzic) : QWidget(wRodzic)
{
     Reka.load(":/img/reka.png");
     list << "0" << "0" << "0" << "0" << "0" << "0" << "0" << "0" << "0" << "0";
     wybranyCzujnik = 0;
}

void WidokReki::aktualizuj(QStringList lista)
{
    list = lista;
    update();
}

void WidokReki::zmianaWybranegoCzujnika(int id)
{
    wybranyCzujnik = id;
}

void WidokReki::paintEvent(QPaintEvent * )
{
    QPainter  Rysownik(this);

    double ProporcjeWS_Obraz = Reka.height()/Reka.width();
    double ProporcjeWS_Okno = height()/width()/2;
    double Skala;

    if (ProporcjeWS_Obraz > ProporcjeWS_Okno) {
       Skala = height()/static_cast<double>(Reka.height());
    } else {
       Skala = width()/static_cast<double>(Reka.width());
    }
    Rysownik.scale(Skala,Skala);
    Rysownik.drawImage(0,0,Reka);
    Rysownik.setPen(Qt::NoPen);
    //czujnik 1
    if (wybranyCzujnik == 0) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[0])));
    Rysownik.drawEllipse(25,200,50,50);
    //czujnik 6
    if (wybranyCzujnik == 5) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[5])));
    Rysownik.drawEllipse(90,540,50,50);
    //czujnik 2
    if (wybranyCzujnik == 1) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[1])));
    Rysownik.drawEllipse(182,65,50,50);
    //czujnik 7
    if (wybranyCzujnik == 6) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[6])));
    Rysownik.drawEllipse(175,508,50,50);
    //czujnik 3
    if (wybranyCzujnik == 2) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[2])));
    Rysownik.drawEllipse(318,24,50,50);
    //czunjik 8
    if (wybranyCzujnik == 7) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[7])));
    Rysownik.drawEllipse(272,470,50,50);
    //czujnik 4
    if (wybranyCzujnik == 3) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[3])));
    Rysownik.drawEllipse(488,97,50,50);
    //czujnik 9
    if (wybranyCzujnik == 8) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[8])));
    Rysownik.drawEllipse(384,500,50,50);
    //czujnik 5
    if (wybranyCzujnik == 4) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[4])));
    Rysownik.drawEllipse(628,537,50,50);
    //czujnik 10
    if (wybranyCzujnik == 9) Rysownik.setPen(QPen(QColor(30,172,211),2));
    else Rysownik.setPen(Qt::NoPen);
    Rysownik.setBrush(QBrush(kolor(list[9])));
    Rysownik.drawEllipse(388,766,50,50);
}
