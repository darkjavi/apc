#include "pprinter.h"

#include <QDebug>

pPrinter::pPrinter(printerType type, QObject *parent) :
    QObject(parent)
{
    m_commandWaiting = false;
    m_connected = false;
    setPrinterType(type);
    connect(this,SIGNAL(error(QString)),this,SLOT(printDebug(QString)));
    connect(&m_commandWatchdog,SIGNAL(timeout()),this,SLOT(commandTimeout()));
    m_commandWatchdog.setInterval(10000); // 10 segundos de timeout para el comando enviado

    setExtruderCount(1);

}

void pPrinter::setPrinterType(printerType ptype)
{
    m_printerType = ptype;
    if(m_printerType == printerDelta) setPlatformType(platformDelta);
    else setPlatformType(platformSquare);
}

void pPrinter::setPlatformType(platformType ptype)
{
    m_platformType = ptype;
}

void pPrinter::setBuildSize(QVector3D bsize)
{
    m_buildSize = bsize;
    if(m_platformType == platformDelta)
    {
        setBedCenter(QVector2D(0,0));
    } else {
        setBedCenter(QVector2D(bsize.x()/2,bsize.y()/2));
    }
}

void pPrinter::setBedCenter(QVector2D bcenter)
{
    m_bedCenter = bcenter;
}


void pPrinter::appendTemp(QVector<double> ntemps)
{
    if(ntemps.count() != m_extruderCount+1)
    {
        emit error("Temp count doesnt match!");
        return;
    }
    m_lastTemps = ntemps;
    m_tempHist.append(ntemps);
    emit temps(m_lastTemps.mid(0,m_lastTemps.count()-1),m_lastTemps.last());
}

void pPrinter::setExtruderCount(quint8 extruders)
{
    m_extruderCount = extruders;
    m_lastTemps.clear();
    m_tempHist.clear();
    QVector<double> init_temps;
    for(int i = 0 ; i < extruders + 1 ; i++) //la ultima temperatura es de la cama
    {
        init_temps.append(0);
    }
    m_lastTemps = init_temps;
    m_tempHist.append(init_temps);
}

QVector<double> pPrinter::getExtruderTemp()
{
    return m_lastTemps.mid(0,m_lastTemps.count()-1);
}

double          pPrinter::getBedTemp()
{
    return m_lastTemps.last();
}


void pPrinter::parseRxBuffer()
{
    m_parseMutex.lock();
        if(m_rxBuffer.contains("\n")) //comprobamos si hay almenos una linea completa en el buffer
        {
            QStringList lines = m_rxBuffer.split("\n");
            quint16 parsedCount = 0;
            lines.removeLast(); // borro el ultimo item, pues va a ser o bien un string vacio si el chorizo terminaba con \n
                                //o una cadena sin finalizar
            for(int l = 0 ; l < lines.count() ; l++)
            {
                QString line = lines.at(l);
                parseLine(line);
                parsedCount += line.count()+1;
            }
            m_rxBuffer.remove(0,parsedCount);
        }
    m_parseMutex.unlock();
    if(m_txBuffer.count() && !m_commandWaiting)
    {
        write(m_txBuffer.first());
        m_txBuffer.removeFirst();
    }
}

void pPrinter::parseLine(QString line)
{
    emit serialOutput(line);

    if(line.contains("ok"))
    {
        m_commandWatchdog.stop();
        m_commandWaiting = false;
        if(line.startsWith("ok") && line.contains("T0:"))
        {// aparentemente esta es la linea de repuesta del M105
            QStringList args = line.split(" ");
            double t0 = args.at(1).split(":").at(1).toDouble();
            double b = args.at(3).split(":").at(1).toDouble();
            QVector<double> result;
            result << t0 << b;
            appendTemp(result);
        }
    }

}

void pPrinter::sendCommand(QString command)
{
    if(m_commandWaiting)
    {
        m_txBuffer.append(command);
    } else {
        write(command);
        m_commandWatchdog.start();
    }
}

void pPrinter::commandTimeout()
{
    emit error("Command Timeout!!!");
    //?
}

void pPrinter::connectPrinter()
{
    if(!m_device.isEmpty())
    {
        connectPrinter(m_device);
    }else {
        emit error("No device set!");
    }
}


void pPrinter::printDebug(QString msg)
{
    qDebug() << msg;
}
