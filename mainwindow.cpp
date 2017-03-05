#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisation
    ui->waterLevel->setMinimum(MIN_NIVEAU);
    ui->waterLevel->setMaximum(MAX_NIVEAU);
    ui->waterLevel->setValue(0);

    ui->progressPorteMontant->setMinimum(0);
    ui->progressPorteMontant->setMaximum(MAX_FERMETURE);
    ui->progressPorteMontant->setValue(MAX_FERMETURE);

    ui->progressPorteAvalant->setMinimum(0);
    ui->progressPorteAvalant->setMaximum(MAX_FERMETURE);
    ui->progressPorteAvalant->setValue(MAX_FERMETURE);


    // Connect porte avalant
    connect(ui->porteAvalantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouverturePorteBas()));
    connect(ui->porteAvalantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermeturePorteBas()));
    connect(ui->porteAvalantArret, SIGNAL(clicked()),
            ecl.porte_bas, SLOT(arret()));
    connect(ecl.porte_bas, SIGNAL(signaletat(int,int)),
            this, SLOT(avalantDoor(int,int)));

    // Connect porte montant
    connect(ui->porteMontantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouverturePorteHaut()));
    connect(ui->porteMontantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermeturePorteHaut()));
    connect(ui->porteMontantArret, SIGNAL(clicked()),
            ecl.porte_haut, SLOT(arret()));
    connect(ecl.porte_haut, SIGNAL(signaletat(int,int)),
            this, SLOT(montantDoor(int,int)));

    // Connect vannes
    connect(ui->vanneMontantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouvertureVanneMontant()));
    connect(ui->vanneMontantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermetureVanneMontant()));
    connect(ui->vanneAvalantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouvertureVanneAvalant()));
    connect(ui->vanneAvalantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermetureVanneAvalant()));
    connect(ecl.vanne_haut, SIGNAL(signaletat(int)),
            this, SLOT(montantVanne(int)));
    connect(ecl.vanne_bas, SIGNAL(signaletat(int)),
            this, SLOT(avalantVanne(int)));


    // Connect niveau eau
    connect(&ecl, SIGNAL(newNivEau(int)),this, SLOT(setWaterLevel(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::avalantDoor(int position, int etat)
{
    switch(etat)
    {
        case OUVERTE:
            ui->porteAvalant->setStyleSheet("background-color: none;");
            break;
        case FERME:
            ui->porteAvalant->setStyleSheet("background-color: black;");
            break;
        case OUVERTURE:
            ui->porteAvalant->setStyleSheet("background-color:orange;");
            break;
        case FERMETURE:
            ui->porteAvalant->setStyleSheet("background-color:orange;");
            break;
        case ARRETE:
            ui->porteAvalant->setStyleSheet("background-color:orange;");
            break;
        case ALARME:
            ui->porteAvalant->setStyleSheet("background-color:red;");
            break;
    }
    ui->porteAvalant->show();

    ui->progressPorteAvalant->setValue(position);
    ui->progressPorteAvalant->show();
}

void MainWindow::montantDoor(int position, int etat)
{
    switch(etat)
    {
        case OUVERTE:
            ui->porteMontant->setStyleSheet("background-color: none;");
            break;
        case FERME:
            ui->porteMontant->setStyleSheet("background-color: black;");
            break;
        case OUVERTURE:
            ui->porteMontant->setStyleSheet("background-color:orange;");
            break;
        case FERMETURE:
            ui->porteMontant->setStyleSheet("background-color:orange;");
            break;
        case ARRETE:
            ui->porteMontant->setStyleSheet("background-color:orange;");
            break;
        case ALARME:
            ui->porteMontant->setStyleSheet("background-color:red;");
            break;
    }

    ui->porteMontant->show();

    ui->progressPorteMontant->setValue(position);
    ui->progressPorteMontant->show();
}

void MainWindow::montantVanne(int etat)
{
    switch(etat)
    {
        case OUVERTE:
            ui->vanneMontant->setStyleSheet("background-color: none;");
            break;
        case FERME:
            ui->vanneMontant->setStyleSheet("background-color: black;");
                      cout << etat << endl;
            break;
        case ALARME:
            ui->vanneMontant->setStyleSheet("background-color:red;");
            break;
    }
    ui->vanneMontant->show();
}

void MainWindow::avalantVanne(int etat)
{
    switch(etat)
    {
        case OUVERTE:
            ui->vanneAvalant->setStyleSheet("background-color: none;");
            break;
        case FERME:
            ui->vanneAvalant->setStyleSheet("background-color: black;");
            cout << etat << endl;
            break;
        case ALARME:
            ui->vanneAvalant->setStyleSheet("background-color:red;");
            break;
    }
    ui->vanneAvalant->show();
}

void MainWindow::setGreenSignalMontant()
{
    ui->signalMontant->setPixmap(QPixmap(":/images/voyant_vert_allume.png"));
}

void MainWindow::setRedSignalMontant()
{
    ui->signalMontant->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
}

void MainWindow::setRedSignalAvalant()
{
    ui->signalAvalant->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
}

void MainWindow::setGreenSignalAvalant()
{
    ui->signalAvalant->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
}

void MainWindow::setAlarme()
{
    ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
}

void MainWindow::resetAlarme()
{
    ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_eteind.png"));
}

void MainWindow::setWaterLevel(int wl)
{
    ui->waterLevel->setValue(wl);
}
