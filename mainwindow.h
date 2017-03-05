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
    void AvalantDoorTransition();
    void MontantDoorTransition();
    void AvalantDoorOpen();
    void MontantDoorOpen();
    void AvalantDoorClose();
    void MontantDoorClose();
    void setGreenSignalMontant();
    void setRedSignalMontant();
};

#endif // MAINWINDOW_H
