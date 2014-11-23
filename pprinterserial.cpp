#include "pprinterserial.h"

pPrinterSerial::pPrinterSerial(printerType ptype, QObject *parent) :
    pPrinter(ptype,parent), m_serial(this)
{
    connect(&m_serial,SIGNAL(readyRead()),this,SLOT(readSerial()));
}


void pPrinterSerial::setPort(QString serial)
{
    m_serial.setPortName(serial);
}

bool pPrinterSerial::setBauds(quint32 bauds)
{
    m_baudrate = bauds;
    return m_serial.setBaudRate(bauds);
}

bool pPrinterSerial::write(QString datastr)
{
    emit dataTX();
    QByteArray data(datastr.toLatin1());
    if(m_serial.write(data)==data.count())
    {
        m_commandWaiting = true;
        return true;
    } else {
        emit error("error writing data!");
        return false;
    }
}

//SLOTS
void pPrinterSerial::connectPrinter(QString device)
{
    m_connectingMutex.lock();
    m_serial.setPortName(device);
    //m_serial.setBaudRate(m_baudrate);
    if(m_serial.open(QIODevice::ReadWrite)){
        m_connected = true;
    }else {
        m_connected = false;
        m_serial.close();
    }
    m_connectingMutex.unlock();
}

void pPrinterSerial::disconnectPrinter()
{
    m_connectingMutex.lock();
    m_serial.close();
    m_connected = false;
    emit SIGNAL(disconnected());
    m_connectingMutex.unlock();
}

void pPrinterSerial::readSerial()
{
    emit dataRX();
    m_rxBuffer.append(m_serial.readAll());
    parseRxBuffer();
}
