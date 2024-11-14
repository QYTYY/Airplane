#include "Widget.h"

#include <QApplication>
#include <flightsearch.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    FlightSearch f;
    //f.show();
    return a.exec();
}
