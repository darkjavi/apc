#include "pcontrollergui.h"
#include "ui_pcontrollergui.h"

pControllerGui::pControllerGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pControllerGui)
{
    ui->setupUi(this);
}

pControllerGui::~pControllerGui()
{
    delete ui;
}
