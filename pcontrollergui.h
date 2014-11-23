#ifndef PCONTROLLERGUI_H
#define PCONTROLLERGUI_H

#include <QMainWindow>

namespace Ui {
class pControllerGui;
}

class pControllerGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit pControllerGui(QWidget *parent = 0);
    ~pControllerGui();

private:
    Ui::pControllerGui *ui;
};

#endif // PCONTROLLERGUI_H
