#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->porteAvalantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouverturePorteBas()));
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
   // ui->signalMontant->setPixmap();
    ui->signalMontant->show();
}

void MainWindow::setRedSignalMontant()
{
    ui->signalMontant->setStyleSheet("border-image:url(/home/victor/cours/IHM/IHMEcluse/images/voyant_rouge_allume.png);");
    ui->signalMontant->show();


}
