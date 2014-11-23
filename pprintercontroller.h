#ifndef PPRINTERCONTROLLER_H
#define PPRINTERCONTROLLER_H

#include <QObject>
#include <QVector>

#include "pprinterserial.h"

class pPrinterController : public QObject
{
    Q_OBJECT
public:
    explicit pPrinterController(QObject *parent = 0);

signals:
    void error(QString errorString);
public slots:
#ifdef DEBUG
    void debugMsg();
#endif

};

#endif // PPRINTERCONTROLLER_H
