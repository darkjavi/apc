#ifndef PPRINTERWIDGET_H
#define PPRINTERWIDGET_H

#include <QFrame>

#include "pprinterserial.h"
#include "vpgles2widget.h"


namespace Ui {
class pPrinterWidget;
}

class pPrinterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit pPrinterWidget(pPrinter* printer = 0,QWidget *parent = 0);
    ~pPrinterWidget();
    void   setPrinter(pPrinter* printer);
    pPrinter* printer() {return m_printer;}
private:
    Ui::pPrinterWidget *ui;
    pPrinter* m_printer;
    vpGLES2Widget bedView;
protected slots:
    void on_connectBtn_clicked();
    void on_sendCommand_clicked();

    void printerConnected();
    void printerDisconnected();
};

#endif // PPRINTERWIDGET_H
