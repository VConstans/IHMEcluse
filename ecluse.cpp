#include "ecluse.h"
#include <iostream>

Ecluse::Ecluse(QObject *parent) :
    QObject(parent)
{
    vanne_bas = new Vanne();
    vanne_bas->moveToThread(&threadVanne_bas);
    connect(vanne_bas,SIGNAL(envoiEtat(int,bool)),
            this,SLOT(test_recoitSignal(int,bool)));
    connect(this,SIGNAL(test_sendSignal()),vanne_bas,SLOT(fermature()));
    threadVanne_bas.start();

    vanne_haut = new Vanne();
    vanne_haut->moveToThread(&threadVanne_haut);
    connect(vanne_haut,SIGNAL(envoiEtat(int,bool)),
            this,SLOT(test_recoitSignal(int,bool)));
    threadVanne_haut.start();

    porte_haut = new Porte();
    porte_bas = new Porte();

    // test
    emit test_sendSignal();
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

void Ecluse::test_recoitSignal(int etat, bool alarme){
   std::cout << "received" << std::endl;
}
