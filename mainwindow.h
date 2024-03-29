#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
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
    bool autoTransActive;
    Ui::MainWindow *ui;

signals:
    void changeStackedIndexCommande(int);
    void changeStackedIndexMessage(int);

    void arretUrg();
    void stopArretUrg();

public slots:
    void avalantDoor(int position, int etat);
    void montantDoor(int position, int etat);
    void montantVanne(int etat);
    void avalantVanne(int etat);
    void inputValeurPanne();
    void setAlarme();
    void resetAlarme();
    void setWaterLevel(int wl);
    void logmsgAuto(string s);
    void logerrAuto(string s);
    void logerrMan(string s);
    void logmsgMan(string s);
    void autoTrans(void);
    void stopAutoMod(void);
    void changerMode();
    void valideMdp();
    void annuleMdp();
    void arretUrgence();
    void stopArretUrgence();
    void manualFirst();
};

#endif // MAINWINDOW_H
