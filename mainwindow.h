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
    void AvalantDoor(int position, int etat);
    void MontantDoor(int position, int etat);
    void setGreenSignalMontant();
    void setRedSignalMontant();
    void setRedSignalAvalant();
    void setGreenSignalAvalant();
    void setAlarme();
    void resetAlarme();
    void setWaterLevel(int wl);
};

#endif // MAINWINDOW_H
