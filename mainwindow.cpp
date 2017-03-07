#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

unsigned char freqPannes = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    autoTransActive = false;
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

    //Connect buton urgence
    connect(ui->buttonAlarme,SIGNAL(clicked()),this,SLOT(arretUrgence()));
    connect(ui->buttonDasacAlarme,SIGNAL(clicked()),this,SLOT(desacAlarme()));

    //Connect button changement mode
    connect(ui->buttonChangerMode,SIGNAL(triggered()),this,SLOT(changerMode()));
    connect(this,SIGNAL(changeStackedIndex(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    emit(changeStackedIndex(0));

    //Connect mdp
    connect(ui->validerMdp,SIGNAL(clicked()),this,SLOT(valideMdp()));
    connect(ui->annulerMdp,SIGNAL(clicked()),this,SLOT(annuleMdp()));

    // Connect porte avalant
    connect(ui->porteAvalantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouverturePorteBas()));
    connect(ui->porteAvalantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermeturePorteBas()));
    connect(ui->porteAvalantArret, SIGNAL(clicked()),
            &ecl, SLOT(arretPorteBas()));
    connect(&ecl, SIGNAL(signalEtatPorteBas(int,int)),
            this, SLOT(avalantDoor(int,int)));

    // Connect porte montant
    connect(ui->porteMontantOuv, SIGNAL(clicked()),
            &ecl, SLOT(ouverturePorteHaut()));
    connect(ui->porteMontantFerm, SIGNAL(clicked()),
            &ecl, SLOT(fermeturePorteHaut()));
    connect(ui->porteMontantArret, SIGNAL(clicked()),
            &ecl, SLOT(arretPorteHaut()));
    connect(&ecl, SIGNAL(signalEtatPorteHaut(int,int)),
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
    connect(&ecl, SIGNAL(signalEtatVanneHaut(int)),
            this, SLOT(montantVanne(int)));
    connect(&ecl, SIGNAL(signalEtatVanneBas(int)),
            this, SLOT(avalantVanne(int)));


    // Connect niveau eau
    connect(&ecl, SIGNAL(newNivEau(int)),this, SLOT(setWaterLevel(int)));

    ///////////////////////////////

    connect(ui->buttonEntrer,SIGNAL(clicked()),this,SLOT(autoTrans()));
    connect(ui->buttonSortir,SIGNAL(clicked()),this,SLOT(autoTrans()));

    connect(&ecl,SIGNAL(error(int)),this,SLOT(logerr(int)));
    connect(&ecl,SIGNAL(message(int)),this,SLOT(logmsg(int)));

    connect(ui->buttonConfigPanne,SIGNAL(triggered()),this,SLOT(inputValeurPanne()));


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
            ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
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
            ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
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
            break;
        case ALARME:
            ui->vanneMontant->setStyleSheet("background-color:red;");
            ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
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
            break;
        case ALARME:
            ui->vanneAvalant->setStyleSheet("background-color:red;");
            ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
            break;
    }
    ui->vanneAvalant->show();
}

void MainWindow::setGreenSignalMontant()
{
    ui->feuMontant->setPixmap(QPixmap(":/images/feu_vert_montant.png"));
}

void MainWindow::setRedSignalMontant()
{
    ui->feuMontant->setPixmap(QPixmap(":/images/feu_rouge_montant.png"));
}

void MainWindow::setRedSignalAvalant()
{
    ui->feuAvalant->setPixmap(QPixmap(":/images/feu_rouge_avalant.png"));
}

void MainWindow::setGreenSignalAvalant()
{
    ui->feuAvalant->setPixmap(QPixmap(":/images/feu_vert_avalant.png"));
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

void MainWindow::logmsg(int mcode)
{
    string s;
    switch(mcode)
    {
       case OUVPORTE: s = "Ouverture porte";
        break;
       case FERMPORTE: s = "Fermature porte";
        break;
       case EAUUP: s = "Eau qui monte";
        break;
       case EAUDOWN: s = "Eau qui descent";
        break;
    }

    ui->messageDisplay->setTextColor(Qt::black);
    ui->messageDisplay->append(QString::fromStdString(s));
}

void MainWindow::logerr(int i)
{
    string s;
    switch(i)
    {
        case EALARMEON: s="Alarme actif"; break;
        case EPORTEOUV: s="Porte ouverte"; break;
        case EVANNEOUV: s="Vanne ouverte"; break;
        case EBADNIVEAU: s="Mauvais niveau d'eau"; break;
    }

    ui->messageDisplay->setTextColor(Qt::red);
    ui->messageDisplay->append(QString::fromStdString(s));
}

void MainWindow::arretUrgence()
{
    ecl.setAlarme(true);
}

void MainWindow::desacAlarme()
{
    ecl.setAlarme(false);
}


/////////////////////////////////////////////////////////////////////////////////////

void MainWindow::stopAutoMod(void){
           autoTransActive = false;
           disconnect(&ecl, SIGNAL(signalPorteBasFerme()),&ecl,SLOT(ouvertureVanneMontant()));
           disconnect(&ecl, SIGNAL(signalEauMax()),&ecl,SLOT(fermetureVanneMontant()));
           disconnect(&ecl, SIGNAL(signalEauMax()),&ecl,SLOT(ouverturePorteHaut()));
           disconnect(&ecl, SIGNAL(signalPorteHautOuverte()),this,SLOT(stopAutoMod()));
           disconnect(&ecl, SIGNAL(signalPorteHautFerme()),&ecl,SLOT(ouvertureVanneAvalant()));
           disconnect(&ecl, SIGNAL(signalEauMin()),&ecl,SLOT(fermetureVanneAvalant()));
           disconnect(&ecl, SIGNAL(signalEauMin()),&ecl,SLOT(ouverturePorteBas()));
           disconnect(&ecl, SIGNAL(signalPorteBasOuverte()),this,SLOT(stopAutoMod()));
}

void MainWindow::autoTrans(void)
{
    if (autoTransActive == true) return;
    autoTransActive = true;


    ecl.fermetureVanneAvalant();
    ecl.fermetureVanneMontant();

    if ((sender() == ui->buttonEntrer && ui->buttonAvalant->isChecked()) ||
        (sender() == ui->buttonSortir && ui->buttonMontant->isChecked()) )
    {

        connect(&ecl, SIGNAL(signalPorteHautOuverte()),this,SLOT(stopAutoMod()));
        if(ecl.getNivEau() < MAX_NIVEAU)
        {
           connect(&ecl, SIGNAL(signalPorteBasFerme()),&ecl,SLOT(ouvertureVanneMontant()));
           connect(&ecl, SIGNAL(signalEauMax()),&ecl,SLOT(fermetureVanneMontant()));
           connect(&ecl, SIGNAL(signalEauMax()),&ecl,SLOT(ouverturePorteHaut()));
           ecl.fermeturePorteBas();
        } else
        {
           ecl.ouverturePorteHaut();

        }
    } else if ((sender() == ui->buttonEntrer && ui->buttonMontant->isChecked()) ||
             (sender() == ui->buttonSortir && ui->buttonAvalant->isChecked()) ){

        connect(&ecl, SIGNAL(signalPorteBasOuverte()),this,SLOT(stopAutoMod()));
        if(ecl.getNivEau() > 0)
        {
           connect(&ecl, SIGNAL(signalPorteHautFerme()),&ecl,SLOT(ouvertureVanneAvalant()));
           connect(&ecl, SIGNAL(signalEauMin()),&ecl,SLOT(fermetureVanneAvalant()));
           connect(&ecl, SIGNAL(signalEauMin()),&ecl,SLOT(ouverturePorteBas()));
           ecl.fermeturePorteHaut();
        } else
        {
           ecl.ouverturePorteBas();

        }

    }
}

void MainWindow::changerMode()
{
    switch(ui->stackedWidget->currentIndex())
    {
        case 0: emit(changeStackedIndex(1)); break;
        case 1: emit(changeStackedIndex(0)); break;
        case 2: emit(changeStackedIndex(0)); break;
    }
}

/////////////////////////////////////////////////////////

void MainWindow::valideMdp()
{
    if(ui->mdp->text()=="")
    {
        emit(changeStackedIndex(2));
    }
    else
    {
        ui->mdp->setText("");
    }
}

void MainWindow::annuleMdp()
{
    emit(changeStackedIndex(0));
}

void MainWindow::inputValeurPanne(void){

   bool ok;
   int i = QInputDialog::getInt(this, tr("Config pannes"),
             tr("Percentage pannes:"), freqPannes, 0, 100, 1, &ok);
   freqPannes = i;
}
