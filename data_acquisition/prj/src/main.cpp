#include "inc/okno.hh"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Okno w(0);
    w.show();

    return a.exec();
}
