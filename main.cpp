#include "pcontrollergui.h"
#include <QApplication>
#include "pprinterserial.h"
#include "pprinterwidget.h"

#include <QDebug>

#define DEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //pControllerGui w;
    //w.show();
    pPrinterWidget w;
    w.show();
    return a.exec();
}
