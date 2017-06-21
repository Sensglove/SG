//Najnowsza wersja aplikacji na https://github.com/Sensglove/SG w katalogu ''wizualizacja''
#include <QApplication>
#include "inc/zakladki.hpp"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    OknoGlowne Okno;

    Okno.show();

    return App.exec();
}
