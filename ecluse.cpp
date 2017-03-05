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

    nivEau = 0;
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
    if (porte_haut->getetat() != FERME ||
        porte_bas->getetat() != FERME  ){
        emit error(EPORTE);
        return;
    }

    vanne_haut->ouverture();
}

void Ecluse::ouvertureVanneAvalant(void){
    if (porte_haut->getetat() != FERME ||
        porte_bas->getetat() != FERME  ){
        emit error(EPORTE);
        return;
    }

    vanne_bas->ouverture();
}

void Ecluse::fermatureVanneMontant(void){
    vanne_haut->fermature();
}

void Ecluse::fermatureVanneAvalant(void){
    vanne_bas->fermature();
}

void Ecluse::ouverturePorteBas(void){
    if (nivEau > MIN_NIVEAU ||
        vanne_bas->getetat() == OUVERTE ||
        vanne_haut->getetat() == OUVERTE){
        emit error(EEAU);
        return ;
    }
    porte_bas->ouverture();
}

void Ecluse::ouverturePorteHaut(void){
    if (nivEau < MAX_NIVEAU ||
        vanne_bas->getetat() == OUVERTE ||
        vanne_haut->getetat() == OUVERTE){
        emit error(EEAU);
        return ;
    }
    porte_haut->ouverture();
}

void Ecluse::fermaturePorteBas(void){
    porte_bas->fermature();
}

void Ecluse::fermaturePorteHaut(void){
    porte_haut->fermature();
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
