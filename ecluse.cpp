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

void Ecluse::ouvertureVanneMontant(void){
    if (alarme == true) {
        emit error(EVANNE);
        return;
    } else if (porte_haut->getetat() != FERME ||
        porte_bas->getetat() != FERME  ){
        emit error(EVANNE);
        return;
    }

    vanne_haut->ouverture();
}

void Ecluse::ouvertureVanneAvalant(void){
    if (alarme == true) {
        emit error(EVANNE);
        return;
    } if (porte_haut->getetat() != FERME ||
        porte_bas->getetat() != FERME  ){
        emit error(EVANNE);
        return;
    }

    vanne_bas->ouverture();
}

void Ecluse::fermetureVanneMontant(void){
    if (alarme == true) {
        emit error(EVANNE);
        return;
    }
    vanne_haut->fermeture();
}

void Ecluse::fermetureVanneAvalant(void){
    if (alarme == true) {
        emit error(EVANNE);
        return;
    }
    vanne_bas->fermeture();
}

void Ecluse::ouverturePorteBas(void){
    if (alarme == true) {
        emit error(EPORTE);
        return;
    } else if (nivEau > MIN_NIVEAU ||
        vanne_bas->getetat() == OUVERTE ||
        vanne_haut->getetat() == OUVERTE){
        emit error(EEAU);
        cout << "Ecluse: je peut pas ouvrir la porte" << endl;
        return ;
    }
    cout << "Ecluse: ouverture porte bas" << endl;
    porte_bas->ouverture();
}

void Ecluse::ouverturePorteHaut(void){
    if (alarme == true) {
        emit error(EPORTE);
        return;
    } else if (nivEau < MAX_NIVEAU ||
        vanne_bas->getetat() == OUVERTE ||
        vanne_haut->getetat() == OUVERTE){
        emit error(EEAU);
        cout << "Ecluse: je peut pas ouvrir la porte" << endl;
        return ;
    }
    cout << "Ecluse: ouverture porte haut" << endl;
    porte_haut->ouverture();
}

void Ecluse::fermeturePorteBas(void){
    if (alarme == true) {
        emit error(EPORTE);
        return;
    }
    porte_bas->fermeture();
}

void Ecluse::fermeturePorteHaut(void){
    if (alarme == true) {
        emit error(EPORTE);
        return;
    }
    porte_haut->fermeture();
}

void Ecluse::arretPorteHaut(void){
    if (alarme == true) {
        emit error(EPORTE);
        return;
    }
    porte_haut->arret();
}

void Ecluse::arretPorteBas(void){
    if (alarme == true) {
        emit error(EPORTE);
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
}

void Ecluse::getEtatPorteBas(int position,int etat){
    if (etat == ALARME) alarme = true;
    emit signalEtatPorteBas(position,etat);
}

void Ecluse::getEtatPorteHaut(int position,int etat){
    if (etat == ALARME) alarme = true;
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
