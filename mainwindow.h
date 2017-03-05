#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

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
    void setRedSignalAvalant();
    void setGreenSignalAvalant();
};

#endif // MAINWINDOW_H
