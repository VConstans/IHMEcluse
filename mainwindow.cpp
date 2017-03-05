#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->porteAvalantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouverturePorteBas()));
    connect(ui->porteAvalantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermeturePorteBas()));
    connect(ui->porteAvalantArret, SIGNAL(clicked()),
            ecl.porte_bas, SLOT(arret()));

    connect(ui->porteMontantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouverturePorteHaut()));
    connect(ui->porteMontantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermeturePorteHaut()));
    connect(ui->porteMontantArret, SIGNAL(clicked()),
            ecl.porte_haut, SLOT(arret()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::avalantDoorTransition()
{
    ui->porteAvalant->setStyleSheet("background-color:orange;");
    ui->porteAvalant->show();
}

void MainWindow::montantDoorTransition()
{
    ui->porteMontant->setStyleSheet("background-color:orange;");
    ui->porteMontant->show();
}

void MainWindow::avalantDoorOpen()
{
    ui->porteAvalant->setStyleSheet("background-color: none;");
    ui->porteAvalant->show();
}

void MainWindow::montantDoorOpen()
{
    ui->porteMontant->setStyleSheet("background-color:none;");
    ui->porteMontant->show();
}

void MainWindow::avalantDoorClose()
{
    ui->porteAvalant->setStyleSheet("background-color: black;");
    ui->porteAvalant->show();
}

void MainWindow::montantDoorClose()
{
    ui->porteMontant->setStyleSheet("background-color:black;");
    ui->porteMontant->show();
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
