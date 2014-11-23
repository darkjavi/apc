#include "pprinterwidget.h"
#include "ui_pprinterwidget.h"

pPrinterWidget::pPrinterWidget(pPrinter* printer,QWidget* parent) :
    QFrame(parent),
    ui(new Ui::pPrinterWidget)
{
    ui->setupUi(this);
    pPrinterSerial* p = new pPrinterSerial();
    p->setDevice("/dev/ttyUSB0");
    //p->setBauds(250000);
//    printer = p;
//    if(printer){
      setPrinter(p);
//     }

    ui->connectBtn->setChecked(false);
    ui->gb_view->layout()->addWidget(&bedView);
}

pPrinterWidget::~pPrinterWidget()
{
    delete ui;
}

void pPrinterWidget::setPrinter(pPrinter *printer)
{
    m_printer = printer;
    connect(m_printer,SIGNAL(serialOutput(QString)),ui->termOut,SLOT(append(QString)));
    connect(m_printer,SIGNAL(connected()),this,SLOT(printerConnected()));
    connect(m_printer,SIGNAL(disconnected()),this,SLOT(printerDisconnected()));
}

void pPrinterWidget::on_sendCommand_clicked()
{
    if(ui->termIn->text().isEmpty())
    {
        ui->termOut->append("Nothing to send!?");
        return;
    }
    if(m_printer->isConnected()){
        m_printer->sendCommand(ui->termIn->text()+"\n");
        ui->termOut->append(ui->termIn->text());
        ui->termIn->clear();
    } else {
        ui->termOut->append("Not Connected!!!");
    }
}

void pPrinterWidget::on_connectBtn_clicked()
{
    if(!ui->connectBtn->isChecked()) {
        m_printer->disconnectPrinter();
    } else {
        m_printer->connectPrinter();
        ui->connectBtn->setText("Connecting...");
        ui->connectBtn->setChecked(true);
    }
}

void pPrinterWidget::printerConnected()
{
    ui->connectBtn->setText("Disconnect");
    ui->connectBtn->setChecked(true);
}

void pPrinterWidget::printerDisconnected()
{
    ui->connectBtn->setText("Connect");
    ui->connectBtn->setChecked(false);
}
