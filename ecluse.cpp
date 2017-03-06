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
        emit error(EALARMEON);
        return;
    } else if (porte_haut->getetat() != FERME ||
               porte_bas->getetat() != FERME  ){
        emit error(EPORTEOUV);
        return;
    }

    emit message(EAUUP);
    vanne_haut->ouverture();
}

void Ecluse::ouvertureVanneAvalant(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    } if (porte_haut->getetat() != FERME ||
          porte_bas->getetat() != FERME  ){
        emit error(EPORTEOUV);
        return;
    }

    emit message(EAUDOWN);
    vanne_bas->ouverture();
}

void Ecluse::fermetureVanneMontant(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    }
    vanne_haut->fermeture();
}

void Ecluse::fermetureVanneAvalant(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    }
    vanne_bas->fermeture();
}

void Ecluse::ouverturePorteBas(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    } else if (nivEau > MIN_NIVEAU) {
        emit error(EBADNIVEAU);
        return ;
    } else if (vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE){
        emit error(EVANNEOUV);
        return ;
    }
    emit message(OUVPORTE);
    porte_bas->ouverture();
}

void Ecluse::ouverturePorteHaut(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    } else if (nivEau < MAX_NIVEAU) {
        emit error(EBADNIVEAU);
        return ;
    } else if(vanne_bas->getetat() == OUVERTE ||
               vanne_haut->getetat() == OUVERTE){
        emit error(EVANNEOUV);
        return ;
    }
    emit message(OUVPORTE);
    porte_haut->ouverture();
}

void Ecluse::fermeturePorteBas(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    }
    emit message(FERMPORTE);
    porte_bas->fermeture();
}

void Ecluse::fermeturePorteHaut(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    }
    emit message(FERMPORTE);
    porte_haut->fermeture();
}

void Ecluse::arretPorteHaut(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    }
    porte_haut->arret();
}

void Ecluse::arretPorteBas(void){
    if (alarme == true) {
        emit error(EALARMEON);
        return;
    }
    porte_bas->arret();
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
