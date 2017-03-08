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

    ui->mdp->setEchoMode(QLineEdit::Password);

    //Connect buton urgence
    connect(ui->buttonAlarme,SIGNAL(clicked()),this,SLOT(arretUrgence()));
    connect(ui->buttonDasacAlarme,SIGNAL(clicked()),&ecl,SLOT(stopArretUrgence()));
    connect(ui->buttonDasacAlarme,SIGNAL(clicked()),this,SLOT(resetAlarme()));

    connect(this,SIGNAL(arretUrg()),&ecl,SLOT(arretUrgence()));
    connect(this,SIGNAL(stopArretUrg()),&ecl,SLOT(stopArretUrgence()));

    //Connect button changement mode
    connect(ui->buttonChangerMode,SIGNAL(triggered()),this,SLOT(changerMode()));
    connect(this,SIGNAL(changeStackedIndexCommande(int)),ui->stackedWidgetCommande,SLOT(setCurrentIndex(int)));
    connect(this,SIGNAL(changeStackedIndexMessage(int)),ui->stackedWidgetMessage,SLOT(setCurrentIndex(int)));
    emit(changeStackedIndexCommande(0));
    emit(changeStackedIndexMessage(0));

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

    connect(ui->vertAvalant,SIGNAL(clicked()),ui->feuAvalant,SLOT(setVert()));
    connect(ui->rougeAvalant,SIGNAL(clicked()),ui->feuAvalant,SLOT(setRouge()));
    connect(ui->vertMontant,SIGNAL(clicked()),ui->feuMontant,SLOT(setVert()));
    connect(ui->rougeMontant,SIGNAL(clicked()),ui->feuMontant,SLOT(setRouge()));

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

    connect(&ecl,SIGNAL(baseError(string)),this,SLOT(logerrAuto(string)));
    connect(&ecl,SIGNAL(verbError(string)),this,SLOT(logerrMan(string)));
    connect(&ecl,SIGNAL(baseMessage(string)),this,SLOT(logmsgAuto(string)));
    connect(&ecl,SIGNAL(verbMessage(string)),this,SLOT(logmsgMan(string)));

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
        case PANNE:
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
        case PANNE:
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
        case ALARME:
            ui->vanneMontant->setStyleSheet("background-color: black;");
            break;
        case PANNE:
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
        case ALARME:
            ui->vanneAvalant->setStyleSheet("background-color: black;");
            break;
        case PANNE:
            ui->vanneAvalant->setStyleSheet("background-color:red;");
            ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
            break;
    }
    ui->vanneAvalant->show();
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

void MainWindow::logmsgAuto(string s)
{
    ui->messageDisplayAuto->setTextColor(Qt::black);
    ui->messageDisplayAuto->append(QString::fromStdString(s));
}

void MainWindow::logerrAuto(string s)
{
    ui->messageDisplayAuto->setTextColor(Qt::red);
    ui->messageDisplayAuto->append(QString::fromStdString(s));
}

void MainWindow::logmsgMan(string s)
{
    ui->messageDisplayMan->setTextColor(Qt::black);
    ui->messageDisplayMan->append(QString::fromStdString(s));
}

void MainWindow::logerrMan(string s)
{
    ui->messageDisplayMan->setTextColor(Qt::red);
    ui->messageDisplayMan->append(QString::fromStdString(s));
}

void MainWindow::arretUrgence()
{
    ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_allume.png"));
    emit(arretUrg());
}

void MainWindow::stopArretUrgence()
{
    ui->alarme->setPixmap(QPixmap(":/images/voyant_rouge_eteind.png"));
    emit(stopArretUrg());
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
           disconnect(&ecl, SIGNAL(signalPorteHautOuverte()),ui->feuMontant,SLOT(setVert()));
           disconnect(&ecl, SIGNAL(signalPorteBasOuverte()),ui->feuAvalant,SLOT(setVert()));
}

void MainWindow::autoTrans(void)
{
    if (autoTransActive == true) return;
    autoTransActive = true;


    ecl.fermetureVanneAvalant();
    ecl.fermetureVanneMontant();
    ui->feuAvalant->setRouge();
    ui->feuMontant->setRouge();

    if ((sender() == ui->buttonEntrer && ui->buttonAvalant->isChecked()) ||
        (sender() == ui->buttonSortir && ui->buttonMontant->isChecked()) )
    {

        connect(&ecl, SIGNAL(signalPorteHautOuverte()),ui->feuMontant,SLOT(setVert()));
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

        connect(&ecl, SIGNAL(signalPorteBasOuverte()),ui->feuAvalant,SLOT(setVert()));
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
    switch(ui->stackedWidgetCommande->currentIndex())
    {
        case 0: emit(changeStackedIndexCommande(1));
                break;
        case 1: emit(changeStackedIndexCommande(0));
                break;
        case 2: emit(changeStackedIndexCommande(0));
                emit(changeStackedIndexMessage(0));break;
    }
}

/////////////////////////////////////////////////////////

void MainWindow::manualFirst(){

    connect(ui->porteAvalantOuv, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
    connect(ui->porteAvalantFerm, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
    connect(ui->porteAvalantArret, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));

    // Connect porte montant
    connect(ui->porteMontantOuv, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
    connect(ui->porteMontantFerm, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
    connect(ui->porteMontantArret, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));

    connect(ui->vertAvalant,SIGNAL(clicked()),
            this,SLOT(stopAutoMod()));
    connect(ui->rougeAvalant,SIGNAL(clicked()),
            this,SLOT(stopAutoMod()));
    connect(ui->vertMontant,SIGNAL(clicked()),
            this,SLOT(stopAutoMod()));
    connect(ui->rougeMontant,SIGNAL(clicked()),this,
            SLOT(stopAutoMod()));

    // Connect vannes
    connect(ui->vanneMontantOuv, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
    connect(ui->vanneMontantFerm, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
    connect(ui->vanneAvalantOuv, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
    connect(ui->vanneAvalantFerm, SIGNAL(clicked()),
            this, SLOT(stopAutoMod()));
}

void MainWindow::valideMdp()
{
    if(ui->mdp->text()=="")
    {

        emit(changeStackedIndexCommande(2));
        emit(changeStackedIndexMessage(1));
        if (autoTransActive == true){
            manualFirst();
        }
    }
    else
    {
        ui->mdp->setText("");
    }
}

void MainWindow::annuleMdp()
{
    emit(changeStackedIndexCommande(0));
}

void MainWindow::inputValeurPanne(void){

   bool ok;
   int i = QInputDialog::getInt(this, tr("Config pannes"),
             tr("Percentage pannes:"), freqPannes, 0, 100, 1, &ok);
   freqPannes = i;
}
