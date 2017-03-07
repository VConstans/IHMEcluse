#include "ecluse.h"
#include <iostream>


Ecluse::Ecluse(QObject *parent) :
    QObject(parent)
{
    vanne_bas = new Vanne();
    vanne_bas->moveToThread(&threadVanne_bas);
    threadVanne_bas.start();

    vanne_haut = new Vanne();
    vanne_haut->moveToThread(&threadVanne_haut);
    threadVanne_haut.start();

    porte_haut = new Porte();
    porte_bas = new Porte();

    timer_remplissage = new QTimer(this);
    connect(timer_remplissage,SIGNAL(timeout()),
            this,SLOT(updateNivEau()));
    timer_remplissage->start(FREQ_UPDATE);

    connect(porte_bas, SIGNAL(signaletat(int,int)),this,SLOT(getEtatPorteBas(int,int)));
    connect(porte_haut, SIGNAL(signaletat(int,int)),this,SLOT(getEtatPorteHaut(int,int)));
    connect(vanne_bas, SIGNAL(signaletat(int)),this,SLOT(getEtatVanneBas(int)));
    connect(vanne_haut, SIGNAL(signaletat(int)),this,SLOT(getEtatVanneHaut(int)));

    nivEau = 0;
    alarme = false;
}


Ecluse::~Ecluse(){
    threadVanne_bas.quit();
    threadVanne_haut.quit();
    threadVanne_bas.wait();
    threadVanne_haut.wait();

    delete vanne_bas;
    delete vanne_haut;
    delete porte_bas;
    delete porte_haut;
}

void Ecluse::setAlarme(bool v)
{
    this->alarme=v;
}

void Ecluse::ouvertureVanneMontant(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible ouvrir vanne montant");
        return;
    } else if (porte_haut->getetat() != FERME ||
               porte_bas->getetat() != FERME  ){
        emit baseError("Error: impossible ouvrir vanne montant");
        emit verbError("--> Porte ouverte");
        return;
    }

    vanne_haut->ouverture();
    emit baseMessage("L'eau monte");
    emit verbMessage("--> Vanne montant ouverte");
}

void Ecluse::ouvertureVanneAvalant(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible ouvrir vanne avalant");
        return;
    } if (porte_haut->getetat() != FERME ||
          porte_bas->getetat() != FERME  ){
        emit baseError("Error: impossible ouvrir vanne avalant");
        emit verbError("--> Porte ouverte");
        return;
    }

    vanne_bas->ouverture();
    emit baseMessage("L'eau baisse");
    emit verbMessage("--> Vanne avalant ouverte");
}

void Ecluse::fermetureVanneMontant(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible fermer vanne montant");
        return;
    }
    vanne_haut->fermeture();
    emit verbMessage("Fermature vanne montant");
}

void Ecluse::fermetureVanneAvalant(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible fermer vanne avalant");
        return;
    }
    vanne_bas->fermeture();
    emit verbMessage("Fermature vanne avalant");
}

void Ecluse::ouverturePorteBas(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible ouvrir porte avalant");
        return;
    } else if (nivEau > MIN_NIVEAU) {
        emit baseError("Error: impossible ouvrir porte avalant");
        emit verbError("--> Niveau de l'eau trop eleve");
        return ;
    } else if (vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE){
        emit baseError("Error: impossible ouvrir porte avalant");
        emit verbError("--> Vanne ouverte");
        return ;
    }
    emit baseMessage("Ouverture porte avalant");
    porte_bas->ouverture();
}

void Ecluse::ouverturePorteHaut(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible ouvrir porte montant");
        return;
    } else if (nivEau < MAX_NIVEAU) {
        emit baseError("Error: impossible ouvrir porte montant");
        emit verbError("--> Niveau de l'eau trop eleve");
        return ;
    } else if(vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE){
        emit baseError("Error: impossible ouvrir porte montant");
        emit verbError("--> Vanne ouverte");
        return ;
    }
    emit baseMessage("Ouverture porte montant");
    porte_haut->ouverture();
}

void Ecluse::fermeturePorteBas(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible fermer porte avalant");
        return;
    }
    emit baseMessage("Fermature porte avalant");
    porte_bas->fermeture();
}

void Ecluse::fermeturePorteHaut(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible fermer porte montant");
        return;
    }
    emit baseMessage("Fermature porte montant");
    porte_haut->fermeture();
}

void Ecluse::arretPorteHaut(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible arreter porte montant");
        return;
    }
    emit verbMessage("Arret porte montant");
    porte_haut->arret();
}

void Ecluse::arretPorteBas(void){
    if (alarme == true) {
        emit baseError("Error: alarme actif");
        emit verbError("--> Impossible arreter porte avalant");
        return;
    }
    emit verbMessage("Arret porte avalant");
}

void Ecluse::updateNivEau(void){
    if (vanne_bas->getetat() == OUVERTE &&
        vanne_haut->getetat() == OUVERTE){

        if (nivEau > MID_NIVEAU) nivEau  -= DEBIT_EAU/2;
        if (nivEau < MID_NIVEAU) nivEau += DEBIT_EAU/2;

    } else if (vanne_bas->getetat() == OUVERTE) {

        if (nivEau > MIN_NIVEAU) nivEau -= DEBIT_EAU;

    } else if (vanne_haut->getetat() == OUVERTE){

        if (nivEau < MAX_NIVEAU) nivEau += DEBIT_EAU;

    } else return;

    emit newNivEau(nivEau);

    if (nivEau == MAX_NIVEAU){
       emit signalEauMax();
    } else if (nivEau == 0) {
       emit signalEauMin();
    }
}

void Ecluse::getEtatPorteBas(int position,int etat){
    switch (etat){
        case ALARME: alarme =true;
        break;
         case FERME: emit signalPorteBasFerme();
        break;
         case OUVERTE: emit signalPorteBasOuverte();
        break;
    }

    emit signalEtatPorteBas(position,etat);
}

void Ecluse::getEtatPorteHaut(int position,int etat){
    switch (etat){
        case ALARME: alarme =true;
        break;
        case FERME: emit signalPorteHautFerme();
        break;
        case OUVERTE: emit signalPorteHautOuverte();
        break;
    }
    emit signalEtatPorteHaut(position,etat);
}

void Ecluse::getEtatVanneBas(int etat){
    if (etat == ALARME) alarme = true;
    emit signalEtatVanneBas(etat);
}

void Ecluse::getEtatVanneHaut(int etat){
    if (etat == ALARME) alarme = true;
    emit signalEtatVanneHaut(etat);
}

 int Ecluse::getNivEau()
 {
     return nivEau;
 }
