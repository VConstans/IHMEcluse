#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AvalantDoorTransition()
{
    ui->porteAvalant->setStyleSheet("background-color:orange;");
    ui->porteAvalant->show();
}

void MainWindow::MontantDoorTransition()
{
    ui->porteMontant->setStyleSheet("background-color:orange;");
    ui->porteMontant->show();
}

void MainWindow::AvalantDoorOpen()
{
    ui->porteAvalant->setStyleSheet("background-color: none;");
    ui->porteAvalant->show();
}

void MainWindow::MontantDoorOpen()
{
    ui->porteMontant->setStyleSheet("background-color:none;");
    ui->porteMontant->show();
}

void MainWindow::AvalantDoorClose()
{
    ui->porteAvalant->setStyleSheet("background-color: black;");
    ui->porteAvalant->show();
}

void MainWindow::MontantDoorClose()
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
