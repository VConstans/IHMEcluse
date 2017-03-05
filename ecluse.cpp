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
