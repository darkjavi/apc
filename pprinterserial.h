#ifndef PPRINTERSERIAL_H
#define PPRINTERSERIAL_H

#include "pprinter.h"

#include <qserialport.h>

class pPrinterSerial : public pPrinter
{
    Q_OBJECT
public:
    explicit pPrinterSerial(pPrinter::printerType ptype = pPrinter::printerGeneric,QObject *parent = 0);
    void setPort(QString serial);
    bool setBauds(quint32 bauds);
protected:
    QSerialPort m_serial;
    quint32     m_baudrate;

    bool write(QString datastr);
signals:
private slots:
    void readSerial();
public slots:
    virtual void connectPrinter(QString device);
    virtual void disconnectPrinter();
};

#endif // PPRINTERSERIAL_H
