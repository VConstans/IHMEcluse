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
    void avalantDoor(int position, int etat);
    void montantDoor(int position, int etat);
    void montantVanne(int etat);
    void avalantVanne(int etat);
    void setGreenSignalMontant();
    void setRedSignalMontant();
    void setRedSignalAvalant();
    void setGreenSignalAvalant();
    void setAlarme();
    void resetAlarme();
    void setWaterLevel(int wl);
    void appendText(string s);
    void autoTrans(void);
    void stopAutoMod(void);
};

#endif // MAINWINDOW_H
