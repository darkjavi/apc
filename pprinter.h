#ifndef PPRINTER_H
#define PPRINTER_H

#include <QObject>
#include <QMutex>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QTimer>

class pPrinter : public QObject
{
    Q_OBJECT
public:
    enum printerType{
        printerGeneric,
        printerPrintBot,
        printerPrusaI2,
        printerPrusaI3,
        printerTantillus,
        printerDelta
    };

    enum platformType {
        platformSquare,
        platformDelta
    };

    explicit pPrinter(printerType type = pPrinter::printerGeneric, QObject *parent = 0);
    void setPrinterType(printerType ptype);
    void setPlatformType(platformType ptype);
    void setBuildSize(QVector3D bsize);
    void setBedCenter(QVector2D bcenter);

    virtual  bool isConnected() {if(m_connectingMutex.tryLock(5000)) m_connectingMutex.unlock(); ;return m_connected;}
    void setDevice(QString device){m_device = device;}
    void setExtruderCount(quint8 extruders);
    quint8 getExtruderCount()  {return m_extruderCount;}
    QVector<double> getExtruderTemp();
    double          getBedTemp();
protected:
    QString m_device;
    bool    m_connected;

    QMutex  m_connectingMutex;
    QMutex  m_parseMutex;
    QTimer  m_commandWatchdog;

    printerType  m_printerType;
    platformType m_platformType;

    QVector3D m_buildSize;
    QVector2D m_bedCenter;
    quint8    m_extruderCount;
    QVector<double>    m_lastTemps;
    QVector< QVector<double> > m_tempHist;

    QString   m_rxBuffer;
    QVector<QString> m_txBuffer;
    bool             m_commandWaiting;

    void         appendTemp(QVector<double> ntemps);
    virtual bool write(QString datastr) = 0;

signals:
    void connected();
    void disconnected();
    void error(QString errorString);
    void serialOutput(QString line);
    void temps(QVector<double> exTemps, double bedTemp);
    void dataTX();
    void dataRX();

protected slots:
    void parseRxBuffer();
    void parseLine(QString line);
    void printDebug(QString msg);
    void commandTimeout();
public slots:
    void sendCommand(QString command);
    void connectPrinter();

    virtual void connectPrinter(QString device) = 0;
    virtual void disconnectPrinter()            = 0;
};

#endif // PPRINTER_H
