#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QMenuBar>
#include <QtNetwork>
#include <QValidator>
#include "inc/zakladki.hpp"
#include "inc/elementy.hpp"
#include "inc/klient.hpp"
#include "inc/globalne.hpp"
#include "inc/reka3d.hpp"

TabCzujnikiNacisku::TabCzujnikiNacisku(QWidget *wRodzic) : QWidget(wRodzic)
{
    wykresy = new WykresyNacisk();
    reka = new WidokReki(this);

    for (int i = 0; i < 10; ++i)
    {
        connect(wykresy->listaWykresow[i],SIGNAL(zaznaczonyWykres(int)),reka, SLOT(zmianaWybranegoCzujnika(int)));
    }

    QHBoxLayout *wszystkieLayout = new QHBoxLayout();
    wszystkieLayout->addWidget(wykresy);
    wszystkieLayout->addWidget(reka);
    setLayout(wszystkieLayout);
}

TabCzujnikiZgiecia::TabCzujnikiZgiecia(QWidget *wRodzic) : QWidget(wRodzic)
{
    wykresy = new WykresyZgiecie();
    reka = new Viewer(this);

    QHBoxLayout *wszystkieLayout = new QHBoxLayout();
    wszystkieLayout->addWidget(wykresy);
    wszystkieLayout->addWidget(reka);

    setLayout(wszystkieLayout);
}

TabElektrody::TabElektrody(QWidget *wRodzic) : QWidget(wRodzic)
{
    wykresy = new WykresyElektrody();

    QHBoxLayout *wszystkieLayout = new QHBoxLayout();
    wszystkieLayout->addWidget(wykresy);

    setLayout(wszystkieLayout);
}

Zakladki::Zakladki(QWidget * wRodzic) : QWidget(wRodzic)
{
    stop = false;
    QTabWidget * Zakladki = new QTabWidget;
    tab1 = new TabCzujnikiNacisku();
    tab2 = new TabCzujnikiZgiecia();
    tab4 = new TabElektrody();
    Zakladki->addTab(tab1, tr("Czujniki nacisku"));
    Zakladki->addTab(tab2, tr("Czujniki zgięcia"));
    Zakladki->addTab(tab4, tr("Biosygnały"));

    if (!thread.isRunning())
        thread.start();

    START = new QPushButton(tr("STOP"));
    START->setMinimumWidth(100);

    connect(START, SIGNAL(clicked()),this,SLOT(toggleWyswietlanie()));

    connect(&thread,SIGNAL(nowaWiadomosc(QString)),&stos,SLOT(dodajWiadomosc(QString)));
    connect(&thread,SIGNAL(nowaWiadomosc(QString)),this, SLOT(wyswietlWiadomosc()));

    connect(this, SIGNAL(gotowyZestawPomiarow(QStringList)), tab1->wykresy, SLOT(aktualizuj(QStringList)));
    connect(this, SIGNAL(gotowyZestawPomiarow(QStringList)), tab1->reka, SLOT(aktualizuj(QStringList)));

    connect(this, SIGNAL(gotowyZestawPomiarow(QStringList)), tab2->wykresy, SLOT(aktualizuj(QStringList)));
    connect(this, SIGNAL(gotowyZestawPomiarow(QStringList)), tab2->reka, SLOT(aktualizuj(QStringList)));

    connect(this, SIGNAL(gotowyZestawPomiarow(QStringList)), tab4->wykresy, SLOT(aktualizuj(QStringList)));

    QGridLayout *glownyLayout = new QGridLayout;
    glownyLayout->addWidget(Zakladki,0,0,1,2);
    glownyLayout->addWidget(START, 1,1);

    setLayout(glownyLayout);
}

void Zakladki::wyswietlWiadomosc()
{
    while (!stos.czyPusty())
    {
        QString nowaWiadomosc = stos.usunWiadomosc();
        interpretuj(nowaWiadomosc);
    }
}

void Zakladki::toggleWyswietlanie()
{
    stop = !stop;
    if (stop == false) START->setText("STOP");
    else START->setText("START");
}

void Zakladki::interpretuj(QString currentFortune)
{
    QStringList full;
    bool ok;
    for (int i = 0; i < 23; ++i)
    {
        QString subString = currentFortune.mid(i*4+1,4);
        int odczyt = subString.toInt(&ok, 16);
        float przeliczony_odczyt = odczyt*3.3/qPow(2,12);
        full.append(tr("%1").arg(przeliczony_odczyt));
        if (i > 9) qDebug() << i << " " << przeliczony_odczyt;
    }
    emit gotowyZestawPomiarow(full);
}

OknoUstawien::OknoUstawien(QWidget * wRodzic) : QDialog(wRodzic)
{
    QPushButton * OK = new QPushButton(tr("OK"));

    QGroupBox * ogolneWykresy = new QGroupBox(tr("Ustawienia wykresów"),this);
    lineEditZakres = new QLineEdit(QString::number(settings.zakres), this);
    lineEditZakres->setMaximumWidth(100);
    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(tr("Zakres wykresu:"), lineEditZakres);
    ogolneWykresy->setLayout(formLayout);

    QGroupBox * polaczenieSerwer = new QGroupBox(tr("Dane serwera"),this);
    lineEditNazwa = new QLineEdit(settings.nazwaSerwera, this);
    lineEditNazwa->setMaximumWidth(100);
    lineEditPort = new QLineEdit(QString::number(settings.portSerwera), this);
    lineEditPort->setMaximumWidth(100);
    QFormLayout *form2Layout = new QFormLayout(this);
    form2Layout->addRow(tr("IP serwera:"), lineEditNazwa);
    form2Layout->addRow(tr("Port serwera:"), lineEditPort);
    polaczenieSerwer->setLayout(form2Layout);

    connect(OK, SIGNAL(clicked()),this,SLOT(zapiszZmiany()));

    QGridLayout *caloscLayout = new QGridLayout(this);
    caloscLayout->addWidget(ogolneWykresy,0,0,1,2);
    caloscLayout->addWidget(polaczenieSerwer,1,0,1,2);
    caloscLayout->addWidget(OK,2,1,1,1);
    setLayout(caloscLayout);
}

void OknoUstawien::zapiszZmiany()
{
    settings.zakres = lineEditZakres->text().toFloat();
    settings.nazwaSerwera = lineEditNazwa->text();
    settings.portSerwera = lineEditPort->text().toInt();

    close();
}

OknoGlowne::OknoGlowne(QWidget *wRodzic) : QMainWindow(wRodzic)
{
    zakladki = new Zakladki;
    setCentralWidget(zakladki);
    setWindowTitle(tr("SensGlove"));

    createActions();
    createMenus();
}

void OknoGlowne::closeEvent( QCloseEvent * event )
{
  zakladki->thread.poinformujSerwer();
  event->accept();
}

void OknoGlowne::otworzOknoUstawien()
{
    OknoUstawien * noweOkno = new OknoUstawien();
    noweOkno->show();
}

void OknoGlowne::createActions()
{
    zmienUstawienia = new QAction(tr("Zmień &ustawienia"), this);
    zmienUstawienia->setShortcuts(QKeySequence::New);
    connect(zmienUstawienia, &QAction::triggered, this, &OknoGlowne::otworzOknoUstawien);
}

void OknoGlowne::createMenus()
{
    ustawienia = menuBar()->addMenu(tr("Ustawienia"));
    ustawienia->addAction(zmienUstawienia);
}
