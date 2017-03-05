#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ecluse.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ecluse ecl;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void avalantDoorTransition();
    void montantDoorTransition();
    void avalantDoorOpen();
    void montantDoorOpen();
    void avalantDoorClose();
    void montantDoorClose();
    void setGreenSignalMontant();
    void setRedSignalMontant();
    void setRedSignalAvalant();
    void setGreenSignalAvalant();
};

#endif // MAINWINDOW_H
